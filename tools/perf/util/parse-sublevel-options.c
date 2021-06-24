<शैली गुरु>
#समावेश <मानककोष.स>
#समावेश <मानक_निवेशt.h>
#समावेश <माला.स>
#समावेश <मानकपन.स>

#समावेश "util/debug.h"
#समावेश "util/parse-sublevel-options.h"

अटल पूर्णांक parse_one_sublevel_option(स्थिर अक्षर *str,
				     काष्ठा sublevel_option *opts)
अणु
	काष्ठा sublevel_option *opt = opts;
	अक्षर *vstr, *s = strdup(str);
	पूर्णांक v = 1;

	अगर (!s) अणु
		pr_err("no memory\n");
		वापस -1;
	पूर्ण

	vstr = म_अक्षर(s, '=');
	अगर (vstr)
		*vstr++ = 0;

	जबतक (opt->name) अणु
		अगर (!म_भेद(s, opt->name))
			अवरोध;
		opt++;
	पूर्ण

	अगर (!opt->name) अणु
		pr_err("Unknown option name '%s'\n", s);
		मुक्त(s);
		वापस -1;
	पूर्ण

	अगर (vstr)
		v = म_से_प(vstr);

	*opt->value_ptr = v;
	मुक्त(s);
	वापस 0;
पूर्ण

/* parse options like --foo a=<n>,b,c... */
पूर्णांक perf_parse_sublevel_options(स्थिर अक्षर *str, काष्ठा sublevel_option *opts)
अणु
	अक्षर *s = strdup(str);
	अक्षर *p = शून्य;
	पूर्णांक ret;

	अगर (!s) अणु
		pr_err("no memory\n");
		वापस -1;
	पूर्ण

	p = म_मोहर(s, ",");
	जबतक (p) अणु
		ret = parse_one_sublevel_option(p, opts);
		अगर (ret) अणु
			मुक्त(s);
			वापस ret;
		पूर्ण

		p = म_मोहर(शून्य, ",");
	पूर्ण

	मुक्त(s);
	वापस 0;
पूर्ण
