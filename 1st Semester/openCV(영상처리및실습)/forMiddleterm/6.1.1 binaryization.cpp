#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main() {
	Mat image = imread("../olaf.jpg", IMREAD_GRAYSCALE);
	CV_Assert(!image.empty());

	Mat thresh_1, thresh_2;
	threshold(image, thresh_1, 127, 255, THRESH_BINARY);
	threshold(image, thresh_2, 127, 255, THRESH_BINARY_INV);

	imshow("image", image);
	imshow("thresh_1", thresh_1);
	imshow("thresh_2", thresh_2);
	waitKey();
	return 0;
}