
#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
using namespace std;
#pragma comment(lib, "ws2_32.lib") /*����ws2_32.lib��̬���ӿ�*/

int main() {
	start: 
    char buff[50000]; //�յ�recv�������صĽ��
    string message;
    string info;
    string subject;
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 1);
    int err = WSAStartup(wVersionRequested, &wsaData);
    SOCKADDR_IN addrServer;
    HOSTENT *pHostent;
    SOCKET sockClient;
	cout << "����鿴�ʼ����Ƿ��ʼ���\n\t1.�鿴����\n\t2.�����ʼ�\n";
    int call;
    cin >> call;
    if (call == 2) {
    sockClient = socket(AF_INET, SOCK_STREAM, 0); //����socket����

     pHostent = gethostbyname("smtp.qq.com"); //�õ��й�����������Ϣ,���ӵ�qq���������

     SOCKADDR_IN addrServer; //����˵�ַ
     addrServer.sin_addr.S_un.S_addr = *((DWORD *)pHostent->h_addr_list[0]); //�õ�smtp�������������ֽ����ip��ַ
     addrServer.sin_family = AF_INET;
     addrServer.sin_port = htons(25); //���Ӷ˿�25
     //int connect (SOCKET s , const struct sockaddr FAR *name , int namelen ); //����ԭ��
     err = connect(sockClient, (SOCKADDR*)&addrServer, sizeof(SOCKADDR)); //���������������
     cout << "connect:" << err << endl;
     buff[recv(sockClient, buff, 1500, 0)] = '\0';
     cout << "connect:" << buff << endl;
     string ehlo = "ehlo 1548708011\r\n";
     send(sockClient, ehlo.c_str(), ehlo.length(), 0);
     buff[recv(sockClient, buff, 1500, 0)] = '\0';
     cout <<"ehlo:"  << buff << endl;
     static string path = "auth login\r\n";
     send(sockClient, path.c_str(), path.length(), 0);
     buff[recv(sockClient, buff, 1500, 0)] = '\0';
     cout << "auth login:" << buff << endl;
     static string uername = "MTU0ODcwODAxMUBxcS5jb20=\r\n";
     send(sockClient, uername.c_str(), uername.length(), 0);
     buff[recv(sockClient, buff, 1500, 0)] = '\0';
     cout << "usrname:" << buff << endl;
     static string psw = "cmtwZXFweXhlc2x5amVjYw==\r\n";
     send(sockClient, psw.c_str(), psw.length(), 0);
     buff[recv(sockClient, buff, 1500, 0)] = '\0';
     cout << "password:" << buff << endl;
     string mail;
     cout << "�����ռ������䣺";
     cin >> mail;
     message = "MAIL FROM:<1548708011@qq.com> \r\nRCPT TO:<";
     message.append(mail);
     message.append("> \r\n");
     cout << "message=" << message;
     send(sockClient, message.c_str(), message.length(), 0);
     buff[recv(sockClient, buff, 1500, 0)] = '\0';
     cout << "mail from��״̬��: " << buff << endl;
     buff[recv(sockClient, buff, 1500, 0)] = '\0';
     cout << "rcpt to��״̬��: " << buff << endl;
     message = "DATA\r\n";
     send(sockClient, message.c_str(), message.length(), 0);
     buff[recv(sockClient, buff, 1500, 0)] = '\0';
     cout<< "data����ص�״̬��: " << buff << endl;

     static string form= "from:<1548708011@qq.com>\r\nto:<"+mail+">\r\nsubject:";

        cout<<"���⣺";
        cin>>subject;
        form.append(subject);
        form.append("\r\n\r\n");
        cout<<"���ݣ�";
        cin>>info;
        form.append(info);
        form.append("\r\n.\r\n");
        send(sockClient, form.c_str(), form.length(), 0);
        message = "quit\r\n";
         send(sockClient, message.c_str(), message.length(), 0);
        buff[recv(sockClient, buff, 1500, 0)] = '\0';
         cout << "����״̬�룺" << buff << endl;

         cout << "���ͳɹ���"<<endl;
         system("pause");
         goto start;
    }
    if (call == 1) {
        sockClient = socket(AF_INET, SOCK_STREAM, 0);
        const char *host_id = "pop3.126.com";
        pHostent = gethostbyname("pop.qq.com");
        int port = 110;
        addrServer.sin_addr.S_un.S_addr = *((DWORD *) pHostent->h_addr_list[0]);
        addrServer.sin_family = AF_INET;
        addrServer.sin_port = htons(port);
        err = connect(sockClient, (SOCKADDR *) &addrServer, sizeof(SOCKADDR));
        buff[recv(sockClient, buff, 500, 0)] = '\0';

        message = "user 1548708011@qq.com\r\n";
        send(sockClient, message.c_str(), message.length(), 0);
        buff[recv(sockClient, buff, 500, 0)] = '\0';
        cout << "Client : send name \nServer:"
                  << buff << endl;

        message = "pass rkpeqpyxeslyjecc\r\n";
        send(sockClient, message.c_str(), message.length(), 0);
        buff[recv(sockClient, buff, 500, 0)] = '\0';
        cout << "Client : send pass \nServer:"
                  << buff << endl;

        message = "stat\r\n";
        send(sockClient, message.c_str(), message.length(), 0);
        buff[recv(sockClient, buff, 500, 0)] = '\0';
        Sleep(1);
        cout << "Client : send stat \nServer : "
                  << buff << endl;

        message = "list\r\n";
        send(sockClient, message.c_str(), message.length(), 0);
        buff[recv(sockClient, buff, 1500, 0)] = '\0';
        Sleep(1);
        cout << "Client : send list \nServer :"
                  << buff << endl;
        int n;
        cout << "������鿴��һ���ʼ����������"
                  << endl;
        cin >> n;
        message = "retr " + to_string(n) + "\r\n";

        send(sockClient, message.c_str(), message.length(), 0);
        Sleep(1);
        cout << "Client : send retr "<<n<<"\n";
        buff[recv(sockClient, buff, 50000, 0)] = '\0';
        cout << "Server ��" << buff << endl;

        message = "QUIT\r\n";
        send(sockClient,message.c_str(),strlen(buff),0);
        Sleep(1);
        buff[recv(sockClient, buff, 50000, 0)] = '\0';
        cout << "Quit Receive: " << buff << endl;

        closesocket(sockClient);
        WSACleanup();
        system("pause");
        goto start;

    }
}



