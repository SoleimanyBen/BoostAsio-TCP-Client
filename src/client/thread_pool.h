#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <condition_variable>
#include <functional>

class ThreadPool
{
private:
	std::queue<std::function<Void()>> m_queued_tasks_;

	std::vector<std::thread> m_thread_pool_;

	std::condition_variable m_condition_;

	std::mutex m_queue_mutex_;

	bool m_is_running_ = true;

public:
	ThreadPool(std::size_t size);

	void start();
	void enqueue(F&& f, Args&&... args);
	void add_to_finished();
};