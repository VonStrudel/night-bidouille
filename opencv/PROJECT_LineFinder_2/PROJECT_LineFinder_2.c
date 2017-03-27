#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

#define ERROR_NO_CAM -2
using namespace std;
using namespace cv;

void update_trackbar(int, void*)
{
}

int main(int argc, char* argv[])
{
	VideoCapture cap(0);
	if(!cap.isOpened())
		return ERROR_NO_CAM;
	int stop = 0;

	double dWidth, dHeight;
	dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);


	cout << "Taille de l'image : w=" << dWidth <<";h=" <<dHeight<<";\n";

	namedWindow("Debug1", CV_WINDOW_AUTOSIZE);
	namedWindow("CameraFeedback", CV_WINDOW_AUTOSIZE);

	Mat frame;

	while(1)
	{

		cap.read(frame);
		if(!cap.read(frame))
		{
			cout << "Couldn't read one frame. Skipping.\n";
			continue;
		}
		imshow("CameraFeedback", frame);

		Mat grey;//= Mat::zeros(frame.size(), frame.type());//
		cvtColor(frame,grey,CV_BGR2GRAY);///Passage en niveaux de gris


		Mat blured;// = Mat::zeros(grey.size(), grey.type());//
		GaussianBlur(grey, blured, Size(9,9), 2,2);///Floutage gaussien particulierement adapte au thresholding otsu utilise apres

		Mat thresholded;// =  Mat::zeros(blured.size(), blured.type());//
		threshold(blured, thresholded, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);//thresholding otsu assez efficace

		imshow("Debug1", thresholded);

		if(waitKey(1) == 27) // NE PAS OUBLIER CELA NE PAS OUBLIER CELA NE PAS OUH BLI AIIII
                {
                        cout << "Arret du programme :  Echap presse© par l'utilisateur" << endl;
                        stop = 1;
                }

	}
}
