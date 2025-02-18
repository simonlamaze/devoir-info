//
// Created by lasma on 02/01/2025.
//
#include <iostream>
#include <array>
#include <vector>
#include "board.h"
using namespace std;
#ifndef PIECES_H
#define PIECES_H

class square {
public:
    int col ;
    int row ;

    square(int col, int row ): col{col}, row{row} {}
    void print() {
        cout << "square col: " << col << " row: " << row << endl;
    }
    bool inside() {
        if (col >= 0 && row >= 0 && col < 8 && row < 9) {
            return true;
        } else {
            return false;
        }
    }
    bool equal (square s) {
        if (col == s.col && row == s.row) {
            return true;
        } else {
            return false;
        }
    }
     square  difference (  square s) { // vecteur de la case vers la case s
        int a = s.col - col ,  b =s.row -row;
        return square(  a , b) ;
    }
    int squarednorm() {
        return col * col + row*row;
    }
    int state(int board[8][8]) { // A appliquer à des cases de l'échiquier
       return board[col-1][row-1];
    }
    square direction() const { // à utiliser quand la case représente un vecteur entre deux cases
        int a =0 , b= 0 ;
        if (col !=0 ) {
            a = col/std::abs(col) ;
        }
        if (row !=0) {
            b = row/std::abs(row) ;
        }
        return {a , b};
    }

};

class coup {
    public:
    square begsq ;
    square endsq ;

    coup( square begsq , square endsq ): begsq{begsq}, endsq{endsq} {}
    void print() {
        begsq.print();
        endsq.print();
    }
};


class piece {


public:
    std::string name ;
    int color; // 1 pour blanc, 2 pour noir
    square currsq ;
    coup lastmove;
    piece( std::string  name, int color, square currsq, coup coup): name(name), color(color), currsq(currsq), lastmove(coup) {}

    piece operator~();

};


#endif //PIECES_H
