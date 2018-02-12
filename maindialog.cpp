#include "maindialog.h"
#include "ui_maindialog.h"

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint & Qt::WindowMinMaxButtonsHint);

    // init data
    ui->noveltyComboBox->addItem(tr("at the organization level"), 0.75);
    ui->noveltyComboBox->addItem(tr("at the level of defense of the Russian Federation"), 0.85);
    ui->noveltyComboBox->addItem(tr("at the level of scientific and technical complex of the Russian Federation"), 1.0);
    ui->noveltyComboBox->addItem(tr("at world level"), 4.0);
    ui->noveltyComboBox->addItem(tr("above the world level"), 8.0);

    ui->objectivityComboBox->addItem(tr("95 % or more"), 0.95);
    ui->objectivityComboBox->addItem(tr("75 - 94 %"), 0.95);
    ui->objectivityComboBox->addItem(tr("60 - 74 %"), 0.85);
    ui->objectivityComboBox->addItem(tr("less than 60 %"), 0.75);

    ui->evidenceSubstantiationComboBox->addItem(tr("no more than 5 %"), 0.95);
    ui->evidenceSubstantiationComboBox->addItem(tr("from 6 to 10 %"), 0.95);
    ui->evidenceSubstantiationComboBox->addItem(tr("from 11 to 15 %"), 0.85);
    ui->evidenceSubstantiationComboBox->addItem(tr("from 16 to 25 %"), 0.75);
    ui->evidenceSubstantiationComboBox->addItem(tr("more 25 %"), 0.5);

    ui->severityComboBox->addItem(tr("more 80 %"), 0.85);
    ui->severityComboBox->addItem(tr("60 - 79 %"), 0.75);
    ui->severityComboBox->addItem(tr("50 - 60 %"), 0.65);
    ui->severityComboBox->addItem(tr("less than 50 %"), 0.5);

    ui->objectnessComboBox->addItem(tr("more 80 %"), 0.95);
    ui->objectnessComboBox->addItem(tr("60 - 79 %"), 0.95);
    ui->objectnessComboBox->addItem(tr("50 - 60 %"), 0.8);
    ui->objectnessComboBox->addItem(tr("less than 50 %"), 0.5);

    ui->systemComboBox->addItem(tr("identification of the set of elements, the formulation of the goal, the formation of the main relationships between the elements of the system and the evaluation of synergies"), 1.0);
    ui->systemComboBox->addItem(tr("identification of elements, formulation of the goal and the formation of the main relationships between the elements of the system"), 0.85);
    ui->systemComboBox->addItem(tr("identification of the elements and formulation of the purpose of the system"), 0.65);
    ui->systemComboBox->addItem(tr("designation of the set of elements of the system"), 0.5);

    ui->verifiabilityComboBox->addItem(tr("within 1 year"), 1.0);
    ui->verifiabilityComboBox->addItem(tr("within 3 years"), 0.8);
    ui->verifiabilityComboBox->addItem(tr("within 5 years"), 0.7);
    ui->verifiabilityComboBox->addItem(tr("within 10 years"), 0.6);
    ui->verifiabilityComboBox->addItem(tr("more than 10 years"), 0.5);

    ui->levelPracticalResultComboBox->addItem(tr("at the level of chiefs OVU"), 1.5);
    ui->levelPracticalResultComboBox->addItem(tr("at the level of deputy MO RF"), 2.0);
    ui->levelPracticalResultComboBox->addItem(tr("MO RF"), 3.0);

    noveltyWeightRatio << 0.27 << 0.197 << 0.162 << 0.125 << 0.28;
    objectivityWeightRatio << 0.157 << 0.154 << 0.155 << 0.203 << 0.15;
    evidenceSubstantiationWeightRatio <<0.146 << 0.201 << 0.188 << 0.13 << 0.14;
    severityWeightRatio << 0.113 << 0.1 << 0.113 << 0.144 << 0.122;
    objectnessWeightRatio << 0.096 << 0.106 << 0.126 << 0.133 << 0.111;
    systemWeightRatio << 0.105 << 0.116 << 0.094 << 0.119 << 0.099;
    verifiabilityWeightRatio << 0.113 << 0.126 << 0.162 << 0.146 << 0.098;

    valuesScientificResult[0] = QList<double>() << 4 << 5 << 8 << 10;
    valuesScientificResult[1] = QList<double>() << 3 << 4 << 8 << 10;
    valuesScientificResult[2] = QList<double>() << 3 << 4 << 7 << 10;
    valuesScientificResult[3] = QList<double>() << 3 << 4 << 7 << 10;
    valuesScientificResult[4] = QList<double>() << 4 << 5 << 7 << 10;

    connect(ui->noveltyComboBox, SIGNAL(activated(int)), this, SLOT(setNoveltyValue()));
    connect(ui->objectivityComboBox, SIGNAL(activated(int)), this, SLOT(setObjectivityValue()));
    connect(ui->evidenceSubstantiationComboBox, SIGNAL(activated(int)), this, SLOT(setEvidenceSubstantiationValue()));
    connect(ui->severityComboBox, SIGNAL(activated(int)), this, SLOT(setSeverityValue()));
    connect(ui->objectnessComboBox, SIGNAL(activated(int)), this, SLOT(setObjectnessValue()));
    connect(ui->systemComboBox, SIGNAL(activated(int)), this, SLOT(setSystemValue()));
    connect(ui->verifiabilityComboBox, SIGNAL(activated(int)), this, SLOT(setVerifiabilityValue()));
    connect(ui->addResultButton, SIGNAL(clicked(bool)), this, SLOT(addResult()));
    connect(ui->generalLaborCostsDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(enableButton()));
    connect(ui->stageLaborCostsScientificDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(enableButton()));
    connect(ui->stageLaborCostsPracticalDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(enableButton()));

    emit ui->noveltyComboBox->activated(0);
    emit ui->objectivityComboBox->activated(0);
    emit ui->evidenceSubstantiationComboBox->activated(0);
    emit ui->severityComboBox->activated(0);
    emit ui->objectnessComboBox->activated(0);
    emit ui->systemComboBox->activated(0);
    emit ui->verifiabilityComboBox->activated(0);
}

