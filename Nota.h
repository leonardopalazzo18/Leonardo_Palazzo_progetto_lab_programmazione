//
// Created by palaz on 14/01/2026.
//

#ifndef PROGETTO_NOTECOLLECTION_LAB_LEONARDO_PALAZZO_NOTA_H
#define PROGETTO_NOTECOLLECTION_LAB_LEONARDO_PALAZZO_NOTA_H
#include <string>

class Nota
{
public:
    //costruttore con parametro di default sul nome dell'eventuale collezione
    Nota(const std::string& title, const std::string& text, const std::string& collectionName = "" );

    //metodi getter
    std::string getTitle() const;
    std::string getText() const;
    std::string getCollectionName() const;
    bool isLocked() const;
    bool isImportant() const;

    //metodo per visualizzazione della nota (titolo + testo)
    void viewNote() const;

    //metodi setter
    void setTitle(const std::string& newTitle);
    void setText(const std::string& newText);
    void setCollectionName(const std::string& newCollectionName);
    void setLocked(bool l);
    void setImportant(bool I);

private:
    //attributi della Nota
    std::string title;
    std::string text;
    std::string collectionName;
    bool locked;
    bool important;
};

#endif //PROGETTO_NOTECOLLECTION_LAB_LEONARDO_PALAZZO_NOTA_H