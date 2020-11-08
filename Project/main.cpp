#include <iostream>
#include<cstring>
#include<vector>
using namespace std;

class Account{
private:
    double balance;
    char *nume;
    vector <double> tranzactii;
    vector <string> actiuni;
public:
    Account(const Account &x){
        nume=new char[strlen(x.nume)+1];
        strcpy(nume,x.nume);
        balance=x.balance;
        tranzactii=x.tranzactii;
        actiuni=x.actiuni;
        cout<<"Cont "<<nume<<" deschis"<<endl;
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
    Account &operator=(const Account &x){
        balance=x.balance;
        tranzactii=x.tranzactii;
        actiuni=x.actiuni;
    }
    Account(const char *c)
    :nume{nullptr}{
        if(c==nullptr || c==" "){
            delete [] nume;
            nume=new char[4];
            strcpy(nume,"None");
        }
        else
        {
            int nume_size=strlen(c)+1;
            delete [] nume;
            nume=new char[nume_size];
            strcpy(nume,c);
        }
        balance=0;
        if(strcmp(nume,"None")!=0)cout<<"Cont "<<nume<<" deschis"<<endl;
    }
    Account(){
        nume=new char[5];
        strcpy(nume,"Guest");
        cout<<"Cont "<<nume<<" deschis"<<endl;
    }
    void get_info(){
    cout<<endl<<endl<<"==========================================="<<endl;
    cout<<"Nume cont:"<<nume<<endl;
    cout<<"Sold curent:"<<balance<<endl;
    cout<<"Tranzactii efectuate:"<<endl;
    for(int i=0;i<tranzactii.size();i++)
        cout<<i+1<<") "<<tranzactii[i]<<", tip tranzactie:"<<actiuni[i]<<endl;
    cout<<"==========================================="<<endl<<endl;
    }
    void add_balance(double x){
        balance+=x;
        if(x>0){
            tranzactii.push_back(x);
            string c{"Adaugare fonduri"};
            actiuni.push_back(c);}
    }
    bool operator==(double &&x){
        if(balance==x)
            return true;
        else
            return false;
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

    Account &operator=(const Account &&x){
        if(this==&x)
            return *this;
        delete [] nume;
        nume=x.nume;
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
        balance+=x.balance;
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
        cout<<"Cont "<<nume<<" inchis"<<endl;
        delete [] nume;
    }

};
std::istream &operator>>(std::istream &s,Account &d){
    char *str=new char[1000];
    s>>str;
    delete [] d.nume;
    d.nume=new char[strlen(str)+1];
    strcpy(d.nume,str);
    delete [] str;
    return s;
}
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
        Furniture(){cout<<"Incepere mobilare"<<endl;}
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
class Masina{
    private:
       char *nume_masina;
       float pret_renovare;
       string culoare;
       double kilometraj;
       vector <string> reparatii{"Cauciucuri","Culoare","Usi","Faruri","Interior"};
       float pret_reparatii[5] {100,30,70,40,120};
       double cash=0;
       string nume_renovare;
    public:
    friend std::istream &operator>>(std::istream &x,Masina &y);
    Masina(const char *c,const string color="incolor",double t=0)
    :nume_masina{nullptr}{
        if(c==nullptr || c==" "){
            delete [] nume_masina;
            nume_masina=new char[4];
            strcpy(nume_masina,"None");
        }
        else
        {
            int nume_size=strlen(c)+1;
            delete [] nume_masina;
            nume_masina=new char[nume_size];
            strcpy(nume_masina,c);
        }
        pret_renovare=0;
        culoare=color;
        cout<<"Masina "<<nume_masina<<" de culoare "<<color<<" adaugata pentru renovare"<<endl;
        kilometraj=t;}
    Masina &operator=(const Masina &x){
        if(this==&x)
            return *this;
        delete [] nume_masina;
        nume_masina=new char[strlen(x.nume_masina)+1];
        strcpy(nume_masina,x.nume_masina);
        pret_renovare=x.pret_renovare;
        kilometraj=x.kilometraj;
        culoare=x.culoare;
        return *this;
    }
    Masina &operator+(const Masina &x){
        if(this==&x)
            return *this;
        kilometraj+=x.kilometraj;
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
    }
    void get_info(){
        cout<<endl<<endl<<"==========================================="<<endl;
        cout<<"Nume masina:"<<nume_masina<<endl;
        cout<<"Culoare masina:"<<culoare<<endl;
        cout<<"Kilometraj masina:"<<kilometraj<<endl;
        cout<<"==========================================="<<endl<<endl;
    }
    Masina(){
        cout<<"Masina invalida"<<endl;
        nume_masina=new char[4];
        strcpy(nume_masina,"None");
        culoare="None";
        kilometraj=0;
    }
    void tranzactie(Masina &s,Account &d){
        cash=d.get_balance();
        cout<<"Alegeti renovarea pt masina:Cauciucuri,Culoare,Usi,Faruri si Interior(la preturile:100,30,70,40 si respectiv 120)"<<endl;
        cin>>s;
        if(pret_renovare!=0)
        {d.add_balance(-pret_renovare);d.tranzactii.push_back(-pret_renovare);d.actiuni.push_back("Renovat "+nume_renovare+" pentru masina "+nume_masina);}
        s.pret_renovare=0;
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
    ~Masina(){delete [] nume_masina;}
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
class Baie{
    private:
        float pret_renovare;
        vector <string> reparatii{"Cada","Toaleta","Chiuveta","Tavan","Pereti","Podea","Usa"};
        float pret_reparatii[7] {100,150,80,200,120,170,80};
        double cash=0;
        string nume_renovare;
    public:
        friend std::istream &operator>>(std::istream &x,Baie &y);
        Baie(){cout<<"Incepere renovare baie"<<endl;}
    void tranzactie(Baie &s,Account &d){
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
int main(){
    //Account Alex{"paraschiv alexandru"};
    //Alex.get_info();
    //Account Cont{"nume"};
    //Cont.add_balance(523.76);
    //Alex+Cont;
    //++Alex;
    //Alex=Cont;
    //........+ alte functii din clasa Account
    //Alex.get_info();
    //Furniture X;
    //X.tranzactie(X,Alex);
    //Masina A{"BMW","Verde",234342};
    //A.tranzactie(A,Alex);
    //Baie D;
    //D.tranzactie(D,Alex);
    //......+ alte functii din clasele Masina,Baie,Furniture
    //cin>>Alex;
    //Alex.get_info();
    return 0;
}
