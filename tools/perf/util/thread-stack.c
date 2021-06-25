<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * thपढ़ो-stack.c: Synthesize a thपढ़ो's stack using call / वापस events
 * Copyright (c) 2014, Intel Corporation.
 */

#समावेश <linux/rbtree.h>
#समावेश <linux/list.h>
#समावेश <linux/log2.h>
#समावेश <linux/zभाग.स>
#समावेश <त्रुटिसं.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश "thread.h"
#समावेश "event.h"
#समावेश "machine.h"
#समावेश "env.h"
#समावेश "debug.h"
#समावेश "symbol.h"
#समावेश "comm.h"
#समावेश "call-path.h"
#समावेश "thread-stack.h"

#घोषणा STACK_GROWTH 2048

/*
 * State of retpoline detection.
 *
 * RETPOLINE_NONE: no retpoline detection
 * X86_RETPOLINE_POSSIBLE: x86 retpoline possible
 * X86_RETPOLINE_DETECTED: x86 retpoline detected
 */
क्रमागत retpoline_state_t अणु
	RETPOLINE_NONE,
	X86_RETPOLINE_POSSIBLE,
	X86_RETPOLINE_DETECTED,
पूर्ण;

/**
 * काष्ठा thपढ़ो_stack_entry - thपढ़ो stack entry.
 * @ret_addr: वापस address
 * @बारtamp: बारtamp (अगर known)
 * @ref: बाह्यal reference (e.g. db_id of sample)
 * @branch_count: the branch count when the entry was created
 * @insn_count: the inकाष्ठाion count when the entry was created
 * @cyc_count the cycle count when the entry was created
 * @db_id: id used क्रम db-export
 * @cp: call path
 * @no_call: a 'call' was not seen
 * @trace_end: a 'call' but trace ended
 * @non_call: a branch but not a 'call' to the start of a dअगरferent symbol
 */
काष्ठा thपढ़ो_stack_entry अणु
	u64 ret_addr;
	u64 बारtamp;
	u64 ref;
	u64 branch_count;
	u64 insn_count;
	u64 cyc_count;
	u64 db_id;
	काष्ठा call_path *cp;
	bool no_call;
	bool trace_end;
	bool non_call;
पूर्ण;

/**
 * काष्ठा thपढ़ो_stack - thपढ़ो stack स्थिरructed from 'call' and 'return'
 *                       branch samples.
 * @stack: array that holds the stack
 * @cnt: number of entries in the stack
 * @sz: current maximum stack size
 * @trace_nr: current trace number
 * @branch_count: running branch count
 * @insn_count: running  inकाष्ठाion count
 * @cyc_count running  cycle count
 * @kernel_start: kernel start address
 * @last_समय: last बारtamp
 * @crp: call/वापस processor
 * @comm: current comm
 * @arr_sz: size of array अगर this is the first element of an array
 * @rstate: used to detect retpolines
 * @br_stack_rb: branch stack (ring buffer)
 * @br_stack_sz: maximum branch stack size
 * @br_stack_pos: current position in @br_stack_rb
 * @mispred_all: mark all branches as mispredicted
 */
काष्ठा thपढ़ो_stack अणु
	काष्ठा thपढ़ो_stack_entry *stack;
	माप_प्रकार cnt;
	माप_प्रकार sz;
	u64 trace_nr;
	u64 branch_count;
	u64 insn_count;
	u64 cyc_count;
	u64 kernel_start;
	u64 last_समय;
	काष्ठा call_वापस_processor *crp;
	काष्ठा comm *comm;
	अचिन्हित पूर्णांक arr_sz;
	क्रमागत retpoline_state_t rstate;
	काष्ठा branch_stack *br_stack_rb;
	अचिन्हित पूर्णांक br_stack_sz;
	अचिन्हित पूर्णांक br_stack_pos;
	bool mispred_all;
पूर्ण;

/*
 * Assume pid == tid == 0 identअगरies the idle task as defined by
 * perf_session__रेजिस्टर_idle_thपढ़ो(). The idle task is really 1 task per cpu,
 * and thereक्रमe requires a stack क्रम each cpu.
 */
अटल अंतरभूत bool thपढ़ो_stack__per_cpu(काष्ठा thपढ़ो *thपढ़ो)
अणु
	वापस !(thपढ़ो->tid || thपढ़ो->pid_);
पूर्ण

अटल पूर्णांक thपढ़ो_stack__grow(काष्ठा thपढ़ो_stack *ts)
अणु
	काष्ठा thपढ़ो_stack_entry *new_stack;
	माप_प्रकार sz, new_sz;

	new_sz = ts->sz + STACK_GROWTH;
	sz = new_sz * माप(काष्ठा thपढ़ो_stack_entry);

	new_stack = पुनः_स्मृति(ts->stack, sz);
	अगर (!new_stack)
		वापस -ENOMEM;

	ts->stack = new_stack;
	ts->sz = new_sz;

	वापस 0;
पूर्ण

अटल पूर्णांक thपढ़ो_stack__init(काष्ठा thपढ़ो_stack *ts, काष्ठा thपढ़ो *thपढ़ो,
			      काष्ठा call_वापस_processor *crp,
			      bool callstack, अचिन्हित पूर्णांक br_stack_sz)
अणु
	पूर्णांक err;

	अगर (callstack) अणु
		err = thपढ़ो_stack__grow(ts);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (br_stack_sz) अणु
		माप_प्रकार sz = माप(काष्ठा branch_stack);

		sz += br_stack_sz * माप(काष्ठा branch_entry);
		ts->br_stack_rb = zalloc(sz);
		अगर (!ts->br_stack_rb)
			वापस -ENOMEM;
		ts->br_stack_sz = br_stack_sz;
	पूर्ण

	अगर (thपढ़ो->maps && thपढ़ो->maps->machine) अणु
		काष्ठा machine *machine = thपढ़ो->maps->machine;
		स्थिर अक्षर *arch = perf_env__arch(machine->env);

		ts->kernel_start = machine__kernel_start(machine);
		अगर (!म_भेद(arch, "x86"))
			ts->rstate = X86_RETPOLINE_POSSIBLE;
	पूर्ण अन्यथा अणु
		ts->kernel_start = 1ULL << 63;
	पूर्ण
	ts->crp = crp;

	वापस 0;
