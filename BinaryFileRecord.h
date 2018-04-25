//Amanda Brooks arb160130 CS3377.002 4/24/18

#include <stdint.h>

const int maxRecordStringLength = 25;
class BinaryFileRecord
{
public:
	uint8_t strLength;
 	char stringBuffer[maxRecordStringLength];
};
