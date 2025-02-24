// SMIS.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once

#include <iostream>
#include <list>
#include <string>
#include <regex>
#include <thread>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <conio.h>

using namespace std;

struct Students {
	string name;
	string className;
	string stdId;
	float score;
	Students() : score(0.0f) {}
	// 创建一个Students对象但未提供任何参数时,score的初始值被设置成0.

};
/* 图省事,教师和学生共用这个结构体.
 * (Teacher)className->授课班级;stdId为"Teacher";score为0.
 */

struct Account {
	string username;
	string password;
};

struct User {
	Students student;
	Account account;
};

// 打开文件失败是最高级错误, 会在cin >> 后直接退出.

list<User> getMessage();

void putMessage(const list<User> &head);

bool usernameRegex(const string& username);

bool passwordRegex(const string& String);

bool compareByScore(const Students& first, const Students& second);

bool avoidRegisterRepeating(const string& account);

bool avoidChangeRepeating(const string& account);

bool avoidAppealRepeating(const string& stdId);

void Register();

void dataEditing(const string& account, const string& password);

bool Login(const list<User> &head,list<User>::iterator* it);

void Student(list<User> &head,const User &user);

void Teacher(list<User> &head,const User &user);

void Admin(list<User> &head);

void todos(list<User> &head);


inline list<User> getMessage() {
	list<User> head;
	fstream file;
	file.open("message.txt", ios::in);
	if (!file.is_open()) {
		system("cls");
		cout << "Student Information Management System" << endl;
		cout << "---------------------------------------------" << endl;
		cout << "Unable to open the file." << endl;
		cout << "Please enter any key to exit." << endl;
		char ch;
		cin >> ch;
		exit(0);
	}
	// 以读取模式打开数据文件

	string line;
	while (getline(file, line)) {
		istringstream iss(line);
		User user;
		iss >> user.student.name
			>> user.student.className
			>> user.student.stdId
			>> user.student.score;
		iss >> user.account.username
			>> user.account.password;
		if (iss.fail()) {
			system("cls");
			cout << "Student Information Management System" << endl;
			cout << "---------------------------------------------" << endl;
			cout << "A line format error has occurred." << line << endl;
			cout << "Please enter any key to continue..." << endl;
			char ch;
			cin >> ch;
			continue;
		}
		// while循环中读取每行数据并作为字符串流解析

		head.push_back(user); // 入栈
	}
	file.close();
	return head;
} // 数据读取函数

inline void putMessage(const list<User> &head) {
		ofstream file("message.txt", ios::out | ios::trunc);
		if (!file.is_open()) {
			system("cls");
			cout << "Student Information Management System" << endl;
			cout << "---------------------------------------------" << endl;
			cout << "Unable to open the file." << endl;
			cout << "Please enter any key to exit." << endl;
			char ch;
			cin >> ch;
			exit(0);
		}
		// 以覆写模式打开数据文件

		auto iter = head.begin();
		while (iter != head.end()) {
			file << iter->student.name << ' '
				 << iter->student.className << ' '
				 << iter->student.stdId << ' '
				 << iter->student.score << ' ';
			file << iter->account.username << ' '
				 << iter->account.password << endl;
			++iter;
		}
		file.close();
} // 数据写入函数

inline bool passwordRegex(const string& String) {
	const regex pattern(R"(^(?=.*\d)(?=.*[a-z])(?=.*[A-Z])[a-zA-Z0-9]{8,16}$)");
	return regex_match(String, pattern);
}
// 密码正则函数: 8-16字符; 包含数字和大小写字母

inline bool usernameRegex(const string &username) {
	const regex pattern(R"(^.{4,12}$)");
	return regex_match(username, pattern);
}
// 用户名正则函数: 4-12字符

inline bool avoidRegisterRepeating(const string& account) {
	ifstream file("account.txt", ios::in);
	if (!file) {
		system("cls");
		cout << "Student Information Management System" << endl;
		cout << "---------------------------------------------" << endl;
		cout << "Unable to open the file." << endl;
		cout << "Please enter any key to exit." << endl;
		char ch;
		cin >> ch;
		exit(0);
	}
	// 以读取模式打开注册请求文件

	string line;
	while (getline(file, line)) {
		system("cls");
		istringstream iss(line);
		string name, className, stdId, username, password;
		if (float score; !(iss >> name >> className >> stdId >> score >> username >> password) && !line.empty() ) {
			system("cls");
			cout << "Student Information Management System" << endl;
			cout << "---------------------------------------------" << endl;
			cout << "A line format error has occurred." << endl;
			cout << "Please enter any key to continue..." << endl;
			char ch;
			cin >> ch;
			continue;
		}
		if (username == account) {
			file.close();
			return true;
		}
		// 根据用户名判断是否重复
	}
	file.close();
	return false;
}
/* 寻找account.txt注册请求重复项函数
 * 返回true则表示存在重复
 */

