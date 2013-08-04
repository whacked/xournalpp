/*
 * Xournal++
 *
 * Undo action for insert (write text, draw stroke...)
 *
 * @author Xournal Team
 * http://xournal.sf.net
 *
 * @license GPL
 */

#ifndef __TEXTBOXUNDOACTION_H__
#define __TEXTBOXUNDOACTION_H__

#include "UndoAction.h"

class XojPage;
class Layer;
class Element;
class Redrawable;

class TextBoxUndoAction: public UndoAction {
public:
	TextBoxUndoAction(PageRef page, Layer * layer, Element * element, Element * oldelement, Redrawable * view);
	virtual ~TextBoxUndoAction();

public:
	virtual bool undo(Control * control);
	virtual bool redo(Control * control);

	virtual String getText();

private:
	XOJ_TYPE_ATTRIB;

	Layer * layer;
	Element * element;
	Element * oldelement;
	Redrawable * view;
};

#endif /* __TEXTBOXUNDOACTION_H__ */
