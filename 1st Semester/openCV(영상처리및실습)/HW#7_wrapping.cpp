#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

uchar bilinear_value(Mat img, double x, double y)
{
    if (x >= img.cols - 1)
        x--;
    if (y >= img.rows - 1)
        y--;
    Point pt((int)x, (int)y);
    int A = img.at<uchar>(pt);
    int B = img.at<uchar>(pt + Point(0, 1));
    int C = img.at<uchar>(pt + Point(1, 0));
    int D = img.at<uchar>(pt + Point(1, 1));

    double alpha = y - pt.y;
    double beta = x - pt.x;
    int M1 = A + (int)cvRound(alpha * (B - A));
    int M2 = C + (int)cvRound(alpha * (D - C));
    int P = M1 + (int)cvRound(beta * (M2 - M1));

    return saturate_cast<uchar>(P);
}

void doWarping(Mat img, Mat& dst, vector<Rect> dstLines, vector<Rect> oriLines)
{
    dst = Mat(img.size(), img.type(), Scalar(0)); 
    Rect rt = Rect(0, 0, img.size().width, img.size().height); 

    for (int i = 0; i < dst.rows; i++)
    {
        for (int j = 0; j < dst.cols; j++)
        {
            double x = j;
            double y = i;

            double tx = 0; 
            double ty = 0;
            double totalWeight = 0; 

            for (int k = 0; k < dstLines.size(); k++) 
            {
                Point2d P = Point2d(dstLines[k].x, dstLines[k].y); 
                Point2d Q = Point2d(dstLines[k].width, dstLines[k].height); 
                Point2d _P = Point2d(oriLines[k].x, oriLines[k].y); 
                Point2d _Q = Point2d(oriLines[k].width, oriLines[k].height);

                double u = ((x - P.x) * (Q.x - P.x) + (y - P.y) * (Q.y - P.y)) / (pow(Q.x - P.x, 2) + pow(Q.y - P.y, 2)); 
                double h = ((y - P.y) * (Q.x - P.x) - (x - P.x) * (Q.y - P.y)) / (sqrt(pow(Q.x - P.x, 2) + pow(Q.y - P.y, 2))); 
                double _x = _P.x + u * (_Q.x - _P.x) - ((h * (_Q.y - _P.y)) / (sqrt(pow(_Q.x - _P.x, 2) + pow(_Q.y - _P.y, 2))));
                double _y = _P.y + u * (_Q.y - _P.y) + ((h * (_Q.x - _P.x)) / (sqrt(pow(_Q.x - _P.x, 2) + pow(_Q.y - _P.y, 2))));

                double d = 0;
                if (u < 0)
                {
                    d = sqrt(pow(x - P.x, 2) + pow(y - P.y, 2));
                }
                else if (u > 1)
                {
                    d = sqrt(pow(x - Q.x, 2) + pow(y - Q.y, 2));
                }
                else
                {
                    d = abs(h); 
                }

                double a = 0.005; 
                double b = 2.0;
                double p = 0.5;
                double weight = pow(pow(sqrt(pow(Q.x - P.x, 2) + (pow(Q.y - P.y, 2))), p) / (a + d), b);


                tx = tx + (_x - x) * weight;
                ty = ty + (_y - y) * weight;
                totalWeight += weight;
            }

            double X = x + tx / totalWeight;
            double Y = y + ty / totalWeight;

            if (rt.contains(Point2d(X, Y))) 
            {
                dst.at<uchar>(i, j) = bilinear_value(img, X, Y);
            }
            else
            {
                dst.at<uchar>(i, j) = 0;
            }
        }
    }
}

int main(int argc, const char* argv[])
{
    Mat image = imread("../lena.jpg", IMREAD_GRAYSCALE);
    CV_Assert(image.data);

    Mat dst;

    vector<Rect> dstLine = { Rect(226, 286, 120, 160) ,Rect(420, 460, 320, 360),Rect(0,0,512,0),Rect(512,0,512,512), Rect(512,512,0,512),Rect(0,512,0,0) };
    vector<Rect> oriLine = { Rect(226, 316, 120, 160),Rect(420, 460, 320, 380),Rect(0,0,512,0),Rect(512,0,512,512), Rect(512,512,0,512),Rect(0,512,0,0) };

    doWarping(image, dst, dstLine, oriLine);
    line(image, Point(226, 286), Point(120, 160), Scalar(0), 1); 
    line(image, Point(226, 316), Point(120, 160), Scalar(0), 1); 
    line(image, Point(420, 460), Point(320, 360), Scalar(255), 1);
    line(image, Point(420, 460), Point(320, 380), Scalar(255), 1);

    imshow("image", image);
    imshow("dst", dst);

    waitKey(0);
    return 0;
}