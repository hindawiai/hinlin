<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) 2007 Alan Stern
 * Copyright (C) 2009 IBM Corporation
 * Copyright (C) 2009 Frederic Weisbecker <fweisbec@gmail.com>
 *
 * Authors: Alan Stern <stern@rowland.harvard.edu>
 *          K.Prasad <prasad@linux.vnet.ibm.com>
 *          Frederic Weisbecker <fweisbec@gmail.com>
 */

/*
 * HW_अवरोधpoपूर्णांक: a unअगरied kernel/user-space hardware अवरोधpoपूर्णांक facility,
 * using the CPU's debug रेजिस्टरs.
 */

#समावेश <linux/perf_event.h>
#समावेश <linux/hw_अवरोधpoपूर्णांक.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/percpu.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/smp.h>

#समावेश <यंत्र/hw_अवरोधpoपूर्णांक.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/debugreg.h>
#समावेश <यंत्र/user.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/tlbflush.h>

/* Per cpu debug control रेजिस्टर value */
DEFINE_PER_CPU(अचिन्हित दीर्घ, cpu_dr7);
EXPORT_PER_CPU_SYMBOL(cpu_dr7);

/* Per cpu debug address रेजिस्टरs values */
अटल DEFINE_PER_CPU(अचिन्हित दीर्घ, cpu_debugreg[HBP_NUM]);

/*
 * Stores the अवरोधpoपूर्णांकs currently in use on each अवरोधpoपूर्णांक address
 * रेजिस्टर क्रम each cpus
 */
अटल DEFINE_PER_CPU(काष्ठा perf_event *, bp_per_reg[HBP_NUM]);


अटल अंतरभूत अचिन्हित दीर्घ
__encode_dr7(पूर्णांक drnum, अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक type)
अणु
	अचिन्हित दीर्घ bp_info;

	bp_info = (len | type) & 0xf;
	bp_info <<= (DR_CONTROL_SHIFT + drnum * DR_CONTROL_SIZE);
	bp_info |= (DR_GLOBAL_ENABLE << (drnum * DR_ENABLE_SIZE));

	वापस bp_info;
पूर्ण

/*
 * Encode the length, type, Exact, and Enable bits क्रम a particular अवरोधpoपूर्णांक
 * as stored in debug रेजिस्टर 7.
 */
अचिन्हित दीर्घ encode_dr7(पूर्णांक drnum, अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक type)
अणु
	वापस __encode_dr7(drnum, len, type) | DR_GLOBAL_SLOWDOWN;
पूर्ण

/*
 * Decode the length and type bits क्रम a particular अवरोधpoपूर्णांक as
 * stored in debug रेजिस्टर 7.  Return the "enabled" status.
 */
पूर्णांक decode_dr7(अचिन्हित दीर्घ dr7, पूर्णांक bpnum, अचिन्हित *len, अचिन्हित *type)
अणु
	पूर्णांक bp_info = dr7 >> (DR_CONTROL_SHIFT + bpnum * DR_CONTROL_SIZE);

	*len = (bp_info & 0xc) | 0x40;
	*type = (bp_info & 0x3) | 0x80;

	वापस (dr7 >> (bpnum * DR_ENABLE_SIZE)) & 0x3;
पूर्ण

/*
 * Install a perf counter अवरोधpoपूर्णांक.
 *
 * We seek a मुक्त debug address रेजिस्टर and use it क्रम this
 * अवरोधpoपूर्णांक. Eventually we enable it in the debug control रेजिस्टर.
 *
 * Atomic: we hold the counter->ctx->lock and we only handle variables
 * and रेजिस्टरs local to this cpu.
 */
