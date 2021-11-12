#include <cstdio>
#include <functional>
#include <thread>
#include <vector>
#include <queue>
#include <condition_variable>
#include <mutex>
#include <chrono>
#include <future>

class ThreadPool {
    
    public:
        ThreadPool (size_t num_threads);
        ~ThreadPool ();

        template <class F, class... Args>
        std::future<typename std::result_of<F(Args...)>::type> EnqueueJob(F&& f, Args&&... args);

    private:
        size_t num_threads_;
        std::vector<std::thread> workers_;
        std::queue<std::function<void ()>> jobs_;

        std::condition_variable cv_job_q_;
        std::mutex m_job_q_;
        bool stop_all;

        void work ();

};

ThreadPool::ThreadPool (size_t num_threads) : num_threads_(num_threads), stop_all(false) {
    workers_.reserve (num_threads_);
    for (size_t i=0; i<num_threads_; i++)
        workers_.emplace_back ([this]() {this->work ();});
}

ThreadPool::~ThreadPool () {
    stop_all = true;
    cv_job_q_.notify_all ();
    for (auto& t : workers_) // range based for statement
        t.join ();
}

// 1. result_of
// 2. &&
// 3. packaged_task
// 4. bind
// 5. forward
// 6. get_future

template <class F, class... Args>
std::future<typename std::result_of<F(Args...)>::type> ThreadPool::EnqueueJob (F&& f, Args&&... args) {
    using return_type = typename std::result_of<F(Args...)>::type;
    auto job = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    std::future<return_type> job_result_future = job->get_future();

    {
        std::lock_guard<std::mutex> lock (m_job_q_);
        jobs_.push ([job]() {(*job) (); });
    }
    cv_job_q_.notify_one ();

    return job_result_future;
}


void ThreadPool::work () {
    while (true) {
        std::unique_lock<std::mutex> lock(m_job_q_);
        cv_job_q_.wait (lock, [this]() {return !this->jobs_.empty() || stop_all; });
        if (stop_all && this->jobs_.empty ()) {
            return ;
        }

        std::function<void()> job = std::move (jobs_.front ());
        jobs_.pop ();
        lock.unlock ();

        job ();
    }

}


int work(int t, int id) {
    printf("%d start \n", id);
    std::this_thread::sleep_for(std::chrono::seconds(t));
    printf("%d end after %ds\n", id, t);
    return t+id;
}

int main() {
    ThreadPool pool(3);

    std::vector<std::future<int>> futures;
    for (int i = 0; i < 10; i++) {
        futures.emplace_back (pool.EnqueueJob (work, (i*i%16), i));
    }

    for (auto& f: futures) {
        printf ("result : %d\n", f.get ());
    }
 
}