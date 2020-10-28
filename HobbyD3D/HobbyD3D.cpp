#include "pch.h"
#include "Logger.h"
#include "Engine.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	Engine engine = Engine(hInstance);

	BOOL bResult;
	while (bResult = engine.Update())
	{
		engine.Prepare();
		engine.Render();
	}

	return bResult == -1 ? 1 : engine.GetExitStatus();
}