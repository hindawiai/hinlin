<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ASM_X86_KVM_H
#घोषणा _ASM_X86_KVM_H

/*
 * KVM x86 specअगरic काष्ठाures and definitions
 *
 */

#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>

#घोषणा KVM_PIO_PAGE_OFFSET 1
#घोषणा KVM_COALESCED_MMIO_PAGE_OFFSET 2
#घोषणा KVM_सूचीTY_LOG_PAGE_OFFSET 64

#घोषणा DE_VECTOR 0
#घोषणा DB_VECTOR 1
#घोषणा BP_VECTOR 3
#घोषणा OF_VECTOR 4
#घोषणा BR_VECTOR 5
#घोषणा UD_VECTOR 6
#घोषणा NM_VECTOR 7
#घोषणा DF_VECTOR 8
#घोषणा TS_VECTOR 10
#घोषणा NP_VECTOR 11
#घोषणा SS_VECTOR 12
#घोषणा GP_VECTOR 13
#घोषणा PF_VECTOR 14
#घोषणा MF_VECTOR 16
#घोषणा AC_VECTOR 17
#घोषणा MC_VECTOR 18
#घोषणा XM_VECTOR 19
#घोषणा VE_VECTOR 20

/* Select x86 specअगरic features in <linux/kvm.h> */
#घोषणा __KVM_HAVE_PIT
#घोषणा __KVM_HAVE_IOAPIC
#घोषणा __KVM_HAVE_IRQ_LINE
#घोषणा __KVM_HAVE_MSI
#घोषणा __KVM_HAVE_USER_NMI
#घोषणा __KVM_HAVE_GUEST_DEBUG
#घोषणा __KVM_HAVE_MSIX
#घोषणा __KVM_HAVE_MCE
#घोषणा __KVM_HAVE_PIT_STATE2
#घोषणा __KVM_HAVE_XEN_HVM
#घोषणा __KVM_HAVE_VCPU_EVENTS
#घोषणा __KVM_HAVE_DEBUGREGS
#घोषणा __KVM_HAVE_XSAVE
#घोषणा __KVM_HAVE_XCRS
#घोषणा __KVM_HAVE_READONLY_MEM

/* Architectural पूर्णांकerrupt line count. */
#घोषणा KVM_NR_INTERRUPTS 256

काष्ठा kvm_memory_alias अणु
	__u32 slot;  /* this has a dअगरferent namespace than memory slots */
	__u32 flags;
	__u64 guest_phys_addr;
	__u64 memory_size;
	__u64 target_phys_addr;
पूर्ण;

/* क्रम KVM_GET_IRQCHIP and KVM_SET_IRQCHIP */
काष्ठा kvm_pic_state अणु
	__u8 last_irr;	/* edge detection */
	__u8 irr;		/* पूर्णांकerrupt request रेजिस्टर */
	__u8 imr;		/* पूर्णांकerrupt mask रेजिस्टर */
	__u8 isr;		/* पूर्णांकerrupt service रेजिस्टर */
	__u8 priority_add;	/* highest irq priority */
	__u8 irq_base;
	__u8 पढ़ो_reg_select;
	__u8 poll;
	__u8 special_mask;
	__u8 init_state;
	__u8 स्वतः_eoi;
	__u8 rotate_on_स्वतः_eoi;
	__u8 special_fully_nested_mode;
	__u8 init4;		/* true अगर 4 byte init */
	__u8 elcr;		/* PIIX edge/trigger selection */
	__u8 elcr_mask;
पूर्ण;

