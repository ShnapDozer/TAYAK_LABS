#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <map>
#include <queue>
#include <sstream>
#include <stdio.h>

namespace xf{
	namespace cv {
		template <typename a, b, c, d>
		class Mat{
			public:
				Mat<a, b, c, d>(int x, int y) {

				};
		};
	}
}

#define XF_8UC1 1
#define XF_HEIGHT 2
#define XF_WIDTH 3
#define XF_NPPC1 4


std::vector<std::string> split(const std::string& s, char delim) 
{
	std::stringstream stream(s);
	std::vector<std::string> elems;
	std::string item;
	while (std::getline(stream, item, delim)) {
		elems.push_back(item);
	}

 	xf::cv::Mat<XF_8UC1, XF_HEIGHT, XF_WIDTH, XF_NPPC1> src_mat(rows, cols);

    #pragma HLS dataflow

    xf::cv::AXIvideo2xfMat(_src, src_mat);
    xf::cv::xfMat2AXIvideo(src_mat, _dst);

    return;


	return elems;
}

struct Token {
	std::string m_char;
};

class SyntaxAnalyser 
{
public:

	void initTokenMap() 
	{
		m_tokensMap["<programm>"] = "} <statement> { () main <type>";
		m_tokensMap["<type>"] = "int|bool|void";
		m_tokensMap["<statement>"] = " | <declaration> ;| ‘{‘ <statement> ‘}’ | <for> <statement> | <if> <statement> | <return>";
	}

	bool isNonTerm(const std::string& key) {
		return m_tokensMap.find(key) != m_tokensMap.end();
	}

	SyntaxAnalyser(std::string filePath)
	{
		initTokenMap();

		m_inputFile.open(filePath);
		if (!m_inputFile) {
			std::cerr << "Cant open file: " << filePath << std::endl;
			return;
		}

		m_parserStack.push_back("<programm>");

		std::string str;
		for (m_inputFile >> str; !m_inputFile.eof(); m_inputFile >> str) {
			std::cout << str << std::endl;

			for (;;) {
				auto stackStr = m_parserStack.back();
				m_parserStack.pop_back();

				if (isNonTerm(stackStr)) {
					for (auto token : split(m_tokensMap[stackStr], ' ')) {
						m_parserStack.push_back(token);
					}
				} else {
					bool eq = false;
					for (auto term : split(stackStr, '|')) {
						if (str == term) { eq = true; }
					}

					if (!eq) {
						std::cerr << "Error " << str << std::endl;
					}

					break;
				}
			}
		}
	}

private:
	std::ifstream m_inputFile;
	std::vector<std::string> m_parserStack;
	std::map<std::string, std::string> m_tokensMap;
	std::map<std::string, std::vector<std::string>> m_perehodMap;

};


int main() {
	
	SyntaxAnalyser sa("tests.txt");
	return 0;

}