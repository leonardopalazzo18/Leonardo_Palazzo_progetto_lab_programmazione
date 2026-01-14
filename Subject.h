//
// Created by palaz on 14/01/2026.
//

#ifndef PROGETTO_NOTECOLLECTION_LAB_LEONARDO_PALAZZO_SUBJECT_H
#define PROGETTO_NOTECOLLECTION_LAB_LEONARDO_PALAZZO_SUBJECT_H
#include "Observer.h"

//enumerazione di azioni da passare nel notify e a sua volta nell'update del concrete observer
//per poter distinguere quando incrementare o decrementare il conteggio di note in una collezione
enum class Action{increment,decrement};

//classe base puramente atratta con metodi puramente virtuali da sovrascrivere nelle derivate concrete
class Subject
{
public:
    virtual ~Subject() = default; //distruttore virtuale default
    virtual void addObserver(Observer* o) = 0;
    virtual void removeObserver(Observer* o) = 0;
    virtual void notify(Action a ) = 0;
};

#endif //PROGETTO_NOTECOLLECTION_LAB_LEONARDO_PALAZZO_SUBJECT_H