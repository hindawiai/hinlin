<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * HW_अवरोधpoपूर्णांक: a unअगरied kernel/user-space hardware अवरोधpoपूर्णांक facility,
 * using the CPU's debug रेजिस्टरs. Derived from
 * "arch/x86/kernel/hw_breakpoint.c"
 *
 * Copyright 2010 IBM Corporation
 * Author: K.Prasad <prasad@linux.vnet.ibm.com>
 */

#समावेश <linux/hw_अवरोधpoपूर्णांक.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/percpu.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/smp.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/hw_अवरोधpoपूर्णांक.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/sstep.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/debugfs.h>
#समावेश <यंत्र/hvcall.h>
#समावेश <यंत्र/inst.h>
#समावेश <linux/uaccess.h>

/*
 * Stores the अवरोधpoपूर्णांकs currently in use on each अवरोधpoपूर्णांक address
 * रेजिस्टर क्रम every cpu
 */
अटल DEFINE_PER_CPU(काष्ठा perf_event *, bp_per_reg[HBP_NUM_MAX]);

/*
 * Returns total number of data or inकाष्ठाion अवरोधpoपूर्णांकs available.
 */
पूर्णांक hw_अवरोधpoपूर्णांक_slots(पूर्णांक type)
अणु
	अगर (type == TYPE_DATA)
		वापस nr_wp_slots();
	वापस 0;		/* no inकाष्ठाion अवरोधpoपूर्णांकs available */
पूर्ण

अटल bool single_step_pending(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_wp_slots(); i++) अणु
		अगर (current->thपढ़ो.last_hit_ubp[i])
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * Install a perf counter अवरोधpoपूर्णांक.
 *
 * We seek a मुक्त debug address रेजिस्टर and use it क्रम this
 * अवरोधpoपूर्णांक.
 *
 * Atomic: we hold the counter->ctx->lock and we only handle variables
 * and रेजिस्टरs local to this cpu.
 */
पूर्णांक arch_install_hw_अवरोधpoपूर्णांक(काष्ठा perf_event *bp)
अणु
	काष्ठा arch_hw_अवरोधpoपूर्णांक *info = counter_arch_bp(bp);
	काष्ठा perf_event **slot;
	पूर्णांक i;

	क्रम (i = 0; i < nr_wp_slots(); i++) अणु
		slot = this_cpu_ptr(&bp_per_reg[i]);
		अगर (!*slot) अणु
			*slot = bp;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (WARN_ONCE(i == nr_wp_slots(), "Can't find any breakpoint slot"))
		वापस -EBUSY;

	/*
	 * Do not install DABR values अगर the inकाष्ठाion must be single-stepped.
	 * If so, DABR will be populated in single_step_dabr_inकाष्ठाion().
	 */
	अगर (!single_step_pending())
		__set_अवरोधpoपूर्णांक(i, info);

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
	काष्ठा arch_hw_अवरोधpoपूर्णांक null_brk = अणु0पूर्ण;
	काष्ठा perf_event **slot;
	पूर्णांक i;

	क्रम (i = 0; i < nr_wp_slots(); i++) अणु
		slot = this_cpu_ptr(&bp_per_reg[i]);
		अगर (*slot == bp) अणु
			*slot = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (WARN_ONCE(i == nr_wp_slots(), "Can't find any breakpoint slot"))
		वापस;

	__set_अवरोधpoपूर्णांक(i, &null_brk);
पूर्ण

अटल bool is_ptrace_bp(काष्ठा perf_event *bp)
अणु
	वापस bp->overflow_handler == ptrace_triggered;
पूर्ण

काष्ठा अवरोधpoपूर्णांक अणु
	काष्ठा list_head list;
	काष्ठा perf_event *bp;
	bool ptrace_bp;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा अवरोधpoपूर्णांक *, cpu_bps[HBP_NUM_MAX]);
अटल LIST_HEAD(task_bps);

अटल काष्ठा अवरोधpoपूर्णांक *alloc_अवरोधpoपूर्णांक(काष्ठा perf_event *bp)
अणु
	काष्ठा अवरोधpoपूर्णांक *पंचांगp;

	पंचांगp = kzalloc(माप(*पंचांगp), GFP_KERNEL);
	अगर (!पंचांगp)
		वापस ERR_PTR(-ENOMEM);
	पंचांगp->bp = bp;
	पंचांगp->ptrace_bp = is_ptrace_bp(bp);
	वापस पंचांगp;
