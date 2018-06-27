#pragma once

/*!
 * Erlaubt es zu messen, wie lange (in Sekunden) die Ausf�hrung einer Funktion/Methode oder 
 * eines Blockes ben�tigt.

 * Usage for global functions:
 * timeFunctionCall(&functionFoo, elapsedTime).function();
 *
 * For Member-Functions internal:
 * (this->*(timeFunctionCall(&ClassFoo::functionBar, elapsedTime).function))();
 *
 * For Member-Function external:
 * (objectFoo->*(timeFunctionCall(&ClassBar::functionBar, elapsedTime).function))(parameter); bzw.
 * (objectFoo.*(timeFunctionCall(&ClassBar::functionBar, elapsedTime.function))(parameter); wenn objectFoo auf dem Stack liegt.
 *
 * For Overloaded Member-Functions:
 * (objectFoo.*(timeFunctionCall<returnType (ClassBar::*)(parameter)>(&ClassBar::functionBar, elapsedTime).function))(parameter).
 * (timeFunctionCall has to be specialized with the Signature of the Method that should be timed.
 *
 * For BlockTiming:
 * double elapsedTime;
 * {
 *    BlockTimer timer(elapsedTime);
 *    // do what you want to time
 * }
 * std::cout << elapsedTime << "s" << std::endl;
 *
 *
 * Die Klasse misst, wie lange eine Objektinstanz existiert.
 * Da das Objekt nach Beenden der timeFunctionCall Methode zerst�rt wird,
 * entspricht dies der Ausf�hrungszeit der �bergebenen Methode.
 * Wenn eine Membermethode getimed werden soll, muss explizit angegeben werden,
 * zu welchem Objekt der Funktionspointer geh�rt, auf den zugegriffen werden muss.
 * Dies geschieht �ber die Ausdr�cke this->* bzw. objectFoo->* / objectFoo.* .
 *
 * timeFunctionCall gibt ein FunctionTimer Objekt zur�ck. Auf diesem kann die zu
 * timende Methode �ber den Member "function" aufgerufen werden. Somit kann normal
 * mit Parametern oder R�ckgabewerten gearbeitet werden.
 *
 * Wenn FunctionTimer mit <void *> spezialisiert wird (oder �ber den typedef BlockTimer),
 * kann auch Code getimed werden, welcher sich nicht in einer Methode befindet.
 * Dazu muss dieser Code lediglich von einem Block umschlossen werden, in welchem 
 * als erste Anweisung ein FunctionTimer-Objekt angelegt wird. Sobald der Block verlassen
 * wird, befindet sich in elapsedTime die Zeit, die zur Ausf�hrung ben�tigt wurde.
 //*/

#include <omp.h>

template <typename T>
class FunctionTimer
{
public:
	FunctionTimer(T function, double& time) : function(function), time(time), stop(0)
	{
		start = omp_get_wtime();
	}

	~FunctionTimer(){
		stop = omp_get_wtime();
		time = stop - start;
	}

	T function;

private:
	double &time, start, stop;
};

template<>
class FunctionTimer<void *>
{
public:
	FunctionTimer(double& time) : time(time), stop(0)
	{
		start = omp_get_wtime();
	}

	~FunctionTimer()
	{
		stop = omp_get_wtime();
		time = stop - start;
	}

private:
	double &time, start, stop;

};

typedef FunctionTimer<void *> BlockTimer;

template<typename T>
FunctionTimer<T> timeFunctionCall(T function, double& time)
{
	return FunctionTimer<T>(function, time);
}

#define TIME_THIS(x, elapsedTime) { \
	BlockTimer t(elapsedTime);      \
	do { x; } while(0);             \
}
