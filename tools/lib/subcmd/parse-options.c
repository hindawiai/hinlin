<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/compiler.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <मानक_निवेशt.h>
#समावेश <माला.स>
#समावेश <प्रकार.स>
#समावेश "subcmd-util.h"
#समावेश "parse-options.h"
#समावेश "subcmd-config.h"
#समावेश "pager.h"

#घोषणा OPT_SHORT 1
#घोषणा OPT_UNSET 2

अक्षर *error_buf;

अटल पूर्णांक opterror(स्थिर काष्ठा option *opt, स्थिर अक्षर *reason, पूर्णांक flags)
अणु
	अगर (flags & OPT_SHORT)
		ख_लिखो(मानक_त्रुटि, " Error: switch `%c' %s", opt->लघु_name, reason);
	अन्यथा अगर (flags & OPT_UNSET)
		ख_लिखो(मानक_त्रुटि, " Error: option `no-%s' %s", opt->दीर्घ_name, reason);
	अन्यथा
		ख_लिखो(मानक_त्रुटि, " Error: option `%s' %s", opt->दीर्घ_name, reason);

	वापस -1;
पूर्ण

अटल स्थिर अक्षर *skip_prefix(स्थिर अक्षर *str, स्थिर अक्षर *prefix)
अणु
	माप_प्रकार len = म_माप(prefix);
	वापस म_भेदन(str, prefix, len) ? शून्य : str + len;
पूर्ण

अटल व्योम optwarning(स्थिर काष्ठा option *opt, स्थिर अक्षर *reason, पूर्णांक flags)
अणु
	अगर (flags & OPT_SHORT)
		ख_लिखो(मानक_त्रुटि, " Warning: switch `%c' %s", opt->लघु_name, reason);
	अन्यथा अगर (flags & OPT_UNSET)
		ख_लिखो(मानक_त्रुटि, " Warning: option `no-%s' %s", opt->दीर्घ_name, reason);
	अन्यथा
		ख_लिखो(मानक_त्रुटि, " Warning: option `%s' %s", opt->दीर्घ_name, reason);
पूर्ण

अटल पूर्णांक get_arg(काष्ठा parse_opt_ctx_t *p, स्थिर काष्ठा option *opt,
		   पूर्णांक flags, स्थिर अक्षर **arg)
अणु
	स्थिर अक्षर *res;

	अगर (p->opt) अणु
		res = p->opt;
		p->opt = शून्य;
	पूर्ण अन्यथा अगर ((opt->flags & PARSE_OPT_LASTARG_DEFAULT) && (p->argc == 1 ||
		    **(p->argv + 1) == '-')) अणु
		res = (स्थिर अक्षर *)opt->defval;
	पूर्ण अन्यथा अगर (p->argc > 1) अणु
		p->argc--;
		res = *++p->argv;
	पूर्ण अन्यथा
		वापस opterror(opt, "requires a value", flags);
	अगर (arg)
		*arg = res;
	वापस 0;
पूर्ण

अटल पूर्णांक get_value(काष्ठा parse_opt_ctx_t *p,
		     स्थिर काष्ठा option *opt, पूर्णांक flags)
