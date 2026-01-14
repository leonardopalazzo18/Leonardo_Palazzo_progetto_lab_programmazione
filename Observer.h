//
// Created by palaz on 14/01/2026.
//

#ifndef PROGETTO_NOTECOLLECTION_LAB_LEONARDO_PALAZZO_OBSERVER_H
#define PROGETTO_NOTECOLLECTION_LAB_LEONARDO_PALAZZO_OBSERVER_H
//nche questa classe puramente astratta (il contatore sarà la derivata concreta che ne implementa i metodi virt)
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update() = 0;
};
#endif //PROGETTO_NOTECOLLECTION_LAB_LEONARDO_PALAZZO_OBSERVER_H