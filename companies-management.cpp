#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <stdlib.h>
#include <typeinfo>
using namespace std;
void menu_output()
{
    cout<<"\n Boghiu Alexandra-Adriana Grupa 134 - Proiect 3 - Nume proiect: Companii (nr 11)\n";
    cout<<"\n\t MENIU:";
    cout<<"\n===========================================\n";
    cout<<"\n";
    cout<<"1. Citirea, memorarea si afisarea a n obiecte";
    cout<<"\n";
    cout<<"2. Exemplu fuzionare companie";
    cout<<"\n";
    cout<<"3. Dynamic_cast";
    cout<<"\n";
    cout<<"4. Nr de obiecte de tip Data (folosind functie tip static)";
    cout<<"\n";
    cout<<"5. Compararea nr obiectelor de tip Manager cu cele de tip Angajat (folosind functie template)";
    cout<<"\n";
    cout<<"6. Exemplu adaugare_departament, stergere_departament";
    cout<<"\n";

    cout<<"0. Iesire.";
    cout<<"\n";
}
const int impozit = 0.84;

template <class T>
T comparare(T a, T b)
{
    if(a > b) return 1;
    else if (a == b) return 2;
    return 3;
}
class Data
{
private:
    int zi;
    int luna;
    int an;
    static int nr_date;
public:
    Data(int zi = 0, int luna = 0, int an = 0)
    {
        nr_date++;
        this->zi = zi;
        this->luna = luna;
        this->an = an;

    }
    Data(const Data&);
    ~Data();

    void set_zi(int);
    void set_luna(int);
    void set_an(int);

    int get_zi() const
    {
        return zi;
    };
    int get_luna() const
    {
        return luna;
    };
    int get_an() const
    {
        return an;
    };
    static void numarObiecteData()
    {
        cout<<nr_date;
    }
    static int retNumarObiecteData()
    {
        return nr_date;
    }
    Data& operator=(const Data &data);
    void citire(istream &in);
    void afisare(ostream &out);
    friend istream& operator>>(istream &in, Data& data);
    friend ostream& operator<<(ostream &out, Data& data);


};
int Data::nr_date;
class Pozitie
{
protected:

