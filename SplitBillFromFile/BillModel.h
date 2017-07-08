#ifndef H_BILLMODEL
#define H_BILLMODEL

#include<string>
#include<map>

using namespace std;

const string keywordTotal = "TOTAL";
const string keywordItem = "ITEM";
const string keywordAll = "ALL";

class Item {
public:
	Item();
	Item(string, int);
	~Item();
	string GetName();
	int GetPrice();
	void SetName(string);
	void SetPrice(int);
private:
	string* name;
	int* price;
};

class Splitter {
public:
	Splitter();
	Splitter(string name);
	~Splitter();
	map<string, Item*>* GetItems();
	string GetName();
	int GetTotalContribution();
	int GetTax();
	void AddItem(Item*);
	void AddItem(string, int);
	void SetName(string);
	void ComputeTotalContribution();
	void ComputeTaxFromBillTotalAndContribution(int, int);
private:
	map<string, Item*>* items;
	string* name;
	int* totalContribution;
	int* tax;
};

class Bill {
public:
	Bill();
	~Bill();
	map<string, Splitter*>* GetSplitters();
	int GetTotalBill();
	int GetTax();
	void AddSplitter(Splitter*);
	void AddItemForAllSplitters(Item*);
	void ComputeTotalBill();
	void SetTax(int);
private:
	map<string, Splitter*>* splitters;
	int* totalBill;
	int* tax;
	int* grandTotal;
};

#endif