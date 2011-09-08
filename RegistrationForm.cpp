#include <QtGui>

#include "RegistrationForm.h"

RegistrationForm::RegistrationForm(QWidget *parent, QString fileName)
    : QWidget(parent),
      mpFile(0)
{
    ui.setupUi(this);
    ui.gradeComboBox->addItem("Choose Below:");
    ui.gradeComboBox->addItem("9th - Freshman");
    ui.gradeComboBox->addItem("10th - Sophomore");
    ui.gradeComboBox->addItem("11th - Junior");
    ui.gradeComboBox->addItem("12th - Senior");

    ui.doyouhaveFacebookComboBox->addItem("Choose Below:");
    ui.doyouhaveFacebookComboBox->addItem("Yes");
    ui.doyouhaveFacebookComboBox->addItem("No");

    mpFile = new QFile(fileName);

    // Set up the file:
    if (!mpFile->exists())
    {
        qDebug() << "File doesn't exist, creating: "
                 << fileName;
        if (!mpFile->open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug() << "Couldn't open the file for writing!";
            return;
        }
        else
        {
            QTextStream out(mpFile);
            out << "\"First Name\""
                << "," << "\"Last Name\""
                << "," << "\"Grade\""
                << "," << "\"School\""
                << "," << "\"Teen E-mail\""
                << "," << "\"Parent E-mail\""
                << "," << "\"Home Phone\""
                << "," << "\"Teen Cell\""
                << "," << "\"Birthday\""
                << "," << "\"Facebook\"" << endl;
        }
        mpFile->close();
    }
    else
    {
        // File exists! Will open for appending later
        qDebug() << "File Exists! Looking good.";
    }
}

void
RegistrationForm::on_submitRegPushButton_clicked()
{
    if (!ValidateForm())
    {
        QMessageBox msgBox;
        QFont msgBoxFont;
        msgBoxFont.setPointSize(14);
        msgBoxFont.setBold(true);
        msgBox.setWindowTitle("Notice");
        msgBox.setFont(msgBoxFont);
        msgBox.setText("Please enter all required fields");
        msgBox.exec();
        return;
    }
    // All fields have been validated.
    // Create line to be appended file
    QString curLine; // Note: performance here is terrible:
    curLine += ui.firstNameLineEdit->text()
        + "," + ui.lastNameLineEdit->text()
        + "," + ui.gradeComboBox->currentText()
        + "," + ui.schoolLineEdit->text()
        + "," + ui.teenEmailLineEdit->text()
        + "," + ui.parentEmailLineEdit->text()
        + "," + ui.homePhoneLineEdit->text()
        + "," + ui.teenCellLineEdit->text()
        + "," + ui.birthdayDateEdit->date().toString("MM/dd/yyyy")
        + "," + ui.doyouhaveFacebookComboBox->currentText();
    // Append line to file
    if (!AppendLineToFile(&curLine))
    {
        QMessageBox msgBox;
        QFont msgBoxFont;
        msgBoxFont.setPointSize(14);
        msgBoxFont.setBold(true);
        msgBox.setWindowTitle("Error!");
        msgBox.setFont(msgBoxFont);
        msgBox.setText("Unable to write file: Please get nearest core member!");
        msgBox.exec();
        return;
    }
    // Clear form
    ClearForm();
    // Display "You're done!" box.
    QMessageBox msgBox;
    QFont msgBoxFont;
    msgBoxFont.setPointSize(14);
    msgBoxFont.setBold(true);
    msgBox.setWindowTitle("Contragulations!");
    msgBox.setFont(msgBoxFont);
    msgBox.setText("You have successfully registered!");
    msgBox.exec();
    return;
}

bool
RegistrationForm::AppendLineToFile(QString* line)
{
    if (!line)
    {
        return false;
    }

    // 1. Open file for writing.
    if (!mpFile->open(QIODevice::Append | QIODevice::Text))
    {
        qDebug() << "Couldn't open the file for writing!";
        return false;
    }
    else
    {
        // 2. Write data to file.
        QTextStream out(mpFile);
        out << *line << endl;;
    }
    // 3. Close file
    mpFile->close();
    return true;
}

void
RegistrationForm::ClearForm()
{
    ui.firstNameLineEdit->setText("");
    ui.lastNameLineEdit->setText("");
    ui.gradeComboBox->setCurrentIndex(0);
    ui.schoolLineEdit->setText("");
    ui.teenEmailLineEdit->setText("");
    ui.parentEmailLineEdit->setText("");
    ui.homePhoneLineEdit->setText("");
    ui.teenCellLineEdit->setText("");
    ui.birthdayDateEdit->setDate(ui.birthdayDateEdit->minimumDate());
    ui.doyouhaveFacebookComboBox->setCurrentIndex(0);
}

bool
RegistrationForm::ValidateForm()
{
    bool passedValidation = true;
    // Note: Teen Cell and Facebook are not required fields
    if (ui.firstNameLineEdit->text() == "")
    {
        ui.firstNameLabel->setText("<font color=red>First Name:</font>");
        passedValidation = false;
    }
    else
    {
        ui.firstNameLabel->setText("<font color=black>First Name:</font>");
    }

    if (ui.lastNameLineEdit->text() == "")
    {
        ui.lastNameLabel->setText("<font color=red>Last Name:</font>");
        passedValidation = false;
    }
    else
    {
        ui.lastNameLabel->setText("<font color=black>Last Name:</font>");
    }

    if (ui.gradeComboBox->currentText() == "Choose Below:")
    {
        ui.gradeLabel->setText("<font color=red>Grade:</font>");
        passedValidation = false;
    }
    else
    {
        ui.gradeLabel->setText("<font color=black>Grade:</font>");
    }

    if (ui.schoolLineEdit->text() == "")
    {
        ui.schoolLabel->setText("<font color=red>School:</font>");
        passedValidation = false;
    }
    else
    {
        ui.schoolLabel->setText("<font color=black>School:</font>");
    }

    if (ui.teenEmailLineEdit->text() == "")
    {
        ui.teenEmailLabel->setText("<font color=red>Teen E-mail:</font>");
        passedValidation = false;
    }
    else
    {
        ui.teenEmailLabel->setText("<font color=black>Teen E-mail:</font>");
    }

    if (ui.parentEmailLineEdit->text() == "")
    {
        ui.parentEmailLabel->setText("<font color=red>Parent E-mail:</font>");
        passedValidation = false;
    }
    else
    {
        ui.parentEmailLabel->setText("<font color=black>Parent E-mail:</font>");
    }

    if (ui.homePhoneLineEdit->text() == "")
    {
        ui.homePhoneLabel->setText("<font color=red>Home Phone #:</font>");
        passedValidation = false;
    }
    else
    {
        ui.homePhoneLabel->setText("<font color=black>Home Phone #:</font>");
    }

    if (ui.birthdayDateEdit->date() == ui.birthdayDateEdit->minimumDate())
    {
        ui.birthdayLabel->setText("<font color=red>Birthday (MM/DD/YYYY):</font>");
        passedValidation = false;
    }
    else
    {
        ui.birthdayLabel->setText("<font color=black>Birthday (MM/DD/YYYY):</font>");
    }
    return passedValidation;
}
