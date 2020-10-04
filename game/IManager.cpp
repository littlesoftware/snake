#include "IManager.h"
#include "log/Logger.h"
#include "common/Exception.h"

#include<sstream>

lsoft::IManager::IManager()
{
}

lsoft::IManager::~IManager()
{
}

void lsoft::IManager::run()
{
    if(!_model)
        log::Logger::system().critical("Model not created");
    if(!_view)
        log::Logger::system().critical("View not created");
    try{
        _model->attach(_view.get());
        _view->initialize();
        _model->initialize();
        _view->run();
        _model->clean();
        _view->clean();
        _model->detach(_view.get());
    }catch(Exception &e)
    {
        std::stringstream ss;
        ss << "Error: ";
        ss << e.what();
        log::Logger::system().critical(ss.str());
    }catch(...)
    {
        log::Logger::system().critical("Unknown error");
    }
}
