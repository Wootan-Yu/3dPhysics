#include "engine.h"

#define USE_GPU_ENGINE 0 //change to 1 to force use of high performance GPU (in my case: GEFORCE RTX 3050)
extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = USE_GPU_ENGINE;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = USE_GPU_ENGINE;
}

//caution: 

int main()
{
	Engine engine;
	engine.run();
	return 0;
}



