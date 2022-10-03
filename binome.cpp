#include <iostream>

using namespace std;

struct t_etudiant {
    string nom;
    t_etudiant* p_binome;
    double* p_note;
};

struct t_binome {
    t_etudiant* etuA, *etuB;
    bool complet;
};                     
                    
struct t_tab_binome { 
    t_binome* tab_binome;
    int capa;
    int occup;
};

//1 TODO: init etudiant sans binome sans note
void init_etudiant(string nomEtu, t_etudiant & etudiant){
    etudiant.nom = nomEtu;
    etudiant.p_binome = nullptr;
    etudiant.p_note = nullptr;
}

//2 DONE
void creerBinome(t_etudiant & e1, t_etudiant & e2, t_tab_binome & tab){ 
    if(tab.occup<tab.capa && e1.p_binome == nullptr && e2.p_binome == nullptr ){ //il faut que les etudiants n'aient pas de binomes 
        e1.p_binome = &e2; //pointeur vers l'autre etudiant
        e2.p_binome = &e1;
        tab.occup+=1;
        tab.tab_binome->etuA = &e1; //pk (*tab.tab_binome).etuA ne marche pas ?
        tab.tab_binome->etuB = &e2;
        tab.tab_binome->complet = true;

    }else{
        cout<<"l'un des etudiants est deja dans un binome"<<endl;
    }
}

//3 TODO: (e, note) e ayant un binome, affecter une note au binome   


//4 TODO: (e1), afficher e1 + e2 + note

//5 TODO: (e) e ayant un binome, dissocier et retirer note

int main() {

    int N = 0;
    while(N<=0){
        cout<<"Nombre d'etudiants"<<endl;
        cin>>N;
    }
    
    int nbBi = (N/2) + 1; // nombre de binomes possibles... si impair, l'etudiant seul sera dans un binome mais aura une moyenne plus élevée
    
    t_etudiant* tab_etu; 
    tab_etu = new t_etudiant[N];
    t_tab_binome tTabBinome;
    
    tTabBinome.tab_binome = new t_binome[nbBi];
    tTabBinome.capa = nbBi;
    tTabBinome.occup = 0; // tableau encore vide

    for(int i=0; i<N; i++){
        cout<<"Nom etudiant"<<endl;
        cin>>tab_etu[i].nom;
    }




    delete[] tab_etu;
    tab_etu = nullptr;
    delete[] tTabBinome.tab_binome;
    tTabBinome.tab_binome = nullptr;
}