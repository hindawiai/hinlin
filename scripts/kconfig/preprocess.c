<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (C) 2018 Masahiro Yamada <yamada.masahiro@socionext.com>

#समावेश <प्रकार.स>
#समावेश <मानकतर्क.स>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>

#समावेश "list.h"
#समावेश "lkc.h"

#घोषणा ARRAY_SIZE(arr)		(माप(arr) / माप((arr)[0]))

अटल अक्षर *expand_string_with_args(स्थिर अक्षर *in, पूर्णांक argc, अक्षर *argv[]);
अटल अक्षर *expand_string(स्थिर अक्षर *in);

अटल व्योम __attribute__((noवापस)) pलिखो_त्रुटि(स्थिर अक्षर *क्रमmat, ...)
अणु
	बहु_सूची ap;

	ख_लिखो(मानक_त्रुटि, "%s:%d: ", current_file->name, yylineno);
	बहु_शुरू(ap, क्रमmat);
	भख_लिखो(मानक_त्रुटि, क्रमmat, ap);
	बहु_पूर्ण(ap);
	ख_लिखो(मानक_त्रुटि, "\n");

	निकास(1);
पूर्ण

/*
 * Environment variables
 */
अटल LIST_HEAD(env_list);

काष्ठा env अणु
	अक्षर *name;
	अक्षर *value;
	काष्ठा list_head node;
पूर्ण;

अटल व्योम env_add(स्थिर अक्षर *name, स्थिर अक्षर *value)
अणु
	काष्ठा env *e;

	e = xदो_स्मृति(माप(*e));
	e->name = xstrdup(name);
	e->value = xstrdup(value);

	list_add_tail(&e->node, &env_list);
पूर्ण

अटल व्योम env_del(काष्ठा env *e)
अणु
	list_del(&e->node);
	मुक्त(e->name);
	मुक्त(e->value);
	मुक्त(e);
पूर्ण

/* The वापसed poपूर्णांकer must be मुक्तd when करोne */
अटल अक्षर *env_expand(स्थिर अक्षर *name)
अणु
	काष्ठा env *e;
	स्थिर अक्षर *value;

	अगर (!*name)
		वापस शून्य;

	list_क्रम_each_entry(e, &env_list, node) अणु
		अगर (!म_भेद(name, e->name))
			वापस xstrdup(e->value);
	पूर्ण

	value = दो_पर्या(name);
	अगर (!value)
		वापस शून्य;

	/*
	 * We need to remember all referenced environment variables.
	 * They will be written out to include/config/स्वतः.conf.cmd
	 */
	env_add(name, value);

	वापस xstrdup(value);
पूर्ण

व्योम env_ग_लिखो_dep(खाता *f, स्थिर अक्षर *स्वतःconfig_name)
अणु
	काष्ठा env *e, *पंचांगp;

	list_क्रम_each_entry_safe(e, पंचांगp, &env_list, node) अणु
		ख_लिखो(f, "ifneq \"$(%s)\" \"%s\"\n", e->name, e->value);
		ख_लिखो(f, "%s: FORCE\n", स्वतःconfig_name);
		ख_लिखो(f, "endif\n");
		env_del(e);
	पूर्ण
पूर्ण

/*
 * Built-in functions
 */
काष्ठा function अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक min_args;
	अचिन्हित पूर्णांक max_args;
	अक्षर *(*func)(पूर्णांक argc, अक्षर *argv[]);
पूर्ण;

अटल अक्षर *करो_error_अगर(पूर्णांक argc, अक्षर *argv[])
अणु
	अगर (!म_भेद(argv[0], "y"))
		pलिखो_त्रुटि("%s", argv[1]);

	वापस xstrdup("");
पूर्ण

अटल अक्षर *करो_filename(पूर्णांक argc, अक्षर *argv[])
अणु
	वापस xstrdup(current_file->name);
पूर्ण

अटल अक्षर *करो_info(पूर्णांक argc, अक्षर *argv[])
अणु
	म_लिखो("%s\n", argv[0]);

	वापस xstrdup("");
पूर्ण

अटल अक्षर *करो_lineno(पूर्णांक argc, अक्षर *argv[])
अणु
	अक्षर buf[16];

	प्र_लिखो(buf, "%d", yylineno);

	वापस xstrdup(buf);
पूर्ण

