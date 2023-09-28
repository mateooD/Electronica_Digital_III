



void configGPIO();
void configIntGPIO();

int main(void)
{
    uint32_t array[16];
    int interrupcion = 0;
    LPC_PINCON-> PINSEL4 &= (0x0); //Elijo todos los puertos del 2.0 a 2.7 como gpio
    configGPIO();
    configIntGPIO();
    while (1)
    {
        /* code */
    }
    return 0;
}


void configGPIO(){
    LPC_GPIO2-> FIODIR &= (0x0);
}

void configIntGPIO(){
    LPC_GPIOINT-> IO2IntEnR |= (0xff);
    LPC_GPIOINT-> IO2IntEnF |= (0xff);
    LPC_GPIOINT-> IO2IntClr |= (0xff); //Limpo la bandera
    NVIC_EnableIRQ(EINT3_IRQn);// activo las interrupciones
}

void EINT3_IRQHandler (void){

    if(interrupcion < 16){
        array[interrupcion] = (LPC_GPIO2-> FIOPIN);//almaceno los 16 bits
        interrupcion++;
        LPC_GPIOINT-> IO2IntClr |= (0xff);
    }
    else{
        interrupcion = 0;
        LPC_GPIOINT-> IO2IntClr |= (0xff);
    }
}
