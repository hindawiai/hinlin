<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2002 Roman Zippel <zippel@linux-m68k.org>
 *
 * Introduced single menu mode (show all sub-menus in one large tree).
 * 2002-11-06 Petr Baudis <pasky@ucw.cz>
 *
 * i18n, 2005, Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 */

#समावेश <प्रकार.स>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <सीमा.स>
#समावेश <मानकतर्क.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <strings.h>
#समावेश <संकेत.स>
#समावेश <unistd.h>

#समावेश "lkc.h"
#समावेश "lxdialog/dialog.h"

#घोषणा JUMP_NB			9

अटल स्थिर अक्षर mconf_पढ़ोme[] =
"Overview\n"
"--------\n"
"This interface lets you select features and parameters for the build.\n"
"Features can either be built-in, modularized, or ignored. Parameters\n"
"must be entered in as decimal or hexadecimal numbers or text.\n"
"\n"
"Menu items beginning with following braces represent features that\n"
"  [ ] can be built in or removed\n"
"  < > can be built in, modularized or removed\n"
"  { } can be built in or modularized (selected by other feature)\n"
"  - - are selected by other feature,\n"
"while *, M or whitespace inside braces means to build in, build as\n"
"a module or to exclude the feature respectively.\n"
"\n"
"To change any of these features, highlight it with the cursor\n"
"keys and press <Y> to build it in, <M> to make it a module or\n"
"<N> to remove it.  You may also press the <Space Bar> to cycle\n"
"through the available options (i.e. Y->N->M->Y).\n"
"\n"
"Some additional keyboard hints:\n"
"\n"
"Menus\n"
"----------\n"
"o  Use the Up/Down arrow keys (cursor keys) to highlight the item you\n"
"   wish to change or the submenu you wish to select and press <Enter>.\n"
"   Submenus are designated by \"--->\", empty ones by \"----\".\n"
"\n"
"   Shortcut: Press the option's highlighted letter (hotkey).\n"
"             Pressing a hotkey more than once will sequence\n"
"             through all visible items which use that hotkey.\n"
"\n"
"   You may also use the <PAGE UP> and <PAGE DOWN> keys to scroll\n"
"   unseen options into view.\n"
"\n"
"o  To exit a menu use the cursor keys to highlight the <Exit> button\n"
"   and press <ENTER>.\n"
"\n"
"   Shortcut: Press <ESC><ESC> or <E> or <X> if there is no hotkey\n"
"             using those letters.  You may press a single <ESC>, but\n"
"             there is a delayed response which you may find annoying.\n"
"\n"
"   Also, the <TAB> and cursor keys will cycle between <Select>,\n"
"   <Exit>, <Help>, <Save>, and <Load>.\n"
"\n"
"o  To get help with an item, use the cursor keys to highlight <Help>\n"
"   and press <ENTER>.\n"
"\n"
"   Shortcut: Press <H> or <?>.\n"
"\n"
"o  To toggle the display of hidden options, press <Z>.\n"
"\n"
"\n"
"Radiolists  (Choice lists)\n"
"-----------\n"
"o  Use the cursor keys to select the option you wish to set and press\n"
"   <S> or the <SPACE BAR>.\n"
"\n"
"   Shortcut: Press the first letter of the option you wish to set then\n"
"             press <S> or <SPACE BAR>.\n"
"\n"
"o  To see available help for the item, use the cursor keys to highlight\n"
"   <Help> and Press <ENTER>.\n"
"\n"
"   Shortcut: Press <H> or <?>.\n"
"\n"
"   Also, the <TAB> and cursor keys will cycle between <Select> and\n"
"   <Help>\n"
"\n"
"\n"
"Data Entry\n"
"-----------\n"
"o  Enter the requested information and press <ENTER>\n"
"   If you are entering hexadecimal values, it is not necessary to\n"
"   add the '0x' prefix to the entry.\n"
"\n"
"o  For help, use the <TAB> or cursor keys to highlight the help option\n"
"   and press <ENTER>.  You can try <TAB><H> as well.\n"
"\n"
"\n"
"Text Box    (Help Window)\n"
"--------\n"
"o  Use the cursor keys to scroll up/down/left/right.  The VI editor\n"
"   keys h,j,k,l function here as do <u>, <d>, <SPACE BAR> and <B> for\n"
"   those who are familiar with less and lynx.\n"
"\n"
"o  Press <E>, <X>, <q>, <Enter> or <Esc><Esc> to exit.\n"
"\n"
"\n"
"Alternate Configuration Files\n"
"-----------------------------\n"
"Menuconfig supports the use of alternate configuration files for\n"
"those who, for various reasons, find it necessary to switch\n"
"between different configurations.\n"
"\n"
"The <Save> button will let you save the current configuration to\n"
"a file of your choosing.  Use the <Load> button to load a previously\n"
"saved alternate configuration.\n"
"\n"
"Even if you don't use alternate configuration files, but you find\n"
"during a Menuconfig session that you have completely messed up your\n"
"settings, you may use the <Load> button to restore your previously\n"
"saved settings from \".config\" without restarting Menuconfig.\n"
"\n"
"Other information\n"
"-----------------\n"
"If you use Menuconfig in an XTERM window, make sure you have your\n"
"$TERM variable set to point to an xterm definition which supports\n"
"color.  Otherwise, Menuconfig will look rather bad.  Menuconfig will\n"
"not display correctly in an RXVT window because rxvt displays only one\n"
"intensity of color, bright.\n"
"\n"
"Menuconfig will display larger menus on screens or xterms which are\n"
"set to display more than the standard 25 row by 80 column geometry.\n"
"In order for this to work, the \"stty size\" command must be able to\n"
"display the screen's current row and column geometry.  I STRONGLY\n"
"RECOMMEND that you make sure you do NOT have the shell variables\n"
"LINES and COLUMNS exported into your environment.  Some distributions\n"
"export those variables via /etc/profile.  Some ncurses programs can\n"
"become confused when those variables (LINES & COLUMNS) don't reflect\n"
"the true screen size.\n"
"\n"
"Optional personality available\n"
"------------------------------\n"
"If you prefer to have all of the options listed in a single menu,\n"
"rather than the default multimenu hierarchy, run the menuconfig with\n"
"MENUCONFIG_MODE environment variable set to single_menu. Example:\n"
"\n"
"make MENUCONFIG_MODE=single_menu menuconfig\n"
"\n"
"<Enter> will then unroll the appropriate category, or enfold it if it\n"
"is already unrolled.\n"
"\n"
"Note that this mode can eventually be a little more CPU expensive\n"
"(especially with a larger number of unrolled categories) than the\n"
"default mode.\n"
"\n"
"Different color themes available\n"
"--------------------------------\n"
"It is possible to select different color themes using the variable\n"
"MENUCONFIG_COLOR. To select a theme use:\n"
"\n"
"make MENUCONFIG_COLOR=<theme> menuconfig\n"
"\n"
"Available themes are\n"
" mono       => selects colors suitable for monochrome displays\n"
" blackbg    => selects a color scheme with black background\n"
" classic    => theme with blue background. The classic look\n"
" bluetitle  => an LCD friendly version of classic. (default)\n"
"\n",
menu_inकाष्ठाions[] =
	"Arrow keys navigate the menu.  "
	"<Enter> selects submenus ---> (or empty submenus ----).  "
	"Highlighted letters are hotkeys.  "
	"Pressing <Y> includes, <N> excludes, <M> modularizes features.  "
	"Press <Esc><Esc> to exit, <?> for Help, </> for Search.  "
	"Legend: [*] built-in  [ ] excluded  <M> module  < > module capable",
