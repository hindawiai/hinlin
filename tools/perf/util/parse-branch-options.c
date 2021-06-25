<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "util/debug.h"
#समावेश "util/event.h"
#समावेश <subcmd/parse-options.h>
#समावेश "util/parse-branch-options.h"
#समावेश <मानककोष.स>
#समावेश <माला.स>

#घोषणा BRANCH_OPT(n, m) \
	अणु .name = n, .mode = (m) पूर्ण

#घोषणा BRANCH_END अणु .name = शून्य पूर्ण

काष्ठा branch_mode अणु
	स्थिर अक्षर *name;
	पूर्णांक mode;
पूर्ण;

अटल स्थिर काष्ठा branch_mode branch_modes[] = अणु
	BRANCH_OPT("u", PERF_SAMPLE_BRANCH_USER),
	BRANCH_OPT("k", PERF_SAMPLE_BRANCH_KERNEL),
	BRANCH_OPT("hv", PERF_SAMPLE_BRANCH_HV),
	BRANCH_OPT("any", PERF_SAMPLE_BRANCH_ANY),
	BRANCH_OPT("any_call", PERF_SAMPLE_BRANCH_ANY_CALL),
	BRANCH_OPT("any_ret", PERF_SAMPLE_BRANCH_ANY_RETURN),
	BRANCH_OPT("ind_call", PERF_SAMPLE_BRANCH_IND_CALL),
	BRANCH_OPT("abort_tx", PERF_SAMPLE_BRANCH_ABORT_TX),
	BRANCH_OPT("in_tx", PERF_SAMPLE_BRANCH_IN_TX),
	BRANCH_OPT("no_tx", PERF_SAMPLE_BRANCH_NO_TX),
	BRANCH_OPT("cond", PERF_SAMPLE_BRANCH_COND),
	BRANCH_OPT("ind_jmp", PERF_SAMPLE_BRANCH_IND_JUMP),
	BRANCH_OPT("call", PERF_SAMPLE_BRANCH_CALL),
	BRANCH_OPT("save_type", PERF_SAMPLE_BRANCH_TYPE_SAVE),
	BRANCH_OPT("stack", PERF_SAMPLE_BRANCH_CALL_STACK),
	BRANCH_END
पूर्ण;

पूर्णांक parse_branch_str(स्थिर अक्षर *str, __u64 *mode)
अणु
#घोषणा ONLY_PLM \
	(PERF_SAMPLE_BRANCH_USER	|\
	 PERF_SAMPLE_BRANCH_KERNEL	|\
	 PERF_SAMPLE_BRANCH_HV)

	पूर्णांक ret = 0;
	अक्षर *p, *s;
	अक्षर *os = शून्य;
	स्थिर काष्ठा branch_mode *br;

	अगर (str == शून्य) अणु
		*mode = PERF_SAMPLE_BRANCH_ANY;
		वापस 0;
	पूर्ण

	/* because str is पढ़ो-only */
	s = os = strdup(str);
	अगर (!s)
		वापस -1;

	क्रम (;;) अणु
		p = म_अक्षर(s, ',');
		अगर (p)
			*p = '\0';

		क्रम (br = branch_modes; br->name; br++) अणु
			अगर (!strहालcmp(s, br->name))
				अवरोध;
		पूर्ण
		अगर (!br->name) अणु
			ret = -1;
			pr_warning("unknown branch filter %s,"
				    " check man page\n", s);
			जाओ error;
		पूर्ण

		*mode |= br->mode;

		अगर (!p)
			अवरोध;

		s = p + 1;
	पूर्ण

	/* शेष to any branch */
	अगर ((*mode & ~ONLY_PLM) == 0) अणु
		*mode = PERF_SAMPLE_BRANCH_ANY;
	पूर्ण
error:
	मुक्त(os);
	वापस ret;
पूर्ण

पूर्णांक
parse_branch_stack(स्थिर काष्ठा option *opt, स्थिर अक्षर *str, पूर्णांक unset)
अणु
	__u64 *mode = (__u64 *)opt->value;

	अगर (unset)
		वापस 0;

	/*
	 * cannot set it twice, -b + --branch-filter क्रम instance
	 */
	अगर (*mode)
		वापस -1;

	वापस parse_branch_str(str, mode);
पूर्ण
