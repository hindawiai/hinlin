<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* For general debugging purposes */

#समावेश <पूर्णांकtypes.h>
#समावेश <माला.स>
#समावेश <मानकतर्क.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <sys/रुको.h>
#समावेश <api/debug.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समय64.h>
#समावेश <sys/समय.स>
#अगर_घोषित HAVE_BACKTRACE_SUPPORT
#समावेश <execinfo.h>
#पूर्ण_अगर
#समावेश "color.h"
#समावेश "event.h"
#समावेश "debug.h"
#समावेश "print_binary.h"
#समावेश "target.h"
#समावेश "ui/helpline.h"
#समावेश "ui/ui.h"
#समावेश "util/parse-sublevel-options.h"

#समावेश <linux/प्रकार.स>

पूर्णांक verbose;
पूर्णांक debug_peo_args;
bool dump_trace = false, quiet = false;
पूर्णांक debug_ordered_events;
अटल पूर्णांक redirect_to_मानक_त्रुटि;
पूर्णांक debug_data_convert;
अटल खाता *debug_file;
bool debug_display_समय;

व्योम debug_set_file(खाता *file)
अणु
	debug_file = file;
पूर्ण

व्योम debug_set_display_समय(bool set)
अणु
	debug_display_समय = set;
पूर्ण

अटल पूर्णांक ख_लिखो_समय(खाता *file)
अणु
	काष्ठा समयval tod;
	काष्ठा पंचांग lसमय;
	अक्षर date[64];

	अगर (!debug_display_समय)
		वापस 0;

	अगर (समय_लोofday(&tod, शून्य) != 0)
		वापस 0;

	अगर (स_स्थानीय_r(&tod.tv_sec, &lसमय) == शून्य)
		वापस 0;

	स_माला(date, माप(date),  "%F %H:%M:%S", &lसमय);
	वापस ख_लिखो(file, "[%s.%06lu] ", date, (दीर्घ)tod.tv_usec);
पूर्ण