पूर्ण

अटल काष्ठा thपढ़ो_stack *thपढ़ो_stack__new(काष्ठा thपढ़ो *thपढ़ो, पूर्णांक cpu,
					      काष्ठा call_वापस_processor *crp,
					      bool callstack,
					      अचिन्हित पूर्णांक br_stack_sz)
अणु
	काष्ठा thपढ़ो_stack *ts = thपढ़ो->ts, *new_ts;
	अचिन्हित पूर्णांक old_sz = ts ? ts->arr_sz : 0;
	अचिन्हित पूर्णांक new_sz = 1;

	अगर (thपढ़ो_stack__per_cpu(thपढ़ो) && cpu > 0)
		new_sz = roundup_घात_of_two(cpu + 1);

	अगर (!ts || new_sz > old_sz) अणु
		new_ts = सुस्मृति(new_sz, माप(*ts));
		अगर (!new_ts)
			वापस शून्य;
		अगर (ts)
			स_नकल(new_ts, ts, old_sz * माप(*ts));
		new_ts->arr_sz = new_sz;
		zमुक्त(&thपढ़ो->ts);
		thपढ़ो->ts = new_ts;
		ts = new_ts;
	पूर्ण

	अगर (thपढ़ो_stack__per_cpu(thपढ़ो) && cpu > 0 &&
	    (अचिन्हित पूर्णांक)cpu < ts->arr_sz)
		ts += cpu;

	अगर (!ts->stack &&
	    thपढ़ो_stack__init(ts, thपढ़ो, crp, callstack, br_stack_sz))
		वापस शून्य;

	वापस ts;
पूर्ण

अटल काष्ठा thपढ़ो_stack *thपढ़ो__cpu_stack(काष्ठा thपढ़ो *thपढ़ो, पूर्णांक cpu)
अणु
	काष्ठा thपढ़ो_stack *ts = thपढ़ो->ts;

	अगर (cpu < 0)
		cpu = 0;

	अगर (!ts || (अचिन्हित पूर्णांक)cpu >= ts->arr_sz)
		वापस शून्य;

	ts += cpu;

	अगर (!ts->stack)
		वापस शून्य;

	वापस ts;
पूर्ण

अटल अंतरभूत काष्ठा thपढ़ो_stack *thपढ़ो__stack(काष्ठा thपढ़ो *thपढ़ो,
						    पूर्णांक cpu)
अणु
	अगर (!thपढ़ो)
		वापस शून्य;

	अगर (thपढ़ो_stack__per_cpu(thपढ़ो))
		वापस thपढ़ो__cpu_stack(thपढ़ो, cpu);

	वापस thपढ़ो->ts;
पूर्ण

अटल पूर्णांक thपढ़ो_stack__push(काष्ठा thपढ़ो_stack *ts, u64 ret_addr,
			      bool trace_end)
अणु
	पूर्णांक err = 0;

	अगर (ts->cnt == ts->sz) अणु
		err = thपढ़ो_stack__grow(ts);
		अगर (err) अणु
			pr_warning("Out of memory: discarding thread stack\n");
			ts->cnt = 0;
		पूर्ण
	पूर्ण

	ts->stack[ts->cnt].trace_end = trace_end;
	ts->stack[ts->cnt++].ret_addr = ret_addr;

	वापस err;
पूर्ण

अटल व्योम thपढ़ो_stack__pop(काष्ठा thपढ़ो_stack *ts, u64 ret_addr)
अणु
	माप_प्रकार i;

	/*
	 * In some हालs there may be functions which are not seen to वापस.
	 * For example when बनाओ_लाँघ / दीर्घ_लाँघ has been used.  Or the perf context
	 * चयन in the kernel which करोesn't stop and start tracing in exactly
	 * the same code path.  When that happens the वापस address will be
	 * further करोwn the stack.  If the वापस address is not found at all,
	 * we assume the opposite (i.e. this is a वापस क्रम a call that wasn't
	 * seen क्रम some reason) and leave the stack alone.
	 */
	क्रम (i = ts->cnt; i; ) अणु
		अगर (ts->stack[--i].ret_addr == ret_addr) अणु
			ts->cnt = i;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम thपढ़ो_stack__pop_trace_end(काष्ठा thपढ़ो_stack *ts)
अणु
	माप_प्रकार i;

	क्रम (i = ts->cnt; i; ) अणु
		अगर (ts->stack[--i].trace_end)
			ts->cnt = i;
		अन्यथा
			वापस;
	पूर्ण
पूर्ण

अटल bool thपढ़ो_stack__in_kernel(काष्ठा thपढ़ो_stack *ts)
अणु
	अगर (!ts->cnt)
		वापस false;

	वापस ts->stack[ts->cnt - 1].cp->in_kernel;
पूर्ण

अटल पूर्णांक thपढ़ो_stack__call_वापस(काष्ठा thपढ़ो *thपढ़ो,
				     काष्ठा thपढ़ो_stack *ts, माप_प्रकार idx,
				     u64 बारtamp, u64 ref, bool no_वापस)
