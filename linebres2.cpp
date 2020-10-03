//Compiled on Windows using MinGW and WinBGI libraries
//cmd: g++ -m32 linebres2.cpp -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32

#include<stdio.h>
#include<graphics.h>
#include<conio.h>

//init n as the no. of "steps" to count in loops, and an empty array.
int n=0;
int *pixels=NULL;

/*Method to export the coordinates to a .txt file. 
Basically runs a loop to fprintf the individual pixels (stored in array) used to map the line.*/
void ExportPixels(int *pixels, int n)
{
  FILE *fp = fopen("Pixels.txt", "w");
  
  fprintf(fp, "x, y\n");
  
  for(int i=0; i<n; i++)
  {
   fprintf(fp, "%d, %d\n", pixels[2*i+0], pixels[2*i+1]);
  }

  fclose(fp);
  printf("Pixel coordinates exported to Pixels.txt successfully!\n");
}

/*Method to export a .svg file of the output. 
Basically writes svg syntax and then runs a loop to insert the pixels coords*/
void Export2SVG(int *pixels, int n, int width, int height)
{
    int scale = 10;
    int margin = 100;
    int i;
    int x1 = pixels[0], x2 = pixels[0];
    int y1 = pixels[1], y2 = pixels[1];
    for(i=1; i<n; i++){
        if(x1>pixels[2*i+0]) x1=pixels[2*i+0]; 
        if(x2<pixels[2*i+0]) x2=pixels[2*i+0];
        if(y1>pixels[2*i+1]) y1=pixels[2*i+1]; 
        if(y2<pixels[2*i+1]) y2=pixels[2*i+1];
    }
    x1 *=scale; x2 *=scale;
    y1 *=scale; y2 *=scale;
  
  FILE *fp = fopen("BRES_SVG.svg", "w");

  fprintf(fp, "<svg width=\"%d\" height=\"%d\" viewBox=\"0 0 %d %d\" fill=\"none\" xmlns=\"http://www.w3.org/2000/svg\"  version=\"1.1\">",
               width,height,width,height);
    for(i=0; i<n; i++)
    {
        fprintf(fp,"\n<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" style=\"fill:yellow;stroke:red;stroke-width:.30;fill-opacity:0.76;stroke-opacity:0.90\"/>", scale*pixels[2*i+0]-x1+100, scale*pixels[2*i+1]-y1+100, scale, scale);
    }

    //Append the endpoints as circle
    fprintf(fp,"\n\n <circle cx=\"%d\" cy=\"%d\" r=\"2\" stroke=\"red\" stroke-width=\"2\" fill=\"blue\" />", scale*pixels[0]-x1+100+scale/2, scale*pixels[1]-y1+100+scale/2);

    fprintf(fp,"\n\n <circle cx=\"%d\" cy=\"%d\" r=\"2\" stroke=\"red\" stroke-width=\"2\" fill=\"blue\" />", scale*pixels[2*(n-1)+0]-x1+100+scale/2, scale*pixels[2*(n-1)+1]-y1+100+scale/2);

    //Append the line segment
    fprintf(fp, "\n\n<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" style=\"stroke:rgb(0,0,155);stroke-width:1\" />\n", scale*pixels[0]-x1+100+scale/2, scale*pixels[1]-y1+100+scale/2, scale*pixels[2*(n-1)+0]-x1+100+scale/2, scale*pixels[2*(n-1)+1]-y1+100+scale/2);
    
/*
    //Text section and print pixel-coords.
    fprintf(fp, "<text x=\"350\" y=\"540\" text-anchor=\"middle\" font-size=\"20px\" fill=\"#000000\">Demonstation of Bresenham's Line Drawing Algorithm</text>");

    fprintf(fp, "<text x=\"350\" y=\"560\" text-anchor=\"middle\" font-size=\"16px\" fill=\"#000000\">Dipyaman Mukherjee, 181001001084, BCS3A</text>");

    fprintf(fp, "<text x=\"125\" y=\"580\" text-anchor=\"start\" font-size=\"12px\" fill=\"#000000\">Pixels plotted: </text>");
    
    int a=125, b=595; //placement of pixel coords
    for(i=0; i<n; i++)
  {
    fprintf(fp, "<text x=\"%d\" y=\"%d\" text-anchor=\"start\" font-size=\"12px\" fill=\"#aaaaaa\">(%d,%d) , </text>",a, b, pixels[2*i+0], pixels[2*i+1]);
    
    //Checks if texts are going out of canvas or not.
    //If so, go to the next line (on y axis)
    if(a>=(width-4500))
    {
        a=125; b+=15;
    }
    else
        a+=50; //moves 50px to the right (x-axis) and prints the coordinate.
  }
*/
  fprintf(fp, "\n </svg>\n");
  fclose(fp);
  printf("SVG created successfully!\n");
}

