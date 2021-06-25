<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * If TRACE_SYSTEM is defined, that will be the directory created
 * in the ftrace directory under /sys/kernel/tracing/events/<प्रणाली>
 *
 * The define_trace.h below will also look क्रम a file name of
 * TRACE_SYSTEM.h where TRACE_SYSTEM is what is defined here.
 * In this हाल, it would look क्रम sample-trace.h
 *
 * If the header name will be dअगरferent than the प्रणाली name
 * (as in this हाल), then you can override the header name that
 * define_trace.h will look up by defining TRACE_INCLUDE_खाता
 *
 * This file is called trace-events-sample.h but we want the प्रणाली
 * to be called "sample-trace". Thereक्रमe we must define the name of this
 * file:
 *
 * #घोषणा TRACE_INCLUDE_खाता trace-events-sample
 *
 * As we करो an the bottom of this file.
 *
 * Notice that TRACE_SYSTEM should be defined outside of #अगर
 * protection, just like TRACE_INCLUDE_खाता.
 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM sample-trace

/*
 * TRACE_SYSTEM is expected to be a C valid variable (alpha-numeric
 * and underscore), although it may start with numbers. If क्रम some
 * reason it is not, you need to add the following lines:
 */
#अघोषित TRACE_SYSTEM_VAR
#घोषणा TRACE_SYSTEM_VAR sample_trace
/*
 * But the above is only needed अगर TRACE_SYSTEM is not alpha-numeric
 * and underscored. By शेष, TRACE_SYSTEM_VAR will be equal to
 * TRACE_SYSTEM. As TRACE_SYSTEM_VAR must be alpha-numeric, अगर
 * TRACE_SYSTEM is not, then TRACE_SYSTEM_VAR must be defined with
 * only alpha-numeric and underscores.
 *
 * The TRACE_SYSTEM_VAR is only used पूर्णांकernally and not visible to
 * user space.
 */

/*
 * Notice that this file is not रक्षित like a normal header.
 * We also must allow क्रम reपढ़ोing of this file. The
 *
 *  || defined(TRACE_HEADER_MULTI_READ)
 *
 * serves this purpose.
 */
#अगर !defined(_TRACE_EVENT_SAMPLE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_EVENT_SAMPLE_H

/*
 * All trace headers should include tracepoपूर्णांक.h, until we finally
 * make it पूर्णांकo a standard header.
 */
#समावेश <linux/tracepoपूर्णांक.h>

