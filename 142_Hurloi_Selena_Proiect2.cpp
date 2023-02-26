#include <iostream>
#include<string.h>
#include<vector>
using namespace std;
class IOInterface
{
public:
    virtual istream& read(istream& in) = 0;
    virtual ostream& write(ostream& out) const = 0 ;
};
class Imobil:public IOInterface
{
protected:
    string locatie;
    float suprafata_utila;
    int an_constructie;
    string compartimentare;
    int nr_camere;
    double pret;
public:
    Imobil();
    Imobil(string locatie, float suprafata_utila, int an_constructie, string compartimentare, int nr_camere,double pret );
    Imobil(const Imobil& im);
    friend istream& operator>>(istream& in, Imobil& im);
    friend ostream& operator<<(ostream& out, const Imobil& im );
    istream& read(istream& in);
    ostream& write(ostream& out) const;
    Imobil& operator=(const Imobil& im);
    virtual void calc_pret_in_functie_de_serviciu()=0;
    ~Imobil()
    {

    }
};
Imobil::Imobil()
{
    this->locatie="Not any";
    this->suprafata_utila=0;
    this->an_constructie=0;
    this->compartimentare="Not any";
    this->nr_camere=0;
    this->pret=0;
}
Imobil::Imobil(string locatie, float suprafata_utila, int an_constructie, string compartimentare, int nr_camere,double pret )
{
    this->locatie=locatie;
    this->suprafata_utila=suprafata_utila;
    this->an_constructie=an_constructie;
    this->compartimentare=compartimentare;
    this->nr_camere=nr_camere;
    this->pret=0;
}
Imobil::Imobil(const Imobil& im)
{
    this->locatie=im.locatie;
    this->suprafata_utila=im.suprafata_utila;
    this->an_constructie=im.an_constructie;
    this->compartimentare=im.compartimentare;
    this->nr_camere=im.nr_camere;
    this->pret=im.pret;
}
istream& operator>>(istream& in, Imobil& im)
{
    return im.read(in);
}
ostream& operator<<(ostream& out, const Imobil& im )
{
    return im.write(out);
}
istream& Imobil::read(istream& in)
{
    cout<<"Locatia imobilului: ";
    in>>this->locatie;
    cout<<"Suprafata utila: ";
    in>>this->suprafata_utila;
    cout<<"Anul constructiei: ";
    in>>this->an_constructie;
    cout<<"Comaprtimentarea imobilului: ";
    in>>this->compartimentare;
    cout<<"Numarul de camere: ";
    in>>this->nr_camere;
    cout<<"Pretul pentru serviciul ales: ";
    in>>this->pret;
    return in;

}
ostream& Imobil::write(ostream& out) const
{
    out<<"Locatia imobilului este: "<<this->locatie<<endl;
    out<<"Suprafata utila este: "<<this->suprafata_utila<<endl;
    out<<"Anul constructiei este: "<<this->an_constructie<<endl;
    out<<"Compartimentarea este: "<<this->compartimentare<<endl;
    out<<"Numarul de camere este: "<<this->nr_camere<<endl;
    out<<"Pretul pentru serviciul ales: "<<this->pret<<endl;
    return out;
}
Imobil& Imobil::operator=(const Imobil& im)
{
    if(this!=&im)
    {
        this->locatie=im.locatie;
        this->suprafata_utila=im.suprafata_utila;
        this->an_constructie=im.an_constructie;
        this->compartimentare=im.compartimentare;
        this->nr_camere=im.nr_camere;
        this->pret=im.pret;
    }
    return *this;
}
class Apartament: public virtual Imobil
{
protected:
    bool loc_parcare;
    int etaj;
    int nr_bucatarii;
    int nr_bai;
    int nr_balcoane;
public:
    Apartament();
    Apartament(string locatie,float suprafata_utila, int an_constructie, string compartimentare, int nr_camere,double pret, bool loc_parcare, int etaj, int nr_bucatarii,int nr_bai,int nr_balcoane);
    Apartament(const Apartament& apt);
    friend istream& operator>>(istream& in, Apartament& apt);
    friend ostream& operator<<(ostream& out, const Apartament& apt);
    istream& read(istream& in);
    ostream& write(ostream& out) const;
    Apartament& operator=(const Apartament& apt);
    ~Apartament() {};
    void calc_pret_in_functie_de_serviciu( );
};
void Apartament::calc_pret_in_functie_de_serviciu( )
{
    if(this->loc_parcare==true)
    {
        cout<<"Pretul de inchiriere pe luna in functie de locul de parcare: "<<this->pret+200<<endl;
    }
    else
        cout<<"Pretul de inchiriere pe luna in functie de locul de parcare: "<<this->pret<<endl;

}
Apartament::Apartament():Imobil()
{
    this->loc_parcare=false;
    this->etaj=0;
    this->nr_bucatarii=0;
    this->nr_bai=0;
    this->nr_balcoane=0;
}
Apartament::Apartament(string locatie,float suprafata_utila, int an_constructie, string compartimentare, int nr_camere,double pret, bool loc_parcare, int etaj, int nr_bucatarii,int nr_bai,int nr_balcoane):Imobil(locatie, suprafata_utila, an_constructie, compartimentare, nr_camere,pret)
{
    this->loc_parcare=loc_parcare;
    this->etaj=etaj;
    this->nr_bai=nr_bai;
    this->nr_bucatarii=nr_bucatarii;
    this->nr_balcoane=nr_balcoane;
}
Apartament::Apartament(const Apartament& apt):Imobil(apt)
{
    this->loc_parcare=apt.loc_parcare;
    this->etaj=apt.etaj;
    this->nr_bai=apt.nr_bai;
    this->nr_bucatarii=apt.nr_bucatarii;
    this->nr_balcoane=apt.nr_balcoane;
}
istream& Apartament::read(istream& in)
{
    Imobil::read(in);
    cout<<"Loc parcare (1 / 0): ";
    in>>this->loc_parcare;
    cout<<"Etajul la care se afla: ";
    in>>this->etaj;
    cout<<"Numarul de bai: ";
    in>>this->nr_bai;
    cout<<"Numarul de bucatarii: ";
    in>>this->nr_bucatarii;
    cout<<"Numarul de balcoane: ";
    in>>this->nr_balcoane;
    return in;
}
ostream& Apartament::write(ostream& out) const
{
    Imobil::write(out);
    out<<"Apartamentul beneficiaza sau nu de loc de parcare: "<<this->loc_parcare<<endl;
    out<<"Etajul la care se afla: "<<this->etaj<<endl;
    out<<"Numarul de bai: "<<this->nr_bai<<endl;
    out<<"Numarul de bucatarii: "<<this->nr_bucatarii<<endl;
    out<<"Numarul de balcoane: "<<this->nr_balcoane<<endl;
    return out;
}
istream& operator>>(istream& in, Apartament& apt)
{

    return apt.read(in);

}
ostream& operator<<(ostream& out, const Apartament& apt )
{

    return apt.write(out);

}
Apartament& Apartament::operator=(const Apartament& apt)
{
    if(this!=&apt)
    {
        Imobil::operator=(apt);
        this->loc_parcare=apt.loc_parcare;
        this->etaj=apt.etaj;
        this->nr_bai=apt.nr_bai;
        this->nr_bucatarii=apt.nr_bucatarii;
        this->nr_balcoane=apt.nr_balcoane;
    }
    return *this;
}
class Hotel:public virtual Imobil
{
protected:

