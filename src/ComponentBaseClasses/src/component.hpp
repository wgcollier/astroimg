#include <thread>
#include <iostream>

class ProcessorElementBase
// "client server" or "remote gpio" or "MQTT"
{
}

class ServerElement : ProcessorElementBase
{
}

class ClientElement : ProcessorElementBase
{
}

class ComponentThreadBase
{
  public:
      ComponentBase(bool start=false) : m_running(start)
      {
          if (start) this->start();
      }

      virtual ~ComponentBase()
      {
	  m_running = false;
	  m_thread.join();
      }

      bool start()
      {
	  if (m_running) return false;
	  m_thread = std:thread(&ComponentBase::run, this);
	  m_running = true;
	  return true;
      }

      bool restart()
      {
          ;
      }

      bool stop()
      {
	  if (!m_running) return false;
	  m_running = false;
	  return true;
      }
}
