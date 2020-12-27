#include <iostream>
#include<cstring>
#include<fstream>
#include<algorithm>
#include<vector>
#include<set>
#include<list>
#include<map>
using namespace std;
int cod=0;
int cod2=0;
class Account{
private:
    int code=0;
    double balance;
    char *nume;
    vector <double> tranzactii;
    vector <string> actiuni;
    void direct_set();
public:
    int get_code(){
        return code;
    }
    friend void load_conturi();
    int get_tranzactii(int h){
        return tranzactii[h];
    }
    string get_actiuni(int h){
        return actiuni[h];
    }
    int tranzactii_max(){
        return tranzactii.size();
    }
    friend void operatiuni();
    friend void remove_account(int c);
    Account(const Account &x){
        //cout<<"From "<<x.nume<<" to "<<nume<<endl;
        nume=new char[strlen(x.nume)+1];
        strcpy(nume,x.nume);
        balance=x.balance;
        tranzactii=x.tranzactii;
        actiuni=x.actiuni;
        //cod++;
        code=x.code;
        //cout<<"Cont "<<nume<<" deschis"<<endl;
    }
    friend std::istream &operator>>(std::istream &s,Account &d);
    friend std::ostream &operator<<(std::ostream &x,const Account &y);
    string get_name(){
        string str;
        for(int i=0;i<strlen(nume);i++)
            str+=nume[i];
        return str;
    }
    double get_balance(){
        return balance;
    }
    friend class Furniture;
    friend class Masina;
    friend class Baie;
    /*
    Account &operator=(const Account &x){
        balance=x.balance;
        tranzactii=x.tranzactii;
        actiuni=x.actiuni;
    }
    */
    Account(const char *c){
        int nume_size=strlen(c)+1;
        nume=new char[nume_size+1];
        strcpy(nume,c);
        balance=0;
        cod++;
        code=cod;
        //if(strcmp(nume,"None")!=0)cout<<"Cont "<<nume<<" deschis"<<endl;
    }
    Account(){
        nume=new char[6];
        strcpy(nume,"Guest");
        //cout<<"Cont "<<nume<<" deschis"<<endl;
        balance=0;
        //cod++;
        //code=cod;
    }
    void get_info(){
    cout<<endl<<endl<<"==========================================="<<endl;
    cout<<"Nume cont:"<<nume<<endl;
    cout<<"Cod unic:"<<code<<endl;
    cout<<"Sold curent:"<<balance<<endl;
    cout<<"Tranzactii efectuate:"<<endl;
    for(int i=0;i<tranzactii.size();i++)
        cout<<i+1<<") "<<tranzactii[i]<<", tip tranzactie:"<<actiuni[i]<<endl;
    cout<<"==========================================="<<endl<<endl;
    }

    void add_balance(double x){
    try{
        if(x<0)
            throw x;
        balance+=x;
        if(x>0){
            tranzactii.push_back(x);
            string c{"Adaugare fonduri"};
            actiuni.push_back(c);}
    }

    catch(double &ex){
        cerr<<"Va rugam introduceti o valoare valida"<<endl;
    }
    }
    bool operator==(const Account &x){
        return code==x.code;
    }
    bool operator<(const Account &x){
        return code<x.code;
    }
    Account &operator++(){
        int x=strlen(nume);
        char *nume2=new char[x+1];
        strcpy(nume2,nume);
        for(int i=0;i<x;i++)
            if(i==0 || nume2[i-1]==' ')
                nume2[i]=toupper(nume2[i]);
        strcpy(nume,nume2);
        delete [] nume2;
        return *this;
    }
    bool operator>=(double &&x){
        if(balance>=x)
            return true;
        else
            return false;
    }

    Account &operator=(const Account &x){
        if(this==&x){
            return *this;
        }
        //if(*nume!='\0')
        if(nume!=NULL)
        delete [] nume;
        nume=new char[strlen(x.nume)+1];
        strcpy(nume,x.nume);
        balance=x.balance;
        tranzactii=x.tranzactii;
        actiuni=x.actiuni;
        code=x.code;
        return *this;
    }


