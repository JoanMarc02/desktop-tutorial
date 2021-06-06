/**
    Grup 4
            Joan Marc Fuentes Soler
            Kirian Rodriguez Alonso
            Oriol Garcia Moreiras
**/
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <map>
#include <queue>
#include <stack>
#include <vector>
#include <list>
#include <cmath>
#include <time.h>
#include <locale.h>

using namespace std;

//Classe Hora
class Hora{

    int h, m, s; //Hora, minuts i segons

public:

    //Constructor per defecte amb l'hora actual, que d√≥na el sistema, llibreria time.h
    Hora(){
        time_t t; //time_t √©s un tipus definit en la llibreria time.h, defineix una tupla de temps
        time( &t );
        struct tm* info = localtime( &t );
        h = info -> tm_hour;
        m = info -> tm_min;
        s = info -> tm_sec;
    }

    //Constructor amb tres par√†metres enters
    Hora(int h, int m, int s){
        this->h=h;
        this->m=m;
        this->s=s;
    }

    //Constructor amb un par√†metre enter quantitat de segons, ha de ser <= 24x3600=84600
    //Se suposa que segons <= 24x3600=84600 segons d'un dia
    Hora(int secs){
        h=secs/3600;
        m=(secs%3600)/60;
        s=(secs%3600)%60;
    }
    //Constructor amb un par√†metre string en format hh:mm:ss o hh-mm-ss
    Hora(string sh){
        string c1 = sh.substr (0,2);//el string dels car‡cters hh
        h=atoi(c1.c_str()); //atoi Ès del C, stoi Ès del C++, la funciÛ que converteix el string en enter
        string c2 = sh.substr (3,2);//el string dels car‡cters mm
        m=atoi(c2.c_str());
        string c3 = sh.substr (6); //el substring de la 6‡† posiciÛ fins al final
        s=atoi(c3.c_str());
    }

    //Constructor de cÚpia
    Hora(const Hora& hora)
    {
        h = hora.h;
        m = hora.m;
        s= hora.s;
    }

    //M√®todes consultors
    int getHora(){
        return h;
    }
    int getMinuts(){
        return m;
    }
    int getSegons(){
        return s;
    }

    //M√®todes modificadors. Se suposa que h, m i s s√≥n v√†lids
    void setHora (int hh){
        h=hh;
    }
    void setMinuts (int mm){
        m=mm;
    }
    void setSegons (int ss){
        s=ss;
    }

    //Incrementar la data amb una quantitat de segons
    void incrementaHora (int ss){
        int segs = s + ss; //sumem els segons totals resultants
        if (segs > 59) {
            int hh=segs/3600;
            h+=hh;
            int mm =(segs - hh*3600)/60;
            m+=mm;
            if (m > 59)
            {
                h++;
                m-=60;
            }
            s=segs- hh*3600-mm*60;
        }
    }

   // L'operador d'assignaci√≥
    Hora& operator = (const Hora& hora)
    {
        if (this != &hora)
        {
            h = hora.h;
            m = hora.m;
            s= hora.s;
        }
        return (*this);
    }

    //L'operador incrementa l'hora amb una quantitat de segons ss
    friend Hora& operator + (Hora& H, int ss)
    {
        int segs= H.s + ss;
        if (segs > 59) {
            int hh=segs/3600;
            H.h+=hh;
            int mm =(segs - hh*3600)/60;
            H.m+=mm;
            if (H.m > 59)
            {
                H.h++;
                H.m-=60;
            }
            H.s=segs- hh*3600-mm*60;
        }
        return H;
    }

    //L'operador resta l'hora que s'esta construint amb una hora donada H. Se suposa que les dues hores estan dintre del mateix dia
    friend Hora operator - (Hora H1, Hora H2)
    {
        int s1 = H1.getHora()*3600 + H1.getMinuts()*60 + H1.getSegons();
         int s2 = H2.getHora()*3600 + H2.getMinuts()*60 + H2.getSegons();

        int s = abs(s1-s2);

        return Hora(s);
    }

    //Operador < per comparar dues hores
    friend bool operator < (Hora& h1, Hora& h2)
    {
        if ( h1.h < h2.h)
        {
            return true;
        }
        else if (h1.h == h2.h and h1.m < h2.m)
        {
            return true;
        }
        else if ( h1.h == h2.h and h1.m == h2.m and h1.s < h2.s)
        {
            return true;
        }
        return false;
    }

    //Comparar dues hores ==
    friend bool operator == (Hora& h1, Hora& h2)
    {
        return ( h1.h == h2.h and h1.m == h2.m and h1.s == h2.s);
    }

    //Llegir una hora per canal d'entrada
    friend istream& operator >> (istream& is, Hora& H)
    {
        is >> H.h;
        is >> H.m;
        is >> H.s;

        return is;
    }

    //Escriure una data per canal de sortida hh:mm:ss format 24h
    friend ostream& operator << (ostream& os, Hora hora)
    {
        os << "Hora: ";
        if (hora.h < 10){
            os << "0";
        }
        os << hora.h <<":";

        if (hora.m < 10){
            os << "0";
        }
        os<< hora.m <<":";

        if (hora.s < 10){
            os << "0";
        }
        os<< hora.s << endl;

        return os;
    }

};

//Classe Data
class Data{

    int dia, mes, any;

public:

    //Constructor per defecte amb la data actual, que d√≥na el sistema, llibreria time.h
    Data(){
        time_t t; //time_t √©s una tupla de temps (dia, mes any, hora, mins, segs) definit en time.h
        time( &t );
        struct tm* info = localtime( &t );
        dia = info -> tm_mday;
        mes = info -> tm_mon + 1;
        any = 1900+ info -> tm_year; // l'any es comen√ßa a comptar a partir del 1900
    }

    //Constructor amb tres par√†metres enters
    Data(int d, int m, int a){
        dia=d;
        mes=m;
        any=a;
    }

    //Constructor amb un par√†metre enter ddmmaaaa
    Data(int ddmmaaaa){
        dia=ddmmaaaa/1000000;
        mes=(ddmmaaaa/10000)%100;
        any=ddmmaaaa%10000;
    }

    //Constructor amb un par‡metre string en format dd:mm:aaaa o dd-mm-aaaa
    //stoi Ès una funciÛ per converir un string (p.ex "12") en un enter (p.ex. 12)
    //Pels compiladors de C++ 11 o posterior, sinÛ utilitzeu atoi
    Data(string sd){
        string c1 = sd.substr (0,2);//el string dels car‡cters dd
        dia=atoi(c1.c_str()); //Per
        string c2 = sd.substr (3,2);//el string dels car‡cters mm
        mes=atoi(c2.c_str());
        string c3 = sd.substr (6); //el substring de la 6‡† posiciÛ fins al final
        any=atoi(c3.c_str());
    }

    //Constructor de c√≤pia
    Data(const Data& data)
    {
        dia = data.dia;
        mes = data.mes;
        any = data.any;
    }

    //M√®todes consultors
    int getDia(){
        return dia;
    }
    int getMes(){
        return mes;
    }
    int getAny(){
        return any;
    }

    //Comprovar si la data que s'esta construint √©s de trasp√†s
    bool de_traspas(int any) const
    {
        return ((any % 4 == 0 && any % 100 != 0) or any%400 == 0);
    }

    //Consultar dies d'un mes i any donats. M√®tode privat. Nom√©s s'utilitzar√† en la classe
    int dias_mes(int mes, int any) const
    {
            int dies = 31;
            if (mes == 4 or mes == 6 or mes == 9 or mes == 11) {
                dies = 30;
            }
            else if (mes == 2) {
                if (de_traspas(any)) {
                    dies = 29;
                }
                else {
                    dies = 28;
                }
            }
            return dies;
        }

    //Comptar els dies des d'1 de gener fins al mes (incl√≤s) de una data donada
    int compta_dias() const
    {
        int sd = 0; //suma de dies
        for (int i = 1; i<= mes; i++)
        {
            sd = sd + dias_mes(i,any);
        }
        return sd;
    }
    //Diferencia de dies entre dues dates, la data D i la que s'est√† construint
    int dif_dias(const Data& D) // se suposa que les dates s√≥n del mateix any
    {
        //comptem els dies fins el mes (incl√≤s) i restem els dies que sobren del mes
        return ((D.compta_dias()-(dias_mes(D.mes,D.any)-D.dia)) - (compta_dias()-(dias_mes(mes,any)-dia)));
    }

