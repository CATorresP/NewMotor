#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "Error.h"
using namespace std;
class IOManager
{
public:
	static bool readFileToBuffer(string filePath, vector<unsigned char>& buffer);
};

