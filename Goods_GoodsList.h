#pragma once

#include<iostream>
#include<list>
#include<vector>
#include<string>

class Goods {
private:
	std::string m_ID;
	std::string m_name;
	std::string m_unit;
	unsigned int m_importPrice;
	unsigned int m_exportPrice;
	int m_quantity;

	std::list<std::string> m_locations;
	int m_lowerLimit;
	int m_upperLimit;
	int m_maxUnitsPerBlock;
public:
	Goods() = default;

	/* Fully information Contructor */
	Goods(const std::string& ID,
		const std::string& name,
		const std::string& unit,
		const unsigned int importPrice,
		const unsigned int exportPrice,
		const int quantity,
		const int lowerLimit = -1,
		const int upperLimit = -1,
		const int maxUnitsPerBlock = -1,
		const std::list<std::string>&locations = {}) :
		m_ID { ID },
		m_name { name },
		m_unit { unit },
		m_importPrice { importPrice },
		m_exportPrice { exportPrice },
		m_quantity { quantity },
		m_lowerLimit { lowerLimit },
		m_upperLimit { upperLimit },
		m_maxUnitsPerBlock { maxUnitsPerBlock },
		m_locations { locations }
	{};

	Goods(const std::string& ID,
		const std::string& name,
		const std::string& unit,
		const unsigned int importPrice,
		const unsigned int exportPrice,
		const int quantity = -1,
		const int lowerLimit = -1,
		const int upperLimit = -1,
		const int maxUnitsPerBlock = -1,
		const std::string& locationString = {}) :
		m_ID{ ID },
		m_name{ name },
		m_unit{ unit },
		m_importPrice{ importPrice },
		m_exportPrice{ exportPrice },
		m_quantity{ quantity },
		m_lowerLimit{ lowerLimit },
		m_upperLimit{ upperLimit },
		m_maxUnitsPerBlock{ maxUnitsPerBlock }
	{
		// Convert from std::string representation to a list of locations.
		std::string locString{ locationString };
		if (locString.size() < 6)
			return;
		int locCount = (locString.size() + 1) / 6;
		for (int i = 0; i < locCount; i++) {
			m_locations.push_back(locString.substr(7 * i, 6));
		}
	};
	/* Group of functions to get information about goods. */
	
	const std::string& getID()   const noexcept { return m_ID; }
	const std::string& getName() const noexcept { return m_name; }
	const std::string& getUnit() const noexcept { return m_unit; }
	const unsigned int getImportPrice() const noexcept { return m_importPrice; }
	const unsigned int getExportPrice() const noexcept { return m_exportPrice; }
	const int getQuantity()   const noexcept { return m_quantity; }
	const int getUpperLimit() const noexcept { return m_upperLimit; }
	const int getlowerLimit() const noexcept { return m_lowerLimit; }
	const int getMaxUnitsInOneBLock() const noexcept {
		return m_maxUnitsPerBlock;
	}
	const std::list<std::string>& getLocations() const noexcept { return m_locations; }

	/* Return a human-readable string with simple information about goods. */
	const std::string getSimpleInfo() const
	{
		std::string toString;
		toString += "ID:   " + m_ID + "\n";
		toString += "Name: " + m_name + "\n";
		toString += "Import Price: " + std::to_string(m_importPrice) + "\n";
		toString += "Export Price: " + std::to_string(m_exportPrice) + "\n";
		toString += "Quantity: " + std::to_string(m_quantity) + " " + m_unit
			+ ((m_quantity == 0 || m_quantity == 1) ? "\n" : "s\n");

		return std::move(toString);
	}

	/* Return a human-readable string with detailed information about goods.*/
	const std::string getDetailedInfo() const
	{
		std::string toString;
		toString = getSimpleInfo();
		toString += "Location:\n";
		for (auto& loc : m_locations) {
			toString += "  Floor ";
			toString += loc[1];
			toString += ", Row ";
			toString += loc[3];
			toString += ", Block number ";
			toString += loc[5];
			toString += "\n";
		}
		toString += "Upper limit: " + std::to_string(m_upperLimit) + "\n";
		toString += "Lower limit: " + std::to_string(m_lowerLimit) + "\n";
		toString += "Maximum goods in one block of warehouse: "
			+ std::to_string(m_maxUnitsPerBlock) + "\n";

		return std::move(toString);
	}
	/* Group of functions to set information about goods. */

	void setID(const std::string & ID) { m_ID = ID; }
	void setName(const std::string & name) { m_name = name; }
	void setUnit(const std::string & unit) { m_unit = unit; }
	void setImportPrice(const unsigned int importPrice) {
		m_importPrice = importPrice;
	}
	void setExportPrice(const unsigned int exportPrice) {
		m_exportPrice = exportPrice;
	}
	void setQuantity(const unsigned int quantity) { m_quantity = quantity; }
	void setLocation(const std::list<std::string>&locations) {
		m_locations = locations;
	}
	void setLowerLimit(int lowerLimit) { m_lowerLimit = lowerLimit; }
	void setUpperLimit(int upperLimit) { m_upperLimit = upperLimit; }
	void setMaxUnits(int maxUnits) { m_maxUnitsPerBlock = maxUnits; }

	/* If string member is not change, input #;
	   if number member is not change, input -1;
	   with list member, if not change, input list with list.size() = 0 */
	void changeInfo(const std::string & name,
		const int importPrice,
		const int exportPrice,
		const std::list<std::string>&locations,
		const int lowerLimit,
		const int upperLimit)
	{
		if (name.compare("#") != 0) setName(name);
		if (importPrice != -1) setImportPrice(importPrice);
		if (exportPrice != -1) setExportPrice(exportPrice);
		if (locations.size() != 0) setLocation(locations);
		if (lowerLimit != -1) setLowerLimit(lowerLimit);
		if (upperLimit != -1) setUpperLimit(upperLimit);
	}

