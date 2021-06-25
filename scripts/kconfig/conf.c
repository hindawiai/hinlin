<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2002 Roman Zippel <zippel@linux-m68k.org>
 */

#समावेश <प्रकार.स>
#समावेश <सीमा.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <समय.स>
#समावेश <unistd.h>
#समावेश <getopt.h>
#समावेश <sys/समय.स>
#समावेश <त्रुटिसं.स>

#समावेश "lkc.h"

अटल व्योम conf(काष्ठा menu *menu);
अटल व्योम check_conf(काष्ठा menu *menu);

क्रमागत input_mode अणु
	oldaskconfig,
	syncconfig,
	oldconfig,
	allnoconfig,
	allyesconfig,
	allmodconfig,
	alldefconfig,
	अक्रमconfig,
	defconfig,
	savedefconfig,
	listnewconfig,
	helpnewconfig,
	olddefconfig,
	yes2modconfig,
	mod2yesconfig,
पूर्ण;
अटल क्रमागत input_mode input_mode = oldaskconfig;
अटल पूर्णांक input_mode_opt;
अटल पूर्णांक indent = 1;
अटल पूर्णांक tty_stdio;
अटल पूर्णांक sync_kconfig;
अटल पूर्णांक conf_cnt;
अटल अक्षर line[PATH_MAX];
अटल काष्ठा menu *rootEntry;

अटल व्योम prपूर्णांक_help(काष्ठा menu *menu)
अणु
	काष्ठा gstr help = str_new();

	menu_get_ext_help(menu, &help);

	म_लिखो("\n%s\n", str_get(&help));
	str_मुक्त(&help);
पूर्ण

अटल व्योम strip(अक्षर *str)
अणु
	अक्षर *p = str;
	पूर्णांक l;

	जबतक ((है_खाली(*p)))
		p++;
	l = म_माप(p);
	अगर (p != str)
		स_हटाओ(str, p, l + 1);
	अगर (!l)
		वापस;
	p = str + l - 1;
	जबतक ((है_खाली(*p)))
		*p-- = 0;
पूर्ण

/* Helper function to facilitate ख_माला_लो() by Jean Sacren. */
अटल व्योम xख_माला_लो(अक्षर *str, पूर्णांक size, खाता *in)
अणु
	अगर (!ख_माला_लो(str, size, in))
		ख_लिखो(मानक_त्रुटि, "\nError in reading or end of file.\n");

	अगर (!tty_stdio)
		म_लिखो("%s", str);
पूर्ण

अटल व्योम set_अक्रमconfig_seed(व्योम)
अणु
	अचिन्हित पूर्णांक seed;
	अक्षर *env;
	bool seed_set = false;

	env = दो_पर्या("KCONFIG_SEED");
	अगर (env && *env) अणु
		अक्षर *endp;

		seed = म_से_दीर्घ(env, &endp, 0);
		अगर (*endp == '\0')
			seed_set = true;
	पूर्ण

	अगर (!seed_set) अणु
		काष्ठा समयval now;

		/*
		 * Use microseconds derived seed, compensate क्रम प्रणालीs where it may
		 * be zero.
		 */
		समय_लोofday(&now, शून्य);
		seed = (now.tv_sec + 1) * (now.tv_usec + 1);
	पूर्ण

	म_लिखो("KCONFIG_SEED=0x%X\n", seed);
	बेक्रम(seed);
पूर्ण

