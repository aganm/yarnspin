

#define  APP_IMPLEMENTATION
#define  APP_WINDOWS
#include "libs/app.h"

#define STB_IMAGE_IMPLEMENTATION
#include "libs/stb_image.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>




typedef struct jo_gif_t jo_gif_t;

jo_gif_t* export_start( int w, int h );

void export_frame( APP_U32* canvas, jo_gif_t* gif, int delay );
void export_end( jo_gif_t* gif );



void setpixel( APP_U32* p, APP_U32 c ) {
    if( c & 0xff000000 ) {
        *p = c;
    }
}

int app_proc( app_t* app, void* user_data ) {
    APP_U32 canvas[ 320 * 200 ];
    memset( canvas, 0, sizeof( canvas ) );
    app_interpolation( app, APP_INTERPOLATION_NONE );
    app_screenmode( app, APP_SCREENMODE_WINDOW );

    int w, h, c;
    APP_U32* back = (APP_U32*) stbi_load( "imgsrc/back.png", &w, &h, &c, 4 );
    APP_U32* mid = (APP_U32*) stbi_load( "imgsrc/buildings.png", &w, &h, &c, 4 );
    APP_U32* front = (APP_U32*) stbi_load( "imgsrc/front.png", &w, &h, &c, 4 );

   // jo_gif_t* gif = export_start( 320, 200 );

    int count = 0;
    while( app_yield( app ) != APP_STATE_EXIT_REQUESTED ) {
        int i = count;
        for( int y = 0; y < 200; ++y ) {
            for( int x = 0; x < 320; ++x ) {
                int bx = x + 0*i / 32;
                int by = y + 0;
                canvas[ x + y * 320 ] = back[ ( bx % w ) + ( by % h ) * w ];
                int mx = x + i / 4;
                int my = y + 0;
                setpixel( &canvas[ x + y * 320 ], mid[ ( mx % w ) + ( my % h ) * w ] );
                int fx = x + i / 1;
                int fy = y;
                setpixel( &canvas[ x + y * 320 ], front[ ( fx % w ) + ( fy % h ) * w ] );
            }
        }

        ++count;

        /*
        if( count > w * 2 ) {
            count = 0;
            break;
        }
        */
        
 //       export_frame( canvas, gif, 10 );
        app_present( app, canvas, 320, 200, 0xffffff, 0x000000 );
        app_present( app, canvas, 320, 200, 0xffffff, 0x000000 );
        app_present( app, canvas, 320, 200, 0xffffff, 0x000000 );
        app_present( app, canvas, 320, 200, 0xffffff, 0x000000 );
    }
 //   export_end(gif);
    return 0;
}



void main() {
    app_run( app_proc, NULL, NULL, NULL, NULL );
}



#include "jo_gif.h"


jo_gif_t* export_start( int w, int h ) {
    jo_gif_t* jo_gif = malloc( sizeof( jo_gif_t ) );
    *jo_gif = jo_gif_start("title.gif", w, h, 0, 256); 
    return jo_gif;
}


void export_frame( APP_U32* canvas, jo_gif_t* gif, int delay ) {
    uint8_t* pixels = malloc( 4 * gif->width * gif->height * 2 );  
    
    memcpy( pixels + 4 * gif->width * gif->height, canvas, 4 * gif->width * gif->height );
    for( int y = 0; y < gif->height; ++y ) {
        memcpy( pixels + 4 * gif->width * y, pixels + 4 * gif->width * ( gif->height + y ), 4 * gif->width );
    }
    jo_gif_frame( gif, pixels, delay, true ); 
    free( pixels );
}


void export_end( jo_gif_t* gif ) {
    jo_gif_end(gif);
    free( gif );
}

