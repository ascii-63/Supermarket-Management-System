#pragma once

#include<iostream>
#include<list>
#include<set>
#include<vector>
#include<string>

constexpr auto MAX_BILLS = 100;
constexpr auto MAX_ID = 9999999999;
constexpr auto MIN_ID = 1000000000;

class Bill {
private:
	std::string m_ID;
	std::string m_date;
	std::string m_type;
	unsigned int m_numberOfGoods;
	std::vector<std::vector<std::string>> m_singleBill;
public:
	Bill() = default;

	/* Simple information Constructor. */
	Bill(const std::string& ID,
		const std::string& date,
		const std::string& type,
		const unsigned int numberOfGoods) :
		m_ID{ ID },
		m_date{ date },
		m_type{ type },
		m_numberOfGoods{ numberOfGoods }
	{};

	/* Full information constructor. */
	Bill(const std::string& ID,
		const std::string& date,
		const std::string& type,
		const unsigned int numberOfGoods,
		const std::vector<std::vector<std::string>> singleBill) :
		m_ID{ ID },
		m_date{ date },
		m_type{ type },
		m_numberOfGoods{ numberOfGoods }
	{
		for (auto& row : singleBill) {
			std::vector<std::string> line;
			for (auto& temp : row) {
				line.push_back(temp);
			}
			m_singleBill.push_back(line);
		}
	}

	/* Group of function to change information of bill. */

	void setID(const std::string& id) { m_ID = id; }
	void setDate(const std::string& date) { m_date = date; }
	void setType(const std::string& type) { m_type = type; }
	void setSingleBill(const std::vector<std::vector<std::string>> singleBill) {
		m_singleBill = singleBill;
	}

	/* Group of function to get information of bill. */

	const std::string getID() const noexcept { return m_ID; }
	const std::string getDate() const noexcept { return m_date; }
	const std::string getType() const noexcept { return m_type; }
	const unsigned int getNumberOfGoods() const noexcept
	{
		return m_singleBill.size();
	}

	const std::vector<std::vector<std::string>> getSingleBill() const noexcept {
		return m_singleBill;
	}

	/* Return a string to upload to file. */
	const std::string toFile()
	{
		std::string buffer;
		buffer += m_ID + " "
			+ m_date + " "
			+ m_type + " "
			+ std::to_string(m_numberOfGoods) + "\n";

		for (auto& row : m_singleBill) {
			for (auto& temp : row) {
				buffer += temp + " ";
			}
			buffer.pop_back(); buffer.push_back('\n');
		}

		buffer.pop_back();

		return std::move(buffer);
	}
};

class BillsList {
private:
	unsigned int m_numberOfBills;
	std::list<Bill> m_billsList;
public:
	BillsList() = default;

	/* Constructor with number of bills. */
	BillsList(const unsigned numberOfBills) : m_numberOfBills{ numberOfBills } {};
    
	/* Check if the list is full or not, return true if full. */
	bool isFull() { return (m_billsList.size() == MAX_BILLS); }

	/* Check if the list if empty ot not, return true if empty. */
	bool isEmpty() { return m_billsList.empty(); }

	/* Group of function to get information. */

	const int getNumberOfBills() const noexcept
	{
		return m_billsList.size();
	}
	const std::list<Bill>& getList() const noexcept { return m_billsList; }

	/* Set list of bills. */
	void setList(const std::list<Bill>& list) { m_billsList = list; }

	/* Add new bill, return 0 if susccesful, return -1 if not. */
	int addBill(const Bill& bill)
	{
		if (isFull()) return -1;
		m_billsList.push_back(bill);
		return 0;
	}

	/* Delete the Bill in list with given ID. */
	auto& delByID(const std::string& ID)
	{
		if (isEmpty()) return m_billsList;

		m_billsList.remove_if(
			[&](auto bill) { return bill.getID() == ID; }
		);
		return m_billsList;
	}

	/* Delete the Bill in list with given date. */
	auto& delByDate(const std::string& date)
	{
		if (isEmpty()) return m_billsList;

		m_billsList.remove_if(
			[&](auto bill) { return bill.getDate() == date; }
		);
		return m_billsList;
	}

	/* Search for all Bill with given ID, return in vector. */
	const auto searchbyID(const std::string& ID)
	{
		std::vector<Bill> result;
		for (auto& bill : m_billsList) {
			std::string bill_ID = bill.getID();
			std::size_t found = bill_ID.find(ID);

			if (found != std::string::npos)
				result.push_back(bill);
		};
		return result;
	}

	/* Search for all Bill with given date, return in vector. */
	const auto searchbyDate(const std::string& date)
	{
		std::vector<Bill> result;
		for (auto& bill : m_billsList) {
			std::string bill_date = bill.getDate();
			std::size_t found = bill_date.find(date);

			if (found != std::string::npos)
				result.push_back(bill);
		};
		return result;
	}

	/* Search for all Bill with given type, return in vector. */
	const auto searchbyType(const std::string& type)
	{
		std::vector<Bill> result;
		for (auto& bill : m_billsList) {
			std::string bill_type = bill.getType();
			std::size_t found = bill_type.find(type);

			if (found != std::string::npos)
				result.push_back(bill);
		};
		return result;
	}

	/* Multi-search with type and date, return in vector. */
	const auto multi_search(const std::string& type, const std::string& date)
	{
		std::vector<Bill> result_type = searchbyType(type);
		std::vector<Bill> result_date = searchbyDate(date);
		std::vector<Bill> result;

		for (auto& bill : result_type) {
			bool check = true;
			for (auto& temp : result) {
				if (temp.getID() == bill.getID())
					check = false;
			}
			if (check) result.push_back(bill);
			
		}

		for (auto& bill : result_date) {
			bool check = true;
			for (auto& temp : result) {
				if (temp.getID() == bill.getID())
					check = false;
			}
			if (check) result.push_back(bill);
		}

		return result;
	}

	/* Return a string to upload to file. */
	const std::string toFile()
	{
		std::string buffer;
		buffer += std::to_string(getNumberOfBills()) + "\n";
		for (auto& bill : m_billsList) {
			buffer += bill.toFile() + "\n";
			//std::cout << bill.toFile() + "\n";
		}
		return std::move(buffer);
	}
};