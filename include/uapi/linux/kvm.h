<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __LINUX_KVM_H
#घोषणा __LINUX_KVM_H

/*
 * Userspace पूर्णांकerface क्रम /dev/kvm - kernel based भव machine
 *
 * Note: you must update KVM_API_VERSION अगर you change this पूर्णांकerface.
 */

#समावेश <linux/स्थिर.h>
#समावेश <linux/types.h>
#समावेश <linux/compiler.h>
#समावेश <linux/ioctl.h>
#समावेश <यंत्र/kvm.h>

#घोषणा KVM_API_VERSION 12

/* *** Deprecated पूर्णांकerfaces *** */

#घोषणा KVM_TRC_SHIFT           16

#घोषणा KVM_TRC_ENTRYEXIT       (1 << KVM_TRC_SHIFT)
#घोषणा KVM_TRC_HANDLER         (1 << (KVM_TRC_SHIFT + 1))

#घोषणा KVM_TRC_VMENTRY         (KVM_TRC_ENTRYEXIT + 0x01)
#घोषणा KVM_TRC_VMEXIT          (KVM_TRC_ENTRYEXIT + 0x02)
#घोषणा KVM_TRC_PAGE_FAULT      (KVM_TRC_HANDLER + 0x01)

#घोषणा KVM_TRC_HEAD_SIZE       12
#घोषणा KVM_TRC_CYCLE_SIZE      8
#घोषणा KVM_TRC_EXTRA_MAX       7

#घोषणा KVM_TRC_INJ_VIRQ         (KVM_TRC_HANDLER + 0x02)
#घोषणा KVM_TRC_REDELIVER_EVT    (KVM_TRC_HANDLER + 0x03)
#घोषणा KVM_TRC_PEND_INTR        (KVM_TRC_HANDLER + 0x04)
#घोषणा KVM_TRC_IO_READ          (KVM_TRC_HANDLER + 0x05)
#घोषणा KVM_TRC_IO_WRITE         (KVM_TRC_HANDLER + 0x06)
#घोषणा KVM_TRC_CR_READ          (KVM_TRC_HANDLER + 0x07)
#घोषणा KVM_TRC_CR_WRITE         (KVM_TRC_HANDLER + 0x08)
#घोषणा KVM_TRC_DR_READ          (KVM_TRC_HANDLER + 0x09)
#घोषणा KVM_TRC_DR_WRITE         (KVM_TRC_HANDLER + 0x0A)
#घोषणा KVM_TRC_MSR_READ         (KVM_TRC_HANDLER + 0x0B)
#घोषणा KVM_TRC_MSR_WRITE        (KVM_TRC_HANDLER + 0x0C)
#घोषणा KVM_TRC_CPUID            (KVM_TRC_HANDLER + 0x0D)
#घोषणा KVM_TRC_INTR             (KVM_TRC_HANDLER + 0x0E)
#घोषणा KVM_TRC_NMI              (KVM_TRC_HANDLER + 0x0F)
#घोषणा KVM_TRC_VMMCALL          (KVM_TRC_HANDLER + 0x10)
#घोषणा KVM_TRC_HLT              (KVM_TRC_HANDLER + 0x11)
#घोषणा KVM_TRC_CLTS             (KVM_TRC_HANDLER + 0x12)
#घोषणा KVM_TRC_LMSW             (KVM_TRC_HANDLER + 0x13)
#घोषणा KVM_TRC_APIC_ACCESS      (KVM_TRC_HANDLER + 0x14)
#घोषणा KVM_TRC_TDP_FAULT        (KVM_TRC_HANDLER + 0x15)
#घोषणा KVM_TRC_GTLB_WRITE       (KVM_TRC_HANDLER + 0x16)
#घोषणा KVM_TRC_STLB_WRITE       (KVM_TRC_HANDLER + 0x17)
#घोषणा KVM_TRC_STLB_INVAL       (KVM_TRC_HANDLER + 0x18)
#घोषणा KVM_TRC_PPC_INSTR        (KVM_TRC_HANDLER + 0x19)

काष्ठा kvm_user_trace_setup अणु
	__u32 buf_size;
	__u32 buf_nr;
पूर्ण;

#घोषणा __KVM_DEPRECATED_MAIN_W_0x06 \
	_IOW(KVMIO, 0x06, काष्ठा kvm_user_trace_setup)
#घोषणा __KVM_DEPRECATED_MAIN_0x07 _IO(KVMIO, 0x07)
#घोषणा __KVM_DEPRECATED_MAIN_0x08 _IO(KVMIO, 0x08)

#घोषणा __KVM_DEPRECATED_VM_R_0x70 _IOR(KVMIO, 0x70, काष्ठा kvm_asचिन्हित_irq)

काष्ठा kvm_अवरोधpoपूर्णांक अणु
	__u32 enabled;
	__u32 padding;
	__u64 address;
पूर्ण;

काष्ठा kvm_debug_guest अणु
	__u32 enabled;
	__u32 pad;
	काष्ठा kvm_अवरोधpoपूर्णांक अवरोधpoपूर्णांकs[4];
	__u32 singlestep;
पूर्ण;

#घोषणा __KVM_DEPRECATED_VCPU_W_0x87 _IOW(KVMIO, 0x87, काष्ठा kvm_debug_guest)

/* *** End of deprecated पूर्णांकerfaces *** */


/* क्रम KVM_CREATE_MEMORY_REGION */
काष्ठा kvm_memory_region अणु
	__u32 slot;
	__u32 flags;
	__u64 guest_phys_addr;
	__u64 memory_size; /* bytes */
पूर्ण;

/* क्रम KVM_SET_USER_MEMORY_REGION */
काष्ठा kvm_userspace_memory_region अणु
	__u32 slot;
	__u32 flags;
	__u64 guest_phys_addr;
	__u64 memory_size; /* bytes */
	__u64 userspace_addr; /* start of the userspace allocated memory */
पूर्ण;

/*
 * The bit 0 ~ bit 15 of kvm_memory_region::flags are visible क्रम userspace,
 * other bits are reserved क्रम kvm पूर्णांकernal use which are defined in
 * include/linux/kvm_host.h.
 */
#घोषणा KVM_MEM_LOG_सूचीTY_PAGES	(1UL << 0)
#घोषणा KVM_MEM_READONLY	(1UL << 1)

/* क्रम KVM_IRQ_LINE */
काष्ठा kvm_irq_level अणु
	/*
	 * ACPI gsi notion of irq.
	 * For IA-64 (APIC model) IOAPIC0: irq 0-23; IOAPIC1: irq 24-47..
	 * For X86 (standard AT mode) PIC0/1: irq 0-15. IOAPIC0: 0-23..
	 * For ARM: See Documentation/virt/kvm/api.rst
	 */
	जोड़ अणु
		__u32 irq;
		__s32 status;
	पूर्ण;
	__u32 level;
पूर्ण;


काष्ठा kvm_irqchip अणु
	__u32 chip_id;
	__u32 pad;
        जोड़ अणु
		अक्षर dummy[512];  /* reserving space */
#अगर_घोषित __KVM_HAVE_PIT
		काष्ठा kvm_pic_state pic;
#पूर्ण_अगर
#अगर_घोषित __KVM_HAVE_IOAPIC
		काष्ठा kvm_ioapic_state ioapic;
#पूर्ण_अगर
	पूर्ण chip;
पूर्ण;

/* क्रम KVM_CREATE_PIT2 */
काष्ठा kvm_pit_config अणु
	__u32 flags;
	__u32 pad[15];
पूर्ण;

#घोषणा KVM_PIT_SPEAKER_DUMMY     1

काष्ठा kvm_s390_skeys अणु
	__u64 start_gfn;
	__u64 count;
	__u64 skeydata_addr;
	__u32 flags;
	__u32 reserved[9];
पूर्ण;

#घोषणा KVM_S390_CMMA_PEEK (1 << 0)

/**
 * kvm_s390_cmma_log - Used क्रम CMMA migration.
 *
 * Used both क्रम input and output.
 *
 * @start_gfn: Guest page number to start from.
 * @count: Size of the result buffer.
 * @flags: Control operation mode via KVM_S390_CMMA_* flags
 * @reमुख्यing: Used with KVM_S390_GET_CMMA_BITS. Indicates how many dirty
 *             pages are still reमुख्यing.
 * @mask: Used with KVM_S390_SET_CMMA_BITS. Biपंचांगap of bits to actually set
 *        in the PGSTE.
 * @values: Poपूर्णांकer to the values buffer.
 *
 * Used in KVM_S390_अणुG,Sपूर्णET_CMMA_BITS ioctls.
 */
काष्ठा kvm_s390_cmma_log अणु
	__u64 start_gfn;
	__u32 count;
	__u32 flags;
	जोड़ अणु
		__u64 reमुख्यing;
		__u64 mask;
	पूर्ण;
	__u64 values;
पूर्ण;

काष्ठा kvm_hyperv_निकास अणु
#घोषणा KVM_EXIT_HYPERV_SYNIC          1
#घोषणा KVM_EXIT_HYPERV_HCALL          2
#घोषणा KVM_EXIT_HYPERV_SYNDBG         3
	__u32 type;
	__u32 pad1;
	जोड़ अणु
		काष्ठा अणु
			__u32 msr;
			__u32 pad2;
			__u64 control;
			__u64 evt_page;
			__u64 msg_page;
		पूर्ण synic;
		काष्ठा अणु
			__u64 input;
			__u64 result;
			__u64 params[2];
		पूर्ण hcall;
		काष्ठा अणु
			__u32 msr;
			__u32 pad2;
			__u64 control;
			__u64 status;
			__u64 send_page;
			__u64 recv_page;
			__u64 pending_page;
		पूर्ण syndbg;
	पूर्ण u;
पूर्ण;

काष्ठा kvm_xen_निकास अणु
#घोषणा KVM_EXIT_XEN_HCALL          1
	__u32 type;
	जोड़ अणु
		काष्ठा अणु
			__u32 दीर्घmode;
			__u32 cpl;
			__u64 input;
			__u64 result;
			__u64 params[6];
		पूर्ण hcall;
	पूर्ण u;
पूर्ण;

#घोषणा KVM_S390_GET_SKEYS_NONE   1
#घोषणा KVM_S390_SKEYS_MAX        1048576

#घोषणा KVM_EXIT_UNKNOWN          0
#घोषणा KVM_EXIT_EXCEPTION        1
#घोषणा KVM_EXIT_IO               2
#घोषणा KVM_EXIT_HYPERCALL        3
#घोषणा KVM_EXIT_DEBUG            4
#घोषणा KVM_EXIT_HLT              5
#घोषणा KVM_EXIT_MMIO             6
#घोषणा KVM_EXIT_IRQ_WINDOW_OPEN  7
#घोषणा KVM_EXIT_SHUTDOWN         8
#घोषणा KVM_EXIT_FAIL_ENTRY       9
#घोषणा KVM_EXIT_INTR             10
#घोषणा KVM_EXIT_SET_TPR          11
#घोषणा KVM_EXIT_TPR_ACCESS       12
#घोषणा KVM_EXIT_S390_SIEIC       13
#घोषणा KVM_EXIT_S390_RESET       14
#घोषणा KVM_EXIT_DCR              15 /* deprecated */
#घोषणा KVM_EXIT_NMI              16
#घोषणा KVM_EXIT_INTERNAL_ERROR   17
#घोषणा KVM_EXIT_OSI              18
#घोषणा KVM_EXIT_PAPR_HCALL	  19
#घोषणा KVM_EXIT_S390_UCONTROL	  20
#घोषणा KVM_EXIT_WATCHDOG         21
#घोषणा KVM_EXIT_S390_TSCH        22
#घोषणा KVM_EXIT_EPR              23
#घोषणा KVM_EXIT_SYSTEM_EVENT     24
#घोषणा KVM_EXIT_S390_STSI        25
#घोषणा KVM_EXIT_IOAPIC_EOI       26
#घोषणा KVM_EXIT_HYPERV           27
#घोषणा KVM_EXIT_ARM_NISV         28
#घोषणा KVM_EXIT_X86_RDMSR        29
#घोषणा KVM_EXIT_X86_WRMSR        30
#घोषणा KVM_EXIT_सूचीTY_RING_FULL  31
#घोषणा KVM_EXIT_AP_RESET_HOLD    32
#घोषणा KVM_EXIT_X86_BUS_LOCK     33
#घोषणा KVM_EXIT_XEN              34

