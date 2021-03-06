#include "MenuItem.h"

MenuItem::MenuItem(ActionHandler * handler, GtkWidget * widget, ActionType type) :
	AbstractItem(NULL, handler, type, widget) {
	XOJ_INIT_TYPE(MenuItem);
}

MenuItem::MenuItem(ActionHandler * handler, GtkWidget * widget, ActionType type, ActionGroup group) :
	AbstractItem(NULL, handler, type, widget) {
	XOJ_INIT_TYPE(MenuItem);
	this->group = group;
}

MenuItem::~MenuItem() {
	XOJ_RELEASE_TYPE(MenuItem);
}
