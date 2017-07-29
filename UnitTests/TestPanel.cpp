#include "stdafx.h"
#include "CppUnitTest.h"
#include "ScreenMock.h"
#include "LabelMock.h"
#include "../Components/Panel.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTests
{		

	TEST_CLASS(TestPanel)
	{
		Panel *p;
		UIComponent *label;
		std::string labelText;

	public:

		TEST_METHOD(Constructor)
		{
			p = new Panel(0, 0, CCTRL.getConsoleSize().X - 1, CCTRL.getConsoleSize().Y - 1, 
				Double, White, Black, NULL);
			Assert::IsNotNull(p);
		}

		TEST_METHOD(AddComponenet)
		{
			Constructor();
			label = new LabelMock(labelText, 5, 15, 15, 7, Double, Blue, Green);
			p->addComponent(label);
			Assert::IsTrue(true); // exception is not raised..
		}

		TEST_METHOD(Draw)
		{
			AddComponenet();
			SCREEN; // init screen mock
			p->draw();
			int textLen = labelText.length();
			int yIndex = label->getYPosition() + 1;
			int startOfText = label->getXPosition() + 1 + label->getWidth()/2 - textLen/2;

			Assert::AreEqual(labelText,
				SCREEN.getScreen()[yIndex].str().substr(startOfText, textLen));
		}
	};
}