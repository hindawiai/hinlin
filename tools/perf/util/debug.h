<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* For debugging general purposes */
#अगर_अघोषित __PERF_DEBUG_H
#घोषणा __PERF_DEBUG_H

#समावेश <मानकतर्क.स>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <linux/compiler.h>

बाह्य पूर्णांक verbose;
बाह्य पूर्णांक debug_peo_args;
बाह्य bool quiet, dump_trace;
बाह्य पूर्णांक debug_ordered_events;
बाह्य पूर्णांक debug_data_convert;

#अगर_अघोषित pr_fmt
#घोषणा pr_fmt(fmt) fmt
#पूर्ण_अगर

#घोषणा pr_err(fmt, ...) \
	eम_लिखो(0, verbose, pr_fmt(fmt), ##__VA_ARGS__)
#घोषणा pr_warning(fmt, ...) \
	eम_लिखो(0, verbose, pr_fmt(fmt), ##__VA_ARGS__)
#घोषणा pr_info(fmt, ...) \
	eम_लिखो(0, verbose, pr_fmt(fmt), ##__VA_ARGS__)
#घोषणा pr_debug(fmt, ...) \
	eम_लिखो(1, verbose, pr_fmt(fmt), ##__VA_ARGS__)
#घोषणा pr_debugN(n, fmt, ...) \
	eम_लिखो(n, verbose, pr_fmt(fmt), ##__VA_ARGS__)
#घोषणा pr_debug2(fmt, ...) pr_debugN(2, pr_fmt(fmt), ##__VA_ARGS__)
#घोषणा pr_debug3(fmt, ...) pr_debugN(3, pr_fmt(fmt), ##__VA_ARGS__)
#घोषणा pr_debug4(fmt, ...) pr_debugN(4, pr_fmt(fmt), ##__VA_ARGS__)

/* Special macro to prपूर्णांक perf_event_खोलो arguments/वापस value. */
#घोषणा pr_debug2_peo(fmt, ...) अणु				\
	अगर (debug_peo_args)						\
		pr_debugN(0, pr_fmt(fmt), ##__VA_ARGS__);	\
	अन्यथा							\
		pr_debugN(2, pr_fmt(fmt), ##__VA_ARGS__);	\
पूर्ण

#घोषणा pr_समय_N(n, var, t, fmt, ...) \
	eम_लिखो_समय(n, var, t, fmt, ##__VA_ARGS__)

#घोषणा pr_oe_समय(t, fmt, ...)  pr_समय_N(1, debug_ordered_events, t, pr_fmt(fmt), ##__VA_ARGS__)
#घोषणा pr_oe_समय2(t, fmt, ...) pr_समय_N(2, debug_ordered_events, t, pr_fmt(fmt), ##__VA_ARGS__)

#घोषणा STRERR_बफ_मानE	128	/* For the buffer size of str_error_r */

जोड़ perf_event;

पूर्णांक dump_म_लिखो(स्थिर अक्षर *fmt, ...) __म_लिखो(1, 2);
व्योम trace_event(जोड़ perf_event *event);

पूर्णांक ui__error(स्थिर अक्षर *क्रमmat, ...) __म_लिखो(1, 2);
पूर्णांक ui__warning(स्थिर अक्षर *क्रमmat, ...) __म_लिखो(1, 2);

व्योम pr_stat(स्थिर अक्षर *fmt, ...);

पूर्णांक eम_लिखो(पूर्णांक level, पूर्णांक var, स्थिर अक्षर *fmt, ...) __म_लिखो(3, 4);
पूर्णांक eम_लिखो_समय(पूर्णांक level, पूर्णांक var, u64 t, स्थिर अक्षर *fmt, ...) __म_लिखो(4, 5);
पूर्णांक veम_लिखो(पूर्णांक level, पूर्णांक var, स्थिर अक्षर *fmt, बहु_सूची args);

पूर्णांक perf_debug_option(स्थिर अक्षर *str);
व्योम debug_set_file(खाता *file);
व्योम debug_set_display_समय(bool set);
व्योम perf_debug_setup(व्योम);
पूर्णांक perf_quiet_option(व्योम);

व्योम dump_stack(व्योम);
व्योम sighandler_dump_stack(पूर्णांक sig);

#पूर्ण_अगर	/* __PERF_DEBUG_H */
