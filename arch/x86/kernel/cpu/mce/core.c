<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Machine check handler.
 *
 * K8 parts Copyright 2002,2003 Andi Kleen, SuSE Lअसल.
 * Rest from unknown author(s).
 * 2004 Andi Kleen. Rewrote most of it.
 * Copyright 2008 Intel Corporation
 * Author: Andi Kleen
 */

#समावेश <linux/thपढ़ो_info.h>
#समावेश <linux/capability.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/kobject.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/kernel.h>
#समावेश <linux/percpu.h>
#समावेश <linux/माला.स>
#समावेश <linux/device.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/delay.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/sched.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/kmod.h>
#समावेश <linux/poll.h>
#समावेश <linux/nmi.h>
#समावेश <linux/cpu.h>
#समावेश <linux/ras.h>
#समावेश <linux/smp.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/export.h>
#समावेश <linux/set_memory.h>
#समावेश <linux/sync_core.h>
#समावेश <linux/task_work.h>
#समावेश <linux/hardirq.h>

#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/mce.h>
#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/reboot.h>

#समावेश "internal.h"

/* sysfs synchronization */
अटल DEFINE_MUTEX(mce_sysfs_mutex);

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/mce.h>

#घोषणा SPINUNIT		100	/* 100ns */

DEFINE_PER_CPU(अचिन्हित, mce_exception_count);

DEFINE_PER_CPU_READ_MOSTLY(अचिन्हित पूर्णांक, mce_num_banks);

काष्ठा mce_bank अणु
	u64			ctl;			/* subevents to enable */
	bool			init;			/* initialise bank? */
पूर्ण;
अटल DEFINE_PER_CPU_READ_MOSTLY(काष्ठा mce_bank[MAX_NR_BANKS], mce_banks_array);

#घोषणा ATTR_LEN               16
/* One object क्रम each MCE bank, shared by all CPUs */
काष्ठा mce_bank_dev अणु
	काष्ठा device_attribute	attr;			/* device attribute */
	अक्षर			attrname[ATTR_LEN];	/* attribute name */
	u8			bank;			/* bank number */
पूर्ण;
अटल काष्ठा mce_bank_dev mce_bank_devs[MAX_NR_BANKS];

काष्ठा mce_venकरोr_flags mce_flags __पढ़ो_mostly;

काष्ठा mca_config mca_cfg __पढ़ो_mostly = अणु
	.bootlog  = -1,
	/*
	 * Tolerant levels:
	 * 0: always panic on uncorrected errors, log corrected errors
	 * 1: panic or SIGBUS on uncorrected errors, log corrected errors
	 * 2: SIGBUS or log uncorrected errors (अगर possible), log corr. errors
	 * 3: never panic or SIGBUS, log all errors (क्रम testing only)
	 */
	.tolerant = 1,
	.monarch_समयout = -1
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा mce, mces_seen);
अटल अचिन्हित दीर्घ mce_need_notअगरy;
अटल पूर्णांक cpu_missing;

/*
 * MCA banks polled by the period polling समयr क्रम corrected events.
 * With Intel CMCI, this only has MCA banks which करो not support CMCI (अगर any).
 */
DEFINE_PER_CPU(mce_banks_t, mce_poll_banks) = अणु
	[0 ... BITS_TO_LONGS(MAX_NR_BANKS)-1] = ~0UL
पूर्ण;

/*
 * MCA banks controlled through firmware first क्रम corrected errors.
 * This is a global list of banks क्रम which we won't enable CMCI and we
 * won't poll. Firmware controls these banks and is responsible क्रम
 * reporting corrected errors through GHES. Uncorrected/recoverable
 * errors are still notअगरied through a machine check.
 */
mce_banks_t mce_banks_ce_disabled;

अटल काष्ठा work_काष्ठा mce_work;
अटल काष्ठा irq_work mce_irq_work;

अटल व्योम (*quirk_no_way_out)(पूर्णांक bank, काष्ठा mce *m, काष्ठा pt_regs *regs);

/*
 * CPU/chipset specअगरic EDAC code can रेजिस्टर a notअगरier call here to prपूर्णांक
 * MCE errors in a human-पढ़ोable क्रमm.
 */
BLOCKING_NOTIFIER_HEAD(x86_mce_decoder_chain);

/* Do initial initialization of a काष्ठा mce */
noinstr व्योम mce_setup(काष्ठा mce *m)
अणु
	स_रखो(m, 0, माप(काष्ठा mce));
	m->cpu = m->extcpu = smp_processor_id();
	/* need the पूर्णांकernal __ version to aव्योम deadlocks */
	m->समय = __kसमय_get_real_seconds();
	m->cpuvenकरोr = boot_cpu_data.x86_venकरोr;
	m->cpuid = cpuid_eax(1);
	m->socketid = cpu_data(m->extcpu).phys_proc_id;
	m->apicid = cpu_data(m->extcpu).initial_apicid;
	m->mcgcap = __rdmsr(MSR_IA32_MCG_CAP);

	अगर (this_cpu_has(X86_FEATURE_INTEL_PPIN))
		m->ppin = __rdmsr(MSR_PPIN);
	अन्यथा अगर (this_cpu_has(X86_FEATURE_AMD_PPIN))
		m->ppin = __rdmsr(MSR_AMD_PPIN);

	m->microcode = boot_cpu_data.microcode;
पूर्ण

DEFINE_PER_CPU(काष्ठा mce, injecपंचांग);
EXPORT_PER_CPU_SYMBOL_GPL(injecपंचांग);

व्योम mce_log(काष्ठा mce *m)
अणु
	अगर (!mce_gen_pool_add(m))
		irq_work_queue(&mce_irq_work);
पूर्ण
EXPORT_SYMBOL_GPL(mce_log);

व्योम mce_रेजिस्टर_decode_chain(काष्ठा notअगरier_block *nb)
अणु
	अगर (WARN_ON(nb->priority < MCE_PRIO_LOWEST ||
		    nb->priority > MCE_PRIO_HIGHEST))
		वापस;

	blocking_notअगरier_chain_रेजिस्टर(&x86_mce_decoder_chain, nb);
पूर्ण
EXPORT_SYMBOL_GPL(mce_रेजिस्टर_decode_chain);

व्योम mce_unरेजिस्टर_decode_chain(काष्ठा notअगरier_block *nb)
अणु
	blocking_notअगरier_chain_unरेजिस्टर(&x86_mce_decoder_chain, nb);
पूर्ण
EXPORT_SYMBOL_GPL(mce_unरेजिस्टर_decode_chain);

अटल अंतरभूत u32 ctl_reg(पूर्णांक bank)
अणु
	वापस MSR_IA32_MCx_CTL(bank);
पूर्ण

अटल अंतरभूत u32 status_reg(पूर्णांक bank)
अणु
	वापस MSR_IA32_MCx_STATUS(bank);
पूर्ण

अटल अंतरभूत u32 addr_reg(पूर्णांक bank)
अणु
	वापस MSR_IA32_MCx_ADDR(bank);
पूर्ण

अटल अंतरभूत u32 misc_reg(पूर्णांक bank)
अणु
	वापस MSR_IA32_MCx_MISC(bank);
पूर्ण

अटल अंतरभूत u32 smca_ctl_reg(पूर्णांक bank)
अणु
	वापस MSR_AMD64_SMCA_MCx_CTL(bank);
पूर्ण

अटल अंतरभूत u32 smca_status_reg(पूर्णांक bank)
अणु
	वापस MSR_AMD64_SMCA_MCx_STATUS(bank);
पूर्ण

अटल अंतरभूत u32 smca_addr_reg(पूर्णांक bank)
अणु
	वापस MSR_AMD64_SMCA_MCx_ADDR(bank);
पूर्ण

अटल अंतरभूत u32 smca_misc_reg(पूर्णांक bank)
अणु
	वापस MSR_AMD64_SMCA_MCx_MISC(bank);
पूर्ण

काष्ठा mca_msr_regs msr_ops = अणु
	.ctl	= ctl_reg,
	.status	= status_reg,
	.addr	= addr_reg,
	.misc	= misc_reg
पूर्ण;

अटल व्योम __prपूर्णांक_mce(काष्ठा mce *m)
अणु
	pr_emerg(HW_ERR "CPU %d: Machine Check%s: %Lx Bank %d: %016Lx\n",
		 m->extcpu,
		 (m->mcgstatus & MCG_STATUS_MCIP ? " Exception" : ""),
		 m->mcgstatus, m->bank, m->status);

	अगर (m->ip) अणु
		pr_emerg(HW_ERR "RIP%s %02x:<%016Lx> ",
			!(m->mcgstatus & MCG_STATUS_EIPV) ? " !INEXACT!" : "",
			m->cs, m->ip);

		अगर (m->cs == __KERNEL_CS)
			pr_cont("{%pS}", (व्योम *)(अचिन्हित दीर्घ)m->ip);
		pr_cont("\n");
	पूर्ण

	pr_emerg(HW_ERR "TSC %llx ", m->tsc);
	अगर (m->addr)
		pr_cont("ADDR %llx ", m->addr);
	अगर (m->misc)
		pr_cont("MISC %llx ", m->misc);
	अगर (m->ppin)
		pr_cont("PPIN %llx ", m->ppin);

	अगर (mce_flags.smca) अणु
		अगर (m->synd)
			pr_cont("SYND %llx ", m->synd);
		अगर (m->ipid)
			pr_cont("IPID %llx ", m->ipid);
	पूर्ण

	pr_cont("\n");

	/*
	 * Note this output is parsed by बाह्यal tools and old fields
	 * should not be changed.
	 */
	pr_emerg(HW_ERR "PROCESSOR %u:%x TIME %llu SOCKET %u APIC %x microcode %x\n",
		m->cpuvenकरोr, m->cpuid, m->समय, m->socketid, m->apicid,
		m->microcode);
पूर्ण

अटल व्योम prपूर्णांक_mce(काष्ठा mce *m)
अणु
	__prपूर्णांक_mce(m);

	अगर (m->cpuvenकरोr != X86_VENDOR_AMD && m->cpuvenकरोr != X86_VENDOR_HYGON)
		pr_emerg_ratelimited(HW_ERR "Run the above through 'mcelog --ascii'\n");
पूर्ण

#घोषणा PANIC_TIMEOUT 5 /* 5 seconds */

अटल atomic_t mce_panicked;

अटल पूर्णांक fake_panic;
अटल atomic_t mce_fake_panicked;

/* Panic in progress. Enable पूर्णांकerrupts and रुको क्रम final IPI */
अटल व्योम रुको_क्रम_panic(व्योम)
अणु
	दीर्घ समयout = PANIC_TIMEOUT*USEC_PER_SEC;

	preempt_disable();
	local_irq_enable();
	जबतक (समयout-- > 0)
		udelay(1);
	अगर (panic_समयout == 0)
		panic_समयout = mca_cfg.panic_समयout;
	panic("Panicing machine check CPU died");
पूर्ण

अटल व्योम mce_panic(स्थिर अक्षर *msg, काष्ठा mce *final, अक्षर *exp)
अणु
	पूर्णांक apei_err = 0;
	काष्ठा llist_node *pending;
	काष्ठा mce_evt_llist *l;

	अगर (!fake_panic) अणु
		/*
		 * Make sure only one CPU runs in machine check panic
		 */
		अगर (atomic_inc_वापस(&mce_panicked) > 1)
			रुको_क्रम_panic();
		barrier();

		bust_spinlocks(1);
		console_verbose();
	पूर्ण अन्यथा अणु
		/* Don't log too much क्रम fake panic */
		अगर (atomic_inc_वापस(&mce_fake_panicked) > 1)
			वापस;
	पूर्ण
	pending = mce_gen_pool_prepare_records();
	/* First prपूर्णांक corrected ones that are still unlogged */
	llist_क्रम_each_entry(l, pending, llnode) अणु
		काष्ठा mce *m = &l->mce;
		अगर (!(m->status & MCI_STATUS_UC)) अणु
			prपूर्णांक_mce(m);
			अगर (!apei_err)
				apei_err = apei_ग_लिखो_mce(m);
		पूर्ण
	पूर्ण
	/* Now prपूर्णांक uncorrected but with the final one last */
	llist_क्रम_each_entry(l, pending, llnode) अणु
		काष्ठा mce *m = &l->mce;
		अगर (!(m->status & MCI_STATUS_UC))
			जारी;
		अगर (!final || mce_cmp(m, final)) अणु
			prपूर्णांक_mce(m);
			अगर (!apei_err)
				apei_err = apei_ग_लिखो_mce(m);
		पूर्ण
	पूर्ण
	अगर (final) अणु
		prपूर्णांक_mce(final);
		अगर (!apei_err)
			apei_err = apei_ग_लिखो_mce(final);
	पूर्ण
	अगर (cpu_missing)
		pr_emerg(HW_ERR "Some CPUs didn't answer in synchronization\n");
	अगर (exp)
		pr_emerg(HW_ERR "Machine check: %s\n", exp);
	अगर (!fake_panic) अणु
		अगर (panic_समयout == 0)
			panic_समयout = mca_cfg.panic_समयout;
		panic(msg);
	पूर्ण अन्यथा
		pr_emerg(HW_ERR "Fake kernel panic: %s\n", msg);