/* For KVM_EXIT_INTERNAL_ERROR */
/* Emulate inकाष्ठाion failed. */
#घोषणा KVM_INTERNAL_ERROR_EMULATION	1
/* Encounter unexpected simultaneous exceptions. */
#घोषणा KVM_INTERNAL_ERROR_SIMUL_EX	2
/* Encounter unexpected vm-निकास due to delivery event. */
#घोषणा KVM_INTERNAL_ERROR_DELIVERY_EV	3
/* Encounter unexpected vm-निकास reason */
#घोषणा KVM_INTERNAL_ERROR_UNEXPECTED_EXIT_REASON	4

/* क्रम KVM_RUN, वापसed by mmap(vcpu_fd, offset=0) */
काष्ठा kvm_run अणु
	/* in */
	__u8 request_पूर्णांकerrupt_winकरोw;
	__u8 immediate_निकास;
	__u8 padding1[6];

	/* out */
	__u32 निकास_reason;
	__u8 पढ़ोy_क्रम_पूर्णांकerrupt_injection;
	__u8 अगर_flag;
	__u16 flags;

	/* in (pre_kvm_run), out (post_kvm_run) */
	__u64 cr8;
	__u64 apic_base;

#अगर_घोषित __KVM_S390
	/* the processor status word क्रम s390 */
	__u64 psw_mask; /* psw upper half */
	__u64 psw_addr; /* psw lower half */
#पूर्ण_अगर
	जोड़ अणु
		/* KVM_EXIT_UNKNOWN */
		काष्ठा अणु
			__u64 hardware_निकास_reason;
		पूर्ण hw;
		/* KVM_EXIT_FAIL_ENTRY */
		काष्ठा अणु
			__u64 hardware_entry_failure_reason;
			__u32 cpu;
		पूर्ण fail_entry;
		/* KVM_EXIT_EXCEPTION */
		काष्ठा अणु
			__u32 exception;
			__u32 error_code;
		पूर्ण ex;
		/* KVM_EXIT_IO */
		काष्ठा अणु
#घोषणा KVM_EXIT_IO_IN  0
#घोषणा KVM_EXIT_IO_OUT 1
			__u8 direction;
			__u8 size; /* bytes */
			__u16 port;
			__u32 count;
			__u64 data_offset; /* relative to kvm_run start */
		पूर्ण io;
		/* KVM_EXIT_DEBUG */
		काष्ठा अणु
			काष्ठा kvm_debug_निकास_arch arch;
		पूर्ण debug;
		/* KVM_EXIT_MMIO */
		काष्ठा अणु
			__u64 phys_addr;
			__u8  data[8];
			__u32 len;
			__u8  is_ग_लिखो;
		पूर्ण mmio;
		/* KVM_EXIT_HYPERCALL */
		काष्ठा अणु
			__u64 nr;
			__u64 args[6];
			__u64 ret;
			__u32 दीर्घmode;
			__u32 pad;
		पूर्ण hypercall;
		/* KVM_EXIT_TPR_ACCESS */
		काष्ठा अणु
			__u64 rip;
			__u32 is_ग_लिखो;
			__u32 pad;
		पूर्ण tpr_access;
		/* KVM_EXIT_S390_SIEIC */
		काष्ठा अणु
			__u8 icptcode;
			__u16 ipa;
			__u32 ipb;
		पूर्ण s390_sieic;
		/* KVM_EXIT_S390_RESET */
#घोषणा KVM_S390_RESET_POR       1
#घोषणा KVM_S390_RESET_CLEAR     2
#घोषणा KVM_S390_RESET_SUBSYSTEM 4
#घोषणा KVM_S390_RESET_CPU_INIT  8
#घोषणा KVM_S390_RESET_IPL       16
		__u64 s390_reset_flags;
		/* KVM_EXIT_S390_UCONTROL */
		काष्ठा अणु
			__u64 trans_exc_code;
			__u32 pgm_code;
		पूर्ण s390_ucontrol;
		/* KVM_EXIT_DCR (deprecated) */
		काष्ठा अणु
			__u32 dcrn;
			__u32 data;
			__u8  is_ग_लिखो;
		पूर्ण dcr;
		/* KVM_EXIT_INTERNAL_ERROR */
		काष्ठा अणु
			__u32 suberror;
			/* Available with KVM_CAP_INTERNAL_ERROR_DATA: */
			__u32 ndata;
			__u64 data[16];
		पूर्ण पूर्णांकernal;
		/* KVM_EXIT_OSI */
		काष्ठा अणु
			__u64 gprs[32];
		पूर्ण osi;
		/* KVM_EXIT_PAPR_HCALL */
		काष्ठा अणु
			__u64 nr;
			__u64 ret;
			__u64 args[9];
		पूर्ण papr_hcall;
		/* KVM_EXIT_S390_TSCH */
		काष्ठा अणु
			__u16 subchannel_id;
			__u16 subchannel_nr;
			__u32 io_पूर्णांक_parm;
			__u32 io_पूर्णांक_word;
			__u32 ipb;
			__u8 dequeued;
		पूर्ण s390_tsch;
		/* KVM_EXIT_EPR */
		काष्ठा अणु
			__u32 epr;
		पूर्ण epr;
		/* KVM_EXIT_SYSTEM_EVENT */
		काष्ठा अणु
#घोषणा KVM_SYSTEM_EVENT_SHUTDOWN       1
#घोषणा KVM_SYSTEM_EVENT_RESET          2
#घोषणा KVM_SYSTEM_EVENT_CRASH          3
			__u32 type;
			__u64 flags;
		पूर्ण प्रणाली_event;
		/* KVM_EXIT_S390_STSI */
		काष्ठा अणु
			__u64 addr;
			__u8 ar;
			__u8 reserved;
			__u8 fc;
			__u8 sel1;
			__u16 sel2;
		पूर्ण s390_stsi;
		/* KVM_EXIT_IOAPIC_EOI */
		काष्ठा अणु
			__u8 vector;
		पूर्ण eoi;
		/* KVM_EXIT_HYPERV */
		काष्ठा kvm_hyperv_निकास hyperv;
		/* KVM_EXIT_ARM_NISV */
		काष्ठा अणु
			__u64 esr_iss;
			__u64 fault_ipa;
		पूर्ण arm_nisv;
		/* KVM_EXIT_X86_RDMSR / KVM_EXIT_X86_WRMSR */
		काष्ठा अणु
			__u8 error; /* user -> kernel */
			__u8 pad[7];
#घोषणा KVM_MSR_EXIT_REASON_INVAL	(1 << 0)
#घोषणा KVM_MSR_EXIT_REASON_UNKNOWN	(1 << 1)
#घोषणा KVM_MSR_EXIT_REASON_FILTER	(1 << 2)
			__u32 reason; /* kernel -> user */
			__u32 index; /* kernel -> user */
			__u64 data; /* kernel <-> user */
		पूर्ण msr;
		/* KVM_EXIT_XEN */
		काष्ठा kvm_xen_निकास xen;
		/* Fix the size of the जोड़. */
		अक्षर padding[256];
	पूर्ण;

	/* 2048 is the size of the अक्षर array used to bound/pad the size
	 * of the जोड़ that holds sync regs.
	 */
	#घोषणा SYNC_REGS_SIZE_BYTES 2048
	/*
	 * shared रेजिस्टरs between kvm and userspace.
	 * kvm_valid_regs specअगरies the रेजिस्टर classes set by the host
	 * kvm_dirty_regs specअगरied the रेजिस्टर classes dirtied by userspace
	 * काष्ठा kvm_sync_regs is architecture specअगरic, as well as the
	 * bits क्रम kvm_valid_regs and kvm_dirty_regs
	 */
	__u64 kvm_valid_regs;
	__u64 kvm_dirty_regs;
	जोड़ अणु
		काष्ठा kvm_sync_regs regs;
		अक्षर padding[SYNC_REGS_SIZE_BYTES];
	पूर्ण s;
पूर्ण;

/* क्रम KVM_REGISTER_COALESCED_MMIO / KVM_UNREGISTER_COALESCED_MMIO */

काष्ठा kvm_coalesced_mmio_zone अणु
	__u64 addr;
	__u32 size;
	जोड़ अणु
		__u32 pad;
		__u32 pio;
	पूर्ण;
पूर्ण;

काष्ठा kvm_coalesced_mmio अणु
	__u64 phys_addr;
	__u32 len;
	जोड़ अणु
		__u32 pad;
		__u32 pio;
	पूर्ण;
	__u8  data[8];
पूर्ण;

काष्ठा kvm_coalesced_mmio_ring अणु
	__u32 first, last;
	काष्ठा kvm_coalesced_mmio coalesced_mmio[0];
पूर्ण;

#घोषणा KVM_COALESCED_MMIO_MAX \
	((PAGE_SIZE - माप(काष्ठा kvm_coalesced_mmio_ring)) / \
	 माप(काष्ठा kvm_coalesced_mmio))

/* क्रम KVM_TRANSLATE */
काष्ठा kvm_translation अणु
	/* in */
	__u64 linear_address;

	/* out */
	__u64 physical_address;
	__u8  valid;
	__u8  ग_लिखोable;
	__u8  usermode;
	__u8  pad[5];
पूर्ण;

/* क्रम KVM_S390_MEM_OP */
काष्ठा kvm_s390_mem_op अणु
	/* in */
	__u64 gaddr;		/* the guest address */
	__u64 flags;		/* flags */
	__u32 size;		/* amount of bytes */
	__u32 op;		/* type of operation */
	__u64 buf;		/* buffer in userspace */
	जोड़ अणु
		__u8 ar;	/* the access रेजिस्टर number */
		__u32 sida_offset; /* offset पूर्णांकo the sida */
		__u8 reserved[32]; /* should be set to 0 */
	पूर्ण;
पूर्ण;
/* types क्रम kvm_s390_mem_op->op */
#घोषणा KVM_S390_MEMOP_LOGICAL_READ	0
#घोषणा KVM_S390_MEMOP_LOGICAL_WRITE	1
#घोषणा KVM_S390_MEMOP_SIDA_READ	2
#घोषणा KVM_S390_MEMOP_SIDA_WRITE	3
/* flags क्रम kvm_s390_mem_op->flags */
#घोषणा KVM_S390_MEMOP_F_CHECK_ONLY		(1ULL << 0)
#घोषणा KVM_S390_MEMOP_F_INJECT_EXCEPTION	(1ULL << 1)

/* क्रम KVM_INTERRUPT */
काष्ठा kvm_पूर्णांकerrupt अणु
	/* in */
	__u32 irq;
पूर्ण;

/* क्रम KVM_GET_सूचीTY_LOG */
काष्ठा kvm_dirty_log अणु
	__u32 slot;
	__u32 padding1;
	जोड़ अणु
		व्योम __user *dirty_biपंचांगap; /* one bit per page */
		__u64 padding2;
	पूर्ण;
पूर्ण;

/* क्रम KVM_CLEAR_सूचीTY_LOG */
काष्ठा kvm_clear_dirty_log अणु
	__u32 slot;
	__u32 num_pages;
	__u64 first_page;
	जोड़ अणु
		व्योम __user *dirty_biपंचांगap; /* one bit per page */
		__u64 padding2;
	पूर्ण;
पूर्ण;

/* क्रम KVM_SET_SIGNAL_MASK */
काष्ठा kvm_संकेत_mask अणु
	__u32 len;
	__u8  sigset[0];
पूर्ण;

/* क्रम KVM_TPR_ACCESS_REPORTING */
काष्ठा kvm_tpr_access_ctl अणु
	__u32 enabled;
	__u32 flags;
	__u32 reserved[8];
पूर्ण;

/* क्रम KVM_SET_VAPIC_ADDR */
काष्ठा kvm_vapic_addr अणु
	__u64 vapic_addr;
पूर्ण;

/* क्रम KVM_SET_MP_STATE */

