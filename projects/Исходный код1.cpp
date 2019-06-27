//выделение границ



#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>
using namespace cv;
using namespace std;
IplImage* frame;


int x = 250, y = 280;
int a = 160, b = 140;
double i, j, k, l, sj, sk, sl, jmax, kmax, lmax;
double r = 10.0;//минимальное число уровней в классе
double L = 256.0;
double N = 307200.0;
double q;
vector<double> hist(256, 0);
Mat src1(Size(640, 480), CV_8UC1);

Mat src(Size(2 * a + 1, 2 * b + 1), CV_8UC1);

Mat src2(Size(2 * a + 1, 2 * b + 1), CV_8UC1);
Mat dst1(Size(2 * a + 1, 2 * b + 1), CV_8UC1);
vector<double> w(4, 0);//вер-ть принадлежности классу 
vector<double> m(4, 0);//средний уровень яркости класса
double mt = 0.0;//средний уровень яркости изображения
vector<double> p(256, 0);//вероятности уровней яркости

double sigma = 0.0;//целевая функция (межклассовая дисперсия)

double mij = a + b, mi, mj;
Mat mask;
CvConnectedComp comp;

vector<vector<Point> > contours;
vector<Vec4i> hierarchy;

void Otsu_3(Mat image, Mat image1);

void myMouseCallback(int event, int x0, int y0, int flags, void* param)
{


	switch (event){
	case CV_EVENT_MOUSEMOVE:
		break;

	case CV_EVENT_LBUTTONDOWN:
		printf("%d x %d\n", x0, y0);
		x = x0;
		y = y0;

		break;

	case CV_EVENT_LBUTTONUP:
		break;
	}
}


int main(int argc, char* argv[])
{
	// имя файла задаётся первым параметром
	char* filename = argc == 2 ? argv[1] : "TEST.avi";

	printf("[i] file: %s\n", filename);

	// окно для отображения картинки
	namedWindow("original", CV_WINDOW_AUTOSIZE);
	namedWindow("segment", CV_WINDOW_AUTOSIZE);
	namedWindow("DT", CV_WINDOW_AUTOSIZE);
	namedWindow("Components", CV_WINDOW_AUTOSIZE);

	// получаем информацию о видео-файле
	CvCapture* capture = cvCreateFileCapture(filename);
	cvSetMouseCallback("original", myMouseCallback, (void*)frame);





	while (1){
		// получаем следующий кадр
		frame = cvQueryFrame(capture);
		if (!frame) {
			break;
		}

		Mat src2(frame);

		imshow("original", src2);

		Rect roi(x - a / 3, y - b, 2 * a + 1, 2 * b + 1);

		cvSetImageROI(frame, roi);

		Mat src1(frame);

		cvResetImageROI(frame);



		Otsu_3(src1, src);
		//cout << jmax << " " << kmax << " " << lmax << " \n";
		for (i = 0; i < src1.rows; i++)// псевдораскраска
		{
			for (j = 0; j < src1.cols; j++)
			{
				if (kmax < src1.at<uchar>(i, j))  src.at<uchar>(i, j) = 0;
				else src.at<uchar>(i, j) = 255;
			}
		}
		medianBlur(src, src, 7);
		//GaussianBlur(src, src, Size(7, 7), 0, 0);

		//здесь нужно выделить все связные пятна и отобрать по размеру

		for (i = 0; i < src.rows; i++)//выбираем пятно ближе к центру
		{
			for (j = 0; j < src.cols; j++)
			{
				if (src.at<uchar>(i, j) == 0){
					if (abs(a - j) + abs(b - i) < mij) mij = abs(a - j) + abs(b - i);
					mi = i; mj = j; //ближайшая к центру точка черного сегмента
				}
			}
		}
		Point seed = (mj, mi);

		//cout << mj << " " << mi << "\n";

		//остальные черные пиксели делаем белыми


		imshow("segment", src);//отображаем сегментацию

		Mat dst = Mat::ones(src.rows, src.cols, CV_8UC1) * 255;


		findContours(src, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);


		

		for (i = 0; i < src.rows; i++)//инвертируем цвета
		{

		for (j = 0; j < src.cols; j++)
		{
		if (src.at<uchar>(i, j) == 0) src.at<uchar>(i, j) = 255;
		else src.at<uchar>(i, j) = 0;
		}
		}



		Scalar color(0, 0, 0);
		drawContours(dst, contours, -1, color, 1, 8);

	

		imshow("Components", dst);

		distanceTransform(dst, dst1, CV_DIST_L1, 3);//здесь нужно переделать



		normalize(dst1, dst1, 0.0, 1.0, NORM_MINMAX);

		imshow("DT", dst1);

		char c = cvWaitKey(25);
		if (c == 27) { // если нажата ESC - выходим
			break;
		}

	}
	cvDestroyAllWindows();
}