/*Method to export a .html file of the output. 
Basically writes svg syntax within HTML coding*/
void Export2HTML(int *pixels, int n, int width, int height)
{
  int scale = 10;
    int margin = 100;
    int i;
    int x1 = pixels[0], x2 = pixels[0];
    int y1 = pixels[1], y2 = pixels[1];
    for(i=1; i<n; i++){
        if(x1>pixels[2*i+0]) x1=pixels[2*i+0]; 
        if(x2<pixels[2*i+0]) x2=pixels[2*i+0];
        if(y1>pixels[2*i+1]) y1=pixels[2*i+1]; 
        if(y2<pixels[2*i+1]) y2=pixels[2*i+1];
    }
    x1 *=scale; x2 *=scale;
    y1 *=scale; y2 *=scale;
  
  FILE *fp = fopen("BRES_HTML.html", "w");
  fprintf(fp, "<!DOCTYPE html>\n<html>\n<body>\n");   //add deader to html
  
  //add SVG image  canvas
  fprintf(fp, "<svg width=\"%d\" height=\"%d\" viewBox=\"0 0 %d %d\" fill=\"none\" xmlns=\"http://www.w3.org/2000/svg\"  version=\"1.1\">",
               width,height,width,height);
    for(i=0; i<n; i++)
    {
        fprintf(fp,"\n<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" style=\"fill:yellow;stroke:red;stroke-width:.30;fill-opacity:0.76;stroke-opacity:0.90\"/>", scale*pixels[2*i+0]-x1+100, scale*pixels[2*i+1]-y1+100, scale, scale);
    }

    //Append the endpoints as circle
    fprintf(fp,"\n\n <circle cx=\"%d\" cy=\"%d\" r=\"2\" stroke=\"red\" stroke-width=\"2\" fill=\"blue\" />", scale*pixels[0]-x1+100+scale/2, scale*pixels[1]-y1+100+scale/2);

    fprintf(fp,"\n\n <circle cx=\"%d\" cy=\"%d\" r=\"2\" stroke=\"red\" stroke-width=\"2\" fill=\"blue\" />", scale*pixels[2*(n-1)+0]-x1+100+scale/2, scale*pixels[2*(n-1)+1]-y1+100+scale/2);

    //Append the line segment
    fprintf(fp, "\n\n<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" style=\"stroke:rgb(0,0,155);stroke-width:1\" />\n", scale*pixels[0]-x1+100+scale/2, scale*pixels[1]-y1+100+scale/2, scale*pixels[2*(n-1)+0]-x1+100+scale/2, scale*pixels[2*(n-1)+1]-y1+100+scale/2);
    

    fprintf(fp, "\n </svg>\n");
    fprintf(fp, "\n</body>\n</html>\n");
    fclose(fp);
  
  printf("HTML created successfully!\n");
}

//Method to draw a line using Bresenham algorithm.
//Start coords, End coords and counter n to count number of steps are passed as arguments.
//Method returns an array with x and y coords. 
int *lineBres(int xa, int ya, int xb, int yb, int *n)
{
    int k,twoDy,twoDyMinusDx;
    int dx = xb - xa;
    int dy = yb - ya;
    int p = 2 * dy - dx;
    twoDy = 2 * dy;
    twoDyMinusDx = 2*dy-2*dx;
    int x, y;

    if (xa > xb)
    {
	    x = xb;
	    y = yb;
	    xb = xa;
    }
    else
    {
	    x = xa;
	    y = ya;
    }
    int *pixels = (int*)malloc(2*(xb+1)*sizeof(int));
    int m=0;
   
    pixels[2*m+0]=x;
    pixels[2*m+1]=y;
   
    m++;
    
    for (k = 0; k <= dx-1; k++)
    {
	    x++;
	    if (p < 0)
	        p = p + twoDy;
	    else
	    {
	        y++;
	        p = p + twoDyMinusDx;
	    }
        
        pixels[2*m+0]=x;
	    pixels[2*m+1]=y;
	    
        m++;
    }
        *n=m;
        printf("\nNumber of pixels = %d\n", *n);
        return pixels;
}

//Method to display the pixels (as a line) by running a loop and printing each indiviual pixel coords.
void display()
{
    for(int i=0;i<n;i++)
    {
        //printf("%d, %d\n", pixels[2*i+0],pixels[2*i+1]);
        putpixel(pixels[2*i+0],pixels[2*i+1],6);
    }
    printf("Waiting for you to close the display-window...\n");
}

//Main method.
int main()
{
    int x1,y1,x2,y2;

    int gd=DETECT,gm;
    
    printf("Enter the starting coordinates: ");
    scanf("%d%d",&x1,&y1);
    printf("Enter the ending coordinates: ");
    scanf("%d%d",&x2,&y2);
    
    //Takes input above, creates a BGI window and passes input to lineBres method.
    //Seeds the pixels array with all the pixel coords.
    initgraph(&gd,&gm,NULL);
    pixels=lineBres(x1,y1,x2,y2,&n);
    
    
    //Export funtions are called here.
    int width=5000;
    int height=5000;
    Export2SVG(pixels, n, width, height);
    Export2HTML(pixels, n, width, height);
    ExportPixels(pixels, n);
    
    //Window already initialized, now to display output. Calls the display method.
    display();

    //Delay function. Specific to WinBGI libraries. 
    //Check https://www.cs.colorado.edu/~main/bgi/doc/ for documentation.
    //Holds the output window forever until manually closed by user.
    
    while (!kbhit( ))
    {
        delay(200);
    }
    return 0;
}