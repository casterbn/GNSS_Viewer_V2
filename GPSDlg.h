// GPSDlg.h : header file
//
#pragma once

#include "resource.h"
#include "Global.h"
#include "DataLog.h"
#include "NMEA.h"
#include "ScanDlg.h"
#include "CfgMsg.h"
#include "Savenmea.h"
#include "Agps_config.h"
#include "FTPDlg.h"
#include "Registry.h"
#include "ClipboardListBox.h"
#include "Label.h"
#include "ColorStatic.h"
#include "MsgList.h"
#include "SerialAgents.h"

#define UWM_SETPROGRESS			  (WM_USER + 0x100)
#define UWM_SETPROMPT_MSG		  (WM_USER + 0x101)
#define UWM_SETTIMEOUT			  (WM_USER + 0x102)
#define UWM_KERNEL_REBOOT		  (WM_USER + 0x103)
#define UWM_FIRST_NMEA			  (WM_USER + 0x104)
#define UWM_SHOW_TIME			    (WM_USER + 0x105)
#define UWM_UPDATE_UI			    (WM_USER + 0x106)
#define UWM_SHOW_RMC_TIME		  (WM_USER + 0x107)
#define UWM_GPSDO_HI_DOWNLOAD (WM_USER + 0x108)
#define UWM_UPDATE_RTK_INFO		(WM_USER + 0x109)
#define UWM_UPDATE_PSTI030		(WM_USER + 0x10A)
#define UWM_UPDATE_PSTI031		(WM_USER + 0x10B)
#define UWM_UPDATE_PSTI032		(WM_USER + 0x10C)
#define UWM_DO_ZENLANE_CMD    (WM_USER + 0x10D)

#define GNSS_CHANEL_LIMIT	16

enum DownloadErrocCode
{
	RETURN_NO_ERROR = 0,
	RETURN_RETRY,
	RETURN_ERROR
};

struct GNSS_SATE_T
{
	S08 k_num;
	U08 slot_num;
	U08 snr;
};

struct GNSS_T
{
	U08 gnss_in_view;
	GNSS_SATE_T sate[GNSS_CHANEL_LIMIT];
};

typedef struct EllipsoidList
{
	U32 a;
	U32 I_F;
} EL;

typedef struct ellipsoidlist
{
	D64 a;
	D64 I_F;
} TEL;

typedef struct datumreferencelist
{
	S16 DeltaX;
	S16 DeltaY;
	S16 DeltaZ;
	D64 Semi_Major_Axis;
	D64 Inversd_Flattening;
	U08 EllipsoidIndex;
} TDRL;

typedef struct DatumReferenceList
{
	S16 DeltaX;
	S16 DeltaY;
	S16 DeltaZ;
	U32 Semi_Major_Axis;
	U32 Inversd_Flattening;
	U08 EllipsoidIndex;
} DRL;

typedef struct {
	U08 Timing_mode;
	U32 Survey_Length;
	U08 RT_Timing_mode;
	U32 RT_Survey_Length;
	D64 latitude;
	D64 longitude;
	F32 altitude;
	D64 RT_latitude;
	D64 RT_longitude;
	F32 RT_altitude;
	U08 attributes;
	U32 Standard_deviation;

} _1PPS_Timing_T;

struct LL2 {
	double lat;
	double lon;
	double speed;
	double alt;
	UtcTime utc;
};

struct PSTI030_Data
{
	F32 rtkAge;
	F32 rtkRatio;
};

struct PSTI031_Data
{
	F32 baseline;
};

struct PSTI032_Data
{
	F32 eastProjection;
	F32 northProjection;
	F32 upProjection;
	F32 baselineLength;
	F32 baselineCourse;
};

// Copy from HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\DeviceClasses
static const GUID GUID_DEVINTERFACE_LIST[] = 
{
	// GUID_DEVINTERFACE_USB_DEVICE
	{ 0xA5DCBF10, 0x6530, 0x11D2, { 0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED } },

	// GUID_DEVINTERFACE_DISK
	{ 0x53f56307, 0xb6bf, 0x11d0, { 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b } },

	// GUID_DEVINTERFACE_HID, 
	{ 0x4D1E55B2, 0xF16F, 0x11CF, { 0x88, 0xCB, 0x00, 0x11, 0x11, 0x00, 0x00, 0x30 } },

	// GUID_NDIS_LAN_CLASS
	{ 0xad498944, 0x762f, 0x11d0, { 0x8d, 0xcb, 0x00, 0xc0, 0x4f, 0xc3, 0x35, 0x8c } }

	//// GUID_DEVINTERFACE_COMPORT
	//{ 0x86e0d1e0, 0x8089, 0x11d0, { 0x9c, 0xe4, 0x08, 0x00, 0x3e, 0x30, 0x1f, 0x73 } },

	//// GUID_DEVINTERFACE_SERENUM_BUS_ENUMERATOR
	//{ 0x4D36E978, 0xE325, 0x11CE, { 0xBF, 0xC1, 0x08, 0x00, 0x2B, 0xE1, 0x03, 0x18 } },

	//// GUID_DEVINTERFACE_PARALLEL
	//{ 0x97F76EF0, 0xF883, 0x11D0, { 0xAF, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x84, 0x5C } },

	//// GUID_DEVINTERFACE_PARCLASS
	//{ 0x811FC6A5, 0xF728, 0x11D0, { 0xA5, 0x37, 0x00, 0x00, 0xF8, 0x75, 0x3E, 0xD1 } }
};

enum { 
	SHOW_STATUS_TIMER = 1,
	TEST_KERNEL_TIMER,
	ECOM_CALIB_TIMER,
	DELAY_QUERY_TIMER,
	DELAY_PLUGIN_TIMER,
  ZENLANE_INIT_TIMER,
  ZENLANE_QUERY_TIMER,
};

enum { 
  DO_NOTHING = 0,
  DO_QUERY_VERSION,
  DO_ZENLANE_INIT,
  DO_ZENLANE_QUERY,
};

class CSoftImDwDlg;
class CSerial;
class CSnrBarChartGps;
class CSnrBarChartGlonass;
class CSnrBarChartGpsGlonass;
class CSnrBarChartBeidou;
class CSnrBarChartGalileo;
class CSnrBarChart;
class CPic_Scatter;
class CPic_Earth;
class CCigRgsDlg;
class CGetRgsDlg;
class BinaryCommand;
class BinaryData;
class CPanelBackground;
class CCommonConfigDlg;

class CGPSDlg : public CDialog
{
public:
	static CGPSDlg* gpsDlg;
	// Construction
	CGPSDlg(CWnd* pParent = NULL);	// standard constructor
	~CGPSDlg();

public:
	enum BoostMode
	{
		ChangeToSram = 0,
		ChangeToFlashAndSram = 1,
		ChangeToTemp = 2,
	};

	enum MsgMode
	{
		NoOutputMode = 0,
		BinaryMessageMode,
		NmeaMessageMode,
	};

	enum CmdErrorCode {
		Ack = 0,
		Ack0,
		NACK,
		FormatError,
		Timeout,
	};

	enum CmdExeMode {
		Display = 0,
		Return,
		NoWait,
	};

