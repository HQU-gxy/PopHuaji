#include "main.h"
#include "AppDelegate.h"
#include "AudioEngine.h"
#include "json/rapidjson.h"
#include "json/document.h"

USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR lpCmdLine,
                       int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    rapidjson::Document d;
    std::string resFile = FileUtils::getInstance()->getStringFromFile("strings.json");
    d.Parse<rapidjson::kParseDefaultFlags>(resFile.c_str());

    // create the application instance
    AppDelegate app;
    auto glView = GLViewImpl::create(d["title"].GetString());
    Director::getInstance()->setOpenGLView(glView);

    glView->setFrameSize(960, 640);

    AudioEngine::play2d("sounds/Funky-Town.mp3", true, 0.2f);

    return Application::getInstance()->run();
}