    //M√®todes modificadors. Se suposa que d, m i a s√≥n v√†lids
    void setDia (int d){
        dia=d;
    }
    void setMes (int m){
        mes=m;
    }
    void setAny (int a){
        any=a;
    }

    //Incrementar la data amb una quantitat de dies
    void incrementaData (int dd){
        dia=dia+dd;
        if (dia > dias_mes(mes, any)) {
            dia = dia-dias_mes(mes,any);
            mes++;
            if (mes > 12) {
                mes = 1;
                any++;
            }
        }
    }

    //Operador d'assignaci√≥
    Data& operator = (const Data& data)
    {
        if (this != &data)
        {
            dia = data.dia;
            mes = data.mes;
            any = data.any;
        }
        return (*this);
    }

    //Diferencia de dies entre dues dates, la data D i la que s'est√† construint
    int operator - (const Data& D) // se suposa que les dates s√≥n del mateix any
    {
        //comptem els dies fins el mes (incl√≤s) i restem els dies que sobren del mes
        return ((compta_dias()-(dias_mes(mes,any)-dia)) -(D.compta_dias()-(dias_mes(D.mes,D.any)-D.dia)));
    }

    //Comparar dues dates <
    friend bool operator < (Data& d1, Data& d2)
    {
        return (d1.any*10000+d1.mes*100+d1.dia < d2.any*10000+d2.mes*100+d2.dia);
    }

    //Comparar dues dates ==
    friend bool operator == (Data& d1, Data& d2)
    {
        return (d1.any*10000+d1.mes*100+d1.dia == d2.any*10000+d2.mes*100+d2.dia);
    }

    //Llegir una data per canal d'entrada
    friend istream& operator >> (istream& is, Data& D)
    {
        is >> D.dia;
        is >> D.mes;
        is >> D.any;

        return is;
    }

    //Escriure una data per canal de sortida dd/mm/aaaa
    friend ostream& operator << (ostream& os, Data d)
    {
        os << "Data: ";
        if (d.dia < 10){
            os << "0";
        }
        os << d.dia <<"/";

        if (d.mes < 10){
            os << "0";
        }
        os<< d.mes << "/" << d.any<<endl;

        return os;
    }

};

//La nova classe DataHora
class DataHora{

    Data data;
    Hora hora;

public:

    //Constructor per defecte. Cridar√† els constructors per defecte de Data i Hora, aix√≠ doncs crear√†
    //la Data i Hora actuals
    DataHora(){}

    //Constructor amb 6 par√†metres dd mm aaaa hh mins segs
    //Cridar√† els constructors respectius de Data i Hora
    DataHora(int dd, int mm, int aaaa, int hh, int mins, int segs):data(dd,mm,aaaa),hora(hh,mins,segs){}

    //Cosntructor amb dos par√†metres
    DataHora(Data d,Hora h):data(d),hora(h){}

    //Constructor amb dues cadenes dd-mm-aaaa hh:mins:segs
    DataHora(string sdata, string shora):data(sdata),hora(shora){}

    //Constructor de c√≤pia
    DataHora(const DataHora& dh)
    {
        data = dh.data;
        hora = dh.hora;
    }

    //M√®todes consultors
    Data& getData()
    {
        return data;
    }

    Hora& getHora()
    {
        return hora;
    }

    bool detraspas()
    {
        return data.de_traspas(data.getAny());
    }

    int getDia()
    {
        return data.getDia();
    }

    int getMes(){
        return data.getMes();
    }

    int getAny(){
        return data.getAny();
    }

    int getLHora(){
        return hora.getHora();
    }
    int getMinuts(){
        return hora.getMinuts();
    }
    int getSegons(){
        return hora.getSegons();
    }

    //Aquest m√®tode retorna true si dues DataHora concideixen en la mateixa data
    //Podria ser √∫til si es vol saber si dos esdeveniments diferents han ocorregut el mateix dia
    friend bool mateixaData(DataHora& dh1, DataHora& dh2)
    {
        return dh1.data == dh2.data;
    }

    //Aquest m√®tode retorna true si dues DataHora concideixen en la mateixa hora
    //Podria ser √∫til si es vol saber si dos esdeveniments diferents han ocorregut en la mateixa hora
    friend bool mateixaHora(DataHora& dh1, DataHora& dh2)
    {
        return dh1.hora == dh2.hora;
    }
    //M√®todes modificadors. Se suposa que d, m i a s√≥n v√†lids
    void setDia (int d){
        data.setDia(d);
    }
    void setMes (int m){
        data.setMes(m);
    }
    void setAny (int a){
        data.setAny(a);
    }

    //M√®todes modificadors. Se suposa que h, m i s s√≥n v√†lids
    void setHora (int hh){
        hora.setHora(hh);
    }
    void setMinuts (int mm){
        hora.setMinuts(mm);
    }
    void setSegons (int ss){
        hora.setSegons(ss);
    }

    void incrementaData(int dd)
    {
        data.incrementaData(dd);
    }

    void setDataHoraActual()
    {
        time_t t; //time_t Ès un tipus definit en la llibreria time.h, defineix una tupla de temps
        time( &t );
        struct tm* info = localtime( &t );
        hora.setHora(info -> tm_hour);
        hora.setMinuts(info -> tm_min);
        hora.setSegons(info -> tm_sec);
        data.setDia(info -> tm_mday);
        data.setMes(info -> tm_mon + 1);
        data.setAny(1900+ info -> tm_year); // l'any es comen√ßa a comptar a partir del 1900
    }

    //Reset data a 01/01/1900
    void resetDataHora()
    {
        data.setDia(1);
        data.setMes(1);
        data.setAny(1900);
        hora.setHora(0);
        hora.setMinuts(0);
        hora.setSegons(0);
    }
    //Operadors

    //Operador + per sumar una quantitat de segons.
    //Pot provocar un canvi de la hora i data en cadena
    friend DataHora& operator += (DataHora& dh, int ss)
    {
        int nousSegs = dh.getSegons() + ss; //segons totals dESAr√©s d'afegir

        if (nousSegs > 59)
        {
            int nousMins = nousSegs/60;//minuts addicionals
            nousSegs = nousSegs - nousMins*60;
            dh.setSegons(nousSegs); //segons resultants finals

            nousMins = nousMins + dh.getMinuts(); //nous minuts sumant els existents
            if (nousMins > 59)
            {
                int novesH = nousMins/60;
                nousMins = nousMins - novesH*60;
                dh.setMinuts(nousMins);//minuts resultants finals

                novesH = novesH + dh.getLHora();
                if (novesH > 24)
                {
                    int nousD = novesH/24;
                    novesH = novesH - nousD*24;
                    dh.setHora(novesH); //hores resultants finals

                    dh.incrementaData(nousD);
                }
                else
                {
                    dh.setHora(novesH);
                }
            }
            else
            {
                dh.setMinuts(nousMins);
            }
        }
        else
        {
            dh.setSegons(nousSegs);
        }

        return dh;
    }

    //Operador d'assignaci√≥
    DataHora& operator = (const DataHora& dh)
    {
        if (this != &dh)
        {
            data = dh.data;
            hora = dh.hora;
        }
        return (*this);
    }

    //Comparar dues dates <
    friend bool operator < (DataHora& dh1, DataHora& dh2)
    {
        return ((dh1.data < dh2.data) or ((dh1.data == dh2.data) and (dh1.hora < dh2.hora)));
    }

    //Comparar dues dates ==
    friend bool operator == (DataHora& dh1, DataHora& dh2)
    {
        return ((dh1.data == dh2.data) and (dh1.hora == dh2.hora));
    }

    //Llegir una data per canal d'entrada
    friend istream& operator >> (istream& is, DataHora& dh)
    {
        is >> dh.data;
        is >> dh.hora;

        return is;
    }

    //Escriure una data per canal de sortida dd/mm/aaaa
    friend ostream& operator << (ostream& os, DataHora dh)
    {
        os << dh.data << dh.hora;

        return os;
    }

};

//Classe Persona
class Persona{

    //-------------->Dades<--------------//
    protected:
    string Nom,Cognom,DNI;
    int Edat;
    char Sexe;
public:
    //--------------->API<---------------//

    //----------->Constructors<----------//

