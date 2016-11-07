
#ifndef Q_DEBUGSTREAM_H_
#define Q_DEBUGSTREAM_H_

#include <iostream>
#include <streambuf>
#include <string>
#include <QDebug>


//Code taken from internet. This is just so that the std::cerr gets redirected to the Qt debug output, only for the cppunit tests
//All credits go to stele http://www.qtforum.org/article/678/redirecting-cout-cerr-to-qdebug.html

class Q_DebugStream : public std::basic_streambuf<char>
{
public:
	Q_DebugStream(std::ostream &stream) : m_stream(stream)
	{
		m_old_buf = stream.rdbuf();
		stream.rdbuf(this);
	}
	~Q_DebugStream()
	{
		// output anything that is left
		if (!m_string.empty())
			qDebug(m_string.c_str());

		m_stream.rdbuf(m_old_buf);
	}

protected:
	virtual int_type overflow(int_type v)
	{
		if (v == '\n')
		{
			qDebug(m_string.c_str());
			m_string.erase(m_string.begin(), m_string.end());
		}
		else
			m_string += v;

		return v;
	}

	virtual std::streamsize xsputn(const char *p, std::streamsize n)
	{
		m_string.append(p, p + n);

		int pos = 0;
		while (pos != std::string::npos)
		{
			pos = m_string.find('\n');
			if (pos != std::string::npos)
			{
				std::string tmp(m_string.begin(), m_string.begin() + pos);
				qDebug(tmp.c_str());
				m_string.erase(m_string.begin(), m_string.begin() + pos + 1);
			}
		}

		return n;
	}

private:
	std::ostream &m_stream;
	std::streambuf *m_old_buf;
	std::string m_string;
};



#endif
