#include "common.hpp"

extern bool isScriptSelected;
extern u32 progressBar, selected;
extern ProgressBar progressbarType;

extern std::unique_ptr<Config> config;
extern C2D_SpriteSheet sprites;

// Draws a Rectangle as the progressbar.
void Animation::DrawProgressBar(u64 currentProgress, u64 totalProgress) {
	if (config->progressDisplay()) {
		// Outline of progressbar.
		Gui::Draw_Rect(30, 120, 340, 30, BLACK);
		Gui::Draw_Rect(31, 121, (int)(((float)currentProgress / (float)totalProgress) * 338.0f), 28, isScriptSelected ? progressBar : config->progressbarColor());
	}
}

void Animation::Button(int x, int y, float speed) {
	static float timer	= 0.0f;
	float highlight_multiplier = fmax(0.0, fabs(fmod(timer, 1.0) - 0.5) / 0.5);
	u8 r, g, b;
	r	= (isScriptSelected ? selected : config->selectedColor()) & 0xFF;
	g	= ((isScriptSelected ? selected : config->selectedColor()) >> 8) & 0xFF;
	b	= ((isScriptSelected ? selected : config->selectedColor()) >> 16) & 0xFF;

	u32 color = C2D_Color32(r + (255 - r) * highlight_multiplier, g + (255 - g) * highlight_multiplier, b + (255 - b) * highlight_multiplier, 255);

	// The actual draw part.
	C2D_ImageTint tint;
	C2D_SetImageTint(&tint, C2D_TopLeft, color, 1);
	C2D_SetImageTint(&tint, C2D_TopRight, color, 1);
	C2D_SetImageTint(&tint, C2D_BotLeft, color, 1);
	C2D_SetImageTint(&tint, C2D_BotRight, color, 1);
	C2D_DrawImageAt(C2D_SpriteSheetGetImage(sprites, sprites_selector_idx), x+4, y+4, 0.5f, &tint); // +4 because to fit the button.

	timer += speed; // Speed of the animation. Example : .030f / .030
}