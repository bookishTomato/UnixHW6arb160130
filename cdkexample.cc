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


	ifstream binInFile("cs3377.bin",ios::in|ios::binary);
	binInFile.read((char*)header,sizeof(BinaryFileRecord));
	
	if((int)header->numRecords >= 1)
	{
	}

	std::stringstream stream;
	stream << "Magic: 0x" << hex << (int)header->magicNumber;
	string magic(stream.str());
  	setCDKMatrixCell(myMatrix, 1, 1,magic.c_str());
	stringstream str2;
	str2 << "Version: " << (int)header->versionNumber;
	string vers(str2.str());
	setCDKMatrixCell(myMatrix, 1, 2,vers.c_str());
	stringstream str3;
	str3 << "NumRecords: " << (int)header->numRecords;
	string recs(str3.str());
	setCDKMatrixCell(myMatrix, 1, 3,recs.c_str());


  	drawCDKMatrix(myMatrix, true);    /* required  */

  	/* So we can see results, pause until a key is pressed. */
  	unsigned char x;
  	cin >> x;

  	// Cleanup screen
  	//   endCDK();
  	//   }
  	//

}
