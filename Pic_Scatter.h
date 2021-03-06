#pragma once

struct ScatterPoint
{
	S16 x;
	S16 y;
};

class ScatterData 
{
public:
	ScatterData() 
	{	
		ClearData();
	};
	~ScatterData() {};

	void SetOrigin();
	void LockEnuData() { setEnuCs.Lock(); }
	void UnlockEnuData() { setEnuCs.Unlock(); }
	void LockLlaData() { setLlaCs.Lock(); }
	void UnlockLlaData() { setLlaCs.Unlock(); }


	double m_enuScale;
	int m_llaScale;

	double mapoffset_x;
	double mapoffset_y;
	bool  m_isGetMapPos;

	int inimaplondeg, inimaplonmin, inimaplonsec, inimaplatdeg, inimaplatmin, inimaplatsec;
	long double  inimaplon, inimaplat, initiallon, initiallat;
	bool IniPos;
	double m_lon;
	double m_lat;
	long double WGS84_X;//initial position
	long double WGS84_Y;//initial position
	long double WGS84_Z;//initial position
	double int_N; //initial data
	double lon_deg;
	double lat_deg;
	Matrix _WGS842NEU;
	Matrix ENU;
	//double current_x, current_y;

    int maplondeg_t,  maplonmin_t;  
	double maplonsec_t; 
	int	maplatdeg_t,  maplatmin_t;
	double maplatsec_t;
    long double  maplon_t, maplat_t, lon_t, lat_t, pmlon,  pmlat;
	long double wgs84_X;
	long double wgs84_Y;
	long double wgs84_Z;
	double      CEP;
    double      TwoDrms;
	long double rms_x;
    long double rms_y;
	double enu_y_mean;
	double enu_x_mean;

	void ClearData()
	{
		//20151029 Doesn't change center point after re-connect or restart, request by Oliver
		_WGS842NEU.SetSize(3, 3);
		m_lon = 0;
		m_lat = 0;
		mapoffset_x = 0;
		mapoffset_y = 0;	
		m_isGetMapPos = false;	

		m_lon = 0.0;	
		m_lat = 0.0;
		WGS84_X = 0.0;	
		WGS84_Y = 0.0;	
		WGS84_Z = 0.0;
		ini_h = 0.0;	
		int_N = 0.0;
		
		wgs84_X = wgs84_Y = wgs84_Z = 0.0;
		ENU.SetSize(3, 1);
		ENU(0, 0) = 0.0;
		ENU(1, 0) = 0.0;
		ENU(2, 0) = 0.0;
		IniPos = true;
		CEP = 0.0;  
		TwoDrms = 0.0;
		rms_x = 0.0;	
		rms_y = 0.0;
		enu_y_mean = enu_x_mean = 0.0F;
		
		Clear();
	}

	void ChangeCoordinateLLA()
	{
		if( inimaplondeg != maplondeg_t || inimaplonmin != maplonmin_t || 
			inimaplonsec != maplonsec_t || inimaplatdeg != maplatdeg_t || 
			inimaplatmin != maplatmin_t || inimaplatsec != maplatsec_t)
		{
			int dif_x,dif_y;			
			dif_x = (int)maplonsec_t - inimaplonsec;
			dif_y = (int)maplatsec_t - inimaplatsec;
			mapoffset_x = (float)(50*(-1*dif_x));
			mapoffset_y = (float)(50*(dif_y));			
		}
		else
		{
			mapoffset_x=0;
			mapoffset_y=0;
		}
		inimaplon     = maplon_t;
		inimaplat     = maplat_t;		
		inimaplondeg  = maplondeg_t;
		inimaplonmin  = maplonmin_t;
		inimaplonsec  = (int)maplonsec_t;
		inimaplatdeg  = maplatdeg_t;
		inimaplatmin  = maplatmin_t;
		inimaplatsec  = (int)maplatsec_t;
	}

	void ChangeENUScale(int index)
	{
#if MORE_ENU_SCALE
		const double enuTable[] = { 0.01, 0.05, 0.1, 0.2, 0.5, 1.0, 2.0, 3.0, 5.0, 
			10.0, 20.0, 30.0, 40.0, 50.0, 100.0, 150.0, 200.0, 300.0 };
#else
		const int enuTable[] = { 1, 2, 3, 5, 10, 20, 30, 40, 50, 100, 150, 200, 300 };
#endif
		m_enuScale = enuTable[index];
	}