अटल bool अक्रमomize_choice_values(काष्ठा symbol *csym)
अणु
	काष्ठा property *prop;
	काष्ठा symbol *sym;
	काष्ठा expr *e;
	पूर्णांक cnt, def;

	/*
	 * If choice is mod then we may have more items selected
	 * and अगर no then no-one.
	 * In both हालs stop.
	 */
	अगर (csym->curr.tri != yes)
		वापस false;

	prop = sym_get_choice_prop(csym);

	/* count entries in choice block */
	cnt = 0;
	expr_list_क्रम_each_sym(prop->expr, e, sym)
		cnt++;

	/*
	 * find a अक्रमom value and set it to yes,
	 * set the rest to no so we have only one set
	 */
	def = अक्रम() % cnt;

	cnt = 0;
	expr_list_क्रम_each_sym(prop->expr, e, sym) अणु
		अगर (def == cnt++) अणु
			sym->def[S_DEF_USER].tri = yes;
			csym->def[S_DEF_USER].val = sym;
		पूर्ण अन्यथा अणु
			sym->def[S_DEF_USER].tri = no;
		पूर्ण
		sym->flags |= SYMBOL_DEF_USER;
		/* clear VALID to get value calculated */
		sym->flags &= ~SYMBOL_VALID;
	पूर्ण
	csym->flags |= SYMBOL_DEF_USER;
	/* clear VALID to get value calculated */
	csym->flags &= ~SYMBOL_VALID;

	वापस true;
पूर्ण

क्रमागत conf_def_mode अणु
	def_शेष,
	def_yes,
	def_mod,
	def_y2m,
	def_m2y,
	def_no,
	def_अक्रमom
पूर्ण;

अटल bool conf_set_all_new_symbols(क्रमागत conf_def_mode mode)
अणु
	काष्ठा symbol *sym, *csym;
	पूर्णांक i, cnt;
	/*
	 * can't go as the शेष in चयन-हाल below, otherwise gcc whines
	 * about -Wmaybe-uninitialized
	 */
	पूर्णांक pby = 50; /* probability of bool     = y */
	पूर्णांक pty = 33; /* probability of tristate = y */
	पूर्णांक pपंचांग = 33; /* probability of tristate = m */
	bool has_changed = false;

	अगर (mode == def_अक्रमom) अणु
		पूर्णांक n, p[3];
		अक्षर *env = दो_पर्या("KCONFIG_PROBABILITY");

		n = 0;
		जबतक (env && *env) अणु
			अक्षर *endp;
			पूर्णांक पंचांगp = म_से_दीर्घ(env, &endp, 10);

			अगर (पंचांगp >= 0 && पंचांगp <= 100) अणु
				p[n++] = पंचांगp;
			पूर्ण अन्यथा अणु
				त्रुटि_सं = दुस्फल;
				लिखो_त्रुटि("KCONFIG_PROBABILITY");
				निकास(1);
			पूर्ण
			env = (*endp == ':') ? endp + 1 : endp;
			अगर (n >= 3)
				अवरोध;
		पूर्ण
		चयन (n) अणु
		हाल 1:
			pby = p[0];
			pपंचांग = pby / 2;
			pty = pby - pपंचांग;
			अवरोध;
		हाल 2:
			pty = p[0];
			pपंचांग = p[1];
			pby = pty + pपंचांग;
			अवरोध;
		हाल 3:
			pby = p[0];
			pty = p[1];
			pपंचांग = p[2];
			अवरोध;
		पूर्ण

		अगर (pty + pपंचांग > 100) अणु
			त्रुटि_सं = दुस्फल;
			लिखो_त्रुटि("KCONFIG_PROBABILITY");
			निकास(1);
		पूर्ण
	पूर्ण

	क्रम_all_symbols(i, sym) अणु
		अगर (sym_has_value(sym) || sym->flags & SYMBOL_VALID)
			जारी;
		चयन (sym_get_type(sym)) अणु
		हाल S_BOOLEAN:
		हाल S_TRISTATE:
			has_changed = true;
			चयन (mode) अणु
			हाल def_yes:
				sym->def[S_DEF_USER].tri = yes;
				अवरोध;
			हाल def_mod:
				sym->def[S_DEF_USER].tri = mod;
				अवरोध;
			हाल def_no:
				sym->def[S_DEF_USER].tri = no;
				अवरोध;
			हाल def_अक्रमom:
				sym->def[S_DEF_USER].tri = no;
				cnt = अक्रम() % 100;
				अगर (sym->type == S_TRISTATE) अणु
					अगर (cnt < pty)
						sym->def[S_DEF_USER].tri = yes;
					अन्यथा अगर (cnt < pty + pपंचांग)
						sym->def[S_DEF_USER].tri = mod;
				पूर्ण अन्यथा अगर (cnt < pby)
					sym->def[S_DEF_USER].tri = yes;
				अवरोध;
			शेष:
				जारी;
			पूर्ण
			अगर (!(sym_is_choice(sym) && mode == def_अक्रमom))
				sym->flags |= SYMBOL_DEF_USER;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

	पूर्ण

	sym_clear_all_valid();

	/*
	 * We have dअगरferent type of choice blocks.
	 * If curr.tri equals to mod then we can select several
	 * choice symbols in one block.
	 * In this हाल we करो nothing.
	 * If curr.tri equals yes then only one symbol can be
	 * selected in a choice block and we set it to yes,
	 * and the rest to no.
	 */
	अगर (mode != def_अक्रमom) अणु
		क्रम_all_symbols(i, csym) अणु
			अगर ((sym_is_choice(csym) && !sym_has_value(csym)) ||
			    sym_is_choice_value(csym))
				csym->flags |= SYMBOL_NEED_SET_CHOICE_VALUES;
		पूर्ण
	पूर्ण

	क्रम_all_symbols(i, csym) अणु
		अगर (sym_has_value(csym) || !sym_is_choice(csym))
			जारी;

		sym_calc_value(csym);
		अगर (mode == def_अक्रमom)
			has_changed |= अक्रमomize_choice_values(csym);
		अन्यथा अणु
			set_all_choice_values(csym);
			has_changed = true;
		पूर्ण
	पूर्ण

	वापस has_changed;
