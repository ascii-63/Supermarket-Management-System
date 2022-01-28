#pragma once

#include<iostream>
#include<string>
#include<vector>

typedef void(*fnc_ptr)();

/* Clear screen. */
void clrscr() { system("cls"); }//std::cout << "\033[2J\033[1;1H"

class MenuNode {
public:
	std::string lable;

	unsigned int number_subMenu;
	unsigned int number_function;
	unsigned int number_option;

	std::vector<MenuNode*> subMenu;

	std::vector<std::string> function_name;
	std::vector<fnc_ptr> function_pointer;

	std::vector<std::string> option;

public:
	MenuNode() = default;
	MenuNode(const std::string& new_lable) : lable{ new_lable } {};

	void addMenu(MenuNode* new_menuNode)
	{
		subMenu.push_back(new_menuNode);
		number_subMenu++; number_option++;
	}

	void addFunction(fnc_ptr _function, const std::string& new_function)
	{
		function_name.push_back(new_function);
		function_pointer.push_back(_function);
		number_function++; number_option++;
	}

	void gainOption()
	{
		for (int i = 0; i < subMenu.size(); i++) { option.push_back(subMenu[i]->lable); }

		for (int i = 0; i < function_name.size(); i++) { option.push_back(function_name[i]); }
	}

	void displayOption()
	{
		std::cout << std::endl;
		std::cout << ">...     " << lable << "     ...<" << std::endl;
		int index = 0;
		if (lable == "Main Menu") index = 1;
		for (index; index < number_option; index++) { std::cout << index << ". " << option[index] << std::endl; }
	}

	MenuNode* directMenu(const int index) { return subMenu[index]; }

	void doFunction(const int index)
	{
		std::cout << ">... " << function_name[index] << std::endl;
		(*function_pointer[index])();
	}

	MenuNode* chooseOption(MenuNode* now)
	{
		std::cout << "\n>... Chose option: ";
		int opt;
		std::cin >> opt;

		if (opt < now->number_subMenu) {
			clrscr();
			return now->directMenu(opt);
		}
		else {
			clrscr();
			now->doFunction(opt - now->number_subMenu);
			return now;
		}
	}
};