    string nume, prenume;
    float salariu;
    Data data_angajare;
    bool is_Manager;

public:
    Pozitie();
    Pozitie(string nume, string prenume, float salariu, Data data_angajare, bool is_Manager): nume(nume), prenume(prenume), salariu(salariu), data_angajare(data_angajare), is_Manager(is_Manager)
    {}
    Pozitie(const Pozitie&);
    ~Pozitie();
    Pozitie& operator=(const Pozitie &pozitie);
    bool operator== (const Pozitie &pozitie) const;
    virtual void citire(istream &in);
    virtual void afisare(ostream &out);
    friend istream& operator>>(istream &in, Pozitie& pozitie);
    friend ostream& operator<<(ostream &out, Pozitie& pozitie);
    virtual int get_data_zi() const
    {
        return data_angajare.get_zi();
    }
    virtual int get_data_luna() const
    {
        return data_angajare.get_luna();
    }
    virtual int get_data_an() const
    {
        return data_angajare.get_an();
    }
    virtual int get_salariu() const
    {
        return salariu;
    }
    virtual bool get_isManager() const
    {
        return is_Manager;
    }
    virtual void adaugare_subord(Pozitie *&pozitie)
    {}
    //  friend class Departament;
    friend class HRManager;

};
class Angajat: public Pozitie
{
    static int nr_a;
public:
    Angajat();
    Angajat(string nume, string prenume, float salariu, Data data_angajare, bool is_Manager): Pozitie(nume, prenume, salariu, data_angajare, is_Manager)
    {
        nr_a++;
    }
    Angajat(const Angajat&);
    ~Angajat();
    Angajat& operator=(const Angajat &angajat);
    bool operator== (const Angajat &angajat) const;
    void citire(istream &in);
    void afisare(ostream &out);
    virtual void succes()
    {
        cout<<"Downcast realizat cu succes.";
    }
    friend istream& operator>>(istream &in, Angajat& angajat);
    friend ostream& operator<<(ostream &out, Angajat& angajat);
    void adaugare_subord(Angajat &angajat)
    {}
    int get_salariu()
    {
        return salariu;
    }
    static void numarObiecteAngajat()
    {
        cout<<nr_a;
    }
    static int retNumarObiecteAngajat()
    {
        return nr_a;
    }
    // friend class Departament;
    friend class HRManager;


};
int Angajat::nr_a;
class Departament
{
private:
    Pozitie **ang;
    string denumire;
    bool scutire_de_impozit;
    int nr_ang;
public:
    Departament(string denumire = "",  int nr_ang = 0, Pozitie **ang = NULL, bool scutire_de_impozit = false)
    {

        this->denumire = denumire;
        this->scutire_de_impozit = scutire_de_impozit;
        this->nr_ang = nr_ang;
        this->ang = new Pozitie*[nr_ang];
        for(int i = 0; i < nr_ang; i++)
            this->ang[i] = ang[i];

    }
    ~Departament()
    {
        denumire = "";
        this->scutire_de_impozit = false;
        nr_ang = 0;
        // delete []ang;
    }
    Departament(const Departament&);
    bool get_scutire_de_impozit()
    {
        return scutire_de_impozit;
    }
    int get_nr_ang()
    {
        return nr_ang;
    }
    string get_denumire_dep()
    {
        return denumire;
    }
    void adaugare_ang(Pozitie *poz);
    Departament& operator=(const Departament &departament);
    bool operator== (const Departament &departament) const;
    void citire(istream &in);
    void afisare(ostream &out);
    friend istream& operator>>(istream &in, Departament& departament);
    friend ostream& operator<<(ostream &out, Departament& departament);
    // friend class Companie;
    friend class HRManager;
    // friend class Manager;
};
class Companie
{
private:
    Departament *dep;
    string denumire_comp;
    int nr_dep;
public:
    Companie(string denumire_comp = "", int nr_dep = 0,Departament *dept = NULL)
    {
        this->denumire_comp = denumire_comp;
        this->nr_dep = nr_dep;
        this->dep = new Departament[nr_dep];
        for(int i = 0; i < nr_dep; i++)
            this->dep[i] = dept[i];
    }
    ~Companie()
    {
        denumire_comp = "";
        nr_dep = 0;
    }
    int get_nr_dep()
    {
        return nr_dep;
    }
    string  get_comp_nume()
    {
        return denumire_comp;
    }
    Companie(const Companie&);
    Companie& operator=(Companie &companie);
    Companie operator+(Companie const &companie);
    bool operator== (const Companie &companie) const;
    void citire(istream &in);
    void afisare(ostream &out);
    friend istream& operator>>(istream &in, Companie& companie);
    friend ostream& operator<<(ostream &out, Companie& companie);
    friend class HRManager;
    // friend class Manager;

};
class Manager:public Pozitie
{
private:
    int nr_subord;
    static int nr_m;
    vector <Pozitie> subord;
public:
    Manager();
    Manager(string nume, string prenume,  float salariu, Data data_angajare, bool is_Manager, int nr_subord, vector <Pozitie> subord = {}): Pozitie(nume, prenume, salariu, data_angajare,is_Manager)
    {
        nr_m++;
        this->nr_subord = nr_subord;
        for(int i = 0; i < subord.size(); i++)
            this->subord[i] = subord[i];
    }
    Manager(const Manager&);
    ~Manager();
    Manager& operator=(const Manager &manager);
    bool operator== (const Manager &manager) const;
    void citire(istream &in);
    void afisare(ostream &out);
    friend istream& operator>>(istream &in, Manager& manager);
    friend ostream& operator<<(ostream &out, Manager& manager);
    void adaugare_subord(Pozitie *&pozitie)
    {

        subord.push_back(*pozitie);
        nr_subord++;
    }
    static int retNumarObiecteManager()
    {
        return nr_m;
    }
    //  friend class Departament;
    friend class HRManager;

};
int Manager::nr_m;
class HRManager
{
private:
    int nr_comp;
    Companie* companii;

public:
    HRManager(int nr_comp = 0, Companie * companii = NULL)
    {
        this->nr_comp = nr_comp;
        this->companii = new Companie[nr_comp];
        for(int i = 0; i < nr_comp; i++)
            this->companii[i] = companii[i];
    }
    ~HRManager()
    {
        nr_comp = 0;
        delete[] companii;
    }
    HRManager& operator=(HRManager &hrmanager);
    void citire(istream &in);
    void afisare(ostream &out);
    friend istream& operator>>(istream &in, HRManager& hrmanager);
    friend ostream& operator<<(ostream &out, HRManager& hrmanager);
    int nr_ang_dep(Companie &c, Departament &d)
    {
        for(int i = 0; i < nr_comp; i++)
            if(c == companii[i])
                for(int j = 0; j < companii[i].nr_dep; j++)
                    if(companii[i].dep[j] == d)
                    {
                        return companii[i].dep[j].get_nr_ang();

                    }

    }
    int nr_ang_comp(Companie &c)
    {
        int suma = 0;
        for(int i = 0; i < nr_comp; i++)
            if(c == companii[i])
                for(int j = 0; j < companii[i].nr_dep; j++)
                    suma += companii[i].dep[j].get_nr_ang();
        return suma;

    }
    int cheltuieli(Companie &c)
    {
        long long suma = 0;

        for(int i = 0; i < nr_comp; i++)
        {
            if(companii[i] == c)
            {
                for(int j = 0; j < companii[i].nr_dep; j++)
                    for(int k = 0; k < companii[i].dep[j].get_nr_ang(); k++)
                        if(companii[i].dep[j].get_scutire_de_impozit() == true)
                            suma += companii[i].dep[j].ang[k]->get_salariu() * impozit;
                        else
                            suma  += companii[i].dep[j].ang[k]->get_salariu();

            }
        }
        return suma;
    }
    void nr_min_ang(int n)
    {
        int numar = 0;
        for(int i = 0; i < nr_comp; i++)
        {
            numar = 0;
            for(int j = 0; j < companii[i].nr_dep; j++)
            {
                if(companii[i].dep[j].nr_ang >= n)
                    cout<<companii[i].dep[j];
            }

        }

    }
    void adaugare_comp(Companie &c)
    {
        int ok = 0;
        for(int i = 0; i < nr_comp; i++)
            if(c == companii[i])
            {
                ok = 1;
                cout<<"Compania a fost introdusa deja.";
                break;
            }
        if(ok == 0)
        {
            Companie *compfals = new Companie[nr_comp + 1];
            for(int i = 0; i < nr_comp; i++)
                compfals[i] = companii[i];
            nr_comp++;
            companii = new Companie[nr_comp];
            for(int i = 0; i < nr_comp; i++)
                companii[i] = compfals[i];
            companii[nr_comp - 1] = c;
            delete[] compfals;

        }

    }
    void adaugare_dep(Companie &c, Departament &d)
    {
        int ok = 0;
        for(int j = 0; j < nr_comp; j++)
        {
            if(companii[j] == c)
            {
                for(int i = 0; i < c.nr_dep; i++)
                    if(d == c.dep[i])
                    {
                        ok = 1;
                        cout<<"Departamentul a fost introdus deja.";
                        break;
                    }

                if(ok == 0)
                {
                    Departament *depfals = new Departament[c.nr_dep + 1];
                    for(int j = 0; j < c.nr_dep; j++)
                        depfals[j] = c.dep[j];
                    c.nr_dep++;
                    c.dep = new Departament[c.nr_dep];
                    for(int j = 0; j < c.nr_dep; j++)
                        c.dep[j] = depfals[j];
                    c.dep[c.nr_dep - 1] = d;

                    delete[] depfals;
                }
            }
        }
    }

