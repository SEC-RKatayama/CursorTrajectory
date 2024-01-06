#include "draw.hpp"
#include "timer.hpp"
#include "track.hpp"

#define DEBUGMODE

#ifdef DEBUGMODE
#include <iostream> // debug
#endif

/**
 * @brief main
 * 
 * @param argv[0]:（略）
 * @param argv[1]:軌跡記録開始までの時間 [s]（今からargv[1]秒後）
 * @param argv[2]:軌跡記録時間 [s]（開始時刻からargv[2]秒間）
 * @param argv[3]:（任意）座標取得間隔 [ms]
*/
int main(int argc, char* argv[]){
    // Check argv
    if (argc < 3){
        fprintf(stderr, "Argument is not enough.\n");
        exit(1);
    }

    CursorTracker cursor_tracker;

    char *endptr1, *endptr2;
    std::chrono::duration wait_time = std::chrono::milliseconds(strtol(argv[1], &endptr1, 10)*1000);
    std::chrono::time_point<std::chrono::steady_clock> start_time = std::chrono::steady_clock::now() + wait_time;
    std::chrono::duration duration = std::chrono::milliseconds(strtol(argv[2], &endptr2, 10)*1000);
    std::chrono::duration interval = std::chrono::milliseconds(100); // カーソル座標取得間隔のデフォルト値
    std::vector<POINT> cursor_trajectory;
    std::vector<std::chrono::time_point<std::chrono::steady_clock>> time_stamp;

    if (argc > 3){
        // interval指定がある場合
        char *endptr_interval;
        interval = std::chrono::milliseconds(strtol(argv[3], &endptr_interval, 10));
        
        // Argument check
        if (*endptr_interval == '\0'){
            fprintf(stdout, "Interval time: %ld s.\n", interval*1000);
        }
        else{
            fprintf(stderr, "Interval time is invalid.\n");
            exit(1);
        }
    }
    
    // Argument check
    if (*endptr1 == '\0'){
        fprintf(stdout, "Wait time (from now): %ld s.\n", wait_time/1000);
    }
    else{
        fprintf(stderr, "First argument is invalid.\n");
        exit(1);
    }
    if (*endptr2 == '\0'){
        fprintf(stdout, "Duration time: %ld s.\n", duration/1000);
    }
    else{
        fprintf(stderr, "Second argument is invalid.\n");
        exit(1);
    }

    // 開始時刻まで待機
    std::this_thread::sleep_until(start_time);

    // マウス軌跡記録
    fprintf(stdout, "Start recording...\n");
    cursor_trajectory = cursor_tracker.recordCursorPos(duration, interval, time_stamp);
    fprintf(stdout, "End recording.\n");

#ifdef DEBUGMODE
    int _len = cursor_trajectory.size();
    printf("(x,y):\n");
    for (int i=0; i<_len; i++){
        printf("(%ld,%ld)\n", cursor_trajectory[i].x, cursor_trajectory[i].y);
    }
    
    for (int i=0; i<_len-1; i++){
        auto _dd = time_stamp[i+1] - time_stamp[i];
        std::cout << "Time diff: " << _dd.count()/1000000 << "ms" << std::endl;
    }
    printf("Number of points = %d\n", _len);
#endif

    // 描画


    return 0;
}