पूर्ण

/* Support code क्रम software error injection */

अटल पूर्णांक msr_to_offset(u32 msr)
अणु
	अचिन्हित bank = __this_cpu_पढ़ो(injecपंचांग.bank);

	अगर (msr == mca_cfg.rip_msr)
		वापस दुरत्व(काष्ठा mce, ip);
	अगर (msr == msr_ops.status(bank))
		वापस दुरत्व(काष्ठा mce, status);
	अगर (msr == msr_ops.addr(bank))
		वापस दुरत्व(काष्ठा mce, addr);
	अगर (msr == msr_ops.misc(bank))
		वापस दुरत्व(काष्ठा mce, misc);
	अगर (msr == MSR_IA32_MCG_STATUS)
		वापस दुरत्व(काष्ठा mce, mcgstatus);
	वापस -1;
पूर्ण

__visible bool ex_handler_rdmsr_fault(स्थिर काष्ठा exception_table_entry *fixup,
				      काष्ठा pt_regs *regs, पूर्णांक trapnr,
				      अचिन्हित दीर्घ error_code,
				      अचिन्हित दीर्घ fault_addr)
अणु
	pr_emerg("MSR access error: RDMSR from 0x%x at rIP: 0x%lx (%pS)\n",
		 (अचिन्हित पूर्णांक)regs->cx, regs->ip, (व्योम *)regs->ip);

	show_stack_regs(regs);

	panic("MCA architectural violation!\n");

	जबतक (true)
		cpu_relax();

	वापस true;
पूर्ण

/* MSR access wrappers used क्रम error injection */
अटल noinstr u64 mce_rdmsrl(u32 msr)
अणु
	DECLARE_ARGS(val, low, high);

	अगर (__this_cpu_पढ़ो(injecपंचांग.finished)) अणु
		पूर्णांक offset;
		u64 ret;

		instrumentation_begin();

		offset = msr_to_offset(msr);
		अगर (offset < 0)
			ret = 0;
		अन्यथा
			ret = *(u64 *)((अक्षर *)this_cpu_ptr(&injecपंचांग) + offset);

		instrumentation_end();

		वापस ret;
	पूर्ण

	/*
	 * RDMSR on MCA MSRs should not fault. If they करो, this is very much an
	 * architectural violation and needs to be reported to hw venकरोr. Panic
	 * the box to not allow any further progress.
	 */
	यंत्र अस्थिर("1: rdmsr\n"
		     "2:\n"
		     _ASM_EXTABLE_HANDLE(1b, 2b, ex_handler_rdmsr_fault)
		     : EAX_EDX_RET(val, low, high) : "c" (msr));


	वापस EAX_EDX_VAL(val, low, high);
पूर्ण

__visible bool ex_handler_wrmsr_fault(स्थिर काष्ठा exception_table_entry *fixup,
				      काष्ठा pt_regs *regs, पूर्णांक trapnr,
				      अचिन्हित दीर्घ error_code,
				      अचिन्हित दीर्घ fault_addr)
अणु
	pr_emerg("MSR access error: WRMSR to 0x%x (tried to write 0x%08x%08x) at rIP: 0x%lx (%pS)\n",
		 (अचिन्हित पूर्णांक)regs->cx, (अचिन्हित पूर्णांक)regs->dx, (अचिन्हित पूर्णांक)regs->ax,
		  regs->ip, (व्योम *)regs->ip);

	show_stack_regs(regs);

	panic("MCA architectural violation!\n");

	जबतक (true)
		cpu_relax();

	वापस true;
पूर्ण

अटल noinstr व्योम mce_wrmsrl(u32 msr, u64 v)
अणु
	u32 low, high;

	अगर (__this_cpu_पढ़ो(injecपंचांग.finished)) अणु
		पूर्णांक offset;

		instrumentation_begin();

		offset = msr_to_offset(msr);
		अगर (offset >= 0)
			*(u64 *)((अक्षर *)this_cpu_ptr(&injecपंचांग) + offset) = v;

		instrumentation_end();

		वापस;
	पूर्ण

	low  = (u32)v;
	high = (u32)(v >> 32);

	/* See comment in mce_rdmsrl() */
	यंत्र अस्थिर("1: wrmsr\n"
		     "2:\n"
		     _ASM_EXTABLE_HANDLE(1b, 2b, ex_handler_wrmsr_fault)
		     : : "c" (msr), "a"(low), "d" (high) : "memory");
पूर्ण

/*
 * Collect all global (w.r.t. this processor) status about this machine
 * check पूर्णांकo our "mce" काष्ठा so that we can use it later to assess
 * the severity of the problem as we पढ़ो per-bank specअगरic details.
 */
अटल अंतरभूत व्योम mce_gather_info(काष्ठा mce *m, काष्ठा pt_regs *regs)
अणु
	mce_setup(m);

	m->mcgstatus = mce_rdmsrl(MSR_IA32_MCG_STATUS);
	अगर (regs) अणु
		/*
		 * Get the address of the inकाष्ठाion at the समय of
		 * the machine check error.
		 */
		अगर (m->mcgstatus & (MCG_STATUS_RIPV|MCG_STATUS_EIPV)) अणु
			m->ip = regs->ip;
			m->cs = regs->cs;

			/*
			 * When in VM86 mode make the cs look like ring 3
			 * always. This is a lie, but it's better than passing
			 * the additional vm86 bit around everywhere.
			 */
			अगर (v8086_mode(regs))
				m->cs |= 3;
		पूर्ण
		/* Use accurate RIP reporting अगर available. */
		अगर (mca_cfg.rip_msr)
			m->ip = mce_rdmsrl(mca_cfg.rip_msr);
	पूर्ण
पूर्ण

पूर्णांक mce_available(काष्ठा cpuinfo_x86 *c)
अणु
	अगर (mca_cfg.disabled)
		वापस 0;
	वापस cpu_has(c, X86_FEATURE_MCE) && cpu_has(c, X86_FEATURE_MCA);
पूर्ण

अटल व्योम mce_schedule_work(व्योम)
अणु
	अगर (!mce_gen_pool_empty())
		schedule_work(&mce_work);
पूर्ण

अटल व्योम mce_irq_work_cb(काष्ठा irq_work *entry)
अणु
	mce_schedule_work();
पूर्ण

/*
 * Check अगर the address reported by the CPU is in a क्रमmat we can parse.
 * It would be possible to add code क्रम most other हालs, but all would
 * be somewhat complicated (e.g. segment offset would require an inकाष्ठाion
 * parser). So only support physical addresses up to page granularity क्रम now.
 */
पूर्णांक mce_usable_address(काष्ठा mce *m)
अणु
	अगर (!(m->status & MCI_STATUS_ADDRV))
		वापस 0;

	/* Checks after this one are Intel/Zhaoxin-specअगरic: */
	अगर (boot_cpu_data.x86_venकरोr != X86_VENDOR_INTEL &&
	    boot_cpu_data.x86_venकरोr != X86_VENDOR_ZHAOXIN)
		वापस 1;

	अगर (!(m->status & MCI_STATUS_MISCV))
		वापस 0;

	अगर (MCI_MISC_ADDR_LSB(m->misc) > PAGE_SHIFT)
		वापस 0;

	अगर (MCI_MISC_ADDR_MODE(m->misc) != MCI_MISC_ADDR_PHYS)
		वापस 0;

	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(mce_usable_address);

bool mce_is_memory_error(काष्ठा mce *m)
अणु
	चयन (m->cpuvenकरोr) अणु
	हाल X86_VENDOR_AMD:
	हाल X86_VENDOR_HYGON:
		वापस amd_mce_is_memory_error(m);

	हाल X86_VENDOR_INTEL:
	हाल X86_VENDOR_ZHAOXIN:
		/*
		 * Intel SDM Volume 3B - 15.9.2 Compound Error Codes
		 *
		 * Bit 7 of the MCACOD field of IA32_MCi_STATUS is used क्रम
		 * indicating a memory error. Bit 8 is used क्रम indicating a
		 * cache hierarchy error. The combination of bit 2 and bit 3
		 * is used क्रम indicating a `generic' cache hierarchy error
		 * But we can't just blindly check the above bits, because अगर
		 * bit 11 is set, then it is a bus/पूर्णांकerconnect error - and
		 * either way the above bits just gives more detail on what
		 * bus/पूर्णांकerconnect error happened. Note that bit 12 can be
		 * ignored, as it's the "filter" bit.
		 */
		वापस (m->status & 0xef80) == BIT(7) ||
		       (m->status & 0xef00) == BIT(8) ||
		       (m->status & 0xeffc) == 0xc;

	शेष:
		वापस false;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mce_is_memory_error);

अटल bool whole_page(काष्ठा mce *m)
अणु
	अगर (!mca_cfg.ser || !(m->status & MCI_STATUS_MISCV))
		वापस true;

	वापस MCI_MISC_ADDR_LSB(m->misc) >= PAGE_SHIFT;
पूर्ण

bool mce_is_correctable(काष्ठा mce *m)
अणु
	अगर (m->cpuvenकरोr == X86_VENDOR_AMD && m->status & MCI_STATUS_DEFERRED)
		वापस false;

	अगर (m->cpuvenकरोr == X86_VENDOR_HYGON && m->status & MCI_STATUS_DEFERRED)
		वापस false;

	अगर (m->status & MCI_STATUS_UC)
		वापस false;

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(mce_is_correctable);

अटल पूर्णांक mce_early_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val,
			      व्योम *data)
अणु
	काष्ठा mce *m = (काष्ठा mce *)data;

	अगर (!m)
		वापस NOTIFY_DONE;

	/* Emit the trace record: */
	trace_mce_record(m);

	set_bit(0, &mce_need_notअगरy);

	mce_notअगरy_irq();

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block early_nb = अणु
	.notअगरier_call	= mce_early_notअगरier,
	.priority	= MCE_PRIO_EARLY,
पूर्ण;

अटल पूर्णांक uc_decode_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val,
			      व्योम *data)
अणु
	काष्ठा mce *mce = (काष्ठा mce *)data;
	अचिन्हित दीर्घ pfn;

	अगर (!mce || !mce_usable_address(mce))
		वापस NOTIFY_DONE;

	अगर (mce->severity != MCE_AO_SEVERITY &&
	    mce->severity != MCE_DEFERRED_SEVERITY)
		वापस NOTIFY_DONE;

	pfn = mce->addr >> PAGE_SHIFT;
	अगर (!memory_failure(pfn, 0)) अणु
		set_mce_nospec(pfn, whole_page(mce));
		mce->kflags |= MCE_HANDLED_UC;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block mce_uc_nb = अणु
	.notअगरier_call	= uc_decode_notअगरier,
	.priority	= MCE_PRIO_UC,
पूर्ण;

अटल पूर्णांक mce_शेष_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val,
				व्योम *data)
अणु
	काष्ठा mce *m = (काष्ठा mce *)data;

	अगर (!m)
		वापस NOTIFY_DONE;

	अगर (mca_cfg.prपूर्णांक_all || !m->kflags)
		__prपूर्णांक_mce(m);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block mce_शेष_nb = अणु
	.notअगरier_call	= mce_शेष_notअगरier,
	/* lowest prio, we want it to run last. */
	.priority	= MCE_PRIO_LOWEST,