    void adaugare_angg(Companie &c, Departament &d, Pozitie *&a)
    {
        int ok = 0;
        for(int j = 0; j < nr_comp; j++)
        {
            if(companii[j].get_comp_nume() == c.get_comp_nume())
            {
                for(int i = 0; i < companii[j].nr_dep; i++)

                    if(d.get_denumire_dep() == c.dep[i].get_denumire_dep())
                    {
                        for(int k = 0; k < companii[j].dep[i].nr_ang; k++)
                            if(c.dep[i].ang[k] == a)
                            {
                                ok = 1;
                                cout<<"Angajatul a fost introdus deja.";
                                break;
                            }

                        if(ok == 0)
                        {

                            int k;
                            Pozitie *angfals[c.dep[i].nr_ang+1];
                            for(k = 0; k < c.dep[i].nr_ang; k++)
                                angfals[k] = c.dep[i].ang[k];
                            angfals[k] = a;
                            c.dep[i].nr_ang++;
                            *c.dep[i].ang = new Pozitie[c.dep[i].nr_ang];

                            for(k=0; k < c.dep[i].nr_ang; k++)
                                c.dep[i].ang[k]=angfals[k];

                        }
                    }
            }
        }

    }


    void stergere_companie (Companie &c)
    {
        for(int i = 0; i < nr_comp; i++)
        {
            if(c.get_comp_nume() == companii[i].get_comp_nume())
            {
                for(int j = i; j < nr_comp - 1; j++)
                    companii[j] = companii[j + 1];
                nr_comp--;
            }
        }

    }
    void stergere_departament (Companie &c, Departament &d)
    {
        for(int j = 0; j < c.nr_dep; j++)
            if(d == c.dep[j])
            {
                for(int k = j; k < c.nr_dep - 1; k++)
                    c.dep[k] = c.dep[k + 1];
                c.nr_dep--;
            }

    }

    void stergere_angajat (Companie &c, Departament &d, Pozitie *a)
    {
        for(int i = 0; i < nr_comp; i++)
        {
            if(c.get_comp_nume() == companii[i].get_comp_nume())
            {
                for(int j = 0; j < companii[i].nr_dep; j++)
                    if(d.get_denumire_dep() == c.dep[j].get_denumire_dep())
                    {
                        for(int k = 0; k < c.dep[j].nr_ang; k++)
                            if(c.dep[j].ang[k] == a)
                            {
                                for(int p = k; p < c.dep[j].nr_ang - 1; p++)
                                    c.dep[j].ang[p] = c.dep[j].ang[p + 1];
                                c.dep[j].nr_ang--;
                            }
                    }

            }
        }

    }
    void afisare_lista(Companie &c)
    {
        for(int i = 0; i < c.nr_dep; i++)
        {
            for(int j = 0; j < c.dep[i].nr_ang; j++)
            {
                if(c.dep[i].ang[j]->get_isManager() == true)
                    cout<<*c.dep[i].ang[j]<<endl;
            }
        }
    }
    void fuzionare(Companie &c1, Companie &c2)
    {
        int v[1000];
        for(int i = 0; i < 1000; i++)
            v[i] = 0;
        for(int i = 0; i < c1.nr_dep; i++)
        {
            for(int j = 0; j < c2.nr_dep; j++)
            {
                if(c1.dep[i].get_denumire_dep() == c2.dep[j].get_denumire_dep())
                {
                    v[j] = 1;
                    for(int k = 0; k < c2.dep[j].nr_ang; k++)
                    {
                        adaugare_angg(c1, c1.dep[i], c2.dep[j].ang[k]);
                    }
                }
            }
        }
        for(int i = 0; i < c2.nr_dep; i++)
            if(v[i] == 0)
            {
                adaugare_dep(c1, c2.dep[i]);
            }

        //cout<<c1;
        /*    for(int j = 0; j < c2.nr_dep; j++)
            {
                int ok = 0;
                for(int i = 0; i < c1.nr_dep; i++)
                {
                    if(c1.dep[i].denumire == c2.dep[j].denumire)
                    {
                        ok = 1;
                    }
                }
                if(ok == 0)
                {
                adaugare_dep(c1, c2.dep[j]);
                cout<<c1.dep;*/

    }

};

