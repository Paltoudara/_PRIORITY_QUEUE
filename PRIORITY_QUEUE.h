//Note that the heap order we want is for every position k to be  greater or equal to it's childern 2k+1 and 2k+2 and less or equal to its parent (k-1)/2
#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
#include<type_traits>
#include<cstdlib>
#include<functional>
#include<utility>
#include"Macros.h"
_PANAGIOTIS_BEGIN
//-----------------------
//		INTERFACE BEGIN
//-----------------------
// template class taking one argument the type and one the comparator which also takes a default value
template<class _Ty, class Compare = std::less<_Ty>>
class priority_queue final {
private:
	//private members,the vector maintains the heap order 
	std::vector<_Ty>_heap{};
	Compare _comp{};
	//
	//sink function done
	//this function  takes an element from the heap and moves it deep down to  heap,if the comparator func is true for its two kinds  
	void sink(std::size_t k)
	{
		//in simple terms when the comparator is operator < the element is moved down if it is less than at least one of its childern _heap[2*k+1] and _heap[2*k+2]
		//and it makes sure that the element is sinked where the largest childer is.
		//Note that the compare function should be a function that takes two 
		//const _Ty& args and returns a bool,or else the behavior is 
		//undefined
		//also the _Ty must be swappable
		while (2 * k + 1 < _heap.size()) {
			std::size_t j{ 2 * k + 1 };
			if (j + 1 < _heap.size() && _comp(
				std::as_const(_heap[j]), std::as_const(_heap[j + 1])))j++;
			if (!_comp(std::as_const(_heap[k]), std::as_const(_heap[j])))break;
			std::swap(_heap[k], _heap[j]);
			k = j;
		}
	}
	//swim func done
	void swim(std::size_t k)
	{
		//in simple terms when the comparator is operator < the element is moved up to the heap if it is bigger than its parent _heap[(k-1)/2]
		//Note that the compare function should be a function that takes two 
		//const _Ty& args and returns a bool,or else the behavior is 
		//undefined
		//also the _Ty must be swappable
		while (k > 0 && _comp(std::as_const(_heap[(k - 1) / 2]),
			std::as_const(_heap[k]))) {
			std::swap(_heap[(k - 1) / 2], _heap[k]);
			k = (k - 1) / 2;
		}
	}
public:
	//default constructor done
	//pretty much is the default state of the priorityqueue
	priority_queue() = default;
	
	explicit priority_queue(const Compare& comp)
		noexcept(std::is_nothrow_copy_constructible_v<Compare>);
	
	priority_queue(const Compare& comp, const std::vector<_Ty>& heap);
	
	priority_queue(const Compare& comp, std::vector<_Ty>&& heap);
	
	priority_queue(const priority_queue<_Ty, Compare>& other);
	
	priority_queue(priority_queue<_Ty, Compare>&& other)
		noexcept(std::is_nothrow_move_constructible_v<Compare>);
	
	bool empty()const noexcept;
	
	std::size_t size()const noexcept;
	
	const _Ty& top()const noexcept(noexcept(_heap.front()));
	
	void push(const _Ty& val);
	
	void push(_Ty&& val);
	 
	template<class ..._Valty>
	void emplace(_Valty&&..._Val);
	
	void pop();
	
	void swap(priority_queue<_Ty, Compare>& other)
		noexcept(std::is_nothrow_swappable_v<Compare>&&
			std::is_nothrow_swappable_v<std::vector<_Ty>>);
	
	priority_queue<_Ty, Compare>& operator=(const priority_queue<_Ty, Compare>& other)&;
	
	priority_queue<_Ty, Compare>& operator=(priority_queue<_Ty, Compare>&& other)
		& noexcept(std::is_nothrow_move_assignable_v<Compare>
			&& std::is_nothrow_move_assignable_v<std::vector<_Ty>>);
	//destructor ,deallocates the heap
	~priority_queue() = default;
	
	void show()const;
};

//-----------------------
//		INTERFACE END
//-----------------------

//-----------------------
//		IMPLEMENTATION BEGIN
//-----------------------