/* not all states are valid on all architectures */
#घोषणा KVM_MP_STATE_RUNNABLE          0
#घोषणा KVM_MP_STATE_UNINITIALIZED     1
#घोषणा KVM_MP_STATE_INIT_RECEIVED     2
#घोषणा KVM_MP_STATE_HALTED            3
#घोषणा KVM_MP_STATE_SIPI_RECEIVED     4
#घोषणा KVM_MP_STATE_STOPPED           5
#घोषणा KVM_MP_STATE_CHECK_STOP        6
#घोषणा KVM_MP_STATE_OPERATING         7
#घोषणा KVM_MP_STATE_LOAD              8
#घोषणा KVM_MP_STATE_AP_RESET_HOLD     9

काष्ठा kvm_mp_state अणु
	__u32 mp_state;
पूर्ण;

काष्ठा kvm_s390_psw अणु
	__u64 mask;
	__u64 addr;
पूर्ण;

/* valid values क्रम type in kvm_s390_पूर्णांकerrupt */
#घोषणा KVM_S390_SIGP_STOP		0xfffe0000u
#घोषणा KVM_S390_PROGRAM_INT		0xfffe0001u
#घोषणा KVM_S390_SIGP_SET_PREFIX	0xfffe0002u
#घोषणा KVM_S390_RESTART		0xfffe0003u
#घोषणा KVM_S390_INT_PFAULT_INIT	0xfffe0004u
#घोषणा KVM_S390_INT_PFAULT_DONE	0xfffe0005u
#घोषणा KVM_S390_MCHK			0xfffe1000u
#घोषणा KVM_S390_INT_CLOCK_COMP		0xffff1004u
#घोषणा KVM_S390_INT_CPU_TIMER		0xffff1005u
#घोषणा KVM_S390_INT_VIRTIO		0xffff2603u
#घोषणा KVM_S390_INT_SERVICE		0xffff2401u
#घोषणा KVM_S390_INT_EMERGENCY		0xffff1201u
#घोषणा KVM_S390_INT_EXTERNAL_CALL	0xffff1202u
/* Anything below 0xfffe0000u is taken by INT_IO */
#घोषणा KVM_S390_INT_IO(ai,cssid,ssid,schid)   \
	(((schid)) |			       \
	 ((ssid) << 16) |		       \
	 ((cssid) << 18) |		       \
	 ((ai) << 26))
#घोषणा KVM_S390_INT_IO_MIN		0x00000000u
#घोषणा KVM_S390_INT_IO_MAX		0xfffdffffu
#घोषणा KVM_S390_INT_IO_AI_MASK		0x04000000u


काष्ठा kvm_s390_पूर्णांकerrupt अणु
	__u32 type;
	__u32 parm;
	__u64 parm64;
पूर्ण;

काष्ठा kvm_s390_io_info अणु
	__u16 subchannel_id;
	__u16 subchannel_nr;
	__u32 io_पूर्णांक_parm;
	__u32 io_पूर्णांक_word;
पूर्ण;

काष्ठा kvm_s390_ext_info अणु
	__u32 ext_params;
	__u32 pad;
	__u64 ext_params2;
पूर्ण;

काष्ठा kvm_s390_pgm_info अणु
	__u64 trans_exc_code;
	__u64 mon_code;
	__u64 per_address;
	__u32 data_exc_code;
	__u16 code;
	__u16 mon_class_nr;
	__u8 per_code;
	__u8 per_aपंचांगid;
	__u8 exc_access_id;
	__u8 per_access_id;
	__u8 op_access_id;
#घोषणा KVM_S390_PGM_FLAGS_ILC_VALID	0x01
#घोषणा KVM_S390_PGM_FLAGS_ILC_0	0x02
#घोषणा KVM_S390_PGM_FLAGS_ILC_1	0x04
#घोषणा KVM_S390_PGM_FLAGS_ILC_MASK	0x06
#घोषणा KVM_S390_PGM_FLAGS_NO_REWIND	0x08
	__u8 flags;
	__u8 pad[2];
पूर्ण;

काष्ठा kvm_s390_prefix_info अणु
	__u32 address;
पूर्ण;

काष्ठा kvm_s390_extcall_info अणु
	__u16 code;
पूर्ण;

काष्ठा kvm_s390_emerg_info अणु
	__u16 code;
पूर्ण;

#घोषणा KVM_S390_STOP_FLAG_STORE_STATUS	0x01
काष्ठा kvm_s390_stop_info अणु
	__u32 flags;
पूर्ण;

काष्ठा kvm_s390_mchk_info अणु
	__u64 cr14;
	__u64 mcic;
	__u64 failing_storage_address;
	__u32 ext_damage_code;
	__u32 pad;
	__u8 fixed_logout[16];
पूर्ण;

काष्ठा kvm_s390_irq अणु
	__u64 type;
	जोड़ अणु
		काष्ठा kvm_s390_io_info io;
		काष्ठा kvm_s390_ext_info ext;
		काष्ठा kvm_s390_pgm_info pgm;
		काष्ठा kvm_s390_emerg_info emerg;
		काष्ठा kvm_s390_extcall_info extcall;
		काष्ठा kvm_s390_prefix_info prefix;
		काष्ठा kvm_s390_stop_info stop;
		काष्ठा kvm_s390_mchk_info mchk;
		अक्षर reserved[64];
	पूर्ण u;
पूर्ण;

काष्ठा kvm_s390_irq_state अणु
	__u64 buf;
	__u32 flags;        /* will stay unused क्रम compatibility reasons */
	__u32 len;
	__u32 reserved[4];  /* will stay unused क्रम compatibility reasons */
पूर्ण;

/* क्रम KVM_SET_GUEST_DEBUG */

#घोषणा KVM_GUESTDBG_ENABLE		0x00000001
#घोषणा KVM_GUESTDBG_SINGLESTEP		0x00000002

काष्ठा kvm_guest_debug अणु
	__u32 control;
	__u32 pad;
	काष्ठा kvm_guest_debug_arch arch;
पूर्ण;

क्रमागत अणु
	kvm_ioeventfd_flag_nr_datamatch,
	kvm_ioeventfd_flag_nr_pio,
	kvm_ioeventfd_flag_nr_deassign,
	kvm_ioeventfd_flag_nr_virtio_ccw_notअगरy,
	kvm_ioeventfd_flag_nr_fast_mmio,
	kvm_ioeventfd_flag_nr_max,
पूर्ण;

#घोषणा KVM_IOEVENTFD_FLAG_DATAMATCH (1 << kvm_ioeventfd_flag_nr_datamatch)
#घोषणा KVM_IOEVENTFD_FLAG_PIO       (1 << kvm_ioeventfd_flag_nr_pio)
#घोषणा KVM_IOEVENTFD_FLAG_DEASSIGN  (1 << kvm_ioeventfd_flag_nr_deassign)
#घोषणा KVM_IOEVENTFD_FLAG_VIRTIO_CCW_NOTIFY \
	(1 << kvm_ioeventfd_flag_nr_virtio_ccw_notअगरy)

#घोषणा KVM_IOEVENTFD_VALID_FLAG_MASK  ((1 << kvm_ioeventfd_flag_nr_max) - 1)

काष्ठा kvm_ioeventfd अणु
	__u64 datamatch;
	__u64 addr;        /* legal pio/mmio address */
	__u32 len;         /* 1, 2, 4, or 8 bytes; or 0 to ignore length */
	__s32 fd;
	__u32 flags;
	__u8  pad[36];
पूर्ण;

#घोषणा KVM_X86_DISABLE_EXITS_MWAIT          (1 << 0)
#घोषणा KVM_X86_DISABLE_EXITS_HLT            (1 << 1)
#घोषणा KVM_X86_DISABLE_EXITS_PAUSE          (1 << 2)
#घोषणा KVM_X86_DISABLE_EXITS_CSTATE         (1 << 3)
#घोषणा KVM_X86_DISABLE_VALID_EXITS          (KVM_X86_DISABLE_EXITS_MWAIT | \
                                              KVM_X86_DISABLE_EXITS_HLT | \
                                              KVM_X86_DISABLE_EXITS_PAUSE | \
                                              KVM_X86_DISABLE_EXITS_CSTATE)

/* क्रम KVM_ENABLE_CAP */
काष्ठा kvm_enable_cap अणु
	/* in */
	__u32 cap;
	__u32 flags;
	__u64 args[4];
	__u8  pad[64];
पूर्ण;

/* क्रम KVM_PPC_GET_PVINFO */

#घोषणा KVM_PPC_PVINFO_FLAGS_EV_IDLE   (1<<0)

काष्ठा kvm_ppc_pvinfo अणु
	/* out */
	__u32 flags;
	__u32 hcall[4];
	__u8  pad[108];
पूर्ण;

/* क्रम KVM_PPC_GET_SMMU_INFO */
#घोषणा KVM_PPC_PAGE_SIZES_MAX_SZ	8

काष्ठा kvm_ppc_one_page_size अणु
	__u32 page_shअगरt;	/* Page shअगरt (or 0) */
	__u32 pte_enc;		/* Encoding in the HPTE (>>12) */
पूर्ण;

काष्ठा kvm_ppc_one_seg_page_size अणु
	__u32 page_shअगरt;	/* Base page shअगरt of segment (or 0) */
	__u32 slb_enc;		/* SLB encoding क्रम BookS */
	काष्ठा kvm_ppc_one_page_size enc[KVM_PPC_PAGE_SIZES_MAX_SZ];
पूर्ण;

#घोषणा KVM_PPC_PAGE_SIZES_REAL		0x00000001
#घोषणा KVM_PPC_1T_SEGMENTS		0x00000002
#घोषणा KVM_PPC_NO_HASH			0x00000004

काष्ठा kvm_ppc_smmu_info अणु
	__u64 flags;
	__u32 slb_size;
	__u16 data_keys;	/* # storage keys supported क्रम data */
	__u16 instr_keys;	/* # storage keys supported क्रम inकाष्ठाions */
	काष्ठा kvm_ppc_one_seg_page_size sps[KVM_PPC_PAGE_SIZES_MAX_SZ];
पूर्ण;

/* क्रम KVM_PPC_RESIZE_HPT_अणुPREPARE,COMMITपूर्ण */
काष्ठा kvm_ppc_resize_hpt अणु
	__u64 flags;
	__u32 shअगरt;
	__u32 pad;
पूर्ण;

#घोषणा KVMIO 0xAE

/* machine type bits, to be used as argument to KVM_CREATE_VM */
#घोषणा KVM_VM_S390_UCONTROL	1

/* on ppc, 0 indicate शेष, 1 should क्रमce HV and 2 PR */
#घोषणा KVM_VM_PPC_HV 1
#घोषणा KVM_VM_PPC_PR 2

/* on MIPS, 0 indicates स्वतः, 1 क्रमces VZ ASE, 2 क्रमces trap & emulate */
#घोषणा KVM_VM_MIPS_AUTO	0
#घोषणा KVM_VM_MIPS_VZ		1
#घोषणा KVM_VM_MIPS_TE		2

#घोषणा KVM_S390_SIE_PAGE_OFFSET 1

/*
 * On arm64, machine type can be used to request the physical
 * address size क्रम the VM. Bits[7-0] are reserved क्रम the guest
 * PA size shअगरt (i.e, log2(PA_Size)). For backward compatibility,
 * value 0 implies the शेष IPA size, 40bits.
 */
#घोषणा KVM_VM_TYPE_ARM_IPA_SIZE_MASK	0xffULL
#घोषणा KVM_VM_TYPE_ARM_IPA_SIZE(x)		\
	((x) & KVM_VM_TYPE_ARM_IPA_SIZE_MASK)
/*
 * ioctls क्रम /dev/kvm fds:
 */
#घोषणा KVM_GET_API_VERSION       _IO(KVMIO,   0x00)
#घोषणा KVM_CREATE_VM             _IO(KVMIO,   0x01) /* वापसs a VM fd */
#घोषणा KVM_GET_MSR_INDEX_LIST    _IOWR(KVMIO, 0x02, काष्ठा kvm_msr_list)

#घोषणा KVM_S390_ENABLE_SIE       _IO(KVMIO,   0x06)
/*
 * Check अगर a kvm extension is available.  Argument is extension number,
 * वापस is 1 (yes) or 0 (no, sorry).
 */
#घोषणा KVM_CHECK_EXTENSION       _IO(KVMIO,   0x03)
/*
 * Get size क्रम mmap(vcpu_fd)
 */
