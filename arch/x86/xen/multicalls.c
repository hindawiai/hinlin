<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Xen hypercall batching.
 *
 * Xen allows multiple hypercalls to be issued at once, using the
 * multicall पूर्णांकerface.  This allows the cost of trapping पूर्णांकo the
 * hypervisor to be amortized over several calls.
 *
 * This file implements a simple पूर्णांकerface क्रम multicalls.  There's a
 * per-cpu buffer of outstanding multicalls.  When you want to queue a
 * multicall क्रम issuing, you can allocate a multicall slot क्रम the
 * call and its arguments, aदीर्घ with storage क्रम space which is
 * poपूर्णांकed to by the arguments (क्रम passing poपूर्णांकers to काष्ठाures,
 * etc).  When the multicall is actually issued, all the space क्रम the
 * commands and allocated memory is मुक्तd क्रम reuse.
 *
 * Multicalls are flushed whenever any of the buffers get full, or
 * when explicitly requested.  There's no way to get per-multicall
 * वापस results back.  It will BUG अगर any of the multicalls fail.
 *
 * Jeremy Fitzhardinge <jeremy@xensource.com>, XenSource Inc, 2007
 */
#समावेश <linux/percpu.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/debugfs.h>

#समावेश <यंत्र/xen/hypercall.h>

#समावेश "multicalls.h"
#समावेश "debugfs.h"

#घोषणा MC_BATCH	32

#घोषणा MC_DEBUG	0

#घोषणा MC_ARGS		(MC_BATCH * 16)


काष्ठा mc_buffer अणु
	अचिन्हित mcidx, argidx, cbidx;
	काष्ठा multicall_entry entries[MC_BATCH];
#अगर MC_DEBUG
	काष्ठा multicall_entry debug[MC_BATCH];
	व्योम *caller[MC_BATCH];
#पूर्ण_अगर
	अचिन्हित अक्षर args[MC_ARGS];
	काष्ठा callback अणु
		व्योम (*fn)(व्योम *);
		व्योम *data;
	पूर्ण callbacks[MC_BATCH];
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा mc_buffer, mc_buffer);
DEFINE_PER_CPU(अचिन्हित दीर्घ, xen_mc_irq_flags);

व्योम xen_mc_flush(व्योम)
अणु
	काष्ठा mc_buffer *b = this_cpu_ptr(&mc_buffer);
	काष्ठा multicall_entry *mc;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	BUG_ON(preemptible());

	/* Disable पूर्णांकerrupts in हाल someone comes in and queues
	   something in the middle */
	local_irq_save(flags);

	trace_xen_mc_flush(b->mcidx, b->argidx, b->cbidx);

#अगर MC_DEBUG
	स_नकल(b->debug, b->entries,
	       b->mcidx * माप(काष्ठा multicall_entry));
#पूर्ण_अगर

	चयन (b->mcidx) अणु
	हाल 0:
		/* no-op */
		BUG_ON(b->argidx != 0);
		अवरोध;

	हाल 1:
		/* Singleton multicall - bypass multicall machinery
		   and just करो the call directly. */
		mc = &b->entries[0];

		mc->result = xen_single_call(mc->op, mc->args[0], mc->args[1],
					     mc->args[2], mc->args[3],
					     mc->args[4]);
		ret = mc->result < 0;
		अवरोध;

	शेष:
		अगर (HYPERVISOR_multicall(b->entries, b->mcidx) != 0)
			BUG();
		क्रम (i = 0; i < b->mcidx; i++)
			अगर (b->entries[i].result < 0)
				ret++;
	पूर्ण

	अगर (WARN_ON(ret)) अणु
		pr_err("%d of %d multicall(s) failed: cpu %d\n",
		       ret, b->mcidx, smp_processor_id());
		क्रम (i = 0; i < b->mcidx; i++) अणु
			अगर (b->entries[i].result < 0) अणु
