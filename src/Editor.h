#pragma once

#include "SDL.h"
#include "Listener.h"

struct PlayerState;
struct Renderer;
struct EditorState;

/*

The Editor class is the base class for all GUI elements.

*/

class Editor: public Listener
{
public:
	static const int maxChildren = 128;
	
	enum MessageClass 
	{
		MessageInfo,
		MessageError
	};	
private:
	Editor *mFocus;
	
	void drawModal(Renderer& renderer, const SDL_Rect& area);
	virtual void onDraw(Renderer& renderer, const SDL_Rect& area) = 0;
	void drawChildren(Renderer& renderer, const SDL_Rect& area);
	
protected:
	Editor *mModal;
	EditorState& mEditorState;
	bool mIsDirty, mRedraw;
	Editor *mParent;
	Editor *mChildren[maxChildren];
	SDL_Rect mChildrenArea[maxChildren];
	int mNumChildren;
	bool mWantsFocus;
	
	void removeFocus();
	void setModal(Editor *modal);
	
	void drawCoveredChildren(Renderer& renderer, const SDL_Rect& area, const SDL_Rect& childArea, int maxIndex);
	
	void invalidateAll();
	void invalidateParent();
	
	bool shouldRedrawBackground() const;
	
	static bool pointInRect(const SDL_Point& point, const SDL_Rect& rect);
	static bool intersectRect(const SDL_Rect& a, const SDL_Rect& b, SDL_Rect& result);
	
public:
	Editor(EditorState& editorState, bool wantFocus = true);
	virtual ~Editor();
	
	void addChild(Editor *child, int x, int y, int w, int h);
	
	void setDirty(bool dirty);
	virtual void onFileSelectorEvent(const Editor& fileSelector, bool accept);
	virtual void onMessageBoxEvent(const Editor& messageBox, int code);
	virtual void onListenableChange(Listenable *listenable);
	virtual bool isDirty() const;
	bool isFocusable() const;
	bool hasDirty() const;
	void setFocus(Editor *editor);
	Editor * getFocus();
	bool hasFocus();
	
	virtual void showMessage(MessageClass messageClass, const char* message);
	void showMessageV(MessageClass messageClass, const char* message, ...) __attribute__((format(printf, 3, 4)));
	void draw(Renderer& renderer, const SDL_Rect& area);
	virtual void onUpdate(int ms);
	void update(int ms);

	/* onEvent() should return false if the event was not consumed
	 * so that the parent Editor knows to process it.
	 */
	virtual bool onEvent(SDL_Event& event);
};
