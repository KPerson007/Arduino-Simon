//Constants for components
const int yellowLED = 10;
const int blueLED = yellowLED + 1; //pin 11
const int redLED = blueLED + 1; //pin 12
const int greenLED = redLED + 1; //pin 13
const int greenButton = 2;
const int redButton = greenButton + 1; //pin 3
const int blueButton = redButton + 1; //pin 4
const int yellowButton = blueButton + 1; //pin 5
const int controlButton = yellowButton + 1; //pin 6

const int maxScore = 16;

//Game vars
int gameState = 1;
int simonSays[maxScore];
int moveIndex = 0;
int score = 0;
int currentIndex = -1;

void setup() {
  for (int i = yellowLED; i <= greenLED; i++)
  {
    pinMode(i, OUTPUT); 
  }
  for (int i = greenButton; i < controlButton; i++)
  {
    pinMode(i, INPUT);
  }
}

void loop() {
  if (digitalRead(controlButton) == HIGH)
  {
    if (gameState == 1)
    {
      gameState = 2;
    }
  }
  if (gameState == 2) //reading
  {
    currentIndex++;
    simonSays[currentIndex] = random(yellowLED, greenLED + 1);
    for (int i = 0; i <= currentIndex; i++)
    {
      lightOn(false, simonSays[currentIndex]);
      delay(500);
      lightOff(false, simonSays[currentIndex]);
    }
    gameState = 3;
  }
  if (gameState = 3) //waiting for response
  {
    int pressedButton = getPressedButton();
    if (pressedButton != -1)
    {
      lightOn(false, convertButtonToLED(pressedButton));
      if (checkAnswer(convertButtonToLED(pressedButton), moveIndex) == true)
      {
        score++;
        int newIndex = moveIndex++;
        if (newIndex > currentIndex)
        {
          moveIndex = 0;
          gameState = 2;
        }
        else
        {
          moveIndex = newIndex;
        }
      }
      else
      {
        gameState = 1;
        lightOn(true, -1);
        delay(500);
        lightOff(true, -1);  
        moveIndex = 0;
        currentIndex = -1;
        score = 0;
      }
    }
    else
    {
      lightOff(true, -1);
    }
  }
}

void lightOn(boolean all, int LED) //if all = true, then LED won't do anything
{
  if (all == true)
  {
    for (int i = yellowLED; i <= greenLED; i++)
    {
      digitalWrite(i, HIGH);
    }
  }
  else
  {
    digitalWrite(LED, HIGH);
  }
}

void lightOff(boolean all, int LED) //if all = true, then LED won't do anything
{
  if (all == true)
  {
    for (int i = yellowLED; i <= greenLED; i++)
    {
      digitalWrite(i, LOW);
    }
  }
  else
  {
    digitalWrite(LED, LOW);
  }
}

int getPressedButton()
{
  for (int i = greenButton; i <= yellowButton; i++)
  {
    if (digitalRead(i) == HIGH)
    {
      return i;
    }
  }
  return -1;
}

int convertButtonToLED(int button)
{
  switch (button)
  {
    case greenButton:
      return greenLED;
      break;
    case redButton:
      return redLED;
      break;
    case blueButton:
      return blueLED;
      break;
    case yellowButton:
      return yellowLED;
      break;  
  }
  return -1;
}

boolean checkAnswer(int answer, int index)
{
  if (simonSays[index] == answer)
  {
    return true;
  }
  else
  {
    return false;
  }
}
