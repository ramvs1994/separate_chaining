# separate_chaining
1.src folder contains server , one tcp client , one udp client , main program where hashing based on five tuples (i.e source IP, destination IP, source Port, destination Port and protocol) is implemented .
main program itself acts as packet sniffing code i.e it captures the packets flowing in and out of the system. I am extracting the five tuples from the captured packet and using hash_func to generate key based on the five tuples. I am using this key to generate index into the hash table . to avoid collisions i have implemented separate chaining in hash table.
EXECUTION SEQUENCE :
open the makefile and edit the LDFLAGS= ,with -L<path for the header file header.h which is in includes directory>, for example say LDFLAGS= -L/home/usr/download/includes/header.h 
you can edit the EXECUTABLE= field to generate your executable with sepecified name 
after making the above changes to the makefile you run the make file using make command, make sure that you are executing the command from the same directory in which your source files and makefile is present. ( main.c insert.c lookup_packet.c delete.c hash_func.c and makefile all in same directory)
now run the executable generated , you need root priveliges to run the executable since i am using raw sockets. so run the command sudo ./<executable>
it start displaying the five tuples of the packets flowing via your system. Now run the server program in sepearate terminal and client program in another separate terminal. you can see the clients ip server ip and their respective port numbers and protocol.
to look up or search ,delete , insert  a packet press ctrl+c in the terminal of main executable then you can see menu with options like lookup , insert , delete and exit . enter your choice as corresponding interger in the menu then you have enter the five tuples of the packet you want to search or insert or delete then corresponding action will happen. 
after completion of the task (lookup or deletet or insert) it resumes capturing packets .
you can exit or lookup again by pressing ctrl+c .


NOTE : you can edit the server ip and port in the appropriate pre-processor directives of server and client programs.
      Run the main executable as super user
