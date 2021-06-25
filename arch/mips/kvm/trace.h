<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2012  MIPS Technologies, Inc.  All rights reserved.
 * Authors: Sanjay Lal <sanjayl@kymasys.com>
 */

#अगर !defined(_TRACE_KVM_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_KVM_H

#समावेश <linux/tracepoपूर्णांक.h>

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM kvm
#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता trace

/*
 * arch/mips/kvm/mips.c
 */
बाह्य bool kvm_trace_guest_mode_change;
पूर्णांक kvm_guest_mode_change_trace_reg(व्योम);
व्योम kvm_guest_mode_change_trace_unreg(व्योम);

/*
 * Tracepoपूर्णांकs क्रम VM enters
 */
DECLARE_EVENT_CLASS(kvm_transition,
	TP_PROTO(काष्ठा kvm_vcpu *vcpu),
	TP_ARGS(vcpu),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, pc)
	),

	TP_fast_assign(
		__entry->pc = vcpu->arch.pc;
	),

	TP_prपूर्णांकk("PC: 0x%08lx",
		  __entry->pc)
);

DEFINE_EVENT(kvm_transition, kvm_enter,
	     TP_PROTO(काष्ठा kvm_vcpu *vcpu),
	     TP_ARGS(vcpu));

DEFINE_EVENT(kvm_transition, kvm_reenter,
	     TP_PROTO(काष्ठा kvm_vcpu *vcpu),
	     TP_ARGS(vcpu));

DEFINE_EVENT(kvm_transition, kvm_out,
	     TP_PROTO(काष्ठा kvm_vcpu *vcpu),
	     TP_ARGS(vcpu));

/* The first 32 निकास reasons correspond to Cause.ExcCode */
#घोषणा KVM_TRACE_EXIT_INT		 0
#घोषणा KVM_TRACE_EXIT_TLBMOD		 1
#घोषणा KVM_TRACE_EXIT_TLBMISS_LD	 2
#घोषणा KVM_TRACE_EXIT_TLBMISS_ST	 3
#घोषणा KVM_TRACE_EXIT_ADDRERR_LD	 4
#घोषणा KVM_TRACE_EXIT_ADDRERR_ST	 5
#घोषणा KVM_TRACE_EXIT_SYSCALL		 8
#घोषणा KVM_TRACE_EXIT_BREAK_INST	 9
#घोषणा KVM_TRACE_EXIT_RESVD_INST	10
#घोषणा KVM_TRACE_EXIT_COP_UNUSABLE	11
#घोषणा KVM_TRACE_EXIT_TRAP_INST	13
#घोषणा KVM_TRACE_EXIT_MSA_FPE		14
#घोषणा KVM_TRACE_EXIT_FPE		15
#घोषणा KVM_TRACE_EXIT_MSA_DISABLED	21
#घोषणा KVM_TRACE_EXIT_GUEST_EXIT	27
/* Further निकास reasons */
#घोषणा KVM_TRACE_EXIT_WAIT		32
#घोषणा KVM_TRACE_EXIT_CACHE		33
#घोषणा KVM_TRACE_EXIT_SIGNAL		34
/* 32 निकास reasons correspond to GuestCtl0.GExcCode (VZ) */
#घोषणा KVM_TRACE_EXIT_GEXCCODE_BASE	64
#घोषणा KVM_TRACE_EXIT_GPSI		64	/*  0 */
#घोषणा KVM_TRACE_EXIT_GSFC		65	/*  1 */
#घोषणा KVM_TRACE_EXIT_HC		66	/*  2 */
#घोषणा KVM_TRACE_EXIT_GRR		67	/*  3 */
#घोषणा KVM_TRACE_EXIT_GVA		72	/*  8 */
#घोषणा KVM_TRACE_EXIT_GHFC		73	/*  9 */
#घोषणा KVM_TRACE_EXIT_GPA		74	/* 10 */

