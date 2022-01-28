#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<list>

constexpr auto NUM_FLOOR = 3;
constexpr auto NUM_ROW_IN_FLOOR = 8;
constexpr auto NUM_BLOCK_IN_ROW = 10;

constexpr auto MAX_BLOCKS = NUM_FLOOR * NUM_ROW_IN_FLOOR * NUM_BLOCK_IN_ROW;

class Block {
private:
	std::string m_block_ID;
	std::string m_goods_ID;
	int m_quantity;
	int m_empty;
public:
	Block() = default;

	/* Fully information Contructor */
	Block(const std::string& block_ID,
		const std::string& goods_ID,
		const int quantity,
		const int empty) :
		m_block_ID { block_ID },
		m_goods_ID { goods_ID },
		m_quantity { quantity },
		m_empty { empty }
	{};

	/* Group of functions to set information about block. */

	void setBlockID(const std::string& ID) { m_block_ID = ID; }
	void setGoodsID(const std::string& ID) { m_goods_ID = ID; }
	void setQuantity(const int quantity) { m_quantity = quantity; }
	void setEmpty(const int empty) { m_empty = empty; }

	/* Group of functions to get information about block. */

	const std::string& getBlockID() const noexcept { return m_block_ID; }
	const std::string& getGoodsID() const noexcept { return m_goods_ID; }
	const int getQuantity() const noexcept { return m_quantity; }
	const int getEmpty() const noexcept { return m_empty; }

	/* Check if block is empty. */
	bool isEmpty() const noexcept { return (m_quantity == 0); }
	bool isFull()  const noexcept { return (m_empty == 0); }

	/* Return a string line to upload to file. */
	const std::string toFile()
	{
		std::string buffer;
		buffer += m_block_ID + " "
			+ m_goods_ID + " ";
		buffer += std::to_string(m_quantity) + " "
			+ std::to_string(m_empty);

		return std::move(buffer);
	}

	/* Return a string to display. */
	const std::string toDisplay()
	{
		std::string buffer;
		buffer += "Block ID: " + m_block_ID + "\n"
			+ "Goods ID: " + m_goods_ID + "\n"
			+ "Quantity: " + std::to_string(m_quantity) + "\n"
			+ "Empty slot: " + std::to_string(m_empty) + "\n";

		return std::move(buffer);
	}
};

class BlocksList {
private:
	std::list<Block> m_blocksList;
	unsigned int m_numberNotEmptyBlocks;
	unsigned int m_numberEmptyBlocks;
	unsigned int m_map[NUM_FLOOR + 1][NUM_ROW_IN_FLOOR + 1][NUM_BLOCK_IN_ROW + 1] = {0};
	
public:
	BlocksList() : 
		m_numberEmptyBlocks { MAX_BLOCKS },
		m_numberNotEmptyBlocks { 0 }
	{};

	/* Get list of blocks. */
	void setList(const std::list<Block> _list)
	{
		m_blocksList = _list;
	}

	/* Group of function to get information about. */

	const int getNumberNotEmptyBlocks() const noexcept { return m_blocksList.size(); }
	const int getNumberEmptyBLocks() const noexcept { return MAX_BLOCKS - m_blocksList.size(); }
	const std::list<Block>& getList() const noexcept { return m_blocksList; }

	/* Check if the list is empty or not, return true if empty. */
	bool isEmpty() { return m_blocksList.empty(); }

	/* Check if the list is full or not, return true if full. */
	bool isFull() { return (m_blocksList.size() == MAX_BLOCKS); }

	/* Mark a block is not empty in map with it's ID. */
	void markBlock(const std::string& ID)
	{
		int floor = std::stoi(ID.substr(1, 1));
		int row = std::stoi(ID.substr(3, 1));
		int block = std::stoi(ID.substr(5, 1));

		m_map[floor][row][block] = 1;
	}

	/* Mark a block is empty in map with it's ID. */
	void unmarkBlock(const std::string& ID)
	{
		int floor = std::stoi(ID.substr(1, 1));
		int row = std::stoi(ID.substr(3, 1));
		int block = std::stoi(ID.substr(5, 1));

		m_map[floor][row][block] = 0;
	}

	/* Add new block to list and map, return 0 if successful, return -1 if not. */
	int addBlock(const Block& block)
	{
		if (isFull()) return -1;
		m_blocksList.push_back(block);

		markBlock(block.getBlockID());

		return 0;
	}

