<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Restartable sequences प्रणाली call
 *
 * Copyright (C) 2015, Google, Inc.,
 * Paul Turner <pjt@google.com> and Andrew Hunter <ahh@google.com>
 * Copyright (C) 2015-2018, EfficiOS Inc.,
 * Mathieu Desnoyers <mathieu.desnoyers@efficios.com>
 */

#समावेश <linux/sched.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/rseq.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/ptrace.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/rseq.h>

#घोषणा RSEQ_CS_PREEMPT_MIGRATE_FLAGS (RSEQ_CS_FLAG_NO_RESTART_ON_MIGRATE | \
				       RSEQ_CS_FLAG_NO_RESTART_ON_PREEMPT)

/*
 *
 * Restartable sequences are a lightweight पूर्णांकerface that allows
 * user-level code to be executed atomically relative to scheduler
 * preemption and संकेत delivery. Typically used क्रम implementing
 * per-cpu operations.
 *
 * It allows user-space to perक्रमm update operations on per-cpu data
 * without requiring heavy-weight atomic operations.
 *
 * Detailed algorithm of rseq user-space assembly sequences:
 *
 *                     init(rseq_cs)
 *                     cpu = TLS->rseq::cpu_id_start
 *   [1]               TLS->rseq::rseq_cs = rseq_cs
 *   [start_ip]        ----------------------------
 *   [2]               अगर (cpu != TLS->rseq::cpu_id)
 *                             जाओ पात_ip;
 *   [3]               <last_inकाष्ठाion_in_cs>
 *   [post_commit_ip]  ----------------------------
 *
 *   The address of jump target पात_ip must be outside the critical
 *   region, i.e.:
 *
 *     [पात_ip] < [start_ip]  || [पात_ip] >= [post_commit_ip]
 *
 *   Steps [2]-[3] (inclusive) need to be a sequence of inकाष्ठाions in
 *   userspace that can handle being पूर्णांकerrupted between any of those
 *   inकाष्ठाions, and then resumed to the पात_ip.
 *
 *   1.  Userspace stores the address of the काष्ठा rseq_cs assembly
 *       block descriptor पूर्णांकo the rseq_cs field of the रेजिस्टरed
 *       काष्ठा rseq TLS area. This update is perक्रमmed through a single
 *       store within the अंतरभूत assembly inकाष्ठाion sequence.
 *       [start_ip]
 *
 *   2.  Userspace tests to check whether the current cpu_id field match
 *       the cpu number loaded beक्रमe start_ip, branching to पात_ip
 *       in हाल of a mismatch.
 *
 *       If the sequence is preempted or पूर्णांकerrupted by a संकेत
 *       at or after start_ip and beक्रमe post_commit_ip, then the kernel
 *       clears TLS->__rseq_abi::rseq_cs, and sets the user-space वापस
 *       ip to पात_ip beक्रमe वापसing to user-space, so the preempted
 *       execution resumes at पात_ip.
 *
 *   3.  Userspace critical section final inकाष्ठाion beक्रमe
 *       post_commit_ip is the commit. The critical section is
 *       self-terminating.
 *       [post_commit_ip]
 *
 *   4.  <success>
 *
 *   On failure at [2], or अगर पूर्णांकerrupted by preempt or संकेत delivery
 *   between [1] and [3]:
 *
 *       [पात_ip]
 *   F1. <failure>
 */

अटल पूर्णांक rseq_update_cpu_id(काष्ठा task_काष्ठा *t)
अणु
	u32 cpu_id = raw_smp_processor_id();
	काष्ठा rseq __user *rseq = t->rseq;

	अगर (!user_ग_लिखो_access_begin(rseq, माप(*rseq)))
		जाओ efault;
	unsafe_put_user(cpu_id, &rseq->cpu_id_start, efault_end);
	unsafe_put_user(cpu_id, &rseq->cpu_id, efault_end);
	user_ग_लिखो_access_end();
	trace_rseq_update(t);
	वापस 0;

efault_end:
	user_ग_लिखो_access_end();
efault:
	वापस -EFAULT;
पूर्ण

अटल पूर्णांक rseq_reset_rseq_cpu_id(काष्ठा task_काष्ठा *t)
अणु
	u32 cpu_id_start = 0, cpu_id = RSEQ_CPU_ID_UNINITIALIZED;

	/*
	 * Reset cpu_id_start to its initial state (0).
	 */
	अगर (put_user(cpu_id_start, &t->rseq->cpu_id_start))
		वापस -EFAULT;
	/*
	 * Reset cpu_id to RSEQ_CPU_ID_UNINITIALIZED, so any user coming
	 * in after unregistration can figure out that rseq needs to be
	 * रेजिस्टरed again.
	 */
	अगर (put_user(cpu_id, &t->rseq->cpu_id))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक rseq_get_rseq_cs(काष्ठा task_काष्ठा *t, काष्ठा rseq_cs *rseq_cs)