अणु
	काष्ठा call_वापस_processor *crp = ts->crp;
	काष्ठा thपढ़ो_stack_entry *tse;
	काष्ठा call_वापस cr = अणु
		.thपढ़ो = thपढ़ो,
		.comm = ts->comm,
		.db_id = 0,
	पूर्ण;
	u64 *parent_db_id;

	tse = &ts->stack[idx];
	cr.cp = tse->cp;
	cr.call_समय = tse->बारtamp;
	cr.वापस_समय = बारtamp;
	cr.branch_count = ts->branch_count - tse->branch_count;
	cr.insn_count = ts->insn_count - tse->insn_count;
	cr.cyc_count = ts->cyc_count - tse->cyc_count;
	cr.db_id = tse->db_id;
	cr.call_ref = tse->ref;
	cr.वापस_ref = ref;
	अगर (tse->no_call)
		cr.flags |= CALL_RETURN_NO_CALL;
	अगर (no_वापस)
		cr.flags |= CALL_RETURN_NO_RETURN;
	अगर (tse->non_call)
		cr.flags |= CALL_RETURN_NON_CALL;

	/*
	 * The parent db_id must be asचिन्हित beक्रमe exporting the child. Note
	 * it is not possible to export the parent first because its inक्रमmation
	 * is not yet complete because its 'return' has not yet been processed.
	 */
	parent_db_id = idx ? &(tse - 1)->db_id : शून्य;

	वापस crp->process(&cr, parent_db_id, crp->data);
पूर्ण

अटल पूर्णांक __thपढ़ो_stack__flush(काष्ठा thपढ़ो *thपढ़ो, काष्ठा thपढ़ो_stack *ts)
अणु
	काष्ठा call_वापस_processor *crp = ts->crp;
	पूर्णांक err;

	अगर (!crp) अणु
		ts->cnt = 0;
		ts->br_stack_pos = 0;
		अगर (ts->br_stack_rb)
			ts->br_stack_rb->nr = 0;
		वापस 0;
	पूर्ण

	जबतक (ts->cnt) अणु
		err = thपढ़ो_stack__call_वापस(thपढ़ो, ts, --ts->cnt,
						ts->last_समय, 0, true);
		अगर (err) अणु
			pr_err("Error flushing thread stack!\n");
			ts->cnt = 0;
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक thपढ़ो_stack__flush(काष्ठा thपढ़ो *thपढ़ो)
अणु
	काष्ठा thपढ़ो_stack *ts = thपढ़ो->ts;
	अचिन्हित पूर्णांक pos;
	पूर्णांक err = 0;

	अगर (ts) अणु
		क्रम (pos = 0; pos < ts->arr_sz; pos++) अणु
			पूर्णांक ret = __thपढ़ो_stack__flush(thपढ़ो, ts + pos);

			अगर (ret)
				err = ret;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम thपढ़ो_stack__update_br_stack(काष्ठा thपढ़ो_stack *ts, u32 flags,
					  u64 from_ip, u64 to_ip)
अणु
	काष्ठा branch_stack *bs = ts->br_stack_rb;
	काष्ठा branch_entry *be;

	अगर (!ts->br_stack_pos)
		ts->br_stack_pos = ts->br_stack_sz;

	ts->br_stack_pos -= 1;

	be              = &bs->entries[ts->br_stack_pos];
	be->from        = from_ip;
	be->to          = to_ip;
	be->flags.value = 0;
	be->flags.पात = !!(flags & PERF_IP_FLAG_TX_ABORT);
	be->flags.in_tx = !!(flags & PERF_IP_FLAG_IN_TX);
	/* No support क्रम mispredict */
	be->flags.mispred = ts->mispred_all;

	अगर (bs->nr < ts->br_stack_sz)
		bs->nr += 1;
पूर्ण

पूर्णांक thपढ़ो_stack__event(काष्ठा thपढ़ो *thपढ़ो, पूर्णांक cpu, u32 flags, u64 from_ip,
			u64 to_ip, u16 insn_len, u64 trace_nr, bool callstack,
			अचिन्हित पूर्णांक br_stack_sz, bool mispred_all)
अणु
	काष्ठा thपढ़ो_stack *ts = thपढ़ो__stack(thपढ़ो, cpu);

	अगर (!thपढ़ो)
		वापस -EINVAL;

	अगर (!ts) अणु
		ts = thपढ़ो_stack__new(thपढ़ो, cpu, शून्य, callstack, br_stack_sz);
		अगर (!ts) अणु
			pr_warning("Out of memory: no thread stack\n");
			वापस -ENOMEM;
		पूर्ण
		ts->trace_nr = trace_nr;
		ts->mispred_all = mispred_all;
	पूर्ण

	/*
	 * When the trace is discontinuous, the trace_nr changes.  In that हाल
	 * the stack might be completely invalid.  Better to report nothing than
	 * to report something misleading, so flush the stack.
	 */
	अगर (trace_nr != ts->trace_nr) अणु
		अगर (ts->trace_nr)
			__thपढ़ो_stack__flush(thपढ़ो, ts);
		ts->trace_nr = trace_nr;
	पूर्ण

	अगर (br_stack_sz)
		thपढ़ो_stack__update_br_stack(ts, flags, from_ip, to_ip);

	/*
	 * Stop here अगर thपढ़ो_stack__process() is in use, or not recording call
	 * stack.
	 */
	अगर (ts->crp || !callstack)
		वापस 0;

	अगर (flags & PERF_IP_FLAG_CALL) अणु
		u64 ret_addr;

		अगर (!to_ip)
			वापस 0;
		ret_addr = from_ip + insn_len;
		अगर (ret_addr == to_ip)
			वापस 0; /* Zero-length calls are excluded */
		वापस thपढ़ो_stack__push(ts, ret_addr,
					  flags & PERF_IP_FLAG_TRACE_END);
	पूर्ण अन्यथा अगर (flags & PERF_IP_FLAG_TRACE_BEGIN) अणु
		/*
		 * If the caller did not change the trace number (which would
		 * have flushed the stack) then try to make sense of the stack.
		 * Possibly, tracing began after वापसing to the current
		 * address, so try to pop that. Also, करो not expect a call made
		 * when the trace ended, to वापस, so pop that.
		 */
		thपढ़ो_stack__pop(ts, to_ip);
		thपढ़ो_stack__pop_trace_end(ts);
	पूर्ण अन्यथा अगर ((flags & PERF_IP_FLAG_RETURN) && from_ip) अणु
		thपढ़ो_stack__pop(ts, to_ip);
	पूर्ण

	वापस 0;