    //Constructor per defecte
    Persona(){}
    //Constructor amb parametres
    Persona(string pNom,string pCognom,string pDNI,int pEdat,char pSexe){

            Nom = pNom;
            Cognom = pCognom;
            DNI = pDNI;
            Edat = pEdat;
            Sexe = pSexe;
    }
    //Constructor amb parametres des d'un fitxer
    Persona(ifstream& fpersona){

        fpersona >> Nom;
        fpersona >> Cognom;
        fpersona >> DNI;
        fpersona >> Edat;
        fpersona >> Sexe;
    }
    //Constructor de copia
    Persona(const Persona& P){

            Nom = P.Nom;
            Cognom = P.Cognom;
            DNI = P.DNI;
            Edat = P.Edat;
            Sexe = P.Sexe;
    }
    //MËtodes consultors getX
    string getNom()const{

        return Nom;
    }
    string getCognom() const{

        return Cognom;
    }
    string getDNI()const{

        return DNI;
    }
    int getEdat() const{

        return Edat;
    }
    char getSexe() const{

        return Sexe;
    }
    //MËtodes modificadors setX
     void setNom(string pNom){

        pNom = Nom;
    }
    void  setCognom(string pCognom) {

        pCognom = Cognom;
    }
    void  setDNI(string pDNI){

        pDNI = DNI;
    }
    void  setEdat(int pEdat) {

        pEdat = Edat;
    }
    void  setSexe(char pSexe) {

        pSexe = Sexe;
    }
    //Operador  d'asignaciÛ
    Persona& operator = (const Persona& P){

        if(this !=&P){

            Nom = P.Nom;
            Cognom = P.Cognom;
            DNI = P.DNI;
            Edat = P.Edat;
            Sexe = P.Sexe;

        }
        return (*this);
    }
    //Operadors relacionals

    //Operador de ==
    friend bool operator == (Persona& P1 , Persona&  P2){

        return((P1.Nom == P2.Nom) and (P1.Cognom == P2.Cognom) and (P1.DNI == P2.DNI) and (P1.Edat == P2.Edat) and (P1.Sexe == P2.Sexe));

    }
    friend bool operator < (Persona& P1 , Persona&  P2){

        return(P1.Edat < P2.Edat);
    }
    friend bool operator > (Persona& P1 , Persona&  P2){

        return(P1.Edat > P2.Edat);
    }
    // Operadors d'extracciÛ >>

    friend istream& operator >> (istream& is, Persona &P){

        is >> P.Nom;
        is >> P.Cognom;
        is >> P.DNI;
        is >> P.Edat;
        is >> P.Sexe;

        return is;
    }
    // Operadors d'inserciÛ <<

    friend ostream& operator << (ostream& os, Persona& P){

        os << "Nom: "<< P.Nom << endl;
        os << "Cognom: "<< P.Cognom << endl;
        os << "DNI: " << P.DNI << endl;
        os << "Edat: " << P.Edat << endl;
        os << "Sexe: " << P.Sexe << endl;

        return os;
    }

};

//Classe Alumnes
class Alumne : public Persona{

    //-------------->Dades<--------------//
    string Aula,DNIA;
    int Curs;
    DataHora HALE; //DataHora del Alumne que entra
    DataHora HALS; //DataHora del Alumne que entra
    double Temp;
public:
    //--------------->API<---------------//

    //----------->Constructors<----------//

    //Constructor per defecte
    Alumne(){}
    //Constructor amb parametres
    Alumne(Persona P,string pDNIA,string pAula,int pCurs,DataHora pHALE,DataHora pHALS, double pTemp):Persona(P){

        DNIA = pDNIA;
        Aula = pAula;
        Curs = pCurs;
        HALE = pHALE;
        HALS = pHALS;
        Temp = pTemp;

    }
    //Constructor amb parametres des d'un fitxer
    Alumne(Persona P,ifstream& falumne):Persona(P){

        falumne >> DNIA;
        falumne >> Aula;
        falumne >> Curs;
        falumne >> HALE;
        falumne >> HALS;
        falumne >> Temp;

    }
    //Constructor de copia
    Alumne(const Alumne& AL):Persona(AL){

        DNIA = AL.DNIA;
        Aula = AL.Aula;
        Curs = AL.Curs;
        HALE = AL.HALE;
        HALS = AL.HALS;
        Temp = AL.Temp;

    }
    //MËtodes consultors getX
    string getDNIA()const{

        return DNIA;
    }
    string getAula()const{

        return Aula;
    }
    int getCurs() const{

        return Curs;
    }
    DataHora getHoraALE()const{

        return HALE;
    }
    DataHora getHoraALS()const{

        return HALS;
    }
    double getTemp()const{

        return Temp;
    }
    //MËtodes modificadors setX
    void setDNIA(string pDNIA){

        pDNIA = DNIA;
    }
    void setAula(string pAula){

        pAula = Aula;
    }
    void setCurs(int pCurs){

        pCurs = Curs;
    }
    void setHoraALE(DataHora pHALE){

        pHALE = HALE;
    }
    void setHoraALS(DataHora pHALS){

        pHALS = HALS;
    }
    void setTemp(double pTemp){

        pTemp = Temp;
    }
    //Operador  d'asignaciÛ
    Alumne& operator = (const Alumne& AL){

        if(this !=&AL){

        Persona::operator = (AL);
        DNIA = AL.DNIA;
        Aula = AL.Aula;
        Curs = AL.Curs;
        HALE = AL.HALE;
        HALS = AL.HALS;
        Temp = AL.Temp;

        }
        return (*this);
    }
    //Operadors relacionals
    friend bool operator == (Alumne& AL1 , Alumne&  AL2){

        return((AL1.DNIA == AL2.DNIA) and (AL1.Aula == AL2.Aula)and (AL1.Curs == AL2.Curs) and (AL1.HALE == AL2.HALE)and (AL1.HALS == AL2.HALS) and (AL1.Temp = AL2.Temp));

    }
    friend bool operator < (Alumne& AL1 , Alumne&  AL2){return true;}
    friend bool operator > (Alumne& AL1 , Alumne&  AL2){return true;}

    // Operadors d'extracciÛ >>

    friend istream& operator >> (istream& is, Alumne &AL){

        Persona P; // La part Persona de A
        //is >> P;

        string Aula,DNIA;
        int Curs;
        DataHora HALE;
        DataHora HALS;
        double Temp;

        is >> DNIA;
        is >> Aula;
        is >> Curs;
        is >> HALE;
        is >> HALS;
        is >> Temp;

        Alumne PAL (P,DNIA,Aula,Curs,HALE,HALS,Temp);
        AL = PAL;

        return is;
    }
    // Operadors d'inserciÛ <<

    friend ostream& operator << (ostream& os, Alumne& AL){

        Persona P = (Persona) AL; //Extrau la part de la persona de A
        os << "Fitxa de l'Alumne: " << endl;
        //os << P;
        os << "------------------ " << endl;
        os << "DNI: " << AL.DNIA << endl;
        os << "Aula: " << AL.Aula << endl;
        os << "Curs: " << AL.Curs << endl;
        os << "Entrada: " << endl;
        os << AL.HALE << endl;
        os << "Sortida: " << endl;
        os << AL.HALS;
        os << "Temperatura: " << AL.Temp << endl;
        os << "------------------" << endl;

        return os;
    }

};

//Fem un petit struct per representar les dades d'entrada i sortida d'un alumne en una aula en una hora d'entrada i sortida donades (se suposa al llarg del dia)
struct EntSort{
   DataHora DHE; //DataHora de Entrada
   DataHora DHS; //DataHora de Sortida
   string DNI; //Una sola entrada/salida per un sol alumne! Mireu la classe Aula per la mem dinàmica

    EntSort(){}

    EntSort(string pDNI, DataHora pDHE, DataHora pDHS){
        DNI = pDNI;
        DHE = pDHE;
        DHS = pDHS;
    }

    EntSort(const EntSort& ES){
        DNI = ES.DNI;
        DHE = ES.DHE;
        DHS = ES.DHS;
    }

    EntSort& operator = (const EntSort& ES){
        if (this != &ES){
            DHE = ES.DHE;
            DHS = ES.DHS;
            DNI = ES.DNI;
        }
        return (*this);
    }

    friend ostream& operator << (ostream& os, const EntSort& ES){
        cout << "E/S:" << endl;
        cout << "----------------------" << endl;
        cout << "HE: " << ES.DHE; //DataHora d'Entrada
        cout << "HS: " << ES.DHS; //DataHora d'Entrada
        cout << "DNI: " << ES.DNI << endl;
        cout << "----------------------" << endl;

        return os;
    }
};