पूर्ण;

/*
 * Read ADDR and MISC रेजिस्टरs.
 */
अटल व्योम mce_पढ़ो_aux(काष्ठा mce *m, पूर्णांक i)
अणु
	अगर (m->status & MCI_STATUS_MISCV)
		m->misc = mce_rdmsrl(msr_ops.misc(i));

	अगर (m->status & MCI_STATUS_ADDRV) अणु
		m->addr = mce_rdmsrl(msr_ops.addr(i));

		/*
		 * Mask the reported address by the reported granularity.
		 */
		अगर (mca_cfg.ser && (m->status & MCI_STATUS_MISCV)) अणु
			u8 shअगरt = MCI_MISC_ADDR_LSB(m->misc);
			m->addr >>= shअगरt;
			m->addr <<= shअगरt;
		पूर्ण

		/*
		 * Extract [55:<lsb>] where lsb is the least signअगरicant
		 * *valid* bit of the address bits.
		 */
		अगर (mce_flags.smca) अणु
			u8 lsb = (m->addr >> 56) & 0x3f;

			m->addr &= GENMASK_ULL(55, lsb);
		पूर्ण
	पूर्ण

	अगर (mce_flags.smca) अणु
		m->ipid = mce_rdmsrl(MSR_AMD64_SMCA_MCx_IPID(i));

		अगर (m->status & MCI_STATUS_SYNDV)
			m->synd = mce_rdmsrl(MSR_AMD64_SMCA_MCx_SYND(i));
	पूर्ण
पूर्ण

DEFINE_PER_CPU(अचिन्हित, mce_poll_count);

/*
 * Poll क्रम corrected events or events that happened beक्रमe reset.
 * Those are just logged through /dev/mcelog.
 *
 * This is executed in standard पूर्णांकerrupt context.
 *
 * Note: spec recommends to panic क्रम fatal unसंकेतled
 * errors here. However this would be quite problematic --
 * we would need to reimplement the Monarch handling and
 * it would mess up the exclusion between exception handler
 * and poll handler -- * so we skip this क्रम now.
 * These हालs should not happen anyways, or only when the CPU
 * is alपढ़ोy totally * confused. In this हाल it's likely it will
 * not fully execute the machine check handler either.
 */
bool machine_check_poll(क्रमागत mcp_flags flags, mce_banks_t *b)
अणु
	काष्ठा mce_bank *mce_banks = this_cpu_ptr(mce_banks_array);
	bool error_seen = false;
	काष्ठा mce m;
	पूर्णांक i;

	this_cpu_inc(mce_poll_count);

	mce_gather_info(&m, शून्य);

	अगर (flags & MCP_TIMESTAMP)
		m.tsc = rdtsc();

	क्रम (i = 0; i < this_cpu_पढ़ो(mce_num_banks); i++) अणु
		अगर (!mce_banks[i].ctl || !test_bit(i, *b))
			जारी;

		m.misc = 0;
		m.addr = 0;
		m.bank = i;

		barrier();
		m.status = mce_rdmsrl(msr_ops.status(i));

		/* If this entry is not valid, ignore it */
		अगर (!(m.status & MCI_STATUS_VAL))
			जारी;

		/*
		 * If we are logging everything (at CPU online) or this
		 * is a corrected error, then we must log it.
		 */
		अगर ((flags & MCP_UC) || !(m.status & MCI_STATUS_UC))
			जाओ log_it;

		/*
		 * Newer Intel प्रणालीs that support software error
		 * recovery need to make additional checks. Other
		 * CPUs should skip over uncorrected errors, but log
		 * everything अन्यथा.
		 */
		अगर (!mca_cfg.ser) अणु
			अगर (m.status & MCI_STATUS_UC)
				जारी;
			जाओ log_it;
		पूर्ण

		/* Log "not enabled" (speculative) errors */
		अगर (!(m.status & MCI_STATUS_EN))
			जाओ log_it;

		/*
		 * Log UCNA (SDM: 15.6.3 "UCR Error Classification")
		 * UC == 1 && PCC == 0 && S == 0
		 */
		अगर (!(m.status & MCI_STATUS_PCC) && !(m.status & MCI_STATUS_S))
			जाओ log_it;

		/*
		 * Skip anything अन्यथा. Presumption is that our पढ़ो of this
		 * bank is racing with a machine check. Leave the log alone
		 * क्रम करो_machine_check() to deal with it.
		 */
		जारी;

log_it:
		error_seen = true;

		अगर (flags & MCP_DONTLOG)
			जाओ clear_it;

		mce_पढ़ो_aux(&m, i);
		m.severity = mce_severity(&m, शून्य, mca_cfg.tolerant, शून्य, false);
		/*
		 * Don't get the IP here because it's unlikely to
		 * have anything to करो with the actual error location.
		 */

		अगर (mca_cfg.करोnt_log_ce && !mce_usable_address(&m))
			जाओ clear_it;

		mce_log(&m);

clear_it:
		/*
		 * Clear state क्रम this bank.
		 */
		mce_wrmsrl(msr_ops.status(i), 0);
	पूर्ण

	/*
	 * Don't clear MCG_STATUS here because it's only defined क्रम
	 * exceptions.
	 */

	sync_core();

	वापस error_seen;
पूर्ण
EXPORT_SYMBOL_GPL(machine_check_poll);

/*
 * Do a quick check अगर any of the events requires a panic.
 * This decides अगर we keep the events around or clear them.
 */
अटल पूर्णांक mce_no_way_out(काष्ठा mce *m, अक्षर **msg, अचिन्हित दीर्घ *validp,
			  काष्ठा pt_regs *regs)
अणु
	अक्षर *पंचांगp = *msg;
	पूर्णांक i;

	क्रम (i = 0; i < this_cpu_पढ़ो(mce_num_banks); i++) अणु
		m->status = mce_rdmsrl(msr_ops.status(i));
		अगर (!(m->status & MCI_STATUS_VAL))
			जारी;

		__set_bit(i, validp);
		अगर (quirk_no_way_out)
			quirk_no_way_out(i, m, regs);

		m->bank = i;
		अगर (mce_severity(m, regs, mca_cfg.tolerant, &पंचांगp, true) >= MCE_PANIC_SEVERITY) अणु
			mce_पढ़ो_aux(m, i);
			*msg = पंचांगp;
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Variable to establish order between CPUs जबतक scanning.
 * Each CPU spins initially until executing is equal its number.
 */
अटल atomic_t mce_executing;

/*
 * Defines order of CPUs on entry. First CPU becomes Monarch.
 */
अटल atomic_t mce_callin;

/*
 * Track which CPUs entered the MCA broadcast synchronization and which not in
 * order to prपूर्णांक holकरोuts.
 */
अटल cpumask_t mce_missing_cpus = CPU_MASK_ALL;

/*
 * Check अगर a समयout रुकोing क्रम other CPUs happened.
 */
अटल पूर्णांक mce_समयd_out(u64 *t, स्थिर अक्षर *msg)
अणु
	/*
	 * The others alपढ़ोy did panic क्रम some reason.
	 * Bail out like in a समयout.
	 * rmb() to tell the compiler that प्रणाली_state
	 * might have been modअगरied by someone अन्यथा.
	 */
	rmb();
	अगर (atomic_पढ़ो(&mce_panicked))
		रुको_क्रम_panic();
	अगर (!mca_cfg.monarch_समयout)
		जाओ out;
	अगर ((s64)*t < SPINUNIT) अणु
		अगर (mca_cfg.tolerant <= 1) अणु
			अगर (cpumask_and(&mce_missing_cpus, cpu_online_mask, &mce_missing_cpus))
				pr_emerg("CPUs not responding to MCE broadcast (may include false positives): %*pbl\n",
					 cpumask_pr_args(&mce_missing_cpus));
			mce_panic(msg, शून्य, शून्य);
		पूर्ण
		cpu_missing = 1;
		वापस 1;
	पूर्ण
	*t -= SPINUNIT;
out:
	touch_nmi_watchकरोg();
	वापस 0;
पूर्ण

/*
 * The Monarch's reign.  The Monarch is the CPU who entered
 * the machine check handler first. It रुकोs क्रम the others to
 * उठाओ the exception too and then grades them. When any
 * error is fatal panic. Only then let the others जारी.
 *
 * The other CPUs entering the MCE handler will be controlled by the
 * Monarch. They are called Subjects.
 *
 * This way we prevent any potential data corruption in a unrecoverable हाल
 * and also makes sure always all CPU's errors are examined.
 *
 * Also this detects the हाल of a machine check event coming from outer
 * space (not detected by any CPUs) In this हाल some बाह्यal agent wants
 * us to shut करोwn, so panic too.
 *
 * The other CPUs might still decide to panic अगर the handler happens
 * in a unrecoverable place, but in this हाल the प्रणाली is in a semi-stable
 * state and won't corrupt anything by itself. It's ok to let the others
 * जारी क्रम a bit first.
 *
 * All the spin loops have समयouts; when a समयout happens a CPU
 * typically elects itself to be Monarch.
 */
अटल व्योम mce_reign(व्योम)
अणु
	पूर्णांक cpu;
	काष्ठा mce *m = शून्य;
	पूर्णांक global_worst = 0;
	अक्षर *msg = शून्य;

	/*
	 * This CPU is the Monarch and the other CPUs have run
	 * through their handlers.
	 * Grade the severity of the errors of all the CPUs.
	 */
	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा mce *mपंचांगp = &per_cpu(mces_seen, cpu);

		अगर (mपंचांगp->severity > global_worst) अणु
			global_worst = mपंचांगp->severity;
			m = &per_cpu(mces_seen, cpu);
		पूर्ण
	पूर्ण

	/*
	 * Cannot recover? Panic here then.
	 * This dumps all the mces in the log buffer and stops the
	 * other CPUs.
	 */
	अगर (m && global_worst >= MCE_PANIC_SEVERITY && mca_cfg.tolerant < 3) अणु
		/* call mce_severity() to get "msg" क्रम panic */
		mce_severity(m, शून्य, mca_cfg.tolerant, &msg, true);
		mce_panic("Fatal machine check", m, msg);
	पूर्ण

	/*
	 * For UC somewhere we let the CPU who detects it handle it.
	 * Also must let जारी the others, otherwise the handling
	 * CPU could deadlock on a lock.
	 */

	/*
	 * No machine check event found. Must be some बाह्यal
	 * source or one CPU is hung. Panic.
	 */
	अगर (global_worst <= MCE_KEEP_SEVERITY && mca_cfg.tolerant < 3)
		mce_panic("Fatal machine check from unknown source", शून्य, शून्य);

	/*
	 * Now clear all the mces_seen so that they करोn't reappear on
	 * the next mce.
	 */
	क्रम_each_possible_cpu(cpu)
		स_रखो(&per_cpu(mces_seen, cpu), 0, माप(काष्ठा mce));
पूर्ण

अटल atomic_t global_nwo;

/*
 * Start of Monarch synchronization. This रुकोs until all CPUs have
 * entered the exception handler and then determines अगर any of them
 * saw a fatal event that requires panic. Then it executes them
 * in the entry order.
 * TBD द्विगुन check parallel CPU hotunplug
 */
