
  #define S_NO 3
  #define sim_time 100000 //ms/s..
  
  extern int sensor0;
  extern int sensor1;
  extern int sensor2;

  extern int robot_0_sensor_model;
  extern int robot_1_sensor_model;
  extern int robot_2_sensor_model;

  extern double response1;	
  extern double response2[S_NO];
  extern float record[S_NO][100000];
  extern int counter;
  extern int toggle;
  extern bool initial;
  extern float a;
  extern float tau[S_NO];
  extern float dd[3][3][4];
  extern float servive_val[S_NO];

  void sensor_start();
  float sensor_response(float concentration, int ch_id, int robot_id, int sensor_model);
