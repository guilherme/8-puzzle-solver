/*
 * Table.h
 *
 *  Created on: Apr 4, 2012
 *      Author: guilherme
 */

#include <vector>
#include <queue>

#ifndef TABLE_H_
#define TABLE_H_

class CompareTable;

class Table {
private:
    int h;
    int g;
    int f;
    std::vector< std::vector<int> > pecas;
    int _delta_l_c(int l_ini, int c_ini, int l_fim, int c_fim);
    Table* parent;

public:
    Table* getParent();
    inline void setParent(Table* parent) { this->parent = parent; };

    bool operator==(const Table* t2) const;
    inline int getPeca(int l, int c) const { return pecas[l][c]; };
    inline void setPeca(int l, int c, int value) { pecas[l][c] = value; };
    inline int _f() { return this->f; };
    inline void setF(int f) { this->f = f; };
    std::priority_queue<Table *, std::vector<Table*>, CompareTable>* neighbors();
    void _g(Table* _tab_final);
    void _h(Table* _tab_final);
    inline int getG() { return this->g; };
    inline int getH() { return this->h; };
    inline void setG(int g) { this->g = g; };
    inline void setH(int h) { this->h = h; };
    void print();
    Table(Table* t);
    Table(int p[3][3]);
	Table();
	virtual ~Table();
};

class CompareTable {

  public:

    bool operator()(Table*& t1, Table*& t2) // return true if t1 is bigger than t2
    {
       if (t1->_f() > t2->_f()) return true;
       return false;
    }

    bool operator()(Table& t1, Table& t2) // return true if t1 is bigger than t2
    {
       if (t1._f() > t2._f()) return true;
       return false;
    };

};

#endif /* TABLE_H_ */