अटल अक्षर *करो_shell(पूर्णांक argc, अक्षर *argv[])
अणु
	खाता *p;
	अक्षर buf[256];
	अक्षर *cmd;
	माप_प्रकार nपढ़ो;
	पूर्णांक i;

	cmd = argv[0];

	p = pखोलो(cmd, "r");
	अगर (!p) अणु
		लिखो_त्रुटि(cmd);
		निकास(1);
	पूर्ण

	nपढ़ो = ख_पढ़ो(buf, 1, माप(buf), p);
	अगर (nपढ़ो == माप(buf))
		nपढ़ो--;

	/* हटाओ trailing new lines */
	जबतक (nपढ़ो > 0 && buf[nपढ़ो - 1] == '\n')
		nपढ़ो--;

	buf[nपढ़ो] = 0;

	/* replace a new line with a space */
	क्रम (i = 0; i < nपढ़ो; i++) अणु
		अगर (buf[i] == '\n')
			buf[i] = ' ';
	पूर्ण

	अगर (pबंद(p) == -1) अणु
		लिखो_त्रुटि(cmd);
		निकास(1);
	पूर्ण

	वापस xstrdup(buf);
पूर्ण

अटल अक्षर *करो_warning_अगर(पूर्णांक argc, अक्षर *argv[])
अणु
	अगर (!म_भेद(argv[0], "y"))
		ख_लिखो(मानक_त्रुटि, "%s:%d: %s\n",
			current_file->name, yylineno, argv[1]);

	वापस xstrdup("");
पूर्ण

अटल स्थिर काष्ठा function function_table[] = अणु
	/* Name		MIN	MAX	Function */
	अणु "error-if",	2,	2,	करो_error_अगर पूर्ण,
	अणु "filename",	0,	0,	करो_filename पूर्ण,
	अणु "info",	1,	1,	करो_info पूर्ण,
	अणु "lineno",	0,	0,	करो_lineno पूर्ण,
	अणु "shell",	1,	1,	करो_shell पूर्ण,
	अणु "warning-if",	2,	2,	करो_warning_अगर पूर्ण,
पूर्ण;

#घोषणा FUNCTION_MAX_ARGS		16

अटल अक्षर *function_expand(स्थिर अक्षर *name, पूर्णांक argc, अक्षर *argv[])
अणु
	स्थिर काष्ठा function *f;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(function_table); i++) अणु
		f = &function_table[i];
		अगर (म_भेद(f->name, name))
			जारी;

		अगर (argc < f->min_args)
			pलिखो_त्रुटि("too few function arguments passed to '%s'",
				name);

		अगर (argc > f->max_args)
			pलिखो_त्रुटि("too many function arguments passed to '%s'",
				name);

		वापस f->func(argc, argv);
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Variables (and user-defined functions)
 */
अटल LIST_HEAD(variable_list);

काष्ठा variable अणु
	अक्षर *name;
	अक्षर *value;
	क्रमागत variable_flavor flavor;
	पूर्णांक exp_count;
	काष्ठा list_head node;
पूर्ण;

अटल काष्ठा variable *variable_lookup(स्थिर अक्षर *name)
अणु
	काष्ठा variable *v;

	list_क्रम_each_entry(v, &variable_list, node) अणु
		अगर (!म_भेद(name, v->name))
			वापस v;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अक्षर *variable_expand(स्थिर अक्षर *name, पूर्णांक argc, अक्षर *argv[])
अणु
	काष्ठा variable *v;
	अक्षर *res;

	v = variable_lookup(name);
	अगर (!v)
		वापस शून्य;

	अगर (argc == 0 && v->exp_count)
		pलिखो_त्रुटि("Recursive variable '%s' references itself (eventually)",
			name);

	अगर (v->exp_count > 1000)
		pलिखो_त्रुटि("Too deep recursive expansion");

	v->exp_count++;

	अगर (v->flavor == VAR_RECURSIVE)
		res = expand_string_with_args(v->value, argc, argv);
	अन्यथा
		res = xstrdup(v->value);

	v->exp_count--;

	वापस res;
पूर्ण

व्योम variable_add(स्थिर अक्षर *name, स्थिर अक्षर *value,
		  क्रमागत variable_flavor flavor)
