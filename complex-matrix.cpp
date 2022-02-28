#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std;
/// Cod preluat din laborator


class complex
{
private:
    double real;
    double imaginar;
public:

    complex ();
    complex (double, double);
    complex (complex&);
    ~complex ();
    void set_real(double);
    void set_imaginar(double);
    double get_real()
    {
        return real;
    };
    double get_imag()
    {
        return imaginar;
    };
    void afisare(ostream &out);
    void citire(istream &in);
    friend istream& operator>>(istream &in, complex& z);
    friend ostream& operator<<(ostream &out, complex& z);
    double modul();
    complex& operator=(complex &z);
    friend complex& operator+(complex& z1, complex& z2);
    friend complex& operator*(complex& z1, complex& z2);
    friend complex& operator/(complex& z1, complex& z2);

    friend class Matrice_Complexa; /// clasa prietena
};

complex::complex()
{
    this->real = 0;
    this->imaginar = 0;
}

complex::complex(double real, double imaginar)
{
    this->real = real;
    this->imaginar = imaginar;
}

complex::complex(complex &z)
{
    this->real = z.real;
    this->imaginar = z.imaginar;
}
complex::~complex()
{
    this->real=0;
    this->imaginar=0;
}


void complex::citire(istream &in)
{
    cout<<"Cititi partea reala: ";
    in>>real;
    cout<<"Cititi partea imaginara: ";
    in>>imaginar;
}
void complex::set_real(double x)
{
    real = x;
}
void complex::set_imaginar(double y)
{
    imaginar=y;
}

istream& operator>>(istream& in,complex& z)
{
    z.citire(in);
    return in;
}
void complex::afisare(ostream &out)
{
    if (imaginar==0)
    {
        out<<real;
    }
    else
    {
        if (imaginar < 0)
        {
            out<<real<<imaginar<<"*i";
        }
        else
        {
            out<<real<<"+"<<imaginar<<"*i";
        }
    }
}
ostream& operator<<(ostream& out, complex& z)
{
    z.afisare(out);
    return out;
}
double complex::modul()
{
    return sqrt(real*real+imaginar*imaginar);
}
complex& complex::operator=(complex &z)
{
    real=z.real;
    imaginar=z.imaginar;
}
inline complex& operator+(complex &z1, complex& z2)
{
    complex *z = new complex;
    z->real = z1.real + z2.real;
    z->imaginar = z1.imaginar + z2.imaginar;
    return *z;
}
inline complex& operator*(complex &z1, complex& z2)
{
    complex *z=new complex;
    z->real = z1.real * z2.real - z1.imaginar * z2.imaginar;
    z->imaginar = z1.real * z2.imaginar + z2.real * z1.imaginar;
    return *z;
}
complex& operator/(complex &z1, complex &z2)
{
    complex *z=new complex;
    z->real = (z1.real*z2.real + z1.imaginar * z2.imaginar) / (z2.real * z2.real + z2.imaginar * z2.imaginar);
    z->imaginar = (z2.real * z1.imaginar - z1.real * z2.imaginar) / (z2.real * z2.real + z2.imaginar * z2.imaginar);
    return *z;
}

/// Clasa Matrice_Complexa

class Matrice_Complexa
{
private:   ///date membre private

    int nr_linii;
    int nr_coloane;
    complex **valori;

public:
    Matrice_Complexa(complex, int, int );   ///constructor pt initializarea cu un nr complex dat pe toate componentele = constructor pt initializare cu parametri
    Matrice_Complexa(); ///constructor pt initializare fara parametri
    Matrice_Complexa(Matrice_Complexa&);  ///constructor de copiere

    ~Matrice_Complexa(); ///destructor

    void set_linii(int); /// set pt linii
    void set_coloane(int); ///set pt coloane
    void set_valori(complex**); ///set pt valori

    void citire(istream &in); ///functie pt citire
    void afisare(ostream &out); ///functie pt afisare
    void citire_obiecte(); ///metoda publica prin care se realizeaza citirea informatiilor complete a n obiecte, memorarea si afisarea lor

    int get_linii() /// get pt linii
    {
        return nr_linii;
    };
    int get_coloane() ///get pt coloane
    {
        return nr_coloane;
    };
    complex get_valori()///get pt valori
    {
        return **valori;
    };

