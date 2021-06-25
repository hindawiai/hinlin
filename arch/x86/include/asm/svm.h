<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SVM_H
#घोषणा __SVM_H

#समावेश <uapi/यंत्र/svm.h>
#समावेश <uapi/यंत्र/kvm.h>

/*
 * 32-bit पूर्णांकercept words in the VMCB Control Area, starting
 * at Byte offset 000h.
 */

क्रमागत पूर्णांकercept_words अणु
	INTERCEPT_CR = 0,
	INTERCEPT_DR,
	INTERCEPT_EXCEPTION,
	INTERCEPT_WORD3,
	INTERCEPT_WORD4,
	INTERCEPT_WORD5,
	MAX_INTERCEPT,
पूर्ण;

क्रमागत अणु
	/* Byte offset 000h (word 0) */
	INTERCEPT_CR0_READ = 0,
	INTERCEPT_CR3_READ = 3,
	INTERCEPT_CR4_READ = 4,
	INTERCEPT_CR8_READ = 8,
	INTERCEPT_CR0_WRITE = 16,
	INTERCEPT_CR3_WRITE = 16 + 3,
	INTERCEPT_CR4_WRITE = 16 + 4,
	INTERCEPT_CR8_WRITE = 16 + 8,
	/* Byte offset 004h (word 1) */
	INTERCEPT_DR0_READ = 32,
	INTERCEPT_DR1_READ,
	INTERCEPT_DR2_READ,
	INTERCEPT_DR3_READ,
	INTERCEPT_DR4_READ,
	INTERCEPT_DR5_READ,
	INTERCEPT_DR6_READ,
	INTERCEPT_DR7_READ,
	INTERCEPT_DR0_WRITE = 48,
	INTERCEPT_DR1_WRITE,
	INTERCEPT_DR2_WRITE,
	INTERCEPT_DR3_WRITE,
	INTERCEPT_DR4_WRITE,
	INTERCEPT_DR5_WRITE,
	INTERCEPT_DR6_WRITE,
	INTERCEPT_DR7_WRITE,
	/* Byte offset 008h (word 2) */
	INTERCEPT_EXCEPTION_OFFSET = 64,
	/* Byte offset 00Ch (word 3) */
	INTERCEPT_INTR = 96,
	INTERCEPT_NMI,
	INTERCEPT_SMI,
	INTERCEPT_INIT,
	INTERCEPT_VINTR,
	INTERCEPT_SELECTIVE_CR0,
	INTERCEPT_STORE_IDTR,
	INTERCEPT_STORE_GDTR,
	INTERCEPT_STORE_LDTR,
	INTERCEPT_STORE_TR,
	INTERCEPT_LOAD_IDTR,
	INTERCEPT_LOAD_GDTR,
	INTERCEPT_LOAD_LDTR,
	INTERCEPT_LOAD_TR,
	INTERCEPT_RDTSC,
	INTERCEPT_RDPMC,
	INTERCEPT_PUSHF,
	INTERCEPT_POPF,
	INTERCEPT_CPUID,
	INTERCEPT_RSM,
	INTERCEPT_IRET,
	INTERCEPT_INTn,
	INTERCEPT_INVD,
	INTERCEPT_PAUSE,
	INTERCEPT_HLT,
	INTERCEPT_INVLPG,
	INTERCEPT_INVLPGA,
	INTERCEPT_IOIO_PROT,
	INTERCEPT_MSR_PROT,
	INTERCEPT_TASK_SWITCH,
	INTERCEPT_FERR_FREEZE,
	INTERCEPT_SHUTDOWN,
	/* Byte offset 010h (word 4) */
	INTERCEPT_VMRUN = 128,
	INTERCEPT_VMMCALL,
	INTERCEPT_VMLOAD,
	INTERCEPT_VMSAVE,
	INTERCEPT_STGI,
	INTERCEPT_CLGI,
	INTERCEPT_SKINIT,
	INTERCEPT_RDTSCP,
	INTERCEPT_ICEBP,
	INTERCEPT_WBINVD,
	INTERCEPT_MONITOR,
	INTERCEPT_MWAIT,
	INTERCEPT_MWAIT_COND,
	INTERCEPT_XSETBV,
	INTERCEPT_RDPRU,
	TRAP_EFER_WRITE,
	TRAP_CR0_WRITE,
	TRAP_CR1_WRITE,
	TRAP_CR2_WRITE,
	TRAP_CR3_WRITE,
	TRAP_CR4_WRITE,
	TRAP_CR5_WRITE,
	TRAP_CR6_WRITE,
	TRAP_CR7_WRITE,
	TRAP_CR8_WRITE,
	/* Byte offset 014h (word 5) */
	INTERCEPT_INVLPGB = 160,
	INTERCEPT_INVLPGB_ILLEGAL,
	INTERCEPT_INVPCID,
	INTERCEPT_MCOMMIT,
	INTERCEPT_TLBSYNC,