inline void dataEditing(const string& username, const string& password, list<User> &head) {
	fstream file;
	file.open("account.txt", ios::app);
	if (!file) {
		system("cls");
		cout << "Student Information Management System" << endl;
		cout << "---------------------------------------------" << endl;
		cout << "Unable to open the file." << endl;
		cout << "Please enter any key to exit." << endl;
		char ch;
		cin >> ch;
		exit(0);
	}
	// 以追加模式打开文件

	system("cls");
	cout << "Student Information Management System" << endl;
	cout << "---------------------------------------------" << endl;
	cout << "Please edit your personal profile now." << endl;
	cout << "Your identity is that of..." << endl;
	cout << "1. Student" << endl;
	cout << "2. Teacher" << endl;
	cout << "---------------------------------------------" << endl;
	cout << "Enter the corresponding serial number to execute the function: " << endl;
	cout << ">> ";
	char da;
	cin >> da;
	if (da == '1') {
		system("cls");
		cout << "Student Information Management System" << endl;
		cout << "---------------------------------------------" << endl;
		cout << "Please enter your name,class and studentID." << endl;
		cout << "Tip. the student ID number is limited to 11 numbers specified by XUPT." << endl;
		string name, Class, studentID;
		cin >> name >> Class >> studentID;
		if (avoidRegisterRepeating(username)) {
			file.close();
			system("cls");
			cout << "Student Information Management System" << endl;
			cout << "---------------------------------------------" << endl;
			cout << "The corresponding account name has been applied for registration." << endl;
			cout << "Enter any key to continue..." << endl;
			char ch;
			cin >> ch;
			return;
		}

		auto iter = head.begin();
		while (iter != head.end()) {
			if (iter->student.stdId == studentID) {
				iter->account.username = username;
				iter->account.password = password;
				system("cls");
				cout << "Student Information Management System" << endl;
				cout << "---------------------------------------------" << endl;
				cout << "Login successfully!" << endl;
				cout << "Please enter any key to exit." << endl;
				char ch;
				cin >> ch;
				file.close();
				return;
			}
			++iter;
		}

		file << name << ' ' << Class << ' ' << studentID << " 0.0 ";
		file << username << ' ' << password << endl;
		system("cls");
		cout << "Student Information Management System" << endl;
		cout << "---------------------------------------------" << endl;
		cout << "Submitted successfully!Awaiting administrator approval." << endl;
		cout << "Please enter any key to exit." << endl;
		char ch;
		cin >> ch;
		file.close();
	}

	if (da == '2') {
		system("cls");
		cout << "Student Information Management System" << endl;
		cout << "---------------------------------------------" << endl;
		cout << "Please enter your name and teachingClass." << endl;
		string name, teachingClass;
		cin >> name >> teachingClass;
		if (avoidRegisterRepeating(username)) {
			file.close();
			system("cls");
			cout << "Student Information Management System" << endl;
			cout << "---------------------------------------------" << endl;
			cout << "The corresponding account name has been applied for registration." << endl;
			cout << "Enter any key to continue..." << endl;
			char ch;
			cin >> ch;
			return;
		}
		file << name << ' ' << teachingClass << " Teacher 0.0 ";
		file << username << ' ' << password << endl;
		system("cls");
		cout << "Student Information Management System" << endl;
		cout << "---------------------------------------------" << endl;
		cout << "Submitted successfully!Awaiting administrator approval." << endl;
		cout << "Please enter any key to exit." << endl;
		char ch;
		cin >> ch;
		file.close();
	}

}
// 资料编辑函数

inline void Register(list<User> &head) {
	while (true) {
		system("cls");
		cout << "Student Information Management System" << endl;
		cout << "---------------------------------------------" << endl;
		cout << "Please enter the preset username and password." << endl;
		cout << "First. Ensure that the username is between 4 and 12 characters in length." << endl;
		cout << "Second. Ensure that the password is between 8 and 16 characters in length." << endl;
		cout << "Third. Ensure that the password contain uppercase and lowercase letters as well as numbers." << endl;
		string username, password;
		cin >> username;

		char ch;
		while((ch = _getch()) != '\r') {
			if(ch == '\b' && !password.empty()) {
				password.pop_back();
				cout << "\b \b";
			}
			else if(!(ch == '\b' && password.empty())) {
				password.push_back(ch);
				_putch('*');
			}
		}
		/* 密码保护设置,输入的字符显示成星号,其实还能做按需显示的功能:
		 * 清空当前行->输出存到的所有字符->继续输出字符 or 清空当前行->输出存到字符个数个星号->原逻辑输出
		 * 不会处理缓冲区问题,于是将getchar()循环改成windows的_getch()函数.
		 * Clang-Tidy: Narrowing conversion from 'int' to signed type 'char' is implementation-defined
		 * 窄型转换警告好烦.
		 */

		if (usernameRegex(username) && passwordRegex(password)) {
			dataEditing(username, password, head);
			return;
		}
		/* 正则匹配!进入资料编辑栏.
		 * 资料编辑被设计成强制执行,如果用户点终端叉叉那么原来输入的账密不会存到链表里.
		 * 这样可以省下做Student和User匹配的工作.
		 */

		system("cls");
		cout << "Student Information Management System" << endl;
		cout << "---------------------------------------------" << endl;
		cout << "The username or password format is incorrect." << endl;
		cout << "If try again,please press 1 key to continue..." << endl;
		cout << "And press any other key to exit." << endl;
		cin >> ch;
		if (ch != '1') break;
	}
}
/* 注册函数
 * 同一个用户名不能被多次申请注册(在资料编辑函数体现)
 */

