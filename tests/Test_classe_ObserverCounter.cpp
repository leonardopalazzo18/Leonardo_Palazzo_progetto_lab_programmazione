//
// Created by palaz on 17/01/2026.
//
#include <gtest/gtest.h>
#include "../ObserverCounter.h"

TEST(ObserverCounterTest, Costruttore)
{
    Collezione coll("Collezione");
    ObserverCounter Obs(&coll);
    EXPECT_EQ(Obs.getCounter(),0);
}

TEST(ObserverCounterTest, update)
{
    Collezione coll("Collezione");
    ObserverCounter Obs(&coll);
    auto n = std::make_shared<Nota>("Titolo","Testo");
    coll.addNote(n);
    EXPECT_EQ(Obs.getCounter(),1);
    coll.removeNote(n);
    EXPECT_EQ(Obs.getCounter(),0);
}
