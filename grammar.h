#pragma once
#ifndef _GRAMMAR_H_
#define _GRAMMAR_H_



#include<map>
#include<set>
#include<vector>
#include<iostream>
#include<list>
#include<string>
#include<queue>
#include<stack>
#include"grammar.h"
using namespace std;

struct ret_to_qt
{
    stack<char>old;
    queue<char>code;
    string relation;
    string action;
    stack<char>nnew;
};

class grammar
{
private:
	map<char, set< vector<char> > >grammarMap;
	set<char>vt;
    set<char>vn;
	map<char, set<char> >firstvt;
	map<char, set<char> >lastvt;
	map<char, set<char> >findMap;
	/*
	*-1表示<
	* 0表示=
	* 1表示>
	*/
	map<pair<char, char>, set<short> >relation;

	queue<char>code;
	stack<char>parser;
	int len;

public:

    char errChar;
    string errSub;
    string errMsg;
    vector<ret_to_qt> rtq;

	friend istream& operator >>(istream& in, grammar & g);
	friend ostream& operator <<(ostream& out, grammar& g);

    bool grammarMapEmpty();

    int get_grammar(string s);

	void clear();
    void parsed_clear();

	void print_vt();
    string print_vt_to_qt();
    string print_vn_to_qt();

	void get_firstvt();
	void cal_firstvt(map<char, set<vector<char> > >::iterator i);
	void print_firstvt();
    string print_firstvt_to_qt();

	void get_lastvt();
	void cal_lastvt(map<char, set<vector<char> > >::iterator i);
	void print_lastvt();
    string print_lastvt_to_qt();

	void get_relation();
	void add_relation(char x, char y, short comp);
	bool print_relation();
    string print_relation_to_qt();
    void fill_relation();

	void get_find();

	void parsing();
    void parsing_to_qt();
    void get_code();
    bool get_code(string ss);

    string code_to_string();

    int comp();
	char get_top();
	char reduction();
	bool findNonTerminal(char x, char y);
	void print_state();

    bool reductionSuccess();

};

#endif // !_GRAMMARLIST_H_
