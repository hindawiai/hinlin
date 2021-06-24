<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * tools/testing/selftests/kvm/include/x86_64/processor.h
 *
 * Copyright (C) 2018, Google LLC.
 */

#अगर_अघोषित SELFTEST_KVM_PROCESSOR_H
#घोषणा SELFTEST_KVM_PROCESSOR_H

#समावेश <निश्चित.स>
#समावेश <मानक_निवेशt.h>

#समावेश <यंत्र/msr-index.h>

#घोषणा X86_EFLAGS_FIXED	 (1u << 1)

#घोषणा X86_CR4_VME		(1ul << 0)
#घोषणा X86_CR4_PVI		(1ul << 1)
#घोषणा X86_CR4_TSD		(1ul << 2)
#घोषणा X86_CR4_DE		(1ul << 3)
#घोषणा X86_CR4_PSE		(1ul << 4)
#घोषणा X86_CR4_PAE		(1ul << 5)
#घोषणा X86_CR4_MCE		(1ul << 6)
#घोषणा X86_CR4_PGE		(1ul << 7)
#घोषणा X86_CR4_PCE		(1ul << 8)
#घोषणा X86_CR4_OSFXSR		(1ul << 9)
#घोषणा X86_CR4_OSXMMEXCPT	(1ul << 10)
#घोषणा X86_CR4_UMIP		(1ul << 11)
#घोषणा X86_CR4_LA57		(1ul << 12)
#घोषणा X86_CR4_VMXE		(1ul << 13)
#घोषणा X86_CR4_SMXE		(1ul << 14)
#घोषणा X86_CR4_FSGSBASE	(1ul << 16)
#घोषणा X86_CR4_PCIDE		(1ul << 17)
#घोषणा X86_CR4_OSXSAVE		(1ul << 18)
#घोषणा X86_CR4_SMEP		(1ul << 20)
#घोषणा X86_CR4_SMAP		(1ul << 21)
#घोषणा X86_CR4_PKE		(1ul << 22)

/* CPUID.1.ECX */
#घोषणा CPUID_VMX		(1ul << 5)
#घोषणा CPUID_SMX		(1ul << 6)
#घोषणा CPUID_PCID		(1ul << 17)
#घोषणा CPUID_XSAVE		(1ul << 26)

/* CPUID.7.EBX */
#घोषणा CPUID_FSGSBASE		(1ul << 0)
#घोषणा CPUID_SMEP		(1ul << 7)
#घोषणा CPUID_SMAP		(1ul << 20)

/* CPUID.7.ECX */
#घोषणा CPUID_UMIP		(1ul << 2)
#घोषणा CPUID_PKU		(1ul << 3)
#घोषणा CPUID_LA57		(1ul << 16)

#घोषणा UNEXPECTED_VECTOR_PORT 0xfff0u

/* General Registers in 64-Bit Mode */
काष्ठा gpr64_regs अणु
	u64 rax;
	u64 rcx;
	u64 rdx;
	u64 rbx;
	u64 rsp;
	u64 rbp;
	u64 rsi;
	u64 rdi;
	u64 r8;
	u64 r9;
	u64 r10;
	u64 r11;
	u64 r12;
	u64 r13;
	u64 r14;
	u64 r15;
पूर्ण;

काष्ठा desc64 अणु
	uपूर्णांक16_t limit0;
	uपूर्णांक16_t base0;
	अचिन्हित base1:8, type:4, s:1, dpl:2, p:1;
	अचिन्हित limit1:4, avl:1, l:1, db:1, g:1, base2:8;
	uपूर्णांक32_t base3;
	uपूर्णांक32_t zero1;
पूर्ण __attribute__((packed));

काष्ठा desc_ptr अणु
	uपूर्णांक16_t size;
	uपूर्णांक64_t address;
पूर्ण __attribute__((packed));

अटल अंतरभूत uपूर्णांक64_t get_desc64_base(स्थिर काष्ठा desc64 *desc)
अणु
	वापस ((uपूर्णांक64_t)desc->base3 << 32) |
		(desc->base0 | ((desc->base1) << 16) | ((desc->base2) << 24));
पूर्ण

