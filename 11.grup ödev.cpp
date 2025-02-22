#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

class Student {
public:

    Student() {

        readFromCsv();
        average();
    }


    string* AdList;
    string* OgrNoList;
    float* ArasinavList;
    float* IkinciSinavList;
    float* OdevList;
    float* FinalList;
    int* devamSayisiList;
    float* averageList;

    int studentCount = 0;
    const string dosyaAdi = "girdi.csv";

    ~Student() {
        delete[] AdList;
        delete[] OgrNoList;
        delete[] ArasinavList;
        delete[] IkinciSinavList;
        delete[] OdevList;
        delete[] FinalList;
        delete[] devamSayisiList;
        delete[] averageList;
    }

    void initArrays() {
        cout << "ogrenci sayisi:" << this->studentCount << endl;
        this->AdList = new string[this->studentCount];
        this->OgrNoList = new string[this->studentCount];
        this->ArasinavList = new float[this->studentCount];
        this->IkinciSinavList = new float[this->studentCount];
        this->OdevList = new float[this->studentCount];
        this->FinalList = new float[this->studentCount];
        this->devamSayisiList = new int[this->studentCount];
        this->averageList = new float[this->studentCount];
    }

    void readFromCsv() {
        ifstream file(this->dosyaAdi);
        if (!file.is_open()) {
            cerr << "Dosya acilamadi: " << this->dosyaAdi << endl;
            return;
        }

        string line;
        int studentCount = 0;
        while (getline(file, line)) {
            studentCount++;
        }
        this->studentCount = studentCount;

        file.clear();
        file.seekg(0, ios::beg);


        initArrays();
        int index = 0;
        while (getline(file, line) && index < studentCount) {
            stringstream ss(line);
            string field;


            getline(ss, AdList[index], ',');
            getline(ss, OgrNoList[index], ',');
            getline(ss, field, ',');
            ArasinavList[index] = stof(field);

            getline(ss, field, ',');
            IkinciSinavList[index] = stof(field);

            getline(ss, field, ',');
            OdevList[index] = stof(field);

            getline(ss, field, ',');
            FinalList[index] = stof(field);

            if (getline(ss, field)) {
                devamSayisiList[index] = stoi(field);
            }
            else {
                devamSayisiList[index] = 0;
            }
            index++;
        }
        file.close();
    };

    void average() {
        for (int i = 0; i < studentCount; ++i) {
            averageList[i] = ArasinavList[i] * 0.2 + IkinciSinavList[i] * 0.2 + OdevList[i] * 0.2 + FinalList[i] * 0.4;
        }
    }

    void print(int mode = -1) {

        cout << setfill('-') << setw(50) << "-" << endl;
        cout << setfill(' ') << left <<
            "| " << setw(15) << "Ad" <<
            "| " << setw(10) << "No" <<
            "| " << setw(10) << "Ortalama" <<
            "| " << setw(8) << "Devam" <<
            "| " << endl;

        cout << setfill('-') << setw(50) << "-" << endl;

        for (int i = 0; i < studentCount; ++i) {
            if (mode == -1) {
                cout << setfill(' ') << left <<
                    "| " << setw(15) << AdList[i]
                    << "| " << setw(10) << OgrNoList[i] <<
                    "| " << fixed << setprecision(2) << setw(10) << averageList[i]
                    << "| " << setw(8) << devamSayisiList[i]
                    << "|" << endl;
            }
            else if (mode == 0 && averageList[i] < 50) {

                cout << setfill(' ') << left
                    << "| " << setw(15) << AdList[i]
                    << "| " << setw(10) << OgrNoList[i]
                    << "| " << fixed << setprecision(2) << setw(10) << averageList[i]
                    << "| " << setw(8) << devamSayisiList[i]
                    << "|" << endl;
            }

            else if (mode == 1 && averageList[i] >= 50) {

                cout << setfill(' ') << left
                    << "| " << setw(15) << AdList[i]
                    << "| " << setw(10) << OgrNoList[i]
                    << "| " << fixed << setprecision(2) << setw(10) << averageList[i]
                    << "| " << setw(8) << devamSayisiList[i]
                    << "|" << endl;
            }
        }

        cout << setfill('-') << setw(50) << "-" << endl;

    }

    void print(string dosya) {

        ofstream file(dosya);
        if (!file) {
            cerr << "dosya acilamadi!" << dosya << endl;
            return;
        }


        for (int i = 0; i < studentCount - 1; i++) {
            for (int j = 0; j < studentCount - i - 1; j++) {
                if (averageList[j] < averageList[j + 1]) {

                    swap(AdList[j], AdList[j + 1]);
                    swap(OgrNoList[j], OgrNoList[j + 1]);
                    swap(ArasinavList[j], ArasinavList[j + 1]);
                    swap(IkinciSinavList[j], IkinciSinavList[j + 1]);
                    swap(OdevList[j], OdevList[j + 1]);
                    swap(FinalList[j], FinalList[j + 1]);
                    swap(devamSayisiList[j], devamSayisiList[j + 1]);
                    swap(averageList[j], averageList[j + 1]);

                }
            }
        }


        file << "Ad,Ogrenci No,Arasinav,Ikinci Sinav,Odev,Final,Devam,Ortalama,Durum\n";

        file << "GECENLER:" << endl;
        for (int i = 0; i < studentCount; ++i) {

            string durum;

            if (averageList[i] >= 50)
                durum = "gecti";
            else
                durum = "kaldi";


            if (durum == "gecti") {


                file << AdList[i] << "," << OgrNoList[i] << "," << ArasinavList[i] << "," << IkinciSinavList[i] << ","
                    << OdevList[i] << "," << FinalList[i] << "," << devamSayisiList[i] << "," << averageList[i] << "," << durum << endl;
            }



        }
        file << "KALANLAR:" << endl;
        for (int i = 0; i < studentCount; i++) {

            string durum;
            if (averageList[i] >= 50)
                durum = "gecti";
            else
                durum = "kaldi";

            if (durum == "kaldi") {


                file << AdList[i] << "," << OgrNoList[i] << "," << ArasinavList[i] << "," << IkinciSinavList[i] << ","
                    << OdevList[i] << "," << FinalList[i] << "," << devamSayisiList[i] << "," << averageList[i] << "," << durum << endl;
            }
        }






        cout << "Dosya olusturuldu." << endl;
        file.close();
    }


};

int main() {
    Student* student = new Student();

    cout << "Listelemek icin bir secim yapin:" << endl;
    cout << "0 - Kalan ogrenciler\n1 - Gecen ogrenciler\n" << endl;

    string giris;
    cout << "Seciminiz: ";
    cin >> giris;

    if (isdigit(giris[0]) || giris[0] == '-') {
        int mode = stoi(giris);
        student->print(mode);
    }
    else {
        student->print(giris);
    }


    delete student;
    return 0;
}