/*
 * The TRACE_EVENT macro is broken up पूर्णांकo 5 parts.
 *
 * name: name of the trace poपूर्णांक. This is also how to enable the tracepoपूर्णांक.
 *   A function called trace_foo_bar() will be created.
 *
 * proto: the prototype of the function trace_foo_bar()
 *   Here it is trace_foo_bar(अक्षर *foo, पूर्णांक bar).
 *
 * args:  must match the arguments in the prototype.
 *    Here it is simply "foo, bar".
 *
 * काष्ठा:  This defines the way the data will be stored in the ring buffer.
 *          The items declared here become part of a special काष्ठाure
 *          called "__entry", which can be used in the fast_assign part of the
 *          TRACE_EVENT macro.
 *
 *      Here are the currently defined types you can use:
 *
 *   __field : Is broken up पूर्णांकo type and name. Where type can be any
 *         primitive type (पूर्णांकeger, दीर्घ or poपूर्णांकer).
 *
 *        __field(पूर्णांक, foo)
 *
 *        __entry->foo = 5;
 *
 *   __field_काष्ठा : This can be any अटल complex data type (काष्ठा, जोड़
 *         but not an array). Be careful using complex types, as each
 *         event is limited in size, and copying large amounts of data
 *         पूर्णांकo the ring buffer can slow things करोwn.
 *
 *         __field_काष्ठा(काष्ठा bar, foo)
 *
 *         __entry->bar.x = y;

 *   __array: There are three fields (type, name, size). The type is the
 *         type of elements in the array, the name is the name of the array.
 *         size is the number of items in the array (not the total size).
 *
 *         __array( अक्षर, foo, 10) is the same as saying: अक्षर foo[10];
 *
 *         Assigning arrays can be करोne like any array:
 *
 *         __entry->foo[0] = 'a';
 *
 *         स_नकल(__entry->foo, bar, 10);
 *
 *   __dynamic_array: This is similar to array, but can vary its size from
 *         instance to instance of the tracepoपूर्णांक being called.
 *         Like __array, this too has three elements (type, name, size);
 *         type is the type of the element, name is the name of the array.
 *         The size is dअगरferent than __array. It is not a अटल number,
 *         but the algorithm to figure out the length of the array क्रम the
 *         specअगरic instance of tracepoपूर्णांक. Again, size is the number of
 *         items in the array, not the total length in bytes.
 *
 *         __dynamic_array( पूर्णांक, foo, bar) is similar to: पूर्णांक foo[bar];
 *
 *         Note, unlike arrays, you must use the __get_dynamic_array() macro
 *         to access the array.
 *
 *         स_नकल(__get_dynamic_array(foo), bar, 10);
 *
 *         Notice, that "__entry" is not needed here.
 *
 *   __string: This is a special kind of __dynamic_array. It expects to
 *         have a null terminated अक्षरacter array passed to it (it allows
 *         क्रम शून्य too, which would be converted पूर्णांकo "(null)"). __string
 *         takes two parameter (name, src), where name is the name of
 *         the string saved, and src is the string to copy पूर्णांकo the
 *         ring buffer.
 *
 *         __string(foo, bar)  is similar to:  म_नकल(foo, bar)
 *
 *         To assign a string, use the helper macro __assign_str().
 *
 *         __assign_str(foo, bar);
 *
 *         In most हालs, the __assign_str() macro will take the same
 *         parameters as the __string() macro had to declare the string.
 *
 *   __biपंचांगask: This is another kind of __dynamic_array, but it expects
 *         an array of दीर्घs, and the number of bits to parse. It takes
 *         two parameters (name, nr_bits), where name is the name of the
 *         biपंचांगask to save, and the nr_bits is the number of bits to record.
 *
 *         __biपंचांगask(target_cpu, nr_cpumask_bits)
 *
 *         To assign a biपंचांगask, use the __assign_biपंचांगask() helper macro.
 *
 *         __assign_biपंचांगask(target_cpus, cpumask_bits(bar), nr_cpumask_bits);
 *
 *
 * fast_assign: This is a C like function that is used to store the items
 *    पूर्णांकo the ring buffer. A special variable called "__entry" will be the
 *    काष्ठाure that poपूर्णांकs पूर्णांकo the ring buffer and has the same fields as
 *    described by the काष्ठा part of TRACE_EVENT above.
 *
 * prपूर्णांकk: This is a way to prपूर्णांक out the data in pretty prपूर्णांक. This is
 *    useful अगर the प्रणाली crashes and you are logging via a serial line,
 *    the data can be prपूर्णांकed to the console using this "printk" method.
 *    This is also used to prपूर्णांक out the data from the trace files.
 *    Again, the __entry macro is used to access the data from the ring buffer.
 *
 *    Note, __dynamic_array, __string, and __biपंचांगask require special helpers
 *       to access the data.
 *
 *      For __dynamic_array(पूर्णांक, foo, bar) use __get_dynamic_array(foo)
 *            Use __get_dynamic_array_len(foo) to get the length of the array
 *            saved. Note, __get_dynamic_array_len() वापसs the total allocated
 *            length of the dynamic array; __prपूर्णांक_array() expects the second
 *            parameter to be the number of elements. To get that, the array length
 *            needs to be भागided by the element size.
 *
 *      For __string(foo, bar) use __get_str(foo)
 *
 *      For __biपंचांगask(target_cpus, nr_cpumask_bits) use __get_biपंचांगask(target_cpus)
 *
 *
 * Note, that क्रम both the assign and the prपूर्णांकk, __entry is the handler
 * to the data काष्ठाure in the ring buffer, and is defined by the
 * TP_STRUCT__entry.
 */

/*
 * It is OK to have helper functions in the file, but they need to be रक्षित
 * from being defined more than once. Remember, this file माला_लो included more
 * than once.
 */
#अगर_अघोषित __TRACE_EVENT_SAMPLE_HELPER_FUNCTIONS
#घोषणा __TRACE_EVENT_SAMPLE_HELPER_FUNCTIONS
अटल अंतरभूत पूर्णांक __length_of(स्थिर पूर्णांक *list)
अणु
	पूर्णांक i;

	अगर (!list)
		वापस 0;

	क्रम (i = 0; list[i]; i++)
		;
	वापस i;
पूर्ण

क्रमागत अणु
	TRACE_SAMPLE_FOO = 2,
	TRACE_SAMPLE_BAR = 4,
	TRACE_SAMPLE_ZOO = 8,
