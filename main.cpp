#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

class PlanActivitate;
class Turist;
class Destinatie;

class Preferinta{

protected:

     string nume;

public:
    Preferinta(){}
    Preferinta(string s):nume(s){}
    Preferinta(const Preferinta& P):nume(P.nume){}
    ~Preferinta(){}

    int operator==(const Preferinta &P){

        return nume==P.nume;

    }
    size_t find(const Preferinta &P){

        return nume.find(P.nume);

    }
    friend istream& operator>>(istream &in,Preferinta& P){

        cin>>P.nume;
        return in;

    }
    friend ostream& operator<<(ostream &out,Preferinta& P){

        cout<<P.nume;
        return out;

    }
    friend Turist;
    friend Destinatie;
    friend PlanActivitate;

};

class Activitate: public Preferinta{

    string descriere;
    int durata;
    int esteRelaxare;
    int esteDrumetie;
    int esteVizitare;
public:
    Activitate():Preferinta(){}
    Activitate(const Preferinta& P):Preferinta(P){}
    Activitate(const Activitate& A,int d=0):Preferinta(A){

        descriere=A.descriere;
        if(d) durata=d;
        else durata=A.durata;
        esteRelaxare=A.esteRelaxare;
        esteDrumetie=A.esteDrumetie;
        esteVizitare=A.esteVizitare;

    }
    Activitate(string s,int d=0):descriere(s),durata(d){

        esteRelaxare=esteDrumetie=esteVizitare=0;
        string a; string b;

        for(int i=0;s[i]!=' ';i++)
            b+=s[i];
        if(b=="relaxare") esteRelaxare=1;
        if(b=="drumetie") esteDrumetie=1;
        if(b=="vizitare") esteVizitare=1;

        for(int i=s.size()-1;s[i]!=' ';i--)
            a+=s[i];
        reverse(a.begin(),a.end());
        Preferinta::nume=a;

    }
    ~Activitate(){}

    int operator<(Activitate& A){

        if(esteDrumetie) return 1;
        if(A.EsteDrumetie()) return 0;
        if(esteVizitare) return 1;
        if(A.EsteVizitare()) return 0;
        return 1;

    }
    int daDurata(){return durata;}
    string daDescriere(){return descriere;}
    int EsteRelaxare(){return esteRelaxare;}
    int EsteDrumetie(){return esteDrumetie;}
    int EsteVizitare(){return esteVizitare;}
    friend istream& operator>>(istream &in,Activitate& A){

        A.esteRelaxare=A.esteDrumetie=A.esteVizitare=0;
        string a; string b;
        getline(cin,a); a.clear();
        getline(cin,A.descriere);

        for(int i=0;A.descriere[i]!=' ';i++)
            b+=A.descriere[i];
        if(b=="relaxare") A.esteRelaxare=1;
        if(b=="drumetie") A.esteDrumetie=1;
        if(b=="vizitare") A.esteVizitare=1;


        for(int i=A.descriere.size()-1;A.descriere[i]!=' ';i--)
            a+=A.descriere[i];
        reverse(a.begin(),a.end());
        A.nume=a;
        cin>>A.durata;
        return in;

    }
    friend ostream& operator<<(ostream &out,Activitate& A){

        cout<<A.descriere<<' '<<A.durata;
        return out;

    }


};

class Turist{