#घोषणा KVM_GET_VCPU_MMAP_SIZE    _IO(KVMIO,   0x04) /* in bytes */
#घोषणा KVM_GET_SUPPORTED_CPUID   _IOWR(KVMIO, 0x05, काष्ठा kvm_cpuid2)
#घोषणा KVM_TRACE_ENABLE          __KVM_DEPRECATED_MAIN_W_0x06
#घोषणा KVM_TRACE_PAUSE           __KVM_DEPRECATED_MAIN_0x07
#घोषणा KVM_TRACE_DISABLE         __KVM_DEPRECATED_MAIN_0x08
#घोषणा KVM_GET_EMULATED_CPUID	  _IOWR(KVMIO, 0x09, काष्ठा kvm_cpuid2)
#घोषणा KVM_GET_MSR_FEATURE_INDEX_LIST    _IOWR(KVMIO, 0x0a, काष्ठा kvm_msr_list)

/*
 * Extension capability list.
 */
#घोषणा KVM_CAP_IRQCHIP	  0
#घोषणा KVM_CAP_HLT	  1
#घोषणा KVM_CAP_MMU_SHADOW_CACHE_CONTROL 2
#घोषणा KVM_CAP_USER_MEMORY 3
#घोषणा KVM_CAP_SET_TSS_ADDR 4
#घोषणा KVM_CAP_VAPIC 6
#घोषणा KVM_CAP_EXT_CPUID 7
#घोषणा KVM_CAP_CLOCKSOURCE 8
#घोषणा KVM_CAP_NR_VCPUS 9       /* वापसs recommended max vcpus per vm */
#घोषणा KVM_CAP_NR_MEMSLOTS 10   /* वापसs max memory slots per vm */
#घोषणा KVM_CAP_PIT 11
#घोषणा KVM_CAP_NOP_IO_DELAY 12
#घोषणा KVM_CAP_PV_MMU 13
#घोषणा KVM_CAP_MP_STATE 14
#घोषणा KVM_CAP_COALESCED_MMIO 15
#घोषणा KVM_CAP_SYNC_MMU 16  /* Changes to host mmap are reflected in guest */
#घोषणा KVM_CAP_IOMMU 18
/* Bug in KVM_SET_USER_MEMORY_REGION fixed: */
#घोषणा KVM_CAP_DESTROY_MEMORY_REGION_WORKS 21
#घोषणा KVM_CAP_USER_NMI 22
#अगर_घोषित __KVM_HAVE_GUEST_DEBUG
#घोषणा KVM_CAP_SET_GUEST_DEBUG 23
#पूर्ण_अगर
#अगर_घोषित __KVM_HAVE_PIT
#घोषणा KVM_CAP_REINJECT_CONTROL 24
#पूर्ण_अगर
#घोषणा KVM_CAP_IRQ_ROUTING 25
#घोषणा KVM_CAP_IRQ_INJECT_STATUS 26
#घोषणा KVM_CAP_ASSIGN_DEV_IRQ 29
/* Another bug in KVM_SET_USER_MEMORY_REGION fixed: */
#घोषणा KVM_CAP_JOIN_MEMORY_REGIONS_WORKS 30
#अगर_घोषित __KVM_HAVE_MCE
#घोषणा KVM_CAP_MCE 31
#पूर्ण_अगर
#घोषणा KVM_CAP_IRQFD 32
#अगर_घोषित __KVM_HAVE_PIT
#घोषणा KVM_CAP_PIT2 33
#पूर्ण_अगर
#घोषणा KVM_CAP_SET_BOOT_CPU_ID 34
#अगर_घोषित __KVM_HAVE_PIT_STATE2
#घोषणा KVM_CAP_PIT_STATE2 35
#पूर्ण_अगर
#घोषणा KVM_CAP_IOEVENTFD 36
#घोषणा KVM_CAP_SET_IDENTITY_MAP_ADDR 37
#अगर_घोषित __KVM_HAVE_XEN_HVM
#घोषणा KVM_CAP_XEN_HVM 38
#पूर्ण_अगर
#घोषणा KVM_CAP_ADJUST_CLOCK 39
#घोषणा KVM_CAP_INTERNAL_ERROR_DATA 40
#अगर_घोषित __KVM_HAVE_VCPU_EVENTS
#घोषणा KVM_CAP_VCPU_EVENTS 41
#पूर्ण_अगर
#घोषणा KVM_CAP_S390_PSW 42
#घोषणा KVM_CAP_PPC_SEGSTATE 43
#घोषणा KVM_CAP_HYPERV 44
#घोषणा KVM_CAP_HYPERV_VAPIC 45
#घोषणा KVM_CAP_HYPERV_SPIN 46
#घोषणा KVM_CAP_PCI_SEGMENT 47
#घोषणा KVM_CAP_PPC_PAIRED_SINGLES 48
#घोषणा KVM_CAP_INTR_SHADOW 49
#अगर_घोषित __KVM_HAVE_DEBUGREGS
#घोषणा KVM_CAP_DEBUGREGS 50
#पूर्ण_अगर
#घोषणा KVM_CAP_X86_ROBUST_SINGLESTEP 51
#घोषणा KVM_CAP_PPC_OSI 52
#घोषणा KVM_CAP_PPC_UNSET_IRQ 53
#घोषणा KVM_CAP_ENABLE_CAP 54
#अगर_घोषित __KVM_HAVE_XSAVE
#घोषणा KVM_CAP_XSAVE 55
#पूर्ण_अगर
#अगर_घोषित __KVM_HAVE_XCRS
#घोषणा KVM_CAP_XCRS 56
#पूर्ण_अगर
#घोषणा KVM_CAP_PPC_GET_PVINFO 57
#घोषणा KVM_CAP_PPC_IRQ_LEVEL 58
#घोषणा KVM_CAP_ASYNC_PF 59
#घोषणा KVM_CAP_TSC_CONTROL 60
#घोषणा KVM_CAP_GET_TSC_KHZ 61
#घोषणा KVM_CAP_PPC_BOOKE_SREGS 62
#घोषणा KVM_CAP_SPAPR_TCE 63
#घोषणा KVM_CAP_PPC_SMT 64
#घोषणा KVM_CAP_PPC_RMA	65
#घोषणा KVM_CAP_MAX_VCPUS 66       /* वापसs max vcpus per vm */
#घोषणा KVM_CAP_PPC_HIOR 67
#घोषणा KVM_CAP_PPC_PAPR 68
#घोषणा KVM_CAP_SW_TLB 69
#घोषणा KVM_CAP_ONE_REG 70
#घोषणा KVM_CAP_S390_GMAP 71
#घोषणा KVM_CAP_TSC_DEADLINE_TIMER 72
#घोषणा KVM_CAP_S390_UCONTROL 73
#घोषणा KVM_CAP_SYNC_REGS 74
#घोषणा KVM_CAP_PCI_2_3 75
#घोषणा KVM_CAP_KVMCLOCK_CTRL 76
#घोषणा KVM_CAP_SIGNAL_MSI 77
#घोषणा KVM_CAP_PPC_GET_SMMU_INFO 78
#घोषणा KVM_CAP_S390_COW 79
#घोषणा KVM_CAP_PPC_ALLOC_HTAB 80
#घोषणा KVM_CAP_READONLY_MEM 81
#घोषणा KVM_CAP_IRQFD_RESAMPLE 82
#घोषणा KVM_CAP_PPC_BOOKE_WATCHDOG 83
#घोषणा KVM_CAP_PPC_HTAB_FD 84
#घोषणा KVM_CAP_S390_CSS_SUPPORT 85
#घोषणा KVM_CAP_PPC_EPR 86
#घोषणा KVM_CAP_ARM_PSCI 87
#घोषणा KVM_CAP_ARM_SET_DEVICE_ADDR 88
#घोषणा KVM_CAP_DEVICE_CTRL 89
#घोषणा KVM_CAP_IRQ_MPIC 90
#घोषणा KVM_CAP_PPC_RTAS 91
#घोषणा KVM_CAP_IRQ_XICS 92
#घोषणा KVM_CAP_ARM_EL1_32BIT 93
#घोषणा KVM_CAP_SPAPR_MULTITCE 94
#घोषणा KVM_CAP_EXT_EMUL_CPUID 95
#घोषणा KVM_CAP_HYPERV_TIME 96
#घोषणा KVM_CAP_IOAPIC_POLARITY_IGNORED 97
#घोषणा KVM_CAP_ENABLE_CAP_VM 98
#घोषणा KVM_CAP_S390_IRQCHIP 99
#घोषणा KVM_CAP_IOEVENTFD_NO_LENGTH 100
#घोषणा KVM_CAP_VM_ATTRIBUTES 101
#घोषणा KVM_CAP_ARM_PSCI_0_2 102
#घोषणा KVM_CAP_PPC_FIXUP_HCALL 103
#घोषणा KVM_CAP_PPC_ENABLE_HCALL 104
#घोषणा KVM_CAP_CHECK_EXTENSION_VM 105
#घोषणा KVM_CAP_S390_USER_SIGP 106
#घोषणा KVM_CAP_S390_VECTOR_REGISTERS 107
#घोषणा KVM_CAP_S390_MEM_OP 108
#घोषणा KVM_CAP_S390_USER_STSI 109
#घोषणा KVM_CAP_S390_SKEYS 110
#घोषणा KVM_CAP_MIPS_FPU 111
#घोषणा KVM_CAP_MIPS_MSA 112
#घोषणा KVM_CAP_S390_INJECT_IRQ 113
#घोषणा KVM_CAP_S390_IRQ_STATE 114
#घोषणा KVM_CAP_PPC_HWRNG 115
#घोषणा KVM_CAP_DISABLE_QUIRKS 116
#घोषणा KVM_CAP_X86_SMM 117
#घोषणा KVM_CAP_MULTI_ADDRESS_SPACE 118
#घोषणा KVM_CAP_GUEST_DEBUG_HW_BPS 119
#घोषणा KVM_CAP_GUEST_DEBUG_HW_WPS 120
#घोषणा KVM_CAP_SPLIT_IRQCHIP 121
#घोषणा KVM_CAP_IOEVENTFD_ANY_LENGTH 122
#घोषणा KVM_CAP_HYPERV_SYNIC 123
#घोषणा KVM_CAP_S390_RI 124
#घोषणा KVM_CAP_SPAPR_TCE_64 125
#घोषणा KVM_CAP_ARM_PMU_V3 126
#घोषणा KVM_CAP_VCPU_ATTRIBUTES 127
#घोषणा KVM_CAP_MAX_VCPU_ID 128
#घोषणा KVM_CAP_X2APIC_API 129
#घोषणा KVM_CAP_S390_USER_INSTR0 130
#घोषणा KVM_CAP_MSI_DEVID 131
#घोषणा KVM_CAP_PPC_HTM 132
#घोषणा KVM_CAP_SPAPR_RESIZE_HPT 133
#घोषणा KVM_CAP_PPC_MMU_RADIX 134
#घोषणा KVM_CAP_PPC_MMU_HASH_V3 135
#घोषणा KVM_CAP_IMMEDIATE_EXIT 136
#घोषणा KVM_CAP_MIPS_VZ 137
#घोषणा KVM_CAP_MIPS_TE 138
#घोषणा KVM_CAP_MIPS_64BIT 139
#घोषणा KVM_CAP_S390_GS 140
#घोषणा KVM_CAP_S390_AIS 141
#घोषणा KVM_CAP_SPAPR_TCE_VFIO 142
#घोषणा KVM_CAP_X86_DISABLE_EXITS 143
#घोषणा KVM_CAP_ARM_USER_IRQ 144
#घोषणा KVM_CAP_S390_CMMA_MIGRATION 145
#घोषणा KVM_CAP_PPC_FWNMI 146
#घोषणा KVM_CAP_PPC_SMT_POSSIBLE 147
#घोषणा KVM_CAP_HYPERV_SYNIC2 148
#घोषणा KVM_CAP_HYPERV_VP_INDEX 149
#घोषणा KVM_CAP_S390_AIS_MIGRATION 150
#घोषणा KVM_CAP_PPC_GET_CPU_CHAR 151
#घोषणा KVM_CAP_S390_BPB 152
#घोषणा KVM_CAP_GET_MSR_FEATURES 153
#घोषणा KVM_CAP_HYPERV_EVENTFD 154
#घोषणा KVM_CAP_HYPERV_TLBFLUSH 155
#घोषणा KVM_CAP_S390_HPAGE_1M 156
#घोषणा KVM_CAP_NESTED_STATE 157
#घोषणा KVM_CAP_ARM_INJECT_SERROR_ESR 158
#घोषणा KVM_CAP_MSR_PLATFORM_INFO 159
#घोषणा KVM_CAP_PPC_NESTED_HV 160
#घोषणा KVM_CAP_HYPERV_SEND_IPI 161
#घोषणा KVM_CAP_COALESCED_PIO 162
#घोषणा KVM_CAP_HYPERV_ENLIGHTENED_VMCS 163
#घोषणा KVM_CAP_EXCEPTION_PAYLOAD 164
#घोषणा KVM_CAP_ARM_VM_IPA_SIZE 165
#घोषणा KVM_CAP_MANUAL_सूचीTY_LOG_PROTECT 166 /* Obsolete */
#घोषणा KVM_CAP_HYPERV_CPUID 167
#घोषणा KVM_CAP_MANUAL_सूचीTY_LOG_PROTECT2 168
#घोषणा KVM_CAP_PPC_IRQ_XIVE 169
#घोषणा KVM_CAP_ARM_SVE 170
#घोषणा KVM_CAP_ARM_PTRAUTH_ADDRESS 171
#घोषणा KVM_CAP_ARM_PTRAUTH_GENERIC 172
#घोषणा KVM_CAP_PMU_EVENT_FILTER 173
#घोषणा KVM_CAP_ARM_IRQ_LINE_LAYOUT_2 174
#घोषणा KVM_CAP_HYPERV_सूचीECT_TLBFLUSH 175
#घोषणा KVM_CAP_PPC_GUEST_DEBUG_SSTEP 176
#घोषणा KVM_CAP_ARM_NISV_TO_USER 177
#घोषणा KVM_CAP_ARM_INJECT_EXT_DABT 178
#घोषणा KVM_CAP_S390_VCPU_RESETS 179
#घोषणा KVM_CAP_S390_PROTECTED 180
#घोषणा KVM_CAP_PPC_SECURE_GUEST 181
#घोषणा KVM_CAP_HALT_POLL 182
#घोषणा KVM_CAP_ASYNC_PF_INT 183
#घोषणा KVM_CAP_LAST_CPU 184
#घोषणा KVM_CAP_SMALLER_MAXPHYADDR 185
#घोषणा KVM_CAP_S390_DIAG318 186
#घोषणा KVM_CAP_STEAL_TIME 187
#घोषणा KVM_CAP_X86_USER_SPACE_MSR 188
#घोषणा KVM_CAP_X86_MSR_FILTER 189
#घोषणा KVM_CAP_ENFORCE_PV_FEATURE_CPUID 190
#घोषणा KVM_CAP_SYS_HYPERV_CPUID 191
#घोषणा KVM_CAP_सूचीTY_LOG_RING 192
#घोषणा KVM_CAP_X86_BUS_LOCK_EXIT 193
#घोषणा KVM_CAP_PPC_DAWR1 194
#घोषणा KVM_CAP_SET_GUEST_DEBUG2 195
#घोषणा KVM_CAP_SGX_ATTRIBUTE 196
#घोषणा KVM_CAP_VM_COPY_ENC_CONTEXT_FROM 197
#घोषणा KVM_CAP_PTP_KVM 198