radiolist_inकाष्ठाions[] =
	"Use the arrow keys to navigate this window or "
	"press the hotkey of the item you wish to select "
	"followed by the <SPACE BAR>. "
	"Press <?> for additional information about this option.",
inputbox_inकाष्ठाions_पूर्णांक[] =
	"Please enter a decimal value. "
	"Fractions will not be accepted.  "
	"Use the <TAB> key to move from the input field to the buttons below it.",
inputbox_inकाष्ठाions_hex[] =
	"Please enter a hexadecimal value. "
	"Use the <TAB> key to move from the input field to the buttons below it.",
inputbox_inकाष्ठाions_string[] =
	"Please enter a string value. "
	"Use the <TAB> key to move from the input field to the buttons below it.",
seपंचांगod_text[] =
	"This feature depends on another which has been configured as a module.\n"
	"As a result, this feature will be built as a module.",
load_config_text[] =
	"Enter the name of the configuration file you wish to load.  "
	"Accept the name shown to restore the configuration you "
	"last retrieved.  Leave blank to abort.",
load_config_help[] =
	"\n"
	"For various reasons, one may wish to keep several different\n"
	"configurations available on a single machine.\n"
	"\n"
	"If you have saved a previous configuration in a file other than the\n"
	"default one, entering its name here will allow you to modify that\n"
	"configuration.\n"
	"\n"
	"If you are uncertain, then you have probably never used alternate\n"
	"configuration files. You should therefore leave this blank to abort.\n",
