#include<iostream>
#include<fstream>
#include<sstream>

#include<set>
#include<list>
#include<vector>
#include<string>

#include<stdlib.h>
#include<Windows.h>
#include<time.h>
#include<algorithm>

#include"Goods_GoodsList.h"
#include"Block_BlocksList.h"
#include"Bill_BillsList.h"

#include"Menu_Data_Structure.h"

#include"winfunc.h"

using namespace std;
using namespace console_setting;

/* ===== Variable Declaration ===== */
GoodsList listOfGoods(MAX_BLOCKS);
BlocksList listOfBlocks;
BillsList listOfBills;

set<string> unavailableID;
/* =================================*/



/* ==================== BEGIN OF: LOAD_UPLOAD_BACKUP_UNDO DATABASE IN FILE ==================== */

/* Read a string to a vector of string line without space. */
vector<string> readFromLineToStringVector(const string& line)
{
	vector<string> result;
	std::stringstream ss(line, ios_base::in);

	while (ss.good()) {
		string substr;
		getline(ss, substr, ' ');
		result.push_back(substr);
	}
	return move(result);
}

/* Copy a file to another file. */
void copyFile(fstream& file_inp, fstream& file_out)
{
	vector<string> data;

	while (!file_inp.eof()) {
		string line;
		getline(file_inp, line, '\n');
		data.push_back(line);
	}

	for (int i = 0; i < data.size(); i++) {
		if (i == data.size() - 1) file_out << data[i];
		else file_out << data[i] << endl;
	}
}

/* Load from file to list of Goods, return 0 if successful, return -1  if not. */
int loadGoodsDB()
{
	fstream file_of_goods;
	file_of_goods.open("List of Goods_upToDate.txt", ios::in);

	fstream backup_file;
	backup_file.open("List of Goods_backup.txt", ios::out);

	if (file_of_goods.is_open()) {
		int number; file_of_goods >> number;
		file_of_goods.seekg(2, ios::cur);

		if (number > MAX_BLOCKS) {
			file_of_goods.close();
			backup_file.close();
			return -1;
		};

		for (int i = 0; i < number; i++) {
			string line;
			getline(file_of_goods, line, '\n');

			vector<string> parsedLine = readFromLineToStringVector(line);
			Goods _temp(parsedLine[0], parsedLine[1], parsedLine[2], stoi(parsedLine[3]), stoi(parsedLine[4]), stoi(parsedLine[5]), stoi(parsedLine[6]), stoi(parsedLine[7]), stoi(parsedLine[8]), parsedLine[9]);
			listOfGoods.addGoods(_temp);
		}

		// Comeback the begin of file upToDate, then copy it to backup file.
		file_of_goods.seekg(0, ios::beg);
		copyFile(file_of_goods, backup_file);

		file_of_goods.close();
		backup_file.close();
		return 0;
	}

	file_of_goods.close();
	backup_file.close();
	return -1;
}

/* Load from file to list of Blocks, return 0 if successful, return -1  if not. */
int loadBlocksDB()
{
	fstream file_of_blocks;
	file_of_blocks.open("List of BLocks_upToDate.txt", ios::in);

	fstream backup_file;
	backup_file.open("List of Blocks_backup.txt", ios::out);

	if (file_of_blocks.is_open()) {
		int number; file_of_blocks >> number;
		file_of_blocks.seekg(2, ios::cur);

		if (number > MAX_BLOCKS) {
			file_of_blocks.close();
			backup_file.close();
			return -1;
		};

		for (int i = 0; i < number; i++) {
			string line;
			getline(file_of_blocks, line, '\n');

			vector<string> parsedLine = readFromLineToStringVector(line);
			Block _temp(parsedLine[0], parsedLine[1], stoi(parsedLine[2]), stoi(parsedLine[3]));
			listOfBlocks.addBlock(_temp);
		}

		// Comeback the begin of file upToDate, then copy it to backup file.
		file_of_blocks.seekg(0, ios::beg);
		copyFile(file_of_blocks, backup_file);

		file_of_blocks.close();
		backup_file.close();
		return 0;
	}

	file_of_blocks.close();
	backup_file.close();
	return -1;
}

/* Load from file to list of Bills, return 0 if successful, return -1  if not. */
int loadBillsDB()
{
	fstream file_of_bills;
	file_of_bills.open("List of Bills_upToDate.txt", ios::in);

	fstream backup_file;
	backup_file.open("List of Bills_backup.txt", ios::out);

	if (file_of_bills.is_open()) {
		int number; file_of_bills >> number;
		file_of_bills.seekg(2, ios::cur);

		if (number > MAX_BILLS) {
			file_of_bills.close();
			backup_file.close();
			return -1;
		};

		for (int i = 0; i < number; i++) {
			string inforLine;
			getline(file_of_bills, inforLine, '\n');

			vector<string> infor = readFromLineToStringVector(inforLine);
			Bill temp(infor[0], infor[1], infor[2], stoi(infor[3]));
			unavailableID.insert(infor[0]);

			vector<vector<string>> singleBill;

			for (int j = 0; j < stoi(infor[3]); j++) {
				string line;
				getline(file_of_bills, line, '\n');

				vector<string> parsedLine = readFromLineToStringVector(line);

				singleBill.push_back(parsedLine);
			}

			temp.setSingleBill(singleBill);

			listOfBills.addBill(temp);
		}

		// Comeback the begin of file upToDate, then copy it to backup file.
		file_of_bills.seekg(0, ios::beg);
		copyFile(file_of_bills, backup_file);

		file_of_bills.close();
		backup_file.close();
		return 0;
	}

	file_of_bills.close();
	backup_file.close();
	return -1;
}

/* Upload Goods DataBase to file, return 0 if successful, return -1 if not. */
int uploadGoodsDB()
{
	fstream file_of_goods;
	file_of_goods.open("List of Goods_upToDate.txt", ios::out);

	if (file_of_goods.is_open()) {
		file_of_goods << listOfGoods.toFile();
		file_of_goods.close();
		return 0;
	}

	file_of_goods.close();
	return -1;
}

