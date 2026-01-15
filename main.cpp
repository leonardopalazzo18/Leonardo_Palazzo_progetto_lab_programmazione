#include <iostream>
#include "Collezione.h"
#include "Nota.h"
#include "ObserverCounter.h"
#include <vector>
#include <memory>
#include <string>
#include <limits>



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
        int n=0;
        for (const auto&  it : AllNotes) {
            std::cout << "[" <<n<< "] ";
            it->viewNote();
            n+=1;
        }
    }
}

int selectNote(const std::vector<std::shared_ptr<Nota>>& notes) {
    if (notes.empty()) {
        std::cout << "Non ci sono note!" << std::endl;
        return -1;
    }
    viewNotes(notes);
    int n;
    do
    {
        std::cout << "Seleziona il numero della nota: ";
        std::cin>>n;
        if (n < 0 || n >= notes.size()) {
            std::cout << "Inserisci un numero valido" << std::endl;
        }
    }while (n < 0 || n >= notes.size());
    return n;
}


int selectCollection(const std::vector<std::shared_ptr<Collezione>>& collections) {
    if (collections.empty()) {
        std::cout <<"Non ci sono collezioni" << std::endl;
        return -1;
    }
    std::cout << "      COLLEZIONI      " << std::endl;
    for (int i = 0; i < collections.size(); ++i) {
        std::cout << "["<<i<<"]" << collections[i]->getName() << std::endl;
    }
    int n;
    do
    {
        std::cout << "Seleziona il numero della collezione: ";
        std::cin>>n;
        if (n < 0 || n >= collections.size()) {
            std::cout << "Inserisci un numero valido" << std::endl;
        }
    }while (n < 0 || n >= collections.size());
    return n;
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
        case 0: //CHIUDI IL PROGRAMMA
            {
                std::cout<<"Arrivederci!"<<std::endl;
                break;
            }
        case 1: //CREA UNA NOTA
            {
                std::string titolo;
                std::string testo;
                std::cout<<"Inserisci titolo della nota: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, titolo);
                std::cout<<"Inserisci testo: ";
                std::getline(std::cin,testo);
                auto newNota = std::make_shared<Nota>(titolo, testo);
                AllNotes.push_back(newNota);
                std::cout<<"La nota e stata creata!"<<std::endl;
                break;
            }
        case 2: //ELIMINA UNA NOTA O UNA COLLEZIONE
            {
                int choice2;
                do
                {
                    std::cout<<"[0] TORNA AL MENU"<<std::endl;
                    std::cout<<"[1] ELIMINA NOTA"<<std::endl;
                    std::cout<<"[2] ELIMINA COLLEZIONE: " <<std::endl;
                    std::cout<<"cosa vuoi fare?: ";
                    std::cin>>choice2;
                    if (choice2<0 or choice2 > 2)
                    {
                        std::cout<<"Per favore inserire un comando corretto"<<std::endl;
                        continue; //riparte da scelta2 e mostra di nuovo le opzioni di elimnazione
                    }
                    switch (choice2)
                    {
                        case 0:
                            {
                                std::cout<<"Sarai reindirizzato al menu"<<std::endl;
                                break;
                            }
                        case 1:
                            {
                                int eliminated = selectNote(AllNotes);
                                if (eliminated == -1)
                                    break;
                                AllNotes.erase(AllNotes.begin()+eliminated);
                                std::cout<<"La nota e' stata eliminata"<<std::endl;
                                break;
                            }
                        case 2:
                            {
                                //prendo il numero della collezione da eliminare ma evito che venga eliminata la collezione 0 ovvero quella delle note importanti
                                int eliminated = selectCollection(AllCollections);
                                if (eliminated == -1)
                                    break;
                                if (eliminated == 0){
                                    std::cout<<"Non e' possibile eliminare la collezione IMPORTANTI"<<std::endl;
                                    break;
                                }
                                //ripristino l'attributo CollectionName di tutte le note che facevano parte della collezione eliminata
                                std::string eliminated_name = AllCollections[eliminated]->getName();
                                for (const auto& it: AllNotes)
                                {
                                    if (it->getCollectionName() == eliminated_name)
                                        it->setCollectionName("");
                                }
                                AllCollections.erase(AllCollections.begin() + eliminated);
                                std::cout<<"La collezione e stata eliminata"<<std::endl;
                                break;
                            }
                        default:
                                break;
                    }
                }while (choice2 != 0);
            }
        case 3: //BLOCCA/SBLOCCA UNA NOTA
            {
                int selection = selectNote(AllNotes);
                if (selection == -1)
                    break;
                int choice3;
                do
                {
                    std::cout<<"[0] TORNA AL MENU"<<std::endl;
                    std::cout<<"[1] BLOCCA NOTA"<<std::endl;
                    std::cout<<"[2] SBLOCCA NOTA: " <<std::endl;
                    std::cout<<"cosa vuoi fare?: ";
                    std::cin>>choice3;
                    if (choice3<0 or choice3>2)
                    {
                        std::cout<<"Per favore inserire un comando corretto"<<std::endl;
                        continue; //riparte da scelta3 e mostra di nuovo le opzioni blocca/sblocca
                    }
                    switch (choice3)
                    {
                        case 0:
                            {
                                std::cout<<"Sarai reindirizzato al menu"<<std::endl;
                                break;
                            }
                        case 1:
                            {
                                if (!AllNotes[selection]->isLocked())
                                {
                                    AllNotes[selection]->setLocked(true);
                                    std::cout<<"Nota BLOCCATA"<<std::endl;
                                }
                                else
                                    std::cout<<"La nota e'gia bloccata!"<<std::endl;
                                break;
                            }
                        case 2:
                            {
                                if (AllNotes[selection]->isLocked())
                                {
                                    AllNotes[selection]->setLocked(false);
                                    std::cout<<"Nota SBLOCCATA"<<std::endl;
                                }
                                else
                                    std::cout<<"La nota e'gia sbloccata!"<<std::endl;
                                break;
                            }
                        default:
                                break;
                    }
                }while (choice3 != 0);
                break;
            }
            case 4: //IMPORTANZA NOTA
            {
                int selection = selectNote(AllNotes);
                if (selection == -1)
                    break;
                int choice3;
                do
                {
                    std::cout<<"[0] TORNA AL MENU"<<std::endl;
                    std::cout<<"[1] AGGIUNGI ALLE NOTE IMPORTANTI"<<std::endl;
                    std::cout<<"[2] RIMUOVI DALLE NOTE IMPORTANTI: " <<std::endl;
                    std::cout<<"cosa vuoi fare?: ";
                    std::cin>>choice3;
                    if (choice3<0 or choice3>2)
                    {
                        std::cout<<"Per favore inserire un comando corretto"<<std::endl;
                        continue; //riparte da scelta3 e mostra di nuovo le opzioni blocca/sblocca
                    }
                    switch (choice3)
                    {
                        case 0:
                            {
                                std::cout<<"Sarai reindirizzato al menu"<<std::endl;
                                break;
                            }
                        case 1:
                            {
                                if (!AllNotes[selection]->isImportant())
                                {
                                    AllCollections[0]->addNote(AllNotes[selection]);
                                    if (!AllNotes[selection]->isLocked())
                                        AllNotes[selection]->setImportant(true);
                                }
                                else
                                    std::cout<<"La nota e' gia tra le IMPORTANTI"<<std::endl;
                                break;
                            }
                        case 2:
                            {
                                if (AllNotes[selection]->isImportant())
                                {
                                    AllCollections[0]->removeNote(AllNotes[selection]);
                                    if (!AllNotes[selection]->isLocked())
                                        AllNotes[selection]->setImportant(false);
                                }
                                else
                                    std::cout<<"La nota non e' tra le note IMPORTANTI!"<<std::endl;
                                break;
                            }
                    default:
                        break;
                    }
                }while (choice3 != 0);
                break;
            }
            //todo casi 5-6-7-9 + test
        case 8: //VISUALIZZA TUTTE LE NOTE
            {
                viewNotes(AllNotes);
                break;
            }
        default:
                break;
        }
    }while (choice !=0);
    return 0;
}

