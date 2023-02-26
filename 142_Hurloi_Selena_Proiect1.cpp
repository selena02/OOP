#include <iostream>
#include<string.h>
#include<list>
#include<iterator>
using namespace std;
class Client
{
private:
    char* nume;
    string prenume;
    string adresa;

    int nr_comenzi_anterioare;
    string* comenzi_anterioare;

    bool glovo_prime;

    float credit;
public:
    Client();
    Client(char* nume, string prenume, string adresa, int nr_comenzi_anterioare,string* comenzi_anterioar, bool glovo_prime, float credit);
    Client(const Client& c);
    Client& operator= (const Client& c);
    Client(int nr_comenzi_anterioare, string* comezi_anterioare);
    Client (char* nume, string prenume);
    ~Client();
    friend istream& operator>>(istream& in, Client& c);
    friend ostream& operator<<(ostream& out, const Client& c);
    Client& operator++();
    Client operator++(int);
    string get_adresa ()
    {
        return this->adresa;
    }
    void set_adresa(string x)
    {
        this->adresa=x;
    }
    bool get_glovo_prime()
    {
        return this->glovo_prime;
    }
    void Discount()
    {
        if (this->glovo_prime)
            cout<<"Clientul va beneficia de trasport gratuit";
        else cout<<"Clientul nu beneficiaza de transport gratuit";
    }
    bool operator==(const Client& c)
    {
        if (this->nume == c.nume && this->credit == c.credit)
            return true;
        return false;

    }
    explicit operator int()
    {
        return (int)this->credit;
    }
    bool operator<(const Client& c)
    {
        if(this->credit<c.credit)
            return true;
        return false;
    }
    Client operator+(float x)
    {
        Client aux = *this;
        aux.credit = aux.credit + x;
        return aux;

    }
    Client operator-(float x)
    {
        Client aux = *this;
        aux.credit = aux.credit - x;
        return aux;

    }
    friend Client operator-(float x, Client c)
    {
        c.credit = c.credit - x;
        return c;
    }

    friend Client operator+(float x, Client c)
    {
        c.credit = c.credit + x;
        return c;
    }
    Client operator+(Client c)
    {
        c.credit = c.credit + this->credit;
        return c;
    }
    Client operator-(Client c)
    {
        c.credit = c.credit - this->credit;
        return c;
    }
    string operator[](int index);

};
string Client::operator[](int index)
{
    if(0<=index && index<this->nr_comenzi_anterioare)
        return this->comenzi_anterioare[index];
    cout<<"index introdus gresit";
}
Client::Client()
{
    this->nume=new char[strlen("Anonim")+1];
    strcpy(this->nume,"Anonim");
    this->prenume="Anonim";
    this->adresa="nu_exista";
    this->comenzi_anterioare=NULL;
    this->nr_comenzi_anterioare=0;
    this->glovo_prime=false;
    this->credit=0;
}
Client::Client(char* nume, string prenume, string adresa, int nr_comenzi_anterioare,string* comenzi_anterioare, bool glovo_prime, float credit)
{
    this->nume=new char[strlen(nume)+1];
    strcpy(this->nume,nume);
    this->prenume=prenume;
    this->adresa=adresa;
    this-> nr_comenzi_anterioare=nr_comenzi_anterioare;
    this->comenzi_anterioare=new string [nr_comenzi_anterioare];
    for(int i=0; i<this->nr_comenzi_anterioare; i++)
        this->comenzi_anterioare[i]=comenzi_anterioare[i];
    this->glovo_prime=glovo_prime;
    this->credit=credit;
}
Client::Client(const Client& c)
{
    this->nume=new char[strlen(c.nume)+1];
    strcpy(this->nume,c.nume);
    this->prenume=c.prenume;
    this->adresa=c.adresa;
    this-> nr_comenzi_anterioare=c.nr_comenzi_anterioare;
    this->comenzi_anterioare=new string [c.nr_comenzi_anterioare];
    for(int i=0; i<this->nr_comenzi_anterioare; i++)
        this->comenzi_anterioare[i]=c.comenzi_anterioare[i];
    this->glovo_prime=c.glovo_prime;
    this->credit=c.credit;
}