//Classe Aula
class Aula {
//-------------->Dades<--------------//

    int CMAX; //Capacitat Maxima d'alumnes en una aula
    DataHora DHE; //DataHora de Entrada
    DataHora DHS; //DataHora de Sortida
    string nomAula;

    //Mem. dinàmica
    EntSort* ESs; // Quantitat indeterminada d'entrades i sortides d'alumnes a l'aula
    int nES; //dimensiÛ de la taula


     //Resta entre datahora de sortida i datahora d'entrada HAUS - HAUE
    void dias_horas_minuts(DataHora HAUS, DataHora HAUE, int& DD, int& HH, int& MM)
    {
        //Dates diferents
        if (!(HAUS.getData() == HAUE.getData()))
        {
            DD = HAUS.getData() - HAUE.getData() - 1;

            Hora Mitjanit1(0,0,0);
            Hora Mitjanit2(24,0,0);

            Hora hores1 = HAUS.getHora() - Mitjanit1;
            Hora hores2 = Mitjanit2 - HAUE.getHora();

            int Hor = hores1.getHora() + hores2.getHora();
            convertir(Hor,DD,HH);

            MM =  hores1.getMinuts() + hores2.getMinuts();
        }
        else
        {
            DD = 0;
            Hora hdif = HAUS.getHora() - HAUE.getHora();
            HH = hdif.getHora();
            MM = hdif.getMinuts();
        }
    }
    //Convertir una quantitat de minuts en dies, hores, minuts
    void DiesHoresMins(int minuts, int& Dies, int& Hores, int& Mins)
    {
        Dies  = minuts / 1440;
        Hores = (minuts % 1440) / 60;
        Mins  = (minuts % 1440) % 60;
    }

    void convertir(int Hor, int& DD, int& HH){
        DD = Hor / 24;
        HH = Hor % 24;
    }

public:
    //--------------->API<---------------//

    //----------->Constructors<----------//

    //Constructor per defecte
    Aula(){}

    //Amb par‡metres, dades llegides des d'un fitxer
    Aula(ifstream& faula){

        faula >> CMAX; //llegim capacitat màxima

        faula >> nES; //llegim el nombre d'entrades i sortides a l'aula

        //Adquirim memòria
        ESs = new EntSort[nES];

        string nomAula, DNIA;
        int dde, mme, aaaae;
        int hhe, mine, sece;
        int dds, mms, aaaas;
        int hhs, mins, secs;
        int i = 0; //pos en la taula dinàmica
        while (faula >> nomAula >> DNIA >> dde >> mme >> aaaae >> hhe >> mine >> sece >> dds >> mms  >> aaaas >> hhs >> mins >> secs)
        {
            DataHora DHENT(dde, mme, aaaae, hhe, mine, sece);
            DataHora DHSORT(dds, mms, aaaas,hhs,mins,secs);

            EntSort EnSr(DNIA,DHENT,DHSORT);

            ESs[i] = EnSr;
            i++;
        }
    }
    //Constructor amb parametres
    //HO PODEU ARREGLAR EN BASE DE L'ANTERIOR CONSTR.
    Aula(int pCMAX, string pnomAula,ifstream& faula){

        CMAX = pCMAX;
        nomAula = pnomAula;
        //Agafem com data i hora d'entrada la data i hora actuals
        DHE.setDataHoraActual();
        DHS.resetDataHora(); //perquË no tingui la data hora actuals
        //Crear la taula de valors, llegint del fitxer
        faula >> nES;
        //Es crea la taula din‡micament, adquireix memÚria
        ESs = new EntSort [nES];
        for(int i=0;i<nES;i++){

            faula >> ESs[i].DNI;
            faula >> ESs[i].DHE;
            faula >> ESs[i].DHS;
        }
    }

    //DESTRUCTOR
    ~Aula()
    {
        delete [] ESs;
    }

    //Constructor de copia
    Aula(const Aula& AU){

        CMAX = AU.CMAX;
        nomAula = AU.nomAula;
        nES = AU.nES;

        ESs = new EntSort [nES];
        //Copiem continguts
        for (int i = 0; i < nES; i++){
            ESs[i] = AU.ESs[i];
        }
    }


     //S'HAN DE REFER JA QUE UNA AULA NO TÉ UNA HORA D'ENTRADA I SORTIDA; TÉ VÀRIES HORES D'ENTRADES I SORTIDES, PER CADA ALUMNE
    //MËtodes consultors getX

    DataHora getDHE()const{

        return DHE;
    }
    DataHora getDHS()const{

        return DHS;
    }

    int getnDNIs(){

        return nES;
    }

    vector<string> getDNIS() const{

        vector<string> DNIs;
        for (int i = 0; i<nES; i++)
        {
            DNIs.push_back(ESs[i].DNI);
        }
             return DNIs;
    }

    string getnomAula()const{

        return nomAula;
    }
    int getCMAX()const{

        return CMAX;
    }
    //MËtodes per modificar valors

    void setnomAula(string pnomAula){

        nomAula = pnomAula;
    }

    void setCMAX(int pCMAX){

        CMAX = pCMAX;
    }

    void setESs(EntSort* pESs){

           ESs = pESs;
    }
    //Operador  d'asignaciÛ
    Aula& operator = (const Aula& AU){ //assigna l'aula a l'objecte

        if(this != &AU){ //faig assignaciÛ
            //copiar informaciÛ
            CMAX = AU.CMAX;
            nomAula = AU.nomAula;
            nES = AU.nES;
            //Cal destruir la taula i crear-la de nou...
            delete [] ESs;
            ESs = new EntSort [nES];
            for (int i = 0; i < nES; i++){
                ESs[i] = AU.ESs[i];
            }
        }
        return (*this);
    }
    //Operadors relacionals
    bool operator == (Aula& AU){
        //comparem component-wise, camp a camp
        return (nomAula == AU.nomAula);

    }
    //Comparem pel nombre d'alumnes que han entrat i sortit
    friend bool operator < (Aula& AU1 , Aula&  AU2)
    {
        return AU1.getnDNIs() < AU2.getnDNIs();
    }


    // Operadors d'extracciÛ >>

    friend istream& operator >> (istream& is, Aula &AU){

        is >> AU.CMAX; //llegim capacitat màxima

        is >> AU.nES; //llegim el nombre d'entrades i sortides a l'aula


        //Adquirim memòria
        EntSort* ESsTEMP = new EntSort[AU.nES];

        string nomAula, DNIA;
        int dde, mme, aaaae;
        int hhe, mine, sece;
        int dds, mms, aaaas;
        int hhs, mins, secs;
        int i = 0; //pos en la taula dinàmica
        while (is >> nomAula >> DNIA >> dde >> mme >> aaaae >> hhe >> mine >> sece >> dds >> mms  >> aaaas >> hhs >> mins >> secs)
        {
            DataHora DHENT(dde, mme, aaaae, hhe, mine, sece);
            DataHora DHSORT(dds, mms, aaaas,hhs,mins,secs);

            EntSort EnSr(DNIA,DHENT,DHSORT);

            ESsTEMP[i] = EnSr;
            i++;
        }
        AU.setESs(ESsTEMP);

    return is;

    }
    // Operadors d'inserciÛ <<

    friend ostream& operator << (ostream& os, Aula &AU){


        os << "Fitxa de la Aula: " << endl;
        os << "------------------" << endl;
        os << "Capacitat m‡xima: " << AU.CMAX << endl;
        os << "Nombre de DNIs: " << AU.nES << endl;
        os << "Nom Aula: " << AU.nomAula <<endl;
        if (AU.nES>0){
            for(int i=0; i< AU.nES;i++){
                //Escrivim entrada/sortida i-èssima
             os << AU.ESs[i] << endl;
            }
        os << endl;
        }
        os << "------------------" << endl;

        return os;
    }
};

//Classe Edifici(Llocs)
class Edifici {

