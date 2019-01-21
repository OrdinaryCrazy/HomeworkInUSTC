/*PLATFORM:UBUNTU 17.10*/
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cstring>

using namespace std;

typedef map<string,unsigned int*> Item;

char* strlow(char* str){
    char* ptr = str;
    while(*ptr != '\0'){
        if(isupper(*ptr))
            *ptr = tolower(*ptr);
        ptr++;
    }
    return str;
}

int main(int argc, char const *argv[])
{
    if(argc != 3){
        cout << "Wrong Arguments\n";
        return -1;
    }
    int NumberOfFiles = *argv[1] - 48;
    string FilePath(argv[2]);

    fstream PostingListFile;
    fstream DictionaryFile;
    PostingListFile.open("list.txt",ios::out | ios::in);
    DictionaryFile.open("dict.txt",ios::out);

    Item Dictionary;

    for(int i = 1;i <= NumberOfFiles;i++){

        string FileName = FilePath;
        FileName.append(1,(char)(i + 48)).append(".txt");
        fstream InputFile;
        InputFile.open(FileName.data());
        InputFile >> noskipws;

        char* Buffer;
        Buffer = new char[500];
        char Divider[30] = " ,.;[]0123456789()-—\"\'%";
        while(! InputFile.eof()){
            InputFile.getline(Buffer,500);
            Buffer = strlow(Buffer);
            char* WordsInThisLine = strtok(Buffer,Divider);
            while(WordsInThisLine != NULL){
                if(! Dictionary.count(WordsInThisLine)){
                    unsigned int* tmp;
                    tmp = new unsigned int[2];
                    tmp[0] = 2; tmp[1] = i; 
                    Dictionary[WordsInThisLine] = tmp;
                }
                else{
                    if(Dictionary[WordsInThisLine][1] != i){
                        Dictionary[WordsInThisLine][0]++;
                        Dictionary[WordsInThisLine][1] = i;
                    }
                }
                WordsInThisLine = strtok(NULL,Divider);
            }
        }
        InputFile.close();
    }
    /* Building posting list */
    Item::iterator WritePointer = Dictionary.begin();
    Item::iterator FrontPointer = WritePointer;
    WritePointer->second[1] = 0;
    WritePointer++;
    PostingListFile << (FrontPointer->second[0] - 1) << ' ';
    for (int j = 1;j < FrontPointer->second[0] - 1;j++) {
        PostingListFile << 0 << " ";
    }
    PostingListFile << 0 << endl;
    while(WritePointer != Dictionary.end()){
        WritePointer->second[1] = FrontPointer->second[1] + FrontPointer->second[0] * 2;
        PostingListFile << (WritePointer->second[0] - 1) << ' ';
        for (int j = 1;j < WritePointer->second[0] - 1;j++) {
            PostingListFile << 0 << ' ';
        }
        PostingListFile << 0 << endl;
        FrontPointer = WritePointer;
        WritePointer++;
    }
    /* Filling posting list */
    for(int i = 1;i <= NumberOfFiles;i++){

        string FileName = FilePath;
        FileName.append(1,(char)(i + 48)).append(".txt");
        fstream InputFile;
        InputFile.open(FileName.data());
        InputFile >> noskipws;

        char* Buffer;
        Buffer = new char[500];
        char Divider[30] = " ,.;[]0123456789()-—\"\'%";
        while(! InputFile.eof()){
            InputFile.getline(Buffer,500);
            Buffer = strlow(Buffer);
            char* WordsInThisLine = strtok(Buffer,Divider);
            
            while(WordsInThisLine != NULL){
                PostingListFile.seekp(Dictionary[WordsInThisLine][1],ios::beg);
                unsigned int Doc;
                PostingListFile >> Doc;
                /* Jump the first one */
                PostingListFile >> Doc;
                while(Doc != 0 && Doc != i){
                    PostingListFile >> Doc; 
                }
                if(Doc != i){ 
                    PostingListFile.seekp(-1,ios::cur);
                    PostingListFile << i;
                }
                WordsInThisLine = strtok(NULL,Divider);
            }
        }
        InputFile.close();
    }
    WritePointer = Dictionary.begin();
    while(WritePointer != Dictionary.end()){
        DictionaryFile << WritePointer->first << ' ';
        DictionaryFile << WritePointer->second[1] << endl;
        WritePointer++;
    }

    PostingListFile.close();
    DictionaryFile.close();

    return 0;
}
