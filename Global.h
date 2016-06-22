#pragma once

#include "Utility.h"
#include <vector>
#include <list>
#include "matrix.h"
#include "Registry.h"

using namespace math;
using namespace std;

#include "CxImage/ximage.h"
#if defined(_DEBUG)
 #pragma comment( lib, "CxImage/DebugLib/cximage.lib" )
 #pragma comment( lib, "CxImage/DebugLib/png.lib" )
 #pragma comment( lib, "CxImage/DebugLib/zlib.lib" )
#else
 #pragma comment( lib, "CxImage/ReleaseLib/cximage.lib" )
 #pragma comment( lib, "CxImage/ReleaseLib/png.lib" )
 #pragma comment( lib, "CxImage/ReleaseLib/zlib.lib" )
#endif

class CWaitReadLog;
class CSerial;
struct GPGSA;
typedef matrix<float> Matrix;

#define LogDefaultName		"Response.log"
#define DefaultTimeout		3000

#define MAX_WAIT_TIME		      INFINITE
#define TIME_OUT_MS               10000
#define TIME_OUT_QUICK_MS         1000
#define SCAN_TIME_OUT_MS          500
#define DOWNLOAD_TIME_OUT_LOOP    10
#define BUF_SIZE 4096
#define BOOTLOADER_SIZE		0x10000

#define WGS84_RA    (6378137.0)                   // semi-major earth axis(ellipsoid equatorial radius)
#define WGS84_INV_F (298.257223563)               // inverse flattening of WGS-84
#define WGS84_F     (1.0/WGS84_INV_F)             // inverse flattening of WGS-84
#define WGS84_RB    (WGS84_RA*(1.0-WGS84_F))      // semi-major earth axis(ellipsoid polar radius)
#define WGS84_E2    (2.0*WGS84_F-WGS84_F*WGS84_F) // eccentricity squared: (RA*RA-RB*RB)/RA*RA
#define WGS84_E2P   (WGS84_E2/(1.0-WGS84_E2))     // eccentricity squared: (RA*RA-RB*RB)/RB*RB

struct Setting
{
	Setting()
	{
		Load();
	}

	void Save()
	{
		CRegistry reg;
		reg.SetRootKey(HKEY_CURRENT_USER);

		if(reg.SetKey("Software\\GNSSViewer\\GPS", false))
		{
			reg.WriteInt("comport", comPort);
			reg.WriteInt("baudrate", baudrate);
			reg.WriteString("firmware", mainFwPath);
			reg.WriteInt("setting_earthBitmap", earthBitmap);
		}

		if(IS_DEBUG && reg.SetKey("Software\\GNSSViewer\\GPS", false))
		{
			reg.WriteInt("setting_delayBeforeBinsize", delayBeforeBinsize);
			reg.WriteInt("setting_boostBaudrateIndex", boostBaudIndex);
			reg.WriteInt("setting_autoQueryVersion", autoQueryVersion);
			reg.WriteInt("setting_boostEphemeris", boostEphemeris);
			reg.WriteInt("setting_checkNmeaError", checkNmeaError);
			reg.WriteInt("setting_responseLog", responseLog);
			reg.WriteString("setting_responseLogPath", responseLogPath);

			reg.WriteInt("setting_specifyCenter", specifyCenter);
			reg.WriteFloat("setting_scatterCenterLon", scatterCenterLon);
			reg.WriteFloat("setting_scatterCenterLat", scatterCenterLat);
			reg.WriteInt("setting_specifyCenterAlt", specifyCenterAlt);
			reg.WriteFloat("setting_scatterCenterAlt", scatterCenterAlt);
			reg.WriteInt("setting_defaultTimeout", defaultTimeout);
			reg.WriteInt("setting_scatterCount", scatterCount);

			reg.WriteInt("recentScatterCenterCount", recentScatterCenter.GetCount());
			for(int i = 0; i < recentScatterCenter.GetCount(); ++i)
			{
				CString key;
				key.Format("recentScatterCenter%d", i);
				reg.WriteString(key, recentScatterCenter[i]);
			}
		}	
	}