अणु
	काष्ठा variable *v;
	अक्षर *new_value;
	bool append = false;

	v = variable_lookup(name);
	अगर (v) अणु
		/* For defined variables, += inherits the existing flavor */
		अगर (flavor == VAR_APPEND) अणु
			flavor = v->flavor;
			append = true;
		पूर्ण अन्यथा अणु
			मुक्त(v->value);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* For undefined variables, += assumes the recursive flavor */
		अगर (flavor == VAR_APPEND)
			flavor = VAR_RECURSIVE;

		v = xदो_स्मृति(माप(*v));
		v->name = xstrdup(name);
		v->exp_count = 0;
		list_add_tail(&v->node, &variable_list);
	पूर्ण

	v->flavor = flavor;

	अगर (flavor == VAR_SIMPLE)
		new_value = expand_string(value);
	अन्यथा
		new_value = xstrdup(value);

	अगर (append) अणु
		v->value = xपुनः_स्मृति(v->value,
				    म_माप(v->value) + म_माप(new_value) + 2);
		म_जोड़ो(v->value, " ");
		म_जोड़ो(v->value, new_value);
		मुक्त(new_value);
	पूर्ण अन्यथा अणु
		v->value = new_value;
	पूर्ण
पूर्ण

अटल व्योम variable_del(काष्ठा variable *v)
अणु
	list_del(&v->node);
	मुक्त(v->name);
	मुक्त(v->value);
	मुक्त(v);
पूर्ण

व्योम variable_all_del(व्योम)
अणु
	काष्ठा variable *v, *पंचांगp;

	list_क्रम_each_entry_safe(v, पंचांगp, &variable_list, node)
		variable_del(v);
पूर्ण

/*
 * Evaluate a clause with arguments.  argc/argv are arguments from the upper
 * function call.
 *
 * Returned string must be मुक्तd when करोne
 */
अटल अक्षर *eval_clause(स्थिर अक्षर *str, माप_प्रकार len, पूर्णांक argc, अक्षर *argv[])
अणु
	अक्षर *पंचांगp, *name, *res, *endptr, *prev, *p;
	पूर्णांक new_argc = 0;
	अक्षर *new_argv[FUNCTION_MAX_ARGS];
	पूर्णांक nest = 0;
	पूर्णांक i;
	अचिन्हित दीर्घ n;

	पंचांगp = xstrndup(str, len);

	/*
	 * If variable name is '1', '2', etc.  It is generally an argument
	 * from a user-function call (i.e. local-scope variable).  If not
	 * available, then look-up global-scope variables.
	 */
	n = म_से_अदीर्घ(पंचांगp, &endptr, 10);
	अगर (!*endptr && n > 0 && n <= argc) अणु
		res = xstrdup(argv[n - 1]);
		जाओ मुक्त_पंचांगp;
	पूर्ण

	prev = p = पंचांगp;

	/*
	 * Split पूर्णांकo tokens
	 * The function name and arguments are separated by a comma.
	 * For example, अगर the function call is like this:
	 *   $(foo,$(x),$(y))
	 *
	 * The input string क्रम this helper should be:
	 *   foo,$(x),$(y)
	 *
	 * and split पूर्णांकo:
	 *   new_argv[0] = 'foo'
	 *   new_argv[1] = '$(x)'
	 *   new_argv[2] = '$(y)'
	 */
	जबतक (*p) अणु
		अगर (nest == 0 && *p == ',') अणु
			*p = 0;
			अगर (new_argc >= FUNCTION_MAX_ARGS)
				pलिखो_त्रुटि("too many function arguments");
			new_argv[new_argc++] = prev;
			prev = p + 1;
		पूर्ण अन्यथा अगर (*p == '(') अणु
			nest++;
		पूर्ण अन्यथा अगर (*p == ')') अणु
			nest--;
		पूर्ण

		p++;
	पूर्ण
	new_argv[new_argc++] = prev;

	/*
	 * Shअगरt arguments
	 * new_argv[0] represents a function name or a variable name.  Put it
	 * पूर्णांकo 'name', then shअगरt the rest of the arguments.  This simplअगरies
	 * 'const' handling.
	 */
	name = expand_string_with_args(new_argv[0], argc, argv);
	new_argc--;
	क्रम (i = 0; i < new_argc; i++)
		new_argv[i] = expand_string_with_args(new_argv[i + 1],
						      argc, argv);

	/* Search क्रम variables */
	res = variable_expand(name, new_argc, new_argv);
	अगर (res)
		जाओ मुक्त;

	/* Look क्रम built-in functions */
	res = function_expand(name, new_argc, new_argv);
	अगर (res)
		जाओ मुक्त;

	/* Last, try environment variable */
	अगर (new_argc == 0) अणु
		res = env_expand(name);
		अगर (res)
			जाओ मुक्त;
	पूर्ण

	res = xstrdup("");
