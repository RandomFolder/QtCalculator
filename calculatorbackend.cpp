#include "calculatorbackend.h"
#include <QDebug>
#include "BigFloat.h"
#include <stack>
#include <cctype>
#include <QStringList>


int precedence(char op){
    if(op == '+'||op == '-')
        return 1;
    if(op == '*'||op == '/')
        return 2;
    return 0;
}

// Function to perform arithmetic operations.
BigFloat applyOp(std::string a, std::string b, char op)
{
    BigFloat v1, v2;
    if (a.back() == '%')
    {
        a.pop_back();
        v1 = BigFloat(a) / BigFloat("100.0");
    }
    else v1 = (a != "n") ? BigFloat(a) : BigFloat(0);

    if (b.back() == '%')
    {
        b.pop_back();

        if (a != "n" && (op == '+' || op == '-'))
        {
            v2 = v1 * BigFloat(b) / 100.0;
        }
        else
        {
            v2 = BigFloat(b) / 100.0;
        }
    }
    else v2 = BigFloat(b);

    switch(op){
    case '+': return v1 + v2;
    case '-': return v1 - v2;
    case '*': return v1 * v2;
    case '/': return v1 * 1.0 / v2;
    }
    return BigFloat(0);
}

BigFloat applyOp(std::string val, char op)
{
    BigFloat v = BigFloat(val);

    switch (op)
    {
    case '%': return v / 100.0;
    }
    return BigFloat(0);
}

// Function that returns value of
// expression after evaluation.
BigFloat evaluate(std::string tokens){
    if (tokens[0] == '-')
    {
        tokens = "n" + tokens;
    }

    for (int i = 0; i < tokens.size(); i++)
    {
        if (tokens[i] == '-' && tokens[i - 1] == '(')
        {
            tokens.insert(i, "n");
        }
    }

    int i;

    // stack to store integer values.
    std::stack <std::string> values;

    // stack to store operators.
    std::stack <char> ops;

    for(i = 0; i < tokens.length(); i++){

        // Current token is a whitespace,
        // skip it.
        if(tokens[i] == ' ')
            continue;

        // Current token is an opening
        // brace, push it to 'ops'
        else if(tokens[i] == '('){
            ops.push(tokens[i]);
        }

        // Current token is a number, push
        // it to stack for numbers.
        else if(isdigit(tokens[i]) || tokens[i] == 'n'){
            std::string numberAsStr = "";

            while(i < tokens.length() && (isdigit(tokens[i]) || tokens[i] == '.' || tokens[i] == '%' || tokens[i] == 'n'))
            {
                numberAsStr += tokens[i];
                i++;
            }

            values.push(numberAsStr);

            i--;
        }

        // Closing brace encountered, solve
        // entire brace.
        else if(tokens[i] == ')')
        {
            while(!ops.empty() && ops.top() != '(')
            {
                std::string val2 = values.top();
                values.pop();

                std::string val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOp(val1, val2, op));
            }

            // pop opening brace.
            if(!ops.empty())
                ops.pop();
        }

        else if (tokens[i] == '%')
        {
            std::string val = values.top();
            values.pop();
            values.push(applyOp(val, '%'));
        }

        // Current token is an operator.
        else
        {
            while(!ops.empty() && precedence(ops.top())
                                       >= precedence(tokens[i])){
                std::string val2 = values.top();
                values.pop();

                std::string val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOp(val1, val2, op));
            }

            // Push current token to 'ops'.
            ops.push(tokens[i]);
        }
    }

    while(!ops.empty()){
        std::string val2 = values.top();
        values.pop();

        std::string val1 = values.top();
        values.pop();

        char op = ops.top();
        ops.pop();

        values.push(applyOp(val1, val2, op));
    }

    if (!values.empty())
    {
        std::string val = values.top();
        values.pop();

        values.push(applyOp(val, "0.0", '+'));
    }

    // Top of 'values' contains result, return it.
    return values.top();
}


bool ExpressionIsValid(std::string expression)
{
    QString symbols = "0123456789)%";

    if (std::count(expression.begin(), expression.end(), '(') != std::count(expression.begin(), expression.end(), ')') || !symbols.contains(expression.back()))
    {
        return false;
    }

    return true;
}


CalculatorBackend::CalculatorBackend(QObject* parent) : QObject(parent)
{
    this->formula = "";
    this->result = "0";
    this->codeValidator = "";
    this->newResult = false;
    this->hiddenMenuIsVisible = false;
    this->canEnterCode = false;
    this->UpdateHiddenMenuVisibility();
}


void CalculatorBackend::UpdateHiddenMenuVisibility()
{
    emit this->hiddenMenuVisibleChanged();
}


QString CalculatorBackend::getFormula() const
{
    return this->formula;
}


void CalculatorBackend::setFormula(const QString& formula)
{
    this->formula = formula;
}


bool CalculatorBackend::hiddenMenuVisible() const
{
    return this->hiddenMenuIsVisible;
}


void CalculatorBackend::setHiddenMenuVisible(const bool& isVisible)
{
    this->hiddenMenuIsVisible = isVisible;
    emit this->hiddenMenuVisibleChanged();
}