#घोषणा KVM_IOAPIC_NUM_PINS  24
काष्ठा kvm_ioapic_state अणु
	__u64 base_address;
	__u32 ioregsel;
	__u32 id;
	__u32 irr;
	__u32 pad;
	जोड़ अणु
		__u64 bits;
		काष्ठा अणु
			__u8 vector;
			__u8 delivery_mode:3;
			__u8 dest_mode:1;
			__u8 delivery_status:1;
			__u8 polarity:1;
			__u8 remote_irr:1;
			__u8 trig_mode:1;
			__u8 mask:1;
			__u8 reserve:7;
			__u8 reserved[4];
			__u8 dest_id;
		पूर्ण fields;
	पूर्ण redirtbl[KVM_IOAPIC_NUM_PINS];
पूर्ण;

#घोषणा KVM_IRQCHIP_PIC_MASTER   0
#घोषणा KVM_IRQCHIP_PIC_SLAVE    1
#घोषणा KVM_IRQCHIP_IOAPIC       2
#घोषणा KVM_NR_IRQCHIPS          3

#घोषणा KVM_RUN_X86_SMM		 (1 << 0)
#घोषणा KVM_RUN_X86_BUS_LOCK     (1 << 1)

/* क्रम KVM_GET_REGS and KVM_SET_REGS */
काष्ठा kvm_regs अणु
	/* out (KVM_GET_REGS) / in (KVM_SET_REGS) */
	__u64 rax, rbx, rcx, rdx;
	__u64 rsi, rdi, rsp, rbp;
	__u64 r8,  r9,  r10, r11;
	__u64 r12, r13, r14, r15;
	__u64 rip, rflags;
पूर्ण;

/* क्रम KVM_GET_LAPIC and KVM_SET_LAPIC */
#घोषणा KVM_APIC_REG_SIZE 0x400
काष्ठा kvm_lapic_state अणु
	अक्षर regs[KVM_APIC_REG_SIZE];
पूर्ण;

काष्ठा kvm_segment अणु
	__u64 base;
	__u32 limit;
	__u16 selector;
	__u8  type;
	__u8  present, dpl, db, s, l, g, avl;
	__u8  unusable;
	__u8  padding;
पूर्ण;

काष्ठा kvm_dtable अणु
	__u64 base;
	__u16 limit;
	__u16 padding[3];
पूर्ण;


/* क्रम KVM_GET_SREGS and KVM_SET_SREGS */
काष्ठा kvm_sregs अणु
	/* out (KVM_GET_SREGS) / in (KVM_SET_SREGS) */
	काष्ठा kvm_segment cs, ds, es, fs, gs, ss;
	काष्ठा kvm_segment tr, ldt;
	काष्ठा kvm_dtable gdt, idt;
	__u64 cr0, cr2, cr3, cr4, cr8;
	__u64 efer;
	__u64 apic_base;
	__u64 पूर्णांकerrupt_biपंचांगap[(KVM_NR_INTERRUPTS + 63) / 64];
पूर्ण;

/* क्रम KVM_GET_FPU and KVM_SET_FPU */
काष्ठा kvm_fpu अणु
	__u8  fpr[8][16];
	__u16 fcw;
	__u16 fsw;
	__u8  ftwx;  /* in fxsave क्रमmat */
	__u8  pad1;
	__u16 last_opcode;
	__u64 last_ip;
	__u64 last_dp;
	__u8  xmm[16][16];
	__u32 mxcsr;
	__u32 pad2;
पूर्ण;

काष्ठा kvm_msr_entry अणु
	__u32 index;
	__u32 reserved;
	__u64 data;
पूर्ण;

/* क्रम KVM_GET_MSRS and KVM_SET_MSRS */
काष्ठा kvm_msrs अणु
	__u32 nmsrs; /* number of msrs in entries */
	__u32 pad;

	काष्ठा kvm_msr_entry entries[0];
पूर्ण;

/* क्रम KVM_GET_MSR_INDEX_LIST */
काष्ठा kvm_msr_list अणु
	__u32 nmsrs; /* number of msrs in entries */
	__u32 indices[0];
पूर्ण;

/* Maximum size of any access biपंचांगap in bytes */
#घोषणा KVM_MSR_FILTER_MAX_BITMAP_SIZE 0x600

