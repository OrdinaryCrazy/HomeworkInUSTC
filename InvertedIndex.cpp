/*PLATFORM:UBUNTU 17.10*/
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cstring>

using namespace std;

typedef map<string,set<unsigned int>> Item;

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

    fstream OutputFile;
    OutputFile.open("InvertedList.txt",ios::out);

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
                    set<unsigned int> Value;
                    Value.insert(i);
                    Dictionary[WordsInThisLine] = Value;
                }
                else{
                    if(!Dictionary[WordsInThisLine].count(i))
                        Dictionary[WordsInThisLine].insert(i);
                }
                WordsInThisLine = strtok(NULL,Divider);
            }
        }
    
        InputFile.close();
    }

    Item::iterator WritePointer = Dictionary.begin();
    set<unsigned int>::iterator SetPointer;
    while(WritePointer != Dictionary.end()){
        OutputFile << WritePointer->first << " ";
        SetPointer = WritePointer->second.begin();
        while(SetPointer != WritePointer->second.end()){
            OutputFile << *SetPointer << " ";
            SetPointer++;
        }
        OutputFile << endl;
        WritePointer++;
    }
    OutputFile.close();

    return 0;
}
