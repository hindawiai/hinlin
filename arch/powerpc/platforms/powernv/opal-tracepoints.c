<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/percpu.h>
#समावेश <linux/jump_label.h>
#समावेश <यंत्र/trace.h>
#समावेश <यंत्र/यंत्र-prototypes.h>

#अगर_घोषित CONFIG_JUMP_LABEL
काष्ठा अटल_key opal_tracepoपूर्णांक_key = STATIC_KEY_INIT;

पूर्णांक opal_tracepoपूर्णांक_regfunc(व्योम)
अणु
	अटल_key_slow_inc(&opal_tracepoपूर्णांक_key);
	वापस 0;
पूर्ण

व्योम opal_tracepoपूर्णांक_unregfunc(व्योम)
अणु
	अटल_key_slow_dec(&opal_tracepoपूर्णांक_key);
पूर्ण
#अन्यथा
/*
 * We optimise OPAL calls by placing opal_tracepoपूर्णांक_refcount
 * directly in the TOC so we can check अगर the opal tracepoपूर्णांकs are
 * enabled via a single load.
 */

/* NB: reg/unreg are called जबतक guarded with the tracepoपूर्णांकs_mutex */
बाह्य दीर्घ opal_tracepoपूर्णांक_refcount;

पूर्णांक opal_tracepoपूर्णांक_regfunc(व्योम)
अणु
	opal_tracepoपूर्णांक_refcount++;
	वापस 0;
पूर्ण

व्योम opal_tracepoपूर्णांक_unregfunc(व्योम)
अणु
	opal_tracepoपूर्णांक_refcount--;
पूर्ण
#पूर्ण_अगर

/*
 * Since the tracing code might execute OPAL calls we need to guard against
 * recursion.
 */
अटल DEFINE_PER_CPU(अचिन्हित पूर्णांक, opal_trace_depth);

व्योम __trace_opal_entry(अचिन्हित दीर्घ opcode, अचिन्हित दीर्घ *args)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक *depth;

	local_irq_save(flags);

	depth = this_cpu_ptr(&opal_trace_depth);

	अगर (*depth)
		जाओ out;

	(*depth)++;
	preempt_disable();
	trace_opal_entry(opcode, args);
	(*depth)--;

out:
	local_irq_restore(flags);
पूर्ण

व्योम __trace_opal_निकास(दीर्घ opcode, अचिन्हित दीर्घ retval)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक *depth;

	local_irq_save(flags);

	depth = this_cpu_ptr(&opal_trace_depth);

	अगर (*depth)
		जाओ out;

	(*depth)++;
	trace_opal_निकास(opcode, retval);
	preempt_enable();
	(*depth)--;

out:
	local_irq_restore(flags);
पूर्ण