Client& Client::operator=(const Client& c)
{
    if(this!=&c)
    {
        if(this->nume!=NULL)
            delete[]this->nume;
        if (this->comenzi_anterioare!=NULL)
            delete[]this->comenzi_anterioare;
        this->nume=new char[strlen(c.nume)+1];
        strcpy( this->nume, c.nume);
        this->prenume=c.prenume;
        this->adresa=c.adresa;
        this-> nr_comenzi_anterioare=c.nr_comenzi_anterioare;
        this->comenzi_anterioare=new string [c.nr_comenzi_anterioare];
        for(int i=0; i<this->nr_comenzi_anterioare; i++)
            this->comenzi_anterioare[i]=c.comenzi_anterioare[i];
        this->glovo_prime=c.glovo_prime;
        this->credit=c.credit;

    }
    return *this;
}
Client::Client(int nr_comenzi_anterioare, string* comezi_anterioare)
{
    this->nr_comenzi_anterioare=nr_comenzi_anterioare;
    this->comenzi_anterioare=new string [nr_comenzi_anterioare];
    for(int i=0; i<this->nr_comenzi_anterioare; i++)
        this->comenzi_anterioare[i]=comenzi_anterioare[i];
}
Client::Client (char* nume, string prenume)
{
    this->nume=new char[strlen(nume)+1];
    strcpy(this->nume,nume);
    this->prenume=prenume;
}
istream& operator>>(istream& in, Client& c)
{
    cout << "Nume: ";

    char nume[200];
    in >> nume;

    if (c.nume != NULL)
    {
        delete[] c.nume;
    }

    c.nume = new char[strlen(nume) + 1];
    strcpy(c.nume, nume);

    cout << "\nPrenume: ";
    in >> c.prenume;

    cout<<"\nAdresa: ";
    in>> c.adresa;

    cout<<"\nNr Comenzi Anterioare :";
    in>>c.nr_comenzi_anterioare;

    if (c.comenzi_anterioare!=NULL)
        delete[] c.comenzi_anterioare;
    c.comenzi_anterioare= new string[c.nr_comenzi_anterioare];
    for(int i=0; i<c.nr_comenzi_anterioare; i++)
    {
        cout<<"\nComanda numarul "<<i+1<<":";
        in>>c.comenzi_anterioare[i];
    }

    cout << "\nGlovo Prime (1 / 0): ";
    in >>c.glovo_prime;

    cout<<"\nCreditul din portofelul virtual al utilizatorului: ";
    in>>c.credit;
    return in;
}
ostream& operator<<(ostream& out, const Client& c)
{
    out<<endl;
    out << "Nume: " << c.nume << '\n';
    out <<"Prenume: "<<c.prenume<<'\n';
    out<<"Adresa: "<<c.adresa<<'\n';
    out<<"Numar comenzi anterioare: "<<c.nr_comenzi_anterioare<<'\n';
    for (int i=0; i<c.nr_comenzi_anterioare; i++)
        out << "Comanda cu numarul  " << (i + 1) << ": " << c.comenzi_anterioare[i]<<'\n';
    out<<"Clientul are/nu are Glovo Prime(1/0): "<<c.glovo_prime<<'\n';
    out<<"Creditul din portofelul virtual al utilizatorului: "<<c.credit<<'\n';
    return out;
}
Client& Client::operator++()// pre_incremet
{
    this->credit++;
    return *this;

}
Client Client::operator++(int)// post_increment
{
    Client aux = *this;
    this->credit++;
    return aux;
}
Client::~Client()
{
    if(this->nume!=NULL)
        delete[] this->nume;
    if(this->comenzi_anterioare!=NULL)
        delete[] this->comenzi_anterioare;

}
class Restaurant
{
private:
    string nume_restaurant;
    string arie_livrare;
    int nr_produse;
    string* produse;
    float rating;
    int total_comenzi;
public:
    Restaurant();
    Restaurant(string nume_restaurant,string arie_livrare, int nr_produse, string* produse, float rating,int total_comenzi);
    Restaurant(const Restaurant& r);
    Restaurant& operator= (const Restaurant& r);
    Restaurant(int nr_produse, string* produse);
    Restaurant (string nume_restaurant, string arie_livrare);
    ~Restaurant();
    friend istream& operator>>(istream& in, Restaurant& r);
    friend ostream& operator<<(ostream& out, const Restaurant& r);
    Restaurant& operator++();
    Restaurant operator++(int);
    void set_nume_restaurant(string x)
    {
        this->nume_restaurant=x;
    }
    string get_nume_restaurant()
    {
        return this->nume_restaurant;
    }
    void arie_de_acoperire(Client a)
    {
        if (this->arie_livrare==a.get_adresa())
            cout<<"Restaurantul livreaza in aria dvs. de acoperire";
        else cout<<"Restaurantul nu livreaza in aria dvs de acoperire";

    }
    bool operator==(const Restaurant& r)
    {
        if (this->nume_restaurant == r.nume_restaurant && this->arie_livrare == r.arie_livrare)
            return true;
        return false;

    }
    explicit operator int()
    {
        return (int)this->rating;
    }
    bool operator<(const Restaurant& r)
    {
        if(this->rating<r.rating)
            return true;
        return false;
    }

