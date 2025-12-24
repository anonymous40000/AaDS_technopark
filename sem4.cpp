#include<vector>
#include<iostream>
#include<cassert>
#include<string>

const size_t InitSize = 8;

template<typename T, typename H>
class HashTable {
public:
	HashTable(H _hasher);
	~HashTable();

	// WithKey: key == cell.Key ? return false : пробируемся дальше
	// Delete: пробируемся дальше / запоминаем firstDeletedIndex (если это первый Deleted)
	// Empty: пишем ключ + ставим WithKey + return true / проверяем firstDeletedIndex и пишем туда(если встречали) + пишем ключ + ставим WithKey + return true
	bool AddKey(const T& key);
	// WithKey: key == cell.Key ? пометить Deleted + return true : пробируемся дальше
	// Delete: пробируемся дальше
	// Empty: return false
	bool DeleteKey(const T& key);
	// WithKey: key == cell.Key ? return true : пробируемся дальше
	// Delete: пробируемся дальше
	// Empty: return false
	bool HasKey(const T& key) const;

private:
	// Открытая адресация
	// 	struct HashTableCell {
	//		T Key;
	//		size_t Hash = 0;
	//		CellState = Empty; // Deleted / WithKey
	//	}
	// 
	// std::vector<HashTableNode>


	struct HashTableNode {
		T Key;
		size_t Hash = 0;
		HashTableNode* Next = nullptr;
	};

	H hasher;
	std::vector<HashTableNode*> table;
	size_t keysCount;

	void growTable();
};

template<typename T, typename H>
HashTable<T, H>::HashTable(H _hasher) :
	hasher(_hasher),
	table(InitSize, nullptr),
	keysCount(0)
{
}

template<typename T, typename H>
HashTable<T, H>::~HashTable()
{
	for (int i = 0; i < table.size(); ++i) {
		HashTableNode* node = table[i];
		while (node != nullptr) {
			HashTableNode* nodeToDelete = node;
			node = node->Next;
			delete nodeToDelete;
		}
	}
}

template<typename T, typename H>
bool HashTable<T, H>::AddKey(const T& key)
{
	if (keysCount > 3 * table.size()) {
		growTable();
	}

//	if (Has(key)) { -- так дорого
//		return false;
//	}

	size_t hash = hasher(key);
	size_t listIndex = hash % table.size();
	HashTableNode* node = table[listIndex];
	while (node != nullptr && node->Key != key) {
		node = node->Next;
	}

	if (node != nullptr) {
		return false;
	}

	HashTableNode* newNode = new HashTableNode();
	newNode->Key = key;
	newNode->Hash = hash;
	newNode->Next = table[listIndex];
	table[listIndex] = newNode;

	++keysCount;
	return true;
}

template<typename T, typename H>
bool HashTable<T, H>::DeleteKey(const T& key)
{
	size_t hash = hasher(key);
	size_t listIndex = hash % table.size();
	HashTableNode* node = table[listIndex];
	HashTableNode* prevNode = nullptr;
	while (node != nullptr && node->Key != key) {
		prevNode = node;
		node = node->Next;
	}

	if (node == nullptr) {
		return false;
	}

	if (prevNode == nullptr) {
		table[listIndex] = node->Next;
	}
	else {
		prevNode->Next = node->Next;
	}

	--keysCount;
	delete node;
	return true;
}

// node1 -> node2 -> node3

template<typename T, typename H>
bool HashTable<T, H>::HasKey(const T& key) const
{
	size_t hash = hasher(key);
	size_t listIndex = hash % table.size();
	HashTableNode* node = table[listIndex];
	while (node != nullptr && node->Key != key) {
		node = node->Next;
	}

	return node != nullptr;
}

template<typename T, typename H>
void HashTable<T, H>::growTable()
{
	std::vector<HashTableNode*> newTable(table.size() * 2, nullptr);
	for (int i = 0; i < table.size(); ++i) {
		HashTableNode* node = table[i];
		while (node != nullptr) {
			HashTableNode* nextNode = node->Next;

			size_t listIndex = node->Hash % newTable.size();
			node->Next = newTable[listIndex];
			newTable[listIndex] = node;

			node = nextNode;
		}
	}
	table = std::move(newTable);
}

struct StringHasher {
	StringHasher(size_t _p) : p(_p) {}
	size_t operator()(const std::string& key) const {
		size_t hash = 0;
		for (const char& c : key) {
			hash = hash * p + c;
		}
		return hash;
	}
private:
	size_t p;
};


int main()
{
	StringHasher hasher(137);
	HashTable<std::string, StringHasher> table(hasher);
	char op = 0;
	std::string word;
	while (std::cin >> op >> word) {
		switch (op) {
		case '+':
			std::cout << (table.AddKey(word) ? "OK" : "FAIL") << std::endl;
			break;
		case '-':
			std::cout << (table.DeleteKey(word) ? "OK" : "FAIL") << std::endl;
			break;
		case '?':
			std::cout << (table.HasKey(word) ? "OK" : "FAIL") << std::endl;
			break;
		}
	}

	return 0;
}