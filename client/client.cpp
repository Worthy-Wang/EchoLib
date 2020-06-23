#include <Unixfunc.h>
#include <iostream>
using namespace std;

int main()
{
    int ret;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(sockfd, -1, "socket");
    struct sockaddr_in sockinfo;
    bzero(&sockinfo, sizeof(sockinfo));
    sockinfo.sin_addr.s_addr = inet_addr("172.21.0.7");
    sockinfo.sin_port = htons(2000);
    sockinfo.sin_family = AF_INET;
    ret = connect(sockfd, (sockaddr *)&sockinfo, sizeof(sockinfo));
    ERROR_CHECK(ret, -1, "connect");

    char buf[100];
    recv(sockfd, buf, sizeof(buf), 0);
    cout << buf << endl;

    while (1)
    {
        bzero(buf, sizeof(buf));
        read(0, buf, sizeof(buf));
        send(sockfd, buf, strlen(buf), 0);

        bzero(buf, sizeof(buf));
        recv(sockfd, buf, sizeof(buf), 0);
        cout << buf << endl;
    }

    while (1)
        ;
    close(sockfd);
    return 0;
}