    DataHora HEE; //DataHora del horario de entrada
    DataHora HES; //DataHora del horario de entrada
    string DNIE;
    double Temp;

public:
    //Constructor per defecte
    Edifici(){}
    //Constructor amb parametres
    Edifici(string pDNIE, DataHora pHEE,DataHora pHES,double pTemp){

        HEE = pHEE;
        HES = pHES;
        DNIE = pDNIE;
        Temp = pTemp;
    }
    Edifici(ifstream& fedifici){

        fedifici >> DNIE;
        fedifici >> HEE;
        fedifici >> HES;
        fedifici >> Temp;
    }
    //Constructor de copia
    Edifici(const Edifici& E){

        DNIE = E.DNIE;
        HEE = E.HEE;
        HES = E.HES;
        Temp = E.Temp;
    }
    //MËtodes consultors getX
    DataHora getHoraE()const{

        return HEE;
    }
    DataHora getHoraS()const{

        return HES;
    }
    string getDNIE()const{

        return DNIE;
    }
    double getTemp()const{

        return Temp;
    }
    //MËtodes modificadors setX
     void setHoraE(DataHora pHEE){

        pHEE = HEE;
    }
    void setHoraS(DataHora pHES){

        pHES  = HES;
    }
    void setDNIE(string pDNIE){

        pDNIE = DNIE;
    }
    void setTemp(double pTemp){

        pTemp = Temp;
    }
    // MetÚdes

    void PosibleCOVID(){
     list <Persona> Infectats,Sans;
        Persona PC,SC;

        if(getTemp()>=37.5){
            Infectats.push_back(PC);
            cout<<"POSSIBLE POSITIU!"<<endl<<"AccÈs denegat"<<endl;
        }
        else{
            Sans.push_back(SC);
            cout<<"POT ENTRAR EN EL Edifici!"<<endl<<"AccÈs aceptat"<<endl;
        }
    }
    //Operador  d'asignaciÛ
    Edifici& operator = (const Edifici& E){

        if(this != &E){

        DNIE = E.DNIE;
        HEE = E.HEE;
        HES = E.HES;
        Temp = E.Temp;

        }
      return(*this);
    }

    //Operadors relacionals
    friend bool operator == (Edifici& E1, Edifici& E2){

        return((E1.DNIE == E2.DNIE) and (E1.HEE == E2.HEE) and (E1.HES == E2.HES) and (E1.Temp = E2.Temp));
    }

    friend bool operator < (Edifici& E1, Edifici& E2){return true;}
    friend bool operator > (Edifici& E1, Edifici& E2){return true;}

    // Operadors d'extracciÛ >>
    friend istream& operator >> (istream& is, Edifici& E){

        is >> E.DNIE;
        is >> E.HEE;
        is >> E.HES;
        is >> E.Temp;

        return is;
    }

    friend ostream& operator << (ostream& os, Edifici& E){

        os << "Fitxa del Edifici: " << endl;
        os << "-------------------" << endl;
        os << "DNI: " << E.DNIE << endl;
        os << E.HEE << endl;
        os << E.HES << endl;
        os << "Temperatura: " << E.Temp << endl;
        os << "------------------" << endl;

        return os;
    }

};

//Classe Professor
class Professor : public Persona{

//-------------->Dades<--------------//
    DataHora HPE,HPS;
    int Curs;
    string Aula,Materia,DNIPP;

public:
    //--------------->API<---------------//

    //----------->Constructors<----------//

    //Constructor per defecte
    Professor(){}
    //Constructor amb parametres
    Professor(Persona P, string pDNIPP,string pAula,string pMateria,DataHora pHPE, DataHora pHPS):Persona(P){

        DNIPP = pDNIPP;
        Aula = pAula;
        Materia = pMateria;
        HPE = pHPE;
        HPS = pHPS;


    }
    //Constructor amb parametres des d'un fitxer
    Professor(Persona P,ifstream& fprofessors):Persona(P){

        fprofessors >> DNIPP;
        fprofessors >> Aula;
        fprofessors >> Materia;
        fprofessors >> HPE;
        fprofessors >> HPS;

    }
    //Constructor de copia
    Professor(const Professor& PP):Persona(PP){

        DNIPP = PP.DNIPP;
        Aula = PP.Aula;
        Materia = PP.Materia;
        HPE = PP.HPE;
        HPS = PP.HPS;
    }
    //Mètodes consultors getX
    string getDNIPP()const {

        return DNIPP;
    }
    string getAula()const{

        return Aula;
    }
    string getMateria()const{

        return Materia;
    }
    DataHora getHoraHPE()const{

        return HPE;
    }
    DataHora getHoraHPS()const{

        return HPS;
    }
    //MËtodes modificadors setX
    void setDNIPP (string pDNIPP) {

        pDNIPP = DNIPP;
    }
    void setAula(string pAula){

        pAula = Aula;
    }
    void setMateria(string pMateria){

        pMateria = Materia;
    }
    void setHoraHPE(DataHora pHPE){

        pHPE = HPE;
    }
    void setHoraHPS(DataHora pHPS){

        pHPS = HPS;
    }
    //Operador  d'asignació
    Professor& operator = (const Professor& PP){

        if(this !=&PP){

        Persona::operator = (PP);
        DNIPP = PP.DNIPP;
        Aula = PP.Aula;
        Materia = PP.Materia;
        HPE = PP.HPE;
        HPS = PP.HPS;

        }
        return (*this);
    }
    //Operadors relacionals
    friend bool operator == (Professor& PP1 , Professor&  PP2){

        return((PP1.DNIPP == PP2.DNIPP) and (PP1.Aula == PP2.Aula) and (PP1.Materia == PP2.Materia)and (PP1.HPE == PP2.HPE) and (PP1.HPS == PP2.HPS));

    }
    friend bool operator < (Professor& PP1 , Professor&  PP2){return true;}
    friend bool operator > (Professor& PP1 , Professor&  PP2){return true;}

    // Operadors d'extracciÛ >>

    friend istream& operator >> (istream& is, Professor& PP){

        Persona P; // La part Persona de A
        //is >> P;
        DataHora HPE;
        DataHora HPS;
        string Aula,Materia,DNIPP;

        is >> DNIPP;
        is >> Aula;
        is >> Materia;
        is >> HPE;
        is >> HPS;

        Professor PR (P,DNIPP,Aula,Materia,HPE,HPS);
        PP = PR;

        return is;
    }
    // Operadors d'inserció <<

    friend ostream& operator << (ostream& os, Professor& PP){

        Persona P = (Persona) PP; //Extrau la part de la persona de A
        os << "Fitxa del Professor/a: " << endl;
        os << "------------------" << endl;
        //os << P;
        os << "DNI: " << PP.DNIPP << endl;
        os << "Aula: " << PP.Aula << endl;
        os << "Materia: " << PP.Materia << endl;
        os << "Hora d'entrada: " << PP.HPE << endl;
        os << "Hora de sortida: " << PP.HPS << endl;
        os << "------------------" << endl;

        return os;
    }
};

//Classe PersonalExtern
class PersonalExtern : public Persona{
//-------------->Dades<--------------//
    DataHora HPE; //DataHora de PE Entrada
    DataHora HPS; //DataHora de PE Sortida
    string Aula;
    string Ocupacio;
    string DNIPE;
public:
    //--------------->API<---------------//

    //----------->Constructors<----------//

    //Constructor per defecte
    PersonalExtern(){}
    //Constructor amb parametres

