#include <iostream>
#include <fstream>
#include "ping.h"

void MakeCrcTable();

//Table of CRCs of all 8-bit messages.
unsigned long crc_table[256];

/*struct Ping //PNG structure
{
	const unsigned char header[] = { 0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, '\0'};
	
	void writeHeader()
	{
		for (int i = 0; i < 8; i++ ) 
	}
};*/

int main()
{
	std::cout << "hi"; //debug
	ping::Chunk** chunk = new ping::Chunk*[1]; //array of chunks
	chunk[0] = new ping::IHDR();
	std::cout << "hi"; //debug
	std::cout << chunk[0]->getSizeInt(); //debug
	
	const unsigned char header[] = { 0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, '\0'};
	
	//std::cout << header; //debug
	
	MakeCrcTable();
	//make ihdr crc
	chunk[0]->setCrc32(ping::calcCrc( crc_table, 0xffffffffL, chunk[0]->getName(), (chunk[0]->getSizeInt())-9));
	
	std::ofstream file;
	file.open("test.png", std::ios::binary );
	file << header << chunk[0]->getName() << chunk[0]->getSizeChar() << chunk[0]->getCrc32();
	//file.write(chunk[0]->getSize_char(), sizeof(char)*chunk[0]->getSize_char().size());
	file.close();
	
	return 0;	
}

// Make the table for a fast CRC.
void MakeCrcTable()
{
	unsigned long c;
	int n, k;
	
	for (n = 0; n < 256; n++) {
		c = (unsigned long) n;
		for (k = 0; k < 8; k++) {
		if (c & 1)
			c = 0xedb88320L ^ (c >> 1);
		else
			c = c >> 1;
		}
		crc_table[n] = c;
	}
}