अटल अंतरभूत uपूर्णांक64_t rdtsc(व्योम)
अणु
	uपूर्णांक32_t eax, edx;
	uपूर्णांक64_t tsc_val;
	/*
	 * The lfence is to रुको (on Intel CPUs) until all previous
	 * inकाष्ठाions have been executed. If software requires RDTSC to be
	 * executed prior to execution of any subsequent inकाष्ठाion, it can
	 * execute LFENCE immediately after RDTSC
	 */
	__यंत्र__ __अस्थिर__("lfence; rdtsc; lfence" : "=a"(eax), "=d"(edx));
	tsc_val = ((uपूर्णांक64_t)edx) << 32 | eax;
	वापस tsc_val;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t rdtscp(uपूर्णांक32_t *aux)
अणु
	uपूर्णांक32_t eax, edx;

	__यंत्र__ __अस्थिर__("rdtscp" : "=a"(eax), "=d"(edx), "=c"(*aux));
	वापस ((uपूर्णांक64_t)edx) << 32 | eax;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t rdmsr(uपूर्णांक32_t msr)
अणु
	uपूर्णांक32_t a, d;

	__यंत्र__ __अस्थिर__("rdmsr" : "=a"(a), "=d"(d) : "c"(msr) : "memory");

	वापस a | ((uपूर्णांक64_t) d << 32);
पूर्ण

अटल अंतरभूत व्योम wrmsr(uपूर्णांक32_t msr, uपूर्णांक64_t value)
अणु
	uपूर्णांक32_t a = value;
	uपूर्णांक32_t d = value >> 32;

	__यंत्र__ __अस्थिर__("wrmsr" :: "a"(a), "d"(d), "c"(msr) : "memory");
पूर्ण


अटल अंतरभूत uपूर्णांक16_t inw(uपूर्णांक16_t port)
अणु
	uपूर्णांक16_t पंचांगp;

	__यंत्र__ __अस्थिर__("in %%dx, %%ax"
		: /* output */ "=a" (पंचांगp)
		: /* input */ "d" (port));

	वापस पंचांगp;
पूर्ण

अटल अंतरभूत uपूर्णांक16_t get_es(व्योम)
अणु
	uपूर्णांक16_t es;

	__यंत्र__ __अस्थिर__("mov %%es, %[es]"
			     : /* output */ [es]"=rm"(es));
	वापस es;
पूर्ण

अटल अंतरभूत uपूर्णांक16_t get_cs(व्योम)
अणु
	uपूर्णांक16_t cs;

	__यंत्र__ __अस्थिर__("mov %%cs, %[cs]"
			     : /* output */ [cs]"=rm"(cs));
	वापस cs;
पूर्ण

अटल अंतरभूत uपूर्णांक16_t get_ss(व्योम)
अणु
	uपूर्णांक16_t ss;

	__यंत्र__ __अस्थिर__("mov %%ss, %[ss]"
			     : /* output */ [ss]"=rm"(ss));
	वापस ss;
पूर्ण

अटल अंतरभूत uपूर्णांक16_t get_ds(व्योम)
अणु
	uपूर्णांक16_t ds;

	__यंत्र__ __अस्थिर__("mov %%ds, %[ds]"
			     : /* output */ [ds]"=rm"(ds));
	वापस ds;
पूर्ण

अटल अंतरभूत uपूर्णांक16_t get_fs(व्योम)
अणु
	uपूर्णांक16_t fs;

	__यंत्र__ __अस्थिर__("mov %%fs, %[fs]"
			     : /* output */ [fs]"=rm"(fs));
	वापस fs;
पूर्ण

अटल अंतरभूत uपूर्णांक16_t get_gs(व्योम)
अणु
	uपूर्णांक16_t gs;

	__यंत्र__ __अस्थिर__("mov %%gs, %[gs]"
			     : /* output */ [gs]"=rm"(gs));
	वापस gs;
पूर्ण

अटल अंतरभूत uपूर्णांक16_t get_tr(व्योम)
अणु
	uपूर्णांक16_t tr;

	__यंत्र__ __अस्थिर__("str %[tr]"
			     : /* output */ [tr]"=rm"(tr));
	वापस tr;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t get_cr0(व्योम)