save_config_text[] =
	"Enter a filename to which this configuration should be saved "
	"as an alternate.  Leave blank to abort.",
save_config_help[] =
	"\n"
	"For various reasons, one may wish to keep different configurations\n"
	"available on a single machine.\n"
	"\n"
	"Entering a file name here will allow you to later retrieve, modify\n"
	"and use the current configuration as an alternate to whatever\n"
	"configuration options you have selected at that time.\n"
	"\n"
	"If you are uncertain what all this means then you should probably\n"
	"leave this blank.\n",
search_help[] =
	"\n"
	"Search for symbols and display their relations.\n"
	"Regular expressions are allowed.\n"
	"Example: search for \"^FOO\"\n"
	"Result:\n"
	"-----------------------------------------------------------------\n"
	"Symbol: FOO [=m]\n"
	"Type  : tristate\n"
	"Prompt: Foo bus is used to drive the bar HW\n"
	"  Location:\n"
	"    -> Bus options (PCI, PCMCIA, EISA, ISA)\n"
	"      -> PCI support (PCI [=y])\n"
	"(1)     -> PCI access mode (<choice> [=y])\n"
	"  Defined at drivers/pci/Kconfig:47\n"
	"  Depends on: X86_LOCAL_APIC && X86_IO_APIC || IA64\n"
	"  Selects: LIBCRC32\n"
	"  Selected by: BAR [=n]\n"
	"-----------------------------------------------------------------\n"
	"o The line 'Type:' shows the type of the configuration option for\n"
	"  this symbol (bool, tristate, string, ...)\n"
	"o The line 'Prompt:' shows the text used in the menu structure for\n"
	"  this symbol\n"
	"o The 'Defined at' line tells at what file / line number the symbol\n"
	"  is defined\n"
	"o The 'Depends on:' line tells what symbols need to be defined for\n"
	"  this symbol to be visible in the menu (selectable)\n"
	"o The 'Location:' lines tells where in the menu structure this symbol\n"
	"  is located\n"
	"    A location followed by a [=y] indicates that this is a\n"
	"    selectable menu item - and the current value is displayed inside\n"
	"    brackets.\n"
	"    Press the key in the (#) prefix to jump directly to that\n"
	"    location. You will be returned to the current search results\n"
	"    after exiting this new menu.\n"
	"o The 'Selects:' line tells what symbols will be automatically\n"
	"  selected if this symbol is selected (y or m)\n"
	"o The 'Selected by' line tells what symbol has selected this symbol\n"
	"\n"
	"Only relevant lines are shown.\n"
	"\n\n"
	"Search examples:\n"
	"Examples: USB	=> find all symbols containing USB\n"
	"          ^USB => find all symbols starting with USB\न"
	"          USB$ => find all symbols ending with USB\n"
	"\n";

अटल पूर्णांक indent;
अटल काष्ठा menu *current_menu;
अटल पूर्णांक child_count;
अटल पूर्णांक single_menu_mode;
अटल पूर्णांक show_all_options;
अटल पूर्णांक save_and_निकास;
अटल पूर्णांक silent;

अटल व्योम conf(काष्ठा menu *menu, काष्ठा menu *active_menu);
अटल व्योम conf_choice(काष्ठा menu *menu);
अटल व्योम conf_string(काष्ठा menu *menu);
अटल व्योम conf_load(व्योम);
अटल व्योम conf_save(व्योम);
अटल पूर्णांक show_textbox_ext(स्थिर अक्षर *title, अक्षर *text, पूर्णांक r, पूर्णांक c,
			    पूर्णांक *keys, पूर्णांक *vscroll, पूर्णांक *hscroll,
			    update_text_fn update_text, व्योम *data);
अटल व्योम show_textbox(स्थिर अक्षर *title, स्थिर अक्षर *text, पूर्णांक r, पूर्णांक c);
अटल व्योम show_helptext(स्थिर अक्षर *title, स्थिर अक्षर *text);
अटल व्योम show_help(काष्ठा menu *menu);

