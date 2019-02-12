#include <iostream>
#include <string.h>
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include <locale>
#include <sstream>

#include <string>
#include <stdio.h>

    #include <tchar.h>
    #include <wininet.h>

#pragma comment (lib, "wininet.lib")
#pragma comment (lib, "libwininet.a")

//https://coinmarketcap.com/api/documentation/v1/#
//https://stackoverflow.com/questions/10106816/how-to-contruct-httpsendrequest-method-of-wininet
//https://github.com/Dondor17/WinINet---Simple-GET-POST-request/blob/master/WinINet%20-%20Simple%20GET-POST%20request/ConsoleApp/ConsoleApp.cpp

using namespace std;

int main()
{
    string website_HTML;

    HINTERNET hIntSession =
      ::InternetOpen(_T("MyApp"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);

    HINTERNET hHttpSession =
      InternetConnect(hIntSession, _T("pro-api.coinmarketcap.com"), 80, 0, 0, INTERNET_SERVICE_HTTP, 0, NULL);

    HINTERNET hHttpRequest = HttpOpenRequest(
      hHttpSession,
      _T("GET"),
      _T("v1/cryptocurrency/listings/latest?start=1&limit=5000&convert=BTC"),
      0, 0, 0, INTERNET_FLAG_RELOAD, 0);

    TCHAR* szHeaders = _T("Content-Type: text/html\r\nX-CMC_PRO_API_KEY: key");
    CHAR szReq[1024] = "";
    if( !HttpSendRequest(hHttpRequest, szHeaders, _tcslen(szHeaders), szReq, strlen(szReq))) {
      DWORD dwErr = GetLastError();
      /// handle error
    }

    CHAR szBuffer[1025];
    DWORD dwRead=0;
    while(::InternetReadFile(hHttpRequest, szBuffer, sizeof(szBuffer)-1, &dwRead) && dwRead) {
      szBuffer[dwRead] = 0;
      OutputDebugStringA(szBuffer);
      dwRead=0;
       int i = 0;
        while (szBuffer[i] >= 32 || szBuffer[i] == '\n' || szBuffer[i] == '\r'){
            website_HTML+=szBuffer[i];
            i += 1;
        }

    }

    ::InternetCloseHandle(hHttpRequest);
    ::InternetCloseHandle(hHttpSession);
    ::InternetCloseHandle(hIntSession);

    cout << website_HTML << endl;

    return 0;
}
