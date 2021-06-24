<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Core of Xen paravirt_ops implementation.
 *
 * This file contains the xen_paravirt_ops काष्ठाure itself, and the
 * implementations क्रम:
 * - privileged inकाष्ठाions
 * - पूर्णांकerrupt flags
 * - segment operations
 * - booting and setup
 *
 * Jeremy Fitzhardinge <jeremy@xensource.com>, XenSource Inc, 2007
 */

#समावेश <linux/cpu.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/smp.h>
#समावेश <linux/preempt.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/percpu.h>
#समावेश <linux/delay.h>
#समावेश <linux/start_kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/memblock.h>
#समावेश <linux/export.h>
#समावेश <linux/mm.h>
#समावेश <linux/page-flags.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/console.h>
#समावेश <linux/pci.h>
#समावेश <linux/gfp.h>
#समावेश <linux/edd.h>
#समावेश <linux/objtool.h>

#समावेश <xen/xen.h>
#समावेश <xen/events.h>
#समावेश <xen/पूर्णांकerface/xen.h>
#समावेश <xen/पूर्णांकerface/version.h>
#समावेश <xen/पूर्णांकerface/physdev.h>
#समावेश <xen/पूर्णांकerface/vcpu.h>
#समावेश <xen/पूर्णांकerface/memory.h>
#समावेश <xen/पूर्णांकerface/nmi.h>
#समावेश <xen/पूर्णांकerface/xen-mca.h>
#समावेश <xen/features.h>
#समावेश <xen/page.h>
#समावेश <xen/hvc-console.h>
#समावेश <xen/acpi.h>

#समावेश <यंत्र/paravirt.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/xen/pci.h>
#समावेश <यंत्र/xen/hypercall.h>
#समावेश <यंत्र/xen/hypervisor.h>
#समावेश <यंत्र/xen/cpuid.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/proto.h>
#समावेश <यंत्र/msr-index.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/stackprotector.h>
#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/mach_traps.h>
#समावेश <यंत्र/mरुको.h>
#समावेश <यंत्र/pci_x86.h>
#समावेश <यंत्र/cpu.h>
#अगर_घोषित CONFIG_X86_IOPL_IOPERM
#समावेश <यंत्र/io_biपंचांगap.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
#समावेश <linux/acpi.h>
#समावेश <यंत्र/acpi.h>
#समावेश <acpi/pdc_पूर्णांकel.h>
#समावेश <acpi/processor.h>
#समावेश <xen/पूर्णांकerface/platक्रमm.h>
#पूर्ण_अगर

#समावेश "xen-ops.h"
#समावेश "mmu.h"
#समावेश "smp.h"
#समावेश "multicalls.h"
#समावेश "pmu.h"

#समावेश "../kernel/cpu/cpu.h" /* get_cpu_cap() */

व्योम *xen_initial_gdt;

अटल पूर्णांक xen_cpu_up_prepare_pv(अचिन्हित पूर्णांक cpu);
अटल पूर्णांक xen_cpu_dead_pv(अचिन्हित पूर्णांक cpu);

काष्ठा tls_descs अणु
	काष्ठा desc_काष्ठा desc[3];
पूर्ण;

/*
 * Updating the 3 TLS descriptors in the GDT on every task चयन is
 * surprisingly expensive so we aव्योम updating them अगर they haven't
 * changed.  Since Xen ग_लिखोs dअगरferent descriptors than the one
 * passed in the update_descriptor hypercall we keep shaकरोw copies to
 * compare against.
 */
अटल DEFINE_PER_CPU(काष्ठा tls_descs, shaकरोw_tls_desc);

अटल व्योम __init xen_banner(व्योम)
अणु
	अचिन्हित version = HYPERVISOR_xen_version(XENVER_version, शून्य);
	काष्ठा xen_extraversion extra;
	HYPERVISOR_xen_version(XENVER_extraversion, &extra);

	pr_info("Booting paravirtualized kernel on %s\n", pv_info.name);
	prपूर्णांकk(KERN_INFO "Xen version: %d.%d%s%s\n",
	       version >> 16, version & 0xffff, extra.extraversion,
	       xen_feature(XENFEAT_mmu_pt_update_preserve_ad) ? " (preserve-AD)" : "");
पूर्ण

अटल व्योम __init xen_pv_init_platक्रमm(व्योम)
अणु
	populate_extra_pte(fix_to_virt(FIX_PARAVIRT_BOOTMAP));

	set_fixmap(FIX_PARAVIRT_BOOTMAP, xen_start_info->shared_info);
	HYPERVISOR_shared_info = (व्योम *)fix_to_virt(FIX_PARAVIRT_BOOTMAP);

	/* xen घड़ी uses per-cpu vcpu_info, need to init it क्रम boot cpu */
	xen_vcpu_info_reset(0);

	/* pvघड़ी is in shared info area */
	xen_init_समय_ops();
पूर्ण

अटल व्योम __init xen_pv_guest_late_init(व्योम)
अणु
#अगर_अघोषित CONFIG_SMP
	/* Setup shared vcpu info क्रम non-smp configurations */
	xen_setup_vcpu_info_placement();
#पूर्ण_अगर
पूर्ण

/* Check अगर running on Xen version (major, minor) or later */
bool
xen_running_on_version_or_later(अचिन्हित पूर्णांक major, अचिन्हित पूर्णांक minor)
अणु
	अचिन्हित पूर्णांक version;

	अगर (!xen_करोमुख्य())
		वापस false;

	version = HYPERVISOR_xen_version(XENVER_version, शून्य);
	अगर ((((version >> 16) == major) && ((version & 0xffff) >= minor)) ||
		((version >> 16) > major))
		वापस true;
	वापस false;
पूर्ण

अटल __पढ़ो_mostly अचिन्हित पूर्णांक cpuid_leaf5_ecx_val;
अटल __पढ़ो_mostly अचिन्हित पूर्णांक cpuid_leaf5_edx_val;

अटल व्योम xen_cpuid(अचिन्हित पूर्णांक *ax, अचिन्हित पूर्णांक *bx,
		      अचिन्हित पूर्णांक *cx, अचिन्हित पूर्णांक *dx)
अणु
	अचिन्हित maskebx = ~0;

	/*
	 * Mask out inconvenient features, to try and disable as many
	 * unsupported kernel subप्रणालीs as possible.
	 */
	चयन (*ax) अणु
	हाल CPUID_MWAIT_LEAF:
		/* Synthesize the values.. */
		*ax = 0;
		*bx = 0;
		*cx = cpuid_leaf5_ecx_val;
		*dx = cpuid_leaf5_edx_val;
		वापस;

	हाल 0xb:
		/* Suppress extended topology stuff */
		maskebx = 0;
		अवरोध;
	पूर्ण

	यंत्र(XEN_EMULATE_PREFIX "cpuid"
		: "=a" (*ax),
		  "=b" (*bx),
		  "=c" (*cx),
		  "=d" (*dx)
		: "0" (*ax), "2" (*cx));

	*bx &= maskebx;
पूर्ण
STACK_FRAME_NON_STANDARD(xen_cpuid); /* XEN_EMULATE_PREFIX */

