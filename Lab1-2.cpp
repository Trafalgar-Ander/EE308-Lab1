#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include<regex>
#include<stack>

#define N 100
using namespace std;

int countKeyNum = 0;
int ifelseNum = 0;
int ifelseifNum = 0;
int switchNum = 0;
int caseNum[100];

class File {
	public:
		void LodeFile(const string&path);
};
bool isIf(string str) {
	regex pattern("if");
	smatch result;
	bool ismatch = regex_search(str, result, pattern);
	return ismatch;
}
bool isElse(string str) {
	regex pattern("else");
	smatch result;
	bool ismatch = regex_search(str, result, pattern);
	return ismatch;
}
bool isElseIf(string str) {
	regex pattern("else if");
	smatch result;
	bool ismatch = regex_search(str, result, pattern);
	return ismatch;
}
bool isSwitch(string str) {
	regex pattern("switch");
	smatch result;
	bool ismatch = regex_search(str, result, pattern);
	return ismatch;
}
bool isCase(string str) {
	regex pattern("case");
	smatch result;
	bool ismatch = regex_search(str, result, pattern);
	return ismatch;
}
void countNumSwitch(stack <string> switchCase) {
	while (!switchCase.empty()) {
		while (switchCase.top() == "case") {
			caseNum[switchNum]++;
			switchCase.pop();
		}
		if (switchCase.top() == "switch") {
			switchNum++;
			switchCase.pop();
		}
	}

}
void countNumIf(stack <string> str_stack) {
	int count = 0;
	while (!str_stack.empty() && str_stack.top() != "if") {
		if (str_stack.top() == "else if") {
			count++;
		}

		str_stack.pop();

	}
	if (count == 0) {
		ifelseNum++;
	} else {
		ifelseifNum++;
	}
	if (!str_stack.empty()) {
		str_stack.pop();
	}


}

void countKey(string s) {

	string keyword[32] = { "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern",
	                       "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed", "sizeof", "static",
	                       "struct", "switch", "typedef", "unsigned", "union", "void", "volatile", "while"};
	
	s = "   " + s;
	
	for (int i = 0; i < 32; i++) {
		regex pattern("[^a-zA-Z0-9_]" + keyword[i] + "[^a-zA-Z0-9_]");
		smatch result;
		bool ismatch = regex_search(s, result, pattern);
		if (ismatch) {
			countKeyNum++;
			//cout << keyword[i] << endl;
		}
	}
}

void File::LodeFile(const string& path) {
	FILE* p = fopen(path.c_str(), "rb");
	if (!p)
		exit(0);
	char str[N + 1];
	strcpy_s(str, path.c_str());
	stack <string> str_stack;
	stack <string> switchCase;
	while (fgets(str, N, p) != NULL) {
		//printf("%s", str);
		//cout << str ;
		countKey(str);
		if (isElseIf(str)) {
			// cout << "ELSE IF" << endl;
			str_stack.push("else if");
		} else if (isElse(str)) {
			// cout << "ELSE" << endl;
			str_stack.push("else");
			countNumIf(str_stack);
		} else if (isIf(str)) {
			// cout << "IF" << endl;
			str_stack.push("if");
		} else if (isSwitch(str)) {
			//cout << "SWITCH" << endl;
			switchCase.push("switch");
		} else if (isCase(str)) {
			// cout << "CASE" << endl;
			switchCase.push("case");
		} else {
		}
	}
	countNumSwitch(switchCase);
	fclose(p);
}

int main()
{
	File file;
	file.LodeFile("C:/Users/Sakura_Six/Desktop/EE308 Èí¼þ¹¤³Ì/Lab/Lab1/testFile.cpp");
	cout <<"total num:"<< countKeyNum << endl;
	cout <<"switch num:" << switchNum << endl;
	cout << "case num:";
	for (int i = switchNum - 1; i >= 0; i--) {
		cout<< caseNum[i] << " ";
	}
	cout << endl;
	cout <<"if-else num: " << ifelseNum << endl;
	cout<<"if-else-else num: " << ifelseifNum << endl;
	
	return 0;
}

