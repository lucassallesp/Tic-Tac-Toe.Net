#include "main.h"

// int ref1 = 503, ref2 = 554, ref3 = 208, ref4 = 654; // Referência das juntas
// int junta1, junta2, junta3, junta4; // medida das juntas
// int erro1 = 0, erro2 = 0, erro3 = 0, erro4 = 0; // erro do cálculo de realimentação
// int kp1 = 6, kp2 = 5, kp3 = 5, kp4 = 5; // Constante de ganho do controlador
// int pwm1, pwm2, pwm3, pwm4; // Saída do controlador PWM

int iRefBase, iRefShoulder, iRefElbow, iRefWrist; // Referência das posições das juntas (0 - 5 V : 0 - 1023)
int iPotLinkBase, iPotLinkShoulder, iPotLinkElbow, iPotLinkWrist; // Entrada lida dos potenciômetros das juntas (0 - 5 V : 0 - 1023)
int iErrorBase, iErrorShoulder, iErrorElbow, iErrorWrist; // Erro entre a referência e a entrada
int iGainBase, iGainShoulder, iGainElbow, iGainWrist; // Ganho proporcional do controlador de cada junta
int iPWMBase, iPWMShoulder, iPWMElbow, iPWMWrist; // Ciclo de trabalho do PWM da ponte H de cada junta (0 - 100% : 0 - 255)
int iPWMBaseSig[2], iPWMShoulderSig[2], iPWMElbowSig[2], iPWMWristSig[2]; // Vetores de sinal dos ciclos de trabalho das juntas
unsigned int uiTimeTick; // Variável de controle de tempo

// void setup() {
//   Serial.begin(115200);
// }

void setup()
{
  // Inicialização dos valores de referência e de ganho
  iRefBase = NEUTRAL_VALUE_BASE;
  iRefShoulder = NEUTRAL_VALUE_SHOULDER;
  iRefElbow = NEUTRAL_VALUE_ELBOW;
  iRefWrist = NEUTRAL_VALUE_WRIST;
  iGainBase = 6;
  iGainShoulder = 5;
  iGainElbow = 5;
  iGainWrist = 5;
  uiTimeTick = 0;

  // Fecha a garra quando inicializa
  analogWrite(PIN_TOOL_OUTPUT_CLOCK,0);
  analogWrite(PIN_TOOL_OUTPUT_COUNTER,ARDUINO_DAC_RESOLUTION);
  delay(2000);
  analogWrite(PIN_TOOL_OUTPUT_COUNTER,0);
  
  // Início da comunicação Serial com frequência de 115200
  Serial.begin(9600);
  Serial.println(ccDeviceReady);
}