अटल अक्षर filename[PATH_MAX+1];
अटल व्योम set_config_filename(स्थिर अक्षर *config_filename)
अणु
	अटल अक्षर menu_backtitle[PATH_MAX+128];

	snम_लिखो(menu_backtitle, माप(menu_backtitle), "%s - %s",
		 config_filename, rooपंचांगenu.prompt->text);
	set_dialog_backtitle(menu_backtitle);

	snम_लिखो(filename, माप(filename), "%s", config_filename);
पूर्ण

काष्ठा subtitle_part अणु
	काष्ठा list_head entries;
	स्थिर अक्षर *text;
पूर्ण;
अटल LIST_HEAD(trail);

अटल काष्ठा subtitle_list *subtitles;
अटल व्योम set_subtitle(व्योम)
अणु
	काष्ठा subtitle_part *sp;
	काष्ठा subtitle_list *pos, *पंचांगp;

	क्रम (pos = subtitles; pos != शून्य; pos = पंचांगp) अणु
		पंचांगp = pos->next;
		मुक्त(pos);
	पूर्ण

	subtitles = शून्य;
	list_क्रम_each_entry(sp, &trail, entries) अणु
		अगर (sp->text) अणु
			अगर (pos) अणु
				pos->next = xसुस्मृति(1, माप(*pos));
				pos = pos->next;
			पूर्ण अन्यथा अणु
				subtitles = pos = xसुस्मृति(1, माप(*pos));
			पूर्ण
			pos->text = sp->text;
		पूर्ण
	पूर्ण

	set_dialog_subtitles(subtitles);
पूर्ण

अटल व्योम reset_subtitle(व्योम)
अणु
	काष्ठा subtitle_list *pos, *पंचांगp;

	क्रम (pos = subtitles; pos != शून्य; pos = पंचांगp) अणु
		पंचांगp = pos->next;
		मुक्त(pos);
	पूर्ण
	subtitles = शून्य;
	set_dialog_subtitles(subtitles);
पूर्ण

काष्ठा search_data अणु
	काष्ठा list_head *head;
	काष्ठा menu **tarमाला_लो;
	पूर्णांक *keys;
पूर्ण;

अटल व्योम update_text(अक्षर *buf, माप_प्रकार start, माप_प्रकार end, व्योम *_data)
अणु
	काष्ठा search_data *data = _data;
	काष्ठा jump_key *pos;
	पूर्णांक k = 0;

	list_क्रम_each_entry(pos, data->head, entries) अणु
		अगर (pos->offset >= start && pos->offset < end) अणु
			अक्षर header[4];

			अगर (k < JUMP_NB) अणु
				पूर्णांक key = '0' + (pos->index % JUMP_NB) + 1;

				प्र_लिखो(header, "(%c)", key);
				data->keys[k] = key;
				data->tarमाला_लो[k] = pos->target;
				k++;
			पूर्ण अन्यथा अणु
				प्र_लिखो(header, "   ");
			पूर्ण

			स_नकल(buf + pos->offset, header, माप(header) - 1);
		पूर्ण
	पूर्ण
	data->keys[k] = 0;
पूर्ण

अटल व्योम search_conf(व्योम)
अणु
	काष्ठा symbol **sym_arr;
	काष्ठा gstr res;
	काष्ठा gstr title;
	अक्षर *dialog_input;
	पूर्णांक dres, vscroll = 0, hscroll = 0;
	bool again;
	काष्ठा gstr sttext;
	काष्ठा subtitle_part stpart;

	title = str_new();
	str_म_लिखो( &title, "Enter (sub)string or regexp to search for "
			      "(with or without \"%s\")", CONFIG_);

