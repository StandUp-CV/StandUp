// Standup_Win32.cpp : Definiert den Einstiegspunkt für die Anwendung.
//

#include "stdafx.h"
#include "Standup_Win32.h"
#include <gl/gl.h>
#include <gl/GLU.h>
#include <wingdi.h>

#define MAX_LOADSTRING 100

// Globale Variablen:
HINSTANCE hInst;								// Aktuelle Instanz
TCHAR szTitle[MAX_LOADSTRING];					// Titelleistentext
TCHAR szWindowClass[MAX_LOADSTRING];			// Klassenname des Hauptfensters
HWND OpenGLWindowHandle;						// OpenGl Window Handle
HGLRC OpenGLHandle;								// Reines OpenGL handle
HWND Win32WindowHandle;							// Win32 Window Handle
HDC OpenGLDCHandle;								// OpenGL DC Handle
bool quit = false;
float theta = 0;

// Vorwärtsdeklarationen der in diesem Codemodul enthaltenen Funktionen:
ATOM				ApplicationRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
// Window callbacks
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
// opengl init/destruct functions
void				CreateOpenGLContext(HINSTANCE& hInstance, WNDCLASS& wc);
void				UpdateOpenGLContext(MSG& msg);
LRESULT CALLBACK	GLWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void				EnableOpenGL(HWND hWnd, HDC * hDC, HGLRC * hRC);
void				DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC);

// FUNKTION: _tWinMain
// ZWECK: inits the main function
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Hier Code einfügen.
	MSG msg;
	HACCEL hAccelTable;
	WNDCLASS wc;

	// Globale Zeichenfolgen initialisieren
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_STANDUP_WIN32, szWindowClass, MAX_LOADSTRING);
	ApplicationRegisterClass(hInstance);

	// Anwendungsinitialisierung ausführen:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_STANDUP_WIN32));

	CreateOpenGLContext(hInstance, wc);

	// Hauptnachrichtenschleife:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		UpdateOpenGLContext(msg);
	}

	return (int) msg.wParam;
}

void CreateOpenGLContext(HINSTANCE& hInstance, WNDCLASS& wc) {
	LPCWSTR OpenGLClassName = L"OpenGLWindow";

	// register window class
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = GLWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
	wc.hCursor = LoadCursor( NULL, IDC_ARROW );
	wc.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH );
	wc.lpszMenuName = NULL;
	wc.lpszClassName = OpenGLClassName;
	RegisterClass( &wc );



	// create main window
	OpenGLWindowHandle = CreateWindowEx( WS_EX_APPWINDOW, 
		wc.lpszClassName, L"StandUp - OpenGL", 
		WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
		0, 0, 1024, 768,
		NULL, NULL, hInstance, NULL );
	
	// enable OpenGL for the window
	EnableOpenGL( OpenGLWindowHandle, &OpenGLDCHandle, &OpenGLHandle );
}

void UpdateOpenGLContext(MSG& msg) {
	// program main loop
	while ( !quit )
	{

		// check for messages
		if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE )  )
		{

			// handle or dispatch messages
			if ( msg.message == WM_QUIT ) 
			{
				quit = TRUE;
			} 
			else 
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
		} 
		else 
		{

			// OpenGL animation code goes here

			glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
			glClear( GL_COLOR_BUFFER_BIT );

			glPushMatrix();
			glRotatef( theta, 0.0f, 0.0f, 1.0f );
			glBegin( GL_TRIANGLES );
			glColor3f( 1.0f, 0.0f, 0.0f ); glVertex2f( 0.0f, 1.0f );
			glColor3f( 0.0f, 1.0f, 0.0f ); glVertex2f( 0.87f, -0.5f );
			glColor3f( 0.0f, 0.0f, 1.0f ); glVertex2f( -0.87f, -0.5f );
			glEnd();
			glPopMatrix();

			SwapBuffers( OpenGLDCHandle );

			theta += 1.0f;

		}

	}

	// shutdown OpenGL
	DisableOpenGL( OpenGLWindowHandle, OpenGLDCHandle, OpenGLHandle );

	// destroy the window explicitly
	DestroyWindow(Win32WindowHandle);
	DestroyWindow(OpenGLWindowHandle);
}

//
//  FUNKTION: ApplicationRegisterClass()
//
//  ZWECK: Registriert die Fensterklasse.
//
ATOM ApplicationRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_STANDUP_WIN32));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_STANDUP_WIN32);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNKTION: InitInstance(HINSTANCE, int)
//
//   ZWECK: Speichert das Instanzenhandle und erstellt das Hauptfenster.
//
//   KOMMENTARE:
//
//        In dieser Funktion wird das Instanzenhandle in einer globalen Variablen gespeichert, und das
//        Hauptprogrammfenster wird erstellt und angezeigt.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{

   hInst = hInstance; // Instanzenhandle in der globalen Variablen speichern

   Win32WindowHandle = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!Win32WindowHandle)
   {
      return FALSE;
   }

   ShowWindow(Win32WindowHandle, nCmdShow);
   UpdateWindow(Win32WindowHandle);

   return TRUE;
}

//
//  FUNKTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ZWECK:  Verarbeitet Meldungen vom Hauptfenster.
//
//  WM_COMMAND	- Verarbeiten des Anwendungsmenüs
//  WM_PAINT	- Zeichnen des Hauptfensters
//  WM_DESTROY	- Beenden-Meldung anzeigen und zurückgeben
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Menüauswahl bearbeiten:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			quit = TRUE;
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Hier den Zeichnungscode hinzufügen.
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Meldungshandler für Infofeld.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


// Opengl Window Procedure
LRESULT CALLBACK GLWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	switch (message)
	{
		
	case WM_CREATE:
		return 0;
		
	case WM_CLOSE:

		PostQuitMessage(0);
		return 0;
		
	case WM_DESTROY:
		return 0;
		
	case WM_KEYDOWN:
		switch ( wParam )
		{
			
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;
			
		}
		return 0;
	
	default:
		return DefWindowProc( hWnd, message, wParam, lParam );
			
	}
	
}

// Enable OpenGL
void EnableOpenGL(HWND hWnd, HDC * hDC, HGLRC * hRC)
{
	PIXELFORMATDESCRIPTOR pfd;
	int format;
	
	// get the device context (DC)
	*hDC = GetDC( hWnd );
	
	// set the pixel format for the DC
	ZeroMemory( &pfd, sizeof( pfd ) );
	pfd.nSize = sizeof( pfd );
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;
	format = ChoosePixelFormat( *hDC, &pfd );
	SetPixelFormat( *hDC, format, &pfd );
	
	// create and enable the render context (RC)
	*hRC = wglCreateContext( *hDC );
	wglMakeCurrent( *hDC, *hRC );
	
}

// Disable OpenGL
void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC)
{
	wglMakeCurrent( NULL, NULL );
	wglDeleteContext( hRC );
	ReleaseDC( hWnd, hDC );
}
