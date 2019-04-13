#include "worker.hpp"
#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <condition_variable>
#include <functional>
#include <future>

class ThreadPool
{
private:
	std::queue<std::function<void()>> m_queued_tasks_;

	std::vector<Worker*> m_worker_pool_;

	std::condition_variable m_condition_;

	std::mutex m_queue_mutex_;

	bool m_is_running_ = true;

	int m_num_workers_;

public:
	ThreadPool(std::size_t size);

	template<class F, class... Args>
	void enqueue(F&& f, Args&& ... args);
};