	/* Delete block in list of blocks. */
	auto& delBlock(const std::string& ID)
	{
		m_blocksList.remove_if(
			[&](auto block) { return block.getBlockID() == ID; }
		);

		unmarkBlock(ID);

		return m_blocksList;
	}

	/* Searching block in list of blocks with given Block ID, return a vector of matching blocks. */
	const auto searchbyBlockID(const std::string& ID)
	{
		std::vector<Block> result;
		for (auto& block : m_blocksList) {
			std::string block_id = block.getBlockID();
			std::size_t found = block_id.find(ID);

			if (found != std::string::npos)
				result.push_back(block);
		}
		return result;
	}

	/* Searching block in list of blocks with given Goods ID, return a vector of matching blocks. */
	const auto searchbyGoodsID(const std::string& ID)
	{
		std::vector<Block> result;
		for (auto& block : m_blocksList) {
			std::string goods_id = block.getGoodsID();
			std::size_t found = goods_id.find(ID);

			if (found != std::string::npos)
				result.push_back(block);
		}
		return result;
	}

	/* Return a Block with given ID in list. */
	auto& find_byID(const std::string ID)
	{
		for (auto& block : m_blocksList) {
			if (block.getBlockID() == ID) return block;
		}
	}

	/* Check a block is empty or not with given Block ID. */
	bool checkBlockEmpty(const std::string& ID)
	{
		std::vector<Block> matching = searchbyBlockID(ID);
		return (matching.empty());
	}

	/* Check a block is full or not with given Block ID. */
	bool checkBlockFull(const std::string& ID)
	{
		auto& matching = find_byID(ID);
		return (matching.isFull());
	}

	/* Return a string to upload to file. */
	auto toFile()
	{
		std::string buffer;
		buffer += std::to_string(getNumberNotEmptyBlocks()) + "\n";
		for (auto& block : m_blocksList) {
			buffer += block.toFile() + "\n";
		}
		return std::move(buffer);
	}

	/* Replace one block by another one. */
	void replaceBlock(const std::string& ID, const Block& replaceBlock)
	{
		for (auto& block : m_blocksList) {
			if (block.getBlockID() == ID) {
				block = replaceBlock;

				unmarkBlock(ID);
				markBlock(replaceBlock.getBlockID());

				return;
			}
		}
		return;
	}

	/* Return a 2-dimensional vector to display nonempty blocks. */
	auto displayNonEmptyBlocks()
	{
		std::vector<std::vector<std::string>> result;
		std::vector<std::string> row;
		unsigned int row_num = 0;

		for (auto& block : m_blocksList)
		{
			row.clear();
			row.push_back(std::to_string(++row_num));
			row.push_back(block.getBlockID());
			row.push_back(block.getGoodsID());
			row.push_back(std::to_string(block.getQuantity()));
			row.push_back(std::to_string(block.getEmpty()));

			result.push_back(std::move(row));
		}
		return result;
	}

	/* Return a string to display empty block. */
	auto displayEmptyBlocks()
	{
		std::string result;

		for (int floor = 1; floor <= NUM_FLOOR; floor++) {
			result += "Floor " + std::to_string(floor) + ":\n";

			for (int row = 1; row <= NUM_ROW_IN_FLOOR; row++) {
				result += "Row " + std::to_string(row) + ": ";

				for (int block = 1; block <= NUM_BLOCK_IN_ROW; block++) {

					if (m_map[floor][row][block] == 0) {
						result += "F" + std::to_string(floor)
							+ "R" + std::to_string(row)
							+ "B" + std::to_string(block)
							+ " ";
					}
				}
				result += "\n";
			}
			result += "\n";
		}
		return std::move(result);
	}

	/* Return a string with General information. */
	auto displayGeneralInfor()
	{
		std::string result;
		result += "Number of floors of the warehouse: " + std::to_string(NUM_FLOOR) + "\n"
			+ "Number of rows at each floor: " + std::to_string(NUM_ROW_IN_FLOOR) + "\n"
			+ "Number of blocks at each row: " + std::to_string(NUM_BLOCK_IN_ROW) + "\n"
			+ "Total blocks is the warehouse: " + std::to_string(MAX_BLOCKS) + "\n"
			+ "Number of empty block: " + std::to_string(getNumberEmptyBLocks()) + "\n"
			+ "Number of nonempty block: " + std::to_string(getNumberNotEmptyBlocks()) + "\n";
		return std::move(result);
	}
};