    char sex;
    int grupaVarsta;
    vector<Preferinta> lista;
public:
    Turist(){}
    Turist(char s,int g):sex(s),grupaVarsta(g){}
    ~Turist(){}
    friend istream& operator>>(istream &in,Turist& T){

        cout<<"Introduceti litera pentru sex(masculin - >M,feminin -> F): ";
        cin>>T.sex;
        cout<<"Introduceti grupa de varsta(0-14 -> 1,15-34 -> 2,35-64 -> 3, peste 64 -> 4): ";
        cin>>T.grupaVarsta;
        cout<<"Introduceti numarul de preferinte: ";
        int nrPreferinte;
        cin>>nrPreferinte;
        cout<<"Introduceti cate o preferinta pe fiecare linie:\n";
        T.lista.resize(nrPreferinte+1);
        for(int i=1;i<=nrPreferinte;i++)
            cin>>T.lista[i];
        return in;

    }
    friend ostream& operator<<(ostream &out,Turist& T){

        cout<<"Sexul: ";
        switch(T.sex){

            case 'M': cout<<"masculin\n"; break;
            case 'F': cout<<"feminin\n"; break;

        }
        cout<<"Grupa de varsta: ";
        switch(T.grupaVarsta){

            case 1: cout<<"0-14\n"; break;
            case 2: cout<<"15-34\n"; break;
            case 3: cout<<"35-64\n"; break;
            case 4: cout<<"peste 64\n"; break;

        }
        cout<<"Preferintele:\n";
        for(unsigned i=1;i<T.lista.size();i++)
            cout<<T.lista[i]<<"\n";
        return out;

    }
    friend PlanActivitate;
};

class Destinatie{

    string nume;
    vector<Activitate> lista;

public:
    Destinatie(){}
    Destinatie(string s,int d){

        Activitate A(s,d);
        lista.push_back(A);

    }
    ~Destinatie(){}

    friend istream& operator>>(istream &in,Destinatie& D){

        cout<<"Numele destinatiei: "; cin>>D.nume;
        cout<<"Numarul de activitati: ";
        int nrActivitati; cin>>nrActivitati;
        cout<<"Introduceti cate o activitate pe cate doua linii(o linie descrierea si o linie durata):\n";
        D.lista.resize(nrActivitati+1);
        for(int j=1;j<=nrActivitati;j++)
            cin>>D.lista[j];
        return in;

    }
    friend ostream& operator<<(ostream &out,Destinatie& D){

        cout<<"Numele destinatiei: "<<D.nume<<"\n";
        cout<<"Numarul de activitati: "<<D.lista.size()-1<<"\n";
        cout<<"Activitatile:\n";
        for(unsigned j=1;j<D.lista.size();j++)
            cout<<D.lista[j]<<"\n";
        return out;

    }
    friend PlanActivitate;
};

class PlanActivitate{

    string nume;
    vector<Activitate> Relaxari;
    vector<Activitate> Drumetii;
    vector<Activitate> Vizitari;

public:
    PlanActivitate(){}
    PlanActivitate(vector<Destinatie> D,vector<Turist> T){

        double Satisfacere;
        double cantitateSatisfacere;
        double procentSatisfacere;
        double sumaSatisfacere;
        double MaxSatisfacere=0;
        vector<Activitate> lista;
        vector<Activitate> Rezultat;

        for(unsigned j=1;j<D.size();j++){

            Activitate dummy("");
            Rezultat.push_back(dummy);

            procentSatisfacere=0;

            for(unsigned i=1;i<T.size();i++){

                sumaSatisfacere=0;

                for(unsigned k=1;k<T[i].lista.size();k++){

                    cantitateSatisfacere=0;

                    for(unsigned p=1;p<D[j].lista.size();p++){

                        if(D[j].lista[p].find(T[i].lista[k])!=string::npos){

                            Satisfacere=1;
                            vector<Activitate>::iterator it;
                            it=find(Rezultat.begin(),Rezultat.end(),D[j].lista[p]);
                            if(it==Rezultat.end())
                                Rezultat.push_back(D[j].lista[p]);

                        }

                        else Satisfacere=0;

                        cantitateSatisfacere=max(cantitateSatisfacere,Satisfacere);

                    }

                    sumaSatisfacere+=cantitateSatisfacere;

                }

                sumaSatisfacere=sumaSatisfacere/(T[i].lista.size()-1)*100;

                if(sumaSatisfacere<50){

                    procentSatisfacere=0;
                    break;

                }

                procentSatisfacere+=sumaSatisfacere;

            }

            procentSatisfacere=procentSatisfacere/(T.size()-1);

            if(MaxSatisfacere<procentSatisfacere){

                MaxSatisfacere=procentSatisfacere;
                lista=Rezultat;
                nume=D[j].nume;

            }

            Rezultat.clear();

        }

        for(unsigned i=1;i<lista.size();i++)
            if(lista[i].EsteDrumetie()){

                int catDurata=lista[i].daDurata()/2;
                int restDurata=lista[i].daDurata()%2;
                Activitate A1(lista[i],catDurata+restDurata);
                Activitate A2(lista[i],catDurata);
                Drumetii.push_back(A1);
                Drumetii.push_back(A2);

            }
            else if(lista[i].EsteVizitare())
                Vizitari.push_back(lista[i]);
            else
                Relaxari.push_back(lista[i]);



    }
    ~PlanActivitate(){}

