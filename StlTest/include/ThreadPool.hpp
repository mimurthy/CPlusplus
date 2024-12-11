#pragma once

#include <deque>
#include <thread>
#include <vector>

namespace custom
{

	template<typename T>
	class ThreadPool
	{
	public:

		ThreadPool(int numOfThreads) : numThreads_(numOfThreads)
		{
			for (int i = 0; i < numThreads_; i++)
			{
				threads_.push_back(std::thread(&ThreadPool::RunThread,this));				
			}
		}

		void RunThread()
		{
			T task;
			while (!stop_)
			{
				std::unique_lock<std::mutex> lck(mutex_);
				cv_.wait(lck, [this]()
					{
						if (taskBucket_.empty() == false || stop_ == true)
							return true;
					});

				if (!taskBucket_.empty() && stop_ == false)
				{
					{						
						task = taskBucket_.front();
						taskBucket_.pop_front();
					}
					lck.unlock();
					// Execute task
					task();
				}
			}
		}

		void AddTask(T task)
		{
			std::lock_guard<std::mutex> lg(mutex_);
			taskBucket_.push_back(task);
			cv_.notify_one();
			return;
		}

		void Stop()
		{
			stop_ = true;
			cv_.notify_all();
		}

		~ThreadPool()
		{
			for (int i = 0; i < numThreads_; i++)
				threads_[i].join();
		}

	private:

		bool stop_ = false;
		std::deque<T> taskBucket_;
		size_t numThreads_ = 0;
		std::vector<std::thread> threads_;
		std::mutex mutex_;
		std::condition_variable cv_;
	};
}