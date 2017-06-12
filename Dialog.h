//
// Created by bulat15g on 6/8/17.
//
#ifndef LETTERS_DIALOG_H
#define LETTERS_DIALOG_H

#include "dirent.h"
class Dialog{
public:
    bool dialogfinished=false;

    Dialog(){

    }

    void makeDialog(){
        int command;
        while (!dialogfinished){
            cout<<"ввести новую букву-1   распознать букву-2     выйти-3"<<endl;

            cin>>command;
            switch (command) {
                case 1: {

                    Letter in;char let;bool rand=false;
                    string fileName,addCommand;

                    cout << "введите название файла и  букву,соответствующую ей ;если нужна случ('rand')\n";
                    cin>>fileName;

                    if(fileName=="rand"){
                        rand= true;
                        in.fillRandLetter();
                        in.showLetter();
                    }
                    cin >> let;
                    if(!rand)in.readFromFile(fileName);

                    addCommand=parseLetToCommand(let);
                    addCommand=parseToAdd(addCommand);

                    in.writeToFile(addCommand);
                    break;


                }
                case 2: {


                    cout << "введите название файла\n";
                    string fileName;cin>>fileName;

                    Letter in;in.readFromFile(fileName);
                    Letter toComparsion;

                    double statistics[26][finddepth+1];
                    double localStatstics[finddepth+1];
                    double currentCompare;

                    char currentLetter=(char)97;
                    int localCountFiles;

                    //сверка общая(по буквам)
                    for (int i = 0; i < 26; ++i) {
                        currentLetter=intToEnglishChar(i);

                        localCountFiles=FilesCountInDirectory(parseLetToCommand(currentLetter));
                        for (int buff = 0; buff < finddepth + 1; ++buff) {
                            localStatstics[buff]=0;
                        }

                        //сверка по конкретной букве
                        if(localCountFiles>=1)
                        for (int j = 1; j <= localCountFiles; ++j) {

                            toComparsion.readFromFile((parseLetToCommand(currentLetter)+to_string(j)));
                            currentCompare=toComparsion.compare(in.image);

                            localStatstics[finddepth]+=currentCompare;
                            //далее,если сравнение более удачное,то идет замена предыдущих результатов

                            bool offsetSucces= false;
                            for (int k = 0;((k < finddepth-1)&&!offsetSucces); ++k) {
                                if(currentCompare>localStatstics[k]){
                                    offsetRightLocalStatistics(localStatstics,k,finddepth+1,currentCompare);
                                    offsetSucces= true;

                                }
                            }
                        }

                        //ввод в общую статистику
                        if(localCountFiles!=0){
                            localStatstics[finddepth]/=localCountFiles;
                            for (int m = 0; m < finddepth + 1; ++m) {
                                statistics[i][m]=localStatstics[m];
                            }
                        }
                        else{
                            for (int m = 0; m < finddepth + 1; ++m) {
                                statistics[i][m]=0;
                            }
                        }


                    }

                    for (int i = 0; i < 26; ++i) {
                        for (int j = 0; j < finddepth + 1; ++j) {
                            cout<<statistics[i][j]<<"     ";
                        }
                        cout<<"  "<<intToEnglishChar(i)<<endl;
                    }

                    break;

                }
                case 3:{
                    dialogfinished= true;
                    break;
                }

            }

        }
    }

    //123 ->112
    void offsetRightLocalStatistics(double mybuff[],int currentIndex,int Size,double currentCompare){
        for (int i = Size-2; i <= currentIndex; --i) {
            mybuff[i]=mybuff[i-1];
        }
        mybuff[currentIndex]=currentCompare;
    }

    string parseToAdd(string addCommand){
        int count=FilesCountInDirectory(addCommand);
        count++;
        addCommand+=to_string(count);
        return addCommand;
    }

    string parseLetToCommand(char let){
        string addCommand;

        addCommand = "Primitives/";
        addCommand += let;
        addCommand+="/";

        return addCommand;
    }

    int FilesCountInDirectory(string directoryName){

        int filecount=0;
        DIR * dir;struct dirent *entry;

        dir=opendir(directoryName.c_str());
        while (dir&&(entry=readdir(dir)) !=NULL ){
            if (entry->d_type==DT_REG) filecount++;
        }
        return filecount;
    }

    void fillRandLetters(int numberOfFillment){
        Letter in;
        char let;
        for (int i = 0; i < numberOfFillment; ++i) {
            in.fillRandLetter();
            let=(char)(97+rand()%26);\
            in.writeToFile(parseToAdd(parseLetToCommand(let)));
        }
    }

    char intToEnglishChar(int i){
        return (char)(97+i);
    }


};



#endif //LETTERS_DIALOG_H
