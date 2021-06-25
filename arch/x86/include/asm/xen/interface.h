<शैली गुरु>
/******************************************************************************
 * arch-x86_32.h
 *
 * Guest OS पूर्णांकerface to x86 Xen.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this software and associated करोcumentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modअगरy, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Copyright (c) 2004-2006, K A Fraser
 */

#अगर_अघोषित _ASM_X86_XEN_INTERFACE_H
#घोषणा _ASM_X86_XEN_INTERFACE_H

/*
 * XEN_GUEST_HANDLE represents a guest poपूर्णांकer, when passed as a field
 * in a काष्ठा in memory.
 * XEN_GUEST_HANDLE_PARAM represent a guest poपूर्णांकer, when passed as an
 * hypercall argument.
 * XEN_GUEST_HANDLE_PARAM and XEN_GUEST_HANDLE are the same on X86 but
 * they might not be on other architectures.
 */
#अगर_घोषित __XEN__
#घोषणा __DEFINE_GUEST_HANDLE(name, type) \
    प्रकार काष्ठा अणु type *p; पूर्ण __guest_handle_ ## name
#अन्यथा
#घोषणा __DEFINE_GUEST_HANDLE(name, type) \
    प्रकार type * __guest_handle_ ## name
#पूर्ण_अगर

#घोषणा DEFINE_GUEST_HANDLE_STRUCT(name) \
	__DEFINE_GUEST_HANDLE(name, काष्ठा name)
#घोषणा DEFINE_GUEST_HANDLE(name) __DEFINE_GUEST_HANDLE(name, name)
#घोषणा GUEST_HANDLE(name)        __guest_handle_ ## name

#अगर_घोषित __XEN__
#अगर defined(__i386__)
#घोषणा set_xen_guest_handle(hnd, val)			\
	करो अणु						\
		अगर (माप(hnd) == 8)			\
			*(uपूर्णांक64_t *)&(hnd) = 0;	\
		(hnd).p = val;				\
	पूर्ण जबतक (0)
#या_अगर defined(__x86_64__)
#घोषणा set_xen_guest_handle(hnd, val)	करो अणु (hnd).p = val; पूर्ण जबतक (0)
#पूर्ण_अगर
#अन्यथा
#अगर defined(__i386__)
#घोषणा set_xen_guest_handle(hnd, val)			\
	करो अणु						\
		अगर (माप(hnd) == 8)			\
			*(uपूर्णांक64_t *)&(hnd) = 0;	\
		(hnd) = val;				\
	पूर्ण जबतक (0)
#या_अगर defined(__x86_64__)
#घोषणा set_xen_guest_handle(hnd, val)	करो अणु (hnd) = val; पूर्ण जबतक (0)
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__
/* Explicitly size पूर्णांकegers that represent pfns in the खुला पूर्णांकerface
 * with Xen so that on ARM we can have one ABI that works क्रम 32 and 64
 * bit guests. */
प्रकार अचिन्हित दीर्घ xen_pfn_t;
#घोषणा PRI_xen_pfn "lx"
प्रकार अचिन्हित दीर्घ xen_uदीर्घ_t;
#घोषणा PRI_xen_uदीर्घ "lx"
प्रकार दीर्घ xen_दीर्घ_t;
#घोषणा PRI_xen_दीर्घ "lx"

/* Guest handles क्रम primitive C types. */
__DEFINE_GUEST_HANDLE(uअक्षर, अचिन्हित अक्षर);
__DEFINE_GUEST_HANDLE(uपूर्णांक,  अचिन्हित पूर्णांक);
DEFINE_GUEST_HANDLE(अक्षर);
DEFINE_GUEST_HANDLE(पूर्णांक);
DEFINE_GUEST_HANDLE(व्योम);
DEFINE_GUEST_HANDLE(uपूर्णांक64_t);
DEFINE_GUEST_HANDLE(uपूर्णांक32_t);
DEFINE_GUEST_HANDLE(xen_pfn_t);
DEFINE_GUEST_HANDLE(xen_uदीर्घ_t);
#पूर्ण_अगर

#अगर_अघोषित HYPERVISOR_VIRT_START
#घोषणा HYPERVISOR_VIRT_START mk_अचिन्हित_दीर्घ(__HYPERVISOR_VIRT_START)
#पूर्ण_अगर

#घोषणा MACH2PHYS_VIRT_START  mk_अचिन्हित_दीर्घ(__MACH2PHYS_VIRT_START)
#घोषणा MACH2PHYS_VIRT_END    mk_अचिन्हित_दीर्घ(__MACH2PHYS_VIRT_END)
#घोषणा MACH2PHYS_NR_ENTRIES  ((MACH2PHYS_VIRT_END-MACH2PHYS_VIRT_START)>>__MACH2PHYS_SHIFT)