अटल पूर्णांक mce_start(पूर्णांक *no_way_out)
अणु
	पूर्णांक order;
	पूर्णांक cpus = num_online_cpus();
	u64 समयout = (u64)mca_cfg.monarch_समयout * NSEC_PER_USEC;

	अगर (!समयout)
		वापस -1;

	atomic_add(*no_way_out, &global_nwo);
	/*
	 * Rely on the implied barrier below, such that global_nwo
	 * is updated beक्रमe mce_callin.
	 */
	order = atomic_inc_वापस(&mce_callin);
	cpumask_clear_cpu(smp_processor_id(), &mce_missing_cpus);

	/*
	 * Wait क्रम everyone.
	 */
	जबतक (atomic_पढ़ो(&mce_callin) != cpus) अणु
		अगर (mce_समयd_out(&समयout,
				  "Timeout: Not all CPUs entered broadcast exception handler")) अणु
			atomic_set(&global_nwo, 0);
			वापस -1;
		पूर्ण
		ndelay(SPINUNIT);
	पूर्ण

	/*
	 * mce_callin should be पढ़ो beक्रमe global_nwo
	 */
	smp_rmb();

	अगर (order == 1) अणु
		/*
		 * Monarch: Starts executing now, the others रुको.
		 */
		atomic_set(&mce_executing, 1);
	पूर्ण अन्यथा अणु
		/*
		 * Subject: Now start the scanning loop one by one in
		 * the original callin order.
		 * This way when there are any shared banks it will be
		 * only seen by one CPU beक्रमe cleared, aव्योमing duplicates.
		 */
		जबतक (atomic_पढ़ो(&mce_executing) < order) अणु
			अगर (mce_समयd_out(&समयout,
					  "Timeout: Subject CPUs unable to finish machine check processing")) अणु
				atomic_set(&global_nwo, 0);
				वापस -1;
			पूर्ण
			ndelay(SPINUNIT);
		पूर्ण
	पूर्ण

	/*
	 * Cache the global no_way_out state.
	 */
	*no_way_out = atomic_पढ़ो(&global_nwo);

	वापस order;
पूर्ण

/*
 * Synchronize between CPUs after मुख्य scanning loop.
 * This invokes the bulk of the Monarch processing.
 */
अटल पूर्णांक mce_end(पूर्णांक order)
अणु
	पूर्णांक ret = -1;
	u64 समयout = (u64)mca_cfg.monarch_समयout * NSEC_PER_USEC;

	अगर (!समयout)
		जाओ reset;
	अगर (order < 0)
		जाओ reset;

	/*
	 * Allow others to run.
	 */
	atomic_inc(&mce_executing);

	अगर (order == 1) अणु
		/* CHECKME: Can this race with a parallel hotplug? */
		पूर्णांक cpus = num_online_cpus();

		/*
		 * Monarch: Wait क्रम everyone to go through their scanning
		 * loops.
		 */
		जबतक (atomic_पढ़ो(&mce_executing) <= cpus) अणु
			अगर (mce_समयd_out(&समयout,
					  "Timeout: Monarch CPU unable to finish machine check processing"))
				जाओ reset;
			ndelay(SPINUNIT);
		पूर्ण

		mce_reign();
		barrier();
		ret = 0;
	पूर्ण अन्यथा अणु
		/*
		 * Subject: Wait क्रम Monarch to finish.
		 */
		जबतक (atomic_पढ़ो(&mce_executing) != 0) अणु
			अगर (mce_समयd_out(&समयout,
					  "Timeout: Monarch CPU did not finish machine check processing"))
				जाओ reset;
			ndelay(SPINUNIT);
		पूर्ण

		/*
		 * Don't reset anything. That's करोne by the Monarch.
		 */
		वापस 0;
	पूर्ण

	/*
	 * Reset all global state.
	 */
reset:
	atomic_set(&global_nwo, 0);
	atomic_set(&mce_callin, 0);
	cpumask_setall(&mce_missing_cpus);
	barrier();

	/*
	 * Let others run again.
	 */
	atomic_set(&mce_executing, 0);
	वापस ret;
पूर्ण

अटल व्योम mce_clear_state(अचिन्हित दीर्घ *toclear)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < this_cpu_पढ़ो(mce_num_banks); i++) अणु
		अगर (test_bit(i, toclear))
			mce_wrmsrl(msr_ops.status(i), 0);
	पूर्ण
पूर्ण

/*
 * Cases where we aव्योम rendezvous handler समयout:
 * 1) If this CPU is offline.
 *
 * 2) If crashing_cpu was set, e.g. we're entering kdump and we need to
 *  skip those CPUs which reमुख्य looping in the 1st kernel - see
 *  crash_nmi_callback().
 *
 * Note: there still is a small winकरोw between kexec-ing and the new,
 * kdump kernel establishing a new #MC handler where a broadcasted MCE
 * might not get handled properly.
 */
अटल noinstr bool mce_check_crashing_cpu(व्योम)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	अगर (arch_cpu_is_offline(cpu) ||
	    (crashing_cpu != -1 && crashing_cpu != cpu)) अणु
		u64 mcgstatus;

		mcgstatus = __rdmsr(MSR_IA32_MCG_STATUS);

		अगर (boot_cpu_data.x86_venकरोr == X86_VENDOR_ZHAOXIN) अणु
			अगर (mcgstatus & MCG_STATUS_LMCES)
				वापस false;
		पूर्ण

		अगर (mcgstatus & MCG_STATUS_RIPV) अणु
			__wrmsr(MSR_IA32_MCG_STATUS, 0, 0);
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम __mc_scan_banks(काष्ठा mce *m, काष्ठा pt_regs *regs, काष्ठा mce *final,
			    अचिन्हित दीर्घ *toclear, अचिन्हित दीर्घ *valid_banks,
			    पूर्णांक no_way_out, पूर्णांक *worst)
अणु
	काष्ठा mce_bank *mce_banks = this_cpu_ptr(mce_banks_array);
	काष्ठा mca_config *cfg = &mca_cfg;
	पूर्णांक severity, i;

	क्रम (i = 0; i < this_cpu_पढ़ो(mce_num_banks); i++) अणु
		__clear_bit(i, toclear);
		अगर (!test_bit(i, valid_banks))
			जारी;

		अगर (!mce_banks[i].ctl)
			जारी;

		m->misc = 0;
		m->addr = 0;
		m->bank = i;

		m->status = mce_rdmsrl(msr_ops.status(i));
		अगर (!(m->status & MCI_STATUS_VAL))
			जारी;

		/*
		 * Corrected or non-संकेतed errors are handled by
		 * machine_check_poll(). Leave them alone, unless this panics.
		 */
		अगर (!(m->status & (cfg->ser ? MCI_STATUS_S : MCI_STATUS_UC)) &&
			!no_way_out)
			जारी;

		/* Set taपूर्णांक even when machine check was not enabled. */
		add_taपूर्णांक(TAINT_MACHINE_CHECK, LOCKDEP_NOW_UNRELIABLE);

		severity = mce_severity(m, regs, cfg->tolerant, शून्य, true);

		/*
		 * When machine check was क्रम corrected/deferred handler करोn't
		 * touch, unless we're panicking.
		 */
		अगर ((severity == MCE_KEEP_SEVERITY ||
		     severity == MCE_UCNA_SEVERITY) && !no_way_out)
			जारी;

		__set_bit(i, toclear);

		/* Machine check event was not enabled. Clear, but ignore. */
		अगर (severity == MCE_NO_SEVERITY)
			जारी;

		mce_पढ़ो_aux(m, i);

		/* assuming valid severity level != 0 */
		m->severity = severity;

		mce_log(m);

		अगर (severity > *worst) अणु
			*final = *m;
			*worst = severity;
		पूर्ण
	पूर्ण

	/* mce_clear_state will clear *final, save locally क्रम use later */
	*m = *final;
पूर्ण

अटल व्योम समाप्त_me_now(काष्ठा callback_head *ch)
अणु
	क्रमce_sig(SIGBUS);
पूर्ण

अटल व्योम समाप्त_me_maybe(काष्ठा callback_head *cb)
अणु
	काष्ठा task_काष्ठा *p = container_of(cb, काष्ठा task_काष्ठा, mce_समाप्त_me);
	पूर्णांक flags = MF_ACTION_REQUIRED;

	pr_err("Uncorrected hardware memory error in user-access at %llx", p->mce_addr);

	अगर (!p->mce_ripv)
		flags |= MF_MUST_KILL;

	अगर (!memory_failure(p->mce_addr >> PAGE_SHIFT, flags) &&
	    !(p->mce_kflags & MCE_IN_KERNEL_COPYIN)) अणु
		set_mce_nospec(p->mce_addr >> PAGE_SHIFT, p->mce_whole_page);
		sync_core();
		वापस;
	पूर्ण

	अगर (p->mce_vaddr != (व्योम __user *)-1l) अणु
		क्रमce_sig_mceerr(BUS_MCEERR_AR, p->mce_vaddr, PAGE_SHIFT);
	पूर्ण अन्यथा अणु
		pr_err("Memory error not recovered");
		समाप्त_me_now(cb);
	पूर्ण
पूर्ण

अटल व्योम queue_task_work(काष्ठा mce *m, पूर्णांक समाप्त_current_task)
अणु
	current->mce_addr = m->addr;
	current->mce_kflags = m->kflags;
	current->mce_ripv = !!(m->mcgstatus & MCG_STATUS_RIPV);
	current->mce_whole_page = whole_page(m);

	अगर (समाप्त_current_task)
		current->mce_समाप्त_me.func = समाप्त_me_now;
	अन्यथा
		current->mce_समाप्त_me.func = समाप्त_me_maybe;

	task_work_add(current, &current->mce_समाप्त_me, TWA_RESUME);
पूर्ण

/*
 * The actual machine check handler. This only handles real
 * exceptions when something got corrupted coming in through पूर्णांक 18.
 *
 * This is executed in NMI context not subject to normal locking rules. This
 * implies that most kernel services cannot be safely used. Don't even
 * think about putting a prपूर्णांकk in there!
 *
 * On Intel प्रणालीs this is entered on all CPUs in parallel through
 * MCE broadcast. However some CPUs might be broken beyond repair,
 * so be always careful when synchronizing with others.
 *
 * Tracing and kprobes are disabled: अगर we पूर्णांकerrupted a kernel context
 * with IF=1, we need to minimize stack usage.  There are also recursion
 * issues: अगर the machine check was due to a failure of the memory
 * backing the user stack, tracing that पढ़ोs the user stack will cause
 * potentially infinite recursion.
 */