MainDialog::~MainDialog()
{
    delete ui;
}

void MainDialog::setNoveltyValue()
{
    ui->noveltyDoubleSpinBox->setValue(ui->noveltyComboBox->currentData().toDouble());
}

void MainDialog::setObjectivityValue()
{
    ui->objectivityDoubleSpinBox->setValue(ui->objectivityComboBox->currentData().toDouble());
}

void MainDialog::setEvidenceSubstantiationValue()
{
    ui->evidenceSubstantiationDoubleSpinBox->setValue(ui->evidenceSubstantiationComboBox->currentData().toDouble());
}

void MainDialog::setSeverityValue()
{
    ui->severityDoubleSpinBox->setValue(ui->severityComboBox->currentData().toDouble());
}

void MainDialog::setObjectnessValue()
{
    ui->objectnessDoubleSpinBox->setValue(ui->objectnessComboBox->currentData().toDouble());
}

void MainDialog::setSystemValue()
{
    ui->systemDoubleSpinBox->setValue(ui->systemComboBox->currentData().toDouble());
}

void MainDialog::setVerifiabilityValue()
{
    ui->verifiabilityDoubleSpinBox->setValue(ui->verifiabilityComboBox->currentData().toDouble());
}

void MainDialog::addResult()
{
    int numLastRow = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(numLastRow);

    bool ok;
    int num = ui->nameStageLineEdit->text().toInt(&ok);
    ui->tableWidget->setItem(numLastRow, 0, new QTableWidgetItem(ui->nameStageLineEdit->text()));
    if (ok)
        ui->nameStageLineEdit->setText(QString::number(++num));

    double Kknr = computAssessingQualityStage();
    ui->tableWidget->setItem(numLastRow, 1, new QTableWidgetItem(QString::number(Kknr)));
    ui->tableWidget->setItem(numLastRow, 2, new QTableWidgetItem(QString::number(valuesScientificResult.value(ui->typeScientificResultComboBox->currentIndex()).at(ui->levelScientificResultComboBox->currentIndex()))));
    ui->tableWidget->setItem(numLastRow, 3, new QTableWidgetItem(QString::number(ui->stageLaborCostsScientificDoubleSpinBox->value())));
    ui->tableWidget->setItem(numLastRow, 4, new QTableWidgetItem(QString::number(ui->stageLaborCostsPracticalDoubleSpinBox->value())));
    ui->tableWidget->setItem(numLastRow, 5, new QTableWidgetItem(QString::number(ui->levelPracticalResultComboBox->currentData().toDouble())));

    setResultGeneral();
}