	enum DownloadMode {
		EnternalLoader,
		EnternalLoaderInBinCmd,
		InternalLoaderV6Gps,
		InternalLoaderV6Gnss,
		InternalLoaderV6Gg12a,
		InternalLoaderV8,
		InternalLoaderV6GpsAddTag,
		InternalLoaderV6GpsDelTag,
		InternalLoaderV6GnssAddTag,
		InternalLoaderV6GnssDelTag,
		InternalLoaderV8AddTag,
		CustomerDownload,
		InternalLoaderSpecial,
		GpsdoMasterSlave,

		HostBasedDownload,
		HostBasedCmdOnly,
		HostBasedBinOnly,
		ParallelDownloadType0,
		ParallelDownloadType1,
		RomExternalDownload,
		CustomerUpgrade
	} m_DownloadMode;

	enum InfoTabStat {
		BasicInfo = 0,
		RtkInfo,
	};

	static UINT UWM_PLAYNMEA_EVENT;
	static UINT UWM_SAVENMEA_EVENT;
	static UINT UWM_UPDATE_EVENT;
#if (SPECIAL_TEST)
	U08* specCmd;
	U32	 specSize;
#endif

#if MORE_ENU_SCALE
	enum { DefauleEnuScale = 5 };
#else
	enum { DefauleEnuScale = 0 };
#endif

protected:
	enum { IDD = IDD_GPS_DIALOG };
	InfoTabStat m_InfoTabStat;
	HICON m_hIcon;
	CString m_lastGpEphFile;
	CString m_lastGlEphFile;
	CString m_lastBdEphFile;

	CSerialAgents m_serialAgents;
	CColorStatic m_ttff;
	CColorStatic m_date;
	CColorStatic m_time;
	CColorStatic m_bootStatus;
	CColorStatic m_swKernel;
	CColorStatic m_swRev;
	CColorStatic m_longitude;
	CColorStatic m_latitude;
	CColorStatic m_altitude;
	CColorStatic m_direction;
	CColorStatic m_speed;
	CColorStatic m_hdop;	
	CColorStatic m_lbl_firmware_path;
	CColorStatic m_rtkAge;	
	CColorStatic m_rtkRatio;	

	CBitmapButton m_CoorSwitch1Btn;
	CBitmapButton m_CoorSwitch2Btn;

#if(_TAB_LAYOUT_)
	CColorStatic m_date2;	
	CColorStatic m_time2;	
	CColorStatic m_eastProjection;	
	CColorStatic m_baselineLength;	
	CColorStatic m_northProjection;	
	CColorStatic m_baselineCourse;	
	CColorStatic m_upProjection;
#endif

	PSTI030_Data m_psti030;
	PSTI031_Data m_psti031;
	PSTI032_Data m_psti032;

	CComboBox m_ComPortCombo;
	CComboBox m_BaudRateCombo;	
	CComboBox m_coordinate;
	CComboBox m_scale;
	CComboBox m_mapscale;

	CPanelBackground* m_infoPanel;
	CPanelBackground* m_earthPanel;
	CPanelBackground* m_scatterPanel;
	CPanelBackground* m_downloadPanel;

	CEdit m_twodrms;
	CEdit m_cep;
	CColorStatic m_twodrms2;
	CColorStatic m_cep2;
	CEdit m_clock_offset;
	CEdit m_noise;
	CColorStatic m_centerAlt;

	CBitmapButton m_ConnectBtn;
	CBitmapButton m_PlayBtn;
	CBitmapButton m_StopBtn;
	CBitmapButton m_RecordBtn;

public:
	CBitmapButton m_CloseBtn;
	CString m_nmeaPlayFilePath;
	HANDLE m_nmeaPlayThread;
	int m_nmeaPlayInterval;
	bool m_nmeaPlayPause;
	CCriticalSection _nmeaPlayInterval;
	CCriticalSection csSatelliteStruct;
#if defined(SAINTMAX_UI)
	CButton m_nmea0183msg;
#endif
	Satellite satecopy_gps[MAX_SATELLITE];
	Satellite sate_gps[MAX_SATELLITE];	
	Satellite satecopy_gnss[MAX_SATELLITE];
	Satellite sate_gnss[MAX_SATELLITE];	
	Satellite satecopy_bd[MAX_SATELLITE];
	Satellite sate_bd[MAX_SATELLITE];	
	Satellite satecopy_ga[MAX_SATELLITE];
	Satellite sate_ga[MAX_SATELLITE];	

protected:
	CBitmapButton m_SetOriginBtn;	
	CBitmapButton m_ClearBtn;		
	CBitmapButton m_DownloadBtn;
	CBitmapButton m_EarthSettingBtn;
	CBitmapButton m_ScatterSettingBtn;

	CStatic m_connectT;
	CListCtrl m_kNumList;
	CToolTipCtrl m_tip;
	CClipboardListBox m_responseList;	

	char m_currentDir[MyMaxPath];
	bool m_gpsdoInProgress;
	CFile m_convertFile;
	CString m_nmeaFilePath;
	GNSS_T m_gnss;
	GNSS_T m_gnssTemp;
	bool m_isFlogOpen;
	int maplondeg, maplonmin, maplonsec, maplatdeg, maplatmin, maplatsec;
	CCriticalSection _save_nmea_cs;

	void UpdateCooridate();
	void DisplayComportError(int com, DWORD errorCode);
	bool NmeaInput();
	bool ComPortInput();
	void ClearInformation(bool onlyQueryInfo = false);
	bool DoDownload(int dlBaudIdx);
	bool DoDownload(int dlBaudIdx, UINT rid);
public:
	static CFont m_textFont;
	static CFont m_infoFontS;
	static CFont m_infoFontM;
	static CFont m_infoFontL;
	static CFont comboFont;;	
	static CFont messageFont;

	CMsgList m_nmeaList;
	CFile m_ephmsFile;

	CFile m_nmeaFile;
	U32 m_nmeaFileSize;

	CSaveNmea* m_saveNmeaDlg;
	CPlayNmea* m_playNmea;
	CScanDlg* m_pScanDlg;
	CSerial* m_serial;
	CSoftImDwDlg* m_psoftImgDlDlg;
	//	FILE *fbin;
	GPGGA m_gpggaMsgBk;
	GPGLL m_gpgllMsg, m_gpgllMsgCopy, m_gpgllMsgCopy1;
	GPGSA m_glgsaMsg, m_glgsaMsgCopy, m_glgsaMsgCopy1;
	GPGSV m_glgsvMsg, m_glgsvMsgCopy, m_glgsvMsgCopy1;
	GPGGA m_gpggaMsg, m_gpggaMsgCopy, m_gpggaMsgCopy1;
	GPGSA m_gpgsaMsg, m_gpgsaMsgCopy, m_gpgsaMsgCopy1;

	GPGSV m_gpgsvMsg, m_gpgsvMsgCopy, m_gpgsvMsgCopy1;
	GPRMC m_gprmcMsg, m_gprmcMsgCopy, m_gprmcMsgCopy1;
	GPVTG m_gpvtgMsg, m_gpvtgMsgCopy, m_gpvtgMsgCopy1;

#if(_MODULE_SUP_800_)
	PSTI004001 m_psti004001, m_psti004001Copy, m_psti004001Copy1;
#endif

