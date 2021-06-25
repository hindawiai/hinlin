<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2002 Roman Zippel <zippel@linux-m68k.org>
 */

#समावेश <QCheckBox>
#समावेश <QDialog>
#समावेश <QHeaderView>
#समावेश <QLineEdit>
#समावेश <QMainWinकरोw>
#समावेश <QPushButton>
#समावेश <QSettings>
#समावेश <QSplitter>
#समावेश <QStyledItemDelegate>
#समावेश <QTextBrowser>
#समावेश <QTreeWidget>

#समावेश "expr.h"

class ConfigList;
class ConfigItem;
class ConfigMainWinकरोw;

class ConfigSettings : खुला QSettings अणु
खुला:
	ConfigSettings();
	QList<पूर्णांक> पढ़ोSizes(स्थिर QString& key, bool *ok);
	bool ग_लिखोSizes(स्थिर QString& key, स्थिर QList<पूर्णांक>& value);
पूर्ण;

क्रमागत colIdx अणु
	promptColIdx, nameColIdx, dataColIdx
पूर्ण;
क्रमागत listMode अणु
	singleMode, menuMode, symbolMode, fullMode, listMode
पूर्ण;
क्रमागत optionMode अणु
	normalOpt = 0, allOpt, promptOpt
पूर्ण;

class ConfigList : खुला QTreeWidget अणु
	Q_OBJECT
	प्रकार class QTreeWidget Parent;
खुला:
	ConfigList(QWidget *parent, स्थिर अक्षर *name = 0);
	~ConfigList();
	व्योम reinit(व्योम);
	ConfigItem* findConfigItem(काष्ठा menu *);
	व्योम setSelected(QTreeWidgetItem *item, bool enable) अणु
		क्रम (पूर्णांक i = 0; i < selectedItems().size(); i++)
			selectedItems().at(i)->setSelected(false);

		item->setSelected(enable);
	पूर्ण

रक्षित:
	व्योम keyPressEvent(QKeyEvent *e);
	व्योम mousePressEvent(QMouseEvent *e);
	व्योम mouseReleaseEvent(QMouseEvent *e);
	व्योम mouseMoveEvent(QMouseEvent *e);
	व्योम mouseDoubleClickEvent(QMouseEvent *e);
	व्योम focusInEvent(QFocusEvent *e);
	व्योम contextMenuEvent(QContextMenuEvent *e);

खुला slots:
	व्योम setRootMenu(काष्ठा menu *menu);

	व्योम updateList();
	व्योम setValue(ConfigItem* item, tristate val);
	व्योम changeValue(ConfigItem* item);
	व्योम updateSelection(व्योम);
	व्योम saveSettings(व्योम);
	व्योम setOptionMode(QAction *action);
	व्योम setShowName(bool on);

संकेतs:
	व्योम menuChanged(काष्ठा menu *menu);
	व्योम menuSelected(काष्ठा menu *menu);
	व्योम itemSelected(काष्ठा menu *menu);
	व्योम parentSelected(व्योम);
	व्योम gotFocus(काष्ठा menu *);
	व्योम showNameChanged(bool on);

खुला:
	व्योम updateListAll(व्योम)
	अणु
		updateAll = true;
		updateList();
		updateAll = false;
	पूर्ण
	व्योम setAllOpen(bool खोलो);
	व्योम setParentMenu(व्योम);

	bool menuSkip(काष्ठा menu *);

	व्योम updateMenuList(ConfigItem *parent, काष्ठा menu*);
	व्योम updateMenuList(काष्ठा menu *menu);

	bool updateAll;

	bool showName;
	क्रमागत listMode mode;
	क्रमागत optionMode optMode;
	काष्ठा menu *rootEntry;
	QPalette disabledColorGroup;
	QPalette inactivedColorGroup;
	QMenu* headerPopup;

	अटल QList<ConfigList *> allLists;
	अटल व्योम updateListForAll();
	अटल व्योम updateListAllForAll();

	अटल QAction *showNormalAction, *showAllAction, *showPromptAction;
पूर्ण;

class ConfigItem : खुला QTreeWidgetItem अणु
	प्रकार class QTreeWidgetItem Parent;
