#ifndef BORDRO_HPP
#define BORDRO_HPP

#include <iostream>
#include <float.h>

struct GelirVergisiDilimi{
    double limit;
    double yuzde;

    double max_vergi;
};

#define DILIM_SAYISI 5
static GelirVergisiDilimi dilimler_2023[DILIM_SAYISI] = {
    GelirVergisiDilimi{ 
        70000,
        0.15,
        10500
    },
    GelirVergisiDilimi{ 
        150000,
        0.2,
        26500
    },
    GelirVergisiDilimi{ 
        370000,
        0.27,
        85900
    },
    GelirVergisiDilimi{ 
        1900000,
        0.35,
        621400
    },
    GelirVergisiDilimi{ 
        DBL_MAX,
        0.40,
        DBL_MAX
    }
};

static GelirVergisiDilimi dilimler[DILIM_SAYISI] = {
    GelirVergisiDilimi{ 
        110000,
        0.15,
        16500
    },
    GelirVergisiDilimi{ 
        230000,
        0.2,
        40500
    },
    GelirVergisiDilimi{ 
        870000,
        0.27,
        85900
    },
    GelirVergisiDilimi{ 
        3000000,
        0.35,
        213300
    },
    GelirVergisiDilimi{ 
        DBL_MAX,
        0.4,
        DBL_MAX
    }
};


enum GelirTuru{
    Maas = 0,
    Ikramiye = 1
};

class Gelir{
    double _brut;
    double _net;
    double _gv;
    double _sigorta;
    double _dv;

    GelirTuru _tur;
public:
    Gelir(double brut, GelirTuru tur = GelirTuru::Maas) : _brut(brut), _tur(tur) {    }

    void net_hesapla(double& vergilendirilen_gelir){
        _sigorta = _brut * 0.15;
        _dv = _brut * 0.00759;
        double taxable = _brut - _sigorta;

        int i = 0;
        for(i = 0; i < DILIM_SAYISI; i++){
            if(dilimler[i].limit > vergilendirilen_gelir){
                break;
            }
        }

        if(dilimler[i].limit < vergilendirilen_gelir + taxable && i + 1 < DILIM_SAYISI){
            _gv = (dilimler[i].limit - vergilendirilen_gelir) * dilimler[i].yuzde;
            _gv += (taxable - dilimler[i].limit + vergilendirilen_gelir) * dilimler[i + 1].yuzde;
        }
        else{
            _gv = taxable * dilimler[i].yuzde;
        }
        vergilendirilen_gelir += taxable;
        _net = taxable - _gv - _dv;
    }


    void yazdir(){
        std::cout << _brut << " | " << _sigorta << " | " << _gv << " | " << _dv << " | " << _net << " | " << _gv / (_brut - _sigorta);
    }

    double net() { return _net;}
    double gv() { return _gv;}
    double dv() { return _dv;}

    GelirTuru tur() { return _tur;}
};

class Bordro{
    std::vector<Gelir> _gelirler;

    double _vergilendirilen_gelir = 0;

public:

    void gelir_ekle(double brut);
    void ikramiye_ekle(double brut);

    void gelirleri_yazdir();

    std::vector<Gelir> gelirler() { return _gelirler;}


    double toplam_ele_gecen();
};

void asgari_ucret_set();


#endif