अणु
	स्थिर अक्षर *s, *arg = शून्य;
	स्थिर पूर्णांक unset = flags & OPT_UNSET;
	पूर्णांक err;

	अगर (unset && p->opt)
		वापस opterror(opt, "takes no value", flags);
	अगर (unset && (opt->flags & PARSE_OPT_NONEG))
		वापस opterror(opt, "isn't available", flags);
	अगर (opt->flags & PARSE_OPT_DISABLED)
		वापस opterror(opt, "is not usable", flags);

	अगर (opt->flags & PARSE_OPT_EXCLUSIVE) अणु
		अगर (p->excl_opt && p->excl_opt != opt) अणु
			अक्षर msg[128];

			अगर (((flags & OPT_SHORT) && p->excl_opt->लघु_name) ||
			    p->excl_opt->दीर्घ_name == शून्य) अणु
				snम_लिखो(msg, माप(msg), "cannot be used with switch `%c'",
					 p->excl_opt->लघु_name);
			पूर्ण अन्यथा अणु
				snम_लिखो(msg, माप(msg), "cannot be used with %s",
					 p->excl_opt->दीर्घ_name);
			पूर्ण
			opterror(opt, msg, flags);
			वापस -3;
		पूर्ण
		p->excl_opt = opt;
	पूर्ण
	अगर (!(flags & OPT_SHORT) && p->opt) अणु
		चयन (opt->type) अणु
		हाल OPTION_CALLBACK:
			अगर (!(opt->flags & PARSE_OPT_NOARG))
				अवरोध;
			/* FALLTHROUGH */
		हाल OPTION_BOOLEAN:
		हाल OPTION_INCR:
		हाल OPTION_BIT:
		हाल OPTION_SET_UINT:
		हाल OPTION_SET_PTR:
			वापस opterror(opt, "takes no value", flags);
		हाल OPTION_END:
		हाल OPTION_ARGUMENT:
		हाल OPTION_GROUP:
		हाल OPTION_STRING:
		हाल OPTION_INTEGER:
		हाल OPTION_UINTEGER:
		हाल OPTION_LONG:
		हाल OPTION_ULONG:
		हाल OPTION_U64:
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (opt->flags & PARSE_OPT_NOBUILD) अणु
		अक्षर reason[128];
		bool noarg = false;

		err = snम_लिखो(reason, माप(reason),
				opt->flags & PARSE_OPT_CANSKIP ?
					"is being ignored because %s " :
					"is not available because %s",
				opt->build_opt);
		reason[माप(reason) - 1] = '\0';

		अगर (err < 0)
			म_नकलन(reason, opt->flags & PARSE_OPT_CANSKIP ?
					"is being ignored" :
					"is not available",
					माप(reason));

		अगर (!(opt->flags & PARSE_OPT_CANSKIP))
			वापस opterror(opt, reason, flags);

		err = 0;
		अगर (unset)
			noarg = true;
		अगर (opt->flags & PARSE_OPT_NOARG)
			noarg = true;
		अगर (opt->flags & PARSE_OPT_OPTARG && !p->opt)
			noarg = true;

		चयन (opt->type) अणु
		हाल OPTION_BOOLEAN:
		हाल OPTION_INCR:
		हाल OPTION_BIT:
		हाल OPTION_SET_UINT:
		हाल OPTION_SET_PTR:
		हाल OPTION_END:
		हाल OPTION_ARGUMENT:
		हाल OPTION_GROUP:
			noarg = true;
			अवरोध;
		हाल OPTION_CALLBACK:
		हाल OPTION_STRING:
		हाल OPTION_INTEGER:
		हाल OPTION_UINTEGER:
		हाल OPTION_LONG:
		हाल OPTION_ULONG:
		हाल OPTION_U64:
		शेष:
			अवरोध;
		पूर्ण

		अगर (!noarg)
			err = get_arg(p, opt, flags, शून्य);
		अगर (err)
			वापस err;

		optwarning(opt, reason, flags);
		वापस 0;
	पूर्ण

	चयन (opt->type) अणु
	हाल OPTION_BIT:
		अगर (unset)
			*(पूर्णांक *)opt->value &= ~opt->defval;
		अन्यथा
			*(पूर्णांक *)opt->value |= opt->defval;
		वापस 0;

	हाल OPTION_BOOLEAN:
		*(bool *)opt->value = unset ? false : true;
		अगर (opt->set)
			*(bool *)opt->set = true;
		वापस 0;

	हाल OPTION_INCR:
		*(पूर्णांक *)opt->value = unset ? 0 : *(पूर्णांक *)opt->value + 1;
		वापस 0;

	हाल OPTION_SET_UINT:
		*(अचिन्हित पूर्णांक *)opt->value = unset ? 0 : opt->defval;
		वापस 0;

	हाल OPTION_SET_PTR:
		*(व्योम **)opt->value = unset ? शून्य : (व्योम *)opt->defval;
		वापस 0;

	हाल OPTION_STRING:
		err = 0;
		अगर (unset)
			*(स्थिर अक्षर **)opt->value = शून्य;
		अन्यथा अगर (opt->flags & PARSE_OPT_OPTARG && !p->opt)
			*(स्थिर अक्षर **)opt->value = (स्थिर अक्षर *)opt->defval;
		अन्यथा
			err = get_arg(p, opt, flags, (स्थिर अक्षर **)opt->value);

		अगर (opt->set)
			*(bool *)opt->set = true;

		/* PARSE_OPT_NOEMPTY: Allow शून्य but disallow empty string. */
		अगर (opt->flags & PARSE_OPT_NOEMPTY) अणु
			स्थिर अक्षर *val = *(स्थिर अक्षर **)opt->value;

			अगर (!val)
				वापस err;

			/* Similar to unset अगर we are given an empty string. */
			अगर (val[0] == '\0') अणु
				*(स्थिर अक्षर **)opt->value = शून्य;
				वापस 0;
			पूर्ण
		पूर्ण

		वापस err;

	हाल OPTION_CALLBACK:
		अगर (opt->set)
			*(bool *)opt->set = true;

		अगर (unset)
			वापस (*opt->callback)(opt, शून्य, 1) ? (-1) : 0;
		अगर (opt->flags & PARSE_OPT_NOARG)
			वापस (*opt->callback)(opt, शून्य, 0) ? (-1) : 0;
		अगर (opt->flags & PARSE_OPT_OPTARG && !p->opt)
			वापस (*opt->callback)(opt, शून्य, 0) ? (-1) : 0;
		अगर (get_arg(p, opt, flags, &arg))
			वापस -1;
		वापस (*opt->callback)(opt, arg, 0) ? (-1) : 0;

	हाल OPTION_INTEGER:
		अगर (unset) अणु
			*(पूर्णांक *)opt->value = 0;
			वापस 0;
		पूर्ण
		अगर (opt->flags & PARSE_OPT_OPTARG && !p->opt) अणु
			*(पूर्णांक *)opt->value = opt->defval;
			वापस 0;
		पूर्ण
		अगर (get_arg(p, opt, flags, &arg))
			वापस -1;
		*(पूर्णांक *)opt->value = म_से_दीर्घ(arg, (अक्षर **)&s, 10);
		अगर (*s)
			वापस opterror(opt, "expects a numerical value", flags);
		वापस 0;

	हाल OPTION_UINTEGER:
		अगर (unset) अणु
			*(अचिन्हित पूर्णांक *)opt->value = 0;
			वापस 0;
		पूर्ण
		अगर (opt->flags & PARSE_OPT_OPTARG && !p->opt) अणु
			*(अचिन्हित पूर्णांक *)opt->value = opt->defval;
			वापस 0;
		पूर्ण
		अगर (get_arg(p, opt, flags, &arg))
			वापस -1;
		अगर (arg[0] == '-')
			वापस opterror(opt, "expects an unsigned numerical value", flags);
		*(अचिन्हित पूर्णांक *)opt->value = म_से_दीर्घ(arg, (अक्षर **)&s, 10);
		अगर (*s)
			वापस opterror(opt, "expects a numerical value", flags);
		वापस 0;

	हाल OPTION_LONG:
		अगर (unset) अणु
			*(दीर्घ *)opt->value = 0;
			वापस 0;
		पूर्ण
		अगर (opt->flags & PARSE_OPT_OPTARG && !p->opt) अणु
			*(दीर्घ *)opt->value = opt->defval;
			वापस 0;
		पूर्ण
		अगर (get_arg(p, opt, flags, &arg))
			वापस -1;
		*(दीर्घ *)opt->value = म_से_दीर्घ(arg, (अक्षर **)&s, 10);
		अगर (*s)
			वापस opterror(opt, "expects a numerical value", flags);
		वापस 0;

	हाल OPTION_ULONG:
		अगर (unset) अणु
			*(अचिन्हित दीर्घ *)opt->value = 0;
			वापस 0;
		पूर्ण
		अगर (opt->flags & PARSE_OPT_OPTARG && !p->opt) अणु
			*(अचिन्हित दीर्घ *)opt->value = opt->defval;
			वापस 0;
		पूर्ण
		अगर (get_arg(p, opt, flags, &arg))
			वापस -1;
		*(अचिन्हित दीर्घ *)opt->value = म_से_अदीर्घ(arg, (अक्षर **)&s, 10);
		अगर (*s)
			वापस opterror(opt, "expects a numerical value", flags);
		वापस 0;

	हाल OPTION_U64:
		अगर (unset) अणु
			*(u64 *)opt->value = 0;
			वापस 0;
		पूर्ण
		अगर (opt->flags & PARSE_OPT_OPTARG && !p->opt) अणु
			*(u64 *)opt->value = opt->defval;
			वापस 0;
		पूर्ण
		अगर (get_arg(p, opt, flags, &arg))
			वापस -1;
		अगर (arg[0] == '-')
			वापस opterror(opt, "expects an unsigned numerical value", flags);
		*(u64 *)opt->value = म_से_अदीर्घl(arg, (अक्षर **)&s, 10);
		अगर (*s)
			वापस opterror(opt, "expects a numerical value", flags);
		वापस 0;

	हाल OPTION_END:
	हाल OPTION_ARGUMENT:
	हाल OPTION_GROUP:
	शेष:
		die("should not happen, someone must be hit on the forehead");
	पूर्ण
