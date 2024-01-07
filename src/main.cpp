#include "draw.hpp"
#include "timer.hpp"
#include "track.hpp"

#ifdef DEBUGMODE_TRACK
#include <iostream>
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
    using namespace std::chrono;

    // Check argv
    if (argc < 3){
        fprintf(stderr, "Argument is not enough.\n");
        exit(1);
    }

    CursorTracker cursor_tracker;
    DrawTrajectory draw_trajectory;

    char *endptr1, *endptr2;
    duration wait_time = milliseconds(strtol(argv[1], &endptr1, 10)*1000);
    time_point<steady_clock> start_time = steady_clock::now() + wait_time;
    duration dur = milliseconds(strtol(argv[2], &endptr2, 10)*1000);
    duration interval = milliseconds(50); // カーソル座標取得間隔のデフォルト値
    std::vector<POINT> cursor_trajectory_win;
    std::vector<cv::Point2i> cursor_trajectory_cv;
    std::vector<time_point<steady_clock>> time_stamp;

    cv::Mat img;
    ScreenResolution resolution;


    if (argc > 3){
        // interval指定がある場合
        char *endptr_interval;
        interval = milliseconds(strtol(argv[3], &endptr_interval, 10));
        
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
        fprintf(stdout, "Duration time: %ld s.\n", dur/1000);
    }
    else{
        fprintf(stderr, "Second argument is invalid.\n");
        exit(1);
    }

    // 開始時刻まで待機
    std::this_thread::sleep_until(start_time);

    // マウス軌跡記録
    fprintf(stdout, "Start recording...\n");
    cursor_trajectory_win = cursor_tracker.recordCursorPos(dur, interval, time_stamp);
    fprintf(stdout, "End recording.\n");

    cursor_trajectory_cv.resize(cursor_trajectory_win.size());
    for (int i=0; i<cursor_trajectory_cv.size(); i++){
        cursor_trajectory_cv[i].x = cursor_trajectory_win[i].x;
        cursor_trajectory_cv[i].y = cursor_trajectory_win[i].y;
    }

#ifdef DEBUGMODE_TRACK
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


    // 描画設定
    resolution = draw_trajectory.getScreenResolution();
    img.create(resolution.y, resolution.x, CV_8UC4);    // CV_8UC4: 8bitRGB + alpha

    // 描画
    draw_trajectory.draw(img, cursor_trajectory_cv, resolution, cv::LINE_AA);

#ifdef DEBUGMODE_DRAW
    // 画像表示
    cv::imshow("Mouse Cursor Trajectory", img);
    cv::waitKey(0);
#endif

    // ファイル保存
    cv::imwrite("output.png", img);

    return 0;
}
