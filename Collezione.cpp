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

void Collezione::addNote(const std::shared_ptr<Nota>& note){
    if (note == nullptr)
    {
        std::cout << "errore, nessuna nota inserita \n" << std::endl;
    }
    else  if (!note->getCollectionName().empty() && note->getCollectionName() == getName())
    {
        std::cout<< "La nota e gia presente nella collezione "<<getName()<<"\n" <<std::endl;
    }
    else if (this->getName() == "IMPORTANTI")
    {
        notes.push_back(note);
        notify(Action::increment);
        std::cout<<"La nota e stata aggiunta alla collezione "<<getName() <<"\n"<< std::endl;
    }
    else if (!note->getCollectionName().empty() && note->getCollectionName() != getName())
    {
        std::cout<<"La nota e gia in un'altra collezione e si trova in: " << note->getCollectionName()<< "\n" <<std::endl;
    }
    else
    {
        notes.push_back(note);
        if (this->getName() != "IMPORTANTI")
            note->setCollectionName(getName());
        notify(Action::increment);
        std::cout<<"La nota e stata aggiunta alla collezione "<<getName() <<"\n"<< std::endl;

    }
}

void Collezione::removeNote(const std::shared_ptr<Nota>& note){
    auto it = std::find(notes.begin(), notes.end(), note);
    if (it == notes.end()) {
        std::cout << " La nota non e' presente nella collezione \n"<< getName()<<std::endl;
    }
    else {
        notes.erase(it);
        if (this->getName() != "IMPORTANTI")
            note->setCollectionName("");
        notify(Action::decrement);
        std::cout << "La nota e stata rimossa dalla collezione \n"<< getName() <<std::endl;
    }
}

void Collezione::viewAllNotes() const{
    if (!notes.empty())
    {
        int n=0;
        std::cout<<"La collezione "<<getName()<<" contiene le seguenti note: \n"<< std::endl;
        for (const auto&  it : notes) {
            std::cout << "[" <<n<< "] ";
            it->viewNote();
            n+=1;
        }
    }
    else
        std::cout<<"La collezione e' vuota \n"<<std::endl;
}

void Collezione::addObserver(Observer* o) {
    observers.push_back(o);
}

void Collezione::removeObserver(Observer* o) {
    observers.remove(o);
}


void Collezione::notify(Action a){
    for ( auto it : observers)
    {
        it->update(a);
    }
}
