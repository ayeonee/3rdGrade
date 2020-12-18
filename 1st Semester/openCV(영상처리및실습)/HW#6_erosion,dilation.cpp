#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

bool check_match(Mat img, Point start, Mat mask, int mode = 0)
{
    for (int u = 0; u < mask.rows; u++)
    {
        for (int v = 0; v < mask.cols; v++) {
            Point pt(v, u); 
            int m = mask.at<uchar>(pt); 
            int p = img.at<uchar>(start + pt); 

            bool ch = (p == 255);
            if (m == 1 && ch == mode) 
            {
                return false;
            }
        }

    }  return true;
}

void erosion(Mat img, Mat& dst, Mat mask) {

    dst = Mat(img.size(), CV_8U, Scalar(0));
    if (mask.empty()) {
        mask = Mat(3, 3, CV_8UC1, Scalar(1));
    }
    Point center = mask.size() / 2;
    for (int i = center.y; i < img.rows - center.y; i++)
    {
        for (int j = center.x; j < img.cols - center.x; j++)
        {
            Point start = Point(j, i) - center;
            bool check = check_match(img, start, mask, 0);
            dst.at<uchar>(i, j) = (check) ? 255 : 0;
        }
    }
}

void dilation(Mat img, Mat& dst, Mat mask)
{
    dst = Mat(img.size(), CV_8U, Scalar(0));
    if (mask.empty()) {
        mask = Mat(3, 3, CV_8UC1, Scalar(1));
    }
    Point center = mask.size() / 2;
    for (int i = center.y; i < img.rows - center.y; i++)
    {
        for (int j = center.x; j < img.cols - center.x; j++)
        {
            Point start = Point(j, i) - center;
            bool check = check_match(img, start, mask, 1);
            dst.at<uchar>(i, j) = (check) ? 0 : 255;
        }
    }
}

int main(int argc, const char* argv[])
{
    Mat image = imread("../leaf.jpg", IMREAD_GRAYSCALE);
    CV_Assert(image.data);

    Mat th_img, dst1;
    threshold(image, th_img, 160, 255, THRESH_BINARY); 

    uchar data[] = {
        0,1,0,
        1,1,1,
        0,1,0
    };

    Mat mask(3, 3, CV_8UC1, data);

    erosion(th_img, dst1, (Mat)mask);
    erosion(dst1, dst1, (Mat)mask);
    erosion(dst1, dst1, (Mat)mask);
    erosion(dst1, dst1, (Mat)mask);
    erosion(dst1, dst1, (Mat)mask);
    erosion(dst1, dst1, (Mat)mask);
    dilation(dst1, dst1, (Mat)mask);
    dilation(dst1, dst1, (Mat)mask);
    dilation(dst1, dst1, (Mat)mask);
    dilation(dst1, dst1, (Mat)mask);
    dilation(dst1, dst1, (Mat)mask);
    dilation(dst1, dst1, (Mat)mask);

    imshow("image", image);
    imshow("th_img", th_img);
    imshow("dst1", dst1);

    waitKey(0);
    return 0;

}