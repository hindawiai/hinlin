<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2008 Nir Tzaअक्षर <nir.tzaअक्षर@gmail.com>
 *
 * Derived from menuconfig.
 */
#अगर_अघोषित _GNU_SOURCE
#घोषणा _GNU_SOURCE
#पूर्ण_अगर
#समावेश <माला.स>
#समावेश <strings.h>
#समावेश <मानककोष.स>

#समावेश "lkc.h"
#समावेश "nconf.h"
#समावेश <प्रकार.स>

अटल स्थिर अक्षर nconf_global_help[] =
"Help windows\n"
"------------\n"
"o  Global help:  Unless in a data entry window, pressing <F1> will give \n"
"   you the global help window, which you are just reading.\n"
"\n"
"o  A short version of the global help is available by pressing <F3>.\n"
"\n"
"o  Local help:  To get help related to the current menu entry, use any\n"
"   of <?> <h>, or if in a data entry window then press <F1>.\n"
"\n"
"\n"
"Menu entries\n"
"------------\n"
"This interface lets you select features and parameters for the kernel\n"
"build.  Kernel features can either be built-in, modularized, or removed.\n"
"Parameters must be entered as text or decimal or hexadecimal numbers.\n"
"\n"
"Menu entries beginning with following braces represent features that\n"
"  [ ]  can be built in or removed\n"
"  < >  can be built in, modularized or removed\n"
"  { }  can be built in or modularized, are selected by another feature\n"
"  - -  are selected by another feature\n"
"  XXX  cannot be selected.  Symbol Info <F2> tells you why.\n"
"*, M or whitespace inside braces means to build in, build as a module\n"
"or to exclude the feature respectively.\n"
"\n"
"To change any of these features, highlight it with the movement keys\n"
"listed below and press <y> to build it in, <m> to make it a module or\n"
"<n> to remove it.  You may press the <Space> key to cycle through the\n"
"available options.\n"
"\n"
"A trailing \"--->\" designates a submenu, a trailing \"----\" an\n"
"empty submenu.\n"
"\n"
"Menu navigation keys\n"
"----------------------------------------------------------------------\n"
"Linewise up                 <Up>\n"
"Linewise down               <Down>\n"
"Pagewise up                 <Page Up>\n"
"Pagewise down               <Page Down>\n"
"First entry                 <Home>\n"
"Last entry                  <End>\n"
"Enter a submenu             <Right>  <Enter>\n"
"Go back to parent menu      <Left>   <Esc>  <F5>\n"
"Close a help window         <Enter>  <Esc>  <F5>\n"
"Close entry window, apply   <Enter>\n"
"Close entry window, forget  <Esc>  <F5>\n"
"Start incremental, case-insensitive search for STRING in menu entries,\n"
"    no regex support, STRING is displayed in upper left corner\n"
"                            </>STRING\n"
"    Remove last character   <Backspace>\n"
"    Jump to next hit        <Down>\n"
"    Jump to previous hit    <Up>\n"
"Exit menu search mode       </>  <Esc>\n"
"Search for configuration variables with or without leading CONFIG_\n"
"                            <F8>RegExpr<Enter>\n"
"Verbose search help         <F8><F1>\n"
"----------------------------------------------------------------------\n"
"\n"
"Unless in a data entry window, key <1> may be used instead of <F1>,\n"
"<2> instead of <F2>, etc.\n"
"\n"
"\n"
"Radiolist (Choice list)\n"
"-----------------------\n"
"Use the movement keys listed above to select the option you wish to set\n"
"and press <Space>.\n"
"\n"
"\n"
"Data entry\n"
"----------\n"
"Enter the requested information and press <Enter>.  Hexadecimal values\n"
"may be entered without the \"0x\" prefix.\n"
"\n"
"\n"
"Text Box (Help Window)\n"
"----------------------\n"
"Use movement keys as listed in table above.\n"
"\n"
"Press any of <Enter> <Esc> <q> <F5> <F9> to exit.\n"
"\n"
"\n"
"Alternate configuration files\n"
"-----------------------------\n"
"nconfig supports switching between different configurations.\n"
"Press <F6> to save your current configuration.  Press <F7> and enter\n"
"a file name to load a previously saved configuration.\n"
"\n"
"\n"
"Terminal configuration\n"
"----------------------\n"
"If you use nconfig in a xterm window, make sure your TERM environment\n"
"variable specifies a terminal configuration which supports at least\n"
"16 colors.  Otherwise nconfig will look rather bad.\n"
"\n"
"If the \"stty size\" command reports the current terminalsize correctly,\n"
"nconfig will adapt to sizes larger than the traditional 80x25 \"standard\"\n"
"and display longer menus properly.\n"
"\n"
"\n"
"Single menu mode\n"
"----------------\n"
"If you prefer to have all of the menu entries listed in a single menu,\n"
"rather than the default multimenu hierarchy, run nconfig with\n"
"NCONFIG_MODE environment variable set to single_menu.  Example:\n"
"\n"
"make NCONFIG_MODE=single_menu nconfig\n"
"\n"
"<Enter> will then unfold the appropriate category, or fold it if it\n"
"is already unfolded.  Folded menu entries will be designated by a\n"
"leading \"++>\" and unfolded entries by a leading \"-->\".\n"
"\n"
"Note that this mode can eventually be a little more CPU expensive than\n"
"the default mode, especially with a larger number of unfolded submenus.\n"
"\n",
menu_no_f_inकाष्ठाions[] =
"Legend:  [*] built-in  [ ] excluded  <M> module  < > module capable.\n"
"Submenus are designated by a trailing \"--->\", empty ones by \"----\".\n"
"\n"
"Use the following keys to navigate the menus:\n"
"Move up or down with <Up> and <Down>.\n"
"Enter a submenu with <Enter> or <Right>.\n"
"Exit a submenu to its parent menu with <Esc> or <Left>.\n"
"Pressing <y> includes, <n> excludes, <m> modularizes features.\n"
"Pressing <Space> cycles through the available options.\n"
"To search for menu entries press </>.\n"
"<Esc> always leaves the current window.\n"
"\n"
"You do not have function keys support.\n"
"Press <1> instead of <F1>, <2> instead of <F2>, etc.\n"
"For verbose global help use key <1>.\n"
"For help related to the current menu entry press <?> or <h>.\n",
menu_inकाष्ठाions[] =
"Legend:  [*] built-in  [ ] excluded  <M> module  < > module capable.\n"
"Submenus are designated by a trailing \"--->\", empty ones by \"----\".\n"
"\n"
"Use the following keys to navigate the menus:\n"
"Move up or down with <Up> or <Down>.\n"
"Enter a submenu with <Enter> or <Right>.\n"
"Exit a submenu to its parent menu with <Esc> or <Left>.\n"
"Pressing <y> includes, <n> excludes, <m> modularizes features.\n"
"Pressing <Space> cycles through the available options.\n"
"To search for menu entries press </>.\n"
"<Esc> always leaves the current window.\n"
"\n"
"Pressing <1> may be used instead of <F1>, <2> instead of <F2>, etc.\n"
"For verbose global help press <F1>.\n"
"For help related to the current menu entry press <?> or <h>.\n",
radiolist_inकाष्ठाions[] =
"Press <Up>, <Down>, <Home> or <End> to navigate a radiolist, select\n"
"with <Space>.\n"
"For help related to the current entry press <?> or <h>.\n"
"For global help press <F1>.\n",
inputbox_inकाष्ठाions_पूर्णांक[] =
"Please enter a decimal value.\n"
"Fractions will not be accepted.\n"
"Press <Enter> to apply, <Esc> to cancel.",
inputbox_inकाष्ठाions_hex[] =
"Please enter a hexadecimal value.\n"
"Press <Enter> to apply, <Esc> to cancel.",
inputbox_inकाष्ठाions_string[] =
"Please enter a string value.\n"
"Press <Enter> to apply, <Esc> to cancel.",
seपंचांगod_text[] =
"This feature depends on another feature which has been configured as a\n"
"module.  As a result, the current feature will be built as a module too.",
load_config_text[] =
"Enter the name of the configuration file you wish to load.\n"
"Accept the name shown to restore the configuration you last\n"
"retrieved.  Leave empty to abort.",
load_config_help[] =
"For various reasons, one may wish to keep several different\n"
"configurations available on a single machine.\n"
"\n"
"If you have saved a previous configuration in a file other than the\n"
"default one, entering its name here will allow you to load and modify\n"
"that configuration.\n"
"\n"
"Leave empty to abort.\n",
save_config_text[] =
"Enter a filename to which this configuration should be saved\n"
"as an alternate.  Leave empty to abort.",
save_config_help[] =
"For various reasons, one may wish to keep several different\n"
"configurations available on a single machine.\n"
"\n"
"Entering a file name here will allow you to later retrieve, modify\n"
"and use the current configuration as an alternate to whatever\n"
"configuration options you have selected at that time.\n"
"\n"
"Leave empty to abort.\n",
search_help[] =
"Search for symbols (configuration variable names CONFIG_*) and display\n"
"their relations.  Regular expressions are supported.\n"
"Example:  Search for \"^FOO\".\n"
"Result:\n"
"-----------------------------------------------------------------\n"
"Symbol: FOO [ = m]\n"
"Prompt: Foo bus is used to drive the bar HW\n"
"Defined at drivers/pci/Kconfig:47\n"
"Depends on: X86_LOCAL_APIC && X86_IO_APIC || IA64\n"
"Location:\n"
"  -> Bus options (PCI, PCMCIA, EISA, ISA)\n"
"    -> PCI support (PCI [ = y])\n"
"      -> PCI access mode (<choice> [ = y])\n"
"Selects: LIBCRC32\n"
"Selected by: BAR\n"
"-----------------------------------------------------------------\n"
"o  The line 'Prompt:' shows the text displayed for this symbol in\n"
"   the menu hierarchy.\n"
"o  The 'Defined at' line tells at what file / line number the symbol is\n"
"   defined.\n"
"o  The 'Depends on:' line lists symbols that need to be defined for\n"
"   this symbol to be visible and selectable in the menu.\n"
"o  The 'Location:' lines tell, where in the menu structure this symbol\n"
"   is located.  A location followed by a [ = y] indicates that this is\n"
"   a selectable menu item, and the current value is displayed inside\n"
"   brackets.\n"
"o  The 'Selects:' line tells, what symbol will be automatically selected\n"
"   if this symbol is selected (y or m).\n"
"o  The 'Selected by' line tells what symbol has selected this symbol.\n"
"\n"
"Only relevant lines are shown.\n"
"\n\n"
"Search examples:\n"
"USB  => find all symbols containing USB\n"
"^USB => find all symbols starting with USB\न"
"USB$ => find all symbols ending with USB\n"
"\n";