void loop()
{
  /* Início da malha de controle */
  // Leitura dos valores dos potenciômetros do manipulador
  iPotLinkBase = analogRead(PIN_BASE_INPUT);
  iPotLinkShoulder = analogRead(PIN_SHOULDER_INPUT);
  iPotLinkElbow = analogRead(PIN_ELBOW_INPUT);
  iPotLinkWrist = analogRead(PIN_WRIST_INPUT);

  // Cálculo dos erros de posição
  iErrorBase = iRefBase - iPotLinkBase;
  iErrorShoulder = iRefShoulder - iPotLinkShoulder;
  iErrorElbow = iRefElbow - iPotLinkElbow;
  iErrorWrist = iRefWrist - iPotLinkWrist;

  // Cálculo do valor de saída do controlador (PWM para Ponte H)
  iPWMBase = iGainBase * iErrorBase;
  iPWMShoulder = iGainShoulder * iErrorShoulder;
  iPWMElbow = iGainElbow * iErrorElbow;
  iPWMWrist = iGainWrist * iErrorWrist;

  // Correção de sinal do PWM e determinação de sentido de acionamento da ponte H
  // Lógica da base: direta
  if(iPWMBase > 0)
  {
    iPWMBaseSig[CLOCKWISE] = 1;
    iPWMBaseSig[COUNTER_CLOCKWISE] = 0;
  }
  else
  {
    iPWMBase = -iPWMBase;
    iPWMBaseSig[CLOCKWISE] = 0;
    iPWMBaseSig[COUNTER_CLOCKWISE] = 1;
  }

  // Lógica do ombro: inversa
  if(iPWMShoulder > 0)
  {
    iPWMShoulderSig[CLOCKWISE] = 0;
    iPWMShoulderSig[COUNTER_CLOCKWISE] = 1;
  }
  else
  {
    iPWMShoulder = -iPWMShoulder;
    iPWMShoulderSig[CLOCKWISE] = 1;
    iPWMShoulderSig[COUNTER_CLOCKWISE] = 0;
  }

  // Lógica do cotovelo: inversa
  if(iPWMElbow > 0)
  {
    iPWMElbowSig[CLOCKWISE] = 0;
    iPWMElbowSig[COUNTER_CLOCKWISE] = 1;
  }
  else
  {
    iPWMElbow = -iPWMElbow;
    iPWMElbowSig[CLOCKWISE] = 1;
    iPWMElbowSig[COUNTER_CLOCKWISE] = 0;
  }

  // Lógica do punho: inversa
  if(iPWMWrist > 0)
  {
    iPWMWristSig[CLOCKWISE] = 0;
    iPWMWristSig[COUNTER_CLOCKWISE] = 1;
  }
  else
  {
    iPWMWrist = -iPWMWrist;
    iPWMWristSig[CLOCKWISE] = 1;
    iPWMWristSig[COUNTER_CLOCKWISE] = 0;
  }

  // Correção de valor máximo do PWM
  if(iPWMBase > 255) iPWMBase = 255;
  if(iPWMShoulder > 255) iPWMShoulder = 255;
  if(iPWMElbow > 255) iPWMElbow = 255;
  if(iPWMWrist > 255) iPWMWrist = 255;

  // Ativação do PWM da Ponte H
  // Base
  analogWrite(PIN_BASE_OUTPUT_CLOCK,iPWMBase * iPWMBaseSig[CLOCKWISE]);
  analogWrite(PIN_BASE_OUTPUT_COUNTER,iPWMBase * iPWMBaseSig[COUNTER_CLOCKWISE]);

  // Ombro
  analogWrite(PIN_SHOULDER_OUTPUT_CLOCK,iPWMShoulder * iPWMShoulderSig[CLOCKWISE]);
  analogWrite(PIN_SHOULDER_OUTPUT_COUNTER,iPWMShoulder * iPWMShoulderSig[COUNTER_CLOCKWISE]);

  // Cotovelo
  analogWrite(PIN_ELBOW_OUTPUT_CLOCK,iPWMElbow * iPWMElbowSig[CLOCKWISE]);
  analogWrite(PIN_ELBOW_OUTPUT_COUNTER,iPWMElbow * iPWMElbowSig[COUNTER_CLOCKWISE]);

  // Punho
  analogWrite(PIN_WRIST_OUTPUT_CLOCK,iPWMWrist * iPWMWristSig[CLOCKWISE]);
  analogWrite(PIN_WRIST_OUTPUT_COUNTER,iPWMWrist * iPWMWristSig[COUNTER_CLOCKWISE]);
  /* Fim da malha de controle */

  /* Início da comunicação Serial e contagem de tempo */
  // Enquanto o valor de referência for diferente da posição neutra e o erro for maior ou igual que 5 o manipulador ignora a comunicação Serial
  if (iRefBase == NEUTRAL_VALUE_BASE
  && iRefShoulder == NEUTRAL_VALUE_SHOULDER
  && iRefElbow == NEUTRAL_VALUE_ELBOW
  && iRefWrist == NEUTRAL_VALUE_WRIST)
  {
    if(abs(iErrorBase) < 5
    && abs(iErrorShoulder) < 5
    && abs(iErrorElbow) < 5
    && abs(iErrorWrist) < 5)
    {
      String sCommand = "";
      if(Serial.available()) // Só lê se há alguma mensagem recebida
      {
        sCommand = Serial.readString();
      }
      if(sCommand != "")
      {
        switch(sCommand[0])
        {
          case MOVE_ARM:
          switch(sCommand[1])
          {
            case CELL1:
            iRefBase = CELL1_VALUE_BASE;
            iRefShoulder = CELL1_VALUE_SHOULDER;
            iRefElbow = CELL1_VALUE_ELBOW;
            iRefWrist = CELL1_VALUE_WRIST;
            break;

            case CELL2:
            iRefBase = CELL2_VALUE_BASE;
            iRefShoulder = CELL2_VALUE_SHOULDER;
            iRefElbow = CELL2_VALUE_ELBOW;
            iRefWrist = CELL2_VALUE_WRIST;
            break;

            case CELL3:
            iRefBase = CELL3_VALUE_BASE;
            iRefShoulder = CELL3_VALUE_SHOULDER;
            iRefElbow = CELL3_VALUE_ELBOW;
            iRefWrist = CELL3_VALUE_WRIST;
            break;

            case CELL4:
            iRefBase = CELL4_VALUE_BASE;
            iRefShoulder = CELL4_VALUE_SHOULDER;
            iRefElbow = CELL4_VALUE_ELBOW;
            iRefWrist = CELL4_VALUE_WRIST;
            break;

            case CELL5:
            iRefBase = CELL5_VALUE_BASE;
            iRefShoulder = CELL5_VALUE_SHOULDER;
            iRefElbow = CELL5_VALUE_ELBOW;
            iRefWrist = CELL5_VALUE_WRIST;
            break;

            case CELL6:
            iRefBase = CELL6_VALUE_BASE;
            iRefShoulder = CELL6_VALUE_SHOULDER;
            iRefElbow = CELL6_VALUE_ELBOW;
            iRefWrist = CELL6_VALUE_WRIST;
            break;

            case CELL7:
            iRefBase = CELL7_VALUE_BASE;
            iRefShoulder = CELL7_VALUE_SHOULDER;
            iRefElbow = CELL7_VALUE_ELBOW;
            iRefWrist = CELL7_VALUE_WRIST;
            break;

            case CELL8:
            iRefBase = CELL8_VALUE_BASE;
            iRefShoulder = CELL8_VALUE_SHOULDER;
            iRefElbow = CELL8_VALUE_ELBOW;
            iRefWrist = CELL8_VALUE_WRIST;
            break;

            case CELL9:
            iRefBase = CELL9_VALUE_BASE;
            iRefShoulder = CELL9_VALUE_SHOULDER;
            iRefElbow = CELL9_VALUE_ELBOW;
            iRefWrist = CELL9_VALUE_WRIST;
            break;

            default:
            Serial.write("Erro: posicao invalida\n");
            break;
          }
          break;

          case READ_CURRENT_POSITION:
          Serial.println(iPotLinkBase);
          Serial.println(iPotLinkShoulder);
          Serial.println(iPotLinkElbow);
          Serial.println(iPotLinkWrist);
          break;

          case OPEN_TOOL:
          analogWrite(PIN_TOOL_OUTPUT_CLOCK,ARDUINO_DAC_RESOLUTION);
          analogWrite(PIN_TOOL_OUTPUT_COUNTER,0);
          delay(2000);
          analogWrite(PIN_TOOL_OUTPUT_CLOCK,0);
          break;

          case CLOSE_TOOL:
          analogWrite(PIN_TOOL_OUTPUT_CLOCK,0);
          analogWrite(PIN_TOOL_OUTPUT_COUNTER,ARDUINO_DAC_RESOLUTION);
          delay(2000);
          analogWrite(PIN_TOOL_OUTPUT_COUNTER,0);
          break;

          default:
          Serial.write("Erro: comando invalido\n");
          break;
        }
      }
    }
  }
  else if(abs(iErrorBase) < 5
    && abs(iErrorShoulder) < 5
    && abs(iErrorElbow) < 5
    && abs(iErrorWrist) < 5)
  {
    delay(1);
    uiTimeTick++;
  }
  /* Fim da comunicação Serial */

  /* Início do código de espera de 2 segundos antes de retornar à posição neutra */
  if(uiTimeTick > 2000)
  {
    uiTimeTick = 0;
    iRefBase = NEUTRAL_VALUE_BASE;
    iRefShoulder = NEUTRAL_VALUE_SHOULDER;
    iRefElbow = NEUTRAL_VALUE_ELBOW;
    iRefWrist = NEUTRAL_VALUE_WRIST;
    Serial.println(ccDeviceReady);
  }
  /* Fim do código de espera */
}

