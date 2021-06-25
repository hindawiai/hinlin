<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <subcmd/pager.h>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश "color.h"
#समावेश <गणित.स>
#समावेश <unistd.h>

पूर्णांक perf_use_color_शेष = -1;

अटल पूर्णांक __color_vsnम_लिखो(अक्षर *bf, माप_प्रकार size, स्थिर अक्षर *color,
			     स्थिर अक्षर *fmt, बहु_सूची args, स्थिर अक्षर *trail)
अणु
	पूर्णांक r = 0;

	/*
	 * Auto-detect:
	 */
	अगर (perf_use_color_शेष < 0) अणु
		अगर (isatty(1) || pager_in_use())
			perf_use_color_शेष = 1;
		अन्यथा
			perf_use_color_शेष = 0;
	पूर्ण

	अगर (perf_use_color_शेष && *color)
		r += scnम_लिखो(bf, size, "%s", color);
	r += vscnम_लिखो(bf + r, size - r, fmt, args);
	अगर (perf_use_color_शेष && *color)
		r += scnम_लिखो(bf + r, size - r, "%s", PERF_COLOR_RESET);
	अगर (trail)
		r += scnम_लिखो(bf + r, size - r, "%s", trail);
	वापस r;
पूर्ण

/* Colors are not included in वापस value */
अटल पूर्णांक __color_भख_लिखो(खाता *fp, स्थिर अक्षर *color, स्थिर अक्षर *fmt,
		बहु_सूची args)
अणु
	पूर्णांक r = 0;

	/*
	 * Auto-detect:
	 */
	अगर (perf_use_color_शेष < 0) अणु
		अगर (isatty(fileno(fp)) || pager_in_use())
			perf_use_color_शेष = 1;
		अन्यथा
			perf_use_color_शेष = 0;
	पूर्ण

	अगर (perf_use_color_शेष && *color)
		ख_लिखो(fp, "%s", color);
	r += भख_लिखो(fp, fmt, args);
	अगर (perf_use_color_शेष && *color)
		ख_लिखो(fp, "%s", PERF_COLOR_RESET);
	वापस r;
पूर्ण

पूर्णांक color_vsnम_लिखो(अक्षर *bf, माप_प्रकार size, स्थिर अक्षर *color,
		    स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	वापस __color_vsnम_लिखो(bf, size, color, fmt, args, शून्य);
पूर्ण

पूर्णांक color_भख_लिखो(खाता *fp, स्थिर अक्षर *color, स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	वापस __color_भख_लिखो(fp, color, fmt, args);
पूर्ण

पूर्णांक color_snम_लिखो(अक्षर *bf, माप_प्रकार size, स्थिर अक्षर *color,
		   स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक r;

	बहु_शुरू(args, fmt);
	r = color_vsnम_लिखो(bf, size, color, fmt, args);
	बहु_पूर्ण(args);
	वापस r;
पूर्ण

पूर्णांक color_ख_लिखो(खाता *fp, स्थिर अक्षर *color, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक r;

	बहु_शुरू(args, fmt);
	r = color_भख_लिखो(fp, color, fmt, args);
	बहु_पूर्ण(args);
	वापस r;
पूर्ण

/*
 * This function splits the buffer by newlines and colors the lines inभागidually.
 *
 * Returns 0 on success.
 */
पूर्णांक color_ख_डालो_lines(खाता *fp, स्थिर अक्षर *color,
		माप_प्रकार count, स्थिर अक्षर *buf)
अणु
	अगर (!*color)
		वापस ख_डालो(buf, count, 1, fp) != 1;

	जबतक (count) अणु
		अक्षर *p = स_प्रथम(buf, '\n', count);

		अगर (p != buf && (ख_माला_दो(color, fp) < 0 ||
				ख_डालो(buf, p ? (माप_प्रकार)(p - buf) : count, 1, fp) != 1 ||
				ख_माला_दो(PERF_COLOR_RESET, fp) < 0))
			वापस -1;
		अगर (!p)
			वापस 0;
		अगर (ख_अक्षर_दो('\n', fp) < 0)
			वापस -1;
		count -= p + 1 - buf;
		buf = p + 1;
	पूर्ण
	वापस 0;
पूर्ण

स्थिर अक्षर *get_percent_color(द्विगुन percent)
अणु
	स्थिर अक्षर *color = PERF_COLOR_NORMAL;

	/*
	 * We color high-overhead entries in red, mid-overhead
	 * entries in green - and keep the low overhead places
	 * normal:
	 */
	अगर (भ_असल(percent) >= MIN_RED)
		color = PERF_COLOR_RED;
	अन्यथा अणु
		अगर (भ_असल(percent) > MIN_GREEN)
			color = PERF_COLOR_GREEN;
	पूर्ण
	वापस color;
पूर्ण

पूर्णांक percent_color_ख_लिखो(खाता *fp, स्थिर अक्षर *fmt, द्विगुन percent)
अणु
	पूर्णांक r;
	स्थिर अक्षर *color;

	color = get_percent_color(percent);
	r = color_ख_लिखो(fp, color, fmt, percent);

	वापस r;
पूर्ण

पूर्णांक value_color_snम_लिखो(अक्षर *bf, माप_प्रकार size, स्थिर अक्षर *fmt, द्विगुन value)
अणु
	स्थिर अक्षर *color = get_percent_color(value);
	वापस color_snम_लिखो(bf, size, color, fmt, value);
पूर्ण

पूर्णांक percent_color_snम_लिखो(अक्षर *bf, माप_प्रकार size, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	द्विगुन percent;

	बहु_शुरू(args, fmt);
	percent = बहु_तर्क(args, द्विगुन);
	बहु_पूर्ण(args);
	वापस value_color_snम_लिखो(bf, size, fmt, percent);
पूर्ण

पूर्णांक percent_color_len_snम_लिखो(अक्षर *bf, माप_प्रकार size, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक len;
	द्विगुन percent;
	स्थिर अक्षर *color;

	बहु_शुरू(args, fmt);
	len = बहु_तर्क(args, पूर्णांक);
	percent = बहु_तर्क(args, द्विगुन);
	बहु_पूर्ण(args);

	color = get_percent_color(percent);
	वापस color_snम_लिखो(bf, size, color, fmt, len, percent);
पूर्ण