inline bool avoidChangeRepeating(const string& account) {
	ifstream file("target.txt");
	if (!file) {
		system("cls");
		cout << "Student Information Management System" << endl;
		cout << "---------------------------------------------" << endl;
		cout << "Unable to open the file." << endl;
		cout << "Please enter any key to exit." << endl;
		char ch;
		cin >> ch;
		exit(0);
	}
	string line;
	while (getline(file, line)) {
		istringstream iss(line);
		string username, oldPassword;
		if (string newPassword; !(iss >> username >> oldPassword >> newPassword) && !line.empty() ) {
			system("cls");
			cout << "Student Information Management System" << endl;
			cout << "---------------------------------------------" << endl;
			cout << "A line format error has occurred." << line << endl;
			cout << "Please enter any key to continue..." << endl;
			char ch;
			cin >> ch;
			continue;
		}
		if (username == account) {
			file.close();
			return true;
		}
	}
	file.close();
	return false;
}
/* 寻找target.txt改密申请重复项函数
 * 返回true则表示存在重复
 * 同样根据用户名判断是否重复
 */

inline bool Login(const list<User> &head,list<User>::iterator* it) {
	while (true) {
		system("cls");
		cout << "Student Information Management System" << endl;
		cout << "---------------------------------------------" << endl;
		cout << "1. Login" << endl;
		cout << "2. Change Password?" << endl;
		cout << "0. Return to the previous level" << endl;
		cout << "---------------------------------------------" << endl;
		cout << "Enter the corresponding serial number to execute the function: " << endl;
		cout << ">> ";
		char lo;
		cin >> lo;
		if (lo == '1') {
			string username, password;
			system("cls");
			cout << "Student Information Management System" << endl;
			cout << "---------------------------------------------" << endl;
			cout << "Please enter the username and password: " << endl;
			cin >> username;

			char ch;
			while((ch = _getch()) != '\r') {
				if(ch == '\b' && !password.empty()) {
					password.pop_back();
					cout << "\b \b";
				}
				else if(!(ch == '\b' && password.empty())) {
					password.push_back(ch);
					_putch('*');
				}
			}

			list<User> temp = head;
			auto iter = temp.begin();
			while (iter != temp.end()) {
				if (iter->account.username == username && iter->account.password == password) {
					system("cls");
					cout << "Student Information Management System" << endl;
					cout << "---------------------------------------------" << endl;
					cout << "Login successful!" << endl;
					*it = iter;
					cout << "Enter any key to continue..." << endl;
					cin >> ch;
					return true;
				}
				++iter;
			}
			system("cls");
			cout << "Student Information Management System" << endl;
			cout << "---------------------------------------------" << endl;
			cout << "Login failed.Press 1 key to continue..." << endl;
			cout << "Or press any other key to exit" << endl;
			cin >> ch;
			if (ch != '1') return false;
			// 登录失败反馈
		}
		if (lo == '2'){
			string username,originalPassword,changePassword;
			system("cls");
			cout << "Student Information Management System" << endl;
			cout << "---------------------------------------------" << endl;
			cout << "Please enter the username,original password and the password you want to change to: " << endl;
			cin >> username >> originalPassword >> changePassword;
			if (originalPassword == changePassword) {
				system("cls");
				cout << "Student Information Management System" << endl;
				cout << "---------------------------------------------" << endl;
				cout << "The new password cannot be the same as the new password." << endl;
				cout << "Enter any key to continue..." << endl;
				char ch;
				cin >> ch;
				continue;
			} // 错误路径1: 新旧密码相同
			list<User> temp = head;
			auto iter = temp.begin();
			while (iter != temp.end()) {
				if (iter->account.username == username && iter->account.password == originalPassword) {
					fstream file;
					file.open("target.txt", ios::app);
					if (!file) {
						system("cls");
						cout << "Student Information Management System" << endl;
						cout << "---------------------------------------------" << endl;
						cout << "Unable to open the file." << endl;
						cout << "Please enter any key to exit." << endl;
						char ch;
						cin >> ch;
						exit(0);
					}
					// 以追加模式打开改密申请文件

					if (avoidChangeRepeating(iter->account.username)) {
						system("cls");
						cout << "Student Information Management System" << endl;
						cout << "---------------------------------------------" << endl;
						cout << "The corresponding account name has been applied for change password." << endl;
						file.close();
					} // 错误路径2: 重复申请
					else {
						file << username << ' ' << originalPassword << ' ' << changePassword << endl;
						system("cls");
						cout << "Student Information Management System" << endl;
						cout << "---------------------------------------------" << endl;
						cout << "Location and application successful!" << endl;
					}
					cout << "Enter any key to continue..." << endl;
					char ch;
					cin >> ch;
					return false;
				}
				++iter;
			}
			if (iter == temp.end()) {
				char ch;
				system("cls");
				cout << "Student Information Management System" << endl;
				cout << "---------------------------------------------" << endl;
				cout << "Sorry,The username or password is incorrect or the account may be nonexistent." << endl;
				cout << "If try again,please press 1 key to continue..." << endl;
				cout << "And press any other key to exit." << endl;
				cin >> ch;
				if (ch != '1') return false;
			} // 错误路径3: 未找到账号
		}
		if (lo == '0'){
			return false;
		}
	}
}

/* 登录函数
 * 包含了登录,密码修改等需求
 * 密码修改的请求与用户名一一对应
 */