पूर्ण

अटल पूर्णांक parse_लघु_opt(काष्ठा parse_opt_ctx_t *p, स्थिर काष्ठा option *options)
अणु
retry:
	क्रम (; options->type != OPTION_END; options++) अणु
		अगर (options->लघु_name == *p->opt) अणु
			p->opt = p->opt[1] ? p->opt + 1 : शून्य;
			वापस get_value(p, options, OPT_SHORT);
		पूर्ण
	पूर्ण

	अगर (options->parent) अणु
		options = options->parent;
		जाओ retry;
	पूर्ण

	वापस -2;
पूर्ण

अटल पूर्णांक parse_दीर्घ_opt(काष्ठा parse_opt_ctx_t *p, स्थिर अक्षर *arg,
                          स्थिर काष्ठा option *options)
अणु
	स्थिर अक्षर *arg_end = म_अक्षर(arg, '=');
	स्थिर काष्ठा option *abbrev_option = शून्य, *ambiguous_option = शून्य;
	पूर्णांक abbrev_flags = 0, ambiguous_flags = 0;

	अगर (!arg_end)
		arg_end = arg + म_माप(arg);

retry:
	क्रम (; options->type != OPTION_END; options++) अणु
		स्थिर अक्षर *rest;
		पूर्णांक flags = 0;

		अगर (!options->दीर्घ_name)
			जारी;

		rest = skip_prefix(arg, options->दीर्घ_name);
		अगर (options->type == OPTION_ARGUMENT) अणु
			अगर (!rest)
				जारी;
			अगर (*rest == '=')
				वापस opterror(options, "takes no value", flags);
			अगर (*rest)
				जारी;
			p->out[p->cpidx++] = arg - 2;
			वापस 0;
		पूर्ण
		अगर (!rest) अणु
			अगर (strstarts(options->दीर्घ_name, "no-")) अणु
				/*
				 * The दीर्घ name itself starts with "no-", so
				 * accept the option without "no-" so that users
				 * करो not have to enter "no-no-" to get the
				 * negation.
				 */
				rest = skip_prefix(arg, options->दीर्घ_name + 3);
				अगर (rest) अणु
					flags |= OPT_UNSET;
					जाओ match;
				पूर्ण
				/* Abbreviated हाल */
				अगर (strstarts(options->दीर्घ_name + 3, arg)) अणु
					flags |= OPT_UNSET;
					जाओ is_abbreviated;
				पूर्ण
			पूर्ण
			/* abbreviated? */
			अगर (!म_भेदन(options->दीर्घ_name, arg, arg_end - arg)) अणु
