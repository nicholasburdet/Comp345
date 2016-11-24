#include <fstream>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

#pragma once

class playerLog
{
	public :
		playerLog(void);
		void addToLog(string logEntry);
		string readLogEntry(int entry);
		void saveToFile(void);
		void loadFromFile(string filename);
		int getLogLength();
	private:
		vector<string> log;
		int logLength = 0;
};