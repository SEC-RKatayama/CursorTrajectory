#include <stdio.h>
#include <thread>
#include <vector>


class PeriodicExecutor{
    public:
        // Constructor
        PeriodicExecutor();

        // Destructor
        ~PeriodicExecutor();


    public:
        /**
         * @brief コールバック関数を回す
         * 
         * @param callback コールバック関数へのポインタ
         * @param interval 周期 [ms]
         * @param arg
        */
        template <typename T, typename... Args>
        void start(T* callback, unsigned int interval, Args... args);


        /**
         * @brief コールバック関数を止める
        */
        void stop();


    private:
        std::thread timer_callback_;
        bool thread_running_;
};
