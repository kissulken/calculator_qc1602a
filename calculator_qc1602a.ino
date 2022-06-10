#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
byte c_sign = 0, c_num = 0;
String first, second;
bool split = true;
char sign = '+';
char keys[4][4] =
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'D','0','E','='}
};
byte rowPins[4] = { 2, 3, 4, 5 };
byte colPins[4] = { 6, 7, 8, 9 };
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);

void setup()
{
    Serial.begin(9600);
    lcd.init();
    lcd.backlight();
    Serial.begin(9600);
    Greetings();
}

void loop()
{
    char key = keypad.getKey();
    if (key != NO_KEY)
    {
        switch (key)
        {
        case 'A':
            c_sign++;
            switch (c_sign)
            {
            case 1:
                sign = '-';
                lcd.setCursor(7, 0);
                lcd.print(sign);
                break;

            case 2:
                sign = '*';
                lcd.setCursor(7, 0);
                lcd.print(sign);
                break;

            case 3:
                sign = '/';
                lcd.setCursor(7, 0);
                lcd.print(sign);
                break;

            case 4:
                sign = '+';
                lcd.setCursor(7, 0);
                lcd.print(sign);
                c_sign = 0;
                break;
            }
            break;

        case 'B':
            split = !split;
            c_num = 0;
            if (split)
            {
                clearArea(0, 6, 0);
                first = "";
            }
            else
            {
                clearArea(9, 14, 0);
                second = "";
            }
            break;

        case 'D':
            lcd.clear();
            Greetings();
            first = "";
            second = "";
            c_num = 0;
            c_sign = 0;
            split = true;
            break;

        case '=':
            if (first != "" && second != "" && second != "0")
            {
                clearArea(0, 16, 1);
                lcd.setCursor(0, 1);
                switch (sign)
                {
                case '+':
                    lcd.print(first.toInt() + second.toInt());
                    break;
                case '-':
                    lcd.print(first.toInt() - second.toInt());
                    break;
                case '*':
                    lcd.print(first.toInt() * second.toInt());
                    break;
                case '/':
                    lcd.print(first.toInt() / second.toInt());
                    break;
                }
            }
            break;

        case 'C':

            break;

        case 'E':

            break;

        default:
            c_num++;
            if (c_num < 6)
            {
                if (split)
                {
                    first += key;
                    lcd.setCursor(0, 0);
                    lcd.print(first);
                }
                else
                {
                    second += key;
                    lcd.setCursor(9, 0);
                    lcd.print(second);
                }
            }
            break;
        }
    }
}

void Greetings()
{
    lcd.setCursor(0, 0);
    lcd.print("Calculate IT!");
    delay(1000);
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.print(sign);
    lcd.setCursor(15, 0);
    lcd.print('=');
    lcd.setCursor(0, 0);
}

void clearArea(int ot, int i_do, int stroka)
{
    for (int i = ot; i < i_do; i++)
    {
        lcd.setCursor(i, stroka);
        lcd.print(" ");
    }
}