अटल bool __init xen_check_mरुको(व्योम)
अणु
#अगर_घोषित CONFIG_ACPI
	काष्ठा xen_platक्रमm_op op = अणु
		.cmd			= XENPF_set_processor_pminfo,
		.u.set_pminfo.id	= -1,
		.u.set_pminfo.type	= XEN_PM_PDC,
	पूर्ण;
	uपूर्णांक32_t buf[3];
	अचिन्हित पूर्णांक ax, bx, cx, dx;
	अचिन्हित पूर्णांक mरुको_mask;

	/* We need to determine whether it is OK to expose the MWAIT
	 * capability to the kernel to harvest deeper than C3 states from ACPI
	 * _CST using the processor_harvest_xen.c module. For this to work, we
	 * need to gather the MWAIT_LEAF values (which the cstate.c code
	 * checks against). The hypervisor won't expose the MWAIT flag because
	 * it would अवरोध backwards compatibility; so we will find out directly
	 * from the hardware and hypercall.
	 */
	अगर (!xen_initial_करोमुख्य())
		वापस false;

	/*
	 * When running under platक्रमm earlier than Xen4.2, करो not expose
	 * mरुको, to aव्योम the risk of loading native acpi pad driver
	 */
	अगर (!xen_running_on_version_or_later(4, 2))
		वापस false;

	ax = 1;
	cx = 0;

	native_cpuid(&ax, &bx, &cx, &dx);

	mरुको_mask = (1 << (X86_FEATURE_EST % 32)) |
		     (1 << (X86_FEATURE_MWAIT % 32));

	अगर ((cx & mरुको_mask) != mरुको_mask)
		वापस false;

	/* We need to emulate the MWAIT_LEAF and क्रम that we need both
	 * ecx and edx. The hypercall provides only partial inक्रमmation.
	 */

	ax = CPUID_MWAIT_LEAF;
	bx = 0;
	cx = 0;
	dx = 0;

	native_cpuid(&ax, &bx, &cx, &dx);

	/* Ask the Hypervisor whether to clear ACPI_PDC_C_C2C3_FFH. If so,
	 * करोn't expose MWAIT_LEAF and let ACPI pick the IOPORT version of C3.
	 */
	buf[0] = ACPI_PDC_REVISION_ID;
	buf[1] = 1;
	buf[2] = (ACPI_PDC_C_CAPABILITY_SMP | ACPI_PDC_EST_CAPABILITY_SWSMP);

	set_xen_guest_handle(op.u.set_pminfo.pdc, buf);

	अगर ((HYPERVISOR_platक्रमm_op(&op) == 0) &&
	    (buf[2] & (ACPI_PDC_C_C1_FFH | ACPI_PDC_C_C2C3_FFH))) अणु
		cpuid_leaf5_ecx_val = cx;
		cpuid_leaf5_edx_val = dx;
	पूर्ण
	वापस true;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल bool __init xen_check_xsave(व्योम)
अणु
	अचिन्हित पूर्णांक cx, xsave_mask;

	cx = cpuid_ecx(1);

	xsave_mask = (1 << (X86_FEATURE_XSAVE % 32)) |
		     (1 << (X86_FEATURE_OSXSAVE % 32));

	/* Xen will set CR4.OSXSAVE अगर supported and not disabled by क्रमce */
	वापस (cx & xsave_mask) == xsave_mask;
पूर्ण

अटल व्योम __init xen_init_capabilities(व्योम)
अणु
	setup_क्रमce_cpu_cap(X86_FEATURE_XENPV);
	setup_clear_cpu_cap(X86_FEATURE_DCA);
	setup_clear_cpu_cap(X86_FEATURE_APERFMPERF);
	setup_clear_cpu_cap(X86_FEATURE_MTRR);
	setup_clear_cpu_cap(X86_FEATURE_ACC);
	setup_clear_cpu_cap(X86_FEATURE_X2APIC);
	setup_clear_cpu_cap(X86_FEATURE_SME);

	/*
	 * Xen PV would need some work to support PCID: CR3 handling as well
	 * as xen_flush_tlb_others() would need updating.
	 */
	setup_clear_cpu_cap(X86_FEATURE_PCID);

	अगर (!xen_initial_करोमुख्य())
		setup_clear_cpu_cap(X86_FEATURE_ACPI);

	अगर (xen_check_mरुको())
		setup_क्रमce_cpu_cap(X86_FEATURE_MWAIT);
	अन्यथा
		setup_clear_cpu_cap(X86_FEATURE_MWAIT);

	अगर (!xen_check_xsave()) अणु
		setup_clear_cpu_cap(X86_FEATURE_XSAVE);
		setup_clear_cpu_cap(X86_FEATURE_OSXSAVE);
	पूर्ण
पूर्ण

अटल व्योम xen_set_debugreg(पूर्णांक reg, अचिन्हित दीर्घ val)
अणु
	HYPERVISOR_set_debugreg(reg, val);
पूर्ण

अटल अचिन्हित दीर्घ xen_get_debugreg(पूर्णांक reg)
अणु
	वापस HYPERVISOR_get_debugreg(reg);
पूर्ण

अटल व्योम xen_end_context_चयन(काष्ठा task_काष्ठा *next)
अणु
	xen_mc_flush();
	paravirt_end_context_चयन(next);
पूर्ण

अटल अचिन्हित दीर्घ xen_store_tr(व्योम)
अणु
	वापस 0;
पूर्ण

/*
 * Set the page permissions क्रम a particular भव address.  If the
 * address is a vदो_स्मृति mapping (or other non-linear mapping), then
 * find the linear mapping of the page and also set its protections to
 * match.
 */
अटल व्योम set_aliased_prot(व्योम *v, pgprot_t prot)
अणु
	पूर्णांक level;
	pte_t *ptep;
	pte_t pte;
	अचिन्हित दीर्घ pfn;
	अचिन्हित अक्षर dummy;
	व्योम *va;

	ptep = lookup_address((अचिन्हित दीर्घ)v, &level);
	BUG_ON(ptep == शून्य);

	pfn = pte_pfn(*ptep);
	pte = pfn_pte(pfn, prot);

	/*
	 * Careful: update_va_mapping() will fail अगर the भव address
	 * we're poking isn't populated in the page tables.  We don't
	 * need to worry about the direct map (that's always in the page
	 * tables), but we need to be careful about vmap space.  In
	 * particular, the top level page table can lazily propagate
	 * entries between processes, so अगर we've चयनed mms since we
	 * vmapped the target in the first place, we might not have the
	 * top-level page table entry populated.
	 *
	 * We disable preemption because we want the same mm active when
	 * we probe the target and when we issue the hypercall.  We'll
	 * have the same nominal mm, but अगर we're a kernel thपढ़ो, lazy
	 * mm dropping could change our pgd.
	 *
	 * Out of an abundance of caution, this uses __get_user() to fault
	 * in the target address just in हाल there's some obscure हाल
	 * in which the target address isn't पढ़ोable.
	 */

	preempt_disable();

	copy_from_kernel_nofault(&dummy, v, 1);

	अगर (HYPERVISOR_update_va_mapping((अचिन्हित दीर्घ)v, pte, 0))
		BUG();

	va = __va(PFN_PHYS(pfn));

	अगर (va != v && HYPERVISOR_update_va_mapping((अचिन्हित दीर्घ)va, pte, 0))
		BUG();

	preempt_enable();