/* क्रम KVM_X86_SET_MSR_FILTER */
काष्ठा kvm_msr_filter_range अणु
#घोषणा KVM_MSR_FILTER_READ  (1 << 0)
#घोषणा KVM_MSR_FILTER_WRITE (1 << 1)
	__u32 flags;
	__u32 nmsrs; /* number of msrs in biपंचांगap */
	__u32 base;  /* MSR index the biपंचांगap starts at */
	__u8 *biपंचांगap; /* a 1 bit allows the operations in flags, 0 denies */
पूर्ण;

#घोषणा KVM_MSR_FILTER_MAX_RANGES 16
काष्ठा kvm_msr_filter अणु
#घोषणा KVM_MSR_FILTER_DEFAULT_ALLOW (0 << 0)
#घोषणा KVM_MSR_FILTER_DEFAULT_DENY  (1 << 0)
	__u32 flags;
	काष्ठा kvm_msr_filter_range ranges[KVM_MSR_FILTER_MAX_RANGES];
पूर्ण;

काष्ठा kvm_cpuid_entry अणु
	__u32 function;
	__u32 eax;
	__u32 ebx;
	__u32 ecx;
	__u32 edx;
	__u32 padding;
पूर्ण;

/* क्रम KVM_SET_CPUID */
काष्ठा kvm_cpuid अणु
	__u32 nent;
	__u32 padding;
	काष्ठा kvm_cpuid_entry entries[0];
पूर्ण;

काष्ठा kvm_cpuid_entry2 अणु
	__u32 function;
	__u32 index;
	__u32 flags;
	__u32 eax;
	__u32 ebx;
	__u32 ecx;
	__u32 edx;
	__u32 padding[3];
पूर्ण;

#घोषणा KVM_CPUID_FLAG_SIGNIFCANT_INDEX		(1 << 0)
#घोषणा KVM_CPUID_FLAG_STATEFUL_FUNC		(1 << 1)
#घोषणा KVM_CPUID_FLAG_STATE_READ_NEXT		(1 << 2)

/* क्रम KVM_SET_CPUID2 */
काष्ठा kvm_cpuid2 अणु
	__u32 nent;
	__u32 padding;
	काष्ठा kvm_cpuid_entry2 entries[0];
पूर्ण;

/* क्रम KVM_GET_PIT and KVM_SET_PIT */
काष्ठा kvm_pit_channel_state अणु
	__u32 count; /* can be 65536 */
	__u16 latched_count;
	__u8 count_latched;
	__u8 status_latched;
	__u8 status;
	__u8 पढ़ो_state;
	__u8 ग_लिखो_state;
	__u8 ग_लिखो_latch;
	__u8 rw_mode;
	__u8 mode;
	__u8 bcd;
	__u8 gate;
	__s64 count_load_समय;
पूर्ण;

काष्ठा kvm_debug_निकास_arch अणु
	__u32 exception;
	__u32 pad;
	__u64 pc;
	__u64 dr6;
	__u64 dr7;
पूर्ण;

#घोषणा KVM_GUESTDBG_USE_SW_BP		0x00010000
#घोषणा KVM_GUESTDBG_USE_HW_BP		0x00020000
#घोषणा KVM_GUESTDBG_INJECT_DB		0x00040000
#घोषणा KVM_GUESTDBG_INJECT_BP		0x00080000

/* क्रम KVM_SET_GUEST_DEBUG */
काष्ठा kvm_guest_debug_arch अणु
	__u64 debugreg[8];
पूर्ण;

काष्ठा kvm_pit_state अणु
	काष्ठा kvm_pit_channel_state channels[3];
पूर्ण;

#घोषणा KVM_PIT_FLAGS_HPET_LEGACY  0x00000001

काष्ठा kvm_pit_state2 अणु
	काष्ठा kvm_pit_channel_state channels[3];
	__u32 flags;
	__u32 reserved[9];
