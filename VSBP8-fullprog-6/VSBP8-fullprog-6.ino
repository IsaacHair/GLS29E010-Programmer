 #define LEN 362 //********make sure to get length correct
 #define JMP 0
 #define OUT 2
 #define ADR 4
 #define BUF 6
 #define I 0
 #define R 1
 //note: only use the least significant 16 bits out of 17 on the address
 //the last bit can be hard wired up or down as desired
uint16_t prog[LEN][4]={
    {0x0000, ADR+0, 0xffff, 0x0001}, //reset (reset to 15 since immediately incremented, so rolls over to 0)
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
    {0x000b, BUF+1, 0x0000, 0x1000},

    {0x1000, ADR+0, 0xffff, 0x1001}, //add 1
    {0x1001, ADR+1, 0x0000, 0x1002}, //0x0000 is ones digit; 0x0003 is 2^4's digit
    {0x1002, JMP+R, 0x0000, 0x1004},
    {0x1004, BUF+1, 0x0000, 0x1800},
    {0x1005, BUF+0, 0x0000, 0x1010},

    {0x1010, ADR+0, 0xffff, 0x1011},
    {0x1011, ADR+1, 0x0001, 0x1012},
    {0x1012, JMP+R, 0x0000, 0x1014},
    {0x1014, BUF+1, 0x0000, 0x1804},
    {0x1015, BUF+0, 0x0000, 0x1020},

    {0x1020, ADR+0, 0xffff, 0x1021},
    {0x1021, ADR+1, 0x0002, 0x1022},
    {0x1022, JMP+R, 0x0000, 0x1024},
    {0x1024, BUF+1, 0x0000, 0x1808},
    {0x1025, BUF+0, 0x0000, 0x1030},

    {0x1030, ADR+0, 0xffff, 0x1031},
    {0x1031, ADR+1, 0x0003, 0x1032},
    {0x1032, JMP+R, 0x0000, 0x1034},
    {0x1034, BUF+1, 0x0000, 0x2000},
    {0x1035, BUF+0, 0x0000, 0x2000},

    {0x1800, OUT+1, 0x0000, 0x1801}, //equalize clock cycles spent to add
    {0x1801, OUT+1, 0x0000, 0x1802},
    {0x1802, OUT+1, 0x0000, 0x1803},
    {0x1803, OUT+1, 0x0000, 0x1804},
    
    {0x1804, OUT+1, 0x0000, 0x1805},
    {0x1805, OUT+1, 0x0000, 0x1806},
    {0x1806, OUT+1, 0x0000, 0x1807},
    {0x1807, OUT+1, 0x0000, 0x1808},
    
    {0x1808, OUT+1, 0x0000, 0x1809},
    {0x1809, OUT+1, 0x0000, 0x180a},
    {0x180a, OUT+1, 0x0000, 0x180b},
    {0x180b, OUT+1, 0x0000, 0x2000},

    {0x2000, ADR+0, 0xffff, 0x2001}, //initialization
    {0x2001, ADR+1, 0x1800, 0x2002},
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
    {0x3001, ADR+1, 0x1800, 0x3002},
    {0x3002, JMP+R, 0x0000, 0x3004},
    {0x3004, OUT+1, 0x0000, 0x3006}, //this is end of path
    {0x3005, OUT+1, 0x0000, 0x300d}, //this is not end of path

    {0x3006, BUF+1, 0x0000, 0x3007}, //set this as not being end
    {0x3007, ADR+0, 0xfff1, 0x3008},
    {0x3008, ADR+1, 0x1810, 0x3009},
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
    {0x3101, ADR+1, 0x1810, 0x3102},
    {0x3102, JMP+R, 0x0000, 0x3104},
    {0x3104, OUT+1, 0x0000, 0x3106}, //this is end of path
    {0x3105, OUT+1, 0x0000, 0x310d}, //this is not end of path

    {0x3106, BUF+1, 0x0000, 0x3107}, //set this as not being end
    {0x3107, ADR+0, 0xfff2, 0x3108},
    {0x3108, ADR+1, 0x1820, 0x3109},
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
    {0x3201, ADR+1, 0x1820, 0x3202},
    {0x3202, JMP+R, 0x0000, 0x3204},
    {0x3204, OUT+1, 0x0000, 0x3206}, //this is end of path
    {0x3205, OUT+1, 0x0000, 0x320d}, //this is not end of path

    {0x3206, BUF+1, 0x0000, 0x3207}, //set this as not being end
    {0x3207, ADR+0, 0xfff4, 0x3208},
    {0x3208, ADR+1, 0x1830, 0x3209},
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
    {0x4001, ADR+1, 0x1800, 0x4002},
    {0x4002, JMP+R, 0x0000, 0x4004},
    {0x4004, OUT+1, 0x0000, 0x4006}, //this is the end of the path
    {0x4005, OUT+1, 0x0000, 0x400d}, //this is not the end of the path

    {0x4006, BUF+1, 0x0000, 0x4007}, //set this as not being the end
    {0x4007, ADR+0, 0xfff1, 0x4008},
    {0x4008, ADR+1, 0x1811, 0x4009},
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
    {0x4101, ADR+1, 0x1810, 0x4102},
    {0x4102, JMP+R, 0x0000, 0x4104},
    {0x4104, OUT+1, 0x0000, 0x4106}, //this is the end of the path
    {0x4105, OUT+1, 0x0000, 0x410d}, //this is not the end of the path

    {0x4106, BUF+1, 0x0000, 0x4107}, //set this as not being the end
    {0x4107, ADR+0, 0xfff2, 0x4108},
    {0x4108, ADR+1, 0x1822, 0x4109},
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
    {0x4201, ADR+1, 0x1820, 0x4202},
    {0x4202, JMP+R, 0x0000, 0x4204},
    {0x4204, OUT+1, 0x0000, 0x4206}, //this is the end of the path
    {0x4205, OUT+1, 0x0000, 0x420d}, //this is not the end of the path

    {0x4206, BUF+1, 0x0000, 0x4207}, //set this as not being the end
    {0x4207, ADR+0, 0xfff4, 0x4208},
    {0x4208, ADR+1, 0x1834, 0x4209},
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


    {0x5000, JMP+I, 0x0001, 0x5002},
    {0x5002, OUT+1, 0x0000, 0x5004}, //reset number if input held low
    {0x5003, OUT+1, 0x0000, 0x5005},

    {0x5004, BUF+0, 0x0000, 0x5100}, //divert to printing 0 (continues to next digit afterward)

    {0x5005, JMP+R, 0x0000, 0x5006}, //test value
    {0x5006, BUF+1, 0xffff, 0x5200}, //flip to one
    {0x5007, BUF+0, 0xffff, 0x5100}, //flip to zero


    {0x5100, ADR+0, 0xffff, 0x5101}, //printing 0
    {0x5101, ADR+1, 0x0003, 0x5102}, //3rd digit
    {0x5102, JMP+R, 0x0000, 0x5104},
    {0x5104, ADR+0, 0xffff, 0x5110},
    {0x5105, ADR+0, 0xffff, 0x5120},


    {0x5110, ADR+0, 0xffff, 0x5111}, //2nd digit
    {0x5111, ADR+1, 0x0002, 0x5112},
    {0x5112, JMP+R, 0x0000, 0x5114},
    {0x5114, ADR+0, 0xffff, 0x5130},
    {0x5115, ADR+0, 0xffff, 0x5140},

    {0x5120, ADR+0, 0xffff, 0x5121},
    {0x5121, ADR+1, 0x0002, 0x5122},
    {0x5122, JMP+R, 0x0000, 0x5124},
    {0x5124, ADR+0, 0xffff, 0x5150},
    {0x5125, ADR+0, 0xffff, 0x5160},


    {0x5130, ADR+0, 0xffff, 0x5131}, //1st digit
    {0x5131, ADR+1, 0x0001, 0x5132},
    {0x5132, JMP+R, 0x0000, 0x5134},
    {0x5134, ADR+0, 0xffff, 0x5170},
    {0x5135, ADR+0, 0xffff, 0x5180},

    {0x5140, ADR+0, 0xffff, 0x5141},
    {0x5141, ADR+1, 0x0001, 0x5142},
    {0x5142, JMP+R, 0x0000, 0x5144},
    {0x5144, ADR+0, 0xffff, 0x5190},
    {0x5145, ADR+0, 0xffff, 0x51a0},

    {0x5150, ADR+0, 0xffff, 0x5151},
    {0x5151, ADR+1, 0x0001, 0x5152},
    {0x5152, JMP+R, 0x0000, 0x5154},
    {0x5154, ADR+0, 0xffff, 0x51b0},
    {0x5155, ADR+0, 0xffff, 0x51c0},

    {0x5160, ADR+0, 0xffff, 0x5161},
    {0x5161, ADR+1, 0x0001, 0x5162},
    {0x5162, JMP+R, 0x0000, 0x5164},
    {0x5164, ADR+0, 0xffff, 0x51d0},
    {0x5165, ADR+0, 0xffff, 0x51e0},


    {0x5170, ADR+0, 0xffff, 0x5171}, //0th digit
    {0x5171, ADR+1, 0x0000, 0x5172},
    {0x5172, JMP+R, 0x0000, 0x5174},
    {0x5174, ADR+0, 0xffff, 0x5400},
    {0x5175, ADR+0, 0xffff, 0x5401},

    {0x5180, ADR+0, 0xffff, 0x5181},
    {0x5181, ADR+1, 0x0000, 0x5182},
    {0x5182, JMP+R, 0x0000, 0x5184},
    {0x5184, ADR+0, 0xffff, 0x5402},
    {0x5185, ADR+0, 0xffff, 0x5403},

    {0x5190, ADR+0, 0xffff, 0x5191},
    {0x5191, ADR+1, 0x0000, 0x5192},
    {0x5192, JMP+R, 0x0000, 0x5194},
    {0x5194, ADR+0, 0xffff, 0x5404},
    {0x5195, ADR+0, 0xffff, 0x5405},
    
    {0x51a0, ADR+0, 0xffff, 0x51a1},
    {0x51a1, ADR+1, 0x0000, 0x51a2},
    {0x51a2, JMP+R, 0x0000, 0x51a4},
    {0x51a4, ADR+0, 0xffff, 0x5406},
    {0x51a5, ADR+0, 0xffff, 0x5407},

    {0x51b0, ADR+0, 0xffff, 0x51b1}, //still 0th digit
    {0x51b1, ADR+1, 0x0000, 0x51b2},
    {0x51b2, JMP+R, 0x0000, 0x51b4},
    {0x51b4, ADR+0, 0xffff, 0x5408},
    {0x51b5, ADR+0, 0xffff, 0x5409},

    {0x51c0, ADR+0, 0xffff, 0x51c1},
    {0x51c1, ADR+1, 0x0000, 0x51c2},
    {0x51c2, JMP+R, 0x0000, 0x51c4},
    {0x51c4, ADR+0, 0xffff, 0x540a},
    {0x51c5, ADR+0, 0xffff, 0x540b},

    {0x51d0, ADR+0, 0xffff, 0x51d1},
    {0x51d1, ADR+1, 0x0000, 0x51d2},
    {0x51d2, JMP+R, 0x0000, 0x51d4},
    {0x51d4, ADR+0, 0xffff, 0x540c},
    {0x51d5, ADR+0, 0xffff, 0x540d},

    {0x51e0, ADR+0, 0xffff, 0x51e1},
    {0x51e1, ADR+1, 0x0000, 0x51e2},
    {0x51e2, JMP+R, 0x0000, 0x51e4},
    {0x51e4, ADR+0, 0xffff, 0x540e},
    {0x51e5, ADR+0, 0xffff, 0x540f},


    {0x5400, OUT+0, 0x0001, 0x1000}, //actually print it
    {0x5401, OUT+0, 0x0002, 0x1000},
    {0x5402, OUT+0, 0x0004, 0x1000},
    {0x5403, OUT+0, 0x0008, 0x1000},
    {0x5404, OUT+0, 0x0010, 0x1000},
    {0x5405, OUT+0, 0x0020, 0x1000},
    {0x5406, OUT+0, 0x0040, 0x1000},
    {0x5407, OUT+0, 0x0080, 0x1000},

    {0x5408, OUT+0, 0x0100, 0x1000},
    {0x5409, OUT+0, 0x0200, 0x1000},
    {0x540a, OUT+0, 0x0400, 0x1000},
    {0x540b, OUT+0, 0x0800, 0x1000},
    {0x540c, OUT+0, 0x1000, 0x1000},
    {0x540d, OUT+0, 0x2000, 0x1000},
    {0x540e, OUT+0, 0x4000, 0x1000},
    {0x540f, OUT+0, 0x8000, 0x1000},



    {0x5200, ADR+0, 0xffff, 0x5201}, //printing 1
    {0x5201, ADR+1, 0x0003, 0x5202}, //3rd digit
    {0x5202, JMP+R, 0x0000, 0x5204},
    {0x5204, ADR+0, 0xffff, 0x5210},
    {0x5205, ADR+0, 0xffff, 0x5220},


    {0x5210, ADR+0, 0xffff, 0x5211}, //2nd digit
    {0x5211, ADR+1, 0x0002, 0x5212},
    {0x5212, JMP+R, 0x0000, 0x5214},
    {0x5214, ADR+0, 0xffff, 0x5230},
    {0x5215, ADR+0, 0xffff, 0x5240},

    {0x5220, ADR+0, 0xffff, 0x5221},
    {0x5221, ADR+1, 0x0002, 0x5222},
    {0x5222, JMP+R, 0x0000, 0x5224},
    {0x5224, ADR+0, 0xffff, 0x5250},
    {0x5225, ADR+0, 0xffff, 0x5260},


    {0x5230, ADR+0, 0xffff, 0x5231}, //1st digit
    {0x5231, ADR+1, 0x0001, 0x5232},
    {0x5232, JMP+R, 0x0000, 0x5234},
    {0x5234, ADR+0, 0xffff, 0x5270},
    {0x5235, ADR+0, 0xffff, 0x5280},

    {0x5240, ADR+0, 0xffff, 0x5241},
    {0x5241, ADR+1, 0x0001, 0x5242},
    {0x5242, JMP+R, 0x0000, 0x5244},
    {0x5244, ADR+0, 0xffff, 0x5290},
    {0x5245, ADR+0, 0xffff, 0x52a0},
    
    {0x5250, ADR+0, 0xffff, 0x5251},
    {0x5251, ADR+1, 0x0001, 0x5252},
    {0x5252, JMP+R, 0x0000, 0x5254},
    {0x5254, ADR+0, 0xffff, 0x52b0},
    {0x5255, ADR+0, 0xffff, 0x52c0},

    {0x5260, ADR+0, 0xffff, 0x5261},
    {0x5261, ADR+1, 0x0001, 0x5262},
    {0x5262, JMP+R, 0x0000, 0x5264},
    {0x5264, ADR+0, 0xffff, 0x52d0},
    {0x5265, ADR+0, 0xffff, 0x52e0},


    {0x5270, ADR+0, 0xffff, 0x5271}, //0th digit
    {0x5271, ADR+1, 0x0000, 0x5272},
    {0x5272, JMP+R, 0x0000, 0x5274},
    {0x5274, ADR+0, 0xffff, 0x5800},
    {0x5275, ADR+0, 0xffff, 0x5801},

    {0x5280, ADR+0, 0xffff, 0x5281},
    {0x5281, ADR+1, 0x0000, 0x5282},
    {0x5282, JMP+R, 0x0000, 0x5284},
    {0x5284, ADR+0, 0xffff, 0x5802},
    {0x5285, ADR+0, 0xffff, 0x5803},

    {0x5290, ADR+0, 0xffff, 0x5291},
    {0x5291, ADR+1, 0x0000, 0x5292},
    {0x5292, JMP+R, 0x0000, 0x5294},
    {0x5294, ADR+0, 0xffff, 0x5804},
    {0x5295, ADR+0, 0xffff, 0x5805},
   
    {0x52a0, ADR+0, 0xffff, 0x52a1},
    {0x52a1, ADR+1, 0x0000, 0x52a2},
    {0x52a2, JMP+R, 0x0000, 0x52a4},
    {0x52a4, ADR+0, 0xffff, 0x5806},
    {0x52a5, ADR+0, 0xffff, 0x5807},

    {0x52b0, ADR+0, 0xffff, 0x52b1}, //still 0th digit
    {0x52b1, ADR+1, 0x0000, 0x52b2},
    {0x52b2, JMP+R, 0x0000, 0x52b4},
    {0x52b4, ADR+0, 0xffff, 0x5808},
    {0x52b5, ADR+0, 0xffff, 0x5809},
    
    {0x52c0, ADR+0, 0xffff, 0x52c1},
    {0x52c1, ADR+1, 0x0000, 0x52c2},
    {0x52c2, JMP+R, 0x0000, 0x52c4},
    {0x52c4, ADR+0, 0xffff, 0x580a},
    {0x52c5, ADR+0, 0xffff, 0x580b},

    {0x52d0, ADR+0, 0xffff, 0x52d1},
    {0x52d1, ADR+1, 0x0000, 0x52d2},
    {0x52d2, JMP+R, 0x0000, 0x52d4},
    {0x52d4, ADR+0, 0xffff, 0x580c},
    {0x52d5, ADR+0, 0xffff, 0x580d},

    {0x52e0, ADR+0, 0xffff, 0x52e1},
    {0x52e1, ADR+1, 0x0000, 0x52e2},
    {0x52e2, JMP+R, 0x0000, 0x52e4},
    {0x52e4, ADR+0, 0xffff, 0x580e},
    {0x52e5, ADR+0, 0xffff, 0x580f},


    {0x5800, OUT+1, 0x0001, 0x0000}, //actually print it
    {0x5801, OUT+1, 0x0002, 0x0000},
    {0x5802, OUT+1, 0x0004, 0x0000},
    {0x5803, OUT+1, 0x0008, 0x0000},
    {0x5804, OUT+1, 0x0010, 0x0000},
    {0x5805, OUT+1, 0x0020, 0x0000},
    {0x5806, OUT+1, 0x0040, 0x0000},
    {0x5807, OUT+1, 0x0080, 0x0000},

    {0x5808, OUT+1, 0x0100, 0x0000},
    {0x5809, OUT+1, 0x0200, 0x0000},
    {0x580a, OUT+1, 0x0400, 0x0000},
    {0x580b, OUT+1, 0x0800, 0x0000},
    {0x580c, OUT+1, 0x1000, 0x0000},
    {0x580d, OUT+1, 0x2000, 0x0000},
    {0x580e, OUT+1, 0x4000, 0x0000},
    {0x580f, OUT+1, 0x8000, 0x0000},
    };
