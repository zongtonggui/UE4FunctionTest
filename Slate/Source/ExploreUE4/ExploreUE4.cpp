// Fill out your copyright notice in the Description page of Project Settings.

#include "ExploreUE4.h"
#include "Modules/ModuleManager.h"
#include "UMG/MenuStyles.h"
#include "SlateStyleRegistry.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, ExploreUE4, "ExploreUE4" );
//Custom implementation of the Default Game Module.
class FSlateTutorialsGameModule : public FDefaultGameModuleImpl
{
	// Called whenever the module is starting up. In here, we unregister any style sets 
	// (which may have been added by other modules) sharing our 
	// style set's name, then initialize our style set. 
	virtual void StartupModule() override
	{
		//Hot reload hack
		FSlateStyleRegistry::UnRegisterSlateStyle(FMenuStyles::GetStyleSetName());
		//FMenuStyles::Initialize();
	}

	// Called whenever the module is shutting down. Here, we simply tell our MenuStyles to shut down.
	virtual void ShutdownModule() override
	{
		FMenuStyles::Shutdown();
	}

};