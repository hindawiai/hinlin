<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SUBCMD_PARSE_OPTIONS_H
#घोषणा __SUBCMD_PARSE_OPTIONS_H

#समावेश <linux/kernel.h>
#समावेश <stdbool.h>
#समावेश <मानक_निवेशt.h>

#अगर_अघोषित NORETURN
#घोषणा NORETURN __attribute__((__noवापस__))
#पूर्ण_अगर

क्रमागत parse_opt_type अणु
	/* special types */
	OPTION_END,
	OPTION_ARGUMENT,
	OPTION_GROUP,
	/* options with no arguments */
	OPTION_BIT,
	OPTION_BOOLEAN,
	OPTION_INCR,
	OPTION_SET_UINT,
	OPTION_SET_PTR,
	/* options with arguments (usually) */
	OPTION_STRING,
	OPTION_INTEGER,
	OPTION_LONG,
	OPTION_ULONG,
	OPTION_CALLBACK,
	OPTION_U64,
	OPTION_UINTEGER,
पूर्ण;

क्रमागत parse_opt_flags अणु
	PARSE_OPT_KEEP_DASHDASH = 1,
	PARSE_OPT_STOP_AT_NON_OPTION = 2,
	PARSE_OPT_KEEP_ARGV0 = 4,
	PARSE_OPT_KEEP_UNKNOWN = 8,
	PARSE_OPT_NO_INTERNAL_HELP = 16,
पूर्ण;

क्रमागत parse_opt_option_flags अणु
	PARSE_OPT_OPTARG  = 1,
	PARSE_OPT_NOARG   = 2,
	PARSE_OPT_NONEG   = 4,
	PARSE_OPT_HIDDEN  = 8,
	PARSE_OPT_LASTARG_DEFAULT = 16,
	PARSE_OPT_DISABLED = 32,
	PARSE_OPT_EXCLUSIVE = 64,
	PARSE_OPT_NOEMPTY  = 128,
	PARSE_OPT_NOBUILD  = 256,
	PARSE_OPT_CANSKIP  = 512,
पूर्ण;

काष्ठा option;
प्रकार पूर्णांक parse_opt_cb(स्थिर काष्ठा option *, स्थिर अक्षर *arg, पूर्णांक unset);

/*
 * `type`::
 *   holds the type of the option, you must have an OPTION_END last in your
 *   array.
 *
 * `लघु_name`::
 *   the अक्षरacter to use as a लघु option name, '\0' अगर none.
 *
 * `दीर्घ_name`::
 *   the दीर्घ option name, without the leading dashes, शून्य अगर none.
 *
 * `value`::
 *   stores poपूर्णांकers to the values to be filled.
 *
 * `argh`::
 *   token to explain the kind of argument this option wants. Keep it
 *   homogeneous across the repository.
 *
 * `help`::
 *   the लघु help associated to what the option करोes.
 *   Must never be शून्य (except क्रम OPTION_END).
 *   OPTION_GROUP uses this poपूर्णांकer to store the group header.
 *
 * `flags`::
 *   mask of parse_opt_option_flags.
 *   PARSE_OPT_OPTARG: says that the argument is optional (not क्रम BOOLEANs)
 *   PARSE_OPT_NOARG: says that this option takes no argument, क्रम CALLBACKs
 *   PARSE_OPT_NONEG: says that this option cannot be negated
 *   PARSE_OPT_HIDDEN this option is skipped in the शेष usage, showed in
 *                    the दीर्घ one.
 *
 * `callback`::
 *   poपूर्णांकer to the callback to use क्रम OPTION_CALLBACK.
 *
 * `defval`::
 *   शेष value to fill (*->value) with क्रम PARSE_OPT_OPTARG.
 *   OPTION_अणुBIT,SET_UINT,SET_PTRपूर्ण store the अणुmask,पूर्णांकeger,poपूर्णांकerपूर्ण to put in
 *   the value when met.
 *   CALLBACKS can use it like they want.
 *
 * `set`::
 *   whether an option was set by the user
 */
