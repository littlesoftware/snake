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
    if(!m_model)
        log::Logger::system().critical("Model not created");
    if(!m_view)
        log::Logger::system().critical("View not created");
    try{
        m_model->attach(m_view.get());
        m_view->initialize();
        m_model->initialize();
        m_view->run();
        m_model->clean();
        m_view->clean();
        m_model->detach(m_view.get());
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
