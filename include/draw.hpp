#include <stdio.h>
#include <vector>
#include <opencv2/opencv.hpp>
#include <windows.h>

#include "struct.hpp"


class DrawTrajectory{
    public:
        // Constructor
        DrawTrajectory();

        // Destructor
        ~DrawTrajectory();


    public:
        /**
         * @brief 点の座標を線でつないで描画する
         * 
         * @param img   [OUT]画像データ
         * @param trajectory    [IN]点の座標
         * @param resolution    [IN]画像の解像度 (x,y)
         * @param line_type     [IN]線の種類。デフォルト(LINE_AA)はアンチエイリアス。
        */
        void draw(cv::Mat img, const std::vector<cv::Point2i> &trajectory, const ScreenResolution resolution, const int line_type=cv::LINE_AA);


        /// @brief PCモニタの解像度を取得し、返す
        ScreenResolution getScreenResolution();

};
