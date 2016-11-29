#include <fstream>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

#pragma once

class player_Log
{
public:
	player_Log(void);
	void addToLog(string logEntry);
	string readLogEntry(int entry);
	void saveToFile(void);
	void loadFromFile(string filename);
	int getLogLength();
private:
	vector<string> log;
	int logLength = 0;
};