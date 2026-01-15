//
// Created by palaz on 14/01/2026.
//
#include <string>
#include "Nota.h"
#include <iostream>

Nota::Nota(const std::string& tit, const std::string& txt, const std::string& c): title(tit), text(txt), collectionName(c), locked (false), important(false){ }

std::string Nota::getTitle() const{
    return title;
}

std::string Nota::getText() const{
    return text;
}

std::string Nota::getCollectionName() const{
    return collectionName;
}

bool Nota::isLocked() const{
    return locked;
}

bool Nota::isImportant() const{
    return important;
}

void Nota::viewNote() const{
    std::cout << "TITOLO: " << title << std::endl;
    std::cout << "COLLEZIONE: " << collectionName << std::endl;
    std::cout << "BLOCCATA: " << (locked ? "SI" : "NO") << std::endl;
    std::cout << "IMPORTANTE: " <<(important ? "SI" : "NO") << std::endl;
    std::cout << "TESTO: " << text << "\n" << std::endl;
}

void Nota::setTitle(const std::string &newTitle) {
    if (!isLocked())
        title = newTitle;
}

void Nota::setText(const std::string &newText) {
    if (!isLocked())
        text = newText;
}

void Nota::setCollectionName(const std::string &newCollectionName) {
    collectionName = newCollectionName;
}

void Nota::setLocked(bool l) {
    locked = l;
}

void Nota::setImportant(bool I) {
    important = I;
}

