#include "pch.h"
#include <iostream>
#include <speechapi_cxx.h>
#include <Windows.h>
#include <MMSystem.h>
#pragma comment(lib,"winmm.lib")
#include <fstream>
#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <string.h>
#define MAX 100
#define CAM_WIDTH 1280
#define CAM_HEIGHT 720
using namespace cv;
using namespace std;
typedef struct facelocation {
	int f1;
	int f2;
}fal;
typedef struct Face {
	char name[10];
	char inum[14];
	char id[10];
	fal fal1;
}face;
int i = 1;
int fc = 1;
face fa[MAX];
int a = 0;
int b = 0;
ofstream fout;
ifstream fin;
int sel = 0;
int sel2 = 0;
String face_cascade_name;
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
String window_name = "Face detection";
int result_selection(int x) {
	if (x == 1) return 1;
	else if (x == 2) return 3;
	else if (x == 3) return 5;
	else if (x == 4) return 10;
	else if (x == 5) return 30;
	else if (x == 6) return 50;
	else if (x == 7) return 70;
	else if (x == 8) return 100;
	else return 0;
}
struct newcard {
	char name[20];
	int idnum;
	char address[100];
	int cardtype;
	char out[15];
};
struct recard {
	char reason[100];
	char name[20];
	int idnum;
	char address[100];
	int cardtype;
	char out[15];
};
recard re[MAX];
newcard in[MAX];
using namespace Microsoft::CognitiveServices::Speech;
int recognizeSpeech()
{
	int respond = 0;
	auto config = SpeechConfig::FromSubscription("189374f5712149cb97947f8f98e3ed91", "koreacentral");
	auto recognizer = SpeechRecognizer::FromConfig(config);
	cout << "말씀하세요...\n";
	auto result = recognizer->RecognizeOnceAsync().get();
	if (result->Reason == ResultReason::RecognizedSpeech)
	{
		if (result->Text == "1.")
			return 1;
		else if (result->Text == "2.")
			return 2;
		else if (result->Text == "3.")
			return 3;
		else if (result->Text == "4.")
			return 4;
		else if (result->Text == "5.")
			return 5;
		else if (result->Text == "6.")
			return 6;
		else if (result->Text == "7.")
			return 7;
		else if (result->Text == "8.")
			return 8;
		else if (result->Text == "Exit.")
			return 9;
		else if (result->Text == "Yes.")
			return 10;
		else if (result->Text == "No.")
			return 11;
		else {
			cout << "잘못된 대답입니다.\n";
			respond=recognizeSpeech();
			return respond;
		}
	}
	else if (result->Reason == ResultReason::NoMatch)
	{
		cout << "NOMATCH: Speech could not be recognized." << std::endl;
	}
	else if (result->Reason == ResultReason::Canceled)
	{
		auto cancellation = CancellationDetails::FromResult(result);
		cout << "CANCELED: Reason=" << (int)cancellation->Reason << std::endl;

		if (cancellation->Reason == CancellationReason::Error)
		{
			cout << "CANCELED: ErrorCode= " << (int)cancellation->ErrorCode << std::endl;
			cout << "CANCELED: ErrorDetails=" << cancellation->ErrorDetails << std::endl;
			cout << "CANCELED: Did you update the subscription info?" << std::endl;
		}
	}
	return 0;
}
void select_card() {
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                                     카 드 선 택                        (Exit.이전메뉴로)             |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|           1. 우송 카드               |               2. IT 카드               |             3. 컴정 카드             |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
}
void new_error() {
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                         다시 카드 신규 발급 메뉴로 돌아갑니다.                                       |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
}
void re_error() {
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                         다시 카드 재 발급 메뉴로 돌아갑니다.                                         |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
}
void selection() {
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                                              |                                                       |" << endl;
	cout << "|                     1. 1만원                                 |                    5. 30만원                          |" << endl;
	cout << "|                                                              |                                                       |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                                              |                                                       |" << endl;
	cout << "|                     2. 3만원                                 |                    6. 50만원                          |" << endl;
	cout << "|                                                              |                                                       |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                                              |                                                       |" << endl;
	cout << "|                     3. 5만원                                 |                    7. 70만원                          |" << endl;
	cout << "|                                                              |                                                       |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                                              |                                                       |" << endl;
	cout << "|                     4. 10만원                                |                    8. 100만원                         |" << endl;
	cout << "|                                                              |                                                       |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
}
void complete() {
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                       카드발급 신청이 정상적으로 되었습니다.                                         |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                       발급 심사후 고객님의 주소로 보내드리겠습니다.                                  |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
}
void ending() {
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                               이용해주셔서 감사합니다.                                               |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
}
void tc_out() {
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                              통장 또는 카드를 받으세요.                                              |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
}
void t_in() {
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                               통장을 넣어주세요.                                                     |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
}
void c_in() {
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                               카드를 넣어주세요.                                                     |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
}
void m_in() {
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                               돈을 넣어주세요.                                                       |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
}
void m_out() {
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                               돈을 받으세요.                                                         |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
}
void deposit_int() {
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                                        입   금                                                       |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|           1. 통장 입금               |               2. 카드 입금             |             3. 무통장 입금           |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
}
void ncard() {
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                                        신   규                                                       |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|           1. 우송 카드               |                 2. IT 카드             |             3. 컴정 카드             |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
}
void rcard() {
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                                        재 발 급                                                      |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|           1. 우송 카드               |                 2. IT 카드             |             3. 컴정 카드             |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "|                                      |                                        |                                      |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
}
void withdraw_int()
{
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                                        출   금                                                       |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                                            |                                                         |" << endl;
	cout << "|                                                            |                                                         |" << endl;
	cout << "|                                                            |                                                         |" << endl;
	cout << "|                                                            |                                                         |" << endl;
	cout << "|                                                            |                                                         |" << endl;
	cout << "|                   1. 통장 출금                             |                     2. 카드 출금                        |" << endl;
	cout << "|                                                            |                                                         |" << endl;
	cout << "|                                                            |                                                         |" << endl;
	cout << "|                                                            |                                                         |" << endl;
	cout << "|                                                            |                                                         |" << endl;
	cout << "|                                                            |                                                         |" << endl;
	cout << "|                                                            |                                                         |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
}
void interface1() {
		cout << "		 ●             ●  ●●●●●		 ●●●●●   ●●●●●● ●        ● ●    ●           " << endl;
		cout << "		  ●    ●     ●   ●      		 ●       ●  ●        ● ● ●     ● ●  ●               " << endl;
		cout << "		   ●  ●●   ●    ●●●●●		 ●●●●●   ●●●●●● ●  ●    ● ●●                 " << endl;
		cout << "		    ●●  ● ●             ●		 ●        ● ●        ● ●    ●  ● ●  ●           " << endl;
		cout << "		     ●     ●      ●●●●●		 ●●●●●● ●        ● ●      ●● ●    ●          " << endl;
		cout << "\n";
		cout << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "|                                                       ATM 업무                                                       |" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "|                                                           |                                                          |" << endl;
		cout << "|                  1. 입 금                                 |                     2.  출 금                            |" << endl;
		cout << "|                                                           |                                                          |" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "|                                                        창구 업무                                                     |" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "|                                                           |                                                          |" << endl;
		cout << "|                    3. 카드 신규 발급                      |                     4.  카드 재 발급                     |" << endl;
		cout << "|                                                           |                                                          |" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
}
void newcard_in() {
	int res = 0;
	char agree = '\0';
	select_card();
	PlaySound(TEXT("4.wav"), NULL, SND_SYNC);
	in[i].cardtype=recognizeSpeech();
	if (in[i].cardtype == 9) return;
	system("cls");
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                                        신   규                                                       |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	switch (in[i].cardtype) {
	case 1:
	{
		cout << "제1조(목적)" << endl;
		cout << "이 약관은 회원의 권익보호 및 거래관계의 명확화를 위하여 신용카드사(이하 “카드사”라 함)와" << endl;
		cout << "신용카드(이하 “카드”라 함)를 이용하고자 하는 회원 간의 필요한 사항을 정함을 목적으로 합니다." << endl;
		cout << "이에 동의하십니까?(Yes or NO)" << endl;
		PlaySound(TEXT("4-1.wav"), NULL, SND_SYNC);
		res = recognizeSpeech();
		if (res == 10) {
			PlaySound(TEXT("4-2.wav"), NULL, SND_SYNC);
			agree = 'Y';
			cout << "이름을 입력하세요.\n";
			cin >> in[i].name;
			cout << "주민번호를 입력하세요\n";
			cin >> in[i].idnum;
			cout << "주소를 입력하세요\n";
			cin >> in[i].address;
			cout << "출금계좌를 입력하세요\n";
			cin >> in[i].out;
			system("cls");
			complete();
			PlaySound(TEXT("4-3.wav"), NULL, SND_SYNC);
			Sleep(2000);
			break;
		}
		else {
			system("cls");
			new_error();
			PlaySound(TEXT("4-4.wav"), NULL, SND_SYNC);
			Sleep(2000);
			system("cls");
			newcard_in();
		}
	}
	case 2:
	{
		cout << "제1조(목적)" << endl;
		cout << "이 약관은 회원의 권익보호 및 거래관계의 명확화를 위하여 신용카드사(이하 “카드사”라 함)와" << endl;
		cout << "신용카드(이하 “카드”라 함)를 이용하고자 하는 회원 간의 필요한 사항을 정함을 목적으로 합니다." << endl;
		cout << "이에 동의하십니까?(Yes or NO)" << endl;
		PlaySound(TEXT("4-1.wav"), NULL, SND_SYNC);
		res = recognizeSpeech();
		if (res == 10) {
			PlaySound(TEXT("4-2.wav"), NULL, SND_SYNC);
			agree = 'Y';
			cout << "이름을 입력하세요.\n";
			cin >> in[i].name;
			cout << "주민번호를 입력하세요\n";
			cin >> in[i].idnum;
			cout << "주소를 입력하세요\n";
			cin >> in[i].address;
			cout << "출금계좌를 입력하세요\n";
			cin >> in[i].out;
			system("cls");
			complete();
			PlaySound(TEXT("4-3.wav"), NULL, SND_SYNC);
			Sleep(2000);
			break;
		}
		else {
			system("cls");
			new_error();
			PlaySound(TEXT("4-4.wav"), NULL, SND_SYNC);
			Sleep(2000);
			system("cls");
			newcard_in();
		}
	}
	case 3:
	{
		cout << "제1조(목적)" << endl;
		cout << "이 약관은 회원의 권익보호 및 거래관계의 명확화를 위하여 신용카드사(이하 “카드사”라 함)와" << endl;
		cout << "신용카드(이하 “카드”라 함)를 이용하고자 하는 회원 간의 필요한 사항을 정함을 목적으로 합니다." << endl;
		cout << "이에 동의하십니까?(Yes or NO)" << endl;
		PlaySound(TEXT("4-1.wav"), NULL, SND_SYNC);
		res = recognizeSpeech();
		if (res == 10) {
			PlaySound(TEXT("4-2.wav"), NULL, SND_SYNC);
			agree = 'Y';
			cout << "이름을 입력하세요.\n";
			cin >> in[i].name;
			cout << "주민번호를 입력하세요\n";
			cin >> in[i].idnum;
			cout << "주소를 입력하세요\n";
			cin >> in[i].address;
			cout << "출금계좌를 입력하세요\n";
			cin >> in[i].out;
			system("cls");
			complete();
			PlaySound(TEXT("4-3.wav"), NULL, SND_SYNC);
			Sleep(2000);
			break;
		}
		else {
			system("cls");
			new_error();
			PlaySound(TEXT("4-4.wav"), NULL, SND_SYNC);
			Sleep(2000);
			system("cls");
			newcard_in();
		}
	}
	}

	ofstream fout;
	fout.open("newcard.dat");
	fout << in[i].name << " " << in[i].idnum << " " << in[i].address << " " << in[i].cardtype << " " << agree << " " << in[i].out << endl;
	fout.close();
}
void re_card() {
	char agree='\0';
	int res = 0;
	select_card();
	PlaySound(TEXT("4.wav"), NULL, SND_SYNC);
	re[i].cardtype = recognizeSpeech();
	if (re[i].cardtype == 9) return;
	system("cls");
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                                        재 발 급                                                      |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	switch (re[i].cardtype) {
	case 1:
	{
		cout << "제1조(목적)" << endl;
		cout << "이 약관은 회원의 권익보호 및 거래관계의 명확화를 위하여 신용카드사(이하 “카드사”라 함)와" << endl;
		cout << "신용카드(이하 “카드”라 함)를 이용하고자 하는 회원 간의 필요한 사항을 정함을 목적으로 합니다." << endl;
		cout << "이에 동의하십니까?(Yes or NO)" << endl;
		PlaySound(TEXT("4-1.wav"), NULL, SND_SYNC);
		res = recognizeSpeech();
		if (res == 10) {
			PlaySound(TEXT("4-2.wav"), NULL, SND_SYNC);
			agree = 'Y';
			cout << "이름을 입력하세요.\n";
			cin >> re[i].name;
			cout << "재발급 사유를 입력하세요.\n";
			cin >> re[i].reason;
			cout << "주민번호를 입력하세요\n";
			cin >> re[i].idnum;
			cout << "주소를 입력하세요\n";
			cin >> re[i].address;
			cout << "출금계좌를 입력하세요\n";
			cin >> re[i].out;
			system("cls");
			complete();
			PlaySound(TEXT("4-3.wav"), NULL, SND_SYNC);
			Sleep(2000);
			break;
		}
		else {
			system("cls");
			re_error();
			PlaySound(TEXT("4-5.wav"), NULL, SND_SYNC);
			Sleep(2000);
			system("cls");
			re_card();
		}
	}
	case 2:
	{
		cout << "제1조(목적)" << endl;
		cout << "이 약관은 회원의 권익보호 및 거래관계의 명확화를 위하여 신용카드사(이하 “카드사”라 함)와" << endl;
		cout << "신용카드(이하 “카드”라 함)를 이용하고자 하는 회원 간의 필요한 사항을 정함을 목적으로 합니다." << endl;
		cout << "이에 동의하십니까?(Yes or NO)" << endl;
		PlaySound(TEXT("4-1.wav"), NULL, SND_SYNC);
		res = recognizeSpeech();
		if (res == 10) {
			PlaySound(TEXT("4-2.wav"), NULL, SND_SYNC);
			agree = 'Y';
			cout << "이름을 입력하세요.\n";
			cin >> re[i].name;
			cout << "재발급 사유를 입력하세요.\n";
			cin >> re[i].reason;
			cout << "주민번호를 입력하세요\n";
			cin >> re[i].idnum;
			cout << "주소를 입력하세요\n";
			cin >> re[i].address;
			cout << "출금계좌를 입력하세요\n";
			cin >> re[i].out;
			system("cls");
			complete();
			PlaySound(TEXT("4-3.wav"), NULL, SND_SYNC);
			Sleep(2000);
			break;
		}
		else {
			system("cls");
			re_error();
			PlaySound(TEXT("4-5.wav"), NULL, SND_SYNC);
			Sleep(2000);
			system("cls");
			re_card();
		}
	}
	case 3:
	{
		cout << "제1조(목적)" << endl;
		cout << "이 약관은 회원의 권익보호 및 거래관계의 명확화를 위하여 신용카드사(이하 “카드사”라 함)와" << endl;
		cout << "신용카드(이하 “카드”라 함)를 이용하고자 하는 회원 간의 필요한 사항을 정함을 목적으로 합니다." << endl;
		cout << "이에 동의하십니까?(Yes or NO)" << endl;
		PlaySound(TEXT("4-1.wav"), NULL, SND_SYNC);
		res = recognizeSpeech();
		if (res == 10) {
			PlaySound(TEXT("4-2.wav"), NULL, SND_SYNC);
			agree = 'Y';
			cout << "이름을 입력하세요.\n";
			cin >> re[i].name;
			cout << "재발급 사유를 입력하세요.\n";
			cin >> re[i].reason;
			cout << "주민번호를 입력하세요\n";
			cin >> re[i].idnum;
			cout << "주소를 입력하세요\n";
			cin >> re[i].address;
			cout << "출금계좌를 입력하세요\n";
			cin >> re[i].out;
			system("cls");
			complete();
			PlaySound(TEXT("4-3.wav"), NULL, SND_SYNC);
			Sleep(2000);
			break;
		}
		else {
			system("cls");
			re_error();
			PlaySound(TEXT("4-5.wav"), NULL, SND_SYNC);
			Sleep(2000);
			system("cls");
			re_card();
		}
	}
	}
	ofstream fout;
	fout.open("recard.dat");
	fout << re[i].name << " " << re[i].reason << " " << re[i].idnum << " " << re[i].address << " " << re[i].cardtype << " " << agree << " " << re[i].out << endl;
	fout.close();
}
int deposit() {
	int r1=0, r2=0, r3=0;
	int tn[20] = {};
	int password2=0;
	deposit_int();
	PlaySound(TEXT("2-1.wav"), NULL, SND_SYNC);
	r1 = recognizeSpeech();
	Sleep(2000);
	system("cls");
	switch (r1) {
	case 1:
	{
		t_in();
		PlaySound(TEXT("2-2.wav"), NULL, SND_SYNC);
		Sleep(2000);
		system("cls");
		selection();
		PlaySound(TEXT("2-4.wav"), NULL, SND_SYNC);
		r2 = recognizeSpeech();
		sel = result_selection(r2);
		Sleep(2000);
		system("cls");
		m_in();
		PlaySound(TEXT("2-5.wav"), NULL, SND_SYNC);
		Sleep(2000);
		system("cls");
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "|                                                        입   금                                                       |" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                   입금하실 금액 : " << sel << "만원이 맞습니까?                                      " << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		PlaySound(TEXT("2-6.wav"), NULL, SND_SYNC);
		r3 = recognizeSpeech();
		if (r3 == 10) {
			system("cls");
			tc_out();
			PlaySound(TEXT("7.wav"), NULL, SND_SYNC);
			Sleep(2000);
			system("cls");
			ending();
			PlaySound(TEXT("2-7.wav"), NULL, SND_SYNC);
			Sleep(2000);
			return 0;
		}
		else system("cls");
		cout << "다시 입금 메뉴로 돌아갑니다.\n";
		PlaySound(TEXT("2-8.wav"), NULL, SND_SYNC);
		system("cls");
		deposit();
	}
	case 2: {
		c_in();
		PlaySound(TEXT("2-9.wav"), NULL, SND_SYNC);
		Sleep(2000);
		system("cls");
		selection();
		PlaySound(TEXT("2-4.wav"), NULL, SND_SYNC);
		r2 = recognizeSpeech();
		sel = result_selection(r2);
		Sleep(2000);
		system("cls");
		m_in();
		PlaySound(TEXT("2-5.wav"), NULL, SND_SYNC);
		Sleep(2000);
		system("cls");
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "|                                                        입   금                                                       |" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                   입금하실 금액 : " << sel  << "만원이 맞습니까?                                     " << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		PlaySound(TEXT("2-6.wav"), NULL, SND_SYNC);
		r3 = recognizeSpeech();
		if (r3 == 10) {
			system("cls");
			tc_out();
			PlaySound(TEXT("7.wav"), NULL, SND_SYNC);
			Sleep(2000);
			system("cls");
			ending();
			PlaySound(TEXT("2-7.wav"), NULL, SND_SYNC);
			Sleep(2000);
			return 0;
		}
		else system("cls");
		cout << "다시 입금 메뉴로 돌아갑니다.\n";
		PlaySound(TEXT("2-8.wav"), NULL, SND_SYNC);
		system("cls");
		deposit();
	}
	case 3:
	{
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "|                                                  무 통 장   입   금                                                  |" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                  계좌번호를 입력해 주세요.                                           | " << endl;
		PlaySound(TEXT("2-10.wav"), NULL, SND_SYNC);
		cout << "                                                       ";cin >> tn[20];                                      cout << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		Sleep(2000);
		system("cls");
		selection();
		PlaySound(TEXT("2-4.wav"), NULL, SND_SYNC);
		r2 = recognizeSpeech();
		sel = result_selection(r2);
		Sleep(2000);
		system("cls");
		m_in();
		PlaySound(TEXT("2-5.wav"), NULL, SND_SYNC);
		Sleep(2000);
		system("cls");
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "|                                                        입   금                                                       |" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                 보내실 계좌번호 : "<<tn[20]<<"                                                       " << endl;
		cout << "|                                   입금하실 금액 : " << sel  << "만원이 맞습니까?                                     " << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		PlaySound(TEXT("2-6.wav"), NULL, SND_SYNC);
		r3 = recognizeSpeech();
		if (r3 == 10) {
			system("cls");
			ending();
			PlaySound(TEXT("2-7.wav"), NULL, SND_SYNC);
			Sleep(2000);
			return 0;
		}
		else system("cls");
		cout << "다시 입금 메뉴로 돌아갑니다.\n";
		PlaySound(TEXT("2-8.wav"), NULL, SND_SYNC);
		system("cls");
		deposit();
	}
	}
	return 0;
}
int withdraw() {
	int r4=0, r5=0, r6=0;
	int password1=0;
	withdraw_int();
	PlaySound(TEXT("3.wav"), NULL, SND_SYNC);
	r4 = recognizeSpeech();
	Sleep(2000);
	system("cls");
	switch (r4) {
	case 1:
	{
		t_in();
		PlaySound(TEXT("3-1.wav"), NULL, SND_SYNC);
		Sleep(2000);
		system("cls");
		selection();
		PlaySound(TEXT("3-3.wav"), NULL, SND_SYNC);
		r5 = recognizeSpeech();
		sel2 = result_selection(r5);
		Sleep(2000);
		system("cls");
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "|                                                        출   금                                                       |" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                   출금하실 금액 : " << sel2 << "만원이 맞습니까?                                    " << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		PlaySound(TEXT("3-4.wav"), NULL, SND_SYNC);
		r6 = recognizeSpeech();
		if (r6 == 10) {
			system("cls");
			m_out();
			PlaySound(TEXT("3-5.wav"), NULL, SND_SYNC);
			Sleep(2000);
			system("cls");
			tc_out();
			PlaySound(TEXT("7.wav"), NULL, SND_SYNC);
			Sleep(2000);
			system("cls");
			ending();
			PlaySound(TEXT("3-6.wav"), NULL, SND_SYNC);
			Sleep(2000);
			return 0;
		}
		else system("cls");
		cout << "다시 출금 메뉴로 돌아갑니다.\n";
		PlaySound(TEXT("3-7.wav"), NULL, SND_SYNC);
		system("cls");
		withdraw();
	}
	case 2:
	{
		c_in();
		PlaySound(TEXT("3-8.wav"), NULL, SND_SYNC);
		Sleep(2000);
		system("cls");
		selection();
		PlaySound(TEXT("3-3.wav"), NULL, SND_SYNC);
		r5 = recognizeSpeech();
		sel2 = result_selection(r5);
		Sleep(2000);
		system("cls");
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "|                                                        출   금                                                       |" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                   출금하실 금액 : " << sel2  << "만원이 맞습니까?                                   " << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		PlaySound(TEXT("3-4.wav"), NULL, SND_SYNC);
		r6 = recognizeSpeech();
		if (r6 == 10) {
			system("cls");
			m_out();
			PlaySound(TEXT("3-5.wav"), NULL, SND_SYNC);
			Sleep(2000);
			system("cls");
			tc_out();
			PlaySound(TEXT("7.wav"), NULL, SND_SYNC);
			Sleep(2000);
			system("cls");
			ending();
			PlaySound(TEXT("3-6.wav"), NULL, SND_SYNC);
			Sleep(2000);
			return 0;
		}
		else system("cls");
		cout << "다시 출금 메뉴로 돌아갑니다.\n";
		PlaySound(TEXT("3-7.wav"), NULL, SND_SYNC);
		system("cls");
		withdraw();
	}

	return 0;
	}
}
void f1() {
	cout << "		 ●             ●  ●●●●●		 ●●●●●   ●●●●●● ●        ● ●    ●           " << endl;
	cout << "		  ●    ●     ●   ●      		 ●       ●  ●        ● ● ●     ● ●  ●               " << endl;
	cout << "		   ●  ●●   ●    ●●●●●		 ●●●●●   ●●●●●● ●  ●    ● ●●                 " << endl;
	cout << "		    ●●  ● ●             ●		 ●        ● ●        ● ●    ●  ● ●  ●           " << endl;
	cout << "		     ●     ●      ●●●●●		 ●●●●●● ●        ● ●      ●● ●    ●          " << endl;
	cout << "\n";
	cout << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                                           |                                                          |" << endl;
	cout << "|                                                           |                                                          |" << endl;
	cout << "|                                                           |                                                          |" << endl;
	cout << "|                                                           |                                                          |" << endl;
	cout << "|                 1 . 얼 굴 등 록                           |                 2 . 얼 굴 인 식                          |" << endl;
	cout << "|                                                           |                                                          |" << endl;
	cout << "|                                                           |                                                          |" << endl;
	cout << "|                                                           |                                                          |" << endl;
	cout << "|                                                           |                                                          |" << endl;
	cout << "|                                                           |                                                          |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
}
void f4() {
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                                     얼 굴 등 록                                                      |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                등록이 완료되었습니다.                                                |" << endl;
	cout << "|                                                메인메뉴로 돌아갑니다.                                                |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
}
int camera() {
	int fcnt = 0;
	face_cascade_name = "C:\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml";
	String eyes_cascade_name = "C:\\opencv\\sources\\data\\haarcascades\\haarcascade_eye_tree_eyeglasses.xml";
	if (!face_cascade.load(face_cascade_name)) { printf("--(!)Error loading face cascade\n"); return -1; };
	if (!eyes_cascade.load(eyes_cascade_name)) { printf("--(!)Error loading\n"); return -1; };
	VideoCapture cam(0);
	Mat frame;
	cam.set(CAP_PROP_FRAME_WIDTH, CAM_WIDTH);
	cam.set(CAP_PROP_FRAME_HEIGHT, CAM_HEIGHT);
	if (!cam.isOpened()) { printf("--(!)Error opening video cam\n"); return -1; }

	while (cam.read(frame))
	{
		if (frame.empty())
		{
			printf(" --(!) No camd frame -- Break!");
			break;
		}

		std::vector<Rect> faces = faces;
		Mat frame_gray;
		cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
		equalizeHist(frame_gray, frame_gray);
		face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
		for (size_t i = 0; i < faces.size(); i++)
		{
			Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
			ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(0, 0, 255), 4, 8, 0);
			a = faces[i].x + faces[i].width / 2;
			b = faces[i].y + faces[i].height / 2;
			Mat faceROI = frame_gray(faces[i]);
			std::vector<Rect> eyes;

			//-- In each face, detect eyes
			eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

			for (size_t j = 0; j < eyes.size(); j++)
			{
				Point eye_center(faces[i].x + eyes[j].x + eyes[j].width / 2, faces[i].y + eyes[j].y + eyes[j].height / 2);
				int radius = cvRound((eyes[j].width + eyes[j].height) * 0.25);
				circle(frame, eye_center, radius, Scalar(255, 0, 0), 4, 8, 0);
			}
		}

		imshow(window_name, frame);
		char c = (char)waitKey(10);
		if (c == 27) {
			break;
		}

	}
	return 0;
}
int face_regi()
{
	fout.open("info.dat");
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                                     얼 굴 등 록                                                      |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "| 기본 정보 입력                                                                                                       |" << endl;
	PlaySound(TEXT("8-1.wav"), NULL, SND_SYNC);
	cout << "|                                                                                                                      |" << endl;
	cout << "| 이름 : "; cin >> fa[i].name; cout << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "| 주민번호 : "; cin >> fa[i].inum; cout << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "| 아이디 : "; cin >> fa[i].id; cout << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	Sleep(3000);
	system("cls");
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                                     얼 굴 등 록                                                      |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                             충분히 얼굴을 인식시킨 후                                                |" << endl;
	cout << "|                                             ESC를 눌러 등록을 완료합니다.                                            |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	PlaySound(TEXT("8-2.wav"), NULL, SND_SYNC);
	Sleep(3000);
	system("cls");
	camera();
	fout << fa[i].name << "," << fa[i].inum << "," << fa[i].id << "," << a << "," << b << endl;
	fa[i].fal1.f1 = a; fa[i].fal1.f2 = b;
	fout.close();
	system("cls");
	f4();
	PlaySound(TEXT("8-3.wav"), NULL, SND_SYNC);
	Sleep(3000);
	system("cls");
	return 0;
}
int face_recog()
{
	int fcnt=1;
	char reid[10];
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                                     얼 굴 인 식                                                      |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	PlaySound(TEXT("8-4.wav"), NULL, SND_SYNC);
	cout << "|                                       아이디를 입력해 주세요 : "; cin >> reid;
	cout << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	Sleep(3000);
	system("cls");
	for (fcnt = 1; fcnt < MAX; fcnt++)
	{
		if (strcmp(reid,fa[fcnt].id)==0) {
			fcnt = fcnt;
			break;
		}
	}
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                                     얼 굴 인 식                                                      |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                 얼굴을 인식시켜 주세요.                                              |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "|                                                                                                                      |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	PlaySound(TEXT("8-5.wav"), NULL, SND_SYNC);
	Sleep(3000);
	system("cls");
	camera();
	if ((fa[fcnt].fal1.f1 - 30 <= a <= fa[fcnt].fal1.f1 + 30) && (fa[fcnt].fal1.f2 - 30 <= b <= fa[fcnt].fal1.f2 + 30))
	{
		system("cls");
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "|                                                     얼 굴 인 식                                                      |" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                               "; cout << fa[fcnt].name << " 고객님 반갑습니다.      " << endl;
		PlaySound(TEXT("8-6.wav"), NULL, SND_SYNC);
		cout << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "|                                                                                                                      |" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		Sleep(5000);
		system("cls");
		return 6;
	}
	else {
		cout << "다시 인식시켜 주세요.";
		Sleep(5000);
		system("cls");
		camera();
	}
	system("cls");
	return 0;
}
int wmain()
{
	int re;
	while (1) {
		f1();
		PlaySound(TEXT("1-1.wav"), NULL, SND_SYNC);
		PlaySound(TEXT("1-2.wav"), NULL, SND_SYNC);
		re = recognizeSpeech();
		system("cls");
		switch (re) {
		case 1: {
			face_regi();
			goto here;
		}
		case 2: face_recog();
			break;
		case 9: goto exit;
		default: 
			system("cls");
			cout << "잘못된 명령입니다. 메인메뉴로 돌아갑니다." << endl;
			Sleep(3000);
			system("cls");
			goto here;
		}
		
		system("cls");
		interface1();
		PlaySound(TEXT("1-2.wav"), NULL, SND_SYNC);
		re = recognizeSpeech();
		cout << "처리 중 입니다.\n";
		Sleep(2000);
		system("cls");
		switch (re)
		{
		case 1: {
			deposit();
			break;
		}
		case 2: {
			withdraw();
			break;
		}
		case 3: {
			newcard_in();
			break;
		}
		case 4: {
			re_card();
			break;
		}
		case 9 : goto exit;
		}
		system("cls");
	here:;
		i++;
	}
exit: return 1;
	return 0;
}