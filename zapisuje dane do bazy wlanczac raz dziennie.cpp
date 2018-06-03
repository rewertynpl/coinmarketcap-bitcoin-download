
#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdlib.h>
#include <string>
#include <windows.h>//potrzebna do HRESULT    dl;
//#include <winbase.h>
//#include <curl/curl.h>//potrzebna do HRESULT    dl;

//#include <C:\Users\marma\Desktop\c++\curl-7.50.3-win64-mingw\include\curl\curl.h>//do code block

copyrights marcin matysek rewwertyn marcinmatysek1@gmail.com


#define MAX_LINE 512
//void get_file( const char * url, const char * file_name, const char * mode );
void dopisz_dzien_do_bazy(struct struktura1 **a1,struct struktura1 **a2,int ile_walut_wczytac1,int ile_walut_wczytac2,int  ile_dni_pobrac_z_bazy_danych2);
void wczytanie_ile_walut(struct struktura1 **a2,int *ile_walut_wczytac);
void wczytanie_ile_dni_w_bazie(struct struktura1 **a2,int *ile_walut_wczytac,int  *ile_dni_pobrac_z_bazy_danych);
void przerabianie_monet();
int zapis_url_do_pliku();
void wczytanie_1(struct struktura1 **a2);
void wczytanie_baze(struct struktura1 **a2);
using namespace std;

struct struktura1
{
    string id;
    string name;
    string symbol;
    int rank1;
    float price_usd;
    float price_btc;
    float a24h_volume_usd;
    float market_cap_usd;
    float available_supply;
    float total_supply;
    float max_supply;
    float percent_change_1h;
    float percent_change_24h;
    float percent_change_7d;
    int last_updated;
    string koniec;
    string kon;
};
int main()
{

//http://cpp0x.pl/forum/temat/?id=16250
//https://stackoverflow.com/questions/5485081/how-do-i-solve-these-libcurl-linking-errors

    //How to read text from internet with C++
    //https://stackoverflow.com/questions/28508236/how-to-read-text-from-internet-with-c
//https://forums.anandtech.com/threads/can-c-read-a-text-file-from-the-internet.808891/
//Pobieranie plików z Internetu

//https://stackoverflow.com/questions/6243638/adding-static-libcurl-to-codeblocks-ide

//wczytywaine pliku z internetu
//get_file( "cpp0x.pl", "index.txt", "w" ); //poberamy tekst(?ród3o strony i zapisujemy do pliku "index.txt")
//get_file( "http://cpp0x.pl/!images/default/icons/artykuly.png", "artykuly.png", "wb" ); //pobieramy plik binarny


//http://www.beej.us/guide/bgnet/html/single/bgnet.html#recvman

//////////////////
    //https://api.coinmarketcap.com/v1/ticker/?limit=0
//////////////////

    int ile_walut_wczytac1=0;
    int ile_walut_wczytac2=0;
    int ile_dni_pobrac_z_bazy_danych2=0;

    struktura1 **a1= new struktura1*[1];
    for(int i=0;i<1;i++)
    {
        a1[i]= new struktura1[1];
    }

    zapis_url_do_pliku();
    przerabianie_monet();
    wczytanie_ile_walut(a1,&ile_walut_wczytac1);
    cout<<"ile_walut_wczytac1 "<<ile_walut_wczytac1<<endl;
    wczytanie_ile_dni_w_bazie(a1,&ile_walut_wczytac2,&ile_dni_pobrac_z_bazy_danych2);

    cout<<"ile_walut_wczytac2 "<<ile_walut_wczytac2<<endl;
    cout<<"ile_dni_pobrac_z_bazy_danych2 "<<ile_dni_pobrac_z_bazy_danych2<<endl;

    struktura1 **a2= new struktura1*[1];
    for(int i=0;i<1;i++)
    {
        a2[i]= new struktura1[ile_walut_wczytac1];
    }

    struktura1 **a3= new struktura1*[ile_dni_pobrac_z_bazy_danych2];
    for(int i=0;i<ile_dni_pobrac_z_bazy_danych2;i++)
    {
        a3[i]= new struktura1[ile_walut_wczytac2];
    }

    //wczytanie z pliku
    wczytanie_1(a2);
    wczytanie_baze(a3);
    //system("pause");
    dopisz_dzien_do_bazy(a2,a3,ile_walut_wczytac1,ile_walut_wczytac2,ile_dni_pobrac_z_bazy_danych2);
    cout<<"dopisz do bazy";//system("pause");

/*
    for(int i1=0;i1<1;i1++)
    {
        for(int j1=0;j1<ile_walut_wczytac1;j1++)
        {

cout<<a2[i1][j1].id<<endl;
cout<<a2[i1][j1].name<<endl;
cout<<a2[i1][j1].symbol<<endl;
cout<<a2[i1][j1].rank1<<endl;
cout<<a2[0][j1].price_usd<<endl;
cout<<a2[0][j1].price_btc<<endl;
cout<<a2[0][j1].a24h_volume_usd<<endl;
cout<<a2[0][j1].market_cap_usd<<endl;
cout<<a2[0][j1].available_supply<<endl;
cout<<a2[0][j1].total_supply<<endl;
cout<<a2[0][j1].max_supply<<endl;
cout<<a2[0][j1].percent_change_1h<<endl;
cout<<a2[0][j1].percent_change_24h<<endl;
cout<<a2[0][j1].percent_change_7d<<endl;
cout<<a2[0][j1].last_updated<<endl;
cout<<a2[0][j1].koniec<<endl;
system("pause");
}
}
*/

    for(int i=0;i<1;i++)
    {
        delete [] a1[i];
    }
    delete [] a1;

    for(int i=0;i<1;i++)
    {
        delete [] a2[i];
    }
    delete [] a2;
    for(int i=0;i<ile_dni_pobrac_z_bazy_danych2;i++)
    {
        delete [] a3[i];
    }
    delete [] a3;
    system("pause");
    return 0;
}


