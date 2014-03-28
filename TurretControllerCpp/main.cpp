/* 
 * File:   main.cpp
 * Author: tyler
 *
 * Created on March 23, 2014, 3:24 PM
 */

#include <cstdlib>
#include <termios.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <iostream>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    char data[] = {'f','r','f','r'};
    FILE *file;
    file = fopen("/dev/ttyACM0","w");
    char input;
    cin>>input;
    while(input!='q')
    {
        cout<<"Input is :"<<input;
        fprintf(file, "%c",input);
        cin>>input;
    }
    fclose(file);
    return 0;
}

