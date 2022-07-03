
#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include<cmath>

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Code::Blocks Template Windows App"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           800,                 /* The programs width */
           500,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}
//function to draw similarities of the chosen point except first quarter
void Draw8Points(HDC hdc , int xc ,int yc , int a , int b , COLORREF color ){
    SetPixel(hdc , xc + a ,yc + b , color);
    SetPixel(hdc , xc - a, yc + b, color);
    SetPixel(hdc , xc - a, yc - b, color);
    //SetPixel(hdc , xc + a, yc - b, color);
    SetPixel(hdc , xc + b, yc + a, color);
    SetPixel(hdc , xc - b, yc + a, color);
    SetPixel(hdc , xc - b, yc - a, color);
    //SetPixel(hdc , xc + b, yc - a, color);

}

void DrawCircle(HDC hdc ,int xc , int yc , int R , COLORREF color)
{
    //computed point (0,R)
    int x = 0 ;
    int y = R ;
    //initial change
    int d = 1-R ;
    Draw8Points(hdc , xc , yc , x , y , color);
    while(x<y){
        if (d<0)
        {
            d+= 2*x+3 ;
        }
        else{
            d+= 2*(x-y) + 5 ;
            y--;
        }
        x++;
        Draw8Points(hdc,xc , yc , x , y, color) ;
    }
}

/*  This function is called by the Windows function DispatchMessage()  */
 int x_c; int y_c;
int x_1; int y_1 ;
int x_2 ; int y_2;
int R1 ; int R2;
int counter = 0 ;

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc = GetDC(hwnd);
    switch (message)                  /* handle the messages */
    {
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        case WM_LBUTTONDBLCLK:
            if(counter==0)
            {
                x_c = LOWORD(lParam);
                y_c = HIWORD(lParam);
                counter++;
            }
            else if(counter ==1) {
                x_1 = LOWORD(lParam);
                y_1 = HIWORD(lParam);
                R1 = sqrt(pow((x_1-x_c),2) + pow((y_1-y_c),2));
                DrawCircle(hdc,x_c, y_c , R1 , RGB(100,100,100));
                counter++;
            }
            else {
                x_2 = LOWORD(lParam);
                y_2 = HIWORD(lParam);
                R2 = sqrt(pow((x_2-x_c),2) + pow((y_2-y_c),2));
                //loop for filling color
                for(R1 ; R1<R2 ; R1++){
                    DrawCircle(hdc,x_c,y_c,R1,RGB(100,100,100));
                }
                counter=0;
            }
            break;

        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