पूर्ण

अटल bool bp_addr_range_overlap(काष्ठा perf_event *bp1, काष्ठा perf_event *bp2)
अणु
	__u64 bp1_saddr, bp1_eaddr, bp2_saddr, bp2_eaddr;

	bp1_saddr = ALIGN_DOWN(bp1->attr.bp_addr, HW_BREAKPOINT_SIZE);
	bp1_eaddr = ALIGN(bp1->attr.bp_addr + bp1->attr.bp_len, HW_BREAKPOINT_SIZE);
	bp2_saddr = ALIGN_DOWN(bp2->attr.bp_addr, HW_BREAKPOINT_SIZE);
	bp2_eaddr = ALIGN(bp2->attr.bp_addr + bp2->attr.bp_len, HW_BREAKPOINT_SIZE);

	वापस (bp1_saddr < bp2_eaddr && bp1_eaddr > bp2_saddr);
पूर्ण

अटल bool alternate_infra_bp(काष्ठा अवरोधpoपूर्णांक *b, काष्ठा perf_event *bp)
अणु
	वापस is_ptrace_bp(bp) ? !b->ptrace_bp : b->ptrace_bp;
पूर्ण

अटल bool can_co_exist(काष्ठा अवरोधpoपूर्णांक *b, काष्ठा perf_event *bp)
अणु
	वापस !(alternate_infra_bp(b, bp) && bp_addr_range_overlap(b->bp, bp));
पूर्ण

अटल पूर्णांक task_bps_add(काष्ठा perf_event *bp)
अणु
	काष्ठा अवरोधpoपूर्णांक *पंचांगp;

	पंचांगp = alloc_अवरोधpoपूर्णांक(bp);
	अगर (IS_ERR(पंचांगp))
		वापस PTR_ERR(पंचांगp);

	list_add(&पंचांगp->list, &task_bps);
	वापस 0;
पूर्ण

अटल व्योम task_bps_हटाओ(काष्ठा perf_event *bp)
अणु
	काष्ठा list_head *pos, *q;

	list_क्रम_each_safe(pos, q, &task_bps) अणु
		काष्ठा अवरोधpoपूर्णांक *पंचांगp = list_entry(pos, काष्ठा अवरोधpoपूर्णांक, list);

		अगर (पंचांगp->bp == bp) अणु
			list_del(&पंचांगp->list);
			kमुक्त(पंचांगp);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * If any task has अवरोधpoपूर्णांक from alternate infraकाष्ठाure,
 * वापस true. Otherwise वापस false.
 */
अटल bool all_task_bps_check(काष्ठा perf_event *bp)
अणु
	काष्ठा अवरोधpoपूर्णांक *पंचांगp;

	list_क्रम_each_entry(पंचांगp, &task_bps, list) अणु
		अगर (!can_co_exist(पंचांगp, bp))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * If same task has अवरोधpoपूर्णांक from alternate infraकाष्ठाure,
 * वापस true. Otherwise वापस false.
 */
अटल bool same_task_bps_check(काष्ठा perf_event *bp)
अणु
	काष्ठा अवरोधpoपूर्णांक *पंचांगp;

	list_क्रम_each_entry(पंचांगp, &task_bps, list) अणु
		अगर (पंचांगp->bp->hw.target == bp->hw.target &&
		    !can_co_exist(पंचांगp, bp))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक cpu_bps_add(काष्ठा perf_event *bp)
अणु
	काष्ठा अवरोधpoपूर्णांक **cpu_bp;
	काष्ठा अवरोधpoपूर्णांक *पंचांगp;
	पूर्णांक i = 0;

	पंचांगp = alloc_अवरोधpoपूर्णांक(bp);
	अगर (IS_ERR(पंचांगp))
		वापस PTR_ERR(पंचांगp);

	cpu_bp = per_cpu_ptr(cpu_bps, bp->cpu);
	क्रम (i = 0; i < nr_wp_slots(); i++) अणु
		अगर (!cpu_bp[i]) अणु
			cpu_bp[i] = पंचांगp;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम cpu_bps_हटाओ(काष्ठा perf_event *bp)
