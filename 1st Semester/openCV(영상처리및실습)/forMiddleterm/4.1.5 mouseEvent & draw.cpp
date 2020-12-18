#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
string title = "이벤트 그리기";
Mat image;

void onMouse(int event, int x, int y, int flags, void* param) {
    static Point pt(-1, -1);
    if (event == EVENT_RBUTTONDOWN) {
        if (pt.x < 0) pt = Point(x, y);  //시작좌표지정
        else {
            rectangle(image, pt, Point(x, y), Scalar(50), 2); //종료좌표지정, 그리기
            imshow(title, image);
            pt = Point(-1, -1);  //시작좌표 초기화
        }
    }
    else if (event == EVENT_LBUTTONDOWN) {
        if (pt.x < 0) pt = Point(x, y);
        else {
            Point2d pt2 = pt - Point(x, y);
            int radius = (int)sqrt(pt2.x * pt2.x + pt2.y * pt2.y); //두 좌표간 거리
            circle(image, pt, radius, Scalar(150), 2);
            imshow(title, image);
            pt = Point(-1, -1);
        }
    }
}
int main()
{
    image = Mat(400, 400, CV_8U, Scalar(255));
    imshow(title, image);
    setMouseCallback(title, onMouse,0);
    waitKey(0);
    return 0;
}