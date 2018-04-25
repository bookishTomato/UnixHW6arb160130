//Amanda Brooks arb160130 CS3377.002 4/24/18
//

#include <stdint.h>

class BinaryFileHeader
{
public:
	uint32_t magicNumber; /* Should be 0xFEEDFACE */
	uint32_t versionNumber;
	uint64_t numRecords;
};
