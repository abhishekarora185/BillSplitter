# BillSplitter
For splitting food bills that include tax. Takes a specified text file format containing participants, items, who ate what, and the total, and computes each person's share, proportionately allocating taxes.

To use this program, keep a txt file with a unique name in the Bills\ folder, providing that same name (omitting the .txt) as input to the program.
Provide the following details in the file:

FIRST LINE: <splitter1> <splitter2> <splitter3> <splitter4>...
SECOND LINE onwards: ITEM <Item name> <Total price> <splitter1> <splitter2>.... (in case everyone splits the item, just enter "ALL" after the total price)
FINAL LINE: TOTAL <Grand total of bill>

NOTE: 
1. All amounts should be integers. Because of numerous divisions, the grand total computed may be a few units less than the actual value.
2. Don't put spaces in the item name, the names entered in second line onwards should match the ones in the first line

Use the example in the Bills/ folder as a reference.