पूर्ण

अटल व्योम conf_reग_लिखो_mod_or_yes(क्रमागत conf_def_mode mode)
अणु
	काष्ठा symbol *sym;
	पूर्णांक i;
	tristate old_val = (mode == def_y2m) ? yes : mod;
	tristate new_val = (mode == def_y2m) ? mod : yes;

	क्रम_all_symbols(i, sym) अणु
		अगर (sym_get_type(sym) == S_TRISTATE &&
		    sym->def[S_DEF_USER].tri == old_val)
			sym->def[S_DEF_USER].tri = new_val;
	पूर्ण
	sym_clear_all_valid();
पूर्ण

अटल पूर्णांक conf_askvalue(काष्ठा symbol *sym, स्थिर अक्षर *def)
अणु
	अगर (!sym_has_value(sym))
		म_लिखो("(NEW) ");

	line[0] = '\n';
	line[1] = 0;

	अगर (!sym_is_changeable(sym)) अणु
		म_लिखो("%s\n", def);
		line[0] = '\n';
		line[1] = 0;
		वापस 0;
	पूर्ण

	चयन (input_mode) अणु
	हाल oldconfig:
	हाल syncconfig:
		अगर (sym_has_value(sym)) अणु
			म_लिखो("%s\n", def);
			वापस 0;
		पूर्ण
		/* fall through */
	शेष:
		ख_साफ(मानक_निकास);
		xख_माला_लो(line, माप(line), मानक_निवेश);
		अवरोध;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक conf_string(काष्ठा menu *menu)
अणु
	काष्ठा symbol *sym = menu->sym;
	स्थिर अक्षर *def;

	जबतक (1) अणु
		म_लिखो("%*s%s ", indent - 1, "", menu->prompt->text);
		म_लिखो("(%s) ", sym->name);
		def = sym_get_string_value(sym);
		अगर (def)
			म_लिखो("[%s] ", def);
		अगर (!conf_askvalue(sym, def))
			वापस 0;
		चयन (line[0]) अणु
		हाल '\n':
			अवरोध;
		हाल '?':
			/* prपूर्णांक help */
			अगर (line[1] == '\n') अणु
				prपूर्णांक_help(menu);
				def = शून्य;
				अवरोध;
			पूर्ण
			/* fall through */
		शेष:
			line[म_माप(line)-1] = 0;
			def = line;
		पूर्ण
		अगर (def && sym_set_string_value(sym, def))
			वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक conf_sym(काष्ठा menu *menu)