is_abbreviated:
				अगर (abbrev_option) अणु
					/*
					 * If this is abbreviated, it is
					 * ambiguous. So when there is no
					 * exact match later, we need to
					 * error out.
					 */
					ambiguous_option = abbrev_option;
					ambiguous_flags = abbrev_flags;
				पूर्ण
				अगर (!(flags & OPT_UNSET) && *arg_end)
					p->opt = arg_end + 1;
				abbrev_option = options;
				abbrev_flags = flags;
				जारी;
			पूर्ण
			/* negated and abbreviated very much? */
			अगर (strstarts("no-", arg)) अणु
				flags |= OPT_UNSET;
				जाओ is_abbreviated;
			पूर्ण
			/* negated? */
			अगर (म_भेदन(arg, "no-", 3))
				जारी;
			flags |= OPT_UNSET;
			rest = skip_prefix(arg + 3, options->दीर्घ_name);
			/* abbreviated and negated? */
			अगर (!rest && strstarts(options->दीर्घ_name, arg + 3))
				जाओ is_abbreviated;
			अगर (!rest)
				जारी;
		पूर्ण
match:
		अगर (*rest) अणु
			अगर (*rest != '=')
				जारी;
			p->opt = rest + 1;
		पूर्ण
		वापस get_value(p, options, flags);
	पूर्ण

	अगर (ambiguous_option) अणु
		 ख_लिखो(मानक_त्रुटि,
			 " Error: Ambiguous option: %s (could be --%s%s or --%s%s)\n",
			 arg,
			 (ambiguous_flags & OPT_UNSET) ?  "no-" : "",
			 ambiguous_option->दीर्घ_name,
			 (abbrev_flags & OPT_UNSET) ?  "no-" : "",
			 abbrev_option->दीर्घ_name);
		 वापस -1;
	पूर्ण
	अगर (abbrev_option)
		वापस get_value(p, abbrev_option, abbrev_flags);

	अगर (options->parent) अणु
		options = options->parent;
		जाओ retry;
	पूर्ण

	वापस -2;
पूर्ण

अटल व्योम check_typos(स्थिर अक्षर *arg, स्थिर काष्ठा option *options)
अणु
	अगर (म_माप(arg) < 3)
		वापस;

	अगर (strstarts(arg, "no-")) अणु
		ख_लिखो(मानक_त्रुटि, " Error: did you mean `--%s` (with two dashes ?)\n", arg);
		निकास(129);
	पूर्ण

	क्रम (; options->type != OPTION_END; options++) अणु
		अगर (!options->दीर्घ_name)
			जारी;
		अगर (strstarts(options->दीर्घ_name, arg)) अणु
			ख_लिखो(मानक_त्रुटि, " Error: did you mean `--%s` (with two dashes ?)\n", arg);
			निकास(129);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम parse_options_start(काष्ठा parse_opt_ctx_t *ctx,
				पूर्णांक argc, स्थिर अक्षर **argv, पूर्णांक flags)
अणु
	स_रखो(ctx, 0, माप(*ctx));
	ctx->argc = argc - 1;
	ctx->argv = argv + 1;
	ctx->out  = argv;
	ctx->cpidx = ((flags & PARSE_OPT_KEEP_ARGV0) != 0);
	ctx->flags = flags;
	अगर ((flags & PARSE_OPT_KEEP_UNKNOWN) &&
	    (flags & PARSE_OPT_STOP_AT_NON_OPTION))
		die("STOP_AT_NON_OPTION and KEEP_UNKNOWN don't go together");
पूर्ण

अटल पूर्णांक usage_with_options_पूर्णांकernal(स्थिर अक्षर * स्थिर *,
				       स्थिर काष्ठा option *, पूर्णांक,
				       काष्ठा parse_opt_ctx_t *);

अटल पूर्णांक parse_options_step(काष्ठा parse_opt_ctx_t *ctx,
			      स्थिर काष्ठा option *options,
			      स्थिर अक्षर * स्थिर usagestr[])
