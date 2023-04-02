#include <Servo.h> //подключаем библиотеку для работы с сервоприводами

//задаем мин. и макс. угол поворота для каждого сервопривода,
//при необходимости их можно исправлять здесь
#define MAX_STOL 180 //большой палец (пин 10) открыт
#define MIN_STOL 0 //большой палец (пин 10) закрыт

#define MAX_INDEX_FINGER 180 //указательный палец (пин 6) закрыт
#define MIN_INDEX_FINGER 0 //указательный палец (пин 6) открыт

#define MAX_MIDDLE_FINGER 180 //средний палец (пин 5) закрыт
#define MIN_MIDDLE_FINGER 0 //средний палец (пин 5) открыт



//задаем скорости движения пальцев
//при необходимости их можно исправлять здесь
#define SPEED_STOL 2

#define SPEED_INDEX_FINGER 2

#define SPEED_MIDDLE_FINGER 3


//создаем объеты для работы с каждым мотором
Servo servo_stol; //большой палец (Сервопривод Tower Pro MG90S, пин 10 на шилде)

Servo servo_index; //указательный палец (Сервопривод Tower Pro MG995, пин 6 на шилде)
Servo servo_manip; //средний палец (Сервопривод Tower Pro MG995, пин 5 на шилде)


//переменные для хранения необработанных значаний ЭМГ-сигнала
int emg1 = 0;
int emg2 = 0;
//переменные для хранения обработанных значаний ЭМГ-сигнала (амплитуды)

//переменные для хранения пороговых значений (для определения сотояния мышцы - расслаблена/напряжена)
int threshold1 = 30;
int threshold2 = 30;
//перменные для хранения мин. и макс. значений при обработке
int max1 = 0;
int min1 = 255;
int max2 = 0;
int min2 = 255;
//служебный переменные для хранения угла поворота вала сервопривода (для каждого сервопривода) 
int t1 = 0;
int t2 = 0;
int t3 = 0;        

//функция для вычисления амплитуды ЭМГ-сигнала (обработанного значания)
/*void calc_amp() {                                                
  for (int k = 0; k < 100; k++) {   
     emg1 = analogRead(A0);
     emg2 = analogRead(A1); 
    Serial.print(emg1); 
    Serial.print(' '); 
    Serial.print(emg2);
    Serial.println(' ');                                                                  
    emg1 = map(emg1, 0, 1023, 0, 255);
    emg2 = map(emg2, 0, 1023, 0, 255);     
    if (emg1 > max1)                      
      max1 = emg1;                       
    if (emg1 < min1)                     
      min1 = emg1;  

    if (emg2 > max2)                      
      max2 = emg2;                       
    if (emg2 < min2)                     
      min2 = emg2; 
  }
  int amp1 =  0.3*amp1 + 0.7*(max1 - min1); 
  int amp2 =  0.3*amp2 + 0.7*(max2 - min2); 
  //при необходимости данные строчки можно раскомментировать для проверки значений с датчиков
  Serial.print(amp1);
  Serial.print("     "); 
  Serial.println(amp2);               
  max1 = 0;                                  
  min1 = 255;  
  max2 = 0;                                  
  min2 = 255;                                 
}
*/
void setup() {
  Serial.begin(115200);
  //указываем к каким контактам подключены сервоприводы
  servo_stol.attach(9);
  
  servo_index.attach(10);
  servo_manip.attach(11);

  
  servo_stol.write(90);
  servo_index.write(90);

  //calc_amp();

  
//  //проверка работоспособности - все пальцы на руке один раз сжимаются и разжимаются 
//  //цикл for выполняется 1 раз (если необходимо сделать несколько сжатий/разжатий, просто меняем условие: i < необходимое число)
//  for (int i = 0; i < 1; i++){
//  //все пальцы сжимаются, цикл while выполняется пока не досигнуты граничные значения угла поворота  
 // while (servo_stol.read() > MIN_STOL || 
//          
//         servo_index_finger.read() < MAX_INDEX_FINGER || 
//         servo_middle_finger.read() < MAX_MIDDLE_FINGER ){
//    //управление валом каждого сервопривода, знак + или - означает в какую сторону поворачивается вал
//    t1 = servo_stol.read() - SPEED_STOL;
//    servo_stol.write(t1);
//    
//    t3 = servo_index_finger.read() + SPEED_INDEX_FINGER;
//    servo_index_finger.write(t3);
//    t4 = servo_middle_finger.read() + SPEED_MIDDLE_FINGER;
//    servo_middle_finger.write(t4);
//    
//    delay(15);  
//  }
  //все пальца разжимаются, цикл while выполняется пока не досигнуто граничное значения угла поворота
//  while (servo_thumb1.read() < MAX_THUMB1 || 
//         servo_thumb2.read() < MAX_THUMB2 || 
//         servo_index_finger.read() > MIN_INDEX_FINGER || 
//         servo_middle_finger.read() > MIN_MIDDLE_FINGER || 
//         servo_little_ring_finfers.read() < MAX_LITTLE_RING_FINGER){
//    //управление валом каждого сервопривода, знак + или - означает в какую сторону поворачивается вал
//    t1 = servo_thumb1.read() + SPEED_THUMB1;
//    servo_thumb1.write(t1);
//    t2 = servo_thumb2.read() + SPEED_THUMB2;
//    servo_thumb2.write(t2); 
//    t3 = servo_index_finger.read() - SPEED_INDEX_FINGER;
//    servo_index_finger.write(t3);
//    t4 = servo_middle_finger.read() - SPEED_MIDDLE_FINGER;
//    servo_middle_finger.write(t4);
//    t5 = servo_little_ring_finfers.read() + SPEED_LITTLE_RING_FINGER;
//    servo_little_ring_finfers.write(t5);
//    delay(15);
//    }
//  }
}

void loop() {
  //вызываем функцию для вычисления амилитуды ЭМГ сигнала для двух датчиков
  emg1 = analogRead(A0);
     emg2 = analogRead(A1); 
     Serial.println(emg1);
     Serial.println(emg2);
          Serial.println(' ');


  
//  //если обе мышцы напряжены (значения амплитуд больше пороговых значений)
 if ( emg1 > threshold1 ){//&& amp2 > threshold2){
  //Serial.print("нагрузка есть");
//    //реализуем жест кулак - все пальцы прижаты к ладони
//    //поворачиваем каждый сервопривод для реализации жеста
//    //при этом углы поворота не должны выходить за мин. и макс. значения
   if (emg1 < 120 && servo_stol.read() > MIN_STOL){
    //Serial.print("правая рука вперед");
      t1 = servo_stol.read() - SPEED_STOL;
      servo_stol.write(t1);
   }else{

   if (emg1 > 120 && servo_stol.read() < MAX_STOL){
   // Serial.print("правая рука назад");
      t1 = servo_stol.read() + SPEED_STOL;
      servo_stol.write(t1);
   }}




   if (emg2 < 120 && servo_index.read() < MAX_INDEX_FINGER ){
      t2 = servo_index.read() - SPEED_INDEX_FINGER;
      servo_index.write(t2);
   }else{

   if (emg2 > 120 && servo_index.read() > MIN_INDEX_FINGER){
      t2 = servo_index.read() + SPEED_INDEX_FINGER;
      servo_index.write(t2);
   }}

   


}}