void przerabianie_monet()
{
    int r=0;
    int m=0;
    int licz=0;
    int flaga1=0;
    int flaga2=0;
    int flaga3=0;
    int flaga4=0;

    string tab1[16]={};
    char* temp0 = new char[sizeof(char)]; // tymczasowy bufor na dane
    char* temp1 = new char[40*sizeof(char)]; // tymczasowy bufor na dane

    ifstream plik1;
    ofstream plik2;

    for(int j=0;j<40;j++)
    {
        temp1[j]='\0';
    }
    plik1.open("1.txt", ios::binary);// otwieramy plik do odczytu binarnego
    plik2.open("2.txt");


    for(int k=0;k<99000;k++)
    {
        m=0;
        for(int i=0;i<11000;i++)
        {
            plik1.read(temp0, sizeof(char));
            //cout << temp1;


            if(flaga1==1)
            {
                licz++;
            }
            if(temp0[0]=='"')
            {
                if(flaga1==0)
                {
                    flaga1=1;
                }
                else
                {
                    flaga1=0;
                    flaga2=1;
                    flaga4=0;
                }
            }
            if(flaga2==1)
            {
                flaga2=0;
                if(flaga3==0)
                {
                    for(int i3=0;i3<100;i3++)
                    {
                    plik1.read(temp0, sizeof(char));
                    if(temp0[0]=='"'){plik1.seekg(-1,ios_base::cur);break;}
                    else if(temp0[0]=='n')
                        {
                            m++;
                            plik2<<"0"<<"\n";
                            flaga1=0;
                            flaga2=0;
                            flaga3=0;
                            flaga4=0;
                            licz=0;
                            break;
                        }

                    flaga3=1;
                }
                }
                else
                {
                    flaga3=0;
                    flaga4=1;
                    //cout <<"  " <<licz <<"  ";
                    plik1.seekg(-licz,ios_base::cur);
                    licz--;
                    plik1.read(temp1, licz*sizeof(char));
                    tab1[m]=temp1;
                    plik2<<tab1[m]<<"\n";
                    plik1.read(temp0, sizeof(char));
                    for(int j=0;j<40;j++)
                    {
                        temp1[j]='\0';
                    }
                    m++;

                }
                 licz=0;
            }
            if(temp0[0]=='}')
            {
                plik2<<"}"<<endl;m=0;
                for(int i2=0;i2<100;i2++)
                {
                    plik1.read(temp0, sizeof(char));
                    if((int)temp0[0]=='{')
                    {
                    flaga4=1;
                    break;
                    }
                }
                break;
            }
        }
            if(temp0[0]==']'){plik2<<"]"<<endl;break;}
    r++;
    }
    plik1.close();
    plik2.close();
}

