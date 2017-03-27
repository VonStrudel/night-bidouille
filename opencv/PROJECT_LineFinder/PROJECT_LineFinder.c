#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>


using namespace cv;
using namespace std;
void update_trackbar(int, void*)
{
}
int main(int argc, char* argv[]) {
	double dWidth, dHeight;
	int stop = 0;
	int col_h = 0,col_s=0, col_v=0;
	int tolerance =0;
	Point p1 = Point(10,10);
	Point p2 = Point(100,100);
	Mat frame; // contiendra une image
	VideoCapture cap(0); // Ouverture de la camera
	if(!cap.isOpened()) // Verification de la bonne ouverture de la camera
	{

		cout << "Couldn't open cam" << endl;
		return -1;
	}

	dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);	// Obtention de la largeur et de la
	dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);	// hauteur de l'image.
	cout <<"Taille de l'image :" << dWidth << "x" << dHeight << " pixels"<< endl; // Affichage
	int hsvl = 0;
	namedWindow("Raw", CV_WINDOW_AUTOSIZE); // Fenetre qui affichera l'image sans modif 
	namedWindow("BitOf", CV_WINDOW_AUTOSIZE); // Le bout de l'image qu'on analyse
	namedWindow("Config", CV_WINDOW_AUTOSIZE); //Toutes les trackbars/trucs a cocher, etc
	namedWindow("BitOf_Calculated", CV_WINDOW_AUTOSIZE);
	namedWindow("Thresholded", CV_WINDOW_AUTOSIZE);
	namedWindow("Canny", CV_WINDOW_AUTOSIZE);
	createTrackbar( "X_P1", "Config", &p1.x, 640, update_trackbar);
	createTrackbar( "X_P2", "Config", &p2.x, 640, update_trackbar);
	createTrackbar( "Y_P1", "Config", &p1.y, 480, update_trackbar);
	createTrackbar( "Y_P2", "Config", &p2.y, 480, update_trackbar);
	//createTrackbar( "H", "Config", &col_h, 179, update_trackbar);
	//createTrackbar( "S", "Config", &col_s, 255, update_trackbar);
	//createTrackbar("V/L", "Config", &col_v, 255, update_trackbar);
	//createTrackbar("HSV0HLS1","Config", &hsvl, 1 , update_trackbar);
	createTrackbar( "TOLERANCE", "Config", &tolerance, 100, update_trackbar);

	while(stop != 1)
	{
		if(!cap.read(frame)) // On lit une frame dans la capture. Si l'operation renvoie false, y'a eu un probleme
		{
			cout << "Couldn't read one frame. Continuing"<< endl;
			continue;
		}
		Mat bitof(frame, Rect(p1,p2)); //on recupere le bout qu'on va analyser
		imshow("BitOf", bitof); // on l'affiche
		rectangle(frame,p1,p2, Scalar(0,0,255)); ////on affiche la zone analysée
		//erode dilate dilate erode
		Mat bitof_calculated;
		//Scalar low_col = Scalar(col_h-tolerance, col_s-tolerance, col_v-tolerance);
		//Scalar up_col = Scalar(col_h+tolerance, col_s+tolerance, col_v+tolerance);
		//inRange(bitof_hsv,low_col, up_col, bitof_calculated);


		//en dessous :  on préarrange l'image tiens
		cvtColor(bitof, bitof_calculated, CV_RGB2GRAY); // on passe en niveaux de gris
		GaussianBlur(bitof_calculated,bitof_calculated, Size(9,9),2,2); // on floute
                Mat bitof_baw;
		// Ici on essaie de bien séparer la ligne du fond
		//adaptiveThreshold(bitof_calculated, bitof_baw, 255, ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY_INV, 3, 2);
		threshold(bitof_calculated,bitof_baw, 0, 255, THRESH_BINARY_INV | THRESH_OTSU); // on utilise un seuil otsu (adaptatif) inversé (on veut la ligne nwar). Note : la tolérance est ignorée vu que c'est auto donc on  met 0	
		//Canny(bitof_calculated,bitof_baw, tolerance, tolerance*3,3);
		//erode(bitof_baw, bitof_baw, element);
		imshow("Canny", bitof_baw);
		Mat bitofbitof = bitof_baw.row(25);
		int nCols = bitofbitof.cols * bitofbitof.channels();
		uchar*p = bitofbitof.ptr<uchar>(0);
		//cout <<nCols;
		char old_p = p[0];
		int xun, xdeu, yun,ydeu;
		for(int i = 0;i< nCols; i++)
		{
			if(p[i]==255)
			{
				if(old_p == 0)
					xun = i;
				old_p = 1;
			}
			else
			{
				if(old_p == 1)
					xdeu = i;
				old_p = 0;
			}
		}
		circle(frame, Point(p1.x + xun, p1.y + 25),5,Scalar(0,0,255),-1,8);
		circle(frame, Point(p1.x + xdeu, p1.y + 25),5,Scalar(0,255,0),-1,8);
		circle(frame, Point(p1.x + (xun+xdeu)/2, p1.y + 25), 7, Scalar(255,0,0), -1,8);
		imshow("Raw", frame); // On affiche la frame raw

		imshow("BiBi", bitofbitof);
		//erode(bitof_calculated, bitof_calculated,Size(9,9)); 
		//dilate(bitof_calculated,bitof_calculated);
		cout <<endl;//<< tolerance << endl;
		//cvLogPolar(&bitof_calculated, &bitof_calculated, Point((p1.x+p2.x)/2, (p1.y+p2.y)/2), 255, CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS);
		imshow("BitOf_Calculated", bitof_calculated);

		if(waitKey(1) == 27)
		{
			cout << "Arrêt du programme :  Echap pressé par l'utilisateur" << endl;
			stop = 1;
		}
	}

	return 0;
}
