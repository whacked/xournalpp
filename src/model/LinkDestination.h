/*
 * Xournal++
 *
 * A link destination in a PDF Document
 *
 * @author Xournal Team
 * http://xournal.sf.net
 *
 * @license GPL
 */

#ifndef __LINKDESTINATION_H__
#define __LINKDESTINATION_H__

#include <gtk/gtk.h>
#include <String.h>

typedef struct _LinkDest XojLinkDest;
typedef struct _LinkDestClass XojLinkDestClass;

class LinkDestination {
public:
	LinkDestination();
	virtual ~LinkDestination();

public:
	int getPdfPage();
	void setPdfPage(int page);

	void setExpand(bool expand);
	bool getExpand();

	bool shouldChangeLeft();
	bool shouldChangeZoom();
	bool shouldChangeTop();

	double getZoom();
	double getLeft();
	double getTop();

	void setChangeLeft(double left);
	void setChangeZoom(double zoom);
	void setChangeTop(double top);

	void setName(String name);
	String getName();
private:
	XOJ_TYPE_ATTRIB;

	int page;
	bool expand;

	double left;
	double top;
	double zoom;

	bool changeLeft;
	bool changeZoom;
	bool changeTop;

	String name;
};

struct _LinkDest {
	GObject base_instance;
	LinkDestination *dest;
};

enum {
	DOCUMENT_LINKS_COLUMN_NAME,
	DOCUMENT_LINKS_COLUMN_LINK,
	DOCUMENT_LINKS_COLUMN_EXPAND,
	DOCUMENT_LINKS_COLUMN_PAGE_NUMBER
};

#define TYPE_LINK_DEST              (link_dest_get_type())
#define LINK_DEST(object)           (G_TYPE_CHECK_INSTANCE_CAST((object), TYPE_LINK_DEST, XojLinkDest))
#define LINK_DEST_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST((klass), TYPE_LINK_DEST, XojLinkDestClass))
#define IS_LINK_DEST(object)        (G_TYPE_CHECK_INSTANCE_TYPE((object), TYPE_LINK_DEST))
#define IS_LINK_DEST_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE((klass), TYPE_LINK_DEST))
#define LINK_DEST_GET_CLASS(object) (G_TYPE_INSTANCE_GET_CLASS((object), TYPE_LINK_DEST, XojLinkDestClass))

GType link_dest_get_type(void) G_GNUC_CONST;
XojLinkDest * link_dest_new();

#endif /* __LINKDESTINATION_H__ */
