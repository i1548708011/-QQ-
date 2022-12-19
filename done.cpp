
#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
using namespace std;
#pragma comment(lib, "ws2_32.lib") /*链接ws2_32.lib动态链接库*/

int main() {
	start: 
    char buff[50000]; //收到recv函数返回的结果
    string message;
    string info;
    string subject;
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 1);
    int err = WSAStartup(wVersionRequested, &wsaData);
    SOCKADDR_IN addrServer;
    HOSTENT *pHostent;
    SOCKET sockClient;
	cout << "你想查看邮件还是发邮件？\n\t1.查看邮箱\n\t2.发送邮件\n";
    int call;
    cin >> call;
    if (call == 2) {
    sockClient = socket(AF_INET, SOCK_STREAM, 0); //建立socket对象

     pHostent = gethostbyname("smtp.qq.com"); //得到有关于域名的信息,链接到qq邮箱服务器

     SOCKADDR_IN addrServer; //服务端地址
     addrServer.sin_addr.S_un.S_addr = *((DWORD *)pHostent->h_addr_list[0]); //得到smtp服务器的网络字节序的ip地址
     addrServer.sin_family = AF_INET;
     addrServer.sin_port = htons(25); //连接端口25
     //int connect (SOCKET s , const struct sockaddr FAR *name , int namelen ); //函数原型
     err = connect(sockClient, (SOCKADDR*)&addrServer, sizeof(SOCKADDR)); //向服务器发送请求
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
     cout << "输入收件人邮箱：";
     cin >> mail;
     message = "MAIL FROM:<1548708011@qq.com> \r\nRCPT TO:<";
     message.append(mail);
     message.append("> \r\n");
     cout << "message=" << message;
     send(sockClient, message.c_str(), message.length(), 0);
     buff[recv(sockClient, buff, 1500, 0)] = '\0';
     cout << "mail from的状态码: " << buff << endl;
     buff[recv(sockClient, buff, 1500, 0)] = '\0';
     cout << "rcpt to的状态码: " << buff << endl;
     message = "DATA\r\n";
     send(sockClient, message.c_str(), message.length(), 0);
     buff[recv(sockClient, buff, 1500, 0)] = '\0';
     cout<< "data命令返回的状态码: " << buff << endl;

     static string form= "from:<1548708011@qq.com>\r\nto:<"+mail+">\r\nsubject:";

        cout<<"主题：";
        cin>>subject;
        form.append(subject);
        form.append("\r\n\r\n");
        cout<<"内容：";
        cin>>info;
        form.append(info);
        form.append("\r\n.\r\n");
        send(sockClient, form.c_str(), form.length(), 0);
        message = "quit\r\n";
         send(sockClient, message.c_str(), message.length(), 0);
        buff[recv(sockClient, buff, 1500, 0)] = '\0';
         cout << "返回状态码：" << buff << endl;

         cout << "发送成功！"<<endl;
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
        cout << "你先想查看那一封邮件？输入序号"
                  << endl;
        cin >> n;
        message = "retr " + to_string(n) + "\r\n";

        send(sockClient, message.c_str(), message.length(), 0);
        Sleep(1);
        cout << "Client : send retr "<<n<<"\n";
        buff[recv(sockClient, buff, 50000, 0)] = '\0';
        cout << "Server ：" << buff << endl;

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



