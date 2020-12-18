#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

//차현상 구현하기
int main()
{
	Mat image1 = imread("../test1.jpg");
	Mat image2 = imread("../test2.jpg");
	CV_Assert(image1.data && image2.data);

	Mat image1_gray, image2_gray, diff, output_mask, masked_image;
	//color값으로 하는 것은 채널3개로 처리해야해서 불편. 
	cvtColor(image1, image1_gray, COLOR_BGR2GRAY); //이미지 그레이스케일로 변환
	cvtColor(image2, image2_gray, COLOR_BGR2GRAY);

	output_mask = Mat(image1.size(), CV_8U, Scalar(0));
	image1.copyTo(masked_image); //masked image는 원본이미지 그대로, 나중에 원본도 출력해주기 위해 따로 작성.

	int threshold = 50; //두개의 차분값이 threshold 이상이어야 함.
	int width = image1.size().width; //이미지의 너비
	int height = image1.size().height; //이미지의 높이

	absdiff(image1_gray, image2_gray, diff); //두 영상을 차분값의 절대값을 넣어줌.

	//차분값에 해당하는 영상에 루프문 돌림. 마스크 영상 생성.
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			if (diff.at<uchar>(j, i) >= threshold) //차분값 영상의 픽셀값이 threshold 넘으면 255
			{
				output_mask.at<uchar>(j,i) = 255;
			}
			else
			{
				output_mask.at<uchar>(j, i) = 0;
			}
		}
	}

	//마스크의 하얀 부분 제외한 부분들은 0으로 처리해서 실제 컬러가 있는 모습으로 처리하게 함.
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			if (output_mask.at<uchar>(j, i) >0) //마스크의 특정부분이 0보다 크면 아무것도 안함.
			{
			}
			else //0과 같은 경우라면 masked image의 값을 0으로 바꿔줌. rgb 3개 값 각각 0으로 처리.
			{
				masked_image.at<Vec3b>(j, i)[0] = 0; //b
				masked_image.at<Vec3b>(j, i)[1] = 0; //g
				masked_image.at<Vec3b>(j, i)[2] = 0; //r
			}
		}
	}

	imshow("image1", image1);
	imshow("image2", image2);
	imshow("output_mask", output_mask);
	imshow("masked_image", masked_image); 

	waitKey(0);
	return 0;
}