//
// Created by palaz on 14/01/2026.
//

#ifndef PROGETTO_NOTECOLLECTION_LAB_LEONARDO_PALAZZO_OBSERVERCOUNTER_H
#define PROGETTO_NOTECOLLECTION_LAB_LEONARDO_PALAZZO_OBSERVERCOUNTER_H

#include "Observer.h"
#include "Collezione.h"

class ObserverCounter : public Observer {
public:
    explicit ObserverCounter(Collezione* c);
    void update(Action a) override;
private:
    Collezione* collezione;
    int counter;
};
#endif //PROGETTO_NOTECOLLECTION_LAB_LEONARDO_PALAZZO_OBSERVERCOUNTER_H