noinstr व्योम करो_machine_check(काष्ठा pt_regs *regs)
अणु
	DECLARE_BITMAP(valid_banks, MAX_NR_BANKS);
	DECLARE_BITMAP(toclear, MAX_NR_BANKS);
	काष्ठा mca_config *cfg = &mca_cfg;
	काष्ठा mce m, *final;
	अक्षर *msg = शून्य;
	पूर्णांक worst = 0;

	/*
	 * Establish sequential order between the CPUs entering the machine
	 * check handler.
	 */
	पूर्णांक order = -1;

	/*
	 * If no_way_out माला_लो set, there is no safe way to recover from this
	 * MCE.  If mca_cfg.tolerant is cranked up, we'll try anyway.
	 */
	पूर्णांक no_way_out = 0;

	/*
	 * If समाप्त_current_task is not set, there might be a way to recover from this
	 * error.
	 */
	पूर्णांक समाप्त_current_task = 0;

	/*
	 * MCEs are always local on AMD. Same is determined by MCG_STATUS_LMCES
	 * on Intel.
	 */
	पूर्णांक lmce = 1;

	this_cpu_inc(mce_exception_count);

	mce_gather_info(&m, regs);
	m.tsc = rdtsc();

	final = this_cpu_ptr(&mces_seen);
	*final = m;

	स_रखो(valid_banks, 0, माप(valid_banks));
	no_way_out = mce_no_way_out(&m, &msg, valid_banks, regs);

	barrier();

	/*
	 * When no restart IP might need to समाप्त or panic.
	 * Assume the worst क्रम now, but अगर we find the
	 * severity is MCE_AR_SEVERITY we have other options.
	 */
	अगर (!(m.mcgstatus & MCG_STATUS_RIPV))
		समाप्त_current_task = (cfg->tolerant == 3) ? 0 : 1;
	/*
	 * Check अगर this MCE is संकेतed to only this logical processor,
	 * on Intel, Zhaoxin only.
	 */
	अगर (m.cpuvenकरोr == X86_VENDOR_INTEL ||
	    m.cpuvenकरोr == X86_VENDOR_ZHAOXIN)
		lmce = m.mcgstatus & MCG_STATUS_LMCES;

	/*
	 * Local machine check may alपढ़ोy know that we have to panic.
	 * Broadcast machine check begins rendezvous in mce_start()
	 * Go through all banks in exclusion of the other CPUs. This way we
	 * करोn't report duplicated events on shared banks because the first one
	 * to see it will clear it.
	 */
	अगर (lmce) अणु
		अगर (no_way_out && cfg->tolerant < 3)
			mce_panic("Fatal local machine check", &m, msg);
	पूर्ण अन्यथा अणु
		order = mce_start(&no_way_out);
	पूर्ण

	__mc_scan_banks(&m, regs, final, toclear, valid_banks, no_way_out, &worst);

	अगर (!no_way_out)
		mce_clear_state(toclear);

	/*
	 * Do most of the synchronization with other CPUs.
	 * When there's any problem use only local no_way_out state.
	 */
	अगर (!lmce) अणु
		अगर (mce_end(order) < 0) अणु
			अगर (!no_way_out)
				no_way_out = worst >= MCE_PANIC_SEVERITY;

			अगर (no_way_out && cfg->tolerant < 3)
				mce_panic("Fatal machine check on current CPU", &m, msg);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * If there was a fatal machine check we should have
		 * alपढ़ोy called mce_panic earlier in this function.
		 * Since we re-पढ़ो the banks, we might have found
		 * something new. Check again to see अगर we found a
		 * fatal error. We call "mce_severity()" again to
		 * make sure we have the right "msg".
		 */
		अगर (worst >= MCE_PANIC_SEVERITY && mca_cfg.tolerant < 3) अणु
			mce_severity(&m, regs, cfg->tolerant, &msg, true);
			mce_panic("Local fatal machine check!", &m, msg);
		पूर्ण
	पूर्ण

	अगर (worst != MCE_AR_SEVERITY && !समाप्त_current_task)
		जाओ out;

	/* Fault was in user mode and we need to take some action */
	अगर ((m.cs & 3) == 3) अणु
		/* If this triggers there is no way to recover. Die hard. */
		BUG_ON(!on_thपढ़ो_stack() || !user_mode(regs));

		queue_task_work(&m, समाप्त_current_task);

	पूर्ण अन्यथा अणु
		/*
		 * Handle an MCE which has happened in kernel space but from
		 * which the kernel can recover: ex_has_fault_handler() has
		 * alपढ़ोy verअगरied that the rIP at which the error happened is
		 * a rIP from which the kernel can recover (by jumping to
		 * recovery code specअगरied in _ASM_EXTABLE_FAULT()) and the
		 * corresponding exception handler which would करो that is the
		 * proper one.
		 */
		अगर (m.kflags & MCE_IN_KERNEL_RECOV) अणु
			अगर (!fixup_exception(regs, X86_TRAP_MC, 0, 0))
				mce_panic("Failed kernel mode recovery", &m, msg);
		पूर्ण

		अगर (m.kflags & MCE_IN_KERNEL_COPYIN)
			queue_task_work(&m, समाप्त_current_task);
	पूर्ण
out:
	mce_wrmsrl(MSR_IA32_MCG_STATUS, 0);
पूर्ण
EXPORT_SYMBOL_GPL(करो_machine_check);

#अगर_अघोषित CONFIG_MEMORY_FAILURE
पूर्णांक memory_failure(अचिन्हित दीर्घ pfn, पूर्णांक flags)
अणु
	/* mce_severity() should not hand us an ACTION_REQUIRED error */
	BUG_ON(flags & MF_ACTION_REQUIRED);
	pr_err("Uncorrected memory error in page 0x%lx ignored\n"
	       "Rebuild kernel with CONFIG_MEMORY_FAILURE=y for smarter handling\n",
	       pfn);

	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * Periodic polling समयr क्रम "silent" machine check errors.  If the
 * poller finds an MCE, poll 2x faster.  When the poller finds no more
 * errors, poll 2x slower (up to check_पूर्णांकerval seconds).
 */
अटल अचिन्हित दीर्घ check_पूर्णांकerval = INITIAL_CHECK_INTERVAL;

अटल DEFINE_PER_CPU(अचिन्हित दीर्घ, mce_next_पूर्णांकerval); /* in jअगरfies */
अटल DEFINE_PER_CPU(काष्ठा समयr_list, mce_समयr);

अटल अचिन्हित दीर्घ mce_adjust_समयr_शेष(अचिन्हित दीर्घ पूर्णांकerval)
अणु
	वापस पूर्णांकerval;
पूर्ण

अटल अचिन्हित दीर्घ (*mce_adjust_समयr)(अचिन्हित दीर्घ पूर्णांकerval) = mce_adjust_समयr_शेष;

अटल व्योम __start_समयr(काष्ठा समयr_list *t, अचिन्हित दीर्घ पूर्णांकerval)
अणु
	अचिन्हित दीर्घ when = jअगरfies + पूर्णांकerval;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	अगर (!समयr_pending(t) || समय_beक्रमe(when, t->expires))
		mod_समयr(t, round_jअगरfies(when));

	local_irq_restore(flags);
पूर्ण

अटल व्योम mce_समयr_fn(काष्ठा समयr_list *t)
अणु
	काष्ठा समयr_list *cpu_t = this_cpu_ptr(&mce_समयr);
	अचिन्हित दीर्घ iv;

	WARN_ON(cpu_t != t);

	iv = __this_cpu_पढ़ो(mce_next_पूर्णांकerval);

	अगर (mce_available(this_cpu_ptr(&cpu_info))) अणु
		machine_check_poll(0, this_cpu_ptr(&mce_poll_banks));

		अगर (mce_पूर्णांकel_cmci_poll()) अणु
			iv = mce_adjust_समयr(iv);
			जाओ करोne;
		पूर्ण
	पूर्ण

	/*
	 * Alert userspace अगर needed. If we logged an MCE, reduce the polling
	 * पूर्णांकerval, otherwise increase the polling पूर्णांकerval.
	 */
	अगर (mce_notअगरy_irq())
		iv = max(iv / 2, (अचिन्हित दीर्घ) HZ/100);
	अन्यथा
		iv = min(iv * 2, round_jअगरfies_relative(check_पूर्णांकerval * HZ));

करोne:
	__this_cpu_ग_लिखो(mce_next_पूर्णांकerval, iv);
	__start_समयr(t, iv);
पूर्ण

/*
 * Ensure that the समयr is firing in @पूर्णांकerval from now.
 */
व्योम mce_समयr_kick(अचिन्हित दीर्घ पूर्णांकerval)
अणु
	काष्ठा समयr_list *t = this_cpu_ptr(&mce_समयr);
	अचिन्हित दीर्घ iv = __this_cpu_पढ़ो(mce_next_पूर्णांकerval);

	__start_समयr(t, पूर्णांकerval);

	अगर (पूर्णांकerval < iv)
		__this_cpu_ग_लिखो(mce_next_पूर्णांकerval, पूर्णांकerval);
पूर्ण

/* Must not be called in IRQ context where del_समयr_sync() can deadlock */
अटल व्योम mce_समयr_delete_all(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_online_cpu(cpu)
		del_समयr_sync(&per_cpu(mce_समयr, cpu));
पूर्ण

/*
 * Notअगरy the user(s) about new machine check events.
 * Can be called from पूर्णांकerrupt context, but not from machine check/NMI
 * context.
 */
पूर्णांक mce_notअगरy_irq(व्योम)
अणु
	/* Not more than two messages every minute */
	अटल DEFINE_RATELIMIT_STATE(ratelimit, 60*HZ, 2);

	अगर (test_and_clear_bit(0, &mce_need_notअगरy)) अणु
		mce_work_trigger();

		अगर (__ratelimit(&ratelimit))
			pr_info(HW_ERR "Machine check events logged\n");

		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mce_notअगरy_irq);

अटल व्योम __mcheck_cpu_mce_banks_init(व्योम)
अणु
	काष्ठा mce_bank *mce_banks = this_cpu_ptr(mce_banks_array);
	u8 n_banks = this_cpu_पढ़ो(mce_num_banks);
	पूर्णांक i;

	क्रम (i = 0; i < n_banks; i++) अणु
		काष्ठा mce_bank *b = &mce_banks[i];

		/*
		 * Init them all, __mcheck_cpu_apply_quirks() is going to apply
		 * the required venकरोr quirks beक्रमe
		 * __mcheck_cpu_init_clear_banks() करोes the final bank setup.
		 */
		b->ctl = -1ULL;
		b->init = true;
	पूर्ण
पूर्ण

/*
 * Initialize Machine Checks क्रम a CPU.
 */
अटल व्योम __mcheck_cpu_cap_init(व्योम)
अणु
	u64 cap;
	u8 b;

	rdmsrl(MSR_IA32_MCG_CAP, cap);

	b = cap & MCG_BANKCNT_MASK;

	अगर (b > MAX_NR_BANKS) अणु
		pr_warn("CPU%d: Using only %u machine check banks out of %u\n",
			smp_processor_id(), MAX_NR_BANKS, b);
		b = MAX_NR_BANKS;
	पूर्ण

	this_cpu_ग_लिखो(mce_num_banks, b);

	__mcheck_cpu_mce_banks_init();

	/* Use accurate RIP reporting अगर available. */
	अगर ((cap & MCG_EXT_P) && MCG_EXT_CNT(cap) >= 9)
		mca_cfg.rip_msr = MSR_IA32_MCG_EIP;

	अगर (cap & MCG_SER_P)
		mca_cfg.ser = 1;
पूर्ण

अटल व्योम __mcheck_cpu_init_generic(व्योम)
अणु
	क्रमागत mcp_flags m_fl = 0;
	mce_banks_t all_banks;
	u64 cap;

	अगर (!mca_cfg.bootlog)
		m_fl = MCP_DONTLOG;

	/*
	 * Log the machine checks left over from the previous reset.
	 */
	biपंचांगap_fill(all_banks, MAX_NR_BANKS);
	machine_check_poll(MCP_UC | m_fl, &all_banks);

	cr4_set_bits(X86_CR4_MCE);

	rdmsrl(MSR_IA32_MCG_CAP, cap);
	अगर (cap & MCG_CTL_P)
		wrmsr(MSR_IA32_MCG_CTL, 0xffffffff, 0xffffffff);
पूर्ण

अटल व्योम __mcheck_cpu_init_clear_banks(व्योम)
अणु
	काष्ठा mce_bank *mce_banks = this_cpu_ptr(mce_banks_array);
	पूर्णांक i;

	क्रम (i = 0; i < this_cpu_पढ़ो(mce_num_banks); i++) अणु
		काष्ठा mce_bank *b = &mce_banks[i];

		अगर (!b->init)
			जारी;
		wrmsrl(msr_ops.ctl(i), b->ctl);
		wrmsrl(msr_ops.status(i), 0);
	पूर्ण
पूर्ण

/*
 * Do a final check to see अगर there are any unused/RAZ banks.
 *
 * This must be करोne after the banks have been initialized and any quirks have
 * been applied.
 *
 * Do not call this from any user-initiated flows, e.g. CPU hotplug or sysfs.
 * Otherwise, a user who disables a bank will not be able to re-enable it
 * without a प्रणाली reboot.
 */
अटल व्योम __mcheck_cpu_check_banks(व्योम)
अणु
	काष्ठा mce_bank *mce_banks = this_cpu_ptr(mce_banks_array);
	u64 msrval;
	पूर्णांक i;

	क्रम (i = 0; i < this_cpu_पढ़ो(mce_num_banks); i++) अणु
		काष्ठा mce_bank *b = &mce_banks[i];

		अगर (!b->init)
			जारी;

		rdmsrl(msr_ops.ctl(i), msrval);
		b->init = !!msrval;
	पूर्ण
पूर्ण

/*
 * During IFU recovery Sandy Bridge -EP4S processors set the RIPV and
 * EIPV bits in MCG_STATUS to zero on the affected logical processor (SDM
 * Vol 3B Table 15-20). But this confuses both the code that determines
 * whether the machine check occurred in kernel or user mode, and also
 * the severity assessment code. Pretend that EIPV was set, and take the
 * ip/cs values from the pt_regs that mce_gather_info() ignored earlier.
 */
