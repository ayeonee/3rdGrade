#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

void calc_histo(const Mat& image, Mat& hist, int bins, int range_max = 256) {
	int histSize[] = { bins };
	float range[] = { 0,(float)range_max };
	int channels[] = { 0 };
	const float* ranges[] = { range };

	calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges);
}

void draw_histo(Mat hist, Mat& hist_img, Size size = Size(256, 200)) {
	hist_img = Mat(size, CV_8U, Scalar(255));
	float bin = (float)hist_img.cols / hist.rows;
	normalize(hist, hist, 0, hist_img.rows, NORM_MINMAX);
	for (int i = 0; i < hist.rows; i++) {
		float start_x = i * bin;
		float end_x = (i + 1) * bin;
		Point2f pt1(start_x, 0);
		Point2f pt2(end_x, hist.at<float>(i));

		if (pt2.y > 0) {
			rectangle(hist_img, pt1, pt2, Scalar(0), -1);
		}
	}
	flip(hist_img, hist_img, 0);
}

int search_valuesIdx(Mat hist, int bias = 0/*출발할 위치(0에서 시작할지 마지막에서 시작할지)*/) {
	for (int i = 0; i < hist.rows; i++) {
		int idx = abs(bias - i); //절댓값 이용
		if (hist.at<float>(idx) > 0) {
			return idx;
		}//화소에 대한 밝기값 반환
	}
	return -1;
}

int main() {
	Mat image = imread("../bit_test.jpg", IMREAD_GRAYSCALE);
	CV_Assert(!image.empty());

	Mat hist, hist_dst, hist_img, hist_dst_img;
	int histsize = 64, ranges = 256; //화소
	calc_histo(image, hist, histsize, ranges);

	float bin_width = (float)ranges / histsize; //막대가 차지하는 크기
	int low_value = (int)(search_valuesIdx(hist, 0) * bin_width); //최소 화소값
	int high_value = (int)(search_valuesIdx(hist, hist.rows - 1) * bin_width); //최대 화소값

	int d_value = high_value - low_value;
	Mat dst = (image - low_value) * 255 / d_value;


	calc_histo(dst, hist_dst, histsize, ranges);
	draw_histo(hist, hist_img);
	draw_histo(hist_dst, hist_dst_img);

	imshow("image", image);
	imshow("hist_img", hist_img);
	imshow("dst", dst);
	imshow("hist_dst_img", hist_dst_img);

	waitKey();
	return 0;
}