/* Maximum number of भव CPUs in multi-processor guests. */
#घोषणा MAX_VIRT_CPUS 32

/*
 * SEGMENT DESCRIPTOR TABLES
 */
/*
 * A number of GDT entries are reserved by Xen. These are not situated at the
 * start of the GDT because some stupid OSes export hard-coded selector values
 * in their ABI. These hard-coded values are always near the start of the GDT,
 * so Xen places itself out of the way, at the far end of the GDT.
 *
 * NB The LDT is set using the MMUEXT_SET_LDT op of HYPERVISOR_mmuext_op
 */
#घोषणा FIRST_RESERVED_GDT_PAGE  14
#घोषणा FIRST_RESERVED_GDT_BYTE  (FIRST_RESERVED_GDT_PAGE * 4096)
#घोषणा FIRST_RESERVED_GDT_ENTRY (FIRST_RESERVED_GDT_BYTE / 8)

/*
 * Send an array of these to HYPERVISOR_set_trap_table().
 * Terminate the array with a sentinel entry, with traps[].address==0.
 * The privilege level specअगरies which modes may enter a trap via a software
 * पूर्णांकerrupt. On x86/64, since rings 1 and 2 are unavailable, we allocate
 * privilege levels as follows:
 *  Level == 0: No one may enter
 *  Level == 1: Kernel may enter
 *  Level == 2: Kernel may enter
 *  Level == 3: Everyone may enter
 */
#घोषणा TI_GET_DPL(_ti)		((_ti)->flags & 3)
#घोषणा TI_GET_IF(_ti)		((_ti)->flags & 4)
#घोषणा TI_SET_DPL(_ti, _dpl)	((_ti)->flags |= (_dpl))
#घोषणा TI_SET_IF(_ti, _अगर)	((_ti)->flags |= ((!!(_अगर))<<2))

#अगर_अघोषित __ASSEMBLY__
काष्ठा trap_info अणु
    uपूर्णांक8_t       vector;  /* exception vector                              */
    uपूर्णांक8_t       flags;   /* 0-3: privilege level; 4: clear event enable?  */
    uपूर्णांक16_t      cs;      /* code selector                                 */
    अचिन्हित दीर्घ address; /* code offset                                   */
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(trap_info);

काष्ठा arch_shared_info अणु
	/*
	 * Number of valid entries in the p2m table(s) anchored at
	 * pfn_to_mfn_frame_list_list and/or p2m_vaddr.
	 */
	अचिन्हित दीर्घ max_pfn;
	/*
	 * Frame containing list of mfns containing list of mfns containing p2m.
	 * A value of 0 indicates it has not yet been set up, ~0 indicates it
	 * has been set to invalid e.g. due to the p2m being too large क्रम the
	 * 3-level p2m tree. In this हाल the linear mapper p2m list anchored
	 * at p2m_vaddr is to be used.
	 */
	xen_pfn_t pfn_to_mfn_frame_list_list;
	अचिन्हित दीर्घ nmi_reason;
	/*
	 * Following three fields are valid अगर p2m_cr3 contains a value
	 * dअगरferent from 0.
	 * p2m_cr3 is the root of the address space where p2m_vaddr is valid.
	 * p2m_cr3 is in the same क्रमmat as a cr3 value in the vcpu रेजिस्टर
	 * state and holds the folded machine frame number (via xen_pfn_to_cr3)
	 * of a L3 or L4 page table.
	 * p2m_vaddr holds the भव address of the linear p2m list. All
	 * entries in the range [0...max_pfn[ are accessible via this poपूर्णांकer.
	 * p2m_generation will be incremented by the guest beक्रमe and after each
	 * change of the mappings of the p2m list. p2m_generation starts at 0
	 * and a value with the least signअगरicant bit set indicates that a
	 * mapping update is in progress. This allows guest बाह्यal software
	 * (e.g. in Dom0) to verअगरy that पढ़ो mappings are consistent and
	 * whether they have changed since the last check.
	 * Modअगरying a p2m element in the linear p2m list is allowed via an
	 * atomic ग_लिखो only.
	 */
	अचिन्हित दीर्घ p2m_cr3;		/* cr3 value of the p2m address space */
	अचिन्हित दीर्घ p2m_vaddr;	/* भव address of the p2m list */
	अचिन्हित दीर्घ p2m_generation;	/* generation count of p2m mapping */
#अगर_घोषित CONFIG_X86_32
	uपूर्णांक32_t wc_sec_hi;
#पूर्ण_अगर
पूर्ण;
#पूर्ण_अगर	/* !__ASSEMBLY__ */

#अगर_घोषित CONFIG_X86_32
#समावेश <यंत्र/xen/पूर्णांकerface_32.h>
#अन्यथा
#समावेश <यंत्र/xen/पूर्णांकerface_64.h>
#पूर्ण_अगर

