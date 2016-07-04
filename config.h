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
