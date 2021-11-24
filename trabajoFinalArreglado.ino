/*
	TRABAJO PRACTICO NUMERO 2 = SISTEMA LUCES;
        
	Integrantes = Orpelli Renzo, Oliverio Santiago.
    Link trabajo= https://www.tinkercad.com/things/2rBEN4sJpuC.
    
*/
#include <LiquidCrystal.h>

// definicion pines de Leds
#define ledGIzquierdo  8
#define ledGDerecho 12
#define ledPDelantera 10
#define ledPTrasera 9
#define ledFreno 11

// definicion botones
#define gIzquierda 7
#define gDerecha  1
#define balizas 2
#define lPosicion  3
#define freno  4
#define estadoNulo  5

// definicion estadoLeds
#define luzGuinioIzquierda 1 
#define luzGuinoDerecha 2
#define luzGuinioBaliza 3
#define	luzPosicionamiento 4
#define luzApagada 0


LiquidCrystal lcd(2,3,4,5,6,7);

void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(ledGIzquierdo, OUTPUT);
  pinMode(ledPTrasera, OUTPUT);
  pinMode(ledPDelantera, OUTPUT);
  pinMode(ledFreno, OUTPUT);
  pinMode(ledGDerecho, OUTPUT);
  lcd.setCursor(0,1);
  lcd.print("LUCES: ");
  
}
int luzCaptada = 0;// INICIALIZO EL  FOTORESITOR
//  VARIABLES QUE GUARDAN LOS ESTADOS ANTERIORES DE LAS LUCES
int posicionamiento = luzApagada; // GUARDA EL VALOR NULO DE UNA LUZ PREVIAMENTE DEFINIDO CON UN DEFINE 
int estadoLedFreno = LOW; // GUARDA EL VALOR ANTERIOR DE LA LUZ DE FRENO
int estadoLedLucesPosicion = LOW; 
int valorGuineoAnterior = luzApagada;//DEFINO VARIABLE A LA QUE SE LE ASIGNAN LOS ESTADOS DE LA LUZ PARA SER UTILIZADDA EN LA FUNCION ESTADO LUCES
int valorA1Antes = 0;

void loop()
{
  int valorA1 = valorBotones();
  if(valorA1 != estadoNulo && valorA1 != valorA1Antes)
  {
      if (valorA1 == gIzquierda)
      {
            crearEfectoGuineo(valorA1);
      }

      if (valorA1 == balizas)
      {
            crearEfectoGuineo(valorA1);
      }	

      if (valorA1 == gDerecha)
      {
          crearEfectoGuineo(valorA1);
      }

      if(valorA1 == lPosicion)
      {
         posicionamiento = luzPosicionamiento;
         estadoLuz(posicionamiento);
      }
  }
  
  if (valorA1 == freno)
      {
            estadoLedFreno = HIGH;
            modoFreno(ledFreno,estadoLedFreno);
      }
      else
      {
            estadoLedFreno = LOW;
            modoFreno(ledFreno,estadoLedFreno);
      }
  
  valorA1Antes = valorA1;
  estadoLedPantalla();
  luzPosicion();
  estadoLuz(valorGuineoAnterior);
  delay(20);
}

// FUNCION VALOR BOTONES. SE ENCARGA DE LEER LA ENTRADA ANALOGICA A1 Y SEGUN EL VALOR DEL BOTON QUE SE PRESIONE LE ASIGNA UNO PREVIAMENTE 
// DECLARADO EN UN DEFINE CON LA FINALIDAD DE QUE SEA MAS ENTENDIBLE PARA EL PROGRAMADOR
int valorBotones(){
  int valorA1 = analogRead(A1);
  if(valorA1 == 512)
  {
  	return gIzquierda;
  }
  if(valorA1 ==	682 || valorA1 == 767)
  {
    return freno; 
  }
  if(valorA1 == 818)
  {
    return balizas;
  }
  if(valorA1 == 877)
  {
    return lPosicion;
  }
  if(valorA1 == 852)
  {
    return gDerecha;
  }
  return estadoNulo;
  
}

//FUNCION QUE RECIBE EL ESTADO DE UN BOTON  Y ASIGANA EL GUINEO CORRESPONDIENTE
void crearEfectoGuineo(int valorBoton)
{
  switch(valorBoton)
  {
    case gIzquierda:
    if(valorGuineoAnterior != luzGuinioIzquierda)
    {
      valorGuineoAnterior = luzGuinioIzquierda;
    }else
    {
      valorGuineoAnterior = luzApagada;
    }
    break;
    case gDerecha:
    if(valorGuineoAnterior != luzGuinoDerecha)
    {
      valorGuineoAnterior = luzGuinoDerecha;
    }else
    {
      valorGuineoAnterior = luzApagada;
    }
    break;
    case balizas:
    if(valorGuineoAnterior != luzGuinioBaliza)
    {
      valorGuineoAnterior = luzGuinioBaliza;
    }else
    {
      valorGuineoAnterior = luzApagada;
    }
  }
}

 // DECLARO NUEVOS MILLIS 
