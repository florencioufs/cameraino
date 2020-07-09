/* =========================================================================

      INSTITUTO FEDERAL DE EDUCAÇÃO, CIÊNCIA E TECNOLOGIA DE SERGIPE     

                        COORDENADORIA DE ELETRÔNICA                      

 -------------------------------------------------------------------------

 Disciplina: Sistemas Programáveis

 Turma     : 4oELN-N / 2012-2

 Professor : Fábio Prudente

 Aluno(s)  : Felipe de Almeida Florencio

            

 -------------------------------------------------------------------------

 Projeto   : Controle para gravação de 4 cameras de vigilância

 Data      : 12/03/2013

 Descrição : Considere um sistema de vigilância para 4 ambientes, cada

             ambiente com 1 sensor de presença (SP) e 1 câmera (cam). Os

             sinais das 4 câmeras passarão por um multiplexador (MUX) de

             vídeo, que selecionará apenas 1 sinal para o gravador de vídeo

             (REC), de acordo com os sinais CH Selector (00 a 11). O

             gravador irá gravar o video em sua entrada, enquanto o sinal

             REC/~PAUSE = 1.

            

             A função do Sistema de Controle (Arduino) é gerar os sinais

             CH Selector e REC/~PAUSE, com a seguinte funcionalidade:

             - Se nenhuma cam estiver ativa, REC/~PAUSE = 0 (pausa)

             - Se pelo menos 1 cam estiver ativa, REC/~PAUSE = 1 (grava)

             - a cam[n] somente será ativa se o SP[n] = 1, e permanecerá

               ativa por mais 20 seg, após SP[n] = 0

             - a cada 1 seg, CH Selector selecionará uma, dentre as cam

               ativas, em sequência

                                      +---------+

             cam1 ------------------->|   MUX   |         +-----------+

             cam2 ------------------->|   de    |-------->| REC video |

             cam3 ------------------->|  video  | video   +-----------+

             cam4 ------------------->|         |               ^ REC/~PAUSE

                                      +---------+               |

                                          ^ ^ CH Selector       |

                     +-------------+      | |                   |

             SP1  -->|             |      | |                   |

             SP2  -->| Sistema de  |------+ |                   |

             SP3  -->|  Controle   |--------+                   |

             SP4  -->|  (Arduino)  |                            |

                     |             |----------------------------+

                     +-------------+

 Entradas  : CH1~CH4 (simulando SP1~SP4)

 Saídas    : LED1~LED4 - indica câmeras ativas

             LED5,LED6 - CH Selector

             LED7      - REC/~PAUSE

 ========================================================================= */

/* -------------------------------------------------------------------------

                 Definições Gerais de E/S para o Shield 01               

 ------------------------------------------------------------------------- */

#define LED1  13 // Vermelho

#define LED2  12 // Amarelo

#define LED3  11 // Verde  - PWM

#define LED4  10 // Verde  - PWM

#define LED5   9 // Verde  - PWM

#define LED6   8 // Verde

#define LED7   7 // Verde

#define LED8   6 // Verde  - PWM

#define LED9   5 // = CH4  - PWM

#define LED10  4 // = CH3

#define LED11  3 // = CH2  - PWM

#define LED12  2 // = CH1

#define CH1    2 // = LED12

#define CH2    3 // = LED11

#define CH3    4 // = LED10

#define CH4    5 // = LED9

/* -------------------------------------------------------------------------

                             Entradas Analógicas                         

 ------------------------------------------------------------------------- */

#define POT    5 // (AN) Potenciômetro

#define LDR    4 // (AN) Sensor de Luminosidade

#define TMP    3 // (AN) Sensor de Temperatura LM-35

//------------------------------------------------------------------------------

#define camtime  20000   //tempo que a camera deve ficar ativada
#define CHtime   1000    //tempo de mudança do CHselector   


