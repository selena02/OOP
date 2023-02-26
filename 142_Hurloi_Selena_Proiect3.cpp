#include <iostream>
#include <cstring>
#include <typeinfo>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <iterator>
#include <map>
using namespace std;
template <class T>
class Comparare
{
    T first, second;
public:
    Comparare(T a, T b)
    {
        first=a;
        second=b;
    }
    T bigger()
    {
        return(first>second?first:second);
    }
};
template<typename T>
int aduna_salarii(T a, T b)
{
    int c=a->calculeaza_salariul();
    int d=b->calculeaza_salariul();
    return c+d;
}
template<typename T>
void activitati_extra(T a)
{
    int c=a.get_nr_activitati();
    int d=a.get_target();
    if (c<d)
        cout<<"Mai trebuiau atinse: "<<d-c<<" target-uri";
    else
        cout<<"S-au efectuat: "<<c-d<<" target-uri in plus";
}
class IOInterface
{
public:
    virtual istream& read(istream& in) = 0;
    virtual ostream& write(ostream& out) const = 0 ;
};
class Colaborator : public IOInterface
{
protected:
    const int id_Colaborator;
    static int contorId;
    char *nume;
    string prenume;
    float salariu_baza;
public:
    Colaborator();
    Colaborator(char* nume,string prenume, float salariu_baza);
    Colaborator(const Colaborator& c);
    Colaborator& operator=(const Colaborator& c);
    ~Colaborator()
    {
        if(this->nume!=NULL)
            delete[] this->nume;

    }
    friend istream& operator>>(istream& in, Colaborator& im);
    friend ostream& operator<<(ostream& out, const Colaborator& im );
    istream& read(istream& in);
    ostream& write(ostream& out) const;
    string get_prenume()
    {
        return this->prenume;
    }
    virtual int calculeaza_salariul()=0;
    float get_salariu_baza()
    {
        return this->salariu_baza;
    }
};
int Colaborator::contorId=1000;
Colaborator::Colaborator():id_Colaborator(contorId++)
{
    this->nume=new char[strlen("Anonim")+1];
    strcpy(this->nume,"Anonim");
    this->prenume="Not any";
    this->salariu_baza=0;
}
Colaborator::Colaborator(char* nume,string prenume, float salariu_baza):id_Colaborator(contorId++)
{
    this->nume=new char[strlen(nume)+1];
    strcpy(this->nume,nume);
    this->prenume=prenume;
    this->salariu_baza=salariu_baza;
}
Colaborator::Colaborator(const Colaborator& c):id_Colaborator(c.contorId)
{
    this->nume=new char[strlen(c.nume)+1];
    strcpy(this->nume,c.nume);
    this->prenume=c.prenume;
    this->salariu_baza=c.salariu_baza;
}
Colaborator& Colaborator::operator=(const Colaborator& c)
{
    if(this!=&c)
    {
        if(this->nume!=NULL)
            delete[]this->nume;
        this->nume=new char[strlen(c.nume)+1];
        strcpy( this->nume, c.nume);
        this->prenume=c.prenume;
        this->salariu_baza=c.salariu_baza;
    }
    return *this;
}
istream& operator>>(istream& in, Colaborator& c)
{
    return c.read(in);
}
ostream& operator<<(ostream& out, const Colaborator& c)
{
    return c.write(out);
}
istream& Colaborator::read(istream& in)
{
    cout<<"Numele Persoanei: ";
    while(true)
    {
        try
        {
            char nume[200];
            in >> nume;
            if (this->nume != NULL)
            {
                delete[] this->nume;
            }
            this->nume = new char[strlen(nume) + 1];
            strcpy(this->nume, nume);
            if(!(this->nume[0]>='A'&&this->nume[0]<='Z'))
                throw string("Numele trebuie sa inceapa cu litera mare. Rescrieti!");
            else break;
        }
        catch (string s)
        {
            cout << s << '\n';
        }
    }
    cout<<"Prenumele Persoanei: ";
    while(true)
    {
        try
        {
            in>>this->prenume;
            if(!(this->prenume[0]>='A'&&this->prenume[0]<='Z'))
                throw string("Prenumele trebuie sa inceapa cu litera mare! Rescrieti!");
            else break;
        }
        catch (string s)
        {
            cout << s << '\n';
        }
    }
    cout<<"Salariul de baza al persoanei: ";
    while(true)
    {
        try
        {
            in>>this->salariu_baza;
            if(this->salariu_baza<=0)
                throw string("Are si el nevoie de bani");
            else break;
        }
        catch (string s)
        {
            cout << s << '\n';
        }
    }
    return in;
}
ostream& Colaborator::write(ostream& out) const
{
    out<<"Numele persoanei este: ";
    out<<this->nume<<endl;
    out<<"Prenumele Persoanei este: ";
    out<<this->prenume<<endl;
    out<<"ID-ul persoanei este: ";
    out<<this->id_Colaborator<<endl;
    out<<"Salariul de baza al persoanei este: ";
    out<<this->salariu_baza<<endl;
    return out;

}
class Inginer: public virtual Colaborator
{
protected:
    int target;
    int nr_activitati;
public:
    Inginer();
    Inginer(char *nume, string prenume, float salariu_baza, int target, int nr_activitati);
    Inginer(const Inginer& i);
    friend istream& operator>>(istream& in, Inginer& i);
    friend ostream& operator<<(ostream& out, const Inginer& i);
    istream& read(istream& in);
    ostream& write(ostream& out) const;
    Inginer& operator=(const Inginer& i);
    ~Inginer() {}
    int get_nr_activitati()
    {
        return this->nr_activitati;
    }
    int calculeaza_salariul();
    int get_target()
    {
        return this->target;
    }
};
int Inginer::calculeaza_salariul()
{
    if (this->nr_activitati>=this->target)
    {
        return((this->nr_activitati-this->target)*100+this->salariu_baza);
    }

    else return(this->salariu_baza);
}
Inginer::Inginer():Colaborator()
{
    this->target=0;
    this->nr_activitati=0;
}

