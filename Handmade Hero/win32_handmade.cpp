#include <windows.h>

LRESULT CALLBACK MainWindowCallback(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;

	switch(message)
	{
		case WM_SIZE:
		{
			OutputDebugStringA("WM_SIZE");
		} break;
		case WM_DESTROY:
		{
			OutputDebugStringA("WM_DESTROY");
		} break;
		case WM_CLOSE:
		{
			OutputDebugStringA("WM_CLOSE");
		} break;
		case WM_ACTIVATEAPP:
		{
			OutputDebugStringA("WM_ACTIVATEAPP");
		} break;
		case WM_PAINT:
		{
			PAINTSTRUCT paint;
			HDC deviceContext = BeginPaint(window, &paint);

			int x = paint.rcPaint.left;
			int y = paint.rcPaint.top;
			int height = paint.rcPaint.bottom - paint.rcPaint.top;
			int width = paint.rcPaint.right - paint.rcPaint.left;

			static DWORD operation = WHITENESS;

			PatBlt(deviceContext, x, y,width, height, operation);

			if (operation == WHITENESS)
			{
				operation = BLACKNESS;
			}
			else
			{
				operation = WHITENESS;
			}

			EndPaint(window, &paint);
		} break;
		default: 
		{
			result = DefWindowProc(window, message, wParam, lParam);
		} break;
	}

	return result;
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCommandLine, int nShowCmd)
{
	WNDCLASS windowClass {};


	windowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = MainWindowCallback;
	windowClass.hInstance = hInstance;
	//windowClass.hIcon = ;
	windowClass.lpszClassName = "Handmade Hero";

	if (RegisterClass(&windowClass))
	{
		const HWND windowHandle = CreateWindowEx
		(
			0,
			windowClass.lpszClassName,
			"Handmade Hero",
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			nullptr,
			nullptr,
			hInstance,
			nullptr
		);

		if (windowHandle)
		{
			MSG message;
			BOOL messageResult;

			while ((messageResult = GetMessage(&message, nullptr, 0, 0)))
			{
				if (messageResult == -1)
				{
					break;
				}

				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}
		else
		{
			
		}
	}
	else
	{
		
	}

	return 0;
}