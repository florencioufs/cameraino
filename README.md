# cameraino

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