    Restaurant operator-(int x)
    {
        Restaurant aux = *this;
        aux.total_comenzi = aux.total_comenzi - x;
        return aux;

    }
    friend Restaurant operator+(int x, Restaurant r)
    {
        r.total_comenzi = r.total_comenzi + x;
        return r;
    }
    friend Restaurant operator-(int x, Restaurant r)
    {
        r.total_comenzi = r.total_comenzi - x;
        return r;
    }

    Restaurant operator-(Restaurant r)
    {
        r.total_comenzi = r.total_comenzi - this->total_comenzi;
        return r;
    }
    string operator[](int index);
};
string Restaurant::operator[](int index)
{
    if(0<=index&& index<this->nr_produse)
        return this->produse[index];
    cout<<"index introdus gresit";
}
Restaurant::Restaurant()
{
    this->nume_restaurant="anonim";
    this->arie_livrare="anonim";
    this->nr_produse=0;
    this->produse=NULL;
    this->rating=0;
    this->total_comenzi=0;
}
Restaurant::Restaurant(string nume_restaurant,string arie_livrare, int nr_produse, string* produse, float rating,int total_comenzi)
{
    this->nume_restaurant=nume_restaurant;
    this->arie_livrare=arie_livrare;
    this->nr_produse=nr_produse;
    this->produse= new string[nr_produse];
    for(int i=0; i<this->nr_produse; i++)
        this->produse[i]=produse[i];
    this->rating=rating;
    this->total_comenzi=0;
}
Restaurant::Restaurant(const Restaurant& r)
{
    this->nume_restaurant=r.nume_restaurant;
    this->arie_livrare=r.arie_livrare;
    this->nr_produse=r.nr_produse;
    this->produse= new string[r.nr_produse];
    this->rating=r.rating;
    for(int i=0; i<this->nr_produse; i++)
        this->produse[i]=r.produse[i];
    this->total_comenzi=r.total_comenzi;
}
Restaurant& Restaurant::operator=(const Restaurant& r)
{
    if (this!=&r)
    {
        if(this->produse!=NULL)
            delete[] this->produse;
        this->nume_restaurant=r.nume_restaurant;
        this->arie_livrare=r.arie_livrare;
        this->nr_produse=r.nr_produse;
        this->rating=r.rating;
        this->produse= new string[r.nr_produse];
        for(int i=0; i<this->nr_produse; i++)
            this->produse[i]=r.produse[i];
        this->total_comenzi=r.total_comenzi;

    }
    return *this;
}
istream& operator>>(istream& in, Restaurant& r)
{
    cout<<"\nNumele restaurantului: ";
    in>>r.nume_restaurant;
    cout<<"\nAria de livrarea a restaurantului: ";
    in>>r.arie_livrare;

    cout<<"\nNumarul de produse: ";
    in>>r.nr_produse;

    if(r.produse!=NULL)
        delete[]r.produse;
    r.produse=new string[r.nr_produse];
    for(int i=0; i<r.nr_produse; i++)
    {
        cout<<"\nProdusul:  "<<i+1<<": ";
        in>>r.produse[i];
    }
    cout<<"\nRatingul restaurantului: ";
    in>>r.rating;

    cout<<"\nTotalul de comenzi: ";

    in>>r.total_comenzi;

    return in;
}
ostream& operator<<(ostream& out, const Restaurant& r)
{
    out<<"Numele restaurantului: "<<r.nume_restaurant<<endl;
    out<<"Aria de livrare a restaurantului: "<<r.arie_livrare<<endl;
    out<<"Numarul de produse: "<<r.nr_produse<<endl;
    for(int i=0; i<r.nr_produse; i++)
        out<<"Produsul: "<<i+1<<" "<<r.produse[i]<<endl;
    out<<"Ratingul restaurantului: "<<r.rating<<endl;
    out<<"Totalul de comenzi: "<<r.total_comenzi;

    return out;
}
Restaurant::Restaurant(int nr_produse, string* produse)
{
    this->nr_produse=nr_produse;
    this->produse= new string[nr_produse];
    for(int i=0; i<this->nr_produse; i++)
        this->produse[i]=produse[i];

}
Restaurant::Restaurant (string nume_restaurant, string arie_livrare)
{
    this->nume_restaurant=nume_restaurant;
    this->arie_livrare=arie_livrare;
}
Restaurant& Restaurant::operator++()
{
    this->total_comenzi++;
    return *this;
}
Restaurant Restaurant::operator++(int)// post_increment
{
    Restaurant aux = *this;
    this->total_comenzi++;
    return aux;
}
Restaurant::~Restaurant()
{
    if(this->produse!=NULL)
        delete[] this->produse;
}
class Comanda
{
private:
    Restaurant nume_restaurant;
    Client client;
    float pret_comanda;
    int nr_produse;
    string* produse;
    const int id_Comanda;
    static int contorId;
public:
    Comanda();
    Comanda(Restaurant nume_restaurant, Client client, float pret_comanda, int nr_produse, string* produse);
    Comanda(const Comanda& ord);
    Comanda& operator= (const Comanda& ord);
    Comanda(int nr_produse, string* produse);
    Comanda (float pret_comanda);
    ~Comanda();
    friend istream& operator>>(istream& in, Comanda& ord);
    friend ostream& operator<<(ostream& out, const Comanda& ord);
    Comanda& operator++();
    Comanda operator++(int);
    float Reducere()
    {
        if(this->client.get_glovo_prime()==true)
            this->pret_comanda=this->pret_comanda-5;
        return this->pret_comanda;
    }
    bool operator==(const Comanda& ord)
    {
        if(this->id_Comanda==ord.id_Comanda)
            return true;
        return false;
    }
    explicit operator int()
    {
        return (int)this->pret_comanda;
    }
    bool operator<(const Comanda& ord)
    {
        if(this->nr_produse<ord.nr_produse)
            return true;
        return false;
    }
    Comanda operator+(float x)
    {
        Comanda aux = *this;
        aux.pret_comanda = aux.pret_comanda + x;
        return aux;
    }
    Comanda operator-(float x)
    {
        Comanda aux = *this;
        aux.pret_comanda = aux.pret_comanda - x;
        return aux;
    }
    friend Comanda operator+(float x, Comanda ord)
    {
        ord.pret_comanda = ord.pret_comanda + x;
        return ord;
    }
    friend Comanda operator-(float x, Comanda ord)
    {
        ord.pret_comanda = ord.pret_comanda - x;
        return ord;
    }
    Comanda operator+(Comanda ord)
    {
        ord.pret_comanda = ord.pret_comanda + this->pret_comanda;
        return ord;
    }
    Comanda operator-(Comanda ord)
    {
        ord.pret_comanda = ord.pret_comanda - this->pret_comanda;
        return ord;
    }
    string operator[](int index);
};
string Comanda::operator[](int index)
{
    if(0<=index&&index<this->nr_produse)
        return this->produse[index];
     cout<<"index introdus gresit";
}
int Comanda::contorId=1000;
Comanda::Comanda():id_Comanda(contorId++)
{
    Restaurant nume_restaurant;
    this->nume_restaurant=nume_restaurant;
    Client client;
    this->client=client;
    this->pret_comanda=0;
    this->nr_produse=0;
    this->produse=NULL;
}
Comanda::Comanda(Restaurant nume_restaurant, Client client, float pret_comanda,int nr_produse, string* produse):id_Comanda(contorId++)
{
    this->nume_restaurant=nume_restaurant;
    this->client=client;
    this->pret_comanda=pret_comanda;
    this->nr_produse=nr_produse;
    this->produse=new string[nr_produse];
    for(int i=0; i<this->nr_produse; i++)
        this->produse[i]=produse[i];

}
Comanda::Comanda(const Comanda& ord):id_Comanda(ord.id_Comanda)
{
    this->nume_restaurant=ord.nume_restaurant;
    this->client=ord.client;
    this->pret_comanda=ord.pret_comanda;
    this->nr_produse=ord.nr_produse;
    this->produse=new string[ord.nr_produse];
    for(int i=0; i<this->nr_produse; i++)
        this->produse[i]=ord.produse[i];
}
Comanda& Comanda::operator=(const Comanda& ord)
{
    if(this!=&ord)
    {

        if (this->produse!=NULL)
            delete[] this->produse;
        this->nume_restaurant=ord.nume_restaurant;
        this->client=ord.client;
        this->pret_comanda=ord.pret_comanda;
        this->nr_produse=ord.nr_produse;
        this->produse=new string[ord.nr_produse];
        for(int i=0; i<this->nr_produse; i++)
            this->produse[i]=ord.produse[i];

    }
    return *this;
}
Comanda::Comanda(int nr_produse, string* produse):id_Comanda(contorId++)
{
    this->nr_produse=nr_produse;
    this->produse=new string[nr_produse];
    for(int i=0; i<this->nr_produse; i++)
        this->produse[i]=produse[i];
}
Comanda::Comanda (float pret_comanda):id_Comanda(contorId++)
{
    this->pret_comanda=pret_comanda;
}
istream& operator>>(istream& in, Comanda& ord)
{

    cout << "\nRestaurantul comenzii: ";

    in>>ord.nume_restaurant;

    cout<<"\nClientul comenzii: ";

    in>>ord.client;

    cout<<"\nPretul Comenzii: ";

    in>>ord.pret_comanda;

    cout<<"\nNumar produse din comanda: ";

    in>>ord.nr_produse;

    if (ord.produse!=NULL)
        delete[] ord.produse;
    ord.produse= new string[ord.nr_produse];
    for(int i=0; i<ord.nr_produse; i++)
    {
        cout<<"\nProdusul numarul: "<<i+1<<":";
        in>>ord.produse[i];
    }
    return in;
}
ostream& operator<<(ostream& out, const Comanda& ord)
{
    out<<endl;
    out<<"Id-ul comenzii este: "<<ord.id_Comanda<<endl;
    out<<"Restaurantul comenzii :\n"<<ord.nume_restaurant;
    out<<"\nClientul comenzii: "<<ord.client;
    out<<"Pretul comenzii: "<<ord.pret_comanda<<endl;
    out<<"Numarul produselor din comanda: "<<ord.nr_produse<<endl;
    for(int i=0; i<ord.nr_produse; i++)
        cout<<"Produsul numarul: "<<i+1<<": "<<ord.produse[i]<<endl;
    return out;
}
Comanda& Comanda::operator++()
{
    this->pret_comanda++;
    return *this;
}
Comanda Comanda::operator++(int)// post_increment
{
    Comanda aux = *this;
    this->pret_comanda++;
    return aux;
}
Comanda::~Comanda()
{

    if(this->produse!=NULL)
        delete[] this->produse;

}
class Curier
{
private:
    string nume;
    string prenume;
    float salariu;
    char initiatala_tatalui;
    int nr_comenzi_anterioare;
    list <Comanda> comenzi;
public:
    Curier();
    Curier(string nume, string prenume, float salariu,char initiatala_tatalui, int nr_comenzi_anterioare, list<Comanda> comenzi);
    Curier(const Curier& liv);
    Curier& operator=(const Curier& liv);
    Curier(string nume, string prenume);
    Curier(int nr_comenzi_anterioare, list<Comanda> comenzi);
    friend istream& operator>>(istream& in, Curier& liv);
    friend ostream& operator<<(ostream& out, const Curier& liv);
    Curier& operator++();
    Curier operator++(int);
    float crestere_salariu()
    {
        if(this->nr_comenzi_anterioare>=100)
            this->salariu=this->salariu+100;
        return this->salariu;

    }
    bool operator==(const Curier& liv)
    {
        if (this->nume == liv.nume && this->prenume==liv.prenume &&this->salariu==liv.salariu )
            return true;
        return false;

    }
    explicit operator int()
    {
        return (int)this->salariu;
    }
    bool operator<(const Curier& liv)
    {
        if(this->salariu<liv.salariu)
            return true;
        return false;
    }
    Curier operator+(float x)
    {
        Curier aux = *this;
        aux.salariu = aux.salariu + x;
        return aux;

    }
    Curier operator-(float x)
    {
        Curier aux = *this;
        aux.salariu = aux.salariu - x;
        return aux;

    }
    friend Curier operator+(float x, Curier liv)
    {
        liv.salariu = liv.salariu + x;
        return liv;
    }
    friend Curier operator-(float x, Curier liv)
    {
        liv.salariu = liv.salariu - x;
        return liv;
    }
    Curier operator+(Curier liv)
    {
        liv.salariu = liv.salariu + this->salariu;
        return liv;
    }
    Curier operator-(Curier liv)
    {
        liv.salariu = liv.salariu - this->salariu;
        return liv;
    }
    Comanda operator[](int index) {
        list<Comanda>::iterator it = this->comenzi.begin();
        advance(it, index);
        return *it;
    }
    friend Curier operator+ (Curier m, Comanda& a) {
        m.comenzi.push_back(a);
        return m;
    }
    friend Curier operator+ (Comanda& a, Curier m) {
        m.comenzi.push_back(a);
        return m;
    }

};

