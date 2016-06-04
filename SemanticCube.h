#ifndef GUARD_SEMANTIC_CUBE
#define GUARD_SEMANTIC_CUBE


#include <iostream>
#include <unordered_map>
#include "Quadruple.h"


class SemanticCube
{

  typedef std::unordered_map<int,int> dimThree;
  typedef std::unordered_map<int, dimThree> dimTwo;
  typedef std::unordered_map<int, dimTwo> dimOne;

public:
	dimOne getMatrix();
  int getResult(int op, int lOp, int rOp);

  const enum {
    T_ENTERO, T_REAL, T_CHAR, T_BOOL, T_INVALID
  };

private:

  //int
  dimThree intInt = {
  	{ Quadruple::I_SUMA, T_ENTERO},
  	{ Quadruple::I_RESTA, T_ENTERO},
  	{ Quadruple::I_DIV, T_ENTERO},
  	{ Quadruple::I_MULT, T_ENTERO},
    { Quadruple::I_MAYOR_QUE, T_BOOL},
    { Quadruple::I_MENOR_IGUAL_QUE, T_BOOL},
    { Quadruple::I_MENOR_QUE, T_BOOL},
    { Quadruple::I_MENOR_IGUAL_QUE, T_BOOL},
    { Quadruple::I_NO_IGUAL, T_BOOL},
    { Quadruple::I_IGUAL, T_BOOL}
  };

  dimThree intDouble = {
  	{ Quadruple::I_SUMA, T_REAL},
  	{ Quadruple::I_RESTA, T_REAL},
  	{ Quadruple::I_DIV, T_REAL},
  	{ Quadruple::I_MULT, T_REAL},
    { Quadruple::I_MAYOR_QUE, T_BOOL},
    { Quadruple::I_MENOR_IGUAL_QUE, T_BOOL},
    { Quadruple::I_MENOR_QUE, T_BOOL},
    { Quadruple::I_MENOR_IGUAL_QUE, T_BOOL},
    { Quadruple::I_NO_IGUAL, T_BOOL},
    { Quadruple::I_IGUAL, T_BOOL}
  };

  dimThree intBool = {
  	{ Quadruple::I_SUMA, T_INVALID},
  	{ Quadruple::I_RESTA, T_INVALID},
  	{ Quadruple::I_DIV, T_INVALID},
  	{ Quadruple::I_MULT, T_INVALID}	
  };

  dimThree intString = {
  	{ Quadruple::I_SUMA, T_CHAR},
  	{ Quadruple::I_RESTA, T_CHAR},
  	{ Quadruple::I_DIV, T_CHAR},
  	{ Quadruple::I_MULT, T_CHAR},
    { Quadruple::I_MAYOR_QUE, T_INVALID},
    { Quadruple::I_MENOR_IGUAL_QUE, T_INVALID},
    { Quadruple::I_MENOR_QUE, T_INVALID},
    { Quadruple::I_MENOR_IGUAL_QUE, T_INVALID},
    { Quadruple::I_NO_IGUAL, T_INVALID},
    { Quadruple::I_IGUAL, T_INVALID}
  };

  //double

  dimThree doubleInt = {
  	{ Quadruple::I_SUMA, T_REAL},
  	{ Quadruple::I_RESTA, T_REAL},
  	{ Quadruple::I_DIV, T_REAL},
  	{ Quadruple::I_MULT, T_REAL},
    { Quadruple::I_MAYOR_QUE, T_BOOL},
    { Quadruple::I_MENOR_IGUAL_QUE, T_BOOL},
    { Quadruple::I_MENOR_QUE, T_BOOL},
    { Quadruple::I_MENOR_IGUAL_QUE, T_BOOL},
    { Quadruple::I_NO_IGUAL, T_BOOL},
    { Quadruple::I_IGUAL, T_BOOL}
  };

  dimThree doubleDouble = {
  	{ Quadruple::I_SUMA, T_REAL},
  	{ Quadruple::I_RESTA, T_REAL},
  	{ Quadruple::I_DIV, T_REAL},
  	{ Quadruple::I_MULT, T_REAL},
    { Quadruple::I_MAYOR_QUE, T_BOOL},
    { Quadruple::I_MENOR_IGUAL_QUE, T_BOOL},
    { Quadruple::I_MENOR_QUE, T_BOOL},
    { Quadruple::I_MENOR_IGUAL_QUE, T_BOOL},
    { Quadruple::I_NO_IGUAL, T_BOOL},
    { Quadruple::I_IGUAL, T_BOOL}
  };

  dimThree doubleBool = {
  	{ Quadruple::I_SUMA, T_INVALID},
  	{ Quadruple::I_RESTA, T_INVALID},
  	{ Quadruple::I_DIV, T_INVALID},
  	{ Quadruple::I_MULT, T_INVALID}	
  };

  dimThree doubleString = {
  	{ Quadruple::I_SUMA, T_CHAR},
  	{ Quadruple::I_RESTA, T_CHAR},
  	{ Quadruple::I_DIV, T_CHAR},
  	{ Quadruple::I_MULT, T_CHAR},
    { Quadruple::I_MAYOR_QUE, T_INVALID},
    { Quadruple::I_MENOR_IGUAL_QUE, T_INVALID},
    { Quadruple::I_MENOR_QUE, T_INVALID},
    { Quadruple::I_MENOR_IGUAL_QUE, T_INVALID},
    { Quadruple::I_NO_IGUAL, T_INVALID},
    { Quadruple::I_IGUAL, T_INVALID}
  };

