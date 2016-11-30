#include "player_Log.h"


player_Log::player_Log(void)
{
	log.resize(log.capacity() + 1);
}

void player_Log::addToLog(string logEntry)
{
	logLength++;
	log.push_back(logEntry);
}

string player_Log::readLogEntry(int entry)
{
	if (entry > logLength)
	{
		return "Log entry out of bounds";
	}
	else
	{
		return log[entry];
	}
}

void player_Log::saveToFile()
{
	ofstream output;
	string extension = "Logs/"; //Enter extension here
	string fName = extension;
	fName.append("lognamehere");

	output.open(fName.append(".txt"));


	for (int i = 0; i < logLength; i++)
	{
		output << "[LogEntry" << i << "]" << " " << log[i] << endl;
	}

	output.close();
}


void player_Log::loadFromFile(string filename)
{
	ifstream input;
	input.open(filename, ios::in);

	string type;
	string logstring;

	input >> type >> logstring;

	if (!input.eof())
	{
		addToLog(logstring);
	}

	while (!input.eof())
	{
		addToLog(logstring);
	}

	input.close();
}

int player_Log::getLogLength()
{
	return logLength;
}