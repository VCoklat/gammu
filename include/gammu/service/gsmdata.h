/* (c) 2001-2004 by Marcin Wiacek */

#ifndef __gsm_wap_h
#define __gsm_wap_h

#include "gsmmisc.h"
#include "../misc/misc.h"

/* --------------------------- WAP or MMS settings ------------------------- */

typedef enum {
	WAPSETTINGS_SPEED_9600,
	WAPSETTINGS_SPEED_14400,
	WAPSETTINGS_SPEED_AUTO
} WAPSettings_Speed;

typedef enum {
	WAPSETTINGS_BEARER_SMS = 1,
	WAPSETTINGS_BEARER_DATA,
	WAPSETTINGS_BEARER_USSD,
	WAPSETTINGS_BEARER_GPRS
} WAPSettings_Bearer;

typedef struct {
	char			Title		[(20+1)*2];
	char			HomePage	[(100+1)*2];
	WAPSettings_Bearer	Bearer;
	bool			IsSecurity;
	bool			IsContinuous;

  	/* for data bearer */
  	bool			IsISDNCall;
	bool			IsNormalAuthentication;

	/* for sms bearer */
	char			Server		[(21+1)*2];

	/* for sms or ussd bearer */
	char			Service		[(20+1)*2];
	bool			IsIP;

	/* for ussd bearer */
	char			Code		[(10+1)*2];

	/* for data or gprs */
	char			IPAddress	[(20+1)*2];
	bool			ManualLogin;
	char			DialUp		[(20+1)*2];
	char			User		[(50+1)*2]; /*is length OK ?*/
	char			Password	[(50+1)*2]; /*is length OK ?*/
	WAPSettings_Speed	Speed;
} GSM_WAPSettings;

typedef struct {
	int			Location;
	unsigned char		Number;
	GSM_WAPSettings		Settings[4];
	bool			Active;
	bool			ReadOnly;
	char			Proxy		[(100+1)*2];
	int			ProxyPort;
	char			Proxy2		[(100+1)*2];
	int			Proxy2Port;

	WAPSettings_Bearer	ActiveBearer;
} GSM_MultiWAPSettings;

void NOKIA_EncodeWAPMMSSettingsSMSText(unsigned char *Buffer, int *Length, GSM_WAPSettings *settings, bool MMS);

/* -------------------------------- WAP Bookmark --------------------------- */

typedef struct {
	unsigned char		Address		[(255+1)*2];
	unsigned char		Title		[(50+1)*2];
	int			Location;
} GSM_WAPBookmark;

void 		NOKIA_EncodeWAPBookmarkSMSText	(unsigned char *Buffer, int *Length, GSM_WAPBookmark *bookmark);
GSM_Error 	GSM_EncodeURLFile		(unsigned char *Buffer, int *Length, GSM_WAPBookmark *bookmark);

/* ------------------------------ MMS Indicator ---------------------------- */

typedef struct {
	char		Address[500];
	char		Title[200];
	char		Sender[200];
} GSM_MMSIndicator;

void GSM_EncodeMMSIndicatorSMSText(unsigned char *Buffer, int *Length, GSM_MMSIndicator Indicator);

void GSM_EncodeWAPIndicatorSMSText(unsigned char *Buffer, int *Length, char *Text, char *URL);

/* ------------------------------ MMS file --------------------------------- */

#define MAX_MULTI_MMS 20

typedef enum {
	MMSADDRESS_PHONE,
	MMSADDRESS_UNKNOWN
} MMSAddressType;

typedef struct {
	GSM_File		File;
	unsigned char		ContentType[400];	// CT in Unicode
	unsigned char		SMIL[400];		// Smil ID in Unicode
} EncodedMultiPartMMSEntry2;

typedef struct {
	/* Subparts */
	EncodedMultiPartMMSEntry2 Entries[MAX_MULTI_MMS];
	int			  EntriesNum;

	unsigned char		  Source[200];		// in Unicode
	MMSAddressType		  SourceType;
	unsigned char		  Destination[200];	// in Unicode
	MMSAddressType		  DestinationType;
	unsigned char	  	  CC[200];		// in Unicode
	MMSAddressType		  CCType;

	unsigned char		  Subject[200];		// in Unicode
	unsigned char		  ContentType[400];	// CT in Unicode
	unsigned char		  MSGType[50];		// no Unicode

	bool			  DateTimeAvailable;
	GSM_DateTime		  DateTime;

	bool			  MMSReportAvailable;
	bool			  MMSReport;
} GSM_EncodedMultiPartMMSInfo2;

GSM_Error GSM_DecodeMMSFileToMultiPart(GSM_File *file, GSM_EncodedMultiPartMMSInfo2 *info);
GSM_Error GSM_ClearMMSMultiPart(GSM_EncodedMultiPartMMSInfo2 *info);

/* ---------------------- MMS folders ------------------------------------- */

/**
 * Number of possible MMS folders.
 */
#define GSM_MAX_MMS_FOLDERS	     	10
/**
 * Maximal length of MMS folder name.
 */
#define GSM_MAX_MMS_FOLDER_NAME_LEN     20

/**
 * Information about MMS folder.
 */
typedef struct {
	/**
	 * Whether it is really inbox.
	 */
	bool		    	InboxFolder;
        /**
  	 * Name for MMS folder.
	 */
        char	    		Name[(GSM_MAX_MMS_FOLDER_NAME_LEN+1)*2];
} GSM_OneMMSFolder;

/**
 * List of MMS folders.
 */
typedef struct {
        /**
	 * Array of structures holding information about each folder.
	 */
        GSM_OneMMSFolder	Folder[GSM_MAX_MMS_FOLDERS];
        /**
 	 * Number of MMS folders.
	 */
        unsigned char	   	Number;
} GSM_MMSFolders;

/* ------------------------------------------------------------------------ */

typedef struct {
	int			Location;
	bool			Active;
	bool			SyncPhonebook;
	bool			SyncCalendar;
	char			Name[(20+1)*2];
	char			PhonebookDataBase[(50+1)*2];
	char			CalendarDataBase[(50+1)*2];
	char			User[(30+1)*2];
	char			Password[(20+1)*2];
	char			Server[(128+1)*2];
	GSM_MultiWAPSettings	Connection;
} GSM_SyncMLSettings;

/* ------------------------------------------------------------------------ */

typedef struct {
	char			Name[(50+1)*2];
	char			HomePage[(200+1)*2];
	char			User[(50+1)*2];
	char			Password[(50+1)*2];
	int			Location;
	bool			Active;
	GSM_MultiWAPSettings	Connection;
} GSM_ChatSettings;

#endif

/* How should editor hadle tabs in this file? Add editor commands here.
 * vim: noexpandtab sw=8 ts=8 sts=8:
 */
