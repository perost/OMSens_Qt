#ifndef MULTIPARAMSWEEPDIALOG_H
#define MULTIPARAMSWEEPDIALOG_H

#include "DualLists.h"

#include <QDialog>
#include <QDoubleSpinBox>
#include <QFrame>
#include <QGridLayout>
#include <QTableWidget>


class Label;
class MultiParamSweepDialog : public QDialog
{
    Q_OBJECT
public:
    MultiParamSweepDialog(QWidget *pParent = 0);
    QGridLayout * initializeLayout();

    void addWidgetsToLayout(QGridLayout *pMainLayout);


private:
    // Members:
    QPushButton *mpRunButton;
    Label *mpHeading;
    QFrame *mpHorizontalLine;
    Label *mpVarsToPlotLabel;
    DualLists *mpVarsToPlotDualLists;
    Label *mpStopTimeLabel;
    QDoubleSpinBox *mpStopTimeBox;
    QTableWidget *mpParamsToSweepTable;
    // Auxs:
    void initializeWindowSettings();
    void setHeading();

    void initializeButton();

private slots:
    void runMultiParamSweep();
};

#endif // MULTIPARAMSWEEPDIALOG_H