पूर्ण

व्योम thपढ़ो_stack__set_trace_nr(काष्ठा thपढ़ो *thपढ़ो, पूर्णांक cpu, u64 trace_nr)
अणु
	काष्ठा thपढ़ो_stack *ts = thपढ़ो__stack(thपढ़ो, cpu);

	अगर (!ts)
		वापस;

	अगर (trace_nr != ts->trace_nr) अणु
		अगर (ts->trace_nr)
			__thपढ़ो_stack__flush(thपढ़ो, ts);
		ts->trace_nr = trace_nr;
	पूर्ण
पूर्ण

अटल व्योम __thपढ़ो_stack__मुक्त(काष्ठा thपढ़ो *thपढ़ो, काष्ठा thपढ़ो_stack *ts)
अणु
	__thपढ़ो_stack__flush(thपढ़ो, ts);
	zमुक्त(&ts->stack);
	zमुक्त(&ts->br_stack_rb);
पूर्ण

अटल व्योम thपढ़ो_stack__reset(काष्ठा thपढ़ो *thपढ़ो, काष्ठा thपढ़ो_stack *ts)
अणु
	अचिन्हित पूर्णांक arr_sz = ts->arr_sz;

	__thपढ़ो_stack__मुक्त(thपढ़ो, ts);
	स_रखो(ts, 0, माप(*ts));
	ts->arr_sz = arr_sz;
पूर्ण

व्योम thपढ़ो_stack__मुक्त(काष्ठा thपढ़ो *thपढ़ो)
अणु
	काष्ठा thपढ़ो_stack *ts = thपढ़ो->ts;
	अचिन्हित पूर्णांक pos;

	अगर (ts) अणु
		क्रम (pos = 0; pos < ts->arr_sz; pos++)
			__thपढ़ो_stack__मुक्त(thपढ़ो, ts + pos);
		zमुक्त(&thपढ़ो->ts);
	पूर्ण
पूर्ण

अटल अंतरभूत u64 callchain_context(u64 ip, u64 kernel_start)
अणु
	वापस ip < kernel_start ? PERF_CONTEXT_USER : PERF_CONTEXT_KERNEL;
पूर्ण

व्योम thपढ़ो_stack__sample(काष्ठा thपढ़ो *thपढ़ो, पूर्णांक cpu,
			  काष्ठा ip_callchain *chain,
			  माप_प्रकार sz, u64 ip, u64 kernel_start)
अणु
	काष्ठा thपढ़ो_stack *ts = thपढ़ो__stack(thपढ़ो, cpu);
	u64 context = callchain_context(ip, kernel_start);
	u64 last_context;
	माप_प्रकार i, j;

	अगर (sz < 2) अणु
		chain->nr = 0;
		वापस;
	पूर्ण

	chain->ips[0] = context;
	chain->ips[1] = ip;

	अगर (!ts) अणु
		chain->nr = 2;
		वापस;
	पूर्ण

	last_context = context;

	क्रम (i = 2, j = 1; i < sz && j <= ts->cnt; i++, j++) अणु
		ip = ts->stack[ts->cnt - j].ret_addr;
		context = callchain_context(ip, kernel_start);
		अगर (context != last_context) अणु
			अगर (i >= sz - 1)
				अवरोध;
			chain->ips[i++] = context;
			last_context = context;
		पूर्ण
		chain->ips[i] = ip;
	पूर्ण

	chain->nr = i;
पूर्ण

/*
 * Hardware sample records, created some समय after the event occurred, need to
 * have subsequent addresses हटाओd from the call chain.
 */
व्योम thपढ़ो_stack__sample_late(काष्ठा thपढ़ो *thपढ़ो, पूर्णांक cpu,
			       काष्ठा ip_callchain *chain, माप_प्रकार sz,
			       u64 sample_ip, u64 kernel_start)
अणु
	काष्ठा thपढ़ो_stack *ts = thपढ़ो__stack(thपढ़ो, cpu);
	u64 sample_context = callchain_context(sample_ip, kernel_start);
	u64 last_context, context, ip;
	माप_प्रकार nr = 0, j;

	अगर (sz < 2) अणु
		chain->nr = 0;
		वापस;
	पूर्ण

	अगर (!ts)
		जाओ out;

	/*
	 * When tracing kernel space, kernel addresses occur at the top of the
	 * call chain after the event occurred but beक्रमe tracing stopped.
	 * Skip them.
	 */
	क्रम (j = 1; j <= ts->cnt; j++) अणु
		ip = ts->stack[ts->cnt - j].ret_addr;
		context = callchain_context(ip, kernel_start);
		अगर (context == PERF_CONTEXT_USER ||
		    (context == sample_context && ip == sample_ip))
			अवरोध;
	पूर्ण

	last_context = sample_ip; /* Use sample_ip as an invalid context */

	क्रम (; nr < sz && j <= ts->cnt; nr++, j++) अणु
		ip = ts->stack[ts->cnt - j].ret_addr;
		context = callchain_context(ip, kernel_start);
		अगर (context != last_context) अणु
			अगर (nr >= sz - 1)
				अवरोध;
			chain->ips[nr++] = context;
			last_context = context;
		पूर्ण
		chain->ips[nr] = ip;
	पूर्ण
out:
	अगर (nr) अणु
		chain->nr = nr;
	पूर्ण अन्यथा अणु
		chain->ips[0] = sample_context;
		chain->ips[1] = sample_ip;
		chain->nr = 2;
	पूर्ण
पूर्ण