void Otsu_3(Mat image, Mat image1)
{
	double max = 0.0;


	for (k = 0; k <= 255; k++)// зануляем 
	{
		hist[k] = 0.0;
		p[k] = 0.0;
	}
	for (i = 0; i < image.rows; i++)// считаем гистограмму
	{
		for (j = 0; j < image.cols; j++)
		{
			hist[image.at<uchar>(i, j)]++;
		}
	}

	for (i = 0; i <= 255; i++)//считаем p[i]
	{
		p[i] = hist[i] / N;

	}

	for (j = 0; j <= 255; j++)//считаем mt
	{
		mt += j*p[j] / L;
	}


	sj = j = 20;
	sk = k = 40;
	sl = l = 60;



	w[0] = w[1] = w[2] = w[3] = 0;
	for (q = 0; q <= j - 1; q++) w[0] += p[q];
	for (q = j; q <= k - 1; q++) w[1] += p[q];
	for (q = k; q <= l - 1; q++) w[2] += p[q];
	for (q = l; q <= 255; q++) w[3] += p[q];


	m[0] = m[1] = m[2] = m[3] = 0;
	if (w[0] != 0)for (q = 0; q <= j - 1; q++) m[0] += q*p[q] / w[0];
	else m[0] = 0;
	if (w[1] != 0)for (q = j; q <= k - 1; q++) m[1] += q*p[q] / w[1];
	else m[1] = 0;
	if (w[2] != 0)for (q = k; q <= l - 1; q++) m[2] += q*p[q] / w[2];
	else m[2] = 0;
	if (w[3] != 0)for (q = l; q <= 255; q++) m[3] += q*p[q] / w[3];
	else m[3] = 0;


	for (j = r; j <= k - r - 1; j += 10)
	{
		for (k = j + r; k <= l - r - 1; k += 10)
		{
			for (l = k + r; l <= 255 - r - 1; l += 10)
			{

				if (l != sl && k == sk && j == sj)//пересчет C3 C4
				{


					w[2] = w[3] = m[2] = m[3] = 0;

					for (q = k; q <= l - 1; q++) w[2] += p[q];

					if (w[2] != 0)for (q = k; q <= l - 1; q++) m[2] += q*p[q] / w[2];
					else m[2] = 0;

					for (q = l; q <= 255; q++) w[3] += p[q];


					if (w[3] != 0)for (q = l; q <= 255; q++) m[3] += q*p[q] / w[3];
					else m[3] = 0;

					sl = l;
				}

				if (l != sl && k != sk && j == sj)//пересчет С2 С3 С4
				{


					w[1] = w[2] = w[3] = m[1] = m[2] = m[3] = 0;

					for (q = j; q <= k - 1; q++) w[1] += p[q];

					if (w[1] != 0)for (q = j; q <= k - 1; q++) m[1] += q*p[q] / w[1];
					else m[1] = 0;

					for (q = k; q <= l - 1; q++) w[2] += p[q];

					if (w[2] != 0)for (q = k; q <= l - 1; q++) m[2] += q*p[q] / w[2];
					else m[2] = 0;

					for (q = l; q <= 255; q++) w[3] += p[q];

					if (w[3] != 0)for (q = l; q <= 255; q++) m[3] += q*p[q] / w[3];
					else m[3] = 0;

					sl = l;

					sk = k;
				}

				if (l != sl && k != sk && j != sj)//пересчет С1 С2 С3 С4
				{

					w[0] = w[1] = w[2] = w[3] = m[0] = m[1] = m[2] = m[3] = 0;

					for (q = 0; q <= j - 1; q++) w[0] += p[q];

					if (w[0] != 0)for (q = 0; q <= j - 1; q++) m[0] += q*p[q] / w[0];
					else m[0] = 0;

					for (q = j; q <= k - 1; q++) w[1] += p[q];

					if (w[1] != 0)for (q = j; q <= k - 1; q++) m[1] += q*p[q] / w[1];
					else m[1] = 0;

					for (q = k; q <= l - 1; q++) w[2] += p[q];

					if (w[2] != 0)for (q = k; q <= l - 1; q++) m[2] += q*p[q] / w[2];
					else m[2] = 0;

					for (q = l; q <= 255; q++) w[3] += p[q];

					if (w[3] != 0)for (q = l; q <= 255; q++) m[3] += q*p[q] / w[3];
					else m[3] = 0;

					sl = l;

					sk = k;

					sj = j;
				}

				sigma = 0;

				for (q = 0; q <= 3; q++) sigma += w[q] * (m[q] - mt)*(m[q] - mt);

				if (sigma >= max) {
					max = sigma;
					jmax = j;
					kmax = k;
					lmax = l;
				}

				//cout << max << "\n";

			}
		}
	}

	for (i = 0; i < image.rows; i++)// псевдораскраска
	{
		for (j = 0; j < image.cols; j++)
		{
			if (image.at<uchar>(i, j) <= jmax)  image1.at<uchar>(i, j) = 0;
			if (jmax < image.at<uchar>(i, j) && image.at<uchar>(i, j) <= kmax)  image1.at<uchar>(i, j) = 80;
			if (kmax < image.at<uchar>(i, j) && image.at<uchar>(i, j) <= lmax) image1.at<uchar>(i, j) = 160;
			if (lmax < image.at<uchar>(i, j))  image1.at<uchar>(i, j) = 255;
			//cout << i << " " << j << "\n";

		}
	}

}