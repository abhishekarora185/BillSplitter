#include "BillModel.h"

// Define Item methods

Item::Item() {
	this->name = new string;
	this->price = new int;
}

Item::Item(string name, int price) {
	this->name = new string(name);
	this->price = new int(price);
}

Item::~Item() {
	delete this->name;
	delete this->price;
	this->name = 0;
	this->price = 0;
}

string Item::GetName() {
	return *this->name;
}

int Item::GetPrice() {
	return *this->price;
}

void Item::SetName(string name) {
	*this->name = name;
}

void Item::SetPrice(int price) {
	*this->price = price;
}

// Define Splitter methods

Splitter::Splitter() {
	this->items = new map<string, Item*>;
	this->totalContribution = new int;
}

Splitter::Splitter(string name) {
	this->items = new map<string, Item*>;
	this->name = new string(name);
	this->totalContribution = new int;
	this->tax = new int;
	*this->totalContribution = 0;
	*this->tax = 0;
}

Splitter::~Splitter() {
	delete this->items;
	delete this->name;
	delete this->totalContribution;
	delete this->tax;
	this->items = 0;
	this->name = 0;
	this->totalContribution = 0;
	this->tax = 0;
}

map<string, Item*>* Splitter::GetItems() {
	return this->items;
}

string Splitter::GetName() {
	return *this->name;
}

int Splitter::GetTotalContribution() {
	return *this->totalContribution;
}

int Splitter::GetTax() {
	return *this->tax;
}

void Splitter::ComputeTotalContribution() {
	map<string, Item*>::iterator it = this->items->begin();
	int totalContribution = 0;

	while (it != this->items->end())
	{
		totalContribution += it->second->GetPrice();
		it++;
	}

	*this->totalContribution = totalContribution;
}

void Splitter::AddItem(Item* item) {
	this->items->insert(make_pair(item->GetName(), item));
}

void Splitter::AddItem(string name, int price) {
	Item *newItem = new Item(name, price);
	this->items->insert(make_pair(name, new Item(name, price)));
}

void Splitter::SetName(string name) {
	*this->name = name;
}

void Splitter::ComputeTaxFromBillTotalAndContribution(int billTotal, int billTax) {
	// Proportionate tax calculation
	int individualTax = billTax * (*this->totalContribution) / billTotal;
	*this->tax = individualTax;
}

// Define Bill methods

Bill::Bill() {
	this->splitters = new map<string, Splitter*>;
	this->totalBill = new int;
	this->tax = new int;
	this->grandTotal = new int;
	*this->totalBill = 0;
	*this->tax = 0;
	*this->grandTotal = 0;
}

Bill::~Bill() {
	delete this->splitters;
	delete this->totalBill;
	delete this->tax;
	delete this->grandTotal;
	this->splitters = 0;
	this->totalBill = 0;
	this->tax = 0;
	this->grandTotal = 0;
}

map<string, Splitter*>* Bill::GetSplitters() {
	return this->splitters;
}

int Bill::GetTotalBill() {
	return *this->totalBill;
}

int Bill::GetTax() {
	return *this->tax;
}

void Bill::AddSplitter(Splitter* splitter) {
	this->splitters->insert(make_pair(splitter->GetName(), splitter));
}

void Bill::AddItemForAllSplitters(Item* item) {
	map<string, Splitter*>::iterator it = this->splitters->begin();
	item->SetPrice(item->GetPrice() / this->splitters->size());

	while (it != this->splitters->end()) {
		it->second->AddItem(item);
		it++;
	}
}

void Bill::ComputeTotalBill() {
	map<string, Splitter*>::iterator it = this->splitters->begin();
	int totalBill = 0;

	while (it != this->splitters->end()) {
		if (it->second->GetTotalContribution() == 0) {
			it->second->ComputeTotalContribution();
		}
		totalBill += it->second->GetTotalContribution();
		it++;
	}

	*this->totalBill = totalBill;
}

void Bill::SetTax(int tax) {
	*this->tax = tax;
	*this->grandTotal = *this->totalBill + *this->tax;

	// Now that the bill's tax has been set, let each splitter compute its own tax contribution from the total and tax amounts
	map<string, Splitter*>::iterator it = this->splitters->begin();

	while (it != splitters->end()) {
		it->second->ComputeTaxFromBillTotalAndContribution(*this->totalBill, *this->tax);
		it++;
	}
}