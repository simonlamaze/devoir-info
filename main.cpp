#include <iostream>
#include "pieces.h"
#include <sstream>
#include <string>
#include <array>
#include <stdio.h>

#include "pieces.h"
using namespace std;
coup nomoves = coup( square (0,0) , square (0,0));
square nullsq = square(0,0); // la case des pièces prises
piece nullpc = piece("King",1,nullsq,nomoves);
coup grandroque = coup( square (10,10) , square (100,100));
coup petitroque = coup( square (100,100) , square (10,10));
// Des constructeurs par défaut, en attendant d'en avoir

void print_piece(piece* p) {
    cout<<p->name<<","<<p-> color << " ,"<< p->currsq.col<< p->currsq.row<<endl;
}

bool samemove(coup m , coup b) {
    if (m.begsq.equal(m.begsq)) {
        if (m.endsq.equal(b.endsq)) {
            return true;
        }
    }
    return false;
}



int column(char c) {
    if (c =='a') {
        return 1;
    }
    if (c =='b') {
        return 2;
    }
    if (c =='c') {
        return 3;
    }
    if (c =='d') {
        return 4;
    }
    if (c =='e') {
        return 5;
    }
    if (c =='f') {
        return 6;
    }
    if (c =='g') {
        return 7;
    }if (c =='h') {
        return 8;
    }
    else {
        return 9;
    }
}