/* Upload Blocks DataBase to file, return 0 if successful, return -1 if not. */
int uploadBlocksDB()
{
	fstream file_of_blocks;
	file_of_blocks.open("List of Blocks_upToDate.txt", ios::out);

	if (file_of_blocks.is_open()) {
		file_of_blocks << listOfBlocks.toFile();
		file_of_blocks.close();
		return 0;
	}

	file_of_blocks.close();
	return -1;
}

/* Upload Bills DataBase to file, return 0 if successful, return -1 if not. */
int uploadBillsDB()
{
	fstream file_of_bills;
	file_of_bills.open("List of Bills_upToDate.txt", ios::out);

	if (file_of_bills.is_open()) {
		file_of_bills << listOfBills.toFile();
		file_of_bills.close();
		return 0;
	}

	file_of_bills.close();
	return -1;
}

/* Load sample database from file */
string loadDB()
{
	int goodsCheck = loadGoodsDB();
	if (goodsCheck == -1)
		return " Error while loading Goods DataBase.\n";

	int blocksCheck = loadBlocksDB();
	if (blocksCheck == -1)
		return "Error while loading Block DataBase.\n";

	int billsCheck = loadBillsDB();
	if (billsCheck == -1)
		return "Error while loading Bill DataBase.\n";

	return "Load and backup DataBase completed.\n";
}

/* Upload sample database to file */
string uploadDB()
{
	int goodsCheck = uploadGoodsDB();
	if (goodsCheck == -1)
		return " Error while uploading Goods DataBase.\n";

	int blocksCheck = uploadBlocksDB();
	if (blocksCheck == -1)
		return "Error while uploading Block DataBase.\n";

	int billsCheck = uploadBillsDB();
	if (billsCheck == -1)
		return "Error while uploading Bill DataBase.\n";

	return "Upload completed.\n";
}

/* Undo DataBase. */
string undoDB()
{
	fstream list_of_goods;
	list_of_goods.open("List of Goods_upToDate.txt", ios::out);
	fstream backup_goods;
	backup_goods.open("List of Goods_backup.txt", ios::in);

	fstream list_of_blocks;
	list_of_blocks.open("List of Blocks_upToDate.txt", ios::out);
	fstream backup_blocks;
	backup_blocks.open("List of Blocks_backup.txt", ios::in);

	fstream list_of_bills;
	list_of_bills.open("List of Bills_upToDate.txt", ios::out);
	fstream backup_bills;
	backup_bills.open("List of Bills_backup.txt", ios::in);

	copyFile(backup_goods, list_of_goods);
	copyFile(backup_blocks, list_of_blocks);
	copyFile(backup_bills, list_of_bills);

	list_of_goods.close();
	backup_goods.close();

	list_of_blocks.close();
	backup_blocks.close();

	list_of_bills.close();
	backup_bills.close();

	return "Undo DataBase completed.\n";
}

/* ==================== END OF: LOAD_UPLOAD_BACKUP_UNDO DATABASE IN FILE ==================== */



/* =================================== BEGIN OF: FUNCTION =================================== */

/* Return a string with given number of spaces. */
const string spacesString(int spaces_num)
{
	string result;
	for (int i = 0; i < spaces_num; i++) result += " ";
	return move(result);
}

/* Auto set number of empty slot in every block. */
void correctEmptySlotInBlock_forCreateBill()
{
	list<Block> result;
	list<Block> temp_list = listOfBlocks.getList();

	for (auto& block : temp_list) {
		if (block.isEmpty()) continue;

		Goods goods_temp = listOfGoods.find_byID(block.getGoodsID());
		block.setEmpty(goods_temp.getMaxUnitsInOneBLock() - block.getQuantity());

		result.push_back(block);
	}

	listOfBlocks.setList(result);
}

/* Create a new Bill, change information in database, return bill ID */
string createBill(string _date, string _type, unsigned _numberOfGoods, vector<vector<string>> _singleBill)
{
	// Random a new ID for Bill, which not existed in database.
	srand((unsigned int)time(0));

	long int newID_num = rand() % (MAX_ID - MIN_ID + 1) + MIN_ID;
	string newID_str = to_string(newID_num);

	set<string>::iterator it;
	it = unavailableID.find(newID_str);

	while (it != unavailableID.end()) {
		newID_num = rand() % (MAX_ID - MIN_ID + 1) + MIN_ID;
		newID_str = to_string(newID_num);
		it = unavailableID.find(newID_str);
	}

	// new ID = newID_str

	Bill newBill(newID_str, _date, _type, _numberOfGoods, _singleBill);
	listOfBills.addBill(newBill);

	if (_type == "Import") { // The bill is import bill.
		for (int i = 0; i < _numberOfGoods; i++) {
			Goods goods_toChange = listOfGoods.find_byID(_singleBill[i][0]);
			goods_toChange.setQuantity(goods_toChange.getQuantity() + stoi(_singleBill[i][3]));

			// Change in blocksList
			int plus_left = stoi(_singleBill[i][3]);
			list<string> blockLocation = goods_toChange.getLocations();
			list<string>::iterator it = blockLocation.begin();

			for (it; it != blockLocation.end(); it++) {
				Block temp = listOfBlocks.find_byID(*it);

				if (temp.isFull())
					continue;

				if (plus_left < temp.getEmpty()) {
					temp.setQuantity(temp.getQuantity() + plus_left);
					plus_left = 0;
				}
				else {
					Goods goods_temp = listOfGoods.find_byID(temp.getGoodsID());
					temp.setQuantity(goods_temp.getMaxUnitsInOneBLock());
					plus_left -= goods_temp.getMaxUnitsInOneBLock();
				}
			}

			while (plus_left > 0) {
				cout << "Enter new block to store this goods: " << goods_toChange.getName();
				string newBlock_str;
				cin >> newBlock_str;

				if (!listOfBlocks.checkBlockEmpty(newBlock_str)) {
					cout << "This block is unavailable, please enter a new one.\n";
					continue;
				}

				Block newBlock_block;
				newBlock_block.setBlockID(newBlock_str);
				newBlock_block.setGoodsID(_singleBill[i][0]);
				Goods goods_temp = listOfGoods.find_byID(_singleBill[i][0]);

				if (plus_left <= goods_temp.getMaxUnitsInOneBLock()) {
					newBlock_block.setQuantity(plus_left);
					listOfBlocks.addBlock(newBlock_block);
					blockLocation.push_back(newBlock_str);
					break;
				}

				newBlock_block.setQuantity(goods_temp.getMaxUnitsInOneBLock());
				plus_left -= goods_temp.getMaxUnitsInOneBLock();

				listOfBlocks.addBlock(newBlock_block);
				blockLocation.push_back(newBlock_str);
			}

			list<string> newLocation;
			it = blockLocation.begin();
			for (it; it != blockLocation.end(); it++) {
				Block temp = listOfBlocks.find_byID(*it);
				if (temp.getQuantity() == 0)
					continue;
				newLocation.push_back(temp.getBlockID());
			}

			goods_toChange.setLocation(newLocation);
			listOfGoods.replaceGoods(_singleBill[i][0], goods_toChange);
		}
	}
	else { // The bill is export bill.
		for (int i = 0; i < _numberOfGoods; i++) {
			Goods goods_toChange = listOfGoods.find_byID(_singleBill[i][0]);
			goods_toChange.setQuantity(goods_toChange.getQuantity() - stoi(_singleBill[i][3]));

			// Change in blocksList
			int minus_left = stoi(_singleBill[i][3]);
			list<string> blockLocation = goods_toChange.getLocations();
			list<string>::iterator it = blockLocation.begin();

			while (minus_left > 0) {
				Block temp = listOfBlocks.find_byID(*it);

				if (temp.getQuantity() > minus_left) {
					temp.setQuantity(temp.getQuantity() - minus_left);
					listOfBlocks.replaceBlock(*it, temp);
					break;
				}
				else if (temp.getQuantity() == minus_left) {
					blockLocation.remove(temp.getBlockID());
					temp.setQuantity(0);
					listOfBlocks.replaceBlock(*it, temp);
					break;
				}

				minus_left -= temp.getQuantity();
				temp.setQuantity(0);
				listOfBlocks.replaceBlock(*it, temp);
				it++;
			}

			list<string> newLocation;
			it = blockLocation.begin();
			for (it; it != blockLocation.end(); it++) {
				Block temp = listOfBlocks.find_byID(*it);
				if (temp.getQuantity() == 0) continue;
				newLocation.push_back(temp.getBlockID());
			}

			goods_toChange.setLocation(newLocation);
			listOfGoods.replaceGoods(_singleBill[i][0], goods_toChange);
		}
	}

	correctEmptySlotInBlock_forCreateBill();
	return newID_str;
}

