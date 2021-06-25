<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2002 Roman Zippel <zippel@linux-m68k.org>
 */

#समावेश <sys/types.h>
#समावेश <प्रकार.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <regex.h>

#समावेश "lkc.h"

काष्ठा symbol symbol_yes = अणु
	.name = "y",
	.curr = अणु "y", yes पूर्ण,
	.flags = SYMBOL_CONST|SYMBOL_VALID,
पूर्ण;

काष्ठा symbol symbol_mod = अणु
	.name = "m",
	.curr = अणु "m", mod पूर्ण,
	.flags = SYMBOL_CONST|SYMBOL_VALID,
पूर्ण;

काष्ठा symbol symbol_no = अणु
	.name = "n",
	.curr = अणु "n", no पूर्ण,
	.flags = SYMBOL_CONST|SYMBOL_VALID,
पूर्ण;

अटल काष्ठा symbol symbol_empty = अणु
	.name = "",
	.curr = अणु "", no पूर्ण,
	.flags = SYMBOL_VALID,
पूर्ण;

काष्ठा symbol *modules_sym;
अटल tristate modules_val;

क्रमागत symbol_type sym_get_type(काष्ठा symbol *sym)
अणु
	क्रमागत symbol_type type = sym->type;

	अगर (type == S_TRISTATE) अणु
		अगर (sym_is_choice_value(sym) && sym->visible == yes)
			type = S_BOOLEAN;
		अन्यथा अगर (modules_val == no)
			type = S_BOOLEAN;
	पूर्ण
	वापस type;
पूर्ण

स्थिर अक्षर *sym_type_name(क्रमागत symbol_type type)
अणु
	चयन (type) अणु
	हाल S_BOOLEAN:
		वापस "bool";
	हाल S_TRISTATE:
		वापस "tristate";
	हाल S_INT:
		वापस "integer";
	हाल S_HEX:
		वापस "hex";
	हाल S_STRING:
		वापस "string";
	हाल S_UNKNOWN:
		वापस "unknown";
	पूर्ण
	वापस "???";
पूर्ण

काष्ठा property *sym_get_choice_prop(काष्ठा symbol *sym)
अणु
	काष्ठा property *prop;

	क्रम_all_choices(sym, prop)
		वापस prop;
	वापस शून्य;
पूर्ण

अटल काष्ठा property *sym_get_शेष_prop(काष्ठा symbol *sym)
अणु
	काष्ठा property *prop;

	क्रम_all_शेषs(sym, prop) अणु
		prop->visible.tri = expr_calc_value(prop->visible.expr);
		अगर (prop->visible.tri != no)
			वापस prop;
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा property *sym_get_range_prop(काष्ठा symbol *sym)
अणु
	काष्ठा property *prop;

	क्रम_all_properties(sym, prop, P_RANGE) अणु
		prop->visible.tri = expr_calc_value(prop->visible.expr);
		अगर (prop->visible.tri != no)
			वापस prop;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल दीर्घ दीर्घ sym_get_range_val(काष्ठा symbol *sym, पूर्णांक base)
अणु
	sym_calc_value(sym);
	चयन (sym->type) अणु
	हाल S_INT:
		base = 10;
		अवरोध;
	हाल S_HEX:
		base = 16;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस म_से_दीर्घl(sym->curr.val, शून्य, base);
पूर्ण

अटल व्योम sym_validate_range(काष्ठा symbol *sym)
अणु
	काष्ठा property *prop;
	पूर्णांक base;
	दीर्घ दीर्घ val, val2;
	अक्षर str[64];

	चयन (sym->type) अणु
	हाल S_INT:
		base = 10;
		अवरोध;
	हाल S_HEX:
		base = 16;
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	prop = sym_get_range_prop(sym);
	अगर (!prop)
		वापस;
	val = म_से_दीर्घl(sym->curr.val, शून्य, base);
	val2 = sym_get_range_val(prop->expr->left.sym, base);
	अगर (val >= val2) अणु
		val2 = sym_get_range_val(prop->expr->right.sym, base);
		अगर (val <= val2)
			वापस;
	पूर्ण
	अगर (sym->type == S_INT)
		प्र_लिखो(str, "%lld", val2);
	अन्यथा
		प्र_लिखो(str, "0x%llx", val2);
	sym->curr.val = xstrdup(str);
पूर्ण

अटल व्योम sym_set_changed(काष्ठा symbol *sym)
अणु
	काष्ठा property *prop;

	sym->flags |= SYMBOL_CHANGED;
	क्रम (prop = sym->prop; prop; prop = prop->next) अणु
		अगर (prop->menu)
			prop->menu->flags |= MENU_CHANGED;
	पूर्ण
पूर्ण

अटल व्योम sym_set_all_changed(व्योम)
अणु
	काष्ठा symbol *sym;
	पूर्णांक i;

	क्रम_all_symbols(i, sym)
		sym_set_changed(sym);
पूर्ण

