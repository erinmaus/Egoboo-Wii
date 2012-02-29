#ifndef ADVENTURE_SYSTEM_INTERFACE_HPP_
#define ADVENTURE_SYSTEM_INTERFACE_HPP_

#include <string>

namespace Adventure
{
	class IDisplay;
	
	class ISystem
	{
		public:
			virtual ~ISystem() = 0;
			
			virtual IDisplay& GetDisplay() = 0;
			virtual const IDisplay& GetDisplay() const = 0;
			
			virtual bool SetApplicationPath(const std::string& path) = 0;
			const std::string& GetApplicationPath() const = 0;
			
			bool Initialize() = 0;
	};
}

#endif
