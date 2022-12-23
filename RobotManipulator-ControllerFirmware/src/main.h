/* Portas:
  Entradas: (res.: 10 bits)
  A0 - Medida do ângulo da base:
  Última medição:
  Mínimo (Esquerda): 110;
  Centro: 480;
  Máximo (Direita): 860.

  A1 - Medida do ângulo do ombro:
  Última medição:
  Mínimo (Horizontal): 715;
  Máximo (Vertical): 475.

  A2 - Medida do ângulo do cotovelo:
  Última medição:
  Mínimo (Fechado): 600;
  Centro (Alinhado ao braço): 244;
  Máximo: 130;

  A3 - Medidda do ângulo do manipulador (punho):
  Última medição:
  Mínimo (Posição interna): 690;
  Centro (Alinhado ao eixo do antebraço): 440;
  Máximo (Posição externa): 210.

  Saídas: (res.: 8 bits)
  Garra: 2 (abre), 3 (fecha)
  Base: 4 (horário) 5 (anti-horário)
  Ombro: 6 (horário/elevação) 7 (anti-horário/descida)
  Cotovelo: 8 (horário/elevação) 9 (anti-horário/descida)
  Punho: 10 (horário/elevação) 11 (anti-horário/descida)
*/

/*
  O arduino se comunicará com o aplicativo pela interface Serial, com a banda de 9600
  O padrão de envio e recebimento de dados se dará por meio do envio de pacotes
  de dados do tipo String com a seguinte sintaxe: "CP", onde:
  - C é o comando recebido do aplicativo (pode ser 'r','o','c' ou 'm');
  - P é a posição em que o símbolo deverá ser desenhado (pode ser de '1' a '9' ou 'n').    
*/

/*
  Mapeamento do tabuleiro do jogo:
  
  n

  1 | 2 | 3
  ---------
  4 | 5 | 6
  ---------
  7 | 8 | 9

*/

/*
  Lógica da ponte H:
 - Base: direta
 - Ombro: inversa
 - Cotovelo: inversa
 - Punho: inversa
 */

#include <Arduino.h>

#define PIN_BASE_INPUT A0 // Potenciômetro da base do manipulador está ligado no pino A0 do arduino
#define PIN_SHOULDER_INPUT A1 // Potenciômetro do ombro do manipulador está ligado no pino A1 do arduino
#define PIN_ELBOW_INPUT A2 // Potenciômetro do cotovelo do manipulador está ligado no pino A2 do arduino
#define PIN_WRIST_INPUT A3 // Potenciômetro da punho do manipulador está ligado no pino A3 do arduino
#define PIN_BASE_OUTPUT_CLOCK 4 // Ponte H do motor da base (sentido horário), ligada no pino 4 do arduino
#define PIN_BASE_OUTPUT_COUNTER 5 // Ponte H do motor da base (sentido anti-horário), ligada no pino 5 do arduino
#define PIN_SHOULDER_OUTPUT_CLOCK 6 // Ponte H do motor do ombro (sentido horário), ligada no pino 6 do arduino
#define PIN_SHOULDER_OUTPUT_COUNTER 7 // Ponte H do motor do ombro (sentido anti-horário), ligada no pino 7 do arduino
#define PIN_ELBOW_OUTPUT_CLOCK 8 // Ponte H do motor do cotovelo (sentido horário), ligada no pino 8 do arduino
#define PIN_ELBOW_OUTPUT_COUNTER 9 // Ponte H do motor do cotovelo (sentido anti-horário), ligada no pino 9 do arduino
#define PIN_WRIST_OUTPUT_CLOCK 10 // Ponte H do motor do punho (sentido horário), ligada no pino 10 do arduino
#define PIN_WRIST_OUTPUT_COUNTER 11 // Ponte H do motor do punho (sentido anti-horário), ligada no pino 11 do arduino
#define PIN_TOOL_OUTPUT_CLOCK 2 // Ponte H do motor da garra (sentido horário), ligada no pino 2 do arduino
#define PIN_TOOL_OUTPUT_COUNTER 3 // Ponte H do motor da garra (sentido anti-horário), ligada no pino 3 do arduino
#define CLOCKWISE 0 // Índice horário do vetor de sinal do PWM da ponte H
#define COUNTER_CLOCKWISE 1 // Índice anti-horário do vetor de sinal do PWM da ponte H

#define ARDUINO_DAC_RESOLUTION 255 // Limite do PID não deve ultrapassar resolução do conversor digital-analógico do arduino 

const char ccDeviceReady = 'r'; // O arduino manda a letra r na porta serial comunicando que terminou sua última tarefa

enum cell_pot_values_t // Enumerador que guarda valores dos potenciômetros correspondentes a cada posição do manipulador
{

  // Valores de potenciômetro da posição neutra
  NEUTRAL_VALUE_BASE = 503,
  NEUTRAL_VALUE_SHOULDER = 554,
  NEUTRAL_VALUE_ELBOW = 208,
  NEUTRAL_VALUE_WRIST = 654,

  CELL1_VALUE_BASE = 450,
  CELL1_VALUE_SHOULDER = 540,
  CELL1_VALUE_ELBOW = 360,
  CELL1_VALUE_WRIST = 590,

  CELL2_VALUE_BASE = 475,
  CELL2_VALUE_SHOULDER = 540,
  CELL2_VALUE_ELBOW = 360,
  CELL2_VALUE_WRIST = 590,

  CELL3_VALUE_BASE = 498,
  CELL3_VALUE_SHOULDER = 540,
  CELL3_VALUE_ELBOW = 360,
  CELL3_VALUE_WRIST = 590,

  CELL4_VALUE_BASE = 442,
  CELL4_VALUE_SHOULDER = 490,
  CELL4_VALUE_ELBOW = 425,
  CELL4_VALUE_WRIST = 575,

  CELL5_VALUE_BASE = 474,
  CELL5_VALUE_SHOULDER = 490,
  CELL5_VALUE_ELBOW = 435,
  CELL5_VALUE_WRIST = 575,

  CELL6_VALUE_BASE = 500,
  CELL6_VALUE_SHOULDER = 490,
  CELL6_VALUE_ELBOW = 425,
  CELL6_VALUE_WRIST = 575,

  CELL7_VALUE_BASE = 430,
  CELL7_VALUE_SHOULDER = 470,
  CELL7_VALUE_ELBOW = 460,
  CELL7_VALUE_WRIST = 580,

  CELL8_VALUE_BASE = 469,
  CELL8_VALUE_SHOULDER = 470,
  CELL8_VALUE_ELBOW = 460,
  CELL8_VALUE_WRIST = 580,

  CELL9_VALUE_BASE = 510,
  CELL9_VALUE_SHOULDER = 470,
  CELL9_VALUE_ELBOW = 460,
  CELL9_VALUE_WRIST = 580,
};

enum serial_commands_t
{
  READ_CURRENT_POSITION = 'r',
  OPEN_TOOL = 'o',
  CLOSE_TOOL = 'c',
  MOVE_ARM = 'm',
};

enum serial_move_coords_t
{
  NEUTRAL = 'n',
  CELL1 = '1',
  CELL2 = '2',
  CELL3 = '3',
  CELL4 = '4',
  CELL5 = '5',
  CELL6 = '6',
  CELL7 = '7',
  CELL8 = '8',
  CELL9 = '9',
};