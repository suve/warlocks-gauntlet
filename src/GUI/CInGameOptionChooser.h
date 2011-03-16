/* Takie fajne 'okienko' co bedzie wyswietlac graczowi 4 (4?) opcje
 * do wyboru klawiszami akcji podczas gry */

#ifndef IN_GAME_OPTION_CHOOSER_H
#define IN_GAME_OPTION_CHOOSER_H

#include "CButton.h"
#include "../IFrameListener.h"

#include <string>
#include <vector>
#include <SFML/Graphics/Color.hpp>

class IOptionChooserHandler;
class CActor;

namespace GUI { class CButton; }

class CInGameOptionChooser;
typedef std::vector<CInGameOptionChooser *> InGameOptionChooserVector;

class CInGameOptionChooser
{
public:
	~CInGameOptionChooser();

    static CInGameOptionChooser * CreateChooser();

    void SetRadius(float radius);
	void SetOptions(const std::vector<std::wstring> & options);
	void SetOptionSize(const sf::Vector2f & size);
	void SetOptionImages(const std::string & normal, const std::string & mouseOver = "");
	void SetOptionFont(const std::string& name, float size);
	void SetOptionColor(const sf::Color color);

	void Show();
	void Hide();

	void Update();
    static void UpdateAll();

	inline const sf::Vector2i& GetSavedCursorPosition() {return mCursorPos;}

    void OptionSelected(size_t selected);
    void SetOptionHandler(IOptionChooserHandler * handler);
    void SetActor(CActor * actor); // w domysle: setPlayer
    bool IsVisible();

private:
	CInGameOptionChooser();
    bool mIsVisible;
	sf::Vector2i mCursorPos;
    std::vector<GUI::CButton*> mButtons;

	float mRadius;
    sf::Vector2f mOptionSize;
    std::string mOptionImageNormal;
    std::string mOptionImageMouseOver;
    sf::Color mOptionColor;
    std::string mOptionFont;
    float mOptionFontSize;

    IOptionChooserHandler * mOptionHandler;
    CActor * mActor; // ja to tak moge sobie przechowywac? Co jak ktos mi zabije tego gracza, wskaznik umrze?

	void UpdatePosition();
	void SaveCursorPosition();
	void RestoreCursorPosition();

    static InGameOptionChooserVector msActiveChoosers;
};

#endif
