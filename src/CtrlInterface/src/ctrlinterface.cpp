#include "ctrlinterface.hpp"

CtrlInterface::CtrlInterface(std::string configpath)
{
    m_configpath = configpath;
    std::cout << "CtrlInterface: " << m_configpath << std::endl;
}

CtrlInterface::~CtrlInterface()
{
    std::cout << "Destruct CtrlInterface" << std::endl;
}

void CtrlInterface::run()
{
    std::cout << "CtrlInterface Running" << std::endl;
    m_cmdq = 1;
    m_tlmq = 1;
    std::cout << "CtrlInterface Done: " << m_cmdq << "   " << m_tlmq << std::endl;
}