#अगर MC_DEBUG
				pr_err("  call %2d: op=%lu arg=[%lx] result=%ld\t%pS\n",
				       i + 1,
				       b->debug[i].op,
				       b->debug[i].args[0],
				       b->entries[i].result,
				       b->caller[i]);
#अन्यथा
				pr_err("  call %2d: op=%lu arg=[%lx] result=%ld\n",
				       i + 1,
				       b->entries[i].op,
				       b->entries[i].args[0],
				       b->entries[i].result);
#पूर्ण_अगर
			पूर्ण
		पूर्ण
	पूर्ण

	b->mcidx = 0;
	b->argidx = 0;

	क्रम (i = 0; i < b->cbidx; i++) अणु
		काष्ठा callback *cb = &b->callbacks[i];

		(*cb->fn)(cb->data);
	पूर्ण
	b->cbidx = 0;

	local_irq_restore(flags);
पूर्ण

काष्ठा multicall_space __xen_mc_entry(माप_प्रकार args)
अणु
	काष्ठा mc_buffer *b = this_cpu_ptr(&mc_buffer);
	काष्ठा multicall_space ret;
	अचिन्हित argidx = roundup(b->argidx, माप(u64));

	trace_xen_mc_entry_alloc(args);

	BUG_ON(preemptible());
	BUG_ON(b->argidx >= MC_ARGS);

	अगर (unlikely(b->mcidx == MC_BATCH ||
		     (argidx + args) >= MC_ARGS)) अणु
		trace_xen_mc_flush_reason((b->mcidx == MC_BATCH) ?
					  XEN_MC_FL_BATCH : XEN_MC_FL_ARGS);
		xen_mc_flush();
		argidx = roundup(b->argidx, माप(u64));
	पूर्ण

	ret.mc = &b->entries[b->mcidx];
#अगर MC_DEBUG
	b->caller[b->mcidx] = __builtin_वापस_address(0);
#पूर्ण_अगर
	b->mcidx++;
	ret.args = &b->args[argidx];
	b->argidx = argidx + args;

	BUG_ON(b->argidx >= MC_ARGS);
	वापस ret;
पूर्ण

काष्ठा multicall_space xen_mc_extend_args(अचिन्हित दीर्घ op, माप_प्रकार size)
अणु
	काष्ठा mc_buffer *b = this_cpu_ptr(&mc_buffer);
	काष्ठा multicall_space ret = अणु शून्य, शून्य पूर्ण;

	BUG_ON(preemptible());
	BUG_ON(b->argidx >= MC_ARGS);

	अगर (unlikely(b->mcidx == 0 ||
		     b->entries[b->mcidx - 1].op != op)) अणु
		trace_xen_mc_extend_args(op, size, XEN_MC_XE_BAD_OP);
		जाओ out;
	पूर्ण

	अगर (unlikely((b->argidx + size) >= MC_ARGS)) अणु
		trace_xen_mc_extend_args(op, size, XEN_MC_XE_NO_SPACE);
		जाओ out;
	पूर्ण

	ret.mc = &b->entries[b->mcidx - 1];
	ret.args = &b->args[b->argidx];
	b->argidx += size;

	BUG_ON(b->argidx >= MC_ARGS);

	trace_xen_mc_extend_args(op, size, XEN_MC_XE_OK);
out:
	वापस ret;
पूर्ण

व्योम xen_mc_callback(व्योम (*fn)(व्योम *), व्योम *data)
अणु
	काष्ठा mc_buffer *b = this_cpu_ptr(&mc_buffer);
	काष्ठा callback *cb;

	अगर (b->cbidx == MC_BATCH) अणु
		trace_xen_mc_flush_reason(XEN_MC_FL_CALLBACK);
		xen_mc_flush();
	पूर्ण

	trace_xen_mc_callback(fn, data);

	cb = &b->callbacks[b->cbidx++];
	cb->fn = fn;
	cb->data = data;
पूर्ण
