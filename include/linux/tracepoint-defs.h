<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित TRACEPOINT_DEFS_H
#घोषणा TRACEPOINT_DEFS_H 1

/*
 * File can be included directly by headers who only want to access
 * tracepoपूर्णांक->key to guard out of line trace calls, or the definition of
 * trace_prपूर्णांक_flagsअणु_u64पूर्ण. Otherwise linux/tracepoपूर्णांक.h should be used.
 */

#समावेश <linux/atomic.h>
#समावेश <linux/अटल_key.h>

काष्ठा अटल_call_key;

काष्ठा trace_prपूर्णांक_flags अणु
	अचिन्हित दीर्घ		mask;
	स्थिर अक्षर		*name;
पूर्ण;

काष्ठा trace_prपूर्णांक_flags_u64 अणु
	अचिन्हित दीर्घ दीर्घ	mask;
	स्थिर अक्षर		*name;
पूर्ण;

काष्ठा tracepoपूर्णांक_func अणु
	व्योम *func;
	व्योम *data;
	पूर्णांक prio;
पूर्ण;

काष्ठा tracepoपूर्णांक अणु
	स्थिर अक्षर *name;		/* Tracepoपूर्णांक name */
	काष्ठा अटल_key key;
	काष्ठा अटल_call_key *अटल_call_key;
	व्योम *अटल_call_tramp;
	व्योम *iterator;
	पूर्णांक (*regfunc)(व्योम);
	व्योम (*unregfunc)(व्योम);
	काष्ठा tracepoपूर्णांक_func __rcu *funcs;
पूर्ण;

#अगर_घोषित CONFIG_HAVE_ARCH_PREL32_RELOCATIONS
प्रकार स्थिर पूर्णांक tracepoपूर्णांक_ptr_t;
#अन्यथा
प्रकार काष्ठा tracepoपूर्णांक * स्थिर tracepoपूर्णांक_ptr_t;
#पूर्ण_अगर

काष्ठा bpf_raw_event_map अणु
	काष्ठा tracepoपूर्णांक	*tp;
	व्योम			*bpf_func;
	u32			num_args;
	u32			writable_size;
पूर्ण __aligned(32);

/*
 * If a tracepoपूर्णांक needs to be called from a header file, it is not
 * recommended to call it directly, as tracepoपूर्णांकs in header files
 * may cause side-effects and bloat the kernel. Instead, use
 * tracepoपूर्णांक_enabled() to test अगर the tracepoपूर्णांक is enabled, then अगर
 * it is, call a wrapper function defined in a C file that will then
 * call the tracepoपूर्णांक.
 *
 * For "trace_foo_bar()", you would need to create a wrapper function
 * in a C file to call trace_foo_bar():
 *   व्योम करो_trace_foo_bar(args) अणु trace_foo_bar(args); पूर्ण
 * Then in the header file, declare the tracepoपूर्णांक:
 *   DECLARE_TRACEPOINT(foo_bar);
 * And call your wrapper:
 *   अटल अंतरभूत व्योम some_अंतरभूतd_function() अणु
 *            [..]
 *            अगर (tracepoपूर्णांक_enabled(foo_bar))
 *                    करो_trace_foo_bar(args);
 *            [..]
 *   पूर्ण
 *
 * Note: tracepoपूर्णांक_enabled(foo_bar) is equivalent to trace_foo_bar_enabled()
 *   but is safe to have in headers, where trace_foo_bar_enabled() is not.
 */
#घोषणा DECLARE_TRACEPOINT(tp) \
	बाह्य काष्ठा tracepoपूर्णांक __tracepoपूर्णांक_##tp

#अगर_घोषित CONFIG_TRACEPOINTS
# define tracepoपूर्णांक_enabled(tp) \
	अटल_key_false(&(__tracepoपूर्णांक_##tp).key)
#अन्यथा
# define tracepoपूर्णांक_enabled(tracepoपूर्णांक) false
#पूर्ण_अगर

#पूर्ण_अगर