अणु
	काष्ठा rseq_cs __user *urseq_cs;
	u64 ptr;
	u32 __user *usig;
	u32 sig;
	पूर्णांक ret;

#अगर_घोषित CONFIG_64BIT
	अगर (get_user(ptr, &t->rseq->rseq_cs.ptr64))
		वापस -EFAULT;
#अन्यथा
	अगर (copy_from_user(&ptr, &t->rseq->rseq_cs.ptr64, माप(ptr)))
		वापस -EFAULT;
#पूर्ण_अगर
	अगर (!ptr) अणु
		स_रखो(rseq_cs, 0, माप(*rseq_cs));
		वापस 0;
	पूर्ण
	अगर (ptr >= TASK_SIZE)
		वापस -EINVAL;
	urseq_cs = (काष्ठा rseq_cs __user *)(अचिन्हित दीर्घ)ptr;
	अगर (copy_from_user(rseq_cs, urseq_cs, माप(*rseq_cs)))
		वापस -EFAULT;

	अगर (rseq_cs->start_ip >= TASK_SIZE ||
	    rseq_cs->start_ip + rseq_cs->post_commit_offset >= TASK_SIZE ||
	    rseq_cs->पात_ip >= TASK_SIZE ||
	    rseq_cs->version > 0)
		वापस -EINVAL;
	/* Check क्रम overflow. */
	अगर (rseq_cs->start_ip + rseq_cs->post_commit_offset < rseq_cs->start_ip)
		वापस -EINVAL;
	/* Ensure that पात_ip is not in the critical section. */
	अगर (rseq_cs->पात_ip - rseq_cs->start_ip < rseq_cs->post_commit_offset)
		वापस -EINVAL;

	usig = (u32 __user *)(अचिन्हित दीर्घ)(rseq_cs->पात_ip - माप(u32));
	ret = get_user(sig, usig);
	अगर (ret)
		वापस ret;

	अगर (current->rseq_sig != sig) अणु
		prपूर्णांकk_ratelimited(KERN_WARNING
			"Possible attack attempt. Unexpected rseq signature 0x%x, expecting 0x%x (pid=%d, addr=%p).\n",
			sig, current->rseq_sig, current->pid, usig);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rseq_need_restart(काष्ठा task_काष्ठा *t, u32 cs_flags)
अणु
	u32 flags, event_mask;
	पूर्णांक ret;

	/* Get thपढ़ो flags. */
	ret = get_user(flags, &t->rseq->flags);
	अगर (ret)
		वापस ret;

	/* Take critical section flags पूर्णांकo account. */
	flags |= cs_flags;

	/*
	 * Restart on संकेत can only be inhibited when restart on
	 * preempt and restart on migrate are inhibited too. Otherwise,
	 * a preempted संकेत handler could fail to restart the prior
	 * execution context on sigवापस.
	 */
	अगर (unlikely((flags & RSEQ_CS_FLAG_NO_RESTART_ON_SIGNAL) &&
		     (flags & RSEQ_CS_PREEMPT_MIGRATE_FLAGS) !=
		     RSEQ_CS_PREEMPT_MIGRATE_FLAGS))
		वापस -EINVAL;

	/*
	 * Load and clear event mask atomically with respect to
	 * scheduler preemption.
	 */
	preempt_disable();
	event_mask = t->rseq_event_mask;
	t->rseq_event_mask = 0;
	preempt_enable();

	वापस !!(event_mask & ~flags);
पूर्ण

अटल पूर्णांक clear_rseq_cs(काष्ठा task_काष्ठा *t)
अणु
	/*
	 * The rseq_cs field is set to शून्य on preemption or संकेत
	 * delivery on top of rseq assembly block, as well as on top
	 * of code outside of the rseq assembly block. This perक्रमms
	 * a lazy clear of the rseq_cs field.
	 *
	 * Set rseq_cs to शून्य.
	 */
#अगर_घोषित CONFIG_64BIT
	वापस put_user(0UL, &t->rseq->rseq_cs.ptr64);
#अन्यथा
	अगर (clear_user(&t->rseq->rseq_cs.ptr64, माप(t->rseq->rseq_cs.ptr64)))
		वापस -EFAULT;
	वापस 0;
#पूर्ण_अगर
पूर्ण

/*
 * Unचिन्हित comparison will be true when ip >= start_ip, and when
 * ip < start_ip + post_commit_offset.
 */
अटल bool in_rseq_cs(अचिन्हित दीर्घ ip, काष्ठा rseq_cs *rseq_cs)
अणु
	वापस ip - rseq_cs->start_ip < rseq_cs->post_commit_offset;
पूर्ण

