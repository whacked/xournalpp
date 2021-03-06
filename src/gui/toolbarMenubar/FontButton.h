/*
 * Xournal++
 *
 * Part of the customizable toolbars
 *
 * @author Xournal Team
 * http://xournal.sf.net
 *
 * @license GPL
 */

#ifndef __FONTBUTTON_H__
#define __FONTBUTTON_H__

#include "AbstractToolItem.h"
#include "../GladeGui.h"
#include "../../model/Font.h"
#include <XournalType.h>

class FontButton: public AbstractToolItem {
public:
	FontButton(ActionHandler * handler, GladeGui * gui, String id, ActionType type, String description, GtkWidget * menuitem = NULL);
	virtual ~FontButton();

public:
	virtual void activated(GdkEvent * event, GtkMenuItem * menuitem, GtkToolButton * toolbutton);
	void setFont(XojFont & font);
	XojFont getFont();
	virtual String getToolDisplayName();
	void showFontDialog();

protected:
	virtual GtkToolItem * createItem(bool horizontal);
	virtual GtkToolItem * createTmpItem(bool horizontal);
	virtual GtkToolItem * newItem();

	GtkWidget * newFontButton();
	static void setFontFontButton(GtkWidget * fontButton, XojFont & font);

	virtual GtkWidget * getNewToolIconImpl();

private:
	XOJ_TYPE_ATTRIB;


	GtkWidget * fontButton;
	GladeGui * gui;
	String description;

	XojFont font;
};

#endif /* __FONTBUTTON_H__ */