    explicit operator int(){
        return (int)this->balance;

    }
    void operator[](int i){
        if(i>=0 || i<tranzactii.size())
            cout<<"Tranzactia:"<<tranzactii[i]<<", tip tranzactie:"<<actiuni[i]<<endl;
        else
            cout<<"Indice invalid";
    }
    Account &operator+(const Account &x){
        if(this==&x)
            return *this;
        balance=x.balance;
        actiuni.clear();tranzactii.clear();
        for(int i=0;i<x.actiuni.size();i++)
            {actiuni.push_back(x.actiuni[i]);tranzactii.push_back(x.tranzactii[i]);}
        return *this;
    }
    Account &operator-(const Account &x){
        if(this==&x)
            return *this;
        for(int i=0;i<x.actiuni.size();i++)
            for(int j=0;j<actiuni.size();j++)
                if(x.actiuni[i]==actiuni[j])
                    if(x.tranzactii[i]==tranzactii[j])
                        {actiuni.erase(actiuni.begin()+ j);tranzactii.erase(tranzactii.begin()+ j);balance-=x.tranzactii[i];j--;}
        return *this;
    }
    ~Account(){
        //cout<<"STERS "<<nume<<" code "<<code<<endl;
        //if(*nume!='\0' && nume!=nullptr)
        if(nume!=nullptr)
        delete [] nume;
        //if(nume!=nullptr && *nume!='\0')
        //{delete [] nume;}
    }

};
std::istream &operator>>(std::istream &s,Account &d){
    //char *str=new char[1000];
    string str;
    cout<<"Introduceti numele nou:";
    s.get();
    getline(s,str);
    delete [] d.nume;
    d.nume=new char[str.length()+1];
    strcpy(d.nume,str.c_str());
    //delete [] str;
    return s;
}
class Renovare{
friend void informatii(Renovare &x);
public:
    /*
    virtual void get_info(){
        cout<<endl<<endl;
        cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl<<"Renovari baie:tavan,podea,pereti la pret de 700,800 si 900"<<endl<<"Renovari masina:Schimbare cauciucuri/usi si renovare interior la pret de 200,500 si 700"<<endl<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
        cout<<endl<<endl;
    }
    */
    friend class Account;
    Renovare(){
        //cout<<"Incepere renovare"<<endl;
    }
    virtual ~Renovare(){
        //cout<<"Inchidere renovare"<<endl;
    }
    /*
    Renovare &operator=(const Renovare *rhs){

    }
    */
protected:
    virtual void info_renovare()=0;
    vector <int> pret;
    vector <string> achizitie;
};
class Furniture{
    private:
        vector <string> tip_mobilier{"Canapea","Pat","Masa","Scaun"};
        vector <float> pret_mobilier{150,200,30,40,10,15,22,17,9};
        vector <string> culoare_mobilier{"Rosu","Galben","Albastru","Verde","Mov"};
        friend std::istream &operator>>(std::istream &x,Furniture &y);
        string achizitie=" ";
        float pret=0,pret2=0;
        int counter;
    public:
        Furniture(){//cout<<"Incepere mobilare"<<endl;
        }
        void tranzactie(Furniture &s,Account &d){
            counter=10;
            pret2=d.get_balance();
            cout<<"Alegeti mobilierul pe care doriti sa-l achizitionati:"<<endl;
            cout<<"Avem:Canapea,Pat,Masa,Scaun(la preturile:150,200,30 si respectiv 40)"<<endl;
            cin>>s;
            if(achizitie!=" "){
            cout<<"Avem culorile:Rosu,Galben,Albastru,Verde,Mov(la preturile:10,15,22,17 si respectiv 9)"<<endl;
            cin>>s;
            d.add_balance(-pret);
            d.tranzactii.push_back(-pret);
            d.actiuni.push_back(achizitie);
            pret=0;
            achizitie=" ";}
        }
        void operator[](int i){
            if(i>=0 && i<tip_mobilier.size())
            cout<<"Pret "<<tip_mobilier[i]<<":"<<pret_mobilier[i]<<endl;
        }
        explicit operator int(){
            return (int)this->pret_mobilier[0];
        }
    ~Furniture(){}
};
std::istream &operator>>(std::istream &x,Furniture &y){
    int t=y.counter;
    string str;
    x>>str;
    for(int i=0;i<4;i++)
        if(str==y.tip_mobilier[i] && y.counter==10){
            if(y.pret2>=y.pret_mobilier[i])
                {y.counter=i;y.pret+=y.pret_mobilier[i];}
            else
                {cout<<"Fonduri insuficiente"<<endl;return x;}
        }
    for(int i=0;i<5;i++)
        if(str==y.culoare_mobilier[i] && y.counter!=10){
            if(y.pret2>=y.pret_mobilier[i+4])
                {y.counter=i;y.pret+=y.pret_mobilier[i+4];}
            else
                {cout<<"Fonduri insuficiente"<<endl;return x;}
        }
    if(t==y.counter)
    {cout<<"Introduceti o valoare valida"<<endl;cin>>y;return x;}
    if(y.achizitie==" ")
        y.achizitie="Achizitionat "+str+" de culoare ";
    else
        y.achizitie=y.achizitie+str;
    return x;
}
class Asigurare{ //Interfata
friend void informatii_asigurare(Asigurare &x);
public:
    virtual void asigurare(int x)=0;
    virtual void info_asigurare()=0;
protected:
};
class Masina:public Renovare,private Asigurare{ //////Masina has a Asigurare , Masina is a Renovare(Renovarea pentru masina este o renovare)

