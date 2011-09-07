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
                << "," << "\"Birthday\"" << endl;
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
    // TODO: Check each item individually, tell the user
    //       which item is missing.
    if ((ui.firstNameLineEdit->text() == "") ||
        (ui.lastNameLineEdit->text() == "") ||
        (ui.gradeComboBox->currentText() == "Choose Below:") ||
        (ui.schoolLineEdit->text() == "") ||
        (ui.teenEmailLineEdit->text() == "") ||
        (ui.parentEmailLineEdit->text() == "") ||
        (ui.homePhoneLineEdit->text() == "") ||
        // (ui.teenCellLineEdit->text() == "") || // Teen cell not required.
        (ui.birthdayDateEdit->date() == ui.birthdayDateEdit->minimumDate()))
    {
        // Might highlight required fields like this:
        // ui.firstNameLabel->setForegroundRole(QPalette::Highlight);
        qDebug() << "Some field is missing!";
        qDebug() << ui.firstNameLineEdit->text()
                 << "," << ui.lastNameLineEdit->text()
                 << "," << ui.gradeComboBox->currentText()
                 << "," << ui.schoolLineEdit->text()
                 << "," << ui.teenEmailLineEdit->text()
                 << "," << ui.parentEmailLineEdit->text()
                 << "," << ui.homePhoneLineEdit->text()
                 << "," << ui.teenCellLineEdit->text()
                 << "," << ui.birthdayDateEdit->date().toString("MM/dd");
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
        + "," + ui.birthdayDateEdit->date().toString("MM/dd/yyyy");
    // Append line to file
    AppendLineToFile(&curLine); // TODO: Check return here, give error if failed!
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
}
