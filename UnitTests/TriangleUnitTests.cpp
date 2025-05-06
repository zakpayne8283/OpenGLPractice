#include "pch.h"
#include "CppUnitTest.h"

#include "../Triangle.h" // TODO: Fix this pathing issue caused by my setup

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// Custom ToString methods for testing
namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {
			template <>
			inline std::wstring ToString<Triangle>(const Triangle& w) {
				return L"Triangle()";
			}
		}
	}
}

namespace UnitTests
{
	TEST_CLASS(WindowUnitTests)
	{
	public:
		TEST_METHOD(TriangleCreation)
		{

		}
	};
}