#define CHIP 0
//determines which chip is being written to; choses values accordingly

//use arduino MEGA

#define ADR 22
#define DATA 40
#define WE 50
#define OE 51
#define CE 52
//data and adr are the 0th pins, counting up increments them on the chip
//lsb is the least number bit for all

uint8_t pvcv[8][2] =
{
  {0, 3},
  {1, 4},
  {2, 5},
  {3, 6},
  {4, 7},
  {5, 2},
  {6, 1},
  {7, 0}
};
uint8_t paca[16][2] =
{
  {0, 10},
  {1, 11},
  {2, 9},
  {3, 8},
  {4, 13},
  {5, 14},
  {6, 0},
  {7, 1},
  {8, 2},
  {9, 3},
  {10, 4},
  {11, 5},
  {12, 6},
  {13, 7},
  {14, 12},
  {15, 15}
};
//the first value is where the data point is recognised on the board
//note: on the board, the lsb is labeled 15, but here these are reversed for clarity
//note: so, the lsb for everything is 0
//the second value is the pin number on the eeprom
//that corresponds to the first value program pin

void setup(){
  Serial.begin(9600);
  while (!Serial)
    delay(10);
  int i;
  for (i = 22; i < 53; i++)
    pinMode(i, OUTPUT);
  digitalWrite(WE, HIGH);
  digitalWrite(OE, HIGH);
  digitalWrite(CE, LOW);
  
  page(0);

  for (i = 0; i < 8; i++)
    pinMode(DATA+i, INPUT);

  Serial.println(chipread(0));
  Serial.println(cvtopv(chipread(0)));
}

