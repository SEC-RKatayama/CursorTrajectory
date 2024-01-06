#include "track.hpp"


// Constructor
CursorTracker::CursorTracker(){
}

// Destructor
CursorTracker::~CursorTracker(){
}


std::vector<POINT> CursorTracker::recordCursorPos(const std::chrono::duration<int, std::milli> duration, const std::chrono::duration<int, std::milli> interval, 
        std::vector<std::chrono::time_point<std::chrono::steady_clock>> &time_stamp){

    std::vector<POINT> cursor_trajectory; // return値
    POINT mouse_point;
    
    auto start_time = std::chrono::steady_clock::now();
    auto next_time = start_time;
    for (;;){
        next_time += interval;
        if (!GetCursorPos(&mouse_point)) {
            auto current_time = std::chrono::steady_clock::now();
            auto elapsed_time = current_time - start_time;
            if (elapsed_time >= duration){
                break; // 失敗した場合でも時間経過を考慮する（さもなければ無限ループに陥る恐れあり）
            }
            continue; // 位置取得に失敗したら次ループで再トライ
        }
        time_stamp.push_back(std::chrono::steady_clock::now());
        cursor_trajectory.push_back(mouse_point);
        
        auto current_time = std::chrono::steady_clock::now();
        auto elapsed_time = current_time - start_time;
        if (elapsed_time >= duration)
            break;
        
        std::this_thread::sleep_until(next_time);
    }

    return cursor_trajectory;
}