खुला:
	ConfigItem(ConfigList *parent, ConfigItem *after, काष्ठा menu *m, bool v)
	: Parent(parent, after), nextItem(0), menu(m), visible(v), goParent(false)
	अणु
		init();
	पूर्ण
	ConfigItem(ConfigItem *parent, ConfigItem *after, काष्ठा menu *m, bool v)
	: Parent(parent, after), nextItem(0), menu(m), visible(v), goParent(false)
	अणु
		init();
	पूर्ण
	ConfigItem(ConfigList *parent, ConfigItem *after, bool v)
	: Parent(parent, after), nextItem(0), menu(0), visible(v), goParent(true)
	अणु
		init();
	पूर्ण
	~ConfigItem(व्योम);
	व्योम init(व्योम);
	व्योम updateMenu(व्योम);
	व्योम testUpdateMenu(bool v);
	ConfigList* listView() स्थिर
	अणु
		वापस (ConfigList*)Parent::treeWidget();
	पूर्ण
	ConfigItem* firstChild() स्थिर
	अणु
		वापस (ConfigItem *)Parent::child(0);
	पूर्ण
	ConfigItem* nextSibling()
	अणु
		ConfigItem *ret = शून्य;
		ConfigItem *_parent = (ConfigItem *)parent();

		अगर(_parent) अणु
			ret = (ConfigItem *)_parent->child(_parent->indexOfChild(this)+1);
		पूर्ण अन्यथा अणु
			QTreeWidget *_treeWidget = treeWidget();
			ret = (ConfigItem *)_treeWidget->topLevelItem(_treeWidget->indexOfTopLevelItem(this)+1);
		पूर्ण

		वापस ret;
	पूर्ण
	// TODO: Implement paपूर्णांकCell

	ConfigItem* nextItem;
	काष्ठा menu *menu;
	bool visible;
	bool goParent;

	अटल QIcon symbolYesIcon, symbolModIcon, symbolNoIcon;
	अटल QIcon choiceYesIcon, choiceNoIcon;
	अटल QIcon menuIcon, menubackIcon;
पूर्ण;

class ConfigItemDelegate : खुला QStyledItemDelegate
अणु
निजी:
	काष्ठा menu *menu;
खुला:
	ConfigItemDelegate(QObject *parent = nullptr)
		: QStyledItemDelegate(parent) अणुपूर्ण
	QWidget *createEditor(QWidget *parent,
			      स्थिर QStyleOptionViewItem &option,
			      स्थिर QModelIndex &index) स्थिर override;
	व्योम setModelData(QWidget *editor, QAbstractItemModel *model,
			  स्थिर QModelIndex &index) स्थिर override;
पूर्ण;

class ConfigInfoView : खुला QTextBrowser अणु
	Q_OBJECT
	प्रकार class QTextBrowser Parent;
	QMenu *contextMenu;
खुला:
	ConfigInfoView(QWidget* parent, स्थिर अक्षर *name = 0);
	bool showDebug(व्योम) स्थिर अणु वापस _showDebug; पूर्ण

खुला slots:
	व्योम setInfo(काष्ठा menu *menu);
	व्योम saveSettings(व्योम);
	व्योम setShowDebug(bool);
	व्योम clicked (स्थिर QUrl &url);

संकेतs:
	व्योम showDebugChanged(bool);
	व्योम menuSelected(काष्ठा menu *);

रक्षित:
	व्योम symbolInfo(व्योम);
	व्योम menuInfo(व्योम);
	QString debug_info(काष्ठा symbol *sym);
	अटल QString prपूर्णांक_filter(स्थिर QString &str);
	अटल व्योम expr_prपूर्णांक_help(व्योम *data, काष्ठा symbol *sym, स्थिर अक्षर *str);
	व्योम contextMenuEvent(QContextMenuEvent *event);

	काष्ठा symbol *sym;
	काष्ठा menu *_menu;
	bool _showDebug;
पूर्ण;

class ConfigSearchWinकरोw : खुला QDialog अणु
	Q_OBJECT
	प्रकार class QDialog Parent;
खुला:
	ConfigSearchWinकरोw(ConfigMainWinकरोw *parent);

खुला slots:
	व्योम saveSettings(व्योम);
	व्योम search(व्योम);

रक्षित:
	QLineEdit* editField;
	QPushButton* searchButton;
	QSplitter* split;
	ConfigList *list;
	ConfigInfoView* info;

	काष्ठा symbol **result;
पूर्ण;

class ConfigMainWinकरोw : खुला QMainWinकरोw अणु
	Q_OBJECT

	अक्षर *configname;
	अटल QAction *saveAction;
	अटल व्योम conf_changed(व्योम);
खुला:
	ConfigMainWinकरोw(व्योम);
खुला slots:
	व्योम changeMenu(काष्ठा menu *);
	व्योम changeItens(काष्ठा menu *);
	व्योम setMenuLink(काष्ठा menu *);
	व्योम listFocusChanged(व्योम);
	व्योम goBack(व्योम);
	व्योम loadConfig(व्योम);
	bool saveConfig(व्योम);
	व्योम saveConfigAs(व्योम);
	व्योम searchConfig(व्योम);
	व्योम showSingleView(व्योम);
	व्योम showSplitView(व्योम);
	व्योम showFullView(व्योम);
	व्योम showIntro(व्योम);
	व्योम showAbout(व्योम);
	व्योम saveSettings(व्योम);

रक्षित:
	व्योम बंदEvent(QCloseEvent *e);

	ConfigSearchWinकरोw *searchWinकरोw;
	ConfigList *menuList;
	ConfigList *configList;
	ConfigInfoView *helpText;
	QAction *backAction;
	QAction *singleViewAction;
	QAction *splitViewAction;
	QAction *fullViewAction;
	QSplitter *split1;
	QSplitter *split2;
पूर्ण;