अणु
	पूर्णांक पूर्णांकernal_help = !(ctx->flags & PARSE_OPT_NO_INTERNAL_HELP);
	पूर्णांक excl_लघु_opt = 1;
	स्थिर अक्षर *arg;

	/* we must reset ->opt, unknown लघु option leave it dangling */
	ctx->opt = शून्य;

	क्रम (; ctx->argc; ctx->argc--, ctx->argv++) अणु
		arg = ctx->argv[0];
		अगर (*arg != '-' || !arg[1]) अणु
			अगर (ctx->flags & PARSE_OPT_STOP_AT_NON_OPTION)
				अवरोध;
			ctx->out[ctx->cpidx++] = ctx->argv[0];
			जारी;
		पूर्ण

		अगर (arg[1] != '-') अणु
			ctx->opt = ++arg;
			अगर (पूर्णांकernal_help && *ctx->opt == 'h') अणु
				वापस usage_with_options_पूर्णांकernal(usagestr, options, 0, ctx);
			पूर्ण
			चयन (parse_लघु_opt(ctx, options)) अणु
			हाल -1:
				वापस parse_options_usage(usagestr, options, arg, 1);
			हाल -2:
				जाओ unknown;
			हाल -3:
				जाओ exclusive;
			शेष:
				अवरोध;
			पूर्ण
			अगर (ctx->opt)
				check_typos(arg, options);
			जबतक (ctx->opt) अणु
				अगर (पूर्णांकernal_help && *ctx->opt == 'h')
					वापस usage_with_options_पूर्णांकernal(usagestr, options, 0, ctx);
				arg = ctx->opt;
				चयन (parse_लघु_opt(ctx, options)) अणु
				हाल -1:
					वापस parse_options_usage(usagestr, options, arg, 1);
				हाल -2:
					/* fake a लघु option thing to hide the fact that we may have
					 * started to parse aggregated stuff
					 *
					 * This is leaky, too bad.
					 */
					ctx->argv[0] = strdup(ctx->opt - 1);
					*(अक्षर *)ctx->argv[0] = '-';
					जाओ unknown;
				हाल -3:
					जाओ exclusive;
				शेष:
					अवरोध;
				पूर्ण
			पूर्ण
			जारी;
		पूर्ण

		अगर (!arg[2]) अणु /* "--" */
			अगर (!(ctx->flags & PARSE_OPT_KEEP_DASHDASH)) अणु
				ctx->argc--;
				ctx->argv++;
			पूर्ण
			अवरोध;
		पूर्ण

		arg += 2;
		अगर (पूर्णांकernal_help && !म_भेद(arg, "help-all"))
			वापस usage_with_options_पूर्णांकernal(usagestr, options, 1, ctx);
		अगर (पूर्णांकernal_help && !म_भेद(arg, "help"))
			वापस usage_with_options_पूर्णांकernal(usagestr, options, 0, ctx);
		अगर (!म_भेद(arg, "list-opts"))
			वापस PARSE_OPT_LIST_OPTS;
		अगर (!म_भेद(arg, "list-cmds"))
			वापस PARSE_OPT_LIST_SUBCMDS;
		चयन (parse_दीर्घ_opt(ctx, arg, options)) अणु
		हाल -1:
			वापस parse_options_usage(usagestr, options, arg, 0);
		हाल -2:
			जाओ unknown;
		हाल -3:
			excl_लघु_opt = 0;
			जाओ exclusive;
		शेष:
			अवरोध;
		पूर्ण
		जारी;
unknown:
		अगर (!(ctx->flags & PARSE_OPT_KEEP_UNKNOWN))
			वापस PARSE_OPT_UNKNOWN;
		ctx->out[ctx->cpidx++] = ctx->argv[0];
		ctx->opt = शून्य;
	पूर्ण
	वापस PARSE_OPT_DONE;

exclusive:
	parse_options_usage(usagestr, options, arg, excl_लघु_opt);
	अगर ((excl_लघु_opt && ctx->excl_opt->लघु_name) ||
	    ctx->excl_opt->दीर्घ_name == शून्य) अणु
		अक्षर opt = ctx->excl_opt->लघु_name;
		parse_options_usage(शून्य, options, &opt, 1);
	पूर्ण अन्यथा अणु
		parse_options_usage(शून्य, options, ctx->excl_opt->दीर्घ_name, 0);
	पूर्ण
	वापस PARSE_OPT_HELP;
पूर्ण

अटल पूर्णांक parse_options_end(काष्ठा parse_opt_ctx_t *ctx)
अणु
	स_हटाओ(ctx->out + ctx->cpidx, ctx->argv, ctx->argc * माप(*ctx->out));
	ctx->out[ctx->cpidx + ctx->argc] = शून्य;
	वापस ctx->cpidx + ctx->argc;
पूर्ण

पूर्णांक parse_options_subcommand(पूर्णांक argc, स्थिर अक्षर **argv, स्थिर काष्ठा option *options,
			स्थिर अक्षर *स्थिर subcommands[], स्थिर अक्षर *usagestr[], पूर्णांक flags)
