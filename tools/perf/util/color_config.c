<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <subcmd/pager.h>
#समावेश <माला.स>
#समावेश "config.h"
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश "color.h"
#समावेश <गणित.स>
#समावेश <unistd.h>

पूर्णांक perf_config_colorbool(स्थिर अक्षर *var, स्थिर अक्षर *value, पूर्णांक मानक_निकास_is_tty)
अणु
	अगर (value) अणु
		अगर (!strहालcmp(value, "never"))
			वापस 0;
		अगर (!strहालcmp(value, "always"))
			वापस 1;
		अगर (!strहालcmp(value, "auto"))
			जाओ स्वतः_color;
	पूर्ण

	/* Missing or explicit false to turn off colorization */
	अगर (!perf_config_bool(var, value))
		वापस 0;

	/* any normal truth value शेषs to 'auto' */
 स्वतः_color:
	अगर (मानक_निकास_is_tty < 0)
		मानक_निकास_is_tty = isatty(1);
	अगर (मानक_निकास_is_tty || pager_in_use()) अणु
		अक्षर *term = दो_पर्या("TERM");
		अगर (term && म_भेद(term, "dumb"))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक perf_color_शेष_config(स्थिर अक्षर *var, स्थिर अक्षर *value,
			      व्योम *cb __maybe_unused)
अणु
	अगर (!म_भेद(var, "color.ui")) अणु
		perf_use_color_शेष = perf_config_colorbool(var, value, -1);
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण
