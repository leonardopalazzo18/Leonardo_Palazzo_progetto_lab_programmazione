//
// Created by palaz on 17/01/2026.
//

#include <gtest/gtest.h>
#include "../Nota.h"


TEST(NotaTest, Costruttore) {
    Nota n("Titolo", "Testo", "Collezione");

    EXPECT_EQ(n.getTitle(),"Titolo" );
    EXPECT_EQ(n.getText(),"Testo");
    EXPECT_EQ(n.getCollectionName(), "Collezione");
    EXPECT_FALSE(n.isLocked());
    EXPECT_FALSE(n.isImportant());
}

// Test setter e getter del titolo
TEST(NotaTest, SetGetTitle) {
    Nota n("Titolo1", "Testo1", "Collezione1");
    n.setTitle("Titolo2");

    EXPECT_EQ(n.getTitle(), "Titolo2");
}

// Test setter e getter del testo
TEST(NotaTest, SetGetText) {
    Nota n("Titolo1", "Testo1", "Collezione1");
    n.setText("Testo2");

    EXPECT_EQ(n.getText(), "Testo2");
}

// Test setter e getter del nome collezione
TEST(NotaTest, SetGetCollectionName) {
    Nota n("Titolo1", "Testo1", "Collezione1");
    n.setCollectionName("Collezione2");

    EXPECT_EQ(n.getCollectionName(), "Collezione2");
}

// Test lock della nota
TEST(NotaTest, NotaLocked) {
    Nota n("Titolo", "Testo", "Collezione");

    n.setLocked(true);
    n.setTitle("Titolo Modificato");
    n.setText("Testo Modificato");

    // Titolo e testo NON devono cambiare
    EXPECT_EQ(n.getTitle(), "Titolo");
    EXPECT_EQ(n.getText(), "Testo");
    EXPECT_TRUE(n.isLocked());
}

// Test unlock della nota
TEST(NotaTest, Locked) {
    Nota n("Titolo", "Testo", "Collezione");

    n.setLocked(true);
    n.setLocked(false);
    n.setTitle("Titolo Modificato");
    n.setText("Testo Modificato");

    EXPECT_EQ(n.getTitle(), "Titolo Modificato");
    EXPECT_EQ(n.getText(), "Testo Modificato");
}

// Test Importanza
TEST(NotaTest, SetImportant) {
    Nota n("Titolo", "Testo", "Collezione");

    n.setImportant(true);
    EXPECT_TRUE(n.isImportant());

    n.setImportant(false);
    EXPECT_FALSE(n.isImportant());
}