अणु
	काष्ठा symbol *sym = menu->sym;
	tristate oldval, newval;

	जबतक (1) अणु
		म_लिखो("%*s%s ", indent - 1, "", menu->prompt->text);
		अगर (sym->name)
			म_लिखो("(%s) ", sym->name);
		अक्षर_दो('[');
		oldval = sym_get_tristate_value(sym);
		चयन (oldval) अणु
		हाल no:
			अक्षर_दो('N');
			अवरोध;
		हाल mod:
			अक्षर_दो('M');
			अवरोध;
		हाल yes:
			अक्षर_दो('Y');
			अवरोध;
		पूर्ण
		अगर (oldval != no && sym_tristate_within_range(sym, no))
			म_लिखो("/n");
		अगर (oldval != mod && sym_tristate_within_range(sym, mod))
			म_लिखो("/m");
		अगर (oldval != yes && sym_tristate_within_range(sym, yes))
			म_लिखो("/y");
		म_लिखो("/?] ");
		अगर (!conf_askvalue(sym, sym_get_string_value(sym)))
			वापस 0;
		strip(line);

		चयन (line[0]) अणु
		हाल 'n':
		हाल 'N':
			newval = no;
			अगर (!line[1] || !म_भेद(&line[1], "o"))
				अवरोध;
			जारी;
		हाल 'm':
		हाल 'M':
			newval = mod;
			अगर (!line[1])
				अवरोध;
			जारी;
		हाल 'y':
		हाल 'Y':
			newval = yes;
			अगर (!line[1] || !म_भेद(&line[1], "es"))
				अवरोध;
			जारी;
		हाल 0:
			newval = oldval;
			अवरोध;
		हाल '?':
			जाओ help;
		शेष:
			जारी;
		पूर्ण
		अगर (sym_set_tristate_value(sym, newval))
			वापस 0;
help:
		prपूर्णांक_help(menu);
	पूर्ण
पूर्ण