void page(uint16_t point) {
  def(0x5555, 0xAA);
  def(0x2AAA, 0x55);
  def(0x5555, 0xA0);
  def(gpatoca(0), gpvtocv(0));
  digitalWrite(WE, HIGH);
  delay(20);
}

void def(uint16_t adr, uint8_t val) {
  setadr(adr);
  digitalWrite(WE, HIGH);
  digitalWrite(WE, LOW);
  setval(val);
}

void setadr(uint16_t adr) {
  int i;
  for (i = 0; i < 16; i++)
    if (adr & (1 << i))
      digitalWrite(ADR+i, HIGH);
    else
      digitalWrite(ADR+i, LOW);
}

void setval(uint8_t val) {
  int i;
  for (i = 0; i < 8; i++)
    if (val & (1 << i))
      digitalWrite(DATA+i, HIGH);
    else
      digitalWrite(DATA+i, LOW);
}

uint8_t gpvtocv(uint16_t point) {
  int i;
  uint8_t val;
  uint8_t ret;
  uint8_t *pret;
  switch (CHIP) {
    case 0:
    val = prog[point][1] << 5;
    break;
    case 1:
    val = prog[point][2] / (1 << 8);
    break;
    case 2:
    val = prog[point][2] % (1 << 8);
    break;
    case 3:
    val = prog[point][3] / (1 << 8);
    break;
    case 4:
    val = prog[point][3] % (1 << 8);
    break;
  }
  pret = &ret;
  for (i = 0; i < 8; i++)
    bitsendval(val, pret, pvcv[i][0], pvcv[i][1]);
  return (ret);
}