    private:
        int code2;
       char *nume_masina;
       float pret_renovare;
       string culoare;
       double kilometraj;
       vector <string> reparatii{"Cauciucuri","Culoare","Usi","Faruri","Interior"};
       float pret_reparatii[5] {100,30,70,40,120};
       double cash=0;
       string nume_renovare;
       bool renovat=false;
       int asig=0;
    public:
    friend void operatiuni();
    friend void remove_masina(int m);
    void info_asigurare(){
        cout<<"Masina asigurata cu suma de:"<<asig<<endl;
    }
    void asigurare(int x){
    try{
        if(x<0)
            throw x;
        asig+=x;
        //cout<<"Masina asigurata"<<endl;
    }
    catch(int &ex){
        cerr<<"Va rugam introduceti o valoare valida"<<endl;
    }
    }
    void tranzactie(Account &x){
        if(x.balance+asig>=1400 && renovat!=true){
        pret.push_back(200);
        achizitie.push_back("Schimbare cauciucuri");
        pret.push_back(500);
        achizitie.push_back("Schimbare usi");
        pret.push_back(700);
        achizitie.push_back("Renovare interior");
        x.balance+=asig;
        x.balance-=1400;
        if(x.balance<asig){
            asig=x.balance;x.balance=0;
        }
        else{
            x.balance-=asig;
        }
        x.tranzactii.push_back(-200);
        x.tranzactii.push_back(-500);
        x.tranzactii.push_back(-700);
        x.actiuni.push_back("Schimbare cauciucuri");
        x.actiuni.push_back("Schimbare usi");
        x.actiuni.push_back("Renovare interior");
        renovat=true;
        cout<<"Masina renovata"<<endl;
        }
        else
            if(x.balance+asig<1400)
                cout<<"Fonduri insuficiente"<<endl;
        else{
            cout<<"Deja renovat"<<endl;
        }

    }
    friend std::istream &operator>>(std::istream &x,Masina &y);
    friend void remove_masina();
    Masina(const char *c,const string color="incolor",double t=0){
        int nume_size=strlen(c)+1;
        //delete [] nume_masina;
        nume_masina=new char[nume_size];
        strcpy(nume_masina,c);
        pret_renovare=0;
        culoare=color;
        cod2++;
        code2=cod2;
        //cout<<"Masina "<<nume_masina<<" de culoare "<<color<<" adaugata pentru renovare"<<endl;
        kilometraj=t;}
    Masina &operator=(const Masina &x){
        if(this==&x)
            return *this;
        if(nume_masina!=NULL)
            delete [] nume_masina;
        nume_masina=new char[strlen(x.nume_masina)+1];
        strcpy(nume_masina,x.nume_masina);
        pret_renovare=x.pret_renovare;
        kilometraj=x.kilometraj;
        culoare=x.culoare;
        //Renovare::operator=(x);
        code2=x.code2;
        asig=x.asig;
        return *this;
    }
    int get_code2(){
        return code2;
    }
    Masina &operator+(const Masina &x){
        if(this==&x)
            return *this;
        if(nume_masina!=NULL)
            delete [] nume_masina;
        nume_masina=new char[strlen(x.nume_masina)+1];
        strcpy(nume_masina,x.nume_masina);
        pret_renovare=x.pret_renovare;
        kilometraj=x.kilometraj;
        culoare=x.culoare;
        asig=x.asig;
        return *this;
    }
    Masina &operator-(const Masina &x){
        if(this==&x)
            return *this;
        kilometraj-=x.kilometraj;
        return *this;
    }
    Masina(const Masina &sursa){
        nume_masina=new char[strlen(sursa.nume_masina)+1];
        strcpy(nume_masina,sursa.nume_masina);
        kilometraj=sursa.kilometraj;
        culoare=sursa.culoare;
        code2=sursa.code2;
        asig=sursa.asig;
    }
    virtual void get_info(){
        cout<<endl<<endl<<"==========================================="<<endl;
        cout<<"Nume masina:"<<nume_masina<<endl;
        cout<<"Cod unic:"<<code2<<endl;
        cout<<"Culoare masina:"<<culoare<<endl;
        cout<<"Kilometraj masina:"<<kilometraj<<endl;
        info_asigurare();
        cout<<"==========================================="<<endl<<endl;
    }
    int get_asig(){
        return asig;
    }
    friend void load_masini();
    Masina(){
        //cout<<"Masina invalida"<<endl;
        nume_masina=new char[5];
        strcpy(nume_masina,"None");
        culoare="None";
        kilometraj=0;
    }
    void renovare(Masina &s,Account &d){
        d.balance+=s.asig;
        cash=d.get_balance();
        cout<<"Alegeti renovarea pt masina:Cauciucuri,Culoare,Usi,Faruri si Interior(la preturile:100,30,70,40 si respectiv 120)"<<endl;
        cin>>s;
        if(pret_renovare!=0)
        {d.add_balance(-pret_renovare);d.tranzactii.push_back(-pret_renovare);d.actiuni.push_back("Renovat "+nume_renovare+" pentru masina "+nume_masina);}
        pret_renovare=0;
        if(d.balance-s.asig<0){
            s.asig=d.balance;
            d.balance=0;
        }
        else
            d.balance-=s.asig;
    }
    explicit operator int(){
        return (int)kilometraj;
    }
    bool operator==(const Masina &x){
        if(strcmp(nume_masina,x.nume_masina)==0)
            if(kilometraj==x.kilometraj)
                if(culoare==x.culoare)
                    {cout<<"Masini identice"<<endl;return true;}
                else
                    {cout<<"Masini diferite"<<endl;return false;}
    }
    bool operator<(const Masina &x){
        return code2<x.code2;
    }
    void info_renovare(){
        set<string> rep;
        for(int i=0;i<reparatii.size();i++)
            rep.insert(reparatii[i]);
        cout<<"==============================================="<<endl;
        cout<<"Renovari valabile pentru masina:"<<endl;
        //int j=0;
        for(const auto &i:rep){
            for(int j=0;j<reparatii.size();j++)
                if(reparatii[j]==i)
                    cout<<"Renovare "<<i<<" la pret de "<<pret_reparatii[j]<<endl;
        }
        cout<<"==============================================="<<endl;
    }
    bool operator>=(const Masina &x){
            if(kilometraj>=x.kilometraj)
                    {cout<<"Masina mai veche"<<endl;return true;}
                else
                    {cout<<"Masina mai noua"<<endl;return false;}
    }
    void operator[](int i){
        if(i>=0 && i<reparatii.size())
            cout<<"Renovare "<<reparatii[i]<<" la pret de "<<pret_reparatii[i]<<endl;
    }
    Masina &operator++(){
        for(int i=0;i<strlen(nume_masina);i++)
            nume_masina[i]=toupper(nume_masina[i]);
        return *this;
    }
    void modificare_masina(const char *c,string x,double j){
        delete [] nume_masina;
        nume_masina=new char[strlen(c)+1];
        strcpy(nume_masina,c);
        culoare=x;
        kilometraj=j;
    }
    double get_kilometraj(){
        return kilometraj;
    }
    string get_culoare(){
        return culoare;
    }
    string get_name(){
        string str;
        for(int i=0;i<strlen(nume_masina);i++)
            str+=nume_masina[i];
        return str;
    }
    virtual ~Masina(){
        if(nume_masina!=nullptr)
        delete [] nume_masina;
        }
};
std::istream &operator>>(std::istream &x,Masina &y){
    string str;
    x>>str;
    y.nume_renovare=str;
    int j=10;
    for(int i=0;i<y.reparatii.size();i++)
        if(str==y.reparatii[i])
            if(y.cash>=y.pret_reparatii[i])
               {y.pret_renovare=y.pret_reparatii[i];j=i;cout<<"Renovare aplicata"<<endl;}
            else
                {cout<<"Fonduri insuficiente"<<endl;return x;}
    if(j==10)
        {cout<<"Introduceti o valoare valida"<<endl;cin>>y;}
    return x;
}
class Baie:public Renovare{
    private:
        float pret_renovare;
        vector <string> reparatii{"Cada","Toaleta","Chiuveta","Tavan","Pereti","Podea","Usa"};
        float pret_reparatii[7] {100,150,80,200,120,170,80};
        double cash=0;
        string nume_renovare;
        bool renovat=false;
    public:
        friend std::istream &operator>>(std::istream &x,Baie &y);
        friend void operatiuni();
        Baie(){//cout<<"Incepere renovare baie"<<endl;
        }
    void info_renovare(){
        map<string,int> bai;
        for(int i=0;i<reparatii.size();i++)
            bai[reparatii[i]]=pret_reparatii[i];
        cout<<"==============================================="<<endl;
        cout<<"Renovari valabile pentru baie:"<<endl;
        for(const auto &i:bai)
            cout<<"Renovare "<<i.first<<" la pret de "<<i.second<<endl;
        cout<<"==============================================="<<endl;
    }
    void renovare(Baie &s,Account &d){
        cash=d.get_balance();
        cout<<"Alegeti renovarea pt bucatarie:Cada,Toaleta,Chiuveta,Tavan,Pereti,Podea si Usa(la preturile:100,150,80,200,120,170 si respectiv 80)"<<endl;
        cin>>s;
        if(pret_renovare!=0)
        if((int)pret_renovare==pret_renovare)
        {d.add_balance(-pret_renovare);d.tranzactii.push_back(-pret_renovare);d.actiuni.push_back("Renovat "+nume_renovare+" din baie");}
        s.pret_renovare=0;
    }
    explicit operator int(){
        return (int)this->pret_reparatii[0];
    }
    void operator[](int i){
        if(i>=0 && i<reparatii.size())
        cout<<"Reparare "<<reparatii[i]<<" la pret de "<<pret_reparatii[i]<<endl;
    }
        ~Baie(){}
        /*
    void renovare(Account &x){
        if(x.balance>=2400 && renovat!=true){
        pret.push_back(700);
        achizitie.push_back("Renovare tavan");
        pret.push_back(800);
        achizitie.push_back("Renovare podea");
        pret.push_back(900);
        achizitie.push_back("Renovare pereti");
        x.balance-=2400;
        x.tranzactii.push_back(-700);
        x.tranzactii.push_back(-800);
        x.tranzactii.push_back(-900);
        x.actiuni.push_back("Renovare tavan");
        x.actiuni.push_back("Renovare podea");
        x.actiuni.push_back("Renovare pereti");
        renovat=true;
        cout<<"Baie renovata"<<endl;
        }
        else
            if(x.balance<2400)
                cout<<"Fonduri insuficiente"<<endl;
        else{
            cout<<"Deja renovat"<<endl;
        }
    }
    */

};
std::istream &operator>>(std::istream &x,Baie &y){
    string str;
    x>>str;
    y.nume_renovare=str;
    int j=10;
    for(int i=0;i<y.reparatii.size();i++)
        if(str==y.reparatii[i])
            if(y.cash>=y.pret_reparatii[i])
               {y.pret_renovare=y.pret_reparatii[i];j=i;cout<<"Renovare aplicata"<<endl;}
            else
                {cout<<"Fonduri insuficiente"<<endl;return x;}
    if(j==10)
        {cout<<"Introduceti o valoare valida"<<endl;cin>>y;}
    return x;
}
std::ostream &operator<<(std::ostream &x,const Account &y){
    x<<y.balance;
    cout<<endl;
    return x;
}
/*
void informatii(Renovare &x){
    x.get_info();
}
*/
vector<Account> vec;
vector<Masina> vec2;
void add_account(){

string num;

cout<<"Alegeti numele:";
cin.get();
getline(cin,num);

char s[num.length()+1];
strcpy(s,num.c_str());
Account Obiect{s};
vec.push_back(Obiect);
}
void add_masina(){

string num;

cout<<"Alegeti modelul:";
cin.get();
getline(cin,num);
char s[num.length()+1];
strcpy(s,num.c_str());
cout<<"Alegeti culoarea:";
string m;
//cin.get();
getline(cin,m);
cout<<"Alegeti kilometrajul:";
int x;
cin>>x;
Masina Obiect{s,m,x};
vec2.push_back(Obiect);
}
void remove_masina(int m){
    for(int i=0;i<vec2.size();i++)
        if(vec2[i].code2==m){
         swap(vec2[i],vec2[vec2.size()-1]);
         vec2.pop_back();
    }
}