पूर्ण;
#पूर्ण_अगर

/*
 * If क्रमागतs are used in the TP_prपूर्णांकk(), their names will be shown in
 * क्रमmat files and not their values. This can cause problems with user
 * space programs that parse the क्रमmat files to know how to translate
 * the raw binary trace output पूर्णांकo human पढ़ोable text.
 *
 * To help out user space programs, any क्रमागत that is used in the TP_prपूर्णांकk()
 * should be defined by TRACE_DEFINE_ENUM() macro. All that is needed to
 * be करोne is to add this macro with the क्रमागत within it in the trace
 * header file, and it will be converted in the output.
 */

TRACE_DEFINE_ENUM(TRACE_SAMPLE_FOO);
TRACE_DEFINE_ENUM(TRACE_SAMPLE_BAR);
TRACE_DEFINE_ENUM(TRACE_SAMPLE_ZOO);

TRACE_EVENT(foo_bar,

	TP_PROTO(स्थिर अक्षर *foo, पूर्णांक bar, स्थिर पूर्णांक *lst,
		 स्थिर अक्षर *string, स्थिर काष्ठा cpumask *mask),

	TP_ARGS(foo, bar, lst, string, mask),

	TP_STRUCT__entry(
		__array(	अक्षर,	foo,    10		)
		__field(	पूर्णांक,	bar			)
		__dynamic_array(पूर्णांक,	list,   __length_of(lst))
		__string(	str,	string			)
		__biपंचांगask(	cpus,	num_possible_cpus()	)
	),

	TP_fast_assign(
		strlcpy(__entry->foo, foo, 10);
		__entry->bar	= bar;
		स_नकल(__get_dynamic_array(list), lst,
		       __length_of(lst) * माप(पूर्णांक));
		__assign_str(str, string);
		__assign_biपंचांगask(cpus, cpumask_bits(mask), num_possible_cpus());
	),

	TP_prपूर्णांकk("foo %s %d %s %s %s %s (%s)", __entry->foo, __entry->bar,

/*
 * Notice here the use of some helper functions. This includes:
 *
 *  __prपूर्णांक_symbolic( variable, अणु value, "string" पूर्ण, ... ),
 *
 *    The variable is tested against each value of the अणु पूर्ण pair. If
 *    the variable matches one of the values, then it will prपूर्णांक the
 *    string in that pair. If non are matched, it वापसs a string
 *    version of the number (अगर __entry->bar == 7 then "7" is वापसed).
 */
		  __prपूर्णांक_symbolic(__entry->bar,
				   अणु 0, "zero" पूर्ण,
				   अणु TRACE_SAMPLE_FOO, "TWO" पूर्ण,
				   अणु TRACE_SAMPLE_BAR, "FOUR" पूर्ण,
				   अणु TRACE_SAMPLE_ZOO, "EIGHT" पूर्ण,
				   अणु 10, "TEN" पूर्ण
			  ),

/*
 *  __prपूर्णांक_flags( variable, "delim", अणु value, "flag" पूर्ण, ... ),
 *
 *    This is similar to __prपूर्णांक_symbolic, except that it tests the bits
 *    of the value. If ((FLAG & variable) == FLAG) then the string is
 *    prपूर्णांकed. If more than one flag matches, then each one that करोes is
 *    also prपूर्णांकed with delim in between them.
 *    If not all bits are accounted क्रम, then the not found bits will be
 *    added in hex क्रमmat: 0x506 will show BIT2|BIT4|0x500
 */
		  __prपूर्णांक_flags(__entry->bar, "|",
				अणु 1, "BIT1" पूर्ण,
				अणु 2, "BIT2" पूर्ण,
				अणु 4, "BIT3" पूर्ण,
				अणु 8, "BIT4" पूर्ण
			  ),
/*
 *  __prपूर्णांक_array( array, len, element_size )
 *
 *    This prपूर्णांकs out the array that is defined by __array in a nice क्रमmat.
 */
		  __prपूर्णांक_array(__get_dynamic_array(list),
				__get_dynamic_array_len(list) / माप(पूर्णांक),
				माप(पूर्णांक)),
		  __get_str(str), __get_biपंचांगask(cpus))
);

