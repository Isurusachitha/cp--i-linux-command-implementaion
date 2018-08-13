#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFFERSIZE 4096
#define COPYMODE   0644

void oops(char*, char*);

int main(int ac , char *av[])
{
	int in_fd, out_fd, n_chars;
	char buf[BUFFERSIZE];     
				
	//check args

	if(ac != 3){
		fprintf(stderr, "usage: %s source destination\n", *av);
		exit(1);
	}                    
	//open files

	if ((in_fd = open(av[1], O_RDONLY)) == -1)
		oops("Cannot open", av[1]);

       //Overwriting authendication

       if ((open(av[2], O_RDONLY)) == -1){

	if((out_fd = creat(av[2], COPYMODE)) == -1)
		oops("Cannot creat", av[2]);

      }else{
        
         char chr;
         printf("%s is already exist. \n",av[2]);
         printf("Do you want to replace it (y/n)? ");
         scanf("%c",&chr);

         if('y'==chr){

          	if((out_fd = creat(av[2], COPYMODE)) == -1)
		   oops("Cannot creat", av[2]);

               printf(" File overwriting ... \n");

         }else if('n'==chr){
               
                printf(" Operation abort ! \n");
                exit(1);
         }else{
           
             printf(" invalid input \n");
             exit(1);
         
         }


      }

	
	//copy files

	while ((n_chars = read(in_fd, buf, BUFFERSIZE)) > 0)
		if(write(out_fd, buf, n_chars) != n_chars)
			oops("Write error to ", av[2]);
	
	if(n_chars == -1)
		oops("Read error from ", av[1]);
	
	// close files
			
	if(close(in_fd) == -1 || close(out_fd) == -1)
		oops("Error closing files" , "");
}

void oops(char *s1, char *s2)
{
	fprintf(stderr,"Error : %s", s1);
	perror(s2);
	exit(1);
}
