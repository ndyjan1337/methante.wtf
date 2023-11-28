#include "../imgui/imgui.h"

namespace imGuiMenu {
	inline float WIDTH = 300;
	inline float HEIGHT = 300;

	inline int tabCount = 1;

	inline float areaSeparatorSpace = 8.f;
	inline float textSeparatorSpace = 4.f;


	inline ImFont* normalText;
	inline ImFont* titleText;
	inline ImFont* highlightText;
	inline ImFont* espNameText;
	inline ImFont* subTitleText;

	void renderMenu(bool state);
	void setStyle();

}