# 🔗 Welcome to the PRIORITY_QUEUE API 🌐 :
## 🧩 Interface

```markdown
```cpp
template<class _Ty, class Compare = std::less<_Ty>>
class priority_queue final {
public: 

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

  void push(const _Ty& val) ;

  void push(_Ty&& val);

  template<class ..._Valty>
  void emplace(_Valty&&..._Val) ;

  void pop();

  void swap(priority_queue<_Ty, Compare>& other)
    noexcept(std::is_nothrow_swappable_v<Compare>&&
      std::is_nothrow_swappable_v<std::vector<_Ty>>);

  priority_queue<_Ty, Compare>& operator=(const priority_queue<_Ty, Compare>& other)& ;

  priority_queue<_Ty, Compare>& operator=(priority_queue<_Ty, Compare>&& other)
		  & noexcept(std::is_nothrow_move_assignable_v<Compare>
			  && std::is_nothrow_move_assignable_v<std::vector<_Ty>>);

  ~priority_queue() = default;

  void show()const;
};


```
# 📝NOTE THAT:
THIS IS THE INTERFACE OF THE PRIORITY QUEUE,WITH THIS INTERFACE YOU CAN MANIPULATE THE PRIORITY QUEUE.IF YOU WANT MORE DETAILS ABOUT THE IMPLEMENTATION JUST SEE THE PRIORITY_QUEUE.h AND Macros.h FOR HOW THINGS ARE DONE,ALSO THIS PRIORITY QUEUE ACCECPTS A COMPARATOR AND A TYPE AS TEMPLATE ARGUMENTS.

# ⚙️MEMBER FUNCTIONS:
1) default constructor just initializes the priority queue,pretty much the default state.

2) a constructor that takes a comparator argument,and  this comparator is used from now on for the priority queue.

3) a constructor that takes a comparator and a vector argument,the comparator is used from now on for the priority queue and we take a copy of the vector and we heapify in order to make it a heap order like structure.Note that a heap structure keeps a certain order for the elements,in simple terms every k element is greater or equal from its 2k+1 and 2k+2 elements.This creates  a binary tree like  data structure which is balanced.

4) copy constructor: we copy the state of the other priority queue.Note that we don't make any more other than that which means if the other heap is not in order we copy the same not in order heap.

5) move constructor: we take the resourses of the other priority queue.Note that we don't make more other than that which means if the other heap is not inorder we move the same not in order heap.The other
is now in valid but unspecified state.

6) empty function just checks if the heap has any elements.

7) size function just checks how many elements the heap has.

8) top function just returns the the first element from the heap only for reading purposes and not changing.

9) push with copy,this function just pushes an element at the end of the heap with copy .After this the heap might become invalid so we call a function to fix this and maintain the heap order.

10) push with move,this function acts the same as push but this time we push the element to the heap with move and not copy.

11) emplace,same behavior as push but this time we create the object in place and then pushe it to the heap.

12) pop,this function swaps the first element of the heap aka the maximum or minimum element based on the order ,with the last element and takes it out from the heap.After this the heap might become invalid so we call a function to fix this and maintain the heap order.

13) swap,this function swaps our contents with the other's contents.

14) copy operator we copy again the state of the other.

16) move operator,we steal the resourses of the other and we leave it in valid but unspecified state.

17) destructor,deallocates the heap

18) show,this function just prints how the heap is,use this function only when the type you passed as template to the priority queue is printable with std::cout
 
# 📝NOTE THAT:
IN ORDER TO UNDERSTAND WHAT HAPPENS TO THE FUNCTIONS EXACTLY YOU MUST SEE THE IMPLEMENTATION.
# 📬IF YOU HAVE ANY ISSEUES ON THIS PLZ FEEL FREE TO SUBMIT THEM 📬
# 👥CONTRIBUTORS:
🎨~Paltoudara
