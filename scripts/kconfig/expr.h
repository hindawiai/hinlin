<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2002 Roman Zippel <zippel@linux-m68k.org>
 */

#अगर_अघोषित EXPR_H
#घोषणा EXPR_H

#अगर_घोषित __cplusplus
बाह्य "C" अणु
#पूर्ण_अगर

#समावेश <निश्चित.स>
#समावेश <मानकपन.स>
#समावेश "list.h"
#अगर_अघोषित __cplusplus
#समावेश <stdbool.h>
#पूर्ण_अगर

काष्ठा file अणु
	काष्ठा file *next;
	काष्ठा file *parent;
	स्थिर अक्षर *name;
	पूर्णांक lineno;
पूर्ण;

प्रकार क्रमागत tristate अणु
	no, mod, yes
पूर्ण tristate;

क्रमागत expr_type अणु
	E_NONE, E_OR, E_AND, E_NOT,
	E_EQUAL, E_UNEQUAL, E_LTH, E_LEQ, E_GTH, E_GEQ,
	E_LIST, E_SYMBOL, E_RANGE
पूर्ण;

जोड़ expr_data अणु
	काष्ठा expr *expr;
	काष्ठा symbol *sym;
पूर्ण;

काष्ठा expr अणु
	क्रमागत expr_type type;
	जोड़ expr_data left, right;
पूर्ण;

#घोषणा EXPR_OR(dep1, dep2)	(((dep1)>(dep2))?(dep1):(dep2))
#घोषणा EXPR_AND(dep1, dep2)	(((dep1)<(dep2))?(dep1):(dep2))
#घोषणा EXPR_NOT(dep)		(2-(dep))

#घोषणा expr_list_क्रम_each_sym(l, e, s) \
	क्रम (e = (l); e && (s = e->right.sym); e = e->left.expr)

काष्ठा expr_value अणु
	काष्ठा expr *expr;
	tristate tri;
पूर्ण;

काष्ठा symbol_value अणु
	व्योम *val;
	tristate tri;
पूर्ण;

क्रमागत symbol_type अणु
	S_UNKNOWN, S_BOOLEAN, S_TRISTATE, S_INT, S_HEX, S_STRING
पूर्ण;

/* क्रमागत values are used as index to symbol.def[] */
क्रमागत अणु
	S_DEF_USER,		/* मुख्य user value */
	S_DEF_AUTO,		/* values पढ़ो from स्वतः.conf */
	S_DEF_DEF3,		/* Reserved क्रम UI usage */
	S_DEF_DEF4,		/* Reserved क्रम UI usage */
	S_DEF_COUNT
पूर्ण;

/*
 * Represents a configuration symbol.
 *
 * Choices are represented as a special kind of symbol and have the
 * SYMBOL_CHOICE bit set in 'flags'.
 */
काष्ठा symbol अणु
	/* The next symbol in the same bucket in the symbol hash table */
	काष्ठा symbol *next;

	/* The name of the symbol, e.g. "FOO" क्रम 'config FOO' */
	अक्षर *name;

	/* S_BOOLEAN, S_TRISTATE, ... */
	क्रमागत symbol_type type;

	/*
	 * The calculated value of the symbol. The SYMBOL_VALID bit is set in
	 * 'flags' when this is up to date. Note that this value might dअगरfer
	 * from the user value set in e.g. a .config file, due to visibility.
	 */
	काष्ठा symbol_value curr;

	/*
	 * Values क्रम the symbol provided from outside. def[S_DEF_USER] holds
	 * the .config value.
	 */
	काष्ठा symbol_value def[S_DEF_COUNT];

	/*
	 * An upper bound on the tristate value the user can set क्रम the symbol
	 * अगर it is a boolean or tristate. Calculated from prompt dependencies,
	 * which also inherit dependencies from enclosing menus, choices, and
	 * अगरs. If 'n', the user value will be ignored.
	 *
	 * Symbols lacking prompts always have visibility 'n'.
	 */
	tristate visible;

	/* SYMBOL_* flags */
	पूर्णांक flags;

	/* List of properties. See prop_type. */
	काष्ठा property *prop;

	/* Dependencies from enclosing menus, choices, and अगरs */
	काष्ठा expr_value dir_dep;

	/* Reverse dependencies through being selected by other symbols */
	काष्ठा expr_value rev_dep;

	/*
	 * "Weak" reverse dependencies through being implied by other symbols
	 */
	काष्ठा expr_value implied;
पूर्ण;

#घोषणा क्रम_all_symbols(i, sym) क्रम (i = 0; i < SYMBOL_HASHSIZE; i++) क्रम (sym = symbol_hash[i]; sym; sym = sym->next)

