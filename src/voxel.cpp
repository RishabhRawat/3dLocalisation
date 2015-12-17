#include "voxel.h"
#include <iostream>
#include <png.h>
#include <cstdlib>
#include <cstdint>


bool loadPngImage(const char *name, int &outWidth, int &outHeight, uint16_t *&outData) {

    png_structp png_ptr;
    png_infop info_ptr;
    unsigned int sig_read = 0;
    int color_type, interlace_type;
    FILE *fp;

    if ((fp = fopen(name, "rb")) == NULL)
        return false;

    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,NULL, NULL, NULL);

    if (png_ptr == NULL) {
        fclose(fp);
        return false;
    }

    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
        fclose(fp);
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        return false;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(fp);
        return false;
    }

    png_init_io(png_ptr, fp);

    png_set_sig_bytes(png_ptr, sig_read);

    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_SWAP_ENDIAN , NULL);

    png_uint_32 width, height;
    int bit_depth;
    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,&interlace_type, NULL, NULL);
    outWidth = width;
    outHeight = height;


    std::cout<<"bit_depth: "<<bit_depth<<std::endl;
    std::cout<<"color_type: "<<color_type<<std::endl;
    outData=NULL;

    unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
    outData = new uint16_t [row_bytes * outHeight];

    png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);

    for (int i = 0; i < outHeight; i++) {
        //FOR NON INVERTED COPY
        //memcpy(&outData[outWidth * i], row_pointers[i], row_bytes);

        //FOR INVERTED COPY
        memcpy(&outData[outWidth * (outHeight-1-i)], row_pointers[i], row_bytes);
    }

    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

    fclose(fp);

    return true;
}



void Voxel::readPCD(const char *filename)
{
	
}

int Voxel::readPngDepthMap(const char *filename)
{
	if(!loadPngImage(filename, width, height, depthMap)) return -1;
    return 0;
}

Voxel::~Voxel()
{
	if(depthMap)
		delete [] depthMap;
}