void blockManagementMenu_displayGeneral()
{
	cout << listOfBlocks.displayGeneralInfor() << endl;
} string func_block_displayGeneral = "Display General Information";

void blockManagementMenu_displayEmptyBlock()
{
	cout << "===========================================================================" << endl;
	cout << listOfBlocks.displayEmptyBlocks() << endl;
	cout << "===========================================================================" << endl;
} string func_block_displayEmptyBlock = "Display Empty Blocks List";

void blockManagementMenu_displayNonEmptyBlock()
{
	vector<vector<string>> displayThis = listOfBlocks.displayNonEmptyBlocks();
	cout << "=======================================================" << endl;
	cout << "| No. | Block ID |  Goods ID  | Quantity | Empty slot |\n"; // 5, 10, 12, 10, 12
	for (auto& line : displayThis) {
		cout << "| " + line[0] + spacesString(4 - line[0].size())
			<< "| " + line[1] + spacesString(9 - line[1].size())
			<< "| " + line[2] + spacesString(11 - line[2].size())
			<< "| " + line[3] + spacesString(9 - line[3].size())
			<< "| " + line[4] + spacesString(11 - line[4].size())
			<< "|\n";
	}
	cout << "=======================================================" << endl;
} string func_block_displayNonEmptyBlock = "Display Non-Empty Blocks List";

void blockManagementMenu_searchBlockID() {
	cout << "  Enter the Block ID to searh: ";

	string id; cin >> id;
	vector<Block> result = listOfBlocks.searchbyBlockID(id);

	if (result.empty())
		cout << endl << ">... No matching blocks found.\n" << endl;
	else {
		cout << endl << ">... Found " << result.size() << (result.size() == 1 ? " matching block:" : " matching blocks:") << endl;
		for (auto& block : result) {
			cout << block.toDisplay() << endl;
			cout << "====================================" << endl;
		}
	}
} string func_block_searchBlockID = "Search by Block ID";

void blockManagementMenu_searchGoodsID() {
	cout << "  Enter the Goods ID to search: ";

	string id; cin >> id;
	vector<Block> result = listOfBlocks.searchbyGoodsID(id);

	if (result.empty())
		cout << ">... No matching blocks found.\n" << endl;
	else {
		cout << ">... Found " << result.size() << (result.size() == 1 ? " matching block:" : " matching blocks:") << endl;
		for (auto& block : result) {
			cout << block.toDisplay() << endl;
			cout << "====================================" << endl;
		}
	}
} string func_block_searchGoodsID = "Search by Goods ID";

void blockManagementMenu_delete()
{
	cout << "  Enter the Block ID to delete: ";
	string id; cin >> id;
	Block block = listOfBlocks.find_byID(id);

	if (block.isEmpty()) {
		list<Block> new_list = listOfBlocks.delBlock(id);
		listOfBlocks.setList(new_list);
		cout << endl << ">... This Block is deleted.\n";
		return;
	}

	cout << endl << "WARNING: This block is not empty.\n"
		<< "Deleting this block will immediately change the value of the goods contained in this block.\n"
		<< "Do you want to continue? (y/n) ";
	string option; cin >> option;

	if (option == "n") {
		cout << endl << ">... Done cancel this block deletion.\n";
		return;
	}

	Goods new_goods = listOfGoods.find_byID(block.getGoodsID());

	list<string> new_location = new_goods.getLocations();
	new_location.remove(id);
	new_goods.setLocation(new_location);

	new_goods.setQuantity(new_goods.getQuantity() - block.getQuantity());

	listOfGoods.replaceGoods(block.getGoodsID(), new_goods);

	list<Block> new_list = listOfBlocks.delBlock(id);
	listOfBlocks.setList(new_list);

	cout << endl << ">... Deleted this block and changed the value of the goods accordingly.\n";
} string func_block_delete = "Delete Block";