काष्ठा option अणु
	क्रमागत parse_opt_type type;
	पूर्णांक लघु_name;
	स्थिर अक्षर *दीर्घ_name;
	व्योम *value;
	स्थिर अक्षर *argh;
	स्थिर अक्षर *help;
	स्थिर अक्षर *build_opt;

	पूर्णांक flags;
	parse_opt_cb *callback;
	पूर्णांकptr_t defval;
	bool *set;
	व्योम *data;
	स्थिर काष्ठा option *parent;
पूर्ण;

#घोषणा check_vtype(v, type) ( BUILD_BUG_ON_ZERO(!__builtin_types_compatible_p(typeof(v), type)) + v )

#घोषणा OPT_END()                   अणु .type = OPTION_END पूर्ण
#घोषणा OPT_PARENT(p)               अणु .type = OPTION_END, .parent = (p) पूर्ण
#घोषणा OPT_ARGUMENT(l, h)          अणु .type = OPTION_ARGUMENT, .दीर्घ_name = (l), .help = (h) पूर्ण
#घोषणा OPT_GROUP(h)                अणु .type = OPTION_GROUP, .help = (h) पूर्ण
#घोषणा OPT_BIT(s, l, v, h, b)      अणु .type = OPTION_BIT, .लघु_name = (s), .दीर्घ_name = (l), .value = check_vtype(v, पूर्णांक *), .help = (h), .defval = (b) पूर्ण
#घोषणा OPT_BOOLEAN(s, l, v, h)     अणु .type = OPTION_BOOLEAN, .लघु_name = (s), .दीर्घ_name = (l), .value = check_vtype(v, bool *), .help = (h) पूर्ण
#घोषणा OPT_BOOLEAN_FLAG(s, l, v, h, f)     अणु .type = OPTION_BOOLEAN, .लघु_name = (s), .दीर्घ_name = (l), .value = check_vtype(v, bool *), .help = (h), .flags = (f) पूर्ण
#घोषणा OPT_BOOLEAN_SET(s, l, v, os, h) \
	अणु .type = OPTION_BOOLEAN, .लघु_name = (s), .दीर्घ_name = (l), \
	.value = check_vtype(v, bool *), .help = (h), \
	.set = check_vtype(os, bool *)पूर्ण
#घोषणा OPT_INCR(s, l, v, h)        अणु .type = OPTION_INCR, .लघु_name = (s), .दीर्घ_name = (l), .value = check_vtype(v, पूर्णांक *), .help = (h) पूर्ण
#घोषणा OPT_SET_UINT(s, l, v, h, i)  अणु .type = OPTION_SET_UINT, .लघु_name = (s), .दीर्घ_name = (l), .value = check_vtype(v, अचिन्हित पूर्णांक *), .help = (h), .defval = (i) पूर्ण
#घोषणा OPT_SET_PTR(s, l, v, h, p)  अणु .type = OPTION_SET_PTR, .लघु_name = (s), .दीर्घ_name = (l), .value = (v), .help = (h), .defval = (p) पूर्ण
#घोषणा OPT_INTEGER(s, l, v, h)     अणु .type = OPTION_INTEGER, .लघु_name = (s), .दीर्घ_name = (l), .value = check_vtype(v, पूर्णांक *), .help = (h) पूर्ण
#घोषणा OPT_UINTEGER(s, l, v, h)    अणु .type = OPTION_UINTEGER, .लघु_name = (s), .दीर्घ_name = (l), .value = check_vtype(v, अचिन्हित पूर्णांक *), .help = (h) पूर्ण
#घोषणा OPT_LONG(s, l, v, h)        अणु .type = OPTION_LONG, .लघु_name = (s), .दीर्घ_name = (l), .value = check_vtype(v, दीर्घ *), .help = (h) पूर्ण
#घोषणा OPT_ULONG(s, l, v, h)        अणु .type = OPTION_ULONG, .लघु_name = (s), .दीर्घ_name = (l), .value = check_vtype(v, अचिन्हित दीर्घ *), .help = (h) पूर्ण
#घोषणा OPT_U64(s, l, v, h)         अणु .type = OPTION_U64, .लघु_name = (s), .दीर्घ_name = (l), .value = check_vtype(v, u64 *), .help = (h) पूर्ण
#घोषणा OPT_STRING(s, l, v, a, h)   अणु .type = OPTION_STRING,  .लघु_name = (s), .दीर्घ_name = (l), .value = check_vtype(v, स्थिर अक्षर **), .argh = (a), .help = (h) पूर्ण
#घोषणा OPT_STRING_OPTARG(s, l, v, a, h, d) \
	अणु .type = OPTION_STRING,  .लघु_name = (s), .दीर्घ_name = (l), \
	  .value = check_vtype(v, स्थिर अक्षर **), .argh =(a), .help = (h), \
	  .flags = PARSE_OPT_OPTARG, .defval = (पूर्णांकptr_t)(d) पूर्ण