/*
 * There may be a हाल where a tracepoपूर्णांक should only be called अगर
 * some condition is set. Otherwise the tracepoपूर्णांक should not be called.
 * But to करो something like:
 *
 *  अगर (cond)
 *     trace_foo();
 *
 * Would cause a little overhead when tracing is not enabled, and that
 * overhead, even अगर small, is not something we want. As tracepoपूर्णांकs
 * use अटल branch (aka jump_labels), where no branch is taken to
 * skip the tracepoपूर्णांक when not enabled, and a jmp is placed to jump
 * to the tracepoपूर्णांक code when it is enabled, having a अगर statement
 * nullअगरies that optimization. It would be nice to place that
 * condition within the अटल branch. This is where TRACE_EVENT_CONDITION
 * comes in.
 *
 * TRACE_EVENT_CONDITION() is just like TRACE_EVENT, except it adds another
 * parameter just after args. Where TRACE_EVENT has:
 *
 * TRACE_EVENT(name, proto, args, काष्ठा, assign, prपूर्णांकk)
 *
 * the CONDITION version has:
 *
 * TRACE_EVENT_CONDITION(name, proto, args, cond, काष्ठा, assign, prपूर्णांकk)
 *
 * Everything is the same as TRACE_EVENT except क्रम the new cond. Think
 * of the cond variable as:
 *
 *   अगर (cond)
 *      trace_foo_bar_with_cond();
 *
 * Except that the logic क्रम the अगर branch is placed after the अटल branch.
 * That is, the अगर statement that processes the condition will not be
 * executed unless that traecpoपूर्णांक is enabled. Otherwise it still reमुख्यs
 * a nop.
 */
TRACE_EVENT_CONDITION(foo_bar_with_cond,

	TP_PROTO(स्थिर अक्षर *foo, पूर्णांक bar),

	TP_ARGS(foo, bar),

	TP_CONDITION(!(bar % 10)),

	TP_STRUCT__entry(
		__string(	foo,    foo		)
		__field(	पूर्णांक,	bar			)
	),

	TP_fast_assign(
		__assign_str(foo, foo);
		__entry->bar	= bar;
	),

	TP_prपूर्णांकk("foo %s %d", __get_str(foo), __entry->bar)
);

पूर्णांक foo_bar_reg(व्योम);
व्योम foo_bar_unreg(व्योम);

/*
 * Now in the हाल that some function needs to be called when the
 * tracepoपूर्णांक is enabled and/or when it is disabled, the
 * TRACE_EVENT_FN() serves this purpose. This is just like TRACE_EVENT()
 * but adds two more parameters at the end:
 *
 * TRACE_EVENT_FN( name, proto, args, काष्ठा, assign, prपूर्णांकk, reg, unreg)
 *
 * reg and unreg are functions with the prototype of:
 *
 *    व्योम reg(व्योम)
 *
 * The reg function माला_लो called beक्रमe the tracepoपूर्णांक is enabled, and
 * the unreg function माला_लो called after the tracepoपूर्णांक is disabled.
 *
 * Note, reg and unreg are allowed to be शून्य. If you only need to
 * call a function beक्रमe enabling, or after disabling, just set one
 * function and pass in शून्य क्रम the other parameter.
 */
TRACE_EVENT_FN(foo_bar_with_fn,

	TP_PROTO(स्थिर अक्षर *foo, पूर्णांक bar),

	TP_ARGS(foo, bar),

	TP_STRUCT__entry(
		__string(	foo,    foo		)
		__field(	पूर्णांक,	bar		)
	),

	TP_fast_assign(
		__assign_str(foo, foo);
		__entry->bar	= bar;
	),

	TP_prपूर्णांकk("foo %s %d", __get_str(foo), __entry->bar),

	foo_bar_reg, foo_bar_unreg
);

/*
 * Each TRACE_EVENT macro creates several helper functions to produce
 * the code to add the tracepoपूर्णांक, create the files in the trace
 * directory, hook it to perf, assign the values and to prपूर्णांक out
 * the raw data from the ring buffer. To prevent too much bloat,
 * अगर there are more than one tracepoपूर्णांक that uses the same क्रमmat
 * क्रम the proto, args, काष्ठा, assign and prपूर्णांकk, and only the name
 * is dअगरferent, it is highly recommended to use the DECLARE_EVENT_CLASS
 *
 * DECLARE_EVENT_CLASS() macro creates most of the functions क्रम the
 * tracepoपूर्णांक. Then DEFINE_EVENT() is use to hook a tracepoपूर्णांक to those
 * functions. This DEFINE_EVENT() is an instance of the class and can
 * be enabled and disabled separately from other events (either TRACE_EVENT
 * or other DEFINE_EVENT()s).
 *
 * Note, TRACE_EVENT() itself is simply defined as:
 *
 * #घोषणा TRACE_EVENT(name, proto, args, tकाष्ठा, assign, prपूर्णांकk)  \
 *  DECLARE_EVENT_CLASS(name, proto, args, tकाष्ठा, assign, prपूर्णांकk); \
 *  DEFINE_EVENT(name, name, proto, args)
 *
 * The DEFINE_EVENT() also can be declared with conditions and reg functions:
 *
 * DEFINE_EVENT_CONDITION(ढाँचा, name, proto, args, cond);
 * DEFINE_EVENT_FN(ढाँचा, name, proto, args, reg, unreg);
 */