पूर्ण

अटल व्योम xen_alloc_ldt(काष्ठा desc_काष्ठा *ldt, अचिन्हित entries)
अणु
	स्थिर अचिन्हित entries_per_page = PAGE_SIZE / LDT_ENTRY_SIZE;
	पूर्णांक i;

	/*
	 * We need to mark the all aliases of the LDT pages RO.  We
	 * करोn't need to call vm_flush_aliases(), though, since that's
	 * only responsible क्रम flushing aliases out the TLBs, not the
	 * page tables, and Xen will flush the TLB क्रम us अगर needed.
	 *
	 * To aव्योम confusing future पढ़ोers: none of this is necessary
	 * to load the LDT.  The hypervisor only checks this when the
	 * LDT is faulted in due to subsequent descriptor access.
	 */

	क्रम (i = 0; i < entries; i += entries_per_page)
		set_aliased_prot(ldt + i, PAGE_KERNEL_RO);
पूर्ण

अटल व्योम xen_मुक्त_ldt(काष्ठा desc_काष्ठा *ldt, अचिन्हित entries)
अणु
	स्थिर अचिन्हित entries_per_page = PAGE_SIZE / LDT_ENTRY_SIZE;
	पूर्णांक i;

	क्रम (i = 0; i < entries; i += entries_per_page)
		set_aliased_prot(ldt + i, PAGE_KERNEL);
पूर्ण

अटल व्योम xen_set_ldt(स्थिर व्योम *addr, अचिन्हित entries)
अणु
	काष्ठा mmuext_op *op;
	काष्ठा multicall_space mcs = xen_mc_entry(माप(*op));

	trace_xen_cpu_set_ldt(addr, entries);

	op = mcs.args;
	op->cmd = MMUEXT_SET_LDT;
	op->arg1.linear_addr = (अचिन्हित दीर्घ)addr;
	op->arg2.nr_ents = entries;

	MULTI_mmuext_op(mcs.mc, op, 1, शून्य, DOMID_SELF);

	xen_mc_issue(PARAVIRT_LAZY_CPU);
पूर्ण

अटल व्योम xen_load_gdt(स्थिर काष्ठा desc_ptr *dtr)
अणु
	अचिन्हित दीर्घ va = dtr->address;
	अचिन्हित पूर्णांक size = dtr->size + 1;
	अचिन्हित दीर्घ pfn, mfn;
	पूर्णांक level;
	pte_t *ptep;
	व्योम *virt;

	/* @size should be at most GDT_SIZE which is smaller than PAGE_SIZE. */
	BUG_ON(size > PAGE_SIZE);
	BUG_ON(va & ~PAGE_MASK);

	/*
	 * The GDT is per-cpu and is in the percpu data area.
	 * That can be भवly mapped, so we need to करो a
	 * page-walk to get the underlying MFN क्रम the
	 * hypercall.  The page can also be in the kernel's
	 * linear range, so we need to RO that mapping too.
	 */
	ptep = lookup_address(va, &level);
	BUG_ON(ptep == शून्य);

	pfn = pte_pfn(*ptep);
	mfn = pfn_to_mfn(pfn);
	virt = __va(PFN_PHYS(pfn));

	make_lowmem_page_पढ़ोonly((व्योम *)va);
	make_lowmem_page_पढ़ोonly(virt);

	अगर (HYPERVISOR_set_gdt(&mfn, size / माप(काष्ठा desc_काष्ठा)))
		BUG();
पूर्ण

/*
 * load_gdt क्रम early boot, when the gdt is only mapped once
 */
अटल व्योम __init xen_load_gdt_boot(स्थिर काष्ठा desc_ptr *dtr)
अणु
	अचिन्हित दीर्घ va = dtr->address;
	अचिन्हित पूर्णांक size = dtr->size + 1;
	अचिन्हित दीर्घ pfn, mfn;
	pte_t pte;

	/* @size should be at most GDT_SIZE which is smaller than PAGE_SIZE. */
	BUG_ON(size > PAGE_SIZE);
	BUG_ON(va & ~PAGE_MASK);

	pfn = virt_to_pfn(va);
	mfn = pfn_to_mfn(pfn);

	pte = pfn_pte(pfn, PAGE_KERNEL_RO);

	अगर (HYPERVISOR_update_va_mapping((अचिन्हित दीर्घ)va, pte, 0))
		BUG();

	अगर (HYPERVISOR_set_gdt(&mfn, size / माप(काष्ठा desc_काष्ठा)))
		BUG();
पूर्ण

अटल अंतरभूत bool desc_equal(स्थिर काष्ठा desc_काष्ठा *d1,
			      स्थिर काष्ठा desc_काष्ठा *d2)
अणु
	वापस !स_भेद(d1, d2, माप(*d1));
पूर्ण

अटल व्योम load_TLS_descriptor(काष्ठा thपढ़ो_काष्ठा *t,
				अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक i)
अणु
	काष्ठा desc_काष्ठा *shaकरोw = &per_cpu(shaकरोw_tls_desc, cpu).desc[i];
	काष्ठा desc_काष्ठा *gdt;
	xmaddr_t maddr;
	काष्ठा multicall_space mc;

	अगर (desc_equal(shaकरोw, &t->tls_array[i]))
		वापस;

	*shaकरोw = t->tls_array[i];

	gdt = get_cpu_gdt_rw(cpu);
	maddr = arbitrary_virt_to_machine(&gdt[GDT_ENTRY_TLS_MIN+i]);
	mc = __xen_mc_entry(0);

	MULTI_update_descriptor(mc.mc, maddr.maddr, t->tls_array[i]);
पूर्ण

अटल व्योम xen_load_tls(काष्ठा thपढ़ो_काष्ठा *t, अचिन्हित पूर्णांक cpu)
अणु
	/*
	 * In lazy mode we need to zero %fs, otherwise we may get an
	 * exception between the new %fs descriptor being loaded and
	 * %fs being effectively cleared at __चयन_to().
	 */
	अगर (paravirt_get_lazy_mode() == PARAVIRT_LAZY_CPU)
		loadsegment(fs, 0);

	xen_mc_batch();

	load_TLS_descriptor(t, cpu, 0);
	load_TLS_descriptor(t, cpu, 1);
	load_TLS_descriptor(t, cpu, 2);

	xen_mc_issue(PARAVIRT_LAZY_CPU);
पूर्ण

अटल व्योम xen_load_gs_index(अचिन्हित पूर्णांक idx)
अणु
	अगर (HYPERVISOR_set_segment_base(SEGBASE_GS_USER_SEL, idx))
		BUG();
पूर्ण

अटल व्योम xen_ग_लिखो_ldt_entry(काष्ठा desc_काष्ठा *dt, पूर्णांक entrynum,
				स्थिर व्योम *ptr)
