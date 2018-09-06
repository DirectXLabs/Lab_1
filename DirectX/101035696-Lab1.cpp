//***************************************************************************
// 101085383 and 101035696 - Lab 1.cpp by James Bews and Jatin Kumar (C) 2017 All Rights Reserved.
//
// Lab 1 submission.
//
// Description:
// Click run to see the results.
//
//*****************************************************************************


#include <windows.h>
#include <DirectXMath.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include<math.h>
using namespace std;
using namespace DirectX;
void PrintMatrix(XMMATRIX *m);//this function calls the rows to be printed
void PrintMatrixRow(XMVECTOR p);//this function prints the rows
int Negate;								//Checkerboard pattern of negation
int Limit = 9;							//Rand of randomness
float getCofactor(XMFLOAT4X4 my4X4, XMFLOAT3X3 tempArray, int p, int q, int n)//get's the cofactor given the index in the matrix and the size
{
	int i = 0, j = 0;
	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
		{
			if (row != p && col != q)
			{
				tempArray.m[i][j++] = my4X4.m[row][col];
				if (j == n - 1)
				{

					j = 0;
					i++;
				}
			}
		}
	}

	XMMATRIX my3x3M = XMLoadFloat3x3(&tempArray);

	XMVECTOR f = XMMatrixDeterminant(my3x3M);
	XMFLOAT4 c;
	XMStoreFloat4(&c, f);

	return c.x;
}
XMMATRIX myAdjointMatrix(XMMATRIX myMatrix) {// this function returns the Adjoint matrix given a matrix
	XMFLOAT4X4 my4X4;
	XMFLOAT4X4 myCofactor4X4;
	XMFLOAT3X3 myReturned3X3 = { 1,0,0,
							  0,1,0,
							  0,0,1,
	};
	XMStoreFloat4x4(&my4X4, myMatrix);

	XMMATRIX returnThisOne;
	bool flip = true;
	for (int i = 0; i < 4; i++) {
		if ((i % 2) + 1 == 1) {
			flip = true;
		}
		else flip = false;
		for (int j = 0; j < 4; j++) {
			if (flip) {
				Negate = 1;
				flip = !flip;
			}
			else {
				Negate = -1;
				flip = !flip;
			}
			myCofactor4X4.m[i][j] = getCofactor(my4X4, myReturned3X3, i, j, 4)*Negate;
			returnThisOne = XMLoadFloat4x4(&myCofactor4X4);


			returnThisOne = XMMatrixTranspose(returnThisOne);


		}
	}
	return returnThisOne;
}
float RandomNumber(int x) {//returns a random number between 0 and x
	float randomNumber = float(rand() % x);
	return randomNumber;
}

XMMATRIX randomizeMatrix() {// this returns a random matrix between 0 and 99
	XMMATRIX newMatrix(RandomNumber(Limit), RandomNumber(Limit), RandomNumber(Limit), RandomNumber(Limit),
		RandomNumber(Limit), RandomNumber(Limit), RandomNumber(Limit), RandomNumber(Limit),
		RandomNumber(Limit), RandomNumber(Limit), RandomNumber(Limit), RandomNumber(Limit),
		RandomNumber(Limit), RandomNumber(Limit), RandomNumber(Limit), RandomNumber(Limit));
	return newMatrix;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
float d = 0;
float det(int n, float mat[10][10])
{
	int c, subi, i, j, subj;
	float submat[10][10];
	if (n == 2)
	{
		return((mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1]));
	}
	else
	{
		for (c = 0; c < n; c++)
		{
			subi = 0;
			for (i = 1; i < n; i++)
			{
				subj = 0;
				for (j = 0; j < n; j++)
				{
					if (j == c)
					{
						continue;
					}
					submat[subi][subj] = mat[i][j];
					subj++;
				}
				subi++;
			}
			d = d + (pow(-1, c) * mat[0][c] * det(n - 1, submat));
		}
	}
	return d;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main() {
	srand(time(NULL));
	XMMATRIX myMatrix = randomizeMatrix();
	cout << "Our Random Matrix" << endl;
	PrintMatrix(&myMatrix);
	//Testing
	XMFLOAT4X4 b;
	XMStoreFloat4x4(&b, myMatrix);
	float mat[10][10];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			
			
			mat[i][j] = b.m[i][j];
			//cout << mat[i][j];
		}
	}
	cout << "\ndeterminant" << det(4, mat);

	//Testing

	cout << endl << "Using XMMatrixInverse" << endl;
	XMVECTOR myVector;
	myVector = XMMatrixDeterminant(myMatrix);

	XMMATRIX newMAT = XMMatrixInverse(&myVector, myMatrix);
	PrintMatrix(&newMAT);
	cout << endl << "Using our inverse" << endl;
	XMMATRIX tempMatrix = myAdjointMatrix(myMatrix);

	XMFLOAT4 f;
	XMStoreFloat4(&f, myVector);
	f.x = 1 / f.x;
	tempMatrix = tempMatrix * f.x;

	PrintMatrix(&tempMatrix);
	system("pause");
}
void PrintMatrix(XMMATRIX *m)
{
	for (int i = 0; i < 4; i++)
	{
		PrintMatrixRow(m->r[i]);
	}
}

void PrintMatrixRow(XMVECTOR p)
{
	XMFLOAT4 c;
	XMStoreFloat4(&c, p);

	cout << "[" << c.x << "\t" << c.y << "\t" << c.z << "\t" << c.w << "]" << endl;
}

//testing 

