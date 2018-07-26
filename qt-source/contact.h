#ifndef CONTACT_H
#define CONTACT_H
#include <QWidget>
#include "login.h"
#include <QPixmap>
#include <QDesktopServices>
#include <QUrl>

/** \namespace Ui
 *	
 * 	Created by Qt. All UI-defined widgets are under this namespace
 */
namespace Ui 
{
	/**	External widget created by the QT UI editor that is used by the contact class.
	 *	Manages all widgets and layouts.
  	 */
	class contact;
}

/**	Implements a QWidget as a pop-up window that allows a user to contact the development team. */
class contact : public QWidget
{
    Q_OBJECT
public:

    /** Alternate constructor. Initializes widgets. */
    explicit contact(QMainWindow *previous, QWidget *parent = nullptr);
	
	/** Destroys all child widgets and layouts */
    ~contact(){};

private slots:

	/** Opens up the users default mail application with a email template to send to the team. */
    void on_pushButton_clicked();
	
	/** Closes this widget and returns to the Login widget. */
    void on_pushButton_2_clicked();

private:
    Ui::contact *ui;
    QMainWindow* m_login;
};

#endif // CONTACT_H