  //string
  dimThree stringInt = {
  	{ Quadruple::I_SUMA, T_CHAR},
  	{ Quadruple::I_RESTA, T_CHAR},
  	{ Quadruple::I_DIV, T_CHAR},
  	{ Quadruple::I_MULT, T_CHAR},
    { Quadruple::I_MAYOR_QUE, T_INVALID},
    { Quadruple::I_MENOR_IGUAL_QUE, T_INVALID},
    { Quadruple::I_MENOR_QUE, T_INVALID},
    { Quadruple::I_MENOR_IGUAL_QUE, T_INVALID},
    { Quadruple::I_NO_IGUAL, T_INVALID},
    { Quadruple::I_IGUAL, T_INVALID}
  };

  dimThree stringDouble = {
  	{ Quadruple::I_SUMA, T_CHAR},
  	{ Quadruple::I_RESTA, T_CHAR},
  	{ Quadruple::I_DIV, T_CHAR},
  	{ Quadruple::I_MULT, T_CHAR},
    { Quadruple::I_MAYOR_QUE, T_INVALID},
    { Quadruple::I_MENOR_IGUAL_QUE, T_INVALID},
    { Quadruple::I_MENOR_QUE, T_INVALID},
    { Quadruple::I_MENOR_IGUAL_QUE, T_INVALID},
    { Quadruple::I_NO_IGUAL, T_INVALID},
    { Quadruple::I_IGUAL, T_INVALID}
  };

  dimThree stringBool = {
  	{ Quadruple::I_SUMA, T_INVALID},
  	{ Quadruple::I_RESTA, T_INVALID},
  	{ Quadruple::I_DIV, T_INVALID},
  	{ Quadruple::I_MULT, T_INVALID}	
  };

  dimThree stringString = {
  	{ Quadruple::I_SUMA, T_CHAR},
  	{ Quadruple::I_RESTA, T_CHAR},
  	{ Quadruple::I_DIV, T_CHAR},
  	{ Quadruple::I_MULT, T_CHAR},
    { Quadruple::I_MAYOR_QUE, T_BOOL},
    { Quadruple::I_MENOR_IGUAL_QUE, T_BOOL},
    { Quadruple::I_MENOR_QUE, T_BOOL},
    { Quadruple::I_MENOR_IGUAL_QUE, T_BOOL},
    { Quadruple::I_NO_IGUAL, T_BOOL},
    { Quadruple::I_IGUAL, T_BOOL}
  };

  //bool

  dimThree boolInt = {
  	{ Quadruple::I_SUMA, T_INVALID},
  	{ Quadruple::I_RESTA, T_INVALID},
  	{ Quadruple::I_DIV, T_INVALID},
  	{ Quadruple::I_MULT, T_INVALID}
  };

  dimThree boolDouble = {
  	{ Quadruple::I_SUMA, T_INVALID},
  	{ Quadruple::I_RESTA, T_INVALID},
  	{ Quadruple::I_DIV, T_INVALID},
  	{ Quadruple::I_MULT, T_INVALID}
  };

  dimThree boolBool = {
  	{ Quadruple::I_SUMA, T_INVALID},
  	{ Quadruple::I_RESTA, T_INVALID},
  	{ Quadruple::I_DIV, T_INVALID},
  	{ Quadruple::I_MULT, T_INVALID},
    { Quadruple::I_MAYOR_QUE, T_INVALID},
    { Quadruple::I_MENOR_IGUAL_QUE, T_INVALID},
    { Quadruple::I_MENOR_QUE, T_INVALID},
    { Quadruple::I_MENOR_IGUAL_QUE, T_INVALID},
    { Quadruple::I_NO_IGUAL, T_INVALID},
    { Quadruple::I_IGUAL, T_INVALID}
  };

  dimThree boolString = {
  	{ Quadruple::I_SUMA, T_INVALID},
  	{ Quadruple::I_RESTA, T_INVALID},
  	{ Quadruple::I_DIV, T_INVALID},
  	{ Quadruple::I_MULT, T_INVALID}
  };



  dimTwo intDim = {
  	{T_ENTERO, intInt},
  	{T_REAL, intDouble},
  	{T_BOOL, intBool},
  	{T_CHAR, intString}
  };

  dimTwo doubleDim = {
  	{T_ENTERO, doubleInt},
  	{T_REAL, doubleDouble},
  	{T_BOOL, doubleBool},
  	{T_CHAR, doubleString}
  };

  dimTwo boolDim = {
  	{T_ENTERO, boolInt},
  	{T_REAL, boolDouble},
  	{T_BOOL, boolBool},
  	{T_CHAR, boolString}
  };

  dimTwo stringDim = {
  	{T_ENTERO, stringInt},
  	{T_REAL, stringDouble},
  	{T_BOOL, stringBool},
  	{T_CHAR, stringString}
  };


   dimOne matrix = {
  	{T_ENTERO, intDim},
  	{T_REAL, doubleDim},
  	{T_BOOL, boolDim},
  	{T_CHAR, stringDim}
  };
};
#endif