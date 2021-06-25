<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <मानकतर्क.स>

/* confdata.c */
व्योम conf_parse(स्थिर अक्षर *name);
पूर्णांक conf_पढ़ो(स्थिर अक्षर *name);
पूर्णांक conf_पढ़ो_simple(स्थिर अक्षर *name, पूर्णांक);
पूर्णांक conf_ग_लिखो_defconfig(स्थिर अक्षर *name);
पूर्णांक conf_ग_लिखो(स्थिर अक्षर *name);
पूर्णांक conf_ग_लिखो_स्वतःconf(पूर्णांक overग_लिखो);
व्योम conf_set_changed(bool val);
bool conf_get_changed(व्योम);
व्योम conf_set_changed_callback(व्योम (*fn)(व्योम));
व्योम conf_set_message_callback(व्योम (*fn)(स्थिर अक्षर *s));

/* symbol.c */
बाह्य काष्ठा symbol * symbol_hash[SYMBOL_HASHSIZE];

काष्ठा symbol * sym_lookup(स्थिर अक्षर *name, पूर्णांक flags);
काष्ठा symbol * sym_find(स्थिर अक्षर *name);
स्थिर अक्षर * sym_escape_string_value(स्थिर अक्षर *in);
काष्ठा symbol ** sym_re_search(स्थिर अक्षर *pattern);
स्थिर अक्षर * sym_type_name(क्रमागत symbol_type type);
व्योम sym_calc_value(काष्ठा symbol *sym);
क्रमागत symbol_type sym_get_type(काष्ठा symbol *sym);
bool sym_tristate_within_range(काष्ठा symbol *sym,tristate tri);
bool sym_set_tristate_value(काष्ठा symbol *sym,tristate tri);
tristate sym_toggle_tristate_value(काष्ठा symbol *sym);
bool sym_string_valid(काष्ठा symbol *sym, स्थिर अक्षर *newval);
bool sym_string_within_range(काष्ठा symbol *sym, स्थिर अक्षर *str);
bool sym_set_string_value(काष्ठा symbol *sym, स्थिर अक्षर *newval);
bool sym_is_changeable(काष्ठा symbol *sym);
काष्ठा property * sym_get_choice_prop(काष्ठा symbol *sym);
स्थिर अक्षर * sym_get_string_value(काष्ठा symbol *sym);

स्थिर अक्षर * prop_get_type_name(क्रमागत prop_type type);

/* preprocess.c */
क्रमागत variable_flavor अणु
	VAR_SIMPLE,
	VAR_RECURSIVE,
	VAR_APPEND,
पूर्ण;
व्योम env_ग_लिखो_dep(खाता *f, स्थिर अक्षर *स्वतः_conf_name);
व्योम variable_add(स्थिर अक्षर *name, स्थिर अक्षर *value,
		  क्रमागत variable_flavor flavor);
व्योम variable_all_del(व्योम);
अक्षर *expand_करोllar(स्थिर अक्षर **str);
अक्षर *expand_one_token(स्थिर अक्षर **str);

/* expr.c */
व्योम expr_prपूर्णांक(काष्ठा expr *e, व्योम (*fn)(व्योम *, काष्ठा symbol *, स्थिर अक्षर *), व्योम *data, पूर्णांक prevtoken);