	GPZDA m_gpzdaMsg, m_gpzdaMsgCopy, m_gpzdaMsgCopy1;
	//for Beidou
	GPGSA m_bdgsaMsg, m_bdgsaMsgCopy, m_bdgsaMsgCopy1;
	GPGSV m_bdgsvMsg, m_bdgsvMsgCopy, m_bdgsvMsgCopy1;
	//for Galileo
	GPGSA m_gagsaMsg, m_gagsaMsgCopy, m_gagsaMsgCopy1;
	GPGSV m_gagsvMsg, m_gagsvMsgCopy, m_gagsvMsgCopy1;


	LogFlashInfo1 m_logFlashInfo;
	U32 m_ttffCount;	
	bool m_initTtff;
	bool m_setTtff;
	U32  m_regAddress;	
	bool m_isPressCloseButton;
	bool m_isConnectOn;		
	bool m_isNmeaUpdated;

	enum { NmeaBufferSize = 1024 };
	char m_nmeaBuffer[NmeaBufferSize];		//NMEA_MSG[1024]
	static U08 m_inputMsg[200];

	void SetTTFF(int t)
	{
		CString str;
		str.Format("%d", t);
		GetDlgItem(IDC_TTFF)->SetWindowText(str);
	}

	CmdErrorCode GetCommandReturnType(U08* buff, int tail, bool showMsg = true);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	bool IsEphmsEmpty(BYTE* buffer);
	bool CeheckOrigin(CString,int);	
	bool CfgPortSendToTarget(U08*,U16,char*);
	bool CheckConnect();
	bool CheckGPS(U08*,U16,char*);
	bool CheckTimeOut(DWORD duration, DWORD timeOut = 10000,  bool silent = false);
	bool CloseOpenUart();
	bool ListSoftVersion(unsigned char* ,int);
	bool NmeaProc(const char*, int, NmeaType&);
	void NmeaOutput(LPCSTR pt, int len);

	bool SendMsg();
	bool SendToTarget(U08* ,U16 ,const char*, bool quick = false);
	bool SendToTargetNoAck(U08*,U16);
	bool SendToTargetNoWait(U08*,U16,LPCSTR);
	bool TIMEOUT_METHOD(time_t,time_t);
	U08 BinaryProc(unsigned char*,int);
	void CopyNmeaToUse();
	void ClearQue();
	void Copy_NMEA_Memery();
	void CreateGPSThread();	
	void DataLogDecompress(bool);
	void DeleteNmeaMemery();
	void GetLogStatus(U08*);
	void GetRegister(U08*);	
	void LogConfigure();
	void MSG_PROC();
	void QueryMsg(unsigned char*);
	void Restart(U08*);
	void ScanGPS();
	void ScanGPS1();
	void ScanGPS2();
	void ScatterPlot(CDC *dc);
	void SetEphms(U08 continues);

	void SetPort(U08,int mode);
#if(_MODULE_SUP_800_)
	void ShowPsti004001();
#endif
	void ShowBootStatus();
	void ShowDirection(bool reset = false);	
	void ShowAltitude(bool reset = false);
	void ShowPDOP(bool reset = false);
	void ShowSpeed(bool reset = false);

	void ShowDate();
	void ShowKNumber();
	void ShowVersion();

	void ShowEarth(CDC *dc);
	void ShowLongitudeLatitude(void);
	void DisplayTime(int h, int m, int s);
	void DisplayTime(int h, int m, D64 s);
	void DisplayDate(int y, int m, int d);

	void DisplayLongitude(LPCWSTR txt);
	void DisplayLatitude(LPCWSTR txt);
	void DisplayLongitude(D64 lon, U08 c);
	void DisplayLatitude(D64 lat, U08 c);
	void DisplayLongitude(int h, int m, double s, char c);
	void DisplayLatitude(int h, int m, double s, char c);

	void DisplaySpeed(D64 speed);
	void DisplayDirection(D64 direction);
	void DisplayStatus(GnssData::QualityMode m);
	void DisplayAltitude(D64 alt);
	void DisplayHdop(D64 hdop);

	void ShowRMCTime();
	void ShowStatus();
	void ShowTime(void);
	void Terminate(void);
	void TerminateGPSThread();
	void Initialization();
	void SetFacMsg(unsigned char*);	
	void continue_write_nmea();

private:
	HANDLE handle_version;
	HANDLE wait_version_complete;
	U08 Soft_Version;
	void Load_Menu();

	CDC bk_dc;
	CDC bar_dc;
	CDC earth_dc;
	CDC chart_dc;

	CButton m_rom_mode;
	int m_noisePower;

	CStatic m_lbl_download;
	CButton m_btn_browse;

public:
	int SetMessage(U08* msg, int len);
	int SetMessage2(U08* dst, U08* src, int srcLen);
	int GetCoordinateSel() { return m_coordinate.GetCurSel(); }
	int GetScaleSel() { return m_scale.GetCurSel(); }
	int GetMapScaleSel() { return m_mapscale.GetCurSel(); }
	bool IsFixed() { return ::IsFixed(m_gpggaMsg.GPSQualityIndicator); }
	void SetNmeaUpdated(bool b);
	bool SetFirstDataIn(bool b);
	void SendRestartCommand(int mode);		
	void target_only_restart(int mode);
	bool TIMEOUT_METHOD_QUICK(time_t start,time_t end);
	void WaitEvent();
	void add_msgtolist(LPCTSTR msg);
	bool SendToTargetBatch(U08* message,U16 length,char* Msg);

	void CLEAR_NMEA_TO_USE();
	int datalog_read_offset_ctl( int start_id,int total_sector,int offset, U08 *buff,long size ,long *receive_count);
	int query_log_boundary(U16 *end,U16 *total);
	void verify_log_format(U08 *datalog,long *size);
	int datalog_read_all( int start_id,int offset, U08 *datalog,long size,long *receive_count );
	bool verify_read_buff(U08 *buff,U08 *datalog,U08 *ptr_last,int size,long *receive_count);
	bool download_eph();
	D64 calculate_tk_double( S16 ref_wn, S32 ref_tow, S16 wn, D64 tow );
	void getBuffWnToc(U08* ephptr,U16 *wn,S32 *toc);
	void get_wn_tow(S16* wn,D64* tow);
	U08 CheckEphAndDownload();
	void ShowColdStartEarth();

	CButton m_bnt_warmstart;
	CButton m_btn_coldstart;

	CButton m_agps_enable;
	CButton m_agps_disable;

	double warmstart_latitude;
	double warmstart_longitude;
	double warmstart_altitude;
	void ConfigBaudrate(int baud, int attribute);
	void WaitReady();
	void Show_Noise();
	void GetAlmanac();
	void close_minitor_1pps_window();
	//=============================================
	void GetGpsAlmanac(CString m_almanac_filename,U08 sv,U08 continues);
	void SetGpsAlmanac(U08 continues);

