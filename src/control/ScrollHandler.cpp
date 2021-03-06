#include "ScrollHandler.h"
#include "Control.h"
#include "../gui/XournalView.h"
#include "../gui/widgets/SpinPageAdapter.h"

ScrollHandler::ScrollHandler(Control * control) {
	XOJ_INIT_TYPE(ScrollHandler);

	this->control = control;
}

ScrollHandler::~ScrollHandler() {
	XOJ_RELEASE_TYPE(ScrollHandler);
}

void ScrollHandler::goToPreviousPage() {
	XOJ_CHECK_TYPE(ScrollHandler);

	if (this->control->getWindow()) {
		scrollToPage(this->control->getWindow()->getXournal()->getCurrentPage() - 1);
	}
}

void ScrollHandler::goToNextPage() {
	XOJ_CHECK_TYPE(ScrollHandler);

	if (this->control->getWindow()) {
		scrollToPage(this->control->getWindow()->getXournal()->getCurrentPage() + 1);
	}
}

void ScrollHandler::scrollToPage(PageRef page, double top) {
	XOJ_CHECK_TYPE(ScrollHandler);

	Document * doc = this->control->getDocument();

	doc->lock();
	int p = doc->indexOf(page);
	doc->unlock();

	if (p != -1) {
		scrollToPage(p, top);
	}
}

void ScrollHandler::scrollToPage(int page, double top) {
	XOJ_CHECK_TYPE(ScrollHandler);

	if (this->control->getWindow()) {
		this->control->getWindow()->getXournal()->scrollTo(page, top);
	}
}

void ScrollHandler::scrollToSpinPange() {
	XOJ_CHECK_TYPE(ScrollHandler);

	if (!this->control->getWindow()) {
		return;
	}
	SpinPageAdapter * spinPageNo = this->control->getWindow()->getSpinPageNo();
	int page = spinPageNo->getPage();
	if (page == 0) {
		return;
	}
	scrollToPage(page - 1);
}

void ScrollHandler::scrollToAnnotatedPage(bool next) {
	XOJ_CHECK_TYPE(ScrollHandler);

	if (!this->control->getWindow()) {
		return;
	}

	int step;
	if (next) {
		step = 1;
	} else {
		step = -1;
	}

	Document * doc = this->control->getDocument();
	doc->lock();

	for (int i = this->control->getCurrentPageNo() + step; i >= 0 && i < doc->getPageCount(); i += step) {
		if (doc->getPage(i).isAnnotated()) {
			scrollToPage(i);
			break;
		}
	}

	doc->unlock();
}

bool ScrollHandler::isPageVisible(int page, int * visibleHeight) {
	XOJ_CHECK_TYPE(ScrollHandler);

	if (!this->control->getWindow()) {
		if(visibleHeight) {
			*visibleHeight = 0;
		}
		return false;
	}

	return this->control->getWindow()->getXournal()->isPageVisible(page, visibleHeight);
}

void ScrollHandler::pageChanged(int page) {
	XOJ_CHECK_TYPE(ScrollHandler);

	scrollToSpinPange();
}