/* Tracepoपूर्णांकs क्रम VM निकासs */
#घोषणा kvm_trace_symbol_निकास_types				\
	अणु KVM_TRACE_EXIT_INT,		"Interrupt" पूर्ण,		\
	अणु KVM_TRACE_EXIT_TLBMOD,	"TLB Mod" पूर्ण,		\
	अणु KVM_TRACE_EXIT_TLBMISS_LD,	"TLB Miss (LD)" पूर्ण,	\
	अणु KVM_TRACE_EXIT_TLBMISS_ST,	"TLB Miss (ST)" पूर्ण,	\
	अणु KVM_TRACE_EXIT_ADDRERR_LD,	"Address Error (LD)" पूर्ण,	\
	अणु KVM_TRACE_EXIT_ADDRERR_ST,	"Address Err (ST)" पूर्ण,	\
	अणु KVM_TRACE_EXIT_SYSCALL,	"System Call" पूर्ण,	\
	अणु KVM_TRACE_EXIT_BREAK_INST,	"Break Inst" पूर्ण,		\
	अणु KVM_TRACE_EXIT_RESVD_INST,	"Reserved Inst" पूर्ण,	\
	अणु KVM_TRACE_EXIT_COP_UNUSABLE,	"COP0/1 Unusable" पूर्ण,	\
	अणु KVM_TRACE_EXIT_TRAP_INST,	"Trap Inst" पूर्ण,		\
	अणु KVM_TRACE_EXIT_MSA_FPE,	"MSA FPE" पूर्ण,		\
	अणु KVM_TRACE_EXIT_FPE,		"FPE" पूर्ण,		\
	अणु KVM_TRACE_EXIT_MSA_DISABLED,	"MSA Disabled" पूर्ण,	\
	अणु KVM_TRACE_EXIT_GUEST_EXIT,	"Guest Exit" पूर्ण,		\
	अणु KVM_TRACE_EXIT_WAIT,		"WAIT" पूर्ण,		\
	अणु KVM_TRACE_EXIT_CACHE,		"CACHE" पूर्ण,		\
	अणु KVM_TRACE_EXIT_SIGNAL,	"Signal" पूर्ण,		\
	अणु KVM_TRACE_EXIT_GPSI,		"GPSI" पूर्ण,		\
	अणु KVM_TRACE_EXIT_GSFC,		"GSFC" पूर्ण,		\
	अणु KVM_TRACE_EXIT_HC,		"HC" पूर्ण,			\
	अणु KVM_TRACE_EXIT_GRR,		"GRR" पूर्ण,		\
	अणु KVM_TRACE_EXIT_GVA,		"GVA" पूर्ण,		\
	अणु KVM_TRACE_EXIT_GHFC,		"GHFC" पूर्ण,		\
	अणु KVM_TRACE_EXIT_GPA,		"GPA" पूर्ण

TRACE_EVENT(kvm_निकास,
	    TP_PROTO(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक reason),
	    TP_ARGS(vcpu, reason),
	    TP_STRUCT__entry(
			__field(अचिन्हित दीर्घ, pc)
			__field(अचिन्हित पूर्णांक, reason)
	    ),

	    TP_fast_assign(
			__entry->pc = vcpu->arch.pc;
			__entry->reason = reason;
	    ),

	    TP_prपूर्णांकk("[%s]PC: 0x%08lx",
		      __prपूर्णांक_symbolic(__entry->reason,
				       kvm_trace_symbol_निकास_types),
		      __entry->pc)
);

#घोषणा KVM_TRACE_MFC0		0
#घोषणा KVM_TRACE_MTC0		1
#घोषणा KVM_TRACE_DMFC0		2
#घोषणा KVM_TRACE_DMTC0		3
#घोषणा KVM_TRACE_RDHWR		4

#घोषणा KVM_TRACE_HWR_COP0	0
#घोषणा KVM_TRACE_HWR_HWR	1

#घोषणा KVM_TRACE_COP0(REG, SEL)	((KVM_TRACE_HWR_COP0 << 8) |	\
					 ((REG) << 3) | (SEL))
#घोषणा KVM_TRACE_HWR(REG, SEL)		((KVM_TRACE_HWR_HWR  << 8) |	\
					 ((REG) << 3) | (SEL))

#घोषणा kvm_trace_symbol_hwr_ops				\
	अणु KVM_TRACE_MFC0,		"MFC0" पूर्ण,		\
	अणु KVM_TRACE_MTC0,		"MTC0" पूर्ण,		\
	अणु KVM_TRACE_DMFC0,		"DMFC0" पूर्ण,		\
	अणु KVM_TRACE_DMTC0,		"DMTC0" पूर्ण,		\
	अणु KVM_TRACE_RDHWR,		"RDHWR" पूर्ण

#घोषणा kvm_trace_symbol_hwr_cop				\
	अणु KVM_TRACE_HWR_COP0,		"COP0" पूर्ण,		\
	अणु KVM_TRACE_HWR_HWR,		"HWR" पूर्ण

