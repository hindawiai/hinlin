<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2002 Roman Zippel <zippel@linux-m68k.org>
 */

#समावेश <प्रकार.स>
#समावेश <मानकतर्क.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>

#समावेश "lkc.h"
#समावेश "internal.h"

अटल स्थिर अक्षर nohelp_text[] = "There is no help available for this option.";

काष्ठा menu rooपंचांगenu;
अटल काष्ठा menu **last_entry_ptr;

काष्ठा file *file_list;
काष्ठा file *current_file;

व्योम menu_warn(काष्ठा menu *menu, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;
	बहु_शुरू(ap, fmt);
	ख_लिखो(मानक_त्रुटि, "%s:%d:warning: ", menu->file->name, menu->lineno);
	भख_लिखो(मानक_त्रुटि, fmt, ap);
	ख_लिखो(मानक_त्रुटि, "\n");
	बहु_पूर्ण(ap);
पूर्ण

अटल व्योम prop_warn(काष्ठा property *prop, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;
	बहु_शुरू(ap, fmt);
	ख_लिखो(मानक_त्रुटि, "%s:%d:warning: ", prop->file->name, prop->lineno);
	भख_लिखो(मानक_त्रुटि, fmt, ap);
	ख_लिखो(मानक_त्रुटि, "\n");
	बहु_पूर्ण(ap);
पूर्ण

व्योम _menu_init(व्योम)
अणु
	current_entry = current_menu = &rooपंचांगenu;
	last_entry_ptr = &rooपंचांगenu.list;
पूर्ण

व्योम menu_add_entry(काष्ठा symbol *sym)
अणु
	काष्ठा menu *menu;

	menu = xदो_स्मृति(माप(*menu));
	स_रखो(menu, 0, माप(*menu));
	menu->sym = sym;
	menu->parent = current_menu;
	menu->file = current_file;
	menu->lineno = zconf_lineno();

	*last_entry_ptr = menu;
	last_entry_ptr = &menu->next;
	current_entry = menu;
	अगर (sym)
		menu_add_symbol(P_SYMBOL, sym, शून्य);
पूर्ण

काष्ठा menu *menu_add_menu(व्योम)
अणु
	last_entry_ptr = &current_entry->list;
	current_menu = current_entry;
	वापस current_menu;
पूर्ण

व्योम menu_end_menu(व्योम)
अणु
	last_entry_ptr = &current_menu->next;
	current_menu = current_menu->parent;
पूर्ण

/*
 * Reग_लिखोs 'm' to 'm' && MODULES, so that it evaluates to 'n' when running
 * without modules
 */
अटल काष्ठा expr *reग_लिखो_m(काष्ठा expr *e)
अणु
	अगर (!e)
		वापस e;

	चयन (e->type) अणु
	हाल E_NOT:
		e->left.expr = reग_लिखो_m(e->left.expr);
		अवरोध;
	हाल E_OR:
	हाल E_AND:
		e->left.expr = reग_लिखो_m(e->left.expr);
		e->right.expr = reग_लिखो_m(e->right.expr);
		अवरोध;
	हाल E_SYMBOL:
		/* change 'm' into 'm' && MODULES */
		अगर (e->left.sym == &symbol_mod)
			वापस expr_alloc_and(e, expr_alloc_symbol(modules_sym));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस e;
पूर्ण

व्योम menu_add_dep(काष्ठा expr *dep)
अणु
	current_entry->dep = expr_alloc_and(current_entry->dep, dep);
पूर्ण

व्योम menu_set_type(पूर्णांक type)
अणु
	काष्ठा symbol *sym = current_entry->sym;

	अगर (sym->type == type)
		वापस;
	अगर (sym->type == S_UNKNOWN) अणु
		sym->type = type;
		वापस;
	पूर्ण
	menu_warn(current_entry,
		"ignoring type redefinition of '%s' from '%s' to '%s'",
		sym->name ? sym->name : "<choice>",
		sym_type_name(sym->type), sym_type_name(type));
पूर्ण

अटल काष्ठा property *menu_add_prop(क्रमागत prop_type type, काष्ठा expr *expr,
				      काष्ठा expr *dep)
अणु
	काष्ठा property *prop;

	prop = xदो_स्मृति(माप(*prop));
	स_रखो(prop, 0, माप(*prop));
	prop->type = type;
	prop->file = current_file;
	prop->lineno = zconf_lineno();
	prop->menu = current_entry;
	prop->expr = expr;
	prop->visible.expr = dep;

	/* append property to the prop list of symbol */
	अगर (current_entry->sym) अणु
		काष्ठा property **propp;

		क्रम (propp = &current_entry->sym->prop;
		     *propp;
		     propp = &(*propp)->next)
			;
		*propp = prop;
	पूर्ण

	वापस prop;
पूर्ण

काष्ठा property *menu_add_prompt(क्रमागत prop_type type, अक्षर *prompt,
				 काष्ठा expr *dep)
अणु
	काष्ठा property *prop = menu_add_prop(type, शून्य, dep);

	अगर (है_खाली(*prompt)) अणु
		prop_warn(prop, "leading whitespace ignored");
		जबतक (है_खाली(*prompt))
			prompt++;
	पूर्ण
	अगर (current_entry->prompt)
		prop_warn(prop, "prompt redefined");

	/* Apply all upper menus' visibilities to actual prompts. */
	अगर (type == P_PROMPT) अणु
		काष्ठा menu *menu = current_entry;

		जबतक ((menu = menu->parent) != शून्य) अणु
			काष्ठा expr *dup_expr;

			अगर (!menu->visibility)
				जारी;
			/*
			 * Do not add a reference to the menu's visibility
			 * expression but use a copy of it. Otherwise the
			 * expression reduction functions will modअगरy
			 * expressions that have multiple references which
			 * can cause unwanted side effects.
			 */
			dup_expr = expr_copy(menu->visibility);

			prop->visible.expr = expr_alloc_and(prop->visible.expr,
							    dup_expr);
		पूर्ण
	पूर्ण

	current_entry->prompt = prop;
	prop->text = prompt;

	वापस prop;
पूर्ण

व्योम menu_add_visibility(काष्ठा expr *expr)
अणु
	current_entry->visibility = expr_alloc_and(current_entry->visibility,
	    expr);
पूर्ण

व्योम menu_add_expr(क्रमागत prop_type type, काष्ठा expr *expr, काष्ठा expr *dep)
अणु
	menu_add_prop(type, expr, dep);
पूर्ण

व्योम menu_add_symbol(क्रमागत prop_type type, काष्ठा symbol *sym, काष्ठा expr *dep)
अणु
	menu_add_prop(type, expr_alloc_symbol(sym), dep);
पूर्ण

अटल पूर्णांक menu_validate_number(काष्ठा symbol *sym, काष्ठा symbol *sym2)
अणु
	वापस sym2->type == S_INT || sym2->type == S_HEX ||
	       (sym2->type == S_UNKNOWN && sym_string_valid(sym, sym2->name));
पूर्ण

अटल व्योम sym_check_prop(काष्ठा symbol *sym)
अणु
	काष्ठा property *prop;
	काष्ठा symbol *sym2;
	अक्षर *use;

	क्रम (prop = sym->prop; prop; prop = prop->next) अणु
		चयन (prop->type) अणु
		हाल P_DEFAULT:
			अगर ((sym->type == S_STRING || sym->type == S_INT || sym->type == S_HEX) &&
			    prop->expr->type != E_SYMBOL)
				prop_warn(prop,
				    "default for config symbol '%s'"
				    " must be a single symbol", sym->name);
			अगर (prop->expr->type != E_SYMBOL)
				अवरोध;
			sym2 = prop_get_symbol(prop);
			अगर (sym->type == S_HEX || sym->type == S_INT) अणु
				अगर (!menu_validate_number(sym, sym2))
					prop_warn(prop,
					    "'%s': number is invalid",
					    sym->name);
			पूर्ण
			अगर (sym_is_choice(sym)) अणु
				काष्ठा property *choice_prop =
					sym_get_choice_prop(sym2);

				अगर (!choice_prop ||
				    prop_get_symbol(choice_prop) != sym)
					prop_warn(prop,
						  "choice default symbol '%s' is not contained in the choice",
						  sym2->name);
			पूर्ण
			अवरोध;
		हाल P_SELECT:
		हाल P_IMPLY:
			use = prop->type == P_SELECT ? "select" : "imply";
			sym2 = prop_get_symbol(prop);
			अगर (sym->type != S_BOOLEAN && sym->type != S_TRISTATE)
				prop_warn(prop,
				    "config symbol '%s' uses %s, but is "
				    "not bool or tristate", sym->name, use);
			अन्यथा अगर (sym2->type != S_UNKNOWN &&
				 sym2->type != S_BOOLEAN &&
				 sym2->type != S_TRISTATE)
				prop_warn(prop,
				    "'%s' has wrong type. '%s' only "
				    "accept arguments of bool and "
				    "tristate type", sym2->name, use);
			अवरोध;
		हाल P_RANGE:
			अगर (sym->type != S_INT && sym->type != S_HEX)
				prop_warn(prop, "range is only allowed "
						"for int or hex symbols");
			अगर (!menu_validate_number(sym, prop->expr->left.sym) ||
			    !menu_validate_number(sym, prop->expr->right.sym))
				prop_warn(prop, "range is invalid");
			अवरोध;
		शेष:
			;
		पूर्ण
	पूर्ण
पूर्ण

व्योम menu_finalize(काष्ठा menu *parent)
अणु
	काष्ठा menu *menu, *last_menu;
	काष्ठा symbol *sym;
	काष्ठा property *prop;
	काष्ठा expr *parentdep, *basedep, *dep, *dep2, **ep;

	sym = parent->sym;
	अगर (parent->list) अणु
		/*
		 * This menu node has children. We (recursively) process them
		 * and propagate parent dependencies beक्रमe moving on.
		 */

		अगर (sym && sym_is_choice(sym)) अणु
			अगर (sym->type == S_UNKNOWN) अणु
				/* find the first choice value to find out choice type */
				current_entry = parent;
				क्रम (menu = parent->list; menu; menu = menu->next) अणु
					अगर (menu->sym && menu->sym->type != S_UNKNOWN) अणु
						menu_set_type(menu->sym->type);
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
			/* set the type of the reमुख्यing choice values */
			क्रम (menu = parent->list; menu; menu = menu->next) अणु
				current_entry = menu;
				अगर (menu->sym && menu->sym->type == S_UNKNOWN)
					menu_set_type(sym->type);
			पूर्ण

			/*
			 * Use the choice itself as the parent dependency of
			 * the contained items. This turns the mode of the
			 * choice पूर्णांकo an upper bound on the visibility of the
			 * choice value symbols.
			 */
			parentdep = expr_alloc_symbol(sym);
		पूर्ण अन्यथा अणु
			/* Menu node क्रम 'menu', 'if' */
			parentdep = parent->dep;
		पूर्ण

		/* For each child menu node... */
		क्रम (menu = parent->list; menu; menu = menu->next) अणु
			/*
			 * Propagate parent dependencies to the child menu
			 * node, also rewriting and simplअगरying expressions
			 */
			basedep = reग_लिखो_m(menu->dep);
			basedep = expr_transक्रमm(basedep);
			basedep = expr_alloc_and(expr_copy(parentdep), basedep);
			basedep = expr_eliminate_dups(basedep);
			menu->dep = basedep;

			अगर (menu->sym)
				/*
				 * Note: For symbols, all prompts are included
				 * too in the symbol's own property list
				 */
				prop = menu->sym->prop;
			अन्यथा
				/*
				 * For non-symbol menu nodes, we just need to
				 * handle the prompt
				 */
				prop = menu->prompt;

			/* For each property... */
			क्रम (; prop; prop = prop->next) अणु
				अगर (prop->menu != menu)
					/*
					 * Two possibilities:
					 *
					 * 1. The property lacks dependencies
					 *    and so isn't location-specअगरic,
					 *    e.g. an 'option'
					 *
					 * 2. The property beदीर्घs to a symbol
					 *    defined in multiple locations and
					 *    is from some other location. It
					 *    will be handled there in that
					 *    हाल.
					 *
					 * Skip the property.
					 */
					जारी;

				/*
				 * Propagate parent dependencies to the
				 * property's condition, rewriting and
				 * simplअगरying expressions at the same समय
				 */
				dep = reग_लिखो_m(prop->visible.expr);
				dep = expr_transक्रमm(dep);
				dep = expr_alloc_and(expr_copy(basedep), dep);
				dep = expr_eliminate_dups(dep);
				अगर (menu->sym && menu->sym->type != S_TRISTATE)
					dep = expr_trans_bool(dep);
				prop->visible.expr = dep;

				/*
				 * Handle selects and implies, which modअगरy the
				 * dependencies of the selected/implied symbol
				 */
				अगर (prop->type == P_SELECT) अणु
					काष्ठा symbol *es = prop_get_symbol(prop);
					es->rev_dep.expr = expr_alloc_or(es->rev_dep.expr,
							expr_alloc_and(expr_alloc_symbol(menu->sym), expr_copy(dep)));
				पूर्ण अन्यथा अगर (prop->type == P_IMPLY) अणु
					काष्ठा symbol *es = prop_get_symbol(prop);
					es->implied.expr = expr_alloc_or(es->implied.expr,
							expr_alloc_and(expr_alloc_symbol(menu->sym), expr_copy(dep)));
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (sym && sym_is_choice(sym))
			expr_मुक्त(parentdep);

		/*
		 * Recursively process children in the same fashion beक्रमe
		 * moving on
		 */
		क्रम (menu = parent->list; menu; menu = menu->next)
			menu_finalize(menu);
	पूर्ण अन्यथा अगर (sym) अणु
		/*
		 * Automatic submenu creation. If sym is a symbol and A, B, C,
		 * ... are consecutive items (symbols, menus, अगरs, etc.) that
		 * all depend on sym, then the following menu काष्ठाure is
		 * created:
		 *
		 *	sym
		 *	 +-A
		 *	 +-B
		 *	 +-C
		 *	 ...
		 *
		 * This also works recursively, giving the following काष्ठाure
		 * अगर A is a symbol and B depends on A:
		 *
		 *	sym
		 *	 +-A
		 *	 | +-B
		 *	 +-C
		 *	 ...
		 */

		basedep = parent->prompt ? parent->prompt->visible.expr : शून्य;
		basedep = expr_trans_compare(basedep, E_UNEQUAL, &symbol_no);
		basedep = expr_eliminate_dups(expr_transक्रमm(basedep));

		/* Examine consecutive elements after sym */
		last_menu = शून्य;
		क्रम (menu = parent->next; menu; menu = menu->next) अणु
			dep = menu->prompt ? menu->prompt->visible.expr : menu->dep;
			अगर (!expr_contains_symbol(dep, sym))
				/* No dependency, quit */
				अवरोध;
			अगर (expr_depends_symbol(dep, sym))
				/* Absolute dependency, put in submenu */
				जाओ next;

			/*
			 * Also consider it a dependency on sym अगर our
			 * dependencies contain sym and are a "superset" of
			 * sym's dependencies, e.g. '(sym || Q) && R' when sym
			 * depends on R.
			 *
			 * Note that 'R' might be from an enclosing menu or अगर,
			 * making this a more common हाल than it might seem.
			 */
			dep = expr_trans_compare(dep, E_UNEQUAL, &symbol_no);
			dep = expr_eliminate_dups(expr_transक्रमm(dep));
			dep2 = expr_copy(basedep);
			expr_eliminate_eq(&dep, &dep2);
			expr_मुक्त(dep);
			अगर (!expr_is_yes(dep2)) अणु
				/* Not superset, quit */
				expr_मुक्त(dep2);
				अवरोध;
			पूर्ण
			/* Superset, put in submenu */
			expr_मुक्त(dep2);
		next:
			menu_finalize(menu);
			menu->parent = parent;
			last_menu = menu;
		पूर्ण
		expr_मुक्त(basedep);
		अगर (last_menu) अणु
			parent->list = parent->next;
			parent->next = last_menu->next;
			last_menu->next = शून्य;
		पूर्ण

		sym->dir_dep.expr = expr_alloc_or(sym->dir_dep.expr, parent->dep);
	पूर्ण
	क्रम (menu = parent->list; menu; menu = menu->next) अणु
		अगर (sym && sym_is_choice(sym) &&
		    menu->sym && !sym_is_choice_value(menu->sym)) अणु
			current_entry = menu;
			menu->sym->flags |= SYMBOL_CHOICEVAL;
			अगर (!menu->prompt)
				menu_warn(menu, "choice value must have a prompt");
			क्रम (prop = menu->sym->prop; prop; prop = prop->next) अणु
				अगर (prop->type == P_DEFAULT)
					prop_warn(prop, "defaults for choice "
						  "values not supported");
				अगर (prop->menu == menu)
					जारी;
				अगर (prop->type == P_PROMPT &&
				    prop->menu->parent->sym != sym)
					prop_warn(prop, "choice value used outside its choice group");
			पूर्ण
			/* Non-tristate choice values of tristate choices must
			 * depend on the choice being set to Y. The choice
			 * values' dependencies were propagated to their
			 * properties above, so the change here must be re-
			 * propagated.
			 */
			अगर (sym->type == S_TRISTATE && menu->sym->type != S_TRISTATE) अणु
				basedep = expr_alloc_comp(E_EQUAL, sym, &symbol_yes);
				menu->dep = expr_alloc_and(basedep, menu->dep);
				क्रम (prop = menu->sym->prop; prop; prop = prop->next) अणु
					अगर (prop->menu != menu)
						जारी;
					prop->visible.expr = expr_alloc_and(expr_copy(basedep),
									    prop->visible.expr);
				पूर्ण
			पूर्ण
			menu_add_symbol(P_CHOICE, sym, शून्य);
			prop = sym_get_choice_prop(sym);
			क्रम (ep = &prop->expr; *ep; ep = &(*ep)->left.expr)
				;
			*ep = expr_alloc_one(E_LIST, शून्य);
			(*ep)->right.sym = menu->sym;
		पूर्ण

		/*
		 * This code serves two purposes:
		 *
		 * (1) Flattening 'if' blocks, which करो not specअगरy a submenu
		 *     and only add dependencies.
		 *
		 *     (Automatic submenu creation might still create a submenu
		 *     from an 'if' beक्रमe this code runs.)
		 *
		 * (2) "Undoing" any स्वतःmatic submenus created earlier below
		 *     promptless symbols.
		 *
		 * Beक्रमe:
		 *
		 *	A
		 *	अगर ... (or promptless symbol)
		 *	 +-B
		 *	 +-C
		 *	D
		 *
		 * After:
		 *
		 *	A
		 *	अगर ... (or promptless symbol)
		 *	B
		 *	C
		 *	D
		 */
		अगर (menu->list && (!menu->prompt || !menu->prompt->text)) अणु
			क्रम (last_menu = menu->list; ; last_menu = last_menu->next) अणु
				last_menu->parent = parent;
				अगर (!last_menu->next)
					अवरोध;
			पूर्ण
			last_menu->next = menu->next;
			menu->next = menu->list;
			menu->list = शून्य;
		पूर्ण
	पूर्ण

	अगर (sym && !(sym->flags & SYMBOL_WARNED)) अणु
		अगर (sym->type == S_UNKNOWN)
			menu_warn(parent, "config symbol defined without type");

		अगर (sym_is_choice(sym) && !parent->prompt)
			menu_warn(parent, "choice must have a prompt");

		/* Check properties connected to this symbol */
		sym_check_prop(sym);
		sym->flags |= SYMBOL_WARNED;
	पूर्ण

	/*
	 * For non-optional choices, add a reverse dependency (corresponding to
	 * a select) of '<visibility> && m'. This prevents the user from
	 * setting the choice mode to 'n' when the choice is visible.
	 *
	 * This would also work क्रम non-choice symbols, but only non-optional
	 * choices clear SYMBOL_OPTIONAL as of writing. Choices are implemented
	 * as a type of symbol.
	 */
	अगर (sym && !sym_is_optional(sym) && parent->prompt) अणु
		sym->rev_dep.expr = expr_alloc_or(sym->rev_dep.expr,
				expr_alloc_and(parent->prompt->visible.expr,
					expr_alloc_symbol(&symbol_mod)));
	पूर्ण
पूर्ण

bool menu_has_prompt(काष्ठा menu *menu)
अणु
	अगर (!menu->prompt)
		वापस false;
	वापस true;
पूर्ण

/*
 * Determine अगर a menu is empty.
 * A menu is considered empty अगर it contains no or only
 * invisible entries.
 */
bool menu_is_empty(काष्ठा menu *menu)
अणु
	काष्ठा menu *child;

	क्रम (child = menu->list; child; child = child->next) अणु
		अगर (menu_is_visible(child))
			वापस(false);
	पूर्ण
	वापस(true);
पूर्ण

bool menu_is_visible(काष्ठा menu *menu)
अणु
	काष्ठा menu *child;
	काष्ठा symbol *sym;
	tristate visible;

	अगर (!menu->prompt)
		वापस false;

	अगर (menu->visibility) अणु
		अगर (expr_calc_value(menu->visibility) == no)
			वापस false;
	पूर्ण

	sym = menu->sym;
	अगर (sym) अणु
		sym_calc_value(sym);
		visible = menu->prompt->visible.tri;
	पूर्ण अन्यथा
		visible = menu->prompt->visible.tri = expr_calc_value(menu->prompt->visible.expr);

	अगर (visible != no)
		वापस true;

	अगर (!sym || sym_get_tristate_value(menu->sym) == no)
		वापस false;

	क्रम (child = menu->list; child; child = child->next) अणु
		अगर (menu_is_visible(child)) अणु
			अगर (sym)
				sym->flags |= SYMBOL_DEF_USER;
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

स्थिर अक्षर *menu_get_prompt(काष्ठा menu *menu)
अणु
	अगर (menu->prompt)
		वापस menu->prompt->text;
	अन्यथा अगर (menu->sym)
		वापस menu->sym->name;
	वापस शून्य;
पूर्ण

काष्ठा menu *menu_get_root_menu(काष्ठा menu *menu)
अणु
	वापस &rooपंचांगenu;
पूर्ण

काष्ठा menu *menu_get_parent_menu(काष्ठा menu *menu)
अणु
	क्रमागत prop_type type;

	क्रम (; menu != &rooपंचांगenu; menu = menu->parent) अणु
		type = menu->prompt ? menu->prompt->type : 0;
		अगर (type == P_MENU)
			अवरोध;
	पूर्ण
	वापस menu;
पूर्ण

bool menu_has_help(काष्ठा menu *menu)
अणु
	वापस menu->help != शून्य;
पूर्ण

स्थिर अक्षर *menu_get_help(काष्ठा menu *menu)
अणु
	अगर (menu->help)
		वापस menu->help;
	अन्यथा
		वापस "";
पूर्ण

अटल व्योम get_def_str(काष्ठा gstr *r, काष्ठा menu *menu)
अणु
	str_म_लिखो(r, "Defined at %s:%d\n",
		   menu->file->name, menu->lineno);
पूर्ण

अटल व्योम get_dep_str(काष्ठा gstr *r, काष्ठा expr *expr, स्थिर अक्षर *prefix)
अणु
	अगर (!expr_is_yes(expr)) अणु
		str_append(r, prefix);
		expr_gstr_prपूर्णांक(expr, r);
		str_append(r, "\n");
	पूर्ण
पूर्ण

अटल व्योम get_prompt_str(काष्ठा gstr *r, काष्ठा property *prop,
			   काष्ठा list_head *head)
अणु
	पूर्णांक i, j;
	काष्ठा menu *submenu[8], *menu, *location = शून्य;
	काष्ठा jump_key *jump = शून्य;

	str_म_लिखो(r, "  Prompt: %s\n", prop->text);

	get_dep_str(r, prop->menu->dep, "  Depends on: ");
	/*
	 * Most prompts in Linux have visibility that exactly matches their
	 * dependencies. For these, we prपूर्णांक only the dependencies to improve
	 * पढ़ोability. However, prompts with अंतरभूत "if" expressions and
	 * prompts with a parent that has a "visible if" expression have
	 * dअगरfering dependencies and visibility. In these rare हालs, we
	 * prपूर्णांक both.
	 */
	अगर (!expr_eq(prop->menu->dep, prop->visible.expr))
		get_dep_str(r, prop->visible.expr, "  Visible if: ");

	menu = prop->menu->parent;
	क्रम (i = 0; menu != &rooपंचांगenu && i < 8; menu = menu->parent) अणु
		bool accessible = menu_is_visible(menu);

		submenu[i++] = menu;
		अगर (location == शून्य && accessible)
			location = menu;
	पूर्ण
	अगर (head && location) अणु
		jump = xदो_स्मृति(माप(काष्ठा jump_key));

		अगर (menu_is_visible(prop->menu)) अणु
			/*
			 * There is not enough room to put the hपूर्णांक at the
			 * beginning of the "Prompt" line. Put the hपूर्णांक on the
			 * last "Location" line even when it would beदीर्घ on
			 * the क्रमmer.
			 */
			jump->target = prop->menu;
		पूर्ण अन्यथा
			jump->target = location;

		अगर (list_empty(head))
			jump->index = 0;
		अन्यथा
			jump->index = list_entry(head->prev, काष्ठा jump_key,
						 entries)->index + 1;

		list_add_tail(&jump->entries, head);
	पूर्ण

	अगर (i > 0) अणु
		str_म_लिखो(r, "  Location:\n");
		क्रम (j = 4; --i >= 0; j += 2) अणु
			menu = submenu[i];
			अगर (jump && menu == location)
				jump->offset = म_माप(r->s);
			str_म_लिखो(r, "%*c-> %s", j, ' ',
				   menu_get_prompt(menu));
			अगर (menu->sym) अणु
				str_म_लिखो(r, " (%s [=%s])", menu->sym->name ?
					menu->sym->name : "<choice>",
					sym_get_string_value(menu->sym));
			पूर्ण
			str_append(r, "\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम get_symbol_props_str(काष्ठा gstr *r, काष्ठा symbol *sym,
				 क्रमागत prop_type tok, स्थिर अक्षर *prefix)
अणु
	bool hit = false;
	काष्ठा property *prop;

	क्रम_all_properties(sym, prop, tok) अणु
		अगर (!hit) अणु
			str_append(r, prefix);
			hit = true;
		पूर्ण अन्यथा
			str_म_लिखो(r, " && ");
		expr_gstr_prपूर्णांक(prop->expr, r);
	पूर्ण
	अगर (hit)
		str_append(r, "\n");
पूर्ण

/*
 * head is optional and may be शून्य
 */
अटल व्योम get_symbol_str(काष्ठा gstr *r, काष्ठा symbol *sym,
		    काष्ठा list_head *head)
अणु
	काष्ठा property *prop;

	अगर (sym && sym->name) अणु
		str_म_लिखो(r, "Symbol: %s [=%s]\n", sym->name,
			   sym_get_string_value(sym));
		str_म_लिखो(r, "Type  : %s\n", sym_type_name(sym->type));
		अगर (sym->type == S_INT || sym->type == S_HEX) अणु
			prop = sym_get_range_prop(sym);
			अगर (prop) अणु
				str_म_लिखो(r, "Range : ");
				expr_gstr_prपूर्णांक(prop->expr, r);
				str_append(r, "\n");
			पूर्ण
		पूर्ण
	पूर्ण

	/* Prपूर्णांक the definitions with prompts beक्रमe the ones without */
	क्रम_all_properties(sym, prop, P_SYMBOL) अणु
		अगर (prop->menu->prompt) अणु
			get_def_str(r, prop->menu);
			get_prompt_str(r, prop->menu->prompt, head);
		पूर्ण
	पूर्ण

	क्रम_all_properties(sym, prop, P_SYMBOL) अणु
		अगर (!prop->menu->prompt) अणु
			get_def_str(r, prop->menu);
			get_dep_str(r, prop->menu->dep, "  Depends on: ");
		पूर्ण
	पूर्ण

	get_symbol_props_str(r, sym, P_SELECT, "Selects: ");
	अगर (sym->rev_dep.expr) अणु
		expr_gstr_prपूर्णांक_revdep(sym->rev_dep.expr, r, yes, "Selected by [y]:\n");
		expr_gstr_prपूर्णांक_revdep(sym->rev_dep.expr, r, mod, "Selected by [m]:\n");
		expr_gstr_prपूर्णांक_revdep(sym->rev_dep.expr, r, no, "Selected by [n]:\n");
	पूर्ण

	get_symbol_props_str(r, sym, P_IMPLY, "Implies: ");
	अगर (sym->implied.expr) अणु
		expr_gstr_prपूर्णांक_revdep(sym->implied.expr, r, yes, "Implied by [y]:\n");
		expr_gstr_prपूर्णांक_revdep(sym->implied.expr, r, mod, "Implied by [m]:\n");
		expr_gstr_prपूर्णांक_revdep(sym->implied.expr, r, no, "Implied by [n]:\n");
	पूर्ण

	str_append(r, "\n\n");
पूर्ण

काष्ठा gstr get_relations_str(काष्ठा symbol **sym_arr, काष्ठा list_head *head)
अणु
	काष्ठा symbol *sym;
	काष्ठा gstr res = str_new();
	पूर्णांक i;

	क्रम (i = 0; sym_arr && (sym = sym_arr[i]); i++)
		get_symbol_str(&res, sym, head);
	अगर (!i)
		str_append(&res, "No matches found.\n");
	वापस res;
पूर्ण


व्योम menu_get_ext_help(काष्ठा menu *menu, काष्ठा gstr *help)
अणु
	काष्ठा symbol *sym = menu->sym;
	स्थिर अक्षर *help_text = nohelp_text;

	अगर (menu_has_help(menu)) अणु
		अगर (sym->name)
			str_म_लिखो(help, "%s%s:\n\n", CONFIG_, sym->name);
		help_text = menu_get_help(menu);
	पूर्ण
	str_म_लिखो(help, "%s\n", help_text);
	अगर (sym)
		get_symbol_str(help, sym, शून्य);
पूर्ण
