<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2005 Intel Corporation
 * 	Venkatesh Pallipadi <venkatesh.pallipadi@पूर्णांकel.com>
 * 	- Added _PDC क्रम SMP C-states on Intel CPUs
 */

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/acpi.h>
#समावेश <linux/cpu.h>
#समावेश <linux/sched.h>

#समावेश <acpi/processor.h>
#समावेश <यंत्र/mरुको.h>
#समावेश <यंत्र/special_insns.h>

/*
 * Initialize bm_flags based on the CPU cache properties
 * On SMP it depends on cache configuration
 * - When cache is not shared among all CPUs, we flush cache
 *   beक्रमe entering C3.
 * - When cache is shared among all CPUs, we use bm_check
 *   mechanism as in UP हाल
 *
 * This routine is called only after all the CPUs are online
 */
व्योम acpi_processor_घातer_init_bm_check(काष्ठा acpi_processor_flags *flags,
					अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpuinfo_x86 *c = &cpu_data(cpu);

	flags->bm_check = 0;
	अगर (num_online_cpus() == 1)
		flags->bm_check = 1;
	अन्यथा अगर (c->x86_venकरोr == X86_VENDOR_INTEL) अणु
		/*
		 * Today all MP CPUs that support C3 share cache.
		 * And caches should not be flushed by software जबतक
		 * entering C3 type state.
		 */
		flags->bm_check = 1;
	पूर्ण

	/*
	 * On all recent Intel platक्रमms, ARB_DISABLE is a nop.
	 * So, set bm_control to zero to indicate that ARB_DISABLE
	 * is not required जबतक entering C3 type state on
	 * P4, Core and beyond CPUs
	 */
	अगर (c->x86_venकरोr == X86_VENDOR_INTEL &&
	    (c->x86 > 0xf || (c->x86 == 6 && c->x86_model >= 0x0f)))
			flags->bm_control = 0;
	/*
	 * For all recent Centaur CPUs, the ucode will make sure that each
	 * core can keep cache coherence with each other जबतक entering C3
	 * type state. So, set bm_check to 1 to indicate that the kernel
	 * करोesn't need to execute a cache flush operation (WBINVD) when
	 * entering C3 type state.
	 */
	अगर (c->x86_venकरोr == X86_VENDOR_CENTAUR) अणु
		अगर (c->x86 > 6 || (c->x86 == 6 && c->x86_model == 0x0f &&
		    c->x86_stepping >= 0x0e))
			flags->bm_check = 1;
	पूर्ण

	अगर (c->x86_venकरोr == X86_VENDOR_ZHAOXIN) अणु
		/*
		 * All Zhaoxin CPUs that support C3 share cache.
		 * And caches should not be flushed by software जबतक
		 * entering C3 type state.
		 */
		flags->bm_check = 1;
		/*
		 * On all recent Zhaoxin platक्रमms, ARB_DISABLE is a nop.
		 * So, set bm_control to zero to indicate that ARB_DISABLE
		 * is not required जबतक entering C3 type state.
		 */
		flags->bm_control = 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(acpi_processor_घातer_init_bm_check);

/* The code below handles cstate entry with monitor-mरुको pair on Intel*/

काष्ठा cstate_entry अणु
	काष्ठा अणु
		अचिन्हित पूर्णांक eax;
		अचिन्हित पूर्णांक ecx;
	पूर्ण states[ACPI_PROCESSOR_MAX_POWER];
पूर्ण;
अटल काष्ठा cstate_entry __percpu *cpu_cstate_entry;	/* per CPU ptr */

अटल लघु mरुको_supported[ACPI_PROCESSOR_MAX_POWER];

#घोषणा NATIVE_CSTATE_BEYOND_HALT	(2)

अटल दीर्घ acpi_processor_ffh_cstate_probe_cpu(व्योम *_cx)
अणु
	काष्ठा acpi_processor_cx *cx = _cx;
	दीर्घ retval;
	अचिन्हित पूर्णांक eax, ebx, ecx, edx;
	अचिन्हित पूर्णांक edx_part;
	अचिन्हित पूर्णांक cstate_type; /* C-state type and not ACPI C-state type */
	अचिन्हित पूर्णांक num_cstate_subtype;

	cpuid(CPUID_MWAIT_LEAF, &eax, &ebx, &ecx, &edx);

	/* Check whether this particular cx_type (in CST) is supported or not */
	cstate_type = ((cx->address >> MWAIT_SUBSTATE_SIZE) &
			MWAIT_CSTATE_MASK) + 1;
	edx_part = edx >> (cstate_type * MWAIT_SUBSTATE_SIZE);
	num_cstate_subtype = edx_part & MWAIT_SUBSTATE_MASK;

	retval = 0;
	/* If the HW करोes not support any sub-states in this C-state */
	अगर (num_cstate_subtype == 0) अणु
		pr_warn(FW_BUG "ACPI MWAIT C-state 0x%x not supported by HW (0x%x)\n",
				cx->address, edx_part);
		retval = -1;
		जाओ out;
	पूर्ण

	/* mरुको ecx extensions INTERRUPT_BREAK should be supported क्रम C2/C3 */
	अगर (!(ecx & CPUID5_ECX_EXTENSIONS_SUPPORTED) ||
	    !(ecx & CPUID5_ECX_INTERRUPT_BREAK)) अणु
		retval = -1;
		जाओ out;
	पूर्ण

	अगर (!mरुको_supported[cstate_type]) अणु
		mरुको_supported[cstate_type] = 1;
		prपूर्णांकk(KERN_DEBUG
			"Monitor-Mwait will be used to enter C-%d state\n",
			cx->type);
	पूर्ण
	snम_लिखो(cx->desc,
			ACPI_CX_DESC_LEN, "ACPI FFH MWAIT 0x%x",
			cx->address);
out:
	वापस retval;
पूर्ण

पूर्णांक acpi_processor_ffh_cstate_probe(अचिन्हित पूर्णांक cpu,
		काष्ठा acpi_processor_cx *cx, काष्ठा acpi_घातer_रेजिस्टर *reg)
अणु
	काष्ठा cstate_entry *percpu_entry;
	काष्ठा cpuinfo_x86 *c = &cpu_data(cpu);
	दीर्घ retval;

	अगर (!cpu_cstate_entry || c->cpuid_level < CPUID_MWAIT_LEAF)
		वापस -1;

	अगर (reg->bit_offset != NATIVE_CSTATE_BEYOND_HALT)
		वापस -1;

	percpu_entry = per_cpu_ptr(cpu_cstate_entry, cpu);
	percpu_entry->states[cx->index].eax = 0;
	percpu_entry->states[cx->index].ecx = 0;

	/* Make sure we are running on right CPU */

	retval = call_on_cpu(cpu, acpi_processor_ffh_cstate_probe_cpu, cx,
			     false);
	अगर (retval == 0) अणु
		/* Use the hपूर्णांक in CST */
		percpu_entry->states[cx->index].eax = cx->address;
		percpu_entry->states[cx->index].ecx = MWAIT_ECX_INTERRUPT_BREAK;
	पूर्ण

	/*
	 * For _CST FFH on Intel, अगर GAS.access_size bit 1 is cleared,
	 * then we should skip checking BM_STS क्रम this C-state.
	 * ref: "Intel Processor Vendor-Specific ACPI Interface Specification"
	 */
	अगर ((c->x86_venकरोr == X86_VENDOR_INTEL) && !(reg->access_size & 0x2))
		cx->bm_sts_skip = 1;

	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_processor_ffh_cstate_probe);

व्योम __cpuidle acpi_processor_ffh_cstate_enter(काष्ठा acpi_processor_cx *cx)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	काष्ठा cstate_entry *percpu_entry;

	percpu_entry = per_cpu_ptr(cpu_cstate_entry, cpu);
	mरुको_idle_with_hपूर्णांकs(percpu_entry->states[cx->index].eax,
	                      percpu_entry->states[cx->index].ecx);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_processor_ffh_cstate_enter);

अटल पूर्णांक __init ffh_cstate_init(व्योम)
अणु
	काष्ठा cpuinfo_x86 *c = &boot_cpu_data;

	अगर (c->x86_venकरोr != X86_VENDOR_INTEL &&
	    c->x86_venकरोr != X86_VENDOR_AMD)
		वापस -1;

	cpu_cstate_entry = alloc_percpu(काष्ठा cstate_entry);
	वापस 0;
पूर्ण

अटल व्योम __निकास ffh_cstate_निकास(व्योम)
अणु
	मुक्त_percpu(cpu_cstate_entry);
	cpu_cstate_entry = शून्य;
पूर्ण

arch_initcall(ffh_cstate_init);
__निकासcall(ffh_cstate_निकास);