काष्ठा mitem अणु
	अक्षर str[256];
	अक्षर tag;
	व्योम *usrptr;
	पूर्णांक is_visible;
पूर्ण;

#घोषणा MAX_MENU_ITEMS 4096
अटल पूर्णांक show_all_items;
अटल पूर्णांक indent;
अटल काष्ठा menu *current_menu;
अटल पूर्णांक child_count;
अटल पूर्णांक single_menu_mode;
/* the winकरोw in which all inक्रमmation appears */
अटल WINDOW *मुख्य_winकरोw;
/* the largest size of the menu winकरोw */
अटल पूर्णांक mwin_max_lines;
अटल पूर्णांक mwin_max_cols;
/* the winकरोw in which we show option buttons */
अटल MENU *curses_menu;
अटल ITEM *curses_menu_items[MAX_MENU_ITEMS];
अटल काष्ठा mitem k_menu_items[MAX_MENU_ITEMS];
अटल अचिन्हित पूर्णांक items_num;
अटल पूर्णांक global_निकास;
/* the currently selected button */
अटल स्थिर अक्षर *current_inकाष्ठाions = menu_inकाष्ठाions;

अटल अक्षर *dialog_input_result;
अटल पूर्णांक dialog_input_result_len;

अटल व्योम conf(काष्ठा menu *menu);
अटल व्योम conf_choice(काष्ठा menu *menu);
अटल व्योम conf_string(काष्ठा menu *menu);
अटल व्योम conf_load(व्योम);
अटल व्योम conf_save(व्योम);
अटल व्योम show_help(काष्ठा menu *menu);
अटल पूर्णांक करो_निकास(व्योम);
अटल व्योम setup_winकरोws(व्योम);
अटल व्योम search_conf(व्योम);

प्रकार व्योम (*function_key_handler_t)(पूर्णांक *key, काष्ठा menu *menu);
अटल व्योम handle_f1(पूर्णांक *key, काष्ठा menu *current_item);
अटल व्योम handle_f2(पूर्णांक *key, काष्ठा menu *current_item);
अटल व्योम handle_f3(पूर्णांक *key, काष्ठा menu *current_item);
अटल व्योम handle_f4(पूर्णांक *key, काष्ठा menu *current_item);
अटल व्योम handle_f5(पूर्णांक *key, काष्ठा menu *current_item);
अटल व्योम handle_f6(पूर्णांक *key, काष्ठा menu *current_item);
अटल व्योम handle_f7(पूर्णांक *key, काष्ठा menu *current_item);
अटल व्योम handle_f8(पूर्णांक *key, काष्ठा menu *current_item);
अटल व्योम handle_f9(पूर्णांक *key, काष्ठा menu *current_item);

