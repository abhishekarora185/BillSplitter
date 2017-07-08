#include "Main.h"

using namespace std;

int main(){
	cout << "Split Bill -- Filename? ";
	string fileName;
	getline(cin, fileName);

	BillFileReader* fileReader = new BillFileReader(fileName);
	fileReader->ComputeBill();

	Bill finalBill = *fileReader->GetBill();

	// Print the results of the bill computation, namely each person, their total and grand total
	cout << "\n<Name> : <Total> + <Tax> = <Grand Total>";

	map<string, Splitter*>::iterator it = finalBill.GetSplitters()->begin();
	while (it != finalBill.GetSplitters()->end()) {
		cout << "\n" << it->second->GetName() << " : " << it->second->GetTotalContribution() << " + " << it->second->GetTax() << " = " << it->second->GetTotalContribution() + it->second->GetTax();
		it++;
	}

	char quit;
	cout << "\n\nQuit? (Press any key and hit enter)";
	cin >> quit;

	return 0;
}