<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <stdbool.h>
#समावेश <मानककोष.स>
#समावेश <मानक_निवेशt.h>
#समावेश <माला.स>
#समावेश <मानकपन.स>
#समावेश "util/debug.h"
#समावेश <subcmd/parse-options.h>
#समावेश "util/perf_regs.h"
#समावेश "util/parse-regs-options.h"

अटल पूर्णांक
__parse_regs(स्थिर काष्ठा option *opt, स्थिर अक्षर *str, पूर्णांक unset, bool पूर्णांकr)
अणु
	uपूर्णांक64_t *mode = (uपूर्णांक64_t *)opt->value;
	स्थिर काष्ठा sample_reg *r = शून्य;
	अक्षर *s, *os = शून्य, *p;
	पूर्णांक ret = -1;
	uपूर्णांक64_t mask;

	अगर (unset)
		वापस 0;

	/*
	 * cannot set it twice
	 */
	अगर (*mode)
		वापस -1;

	अगर (पूर्णांकr)
		mask = arch__पूर्णांकr_reg_mask();
	अन्यथा
		mask = arch__user_reg_mask();

	/* str may be शून्य in हाल no arg is passed to -I */
	अगर (str) अणु
		/* because str is पढ़ो-only */
		s = os = strdup(str);
		अगर (!s)
			वापस -1;

		क्रम (;;) अणु
			p = म_अक्षर(s, ',');
			अगर (p)
				*p = '\0';

			अगर (!म_भेद(s, "?")) अणु
				ख_लिखो(मानक_त्रुटि, "available registers: ");
#अगर_घोषित HAVE_PERF_REGS_SUPPORT
				क्रम (r = sample_reg_masks; r->name; r++) अणु
					अगर (r->mask & mask)
						ख_लिखो(मानक_त्रुटि, "%s ", r->name);
				पूर्ण
#पूर्ण_अगर
				ख_अक्षर_दो('\n', मानक_त्रुटि);
				/* just prपूर्णांकing available regs */
				जाओ error;
			पूर्ण
#अगर_घोषित HAVE_PERF_REGS_SUPPORT
			क्रम (r = sample_reg_masks; r->name; r++) अणु
				अगर ((r->mask & mask) && !strहालcmp(s, r->name))
					अवरोध;
			पूर्ण
#पूर्ण_अगर
			अगर (!r || !r->name) अणु
				ui__warning("Unknown register \"%s\", check man page or run \"perf record %s?\"\n",
					    s, पूर्णांकr ? "-I" : "--user-regs=");
				जाओ error;
			पूर्ण

			*mode |= r->mask;

			अगर (!p)
				अवरोध;

			s = p + 1;
		पूर्ण
	पूर्ण
	ret = 0;

	/* शेष to all possible regs */
	अगर (*mode == 0)
		*mode = mask;
error:
	मुक्त(os);
	वापस ret;
पूर्ण

पूर्णांक
parse_user_regs(स्थिर काष्ठा option *opt, स्थिर अक्षर *str, पूर्णांक unset)
अणु
	वापस __parse_regs(opt, str, unset, false);
पूर्ण

पूर्णांक
parse_पूर्णांकr_regs(स्थिर काष्ठा option *opt, स्थिर अक्षर *str, पूर्णांक unset)
अणु
	वापस __parse_regs(opt, str, unset, true);
पूर्ण