अणु
	काष्ठा अवरोधpoपूर्णांक **cpu_bp;
	पूर्णांक i = 0;

	cpu_bp = per_cpu_ptr(cpu_bps, bp->cpu);
	क्रम (i = 0; i < nr_wp_slots(); i++) अणु
		अगर (!cpu_bp[i])
			जारी;

		अगर (cpu_bp[i]->bp == bp) अणु
			kमुक्त(cpu_bp[i]);
			cpu_bp[i] = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल bool cpu_bps_check(पूर्णांक cpu, काष्ठा perf_event *bp)
अणु
	काष्ठा अवरोधpoपूर्णांक **cpu_bp;
	पूर्णांक i;

	cpu_bp = per_cpu_ptr(cpu_bps, cpu);
	क्रम (i = 0; i < nr_wp_slots(); i++) अणु
		अगर (cpu_bp[i] && !can_co_exist(cpu_bp[i], bp))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool all_cpu_bps_check(काष्ठा perf_event *bp)
अणु
	पूर्णांक cpu;

	क्रम_each_online_cpu(cpu) अणु
		अगर (cpu_bps_check(cpu, bp))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * We करोn't use any locks to serialize accesses to cpu_bps or task_bps
 * because are alपढ़ोy inside nr_bp_mutex.
 */
पूर्णांक arch_reserve_bp_slot(काष्ठा perf_event *bp)
अणु
	पूर्णांक ret;

	/* ptrace अवरोधpoपूर्णांक */
	अगर (is_ptrace_bp(bp)) अणु
		अगर (all_cpu_bps_check(bp))
			वापस -ENOSPC;

		अगर (same_task_bps_check(bp))
			वापस -ENOSPC;

		वापस task_bps_add(bp);
	पूर्ण

	/* perf अवरोधpoपूर्णांक */
	अगर (is_kernel_addr(bp->attr.bp_addr))
		वापस 0;

	अगर (bp->hw.target && bp->cpu == -1) अणु
		अगर (same_task_bps_check(bp))
			वापस -ENOSPC;

		वापस task_bps_add(bp);
	पूर्ण अन्यथा अगर (!bp->hw.target && bp->cpu != -1) अणु
		अगर (all_task_bps_check(bp))
			वापस -ENOSPC;

		वापस cpu_bps_add(bp);
	पूर्ण

	अगर (same_task_bps_check(bp))
		वापस -ENOSPC;

	ret = cpu_bps_add(bp);
	अगर (ret)
		वापस ret;
	ret = task_bps_add(bp);
	अगर (ret)
		cpu_bps_हटाओ(bp);

	वापस ret;
पूर्ण

व्योम arch_release_bp_slot(काष्ठा perf_event *bp)
अणु
	अगर (!is_kernel_addr(bp->attr.bp_addr)) अणु
		अगर (bp->hw.target)
			task_bps_हटाओ(bp);
		अगर (bp->cpu != -1)
			cpu_bps_हटाओ(bp);
	पूर्ण
पूर्ण

/*
 * Perक्रमm cleanup of arch-specअगरic counters during unregistration
 * of the perf-event
 */
