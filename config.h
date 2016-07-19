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
        //char *ModServion_maincomm;
        //char *ModServion_dataserver;
        char *ModServerIp;
        //unsigned char *StationName;
};

struct GPS_Data
{
	char *Gps_time;
	char *Gps_sv;
	char *Gps_latitude;
	char *Gps_longitude;
	//char Gps_warn;
	char *Gps_speed;
	char *Gps_date;// utc date
};

struct Sensor_Data
{
	char *type;
	char *sensordata;
	char *reseverarea;
};

int GetGpsData(
	struct GPS_Data gpsdata
	);
int GetSensorNodeData(
	struct Sensor_Data sensordata
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
