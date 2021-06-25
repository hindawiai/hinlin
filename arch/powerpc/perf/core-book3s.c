<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Perक्रमmance event support - घातerpc architecture code
 *
 * Copyright 2008-2009 Paul Mackerras, IBM Corporation.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/percpu.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/pmc.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/code-patching.h>
#समावेश <यंत्र/पूर्णांकerrupt.h>

#अगर_घोषित CONFIG_PPC64
#समावेश "internal.h"
#पूर्ण_अगर

#घोषणा BHRB_MAX_ENTRIES	32
#घोषणा BHRB_TARGET		0x0000000000000002
#घोषणा BHRB_PREDICTION		0x0000000000000001
#घोषणा BHRB_EA			0xFFFFFFFFFFFFFFFCUL

काष्ठा cpu_hw_events अणु
	पूर्णांक n_events;
	पूर्णांक n_percpu;
	पूर्णांक disabled;
	पूर्णांक n_added;
	पूर्णांक n_limited;
	u8  pmcs_enabled;
	काष्ठा perf_event *event[MAX_HWEVENTS];
	u64 events[MAX_HWEVENTS];
	अचिन्हित पूर्णांक flags[MAX_HWEVENTS];
	काष्ठा mmcr_regs mmcr;
	काष्ठा perf_event *limited_counter[MAX_LIMITED_HWCOUNTERS];
	u8  limited_hwidx[MAX_LIMITED_HWCOUNTERS];
	u64 alternatives[MAX_HWEVENTS][MAX_EVENT_ALTERNATIVES];
	अचिन्हित दीर्घ amasks[MAX_HWEVENTS][MAX_EVENT_ALTERNATIVES];
	अचिन्हित दीर्घ avalues[MAX_HWEVENTS][MAX_EVENT_ALTERNATIVES];

	अचिन्हित पूर्णांक txn_flags;
	पूर्णांक n_txn_start;

	/* BHRB bits */
	u64				bhrb_filter;	/* BHRB HW branch filter */
	अचिन्हित पूर्णांक			bhrb_users;
	व्योम				*bhrb_context;
	काष्ठा	perf_branch_stack	bhrb_stack;
	काष्ठा	perf_branch_entry	bhrb_entries[BHRB_MAX_ENTRIES];
	u64				ic_init;

	/* Store the PMC values */
	अचिन्हित दीर्घ pmcs[MAX_HWEVENTS];
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा cpu_hw_events, cpu_hw_events);

अटल काष्ठा घातer_pmu *ppmu;

/*
 * Normally, to ignore kernel events we set the FCS (मुक्तze counters
 * in supervisor mode) bit in MMCR0, but अगर the kernel runs with the
 * hypervisor bit set in the MSR, or अगर we are running on a processor
 * where the hypervisor bit is क्रमced to 1 (as on Apple G5 processors),
 * then we need to use the FCHV bit to ignore kernel events.
 */
अटल अचिन्हित पूर्णांक मुक्तze_events_kernel = MMCR0_FCS;

/*
 * 32-bit करोesn't have MMCRA but करोes have an MMCR2,
 * and a few other names are dअगरferent.
 * Also 32-bit करोesn't have MMCR3, SIER2 and SIER3.
 * Define them as zero knowing that any code path accessing
 * these रेजिस्टरs (via mtspr/mfspr) are करोne under ppmu flag
 * check क्रम PPMU_ARCH_31 and we will not enter that code path
 * क्रम 32-bit.
 */
#अगर_घोषित CONFIG_PPC32

#घोषणा MMCR0_FCHV		0
#घोषणा MMCR0_PMCjCE		MMCR0_PMCnCE
#घोषणा MMCR0_FC56		0
#घोषणा MMCR0_PMAO		0
#घोषणा MMCR0_EBE		0
#घोषणा MMCR0_BHRBA		0
#घोषणा MMCR0_PMCC		0
#घोषणा MMCR0_PMCC_U6		0

#घोषणा SPRN_MMCRA		SPRN_MMCR2
#घोषणा SPRN_MMCR3		0
#घोषणा SPRN_SIER2		0
#घोषणा SPRN_SIER3		0
#घोषणा MMCRA_SAMPLE_ENABLE	0
#घोषणा MMCRA_BHRB_DISABLE     0
#घोषणा MMCR0_PMCCEXT		0

अटल अंतरभूत अचिन्हित दीर्घ perf_ip_adjust(काष्ठा pt_regs *regs)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम perf_get_data_addr(काष्ठा perf_event *event, काष्ठा pt_regs *regs, u64 *addrp) अणु पूर्ण
अटल अंतरभूत u32 perf_get_misc_flags(काष्ठा pt_regs *regs)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम perf_पढ़ो_regs(काष्ठा pt_regs *regs)
अणु
	regs->result = 0;
पूर्ण

अटल अंतरभूत पूर्णांक siar_valid(काष्ठा pt_regs *regs)
अणु
	वापस 1;
पूर्ण

अटल bool is_ebb_event(काष्ठा perf_event *event) अणु वापस false; पूर्ण
अटल पूर्णांक ebb_event_check(काष्ठा perf_event *event) अणु वापस 0; पूर्ण
अटल व्योम ebb_event_add(काष्ठा perf_event *event) अणु पूर्ण
अटल व्योम ebb_चयन_out(अचिन्हित दीर्घ mmcr0) अणु पूर्ण
अटल अचिन्हित दीर्घ ebb_चयन_in(bool ebb, काष्ठा cpu_hw_events *cpuhw)
अणु
	वापस cpuhw->mmcr.mmcr0;
पूर्ण

अटल अंतरभूत व्योम घातer_pmu_bhrb_enable(काष्ठा perf_event *event) अणुपूर्ण
अटल अंतरभूत व्योम घातer_pmu_bhrb_disable(काष्ठा perf_event *event) अणुपूर्ण
अटल व्योम घातer_pmu_sched_task(काष्ठा perf_event_context *ctx, bool sched_in) अणुपूर्ण
अटल अंतरभूत व्योम घातer_pmu_bhrb_पढ़ो(काष्ठा perf_event *event, काष्ठा cpu_hw_events *cpuhw) अणुपूर्ण
अटल व्योम pmao_restore_workaround(bool ebb) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_PPC32 */

bool is_sier_available(व्योम)
अणु
	अगर (!ppmu)
		वापस false;

	अगर (ppmu->flags & PPMU_HAS_SIER)
		वापस true;

	वापस false;
पूर्ण

/*
 * Return PMC value corresponding to the
 * index passed.
 */
अचिन्हित दीर्घ get_pmcs_ext_regs(पूर्णांक idx)
अणु
	काष्ठा cpu_hw_events *cpuhw = this_cpu_ptr(&cpu_hw_events);

	वापस cpuhw->pmcs[idx];
पूर्ण

अटल bool regs_use_siar(काष्ठा pt_regs *regs)
अणु
	/*
	 * When we take a perक्रमmance monitor exception the regs are setup
	 * using perf_पढ़ो_regs() which overloads some fields, in particular
	 * regs->result to tell us whether to use SIAR.
	 *
	 * However अगर the regs are from another exception, eg. a syscall, then
	 * they have not been setup using perf_पढ़ो_regs() and so regs->result
	 * is something अक्रमom.
	 */
	वापस ((TRAP(regs) == INTERRUPT_PERFMON) && regs->result);
पूर्ण

/*
 * Things that are specअगरic to 64-bit implementations.
 */
#अगर_घोषित CONFIG_PPC64

