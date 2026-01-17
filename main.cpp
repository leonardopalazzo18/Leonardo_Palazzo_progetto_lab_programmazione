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
    std::cout<<"[2] Crea una collezione"<<std::endl;
    std::cout<<"[3] Elimina una nota o una collezione"<<std::endl;
    std::cout<<"[4] Blocca/Sblocca una nota"<<std::endl;
    std::cout<<"[5] Aggiungi/Rimuovi una nota da una collezione"<<std::endl;
    std::cout<<"[6] Visualizza le note di una collezione"<<std::endl;
    std::cout<<"[7] Visualizza tutte le note"<<std::endl;
    std::cout<<"[8] Visualizza tutte le collezioni"<<std::endl;
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
    else
        std::cout<<"Non ci sono note! "<<"\n"<<std::endl;
}

int selectNote(const std::vector<std::shared_ptr<Nota>>& notes) {
    if (notes.empty()) {
        std::cout << "Non ci sono note! "<<"\n" << std::endl;
        return -1;
    }
    viewNotes(notes);
    int n;
    do
    {
        std::cout << "Seleziona il numero della nota: ";
        std::cin>>n;
        if (n < 0 || n >= notes.size()) {
            std::cout << "Inserisci un numero valido"<<"\n" << std::endl;
        }
    }while (n < 0 || n >= notes.size());
    return n;
}

void viewCollections(const std::vector<std::shared_ptr<Collezione>>& collections, const std::vector<ObserverCounter*>& counters)
{
    std::cout<<"       COLLEZIONI:       "<<std::endl;
    for (int i = 0; i < collections.size(); ++i) {
        std::cout << "["<<i<<"]" << collections[i]->getName()<<" {"<<counters[i]->getCounter()<<" note}"<<std::endl;
    }
    std::cout<<"\n";
}


int selectCollection(const std::vector<std::shared_ptr<Collezione>>& collections,const std::vector<ObserverCounter*>& counters) {
    viewCollections(collections,counters);
    int n;
    do
    {
        std::cout << "Seleziona il numero della collezione: ";
        std::cin>>n;
        if (n < 0 || n >= collections.size()) {
            std::cout << "Inserisci un numero valido"<<"\n" << std::endl;
        }
    }while (n < 0 || n >= collections.size());
    return n;
}

