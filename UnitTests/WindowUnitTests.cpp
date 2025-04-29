#include "pch.h"
#include "CppUnitTest.h"

#include "../Window.h" // TODO: Fix this pathing issue caused by my setup

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// Custom ToString methods for testing
namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {
			template <>
			inline std::wstring ToString<Window>(const Window& w) {
				return L"Window()";
			}
		}
	}
}

namespace UnitTests
{
	TEST_CLASS(WindowUnitTests)
	{
	public:

		TEST_METHOD(ClassInstantiation)
		{
			Window* newWindow = new Window();

			Assert::IsNotNull(newWindow);

			delete newWindow;
		}
	};
}
