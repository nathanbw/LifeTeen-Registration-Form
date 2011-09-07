#ifndef _RegistrationForm_h_
#define _RegistrationForm_h_

#include "ui_RegistrationForm.h"

class QFile;

class RegistrationForm : public QWidget
{
    Q_OBJECT;
public:
    RegistrationForm(QWidget *parent = 0, QString fileName = "");

private slots:
    void on_submitRegPushButton_clicked();
    // void on_inputSpinBox2_valueChanged(int value);

private:
    bool AppendLineToFile(QString* line);
    void ClearForm();

    Ui::RegistrationForm ui;
    QFile *mpFile;
};

#endif