Companie::Companie(const Companie &companie)
{
    this->denumire_comp = companie.denumire_comp;
    this->nr_dep = companie.nr_dep;
    this->dep = new Departament[nr_dep];
    for(int i = 0; i < nr_dep; i++)
        this->dep[i] = companie.dep[i];
}
Data::Data(const Data &data)
{
    this->zi = data.zi;
    this->an = data.an;
    this->luna = data.luna;
}
Data::~Data()
{
    zi = 0;
    luna = 0;
    an = 0;

}
Data& Data::operator=(const Data &data)
{
    zi = data.zi;
    an = data.an;
    luna = data.luna;
}
void Data::citire(istream &in)
{
    string a;
    try
    {
        cout<<"Cititi ziua:";
        in>>a;
        if(a.size() > 2)
            throw 1;
        if(a.size() == 1 &&  !(a[0] > '0' && a[0] <= '9'))
            throw 1;
        if(a.size() == 2 && a[0] >= '4')
            throw 1;
        if(a.size() == 2 && (a[0] == '3' && a[1] >= '2'))
            throw 1;
        if(a.size() == 2 && (a[0] >= '0' && a[0] <= '2' && (a[1] < '0' || a[1] > '9')))
            throw 1;
        zi = stoi(a);
    }
    catch(int)
    {
        cout<<"Introduceti o zi valida. (1 -> 31)";
        exit(1);
    }
    try
    {
        cout<<"Cititi luna: ";
        in>>a;
        if(a.size() > 2)
            throw 1;
        if(a.size() == 1 &&  !(a[0] > '0' && a[0] <= '9'))
            throw 1;
        if(a.size() == 2 && a[0] > '1')
            throw 1;
        if(a.size() == 2 && (a[0] == '1' && a[1] > '2'))
            throw 1;
        luna = stoi(a);
    }
    catch(int)
    {
        cout<<"Introduceti o luna valida. (1 -> 12)";
        exit(1);
    }
    try
    {
        cout<<"Cititi anul: ";
        in>>a;
        if(a.size() != 4)
            throw 1;
        if(a[0] != '2' || a[1] != '0')
            throw 1;
        if(a[2] > '2')
            throw 1;
        if(a[2] == '2' && a[3] > '2')
            throw 1;
        an = stoi(a);
    }
    catch(int)
    {
        cout<<"Introduceti un an valid. (2000 -> 2021)";
        exit(1);
    }
}
istream& operator>>(istream& in, Data& data)
{
    data.citire(in);
    return in;
}

void Data::afisare(ostream &out)
{
    out<<"Data este: ";
    out<<zi<<'.'<<luna<<'.'<<an<<endl;
}
ostream& operator<<(ostream& out, Data& data)
{
    data.afisare(out);
    return out;
}
void Data::set_zi(int x)
{
    zi = x;
}
void Data::set_luna(int y)
{
    luna = y;
}
void Data::set_an(int z)
{
    an = z;
}
Departament::Departament(const Departament &departament)
{
    this->denumire = denumire;
    this->scutire_de_impozit = scutire_de_impozit;
    this->nr_ang = nr_ang;
    for(int i = 0; i < nr_ang; i++)
        this->ang[i] = ang[i];
}