	void GetAlmanac_tmp();
	void activate_minihomer();
	void set_minihomerkey(U08* key,int len);
	void set_minihomerid(U08* id,int len);
	void Close_Open_Port(WPARAM wParam,CString port_name);
	U08 MinihomerQuerytag();
	void MinihomerSettagecco();
	void query_dr_info();
	void Create_earth_pic(CDC *dc);
	void clear_login_password();
	U08 Base_Rom();
	void ClearGlonass();
	char* BootloaderRom_Combination(CString prom_path,int *buff_size);
#ifdef GG12A
	bool check_gg12a_format(const char *file_path);
#endif
	void SetGlonassAlmanac(U08 continues);
	void GetGlonassAlmanac(CString m_almanac_filename,U08 sv,U08 continues);
	void SetBeidouAlmanac(U08 continues);
	void GetBeidouAlmanac(CString m_almanac_filename,U08 sv,U08 continues);

	void SetBeidouEphms(U08 continues);	
	void SetGlonassEphms(U08 continues);
	bool IsGlonassEphmsEmpty(BYTE* buffer);

	void GetTimeCorrection(CString m_filename);
	void SetTimeCorrection(CString m_filename);
	U08 parse_psti_others(const char *buff, int psti_id);

	//For Common Download Clasases
public:
	int m_nDownloadBaudIdx;
	int m_nDownloadBufferIdx;
	UINT m_nDownloadResource;
	CString m_strDownloadImage;
	CString m_strDownloadImage2;
	int m_nSlaveSourceBaud;
	int m_nSlaveTargetBaud;

	bool CheckTagType();
	bool Download();
	bool Download2();
	bool Download3();
	void SetBaudrate(int b);
	BOOL GetShowBinaryCmdData() { return m_bShowBinaryCmdData; }
	void BoostBaudrate(BOOL bRestore, BoostMode mode = ChangeToTemp, bool isForce = false);
	//BOOL OpenDataLogFile(UINT nOpenFlags);
	
	void SetInputMode(MsgMode i) { m_inputMode = i; }
	void SetMode() { m_inputMode = GetMsgType(); }
	MsgMode GetMsgType() { return m_msgType; };
	void SetMsgType(MsgMode m) 
	{ 
		if(m_msgType != m)
		{
			DeleteNmeaMemery();	
			ClearInformation();
			m_msgType = m; 
		}
	};
	U08 GetRestartMode() { return m_restartMode; }
	bool ExecuteConfigureCommand(U08 *cmd, int size, LPCSTR msg, bool restoreConnect = true);
	void LogReadBatchControl();
	void GetEphms(U08 SV, U08 continues = FALSE);	
	void GetGlonassEphms(U08 SV, U08 continues = FALSE);
	void GetBeidouEphms(U08 SV, U08 continues = FALSE);

	bool SaveEphemeris(U08* buff,U08 id);
	bool SaveEphemeris2(U08* buff, WORD id);
	void Refresh_EarthChart(CDC *earth_dc);
	int GetCustomerID()
	{ return m_customerID; }
	NMEA nmea;

private:
	BOOL m_bShowBinaryCmdData;
	int downloadTotalSize;
	int downloadProgress;
	MsgMode m_msgType;
	U08 m_restartMode;
	MsgMode m_inputMode;
	CString datalogFilename;
	CFile dataLogFile;


	enum DataLogType
	{
		FIXNONE = 0,
		FIXFULL = 1,
		FIXINC = 2,
		FIXPOI = 3,
		FIXMULTI = 4,
		FIXPOIMULTI = 0x0C,

		FIXFULL2 = 11,
		FIXINC2 = 12,
		FIXPOI2 = 13,
	};