व्योम thपढ़ो_stack__br_sample(काष्ठा thपढ़ो *thपढ़ो, पूर्णांक cpu,
			     काष्ठा branch_stack *dst, अचिन्हित पूर्णांक sz)
अणु
	काष्ठा thपढ़ो_stack *ts = thपढ़ो__stack(thपढ़ो, cpu);
	स्थिर माप_प्रकार bsz = माप(काष्ठा branch_entry);
	काष्ठा branch_stack *src;
	काष्ठा branch_entry *be;
	अचिन्हित पूर्णांक nr;

	dst->nr = 0;

	अगर (!ts)
		वापस;

	src = ts->br_stack_rb;
	अगर (!src->nr)
		वापस;

	dst->nr = min((अचिन्हित पूर्णांक)src->nr, sz);

	be = &dst->entries[0];
	nr = min(ts->br_stack_sz - ts->br_stack_pos, (अचिन्हित पूर्णांक)dst->nr);
	स_नकल(be, &src->entries[ts->br_stack_pos], bsz * nr);

	अगर (src->nr >= ts->br_stack_sz) अणु
		sz -= nr;
		be = &dst->entries[nr];
		nr = min(ts->br_stack_pos, sz);
		स_नकल(be, &src->entries[0], bsz * ts->br_stack_pos);
	पूर्ण
पूर्ण

/* Start of user space branch entries */
अटल bool us_start(काष्ठा branch_entry *be, u64 kernel_start, bool *start)
अणु
	अगर (!*start)
		*start = be->to && be->to < kernel_start;

	वापस *start;
पूर्ण

/*
 * Start of branch entries after the ip fell in between 2 branches, or user
 * space branch entries.
 */
अटल bool ks_start(काष्ठा branch_entry *be, u64 sample_ip, u64 kernel_start,
		     bool *start, काष्ठा branch_entry *nb)
अणु
	अगर (!*start) अणु
		*start = (nb && sample_ip >= be->to && sample_ip <= nb->from) ||
			 be->from < kernel_start ||
			 (be->to && be->to < kernel_start);
	पूर्ण

	वापस *start;
पूर्ण

/*
 * Hardware sample records, created some समय after the event occurred, need to
 * have subsequent addresses हटाओd from the branch stack.
 */
व्योम thपढ़ो_stack__br_sample_late(काष्ठा thपढ़ो *thपढ़ो, पूर्णांक cpu,
				  काष्ठा branch_stack *dst, अचिन्हित पूर्णांक sz,
				  u64 ip, u64 kernel_start)
अणु
	काष्ठा thपढ़ो_stack *ts = thपढ़ो__stack(thपढ़ो, cpu);
	काष्ठा branch_entry *d, *s, *spos, *ssz;
	काष्ठा branch_stack *src;
	अचिन्हित पूर्णांक nr = 0;
	bool start = false;

	dst->nr = 0;

	अगर (!ts)
		वापस;

	src = ts->br_stack_rb;
	अगर (!src->nr)
		वापस;

	spos = &src->entries[ts->br_stack_pos];
	ssz  = &src->entries[ts->br_stack_sz];

	d = &dst->entries[0];
	s = spos;

	अगर (ip < kernel_start) अणु
		/*
		 * User space sample: start copying branch entries when the
		 * branch is in user space.
		 */
		क्रम (s = spos; s < ssz && nr < sz; s++) अणु
			अगर (us_start(s, kernel_start, &start)) अणु
				*d++ = *s;
				nr += 1;
			पूर्ण
		पूर्ण

		अगर (src->nr >= ts->br_stack_sz) अणु
			क्रम (s = &src->entries[0]; s < spos && nr < sz; s++) अणु
				अगर (us_start(s, kernel_start, &start)) अणु
					*d++ = *s;
					nr += 1;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा branch_entry *nb = शून्य;

		/*
		 * Kernel space sample: start copying branch entries when the ip
		 * falls in between 2 branches (or the branch is in user space
		 * because then the start must have been missed).
		 */
		क्रम (s = spos; s < ssz && nr < sz; s++) अणु
			अगर (ks_start(s, ip, kernel_start, &start, nb)) अणु
				*d++ = *s;
				nr += 1;
			पूर्ण
			nb = s;
		पूर्ण

		अगर (src->nr >= ts->br_stack_sz) अणु
			क्रम (s = &src->entries[0]; s < spos && nr < sz; s++) अणु
				अगर (ks_start(s, ip, kernel_start, &start, nb)) अणु
					*d++ = *s;
					nr += 1;
				पूर्ण
				nb = s;
			पूर्ण
		पूर्ण
	पूर्ण

	dst->nr = nr;
पूर्ण

काष्ठा call_वापस_processor *
call_वापस_processor__new(पूर्णांक (*process)(काष्ठा call_वापस *cr, u64 *parent_db_id, व्योम *data),
			   व्योम *data)
अणु
	काष्ठा call_वापस_processor *crp;

	crp = zalloc(माप(काष्ठा call_वापस_processor));
	अगर (!crp)
		वापस शून्य;
	crp->cpr = call_path_root__new();
	अगर (!crp->cpr)
		जाओ out_मुक्त;
	crp->process = process;
	crp->data = data;
	वापस crp;

out_मुक्त:
	मुक्त(crp);
	वापस शून्य;
पूर्ण

व्योम call_वापस_processor__मुक्त(काष्ठा call_वापस_processor *crp)
अणु
	अगर (crp) अणु
		call_path_root__मुक्त(crp->cpr);
		मुक्त(crp);
	पूर्ण
पूर्ण

अटल पूर्णांक thपढ़ो_stack__push_cp(काष्ठा thपढ़ो_stack *ts, u64 ret_addr,
				 u64 बारtamp, u64 ref, काष्ठा call_path *cp,
				 bool no_call, bool trace_end)