	void Load()
	{
		CRegistry reg;
		reg.SetRootKey(HKEY_CURRENT_USER);
		const double defaultCenterLon = 121.008756203;
		const double defaultCenterLat = 24.784893606;
		const double defaultCenterAlt = 100.0;

		if(IS_DEBUG && reg.SetKey("Software\\GNSSViewer\\GPS", true))
		{
			delayBeforeBinsize = reg.ReadInt("setting_delayBeforeBinsize", 0);
			boostBaudIndex = reg.ReadInt("setting_boostBaudrateIndex", BAUDRATE_DEFAULT);
			autoQueryVersion = reg.ReadInt("setting_autoQueryVersion", TRUE);
			boostEphemeris = reg.ReadInt("setting_boostEphemeris", FALSE);
			checkNmeaError = reg.ReadInt("setting_checkNmeaError", SHOW_ERROR_NMEA_NOTIFY);
			responseLog = reg.ReadInt("setting_responseLog", FALSE);
			responseLogPath = reg.ReadString("setting_responseLogPath", LogDefaultName);
			specifyCenter = reg.ReadInt("setting_specifyCenter", FALSE);
			scatterCenterLon = reg.ReadFloat("setting_scatterCenterLon", defaultCenterLon);
			scatterCenterLat = reg.ReadFloat("setting_scatterCenterLat", defaultCenterLat);
			specifyCenterAlt = reg.ReadInt("setting_specifyCenterAlt", FALSE);
			scatterCenterAlt = reg.ReadFloat("setting_scatterCenterAlt", defaultCenterAlt);
			defaultTimeout = reg.ReadInt("setting_defaultTimeout", DefaultTimeout);
			scatterCount = reg.ReadInt("setting_scatterCount", MAX_SCATTER_COUNT);

			int recentCount = reg.ReadInt("recentScatterCenterCount", 0);
			for(int i = 0; i < recentCount; ++i)
			{
				CString key, data;
				key.Format("recentScatterCenter%d", i);
				data = reg.ReadString(key, "");
				recentScatterCenter.Add(data);
			}
		}
		else
		{
			delayBeforeBinsize = 0;
			boostBaudIndex = BAUDRATE_DEFAULT;
			autoQueryVersion = TRUE;
			boostEphemeris = FALSE;
			checkNmeaError = SHOW_ERROR_NMEA_NOTIFY;
			responseLog = FALSE;
			responseLogPath = LogDefaultName;
			specifyCenter = FALSE;
			scatterCenterLon = defaultCenterLon;
			scatterCenterLat = defaultCenterLat;
			specifyCenterAlt = FALSE;
			scatterCenterAlt = defaultCenterAlt;
			defaultTimeout = DefaultTimeout;
			scatterCount = MAX_SCATTER_COUNT;
		}

		if(reg.SetKey("Software\\GNSSViewer\\GPS", true))
		{
			comPort = reg.ReadInt("comport", 0);
			baudrate = reg.ReadInt("baudrate", 1);
			mainFwPath = reg.ReadString("firmware", "");
			earthBitmap = reg.ReadInt("setting_earthBitmap", 0);
		}
		else
		{
			comPort = 0;
			baudrate = 1;
			mainFwPath = "";
			earthBitmap = 0;
		}
		downloadTesting = FALSE;
		if(scatterCount <= 0)
		{
			scatterCount = MAX_SCATTER_COUNT;
		}
	}

	void AddRecentScatterCenter(LPCSTR r)
	{
		for(int i = 0; i < recentScatterCenter.GetCount(); ++i)
		{
			if(recentScatterCenter[i] == r)
			{
				recentScatterCenter.RemoveAt(i);
			}
		}
		if(recentScatterCenter.GetCount() > 9)
			recentScatterCenter.RemoveAt(0);
		recentScatterCenter.Add(r);
	}

	int GetBaudrateIndex() { return baudrate; }
	int GetBaudrate() { return BaudrateTable[baudrate]; }
	void SetBaudrateIndex(int b) { baudrate = b; }
	void SetBaudrate(int b);
	int GetComPortIndex() { return comPort - 1; }
	int GetComPort() { return comPort; }
	void SetComPortIndex(int c) { comPort = c + 1; }
	void SetComPort(int c) { comPort = c; }

	//General use
	static int BaudrateTable[];
	static const int BaudrateTableSize;
	CString mainFwPath;
	int earthBitmap;

	//Internal Use only
	int delayBeforeBinsize;
	int boostBaudIndex;
	BOOL autoQueryVersion;
	BOOL boostEphemeris;
	BOOL checkNmeaError;
	BOOL downloadTesting;
	BOOL responseLog;
	CString responseLogPath;
	BOOL specifyCenter;
	double scatterCenterLon;
	double scatterCenterLat;
	BOOL specifyCenterAlt;
	double scatterCenterAlt;
	int defaultTimeout;
	int scatterCount;
	CStringArray recentScatterCenter;

protected:

