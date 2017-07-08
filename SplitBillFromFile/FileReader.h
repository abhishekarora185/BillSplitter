#ifndef H_FILEREADER
#define H_FILEREADER

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "BillModel.h"

const string filePath = "./Bills/";
const string fileTypeExtension = ".txt";

using namespace std;

class BillFileReader {
public:
	BillFileReader();
	BillFileReader(string);
	~BillFileReader();
	void OpenFile(string);
	Bill* GetBill();
	void ComputeBill();
private:
	Bill* bill;
	ifstream* billFile;
};

#endif