व्योम arch_unरेजिस्टर_hw_अवरोधpoपूर्णांक(काष्ठा perf_event *bp)
अणु
	/*
	 * If the अवरोधpoपूर्णांक is unरेजिस्टरed between a hw_अवरोधpoपूर्णांक_handler()
	 * and the single_step_dabr_inकाष्ठाion(), then cleanup the अवरोधpoपूर्णांक
	 * restoration variables to prevent dangling poपूर्णांकers.
	 * FIXME, this should not be using bp->ctx at all! Sayeth peterz.
	 */
	अगर (bp->ctx && bp->ctx->task && bp->ctx->task != ((व्योम *)-1L)) अणु
		पूर्णांक i;

		क्रम (i = 0; i < nr_wp_slots(); i++) अणु
			अगर (bp->ctx->task->thपढ़ो.last_hit_ubp[i] == bp)
				bp->ctx->task->thपढ़ो.last_hit_ubp[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Check क्रम भव address in kernel space.
 */
पूर्णांक arch_check_bp_in_kernelspace(काष्ठा arch_hw_अवरोधpoपूर्णांक *hw)
अणु
	वापस is_kernel_addr(hw->address);
पूर्ण

पूर्णांक arch_bp_generic_fields(पूर्णांक type, पूर्णांक *gen_bp_type)
अणु
	*gen_bp_type = 0;
	अगर (type & HW_BRK_TYPE_READ)
		*gen_bp_type |= HW_BREAKPOINT_R;
	अगर (type & HW_BRK_TYPE_WRITE)
		*gen_bp_type |= HW_BREAKPOINT_W;
	अगर (*gen_bp_type == 0)
		वापस -EINVAL;
	वापस 0;
पूर्ण

/*
 * Watchpoपूर्णांक match range is always द्विगुनword(8 bytes) aligned on
 * घातerpc. If the given range is crossing द्विगुनword boundary, we
 * need to increase the length such that next द्विगुनword also get
 * covered. Ex,
 *
 *          address   len = 6 bytes
 *                |=========.
 *   |------------v--|------v--------|
 *   | | | | | | | | | | | | | | | | |
 *   |---------------|---------------|
 *    <---8 bytes--->
 *
 * In this हाल, we should configure hw as:
 *   start_addr = address & ~(HW_BREAKPOINT_SIZE - 1)
 *   len = 16 bytes
 *
 * @start_addr is inclusive but @end_addr is exclusive.
 */
अटल पूर्णांक hw_अवरोधpoपूर्णांक_validate_len(काष्ठा arch_hw_अवरोधpoपूर्णांक *hw)
अणु
	u16 max_len = DABR_MAX_LEN;
	u16 hw_len;
	अचिन्हित दीर्घ start_addr, end_addr;

	start_addr = ALIGN_DOWN(hw->address, HW_BREAKPOINT_SIZE);
	end_addr = ALIGN(hw->address + hw->len, HW_BREAKPOINT_SIZE);
	hw_len = end_addr - start_addr;

	अगर (dawr_enabled()) अणु
		max_len = DAWR_MAX_LEN;
		/* DAWR region can't cross 512 bytes boundary on p10 predecessors */
		अगर (!cpu_has_feature(CPU_FTR_ARCH_31) &&
		    (ALIGN_DOWN(start_addr, SZ_512) != ALIGN_DOWN(end_addr - 1, SZ_512)))
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_PPC_8xx)) अणु
		/* 8xx can setup a range without limitation */
		max_len = U16_MAX;
	पूर्ण

	अगर (hw_len > max_len)
		वापस -EINVAL;

	hw->hw_len = hw_len;
	वापस 0;
पूर्ण

/*
 * Validate the arch-specअगरic HW Breakpoपूर्णांक रेजिस्टर settings
 */
पूर्णांक hw_अवरोधpoपूर्णांक_arch_parse(काष्ठा perf_event *bp,
			     स्थिर काष्ठा perf_event_attr *attr,
			     काष्ठा arch_hw_अवरोधpoपूर्णांक *hw)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (!bp || !attr->bp_len)
		वापस ret;

	hw->type = HW_BRK_TYPE_TRANSLATE;
	अगर (attr->bp_type & HW_BREAKPOINT_R)
		hw->type |= HW_BRK_TYPE_READ;
	अगर (attr->bp_type & HW_BREAKPOINT_W)
		hw->type |= HW_BRK_TYPE_WRITE;
	अगर (hw->type == HW_BRK_TYPE_TRANSLATE)
		/* must set alteast पढ़ो or ग_लिखो */
		वापस ret;
	अगर (!attr->exclude_user)
		hw->type |= HW_BRK_TYPE_USER;
	अगर (!attr->exclude_kernel)
		hw->type |= HW_BRK_TYPE_KERNEL;
	अगर (!attr->exclude_hv)
		hw->type |= HW_BRK_TYPE_HYP;
	hw->address = attr->bp_addr;
	hw->len = attr->bp_len;

	अगर (!ppc_अवरोधpoपूर्णांक_available())
		वापस -ENODEV;

	वापस hw_अवरोधpoपूर्णांक_validate_len(hw);
पूर्ण

/*
 * Restores the अवरोधpoपूर्णांक on the debug रेजिस्टरs.
 * Invoke this function अगर it is known that the execution context is
 * about to change to cause loss of MSR_SE settings.
 */
व्योम thपढ़ो_change_pc(काष्ठा task_काष्ठा *tsk, काष्ठा pt_regs *regs)
अणु
	काष्ठा arch_hw_अवरोधpoपूर्णांक *info;
	पूर्णांक i;

	क्रम (i = 0; i < nr_wp_slots(); i++) अणु
		अगर (unlikely(tsk->thपढ़ो.last_hit_ubp[i]))
			जाओ reset;
	पूर्ण
	वापस;