	/* Check goods is empty or not, retun true if empty. */
	bool isEmpty() const noexcept { return (m_quantity == 0); }

	/* Check if goods quantity is less than lower limit, return true if it does. */
	bool isLower() const noexcept { return (m_quantity < m_lowerLimit); }

	/* Check if goods quantity is more than upper limit, return true if it does. */
	bool isUpper() const noexcept { return (m_quantity > m_upperLimit); }

	/* Return a string line to upload to file. */
	const std::string toFile()
	{
		std::string buffer;
		buffer += m_ID + " "
			+ m_name + " "
			+ m_unit + " ";
		buffer += std::to_string(m_importPrice) + " "
			+ std::to_string(m_exportPrice) + " "
			+ std::to_string(m_quantity) + " "
			+ std::to_string(m_lowerLimit) + " "
			+ std::to_string(m_upperLimit) + " "
			+ std::to_string(m_maxUnitsPerBlock) + " ";

		for (auto& it : m_locations)
			buffer += it + "_";

		buffer.pop_back();

		return std::move(buffer);
	}
};

class GoodsList {
private:
	std::list<Goods> m_goodsList;
	unsigned int m_capacity;
public:
	GoodsList() = default;

	/* Contructor with capacity */
	GoodsList(const unsigned capacity) : m_capacity{ capacity } {};

	/* Group of function to set information about. */

	void setQuantity(const unsigned int quantity) { /*deprecated*/ }
	void setCapacity(const unsigned int capacity) { m_capacity = capacity; }
	void setList(const std::list<Goods>& list) { m_goodsList = list; }

	/* Group of function to get information about. */

	const int getQuantity() const noexcept { return m_goodsList.size(); }
	const int getCapacity() const noexcept { return m_capacity; }
	const std::list<Goods>& getList() const noexcept { return m_goodsList; }

	/* Check if the list is empty or not, return true if empty. */
	bool isEmpty() { return m_goodsList.empty(); }

	/* Check if the list is full or not, return true if full. */
	bool isFull() { return (m_goodsList.size() == m_capacity); }

	// Add new goods to the list, return 0 if successfull, return -1 if not.
	int addGoods(const Goods& goods)
	{
		if (isFull()) return -1;
		m_goodsList.push_back(goods);
		return 0;
	}

	// Delete the goods with given ID, return the list after delete (or original list if no matching ID).
	auto& delByID(const std::string& ID)
	{
		m_goodsList.remove_if(
			[&](auto goods) { return goods.getID() == ID; }
		);
		return m_goodsList;
	}

	// Delete the goods with given name, return the list after delete (or original list if no matching name).
	auto& delByName(const std::string& name)
	{
		m_goodsList.remove_if(
			[&](auto goods) { return goods.getName() == name; }
		);
		return m_goodsList;
	}

	// Searching goods in the list by given ID, return a vector with matching goods.
	const auto searchbyID(const std::string& ID)
	{
		std::vector<Goods> result;
		for (auto& goods : m_goodsList) {
			std::string goods_id = goods.getID();
			std::size_t found = goods_id.find(ID);

			if (found != std::string::npos)
				result.push_back(goods);
		};
		return result;
	}

	// Searching goods in the list by given name, return a vector with matching goods.
	const auto searchbyName(const std::string& name)
	{
		std::vector<Goods> result;
		for (auto& goods : m_goodsList) {
			std::string goods_name = goods.getName();
			std::size_t found = goods_name.find(name);

			if (found != std::string::npos)
				result.push_back(goods);
		};
		return result;
	}

	/* Return a Goods with given ID in list. */
	auto& find_byID(const std::string& ID)
	{
		for (auto& goods : m_goodsList) {
			if (goods.getID() == ID) return goods;
		};
	}

	/* Return a string to upload to file. */
	auto toFile()
	{
		std::string buffer;
		buffer += std::to_string(getQuantity()) + "\n";
		for (auto& goods : m_goodsList) {
			buffer += goods.toFile() + "\n";
		}
		return std::move(buffer);
	}

	/* Replace 1 goods by another one. */
	void replaceGoods(const std::string& ID, const Goods& replaceGoods)
	{
		for (auto& goods : m_goodsList) {
			if (goods.getID() == ID) {
				goods = replaceGoods;
				return;
			}
		}
		return;
	}

	/* Return a vector with goods need to import more. */
	auto importMore()
	{
		std::vector<Goods> result;
		for (auto& goods : m_goodsList) {
			if (goods.isLower()) result.push_back(goods);
		}
		return result;
	}

	/* Return a vector with goods don't need to import more. */
	auto notImportMore()
	{
		std::vector<Goods> result;
		for (auto& goods : m_goodsList) {
			if (goods.isUpper()) result.push_back(goods);
		}
		return result;
	}

	/* Return a 2-dimensional vector to display list of goods. */
	auto displayList()
	{
		std::vector<std::vector<std::string>> result;
		std::vector<std::string> row;
		std::string buffer;
		unsigned int row_num = 0;

		for (auto& goods : m_goodsList)
		{
			row.clear();
			row.push_back(std::to_string(++row_num));
			row.push_back(goods.getID());
			row.push_back(goods.getName());
			row.push_back(std::to_string(goods.getQuantity()));
			row.push_back(goods.getUnit());
			row.push_back(std::to_string(goods.getImportPrice()));
			row.push_back(std::to_string(goods.getExportPrice()));

			buffer.clear();
			auto &locations = goods.getLocations();
			for (auto& loc : locations)
				buffer += loc + " ";
			buffer.pop_back();
			row.push_back(buffer);

			result.push_back(row);
		}
		return result;
	}
};