unsigned long nuevosMillis = 0;
unsigned long nuevosMillisAntes = 0;
int estadoAnteriorLed = LOW; // DEFINO VARIABLE PARA PARPADEO DE LEDS

// FUNCION QUE RECIBE EL ESTADO DE LA LUZ Y LAS EJECUTA SEGUN EL CASE
int estadoLuz(int valorBoton)
{
  nuevosMillis = millis();
  switch(valorBoton)
  {
      case luzApagada:
      digitalWrite(ledGIzquierdo, LOW);
      digitalWrite(ledGDerecho, LOW);
      lcd.setCursor(0,0);
      lcd.print(' ');
      lcd.setCursor(15,0);
      lcd.print(' ');
      break;
    case luzGuinioIzquierda:
        if(nuevosMillis - nuevosMillisAntes >= 500)
        {
            nuevosMillisAntes = nuevosMillis;
            estadoAnteriorLed= !estadoAnteriorLed;
        }
    	digitalWrite(ledGIzquierdo, estadoAnteriorLed);
        digitalWrite(ledGDerecho, LOW);
        lcd.setCursor(0,0);
    	if(estadoAnteriorLed==HIGH)lcd.print('<');
    	else lcd.print(' ');
    	lcd.setCursor(15,0);
    	lcd.print(' ');
    	
    break;
    case luzGuinioBaliza:
    	if(nuevosMillis - nuevosMillisAntes >= 500)
        {
            nuevosMillisAntes = nuevosMillis;
            estadoAnteriorLed= !estadoAnteriorLed;
        }
    	digitalWrite(ledGIzquierdo, estadoAnteriorLed);
    	digitalWrite(ledGDerecho, estadoAnteriorLed);
    	lcd.setCursor(0,0);
    	if(estadoAnteriorLed==HIGH)lcd.print('<');
    	else lcd.print(' ');
    	lcd.setCursor(15,0);
    	if(estadoAnteriorLed==HIGH)lcd.print('>');
    	else lcd.print(' ');
    break;
    case luzGuinoDerecha:
    	if(nuevosMillis - nuevosMillisAntes >= 500)
        {
            nuevosMillisAntes = nuevosMillis;
            estadoAnteriorLed= !estadoAnteriorLed;
        }
    	digitalWrite(ledGIzquierdo, LOW);
    	digitalWrite(ledGDerecho, estadoAnteriorLed);
        lcd.setCursor(0,0);
    	lcd.print(' ');
    	lcd.setCursor(15,0);
    	if(estadoAnteriorLed==HIGH)lcd.print('>');
    	else lcd.print(' ');
    break;
    case luzPosicionamiento:
       estadoLedLucesPosicion = !estadoLedLucesPosicion;
    break;
    
  }
}
// FUNCION QUE RECIBE EL PIN D DONDE ESTA CONECTADO EL ARDUINO Y EL ESTADO DE LA LED (VARIA ENTRE HIGH Y LOW)
int modoFreno(int pinLed, int estadoLed)
{
    digitalWrite(pinLed, estadoLed);
  	lcd.setCursor(7,0);
  	if(estadoLed==HIGH)
   	{
		lcd.print(" !! ");
    }
  	else
    {
      lcd.print("   ");
    }
}
//FUNCION ENCARGADA DE LEER LA ENTRADA ANALOGICA DEDICADA AL FOTORESISTOR  Y  SI ESTE CAPTA BAJA LUMINOSIDAD ESTA FUNCION SE ENCARGA DE PRENDER LAS LUCES Y APAGARLAS CUANDO LA LUMINOSIDAD ESTE ALTA
void luzPosicion(){
  luzCaptada = analogRead(A3);
  lcd.setCursor(7,1);
  int valorFotoresistor = analogRead(A3);
 
  if(valorFotoresistor <= 661){
    digitalWrite(ledPTrasera, HIGH);
    digitalWrite(ledPDelantera, HIGH);
    lcd.print("ON ");
  }
  else {
    digitalWrite(ledPTrasera, estadoLedLucesPosicion);
    digitalWrite(ledPDelantera, estadoLedLucesPosicion);
  }
}
//FUNCION QUE LEE LOS ESTADOS DE LAS VARIABLES Y SI ALGUNA DE ESTAS ESTA EN HIGH CAMBIA EL ESTADO EN LA PANTALLA
void estadoLedPantalla()
{
  lcd.setCursor(7,1);
  if(estadoAnteriorLed==HIGH || estadoLedFreno == HIGH || estadoLedLucesPosicion== HIGH)lcd.print("ON ");
  else lcd.print("OFF ");
}