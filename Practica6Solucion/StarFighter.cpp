/** 
 * @file StarFighter.cpp
 * @author Casipro Gramo
 * 
 * @date Fecha estelar 20160309
 */

#include <stdexcept>
#include <sstream>
#include <iostream>

#include "StarFighter.h"

using std::string;

int StarFighter::_numStarFighters = 0;

StarFighter::StarFighter ( ): StarFighter ( "", "" ) {
    for(int i=0;i<MAX;++i){
        piezas[i]= nullptr;
    }
}

StarFighter::StarFighter ( string marca, string modelo ):
                           _marca (marca), _modelo(modelo)
{
   _numStarFighters++;
   _idSF = _numStarFighters;

    for(int i=0;i<MAX;++i){
        piezas[i]= nullptr;
    }

}

StarFighter::StarFighter ( const StarFighter& orig ):
    _marca(orig._marca),_modelo(orig._modelo),
    _numPlazas(orig._numPlazas)
{
   _numStarFighters++;
   _idSF = _numStarFighters;

   for(int i=0;i<orig.numPiezas;++i){
       //Para que dos naves distintas no apunten a las mismas piezas
       piezas[i]=new Pieza(*orig.piezas[i]);
   }
}

StarFighter::~StarFighter ( )
{
   //std::cout<<"Destruyendo nave"<<std::endl;

    for(int i=0;i<MAX;++i){
        delete piezas[i];
        piezas[i]= nullptr;
    }
}

/**
 * @todo Aquí hay que añadir la comprobación del parámetro y lanzar la excepción
 *       correspondiente. El número de plazas no puede ser <= 0
 */
StarFighter& StarFighter::setNumPlazas ( int numPlazas )
{
   if ( numPlazas <= 0 )
   {
      throw std::invalid_argument ( "StarFighter::StarFighter: el número de"
                                    " plazas no puede ser negativo" );
   }

    this->_numPlazas = numPlazas;
    return *this;
}

int StarFighter::getNumPlazas ( ) const
{
   return _numPlazas;
}

StarFighter& StarFighter::setModelo ( string modelo )
{
   this->_modelo = modelo;
   return *this;
}

string StarFighter::getModelo ( ) const
{
   return _modelo;
}

StarFighter& StarFighter::setMarca ( string marca )
{
   this->_marca = marca;
   return *this;
}

string StarFighter::getMarca ( ) const
{
   return _marca;
}

int StarFighter::getIdSF ( ) const
{
   return _idSF;
}

string StarFighter::toCSV () const
{
   std::stringstream aux;

   aux << _marca << " ; "
       << _modelo << " ; "
       << _numPlazas;

   return aux.str ();
}

StarFighter& StarFighter::operator = (const StarFighter& otro)
{
   if ( this != &otro )
   {
      _marca = otro._marca;
      _modelo = otro._modelo;
      _numPlazas = otro._numPlazas;

      //Para evitar que hayan dos naves apuntando a las mismas piezas
      for(int i=0;i<otro.numPiezas;++i){
          piezas[i]=new Pieza(*otro.piezas[i]);
      }
   }
   
   return *this;
}

void StarFighter::fromCSV (string& datos)
{
   std::stringstream aux;
   
   aux << datos;
   
   getline ( aux, _marca, ';' );
   getline ( aux, _modelo, ';' );
   aux >> _numPlazas;
}

StarFighter &StarFighter::addPieza(Pieza &p) {
    if(numPiezas==MAX){
        throw std::invalid_argument("StarFighter::addPieza. No se pueden añadir mas piezas");
    }
    piezas[numPiezas]=new Pieza(p);
    ++numPiezas;

    return *this;
}

Pieza &StarFighter::obtenerPieza(int cual) {
    if(cual<1 || cual > numPiezas){
        throw std::invalid_argument("StarFighter::obtenerPieza  ,Nos se puedo obtener la pieza");
    }

    return *piezas[cual-1];
}

void StarFighter::quitarPieza(int cual) {
    if(cual<1 || cual > numPiezas){
        throw std::invalid_argument("StarFighter::quitarPieza  ,Nos se puedo obtener la pieza");
    }

    delete piezas[cual-1];
    piezas[cual-1]= nullptr;

    for(int i=cual-1;i<numPiezas-1;++i){
        piezas[i]=piezas[i+1];
    }
    delete piezas[numPiezas-1];
    piezas[numPiezas-1]= nullptr;
}

float StarFighter::calculaPeso() {
    float peso =0;

    for(int i=0;i<numPiezas;++i){
        peso =peso + piezas[i]->getPeso();
    }

    return peso;
}
