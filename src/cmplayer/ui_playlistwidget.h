/********************************************************************************
** Form generated from reading ui file 'playlistwidget.ui'
**
** Created: Thu Mar 12 09:58:05 2009
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_PLAYLISTWIDGET_H
#define UI_PLAYLISTWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableView>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlayListWidget
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QToolButton *open_button;
    QToolButton *add_button;
    QToolButton *erase_button;
    QToolButton *up_button;
    QToolButton *down_button;
    QToolButton *clear_button;
    QToolButton *save_button;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *spacerItem;
    QToolButton *close_button;
    QTableView *list;
    QCheckBox *shutdown_check;

    void setupUi(QWidget *PlayListWidget)
    {
    if (PlayListWidget->objectName().isEmpty())
        PlayListWidget->setObjectName(QString::fromUtf8("PlayListWidget"));
    PlayListWidget->resize(256, 255);
    vboxLayout = new QVBoxLayout(PlayListWidget);
    vboxLayout->setMargin(0);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(0);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    open_button = new QToolButton(PlayListWidget);
    open_button->setObjectName(QString::fromUtf8("open_button"));
    open_button->setFocusPolicy(Qt::NoFocus);
    QIcon icon;
    icon.addPixmap(QPixmap(QString::fromUtf8(":/img/document-open.png")), QIcon::Normal, QIcon::Off);
    open_button->setIcon(icon);
    open_button->setAutoRaise(true);

    hboxLayout->addWidget(open_button);

    add_button = new QToolButton(PlayListWidget);
    add_button->setObjectName(QString::fromUtf8("add_button"));
    add_button->setFocusPolicy(Qt::NoFocus);
    QIcon icon1;
    icon1.addPixmap(QPixmap(QString::fromUtf8(":/img/list-add.png")), QIcon::Normal, QIcon::Off);
    add_button->setIcon(icon1);
    add_button->setAutoRaise(true);

    hboxLayout->addWidget(add_button);

    erase_button = new QToolButton(PlayListWidget);
    erase_button->setObjectName(QString::fromUtf8("erase_button"));
    erase_button->setFocusPolicy(Qt::NoFocus);
    QIcon icon2;
    icon2.addPixmap(QPixmap(QString::fromUtf8(":/img/list-remove.png")), QIcon::Normal, QIcon::Off);
    erase_button->setIcon(icon2);
    erase_button->setAutoRaise(true);

    hboxLayout->addWidget(erase_button);

    up_button = new QToolButton(PlayListWidget);
    up_button->setObjectName(QString::fromUtf8("up_button"));
    up_button->setFocusPolicy(Qt::NoFocus);
    QIcon icon3;
    icon3.addPixmap(QPixmap(QString::fromUtf8(":/img/arrow-up.png")), QIcon::Normal, QIcon::Off);
    up_button->setIcon(icon3);
    up_button->setAutoRaise(true);

    hboxLayout->addWidget(up_button);

    down_button = new QToolButton(PlayListWidget);
    down_button->setObjectName(QString::fromUtf8("down_button"));
    down_button->setFocusPolicy(Qt::NoFocus);
    QIcon icon4;
    icon4.addPixmap(QPixmap(QString::fromUtf8(":/img/arrow-down.png")), QIcon::Normal, QIcon::Off);
    down_button->setIcon(icon4);
    down_button->setAutoRaise(true);

    hboxLayout->addWidget(down_button);

    clear_button = new QToolButton(PlayListWidget);
    clear_button->setObjectName(QString::fromUtf8("clear_button"));
    clear_button->setFocusPolicy(Qt::NoFocus);
    QIcon icon5;
    icon5.addPixmap(QPixmap(QString::fromUtf8(":/img/edit-clear-list.png")), QIcon::Normal, QIcon::Off);
    clear_button->setIcon(icon5);
    clear_button->setAutoRaise(true);

    hboxLayout->addWidget(clear_button);

    save_button = new QToolButton(PlayListWidget);
    save_button->setObjectName(QString::fromUtf8("save_button"));
    save_button->setFocusPolicy(Qt::NoFocus);
    QIcon icon6;
    icon6.addPixmap(QPixmap(QString::fromUtf8(":/img/document-save.png")), QIcon::Normal, QIcon::Off);
    save_button->setIcon(icon6);
    save_button->setAutoRaise(true);

    hboxLayout->addWidget(save_button);

    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(0);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    spacerItem = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout1->addItem(spacerItem);

    close_button = new QToolButton(PlayListWidget);
    close_button->setObjectName(QString::fromUtf8("close_button"));
    close_button->setFocusPolicy(Qt::NoFocus);
    QIcon icon7;
    icon7.addPixmap(QPixmap(QString::fromUtf8(":/img/window-close.png")), QIcon::Normal, QIcon::Off);
    close_button->setIcon(icon7);
    close_button->setAutoRaise(true);

    hboxLayout1->addWidget(close_button);


    hboxLayout->addLayout(hboxLayout1);


    vboxLayout->addLayout(hboxLayout);

    list = new QTableView(PlayListWidget);
    list->setObjectName(QString::fromUtf8("list"));
    list->setAlternatingRowColors(true);
    list->setSelectionBehavior(QAbstractItemView::SelectRows);
    list->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    list->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

    vboxLayout->addWidget(list);

    shutdown_check = new QCheckBox(PlayListWidget);
    shutdown_check->setObjectName(QString::fromUtf8("shutdown_check"));

    vboxLayout->addWidget(shutdown_check);


    retranslateUi(PlayListWidget);

    QMetaObject::connectSlotsByName(PlayListWidget);
    } // setupUi

    void retranslateUi(QWidget *PlayListWidget)
    {

#ifndef QT_NO_TOOLTIP
    open_button->setToolTip(QApplication::translate("PlayListWidget", "Open", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP

    open_button->setText(QString());

#ifndef QT_NO_TOOLTIP
    add_button->setToolTip(QApplication::translate("PlayListWidget", "Add", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP

    add_button->setText(QString());

#ifndef QT_NO_TOOLTIP
    erase_button->setToolTip(QApplication::translate("PlayListWidget", "Erase", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP

    erase_button->setText(QString());

#ifndef QT_NO_TOOLTIP
    up_button->setToolTip(QApplication::translate("PlayListWidget", "Up", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP

    up_button->setText(QString());

#ifndef QT_NO_TOOLTIP
    down_button->setToolTip(QApplication::translate("PlayListWidget", "Down", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP

    down_button->setText(QString());

#ifndef QT_NO_TOOLTIP
    clear_button->setToolTip(QApplication::translate("PlayListWidget", "Clear", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP

    clear_button->setText(QString());

#ifndef QT_NO_TOOLTIP
    save_button->setToolTip(QApplication::translate("PlayListWidget", "Save", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP

    save_button->setText(QString());

#ifndef QT_NO_TOOLTIP
    close_button->setToolTip(QApplication::translate("PlayListWidget", "Close", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP

    close_button->setText(QApplication::translate("PlayListWidget", "...", 0, QApplication::UnicodeUTF8));
    shutdown_check->setText(QApplication::translate("PlayListWidget", "Shutdown when the list finished", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(PlayListWidget);
    } // retranslateUi

};

namespace Ui {
    class PlayListWidget: public Ui_PlayListWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYLISTWIDGET_H