void remove_account(int c){
    for(int i=0;i<vec.size();i++){
        if(vec[i].code==c){
            /*
            if(vec.empty()==1)
                cout<<"Niciun cont introdus"<<endl;
            else{
                cout<<"Conturi introduse:"<<endl;
                for(int j=0;j<vec.size();j++)
                    cout<<"Nume cont:"<<vec[j].nume<<", cod unic:"<<vec[j].code<<", fonduri cont:"<<vec[j].balance<<endl;
            }
            */
            /*
            Account No;
            No=vec[i];
            vec[i]=vec[vec.size()-1];
            vec[vec.size()-1]=No;
            */
            swap(vec[i],vec[vec.size()-1]);
            vec.pop_back();
        }
    }
}
void operatiuni(){
    int d=1;
    Furniture mobila;
    Baie baie;
    while(d!=0){
        cout<<"Alegeti numarul fiecarei optiuni:"<<endl;
        cout<<"1) Setari cont"<<endl;
        cout<<"2) Renovare masina"<<endl;
        cout<<"3) Setari casa"<<endl;
        cout<<"0) Iesire"<<endl<<endl;
        if(vec.empty()==1)
            cout<<"Niciun cont introdus"<<endl;
        else{
            cout<<"========================================"<<endl;
            cout<<"Conturi introduse:"<<endl;
            for(int i=0;i<vec.size();i++)
                cout<<"Nume cont:"<<vec[i].nume<<", cod unic:"<<vec[i].code<<", fonduri cont:"<<vec[i].balance<<endl;
            cout<<"========================================"<<endl;
        }
        if(vec2.empty()==1)
            cout<<"Nici-o masina introdusa"<<endl;
        else{
            cout<<"========================================"<<endl;
            cout<<"Masini introduse:"<<endl;
            for(int i=0;i<vec2.size();i++)
                cout<<"Model masina:"<<vec2[i].nume_masina<<", cod unic:"<<vec2[i].code2<<", culoare masina:"<<vec2[i].culoare<<", kilometraj masina:"<<vec2[i].kilometraj<<", asigurare:"<<vec2[i].asig<<endl;
            cout<<"========================================"<<endl;
        }
        cin>>d;
        int t=1;
        if(d==1){
            while(t!=0){
                cout<<"Optiuni:"<<endl;
                cout<<"1) Adaugare cont:"<<endl;
                cout<<"2) Stergere cont:"<<endl;
                cout<<"3) Redenumiti un cont:"<<endl;
                cout<<"4) Adaugati fonduri:"<<endl;
                cout<<"5) Afisare informatii cont:"<<endl;
                cout<<"6) Copiere cont(Numele si codul unic nu vor fi copiate):"<<endl;
                cout<<"7) Eliminare tranzactii duplicate de 2 conturi:"<<endl;
                cout<<"0) Inapoi"<<endl;
                if(vec.empty()==1)
                    cout<<"Niciun cont introdus"<<endl;
                else{
                    cout<<"========================================"<<endl;
                    cout<<"Conturi introduse:"<<endl;
                    for(int i=0;i<vec.size();i++)
                        cout<<"Nume cont:"<<vec[i].nume<<", cod unic:"<<vec[i].code<<", fonduri cont:"<<vec[i].balance<<endl;
                    cout<<"========================================"<<endl;
                    }
                 if(vec2.empty()==1)
                    cout<<"Nici-o masina introdusa"<<endl;
                else{
                    cout<<"========================================"<<endl;
                    cout<<"Masini introduse:"<<endl;
                    for(int i=0;i<vec2.size();i++)
                        cout<<"Model masina:"<<vec2[i].nume_masina<<", cod unic:"<<vec2[i].code2<<", culoare masina:"<<vec2[i].culoare<<", kilometraj masina:"<<vec2[i].kilometraj<<", asigurare:"<<vec2[i].asig<<endl;
                    cout<<"========================================"<<endl;
                    }
                cin>>t;
                if(t==1){
                    add_account();
                    sort(vec.begin(),vec.end());
                }
                else
                if(t==2){
                    char z[100];
                    cout<<"Scrieti codul contului ales:"<<endl;
                    cin>>z;
                    int m=atoi(z);

                    int k=0;
                    for(int i=0;i<vec.size();i++)
                        if(vec[i].code==m)
                         {remove_account(m);k=1;sort(vec.begin(),vec.end());}
                    if(k==0)
                        cout<<"Cod invalid"<<endl;


                         }
                else
                if(t==3){
                    char z[100];
                    cout<<"Scrieti codul contului ales:";
                    cin.get();
                    cin.get(z,100);
                    int m=atoi(z);
                    int k=0;
                    for(int i=0;i<vec.size();i++){
                        if(vec[i].code==m)
                            {cin>>vec[i];k=1;}
                    }
                    if(k==0)
                        cout<<"Cod invalid"<<endl;
                }
                else
                if(t==4){
                    char z[100];
                    cout<<"Scrieti codul contului ales:";
                    cin.get();
                    cin.get(z,100);
                    int m=atoi(z);
                    int k=0;
                    for(int i=0;i<vec.size();i++)
                        if(vec[i].code==m)
                        {
                        k=1;
                        cout<<"Cat doriti sa adaugati?"<<endl;
                        char g[100];
                        cin>>g;
                        m=atoi(g);
                        vec[i].add_balance(m);
                        if(m==0)
                            cout<<"Valoare invalida"<<endl;
                            }
                    if(k==0)
                        cout<<"Cod invalid"<<endl;
                }
                else
                if(t==5){
                    cout<<"Scrieti codul contului ales:";
                    char z[100];
                    cin>>z;
                    int m=atoi(z);
                    int k=0;
                    for(int i=0;i<vec.size();i++)
                        if(vec[i].code==m)
                            {vec[i].get_info();k=1;}
                    if(k==0)
                        cout<<"Cod invalid"<<endl;
                }
                else
                if(t==6){
                    cout<<"Scrieti codul contului pe care vreti sa-l copiati:";
                    char z[100];cin.get();cin.get(z,100);int m=atoi(z);
                    if(m==0){
                     cout<<"Cod invalid"<<endl;break;
                    }
                    cout<<"Scrieti codul contului in care vreti sa copiati contul anterior:";
                    char z2[100];cin.get();cin.get(z2,100);int n=atoi(z2);
                    if(n==0){
                        cout<<"Cod invalid"<<endl;break;
                    }
                    for(int i=0;i<vec.size();i++)
                        for(int j=0;j<vec.size();j++)
                            if(vec[i].code==m && vec[j].code==n)
                                vec[j]+vec[i];
                }
                else
                if(t==7){
                    cout<<"Scrieti codul contului care contine tranzactiile duplicate:";
                    char z[100];cin.get();cin.get(z,100);int m=atoi(z);
                    if(m==0){
                     cout<<"Cod invalid"<<endl;break;
                    }
                    cout<<"Scrieti codul contului din care vreti sa stergeti:";
                    char z2[100];cin.get();cin.get(z2,100);int n=atoi(z2);
                    if(n==0){
                        cout<<"Cod invalid"<<endl;break;
                    }
                    for(int i=0;i<vec.size();i++)
                        for(int j=0;j<vec.size();j++)
                            if(vec[i].code==m && vec[j].code==n)
                                vec[j]-vec[i];
                }
                else
                if(t!=0)
                    cout<<"Cod invalid"<<endl;
            }
        }
        else
        if(d==2){
            while(t!=0){
                cout<<"Optiuni:"<<endl;
                cout<<"1) Adaugare masina:"<<endl;
                cout<<"2) Stergere masina:"<<endl;
                cout<<"3) Informatii masina:"<<endl;
                cout<<"4) Asigurare masina:"<<endl;
                cout<<"5) Renovare masina(Necesita un cont cu fonduri suficiente):"<<endl;
                cout<<"6) Copiere masina:"<<endl;
                cout<<"7) Modificare masina:"<<endl;
                cout<<"0) Inapoi"<<endl;
                if(vec.empty()==1)
                    cout<<"Niciun cont introdus"<<endl;
                else{
                    cout<<"========================================"<<endl;
                    cout<<"Conturi introduse:"<<endl;
                    for(int i=0;i<vec.size();i++)
                        cout<<"Nume cont:"<<vec[i].nume<<", cod unic:"<<vec[i].code<<", fonduri cont:"<<vec[i].balance<<endl;
                    cout<<"========================================"<<endl;
                    }
                if(vec2.empty()==1)
                    cout<<"Nici-o masina introdusa"<<endl;
                else{
                    cout<<"========================================"<<endl;
                    cout<<"Masini introduse:"<<endl;
                    for(int i=0;i<vec2.size();i++)
                        cout<<"Model masina:"<<vec2[i].nume_masina<<", cod unic:"<<vec2[i].code2<<", culoare masina:"<<vec2[i].culoare<<", kilometraj masina:"<<vec2[i].kilometraj<<", asigurare:"<<vec2[i].asig<<endl;
                    cout<<"========================================"<<endl;
                    }
                cin>>t;
                if(t==1){
                    add_masina();
                    sort(vec2.begin(),vec2.end());
                }
                else
                if(t==2){
                    cout<<"Scrieti codul masinii alese:";
                    char z[100];
                    cin.get();
                    cin.get(z,100);
                    int m=atoi(z);
                    int k=0;
                    for(int i=0;i<vec2.size();i++)
                    if(vec2[i].code2==m){
                        remove_masina(m);k=1;sort(vec2.begin(),vec2.end());
                    }
                    if(k==0)
                        cout<<"Cod invalid"<<endl;

                }
                else
                if(t==3){
                    cout<<"Scrieti codul masinii alese:";
                    char z[100];
                    cin.get();
                    cin.get(z,100);
                    int m=atoi(z);
                    int k=0;
                    for(int i=0;i<vec2.size();i++)
                        if(vec2[i].code2==m){
                            vec2[i].get_info();k=1;
                    }
                    if(k==0)
                        cout<<"Cod invalid"<<endl;
                }
                else
                if(t==4){
                    cout<<"Scrieti codul masinii alese:";
                    char z[100];
                    cin.get();
                    cin.get(z,100);
                    int m=atoi(z);
                    int k=0;
                    for(int i=0;i<vec2.size();i++)
                        if(vec2[i].code2==m){
                            k=1;
                            cout<<"Alegeti suma dorita:";
                            cin.get();
                            cin.get(z,100);
                            m=atoi(z);
                            if(m==0)
                                cout<<"Valoare invalida"<<endl;
                            else
                                vec2[i].asigurare(m);
                    }
                    if(k==0)
                        cout<<"Cod invalid"<<endl;
                }
                else
                if(t==5){
                    cout<<"Scrieti codul masinii alese:";
                    char z[100];
                    cin.get();
                    cin.get(z,100);
                    int m=atoi(z);
                    if(m==0){
                        cout<<"Cod de masina invalid"<<endl;
                        break;
                    }
                    cout<<"Scrieti codul contului ales:";
                    char z2[100];
                    cin.get();
                    cin.get(z2,100);
                    int n=atoi(z2);
                    if(n==0){
                        cout<<"Cod de cont invalid"<<endl;
                        break;
                    }
                    int k=0;
                    for(int i=0;i<vec2.size();i++)
                        for(int j=0;j<vec.size();j++)
                            if(vec2[i].code2==m &&vec[j].code==n){
                                vec2[i].renovare(vec2[i],vec[j]);k=1;
                                }
                    if(k==0)
                        cout<<"Cod invalid"<<endl;
                }
                else
                if(t==6){
                    cout<<"Scrieti codul masinii din care vreti sa copiati:";
                    char z[100];
                    cin.get();
                    cin.get(z,100);
                    int m=atoi(z);
                    if(m==0){
                        cout<<"Cod invalid"<<endl;
                        break;
                    }
                    cout<<"Scrieti codul masinii in care vreti sa copiati:";
                    char z2[100];
                    cin.get();
                    cin.get(z2,100);
                    int n=atoi(z2);
                    if(n==0){
                        cout<<"Cod invalid"<<endl;
                        break;
                    }
                    int k=0;
                    for(int i=0;i<vec2.size();i++)
                        for(int j=0;j<vec2.size();j++)
                            if(vec2[i].code2==m &&vec2[j].code2==n)
                            {
                            k=1;
                            vec2[j]+vec2[i];
                            }
                    if(k==0)
                        cout<<"Cod invalid"<<endl;
                }
                else
                if(t==7){
                    cout<<"Alegeti codul masinii alese:";
                    char z3[100];
                    cin.get();
                    cin.get(z3,100);
                    int n=atoi(z3);
                    cout<<"Alegeti noul model:";
                    char z[100];
                    cin.get();
                    cin.get(z,100);
                    cout<<"Alegeti noua culoare:";
                    char z2[100];
                    cin.get();
                    cin.get(z2,100);
                    string str{z2};
                    cout<<"Alegeti noul kilometraj:";
                    cin.get();
                    cin.get(z2,100);
                    double m=atoi(z2);
                    if(m==0)
                    while(m==0){
                        cout<<"Introduceti o valoare valida"<<endl;
                        cin.get();
                        cin.get(z2,100);
                        m=atoi(z2);
                    }
                    int k=0;
                    for(int i=0;i<vec2.size();i++)
                        if(vec2[i].code2==n){
                        k=1;vec2[i].modificare_masina(z,str,m);
                        }
                    if(k==0)
                        cout<<"Valoare invalida"<<endl;

                }
            }
        }
        else
        if(d==3){
        while(t!=0){
          cout<<"Optiuni:"<<endl;
          cout<<"1) Adaugare mobilier:"<<endl;
          cout<<"2) renovare baie:"<<endl;
          cout<<"3) Informatii renovare:"<<endl;
          cout<<"0) Inapoi"<<endl;
          if(vec.empty()==1)
            cout<<"Niciun cont introdus"<<endl;
        else{
            cout<<"========================================"<<endl;
            cout<<"Conturi introduse:"<<endl;
            for(int i=0;i<vec.size();i++)
                cout<<"Nume cont:"<<vec[i].nume<<", cod unic:"<<vec[i].code<<", fonduri cont:"<<vec[i].balance<<endl;
            cout<<"========================================"<<endl;
        }
        cin>>t;
         if(t==1){
            cout<<"Introduceti codul contului ales:";
            char z[100];
            cin.get();
            cin.get(z,100);
            int m=atoi(z);
            int k=0;
            for(int i=0;i<vec.size();i++)
                if(vec[i].code==m){
                    k=1;mobila.tranzactie(mobila,vec[i]);
                }
            if(k==0)
                cout<<"Cod invalid"<<endl;
         }
         else
         if(t==2){
            cout<<"Introduceti codul contului ales:";
            char z[100];
            cin.get();
            cin.get(z,100);
            int m=atoi(z);
            int k=0;
            for(int i=0;i<vec.size();i++)
                if(vec[i].code==m){
                    k=1;baie.renovare(baie,vec[i]);
                }
            if(k==0)
                cout<<"Cod invalid"<<endl;
         }
         else
         if(t==3){
            if(vec2.empty())
                cout<<"Nici-o masina introdusa"<<endl;
            else
                vec2[0].info_renovare();
            baie.info_renovare();
         }
        }
        }
    }
}

