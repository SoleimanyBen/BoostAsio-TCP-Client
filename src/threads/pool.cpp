#include "pool.hpp"
#include "worker.hpp"

ThreadPool::ThreadPool(std::size_t size)
{
	create_workers(size);
}

// Create workers
void ThreadPool::create_workers(int size)
{
	for (int i = 0; i < size; ++i)
	{
		m_worker_pool_.push_back(new Worker())
	}
}

template<class F, class... Args>
void ThreadPool::enqueue(F&& f, Args&& ... args)
{
	std::packaged_task<F> task(std::bind(std::forward<F>(f), std::forward<Args>(args)...));

	for (int i = 0; i < m_num_workers_; ++i)
	{
		m_queue_mutex_.lock();

		if (m_worker_pool_[i]->get_tasks_amt < 0)
		{
			m_worker_pool_[i]->assign_task(task);
			
			return;
		}
	}
}