<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/hw_अवरोधpoपूर्णांक.c
 *
 * Unअगरied kernel/user-space hardware अवरोधpoपूर्णांक facility क्रम the on-chip UBC.
 *
 * Copyright (C) 2009 - 2010  Paul Mundt
 */
#समावेश <linux/init.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/hw_अवरोधpoपूर्णांक.h>
#समावेश <linux/percpu.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <यंत्र/hw_अवरोधpoपूर्णांक.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/traps.h>

/*
 * Stores the अवरोधpoपूर्णांकs currently in use on each अवरोधpoपूर्णांक address
 * रेजिस्टर क्रम each cpus
 */
अटल DEFINE_PER_CPU(काष्ठा perf_event *, bp_per_reg[HBP_NUM]);

/*
 * A dummy placeholder क्रम early accesses until the CPUs get a chance to
 * रेजिस्टर their UBCs later in the boot process.
 */
अटल काष्ठा sh_ubc ubc_dummy = अणु .num_events = 0 पूर्ण;

अटल काष्ठा sh_ubc *sh_ubc __पढ़ो_mostly = &ubc_dummy;

/*
 * Install a perf counter अवरोधpoपूर्णांक.
 *
 * We seek a मुक्त UBC channel and use it क्रम this अवरोधpoपूर्णांक.
 *
 * Atomic: we hold the counter->ctx->lock and we only handle variables
 * and रेजिस्टरs local to this cpu.
 */
पूर्णांक arch_install_hw_अवरोधpoपूर्णांक(काष्ठा perf_event *bp)
अणु
	काष्ठा arch_hw_अवरोधpoपूर्णांक *info = counter_arch_bp(bp);
	पूर्णांक i;

	क्रम (i = 0; i < sh_ubc->num_events; i++) अणु
		काष्ठा perf_event **slot = this_cpu_ptr(&bp_per_reg[i]);

		अगर (!*slot) अणु
			*slot = bp;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (WARN_ONCE(i == sh_ubc->num_events, "Can't find any breakpoint slot"))
		वापस -EBUSY;

	clk_enable(sh_ubc->clk);
	sh_ubc->enable(info, i);

	वापस 0;
पूर्ण

/*
 * Uninstall the अवरोधpoपूर्णांक contained in the given counter.
 *
 * First we search the debug address रेजिस्टर it uses and then we disable
 * it.
 *
 * Atomic: we hold the counter->ctx->lock and we only handle variables
 * and रेजिस्टरs local to this cpu.
 */
व्योम arch_uninstall_hw_अवरोधpoपूर्णांक(काष्ठा perf_event *bp)
अणु
	काष्ठा arch_hw_अवरोधpoपूर्णांक *info = counter_arch_bp(bp);
	पूर्णांक i;

	क्रम (i = 0; i < sh_ubc->num_events; i++) अणु
		काष्ठा perf_event **slot = this_cpu_ptr(&bp_per_reg[i]);

		अगर (*slot == bp) अणु
			*slot = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (WARN_ONCE(i == sh_ubc->num_events, "Can't find any breakpoint slot"))
		वापस;

	sh_ubc->disable(info, i);
	clk_disable(sh_ubc->clk);
पूर्ण

अटल पूर्णांक get_hbp_len(u16 hbp_len)
अणु
	अचिन्हित पूर्णांक len_in_bytes = 0;

	चयन (hbp_len) अणु
	हाल SH_BREAKPOINT_LEN_1:
		len_in_bytes = 1;
		अवरोध;
	हाल SH_BREAKPOINT_LEN_2:
		len_in_bytes = 2;
		अवरोध;
	हाल SH_BREAKPOINT_LEN_4:
		len_in_bytes = 4;
		अवरोध;
	हाल SH_BREAKPOINT_LEN_8:
		len_in_bytes = 8;
		अवरोध;
	पूर्ण
	वापस len_in_bytes;
पूर्ण

/*
 * Check क्रम भव address in kernel space.
 */
पूर्णांक arch_check_bp_in_kernelspace(काष्ठा arch_hw_अवरोधpoपूर्णांक *hw)
अणु
	अचिन्हित पूर्णांक len;
	अचिन्हित दीर्घ va;

	va = hw->address;
	len = get_hbp_len(hw->len);

	वापस (va >= TASK_SIZE) && ((va + len - 1) >= TASK_SIZE);
पूर्ण