#अगर_घोषित KVM_CAP_IRQ_ROUTING

काष्ठा kvm_irq_routing_irqchip अणु
	__u32 irqchip;
	__u32 pin;
पूर्ण;

काष्ठा kvm_irq_routing_msi अणु
	__u32 address_lo;
	__u32 address_hi;
	__u32 data;
	जोड़ अणु
		__u32 pad;
		__u32 devid;
	पूर्ण;
पूर्ण;

काष्ठा kvm_irq_routing_s390_adapter अणु
	__u64 ind_addr;
	__u64 summary_addr;
	__u64 ind_offset;
	__u32 summary_offset;
	__u32 adapter_id;
पूर्ण;

काष्ठा kvm_irq_routing_hv_sपूर्णांक अणु
	__u32 vcpu;
	__u32 sपूर्णांक;
पूर्ण;

/* gsi routing entry types */
#घोषणा KVM_IRQ_ROUTING_IRQCHIP 1
#घोषणा KVM_IRQ_ROUTING_MSI 2
#घोषणा KVM_IRQ_ROUTING_S390_ADAPTER 3
#घोषणा KVM_IRQ_ROUTING_HV_SINT 4

काष्ठा kvm_irq_routing_entry अणु
	__u32 gsi;
	__u32 type;
	__u32 flags;
	__u32 pad;
	जोड़ अणु
		काष्ठा kvm_irq_routing_irqchip irqchip;
		काष्ठा kvm_irq_routing_msi msi;
		काष्ठा kvm_irq_routing_s390_adapter adapter;
		काष्ठा kvm_irq_routing_hv_sपूर्णांक hv_sपूर्णांक;
		__u32 pad[8];
	पूर्ण u;
पूर्ण;

काष्ठा kvm_irq_routing अणु
	__u32 nr;
	__u32 flags;
	काष्ठा kvm_irq_routing_entry entries[0];
पूर्ण;

#पूर्ण_अगर

#अगर_घोषित KVM_CAP_MCE
/* x86 MCE */
काष्ठा kvm_x86_mce अणु
	__u64 status;
	__u64 addr;
	__u64 misc;
	__u64 mcg_status;
	__u8 bank;
	__u8 pad1[7];
	__u64 pad2[3];
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित KVM_CAP_XEN_HVM
#घोषणा KVM_XEN_HVM_CONFIG_HYPERCALL_MSR	(1 << 0)
#घोषणा KVM_XEN_HVM_CONFIG_INTERCEPT_HCALL	(1 << 1)
#घोषणा KVM_XEN_HVM_CONFIG_SHARED_INFO		(1 << 2)
#घोषणा KVM_XEN_HVM_CONFIG_RUNSTATE		(1 << 3)

काष्ठा kvm_xen_hvm_config अणु
	__u32 flags;
	__u32 msr;
	__u64 blob_addr_32;
	__u64 blob_addr_64;
	__u8 blob_size_32;
	__u8 blob_size_64;
	__u8 pad2[30];
पूर्ण;
#पूर्ण_अगर

#घोषणा KVM_IRQFD_FLAG_DEASSIGN (1 << 0)
/*
 * Available with KVM_CAP_IRQFD_RESAMPLE
 *
 * KVM_IRQFD_FLAG_RESAMPLE indicates resamplefd is valid and specअगरies
 * the irqfd to operate in resampling mode क्रम level triggered पूर्णांकerrupt
 * emulation.  See Documentation/virt/kvm/api.rst.
 */
#घोषणा KVM_IRQFD_FLAG_RESAMPLE (1 << 1)

काष्ठा kvm_irqfd अणु
	__u32 fd;
	__u32 gsi;
	__u32 flags;
	__u32 resamplefd;
	__u8  pad[16];
पूर्ण;

/* For KVM_CAP_ADJUST_CLOCK */

/* Do not use 1, KVM_CHECK_EXTENSION वापसed it beक्रमe we had flags.  */
#घोषणा KVM_CLOCK_TSC_STABLE		2

काष्ठा kvm_घड़ी_data अणु
	__u64 घड़ी;
	__u32 flags;
	__u32 pad[9];
पूर्ण;

/* For KVM_CAP_SW_TLB */

#घोषणा KVM_MMU_FSL_BOOKE_NOHV		0
#घोषणा KVM_MMU_FSL_BOOKE_HV		1

काष्ठा kvm_config_tlb अणु
	__u64 params;
	__u64 array;
	__u32 mmu_type;
	__u32 array_len;
पूर्ण;

काष्ठा kvm_dirty_tlb अणु
	__u64 biपंचांगap;
	__u32 num_dirty;
पूर्ण;

/* Available with KVM_CAP_ONE_REG */

#घोषणा KVM_REG_ARCH_MASK	0xff00000000000000ULL
#घोषणा KVM_REG_GENERIC		0x0000000000000000ULL

/*
 * Architecture specअगरic रेजिस्टरs are to be defined in arch headers and
 * ORed with the arch identअगरier.
 */
#घोषणा KVM_REG_PPC		0x1000000000000000ULL
#घोषणा KVM_REG_X86		0x2000000000000000ULL
#घोषणा KVM_REG_IA64		0x3000000000000000ULL
#घोषणा KVM_REG_ARM		0x4000000000000000ULL
#घोषणा KVM_REG_S390		0x5000000000000000ULL
#घोषणा KVM_REG_ARM64		0x6000000000000000ULL
#घोषणा KVM_REG_MIPS		0x7000000000000000ULL
#घोषणा KVM_REG_RISCV		0x8000000000000000ULL

#घोषणा KVM_REG_SIZE_SHIFT	52
#घोषणा KVM_REG_SIZE_MASK	0x00f0000000000000ULL
#घोषणा KVM_REG_SIZE_U8		0x0000000000000000ULL
#घोषणा KVM_REG_SIZE_U16	0x0010000000000000ULL
#घोषणा KVM_REG_SIZE_U32	0x0020000000000000ULL
#घोषणा KVM_REG_SIZE_U64	0x0030000000000000ULL
#घोषणा KVM_REG_SIZE_U128	0x0040000000000000ULL
#घोषणा KVM_REG_SIZE_U256	0x0050000000000000ULL
#घोषणा KVM_REG_SIZE_U512	0x0060000000000000ULL
#घोषणा KVM_REG_SIZE_U1024	0x0070000000000000ULL
#घोषणा KVM_REG_SIZE_U2048	0x0080000000000000ULL

काष्ठा kvm_reg_list अणु
	__u64 n; /* number of regs */
	__u64 reg[0];
पूर्ण;

काष्ठा kvm_one_reg अणु
	__u64 id;
	__u64 addr;
पूर्ण;

#घोषणा KVM_MSI_VALID_DEVID	(1U << 0)
काष्ठा kvm_msi अणु
	__u32 address_lo;
	__u32 address_hi;
	__u32 data;
	__u32 flags;
	__u32 devid;
	__u8  pad[12];
पूर्ण;

काष्ठा kvm_arm_device_addr अणु
	__u64 id;
	__u64 addr;
पूर्ण;

/*
 * Device control API, available with KVM_CAP_DEVICE_CTRL
 */
#घोषणा KVM_CREATE_DEVICE_TEST		1

काष्ठा kvm_create_device अणु
	__u32	type;	/* in: KVM_DEV_TYPE_xxx */
	__u32	fd;	/* out: device handle */
	__u32	flags;	/* in: KVM_CREATE_DEVICE_xxx */
पूर्ण;

काष्ठा kvm_device_attr अणु
	__u32	flags;		/* no flags currently defined */
	__u32	group;		/* device-defined */
	__u64	attr;		/* group-defined */
	__u64	addr;		/* userspace address of attr data */
पूर्ण;

#घोषणा  KVM_DEV_VFIO_GROUP			1
#घोषणा   KVM_DEV_VFIO_GROUP_ADD			1
#घोषणा   KVM_DEV_VFIO_GROUP_DEL			2
#घोषणा   KVM_DEV_VFIO_GROUP_SET_SPAPR_TCE		3

क्रमागत kvm_device_type अणु
	KVM_DEV_TYPE_FSL_MPIC_20	= 1,
#घोषणा KVM_DEV_TYPE_FSL_MPIC_20	KVM_DEV_TYPE_FSL_MPIC_20
	KVM_DEV_TYPE_FSL_MPIC_42,
#घोषणा KVM_DEV_TYPE_FSL_MPIC_42	KVM_DEV_TYPE_FSL_MPIC_42
	KVM_DEV_TYPE_XICS,
#घोषणा KVM_DEV_TYPE_XICS		KVM_DEV_TYPE_XICS
	KVM_DEV_TYPE_VFIO,
#घोषणा KVM_DEV_TYPE_VFIO		KVM_DEV_TYPE_VFIO
	KVM_DEV_TYPE_ARM_VGIC_V2,
#घोषणा KVM_DEV_TYPE_ARM_VGIC_V2	KVM_DEV_TYPE_ARM_VGIC_V2
	KVM_DEV_TYPE_FLIC,