Inginer::Inginer(char *nume, string prenume, float salariu_baza, int target, int nr_activitati):Colaborator(nume, prenume, salariu_baza)
{
    this->target=target;
    this->nr_activitati=nr_activitati;
}

Inginer& Inginer::operator=(const Inginer& i)
{
    if(this!=&i)
    {
        Colaborator::operator=(i);
        this->target=i.target;
        this->nr_activitati=i.nr_activitati;
    }
    return *this;
}
istream& Inginer::read(istream& in)
{
    Colaborator::read(in);
    cout<<"Numarul de target-uri obligatorii: ";
    in>>this->target;
    cout<<"Numarul de activitati atinse de inginer: ";
    in>>this->nr_activitati;
    return in;
}
ostream& Inginer::write(ostream& out) const
{
    Colaborator::write(out);
    out<<"Numarul de target-uri obligatorii: "<<this->target<<endl;
    out<<"Numarul de activitati atinse de inginer: "<<this->nr_activitati<<endl;
    return out;
}
istream& operator>>(istream& in, Inginer& i)
{

    return i.read(in);

}
ostream& operator<<(ostream& out, const Inginer& i)
{

    return i.write(out);

}
Inginer::Inginer(const Inginer& i):Colaborator(i)
{
    this->target=i.target;
    this->nr_activitati=i.nr_activitati;
}
class Sef: public virtual Colaborator
{
protected:
    int nr_persoane_echipa;
public:
    Sef();
    Sef(char *nume, string prenume, float salariu_baza, int nr_persoane_echipa);
    Sef(const Sef& s);
    friend istream& operator>>(istream& in, Sef& s);
    friend ostream& operator<<(ostream& out, const Sef& s);
    istream& read(istream& in);
    ostream& write(ostream& out) const;
    Sef& operator=(const Sef& s);
    ~Sef() {}
    int calculeaza_salariul();
};
int Sef::calculeaza_salariul()
{
    return(this->salariu_baza+100*this->nr_persoane_echipa);
}
Sef::Sef():Colaborator()
{
    this->nr_persoane_echipa=0;
}
Sef::Sef(char *nume, string prenume, float salariu_baza, int nr_persoane_echipa):Colaborator(nume, prenume, salariu_baza)
{

    this->nr_persoane_echipa=0;
}
Sef& Sef::operator=(const Sef& s)
{
    if(this!=&s)
    {
        Colaborator::operator=(s);
        this->nr_persoane_echipa=s.nr_persoane_echipa;
    }
    return *this;
}
istream& Sef::read(istream& in)
{
    Colaborator::read(in);
    cout<<"Numarul de oameni din echipa sefului: ";
    in>>this->nr_persoane_echipa;
    return in;
}
ostream& Sef::write(ostream& out) const
{
    Colaborator::write(out);
    out<<"Numarul de oameni din echipa sefului: "<<this->nr_persoane_echipa<<endl;
    return out;
}
istream& operator>>(istream& in, Sef& s)
{

    return s.read(in);

}
ostream& operator<<(ostream& out, const Sef& s)
{

    return s.write(out);

}
Sef::Sef(const Sef& s):Colaborator(s)
{
    this->nr_persoane_echipa=s.nr_persoane_echipa;
}
class InginerSef: public virtual Inginer, public virtual Sef
{
protected:
    int nr_proiecte;
public:
    InginerSef();
    InginerSef(char* nume,string prenume,float salariu_baza,int target,int nr_activitati,int nr_persoane_echipa,int nr_proiecte);
    InginerSef(const InginerSef& is);
    friend istream& operator>>(istream& in, InginerSef& is);
    friend ostream& operator<<(ostream& out, const InginerSef& is);
    istream& read(istream& in);
    ostream& write(ostream& out) const;
    InginerSef& operator=(const InginerSef& is);
    ~InginerSef() {};
    int calculeaza_salariul( );
};
InginerSef::InginerSef():Colaborator(),Inginer(),Sef()
{
    this->nr_proiecte=0;
}

