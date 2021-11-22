int latchPin = 3; //
int clockPin = 4; // variaveis para os registradores de deslocamento
int dataPin = 5; //

int velocidade = 6;//  deslocamento
int rpm = 7;//        descolamento

const int CVT = A0; // Define o pino que lera a saída do LM35
float temperaturaCVT; // Variável que armazenará a temperatura medida na cvt

const int MTR = A1; // Define o pino que lera a saída do LM35
float temperaturaMTR; // Variável que armazenará a temperatura medida no motor

int bomba1 = 8;//
int bomba2 = 10;// combustivel
int bomba3 = 11;//
int bomba4 = 12;//

int dezena;// calculo para display da velocidade
int unidade;//

int ss=0,ps=0,rota=0;   // variaveis para calculos da velocidade na roda
int ssm=0,psm=0,rotam=0;// variaveis para calculos do RPM no volante do motor
int raio=0,raiom=0;     // raio da roda e raio do volante do motor A DEFINIR                 
int i;

//                        10            4      4       4          7            7
int tela[40] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
             //--rpm---------------/--comb-/--cvt--/--mtr--/----dezena---/----unid-----/
void setup()
 
{
  
  pinMode(latchPin, OUTPUT);//
  pinMode(clockPin, OUTPUT);// setando os pinos para os registradores de deslocamento
  pinMode(dataPin, OUTPUT);//
}

void loop() 