    string ora_checkin;
    float rating;
    int nr_nopti;
public:
    Hotel();
    Hotel(string locatie,float suprafata_utila, int an_constructie,string compartimentare,int nr_camere,double pret,string ora_checkin, float rating, int nr_nopti);
    Hotel(const Hotel& hot);
    friend istream& operator>>(istream& in, Hotel& hot);
    friend ostream& operator<<(ostream& out, const Hotel& hot);
    istream& read(istream& in);
    ostream& write(ostream& out) const;
    Hotel& operator=(const Hotel& hot);
    ~Hotel() {};
    void calc_pret_in_functie_de_serviciu( );

};
Hotel::Hotel():Imobil()
{
    this->ora_checkin="not any";
    this->rating=0;
    this->nr_nopti=0;
}
Hotel::Hotel(string locatie,float suprafata_utila, int an_constructie,string compartimentare,int nr_camere,double pret,string ora_checkin, float rating, int nr_nopti):Imobil(locatie, suprafata_utila, an_constructie, compartimentare, nr_camere,pret)
{
    this->ora_checkin=ora_checkin;
    this->rating=rating;
    this->nr_nopti=nr_nopti;
}
Hotel::Hotel(const Hotel& hot):Imobil(hot)
{
    this->ora_checkin=hot.ora_checkin;
    this->rating=hot.rating;
    this->nr_nopti=hot.nr_nopti;
}
istream& Hotel::read(istream& in)
{
    Imobil::read(in);
    cout<<"Ora de check-in: ";
    in>>this->ora_checkin;
    cout<<"Rating-ul: ";
    in>>this->rating;
    cout<<"Numarul de nopti petrecute: ";
    in>>this->nr_nopti;
    return in;
}
ostream& Hotel::write(ostream& out) const
{
    Imobil::write(out);
    out<<"Ora de check-in este: "<<this->ora_checkin<<endl;
    out<<"Rating-ul este: "<<this->rating<<endl;
    out<<"Numarul de nopti petrecute: "<<this->nr_nopti<<endl;
    return out;
}
istream& operator>>(istream& in, Hotel& hot)
{

    return hot.read(in);

}
ostream& operator<<(ostream& out, const Hotel& hot)
{

    return hot.write(out);

}
Hotel& Hotel::operator=(const Hotel& hot)
{
    if(this!=&hot)
    {
        Imobil::operator=(hot);
        this->ora_checkin=hot.ora_checkin;
        this->rating=hot.rating;
        this->nr_nopti=hot.nr_nopti;
    }
    return *this;
}
void Hotel::calc_pret_in_functie_de_serviciu( )
{
    cout<<"Pretul total in functie de noptile petrecute: "<<this->pret*this->nr_nopti<<endl;
}
class ApartamentHotelier : public virtual Apartament, public virtual Hotel
{
protected:
    int capacitate_persoane;
    float taxa_animal;
    bool animal_companie;
public:
    ApartamentHotelier();
    ApartamentHotelier(string locatie, float suprafata_utila, int an_constructie, string compartimentare, int nr_camere,double pret,bool loc_parcare, int etaj, int nr_bucatarii,int nr_bai,int nr_balcoane,string ora_checkin,float rating, int nr_nopti, int capacitate_persoane, float taxa_animal,bool animal_companie);
    ApartamentHotelier(const ApartamentHotelier& ah);
    friend istream& operator>>(istream& in, ApartamentHotelier& ah);
    friend ostream& operator<<(ostream& out, const ApartamentHotelier& ah);
    istream& read(istream& in);
    ostream& write(ostream& out) const;
    ApartamentHotelier& operator=(const ApartamentHotelier& ah);
    ~ApartamentHotelier() {};
    void calc_pret_in_functie_de_serviciu( );

};
ApartamentHotelier::ApartamentHotelier():Imobil(),Apartament(),Hotel()
{
    this->capacitate_persoane=0;
    this->taxa_animal=0;
    this->animal_companie=false;
}
ApartamentHotelier::ApartamentHotelier(string locatie, float suprafata_utila, int an_constructie, string compartimentare, int nr_camere,double pret,bool loc_parcare, int etaj, int nr_bucatarii,int nr_bai,int nr_balcoane,string ora_checkin,float rating, int nr_nopti, int capacitate_persoane, float taxa_animal,bool animal_companie) :Imobil(locatie,suprafata_utila,an_constructie,compartimentare,nr_camere,pret),Apartament(locatie,suprafata_utila,an_constructie,compartimentare,nr_camere,pret,loc_parcare, etaj, nr_bucatarii,nr_bai,nr_balcoane),Hotel(locatie,suprafata_utila,an_constructie,compartimentare,nr_camere,pret,ora_checkin,rating,nr_nopti)
{
    this->capacitate_persoane=capacitate_persoane;
    this->taxa_animal=taxa_animal;
    this->animal_companie=animal_companie;
}
ApartamentHotelier::ApartamentHotelier(const ApartamentHotelier& ah):Imobil(ah),Apartament(ah),Hotel(ah)
{
    this->capacitate_persoane=ah.capacitate_persoane;
    this->taxa_animal=ah.taxa_animal;
    this->animal_companie=ah.animal_companie;
}
ApartamentHotelier& ApartamentHotelier::operator=(const ApartamentHotelier& ah)
{
    if(this!=&ah)
    {
        Apartament::operator=(ah);
        Hotel::operator=(ah);
        this->capacitate_persoane=ah.capacitate_persoane;
        this->taxa_animal=ah.taxa_animal;
        this->animal_companie=ah.animal_companie;
    }
    return *this;
}
istream& ApartamentHotelier::read(istream& in)
{
    Imobil::read(in);
    cout<<"Loc parcare (1 / 0): ";
    in>>this->loc_parcare;
    cout<<"Etajul la care se afla: ";
    in>>this->etaj;
    cout<<"Numarul de bai: ";
    in>>this->nr_bai;
    cout<<"Numarul de bucatarii: ";
    in>>this->nr_bucatarii;
    cout<<"Numarul de balcoane: ";
    in>>this->nr_balcoane;
    cout<<"Ora de check-in: ";
    in>>this->ora_checkin;
    cout<<"Rating-ul: ";
    in>>this->rating;
    cout<<"Numarul de nopti petrecute: ";
    in>>this->nr_nopti;
    cout<<"Numarul maxim de persoane acceptate: ";
    in>>this->capacitate_persoane;
    cout<<"Taxa pentru animale de companie: ";
    in>>this->taxa_animal;
    cout<<"Este prezent sau nu un animal de companie (1 / 0): ";
    in>>this->animal_companie;

    return in;
}
ostream& ApartamentHotelier::write(ostream& out) const
{
    Imobil::write(out);
    out<<"Apartamentul beneficiaza sau nu de loc de parcare: "<<this->loc_parcare<<endl;
    out<<"Etajul la care se afla: "<<this->etaj<<endl;
    out<<"Numarul de bai: "<<this->nr_bai<<endl;
    out<<"Numarul de bucatarii: "<<this->nr_bucatarii<<endl;
    out<<"Numarul de balcoane: "<<this->nr_balcoane<<endl;
    out<<"Ora de check-in este: "<<this->ora_checkin<<endl;
    out<<"Rating-ul este: "<<this->rating<<endl;
    out<<"Numarul de nopti petrecute: "<<this->nr_nopti<<endl;
    out<<"Numarul maxim de persoane: "<<this->capacitate_persoane<<endl;
    out<<"Taxa pentru animale de companie: "<<this->taxa_animal<<endl;
    out<<"Este prezent sau nu un animal de companie (1 / 0): "<<this->animal_companie<<endl;
    return out;

}
istream& operator>>(istream& in, ApartamentHotelier& ah)
{
    return ah.read(in);
}
ostream& operator<<(ostream& out, const ApartamentHotelier& ah )
{
    return ah.write(out);
}
void ApartamentHotelier::calc_pret_in_functie_de_serviciu( )
{
    cout<<"Pretul final in functie de numarul de nopti petrecute si prezenta animalelor de companie: ";
    if (this->animal_companie==true)
        cout<<this->pret*this->nr_nopti+this->taxa_animal;
    else
        cout<<this->pret*this->nr_nopti;
}
class Dezvoltator
{
protected:
    string nume;
    string tip_persoana;
    int nr_proiecte;
    string* numele_proiectelor;
public:
    Dezvoltator();
    Dezvoltator(string nume, string tip_persoana, int nr_proiecte,string* numele_proiectelor);
    friend istream& operator>>(istream& in, Dezvoltator& dez);
    friend ostream& operator<<(ostream& out, const Dezvoltator& dez);
    Dezvoltator& operator=(const Dezvoltator& dez);
    Dezvoltator(const Dezvoltator& dez);
    void  Detine_sau_nu_dezvoltatorul_acest_proiect(string proiect);
    ~Dezvoltator();

};
void Dezvoltator::Detine_sau_nu_dezvoltatorul_acest_proiect(string proiect)
{
    int a=0;
    for(int i=0; i<this->nr_proiecte; i++)
        if(this->numele_proiectelor[i]==proiect)
            a=1;
    if(a==1)
        cout<<"Dezvoltatorul a compus acest proiect"<<endl;
    else
        cout<<"Dezvoltatorul nu a compus acest proiect"<<endl;
}
Dezvoltator::Dezvoltator()
{
    this->nume="Not any";
    this->tip_persoana="Not any";
    this->nr_proiecte=0;
    this->numele_proiectelor=NULL;

}
Dezvoltator::Dezvoltator(string nume, string tip_persoana, int nr_proiecte,string* numele_proiectelor)
{
    this->nume=nume;
    this->tip_persoana=tip_persoana;
    this->nr_proiecte=nr_proiecte;
    this->numele_proiectelor=new string[nr_proiecte];
    for(int i=0; i<nr_proiecte; i++)
    {
        this->numele_proiectelor[i]=numele_proiectelor[i];
    }
}
Dezvoltator::Dezvoltator(const Dezvoltator& dez)
{
    this->nume=dez.nume;
    this->tip_persoana=dez.tip_persoana;
    this->nr_proiecte=dez.nr_proiecte;
    this->numele_proiectelor=new string[dez.nr_proiecte];
    for(int i=0; i<dez.nr_proiecte; i++)
        this->numele_proiectelor[i]=dez.numele_proiectelor[i];
}
Dezvoltator& Dezvoltator::operator=(const Dezvoltator& dez)
{
    if(this!=&dez)
    {

        this->nume=dez.nume;
        this->tip_persoana=dez.tip_persoana;
        this->nr_proiecte=dez.nr_proiecte;
        if(this->numele_proiectelor!=NULL)
            delete [] this->numele_proiectelor;

        this->numele_proiectelor=new string[dez.nr_proiecte];
        for(int i=0; i<dez.nr_proiecte; i++)
            this->numele_proiectelor[i]=dez.numele_proiectelor[i];
    }
    return *this;
}
Dezvoltator::~Dezvoltator()
{
    if(this->numele_proiectelor!=NULL)
        delete [] this->numele_proiectelor;
}
istream& operator>>(istream& in, Dezvoltator& dez)
{
    cout<<"Numele dezvoltatorului este: ";

    in>>dez.nume;
    cout<<"Aceste dezvoltator este persoana fizica/juridica: ";
    in>>dez.tip_persoana;

    cout<<"Numarul de proiecte: ";
    in>>dez.nr_proiecte;
    if(dez.numele_proiectelor!=NULL)
        delete [] dez.numele_proiectelor;
    cout<<"Numele proiectelor sunt: "<<endl;
    dez.numele_proiectelor=new string[dez.nr_proiecte];
    for(int i=0; i<dez.nr_proiecte; i++)
        in>>dez.numele_proiectelor[i];

    return in;
}
ostream& operator<<(ostream& out, const Dezvoltator& dez )
{
    out<<"Numele dezvoltatorului este: "<<dez.nume<<endl;
    out<<"Dezvoltatorul este persoana juridica/fizica: "<<dez.tip_persoana<<endl;
    out<<"Numarul de proiecte ale dezvoltatorului: "<<dez.nr_proiecte<<endl;
    out<<"Proiectele dezvoltatorului: "<<endl;
    for(int i=0; i<dez.nr_proiecte; i++)
    {
        out<<dez.numele_proiectelor[i];
        out<<endl;
    }
    return out;
}
int main()
{
   vector <Dezvoltator> listaDezvoltatori;
    vector<Imobil*> listaImobiliare;
    int k=1,comanada;
    while(k==1)
    {
        cout<<"1-Adaugare Dezvoltator\n2-Adaugare Imobiliare\n3-Stop\n";
        cin>>comanada;
        switch(comanada)
        {
        case 1:
        {
            Dezvoltator a;
            cin>>a;
            listaDezvoltatori.push_back(a);
            int t=1, x;
            while(t==1)
            {
                cout<<"1-Update\n2-Delete\n3-Afisare dezvoltatori\n4-Detine dezvoltatorul acest proiect?\n5-Inapoi la meniul principal\n";
                cin>>x;
                switch(x)
                {
                case 1:
                {
                    Dezvoltator b;
                    cin>>b;
                    cout<<"Introduceti numarul dezvoltatorului caruia ii faceti update: ";
                    int care;
                    cin>>care;
                    listaDezvoltatori[care-1]=b;
                    break;
                }
                case 2:
                {
                    cout<<"Al catelea dezvoltator doriti sa eliminati: ";
                    int i;
                    cin>>i;
                    listaDezvoltatori.erase(listaDezvoltatori.begin()+i);
                    break;
                }
                case 5:
                {
                    t=0;
                    break;
                }
                case 3:
                {
                    for(int i=0; i<listaDezvoltatori.size(); i++)
                        cout<<listaDezvoltatori[i];
                    break;
                }
                case 4:
                {
                    cout<<"Numele proiectului pe care vreti sa-l verificati: ";
                    string proiect;
                    cin>>proiect;
                    cout<<"Al catelea dezvoltator: ";
                    int y;
                    cin>>y;
                    listaDezvoltatori[y-1].Detine_sau_nu_dezvoltatorul_acest_proiect(proiect);
                    break;
                }

                default:
                {
                    cout<<"Ati introdus o valoare gresita\n";
                    break;
                }
                }
            }

            break;
        }
        case 2:
        {

            int tip,t=1;
            while(t==1)
            {
                cout<<"1-Adauga Apartament\n2-Adauga Hotel\n3-Adauga Apartament Hotelier\n4-Intoarcere meniu principal\n5-Afisaza imobiliare\n6-Update\n7-Delete\n8-Pretul final in functie de serviciul ales\n";
                cin>>tip;
                switch(tip)
                {
                case 1:
                {
                    Apartament a;
                    cin>>a;
                    listaImobiliare.push_back(new Apartament(a));
                    break;
                }
                case 2:
                {
                    Hotel a;
                    cin>>a;
                    listaImobiliare.push_back(new Hotel(a));
                    break;
                }
                case 3:
                {
                    ApartamentHotelier a;
                    cin>>a;
                    listaImobiliare.push_back(new ApartamentHotelier(a));
                    break;
                }
                case 4:
                {
                    t=0;
                    break;
                }
                case 5:
                {
                    for(int i=0; i<listaImobiliare.size(); i++)
                        cout<<*listaImobiliare[i];
                    break;
                }
                case 6:
                {
                    cout<<"Al catelea imobiliar doriti sa-i faceti update: ";
                    int nr;
                    cin>>nr;
                    delete listaImobiliare[nr-1];
                    cout<<"Cu ce tip de imobiliar inlocuiti?\n1-Apartament\n2-Hotel\n3-Apartament Hotelier\n";
                    int tip;
                    cin>>tip;
                    switch(tip)
                    {
                    case 1:
                    {
                        Apartament a;
                        cin>>a;
                        listaImobiliare[nr-1]=new Apartament(a);
                        break;

                    }
                    case 2:
                    {
                        Hotel a;
                        cin>>a;
                        listaImobiliare[nr-1]=new Hotel(a);
                        break;

                    }
                    case 3:
                    {
                        ApartamentHotelier a;
                        cin>>a;
                        listaImobiliare[nr-1]=new ApartamentHotelier(a);
                        break;
                    }

                    }
                    break;
                }
                case 7:
                {
                    cout<<"Al catelea imobil doriti sa eliminati: ";
                    int nr;
                    cin>>nr;
                    listaImobiliare.erase(listaImobiliare.begin()+nr);
                    break;

                }
                case 8:
                {
                    cout<<"Numarul imobilului pentru care calculati pretul tipului de serviciu ales: ";
                    int nr;
                    cin>>nr;
                    listaImobiliare[nr-1

                    ]->calc_pret_in_functie_de_serviciu();
                    cout<<endl;
                    break;
                }


                default:
                {
                    cout<<"Ati introdus o valoare gresita\n";
                    break;
                }
                }
            }


            break;
        }
        case 3:
        {
            k=0;
            break;
        }
        default:
        {
            cout<<"Ati introdus o valoare gresita\n";
            break;
        }
        }
    }
    return 0;
}