#घोषणा SYMBOL_CONST      0x0001  /* symbol is स्थिर */
#घोषणा SYMBOL_CHECK      0x0008  /* used during dependency checking */
#घोषणा SYMBOL_CHOICE     0x0010  /* start of a choice block (null name) */
#घोषणा SYMBOL_CHOICEVAL  0x0020  /* used as a value in a choice block */
#घोषणा SYMBOL_VALID      0x0080  /* set when symbol.curr is calculated */
#घोषणा SYMBOL_OPTIONAL   0x0100  /* choice is optional - values can be 'n' */
#घोषणा SYMBOL_WRITE      0x0200  /* ग_लिखो symbol to file (KCONFIG_CONFIG) */
#घोषणा SYMBOL_CHANGED    0x0400  /* ? */
#घोषणा SYMBOL_WRITTEN    0x0800  /* track info to aव्योम द्विगुन-ग_लिखो to .config */
#घोषणा SYMBOL_NO_WRITE   0x1000  /* Symbol क्रम पूर्णांकernal use only; it will not be written */
#घोषणा SYMBOL_CHECKED    0x2000  /* used during dependency checking */
#घोषणा SYMBOL_WARNED     0x8000  /* warning has been issued */

/* Set when symbol.def[] is used */
#घोषणा SYMBOL_DEF        0x10000  /* First bit of SYMBOL_DEF */
#घोषणा SYMBOL_DEF_USER   0x10000  /* symbol.def[S_DEF_USER] is valid */
#घोषणा SYMBOL_DEF_AUTO   0x20000  /* symbol.def[S_DEF_AUTO] is valid */
#घोषणा SYMBOL_DEF3       0x40000  /* symbol.def[S_DEF_3] is valid */
#घोषणा SYMBOL_DEF4       0x80000  /* symbol.def[S_DEF_4] is valid */

/* choice values need to be set beक्रमe calculating this symbol value */
#घोषणा SYMBOL_NEED_SET_CHOICE_VALUES  0x100000

#घोषणा SYMBOL_MAXLENGTH	256
#घोषणा SYMBOL_HASHSIZE		9973

/* A property represent the config options that can be associated
 * with a config "symbol".
 * Sample:
 * config FOO
 *         शेष y
 *         prompt "foo prompt"
 *         select BAR
 * config BAZ
 *         पूर्णांक "BAZ Value"
 *         range 1..255
 *
 * Please, also check parser.y:prपूर्णांक_symbol() when modअगरying the
 * list of property types!
 */
क्रमागत prop_type अणु
	P_UNKNOWN,
	P_PROMPT,   /* prompt "foo prompt" or "BAZ Value" */
	P_COMMENT,  /* text associated with a comment */
	P_MENU,     /* prompt associated with a menu or menuconfig symbol */
	P_DEFAULT,  /* शेष y */
	P_CHOICE,   /* choice value */
	P_SELECT,   /* select BAR */
	P_IMPLY,    /* imply BAR */
	P_RANGE,    /* range 7..100 (क्रम a symbol) */
	P_SYMBOL,   /* where a symbol is defined */
पूर्ण;

काष्ठा property अणु
	काष्ठा property *next;     /* next property - null अगर last */
	क्रमागत prop_type type;       /* type of property */
	स्थिर अक्षर *text;          /* the prompt value - P_PROMPT, P_MENU, P_COMMENT */
	काष्ठा expr_value visible;
	काष्ठा expr *expr;         /* the optional conditional part of the property */
	काष्ठा menu *menu;         /* the menu the property are associated with
	                            * valid क्रम: P_SELECT, P_RANGE, P_CHOICE,
	                            * P_PROMPT, P_DEFAULT, P_MENU, P_COMMENT */
	काष्ठा file *file;         /* what file was this property defined */
	पूर्णांक lineno;                /* what lineno was this property defined */
पूर्ण;

#घोषणा क्रम_all_properties(sym, st, tok) \
	क्रम (st = sym->prop; st; st = st->next) \
		अगर (st->type == (tok))
#घोषणा क्रम_all_शेषs(sym, st) क्रम_all_properties(sym, st, P_DEFAULT)
#घोषणा क्रम_all_choices(sym, st) क्रम_all_properties(sym, st, P_CHOICE)
#घोषणा क्रम_all_prompts(sym, st) \
	क्रम (st = sym->prop; st; st = st->next) \
		अगर (st->text)

/*
 * Represents a node in the menu tree, as seen in e.g. menuconfig (though used
 * क्रम all front ends). Each symbol, menu, etc. defined in the Kconfig files
 * माला_लो a node. A symbol defined in multiple locations माला_लो one node at each
 * location.
 */