#घोषणा OPT_STRING_OPTARG_SET(s, l, v, os, a, h, d) \
	अणु .type = OPTION_STRING, .लघु_name = (s), .दीर्घ_name = (l), \
	  .value = check_vtype(v, स्थिर अक्षर **), .argh = (a), .help = (h), \
	  .flags = PARSE_OPT_OPTARG, .defval = (पूर्णांकptr_t)(d), \
	  .set = check_vtype(os, bool *)पूर्ण
#घोषणा OPT_STRING_NOEMPTY(s, l, v, a, h)   अणु .type = OPTION_STRING,  .लघु_name = (s), .दीर्घ_name = (l), .value = check_vtype(v, स्थिर अक्षर **), .argh = (a), .help = (h), .flags = PARSE_OPT_NOEMPTYपूर्ण
#घोषणा OPT_DATE(s, l, v, h) \
	अणु .type = OPTION_CALLBACK, .लघु_name = (s), .दीर्घ_name = (l), .value = (v), .argh = "time", .help = (h), .callback = parse_opt_approxidate_cb पूर्ण
#घोषणा OPT_CALLBACK(s, l, v, a, h, f) \
	अणु .type = OPTION_CALLBACK, .लघु_name = (s), .दीर्घ_name = (l), .value = (v), .argh = (a), .help = (h), .callback = (f) पूर्ण
#घोषणा OPT_CALLBACK_SET(s, l, v, os, a, h, f) \
	अणु .type = OPTION_CALLBACK, .लघु_name = (s), .दीर्घ_name = (l), .value = (v), .argh = (a), .help = (h), .callback = (f), .set = check_vtype(os, bool *)पूर्ण
#घोषणा OPT_CALLBACK_NOOPT(s, l, v, a, h, f) \
	अणु .type = OPTION_CALLBACK, .लघु_name = (s), .दीर्घ_name = (l), .value = (v), .argh = (a), .help = (h), .callback = (f), .flags = PARSE_OPT_NOARG पूर्ण
#घोषणा OPT_CALLBACK_DEFAULT(s, l, v, a, h, f, d) \
	अणु .type = OPTION_CALLBACK, .लघु_name = (s), .दीर्घ_name = (l), .value = (v), .argh = (a), .help = (h), .callback = (f), .defval = (पूर्णांकptr_t)d, .flags = PARSE_OPT_LASTARG_DEFAULT पूर्ण
#घोषणा OPT_CALLBACK_DEFAULT_NOOPT(s, l, v, a, h, f, d) \
	अणु .type = OPTION_CALLBACK, .लघु_name = (s), .दीर्घ_name = (l),\
	.value = (v), .arg = (a), .help = (h), .callback = (f), .defval = (पूर्णांकptr_t)d,\
	.flags = PARSE_OPT_LASTARG_DEFAULT | PARSE_OPT_NOARGपूर्ण
#घोषणा OPT_CALLBACK_OPTARG(s, l, v, d, a, h, f) \
	अणु .type = OPTION_CALLBACK, .लघु_name = (s), .दीर्घ_name = (l), \
	  .value = (v), .argh = (a), .help = (h), .callback = (f), \
	  .flags = PARSE_OPT_OPTARG, .data = (d) पूर्ण

/* parse_options() will filter out the processed options and leave the
 * non-option argments in argv[].
 * Returns the number of arguments left in argv[].
 *
 * NOTE: parse_options() and parse_options_subcommand() may call निकास() in the
 * हाल of an error (or क्रम 'special' options like --list-cmds or --list-opts).
 */