//comparator constructor done
//pretty much it initializes the _heap in the default state and copies the comp argument
template<class _Ty,class Compare>
priority_queue<_Ty, Compare>::priority_queue(const Compare& comp) noexcept(std::is_nothrow_copy_constructible_v<Compare>)
	:_heap{}, _comp{ comp }
{}
//constructor with comp& and heap& done
//pretty much it copies the heap argument and the comp argument
template<class _Ty,class Compare>
priority_queue<_Ty,Compare>::priority_queue(const Compare& comp, const std::vector<_Ty>& heap)
	:_comp{ comp }, _heap{ heap }
{
	//if all goes good we make heap.
	//Note that now we must heapify the heap that was given to use in order to create that heap order,for this we use the sink function.
	//If the func sink throws we are in partially modified or not heap
	//If the func sink succeeds we have the heap order that we want 
	//call the func sink to create the heap order
	for (long long k = static_cast<long long>(_heap.size() / 2 - 1); k >= 0; k--) {
		sink(k);
	}
}
//constructor with &comp and &&heap done
//same as the constructor up but this team we move heap to _heap and leave heap argument in valid but unspecified state
template<class _Ty,class Compare>
priority_queue<_Ty,Compare>::priority_queue(const Compare& comp, std::vector<_Ty>&& heap)
	:_comp{ comp }, _heap{ std::move(heap) }
{
	//if all goes good we make heap.
	//Note that now we must heapify the heap that was given to us in order to create that heap order,for this we use the sink function.
	//If the func sink throws we are in partially modified or not heap
	//If the func sink succeeds we have the heap order that we want 
	//call the func sink to create the heap order
	for (long long k = static_cast<long long>(_heap.size() / 2 - 1); k >= 0; k--) {
		sink(k);
	}
}
//copy constructor done
//we take a copy of the state of the other priority queue as it is
template<class _Ty,class Compare>
priority_queue<_Ty,Compare>::priority_queue(const priority_queue<_Ty, Compare>& other)
	:_comp{ other._comp }, _heap{ other._heap } {
}
//move constructor done
//we steal the resourses of the other priority queue and keep it as it is.
//Note that the other priority queue is left in valid but unspecified state.
template<class _Ty,class Compare>
priority_queue<_Ty,Compare>::priority_queue(priority_queue<_Ty, Compare>&& other)
noexcept(std::is_nothrow_move_constructible_v<Compare>)
	:_comp{ std::move(other._comp) }, _heap{ std::move(other._heap) } {
}
//checks if the heap is empty
template<class _Ty, class Compare>
bool priority_queue<_Ty, Compare>::empty()const noexcept {
	return _heap.empty();
}
//the size of the heap
template<class _Ty, class Compare>
std::size_t priority_queue<_Ty, Compare>::size()const noexcept {
	return _heap.size();
}
//the first element of the heap
template<class _Ty, class Compare>
const _Ty& priority_queue<_Ty, Compare>::top()const noexcept(noexcept(_heap.front())) {
	return _heap.front();
}
//pushes and element at the end of the heap and it makes it go up in the heap if it is bigger than its parent _heap[(k-1)/2]
template<class _Ty, class Compare>
void priority_queue<_Ty, Compare>::push(const _Ty& val) {
	_heap.push_back(val);//copy val
	swim(_heap.size() - 1);//safe because _heap.size()>=1
}
//same case as push(const _Ty&val)
template<class _Ty, class Compare>
void priority_queue<_Ty, Compare>::push(_Ty&& val) {
	_heap.push_back(std::move(val));//move val
	swim(_heap.size() - 1);//safe because _heap.size()>=1
}
//same case as push 
template<class _Ty, class Compare>
template<class ..._Valty>
void priority_queue<_Ty, Compare>::emplace(_Valty&&..._Val) {
	_heap.emplace_back(std::forward<_Valty>(_Val)...);//we create the object in place
	swim(_heap.size() - 1);//safe because _heap.size()>=1
}
//swap with the last element of heap and then take  it out,no we must correct again the heap order so we sink _heap[0] down to the heap if it is 
//less than its two children 2k+1 and 2k+2
template<class _Ty, class Compare>
void priority_queue<_Ty, Compare>::pop() {
	if (_heap.size() != 0) {
		std::swap(_heap[0], _heap[_heap.size() - 1]);
		_heap.pop_back();
		sink(0);
	}
}
//swaps the private members between two priority queue's
template<class _Ty, class Compare>
void priority_queue<_Ty, Compare>::swap(priority_queue<_Ty, Compare>& other)
noexcept(std::is_nothrow_swappable_v<Compare>&&
	std::is_nothrow_swappable_v<std::vector<_Ty>>)
{
	std::swap(_comp, other._comp);
	_heap.swap(other._heap);
}
//we copy the state of the other priority queue and make no changes to it 
template<class _Ty, class Compare>
priority_queue<_Ty, Compare>& priority_queue<_Ty, Compare>::operator=(const priority_queue<_Ty, Compare>& other)& {
	if (this != &other) {
		_comp = other._comp;
		_heap = other._heap;
	}
	return *this;
}
//we steal the state of the other priority queue and make no changes to it,the other is in valid but unspecified state after this operation
template<class _Ty, class Compare>
priority_queue<_Ty, Compare>& priority_queue<_Ty, Compare>::operator=(priority_queue<_Ty, Compare>&& other)
& noexcept(std::is_nothrow_move_assignable_v<Compare>
	&& std::is_nothrow_move_assignable_v<std::vector<_Ty>>)
{
	if (this != &other) {
		_comp = std::move(other._comp);
		_heap = std::move(other._heap);
	}
	return *this;
}
//print the elements of the queue,use this function only if you know that the elements are printable with std::cout
template<class _Ty, class Compare>
void priority_queue<_Ty, Compare>::show()const {
	for (std::size_t i = 0; i < _heap.size(); i++) {
		std::cout << _heap[i] << '\n';
	}
}

//-----------------------
//		IMPLEMENTATION END
//-----------------------

_PANAGIOTIS_END