पूर्ण;


काष्ठा __attribute__ ((__packed__)) vmcb_control_area अणु
	u32 पूर्णांकercepts[MAX_INTERCEPT];
	u32 reserved_1[15 - MAX_INTERCEPT];
	u16 छोड़ो_filter_thresh;
	u16 छोड़ो_filter_count;
	u64 iopm_base_pa;
	u64 msrpm_base_pa;
	u64 tsc_offset;
	u32 asid;
	u8 tlb_ctl;
	u8 reserved_2[3];
	u32 पूर्णांक_ctl;
	u32 पूर्णांक_vector;
	u32 पूर्णांक_state;
	u8 reserved_3[4];
	u32 निकास_code;
	u32 निकास_code_hi;
	u64 निकास_info_1;
	u64 निकास_info_2;
	u32 निकास_पूर्णांक_info;
	u32 निकास_पूर्णांक_info_err;
	u64 nested_ctl;
	u64 avic_vapic_bar;
	u64 ghcb_gpa;
	u32 event_inj;
	u32 event_inj_err;
	u64 nested_cr3;
	u64 virt_ext;
	u32 clean;
	u32 reserved_5;
	u64 next_rip;
	u8 insn_len;
	u8 insn_bytes[15];
	u64 avic_backing_page;	/* Offset 0xe0 */
	u8 reserved_6[8];	/* Offset 0xe8 */
	u64 avic_logical_id;	/* Offset 0xf0 */
	u64 avic_physical_id;	/* Offset 0xf8 */
	u8 reserved_7[8];
	u64 vmsa_pa;		/* Used क्रम an SEV-ES guest */
पूर्ण;


#घोषणा TLB_CONTROL_DO_NOTHING 0
#घोषणा TLB_CONTROL_FLUSH_ALL_ASID 1
#घोषणा TLB_CONTROL_FLUSH_ASID 3
#घोषणा TLB_CONTROL_FLUSH_ASID_LOCAL 7

#घोषणा V_TPR_MASK 0x0f

#घोषणा V_IRQ_SHIFT 8
#घोषणा V_IRQ_MASK (1 << V_IRQ_SHIFT)

#घोषणा V_GIF_SHIFT 9
#घोषणा V_GIF_MASK (1 << V_GIF_SHIFT)

#घोषणा V_INTR_PRIO_SHIFT 16
#घोषणा V_INTR_PRIO_MASK (0x0f << V_INTR_PRIO_SHIFT)

#घोषणा V_IGN_TPR_SHIFT 20
#घोषणा V_IGN_TPR_MASK (1 << V_IGN_TPR_SHIFT)

#घोषणा V_INTR_MASKING_SHIFT 24
#घोषणा V_INTR_MASKING_MASK (1 << V_INTR_MASKING_SHIFT)

#घोषणा V_GIF_ENABLE_SHIFT 25
#घोषणा V_GIF_ENABLE_MASK (1 << V_GIF_ENABLE_SHIFT)

#घोषणा AVIC_ENABLE_SHIFT 31
#घोषणा AVIC_ENABLE_MASK (1 << AVIC_ENABLE_SHIFT)

#घोषणा LBR_CTL_ENABLE_MASK BIT_ULL(0)
#घोषणा VIRTUAL_VMLOAD_VMSAVE_ENABLE_MASK BIT_ULL(1)