अणु
	uपूर्णांक64_t cr0;

	__यंत्र__ __अस्थिर__("mov %%cr0, %[cr0]"
			     : /* output */ [cr0]"=r"(cr0));
	वापस cr0;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t get_cr3(व्योम)
अणु
	uपूर्णांक64_t cr3;

	__यंत्र__ __अस्थिर__("mov %%cr3, %[cr3]"
			     : /* output */ [cr3]"=r"(cr3));
	वापस cr3;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t get_cr4(व्योम)
अणु
	uपूर्णांक64_t cr4;

	__यंत्र__ __अस्थिर__("mov %%cr4, %[cr4]"
			     : /* output */ [cr4]"=r"(cr4));
	वापस cr4;
पूर्ण

अटल अंतरभूत व्योम set_cr4(uपूर्णांक64_t val)
अणु
	__यंत्र__ __अस्थिर__("mov %0, %%cr4" : : "r" (val) : "memory");
पूर्ण

अटल अंतरभूत काष्ठा desc_ptr get_gdt(व्योम)
अणु
	काष्ठा desc_ptr gdt;
	__यंत्र__ __अस्थिर__("sgdt %[gdt]"
			     : /* output */ [gdt]"=m"(gdt));
	वापस gdt;
पूर्ण

अटल अंतरभूत काष्ठा desc_ptr get_idt(व्योम)
अणु
	काष्ठा desc_ptr idt;
	__यंत्र__ __अस्थिर__("sidt %[idt]"
			     : /* output */ [idt]"=m"(idt));
	वापस idt;
पूर्ण

अटल अंतरभूत व्योम outl(uपूर्णांक16_t port, uपूर्णांक32_t value)
अणु
	__यंत्र__ __अस्थिर__("outl %%eax, %%dx" : : "d"(port), "a"(value));
पूर्ण

अटल अंतरभूत व्योम cpuid(uपूर्णांक32_t *eax, uपूर्णांक32_t *ebx,
			 uपूर्णांक32_t *ecx, uपूर्णांक32_t *edx)
अणु
	/* ecx is often an input as well as an output. */
	यंत्र अस्थिर("cpuid"
	    : "=a" (*eax),
	      "=b" (*ebx),
	      "=c" (*ecx),
	      "=d" (*edx)
	    : "0" (*eax), "2" (*ecx)
	    : "memory");
पूर्ण

