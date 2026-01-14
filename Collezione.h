//
// Created by palaz on 14/01/2026.
//

#ifndef PROGETTO_NOTECOLLECTION_LAB_LEONARDO_PALAZZO_COLLEZIONE_H
#define PROGETTO_NOTECOLLECTION_LAB_LEONARDO_PALAZZO_COLLEZIONE_H
#include "Subject.h"
#include "Nota.h"
#include "Observer.h"
#include <string>
#include <list>
#include <memory>


class Collezione : public Subject
{
public:
    explicit Collezione(const std::string& name);
    std::string getName() const;
    void addNote(std::shared_ptr<Nota>& note);
    void removeNote(std::shared_ptr<Nota>& note);
    void viewspecificNote(const std::string& notetitle);
    void viewAllNotes() const;


    void addObserver(Observer* obs) override;
    void removeObserver(Observer * obs)override;
    void notify(Action a) override;

private:
    std::string name;
    std::list<std::shared_ptr<Nota>> notes;
    std::list<Observer*> observers;
};


#endif //PROGETTO_NOTECOLLECTION_LAB_LEONARDO_PALAZZO_COLLEZIONE_H
