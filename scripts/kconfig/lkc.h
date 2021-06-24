<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2002 Roman Zippel <zippel@linux-m68k.org>
 */

#अगर_अघोषित LKC_H
#घोषणा LKC_H

#समावेश <निश्चित.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>

#समावेश "expr.h"

#अगर_घोषित __cplusplus
बाह्य "C" अणु
#पूर्ण_अगर

#समावेश "lkc_proto.h"

#घोषणा SRCTREE "srctree"

#अगर_अघोषित CONFIG_
#घोषणा CONFIG_ "CONFIG_"
#पूर्ण_अगर
अटल अंतरभूत स्थिर अक्षर *CONFIG_prefix(व्योम)
अणु
	वापस दो_पर्या( "CONFIG_" ) ?: CONFIG_;
पूर्ण
#अघोषित CONFIG_
#घोषणा CONFIG_ CONFIG_prefix()

बाह्य पूर्णांक yylineno;
व्योम zconfdump(खाता *out);
व्योम zconf_starthelp(व्योम);
खाता *zconf_ख_खोलो(स्थिर अक्षर *name);
व्योम zconf_initscan(स्थिर अक्षर *name);
व्योम zconf_nextfile(स्थिर अक्षर *name);
पूर्णांक zconf_lineno(व्योम);
स्थिर अक्षर *zconf_curname(व्योम);

/* confdata.c */
स्थिर अक्षर *conf_get_configname(व्योम);
व्योम set_all_choice_values(काष्ठा symbol *csym);

/* confdata.c and expr.c */
अटल अंतरभूत व्योम xख_डालो(स्थिर व्योम *str, माप_प्रकार len, माप_प्रकार count, खाता *out)
अणु
	निश्चित(len != 0);

	अगर (ख_डालो(str, len, count, out) != count)
		ख_लिखो(मानक_त्रुटि, "Error in writing or end of file.\n");
पूर्ण

/* util.c */
काष्ठा file *file_lookup(स्थिर अक्षर *name);
व्योम *xदो_स्मृति(माप_प्रकार size);
व्योम *xसुस्मृति(माप_प्रकार nmemb, माप_प्रकार size);
व्योम *xपुनः_स्मृति(व्योम *p, माप_प्रकार size);
अक्षर *xstrdup(स्थिर अक्षर *s);
अक्षर *xstrndup(स्थिर अक्षर *s, माप_प्रकार n);

/* lexer.l */
पूर्णांक yylex(व्योम);

काष्ठा gstr अणु
	माप_प्रकार len;
	अक्षर  *s;
	/*
	* when max_width is not zero दीर्घ lines in string s (अगर any) get
	* wrapped not to exceed the max_width value
	*/
	पूर्णांक max_width;
पूर्ण;
काष्ठा gstr str_new(व्योम);
व्योम str_मुक्त(काष्ठा gstr *gs);
व्योम str_append(काष्ठा gstr *gs, स्थिर अक्षर *s);
व्योम str_म_लिखो(काष्ठा gstr *gs, स्थिर अक्षर *fmt, ...);
स्थिर अक्षर *str_get(काष्ठा gstr *gs);

/* menu.c */
व्योम _menu_init(व्योम);
व्योम menu_warn(काष्ठा menu *menu, स्थिर अक्षर *fmt, ...);
काष्ठा menu *menu_add_menu(व्योम);
व्योम menu_end_menu(व्योम);
व्योम menu_add_entry(काष्ठा symbol *sym);
व्योम menu_add_dep(काष्ठा expr *dep);
व्योम menu_add_visibility(काष्ठा expr *dep);
काष्ठा property *menu_add_prompt(क्रमागत prop_type type, अक्षर *prompt, काष्ठा expr *dep);
व्योम menu_add_expr(क्रमागत prop_type type, काष्ठा expr *expr, काष्ठा expr *dep);
व्योम menu_add_symbol(क्रमागत prop_type type, काष्ठा symbol *sym, काष्ठा expr *dep);
व्योम menu_finalize(काष्ठा menu *parent);
व्योम menu_set_type(पूर्णांक type);

बाह्य काष्ठा menu rooपंचांगenu;

bool menu_is_empty(काष्ठा menu *menu);
bool menu_is_visible(काष्ठा menu *menu);
bool menu_has_prompt(काष्ठा menu *menu);
स्थिर अक्षर *menu_get_prompt(काष्ठा menu *menu);
काष्ठा menu *menu_get_root_menu(काष्ठा menu *menu);
काष्ठा menu *menu_get_parent_menu(काष्ठा menu *menu);
bool menu_has_help(काष्ठा menu *menu);
स्थिर अक्षर *menu_get_help(काष्ठा menu *menu);
काष्ठा gstr get_relations_str(काष्ठा symbol **sym_arr, काष्ठा list_head *head);
व्योम menu_get_ext_help(काष्ठा menu *menu, काष्ठा gstr *help);

/* symbol.c */
व्योम sym_clear_all_valid(व्योम);
काष्ठा symbol *sym_choice_शेष(काष्ठा symbol *sym);
काष्ठा property *sym_get_range_prop(काष्ठा symbol *sym);
स्थिर अक्षर *sym_get_string_शेष(काष्ठा symbol *sym);
काष्ठा symbol *sym_check_deps(काष्ठा symbol *sym);
काष्ठा symbol *prop_get_symbol(काष्ठा property *prop);

अटल अंतरभूत tristate sym_get_tristate_value(काष्ठा symbol *sym)
अणु
	वापस sym->curr.tri;
पूर्ण


अटल अंतरभूत काष्ठा symbol *sym_get_choice_value(काष्ठा symbol *sym)
अणु
	वापस (काष्ठा symbol *)sym->curr.val;
पूर्ण

अटल अंतरभूत bool sym_set_choice_value(काष्ठा symbol *ch, काष्ठा symbol *chval)
अणु
	वापस sym_set_tristate_value(chval, yes);
पूर्ण

अटल अंतरभूत bool sym_is_choice(काष्ठा symbol *sym)
अणु
	वापस sym->flags & SYMBOL_CHOICE ? true : false;
पूर्ण

अटल अंतरभूत bool sym_is_choice_value(काष्ठा symbol *sym)
अणु
	वापस sym->flags & SYMBOL_CHOICEVAL ? true : false;
पूर्ण

अटल अंतरभूत bool sym_is_optional(काष्ठा symbol *sym)
अणु
	वापस sym->flags & SYMBOL_OPTIONAL ? true : false;
पूर्ण

अटल अंतरभूत bool sym_has_value(काष्ठा symbol *sym)
अणु
	वापस sym->flags & SYMBOL_DEF_USER ? true : false;
पूर्ण

#अगर_घोषित __cplusplus
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* LKC_H */