अणु
	काष्ठा parse_opt_ctx_t ctx;

	/* build usage string अगर it's not provided */
	अगर (subcommands && !usagestr[0]) अणु
		अक्षर *buf = शून्य;

		aम_जोड़ोf(&buf, "%s %s [<options>] {", subcmd_config.exec_name, argv[0]);

		क्रम (पूर्णांक i = 0; subcommands[i]; i++) अणु
			अगर (i)
				aम_जोड़ो(&buf, "|");
			aम_जोड़ो(&buf, subcommands[i]);
		पूर्ण
		aम_जोड़ो(&buf, "}");

		usagestr[0] = buf;
	पूर्ण

	parse_options_start(&ctx, argc, argv, flags);
	चयन (parse_options_step(&ctx, options, usagestr)) अणु
	हाल PARSE_OPT_HELP:
		निकास(129);
	हाल PARSE_OPT_DONE:
		अवरोध;
	हाल PARSE_OPT_LIST_OPTS:
		जबतक (options->type != OPTION_END) अणु
			अगर (options->दीर्घ_name)
				म_लिखो("--%s ", options->दीर्घ_name);
			options++;
		पूर्ण
		अक्षर_दो('\n');
		निकास(130);
	हाल PARSE_OPT_LIST_SUBCMDS:
		अगर (subcommands) अणु
			क्रम (पूर्णांक i = 0; subcommands[i]; i++)
				म_लिखो("%s ", subcommands[i]);
		पूर्ण
		अक्षर_दो('\n');
		निकास(130);
	शेष: /* PARSE_OPT_UNKNOWN */
		अगर (ctx.argv[0][1] == '-')
			aम_जोड़ोf(&error_buf, "unknown option `%s'",
				 ctx.argv[0] + 2);
		अन्यथा
			aम_जोड़ोf(&error_buf, "unknown switch `%c'", *ctx.opt);
		usage_with_options(usagestr, options);
	पूर्ण

	वापस parse_options_end(&ctx);
पूर्ण

पूर्णांक parse_options(पूर्णांक argc, स्थिर अक्षर **argv, स्थिर काष्ठा option *options,
		  स्थिर अक्षर * स्थिर usagestr[], पूर्णांक flags)
अणु
	वापस parse_options_subcommand(argc, argv, options, शून्य,
					(स्थिर अक्षर **) usagestr, flags);
पूर्ण

#घोषणा USAGE_OPTS_WIDTH 24
#घोषणा USAGE_GAP         2

अटल व्योम prपूर्णांक_option_help(स्थिर काष्ठा option *opts, पूर्णांक full)
अणु
	माप_प्रकार pos;
	पूर्णांक pad;

	अगर (opts->type == OPTION_GROUP) अणु
		ख_अक्षर_दो('\n', मानक_त्रुटि);
		अगर (*opts->help)
			ख_लिखो(मानक_त्रुटि, "%s\n", opts->help);
		वापस;
	पूर्ण
	अगर (!full && (opts->flags & PARSE_OPT_HIDDEN))
		वापस;
	अगर (opts->flags & PARSE_OPT_DISABLED)
		वापस;

	pos = ख_लिखो(मानक_त्रुटि, "    ");
	अगर (opts->लघु_name)
		pos += ख_लिखो(मानक_त्रुटि, "-%c", opts->लघु_name);
	अन्यथा
		pos += ख_लिखो(मानक_त्रुटि, "    ");

	अगर (opts->दीर्घ_name && opts->लघु_name)
		pos += ख_लिखो(मानक_त्रुटि, ", ");
	अगर (opts->दीर्घ_name)
		pos += ख_लिखो(मानक_त्रुटि, "--%s", opts->दीर्घ_name);

	चयन (opts->type) अणु
	हाल OPTION_ARGUMENT:
		अवरोध;
	हाल OPTION_LONG:
	हाल OPTION_ULONG:
	हाल OPTION_U64:
	हाल OPTION_INTEGER:
	हाल OPTION_UINTEGER:
		अगर (opts->flags & PARSE_OPT_OPTARG)
			अगर (opts->दीर्घ_name)
				pos += ख_लिखो(मानक_त्रुटि, "[=<n>]");
			अन्यथा
				pos += ख_लिखो(मानक_त्रुटि, "[<n>]");
		अन्यथा
			pos += ख_लिखो(मानक_त्रुटि, " <n>");
		अवरोध;
	हाल OPTION_CALLBACK:
		अगर (opts->flags & PARSE_OPT_NOARG)
			अवरोध;
		/* FALLTHROUGH */
	हाल OPTION_STRING:
		अगर (opts->argh) अणु
			अगर (opts->flags & PARSE_OPT_OPTARG)
				अगर (opts->दीर्घ_name)
					pos += ख_लिखो(मानक_त्रुटि, "[=<%s>]", opts->argh);
				अन्यथा
					pos += ख_लिखो(मानक_त्रुटि, "[<%s>]", opts->argh);
			अन्यथा
				pos += ख_लिखो(मानक_त्रुटि, " <%s>", opts->argh);
		पूर्ण अन्यथा अणु
			अगर (opts->flags & PARSE_OPT_OPTARG)
				अगर (opts->दीर्घ_name)
					pos += ख_लिखो(मानक_त्रुटि, "[=...]");
				अन्यथा
					pos += ख_लिखो(मानक_त्रुटि, "[...]");
			अन्यथा
				pos += ख_लिखो(मानक_त्रुटि, " ...");
		पूर्ण
		अवरोध;
	शेष: /* OPTION_अणुBIT,BOOLEAN,SET_UINT,SET_PTRपूर्ण */
	हाल OPTION_END:
	हाल OPTION_GROUP:
	हाल OPTION_BIT:
	हाल OPTION_BOOLEAN:
	हाल OPTION_INCR:
	हाल OPTION_SET_UINT:
	हाल OPTION_SET_PTR:
		अवरोध;
	पूर्ण

	अगर (pos <= USAGE_OPTS_WIDTH)
		pad = USAGE_OPTS_WIDTH - pos;
	अन्यथा अणु
		ख_अक्षर_दो('\n', मानक_त्रुटि);
		pad = USAGE_OPTS_WIDTH;
	पूर्ण
	ख_लिखो(मानक_त्रुटि, "%*s%s\n", pad + USAGE_GAP, "", opts->help);
	अगर (opts->flags & PARSE_OPT_NOBUILD)
		ख_लिखो(मानक_त्रुटि, "%*s(not built-in because %s)\n",
			USAGE_OPTS_WIDTH + USAGE_GAP, "",
			opts->build_opt);
