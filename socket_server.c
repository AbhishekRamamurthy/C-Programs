/*
	Basic server program, where it returns successful connection message and terminates
*/
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<errno.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
#define max_con 5

/*
	stucture to to socket port and length
*/

struct sock_port_len {
	
	int port,length;
}s_p_l;

/* 	
	nested structure to hold sockaddr_in and sock_port_len
	data type
*/ 
struct sock_spl_client {
	
	struct sockaddr_in client;
	struct sock_port_len spl;
}sock_spl_client; 

/* 
	Function to open socket and update the socket attributes
*/

struct sockaddr_in open_socket (struct sockaddr_in sock, 
								struct sock_port_len *sock_des) {
	
	int serv_sock;
	if((serv_sock=socket(AF_INET,SOCK_STREAM,0))==-1) {
		
		perror("\nserv_sock creation failed\n");
		exit(-1);
	}

	memset(&sock,0,sizeof(&sock));

	sock.sin_family=AF_INET;
	sock.sin_port=htons(1000);
	sock.sin_addr.s_addr=INADDR_ANY;//listen on all interfaces
	bzero(&sock.sin_zero,8);

	sock_des->port=serv_sock;
	sock_des->length=sizeof(struct sockaddr_in);
	return sock;
}

/*
	Function to bind the socket port
*/

void bind_socket (struct sock_port_len *sock_des, struct sockaddr_in *sock) {
	
	if((bind(sock_des->port,(struct sockaddr *) sock, sock_des->length)) ==-1) {
		
		perror("\nbinding socket with port failed\n");
		exit(-1);
	}
}

/*
	Function to send message upon successfull connnection
*/

/*
void send_message(int cli,struct sockaddr_in *client) {
	
	//char message[]="connection successful\n";
	char message[]="thread creation successful\n";
	send(cli,message,strlen(message),0);
	//printf("connection successful with = %d\n",inet_ntoa(client->sin_addr));
	
	printf("thread successfull created for = %d\n",inet_ntoa(client->sin_addr));
}
*/

void* send_message(void *cli_p_ad) {
	
	//char message[]="connection successful\n";
	struct sock_spl_client *cli;
	struct sock_port_len client_socket;
	struct sockaddr_in client;
	
	int cli_port;
	
	cli= (struct sock_spl_client *) cli_p_ad;
	
	client_socket=cli->spl;
	client=cli->client;
	cli_port= client_socket.port;
	
	char message[]="\nwelcome \n";
	send(cli_port,message,strlen(message),0);
	//printf("connection successful with = %d\n",inet_ntoa(client->sin_addr));
	
	printf("Connection established with = %d\n",inet_ntoa(client.sin_addr));
}

void send_busy_message(int cli,struct sockaddr_in *client) {
	
	char message[]="server busy\n";
	send(cli,message,strlen(message),0);
	printf("busy message sent for = %d\n",inet_ntoa(client->sin_addr));
}
/*
	function to accept connection 
*/

//int accept_connection(struct sockaddr_in *client, struct sock_port_len *sock) {
//	
//	int cli;
//	if((cli=accept(sock->port,(struct sockaddr *) client, &sock->length))== -1) {
//		
//		perror("\n Connection from client failed\n");
//		exit(-1);
//	}
//	send_message(cli,client);
//	//return cli;
//}

int accept_connection(void *carrier) {
	
	int con=1,count=1;
	int cli;
	void *cli_carrier;
	struct sock_spl_client *spl_c, cli_p_ad;
	struct sockaddr_in client;
	struct sock_port_len spl,client_port;
	int port,length;	
	pthread_t ta_con[max_con];	
	
	spl_c= (struct sock_spl_client *) carrier;

	client=spl_c->client;
	spl=spl_c->spl;
	
	for (;con<=max_con;) {
		if((cli=accept(spl.port,(struct sockaddr *) &client, &spl.length))== -1) {

			perror("\n Connection from client failed\n");
			exit(-1);
		}
	
		client_port.port=cli;
		client_port.length=sizeof(struct sockaddr_in);
		
		cli_p_ad.spl=client_port;
		cli_p_ad.client=client;	
		cli_carrier=(void *) &cli_p_ad;
		
		if(con > max_con) {

			send_busy_message(cli,&client);
			con++;
			close(cli);
		} else {
			
			pthread_create( &ta_con[con],NULL,send_message,cli_carrier);
			count++;
			con++;
		}
	}
	con=1;	
	for(con=1;con<=count;con++) {

		pthread_join(ta_con[con],NULL);
		printf("\nthread joined = %d",con);
	}
	return 1;	
}

void main () {
	
	int serv_sock,cli_sock;
	int length;
	int ret;
	struct sockaddr_in server,client;
	void *carrier;
	
	server=open_socket(server,&s_p_l);	
	bind_socket(&s_p_l,&server);
	
	sock_spl_client.client=client;
	sock_spl_client.spl=s_p_l;
	carrier=(void *)&sock_spl_client;

	//maximum connection  in queue 5
	if(listen (s_p_l.port,5) == -1) {
		perror("\n more than 5 clients trying to access\n");
		exit(-1);
	}
	
/*	
	while (1) {

	cli_sock=accept_connection(&client,&s_p_l);
	//close(cli_sock);
	}
*/
	
	while(1) {
	
		ret=accept_connection(carrier);
		
		if(ret == 1) {
			break;
		}
	}
	printf("\nServer is shutting down\n");
}