void blockManagementMenu_move()
{
	cout << "  Enter the block to be moved: ";
	string from_block; cin >> from_block;

	cout << "Do you want to display list of empty block? (y/n) ";
	string option; cin >> option;
	if (option == "y")
		cout << listOfBlocks.displayEmptyBlocks();

	cout << "Enter the block to move to: ";
	string to_block; cin >> to_block;
	clrscr();

	Block old_block = listOfBlocks.find_byID(from_block);
	Block new_block(to_block, old_block.getGoodsID(), old_block.getQuantity(), old_block.getEmpty());

	int checkAdd = listOfBlocks.addBlock(new_block);
	list<Block> new_list = listOfBlocks.delBlock(from_block);
	listOfBlocks.setList(new_list);

	Goods goods_toChange = listOfGoods.find_byID(new_block.getGoodsID());
	list<string> new_location = goods_toChange.getLocations();
	replace_if(new_location.begin(), new_location.end(),
		[&](string loca) { return loca == from_block; },
		to_block);
	goods_toChange.setLocation(new_location);
	listOfGoods.replaceGoods(new_block.getGoodsID(), goods_toChange);

	cout << ">... Move successful.\n";
} string func_block_move = "Move Goods from a Block to another Block";


void mainMenu_undo()
{
	cout << "  Do you want to undo the database? (y/n) ";
	string option; cin >> option;

	if (option == "n")
		return;

	cout << undoDB() << loadDB() << endl;
} string func_main_undo = "Undo DataBase to previous version";

void mainMenu_exit()
{
	cout << "  Do you want to continue? (y/n) ";
	string option; cin >> option;

	if (option == "n")
		return;

	clrscr();
	cout << uploadDB() << endl;
	cout << "Exit!!!"; exit(0);
} string func_main_exit = "Exit program";

void mainMenu_createBill()
{
	cout << "  Automatically generate new Bill ID: Done.\n";

	cout << "  Enter date: ";
	string date; cin >> date;
	cout << "  Enter type of bill (Import/Export): ";
	string type; cin >> type;
	cout << "  Enter number of goods in this bill: ";
	unsigned int number; cin >> number;
	clrscr();

	cout << "  Enter the information of each goods:\n";

	vector<vector<string>> singleBill;
	for (int i = 1; i <= number; i++) {
		vector<string> line;
		string buffer;

		cout << "No." << i << endl;
		cout << "  Goods ID: ";
		cin >> buffer; line.push_back(buffer); buffer.clear();
		cout << "  Goods Name: ";
		cin >> buffer; line.push_back(buffer); buffer.clear();
		cout << "  Goods Unit: ";
		cin >> buffer; line.push_back(buffer); buffer.clear();
		cout << "  Quantity: ";
		cin >> buffer; line.push_back(buffer); buffer.clear();

		singleBill.push_back(line);
	}

	clrscr();
	cout << ">... Create Bill successful.\n" << endl;

	cout << "Bill ID: " << createBill(date, type, number, singleBill) << endl;
	cout << "Date: " << date << endl;
	cout << "Type: " << type << endl;
	cout << "Number of goods in bill: " << number << endl;

	cout << "=======================================================================" << endl;
	int count = 0;
	cout << "| No. |  Goods ID  |          Goods Name          |  Unit  | Quantity |\n"; // 4, 11, 29, 7, 9
	for (auto& line : singleBill) {
		cout << "| " + to_string(++count) + spacesString(4 - to_string(count).size())
			<< "| " + line[0] + spacesString(11 - line[0].size())
			<< "| " + line[1] + spacesString(29 - line[1].size())
			<< "| " + line[2] + spacesString(7 - line[2].size())
			<< "| " + line[3] + spacesString(9 - line[3].size())
			<< "|\n";
	}
	cout << "=======================================================================" << endl;

} string func_main_createBill = "Create new Bill";
//intro
void draw(int color, int n) {
	setcolor(color, color);
	for (int i = 0; i < n; i++) cout << " ";
}
void endl() {
	cout << "\n";
}
void intro() {
	endl();
	draw(0, 2);     /*D*/ draw(9, 4);                           draw(0, 3);     /*H*/ draw(10, 2); draw(0, 2); draw(10, 2);      draw(0, 2);    /*A*/ draw(12, 4);                           endl();
	draw(0, 2);     /*D*/ draw(9, 2); draw(0, 2); draw(9, 2);   draw(0, 1);     /*H*/ draw(10, 2); draw(0, 2); draw(10, 2);      draw(0, 1);    /*A*/ draw(12, 2); draw(0, 2); draw(12, 2);  endl();
	draw(0, 2);     /*D*/ draw(9, 2); draw(0, 2); draw(9, 2);   draw(0, 1);     /*H*/ draw(10, 6);                               draw(0, 1);    /*A*/ draw(12, 2); draw(0, 2); draw(12, 2);  endl();
	draw(0, 2);     /*D*/ draw(9, 2); draw(0, 2); draw(9, 2);   draw(0, 1);     /*H*/ draw(10, 2); draw(0, 2); draw(10, 2);      draw(0, 1);    /*A*/ draw(12, 6);                           endl();
	draw(0, 2);     /*D*/ draw(9, 4);                           draw(0, 3);     /*H*/ draw(10, 2); draw(0, 2); draw(10, 2);      draw(0, 1);    /*A*/ draw(12, 2); draw(0, 2); draw(12, 2);  endl();
	endl();
	draw(0, 2); setcolor(0, 14); cout << "Warehouse Management System" << endl<<endl;
}
void loading() {
	for (int i = 1; i <= 10; i++) {
		setcolor(0, 6); gotoxy(5, 10); cout << "LOADING " << i << "0%"<<endl;
		draw(0, 5); draw(11, i*2);
		Sleep(200);
	}
	endl();
}
void consolesetting() {
	SetTitle(L"Warehouse Management System");
	SetMaximize();
}

void pre_mainMenu() {
	consolesetting();
	intro(); loading(); setcolor(0, 7);
	cout << loadDB() << endl;
	
	for (int i = 3; i > 1; i--) {
		cout << "Go to Main Menu in " << i << " seconds.\n";
		Sleep(1000);
	}
	cout << "Go to Main Menu in 1 second.\n";
	Sleep(1000);

	clrscr();
} string func_pre = "Load and Back up DataBase";


