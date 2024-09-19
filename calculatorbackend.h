#ifndef CALCULATORBACKEND_H
#define CALCULATORBACKEND_H
#include <QString>
#include <QObject>
#include <qqml.h>

class CalculatorBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString formula READ getFormula WRITE setFormula NOTIFY formulaChanged FINAL)
    Q_PROPERTY(QString result READ getResult WRITE setResult NOTIFY resultChanged FINAL)
    Q_PROPERTY(bool hiddenMenuVisible READ hiddenMenuVisible WRITE setHiddenMenuVisible NOTIFY hiddenMenuVisibleChanged FINAL)
signals:
    void formulaChanged();
    void resultChanged();
    void hiddenMenuVisibleChanged();
public:
    CalculatorBackend(QObject* parent = 0);
    QString getFormula() const;
    QString getResult() const;
    void setFormula(const QString& formula);
    void setResult(const QString& result);
    bool hiddenMenuVisible() const;
    void setHiddenMenuVisible(const bool& isVisible);
    Q_INVOKABLE void doAction(const QString& enteredValue);
    Q_INVOKABLE void enableCodeEnter();
    Q_INVOKABLE void disableCodeEnter();
private:
    QString formula;
    QString result;
    QString codeValidator;
    bool newResult;
    bool canEnterCode;
    bool hiddenMenuIsVisible;

    void UpdateHiddenMenuVisibility();
    void checkIfCodeIsEntered();
};

#endif // CALCULATORBACKEND_H
