#ifndef INCLUDE_CTRLINTERFACE_H
#define INCLUDE_CTRLINTERFACE_H

#include <vector>
#include <iostream>
#include "component.hpp"

class CtrlInterface : public ComponentThreadBase
{
   public:
       CtrlInterface(std::string pathname);
       ~CtrlInterface();

   protected:
       void run();

   private:
       std::string m_configpath;
       
};



#endif // INCLUDE_CTRLINTERFACE_H