inline bool avoidAppealRepeating(const string& stdId) {
	ifstream file("appeal.txt");
	if (!file) {
		system("cls");
		cout << "Student Information Management System" << endl;
		cout << "---------------------------------------------" << endl;
		cout << "Unable to open the file." << endl;
		cout << "Please enter any key to exit." << endl;
		char ch;
		cin >> ch;
		exit(0);
	}
	string line;
	while (getline(file, line)) {

		system("cls");
		istringstream iss(line);
		string name, studentID;
		float score, real;
		if (string className; !(iss >> name >> className >> studentID >> score >> real) && !line.empty() ) {
			system("cls");
			cout << "Student Information Management System" << endl;
			cout << "---------------------------------------------" << endl;
			cout << "Format does not meet expectations." << endl;
			cout << "Enter any key to continue..." << endl;
			char ch;
			cin >> ch;
			continue;
		}
		if (stdId == studentID) {
			file.close();
			return true;
		}
	}
	file.close();
	return false;
}
/* 寻找appeal.txt改密申请重复项函数
 * 返回true则表示存在重复
 * 根据学号判断是否重复
 */

inline void Student(list<User> &head,const User &user) { // (head, *it)
	char st;
	while (true) {
		system("cls");
		cout << user.student.name << ",welcome to use Student Information Management System!" << endl;
		cout << "---------------------------------------------" << endl;
		cout << "1. Grade Inquiry" << endl;
		cout << "2. Class grades" << endl;
		cout << "3. Grade ranking" << endl;
		cout << "4. Grade Appeal" << endl;
		cout << "0. Return to the previous level" << endl;
		cout << "---------------------------------------------" << endl;
		cout << "Enter the corresponding serial number to execute the function: " << endl;
		cout << ">> ";
		cin >> st;
		if (st == '1') {
			system("cls");
			cout << "Student Information Management System" << endl;
			cout << "---------------------------------------------" << endl;
			cout << "Your grade is: " << user.student.score << endl;
			cout << "Enter any key to continue..." << endl;
			char ch;
			cin >> ch;
			continue;
		}
		if (st == '2') {
			auto iter = head.begin();
			int counter = 0;
			system("cls");
			cout << "Student Information Management System" << endl;
			cout << "---------------------------------------------" << endl;
			while (iter != head.end()) {
				if (iter->student.className == user.student.className && iter->student.stdId != "Teacher") {
					cout << iter->student.name << ' ' << iter->student.score << endl;
					++counter;
				}
				++iter;
			}
			if (iter == head.end() && !counter) {
				cout << "Based on the data,we have only found your grade." << endl;
			}
			cout << "Please enter any key to continue..." << endl;
			char ch;
			cin >> ch;
			continue;
		}
		if (st == '3') {
			system("cls");
			list<User> temp = head;
			auto iter = temp.begin();
			vector grades{user.student.score};
			while (iter != temp.end()) {
				if (iter->student.className == user.student.className && iter->student.stdId != user.student.stdId && iter->student.stdId != "Teacher") {
					grades.push_back(iter->student.score);
				}
				++iter;
			}
			if (iter == temp.end()) {
				sort(grades.begin(), grades.end());
				const size_t all = grades.size();
				int i = all;
				while (i > 0) {
					--i;
					if (grades[i] == user.student.score) {
						system("cls");
						cout << "Student Information Management System" << endl;
						cout << "---------------------------------------------" << endl;
						cout << "Your ranking in the grade is: " << all - i << '/' << all << endl;
						break;
					}
				}
			}
			cout << "Please enter any key to continue..." << endl;
			char ch;
			cin >> ch;
			continue;
		}
		if (st == '4') {
			system("cls");
			cout << "Student Information Management System" << endl;
			cout << "---------------------------------------------" << endl;
			cout << "Enter the score you believe you truly deserve." << endl;
			float real;
			cin >> real;
			int counter = 0;
			if (!avoidAppealRepeating(user.student.stdId)) {
				fstream file;
				file.open("appeal.txt", ios::app);
				file << user.student.name << ' ' << user.student.className << ' ' << user.student.stdId << ' ' << user.student.score << ' ' << real << endl;
				file.close();
				system("cls");
				cout << "Student Information Management System" << endl;
				cout << "---------------------------------------------" << endl;
				cout << "Request successful!Awaiting administrator reply." << endl;
				++counter;
			}
			if (!counter) {
				system("cls");
				cout << "Student Information Management System" << endl;
				cout << "---------------------------------------------" << endl;
				cout << "You have already appealed." << endl;
			}
			cout << "Please enter any key to continue..." << endl;
			char ch;
			cin >> ch;
			continue;
		}
		if (st == '0'){
			system("cls");
			return;
		}
	}
}
/* 学生函数
 * 包含了成绩查询,获取排名,成绩申诉等需求
 * 至多进行一次成绩申诉.
 */

inline bool compareByScore(const Students& first, const Students& second) {
	return first.score > second.score;
}
/* 降序比较函数
 * 但比较的是Students结构体
 */