अणु
	xmaddr_t mach_lp = arbitrary_virt_to_machine(&dt[entrynum]);
	u64 entry = *(u64 *)ptr;

	trace_xen_cpu_ग_लिखो_ldt_entry(dt, entrynum, entry);

	preempt_disable();

	xen_mc_flush();
	अगर (HYPERVISOR_update_descriptor(mach_lp.maddr, entry))
		BUG();

	preempt_enable();
पूर्ण

व्योम noist_exc_debug(काष्ठा pt_regs *regs);

DEFINE_IDTENTRY_RAW(xenpv_exc_nmi)
अणु
	/* On Xen PV, NMI करोesn't use IST.  The C part is the same as native. */
	exc_nmi(regs);
पूर्ण

DEFINE_IDTENTRY_RAW_ERRORCODE(xenpv_exc_द्विगुन_fault)
अणु
	/* On Xen PV, DF करोesn't use IST.  The C part is the same as native. */
	exc_द्विगुन_fault(regs, error_code);
पूर्ण

DEFINE_IDTENTRY_RAW(xenpv_exc_debug)
अणु
	/*
	 * There's no IST on Xen PV, but we still need to dispatch
	 * to the correct handler.
	 */
	अगर (user_mode(regs))
		noist_exc_debug(regs);
	अन्यथा
		exc_debug(regs);
पूर्ण

DEFINE_IDTENTRY_RAW(exc_xen_unknown_trap)
अणु
	/* This should never happen and there is no way to handle it. */
	pr_err("Unknown trap in Xen PV mode.");
	BUG();
पूर्ण

#अगर_घोषित CONFIG_X86_MCE
DEFINE_IDTENTRY_RAW(xenpv_exc_machine_check)
अणु
	/*
	 * There's no IST on Xen PV, but we still need to dispatch
	 * to the correct handler.
	 */
	अगर (user_mode(regs))
		noist_exc_machine_check(regs);
	अन्यथा
		exc_machine_check(regs);
पूर्ण
#पूर्ण_अगर

काष्ठा trap_array_entry अणु
	व्योम (*orig)(व्योम);
	व्योम (*xen)(व्योम);
	bool ist_okay;
पूर्ण;

#घोषणा TRAP_ENTRY(func, ist_ok) अणु			\
	.orig		= यंत्र_##func,			\
	.xen		= xen_यंत्र_##func,		\
	.ist_okay	= ist_ok पूर्ण

#घोषणा TRAP_ENTRY_REसूची(func, ist_ok) अणु		\
	.orig		= यंत्र_##func,			\
	.xen		= xen_यंत्र_xenpv_##func,		\
	.ist_okay	= ist_ok पूर्ण

अटल काष्ठा trap_array_entry trap_array[] = अणु
	TRAP_ENTRY_REसूची(exc_debug,			true  ),
	TRAP_ENTRY_REसूची(exc_द्विगुन_fault,		true  ),
#अगर_घोषित CONFIG_X86_MCE
	TRAP_ENTRY_REसूची(exc_machine_check,		true  ),
#पूर्ण_अगर
	TRAP_ENTRY_REसूची(exc_nmi,			true  ),
	TRAP_ENTRY(exc_पूर्णांक3,				false ),
	TRAP_ENTRY(exc_overflow,			false ),
#अगर_घोषित CONFIG_IA32_EMULATION
	अणु entry_INT80_compat,          xen_entry_INT80_compat,          false पूर्ण,
#पूर्ण_अगर
	TRAP_ENTRY(exc_page_fault,			false ),
	TRAP_ENTRY(exc_भागide_error,			false ),
	TRAP_ENTRY(exc_bounds,				false ),
	TRAP_ENTRY(exc_invalid_op,			false ),
	TRAP_ENTRY(exc_device_not_available,		false ),
	TRAP_ENTRY(exc_coproc_segment_overrun,		false ),
	TRAP_ENTRY(exc_invalid_tss,			false ),
	TRAP_ENTRY(exc_segment_not_present,		false ),
	TRAP_ENTRY(exc_stack_segment,			false ),
	TRAP_ENTRY(exc_general_protection,		false ),
	TRAP_ENTRY(exc_spurious_पूर्णांकerrupt_bug,		false ),
	TRAP_ENTRY(exc_coprocessor_error,		false ),
	TRAP_ENTRY(exc_alignment_check,			false ),
	TRAP_ENTRY(exc_simd_coprocessor_error,		false ),
पूर्ण;

अटल bool __ref get_trap_addr(व्योम **addr, अचिन्हित पूर्णांक ist)
अणु
	अचिन्हित पूर्णांक nr;
	bool ist_okay = false;
	bool found = false;

	/*
	 * Replace trap handler addresses by Xen specअगरic ones.
	 * Check क्रम known traps using IST and whitelist them.
	 * The debugger ones are the only ones we care about.
	 * Xen will handle faults like द्विगुन_fault, so we should never see
	 * them.  Warn अगर there's an unexpected IST-using fault handler.
	 */
	क्रम (nr = 0; nr < ARRAY_SIZE(trap_array); nr++) अणु
		काष्ठा trap_array_entry *entry = trap_array + nr;

		अगर (*addr == entry->orig) अणु
			*addr = entry->xen;
			ist_okay = entry->ist_okay;
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (nr == ARRAY_SIZE(trap_array) &&
	    *addr >= (व्योम *)early_idt_handler_array[0] &&
	    *addr < (व्योम *)early_idt_handler_array[NUM_EXCEPTION_VECTORS]) अणु
		nr = (*addr - (व्योम *)early_idt_handler_array[0]) /
		     EARLY_IDT_HANDLER_SIZE;
		*addr = (व्योम *)xen_early_idt_handler_array[nr];
		found = true;
	पूर्ण

	अगर (!found)
		*addr = (व्योम *)xen_यंत्र_exc_xen_unknown_trap;

	अगर (WARN_ON(found && ist != 0 && !ist_okay))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक cvt_gate_to_trap(पूर्णांक vector, स्थिर gate_desc *val,
			    काष्ठा trap_info *info)
अणु
	अचिन्हित दीर्घ addr;

	अगर (val->bits.type != GATE_TRAP && val->bits.type != GATE_INTERRUPT)
		वापस 0;

	info->vector = vector;

	addr = gate_offset(val);
	अगर (!get_trap_addr((व्योम **)&addr, val->bits.ist))
		वापस 0;
	info->address = addr;

	info->cs = gate_segment(val);
	info->flags = val->bits.dpl;
	/* पूर्णांकerrupt gates clear IF */
	अगर (val->bits.type == GATE_INTERRUPT)
		info->flags |= 1 << 2;

	वापस 1;
पूर्ण

/* Locations of each CPU's IDT */
अटल DEFINE_PER_CPU(काष्ठा desc_ptr, idt_desc);

/* Set an IDT entry.  If the entry is part of the current IDT, then
   also update Xen. */
