//TP 2018/2019: Zadaća 5, Zadatak 6
#include <iostream>
#include <fstream>
#include <string>

template <typename TipEl>
class DatotecniKontejner
{
    std::fstream tok;
    public:
    DatotecniKontejner(const std::string &ime_datoteke):tok(ime_datoteke,std::ios::binary | std::ios::out)
    {

        if(!tok)
        throw std::logic_error("Problemi prilikom otvaranja ili kreiranja datoteke");
        tok.close();
        tok.open(ime_datoteke,std::ios::binary|std::ios::in|std::ios::out);
    }
    int DajBrojElemenata()
    {
        tok.seekg(0,std::ios::end);
        return tok.tellg()/sizeof(TipEl);
    }
    TipEl DajElement(int pozicija)
    {

        if((pozicija*sizeof(TipEl))>=(((*this).DajBrojElemenata()-1)*sizeof(TipEl)))
        {
        throw std::range_error("Neispravna pozicija");
        }
        tok.seekg(int(pozicija*sizeof(TipEl)));
        TipEl el;
        tok.read(reinterpret_cast<char*>(&el),sizeof(el));
        return el;
    }
    void IzmijeniElement(int pozicija,const TipEl &element)
    {
        TipEl el=element;
        tok.seekp(int(pozicija*sizeof(TipEl)));
        tok.write(reinterpret_cast<char*>(&el),sizeof(el));
        tok.flush();
    }
   /* void Sortiraj(std::function<bool(const TipEl &,const TipEl &)>kriterij=std::less<TipEl>());*/
//template<typename TipEl>
    void DodajNoviElement(const TipEl &element)
    {
        TipEl el=element;
        tok.seekg(0,std::ios::end);
        tok.seekp(tok.tellg());
        tok.write(reinterpret_cast<char*>(&el),sizeof(el));
        tok.flush();
    }
};
int main ()
{
    DatotecniKontejner<int> t("dat.bin");
	return 0;
}