    PersonalExtern(Persona P,string pDNIPE,string pAula,string pOcupacio,DataHora pHPE, DataHora pHPS):Persona(P){

        HPS = pHPS;
        HPE = pHPE;
        Aula = pAula;
        Ocupacio = pOcupacio;
        DNIPE = pDNIPE;

    }
    //Constructor amb parametres des d'un fitxer
    PersonalExtern(Persona P,ifstream& fpersonalextern):Persona(P){

        fpersonalextern >> DNIPE;
        fpersonalextern >> Aula;
        fpersonalextern >> Ocupacio;
        fpersonalextern >> HPE;
        fpersonalextern >> HPS;
    }
    //Constructor de copia
    PersonalExtern(const PersonalExtern& PE):Persona(PE){

        DNIPE = PE.DNIPE;
        Aula = PE.Aula;
        Ocupacio = PE.Ocupacio;
        HPE = PE.HPE;
        HPS = PE.HPS;

    }
    //MËtodes consultors getX
    DataHora getHPE()const{

        return HPE;
    }
    DataHora getHPS()const{

        return HPS;
    }
    string getAula()const{

        return Aula;
    }
    string getOcupacio()const{

        return Ocupacio;
    }
    string getDNIPE()const{

        return DNIPE;
    }
    //MËtodes modificadors setX
    void setHPE(DataHora pHPE){

        pHPE = HPE;
    }
    void setHPS(DataHora pHPS){

        pHPS = HPS;
    }
    void setAula(string pAula){

        pAula = Aula;
    }
    void setOcupacio(string pOcupacio){

        pOcupacio = Ocupacio;
    }
    void setDNIPE(string pDNIPE){

        pDNIPE = DNIPE;
    }
    //Operador  d'asignaciÛ
    PersonalExtern& operator = (const PersonalExtern& PE){

        if(this !=&PE){

        Persona::operator = (PE);
        DNIPE = PE.DNIPE;
        Aula = PE.Aula;
        Ocupacio = PE.Ocupacio;
        HPE = PE.HPE;
        HPS = PE.HPS;

        }
        return (*this);
    }
    //Operadors relacionals
    friend bool operator == (PersonalExtern& PE1 , PersonalExtern&  PE2){

        return((PE1.DNIPE==PE2.DNIPE) and (PE1.Aula == PE2.Aula) and (PE1.Ocupacio == PE2.Ocupacio) and (PE1.HPE==PE2.HPE)and (PE1.HPS==PE2.HPS));// and (PE1.h==PE2.h) and(PE1.m==PE2.m) and (PE1.s==PE2.s));

    }
    friend bool operator < (PersonalExtern& PE1 , PersonalExtern&  PE2){return true;}
    friend bool operator > (PersonalExtern& PE1 , PersonalExtern&  PE2){return true;}

    // Operadors d'extracciÛ >>

    friend istream& operator >> (istream& is, PersonalExtern &PE){

        Persona P; // La part Perosna de A
        //is >> P;
        DataHora HPE;
        DataHora HPS;
        string Aula,Ocupacio,DNIPE;
        is >> DNIPE;
        is >> Aula;
        is >> Ocupacio;
        is >> HPE;
        is >> HPS;
        PersonalExtern PR (P,DNIPE,Aula,Ocupacio,HPE,HPS);
        PE = PR;

        return is;
    }
    // Operadors d'inserciÛ <<

    friend ostream& operator << (ostream& os, PersonalExtern& PE){

        Persona P = (Persona) PE; //Extrau la part de la persona de A
        os << "Fitxa de la Personal Extern: " << endl;
        os << "------------------" << endl;
        //os << P;
        os << "DNI: " << PE.DNIPE << endl;
        os << "Aula: " << PE.Aula << endl;
        os << "OcupaciÛ/C‡rrec: " << PE.Ocupacio << endl << endl ;
        os << "Entrada: " <<endl;
        os << PE.HPE;
        os << endl ;
        os << "Sortida: " <<endl;
        os << PE.HPS;
        os << "------------------" << endl;

        return os;
    }
};

//Menu Persona
void MenuPersona (int& opP){
    setlocale(LC_ALL,"Catalan");
    cout <<" ------------------------------------------" << endl;
    cout <<" Escull una opcio. " << endl;
    cout << "1. Desplegar la llista amb la informacio de cada persona que entra a l'edifici " << endl;
    cout << "2. Afegir positiu al registre " << endl;
    cout << "3. Eliminar positiu al registre" << endl;
    cout << "4. Coneixer la quantitat maxima de persones que hi ha dins de l'edifici " << endl;
    cout << "5. Acabar" << endl;
    cout <<" ------------------------------------------" << endl;
    cin >> opP;
    while(opP < 1 or opP > 5){
        cout << "Opcio incorrecte. Torna a escollir una opcio:" << endl;
        cin >> opP;}
}

//Menu Professor
void MenuProfessor(int& opS){

    setlocale(LC_ALL,"Catalan");
    cout <<" ------------------------------------------" << endl;
    cout <<" Escull una opcio. " << endl;
    cout << "1. Desplegar la llista del professors dins l'edifici " << endl;
    cout << "2. Coneixer la quantitat de professors assignats en cada aula " << endl;
    cout << "3. Coneixer la quantitat de professors dins d'edifici" << endl;
    cout << "4. Acabar" << endl;
    cout <<" ------------------------------------------" << endl;
    cin >> opS;
    while(opS< 1 or opS > 4){
       cout << "Opcio incorrecte. Torna a escollir una opcio:" << endl;
        cin >> opS;
    }
}

//Menu Alumne
void MenuAlumne(int& opA){

    setlocale(LC_ALL,"Catalan");
    cout <<" ------------------------------------------" << endl;
    cout <<" Escull una opcio. " << endl;
    cout << "1. Desplagar la lista d'alumnes que han entrat a l'edifici " << endl;
    cout << "2. Afegir positiu al registre" << endl;
    cout << "3. Eliminar positiu al registre " << endl;
    cout << "4. Coneixer la quantitat màxima de persones que hi ha dins de l'edifici " << endl;
    cout << "5. Buscar a l'alumne mitjaçant el DNI" << endl;
    cout << "6. Acabar" << endl;
    cout <<" ------------------------------------------" << endl;
    cin >> opA;
    while(opA < 1 or opA > 6){
        cout << "Opcio incorrecte. Torna a escollir una opcio:" << endl;
        cin >> opA;
    }
}

//Menu Edifici
void MenuEdifici(int& opE){

    setlocale(LC_ALL,"Catalan");
    cout <<" ------------------------------------------" << endl;
    cout <<" Escull una opció. " << endl;
    cout << "1. Desplegar la llista de possibles contagiats " << endl;
    cout << "2. Desplagar la llista dels no contagiats " << endl;
    cout << "3. Entrar persona a l'edifici " << endl;
    cout << "4. Sortir persona de l'edifici" << endl;
    cout << "5. Confinar Aula de l'edifici" << endl;
    cout << "6. Acabar" << endl;
    cout <<" ------------------------------------------" << endl;
    cin >> opE;
    while(opE < 1 or opE > 6){
        cout << "Opcio incorrecte. Torna a escollir una opcio:" << endl;
        cin >> opE;
    }
}

//Menu Aula
void MenuAula(int& opAU){

    setlocale(LC_ALL,"Catalan");
    cout <<" ------------------------------------------" << endl;
    cout <<" Escull una opció. " << endl;
    cout << "1. " << endl;
    cout << "2. " << endl;
    cout << "3. " << endl;
    cout << "4. " << endl;
    cout << "5. " << endl;
    cout << "6. Acabar" << endl;
    cout <<" ------------------------------------------" << endl;
    cin >> opAU;
    while(opAU < 1 or opAU > 6){
        cout << "Opcio incorrecte. Torna a escollir una opcio:" << endl;
        cin >> opAU;
    }
}

//Menu Personal Extern
void MenuPersonaExtern(int& opPE){

    setlocale(LC_ALL,"Catalan");
    cout <<" ------------------------------------------" << endl;
    cout <<" Escull una opcio. " << endl;
    cout << "1. Desplegar la llista del personal extern dins l'edifici " << endl;
    cout << "2. Coneixer la quantitat de personal extern assignats en cada aula " << endl;
    cout << "3. Coneixer la quantitat de personal extern dins d'edifici" << endl;
    cout << "4. Acabar" << endl;
    cout <<" ------------------------------------------" << endl;
    cin >> opPE;
    while(opPE < 1 or opPE > 4){
        cout << "Opcio incorrecte. Torna a escollir una opcio:" << endl;
        cin >> opPE;
    }

}

//Menu Principal
void MenuPrincipal(int &option){

        setlocale(LC_ALL,"Catalan");
        cout <<" --------------------------------------------------------------------------------------------" << endl;
        cout << "Benvingut al Menu Principal del programa sobre la Gestio d'Aules Covid-19 d'un Centre Docent "<<endl;
        cout << endl << endl;
        cout << "MENU D'OPCIONS: Escull una opcio." << endl;
        cout << "\n1. Menu Persona" << endl;
        cout << "\n2. Menu Aula" << endl;
        cout << "\n3. Menu Alumne" << endl;
        cout << "\n4. Menu Professor " << endl;
        cout << "\n5. Menu Personal Extern" << endl;
        cout << "\n6. Menu Edifici" << endl;
        cout << "\n7. Finalitzar!" << endl;
        cout <<" --------------------------------------------------------------------------------------------" << endl;
        cin >> option;
        while (option < 1 || option > 7){
            cout << "OpciÛ incorrecte. Torna a escollir una opciÛ:" << endl;
            cin >> option;
        }
}

