#pragma once
#include <cstring>

namespace custom
{
	class string
	{
	public:
		string() : size_(1), capacity_(1)
		{
			s = new char[size_];
			s[0] = '\0';
		}

		string(const char* str)
		{
			size_ = capacity_ = strlen(str) + 1;
			s = new char[size_];
			strcpy_s(s, size_, str);
			s[size()] = '\0';
		}

		string(const string& rhs) : string(rhs.c_str())
		{
		}

		string& operator = (const string& rhs)
		{
			if (this != &rhs)
			{
				delete s;
				size_ = capacity_ = strlen(rhs.c_str()) + 1;
				s = new char[size_];
				strcpy_s(s, size_, rhs.c_str());
				s[size()] = '\0';
			}
			return *this;
		}

		string(string&& rhs)
		{
			if (this != &rhs)
			{
				size_ = rhs.size_;
				capacity_ = rhs.capacity_;
				s = const_cast<char*>(rhs.c_str());
				rhs.s = nullptr;
				rhs.size_ = rhs.capacity_ = 0;
			}
		}

		string& operator = (string&& rhs)
		{
			size_ = rhs.size_;
			capacity_ = rhs.capacity_;
			s = const_cast<char*>(rhs.c_str());
			rhs.s = nullptr;
			rhs.size_ = rhs.capacity_ = 0;
			return *this;
		}

		bool operator == (const string& rhs)
		{
			if (size_ != rhs.size_)
				return false;

			if (strcmp(s, rhs.c_str()) == 0)
				return true;

			return false;
		}

		bool operator != (const string& rhs)
		{
			return !operator==(rhs);
		}

		string operator + (const string& rhs)
		{
			size_t new_size = size_ + rhs.size_ + 1;
			char *temp = new char[new_size];
			strcpy_s(temp, new_size, s);
			strcat_s(temp, new_size, rhs.s);
			return string(temp);
		}

		string& operator += (const string& rhs)
		{
			size_t new_size = size() + rhs.size() + 1;
			char *temp = new char[new_size];
			strcpy_s(temp, new_size, s);
			strcat_s(temp, new_size, rhs.s);
			delete s;
			s = temp;
			size_ = capacity_ = new_size;
			s[size()] = '\0';
			return *this;
		}

		~string()
		{ 
			delete s;
		}

		bool empty() const
		{
			return size_ == 0;
		}

		size_t size() const
		{
			return size_ - 1;
		}

		size_t capacity() const
		{
			return capacity_;
		}

		const char* c_str() const
		{
			return s;
		}

		size_t size_ = 0;
		size_t capacity_ = 0;
		char *s = nullptr;		
	};
}