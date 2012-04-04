/*
 * main.cpp
 *
 *  Created on: Apr 4, 2012
 *      Author: guilherme
 */

#include "Table.h"
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

bool _t_find(std::priority_queue<Table*, std::vector<Table*>, CompareTable> q, const Table *el) {
	Table *p;
	while(!q.empty()) {
		p = q.top();
		if(p == el) {
			return true;
		}
		q.pop();
	};
	return false;
};

int main(int argc, char *argv[]) {
  int pecas_inicial[3][3] = { { 2,8,3 },{ 1,6,4 }, { 7,0,5 } };
  int pecas_final[3][3] = { { 1,2,3 }, { 8,0,4 }, { 7,6,5 } };
  Table *_tab_inicial = new Table(pecas_inicial);
  Table *_tab_final   = new Table(pecas_final);
  _tab_inicial->_g(_tab_final);
  _tab_inicial->_h(_tab_final);

  std::priority_queue<Table*, std::vector<Table*>, CompareTable> open_list;
  std::priority_queue<Table*, std::vector<Table*>, CompareTable> closed_list;
  std::vector<Table *> _return;
  std::priority_queue<Table*, std::vector<Table*>, CompareTable>* neighbors;

  open_list.push(_tab_inicial);

  Table *_current_tab;
  Table *neighbor;

  while(open_list.size() > 0) {
    _current_tab = open_list.top();

    if(*_current_tab == _tab_final) {
      while(_current_tab->getParent()) {
        _return.push_back(_current_tab);
        _current_tab = _current_tab->getParent();
      };

      break;
    };
    open_list.pop();

    closed_list.push(_current_tab);

    neighbors = _current_tab->neighbors();

    while(neighbors->size() > 0) {
      neighbor = neighbors->top();


      if(_t_find(closed_list, neighbor)) {
        continue;
      };

      int g_score = _current_tab->getG() + 1;
      int score_is_best = 0;


      if(!_t_find(open_list,neighbor)) {
        score_is_best = 1;
        neighbor->_h(_tab_final);
        open_list.push(neighbor);
      } else if(g_score < neighbor->getG()) {
        score_is_best = 1;
      };

      if(score_is_best) {
        neighbor->setParent(_current_tab);
        neighbor->setG(g_score);
        neighbor->setF(neighbor->getG() + neighbor->getH());
      };

      neighbors->pop();
    };
  };



  if(!_return.empty()) {
	  _tab_inicial->print();
	  while(!_return.empty()) {
		_current_tab = _return.back();
		_current_tab->print();
		_return.pop_back();
	  };
  } else {
	cout<<"N‹o achou nenhuma solucao"<< endl;
  };
  delete _tab_inicial;
  delete _tab_final;
  return 0;
};




