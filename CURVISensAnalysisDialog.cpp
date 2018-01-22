#include "CURVISensAnalysisDialog.h"
#include "utilities.h"
#include <QMessageBox>
#include <QLabel>
#include <QFrame>
#include <QGridLayout>

// BORRAR:
#include <iostream>
// BORRAR^

void CURVISensAnalysisDialog::initializeWindowSettings()
{
    setWindowTitle("Parameter Sensitivity Analysis - Empirical Indices");
    setAttribute(Qt::WA_DeleteOnClose);
    setMinimumWidth(550);
}

void CURVISensAnalysisDialog::setHeading()
{
    // set import heading
    mpHeading = Utilities::getHeadingLabel("CURVI Sensitivity Analysis");
    // set separator line
    mpHorizontalLine = Utilities::getHeadingLine();
}

void CURVISensAnalysisDialog::initializeFormInputsAndLabels(const double maxTargetTime, const double maxPerturbationPercentage, const QVector<QString> modelVars, const double defaultTime, const double minPerturbationPercentage, const QVector<QString> modelParams)
{
    // User inputs
    mpLowerBoundLabel = new Label(tr("Lower Bound:"));
    mpLowerBoundBox = new QDoubleSpinBox;
    mpLowerBoundBox->setRange(minPerturbationPercentage, 0);
    mpLowerBoundBox->setValue(-5);
    mpLowerBoundBox->setSuffix("%");
    mpUpperBoundLabel = new Label(tr("Upper Bound:"));
    mpUpperBoundBox = new QDoubleSpinBox;
    mpUpperBoundBox->setRange(0, maxPerturbationPercentage);
    mpUpperBoundBox->setValue(5);
    mpUpperBoundBox->setSuffix("%");

    mpVariableLabel = new Label(tr("Target Variable:"));
    // The button group is purely backend specific. No effect on the GUI
    mpOptimTypeButtonGroup = new QButtonGroup();
    mpMaxRadio = new QRadioButton(tr("Maximize"),this);
    mpMaxRadio->toggle(); //This index start selected by default
    mpMinRadio = new QRadioButton(tr("Minimize"),this);
    mpOptimTypeButtonGroup->addButton(mpMinRadio, 0);
    mpOptimTypeButtonGroup->addButton(mpMaxRadio, 1);

    mpVariableComboBox = new QComboBox;
    for (int i_vars=0; i_vars<modelVars.size(); i_vars++)
    {
        mpVariableComboBox->addItem(modelVars[i_vars], QVariant(i_vars));
    }

    mpParameterLabel = new Label(tr("Parameter:"));
    mpParameterComboBox = new QComboBox;
    for (int i_params=0; i_params<modelParams.size(); i_params++)
    {
        mpParameterComboBox->addItem(modelParams[i_params], QVariant(i_params));
    }


    mpTimeLabel = new Label(tr("Time:"));
    mpTimeBox = new QDoubleSpinBox;
    mpTimeBox->setRange(0, maxTargetTime);
    mpTimeBox->setValue(defaultTime);
}

void CURVISensAnalysisDialog::initializeButton()
{
    // create OK button
    mpRunButton = new QPushButton("Ok");
    mpRunButton->setAutoDefault(true);
    connect(mpRunButton, SIGNAL(clicked()), SLOT(runCURVISensAnalysis()));
}

QGridLayout * CURVISensAnalysisDialog::initializeLayout()
{
    // set grid layout
    QGridLayout *pMainLayout = new QGridLayout;
    pMainLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    return pMainLayout;
}

void CURVISensAnalysisDialog::addWidgetsToLayout(QGridLayout *pMainLayout)
{
    pMainLayout->addWidget(mpHeading, 0, 0, 1, 3);
    pMainLayout->addWidget(mpHorizontalLine, 1, 0, 1, 3);
    pMainLayout->addWidget(mpLowerBoundLabel, 2, 0);
    pMainLayout->addWidget(mpLowerBoundBox, 2, 1);
    pMainLayout->addWidget(mpUpperBoundLabel, 2, 2);
    pMainLayout->addWidget(mpUpperBoundBox, 2, 3);
    pMainLayout->addWidget(mpVariableLabel, 5, 0);
    pMainLayout->addWidget(mpMaxRadio, 5, 1);
    pMainLayout->addWidget(mpMinRadio, 6, 1);
    pMainLayout->addWidget(mpVariableComboBox, 5, 2);
    pMainLayout->addWidget(mpParameterLabel, 7, 0);
    pMainLayout->addWidget(mpParameterComboBox,7, 1);
    pMainLayout->addWidget(mpTimeLabel, 8, 0);
    pMainLayout->addWidget(mpTimeBox, 8, 1);

    pMainLayout->addWidget(mpRunButton, 10, 0, 1, 3, Qt::AlignRight);
}

CURVISensAnalysisDialog::CURVISensAnalysisDialog(QWidget *pParent) : QDialog(pParent)
{
    // Function parameters
    const double defaultTime= 2000;
    const double maxTargetTime= 5000;
    const double maxPerturbationPercentage= 100;
    const double minPerturbationPercentage= -100;
    // Model information:
    const QVector<QString> modelVars( QVector<QString>()
                                   << "population"
                                   << "nr_resources"
                                   << "human_welfare_index");
    const QVector<QString> modelParams( QVector<QString>()
                                   << "nr_resources_init"
                                   << "param_2"
                                   << "param_3");
    initializeWindowSettings();
    setHeading();
    initializeFormInputsAndLabels(maxTargetTime, maxPerturbationPercentage, modelVars, defaultTime, minPerturbationPercentage, modelParams);
    initializeButton();
    QGridLayout *pMainLayout = initializeLayout();
    addWidgetsToLayout(pMainLayout);
    setLayout(pMainLayout);
}

void CURVISensAnalysisDialog::runCURVISensAnalysis()
{
    std::cout << "Values chosen:" << std::endl;
    //std::cout << " Percentage: " << mpPercentageBox->text().toUtf8().constData() << std::endl;
    std::cout << " Variable i: " << mpVariableComboBox->currentIndex() << std::endl;
    std::cout << " Index i: " << mpOptimTypeButtonGroup->checkedId() << std::endl;
    std::cout << " Time: " << mpTimeBox->text().toUtf8().constData() << std::endl;
    accept();
}