again:
	dialog_clear();
	dres = dialog_inputbox("Search Configuration Parameter",
			      str_get(&title),
			      10, 75, "");
	चयन (dres) अणु
	हाल 0:
		अवरोध;
	हाल 1:
		show_helptext("Search Configuration", search_help);
		जाओ again;
	शेष:
		str_मुक्त(&title);
		वापस;
	पूर्ण

	/* strip the prefix अगर necessary */
	dialog_input = dialog_input_result;
	अगर (strnहालcmp(dialog_input_result, CONFIG_, म_माप(CONFIG_)) == 0)
		dialog_input += म_माप(CONFIG_);

	sttext = str_new();
	str_म_लिखो(&sttext, "Search (%s)", dialog_input_result);
	stpart.text = str_get(&sttext);
	list_add_tail(&stpart.entries, &trail);

	sym_arr = sym_re_search(dialog_input);
	करो अणु
		LIST_HEAD(head);
		काष्ठा menu *tarमाला_लो[JUMP_NB];
		पूर्णांक keys[JUMP_NB + 1], i;
		काष्ठा search_data data = अणु
			.head = &head,
			.tarमाला_लो = tarमाला_लो,
			.keys = keys,
		पूर्ण;
		काष्ठा jump_key *pos, *पंचांगp;

		res = get_relations_str(sym_arr, &head);
		set_subtitle();
		dres = show_textbox_ext("Search Results", (अक्षर *)
					str_get(&res), 0, 0, keys, &vscroll,
					&hscroll, &update_text, (व्योम *)
					&data);
		again = false;
		क्रम (i = 0; i < JUMP_NB && keys[i]; i++)
			अगर (dres == keys[i]) अणु
				conf(tarमाला_लो[i]->parent, tarमाला_लो[i]);
				again = true;
			पूर्ण
		str_मुक्त(&res);
		list_क्रम_each_entry_safe(pos, पंचांगp, &head, entries)
			मुक्त(pos);
	पूर्ण जबतक (again);
	मुक्त(sym_arr);
	str_मुक्त(&title);
	list_del(trail.prev);
	str_मुक्त(&sttext);
पूर्ण

अटल व्योम build_conf(काष्ठा menu *menu)
अणु
	काष्ठा symbol *sym;
	काष्ठा property *prop;
	काष्ठा menu *child;
	पूर्णांक type, पंचांगp, करोपूर्णांक = 2;
	tristate val;
	अक्षर ch;
	bool visible;

	/*
	 * note: menu_is_visible() has side effect that it will
	 * recalc the value of the symbol.
	 */
	visible = menu_is_visible(menu);
	अगर (show_all_options && !menu_has_prompt(menu))
		वापस;
	अन्यथा अगर (!show_all_options && !visible)
		वापस;

	sym = menu->sym;
	prop = menu->prompt;
	अगर (!sym) अणु
		अगर (prop && menu != current_menu) अणु
			स्थिर अक्षर *prompt = menu_get_prompt(menu);
			चयन (prop->type) अणु
			हाल P_MENU:
				child_count++;
				अगर (single_menu_mode) अणु
					item_make("%s%*c%s",
						  menu->data ? "-->" : "++>",
						  indent + 1, ' ', prompt);
				पूर्ण अन्यथा
					item_make("   %*c%s  %s",
						  indent + 1, ' ', prompt,
						  menu_is_empty(menu) ? "----" : "--->");
				item_set_tag('m');
				item_set_data(menu);
				अगर (single_menu_mode && menu->data)
					जाओ conf_childs;
				वापस;
			हाल P_COMMENT:
				अगर (prompt) अणु
					child_count++;
					item_make("   %*c*** %s ***", indent + 1, ' ', prompt);
					item_set_tag(':');
					item_set_data(menu);
				पूर्ण
				अवरोध;
			शेष:
				अगर (prompt) अणु
					child_count++;
					item_make("---%*c%s", indent + 1, ' ', prompt);
					item_set_tag(':');
					item_set_data(menu);
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
				item_make("[%c]", val == no ? ' ' : '*');
				अवरोध;
			हाल S_TRISTATE:
				चयन (val) अणु
				हाल yes: ch = '*'; अवरोध;
				हाल mod: ch = 'M'; अवरोध;
				शेष:  ch = ' '; अवरोध;
				पूर्ण
				item_make("<%c>", ch);
				अवरोध;
			पूर्ण
			item_set_tag('t');
			item_set_data(menu);
		पूर्ण अन्यथा अणु
			item_make("   ");
			item_set_tag(def_menu ? 't' : ':');
			item_set_data(menu);
		पूर्ण

		item_add_str("%*c%s", indent + 1, ' ', menu_get_prompt(menu));
		अगर (val == yes) अणु
			अगर (def_menu) अणु
				item_add_str(" (%s)", menu_get_prompt(def_menu));
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
			item_make("---%*c%s", indent + 1, ' ', menu_get_prompt(menu));
			item_set_tag(':');
			item_set_data(menu);
			जाओ conf_childs;
		पूर्ण
		child_count++;
		val = sym_get_tristate_value(sym);
		अगर (sym_is_choice_value(sym) && val == yes) अणु
			item_make("   ");
			item_set_tag(':');
			item_set_data(menu);
		पूर्ण अन्यथा अणु
			चयन (type) अणु
			हाल S_BOOLEAN:
				अगर (sym_is_changeable(sym))
					item_make("[%c]", val == no ? ' ' : '*');
				अन्यथा
					item_make("-%c-", val == no ? ' ' : '*');
				item_set_tag('t');
				item_set_data(menu);
				अवरोध;
			हाल S_TRISTATE:
				चयन (val) अणु
				हाल yes: ch = '*'; अवरोध;
				हाल mod: ch = 'M'; अवरोध;
				शेष:  ch = ' '; अवरोध;
				पूर्ण
				अगर (sym_is_changeable(sym)) अणु
					अगर (sym->rev_dep.tri == mod)
						item_make("{%c}", ch);
					अन्यथा
						item_make("<%c>", ch);
				पूर्ण अन्यथा
					item_make("-%c-", ch);
				item_set_tag('t');
				item_set_data(menu);
				अवरोध;
			शेष:
				पंचांगp = 2 + म_माप(sym_get_string_value(sym)); /* () = 2 */
				item_make("(%s)", sym_get_string_value(sym));
				पंचांगp = indent - पंचांगp + 4;
				अगर (पंचांगp < 0)
					पंचांगp = 0;
				item_add_str("%*c%s%s", पंचांगp, ' ', menu_get_prompt(menu),
					     (sym_has_value(sym) || !sym_is_changeable(sym)) ?
					     "" : " (NEW)");
				item_set_tag('s');
				item_set_data(menu);
				जाओ conf_childs;
			पूर्ण
		पूर्ण
		item_add_str("%*c%s%s", indent + 1, ' ', menu_get_prompt(menu),
			  (sym_has_value(sym) || !sym_is_changeable(sym)) ?
			  "" : " (NEW)");
		अगर (menu->prompt->type == P_MENU) अणु
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