अटल व्योम xen_ग_लिखो_idt_entry(gate_desc *dt, पूर्णांक entrynum, स्थिर gate_desc *g)
अणु
	अचिन्हित दीर्घ p = (अचिन्हित दीर्घ)&dt[entrynum];
	अचिन्हित दीर्घ start, end;

	trace_xen_cpu_ग_लिखो_idt_entry(dt, entrynum, g);

	preempt_disable();

	start = __this_cpu_पढ़ो(idt_desc.address);
	end = start + __this_cpu_पढ़ो(idt_desc.size) + 1;

	xen_mc_flush();

	native_ग_लिखो_idt_entry(dt, entrynum, g);

	अगर (p >= start && (p + 8) <= end) अणु
		काष्ठा trap_info info[2];

		info[1].address = 0;

		अगर (cvt_gate_to_trap(entrynum, g, &info[0]))
			अगर (HYPERVISOR_set_trap_table(info))
				BUG();
	पूर्ण

	preempt_enable();
पूर्ण

अटल व्योम xen_convert_trap_info(स्थिर काष्ठा desc_ptr *desc,
				  काष्ठा trap_info *traps)
अणु
	अचिन्हित in, out, count;

	count = (desc->size+1) / माप(gate_desc);
	BUG_ON(count > 256);

	क्रम (in = out = 0; in < count; in++) अणु
		gate_desc *entry = (gate_desc *)(desc->address) + in;

		अगर (cvt_gate_to_trap(in, entry, &traps[out]))
			out++;
	पूर्ण
	traps[out].address = 0;
पूर्ण

व्योम xen_copy_trap_info(काष्ठा trap_info *traps)
अणु
	स्थिर काष्ठा desc_ptr *desc = this_cpu_ptr(&idt_desc);

	xen_convert_trap_info(desc, traps);
पूर्ण

/* Load a new IDT पूर्णांकo Xen.  In principle this can be per-CPU, so we
   hold a spinlock to protect the अटल traps[] array (अटल because
   it aव्योमs allocation, and saves stack space). */
अटल व्योम xen_load_idt(स्थिर काष्ठा desc_ptr *desc)
अणु
	अटल DEFINE_SPINLOCK(lock);
	अटल काष्ठा trap_info traps[257];

	trace_xen_cpu_load_idt(desc);

	spin_lock(&lock);

	स_नकल(this_cpu_ptr(&idt_desc), desc, माप(idt_desc));

	xen_convert_trap_info(desc, traps);

	xen_mc_flush();
	अगर (HYPERVISOR_set_trap_table(traps))
		BUG();

	spin_unlock(&lock);
पूर्ण

/* Write a GDT descriptor entry.  Ignore LDT descriptors, since
   they're handled dअगरferently. */
अटल व्योम xen_ग_लिखो_gdt_entry(काष्ठा desc_काष्ठा *dt, पूर्णांक entry,
				स्थिर व्योम *desc, पूर्णांक type)
अणु
	trace_xen_cpu_ग_लिखो_gdt_entry(dt, entry, desc, type);

	preempt_disable();

	चयन (type) अणु
	हाल DESC_LDT:
	हाल DESC_TSS:
		/* ignore */
		अवरोध;

	शेष: अणु
		xmaddr_t maddr = arbitrary_virt_to_machine(&dt[entry]);

		xen_mc_flush();
		अगर (HYPERVISOR_update_descriptor(maddr.maddr, *(u64 *)desc))
			BUG();
	पूर्ण

	पूर्ण

	preempt_enable();
पूर्ण

/*
 * Version of ग_लिखो_gdt_entry क्रम use at early boot-समय needed to
 * update an entry as simply as possible.
 */
अटल व्योम __init xen_ग_लिखो_gdt_entry_boot(काष्ठा desc_काष्ठा *dt, पूर्णांक entry,
					    स्थिर व्योम *desc, पूर्णांक type)
अणु
	trace_xen_cpu_ग_लिखो_gdt_entry(dt, entry, desc, type);

	चयन (type) अणु
	हाल DESC_LDT:
	हाल DESC_TSS:
		/* ignore */
		अवरोध;

	शेष: अणु
		xmaddr_t maddr = virt_to_machine(&dt[entry]);

		अगर (HYPERVISOR_update_descriptor(maddr.maddr, *(u64 *)desc))
			dt[entry] = *(काष्ठा desc_काष्ठा *)desc;
	पूर्ण

	पूर्ण
पूर्ण

अटल व्योम xen_load_sp0(अचिन्हित दीर्घ sp0)
अणु
	काष्ठा multicall_space mcs;

	mcs = xen_mc_entry(0);
	MULTI_stack_चयन(mcs.mc, __KERNEL_DS, sp0);
	xen_mc_issue(PARAVIRT_LAZY_CPU);
	this_cpu_ग_लिखो(cpu_tss_rw.x86_tss.sp0, sp0);
पूर्ण

#अगर_घोषित CONFIG_X86_IOPL_IOPERM
अटल व्योम xen_invalidate_io_biपंचांगap(व्योम)
अणु
	काष्ठा physdev_set_iobiपंचांगap iobiपंचांगap = अणु
		.biपंचांगap = शून्य,
		.nr_ports = 0,
	पूर्ण;

	native_tss_invalidate_io_biपंचांगap();
	HYPERVISOR_physdev_op(PHYSDEVOP_set_iobiपंचांगap, &iobiपंचांगap);
पूर्ण

अटल व्योम xen_update_io_biपंचांगap(व्योम)
अणु
	काष्ठा physdev_set_iobiपंचांगap iobiपंचांगap;
	काष्ठा tss_काष्ठा *tss = this_cpu_ptr(&cpu_tss_rw);

	native_tss_update_io_biपंचांगap();

	iobiपंचांगap.biपंचांगap = (uपूर्णांक8_t *)(&tss->x86_tss) +
			  tss->x86_tss.io_biपंचांगap_base;
	अगर (tss->x86_tss.io_biपंचांगap_base == IO_BITMAP_OFFSET_INVALID)
		iobiपंचांगap.nr_ports = 0;
	अन्यथा
		iobiपंचांगap.nr_ports = IO_BITMAP_BITS;

	HYPERVISOR_physdev_op(PHYSDEVOP_set_iobiपंचांगap, &iobiपंचांगap);
पूर्ण
#पूर्ण_अगर

अटल व्योम xen_io_delay(व्योम)
अणु
पूर्ण

अटल DEFINE_PER_CPU(अचिन्हित दीर्घ, xen_cr0_value);

अटल अचिन्हित दीर्घ xen_पढ़ो_cr0(व्योम)
अणु
	अचिन्हित दीर्घ cr0 = this_cpu_पढ़ो(xen_cr0_value);

	अगर (unlikely(cr0 == 0)) अणु
		cr0 = native_पढ़ो_cr0();
		this_cpu_ग_लिखो(xen_cr0_value, cr0);
	पूर्ण

	वापस cr0;
पूर्ण

अटल व्योम xen_ग_लिखो_cr0(अचिन्हित दीर्घ cr0)
अणु
	काष्ठा multicall_space mcs;

	this_cpu_ग_लिखो(xen_cr0_value, cr0);

	/* Only pay attention to cr0.TS; everything अन्यथा is
	   ignored. */
	mcs = xen_mc_entry(0);

	MULTI_fpu_taskचयन(mcs.mc, (cr0 & X86_CR0_TS) != 0);

	xen_mc_issue(PARAVIRT_LAZY_CPU);
