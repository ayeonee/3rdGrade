
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void calc_histo(const Mat& image, Mat& hist/*hist 객체로 받음*/, int bins, int range_max = 256) {
	int histSize[] = { bins };//크기선언
	float range[] = { 0,(float)range_max };//배열 객체 선언
	int channels[] = { 0 };//채널 배열 선언
	const float* ranges[] = { range };//range를 다시 배열로(2차원)

	calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges);
	//사진불러오고, 사진갯수, 채널이 배열로 들어가야함(1채널),  마스크(사용 x 여서 행렬하나 넣어줌), hist 인자를 반환하는 배열, 히스토그램에 대한 갯수,  히스토그램의 크기(배열로만들어야함), 표현되어야할 범위 설정(2차원배열),
}

void draw_histo(Mat hist, Mat& hist_img, Size size = Size(256, 200)) {
	hist_img = Mat(size, CV_8U, Scalar(255)); //배경색 흰색
	float bin = (float)hist_img.cols / hist.rows; //한단계당 넓이계산
	normalize(hist, hist, 0, hist_img.rows, NORM_MINMAX); //정규화, MINMAX=그래프높이값 정하려고

	for (int i = 0; i < hist.rows; i++) {//실제로 그림 그리기
		float start_x = i * bin; //시작되는 x 축(명암값)과 끝나는 x축의 위치값
		float end_x = (i + 1) * bin;
		Point2f pt1(start_x, 0); //사각형으로 만들라고
		Point2f pt2(end_x, hist.at<float>(i)); //해당위치의 y값(빈도수)불러옴

		if (pt2.y > 0) {
			rectangle(hist_img, pt1, pt2, Scalar(0), -1);
		}
	}
	flip(hist_img, hist_img, 0); //히스토그램 뒤집기
}

int main() {
	Mat image = imread("../bit_test.jpg", IMREAD_GRAYSCALE);
	CV_Assert(!image.empty());

	Mat hist, hist_img;
	calc_histo(image, hist, 256);
	cout << hist.t() << endl;
	draw_histo(hist, hist_img);
	cout << hist.t() << endl; //정규화후 

	imshow("image", image);
	imshow("hist_img", hist_img);
	waitKey();
	return 0;
}