{
  

//LM35
    //CVT
    temperaturaCVT = (float(analogRead(CVT))*5/(1023))/0.01;
      if (temperaturaCVT<=25)                    //acender 1 led
         {
          tela[28]=1;
         tela[27]=0;
         tela[26]=0;
         tela[25]=0;}
      if (temperaturaCVT>25&&temperaturaCVT<=55) //acender 2 leds
         {
          tela[28]=1;
         tela[27]=1;
         tela[26]=0;
         tela[25]=0;}          
      if (temperaturaCVT>55&&temperaturaCVT<=80) //acender 3 leds
         {
          tela[28]=1;
         tela[27]=1;
         tela[26]=1;
         tela[25]=0;}
      if (temperaturaCVT>80)                    //acender 4 leds
         {
          tela[28]=1;
         tela[27]=1;
         tela[26]=1;
         tela[25]=1;}  
    //MTR
    temperaturaMTR = (float(analogRead(MTR))*5/(1023))/0.01; 
      if (temperaturaCVT<=25)                    //acender 1 led
         {
          tela[24]=1;
         tela[23]=0;
         tela[22]=0;
         tela[21]=0;}
      if (temperaturaCVT>25&&temperaturaCVT<=55) //acender 2 leds
         {
          tela[24]=1;
         tela[23]=1;
         tela[22]=0;
         tela[21]=0;}          
      if (temperaturaCVT>55&&temperaturaCVT<=80) //acender 3 leds
         {
          tela[24]=1;
         tela[23]=1;
         tela[22]=1;
         tela[21]=0;}
      if (temperaturaCVT>80)                    //acender 4 leds
         {
          tela[24]=1;
         tela[23]=1;
         tela[22]=1;
         tela[21]=1;}               

//BOMBA
    if (digitalRead(bomba1==HIGH&&bomba2==HIGH&&bomba3==HIGH&&bomba4==HIGH))//bug
         {
          tela[20]=0;
         tela[19]=0;
         tela[18]=0;
         tela[17]=0;}
    if (digitalRead(bomba1==HIGH&&bomba2==LOW&&bomba3==LOW&&bomba4==LOW))//acende 1 led de baixo nivel
         {
          tela[20]=1;
         tela[19]=0;
         tela[18]=0;
         tela[17]=0;}
    if (digitalRead(bomba1==HIGH&&bomba2==HIGH&&bomba3==LOW&&bomba4==LOW))//acende 2 led de nivel medio
         {
          tela[20]=1;
         tela[19]=1;
         tela[18]=0;
         tela[17]=0;}
    if (digitalRead(bomba1==LOW&&bomba2==HIGH&&bomba3==LOW&&bomba4==LOW))// acende 2 led de nivel definitivamente medio
         {
          tela[20]=1;
         tela[19]=1;
         tela[18]=0;
         tela[17]=0;}
    if (digitalRead(bomba1==LOW&&bomba2==HIGH&&bomba3==HIGH&&bomba4==LOW))// acende 3 led de nivel medio alto
         {
          tela[20]=1;
         tela[19]=1;
         tela[18]=1;
         tela[17]=0;}
    if (digitalRead(bomba1==LOW&&bomba2==LOW&&bomba3==HIGH&&bomba4==LOW)) // acende 3 led de nivel medio alto definitivo
         {
          tela[20]=1;
         tela[19]=1;
         tela[18]=1;
         tela[17]=0;}
    if (digitalRead(bomba1==LOW&&bomba2==LOW&&bomba3==HIGH&&bomba4==HIGH))// acende 4 led de nivel alto
         {
          tela[20]=1;
         tela[19]=1;
         tela[18]=1;
         tela[17]=1;}
    if (digitalRead(bomba1==LOW&&bomba2==LOW&&bomba3==LOW&&bomba4==HIGH))// acende 4 led de nivel alto definitivo
         {
          tela[20]=1;
         tela[19]=1;
         tela[18]=1;
         tela[17]=1;}
    if (digitalRead(bomba1==LOW&&bomba2==LOW&&bomba3==LOW&&bomba4==LOW))// a boia não esta no lugar
         {
          tela[20]=0;
         tela[19]=0;
         tela[18]=0;
         tela[17]=0;}



// velocidade e rpm

    //calculo da velocidade e rpm
    
    //flag no sensor, impede que o programa leia estado de alto quando o botao ja foi solto.
        if(ps == 0 && ss == HIGH)   
          {
            rota++; //incrementa a variavel rota para informar q o pneu deu uma volta
            ps=1;
          }
        if(ps == 0 && ss == LOW)
          {
            ps=0;
          }
        if(ps == 1 && ss == HIGH)
          {
            ps=1;
          }
        if(ps == 1 && ss == LOW)
          {
            ps=0;
          }

        if(psm == 0 && ssm == HIGH)
          {
            rotam++;
            psm=1;
          }
        if(psm == 0 && ssm == LOW)
          {
            psm=0;
          }
        if(psm == 1 && ssm == HIGH)
          {
            psm=1;
          }
        if(psm == 1 && ssm == LOW)
          {
            psm=0;
          }

      if (millis()%250 == 0)// a cada 0.25 segundo o programa imprime as variaveis e depois reseta os dados
      { 
      
      velocidade=rota*2*3.14*raio;  //  quantidade de vezes que a roda girou vezes o comprimento da circunferencia
      velocidade=velocidade/0.25;    //  espaço pelo tempo de atualizacao dos dados que eh 0.25 segundos
      velocidade=velocidade*3.6;    //  tranformando m/s em km/h

      rpm=rotam*4*60;               // quantidade de vezes que o volante do motor girou em .25 segundos vezes 4 vezes 60 para sair os rpm
      
      
    //display da velocidade
    
          dezena = velocidade/10;
            if (dezena=0){  //escreve o 0 na casa da dezena
              tela[1]=0;
              tela[2]=1;
              tela[3]=0;
              tela[4]=0;
              tela[5]=0;
              tela[6]=0;
              tela[7]=0;}
            if (dezena=1){  //escreve o 1 na casa da dezena
              tela[1]=1;
              tela[2]=1;
              tela[3]=1;
              tela[4]=1;
              tela[5]=0;
              tela[6]=0;
              tela[7]=1;}
            if (dezena=2){  //escreve o 2 na casa da dezena
              tela[1]=1;
              tela[2]=0;
              tela[3]=0;
              tela[4]=0;
              tela[5]=1;
              tela[6]=0;
              tela[7]=0;}
            if (dezena=3){  //escreve o 3 na casa da dezena
              tela[1]=1;
              tela[2]=0;
              tela[3]=1;
              tela[4]=0;
              tela[5]=0;
              tela[6]=0;
              tela[7]=0;}
            if (dezena=4){  //escreve o 4 na casa da dezena
              tela[1]=0;
              tela[2]=0;
              tela[3]=1;
              tela[4]=1;
              tela[5]=0;
              tela[6]=0;
              tela[7]=1;}
            if (dezena=5){  //escreve o 5 na casa da dezena
              tela[1]=0;
              tela[2]=0;
              tela[3]=1;
              tela[4]=0;
              tela[5]=0;
              tela[6]=1;
              tela[7]=0;}
            if (dezena=6){  //escreve o 6 na casa da dezena
              tela[1]=0;
              tela[2]=0;
              tela[3]=0;
              tela[4]=0;
              tela[5]=0;
              tela[6]=1;
              tela[7]=0;}
            if (dezena=7){  //escreve o 7 na casa da dezena
              tela[1]=1;
              tela[2]=1;
              tela[3]=1;
              tela[4]=1;
              tela[5]=0;
              tela[6]=0;
              tela[7]=0;}
            if (dezena=8){  //escreve o 8 na casa da dezena
              tela[1]=0;
              tela[2]=0;
              tela[3]=0;
              tela[4]=0;
              tela[5]=0;
              tela[6]=0;
              tela[7]=0;}
            if (dezena=9){  //escreve o 9 na casa da dezena              
              tela[1]=0;
              tela[2]=0;
              tela[3]=1;
              tela[4]=1;
              tela[5]=0;
              tela[6]=0;
              tela[7]=0;}
        
            unidade = velocidade%10;
            if (unidade=0){  //escreve o 0 na casa da unidade
              tela[9]=0;
              tela[10]=1;
              tela[11]=0;
              tela[12]=0;
              tela[13]=0;
              tela[14]=0;
              tela[15]=0;}
            if (unidade=1){  //escreve o 1 na casa da unidade
              tela[9]=1;
              tela[10]=1;
              tela[11]=1;
              tela[12]=1;
              tela[13]=0;
              tela[14]=0;
              tela[15]=1;}
            if (unidade=2){  //escreve o 2 na casa da unidade
              tela[9]=1;
              tela[10]=0;
              tela[11]=0;
              tela[12]=0;
              tela[13]=1;
              tela[14]=0;
              tela[15]=0;}
            if (unidade=3){  //escreve o 3 na casa da unidade
              tela[9]=1;
              tela[10]=0;
              tela[11]=1;
              tela[12]=0;
              tela[13]=0;
              tela[14]=0;
              tela[15]=0;}
            if (unidade=4){  //escreve o 4 na casa da unidade
              tela[9]=0;
              tela[10]=0;
              tela[11]=1;
              tela[12]=1;
              tela[13]=0;
              tela[14]=0;
              tela[15]=1;}
            if (unidade=5){  //escreve o 5 na casa da unidade
              tela[9]=0;
              tela[10]=0;
              tela[11]=1;
              tela[12]=0;
              tela[13]=0;
              tela[14]=1;
              tela[15]=0;}
            if (unidade=6){  //escreve o 6 na casa da unidade
              tela[9]=0;
              tela[10]=0;
              tela[11]=0;
              tela[12]=0;
              tela[13]=0;
              tela[14]=1;
              tela[15]=0;}
            if (unidade=7){  //escreve o 7 na casa da unidade
              tela[9]=1;
              tela[10]=1;
              tela[11]=1;
              tela[12]=1;
              tela[13]=0;
              tela[14]=0;
              tela[15]=0;}
            if (unidade=8){  //escreve o 8 na casa da unidade
              tela[9]=0;
              tela[10]=0;
              tela[11]=0;
              tela[12]=0;
              tela[13]=0;
              tela[14]=0;
              tela[15]=0;}
            if (unidade=9){  //escreve o 9 na casa da unidade
              tela[9]=0;
              tela[10]=0;
              tela[11]=1;
              tela[12]=1;
              tela[13]=0;
              tela[14]=0;
              tela[15]=0;}      
      
      
    //display de rpm

            if (rpm<=400){               //acende 1 led
              tela[37]=1; 
              tela[36]=0;
              tela[35]=0;
              tela[34]=0;
              tela[33]=0;
              tela[32]=0;
              tela[31]=0;
              tela[30]=0;
              tela[29]=0;
              }
            if (rpm>400&&rpm<=800){      //acende 2 led
              tela[37]=1; 
              tela[36]=1;
              tela[35]=0;
              tela[34]=0;
              tela[33]=0;
              tela[32]=0;
              tela[31]=0;
              tela[30]=0;
              tela[29]=0;
              }
            if (rpm>800&&rpm<=1200){     //acende 3 led
              tela[37]=1; 
              tela[36]=1;
              tela[35]=1;
              tela[34]=0;
              tela[33]=0;
              tela[32]=0;
              tela[31]=0;
              tela[30]=0;
              tela[29]=0;
              }
            if (rpm>1200&&rpm<=1400){    //acende 4 led
              tela[37]=1; 
              tela[36]=1;
              tela[35]=1;
              tela[34]=1;
              tela[33]=0;
              tela[32]=0;
              tela[31]=0;
              tela[30]=0;
              tela[29]=0;
              }
            if (rpm>1400&&rpm<=1800){    //acende 5 led
              tela[37]=1; 
              tela[36]=1;
              tela[35]=1;
              tela[34]=1;
              tela[33]=1;
              tela[32]=0;
              tela[31]=0;
              tela[30]=0;
              tela[29]=0;
              }
            if (rpm>1800&&rpm<=2400){    //acende 6 led
              tela[37]=1; 
              tela[36]=1;
              tela[35]=1;
              tela[34]=1;
              tela[33]=1;
              tela[32]=1;
              tela[31]=0;
              tela[30]=0;
              tela[29]=0;
              }
            if (rpm>2800&&rpm<=3200){    //acende 7 led
              tela[37]=1; 
              tela[36]=1;
              tela[35]=1;
              tela[34]=1;
              tela[33]=1;
              tela[32]=1;
              tela[31]=1;
              tela[30]=0;
              tela[29]=0;
              }
            if (rpm>3200&&rpm<=3600){    //acende 8 led
              tela[37]=1; 
              tela[36]=1;
              tela[35]=1;
              tela[34]=1;
              tela[33]=1;
              tela[32]=1;
              tela[31]=1;
              tela[30]=1;
              tela[29]=0;
              }
            if (rpm>3600){    //acende 9 led
              tela[37]=1; 
              tela[36]=1;
              tela[35]=1;
              tela[34]=1;
              tela[33]=1;
              tela[32]=1;
              tela[31]=1;
              tela[30]=1;
              tela[29]=1;
              }
        
    // descarga de dados nos registradores de deslocamento
    
    digitalWrite(latchPin, LOW);
    digitalWrite(clockPin, LOW);
    for(i=0;i<41;i++)
        {
        dataPin=tela[i];
        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
        }
    digitalWrite(latchPin, HIGH);
    
    rpm=0;              // zera as variaveis de velocidade e rpm a cada .25 segundos, o fim do if
    velocidade=0;       //
    rota=0;             // zera as rotacoes da roda e do volante do motor para novo calculo
    rotam=0;            //
     }
}