अटल व्योम conf(काष्ठा menu *menu, काष्ठा menu *active_menu)
अणु
	काष्ठा menu *submenu;
	स्थिर अक्षर *prompt = menu_get_prompt(menu);
	काष्ठा subtitle_part stpart;
	काष्ठा symbol *sym;
	पूर्णांक res;
	पूर्णांक s_scroll = 0;

	अगर (menu != &rooपंचांगenu)
		stpart.text = menu_get_prompt(menu);
	अन्यथा
		stpart.text = शून्य;
	list_add_tail(&stpart.entries, &trail);

	जबतक (1) अणु
		item_reset();
		current_menu = menu;
		build_conf(menu);
		अगर (!child_count)
			अवरोध;
		set_subtitle();
		dialog_clear();
		res = dialog_menu(prompt ? prompt : "Main Menu",
				  menu_inकाष्ठाions,
				  active_menu, &s_scroll);
		अगर (res == 1 || res == KEY_ESC || res == -ERRDISPLAYTOOSMALL)
			अवरोध;
		अगर (item_count() != 0) अणु
			अगर (!item_activate_selected())
				जारी;
			अगर (!item_tag())
				जारी;
		पूर्ण
		submenu = item_data();
		active_menu = item_data();
		अगर (submenu)
			sym = submenu->sym;
		अन्यथा
			sym = शून्य;

		चयन (res) अणु
		हाल 0:
			चयन (item_tag()) अणु
			हाल 'm':
				अगर (single_menu_mode)
					submenu->data = (व्योम *) (दीर्घ) !submenu->data;
				अन्यथा
					conf(submenu, शून्य);
				अवरोध;
			हाल 't':
				अगर (sym_is_choice(sym) && sym_get_tristate_value(sym) == yes)
					conf_choice(submenu);
				अन्यथा अगर (submenu->prompt->type == P_MENU)
					conf(submenu, शून्य);
				अवरोध;
			हाल 's':
				conf_string(submenu);
				अवरोध;
			पूर्ण
			अवरोध;
		हाल 2:
			अगर (sym)
				show_help(submenu);
			अन्यथा अणु
				reset_subtitle();
				show_helptext("README", mconf_पढ़ोme);
			पूर्ण
			अवरोध;
		हाल 3:
			reset_subtitle();
			conf_save();
			अवरोध;
		हाल 4:
			reset_subtitle();
			conf_load();
			अवरोध;
		हाल 5:
			अगर (item_is_tag('t')) अणु
				अगर (sym_set_tristate_value(sym, yes))
					अवरोध;
				अगर (sym_set_tristate_value(sym, mod))
					show_textbox(शून्य, seपंचांगod_text, 6, 74);
			पूर्ण
			अवरोध;
		हाल 6:
			अगर (item_is_tag('t'))
				sym_set_tristate_value(sym, no);
			अवरोध;
		हाल 7:
			अगर (item_is_tag('t'))
				sym_set_tristate_value(sym, mod);
			अवरोध;
		हाल 8:
			अगर (item_is_tag('t'))
				sym_toggle_tristate_value(sym);
			अन्यथा अगर (item_is_tag('m'))
				conf(submenu, शून्य);
			अवरोध;
		हाल 9:
			search_conf();
			अवरोध;
		हाल 10:
			show_all_options = !show_all_options;
			अवरोध;
		पूर्ण
	पूर्ण

	list_del(trail.prev);
