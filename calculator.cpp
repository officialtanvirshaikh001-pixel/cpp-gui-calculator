
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <string>
#include <cstdlib>

Fl_Input *display;
double firstNumber = 0;
char operation = '\0';
bool newNumber = true;

void button_click(Fl_Widget *widget, void *) {
    const char *label = widget->label();
    std::string text = label;

    if (text == "C") {
        display->value("0");
        firstNumber = 0;
        operation = '\0';
        newNumber = true;
    }
    else if (text == "+" || text == "-" ||
             text == "*" || text == "/") {
        firstNumber = atof(display->value());
        operation = text[0];
        newNumber = true;
    }
    else if (text == "=") {
        double secondNumber = atof(display->value());
        double result = 0;

        if (operation == '+')
            result = firstNumber + secondNumber;
        else if (operation == '-')
            result = firstNumber - secondNumber;
        else if (operation == '*')
            result = firstNumber * secondNumber;
        else if (operation == '/') {
            if (secondNumber == 0) {
                display->value("Cannot divide by zero");
                newNumber = true;
                return;
            }
            result = firstNumber / secondNumber;
        }

        char answer[100];
        snprintf(answer, sizeof(answer), "%.10g", result);
        display->value(answer);
        newNumber = true;
    }
    else {
        if (newNumber) {
            display->value(text.c_str());
            newNumber = false;
        } else {
            std::string current = display->value();
            current += text;
            display->value(current.c_str());
        }
    }
}

int main() {
    Fl_Window *window = new Fl_Window(320, 380, "My C++ Calculator");

    display = new Fl_Input(20, 20, 280, 45);
    display->value("0");
    display->readonly(1);
    display->textsize(20);

    const char *labels[] = {
        "7", "8", "9", "/",
        "4", "5", "6", "*",
        "1", "2", "3", "-",
        "C", "0", "=", "+"
    };

    int index = 0;
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            Fl_Button *button = new Fl_Button(
                20 + col * 70,
                85 + row * 65,
                60, 55,
                labels[index]
            );

            button->callback(button_click);
            index++;
        }
    }

    window->end();
    window->show();
    return Fl::run();
}