InginerSef::InginerSef(char* nume,string prenume,float salariu_baza,int target,int nr_activitati,int nr_persoane_echipa,int nr_proiecte):Colaborator(nume,prenume,salariu_baza),Inginer(nume,prenume,salariu_baza,target,nr_activitati),Sef(nume,prenume,salariu_baza,nr_persoane_echipa)
{
    this->nr_proiecte=nr_proiecte;
}

InginerSef::InginerSef(const InginerSef& is):Colaborator(is),Inginer(is),Sef(is)
{
    this->nr_proiecte=is.nr_proiecte;
}

InginerSef& InginerSef::operator=(const InginerSef& is)
{
    if(this!=&is)
    {
        Inginer::operator=(is);
        Sef::operator=(is);
        this->nr_proiecte=is.nr_proiecte;
    }
    return *this;
}

istream& InginerSef::read(istream& in)
{
    Colaborator::read(in);
    cout<<"Numarul de target-uri obligatorii: ";
    in>>this->target;
    cout<<"Numarul de activitati atinse de inginer-sef: ";
    in>>this->nr_activitati;
    cout<<"Numarul de oameni din echipa inginerului-sef: ";
    in>>this->nr_persoane_echipa;
    cout<<"Cate proiecte a finalizat inginerul-sef: ";
    in>>this->nr_proiecte;
    return in;
}
ostream& InginerSef::write(ostream& out) const
{
    Colaborator::write(out);
    out<<"Numarul de target-uri obligatorii: "<<this->target<<endl;
    out<<"Numarul de activitati atinse de inginer: "<<this->nr_activitati<<endl;
    out<<"Numarul de oameni din echipa inginerului-sef: "<<this->nr_persoane_echipa<<endl;
    out<<"Numarul de proiecte finalizate de inginerul-sef: "<<this->nr_proiecte;
    return out;
}
istream& operator>>(istream& in, InginerSef& is)
{
    return is.read(in);
}
ostream& operator<<(ostream& out, const InginerSef& is )
{
    return is.write(out);
}
int::InginerSef::calculeaza_salariul()
{
    return(this->salariu_baza+100*this->nr_proiecte);
}
class MeniuInteractiv
{
    static MeniuInteractiv *obiect;
    MeniuInteractiv() {}
public:
    static MeniuInteractiv* getInstance()
    {
        if(!obiect)
            obiect=new MeniuInteractiv();
        return obiect;
    }
    void meniu ( )
    {
        int k=1,comanda,i=0;
        vector <Colaborator*> listacolaboratori;
        set<int, greater<int> > s1;
        map<string, int> my_map;
        list <string> listanume;
        while(k==1)
        {
            cout<<"1-Adaugare Inginer\n2-Adaugare Sef\n3-Adaugare Inginer-Sef\n4-Stop\n5-Afisare Colaboratori\n6-Afisarea salariilor\n7-Afisare map prenume/salariu\n8-Calculeaza salariul pentru un anumit colaborant\n9-Aduna 2 salarii\n10-Compara salariul de baza dintre 2 colaboratori\n11-Cate activitati extra pentru un inginer ce nu face parte din firma?\n12-Delete\n13-Afiseaza toate prenumele colaboratorilor\n ";
            cin>>comanda;
            switch(comanda)
            {
            case 1:
            {

                listacolaboratori.push_back(new Inginer);
                cin>>dynamic_cast<Inginer&>(*listacolaboratori[i]);
                s1.insert(listacolaboratori[i]->calculeaza_salariul());
                my_map.insert(std::pair<string, int>(listacolaboratori[i]->get_prenume(),listacolaboratori[i]->calculeaza_salariul()));
                listanume.push_back(listacolaboratori[i]->get_prenume());
                i++;
                break;
            }
            case 2:
            {
                listacolaboratori.push_back(new Sef);
                cin>>dynamic_cast<Sef&>(*listacolaboratori[i]);
                my_map.insert(std::pair<string, int>(listacolaboratori[i]->get_prenume(),listacolaboratori[i]->calculeaza_salariul()));
                s1.insert(listacolaboratori[i]->calculeaza_salariul());
                listanume.push_back(listacolaboratori[i]->get_prenume());
                i++;
                break;
            }
            case 3:
            {
                listacolaboratori.push_back(new InginerSef);
                cin>>dynamic_cast<InginerSef&>(*listacolaboratori[i]);
                my_map.insert(std::pair<string, int>(listacolaboratori[i]->get_prenume(),listacolaboratori[i]->calculeaza_salariul()));
                s1.insert(listacolaboratori[i]->calculeaza_salariul());
                listanume.push_back(listacolaboratori[i]->get_prenume());
                i++;
                break;
            }
            case 4:
            {
                k=0;
                break;
            }
            case 5:
            {
                try
                {
                    int a=listacolaboratori.size();
                    if (a==0)
                        throw string ("Nu exisa elemente in lista: ");
                    else
                    {
                        for(int j=0; j<listacolaboratori.size(); j++)
                            cout<<*listacolaboratori[j];

                    }
                }
                catch (string s)
                {
                    cout<<s<<'\n';
                }
                break;

            }
            case 6:
            {
                try
                {
                    int a=s1.size();
                    if (a==0)
                        throw string ("Nu exisa elemente in lista: ");
                    else
                    {
                        set<int, greater<int> >::iterator itr;
                        if(s1.size()!=0)
                            cout << "\nToate salariile calculate : \n";
                        for (itr = s1.begin(); itr != s1.end(); itr++)
                        {
                            cout << *itr << " ";
                        }
                        cout << endl;

                    }

                }
                catch (string s)
                {
                    cout<<s<<'\n';
                }
                break;

            }
            case 7:
            {

                try
                {
                    int a=my_map.size();
                    if (a==0)
                        throw string ("Nu exisa elemente in map: ");
                    else
                    {
                        for (map<string, int>::iterator it = my_map.begin(); it != my_map.end(); ++it)
                            cout << (*it).first << ": " << (*it).second << endl;
                        cout<<'\n';

                    }
                }
                catch (string s)
                {
                    cout<<s<<'\n';
                }
                break;

            }
            case 8:
            {

                cout<<"Pentru al catelea colaborator doriti sa calculati salariul?"<<endl;
                int x;
                while(true)
                {
                    try
                    {
                        cin>>x;
                        if (x>listacolaboratori.size())
                            throw string ("Acest colaborator nu se afla in lista: ");
                        else
                            break;
                    }
                    catch (string s)
                    {
                        cout<<s<<'\n';
                    }

                }

                cout<<"Colaboratorul "<<x<<" are salariul de: "<<listacolaboratori[x-1]->calculeaza_salariul()<<endl;
                break;
            }
            case 9:
            {
                cout<<"Intre care colaboratori doriti sa faceti suma salariilor? "<<endl;
                int c,d;
                while(true)
                {
                    try
                    {
                        cin>>c>>d;
                        if (c>listacolaboratori.size()||d>listacolaboratori.size())
                            throw string ("Acesti colaboratori nu se afla in lista: ");
                        else
                            break;
                    }
                    catch (string s)
                    {
                        cout<<s<<'\n';
                    }
                }

                cout<<"Suma salariilor este: "<<aduna_salarii(listacolaboratori[c-1],listacolaboratori[d-1])<<endl;
                break;
            }
            case 10:
            {
                cout<<"Intre care colaboratori doriti sa comparati salariul de baza? "<<endl;
                int c,d;
                while(true)
                {
                    try
                    {
                        cin>>c>>d;
                        if (c>listacolaboratori.size()||d>listacolaboratori.size())
                            throw string ("Acesti colaboratori nu se afla in lista: ");
                        else
                            break;
                    }
                    catch (string s)
                    {
                        cout<<s<<'\n';
                    }
                }
                int x=listacolaboratori[c-1]->get_salariu_baza();
                int y=listacolaboratori[d-1]->get_salariu_baza();
                Comparare <float> myOBJ(x, y);
                cout << "Salariul de baza mai mare este: " << myOBJ.bigger() << endl;
                break;
            }
            case 11:
            {
                Inginer a;
                cin>>a;
                activitati_extra(a);
                cout<<'\n';
                break;
            }
            case 12:
            {

                cout<<"Al catelea colaborator doriti sa eliminati?: ";
                int nr;
                while(true)
                {
                    try
                    {
                        cin>>nr;
                        if (nr>listacolaboratori.size())
                            throw string ("Acesti colaboratori nu se afla in lista: ");
                        else
                            break;
                    }
                    catch (string s)
                    {
                        cout<<s<<'\n';
                    }
                }
                listacolaboratori.erase(listacolaboratori.begin()+nr-1);
                break;
            }
            case 13:
            {
                try
                {
                    int a=listanume.size();
                    if (a==0)
                        throw string ("Nu exisa elemente in lista: ");
                    else
                    {
                        list<string>::iterator it;
                        for(it=listanume.begin(); it!=listanume.end(); it++)
                            cout <<  *it << " ";
                        cout << "\n";
                    }
                }
                catch (string s)
                {
                    cout<<s<<'\n';
                }
                break;
            }

            }

        }

    }
};
MeniuInteractiv* MeniuInteractiv::obiect=0;
int main()
{
    MeniuInteractiv *meniulMeu=meniulMeu->getInstance();
    meniulMeu->meniu();
}
