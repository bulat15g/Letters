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

                    int statistics[26][finddepth+1];
                    int localStatstics[finddepth+1];
                    int currentCompare;

                    char currentLetter=(char)97;
                    int localCountFiles;

                    //сверка общая(по буквам)
                    for (int i = 0; i < 26; ++i) {
                        currentLetter=(char)(97+i);

                        localCountFiles=FilesCountInDirectory(parseLetToCommand(currentLetter));
                        for (int buff = 0; buff < finddepth + 1; ++buff) {
                            localStatstics[buff]=0;
                        }

                        //сверка по конкретной букве
                        cout<<localCountFiles<<"     count files"<<currentLetter<<endl;
                        //КРАШ ТУТ НА 2 букве
                        for (int j = 1; j <= localCountFiles; ++j) {
                            cout<<"FUCKEN SHET and    "<<endl;

                            toComparsion.readFromFile((parseLetToCommand(currentLetter)+to_string(j)));
                            currentCompare=toComparsion.compare(in.image);

                            localStatstics[finddepth]+=currentCompare;
                            //далее,если сравнение более удачное,то идет замена предыдущих результатов

                            for (int k = 0; k < finddepth-1; ++k) {
                                if(currentCompare>localStatstics[k]){
                                    //сдвиг
                                    for (int l = finddepth-1; l >k ; --l) {
                                        localStatstics[l]=localStatstics[l-1];
                                    }
                                    localStatstics[k]=currentCompare;
                                }
                            }
                        }
//
                        localStatstics[finddepth]/=localCountFiles;
                        for (int m = 0; m < finddepth + 1; ++m) {
                            statistics[i][m]=localStatstics[m];
                        }

                    }
                    cout<<"aaand im here";
                    for (int i = 0; i < 26; ++i) {
                        for (int j = 0; j < finddepth + 1; ++j) {
                            cout<<statistics[i][j]<<"     ";
                        }
                        cout<<"  "<<(char)(97+i)<<endl;
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


};



#endif //LETTERS_DIALOG_H