#घोषणा SET_XMM(__var, __xmm) \
	यंत्र अस्थिर("movq %0, %%"#__xmm : : "r"(__var) : #__xmm)

अटल अंतरभूत व्योम set_xmm(पूर्णांक n, अचिन्हित दीर्घ val)
अणु
	चयन (n) अणु
	हाल 0:
		SET_XMM(val, xmm0);
		अवरोध;
	हाल 1:
		SET_XMM(val, xmm1);
		अवरोध;
	हाल 2:
		SET_XMM(val, xmm2);
		अवरोध;
	हाल 3:
		SET_XMM(val, xmm3);
		अवरोध;
	हाल 4:
		SET_XMM(val, xmm4);
		अवरोध;
	हाल 5:
		SET_XMM(val, xmm5);
		अवरोध;
	हाल 6:
		SET_XMM(val, xmm6);
		अवरोध;
	हाल 7:
		SET_XMM(val, xmm7);
		अवरोध;
	पूर्ण
पूर्ण

प्रकार अचिन्हित दीर्घ v1di __attribute__ ((vector_size (8)));
अटल अंतरभूत अचिन्हित दीर्घ get_xmm(पूर्णांक n)
अणु
	निश्चित(n >= 0 && n <= 7);

	रेजिस्टर v1di xmm0 __यंत्र__("%xmm0");
	रेजिस्टर v1di xmm1 __यंत्र__("%xmm1");
	रेजिस्टर v1di xmm2 __यंत्र__("%xmm2");
	रेजिस्टर v1di xmm3 __यंत्र__("%xmm3");
	रेजिस्टर v1di xmm4 __यंत्र__("%xmm4");
	रेजिस्टर v1di xmm5 __यंत्र__("%xmm5");
	रेजिस्टर v1di xmm6 __यंत्र__("%xmm6");
	रेजिस्टर v1di xmm7 __यंत्र__("%xmm7");
	चयन (n) अणु
	हाल 0:
		वापस (अचिन्हित दीर्घ)xmm0;
	हाल 1:
		वापस (अचिन्हित दीर्घ)xmm1;
	हाल 2:
		वापस (अचिन्हित दीर्घ)xmm2;
	हाल 3:
		वापस (अचिन्हित दीर्घ)xmm3;
	हाल 4:
		वापस (अचिन्हित दीर्घ)xmm4;
	हाल 5:
		वापस (अचिन्हित दीर्घ)xmm5;
	हाल 6:
		वापस (अचिन्हित दीर्घ)xmm6;
	हाल 7:
		वापस (अचिन्हित दीर्घ)xmm7;
	पूर्ण
	वापस 0;
पूर्ण

bool is_पूर्णांकel_cpu(व्योम);

काष्ठा kvm_x86_state;
काष्ठा kvm_x86_state *vcpu_save_state(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid);
व्योम vcpu_load_state(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid,
		     काष्ठा kvm_x86_state *state);

काष्ठा kvm_msr_list *kvm_get_msr_index_list(व्योम);
uपूर्णांक64_t kvm_get_feature_msr(uपूर्णांक64_t msr_index);
काष्ठा kvm_cpuid2 *kvm_get_supported_cpuid(व्योम);

काष्ठा kvm_cpuid2 *vcpu_get_cpuid(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid);
व्योम vcpu_set_cpuid(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid,
		    काष्ठा kvm_cpuid2 *cpuid);

काष्ठा kvm_cpuid_entry2 *
kvm_get_supported_cpuid_index(uपूर्णांक32_t function, uपूर्णांक32_t index);

अटल अंतरभूत काष्ठा kvm_cpuid_entry2 *
kvm_get_supported_cpuid_entry(uपूर्णांक32_t function)
अणु
	वापस kvm_get_supported_cpuid_index(function, 0);
पूर्ण

uपूर्णांक64_t vcpu_get_msr(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, uपूर्णांक64_t msr_index);
पूर्णांक _vcpu_set_msr(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, uपूर्णांक64_t msr_index,
		  uपूर्णांक64_t msr_value);
व्योम vcpu_set_msr(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, uपूर्णांक64_t msr_index,
	  	  uपूर्णांक64_t msr_value);

uपूर्णांक32_t kvm_get_cpuid_max_basic(व्योम);
uपूर्णांक32_t kvm_get_cpuid_max_extended(व्योम);
व्योम kvm_get_cpu_address_width(अचिन्हित पूर्णांक *pa_bits, अचिन्हित पूर्णांक *va_bits);

काष्ठा ex_regs अणु
	uपूर्णांक64_t rax, rcx, rdx, rbx;
	uपूर्णांक64_t rbp, rsi, rdi;
	uपूर्णांक64_t r8, r9, r10, r11;
	uपूर्णांक64_t r12, r13, r14, r15;
	uपूर्णांक64_t vector;
	uपूर्णांक64_t error_code;
	uपूर्णांक64_t rip;
	uपूर्णांक64_t cs;
	uपूर्णांक64_t rflags;
पूर्ण;

व्योम vm_init_descriptor_tables(काष्ठा kvm_vm *vm);
व्योम vcpu_init_descriptor_tables(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid);
व्योम vm_handle_exception(काष्ठा kvm_vm *vm, पूर्णांक vector,
			व्योम (*handler)(काष्ठा ex_regs *));

/*
 * set_cpuid() - overग_लिखोs a matching cpuid entry with the provided value.
 *		 matches based on ent->function && ent->index. वापसs true
 *		 अगर a match was found and successfully overwritten.
 * @cpuid: the kvm cpuid list to modअगरy.
 * @ent: cpuid entry to insert
 */
bool set_cpuid(काष्ठा kvm_cpuid2 *cpuid, काष्ठा kvm_cpuid_entry2 *ent);

uपूर्णांक64_t kvm_hypercall(uपूर्णांक64_t nr, uपूर्णांक64_t a0, uपूर्णांक64_t a1, uपूर्णांक64_t a2,
		       uपूर्णांक64_t a3);

काष्ठा kvm_cpuid2 *kvm_get_supported_hv_cpuid(व्योम);
व्योम vcpu_set_hv_cpuid(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid);
काष्ठा kvm_cpuid2 *vcpu_get_supported_hv_cpuid(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid);

/*
 * Basic CPU control in CR0
 */
#घोषणा X86_CR0_PE          (1UL<<0) /* Protection Enable */
#घोषणा X86_CR0_MP          (1UL<<1) /* Monitor Coprocessor */
#घोषणा X86_CR0_EM          (1UL<<2) /* Emulation */
#घोषणा X86_CR0_TS          (1UL<<3) /* Task Switched */
#घोषणा X86_CR0_ET          (1UL<<4) /* Extension Type */
#घोषणा X86_CR0_NE          (1UL<<5) /* Numeric Error */
#घोषणा X86_CR0_WP          (1UL<<16) /* Write Protect */
#घोषणा X86_CR0_AM          (1UL<<18) /* Alignment Mask */
#घोषणा X86_CR0_NW          (1UL<<29) /* Not Write-through */
#घोषणा X86_CR0_CD          (1UL<<30) /* Cache Disable */
#घोषणा X86_CR0_PG          (1UL<<31) /* Paging */

#घोषणा APIC_DEFAULT_GPA		0xfee00000ULL

/* APIC base address MSR and fields */
#घोषणा MSR_IA32_APICBASE		0x0000001b
#घोषणा MSR_IA32_APICBASE_BSP		(1<<8)
#घोषणा MSR_IA32_APICBASE_EXTD		(1<<10)
#घोषणा MSR_IA32_APICBASE_ENABLE	(1<<11)
#घोषणा MSR_IA32_APICBASE_BASE		(0xfffff<<12)
#घोषणा		GET_APIC_BASE(x)	(((x) >> 12) << 12)

#घोषणा APIC_BASE_MSR	0x800
#घोषणा X2APIC_ENABLE	(1UL << 10)
#घोषणा	APIC_ID		0x20
#घोषणा	APIC_LVR	0x30
#घोषणा		GET_APIC_ID_FIELD(x)	(((x) >> 24) & 0xFF)
#घोषणा	APIC_TASKPRI	0x80
#घोषणा	APIC_PROCPRI	0xA0
#घोषणा	APIC_EOI	0xB0
#घोषणा	APIC_SPIV	0xF0
#घोषणा		APIC_SPIV_FOCUS_DISABLED	(1 << 9)
#घोषणा		APIC_SPIV_APIC_ENABLED		(1 << 8)
#घोषणा	APIC_ICR	0x300
#घोषणा		APIC_DEST_SELF		0x40000
#घोषणा		APIC_DEST_ALLINC	0x80000
#घोषणा		APIC_DEST_ALLBUT	0xC0000
#घोषणा		APIC_ICR_RR_MASK	0x30000
#घोषणा		APIC_ICR_RR_INVALID	0x00000
#घोषणा		APIC_ICR_RR_INPROG	0x10000
#घोषणा		APIC_ICR_RR_VALID	0x20000
#घोषणा		APIC_INT_LEVELTRIG	0x08000
#घोषणा		APIC_INT_ASSERT		0x04000
#घोषणा		APIC_ICR_BUSY		0x01000
#घोषणा		APIC_DEST_LOGICAL	0x00800
#घोषणा		APIC_DEST_PHYSICAL	0x00000
#घोषणा		APIC_DM_FIXED		0x00000
#घोषणा		APIC_DM_FIXED_MASK	0x00700
#घोषणा		APIC_DM_LOWEST		0x00100
#घोषणा		APIC_DM_SMI		0x00200
#घोषणा		APIC_DM_REMRD		0x00300
#घोषणा		APIC_DM_NMI		0x00400
#घोषणा		APIC_DM_INIT		0x00500
#घोषणा		APIC_DM_STARTUP		0x00600
#घोषणा		APIC_DM_EXTINT		0x00700
#घोषणा		APIC_VECTOR_MASK	0x000FF
#घोषणा	APIC_ICR2	0x310
#घोषणा		SET_APIC_DEST_FIELD(x)	((x) << 24)

/* VMX_EPT_VPID_CAP bits */
#घोषणा VMX_EPT_VPID_CAP_AD_BITS       (1ULL << 21)

#पूर्ण_अगर /* SELFTEST_KVM_PROCESSOR_H */