अटल अंतरभूत अचिन्हित दीर्घ perf_ip_adjust(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ mmcra = regs->dsisr;

	अगर ((ppmu->flags & PPMU_HAS_SSLOT) && (mmcra & MMCRA_SAMPLE_ENABLE)) अणु
		अचिन्हित दीर्घ slot = (mmcra & MMCRA_SLOT) >> MMCRA_SLOT_SHIFT;
		अगर (slot > 1)
			वापस 4 * (slot - 1);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * The user wants a data address recorded.
 * If we're not करोing inकाष्ठाion sampling, give them the SDAR
 * (sampled data address).  If we are करोing inकाष्ठाion sampling, then
 * only give them the SDAR अगर it corresponds to the inकाष्ठाion
 * poपूर्णांकed to by SIAR; this is indicated by the [POWER6_]MMCRA_SDSYNC, the
 * [POWER7P_]MMCRA_SDAR_VALID bit in MMCRA, or the SDAR_VALID bit in SIER.
 */
अटल अंतरभूत व्योम perf_get_data_addr(काष्ठा perf_event *event, काष्ठा pt_regs *regs, u64 *addrp)
अणु
	अचिन्हित दीर्घ mmcra = regs->dsisr;
	bool sdar_valid;

	अगर (ppmu->flags & PPMU_HAS_SIER)
		sdar_valid = regs->dar & SIER_SDAR_VALID;
	अन्यथा अणु
		अचिन्हित दीर्घ sdsync;

		अगर (ppmu->flags & PPMU_SIAR_VALID)
			sdsync = POWER7P_MMCRA_SDAR_VALID;
		अन्यथा अगर (ppmu->flags & PPMU_ALT_SIPR)
			sdsync = POWER6_MMCRA_SDSYNC;
		अन्यथा अगर (ppmu->flags & PPMU_NO_SIAR)
			sdsync = MMCRA_SAMPLE_ENABLE;
		अन्यथा
			sdsync = MMCRA_SDSYNC;

		sdar_valid = mmcra & sdsync;
	पूर्ण

	अगर (!(mmcra & MMCRA_SAMPLE_ENABLE) || sdar_valid)
		*addrp = mfspr(SPRN_SDAR);

	अगर (is_kernel_addr(mfspr(SPRN_SDAR)) && event->attr.exclude_kernel)
		*addrp = 0;
पूर्ण

अटल bool regs_sihv(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ sihv = MMCRA_SIHV;

	अगर (ppmu->flags & PPMU_HAS_SIER)
		वापस !!(regs->dar & SIER_SIHV);

	अगर (ppmu->flags & PPMU_ALT_SIPR)
		sihv = POWER6_MMCRA_SIHV;

	वापस !!(regs->dsisr & sihv);
पूर्ण

अटल bool regs_sipr(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ sipr = MMCRA_SIPR;

	अगर (ppmu->flags & PPMU_HAS_SIER)
		वापस !!(regs->dar & SIER_SIPR);

	अगर (ppmu->flags & PPMU_ALT_SIPR)
		sipr = POWER6_MMCRA_SIPR;

	वापस !!(regs->dsisr & sipr);
पूर्ण

अटल अंतरभूत u32 perf_flags_from_msr(काष्ठा pt_regs *regs)
अणु
	अगर (regs->msr & MSR_PR)
		वापस PERF_RECORD_MISC_USER;
	अगर ((regs->msr & MSR_HV) && मुक्तze_events_kernel != MMCR0_FCHV)
		वापस PERF_RECORD_MISC_HYPERVISOR;
	वापस PERF_RECORD_MISC_KERNEL;
पूर्ण

अटल अंतरभूत u32 perf_get_misc_flags(काष्ठा pt_regs *regs)
अणु
	bool use_siar = regs_use_siar(regs);
	अचिन्हित दीर्घ mmcra = regs->dsisr;
	पूर्णांक marked = mmcra & MMCRA_SAMPLE_ENABLE;

	अगर (!use_siar)
		वापस perf_flags_from_msr(regs);

	/*
	 * Check the address in SIAR to identअगरy the
	 * privilege levels since the SIER[MSR_HV, MSR_PR]
	 * bits are not set क्रम marked events in घातer10
	 * DD1.
	 */
	अगर (marked && (ppmu->flags & PPMU_P10_DD1)) अणु
		अचिन्हित दीर्घ siar = mfspr(SPRN_SIAR);
		अगर (siar) अणु
			अगर (is_kernel_addr(siar))
				वापस PERF_RECORD_MISC_KERNEL;
			वापस PERF_RECORD_MISC_USER;
		पूर्ण अन्यथा अणु
			अगर (is_kernel_addr(regs->nip))
				वापस PERF_RECORD_MISC_KERNEL;
			वापस PERF_RECORD_MISC_USER;
		पूर्ण
	पूर्ण

	/*
	 * If we करोn't have flags in MMCRA, rather than using
	 * the MSR, we पूर्णांकuit the flags from the address in
	 * SIAR which should give slightly more reliable
	 * results
	 */
	अगर (ppmu->flags & PPMU_NO_SIPR) अणु
		अचिन्हित दीर्घ siar = mfspr(SPRN_SIAR);
		अगर (is_kernel_addr(siar))
			वापस PERF_RECORD_MISC_KERNEL;
		वापस PERF_RECORD_MISC_USER;
	पूर्ण

	/* PR has priority over HV, so order below is important */
	अगर (regs_sipr(regs))
		वापस PERF_RECORD_MISC_USER;

	अगर (regs_sihv(regs) && (मुक्तze_events_kernel != MMCR0_FCHV))
		वापस PERF_RECORD_MISC_HYPERVISOR;

	वापस PERF_RECORD_MISC_KERNEL;
पूर्ण

/*
 * Overload regs->dsisr to store MMCRA so we only need to पढ़ो it once
 * on each पूर्णांकerrupt.
 * Overload regs->dar to store SIER अगर we have it.
 * Overload regs->result to specअगरy whether we should use the MSR (result
 * is zero) or the SIAR (result is non zero).
 */
अटल अंतरभूत व्योम perf_पढ़ो_regs(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ mmcra = mfspr(SPRN_MMCRA);
	पूर्णांक marked = mmcra & MMCRA_SAMPLE_ENABLE;
	पूर्णांक use_siar;

	regs->dsisr = mmcra;

	अगर (ppmu->flags & PPMU_HAS_SIER)
		regs->dar = mfspr(SPRN_SIER);

	/*
	 * If this isn't a PMU exception (eg a software event) the SIAR is
	 * not valid. Use pt_regs.
	 *
	 * If it is a marked event use the SIAR.
	 *
	 * If the PMU करोesn't update the SIAR क्रम non marked events use
	 * pt_regs.
	 *
	 * If the PMU has HV/PR flags then check to see अगर they
	 * place the exception in userspace. If so, use pt_regs. In
	 * continuous sampling mode the SIAR and the PMU exception are
	 * not synchronised, so they may be many inकाष्ठाions apart.
	 * This can result in confusing backtraces. We still want
	 * hypervisor samples as well as samples in the kernel with
	 * पूर्णांकerrupts off hence the userspace check.
	 */
	अगर (TRAP(regs) != INTERRUPT_PERFMON)
		use_siar = 0;
	अन्यथा अगर ((ppmu->flags & PPMU_NO_SIAR))
		use_siar = 0;
	अन्यथा अगर (marked)
		use_siar = 1;
	अन्यथा अगर ((ppmu->flags & PPMU_NO_CONT_SAMPLING))
		use_siar = 0;
	अन्यथा अगर (!(ppmu->flags & PPMU_NO_SIPR) && regs_sipr(regs))
		use_siar = 0;
	अन्यथा
		use_siar = 1;

	regs->result = use_siar;
पूर्ण

/*
 * On processors like P7+ that have the SIAR-Valid bit, marked inकाष्ठाions
 * must be sampled only अगर the SIAR-valid bit is set.
 *
 * For unmarked inकाष्ठाions and क्रम processors that करोn't have the SIAR-Valid
 * bit, assume that SIAR is valid.
 */
अटल अंतरभूत पूर्णांक siar_valid(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ mmcra = regs->dsisr;
	पूर्णांक marked = mmcra & MMCRA_SAMPLE_ENABLE;

	अगर (marked) अणु
		/*
		 * SIER[SIAR_VALID] is not set क्रम some
		 * marked events on घातer10 DD1, so drop
		 * the check क्रम SIER[SIAR_VALID] and वापस true.
		 */
		अगर (ppmu->flags & PPMU_P10_DD1)
			वापस 0x1;
		अन्यथा अगर (ppmu->flags & PPMU_HAS_SIER)
			वापस regs->dar & SIER_SIAR_VALID;

		अगर (ppmu->flags & PPMU_SIAR_VALID)
			वापस mmcra & POWER7P_MMCRA_SIAR_VALID;
	पूर्ण

	वापस 1;
पूर्ण


/* Reset all possible BHRB entries */
अटल व्योम घातer_pmu_bhrb_reset(व्योम)
अणु
	यंत्र अस्थिर(PPC_CLRBHRB);
पूर्ण

अटल व्योम घातer_pmu_bhrb_enable(काष्ठा perf_event *event)
अणु
	काष्ठा cpu_hw_events *cpuhw = this_cpu_ptr(&cpu_hw_events);

	अगर (!ppmu->bhrb_nr)
		वापस;

	/* Clear BHRB अगर we changed task context to aव्योम data leaks */
	अगर (event->ctx->task && cpuhw->bhrb_context != event->ctx) अणु
		घातer_pmu_bhrb_reset();
		cpuhw->bhrb_context = event->ctx;
	पूर्ण
	cpuhw->bhrb_users++;
	perf_sched_cb_inc(event->ctx->pmu);
पूर्ण

अटल व्योम घातer_pmu_bhrb_disable(काष्ठा perf_event *event)
अणु
	काष्ठा cpu_hw_events *cpuhw = this_cpu_ptr(&cpu_hw_events);

	अगर (!ppmu->bhrb_nr)
		वापस;

	WARN_ON_ONCE(!cpuhw->bhrb_users);
	cpuhw->bhrb_users--;
	perf_sched_cb_dec(event->ctx->pmu);

	अगर (!cpuhw->disabled && !cpuhw->bhrb_users) अणु
		/* BHRB cannot be turned off when other
		 * events are active on the PMU.
		 */

		/* aव्योम stale poपूर्णांकer */
		cpuhw->bhrb_context = शून्य;
	पूर्ण
पूर्ण

/* Called from ctxsw to prevent one process's branch entries to
 * mingle with the other process's entries during context चयन.
 */
अटल व्योम घातer_pmu_sched_task(काष्ठा perf_event_context *ctx, bool sched_in)
अणु
	अगर (!ppmu->bhrb_nr)
		वापस;

	अगर (sched_in)
		घातer_pmu_bhrb_reset();
पूर्ण
/* Calculate the to address क्रम a branch */
अटल __u64 घातer_pmu_bhrb_to(u64 addr)
अणु
	अचिन्हित पूर्णांक instr;
	__u64 target;

	अगर (is_kernel_addr(addr)) अणु
		अगर (copy_from_kernel_nofault(&instr, (व्योम *)addr,
				माप(instr)))
			वापस 0;

		वापस branch_target((काष्ठा ppc_inst *)&instr);
	पूर्ण

	/* Userspace: need copy inकाष्ठाion here then translate it */
	अगर (copy_from_user_nofault(&instr, (अचिन्हित पूर्णांक __user *)addr,
			माप(instr)))
		वापस 0;

	target = branch_target((काष्ठा ppc_inst *)&instr);
	अगर ((!target) || (instr & BRANCH_ABSOLUTE))
		वापस target;

	/* Translate relative branch target from kernel to user address */
	वापस target - (अचिन्हित दीर्घ)&instr + addr;
पूर्ण

/* Processing BHRB entries */
अटल व्योम घातer_pmu_bhrb_पढ़ो(काष्ठा perf_event *event, काष्ठा cpu_hw_events *cpuhw)
अणु
	u64 val;
	u64 addr;
	पूर्णांक r_index, u_index, pred;

	r_index = 0;
	u_index = 0;
	जबतक (r_index < ppmu->bhrb_nr) अणु
		/* Assembly पढ़ो function */
		val = पढ़ो_bhrb(r_index++);
		अगर (!val)
			/* Terminal marker: End of valid BHRB entries */
			अवरोध;
		अन्यथा अणु
			addr = val & BHRB_EA;
			pred = val & BHRB_PREDICTION;

			अगर (!addr)
				/* invalid entry */
				जारी;

			/*
			 * BHRB rolling buffer could very much contain the kernel
			 * addresses at this poपूर्णांक. Check the privileges beक्रमe
			 * exporting it to userspace (aव्योम exposure of regions
			 * where we could have speculative execution)
			 * Inहाल of ISA v3.1, BHRB will capture only user-space
			 * addresses, hence include a check beक्रमe filtering code
			 */
			अगर (!(ppmu->flags & PPMU_ARCH_31) &&
			    is_kernel_addr(addr) && event->attr.exclude_kernel)
				जारी;

			/* Branches are पढ़ो most recent first (ie. mfbhrb 0 is
			 * the most recent branch).
			 * There are two types of valid entries:
			 * 1) a target entry which is the to address of a
			 *    computed जाओ like a blr,bctr,btar.  The next
			 *    entry पढ़ो from the bhrb will be branch
			 *    corresponding to this target (ie. the actual
			 *    blr/bctr/btar inकाष्ठाion).
			 * 2) a from address which is an actual branch.  If a
			 *    target entry proceeds this, then this is the
			 *    matching branch क्रम that target.  If this is not
			 *    following a target entry, then this is a branch
			 *    where the target is given as an immediate field
			 *    in the inकाष्ठाion (ie. an i or b क्रमm branch).
			 *    In this हाल we need to पढ़ो the inकाष्ठाion from
			 *    memory to determine the target/to address.
			 */

			अगर (val & BHRB_TARGET) अणु
				/* Target branches use two entries
				 * (ie. computed जाओs/XL क्रमm)
				 */
				cpuhw->bhrb_entries[u_index].to = addr;
				cpuhw->bhrb_entries[u_index].mispred = pred;
				cpuhw->bhrb_entries[u_index].predicted = ~pred;

				/* Get from address in next entry */
				val = पढ़ो_bhrb(r_index++);
				addr = val & BHRB_EA;
				अगर (val & BHRB_TARGET) अणु
					/* Shouldn't have two tarमाला_लो in a
					   row.. Reset index and try again */
					r_index--;
					addr = 0;
				पूर्ण
				cpuhw->bhrb_entries[u_index].from = addr;
			पूर्ण अन्यथा अणु
				/* Branches to immediate field 
				   (ie I or B क्रमm) */
				cpuhw->bhrb_entries[u_index].from = addr;
				cpuhw->bhrb_entries[u_index].to =
					घातer_pmu_bhrb_to(addr);
				cpuhw->bhrb_entries[u_index].mispred = pred;
				cpuhw->bhrb_entries[u_index].predicted = ~pred;
			पूर्ण
			u_index++;

		पूर्ण
	पूर्ण
	cpuhw->bhrb_stack.nr = u_index;
	cpuhw->bhrb_stack.hw_idx = -1ULL;
	वापस;
पूर्ण

अटल bool is_ebb_event(काष्ठा perf_event *event)
अणु
	/*
	 * This could be a per-PMU callback, but we'd rather aव्योम the cost. We
	 * check that the PMU supports EBB, meaning those that करोn't can still
	 * use bit 63 of the event code क्रम something अन्यथा अगर they wish.
	 */
	वापस (ppmu->flags & PPMU_ARCH_207S) &&
	       ((event->attr.config >> PERF_EVENT_CONFIG_EBB_SHIFT) & 1);
पूर्ण

अटल पूर्णांक ebb_event_check(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event *leader = event->group_leader;

	/* Event and group leader must agree on EBB */
	अगर (is_ebb_event(leader) != is_ebb_event(event))
		वापस -EINVAL;

	अगर (is_ebb_event(event)) अणु
		अगर (!(event->attach_state & PERF_ATTACH_TASK))
			वापस -EINVAL;

		अगर (!leader->attr.pinned || !leader->attr.exclusive)
			वापस -EINVAL;

		अगर (event->attr.freq ||
		    event->attr.inherit ||
		    event->attr.sample_type ||
		    event->attr.sample_period ||
		    event->attr.enable_on_exec)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ebb_event_add(काष्ठा perf_event *event)
अणु
	अगर (!is_ebb_event(event) || current->thपढ़ो.used_ebb)
		वापस;

	/*
	 * IFF this is the first समय we've added an EBB event, set
	 * PMXE in the user MMCR0 so we can detect when it's cleared by
	 * userspace. We need this so that we can context चयन जबतक
	 * userspace is in the EBB handler (where PMXE is 0).
	 */
	current->thपढ़ो.used_ebb = 1;
	current->thपढ़ो.mmcr0 |= MMCR0_PMXE;
पूर्ण

अटल व्योम ebb_चयन_out(अचिन्हित दीर्घ mmcr0)
अणु
	अगर (!(mmcr0 & MMCR0_EBE))
		वापस;

	current->thपढ़ो.siar  = mfspr(SPRN_SIAR);
	current->thपढ़ो.sier  = mfspr(SPRN_SIER);
	current->thपढ़ो.sdar  = mfspr(SPRN_SDAR);
	current->thपढ़ो.mmcr0 = mmcr0 & MMCR0_USER_MASK;
	current->thपढ़ो.mmcr2 = mfspr(SPRN_MMCR2) & MMCR2_USER_MASK;
	अगर (ppmu->flags & PPMU_ARCH_31) अणु
		current->thपढ़ो.mmcr3 = mfspr(SPRN_MMCR3);
		current->thपढ़ो.sier2 = mfspr(SPRN_SIER2);
		current->thपढ़ो.sier3 = mfspr(SPRN_SIER3);
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ ebb_चयन_in(bool ebb, काष्ठा cpu_hw_events *cpuhw)
अणु
	अचिन्हित दीर्घ mmcr0 = cpuhw->mmcr.mmcr0;

	अगर (!ebb)
		जाओ out;

	/* Enable EBB and पढ़ो/ग_लिखो to all 6 PMCs and BHRB क्रम userspace */
	mmcr0 |= MMCR0_EBE | MMCR0_BHRBA | MMCR0_PMCC_U6;

	/*
	 * Add any bits from the user MMCR0, FC or PMAO. This is compatible
	 * with pmao_restore_workaround() because we may add PMAO but we never
	 * clear it here.
	 */
	mmcr0 |= current->thपढ़ो.mmcr0;

	/*
	 * Be careful not to set PMXE अगर userspace had it cleared. This is also
	 * compatible with pmao_restore_workaround() because it has alपढ़ोy
	 * cleared PMXE and we leave PMAO alone.
	 */
	अगर (!(current->thपढ़ो.mmcr0 & MMCR0_PMXE))
		mmcr0 &= ~MMCR0_PMXE;

	mtspr(SPRN_SIAR, current->thपढ़ो.siar);
	mtspr(SPRN_SIER, current->thपढ़ो.sier);
	mtspr(SPRN_SDAR, current->thपढ़ो.sdar);

	/*
	 * Merge the kernel & user values of MMCR2. The semantics we implement
	 * are that the user MMCR2 can set bits, ie. cause counters to मुक्तze,
	 * but not clear bits. If a task wants to be able to clear bits, ie.
	 * unमुक्तze counters, it should not set exclude_xxx in its events and
	 * instead manage the MMCR2 entirely by itself.
	 */
	mtspr(SPRN_MMCR2, cpuhw->mmcr.mmcr2 | current->thपढ़ो.mmcr2);

	अगर (ppmu->flags & PPMU_ARCH_31) अणु
		mtspr(SPRN_MMCR3, current->thपढ़ो.mmcr3);
		mtspr(SPRN_SIER2, current->thपढ़ो.sier2);
		mtspr(SPRN_SIER3, current->thपढ़ो.sier3);
	पूर्ण
out:
	वापस mmcr0;
पूर्ण

अटल व्योम pmao_restore_workaround(bool ebb)
अणु
	अचिन्हित pmcs[6];

	अगर (!cpu_has_feature(CPU_FTR_PMAO_BUG))
		वापस;

	/*
	 * On POWER8E there is a hardware defect which affects the PMU context
	 * चयन logic, ie. घातer_pmu_disable/enable().
	 *
	 * When a counter overflows PMXE is cleared and FC/PMAO is set in MMCR0
	 * by the hardware. Someसमय later the actual PMU exception is
	 * delivered.
	 *
	 * If we context चयन, or simply disable/enable, the PMU prior to the
	 * exception arriving, the exception will be lost when we clear PMAO.
	 *
	 * When we reenable the PMU, we will ग_लिखो the saved MMCR0 with PMAO
	 * set, and this _should_ generate an exception. However because of the
	 * defect no exception is generated when we ग_लिखो PMAO, and we get
	 * stuck with no counters counting but no exception delivered.
	 *
	 * The workaround is to detect this हाल and tweak the hardware to
	 * create another pending PMU exception.
	 *
	 * We करो that by setting up PMC6 (cycles) क्रम an imminent overflow and
	 * enabling the PMU. That causes a new exception to be generated in the
	 * chip, but we करोn't take it yet because we have पूर्णांकerrupts hard
	 * disabled. We then ग_लिखो back the PMU state as we want it to be seen
	 * by the exception handler. When we reenable पूर्णांकerrupts the exception
	 * handler will be called and see the correct state.
	 *
	 * The logic is the same क्रम EBB, except that the exception is gated by
	 * us having पूर्णांकerrupts hard disabled as well as the fact that we are
	 * not in userspace. The exception is finally delivered when we वापस
	 * to userspace.
	 */

	/* Only अगर PMAO is set and PMAO_SYNC is clear */
	अगर ((current->thपढ़ो.mmcr0 & (MMCR0_PMAO | MMCR0_PMAO_SYNC)) != MMCR0_PMAO)
		वापस;

	/* If we're करोing EBB, only अगर BESCR[GE] is set */
	अगर (ebb && !(current->thपढ़ो.bescr & BESCR_GE))
		वापस;

	/*
	 * We are alपढ़ोy soft-disabled in घातer_pmu_enable(). We need to hard
	 * disable to actually prevent the PMU exception from firing.
	 */
	hard_irq_disable();

	/*
	 * This is a bit gross, but we know we're on POWER8E and have 6 PMCs.
	 * Using पढ़ो/ग_लिखो_pmc() in a क्रम loop adds 12 function calls and
	 * almost द्विगुनs our code size.
	 */
	pmcs[0] = mfspr(SPRN_PMC1);
	pmcs[1] = mfspr(SPRN_PMC2);
	pmcs[2] = mfspr(SPRN_PMC3);
	pmcs[3] = mfspr(SPRN_PMC4);
	pmcs[4] = mfspr(SPRN_PMC5);
	pmcs[5] = mfspr(SPRN_PMC6);

	/* Ensure all मुक्तze bits are unset */
	mtspr(SPRN_MMCR2, 0);

	/* Set up PMC6 to overflow in one cycle */
	mtspr(SPRN_PMC6, 0x7FFFFFFE);

	/* Enable exceptions and unमुक्तze PMC6 */
	mtspr(SPRN_MMCR0, MMCR0_PMXE | MMCR0_PMCjCE | MMCR0_PMAO);

	/* Now we need to reमुक्तze and restore the PMCs */
	mtspr(SPRN_MMCR0, MMCR0_FC | MMCR0_PMAO);

	mtspr(SPRN_PMC1, pmcs[0]);
	mtspr(SPRN_PMC2, pmcs[1]);
	mtspr(SPRN_PMC3, pmcs[2]);
	mtspr(SPRN_PMC4, pmcs[3]);
	mtspr(SPRN_PMC5, pmcs[4]);
	mtspr(SPRN_PMC6, pmcs[5]);
पूर्ण

#पूर्ण_अगर /* CONFIG_PPC64 */

अटल व्योम perf_event_पूर्णांकerrupt(काष्ठा pt_regs *regs);

/*
 * Read one perक्रमmance monitor counter (PMC).
 */
अटल अचिन्हित दीर्घ पढ़ो_pmc(पूर्णांक idx)
अणु
	अचिन्हित दीर्घ val;

	चयन (idx) अणु
	हाल 1:
		val = mfspr(SPRN_PMC1);
		अवरोध;
	हाल 2:
		val = mfspr(SPRN_PMC2);
		अवरोध;
	हाल 3:
		val = mfspr(SPRN_PMC3);
		अवरोध;
	हाल 4:
		val = mfspr(SPRN_PMC4);
		अवरोध;
	हाल 5:
		val = mfspr(SPRN_PMC5);
		अवरोध;
	हाल 6:
		val = mfspr(SPRN_PMC6);
		अवरोध;
#अगर_घोषित CONFIG_PPC64
	हाल 7:
		val = mfspr(SPRN_PMC7);
		अवरोध;
	हाल 8:
		val = mfspr(SPRN_PMC8);
		अवरोध;
#पूर्ण_अगर /* CONFIG_PPC64 */
	शेष:
		prपूर्णांकk(KERN_ERR "oops trying to read PMC%d\n", idx);
		val = 0;
	पूर्ण
	वापस val;
पूर्ण

/*
 * Write one PMC.
 */
अटल व्योम ग_लिखो_pmc(पूर्णांक idx, अचिन्हित दीर्घ val)
अणु
	चयन (idx) अणु
	हाल 1:
		mtspr(SPRN_PMC1, val);
		अवरोध;
	हाल 2:
		mtspr(SPRN_PMC2, val);
		अवरोध;
	हाल 3:
		mtspr(SPRN_PMC3, val);
		अवरोध;
	हाल 4:
		mtspr(SPRN_PMC4, val);
		अवरोध;
	हाल 5:
		mtspr(SPRN_PMC5, val);
		अवरोध;
	हाल 6:
		mtspr(SPRN_PMC6, val);
		अवरोध;
#अगर_घोषित CONFIG_PPC64
	हाल 7:
		mtspr(SPRN_PMC7, val);
		अवरोध;
	हाल 8:
		mtspr(SPRN_PMC8, val);
		अवरोध;
#पूर्ण_अगर /* CONFIG_PPC64 */
	शेष:
		prपूर्णांकk(KERN_ERR "oops trying to write PMC%d\n", idx);
	पूर्ण
पूर्ण

/* Called from sysrq_handle_showregs() */
व्योम perf_event_prपूर्णांक_debug(व्योम)
अणु
	अचिन्हित दीर्घ sdar, sier, flags;
	u32 pmcs[MAX_HWEVENTS];
	पूर्णांक i;

	अगर (!ppmu) अणु
		pr_info("Performance monitor hardware not registered.\n");
		वापस;
	पूर्ण

	अगर (!ppmu->n_counter)
		वापस;

	local_irq_save(flags);

	pr_info("CPU: %d PMU registers, ppmu = %s n_counters = %d",
		 smp_processor_id(), ppmu->name, ppmu->n_counter);

	क्रम (i = 0; i < ppmu->n_counter; i++)
		pmcs[i] = पढ़ो_pmc(i + 1);

	क्रम (; i < MAX_HWEVENTS; i++)
		pmcs[i] = 0xdeadbeef;

	pr_info("PMC1:  %08x PMC2: %08x PMC3: %08x PMC4: %08x\n",
		 pmcs[0], pmcs[1], pmcs[2], pmcs[3]);

	अगर (ppmu->n_counter > 4)
		pr_info("PMC5:  %08x PMC6: %08x PMC7: %08x PMC8: %08x\n",
			 pmcs[4], pmcs[5], pmcs[6], pmcs[7]);

	pr_info("MMCR0: %016lx MMCR1: %016lx MMCRA: %016lx\n",
		mfspr(SPRN_MMCR0), mfspr(SPRN_MMCR1), mfspr(SPRN_MMCRA));

	sdar = sier = 0;
#अगर_घोषित CONFIG_PPC64
	sdar = mfspr(SPRN_SDAR);

	अगर (ppmu->flags & PPMU_HAS_SIER)
		sier = mfspr(SPRN_SIER);

	अगर (ppmu->flags & PPMU_ARCH_207S) अणु
		pr_info("MMCR2: %016lx EBBHR: %016lx\n",
			mfspr(SPRN_MMCR2), mfspr(SPRN_EBBHR));
		pr_info("EBBRR: %016lx BESCR: %016lx\n",
			mfspr(SPRN_EBBRR), mfspr(SPRN_BESCR));
	पूर्ण

	अगर (ppmu->flags & PPMU_ARCH_31) अणु
		pr_info("MMCR3: %016lx SIER2: %016lx SIER3: %016lx\n",
			mfspr(SPRN_MMCR3), mfspr(SPRN_SIER2), mfspr(SPRN_SIER3));
	पूर्ण
#पूर्ण_अगर
	pr_info("SIAR:  %016lx SDAR:  %016lx SIER:  %016lx\n",
		mfspr(SPRN_SIAR), sdar, sier);

	local_irq_restore(flags);
पूर्ण

/*
 * Check अगर a set of events can all go on the PMU at once.
 * If they can't, this will look at alternative codes क्रम the events
 * and see अगर any combination of alternative codes is feasible.
 * The feasible set is वापसed in event_id[].
 */
अटल पूर्णांक घातer_check_स्थिरraपूर्णांकs(काष्ठा cpu_hw_events *cpuhw,
				   u64 event_id[], अचिन्हित पूर्णांक cflags[],
				   पूर्णांक n_ev, काष्ठा perf_event **event)
अणु
	अचिन्हित दीर्घ mask, value, nv;
	अचिन्हित दीर्घ smasks[MAX_HWEVENTS], svalues[MAX_HWEVENTS];
	पूर्णांक n_alt[MAX_HWEVENTS], choice[MAX_HWEVENTS];
	पूर्णांक i, j;
	अचिन्हित दीर्घ addf = ppmu->add_fields;
	अचिन्हित दीर्घ tadd = ppmu->test_adder;
	अचिन्हित दीर्घ grp_mask = ppmu->group_स्थिरraपूर्णांक_mask;
	अचिन्हित दीर्घ grp_val = ppmu->group_स्थिरraपूर्णांक_val;

	अगर (n_ev > ppmu->n_counter)
		वापस -1;

	/* First see अगर the events will go on as-is */
	क्रम (i = 0; i < n_ev; ++i) अणु
		अगर ((cflags[i] & PPMU_LIMITED_PMC_REQD)
		    && !ppmu->limited_pmc_event(event_id[i])) अणु
			ppmu->get_alternatives(event_id[i], cflags[i],
					       cpuhw->alternatives[i]);
			event_id[i] = cpuhw->alternatives[i][0];
		पूर्ण
		अगर (ppmu->get_स्थिरraपूर्णांक(event_id[i], &cpuhw->amasks[i][0],
					 &cpuhw->avalues[i][0], event[i]->attr.config1))
			वापस -1;
	पूर्ण
	value = mask = 0;
	क्रम (i = 0; i < n_ev; ++i) अणु
		nv = (value | cpuhw->avalues[i][0]) +
			(value & cpuhw->avalues[i][0] & addf);

		अगर (((((nv + tadd) ^ value) & mask) & (~grp_mask)) != 0)
			अवरोध;

		अगर (((((nv + tadd) ^ cpuhw->avalues[i][0]) & cpuhw->amasks[i][0])
			& (~grp_mask)) != 0)
			अवरोध;

		value = nv;
		mask |= cpuhw->amasks[i][0];
	पूर्ण
	अगर (i == n_ev) अणु
		अगर ((value & mask & grp_mask) != (mask & grp_val))
			वापस -1;
		अन्यथा
			वापस 0;	/* all OK */
	पूर्ण

	/* करोesn't work, gather alternatives... */
	अगर (!ppmu->get_alternatives)
		वापस -1;
	क्रम (i = 0; i < n_ev; ++i) अणु
		choice[i] = 0;
		n_alt[i] = ppmu->get_alternatives(event_id[i], cflags[i],
						  cpuhw->alternatives[i]);
		क्रम (j = 1; j < n_alt[i]; ++j)
			ppmu->get_स्थिरraपूर्णांक(cpuhw->alternatives[i][j],
					     &cpuhw->amasks[i][j],
					     &cpuhw->avalues[i][j],
					     event[i]->attr.config1);
	पूर्ण

	/* क्रमागतerate all possibilities and see अगर any will work */
	i = 0;
	j = -1;
	value = mask = nv = 0;
	जबतक (i < n_ev) अणु
		अगर (j >= 0) अणु
			/* we're backtracking, restore context */
			value = svalues[i];
			mask = smasks[i];
			j = choice[i];
		पूर्ण
		/*
		 * See अगर any alternative k क्रम event_id i,
		 * where k > j, will satisfy the स्थिरraपूर्णांकs.
		 */
		जबतक (++j < n_alt[i]) अणु
			nv = (value | cpuhw->avalues[i][j]) +
				(value & cpuhw->avalues[i][j] & addf);
			अगर ((((nv + tadd) ^ value) & mask) == 0 &&
			    (((nv + tadd) ^ cpuhw->avalues[i][j])
			     & cpuhw->amasks[i][j]) == 0)
				अवरोध;
		पूर्ण
		अगर (j >= n_alt[i]) अणु
			/*
			 * No feasible alternative, backtrack
			 * to event_id i-1 and जारी क्रमागतerating its
			 * alternatives from where we got up to.
			 */
			अगर (--i < 0)
				वापस -1;
		पूर्ण अन्यथा अणु
			/*
			 * Found a feasible alternative क्रम event_id i,
			 * remember where we got up to with this event_id,
			 * go on to the next event_id, and start with
			 * the first alternative क्रम it.
			 */
			choice[i] = j;
			svalues[i] = value;
			smasks[i] = mask;
			value = nv;
			mask |= cpuhw->amasks[i][j];
			++i;
			j = -1;
		पूर्ण
	पूर्ण

	/* OK, we have a feasible combination, tell the caller the solution */
	क्रम (i = 0; i < n_ev; ++i)
		event_id[i] = cpuhw->alternatives[i][choice[i]];
	वापस 0;
पूर्ण

/*
 * Check अगर newly-added events have consistent settings क्रम
 * exclude_अणुuser,kernel,hvपूर्ण with each other and any previously
 * added events.
 */
अटल पूर्णांक check_excludes(काष्ठा perf_event **ctrs, अचिन्हित पूर्णांक cflags[],
			  पूर्णांक n_prev, पूर्णांक n_new)
अणु
	पूर्णांक eu = 0, ek = 0, eh = 0;
	पूर्णांक i, n, first;
	काष्ठा perf_event *event;

	/*
	 * If the PMU we're on supports per event exclude settings then we
	 * करोn't need to करो any of this logic. NB. This assumes no PMU has both
	 * per event exclude and limited PMCs.
	 */
	अगर (ppmu->flags & PPMU_ARCH_207S)
		वापस 0;

	n = n_prev + n_new;
	अगर (n <= 1)
		वापस 0;

	first = 1;
	क्रम (i = 0; i < n; ++i) अणु
		अगर (cflags[i] & PPMU_LIMITED_PMC_OK) अणु
			cflags[i] &= ~PPMU_LIMITED_PMC_REQD;
			जारी;
		पूर्ण
		event = ctrs[i];
		अगर (first) अणु
			eu = event->attr.exclude_user;
			ek = event->attr.exclude_kernel;
			eh = event->attr.exclude_hv;
			first = 0;
		पूर्ण अन्यथा अगर (event->attr.exclude_user != eu ||
			   event->attr.exclude_kernel != ek ||
			   event->attr.exclude_hv != eh) अणु
			वापस -EAGAIN;
		पूर्ण
	पूर्ण

	अगर (eu || ek || eh)
		क्रम (i = 0; i < n; ++i)
			अगर (cflags[i] & PPMU_LIMITED_PMC_OK)
				cflags[i] |= PPMU_LIMITED_PMC_REQD;

	वापस 0;
पूर्ण

अटल u64 check_and_compute_delta(u64 prev, u64 val)
अणु
	u64 delta = (val - prev) & 0xfffffffful;

	/*
	 * POWER7 can roll back counter values, अगर the new value is smaller
	 * than the previous value it will cause the delta and the counter to
	 * have bogus values unless we rolled a counter over.  If a coutner is
	 * rolled back, it will be smaller, but within 256, which is the maximum
	 * number of events to rollback at once.  If we detect a rollback
	 * वापस 0.  This can lead to a small lack of precision in the
	 * counters.
	 */
	अगर (prev > val && (prev - val) < 256)
		delta = 0;

	वापस delta;
पूर्ण

अटल व्योम घातer_pmu_पढ़ो(काष्ठा perf_event *event)
अणु
	s64 val, delta, prev;

	अगर (event->hw.state & PERF_HES_STOPPED)
		वापस;

	अगर (!event->hw.idx)
		वापस;

	अगर (is_ebb_event(event)) अणु
		val = पढ़ो_pmc(event->hw.idx);
		local64_set(&event->hw.prev_count, val);
		वापस;
	पूर्ण

	/*
	 * Perक्रमmance monitor पूर्णांकerrupts come even when पूर्णांकerrupts
	 * are soft-disabled, as दीर्घ as पूर्णांकerrupts are hard-enabled.
	 * Thereक्रमe we treat them like NMIs.
	 */
	करो अणु
		prev = local64_पढ़ो(&event->hw.prev_count);
		barrier();
		val = पढ़ो_pmc(event->hw.idx);
		delta = check_and_compute_delta(prev, val);
		अगर (!delta)
			वापस;
	पूर्ण जबतक (local64_cmpxchg(&event->hw.prev_count, prev, val) != prev);

	local64_add(delta, &event->count);

	/*
	 * A number of places program the PMC with (0x80000000 - period_left).
	 * We never want period_left to be less than 1 because we will program
	 * the PMC with a value >= 0x800000000 and an edge detected PMC will
	 * roll around to 0 beक्रमe taking an exception. We have seen this
	 * on POWER8.
	 *
	 * To fix this, clamp the minimum value of period_left to 1.
	 */
	करो अणु
		prev = local64_पढ़ो(&event->hw.period_left);
		val = prev - delta;
		अगर (val < 1)
			val = 1;
	पूर्ण जबतक (local64_cmpxchg(&event->hw.period_left, prev, val) != prev);
पूर्ण

/*
 * On some machines, PMC5 and PMC6 can't be written, don't respect
 * the मुक्तze conditions, and करोn't generate पूर्णांकerrupts.  This tells
 * us अगर `event' is using such a PMC.
 */
अटल पूर्णांक is_limited_pmc(पूर्णांक pmcnum)
अणु
	वापस (ppmu->flags & PPMU_LIMITED_PMC5_6)
		&& (pmcnum == 5 || pmcnum == 6);
पूर्ण

अटल व्योम मुक्तze_limited_counters(काष्ठा cpu_hw_events *cpuhw,
				    अचिन्हित दीर्घ pmc5, अचिन्हित दीर्घ pmc6)
अणु
	काष्ठा perf_event *event;
	u64 val, prev, delta;
	पूर्णांक i;

	क्रम (i = 0; i < cpuhw->n_limited; ++i) अणु
		event = cpuhw->limited_counter[i];
		अगर (!event->hw.idx)
			जारी;
		val = (event->hw.idx == 5) ? pmc5 : pmc6;
		prev = local64_पढ़ो(&event->hw.prev_count);
		event->hw.idx = 0;
		delta = check_and_compute_delta(prev, val);
		अगर (delta)
			local64_add(delta, &event->count);
	पूर्ण
पूर्ण

अटल व्योम thaw_limited_counters(काष्ठा cpu_hw_events *cpuhw,
				  अचिन्हित दीर्घ pmc5, अचिन्हित दीर्घ pmc6)
अणु
	काष्ठा perf_event *event;
	u64 val, prev;
	पूर्णांक i;

	क्रम (i = 0; i < cpuhw->n_limited; ++i) अणु
		event = cpuhw->limited_counter[i];
		event->hw.idx = cpuhw->limited_hwidx[i];
		val = (event->hw.idx == 5) ? pmc5 : pmc6;
		prev = local64_पढ़ो(&event->hw.prev_count);
		अगर (check_and_compute_delta(prev, val))
			local64_set(&event->hw.prev_count, val);
		perf_event_update_userpage(event);
	पूर्ण
पूर्ण

/*
 * Since limited events करोn't respect the मुक्तze conditions, we
 * have to पढ़ो them immediately after मुक्तzing or unमुक्तzing the
 * other events.  We try to keep the values from the limited
 * events as consistent as possible by keeping the delay (in
 * cycles and inकाष्ठाions) between मुक्तzing/unमुक्तzing and पढ़ोing
 * the limited events as small and consistent as possible.
 * Thereक्रमe, अगर any limited events are in use, we पढ़ो them
 * both, and always in the same order, to minimize variability,
 * and करो it inside the same यंत्र that ग_लिखोs MMCR0.
 */
अटल व्योम ग_लिखो_mmcr0(काष्ठा cpu_hw_events *cpuhw, अचिन्हित दीर्घ mmcr0)
अणु
	अचिन्हित दीर्घ pmc5, pmc6;

	अगर (!cpuhw->n_limited) अणु
		mtspr(SPRN_MMCR0, mmcr0);
		वापस;
	पूर्ण

	/*
	 * Write MMCR0, then पढ़ो PMC5 and PMC6 immediately.
	 * To ensure we करोn't get a perक्रमmance monitor पूर्णांकerrupt
	 * between writing MMCR0 and मुक्तzing/thawing the limited
	 * events, we first ग_लिखो MMCR0 with the event overflow
	 * पूर्णांकerrupt enable bits turned off.
	 */
	यंत्र अस्थिर("mtspr %3,%2; mfspr %0,%4; mfspr %1,%5"
		     : "=&r" (pmc5), "=&r" (pmc6)
		     : "r" (mmcr0 & ~(MMCR0_PMC1CE | MMCR0_PMCjCE)),
		       "i" (SPRN_MMCR0),
		       "i" (SPRN_PMC5), "i" (SPRN_PMC6));

	अगर (mmcr0 & MMCR0_FC)
		मुक्तze_limited_counters(cpuhw, pmc5, pmc6);
	अन्यथा
		thaw_limited_counters(cpuhw, pmc5, pmc6);

	/*
	 * Write the full MMCR0 including the event overflow पूर्णांकerrupt
	 * enable bits, अगर necessary.
	 */
	अगर (mmcr0 & (MMCR0_PMC1CE | MMCR0_PMCjCE))
		mtspr(SPRN_MMCR0, mmcr0);
पूर्ण

/*
 * Disable all events to prevent PMU पूर्णांकerrupts and to allow
 * events to be added or हटाओd.
 */
अटल व्योम घातer_pmu_disable(काष्ठा pmu *pmu)
अणु
	काष्ठा cpu_hw_events *cpuhw;
	अचिन्हित दीर्घ flags, mmcr0, val, mmcra;

	अगर (!ppmu)
		वापस;
	local_irq_save(flags);
	cpuhw = this_cpu_ptr(&cpu_hw_events);

	अगर (!cpuhw->disabled) अणु
		/*
		 * Check अगर we ever enabled the PMU on this cpu.
		 */
		अगर (!cpuhw->pmcs_enabled) अणु
			ppc_enable_pmcs();
			cpuhw->pmcs_enabled = 1;
		पूर्ण

		/*
		 * Set the 'freeze counters' bit, clear EBE/BHRBA/PMCC/PMAO/FC56
		 */
		val  = mmcr0 = mfspr(SPRN_MMCR0);
		val |= MMCR0_FC;
		val &= ~(MMCR0_EBE | MMCR0_BHRBA | MMCR0_PMCC | MMCR0_PMAO |
			 MMCR0_FC56);
		/* Set mmcr0 PMCCEXT क्रम p10 */
		अगर (ppmu->flags & PPMU_ARCH_31)
			val |= MMCR0_PMCCEXT;

		/*
		 * The barrier is to make sure the mtspr has been
		 * executed and the PMU has frozen the events etc.
		 * beक्रमe we वापस.
		 */
		ग_लिखो_mmcr0(cpuhw, val);
		mb();
		isync();

		val = mmcra = cpuhw->mmcr.mmcra;

		/*
		 * Disable inकाष्ठाion sampling अगर it was enabled
		 */
		अगर (cpuhw->mmcr.mmcra & MMCRA_SAMPLE_ENABLE)
			val &= ~MMCRA_SAMPLE_ENABLE;

		/* Disable BHRB via mmcra (BHRBRD) क्रम p10 */
		अगर (ppmu->flags & PPMU_ARCH_31)
			val |= MMCRA_BHRB_DISABLE;

		/*
		 * Write SPRN_MMCRA अगर mmcra has either disabled
		 * inकाष्ठाion sampling or BHRB.
		 */
		अगर (val != mmcra) अणु
			mtspr(SPRN_MMCRA, mmcra);
			mb();
			isync();
		पूर्ण

		cpuhw->disabled = 1;
		cpuhw->n_added = 0;

		ebb_चयन_out(mmcr0);

#अगर_घोषित CONFIG_PPC64
		/*
		 * These are पढ़ोable by userspace, may contain kernel
		 * addresses and are not चयनed by context चयन, so clear
		 * them now to aव्योम leaking anything to userspace in general
		 * including to another process.
		 */
		अगर (ppmu->flags & PPMU_ARCH_207S) अणु
			mtspr(SPRN_SDAR, 0);
			mtspr(SPRN_SIAR, 0);
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	local_irq_restore(flags);
पूर्ण

/*
 * Re-enable all events अगर disable == 0.
 * If we were previously disabled and events were added, then
 * put the new config on the PMU.
 */
अटल व्योम घातer_pmu_enable(काष्ठा pmu *pmu)
अणु
	काष्ठा perf_event *event;
	काष्ठा cpu_hw_events *cpuhw;
	अचिन्हित दीर्घ flags;
	दीर्घ i;
	अचिन्हित दीर्घ val, mmcr0;
	s64 left;
	अचिन्हित पूर्णांक hwc_index[MAX_HWEVENTS];
	पूर्णांक n_lim;
	पूर्णांक idx;
	bool ebb;

	अगर (!ppmu)
		वापस;
	local_irq_save(flags);

	cpuhw = this_cpu_ptr(&cpu_hw_events);
	अगर (!cpuhw->disabled)
		जाओ out;

	अगर (cpuhw->n_events == 0) अणु
		ppc_set_pmu_inuse(0);
		जाओ out;
	पूर्ण

	cpuhw->disabled = 0;

	/*
	 * EBB requires an exclusive group and all events must have the EBB
	 * flag set, or not set, so we can just check a single event. Also we
	 * know we have at least one event.
	 */
	ebb = is_ebb_event(cpuhw->event[0]);

	/*
	 * If we didn't change anything, or only हटाओd events,
	 * no need to recalculate MMCR* settings and reset the PMCs.
	 * Just reenable the PMU with the current MMCR* settings
	 * (possibly updated क्रम removal of events).
	 */
	अगर (!cpuhw->n_added) अणु
		mtspr(SPRN_MMCRA, cpuhw->mmcr.mmcra & ~MMCRA_SAMPLE_ENABLE);
		mtspr(SPRN_MMCR1, cpuhw->mmcr.mmcr1);
		अगर (ppmu->flags & PPMU_ARCH_31)
			mtspr(SPRN_MMCR3, cpuhw->mmcr.mmcr3);
		जाओ out_enable;
	पूर्ण

	/*
	 * Clear all MMCR settings and recompute them क्रम the new set of events.
	 */
	स_रखो(&cpuhw->mmcr, 0, माप(cpuhw->mmcr));

	अगर (ppmu->compute_mmcr(cpuhw->events, cpuhw->n_events, hwc_index,
			       &cpuhw->mmcr, cpuhw->event, ppmu->flags)) अणु
		/* shouldn't ever get here */
		prपूर्णांकk(KERN_ERR "oops compute_mmcr failed\n");
		जाओ out;
	पूर्ण

	अगर (!(ppmu->flags & PPMU_ARCH_207S)) अणु
		/*
		 * Add in MMCR0 मुक्तze bits corresponding to the attr.exclude_*
		 * bits क्रम the first event. We have alपढ़ोy checked that all
		 * events have the same value क्रम these bits as the first event.
		 */
		event = cpuhw->event[0];
		अगर (event->attr.exclude_user)
			cpuhw->mmcr.mmcr0 |= MMCR0_FCP;
		अगर (event->attr.exclude_kernel)
			cpuhw->mmcr.mmcr0 |= मुक्तze_events_kernel;
		अगर (event->attr.exclude_hv)
			cpuhw->mmcr.mmcr0 |= MMCR0_FCHV;
	पूर्ण

	/*
	 * Write the new configuration to MMCR* with the मुक्तze
	 * bit set and set the hardware events to their initial values.
	 * Then unमुक्तze the events.
	 */
	ppc_set_pmu_inuse(1);
	mtspr(SPRN_MMCRA, cpuhw->mmcr.mmcra & ~MMCRA_SAMPLE_ENABLE);
	mtspr(SPRN_MMCR1, cpuhw->mmcr.mmcr1);
	mtspr(SPRN_MMCR0, (cpuhw->mmcr.mmcr0 & ~(MMCR0_PMC1CE | MMCR0_PMCjCE))
				| MMCR0_FC);
	अगर (ppmu->flags & PPMU_ARCH_207S)
		mtspr(SPRN_MMCR2, cpuhw->mmcr.mmcr2);

	अगर (ppmu->flags & PPMU_ARCH_31)
		mtspr(SPRN_MMCR3, cpuhw->mmcr.mmcr3);

	/*
	 * Read off any pre-existing events that need to move
	 * to another PMC.
	 */
	क्रम (i = 0; i < cpuhw->n_events; ++i) अणु
		event = cpuhw->event[i];
		अगर (event->hw.idx && event->hw.idx != hwc_index[i] + 1) अणु
			घातer_pmu_पढ़ो(event);
			ग_लिखो_pmc(event->hw.idx, 0);
			event->hw.idx = 0;
		पूर्ण
	पूर्ण

	/*
	 * Initialize the PMCs क्रम all the new and moved events.
	 */
	cpuhw->n_limited = n_lim = 0;
	क्रम (i = 0; i < cpuhw->n_events; ++i) अणु
		event = cpuhw->event[i];
		अगर (event->hw.idx)
			जारी;
		idx = hwc_index[i] + 1;
		अगर (is_limited_pmc(idx)) अणु
			cpuhw->limited_counter[n_lim] = event;
			cpuhw->limited_hwidx[n_lim] = idx;
			++n_lim;
			जारी;
		पूर्ण

		अगर (ebb)
			val = local64_पढ़ो(&event->hw.prev_count);
		अन्यथा अणु
			val = 0;
			अगर (event->hw.sample_period) अणु
				left = local64_पढ़ो(&event->hw.period_left);
				अगर (left < 0x80000000L)
					val = 0x80000000L - left;
			पूर्ण
			local64_set(&event->hw.prev_count, val);
		पूर्ण

		event->hw.idx = idx;
		अगर (event->hw.state & PERF_HES_STOPPED)
			val = 0;
		ग_लिखो_pmc(idx, val);

		perf_event_update_userpage(event);
	पूर्ण
	cpuhw->n_limited = n_lim;
	cpuhw->mmcr.mmcr0 |= MMCR0_PMXE | MMCR0_FCECE;

 out_enable:
	pmao_restore_workaround(ebb);

	mmcr0 = ebb_चयन_in(ebb, cpuhw);

	mb();
	अगर (cpuhw->bhrb_users)
		ppmu->config_bhrb(cpuhw->bhrb_filter);

	ग_लिखो_mmcr0(cpuhw, mmcr0);

	/*
	 * Enable inकाष्ठाion sampling अगर necessary
	 */
	अगर (cpuhw->mmcr.mmcra & MMCRA_SAMPLE_ENABLE) अणु
		mb();
		mtspr(SPRN_MMCRA, cpuhw->mmcr.mmcra);
	पूर्ण

 out:

	local_irq_restore(flags);
पूर्ण

अटल पूर्णांक collect_events(काष्ठा perf_event *group, पूर्णांक max_count,
			  काष्ठा perf_event *ctrs[], u64 *events,
			  अचिन्हित पूर्णांक *flags)
अणु
	पूर्णांक n = 0;
	काष्ठा perf_event *event;

	अगर (group->pmu->task_ctx_nr == perf_hw_context) अणु
		अगर (n >= max_count)
			वापस -1;
		ctrs[n] = group;
		flags[n] = group->hw.event_base;
		events[n++] = group->hw.config;
	पूर्ण
	क्रम_each_sibling_event(event, group) अणु
		अगर (event->pmu->task_ctx_nr == perf_hw_context &&
		    event->state != PERF_EVENT_STATE_OFF) अणु
			अगर (n >= max_count)
				वापस -1;
			ctrs[n] = event;
			flags[n] = event->hw.event_base;
			events[n++] = event->hw.config;
		पूर्ण
	पूर्ण
	वापस n;
पूर्ण

/*
 * Add an event to the PMU.
 * If all events are not alपढ़ोy frozen, then we disable and
 * re-enable the PMU in order to get hw_perf_enable to करो the
 * actual work of reconfiguring the PMU.
 */
अटल पूर्णांक घातer_pmu_add(काष्ठा perf_event *event, पूर्णांक ef_flags)
अणु
	काष्ठा cpu_hw_events *cpuhw;
	अचिन्हित दीर्घ flags;
	पूर्णांक n0;
	पूर्णांक ret = -EAGAIN;

	local_irq_save(flags);
	perf_pmu_disable(event->pmu);

	/*
	 * Add the event to the list (अगर there is room)
	 * and check whether the total set is still feasible.
	 */
	cpuhw = this_cpu_ptr(&cpu_hw_events);
	n0 = cpuhw->n_events;
	अगर (n0 >= ppmu->n_counter)
		जाओ out;
	cpuhw->event[n0] = event;
	cpuhw->events[n0] = event->hw.config;
	cpuhw->flags[n0] = event->hw.event_base;

	/*
	 * This event may have been disabled/stopped in record_and_restart()
	 * because we exceeded the ->event_limit. If re-starting the event,
	 * clear the ->hw.state (STOPPED and UPTODATE flags), so the user
	 * notअगरication is re-enabled.
	 */
	अगर (!(ef_flags & PERF_EF_START))
		event->hw.state = PERF_HES_STOPPED | PERF_HES_UPTODATE;
	अन्यथा
		event->hw.state = 0;

	/*
	 * If group events scheduling transaction was started,
	 * skip the schedulability test here, it will be perक्रमmed
	 * at commit समय(->commit_txn) as a whole
	 */
	अगर (cpuhw->txn_flags & PERF_PMU_TXN_ADD)
		जाओ nocheck;

	अगर (check_excludes(cpuhw->event, cpuhw->flags, n0, 1))
		जाओ out;
	अगर (घातer_check_स्थिरraपूर्णांकs(cpuhw, cpuhw->events, cpuhw->flags, n0 + 1, cpuhw->event))
		जाओ out;
	event->hw.config = cpuhw->events[n0];

nocheck:
	ebb_event_add(event);

	++cpuhw->n_events;
	++cpuhw->n_added;

	ret = 0;
 out:
	अगर (has_branch_stack(event)) अणु
		u64 bhrb_filter = -1;

		अगर (ppmu->bhrb_filter_map)
			bhrb_filter = ppmu->bhrb_filter_map(
				event->attr.branch_sample_type);

		अगर (bhrb_filter != -1) अणु
			cpuhw->bhrb_filter = bhrb_filter;
			घातer_pmu_bhrb_enable(event);
		पूर्ण
	पूर्ण

	perf_pmu_enable(event->pmu);
	local_irq_restore(flags);
	वापस ret;
पूर्ण

/*
 * Remove an event from the PMU.
 */
अटल व्योम घातer_pmu_del(काष्ठा perf_event *event, पूर्णांक ef_flags)
अणु
	काष्ठा cpu_hw_events *cpuhw;
	दीर्घ i;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	perf_pmu_disable(event->pmu);

	घातer_pmu_पढ़ो(event);

	cpuhw = this_cpu_ptr(&cpu_hw_events);
	क्रम (i = 0; i < cpuhw->n_events; ++i) अणु
		अगर (event == cpuhw->event[i]) अणु
			जबतक (++i < cpuhw->n_events) अणु
				cpuhw->event[i-1] = cpuhw->event[i];
				cpuhw->events[i-1] = cpuhw->events[i];
				cpuhw->flags[i-1] = cpuhw->flags[i];
			पूर्ण
			--cpuhw->n_events;
			ppmu->disable_pmc(event->hw.idx - 1, &cpuhw->mmcr);
			अगर (event->hw.idx) अणु
				ग_लिखो_pmc(event->hw.idx, 0);
				event->hw.idx = 0;
			पूर्ण
			perf_event_update_userpage(event);
			अवरोध;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < cpuhw->n_limited; ++i)
		अगर (event == cpuhw->limited_counter[i])
			अवरोध;
	अगर (i < cpuhw->n_limited) अणु
		जबतक (++i < cpuhw->n_limited) अणु
			cpuhw->limited_counter[i-1] = cpuhw->limited_counter[i];
			cpuhw->limited_hwidx[i-1] = cpuhw->limited_hwidx[i];
		पूर्ण
		--cpuhw->n_limited;
	पूर्ण
	अगर (cpuhw->n_events == 0) अणु
		/* disable exceptions अगर no events are running */
		cpuhw->mmcr.mmcr0 &= ~(MMCR0_PMXE | MMCR0_FCECE);
	पूर्ण

	अगर (has_branch_stack(event))
		घातer_pmu_bhrb_disable(event);

	perf_pmu_enable(event->pmu);
	local_irq_restore(flags);
पूर्ण

/*
 * POWER-PMU करोes not support disabling inभागidual counters, hence
 * program their cycle counter to their max value and ignore the पूर्णांकerrupts.
 */

अटल व्योम घातer_pmu_start(काष्ठा perf_event *event, पूर्णांक ef_flags)
अणु
	अचिन्हित दीर्घ flags;
	s64 left;
	अचिन्हित दीर्घ val;

	अगर (!event->hw.idx || !event->hw.sample_period)
		वापस;

	अगर (!(event->hw.state & PERF_HES_STOPPED))
		वापस;

	अगर (ef_flags & PERF_EF_RELOAD)
		WARN_ON_ONCE(!(event->hw.state & PERF_HES_UPTODATE));

	local_irq_save(flags);
	perf_pmu_disable(event->pmu);

	event->hw.state = 0;
	left = local64_पढ़ो(&event->hw.period_left);

	val = 0;
	अगर (left < 0x80000000L)
		val = 0x80000000L - left;

	ग_लिखो_pmc(event->hw.idx, val);

	perf_event_update_userpage(event);
	perf_pmu_enable(event->pmu);
	local_irq_restore(flags);
पूर्ण

अटल व्योम घातer_pmu_stop(काष्ठा perf_event *event, पूर्णांक ef_flags)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!event->hw.idx || !event->hw.sample_period)
		वापस;

	अगर (event->hw.state & PERF_HES_STOPPED)
		वापस;

	local_irq_save(flags);
	perf_pmu_disable(event->pmu);

	घातer_pmu_पढ़ो(event);
	event->hw.state |= PERF_HES_STOPPED | PERF_HES_UPTODATE;
	ग_लिखो_pmc(event->hw.idx, 0);

	perf_event_update_userpage(event);
	perf_pmu_enable(event->pmu);
	local_irq_restore(flags);
पूर्ण

/*
 * Start group events scheduling transaction
 * Set the flag to make pmu::enable() not perक्रमm the
 * schedulability test, it will be perक्रमmed at commit समय
 *
 * We only support PERF_PMU_TXN_ADD transactions. Save the
 * transaction flags but otherwise ignore non-PERF_PMU_TXN_ADD
 * transactions.
 */
अटल व्योम घातer_pmu_start_txn(काष्ठा pmu *pmu, अचिन्हित पूर्णांक txn_flags)
अणु
	काष्ठा cpu_hw_events *cpuhw = this_cpu_ptr(&cpu_hw_events);

	WARN_ON_ONCE(cpuhw->txn_flags);		/* txn alपढ़ोy in flight */

	cpuhw->txn_flags = txn_flags;
	अगर (txn_flags & ~PERF_PMU_TXN_ADD)
		वापस;

	perf_pmu_disable(pmu);
	cpuhw->n_txn_start = cpuhw->n_events;
पूर्ण

/*
 * Stop group events scheduling transaction
 * Clear the flag and pmu::enable() will perक्रमm the
 * schedulability test.
 */
अटल व्योम घातer_pmu_cancel_txn(काष्ठा pmu *pmu)
अणु
	काष्ठा cpu_hw_events *cpuhw = this_cpu_ptr(&cpu_hw_events);
	अचिन्हित पूर्णांक txn_flags;

	WARN_ON_ONCE(!cpuhw->txn_flags);	/* no txn in flight */

	txn_flags = cpuhw->txn_flags;
	cpuhw->txn_flags = 0;
	अगर (txn_flags & ~PERF_PMU_TXN_ADD)
		वापस;

	perf_pmu_enable(pmu);
पूर्ण

/*
 * Commit group events scheduling transaction
 * Perक्रमm the group schedulability test as a whole
 * Return 0 अगर success
 */
अटल पूर्णांक घातer_pmu_commit_txn(काष्ठा pmu *pmu)
अणु
	काष्ठा cpu_hw_events *cpuhw;
	दीर्घ i, n;

	अगर (!ppmu)
		वापस -EAGAIN;

	cpuhw = this_cpu_ptr(&cpu_hw_events);
	WARN_ON_ONCE(!cpuhw->txn_flags);	/* no txn in flight */

	अगर (cpuhw->txn_flags & ~PERF_PMU_TXN_ADD) अणु
		cpuhw->txn_flags = 0;
		वापस 0;
	पूर्ण

	n = cpuhw->n_events;
	अगर (check_excludes(cpuhw->event, cpuhw->flags, 0, n))
		वापस -EAGAIN;
	i = घातer_check_स्थिरraपूर्णांकs(cpuhw, cpuhw->events, cpuhw->flags, n, cpuhw->event);
	अगर (i < 0)
		वापस -EAGAIN;

	क्रम (i = cpuhw->n_txn_start; i < n; ++i)
		cpuhw->event[i]->hw.config = cpuhw->events[i];

	cpuhw->txn_flags = 0;
	perf_pmu_enable(pmu);
	वापस 0;
पूर्ण

/*
 * Return 1 अगर we might be able to put event on a limited PMC,
 * or 0 अगर not.
 * An event can only go on a limited PMC अगर it counts something
 * that a limited PMC can count, करोesn't require पूर्णांकerrupts, and
 * करोesn't exclude any processor mode.
 */
अटल पूर्णांक can_go_on_limited_pmc(काष्ठा perf_event *event, u64 ev,
				 अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक n;
	u64 alt[MAX_EVENT_ALTERNATIVES];

	अगर (event->attr.exclude_user
	    || event->attr.exclude_kernel
	    || event->attr.exclude_hv
	    || event->attr.sample_period)
		वापस 0;

	अगर (ppmu->limited_pmc_event(ev))
		वापस 1;

	/*
	 * The requested event_id isn't on a limited PMC alपढ़ोy;
	 * see अगर any alternative code goes on a limited PMC.
	 */
	अगर (!ppmu->get_alternatives)
		वापस 0;

	flags |= PPMU_LIMITED_PMC_OK | PPMU_LIMITED_PMC_REQD;
	n = ppmu->get_alternatives(ev, flags, alt);

	वापस n > 0;
पूर्ण

/*
 * Find an alternative event_id that goes on a normal PMC, अगर possible,
 * and वापस the event_id code, or 0 अगर there is no such alternative.
 * (Note: event_id code 0 is "don't count" on all machines.)
 */
अटल u64 normal_pmc_alternative(u64 ev, अचिन्हित दीर्घ flags)
अणु
	u64 alt[MAX_EVENT_ALTERNATIVES];
	पूर्णांक n;

	flags &= ~(PPMU_LIMITED_PMC_OK | PPMU_LIMITED_PMC_REQD);
	n = ppmu->get_alternatives(ev, flags, alt);
	अगर (!n)
		वापस 0;
	वापस alt[0];
पूर्ण

/* Number of perf_events counting hardware events */
अटल atomic_t num_events;
/* Used to aव्योम races in calling reserve/release_pmc_hardware */
अटल DEFINE_MUTEX(pmc_reserve_mutex);

/*
 * Release the PMU अगर this is the last perf_event.
 */
अटल व्योम hw_perf_event_destroy(काष्ठा perf_event *event)
अणु
	अगर (!atomic_add_unless(&num_events, -1, 1)) अणु
		mutex_lock(&pmc_reserve_mutex);
		अगर (atomic_dec_वापस(&num_events) == 0)
			release_pmc_hardware();
		mutex_unlock(&pmc_reserve_mutex);
	पूर्ण
पूर्ण

/*
 * Translate a generic cache event_id config to a raw event_id code.
 */
अटल पूर्णांक hw_perf_cache_event(u64 config, u64 *eventp)
अणु
	अचिन्हित दीर्घ type, op, result;
	u64 ev;

	अगर (!ppmu->cache_events)
		वापस -EINVAL;

	/* unpack config */
	type = config & 0xff;
	op = (config >> 8) & 0xff;
	result = (config >> 16) & 0xff;

	अगर (type >= PERF_COUNT_HW_CACHE_MAX ||
	    op >= PERF_COUNT_HW_CACHE_OP_MAX ||
	    result >= PERF_COUNT_HW_CACHE_RESULT_MAX)
		वापस -EINVAL;

	ev = (*ppmu->cache_events)[type][op][result];
	अगर (ev == 0)
		वापस -EOPNOTSUPP;
	अगर (ev == -1)
		वापस -EINVAL;
	*eventp = ev;
	वापस 0;
पूर्ण

अटल bool is_event_blacklisted(u64 ev)
अणु
	पूर्णांक i;

	क्रम (i=0; i < ppmu->n_blacklist_ev; i++) अणु
		अगर (ppmu->blacklist_ev[i] == ev)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक घातer_pmu_event_init(काष्ठा perf_event *event)
अणु
	u64 ev;
	अचिन्हित दीर्घ flags, irq_flags;
	काष्ठा perf_event *ctrs[MAX_HWEVENTS];
	u64 events[MAX_HWEVENTS];
	अचिन्हित पूर्णांक cflags[MAX_HWEVENTS];
	पूर्णांक n;
	पूर्णांक err;
	काष्ठा cpu_hw_events *cpuhw;

	अगर (!ppmu)
		वापस -ENOENT;

	अगर (has_branch_stack(event)) अणु
	        /* PMU has BHRB enabled */
		अगर (!(ppmu->flags & PPMU_ARCH_207S))
			वापस -EOPNOTSUPP;
	पूर्ण

	चयन (event->attr.type) अणु
	हाल PERF_TYPE_HARDWARE:
		ev = event->attr.config;
		अगर (ev >= ppmu->n_generic || ppmu->generic_events[ev] == 0)
			वापस -EOPNOTSUPP;

		अगर (ppmu->blacklist_ev && is_event_blacklisted(ev))
			वापस -EINVAL;
		ev = ppmu->generic_events[ev];
		अवरोध;
	हाल PERF_TYPE_HW_CACHE:
		err = hw_perf_cache_event(event->attr.config, &ev);
		अगर (err)
			वापस err;

		अगर (ppmu->blacklist_ev && is_event_blacklisted(ev))
			वापस -EINVAL;
		अवरोध;
	हाल PERF_TYPE_RAW:
		ev = event->attr.config;

		अगर (ppmu->blacklist_ev && is_event_blacklisted(ev))
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -ENOENT;
	पूर्ण

	/*
	 * PMU config रेजिस्टरs have fields that are
	 * reserved and some specअगरic values क्रम bit fields are reserved.
	 * For ex., MMCRA[61:62] is Ranकरोme Sampling Mode (SM)
	 * and value of 0b11 to this field is reserved.
	 * Check क्रम invalid values in attr.config.
	 */
	अगर (ppmu->check_attr_config &&
	    ppmu->check_attr_config(event))
		वापस -EINVAL;

	event->hw.config_base = ev;
	event->hw.idx = 0;

	/*
	 * If we are not running on a hypervisor, क्रमce the
	 * exclude_hv bit to 0 so that we करोn't care what
	 * the user set it to.
	 */
	अगर (!firmware_has_feature(FW_FEATURE_LPAR))
		event->attr.exclude_hv = 0;

	/*
	 * If this is a per-task event, then we can use
	 * PM_RUN_* events पूर्णांकerchangeably with their non RUN_*
	 * equivalents, e.g. PM_RUN_CYC instead of PM_CYC.
	 * XXX we should check अगर the task is an idle task.
	 */
	flags = 0;
	अगर (event->attach_state & PERF_ATTACH_TASK)
		flags |= PPMU_ONLY_COUNT_RUN;

	/*
	 * If this machine has limited events, check whether this
	 * event_id could go on a limited event.
	 */
	अगर (ppmu->flags & PPMU_LIMITED_PMC5_6) अणु
		अगर (can_go_on_limited_pmc(event, ev, flags)) अणु
			flags |= PPMU_LIMITED_PMC_OK;
		पूर्ण अन्यथा अगर (ppmu->limited_pmc_event(ev)) अणु
			/*
			 * The requested event_id is on a limited PMC,
			 * but we can't use a limited PMC; see अगर any
			 * alternative goes on a normal PMC.
			 */
			ev = normal_pmc_alternative(ev, flags);
			अगर (!ev)
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Extra checks क्रम EBB */
	err = ebb_event_check(event);
	अगर (err)
		वापस err;

	/*
	 * If this is in a group, check अगर it can go on with all the
	 * other hardware events in the group.  We assume the event
	 * hasn't been linked into its leader's sibling list at this poपूर्णांक.
	 */
	n = 0;
	अगर (event->group_leader != event) अणु
		n = collect_events(event->group_leader, ppmu->n_counter - 1,
				   ctrs, events, cflags);
		अगर (n < 0)
			वापस -EINVAL;
	पूर्ण
	events[n] = ev;
	ctrs[n] = event;
	cflags[n] = flags;
	अगर (check_excludes(ctrs, cflags, n, 1))
		वापस -EINVAL;

	local_irq_save(irq_flags);
	cpuhw = this_cpu_ptr(&cpu_hw_events);

	err = घातer_check_स्थिरraपूर्णांकs(cpuhw, events, cflags, n + 1, ctrs);

	अगर (has_branch_stack(event)) अणु
		u64 bhrb_filter = -1;

		अगर (ppmu->bhrb_filter_map)
			bhrb_filter = ppmu->bhrb_filter_map(
					event->attr.branch_sample_type);

		अगर (bhrb_filter == -1) अणु
			local_irq_restore(irq_flags);
			वापस -EOPNOTSUPP;
		पूर्ण
		cpuhw->bhrb_filter = bhrb_filter;
	पूर्ण

	local_irq_restore(irq_flags);
	अगर (err)
		वापस -EINVAL;

	event->hw.config = events[n];
	event->hw.event_base = cflags[n];
	event->hw.last_period = event->hw.sample_period;
	local64_set(&event->hw.period_left, event->hw.last_period);

	/*
	 * For EBB events we just context चयन the PMC value, we करोn't करो any
	 * of the sample_period logic. We use hw.prev_count क्रम this.
	 */
	अगर (is_ebb_event(event))
		local64_set(&event->hw.prev_count, 0);

	/*
	 * See अगर we need to reserve the PMU.
	 * If no events are currently in use, then we have to take a
	 * mutex to ensure that we करोn't race with another task करोing
	 * reserve_pmc_hardware or release_pmc_hardware.
	 */
	err = 0;
	अगर (!atomic_inc_not_zero(&num_events)) अणु
		mutex_lock(&pmc_reserve_mutex);
		अगर (atomic_पढ़ो(&num_events) == 0 &&
		    reserve_pmc_hardware(perf_event_पूर्णांकerrupt))
			err = -EBUSY;
		अन्यथा
			atomic_inc(&num_events);
		mutex_unlock(&pmc_reserve_mutex);
	पूर्ण
	event->destroy = hw_perf_event_destroy;

	वापस err;
पूर्ण

अटल पूर्णांक घातer_pmu_event_idx(काष्ठा perf_event *event)
अणु
	वापस event->hw.idx;
पूर्ण

sमाप_प्रकार घातer_events_sysfs_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *page)
अणु
	काष्ठा perf_pmu_events_attr *pmu_attr;

	pmu_attr = container_of(attr, काष्ठा perf_pmu_events_attr, attr);

	वापस प्र_लिखो(page, "event=0x%02llx\n", pmu_attr->id);
पूर्ण

अटल काष्ठा pmu घातer_pmu = अणु
	.pmu_enable	= घातer_pmu_enable,
	.pmu_disable	= घातer_pmu_disable,
	.event_init	= घातer_pmu_event_init,
	.add		= घातer_pmu_add,
	.del		= घातer_pmu_del,
	.start		= घातer_pmu_start,
	.stop		= घातer_pmu_stop,
	.पढ़ो		= घातer_pmu_पढ़ो,
	.start_txn	= घातer_pmu_start_txn,
	.cancel_txn	= घातer_pmu_cancel_txn,
	.commit_txn	= घातer_pmu_commit_txn,
	.event_idx	= घातer_pmu_event_idx,
	.sched_task	= घातer_pmu_sched_task,
पूर्ण;

#घोषणा PERF_SAMPLE_ADDR_TYPE  (PERF_SAMPLE_ADDR |		\
				PERF_SAMPLE_PHYS_ADDR |		\
				PERF_SAMPLE_DATA_PAGE_SIZE)
/*
 * A counter has overflowed; update its count and record
 * things अगर requested.  Note that पूर्णांकerrupts are hard-disabled
 * here so there is no possibility of being पूर्णांकerrupted.
 */
अटल व्योम record_and_restart(काष्ठा perf_event *event, अचिन्हित दीर्घ val,
			       काष्ठा pt_regs *regs)
अणु
	u64 period = event->hw.sample_period;
	s64 prev, delta, left;
	पूर्णांक record = 0;

	अगर (event->hw.state & PERF_HES_STOPPED) अणु
		ग_लिखो_pmc(event->hw.idx, 0);
		वापस;
	पूर्ण

	/* we करोn't have to worry about पूर्णांकerrupts here */
	prev = local64_पढ़ो(&event->hw.prev_count);
	delta = check_and_compute_delta(prev, val);
	local64_add(delta, &event->count);

	/*
	 * See अगर the total period क्रम this event has expired,
	 * and update क्रम the next period.
	 */
	val = 0;
	left = local64_पढ़ो(&event->hw.period_left) - delta;
	अगर (delta == 0)
		left++;
	अगर (period) अणु
		अगर (left <= 0) अणु
			left += period;
			अगर (left <= 0)
				left = period;

			/*
			 * If address is not requested in the sample via
			 * PERF_SAMPLE_IP, just record that sample irrespective
			 * of SIAR valid check.
			 */
			अगर (event->attr.sample_type & PERF_SAMPLE_IP)
				record = siar_valid(regs);
			अन्यथा
				record = 1;

			event->hw.last_period = event->hw.sample_period;
		पूर्ण
		अगर (left < 0x80000000LL)
			val = 0x80000000LL - left;
	पूर्ण

	ग_लिखो_pmc(event->hw.idx, val);
	local64_set(&event->hw.prev_count, val);
	local64_set(&event->hw.period_left, left);
	perf_event_update_userpage(event);

	/*
	 * Due to hardware limitation, someबार SIAR could sample a kernel
	 * address even when मुक्तze on supervisor state (kernel) is set in
	 * MMCR2. Check attr.exclude_kernel and address to drop the sample in
	 * these हालs.
	 */
	अगर (event->attr.exclude_kernel &&
	    (event->attr.sample_type & PERF_SAMPLE_IP) &&
	    is_kernel_addr(mfspr(SPRN_SIAR)))
		record = 0;

	/*
	 * Finally record data अगर requested.
	 */
	अगर (record) अणु
		काष्ठा perf_sample_data data;

		perf_sample_data_init(&data, ~0ULL, event->hw.last_period);

		अगर (event->attr.sample_type & PERF_SAMPLE_ADDR_TYPE)
			perf_get_data_addr(event, regs, &data.addr);

		अगर (event->attr.sample_type & PERF_SAMPLE_BRANCH_STACK) अणु
			काष्ठा cpu_hw_events *cpuhw;
			cpuhw = this_cpu_ptr(&cpu_hw_events);
			घातer_pmu_bhrb_पढ़ो(event, cpuhw);
			data.br_stack = &cpuhw->bhrb_stack;
		पूर्ण

		अगर (event->attr.sample_type & PERF_SAMPLE_DATA_SRC &&
						ppmu->get_mem_data_src)
			ppmu->get_mem_data_src(&data.data_src, ppmu->flags, regs);

		अगर (event->attr.sample_type & PERF_SAMPLE_WEIGHT_TYPE &&
						ppmu->get_mem_weight)
			ppmu->get_mem_weight(&data.weight.full, event->attr.sample_type);

		अगर (perf_event_overflow(event, &data, regs))
			घातer_pmu_stop(event, 0);
	पूर्ण अन्यथा अगर (period) अणु
		/* Account क्रम पूर्णांकerrupt in हाल of invalid SIAR */
		अगर (perf_event_account_पूर्णांकerrupt(event))
			घातer_pmu_stop(event, 0);
	पूर्ण
पूर्ण

/*
 * Called from generic code to get the misc flags (i.e. processor mode)
 * क्रम an event_id.
 */
अचिन्हित दीर्घ perf_misc_flags(काष्ठा pt_regs *regs)
अणु
	u32 flags = perf_get_misc_flags(regs);

	अगर (flags)
		वापस flags;
	वापस user_mode(regs) ? PERF_RECORD_MISC_USER :
		PERF_RECORD_MISC_KERNEL;
पूर्ण

/*
 * Called from generic code to get the inकाष्ठाion poपूर्णांकer
 * क्रम an event_id.
 */
अचिन्हित दीर्घ perf_inकाष्ठाion_poपूर्णांकer(काष्ठा pt_regs *regs)
अणु
	bool use_siar = regs_use_siar(regs);
	अचिन्हित दीर्घ siar = mfspr(SPRN_SIAR);

	अगर (ppmu && (ppmu->flags & PPMU_P10_DD1)) अणु
		अगर (siar)
			वापस siar;
		अन्यथा
			वापस regs->nip;
	पूर्ण अन्यथा अगर (use_siar && siar_valid(regs))
		वापस mfspr(SPRN_SIAR) + perf_ip_adjust(regs);
	अन्यथा अगर (use_siar)
		वापस 0;		// no valid inकाष्ठाion poपूर्णांकer
	अन्यथा
		वापस regs->nip;
पूर्ण

अटल bool pmc_overflow_घातer7(अचिन्हित दीर्घ val)
अणु
	/*
	 * Events on POWER7 can roll back अगर a speculative event करोesn't
	 * eventually complete. Unक्रमtunately in some rare हालs they will
	 * उठाओ a perक्रमmance monitor exception. We need to catch this to
	 * ensure we reset the PMC. In all हालs the PMC will be 256 or less
	 * cycles from overflow.
	 *
	 * We only करो this अगर the first pass fails to find any overflowing
	 * PMCs because a user might set a period of less than 256 and we
	 * करोn't want to mistakenly reset them.
	 */
	अगर ((0x80000000 - val) <= 256)
		वापस true;

	वापस false;
पूर्ण

अटल bool pmc_overflow(अचिन्हित दीर्घ val)
अणु
	अगर ((पूर्णांक)val < 0)
		वापस true;

	वापस false;
पूर्ण

/*
 * Perक्रमmance monitor पूर्णांकerrupt stuff
 */
अटल व्योम __perf_event_पूर्णांकerrupt(काष्ठा pt_regs *regs)
अणु
	पूर्णांक i, j;
	काष्ठा cpu_hw_events *cpuhw = this_cpu_ptr(&cpu_hw_events);
	काष्ठा perf_event *event;
	पूर्णांक found, active;

	अगर (cpuhw->n_limited)
		मुक्तze_limited_counters(cpuhw, mfspr(SPRN_PMC5),
					mfspr(SPRN_PMC6));

	perf_पढ़ो_regs(regs);

	/* Read all the PMCs since we'll need them a bunch of बार */
	क्रम (i = 0; i < ppmu->n_counter; ++i)
		cpuhw->pmcs[i] = पढ़ो_pmc(i + 1);

	/* Try to find what caused the IRQ */
	found = 0;
	क्रम (i = 0; i < ppmu->n_counter; ++i) अणु
		अगर (!pmc_overflow(cpuhw->pmcs[i]))
			जारी;
		अगर (is_limited_pmc(i + 1))
			जारी; /* these won't generate IRQs */
		/*
		 * We've found one that's overflowed.  For active
		 * counters we need to log this.  For inactive
		 * counters, we need to reset it anyway
		 */
		found = 1;
		active = 0;
		क्रम (j = 0; j < cpuhw->n_events; ++j) अणु
			event = cpuhw->event[j];
			अगर (event->hw.idx == (i + 1)) अणु
				active = 1;
				record_and_restart(event, cpuhw->pmcs[i], regs);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!active)
			/* reset non active counters that have overflowed */
			ग_लिखो_pmc(i + 1, 0);
	पूर्ण
	अगर (!found && pvr_version_is(PVR_POWER7)) अणु
		/* check active counters क्रम special buggy p7 overflow */
		क्रम (i = 0; i < cpuhw->n_events; ++i) अणु
			event = cpuhw->event[i];
			अगर (!event->hw.idx || is_limited_pmc(event->hw.idx))
				जारी;
			अगर (pmc_overflow_घातer7(cpuhw->pmcs[event->hw.idx - 1])) अणु
				/* event has overflowed in a buggy way*/
				found = 1;
				record_and_restart(event,
						   cpuhw->pmcs[event->hw.idx - 1],
						   regs);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (unlikely(!found) && !arch_irq_disabled_regs(regs))
		prपूर्णांकk_ratelimited(KERN_WARNING "Can't find PMC that caused IRQ\n");

	/*
	 * Reset MMCR0 to its normal value.  This will set PMXE and
	 * clear FC (मुक्तze counters) and PMAO (perf mon alert occurred)
	 * and thus allow पूर्णांकerrupts to occur again.
	 * XXX might want to use MSR.PM to keep the events frozen until
	 * we get back out of this पूर्णांकerrupt.
	 */
	ग_लिखो_mmcr0(cpuhw, cpuhw->mmcr.mmcr0);

	/* Clear the cpuhw->pmcs */
	स_रखो(&cpuhw->pmcs, 0, माप(cpuhw->pmcs));

पूर्ण

अटल व्योम perf_event_पूर्णांकerrupt(काष्ठा pt_regs *regs)
अणु
	u64 start_घड़ी = sched_घड़ी();

	__perf_event_पूर्णांकerrupt(regs);
	perf_sample_event_took(sched_घड़ी() - start_घड़ी);
पूर्ण

अटल पूर्णांक घातer_pmu_prepare_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpu_hw_events *cpuhw = &per_cpu(cpu_hw_events, cpu);

	अगर (ppmu) अणु
		स_रखो(cpuhw, 0, माप(*cpuhw));
		cpuhw->mmcr.mmcr0 = MMCR0_FC;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक रेजिस्टर_घातer_pmu(काष्ठा घातer_pmu *pmu)
अणु
	अगर (ppmu)
		वापस -EBUSY;		/* something's alपढ़ोy रेजिस्टरed */

	ppmu = pmu;
	pr_info("%s performance monitor hardware support registered\n",
		pmu->name);

	घातer_pmu.attr_groups = ppmu->attr_groups;
	घातer_pmu.capabilities |= (ppmu->capabilities & PERF_PMU_CAP_EXTENDED_REGS);

#अगर_घोषित MSR_HV
	/*
	 * Use FCHV to ignore kernel events अगर MSR.HV is set.
	 */
	अगर (mfmsr() & MSR_HV)
		मुक्तze_events_kernel = MMCR0_FCHV;
#पूर्ण_अगर /* CONFIG_PPC64 */

	perf_pmu_रेजिस्टर(&घातer_pmu, "cpu", PERF_TYPE_RAW);
	cpuhp_setup_state(CPUHP_PERF_POWER, "perf/powerpc:prepare",
			  घातer_pmu_prepare_cpu, शून्य);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PPC64
अटल पूर्णांक __init init_ppc64_pmu(व्योम)
अणु
	/* run through all the pmu drivers one at a समय */
	अगर (!init_घातer5_pmu())
		वापस 0;
	अन्यथा अगर (!init_घातer5p_pmu())
		वापस 0;
	अन्यथा अगर (!init_घातer6_pmu())
		वापस 0;
	अन्यथा अगर (!init_घातer7_pmu())
		वापस 0;
	अन्यथा अगर (!init_घातer8_pmu())
		वापस 0;
	अन्यथा अगर (!init_घातer9_pmu())
		वापस 0;
	अन्यथा अगर (!init_घातer10_pmu())
		वापस 0;
	अन्यथा अगर (!init_ppc970_pmu())
		वापस 0;
	अन्यथा
		वापस init_generic_compat_pmu();
पूर्ण
early_initcall(init_ppc64_pmu);
#पूर्ण_अगर
