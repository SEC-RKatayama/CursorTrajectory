#include "draw.hpp"


// Constructor
DrawTrajectory::DrawTrajectory()
{
}

// Destructor
DrawTrajectory::~DrawTrajectory()
{
}


void DrawTrajectory::draw(cv::Mat img, const std::vector<cv::Point2i> &trajectory, const ScreenResolution resolution, const int line_type){
    for (int i=0; i<trajectory.size()-1; i++){
        cv::line(img, trajectory[i], trajectory[i+1], cv::Scalar(255,0,255,255), 1, line_type);
    }
    return;
}


ScreenResolution DrawTrajectory::getScreenResolution(){
    ScreenResolution screen_resolution;

    screen_resolution.x = GetSystemMetrics(SM_CXSCREEN);
    screen_resolution.y = GetSystemMetrics(SM_CYSCREEN);

    return screen_resolution;
}