void goodsManagementMenu_displayList()
{
	vector<vector<string>> displayMe = listOfGoods.displayList();
	cout << "=======================================================================================================================================" << endl;
	cout << "| No. |  Goods ID  |             Goods Name             | Quantity | Unit | Import Price | Export Price |          Locations          |\n";
	for (auto& line : displayMe) {
		cout << "| " + line[0] + spacesString(4 - line[0].size())
			<< "| " + line[1] + spacesString(11 - line[1].size())
			<< "| " + line[2] + spacesString(35 - line[2].size())
			<< "| " + line[3] + spacesString(9 - line[3].size())
			<< "| " + line[4] + spacesString(5 - line[4].size())
			<< "| " + line[5] + spacesString(13 - line[5].size())
			<< "| " + line[6] + spacesString(13 - line[6].size())
			<< "| " + line[7] + spacesString(28 - line[7].size())
			<< "|\n";
	}
	cout << "=======================================================================================================================================" << endl;
} string func_goods_displayList = "Display list of all Goods in system";

void goodsManagementMenu_importMore()
{
	vector<Goods> displayMe = listOfGoods.importMore();

	if (displayMe.size() == 0)
		cout << ">... There are no goods that need to be imported.\n";
	else {
		cout << ">... There are " << (displayMe.size()) << " goods that need to be imported.\n" << endl;

		int count = 0;
		cout << "=======================================================================" << endl;
		cout << "| No. |  Goods ID  |             Goods Name             | Import More |\n";
		for (auto& goods : displayMe) {
			cout << "| " + to_string(++count) + spacesString(4 - to_string(count).size())
				+ "| " + goods.getID() + spacesString(11 - goods.getID().size())
				+ "| " + goods.getName() + spacesString(35 - goods.getName().size())
				+ "| " + to_string(goods.getlowerLimit() - goods.getQuantity()) + spacesString(12 - to_string(goods.getlowerLimit() - goods.getQuantity()).size())
				+ "|\n";
		}
		cout << "=======================================================================" << endl;
	}
} string func_goods_imMore = "Display list of Goods that need to be imported more";

void goodsManagementMenu_notImportMore()
{
	vector<Goods> displayMe = listOfGoods.notImportMore();

	if (displayMe.size() == 0)
		cout << ">... There are no goods that dont't need to be imported.\n";
	else {
		cout << ">... There are " << (displayMe.size()) << " goods that don't need to be imported.\n" << endl;

		int count = 0;
		cout << "=========================================================" << endl;
		cout << "| No. |  Goods ID  |             Goods Name             |\n";
		for (auto& goods : displayMe) {
			cout << "| " + to_string(++count) + spacesString(4 - to_string(count).size())
				+ "| " + goods.getID() + spacesString(11 - goods.getID().size())
				+ "| " + goods.getName() + spacesString(35 - goods.getName().size())
				+ "|\n";
		}
		cout << "=========================================================" << endl;
	}
} string func_goods_notImMore = "Display list of goods that don't need to be imported more";

void goodsManagementMenu_searchID()
{
	cout << "  Enter the Goods ID to searh: ";

	string id; cin >> id;
	vector<Goods> result = listOfGoods.searchbyID(id);

	if (result.empty())
		cout << endl << ">... No matching goods found.\n" << endl;
	else {
		cout << endl << ">... Found " << result.size() << " matching goods:" << endl;
		for (auto& goods : result) {
			cout << goods.getSimpleInfo() << endl;
			cout << "=====================================================" << endl;
		}
	}
} string func_goods_searchID = "Search by Goods ID";

void goodsManagementMenu_searchName()
{
	cout << "  Enter the Goods Name to searh: ";

	string name; cin >> name;
	vector<Goods> result = listOfGoods.searchbyName(name);

	if (result.empty())
		cout << endl << ">... No matching goods found.\n" << endl;
	else {
		cout << endl << ">... Found " << result.size() << " matching goods:" << endl;
		for (auto& goods : result) {
			cout << goods.getSimpleInfo() << endl;
			cout << "=====================================================" << endl;
		}
	}
} string func_goods_searchName = "Search by name";

void goodsManagementMenu_addGoods()
{
	cout << "  Enter ID: ";
	string id; cin >> id;

	cout << "  Enter name: ";
	string name; cin >> name;

	cout << "  Enter unit: ";
	string unit; cin >> unit;

	cout << "  Enter Import Price: ";
	unsigned int imP; cin >> imP;

	cout << "  Enter Export Price: ";
	unsigned int exP; cin >> exP;

	cout << "  Enter Quantity: ";
	int quan; cin >> quan;

	cout << "  Enter minimum quantity of this goods need in warehouse: ";
	int low; cin >> low;

	cout << "  Enter maximum quantity of this goods in warehouse: ";
	int up; cin >> up;

	cout << "  Emter maximum quantity of this goods in one block: ";
	int max; cin >> max;

	clrscr();
	cout << ">... Add new Goods to system:\n" << endl;

	int recom_num = quan / max + 1;
	cout << "Suggested block number to accommodate this goods is: " << recom_num << (recom_num == 1 ? " block\n" : " blocks\n");
	cout << "  Enter number of blocks to accommodate this goods: ";
	int num_block; cin >> num_block;

	cout << "\nDo you want to display list of empty block? (y/n) ";
	string option; cin >> option;
	if (option == "y") {
		clrscr();
		cout << listOfBlocks.displayEmptyBlocks();
	}

	list<string> location;
	int slot_left = quan;
	string buffer;
	cout << ">... Enter " << num_block << (num_block == 1 ? " block " : " blocks ") << "to accommodate this goods:\n";
	for (int i = 0; i < num_block; i++) {
		Block new_block;

		cout << endl << "  Block ID: ";
		buffer.clear(); cin >> buffer;
		new_block.setBlockID(buffer);

		new_block.setGoodsID(id);

		cout << "  Goods quantity in this block (max: " << (slot_left <= max ? slot_left : max) << "): ";
		buffer.clear(); cin >> buffer;
		new_block.setQuantity(stoi(buffer));
		slot_left -= stoi(buffer);

		new_block.setEmpty(max - new_block.getQuantity());

		listOfBlocks.addBlock(new_block);
		location.push_back(new_block.getBlockID());
	}

	Goods new_goods(id, name, unit, imP, exP, quan, low, up, max, location);
	listOfGoods.addGoods(new_goods);

	clrscr();
	cout << ">... Added new goods successfully.\n" << endl;
	cout << new_goods.getDetailedInfo();
} string func_goods_add = "Add new Goods to system";

