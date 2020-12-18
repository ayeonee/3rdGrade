#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

uchar bilinear_value(Mat img, double x, double y) //양선형 보간법, 좀 더 부드러운 영상을 만들기 위해
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

void doWarping(Mat img, Mat& dst, vector<Rect> dstLines, vector<Rect> oriLines) //반환값 필요없어서 void , 제어선을 받아야하는데  시작점(P)과 끝점(Q)의 각각 x,y좌표를 넣어야해서 4개를 한번에 받을 수 있는 Rect함수 사용 
{
    dst = Mat(img.size(), img.type(), Scalar(0)); //목적영상의 크기,타입 지정
    Rect rt = Rect(0, 0, img.size().width, img.size().height); //원본영상 위치값 구하고 목적에 갖다놔야하는데, 만약 대응하는 픽셀이 없다면 없는 부분은 출력을 안하거나 검게 칠하는 코드를 넣어야함. 원본 영상 안에 새로만든 좌표가 포함하는가를 판단하기 위해 Rect 만듦.

    for (int i = 0; i < dst.rows; i++)
    {
        for (int j = 0; j < dst.cols; j++)
        {
            double x = j;
            double y = i;

            double tx = 0; //가중치에 대한 값
            double ty = 0;
            double totalWeight = 0; //전체 가중치에 대한 값(여러개의 가중치에 대한 누적값), 픽셀에 따른 가중치를 계산하게 됨 

            for (int k = 0; k < dstLines.size(); k++) //여러개의 제어선들이 생길 수 있기 때문에 모든 제어선들에 대해 가중치를 정하고 실제 대응하는 원본의 픽셀값을 구해야함.
            {
                Point2d P = Point2d(dstLines[k].x, dstLines[k].y); //제어선에 대한 값들을 P와Q로바꿈, 목적영상의 제어선의 P선언
                Point2d Q = Point2d(dstLines[k].width, dstLines[k].height); // 너비로 표현이 되어있음
                Point2d _P = Point2d(oriLines[k].x, oriLines[k].y); //원본영상 제어선의 _P
                Point2d _Q = Point2d(oriLines[k].width, oriLines[k].height); //원본영상 제어선의 _Q

                //1) u
                double u = ((x - P.x) * (Q.x - P.x) + (y - P.y) * (Q.y - P.y)) / (pow(Q.x - P.x, 2) + pow(Q.y - P.y, 2)); //pow=제곱
                //2)변위 h
                double h = ((y - P.y) * (Q.x - P.x) - (x - P.x) * (Q.y - P.y)) / (sqrt(pow(Q.x - P.x, 2) + pow(Q.y - P.y, 2))); //sqrt=루트
                //3) 대응픽셀위치계산
                double _x=_P.x+u*(_Q.x-_P.x)-((h*(_Q.y-_P.y))/ (sqrt(pow(_Q.x - _P.x, 2) + pow(_Q.y - _P.y, 2))));
                double _y = _P.y + u * (_Q.y - _P.y) + ((h * (_Q.x - _P.x)) / (sqrt(pow(_Q.x - _P.x, 2) + pow(_Q.y - _P.y, 2))));
                //4)d(픽셀과 제어선의 거리 계산
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
                    d = abs(h); //abs=절댓값
                }
                // weight 가중치 계산
                double a = 0.001;
                double b = 2.0;
                double p = 0.75;
                double weight = pow(pow(sqrt(pow(Q.x - P.x, 2) + (pow(Q.y - P.y, 2))), p) / (a + d), b);

                //tx,ty
                tx = tx + (_x - x) * weight;
                ty = ty + (_y - y) * weight;
                totalWeight += weight;
            }
            //실제 가중치가 적용된 x,y좌표 계산
            double X = x + tx / totalWeight;
            double Y = y + ty / totalWeight;

            if (rt.contains(Point2d(X, Y))) //X,Y가 원본 영상에 있는지 검사
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

    vector<Rect> dstLine = { Rect(118, 144, 139, 154) ,Rect(0,0,512,0),Rect(512,0,512,512), Rect(512,512,0,512),Rect(0,512,0,0) }; //목적영상의 제어선 라인, 만약 단일 제어선이라면 모든 픽셀이 그 제어선 기준으로 워핑되게됨(사진 전체가 돌아가게 됨), 이를 막으려면 목적영상의 끝에 제어선들을 추가해서 돌아가지 않도록 해야 함, Rec(시작좌표, 종료좌표)
    vector<Rect> oriLine = { Rect(118, 154, 139, 154),Rect(0,0,512,0),Rect(512,0,512,512), Rect(512,512,0,512),Rect(0,512,0,0) }; //원본영상의 제어선 라인

    doWarping(image, dst, dstLine, oriLine);
    line(image, Point(118, 145), Point(139, 154), Scalar(0),1); //목적영상의 제어선에 관한 좌표값
    line(image, Point(118, 154), Point(139, 154), Scalar(0),1); //원본영상의 제어선에 관한 좌표값


    imshow("image", image);
    imshow("dst", dst);

    waitKey(0);
    return 0;
} 