Pozitie::Pozitie()
{
    this->nume = "";
    this->prenume = "";
    this->salariu = 0.0;
    this->is_Manager = false;
    Data data_angajare;
}
Pozitie::Pozitie(const Pozitie &pozitie)
{
    this->nume = pozitie.nume;
    this->prenume = pozitie.prenume;
    this->salariu = pozitie.salariu;
    this->data_angajare = pozitie.data_angajare;
    this->is_Manager = pozitie.is_Manager;
}
Pozitie::~Pozitie()
{
    this->nume = "";
    this->prenume = "";
    this->salariu = 0.0;
    this->is_Manager = false;
    data_angajare.set_zi(0);
    data_angajare.set_luna(0);
    data_angajare.set_an(0);
}
Pozitie& Pozitie::operator=(const Pozitie &pozitie)
{
    nume = pozitie.nume;
    prenume = pozitie.prenume;
    salariu = pozitie.salariu;
    data_angajare = pozitie.data_angajare;
    is_Manager = pozitie.is_Manager;
}
bool Pozitie::operator== (const Pozitie& rhs) const
{
    bool ok = true;
    if(nume != rhs.nume || prenume != rhs.prenume || salariu != rhs.salariu || is_Manager != rhs.is_Manager
            || data_angajare.get_an() != rhs.data_angajare.get_an() ||data_angajare.get_luna() != rhs.data_angajare.get_luna()
            || data_angajare.get_zi() != rhs.data_angajare.get_zi())
        ok = false;
    return ok;

}
void Pozitie::citire(istream &in)
{
    string a;
    try
    {
        cout<<"Cititi numele: ";
        in>>a;
        if(a[0] < 'A' || a[0] > 'Z')
            throw 1;
        for(int i = 1; i < a.length(); i++)
            if(a[i] < 'a' || a[i] > 'z')
                throw 1;
        nume = a;
    }
    catch(int)
    {
        cout<<"Introduceti un nume valid.";
        exit(1);
    }
    try
    {
        cout<<"Cititi prenumele: ";
        in.get();
        getline(in, a);
        if(a[0] < 'A' || a[0] > 'Z')
            throw 1;
        for(int i = 1; i < a.length(); i++)
        {
            if((a[i] < 'a' || a[i] > 'z') && a[i] != ' ')
                throw 1;

        }
        prenume = a;
    }
    catch(int)
    {
        cout<<"Introduceti un prenume valid.";
        exit(1);
    }
    try
    {
        int ok = 0;
        cout<<"Cititi salariul: ";
        in>>a;
        if(a[0] == '.')
            throw 1;
        for(int i = 0; i < a.length(); i++)
        {
            if(a[i] == '.' && ok == 0)
            {
                ok = 1;
            }
            else if((a[i] < '0' || a[i] > '9') && a[i] != '.')
                throw 1;
        }
        salariu = stof(a);
    }
    catch(int)
    {
        cout<<"Introduceti un salariu valid.";
        exit(1);
    }
    in>>data_angajare;
}
istream& operator>>(istream& in, Pozitie& pozitie)
{
    pozitie.citire(in);
    return in;
}
void Pozitie::afisare(ostream &out)
{
    out<<"Numele angajatului este: ";
    out<<nume<<' '<<prenume<<endl;
    out<<"Salariul angajatului este: ";
    out<<salariu<<endl;
    out<<data_angajare;
    if(is_Manager ==  true) out<<"Este manager."<<endl;
    else out<<"Nu este manager."<<endl;
}
ostream& operator<<(ostream& out, Pozitie& pozitie)
{
    pozitie.afisare(out);
    return out;
}
Angajat::Angajat():Pozitie()
{
    nr_a++;
}
Angajat::Angajat(const Angajat &angajat)
{
    this->nume = angajat.nume;
    this->prenume = angajat.prenume;
    this->salariu = angajat.salariu;
    this->data_angajare = angajat.data_angajare;
    this->is_Manager = angajat.is_Manager;
}
Angajat::~Angajat()
{
    this->nume = "";
    this->prenume = "";
    this->salariu = 0.0;
    this->is_Manager = false;
    data_angajare.set_zi(0);
    data_angajare.set_luna(0);
    data_angajare.set_an(0);
}
Angajat& Angajat::operator=(const Angajat &angajat)
{
    nume = angajat.nume;
    prenume = angajat.prenume;
    salariu = angajat.salariu;
    data_angajare = angajat.data_angajare;
    is_Manager = angajat.is_Manager;
}
bool Angajat::operator== (const Angajat& rhs) const
{
    bool ok = true;
    if(nume != rhs.nume || prenume != rhs.prenume || salariu != rhs.salariu || is_Manager != rhs.is_Manager
            || data_angajare.get_an() != rhs.data_angajare.get_an() ||data_angajare.get_luna() != rhs.data_angajare.get_luna()
            || data_angajare.get_zi() != rhs.data_angajare.get_zi())
        ok = false;
    return ok;

}
void Angajat::citire(istream &in)
{
    string a;
    try
    {
        cout<<"Cititi numele: ";
        in>>a;
        if(a[0] < 'A' || a[0] > 'Z')
            throw 1;
        for(int i = 1; i < a.length(); i++)
            if(a[i] < 'a' || a[i] > 'z')
                throw 1;
        nume = a;
    }
    catch(int)
    {
        cout<<"Introduceti un nume valid.";
        exit(1);
    }
    try
    {
        cout<<"Cititi prenumele: ";
        in.get();
        getline(in, a);
        if(a[0] < 'A' || a[0] > 'Z')
            throw 1;
        for(int i = 1; i < a.length(); i++)
            if(a[i] < 'a' || a[i] > 'z' && a[i] != ' ')
                throw 1;
        prenume = a;
    }
    catch(int)
    {
        cout<<"Introduceti un prenume valid.";
        exit(1);
    }
    try
    {
        int ok = 0;
        cout<<"Cititi salariul: ";
        in>>a;
        if(a[0] == '.')
            throw 1;
        for(int i = 0; i < a.length(); i++)
        {
            if(a[i] == '.' && ok == 0)
            {
                ok = 1;
            }
            else if((a[i] < '0' || a[i] > '9') && a[i] != '.')
                throw 1;
        }
        salariu = stof(a);
    }
    catch(int)
    {
        cout<<"Introduceti un salariu valid.";
        exit(1);
    }
    in>>data_angajare;
}
istream& operator>>(istream& in, Angajat& angajat)
{
    // angajat.citire(in);
    in>>static_cast<Pozitie&>(angajat);
    return in;
}
void Angajat::afisare(ostream &out)
{
    out<<"Numele angajatului este: ";
    out<<nume<<' '<<prenume<<endl;
    out<<"Salariul angajatului este: ";
    out<<salariu<<endl;
    out<<data_angajare;
    if(is_Manager ==  true) out<<"Este manager."<<endl;
    else out<<"Nu este manager."<<endl;
}
ostream& operator<<(ostream& out, Angajat& angajat)
{
    angajat.afisare(out);
    return out;
}
Manager::Manager()
{
    nr_m++;
    this->nume = "";
    this->prenume = "";
    this->salariu = 0.0;
    this->is_Manager = true;
    this->nr_subord = 0;
    Data data_angajare;
    vector <Angajat> subord = {};
}
Manager::Manager(const Manager &manager)
{
    this->nume = manager.nume;
    this->prenume = manager.prenume;
    this->salariu = manager.salariu;
    this->data_angajare = manager.data_angajare;
    this->is_Manager = manager.is_Manager;
    this->nr_subord = manager.nr_subord;
    for(int i = 0; i < subord.size(); i++)
        this->subord[i] = subord[i];
}
Manager::~Manager()
{
    this->nume = "";
    this->prenume = "";
    this->salariu = 0.0;
    this->is_Manager = true;
    this->nr_subord = 0;
    data_angajare.set_zi(0);
    data_angajare.set_luna(0);
    data_angajare.set_an(0);
}
Manager& Manager::operator=(const Manager &manager)
{
    if(this != &manager)
    {
        nume = manager.nume;
        prenume = manager.prenume;
        salariu = manager.salariu;
        data_angajare = manager.data_angajare;
        is_Manager = manager.is_Manager;
        subord = manager.subord;
    }
    return *this;
}
void Manager::citire(istream &in)
{
    string a;
    try
    {
        cout<<"Cititi numele: ";
        in>>a;
        if(a[0] < 'A' || a[0] > 'Z')
            throw 1;
        for(int i = 1; i < a.length(); i++)
            if(a[i] < 'a' || a[i] > 'z')
                throw 1;
        nume = a;
    }
    catch(int)
    {
        cout<<"Introduceti un nume valid.";
        exit(1);
    }
    try
    {
        cout<<"Cititi prenumele: ";
        in.get();
        getline(in, a);
        if(a[0] < 'A' || a[0] > 'Z')
            throw 1;
        for(int i = 1; i < a.length(); i++)
            if((a[i] < 'a' || a[i] > 'z') && a[i] != ' ')
                throw 1;
        prenume = a;
    }
    catch(int)
    {
        cout<<"Introduceti un prenume valid.";
        exit(1);
    }
    try
    {
        int ok = 0;
        cout<<"Cititi salariul: ";
        in>>a;
        if(a[0] == '.')
            throw 1;
        for(int i = 0; i < a.length(); i++)
        {
            if(a[i] == '.' && ok == 0)
            {
                ok = 1;
            }
            else if((a[i] < '0' || a[i] > '9') && a[i] != '.')
                throw 1;
        }
        salariu = stof(a);
    }
    catch(int)
    {
        cout<<"Introduceti un salariu valid.";
        exit(1);
    }
    in>>data_angajare;
    try
    {
        cout<<"Cititi nr de angajati subordonati: ";
        in>>a;
        for(int i = 0; i < a.length(); i++)
        {
            if(a[i] < '0' || a[i] > '9')
                throw 1;
        }
        nr_subord  = stoi(a);
    }
    catch(int)
    {
        cout<<"Introduceti un numar de subordonati valid.";
        exit(1);
    }
    if(nr_subord > 0) cout<<"Urmeaza sa introduceti subordonatii. Introduceti subordonati deja inscrisi in departament/companie."<<endl;
    Angajat angsub;
    for(int i = 0; i < nr_subord; i++)
    {
        in>>angsub;
        subord.push_back(angsub);

    }
}
istream& operator>>(istream& in, Manager& manager)
{
    in>>static_cast<Pozitie&>(manager);
    return in;
    //manager.citire(in);
}
void Manager::afisare(ostream &out)
{
    out<<"Numele managerului este: ";
    out<<nume<<' '<<prenume<<endl;
    out<<"Salariul managerului este: ";
    out<<salariu<<endl;
    out<<data_angajare;
    out<<"Managerul are "<<nr_subord<<" subordonati"<<endl;
    for(int i = 0; i < subord.size(); i++)
        out<<subord[i]<<" ";
}
ostream& operator<<(ostream& out, Manager& manager)
{
    manager.afisare(out);
    return out;
}
Departament& Departament::operator=(const Departament &departament)
{
    if(this != &departament)
    {
        denumire = departament.denumire;
        nr_ang = departament.nr_ang;
        ang = new Pozitie*[nr_ang];
        for(int i = 0; i < nr_ang; i++)
            ang[i] = departament.ang[i];
        scutire_de_impozit = departament.scutire_de_impozit;
    }
    return *this;
}
bool Departament::operator== (const Departament& rhs) const
{
    bool ok;
    if(denumire != rhs.denumire) return false;
    if(nr_ang != rhs.nr_ang)
        return false;
    if(nr_ang == 0)
        return true;
    for(int i = 0; i < nr_ang; i++)
    {
        ok = false;
        for(int j = 0; j < nr_ang; j++)
            if(ang[i] == rhs.ang[j]) ok = true;

        if(ok == false) return ok;
    }
    return ok;
}
void Departament::adaugare_ang(Pozitie *poz)
{
    int i;
    Pozitie *copie[this->nr_ang+1];
    for(i = 0; i < this->nr_ang; i++)
        copie[i] = this->ang[i];
    copie[i] = poz;
    this->nr_ang++;
    *ang=new Pozitie[this->nr_ang];
    for(int i = 0; i< this->nr_ang; i++)
        this->ang[i] = copie[i];

}
void Departament::citire(istream &in)
{
    string a;
    try
    {
        cout<<"Cititi denumirea departamentului: ";
        in.get();
        getline(in, a);
        if(a[0] < 'A' || a[0] > 'Z')
            throw 1;
        for(int i = 1; i < a.length(); i++)
            if(!(a[i] >= 'a' && a[i] <= 'z') && !(a[i] >= 'A' && a[i] <= 'Z')  && a[i] != ' ')
                throw 1;
        denumire = a;
    }
    catch(int)
    {
        cout<<"Introduceti o denumire valida.";
        exit(1);
    }
    try
    {
        cout<<"Cititi nr de angajati: ";
        in>>a;
        for(int i = 0; i < a.length(); i++)
        {
            if(a[i] < '0' || a[i] > '9')
                throw 1;
        }
        nr_ang = stoi(a);
    }
    catch(int)
    {
        cout<<"Introduceti un nr de angajati valid.";
        exit(1);
    }
    if(nr_ang > 0)
        cout<<"Urmeaza sa cititi datele angajatilor:"<<endl;
    ang = new Pozitie*[nr_ang];
    for(int i = 0; i < nr_ang; i++)
    {
        cout<<"1. Angajat"<<endl;
        cout<<"2. Manager"<<endl;
        int alegere;
        try
        {
            cin>>alegere;
            if(alegere == 1)
            {
                Pozitie *p = new Angajat;
                cin>>*p;
                ang[i] = p;

            }
            else if(alegere == 2)
            {
                Pozitie *p = new Manager;
                cin>>*p;
                ang[i] = p;
            }
            else throw 1;
        }
        catch(int)
        {
            cout<<"Introduceti o alegere valida. (1 / 2)";
            exit(1);
        }
    }
}
istream& operator>>(istream& in, Departament& departament)
{
    departament.citire(in);
    return in;
}

