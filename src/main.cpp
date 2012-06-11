#include "main.h"
#include "IntroGameState.h"


DRReturn load()
{
	if(EnInit_INI("data/config.ini"))
		LOG_ERROR("Fehler bei init OpenGL", DR_ERROR);  
	return DR_OK;
}

void exit()
{
	EnExit();
}


#ifdef _WIN32
#undef main
#endif

int main()
{
	if(load())
	{
		printf("error by load\n");
		exit();
		return -1;
	}
	if(EnGameLoop(DRGameStatePtr(new IntroGameState), false))
	{
		printf("error in gameLoop\n");
		exit();
		return -1;
	}
	exit();
    return 42;
}