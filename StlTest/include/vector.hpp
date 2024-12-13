#pragma once

namespace custom
{
	template <typename T>
	class Allocator
	{
	public:
		using pointer = T * ;
		using reference = T & ;
		using size_type = size_t;
		using value_type = T;

		template <typename U>
		struct rebind
		{
			typedef Allocator<U> other;
		};

		// Constructor and Destructor
		Allocator() = default;
		~Allocator() = default;

		// Copy constructor for other types
		template <typename U>
		Allocator(const Allocator<U>&) noexcept
		{
		}

		pointer allocate(size_type numObjects)
		{
			return reinterpret_cast<pointer>(::operator new(numObjects * sizeof(T)));
		}

		void deallocate(pointer ptrToMemory, size_type numObjects)
		{
			if (numObjects > 1)
				::operator delete[](ptrToMemory);
			else
				::operator delete(ptrToMemory);
		}

		// Construct an object in-place
		template <typename... Args>
		void construct(pointer ptr, Args&&... args)
		{
			new (ptr) T(std::forward<Args>(args)...);
			//new (ptr) T(args...);
		}

		// Destroy an object
		void destroy(pointer ptr)
		{
			ptr->~T();
		}

		// Comparators (required by some STL algorithms)
		bool operator==(const Allocator&) const noexcept { return true; }
		bool operator!=(const Allocator&) const noexcept { return false; }
	};
	
	template<typename T, typename Alloc = Allocator<T> >
	class vector 
	{
		using value_type = T;		
	public:

		// Default constructor
		vector() : vector(1,0)
		{
			
		}

		template<typename... Args>
		vector(int size, Args... args) : size_(size), capacity_(size)
		{				
			data_ = allocater.allocate(capacity_);
			for (int i = 0; i < size; i++)
			{				
				allocater.construct(&data_[i], args...);
			}				
		}

		// Constructor with initializer list
		vector(std::initializer_list<T> list)
		{
			size_ = capacity_ = list.size();
			data_ = allocater.allocate(capacity_);
			int i = 0;
			for( auto iter = list.begin(); iter != list.end(); iter++)			
			{	
				//allocater.construct(&data_[i++], *iter);				
			}			
		}

		// Copy constructor
		vector(const vector& rhs)
		{
			size_			= rhs.size_;
			capacity_	= rhs.capacity_;
			data_			= new T[capacity_];
			for (int i = 0; i < capacity_; i++)
			{
				data_[i] = rhs.data_[i];
			}
		}

		// Copy assignment operator
		vector& operator = (const vector& rhs)
		{	
			if (this != rhs) // self assignment check
			{
				size_ = rhs.size_;
				capacity_ = rhs.capacity_;
				data_ = new T[capacity_];
				for (int i = 0; i < capacity_; i++)
				{
					data_[i] = rhs.data_[i];
				}
			}
			return *this;
		}

		// Move constructor
		vector(vector&& rhs) noexcept
		{
			data_ = rhs.data_;
			size_ = rhs.size_;
			capacity_ = rhs.capacity_;

			rhs.data_ = nullptr;
			rhs.size_ = 0;
			rhs.capacity_ = 0;
		}

		// Move assignment operator
		vector& operator = (const vector&& rhs) noexcept
		{			
			data_ = rhs.data_;
			size_ = rhs.size_;
			capacity_ = rhs.capacity_;
		}

		void reserve(size_t size)
		{			
			auto temp = allocater.allocate(size);
			if (temp != data_) // can be a realloc and memory expanded at the same place
			{
				for (int i = 0; i < size_; i++)
				{
					temp[i] = data_[i];
				}

				for (int i = 0; i < size_; i++)
				{
					allocater.destroy(&data_[i]);
				}

				allocater.deallocate(&data_[0], capacity_);
				data_ = temp;
			}
			capacity_ = size;
		}

		void shrink_to_fit()
		{
			reserve(size_);			
		}

		void resize(size_t size)
		{
			if (size < size_)
			{
				for (int i = size; i < size_; i++)
				{
					allocater.destroy(&data_[i]);
				}
				size_ = size;
			}
		}

		void push_back(T& elem)
		{
			if (size_ == capacity_)
				reserve(capacity_ * 2);

			allocater.construct(&data_[size_++], elem);
		}

		void emplace_back(T&& elem)
		{
			if (size_ == capacity_)
				reserve(capacity_ * 2);
						
			allocater.construct(&data_[size_++], std::forward<T&&>(elem));
		}

		T* data()
		{
			return &data_[0];
		}

		void pop_back()
		{
			--size_;
		}

		T& operator[] (int index)
		{
			return data_[index];
		}

		const T& operator[] (int index) const
		{
			return data_[index];
		}

		inline size_t capacity() const
		{
			return capacity_;
		}

		inline size_t size() const
		{
			return size_;
		}

		~vector()
		{
			for (int i = 0; i < size_; i++)
			{
				allocater.destroy(&data_[i]);
			}

			allocater.deallocate(&data_[0], capacity_);
		}		

	private:
		T * data_ = nullptr;
		int capacity_ = 0;
		int size_ = 0;
		Alloc allocater;
	};

}