reset:
	regs->msr &= ~MSR_SE;
	क्रम (i = 0; i < nr_wp_slots(); i++) अणु
		info = counter_arch_bp(__this_cpu_पढ़ो(bp_per_reg[i]));
		__set_अवरोधpoपूर्णांक(i, info);
		tsk->thपढ़ो.last_hit_ubp[i] = शून्य;
	पूर्ण
पूर्ण

अटल bool is_larx_stcx_instr(पूर्णांक type)
अणु
	वापस type == LARX || type == STCX;
पूर्ण

अटल bool is_octword_vsx_instr(पूर्णांक type, पूर्णांक size)
अणु
	वापस ((type == LOAD_VSX || type == STORE_VSX) && size == 32);
पूर्ण

/*
 * We've failed in reliably handling the hw-अवरोधpoपूर्णांक. Unरेजिस्टर
 * it and throw a warning message to let the user know about it.
 */
अटल व्योम handler_error(काष्ठा perf_event *bp, काष्ठा arch_hw_अवरोधpoपूर्णांक *info)
अणु
	WARN(1, "Unable to handle hardware breakpoint. Breakpoint at 0x%lx will be disabled.",
	     info->address);
	perf_event_disable_inatomic(bp);
पूर्ण

अटल व्योम larx_stcx_err(काष्ठा perf_event *bp, काष्ठा arch_hw_अवरोधpoपूर्णांक *info)
अणु
	prपूर्णांकk_ratelimited("Breakpoint hit on instruction that can't be emulated. Breakpoint at 0x%lx will be disabled.\n",
			   info->address);
	perf_event_disable_inatomic(bp);
पूर्ण

अटल bool stepping_handler(काष्ठा pt_regs *regs, काष्ठा perf_event **bp,
			     काष्ठा arch_hw_अवरोधpoपूर्णांक **info, पूर्णांक *hit,
			     काष्ठा ppc_inst instr)
अणु
	पूर्णांक i;
	पूर्णांक stepped;

	/* Do not emulate user-space inकाष्ठाions, instead single-step them */
	अगर (user_mode(regs)) अणु
		क्रम (i = 0; i < nr_wp_slots(); i++) अणु
			अगर (!hit[i])
				जारी;
			current->thपढ़ो.last_hit_ubp[i] = bp[i];
			info[i] = शून्य;
		पूर्ण
		regs->msr |= MSR_SE;
		वापस false;
	पूर्ण

	stepped = emulate_step(regs, instr);
	अगर (!stepped) अणु
		क्रम (i = 0; i < nr_wp_slots(); i++) अणु
			अगर (!hit[i])
				जारी;
			handler_error(bp[i], info[i]);
			info[i] = शून्य;
		पूर्ण
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम handle_p10dd1_spurious_exception(काष्ठा arch_hw_अवरोधpoपूर्णांक **info,
					     पूर्णांक *hit, अचिन्हित दीर्घ ea)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ hw_end_addr;

	/*
	 * Handle spurious exception only when any bp_per_reg is set.
	 * Otherwise this might be created by xmon and not actually a
	 * spurious exception.
	 */
	क्रम (i = 0; i < nr_wp_slots(); i++) अणु
		अगर (!info[i])
			जारी;

		hw_end_addr = ALIGN(info[i]->address + info[i]->len, HW_BREAKPOINT_SIZE);

		/*
		 * Ending address of DAWR range is less than starting
		 * address of op.
		 */
		अगर ((hw_end_addr - 1) >= ea)
			जारी;

		/*
		 * Those addresses need to be in the same or in two
		 * consecutive 512B blocks;
		 */
		अगर (((hw_end_addr - 1) >> 10) != (ea >> 10))
			जारी;

		/*
		 * 'op address + 64B' generates an address that has a
		 * carry पूर्णांकo bit 52 (crosses 2K boundary).
		 */
		अगर ((ea & 0x800) == ((ea + 64) & 0x800))
			जारी;

		अवरोध;
	पूर्ण

	अगर (i == nr_wp_slots())
		वापस;

	क्रम (i = 0; i < nr_wp_slots(); i++) अणु
		अगर (info[i]) अणु
			hit[i] = 1;
			info[i]->type |= HW_BRK_TYPE_EXTRANEOUS_IRQ;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक hw_अवरोधpoपूर्णांक_handler(काष्ठा die_args *args)