पूर्ण

अटल पूर्णांक option__cmp(स्थिर व्योम *va, स्थिर व्योम *vb)
अणु
	स्थिर काष्ठा option *a = va, *b = vb;
	पूर्णांक sa = छोटे(a->लघु_name), sb = छोटे(b->लघु_name), ret;

	अगर (sa == 0)
		sa = 'z' + 1;
	अगर (sb == 0)
		sb = 'z' + 1;

	ret = sa - sb;

	अगर (ret == 0) अणु
		स्थिर अक्षर *la = a->दीर्घ_name ?: "",
			   *lb = b->दीर्घ_name ?: "";
		ret = म_भेद(la, lb);
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा option *options__order(स्थिर काष्ठा option *opts)
अणु
	पूर्णांक nr_opts = 0, len;
	स्थिर काष्ठा option *o = opts;
	काष्ठा option *ordered;

	क्रम (o = opts; o->type != OPTION_END; o++)
		++nr_opts;

	len = माप(*o) * (nr_opts + 1);
	ordered = दो_स्मृति(len);
	अगर (!ordered)
		जाओ out;
	स_नकल(ordered, opts, len);

	क्विक(ordered, nr_opts, माप(*o), option__cmp);
out:
	वापस ordered;
पूर्ण

अटल bool option__in_argv(स्थिर काष्ठा option *opt, स्थिर काष्ठा parse_opt_ctx_t *ctx)
अणु
	पूर्णांक i;

	क्रम (i = 1; i < ctx->argc; ++i) अणु
		स्थिर अक्षर *arg = ctx->argv[i];

		अगर (arg[0] != '-') अणु
			अगर (arg[1] == '\0') अणु
				अगर (arg[0] == opt->लघु_name)
					वापस true;
				जारी;
			पूर्ण

			अगर (opt->दीर्घ_name && म_भेद(opt->दीर्घ_name, arg) == 0)
				वापस true;

			अगर (opt->help && strहालstr(opt->help, arg) != शून्य)
				वापस true;

			जारी;
		पूर्ण

		अगर (arg[1] == opt->लघु_name ||
		    (arg[1] == '-' && opt->दीर्घ_name && म_भेद(opt->दीर्घ_name, arg + 2) == 0))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक usage_with_options_पूर्णांकernal(स्थिर अक्षर * स्थिर *usagestr,
				       स्थिर काष्ठा option *opts, पूर्णांक full,
				       काष्ठा parse_opt_ctx_t *ctx)
अणु
	काष्ठा option *ordered;

	अगर (!usagestr)
		वापस PARSE_OPT_HELP;

	setup_pager();

	अगर (error_buf) अणु
		ख_लिखो(मानक_त्रुटि, "  Error: %s\n", error_buf);
		zमुक्त(&error_buf);
	पूर्ण

	ख_लिखो(मानक_त्रुटि, "\n Usage: %s\n", *usagestr++);
	जबतक (*usagestr && **usagestr)
		ख_लिखो(मानक_त्रुटि, "    or: %s\n", *usagestr++);
	जबतक (*usagestr) अणु
		ख_लिखो(मानक_त्रुटि, "%s%s\n",
				**usagestr ? "    " : "",
				*usagestr);
		usagestr++;
	पूर्ण

	अगर (opts->type != OPTION_GROUP)
		ख_अक्षर_दो('\n', मानक_त्रुटि);

	ordered = options__order(opts);
	अगर (ordered)
		opts = ordered;

	क्रम (  ; opts->type != OPTION_END; opts++) अणु
		अगर (ctx && ctx->argc > 1 && !option__in_argv(opts, ctx))
			जारी;
		prपूर्णांक_option_help(opts, full);
	पूर्ण

	ख_अक्षर_दो('\n', मानक_त्रुटि);

	मुक्त(ordered);

	वापस PARSE_OPT_HELP;