	//General use
	int comPort;
	int baudrate;

};

typedef struct UTC_TIME_T {
	S16 year;
	S16 month;
	S16 day;
	S16 day_of_year;
	S16 hour;
	S16 minute;
	F32 sec;
} UtcTime;

struct POS_T {
  D64 px;
  D64 py;
  D64 pz;
};

struct LLA_T {
	D64 lat;
	D64 lon;
	F32 alt;
};

struct LL {
	double lat;
	double lon;
	double speed;
	double alt;
	UtcTime utc;
};

enum QualityMode {
	Uninitial = 0,
	Unlocated,
	EstimatedMode,
	DgpsMode,
	PpsMode,
	PositionFix2d,
	PositionFix3d,

	SurveyIn,
	StaticMode,
	DataNotValid,
	AutonomousMode,
	DgpsMode2,
	FixRTK,
	FloatRTK,
};

enum WlfResult {
	wlf_None,
	wlf_ok,
	wlf_end,
	wlf_error1,
	wlf_error2,
	wlf_error3,
	wlf_error4,
	wlf_error5,
	wlf_resend,
	wlf_reset,
	wlf_resendbin,
	wlf_timeout,
	//for Loader debug
	wlf_error41,
	wlf_error42,
	wlf_error43,
	wlf_Ready,
	wlf_Ready1,
	wlf_Ready2,
};

extern Setting g_setting;

#define MAX_SATELLITE				32
#define MyMaxPath		(MAX_PATH * 8)
#define BINMSG_ERROR                0

extern const double R2D;
extern const COLORREF g_panelBkColor;

extern U08 type;
extern U08 attribute;
extern U08 msgid;

extern U08  slgga;	
extern U08  slgsa;
extern U08  slgsv;
extern U08  slgll;
extern U08  slrmc;
extern U08  slvtg;
extern U08  slzda;
extern U08  slgns;

extern HANDLE g_connectEvent;
extern HANDLE g_closeEvent;
extern CWaitReadLog* WRL;
extern HANDLE	waitlog;
extern const S16 DefaultLeapSeconds;

extern double pos_lat, pos_lon;
extern int m_almanac_no;
extern CString m_almanac_filename;

class CMonitor_1PPS;
extern CMonitor_1PPS *dia_monitor_1pps;
//extern bool g_doesNotChangeBaudrate;
extern int FlashBytes[];

U32 ConvertCharToU32(const char *src);
UINT WaitLogRead(LPVOID pParam);
bool IsFixed(U16 gga_indicator);
bool CheckInUse(int id, GPGSA* gsa);
double Deg2Rad(double degree);
double Rad2Deg(double rad);
float FixedPointToSingle(U32 FixedPointValue, int NumberOfFractionalBits);
void COO_geodetic_to_cartesian( const LLA_T* lla_p, POS_T* xyz_p );
//void  convert_gps_time_to_utc( S16 wn, D64 tow, UTC_T* utc_p );

extern const char* DatumList[];
extern const int DatumListSize;

U08 Cal_Checksum(U08* pt);
UINT16 CalCheckSum2(U08* pt);
void UtcConvertGpsToUtcTime(S16 wn, D64 tow, UtcTime *utc_time_p);
void UtcConvertUtcToGpsTime(const UtcTime *utc_time_p, S16 *wn_p, D64 *tow_p);
QualityMode GetGnssQualityMode(U32 qualityIndicator, U08 gpMode = 0, U08 glMode = 0, U08 gaMode = 0, U08 bdMode = 0);
//QualityMode GetGnssQualityMode(const U32 qualityIndicator, const U08 gpMode = 0, const U08 glMode = 0, const  gaMode = 0, const U08 bdMode = 0);
D64 ConvertLeonDouble(const U08* ptr);
F32 ConvertLeonFloat(const U08* ptr);
U16 ConvertLeonU16(const U08* ptr);
S16 ConvertLeonS16(const U08* ptr);
U32 ConvertLeonU32(const U08* ptr);
S32 ConvertLeonS32(const U08* ptr);
WlfResult WaitingLoaderFeedback(CSerial* serial, int TimeoutLimit, CWnd* msgWnd);

//void UTC_convert_gps_to_utc_time_by_default_parameters( S16 wn, D64 tow, UtcTime *utc_time_p );