#घोषणा SVM_INTERRUPT_SHADOW_MASK	BIT_ULL(0)
#घोषणा SVM_GUEST_INTERRUPT_MASK	BIT_ULL(1)

#घोषणा SVM_IOIO_STR_SHIFT 2
#घोषणा SVM_IOIO_REP_SHIFT 3
#घोषणा SVM_IOIO_SIZE_SHIFT 4
#घोषणा SVM_IOIO_ASIZE_SHIFT 7

#घोषणा SVM_IOIO_TYPE_MASK 1
#घोषणा SVM_IOIO_STR_MASK (1 << SVM_IOIO_STR_SHIFT)
#घोषणा SVM_IOIO_REP_MASK (1 << SVM_IOIO_REP_SHIFT)
#घोषणा SVM_IOIO_SIZE_MASK (7 << SVM_IOIO_SIZE_SHIFT)
#घोषणा SVM_IOIO_ASIZE_MASK (7 << SVM_IOIO_ASIZE_SHIFT)

#घोषणा SVM_VM_CR_VALID_MASK	0x001fULL
#घोषणा SVM_VM_CR_SVM_LOCK_MASK 0x0008ULL
#घोषणा SVM_VM_CR_SVM_DIS_MASK  0x0010ULL

#घोषणा SVM_NESTED_CTL_NP_ENABLE	BIT(0)
#घोषणा SVM_NESTED_CTL_SEV_ENABLE	BIT(1)
#घोषणा SVM_NESTED_CTL_SEV_ES_ENABLE	BIT(2)

काष्ठा vmcb_seg अणु
	u16 selector;
	u16 attrib;
	u32 limit;
	u64 base;
पूर्ण __packed;

काष्ठा vmcb_save_area अणु
	काष्ठा vmcb_seg es;
	काष्ठा vmcb_seg cs;
	काष्ठा vmcb_seg ss;
	काष्ठा vmcb_seg ds;
	काष्ठा vmcb_seg fs;
	काष्ठा vmcb_seg gs;
	काष्ठा vmcb_seg gdtr;
	काष्ठा vmcb_seg ldtr;
	काष्ठा vmcb_seg idtr;
	काष्ठा vmcb_seg tr;
	u8 reserved_1[43];
	u8 cpl;
	u8 reserved_2[4];
	u64 efer;
	u8 reserved_3[104];
	u64 xss;		/* Valid क्रम SEV-ES only */
	u64 cr4;
	u64 cr3;
	u64 cr0;
	u64 dr7;
	u64 dr6;
	u64 rflags;
	u64 rip;
	u8 reserved_4[88];
	u64 rsp;
	u8 reserved_5[24];
	u64 rax;
	u64 star;
	u64 lstar;
	u64 cstar;
	u64 sfmask;
	u64 kernel_gs_base;
	u64 sysenter_cs;
	u64 sysenter_esp;
	u64 sysenter_eip;
	u64 cr2;
	u8 reserved_6[32];
	u64 g_pat;
	u64 dbgctl;
	u64 br_from;
	u64 br_to;
	u64 last_excp_from;
	u64 last_excp_to;

	/*
	 * The following part of the save area is valid only क्रम
	 * SEV-ES guests when referenced through the GHCB or क्रम
	 * saving to the host save area.
	 */
	u8 reserved_7[72];
	u32 spec_ctrl;		/* Guest version of SPEC_CTRL at 0x2E0 */
	u8 reserved_7b[4];
	u32 pkru;
	u8 reserved_7a[20];
	u64 reserved_8;		/* rax alपढ़ोy available at 0x01f8 */
	u64 rcx;
	u64 rdx;
	u64 rbx;
	u64 reserved_9;		/* rsp alपढ़ोy available at 0x01d8 */
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
	u8 reserved_10[16];
	u64 sw_निकास_code;
	u64 sw_निकास_info_1;
	u64 sw_निकास_info_2;
	u64 sw_scratch;
	u8 reserved_11[56];
	u64 xcr0;
	u8 valid_biपंचांगap[16];
	u64 x87_state_gpa;
पूर्ण __packed;