void goodsManagementMenu_delete()
{
	cout << "  Enter the goods ID to delete: ";
	string id; cin >> id;
	Goods goods = listOfGoods.find_byID(id);

	if (goods.isEmpty()) {
		list<Goods> new_goods_list = listOfGoods.delByID(id);
		listOfGoods.setList(new_goods_list);
		cout << endl << ">... This Goods is deleted.\n";
		return;
	}

	cout << "WARNING: This goods is still in warehouse\n"
		<< "Deleting this goods will immediately change the block contain this goods.\n"
		<< "Do you want to continue? (y/n) ";
	string option; cin >> option;

	if (option == "n") {
		cout << endl << ">... Done cancel this goods deletion.\n";
		return;
	}

	list<string> block_list = goods.getLocations();
	for (auto& block : block_list) {
		list<Block> new_block_list = listOfBlocks.delBlock(block);
		listOfBlocks.setList(new_block_list);
	}

	list<Goods> new_goods_list = listOfGoods.delByID(id);
	listOfGoods.setList(new_goods_list);

	cout << endl << ">... Deleted this goods and blocks accordingly.\n";
} string func_goods_delete = "Delete Goods";

void goodsManagementMenu_changeInformation()
{
	cout << "  Enter ID of Goods need to change: ";
	string id; cin >> id;
	auto& new_goods = listOfGoods.find_byID(id);

	cout << "NOTE: If numeric information does not need to be changed, enter -1\n"
		<< "      If the text information does not need to be changed, enter #\n"
		<< endl
		<< "Modifiable information: Name, Import Price, Export Price, Locations, Minimum Quantity and Maximum Quantity.\n"
		<< "Unmodifiable information: ID, Unit, The Maximum Number Of Goods That Can Be Stored In 1 Block.\n"
		<< "Quantity only can change when create bill.\n"
		<< endl;

	clrscr();
	cout << ">... Change information about goods:\n" << endl;

	cout << "Do you want to display current information of this goods? (y/n): ";
	string option; cin >> option;
	if (option == "y")
		cout << endl << new_goods.getDetailedInfo() << endl;

	cout << "  Enter new Name: ";
	string name; cin >> name;
	cout << "  Enter new Import Price: ";
	int imP; cin >> imP;
	cout << "  Enter new Export Price: ";
	int exP; cin >> exP;
	cout << "  Enter new Minimum Quantity: ";
	int min; cin >> min;
	cout << "  Enter new Maximum Quantity: ";
	int max; cin >> max;

	clrscr();
	cout << ">... Change information about goods:\n" << endl;
	cout << "\nDo you want to display list of empty block to change location? (y/n) ";
	option.clear(); cin >> option;
	if (option == "y") {
		clrscr();
		cout << listOfBlocks.displayEmptyBlocks();
	}

	list<string> locations;
	cout << "  Enter new Locations (Block IDs are separated by spaces):\n";
	string line;
	std::getline(std::cin >> std::ws, line);
	vector<string> loc = readFromLineToStringVector(line);
	if (loc[0] != "#") {
		for (auto& str : loc)
			locations.push_back(str);
	}

	for (auto& block : new_goods.getLocations()) {
		list<Block> new_block_list = listOfBlocks.delBlock(block);
		listOfBlocks.setList(new_block_list);
	}

	new_goods.changeInfo(name, imP, exP, locations, min, max);
	listOfGoods.replaceGoods(id, new_goods);

	if (!locations.empty()) {
		int slot_left = new_goods.getQuantity();

		for (auto& block : locations) {
			Block new_block;
			new_block.setBlockID(block);
			new_block.setGoodsID(id);

			cout << "  Goods quantity in block " << block
				<< " (max: " << (slot_left <= new_goods.getMaxUnitsInOneBLock() ? slot_left : new_goods.getMaxUnitsInOneBLock()) << "): ";
			int slot; cin >> slot;
			new_block.setQuantity(slot);
			slot_left -= slot;

			new_block.setEmpty(new_goods.getMaxUnitsInOneBLock() - slot);

			listOfBlocks.addBlock(new_block);
		}
	}

	clrscr();
	cout << ">... Finished changing information.\n";
	cout << "New information of Goods " << id << " :\n";
	cout << new_goods.getDetailedInfo() << endl;
} string func_goods_change = "Change information about one Goods";


void billManagementMenu_displayList()
{
	cout << endl << "There are " << listOfBills.getNumberOfBills() << " bills in stock.\n" << endl;

	for (auto& bill : listOfBills.getList()) {
		cout << "Bill ID: " << bill.getID() << endl;
		cout << "Date: " << bill.getDate() << endl;
		cout << "Type: " << bill.getType() << endl;
		cout << "Number of goods in bill: " << bill.getNumberOfGoods() << endl;

		cout << "=======================================================================" << endl;
		int count = 0;
		cout << "| No. |  Goods ID  |          Goods Name          |  Unit  | Quantity |\n"; // 4, 11, 29, 7, 9
		for (auto& line : bill.getSingleBill()) {
			cout << "| " + to_string(++count) + spacesString(4 - to_string(count).size())
				<< "| " + line[0] + spacesString(11 - line[0].size())
				<< "| " + line[1] + spacesString(29 - line[1].size())
				<< "| " + line[2] + spacesString(7 - line[2].size())
				<< "| " + line[3] + spacesString(9 - line[3].size())
				<< "|\n";
		}
		cout << "=======================================================================" << endl;
		cout << endl;
	}
} string func_bill_displayList = "Display list of all Bills in system";

void billManagementMenu_deleteByID()
{
	cout << "  Enter ID of Bill need to delete: ";
	string id; cin >> id;

	list<Bill> new_list = listOfBills.delByID(id);
	listOfBills.setList(new_list);

	cout << ">... Deleted.\n" << endl;
} string func_bill_deleteID = "Delete Bill by ID";

void billManagementMenu_deleteByDate()
{
	cout << "  Enter Date of Bills need to delete: ";
	string date; cin >> date;

	list<Bill> new_list = listOfBills.delByDate(date);
	listOfBills.setList(new_list);

	cout << ">... Deleted.\n" << endl;
} string func_bill_deleteDate = "Delete Bill by date";