अटल व्योम quirk_sandybridge_अगरu(पूर्णांक bank, काष्ठा mce *m, काष्ठा pt_regs *regs)
अणु
	अगर (bank != 0)
		वापस;
	अगर ((m->mcgstatus & (MCG_STATUS_EIPV|MCG_STATUS_RIPV)) != 0)
		वापस;
	अगर ((m->status & (MCI_STATUS_OVER|MCI_STATUS_UC|
		          MCI_STATUS_EN|MCI_STATUS_MISCV|MCI_STATUS_ADDRV|
			  MCI_STATUS_PCC|MCI_STATUS_S|MCI_STATUS_AR|
			  MCACOD)) !=
			 (MCI_STATUS_UC|MCI_STATUS_EN|
			  MCI_STATUS_MISCV|MCI_STATUS_ADDRV|MCI_STATUS_S|
			  MCI_STATUS_AR|MCACOD_INSTR))
		वापस;

	m->mcgstatus |= MCG_STATUS_EIPV;
	m->ip = regs->ip;
	m->cs = regs->cs;
पूर्ण

/* Add per CPU specअगरic workarounds here */
अटल पूर्णांक __mcheck_cpu_apply_quirks(काष्ठा cpuinfo_x86 *c)
अणु
	काष्ठा mce_bank *mce_banks = this_cpu_ptr(mce_banks_array);
	काष्ठा mca_config *cfg = &mca_cfg;

	अगर (c->x86_venकरोr == X86_VENDOR_UNKNOWN) अणु
		pr_info("unknown CPU type - not enabling MCE support\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* This should be disabled by the BIOS, but isn't always */
	अगर (c->x86_venकरोr == X86_VENDOR_AMD) अणु
		अगर (c->x86 == 15 && this_cpu_पढ़ो(mce_num_banks) > 4) अणु
			/*
			 * disable GART TBL walk error reporting, which
			 * trips off incorrectly with the IOMMU & 3ware
			 * & Cerberus:
			 */
			clear_bit(10, (अचिन्हित दीर्घ *)&mce_banks[4].ctl);
		पूर्ण
		अगर (c->x86 < 0x11 && cfg->bootlog < 0) अणु
			/*
			 * Lots of broken BIOS around that करोn't clear them
			 * by शेष and leave crap in there. Don't log:
			 */
			cfg->bootlog = 0;
		पूर्ण
		/*
		 * Various K7s with broken bank 0 around. Always disable
		 * by शेष.
		 */
		अगर (c->x86 == 6 && this_cpu_पढ़ो(mce_num_banks) > 0)
			mce_banks[0].ctl = 0;

		/*
		 * overflow_recov is supported क्रम F15h Models 00h-0fh
		 * even though we करोn't have a CPUID bit क्रम it.
		 */
		अगर (c->x86 == 0x15 && c->x86_model <= 0xf)
			mce_flags.overflow_recov = 1;

	पूर्ण

	अगर (c->x86_venकरोr == X86_VENDOR_INTEL) अणु
		/*
		 * SDM करोcuments that on family 6 bank 0 should not be written
		 * because it aliases to another special BIOS controlled
		 * रेजिस्टर.
		 * But it's not aliased anymore on model 0x1a+
		 * Don't ignore bank 0 completely because there could be a
		 * valid event later, merely करोn't ग_लिखो CTL0.
		 */

		अगर (c->x86 == 6 && c->x86_model < 0x1A && this_cpu_पढ़ो(mce_num_banks) > 0)
			mce_banks[0].init = false;

		/*
		 * All newer Intel प्रणालीs support MCE broadcasting. Enable
		 * synchronization with a one second समयout.
		 */
		अगर ((c->x86 > 6 || (c->x86 == 6 && c->x86_model >= 0xe)) &&
			cfg->monarch_समयout < 0)
			cfg->monarch_समयout = USEC_PER_SEC;

		/*
		 * There are also broken BIOSes on some Pentium M and
		 * earlier प्रणालीs:
		 */
		अगर (c->x86 == 6 && c->x86_model <= 13 && cfg->bootlog < 0)
			cfg->bootlog = 0;

		अगर (c->x86 == 6 && c->x86_model == 45)
			quirk_no_way_out = quirk_sandybridge_अगरu;
	पूर्ण

	अगर (c->x86_venकरोr == X86_VENDOR_ZHAOXIN) अणु
		/*
		 * All newer Zhaoxin CPUs support MCE broadcasting. Enable
		 * synchronization with a one second समयout.
		 */
		अगर (c->x86 > 6 || (c->x86_model == 0x19 || c->x86_model == 0x1f)) अणु
			अगर (cfg->monarch_समयout < 0)
				cfg->monarch_समयout = USEC_PER_SEC;
		पूर्ण
	पूर्ण

	अगर (cfg->monarch_समयout < 0)
		cfg->monarch_समयout = 0;
	अगर (cfg->bootlog != 0)
		cfg->panic_समयout = 30;

	वापस 0;
पूर्ण

अटल पूर्णांक __mcheck_cpu_ancient_init(काष्ठा cpuinfo_x86 *c)
अणु
	अगर (c->x86 != 5)
		वापस 0;

	चयन (c->x86_venकरोr) अणु
	हाल X86_VENDOR_INTEL:
		पूर्णांकel_p5_mcheck_init(c);
		वापस 1;
	हाल X86_VENDOR_CENTAUR:
		winchip_mcheck_init(c);
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Init basic CPU features needed क्रम early decoding of MCEs.
 */
अटल व्योम __mcheck_cpu_init_early(काष्ठा cpuinfo_x86 *c)
अणु
	अगर (c->x86_venकरोr == X86_VENDOR_AMD || c->x86_venकरोr == X86_VENDOR_HYGON) अणु
		mce_flags.overflow_recov = !!cpu_has(c, X86_FEATURE_OVERFLOW_RECOV);
		mce_flags.succor	 = !!cpu_has(c, X86_FEATURE_SUCCOR);
		mce_flags.smca		 = !!cpu_has(c, X86_FEATURE_SMCA);
		mce_flags.amd_threshold	 = 1;

		अगर (mce_flags.smca) अणु
			msr_ops.ctl	= smca_ctl_reg;
			msr_ops.status	= smca_status_reg;
			msr_ops.addr	= smca_addr_reg;
			msr_ops.misc	= smca_misc_reg;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mce_centaur_feature_init(काष्ठा cpuinfo_x86 *c)
अणु
	काष्ठा mca_config *cfg = &mca_cfg;

	 /*
	  * All newer Centaur CPUs support MCE broadcasting. Enable
	  * synchronization with a one second समयout.
	  */
	अगर ((c->x86 == 6 && c->x86_model == 0xf && c->x86_stepping >= 0xe) ||
	     c->x86 > 6) अणु
		अगर (cfg->monarch_समयout < 0)
			cfg->monarch_समयout = USEC_PER_SEC;
	पूर्ण
पूर्ण

अटल व्योम mce_zhaoxin_feature_init(काष्ठा cpuinfo_x86 *c)
अणु
	काष्ठा mce_bank *mce_banks = this_cpu_ptr(mce_banks_array);

	/*
	 * These CPUs have MCA bank 8 which reports only one error type called
	 * SVAD (System View Address Decoder). The reporting of that error is
	 * controlled by IA32_MC8.CTL.0.
	 *
	 * If enabled, prefetching on these CPUs will cause SVAD MCE when
	 * भव machines start and result in a प्रणाली  panic. Always disable
	 * bank 8 SVAD error by शेष.
	 */
	अगर ((c->x86 == 7 && c->x86_model == 0x1b) ||
	    (c->x86_model == 0x19 || c->x86_model == 0x1f)) अणु
		अगर (this_cpu_पढ़ो(mce_num_banks) > 8)
			mce_banks[8].ctl = 0;
	पूर्ण

	पूर्णांकel_init_cmci();
	पूर्णांकel_init_lmce();
	mce_adjust_समयr = cmci_पूर्णांकel_adjust_समयr;
पूर्ण

अटल व्योम mce_zhaoxin_feature_clear(काष्ठा cpuinfo_x86 *c)
अणु
	पूर्णांकel_clear_lmce();
पूर्ण

अटल व्योम __mcheck_cpu_init_venकरोr(काष्ठा cpuinfo_x86 *c)
अणु
	चयन (c->x86_venकरोr) अणु
	हाल X86_VENDOR_INTEL:
		mce_पूर्णांकel_feature_init(c);
		mce_adjust_समयr = cmci_पूर्णांकel_adjust_समयr;
		अवरोध;

	हाल X86_VENDOR_AMD: अणु
		mce_amd_feature_init(c);
		अवरोध;
		पूर्ण

	हाल X86_VENDOR_HYGON:
		mce_hygon_feature_init(c);
		अवरोध;

	हाल X86_VENDOR_CENTAUR:
		mce_centaur_feature_init(c);
		अवरोध;

	हाल X86_VENDOR_ZHAOXIN:
		mce_zhaoxin_feature_init(c);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम __mcheck_cpu_clear_venकरोr(काष्ठा cpuinfo_x86 *c)
अणु
	चयन (c->x86_venकरोr) अणु
	हाल X86_VENDOR_INTEL:
		mce_पूर्णांकel_feature_clear(c);
		अवरोध;

	हाल X86_VENDOR_ZHAOXIN:
		mce_zhaoxin_feature_clear(c);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mce_start_समयr(काष्ठा समयr_list *t)
अणु
	अचिन्हित दीर्घ iv = check_पूर्णांकerval * HZ;

	अगर (mca_cfg.ignore_ce || !iv)
		वापस;

	this_cpu_ग_लिखो(mce_next_पूर्णांकerval, iv);
	__start_समयr(t, iv);
पूर्ण

अटल व्योम __mcheck_cpu_setup_समयr(व्योम)
अणु
	काष्ठा समयr_list *t = this_cpu_ptr(&mce_समयr);

	समयr_setup(t, mce_समयr_fn, TIMER_PINNED);
पूर्ण

अटल व्योम __mcheck_cpu_init_समयr(व्योम)
अणु
	काष्ठा समयr_list *t = this_cpu_ptr(&mce_समयr);

	समयr_setup(t, mce_समयr_fn, TIMER_PINNED);
	mce_start_समयr(t);
पूर्ण

bool filter_mce(काष्ठा mce *m)
अणु
	अगर (boot_cpu_data.x86_venकरोr == X86_VENDOR_AMD)
		वापस amd_filter_mce(m);
	अगर (boot_cpu_data.x86_venकरोr == X86_VENDOR_INTEL)
		वापस पूर्णांकel_filter_mce(m);

	वापस false;
पूर्ण

/* Handle unconfigured पूर्णांक18 (should never happen) */
अटल noinstr व्योम unexpected_machine_check(काष्ठा pt_regs *regs)
अणु
	instrumentation_begin();
	pr_err("CPU#%d: Unexpected int18 (Machine Check)\n",
	       smp_processor_id());
	instrumentation_end();
पूर्ण

/* Call the installed machine check handler क्रम this CPU setup. */
व्योम (*machine_check_vector)(काष्ठा pt_regs *) = unexpected_machine_check;

अटल __always_अंतरभूत व्योम exc_machine_check_kernel(काष्ठा pt_regs *regs)
अणु
	irqentry_state_t irq_state;

	WARN_ON_ONCE(user_mode(regs));

	/*
	 * Only required when from kernel mode. See
	 * mce_check_crashing_cpu() क्रम details.
	 */
	अगर (machine_check_vector == करो_machine_check &&
	    mce_check_crashing_cpu())
		वापस;

	irq_state = irqentry_nmi_enter(regs);
	/*
	 * The call tarमाला_लो are marked noinstr, but objtool can't figure
	 * that out because it's an indirect call. Annotate it.
	 */
	instrumentation_begin();

	machine_check_vector(regs);

	instrumentation_end();
	irqentry_nmi_निकास(regs, irq_state);
पूर्ण

अटल __always_अंतरभूत व्योम exc_machine_check_user(काष्ठा pt_regs *regs)
अणु
	irqentry_enter_from_user_mode(regs);
	instrumentation_begin();

	machine_check_vector(regs);

	instrumentation_end();
	irqentry_निकास_to_user_mode(regs);
पूर्ण

#अगर_घोषित CONFIG_X86_64
/* MCE hit kernel mode */
DEFINE_IDTENTRY_MCE(exc_machine_check)
अणु
	अचिन्हित दीर्घ dr7;

	dr7 = local_db_save();
	exc_machine_check_kernel(regs);
	local_db_restore(dr7);
पूर्ण

/* The user mode variant. */
DEFINE_IDTENTRY_MCE_USER(exc_machine_check)
अणु
	अचिन्हित दीर्घ dr7;

	dr7 = local_db_save();
	exc_machine_check_user(regs);
	local_db_restore(dr7);
पूर्ण
#अन्यथा
/* 32bit unअगरied entry poपूर्णांक */
DEFINE_IDTENTRY_RAW(exc_machine_check)
अणु
	अचिन्हित दीर्घ dr7;

	dr7 = local_db_save();
	अगर (user_mode(regs))
		exc_machine_check_user(regs);
	अन्यथा
		exc_machine_check_kernel(regs);
	local_db_restore(dr7);
पूर्ण
#पूर्ण_अगर

/*
 * Called क्रम each booted CPU to set up machine checks.
 * Must be called with preempt off:
 */
व्योम mcheck_cpu_init(काष्ठा cpuinfo_x86 *c)
अणु
	अगर (mca_cfg.disabled)
		वापस;

	अगर (__mcheck_cpu_ancient_init(c))
		वापस;

	अगर (!mce_available(c))
		वापस;

	__mcheck_cpu_cap_init();

	अगर (__mcheck_cpu_apply_quirks(c) < 0) अणु
		mca_cfg.disabled = 1;
		वापस;
	पूर्ण

	अगर (mce_gen_pool_init()) अणु
		mca_cfg.disabled = 1;
		pr_emerg("Couldn't allocate MCE records pool!\n");
		वापस;
	पूर्ण

	machine_check_vector = करो_machine_check;

	__mcheck_cpu_init_early(c);
	__mcheck_cpu_init_generic();
	__mcheck_cpu_init_venकरोr(c);
	__mcheck_cpu_init_clear_banks();
	__mcheck_cpu_check_banks();
	__mcheck_cpu_setup_समयr();
पूर्ण

/*
 * Called क्रम each booted CPU to clear some machine checks opt-ins
 */
व्योम mcheck_cpu_clear(काष्ठा cpuinfo_x86 *c)
अणु
	अगर (mca_cfg.disabled)
		वापस;

	अगर (!mce_available(c))
		वापस;

	/*
	 * Possibly to clear general settings generic to x86
	 * __mcheck_cpu_clear_generic(c);
	 */
	__mcheck_cpu_clear_venकरोr(c);

पूर्ण

अटल व्योम __mce_disable_bank(व्योम *arg)
अणु
	पूर्णांक bank = *((पूर्णांक *)arg);
	__clear_bit(bank, this_cpu_ptr(mce_poll_banks));
	cmci_disable_bank(bank);
पूर्ण

व्योम mce_disable_bank(पूर्णांक bank)
अणु
	अगर (bank >= this_cpu_पढ़ो(mce_num_banks)) अणु
		pr_warn(FW_BUG
			"Ignoring request to disable invalid MCA bank %d.\n",
			bank);
		वापस;
	पूर्ण
	set_bit(bank, mce_banks_ce_disabled);
	on_each_cpu(__mce_disable_bank, &bank, 1);
पूर्ण

/*
 * mce=off Disables machine check
 * mce=no_cmci Disables CMCI
 * mce=no_lmce Disables LMCE
 * mce=करोnt_log_ce Clears corrected events silently, no log created क्रम CEs.
 * mce=prपूर्णांक_all Prपूर्णांक all machine check logs to console
 * mce=ignore_ce Disables polling and CMCI, corrected events are not cleared.
 * mce=TOLERANCELEVEL[,monarchसमयout] (number, see above)
 *	monarchसमयout is how दीर्घ to रुको क्रम other CPUs on machine
 *	check, or 0 to not रुको
 * mce=bootlog Log MCEs from beक्रमe booting. Disabled by शेष on AMD Fam10h
	and older.
 * mce=nobootlog Don't log MCEs from beक्रमe booting.
 * mce=bios_cmci_threshold Don't program the CMCI threshold
 * mce=recovery क्रमce enable copy_mc_fragile()
 */
अटल पूर्णांक __init mcheck_enable(अक्षर *str)
अणु
	काष्ठा mca_config *cfg = &mca_cfg;

	अगर (*str == 0) अणु
		enable_p5_mce();
		वापस 1;
	पूर्ण
	अगर (*str == '=')
		str++;
	अगर (!म_भेद(str, "off"))
		cfg->disabled = 1;
	अन्यथा अगर (!म_भेद(str, "no_cmci"))
		cfg->cmci_disabled = true;
	अन्यथा अगर (!म_भेद(str, "no_lmce"))
		cfg->lmce_disabled = 1;
	अन्यथा अगर (!म_भेद(str, "dont_log_ce"))
		cfg->करोnt_log_ce = true;
	अन्यथा अगर (!म_भेद(str, "print_all"))
		cfg->prपूर्णांक_all = true;
	अन्यथा अगर (!म_भेद(str, "ignore_ce"))
		cfg->ignore_ce = true;
	अन्यथा अगर (!म_भेद(str, "bootlog") || !म_भेद(str, "nobootlog"))
		cfg->bootlog = (str[0] == 'b');
	अन्यथा अगर (!म_भेद(str, "bios_cmci_threshold"))
		cfg->bios_cmci_threshold = 1;
	अन्यथा अगर (!म_भेद(str, "recovery"))
		cfg->recovery = 1;
	अन्यथा अगर (है_अंक(str[0])) अणु
		अगर (get_option(&str, &cfg->tolerant) == 2)
			get_option(&str, &(cfg->monarch_समयout));
	पूर्ण अन्यथा अणु
		pr_info("mce argument %s ignored. Please use /sys\n", str);
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण
__setup("mce", mcheck_enable);

पूर्णांक __init mcheck_init(व्योम)
अणु
	mce_रेजिस्टर_decode_chain(&early_nb);
	mce_रेजिस्टर_decode_chain(&mce_uc_nb);
	mce_रेजिस्टर_decode_chain(&mce_शेष_nb);
	mcheck_venकरोr_init_severity();

	INIT_WORK(&mce_work, mce_gen_pool_process);
	init_irq_work(&mce_irq_work, mce_irq_work_cb);

	वापस 0;
पूर्ण

/*
 * mce_syscore: PM support
 */

/*
 * Disable machine checks on suspend and shutकरोwn. We can't really handle
 * them later.
 */
अटल व्योम mce_disable_error_reporting(व्योम)
अणु
	काष्ठा mce_bank *mce_banks = this_cpu_ptr(mce_banks_array);
	पूर्णांक i;

	क्रम (i = 0; i < this_cpu_पढ़ो(mce_num_banks); i++) अणु
		काष्ठा mce_bank *b = &mce_banks[i];

		अगर (b->init)
			wrmsrl(msr_ops.ctl(i), 0);
	पूर्ण
	वापस;
पूर्ण

अटल व्योम venकरोr_disable_error_reporting(व्योम)
अणु
	/*
	 * Don't clear on Intel or AMD or Hygon or Zhaoxin CPUs. Some of these
	 * MSRs are socket-wide. Disabling them क्रम just a single offlined CPU
	 * is bad, since it will inhibit reporting क्रम all shared resources on
	 * the socket like the last level cache (LLC), the पूर्णांकegrated memory
	 * controller (iMC), etc.
	 */
	अगर (boot_cpu_data.x86_venकरोr == X86_VENDOR_INTEL ||
	    boot_cpu_data.x86_venकरोr == X86_VENDOR_HYGON ||
	    boot_cpu_data.x86_venकरोr == X86_VENDOR_AMD ||
	    boot_cpu_data.x86_venकरोr == X86_VENDOR_ZHAOXIN)
		वापस;

	mce_disable_error_reporting();
पूर्ण

अटल पूर्णांक mce_syscore_suspend(व्योम)
अणु
	venकरोr_disable_error_reporting();
	वापस 0;
पूर्ण

अटल व्योम mce_syscore_shutकरोwn(व्योम)
अणु
	venकरोr_disable_error_reporting();
पूर्ण

/*
 * On resume clear all MCE state. Don't want to see leftovers from the BIOS.
 * Only one CPU is active at this समय, the others get re-added later using
 * CPU hotplug:
 */
अटल व्योम mce_syscore_resume(व्योम)
अणु
	__mcheck_cpu_init_generic();
	__mcheck_cpu_init_venकरोr(raw_cpu_ptr(&cpu_info));
	__mcheck_cpu_init_clear_banks();
पूर्ण

अटल काष्ठा syscore_ops mce_syscore_ops = अणु
	.suspend	= mce_syscore_suspend,
	.shutकरोwn	= mce_syscore_shutकरोwn,
	.resume		= mce_syscore_resume,
पूर्ण;

/*
 * mce_device: Sysfs support
 */

अटल व्योम mce_cpu_restart(व्योम *data)
अणु
	अगर (!mce_available(raw_cpu_ptr(&cpu_info)))
		वापस;
	__mcheck_cpu_init_generic();
	__mcheck_cpu_init_clear_banks();
	__mcheck_cpu_init_समयr();
पूर्ण

/* Reinit MCEs after user configuration changes */
अटल व्योम mce_restart(व्योम)
अणु
	mce_समयr_delete_all();
	on_each_cpu(mce_cpu_restart, शून्य, 1);
पूर्ण

/* Toggle features क्रम corrected errors */
अटल व्योम mce_disable_cmci(व्योम *data)
अणु
	अगर (!mce_available(raw_cpu_ptr(&cpu_info)))
		वापस;
	cmci_clear();
पूर्ण

अटल व्योम mce_enable_ce(व्योम *all)
अणु
	अगर (!mce_available(raw_cpu_ptr(&cpu_info)))
		वापस;
	cmci_reenable();
	cmci_recheck();
	अगर (all)
		__mcheck_cpu_init_समयr();
पूर्ण

अटल काष्ठा bus_type mce_subsys = अणु
	.name		= "machinecheck",
	.dev_name	= "machinecheck",
पूर्ण;

DEFINE_PER_CPU(काष्ठा device *, mce_device);

अटल अंतरभूत काष्ठा mce_bank_dev *attr_to_bank(काष्ठा device_attribute *attr)
अणु
	वापस container_of(attr, काष्ठा mce_bank_dev, attr);
पूर्ण

अटल sमाप_प्रकार show_bank(काष्ठा device *s, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	u8 bank = attr_to_bank(attr)->bank;
	काष्ठा mce_bank *b;

	अगर (bank >= per_cpu(mce_num_banks, s->id))
		वापस -EINVAL;

	b = &per_cpu(mce_banks_array, s->id)[bank];

	अगर (!b->init)
		वापस -ENODEV;

	वापस प्र_लिखो(buf, "%llx\n", b->ctl);
पूर्ण

अटल sमाप_प्रकार set_bank(काष्ठा device *s, काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	u8 bank = attr_to_bank(attr)->bank;
	काष्ठा mce_bank *b;
	u64 new;

	अगर (kstrtou64(buf, 0, &new) < 0)
		वापस -EINVAL;

	अगर (bank >= per_cpu(mce_num_banks, s->id))
		वापस -EINVAL;

	b = &per_cpu(mce_banks_array, s->id)[bank];

	अगर (!b->init)
		वापस -ENODEV;

	b->ctl = new;
	mce_restart();

	वापस size;
पूर्ण

अटल sमाप_प्रकार set_ignore_ce(काष्ठा device *s,
			     काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	u64 new;

	अगर (kstrtou64(buf, 0, &new) < 0)
		वापस -EINVAL;

	mutex_lock(&mce_sysfs_mutex);
	अगर (mca_cfg.ignore_ce ^ !!new) अणु
		अगर (new) अणु
			/* disable ce features */
			mce_समयr_delete_all();
			on_each_cpu(mce_disable_cmci, शून्य, 1);
			mca_cfg.ignore_ce = true;
		पूर्ण अन्यथा अणु
			/* enable ce features */
			mca_cfg.ignore_ce = false;
			on_each_cpu(mce_enable_ce, (व्योम *)1, 1);
		पूर्ण
	पूर्ण
	mutex_unlock(&mce_sysfs_mutex);

	वापस size;
पूर्ण

अटल sमाप_प्रकार set_cmci_disabled(काष्ठा device *s,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	u64 new;

	अगर (kstrtou64(buf, 0, &new) < 0)
		वापस -EINVAL;

	mutex_lock(&mce_sysfs_mutex);
	अगर (mca_cfg.cmci_disabled ^ !!new) अणु
		अगर (new) अणु
			/* disable cmci */
			on_each_cpu(mce_disable_cmci, शून्य, 1);
			mca_cfg.cmci_disabled = true;
		पूर्ण अन्यथा अणु
			/* enable cmci */
			mca_cfg.cmci_disabled = false;
			on_each_cpu(mce_enable_ce, शून्य, 1);
		पूर्ण
	पूर्ण
	mutex_unlock(&mce_sysfs_mutex);

	वापस size;
पूर्ण

अटल sमाप_प्रकार store_पूर्णांक_with_restart(काष्ठा device *s,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ old_check_पूर्णांकerval = check_पूर्णांकerval;
	sमाप_प्रकार ret = device_store_uदीर्घ(s, attr, buf, size);

	अगर (check_पूर्णांकerval == old_check_पूर्णांकerval)
		वापस ret;

	mutex_lock(&mce_sysfs_mutex);
	mce_restart();
	mutex_unlock(&mce_sysfs_mutex);

	वापस ret;
पूर्ण

अटल DEVICE_INT_ATTR(tolerant, 0644, mca_cfg.tolerant);
अटल DEVICE_INT_ATTR(monarch_समयout, 0644, mca_cfg.monarch_समयout);
अटल DEVICE_BOOL_ATTR(करोnt_log_ce, 0644, mca_cfg.करोnt_log_ce);
अटल DEVICE_BOOL_ATTR(prपूर्णांक_all, 0644, mca_cfg.prपूर्णांक_all);

अटल काष्ठा dev_ext_attribute dev_attr_check_पूर्णांकerval = अणु
	__ATTR(check_पूर्णांकerval, 0644, device_show_पूर्णांक, store_पूर्णांक_with_restart),
	&check_पूर्णांकerval
पूर्ण;

अटल काष्ठा dev_ext_attribute dev_attr_ignore_ce = अणु
	__ATTR(ignore_ce, 0644, device_show_bool, set_ignore_ce),
	&mca_cfg.ignore_ce
पूर्ण;

अटल काष्ठा dev_ext_attribute dev_attr_cmci_disabled = अणु
	__ATTR(cmci_disabled, 0644, device_show_bool, set_cmci_disabled),
	&mca_cfg.cmci_disabled
पूर्ण;

अटल काष्ठा device_attribute *mce_device_attrs[] = अणु
	&dev_attr_tolerant.attr,
	&dev_attr_check_पूर्णांकerval.attr,
#अगर_घोषित CONFIG_X86_MCELOG_LEGACY
	&dev_attr_trigger,
#पूर्ण_अगर
	&dev_attr_monarch_समयout.attr,
	&dev_attr_करोnt_log_ce.attr,
	&dev_attr_prपूर्णांक_all.attr,
	&dev_attr_ignore_ce.attr,
	&dev_attr_cmci_disabled.attr,
	शून्य
पूर्ण;

अटल cpumask_var_t mce_device_initialized;

अटल व्योम mce_device_release(काष्ठा device *dev)
अणु
	kमुक्त(dev);
पूर्ण

/* Per CPU device init. All of the CPUs still share the same bank device: */
अटल पूर्णांक mce_device_create(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा device *dev;
	पूर्णांक err;
	पूर्णांक i, j;

	अगर (!mce_available(&boot_cpu_data))
		वापस -EIO;

	dev = per_cpu(mce_device, cpu);
	अगर (dev)
		वापस 0;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;
	dev->id  = cpu;
	dev->bus = &mce_subsys;
	dev->release = &mce_device_release;

	err = device_रेजिस्टर(dev);
	अगर (err) अणु
		put_device(dev);
		वापस err;
	पूर्ण

	क्रम (i = 0; mce_device_attrs[i]; i++) अणु
		err = device_create_file(dev, mce_device_attrs[i]);
		अगर (err)
			जाओ error;
	पूर्ण
	क्रम (j = 0; j < per_cpu(mce_num_banks, cpu); j++) अणु
		err = device_create_file(dev, &mce_bank_devs[j].attr);
		अगर (err)
			जाओ error2;
	पूर्ण
	cpumask_set_cpu(cpu, mce_device_initialized);
	per_cpu(mce_device, cpu) = dev;

	वापस 0;
error2:
	जबतक (--j >= 0)
		device_हटाओ_file(dev, &mce_bank_devs[j].attr);
error:
	जबतक (--i >= 0)
		device_हटाओ_file(dev, mce_device_attrs[i]);

	device_unरेजिस्टर(dev);

	वापस err;
पूर्ण

अटल व्योम mce_device_हटाओ(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा device *dev = per_cpu(mce_device, cpu);
	पूर्णांक i;

	अगर (!cpumask_test_cpu(cpu, mce_device_initialized))
		वापस;

	क्रम (i = 0; mce_device_attrs[i]; i++)
		device_हटाओ_file(dev, mce_device_attrs[i]);

	क्रम (i = 0; i < per_cpu(mce_num_banks, cpu); i++)
		device_हटाओ_file(dev, &mce_bank_devs[i].attr);

	device_unरेजिस्टर(dev);
	cpumask_clear_cpu(cpu, mce_device_initialized);
	per_cpu(mce_device, cpu) = शून्य;
पूर्ण

/* Make sure there are no machine checks on offlined CPUs. */
अटल व्योम mce_disable_cpu(व्योम)
अणु
	अगर (!mce_available(raw_cpu_ptr(&cpu_info)))
		वापस;

	अगर (!cpuhp_tasks_frozen)
		cmci_clear();

	venकरोr_disable_error_reporting();
पूर्ण

अटल व्योम mce_reenable_cpu(व्योम)
अणु
	काष्ठा mce_bank *mce_banks = this_cpu_ptr(mce_banks_array);
	पूर्णांक i;

	अगर (!mce_available(raw_cpu_ptr(&cpu_info)))
		वापस;

	अगर (!cpuhp_tasks_frozen)
		cmci_reenable();
	क्रम (i = 0; i < this_cpu_पढ़ो(mce_num_banks); i++) अणु
		काष्ठा mce_bank *b = &mce_banks[i];

		अगर (b->init)
			wrmsrl(msr_ops.ctl(i), b->ctl);
	पूर्ण
पूर्ण

अटल पूर्णांक mce_cpu_dead(अचिन्हित पूर्णांक cpu)
अणु
	mce_पूर्णांकel_hcpu_update(cpu);

	/* पूर्णांकentionally ignoring frozen here */
	अगर (!cpuhp_tasks_frozen)
		cmci_rediscover();
	वापस 0;
पूर्ण

अटल पूर्णांक mce_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा समयr_list *t = this_cpu_ptr(&mce_समयr);
	पूर्णांक ret;

	mce_device_create(cpu);

	ret = mce_threshold_create_device(cpu);
	अगर (ret) अणु
		mce_device_हटाओ(cpu);
		वापस ret;
	पूर्ण
	mce_reenable_cpu();
	mce_start_समयr(t);
	वापस 0;
पूर्ण

अटल पूर्णांक mce_cpu_pre_करोwn(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा समयr_list *t = this_cpu_ptr(&mce_समयr);

	mce_disable_cpu();
	del_समयr_sync(t);
	mce_threshold_हटाओ_device(cpu);
	mce_device_हटाओ(cpu);
	वापस 0;
पूर्ण

अटल __init व्योम mce_init_banks(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_NR_BANKS; i++) अणु
		काष्ठा mce_bank_dev *b = &mce_bank_devs[i];
		काष्ठा device_attribute *a = &b->attr;

		b->bank = i;

		sysfs_attr_init(&a->attr);
		a->attr.name	= b->attrname;
		snम_लिखो(b->attrname, ATTR_LEN, "bank%d", i);

		a->attr.mode	= 0644;
		a->show		= show_bank;
		a->store	= set_bank;
	पूर्ण
पूर्ण

/*
 * When running on XEN, this initcall is ordered against the XEN mcelog
 * initcall:
 *
 *   device_initcall(xen_late_init_mcelog);
 *   device_initcall_sync(mcheck_init_device);
 */
अटल __init पूर्णांक mcheck_init_device(व्योम)
अणु
	पूर्णांक err;

	/*
	 * Check अगर we have a spare भव bit. This will only become
	 * a problem अगर/when we move beyond 5-level page tables.
	 */
	MAYBE_BUILD_BUG_ON(__VIRTUAL_MASK_SHIFT >= 63);

	अगर (!mce_available(&boot_cpu_data)) अणु
		err = -EIO;
		जाओ err_out;
	पूर्ण

	अगर (!zalloc_cpumask_var(&mce_device_initialized, GFP_KERNEL)) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण

	mce_init_banks();

	err = subsys_प्रणाली_रेजिस्टर(&mce_subsys, शून्य);
	अगर (err)
		जाओ err_out_mem;

	err = cpuhp_setup_state(CPUHP_X86_MCE_DEAD, "x86/mce:dead", शून्य,
				mce_cpu_dead);
	अगर (err)
		जाओ err_out_mem;

	/*
	 * Invokes mce_cpu_online() on all CPUs which are online when
	 * the state is installed.
	 */
	err = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "x86/mce:online",
				mce_cpu_online, mce_cpu_pre_करोwn);
	अगर (err < 0)
		जाओ err_out_online;

	रेजिस्टर_syscore_ops(&mce_syscore_ops);

	वापस 0;

err_out_online:
	cpuhp_हटाओ_state(CPUHP_X86_MCE_DEAD);

err_out_mem:
	मुक्त_cpumask_var(mce_device_initialized);

err_out:
	pr_err("Unable to init MCE device (rc: %d)\n", err);

	वापस err;
पूर्ण
device_initcall_sync(mcheck_init_device);

/*
 * Old style boot options parsing. Only क्रम compatibility.
 */
अटल पूर्णांक __init mcheck_disable(अक्षर *str)
अणु
	mca_cfg.disabled = 1;
	वापस 1;
पूर्ण
__setup("nomce", mcheck_disable);

#अगर_घोषित CONFIG_DEBUG_FS
काष्ठा dentry *mce_get_debugfs_dir(व्योम)
अणु
	अटल काष्ठा dentry *dmce;

	अगर (!dmce)
		dmce = debugfs_create_dir("mce", शून्य);

	वापस dmce;
पूर्ण

अटल व्योम mce_reset(व्योम)
अणु
	cpu_missing = 0;
	atomic_set(&mce_fake_panicked, 0);
	atomic_set(&mce_executing, 0);
	atomic_set(&mce_callin, 0);
	atomic_set(&global_nwo, 0);
	cpumask_setall(&mce_missing_cpus);
पूर्ण

अटल पूर्णांक fake_panic_get(व्योम *data, u64 *val)
अणु
	*val = fake_panic;
	वापस 0;
पूर्ण

अटल पूर्णांक fake_panic_set(व्योम *data, u64 val)
अणु
	mce_reset();
	fake_panic = val;
	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(fake_panic_fops, fake_panic_get, fake_panic_set,
			 "%llu\n");

अटल व्योम __init mcheck_debugfs_init(व्योम)
अणु
	काष्ठा dentry *dmce;

	dmce = mce_get_debugfs_dir();
	debugfs_create_file_unsafe("fake_panic", 0444, dmce, शून्य,
				   &fake_panic_fops);
पूर्ण
#अन्यथा
अटल व्योम __init mcheck_debugfs_init(व्योम) अणु पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init mcheck_late_init(व्योम)
अणु
	अगर (mca_cfg.recovery)
		enable_copy_mc_fragile();

	mcheck_debugfs_init();

	/*
	 * Flush out everything that has been logged during early boot, now that
	 * everything has been initialized (workqueues, decoders, ...).
	 */
	mce_schedule_work();

	वापस 0;
पूर्ण
late_initcall(mcheck_late_init);