#घोषणा KVM_DEV_TYPE_FLIC		KVM_DEV_TYPE_FLIC
	KVM_DEV_TYPE_ARM_VGIC_V3,
#घोषणा KVM_DEV_TYPE_ARM_VGIC_V3	KVM_DEV_TYPE_ARM_VGIC_V3
	KVM_DEV_TYPE_ARM_VGIC_ITS,
#घोषणा KVM_DEV_TYPE_ARM_VGIC_ITS	KVM_DEV_TYPE_ARM_VGIC_ITS
	KVM_DEV_TYPE_XIVE,
#घोषणा KVM_DEV_TYPE_XIVE		KVM_DEV_TYPE_XIVE
	KVM_DEV_TYPE_ARM_PV_TIME,
#घोषणा KVM_DEV_TYPE_ARM_PV_TIME	KVM_DEV_TYPE_ARM_PV_TIME
	KVM_DEV_TYPE_MAX,
पूर्ण;

काष्ठा kvm_vfio_spapr_tce अणु
	__s32	groupfd;
	__s32	tablefd;
पूर्ण;

/*
 * ioctls क्रम VM fds
 */
#घोषणा KVM_SET_MEMORY_REGION     _IOW(KVMIO,  0x40, काष्ठा kvm_memory_region)
/*
 * KVM_CREATE_VCPU receives as a parameter the vcpu slot, and वापसs
 * a vcpu fd.
 */
#घोषणा KVM_CREATE_VCPU           _IO(KVMIO,   0x41)
#घोषणा KVM_GET_सूचीTY_LOG         _IOW(KVMIO,  0x42, काष्ठा kvm_dirty_log)
/* KVM_SET_MEMORY_ALIAS is obsolete: */
#घोषणा KVM_SET_MEMORY_ALIAS      _IOW(KVMIO,  0x43, काष्ठा kvm_memory_alias)
#घोषणा KVM_SET_NR_MMU_PAGES      _IO(KVMIO,   0x44)
#घोषणा KVM_GET_NR_MMU_PAGES      _IO(KVMIO,   0x45)
#घोषणा KVM_SET_USER_MEMORY_REGION _IOW(KVMIO, 0x46, \
					काष्ठा kvm_userspace_memory_region)
#घोषणा KVM_SET_TSS_ADDR          _IO(KVMIO,   0x47)
#घोषणा KVM_SET_IDENTITY_MAP_ADDR _IOW(KVMIO,  0x48, __u64)

/* enable ucontrol क्रम s390 */
काष्ठा kvm_s390_ucas_mapping अणु
	__u64 user_addr;
	__u64 vcpu_addr;
	__u64 length;
पूर्ण;
#घोषणा KVM_S390_UCAS_MAP        _IOW(KVMIO, 0x50, काष्ठा kvm_s390_ucas_mapping)
#घोषणा KVM_S390_UCAS_UNMAP      _IOW(KVMIO, 0x51, काष्ठा kvm_s390_ucas_mapping)
#घोषणा KVM_S390_VCPU_FAULT	 _IOW(KVMIO, 0x52, अचिन्हित दीर्घ)

/* Device model IOC */
#घोषणा KVM_CREATE_IRQCHIP        _IO(KVMIO,   0x60)
#घोषणा KVM_IRQ_LINE              _IOW(KVMIO,  0x61, काष्ठा kvm_irq_level)
#घोषणा KVM_GET_IRQCHIP           _IOWR(KVMIO, 0x62, काष्ठा kvm_irqchip)
#घोषणा KVM_SET_IRQCHIP           _IOR(KVMIO,  0x63, काष्ठा kvm_irqchip)
#घोषणा KVM_CREATE_PIT            _IO(KVMIO,   0x64)
#घोषणा KVM_GET_PIT               _IOWR(KVMIO, 0x65, काष्ठा kvm_pit_state)
#घोषणा KVM_SET_PIT               _IOR(KVMIO,  0x66, काष्ठा kvm_pit_state)
#घोषणा KVM_IRQ_LINE_STATUS       _IOWR(KVMIO, 0x67, काष्ठा kvm_irq_level)
#घोषणा KVM_REGISTER_COALESCED_MMIO \
			_IOW(KVMIO,  0x67, काष्ठा kvm_coalesced_mmio_zone)
#घोषणा KVM_UNREGISTER_COALESCED_MMIO \
			_IOW(KVMIO,  0x68, काष्ठा kvm_coalesced_mmio_zone)
#घोषणा KVM_ASSIGN_PCI_DEVICE     _IOR(KVMIO,  0x69, \
				       काष्ठा kvm_asचिन्हित_pci_dev)
#घोषणा KVM_SET_GSI_ROUTING       _IOW(KVMIO,  0x6a, काष्ठा kvm_irq_routing)
/* deprecated, replaced by KVM_ASSIGN_DEV_IRQ */
#घोषणा KVM_ASSIGN_IRQ            __KVM_DEPRECATED_VM_R_0x70
#घोषणा KVM_ASSIGN_DEV_IRQ        _IOW(KVMIO,  0x70, काष्ठा kvm_asचिन्हित_irq)
#घोषणा KVM_REINJECT_CONTROL      _IO(KVMIO,   0x71)
#घोषणा KVM_DEASSIGN_PCI_DEVICE   _IOW(KVMIO,  0x72, \
				       काष्ठा kvm_asचिन्हित_pci_dev)
#घोषणा KVM_ASSIGN_SET_MSIX_NR    _IOW(KVMIO,  0x73, \
				       काष्ठा kvm_asचिन्हित_msix_nr)
#घोषणा KVM_ASSIGN_SET_MSIX_ENTRY _IOW(KVMIO,  0x74, \
				       काष्ठा kvm_asचिन्हित_msix_entry)
#घोषणा KVM_DEASSIGN_DEV_IRQ      _IOW(KVMIO,  0x75, काष्ठा kvm_asचिन्हित_irq)
#घोषणा KVM_IRQFD                 _IOW(KVMIO,  0x76, काष्ठा kvm_irqfd)
#घोषणा KVM_CREATE_PIT2		  _IOW(KVMIO,  0x77, काष्ठा kvm_pit_config)
#घोषणा KVM_SET_BOOT_CPU_ID       _IO(KVMIO,   0x78)
#घोषणा KVM_IOEVENTFD             _IOW(KVMIO,  0x79, काष्ठा kvm_ioeventfd)
#घोषणा KVM_XEN_HVM_CONFIG        _IOW(KVMIO,  0x7a, काष्ठा kvm_xen_hvm_config)
#घोषणा KVM_SET_CLOCK             _IOW(KVMIO,  0x7b, काष्ठा kvm_घड़ी_data)
#घोषणा KVM_GET_CLOCK             _IOR(KVMIO,  0x7c, काष्ठा kvm_घड़ी_data)
/* Available with KVM_CAP_PIT_STATE2 */
#घोषणा KVM_GET_PIT2              _IOR(KVMIO,  0x9f, काष्ठा kvm_pit_state2)
#घोषणा KVM_SET_PIT2              _IOW(KVMIO,  0xa0, काष्ठा kvm_pit_state2)
/* Available with KVM_CAP_PPC_GET_PVINFO */
#घोषणा KVM_PPC_GET_PVINFO	  _IOW(KVMIO,  0xa1, काष्ठा kvm_ppc_pvinfo)
/* Available with KVM_CAP_TSC_CONTROL */
#घोषणा KVM_SET_TSC_KHZ           _IO(KVMIO,  0xa2)
#घोषणा KVM_GET_TSC_KHZ           _IO(KVMIO,  0xa3)
/* Available with KVM_CAP_PCI_2_3 */
#घोषणा KVM_ASSIGN_SET_INTX_MASK  _IOW(KVMIO,  0xa4, \
				       काष्ठा kvm_asचिन्हित_pci_dev)
/* Available with KVM_CAP_SIGNAL_MSI */
#घोषणा KVM_SIGNAL_MSI            _IOW(KVMIO,  0xa5, काष्ठा kvm_msi)
/* Available with KVM_CAP_PPC_GET_SMMU_INFO */
#घोषणा KVM_PPC_GET_SMMU_INFO	  _IOR(KVMIO,  0xa6, काष्ठा kvm_ppc_smmu_info)
/* Available with KVM_CAP_PPC_ALLOC_HTAB */
#घोषणा KVM_PPC_ALLOCATE_HTAB	  _IOWR(KVMIO, 0xa7, __u32)
#घोषणा KVM_CREATE_SPAPR_TCE	  _IOW(KVMIO,  0xa8, काष्ठा kvm_create_spapr_tce)
#घोषणा KVM_CREATE_SPAPR_TCE_64	  _IOW(KVMIO,  0xa8, \
				       काष्ठा kvm_create_spapr_tce_64)
/* Available with KVM_CAP_RMA */
#घोषणा KVM_ALLOCATE_RMA	  _IOR(KVMIO,  0xa9, काष्ठा kvm_allocate_rma)
/* Available with KVM_CAP_PPC_HTAB_FD */
#घोषणा KVM_PPC_GET_HTAB_FD	  _IOW(KVMIO,  0xaa, काष्ठा kvm_get_htab_fd)
/* Available with KVM_CAP_ARM_SET_DEVICE_ADDR */
#घोषणा KVM_ARM_SET_DEVICE_ADDR	  _IOW(KVMIO,  0xab, काष्ठा kvm_arm_device_addr)
/* Available with KVM_CAP_PPC_RTAS */
#घोषणा KVM_PPC_RTAS_DEFINE_TOKEN _IOW(KVMIO,  0xac, काष्ठा kvm_rtas_token_args)
/* Available with KVM_CAP_SPAPR_RESIZE_HPT */
#घोषणा KVM_PPC_RESIZE_HPT_PREPARE _IOR(KVMIO, 0xad, काष्ठा kvm_ppc_resize_hpt)
#घोषणा KVM_PPC_RESIZE_HPT_COMMIT  _IOR(KVMIO, 0xae, काष्ठा kvm_ppc_resize_hpt)
/* Available with KVM_CAP_PPC_RADIX_MMU or KVM_CAP_PPC_HASH_MMU_V3 */
#घोषणा KVM_PPC_CONFIGURE_V3_MMU  _IOW(KVMIO,  0xaf, काष्ठा kvm_ppc_mmuv3_cfg)
/* Available with KVM_CAP_PPC_RADIX_MMU */
#घोषणा KVM_PPC_GET_RMMU_INFO	  _IOW(KVMIO,  0xb0, काष्ठा kvm_ppc_rmmu_info)
/* Available with KVM_CAP_PPC_GET_CPU_CHAR */
#घोषणा KVM_PPC_GET_CPU_CHAR	  _IOR(KVMIO,  0xb1, काष्ठा kvm_ppc_cpu_अक्षर)
/* Available with KVM_CAP_PMU_EVENT_FILTER */
#घोषणा KVM_SET_PMU_EVENT_FILTER  _IOW(KVMIO,  0xb2, काष्ठा kvm_pmu_event_filter)
#घोषणा KVM_PPC_SVM_OFF		  _IO(KVMIO,  0xb3)

/* ioctl क्रम vm fd */
#घोषणा KVM_CREATE_DEVICE	  _IOWR(KVMIO,  0xe0, काष्ठा kvm_create_device)

/* ioctls क्रम fds वापसed by KVM_CREATE_DEVICE */
#घोषणा KVM_SET_DEVICE_ATTR	  _IOW(KVMIO,  0xe1, काष्ठा kvm_device_attr)
#घोषणा KVM_GET_DEVICE_ATTR	  _IOW(KVMIO,  0xe2, काष्ठा kvm_device_attr)
#घोषणा KVM_HAS_DEVICE_ATTR	  _IOW(KVMIO,  0xe3, काष्ठा kvm_device_attr)

/*
 * ioctls क्रम vcpu fds
 */
