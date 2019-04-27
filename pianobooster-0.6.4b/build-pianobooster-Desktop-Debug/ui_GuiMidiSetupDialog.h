/********************************************************************************
** Form generated from reading UI file 'GuiMidiSetupDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUIMIDISETUPDIALOG_H
#define UI_GUIMIDISETUPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GuiMidiSettingsDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *midiSetupTabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_6;
    QSpacerItem *verticalSpacer_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *midiInfoText;
    QGridLayout *_2;
    QLabel *label;
    QComboBox *midiInputCombo;
    QLabel *label_2;
    QComboBox *midiOutputCombo;
    QSpacerItem *verticalSpacer;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout;
    QListWidget *soundFontList;
    QVBoxLayout *verticalLayout_5;
    QPushButton *fluidAddButton;
    QPushButton *fluidRemoveButton;
    QSpacerItem *verticalSpacer_3;
    QGroupBox *fluidSettingsGroupBox;
    QVBoxLayout *verticalLayout_4;
    QGridLayout *gridLayout;
    QLineEdit *audioDeviceLineEdit;
    QLabel *label_7;
    QLabel *label_18;
    QSpinBox *masterGainSpin;
    QLabel *label_8;
    QComboBox *audioDriverCombo;
    QLabel *label_9;
    QComboBox *sampleRateCombo;
    QLabel *label_3;
    QSpinBox *bufferSizeSpin;
    QLabel *label_4;
    QSpinBox *bufferCountsSpin;
    QCheckBox *reverbCheck;
    QCheckBox *chorusCheck;
    QWidget *tab_3;
    QPushButton *latencyFixButton;
    QLabel *latencyFixLabel;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *GuiMidiSettingsDialog)
    {
        if (GuiMidiSettingsDialog->objectName().isEmpty())
            GuiMidiSettingsDialog->setObjectName(QStringLiteral("GuiMidiSettingsDialog"));
        GuiMidiSettingsDialog->resize(501, 384);
        verticalLayout = new QVBoxLayout(GuiMidiSettingsDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        midiSetupTabWidget = new QTabWidget(GuiMidiSettingsDialog);
        midiSetupTabWidget->setObjectName(QStringLiteral("midiSetupTabWidget"));
        midiSetupTabWidget->setContextMenuPolicy(Qt::PreventContextMenu);
        midiSetupTabWidget->setTabShape(QTabWidget::Rounded);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout_6 = new QVBoxLayout(tab);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalSpacer_2 = new QSpacerItem(396, 28, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_2);

        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        midiInfoText = new QTextEdit(groupBox);
        midiInfoText->setObjectName(QStringLiteral("midiInfoText"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(midiInfoText->sizePolicy().hasHeightForWidth());
        midiInfoText->setSizePolicy(sizePolicy);
        midiInfoText->setMaximumSize(QSize(16777215, 100));
        midiInfoText->setAcceptDrops(false);
        midiInfoText->setReadOnly(true);

        verticalLayout_2->addWidget(midiInfoText);

        _2 = new QGridLayout();
        _2->setObjectName(QStringLiteral("_2"));
        _2->setSizeConstraint(QLayout::SetMinimumSize);
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        _2->addWidget(label, 0, 0, 1, 1);

        midiInputCombo = new QComboBox(groupBox);
        midiInputCombo->setObjectName(QStringLiteral("midiInputCombo"));
#ifndef QT_NO_WHATSTHIS
        midiInputCombo->setWhatsThis(QStringLiteral(""));
#endif // QT_NO_WHATSTHIS

        _2->addWidget(midiInputCombo, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        _2->addWidget(label_2, 1, 0, 1, 1);

        midiOutputCombo = new QComboBox(groupBox);
        midiOutputCombo->setObjectName(QStringLiteral("midiOutputCombo"));

        _2->addWidget(midiOutputCombo, 1, 1, 1, 1);


        verticalLayout_2->addLayout(_2);


        verticalLayout_6->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(396, 28, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer);

        midiSetupTabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout_3 = new QVBoxLayout(tab_2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        groupBox_3 = new QGroupBox(tab_2);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout_7 = new QVBoxLayout(groupBox_3);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        soundFontList = new QListWidget(groupBox_3);
        soundFontList->setObjectName(QStringLiteral("soundFontList"));

        horizontalLayout->addWidget(soundFontList);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        fluidAddButton = new QPushButton(groupBox_3);
        fluidAddButton->setObjectName(QStringLiteral("fluidAddButton"));

        verticalLayout_5->addWidget(fluidAddButton);

        fluidRemoveButton = new QPushButton(groupBox_3);
        fluidRemoveButton->setObjectName(QStringLiteral("fluidRemoveButton"));

        verticalLayout_5->addWidget(fluidRemoveButton);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_3);


        horizontalLayout->addLayout(verticalLayout_5);


        verticalLayout_7->addLayout(horizontalLayout);


        verticalLayout_3->addWidget(groupBox_3);

        fluidSettingsGroupBox = new QGroupBox(tab_2);
        fluidSettingsGroupBox->setObjectName(QStringLiteral("fluidSettingsGroupBox"));
        verticalLayout_4 = new QVBoxLayout(fluidSettingsGroupBox);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        audioDeviceLineEdit = new QLineEdit(fluidSettingsGroupBox);
        audioDeviceLineEdit->setObjectName(QStringLiteral("audioDeviceLineEdit"));
        audioDeviceLineEdit->setMinimumSize(QSize(150, 0));

        gridLayout->addWidget(audioDeviceLineEdit, 1, 4, 1, 1);

        label_7 = new QLabel(fluidSettingsGroupBox);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_7, 1, 2, 1, 1);

        label_18 = new QLabel(fluidSettingsGroupBox);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_18, 0, 0, 1, 1);

        masterGainSpin = new QSpinBox(fluidSettingsGroupBox);
        masterGainSpin->setObjectName(QStringLiteral("masterGainSpin"));

        gridLayout->addWidget(masterGainSpin, 0, 1, 1, 1);

        label_8 = new QLabel(fluidSettingsGroupBox);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_8, 0, 2, 1, 1);

        audioDriverCombo = new QComboBox(fluidSettingsGroupBox);
        audioDriverCombo->setObjectName(QStringLiteral("audioDriverCombo"));

        gridLayout->addWidget(audioDriverCombo, 0, 4, 1, 1);

        label_9 = new QLabel(fluidSettingsGroupBox);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_9, 2, 2, 1, 1);

        sampleRateCombo = new QComboBox(fluidSettingsGroupBox);
        sampleRateCombo->setObjectName(QStringLiteral("sampleRateCombo"));

        gridLayout->addWidget(sampleRateCombo, 2, 4, 1, 1);

        label_3 = new QLabel(fluidSettingsGroupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        bufferSizeSpin = new QSpinBox(fluidSettingsGroupBox);
        bufferSizeSpin->setObjectName(QStringLiteral("bufferSizeSpin"));

        gridLayout->addWidget(bufferSizeSpin, 1, 1, 1, 1);

        label_4 = new QLabel(fluidSettingsGroupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        bufferCountsSpin = new QSpinBox(fluidSettingsGroupBox);
        bufferCountsSpin->setObjectName(QStringLiteral("bufferCountsSpin"));

        gridLayout->addWidget(bufferCountsSpin, 2, 1, 1, 1);

        reverbCheck = new QCheckBox(fluidSettingsGroupBox);
        reverbCheck->setObjectName(QStringLiteral("reverbCheck"));

        gridLayout->addWidget(reverbCheck, 3, 0, 1, 1);

        chorusCheck = new QCheckBox(fluidSettingsGroupBox);
        chorusCheck->setObjectName(QStringLiteral("chorusCheck"));

        gridLayout->addWidget(chorusCheck, 3, 1, 1, 1);


        verticalLayout_4->addLayout(gridLayout);


        verticalLayout_3->addWidget(fluidSettingsGroupBox);

        midiSetupTabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        latencyFixButton = new QPushButton(tab_3);
        latencyFixButton->setObjectName(QStringLiteral("latencyFixButton"));
        latencyFixButton->setGeometry(QRect(40, 120, 121, 29));
        latencyFixLabel = new QLabel(tab_3);
        latencyFixLabel->setObjectName(QStringLiteral("latencyFixLabel"));
        latencyFixLabel->setGeometry(QRect(200, 130, 195, 17));
        latencyFixLabel->setAlignment(Qt::AlignCenter);
        midiSetupTabWidget->addTab(tab_3, QString());

        verticalLayout->addWidget(midiSetupTabWidget);

        buttonBox = new QDialogButtonBox(GuiMidiSettingsDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

        buttonBox->raise();
        midiSetupTabWidget->raise();

        retranslateUi(GuiMidiSettingsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), GuiMidiSettingsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), GuiMidiSettingsDialog, SLOT(reject()));

        midiSetupTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(GuiMidiSettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *GuiMidiSettingsDialog)
    {
        GuiMidiSettingsDialog->setWindowTitle(QApplication::translate("GuiMidiSettingsDialog", "Dialog", 0));
        groupBox->setTitle(QApplication::translate("GuiMidiSettingsDialog", "Select the MIDI devices", 0));
        label->setText(QApplication::translate("GuiMidiSettingsDialog", "Midi Input Device:", 0));
        label_2->setText(QApplication::translate("GuiMidiSettingsDialog", "Midi Output Device:", 0));
        midiSetupTabWidget->setTabText(midiSetupTabWidget->indexOf(tab), QApplication::translate("GuiMidiSettingsDialog", "MIDI input && output", 0));
        groupBox_3->setTitle(QApplication::translate("GuiMidiSettingsDialog", "Sound Fonts", 0));
        fluidAddButton->setText(QApplication::translate("GuiMidiSettingsDialog", "Add", 0));
        fluidRemoveButton->setText(QApplication::translate("GuiMidiSettingsDialog", "Remove", 0));
        fluidSettingsGroupBox->setTitle(QApplication::translate("GuiMidiSettingsDialog", "Settings", 0));
        label_7->setText(QApplication::translate("GuiMidiSettingsDialog", "Audio Device:", 0));
        label_18->setText(QApplication::translate("GuiMidiSettingsDialog", "Master Gain:", 0));
        label_8->setText(QApplication::translate("GuiMidiSettingsDialog", "Audio Driver:", 0));
        label_9->setText(QApplication::translate("GuiMidiSettingsDialog", "Sample Rate:", 0));
        label_3->setText(QApplication::translate("GuiMidiSettingsDialog", "Buffer Size", 0));
        label_4->setText(QApplication::translate("GuiMidiSettingsDialog", "Buffer counts", 0));
        reverbCheck->setText(QApplication::translate("GuiMidiSettingsDialog", "Reverb", 0));
        chorusCheck->setText(QApplication::translate("GuiMidiSettingsDialog", "Chorus", 0));
        midiSetupTabWidget->setTabText(midiSetupTabWidget->indexOf(tab_2), QApplication::translate("GuiMidiSettingsDialog", "FluidSynth", 0));
        latencyFixButton->setText(QApplication::translate("GuiMidiSettingsDialog", "Latency", 0));
        latencyFixLabel->setText(QApplication::translate("GuiMidiSettingsDialog", "0 (msec)", 0));
        midiSetupTabWidget->setTabText(midiSetupTabWidget->indexOf(tab_3), QApplication::translate("GuiMidiSettingsDialog", "Latency Fix", 0));
    } // retranslateUi

};

namespace Ui {
    class GuiMidiSettingsDialog: public Ui_GuiMidiSettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUIMIDISETUPDIALOG_H
