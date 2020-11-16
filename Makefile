all: project1 project2 project3
	
project1: project1.c
	gcc -o project1 -std=c99 -Wall -O1 project1.c
project2: project2.c
	gcc -o project2 -std=c99 -Wall -O1 project2.c
project3: project3.c
	gcc -o project3 -std=c99 -Wall -O1 project3.c
