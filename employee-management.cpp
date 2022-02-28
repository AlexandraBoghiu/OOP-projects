#include <iostream>
#include <cstring>
#include <stdlib.h>
using namespace std;
int n, *ang;
class Data
{
protected:
    int zi;
    char *luna;
    int an;
public:
    Data(int zi = 0, char *luna = "", int an = 0)
    {
        this->zi = zi;
        int numar = strlen(luna) + 1;
        this->luna = new char[numar];
        strcpy(this->luna, luna);
        this->an = an;
    }
    Data(Data&);
    ~Data();

    void set_zi(int);
    void set_luna(char*);
    void set_an(int);

    int get_zi()
    {
        return zi;
    };
    char* get_luna()
    {
        return luna;
    };
    int get_an()
    {
        return an;
    };

    Data& operator=(Data &data);
    void citire(istream &in);
    void afisare(ostream &out);
    friend istream& operator>>(istream &in, Data& data);
    friend ostream& operator<<(ostream &out, Data& data);


};

class Angajat
{
protected:
    string nume, prenume;
    float salariu;
    Data data_angajare;
    static int nr;
public:
    Angajat();
    Angajat(string nume, string prenume, float salariu, Data data_angajare): nume(nume), prenume(prenume), salariu(salariu), data_angajare(data_angajare)
    {
        nr++;
    }
    Angajat(Angajat&);
    ~Angajat();
    Angajat& operator=(Angajat &angajat);
    virtual void citire(istream &in);
    virtual void afisare(ostream &out);
    friend istream& operator>>(istream &in, Angajat& angajat);
    friend ostream& operator<<(ostream &out, Angajat& angajat);
    static  void nrObiecte()
    {
        cout<<nr;
    }
    int get_ann()
    {
        return data_angajare.get_an();

    }
    virtual int get_nr_minori_intretinere() {}

    virtual int get_annn() {}

    virtual char* get_lunaaa() {}

};
class Part_Time: public Angajat
{
private:
    int nr_ore_zi;
    Data final_contract;
public:

    Part_Time();
    Part_Time(int nr_ore_zi, Data final_contract, string numept, string prenumept, float salariupt, Data data_angajarept);
    Part_Time(Part_Time&);
    ~Part_Time();
    Part_Time& operator=(Part_Time &part_time);
    void citire(istream &in);
    void afisare(ostream &out);
    friend istream& operator>>(istream &in, Part_Time& part_time);
    friend ostream& operator<<(ostream &out, Part_Time& part_time);
    int get_nr_minori_intretinere() {};

    int get_annn()
    {
        return final_contract.get_an();
    }
    char* get_lunaaa()
    {
        return final_contract.get_luna();
    }
};

class Permanent: public Angajat
{
private:
    int nr_minori_intretinere;
public:

    Permanent();
    Permanent(int nr_minori_intretinere, string numep, string prenumep, float salariup, Data data_angajarep);
    Permanent(Permanent&);
    ~Permanent();
    Permanent& operator=(Permanent &permanent);
    void citire(istream &in);
    void afisare(ostream &out);
    friend istream& operator>>(istream &in, Permanent& permanent);
    friend ostream& operator<<(ostream &out, Permanent& permanent);
    int get_nr_minori_intretinere()
    {
        return nr_minori_intretinere;
    }
    int get_annn() {}
    char* get_lunaaa() {}

};


Data::Data(Data &data)
{
    this->zi = data.zi;
    this->an = data.an;
    this->luna = new char[strlen(data.luna) + 1];
    strcpy(this->luna, data.luna);
}
Data::~Data()
{
    zi = 0;
    delete(this->luna);
    an = 0;

}
Data& Data::operator=(Data &data)
{
    zi = data.zi;
    an = data.an;
    luna = new char[strlen(data.luna) + 1];
    strcpy(luna, data.luna);
}
void Data::citire(istream &in)
{
    cout<<"Cititi ziua:";
    in>>zi;
    cout<<"Cititi luna: ";
    in>>luna;
    cout<<"Cititi anul:";
    in>>an;
}
istream& operator>>(istream& in, Data& data)
{
    data.citire(in);
    return in;
}

