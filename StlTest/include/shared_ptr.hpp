#pragma once

namespace custom
{
	template<typename T>
	class shared_ptr
	{
	public:

		/// default constructor
		shared_ptr()
		{			
		}

		/// parameterized constructor
		shared_ptr(T* ptr) : shared_ptr()
		{
			rawPtr = ptr;
			refCnt = new size_t;
			*refCnt = 1;
		}

		/// copy constructor
		shared_ptr(const shared_ptr& rhs)
		{
			rawPtr = rhs.rawPtr;
			refCnt = rhs.refCnt;
			(*refCnt)++;
		}

		/// copy assignment operator
		shared_ptr& operator = (const shared_ptr& rhs)
		{
			if (this != &rhs) // self assignment test
			{
				if ( refCnt)
					(*refCnt)--;
				rawPtr = rhs.rawPtr;
				refCnt = rhs.refCnt;
				(*refCnt)++;
			}

			return *this;
		}

		/// move constructor
		shared_ptr(shared_ptr&& rhs)
		{			
			rawPtr = rhs.rawPtr;
			refCnt = rhs.refCnt;			
			rhs.rawPtr = nullptr;
			rhs.refCnt = nullptr;
		}

		/// move assignment operator
		shared_ptr& operator = (shared_ptr&& rhs)
		{
			refCnt--;
			rawPtr = rhs.rawPtr;
			refCnt = rhs.refCnt;
			(*refCnt)++;
			rhs.rawPtr = nullptr;
			rhs.refCnt = nullptr;
		}

		T* operator -> ()
		{
			return rawPtr;
		}

		T operator * ()
		{
			return *rawPtr;
		}

		const T* get()
		{
			return rawPtr;
		}

		/// destructor
		~shared_ptr()
		{
			std::cout << "Destructor" << std::endl;
			if ( refCnt && ((*refCnt)--) == 0)
			{
				if ( rawPtr != nullptr)
					delete rawPtr;
			}
		}

	private:
		T* rawPtr = nullptr;
		size_t *refCnt = nullptr;
	};

	template<typename T, typename... Args>
	shared_ptr<T> make_shared(Args&&... args)
	{
		return shared_ptr<T>(new T(std::forward<Args>(args)...));
	}
}