Curier::Curier()
{
    this->nume="Anonim";
    this->prenume="Anonim";
    this->salariu=0;
    this->initiatala_tatalui='W';
    this->nr_comenzi_anterioare=0;
    this->comenzi={};
}
Curier::Curier(string nume, string prenume, float salariu,char initiatala_tatalui, int nr_comenzi_anterioare, list<Comanda> comenzi)
{
    this->nume=nume;
    this->prenume=prenume;
    this->salariu=salariu;
    this->initiatala_tatalui=initiatala_tatalui;
    this->nr_comenzi_anterioare=nr_comenzi_anterioare;
    this->comenzi=comenzi;

}
Curier::Curier(string nume, string prenume)
{
    this->nume=nume;
    this->prenume=prenume;
}
Curier::Curier(const Curier& liv)
{
    this->nume= liv.nume;
    this->prenume=liv.prenume;
    this->salariu=liv.salariu;
    this->initiatala_tatalui=liv.initiatala_tatalui;
    this->nr_comenzi_anterioare=liv.nr_comenzi_anterioare;
    this->comenzi=comenzi;

}
Curier::Curier(int nr_comenzi_anterioare, list<Comanda> comenzi)
{
    this->nr_comenzi_anterioare=nr_comenzi_anterioare;
    this->comenzi=comenzi;

}
Curier& Curier::operator=(const Curier& liv)
{
    if (this!=&liv)
    {

        this->nume= liv.nume;
        this->prenume=liv.prenume;
        this->salariu=liv.salariu;
        this->initiatala_tatalui=liv.initiatala_tatalui;
        this->nr_comenzi_anterioare=liv.nr_comenzi_anterioare;
        this->comenzi=liv.comenzi;
    }
    return *this;
}