पूर्णांक arch_install_hw_अवरोधpoपूर्णांक(काष्ठा perf_event *bp)
अणु
	काष्ठा arch_hw_अवरोधpoपूर्णांक *info = counter_arch_bp(bp);
	अचिन्हित दीर्घ *dr7;
	पूर्णांक i;

	lockdep_निश्चित_irqs_disabled();

	क्रम (i = 0; i < HBP_NUM; i++) अणु
		काष्ठा perf_event **slot = this_cpu_ptr(&bp_per_reg[i]);

		अगर (!*slot) अणु
			*slot = bp;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (WARN_ONCE(i == HBP_NUM, "Can't find any breakpoint slot"))
		वापस -EBUSY;

	set_debugreg(info->address, i);
	__this_cpu_ग_लिखो(cpu_debugreg[i], info->address);

	dr7 = this_cpu_ptr(&cpu_dr7);
	*dr7 |= encode_dr7(i, info->len, info->type);

	/*
	 * Ensure we first ग_लिखो cpu_dr7 beक्रमe we set the DR7 रेजिस्टर.
	 * This ensures an NMI never see cpu_dr7 0 when DR7 is not.
	 */
	barrier();

	set_debugreg(*dr7, 7);
	अगर (info->mask)
		set_dr_addr_mask(info->mask, i);

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
	अचिन्हित दीर्घ dr7;
	पूर्णांक i;

	lockdep_निश्चित_irqs_disabled();

	क्रम (i = 0; i < HBP_NUM; i++) अणु
		काष्ठा perf_event **slot = this_cpu_ptr(&bp_per_reg[i]);

		अगर (*slot == bp) अणु
			*slot = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (WARN_ONCE(i == HBP_NUM, "Can't find any breakpoint slot"))
		वापस;

	dr7 = this_cpu_पढ़ो(cpu_dr7);
	dr7 &= ~__encode_dr7(i, info->len, info->type);

	set_debugreg(dr7, 7);
	अगर (info->mask)
		set_dr_addr_mask(0, i);

	/*
	 * Ensure the ग_लिखो to cpu_dr7 is after we've set the DR7 रेजिस्टर.
	 * This ensures an NMI never see cpu_dr7 0 when DR7 is not.
	 */
	barrier();

	this_cpu_ग_लिखो(cpu_dr7, dr7);
पूर्ण

अटल पूर्णांक arch_bp_generic_len(पूर्णांक x86_len)
अणु
	चयन (x86_len) अणु
	हाल X86_BREAKPOINT_LEN_1:
		वापस HW_BREAKPOINT_LEN_1;
	हाल X86_BREAKPOINT_LEN_2:
		वापस HW_BREAKPOINT_LEN_2;
	हाल X86_BREAKPOINT_LEN_4:
		वापस HW_BREAKPOINT_LEN_4;
#अगर_घोषित CONFIG_X86_64
	हाल X86_BREAKPOINT_LEN_8:
		वापस HW_BREAKPOINT_LEN_8;
#पूर्ण_अगर
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक arch_bp_generic_fields(पूर्णांक x86_len, पूर्णांक x86_type,
			   पूर्णांक *gen_len, पूर्णांक *gen_type)
अणु
	पूर्णांक len;

	/* Type */
	चयन (x86_type) अणु
	हाल X86_BREAKPOINT_EXECUTE:
		अगर (x86_len != X86_BREAKPOINT_LEN_X)
			वापस -EINVAL;

		*gen_type = HW_BREAKPOINT_X;
		*gen_len = माप(दीर्घ);
		वापस 0;
	हाल X86_BREAKPOINT_WRITE:
		*gen_type = HW_BREAKPOINT_W;
		अवरोध;
	हाल X86_BREAKPOINT_RW:
		*gen_type = HW_BREAKPOINT_W | HW_BREAKPOINT_R;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Len */
	len = arch_bp_generic_len(x86_len);
	अगर (len < 0)
		वापस -EINVAL;
	*gen_len = len;

	वापस 0;
पूर्ण

/*
 * Check क्रम भव address in kernel space.
 */
पूर्णांक arch_check_bp_in_kernelspace(काष्ठा arch_hw_अवरोधpoपूर्णांक *hw)
अणु
	अचिन्हित दीर्घ va;
	पूर्णांक len;

	va = hw->address;
	len = arch_bp_generic_len(hw->len);
	WARN_ON_ONCE(len < 0);

	/*
	 * We करोn't need to worry about va + len - 1 overflowing:
	 * we alपढ़ोy require that va is aligned to a multiple of len.
	 */
	वापस (va >= TASK_SIZE_MAX) || ((va + len - 1) >= TASK_SIZE_MAX);