#घोषणा kvm_trace_symbol_hwr_regs				\
	अणु KVM_TRACE_COP0( 0, 0),	"Index" पूर्ण,		\
	अणु KVM_TRACE_COP0( 2, 0),	"EntryLo0" पूर्ण,		\
	अणु KVM_TRACE_COP0( 3, 0),	"EntryLo1" पूर्ण,		\
	अणु KVM_TRACE_COP0( 4, 0),	"Context" पूर्ण,		\
	अणु KVM_TRACE_COP0( 4, 2),	"UserLocal" पूर्ण,		\
	अणु KVM_TRACE_COP0( 5, 0),	"PageMask" पूर्ण,		\
	अणु KVM_TRACE_COP0( 6, 0),	"Wired" पूर्ण,		\
	अणु KVM_TRACE_COP0( 7, 0),	"HWREna" पूर्ण,		\
	अणु KVM_TRACE_COP0( 8, 0),	"BadVAddr" पूर्ण,		\
	अणु KVM_TRACE_COP0( 9, 0),	"Count" पूर्ण,		\
	अणु KVM_TRACE_COP0(10, 0),	"EntryHi" पूर्ण,		\
	अणु KVM_TRACE_COP0(11, 0),	"Compare" पूर्ण,		\
	अणु KVM_TRACE_COP0(12, 0),	"Status" पूर्ण,		\
	अणु KVM_TRACE_COP0(12, 1),	"IntCtl" पूर्ण,		\
	अणु KVM_TRACE_COP0(12, 2),	"SRSCtl" पूर्ण,		\
	अणु KVM_TRACE_COP0(13, 0),	"Cause" पूर्ण,		\
	अणु KVM_TRACE_COP0(14, 0),	"EPC" पूर्ण,		\
	अणु KVM_TRACE_COP0(15, 0),	"PRId" पूर्ण,		\
	अणु KVM_TRACE_COP0(15, 1),	"EBase" पूर्ण,		\
	अणु KVM_TRACE_COP0(16, 0),	"Config" पूर्ण,		\
	अणु KVM_TRACE_COP0(16, 1),	"Config1" पूर्ण,		\
	अणु KVM_TRACE_COP0(16, 2),	"Config2" पूर्ण,		\
	अणु KVM_TRACE_COP0(16, 3),	"Config3" पूर्ण,		\
	अणु KVM_TRACE_COP0(16, 4),	"Config4" पूर्ण,		\
	अणु KVM_TRACE_COP0(16, 5),	"Config5" पूर्ण,		\
	अणु KVM_TRACE_COP0(16, 7),	"Config7" पूर्ण,		\
	अणु KVM_TRACE_COP0(17, 1),	"MAAR" पूर्ण,		\
	अणु KVM_TRACE_COP0(17, 2),	"MAARI" पूर्ण,		\
	अणु KVM_TRACE_COP0(26, 0),	"ECC" पूर्ण,		\
	अणु KVM_TRACE_COP0(30, 0),	"ErrorEPC" पूर्ण,		\
	अणु KVM_TRACE_COP0(31, 2),	"KScratch1" पूर्ण,		\
	अणु KVM_TRACE_COP0(31, 3),	"KScratch2" पूर्ण,		\
	अणु KVM_TRACE_COP0(31, 4),	"KScratch3" पूर्ण,		\
	अणु KVM_TRACE_COP0(31, 5),	"KScratch4" पूर्ण,		\
	अणु KVM_TRACE_COP0(31, 6),	"KScratch5" पूर्ण,		\
	अणु KVM_TRACE_COP0(31, 7),	"KScratch6" पूर्ण,		\
	अणु KVM_TRACE_HWR( 0, 0),		"CPUNum" पूर्ण,		\
	अणु KVM_TRACE_HWR( 1, 0),		"SYNCI_Step" पूर्ण,		\
	अणु KVM_TRACE_HWR( 2, 0),		"CC" पूर्ण,			\
	अणु KVM_TRACE_HWR( 3, 0),		"CCRes" पूर्ण,		\
	अणु KVM_TRACE_HWR(29, 0),		"ULR" पूर्ण

TRACE_EVENT(kvm_hwr,
	    TP_PROTO(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक op, अचिन्हित पूर्णांक reg,
		     अचिन्हित दीर्घ val),
	    TP_ARGS(vcpu, op, reg, val),
	    TP_STRUCT__entry(
			__field(अचिन्हित दीर्घ, val)
			__field(u16, reg)
			__field(u8, op)
	    ),

	    TP_fast_assign(
			__entry->val = val;
			__entry->reg = reg;
			__entry->op = op;
	    ),

	    TP_prपूर्णांकk("%s %s (%s:%u:%u) 0x%08lx",
		      __prपूर्णांक_symbolic(__entry->op,
				       kvm_trace_symbol_hwr_ops),
		      __prपूर्णांक_symbolic(__entry->reg,
				       kvm_trace_symbol_hwr_regs),
		      __prपूर्णांक_symbolic(__entry->reg >> 8,
				       kvm_trace_symbol_hwr_cop),
		      (__entry->reg >> 3) & 0x1f,
		      __entry->reg & 0x7,
		      __entry->val)
);

#घोषणा KVM_TRACE_AUX_RESTORE		0
#घोषणा KVM_TRACE_AUX_SAVE		1
#घोषणा KVM_TRACE_AUX_ENABLE		2
#घोषणा KVM_TRACE_AUX_DISABLE		3
#घोषणा KVM_TRACE_AUX_DISCARD		4

