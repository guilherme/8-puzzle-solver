/*
 * Table.cpp
 *
 *  Created on: Apr 4, 2012
 *      Author: guilherme
 */

#include "Table.h"
#include <iostream>
#include <iomanip>

#ifndef LINHAS
#define LINHAS 3
#endif
#ifndef COLUNAS
#define COLUNAS 3
#endif


bool Table::operator==(const Table *t) const {
	int l, c;
	for(l = 0; l < LINHAS; l++) {
			for(c = 0; c < COLUNAS; c++) {
				 if(getPeca(l,c) != t->getPeca(l,c))
					 return false;
			};
		};
	return true;
};
void Table::_g(Table* _tab_final) {
    int i = 0;
    int j = 0;
    this->g = 0;
    for(i = 0; i < COLUNAS; i++) {
      for(j = 0; j < LINHAS; j++) {
        if(this->pecas[i][j] == _tab_final->getPeca(i,j)) {
          this->g++;
        };
      };
    };
};
void Table::_h(Table* _tab_final) {
    int i,j,l,c;
    this->h = 0;
    for(i = 0; i < LINHAS; i++) {
      for(j = 0; j < COLUNAS; j++) {
        if(this->pecas[i][j] != _tab_final->getPeca(i,j)) {
          for(l = 0; l < LINHAS; l++) {
            for(c = 0; c < COLUNAS; c++) {
              if(this->pecas[i][j] == _tab_final->getPeca(l,c)) {
                break;
              };
            };
          };
          this->h += _delta_l_c(i,j,l,c);
        };
      };
    };
};
std::priority_queue<Table*, std::vector<Table*>, CompareTable>* Table::neighbors() {
	std::priority_queue<Table*, std::vector<Table*>, CompareTable>* neighbors = new std::priority_queue<Table*, std::vector<Table*>, CompareTable>();

	// PROCURA O VAZIO NO TABULEIRO
	int l;
	int c;
	int empty_l = -1;
	int empty_c = -1;
	int aux;
	for(l = 0; l < LINHAS; l++) {
		for(c = 0; c < COLUNAS; c++) {
		  if(this->getPeca(l,c) == 0) {
			empty_l = l;
			empty_c = c;
			break;
		  };
		};
	};

	if(empty_l == -1 || empty_c == -1) {
		return neighbors;
	};


	if(empty_l+1 < LINHAS) {
		Table* t = new Table(this);
		aux = t->getPeca(empty_l+1,empty_c);
	    t->setPeca(empty_l,empty_c, aux);
	    t->setPeca(empty_l+1,empty_c,0);
	    neighbors->push(t);
	};
	// checa se pode mover para baixo
	if(empty_l-1 >= 0) {
		Table* t = new Table(this);
	    aux = t->getPeca(empty_l-1,empty_c);
	    t->setPeca(empty_l,empty_c,aux);
	    t->setPeca(empty_l-1,empty_c,0);
	    neighbors->push(t);
	  };
	  // checa se pode mover para esquerda
	if(empty_c-1 >= 0) {
		Table* t = new Table(this);
	    aux = t->getPeca(empty_l,empty_c-1);
	    t->setPeca(empty_l,empty_c, aux);
	    t->setPeca(empty_l,empty_c-1,0);
	    neighbors->push(t);
	  };
	  // checa se pode mover para direita
	if(empty_c+1 < COLUNAS) {
		Table* t = new Table(this);
	    aux = t->getPeca(empty_l,empty_c+1);
	    t->setPeca(empty_l,empty_c, aux);
	    t->setPeca(empty_l,empty_c+1, 0);
	    neighbors->push(t);
	  };

	return neighbors;
};

int Table::_delta_l_c(int l_ini, int c_ini, int l_fim, int c_fim) {
  int delta_l;
  int delta_c;

  delta_l =  abs(l_fim-l_ini);
  delta_c =  abs(c_fim-c_fim);

  return delta_l + delta_c;
};

void Table::print() {
	int l,c;
	std::cout << std::setw(15) << "g(x)" << " h(x) " << "f(x)" << std::endl;
	for(l = 0; l < LINHAS; l++) {
			for(c = 0; c < COLUNAS; c++) {
				 std::cout << getPeca(l,c) << std::setw(3);
			};
			std::cout << std::setw(7) << getG() << std::setw(5) << getH() << std::setw(5) << _f();
			std::cout << std::endl;
		};
};
Table::Table(int p[3][3]) {
	pecas.resize(3, std::vector<int>(3,0));
	int l,c;
	for(l = 0; l < LINHAS; l++) {
		for(c = 0; c < COLUNAS; c++) {
			this->pecas[l][c] = p[l][c];
		};
	};
};



Table::Table(Table* t) {
	pecas.resize(3, std::vector<int>(3,0));
	int l,c;
	for(l = 0; l < LINHAS; l++) {
		for(c = 0; c < COLUNAS; c++) {
			  setPeca(l,c, t->getPeca(l,c));
		};
	};
	this->h = t->getH();
	this->g = t->getG();
	this->f = this->g + this->h;
};

Table* Table::getParent() {
	return this->parent;
};


Table::Table() {
	pecas.resize(3, std::vector<int>(3,0));
	// TODO Auto-generated constructor stub

}

Table::~Table() {
	// TODO Auto-generated destructor stub
}

