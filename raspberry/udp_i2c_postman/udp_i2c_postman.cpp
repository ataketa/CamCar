#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <bcm2835.h>

using namespace std;

#define PORT 8882
#define MAXDATASIZE 1

/*      udp variables      */
int sockfd;
sockaddr_in server,client;
int sin_size;
int num;
char buf[MAXDATASIZE];
/*      i2c variables     */
//char sendword = 'a';


int main()
{ 

	/*   initialize udp        */
	if((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) == -1){
		cerr<<"socket setup failed\n";
		exit(1);
	}
	else cout<<"socket setted\n";

	bzero(&server, sizeof(server));
	server.sin_family = PF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sockfd, (sockaddr *)&server, sizeof(sockaddr)) == -1){
		cerr<<"bind error\n";
		exit(1);
	}
	else cout<<"bind success\n";
	sin_size = sizeof(sockaddr_in);

	/*     initialize i2c      */
	if(!bcm2835_init()){
		cerr<<"bcm2835 i2c initialize failed \n";
		return -1;
	}
	else cout<<"bcm2835 i2c initialized! \n";

	bcm2835_i2c_setSlaveAddress(0x25);
	cout<<"bcm2835 i2c addr set\n";
	bcm2835_i2c_set_baudrate(40000);
	cout<<"bcm2835 i2c baud set\n";
	bcm2835_i2c_begin();
	cout<<"bcm2835 i2c begin\n";

	/*      start to transport    */
	cout<<"start to transport\n";	
	while(1){
		num = recvfrom(sockfd, buf, MAXDATASIZE, 0, (sockaddr*)&client,(socklen_t*)&sin_size);
		if(num == -1){
			cout<<"recv error\n";
			break;
		}
		if(num > 0){
		//buf[MAXDATASIZE] = '\0';
		cout<<buf<<endl;
		bcm2835_i2c_write( buf , 1);
		}
	}

	bcm2835_i2c_end();
	bcm2835_close();
	close(sockfd);
	cout<<"udp closed\n";



	return 0;
}