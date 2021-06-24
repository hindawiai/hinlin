<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * Copyright SUSE Linux Products GmbH 2009
 *
 * Authors: Alexander Graf <agraf@suse.de>
 */

#अगर_अघोषित __ASM_KVM_BOOK3S_ASM_H__
#घोषणा __ASM_KVM_BOOK3S_ASM_H__

/* XICS ICP रेजिस्टर offsets */
#घोषणा XICS_XIRR		4
#घोषणा XICS_MFRR		0xc
#घोषणा XICS_IPI		2	/* पूर्णांकerrupt source # क्रम IPIs */

/* LPIDs we support with this build -- runसमय limit may be lower */
#घोषणा KVMPPC_NR_LPIDS			(LPID_RSVD + 1)

/* Maximum number of thपढ़ोs per physical core */
#घोषणा MAX_SMT_THREADS		8

/* Maximum number of subcores per physical core */
#घोषणा MAX_SUBCORES		4

#अगर_घोषित __ASSEMBLY__

#अगर_घोषित CONFIG_KVM_BOOK3S_HANDLER

#समावेश <यंत्र/kvm_यंत्र.h>

.macro DO_KVM पूर्णांकno
	.अगर (\पूर्णांकno == BOOK3S_INTERRUPT_SYSTEM_RESET) || \
	    (\पूर्णांकno == BOOK3S_INTERRUPT_MACHINE_CHECK) || \
	    (\पूर्णांकno == BOOK3S_INTERRUPT_DATA_STORAGE) || \
	    (\पूर्णांकno == BOOK3S_INTERRUPT_INST_STORAGE) || \
	    (\पूर्णांकno == BOOK3S_INTERRUPT_DATA_SEGMENT) || \
	    (\पूर्णांकno == BOOK3S_INTERRUPT_INST_SEGMENT) || \
	    (\पूर्णांकno == BOOK3S_INTERRUPT_EXTERNAL) || \
	    (\पूर्णांकno == BOOK3S_INTERRUPT_EXTERNAL_HV) || \
	    (\पूर्णांकno == BOOK3S_INTERRUPT_ALIGNMENT) || \
	    (\पूर्णांकno == BOOK3S_INTERRUPT_PROGRAM) || \
	    (\पूर्णांकno == BOOK3S_INTERRUPT_FP_UNAVAIL) || \
	    (\पूर्णांकno == BOOK3S_INTERRUPT_DECREMENTER) || \
	    (\पूर्णांकno == BOOK3S_INTERRUPT_SYSCALL) || \
	    (\पूर्णांकno == BOOK3S_INTERRUPT_TRACE) || \
	    (\पूर्णांकno == BOOK3S_INTERRUPT_PERFMON) || \
	    (\पूर्णांकno == BOOK3S_INTERRUPT_ALTIVEC) || \
	    (\पूर्णांकno == BOOK3S_INTERRUPT_VSX)

	b	kvmppc_trampoline_\पूर्णांकno
kvmppc_resume_\पूर्णांकno:

	.endअगर
.endm

#अन्यथा

.macro DO_KVM पूर्णांकno
.endm

#पूर्ण_अगर /* CONFIG_KVM_BOOK3S_HANDLER */

#अन्यथा  /*__ASSEMBLY__ */

काष्ठा kvmppc_vcore;

/* Struct used क्रम coordinating micro-thपढ़ोing (split-core) mode changes */
काष्ठा kvm_split_mode अणु
	अचिन्हित दीर्घ	rpr;
	अचिन्हित दीर्घ	pmmar;
	अचिन्हित दीर्घ	ldbar;
	u8		subcore_size;
	u8		करो_nap;
	u8		napped[MAX_SMT_THREADS];
	काष्ठा kvmppc_vcore *vc[MAX_SUBCORES];
पूर्ण;

/*
 * This काष्ठा goes in the PACA on 64-bit processors.  It is used
 * to store host state that needs to be saved when we enter a guest
 * and restored when we निकास, but isn't specअगरic to any particular
 * guest or vcpu.  It also has some scratch fields used by the guest
 * निकास code.
 */
काष्ठा kvmppc_host_state अणु
	uदीर्घ host_r1;
	uदीर्घ host_r2;
	uदीर्घ host_msr;
	uदीर्घ vmhandler;
	uदीर्घ scratch0;
	uदीर्घ scratch1;
	uदीर्घ scratch2;
	u8 in_guest;
	u8 restore_hid5;
	u8 napping;

#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
	u8 hwthपढ़ो_req;
	u8 hwthपढ़ो_state;
	u8 host_ipi;
	u8 ptid;		/* thपढ़ो number within subcore when split */
	u8 fake_suspend;
	काष्ठा kvm_vcpu *kvm_vcpu;
	काष्ठा kvmppc_vcore *kvm_vcore;
	व्योम __iomem *xics_phys;
	व्योम __iomem *xive_tima_phys;
	व्योम __iomem *xive_tima_virt;
	u32 saved_xirr;
	u64 dabr;
	u64 host_mmcr[10];	/* MMCR 0,1,A, SIAR, SDAR, MMCR2, SIER, MMCR3, SIER2/3 */
	u32 host_pmc[8];
	u64 host_purr;
	u64 host_spurr;
	u64 host_dscr;
	u64 dec_expires;
	काष्ठा kvm_split_mode *kvm_split_mode;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	u64 cfar;
	u64 ppr;
	u64 host_fscr;
#पूर्ण_अगर
पूर्ण;

काष्ठा kvmppc_book3s_shaकरोw_vcpu अणु
	bool in_use;
	uदीर्घ gpr[14];
	u32 cr;
	uदीर्घ xer;
	uदीर्घ ctr;
	uदीर्घ lr;
	uदीर्घ pc;

	uदीर्घ shaकरोw_srr1;
	uदीर्घ fault_dar;
	u32 fault_dsisr;
	u32 last_inst;

#अगर_घोषित CONFIG_PPC_BOOK3S_32
	u32     sr[16];			/* Guest SRs */

	काष्ठा kvmppc_host_state hstate;
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_BOOK3S_64
	u8 slb_max;			/* highest used guest slb entry */
	काष्ठा  अणु
		u64     esid;
		u64     vsid;
	पूर्ण slb[64];			/* guest SLB */
	u64 shaकरोw_fscr;
#पूर्ण_अगर
पूर्ण;

#पूर्ण_अगर /*__ASSEMBLY__ */

/* Values क्रम kvm_state */
#घोषणा KVM_HWTHREAD_IN_KERNEL	0
#घोषणा KVM_HWTHREAD_IN_IDLE	1
#घोषणा KVM_HWTHREAD_IN_KVM	2

#पूर्ण_अगर /* __ASM_KVM_BOOK3S_ASM_H__ */