अटल पूर्णांक conf_choice(काष्ठा menu *menu)
अणु
	काष्ठा symbol *sym, *def_sym;
	काष्ठा menu *child;
	bool is_new;

	sym = menu->sym;
	is_new = !sym_has_value(sym);
	अगर (sym_is_changeable(sym)) अणु
		conf_sym(menu);
		sym_calc_value(sym);
		चयन (sym_get_tristate_value(sym)) अणु
		हाल no:
			वापस 1;
		हाल mod:
			वापस 0;
		हाल yes:
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (sym_get_tristate_value(sym)) अणु
		हाल no:
			वापस 1;
		हाल mod:
			म_लिखो("%*s%s\n", indent - 1, "", menu_get_prompt(menu));
			वापस 0;
		हाल yes:
			अवरोध;
		पूर्ण
	पूर्ण

	जबतक (1) अणु
		पूर्णांक cnt, def;

		म_लिखो("%*s%s\n", indent - 1, "", menu_get_prompt(menu));
		def_sym = sym_get_choice_value(sym);
		cnt = def = 0;
		line[0] = 0;
		क्रम (child = menu->list; child; child = child->next) अणु
			अगर (!menu_is_visible(child))
				जारी;
			अगर (!child->sym) अणु
				म_लिखो("%*c %s\n", indent, '*', menu_get_prompt(child));
				जारी;
			पूर्ण
			cnt++;
			अगर (child->sym == def_sym) अणु
				def = cnt;
				म_लिखो("%*c", indent, '>');
			पूर्ण अन्यथा
				म_लिखो("%*c", indent, ' ');
			म_लिखो(" %d. %s", cnt, menu_get_prompt(child));
			अगर (child->sym->name)
				म_लिखो(" (%s)", child->sym->name);
			अगर (!sym_has_value(child->sym))
				म_लिखो(" (NEW)");
			म_लिखो("\n");
		पूर्ण
		म_लिखो("%*schoice", indent - 1, "");
		अगर (cnt == 1) अणु
			म_लिखो("[1]: 1\n");
			जाओ conf_childs;
		पूर्ण
		म_लिखो("[1-%d?]: ", cnt);
		चयन (input_mode) अणु
		हाल oldconfig:
		हाल syncconfig:
			अगर (!is_new) अणु
				cnt = def;
				म_लिखो("%d\n", cnt);
				अवरोध;
			पूर्ण
			/* fall through */
		हाल oldaskconfig:
			ख_साफ(मानक_निकास);
			xख_माला_लो(line, माप(line), मानक_निवेश);
			strip(line);
			अगर (line[0] == '?') अणु
				prपूर्णांक_help(menu);
				जारी;
			पूर्ण
			अगर (!line[0])
				cnt = def;
			अन्यथा अगर (है_अंक(line[0]))
				cnt = म_से_प(line);
			अन्यथा
				जारी;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

	conf_childs:
		क्रम (child = menu->list; child; child = child->next) अणु
			अगर (!child->sym || !menu_is_visible(child))
				जारी;
			अगर (!--cnt)
				अवरोध;
		पूर्ण
		अगर (!child)
			जारी;
		अगर (line[0] && line[म_माप(line) - 1] == '?') अणु
			prपूर्णांक_help(child);
			जारी;
		पूर्ण
		sym_set_choice_value(sym, child->sym);
		क्रम (child = child->list; child; child = child->next) अणु
			indent += 2;
			conf(child);
			indent -= 2;
		पूर्ण
		वापस 1;
	पूर्ण
पूर्ण

अटल व्योम conf(काष्ठा menu *menu)
अणु
	काष्ठा symbol *sym;
	काष्ठा property *prop;
	काष्ठा menu *child;

	अगर (!menu_is_visible(menu))
		वापस;

	sym = menu->sym;
	prop = menu->prompt;
	अगर (prop) अणु
		स्थिर अक्षर *prompt;

		चयन (prop->type) अणु
		हाल P_MENU:
			/*
			 * Except in oldaskconfig mode, we show only menus that
			 * contain new symbols.
			 */
			अगर (input_mode != oldaskconfig && rootEntry != menu) अणु
				check_conf(menu);
				वापस;
			पूर्ण
			/* fall through */
		हाल P_COMMENT:
			prompt = menu_get_prompt(menu);
			अगर (prompt)
				म_लिखो("%*c\n%*c %s\n%*c\n",
					indent, '*',
					indent, '*', prompt,
					indent, '*');
		शेष:
			;
		पूर्ण
	पूर्ण

	अगर (!sym)
		जाओ conf_childs;

	अगर (sym_is_choice(sym)) अणु
		conf_choice(menu);
		अगर (sym->curr.tri != mod)
			वापस;
		जाओ conf_childs;
	पूर्ण

	चयन (sym->type) अणु
	हाल S_INT:
	हाल S_HEX:
	हाल S_STRING:
		conf_string(menu);
		अवरोध;
	शेष:
		conf_sym(menu);
		अवरोध;
	पूर्ण

conf_childs:
	अगर (sym)
		indent += 2;
	क्रम (child = menu->list; child; child = child->next)
		conf(child);
	अगर (sym)
		indent -= 2;
पूर्ण