काष्ठा function_keys अणु
	स्थिर अक्षर *key_str;
	स्थिर अक्षर *func;
	function_key key;
	function_key_handler_t handler;
पूर्ण;

अटल स्थिर पूर्णांक function_keys_num = 9;
अटल काष्ठा function_keys function_keys[] = अणु
	अणु
		.key_str = "F1",
		.func = "Help",
		.key = F_HELP,
		.handler = handle_f1,
	पूर्ण,
	अणु
		.key_str = "F2",
		.func = "SymInfo",
		.key = F_SYMBOL,
		.handler = handle_f2,
	पूर्ण,
	अणु
		.key_str = "F3",
		.func = "Help 2",
		.key = F_INSTS,
		.handler = handle_f3,
	पूर्ण,
	अणु
		.key_str = "F4",
		.func = "ShowAll",
		.key = F_CONF,
		.handler = handle_f4,
	पूर्ण,
	अणु
		.key_str = "F5",
		.func = "Back",
		.key = F_BACK,
		.handler = handle_f5,
	पूर्ण,
	अणु
		.key_str = "F6",
		.func = "Save",
		.key = F_SAVE,
		.handler = handle_f6,
	पूर्ण,
	अणु
		.key_str = "F7",
		.func = "Load",
		.key = F_LOAD,
		.handler = handle_f7,
	पूर्ण,
	अणु
		.key_str = "F8",
		.func = "SymSearch",
		.key = F_SEARCH,
		.handler = handle_f8,
	पूर्ण,
	अणु
		.key_str = "F9",
		.func = "Exit",
		.key = F_EXIT,
		.handler = handle_f9,
	पूर्ण,
पूर्ण;