#घोषणा KVM_TRACE_AUX_FPU		1
#घोषणा KVM_TRACE_AUX_MSA		2
#घोषणा KVM_TRACE_AUX_FPU_MSA		3

#घोषणा kvm_trace_symbol_aux_op		\
	अणु KVM_TRACE_AUX_RESTORE, "restore" पूर्ण,	\
	अणु KVM_TRACE_AUX_SAVE,    "save" पूर्ण,	\
	अणु KVM_TRACE_AUX_ENABLE,  "enable" पूर्ण,	\
	अणु KVM_TRACE_AUX_DISABLE, "disable" पूर्ण,	\
	अणु KVM_TRACE_AUX_DISCARD, "discard" पूर्ण

#घोषणा kvm_trace_symbol_aux_state		\
	अणु KVM_TRACE_AUX_FPU,     "FPU" पूर्ण,	\
	अणु KVM_TRACE_AUX_MSA,     "MSA" पूर्ण,	\
	अणु KVM_TRACE_AUX_FPU_MSA, "FPU & MSA" पूर्ण

TRACE_EVENT(kvm_aux,
	    TP_PROTO(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक op,
		     अचिन्हित पूर्णांक state),
	    TP_ARGS(vcpu, op, state),
	    TP_STRUCT__entry(
			__field(अचिन्हित दीर्घ, pc)
			__field(u8, op)
			__field(u8, state)
	    ),

	    TP_fast_assign(
			__entry->pc = vcpu->arch.pc;
			__entry->op = op;
			__entry->state = state;
	    ),

	    TP_prपूर्णांकk("%s %s PC: 0x%08lx",
		      __prपूर्णांक_symbolic(__entry->op,
				       kvm_trace_symbol_aux_op),
		      __prपूर्णांक_symbolic(__entry->state,
				       kvm_trace_symbol_aux_state),
		      __entry->pc)
);

TRACE_EVENT(kvm_asid_change,
	    TP_PROTO(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक old_asid,
		     अचिन्हित पूर्णांक new_asid),
	    TP_ARGS(vcpu, old_asid, new_asid),
	    TP_STRUCT__entry(
			__field(अचिन्हित दीर्घ, pc)
			__field(u8, old_asid)
			__field(u8, new_asid)
	    ),

	    TP_fast_assign(
			__entry->pc = vcpu->arch.pc;
			__entry->old_asid = old_asid;
			__entry->new_asid = new_asid;
	    ),

	    TP_prपूर्णांकk("PC: 0x%08lx old: 0x%02x new: 0x%02x",
		      __entry->pc,
		      __entry->old_asid,
		      __entry->new_asid)
);

TRACE_EVENT(kvm_guestid_change,
	    TP_PROTO(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक guestid),
	    TP_ARGS(vcpu, guestid),
	    TP_STRUCT__entry(
			__field(अचिन्हित पूर्णांक, guestid)
	    ),

	    TP_fast_assign(
			__entry->guestid = guestid;
	    ),

	    TP_prपूर्णांकk("GuestID: 0x%02x",
		      __entry->guestid)
);

TRACE_EVENT_FN(kvm_guest_mode_change,
	    TP_PROTO(काष्ठा kvm_vcpu *vcpu),
	    TP_ARGS(vcpu),
	    TP_STRUCT__entry(
			__field(अचिन्हित दीर्घ, epc)
			__field(अचिन्हित दीर्घ, pc)
			__field(अचिन्हित दीर्घ, badvaddr)
			__field(अचिन्हित पूर्णांक, status)
			__field(अचिन्हित पूर्णांक, cause)
	    ),

	    TP_fast_assign(
			__entry->epc = kvm_पढ़ो_c0_guest_epc(vcpu->arch.cop0);
			__entry->pc = vcpu->arch.pc;
			__entry->badvaddr = kvm_पढ़ो_c0_guest_badvaddr(vcpu->arch.cop0);
			__entry->status = kvm_पढ़ो_c0_guest_status(vcpu->arch.cop0);
			__entry->cause = kvm_पढ़ो_c0_guest_cause(vcpu->arch.cop0);
	    ),

	    TP_prपूर्णांकk("EPC: 0x%08lx PC: 0x%08lx Status: 0x%08x Cause: 0x%08x BadVAddr: 0x%08lx",
		      __entry->epc,
		      __entry->pc,
		      __entry->status,
		      __entry->cause,
		      __entry->badvaddr),

	    kvm_guest_mode_change_trace_reg,
	    kvm_guest_mode_change_trace_unreg
);

#पूर्ण_अगर /* _TRACE_KVM_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
