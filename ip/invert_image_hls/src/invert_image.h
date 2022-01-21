#include <stdint.h>

#define IMAGE_X         480
#define IMAGE_Y         640
#define SIZE            IMAGE_X*IMAGE_Y
//#define SIZE			10

void invert_image(uint8_t image_in[SIZE], uint8_t image_out[SIZE]);
