#include <stdio.h>
#include <thread>
#include <vector>
#include <chrono>
#include <windows.h>


namespace std::chrono{

class CursorTracker{
    
    public:
        // Constructor
        CursorTracker();

        // Destructor
        ~CursorTracker();


    public:
        /**
         * @brief 一定時間マウスの軌跡を座標で記録し、返却する
         * 
         * @param duration [IN]記録する時間
         * @param interval [IN]マウスカーソル座標を読み取る時間間隔
         * @param time_stamp [OUT]マウスカーソル座標を読み取った時刻のタイムスタンプ
         * 
         * @return タイムスタンプ付きマウスカーソル座標。 (3,n): time, x, yの3行。
        */
        std::vector<POINT> recordCursorPos(const chrono::duration<int, std::milli> duration, const chrono::duration<int, std::milli> interval,
            std::vector<chrono::time_point<chrono::steady_clock>> &time_stamp);

};

}