    friend istream& operator>>(istream &in, Matrice_Complexa& valori); ///supraincarcarea operatorului >>
    friend ostream& operator<<(ostream &out, Matrice_Complexa& valori); ///supraincarcarea operatorului <<

    Matrice_Complexa& operator=(const Matrice_Complexa&); ///supraincarcarea operatorului =
    friend  Matrice_Complexa operator+(const Matrice_Complexa&, const Matrice_Complexa&); ///supraincarcarea operatorului +
    friend  Matrice_Complexa operator*(const Matrice_Complexa&, const Matrice_Complexa&); ///supraincarcarea operatorului *

    Matrice_Complexa suma (const Matrice_Complexa& A, const Matrice_Complexa& B); ///metoda pentru calcularea sumei a doua matrice
    Matrice_Complexa produs (const Matrice_Complexa& A, const Matrice_Complexa& B); ///metoda pentru calcularea produsului a doua matrice
};
void Matrice_Complexa::set_linii(int l)
{
    nr_linii = l;
}
void Matrice_Complexa::set_coloane(int c)
{
    nr_coloane = c;
}
void Matrice_Complexa::set_valori(complex **Matrice_oarecare)
{
    for (int i = 0; i < nr_linii; i++)
        for (int j = 0; j < nr_coloane; j++)
        {
            valori[i][j] = Matrice_oarecare[i][j];

        }
}
Matrice_Complexa::Matrice_Complexa(complex nr, int l, int c)
{
    nr_linii = l;
    nr_coloane = c;
    valori = new complex*[nr_linii];
    for(int i = 0; i < nr_linii; i++)
        valori[i] = new complex[nr_coloane];

    for (int i = 0; i < nr_linii; i++)
        for (int j = 0; j < nr_coloane; j++)
            valori[i][j] = nr;

}
Matrice_Complexa::Matrice_Complexa(Matrice_Complexa& A)
{
   this->nr_linii = A.nr_linii;
    this->nr_coloane = A.nr_coloane;
     for (int i = 0; i < nr_linii; i++)
        for (int j = 0; j < nr_coloane; j++)
            this->valori[i][j] = A.valori[i][j];
}
Matrice_Complexa::Matrice_Complexa()
{
    this->nr_linii = 0;
    this->nr_coloane = 0;
}

Matrice_Complexa::~Matrice_Complexa()
{
    for(int i = 0; i < this->nr_linii; i++)
        delete[] this->valori[i];
    delete[] this->valori;
}

void Matrice_Complexa::citire(istream &in)
{
    cout<<"Introduceti numarul de linii: ";
    in>>this->nr_linii;
    cout<<"Introduceti numarul de coloane: ";
    in>>this->nr_coloane;

    cout<<"Introduceti elementele matricei: ";
    valori = new complex*[this->nr_linii];

    for(int i = 0; i < this->nr_linii; i++)
        valori[i] = new complex[this->nr_coloane];

    for(int i = 0; i < this->nr_linii; i++)
        for(int j = 0; j < this->nr_coloane; j++)
            in>>this->valori[i][j];

}

