#include<stdio.h>
#include<math.h>
#include<time.h>
#include"ext.h"


int main(int argc,char const *argv[])
{
    puts("Code in C - SVG\n---------------\n");
    

        
    svg* psvg;
    psvg = svg_create(1920, 800);

    if(psvg == NULL)
    {
        puts("psvg is NULL");
    }
    else
    {
         test(psvg,argv[1]);
       
    }
    
    
     svg_save(psvg, "monfichier.svg");
        svg_free(psvg);
    
    
    
    
   
    
    return EXIT_SUCCESS;
}

