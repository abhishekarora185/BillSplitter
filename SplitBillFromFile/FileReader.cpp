#include "FileReader.h"

BillFileReader::BillFileReader() {
	this->bill = new Bill;
	this->billFile = new ifstream;
}

BillFileReader::BillFileReader(string fileName) {
	this->bill = new Bill;
	this->billFile = new ifstream;
	this->OpenFile(fileName);
}

BillFileReader::~BillFileReader() {
	this->billFile->close();
	delete this->bill;
	delete this->billFile;
}

void BillFileReader::OpenFile(string fileName) {
	string fullFilePath = filePath + fileName + fileTypeExtension;
	this->billFile->open(fullFilePath.c_str(), ifstream::in);
}

Bill* BillFileReader::GetBill() {
	return this->bill;
}

void BillFileReader::ComputeBill() {
	// Read the file in the specified format

	// First line - names of splitters
	string str;

	while (*this->billFile >> str && str != keywordItem) {
		this->bill->AddSplitter(new Splitter(str));
	}

	// Now, keep reading in the format <ITEM keyword> <item> <price> <splitters>
	while (str == keywordItem) {
		string itemName;
		int itemPrice;
		
		*this->billFile >> itemName;
		*this->billFile >> itemPrice;

		
		int numberOfSplittersForItem = 0;
		vector<string>* splittersForItem = new vector<string>;

		// Store the names of splitters, and count them
		while (*this->billFile >> str && str != keywordItem && str != keywordTotal) {
			if (str != keywordAll) {
				numberOfSplittersForItem++;
			}
			splittersForItem->push_back(str);
		}

		// Create an item based on the split price
		if (numberOfSplittersForItem > 0) {
			itemPrice = itemPrice / numberOfSplittersForItem;
		}
		Item* item = new Item(itemName, itemPrice);

		vector<string>::iterator it = splittersForItem->begin();
		while (it != splittersForItem->end()) {
			if (numberOfSplittersForItem == 0 && *it == keywordAll){
				// Append the item to all splitters
				this->bill->AddItemForAllSplitters(item);
				break;
			}
			else {
				this->bill->GetSplitters()->find(*it)->second->AddItem(item);
			}

			it++;
		}

		delete splittersForItem;
		splittersForItem = 0;
	}

	// Compute and store the total without tax
	this->bill->ComputeTotalBill();

	// Now, store the grand total and use it to compute the tax split
	int grandTotal;
	*this->billFile >> grandTotal;

	this->bill->SetTax(grandTotal - this->bill->GetTotalBill());
}