inline void Teacher(list<User> &head,const User &user) {
	while (true) {
		system("cls");
		cout << user.student.name << ",welcome to use Student Information Management System!" << endl;
		cout << "---------------------------------------------" << endl;
		cout << "1. Add student information" << endl;
		cout << "2. Delete student information" << endl;
		cout << "3. Change student information" << endl;
		cout << "4. Inquire about student information" << endl;
		cout << "5. Output the grades of this class" << endl;
		cout << "6. Download to files" << endl;
		cout << "7. Class grade ranking" << endl;
		cout << "8. Remind of grade updates" << endl;
		cout << "0. Return to the previous level" << endl;
		cout << "---------------------------------------------" << endl;
		cout << "Enter the corresponding serial number to execute the function: " << endl;
		cout << ">> ";
		char te;
		cin >> te;
		if (te == '1') {
			float score;
			string name, Class, studentID;
			system("cls");
			cout << "Student Information Management System" << endl;
			cout << "---------------------------------------------" << endl;
			cout << "Please enter the student's name,class,studentID and score(if not,fill in 0)." << endl;
			cin >> name >> Class >> studentID >> score;

			auto iter = head.begin();
			while (iter != head.end()) {
				if (iter->student.stdId == studentID) {
					system("cls");
					cout << "Student Information Management System" << endl;
					cout << "---------------------------------------------" << endl;
					cout << "The student has been recorded in the system." << endl;
					break;
				}
				++iter;
			}
			if (iter == head.end()) {
				User newone;
				newone.student.name = name;
				newone.student.className = Class;
				newone.student.stdId = studentID;
				newone.student.score = score;

				newone.account.username = studentID;
				newone.account.password = studentID;

				head.push_back(newone);
				system("cls");
				cout << "Student Information Management System" << endl;
				cout << "---------------------------------------------" << endl;
				cout << "Student information added successfully." << endl;
				cout << "Wait for the administrator to update or restart the program to check the results." << endl;
			}
			cout << "Please enter any key to continue..." << endl;
			char ch;
			cin >> ch;
			continue;
		}
		if (te == '2') {
			string name, studentID;
			system("cls");
			cout << "Student Information Management System" << endl;
			cout << "---------------------------------------------" << endl;
			cout << "Please enter the student's name and studentID" << endl;
			cin >> name >> studentID;
			auto iter = head.begin();
			while (iter != head.end()) {
				if (iter->student.name == name && iter->student.stdId == studentID) {
					head.erase(iter);
					system("cls");
					cout << "Student Information Management System" << endl;
					cout << "---------------------------------------------" << endl;
					cout << "Student information deleted successfully." << endl;
					cout << "Wait for the administrator to update or restart the program to check the results." << endl;
					break;
				}
				++iter;
			}
			if (iter == head.end()) {
				system("cls");
				cout << "Student Information Management System" << endl;
				cout << "---------------------------------------------" << endl;
				cout << "Sorry,do not find this student." << endl;
			} // 错误路径: 未找到同学
			cout << "Please enter any key to continue..." << endl;
			char ch;
			cin >> ch;
			continue;
		}
		if (te == '3') {
			system("cls");
			cout << "Student Information Management System" << endl;
			cout << "---------------------------------------------" << endl;
			cout << "Please enter the student's name whose grade you want to change." << endl;
			string name;
			cin >> name;

			auto iter = head.begin();
			while (iter != head.end()) {
				if (iter->student.name == name) {
					system("cls");
					cout << "Student Information Management System" << endl;
					cout << "---------------------------------------------" << endl;
					cout << "Please enter the grade you want to change to: " << endl;
					float score;
					cin >> score;
					iter->student.score = score;
					system("cls");
					cout << "Student Information Management System" << endl;
					cout << "---------------------------------------------" << endl;
					cout << "Changed successfully!" << endl;
					cout << "Wait for the administrator to update or restart the program to check the results." << endl;
					break;
				}
				++iter;
			}
			if (iter == head.end()) {
				system("cls");
				cout << "Student Information Management System" << endl;
				cout << "---------------------------------------------" << endl;
				cout << "Sorry,do not find this student." << endl;
			}
			cout << "Please enter any key to continue..." << endl;
			char ch;
			cin >> ch;
			continue;
		}
		if (te == '4') {
			system("cls");
			cout << "Student Information Management System" << endl;
			cout << "---------------------------------------------" << endl;
			cout << "Enter the student's name for the information you want to query." << endl;
			string name;
			cin >> name;
			auto iter = head.begin();
			while (iter != head.end()) {
				if (iter->student.name == name) {
					system("cls");
					cout << "Student Information Management System" << endl;
					cout << "---------------------------------------------" << endl;
					cout << iter->student.name << ' ' << iter->student.className << ' ' << iter->student.stdId << ' ' << iter->student.score << endl;
					break;
				}
				++iter;
			}
			if (iter == head.end()) {
				system("cls");
				cout << "Student Information Management System" << endl;
				cout << "---------------------------------------------" << endl;
				cout << "Sorry,do not find this student." << endl;
			}
			cout << "Please enter any key to continue..." << endl;
			char ch;
			cin >> ch;
			continue;
		}
		if (te == '5') {
			system("cls");
			cout << "Student Information Management System" << endl;
			cout << "---------------------------------------------" << endl;
			int counter = 0;
			auto iter = head.begin();
			while (iter != head.end()) {
				if (iter->student.className == user.student.className && iter->student.stdId != "Teacher" ) {
					cout << iter->student.name << ' ' << iter->student.className << ' ' << iter->student.stdId << ' ' << iter->student.score << endl;
					++counter;
				}
				++iter;
			}
			if (iter == head.end() && !counter) {
				cout << "Based on the data,we did not find any information." << endl;
			}
			cout << "Please enter any key to continue..." << endl;
			char ch;
			cin >> ch;
			continue;
		}
		if (te == '6') {
			string filename;
			system("cls");
			cout << "Student Information Management System" << endl;
			cout << "---------------------------------------------" << endl;
			cout << "Please enter the complete path to save the file(example: /path/to/save/example_data.txt): " << endl;
			cin >> filename;
			if (filename.empty()) {
				system("cls");
				cout << "Student Information Management System" << endl;
				cout << "---------------------------------------------" << endl;
				cout << "The file path cannot be empty." << endl;
				cout << "Please enter any key to continue..." << endl;
				char ch;
				cin >> ch;
				continue;
			}

			fstream openFile;
			openFile.open(filename, ios::out);
			if (!openFile) {
				system("cls");
				cout << "Student Information Management System" << endl;
				cout << "---------------------------------------------" << endl;
				cout << "Unable to open the file." << endl;
				cout << "Please enter any key to exit." << endl;
				char ch;
				cin >> ch;
				exit(0);
			}

			fstream file;
			file.open("message.txt", ios::in);
			if (!file) {
				system("cls");
				cout << "Student Information Management System" << endl;
				cout << "---------------------------------------------" << endl;
				cout << "Unable to open the file." << endl;
				cout << "Please enter any key to exit." << endl;
				char ch;
				cin >> ch;
				exit(0);
			}
			string line;
			while (getline(file,line)) {
				istringstream iss(line);
				User temp;
				iss >> temp.student.name
					>> temp.student.className
					>> temp.student.stdId
					>> temp.student.score;
				iss >> temp.account.username
					>> temp.account.password;
				if (temp.student.className == user.student.className && temp.student.stdId != "Teacher") {
					openFile << line << endl;
				}
			}
			file.close();
			openFile.close();
			system("cls");
			cout << "Student Information Management System" << endl;
			cout << "---------------------------------------------" << endl;
			cout << "The data file has been saved at: " << filename << endl;
			cout << "Please enter any key to continue..." << endl;
			char ch;
			cin >> ch;
			continue;
		}
		if (te == '7') {
			system("cls");
			cout << "Student Information Management System" << endl;
			cout << "---------------------------------------------" << endl;
			list<Students> temp;
			auto iter = head.begin();
			while (iter != head.end()) {
				if (iter->student.className == user.student.className && iter->student.stdId != "Teacher" ) {
					temp.push_back(iter->student);
				}
				++iter;
			}
			if (temp.empty()) {
				cout << "Based on the data,we did not find any information." << endl;
				cout << "Please enter any key to continue..." << endl;
				char ch;
				cin >> ch;
				continue;
			}
			temp.sort(compareByScore);
			auto it = temp.begin();
			while (it != temp.end()) {
				cout << it->name << ' ' << it->className << ' ' << it->stdId << ' ' << it->score << endl;
				++it;
			}
			cout << "Please enter any key to continue..." << endl;
			char ch;
			cin >> ch;
			continue;
		}
		if (te == '8') {
			system("cls");
			cout << "Student Information Management System" << endl;
			cout << "---------------------------------------------" << endl;
			fstream file;
			file.open("update.txt",ios::app);
			if (!file.is_open()) {
				system("cls");
				cout << "Student Information Management System" << endl;
				cout << "---------------------------------------------" << endl;
				cout << "Unable to open the file." << endl;
				cout << "Please enter any key to exit." << endl;
				char ch;
				cin >> ch;
				exit(0);
			}
			file.close();
			file << "Teacher " << user.student.name << " " << "request to update the grade database." << endl;
			cout << "Request successful!Awaiting administrator reply." << endl;
			cout << "Please enter any key to continue..." << endl;
			char ch;
			cin >> ch;
			continue;
		}
		if (te == '0'){
			system("cls");
			return;
		}
	}
}
/* 教师函数
 * 包含了增删改查学生信息,输出本班成绩,下载到文件中,提醒成绩更新等需求
 */

