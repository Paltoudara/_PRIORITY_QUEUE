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
