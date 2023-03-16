#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

//complexity: O(1)
SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	index = 0;
}


//complexity: O(1)
TComp SortedBagIterator::getCurrent() {
	if (index < bag.current_size)
		return bag.bag[index];

	throw exception();
}


//complexity: O(1)
bool SortedBagIterator::valid() {
	return (index < bag.current_size);
}


//complexity: O(1)
void SortedBagIterator::next() {
	if (index >= bag.current_size)
		throw exception();
	index ++;
}


//complexity: O(1)
void SortedBagIterator::first() {
	index = 0;
}

