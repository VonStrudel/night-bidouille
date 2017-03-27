#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"

#include <iostream>

using namespace cv;
using namespace std;
int main(){
	int running = 1; //gere la boucle principale
	Mat rawFrame; //matrice contenant l'image non traite
	Mat grayFrame;
	Mat tempFrame;
	int xBoard = 11;
	int yBoard = 12;
	Size chessPatern(xBoard,yBoard);
	vector<Point2f> corners;
	Point2f dst[4] = {Point2f(0,0), Point2f(300,0), Point2f(0,300), Point2f(300,300)};
	Point2f src[4];
	bool chessBoardFound;
	int frames = 0;
	Mat perspective;
	VideoCapture cap(0);
	if(!cap.isOpened()){
		cout << "Couldn't open cam" << endl;
		return -1;
	}

	namedWindow("W_Raw", CV_WINDOW_AUTOSIZE); //creation de la fenetre qui contient l'image non traité
//	namedWindow("W_Gray", CV_WINDOW_AUTOSIZE); //fenetre qui affiche l'image en 8bit nuances de gris
	namedWindow("W_Temp", CV_WINDOW_AUTOSIZE);
	while(running == 1){
		if(!cap.read(rawFrame)){
			cout << "Une image n'a pas pu être lue" << endl;
			continue;
		}

		cvtColor(rawFrame, grayFrame, CV_BGR2GRAY);
		if(!chessBoardFound){
			chessBoardFound = findChessboardCorners(grayFrame, chessPatern, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_FAST_CHECK);
			frames = 0;

		cout << chessBoardFound << endl;
		src[0] = corners.at(131);
		src[1] = corners.at(10);
		src[2] = corners.at(121);
		src[3] = corners.at(0);
		perspective = getPerspectiveTransform(src,dst);
		}
		warpPerspective(rawFrame,tempFrame, perspective,Size(300,300), INTER_LINEAR);
		
		/*if(chessBoardFound){
			cornerSubPix(grayFrame, corners, chessPatern, Size(-1,-1), TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
			drawChessboardCorners(rawFrame, chessPatern, corners, 1 );
		}*/

//		imshow("W_Gray", grayFrame); //image en 8bit graw
		imshow("W_Raw", rawFrame); //affiche dans la fenetre W_Raw la matrice rawFrame
		imshow("W_Temp", tempFrame);
		if(waitKey(1) == 27){
			cout << "arret du programme demande par l'utilisateur" << endl;
			running = 0;
		}
		frames++;

	}
	return 0;
}