पूर्ण

अटल व्योम xen_ग_लिखो_cr4(अचिन्हित दीर्घ cr4)
अणु
	cr4 &= ~(X86_CR4_PGE | X86_CR4_PSE | X86_CR4_PCE);

	native_ग_लिखो_cr4(cr4);
पूर्ण

अटल u64 xen_पढ़ो_msr_safe(अचिन्हित पूर्णांक msr, पूर्णांक *err)
अणु
	u64 val;

	अगर (pmu_msr_पढ़ो(msr, &val, err))
		वापस val;

	val = native_पढ़ो_msr_safe(msr, err);
	चयन (msr) अणु
	हाल MSR_IA32_APICBASE:
		val &= ~X2APIC_ENABLE;
		अवरोध;
	पूर्ण
	वापस val;
पूर्ण

अटल पूर्णांक xen_ग_लिखो_msr_safe(अचिन्हित पूर्णांक msr, अचिन्हित low, अचिन्हित high)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक which;
	u64 base;

	ret = 0;

	चयन (msr) अणु
	हाल MSR_FS_BASE:		which = SEGBASE_FS; जाओ set;
	हाल MSR_KERNEL_GS_BASE:	which = SEGBASE_GS_USER; जाओ set;
	हाल MSR_GS_BASE:		which = SEGBASE_GS_KERNEL; जाओ set;

	set:
		base = ((u64)high << 32) | low;
		अगर (HYPERVISOR_set_segment_base(which, base) != 0)
			ret = -EIO;
		अवरोध;

	हाल MSR_STAR:
	हाल MSR_CSTAR:
	हाल MSR_LSTAR:
	हाल MSR_SYSCALL_MASK:
	हाल MSR_IA32_SYSENTER_CS:
	हाल MSR_IA32_SYSENTER_ESP:
	हाल MSR_IA32_SYSENTER_EIP:
		/* Fast syscall setup is all करोne in hypercalls, so
		   these are all ignored.  Stub them out here to stop
		   Xen console noise. */
		अवरोध;

	शेष:
		अगर (!pmu_msr_ग_लिखो(msr, low, high, &ret))
			ret = native_ग_लिखो_msr_safe(msr, low, high);
	पूर्ण

	वापस ret;
पूर्ण

अटल u64 xen_पढ़ो_msr(अचिन्हित पूर्णांक msr)
अणु
	/*
	 * This will silently swallow a #GP from RDMSR.  It may be worth
	 * changing that.
	 */
	पूर्णांक err;

	वापस xen_पढ़ो_msr_safe(msr, &err);
पूर्ण

अटल व्योम xen_ग_लिखो_msr(अचिन्हित पूर्णांक msr, अचिन्हित low, अचिन्हित high)
अणु
	/*
	 * This will silently swallow a #GP from WRMSR.  It may be worth
	 * changing that.
	 */
	xen_ग_लिखो_msr_safe(msr, low, high);
पूर्ण