अटल व्योम sym_calc_visibility(काष्ठा symbol *sym)
अणु
	काष्ठा property *prop;
	काष्ठा symbol *choice_sym = शून्य;
	tristate tri;

	/* any prompt visible? */
	tri = no;

	अगर (sym_is_choice_value(sym))
		choice_sym = prop_get_symbol(sym_get_choice_prop(sym));

	क्रम_all_prompts(sym, prop) अणु
		prop->visible.tri = expr_calc_value(prop->visible.expr);
		/*
		 * Tristate choice_values with visibility 'mod' are
		 * not visible अगर the corresponding choice's value is
		 * 'yes'.
		 */
		अगर (choice_sym && sym->type == S_TRISTATE &&
		    prop->visible.tri == mod && choice_sym->curr.tri == yes)
			prop->visible.tri = no;

		tri = EXPR_OR(tri, prop->visible.tri);
	पूर्ण
	अगर (tri == mod && (sym->type != S_TRISTATE || modules_val == no))
		tri = yes;
	अगर (sym->visible != tri) अणु
		sym->visible = tri;
		sym_set_changed(sym);
	पूर्ण
	अगर (sym_is_choice_value(sym))
		वापस;
	/* शेषing to "yes" अगर no explicit "depends on" are given */
	tri = yes;
	अगर (sym->dir_dep.expr)
		tri = expr_calc_value(sym->dir_dep.expr);
	अगर (tri == mod && sym_get_type(sym) == S_BOOLEAN)
		tri = yes;
	अगर (sym->dir_dep.tri != tri) अणु
		sym->dir_dep.tri = tri;
		sym_set_changed(sym);
	पूर्ण
	tri = no;
	अगर (sym->rev_dep.expr)
		tri = expr_calc_value(sym->rev_dep.expr);
	अगर (tri == mod && sym_get_type(sym) == S_BOOLEAN)
		tri = yes;
	अगर (sym->rev_dep.tri != tri) अणु
		sym->rev_dep.tri = tri;
		sym_set_changed(sym);
	पूर्ण
	tri = no;
	अगर (sym->implied.expr)
		tri = expr_calc_value(sym->implied.expr);
	अगर (tri == mod && sym_get_type(sym) == S_BOOLEAN)
		tri = yes;
	अगर (sym->implied.tri != tri) अणु
		sym->implied.tri = tri;
		sym_set_changed(sym);
	पूर्ण
पूर्ण

/*
 * Find the शेष symbol क्रम a choice.
 * First try the शेष values क्रम the choice symbol
 * Next locate the first visible choice value
 * Return शून्य अगर none was found
 */
काष्ठा symbol *sym_choice_शेष(काष्ठा symbol *sym)
अणु
	काष्ठा symbol *def_sym;
	काष्ठा property *prop;
	काष्ठा expr *e;

	/* any of the शेषs visible? */
	क्रम_all_शेषs(sym, prop) अणु
		prop->visible.tri = expr_calc_value(prop->visible.expr);
		अगर (prop->visible.tri == no)
			जारी;
		def_sym = prop_get_symbol(prop);
		अगर (def_sym->visible != no)
			वापस def_sym;
	पूर्ण

	/* just get the first visible value */
	prop = sym_get_choice_prop(sym);
	expr_list_क्रम_each_sym(prop->expr, e, def_sym)
		अगर (def_sym->visible != no)
			वापस def_sym;

	/* failed to locate any शेषs */
	वापस शून्य;
पूर्ण

अटल काष्ठा symbol *sym_calc_choice(काष्ठा symbol *sym)
अणु
	काष्ठा symbol *def_sym;
	काष्ठा property *prop;
	काष्ठा expr *e;
	पूर्णांक flags;

	/* first calculate all choice values' visibilities */
	flags = sym->flags;
	prop = sym_get_choice_prop(sym);
	expr_list_क्रम_each_sym(prop->expr, e, def_sym) अणु
		sym_calc_visibility(def_sym);
		अगर (def_sym->visible != no)
			flags &= def_sym->flags;
	पूर्ण

	sym->flags &= flags | ~SYMBOL_DEF_USER;

	/* is the user choice visible? */
	def_sym = sym->def[S_DEF_USER].val;
	अगर (def_sym && def_sym->visible != no)
		वापस def_sym;

	def_sym = sym_choice_शेष(sym);

	अगर (def_sym == शून्य)
		/* no choice? reset tristate value */
		sym->curr.tri = no;

	वापस def_sym;
पूर्ण

अटल व्योम sym_warn_unmet_dep(काष्ठा symbol *sym)
अणु
	काष्ठा gstr gs = str_new();

	str_म_लिखो(&gs,
		   "\nWARNING: unmet direct dependencies detected for %s\n",
		   sym->name);
	str_म_लिखो(&gs,
		   "  Depends on [%c]: ",
		   sym->dir_dep.tri == mod ? 'm' : 'n');
	expr_gstr_prपूर्णांक(sym->dir_dep.expr, &gs);
	str_म_लिखो(&gs, "\n");

	expr_gstr_prपूर्णांक_revdep(sym->rev_dep.expr, &gs, yes,
			       "  Selected by [y]:\n");
	expr_gstr_prपूर्णांक_revdep(sym->rev_dep.expr, &gs, mod,
			       "  Selected by [m]:\n");

	ख_माला_दो(str_get(&gs), मानक_त्रुटि);
पूर्ण

