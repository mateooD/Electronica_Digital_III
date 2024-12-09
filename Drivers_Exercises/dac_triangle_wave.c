/*
* brief: Generate a  triangle wave using the DAC
* author:
* 
*/

#include "LPC17xx.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_dac.h"

#define TRIANGLE_TABLE_SIZE 60

uint32_t triangle_table[TRIANGLE_TABLE_SIZE] = {
    0,  17,  34,  51,  68,  85, 102, 119, 136, 153,
  170, 187, 204, 221, 238, 255, 272, 289, 306, 323,
  340, 357, 374, 391, 408, 425, 442, 459, 476, 493,
  510, 527, 544, 561, 578, 595, 612, 629, 646, 663,
  680, 697, 714, 731, 748, 765, 782, 799, 816, 833,
  850, 867, 884, 901, 918, 935, 952, 969, 986, 1003
};

void config_dac();
void config_dma();
void generate_triangle_wave();

int main(void){
    SystemInit();
    config_dac();
    config_dma();
    generate_triangle_wave();

    while(1){
        //Do nothing
    }
    return 0;
}

void config_dac(){

}
void config_dma(){

}
void generate_triangle_wave(){

}


