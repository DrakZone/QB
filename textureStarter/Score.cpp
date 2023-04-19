#include <sstream>
#include <DDSTextureLoader.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <iomanip>

#include "SpriteBatch.h"

#include "Score.h"
#include "CommonStates.h"



//Start of Score class
//-----------------------------------------------------------------------------
void Score::initialise() {
	amount_ = 0;
	value = 1;
}
int Score::getAmount() const {
	return amount_;
}
//increment when value>0, decrement otherwise
void Score::updateAmount(int value) {
	amount_ += value;
}
//--------end of Score class
//-----------------------------------------------------------------------------

void Font::Initiallise(MyD3D& d3d)
{
	assert(md3d == nullptr);
	md3d = &d3d;

	pSpriteBatch = new SpriteBatch(&md3d->GetDeviceCtx());
	assert(pSpriteBatch);

	pSpriteFont = new SpriteFont(&md3d->GetDevice(), L"../bin/data/digital-8.spritefont");
	assert(pSpriteFont);

}

void Font::Erase()
{
	delete pSpriteFont;
	pSpriteFont = nullptr;
	delete pSpriteBatch;
	pSpriteBatch = nullptr;
}

void Font::Print()
{
	//stringstream ss;
	//ss << score.getAmount();
	//string str = ss.str();
	stringstream strs;
	strs << score.getAmount();
	string temp_str = strs.str();
	char* char_type = (char*)temp_str.c_str();

	CommonStates dxstate(&md3d->GetDevice());
	pSpriteBatch->Begin(SpriteSortMode_Deferred, dxstate.NonPremultiplied());

	pSpriteFont->DrawString(pSpriteBatch, "Score:", Vector3(0, 0, 0), Colours::Blue, 0.0f, Origin, Scale);

	pSpriteFont->DrawString(pSpriteBatch, char_type, Vector3(190, 0, 0), Colours::Blue, 0.0f, Origin, Scale);

	pSpriteBatch->End();
}