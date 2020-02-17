
#include "Logger.h"
#include "Platform.h"
#include "VulkanRenderer.h"
#include "Engine.h"

namespace Regen {

    Engine::Engine( const char* applicationName ) {
        Regen::Logger::Log( "Initializing Regen Engine: %d", 4 );
        _platform = new Platform( this, applicationName );
        _renderer = new VulkanRenderer( _platform );
    }

    Engine::~Engine() {

    }

    void Engine::Run() {
        _platform->StartGameLoop();
    }

    void Engine::OnLoop( const F32 deltaTime ) {

    }
}