istream& operator>>(istream& in, Curier& liv)
{
    cout<<"Datale de identificare ale curierului: \n";
    cout<<"\nNumele curierului: ";
    in>>liv.nume;
    cout<<"\nPrenumele curierului: ";
    in>>liv.prenume;
    cout<<"\nSalariul curierului: ";
    in>>liv.salariu;
    cout<<"\nInitiala tatalui: ";
    in>>liv.initiatala_tatalui;
    cout<<"\nNumar de comenzi efectuate de curier: ";
    in>>liv.nr_comenzi_anterioare;
    int k=1,comanda;
    while(k==1)
        {
            cout<<"1-Add an order\n";
            cout<<"2_Stop\n";
            cin>>comanda;
            switch(comanda)
            {
            case 1:
                {
                    Comanda a;
                    cin>>a;
                    liv.comenzi.push_back(a);
                    break;
                }
            case 2:
                {
                    k=0;
                    break;
                }
            default:
                {
                    cout<<"Comanda incoreta\n";
                    break;
                }

            }
        }

    return in;
}
ostream& operator<<(ostream& out,const Curier& liv)
{
    out<<"\nNumele curierului: "<<liv.nume;
    out<<"\nPrenumele Curierului: "<<liv.prenume;
    out<<"\nSalariul curierului: "<<liv.salariu;
    out<<"\nInitiala tatalui: "<<liv.initiatala_tatalui;
    out<<"\nNumarul de comenzi efectuate: "<<liv.nr_comenzi_anterioare;
    out<<"\nComenzile curierului sunt: "<<endl;
    for (auto const& i : liv.comenzi) {
    cout << i<<endl;
}
    return out;
}
Curier& Curier::operator++()
{
    this->salariu++;
    return *this;
}
Curier Curier::operator++(int)
{
    Curier aux = *this;
    this->salariu++;
    return aux;
}
int main()
{
    Curier a;
    cin>>a;
    cout<<a;

}