#घोषणा KVM_RUN                   _IO(KVMIO,   0x80)
#घोषणा KVM_GET_REGS              _IOR(KVMIO,  0x81, काष्ठा kvm_regs)
#घोषणा KVM_SET_REGS              _IOW(KVMIO,  0x82, काष्ठा kvm_regs)
#घोषणा KVM_GET_SREGS             _IOR(KVMIO,  0x83, काष्ठा kvm_sregs)
#घोषणा KVM_SET_SREGS             _IOW(KVMIO,  0x84, काष्ठा kvm_sregs)
#घोषणा KVM_TRANSLATE             _IOWR(KVMIO, 0x85, काष्ठा kvm_translation)
#घोषणा KVM_INTERRUPT             _IOW(KVMIO,  0x86, काष्ठा kvm_पूर्णांकerrupt)
/* KVM_DEBUG_GUEST is no दीर्घer supported, use KVM_SET_GUEST_DEBUG instead */
#घोषणा KVM_DEBUG_GUEST           __KVM_DEPRECATED_VCPU_W_0x87
#घोषणा KVM_GET_MSRS              _IOWR(KVMIO, 0x88, काष्ठा kvm_msrs)
#घोषणा KVM_SET_MSRS              _IOW(KVMIO,  0x89, काष्ठा kvm_msrs)
#घोषणा KVM_SET_CPUID             _IOW(KVMIO,  0x8a, काष्ठा kvm_cpuid)
#घोषणा KVM_SET_SIGNAL_MASK       _IOW(KVMIO,  0x8b, काष्ठा kvm_संकेत_mask)
#घोषणा KVM_GET_FPU               _IOR(KVMIO,  0x8c, काष्ठा kvm_fpu)
#घोषणा KVM_SET_FPU               _IOW(KVMIO,  0x8d, काष्ठा kvm_fpu)
#घोषणा KVM_GET_LAPIC             _IOR(KVMIO,  0x8e, काष्ठा kvm_lapic_state)
#घोषणा KVM_SET_LAPIC             _IOW(KVMIO,  0x8f, काष्ठा kvm_lapic_state)
#घोषणा KVM_SET_CPUID2            _IOW(KVMIO,  0x90, काष्ठा kvm_cpuid2)
#घोषणा KVM_GET_CPUID2            _IOWR(KVMIO, 0x91, काष्ठा kvm_cpuid2)
/* Available with KVM_CAP_VAPIC */
#घोषणा KVM_TPR_ACCESS_REPORTING  _IOWR(KVMIO, 0x92, काष्ठा kvm_tpr_access_ctl)
/* Available with KVM_CAP_VAPIC */
#घोषणा KVM_SET_VAPIC_ADDR        _IOW(KVMIO,  0x93, काष्ठा kvm_vapic_addr)
/* valid क्रम भव machine (क्रम भग्नing पूर्णांकerrupt)_and_ vcpu */
#घोषणा KVM_S390_INTERRUPT        _IOW(KVMIO,  0x94, काष्ठा kvm_s390_पूर्णांकerrupt)
/* store status क्रम s390 */
#घोषणा KVM_S390_STORE_STATUS_NOADDR    (-1ul)
#घोषणा KVM_S390_STORE_STATUS_PREFIXED  (-2ul)
#घोषणा KVM_S390_STORE_STATUS	  _IOW(KVMIO,  0x95, अचिन्हित दीर्घ)
/* initial ipl psw क्रम s390 */
#घोषणा KVM_S390_SET_INITIAL_PSW  _IOW(KVMIO,  0x96, काष्ठा kvm_s390_psw)
/* initial reset क्रम s390 */
#घोषणा KVM_S390_INITIAL_RESET    _IO(KVMIO,   0x97)
#घोषणा KVM_GET_MP_STATE          _IOR(KVMIO,  0x98, काष्ठा kvm_mp_state)
#घोषणा KVM_SET_MP_STATE          _IOW(KVMIO,  0x99, काष्ठा kvm_mp_state)
/* Available with KVM_CAP_USER_NMI */
#घोषणा KVM_NMI                   _IO(KVMIO,   0x9a)
/* Available with KVM_CAP_SET_GUEST_DEBUG */
#घोषणा KVM_SET_GUEST_DEBUG       _IOW(KVMIO,  0x9b, काष्ठा kvm_guest_debug)
/* MCE क्रम x86 */
#घोषणा KVM_X86_SETUP_MCE         _IOW(KVMIO,  0x9c, __u64)
#घोषणा KVM_X86_GET_MCE_CAP_SUPPORTED _IOR(KVMIO,  0x9d, __u64)
#घोषणा KVM_X86_SET_MCE           _IOW(KVMIO,  0x9e, काष्ठा kvm_x86_mce)
/* Available with KVM_CAP_VCPU_EVENTS */
#घोषणा KVM_GET_VCPU_EVENTS       _IOR(KVMIO,  0x9f, काष्ठा kvm_vcpu_events)
#घोषणा KVM_SET_VCPU_EVENTS       _IOW(KVMIO,  0xa0, काष्ठा kvm_vcpu_events)
/* Available with KVM_CAP_DEBUGREGS */
#घोषणा KVM_GET_DEBUGREGS         _IOR(KVMIO,  0xa1, काष्ठा kvm_debugregs)
#घोषणा KVM_SET_DEBUGREGS         _IOW(KVMIO,  0xa2, काष्ठा kvm_debugregs)
/*
 * vcpu version available with KVM_ENABLE_CAP
 * vm version available with KVM_CAP_ENABLE_CAP_VM
 */
#घोषणा KVM_ENABLE_CAP            _IOW(KVMIO,  0xa3, काष्ठा kvm_enable_cap)
/* Available with KVM_CAP_XSAVE */
#घोषणा KVM_GET_XSAVE		  _IOR(KVMIO,  0xa4, काष्ठा kvm_xsave)
#घोषणा KVM_SET_XSAVE		  _IOW(KVMIO,  0xa5, काष्ठा kvm_xsave)
/* Available with KVM_CAP_XCRS */
#घोषणा KVM_GET_XCRS		  _IOR(KVMIO,  0xa6, काष्ठा kvm_xcrs)
#घोषणा KVM_SET_XCRS		  _IOW(KVMIO,  0xa7, काष्ठा kvm_xcrs)
/* Available with KVM_CAP_SW_TLB */
#घोषणा KVM_सूचीTY_TLB		  _IOW(KVMIO,  0xaa, काष्ठा kvm_dirty_tlb)
/* Available with KVM_CAP_ONE_REG */
#घोषणा KVM_GET_ONE_REG		  _IOW(KVMIO,  0xab, काष्ठा kvm_one_reg)
#घोषणा KVM_SET_ONE_REG		  _IOW(KVMIO,  0xac, काष्ठा kvm_one_reg)
/* VM is being stopped by host */
#घोषणा KVM_KVMCLOCK_CTRL	  _IO(KVMIO,   0xad)
#घोषणा KVM_ARM_VCPU_INIT	  _IOW(KVMIO,  0xae, काष्ठा kvm_vcpu_init)
#घोषणा KVM_ARM_PREFERRED_TARGET  _IOR(KVMIO,  0xaf, काष्ठा kvm_vcpu_init)
#घोषणा KVM_GET_REG_LIST	  _IOWR(KVMIO, 0xb0, काष्ठा kvm_reg_list)
/* Available with KVM_CAP_S390_MEM_OP */
#घोषणा KVM_S390_MEM_OP		  _IOW(KVMIO,  0xb1, काष्ठा kvm_s390_mem_op)
/* Available with KVM_CAP_S390_SKEYS */
#घोषणा KVM_S390_GET_SKEYS      _IOW(KVMIO, 0xb2, काष्ठा kvm_s390_skeys)
#घोषणा KVM_S390_SET_SKEYS      _IOW(KVMIO, 0xb3, काष्ठा kvm_s390_skeys)
/* Available with KVM_CAP_S390_INJECT_IRQ */
#घोषणा KVM_S390_IRQ              _IOW(KVMIO,  0xb4, काष्ठा kvm_s390_irq)
/* Available with KVM_CAP_S390_IRQ_STATE */
#घोषणा KVM_S390_SET_IRQ_STATE	  _IOW(KVMIO, 0xb5, काष्ठा kvm_s390_irq_state)
#घोषणा KVM_S390_GET_IRQ_STATE	  _IOW(KVMIO, 0xb6, काष्ठा kvm_s390_irq_state)
/* Available with KVM_CAP_X86_SMM */
#घोषणा KVM_SMI                   _IO(KVMIO,   0xb7)
/* Available with KVM_CAP_S390_CMMA_MIGRATION */
#घोषणा KVM_S390_GET_CMMA_BITS      _IOWR(KVMIO, 0xb8, काष्ठा kvm_s390_cmma_log)
#घोषणा KVM_S390_SET_CMMA_BITS      _IOW(KVMIO, 0xb9, काष्ठा kvm_s390_cmma_log)
/* Memory Encryption Commands */
#घोषणा KVM_MEMORY_ENCRYPT_OP      _IOWR(KVMIO, 0xba, अचिन्हित दीर्घ)

काष्ठा kvm_enc_region अणु
	__u64 addr;
	__u64 size;
पूर्ण;

#घोषणा KVM_MEMORY_ENCRYPT_REG_REGION    _IOR(KVMIO, 0xbb, काष्ठा kvm_enc_region)
#घोषणा KVM_MEMORY_ENCRYPT_UNREG_REGION  _IOR(KVMIO, 0xbc, काष्ठा kvm_enc_region)

/* Available with KVM_CAP_HYPERV_EVENTFD */
#घोषणा KVM_HYPERV_EVENTFD        _IOW(KVMIO,  0xbd, काष्ठा kvm_hyperv_eventfd)

/* Available with KVM_CAP_NESTED_STATE */
#घोषणा KVM_GET_NESTED_STATE         _IOWR(KVMIO, 0xbe, काष्ठा kvm_nested_state)
#घोषणा KVM_SET_NESTED_STATE         _IOW(KVMIO,  0xbf, काष्ठा kvm_nested_state)

/* Available with KVM_CAP_MANUAL_सूचीTY_LOG_PROTECT_2 */
#घोषणा KVM_CLEAR_सूचीTY_LOG          _IOWR(KVMIO, 0xc0, काष्ठा kvm_clear_dirty_log)

/* Available with KVM_CAP_HYPERV_CPUID (vcpu) / KVM_CAP_SYS_HYPERV_CPUID (प्रणाली) */
#घोषणा KVM_GET_SUPPORTED_HV_CPUID _IOWR(KVMIO, 0xc1, काष्ठा kvm_cpuid2)

/* Available with KVM_CAP_ARM_SVE */
#घोषणा KVM_ARM_VCPU_FINALIZE	  _IOW(KVMIO,  0xc2, पूर्णांक)

/* Available with  KVM_CAP_S390_VCPU_RESETS */
#घोषणा KVM_S390_NORMAL_RESET	_IO(KVMIO,   0xc3)
#घोषणा KVM_S390_CLEAR_RESET	_IO(KVMIO,   0xc4)

काष्ठा kvm_s390_pv_sec_parm अणु
	__u64 origin;
	__u64 length;
पूर्ण;

काष्ठा kvm_s390_pv_unp अणु
	__u64 addr;
	__u64 size;
	__u64 tweak;
पूर्ण;

क्रमागत pv_cmd_id अणु
	KVM_PV_ENABLE,
	KVM_PV_DISABLE,
	KVM_PV_SET_SEC_PARMS,
	KVM_PV_UNPACK,
	KVM_PV_VERIFY,
	KVM_PV_PREP_RESET,
	KVM_PV_UNSHARE_ALL,
पूर्ण;

काष्ठा kvm_pv_cmd अणु
	__u32 cmd;	/* Command to be executed */
	__u16 rc;	/* Ultravisor वापस code */
	__u16 rrc;	/* Ultravisor वापस reason code */
	__u64 data;	/* Data or address */
	__u32 flags;    /* flags क्रम future extensions. Must be 0 क्रम now */
	__u32 reserved[3];
पूर्ण;

/* Available with KVM_CAP_S390_PROTECTED */
#घोषणा KVM_S390_PV_COMMAND		_IOWR(KVMIO, 0xc5, काष्ठा kvm_pv_cmd)

/* Available with KVM_CAP_X86_MSR_FILTER */
#घोषणा KVM_X86_SET_MSR_FILTER	_IOW(KVMIO,  0xc6, काष्ठा kvm_msr_filter)

/* Available with KVM_CAP_सूचीTY_LOG_RING */
#घोषणा KVM_RESET_सूचीTY_RINGS		_IO(KVMIO, 0xc7)