पूर्णांक arch_bp_generic_fields(पूर्णांक sh_len, पूर्णांक sh_type,
			   पूर्णांक *gen_len, पूर्णांक *gen_type)
अणु
	/* Len */
	चयन (sh_len) अणु
	हाल SH_BREAKPOINT_LEN_1:
		*gen_len = HW_BREAKPOINT_LEN_1;
		अवरोध;
	हाल SH_BREAKPOINT_LEN_2:
		*gen_len = HW_BREAKPOINT_LEN_2;
		अवरोध;
	हाल SH_BREAKPOINT_LEN_4:
		*gen_len = HW_BREAKPOINT_LEN_4;
		अवरोध;
	हाल SH_BREAKPOINT_LEN_8:
		*gen_len = HW_BREAKPOINT_LEN_8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Type */
	चयन (sh_type) अणु
	हाल SH_BREAKPOINT_READ:
		*gen_type = HW_BREAKPOINT_R;
		अवरोध;
	हाल SH_BREAKPOINT_WRITE:
		*gen_type = HW_BREAKPOINT_W;
		अवरोध;
	हाल SH_BREAKPOINT_RW:
		*gen_type = HW_BREAKPOINT_W | HW_BREAKPOINT_R;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक arch_build_bp_info(काष्ठा perf_event *bp,
			      स्थिर काष्ठा perf_event_attr *attr,
			      काष्ठा arch_hw_अवरोधpoपूर्णांक *hw)
अणु
	hw->address = attr->bp_addr;

	/* Len */
	चयन (attr->bp_len) अणु
	हाल HW_BREAKPOINT_LEN_1:
		hw->len = SH_BREAKPOINT_LEN_1;
		अवरोध;
	हाल HW_BREAKPOINT_LEN_2:
		hw->len = SH_BREAKPOINT_LEN_2;
		अवरोध;
	हाल HW_BREAKPOINT_LEN_4:
		hw->len = SH_BREAKPOINT_LEN_4;
		अवरोध;
	हाल HW_BREAKPOINT_LEN_8:
		hw->len = SH_BREAKPOINT_LEN_8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Type */
	चयन (attr->bp_type) अणु
	हाल HW_BREAKPOINT_R:
		hw->type = SH_BREAKPOINT_READ;
		अवरोध;
	हाल HW_BREAKPOINT_W:
		hw->type = SH_BREAKPOINT_WRITE;
		अवरोध;
	हाल HW_BREAKPOINT_W | HW_BREAKPOINT_R:
		hw->type = SH_BREAKPOINT_RW;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Validate the arch-specअगरic HW Breakpoपूर्णांक रेजिस्टर settings
 */
पूर्णांक hw_अवरोधpoपूर्णांक_arch_parse(काष्ठा perf_event *bp,
			     स्थिर काष्ठा perf_event_attr *attr,
			     काष्ठा arch_hw_अवरोधpoपूर्णांक *hw)
अणु
	अचिन्हित पूर्णांक align;
	पूर्णांक ret;

	ret = arch_build_bp_info(bp, attr, hw);
	अगर (ret)
		वापस ret;

	ret = -EINVAL;

	चयन (hw->len) अणु
	हाल SH_BREAKPOINT_LEN_1:
		align = 0;
		अवरोध;
	हाल SH_BREAKPOINT_LEN_2:
		align = 1;
		अवरोध;
	हाल SH_BREAKPOINT_LEN_4:
		align = 3;
		अवरोध;
	हाल SH_BREAKPOINT_LEN_8:
		align = 7;
		अवरोध;
	शेष:
		वापस ret;
	पूर्ण

	/*
	 * Check that the low-order bits of the address are appropriate
	 * क्रम the alignment implied by len.
	 */
	अगर (hw->address & align)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/*
 * Release the user अवरोधpoपूर्णांकs used by ptrace
 */
व्योम flush_ptrace_hw_अवरोधpoपूर्णांक(काष्ठा task_काष्ठा *tsk)
अणु
	पूर्णांक i;
	काष्ठा thपढ़ो_काष्ठा *t = &tsk->thपढ़ो;

	क्रम (i = 0; i < sh_ubc->num_events; i++) अणु
		unरेजिस्टर_hw_अवरोधpoपूर्णांक(t->ptrace_bps[i]);
		t->ptrace_bps[i] = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक __kprobes hw_अवरोधpoपूर्णांक_handler(काष्ठा die_args *args)