पूर्णांक veम_लिखो(पूर्णांक level, पूर्णांक var, स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	पूर्णांक ret = 0;

	अगर (var >= level) अणु
		अगर (use_browser >= 1 && !redirect_to_मानक_त्रुटि) अणु
			ui_helpline__vshow(fmt, args);
		पूर्ण अन्यथा अणु
			ret = ख_लिखो_समय(debug_file);
			ret += भख_लिखो(debug_file, fmt, args);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक eम_लिखो(पूर्णांक level, पूर्णांक var, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक ret;

	बहु_शुरू(args, fmt);
	ret = veम_लिखो(level, var, fmt, args);
	बहु_पूर्ण(args);

	वापस ret;
पूर्ण

अटल पूर्णांक veम_लिखो_समय(u64 t, स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	पूर्णांक ret = 0;
	u64 secs, usecs, nsecs = t;

	secs   = nsecs / NSEC_PER_SEC;
	nsecs -= secs  * NSEC_PER_SEC;
	usecs  = nsecs / NSEC_PER_USEC;

	ret = ख_लिखो(मानक_त्रुटि, "[%13" PRIu64 ".%06" PRIu64 "] ",
		      secs, usecs);
	ret += भख_लिखो(मानक_त्रुटि, fmt, args);
	वापस ret;
पूर्ण

पूर्णांक eम_लिखो_समय(पूर्णांक level, पूर्णांक var, u64 t, स्थिर अक्षर *fmt, ...)
अणु
	पूर्णांक ret = 0;
	बहु_सूची args;

	अगर (var >= level) अणु
		बहु_शुरू(args, fmt);
		ret = veम_लिखो_समय(t, fmt, args);
		बहु_पूर्ण(args);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Overloading libtraceevent standard info prपूर्णांक
 * function, display with -v in perf.
 */
व्योम pr_stat(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	veम_लिखो(1, verbose, fmt, args);
	बहु_पूर्ण(args);
	eम_लिखो(1, verbose, "\n");
पूर्ण

पूर्णांक dump_म_लिखो(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक ret = 0;

	अगर (dump_trace) अणु
		बहु_शुरू(args, fmt);
		ret = भ_लिखो(fmt, args);
		बहु_पूर्ण(args);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक trace_event_prपूर्णांकer(क्रमागत binary_prपूर्णांकer_ops op,
			       अचिन्हित पूर्णांक val, व्योम *extra, खाता *fp)
अणु
	स्थिर अक्षर *color = PERF_COLOR_BLUE;
	जोड़ perf_event *event = (जोड़ perf_event *)extra;
	अचिन्हित अक्षर ch = (अचिन्हित अक्षर)val;
	पूर्णांक prपूर्णांकed = 0;

	चयन (op) अणु
	हाल BINARY_PRINT_DATA_BEGIN:
		prपूर्णांकed += ख_लिखो(fp, ".");
		prपूर्णांकed += color_ख_लिखो(fp, color, "\n. ... raw event: size %d bytes\n",
					 event->header.size);
		अवरोध;
	हाल BINARY_PRINT_LINE_BEGIN:
		prपूर्णांकed += ख_लिखो(fp, ".");
		अवरोध;
	हाल BINARY_PRINT_ADDR:
		prपूर्णांकed += color_ख_लिखो(fp, color, "  %04x: ", val);
		अवरोध;
	हाल BINARY_PRINT_NUM_DATA:
		prपूर्णांकed += color_ख_लिखो(fp, color, " %02x", val);
		अवरोध;
	हाल BINARY_PRINT_NUM_PAD:
		prपूर्णांकed += color_ख_लिखो(fp, color, "   ");
		अवरोध;
	हाल BINARY_PRINT_SEP:
		prपूर्णांकed += color_ख_लिखो(fp, color, "  ");
		अवरोध;
	हाल BINARY_PRINT_CHAR_DATA:
		prपूर्णांकed += color_ख_लिखो(fp, color, "%c",
			      है_छाप(ch) ? ch : '.');
		अवरोध;
	हाल BINARY_PRINT_CHAR_PAD:
		prपूर्णांकed += color_ख_लिखो(fp, color, " ");
		अवरोध;
	हाल BINARY_PRINT_LINE_END:
		prपूर्णांकed += color_ख_लिखो(fp, color, "\n");
		अवरोध;
	हाल BINARY_PRINT_DATA_END:
		prपूर्णांकed += ख_लिखो(fp, "\n");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस prपूर्णांकed;
पूर्ण

व्योम trace_event(जोड़ perf_event *event)
अणु
	अचिन्हित अक्षर *raw_event = (व्योम *)event;

	अगर (!dump_trace)
		वापस;

	prपूर्णांक_binary(raw_event, event->header.size, 16,
		     trace_event_prपूर्णांकer, event);
पूर्ण

अटल काष्ठा sublevel_option debug_opts[] = अणु
	अणु .name = "verbose",		.value_ptr = &verbose पूर्ण,
	अणु .name = "ordered-events",	.value_ptr = &debug_ordered_eventsपूर्ण,
	अणु .name = "stderr",		.value_ptr = &redirect_to_मानक_त्रुटिपूर्ण,
	अणु .name = "data-convert",	.value_ptr = &debug_data_convert पूर्ण,
	अणु .name = "perf-event-open",	.value_ptr = &debug_peo_args पूर्ण,
	अणु .name = शून्य, पूर्ण
पूर्ण;

पूर्णांक perf_debug_option(स्थिर अक्षर *str)
अणु
	पूर्णांक ret;

	ret = perf_parse_sublevel_options(str, debug_opts);
	अगर (ret)
		वापस ret;

	/* Allow only verbose value in range (0, 10), otherwise set 0. */
	verbose = (verbose < 0) || (verbose > 10) ? 0 : verbose;

	वापस 0;
पूर्ण

पूर्णांक perf_quiet_option(व्योम)
अणु
	काष्ठा sublevel_option *opt = &debug_opts[0];

	/* disable all debug messages */
	जबतक (opt->name) अणु
		*opt->value_ptr = -1;
		opt++;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा DEBUG_WRAPPER(__n, __l)				\
अटल पूर्णांक pr_ ## __n ## _wrapper(स्थिर अक्षर *fmt, ...)	\
अणु							\
	बहु_सूची args;					\
	पूर्णांक ret;					\
							\
	बहु_शुरू(args, fmt);				\
	ret = veम_लिखो(__l, verbose, fmt, args);	\
	बहु_पूर्ण(args);					\
	वापस ret;					\
पूर्ण

DEBUG_WRAPPER(warning, 0);
DEBUG_WRAPPER(debug, 1);

व्योम perf_debug_setup(व्योम)
अणु
	debug_set_file(मानक_त्रुटि);
	libapi_set_prपूर्णांक(pr_warning_wrapper, pr_warning_wrapper, pr_debug_wrapper);
पूर्ण

/* Obtain a backtrace and prपूर्णांक it to मानक_निकास. */
#अगर_घोषित HAVE_BACKTRACE_SUPPORT
व्योम dump_stack(व्योम)
अणु
	व्योम *array[16];
	माप_प्रकार size = backtrace(array, ARRAY_SIZE(array));
	अक्षर **strings = backtrace_symbols(array, size);
	माप_प्रकार i;

	म_लिखो("Obtained %zd stack frames.\n", size);

	क्रम (i = 0; i < size; i++)
		म_लिखो("%s\n", strings[i]);

	मुक्त(strings);
पूर्ण
#अन्यथा
व्योम dump_stack(व्योम) अणुपूर्ण
#पूर्ण_अगर

व्योम sighandler_dump_stack(पूर्णांक sig)
अणु
	pसंकेत(sig, "perf");
	dump_stack();
	संकेत(sig, संक_पूर्व);
	उठाओ(sig);
पूर्ण
