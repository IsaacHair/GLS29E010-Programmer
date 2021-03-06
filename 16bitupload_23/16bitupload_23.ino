 #define LEN 176 //********make sure to get length correct
 #define JMP 0
 #define OUT 2
 #define ADR 4
 #define BUF 6
 #define I 0
 #define R 1
uint16_t prog[LEN][4]={
    {0x0000, ADR+0, 0xffff, 0x0001}, //reset
    {0x0001, ADR+1, 0x0000, 0x0002},
    {0x0002, BUF+1, 0x0000, 0x0003},

    {0x0003, ADR+0, 0xffff, 0x0004},
    {0x0004, ADR+1, 0x0001, 0x0005},
    {0x0005, BUF+1, 0x0000, 0x0006},
    
    {0x0006, ADR+0, 0xffff, 0x0007},
    {0x0007, ADR+1, 0x0002, 0x0008},
    {0x0008, BUF+1, 0x0000, 0x0009},

    {0x0009, ADR+0, 0xffff, 0x000a},
    {0x000a, ADR+1, 0x0003, 0x000b},
    {0x000b, BUF+1, 0x0000, 0x0010},

    {0x0010, OUT+0, 0xfff0, 0x1000}, //fix output

    {0x1000, ADR+0, 0xffff, 0x1001}, //add 1
    {0x1001, ADR+1, 0x0000, 0x1002},
    {0x1002, JMP+R, 0x0000, 0x1004},
    {0x1004, BUF+1, 0x0000, 0x1f00},
    {0x1005, BUF+0, 0x0000, 0x1010},

    {0x1010, ADR+0, 0xffff, 0x1011},
    {0x1011, ADR+1, 0x0001, 0x1012},
    {0x1012, JMP+R, 0x0000, 0x1014},
    {0x1014, BUF+1, 0x0000, 0x1f04},
    {0x1015, BUF+0, 0x0000, 0x1020},

    {0x1020, ADR+0, 0xffff, 0x1021},
    {0x1021, ADR+1, 0x0002, 0x1022},
    {0x1022, JMP+R, 0x0000, 0x1024},
    {0x1024, BUF+1, 0x0000, 0x1f08},
    {0x1025, BUF+0, 0x0000, 0x1030},

    {0x1030, ADR+0, 0xffff, 0x1031},
    {0x1031, ADR+1, 0x0003, 0x1032},
    {0x1032, JMP+R, 0x0000, 0x1034},
    {0x1034, BUF+1, 0x0000, 0x2000},
    {0x1035, BUF+0, 0x0000, 0x2000},

    {0x1f00, OUT+1, 0x0000, 0x1f01}, //equalize clock cycles spent to add
    {0x1f01, OUT+1, 0x0000, 0x1f02},
    {0x1f02, OUT+1, 0x0000, 0x1f03},
    {0x1f03, OUT+1, 0x0000, 0x1f04},
    
    {0x1f04, OUT+1, 0x0000, 0x1f05},
    {0x1f05, OUT+1, 0x0000, 0x1f06},
    {0x1f06, OUT+1, 0x0000, 0x1f07},
    {0x1f07, OUT+1, 0x0000, 0x1f08},
    
    {0x1f08, OUT+1, 0x0000, 0x1f09},
    {0x1f09, OUT+1, 0x0000, 0x1f0a},
    {0x1f0a, OUT+1, 0x0000, 0x1f0b},
    {0x1f0b, OUT+1, 0x0000, 0x2000},

    {0x2000, ADR+0, 0xffff, 0x2001}, //initialization
    {0x2001, ADR+1, 0x1f00, 0x2002},
    {0x2002, BUF+0, 0x0000, 0x2010},

    {0x2010, ADR+0, 0xffff, 0x2011}, //getting values
    {0x2011, ADR+1, 0x0000, 0x2012},
    {0x2012, JMP+R, 0x0000, 0x2014},
    {0x2014, OUT+1, 0x0000, 0x3000},
    {0x2015, OUT+1, 0x0000, 0x4000},

    {0x2020, ADR+0, 0xffff, 0x2021},
    {0x2021, ADR+1, 0x0001, 0x2022},
    {0x2022, JMP+R, 0x0000, 0x2024},
    {0x2024, OUT+1, 0x0000, 0x3000},
    {0x2025, OUT+1, 0x0000, 0x4000},

    {0x2030, ADR+0, 0xffff, 0x2031},
    {0x2031, ADR+1, 0x0002, 0x2032},
    {0x2032, JMP+R, 0x0000, 0x2034},
    {0x2034, OUT+1, 0x0000, 0x3000},
    {0x2035, OUT+1, 0x0000, 0x4000},

    {0x2040, ADR+0, 0xffff, 0x2041},
    {0x2041, ADR+1, 0x0003, 0x2042},
    {0x2042, JMP+R, 0x0000, 0x2044},
    {0x2044, OUT+1, 0x0000, 0x3000},
    {0x2045, OUT+1, 0x0000, 0x4000},


    {0x3000, ADR+0, 0xffff, 0x3001}, //if the value is a zero - bit 0
    {0x3001, ADR+1, 0x1f00, 0x3002},
    {0x3002, JMP+R, 0x0000, 0x3004},
    {0x3004, OUT+1, 0x0000, 0x3006}, //this is end of path
    {0x3005, OUT+1, 0x0000, 0x300d}, //this is not end of path

    {0x3006, BUF+1, 0x0000, 0x3007}, //set this as not being end
    {0x3007, ADR+0, 0xfff1, 0x3008},
    {0x3008, ADR+1, 0x1f10, 0x3009},
    {0x3009, BUF+0, 0x0000, 0x300a}, //set what will be the next address (by changing the 1 bit that is being worked on right now) as the end
    {0x300a, ADR+0, 0xfff1, 0x300b},
    {0x300b, ADR+1, 0x1000, 0x300c},
    {0x300c, BUF+0, 0x0000, 0x2020}, //write value so the program knows what to make the next address

    {0x300d, ADR+0, 0xfff0, 0x300e},
    {0x300e, ADR+1, 0x1000, 0x300f},
    {0x300f, JMP+R, 0x0000, 0x3010}, //seeing where to lead path as end
    {0x3010, ADR+0, 0x0001, 0x3100},
    {0x3011, ADR+1, 0x0001, 0x3100},


    {0x3100, ADR+0, 0xfff0, 0x3101}, //bit 1
    {0x3101, ADR+1, 0x1f10, 0x3102},
    {0x3102, JMP+R, 0x0000, 0x3104},
    {0x3104, OUT+1, 0x0000, 0x3106}, //this is end of path
    {0x3105, OUT+1, 0x0000, 0x310d}, //this is not end of path

    {0x3106, BUF+1, 0x0000, 0x3107}, //set this as not being end
    {0x3107, ADR+0, 0xfff2, 0x3108},
    {0x3108, ADR+1, 0x1f20, 0x3109},
    {0x3109, BUF+0, 0x0000, 0x310a}, //set what will be the next address (by changing the 1 bit that is being worked on right now) as the end
    {0x310a, ADR+0, 0xfff2, 0x310b},
    {0x310b, ADR+1, 0x1010, 0x310c},
    {0x310c, BUF+0, 0x0000, 0x2030}, //write value so the program knows what to make the next address

    {0x310d, ADR+0, 0xfff0, 0x310e},
    {0x310e, ADR+1, 0x1010, 0x310f},
    {0x310f, JMP+R, 0x0000, 0x3110}, //seeing where to lead path as end
    {0x3110, ADR+0, 0x0002, 0x3200},
    {0x3111, ADR+1, 0x0002, 0x3200},


    {0x3200, ADR+0, 0xfff0, 0x3201}, //bit 2
    {0x3201, ADR+1, 0x1f20, 0x3202},
    {0x3202, JMP+R, 0x0000, 0x3204},
    {0x3204, OUT+1, 0x0000, 0x3206}, //this is end of path
    {0x3205, OUT+1, 0x0000, 0x320d}, //this is not end of path

    {0x3206, BUF+1, 0x0000, 0x3207}, //set this as not being end
    {0x3207, ADR+0, 0xfff4, 0x3208},
    {0x3208, ADR+1, 0x1f30, 0x3209},
    {0x3209, BUF+0, 0x0000, 0x320a}, //set what will be the next address (by changing the 1 bit that is being worked on right now) as the end
    {0x320a, ADR+0, 0xfff4, 0x320b},
    {0x320b, ADR+1, 0x1020, 0x320c},
    {0x320c, BUF+0, 0x0000, 0x2040}, //write value so the program knows what to make the next address

    {0x320d, ADR+0, 0xfff0, 0x320e},
    {0x320e, ADR+1, 0x1020, 0x320f},
    {0x320f, JMP+R, 0x0000, 0x3210}, //seeing where to lead path as end
    {0x3210, ADR+0, 0x0004, 0x3300},
    {0x3211, ADR+1, 0x0004, 0x3300},


    {0x3300, ADR+0, 0xfff0, 0x3301}, //add on last bit and clear rest of number
    {0x3301, ADR+1, 0x1030, 0x5000},


    {0x4000, ADR+0, 0xffff, 0x4001}, //if the value is a one - bit 0
    {0x4001, ADR+1, 0x1f00, 0x4002},
    {0x4002, JMP+R, 0x0000, 0x4004},
    {0x4004, OUT+1, 0x0000, 0x4006}, //this is the end of the path
    {0x4005, OUT+1, 0x0000, 0x400d}, //this is not the end of the path

    {0x4006, BUF+1, 0x0000, 0x4007}, //set this as not being the end
    {0x4007, ADR+0, 0xfff1, 0x4008},
    {0x4008, ADR+1, 0x1f11, 0x4009},
    {0x4009, BUF+0, 0x0000, 0x400a}, //set what will be the next address (by changing the 1 bit that is worked on right now) as the end
    {0x400a, ADR+0, 0xfff1, 0x400b},
    {0x400b, ADR+1, 0x1000, 0x400c},
    {0x400c, BUF+1, 0x0000, 0x2020}, //write value so program knows where to make next address

    {0x400d, ADR+0, 0xfff0, 0x400e},
    {0x400e, ADR+1, 0x1000, 0x400f},
    {0x400f, JMP+R, 0x0000, 0x4010}, //seeing where to lead path as end
    {0x4010, ADR+0, 0x0001, 0x4100},
    {0x4011, ADR+1, 0x0001, 0x4100},


    {0x4100, ADR+0, 0xfff0, 0x4101}, //bit 1
    {0x4101, ADR+1, 0x1f10, 0x4102},
    {0x4102, JMP+R, 0x0000, 0x4104},
    {0x4104, OUT+1, 0x0000, 0x4106}, //this is the end of the path
    {0x4105, OUT+1, 0x0000, 0x410d}, //this is not the end of the path

    {0x4106, BUF+1, 0x0000, 0x4107}, //set this as not being the end
    {0x4107, ADR+0, 0xfff2, 0x4108},
    {0x4108, ADR+1, 0x1f22, 0x4109},
    {0x4109, BUF+0, 0x0000, 0x410a}, //set what will be the next address (by changing the 1 bit that is worked on right now) as the end
    {0x410a, ADR+0, 0xfff2, 0x410b},
    {0x410b, ADR+1, 0x1010, 0x410c},
    {0x410c, BUF+1, 0x0000, 0x2030}, //write value so program knows where to make next address

    {0x410d, ADR+0, 0xfff0, 0x410e},
    {0x410e, ADR+1, 0x1010, 0x410f},
    {0x410f, JMP+R, 0x0000, 0x4110}, //seeing where to lead path as end
    {0x4110, ADR+0, 0x0002, 0x4200},
    {0x4111, ADR+1, 0x0002, 0x4200},


    {0x4200, ADR+0, 0xfff0, 0x4201}, //bit 2
    {0x4201, ADR+1, 0x1f20, 0x4202},
    {0x4202, JMP+R, 0x0000, 0x4204},
    {0x4204, OUT+1, 0x0000, 0x4206}, //this is the end of the path
    {0x4205, OUT+1, 0x0000, 0x420d}, //this is not the end of the path

    {0x4206, BUF+1, 0x0000, 0x4207}, //set this as not being the end
    {0x4207, ADR+0, 0xfff4, 0x4208},
    {0x4208, ADR+1, 0x1f34, 0x4209},
    {0x4209, BUF+0, 0x0000, 0x420a}, //set what will be the next address (by changing the 1 bit that is worked on right now) as the end
    {0x420a, ADR+0, 0xfff4, 0x420b},
    {0x420b, ADR+1, 0x1020, 0x420c},
    {0x420c, BUF+1, 0x0000, 0x2040}, //write value so program knows where to make next address
    
    {0x420d, ADR+0, 0xfff0, 0x420e},
    {0x420e, ADR+1, 0x1020, 0x420f},
    {0x420f, JMP+R, 0x0000, 0x4210}, //seeing where to lead path as end
    {0x4210, ADR+0, 0x0004, 0x4300},
    {0x4211, ADR+1, 0x0004, 0x4300},


    {0x4300, ADR+0, 0xfff0, 0x4301}, //set address properly and write last bit of address
    {0x4301, ADR+1, 0x1038, 0x5000},


    {0x5000, JMP+I, 0x0001, 0x5000},
    {0x5001, OUT+1, 0x0000, 0x1000},
    };