int main()
{
    std::vector<std::shared_ptr<Nota>> AllNotes;
    std::vector<std::shared_ptr<Collezione>> AllCollections;
    std::vector<ObserverCounter*> AllCounters;

    //Creo subito la collezione importanti e il suo shraed_ptr
    auto Importanti = std::make_shared<Collezione>("IMPORTANTI");

    //La aggiungo alla lista delle collezioni
    AllCollections.push_back(Importanti);

    // creo un contatore che osserva la collezione delle importanti ma per crearlo devo passare
    //un puntatore grezzo e non uno shared quindi applico ad Importanti il metodo get().
    //così passo lo shared_ptre come grezzo.
    auto ImpCounter = new ObserverCounter(Importanti.get());
    AllCounters.push_back(ImpCounter); // lo aggiungo alla lista dei contatori in posizione 0 uguale alla posizione delle note importanti


    int choice;
    do
    {
        viewMenù();
        std::cin >> choice;
        if (choice<0 or choice > 9)
        {
            std::cout<<"Per favore inserire un comando corretto"<<"\n"<<std::endl;
            continue; //riparte il ciclo e rimostra il menù
        }
        switch (choice)
        {
        case 0: //CHIUDI IL PROGRAMMA
            {
                std::cout<<"Arrivederci!"<<"\n"<<std::endl;
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
                std::cout<<"La nota e stata creata!"<<"\n"<<std::endl;
                break;
            }
        case 2: //CREA UNA COLLEZIONE
            {
                std::string n;
                std::cout<<"Inserisci il nome della collezione: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, n);
                auto newCollection = std::make_shared<Collezione>(n);
                AllCollections.push_back(newCollection);
                auto newCounter = new ObserverCounter (newCollection.get());
                AllCounters.push_back(newCounter);
                std::cout<<"La collezione e stata creata!"<<"\n"<<std::endl;
                break;
            }
        case 3: //ELIMINA UNA NOTA O UNA COLLEZIONE
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
                        std::cout<<"Per favore inserire un comando corretto"<<"\n"<<std::endl;
                        continue; //riparte da scelta2 e mostra di nuovo le opzioni di elimnazione
                    }
                    switch (choice2)
                    {
                        case 0:
                            {
                                std::cout<<"Sarai reindirizzato al menu"<<"\n"<<std::endl;
                                break;
                            }
                        case 1:
                            {
                                int eliminated = selectNote(AllNotes);
                                if (eliminated == -1)
                                    break;
                                AllNotes.erase(AllNotes.begin()+eliminated);
                                std::cout<<"La nota e' stata eliminata"<<"\n"<<std::endl;
                                break;
                            }
                        case 2:
                            {
                                //prendo il numero della collezione da eliminare ma evito che venga eliminata la collezione 0 ovvero quella delle note importanti
                                int eliminated = selectCollection(AllCollections,AllCounters);
                                if (eliminated == -1)
                                    break;
                                if (eliminated == 0){
                                    std::cout<<"Non e' possibile eliminare la collezione IMPORTANTI"<<"\n"<<std::endl;
                                    break;
                                }
                                //ripristino l'attributo CollectionName di tutte le note che facevano parte della collezione eliminata
                                std::string eliminated_name = AllCollections[eliminated]->getName();
                                for (const auto& it: AllNotes)
                                {
                                    if (it->getCollectionName() == eliminated_name)
                                        it->setCollectionName("");
                                }
                                //elimino adesso sia la collezione che il suo contatore
                                AllCollections.erase(AllCollections.begin() + eliminated);
                                AllCounters.erase(AllCounters.begin() + eliminated);
                                std::cout<<"La collezione e stata eliminata"<<"\n"<<std::endl;
                                break;
                            }
                        default:
                                break;
                    }
                }while (choice2 != 0);
                break;
            }
        case 4: //BLOCCA/SBLOCCA UNA NOTA
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
                        std::cout<<"Per favore inserire un comando corretto"<<"\n"<<std::endl;
                        continue;
                    }
                    switch (choice3)
                    {
                        case 0:
                            {
                                std::cout<<"Sarai reindirizzato al menu"<<"\n"<<std::endl;
                                break;
                            }
                        case 1:
                            {
                                if (!AllNotes[selection]->isLocked())
                                {
                                    AllNotes[selection]->setLocked(true);
                                    std::cout<<"Nota BLOCCATA"<<"\n"<<std::endl;
                                }
                                else
                                    std::cout<<"La nota e'gia bloccata!"<<"\n"<<std::endl;
                                break;
                            }
                        case 2:
                            {
                                if (AllNotes[selection]->isLocked())
                                {
                                    AllNotes[selection]->setLocked(false);
                                    std::cout<<"Nota SBLOCCATA"<<"\n"<<std::endl;
                                }
                                else
                                    std::cout<<"La nota e'gia sbloccata!"<<"\n"<<std::endl;
                                break;
                            }
                        default:
                                break;
                    }
                }while (choice3 != 0);
                break;
            }
        case 5: //AGGIUNGI RIMUOVI UNA NOTA SCELTA DA UNA COLLEZIONE SCELTA
            {
                int noteselected = selectNote(AllNotes);
                if (noteselected == -1)
                    break;
                if (AllNotes[noteselected]->isLocked())
                {
                    std::cout<<"Nota bloccata, sbloccare prima! \n" <<std::endl;
                    break;
                }
                int choice4;
                do
                {
                    std::cout<<"[0] TORNA AL MENU"<<std::endl;
                    std::cout<<"[1] AGGIUNGI A"<<std::endl;
                    std::cout<<"[2] RIMUOVI DA" <<std::endl;
                    std::cout<<"cosa vuoi fare?: ";
                    std::cin>>choice4;
                    if (choice4<0 or choice4>2)
                    {
                        std::cout<<"Per favore inserire un comando corretto"<<"\n"<<std::endl;
                        continue;
                    }
                    switch (choice4)
                    {
                        case 0:
                            {
                                std::cout<<"Sarai reindirizzato al menu"<<"\n"<<std::endl;
                                break;
                            }
                        case 1:
                            {
                                //aggiungo la nota scelta alla collezione scelta (se possibile)
                                int collselected =  selectCollection(AllCollections,AllCounters);
                                if (collselected == 0 && AllNotes[noteselected]->isImportant())
                                    std::cout<<"La nota e' gia tra le note IMPORTANTI"<<std::endl;
                                else
                                {
                                    AllCollections[collselected]->addNote(AllNotes[noteselected]);
                                }
                                break;
                            }
                        case 2:
                            {
                                //rimuovo la nota scelta alla collezione scelta (se possibile)
                                int collselected =  selectCollection(AllCollections,AllCounters);
                                AllCollections[collselected]->removeNote(AllNotes[noteselected]);
                                break;
                            }
                        default:
                            break;
                    }
                }while (choice4 != 0);
                break;
            }
        case 6: //VISUALIZZA TUTTE LE NOTE DI UNA COLLEZIONE
            {
                int selection = selectCollection(AllCollections,AllCounters);
                AllCollections[selection]->viewAllNotes();
                break;
            }
        case 7: //VISUALIZZA TUTTE LE NOTE
            {
                viewNotes(AllNotes);
                break;
            }
        case 8: //VISUALIZZA TUTTE LE COLLEZIONI
            {
                viewCollections(AllCollections,AllCounters);
                break;
            }
        case 9: //MODIFICA TITOLO/TESTO DI UNA NOTA
            {
                int selection = selectNote(AllNotes);
                if (selection == -1)
                    break;
                if (AllNotes[selection]->isLocked())
                {
                    std::cout<<"Nota bloccata, sbloccare prima"<<"\n"<<std::endl;
                    break;
                }
                int choice5;
                do
                {
                    std::cout<<"[0] TORNA AL MENU"<<std::endl;
                    std::cout<<"[1] MODIFICA TITOLO"<<std::endl;
                    std::cout<<"[2] MODIFICA TESTO" <<std::endl;
                    std::cout<<"cosa vuoi fare?: ";
                    std::cin>>choice5;
                    if (choice5<0 or choice5>2)
                    {
                        std::cout<<"Per favore inserire un comando corretto"<<"\n"<<std::endl;
                        continue;
                    }
                    switch (choice5)
                    {
                        case 0:
                            {
                                std::cout<<"Sarai reindirizzato al menu"<<"\n"<<std::endl;
                                break;
                            }
                        case 1:
                            {
                                std::string newtitle;
                                std::cout<<"Inserisci il  nuovo titolo: ";
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                std::getline(std::cin, newtitle);
                                AllNotes[selection]->setTitle(newtitle);
                                break;
                            }
                        case 2:
                            {
                                std::string newtext;
                                std::cout<<"Inserisci il  nuovo testo: ";
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                std::getline(std::cin, newtext);
                                AllNotes[selection]->setText(newtext);
                                break;
                            }
                        default:
                            break;
                    }
                }while (choice5 != 0);
                break;
            }
        default:
                break;
        }
    }while (choice !=0);
    return 0;
}