    friend ostream& operator<<(ostream &out,PlanActivitate P){

        cout<<"Destinatia aleasa este: "<<P.nume<<"\n";
        cout<<"Lista de activitati este:\n";
        int z=1;
        int r,c,ld,lr,lv;
        ld=P.Drumetii.size();
        lr=P.Relaxari.size();
        lv=P.Vizitari.size();

        while(ld || lr || lv){

            r=12; c=8;
            cout<<"Ziua "<<z<<"\n";

            cout.flush();

            while(ld && P.Drumetii[ld-1].daDurata()<=r){

                c+=P.Drumetii[ld-1].daDurata();
                if(c<10) cout<<"0";
                cout<<c<<":00 ";
                cout<<P.Drumetii[ld-1].daDescriere()<<"\n";
                r-=P.Drumetii[ld-1].daDurata();
                P.Drumetii.pop_back(); --ld;

            }

            while(lv && P.Vizitari[lv-1].daDurata()<=r){

                c+=P.Vizitari[lv-1].daDurata();
                if(c<10) cout<<"0";
                cout<<c<<":00 ";
                cout<<P.Vizitari[lv-1].daDescriere()<<"\n";
                r-=P.Vizitari[lv-1].daDurata();
                P.Vizitari.pop_back(); --lv;

            }

            while(lr && P.Relaxari[lr-1].daDurata()<=r){

                c+=P.Relaxari[lr-1].daDurata();
                if(c<10) cout<<"0";
                cout<<c<<":00 ";
                cout<<P.Relaxari[lr-1].daDescriere()<<"\n";
                r-=P.Relaxari[lr-1].daDurata();
                P.Relaxari.pop_back(); --lr;

            }

            ++z;

        }

        return out;

    }


};

int main(){

    int nrDestinatii;
    int nrTuristi;
    vector<Destinatie> D;
    vector<Turist> T;

    {///Citire
    cout<<"Introduce numarul de destinatii: ";
    cin>>nrDestinatii;
    D.resize(nrDestinatii+1);

    for(int i=1;i<=nrDestinatii;i++){

        cout<<"Destinatia "<<i<<"\n";
        cin>>D[i];
        cout<<"\n";

    }cout<<"\n***********************\n";

    cout<<"Introduce numarul de turisti: ";
    cin>>nrTuristi;
    T.resize(nrTuristi+1);

    for(int i=1;i<=nrTuristi;i++){

        cout<<"Turist "<<i<<"\n";
        cin>>T[i];
        cout<<"\n";

    }cout<<"\n***********************\n";
    }

    {///Afisare

    for(int i=1;i<=nrDestinatii;i++){

        cout<<"Destinatia "<<i<<"\n";
        cout<<D[i]<<"\n";

    }cout<<"\n***********************\n";

    for(int i=1;i<=nrTuristi;i++){

        cout<<"Turist "<<i<<"\n";
        cout<<T[i]<<"\n";

    }cout<<"\n***********************\n";

    }

    PlanActivitate P(D,T);
    cout<<P;

}