void show_board(int board[8][8]) {
    for (int i = 0; i < 8; i++) {
        cout<<"row "<<i<<": ";
        for (int j = 0; j < 8; j++) {
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
}

piece* getpiece(square sq, array<piece* ,16 > WhitePieces , array<piece* ,16 > BlackPieces) {
    piece* pc = &nullpc;
    for (piece* pièce : WhitePieces) {
        if (pièce->currsq.equal(sq)) {
            pc= pièce ;
            return pc;
        }
    }
    for (piece* pièce : BlackPieces) {
        if (pièce->currsq.equal(sq)) {
            pc= pièce ;
            return pc;
        }
    }


    return pc ;
}
void print_b(int board[8][8], array<piece*, 16> WhitePieces , array<piece*, 16> BlackPieces) {
    cout <<"   _________________________________________"<< endl;
    for (int i= 0 ; i<8 ; i++) {
        cout << " "<< 7-i+1 <<" |" ;
        for (int j= 0 ; j<8 ; j++) {
            if (board[j][7-i ]== 1) {
                piece* pièce =getpiece(square(j+1, 7-i+1), WhitePieces,BlackPieces);

                cout <<" "<< pièce->name[0]<<"B |";


            }
            else if (board[j][7-i]== 2) {
                piece* pièce =getpiece(square(j+1, 7-i+1), WhitePieces,BlackPieces);

                cout <<" "<< pièce->name[0]<<"N |";

            }
            else {
                cout <<"    |";
            }
        }
        cout << endl;
        cout <<"   |____|____|____|____|____|____|____|____|"<< endl;
    }
    cout << "     a    b    c    d    e    f    g    h "<< endl ;
}
bool cango(piece* pièce , square s , int board[8][8], array<piece*,16> WhitePieces,array<piece*,16> BlackPieces ) {
    if (pièce->name == "Cavalier") {
        square currsqb = square(pièce->currsq.col -1 , pièce->currsq.row -1);
        square arrow = currsqb.difference(s);
        if (square(s.col +1, s.row +1).state(board)== pièce->color ){
            return false ;
            cout<<"hop"<<endl;
        } // On vérifie que l'on n'atterrit pas sur une case de la même couleur

        else if (abs(arrow.col)==2){

            if (abs(arrow.row)==1)  {

                return true ;
            }
        }
        else if (abs(arrow.col)==1){
            if (abs(arrow.row)==2){

                return true ;
            }
        }
    }
    if (pièce->name == "Fou"){
        square currsqb = square(pièce->currsq.col -1 , pièce->currsq.row -1);

        square arrow = currsqb.difference(s);
        square dir=arrow.direction();
        if (square(s.col +1, s.row +1).state(board)== pièce->color ) {
            return false ;      // on ne peut pas aller sur la case si elle est de la même couleur que la pièce
        }

        if (abs(arrow.col)!= abs(arrow.row) ) {
            return false ;
        }
        // On a testé que le mouvement était diagonal
        int length = abs(arrow.col);
        // longueur du mouvement, on peut prendre col ou row indifférement
        for (int i =1 ; i<length ; i++) {
            square sqb = square(currsqb.col + dir.col*i +1 , currsqb.row + dir.row*i +1);
            if (sqb.state(board)!= 0 ) { // Il faut que la case soit vide pour passer dessus
                return false ;
            }
        }


        return true ;
    }
    if (pièce->name=="Pawn") {

        square currsqb = square(pièce->currsq.col -1 , pièce->currsq.row -1);

        square arrow = currsqb.difference(s);

        int sens = 3 - 2*pièce->color ;  // sens d'avancée des pions, 1 si c'est les blancs, -1 si c'est les noirs
        int rangdép =  -3 + 5* pièce->color ; // rang de départ des pions
        int pash = abs(arrow.row) , pasl= abs(arrow.col);
        //On va distinguer suivant la valeur de pash

        if (pash>2 or pash ==0) {
            return false;
        }
        // on vérifie qu'on va bien dans le bon sens :
        if (arrow.row*sens<0) { // cela signifie que le pion irait dans le mauvais sens
            return false ;
        }
        if (pash ==2) { // on vérifie que l'avancée de deux est légale
            if (pièce->currsq.row!=rangdép) { // ie qu'on est sur la rangée de départ ( on pourrait aussi vérifier que le pion n'a pas bougé)
                return false;
            }
            if (pasl !=0) { // on n'avance pas de deux en diagonale
                return false;
            }

            if (square(pièce->currsq.col , pièce->currsq.row  + sens ).state(board)!= 0) {
                return false ;
                // si la case par laquelle on veut passer est occupée, on ne oeut avancer de deux cases
            }
            if (square(s.col +1, s.row +1).state(board)== 3-pièce->color) {
                return false;
            }
        }
        if (pash==1) { // si le pion n'avance que de un, il vaut vérifier les prises
            if (pasl>1) {
                return false;
            }
            if (pasl==1 ) {

                if (square(currsqb.col + arrow.col +1, currsqb.row +1+arrow.row).state(board)== 3-pièce->color) {
                    return true;
                }
                if (square(currsqb.col + arrow.col +1, currsqb.row +1+arrow.row).state(board)== 0) {
                    if (pièce->currsq.row!=5) {
                        return false;
                    }
                    cout<<"hip"<<endl;

                    piece* pn = getpiece(square(pièce->currsq.col + arrow.col , pièce->currsq.row), WhitePieces, BlackPieces);
                    if (pn->name!="Pawn") {
                        return false;
                    }
                    square a= pn->lastmove.begsq.difference(pn->lastmove.endsq);
                    if (a.squarednorm()!=4) {
                        return false;
                    }
                        // La prise en passant est légale si on arrive jusqu'ici
                    return true;


                }
                return false;
            }
            // On ne peut que prendre en diagonale
            if (pasl == 0) {
                if (square(s.col +1, s.row +1).state(board)!= 0) {
                    return false; // on ne peut pas prendre en avançant droit
                }
            }

        }
        if (square(s.col +1, s.row +1).state(board)== pièce->color) {
            return false ;
        }
        return true ;
    }
    if (pièce->name == "Dame") {
        square currsqb = square(pièce->currsq.col -1 , pièce->currsq.row -1);
        square arrow = currsqb.difference(s);

        if (abs(arrow.col) !=abs(arrow.row) ){
            if (abs(arrow.col)>0) {
                if (abs(arrow.row)>0) {
                    return false ;
                }
            }
        } //  on a testé si la direction était soit diagonale soit straigth
        // On détermine la direction dans laquelle on va

        // Pour pouvoir vérifier case par case si on peut passer dessus
        int length = max(abs(arrow.col),abs(arrow.row)) ;

        square dir=arrow.direction();

        // length est le nombre de cases que l'on parcourt
        for (int i =1 ; i<length ; i++) {
            auto sqb = square(currsqb.col + dir.col*i +1 , currsqb.row + dir.row*i+1);
            if (sqb.state(board)!= 0 ) {
                return false ;
            }
        }

        if (square(s.col +1, s.row +1).state(board)== pièce->color ) {
            return false ;
        }
        return true;
    }
    if (pièce->name == "Roi") {
        square currsqb = square(pièce->currsq.col -1 , pièce->currsq.row -1);
        square arrow = s.difference(currsqb);
        if (square(s.col +1, s.row +1).state(board)==pièce->color){
            return false;
        }else if (arrow.squarednorm()> 2) {
            return false ;
        } else {
            return true ;
        }
    }
    if (pièce->name=="Tour") {
        square currsqb = square(pièce->currsq.col -1 , pièce->currsq.row -1);
        square arrow = currsqb.difference(s);

        if (arrow.col*arrow.row != 0  ) {
            return false ;
        }
        square dir = arrow.direction();
        int length  = max(abs(arrow.col ) , abs(arrow.row )); ;
        // le maximum des deux valeurs absolues
        for (int i =1 ; i<length ; i++) {
            auto sqb = square(currsqb.col + dir.col*i +1, currsqb.row + dir.row*i+1);
            if (sqb.state(board)!= 0 ) {
                return false ;
            }
        }
        if (square(s.col +1, s.row +1) .state(board)== pièce->color ) {
            return false ;
        }
        return true;
    }
    else {
        return false ;
    }
}
// une fonction qui calcule un score matériel selon les formules classiques associant un prix à chaque pièce (  P=1 , F,C= 3, T=5 , D=9)
int prix(piece* pièce) {
    if (pièce->name =="Pawn") {
        return 1;
    }
    if (pièce->name =="Fou") {
        return 3;
    }
    if (pièce->name =="Cavalier") {
        return 3;
    }
    if (pièce->name =="Tour") {
        return 5;
    }
    if (pièce->name =="Dame") {
        return 9;
    }
    return 0 ;
}


int scorematériel (int board[8][8], array<piece*, 16> WhitePieces , array<piece*, 16> BlackPieces, int Player) {
    array<piece* , 16> piècesjoueur ;
    array<piece* , 16> piècesautrejoueur ;
    if (  Player == 1) {
        piècesjoueur = WhitePieces;
        piècesautrejoueur = BlackPieces;
    } else if (Player == 2) {
        piècesjoueur = BlackPieces;
        piècesautrejoueur = WhitePieces;
    }
    int SM=0;
    for (int i = 1; i<16 ;i++) {
        if (!piècesjoueur[i]->currsq.equal(nullsq)) {
            SM += prix(piècesjoueur[i]);
        }
        if (!piècesautrejoueur[i]->currsq.equal(nullsq)) {
            SM += -prix(piècesautrejoueur[i]);
        }
    }
    return SM;
}
int score(square cs) {
    if (2<=cs.col<=5 && 2<=cs.row<=5) {
        return 2;
    }
    return 1 ;
}

int scoreactivité (int board[8][8], array<piece*, 16> WhitePieces , array<piece*, 16> BlackPieces, int Player) {
    array<piece* , 16> piècesjoueur ;

    if (  Player == 1) {
        piècesjoueur = WhitePieces;

    } else if (Player == 2) {
        piècesjoueur = BlackPieces;
    }
    int SA = 0 ;
    for (int i = 1; i<8; i++) {
        for (int j=1; j<8; j++) {
            bool controllé = false;
            for (piece* pièce : piècesjoueur) {
                if (cango(pièce,square(i,j),board, WhitePieces, BlackPieces)) {
                    SA+=score(square(i,j));
                }
            }
        }
    }
    return SA;

}
// Maintenant on calcule la fonction de score global


// On a une liste de pièces dont on fera évoluer l'état au fur et à mesure de la partie
// maintenant une question qui teste la légalité d'un coup
bool ischeck( int board[8][8] ,int Player , array<piece* , 16> &WhitePieces,array<piece*, 16> &BlackPieces ) {
    auto boardb = board ;
    piece* roi = &nullpc;
    if (Player ==1) {
        roi = WhitePieces[0];
    }
    if (Player ==2) {
        roi = BlackPieces[0];
    }
    square caseroi = square (roi->currsq.col -1 ,roi->currsq.row -1) ;
    //maintenant il faut tester si les pièces de l'autre joueur attaquent la case du roi
    if (Player ==1) {
        for (int i=1; i<16; i++) {
            piece* piècea = BlackPieces[i];
            if (cango(piècea , caseroi, boardb,WhitePieces,BlackPieces) == true) {
                return true ;
            }
        }
    }
    if (Player ==2) {
        for (int i=1; i<16; i++) {
            piece* piècea = WhitePieces[i];
            if (cango(piècea , caseroi, boardb,WhitePieces,BlackPieces) == true) {
                return true ;
            }

        } // On a vérifié que les pièces adverses ne pouvaient pas aller sur la case du roi du joueur
    }

    return false ;
}
array<bool, 2> roquespossible(int board[8][8], array<piece*, 16> WhitePieces, array<piece*, 16> BlackPieces, int Player) {
    // Le premier bool dit si le joueur peut faire le petit roque, le second si il peut faire le grand roque
    array<bool,2> roquesp = {true,true};
    array<piece* , 16> piècesjoueur ;
    array<piece* , 16> piècesautrejoueur ;
    if (  Player == 1) {
        piècesjoueur = WhitePieces;
        piècesautrejoueur = BlackPieces;
    } else if (Player == 2) {
        piècesjoueur = BlackPieces;
        piècesautrejoueur = WhitePieces;
    }
    int rowroque = -7+Player*7; //La rangée de roque ( 0 pour B , 7 pr N )
    piece* roi = piècesjoueur[0];
    piece* tourh = piècesjoueur[2];
    piece* toura = piècesjoueur[3];

    if (!samemove(roi->lastmove, nomoves)) {
        return {false,false};
    }

    // on teste que le roi n'a jamais bougé
    if (ischeck(board,Player, WhitePieces,BlackPieces)) {
        return {false, false};
    }
    // on teste que le roi n'est pas en échec
    if (!samemove(tourh->lastmove, nomoves)) {
        roquesp[0] =false ;
    }
    if (!samemove(toura->lastmove, nomoves)) {
        roquesp[1] =false ;
    }

    // on vérifie que les tous n'ont pas bougé
    for (int i=8 ; i<16 ; i++) {
        piece* pièce = piècesautrejoueur[i];
        if (cango(pièce,square(2,rowroque), board,WhitePieces,BlackPieces) or cango(pièce,square(3,rowroque), board,WhitePieces,BlackPieces)) {
            roquesp[1]=false;
        }
        if (cango(pièce,square(5,rowroque), board,WhitePieces,BlackPieces) or cango(pièce,square(6,rowroque), board,WhitePieces,BlackPieces)) {
            roquesp[0]=false;
        }
    }



    // on a testé que les cases de passage du roi étaient inaccessibles aux pièces adverses, à noter que je ne prends pas en compte le cas où un pion adverse empêche le roque
    // ce cas n'a a ma connaissance jamais existé en pratique ( il faudrait changer board pour un coup en y mettant roi et vériier (long et inutile))
    if (square(2,rowroque+1).state(board)!=0 or square(3,rowroque+1).state(board)!=0 or square(4,rowroque+1).state(board)!=0) {
        roquesp[1]=false;
        // pas de grand roque si une des cases est occupée
    }
    if (square(6,rowroque+1).state(board)!=0 or square(7,rowroque+1).state(board)!=0 ) {
        roquesp[0]=false;
        // pas de petit roque si une des cases est occupée
    }

    return roquesp;
    // J'ai presque pris toutes les possibilités en compte , cette fonction peut être améliorée mais ce serait moche et long
}

bool legalMove ( int board[8][8],array<piece* , 16> &WhitePieces,array<piece*, 16> &BlackPieces , coup* Newmove , int Player) {

    array<bool,2> roquespossibles = roquespossible(board,WhitePieces,BlackPieces,Player);

    if (samemove(*Newmove,grandroque)) {
        if (roquespossibles[1]) {
            return true ;
        }
        return false;
    }
    if (samemove(*Newmove,petitroque)) {
        if (roquespossibles[0]) {
            return true ;
        }
        return false;
    }
    // On a testé si les roques marchent, reste à implémenter le changement de position du roi et de la tour .
    square begsq = Newmove->begsq;
    square endsq = Newmove->endsq;
    if (begsq.inside() == false or endsq.inside() == false) {
        return false;
        // on vérifie qu'on reste dans l'échiquier
    }

    if (board[begsq.col][begsq.row] != Player) {
        return false;
        // il faut que le joueur bouge une de ses pîèces
    }
    if (begsq.equal(endsq )) {
        return false ; // on ne peut pas passer son tour
    }
    int indicepiece = 16 ;
    for (int i = 0 ;i<16 ;i++) {
        piece* pièce ;
        if (  Player == 1) {pièce = WhitePieces[i];
        } else if (Player == 2) {pièce = BlackPieces[i];
        }
        if (pièce->currsq.equal( square(begsq.col+1,begsq.row+1))==true) {
            indicepiece =  i;
        }
    }
    array<piece* , 16> piècesjoueurs ;
    if (  Player == 1) {
        piècesjoueurs = WhitePieces;
    } else if (Player == 2) {
        piècesjoueurs = BlackPieces;
    }
    auto piècejouée = piècesjoueurs[indicepiece];
    // on a récupéré la pièce jouée

    bool peutaller = cango(piècejouée,endsq, board,WhitePieces, BlackPieces);
    if (!peutaller) {
        return false;
    }
   //on a vérifié que la pièce peut aller sur la case en qustion

    // Maintenant il faut vérifier qu'une fois qu'on a joué le coup on n'est pas échec, c'est plus compliqué
    int casemem = board[endsq.col][endsq.row];
    board[begsq.col][begsq.row] = 0;
    board[endsq.col][endsq.row] = Player;
    int piece_jouee= 0 ; // indice de la pièce jouée
    int piece_prise = 16;// indice de la pièce prise

    square tempsqpl =nullsq ; //la case temporaire de la pièce qui sera détectée comme jouée
    square  tempsqpl2 = nullsq ; // la case temporaire de la pièce qui sera détectée comme prise
    if (Player ==1) {

        for (int i = 0 ; i < 16; i++) {
            piece* pièce = WhitePieces[i];
            if (pièce->currsq.equal(square(Newmove->begsq.col+1,Newmove->begsq.row+1))) {
                tempsqpl = pièce->currsq;
                piece_jouee = i ;

            }

        }
        tempsqpl = WhitePieces[piece_jouee]->currsq;
        WhitePieces[piece_jouee]->currsq = square(Newmove->endsq.col+1,Newmove->endsq.row+1);
        for (int i = 0 ; i < 16; i++) { // on recherche parmi les pièces adverses si une est prise
            piece* pièce = BlackPieces[i];
            if (pièce->currsq.equal(square(Newmove->endsq.col+1,Newmove->endsq.row+1))) {
                piece_prise = i ;
            }
        }

        if (piece_prise<16) {
            tempsqpl2= BlackPieces[piece_prise]->currsq;
            BlackPieces[piece_prise]->currsq = nullsq;

        }
    }

    if (Player ==2) {
        for (int i = 0 ; i < 16; i++) {

            piece* pièce = BlackPieces[i];
            if (pièce->currsq.equal(square(Newmove->begsq.col+1,Newmove->begsq.row+1))) {
                tempsqpl = pièce->currsq;
                piece_jouee = i ;
            }

        }
        tempsqpl = BlackPieces[piece_jouee]->currsq;
        BlackPieces[piece_jouee]->currsq = square(Newmove->endsq.col+1,Newmove->endsq.row+1);
        for (int i = 0 ; i < 16; i++) { // on recherche parmi les pièces adverses si une est prise
            piece* pièce = WhitePieces[i];
            if (pièce->currsq.equal(square(Newmove->endsq.col+1,Newmove->endsq.row+1))) {
                piece_prise = i ;
            }
        }
        if (piece_prise<16) {
            tempsqpl2= WhitePieces[piece_prise]->currsq;
            WhitePieces[piece_prise]->currsq = nullsq;

        }

    }
        // il faut update l'échiquier pour vérifier qu'il n'y a pas échec après le coup , et surtout changer l'état des pièces
    bool check = ischeck(board ,Player,WhitePieces,BlackPieces);

    //maintenant on rechange les listes de pièces
    //print_piece(piece_jouee);
    //tempsqpl.print();
    if (Player == 1) {
        WhitePieces[piece_jouee]->currsq = tempsqpl;
        if (piece_prise<16) {
            BlackPieces[piece_prise]->currsq = tempsqpl2;
        }
    }
    if (Player == 2) {
        BlackPieces[piece_jouee]->currsq = tempsqpl;
        if (piece_prise<16) {
            WhitePieces[piece_prise]->currsq = tempsqpl2;
        }
    }
    board[begsq.col][begsq.row] = Player;
    board[endsq.col][endsq.row] = casemem;
    // Il faut rechanger le tout
    if (check == true) {
        return false;
    }
    piècejouée->lastmove = *Newmove;
     // on change le plateau si le coup est légal

    return true;
}

// Une fonction qui teste si un joueur est en échec dans une position donnée

// une fonction de score global



// teste si le joueur dont c'est le tour est en échec

coup parsemove(string s) {
    if (s=="0-0") {
        return petitroque;
    }
    else if (s=="0-0-0") {
        return grandroque;
    }
    int sa  = column(s[0]);

    char* sb = &s[1];
    int sc  = column(s[3]);
    char* sd = &s[4];

return coup (square(sa-1,stoi(sb)-1), square(sc-1,stoi(sd)-1)); // on renvoie avec les cases décalées de 1 pur correspondre aux bons indice du plateau
}
// Pou lire un coup de la console


void print_pieces(const array<piece* , 16> &vec) {
    for (piece* piece : vec) {
        cout << piece->name << " "<< piece->currsq.col << piece->currsq.row << endl;
    }
}

vector<coup*> legalmoves (int board[8][8] ,array<piece* , 16> WhitePieces , array<piece* , 16> BlackPieces, int Player){
    vector<coup*> coupslgo ;
    if (Player == 1) {
        for (piece* pièce:WhitePieces) {
            square sqb = square(pièce->currsq.col -1,pièce->currsq.row -1) ;
            for (int i = 0 ; i<8 ; i++) {
                for ( int  j = 0 ; j<8 ; j++) {
                        if (!sqb.equal(square(i,j))) {
                            coup* movet = new coup(sqb,square(i,j));
                            if (legalMove(board , WhitePieces , BlackPieces, movet ,Player)) {
                                coupslgo.push_back(movet);
                            }
                        }
                    // On a testé, pour chaque pièce du joueur dont c'est le trait, toutes les cases de l'échiquier, loin certes d'être optimal ,
                    // mais suffisant.
                }


            }
        }
    }else {
        for (piece* pièce:BlackPieces) {
            square sqb = square(pièce->currsq.col -1,pièce->currsq.row -1) ;
            for (int i = 0 ; i<8 ; i++) {
                for ( int  j = 0 ; j<8 ; j++) {
                    if (!sqb.equal(square(i,j))) {

                        coup* movet = new coup(sqb,square(i,j));
                        if (square(i,j).equal(square(3,6))) {
                            bool bis = legalMove(board , WhitePieces , BlackPieces, movet ,Player);
                        }
                        if (legalMove(board , WhitePieces , BlackPieces, movet ,Player)) {
                            coupslgo.push_back(movet);

                        }
                    }
                    // On a testé, pour chaque pièce du joueur dont c'est le trait, toutes les cases de l'échiquier, loin certes d'être optimal ,
                    // mais suffisant.
                }

            }
        }
    }
    array<bool,2> roquespossibles = roquespossible(board,WhitePieces,BlackPieces,Player);
    if (roquespossibles[1] == true) {
        coupslgo.push_back(&grandroque);
    }
    if (roquespossibles[0] == true) {
        coupslgo.push_back(&petitroque);
    }
    return coupslgo;
}

bool ischeckmate(int board[8][8] ,int Player,array<piece* , 16> WhitePieces,array<piece*, 16> BlackPieces){
    //je ferai cette fonction une fois que j'arrive à vérifier la légalité des coups correctement
    if (!ischeck(board, Player, WhitePieces, BlackPieces)) {
        return false;
    }

    vector<coup*>  coupslégaux={}; // il faudra définir une liste de coups légaux un jour où l'autre .
    coupslégaux = legalmoves(board , WhitePieces , BlackPieces , Player);
    if (coupslégaux.empty()) {
        return true;
    }
    return false ;
}

bool isstalemate(int board[8][8] ,int Player,array<piece* , 16> WhitePieces,array<piece*, 16> BlackPieces){
    //je ferai cette fonction une fois que j'arrive à vérifier la légalité des coups correctement
    if (ischeck(board, Player, WhitePieces, BlackPieces)) {
        return false;
    }

    vector<coup*>  coupslégaux={}; // il faudra définir une liste de coups légaux un jour où l'autre .
    coupslégaux = legalmoves(board , WhitePieces , BlackPieces , Player);
    if (coupslégaux.empty()) {
        return true;
    }
    return false ;
}

int scoreg (int board[8][8] ,int Player , array<piece* , 16> WhitePieces,array<piece*, 16> BlackPieces) { // calcule le score du point de vue de Player
    int SM =scorematériel(board  , WhitePieces,  BlackPieces, Player);
    int SA = scoreactivité(board , WhitePieces , BlackPieces, Player);
    int S = SA + SM * 5 ;
    if (ischeckmate(board, 3-Player, WhitePieces, BlackPieces)) {
        S+=1000 ;

    }
    if (isstalemate(board, 3-Player, WhitePieces, BlackPieces)) {
       return 0;

    }
    return S ;

}

int main()  {

    piece WK = piece("Roi", 1, square(5, 1), nomoves) , WQ =piece("Dame" , 1 , square  (4 ,1) , nomoves) , WRa = piece("Tour" , 1 , square  (1 ,1) , nomoves), WRh =piece("Tour" , 1 , square  (8 ,1) , nomoves);
    piece WNb = piece ("Cavalier" , 1 , square  (2 ,1) , nomoves) , WNg =piece("Cavalier" , 1 , square  (7 ,1) , nomoves) , WBc = piece("Fou" , 1 , square  (3 ,1) , nomoves), WBf =piece("Fou" , 1 , square  (6 ,1) , nomoves);
    piece WPa = piece("Pawn" , 1 , square  (1 ,2) , nomoves) , WPb = piece("Pawn" , 1 , square  (2 ,2) , nomoves) , WPc = piece("Pawn" , 1 , square  (3 ,2) , nomoves), WPd =piece("Pawn" , 1 , square  (4 ,2) , nomoves);
    piece WPe = piece("Pawn" , 1 , square  (5 ,2) , nomoves) , WPf =piece("Pawn" , 1 , square  (6 ,2) , nomoves) , WPg = piece ("Pawn" , 1 , square  (7 ,2) , nomoves), WPh =piece("Pawn" , 1 , square  (8 ,2) , nomoves);
    array<piece* , 16> WhitePieces= { &WK , &WQ ,&WRa , &WRh , &WNb , &WNg , &WBc, &WBf, &WPa, &WPb, &WPc, &WPd, &WPe, &WPf, &WPg, &WPh  };

// maintenant on déclare les pièces noires

    piece BK = piece("Roi" , 2, square  (5 ,8) , nomoves) , BQ =piece("Dame" , 2 , square  (4 ,8) , nomoves) , BRa =piece("Tour" , 2 , square  (1 ,8) , nomoves), BRh =piece("Tour" , 2 , square  (8 ,8) , nomoves);
    piece BNb = piece("Cavalier" , 2 , square  (2 ,8) , nomoves) , BNg =piece("Cavalier" , 2 , square  (7 ,8) , nomoves) , BBc =piece("Fou" , 2 , square  (3 ,8) , nomoves), BBf =piece("Fou" , 2 , square  (6 ,8) , nomoves);
    piece BPa = piece("Pawn" , 2 , square  (1 ,7) , nomoves) , BPb =piece("Pawn" , 2 , square  (2 ,7) , nomoves) , BPc =piece("Pawn" , 2 , square  (3 ,7) , nomoves), BPd =piece("Pawn" , 2 , square  (4 ,7) , nomoves);
    piece BPe = piece("Pawn" , 2 , square  (5 ,7) , nomoves) , BPf =piece("Pawn" , 2 , square  (6 ,7) , nomoves) , BPg =piece("Pawn" , 2 , square  (7 ,7) , nomoves), BPh =piece("Pawn" , 2 , square  (8 ,7) , nomoves);
    array<piece*, 16> BlackPieces= { &BK , &BQ ,&BRa , &BRh , &BNb , &BNg , &BBc, &BBf, &BPa, &BPb, &BPc, &BPd, &BPe, &BPf, &BPg, &BPh   };

    vector<coup> Coups= {}; // Liste des coups de la partie
    int Player =1 ; // Joueur dont c'est le tour , ici les blancs
    int board[8][8];
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = 0;
        }
    }
    // On a initialisé l'échiquier
    for (piece* pièce : WhitePieces) {
       board[pièce->currsq.col-1][pièce->currsq.row-1] = 1;
    }
    for (piece* pièce : BlackPieces) {
        board[pièce->currsq.col-1][pièce->currsq.row-1] = 2;
    }
    bool GameEnd  = false;

    print_b(board , WhitePieces, BlackPieces);


    // On a initialisé l'état des cases , maintenant il va falloir ariver à afficher cela avec SDL , youpi
    while (!GameEnd) {


        coup Newmove = nomoves ;
        bool isvalidmove = false;

        bool enpassant = false ;
        square enpassantpris = nullsq;
        // voici deux variables qui seront changées par  legalMove

        while (!isvalidmove) {
            cout<<"Jouez un coup : "<<endl;
            // Récupère un coup dans la console , le joue, et fait jouer soit un autre joueur soit l'IA
            string s ;
            cin >> s ;
            Newmove = parsemove(s);
            // On a récupéré la case de départ

            isvalidmove = legalMove(board, WhitePieces, BlackPieces ,&Newmove  , Player  ) ;

            if (!isvalidmove) {
                cout << "coup illégal"<<endl;
            }
        }
        // On a un coup légal désormais
        // On change l'état de l'échiquier
        int rangprom = 14 - 7* Player ;
        array<piece* , 16> piècesjoueur ;
        array<piece* , 16> piècesautrejoueur ;
        int rowroque = -7+Player*7;
        if (  Player == 1) {
            piècesjoueur = WhitePieces;
            piècesautrejoueur = BlackPieces;
        } else if (Player == 2) {
            piècesjoueur = BlackPieces;
            piècesautrejoueur = WhitePieces;
        }
        if (samemove(Newmove,grandroque)) {
            show_board(board);
            piècesjoueur[0]->currsq = square(3,rowroque +1);
            piècesjoueur[2]->currsq = square(4,rowroque +1 );
            // on change les cases des pièces, puis board
            board[0][rowroque] = 0 ;
            board[2][rowroque] = Player ;
            board[3][rowroque] = Player;
            board[4][rowroque] = 0 ;
        }


        else if (samemove(Newmove,petitroque)) {
            piècesjoueur[0]->currsq = square(7,rowroque +1);
            piècesjoueur[3]->currsq = square(6,rowroque +1 );
            // on change les cases des pièces, puis board
            board[7][rowroque] = 0 ;
            board[6][rowroque] = Player ;
            board[5][rowroque] = Player ;
            board[4][rowroque] = 0 ;
            show_board(board);
        }

        // on a vérifié que le coup n'était pas un roque, si ça l'était on a fait les changements inhérents .
        else { // Si pas de roque




            // Vérifions que l'on n'a pas fait une prise en passant:


            piece* piecejouee = getpiece(square(Newmove.begsq.col+1,Newmove.begsq.row+1),WhitePieces , BlackPieces);
            piece* pieceprise= getpiece(square(Newmove.endsq.col+1,Newmove.endsq.row+1),WhitePieces , BlackPieces);

            square arrow = Newmove.begsq.difference(Newmove.endsq);

            square sqtemp = square(piecejouee->currsq.col+arrow.col,piecejouee->currsq.row); // sert uniquement si on repère une prise en passant

            piecejouee->currsq = square(Newmove.endsq.col+1,Newmove.endsq.row+1);
            pieceprise->currsq = nullsq; // même si aucune pièce n'est prise cela marche
            if (piecejouee->name=="Pawn" )  {
                if (Newmove.endsq.row==rangprom) {
                    cout<< "En quelle pièce vous promouvez vous ? "<<endl;
                    cin >> piecejouee->name;
                }
                if (abs(arrow.col)==1 && abs(arrow.row)==1) {

                    if (board[Newmove.endsq.col][Newmove.endsq.row] == 0) {
                        sqtemp.print();
                        piece* piecepriseep = getpiece(sqtemp,WhitePieces,BlackPieces);
                        print_pieces(BlackPieces);
                        piecepriseep->currsq = nullsq;
                        board[sqtemp.col-1][sqtemp.row-1] = 0 ;

                    }
                }
            }

            board[Newmove.begsq.col][Newmove.begsq.row] = 0;
            board[Newmove.endsq.col][Newmove.endsq.row] = Player; // à noter que la prise en passant reste pssible plus d'un coup après ( à ne pas faire donc)(c'est réglable en gardant en mémoire le coup précédetn, mais je préfère essayer de programmer une petite IA
        }


        // on change de trait, nouveau coup !



        Player = 3 - Player ;

        if (ischeck(board, Player , WhitePieces, BlackPieces)) {
            cout<<"Echec ! "<<endl;
        }


        print_b( board , WhitePieces,  BlackPieces);

        if (ischeckmate(  board , Player ,WhitePieces ,BlackPieces)) {
            cout<<"Echec et Mat! "<<endl;
            GameEnd =true ;

        }
        if (isstalemate(  board , Player ,WhitePieces ,BlackPieces)) {
            cout<<"Pat! Match nul!"<<endl;
            GameEnd =true ;

        }


    }
    cout<< "Fin de la partie"<< endl ;
}
