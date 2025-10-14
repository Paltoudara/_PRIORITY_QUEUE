#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
#include<type_traits>
#include<cstdlib>
#include<functional>
#include<utility>
#include<cassert>
#include"Header.h"
_PANAGIOTIS_BEGIN
template<class _Ty,class Compare=std::less<_Ty>>
class priority_queue final{
private:
	//
	std::vector<_Ty>_heap;
	Compare _comp;
	//
	void sink(std::size_t k)
	{
		static_assert(std::is_swappable_v<_Ty>
			,"the type must be swappable");
		//note that the compare func should be a func that takes two 
		//const _Ty& args and returns a bool,or else the behavior is 
		//undefined
		while (2 * k + 1 < _heap.size()) {
			std::size_t j{ 2 * k + 1 };
			if (j + 1 < _heap.size() && _comp(
				std::as_const(_heap[j]) ,std::as_const(_heap[j + 1])))j++;
			if (!_comp(std::as_const(_heap[k]) ,std::as_const( _heap[j])))break;
			std::swap(_heap[k], _heap[j]);
			k = j;
		}
	}
	void swim(std::size_t k)
	{
		static_assert(std::is_swappable_v<_Ty>, "the type must"
			"be swappable");
		//note that the compare func should be a func that takes two 
		//const _Ty& args and returns a bool,or else the behavior is 
		//undefined
		while (k > 0 && _comp(std::as_const(_heap[(k - 1) / 2]),
			std::as_const( _heap[k]))) {
			std::swap(_heap[k], _heap[(k - 1) / 2]);
			k = (k - 1) / 2;
		}
	}
public:
	//default constructor done
	priority_queue()noexcept(
		std::is_nothrow_default_constructible_v<std::vector<_Ty>>
		&&std::is_nothrow_default_constructible_v<Compare>)
		:_heap{}, _comp{}
	{
		static_assert(std::is_default_constructible_v<std::vector<_Ty>>
			&& std::is_default_constructible_v<Compare>
			,"the heap and comparator must be default constructible");
	}
	//comparator constructor done
	explicit priority_queue(const Compare& comp)noexcept(
		std::is_nothrow_default_constructible_v<std::vector<_Ty>>
		&&std::is_nothrow_copy_constructible_v<Compare>)
		:_heap{},_comp{comp}
	{
		static_assert(std::is_default_constructible_v<std::vector<_Ty>>
			&& std::is_copy_constructible_v<Compare>,
			"the heap must be default constructible and the comp must"
			"be copy constructible");
	}
	//constructor with comp& and heap& done
	priority_queue(const Compare& comp, const std::vector<_Ty>& heap)
		:_comp{comp},_heap{heap}
	{
		static_assert(std::is_copy_constructible_v<Compare>
			&& std::is_copy_constructible_v<std::vector<_Ty>>,
			"the heap must be copy constructible and the comp must"
			"be copy constructible");
		//if copy fails no object created
		//if all goes good we make heap
		
		//if the func sink throws we are in partially modified or not heap
		//or else the we have the heap order we want 
		//call the func sink to create the heap order
		for (long long k = static_cast<long long>(_heap.size() / 2 - 1); k >= 0; k--) {
			sink(k);
		}
	}
	priority_queue(const Compare& comp, std::vector<_Ty>&& heap)
		:_comp{comp},_heap{std::move(heap)}
	{
		static_assert(std::is_copy_constructible_v<Compare>
			&& std::is_move_constructible_v<std::vector<_Ty>>,"the comp"
			"should be copy constructible and the vector should be"
			"move constructible");
		//if move fails no object created
		//if all goes good we make heap

		//if the func sink throws we are in partially modified or not heap
		//or else we have the heap order we want 
		//call the func sink to create the heap order
		for (long long k = static_cast<long long>(_heap.size() / 2 - 1); k >= 0; k--) {
			sink(k);
		}
	}
	priority_queue(const priority_queue<_Ty, Compare>& other) 
		:_comp{}, _heap{}
	{
		static_assert(std::is_default_constructible_v<Compare>&&
			std::is_default_constructible_v<std::vector<_Ty>>,"the"
			"comp must be default constructible and the heap must be"
			"default constructible");
		static_assert(std::is_copy_assignable_v<Compare> &&
			std::is_copy_assignable_v<std::vector<_Ty>>, "the"
			"comp must be copy assignable and the heap must be"
			"copy assignable");
		if (this != &other) {
			_comp = other._comp;
			_heap = other._heap;
		}
	}
	priority_queue(priority_queue<_Ty, Compare>&& other) 
		:_comp{}, _heap{}
	{
		static_assert(std::is_default_constructible_v<Compare> &&
			std::is_default_constructible_v<std::vector<_Ty>>, "the"
			"comp must be default constructible and the heap must be"
			"default constructible");
		static_assert(std::is_move_assignable_v<Compare> &&
			std::is_move_assignable_v<std::vector<_Ty>>, "the"
			"comp must be move assignable and the heap must be"
			"move assignable");
		if (this != &other) {
			_comp =std::move( other._comp);
			_heap = std::move(other._heap);
		}
	}
	bool empty()const noexcept {
		return _heap.empty();
	}
	std::size_t size()const noexcept {
		return _heap.size();
	}
	const _Ty& top()const noexcept {
		return _heap.front();
	}
	void push(const _Ty& val) {
		_heap.push_back(val);
		swim(_heap.size() - 1);
	}
	void push(_Ty&& val) {
		_heap.push_back(std::move(val));
		swim(_heap.size()-1);//safe because _heap.size()>=1
	}
	template<class ..._Valty>
	void emplace(_Valty&&..._Val) {
		_heap.emplace_back(std::forward<_Valty>(_Val)...);
		swim(_heap.size() - 1);
	}
	void pop() {
		//throw exception if the heap has no elements
		static_assert(std::is_swappable_v<_Ty>,"the type _Ty must be"
			"swappable");
		std::swap(_heap[0],_heap [_heap.size()-1]);
		_heap.pop_back();
		sink(0);
	}
	void swap(priority_queue<_Ty,Compare>&other)
		noexcept(std::is_nothrow_swappable_v<Compare>&&
			std::is_nothrow_swappable_v<std::vector<_Ty>>)
	{
		std::swap(_comp, other._comp);
		std::swap(_heap, other._heap);
	}
};

_PANAGIOTIS_END
