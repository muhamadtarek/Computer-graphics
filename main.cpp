#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <iostream>

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");
int x1,y1,x2,y2,x3,y3,count1=0;

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
           544,                 /* The programs width */
           375,                 /* and height in pixels */
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
void Swap(int &x,int &y){
  int temp=x;
  x=y;
  y=temp;
}
void midPoint(HDC hdc,int x1,int y1,int x2,int y2){
  int x,y;
  int dx=x2-x1;
  int dy = y2-y1;
  if(abs(dx)>=abs(dy)){
    if(x1>x2){
        Swap(x1,x2);
        Swap(y1,y2);
    }
    x=x1;
    y=y1;
    SetPixel(hdc,x,y,RGB(0,0,0));
    int d = dx-2*dy;
    int d1 = -2*dy;
    int d2 = 2*dx-2*dy;
    while(x<x2){
        if(d>0){
            d+=d1;
        }else{
            d+=d2;
            y++;
        }
        x++;
        SetPixel(hdc,x,y,RGB(0,0,0));
    }

  }else{
    if(y1>y2){
        Swap(x1,x2);
        Swap(y1,y2);
    }
    x=x1;
    y=y1;
    SetPixel(hdc,x,y,RGB(0,0,0));
    int d = 2*dx-dy;
    int d1 = 2*dx-2*dy;
    int d2 = 2*dx;
    while(y<y2){
        if(d>0){
            d+=d1;
            x++;
        }else{
          d+=d2;
        }
        y++;
        SetPixel(hdc,x,y,RGB(0,0,0));
    }

  }
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    int x,y;

    switch (message)                  /* handle the messages */
    {
        case WM_LBUTTONDOWN:
            hdc = GetDC(hwnd);
            x=LOWORD(lParam);
            y=HIWORD(lParam);
            if(count1==0){
                x1=x;
                y1=y;
                count1++;
            }else if(count1==1){
              x2=x;
              y2=y;
              count1++;
              midPoint(hdc,x1,y1,x2,y2);
            }else if(count1==2){
              x3=x;
              y3=y;
              count1++;
              midPoint(hdc,x2,y2,x3,y3);
            }else if(count1==3){
              x3=x;
              y3=y;
              count1++;
              midPoint(hdc,x1,y1,x3,y3);
            }

            ReleaseDC(hwnd,hdc);
            break;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
