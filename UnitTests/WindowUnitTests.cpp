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
		TEST_METHOD(WindowInitializeDefault)
		{
			// Initialize without parameters - use defaults
			Window::initialize();

			// Window should not null
			Assert::IsNotNull(Window::getWindow());

			// Tear down (ignore exit())
			Window::teardown(true);
		}

		TEST_METHOD(WindowInitializeWithParameters)
		{
			// Initialize with custom parameters
			Window::initialize(1600, 900, "Custom Title");

			// TODO: Make sure the initialized parameters are active (e.g. window name should match)

			// Window should not null
			Assert::IsNotNull(Window::getWindow());

			// Tear down (ignore exit())
			Window::teardown(true);
		}
	};
}