inline void todos(list<User> &head) {
	while (true) {
		system("cls");
		cout << "Student Information Management System" << endl;
		cout << "---------------------------------------------" << endl;
		cout << "1. Account registration request" << endl;
		cout << "2. Password change request" << endl;
		cout << "3. View the request for grade appeals" << endl;
		cout << "4. View request to update grade database" << endl;
		cout << "0. Return to the previous level" << endl;
		cout << "---------------------------------------------" << endl;
		cout << "Enter the corresponding serial number to execute the function: " << endl;
		cout << ">> ";
		char todo;
		cin >> todo;
		if (todo == '1') {
			fstream file;
			file.open("account.txt", ios::in);
			if (!file) {
				system("cls");
				cout << "Student Information Management System" << endl;
				cout << "---------------------------------------------" << endl;
				cout << "Unable to open the file." << endl;
				cout << "Please enter any key to exit." << endl;
				char ch;
				cin >> ch;
				exit(0);
			}
			string line;
			while (getline(file, line)) {
				system("cls");
				istringstream iss(line);
				User user;
				iss >> user.student.name
					>> user.student.className
					>> user.student.stdId
					>> user.student.score;
				iss >> user.account.username
					>> user.account.password;
				if (iss.fail()) {
					cout << "Student Information Management System" << endl;
					cout << "---------------------------------------------" << endl;
					cout << "A line format error has occurred." << line << endl;
					cout << "Please enter any key to continue..." << endl;
					char ch;
					cin >> ch;
					continue;
				}
				system("cls");
				cout << "Student Information Management System" << endl;
				cout << "---------------------------------------------" << endl;
				cout << line << endl;
				cout << "If you approve the registration request,please press 1." << endl;
				cout << "And press any other key to get next one." << endl;
				char ch;
				cin >> ch;
				if (ch == '1') {
					head.push_back(user);
				}
			}
			file.close();
			fstream defile("account.txt", ios::out | ios::trunc);
			defile.close();
			continue;
		}
		if (todo == '2') {
			system("cls");
			fstream file;
			file.open("target.txt", ios::in);
			if (!file) {
				system("cls");
				cout << "Student Information Management System" << endl;
				cout << "---------------------------------------------" << endl;
				cout << "Unable to open the file." << endl;
				cout << "Please enter any key to exit." << endl;
				char ch;
				cin >> ch;
				exit(0);
			}
			string line;
			while (getline(file, line)) {
				istringstream iss(line);
				string account, oldPassword, newPassword;
				iss >> account >> oldPassword >> newPassword;
				if (iss.fail()) {
					system("cls");
					cout << "Student Information Management System" << endl;
					cout << "---------------------------------------------" << endl;
					cout << "A line format error has occurred." << line << endl;
					cout << "Please enter any key to continue..." << endl;
					char ch;
					cin >> ch;
					continue;
				}
				Account User = {account, newPassword};
				auto it = head.begin();
				while (it != head.end()) {
					if (it->account.username == account && it->account.password == oldPassword) {
						system("cls");
						cout << "Student Information Management System" << endl;
						cout << "---------------------------------------------" << endl;
						cout << line << endl;
						cout << "If you approve this password change request,please press 1." << endl;
						cout << "And press any other key to get next one." << endl;
						char ch;
						cin >> ch;
						if (ch == '1') {
							it->account = User;
						}
						break;
					}
					++it;
				}
			}
			file.close();
			fstream defile("target.txt", ios::out | ios::trunc);
			defile.close();
			continue;
		}
		if (todo == '3') {
			system("cls");
			fstream file;
			file.open("appeal.txt", ios::in);
			if (!file) {
				system("cls");
				cout << "Student Information Management System" << endl;
				cout << "---------------------------------------------" << endl;
				cout << "Unable to open the file." << endl;
				cout << "Please enter any key to continue..." << endl;
				char ch;
				cin >> ch;
				continue;
			}
			string line;
			while (getline(file, line)) {
				istringstream iss(line);
				string name, className, stdId;
				float oldScore, newScore;
				iss >> name >> className >> stdId >> oldScore >> newScore;
				if (iss.fail()) {
					system("cls");
					cout << "Student Information Management System" << endl;
					cout << "---------------------------------------------" << endl;
					cout << "A line format error has occurred." << line << endl;
					cout << "Please enter any key to continue..." << endl;
					char ch;
					cin >> ch;
				}
				system("cls");
				cout << "Student Information Management System" << endl;
				cout << "---------------------------------------------" << endl;
				cout << line << endl;
				cout << "If you approve this password change request,please press 1." << endl;
				cout << "And press any other key to get next one." << endl;
				char ch;
				cin >> ch;
				if (ch == '1') {
					auto it = head.begin();
					while (it != head.end()) {
						if (it->student.stdId == stdId) {
							it->student.score = newScore;
							break;
						}
						++it;
					}
				}
			}
			file.close();
			fstream defile("appeal.txt", ios::out | ios::trunc);
			defile.close();
			continue;
		}
		if (todo == '4') {
			system("cls");
			fstream file;
			file.open("update.txt", ios::in);
			if (!file) {
				system("cls");
				cout << "Student Information Management System" << endl;
				cout << "---------------------------------------------" << endl;
				cout << "Unable to open the file." << endl;
				cout << "Please enter any key to exit." << endl;
				char ch;
				cin >> ch;
				exit(0);
			}

			system("cls");
			cout << "Student Information Management System" << endl;
			cout << "---------------------------------------------" << endl;
			string line;
			while (getline(file, line)) {
				cout << line << endl;
			}
			cout << "If you approve these update grade database requests,please press 1." << endl;
			cout << "And press any other key to get next one." << endl;
			char ch;
			cin >> ch;
			if (ch == '1'){
				putMessage(head);
			}
			file.close();
			fstream defile("update.txt", ios::out | ios::trunc);
			defile.close();
			continue;
		}
		if (todo == '0') {
			return;
		}
	}
}
/* 管理员代办函数
 * 包含账户注册,密码修改,成绩申诉和更新成绩库等请求,每个请求对应一个文件
 * 不论管理员对每行请求的态度与否,在管理员处理某类请求后文件被清空
 */

