#pragma once
void write_JPEG_file(char *filename, char* image_buffer,int image_width,int image_height ,int quality=100);
int read_JPEG_file(char *filename,char** buf,int* w,int *h);