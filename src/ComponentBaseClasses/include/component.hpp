#include <thread>
#include <iostream>

class ProcessorElementBase
// "client server" or "remote gpio" or "MQTT"
{
};

class ServerElement : ProcessorElementBase
{
};

class ClientElement : ProcessorElementBase
{
};

class ComponentThreadBase
{
  public:
      ComponentThreadBase(bool start=false) : m_running(start)
      {
          if (start) this->start();
      }

      virtual ~ComponentThreadBase()
      {
	  m_running = false;
	  m_thread.join();
      }

      bool start()
      {
	  if (m_running) return false;
	  m_thread = std::thread(&ComponentThreadBase::run, this);
	  m_running = true;
	  return true;
      }

      bool restart()
      {
          return true;
      }

      bool stop()
      {
	  if (!m_running) return false;
	  m_running = false;
	  return true;
      }

   protected:
      virtual void run() = 0;

   protected:
      int m_cmdq = 0;
      int m_tlmq = 0;
      bool m_running;
      std::thread m_thread;
};