void billManagementMenu_search_ID()
{
	cout << "  Enter ID: ";
	string id; cin >> id;

	auto result = listOfBills.searchbyID(id);
	if (result.empty())
		cout << ">... Couldn't find a matching bill.\n";
	else {
		cout << ">... Found " << result.size() << (result.size() == 1 ? " matching bill:" : " matching bills:") << endl
			<< endl;

		for (auto& bill : result) {
			cout << "Bill ID: " << bill.getID() << endl;
			cout << "Date: " << bill.getDate() << endl;
			cout << "Type: " << bill.getType() << endl;
			cout << "Number of goods in bill: " << bill.getNumberOfGoods() << endl;

			cout << "=======================================================================" << endl;
			int count = 0;
			cout << "| No. |  Goods ID  |          Goods Name          |  Unit  | Quantity |\n"; // 4, 11, 29, 7, 9
			for (auto& line : bill.getSingleBill()) {
				cout << "| " + to_string(++count) + spacesString(4 - to_string(count).size())
					<< "| " + line[0] + spacesString(11 - line[0].size())
					<< "| " + line[1] + spacesString(29 - line[1].size())
					<< "| " + line[2] + spacesString(7 - line[2].size())
					<< "| " + line[3] + spacesString(9 - line[3].size())
					<< "|\n";
			}
			cout << "=======================================================================" << endl;
			cout << endl;
		}
	}
} string func_bill_searchID = "Search by ID";

void billManagementMenu_search_Date()
{
	cout << "  Enter Date (dd/mm/yyyy): ";
	string date; cin >> date;

	auto result = listOfBills.searchbyDate(date);
	if (result.empty())
		cout << ">... Couldn't find a matching bill.\n";
	else {
		cout << ">... Found " << result.size() << (result.size() == 1 ? " matching bill:" : " matching bills:") << endl
			<< endl;

		for (auto& bill : result) {
			cout << "Bill ID: " << bill.getID() << endl;
			cout << "Date: " << bill.getDate() << endl;
			cout << "Type: " << bill.getType() << endl;
			cout << "Number of goods in bill: " << bill.getNumberOfGoods() << endl;

			cout << "=======================================================================" << endl;
			int count = 0;
			cout << "| No. |  Goods ID  |          Goods Name          |  Unit  | Quantity |\n"; // 4, 11, 29, 7, 9
			for (auto& line : bill.getSingleBill()) {
				cout << "| " + to_string(++count) + spacesString(4 - to_string(count).size())
					<< "| " + line[0] + spacesString(11 - line[0].size())
					<< "| " + line[1] + spacesString(29 - line[1].size())
					<< "| " + line[2] + spacesString(7 - line[2].size())
					<< "| " + line[3] + spacesString(9 - line[3].size())
					<< "|\n";
			}
			cout << "=======================================================================" << endl;
			cout << endl;
		}
	}
} string func_bill_searchDate = "Search by date";

void billManagementMenu_search_Type()
{
	cout << "  Enter Type (Import/Export): ";
	string type; cin >> type;

	auto result = listOfBills.searchbyType(type);
	if (result.empty())
		cout << ">... Couldn't find a matching bill.\n";
	else {
		cout << ">... Found " << result.size() << (result.size() == 1 ? " matching bill:" : " matching bills:") << endl
			<< endl;

		for (auto& bill : result) {
			cout << "Bill ID: " << bill.getID() << endl;
			cout << "Date: " << bill.getDate() << endl;
			cout << "Type: " << bill.getType() << endl;
			cout << "Number of goods in bill: " << bill.getNumberOfGoods() << endl;

			cout << "=======================================================================" << endl;
			int count = 0;
			cout << "| No. |  Goods ID  |          Goods Name          |  Unit  | Quantity |\n"; // 4, 11, 29, 7, 9
			for (auto& line : bill.getSingleBill()) {
				cout << "| " + to_string(++count) + spacesString(4 - to_string(count).size())
					<< "| " + line[0] + spacesString(11 - line[0].size())
					<< "| " + line[1] + spacesString(29 - line[1].size())
					<< "| " + line[2] + spacesString(7 - line[2].size())
					<< "| " + line[3] + spacesString(9 - line[3].size())
					<< "|\n";
			}
			cout << "=======================================================================" << endl;
			cout << endl;
		}
	}
} string func_bill_searchType = "Search by type";

void billManagementMenu_multiSearch()
{
	cout << "  Enter Date (dd/mm/yyyy): ";
	string date; cin >> date;
	cout << "  Enter Type (Import/Export): ";
	string type; cin >> type;

	auto result = listOfBills.multi_search(type, date);
	if (result.empty())
		cout << ">... Couldn't find a matching bill.\n";
	else {
		cout << ">... Found " << result.size() << (result.size() == 1 ? " matching bill:" : " matching bills:") << endl
			<< endl;

		for (auto& bill : result) {
			cout << "Bill ID: " << bill.getID() << endl;
			cout << "Date: " << bill.getDate() << endl;
			cout << "Type: " << bill.getType() << endl;
			cout << "Number of goods in bill: " << bill.getNumberOfGoods() << endl;

			cout << "=======================================================================" << endl;
			int count = 0;
			cout << "| No. |  Goods ID  |          Goods Name          |  Unit  | Quantity |\n"; // 4, 11, 29, 7, 9
			for (auto& line : bill.getSingleBill()) {
				cout << "| " + to_string(++count) + spacesString(4 - to_string(count).size())
					<< "| " + line[0] + spacesString(11 - line[0].size())
					<< "| " + line[1] + spacesString(29 - line[1].size())
					<< "| " + line[2] + spacesString(7 - line[2].size())
					<< "| " + line[3] + spacesString(9 - line[3].size())
					<< "|\n";
			}
			cout << "=======================================================================" << endl;
			cout << endl;
		}
	}
} string func_bill_multiSearch = "Multi-Search with type and date";

/* ==================================== END OF: FUNCTION ==================================== */




/* ================================== BEGIN OF: MENU TREE ================================== */

string main_menu = "Main Menu";
MenuNode* Main_Menu = new MenuNode(main_menu);

