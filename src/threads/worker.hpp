#include <condition_variable>
#include <vector>
#include <queue>
#include <mutex>
#include <functional>
#include <future>


class Worker
{
private:
	std::condition_variable m_condition_;
	std::mutex m_queue_mutex_;

	std::thread m_thread_;

	std::queue<Void()> m_task_queue_;

	bool m_is_running_;

public:
	Worker();

	void start_worker();
	void stop_worker();
	void start_thread();

	void assign_task(std::packaged_task task);

	bool has_tasks();
	
	int get_tasks_amt();
};