inline void Admin(list<User> &head) {
	while (true) {
		system("cls");
		cout << "Student Information Management System" << endl;
		cout << "---------------------------------------------" << endl;
		cout << "1. View to-dos" << endl;
		cout << "2. Enter the teacher's end to modify the information" << endl;
		cout << "3. Delete accounts" << endl;
		cout << "4. Change accounts" << endl;
		cout << "5. Inquire about accounts" << endl;
		cout << "6. Enter all accounts" << endl;
		cout << "7. Output all accounts" << endl;
		cout << "0. Return to the previous level" << endl;
		cout << "---------------------------------------------" << endl;
		cout << "Enter the corresponding serial number to execute the function: " << endl;
		cout << ">> ";
		char ad;
		cin >> ad;
		if (ad == '1') {
			todos(head);
			continue;
		}
		if (ad == '2') {
			User temp;
			temp.student.name = "Administrator";
			Teacher(head,temp);
			continue;
		}
		if (ad == '3') {
			system("cls");
			cout << "Student Information Management System" << endl;
			cout << "---------------------------------------------" << endl;
			cout << "Enter the account you want to delete: " << endl;
			string username;
			cin >> username;
			auto iter = head.begin();
			while (iter != head.end()) {
				if (iter->account.username == username) {
					head.erase(iter);
					system("cls");
					cout << "Student Information Management System" << endl;
					cout << "---------------------------------------------" << endl;
					cout << "Deleted successfully!" << endl;
					break;
				}
				++iter;
			}
			if (iter == head.end()) {
				system("cls");
				cout << "Student Information Management System" << endl;
				cout << "---------------------------------------------" << endl;
				cout << "Based on the data,we did not find this account." << endl;
			}
			cout << "Please enter any key to continue..." << endl;
			char ch;
			cin >> ch;
			continue;
		}
		if (ad == '4') {
			system("cls");
			cout << "Student Information Management System" << endl;
			cout << "---------------------------------------------" << endl;
			cout << "1. Change username" << endl;
			cout << "2. Change password" << endl;
			cout << "0. Return to the previous level" << endl;
			cout << "---------------------------------------------" << endl;
			cout << "Enter the corresponding serial number to execute the function: " << endl;
			cout << ">> ";
			char i;
			string username;
			string temp;
			cin >> i;
			if (i == '1') {
				system("cls");
				cout << "Student Information Management System" << endl;
				cout << "---------------------------------------------" << endl;
				cout << "Enter the account you want to change and the new username." << endl;
				cin >> username >> temp;
				auto iter = head.begin();
				while (iter != head.end()) {
					if (iter->account.username == username) {
						iter->account.username = temp;
						system("cls");
						cout << "Student Information Management System" << endl;
						cout << "---------------------------------------------" << endl;
						cout << "Modified successfully!" << endl;
						break;
					}
					++iter;
				}
				if (iter == head.end()) {
					system("cls");
					cout << "Student Information Management System" << endl;
					cout << "---------------------------------------------" << endl;
					cout << "We do not find this account." << endl;
				}
			}
			if (i == '2') {
				system("cls");
				cout << "Student Information Management System" << endl;
				cout << "---------------------------------------------" << endl;
				cout << "Enter the account you want to change and the new password." << endl;
				cin >> username >> temp;
				auto iter = head.begin();
				while (iter != head.end()) {
					if (iter->account.username == username) {
						iter->account.password = temp;
						system("cls");
						cout << "Student Information Management System" << endl;
						cout << "---------------------------------------------" << endl;
						cout << "Modified successfully!" << endl;
						break;
					}
					++iter;
				}
				if (iter == head.end()) {
					system("cls");
					cout << "Student Information Management System" << endl;
					cout << "---------------------------------------------" << endl;
					cout << "We do not find this account." << endl;
				}

			}
			if (i == '0'){
				system("cls");
				cout << "Student Information Management System" << endl;
				cout << "---------------------------------------------" << endl;
			}
			cout << "Please enter any key to continue..." << endl;
			char ch;
			cin >> ch;
			continue;
		}
		if (ad == '5') {
			system("cls");
			cout << "Student Information Management System" << endl;
			cout << "---------------------------------------------" << endl;
			cout << "Enter the account you want to inquire." << endl;
			string username;
			cin >> username;
			auto iter = head.begin();
			while (iter != head.end()) {
				if (iter->account.username == username) {
					system("cls");
					cout << "Student Information Management System" << endl;
					cout << "---------------------------------------------" << endl;
					cout << "Obtained account successfully." << endl;
					cout << iter->account.username << ' ' << iter->account.password << endl;
					cout << iter->student.name << ' ' << iter->student.className << ' ' << iter->student.stdId << ' ' << iter->student.score << endl;
				}
				++iter;
			}
			cout << "Please enter any key to continue..." << endl;
			char ch;
			cin >> ch;
			continue;
		}
		if (ad == '6') {
			putMessage(head);
			system("cls");
			cout << "Student Information Management System" << endl;
			cout << "---------------------------------------------" << endl;
			cout << "Update grade database successfully." << endl;
			cout << "Please enter any key to continue..." << endl;

			char ch;
			cin >> ch;
			continue;
		}
		if (ad == '7') {
			system("cls");
			cout << "Student Information Management System" << endl;
			cout << "---------------------------------------------" << endl;
			auto iter = head.begin();
			while (iter != head.end()) {
				cout << iter->account.username << ' ' << iter->account.password << endl;
				++iter;
			}
			cout << "Please enter any key to continue..." << endl;
			char ch;
			cin >> ch;
			continue;
		}
		if (ad == '0') {
			return;
		}
	}
}
/* 管理员函数
 * 包含了查看代办,进入教师端进行修改,增删改查账户,读写所有账号和密码等需求
 */