अणु
	पूर्णांक cpu, i, rc = NOTIFY_STOP;
	काष्ठा perf_event *bp;
	अचिन्हित पूर्णांक cmf, resume_mask;

	/*
	 * Do an early वापस अगर none of the channels triggered.
	 */
	cmf = sh_ubc->triggered_mask();
	अगर (unlikely(!cmf))
		वापस NOTIFY_DONE;

	/*
	 * By शेष, resume all of the active channels.
	 */
	resume_mask = sh_ubc->active_mask();

	/*
	 * Disable अवरोधpoपूर्णांकs during exception handling.
	 */
	sh_ubc->disable_all();

	cpu = get_cpu();
	क्रम (i = 0; i < sh_ubc->num_events; i++) अणु
		अचिन्हित दीर्घ event_mask = (1 << i);

		अगर (likely(!(cmf & event_mask)))
			जारी;

		/*
		 * The counter may be concurrently released but that can only
		 * occur from a call_rcu() path. We can then safely fetch
		 * the अवरोधpoपूर्णांक, use its callback, touch its counter
		 * जबतक we are in an rcu_पढ़ो_lock() path.
		 */
		rcu_पढ़ो_lock();

		bp = per_cpu(bp_per_reg[i], cpu);
		अगर (bp)
			rc = NOTIFY_DONE;

		/*
		 * Reset the condition match flag to denote completion of
		 * exception handling.
		 */
		sh_ubc->clear_triggered_mask(event_mask);

		/*
		 * bp can be शून्य due to concurrent perf counter
		 * removing.
		 */
		अगर (!bp) अणु
			rcu_पढ़ो_unlock();
			अवरोध;
		पूर्ण

		/*
		 * Don't restore the channel अगर the अवरोधpoपूर्णांक is from
		 * ptrace, as it always operates in one-shot mode.
		 */
		अगर (bp->overflow_handler == ptrace_triggered)
			resume_mask &= ~(1 << i);

		perf_bp_event(bp, args->regs);

		/* Deliver the संकेत to userspace */
		अगर (!arch_check_bp_in_kernelspace(&bp->hw.info)) अणु
			क्रमce_sig_fault(SIGTRAP, TRAP_HWBKPT,
					(व्योम __user *)शून्य);
		पूर्ण

		rcu_पढ़ो_unlock();
	पूर्ण

	अगर (cmf == 0)
		rc = NOTIFY_DONE;

	sh_ubc->enable_all(resume_mask);

	put_cpu();

	वापस rc;
पूर्ण

BUILD_TRAP_HANDLER(अवरोधpoपूर्णांक)
अणु
	अचिन्हित दीर्घ ex = lookup_exception_vector();
	TRAP_HANDLER_DECL;

	notअगरy_die(DIE_BREAKPOINT, "breakpoint", regs, 0, ex, SIGTRAP);
पूर्ण

/*
 * Handle debug exception notअगरications.
 */
पूर्णांक __kprobes hw_अवरोधpoपूर्णांक_exceptions_notअगरy(काष्ठा notअगरier_block *unused,
				    अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा die_args *args = data;

	अगर (val != DIE_BREAKPOINT)
		वापस NOTIFY_DONE;

	/*
	 * If the अवरोधpoपूर्णांक hasn't been triggered by the UBC, it's
	 * probably from a debugger, so करोn't करो anything more here.
	 *
	 * This also permits the UBC पूर्णांकerface घड़ी to reमुख्य off क्रम
	 * non-UBC अवरोधpoपूर्णांकs, as we करोn't need to check the triggered
	 * or active channel masks.
	 */
	अगर (args->trapnr != sh_ubc->trap_nr)
		वापस NOTIFY_DONE;

	वापस hw_अवरोधpoपूर्णांक_handler(data);
पूर्ण

व्योम hw_अवरोधpoपूर्णांक_pmu_पढ़ो(काष्ठा perf_event *bp)
अणु
	/* TODO */
पूर्ण

पूर्णांक रेजिस्टर_sh_ubc(काष्ठा sh_ubc *ubc)
अणु
	/* Bail अगर it's alपढ़ोy asचिन्हित */
	अगर (sh_ubc != &ubc_dummy)
		वापस -EBUSY;
	sh_ubc = ubc;

	pr_info("HW Breakpoints: %s UBC support registered\n", ubc->name);

	WARN_ON(ubc->num_events > HBP_NUM);

	वापस 0;
पूर्ण
