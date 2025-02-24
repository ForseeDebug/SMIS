// SMIS.cpp: 定义应用程序的入口点。
//

#include "Specific functions.h"

#define ADMINISTRATOR_CODE "!!$%!$"
using namespace std;

/* 使用getchar()来留存控制台信息不鲜遇到缓冲区问题.
 * 于是代码中使用cin >> 作为替代.
 */

int main()
{
	list<User> head = getMessage();
	cout << "Student Information Management System" << endl;
	cout << "---------------------------------------------" << endl;
	cout << "Data read successful!" << endl;
	cout << "Press any key to enter the system..." << endl;
	char ch;
	cin >> ch;
	// 在进入系统前将文件内的数据读取到链表中

	while (true) {
		system("cls");
		cout << "Student Information Management System" << endl;
		cout << "---------------------------------------------" << endl;
		cout << "1. Students" << endl;
		cout << "2. Teachers" << endl;
		cout << "3. Administrators" << endl;
		cout << "4. Register" << endl;
		cout << "0. Exit" << endl;
		cout << "---------------------------------------------" << endl;
		cout << "Enter the corresponding serial number to execute the function: " << endl;
		cout << ">> ";
		cin >> ch;
		if (ch == '1') {

			auto it = head.begin();
			const string code = "Teacher";
			if (Login(head,&it)) {
				User user = *it;
				if (it->student.stdId == code) {
					system("cls");
					cout << "Student Information Management System" << endl;
					cout << "---------------------------------------------" << endl;
					cout << "Detected that you are teacher." << endl;
					cout << "Entering the teacher end..." << endl;
					cout << "Press any key to continue." << endl;
					int cou;
					cin >> cou;
					Teacher(head, user);
				}
				else {
					
					Student(head, user);
				}
			} // 定义一个迭代器it传入登录函数,如果登录成功会将迭代器指向用户账户.

		}

		else if (ch == '2') {

			auto it = head.begin();
			const string code = "Teacher";
			if (Login(head,&it)) {
				User user = *it;
				if (it->student.stdId == code) {
					Teacher(head, user);
				}
				else {
					system("cls");
					cout << "Student Information Management System" << endl;
					cout << "---------------------------------------------" << endl;
					cout << "Detected that you are student." << endl;
					cout << "Entering the student end..." << endl;
					cout << "Press any key to continue." << endl;
					int cou;
					cin >> cou;
					Student(head, user);
				}
			}

		}

		else if (ch == '3') {

			while (true) {
				system("cls");
				cout << "Student Information Management System" << endl;
				cout << "---------------------------------------------" << endl;
				cout << "Please enter the administrator code" << endl;
				string code;
				cin >> code;
				if (code == ADMINISTRATOR_CODE) {
					Admin(head);
					break;
				}
				system("cls");
				cout << "Student Information Management System" << endl;
				cout << "---------------------------------------------" << endl;
				cout << "Enter failed.Press 1 key to continue..." << endl;
				cout << "Or press any other key to exit" << endl;
				cin >> ch;
				if (ch != '1') break;
			}

		}

		else if (ch == '4') {

			Register(head);

		}

		else if (ch == '0'){

			putMessage(head);
			// 用户按照正常路线行走到退出程序时会将修改后的链表数据覆盖写入文件中.
			break;

		}

		else if (ch == '5') {

			system("cls");
			cout << "maertsS noissimrep lanosretnI tnedutS" << endl;
			cout << "---------------------------------------------" << endl;
			cout << "This is an Easter egg." << endl;
			cout << "Press any key to continue." << endl;
			cin >> ch;

		} // 这是一枚彩蛋

		else {

			system("cls");
			cout << "Student Information Management System" << endl;
			cout << "---------------------------------------------" << endl;
			cout << "Invalid input." << endl;
			cout << "Press any key to continue..." << endl;
			cin >> ch;

		}

	}

	return 0;
}