void load_conturi(){
    ifstream f("conturi.txt");
    char s[1000],*p,separator[]=",";
    f.getline(s,1000);
    //cout<<"Cod="<<s<<endl;
    cod=atoi(s);
    f.getline(s,1000);
    while(f.good()){
        p=strtok(s,separator);
        Account cont;
        while(p){
            //cout<<p<<" ";
            delete [] cont.nume;
            cont.nume=new char[strlen(p)+1];
            strcpy(cont.nume,p);
            p=strtok(NULL,separator);
            double m=atoi(p);
            cont.balance=m;
            p=strtok(NULL,separator);
            int n=atoi(p);
            cont.code=n;
            p=strtok(NULL,separator);
            m=0;
            while(p){
                m=atoi(p);cont.tranzactii.push_back(m);
                p=strtok(NULL,separator);
                string str{p};
                cont.actiuni.push_back(str);
                p=strtok(NULL,separator);
            }
            vec.push_back(cont);

        }
        cout<<endl;
        f.getline(s,1000);
    }
    f.close();

}
void save_conturi(){
    ofstream g("conturi.txt");
    g<<cod<<endl;
    for(int i=0;i<vec.size();i++){
        g<<vec[i].get_name()<<","<<vec[i].get_balance()<<","<<vec[i].get_code();
        for(int j=0;j<vec[i].tranzactii_max();j++)
            g<<","<<vec[i].get_tranzactii(j)<<","<<vec[i].get_actiuni(j);
        g<<endl;
    }
    g.close();
}
void save_masini(){
    ofstream g("masini.txt");
    g<<cod2<<endl;
    for(int i=0;i<vec2.size();i++)
        g<<vec2[i].get_name()<<","<<vec2[i].get_code2()<<","<<vec2[i].get_culoare()<<","<<vec2[i].get_kilometraj()<<","<<vec2[i].get_asig()<<endl;
    g.close();

}

void load_masini(){
    ifstream f("masini.txt");
    char s[1000],*p,separator[]=",";
    f.getline(s,1000);
    cod2=atoi(s);
    f.getline(s,1000);
    while(f.good()){
        p=strtok(s,separator);
        Masina Mas;
        while(p){
            delete [] Mas.nume_masina;
            Mas.nume_masina=new char[strlen(p)+1];
            strcpy(Mas.nume_masina,p);
            p=strtok(NULL,separator);
            int m=atoi(p);
            Mas.code2=m;
            p=strtok(NULL,separator);
            string str{p};
            Mas.culoare=str;
            p=strtok(NULL,separator);
            double n=atoi(p);
            Mas.kilometraj=n;
            p=strtok(NULL,separator);
            m=atoi(p);
            Mas.asig=m;
            p=strtok(NULL,separator);
        }
        vec2.push_back(Mas);
        f.getline(s,1000);
    }
    f.close();
}

int main(){
    load_masini();
    load_conturi();
    operatiuni();
    save_conturi();
    save_masini();

    return 0;
}