काष्ठा menu अणु
	/* The next menu node at the same level */
	काष्ठा menu *next;

	/* The parent menu node, corresponding to e.g. a menu or choice */
	काष्ठा menu *parent;

	/* The first child menu node, क्रम e.g. menus and choices */
	काष्ठा menu *list;

	/*
	 * The symbol associated with the menu node. Choices are implemented as
	 * a special kind of symbol. शून्य क्रम menus, comments, and अगरs.
	 */
	काष्ठा symbol *sym;

	/*
	 * The prompt associated with the node. This holds the prompt क्रम a
	 * symbol as well as the text क्रम a menu or comment, aदीर्घ with the
	 * type (P_PROMPT, P_MENU, etc.)
	 */
	काष्ठा property *prompt;

	/*
	 * 'visible if' dependencies. If more than one is given, they will be
	 * ANDed together.
	 */
	काष्ठा expr *visibility;

	/*
	 * Ordinary dependencies from e.g. 'depends on' and 'if', ANDed
	 * together
	 */
	काष्ठा expr *dep;

	/* MENU_* flags */
	अचिन्हित पूर्णांक flags;

	/* Any help text associated with the node */
	अक्षर *help;

	/* The location where the menu node appears in the Kconfig files */
	काष्ठा file *file;
	पूर्णांक lineno;

	/* For use by front ends that need to store auxiliary data */
	व्योम *data;
पूर्ण;

/*
 * Set on a menu node when the corresponding symbol changes state in some way.
 * Can be checked by front ends.
 */
#घोषणा MENU_CHANGED		0x0001

#घोषणा MENU_ROOT		0x0002

काष्ठा jump_key अणु
	काष्ठा list_head entries;
	माप_प्रकार offset;
	काष्ठा menu *target;
	पूर्णांक index;
पूर्ण;

बाह्य काष्ठा file *file_list;
बाह्य काष्ठा file *current_file;
काष्ठा file *lookup_file(स्थिर अक्षर *name);

बाह्य काष्ठा symbol symbol_yes, symbol_no, symbol_mod;
बाह्य काष्ठा symbol *modules_sym;
बाह्य पूर्णांक cdebug;
काष्ठा expr *expr_alloc_symbol(काष्ठा symbol *sym);
काष्ठा expr *expr_alloc_one(क्रमागत expr_type type, काष्ठा expr *ce);
काष्ठा expr *expr_alloc_two(क्रमागत expr_type type, काष्ठा expr *e1, काष्ठा expr *e2);
काष्ठा expr *expr_alloc_comp(क्रमागत expr_type type, काष्ठा symbol *s1, काष्ठा symbol *s2);
काष्ठा expr *expr_alloc_and(काष्ठा expr *e1, काष्ठा expr *e2);
काष्ठा expr *expr_alloc_or(काष्ठा expr *e1, काष्ठा expr *e2);
काष्ठा expr *expr_copy(स्थिर काष्ठा expr *org);
व्योम expr_मुक्त(काष्ठा expr *e);
व्योम expr_eliminate_eq(काष्ठा expr **ep1, काष्ठा expr **ep2);
पूर्णांक expr_eq(काष्ठा expr *e1, काष्ठा expr *e2);
tristate expr_calc_value(काष्ठा expr *e);
काष्ठा expr *expr_trans_bool(काष्ठा expr *e);
काष्ठा expr *expr_eliminate_dups(काष्ठा expr *e);
काष्ठा expr *expr_transक्रमm(काष्ठा expr *e);
पूर्णांक expr_contains_symbol(काष्ठा expr *dep, काष्ठा symbol *sym);
bool expr_depends_symbol(काष्ठा expr *dep, काष्ठा symbol *sym);
काष्ठा expr *expr_trans_compare(काष्ठा expr *e, क्रमागत expr_type type, काष्ठा symbol *sym);

व्योम expr_fprपूर्णांक(काष्ठा expr *e, खाता *out);
काष्ठा gstr; /* क्रमward */
व्योम expr_gstr_prपूर्णांक(काष्ठा expr *e, काष्ठा gstr *gs);
व्योम expr_gstr_prपूर्णांक_revdep(काष्ठा expr *e, काष्ठा gstr *gs,
			    tristate pr_type, स्थिर अक्षर *title);

अटल अंतरभूत पूर्णांक expr_is_yes(काष्ठा expr *e)
अणु
	वापस !e || (e->type == E_SYMBOL && e->left.sym == &symbol_yes);
पूर्ण

अटल अंतरभूत पूर्णांक expr_is_no(काष्ठा expr *e)
अणु
	वापस e && (e->type == E_SYMBOL && e->left.sym == &symbol_no);
पूर्ण

#अगर_घोषित __cplusplus
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* EXPR_H */
