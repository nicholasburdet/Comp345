#include "playerLog.h"


playerLog::playerLog(void)
{
	log.resize(log.capacity() + 1);
}

void playerLog::addToLog(string logEntry)
{
	logLength++;
	if (logLength > log.capacity())
	{
		log.resize(log.capacity() + 5);
	}
	log.push_back(logEntry);
}

string playerLog::readLogEntry(int entry)
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

void playerLog::saveToFile()
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


void playerLog::loadFromFile(string filename)
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

int playerLog::getLogLength()
{
	return logLength;
}
