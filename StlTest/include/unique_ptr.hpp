#pragma once

namespace custom
{
	template <typename T>
	class unique_ptr
	{
	public:
		/// constructor
		unique_ptr()
		{
			std::cout << "Unique_ptr T constructor" << std::endl;
		}

		/// parameterized constructor
		unique_ptr(T* ptr) : rawPtr(ptr)
		{
			std::cout << "Unique_ptr T constructor" << std::endl;
		}

		/// copy constructor
		unique_ptr(const unique_ptr& rhs) = delete;		

		/// move constructor
		unique_ptr(unique_ptr&& rhs)
		{
			rawPtr = rhs.rawPtr;
			rhs.rawPtr = nullptr;
		}

		/// copy assignment operator
		unique_ptr& operator = (const unique_ptr& rhs) = delete;

		/// move assignment operator
		unique_ptr& operator = (unique_ptr&& rhs)
		{
			rawPtr = rhs.rawPtr;
			rhs.rawPtr = nullptr;
		}

		T* get()
		{
			return rawPtr;
		}

		T* operator -> ()
		{
			return rawPtr;
		}

		T operator * ()
		{
			return *rawPtr;
		}

		T* release()
		{
			if (rawPtr == nullptr)
				return nullptr;
			
			auto temp = rawPtr;
			rawPtr = nullptr;
			return temp;		
		}

		operator bool()
		{
			return (rawPtr != nullptr);
		}

		/// destructor
		~unique_ptr()
		{
			if (rawPtr != nullptr)
			{
				std::cout << "Deleting raw pointer" << std::endl;
				delete rawPtr;
			}
		}

		void reset(T* ptr)
		{
			rawPtr = ptr;
		}

		T* rawPtr = nullptr;
	};

	template <typename T>
	class unique_ptr<T[]>
	{
	public:
		/// constructor
		unique_ptr()
		{
			std::cout << "Unique_ptr T[]" << std::endl;
		}

		/// parameterized constructor
		unique_ptr(T* ptr) : rawPtrArr(ptr)
		{
			std::cout << "Unique_ptr T[]" << std::endl;
		}

		/// copy constructor
		unique_ptr(const unique_ptr& rhs) = delete;

		/// copy assignment operator
		unique_ptr& operator = (const unique_ptr& rhs) = delete;

		/// move constructor
		unique_ptr(unique_ptr&& rhs)
		{
			rawPtrArr = rhs.rawPtrArr;
			rhs.rawPtrArr = nullptr;
		}

		/// move assignment operator
		unique_ptr& operator = (unique_ptr&& rhs)
		{
			rawPtrArr = rhs.rawPtrArr;
			rhs.rawPtrArr = nullptr;
		}

		T& operator [] (int index)
		{
			return rawPtrArr[index];
		}

		~unique_ptr()
		{
			delete[] rawPtrArr;
		}

		T* rawPtrArr;
	};

	template<typename T, typename... Args>
	unique_ptr<T> make_unique(Args&&... args)
	{
		return unique_ptr<T>(new T(std::forward<Args>(args)...));
	}
}