अणु
	काष्ठा thपढ़ो_stack_entry *tse;
	पूर्णांक err;

	अगर (!cp)
		वापस -ENOMEM;

	अगर (ts->cnt == ts->sz) अणु
		err = thपढ़ो_stack__grow(ts);
		अगर (err)
			वापस err;
	पूर्ण

	tse = &ts->stack[ts->cnt++];
	tse->ret_addr = ret_addr;
	tse->बारtamp = बारtamp;
	tse->ref = ref;
	tse->branch_count = ts->branch_count;
	tse->insn_count = ts->insn_count;
	tse->cyc_count = ts->cyc_count;
	tse->cp = cp;
	tse->no_call = no_call;
	tse->trace_end = trace_end;
	tse->non_call = false;
	tse->db_id = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक thपढ़ो_stack__pop_cp(काष्ठा thपढ़ो *thपढ़ो, काष्ठा thपढ़ो_stack *ts,
				u64 ret_addr, u64 बारtamp, u64 ref,
				काष्ठा symbol *sym)
अणु
	पूर्णांक err;

	अगर (!ts->cnt)
		वापस 1;

	अगर (ts->cnt == 1) अणु
		काष्ठा thपढ़ो_stack_entry *tse = &ts->stack[0];

		अगर (tse->cp->sym == sym)
			वापस thपढ़ो_stack__call_वापस(thपढ़ो, ts, --ts->cnt,
							 बारtamp, ref, false);
	पूर्ण

	अगर (ts->stack[ts->cnt - 1].ret_addr == ret_addr &&
	    !ts->stack[ts->cnt - 1].non_call) अणु
		वापस thपढ़ो_stack__call_वापस(thपढ़ो, ts, --ts->cnt,
						 बारtamp, ref, false);
	पूर्ण अन्यथा अणु
		माप_प्रकार i = ts->cnt - 1;

		जबतक (i--) अणु
			अगर (ts->stack[i].ret_addr != ret_addr ||
			    ts->stack[i].non_call)
				जारी;
			i += 1;
			जबतक (ts->cnt > i) अणु
				err = thपढ़ो_stack__call_वापस(thपढ़ो, ts,
								--ts->cnt,
								बारtamp, ref,
								true);
				अगर (err)
					वापस err;
			पूर्ण
			वापस thपढ़ो_stack__call_वापस(thपढ़ो, ts, --ts->cnt,
							 बारtamp, ref, false);
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक thपढ़ो_stack__bottom(काष्ठा thपढ़ो_stack *ts,
				काष्ठा perf_sample *sample,
				काष्ठा addr_location *from_al,
				काष्ठा addr_location *to_al, u64 ref)
अणु
	काष्ठा call_path_root *cpr = ts->crp->cpr;
	काष्ठा call_path *cp;
	काष्ठा symbol *sym;
	u64 ip;

	अगर (sample->ip) अणु
		ip = sample->ip;
		sym = from_al->sym;
	पूर्ण अन्यथा अगर (sample->addr) अणु
		ip = sample->addr;
		sym = to_al->sym;
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण

	cp = call_path__findnew(cpr, &cpr->call_path, sym, ip,
				ts->kernel_start);

	वापस thपढ़ो_stack__push_cp(ts, ip, sample->समय, ref, cp,
				     true, false);
पूर्ण

अटल पूर्णांक thपढ़ो_stack__pop_ks(काष्ठा thपढ़ो *thपढ़ो, काष्ठा thपढ़ो_stack *ts,
				काष्ठा perf_sample *sample, u64 ref)
अणु
	u64 पंचांग = sample->समय;
	पूर्णांक err;

	/* Return to userspace, so pop all kernel addresses */
	जबतक (thपढ़ो_stack__in_kernel(ts)) अणु
		err = thपढ़ो_stack__call_वापस(thपढ़ो, ts, --ts->cnt,
						पंचांग, ref, true);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक thपढ़ो_stack__no_call_वापस(काष्ठा thपढ़ो *thपढ़ो,
					काष्ठा thपढ़ो_stack *ts,
					काष्ठा perf_sample *sample,
					काष्ठा addr_location *from_al,
					काष्ठा addr_location *to_al, u64 ref)
अणु
	काष्ठा call_path_root *cpr = ts->crp->cpr;
	काष्ठा call_path *root = &cpr->call_path;
	काष्ठा symbol *fsym = from_al->sym;
	काष्ठा symbol *tsym = to_al->sym;
	काष्ठा call_path *cp, *parent;
	u64 ks = ts->kernel_start;
	u64 addr = sample->addr;
	u64 पंचांग = sample->समय;
	u64 ip = sample->ip;
	पूर्णांक err;

	अगर (ip >= ks && addr < ks) अणु
		/* Return to userspace, so pop all kernel addresses */
		err = thपढ़ो_stack__pop_ks(thपढ़ो, ts, sample, ref);
		अगर (err)
			वापस err;

		/* If the stack is empty, push the userspace address */
		अगर (!ts->cnt) अणु
			cp = call_path__findnew(cpr, root, tsym, addr, ks);
			वापस thपढ़ो_stack__push_cp(ts, 0, पंचांग, ref, cp, true,
						     false);
		पूर्ण
	पूर्ण अन्यथा अगर (thपढ़ो_stack__in_kernel(ts) && ip < ks) अणु
		/* Return to userspace, so pop all kernel addresses */
		err = thपढ़ो_stack__pop_ks(thपढ़ो, ts, sample, ref);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (ts->cnt)
		parent = ts->stack[ts->cnt - 1].cp;
	अन्यथा
		parent = root;

	अगर (parent->sym == from_al->sym) अणु
		/*
		 * At the bottom of the stack, assume the missing 'call' was
		 * beक्रमe the trace started. So, pop the current symbol and push
		 * the 'to' symbol.
		 */
		अगर (ts->cnt == 1) अणु
			err = thपढ़ो_stack__call_वापस(thपढ़ो, ts, --ts->cnt,
							पंचांग, ref, false);
			अगर (err)
				वापस err;
		पूर्ण

		अगर (!ts->cnt) अणु
			cp = call_path__findnew(cpr, root, tsym, addr, ks);

			वापस thपढ़ो_stack__push_cp(ts, addr, पंचांग, ref, cp,
						     true, false);
		पूर्ण

		/*
		 * Otherwise assume the 'return' is being used as a jump (e.g.
		 * retpoline) and just push the 'to' symbol.
		 */
		cp = call_path__findnew(cpr, parent, tsym, addr, ks);

		err = thपढ़ो_stack__push_cp(ts, 0, पंचांग, ref, cp, true, false);
		अगर (!err)
			ts->stack[ts->cnt - 1].non_call = true;

		वापस err;
	पूर्ण

	/*
	 * Assume 'parent' has not yet returned, so push 'to', and then push and
	 * pop 'from'.
	 */

	cp = call_path__findnew(cpr, parent, tsym, addr, ks);

	err = thपढ़ो_stack__push_cp(ts, addr, पंचांग, ref, cp, true, false);
	अगर (err)
		वापस err;

	cp = call_path__findnew(cpr, cp, fsym, ip, ks);

	err = thपढ़ो_stack__push_cp(ts, ip, पंचांग, ref, cp, true, false);
	अगर (err)
		वापस err;

	वापस thपढ़ो_stack__call_वापस(thपढ़ो, ts, --ts->cnt, पंचांग, ref, false);