QString CalculatorBackend::getResult() const
{
    return this->result;
}


void CalculatorBackend::setResult(const QString& result)
{
    this->result = result;
}


void CalculatorBackend::enableCodeEnter()
{
    this->codeValidator = "";
    this->canEnterCode = true;
}


void CalculatorBackend::disableCodeEnter()
{
    this->canEnterCode = false;
}


void CalculatorBackend::checkIfCodeIsEntered()
{
    if (this->codeValidator.endsWith("123"))
    {
        this->hiddenMenuIsVisible = true;
        emit this->hiddenMenuVisibleChanged();
    }
}


void CalculatorBackend::doAction(const QString& enteredValue)
{
    if (enteredValue == "C")
    {
        this->result = "0";
        this->formula = "";
    }
    else if (enteredValue == "=")
    {
        this->formula = this->formula.replace("÷", "/");
        this->formula = this->formula.replace("×", "*");
        if (this->formula != "" && ExpressionIsValid(this->formula.toStdString()))
        {
            BigFloat res = evaluate(this->formula.toStdString());
            QString resAsStr = QString::fromStdString(res.ToString());

            QString decimals = resAsStr.split('.').takeLast();
            int decimalsCount = 0;
            for (int i = 0; i < decimals.size(); i++)
            {
                if (decimals[i] != '0') decimalsCount = i + 1;
            }
            res.SetPrecision(decimalsCount);
            this->result = QString::fromUtf8(res.ToString().c_str());
            this->newResult = true;

            if (this->result == "nan")
            {
                this->result = "0";
                this->formula = "";
            }
        }
        this->formula = this->formula.replace("/", "÷");
        this->formula = this->formula.replace("*", "×");
    }
    else if (enteredValue == "⁺∕₋")
    {
        if (this->newResult)
        {
            this->formula = this->result;
            this->result = "0";
            this->newResult = false;
        }

        QString operators = "+-÷×";

        if (this->formula == "" || this->formula[this->formula.size() - 1] == '(')
        {
            this->formula += "(-";
        }
        else if (operators.contains(this->formula[this->formula.size() - 1]))
        {
            this->formula += "";
        }
        else
        {
            this->formula += "×(-1)";
        }
    }
    else if (enteredValue == "()")
    {
        if (this->newResult)
        {
            this->formula = this->result;
            this->result = "0";
            this->newResult = false;
        }

        int openBracketsCount = this->formula.count('(');
        int closeBracketsCount = this->formula.count(')');

        if (openBracketsCount != closeBracketsCount && this->formula[this->formula.size() - 1] != '(')
        {
            QString operators = "+-÷×";

            if (operators.contains(this->formula[this->formula.size() - 1]))
            {
                this->formula += "(";
            }
            else
            {
                this->formula += ")";
            }
        }
        else
        {
            QString symbols = ")0123456789";

            if (this->formula != "" && symbols.contains(this->formula[this->formula.size() - 1]))
            {
                this->formula += "×";
            }
            this->formula += "(";
        }
    }
    else if (enteredValue == "%")
    {
        if (this->newResult)
        {
            this->formula = this->result;
            this->result = "0";
            this->newResult = false;
        }

        QString symbols = ")0123456789";
        if (this->formula != "" && symbols.contains(this->formula[this->formula.size() - 1]))
        {
            this->formula += "%";
        }
    }
    else if (enteredValue == ".")
    {
        if (this->newResult)
        {
            this->formula = this->result;
            this->result = "0";
            this->newResult = false;
        }

        QString operators = "(+-÷×";
        QString operators2 = ")%";

        if (this->formula == "" || operators.contains(this->formula[this->formula.size() - 1]))
        {
            this->formula += "0.0";
        }
        else if (operators2.contains(this->formula[this->formula.size() - 1]))
        {
            this->formula += "×0.0";
        }
        else
        {
            QString formulaCopy = this->formula;

            for (int i = 0; i < operators.size(); i++)
            {
                formulaCopy = formulaCopy.replace(operators[i], ' ');
            }

            for (int i = 0; i < operators2.size(); i++)
            {
                formulaCopy = formulaCopy.replace(operators2[i], ' ');
            }

            QStringList list = formulaCopy.split(' ');

            if (!list.last().contains('.')) this->formula += ".";
        }
    }
    else
    {
        if (this->newResult)
        {
            this->formula = this->result;
            this->result = "0";
            this->newResult = false;
        }

        QString operators = "(+-÷×";

        if (operators.contains(enteredValue))
        {
            if (this->formula != "" && !operators.contains(this->formula[this->formula.size() - 1]))
            {
                this->formula += enteredValue;
            }
        }
        else
        {
            if (this->formula == "0")
            {
                this->formula = "";
            }
            if (this->formula != "" && this->formula[this->formula.size() - 1] == ')')
            {
                this->formula += "×";
            }
            this->formula += enteredValue;
        }
    }
    emit this->formulaChanged();
    emit resultChanged();

    if (this->canEnterCode)
    {
        this->codeValidator += enteredValue;
        this->checkIfCodeIsEntered();
    }
}
