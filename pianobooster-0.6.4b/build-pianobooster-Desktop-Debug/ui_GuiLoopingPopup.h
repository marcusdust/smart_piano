/********************************************************************************
** Form generated from reading UI file 'GuiLoopingPopup.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUILOOPINGPOPUP_H
#define UI_GUILOOPINGPOPUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GuiLoopingPopup
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QDoubleSpinBox *loopBarsSpin;
    QLabel *loopingText;

    void setupUi(QWidget *GuiLoopingPopup)
    {
        if (GuiLoopingPopup->objectName().isEmpty())
            GuiLoopingPopup->setObjectName(QStringLiteral("GuiLoopingPopup"));
        GuiLoopingPopup->resize(157, 70);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GuiLoopingPopup->sizePolicy().hasHeightForWidth());
        GuiLoopingPopup->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(GuiLoopingPopup);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalLayout->setContentsMargins(-1, 2, -1, 4);
        label_3 = new QLabel(GuiLoopingPopup);
        label_3->setObjectName(QStringLiteral("label_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(label_3);

        loopBarsSpin = new QDoubleSpinBox(GuiLoopingPopup);
        loopBarsSpin->setObjectName(QStringLiteral("loopBarsSpin"));
        loopBarsSpin->setMaximumSize(QSize(62, 16777215));
        loopBarsSpin->setFrame(true);
        loopBarsSpin->setDecimals(1);
        loopBarsSpin->setMaximum(99.9);

        horizontalLayout->addWidget(loopBarsSpin);


        verticalLayout->addLayout(horizontalLayout);

        loopingText = new QLabel(GuiLoopingPopup);
        loopingText->setObjectName(QStringLiteral("loopingText"));

        verticalLayout->addWidget(loopingText);


        retranslateUi(GuiLoopingPopup);

        QMetaObject::connectSlotsByName(GuiLoopingPopup);
    } // setupUi

    void retranslateUi(QWidget *GuiLoopingPopup)
    {
        GuiLoopingPopup->setWindowTitle(QApplication::translate("GuiLoopingPopup", "Form", 0));
        label_3->setText(QApplication::translate("GuiLoopingPopup", "Repeat Bars:", 0));
        loopingText->setText(QApplication::translate("GuiLoopingPopup", "End bar", 0));
    } // retranslateUi

};

namespace Ui {
    class GuiLoopingPopup: public Ui_GuiLoopingPopup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUILOOPINGPOPUP_H