DECLARE_EVENT_CLASS(foo_ढाँचा,

	TP_PROTO(स्थिर अक्षर *foo, पूर्णांक bar),

	TP_ARGS(foo, bar),

	TP_STRUCT__entry(
		__string(	foo,    foo		)
		__field(	पूर्णांक,	bar		)
	),

	TP_fast_assign(
		__assign_str(foo, foo);
		__entry->bar	= bar;
	),

	TP_prपूर्णांकk("foo %s %d", __get_str(foo), __entry->bar)
);

/*
 * Here's a better way क्रम the previous samples (except, the first
 * example had more fields and could not be used here).
 */
DEFINE_EVENT(foo_ढाँचा, foo_with_ढाँचा_simple,
	TP_PROTO(स्थिर अक्षर *foo, पूर्णांक bar),
	TP_ARGS(foo, bar));

DEFINE_EVENT_CONDITION(foo_ढाँचा, foo_with_ढाँचा_cond,
	TP_PROTO(स्थिर अक्षर *foo, पूर्णांक bar),
	TP_ARGS(foo, bar),
	TP_CONDITION(!(bar % 8)));


DEFINE_EVENT_FN(foo_ढाँचा, foo_with_ढाँचा_fn,
	TP_PROTO(स्थिर अक्षर *foo, पूर्णांक bar),
	TP_ARGS(foo, bar),
	foo_bar_reg, foo_bar_unreg);

/*
 * Anyसमय two events share basically the same values and have
 * the same output, use the DECLARE_EVENT_CLASS() and DEFINE_EVENT()
 * when ever possible.
 */

/*
 * If the event is similar to the DECLARE_EVENT_CLASS, but you need
 * to have a dअगरferent output, then use DEFINE_EVENT_PRINT() which
 * lets you override the TP_prपूर्णांकk() of the class.
 */

DEFINE_EVENT_PRINT(foo_ढाँचा, foo_with_ढाँचा_prपूर्णांक,
	TP_PROTO(स्थिर अक्षर *foo, पूर्णांक bar),
	TP_ARGS(foo, bar),
	TP_prपूर्णांकk("bar %s %d", __get_str(foo), __entry->bar));

#पूर्ण_अगर

/***** NOTICE! The #अगर protection ends here. *****/


/*
 * There are several ways I could have करोne this. If I left out the
 * TRACE_INCLUDE_PATH, then it would शेष to the kernel source
 * include/trace/events directory.
 *
 * I could specअगरy a path from the define_trace.h file back to this
 * file.
 *
 * #घोषणा TRACE_INCLUDE_PATH ../../samples/trace_events
 *
 * But the safest and easiest way to simply make it use the directory
 * that the file is in is to add in the Makefile:
 *
 * CFLAGS_trace-events-sample.o := -I$(src)
 *
 * This will make sure the current path is part of the include
 * काष्ठाure क्रम our file so that define_trace.h can find it.
 *
 * I could have made only the top level directory the include:
 *
 * CFLAGS_trace-events-sample.o := -I$(PWD)
 *
 * And then let the path to this directory be the TRACE_INCLUDE_PATH:
 *
 * #घोषणा TRACE_INCLUDE_PATH samples/trace_events
 *
 * But then अगर something defines "samples" or "trace_events" as a macro
 * then we could risk that being converted too, and give us an unexpected
 * result.
 */
#अघोषित TRACE_INCLUDE_PATH
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_PATH .
/*
 * TRACE_INCLUDE_खाता is not needed अगर the filename and TRACE_SYSTEM are equal
 */
#घोषणा TRACE_INCLUDE_खाता trace-events-sample
#समावेश <trace/define_trace.h>