string block_menu = "Block Management Menu";
MenuNode* Block_Menu = new MenuNode(block_menu);

string block_display_menu = "Display Menu";
MenuNode* Block_Display_Menu = new MenuNode(block_display_menu);

string block_search_menu = "Search Menu";
MenuNode* Block_Search_Menu = new MenuNode(block_search_menu);

string bill_menu = "Bill Management Menu";
MenuNode* Bill_Menu = new MenuNode(bill_menu);

string bill_search_menu = "Search Menu";
MenuNode* Bill_Search_Menu = new MenuNode(bill_search_menu);

string bill_delete_menu = "Delete Menu";
MenuNode* Bill_Delete_Menu = new MenuNode(bill_delete_menu);

string goods_menu = "Goods Management Menu";
MenuNode* Goods_Menu = new MenuNode(goods_menu);

string goods_display_menu = "Display Menu";
MenuNode* Goods_Display_Menu = new MenuNode(goods_display_menu);

string goods_search_menu = "Search Menu";
MenuNode* Goods_Search_Menu = new MenuNode(goods_search_menu);

void makeTree() {
	Main_Menu->addMenu(Main_Menu);
	Main_Menu->addMenu(Goods_Menu);
	Main_Menu->addMenu(Block_Menu);
	Main_Menu->addMenu(Bill_Menu);
	Main_Menu->addFunction(&mainMenu_createBill, func_main_createBill);
	Main_Menu->addFunction(&mainMenu_undo, func_main_undo);
	Main_Menu->addFunction(&mainMenu_exit, func_main_exit);
	Main_Menu->gainOption();

	Goods_Menu->addMenu(Main_Menu);
	Goods_Menu->addMenu(Goods_Display_Menu);
	Goods_Menu->addMenu(Goods_Search_Menu);
	Goods_Menu->addFunction(&goodsManagementMenu_addGoods, func_goods_add);
	Goods_Menu->addFunction(&goodsManagementMenu_changeInformation, func_goods_change);
	Goods_Menu->addFunction(&goodsManagementMenu_delete, func_goods_delete);
	Goods_Menu->addFunction(&mainMenu_exit, func_main_exit);
	Goods_Menu->gainOption();

	Goods_Display_Menu->addMenu(Main_Menu);
	Goods_Display_Menu->addFunction(&goodsManagementMenu_displayList, func_goods_displayList);
	Goods_Display_Menu->addFunction(&goodsManagementMenu_importMore, func_goods_imMore);
	Goods_Display_Menu->addFunction(&goodsManagementMenu_notImportMore, func_goods_notImMore);
	Goods_Display_Menu->addFunction(&mainMenu_exit, func_main_exit);
	Goods_Display_Menu->gainOption();

	Goods_Search_Menu->addMenu(Main_Menu);
	Goods_Search_Menu->addFunction(&goodsManagementMenu_searchID, func_goods_searchID);
	Goods_Search_Menu->addFunction(&goodsManagementMenu_searchName, func_goods_searchName);
	Goods_Search_Menu->addFunction(&mainMenu_exit, func_main_exit);
	Goods_Search_Menu->gainOption();

	Block_Menu->addMenu(Main_Menu);
	Block_Menu->addMenu(Block_Display_Menu);
	Block_Menu->addMenu(Block_Search_Menu);
	Block_Menu->addFunction(&blockManagementMenu_move, func_block_move);
	Block_Menu->addFunction(&blockManagementMenu_delete, func_block_delete);
	Block_Menu->addFunction(&mainMenu_exit, func_main_exit);
	Block_Menu->gainOption();

	Block_Display_Menu->addMenu(Main_Menu);
	Block_Display_Menu->addFunction(&blockManagementMenu_displayGeneral, func_block_displayGeneral);
	Block_Display_Menu->addFunction(&blockManagementMenu_displayEmptyBlock, func_block_displayEmptyBlock);
	Block_Display_Menu->addFunction(&blockManagementMenu_displayNonEmptyBlock, func_block_displayNonEmptyBlock);
	Block_Display_Menu->addFunction(&mainMenu_exit, func_main_exit);
	Block_Display_Menu->gainOption();

	Block_Search_Menu->addMenu(Main_Menu);
	Block_Search_Menu->addFunction(&blockManagementMenu_searchBlockID, func_block_searchBlockID);
	Block_Search_Menu->addFunction(&blockManagementMenu_searchGoodsID, func_block_searchGoodsID);
	Block_Search_Menu->addFunction(&mainMenu_exit, func_main_exit);
	Block_Search_Menu->gainOption();

	Bill_Menu->addMenu(Main_Menu);
	Bill_Menu->addMenu(Bill_Search_Menu);
	Bill_Menu->addMenu(Bill_Delete_Menu);
	Bill_Menu->addFunction(&billManagementMenu_displayList, func_bill_displayList);
	Bill_Menu->addFunction(&mainMenu_exit, func_main_exit);
	Bill_Menu->gainOption();

	Bill_Search_Menu->addMenu(Main_Menu);
	Bill_Search_Menu->addFunction(&billManagementMenu_search_ID, func_bill_searchID);
	Bill_Search_Menu->addFunction(&billManagementMenu_search_Date, func_bill_searchDate);
	Bill_Search_Menu->addFunction(&billManagementMenu_search_Type, func_bill_searchType);
	Bill_Search_Menu->addFunction(&billManagementMenu_multiSearch, func_bill_multiSearch);
	Bill_Search_Menu->addFunction(&mainMenu_exit, func_main_exit);
	Bill_Search_Menu->gainOption();

	Bill_Delete_Menu->addMenu(Main_Menu);
	Bill_Delete_Menu->addFunction(&billManagementMenu_deleteByID, func_bill_deleteID);
	Bill_Delete_Menu->addFunction(&billManagementMenu_deleteByDate, func_bill_deleteDate);
	Bill_Delete_Menu->addFunction(&mainMenu_exit, func_main_exit);
	Bill_Delete_Menu->gainOption();
}

/* ==================================== END OF: MENU TREE ==================================== */

int main()
{
	
	pre_mainMenu();

	makeTree();
	MenuNode* nowMenu = Main_Menu; // Start.

	while (1) {
		nowMenu->displayOption();
		nowMenu = nowMenu->chooseOption(nowMenu);
	}

	return 0;
}