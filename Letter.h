//
// Created by temporal on 06.06.2017.
//

#ifndef UNTITLED_LETTER_H
#define UNTITLED_LETTER_H


int const dimention=8;
int const depth=2;
int const finddepth=3;

class Letter{
public:
    int image[dimention][dimention];

    Letter(int abc[dimention][dimention]){
        for (int i = 0; i < dimention; ++i) {
            for (int j = 0; j < dimention; ++j) {
                image[i][j]=abc[i][j];
            }
        }
    }

    Letter(){
        for (int i = 0; i < dimention; ++i) {
            for (int j = 0; j < dimention; ++j) {
                image[i][j]=0;
            }
        }
    }

    double compare(int abc[dimention][dimention]){
        double score=0;
        for (int i = 0; i < dimention; ++i) {
            for (int j = 0; j < dimention; ++j) {
                if (image[i][j]==abc[i][j]){
                    score++;
                }
            }
        }
        return score/((double)(dimention*dimention));
    }

    Letter(Letter &second) {
        for (int i = 0; i < dimention; ++i) {
            for (int j = 0; j < dimention; ++j) {
                this->image[i][j]=second.image[i][j];
            }
        }
    }

    void fillLetter(){
        for (int i = 0; i < dimention; ++i) {
            cout<<"введите "<<i<<"   строку";
            for (int j = 0; j < dimention; ++j) {
                cin>>image[i][j];
            }
        }
    }

    void fillRandLetter(){
        for (int i = 0; i < dimention; ++i) {
            for (int j = 0; j < dimention; ++j) {
                image[i][j]=rand()%depth;
            }
        }
    }

    void showLetter(){
        for (int i = 0; i < dimention; ++i) {
            for (int j = 0; j < dimention; ++j) {
                cout<<image[i][j]<<" ";

            }
            cout<<endl;
        }
        cout<<endl<<endl;
    }

    void readFromFile(string name){
        ifstream in;
        in.open(name);
        for (int i = 0; i < dimention; ++i) {
            for (int j = 0; j < dimention; ++j) {
                in>>image[i][j];
            }
        }
        in.close();
//        delete in;
    }

    void writeToFile(string name){
        ofstream out;
        out.open(name,ios::out);
        for (int i = 0; i < dimention; ++i) {
            for (int j = 0; j < dimention; ++j) {
                out<<image[i][j]<< " ";
            }
            out<<endl;
        }
        out.close();
//        delete out;
    }

//    ~Letter(){
//        delete[] image;
//    }

};

#endif //UNTITLED_LETTER_H
