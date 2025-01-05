#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

Bool_t Wave(string data_file = "wave_0.dat" /* domyślna nazwa pliku */, Bool_t removing_baseline = kTRUE /* zmienna odpowiadająca za odejmowanie linii bazowej */){
    
    // tworzenie pojemnika na dane
    fstream decector_data; 

    // wczytywanie danych z pliku (przy założeniu, że jest to plik binarny)
    decector_data.open(data_file, ios::binary | ios::in);

    // komunikat w przypadku błędu podczas otwierania pliku
    if (!decector_data.is_open()){ 
        cout << "Nie udało się załadować pliku!" << endl;
    }
    
    // długość pojedynczego sygnału
    Int_t signal_lenght = 1024; 

    // tworzenie płótna
    TCanvas *canvas = new TCanvas("canvas", "canvas", 700 ,400);

    // tworzenie histogramu (w zakresie od 0 do 1024)
    TH1F *histogram = new TH1F("histogram","signal", signal_lenght, 0, signal_lenght);

    // zdefiniowanie tytułów osi
    histogram->GetXaxis()->SetTitle("Czas (ns)");
    histogram->GetYaxis()->SetTitle("Amplituda (mV)");

    // zdefiniowanie zakresów histrogramu
    histogram->GetXaxis()->SetRangeUser(0, signal_lenght);
    histogram->GetYaxis()->SetRangeUser(400,1000);

    // tworzenie wektora przechowującego wartości jednego sygnał↓
    vector<float> signal_vector; 

    // zmienne pomocnicze do konwersji wartości z binarnej na wartość typu float
    float* float_value;
    char * binary_value = new char[sizeof(float)];
    float conversion_constant = 1/4.096;

    // numer wartości w danym sygnale (od 0 do 1023)
    Int_t value_number = 0;

    // numer sygnału
    Int_t signal_number = 1;

        
    // przypadek, w którym linia bazowa jest odejmowana
    if(removing_baseline == kTRUE){

        // dopóki nie dotrzemy do końca pliku
        while(!decector_data.eof()){

            // odczytanie pojedynczej wartości binarnej z pliku i zapisanie jej w zmiennej binary_value 
            decector_data.read(binary_value, sizeof(float));

            // rzutowanie wartości binarnej na zmienną typu float
            float_value = (float*)binary_value;

            // konwersja na wartość wyrażoną w mV
            *float_value *= conversion_constant;            
            
            // dodanie pojedynczej wartości do wektora przechowującego wartości sygnału
            signal_vector.push_back(*float_value);

            // przejście do kolejnej pojedynczej wartości (iteracja)
            value_number += 1;

            // koniec pojedynczego sygnału (co 1024 iteracje)
            if(value_number%signal_lenght == 0){

                // obliczanie sumy z 50 pierwszych wartości sygnału
                Float_t first_50_sum = accumulate(signal_vector.begin(), signal_vector.begin() + 50, 0.0);

                // obliczanie średniej z 50 pierwszych wartości sygnału (linii bazowej)
                Float_t first_50_average = first_50_sum/50;
                    
                    // odejmowanie średniej od każdej wartości w sygnale (odejmowanie linii bazowej)
                    for(Int_t i = 0; i < signal_lenght; i++){
                        histogram->SetBinContent(i + 1, signal_vector[i] - first_50_average);
                    }
                    
                    // rysowanie histogramu
                    histogram->Draw();

                    // tworzenie komunikatu rysowanego na płótnie
                    TPaveText *pt = new TPaveText(0.7,0.75,0.2,0.85,"NDC");

                    // wypełnienie białym kolorem
                    pt->SetFillColor(0);

                    // edytowanie tekstu
                    pt->SetTextAlign(12);

                    // utworzenie treści komunikatu
                    pt->AddText(Form("Odjeto linie bazowa o wartosci: %f", first_50_average));

                    // rysowanie komunikatu
                    pt->Draw();  

                    // zmiana zakresu wartości na osi Y
                    histogram->GetYaxis()->SetRangeUser(400 - first_50_average, 1000 - first_50_average);

                    // tworzenie tytułu
                    histogram->SetTitle(Form("Sygnal numer %i", signal_number));

                    // aktualizowanie płótna
                    canvas->Update();

                    // zatrzymanie programu pozwalające na przeglądanie histogramów jeden po drugim
                    canvas->WaitPrimitive();

                    // czyszczenie histogramu przed następnym sygnałem
                    histogram->Reset();

                    // czyszczenie wektora wartości przed następnym sygnałem
                    signal_vector.clear();

                    // czyszczenie numeru wartości
                    value_number = 0;

                    // przejście do następnego sygnału
                    signal_number += 1;
            }
        }
    }



    // przypadek, w którym linia bazowa nie jest odejmowana
    else{ 
        
        while(!decector_data.eof()){

            // odczytanie pojedynczej wartości binarnej z pliku i zapisanie jej w zmiennej binary_value 
            decector_data.read(binary_value, sizeof(float));

            // rzutowanie wartości binarnej na zmienną typu float
            float_value = (float*)binary_value;

            // konwersja na wartość wyrażoną w mV
            *float_value *= conversion_constant;            
            
            // dodanie pojedynczej wartości do wektora przechowującego wartości sygnału
            signal_vector.push_back(*float_value);

            // przejście do kolejnej pojedynczej wartości (iteracja)
            value_number += 1;

            // koniec pojedynczego sygnału (co 1024 iteracje)
            if(value_number%signal_lenght == 0){

                // wypełnianie histogramu
                for(Int_t i = 0; i < signal_lenght; i++){
                    histogram->SetBinContent(i + 1, signal_vector[i]);
                }
                    
                // rysowanie histogramu
                histogram->Draw();

                // tworzenie tytułu
                histogram->SetTitle(Form("Sygnal numer %i", signal_number));

                // aktualizowanie płótna
                canvas->Update();

                // zatrzymanie programu pozwalające na przeglądanie histogramów jeden po drugim
                canvas->WaitPrimitive();

                // czyszczenie histogramu przed następnym sygnałem
                histogram->Reset();

                // czyszczenie wektora wartości przed następnym sygnałem
                signal_vector.clear();

                // czyszczenie numeru wartości
                value_number = 0;

                // przejście do następnego sygnału
                signal_number += 1;
            }
        }        
    }

    // zamykanie pliku
    decector_data.close();

    // koniec funkcji
    return kTRUE; 
}