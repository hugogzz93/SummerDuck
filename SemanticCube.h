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

private:

  //int
  dimThree intInt = {
  	{ Quadruple::I_SUMA, Quadruple::T_ENTERO},
  	{ Quadruple::I_RESTA, Quadruple::T_ENTERO},
  	{ Quadruple::I_DIV, Quadruple::T_ENTERO},
  	{ Quadruple::I_MULT, Quadruple::T_ENTERO},
    { Quadruple::I_MAYOR_QUE, Quadruple::T_BOOL},
    { Quadruple::I_MENOR_IGUAL_QUE, Quadruple::T_BOOL},
    { Quadruple::I_MENOR_QUE, Quadruple::T_BOOL},
    { Quadruple::I_MENOR_IGUAL_QUE, Quadruple::T_BOOL},
    { Quadruple::I_NO_IGUAL, Quadruple::T_BOOL},
    { Quadruple::I_IGUAL, Quadruple::T_BOOL}
  };

  dimThree intDouble = {
  	{ Quadruple::I_SUMA, Quadruple::T_REAL},
  	{ Quadruple::I_RESTA, Quadruple::T_REAL},
  	{ Quadruple::I_DIV, Quadruple::T_REAL},
  	{ Quadruple::I_MULT, Quadruple::T_REAL},
    { Quadruple::I_MAYOR_QUE, Quadruple::T_BOOL},
    { Quadruple::I_MENOR_IGUAL_QUE, Quadruple::T_BOOL},
    { Quadruple::I_MENOR_QUE, Quadruple::T_BOOL},
    { Quadruple::I_MENOR_IGUAL_QUE, Quadruple::T_BOOL},
    { Quadruple::I_NO_IGUAL, Quadruple::T_BOOL},
    { Quadruple::I_IGUAL, Quadruple::T_BOOL}
  };

  dimThree intBool = {
  	{ Quadruple::I_SUMA, Quadruple::T_INVALID},
  	{ Quadruple::I_RESTA, Quadruple::T_INVALID},
  	{ Quadruple::I_DIV, Quadruple::T_INVALID},
  	{ Quadruple::I_MULT, Quadruple::T_INVALID}	
  };

  dimThree intString = {
  	{ Quadruple::I_SUMA, Quadruple::T_CHAR},
  	{ Quadruple::I_RESTA, Quadruple::T_CHAR},
  	{ Quadruple::I_DIV, Quadruple::T_CHAR},
  	{ Quadruple::I_MULT, Quadruple::T_CHAR},
    { Quadruple::I_MAYOR_QUE, Quadruple::T_INVALID},
    { Quadruple::I_MENOR_IGUAL_QUE, Quadruple::T_INVALID},
    { Quadruple::I_MENOR_QUE, Quadruple::T_INVALID},
    { Quadruple::I_MENOR_IGUAL_QUE, Quadruple::T_INVALID},
    { Quadruple::I_NO_IGUAL, Quadruple::T_INVALID},
    { Quadruple::I_IGUAL, Quadruple::T_INVALID}
  };

  //double

  dimThree doubleInt = {
  	{ Quadruple::I_SUMA, Quadruple::T_REAL},
  	{ Quadruple::I_RESTA, Quadruple::T_REAL},
  	{ Quadruple::I_DIV, Quadruple::T_REAL},
  	{ Quadruple::I_MULT, Quadruple::T_REAL},
    { Quadruple::I_MAYOR_QUE, Quadruple::T_BOOL},
    { Quadruple::I_MENOR_IGUAL_QUE, Quadruple::T_BOOL},
    { Quadruple::I_MENOR_QUE, Quadruple::T_BOOL},
    { Quadruple::I_MENOR_IGUAL_QUE, Quadruple::T_BOOL},
    { Quadruple::I_NO_IGUAL, Quadruple::T_BOOL},
    { Quadruple::I_IGUAL, Quadruple::T_BOOL}
  };

  dimThree doubleDouble = {
  	{ Quadruple::I_SUMA, Quadruple::T_REAL},
  	{ Quadruple::I_RESTA, Quadruple::T_REAL},
  	{ Quadruple::I_DIV, Quadruple::T_REAL},
  	{ Quadruple::I_MULT, Quadruple::T_REAL},
    { Quadruple::I_MAYOR_QUE, Quadruple::T_BOOL},
    { Quadruple::I_MENOR_IGUAL_QUE, Quadruple::T_BOOL},
    { Quadruple::I_MENOR_QUE, Quadruple::T_BOOL},
    { Quadruple::I_MENOR_IGUAL_QUE, Quadruple::T_BOOL},
    { Quadruple::I_NO_IGUAL, Quadruple::T_BOOL},
    { Quadruple::I_IGUAL, Quadruple::T_BOOL}
  };

  dimThree doubleBool = {
  	{ Quadruple::I_SUMA, Quadruple::T_INVALID},
  	{ Quadruple::I_RESTA, Quadruple::T_INVALID},
  	{ Quadruple::I_DIV, Quadruple::T_INVALID},
  	{ Quadruple::I_MULT, Quadruple::T_INVALID}	
  };

  dimThree doubleString = {
  	{ Quadruple::I_SUMA, Quadruple::T_CHAR},
  	{ Quadruple::I_RESTA, Quadruple::T_CHAR},
  	{ Quadruple::I_DIV, Quadruple::T_CHAR},
  	{ Quadruple::I_MULT, Quadruple::T_CHAR},
    { Quadruple::I_MAYOR_QUE, Quadruple::T_INVALID},
    { Quadruple::I_MENOR_IGUAL_QUE, Quadruple::T_INVALID},
    { Quadruple::I_MENOR_QUE, Quadruple::T_INVALID},
    { Quadruple::I_MENOR_IGUAL_QUE, Quadruple::T_INVALID},
    { Quadruple::I_NO_IGUAL, Quadruple::T_INVALID},
    { Quadruple::I_IGUAL, Quadruple::T_INVALID}
  };

  //string
  dimThree stringInt = {
  	{ Quadruple::I_SUMA, Quadruple::T_CHAR},
  	{ Quadruple::I_RESTA, Quadruple::T_CHAR},
  	{ Quadruple::I_DIV, Quadruple::T_CHAR},
  	{ Quadruple::I_MULT, Quadruple::T_CHAR},
    { Quadruple::I_MAYOR_QUE, Quadruple::T_INVALID},
    { Quadruple::I_MENOR_IGUAL_QUE, Quadruple::T_INVALID},
    { Quadruple::I_MENOR_QUE, Quadruple::T_INVALID},
    { Quadruple::I_MENOR_IGUAL_QUE, Quadruple::T_INVALID},
    { Quadruple::I_NO_IGUAL, Quadruple::T_INVALID},
    { Quadruple::I_IGUAL, Quadruple::T_INVALID}
  };

  dimThree stringDouble = {
  	{ Quadruple::I_SUMA, Quadruple::T_CHAR},
  	{ Quadruple::I_RESTA, Quadruple::T_CHAR},
  	{ Quadruple::I_DIV, Quadruple::T_CHAR},
  	{ Quadruple::I_MULT, Quadruple::T_CHAR},
    { Quadruple::I_MAYOR_QUE, Quadruple::T_INVALID},
    { Quadruple::I_MENOR_IGUAL_QUE, Quadruple::T_INVALID},
    { Quadruple::I_MENOR_QUE, Quadruple::T_INVALID},
    { Quadruple::I_MENOR_IGUAL_QUE, Quadruple::T_INVALID},
    { Quadruple::I_NO_IGUAL, Quadruple::T_INVALID},
    { Quadruple::I_IGUAL, Quadruple::T_INVALID}
  };

  dimThree stringBool = {
  	{ Quadruple::I_SUMA, Quadruple::T_INVALID},
  	{ Quadruple::I_RESTA, Quadruple::T_INVALID},
  	{ Quadruple::I_DIV, Quadruple::T_INVALID},
  	{ Quadruple::I_MULT, Quadruple::T_INVALID}	
  };

  dimThree stringString = {
  	{ Quadruple::I_SUMA, Quadruple::T_CHAR},
  	{ Quadruple::I_RESTA, Quadruple::T_CHAR},
  	{ Quadruple::I_DIV, Quadruple::T_CHAR},
  	{ Quadruple::I_MULT, Quadruple::T_CHAR},
    { Quadruple::I_MAYOR_QUE, Quadruple::T_BOOL},
    { Quadruple::I_MENOR_IGUAL_QUE, Quadruple::T_BOOL},
    { Quadruple::I_MENOR_QUE, Quadruple::T_BOOL},
    { Quadruple::I_MENOR_IGUAL_QUE, Quadruple::T_BOOL},
    { Quadruple::I_NO_IGUAL, Quadruple::T_BOOL},
    { Quadruple::I_IGUAL, Quadruple::T_BOOL}
  };

  //bool

  dimThree boolInt = {
  	{ Quadruple::I_SUMA, Quadruple::T_INVALID},
  	{ Quadruple::I_RESTA, Quadruple::T_INVALID},
  	{ Quadruple::I_DIV, Quadruple::T_INVALID},
  	{ Quadruple::I_MULT, Quadruple::T_INVALID}
  };

  dimThree boolDouble = {
  	{ Quadruple::I_SUMA, Quadruple::T_INVALID},
  	{ Quadruple::I_RESTA, Quadruple::T_INVALID},
  	{ Quadruple::I_DIV, Quadruple::T_INVALID},
  	{ Quadruple::I_MULT, Quadruple::T_INVALID}
  };

  dimThree boolBool = {
  	{ Quadruple::I_SUMA, Quadruple::T_INVALID},
  	{ Quadruple::I_RESTA, Quadruple::T_INVALID},
  	{ Quadruple::I_DIV, Quadruple::T_INVALID},
  	{ Quadruple::I_MULT, Quadruple::T_INVALID},
    { Quadruple::I_MAYOR_QUE, Quadruple::T_INVALID},
    { Quadruple::I_MENOR_IGUAL_QUE, Quadruple::T_INVALID},
    { Quadruple::I_MENOR_QUE, Quadruple::T_INVALID},
    { Quadruple::I_MENOR_IGUAL_QUE, Quadruple::T_INVALID},
    { Quadruple::I_NO_IGUAL, Quadruple::T_INVALID},
    { Quadruple::I_IGUAL, Quadruple::T_INVALID}
  };

  dimThree boolString = {
  	{ Quadruple::I_SUMA, Quadruple::T_INVALID},
  	{ Quadruple::I_RESTA, Quadruple::T_INVALID},
  	{ Quadruple::I_DIV, Quadruple::T_INVALID},
  	{ Quadruple::I_MULT, Quadruple::T_INVALID}
  };



  dimTwo intDim = {
  	{Quadruple::T_ENTERO, intInt},
  	{Quadruple::T_REAL, intDouble},
  	{Quadruple::T_BOOL, intBool},
  	{Quadruple::T_CHAR, intString}
  };

  dimTwo doubleDim = {
  	{Quadruple::T_ENTERO, doubleInt},
  	{Quadruple::T_REAL, doubleDouble},
  	{Quadruple::T_BOOL, doubleBool},
  	{Quadruple::T_CHAR, doubleString}
  };

  dimTwo boolDim = {
  	{Quadruple::T_ENTERO, boolInt},
  	{Quadruple::T_REAL, boolDouble},
  	{Quadruple::T_BOOL, boolBool},
  	{Quadruple::T_CHAR, boolString}
  };

  dimTwo stringDim = {
  	{Quadruple::T_ENTERO, stringInt},
  	{Quadruple::T_REAL, stringDouble},
  	{Quadruple::T_BOOL, stringBool},
  	{Quadruple::T_CHAR, stringString}
  };


   dimOne matrix = {
  	{Quadruple::T_ENTERO, intDim},
  	{Quadruple::T_REAL, doubleDim},
  	{Quadruple::T_BOOL, boolDim},
  	{Quadruple::T_CHAR, stringDim}
  };
};
#endif