//VOIDS.......
/**
- Eliminar posibles contagis alhora de l'entrada a l'edifici HECHO (LIST)
- Poder gestionar les entrades i sortides del centre, inclÚs líhora del pati. HECHO (QUEUE)
- Capacitat de poder confinar una aula si se'n registren mÈs de tres
  positius en aquesta. HECHO KIRIAN EL CRACK

- ConËixer la quantitat de grups (persona ,alumnes, professors, personal
  extern) que hi ha dins l'edifici i calcular el total. STACK HECHO

- Conèixer la quantitat d'alumnes que hi ha en una aula segons el
  moment del dia. HECHO  EN CADA CLASE

- Presenciar la distribuciÛ de seguretat díaules i dels edificis respecte a la
  relaciÛ espai/persones.

- ¡¡¡ Cálculos estadisticos !!!

- Tenir la capacitat d'afegir i eliminar positius al registre.

**/
// Menu Interactiu
int main(void){

    setlocale(LC_ALL,"Catalan");
    int option;
    MenuPrincipal(option);
    while (1 <= option && option <= 6){
        switch (option){
            case 1: {

                setlocale(LC_ALL,"Catalan");
                cout << "Has escollit el Menu de Persona" << endl;
                cout << "\nBenvingut al Menu de Persona " << endl;
                ifstream fpersona("personas.txt");
                Persona P(fpersona);
                stack<Persona,vector<Persona> > GestioPersona;
                int opP;
                MenuPersona(opP);
                while (1 <= opP & opP <= 4){
                        switch (opP){
                        case 1: {
                                cout << "1.Desplegar la llista amb la informacio de cada persona que entra a l'edifici" <<endl;
                                vector<Persona> vP;
                                vP.push_back(P);
                                while(fpersona>>P){

                                vP.push_back(P);
                                }
                                for(int i=0;i<vP.size();i++){

                                cout << vP[i] << endl;
                                }
                                break;
                        }
                        case 2: {
                                cout << "2.Afegir positiu al registre " <<endl;
                                //queue<Persona> GestioPersona;
                                string NOM,DNI,COGNOM;int Edat;char Sexe;
                                cout << "Introdueix un nom: "<<endl; cin >> NOM;
                                cout << "Introdueix un Cognom: "<<endl; cin >>COGNOM;
                                cout << "Introdueix un DNI: "<<endl; cin >> DNI;
                                cout << "Introdueix un Edat: "<<endl; cin >> Edat;
                                cout << "Introdueix un Sexe(D/H ,Dona = D , Home = H) : "<<endl; cin >> Sexe;
                                Persona P(NOM,COGNOM,DNI,Edat,Sexe);
                                GestioPersona.push(P);
                                cout << P;
                                break;
                        }
                        case 3:{
                                cout << "3.Eliminar positiu al registre" <<endl;
                                //queue<Persona>GestioPersona;
                                if(!GestioPersona.empty()){
                                P = GestioPersona.top();
                                cout << "Nom : " << P.getNom()<< " Cognom: " << P.getCognom() << " DNI: " << P.getDNI() << " Edat:  " << P.getEdat() << " Sexe(Home H/ Dona D ):  " << P.getSexe() << endl;
                                GestioPersona.pop();
                        }
                        else {cout << "No hi ha persones dins l'edifici!"<< endl;}
                                break;
                        }
                        case 4:{
                                cout << "Coneixer la quantitat màxima de persones que hi ha dins de l'edifici" <<endl;
                                Persona PE;
                                stack <Persona> personas;
                                personas.push(PE);
                                int cont=0;
                                while(fpersona>>PE){
                                    personas.push(PE);
                                }
                                cont = personas.size();
                                cout << " Total de persones dins l'edifici : "<< cont << endl;
                                break;
                        }
                        case 5: {
                                cout << "Buscar a l'alumne mitjaçant el DNI" << endl;
                                map<string,Persona> BuscaPersona;
                                map<string,Persona>:: iterator it;
                                string dni,cog,nom;int edat;char sexe;
                                Persona P;
                                while(fpersona>>P){
                                Persona P(nom,cog,dni,edat,sexe);
                                BuscaPersona.insert(dni,P);
                                }
                                /*
                                cout << "Introdueixi el DNI " << endl; cin >> DNI;
                                for(it = BuscaPersona.begin(); it != BuscaPersona.end();it++){

                                    it
                                */

                                break;
                        }
                        default: {}
                        }
                    MenuPersona(opP);
                    }
                MenuPrincipal(option);
             break;
            }
            case 2: {
                cout << "Has escollit el Menu Aules" << endl;
                cout << "\nBenvingut al Menu d'aules " << endl;
                ifstream faula1("TR1.txt");
                Aula A1(faula1);
                cout << A1;
                ifstream faula2("TR2.txt");
                Aula A2(faula2);
                cout << A2;
                ifstream faula3("TR3.txt");
                Aula A3(faula3);
                cout << A3;
                /*vector<Aula> vAU;
                vAU.push_back(AU);
                while(faula>>AU){
                   vAU.push_back(AU);
                }
                for(int i=0;i<vAU.size();i++){
                    cout << vAU[i] << endl;
                }
                */
                break;
            }
            case 3: {

                setlocale(LC_ALL,"Catalan");
                cout << "Has escollit el Menu Alumnes" << endl;
                cout << "\nBenvingut al Menu d'alumnes " << endl;
                ifstream falumne("alumnes.txt");
                Persona P;
                Alumne AL(P,falumne);
                int opA;
                MenuAlumne(opA);
                while (1 <= opA & opA <= 3){
                        switch (opA){
                            case 1: {
                                cout << "1.Desplagar la lista d'alumnes que han entrat a l'edifici " <<endl;
                                vector<Alumne> vA;
                                vA.push_back(AL);
                                while(falumne>>AL){
                                    vA.push_back(AL);
                                }
                                for(int i=0;i<vA.size();i++){
                                    cout << vA[i] << endl;
                                    }
                                break;
                            }
                            case 2: {
                                cout << "2.Coneixer la quantitat d'alumnes que hi ha en cada aula" <<endl;
                                vector<Alumne> vA;
                                vA.push_back(AL);
                                int cont1=1,cont2=0,cont3=0;
                                while(falumne>>AL){
                                    vA.push_back(AL);
                                    if(AL.getAula()=="TR1-001"){cont1++;}
                                    else if(AL.getAula()=="TR2-001"){cont2++;}
                                    else if(AL.getAula()=="TR3-001"){cont3++;}

                                }
                                cout<<"Total d'alumnes en la classe TR1-001 es de : "<< cont1 << endl;
                                cout<<"Total d'alumnes en la classe TR2-001 es de : "<< cont2 << endl;
                                cout<<"Total d'alumnes en la classe TR3-001 es de : "<< cont3 << endl;
                                break;
                            }
                            case 3: {
                                cout << "3.Coneixer la quantitat d'alumnes en un edifici" <<endl;
                                vector<Alumne> vA;
                                int contA=0;
                                vA.push_back(AL);
                                while(falumne>>AL){
                                    vA.push_back(AL);

                                }
                                contA=vA.size();
                                cout << "Total d'alumnes dins l'edifici : " << contA << endl;
                                break;
                            }
                            default: {}
                        }
                    MenuAlumne(opA);
                    }
                MenuPrincipal(option);
             break;
            }
            case 4: {
                cout << "Has escollit el Menu de Professors" << endl;
                cout << "\nBenvingut al Menu de professors " << endl;
                ifstream fprofessors("professor.txt");
                Persona P;
                Professor PP(P,fprofessors);
                int opS;
                MenuProfessor(opS);
                while (1 <= opS & opS <= 3){
                        switch (opS){
                            case 1: {
                                cout << "1.Desplegar la llista del professors dins l'edifici " <<endl;
                                vector<Professor> vPP;
                                vPP.push_back(PP);
                                while(fprofessors>>PP){

                                    vPP.push_back(PP);
                                }
                                for(int i=0;i<vPP.size();i++){

                                    cout << vPP[i] << endl;
                                }
                                break;
                            }
                            case 2: {
                                cout << "2.Coneixer la quantitat de professors assignats en cada aula " <<endl;
                                vector<Professor> vPP;
                                vPP.push_back(PP);
                                int cont1=1,cont2=0,cont3=0;
                                while(fprofessors>>PP){
                                    vPP.push_back(PP);

                                    if(PP.getAula()=="TR1-001"){cont1++;}
                                    else if(PP.getAula()=="TR2-001"){cont2++;}
                                    else if(PP.getAula()=="TR3-001"){cont3++;}
                                }
                                cout<<"Total de professors en la classe TR1-001 es de : "<< cont1 << endl;
                                cout<<"Total de professors en la classe TR2-001 es de : "<< cont2 << endl;
                                cout<<"Total de professors en la classe TR3-001 es de : "<< cont3 << endl;
                                break;
                            }
                            case 3: {
                                cout << "3. Coneixer la quantitat de professors dins d'edifici" <<endl;
                                vector<Professor> vPP;
                                int contP=0;
                                vPP.push_back(PP);
                                while(fprofessors>>PP){

                                    vPP.push_back(PP);
                                }
                                contP=vPP.size();
                                cout << "Total de professors  dins l'edifici : " << contP << endl;
                                break;
                            }
                            default: {}
                        }
                    MenuProfessor(opS);
                    }
                MenuPrincipal(option);
             break;
            }
            case 5: {
                setlocale(LC_ALL,"Catalan");
                cout << "Has escollit el Menu Personal Extern " << endl;
                cout << "\nBenvingut al Menu del personal Extern " << endl;
                ifstream fpersonalextern("personalextern.txt");
                Persona P;
                PersonalExtern PE(P,fpersonalextern);
                int opPE;
                MenuAlumne(opPE);
                while (1 <= opPE & opPE <= 3){
                        switch (opPE){
                            case 1: {
                                cout << "1.Coneixer la quantitat de personal extern assignats en cada aula " <<endl;
                                vector<PersonalExtern> vPE;
                                vPE.push_back(PE);
                                while(fpersonalextern>>PE){
                                    vPE.push_back(PE);
                                }
                                for(int i=0;i<vPE.size();i++){
                                    cout << vPE[i] << endl;
                                    }
                                break;
                            }
                            case 2: {
                                cout << "2.Coneixer la quantitat de personal extern assignats en cada aula" <<endl;
                                vector<PersonalExtern> vPE;
                                vPE.push_back(PE);
                                int cont1=1,cont2=0,cont3=0;
                                while(fpersonalextern>>PE){
                                    vPE.push_back(PE);
                                    if(PE.getAula()=="TR1-001"){cont1++;}
                                    else if(PE.getAula()=="TR2-001"){cont2++;}
                                    else if(PE.getAula()=="TR3-001"){cont3++;}

                                }
                                cout<<"Total d'alumnes en la classe TR1-001 es de : "<< cont1 << endl;
                                cout<<"Total d'alumnes en la classe TR2-001 es de : "<< cont2 << endl;
                                cout<<"Total d'alumnes en la classe TR3-001 es de : "<< cont3 << endl;
                                break;
                            }
                            case 3: {
                                cout << "3.Coneixer la quantitat de personal extern dins d'edifici" <<endl;
                                vector<PersonalExtern> vPE;
                                int contPE=0;
                                vPE.push_back(PE);
                                while(fpersonalextern>>PE){
                                    vPE.push_back(PE);

                                }
                                contPE=vPE.size();
                                cout << "Total d'alumnes dins l'edifici : " << contPE << endl;
                                break;
                            }
                            default: {}
                        }
                    MenuPersonaExtern(opPE);
                    }
                MenuPrincipal(option);
             break;
            }
            case 6: {
                cout << "Has escollit el Menu Edifici" << endl;
                cout << "\nBenvingut al Menu d'edificis " << endl;
                ifstream fedifici("edificis.txt");
                Edifici EE(fedifici);

                queue<Edifici> GestioEdifici;
                int opE;
                MenuEdifici(opE);
                while (1 <= opE & opE <= 5){
                    switch (opE){

                    case 1:{
                     cout << "1.Desplegar la llista de possibles contagiats" <<endl;
                        list<Edifici> Infectats;
                        list<Edifici>:: iterator it = Infectats.begin();
                        string dnie; DataHora E,S;double temp;
                        while(fedifici >> dnie >> E >> S >>temp){
                            if(temp>=37.5){
                                    Edifici EI(dnie,E,S,temp);
                                    Infectats.push_back(EI);

                            }
                        }

                          for(it=Infectats.begin();it!=Infectats.end();it++){
                            cout<<"---------------------------"<<endl;
                            cout<<*it<<endl;
                            cout<<"Possible infectat, acces denegat!"<<endl;
                            cout<<"---------------------------"<<endl;
                        }
                    break;
                    }
                    case 2:{
                        cout << "2.Desplagar la llista dels no contagiats" <<endl; //NO FUNCIONA SI USAS EL CASE 1, HAY QUE SALIR AL MENU PRINCIPAL "5" Y VOLVER A ESTE CASE
                        ///Eliminar posibles contagis alhora de l'entrada a l'edifici
                        list<Edifici> Sans;
                        list<Edifici>:: iterator it2 = Sans.begin();
                        string dnie2; DataHora E2,S2;double temp2;
                        while(fedifici >> dnie2 >> E2 >> S2 >>temp2){
                            if(temp2<37.5){
                                    Edifici ES(dnie2,E2,S2,temp2);
                                    Sans.push_back(ES);
                                }
                        }
                        for(it2=Sans.begin();it2!=Sans.end();it2++){
                            cout<<"---------------------------"<<endl;
                            cout<<*it2<<endl;
                            cout<<"Pots entrar."<<endl;
                            cout<<"---------------------------"<<endl;
                        }
                    break;
                    }
                    case 3:{
                        cout << "3.Entrar persona a l'edifici" <<endl;
                        string DNIE; double Temp;
                        DataHora HEE; //DataHora d'entrada
                        DataHora HES; //DataHora de sortida

                        cout << "Introdueix un DNI: "<<endl; cin >> DNIE;
                        cout << "Introdueix una DataHora d'entrada(5/06/2021 19:25:35 nomes els numeros)  " << endl; cin >> HEE;
                        cout << "Introdueix una DataHora de sortida(6/06/2021 20:20:15 nomes els numeros)  " << endl; cin >> HES;
                        cout << "Introdueix una Temperatura entre 35.0 i 41 : "<<endl; cin >> Temp;
                        Edifici EE(DNIE,HEE,HES,Temp);
                        GestioEdifici.push(EE);
                        cout<<EE;
                        break;
                    }
                    case 4: {
                        cout << "4.Sortir persona de l'edifici" <<endl;
                        if(!GestioEdifici.empty()){
                            Edifici EE = GestioEdifici.front();
                            cout << "Esta sortint la persona amb DNI: "<<EE.getDNIE()<<" i amb una temperatura de "<<EE.getTemp()<<endl;
                            GestioEdifici.pop();
                        }
                        else {cout << "No hi ha persones dins l'edifici!"<< endl;}
                    break;
                    }
                    case 5:{
                        cout << "5. Confinar Aula de l'edifici" << endl;
                        vector<Edifici> Total;
                        vector<Edifici> Infectats2;
                        list<Edifici> Infectats;
                        int cont=0;
                        string dniC; DataHora EC,SC;double tempC;
                        while(fedifici >> dniC >> EC >> SC >>tempC){
                            Edifici D(dniC,EC,SC,tempC);
                            Total.push_back(D);
                            if(tempC>=37.5){
                                    Edifici EI(dniC,EC,SC,tempC);
                                    Infectats2.push_back(EI);
                            }
                        }
                        for(int i=0;i<=Infectats2.size();i++){
                            for(int y=0;y<=Total.size();y++){
                                    if(Infectats2[i].getDNIE()==Total[y].getDNIE()){
                                        cont++;
                                    }
                            }
                        }
                        if(cont>=5){
                            cout<<endl<<endl<<"WARNING  WARNING WARNING  WARNING WARNING  WARNING WARNING  WARNING "<<endl<<endl;
                            cout<<"L'edifici ha sigut confinat per excÃ©s de positius de COVID-19"<<endl<<endl;
                            cout<<"WARNING  WARNING WARNING  WARNING WARNING  WARNING WARNING  WARNING "<<endl<<endl;
                        }
                        else cout<<"Edifici sense suficients contagis"<<endl;

                        break;
                    }
                default: {}
                }
            MenuEdifici(opE);
            }
          }
        }
    MenuPrincipal(option);
    }
cout << "\nPrograma finalitzat fins aviat! " << endl;
}