/* Per-VM Xen attributes */
#घोषणा KVM_XEN_HVM_GET_ATTR	_IOWR(KVMIO, 0xc8, काष्ठा kvm_xen_hvm_attr)
#घोषणा KVM_XEN_HVM_SET_ATTR	_IOW(KVMIO,  0xc9, काष्ठा kvm_xen_hvm_attr)

काष्ठा kvm_xen_hvm_attr अणु
	__u16 type;
	__u16 pad[3];
	जोड़ अणु
		__u8 दीर्घ_mode;
		__u8 vector;
		काष्ठा अणु
			__u64 gfn;
		पूर्ण shared_info;
		__u64 pad[8];
	पूर्ण u;
पूर्ण;

/* Available with KVM_CAP_XEN_HVM / KVM_XEN_HVM_CONFIG_SHARED_INFO */
#घोषणा KVM_XEN_ATTR_TYPE_LONG_MODE		0x0
#घोषणा KVM_XEN_ATTR_TYPE_SHARED_INFO		0x1
#घोषणा KVM_XEN_ATTR_TYPE_UPCALL_VECTOR		0x2

/* Per-vCPU Xen attributes */
#घोषणा KVM_XEN_VCPU_GET_ATTR	_IOWR(KVMIO, 0xca, काष्ठा kvm_xen_vcpu_attr)
#घोषणा KVM_XEN_VCPU_SET_ATTR	_IOW(KVMIO,  0xcb, काष्ठा kvm_xen_vcpu_attr)

काष्ठा kvm_xen_vcpu_attr अणु
	__u16 type;
	__u16 pad[3];
	जोड़ अणु
		__u64 gpa;
		__u64 pad[8];
		काष्ठा अणु
			__u64 state;
			__u64 state_entry_समय;
			__u64 समय_running;
			__u64 समय_runnable;
			__u64 समय_blocked;
			__u64 समय_offline;
		पूर्ण runstate;
	पूर्ण u;
पूर्ण;

/* Available with KVM_CAP_XEN_HVM / KVM_XEN_HVM_CONFIG_SHARED_INFO */
#घोषणा KVM_XEN_VCPU_ATTR_TYPE_VCPU_INFO	0x0
#घोषणा KVM_XEN_VCPU_ATTR_TYPE_VCPU_TIME_INFO	0x1
#घोषणा KVM_XEN_VCPU_ATTR_TYPE_RUNSTATE_ADDR	0x2
#घोषणा KVM_XEN_VCPU_ATTR_TYPE_RUNSTATE_CURRENT	0x3
#घोषणा KVM_XEN_VCPU_ATTR_TYPE_RUNSTATE_DATA	0x4
#घोषणा KVM_XEN_VCPU_ATTR_TYPE_RUNSTATE_ADJUST	0x5

/* Secure Encrypted Virtualization command */
क्रमागत sev_cmd_id अणु
	/* Guest initialization commands */
	KVM_SEV_INIT = 0,
	KVM_SEV_ES_INIT,
	/* Guest launch commands */
	KVM_SEV_LAUNCH_START,
	KVM_SEV_LAUNCH_UPDATE_DATA,
	KVM_SEV_LAUNCH_UPDATE_VMSA,
	KVM_SEV_LAUNCH_SECRET,
	KVM_SEV_LAUNCH_MEASURE,
	KVM_SEV_LAUNCH_FINISH,
	/* Guest migration commands (outgoing) */
	KVM_SEV_SEND_START,
	KVM_SEV_SEND_UPDATE_DATA,
	KVM_SEV_SEND_UPDATE_VMSA,
	KVM_SEV_SEND_FINISH,
	/* Guest migration commands (incoming) */
	KVM_SEV_RECEIVE_START,
	KVM_SEV_RECEIVE_UPDATE_DATA,
	KVM_SEV_RECEIVE_UPDATE_VMSA,
	KVM_SEV_RECEIVE_FINISH,
	/* Guest status and debug commands */
	KVM_SEV_GUEST_STATUS,
	KVM_SEV_DBG_DECRYPT,
	KVM_SEV_DBG_ENCRYPT,
	/* Guest certअगरicates commands */
	KVM_SEV_CERT_EXPORT,
	/* Attestation report */
	KVM_SEV_GET_ATTESTATION_REPORT,
	/* Guest Migration Extension */
	KVM_SEV_SEND_CANCEL,

	KVM_SEV_NR_MAX,
पूर्ण;

काष्ठा kvm_sev_cmd अणु
	__u32 id;
	__u64 data;
	__u32 error;
	__u32 sev_fd;
पूर्ण;

काष्ठा kvm_sev_launch_start अणु
	__u32 handle;
	__u32 policy;
	__u64 dh_uaddr;
	__u32 dh_len;
	__u64 session_uaddr;
	__u32 session_len;
पूर्ण;

काष्ठा kvm_sev_launch_update_data अणु
	__u64 uaddr;
	__u32 len;
पूर्ण;


काष्ठा kvm_sev_launch_secret अणु
	__u64 hdr_uaddr;
	__u32 hdr_len;
	__u64 guest_uaddr;
	__u32 guest_len;
	__u64 trans_uaddr;
	__u32 trans_len;
पूर्ण;

काष्ठा kvm_sev_launch_measure अणु
	__u64 uaddr;
	__u32 len;
पूर्ण;

काष्ठा kvm_sev_guest_status अणु
	__u32 handle;
	__u32 policy;
	__u32 state;
पूर्ण;

काष्ठा kvm_sev_dbg अणु
	__u64 src_uaddr;
	__u64 dst_uaddr;
	__u32 len;
पूर्ण;

काष्ठा kvm_sev_attestation_report अणु
	__u8 mnonce[16];
	__u64 uaddr;
	__u32 len;
पूर्ण;

काष्ठा kvm_sev_send_start अणु
	__u32 policy;
	__u64 pdh_cert_uaddr;
	__u32 pdh_cert_len;
	__u64 plat_certs_uaddr;
	__u32 plat_certs_len;
	__u64 amd_certs_uaddr;
	__u32 amd_certs_len;
	__u64 session_uaddr;
	__u32 session_len;
पूर्ण;

काष्ठा kvm_sev_send_update_data अणु
	__u64 hdr_uaddr;
	__u32 hdr_len;
	__u64 guest_uaddr;
	__u32 guest_len;
	__u64 trans_uaddr;
	__u32 trans_len;
पूर्ण;

काष्ठा kvm_sev_receive_start अणु
	__u32 handle;
	__u32 policy;
	__u64 pdh_uaddr;
	__u32 pdh_len;
	__u64 session_uaddr;
	__u32 session_len;
पूर्ण;

काष्ठा kvm_sev_receive_update_data अणु
	__u64 hdr_uaddr;
	__u32 hdr_len;
	__u64 guest_uaddr;
	__u32 guest_len;
	__u64 trans_uaddr;
	__u32 trans_len;
पूर्ण;

#घोषणा KVM_DEV_ASSIGN_ENABLE_IOMMU	(1 << 0)
#घोषणा KVM_DEV_ASSIGN_PCI_2_3		(1 << 1)
#घोषणा KVM_DEV_ASSIGN_MASK_INTX	(1 << 2)

काष्ठा kvm_asचिन्हित_pci_dev अणु
	__u32 asचिन्हित_dev_id;
	__u32 busnr;
	__u32 devfn;
	__u32 flags;
	__u32 segnr;
	जोड़ अणु
		__u32 reserved[11];
	पूर्ण;
पूर्ण;

#घोषणा KVM_DEV_IRQ_HOST_INTX    (1 << 0)
#घोषणा KVM_DEV_IRQ_HOST_MSI     (1 << 1)
#घोषणा KVM_DEV_IRQ_HOST_MSIX    (1 << 2)

#घोषणा KVM_DEV_IRQ_GUEST_INTX   (1 << 8)
#घोषणा KVM_DEV_IRQ_GUEST_MSI    (1 << 9)
#घोषणा KVM_DEV_IRQ_GUEST_MSIX   (1 << 10)

#घोषणा KVM_DEV_IRQ_HOST_MASK	 0x00ff
#घोषणा KVM_DEV_IRQ_GUEST_MASK   0xff00

काष्ठा kvm_asचिन्हित_irq अणु
	__u32 asचिन्हित_dev_id;
	__u32 host_irq; /* ignored (legacy field) */
	__u32 guest_irq;
	__u32 flags;
	जोड़ अणु
		__u32 reserved[12];
	पूर्ण;
पूर्ण;

काष्ठा kvm_asचिन्हित_msix_nr अणु
	__u32 asचिन्हित_dev_id;
	__u16 entry_nr;
	__u16 padding;
पूर्ण;

#घोषणा KVM_MAX_MSIX_PER_DEV		256
काष्ठा kvm_asचिन्हित_msix_entry अणु
	__u32 asचिन्हित_dev_id;
	__u32 gsi;
	__u16 entry; /* The index of entry in the MSI-X table */
	__u16 padding[3];
पूर्ण;

#घोषणा KVM_X2APIC_API_USE_32BIT_IDS            (1ULL << 0)
#घोषणा KVM_X2APIC_API_DISABLE_BROADCAST_QUIRK  (1ULL << 1)

/* Available with KVM_CAP_ARM_USER_IRQ */

/* Bits क्रम run->s.regs.device_irq_level */
#घोषणा KVM_ARM_DEV_EL1_VTIMER		(1 << 0)
#घोषणा KVM_ARM_DEV_EL1_PTIMER		(1 << 1)
#घोषणा KVM_ARM_DEV_PMU			(1 << 2)

काष्ठा kvm_hyperv_eventfd अणु
	__u32 conn_id;
	__s32 fd;
	__u32 flags;
	__u32 padding[3];
पूर्ण;

#घोषणा KVM_HYPERV_CONN_ID_MASK		0x00ffffff
#घोषणा KVM_HYPERV_EVENTFD_DEASSIGN	(1 << 0)

#घोषणा KVM_सूचीTY_LOG_MANUAL_PROTECT_ENABLE    (1 << 0)
#घोषणा KVM_सूचीTY_LOG_INITIALLY_SET            (1 << 1)

/*
 * Arch needs to define the macro after implementing the dirty ring
 * feature.  KVM_सूचीTY_LOG_PAGE_OFFSET should be defined as the
 * starting page offset of the dirty ring काष्ठाures.
 */
#अगर_अघोषित KVM_सूचीTY_LOG_PAGE_OFFSET
#घोषणा KVM_सूचीTY_LOG_PAGE_OFFSET 0
#पूर्ण_अगर

/*
 * KVM dirty GFN flags, defined as:
 *
 * |---------------+---------------+--------------|
 * | bit 1 (reset) | bit 0 (dirty) | Status       |
 * |---------------+---------------+--------------|
 * |             0 |             0 | Invalid GFN  |
 * |             0 |             1 | Dirty GFN    |
 * |             1 |             X | GFN to reset |
 * |---------------+---------------+--------------|
 *
 * Lअगरecycle of a dirty GFN goes like:
 *
 *      dirtied         harvested        reset
 * 00 -----------> 01 -------------> 1X -------+
 *  ^                                          |
 *  |                                          |
 *  +------------------------------------------+
 *
 * The userspace program is only responsible क्रम the 01->1X state
 * conversion after harvesting an entry.  Also, it must not skip any
 * dirty bits, so that dirty bits are always harvested in sequence.
 */
#घोषणा KVM_सूचीTY_GFN_F_सूचीTY           _BITUL(0)
#घोषणा KVM_सूचीTY_GFN_F_RESET           _BITUL(1)
#घोषणा KVM_सूचीTY_GFN_F_MASK            0x3

/*
 * KVM dirty rings should be mapped at KVM_सूचीTY_LOG_PAGE_OFFSET of
 * per-vcpu mmaped regions as an array of काष्ठा kvm_dirty_gfn.  The
 * size of the gfn buffer is decided by the first argument when
 * enabling KVM_CAP_सूचीTY_LOG_RING.
 */
काष्ठा kvm_dirty_gfn अणु
	__u32 flags;
	__u32 slot;
	__u64 offset;
पूर्ण;

#घोषणा KVM_BUS_LOCK_DETECTION_OFF             (1 << 0)
#घोषणा KVM_BUS_LOCK_DETECTION_EXIT            (1 << 1)

#पूर्ण_अगर /* __LINUX_KVM_H */