पूर्ण

अटल पूर्णांक show_textbox_ext(स्थिर अक्षर *title, अक्षर *text, पूर्णांक r, पूर्णांक c, पूर्णांक
			    *keys, पूर्णांक *vscroll, पूर्णांक *hscroll, update_text_fn
			    update_text, व्योम *data)
अणु
	dialog_clear();
	वापस dialog_textbox(title, text, r, c, keys, vscroll, hscroll,
			      update_text, data);
पूर्ण

अटल व्योम show_textbox(स्थिर अक्षर *title, स्थिर अक्षर *text, पूर्णांक r, पूर्णांक c)
अणु
	show_textbox_ext(title, (अक्षर *) text, r, c, (पूर्णांक []) अणु0पूर्ण, शून्य, शून्य,
			 शून्य, शून्य);
पूर्ण

अटल व्योम show_helptext(स्थिर अक्षर *title, स्थिर अक्षर *text)
अणु
	show_textbox(title, text, 0, 0);
पूर्ण

अटल व्योम conf_message_callback(स्थिर अक्षर *s)
अणु
	अगर (save_and_निकास) अणु
		अगर (!silent)
			म_लिखो("%s", s);
	पूर्ण अन्यथा अणु
		show_textbox(शून्य, s, 6, 60);
	पूर्ण
पूर्ण

अटल व्योम show_help(काष्ठा menu *menu)
अणु
	काष्ठा gstr help = str_new();

	help.max_width = geपंचांगaxx(stdscr) - 10;
	menu_get_ext_help(menu, &help);

	show_helptext(menu_get_prompt(menu), str_get(&help));
	str_मुक्त(&help);
पूर्ण

