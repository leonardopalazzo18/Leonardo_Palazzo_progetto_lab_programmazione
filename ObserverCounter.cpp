//
// Created by palaz on 14/01/2026.
//
#include"Subject.h"
#include "ObserverCounter.h"

ObserverCounter::ObserverCounter(Collezione* c): collezione(c), counter(0)
{
    c->addObserver(this); // creo il collegamento tra concrete observer e subject concrete
}

void ObserverCounter::update(Action a)
{
    if ( a == Action::increment)
        counter++;
    else if ( a == Action::decrement)
        counter--;
}

int ObserverCounter::getCounter() const {return this->counter;}