double MainDialog::computAssessingQualityStage()
{
    double Knov = (1 - ui->amountBorrowingDoubleSpinBox->value()) * ui->noveltyDoubleSpinBox->value();
    double Kob = ui->objectivityDoubleSpinBox->value();
    double Kdo = ui->evidenceSubstantiationDoubleSpinBox->value();
    double Kv = ui->severityDoubleSpinBox->value();
    double Kpr = ui->objectnessDoubleSpinBox->value();
    double Ksis = ui->systemDoubleSpinBox->value();
    double Kprak = ui->verifiabilityDoubleSpinBox->value();

    int indexTypeScientificResearch = ui->typeScientificResearchComboBox->currentIndex();

    double Kknr = pow(Knov, noveltyWeightRatio[indexTypeScientificResearch]) *
                  pow(Kob, objectivityWeightRatio[indexTypeScientificResearch]) *
                  pow(Kdo, evidenceSubstantiationWeightRatio[indexTypeScientificResearch]) *
                  pow(Kv, severityWeightRatio[indexTypeScientificResearch]) *
                  pow(Kpr, objectnessWeightRatio[indexTypeScientificResearch]) *
                  pow(Ksis, systemWeightRatio[indexTypeScientificResearch]) *
                  pow(Kprak, verifiabilityWeightRatio[indexTypeScientificResearch]);

    return Kknr;
}

double MainDialog::computAssessingQualityGeneral()
{
    double k = 0;
    double generalLaborCosts = ui->generalLaborCostsDoubleSpinBox->value();

    for (int row = 0; row < ui->tableWidget->rowCount(); row++) {
        double Ki = ui->tableWidget->item(row, 1)->text().toDouble();
        double laborCosts = ui->tableWidget->item(row, 3)->text().toDouble();
        k += Ki * (laborCosts / generalLaborCosts);
    }

    return k;
}

void MainDialog::setResultGeneral()
{
    double Kknr = computAssessingQualityGeneral();

    ui->resultKNRLabel->setText(QString::number(Kknr));

    double Krnr = computeEffectiveness();

    ui->resultRNRLabel->setText(QString::number(Krnr));
}

void MainDialog::enableButton()
{
    if (ui->generalLaborCostsDoubleSpinBox->value() != 0 &&
            ui->stageLaborCostsScientificDoubleSpinBox->value() != 0 &&
            ui->stageLaborCostsPracticalDoubleSpinBox->value() != 0)
        ui->addResultButton->setEnabled(true);
    else
        ui->addResultButton->setEnabled(false);
}

double MainDialog::computeEffectiveness()
{
    double generalLaborCosts = ui->generalLaborCostsDoubleSpinBox->value();
    double Kunri = 0;
    double Kunr = 0;
    double Kupri = 0;
    double Kupr = 0;
    double laborCostsScientific = 0;
    double laborCostsPractical = 0;
    double Qnr = 0;
    double Qpr = 0;
    double Knr = 0;
    double Kpr = 0;
    double Anr = ui->weightingFactorScientificResultDoubleSpinBox->value();
    double Apr = ui->weightingFactorPracticalResultDoubleSpinBox->value();

    for (int row = 0; row < ui->tableWidget->rowCount(); row++) {
        Kunri += ui->tableWidget->item(row, 2)->text().toInt();
        laborCostsScientific = ui->tableWidget->item(row, 3)->text().toDouble();
        laborCostsPractical = ui->tableWidget->item(row, 4)->text().toDouble();
        Qnr += laborCostsScientific;
        Qpr += laborCostsPractical;
        Kunr += Kunri * laborCostsScientific;
        Kupr += Kupri * laborCostsPractical;
    }
    Knr = (Kunr + generalLaborCosts * Qnr) / generalLaborCosts;
    Kpr = (Kupr + generalLaborCosts * Qpr) / generalLaborCosts;


    return pow(Knr, Anr) * pow(Kpr, Apr);
}