अटल व्योम conf_choice(काष्ठा menu *menu)
अणु
	स्थिर अक्षर *prompt = menu_get_prompt(menu);
	काष्ठा menu *child;
	काष्ठा symbol *active;

	active = sym_get_choice_value(menu->sym);
	जबतक (1) अणु
		पूर्णांक res;
		पूर्णांक selected;
		item_reset();

		current_menu = menu;
		क्रम (child = menu->list; child; child = child->next) अणु
			अगर (!menu_is_visible(child))
				जारी;
			अगर (child->sym)
				item_make("%s", menu_get_prompt(child));
			अन्यथा अणु
				item_make("*** %s ***", menu_get_prompt(child));
				item_set_tag(':');
			पूर्ण
			item_set_data(child);
			अगर (child->sym == active)
				item_set_selected(1);
			अगर (child->sym == sym_get_choice_value(menu->sym))
				item_set_tag('X');
		पूर्ण
		dialog_clear();
		res = dialog_checklist(prompt ? prompt : "Main Menu",
					radiolist_inकाष्ठाions,
					MENUBOX_HEIGTH_MIN,
					MENUBOX_WIDTH_MIN,
					CHECKLIST_HEIGTH_MIN);
		selected = item_activate_selected();
		चयन (res) अणु
		हाल 0:
			अगर (selected) अणु
				child = item_data();
				अगर (!child->sym)
					अवरोध;

				sym_set_tristate_value(child->sym, yes);
			पूर्ण
			वापस;
		हाल 1:
			अगर (selected) अणु
				child = item_data();
				show_help(child);
				active = child->sym;
			पूर्ण अन्यथा
				show_help(menu);
			अवरोध;
		हाल KEY_ESC:
			वापस;
		हाल -ERRDISPLAYTOOSMALL:
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
			heading = "Internal mconf error!";
		पूर्ण
		dialog_clear();
		res = dialog_inputbox(prompt ? prompt : "Main Menu",
				      heading, 10, 75,
				      sym_get_string_value(menu->sym));
		चयन (res) अणु
		हाल 0:
			अगर (sym_set_string_value(menu->sym, dialog_input_result))
				वापस;
			show_textbox(शून्य, "You have made an invalid entry.", 5, 43);
			अवरोध;
		हाल 1:
			show_help(menu);
			अवरोध;
		हाल KEY_ESC:
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम conf_load(व्योम)
अणु

	जबतक (1) अणु
		पूर्णांक res;
		dialog_clear();
		res = dialog_inputbox(शून्य, load_config_text,
				      11, 55, filename);
		चयन(res) अणु
		हाल 0:
			अगर (!dialog_input_result[0])
				वापस;
			अगर (!conf_पढ़ो(dialog_input_result)) अणु
				set_config_filename(dialog_input_result);
				conf_set_changed(true);
				वापस;
			पूर्ण
			show_textbox(शून्य, "File does not exist!", 5, 38);
			अवरोध;
		हाल 1:
			show_helptext("Load Alternate Configuration", load_config_help);
			अवरोध;
		हाल KEY_ESC:
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम conf_save(व्योम)
अणु
	जबतक (1) अणु
		पूर्णांक res;
		dialog_clear();
		res = dialog_inputbox(शून्य, save_config_text,
				      11, 55, filename);
		चयन(res) अणु
		हाल 0:
			अगर (!dialog_input_result[0])
				वापस;
			अगर (!conf_ग_लिखो(dialog_input_result)) अणु
				set_config_filename(dialog_input_result);
				वापस;
			पूर्ण
			show_textbox(शून्य, "Can't create file!", 5, 60);
			अवरोध;
		हाल 1:
			show_helptext("Save Alternate Configuration", save_config_help);
			अवरोध;
		हाल KEY_ESC:
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक handle_निकास(व्योम)
अणु
	पूर्णांक res;

	save_and_निकास = 1;
	reset_subtitle();
	dialog_clear();
	अगर (conf_get_changed())
		res = dialog_yesno(शून्य,
				   "Do you wish to save your new configuration?\n"
				     "(Press <ESC><ESC> to continue kernel configuration.)",
				   6, 60);
	अन्यथा
		res = -1;

	end_dialog(saved_x, saved_y);

	चयन (res) अणु
	हाल 0:
		अगर (conf_ग_लिखो(filename)) अणु
			ख_लिखो(मानक_त्रुटि, "\n\n"
					  "Error while writing of the configuration.\n"
					  "Your configuration changes were NOT saved."
					  "\n\n");
			वापस 1;
		पूर्ण
		conf_ग_लिखो_स्वतःconf(0);
		/* fall through */
	हाल -1:
		अगर (!silent)
			म_लिखो("\n\n"
				 "*** End of the configuration.\n"
				 "*** Execute 'make' to start the build or try 'make help'."
				 "\n\n");
		res = 0;
		अवरोध;
	शेष:
		अगर (!silent)
			ख_लिखो(मानक_त्रुटि, "\n\n"
					  "Your configuration changes were NOT saved."
					  "\n\n");
		अगर (res != KEY_ESC)
			res = 0;
	पूर्ण

	वापस res;
पूर्ण

अटल व्योम sig_handler(पूर्णांक signo)
अणु
	निकास(handle_निकास());
पूर्ण

पूर्णांक मुख्य(पूर्णांक ac, अक्षर **av)
अणु
	अक्षर *mode;
	पूर्णांक res;

	संकेत(संक_विघ्न, sig_handler);

	अगर (ac > 1 && म_भेद(av[1], "-s") == 0) अणु
		silent = 1;
		/* Silence conf_पढ़ो() until the real callback is set up */
		conf_set_message_callback(शून्य);
		av++;
	पूर्ण
	conf_parse(av[1]);
	conf_पढ़ो(शून्य);

	mode = दो_पर्या("MENUCONFIG_MODE");
	अगर (mode) अणु
		अगर (!strहालcmp(mode, "single_menu"))
			single_menu_mode = 1;
	पूर्ण

	अगर (init_dialog(शून्य)) अणु
		ख_लिखो(मानक_त्रुटि, "Your display is too small to run Menuconfig!\n");
		ख_लिखो(मानक_त्रुटि, "It must be at least 19 lines by 80 columns.\n");
		वापस 1;
	पूर्ण

	set_config_filename(conf_get_configname());
	conf_set_message_callback(conf_message_callback);
	करो अणु
		conf(&rooपंचांगenu, शून्य);
		res = handle_निकास();
	पूर्ण जबतक (res == KEY_ESC);

	वापस res;
पूर्ण
