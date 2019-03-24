#include "ros/ros.h"
#include "std_msgs/String.h"

#include "XMLHttpRequest.h"

#include <sstream>
#include <stdio.h> /* printf, sprintf */
#include <stdlib.h> /* exit */
#include <unistd.h> /* read, write, close */
#include <string.h> /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h> /* struct hostent, gethostbyname */

#include <curl/curl.h>

// code taken from https://stackoverflow.com/questions/22077802/simple-c-example-of-doing-an-http-post-and-consuming-the-response/22135885#22135885 

int main(int argc, char *argv[])
{
	ros::init(argc, argv, "XHR_comm");
	ros::NodeHandle node_handle
	
	int portno = 80; // default port for the ESP32 with XHR requests is 80
    char *host = strlen(argv[1])>0?argv[1]:"localhost";

    /* below code taken from https://curl.haxx.se/libcurl/c/simple.html */
    // reference on using libcurl's "easy" interface: https://curl.haxx.se/libcurl/c/libcurl-easy.html
    CURL *curl;
    CURLcode res;

    // using libcurl's "easy" interface
    curl = curl_easy_init();
    if (curl)
    {
    	//curl_easy_setopt(curl, CURLOPT_URL, "https://example.com");
	    /* example.com is redirected, so we tell libcurl to follow redirection */ 
	    // might need to use CURLOPT_DNS_LOCAL instead
    	curl_easy_setopt(curl, CURLOPT_DNS_LOCAL_IP4, "192.168.0.128");


	    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	 
	    /* Perform the request, res will get the return code */ 
	    res = curl_easy_perform(curl);
	    /* Check for errors */ 
	    if(res != CURLE_OK) 
	    { 
	      fprintf(stderr, "curl_easy_perform() failed: %s\n",
	              curl_easy_strerror(res));
	    }
	 
	    /* always cleanup */ 
	    curl_easy_cleanup(curl);
    }
}