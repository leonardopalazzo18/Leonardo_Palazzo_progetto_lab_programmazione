#include <iostream>
#include "Collezione.h"
#include "Nota.h"
#include "ObserverCounter.h"
#include <vector>
#include <memory>
#include <string>



void viewMenù()
{
    std::cout<<"        NOTES MENU        "<<std::endl;
    std::cout<<"[0] Esci "<<std::endl;
    std::cout<<"[1] Crea una nuova Nota"<<std::endl;
    std::cout<<"[2] Elimina una nota o una collezione"<<std::endl;
    std::cout<<"[3] Blocca/Sblocca una nota"<<std::endl;
    std::cout<<"[4] Aggiungi/Rimuovi dalle note importanti"<<std::endl;
    std::cout<<"[5] Aggiungi/Rimuovi una nota da una collezione"<<std::endl;
    std::cout<<"[6] Visualizza una nota"<<std::endl;
    std::cout<<"[7] Visualizza una nota di una collezione"<<std::endl;
    std::cout<<"[8] Visualizza tutte le note"<<std::endl;
    std::cout<<"[9] Modifica testo/titolo di una nota" <<std::endl;
    std::cout<<"Cosa vuoi fare? ";

}

void viewNotes(const std::vector<std::shared_ptr<Nota>>& AllNotes)
{
    if (!AllNotes.empty()){
        std::cout<<"        NOTE:       "<<std::endl;
        int n=1;
        for (const auto&  it : AllNotes) {
            std::cout << "[" <<n<< "] ";
            it->viewNote();
            n+=1;
        }
    }
}



int main()
{
    std::vector<std::shared_ptr<Nota>> AllNotes;
    std::vector<std::shared_ptr<Collezione>> AllCollections;
    std::vector<ObserverCounter*> AllCounters;

    //Creo la collezione importanti e il suo shraed_ptr
    auto Importanti = std::make_shared<Collezione>("IMPORTANTI");

    //La aggiungo alla lista delle collezioni
    AllCollections.push_back(Importanti);

    // creo un contatore che osserava la collezione delle importanti ma per crearlo devo passare
    //un puntatore grezzo e non uno shared quindi applico ad Importanti il metodo get().
    //così passo lo shared_ptre come grezzo.
    auto ImpCounter = new ObserverCounter(Importanti.get());


    int choice;
    do
    {
        viewMenù();
        std::cin >> choice;
        if (choice<0 or choice > 9)
        {

            std::cout<<"Per favore inserire un comando corretto"<<std::endl;
            continue; //riparte il ciclo e rimostra il menù
        }
        switch (choice)
        {
            case 0:
                {
                    std::cout<<"Arrivederci!"<<std::endl;
                }
            case 1:
                {
                    std::string titolo;
                    std::string testo;
                    std::cout<<"Inserisci titolo della nota: ";
                    std::cin>>titolo;
                    std::cout<<"Inserisci testo: ";
                    std::cin>>testo;
                    auto newNota = std::make_shared<Nota>(titolo, testo);
                    AllNotes.push_back(newNota);
                    std::cout<<"La nota " << newNota->getTitle()<<" è stata creata"<<std::endl;
                    break;
            case 8:
                {
                    viewNotes(AllNotes);
                    break;
                }
            default:
                {
                    std::cout<<"Inserire un comando corretto"<<std::endl;
                    break;
                }
        }

    }while (choice !=0);

    return 0;
}