अटल व्योम prपूर्णांक_function_line(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक offset = 1;
	स्थिर पूर्णांक skip = 1;
	पूर्णांक lines = geपंचांगaxy(stdscr);

	क्रम (i = 0; i < function_keys_num; i++) अणु
		wattrset(मुख्य_winकरोw, attr_function_highlight);
		mvwprपूर्णांकw(मुख्य_winकरोw, lines-3, offset,
				"%s",
				function_keys[i].key_str);
		wattrset(मुख्य_winकरोw, attr_function_text);
		offset += म_माप(function_keys[i].key_str);
		mvwprपूर्णांकw(मुख्य_winकरोw, lines-3,
				offset, "%s",
				function_keys[i].func);
		offset += म_माप(function_keys[i].func) + skip;
	पूर्ण
	wattrset(मुख्य_winकरोw, attr_normal);
पूर्ण

/* help */
अटल व्योम handle_f1(पूर्णांक *key, काष्ठा menu *current_item)
अणु
	show_scroll_win(मुख्य_winकरोw,
			"Global help", nconf_global_help);
	वापस;
पूर्ण

/* symbole help */
अटल व्योम handle_f2(पूर्णांक *key, काष्ठा menu *current_item)
अणु
	show_help(current_item);
	वापस;
पूर्ण

/* inकाष्ठाions */
अटल व्योम handle_f3(पूर्णांक *key, काष्ठा menu *current_item)
अणु
	show_scroll_win(मुख्य_winकरोw,
			"Short help",
			current_inकाष्ठाions);
	वापस;
पूर्ण

/* config */
अटल व्योम handle_f4(पूर्णांक *key, काष्ठा menu *current_item)
अणु
	पूर्णांक res = btn_dialog(मुख्य_winकरोw,
			"Show all symbols?",
			2,
			"   <Show All>   ",
			"<Don't show all>");
	अगर (res == 0)
		show_all_items = 1;
	अन्यथा अगर (res == 1)
		show_all_items = 0;

	वापस;
पूर्ण

/* back */
अटल व्योम handle_f5(पूर्णांक *key, काष्ठा menu *current_item)
अणु
	*key = KEY_LEFT;
	वापस;
पूर्ण

/* save */
अटल व्योम handle_f6(पूर्णांक *key, काष्ठा menu *current_item)
अणु
	conf_save();
	वापस;
पूर्ण

/* load */
अटल व्योम handle_f7(पूर्णांक *key, काष्ठा menu *current_item)
अणु
	conf_load();
	वापस;
पूर्ण

/* search */
अटल व्योम handle_f8(पूर्णांक *key, काष्ठा menu *current_item)
अणु
	search_conf();
	वापस;
पूर्ण

/* निकास */
अटल व्योम handle_f9(पूर्णांक *key, काष्ठा menu *current_item)
अणु
	करो_निकास();
	वापस;
पूर्ण

/* वापस != 0 to indicate the key was handles */
अटल पूर्णांक process_special_keys(पूर्णांक *key, काष्ठा menu *menu)
अणु
	पूर्णांक i;

	अगर (*key == KEY_RESIZE) अणु
		setup_winकरोws();
		वापस 1;
	पूर्ण

	क्रम (i = 0; i < function_keys_num; i++) अणु
		अगर (*key == KEY_F(function_keys[i].key) ||
		    *key == '0' + function_keys[i].key)अणु
			function_keys[i].handler(key, menu);
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम clean_items(व्योम)
अणु
	पूर्णांक i;
	क्रम (i = 0; curses_menu_items[i]; i++)
		मुक्त_item(curses_menu_items[i]);
	bzero(curses_menu_items, माप(curses_menu_items));
	bzero(k_menu_items, माप(k_menu_items));
	items_num = 0;
पूर्ण

प्रकार क्रमागत अणुMATCH_TINKER_PATTERN_UP, MATCH_TINKER_PATTERN_DOWN,
	FIND_NEXT_MATCH_DOWN, FIND_NEXT_MATCH_UPपूर्ण match_f;

/* वापस the index of the matched item, or -1 अगर no such item exists */
अटल पूर्णांक get_mext_match(स्थिर अक्षर *match_str, match_f flag)
अणु
	पूर्णांक match_start, index;

	/* Do not search अगर the menu is empty (i.e. items_num == 0) */
	match_start = item_index(current_item(curses_menu));
	अगर (match_start == ERR)
		वापस -1;

	अगर (flag == FIND_NEXT_MATCH_DOWN)
		++match_start;
	अन्यथा अगर (flag == FIND_NEXT_MATCH_UP)
		--match_start;

	match_start = (match_start + items_num) % items_num;
	index = match_start;
	जबतक (true) अणु
		अक्षर *str = k_menu_items[index].str;
		अगर (strहालstr(str, match_str) != शून्य)
			वापस index;
		अगर (flag == FIND_NEXT_MATCH_UP ||
		    flag == MATCH_TINKER_PATTERN_UP)
			--index;
		अन्यथा
			++index;
		index = (index + items_num) % items_num;
		अगर (index == match_start)
			वापस -1;
	पूर्ण
पूर्ण

/* Make a new item. */
अटल व्योम item_make(काष्ठा menu *menu, अक्षर tag, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;

	अगर (items_num > MAX_MENU_ITEMS-1)
		वापस;

	bzero(&k_menu_items[items_num], माप(k_menu_items[0]));
	k_menu_items[items_num].tag = tag;
	k_menu_items[items_num].usrptr = menu;
	अगर (menu != शून्य)
		k_menu_items[items_num].is_visible =
			menu_is_visible(menu);
	अन्यथा
		k_menu_items[items_num].is_visible = 1;

	बहु_शुरू(ap, fmt);
	vsnम_लिखो(k_menu_items[items_num].str,
		  माप(k_menu_items[items_num].str),
		  fmt, ap);
	बहु_पूर्ण(ap);

	अगर (!k_menu_items[items_num].is_visible)
		स_नकल(k_menu_items[items_num].str, "XXX", 3);

	curses_menu_items[items_num] = new_item(
			k_menu_items[items_num].str,
			k_menu_items[items_num].str);
	set_item_userptr(curses_menu_items[items_num],
			&k_menu_items[items_num]);
	/*
	अगर (!k_menu_items[items_num].is_visible)
		item_opts_off(curses_menu_items[items_num], O_SELECTABLE);
	*/

	items_num++;
	curses_menu_items[items_num] = शून्य;
पूर्ण

/* very hackish. adds a string to the last item added */
अटल व्योम item_add_str(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;
	पूर्णांक index = items_num-1;
	अक्षर new_str[256];
	अक्षर पंचांगp_str[256];

	अगर (index < 0)
		वापस;

	बहु_शुरू(ap, fmt);
	vsnम_लिखो(new_str, माप(new_str), fmt, ap);
	बहु_पूर्ण(ap);
	snम_लिखो(पंचांगp_str, माप(पंचांगp_str), "%s%s",
			k_menu_items[index].str, new_str);
	म_नकलन(k_menu_items[index].str,
		पंचांगp_str,
		माप(k_menu_items[index].str));

	मुक्त_item(curses_menu_items[index]);
	curses_menu_items[index] = new_item(
			k_menu_items[index].str,
			k_menu_items[index].str);
	set_item_userptr(curses_menu_items[index],
			&k_menu_items[index]);
पूर्ण

/* get the tag of the currently selected item */
अटल अक्षर item_tag(व्योम)
अणु
	ITEM *cur;
	काष्ठा mitem *mcur;

	cur = current_item(curses_menu);
	अगर (cur == शून्य)
		वापस 0;
	mcur = (काष्ठा mitem *) item_userptr(cur);
	वापस mcur->tag;
पूर्ण

अटल पूर्णांक curses_item_index(व्योम)
अणु
	वापस  item_index(current_item(curses_menu));
पूर्ण

अटल व्योम *item_data(व्योम)
अणु
	ITEM *cur;
	काष्ठा mitem *mcur;

	cur = current_item(curses_menu);
	अगर (!cur)
		वापस शून्य;
	mcur = (काष्ठा mitem *) item_userptr(cur);
	वापस mcur->usrptr;

पूर्ण

अटल पूर्णांक item_is_tag(अक्षर tag)
अणु
	वापस item_tag() == tag;
पूर्ण

अटल अक्षर filename[PATH_MAX+1];
अटल अक्षर menu_backtitle[PATH_MAX+128];
अटल व्योम set_config_filename(स्थिर अक्षर *config_filename)
अणु
	snम_लिखो(menu_backtitle, माप(menu_backtitle), "%s - %s",
		 config_filename, rooपंचांगenu.prompt->text);

	snम_लिखो(filename, माप(filename), "%s", config_filename);
पूर्ण

/* वापस = 0 means we are successful.
 * -1 means go on करोing what you were करोing
 */
अटल पूर्णांक करो_निकास(व्योम)
अणु
	पूर्णांक res;
	अगर (!conf_get_changed()) अणु
		global_निकास = 1;
		वापस 0;
	पूर्ण
	res = btn_dialog(मुख्य_winकरोw,
			"Do you wish to save your new configuration?\n"
				"<ESC> to cancel and resume nconfig.",
			2,
			"   <save>   ",
			"<don't save>");
	अगर (res == KEY_EXIT) अणु
		global_निकास = 0;
		वापस -1;
	पूर्ण

	/* अगर we got here, the user really wants to निकास */
	चयन (res) अणु
	हाल 0:
		res = conf_ग_लिखो(filename);
		अगर (res)
			btn_dialog(
				मुख्य_winकरोw,
				"Error during writing of configuration.\n"
				  "Your configuration changes were NOT saved.",
				  1,
				  "<OK>");
		conf_ग_लिखो_स्वतःconf(0);
		अवरोध;
	शेष:
		btn_dialog(
			मुख्य_winकरोw,
			"Your configuration changes were NOT saved.",
			1,
			"<OK>");
		अवरोध;
	पूर्ण
	global_निकास = 1;
	वापस 0;
पूर्ण


अटल व्योम search_conf(व्योम)
अणु
	काष्ठा symbol **sym_arr;
	काष्ठा gstr res;
	काष्ठा gstr title;
	अक्षर *dialog_input;
	पूर्णांक dres;

	title = str_new();
	str_म_लिखो( &title, "Enter (sub)string or regexp to search for "
			      "(with or without \"%s\")", CONFIG_);

again:
	dres = dialog_inputbox(मुख्य_winकरोw,
			"Search Configuration Parameter",
			str_get(&title),
			"", &dialog_input_result, &dialog_input_result_len);
	चयन (dres) अणु
	हाल 0:
		अवरोध;
	हाल 1:
		show_scroll_win(मुख्य_winकरोw,
				"Search Configuration", search_help);
		जाओ again;
	शेष:
		str_मुक्त(&title);
		वापस;
	पूर्ण

	/* strip the prefix अगर necessary */
	dialog_input = dialog_input_result;
	अगर (strnहालcmp(dialog_input_result, CONFIG_, म_माप(CONFIG_)) == 0)
		dialog_input += म_माप(CONFIG_);

	sym_arr = sym_re_search(dialog_input);
	res = get_relations_str(sym_arr, शून्य);
	मुक्त(sym_arr);
	show_scroll_win(मुख्य_winकरोw,
			"Search Results", str_get(&res));
	str_मुक्त(&res);
	str_मुक्त(&title);
पूर्ण


अटल व्योम build_conf(काष्ठा menu *menu)
अणु
	काष्ठा symbol *sym;
	काष्ठा property *prop;
	काष्ठा menu *child;
	पूर्णांक type, पंचांगp, करोपूर्णांक = 2;
	tristate val;
	अक्षर ch;

	अगर (!menu || (!show_all_items && !menu_is_visible(menu)))
		वापस;

	sym = menu->sym;
	prop = menu->prompt;
	अगर (!sym) अणु
		अगर (prop && menu != current_menu) अणु
			स्थिर अक्षर *prompt = menu_get_prompt(menu);
			क्रमागत prop_type ptype;
			ptype = menu->prompt ? menu->prompt->type : P_UNKNOWN;
			चयन (ptype) अणु
			हाल P_MENU:
				child_count++;
				अगर (single_menu_mode) अणु
					item_make(menu, 'm',
						"%s%*c%s",
						menu->data ? "-->" : "++>",
						indent + 1, ' ', prompt);
				पूर्ण अन्यथा
					item_make(menu, 'm',
						  "   %*c%s  %s",
						  indent + 1, ' ', prompt,
						  menu_is_empty(menu) ? "----" : "--->");

				अगर (single_menu_mode && menu->data)
					जाओ conf_childs;
				वापस;
			हाल P_COMMENT:
				अगर (prompt) अणु
					child_count++;
					item_make(menu, ':',
						"   %*c*** %s ***",
						indent + 1, ' ',
						prompt);
				पूर्ण
				अवरोध;
			शेष:
				अगर (prompt) अणु
					child_count++;
					item_make(menu, ':', "---%*c%s",
						indent + 1, ' ',
						prompt);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा
			करोपूर्णांक = 0;
		जाओ conf_childs;
	पूर्ण

	type = sym_get_type(sym);
	अगर (sym_is_choice(sym)) अणु
		काष्ठा symbol *def_sym = sym_get_choice_value(sym);
		काष्ठा menu *def_menu = शून्य;

		child_count++;
		क्रम (child = menu->list; child; child = child->next) अणु
			अगर (menu_is_visible(child) && child->sym == def_sym)
				def_menu = child;
		पूर्ण

		val = sym_get_tristate_value(sym);
		अगर (sym_is_changeable(sym)) अणु
			चयन (type) अणु
			हाल S_BOOLEAN:
				item_make(menu, 't', "[%c]",
						val == no ? ' ' : '*');
				अवरोध;
			हाल S_TRISTATE:
				चयन (val) अणु
				हाल yes:
					ch = '*';
					अवरोध;
				हाल mod:
					ch = 'M';
					अवरोध;
				शेष:
					ch = ' ';
					अवरोध;
				पूर्ण
				item_make(menu, 't', "<%c>", ch);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			item_make(menu, def_menu ? 't' : ':', "   ");
		पूर्ण

		item_add_str("%*c%s", indent + 1,
				' ', menu_get_prompt(menu));
		अगर (val == yes) अणु
			अगर (def_menu) अणु
				item_add_str(" (%s)",
					menu_get_prompt(def_menu));
				item_add_str("  --->");
				अगर (def_menu->list) अणु
					indent += 2;
					build_conf(def_menu);
					indent -= 2;
				पूर्ण
			पूर्ण
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (menu == current_menu) अणु
			item_make(menu, ':',
				"---%*c%s", indent + 1,
				' ', menu_get_prompt(menu));
			जाओ conf_childs;
		पूर्ण
		child_count++;
		val = sym_get_tristate_value(sym);
		अगर (sym_is_choice_value(sym) && val == yes) अणु
			item_make(menu, ':', "   ");
		पूर्ण अन्यथा अणु
			चयन (type) अणु
			हाल S_BOOLEAN:
				अगर (sym_is_changeable(sym))
					item_make(menu, 't', "[%c]",
						val == no ? ' ' : '*');
				अन्यथा
					item_make(menu, 't', "-%c-",
						val == no ? ' ' : '*');
				अवरोध;
			हाल S_TRISTATE:
				चयन (val) अणु
				हाल yes:
					ch = '*';
					अवरोध;
				हाल mod:
					ch = 'M';
					अवरोध;
				शेष:
					ch = ' ';
					अवरोध;
				पूर्ण
				अगर (sym_is_changeable(sym)) अणु
					अगर (sym->rev_dep.tri == mod)
						item_make(menu,
							't', "{%c}", ch);
					अन्यथा
						item_make(menu,
							't', "<%c>", ch);
				पूर्ण अन्यथा
					item_make(menu, 't', "-%c-", ch);
				अवरोध;
			शेष:
				पंचांगp = 2 + म_माप(sym_get_string_value(sym));
				item_make(menu, 's', "    (%s)",
						sym_get_string_value(sym));
				पंचांगp = indent - पंचांगp + 4;
				अगर (पंचांगp < 0)
					पंचांगp = 0;
				item_add_str("%*c%s%s", पंचांगp, ' ',
						menu_get_prompt(menu),
						(sym_has_value(sym) ||
						 !sym_is_changeable(sym)) ? "" :
						" (NEW)");
				जाओ conf_childs;
			पूर्ण
		पूर्ण
		item_add_str("%*c%s%s", indent + 1, ' ',
				menu_get_prompt(menu),
				(sym_has_value(sym) || !sym_is_changeable(sym)) ?
				"" : " (NEW)");
		अगर (menu->prompt && menu->prompt->type == P_MENU) अणु
			item_add_str("  %s", menu_is_empty(menu) ? "----" : "--->");
			वापस;
		पूर्ण
	पूर्ण

conf_childs:
	indent += करोपूर्णांक;
	क्रम (child = menu->list; child; child = child->next)
		build_conf(child);
	indent -= करोपूर्णांक;
पूर्ण

अटल व्योम reset_menu(व्योम)
अणु
	unpost_menu(curses_menu);
	clean_items();
पूर्ण

/* adjust the menu to show this item.
 * prefer not to scroll the menu अगर possible*/
अटल व्योम center_item(पूर्णांक selected_index, पूर्णांक *last_top_row)
अणु
	पूर्णांक toprow;

	set_top_row(curses_menu, *last_top_row);
	toprow = top_row(curses_menu);
	अगर (selected_index < toprow ||
	    selected_index >= toprow+mwin_max_lines) अणु
		toprow = max(selected_index-mwin_max_lines/2, 0);
		अगर (toprow >= item_count(curses_menu)-mwin_max_lines)
			toprow = item_count(curses_menu)-mwin_max_lines;
		set_top_row(curses_menu, toprow);
	पूर्ण
	set_current_item(curses_menu,
			curses_menu_items[selected_index]);
	*last_top_row = toprow;
	post_menu(curses_menu);
	refresh_all_winकरोws(मुख्य_winकरोw);
पूर्ण

/* this function assumes reset_menu has been called beक्रमe */
अटल व्योम show_menu(स्थिर अक्षर *prompt, स्थिर अक्षर *inकाष्ठाions,
		पूर्णांक selected_index, पूर्णांक *last_top_row)
अणु
	पूर्णांक maxx, maxy;
	WINDOW *menu_winकरोw;

	current_inकाष्ठाions = inकाष्ठाions;

	clear();
	prपूर्णांक_in_middle(stdscr, 1, geपंचांगaxx(stdscr),
			menu_backtitle,
			attr_मुख्य_heading);

	wattrset(मुख्य_winकरोw, attr_मुख्य_menu_box);
	box(मुख्य_winकरोw, 0, 0);
	wattrset(मुख्य_winकरोw, attr_मुख्य_menu_heading);
	mvwprपूर्णांकw(मुख्य_winकरोw, 0, 3, " %s ", prompt);
	wattrset(मुख्य_winकरोw, attr_normal);

	set_menu_items(curses_menu, curses_menu_items);

	/* position the menu at the middle of the screen */
	scale_menu(curses_menu, &maxy, &maxx);
	maxx = min(maxx, mwin_max_cols-2);
	maxy = mwin_max_lines;
	menu_winकरोw = derwin(मुख्य_winकरोw,
			maxy,
			maxx,
			2,
			(mwin_max_cols-maxx)/2);
	keypad(menu_winकरोw, TRUE);
	set_menu_win(curses_menu, menu_winकरोw);
	set_menu_sub(curses_menu, menu_winकरोw);

	/* must reनिश्चित this after changing items, otherwise वापसs to a
	 * शेष of 16
	 */
	set_menu_क्रमmat(curses_menu, maxy, 1);
	center_item(selected_index, last_top_row);
	set_menu_क्रमmat(curses_menu, maxy, 1);

	prपूर्णांक_function_line();

	/* Post the menu */
	post_menu(curses_menu);
	refresh_all_winकरोws(मुख्य_winकरोw);
पूर्ण

अटल व्योम adj_match_dir(match_f *match_direction)
अणु
	अगर (*match_direction == FIND_NEXT_MATCH_DOWN)
		*match_direction =
			MATCH_TINKER_PATTERN_DOWN;
	अन्यथा अगर (*match_direction == FIND_NEXT_MATCH_UP)
		*match_direction =
			MATCH_TINKER_PATTERN_UP;
	/* अन्यथा, करो no change.. */
पूर्ण

काष्ठा match_state
अणु
	पूर्णांक in_search;
	match_f match_direction;
	अक्षर pattern[256];
पूर्ण;

/* Return 0 means I have handled the key. In such a हाल, ans should hold the
 * item to center, or -1 otherwise.
 * Else वापस -1 .
 */
अटल पूर्णांक करो_match(पूर्णांक key, काष्ठा match_state *state, पूर्णांक *ans)
अणु
	अक्षर c = (अक्षर) key;
	पूर्णांक terminate_search = 0;
	*ans = -1;
	अगर (key == '/' || (state->in_search && key == 27)) अणु
		move(0, 0);
		refresh();
		clrtoeol();
		state->in_search = 1-state->in_search;
		bzero(state->pattern, माप(state->pattern));
		state->match_direction = MATCH_TINKER_PATTERN_DOWN;
		वापस 0;
	पूर्ण अन्यथा अगर (!state->in_search)
		वापस 1;

	अगर (है_अक्षर_अंक(c) || है_चित्र(c) || c == ' ') अणु
		state->pattern[म_माप(state->pattern)] = c;
		state->pattern[म_माप(state->pattern)] = '\0';
		adj_match_dir(&state->match_direction);
		*ans = get_mext_match(state->pattern,
				state->match_direction);
	पूर्ण अन्यथा अगर (key == KEY_DOWN) अणु
		state->match_direction = FIND_NEXT_MATCH_DOWN;
		*ans = get_mext_match(state->pattern,
				state->match_direction);
	पूर्ण अन्यथा अगर (key == KEY_UP) अणु
		state->match_direction = FIND_NEXT_MATCH_UP;
		*ans = get_mext_match(state->pattern,
				state->match_direction);
	पूर्ण अन्यथा अगर (key == KEY_BACKSPACE || key == 8 || key == 127) अणु
		state->pattern[म_माप(state->pattern)-1] = '\0';
		adj_match_dir(&state->match_direction);
	पूर्ण अन्यथा
		terminate_search = 1;

	अगर (terminate_search) अणु
		state->in_search = 0;
		bzero(state->pattern, माप(state->pattern));
		move(0, 0);
		refresh();
		clrtoeol();
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम conf(काष्ठा menu *menu)
अणु
	काष्ठा menu *submenu = शून्य;
	काष्ठा symbol *sym;
	पूर्णांक res;
	पूर्णांक current_index = 0;
	पूर्णांक last_top_row = 0;
	काष्ठा match_state match_state = अणु
		.in_search = 0,
		.match_direction = MATCH_TINKER_PATTERN_DOWN,
		.pattern = "",
	पूर्ण;

	जबतक (!global_निकास) अणु
		reset_menu();
		current_menu = menu;
		build_conf(menu);
		अगर (!child_count)
			अवरोध;

		show_menu(menu_get_prompt(menu), menu_inकाष्ठाions,
			  current_index, &last_top_row);
		keypad((menu_win(curses_menu)), TRUE);
		जबतक (!global_निकास) अणु
			अगर (match_state.in_search) अणु
				mvprपूर्णांकw(0, 0,
					"searching: %s", match_state.pattern);
				clrtoeol();
			पूर्ण
			refresh_all_winकरोws(मुख्य_winकरोw);
			res = wअ_लोh(menu_win(curses_menu));
			अगर (!res)
				अवरोध;
			अगर (करो_match(res, &match_state, &current_index) == 0) अणु
				अगर (current_index != -1)
					center_item(current_index,
						    &last_top_row);
				जारी;
			पूर्ण
			अगर (process_special_keys(&res,
						(काष्ठा menu *) item_data()))
				अवरोध;
			चयन (res) अणु
			हाल KEY_DOWN:
				menu_driver(curses_menu, REQ_DOWN_ITEM);
				अवरोध;
			हाल KEY_UP:
				menu_driver(curses_menu, REQ_UP_ITEM);
				अवरोध;
			हाल KEY_NPAGE:
				menu_driver(curses_menu, REQ_SCR_DPAGE);
				अवरोध;
			हाल KEY_PPAGE:
				menu_driver(curses_menu, REQ_SCR_UPAGE);
				अवरोध;
			हाल KEY_HOME:
				menu_driver(curses_menu, REQ_FIRST_ITEM);
				अवरोध;
			हाल KEY_END:
				menu_driver(curses_menu, REQ_LAST_ITEM);
				अवरोध;
			हाल 'h':
			हाल '?':
				show_help((काष्ठा menu *) item_data());
				अवरोध;
			पूर्ण
			अगर (res == 10 || res == 27 ||
				res == 32 || res == 'n' || res == 'y' ||
				res == KEY_LEFT || res == KEY_RIGHT ||
				res == 'm')
				अवरोध;
			refresh_all_winकरोws(मुख्य_winकरोw);
		पूर्ण

		refresh_all_winकरोws(मुख्य_winकरोw);
		/* अगर ESC or left*/
		अगर (res == 27 || (menu != &rooपंचांगenu && res == KEY_LEFT))
			अवरोध;

		/* remember location in the menu */
		last_top_row = top_row(curses_menu);
		current_index = curses_item_index();

		अगर (!item_tag())
			जारी;

		submenu = (काष्ठा menu *) item_data();
		अगर (!submenu || !menu_is_visible(submenu))
			जारी;
		sym = submenu->sym;

		चयन (res) अणु
		हाल ' ':
			अगर (item_is_tag('t'))
				sym_toggle_tristate_value(sym);
			अन्यथा अगर (item_is_tag('m'))
				conf(submenu);
			अवरोध;
		हाल KEY_RIGHT:
		हाल 10: /* ENTER WAS PRESSED */
			चयन (item_tag()) अणु
			हाल 'm':
				अगर (single_menu_mode)
					submenu->data =
						(व्योम *) (दीर्घ) !submenu->data;
				अन्यथा
					conf(submenu);
				अवरोध;
			हाल 't':
				अगर (sym_is_choice(sym) &&
				    sym_get_tristate_value(sym) == yes)
					conf_choice(submenu);
				अन्यथा अगर (submenu->prompt &&
					 submenu->prompt->type == P_MENU)
					conf(submenu);
				अन्यथा अगर (res == 10)
					sym_toggle_tristate_value(sym);
				अवरोध;
			हाल 's':
				conf_string(submenu);
				अवरोध;
			पूर्ण
			अवरोध;
		हाल 'y':
			अगर (item_is_tag('t')) अणु
				अगर (sym_set_tristate_value(sym, yes))
					अवरोध;
				अगर (sym_set_tristate_value(sym, mod))
					btn_dialog(मुख्य_winकरोw, seपंचांगod_text, 0);
			पूर्ण
			अवरोध;
		हाल 'n':
			अगर (item_is_tag('t'))
				sym_set_tristate_value(sym, no);
			अवरोध;
		हाल 'm':
			अगर (item_is_tag('t'))
				sym_set_tristate_value(sym, mod);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम conf_message_callback(स्थिर अक्षर *s)
अणु
	btn_dialog(मुख्य_winकरोw, s, 1, "<OK>");
पूर्ण

अटल व्योम show_help(काष्ठा menu *menu)
अणु
	काष्ठा gstr help;

	अगर (!menu)
		वापस;

	help = str_new();
	menu_get_ext_help(menu, &help);
	show_scroll_win(मुख्य_winकरोw, menu_get_prompt(menu), str_get(&help));
	str_मुक्त(&help);
पूर्ण

अटल व्योम conf_choice(काष्ठा menu *menu)
अणु
	स्थिर अक्षर *prompt = menu_get_prompt(menu);
	काष्ठा menu *child = शून्य;
	काष्ठा symbol *active;
	पूर्णांक selected_index = 0;
	पूर्णांक last_top_row = 0;
	पूर्णांक res, i = 0;
	काष्ठा match_state match_state = अणु
		.in_search = 0,
		.match_direction = MATCH_TINKER_PATTERN_DOWN,
		.pattern = "",
	पूर्ण;

	active = sym_get_choice_value(menu->sym);
	/* this is mostly duplicated from the conf() function. */
	जबतक (!global_निकास) अणु
		reset_menu();

		क्रम (i = 0, child = menu->list; child; child = child->next) अणु
			अगर (!show_all_items && !menu_is_visible(child))
				जारी;

			अगर (child->sym == sym_get_choice_value(menu->sym))
				item_make(child, ':', "<X> %s",
						menu_get_prompt(child));
			अन्यथा अगर (child->sym)
				item_make(child, ':', "    %s",
						menu_get_prompt(child));
			अन्यथा
				item_make(child, ':', "*** %s ***",
						menu_get_prompt(child));

			अगर (child->sym == active)अणु
				last_top_row = top_row(curses_menu);
				selected_index = i;
			पूर्ण
			i++;
		पूर्ण
		show_menu(prompt ? prompt : "Choice Menu",
				radiolist_inकाष्ठाions,
				selected_index,
				&last_top_row);
		जबतक (!global_निकास) अणु
			अगर (match_state.in_search) अणु
				mvprपूर्णांकw(0, 0, "searching: %s",
					 match_state.pattern);
				clrtoeol();
			पूर्ण
			refresh_all_winकरोws(मुख्य_winकरोw);
			res = wअ_लोh(menu_win(curses_menu));
			अगर (!res)
				अवरोध;
			अगर (करो_match(res, &match_state, &selected_index) == 0) अणु
				अगर (selected_index != -1)
					center_item(selected_index,
						    &last_top_row);
				जारी;
			पूर्ण
			अगर (process_special_keys(
						&res,
						(काष्ठा menu *) item_data()))
				अवरोध;
			चयन (res) अणु
			हाल KEY_DOWN:
				menu_driver(curses_menu, REQ_DOWN_ITEM);
				अवरोध;
			हाल KEY_UP:
				menu_driver(curses_menu, REQ_UP_ITEM);
				अवरोध;
			हाल KEY_NPAGE:
				menu_driver(curses_menu, REQ_SCR_DPAGE);
				अवरोध;
			हाल KEY_PPAGE:
				menu_driver(curses_menu, REQ_SCR_UPAGE);
				अवरोध;
			हाल KEY_HOME:
				menu_driver(curses_menu, REQ_FIRST_ITEM);
				अवरोध;
			हाल KEY_END:
				menu_driver(curses_menu, REQ_LAST_ITEM);
				अवरोध;
			हाल 'h':
			हाल '?':
				show_help((काष्ठा menu *) item_data());
				अवरोध;
			पूर्ण
			अगर (res == 10 || res == 27 || res == ' ' ||
					res == KEY_LEFT)अणु
				अवरोध;
			पूर्ण
			refresh_all_winकरोws(मुख्य_winकरोw);
		पूर्ण
		/* अगर ESC or left */
		अगर (res == 27 || res == KEY_LEFT)
			अवरोध;

		child = item_data();
		अगर (!child || !menu_is_visible(child) || !child->sym)
			जारी;
		चयन (res) अणु
		हाल ' ':
		हाल  10:
		हाल KEY_RIGHT:
			sym_set_tristate_value(child->sym, yes);
			वापस;
		हाल 'h':
		हाल '?':
			show_help(child);
			active = child->sym;
			अवरोध;
		हाल KEY_EXIT:
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम conf_string(काष्ठा menu *menu)
अणु
	स्थिर अक्षर *prompt = menu_get_prompt(menu);

	जबतक (1) अणु
		पूर्णांक res;
		स्थिर अक्षर *heading;

		चयन (sym_get_type(menu->sym)) अणु
		हाल S_INT:
			heading = inputbox_inकाष्ठाions_पूर्णांक;
			अवरोध;
		हाल S_HEX:
			heading = inputbox_inकाष्ठाions_hex;
			अवरोध;
		हाल S_STRING:
			heading = inputbox_inकाष्ठाions_string;
			अवरोध;
		शेष:
			heading = "Internal nconf error!";
		पूर्ण
		res = dialog_inputbox(मुख्य_winकरोw,
				prompt ? prompt : "Main Menu",
				heading,
				sym_get_string_value(menu->sym),
				&dialog_input_result,
				&dialog_input_result_len);
		चयन (res) अणु
		हाल 0:
			अगर (sym_set_string_value(menu->sym,
						dialog_input_result))
				वापस;
			btn_dialog(मुख्य_winकरोw,
				"You have made an invalid entry.", 0);
			अवरोध;
		हाल 1:
			show_help(menu);
			अवरोध;
		हाल KEY_EXIT:
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम conf_load(व्योम)
अणु
	जबतक (1) अणु
		पूर्णांक res;
		res = dialog_inputbox(मुख्य_winकरोw,
				शून्य, load_config_text,
				filename,
				&dialog_input_result,
				&dialog_input_result_len);
		चयन (res) अणु
		हाल 0:
			अगर (!dialog_input_result[0])
				वापस;
			अगर (!conf_पढ़ो(dialog_input_result)) अणु
				set_config_filename(dialog_input_result);
				conf_set_changed(true);
				वापस;
			पूर्ण
			btn_dialog(मुख्य_winकरोw, "File does not exist!", 0);
			अवरोध;
		हाल 1:
			show_scroll_win(मुख्य_winकरोw,
					"Load Alternate Configuration",
					load_config_help);
			अवरोध;
		हाल KEY_EXIT:
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम conf_save(व्योम)
अणु
	जबतक (1) अणु
		पूर्णांक res;
		res = dialog_inputbox(मुख्य_winकरोw,
				शून्य, save_config_text,
				filename,
				&dialog_input_result,
				&dialog_input_result_len);
		चयन (res) अणु
		हाल 0:
			अगर (!dialog_input_result[0])
				वापस;
			res = conf_ग_लिखो(dialog_input_result);
			अगर (!res) अणु
				set_config_filename(dialog_input_result);
				वापस;
			पूर्ण
			btn_dialog(मुख्य_winकरोw, "Can't create file!",
				1, "<OK>");
			अवरोध;
		हाल 1:
			show_scroll_win(मुख्य_winकरोw,
				"Save Alternate Configuration",
				save_config_help);
			अवरोध;
		हाल KEY_EXIT:
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम setup_winकरोws(व्योम)
अणु
	पूर्णांक lines, columns;

	geपंचांगaxyx(stdscr, lines, columns);

	अगर (मुख्य_winकरोw != शून्य)
		delwin(मुख्य_winकरोw);

	/* set up the menu and menu winकरोw */
	मुख्य_winकरोw = newwin(lines-2, columns-2, 2, 1);
	keypad(मुख्य_winकरोw, TRUE);
	mwin_max_lines = lines-7;
	mwin_max_cols = columns-6;

	/* panels order is from bottom to top */
	new_panel(मुख्य_winकरोw);
पूर्ण

पूर्णांक मुख्य(पूर्णांक ac, अक्षर **av)
अणु
	पूर्णांक lines, columns;
	अक्षर *mode;

	अगर (ac > 1 && म_भेद(av[1], "-s") == 0) अणु
		/* Silence conf_पढ़ो() until the real callback is set up */
		conf_set_message_callback(शून्य);
		av++;
	पूर्ण
	conf_parse(av[1]);
	conf_पढ़ो(शून्य);

	mode = दो_पर्या("NCONFIG_MODE");
	अगर (mode) अणु
		अगर (!strहालcmp(mode, "single_menu"))
			single_menu_mode = 1;
	पूर्ण

	/* Initialize curses */
	initscr();
	/* set color theme */
	set_colors();

	cअवरोध();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);

	geपंचांगaxyx(stdscr, lines, columns);
	अगर (columns < 75 || lines < 20) अणु
		endwin();
		म_लिखो("Your terminal should have at "
			"least 20 lines and 75 columns\n");
		वापस 1;
	पूर्ण

	noसमयout(stdscr, FALSE);
#अगर NCURSES_REENTRANT
	set_escdelay(1);
#अन्यथा
	ESCDELAY = 1;
#पूर्ण_अगर

	/* set btns menu */
	curses_menu = new_menu(curses_menu_items);
	menu_opts_off(curses_menu, O_SHOWDESC);
	menu_opts_on(curses_menu, O_SHOWMATCH);
	menu_opts_on(curses_menu, O_ONEVALUE);
	menu_opts_on(curses_menu, O_NONCYCLIC);
	menu_opts_on(curses_menu, O_IGNORECASE);
	set_menu_mark(curses_menu, " ");
	set_menu_क्रमe(curses_menu, attr_मुख्य_menu_क्रमe);
	set_menu_back(curses_menu, attr_मुख्य_menu_back);
	set_menu_grey(curses_menu, attr_मुख्य_menu_grey);

	set_config_filename(conf_get_configname());
	setup_winकरोws();

	/* check क्रम KEY_FUNC(1) */
	अगर (has_key(KEY_F(1)) == FALSE) अणु
		show_scroll_win(मुख्य_winकरोw,
				"Instructions",
				menu_no_f_inकाष्ठाions);
	पूर्ण

	conf_set_message_callback(conf_message_callback);
	/* करो the work */
	जबतक (!global_निकास) अणु
		conf(&rooपंचांगenu);
		अगर (!global_निकास && करो_निकास() == 0)
			अवरोध;
	पूर्ण
	/* ok, we are करोne */
	unpost_menu(curses_menu);
	मुक्त_menu(curses_menu);
	delwin(मुख्य_winकरोw);
	clear();
	refresh();
	endwin();
	वापस 0;
पूर्ण
