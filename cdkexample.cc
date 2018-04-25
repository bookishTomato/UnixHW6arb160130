/*
 *Usage of CDK Matrix
 *
 * File: example1.cc
 * Author: Stephen Perkins
 * Email: stephen.perkins@utdallas.edu
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdint.h>
#include <sstream>
#include "BinaryFileHeader.h"
#include "BinaryFileRecord.h"
#include "cdk.h"

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 25
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

int main()
{
	WINDOW *window;
	CDKSCREEN *cdkscreen;
	CDKMATRIX *myMatrix;	//CDK Screen Matrix
	
	//Remember that matrix starts out at 1,1
	//Since arrays start out at 0, the first entries
	//below ("R0", and "C0") are just placeholders.
	//
	//Finally... make sure your arrays have enough entries given the
	//values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
	//above...
	
	const char *rowTitles[] = {"a","a","b","c","d","e"};
	const char *columnTitles[] = {"C0","a","b","c","d","e"};
	int boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
	int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  	/*
 	*    * Initialize the Cdk screen.
 	*       *
 	*          * Make sure the putty terminal is large enough
 	*             */
 	window = initscr();
  	cdkscreen = initCDKScreen(window);

  	/* Start CDK Colors */
  	initCDKColor();

  	/*
 	*    * Create the matrix.  Need to manually cast (const char**) to (char **)
 	*      */
  	myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  	if (myMatrix ==NULL)
    	{
      	printf("Error creating Matrix\n");
      	_exit(1);
    	}

  	/* Display the Matrix */
  	drawCDKMatrix(myMatrix, true);

  	/*
 	*    * Dipslay a message
 	*       */

	BinaryFileHeader *header = new BinaryFileHeader();
	BinaryFileRecord *rec1 = new BinaryFileRecord();
	BinaryFileRecord *rec2 = new BinaryFileRecord();
	BinaryFileRecord *rec3 = new BinaryFileRecord();	
	BinaryFileRecord *rec4 = new BinaryFileRecord();

	/*
 	*	Get everything out of the file
 	*
 	*/ 
	ifstream binInFile("cs3377.bin",ios::in|ios::binary);
	binInFile.read((char*)header,sizeof(BinaryFileHeader));
	
	binInFile.read((char*)rec1,sizeof(BinaryFileRecord));
	binInFile.read((char*)rec2,sizeof(BinaryFileRecord));
	binInFile.read((char*)rec3,sizeof(BinaryFileRecord));
	binInFile.read((char*)rec4,sizeof(BinaryFileRecord));

	//Convert to strings

	std::stringstream stream;
	stream << "Magic: 0x" << hex << (int)header->magicNumber;
	string magic(stream.str());
  	stringstream str2;
	str2 << "Version: " << (int)header->versionNumber;
	string vers(str2.str());
	stringstream str3;
	str3 << "NumRecords: " << (int)header->numRecords;
	string recs(str3.str());
	
	std::stringstream r1;
	r1 << "strlen: " << (int)rec1->strLength;
	string strln1(r1.str());
	r1.str("");
	r1 << (char*)rec1->stringBuffer;
	string re1(r1.str());

        std::stringstream r2;
        r2 << "strlen: " << (int)rec2->strLength;
        string strln2(r2.str());
        r2.str("");
        r2 << (char*)rec2->stringBuffer;
        string re2(r2.str());
       
	std::stringstream r3;
        r3 << "strlen: " << (int)rec3->strLength;
        string strln3(r3.str());
        r3.str("");
        r3 << (char*)rec3->stringBuffer;
        string re3(r3.str());
        
	std::stringstream r4;
        r4 << "strlen: " << (int)rec4->strLength;
        string strln4(r4.str());
        r4.str("");
        r4 << (char*)rec4->stringBuffer;
        string re4(r4.str());

	//Put in the matrix

	setCDKMatrixCell(myMatrix, 1, 1,magic.c_str());
	setCDKMatrixCell(myMatrix, 1, 2,vers.c_str());
	setCDKMatrixCell(myMatrix, 1, 3,recs.c_str());

	setCDKMatrixCell(myMatrix, 2, 1,strln1.c_str());
	setCDKMatrixCell(myMatrix, 2, 2,re1.c_str());

        setCDKMatrixCell(myMatrix, 3, 1,strln2.c_str());
        setCDKMatrixCell(myMatrix, 3, 2,re2.c_str());

        setCDKMatrixCell(myMatrix, 4, 1,strln3.c_str());
        setCDKMatrixCell(myMatrix, 4, 2,re3.c_str());

        setCDKMatrixCell(myMatrix, 5, 1,strln4.c_str());
        setCDKMatrixCell(myMatrix, 5, 2,re4.c_str());


  	drawCDKMatrix(myMatrix, true);    /* required  */

  	/* So we can see results, pause until a key is pressed. */
  	unsigned char x;
  	cin >> x;

  	// Cleanup screen
  	//   endCDK();
  	//   }
  	//

}