पूर्ण

/*
 * Checks whether the range [addr, end], overlaps the area [base, base + size).
 */
अटल अंतरभूत bool within_area(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			       अचिन्हित दीर्घ base, अचिन्हित दीर्घ size)
अणु
	वापस end >= base && addr < (base + size);
पूर्ण

/*
 * Checks whether the range from addr to end, inclusive, overlaps the fixed
 * mapped CPU entry area range or other ranges used क्रम CPU entry.
 */
अटल अंतरभूत bool within_cpu_entry(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end)
अणु
	पूर्णांक cpu;

	/* CPU entry erea is always used क्रम CPU entry */
	अगर (within_area(addr, end, CPU_ENTRY_AREA_BASE,
			CPU_ENTRY_AREA_TOTAL_SIZE))
		वापस true;

	/*
	 * When FSGSBASE is enabled, paranoid_entry() fetches the per-CPU
	 * GSBASE value via __per_cpu_offset or pcpu_unit_offsets.
	 */
#अगर_घोषित CONFIG_SMP
	अगर (within_area(addr, end, (अचिन्हित दीर्घ)__per_cpu_offset,
			माप(अचिन्हित दीर्घ) * nr_cpu_ids))
		वापस true;
#अन्यथा
	अगर (within_area(addr, end, (अचिन्हित दीर्घ)&pcpu_unit_offsets,
			माप(pcpu_unit_offsets)))
		वापस true;
#पूर्ण_अगर

	क्रम_each_possible_cpu(cpu) अणु
		/* The original rw GDT is being used after load_direct_gdt() */
		अगर (within_area(addr, end, (अचिन्हित दीर्घ)get_cpu_gdt_rw(cpu),
				GDT_SIZE))
			वापस true;

		/*
		 * cpu_tss_rw is not directly referenced by hardware, but
		 * cpu_tss_rw is also used in CPU entry code,
		 */
		अगर (within_area(addr, end,
				(अचिन्हित दीर्घ)&per_cpu(cpu_tss_rw, cpu),
				माप(काष्ठा tss_काष्ठा)))
			वापस true;

		/*
		 * cpu_tlbstate.user_pcid_flush_mask is used क्रम CPU entry.
		 * If a data अवरोधpoपूर्णांक on it, it will cause an unwanted #DB.
		 * Protect the full cpu_tlbstate काष्ठाure to be sure.
		 */
		अगर (within_area(addr, end,
				(अचिन्हित दीर्घ)&per_cpu(cpu_tlbstate, cpu),
				माप(काष्ठा tlb_state)))
			वापस true;

		/*
		 * When in guest (X86_FEATURE_HYPERVISOR), local_db_save()
		 * will पढ़ो per-cpu cpu_dr7 beक्रमe clear dr7 रेजिस्टर.
		 */
		अगर (within_area(addr, end, (अचिन्हित दीर्घ)&per_cpu(cpu_dr7, cpu),
				माप(cpu_dr7)))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक arch_build_bp_info(काष्ठा perf_event *bp,
			      स्थिर काष्ठा perf_event_attr *attr,
			      काष्ठा arch_hw_अवरोधpoपूर्णांक *hw)
