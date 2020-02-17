#include "Types.h"
#include "Defines.h"
#include "Engine.h"




int main( int argc, const char** argv ) {
    Regen::Engine* engine = new Regen::Engine( "Regen" );
    engine->Run();
    delete engine;
    return 0;
}