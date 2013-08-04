#include "InsertDeletePageUndoAction.h"
#include "../model/PageRef.h"
#include "../model/Document.h"
#include "../control/Control.h"
#include "../gui/Cursor.h"

InsertDeletePageUndoAction::InsertDeletePageUndoAction(PageRef page, int pagePos, bool inserted) : UndoAction("InsertDeletePageUndoAction") {
	XOJ_INIT_TYPE(InsertDeletePageUndoAction);

	this->inserted = inserted;
	this->page = page;
	this->pagePos = pagePos;
}

InsertDeletePageUndoAction::~InsertDeletePageUndoAction() {
	XOJ_CHECK_TYPE(InsertDeletePageUndoAction);

	this->page = NULL;

	XOJ_RELEASE_TYPE(InsertDeletePageUndoAction);
}

bool InsertDeletePageUndoAction::undo(Control * control) {
	XOJ_CHECK_TYPE(InsertDeletePageUndoAction);

	if (this->inserted) {
		return deletePage(control);
	} else {
		return insertPage(control);
	}
}

bool InsertDeletePageUndoAction::redo(Control * control) {
	XOJ_CHECK_TYPE(InsertDeletePageUndoAction);

	if (this->inserted) {
		return insertPage(control);
	} else {
		return deletePage(control);
	}
}

bool InsertDeletePageUndoAction::insertPage(Control * control) {
	XOJ_CHECK_TYPE(InsertDeletePageUndoAction);

	Document * doc = control->getDocument();

	//just in case there would be a hang here,
	//we'll clear the selection in redo as well
	control->clearSelectionEndText();

	doc->lock();
	doc->insertPage(this->page, this->pagePos);
	doc->unlock();

	control->firePageInserted(this->pagePos);
	control->getCursor()->updateCursor();
	control->getScrollHandler()->scrollToPage(this->pagePos);
	control->updateDeletePageButton();

	return true;
}

bool InsertDeletePageUndoAction::deletePage(Control * control) {
	XOJ_CHECK_TYPE(InsertDeletePageUndoAction);

	Document * doc = control->getDocument();

	//in order to fix the hang, we need to get out
	//of text mode
	//***This might kill whatever we've got selected
	control->clearSelectionEndText();

	doc->lock();
	int pNr = doc->indexOf(page);
	if (pNr == -1) {
		doc->unlock();
		// this should not happen
		return false;
	}

	// first send event, then delete page...
	control->firePageDeleted(pNr);
	doc->deletePage(pNr);

	control->updateDeletePageButton();

	doc->unlock();
	return true;
}

String InsertDeletePageUndoAction::getText() {
	XOJ_CHECK_TYPE(InsertDeletePageUndoAction);

	if (this->inserted) {
		return _("Page inserted");
	} else {
		return _("Page deleted");
	}
}
