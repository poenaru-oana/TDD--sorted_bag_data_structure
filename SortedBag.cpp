#include "SortedBag.h"
#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r) {
	this->capacity = 10;
	this->bag = new TComp[capacity];
	this->current_size = 0;
	this->relation = r;
}


//complexity: O(n/2 + log(2)n) 
void SortedBag::add(TComp e) {
	//resize
	if (current_size + 1 == capacity) {
		capacity *= 2;
		TComp* temp = new TComp[capacity];
		for (int i = 0; i < current_size; i++)
			temp[i] = bag[i];
		delete[] bag;
		bag = temp;
	}

	//find position for insert
	int l = 0, r = current_size - 1, mid;
	while (l <= r) {
		mid = (l + r) / 2;

		if (relation(e, bag[mid]))
			r = mid - 1;
		else
			l = mid + 1;
	}
	mid = r + 1;

	//insert
	for (int i = current_size; i > mid; i--)
		bag[i] = bag[i - 1];
	bag[mid] = e;
	current_size ++;
}


//complexity: O(n/2 + log(2)n)
bool SortedBag::remove(TComp e) {
	bool Found = false;
	int l = 0, r = current_size - 1, mid;
	while (l <= r) {
		mid = (l + r) / 2;

		if (e == bag[mid]) {
			Found = true;
			break;
		}
		else
			if (relation(e, bag[mid]))
				r = mid - 1;
			else
				l = mid + 1;
	}

	if (Found) {
		for (int i = mid; i < current_size-1; i++)
			bag[i] = bag[i + 1];
		bag[current_size-1] = 0;
		current_size --;
	}

	return Found;
}


//complexity: O(log(2)n)
bool SortedBag::search(TComp elem) const {
	int l = 0, r = current_size - 1, mid;
	while (l <= r) {
		mid = (l + r) / 2;

		if (elem == bag[mid])
			return true;
		else
		if (relation(elem, bag[mid]))
			r = mid - 1;
		else
			l = mid + 1;
	}
	return false;
}


//complexity: O(n)
int SortedBag::nrOccurrences(TComp elem) const {
	int counter = 0;
	for (int i = 0; i < current_size; i++)
		if (bag[i] == elem)
			counter ++;

	return counter;
}


//complexity: O(1)
int SortedBag::size() const {
	return current_size;
}


//complexity: O(1)
bool SortedBag::isEmpty() const {
	return (current_size == 0);
}


//complexity: O(1)
SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}


//complexity: O(1)
SortedBag::~SortedBag() {
	delete[] bag;
}


void SortedBag::intersection(const SortedBag& b) {
	bool Found = 0;
	int lastThisIndex = 0;
	int lastBIndex = 0;

	while (lastThisIndex < this->current_size || lastBIndex < b.current_size)
		if (this->bag[lastThisIndex] < b.bag[lastBIndex]) {
			this->remove(this->bag[lastThisIndex]);
			lastThisIndex++;
		}
		else if (this->bag[lastThisIndex] > b.bag[lastBIndex])
			lastBIndex++;
		else
			lastThisIndex++; lastBIndex++;
}