पूर्ण

व्योम usage_with_options(स्थिर अक्षर * स्थिर *usagestr,
			स्थिर काष्ठा option *opts)
अणु
	usage_with_options_पूर्णांकernal(usagestr, opts, 0, शून्य);
	निकास(129);
पूर्ण

व्योम usage_with_options_msg(स्थिर अक्षर * स्थिर *usagestr,
			    स्थिर काष्ठा option *opts, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;
	अक्षर *पंचांगp = error_buf;

	बहु_शुरू(ap, fmt);
	अगर (vaप्र_लिखो(&error_buf, fmt, ap) == -1)
		die("vasprintf failed");
	बहु_पूर्ण(ap);

	मुक्त(पंचांगp);

	usage_with_options_पूर्णांकernal(usagestr, opts, 0, शून्य);
	निकास(129);
पूर्ण

पूर्णांक parse_options_usage(स्थिर अक्षर * स्थिर *usagestr,
			स्थिर काष्ठा option *opts,
			स्थिर अक्षर *optstr, bool लघु_opt)
अणु
	अगर (!usagestr)
		जाओ opt;

	ख_लिखो(मानक_त्रुटि, "\n Usage: %s\n", *usagestr++);
	जबतक (*usagestr && **usagestr)
		ख_लिखो(मानक_त्रुटि, "    or: %s\n", *usagestr++);
	जबतक (*usagestr) अणु
		ख_लिखो(मानक_त्रुटि, "%s%s\n",
				**usagestr ? "    " : "",
				*usagestr);
		usagestr++;
	पूर्ण
	ख_अक्षर_दो('\n', मानक_त्रुटि);

opt:
	क्रम (  ; opts->type != OPTION_END; opts++) अणु
		अगर (लघु_opt) अणु
			अगर (opts->लघु_name == *optstr) अणु
				prपूर्णांक_option_help(opts, 0);
				अवरोध;
			पूर्ण
			जारी;
		पूर्ण

		अगर (opts->दीर्घ_name == शून्य)
			जारी;

		अगर (strstarts(opts->दीर्घ_name, optstr))
			prपूर्णांक_option_help(opts, 0);
		अगर (strstarts("no-", optstr) &&
		    strstarts(opts->दीर्घ_name, optstr + 3))
			prपूर्णांक_option_help(opts, 0);
	पूर्ण

	वापस PARSE_OPT_HELP;
पूर्ण


पूर्णांक parse_opt_verbosity_cb(स्थिर काष्ठा option *opt,
			   स्थिर अक्षर *arg __maybe_unused,
			   पूर्णांक unset)
अणु
	पूर्णांक *target = opt->value;

	अगर (unset)
		/* --no-quiet, --no-verbose */
		*target = 0;
	अन्यथा अगर (opt->लघु_name == 'v') अणु
		अगर (*target >= 0)
			(*target)++;
		अन्यथा
			*target = 1;
	पूर्ण अन्यथा अणु
		अगर (*target <= 0)
			(*target)--;
		अन्यथा
			*target = -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा option *
find_option(काष्ठा option *opts, पूर्णांक लघुopt, स्थिर अक्षर *दीर्घopt)
अणु
	क्रम (; opts->type != OPTION_END; opts++) अणु
		अगर ((लघुopt && opts->लघु_name == लघुopt) ||
		    (opts->दीर्घ_name && दीर्घopt &&
		     !म_भेद(opts->दीर्घ_name, दीर्घopt)))
			वापस opts;
	पूर्ण
	वापस शून्य;
पूर्ण

व्योम set_option_flag(काष्ठा option *opts, पूर्णांक लघुopt, स्थिर अक्षर *दीर्घopt,
		     पूर्णांक flag)
अणु
	काष्ठा option *opt = find_option(opts, लघुopt, दीर्घopt);

	अगर (opt)
		opt->flags |= flag;
	वापस;
पूर्ण

व्योम set_option_nobuild(काष्ठा option *opts, पूर्णांक लघुopt,
			स्थिर अक्षर *दीर्घopt,
			स्थिर अक्षर *build_opt,
			bool can_skip)
अणु
	काष्ठा option *opt = find_option(opts, लघुopt, दीर्घopt);

	अगर (!opt)
		वापस;

	opt->flags |= PARSE_OPT_NOBUILD;
	opt->flags |= can_skip ? PARSE_OPT_CANSKIP : 0;
	opt->build_opt = build_opt;
पूर्ण
