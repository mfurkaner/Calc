#include "bordro.hpp"

Bordro asgari_bordro;

void asgari_ucret_set(){
    double yeni_asg = 20002;

    for(int i=0; i<12;i++){
        asgari_bordro.gelir_ekle(yeni_asg);
    }
}

void Bordro::gelir_ekle(double brut){
    _gelirler.push_back(Gelir(brut, GelirTuru::Ikramiye));
    _gelirler.back().net_hesapla(_vergilendirilen_gelir);
}

void Bordro::ikramiye_ekle(double brut){
    _gelirler.push_back(Gelir(brut));
    _gelirler.back().net_hesapla(_vergilendirilen_gelir);
}


void Bordro::gelirleri_yazdir(){

    std::cout << _gelirler.size() << std::endl;
    std::cout << "Brut | Sigorta | Gelir V | Damga |  Net  | Ort dilim |  Ele geçen  \n";

    int j = 0;
    for( int i = 0; i < _gelirler.size(); i++ ){
        _gelirler[i].yazdir();
        auto ab = asgari_bordro.gelirler().at(i);
        std::cout << " | " << _gelirler[i].net() + ab.gv() + ab.dv() << std::endl;

    }
}


double Bordro::toplam_ele_gecen(){
    double toplam = 0;
    for( int i = 0; i < _gelirler.size(); i++ ){
        auto ab = asgari_bordro.gelirler().at(i);
        toplam += _gelirler[i].net() + ab.gv() + ab.dv();
    }

    return toplam;
}