uint8_t cvtopv(uint8_t v) {
  int i;
  uint8_t val;
  uint8_t ret;
  uint8_t *pret;
  val = v;
  pret = &ret;
  for (i = 0; i < 8; i++)
    bitsendval(val, pret, pvcv[i][1], pvcv[i][0]);
  return (ret);
}

uint16_t gpatoca(uint16_t point) {
  int i;
  uint16_t adr;
  uint16_t ret;
  uint16_t *pret;
  adr = prog[point][0];
  pret = &ret;
  for (i = 0; i < 16; i++)
    bitsendadr(adr, pret, paca[i][0], paca[i][1]);
  return (ret);
}

uint16_t catopa(uint16_t point) {
  int i;
  uint16_t adr;
  uint16_t ret;
  uint16_t *pret;
  adr = point;
  pret = &ret;
  for (i = 0; i < 16; i++)
    bitsendadr(adr, pret, paca[i][1], paca[i][0]);
  return (ret);
}

void bitsendval(uint8_t val, uint8_t *pret, uint8_t s, uint8_t e) {
  if (val & (1 << s))
    *pret |= (1 << e);
  else
    *pret &= (B11111111^(1 << e));
}

void bitsendadr(uint16_t adr, uint16_t *pret, uint8_t s, uint8_t e) {
  if (adr & (1 << s))
    *pret |= (1 << e);
  else
    *pret &= (((B11111111<<8)|B11111111)^(1 << e));
}

uint8_t chipread(uint16_t adr) {
  int i;
  uint8_t ret;
  setadr(adr);
  for (i = 0, ret = 0; i < 8; i++)
    if (digitalRead(DATA+i))
      ret += (1 << i);
  return (ret);
}

void loop(){}