#समावेश <यंत्र/pvघड़ी-abi.h>

#अगर_अघोषित __ASSEMBLY__
/*
 * The following is all CPU context. Note that the fpu_ctxt block is filled
 * in by FXSAVE अगर the CPU has feature FXSR; otherwise FSAVE is used.
 *
 * Also note that when calling DOMCTL_setvcpucontext and VCPU_initialise
 * क्रम HVM and PVH guests, not all inक्रमmation in this काष्ठाure is updated:
 *
 * - For HVM guests, the काष्ठाures पढ़ो include: fpu_ctxt (अगर
 * VGCT_I387_VALID is set), flags, user_regs, debugreg[*]
 *
 * - PVH guests are the same as HVM guests, but additionally use ctrlreg[3] to
 * set cr3. All other fields not used should be set to 0.
 */
काष्ठा vcpu_guest_context अणु
    /* FPU रेजिस्टरs come first so they can be aligned क्रम FXSAVE/FXRSTOR. */
    काष्ठा अणु अक्षर x[512]; पूर्ण fpu_ctxt;       /* User-level FPU रेजिस्टरs     */
#घोषणा VGCF_I387_VALID                (1<<0)
#घोषणा VGCF_IN_KERNEL                 (1<<2)
#घोषणा _VGCF_i387_valid               0
#घोषणा VGCF_i387_valid                (1<<_VGCF_i387_valid)
#घोषणा _VGCF_in_kernel                2
#घोषणा VGCF_in_kernel                 (1<<_VGCF_in_kernel)
#घोषणा _VGCF_failsafe_disables_events 3
#घोषणा VGCF_failsafe_disables_events  (1<<_VGCF_failsafe_disables_events)
#घोषणा _VGCF_syscall_disables_events  4
#घोषणा VGCF_syscall_disables_events   (1<<_VGCF_syscall_disables_events)
#घोषणा _VGCF_online                   5
#घोषणा VGCF_online                    (1<<_VGCF_online)
    अचिन्हित दीर्घ flags;                    /* VGCF_* flags                 */
    काष्ठा cpu_user_regs user_regs;         /* User-level CPU रेजिस्टरs     */
    काष्ठा trap_info trap_ctxt[256];        /* Virtual IDT                  */
    अचिन्हित दीर्घ ldt_base, ldt_ents;       /* LDT (linear address, # ents) */
    अचिन्हित दीर्घ gdt_frames[16], gdt_ents; /* GDT (machine frames, # ents) */
    अचिन्हित दीर्घ kernel_ss, kernel_sp;     /* Virtual TSS (only SS1/SP1)   */
    /* NB. User pagetable on x86/64 is placed in ctrlreg[1]. */
    अचिन्हित दीर्घ ctrlreg[8];               /* CR0-CR7 (control रेजिस्टरs)  */
    अचिन्हित दीर्घ debugreg[8];              /* DB0-DB7 (debug रेजिस्टरs)    */
#अगर_घोषित __i386__
    अचिन्हित दीर्घ event_callback_cs;        /* CS:EIP of event callback     */
    अचिन्हित दीर्घ event_callback_eip;
    अचिन्हित दीर्घ failsafe_callback_cs;     /* CS:EIP of failsafe callback  */
    अचिन्हित दीर्घ failsafe_callback_eip;
#अन्यथा
    अचिन्हित दीर्घ event_callback_eip;
    अचिन्हित दीर्घ failsafe_callback_eip;
    अचिन्हित दीर्घ syscall_callback_eip;
#पूर्ण_अगर
    अचिन्हित दीर्घ vm_assist;                /* VMASST_TYPE_* biपंचांगap */
#अगर_घोषित __x86_64__
    /* Segment base addresses. */
    uपूर्णांक64_t      fs_base;
    uपूर्णांक64_t      gs_base_kernel;
    uपूर्णांक64_t      gs_base_user;
#पूर्ण_अगर
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(vcpu_guest_context);

/* AMD PMU रेजिस्टरs and काष्ठाures */
काष्ठा xen_pmu_amd_ctxt अणु
	/*
	 * Offsets to counter and control MSRs (relative to xen_pmu_arch.c.amd).
	 * For PV(H) guests these fields are RO.
	 */
	uपूर्णांक32_t counters;
	uपूर्णांक32_t ctrls;

	/* Counter MSRs */
#अगर defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
	uपूर्णांक64_t regs[];
#या_अगर defined(__GNUC__)
	uपूर्णांक64_t regs[0];
#पूर्ण_अगर
पूर्ण;

/* Intel PMU रेजिस्टरs and काष्ठाures */
काष्ठा xen_pmu_cntr_pair अणु
	uपूर्णांक64_t counter;
	uपूर्णांक64_t control;
पूर्ण;

