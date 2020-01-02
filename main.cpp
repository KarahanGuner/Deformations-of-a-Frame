#include <iostream>
#include <cmath>
#include <stdlib.h>

// Since this code uses variables while creating arrays it may not compile on some IDE's.
// Coded on CodeBlocks with GNU Compiler.

using namespace std;
int Nodes[100][2];
int EI[50];
int EA[50];
int DOFT[100][3];
int s = 1; // i increases 2 per loop, we needed something that increased by one. gives the number of members.
double loadmagnitude[3][50]; //loads type and its magnitude
int loaddegree[3][50]; //orientation of the load relative to local axis of the member it sits on
int loadmember[50]; //which member the load is on
double loaddistance[3][50]; //location of the force relative to start of the member it sits on
int nofl; // counts number of loads

void Input() {
    cout << "Before you start, give numbers to each member on the paper and enter them in that order." << endl;
    cout << "If there is distributed load enter where the load is as a separate member." << endl;
    cout << "Mind that order of coordinates you enter dictates that member's orientation.  " << endl;
	cout << "Dont forget to press Enter after each entry." << endl;
	cout << "Do not use brackets." << endl;
	char Done = 'n';
	for (int i = 0; i < 100; i+=2) {
		char restrX = 'n';
		char restrY = 'n';
		char restrRot = 'n';
		cout << "Enter first node koordinates for member " << s << ":" << endl;
		cin >> Nodes[i][0] >> Nodes[i][1];
		cout << "Is the first node for member " << s << " restricted in X direction? (Y/N)" << endl;
		cin >> restrX;
		if (restrX == 'Y' || restrX == 'y') {
			DOFT[i][0] = 1;
		}
		else {
			DOFT[i][0] = 0;
		}
		cout << "Is the first node for member " << s << " restricted in Y direction? (Y/N)" << endl;
		cin >> restrY;
		if (restrY == 'Y' || restrY == 'y') {
			DOFT[i][1] = 1;
		}
		else {
			DOFT[i][1] = 0;
		}
		cout << "Is the first node for member " << s << " restricted in against Rotation? (Y/N)" << endl;
		cin >> restrRot;
		if (restrRot == 'Y' || restrRot == 'y') {
			DOFT[i][2] = 1;
		}
		else {
			DOFT[i][2] = 0;
		}
		cout << "Enter second node koordinates for member " << s << ":" << endl;
		cin >> Nodes[i+1][0] >> Nodes[i+1][1];
		cout << "Is the second node for member " << s << " restricted in X direction? (Y/N)" << endl;
		cin >> restrX;
		if (restrX == 'Y' || restrX == 'y') {
			DOFT[i+1][0] = 1;
		}
		else {
			DOFT[i+1][0] = 0;
		}
		cout << "Is the second node for member " << s << " restricted in Y direction? (Y/N)" << endl;
		cin >> restrY;
		if (restrY == 'Y' || restrY == 'y') {
			DOFT[i+1][1] = 1;
		}
		else {
			DOFT[i+1][1] = 0;
		}
		cout << "Is the second node for member " << s << " restricted in against Rotation? (Y/N)" << endl;
		cin >> restrRot;
		if (restrRot == 'Y' || restrRot == 'y') {
			DOFT[i+1][2] = 1;
		}
		else {
			DOFT[i+1][2] = 0;
		}
		cout << "Enter EI(kNm^2) for member " << s << ":" << endl;
		cin >> EI[s - 1];
		cout << "Enter EA(kN) for member " << s << ":" << endl;
		cin >> EA[s - 1];
		cout << "Are you done? (Y/N) Entering Y will put you in load entering stage." << endl;
		cin >> Done;
		if (Done == 'Y' || Done == 'y') {
			break;
		}
		s++;
	}

    for(int i = 0; i < 50; i++){
        for(int j=0; j < 3 ; j++){
            loadmagnitude[j][i] = 0;
        }
    }
    for(int i = 0; i < 50; i++){
        for(int j=0; j < 3 ; j++){
            loaddegree[j][i] = 0;
        }
    }
    for(int i = 0; i<50;i++){
        loadmember[i] = 0;
    }
    for(int i = 0; i < 50; i++){
        for(int j=0; j < 3 ; j++){
            loaddistance[j][i] = 0;
        }
    }
	for(int i=0; i < 100; i++){ //to take inputs of the loads
        char aaa = 'n'; //to exit the loop
        char llll = 'a'; //to enter type of loading
        cout << "Is there any load unentered? Yes(y) or No(n)" << endl;
        cin >> aaa;
        if (aaa == 'N' || aaa == 'n') {
			break;
		}
		cout << "What is the type of loading? Use kN and m as units." << endl;
		cout << "For point load enter: p" << endl;
		cout << "For distributed load enter: d" << endl;
		cout << "For point moment enter: m" << endl;
		cin >> llll;
		if (llll == 'P' || llll == 'p') {
            cout << "At which member the load is on?" << endl;
            cin >> loadmember[i];
            cout << "How far is the load away from the start of the member?" << endl;
            cin >> loaddistance[0][i];
            cout << "What is the magnitude of this load?" << endl;
            cin >> loadmagnitude[0][i];
            cout << "If the load is downwards relative to member's local coordinates enter 0, if it is upwards enter 1" << endl;
            cin >> loaddegree[0][i];
		}
		if (llll == 'D' || llll == 'd') {
            cout << "At which member the load is on?" << endl;
            cin >> loadmember[i];
            cout << "What is the magnitude of this load?" << endl;
            cin >> loadmagnitude[1][i];
            cout << "If the load is downwards relative to member's local coordinates enter 0, if it is upwards enter 1" << endl;
            cin >> loaddegree[1][i];
		}
		if (llll == 'M' || llll == 'm') {
            cout << "At which member the load is on?" << endl;
            cin >> loadmember[i];
            cout << "How far is the moment away from the start of the member?" << endl;
            cin >> loaddistance[2][i];
            cout << "What is the magnitude of this load?" << endl;
            cin >> loadmagnitude[2][i];
            cout << "If the moment is counterclockwise enter 0, if it is clockwise enter 1" << endl;
            cin >> loaddegree[2][i];
		}
		nofl = nofl + 1;
	}
}

