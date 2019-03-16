/* 
 * File:   main.cpp
 * Author: yvvidolov
 *
 * Created on March 16, 2019, 11:26 AM
 */

#include <cstdlib>

#include <opencv2/opencv.hpp>
#include <experimental/filesystem>

using namespace std;
using namespace cv;

namespace fs = std::experimental::filesystem;

int mc[3] = {0};
int mp[2] = {0};
Mat markers;
Mat draw;

int main(int argc, char** argv) 
{
    if(argc < 2)
    {
        cout<<"[Usage] Please provide file or directory"<<endl;
        cout<<"[Example] "<<argv[0]<<" myImage.bmp"<<endl;
        cout<<"[Example] "<<argv[0]<<" ./myPath/"<<endl;
        return 0;
    }
    
    vector<string> fileNames;
    const char* imgPath = argv[1];
    if(fs::is_directory(imgPath))
    {
        for (const auto & entry : fs::directory_iterator(imgPath))
            if(entry.status().type() == fs::file_type::regular)
                fileNames.push_back(entry.path());
    }
    else fileNames.push_back(imgPath);
    
    namedWindow("ctrl");
    namedWindow("draw");
    
    cv::setMouseCallback("draw", [](int event, int x, int y, int flags, void* userdata){
        if(event == EVENT_LBUTTONDOWN) mc[0] = 1;
        if(event == EVENT_LBUTTONUP) mc[0] = 0;
        if(event == EVENT_MBUTTONDOWN) mc[1] = 1;
        if(event == EVENT_MBUTTONUP) mc[1] = 0;
        if(event == EVENT_RBUTTONDOWN) mc[2] = 1;
        if(event == EVENT_RBUTTONUP) mc[2] = 0;
        
//        if(event == EVENT_MOUSEMOVE)
        {
            mp[0] = x;
            mp[1] = y;
        
            if(x > 0 && x < markers.cols && y > 0 && y < markers.rows)
            {
                if(mc[0]) {
//                    markers.at<int>(y, x) = 1;
                    circle(markers, Point(x, y), 8, Scalar(1), 4);
                }
                if(mc[1]) {
                    circle(markers, Point(x, y), 8, Scalar(0), 10);
                }
                if(mc[2]) {
//                    markers.at<int>(y, x) = 2;
                    circle(markers, Point(x, y), 8, Scalar(2), 4);
                }
            }
        }
    });
    
    int imid = 0; cv::createTrackbar("img", "ctrl", &imid, std::max(1, (int)fileNames.size()-1));

    int imidold = -1;
    
    Mat in;
    while(1)
    {
        if(imidold != imid)
        {
            imidold = imid;
            
            in = imread(fileNames[imid].c_str());
            pyrDown(in, in); pyrDown(in, in);
            
            markers = Mat::zeros(in.size(), CV_32S);
            draw = Mat(in.size(), CV_8UC3);
        }
        if(in.empty()) { imidold = -1; continue; }
        
        Mat gr; cvtColor(in, gr, CV_RGB2GRAY);
        
        for(int y = 0; y < draw.rows; ++y)
        for(int x = 0; x < draw.cols; ++x)
            draw.at<Vec3b>(y, x) = in.at<Vec3b>(y, x)*0.8 + Vec3b(0, markers.at<int>(y, x)==1?255:0, markers.at<int>(y, x)==2?255:0);

        Mat mrk = markers.clone();
        watershed(in, mrk);
        
        for(int y = 1; y < draw.rows-1; ++y)
        for(int x = 1; x < draw.cols-1; ++x)
        {
            if(mrk.at<int>(y, x) == 1) 
            {
                draw.at<Vec3b>(y, x) += Vec3b(0, 100, 0);
                if(mrk.at<int>(y, x-1) != 1 || mrk.at<int>(y, x+1) != 1 ||
                   mrk.at<int>(y-1, x) != 1 || mrk.at<int>(y+1, x) != 1) 
                    draw.at<Vec3b>(y, x) += Vec3b(0, 0, 100);
            }
        }
        
        circle(draw, Point(mp[0], mp[1]), 8, Scalar(255, 255, 255), 2, CV_AA);

        imshow("draw", draw);
        char c = waitKey(1);
        
        if(c == 27) break; 
        if(c == 10) {
            imidold = -1;
            Mat mask(in.size(), CV_8UC1, Scalar(0));
            for(int y = 1; y < draw.rows-1; ++y)
            for(int x = 1; x < draw.cols-1; ++x)
            {
                if(mrk.at<int>(y, x) == 1) 
                {
                    mask.at<uint8_t>(y, x) = 255;
                }
            }
            ostringstream outfn;
            string::size_type dot = fileNames[imid].find_last_of('.');
            if(dot == string::npos) outfn<<fileNames[imid].substr(0, dot)<<"_mask";
            else outfn<<fileNames[imid].substr(0, dot)<<"_mask"<<fileNames[imid].substr(dot);
            imwrite(outfn.str(), mask);
            
//            imid++; if(imid >= fileNames.size()) imid = 0;
            imid = ++imid % (fileNames.size() - 0);
        }
    }

    return 0;
}
