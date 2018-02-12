#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include <QMap>

namespace Ui {
    class MainDialog;
}

class MainDialog : public QDialog
{
        Q_OBJECT

    public:
        explicit MainDialog(QWidget *parent = 0);
        ~MainDialog();

    public slots:
        void setNoveltyValue();
        void setObjectivityValue();
        void setEvidenceSubstantiationValue();
        void setSeverityValue();
        void setObjectnessValue();
        void setSystemValue();
        void setVerifiabilityValue();
        void addResult();
        void enableButton();

    private:
        Ui::MainDialog *ui;
        QList<double> noveltyWeightRatio;
        QList<double> objectivityWeightRatio;
        QList<double> evidenceSubstantiationWeightRatio;
        QList<double> severityWeightRatio;
        QList<double> objectnessWeightRatio;
        QList<double> systemWeightRatio;
        QList<double> verifiabilityWeightRatio;
        QMap<int, QList<double> > valuesScientificResult;

        void setResultGeneral();
        double computAssessingQualityStage();
        double computAssessingQualityGeneral();
        double computeEffectiveness();
};

#endif // MAINDIALOG_H