काष्ठा ghcb अणु
	काष्ठा vmcb_save_area save;
	u8 reserved_save[2048 - माप(काष्ठा vmcb_save_area)];

	u8 shared_buffer[2032];

	u8 reserved_1[10];
	u16 protocol_version;	/* negotiated SEV-ES/GHCB protocol version */
	u32 ghcb_usage;
पूर्ण __packed;


#घोषणा EXPECTED_VMCB_SAVE_AREA_SIZE		1032
#घोषणा EXPECTED_VMCB_CONTROL_AREA_SIZE		272
#घोषणा EXPECTED_GHCB_SIZE			PAGE_SIZE

अटल अंतरभूत व्योम __unused_size_checks(व्योम)
अणु
	BUILD_BUG_ON(माप(काष्ठा vmcb_save_area)	!= EXPECTED_VMCB_SAVE_AREA_SIZE);
	BUILD_BUG_ON(माप(काष्ठा vmcb_control_area)	!= EXPECTED_VMCB_CONTROL_AREA_SIZE);
	BUILD_BUG_ON(माप(काष्ठा ghcb)		!= EXPECTED_GHCB_SIZE);
पूर्ण

काष्ठा vmcb अणु
	काष्ठा vmcb_control_area control;
	u8 reserved_control[1024 - माप(काष्ठा vmcb_control_area)];
	काष्ठा vmcb_save_area save;
पूर्ण __packed;

#घोषणा SVM_CPUID_FUNC 0x8000000a

#घोषणा SVM_VM_CR_SVM_DISABLE 4

#घोषणा SVM_SELECTOR_S_SHIFT 4
#घोषणा SVM_SELECTOR_DPL_SHIFT 5
#घोषणा SVM_SELECTOR_P_SHIFT 7
#घोषणा SVM_SELECTOR_AVL_SHIFT 8
#घोषणा SVM_SELECTOR_L_SHIFT 9
#घोषणा SVM_SELECTOR_DB_SHIFT 10
#घोषणा SVM_SELECTOR_G_SHIFT 11

#घोषणा SVM_SELECTOR_TYPE_MASK (0xf)
#घोषणा SVM_SELECTOR_S_MASK (1 << SVM_SELECTOR_S_SHIFT)
#घोषणा SVM_SELECTOR_DPL_MASK (3 << SVM_SELECTOR_DPL_SHIFT)
#घोषणा SVM_SELECTOR_P_MASK (1 << SVM_SELECTOR_P_SHIFT)
#घोषणा SVM_SELECTOR_AVL_MASK (1 << SVM_SELECTOR_AVL_SHIFT)
#घोषणा SVM_SELECTOR_L_MASK (1 << SVM_SELECTOR_L_SHIFT)
#घोषणा SVM_SELECTOR_DB_MASK (1 << SVM_SELECTOR_DB_SHIFT)
#घोषणा SVM_SELECTOR_G_MASK (1 << SVM_SELECTOR_G_SHIFT)

#घोषणा SVM_SELECTOR_WRITE_MASK (1 << 1)
#घोषणा SVM_SELECTOR_READ_MASK SVM_SELECTOR_WRITE_MASK
#घोषणा SVM_SELECTOR_CODE_MASK (1 << 3)

#घोषणा SVM_EVTINJ_VEC_MASK 0xff

#घोषणा SVM_EVTINJ_TYPE_SHIFT 8
#घोषणा SVM_EVTINJ_TYPE_MASK (7 << SVM_EVTINJ_TYPE_SHIFT)

#घोषणा SVM_EVTINJ_TYPE_INTR (0 << SVM_EVTINJ_TYPE_SHIFT)
#घोषणा SVM_EVTINJ_TYPE_NMI (2 << SVM_EVTINJ_TYPE_SHIFT)
#घोषणा SVM_EVTINJ_TYPE_EXEPT (3 << SVM_EVTINJ_TYPE_SHIFT)
#घोषणा SVM_EVTINJ_TYPE_SOFT (4 << SVM_EVTINJ_TYPE_SHIFT)

#घोषणा SVM_EVTINJ_VALID (1 << 31)
#घोषणा SVM_EVTINJ_VALID_ERR (1 << 11)

#घोषणा SVM_EXITINTINFO_VEC_MASK SVM_EVTINJ_VEC_MASK
#घोषणा SVM_EXITINTINFO_TYPE_MASK SVM_EVTINJ_TYPE_MASK