अणु
	अचिन्हित दीर्घ bp_end;

	bp_end = attr->bp_addr + attr->bp_len - 1;
	अगर (bp_end < attr->bp_addr)
		वापस -EINVAL;

	/*
	 * Prevent any अवरोधpoपूर्णांक of any type that overlaps the CPU
	 * entry area and data.  This protects the IST stacks and also
	 * reduces the chance that we ever find out what happens अगर
	 * there's a data अवरोधpoपूर्णांक on the GDT, IDT, or TSS.
	 */
	अगर (within_cpu_entry(attr->bp_addr, bp_end))
		वापस -EINVAL;

	hw->address = attr->bp_addr;
	hw->mask = 0;

	/* Type */
	चयन (attr->bp_type) अणु
	हाल HW_BREAKPOINT_W:
		hw->type = X86_BREAKPOINT_WRITE;
		अवरोध;
	हाल HW_BREAKPOINT_W | HW_BREAKPOINT_R:
		hw->type = X86_BREAKPOINT_RW;
		अवरोध;
	हाल HW_BREAKPOINT_X:
		/*
		 * We करोn't allow kernel अवरोधpoपूर्णांकs in places that are not
		 * acceptable क्रम kprobes.  On non-kprobes kernels, we करोn't
		 * allow kernel अवरोधpoपूर्णांकs at all.
		 */
		अगर (attr->bp_addr >= TASK_SIZE_MAX) अणु
			अगर (within_kprobe_blacklist(attr->bp_addr))
				वापस -EINVAL;
		पूर्ण

		hw->type = X86_BREAKPOINT_EXECUTE;
		/*
		 * x86 inst अवरोधpoपूर्णांकs need to have a specअगरic undefined len.
		 * But we still need to check userspace is not trying to setup
		 * an unsupported length, to get a range अवरोधpoपूर्णांक क्रम example.
		 */
		अगर (attr->bp_len == माप(दीर्घ)) अणु
			hw->len = X86_BREAKPOINT_LEN_X;
			वापस 0;
		पूर्ण
		fallthrough;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Len */
	चयन (attr->bp_len) अणु
	हाल HW_BREAKPOINT_LEN_1:
		hw->len = X86_BREAKPOINT_LEN_1;
		अवरोध;
	हाल HW_BREAKPOINT_LEN_2:
		hw->len = X86_BREAKPOINT_LEN_2;
		अवरोध;
	हाल HW_BREAKPOINT_LEN_4:
		hw->len = X86_BREAKPOINT_LEN_4;
		अवरोध;
#अगर_घोषित CONFIG_X86_64
	हाल HW_BREAKPOINT_LEN_8:
		hw->len = X86_BREAKPOINT_LEN_8;
		अवरोध;
#पूर्ण_अगर
	शेष:
		/* AMD range अवरोधpoपूर्णांक */
		अगर (!is_घातer_of_2(attr->bp_len))
			वापस -EINVAL;
		अगर (attr->bp_addr & (attr->bp_len - 1))
			वापस -EINVAL;

		अगर (!boot_cpu_has(X86_FEATURE_BPEXT))
			वापस -EOPNOTSUPP;

		/*
		 * It's impossible to use a range अवरोधpoपूर्णांक to fake out
		 * user vs kernel detection because bp_len - 1 can't
		 * have the high bit set.  If we ever allow range inकाष्ठाion
		 * अवरोधpoपूर्णांकs, then we'll have to check क्रम kprobe-blacklisted
		 * addresses anywhere in the range.
		 */
		hw->mask = attr->bp_len - 1;
		hw->len = X86_BREAKPOINT_LEN_1;
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

	चयन (hw->len) अणु
	हाल X86_BREAKPOINT_LEN_1:
		align = 0;
		अगर (hw->mask)
			align = hw->mask;
		अवरोध;
	हाल X86_BREAKPOINT_LEN_2:
		align = 1;
		अवरोध;
	हाल X86_BREAKPOINT_LEN_4:
		align = 3;
		अवरोध;
#अगर_घोषित CONFIG_X86_64
	हाल X86_BREAKPOINT_LEN_8:
		align = 7;
		अवरोध;
#पूर्ण_अगर
	शेष:
		WARN_ON_ONCE(1);
		वापस -EINVAL;
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

	क्रम (i = 0; i < HBP_NUM; i++) अणु
		unरेजिस्टर_hw_अवरोधpoपूर्णांक(t->ptrace_bps[i]);
		t->ptrace_bps[i] = शून्य;
	पूर्ण

	t->भव_dr6 = 0;
	t->ptrace_dr7 = 0;
पूर्ण

व्योम hw_अवरोधpoपूर्णांक_restore(व्योम)
अणु
	set_debugreg(__this_cpu_पढ़ो(cpu_debugreg[0]), 0);
	set_debugreg(__this_cpu_पढ़ो(cpu_debugreg[1]), 1);
	set_debugreg(__this_cpu_पढ़ो(cpu_debugreg[2]), 2);
	set_debugreg(__this_cpu_पढ़ो(cpu_debugreg[3]), 3);
	set_debugreg(DR6_RESERVED, 6);
	set_debugreg(__this_cpu_पढ़ो(cpu_dr7), 7);