बाह्य पूर्णांक parse_options(पूर्णांक argc, स्थिर अक्षर **argv,
                         स्थिर काष्ठा option *options,
                         स्थिर अक्षर * स्थिर usagestr[], पूर्णांक flags);

बाह्य पूर्णांक parse_options_subcommand(पूर्णांक argc, स्थिर अक्षर **argv,
				स्थिर काष्ठा option *options,
				स्थिर अक्षर *स्थिर subcommands[],
				स्थिर अक्षर *usagestr[], पूर्णांक flags);

बाह्य NORETURN व्योम usage_with_options(स्थिर अक्षर * स्थिर *usagestr,
                                        स्थिर काष्ठा option *options);
बाह्य NORETURN __attribute__((क्रमmat(म_लिखो,3,4)))
व्योम usage_with_options_msg(स्थिर अक्षर * स्थिर *usagestr,
			    स्थिर काष्ठा option *options,
			    स्थिर अक्षर *fmt, ...);

/*----- incremantal advanced APIs -----*/

क्रमागत अणु
	PARSE_OPT_HELP = -1,
	PARSE_OPT_DONE,
	PARSE_OPT_LIST_OPTS,
	PARSE_OPT_LIST_SUBCMDS,
	PARSE_OPT_UNKNOWN,
पूर्ण;

/*
 * It's okay क्रम the caller to consume argv/argc in the usual way.
 * Other fields of that काष्ठाure are निजी to parse-options and should not
 * be modअगरied in any way.
 */
काष्ठा parse_opt_ctx_t अणु
	स्थिर अक्षर **argv;
	स्थिर अक्षर **out;
	पूर्णांक argc, cpidx;
	स्थिर अक्षर *opt;
	स्थिर काष्ठा option *excl_opt;
	पूर्णांक flags;
पूर्ण;

बाह्य पूर्णांक parse_options_usage(स्थिर अक्षर * स्थिर *usagestr,
			       स्थिर काष्ठा option *opts,
			       स्थिर अक्षर *optstr,
			       bool लघु_opt);


/*----- some often used options -----*/
बाह्य पूर्णांक parse_opt_abbrev_cb(स्थिर काष्ठा option *, स्थिर अक्षर *, पूर्णांक);
बाह्य पूर्णांक parse_opt_approxidate_cb(स्थिर काष्ठा option *, स्थिर अक्षर *, पूर्णांक);
बाह्य पूर्णांक parse_opt_verbosity_cb(स्थिर काष्ठा option *, स्थिर अक्षर *, पूर्णांक);

#घोषणा OPT__VERBOSE(var)  OPT_BOOLEAN('v', "verbose", (var), "be verbose")
#घोषणा OPT__QUIET(var)    OPT_BOOLEAN('q', "quiet",   (var), "be quiet")
#घोषणा OPT__VERBOSITY(var) \
	अणु OPTION_CALLBACK, 'v', "verbose", (var), शून्य, "be more verbose", \
	  PARSE_OPT_NOARG, &parse_opt_verbosity_cb, 0 पूर्ण, \
	अणु OPTION_CALLBACK, 'q', "quiet", (var), शून्य, "be more quiet", \
	  PARSE_OPT_NOARG, &parse_opt_verbosity_cb, 0 पूर्ण
#घोषणा OPT__DRY_RUN(var)  OPT_BOOLEAN('n', "dry-run", (var), "dry run")
#घोषणा OPT__ABBREV(var)  \
	अणु OPTION_CALLBACK, 0, "abbrev", (var), "n", \
	  "use <n> digits to display SHA-1s", \
	  PARSE_OPT_OPTARG, &parse_opt_abbrev_cb, 0 पूर्ण

बाह्य स्थिर अक्षर *parse_options_fix_filename(स्थिर अक्षर *prefix, स्थिर अक्षर *file);

व्योम set_option_flag(काष्ठा option *opts, पूर्णांक sopt, स्थिर अक्षर *lopt, पूर्णांक flag);
व्योम set_option_nobuild(काष्ठा option *opts, पूर्णांक लघुopt, स्थिर अक्षर *दीर्घopt,
			स्थिर अक्षर *build_opt, bool can_skip);

#पूर्ण_अगर /* __SUBCMD_PARSE_OPTIONS_H */
