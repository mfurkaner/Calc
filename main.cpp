#include <iostream>
#include <float.h>

#include "src/bordro.hpp"

extern Bordro asgari_bordro;


int main(){


    asgari_ucret_set();

    double brut2023 = 0;

    std::cout << "2023 yil sonu brut maasin kac? (TL) : ";
    std::cin >> brut2023;

    Bordro bosch;

    std::cout << "Ocak zammi kac olsun? (%) : ";
    double ocak_zam;
    std::cin >> ocak_zam;

    ocak_zam /= 100;
    ocak_zam += 1;

    int ay = 12;

    for(int i=0; i<6 ; i++){
        bosch.gelir_ekle(brut2023*1.33*ocak_zam);
    }

    std::cout << "Temmuz zammi kac olsun? (%) : ";
    double tem_zam;
    std::cin >> tem_zam;

    tem_zam /= 100;
    tem_zam += 1;

    for(int i=0; i<6 ; i++){
        bosch.gelir_ekle(57000*1.33*ocak_zam*tem_zam);
    }
    

    bosch.gelirleri_yazdir();

    std::cout << "Tot : " << bosch.toplam_ele_gecen() << std::endl;

    std::cout << "Kac TL ile baslamak istersin? : ";

    double start;
    double toplam = bosch.toplam_ele_gecen();

    std::cin >> start;
    

    double n = toplam / start;
    double min = DBL_MAX;
    double min_k;
    


    for ( double k = 1 ; k < 2 ; k+=0.00001){

        double value = 1;

        for(int iter = 1; iter < ay; iter++){
            value += std::pow(k, iter);
        }

        value -= n;

        if(abs(value) < min){
            min = abs(value);
            min_k = k;
        }
    }

    std::cout << start <<  " TL baslama maasi icin ortalama aylik zam degeri : % " << (min_k - 1)*100 << std::endl;

    std::cout << "Aylik yuzde kac zam almak istersin? (%) : ";
    double actual_k;
    std::cin >> actual_k;

    actual_k /=100;
    actual_k += 1;

    std::cout << "Bu, yilda % " << (pow(actual_k, 11) - 1)*100 << " zam eder.\n";
    

    std::vector<double> proposed;
    std::vector<double> siemens;

    proposed.push_back(start);
    siemens.push_back(55000);
    double siemens_k = pow(actual_k, 3); 

    std::cout << "Siemenste % " << (siemens_k - 1)*100 << " ceyrek zammi alsan\n";

    for(int i = 0; i < ay - 1 ; i++){
        proposed.push_back(proposed.back()*actual_k);

        if( i % 3 == 2){
            siemens.push_back(siemens.back()*siemens_k);
        }
        else{
            siemens.push_back(siemens.back());
        }
    }
    std::cout << std::endl;

    std::cout << "  proposed  |  siemenste " << std::endl; 
    double prop_tot = 0;
    double siemens_tot = 0;
    double yatacak_tot = 0;
    for(int i = 0; i < proposed.size(); i++){
        auto ab = asgari_bordro.gelirler().at(i);
        double yatacak = bosch.gelirler().at(i).net() + ab.gv() + ab.dv();
        std::cout << i+1 << ") " << proposed[i] << " TL  |  " << siemens[i] << " TL" << std::endl;
        prop_tot += proposed[i];
        siemens_tot += siemens[i];
        yatacak_tot += yatacak;
    }
    std::cout << std::endl;

    std::cout << "Kalan : " << yatacak_tot - prop_tot << " TL" <<std::endl;
    std::cout << "Siemensten : " << yatacak_tot - siemens_tot << " TL kar ettin (% " << (yatacak_tot - siemens_tot)/siemens_tot << ")" <<std::endl;

    std::cout << "  proposed  |  bütçe  |  ikramiye (dokunma)" << std::endl; 
    double dolar_try = 29;
    double ikramiye_tot_dolar = 0;
    for(int i=0; i<proposed.size(); i++){
        std::cout << i+1 << ") " << proposed[i] << " TL  |  "  << proposed[i]*3/4 << " TL  |  " << proposed[i]/4 << " TL (" << proposed[i]/(4*dolar_try) << " USD)" << std::endl;
        ikramiye_tot_dolar += proposed[i]/(4*dolar_try);
        dolar_try *= 1.041;
    }
    std::cout << std::endl;

    double buffer_fon = 0;
    double flat_buffer_fon = 0;
    double buffer_k = 1.041;

    std::cout << "Bufferda ortalama aylik %" << (buffer_k - 1)*100 << " artis olursa \n";

    std::cout << "  yatacak  |  proposed  |  buffera  |  buffer tlde kalsa  |  buffer degerlendirirsen " << std::endl; 
    for(int i = 0; i < proposed.size(); i++){
        auto ab = asgari_bordro.gelirler().at(i);
        double yatacak = bosch.gelirler().at(i).net() + ab.gv() + ab.dv();
        double artan = yatacak - proposed[i];
        buffer_fon *= buffer_k;
        buffer_fon += artan;
        flat_buffer_fon += artan;
        std::cout << i+1 << ") " << yatacak << " TL  |  "  << proposed[i] << " TL  |  "  << artan << " TL  |  " << flat_buffer_fon << " TL  |  " << buffer_fon << " TL" << std::endl;
    }

    double saved = ikramiye_tot_dolar + buffer_fon/dolar_try;
    std::cout << "\nToplam potansiyel biriktirilebilen miktar : " << saved  << " USD (1 USD = " << dolar_try << " TRY)" << std::endl;
    std::cout << "0.8 güvenlik payı ile : " << saved*0.8 << " USD" << std::endl;

    int yurt_disi_count = 0;
    double gunluk_artan_harcirah = 0;
    double artan_harcirah;
    std::cout << "Kaç kere yurt dışına çıktın? : ";
    std::cin >> yurt_disi_count;

    std::cout << "Ortalama günlük kaç dolar arttırdın? : ";
    std::cin >> gunluk_artan_harcirah;
    artan_harcirah = gunluk_artan_harcirah*yurt_disi_count;

    double yikama_artan = yurt_disi_count/(7*2)*20;

    std::cout << "Yurt dışından toplam artış : " << artan_harcirah + yikama_artan << " USD" <<std::endl;
    std::cout << "0.8 güvenlik payı ile : " << (artan_harcirah + yikama_artan)*0.8 << " USD" << std::endl;


    std::cout << "Yılda toplam potansiyel biriktirme : " << (artan_harcirah + yikama_artan + saved) << " USD" << std::endl;

    return EXIT_SUCCESS;
}