पूर्ण;

काष्ठा kvm_reinject_control अणु
	__u8 pit_reinject;
	__u8 reserved[31];
पूर्ण;

/* When set in flags, include corresponding fields on KVM_SET_VCPU_EVENTS */
#घोषणा KVM_VCPUEVENT_VALID_NMI_PENDING	0x00000001
#घोषणा KVM_VCPUEVENT_VALID_SIPI_VECTOR	0x00000002
#घोषणा KVM_VCPUEVENT_VALID_SHADOW	0x00000004
#घोषणा KVM_VCPUEVENT_VALID_SMM		0x00000008
#घोषणा KVM_VCPUEVENT_VALID_PAYLOAD	0x00000010

/* Interrupt shaकरोw states */
#घोषणा KVM_X86_SHADOW_INT_MOV_SS	0x01
#घोषणा KVM_X86_SHADOW_INT_STI		0x02

/* क्रम KVM_GET/SET_VCPU_EVENTS */
काष्ठा kvm_vcpu_events अणु
	काष्ठा अणु
		__u8 injected;
		__u8 nr;
		__u8 has_error_code;
		__u8 pending;
		__u32 error_code;
	पूर्ण exception;
	काष्ठा अणु
		__u8 injected;
		__u8 nr;
		__u8 soft;
		__u8 shaकरोw;
	पूर्ण पूर्णांकerrupt;
	काष्ठा अणु
		__u8 injected;
		__u8 pending;
		__u8 masked;
		__u8 pad;
	पूर्ण nmi;
	__u32 sipi_vector;
	__u32 flags;
	काष्ठा अणु
		__u8 smm;
		__u8 pending;
		__u8 smm_inside_nmi;
		__u8 latched_init;
	पूर्ण smi;
	__u8 reserved[27];
	__u8 exception_has_payload;
	__u64 exception_payload;
पूर्ण;

/* क्रम KVM_GET/SET_DEBUGREGS */
काष्ठा kvm_debugregs अणु
	__u64 db[4];
	__u64 dr6;
	__u64 dr7;
	__u64 flags;
	__u64 reserved[9];
पूर्ण;

/* क्रम KVM_CAP_XSAVE */
काष्ठा kvm_xsave अणु
	__u32 region[1024];
पूर्ण;

#घोषणा KVM_MAX_XCRS	16

काष्ठा kvm_xcr अणु
	__u32 xcr;
	__u32 reserved;
	__u64 value;
पूर्ण;

काष्ठा kvm_xcrs अणु
	__u32 nr_xcrs;
	__u32 flags;
	काष्ठा kvm_xcr xcrs[KVM_MAX_XCRS];
	__u64 padding[16];
पूर्ण;

#घोषणा KVM_SYNC_X86_REGS      (1UL << 0)
#घोषणा KVM_SYNC_X86_SREGS     (1UL << 1)
#घोषणा KVM_SYNC_X86_EVENTS    (1UL << 2)

#घोषणा KVM_SYNC_X86_VALID_FIELDS \
	(KVM_SYNC_X86_REGS| \
	 KVM_SYNC_X86_SREGS| \
	 KVM_SYNC_X86_EVENTS)

/* kvm_sync_regs काष्ठा included by kvm_run काष्ठा */
काष्ठा kvm_sync_regs अणु
	/* Members of this काष्ठाure are potentially malicious.
	 * Care must be taken by code पढ़ोing, esp. पूर्णांकerpreting,
	 * data fields from them inside KVM to prevent TOCTOU and
	 * द्विगुन-fetch types of vulnerabilities.
	 */
	काष्ठा kvm_regs regs;
	काष्ठा kvm_sregs sregs;
	काष्ठा kvm_vcpu_events events;
पूर्ण;