int zapis_url_do_pliku()
{
//source https://www.go4expert.com/articles/download-file-using-urldownloadtofile-c-t28721/
       char url[MAX_LINE] = "https://api.coinmarketcap.com/v1/ticker/?limit=0";
    char destination[MAX_LINE] = "1.txt";
    char buffer[20000];

    HRESULT    dl;

    typedef HRESULT (WINAPI * URLDownloadToFileA_t)(LPUNKNOWN pCaller, LPCSTR szURL, LPCSTR szFileName, DWORD dwReserved, void * lpfnCB);
    URLDownloadToFileA_t xURLDownloadToFileA;
    xURLDownloadToFileA = (URLDownloadToFileA_t)GetProcAddress(LoadLibraryA("urlmon"), "URLDownloadToFileA");

    dl = xURLDownloadToFileA(NULL, url, destination, 0, NULL);

    sprintf( buffer, "Downloading File From: %s, To: %s\n", url, destination);
    if(dl == S_OK)
    {
        sprintf(buffer, "File Successfully Downloaded To: %s\n", destination);
        printf(buffer);//system("pause");
    }
    else if(dl == E_OUTOFMEMORY)
    {
        sprintf(buffer, "Failed To Download File Reason: Insufficient Memory\n");
        printf(buffer);//system("pause");
        return 0;
    }
    else
    {
        sprintf( buffer, "Failed To Download File Reason: Unknown");
        printf(buffer);//system("pause");
        return 0;
    }
}
void wczytanie_1(struct struktura1 **a2)
{      ifstream plik3;
    plik3.open("2.txt", ios::binary);// otwieramy plik do odczytu binarnego
    char* temp6 = new char[40*sizeof(char)]; // tymczasowy bufor na dane
    for(int j=0;j<40;j++)
    {
        temp6[j]='\0';
    }
    char* temp5 = new char[sizeof(char)]; // tymczasowy bufor na dane
    int licz2=0,licz3=0,licz1=0;
    char zm1;
    for(int i1=0;i1<1;i1++)
    {
        plik3>>zm1;
        if(plik3.eof()){cout<<"plik3.eof() "<<endl;break;}
        else{plik3.seekg(-1,ios_base::cur);}
        for(int j1=0;j1<11000;j1++)
        {   licz1++;
            licz2=0;
            licz3++;
            plik3>>a2[i1][j1].id;
            plik3.read(temp5, sizeof(char));
            for(int i2=0;i2<100;i2++)
            {
            plik3.read(temp5, sizeof(char));
            licz2++;
            if(temp5[0]==13){plik3.seekg(-(licz2-1),ios_base::cur);break;}
            //bo niektore coiny sa zapisane bez spacji np Bitcoin Cash
            }
            for(int j=0;j<40;j++)
            {
                temp6[j]='\0';
            }
            plik3.read(temp6, (licz2-1)*sizeof(char));
            a2[i1][j1].name=temp6;
            //cout<<licz2<<"  "<<temp6<<endl;system("pause");
            plik3>>a2[i1][j1].symbol>>a2[i1][j1].rank1>>a2[i1][j1].price_usd
            >>a2[i1][j1].price_btc>>a2[i1][j1].a24h_volume_usd>>a2[i1][j1].market_cap_usd>>a2[i1][j1].available_supply
            >>a2[i1][j1].total_supply>>a2[i1][j1].max_supply>>a2[i1][j1].percent_change_1h>>a2[i1][j1].percent_change_24h
            >>a2[i1][j1].percent_change_7d>>a2[i1][j1].last_updated>>a2[i1][j1].koniec;

            plik3>>zm1;
            if(zm1==']'){cout<<"void wczytanie_1 wczytano "<<licz3<<" walut"<<endl;break;}
            else{plik3.seekg(-1,ios_base::cur);}
        }
        a2[i1][licz1-1].kon="]";
        licz1=0;
    }
    plik3.close();
}
void wczytanie_baze(struct struktura1 **a2)
{
    ifstream plik3;
    plik3.open("baza.txt", ios::binary);// otwieramy plik do odczytu binarnego
    char* temp6 = new char[40*sizeof(char)]; // tymczasowy bufor na dane
    for(int j=0;j<40;j++)
    {
        temp6[j]='\0';
    }
    char* temp5 = new char[sizeof(char)]; // tymczasowy bufor na dane
    int licz2=0,licz3=0,licz3_max=0,licz_dni=0,licz1=0;
    char zm1;
    for(int i1=0;i1<10000;i1++)
    {
        plik3>>zm1;
        if(plik3.eof()){cout<<"liczba dni;;; "<<licz_dni<<" "<<endl;break;}
        else{plik3.seekg(-1,ios_base::cur);}
        licz_dni++;
        for(int j1=0;j1<11000;j1++)
        {   licz1++;
            licz2=0;
            licz3++;
            plik3>>a2[i1][j1].id;
            plik3.read(temp5, sizeof(char));
            for(int i2=0;i2<100;i2++)
            {
            plik3.read(temp5, sizeof(char));
            licz2++;
            if(temp5[0]==13){plik3.seekg(-(licz2-1),ios_base::cur);break;}
            //bo niektore coiny sa zapisane bez spacji np Bitcoin Cash
            }
            for(int j=0;j<40;j++)
            {
                temp6[j]='\0';
            }
            plik3.read(temp6, (licz2-1)*sizeof(char));
            a2[i1][j1].name=temp6;
            //cout<<licz2<<"  "<<temp6<<endl;system("pause");
            plik3>>a2[i1][j1].symbol>>a2[i1][j1].rank1>>a2[i1][j1].price_usd
            >>a2[i1][j1].price_btc>>a2[i1][j1].a24h_volume_usd>>a2[i1][j1].market_cap_usd>>a2[i1][j1].available_supply
            >>a2[i1][j1].total_supply>>a2[i1][j1].max_supply>>a2[i1][j1].percent_change_1h>>a2[i1][j1].percent_change_24h
            >>a2[i1][j1].percent_change_7d>>a2[i1][j1].last_updated>>a2[i1][j1].koniec;

            plik3>>zm1;
            if(zm1==']'){cout<<"wczytano "<<licz3<<" walut"<<"a2[i1][j1].symbol"<<a2[i1][j1].symbol<<endl;break;}
            else{plik3.seekg(-1,ios_base::cur);}
        }
        a2[i1][licz1-1].kon="]";
        licz1=0;
        licz3=0;
        if(licz3_max<licz3){licz3_max=licz3;}
        plik3>>zm1;
        if(plik3.eof()){cout<<"liczba dni "<<licz_dni<<" "<<endl;break;}
        else{plik3.seekg(-1,ios_base::cur);}
    }

    plik3.close();
}