अटल पूर्णांक rseq_ip_fixup(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ ip = inकाष्ठाion_poपूर्णांकer(regs);
	काष्ठा task_काष्ठा *t = current;
	काष्ठा rseq_cs rseq_cs;
	पूर्णांक ret;

	ret = rseq_get_rseq_cs(t, &rseq_cs);
	अगर (ret)
		वापस ret;

	/*
	 * Handle potentially not being within a critical section.
	 * If not nested over a rseq critical section, restart is useless.
	 * Clear the rseq_cs poपूर्णांकer and वापस.
	 */
	अगर (!in_rseq_cs(ip, &rseq_cs))
		वापस clear_rseq_cs(t);
	ret = rseq_need_restart(t, rseq_cs.flags);
	अगर (ret <= 0)
		वापस ret;
	ret = clear_rseq_cs(t);
	अगर (ret)
		वापस ret;
	trace_rseq_ip_fixup(ip, rseq_cs.start_ip, rseq_cs.post_commit_offset,
			    rseq_cs.पात_ip);
	inकाष्ठाion_poपूर्णांकer_set(regs, (अचिन्हित दीर्घ)rseq_cs.पात_ip);
	वापस 0;
पूर्ण

/*
 * This resume handler must always be executed between any of:
 * - preemption,
 * - संकेत delivery,
 * and वापस to user-space.
 *
 * This is how we can ensure that the entire rseq critical section
 * will issue the commit inकाष्ठाion only अगर executed atomically with
 * respect to other thपढ़ोs scheduled on the same CPU, and with respect
 * to संकेत handlers.
 */
व्योम __rseq_handle_notअगरy_resume(काष्ठा kसंकेत *ksig, काष्ठा pt_regs *regs)
अणु
	काष्ठा task_काष्ठा *t = current;
	पूर्णांक ret, sig;

	अगर (unlikely(t->flags & PF_EXITING))
		वापस;
	ret = rseq_ip_fixup(regs);
	अगर (unlikely(ret < 0))
		जाओ error;
	अगर (unlikely(rseq_update_cpu_id(t)))
		जाओ error;
	वापस;

error:
	sig = ksig ? ksig->sig : 0;
	क्रमce_sigsegv(sig);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_RSEQ

/*
 * Terminate the process अगर a syscall is issued within a restartable
 * sequence.
 */
व्योम rseq_syscall(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ ip = inकाष्ठाion_poपूर्णांकer(regs);
	काष्ठा task_काष्ठा *t = current;
	काष्ठा rseq_cs rseq_cs;

	अगर (!t->rseq)
		वापस;
	अगर (rseq_get_rseq_cs(t, &rseq_cs) || in_rseq_cs(ip, &rseq_cs))
		क्रमce_sig(संक_अंश);
पूर्ण

#पूर्ण_अगर

/*
 * sys_rseq - setup restartable sequences क्रम caller thपढ़ो.
 */
SYSCALL_DEFINE4(rseq, काष्ठा rseq __user *, rseq, u32, rseq_len,
		पूर्णांक, flags, u32, sig)
अणु
	पूर्णांक ret;

	अगर (flags & RSEQ_FLAG_UNREGISTER) अणु
		अगर (flags & ~RSEQ_FLAG_UNREGISTER)
			वापस -EINVAL;
		/* Unरेजिस्टर rseq क्रम current thपढ़ो. */
		अगर (current->rseq != rseq || !current->rseq)
			वापस -EINVAL;
		अगर (rseq_len != माप(*rseq))
			वापस -EINVAL;
		अगर (current->rseq_sig != sig)
			वापस -EPERM;
		ret = rseq_reset_rseq_cpu_id(current);
		अगर (ret)
			वापस ret;
		current->rseq = शून्य;
		current->rseq_sig = 0;
		वापस 0;
	पूर्ण

	अगर (unlikely(flags))
		वापस -EINVAL;

	अगर (current->rseq) अणु
		/*
		 * If rseq is alपढ़ोy रेजिस्टरed, check whether
		 * the provided address dअगरfers from the prior
		 * one.
		 */
		अगर (current->rseq != rseq || rseq_len != माप(*rseq))
			वापस -EINVAL;
		अगर (current->rseq_sig != sig)
			वापस -EPERM;
		/* Alपढ़ोy रेजिस्टरed. */
		वापस -EBUSY;
	पूर्ण

	/*
	 * If there was no rseq previously रेजिस्टरed,
	 * ensure the provided rseq is properly aligned and valid.
	 */
	अगर (!IS_ALIGNED((अचिन्हित दीर्घ)rseq, __alignof__(*rseq)) ||
	    rseq_len != माप(*rseq))
		वापस -EINVAL;
	अगर (!access_ok(rseq, rseq_len))
		वापस -EFAULT;
	current->rseq = rseq;
	current->rseq_sig = sig;
	/*
	 * If rseq was previously inactive, and has just been
	 * रेजिस्टरed, ensure the cpu_id_start and cpu_id fields
	 * are updated beक्रमe वापसing to user-space.
	 */
	rseq_set_notअगरy_resume(current);

	वापस 0;
पूर्ण