#घोषणा	SVM_EXITINTINFO_TYPE_INTR SVM_EVTINJ_TYPE_INTR
#घोषणा	SVM_EXITINTINFO_TYPE_NMI SVM_EVTINJ_TYPE_NMI
#घोषणा	SVM_EXITINTINFO_TYPE_EXEPT SVM_EVTINJ_TYPE_EXEPT
#घोषणा	SVM_EXITINTINFO_TYPE_SOFT SVM_EVTINJ_TYPE_SOFT

#घोषणा SVM_EXITINTINFO_VALID SVM_EVTINJ_VALID
#घोषणा SVM_EXITINTINFO_VALID_ERR SVM_EVTINJ_VALID_ERR

#घोषणा SVM_EXITINFOSHIFT_TS_REASON_IRET 36
#घोषणा SVM_EXITINFOSHIFT_TS_REASON_JMP 38
#घोषणा SVM_EXITINFOSHIFT_TS_HAS_ERROR_CODE 44

#घोषणा SVM_EXITINFO_REG_MASK 0x0F

#घोषणा SVM_CR0_SELECTIVE_MASK (X86_CR0_TS | X86_CR0_MP)

/* GHCB Accessor functions */

#घोषणा GHCB_BITMAP_IDX(field)							\
	(दुरत्व(काष्ठा vmcb_save_area, field) / माप(u64))

#घोषणा DEFINE_GHCB_ACCESSORS(field)						\
	अटल अंतरभूत bool ghcb_##field##_is_valid(स्थिर काष्ठा ghcb *ghcb)	\
	अणु									\
		वापस test_bit(GHCB_BITMAP_IDX(field),				\
				(अचिन्हित दीर्घ *)&ghcb->save.valid_biपंचांगap);	\
	पूर्ण									\
										\
	अटल अंतरभूत u64 ghcb_get_##field(काष्ठा ghcb *ghcb)			\
	अणु									\
		वापस ghcb->save.field;					\
	पूर्ण									\
										\
	अटल अंतरभूत u64 ghcb_get_##field##_अगर_valid(काष्ठा ghcb *ghcb)	\
	अणु									\
		वापस ghcb_##field##_is_valid(ghcb) ? ghcb->save.field : 0;	\
	पूर्ण									\
										\
	अटल अंतरभूत व्योम ghcb_set_##field(काष्ठा ghcb *ghcb, u64 value)	\
	अणु									\
		__set_bit(GHCB_BITMAP_IDX(field),				\
			  (अचिन्हित दीर्घ *)&ghcb->save.valid_biपंचांगap);		\
		ghcb->save.field = value;					\
	पूर्ण

DEFINE_GHCB_ACCESSORS(cpl)
DEFINE_GHCB_ACCESSORS(rip)
DEFINE_GHCB_ACCESSORS(rsp)
DEFINE_GHCB_ACCESSORS(rax)
DEFINE_GHCB_ACCESSORS(rcx)
DEFINE_GHCB_ACCESSORS(rdx)
DEFINE_GHCB_ACCESSORS(rbx)
DEFINE_GHCB_ACCESSORS(rbp)
DEFINE_GHCB_ACCESSORS(rsi)
DEFINE_GHCB_ACCESSORS(rdi)
DEFINE_GHCB_ACCESSORS(r8)
DEFINE_GHCB_ACCESSORS(r9)
DEFINE_GHCB_ACCESSORS(r10)
DEFINE_GHCB_ACCESSORS(r11)
DEFINE_GHCB_ACCESSORS(r12)
DEFINE_GHCB_ACCESSORS(r13)
DEFINE_GHCB_ACCESSORS(r14)
DEFINE_GHCB_ACCESSORS(r15)
DEFINE_GHCB_ACCESSORS(sw_निकास_code)
DEFINE_GHCB_ACCESSORS(sw_निकास_info_1)
DEFINE_GHCB_ACCESSORS(sw_निकास_info_2)
DEFINE_GHCB_ACCESSORS(sw_scratch)
DEFINE_GHCB_ACCESSORS(xcr0)

#पूर्ण_अगर