	void ChangeLLAScale(int index)
	{
		const int llaTable[] = { 1, 2, 3, 5, 10, 60, 120, 180, 300, 600 };
		mapoffset_x = 0;
		mapoffset_y = 0;
		m_llaScale = llaTable[index];
	}

	void SetMapLocation(double lon, double lat)
	{
		maplondeg_t = int(lon/100);
		maplonmin_t = (int)lon-int(lon/100)*100;
		maplonsec_t = ((lon-(int)lon)*60.0);

		maplatdeg_t = int(lat/100);
		maplatmin_t = (int)lat-int(lat/100)*100;
		maplatsec_t = ((lat-(int)lat)*60.0);

		maplon_t = maplondeg_t+(double)maplonmin_t/60+(double)maplonsec_t/3600;
		maplat_t = maplatdeg_t+(double)maplatmin_t/60+(double)maplatsec_t/3600;  
	}

	void Clear()
	{
		LockLlaData();			
		llaPointSet.clear();			
		UnlockLlaData();		

		LockEnuData();
		enu_x.clear();
		enu_y.clear();	
		UnlockEnuData();
	}

	void SetENU(double lon, double lat, double h);
	void InitPos();
	void AddLLAPoint(ScatterPoint* llaPoint);
	const vector<ScatterPoint>& GetLLAPoint() const
	{ return llaPointSet; };
	list<double> enu_x;	
	list<double> enu_y;
	double ini_h; //initial data	    

protected:
	vector<ScatterPoint> llaPointSet;	
	CCriticalSection setEnuCs;		//_GET_ENU_POINT_CS;
	CCriticalSection setLlaCs;		//_GET_LLA_POINT_CS;	
	//CCriticalSection _GETENUPOINTCS;

	void SetRotationMatrix();

};
extern ScatterData g_scatterData;

class ScatterLLA 
{
public:
    ScatterLLA(double lon, double lat, float alt)
    {
        longitude = lon;
        latitude = lat;
        altitude = alt;
    }

    ScatterLLA()
    {
        longitude = 0;
        latitude = 0;
        altitude = 0;
    }

    double GetLontitude() { return longitude; }
    double GetLatitude() { return latitude; }
    float GetAltitude() { return altitude; }

    void SetCurrentX(double x) { currentX = x; }
	void SetCurrentY(double y) { currentY = y; }

protected:
	double longitude;
    double latitude;
    float altitude;
    double currentX;
    double currentY;
    double enu_u;
    double wgs_x;
    double wgs_y;
    double wgs_z;
    double plot_x;
    double plot_y;
};

class BaseMat
{
public:
    double val[3][3];
    int row, col, rowSize, colSize;
    int refCnt;

    BaseMat(int r, int c, double** v) {
        row = r;
        rowSize = r;
        col = c;
        colSize = c;
        refCnt = 1;
        if(v != NULL)
		{
            val[0][0] = v[0][0];
            val[0][1] = v[0][1];
            val[0][2] = v[0][2];
            val[1][0] = v[1][0];
            val[1][1] = v[1][1];
            val[1][2] = v[1][2];
            val[2][0] = v[2][0];
            val[2][1] = v[2][1];
            val[2][2] = v[2][2];
		}
        else
		{
            val[0][0] = 0;
            val[0][1] = 0;
            val[0][2] = 0;
            val[1][0] = 0;
            val[1][1] = 0;
            val[1][2] = 0;
            val[2][0] = 0;
            val[2][1] = 0;
            val[2][2] = 0;					
		}
    }


};

class Matrix2
{
public:
	Matrix2(int row, int col) :
		_m(row, col, NULL)
	{
    }

	Matrix2 MultiplicationBy(const Matrix2& m) {
        Matrix2 temp(_m.row, m._m.col);

        for(int i = 0; i < _m.row; ++i) {
            for (int j = 0; j < m._m.col; ++j) {
                temp._m.val[i][j] = 0;
                for (int k = 0; k < _m.col; ++k) {
                    temp._m.val[i][j] += _m.val[i][k] * m._m.val[k][j];
                }
            }
        }
        return temp;
    }
    // Subscript operator
    double GetAt(int r, int c) {
        return _m.val[r][c];
    }
    double SetAt(int r, int c, double v) {
        _m.val[r][c] = v;
        return v;
    }
protected:
    BaseMat _m;
};

struct Position {
    double px;
    double py;
    double pz;
};

