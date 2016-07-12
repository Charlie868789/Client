#ifndef CONFIG_H_
#define CONFIG_H_
/*
* The parameter define as follows:
*   lpAppName
*   lpKeyName
*   lpString
*   lpFileName
*   lpReturnedString
*   nSize
*   nDefault
*/

struct ModuleInfo
{
        //unsigned char *ModServion_maincomm;
        //unsigned char *ModServion_dataserver;
        unsigned char *ModServerIp;
        //unsigned char *StationName;
};

struct GPS_Data
{
	char Gps_time[20];
	char Gps_sv;
	char Gps_latitude[12];
	char Gps_longitude[12];
	//char Gps_warn;
	char Gps_speed[5];
	char Gps_date[8];// utc date
};

int GetGpsData(
	struct GPS_Data gpsdata
	);
int WritePrivateProfileString(
                        char *lpAppName,
                        char *lpKeyName,
                        char *lpString,
                        char *lpFileName
        );

int GetPrivateProfileString(
                        char *lpAppName,
                        char *lpKeyName,
                        char *lpDefault,
                        char *lpReturnedString,
                        unsigned long nSize,
                        char *lpFileName
        );

int GetPrivateProfileUL(
                        char *lpAppName,
                        char *lpKeyName,
                        unsigned long nDefault,
                        char *lpFileName
        );

int GetPrivateKeyName(
                        char *lpAppName,
                        char *lpKeyName,
                        char *lpDefault,
                        char *lpReturnedString,
                        unsigned long nSize,
                        char *lpFileName
        );

void LTruncate(
                   char *pString,
                   char *szFill
        );

void RTruncate(
                  char *pString,
                  char *szFill
        );
//Reading Module Info
int ReadModinfo(
		struct ModuleInfo ModInfo
	);
#endif
