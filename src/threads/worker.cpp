#include "worker.hpp"


Worker::Worker() {}

// Worker starts loop and is blocked by condition variables, once it is told to continue it will unblock and operate on the thread
void Worker::start_worker()
{
	for (;;)
	{
		std::function<Void()> task;

		{
			std::unique_lock<std::mutex> lock(m_queue_mutex_);

			m_condition_.wait(lock, has_tasks_());

			task = std::move(m_task_queue_.front());

			m_task_queue_.pop();
		}

		m_thread_(task());
	}
}

void Worker::assign_task(std::packaged_task task)
{
	m_task_queue_.front(task);
}

int Worker::has_tasks()
{
	if (m_task_queue_.size() > 0 && m_is_running_)
		return true;

	return false;
}

int Worker::get_tasks_amt()
{
	return m_task_queue_.size();
}