class ScatterData2 {
public:
	ScatterData2() :
		centerWgs84(3, 3), enu(3, 1)
	{
        enu.SetAt(0, 0, 0);
        enu.SetAt(1, 0, 0);
        enu.SetAt(2, 0, 0);
		isInitialized = false;
    }

	bool isInitialized;
	std::list<ScatterLLA> pData;
    Matrix2 centerWgs84;
    Matrix2 enu;

    void SetOrigin() 
	{
		if(pData.size() == 0)
			return;
		ScatterLLA p = pData.back();
		orgLon = p.GetLontitude();
		orgLat = p.GetLatitude();
		orgH = p.GetAltitude();
		SetRotationMatrix();
		isInitialized = true;
		UpdateAllData();
	}

    void SetOrigin(double lon, double lat, float alt) 
	{
        orgLon = lon;
        orgLat = lat;
        orgH = alt;
        SetRotationMatrix();
        isInitialized = true;
        UpdateAllData();
    }

    void ClearAllData() {
        pData.clear();
    }

    void AddCooridate(double lon, double lat, float alt) {
        if(pData.size() == 1000) {
			pData.erase(pData.begin());
        }
		pData.push_back(CreateLlaFromCooridate(lon, lat, alt));
    }

protected:
	double orgLon, orgLat;
    float orgH;
    Position centerPt;

    void SetRotationMatrix()
    {
        double lonR = Deg2Rad(orgLon);
        double latR = Deg2Rad(orgLat);

        centerWgs84.SetAt(0, 0, -sin(lonR));
        centerWgs84.SetAt(0, 1, cos(lonR));
        centerWgs84.SetAt(0, 2, 0);
        centerWgs84.SetAt(1, 0, -sin(latR)*cos(lonR));
        centerWgs84.SetAt(1, 1, -sin(latR)*sin(lonR));
        centerWgs84.SetAt(1, 2, cos(latR));
        centerWgs84.SetAt(2, 0, cos(latR)*cos(lonR));
        centerWgs84.SetAt(2, 1, cos(latR)*sin(lonR));
        centerWgs84.SetAt(2, 2, sin(latR));
        centerPt = COO_geodetic_to_cartesian(lonR, latR, orgH);
    }

    void UpdateAllData() {
		for (std::list<ScatterLLA>::iterator ite = pData.begin(); ite != pData.end(); ++ite) 
		{
            ScatterLLA lla = *ite;
            *ite = CreateLlaFromCooridate(lla.GetLontitude(), lla.GetLatitude(), lla.GetAltitude());
        }
    }

    Position COO_geodetic_to_cartesian(double lon, double lat, double alt)
    {
        double temp;
        double s_phi = sin(lat);
        double c_phi = cos(lat);

        // radius of curvature in prime vertical
        double N = WGS84_RA / sqrt(1 - WGS84_E2 * s_phi * s_phi);
        temp = (N + alt) * c_phi;
        Position xyz;
        xyz.px = temp * cos(lon);
        xyz.py = temp * sin(lon);
        xyz.pz = (N * (1 - WGS84_E2) + alt) * s_phi;
        return xyz;
    }

    void SetEnu(double lon, double lat, double h) {
        Position pt = COO_geodetic_to_cartesian(lon, lat, h);
        enu.SetAt(0, 0, pt.px - centerPt.px);
        enu.SetAt(1, 0, pt.py - centerPt.py);
        enu.SetAt(2, 0, pt.pz - centerPt.pz);

        enu = centerWgs84.MultiplicationBy(enu);
    }

    ScatterLLA CreateLlaFromCooridate(double lon, double lat, float alt) {
        SetEnu(Deg2Rad(lon), Deg2Rad(lat), (double) alt);
        ScatterLLA lla(lon, lat, alt);
        lla.SetCurrentX(enu.GetAt(0, 0));
        lla.SetCurrentY(enu.GetAt(1, 0));
        return lla;
    }
};


class CPic_Scatter : public CStatic
{
public:
	CPic_Scatter(void);
	~CPic_Scatter(void);
	
protected:
	void Refresh_ScatterChart(CDC *scatter_dc);
	void Create_scatterplot(CDC *dc);
	void Show_ScatterChart(CDC *dc);
	void DrawScatterInfo(CDC *dc);
	void DrawScatterAltitude(CDC *dc, double initH , double h);

	int plot_x1,plot_x2,plot_y1,plot_y2;
	int plot_cross_x,plot_cross_y;
    CPoint HScatterScale[5];
    CPoint VScatterScale[5];



	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
};
