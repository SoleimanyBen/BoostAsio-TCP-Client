#include "thread_pool.h"

ThreadPool::ThreadPool(std::size_t size) 
{
	for (size_t i = 0; i < size; ++i)
	{
		m_thread_pool_.emplace_back(
			[this]()
			{
				
				while (true)
				{
					std::function<void()> task;

					{
						std::unique_lock<std::mutex> lock()
					}
				}
			}
		)
	}
}

void ThreadPool::start()
{

}

template<class F, class... Args>
void ThreadPool::enqueue(F&& f, Args&&... args)
{
	
}