//
// Created by palaz on 17/01/2026.
//
#include "../Collezione.h"
#include "../Nota.h"
#include <gtest/gtest.h>

#include "../ObserverCounter.h"

TEST(CollezioneTest, Costruttore)
{
    Collezione c("Nome");
    EXPECT_EQ(c.getName(),"Nome");
}

TEST (CollezioneTest, addNote)
{
    Collezione c("Nome");
    Collezione i("IMPORTANTI");
    auto n = std::make_shared<Nota>("Titolo","Testo");
    ObserverCounter cont (&c);
    c.addNote(n);
    i.addNote(n);
    EXPECT_EQ(n->getCollectionName(),"Nome");
    EXPECT_EQ(cont.getCounter(),1);
    EXPECT_TRUE(n->isImportant());
}

TEST (CollezioneTest, removeNote)
{
    Collezione c("Nome");
    Collezione i("IMPORTANTI");
    auto n = std::make_shared<Nota>("Titolo","Testo");
    ObserverCounter cont (&c);
    c.addNote(n);
    i.addNote(n);

    c.removeNote(n);
    i.removeNote(n);
    EXPECT_EQ(n->getCollectionName(),"");
    EXPECT_EQ(cont.getCounter(),0);
    EXPECT_FALSE(n->isImportant());

}