व्योम sym_calc_value(काष्ठा symbol *sym)
अणु
	काष्ठा symbol_value newval, oldval;
	काष्ठा property *prop;
	काष्ठा expr *e;

	अगर (!sym)
		वापस;

	अगर (sym->flags & SYMBOL_VALID)
		वापस;

	अगर (sym_is_choice_value(sym) &&
	    sym->flags & SYMBOL_NEED_SET_CHOICE_VALUES) अणु
		sym->flags &= ~SYMBOL_NEED_SET_CHOICE_VALUES;
		prop = sym_get_choice_prop(sym);
		sym_calc_value(prop_get_symbol(prop));
	पूर्ण

	sym->flags |= SYMBOL_VALID;

	oldval = sym->curr;

	चयन (sym->type) अणु
	हाल S_INT:
	हाल S_HEX:
	हाल S_STRING:
		newval = symbol_empty.curr;
		अवरोध;
	हाल S_BOOLEAN:
	हाल S_TRISTATE:
		newval = symbol_no.curr;
		अवरोध;
	शेष:
		sym->curr.val = sym->name;
		sym->curr.tri = no;
		वापस;
	पूर्ण
	sym->flags &= ~SYMBOL_WRITE;

	sym_calc_visibility(sym);

	अगर (sym->visible != no)
		sym->flags |= SYMBOL_WRITE;

	/* set शेष अगर recursively called */
	sym->curr = newval;

	चयन (sym_get_type(sym)) अणु
	हाल S_BOOLEAN:
	हाल S_TRISTATE:
		अगर (sym_is_choice_value(sym) && sym->visible == yes) अणु
			prop = sym_get_choice_prop(sym);
			newval.tri = (prop_get_symbol(prop)->curr.val == sym) ? yes : no;
		पूर्ण अन्यथा अणु
			अगर (sym->visible != no) अणु
				/* अगर the symbol is visible use the user value
				 * अगर available, otherwise try the शेष value
				 */
				अगर (sym_has_value(sym)) अणु
					newval.tri = EXPR_AND(sym->def[S_DEF_USER].tri,
							      sym->visible);
					जाओ calc_newval;
				पूर्ण
			पूर्ण
			अगर (sym->rev_dep.tri != no)
				sym->flags |= SYMBOL_WRITE;
			अगर (!sym_is_choice(sym)) अणु
				prop = sym_get_शेष_prop(sym);
				अगर (prop) अणु
					newval.tri = EXPR_AND(expr_calc_value(prop->expr),
							      prop->visible.tri);
					अगर (newval.tri != no)
						sym->flags |= SYMBOL_WRITE;
				पूर्ण
				अगर (sym->implied.tri != no) अणु
					sym->flags |= SYMBOL_WRITE;
					newval.tri = EXPR_OR(newval.tri, sym->implied.tri);
					newval.tri = EXPR_AND(newval.tri,
							      sym->dir_dep.tri);
				पूर्ण
			पूर्ण
		calc_newval:
			अगर (sym->dir_dep.tri < sym->rev_dep.tri)
				sym_warn_unmet_dep(sym);
			newval.tri = EXPR_OR(newval.tri, sym->rev_dep.tri);
		पूर्ण
		अगर (newval.tri == mod && sym_get_type(sym) == S_BOOLEAN)
			newval.tri = yes;
		अवरोध;
	हाल S_STRING:
	हाल S_HEX:
	हाल S_INT:
		अगर (sym->visible != no && sym_has_value(sym)) अणु
			newval.val = sym->def[S_DEF_USER].val;
			अवरोध;
		पूर्ण
		prop = sym_get_शेष_prop(sym);
		अगर (prop) अणु
			काष्ठा symbol *ds = prop_get_symbol(prop);
			अगर (ds) अणु
				sym->flags |= SYMBOL_WRITE;
				sym_calc_value(ds);
				newval.val = ds->curr.val;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		;
	पूर्ण

	sym->curr = newval;
	अगर (sym_is_choice(sym) && newval.tri == yes)
		sym->curr.val = sym_calc_choice(sym);
	sym_validate_range(sym);

	अगर (स_भेद(&oldval, &sym->curr, माप(oldval))) अणु
		sym_set_changed(sym);
		अगर (modules_sym == sym) अणु
			sym_set_all_changed();
			modules_val = modules_sym->curr.tri;
		पूर्ण
	पूर्ण

	अगर (sym_is_choice(sym)) अणु
		काष्ठा symbol *choice_sym;

		prop = sym_get_choice_prop(sym);
		expr_list_क्रम_each_sym(prop->expr, e, choice_sym) अणु
			अगर ((sym->flags & SYMBOL_WRITE) &&
			    choice_sym->visible != no)
				choice_sym->flags |= SYMBOL_WRITE;
			अगर (sym->flags & SYMBOL_CHANGED)
				sym_set_changed(choice_sym);
		पूर्ण
	पूर्ण

	अगर (sym->flags & SYMBOL_NO_WRITE)
		sym->flags &= ~SYMBOL_WRITE;

	अगर (sym->flags & SYMBOL_NEED_SET_CHOICE_VALUES)
		set_all_choice_values(sym);
पूर्ण

व्योम sym_clear_all_valid(व्योम)
अणु
	काष्ठा symbol *sym;
	पूर्णांक i;

	क्रम_all_symbols(i, sym)
		sym->flags &= ~SYMBOL_VALID;
	conf_set_changed(true);
	sym_calc_value(modules_sym);
पूर्ण

bool sym_tristate_within_range(काष्ठा symbol *sym, tristate val)
अणु
	पूर्णांक type = sym_get_type(sym);

	अगर (sym->visible == no)
		वापस false;

	अगर (type != S_BOOLEAN && type != S_TRISTATE)
		वापस false;

	अगर (type == S_BOOLEAN && val == mod)
		वापस false;
	अगर (sym->visible <= sym->rev_dep.tri)
		वापस false;
	अगर (sym_is_choice_value(sym) && sym->visible == yes)
		वापस val == yes;
	वापस val >= sym->rev_dep.tri && val <= sym->visible;
पूर्ण

