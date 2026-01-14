//
// Created by palaz on 14/01/2026.
//
#include "Subject.h"
#include "Collezione.h"
#include "Nota.h"
#include "Observer.h"
#include <string>
#include <list>
#include <memory>
#include <iostream>
#include <algorithm>



Collezione::Collezione(const std::string& name):name(name){}

std::string Collezione::getName() const {return name;}

void Collezione::addNote(std::shared_ptr<Nota>& note){
    if (note == nullptr)
    {
        std::cout << "errore, nessuna nota inserita" << std::endl;
    }
    else  if (!note->getTitle().empty() && note->getTitle() == getName())
    {
        std::cout<< "La nota è già presente in questa collezione!" <<std::endl;
    }
    else if (!note->getTitle().empty() && note->getTitle() != getName())
    {
        std::cout<<"La nota è già in un'altra collezione e si trova in: " << note->getTitle() <<std::endl;
    }
    else
    {
        notes.push_back(note);
        note->setCollectionName(getName());
        notify(Action::increment);
        std::cout<<"La nota è stata aggiunta alla collezione "<<getName() <<std::endl;

    }
}

void Collezione::removeNote(std::shared_ptr<Nota>& note){
    auto it = std::find(notes.begin(), notes.end(), note);
    if (it == notes.end()) {
        std::cout << " La nota non è presente nella collezione "<< getName()<<std::endl;
    }
    else if ((*it)->isLocked()) {
        std::cout << "Impossibile rimuovere la nota perchè è BLOCCATA" << std::endl;
    }
    else {
        notes.erase(it);
        note->setCollectionName("");
        notify(Action::decrement);
        std::cout << "La nota è stata rimossa dalla collezione "<< getName() <<std::endl;
    }
}


void Collezione::viewspecificNote(const std::string& notetitle){
    bool found = false;
    for (const auto& it : notes)
    {
        if (it->getTitle()  == notetitle)
        {
            it->viewNote();
            found = true;
            break;
        }
    }
    if (found)
        std::cout<<"La nota con titolo "<< notetitle<<" non è stata trovata nella collezione "<<getName()<<std::endl;
}

void Collezione::viewAllNotes() const{
    int n=1;
    for (const auto&  it : notes) {
        std::cout << "[" <<n<< "] ";
        it->viewNote();
        n+=1;
    }
}

void Collezione::addObserver(Observer* o) {
    observers.push_back(o);
}

void Collezione::removeObserver(Observer* o) {
    observers.remove(o);
}


void Collezione::notify(Action a){
    for ( auto it : notes)
    {
        it->update(a);
    }
}