void setup () {

pinMode (LED1, OUTPUT);

pinMode (LED2, OUTPUT);

pinMode (LED3, OUTPUT);

pinMode (LED4, OUTPUT);

pinMode (LED5, OUTPUT);

pinMode (LED6, OUTPUT);

pinMode (LED7, OUTPUT);

pinMode (LED8, OUTPUT);

pinMode (CH1 , INPUT ); // (CH1, INPUT) ou (LED12, OUTPUT)

pinMode (CH2 , INPUT ); // (CH2, INPUT) ou (LED11, OUTPUT)

pinMode (CH3 , INPUT ); // (CH3, INPUT) ou (LED10, OUTPUT)

pinMode (CH4 , INPUT ); // (CH4, INPUT) ou (LED9, OUTPUT)

}
/*----------------------------------------------------------------------------------------

Função para ativar o REC/~PAUSE

-------------------------------------------------------------------------------------------*/
void controleREC(boolean cameraativa[]){
  if (cameraativa[0]==1 || cameraativa[1]==1 || cameraativa[2]==1 || cameraativa[3]==1)
     digitalWrite(LED7, HIGH);
  else
    digitalWrite(LED7, LOW);
}

/*----------------------------------------------------------------------------------------

Função para acender os leds do CH Selector

-------------------------------------------------------------------------------------------*/

void acenderCH(byte c){
  if (c==1 || c==3)
    digitalWrite(LED6, HIGH);
  else 
    digitalWrite(LED6, LOW);
  if (c==2 || c==3)
    digitalWrite(LED5, HIGH);
  else 
    digitalWrite(LED5, LOW);
 }
 
 /*----------------------------------------------------------------------------------------

 Funçao para controlar o CH selector, de modo que ele alterne de acordo com a camera e com 
 o tempo de 1s

-------------------------------------------------------------------------------------------*/

void controleCH(boolean cameraativa[]){
  static unsigned long time=millis()+CHtime;
  static byte estado=0;
  if(millis()-time>=CHtime){
  switch (estado){
    case 0:
        if ( cameraativa[0]==1){
          acenderCH(0);
          time=millis();
        }
        estado=1;
        break;
    case 1:
        if ( cameraativa[1]==1){
          acenderCH(1);
          time=millis();
        }
        estado=2;
        break;
    case 2:
        if (cameraativa[2]==1){
          acenderCH(2);
          time=millis();
        }
        estado=3;
        break;
    case 3 :
        if ( cameraativa[3]==1){
          acenderCH(3);
          time=millis();
        }
        estado=0;
        break;
  
  }}
  
  /*----------------------------------------------------------------------------------------

 Funçao para ativar a camera de acordo com o sensor e de acordo com o tempo de 20s

-------------------------------------------------------------------------------------------*/ 

}

void ativarCamera(boolean cameraativa[]){
  static unsigned long time[4] = {millis(), millis(), millis(), millis()};
  if (digitalRead(CH1)){
    digitalWrite(LED1, HIGH);
    cameraativa[0]=1; time[0]=millis(); }
  else {
    if (millis()-time[0]>=camtime){
      digitalWrite(LED1, LOW);
      cameraativa[0]=0;}}


  if (digitalRead(CH2)){
    digitalWrite(LED2, HIGH);
    cameraativa[1]=1; time[1]=millis();}
  else {
    if (millis()-time[1]>=camtime){
      digitalWrite(LED2, LOW);
      cameraativa[1]=0;}}


  if (digitalRead(CH3)){
    digitalWrite(LED3, HIGH);
    cameraativa[2]=1; time[2]=millis();} 
  else {
    if (millis()-time[2]>=camtime){
      digitalWrite(LED3, LOW);
      cameraativa[2]=0;}}


  if (digitalRead(CH4)){
    digitalWrite(LED4, HIGH);
    cameraativa[3]=1; time[3]=millis();}
  else {
    if (millis()-time[3]>=camtime){
      digitalWrite(LED4, LOW);
      cameraativa[3]=0;}}
  
  //delay(50);
}

void loop () {
 static boolean cameraativa[4]= {0, 0, 0, 0};
 ativarCamera(cameraativa);
 controleCH(cameraativa);
 controleREC(cameraativa);
 


}


