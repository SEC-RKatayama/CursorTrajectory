#include "timer.hpp"


// Constructor
PeriodicExecutor::PeriodicExecutor() : thread_running_(false)
{
}

// Destructor
PeriodicExecutor::~PeriodicExecutor()
{
    stop();
}


template <typename T, typename... Args>
void PeriodicExecutor::start(T* callback, unsigned int interval_int, Args... args){
    thread_running_ = true;

    const auto interval = std::chrono::milliseconds(interval_int);

    timer_callback_ = std::thread([this, interval, callback, args...]() {
        auto next = std::chrono::steady_clock::now();
        while (thread_running_) {
            next += interval;
            std::this_thread::sleep_until(next);
            callback->callback(args...);
        }
    });
}

void PeriodicExecutor::stop(){
    if (!thread_running_)
        return;
    
    thread_running_ = false;

    if (timer_callback_.joinable())
        timer_callback_.join();
}