istream & operator>>(istream& in, Matrice_Complexa& valori)
{
    valori.citire(in);
    return in;
}
void Matrice_Complexa::afisare(ostream& out)
{
    for(int i = 0; i < this->nr_linii; i++)
    {
        for(int j = 0; j < this->nr_coloane; j++)
            out<<this->valori[i][j]<<" ";
        out<<endl;
    }

}
ostream& operator<<(ostream& out, Matrice_Complexa& valori)
{
    valori.afisare(out);
    return out;
}
Matrice_Complexa& Matrice_Complexa::operator=(const Matrice_Complexa &Matrice_Oarecare)
{
    if(this == &Matrice_Oarecare) return *this;

    for (int i  = 0; i < nr_linii; i ++)
        delete[] valori[i];

    if(nr_linii !=0)
        delete[] valori;

    nr_linii = Matrice_Oarecare.nr_linii;
    nr_coloane = Matrice_Oarecare.nr_coloane;

    valori = new complex*[nr_linii];
    for (int i = 0; i  < nr_linii; i ++)
        valori[i] = new complex[nr_coloane];

    for (int i = 0; i  < nr_linii; i ++)
        for (int j = 0; j< nr_coloane; j++)
            valori[i][j] = Matrice_Oarecare.valori[i][j];

    return *this;
}
Matrice_Complexa operator+(const Matrice_Complexa &A, const Matrice_Complexa& B)
{
    complex numar(0,0);
    Matrice_Complexa C(numar, A.nr_linii, A.nr_coloane);
    if (A.nr_linii != B.nr_linii || A.nr_coloane != B.nr_coloane)
    {
        cout<<"Nu se pot aduna din cauza dimensiunilor. Se va returna o matrice nula."<<endl;
        return C;
    }
    else
    {
        for(int i = 0; i < C.nr_linii; i++)
            for(int j = 0; j < C.nr_coloane; j++)
                C.valori[i][j] = A.valori[i][j] + B.valori[i][j];
        return C;
    }
}
Matrice_Complexa operator*(const Matrice_Complexa& A, const Matrice_Complexa& B)
{


    complex numar(0,0);
    Matrice_Complexa C(numar, A.nr_linii, B.nr_coloane);
    if (A.nr_coloane != B.nr_linii)
    {
        cout<<"Nu se pot inmulti din cauza dimensiunilor. Se va returna o matrice nula."<<endl;
        return C;
    }
    for (int i = 0; i < A.nr_linii; i++)
        for (int j = 0; j < A.nr_coloane; j++)
            for (int k = 0; k < B.nr_coloane; k++)
                C.valori[i][j] = C.valori[i][j] + (A.valori[i][k] * B.valori[k][j]);

    return C;

}
Matrice_Complexa Matrice_Complexa::suma(const Matrice_Complexa& A, const Matrice_Complexa& B)
{
    complex numar(0,0);
    Matrice_Complexa D(numar, A.nr_linii, B.nr_coloane);
    D = A + B;
    return D;
}
Matrice_Complexa Matrice_Complexa::produs(const Matrice_Complexa& A, const Matrice_Complexa& B)
{
    complex numar(0,0);
    Matrice_Complexa E(numar, A.nr_linii, B.nr_coloane);
    E = A * B;
    return E;
}
void Matrice_Complexa::citire_obiecte()
{
    int nr;
    cout<<"Introduceti numarul de matrice care sa fie citite:  ";
    cin>>nr;
    cout<<endl;
    Matrice_Complexa *valori = new Matrice_Complexa[nr];
    for(int i = 0; i < nr; i++)
    {
        cin>>valori[i];
        cout<<valori[i];
    }

}
void menu_output()
{
    cout<<"\n Boghiu Alexandra-Adriana Grupa 134 - Proiect 2 - Nume proiect: Matrice_Complexa\n";
    cout<<"\n\t MENIU:";
    cout<<"\n===========================================\n";
    cout<<"\n";
    cout<<"1. Citire, memorare si afisare a n obiecte";
    cout<<"\n";
    cout<<"2. Constructor pentru initializarea matricei cu un numar";
    cout<<"\n";
    cout<<"3. Suma a doua matrice";
    cout<<"\n";
    cout<<"4. Produsul a doua matrice";
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
        menu_output(); ///codul pt meniu este preluat din laborator

        cout<<"\nIntroduceti numarul actiunii: ";
        cin>>option;

        if (option == 1)
        {
            Matrice_Complexa M;
            M.citire_obiecte();
        }
        if (option == 2)
        {
            int l, c;
            complex nr;
            cout<<"Introduceti dimensiunile matricei.\n";
            cout<<"Introduceti numarul de linii.\n";
            cin>>l;
            cout<<"Introduceti numarul de coloane.\n";
            cin>>c;
            cout<<"Introduceti numarul cu care doriti sa fie initializata matricea.\n";
            cin>>nr;
            Matrice_Complexa M(nr, l, c);
            cout<<M;
        }
        if (option == 3)
        {
            cout<<"Urmeaza sa introduceti, pe rand, cele doua matrice.\n";
            Matrice_Complexa A, B, C;
            cin>>A;
            cin>>B;
            C = A + B;
            cout<<C;
        }
        if (option == 4)
        {
            cout<<"Urmeaza sa introduceti, pe rand, cele doua matrice.\n";
            Matrice_Complexa A, B, C;
            cin>>A;
            cin>>B;
            C = A * B;
            cout<<C;
        }
        if (option==0)
        {
            cout<<"\nEXIT!\n";
        }
        if (option < 0||option > 4)
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


