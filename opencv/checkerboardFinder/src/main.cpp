#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

int main(){
	int running = 1; //gere la boucle principale
	Mat rawFrame; //matrice contenant l'image non traite

	VideoCapture cap(0);
	if(!cap.isOpened()){
		cout << "Couldn't open cam" << endl;
		return -1;
	}

	namedWindow("W_Raw", CV_WINDOWS_AUTOSIZE); //creation de la fenetre qui contient l'image non traité

	while(running == 1){
		if(!cap.read(rawFrame)){
			cout << "Une image n'a pas pu être lue" << endl;
			continue;
		}

		imshow("W_Raw", rawFrame); //affiche dans la fenetre W_Raw la matrice rawFrame

		if(waitKey(1) == 27){
			cout << "arret du programme demande par l'utilisateur" << endl;
			running = 0;
		}

		return 0;
	}
}