void Data::afisare(ostream &out)
{
    out<<"Data este: ";
    out<<zi<<' '<<luna<<' '<<an<<endl;
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
void Data::set_luna(char* y)
{
    strcpy(luna, y);
}
void Data::set_an(int z)
{
    an = z;
}

///--------------------------------------------------------------------------------------------------------

Part_Time::Part_Time():Angajat()
{
    this->nr_ore_zi= 0;
}
Part_Time::Part_Time(int nr_ore_zi, Data final_contract, string numept, string prenumept, float salariupt, Data data_angajarept):Angajat(numept, prenumept, salariupt, data_angajarept), final_contract(final_contract)
{
    this->nr_ore_zi = nr_ore_zi;

}

Part_Time::Part_Time(Part_Time &part_time)
{
    this->nr_ore_zi = part_time.nr_ore_zi;
    this->final_contract = part_time.final_contract;
    this->nr_ore_zi = part_time.nr_ore_zi;
    this->final_contract = part_time.final_contract;
    this->nume = part_time.nume;
    this->prenume = part_time.prenume;
    this->salariu = part_time.salariu;
    this->data_angajare = part_time.data_angajare;
}
Part_Time::~Part_Time()
{
    nr_ore_zi = 0;
    this->nume = "";
    this->prenume = "";
    this->salariu = 0.0;
    data_angajare.set_zi(0);
    data_angajare.set_luna("");
    data_angajare.set_an(0);
    final_contract.set_zi(0);
    final_contract.set_luna("");
    final_contract.set_an(0);

}
Part_Time& Part_Time::operator=(Part_Time &part_time)
{
    nr_ore_zi = part_time.nr_ore_zi;
    final_contract = part_time.final_contract;
    nume = part_time.nume;
    prenume = part_time.prenume;
    salariu = part_time.salariu;
    data_angajare = part_time.data_angajare;
}
void Part_Time::citire(istream &in)
{
    Angajat::citire(in);
    cout<<"Cititi numarul de ore: "<<endl;
    in>>nr_ore_zi;
    cout<<"Urmeaza sa cititi data de final a contractului."<<endl;
    in>>final_contract;
}
istream& operator>>(istream& in, Part_Time& part_time)
{
    part_time.citire(in);
    return in;
}

void Part_Time::afisare(ostream &out)
{
    Angajat::afisare(out);
    out<<endl;
    out<<"Numarul de ore lucrate pe zi este: "<<endl;
    out<<nr_ore_zi<<endl;
    out<<final_contract<<endl;

}
ostream& operator<<(ostream& out, Part_Time& part_time)
{
    part_time.afisare(out);
    return out;
}

///--------------------------------------------------------------------------------------------------------

Permanent::Permanent():Angajat()
{
    this->nr_minori_intretinere = 0;

}
Permanent::Permanent(int nr_minori_intretinere, string numep, string prenumep, float salariup, Data data_angajarep):Angajat(numep, prenumep, salariup, data_angajarep)
{
    this->nr_minori_intretinere = nr_minori_intretinere;

}
Permanent::Permanent(Permanent &permanent)
{
    this->nr_minori_intretinere = permanent.nr_minori_intretinere;
    this->nume = permanent.nume;
    this->prenume = permanent.prenume;
    this->salariu = permanent.salariu;
    this->data_angajare = permanent.data_angajare;
}
Permanent::~Permanent()
{
    this->nr_minori_intretinere = 0;
    this->nume = "";
    this->prenume = "";
    this->salariu = 0.0;
    data_angajare.set_zi(0);
    data_angajare.set_luna("");
    data_angajare.set_an(0);
}
Permanent& Permanent::operator=(Permanent &permanent)
{
    nr_minori_intretinere = permanent.nr_minori_intretinere;
    nume = permanent.nume;
    prenume = permanent.prenume;
    salariu = permanent.salariu;
    data_angajare = permanent.data_angajare;
}
void Permanent::citire(istream &in)
{

    Angajat::citire(in);
    cout<<"Cititi numarul de copii minori ai angajatului: "<<endl;
    in>>nr_minori_intretinere;
}
istream& operator>>(istream& in, Permanent& permanent)
{
    permanent.citire(in);
    return in;
}

void Permanent::afisare(ostream &out)
{
    Angajat::afisare(out);
    out<<endl;
    out<<"Numarul de copii minori ai angajatului: "<<endl;
    out<<nr_minori_intretinere<<endl;

}
ostream& operator<<(ostream& out, Permanent& permanent)
{
    permanent.afisare(out);
    return out;
}

///-------------------------------------------------------------------------------

int Angajat::nr;
Angajat::Angajat()
{
    nr++;
    this->nume = "";
    this->prenume = "";
    this->salariu = 0.0;
    Data data_angajare;

}

Angajat::Angajat(Angajat &angajat)
{
    this->nume = angajat.nume;
    this->prenume = angajat.prenume;
    this->salariu = angajat.salariu;
    this->data_angajare = angajat.data_angajare;
}
Angajat::~Angajat()
{
    this->nume = "";
    this->prenume = "";
    this->salariu = 0.0;
    data_angajare.set_zi(0);
    data_angajare.set_luna("");
    data_angajare.set_an(0);

}
Angajat& Angajat::operator=(Angajat &angajat)
{
    nume = angajat.nume;
    prenume = angajat.prenume;
    salariu = angajat.salariu;
    data_angajare = angajat.data_angajare;
}
void Angajat::citire(istream &in)
{
    cout<<"Cititi numele: ";
    in>>nume;
    cout<<"Cititi prenumele: ";
    in>>prenume;
    cout<<"Cititi salariul:";
    in>>salariu;
    in>>data_angajare;
}
istream& operator>>(istream& in, Angajat& angajat)
{
    angajat.citire(in);
    return in;
}

void Angajat::afisare(ostream &out)
{
    out<<"Numele angajatului este: "<<endl;
    out<<nume<<' '<<prenume<<endl;
    out<<"Salariul angajatului este: "<<endl;
    out<<salariu<<endl;
    out<<data_angajare;
}
ostream& operator<<(ostream& out, Angajat& angajat)
{
    angajat.afisare(out);
    return out;
}



void menu_output()
{
    cout<<"\n Boghiu Alexandra-Adriana Grupa 134 - Proiect 2 - Nume proiect: Salarizare (nr 3)\n";
    cout<<"\n\t MENIU:";
    cout<<"\n===========================================\n";
    cout<<"\n";
    cout<<"1. Citirea, memorarea si afisarea a n obiecte";
    cout<<"\n";
    cout<<"2. Citirea, memorarea a n obiecte si calcularea primei";
    cout<<"\n";
    cout<<"3. Upcasting si downcasting";
    cout<<"\n";
    cout<<"4. Afisarea numarului de obiecte create pana in acest moment";
    cout<<"\n";
    cout<<"0. Iesire.";
    cout<<"\n";
}
void menu()
{
    int option;///optiunea aleasa din meniu
    option=0;

    do
    {
        menu_output();

        cout<<"\nIntroduceti numarul actiunii: ";
        cin>>option;

        if (option==1)
        {
            cout<<"Introduceti numarul de angajati: "<<endl;
            cin>>n;
            Angajat **obiecte = new Angajat*[n];

            for(int i = 0; i < n; i++)
            {
                cout<<"Obiectul este de tip Part_Time sau Permanent?"<<endl<<"1. Part_Time"<<endl<<"2. Permanent"<<endl;
                int nr;
                cin>>nr;
                if (nr == 1)
                {
                    Angajat *p = new Part_Time;
                    cin>>*p;
                    obiecte[i] = p;
                }
                else if (nr == 2)
                {
                    Angajat *p = new Permanent;
                    cin>>*p;
                    obiecte[i] = p;
                }
            }
            for(int i = 0; i < n; i++)
                cout<<*obiecte[i]<<endl;
            delete []obiecte;
        }
        if (option==2)
        {
            cout<<"Introduceti numarul de angajati: "<<endl;
            cin>>n;
            Angajat **obiecte = new Angajat*[n];
            float valori_prima[n];
            for(int i = 0; i < n; i++)
            {
                cout<<"Obiectul este de tip Part_Time sau Permanent?"<<endl<<"1. Part_Time"<<endl<<"2. Permanent"<<endl;
                int nr;
                cin>>nr;
                if (nr == 1)
                {
                    Angajat *p = new Part_Time;  //downcast
                    cin>>*p;
                    obiecte[i] = p;
                }
                else if (nr == 2)
                {
                    Angajat *p = new Permanent;
                    cin>>*p;
                    obiecte[i] = p;
                }


                Data data_curenta;
                cout<<"Introduceti data curenta: "<<endl;
                cin>>data_curenta;
                float prima;
                cout<<"Introduceti suma standard(prima): "<<endl;
                cin>>prima;

                for(int i = 0; i < n; i++)
                {
                    if(strstr(typeid(*obiecte[i]).name(), "Permanent"))
                    {

                        int an_angajare = obiecte[i]->get_ann();
                        if(an_angajare < 2020)
                            valori_prima[i] = prima + (2020 - an_angajare) * (obiecte[i]->get_nr_minori_intretinere())*prima/100;
                        else
                            valori_prima[i] = prima;
                    }
                    else
                    {

                        if (obiecte[i]->get_annn() == data_curenta.get_an() && strcmp(obiecte[i]->get_lunaaa(), data_curenta.get_luna()) == 0)
                            valori_prima[i] = 0.75 * prima;
                        else
                            valori_prima[i] = prima;

                    }
                }
            }
                for(int i = 0; i < n; i++)
                    cout<<valori_prima[i]<<" ";

            delete []obiecte;
        }
        if (option==3)
        {
            Part_Time *x = (Part_Time*)new Angajat;

            cout<<"Upcasting: "<<typeid(*x).name()<<endl;

            Angajat *xx = new Part_Time;

            cout<<"Downcasting: "<<typeid(*xx).name();

        }
        if(option==4)
        {
            Angajat::nrObiecte();
        }
        if (option==0)
        {
            cout<<"\nEXIT!\n";
        }
        if (option<0||option>4)
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
    ///Am considerat ca nu se pot introduce date gresite, iar anul curent nu este mai mare decat 2020.
    menu();
    return 0;
}