अटल व्योम check_conf(काष्ठा menu *menu)
अणु
	काष्ठा symbol *sym;
	काष्ठा menu *child;

	अगर (!menu_is_visible(menu))
		वापस;

	sym = menu->sym;
	अगर (sym && !sym_has_value(sym) &&
	    (sym_is_changeable(sym) ||
	     (sym_is_choice(sym) && sym_get_tristate_value(sym) == yes))) अणु

		चयन (input_mode) अणु
		हाल listnewconfig:
			अगर (sym->name) अणु
				स्थिर अक्षर *str;

				अगर (sym->type == S_STRING) अणु
					str = sym_get_string_value(sym);
					str = sym_escape_string_value(str);
					म_लिखो("%s%s=%s\n", CONFIG_, sym->name, str);
					मुक्त((व्योम *)str);
				पूर्ण अन्यथा अणु
					str = sym_get_string_value(sym);
					म_लिखो("%s%s=%s\n", CONFIG_, sym->name, str);
				पूर्ण
			पूर्ण
			अवरोध;
		हाल helpnewconfig:
			म_लिखो("-----\n");
			prपूर्णांक_help(menu);
			म_लिखो("-----\n");
			अवरोध;
		शेष:
			अगर (!conf_cnt++)
				म_लिखो("*\n* Restart config...\n*\n");
			rootEntry = menu_get_parent_menu(menu);
			conf(rootEntry);
			अवरोध;
		पूर्ण
	पूर्ण

	क्रम (child = menu->list; child; child = child->next)
		check_conf(child);
पूर्ण

अटल काष्ठा option दीर्घ_opts[] = अणु
	अणु"help",          no_argument,       शून्य,            'h'पूर्ण,
	अणु"silent",        no_argument,       शून्य,            's'पूर्ण,
	अणु"oldaskconfig",  no_argument,       &input_mode_opt, oldaskconfigपूर्ण,
	अणु"oldconfig",     no_argument,       &input_mode_opt, oldconfigपूर्ण,
	अणु"syncconfig",    no_argument,       &input_mode_opt, syncconfigपूर्ण,
	अणु"defconfig",     required_argument, &input_mode_opt, defconfigपूर्ण,
	अणु"savedefconfig", required_argument, &input_mode_opt, savedefconfigपूर्ण,
	अणु"allnoconfig",   no_argument,       &input_mode_opt, allnoconfigपूर्ण,
	अणु"allyesconfig",  no_argument,       &input_mode_opt, allyesconfigपूर्ण,
	अणु"allmodconfig",  no_argument,       &input_mode_opt, allmodconfigपूर्ण,
	अणु"alldefconfig",  no_argument,       &input_mode_opt, alldefconfigपूर्ण,
	अणु"randconfig",    no_argument,       &input_mode_opt, अक्रमconfigपूर्ण,
	अणु"listnewconfig", no_argument,       &input_mode_opt, listnewconfigपूर्ण,
	अणु"helpnewconfig", no_argument,       &input_mode_opt, helpnewconfigपूर्ण,
	अणु"olddefconfig",  no_argument,       &input_mode_opt, olddefconfigपूर्ण,
	अणु"yes2modconfig", no_argument,       &input_mode_opt, yes2modconfigपूर्ण,
	अणु"mod2yesconfig", no_argument,       &input_mode_opt, mod2yesconfigपूर्ण,
	अणुशून्य, 0, शून्य, 0पूर्ण
पूर्ण;

अटल व्योम conf_usage(स्थिर अक्षर *progname)
अणु
	म_लिखो("Usage: %s [options] <kconfig-file>\n", progname);
	म_लिखो("\n");
	म_लिखो("Generic options:\n");
	म_लिखो("  -h, --help              Print this message and exit.\n");
	म_लिखो("  -s, --silent            Do not print log.\n");
	म_लिखो("\n");
	म_लिखो("Mode options:\n");
	म_लिखो("  --listnewconfig         List new options\n");
	म_लिखो("  --helpnewconfig         List new options and help text\n");
	म_लिखो("  --oldaskconfig          Start a new configuration using a line-oriented program\n");
	म_लिखो("  --oldconfig             Update a configuration using a provided .config as base\n");
	म_लिखो("  --syncconfig            Similar to oldconfig but generates configuration in\n"
	       "                          include/{generated/,config/}\n");
	म_लिखो("  --olddefconfig          Same as oldconfig but sets new symbols to their default value\n");
	म_लिखो("  --defconfig <file>      New config with default defined in <file>\n");
	म_लिखो("  --savedefconfig <file>  Save the minimal current configuration to <file>\n");
	म_लिखो("  --allnoconfig           New config where all options are answered with no\n");
	म_लिखो("  --allyesconfig          New config where all options are answered with yes\n");
	म_लिखो("  --allmodconfig          New config where all options are answered with mod\n");
	म_लिखो("  --alldefconfig          New config with all symbols set to default\n");
	म_लिखो("  --randconfig            New config with random answer to all options\n");
	म_लिखो("  --yes2modconfig         Change answers from yes to mod if possible\n");
	म_लिखो("  --mod2yesconfig         Change answers from mod to yes if possible\n");
	म_लिखो("  (If none of the above is given, --oldaskconfig is the default)\n");