मुक्त:
	क्रम (i = 0; i < new_argc; i++)
		मुक्त(new_argv[i]);
	मुक्त(name);
मुक्त_पंचांगp:
	मुक्त(पंचांगp);

	वापस res;
पूर्ण

/*
 * Expand a string that follows '$'
 *
 * For example, अगर the input string is
 *     ($(FOO)$($(BAR)))$(BAZ)
 * this helper evaluates
 *     $($(FOO)$($(BAR)))
 * and वापसs a new string containing the expansion (note that the string is
 * recursively expanded), also advancing 'str' to poपूर्णांक to the next अक्षरacter
 * after the corresponding closing parenthesis, in this हाल, *str will be
 *     $(BAR)
 */
अटल अक्षर *expand_करोllar_with_args(स्थिर अक्षर **str, पूर्णांक argc, अक्षर *argv[])
अणु
	स्थिर अक्षर *p = *str;
	स्थिर अक्षर *q;
	पूर्णांक nest = 0;

	/*
	 * In Kconfig, variable/function references always start with "$(".
	 * Neither single-letter variables as in $A nor curly braces as in $अणुCCपूर्ण
	 * are supported.  '$' not followed by '(' loses its special meaning.
	 */
	अगर (*p != '(') अणु
		*str = p;
		वापस xstrdup("$");
	पूर्ण

	p++;
	q = p;
	जबतक (*q) अणु
		अगर (*q == '(') अणु
			nest++;
		पूर्ण अन्यथा अगर (*q == ')') अणु
			अगर (nest-- == 0)
				अवरोध;
		पूर्ण
		q++;
	पूर्ण

	अगर (!*q)
		pलिखो_त्रुटि("unterminated reference to '%s': missing ')'", p);

	/* Advance 'str' to after the expanded initial portion of the string */
	*str = q + 1;

	वापस eval_clause(p, q - p, argc, argv);
पूर्ण

अक्षर *expand_करोllar(स्थिर अक्षर **str)
अणु
	वापस expand_करोllar_with_args(str, 0, शून्य);
पूर्ण

अटल अक्षर *__expand_string(स्थिर अक्षर **str, bool (*is_end)(अक्षर c),
			     पूर्णांक argc, अक्षर *argv[])
अणु
	स्थिर अक्षर *in, *p;
	अक्षर *expansion, *out;
	माप_प्रकार in_len, out_len;

	out = xदो_स्मृति(1);
	*out = 0;
	out_len = 1;

	p = in = *str;

	जबतक (1) अणु
		अगर (*p == '$') अणु
			in_len = p - in;
			p++;
			expansion = expand_करोllar_with_args(&p, argc, argv);
			out_len += in_len + म_माप(expansion);
			out = xपुनः_स्मृति(out, out_len);
			म_जोड़न(out, in, in_len);
			म_जोड़ो(out, expansion);
			मुक्त(expansion);
			in = p;
			जारी;
		पूर्ण

		अगर (is_end(*p))
			अवरोध;

		p++;
	पूर्ण

	in_len = p - in;
	out_len += in_len;
	out = xपुनः_स्मृति(out, out_len);
	म_जोड़न(out, in, in_len);

	/* Advance 'str' to the end अक्षरacter */
	*str = p;

	वापस out;
पूर्ण

अटल bool is_end_of_str(अक्षर c)
अणु
	वापस !c;
पूर्ण

/*
 * Expand variables and functions in the given string.  Undefined variables
 * expand to an empty string.
 * The वापसed string must be मुक्तd when करोne.
 */
अटल अक्षर *expand_string_with_args(स्थिर अक्षर *in, पूर्णांक argc, अक्षर *argv[])
अणु
	वापस __expand_string(&in, is_end_of_str, argc, argv);
पूर्ण

अटल अक्षर *expand_string(स्थिर अक्षर *in)
अणु
	वापस expand_string_with_args(in, 0, शून्य);
पूर्ण

अटल bool is_end_of_token(अक्षर c)
अणु
	वापस !(है_अक्षर_अंक(c) || c == '_' || c == '-');
पूर्ण

/*
 * Expand variables in a token.  The parsing stops when a token separater
 * (in most हालs, it is a whitespace) is encountered.  'str' is updated to
 * poपूर्णांक to the next अक्षरacter.
 *
 * The वापसed string must be मुक्तd when करोne.
 */
अक्षर *expand_one_token(स्थिर अक्षर **str)
अणु
	वापस __expand_string(str, is_end_of_token, 0, शून्य);
पूर्ण