bool sym_set_tristate_value(काष्ठा symbol *sym, tristate val)
अणु
	tristate oldval = sym_get_tristate_value(sym);

	अगर (oldval != val && !sym_tristate_within_range(sym, val))
		वापस false;

	अगर (!(sym->flags & SYMBOL_DEF_USER)) अणु
		sym->flags |= SYMBOL_DEF_USER;
		sym_set_changed(sym);
	पूर्ण
	/*
	 * setting a choice value also resets the new flag of the choice
	 * symbol and all other choice values.
	 */
	अगर (sym_is_choice_value(sym) && val == yes) अणु
		काष्ठा symbol *cs = prop_get_symbol(sym_get_choice_prop(sym));
		काष्ठा property *prop;
		काष्ठा expr *e;

		cs->def[S_DEF_USER].val = sym;
		cs->flags |= SYMBOL_DEF_USER;
		prop = sym_get_choice_prop(cs);
		क्रम (e = prop->expr; e; e = e->left.expr) अणु
			अगर (e->right.sym->visible != no)
				e->right.sym->flags |= SYMBOL_DEF_USER;
		पूर्ण
	पूर्ण

	sym->def[S_DEF_USER].tri = val;
	अगर (oldval != val)
		sym_clear_all_valid();

	वापस true;
पूर्ण

tristate sym_toggle_tristate_value(काष्ठा symbol *sym)
अणु
	tristate oldval, newval;

	oldval = newval = sym_get_tristate_value(sym);
	करो अणु
		चयन (newval) अणु
		हाल no:
			newval = mod;
			अवरोध;
		हाल mod:
			newval = yes;
			अवरोध;
		हाल yes:
			newval = no;
			अवरोध;
		पूर्ण
		अगर (sym_set_tristate_value(sym, newval))
			अवरोध;
	पूर्ण जबतक (oldval != newval);
	वापस newval;
पूर्ण