पूर्ण

पूर्णांक मुख्य(पूर्णांक ac, अक्षर **av)
अणु
	स्थिर अक्षर *progname = av[0];
	पूर्णांक opt;
	स्थिर अक्षर *name, *defconfig_file = शून्य /* gcc uninit */;
	पूर्णांक no_conf_ग_लिखो = 0;

	tty_stdio = isatty(0) && isatty(1);

	जबतक ((opt = getopt_दीर्घ(ac, av, "hs", दीर्घ_opts, शून्य)) != -1) अणु
		चयन (opt) अणु
		हाल 'h':
			conf_usage(progname);
			निकास(1);
			अवरोध;
		हाल 's':
			conf_set_message_callback(शून्य);
			अवरोध;
		हाल 0:
			input_mode = input_mode_opt;
			चयन (input_mode) अणु
			हाल syncconfig:
				/*
				 * syncconfig is invoked during the build stage.
				 * Suppress distracting
				 *   "configuration written to ..."
				 */
				conf_set_message_callback(शून्य);
				sync_kconfig = 1;
				अवरोध;
			हाल defconfig:
			हाल savedefconfig:
				defconfig_file = optarg;
				अवरोध;
			हाल अक्रमconfig:
				set_अक्रमconfig_seed();
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (ac == optind) अणु
		ख_लिखो(मानक_त्रुटि, "%s: Kconfig file missing\n", av[0]);
		conf_usage(progname);
		निकास(1);
	पूर्ण
	conf_parse(av[optind]);
	//zconfdump(मानक_निकास);

	चयन (input_mode) अणु
	हाल defconfig:
		अगर (conf_पढ़ो(defconfig_file)) अणु
			ख_लिखो(मानक_त्रुटि,
				"***\n"
				  "*** Can't find default configuration \"%s\"!\n"
				  "***\n",
				defconfig_file);
			निकास(1);
		पूर्ण
		अवरोध;
	हाल savedefconfig:
	हाल syncconfig:
	हाल oldaskconfig:
	हाल oldconfig:
	हाल listnewconfig:
	हाल helpnewconfig:
	हाल olddefconfig:
	हाल yes2modconfig:
	हाल mod2yesconfig:
		conf_पढ़ो(शून्य);
		अवरोध;
	हाल allnoconfig:
	हाल allyesconfig:
	हाल allmodconfig:
	हाल alldefconfig:
	हाल अक्रमconfig:
		name = दो_पर्या("KCONFIG_ALLCONFIG");
		अगर (!name)
			अवरोध;
		अगर ((म_भेद(name, "") != 0) && (म_भेद(name, "1") != 0)) अणु
			अगर (conf_पढ़ो_simple(name, S_DEF_USER)) अणु
				ख_लिखो(मानक_त्रुटि,
					"*** Can't read seed configuration \"%s\"!\n",
					name);
				निकास(1);
			पूर्ण
			अवरोध;
		पूर्ण
		चयन (input_mode) अणु
		हाल allnoconfig:	name = "allno.config"; अवरोध;
		हाल allyesconfig:	name = "allyes.config"; अवरोध;
		हाल allmodconfig:	name = "allmod.config"; अवरोध;
		हाल alldefconfig:	name = "alldef.config"; अवरोध;
		हाल अक्रमconfig:	name = "allrandom.config"; अवरोध;
		शेष: अवरोध;
		पूर्ण
		अगर (conf_पढ़ो_simple(name, S_DEF_USER) &&
		    conf_पढ़ो_simple("all.config", S_DEF_USER)) अणु
			ख_लिखो(मानक_त्रुटि,
				"*** KCONFIG_ALLCONFIG set, but no \"%s\" or \"all.config\" file found\n",
				name);
			निकास(1);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (sync_kconfig) अणु
		name = दो_पर्या("KCONFIG_NOSILENTUPDATE");
		अगर (name && *name) अणु
			अगर (conf_get_changed()) अणु
				ख_लिखो(मानक_त्रुटि,
					"\n*** The configuration requires explicit update.\n\n");
				वापस 1;
			पूर्ण
			no_conf_ग_लिखो = 1;
		पूर्ण
	पूर्ण

	चयन (input_mode) अणु
	हाल allnoconfig:
		conf_set_all_new_symbols(def_no);
		अवरोध;
	हाल allyesconfig:
		conf_set_all_new_symbols(def_yes);
		अवरोध;
	हाल allmodconfig:
		conf_set_all_new_symbols(def_mod);
		अवरोध;
	हाल alldefconfig:
		conf_set_all_new_symbols(def_शेष);
		अवरोध;
	हाल अक्रमconfig:
		/* Really nothing to करो in this loop */
		जबतक (conf_set_all_new_symbols(def_अक्रमom)) ;
		अवरोध;
	हाल defconfig:
		conf_set_all_new_symbols(def_शेष);
		अवरोध;
	हाल savedefconfig:
		अवरोध;
	हाल yes2modconfig:
		conf_reग_लिखो_mod_or_yes(def_y2m);
		अवरोध;
	हाल mod2yesconfig:
		conf_reग_लिखो_mod_or_yes(def_m2y);
		अवरोध;
	हाल oldaskconfig:
		rootEntry = &rooपंचांगenu;
		conf(&rooपंचांगenu);
		input_mode = oldconfig;
		/* fall through */
	हाल oldconfig:
	हाल listnewconfig:
	हाल helpnewconfig:
	हाल syncconfig:
		/* Update until a loop caused no more changes */
		करो अणु
			conf_cnt = 0;
			check_conf(&rooपंचांगenu);
		पूर्ण जबतक (conf_cnt);
		अवरोध;
	हाल olddefconfig:
	शेष:
		अवरोध;
	पूर्ण

	अगर (input_mode == savedefconfig) अणु
		अगर (conf_ग_लिखो_defconfig(defconfig_file)) अणु
			ख_लिखो(मानक_त्रुटि, "n*** Error while saving defconfig to: %s\n\n",
				defconfig_file);
			वापस 1;
		पूर्ण
	पूर्ण अन्यथा अगर (input_mode != listnewconfig && input_mode != helpnewconfig) अणु
		अगर (!no_conf_ग_लिखो && conf_ग_लिखो(शून्य)) अणु
			ख_लिखो(मानक_त्रुटि, "\n*** Error during writing of the configuration.\n\n");
			निकास(1);
		पूर्ण

		/*
		 * Create स्वतः.conf अगर it करोes not exist.
		 * This prevents GNU Make 4.1 or older from emitting
		 * "include/config/auto.conf: No such file or directory"
		 * in the top-level Makefile
		 *
		 * syncconfig always creates or updates स्वतः.conf because it is
		 * used during the build.
		 */
		अगर (conf_ग_लिखो_स्वतःconf(sync_kconfig) && sync_kconfig) अणु
			ख_लिखो(मानक_त्रुटि,
				"\n*** Error during sync of the configuration.\n\n");
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