void Logic() {
	int DOFT2[100][3];
	int DOFT3[100][3];
	int DOFT4[100][3];
	for (int i = 0; i < 100; i++) { // equals DOFT2 TO DOFT. to always have a copy of DOFT
		for (int j = 0; j < 3; j++) {
			DOFT2[i][j] = DOFT[i][j];
		}
	}
	for (int i = 0; i < 100; i++) { // Creates DOFT2
		for(int j = 1; j < 100; j++){
			if (i + j < 100 && Nodes[i][0] == Nodes[i + j][0] && Nodes[i][1] == Nodes[i + j][1]) {
			DOFT2[i+j][0] = 99;
			DOFT2[i+j][1] = 99;
			DOFT2[i+j][2] = 99;
			}
		}
	}
	int _a = 0;
	int cF = 0; // to count free dofs
	int cR = 0; // to count restricted dofs
	int nodofs = 0; //number of dofs
	int noun = 0; //number of unique nodes
	for (int i = 0; i < 100; i++) { // Counts how many free dofs there are
		for (int j = 0; j < 3; j++) {
			if (DOFT2[i][j] == 0) {
				cF++;
			}
		}
	}
	for (int i = 0; i < 100; i++) { // Counts how many restricted dofs there are
		for (int j = 0; j < 3; j++) {
			if (DOFT2[i][j] == 1) {
				cR++;
			}
		}
	}
	nodofs = cF + cR;
	noun = nodofs / 3;

	int _cF = cF + 1; // to always have cF value stored. _cF is used to create numbers for restricted dofs.
	int _cC = 1; // to create numbers for free dofs.
	for (int i = 0; i < 100; i++) { // Creates DOFT3
		for (int j = 0; j < 3; j++) {
			if (DOFT2[i][j] == 1) {
				DOFT3[i][j] = -(_cF);
					_cF++;
			}
			if (DOFT2[i][j] == 0) {
				DOFT3[i][j] = _cC;
					_cC++;
			}
		}
	}
	for (int i = 0; i < 100; i++) { // equals DOFT4 TO DOFT3. to always have a copy of DOFT3
		for (int j = 0; j < 3; j++) {
			DOFT4[i][j] = DOFT3[i][j];
		}
	}
	for (int i = 0; i < 100; i++) { // Creates DOFT4
		for (int j = 1; j < 100; j++) {
			if (i+j < 100 && Nodes[i][0] == Nodes[i + j][0] && Nodes[i][1] == Nodes[i + j][1]) {
				DOFT4[i + j][0] = DOFT4[i][0];
				DOFT4[i + j][1] = DOFT4[i][1];
				DOFT4[i + j][2] = DOFT4[i][2];
			}
		}
	}

	for (int i = 0; i < 100; i++){ // changes DOFT4 to its absolute values
        for (int j = 0; j < 3; j++){
            DOFT4[i][j] = abs(DOFT4[i][j]);
        }
	}

	double lengths[50];
	for (int i = 0; i < 2 * s; i+=2) { // calculates lengths
		lengths[i/2] = pow((pow((Nodes[i+1][0] - Nodes[i][0]), 2) + pow((Nodes[i + 1][1] - Nodes[i][1]), 2)), 0.5);
	}

	double thetas[50];
	for (int i = 0; i < 2*s; i+=2) { // calculates thetas
		thetas[i/2] = asin((Nodes[i + 1][1] - Nodes[i][1]) / lengths[i / 2]);
	}


	double Kl[50][6][6]; //3d array to hold 50 members' local stiffnesses
	for (int i = 0; i < s; i++) { //creates Klocals
		Kl[i][0][0] = EA[i] / lengths[i];
		Kl[i][0][1] = 0;
		Kl[i][0][2] = 0;
		Kl[i][0][3] = -(EA[i] / lengths[i]);
		Kl[i][0][4] = 0;
		Kl[i][0][5] = 0;

		Kl[i][1][0] = 0;
		Kl[i][1][1] = 12*EI[i]/pow(lengths[i], 3);
		Kl[i][1][2] = 6 * EI[i] / pow(lengths[i], 2);
		Kl[i][1][3] = 0;
		Kl[i][1][4] = -(12 * EI[i] / pow(lengths[i], 3));
		Kl[i][1][5] = (6 * EI[i] / pow(lengths[i], 2));

		Kl[i][2][0] = 0;
		Kl[i][2][1] = 6 * EI[i] / pow(lengths[i], 2);
		Kl[i][2][2] = 4*EI[i]/ lengths[i];
		Kl[i][2][3] = 0;
		Kl[i][2][4] = -(6 * EI[i] / pow(lengths[i], 2));
		Kl[i][2][5] = 2 * EI[i] / lengths[i];

		Kl[i][3][0] = -(EA[i] / lengths[i]);
		Kl[i][3][1] = 0;
		Kl[i][3][2] = 0;
		Kl[i][3][3] = EA[i] / lengths[i];
		Kl[i][3][4] = 0;
		Kl[i][3][5] = 0;

		Kl[i][4][0] = 0;
		Kl[i][4][1] = -(12 * EI[i] / pow(lengths[i], 3));
		Kl[i][4][2] = -(6 * EI[i] / pow(lengths[i], 2));
		Kl[i][4][3] = 0;
		Kl[i][4][4] = 12 * EI[i] / pow(lengths[i], 3);
		Kl[i][4][5] = -(6 * EI[i] / pow(lengths[i], 2));

		Kl[i][5][0] = 0;
		Kl[i][5][1] = 6 * EI[i] / pow(lengths[i], 2);
		Kl[i][5][2] = 2 * EI[i] / lengths[i];
		Kl[i][5][3] = 0;
		Kl[i][5][4] = -(6 * EI[i] / pow(lengths[i], 2));
		Kl[i][5][5] = 4 * EI[i] / lengths[i];
	}

    double rtk[6][6]; //hold the matrix of Rt*Kl
	double Kltog[6][6]; //hold the matrix of Rt*Kl*R
	double Kglobal[nodofs][nodofs];// final Kglobal
    for(int i = 0; i < nodofs; i++){ // initially Kglobal starts as a zero matrix
            for(int j = 0; j < nodofs; j++){
                Kglobal[i][j]=0;
            }
        }
    int _ss = 0; // counter that increases by 2 each time
	for (int i = 0; i < s; i++) { //creates Kglobal
        double Rotation[6][6] = {
                                {cos(thetas[i]), sin(thetas[i]), 0, 0, 0, 0},
                                {-(sin(thetas[i])), cos(thetas[i]), 0, 0, 0, 0},
                                {0, 0, 1, 0, 0, 0},
                                {0, 0, 0, cos(thetas[i]), sin(thetas[i]), 0},
                                {0, 0, 0, -(sin(thetas[i])), cos(thetas[i]), 0},
                                {0, 0, 0, 0, 0, 1}
                            };
        double tRotation[6][6];
        for (int j = 0; j < 6; j++){
            for(int h = 0; h < 6 ; h++){
                tRotation[j][h] = Rotation[h][j];
            }
        }

        for(int j = 0; j < 6; j++){ // initially Kltog starts as a zero matrix
            for(int h = 0; h < 6; h++){
                Kltog[j][h]=0;
                rtk[j][h]=0;
            }
        }

        for(int j= 0; j < 6; j++){ // matrix multiplication
            for(int h = 0; h < 6; h++){
                for(int k= 0; k < 6; k++){
                    rtk[j][h] = rtk[j][h] + tRotation[j][k]* Kl[i][k][h];
                }
            }
        }

        for(int j= 0; j < 6; j++){ // matrix multiplication
            for(int h = 0; h < 6; h++){
                for(int k= 0; k < 6; k++){
                    Kltog[j][h] = Kltog[j][h] + rtk[j][k]* Rotation[k][h];
                }
            }
        }

        for(int j= 0; j < 6; j++){
            for(int h=0; h < 6; h++){
                int oneone = _ss;
                int onetwo = j;
                int twoone = _ss;
                int twotwo = h;

                if(j > 2){
                    oneone = _ss +1;
                    onetwo = j -3;
                }
                if(h > 2){
                    twoone = _ss +1;
                    twotwo = h -3;
                }
                Kglobal[DOFT4[oneone][onetwo]-1][DOFT4[twoone][twotwo]-1] += Kltog[j][h];
            }
        }
        _ss = _ss +2;
	}

	//load calculations are done here:
	double loads[nodofs]; //the final force vector
	for(int i =0 ; i < nodofs; i++){ //makes every entry of loads 0 to start
        loads[i]=0;
	}

	for(int i=0; i < nofl; i++){ //creates the force vector
	    double lloads[6]; //local force vector for each member
            for(int k =0 ; k < 6; k++){ //makes every entry of loads 0 to start
            lloads[k]=0;
            }
        if(loaddegree[0][i] == 1 || loaddegree[1][i] == 1 || loaddegree[2][i] == 1){ //when the load is upwards relative to member's local orientation
            if(loadmagnitude[0][i] != 0){ //point load
                lloads[0] = 0;
                lloads[1] = loadmagnitude[0][i]*(lengths[loadmember[i]-1]-loaddistance[0][i])*(lengths[loadmember[i]-1]-loaddistance[0][i])*(3*loaddistance[0][i]+(lengths[loadmember[i]-1]-loaddistance[0][i]))/(lengths[loadmember[i]-1]*lengths[loadmember[i]-1]*lengths[loadmember[i]-1]);
                lloads[2] = loadmagnitude[0][i]*loaddistance[0][i]*(lengths[loadmember[i]-1]-loaddistance[0][i])*(lengths[loadmember[i]-1]-loaddistance[0][i])/(lengths[loadmember[i]-1]*lengths[loadmember[i]-1]);
                lloads[3] = 0;
                lloads[4] = loadmagnitude[0][i]*loaddistance[0][i]*loaddistance[0][i]*(loaddistance[0][i]+3*(lengths[loadmember[i]-1]-loaddistance[0][i]))/(lengths[loadmember[i]-1]*lengths[loadmember[i]-1]*lengths[loadmember[i]-1]);
                lloads[5] = -(loadmagnitude[0][i]*loaddistance[0][i]*loaddistance[0][i]*(lengths[loadmember[i]-1]-loaddistance[0][i])/(lengths[loadmember[i]-1]*lengths[loadmember[i]-1]));
            }else if(loadmagnitude[1][i] != 0){ //distributed load
                lloads[0] = 0;
                lloads[1] = loadmagnitude[1][i]*lengths[loadmember[i]-1]/2;
                lloads[2] = loadmagnitude[1][i]*lengths[loadmember[i]-1]*lengths[loadmember[i]-1]/12;
                lloads[3] = 0;
                lloads[4] = loadmagnitude[1][i]*lengths[loadmember[i]-1]/2;
                lloads[5] = -(loadmagnitude[1][i]*lengths[loadmember[i]-1]*lengths[loadmember[i]-1]/12);
            }else{ //point moment
                lloads[0] = 0;
                lloads[1] = 6*loadmagnitude[2][i]*loaddistance[2][i]*(lengths[loadmember[i]-1]-loaddistance[2][i])/(lengths[loadmember[i]-1]*lengths[loadmember[i]-1]*lengths[loadmember[i]-1]);
                lloads[2] = loadmagnitude[2][i]*(lengths[loadmember[i]-1]-loaddistance[2][i])*(3*loaddistance[2][i]-lengths[loadmember[i]-1])/(lengths[loadmember[i]-1]*lengths[loadmember[i]-1]);
                lloads[3] = 0;
                lloads[4] = -(6*loadmagnitude[2][i]*loaddistance[2][i]*(lengths[loadmember[i]-1]-loaddistance[2][i])/(lengths[loadmember[i]-1]*lengths[loadmember[i]-1]*lengths[loadmember[i]-1]));
                lloads[5] = loadmagnitude[2][i]*loaddistance[2][i]*(3*(lengths[loadmember[i]-1]-loaddistance[2][i])-lengths[loadmember[i]-1])/(lengths[loadmember[i]-1]*lengths[loadmember[i]-1]);
            }

        } else { //when the load is downwards
            if(loadmagnitude[0][i] != 0){//point load
                lloads[0] = 0;
                lloads[1] = -(loadmagnitude[0][i]*(lengths[loadmember[i]-1]-loaddistance[0][i])*(lengths[loadmember[i]-1]-loaddistance[0][i])*(3*loaddistance[0][i]+(lengths[loadmember[i]-1]-loaddistance[0][i]))/(lengths[loadmember[i]-1]*lengths[loadmember[i]-1]*lengths[loadmember[i]-1]));
                lloads[2] = -(loadmagnitude[0][i]*loaddistance[0][i]*(lengths[loadmember[i]-1]-loaddistance[0][i])*(lengths[loadmember[i]-1]-loaddistance[0][i])/(lengths[loadmember[i]-1]*lengths[loadmember[i]-1]));
                lloads[3] = 0;
                lloads[4] = -(loadmagnitude[0][i]*loaddistance[0][i]*loaddistance[0][i]*(loaddistance[0][i]+3*(lengths[loadmember[i]-1]-loaddistance[0][i]))/(lengths[loadmember[i]-1]*lengths[loadmember[i]-1]*lengths[loadmember[i]-1]));
                lloads[5] = loadmagnitude[0][i]*loaddistance[0][i]*loaddistance[0][i]*(lengths[loadmember[i]-1]-loaddistance[0][i])/(lengths[loadmember[i]-1]*lengths[loadmember[i]-1]);
            }else if(loadmagnitude[1][i] != 0){//distributed load
                lloads[0] = 0;
                lloads[1] = -(loadmagnitude[1][i]*lengths[loadmember[i]-1]/2);
                lloads[2] = -(loadmagnitude[1][i]*lengths[loadmember[i]-1]*lengths[loadmember[i]-1]/12);
                lloads[3] = 0;
                lloads[4] = -(loadmagnitude[1][i]*lengths[loadmember[i]-1]/2);
                lloads[5] = loadmagnitude[1][i]*lengths[loadmember[i]-1]*lengths[loadmember[i]-1]/12;
            }else{
                lloads[0] = 0;
                lloads[1] = -(6*loadmagnitude[2][i]*loaddistance[2][i]*(lengths[loadmember[i]-1]-loaddistance[2][i])/(lengths[loadmember[i]-1]*lengths[loadmember[i]-1]*lengths[loadmember[i]-1]));
                lloads[2] = -(loadmagnitude[2][i]*(lengths[loadmember[i]-1]-loaddistance[2][i])*(3*loaddistance[2][i]-lengths[loadmember[i]-1])/(lengths[loadmember[i]-1]*lengths[loadmember[i]-1]));
                lloads[3] = 0;
                lloads[4] = 6*loadmagnitude[2][i]*loaddistance[2][i]*(lengths[loadmember[i]-1]-loaddistance[2][i])/(lengths[loadmember[i]-1]*lengths[loadmember[i]-1]*lengths[loadmember[i]-1]);
                lloads[5] = -(loadmagnitude[2][i]*loaddistance[2][i]*(3*(lengths[loadmember[i]-1]-loaddistance[2][i])-lengths[loadmember[i]-1])/(lengths[loadmember[i]-1]*lengths[loadmember[i]-1]));
            }
        }


        double rloads[6] = {0, 0, 0, 0, 0, 0}; //rotated lloads

        double aRotation[6][6] = {
                                {cos(thetas[loadmember[i]-1]), sin(thetas[loadmember[i]-1]), 0, 0, 0, 0},
                                {-(sin(thetas[loadmember[i]-1])), cos(thetas[loadmember[i]-1]), 0, 0, 0, 0},
                                {0, 0, 1, 0, 0, 0},
                                {0, 0, 0, cos(thetas[loadmember[i]-1]), sin(thetas[loadmember[i]-1]), 0},
                                {0, 0, 0, -(sin(thetas[loadmember[i]-1])), cos(thetas[loadmember[i]-1]), 0},
                                {0, 0, 0, 0, 0, 1}
                            };
        double ttRotation[6][6];
        for (int j = 0; j < 6; j++){
            for(int h = 0; h < 6 ; h++){
                ttRotation[j][h] = aRotation[h][j];
            }
        }

        for(int h= 0; h < 6; h++){ // matrix multiplication
            for(int k = 0; k < 6; k++){
                rloads[h] = rloads[h] + lloads[k]*ttRotation[h][k];
            }
        }


        //here lloads are going to be added to loads
        loads[DOFT4[2*loadmember[i]-2][0]-1] = loads[DOFT4[2*loadmember[i]-2][0]-1] + rloads[0];
        loads[DOFT4[2*loadmember[i]-2][1]-1] = loads[DOFT4[2*loadmember[i]-2][1]-1] + rloads[1];
        loads[DOFT4[2*loadmember[i]-2][2]-1] = loads[DOFT4[2*loadmember[i]-2][2]-1] + rloads[2];
        loads[DOFT4[2*loadmember[i]-1][0]-1] = loads[DOFT4[2*loadmember[i]-1][0]-1] + rloads[3];
        loads[DOFT4[2*loadmember[i]-1][1]-1] = loads[DOFT4[2*loadmember[i]-1][1]-1] + rloads[4];
        loads[DOFT4[2*loadmember[i]-1][2]-1] = loads[DOFT4[2*loadmember[i]-1][2]-1] + rloads[5];
	}

    cout << "Kglobal:" << endl;
	for(int i =0; i < nodofs ; i++){
        for(int j = 0; j < nodofs ; j++){
            if(-0.00001 < Kglobal[i][j] && Kglobal[i][j] < 0.00001){
            cout << "0" << " ";
            } else{
            cout << Kglobal[i][j] << " ";
            }
        }
        cout << endl;
	}

	cout << "Loads:" << endl;
	for(int i =0; i < nodofs ; i++){
        cout << i+1 << ":" << loads[i] << " " << endl;
	}

	double augmented[cF][cF+1];//to be able to do Gauss - Jordan Elimination
	for(int i=0; i < cF; i++){
        for(int j=0; j < cF; j++){
            augmented[i][j] = Kglobal[i][j];
        }
	}
	for(int i = 0; i< cF; i++){
        augmented[i][cF] = loads[i];
	}


	double k;
	for(int i=0; i<cF; i++){
        for(int j=1; j<cF; j++){
            if(augmented[i][i] != 0 && i < j){
                k =augmented[j][i]/augmented[i][i];
            for(int h=0; h<cF+1 ; h++){
                augmented[j][h] = augmented[j][h] - k*augmented[i][h];
            }
            }
        }
    }


    double n[cF][cF+1];
    for(int i =0; i <cF ; i++){
        n[i][cF] = augmented[cF-1-i][cF];
        for(int j=0; j<cF; j++){
            n[i][j] = augmented[cF-1-i][cF-1-j];
        }
    }


    for(int i=0; i<cF; i++){
        for(int j=1; j<cF; j++){
            if(n[i][i] != 0 && i < j){
                k =n[j][i]/n[i][i];
            for(int h=0; h<cF+1 ; h++){
                n[j][h] = n[j][h] - k*n[i][h];
            }
            }
        }
    }

    double u[cF];
    for(int i = 0; i<cF ;i++){
        u[cF-1-i] = n[i][cF]/n[i][i];

    }
    cout << "Deformations in order:" <<endl;
    for(int i = 0; i<cF ;i++){
        cout << i+1 << ":" << u[i] << endl;
    }

}

int main()
{
    // Since this code uses variables while creating arrays it may not compile on some IDE's.

	Input();
	Logic();
	system("pause");

}