अणु
	bool err = false;
	पूर्णांक rc = NOTIFY_STOP;
	काष्ठा perf_event *bp[HBP_NUM_MAX] = अणु शून्य पूर्ण;
	काष्ठा pt_regs *regs = args->regs;
	काष्ठा arch_hw_अवरोधpoपूर्णांक *info[HBP_NUM_MAX] = अणु शून्य पूर्ण;
	पूर्णांक i;
	पूर्णांक hit[HBP_NUM_MAX] = अणु0पूर्ण;
	पूर्णांक nr_hit = 0;
	bool ptrace_bp = false;
	काष्ठा ppc_inst instr = ppc_inst(0);
	पूर्णांक type = 0;
	पूर्णांक size = 0;
	अचिन्हित दीर्घ ea;

	/* Disable अवरोधpoपूर्णांकs during exception handling */
	hw_अवरोधpoपूर्णांक_disable();

	/*
	 * The counter may be concurrently released but that can only
	 * occur from a call_rcu() path. We can then safely fetch
	 * the अवरोधpoपूर्णांक, use its callback, touch its counter
	 * जबतक we are in an rcu_पढ़ो_lock() path.
	 */
	rcu_पढ़ो_lock();

	अगर (!IS_ENABLED(CONFIG_PPC_8xx))
		wp_get_instr_detail(regs, &instr, &type, &size, &ea);

	क्रम (i = 0; i < nr_wp_slots(); i++) अणु
		bp[i] = __this_cpu_पढ़ो(bp_per_reg[i]);
		अगर (!bp[i])
			जारी;

		info[i] = counter_arch_bp(bp[i]);
		info[i]->type &= ~HW_BRK_TYPE_EXTRANEOUS_IRQ;

		अगर (wp_check_स्थिरraपूर्णांकs(regs, instr, ea, type, size, info[i])) अणु
			अगर (!IS_ENABLED(CONFIG_PPC_8xx) &&
			    ppc_inst_equal(instr, ppc_inst(0))) अणु
				handler_error(bp[i], info[i]);
				info[i] = शून्य;
				err = 1;
				जारी;
			पूर्ण

			अगर (is_ptrace_bp(bp[i]))
				ptrace_bp = true;
			hit[i] = 1;
			nr_hit++;
		पूर्ण
	पूर्ण

	अगर (err)
		जाओ reset;

	अगर (!nr_hit) अणु
		/* Workaround क्रम Power10 DD1 */
		अगर (!IS_ENABLED(CONFIG_PPC_8xx) && mfspr(SPRN_PVR) == 0x800100 &&
		    is_octword_vsx_instr(type, size)) अणु
			handle_p10dd1_spurious_exception(info, hit, ea);
		पूर्ण अन्यथा अणु
			rc = NOTIFY_DONE;
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * Return early after invoking user-callback function without restoring
	 * DABR अगर the अवरोधpoपूर्णांक is from ptrace which always operates in
	 * one-shot mode. The ptrace-ed process will receive the SIGTRAP संकेत
	 * generated in करो_dabr().
	 */
	अगर (ptrace_bp) अणु
		क्रम (i = 0; i < nr_wp_slots(); i++) अणु
			अगर (!hit[i])
				जारी;
			perf_bp_event(bp[i], regs);
			info[i] = शून्य;
		पूर्ण
		rc = NOTIFY_DONE;
		जाओ reset;
	पूर्ण

	अगर (!IS_ENABLED(CONFIG_PPC_8xx)) अणु
		अगर (is_larx_stcx_instr(type)) अणु
			क्रम (i = 0; i < nr_wp_slots(); i++) अणु
				अगर (!hit[i])
					जारी;
				larx_stcx_err(bp[i], info[i]);
				info[i] = शून्य;
			पूर्ण
			जाओ reset;
		पूर्ण

		अगर (!stepping_handler(regs, bp, info, hit, instr))
			जाओ reset;
	पूर्ण

	/*
	 * As a policy, the callback is invoked in a 'trigger-after-execute'
	 * fashion
	 */
	क्रम (i = 0; i < nr_wp_slots(); i++) अणु
		अगर (!hit[i])
			जारी;
		अगर (!(info[i]->type & HW_BRK_TYPE_EXTRANEOUS_IRQ))
			perf_bp_event(bp[i], regs);
	पूर्ण

reset:
	क्रम (i = 0; i < nr_wp_slots(); i++) अणु
		अगर (!info[i])
			जारी;
		__set_अवरोधpoपूर्णांक(i, info[i]);
	पूर्ण

