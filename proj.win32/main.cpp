#include "main.h"
#include "AppDelegate.h"
#include "AudioEngine.h"

USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
    auto glView = Director::getInstance()->getOpenGLView();
    if(!glView)
        glView = GLViewImpl::create("Fuck Me");
    Director::getInstance()->setOpenGLView(glView);

    glView->setViewName("popstart");
    glView->setFrameSize(960, 640);

    AudioEngine::play2d("sounds/Funky-Town.mp3", true,0.2f);

    return Application::getInstance()->run();
}
