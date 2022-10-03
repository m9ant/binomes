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

t_etudiant etuFantome;// servira quand il y aura un nombre impair d'étudiants



//1 DONE
void initEtu(string nomEtu, t_etudiant & etudiant){
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

//3 DONE   
void notePourBinome(t_etudiant & etu, double & note){ // note en ref pour acceder a l'adresse réelle, non pas celle du parametre qui est locale
    if(etu.p_binome == nullptr){
        cout<<"cet etudiant n'a pas de binome, donc pas de note"<<endl; 
    }else{
        etu.p_note = &note;
    }
}

//4 DONE
void infoBinome(t_etudiant & etu){
    if(etu.p_note == nullptr){
        cout<<"cet etudiant n'a pas de binome/note"<<endl;
    }else{
        cout<<"Nom etu 1: "<<etu.nom<<endl;
        cout<<"Nom etu 2: "<<etu.p_binome->nom<<endl;
        cout<<"La note  : "<<*(etu.p_note)<<endl;
    }
}

//5 DONE
void dissocier(t_etudiant & etu){
    etu.p_binome->p_binome = nullptr; //on dissocie en premier l'autre etudiant ensuite l'etudiant passé en paramètre
    etu.p_binome = nullptr;
    etu.p_note = nullptr;
}


int main() {

    int N = 0;
    while(N<=0){
        cout<<"Nombre d'etudiants"<<endl;
        cin>>N;
    }
    
    int nbBi; //nombre de binomes possibles

    if(N%2 == 0){
        nbBi = N/2;
    }else{
        nbBi = (N/2) + 1;
    }
 
    t_etudiant* tab_etu; 
    tab_etu = new t_etudiant[nbBi*2]; //N=3, Si t_etudiant[N] => tableau de 3 etudiants, l'etudiant fantome doit etre alors inclus si N est impaire: [(anna, aya) ;; (chris, etuFantome)]
    if(N%2 != 0){
        tab_etu[(nbBi*2)-1] = etuFantome; //eg: quand N=3, je place l'etudiant fantome à la dernière case du talbeau;
    }

    t_tab_binome tTabBinome;
    tTabBinome.tab_binome = new t_binome[nbBi];
    tTabBinome.capa = nbBi;
    tTabBinome.occup = 0;

    //remplir un tableau d'etudiant, si etuFantome existe, pas de probleme, for() s'arrete avant d'atteindre N, N= (nbBi*2)-1
    for(int i=0; i<N; i++){
        cout<<"Nom etudiant"<<endl;
        cin>>tab_etu[i].nom;
    }



    /*main according to the worksheet
    ALGO demandant au user deux etu, formant un binome des deux etu, leur affectant une note saisie, affichant leurs noms, leur note, puis les dissociant
    */
    t_etudiant etu1, etu2;
    string s1, s2;
    cout<<"Nom du 1er etudiant"<<endl;
    cin>>s1;
    cout<<"Nom du 2e etudiant "<<endl;
    cin>>s2;

    initEtu(s1, etu1);
    initEtu(s2, etu2);

    //FORMATION BINOME
    creerBinome(etu1, etu2, tTabBinome);

    //AFFECTATION NOTE
    double mark;
    cout<<"Note du binome: "<<endl;
    cin>>mark;
    notePourBinome(etu1, mark);

    //AFFICHAGE BINOME
    infoBinome(etu1);

    //DISSOCIER BINOME
    dissocier(etu1);



    delete[] tab_etu;
    tab_etu = nullptr;
    delete[] tTabBinome.tab_binome;
    tTabBinome.tab_binome = nullptr;
}