पूर्ण

अटल पूर्णांक thपढ़ो_stack__trace_begin(काष्ठा thपढ़ो *thपढ़ो,
				     काष्ठा thपढ़ो_stack *ts, u64 बारtamp,
				     u64 ref)
अणु
	काष्ठा thपढ़ो_stack_entry *tse;
	पूर्णांक err;

	अगर (!ts->cnt)
		वापस 0;

	/* Pop trace end */
	tse = &ts->stack[ts->cnt - 1];
	अगर (tse->trace_end) अणु
		err = thपढ़ो_stack__call_वापस(thपढ़ो, ts, --ts->cnt,
						बारtamp, ref, false);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक thपढ़ो_stack__trace_end(काष्ठा thपढ़ो_stack *ts,
				   काष्ठा perf_sample *sample, u64 ref)
अणु
	काष्ठा call_path_root *cpr = ts->crp->cpr;
	काष्ठा call_path *cp;
	u64 ret_addr;

	/* No poपूर्णांक having 'trace end' on the bottom of the stack */
	अगर (!ts->cnt || (ts->cnt == 1 && ts->stack[0].ref == ref))
		वापस 0;

	cp = call_path__findnew(cpr, ts->stack[ts->cnt - 1].cp, शून्य, 0,
				ts->kernel_start);

	ret_addr = sample->ip + sample->insn_len;

	वापस thपढ़ो_stack__push_cp(ts, ret_addr, sample->समय, ref, cp,
				     false, true);
पूर्ण

अटल bool is_x86_retpoline(स्थिर अक्षर *name)
अणु
	स्थिर अक्षर *p = म_माला(name, "__x86_indirect_thunk_");

	वापस p == name || !म_भेद(name, "__indirect_thunk_start");
पूर्ण

/*
 * x86 retpoline functions pollute the call graph. This function हटाओs them.
 * This करोes not handle function वापस thunks, nor is there any improvement
 * क्रम the handling of अंतरभूत thunks or बाह्य thunks.
 */
अटल पूर्णांक thपढ़ो_stack__x86_retpoline(काष्ठा thपढ़ो_stack *ts,
				       काष्ठा perf_sample *sample,
				       काष्ठा addr_location *to_al)
अणु
	काष्ठा thपढ़ो_stack_entry *tse = &ts->stack[ts->cnt - 1];
	काष्ठा call_path_root *cpr = ts->crp->cpr;
	काष्ठा symbol *sym = tse->cp->sym;
	काष्ठा symbol *tsym = to_al->sym;
	काष्ठा call_path *cp;

	अगर (sym && is_x86_retpoline(sym->name)) अणु
		/*
		 * This is a x86 retpoline fn. It pollutes the call graph by
		 * showing up everywhere there is an indirect branch, but करोes
		 * not itself mean anything. Here the top-of-stack is हटाओd,
		 * by decrementing the stack count, and then further करोwn, the
		 * resulting top-of-stack is replaced with the actual target.
		 * The result is that the retpoline functions will no दीर्घer
		 * appear in the call graph. Note this only affects the call
		 * graph, since all the original branches are left unchanged.
		 */
		ts->cnt -= 1;
		sym = ts->stack[ts->cnt - 2].cp->sym;
		अगर (sym && sym == tsym && to_al->addr != tsym->start) अणु
			/*
			 * Target is back to the middle of the symbol we came
			 * from so assume it is an indirect jmp and क्रमget it
			 * altogether.
			 */
			ts->cnt -= 1;
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अगर (sym && sym == tsym) अणु
		/*
		 * Target is back to the symbol we came from so assume it is an
		 * indirect jmp and क्रमget it altogether.
		 */
		ts->cnt -= 1;
		वापस 0;
	पूर्ण

	cp = call_path__findnew(cpr, ts->stack[ts->cnt - 2].cp, tsym,
				sample->addr, ts->kernel_start);
	अगर (!cp)
		वापस -ENOMEM;

	/* Replace the top-of-stack with the actual target */
	ts->stack[ts->cnt - 1].cp = cp;

	वापस 0;
पूर्ण

पूर्णांक thपढ़ो_stack__process(काष्ठा thपढ़ो *thपढ़ो, काष्ठा comm *comm,
			  काष्ठा perf_sample *sample,
			  काष्ठा addr_location *from_al,
			  काष्ठा addr_location *to_al, u64 ref,
			  काष्ठा call_वापस_processor *crp)