void Departament::afisare(ostream &out)
{
    out<<"Denumirea departamentului este: ";
    out<<denumire<<endl;
    out<<"Departamentul are "<<nr_ang<<" angajati"<<endl;
    for(int i = 0; i < nr_ang; i++)
        out<<*ang[i]<<" ";

}
ostream& operator<<(ostream& out, Departament& departament)
{
    departament.afisare(out);
    return out;
}
Companie& Companie::operator=(Companie &companie)
{
    if(this != &companie)
    {
        denumire_comp = companie.denumire_comp;
        nr_dep = companie.nr_dep;
        dep = new Departament[nr_dep];
        for(int i = 0; i < nr_dep; i++)
            dep[i] = companie.dep[i];
    }
    return *this;
}
bool Companie::operator == (const Companie& rhs) const
{
    bool ok = false;
    if(denumire_comp != rhs.denumire_comp)
        return false;

    if (nr_dep != rhs.nr_dep)
        return false;
    if(nr_dep == 0)
        return true;
    for(int i = 0; i < nr_dep; i++)
    {
        ok = false;
        for(int j = 0; j < nr_dep; j++)
            if(dep[i] == rhs.dep[j]) ok = true;
        if(ok == false) return ok;
    }
    return ok;
}
void Companie::citire(istream &in)
{
    string a;
    try
    {
        cout<<"Cititi denumirea companiei: ";
        in.get();
        getline(in, a);
        for(int i = 1; i < a.length(); i++)
            if(!(a[i] >= 'a' && a[i] <= 'z') && !(a[i] >= 'A' && a[i] <= 'Z') && a[i] != ' ')
                throw 1;
        denumire_comp = a;
    }
    catch(int)
    {
        cout<<"Introduceti o denumire valida.";
        exit(1);
    }
    try
    {
        cout<<"Cititi nr de departamente: ";
        in>>a;
        for(int i = 0; i < a.length(); i++)
        {
            if(a[i] < '0' || a[i] > '9')
                throw 1;
        }
        nr_dep = stoi(a);
    }
    catch(int)
    {
        cout<<"Introduceti un nr de departamente valid.";
        exit(1);
    }
    cout<<"Urmeaza sa cititi departamentele:"<<endl;
    dep = new Departament[this->nr_dep];
    for(int i = 0; i < nr_dep; i++)
        cin>>dep[i];

}
istream& operator>>(istream& in, Companie& companie)
{
    companie.citire(in);
    return in;
}