काष्ठा xen_pmu_पूर्णांकel_ctxt अणु
	/*
	 * Offsets to fixed and architectural counter MSRs (relative to
	 * xen_pmu_arch.c.पूर्णांकel).
	 * For PV(H) guests these fields are RO.
	 */
	uपूर्णांक32_t fixed_counters;
	uपूर्णांक32_t arch_counters;

	/* PMU रेजिस्टरs */
	uपूर्णांक64_t global_ctrl;
	uपूर्णांक64_t global_ovf_ctrl;
	uपूर्णांक64_t global_status;
	uपूर्णांक64_t fixed_ctrl;
	uपूर्णांक64_t ds_area;
	uपूर्णांक64_t pebs_enable;
	uपूर्णांक64_t debugctl;

	/* Fixed and architectural counter MSRs */
#अगर defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
	uपूर्णांक64_t regs[];
#या_अगर defined(__GNUC__)
	uपूर्णांक64_t regs[0];
#पूर्ण_अगर
पूर्ण;

/* Sampled करोमुख्य's रेजिस्टरs */
काष्ठा xen_pmu_regs अणु
	uपूर्णांक64_t ip;
	uपूर्णांक64_t sp;
	uपूर्णांक64_t flags;
	uपूर्णांक16_t cs;
	uपूर्णांक16_t ss;
	uपूर्णांक8_t cpl;
	uपूर्णांक8_t pad[3];
पूर्ण;

/* PMU flags */
#घोषणा PMU_CACHED	   (1<<0) /* PMU MSRs are cached in the context */
#घोषणा PMU_SAMPLE_USER	   (1<<1) /* Sample is from user or kernel mode */
#घोषणा PMU_SAMPLE_REAL	   (1<<2) /* Sample is from realmode */
#घोषणा PMU_SAMPLE_PV	   (1<<3) /* Sample from a PV guest */

/*
 * Architecture-specअगरic inक्रमmation describing state of the processor at
 * the समय of PMU पूर्णांकerrupt.
 * Fields of this काष्ठाure marked as RW क्रम guest should only be written by
 * the guest when PMU_CACHED bit in pmu_flags is set (which is करोne by the
 * hypervisor during PMU पूर्णांकerrupt). Hypervisor will पढ़ो updated data in
 * XENPMU_flush hypercall and clear PMU_CACHED bit.
 */
काष्ठा xen_pmu_arch अणु
	जोड़ अणु
		/*
		 * Processor's रेजिस्टरs at the समय of पूर्णांकerrupt.
		 * WO क्रम hypervisor, RO क्रम guests.
		 */
		काष्ठा xen_pmu_regs regs;
		/*
		 * Padding क्रम adding new रेजिस्टरs to xen_pmu_regs in
		 * the future
		 */
#घोषणा XENPMU_REGS_PAD_SZ  64
		uपूर्णांक8_t pad[XENPMU_REGS_PAD_SZ];
	पूर्ण r;

	/* WO क्रम hypervisor, RO क्रम guest */
	uपूर्णांक64_t pmu_flags;

	/*
	 * APIC LVTPC रेजिस्टर.
	 * RW क्रम both hypervisor and guest.
	 * Only APIC_LVT_MASKED bit is loaded by the hypervisor पूर्णांकo hardware
	 * during XENPMU_flush or XENPMU_lvtpc_set.
	 */
	जोड़ अणु
		uपूर्णांक32_t lapic_lvtpc;
		uपूर्णांक64_t pad;
	पूर्ण l;

	/*
	 * Venकरोr-specअगरic PMU रेजिस्टरs.
	 * RW क्रम both hypervisor and guest (see exceptions above).
	 * Guest's updates to this field are verअगरied and then loaded by the
	 * hypervisor पूर्णांकo hardware during XENPMU_flush
	 */
	जोड़ अणु
		काष्ठा xen_pmu_amd_ctxt amd;
		काष्ठा xen_pmu_पूर्णांकel_ctxt पूर्णांकel;

		/*
		 * Padding क्रम contexts (fixed parts only, करोes not include
		 * MSR banks that are specअगरied by offsets)
		 */
#घोषणा XENPMU_CTXT_PAD_SZ  128
		uपूर्णांक8_t pad[XENPMU_CTXT_PAD_SZ];
	पूर्ण c;
पूर्ण;

#पूर्ण_अगर	/* !__ASSEMBLY__ */

/*
 * Prefix क्रमces emulation of some non-trapping inकाष्ठाions.
 * Currently only CPUID.
 */
#समावेश <यंत्र/emulate_prefix.h>

#घोषणा XEN_EMULATE_PREFIX __ASM_FORM(.byte __XEN_EMULATE_PREFIX ;)
#घोषणा XEN_CPUID          XEN_EMULATE_PREFIX __ASM_FORM(cpuid)

#पूर्ण_अगर /* _ASM_X86_XEN_INTERFACE_H */