अणु
	काष्ठा thपढ़ो_stack *ts = thपढ़ो__stack(thपढ़ो, sample->cpu);
	क्रमागत retpoline_state_t rstate;
	पूर्णांक err = 0;

	अगर (ts && !ts->crp) अणु
		/* Supersede thपढ़ो_stack__event() */
		thपढ़ो_stack__reset(thपढ़ो, ts);
		ts = शून्य;
	पूर्ण

	अगर (!ts) अणु
		ts = thपढ़ो_stack__new(thपढ़ो, sample->cpu, crp, true, 0);
		अगर (!ts)
			वापस -ENOMEM;
		ts->comm = comm;
	पूर्ण

	rstate = ts->rstate;
	अगर (rstate == X86_RETPOLINE_DETECTED)
		ts->rstate = X86_RETPOLINE_POSSIBLE;

	/* Flush stack on exec */
	अगर (ts->comm != comm && thपढ़ो->pid_ == thपढ़ो->tid) अणु
		err = __thपढ़ो_stack__flush(thपढ़ो, ts);
		अगर (err)
			वापस err;
		ts->comm = comm;
	पूर्ण

	/* If the stack is empty, put the current symbol on the stack */
	अगर (!ts->cnt) अणु
		err = thपढ़ो_stack__bottom(ts, sample, from_al, to_al, ref);
		अगर (err)
			वापस err;
	पूर्ण

	ts->branch_count += 1;
	ts->insn_count += sample->insn_cnt;
	ts->cyc_count += sample->cyc_cnt;
	ts->last_समय = sample->समय;

	अगर (sample->flags & PERF_IP_FLAG_CALL) अणु
		bool trace_end = sample->flags & PERF_IP_FLAG_TRACE_END;
		काष्ठा call_path_root *cpr = ts->crp->cpr;
		काष्ठा call_path *cp;
		u64 ret_addr;

		अगर (!sample->ip || !sample->addr)
			वापस 0;

		ret_addr = sample->ip + sample->insn_len;
		अगर (ret_addr == sample->addr)
			वापस 0; /* Zero-length calls are excluded */

		cp = call_path__findnew(cpr, ts->stack[ts->cnt - 1].cp,
					to_al->sym, sample->addr,
					ts->kernel_start);
		err = thपढ़ो_stack__push_cp(ts, ret_addr, sample->समय, ref,
					    cp, false, trace_end);

		/*
		 * A call to the same symbol but not the start of the symbol,
		 * may be the start of a x86 retpoline.
		 */
		अगर (!err && rstate == X86_RETPOLINE_POSSIBLE && to_al->sym &&
		    from_al->sym == to_al->sym &&
		    to_al->addr != to_al->sym->start)
			ts->rstate = X86_RETPOLINE_DETECTED;

	पूर्ण अन्यथा अगर (sample->flags & PERF_IP_FLAG_RETURN) अणु
		अगर (!sample->addr) अणु
			u32 वापस_from_kernel = PERF_IP_FLAG_SYSCALLRET |
						 PERF_IP_FLAG_INTERRUPT;

			अगर (!(sample->flags & वापस_from_kernel))
				वापस 0;

			/* Pop kernel stack */
			वापस thपढ़ो_stack__pop_ks(thपढ़ो, ts, sample, ref);
		पूर्ण

		अगर (!sample->ip)
			वापस 0;

		/* x86 retpoline 'return' doesn't match the stack */
		अगर (rstate == X86_RETPOLINE_DETECTED && ts->cnt > 2 &&
		    ts->stack[ts->cnt - 1].ret_addr != sample->addr)
			वापस thपढ़ो_stack__x86_retpoline(ts, sample, to_al);

		err = thपढ़ो_stack__pop_cp(thपढ़ो, ts, sample->addr,
					   sample->समय, ref, from_al->sym);
		अगर (err) अणु
			अगर (err < 0)
				वापस err;
			err = thपढ़ो_stack__no_call_वापस(thपढ़ो, ts, sample,
							   from_al, to_al, ref);
		पूर्ण
	पूर्ण अन्यथा अगर (sample->flags & PERF_IP_FLAG_TRACE_BEGIN) अणु
		err = thपढ़ो_stack__trace_begin(thपढ़ो, ts, sample->समय, ref);
	पूर्ण अन्यथा अगर (sample->flags & PERF_IP_FLAG_TRACE_END) अणु
		err = thपढ़ो_stack__trace_end(ts, sample, ref);
	पूर्ण अन्यथा अगर (sample->flags & PERF_IP_FLAG_BRANCH &&
		   from_al->sym != to_al->sym && to_al->sym &&
		   to_al->addr == to_al->sym->start) अणु
		काष्ठा call_path_root *cpr = ts->crp->cpr;
		काष्ठा call_path *cp;

		/*
		 * The compiler might optimize a call/ret combination by making
		 * it a jmp. Make that visible by recording on the stack a
		 * branch to the start of a dअगरferent symbol. Note, that means
		 * when a ret pops the stack, all jmps must be popped off first.
		 */
		cp = call_path__findnew(cpr, ts->stack[ts->cnt - 1].cp,
					to_al->sym, sample->addr,
					ts->kernel_start);
		err = thपढ़ो_stack__push_cp(ts, 0, sample->समय, ref, cp, false,
					    false);
		अगर (!err)
			ts->stack[ts->cnt - 1].non_call = true;
	पूर्ण

	वापस err;
पूर्ण

माप_प्रकार thपढ़ो_stack__depth(काष्ठा thपढ़ो *thपढ़ो, पूर्णांक cpu)
अणु
	काष्ठा thपढ़ो_stack *ts = thपढ़ो__stack(thपढ़ो, cpu);

	अगर (!ts)
		वापस 0;
	वापस ts->cnt;
पूर्ण