void Companie::afisare(ostream &out)
{
    out<<"Denumirea companiei este: ";
    out<<denumire_comp<<endl;
    out<<"Compania are "<<nr_dep<<" departamente."<<endl;
    if(nr_dep > 0)
        out<<"Departamentele companiei se numesc: "<<endl;
    for(int i = 0; i < nr_dep; i++)
        out<<dep[i]<<" ";

}
ostream& operator<<(ostream& out, Companie& companie)
{
    companie.afisare(out);
    return out;
}
void HRManager::afisare(ostream &out)
{
    out<<"Nr companiilor: "<<endl;
    out<<nr_comp<<endl;
    if(nr_comp > 0)  out<<"Companiile din HRManager sunt: "<<endl;
    for(int i = 0; i < nr_comp; i++)
        out<<companii[i]<<" ";

}
ostream& operator<<(ostream& out, HRManager& hrmanager)
{
    hrmanager.afisare(out);
    return out;
}

void menu()
{
    int option;///optiunea aleasa din meniu
    option=0;
    int numar = 0;
    Pozitie **obiecte;
    do
    {
        menu_output();

        cout<<"\nIntroduceti numarul actiunii: ";
        cin>>option;

        if (option==1)
        {
            string a;
            try
            {
                cout<<"Introduceti nr de obiecte. ";
                cin>>a;
                for(int i = 0; i < a.length(); i++)
                {
                    if(a[i] < '0' || a[i] > '9')
                        throw 1;
                }
                numar = stoi(a);

            }
            catch(int)
            {
                cout<<"Introduceti un numar valid.";
                exit(1);
            }


            obiecte = new Pozitie*[numar];
            for(int i = 0; i < numar; i++)
            {
                cout<<"Obiectul este de tip Angajat sau Manager?"<<endl<<"1. Angajat"<<endl<<"2. Manager"<<endl;
                int nr;
                string a;
                try
                {
                    cin>>a;
                    if (a[0] == '1' && a.size() == 1)
                    {
                        Pozitie *p = new Angajat;
                        cin>>*p;
                        obiecte[i] = p;
                    }
                    else if (a[0] == '2' && a.size() == 1)
                    {
                        Pozitie *p = new Manager;
                        cin>>*p;
                        obiecte[i] = p;
                    }
                    else throw 1;
                }
                catch(int)
                {
                    cout<<"Introduceti o optiune valida. (1 / 2)";
                    exit(1);
                }
            }

            for(int i = 0; i < numar; i++)
                cout<<*obiecte[i]<<endl;
            delete []obiecte;
        }
        if (option==2)
        {
            Companie C1;
            Companie C2;
            cin>>C1;
            cin>>C2;
            Companie* comp = new Companie[2];
            comp[0] = C1;
            comp[1] = C2;
            HRManager h(2, comp);
            h.fuzionare(C1, C2);
            cout<<"Compania obtinuta este: "<<endl<<C1;
        }
        if (option==3)
        {
            Angajat a;
            Pozitie *p = new Angajat;
            if(Angajat* a = dynamic_cast<Angajat*>(p))
                a->succes();
        }
        if (option==4)
        {
            //Data d;
            Data::numarObiecteData();
        }
        if (option==5)
        {
            if(comparare(Angajat::retNumarObiecteAngajat(), Manager::retNumarObiecteManager()) ==  1)
                cout<<"Sunt mai multe obiecte de tip Angajat decat de tip Manager";
            else if(comparare(Angajat::retNumarObiecteAngajat(), Manager::retNumarObiecteManager()) ==  2)
                cout<<"Sunt la fel de multe obiecte de tip Angajat si de tip Manager";
            else if(comparare(Angajat::retNumarObiecteAngajat(), Manager::retNumarObiecteManager()) ==  3)
                cout<<"Sunt mai multe obiecte de tip Manager decat de tip Angajat";
        }
        if(option==6)
        {
            Companie C;
            Companie *Comp = new Companie[1];
            HRManager H;
            Departament d;
            Pozitie **Ang = new Pozitie*[1];
            Pozitie *A = new Angajat;
            Ang[0] = A;
            Departament dd;
            cout<<"-> Obiectul de tip HRManager inainte de adaugarea companiei: "<<endl;
            cout<<H;
            cout<<"-> Obiectul de tip HRManager dupa adaugarea companiei: "<<endl;
            H.adaugare_comp(C);
            cout<<H;
            cout<<"-> Compania inainte de adaugarea departamentului: "<<endl;
            cout<<C<<endl;
            cout<<"-> Compania dupa adaugarea departamentului: "<<endl;
            H.adaugare_dep(C, dd);
            H.stergere_companie(C);
            H.adaugare_comp(C);
            cout<<C<<endl;
            cout<<"-> Compania dupa adaugarea angajatului: "<<endl;
            H.adaugare_angg(C, dd, A);
            cout<<C;
            cout<<"-> Compania dupa stergerea angajatului: "<<endl;
            H.stergere_angajat(C,dd,A);
            cout<<C;
            cout<<"-> Compania dupa stergerea departamentului: "<<endl;
            H.stergere_departament(C, dd);
            cout<<C;
            cout<<"-> Obiectul de tip HRManager dupa stergerea companiei: "<<endl;
            H.stergere_companie(C);
            cout<<H;
        }
        if (option==0)
        {
            cout<<"\nEXIT!\n";
        }
        if (option<0||option>6)
        {
            cout<<"\nSelectie invalida\n";
        }
        cout<<"\n";
        system("pause"); ///Pauza - Press any key to continue...
        system("cls");   ///Sterge continutul curent al consolei
    }
    while(option!=0);
}
int main()
{
    menu();

    return 0;
}
