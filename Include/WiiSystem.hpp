#ifndef ADVENTURE_SYSTEM_WII_HPP_
#define ADVENTURE_SYSTEM_WII_HPP_

#include <string>

#include "ISystem.hpp"
#include "WiiDisplay.hpp"

namespace Adventure
{
	class WiiSystem : public ISystem
	{
		public:
			WiiSystem();
			~WiiSystem();
			
			IDisplay& GetDisplay();
			const IDisplay& GetDisplay() const;
			
			bool SetApplicationPath(const std::string& path);
			const std::string& GetApplicationPath() const;
			
			bool Initialize();
			
			static const std::string DefaultApplicationPath;
		
		private:
			std::string applicationPath;
			
			WiiDisplay display;
	};
}

#endif