पूर्ण
EXPORT_SYMBOL_GPL(hw_अवरोधpoपूर्णांक_restore);

/*
 * Handle debug exception notअगरications.
 *
 * Return value is either NOTIFY_STOP or NOTIFY_DONE as explained below.
 *
 * NOTIFY_DONE वापसed अगर one of the following conditions is true.
 * i) When the causative address is from user-space and the exception
 * is a valid one, i.e. not triggered as a result of lazy debug रेजिस्टर
 * चयनing
 * ii) When there are more bits than trap<n> set in DR6 रेजिस्टर (such
 * as BD, BS or BT) indicating that more than one debug condition is
 * met and requires some more action in करो_debug().
 *
 * NOTIFY_STOP वापसed क्रम all other हालs
 *
 */
अटल पूर्णांक hw_अवरोधpoपूर्णांक_handler(काष्ठा die_args *args)
अणु
	पूर्णांक i, rc = NOTIFY_STOP;
	काष्ठा perf_event *bp;
	अचिन्हित दीर्घ *dr6_p;
	अचिन्हित दीर्घ dr6;
	bool bpx;

	/* The DR6 value is poपूर्णांकed by args->err */
	dr6_p = (अचिन्हित दीर्घ *)ERR_PTR(args->err);
	dr6 = *dr6_p;

	/* Do an early वापस अगर no trap bits are set in DR6 */
	अगर ((dr6 & DR_TRAP_BITS) == 0)
		वापस NOTIFY_DONE;

	/* Handle all the अवरोधpoपूर्णांकs that were triggered */
	क्रम (i = 0; i < HBP_NUM; ++i) अणु
		अगर (likely(!(dr6 & (DR_TRAP0 << i))))
			जारी;

		bp = this_cpu_पढ़ो(bp_per_reg[i]);
		अगर (!bp)
			जारी;

		bpx = bp->hw.info.type == X86_BREAKPOINT_EXECUTE;

		/*
		 * TF and data अवरोधpoपूर्णांकs are traps and can be merged, however
		 * inकाष्ठाion अवरोधpoपूर्णांकs are faults and will be उठाओd
		 * separately.
		 *
		 * However DR6 can indicate both TF and inकाष्ठाion
		 * अवरोधpoपूर्णांकs. In that हाल take TF as that has precedence and
		 * delay the inकाष्ठाion अवरोधpoपूर्णांक क्रम the next exception.
		 */
		अगर (bpx && (dr6 & DR_STEP))
			जारी;

		/*
		 * Reset the 'i'th TRAP bit in dr6 to denote completion of
		 * exception handling
		 */
		(*dr6_p) &= ~(DR_TRAP0 << i);

		perf_bp_event(bp, args->regs);

		/*
		 * Set up resume flag to aव्योम अवरोधpoपूर्णांक recursion when
		 * वापसing back to origin.
		 */
		अगर (bpx)
			args->regs->flags |= X86_EFLAGS_RF;
	पूर्ण

	/*
	 * Further processing in करो_debug() is needed क्रम a) user-space
	 * अवरोधpoपूर्णांकs (to generate संकेतs) and b) when the प्रणाली has
	 * taken exception due to multiple causes
	 */
	अगर ((current->thपढ़ो.भव_dr6 & DR_TRAP_BITS) ||
	    (dr6 & (~DR_TRAP_BITS)))
		rc = NOTIFY_DONE;

	वापस rc;
पूर्ण

/*
 * Handle debug exception notअगरications.
 */
पूर्णांक hw_अवरोधpoपूर्णांक_exceptions_notअगरy(
		काष्ठा notअगरier_block *unused, अचिन्हित दीर्घ val, व्योम *data)
अणु
	अगर (val != DIE_DEBUG)
		वापस NOTIFY_DONE;

	वापस hw_अवरोधpoपूर्णांक_handler(data);
पूर्ण

व्योम hw_अवरोधpoपूर्णांक_pmu_पढ़ो(काष्ठा perf_event *bp)
अणु
	/* TODO */
पूर्ण