/* This is called once we have the cpu_possible_mask */
व्योम __init xen_setup_vcpu_info_placement(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		/* Set up direct vCPU id mapping क्रम PV guests. */
		per_cpu(xen_vcpu_id, cpu) = cpu;

		/*
		 * xen_vcpu_setup(cpu) can fail  -- in which हाल it
		 * falls back to the shared_info version क्रम cpus
		 * where xen_vcpu_nr(cpu) < MAX_VIRT_CPUS.
		 *
		 * xen_cpu_up_prepare_pv() handles the rest by failing
		 * them in hotplug.
		 */
		(व्योम) xen_vcpu_setup(cpu);
	पूर्ण

	/*
	 * xen_vcpu_setup managed to place the vcpu_info within the
	 * percpu area क्रम all cpus, so make use of it.
	 */
	अगर (xen_have_vcpu_info_placement) अणु
		pv_ops.irq.save_fl = __PV_IS_CALLEE_SAVE(xen_save_fl_direct);
		pv_ops.irq.irq_disable =
			__PV_IS_CALLEE_SAVE(xen_irq_disable_direct);
		pv_ops.irq.irq_enable =
			__PV_IS_CALLEE_SAVE(xen_irq_enable_direct);
		pv_ops.mmu.पढ़ो_cr2 =
			__PV_IS_CALLEE_SAVE(xen_पढ़ो_cr2_direct);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा pv_info xen_info __initस्थिर = अणु
	.extra_user_64bit_cs = FLAT_USER_CS64,
	.name = "Xen",
पूर्ण;

अटल स्थिर काष्ठा pv_cpu_ops xen_cpu_ops __initस्थिर = अणु
	.cpuid = xen_cpuid,

	.set_debugreg = xen_set_debugreg,
	.get_debugreg = xen_get_debugreg,

	.पढ़ो_cr0 = xen_पढ़ो_cr0,
	.ग_लिखो_cr0 = xen_ग_लिखो_cr0,

	.ग_लिखो_cr4 = xen_ग_लिखो_cr4,

	.wbinvd = native_wbinvd,

	.पढ़ो_msr = xen_पढ़ो_msr,
	.ग_लिखो_msr = xen_ग_लिखो_msr,

	.पढ़ो_msr_safe = xen_पढ़ो_msr_safe,
	.ग_लिखो_msr_safe = xen_ग_लिखो_msr_safe,

	.पढ़ो_pmc = xen_पढ़ो_pmc,

	.load_tr_desc = paravirt_nop,
	.set_ldt = xen_set_ldt,
	.load_gdt = xen_load_gdt,
	.load_idt = xen_load_idt,
	.load_tls = xen_load_tls,
	.load_gs_index = xen_load_gs_index,

	.alloc_ldt = xen_alloc_ldt,
	.मुक्त_ldt = xen_मुक्त_ldt,

	.store_tr = xen_store_tr,

	.ग_लिखो_ldt_entry = xen_ग_लिखो_ldt_entry,
	.ग_लिखो_gdt_entry = xen_ग_लिखो_gdt_entry,
	.ग_लिखो_idt_entry = xen_ग_लिखो_idt_entry,
	.load_sp0 = xen_load_sp0,

#अगर_घोषित CONFIG_X86_IOPL_IOPERM
	.invalidate_io_biपंचांगap = xen_invalidate_io_biपंचांगap,
	.update_io_biपंचांगap = xen_update_io_biपंचांगap,
#पूर्ण_अगर
	.io_delay = xen_io_delay,

	.start_context_चयन = paravirt_start_context_चयन,
	.end_context_चयन = xen_end_context_चयन,
पूर्ण;

अटल व्योम xen_restart(अक्षर *msg)
अणु
	xen_reboot(SHUTDOWN_reboot);
पूर्ण

अटल व्योम xen_machine_halt(व्योम)
अणु
	xen_reboot(SHUTDOWN_घातeroff);
पूर्ण

अटल व्योम xen_machine_घातer_off(व्योम)
अणु
	अगर (pm_घातer_off)
		pm_घातer_off();
	xen_reboot(SHUTDOWN_घातeroff);
पूर्ण

अटल व्योम xen_crash_shutकरोwn(काष्ठा pt_regs *regs)
अणु
	xen_reboot(SHUTDOWN_crash);
पूर्ण

अटल स्थिर काष्ठा machine_ops xen_machine_ops __initस्थिर = अणु
	.restart = xen_restart,
	.halt = xen_machine_halt,
	.घातer_off = xen_machine_घातer_off,
	.shutकरोwn = xen_machine_halt,
	.crash_shutकरोwn = xen_crash_shutकरोwn,
	.emergency_restart = xen_emergency_restart,
पूर्ण;

अटल अचिन्हित अक्षर xen_get_nmi_reason(व्योम)
अणु
	अचिन्हित अक्षर reason = 0;

	/* Conकाष्ठा a value which looks like it came from port 0x61. */
	अगर (test_bit(_XEN_NMIREASON_io_error,
		     &HYPERVISOR_shared_info->arch.nmi_reason))
		reason |= NMI_REASON_IOCHK;
	अगर (test_bit(_XEN_NMIREASON_pci_serr,
		     &HYPERVISOR_shared_info->arch.nmi_reason))
		reason |= NMI_REASON_SERR;

	वापस reason;
पूर्ण

अटल व्योम __init xen_boot_params_init_edd(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_EDD)
	काष्ठा xen_platक्रमm_op op;
	काष्ठा edd_info *edd_info;
	u32 *mbr_signature;
	अचिन्हित nr;
	पूर्णांक ret;

	edd_info = boot_params.eddbuf;
	mbr_signature = boot_params.edd_mbr_sig_buffer;

	op.cmd = XENPF_firmware_info;

	op.u.firmware_info.type = XEN_FW_DISK_INFO;
	क्रम (nr = 0; nr < EDDMAXNR; nr++) अणु
		काष्ठा edd_info *info = edd_info + nr;

		op.u.firmware_info.index = nr;
		info->params.length = माप(info->params);
		set_xen_guest_handle(op.u.firmware_info.u.disk_info.edd_params,
				     &info->params);
		ret = HYPERVISOR_platक्रमm_op(&op);
		अगर (ret)
			अवरोध;

#घोषणा C(x) info->x = op.u.firmware_info.u.disk_info.x
		C(device);
		C(version);
		C(पूर्णांकerface_support);
		C(legacy_max_cylinder);
		C(legacy_max_head);
		C(legacy_sectors_per_track);
#अघोषित C
	पूर्ण
	boot_params.eddbuf_entries = nr;

	op.u.firmware_info.type = XEN_FW_DISK_MBR_SIGNATURE;
	क्रम (nr = 0; nr < EDD_MBR_SIG_MAX; nr++) अणु
		op.u.firmware_info.index = nr;
		ret = HYPERVISOR_platक्रमm_op(&op);
		अगर (ret)
			अवरोध;
		mbr_signature[nr] = op.u.firmware_info.u.disk_mbr_signature.mbr_signature;
	पूर्ण
	boot_params.edd_mbr_sig_buf_entries = nr;
#पूर्ण_अगर
पूर्ण

/*
 * Set up the GDT and segment रेजिस्टरs क्रम -fstack-protector.  Until
 * we करो this, we have to be careful not to call any stack-रक्षित
 * function, which is most of the kernel.
 */
अटल व्योम __init xen_setup_gdt(पूर्णांक cpu)
अणु
	pv_ops.cpu.ग_लिखो_gdt_entry = xen_ग_लिखो_gdt_entry_boot;
	pv_ops.cpu.load_gdt = xen_load_gdt_boot;

	चयन_to_new_gdt(cpu);

	pv_ops.cpu.ग_लिखो_gdt_entry = xen_ग_लिखो_gdt_entry;
	pv_ops.cpu.load_gdt = xen_load_gdt;
पूर्ण

अटल व्योम __init xen_करोm0_set_legacy_features(व्योम)
अणु
	x86_platक्रमm.legacy.rtc = 1;
पूर्ण

/* First C function to be called on Xen boot */
यंत्रlinkage __visible व्योम __init xen_start_kernel(व्योम)
अणु
	काष्ठा physdev_set_iopl set_iopl;
	अचिन्हित दीर्घ initrd_start = 0;
	पूर्णांक rc;

	अगर (!xen_start_info)
		वापस;

	xen_करोमुख्य_type = XEN_PV_DOMAIN;
	xen_start_flags = xen_start_info->flags;

	xen_setup_features();

	/* Install Xen paravirt ops */
	pv_info = xen_info;
	pv_ops.cpu = xen_cpu_ops;
	paravirt_iret = xen_iret;
	xen_init_irq_ops();

	/*
	 * Setup xen_vcpu early because it is needed क्रम
	 * local_irq_disable(), irqs_disabled(), e.g. in prपूर्णांकk().
	 *
	 * Don't करो the full vcpu_info placement stuff until we have
	 * the cpu_possible_mask and a non-dummy shared_info.
	 */
	xen_vcpu_info_reset(0);

	x86_platक्रमm.get_nmi_reason = xen_get_nmi_reason;

	x86_init.resources.memory_setup = xen_memory_setup;
	x86_init.irqs.पूर्णांकr_mode_select	= x86_init_noop;
	x86_init.irqs.पूर्णांकr_mode_init	= x86_init_noop;
	x86_init.oem.arch_setup = xen_arch_setup;
	x86_init.oem.banner = xen_banner;
	x86_init.hyper.init_platक्रमm = xen_pv_init_platक्रमm;
	x86_init.hyper.guest_late_init = xen_pv_guest_late_init;

	/*
	 * Set up some pagetable state beक्रमe starting to set any ptes.
	 */

	xen_setup_machphys_mapping();
	xen_init_mmu_ops();

	/* Prevent unwanted bits from being set in PTEs. */
	__supported_pte_mask &= ~_PAGE_GLOBAL;
	__शेष_kernel_pte_mask &= ~_PAGE_GLOBAL;

	/*
	 * Prevent page tables from being allocated in highmem, even
	 * अगर CONFIG_HIGHPTE is enabled.
	 */
	__userpte_alloc_gfp &= ~__GFP_HIGHMEM;

	/* Get mfn list */
	xen_build_dynamic_phys_to_machine();

	/* Work out अगर we support NX */
	get_cpu_cap(&boot_cpu_data);
	x86_configure_nx();

	/*
	 * Set up kernel GDT and segment रेजिस्टरs, मुख्यly so that
	 * -fstack-protector code can be executed.
	 */
	xen_setup_gdt(0);

	/* Determine भव and physical address sizes */
	get_cpu_address_sizes(&boot_cpu_data);

	/* Let's presume PV guests always boot on vCPU with id 0. */
	per_cpu(xen_vcpu_id, 0) = 0;

	idt_setup_early_handler();

	xen_init_capabilities();

#अगर_घोषित CONFIG_X86_LOCAL_APIC
	/*
	 * set up the basic apic ops.
	 */
	xen_init_apic();
#पूर्ण_अगर

	अगर (xen_feature(XENFEAT_mmu_pt_update_preserve_ad)) अणु
		pv_ops.mmu.ptep_modअगरy_prot_start =
			xen_ptep_modअगरy_prot_start;
		pv_ops.mmu.ptep_modअगरy_prot_commit =
			xen_ptep_modअगरy_prot_commit;
	पूर्ण

	machine_ops = xen_machine_ops;

	/*
	 * The only reliable way to retain the initial address of the
	 * percpu gdt_page is to remember it here, so we can go and
	 * mark it RW later, when the initial percpu area is मुक्तd.
	 */
	xen_initial_gdt = &per_cpu(gdt_page, 0);

	xen_smp_init();

#अगर_घोषित CONFIG_ACPI_NUMA
	/*
	 * The pages we from Xen are not related to machine pages, so
	 * any NUMA inक्रमmation the kernel tries to get from ACPI will
	 * be meaningless.  Prevent it from trying.
	 */
	disable_srat();
#पूर्ण_अगर
	WARN_ON(xen_cpuhp_setup(xen_cpu_up_prepare_pv, xen_cpu_dead_pv));

	local_irq_disable();
	early_boot_irqs_disabled = true;

	xen_raw_console_ग_लिखो("mapping kernel into physical memory\n");
	xen_setup_kernel_pagetable((pgd_t *)xen_start_info->pt_base,
				   xen_start_info->nr_pages);
	xen_reserve_special_pages();

	/*
	 * We used to करो this in xen_arch_setup, but that is too late
	 * on AMD were early_cpu_init (run beक्रमe ->arch_setup()) calls
	 * early_amd_init which pokes 0xcf8 port.
	 */
	set_iopl.iopl = 1;
	rc = HYPERVISOR_physdev_op(PHYSDEVOP_set_iopl, &set_iopl);
	अगर (rc != 0)
		xen_raw_prपूर्णांकk("physdev_op failed %d\n", rc);


	अगर (xen_start_info->mod_start) अणु
	    अगर (xen_start_info->flags & SIF_MOD_START_PFN)
		initrd_start = PFN_PHYS(xen_start_info->mod_start);
	    अन्यथा
		initrd_start = __pa(xen_start_info->mod_start);
	पूर्ण

	/* Poke various useful things पूर्णांकo boot_params */
	boot_params.hdr.type_of_loader = (9 << 4) | 0;
	boot_params.hdr.ramdisk_image = initrd_start;
	boot_params.hdr.ramdisk_size = xen_start_info->mod_len;
	boot_params.hdr.cmd_line_ptr = __pa(xen_start_info->cmd_line);
	boot_params.hdr.hardware_subarch = X86_SUBARCH_XEN;

	अगर (!xen_initial_करोमुख्य()) अणु
		add_preferred_console("xenboot", 0, शून्य);
		अगर (pci_xen)
			x86_init.pci.arch_init = pci_xen_init;
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा करोm0_vga_console_info *info =
			(व्योम *)((अक्षर *)xen_start_info +
				 xen_start_info->console.करोm0.info_off);
		काष्ठा xen_platक्रमm_op op = अणु
			.cmd = XENPF_firmware_info,
			.पूर्णांकerface_version = XENPF_INTERFACE_VERSION,
			.u.firmware_info.type = XEN_FW_KBD_SHIFT_FLAGS,
		पूर्ण;

		x86_platक्रमm.set_legacy_features =
				xen_करोm0_set_legacy_features;
		xen_init_vga(info, xen_start_info->console.करोm0.info_size);
		xen_start_info->console.करोmU.mfn = 0;
		xen_start_info->console.करोmU.evtchn = 0;

		अगर (HYPERVISOR_platक्रमm_op(&op) == 0)
			boot_params.kbd_status = op.u.firmware_info.u.kbd_shअगरt_flags;

		/* Make sure ACS will be enabled */
		pci_request_acs();

		xen_acpi_sleep_रेजिस्टर();

		/* Aव्योम searching क्रम BIOS MP tables */
		x86_init.mpparse.find_smp_config = x86_init_noop;
		x86_init.mpparse.get_smp_config = x86_init_uपूर्णांक_noop;

		xen_boot_params_init_edd();

#अगर_घोषित CONFIG_ACPI
		/*
		 * Disable selecting "Firmware First mode" क्रम correctable
		 * memory errors, as this is the duty of the hypervisor to
		 * decide.
		 */
		acpi_disable_cmcff = 1;
#पूर्ण_अगर
	पूर्ण

	अगर (!boot_params.screen_info.orig_video_isVGA)
		add_preferred_console("tty", 0, शून्य);
	add_preferred_console("hvc", 0, शून्य);
	अगर (boot_params.screen_info.orig_video_isVGA)
		add_preferred_console("tty", 0, शून्य);

#अगर_घोषित CONFIG_PCI
	/* PCI BIOS service won't work from a PV guest. */
	pci_probe &= ~PCI_PROBE_BIOS;
#पूर्ण_अगर
	xen_raw_console_ग_लिखो("about to get started...\n");

	/* We need this क्रम prपूर्णांकk बारtamps */
	xen_setup_runstate_info(0);

	xen_efi_init(&boot_params);

	/* Start the world */
	cr4_init_shaकरोw(); /* 32b kernel करोes this in i386_start_kernel() */
	x86_64_start_reservations((अक्षर *)__pa_symbol(&boot_params));
पूर्ण

अटल पूर्णांक xen_cpu_up_prepare_pv(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक rc;

	अगर (per_cpu(xen_vcpu, cpu) == शून्य)
		वापस -ENODEV;

	xen_setup_समयr(cpu);

	rc = xen_smp_पूर्णांकr_init(cpu);
	अगर (rc) अणु
		WARN(1, "xen_smp_intr_init() for CPU %d failed: %d\n",
		     cpu, rc);
		वापस rc;
	पूर्ण

	rc = xen_smp_पूर्णांकr_init_pv(cpu);
	अगर (rc) अणु
		WARN(1, "xen_smp_intr_init_pv() for CPU %d failed: %d\n",
		     cpu, rc);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xen_cpu_dead_pv(अचिन्हित पूर्णांक cpu)
अणु
	xen_smp_पूर्णांकr_मुक्त(cpu);
	xen_smp_पूर्णांकr_मुक्त_pv(cpu);

	xen_tearकरोwn_समयr(cpu);

	वापस 0;
पूर्ण

अटल uपूर्णांक32_t __init xen_platक्रमm_pv(व्योम)
अणु
	अगर (xen_pv_करोमुख्य())
		वापस xen_cpuid_base();

	वापस 0;
पूर्ण

स्थिर __initस्थिर काष्ठा hypervisor_x86 x86_hyper_xen_pv = अणु
	.name                   = "Xen PV",
	.detect                 = xen_platक्रमm_pv,
	.type			= X86_HYPER_XEN_PV,
	.runसमय.pin_vcpu       = xen_pin_vcpu,
	.ignore_nopv		= true,
पूर्ण;
