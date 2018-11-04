#include <stdio.h>
#include <unistd.h>
#include <apu2_gpio.h>
#include <string.h>
#include <errno.h>   // for errno


void switchled(int led, int state){

    switch(state) {

        case 0: switch(led) {
                    case 1: printf("switching LED%d off\n",led);
                            apu_gpio_set_dir(APU_LED1, APU_DIR_OUT);
                            apu_gpio_set_val(APU_LED1, state^1);
                            break;
                    case 2: printf("switching LED%d off\n",led);
                            apu_gpio_set_dir(APU_LED2, APU_DIR_OUT);
                            apu_gpio_set_val(APU_LED2, state^1);
                            break;
                    case 3: printf("switching LED%d off\n",led);
                            apu_gpio_set_dir(APU_LED3, APU_DIR_OUT);
                            apu_gpio_set_val(APU_LED3, state^1);
                            break;
                } break;

        case 1: switch(led) {
                    case 1: printf("switching LED%d on\n",led);
                            apu_gpio_set_dir(APU_LED1, APU_DIR_OUT);
                            apu_gpio_set_val(APU_LED1, state^1);
                            break;
                    case 2: printf("switching LED%d on\n",led);
                            apu_gpio_set_dir(APU_LED2, APU_DIR_OUT);
                            apu_gpio_set_val(APU_LED2, state^1);
                            break;
                    case 3: printf("switching LED%d on\n",led);
                            apu_gpio_set_dir(APU_LED3, APU_DIR_OUT);
                            apu_gpio_set_val(APU_LED3, state^1);
                            break;
                } break;
    }

}

void multiswitch(int led1, int led2, int led3){

    switch(led1) {
        case 1: printf("switching LED1 on\n");
                apu_gpio_set_dir(APU_LED1, APU_DIR_OUT);
                apu_gpio_set_val(APU_LED1, 0);
                break;
        case 0: printf("switching LED1 off\n");
                apu_gpio_set_dir(APU_LED1, APU_DIR_OUT);
                apu_gpio_set_val(APU_LED1, 1);
                break;
    }
    switch(led2) {
        case 1: printf("switching LED2 on\n");
                apu_gpio_set_dir(APU_LED2, APU_DIR_OUT);
                apu_gpio_set_val(APU_LED2, 0);
                break;
        case 0: printf("switching LED2 off\n");
                apu_gpio_set_dir(APU_LED2, APU_DIR_OUT);
                apu_gpio_set_val(APU_LED2, 1);
                break;
    }
    switch(led3) {
        case 1: printf("switching LED3 on\n");
                apu_gpio_set_dir(APU_LED3, APU_DIR_OUT);
                apu_gpio_set_val(APU_LED3, 0);
                break;
        case 0: printf("switching LED3 off\n");
                apu_gpio_set_dir(APU_LED3, APU_DIR_OUT);
                apu_gpio_set_val(APU_LED3, 1);
                break;
    }

}

int main(int argc, char *argv[]) {
    int status, i;
    unsigned val = 1;

    char *p;
    int led;
    int state;


    printf("Library version: %s\n", apu_gpio_version());
    printf("Status LED (c) by Adams Inc. 2018\n\n");

    if (argc > 3 || argc == 1){
        printf("Usage:\t\tled\tstate\n");        
        printf("\tblink\t[0|1|2]\t[0|1]\n\n");
        printf("Example:\nTurn on first LED\n");
        printf("\tblink 0 1\n\n");
        printf("Usage:\t\tLED1&LED2&LED3\n");
        printf("\tblink\t[0|1][0|1][0|1]\n\n");
        printf("Example:\nTurn on second only LED\n");
        printf("\tblink 010\n\n");

        return -1;
    }

    status = apu_gpio_init();
    if (status < 0) {
        printf("GPIO library init failed: %d\n", status);
        //return -8;
    }

    if (argc == 3){
        //check input type and range      
        errno = 0;
        led = strtol(argv[1], &p, 10);

        // Check for errors: e.g., the string does not represent an integer
        // or the integer is larger than int
        if (errno != 0 || *p != '\0' || led < 1 || led > 3) {
            // Put here the handling of the error, like exiting the program with
            // an error message
            printf("Argument out of range (1-3)\n");
            return -2;
        }	

        errno = 0;
        state = strtol(argv[2], &p, 10);    
        if (errno != 0 || *p != '\0' || state < 0 || state > 1) {
            // Put here the handling of the error, like exiting the program with
            // an error message
            printf("Argument out of range (0-1)\n");
            return -4;
        }	
        
        switchled(led, state);
    }

    if (argc == 2){
        size_t length = strlen(argv[1]);
        if (length == 3){
            int led1 = argv[1][0] - '0';
            int led2 = argv[1][1] - '0';
            int led3 = argv[1][2] - '0';
            printf("Switch LED1: %d LED2 %d LED3 %d\n",led1,led2,led3);
            multiswitch(led1, led2, led3);
        }else {
            printf("Argument out of range (3)\n");
            return -4;            
        }

    }

	return 0;

}
