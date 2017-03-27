#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"

#include <iostream>

using namespace cv;
using namespace std;
int main(){
	bool chessBoardFound;
	int running = 1; //gere la boucle principale
	int xBoard = 11;
	int yBoard = 11;
	int imgSizeFinal = 500; //taille de l'image finale
	int frames = 0;
	Mat rawFrame; //matrice contenant l'image non traite
	Mat grayFrame; //matrice contenant en niveaux de gris
	Mat tempFrame; //matrice temporaire
	Mat perspective; //matrice de perspective
	Size chessPatern(xBoard,yBoard); //taille du board recherche
	vector<Point2f> corners; //liste des coins trouvees findChessboardCorner
	Point2f dst[4] = {  Point2f(0,0), Point2f(imgSizeFinal,0), Point2f(0,imgSizeFinal), Point2f(imgSizeFinal, imgSizeFinal )}; //liste des coins de l'image rogne (300 arbitraire)

	VideoCapture cap(0); //allume la cam et get le flux

	if(!cap.isOpened()){
		cout << "Couldn't open cam" << endl;
		return -1;
	}

	namedWindow("W_Raw", CV_WINDOW_AUTOSIZE); //creation de la fenetre qui contient l'image non traité
	namedWindow("W_Temp", CV_WINDOW_AUTOSIZE); //affiche la fenetre finie

	while(running == 1){

		if(!cap.read(rawFrame)){
			cout << "Une image n'a pas pu être lue" << endl;
			continue;
		}

		cvtColor(rawFrame, grayFrame, CV_BGR2GRAY); //convertie l'image en noir et blanc

		if(!chessBoardFound){
			chessBoardFound = findChessboardCorners(grayFrame, chessPatern, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_FAST_CHECK); // trouve  les corners
			Point2f src[] = {corners.at(xBoard * yBoard -1), corners.at(xBoard - 1), corners.at(xBoard*(yBoard - 1)), corners.at(0)};
			perspective = getPerspectiveTransform(src,dst);
		}

		if(chessBoardFound){
			warpPerspective(rawFrame,tempFrame, perspective,Size(imgSizeFinal+1000,imgSizeFinal), INTER_LINEAR);
			cornerSubPix(grayFrame, corners, chessPatern, Size(-1,-1), TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
			drawChessboardCorners(rawFrame, chessPatern, corners, 1 );
		}

		imshow("W_Raw", rawFrame); //affiche dans la fenetre W_Raw la matrice rawFrame
		imshow("W_Temp", tempFrame);

		if(waitKey(1) == 27){
			cout << "arret du programme demande par l'utilisateur" << endl;
			running = 0;
		}
	}
	return 0;
}