#घोषणा KVM_X86_QUIRK_LINT0_REENABLED	   (1 << 0)
#घोषणा KVM_X86_QUIRK_CD_NW_CLEARED	   (1 << 1)
#घोषणा KVM_X86_QUIRK_LAPIC_MMIO_HOLE	   (1 << 2)
#घोषणा KVM_X86_QUIRK_OUT_7E_INC_RIP	   (1 << 3)
#घोषणा KVM_X86_QUIRK_MISC_ENABLE_NO_MWAIT (1 << 4)

#घोषणा KVM_STATE_NESTED_FORMAT_VMX	0
#घोषणा KVM_STATE_NESTED_FORMAT_SVM	1

#घोषणा KVM_STATE_NESTED_GUEST_MODE	0x00000001
#घोषणा KVM_STATE_NESTED_RUN_PENDING	0x00000002
#घोषणा KVM_STATE_NESTED_EVMCS		0x00000004
#घोषणा KVM_STATE_NESTED_MTF_PENDING	0x00000008
#घोषणा KVM_STATE_NESTED_GIF_SET	0x00000100

#घोषणा KVM_STATE_NESTED_SMM_GUEST_MODE	0x00000001
#घोषणा KVM_STATE_NESTED_SMM_VMXON	0x00000002

#घोषणा KVM_STATE_NESTED_VMX_VMCS_SIZE	0x1000

#घोषणा KVM_STATE_NESTED_SVM_VMCB_SIZE	0x1000

#घोषणा KVM_STATE_VMX_PREEMPTION_TIMER_DEADLINE	0x00000001

काष्ठा kvm_vmx_nested_state_data अणु
	__u8 vmcs12[KVM_STATE_NESTED_VMX_VMCS_SIZE];
	__u8 shaकरोw_vmcs12[KVM_STATE_NESTED_VMX_VMCS_SIZE];
पूर्ण;

काष्ठा kvm_vmx_nested_state_hdr अणु
	__u64 vmxon_pa;
	__u64 vmcs12_pa;

	काष्ठा अणु
		__u16 flags;
	पूर्ण smm;

	__u16 pad;

	__u32 flags;
	__u64 preemption_समयr_deadline;
पूर्ण;

काष्ठा kvm_svm_nested_state_data अणु
	/* Save area only used अगर KVM_STATE_NESTED_RUN_PENDING.  */
	__u8 vmcb12[KVM_STATE_NESTED_SVM_VMCB_SIZE];
पूर्ण;

काष्ठा kvm_svm_nested_state_hdr अणु
	__u64 vmcb_pa;
पूर्ण;

/* क्रम KVM_CAP_NESTED_STATE */
काष्ठा kvm_nested_state अणु
	__u16 flags;
	__u16 क्रमmat;
	__u32 size;

	जोड़ अणु
		काष्ठा kvm_vmx_nested_state_hdr vmx;
		काष्ठा kvm_svm_nested_state_hdr svm;

		/* Pad the header to 128 bytes.  */
		__u8 pad[120];
	पूर्ण hdr;

	/*
	 * Define data region as 0 bytes to preserve backwards-compatability
	 * to old definition of kvm_nested_state in order to aव्योम changing
	 * KVM_अणुGET,PUTपूर्ण_NESTED_STATE ioctl values.
	 */
	जोड़ अणु
		काष्ठा kvm_vmx_nested_state_data vmx[0];
		काष्ठा kvm_svm_nested_state_data svm[0];
	पूर्ण data;
पूर्ण;

/* क्रम KVM_CAP_PMU_EVENT_FILTER */
काष्ठा kvm_pmu_event_filter अणु
	__u32 action;
	__u32 nevents;
	__u32 fixed_counter_biपंचांगap;
	__u32 flags;
	__u32 pad[4];
	__u64 events[0];
पूर्ण;

#घोषणा KVM_PMU_EVENT_ALLOW 0
#घोषणा KVM_PMU_EVENT_DENY 1

#पूर्ण_अगर /* _ASM_X86_KVM_H */