void setup() {
  int i, j;

  for (i = 0; i < 54; i++)
    pinMode(i, OUTPUT);

  digitalWrite(52, HIGH);
  digitalWrite(53, HIGH);
  
  for (i = 0; i < 160; i++, delay(25)) //4 second delay to reset
    if (i%2)
      digitalWrite(19, HIGH);
    else
      digitalWrite(19, LOW);

  for (i = 0; i < LEN; i++) { //write instructions
    for (j = 0; j < 52; j++) //resetting pins
      digitalWrite(j, LOW);

    for (j = 0; j < 16; j++) //current address
      if ((int) (prog[i][0]/pow(2, 15-j)) % 2)
        digitalWrite(51-j*2, HIGH);

    for (j = 35; j < 51; j++) //next address
      if ((int) (prog[i][3]/pow(2, 50-j)) % 2)
        digitalWrite(120-j*2, HIGH);

    for (j = 16; j < 19; j++) //operation code
      if ((int) (prog[i][1]/pow(2, 18-j)) % 2)
        digitalWrite(j, HIGH);

    for (j = 19; j < 35; j++) //operand
      if ((int) (prog[i][2]/pow(2, 34-j)) % 2)
        digitalWrite(j-19, HIGH);

    delay(1);
    digitalWrite(52, LOW);
    delay(1);
    digitalWrite(52, HIGH);
    delay(1);
  }

  digitalWrite(52, HIGH);
  digitalWrite(53, LOW);

  for (i = 0; i < 52; i++)
    pinMode(i, INPUT);
}

void loop() {

}