bool sym_string_valid(काष्ठा symbol *sym, स्थिर अक्षर *str)
अणु
	चिन्हित अक्षर ch;

	चयन (sym->type) अणु
	हाल S_STRING:
		वापस true;
	हाल S_INT:
		ch = *str++;
		अगर (ch == '-')
			ch = *str++;
		अगर (!है_अंक(ch))
			वापस false;
		अगर (ch == '0' && *str != 0)
			वापस false;
		जबतक ((ch = *str++)) अणु
			अगर (!है_अंक(ch))
				वापस false;
		पूर्ण
		वापस true;
	हाल S_HEX:
		अगर (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
			str += 2;
		ch = *str++;
		करो अणु
			अगर (!है_षष्ठादशक(ch))
				वापस false;
		पूर्ण जबतक ((ch = *str++));
		वापस true;
	हाल S_BOOLEAN:
	हाल S_TRISTATE:
		चयन (str[0]) अणु
		हाल 'y': case 'Y':
		हाल 'm': case 'M':
		हाल 'n': case 'N':
			वापस true;
		पूर्ण
		वापस false;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

bool sym_string_within_range(काष्ठा symbol *sym, स्थिर अक्षर *str)
अणु
	काष्ठा property *prop;
	दीर्घ दीर्घ val;

	चयन (sym->type) अणु
	हाल S_STRING:
		वापस sym_string_valid(sym, str);
	हाल S_INT:
		अगर (!sym_string_valid(sym, str))
			वापस false;
		prop = sym_get_range_prop(sym);
		अगर (!prop)
			वापस true;
		val = म_से_दीर्घl(str, शून्य, 10);
		वापस val >= sym_get_range_val(prop->expr->left.sym, 10) &&
		       val <= sym_get_range_val(prop->expr->right.sym, 10);
	हाल S_HEX:
		अगर (!sym_string_valid(sym, str))
			वापस false;
		prop = sym_get_range_prop(sym);
		अगर (!prop)
			वापस true;
		val = म_से_दीर्घl(str, शून्य, 16);
		वापस val >= sym_get_range_val(prop->expr->left.sym, 16) &&
		       val <= sym_get_range_val(prop->expr->right.sym, 16);
	हाल S_BOOLEAN:
	हाल S_TRISTATE:
		चयन (str[0]) अणु
		हाल 'y': case 'Y':
			वापस sym_tristate_within_range(sym, yes);
		हाल 'm': case 'M':
			वापस sym_tristate_within_range(sym, mod);
		हाल 'n': case 'N':
			वापस sym_tristate_within_range(sym, no);
		पूर्ण
		वापस false;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

bool sym_set_string_value(काष्ठा symbol *sym, स्थिर अक्षर *newval)
अणु
	स्थिर अक्षर *oldval;
	अक्षर *val;
	पूर्णांक size;

	चयन (sym->type) अणु
	हाल S_BOOLEAN:
	हाल S_TRISTATE:
		चयन (newval[0]) अणु
		हाल 'y': case 'Y':
			वापस sym_set_tristate_value(sym, yes);
		हाल 'm': case 'M':
			वापस sym_set_tristate_value(sym, mod);
		हाल 'n': case 'N':
			वापस sym_set_tristate_value(sym, no);
		पूर्ण
		वापस false;
	शेष:
		;
	पूर्ण

	अगर (!sym_string_within_range(sym, newval))
		वापस false;

	अगर (!(sym->flags & SYMBOL_DEF_USER)) अणु
		sym->flags |= SYMBOL_DEF_USER;
		sym_set_changed(sym);
	पूर्ण

	oldval = sym->def[S_DEF_USER].val;
	size = म_माप(newval) + 1;
	अगर (sym->type == S_HEX && (newval[0] != '0' || (newval[1] != 'x' && newval[1] != 'X'))) अणु
		size += 2;
		sym->def[S_DEF_USER].val = val = xदो_स्मृति(size);
		*val++ = '0';
		*val++ = 'x';
	पूर्ण अन्यथा अगर (!oldval || म_भेद(oldval, newval))
		sym->def[S_DEF_USER].val = val = xदो_स्मृति(size);
	अन्यथा
		वापस true;

	म_नकल(val, newval);
	मुक्त((व्योम *)oldval);
	sym_clear_all_valid();

	वापस true;
पूर्ण

/*
 * Find the शेष value associated to a symbol.
 * For tristate symbol handle the modules=n हाल
 * in which हाल "m" becomes "y".
 * If the symbol करोes not have any शेष then fallback
 * to the fixed शेष values.
 */
स्थिर अक्षर *sym_get_string_शेष(काष्ठा symbol *sym)
अणु
	काष्ठा property *prop;
	काष्ठा symbol *ds;
	स्थिर अक्षर *str;
	tristate val;

	sym_calc_visibility(sym);
	sym_calc_value(modules_sym);
	val = symbol_no.curr.tri;
	str = symbol_empty.curr.val;

	/* If symbol has a शेष value look it up */
	prop = sym_get_शेष_prop(sym);
	अगर (prop != शून्य) अणु
		चयन (sym->type) अणु
		हाल S_BOOLEAN:
		हाल S_TRISTATE:
			/* The visibility may limit the value from yes => mod */
			val = EXPR_AND(expr_calc_value(prop->expr), prop->visible.tri);
			अवरोध;
		शेष:
			/*
			 * The following fails to handle the situation
			 * where a शेष value is further limited by
			 * the valid range.
			 */
			ds = prop_get_symbol(prop);
			अगर (ds != शून्य) अणु
				sym_calc_value(ds);
				str = (स्थिर अक्षर *)ds->curr.val;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Handle select statements */
	val = EXPR_OR(val, sym->rev_dep.tri);

	/* transpose mod to yes अगर modules are not enabled */
	अगर (val == mod)
		अगर (!sym_is_choice_value(sym) && modules_sym->curr.tri == no)
			val = yes;

	/* transpose mod to yes अगर type is bool */
	अगर (sym->type == S_BOOLEAN && val == mod)
		val = yes;

	/* adjust the शेष value अगर this symbol is implied by another */
	अगर (val < sym->implied.tri)
		val = sym->implied.tri;

	चयन (sym->type) अणु
	हाल S_BOOLEAN:
	हाल S_TRISTATE:
		चयन (val) अणु
		हाल no: वापस "n";
		हाल mod: वापस "m";
		हाल yes: वापस "y";
		पूर्ण
	हाल S_INT:
	हाल S_HEX:
		वापस str;
	हाल S_STRING:
		वापस str;
	हाल S_UNKNOWN:
		अवरोध;
	पूर्ण
	वापस "";
पूर्ण

स्थिर अक्षर *sym_get_string_value(काष्ठा symbol *sym)
अणु
	tristate val;

	चयन (sym->type) अणु
	हाल S_BOOLEAN:
	हाल S_TRISTATE:
		val = sym_get_tristate_value(sym);
		चयन (val) अणु
		हाल no:
			वापस "n";
		हाल mod:
			sym_calc_value(modules_sym);
			वापस (modules_sym->curr.tri == no) ? "n" : "m";
		हाल yes:
			वापस "y";
		पूर्ण
		अवरोध;
	शेष:
		;
	पूर्ण
	वापस (स्थिर अक्षर *)sym->curr.val;
पूर्ण

bool sym_is_changeable(काष्ठा symbol *sym)
अणु
	वापस sym->visible > sym->rev_dep.tri;
पूर्ण

अटल अचिन्हित strhash(स्थिर अक्षर *s)
अणु
	/* fnv32 hash */
	अचिन्हित hash = 2166136261U;
	क्रम (; *s; s++)
		hash = (hash ^ *s) * 0x01000193;
	वापस hash;
पूर्ण

काष्ठा symbol *sym_lookup(स्थिर अक्षर *name, पूर्णांक flags)
अणु
	काष्ठा symbol *symbol;
	अक्षर *new_name;
	पूर्णांक hash;

	अगर (name) अणु
		अगर (name[0] && !name[1]) अणु
			चयन (name[0]) अणु
			हाल 'y': वापस &symbol_yes;
			हाल 'm': वापस &symbol_mod;
			हाल 'n': वापस &symbol_no;
			पूर्ण
		पूर्ण
		hash = strhash(name) % SYMBOL_HASHSIZE;

		क्रम (symbol = symbol_hash[hash]; symbol; symbol = symbol->next) अणु
			अगर (symbol->name &&
			    !म_भेद(symbol->name, name) &&
			    (flags ? symbol->flags & flags
				   : !(symbol->flags & (SYMBOL_CONST|SYMBOL_CHOICE))))
				वापस symbol;
		पूर्ण
		new_name = xstrdup(name);
	पूर्ण अन्यथा अणु
		new_name = शून्य;
		hash = 0;
	पूर्ण

	symbol = xदो_स्मृति(माप(*symbol));
	स_रखो(symbol, 0, माप(*symbol));
	symbol->name = new_name;
	symbol->type = S_UNKNOWN;
	symbol->flags = flags;

	symbol->next = symbol_hash[hash];
	symbol_hash[hash] = symbol;

	वापस symbol;
पूर्ण

काष्ठा symbol *sym_find(स्थिर अक्षर *name)
अणु
	काष्ठा symbol *symbol = शून्य;
	पूर्णांक hash = 0;

	अगर (!name)
		वापस शून्य;

	अगर (name[0] && !name[1]) अणु
		चयन (name[0]) अणु
		हाल 'y': वापस &symbol_yes;
		हाल 'm': वापस &symbol_mod;
		हाल 'n': वापस &symbol_no;
		पूर्ण
	पूर्ण
	hash = strhash(name) % SYMBOL_HASHSIZE;

	क्रम (symbol = symbol_hash[hash]; symbol; symbol = symbol->next) अणु
		अगर (symbol->name &&
		    !म_भेद(symbol->name, name) &&
		    !(symbol->flags & SYMBOL_CONST))
				अवरोध;
	पूर्ण

	वापस symbol;
पूर्ण

स्थिर अक्षर *sym_escape_string_value(स्थिर अक्षर *in)
अणु
	स्थिर अक्षर *p;
	माप_प्रकार reslen;
	अक्षर *res;
	माप_प्रकार l;

	reslen = म_माप(in) + म_माप("\"\"") + 1;

	p = in;
	क्रम (;;) अणु
		l = म_खोज(p, "\"\\");
		p += l;

		अगर (p[0] == '\0')
			अवरोध;

		reslen++;
		p++;
	पूर्ण

	res = xदो_स्मृति(reslen);
	res[0] = '\0';

	म_जोड़ो(res, "\"");

	p = in;
	क्रम (;;) अणु
		l = म_खोज(p, "\"\\");
		म_जोड़न(res, p, l);
		p += l;

		अगर (p[0] == '\0')
			अवरोध;

		म_जोड़ो(res, "\\");
		म_जोड़न(res, p++, 1);
	पूर्ण

	म_जोड़ो(res, "\"");
	वापस res;
पूर्ण

काष्ठा sym_match अणु
	काष्ठा symbol	*sym;
	off_t		so, eo;
पूर्ण;

/* Compare matched symbols as thus:
 * - first, symbols that match exactly
 * - then, alphabetical sort
 */
अटल पूर्णांक sym_rel_comp(स्थिर व्योम *sym1, स्थिर व्योम *sym2)
अणु
	स्थिर काष्ठा sym_match *s1 = sym1;
	स्थिर काष्ठा sym_match *s2 = sym2;
	पूर्णांक exact1, exact2;

	/* Exact match:
	 * - अगर matched length on symbol s1 is the length of that symbol,
	 *   then this symbol should come first;
	 * - अगर matched length on symbol s2 is the length of that symbol,
	 *   then this symbol should come first.
	 * Note: since the search can be a regexp, both symbols may match
	 * exactly; अगर this is the हाल, we can't decide which comes first,
	 * and we fallback to sorting alphabetically.
	 */
	exact1 = (s1->eo - s1->so) == म_माप(s1->sym->name);
	exact2 = (s2->eo - s2->so) == म_माप(s2->sym->name);
	अगर (exact1 && !exact2)
		वापस -1;
	अगर (!exact1 && exact2)
		वापस 1;

	/* As a fallback, sort symbols alphabetically */
	वापस म_भेद(s1->sym->name, s2->sym->name);
पूर्ण

काष्ठा symbol **sym_re_search(स्थिर अक्षर *pattern)
अणु
	काष्ठा symbol *sym, **sym_arr = शून्य;
	काष्ठा sym_match *sym_match_arr = शून्य;
	पूर्णांक i, cnt, size;
	regex_t re;
	regmatch_t match[1];

	cnt = size = 0;
	/* Skip अगर empty */
	अगर (म_माप(pattern) == 0)
		वापस शून्य;
	अगर (regcomp(&re, pattern, REG_EXTENDED|REG_ICASE))
		वापस शून्य;

	क्रम_all_symbols(i, sym) अणु
		अगर (sym->flags & SYMBOL_CONST || !sym->name)
			जारी;
		अगर (regexec(&re, sym->name, 1, match, 0))
			जारी;
		अगर (cnt >= size) अणु
			व्योम *पंचांगp;
			size += 16;
			पंचांगp = पुनः_स्मृति(sym_match_arr, size * माप(काष्ठा sym_match));
			अगर (!पंचांगp)
				जाओ sym_re_search_मुक्त;
			sym_match_arr = पंचांगp;
		पूर्ण
		sym_calc_value(sym);
		/* As regexec वापसed 0, we know we have a match, so
		 * we can use match[0].rm_[se]o without further checks
		 */
		sym_match_arr[cnt].so = match[0].rm_so;
		sym_match_arr[cnt].eo = match[0].rm_eo;
		sym_match_arr[cnt++].sym = sym;
	पूर्ण
	अगर (sym_match_arr) अणु
		क्विक(sym_match_arr, cnt, माप(काष्ठा sym_match), sym_rel_comp);
		sym_arr = दो_स्मृति((cnt+1) * माप(काष्ठा symbol *));
		अगर (!sym_arr)
			जाओ sym_re_search_मुक्त;
		क्रम (i = 0; i < cnt; i++)
			sym_arr[i] = sym_match_arr[i].sym;
		sym_arr[cnt] = शून्य;
	पूर्ण
sym_re_search_मुक्त:
	/* sym_match_arr can be शून्य अगर no match, but मुक्त(शून्य) is OK */
	मुक्त(sym_match_arr);
	regमुक्त(&re);

	वापस sym_arr;
पूर्ण

/*
 * When we check क्रम recursive dependencies we use a stack to save
 * current state so we can prपूर्णांक out relevant info to user.
 * The entries are located on the call stack so no need to मुक्त memory.
 * Note insert() हटाओ() must always match to properly clear the stack.
 */
अटल काष्ठा dep_stack अणु
	काष्ठा dep_stack *prev, *next;
	काष्ठा symbol *sym;
	काष्ठा property *prop;
	काष्ठा expr **expr;
पूर्ण *check_top;

अटल व्योम dep_stack_insert(काष्ठा dep_stack *stack, काष्ठा symbol *sym)
अणु
	स_रखो(stack, 0, माप(*stack));
	अगर (check_top)
		check_top->next = stack;
	stack->prev = check_top;
	stack->sym = sym;
	check_top = stack;
पूर्ण

अटल व्योम dep_stack_हटाओ(व्योम)
अणु
	check_top = check_top->prev;
	अगर (check_top)
		check_top->next = शून्य;
पूर्ण

/*
 * Called when we have detected a recursive dependency.
 * check_top poपूर्णांक to the top of the stact so we use
 * the ->prev poपूर्णांकer to locate the bottom of the stack.
 */
अटल व्योम sym_check_prपूर्णांक_recursive(काष्ठा symbol *last_sym)
अणु
	काष्ठा dep_stack *stack;
	काष्ठा symbol *sym, *next_sym;
	काष्ठा menu *menu = शून्य;
	काष्ठा property *prop;
	काष्ठा dep_stack cv_stack;

	अगर (sym_is_choice_value(last_sym)) अणु
		dep_stack_insert(&cv_stack, last_sym);
		last_sym = prop_get_symbol(sym_get_choice_prop(last_sym));
	पूर्ण

	क्रम (stack = check_top; stack != शून्य; stack = stack->prev)
		अगर (stack->sym == last_sym)
			अवरोध;
	अगर (!stack) अणु
		ख_लिखो(मानक_त्रुटि, "unexpected recursive dependency error\n");
		वापस;
	पूर्ण

	क्रम (; stack; stack = stack->next) अणु
		sym = stack->sym;
		next_sym = stack->next ? stack->next->sym : last_sym;
		prop = stack->prop;
		अगर (prop == शून्य)
			prop = stack->sym->prop;

		/* क्रम choice values find the menu entry (used below) */
		अगर (sym_is_choice(sym) || sym_is_choice_value(sym)) अणु
			क्रम (prop = sym->prop; prop; prop = prop->next) अणु
				menu = prop->menu;
				अगर (prop->menu)
					अवरोध;
			पूर्ण
		पूर्ण
		अगर (stack->sym == last_sym)
			ख_लिखो(मानक_त्रुटि, "%s:%d:error: recursive dependency detected!\n",
				prop->file->name, prop->lineno);

		अगर (sym_is_choice(sym)) अणु
			ख_लिखो(मानक_त्रुटि, "%s:%d:\tchoice %s contains symbol %s\n",
				menu->file->name, menu->lineno,
				sym->name ? sym->name : "<choice>",
				next_sym->name ? next_sym->name : "<choice>");
		पूर्ण अन्यथा अगर (sym_is_choice_value(sym)) अणु
			ख_लिखो(मानक_त्रुटि, "%s:%d:\tsymbol %s is part of choice %s\n",
				menu->file->name, menu->lineno,
				sym->name ? sym->name : "<choice>",
				next_sym->name ? next_sym->name : "<choice>");
		पूर्ण अन्यथा अगर (stack->expr == &sym->dir_dep.expr) अणु
			ख_लिखो(मानक_त्रुटि, "%s:%d:\tsymbol %s depends on %s\n",
				prop->file->name, prop->lineno,
				sym->name ? sym->name : "<choice>",
				next_sym->name ? next_sym->name : "<choice>");
		पूर्ण अन्यथा अगर (stack->expr == &sym->rev_dep.expr) अणु
			ख_लिखो(मानक_त्रुटि, "%s:%d:\tsymbol %s is selected by %s\n",
				prop->file->name, prop->lineno,
				sym->name ? sym->name : "<choice>",
				next_sym->name ? next_sym->name : "<choice>");
		पूर्ण अन्यथा अगर (stack->expr == &sym->implied.expr) अणु
			ख_लिखो(मानक_त्रुटि, "%s:%d:\tsymbol %s is implied by %s\n",
				prop->file->name, prop->lineno,
				sym->name ? sym->name : "<choice>",
				next_sym->name ? next_sym->name : "<choice>");
		पूर्ण अन्यथा अगर (stack->expr) अणु
			ख_लिखो(मानक_त्रुटि, "%s:%d:\tsymbol %s %s value contains %s\n",
				prop->file->name, prop->lineno,
				sym->name ? sym->name : "<choice>",
				prop_get_type_name(prop->type),
				next_sym->name ? next_sym->name : "<choice>");
		पूर्ण अन्यथा अणु
			ख_लिखो(मानक_त्रुटि, "%s:%d:\tsymbol %s %s is visible depending on %s\n",
				prop->file->name, prop->lineno,
				sym->name ? sym->name : "<choice>",
				prop_get_type_name(prop->type),
				next_sym->name ? next_sym->name : "<choice>");
		पूर्ण
	पूर्ण

	ख_लिखो(मानक_त्रुटि,
		"For a resolution refer to Documentation/kbuild/kconfig-language.rst\n"
		"subsection \"Kconfig recursive dependency limitations\"\n"
		"\n");

	अगर (check_top == &cv_stack)
		dep_stack_हटाओ();
पूर्ण

अटल काष्ठा symbol *sym_check_expr_deps(काष्ठा expr *e)
अणु
	काष्ठा symbol *sym;

	अगर (!e)
		वापस शून्य;
	चयन (e->type) अणु
	हाल E_OR:
	हाल E_AND:
		sym = sym_check_expr_deps(e->left.expr);
		अगर (sym)
			वापस sym;
		वापस sym_check_expr_deps(e->right.expr);
	हाल E_NOT:
		वापस sym_check_expr_deps(e->left.expr);
	हाल E_EQUAL:
	हाल E_GEQ:
	हाल E_GTH:
	हाल E_LEQ:
	हाल E_LTH:
	हाल E_UNEQUAL:
		sym = sym_check_deps(e->left.sym);
		अगर (sym)
			वापस sym;
		वापस sym_check_deps(e->right.sym);
	हाल E_SYMBOL:
		वापस sym_check_deps(e->left.sym);
	शेष:
		अवरोध;
	पूर्ण
	ख_लिखो(मानक_त्रुटि, "Oops! How to check %d?\n", e->type);
	वापस शून्य;
पूर्ण

/* वापस शून्य when dependencies are OK */
अटल काष्ठा symbol *sym_check_sym_deps(काष्ठा symbol *sym)
अणु
	काष्ठा symbol *sym2;
	काष्ठा property *prop;
	काष्ठा dep_stack stack;

	dep_stack_insert(&stack, sym);

	stack.expr = &sym->dir_dep.expr;
	sym2 = sym_check_expr_deps(sym->dir_dep.expr);
	अगर (sym2)
		जाओ out;

	stack.expr = &sym->rev_dep.expr;
	sym2 = sym_check_expr_deps(sym->rev_dep.expr);
	अगर (sym2)
		जाओ out;

	stack.expr = &sym->implied.expr;
	sym2 = sym_check_expr_deps(sym->implied.expr);
	अगर (sym2)
		जाओ out;

	stack.expr = शून्य;

	क्रम (prop = sym->prop; prop; prop = prop->next) अणु
		अगर (prop->type == P_CHOICE || prop->type == P_SELECT ||
		    prop->type == P_IMPLY)
			जारी;
		stack.prop = prop;
		sym2 = sym_check_expr_deps(prop->visible.expr);
		अगर (sym2)
			अवरोध;
		अगर (prop->type != P_DEFAULT || sym_is_choice(sym))
			जारी;
		stack.expr = &prop->expr;
		sym2 = sym_check_expr_deps(prop->expr);
		अगर (sym2)
			अवरोध;
		stack.expr = शून्य;
	पूर्ण

out:
	dep_stack_हटाओ();

	वापस sym2;
पूर्ण

अटल काष्ठा symbol *sym_check_choice_deps(काष्ठा symbol *choice)
अणु
	काष्ठा symbol *sym, *sym2;
	काष्ठा property *prop;
	काष्ठा expr *e;
	काष्ठा dep_stack stack;

	dep_stack_insert(&stack, choice);

	prop = sym_get_choice_prop(choice);
	expr_list_क्रम_each_sym(prop->expr, e, sym)
		sym->flags |= (SYMBOL_CHECK | SYMBOL_CHECKED);

	choice->flags |= (SYMBOL_CHECK | SYMBOL_CHECKED);
	sym2 = sym_check_sym_deps(choice);
	choice->flags &= ~SYMBOL_CHECK;
	अगर (sym2)
		जाओ out;

	expr_list_क्रम_each_sym(prop->expr, e, sym) अणु
		sym2 = sym_check_sym_deps(sym);
		अगर (sym2)
			अवरोध;
	पूर्ण
out:
	expr_list_क्रम_each_sym(prop->expr, e, sym)
		sym->flags &= ~SYMBOL_CHECK;

	अगर (sym2 && sym_is_choice_value(sym2) &&
	    prop_get_symbol(sym_get_choice_prop(sym2)) == choice)
		sym2 = choice;

	dep_stack_हटाओ();

	वापस sym2;
पूर्ण

काष्ठा symbol *sym_check_deps(काष्ठा symbol *sym)
अणु
	काष्ठा symbol *sym2;
	काष्ठा property *prop;

	अगर (sym->flags & SYMBOL_CHECK) अणु
		sym_check_prपूर्णांक_recursive(sym);
		वापस sym;
	पूर्ण
	अगर (sym->flags & SYMBOL_CHECKED)
		वापस शून्य;

	अगर (sym_is_choice_value(sym)) अणु
		काष्ठा dep_stack stack;

		/* क्रम choice groups start the check with मुख्य choice symbol */
		dep_stack_insert(&stack, sym);
		prop = sym_get_choice_prop(sym);
		sym2 = sym_check_deps(prop_get_symbol(prop));
		dep_stack_हटाओ();
	पूर्ण अन्यथा अगर (sym_is_choice(sym)) अणु
		sym2 = sym_check_choice_deps(sym);
	पूर्ण अन्यथा अणु
		sym->flags |= (SYMBOL_CHECK | SYMBOL_CHECKED);
		sym2 = sym_check_sym_deps(sym);
		sym->flags &= ~SYMBOL_CHECK;
	पूर्ण

	वापस sym2;
पूर्ण

काष्ठा symbol *prop_get_symbol(काष्ठा property *prop)
अणु
	अगर (prop->expr && (prop->expr->type == E_SYMBOL ||
			   prop->expr->type == E_LIST))
		वापस prop->expr->left.sym;
	वापस शून्य;
पूर्ण

स्थिर अक्षर *prop_get_type_name(क्रमागत prop_type type)
अणु
	चयन (type) अणु
	हाल P_PROMPT:
		वापस "prompt";
	हाल P_COMMENT:
		वापस "comment";
	हाल P_MENU:
		वापस "menu";
	हाल P_DEFAULT:
		वापस "default";
	हाल P_CHOICE:
		वापस "choice";
	हाल P_SELECT:
		वापस "select";
	हाल P_IMPLY:
		वापस "imply";
	हाल P_RANGE:
		वापस "range";
	हाल P_SYMBOL:
		वापस "symbol";
	हाल P_UNKNOWN:
		अवरोध;
	पूर्ण
	वापस "unknown";
पूर्ण