// void loop() {
//   junta1 = analogRead(A0);
//   junta2 = analogRead(A1);
//   junta3 = analogRead(A2);
//   junta4 = analogRead(A3);

//   erro1 = ref1 - junta1;
//   erro2 = ref2 - junta2;
//   erro3 = ref3 - junta3;
//   erro4 = ref4 - junta4;

//   pwm1 = kp1*erro1;
//   pwm2 = kp2*erro2;
//   pwm3 = kp3*erro3;
//   pwm4 = kp4*erro4;
  
//   if(pwm1 > 0)
//   {
//     if(pwm1 > 255)
//     {
//       pwm1 = 255;
//     }
//     analogWrite(4,pwm1);
//     analogWrite(5,0);
//   }
//   else
//   {
//     if(pwm1 < -255)
//     {
//       pwm1 = -255;
//     }
//     analogWrite(4,0);
//     analogWrite(5,-pwm1);
//   }


//   if(pwm2 > 0)
//   {
//     if(pwm2 > 255)
//     {
//       pwm2 = 255;
//     }
//     analogWrite(6,0);
//     analogWrite(7,pwm2);
//   }
//   else
//   {
//     if(pwm2 < -255)
//     {
//       pwm2 = -255;
//     }
//     analogWrite(6,-pwm2);
//     analogWrite(7,0);
//   }

//   if(pwm3 > 0)
//   {
//     if(pwm3 > 255)
//     {
//       pwm3 = 255;
//     }
//     analogWrite(8,0);
//     analogWrite(9,pwm3);
//   }
//   else
//   {
//     if(pwm3 < -255)
//     {
//       pwm3 = -255;
//     }
//     analogWrite(8,-pwm3);
//     analogWrite(9,0);
//   }

//   if(pwm4 > 0)
//   {
//     if(pwm4 > 255)
//     {
//       pwm4 = 255;
//     }
//     analogWrite(10,0);
//     analogWrite(11,pwm4);
//   }
//   else
//   {
//     if(pwm4 < -255)
//     {
//       pwm4 = -255;
//     }
//     analogWrite(10,-pwm4);
//     analogWrite(11,0);
//   }

//   Serial.print(junta1);
//   Serial.write("\t\t");
//   Serial.println(erro1);
// }