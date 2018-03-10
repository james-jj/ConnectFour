//
//  GUI.cpp
//  ConnectFour
//
//  Created by James Johnstone on 05/08/2017.
//  Copyright © 2017 James Johnstone. All rights reserved.
//
#include "GUI.h"

#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include <QFont>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QList>
#include <QSignalMapper>
#include <QString>

#include "Board.h"
#include "Column.h"
#include "GUIColumn.h"

GUI::GUI() {
  // create scene
  scene = new QGraphicsScene();

  // addColumnButtons();
  addRestartButton();

  // construct GUI board
  guiboard = new GUIBoard(scene);

  // add a view to visualise the scene
  view = new QGraphicsView(scene);
  view->resize(QSize(1024, 768));

  view->show();  // make the scene visible

  currentPlayerTxt = new QGraphicsTextItem;
  currentPlayerTxt->setFont(QFont("Serif", 20));
  currentPlayerTxt->setPos(700, 300);

  scoreTxt = new QGraphicsTextItem;
  scoreTxt->setFont(QFont("Serif", 20));
  scoreTxt->setPos(700, 200);
  scoreTxt->setPlainText(QString("Player 1's score = 0\nPlayer 2's score = 0"));

  scene->addItem(currentPlayerTxt);
  scene->addItem(scoreTxt);
}

void GUI::addRestartButton() {
  QString buttonLabel = "Restart";
  restartButton = new QPushButton(buttonLabel);
  restartButton->setGeometry(0, 0, 100, 100);
  restartButton->move(700, 350);
  scene->addWidget(restartButton);
}

QPushButton* GUI::getRestartButton() const { return restartButton; }

void GUI::clearScene() {
  // remove all discs from scene
  QList<QGraphicsEllipseItem*> discs = guiboard->getDiscsOnScene();
  for (auto& disc : discs) {
    scene->removeItem(disc);
  }
  guiboard->clear();
}

void GUI::addColumnButtons() {
  // create 7 buttons and add to the scene
  std::stringstream buttonStream;
  QString buttonLabel;
  QPushButton* button;
  buttonMapper = new QSignalMapper;
  for (int i = 0; i < 7; ++i) {
    // create numbered button label
    buttonStream.str("");
    buttonStream << "Button" << i;
    buttonLabel = QString::fromStdString(buttonStream.str());

    // create new button with numbered button label and add to button list
    button = new QPushButton(buttonLabel);
    buttons.append(button);
    buttons[i]->setGeometry(0, 0, 100, 100);
    buttons[i]->move(i * 100, 0);

    // connect button to a map which is mapped to a function
    QObject::connect(buttons[i], SIGNAL(clicked()), buttonMapper, SLOT(map()));

    // set the input value which is passed to the mapped function - the button #
    buttonMapper->setMapping(buttons[i], i);

    // add button to scene
    scene->addWidget(buttons[i]);
  }
}

void GUI::updateScoreTxt(const std::vector<unsigned int>& scores) {
  scoreTxt->setPlainText(QString("Player 1's score = %1\nPlayer 2's score = %2")
                             .arg(scores[0])
                             .arg(scores[1]));
}

void GUI::updatePlayerTxt(int playerID) {
  currentPlayerTxt->setPlainText(QString("Player %1's turn").arg(playerID));
}

GUIBoard* GUI::getGUIBoard() const { return guiboard; }

QSignalMapper* GUI::getButtonMapper() const { return buttonMapper; }

void GUI::drawWin(const std::vector<unsigned int>& scores,
                  const std::vector<std::tuple<int, int>>& winCoords) {
  Expects(scores.size() == 2);
  guiboard->drawConnectFour(winCoords);
  updateScoreTxt(scores);
}
