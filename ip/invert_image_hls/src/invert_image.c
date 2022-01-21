#include "invert_image.h"

void invert_image(uint8_t image_in[SIZE], uint8_t image_out[SIZE])
{
#pragma HLS TOP
#pragma HLS INTERFACE s_axilite bundle=BUS_A port=image_in
#pragma HLS INTERFACE s_axilite bundle=BUS_A port=image_out
#pragma HLS INTERFACE s_axilite bundle=BUS_A port=return

//      loop_x: for (int i = 0; i < IMAGE_X; i++)
//      {
//              loop_y: for (int j = 0; j < IMAGE_Y; j++)
//              {
//                      image_out[i*IMAGE_Y+j] = image_in[i*IMAGE_Y+(IMAGE_Y-1-j)];
//              }
//      }

	loop: for(int i = 0; i < SIZE; i++)
	{
		image_out[i] = image_in[SIZE-i-1];
	}
}