out:
	rcu_पढ़ो_unlock();
	वापस rc;
पूर्ण
NOKPROBE_SYMBOL(hw_अवरोधpoपूर्णांक_handler);

/*
 * Handle single-step exceptions following a DABR hit.
 */
अटल पूर्णांक single_step_dabr_inकाष्ठाion(काष्ठा die_args *args)
अणु
	काष्ठा pt_regs *regs = args->regs;
	काष्ठा perf_event *bp = शून्य;
	काष्ठा arch_hw_अवरोधpoपूर्णांक *info;
	पूर्णांक i;
	bool found = false;

	/*
	 * Check अगर we are single-stepping as a result of a
	 * previous HW Breakpoपूर्णांक exception
	 */
	क्रम (i = 0; i < nr_wp_slots(); i++) अणु
		bp = current->thपढ़ो.last_hit_ubp[i];

		अगर (!bp)
			जारी;

		found = true;
		info = counter_arch_bp(bp);

		/*
		 * We shall invoke the user-defined callback function in the
		 * single stepping handler to confirm to 'trigger-after-execute'
		 * semantics
		 */
		अगर (!(info->type & HW_BRK_TYPE_EXTRANEOUS_IRQ))
			perf_bp_event(bp, regs);
		current->thपढ़ो.last_hit_ubp[i] = शून्य;
	पूर्ण

	अगर (!found)
		वापस NOTIFY_DONE;

	क्रम (i = 0; i < nr_wp_slots(); i++) अणु
		bp = __this_cpu_पढ़ो(bp_per_reg[i]);
		अगर (!bp)
			जारी;

		info = counter_arch_bp(bp);
		__set_अवरोधpoपूर्णांक(i, info);
	पूर्ण

	/*
	 * If the process was being single-stepped by ptrace, let the
	 * other single-step actions occur (e.g. generate SIGTRAP).
	 */
	अगर (test_thपढ़ो_flag(TIF_SINGLESTEP))
		वापस NOTIFY_DONE;

	वापस NOTIFY_STOP;
पूर्ण
NOKPROBE_SYMBOL(single_step_dabr_inकाष्ठाion);

/*
 * Handle debug exception notअगरications.
 */
पूर्णांक hw_अवरोधpoपूर्णांक_exceptions_notअगरy(
		काष्ठा notअगरier_block *unused, अचिन्हित दीर्घ val, व्योम *data)
अणु
	पूर्णांक ret = NOTIFY_DONE;

	चयन (val) अणु
	हाल DIE_DABR_MATCH:
		ret = hw_अवरोधpoपूर्णांक_handler(data);
		अवरोध;
	हाल DIE_SSTEP:
		ret = single_step_dabr_inकाष्ठाion(data);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
NOKPROBE_SYMBOL(hw_अवरोधpoपूर्णांक_exceptions_notअगरy);

/*
 * Release the user अवरोधpoपूर्णांकs used by ptrace
 */
व्योम flush_ptrace_hw_अवरोधpoपूर्णांक(काष्ठा task_काष्ठा *tsk)
अणु
	पूर्णांक i;
	काष्ठा thपढ़ो_काष्ठा *t = &tsk->thपढ़ो;

	क्रम (i = 0; i < nr_wp_slots(); i++) अणु
		unरेजिस्टर_hw_अवरोधpoपूर्णांक(t->ptrace_bps[i]);
		t->ptrace_bps[i] = शून्य;
	पूर्ण
पूर्ण

व्योम hw_अवरोधpoपूर्णांक_pmu_पढ़ो(काष्ठा perf_event *bp)
अणु
	/* TODO */
पूर्ण

व्योम ptrace_triggered(काष्ठा perf_event *bp,
		      काष्ठा perf_sample_data *data, काष्ठा pt_regs *regs)
अणु
	काष्ठा perf_event_attr attr;

	/*
	 * Disable the अवरोधpoपूर्णांक request here since ptrace has defined a
	 * one-shot behaviour क्रम अवरोधpoपूर्णांक exceptions in PPC64.
	 * The SIGTRAP संकेत is generated स्वतःmatically क्रम us in करो_dabr().
	 * We करोn't have to करो anything about that here
	 */
	attr = bp->attr;
	attr.disabled = true;
	modअगरy_user_hw_अवरोधpoपूर्णांक(bp, &attr);
पूर्ण