void wczytanie_ile_walut(struct struktura1 **a2,int *ile_walut_wczytac)
{
    ifstream plik3;
    plik3.open("2.txt", ios::binary);// otwieramy plik do odczytu binarnego
    char* temp6 = new char[40*sizeof(char)]; // tymczasowy bufor na dane
    for(int j=0;j<40;j++)
    {
        temp6[j]='\0';
    }
    char* temp5 = new char[sizeof(char)]; // tymczasowy bufor na dane
    int licz2=0,licz3=0;
    char zm1;
    for(int i1=0;i1<1;i1++)
    {
        plik3>>zm1;
        if(plik3.eof()){cout<<"plik3.eof() "<<endl;break;}
        else{plik3.seekg(-1,ios_base::cur);}
        for(int j1=0;j1<11000;j1++)
        {
            licz2=0;
            licz3++;
            plik3>>a2[0][0].id;
            plik3.read(temp5, sizeof(char));
            for(int i2=0;i2<100;i2++)
            {
            plik3.read(temp5, sizeof(char));
            licz2++;
            if(temp5[0]==13){plik3.seekg(-(licz2-1),ios_base::cur);break;}
            //bo niektore coiny sa zapisane bez spacji np Bitcoin Cash
            }
            for(int j=0;j<40;j++)
            {
                temp6[j]='\0';
            }
            plik3.read(temp6, (licz2-1)*sizeof(char));
            a2[0][0].name=temp6;
            //cout<<licz2<<"  "<<temp6<<endl;system("pause");
            plik3>>a2[0][0].symbol>>a2[0][0].rank1>>a2[0][0].price_usd
            >>a2[0][0].price_btc>>a2[0][0].a24h_volume_usd>>a2[0][0].market_cap_usd>>a2[0][0].available_supply
            >>a2[0][0].total_supply>>a2[0][0].max_supply>>a2[0][0].percent_change_1h>>a2[0][0].percent_change_24h
            >>a2[0][0].percent_change_7d>>a2[0][0].last_updated>>a2[0][0].koniec;

            plik3>>zm1;
            if(zm1==']'){cout<<"void wczytanie_ile_walut wczytano "<<licz3<<" walut"<<endl;break;}
            else{plik3.seekg(-1,ios_base::cur);}
        }
    }
    *ile_walut_wczytac=licz3;
    plik3.close();
}
void wczytanie_ile_dni_w_bazie(struct struktura1 **a2,int *ile_walut_wczytac,int  *ile_dni_pobrac_z_bazy_danych)
{

    ifstream plik3;
    plik3.open("baza.txt", ios::binary);// otwieramy plik do odczytu binarnego

    if( plik3.good() )
    {
        //INFO: plik uda³o siê otworzyæ
    } else
    {
        cout<<endl<<endl<<"nie ma pliku baza.txt utworz go w folderze programu zamknij program"<<endl<<endl;system("pause");
    } //else

    char* temp6 = new char[40*sizeof(char)]; // tymczasowy bufor na dane
    for(int j=0;j<40;j++)
    {
        temp6[j]='\0';
    }
    char* temp5 = new char[sizeof(char)]; // tymczasowy bufor na dane
    int licz2=0,licz3=0,licz3_max=0,licz_dni=0;
    char zm1;
    for(int i1=0;i1<9000;i1++)
    {
        plik3>>zm1;
        if(plik3.eof()){cout<<"liczba dni;;; "<<licz_dni<<" "<<endl;break;}
        else{plik3.seekg(-1,ios_base::cur);}
        licz_dni++;
        for(int j1=0;j1<11000;j1++)
        {
            licz2=0;
            licz3++;
            plik3>>a2[0][0].id;
            plik3.read(temp5, sizeof(char));
            for(int i2=0;i2<100;i2++)
            {
            plik3.read(temp5, sizeof(char));
            licz2++;
            if(temp5[0]==13){plik3.seekg(-(licz2-1),ios_base::cur);break;}
            //bo niektore coiny sa zapisane bez spacji np Bitcoin Cash
            }
            for(int j=0;j<40;j++)
            {
                temp6[j]='\0';
            }
            plik3.read(temp6, (licz2-1)*sizeof(char));
            a2[0][0].name=temp6;
            //cout<<licz2<<"  "<<temp6<<endl;system("pause");
            plik3>>a2[0][0].symbol>>a2[0][0].rank1>>a2[0][0].price_usd
            >>a2[0][0].price_btc>>a2[0][0].a24h_volume_usd>>a2[0][0].market_cap_usd>>a2[0][0].available_supply
            >>a2[0][0].total_supply>>a2[0][0].max_supply>>a2[0][0].percent_change_1h>>a2[0][0].percent_change_24h
            >>a2[0][0].percent_change_7d>>a2[0][0].last_updated>>a2[0][0].koniec;
            plik3>>zm1;
            if(zm1==']'){break;}
            else{plik3.seekg(-1,ios_base::cur);}
        }
        if(licz3_max<=licz3){licz3_max=licz3;}
        plik3>>zm1;
        if(plik3.eof()){cout<<"liczba dni1 "<<licz_dni<<" "<<endl;break;}
        else{plik3.seekg(-1,ios_base::cur);}
        licz3=0;
    }
    cout<<"max ilosc walut w dniu to "<<licz3_max<<" walut"<<endl;
    *ile_walut_wczytac=licz3_max;
    *ile_dni_pobrac_z_bazy_danych=licz_dni;
    plik3.close();
}void dopisz_dzien_do_bazy(struct struktura1 **a1,struct struktura1 **a2,int ile_walut_wczytac1,int ile_walut_wczytac2,int  ile_dni_pobrac_z_bazy_danych2)
{

    ofstream plik3;
    plik3.open("baza.txt");//

    for(int i1=0;i1<1;i1++)
    {
        for(int j1=0;j1<ile_walut_wczytac1;j1++)
        {
            plik3<<a1[i1][j1].id<<endl;
            plik3<<a1[i1][j1].name<<endl;
            plik3<<a1[i1][j1].symbol<<endl;
            plik3<<a1[i1][j1].rank1<<endl;
            plik3<<a1[i1][j1].price_usd<<endl;
            plik3<<a1[i1][j1].price_btc<<endl;
            plik3<<a1[i1][j1].a24h_volume_usd<<endl;
            plik3<<a1[i1][j1].market_cap_usd<<endl;
            plik3<<a1[i1][j1].available_supply<<endl;
            plik3<<a1[i1][j1].total_supply<<endl;
            plik3<<a1[i1][j1].max_supply<<endl;
            plik3<<a1[i1][j1].percent_change_1h<<endl;
            plik3<<a1[i1][j1].percent_change_24h<<endl;
            plik3<<a1[i1][j1].percent_change_7d<<endl;
            plik3<<a1[i1][j1].last_updated<<endl;
            plik3<<a1[i1][j1].koniec<<endl;

            if(a1[i1][j1].kon=="]")
            {
                cout<<"a1[i1][j1].kon"<<a1[i1][j1].kon<<endl;
                plik3<<a1[i1][j1].kon<<endl;
                break;
            }
        }
    }
    for(int i1=0;i1<ile_dni_pobrac_z_bazy_danych2;i1++)
    {
        for(int j1=0;j1<ile_walut_wczytac2;j1++)
        {
            plik3<<a2[i1][j1].id<<endl;
            plik3<<a2[i1][j1].name<<endl;
            plik3<<a2[i1][j1].symbol<<endl;
            plik3<<a2[i1][j1].rank1<<endl;
            plik3<<a2[i1][j1].price_usd<<endl;
            plik3<<a2[i1][j1].price_btc<<endl;
            plik3<<a2[i1][j1].a24h_volume_usd<<endl;
            plik3<<a2[i1][j1].market_cap_usd<<endl;
            plik3<<a2[i1][j1].available_supply<<endl;
            plik3<<a2[i1][j1].total_supply<<endl;
            plik3<<a2[i1][j1].max_supply<<endl;
            plik3<<a2[i1][j1].percent_change_1h<<endl;
            plik3<<a2[i1][j1].percent_change_24h<<endl;
            plik3<<a2[i1][j1].percent_change_7d<<endl;
            plik3<<a2[i1][j1].last_updated<<endl;
            plik3<<a2[i1][j1].koniec<<endl;
            if(a2[i1][j1].kon=="]")
            {   cout<<i1<<" a2[i1][j1].kon "<<a2[i1][j1].kon<<endl;
                plik3<<a2[i1][j1].kon<<endl;
                break;
            }
        }
    }

    plik3.close();
}
