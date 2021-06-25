<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * tools/testing/selftests/kvm/include/x86_64/svm.h
 * This is a copy of arch/x86/include/यंत्र/svm.h
 *
 */

#अगर_अघोषित SELFTEST_KVM_SVM_H
#घोषणा SELFTEST_KVM_SVM_H

क्रमागत अणु
	INTERCEPT_INTR,
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
	INTERCEPT_VMRUN,
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
पूर्ण;


काष्ठा __attribute__ ((__packed__)) vmcb_control_area अणु
	u32 पूर्णांकercept_cr;
	u32 पूर्णांकercept_dr;
	u32 पूर्णांकercept_exceptions;
	u64 पूर्णांकercept;
	u8 reserved_1[40];
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
	u8 reserved_4[8];
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
	u8 reserved_7[768];
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

#घोषणा SVM_INTERRUPT_SHADOW_MASK 1

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

काष्ठा __attribute__ ((__packed__)) vmcb_seg अणु
	u16 selector;
	u16 attrib;
	u32 limit;
	u64 base;
पूर्ण;

काष्ठा __attribute__ ((__packed__)) vmcb_save_area अणु
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
	u8 reserved_3[112];
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
पूर्ण;

काष्ठा __attribute__ ((__packed__)) vmcb अणु
	काष्ठा vmcb_control_area control;
	काष्ठा vmcb_save_area save;
पूर्ण;

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

#घोषणा INTERCEPT_CR0_READ	0
#घोषणा INTERCEPT_CR3_READ	3
#घोषणा INTERCEPT_CR4_READ	4
#घोषणा INTERCEPT_CR8_READ	8
#घोषणा INTERCEPT_CR0_WRITE	(16 + 0)
#घोषणा INTERCEPT_CR3_WRITE	(16 + 3)
#घोषणा INTERCEPT_CR4_WRITE	(16 + 4)
#घोषणा INTERCEPT_CR8_WRITE	(16 + 8)

#घोषणा INTERCEPT_DR0_READ	0
#घोषणा INTERCEPT_DR1_READ	1
#घोषणा INTERCEPT_DR2_READ	2
#घोषणा INTERCEPT_DR3_READ	3
#घोषणा INTERCEPT_DR4_READ	4
#घोषणा INTERCEPT_DR5_READ	5
#घोषणा INTERCEPT_DR6_READ	6
#घोषणा INTERCEPT_DR7_READ	7
#घोषणा INTERCEPT_DR0_WRITE	(16 + 0)
#घोषणा INTERCEPT_DR1_WRITE	(16 + 1)
#घोषणा INTERCEPT_DR2_WRITE	(16 + 2)
#घोषणा INTERCEPT_DR3_WRITE	(16 + 3)
#घोषणा INTERCEPT_DR4_WRITE	(16 + 4)
#घोषणा INTERCEPT_DR5_WRITE	(16 + 5)
#घोषणा INTERCEPT_DR6_WRITE	(16 + 6)
#घोषणा INTERCEPT_DR7_WRITE	(16 + 7)

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

#पूर्ण_अगर /* SELFTEST_KVM_SVM_H */