	UINT GetBinFromResource(int baud);
	U08 PlRomNoAlloc2(const CString& prom_path);
	U08 PlRomNoAllocV8(const CString& prom_path);
	U08 PlRomCustomerUpgrade(UINT rid);
	bool FirmwareUpdate(const CString& strFwPath);
	int SendRomBuffer3(const U08* sData, int sDataSize, BinaryData &binData, int fbinSize, 
		bool needSleep, CWnd* notifyWnd);
	int SendRomBufferCustomerUpgrade(const U08* sData, int sDataSize, BinaryData &f, int fbinSize, 
		bool needSleep, CWnd* notifyWnd);
	bool DownloadLoader();
	UINT GetSrecFromResource(int baud);
	bool QueryPassword();
	void GetLoaderDownloadCmd(char* msg, int size);
	//Data Log functions
	bool DatalogReadAll(int start_id,int offset, U08 *datalog,long size,long *receive_count );
	bool VerifyDataLogBuffer(U08 *buff, U08 *datalog, U08 *ptr_last, int size, long *receive_count);
	bool DataLogReadOffsetCtrl(int start_id, int total_sector, int offset, U08 *buff, long size , long *receive_count);
	bool QueryDataLogBoundary(U16 *end, U16 *total);
	void VerifyDataLogFormat(U08 *datalog,long *size);
	DataLogType GetDataLogType(U16 word);
	//For Common Binary Clasases
public:
	CmdErrorCode ExcuteBinaryCommand(int cmdIdx, BinaryCommand* cmd, BinaryData* ackCmd, DWORD timeOut = g_setting.defaultTimeout, bool silent = false);
	CmdErrorCode ExcuteBinaryCommandNoWait(int cmdIdx, BinaryCommand* cmd);
	CGPSDlg::CmdErrorCode GetBinaryResponse(BinaryData* ackCmd, U08 cAck, U08 cAckSub, DWORD timeOut, bool silent, bool noWaitAck = false, int cmdSize = -1, int cmdLen = 0);
	CmdErrorCode QueryRtkMode2(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryPsti030(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryPsti032(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryPsti004(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryGeofenceEx(CmdExeMode nMode, void* outputData);

  U08 m_nGeofecingNo;

	//Query Functions
	int m_nDefaultTimeout;
	BOOL m_bClearPsti032;
protected:
	typedef CmdErrorCode (CGPSDlg::*QueryFunction)(CmdExeMode, void*);
	void GenericQuery(QueryFunction pfn);

	CmdErrorCode QueryPositionRate(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryDatum(CmdExeMode nMode, void* outputData);
	CmdErrorCode QuerySha1String(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryConstellationCapability(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryVersionExtension(CmdExeMode nMode, void* outputData);
	CmdErrorCode SendZenlandInitCmd(CmdExeMode nMode, void* outputData);
	CmdErrorCode SendZenlandQueryCmd(CmdExeMode nMode, void* outputData);

	CmdErrorCode QuerySoftwareVersionSystemCode(CmdExeMode nMode, void* outputData);
	CmdErrorCode QuerySoftwareCrcSystemCode(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryPositionPinning(CmdExeMode nMode, void* outputData);
	CmdErrorCode Query1ppsMode(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryPowerMode(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryV8PowerSavingParameters(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryProprietaryMessage(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryTiming(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryDopMask(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryElevationAndCnrMask(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryAntennaDetection(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryNoisePower(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryDrInfo(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryDrHwParameter(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryGnssSelectionForNavigationSystem(CmdExeMode nMode, void* outputData);
	CmdErrorCode QuerySbas(CmdExeMode nMode, void* outputData);
	CmdErrorCode QuerySagps(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryQzss(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryNoisePowerControl(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryInterferenceDetectControl(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryNmeaBinaryOutputDestination(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryParameterSearchEngineNumber(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryAgpsStatus(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryDatalogLogStatus(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryRegister(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryPositionFixNavigationMask(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryChannelDoppler(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryNmeaIntervalV8(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryNmeaInterval2V8(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryEricssonInterval(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryClockOffset(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryRefTimeSyncToGpsTime(CmdExeMode nMode, void* outputData);
	CmdErrorCode QuerySearchEngineSleepCriteria(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryDatumIndex(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryVeryLowSpeed(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryDofunUniqueId(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryUartPass(CmdExeMode nMode, void* outputData);
	CmdErrorCode GpsdoResetSlave(CmdExeMode nMode, void* outputData);
	CmdErrorCode GpsdoEnterRom(CmdExeMode nMode, void* outputData);
	CmdErrorCode GpsdoLeaveRom(CmdExeMode nMode, void* outputData);
	CmdErrorCode GpsdoEnterDownload(CmdExeMode nMode, void* outputData);
	CmdErrorCode GpsdoLeaveDownload(CmdExeMode nMode, void* outputData);
	CmdErrorCode GpsdoEnterDownloadHigh(CmdExeMode nMode, void* outputData);
	CmdErrorCode GpsdoEnterUart(CmdExeMode nMode, void* outputData);
	CmdErrorCode GpsdoLeaveUart(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryNavigationModeV8(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryGnssBootStatus(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryDrMultiHz(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryGnssKnumberSlotCnr2(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryGnssNmeaTalkId(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryGnssNavSol(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryCustomerID(CmdExeMode nMode, void* outputData);
	CmdErrorCode Query1ppsFreqencyOutput(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryBinaryMeasurementDataOut(CmdExeMode nMode, void* outputData);
	CmdErrorCode QuerySerialNumber(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryDgps(CmdExeMode nMode, void* outputData);
	CmdErrorCode QuerySmoothMode(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryTimeStamping(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryGpsTime(CmdExeMode nMode, void* outputData);
	CmdErrorCode QuerySignalDisturbanceStatus(CmdExeMode nMode, void* outputData);
	CmdErrorCode QuerySignalDisturbanceData(CmdExeMode nMode, void* outputData);
	CmdErrorCode ResetOdometer(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryCableDelay(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryGeofenceResult(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryGeofenceResultEx(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryRtkMode(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryRtkParameters(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryPstmDeviceAddress(CmdExeMode nMode, void* outputData);
	CmdErrorCode QueryPstnLatLonDigits(CmdExeMode nMode, void* outputData);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedConnect();
	afx_msg void OnBnClickedRecord();
	afx_msg void OnBnClickedPlay();
	afx_msg void OnBnClickedStop();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedClose();
	afx_msg void OnCbnCloseupCoordinate();
	afx_msg void OnCbnCloseupEnuscale();
	afx_msg void OnCbnCloseupMapscale();
	afx_msg void OnBnClickedSetOrigin();
	afx_msg void OnFileSavescatterdata();
	afx_msg void OnFileSavepath();
	afx_msg void OnFileSaveplacemark();
	afx_msg void OnBnClickedGpgga();
	afx_msg void OnBnClickedGpgll();
	afx_msg void OnBnClickedGpgsa();
	afx_msg void OnBnClickedGpvtg();
	afx_msg void OnBnClickedGpgsv();
	afx_msg void OnBnClickedGprmc();
	afx_msg void OnBnClickedGpzda();
	afx_msg void OnFileSetup();
	afx_msg void OnFileExit();
	afx_msg void OnClose();
	afx_msg void OnHelpAbout();
	afx_msg void OnDRomwrite();
	afx_msg void OnDownloadRomwrite();
	afx_msg void OnBinarySystemRestart();
	afx_msg void OnBinaryDumpData();
	afx_msg void OnConfigureSerialPort();
	afx_msg void OnSetFactoryDefaultNoReboot();
	afx_msg void OnSetFactoryDefaultReboot();
	//afx_msg void OnBinaryConfigurenmeaoutput();
	afx_msg void OnConfigureNmeaIntervalV8();
	afx_msg void OnConfigureEricssonSentecneInterval();
	afx_msg void OnConfigureSerialNumber();
	afx_msg void OnBinaryConfiguredatum();
	//afx_msg void OnBinaryConfiguredopmask();
	afx_msg void OnConverterDecompress();	
	afx_msg void OnCovDecopre();
	afx_msg void OnConverterCompress();
	//afx_msg void OnLoggerConvert();	
	afx_msg void OnDatalogClearControl();
	afx_msg void OnDatalogLogconfigurecontrol();	
	afx_msg void OnSoftwareimagedownloadLoaderimage();
	afx_msg void OnSoftwareimagedownloadImageonly();
	afx_msg void OnBinaryGetrgister();
	afx_msg void OnBinaryConfigureregister();
	afx_msg void OnBnClickedClear();
	afx_msg void OnBnClickedHotstart();
	afx_msg void OnBnClickedWarmstart();
	afx_msg void OnBnClickedColdstart();
	afx_msg void OnBnClickedNoOutput();
	afx_msg void OnBnClickedNmeaOutput();
	afx_msg void OnBnClickedBinaryOutput();
	afx_msg void OnBnClickedDownload();
	afx_msg void OnFileSaveNmea();
	afx_msg void OnFileSaveBinary();
	afx_msg void OnVerifyFirmware();
	afx_msg void OnFilePlayNmea();
	afx_msg void OnConverterKml();
	afx_msg void OnRawMeasurementOutputConvert();
	afx_msg void OnBnClickedScanAll();
	afx_msg void OnBnClickedScanPort();
	afx_msg void OnBnClickedScanBaudrate();
	afx_msg void OnBinaryConfiguremessagetype();
	afx_msg void OnEphemerisGetephemeris();
	afx_msg void OnEphemerisSetephemeris();
	afx_msg void OnAgpsConfig();
	afx_msg void OnFileCleannema();
	afx_msg void OnBnClickedBrowse();
	afx_msg void OnWaasQuerywaasstatus();
	afx_msg void OnWaasWaasenable();
	afx_msg void OnWaasWaasdisable();
	afx_msg void OnBinaryConfiguremessageType();
	afx_msg void OnBinaryConfigurebinarymsginterval();
	afx_msg void OnBinaryConfigureBinaryInterval();
	afx_msg void OnBinaryPositionfinder();
	afx_msg void OnConfigurePositionUpdateRate();
	afx_msg void OnBinaryConfigDrMultiHz();
	afx_msg void OnDatalogLogReadBatch();
	afx_msg void OnBinaryConfigurepositionpinning();
	afx_msg void OnBinaryConfigurepinningparameters();
	afx_msg void OnMultimodeConfiguremode();
	afx_msg void OnMultimodeQuerymode();
	afx_msg void OnBinaryConfiguresubsecregister();
	afx_msg void OnConfigGpsMeasurementMode();
	afx_msg void OnBinaryQuery1pps();
	afx_msg void OnBinaryConfigurepowermode();
	afx_msg void OnBinaryConfiguremultipath();
	//afx_msg void OnWaasWaas();
	afx_msg void OnGetGpsAlmanac();
	afx_msg void OnBinaryQuerybinarymsginterval();
	afx_msg void OnBinaryResetodometer();
	afx_msg void OnConfigTiming();
	afx_msg void OnConfigTimingCableDelay();
	afx_msg void OnConfigureDopMask();
	afx_msg void OnConfigElevationAndCnrMask();
	afx_msg void OnMonitoring1Pps();
	afx_msg void OnConfigureProprietaryNmea();
	afx_msg void OnSetGpsAlmanac();
	afx_msg void OnMinihomerActivate();
	afx_msg LRESULT OnMyDeviceChange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnKernelReboot(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnPlayNmeaEvent(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSaveNmeaEvent(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateEvent(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnFirstNmea(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnShowTime(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnShowRMCTime(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateUI(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGpsdoHiDownload(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateRtkInfo(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdatePsti030(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdatePsti031(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdatePsti032(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDoZenlaneCmd(WPARAM wParam, LPARAM lParam);

	afx_msg void OnMinihomerSettagecco();
	afx_msg void OnMinihomerQuerytag();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnBnClickedRomMode();
	afx_msg void OnBnClickedKnumEnable();
	afx_msg void OnBnClickedKnumDisable();
	afx_msg void OnConfigNmeaOutputComPort();
	afx_msg void OnBinaryConfigurenmeatalkerid();
	afx_msg void OnGetGlonassAlmanac();
	afx_msg void OnSetGlonassAlmanac();
	afx_msg void OnGetBeidouAlmanac();
	afx_msg void OnSetBeidouAlmanac();
	//afx_msg void OnEphemerisSetgpsglonass();
	//afx_msg void OnEphemerisSetgpsglonassAlmanac();
	afx_msg void OnEphemerisGettimecorrections();
	afx_msg void OnEphemerisSettimecorrections();
	afx_msg void OnConfigProprietaryMessage();
	afx_msg void OnConfigPowerSavingParameters();
	//afx_msg void OnConfigPowerSavingParametersRom();
	afx_msg void OnBinaryConfigureantennadetection();
	afx_msg void OnConfigure1PpsOutputMode();	//new
	afx_msg void OnQuery1PpsOutputMode();
	afx_msg void OnConfigGnssDozeMode();
	afx_msg void OnBnClickedECompassCalibration();
	afx_msg void OnConfigure1PpsPulseWidth();
	afx_msg void OnQuery1PpsPulseWidth();
	afx_msg void OnConfigQueryGnssNavSol();
	afx_msg void OnConfigBinaryMeasurementDataOut();
	afx_msg void OnConfig1ppsFrequencyOutput();
	afx_msg void OnLineAssistance();
	//afx_msg void On1ppstimingQueryppspulseclksrc();
	afx_msg void OnBinaryConfigureSBAS();
	afx_msg void OnBinaryConfigureSAGPS();
	afx_msg void OnBinaryConfigureQZSS();
	afx_msg void OnBinaryConfigureDGPS();
	afx_msg void OnBinaryConfigureSmoothMode();
	afx_msg void OnBinaryConfigTimeStamping();
	afx_msg void OnConfigLeapSeconds();
	afx_msg void OnConfigParamSearchEngineSleepCriteria();
	afx_msg void OnConfigDatumIndex();
	afx_msg void OnConfigVeryLowSpeed();
	afx_msg void OnConfigDofunUniqueId();
	afx_msg void OnEraseDofunUniqueId();
	afx_msg void OnConfigureNoisePowerControl();
	afx_msg void OnConfigureInterferenceDetectControl();
	afx_msg void OnConfigNMEABinaryOutputDestination();
	afx_msg void OnConfigParameterSearchEngineNumber();
	afx_msg void OnAgpsFtpSrec();
	afx_msg void OnRomAgpsFtpSrec();
	afx_msg void OnRomAgpsFtpNew();
	afx_msg void OnClockOffsetPredict();
	afx_msg void OnClockOffsetPredictOld();
	afx_msg void OnHostBasedDownload();
	afx_msg void OnFiremareDownload();
	afx_msg void OnConfigPositionFixNavigationMask();
	afx_msg void OnParallelDownload();
	afx_msg void OnConfigRefTimeSyncToGpsTime();
	afx_msg void OnNmeaChecksumCalculator();
	afx_msg void OnBinaryChecksumCalculator();
	afx_msg void OnTestExternalSrec();
	afx_msg void OnIqPlot();
	afx_msg void OnReadMemToFile();
	afx_msg void OnWriteMemToFile();
	afx_msg void OnUpgradeDownload();
	afx_msg void OnPatch();
	afx_msg void OnGetGlonassEphemeris();
	afx_msg void OnSetGlonassEphemeris();
	afx_msg void OnGetBeidouEphemeris();
	afx_msg void OnSetBeidouEphemeris();
	afx_msg void OnSup800EraseData();
	afx_msg void OnSup800WriteData();
	afx_msg void OnSup800ReadData();
	afx_msg void OnConfigGeofence();
	afx_msg void OnConfigGeofence1();
	afx_msg void OnConfigGeofence2();
	afx_msg void OnConfigGeofence3();
	afx_msg void OnConfigGeofence4();
	afx_msg void OnConfigRtkMode();
	afx_msg void OnConfigRtkMode2();
	afx_msg void OnConfigRtkParameters();
	afx_msg void OnRtkReset();
	afx_msg void OnConfigMessageOut();
	afx_msg void OnConfigSubSecRegister();
	afx_msg void OnConfigPstmDeviceAddress();
	afx_msg void OnConfigPstmLatLonDigits();
	afx_msg void OnConfigureSignalDisturbanceStatus();
	afx_msg void OnConfigureGpsUtcLeapSecondsInUtc();
	afx_msg void OnGpsdoFirmwareDownload();
	//afx_msg void OnStnClickedInformationT();
	afx_msg void OnStnClickedInformationB();
	//afx_msg void OnStnClickedRtkInfoT();
	afx_msg void OnStnClickedRtkInfoB();
	afx_msg void OnBnClickedCoorSwitch();
	afx_msg void OnConfigPsti030();
	afx_msg void OnConfigPsti032();
	afx_msg void OnConfigPsti004();

	afx_msg void OnQueryPositionRate()
	{ GenericQuery(&CGPSDlg::QueryPositionRate); }
	afx_msg void OnQueryDatum()
	{ GenericQuery(&CGPSDlg::QueryDatum); }
	afx_msg void OnQuerySha1String()
	{ GenericQuery(&CGPSDlg::QuerySha1String); }
	afx_msg void OnQueryConstellationCapability()
	{ GenericQuery(&CGPSDlg::QueryConstellationCapability); }
	afx_msg void OnQueryVersionExtension()
	{ GenericQuery(&CGPSDlg::QueryVersionExtension); }
	afx_msg void OnQuerySoftwareVersionSystemCode()
	{ GenericQuery(&CGPSDlg::QuerySoftwareVersionSystemCode); }
	afx_msg void OnQuerySoftwareCrcSystemCode()	
	{ GenericQuery(&CGPSDlg::QuerySoftwareCrcSystemCode); }
	afx_msg void OnQueryPositionPinning()
	{ GenericQuery(&CGPSDlg::QueryPositionPinning); }
	afx_msg void OnQuery1ppsMode()
	{ GenericQuery(&CGPSDlg::Query1ppsMode); }
	afx_msg void OnQueryPowerMode()
	{ GenericQuery(&CGPSDlg::QueryPowerMode); }
	afx_msg void OnQueryV8PowerSavingParameters()
	{ GenericQuery(&CGPSDlg::QueryV8PowerSavingParameters); }
	afx_msg void OnQueryProprietaryMessage()
	{ GenericQuery(&CGPSDlg::QueryProprietaryMessage); }
	afx_msg void OnQueryTiming()
	{ GenericQuery(&CGPSDlg::QueryTiming); }
	afx_msg void OnQueryDopMask()
	{ GenericQuery(&CGPSDlg::QueryDopMask); }
	afx_msg void OnQueryElevationAndCnrMask()
	{ GenericQuery(&CGPSDlg::QueryElevationAndCnrMask); }
	afx_msg void OnQueryAntennaDetection()
	{ GenericQuery(&CGPSDlg::QueryAntennaDetection); }
	afx_msg void OnQueryNoisePower()
	{ GenericQuery(&CGPSDlg::QueryNoisePower); }
	afx_msg void OnQueryDrInfo()
	{ GenericQuery(&CGPSDlg::QueryDrInfo); }
	afx_msg void OnQueryDrHwParameter()
	{ GenericQuery(&CGPSDlg::QueryDrHwParameter); }
	afx_msg void OnQuerySbas()
	{ GenericQuery(&CGPSDlg::QuerySbas); }
	afx_msg void OnQuerySagps()
	{ GenericQuery(&CGPSDlg::QuerySagps); }
	afx_msg void OnQueryQzss()
	{ GenericQuery(&CGPSDlg::QueryQzss); }
	afx_msg void OnQueryNoisePowerControl()
	{ GenericQuery(&CGPSDlg::QueryNoisePowerControl); }
	afx_msg void OnQueryInterferenceDetectControl()
	{ GenericQuery(&CGPSDlg::QueryInterferenceDetectControl); }
	afx_msg void OnQueryNmeaBinaryOutputDestination()
	{ GenericQuery(&CGPSDlg::QueryNmeaBinaryOutputDestination); }
	afx_msg void OnQueryParameterSearchEngineNumber()
	{ GenericQuery(&CGPSDlg::QueryParameterSearchEngineNumber); }
	afx_msg void OnQueryAgpsStatus()
	{ GenericQuery(&CGPSDlg::QueryAgpsStatus); }
	afx_msg void OnQueryDatalogLogStatus()
	{ GenericQuery(&CGPSDlg::QueryDatalogLogStatus); }
	afx_msg void OnQueryPositionFixNavigationMask()
	{ GenericQuery(&CGPSDlg::QueryPositionFixNavigationMask); }
	afx_msg void OnQueryNmeaIntervalV8()
#if (CUSTOMER_ID==0x0001)	//SWID customize
	{ GenericQuery(&CGPSDlg::QueryNmeaInterval2V8); }
#else
	{ GenericQuery(&CGPSDlg::QueryNmeaIntervalV8); }
#endif
	afx_msg void OnQueryEricssonInterval()
	{ GenericQuery(&CGPSDlg::QueryEricssonInterval); }
	afx_msg void OnQueryRefTimeSyncToGpsTime()
	{ GenericQuery(&CGPSDlg::QueryRefTimeSyncToGpsTime); }
	afx_msg void OnQuerySearchEngineSleepCriteria()
	{ GenericQuery(&CGPSDlg::QuerySearchEngineSleepCriteria); }
	afx_msg void OnQueryDatumIndex()
	{ GenericQuery(&CGPSDlg::QueryDatumIndex); }
	afx_msg void OnQueryVeryLowSpeed()
	{ GenericQuery(&CGPSDlg::QueryVeryLowSpeed); }
	afx_msg void OnQueryDofunUniqueId()
	{ GenericQuery(&CGPSDlg::QueryDofunUniqueId); }

	afx_msg void OnQueryUartPass()
	{ GenericQuery(&CGPSDlg::QueryUartPass); }
	afx_msg void OnGpsdoResetSlave()
	{ GenericQuery(&CGPSDlg::GpsdoResetSlave); }
	afx_msg void OnGpsdoEnterRom()
	{ GenericQuery(&CGPSDlg::GpsdoEnterRom); }
	afx_msg void OnGpsdoLeaveRom()
	{ GenericQuery(&CGPSDlg::GpsdoLeaveRom); }
	afx_msg void OnGpsdoEnterDownload()
	{ GenericQuery(&CGPSDlg::GpsdoEnterDownload); }
	afx_msg void OnGpsdoLeaveDownload()
	{ GenericQuery(&CGPSDlg::GpsdoLeaveDownload); }
	afx_msg void OnGpsdoEnterDownloadHigh()
	{ GenericQuery(&CGPSDlg::GpsdoEnterDownloadHigh); }
	afx_msg void OnGpsdoEnterUart()
	{ GenericQuery(&CGPSDlg::GpsdoEnterUart); }
	afx_msg void OnGpsdoLeaveUart()
	{ GenericQuery(&CGPSDlg::GpsdoLeaveUart); }
	afx_msg void OnQueryNavigationModeV8()
	{ GenericQuery(&CGPSDlg::QueryNavigationModeV8); }
	afx_msg void OnQueryGnssBootStatus()
	{ GenericQuery(&CGPSDlg::QueryGnssBootStatus); }
	afx_msg void OnQueryDrMultiHz()
	{ GenericQuery(&CGPSDlg::QueryDrMultiHz); }
	afx_msg void OnQueryGnssKnumberSlotCnr2()
	{ GenericQuery(&CGPSDlg::QueryGnssKnumberSlotCnr2); }
	afx_msg void OnQueryGnssNmeaTalkId()
	{ GenericQuery(&CGPSDlg::QueryGnssNmeaTalkId); }
	afx_msg void OnQueryGnssNavSol()
	{ GenericQuery(&CGPSDlg::QueryGnssNavSol); }
	afx_msg void OnQueryCustomerID()
	{ GenericQuery(&CGPSDlg::QueryCustomerID); }
	afx_msg void OnQuery1ppsFreqencyOutput()
	{ GenericQuery(&CGPSDlg::Query1ppsFreqencyOutput); }
	afx_msg void OnQueryBinaryMeasurementDataOut()
	{ GenericQuery(&CGPSDlg::QueryBinaryMeasurementDataOut); }
	afx_msg void OnQuerySerialNumber()
	{ GenericQuery(&CGPSDlg::QuerySerialNumber); }
	afx_msg void OnQueryDgps()
	{ GenericQuery(&CGPSDlg::QueryDgps); }
	afx_msg void OnQuerySmoothMode()
	{ GenericQuery(&CGPSDlg::QuerySmoothMode); }
	afx_msg void OnQueryTimeStamping()
	{ GenericQuery(&CGPSDlg::QueryTimeStamping); }
	afx_msg void OnQueryGpsTime()
	{ GenericQuery(&CGPSDlg::QueryGpsTime); }
	afx_msg void OnQuerySignalDisturbanceStatus()
	{ GenericQuery(&CGPSDlg::QuerySignalDisturbanceStatus); }
	afx_msg void OnQuerySignalDisturbanceData()
	{ GenericQuery(&CGPSDlg::QuerySignalDisturbanceData); }
	afx_msg void OnResetOdometer()
	{ GenericQuery(&CGPSDlg::ResetOdometer); }
	afx_msg void OnQueryCableDelay()
	{ GenericQuery(&CGPSDlg::QueryCableDelay); }
	//afx_msg void OnQueryGeofence()
	//{ m_nGeofecingNo = 0; GenericQuery(&CGPSDlg::QueryGeofence); }
	afx_msg void OnQueryGeofence1()
	{ m_nGeofecingNo = 1; GenericQuery(&CGPSDlg::QueryGeofenceEx); }
	afx_msg void OnQueryGeofence2()
	{ m_nGeofecingNo = 2; GenericQuery(&CGPSDlg::QueryGeofenceEx); }
	afx_msg void OnQueryGeofence3()
	{ m_nGeofecingNo = 3; GenericQuery(&CGPSDlg::QueryGeofenceEx); }
	afx_msg void OnQueryGeofence4()
	{ m_nGeofecingNo = 4; GenericQuery(&CGPSDlg::QueryGeofenceEx); }
	afx_msg void OnQueryGeofenceResult()
	{ GenericQuery(&CGPSDlg::QueryGeofenceResult); }
	afx_msg void OnQueryGeofenceResultEx()
	{ GenericQuery(&CGPSDlg::QueryGeofenceResultEx); }
	afx_msg void OnQueryRtkMode()
	{ GenericQuery(&CGPSDlg::QueryRtkMode); }
	afx_msg void OnQueryRtkMode2()
	{ GenericQuery(&CGPSDlg::QueryRtkMode2); }
	afx_msg void OnQueryRtkParameters()
	{ GenericQuery(&CGPSDlg::QueryRtkParameters); }
	afx_msg void OnQueryPstmDeviceAddress()
	{ GenericQuery(&CGPSDlg::QueryPstmDeviceAddress); }
	afx_msg void OnQueryPstnLatLonDigits()
	{ GenericQuery(&CGPSDlg::QueryPstnLatLonDigits); }
	afx_msg void OnQueryPsti030()
	{ GenericQuery(&CGPSDlg::QueryPsti030); }
	afx_msg void OnQueryPsti032()
	{ GenericQuery(&CGPSDlg::QueryPsti032); }
	afx_msg void OnQueryPsti004()
	{ GenericQuery(&CGPSDlg::QueryPsti004); }

	struct MenuItemEntry {
		BOOL showOption;
		UINT type;			//MF_STRING, MF_SEPARATOR, MF_POPUP
		UINT id;
		LPCSTR	pszText;
		MenuItemEntry*	subMenu;
	};

	struct UiLocationEntry {
		BOOL showOption;
		UINT type;			//MF_STRING, MF_SEPARATOR, MF_POPUP
		UINT id;
		RECT rect;
	};

	enum PrnType
	{
		Unknown = 0,
		Gps = 1,
		Glonass = 2,
		Beidou = 3,
		Gallilo = 4,
	};

	enum CoorFormat
	{
		Degree = 0,
		DegreeMinute,
		DegreeMinuteSecond,
	};

	BOOL m_copyLatLon;
	CoorFormat m_coorFormat;
	void Show_EarthChart(CDC *dc);
	void DrawGnssSatellite(CDC* dc, int id, int centerX, int centerY);
	void DrawBdSatellite(CDC* dc, int id, int centerX, int centerY);
	void DrawGaSatellite(CDC* dc, int id, int centerX, int centerY);

	void parse_sti_03_message(const char *buff,int len); /* for timing module */
	void parse_sti_04_001_message(const char *buff, int len); /* for timing module */
	void parse_sti_message(const char *buff,int len);
	void parse_sti_0_message(const char *buff,int len); /* for timing module */
	//	void parse_rtoem_message(const char *buff, int len);
	void parse_psti_50(const char *buff);
	void parse_sti_20_message(const char *buff,int len); /* for timing module */

#if(MORE_INFO || _TAB_LAYOUT_)
	void parse_sti_30_message(const char *buff,int len); /* for RTK module */
#endif
#if (SHOW_RTK_BASELINE || _TAB_LAYOUT_)
	void parse_sti_31_message(const char *buff,int len); /* for RTK module */
#endif
#if(_TAB_LAYOUT_)
	void parse_sti_32_message(const char *buff,int len); /* for RTK module moving base*/
#endif

	//	void Config_silab_baudrate(HANDLE *m_DeviceHandle);
	//	void Config_silab_baudrate_flash(HANDLE *m_DeviceHandle);
	void DoCommonConfig(CCommonConfigDlg* dlg);
	void DoCommonConfigDirect(CCommonConfigDlg* dlg, int type);
	//Functions for combain GPS / GNSS Viewer UI Layout.
	int CreateSubMenu(const HMENU hMenu, const MenuItemEntry* menuItemTable, LPCSTR pszSubMenuText);
	PrnType GetPrnType(int id);
	void RescaleDialog();
	void SwitchToConnectedStatus(BOOL bSwitch);
	void SetFactoryDefault(bool isReboot);
	void GetGPSStatus();
	bool DoZenlandInit();
	bool DoZenlandQuery();
	void SetConnectTitle(bool isInConnect);
	//Test Clock Offser
	U08 QueryChanelFreq(int chanel, U16 *prn, double *freq);
	U08 PredictClockOffset(double *clk_offset);
	//End
	bool WriteRegister(U32 addr, U32 data, LPCSTR prompt = NULL);

	//	int m_comPort;
	//	int m_baudrate;
	WPARAM plugin_wParam;
	CString plugin_port_name;
	U16 m_customerId;

	CLabel m_wgs84_x,m_wgs84_y,m_wgs84_z;
	CLabel m_enu_e,m_enu_n,m_enu_u;
	CSnrBarChartGpsGlonass* gpsSnrBar;
	//	CSnrBarChartGlonass* gnssSnrBar;
	CSnrBarChartBeidou* bdSnrBar;
	CSnrBarChartGalileo* gaSnrBar;
	CPic_Scatter* pic_scatter;
	CPic_Earth* pic_earth;
	CLabel m_fixed_status;

	CEdit m_odo_meter;
	//CEdit m_gyro_data;
	CEdit m_backward_indicator;
	CStatic m_lbl_odo_meter;
	CStatic m_lbl_gyro_data;
	CStatic m_lbl_backward_indicator;

	BinaryData m_versionInfo;
	BinaryData m_bootInfo;

	bool m_firstDataIn;
	U32 m_customerID;
	int m_dataLogDecompressMode;

	DECLARE_MESSAGE_MAP()
protected:
  int m_nDoFlag;
	bool ShowCommand(U08 *buffer, int length);
	void ShowFormatError(U08* cmd, U08* ack);
	void SwitchInfoTab();
};
