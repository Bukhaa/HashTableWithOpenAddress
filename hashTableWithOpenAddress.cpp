#include <iostream>
#include <vector>

template<typename K, typename D>
class hashTableWithOpenAddress {
private:

	enum state {
		FREE,
		BUSY,
		DELETED
	};

	class bucket {
	public:
		std::pair<K, D> element;
		state state;
	};

public:
	hashTableWithOpenAddress(size_t size);
	K transformKeyToNumber(K key);
	K hashFunc(K key);
	void insert(std::pair<K, D> el);
	void remove(K key);
	void printTable()const;
	size_t sizeOfTable()const;
	size_t sizeOfElementsInTable()const;
	bool empty()const;
	void clear();
	D find(K key);

private:
	std::vector<bucket> table;
	size_t size;
};

template<typename K, typename D>
hashTableWithOpenAddress<K, D>::hashTableWithOpenAddress(size_t size_) {

	size = 0;
	table.resize(size_);
}

template<typename K, typename D>
K hashTableWithOpenAddress<K, D>::transformKeyToNumber(K key) {

	int resultNumber = 0;
	int factor = 1;
	while (key > 0)
	{
		int digit = key % 10;
		resultNumber += digit * factor;
		factor = factor * 10;
		key = key / 1000;
	}

	return resultNumber;
}

template<typename K, typename D>
K hashTableWithOpenAddress<K, D>::hashFunc(K key) {

	K numberForHashFunc = transformKeyToNumber(key);
	return numberForHashFunc % table.size();
}

template<typename K, typename D>
void hashTableWithOpenAddress<K, D>::insert(std::pair<K, D> el) {

	++size;
	int k = 0;
	K index = hashFunc(el.first);
	while (table[index].state == state::BUSY) {
		index = (index + 1) % table.size();
		k++;
	}

	table[index].element.second = el.second;
	table[index].element.first = el.first;
	table[index].state = state::BUSY;
}

template<typename K, typename D>
void hashTableWithOpenAddress<K, D>::remove(K key) {

	int k = 0;
	K index = hashFunc(key);
	while (table[index].state != state::FREE) {
		k += 1;
		if (table[index].element.first == key) {
			table[index].state = state::DELETED;
			table[index].element.second = 0;
			--size;
		}
		index = (index + 1) % table.size();
	}
}
template<typename K, typename D>
size_t hashTableWithOpenAddress<K, D>::sizeOfTable()const {

	return table.size();
}

template<typename K, typename D>
size_t hashTableWithOpenAddress<K, D>::sizeOfElementsInTable()const {

	return size;
}

template<typename K, typename D>
bool hashTableWithOpenAddress<K, D>::empty()const {

	return sizeOfElementsInTable() == 0;
}

template<typename K, typename D>
void hashTableWithOpenAddress<K, D>::clear() {

	for (size_t i = 0; i < table.size(); ++i) {
		if (table[i].state != state::FREE) {
			table[i].element.second = 0;
			table[i].state = state::FREE;
		}
	}
	size = 0;
}

template<typename K, typename D>
D hashTableWithOpenAddress<K, D>::find(K key) {

	int k = 0;
	int index = hashFunc(key);
	while (table[index].state != state::FREE) {
		k += 1;
		if (table[index].element.first == key) {
			k += 1;
			std::cout << "Трудоемкость при поиске: " << k << std::endl;
			return table[index].element.second;
			
		}

		index = (index + 1) % table.size();
	}

	return INT_MIN;
}

template<typename K, typename D>
void hashTableWithOpenAddress<K, D>::printTable()const {

	for (size_t i = 0; i < table.size(); ++i) {
		std::string stateItem = "";
		if (table[i].state == state::FREE)
			stateItem = "free";
		else if (table[i].state == state::BUSY)
			stateItem = "busy";
		else
			stateItem = "deleted";

		std::cout << "Индекс: " << i << " " << "Значение ключа: " << table[i].element.second << " " << "Состояние: " << stateItem << std::endl;
	}
}

template< typename D>
bool func(const std::vector<D>& v1, const std::vector<D>& v2) {

	hashTableWithOpenAddress<D,D> table(v1.size());
	for (size_t i = 0; i < v1.size(); ++i) {
		table.insert({ i,v1[i] });
	}

	size_t l = 1;
	for (size_t i = 0; i < v1.size(); ++i) {
		if (table.find(i) == v2[0]) {
			for (size_t j = i + 1; j < table.sizeOfTable(), l < v2.size(); ++j, ++l) {
				if (table.find(j) != v2[l])
					return false;
			}
			return true;
		}
	}

	return false;
}

int main()
{
	return 0;
}


