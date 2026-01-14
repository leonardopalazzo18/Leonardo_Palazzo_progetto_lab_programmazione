//
// Created by palaz on 14/01/2026.
//

#ifndef PROGETTO_NOTECOLLECTION_LAB_LEONARDO_PALAZZO_SUBJECT_H
#define PROGETTO_NOTECOLLECTION_LAB_LEONARDO_PALAZZO_SUBJECT_H
#include <list>
#include "Observer.h"

//classe base puramente atratta con metodi puramente virtuali da sovrascrivere nelle derivate concrete
class Subject
{
public:
    virtual ~Subject() = default; //distruttore virtuale default
    virtual void addObserver(Observer* o) = 0;
    virtual void removeObserver(Observer* o) = 0;
    virtual void notify() = 0;
protected:
    std::list <Observer*> observers;
};

#endif //PROGETTO_NOTECOLLECTION_LAB_LEONARDO_PALAZZO_SUBJECT_H