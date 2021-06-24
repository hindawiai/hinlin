<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * Copyright (C) 2001 PPC64 Team, IBM Corp
 *
 * This काष्ठा defines the way the रेजिस्टरs are stored on the
 * kernel stack during a प्रणाली call or other kernel entry.
 *
 * this should only contain अस्थिर regs
 * since we can keep non-अस्थिर in the thपढ़ो_काष्ठा
 * should set this up when only अस्थिरs are saved
 * by पूर्णांकr code.
 *
 * Since this is going on the stack, *CARE MUST BE TAKEN* to insure
 * that the overall काष्ठाure is a multiple of 16 bytes in length.
 *
 * Note that the offsets of the fields in this काष्ठा correspond with
 * the PT_* values below.  This simplअगरies arch/घातerpc/kernel/ptrace.c.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#अगर_अघोषित _UAPI_ASM_POWERPC_PTRACE_H
#घोषणा _UAPI_ASM_POWERPC_PTRACE_H


#समावेश <linux/types.h>

#अगर_अघोषित __ASSEMBLY__

#अगर_घोषित __KERNEL__
काष्ठा user_pt_regs
#अन्यथा
काष्ठा pt_regs
#पूर्ण_अगर
अणु
	अचिन्हित दीर्घ gpr[32];
	अचिन्हित दीर्घ nip;
	अचिन्हित दीर्घ msr;
	अचिन्हित दीर्घ orig_gpr3;	/* Used क्रम restarting प्रणाली calls */
	अचिन्हित दीर्घ ctr;
	अचिन्हित दीर्घ link;
	अचिन्हित दीर्घ xer;
	अचिन्हित दीर्घ ccr;
#अगर_घोषित __घातerpc64__
	अचिन्हित दीर्घ softe;		/* Soft enabled/disabled */
#अन्यथा
	अचिन्हित दीर्घ mq;		/* 601 only (not used at present) */
					/* Used on APUS to hold IPL value. */
#पूर्ण_अगर
	अचिन्हित दीर्घ trap;		/* Reason क्रम being here */
	/* N.B. क्रम critical exceptions on 4xx, the dar and dsisr
	   fields are overloaded to hold srr0 and srr1. */
	अचिन्हित दीर्घ dar;		/* Fault रेजिस्टरs */
	अचिन्हित दीर्घ dsisr;		/* on 4xx/Book-E used क्रम ESR */
	अचिन्हित दीर्घ result;		/* Result of a प्रणाली call */
पूर्ण;

#पूर्ण_अगर /* __ASSEMBLY__ */


/*
 * Offsets used by 'ptrace' प्रणाली call पूर्णांकerface.
 * These can't be changed without अवरोधing binary compatibility
 * with MkLinux, etc.
 */
#घोषणा PT_R0	0
#घोषणा PT_R1	1
#घोषणा PT_R2	2
#घोषणा PT_R3	3
#घोषणा PT_R4	4
#घोषणा PT_R5	5
#घोषणा PT_R6	6
#घोषणा PT_R7	7
#घोषणा PT_R8	8
#घोषणा PT_R9	9
#घोषणा PT_R10	10
#घोषणा PT_R11	11
#घोषणा PT_R12	12
#घोषणा PT_R13	13
#घोषणा PT_R14	14
#घोषणा PT_R15	15
#घोषणा PT_R16	16
#घोषणा PT_R17	17
#घोषणा PT_R18	18
#घोषणा PT_R19	19
#घोषणा PT_R20	20
#घोषणा PT_R21	21
#घोषणा PT_R22	22
#घोषणा PT_R23	23
#घोषणा PT_R24	24
#घोषणा PT_R25	25
#घोषणा PT_R26	26
#घोषणा PT_R27	27
#घोषणा PT_R28	28
#घोषणा PT_R29	29
#घोषणा PT_R30	30
#घोषणा PT_R31	31

#घोषणा PT_NIP	32
#घोषणा PT_MSR	33
#घोषणा PT_ORIG_R3 34
#घोषणा PT_CTR	35
#घोषणा PT_LNK	36
#घोषणा PT_XER	37
#घोषणा PT_CCR	38
#अगर_अघोषित __घातerpc64__
#घोषणा PT_MQ	39
#अन्यथा
#घोषणा PT_SOFTE 39
#पूर्ण_अगर
#घोषणा PT_TRAP	40
#घोषणा PT_DAR	41
#घोषणा PT_DSISR 42
#घोषणा PT_RESULT 43
#घोषणा PT_DSCR 44
#घोषणा PT_REGS_COUNT 44

#घोषणा PT_FPR0	48	/* each FP reg occupies 2 slots in this space */

#अगर_अघोषित __घातerpc64__

#घोषणा PT_FPR31 (PT_FPR0 + 2*31)
#घोषणा PT_FPSCR (PT_FPR0 + 2*32 + 1)

#अन्यथा /* __घातerpc64__ */

#घोषणा PT_FPSCR (PT_FPR0 + 32)	/* each FP reg occupies 1 slot in 64-bit space */


#घोषणा PT_VR0 82	/* each Vector reg occupies 2 slots in 64-bit */
#घोषणा PT_VSCR (PT_VR0 + 32*2 + 1)
#घोषणा PT_VRSAVE (PT_VR0 + 33*2)


/*
 * Only store first 32 VSRs here. The second 32 VSRs in VR0-31
 */
#घोषणा PT_VSR0 150	/* each VSR reg occupies 2 slots in 64-bit */
#घोषणा PT_VSR31 (PT_VSR0 + 2*31)
#पूर्ण_अगर /* __घातerpc64__ */

/*
 * Get/set all the altivec रेजिस्टरs v0..v31, vscr, vrsave, in one go.
 * The transfer totals 34 quadword.  Quadwords 0-31 contain the
 * corresponding vector रेजिस्टरs.  Quadword 32 contains the vscr as the
 * last word (offset 12) within that quadword.  Quadword 33 contains the
 * vrsave as the first word (offset 0) within the quadword.
 *
 * This definition of the VMX state is compatible with the current PPC32
 * ptrace पूर्णांकerface.  This allows संकेत handling and ptrace to use the same
 * काष्ठाures.  This also simplअगरies the implementation of a bi-arch
 * (combined (32- and 64-bit) gdb.
 */
#घोषणा PTRACE_GETVRREGS	0x12
#घोषणा PTRACE_SETVRREGS	0x13

/* Get/set all the upper 32-bits of the SPE रेजिस्टरs, accumulator, and
 * spefscr, in one go */
#घोषणा PTRACE_GETEVRREGS	0x14
#घोषणा PTRACE_SETEVRREGS	0x15

/* Get the first 32 128bit VSX रेजिस्टरs */
#घोषणा PTRACE_GETVSRREGS	0x1b
#घोषणा PTRACE_SETVSRREGS	0x1c

/* Syscall emulation defines */
#घोषणा PTRACE_SYSEMU			0x1d
#घोषणा PTRACE_SYSEMU_SINGLESTEP	0x1e

/*
 * Get or set a debug रेजिस्टर. The first 16 are DABR रेजिस्टरs and the
 * second 16 are IABR रेजिस्टरs.
 */
#घोषणा PTRACE_GET_DEBUGREG	0x19
#घोषणा PTRACE_SET_DEBUGREG	0x1a

/* (new) PTRACE requests using the same numbers as x86 and the same
 * argument ordering. Additionally, they support more रेजिस्टरs too
 */
#घोषणा PTRACE_GETREGS            0xc
#घोषणा PTRACE_SETREGS            0xd
#घोषणा PTRACE_GETFPREGS          0xe
#घोषणा PTRACE_SETFPREGS          0xf
#घोषणा PTRACE_GETREGS64	  0x16
#घोषणा PTRACE_SETREGS64	  0x17

/* Calls to trace a 64bit program from a 32bit program */
#घोषणा PPC_PTRACE_PEEKTEXT_3264 0x95
#घोषणा PPC_PTRACE_PEEKDATA_3264 0x94
#घोषणा PPC_PTRACE_POKETEXT_3264 0x93
#घोषणा PPC_PTRACE_POKEDATA_3264 0x92
#घोषणा PPC_PTRACE_PEEKUSR_3264  0x91
#घोषणा PPC_PTRACE_POKEUSR_3264  0x90

#घोषणा PTRACE_SINGLEBLOCK	0x100	/* resume execution until next branch */

#घोषणा PPC_PTRACE_GETHWDBGINFO	0x89
#घोषणा PPC_PTRACE_SETHWDEBUG	0x88
#घोषणा PPC_PTRACE_DELHWDEBUG	0x87

#अगर_अघोषित __ASSEMBLY__

काष्ठा ppc_debug_info अणु
	__u32 version;			/* Only version 1 exists to date */
	__u32 num_inकाष्ठाion_bps;
	__u32 num_data_bps;
	__u32 num_condition_regs;
	__u32 data_bp_alignment;
	__u32 माप_condition;		/* size of the DVC रेजिस्टर */
	__u64 features;
पूर्ण;

#पूर्ण_अगर /* __ASSEMBLY__ */

/*
 * features will have bits indication whether there is support क्रम:
 */
#घोषणा PPC_DEBUG_FEATURE_INSN_BP_RANGE		0x0000000000000001
#घोषणा PPC_DEBUG_FEATURE_INSN_BP_MASK		0x0000000000000002
#घोषणा PPC_DEBUG_FEATURE_DATA_BP_RANGE		0x0000000000000004
#घोषणा PPC_DEBUG_FEATURE_DATA_BP_MASK		0x0000000000000008
#घोषणा PPC_DEBUG_FEATURE_DATA_BP_DAWR		0x0000000000000010
#घोषणा PPC_DEBUG_FEATURE_DATA_BP_ARCH_31	0x0000000000000020

#अगर_अघोषित __ASSEMBLY__

काष्ठा ppc_hw_अवरोधpoपूर्णांक अणु
	__u32 version;		/* currently, version must be 1 */
	__u32 trigger_type;	/* only some combinations allowed */
	__u32 addr_mode;	/* address match mode */
	__u32 condition_mode;	/* अवरोध/watchpoपूर्णांक condition flags */
	__u64 addr;		/* अवरोध/watchpoपूर्णांक address */
	__u64 addr2;		/* range end or mask */
	__u64 condition_value;	/* contents of the DVC रेजिस्टर */
पूर्ण;

#पूर्ण_अगर /* __ASSEMBLY__ */

/*
 * Trigger Type
 */
#घोषणा PPC_BREAKPOINT_TRIGGER_EXECUTE	0x00000001
#घोषणा PPC_BREAKPOINT_TRIGGER_READ	0x00000002
#घोषणा PPC_BREAKPOINT_TRIGGER_WRITE	0x00000004
#घोषणा PPC_BREAKPOINT_TRIGGER_RW	\
	(PPC_BREAKPOINT_TRIGGER_READ | PPC_BREAKPOINT_TRIGGER_WRITE)

/*
 * Address Mode
 */
#घोषणा PPC_BREAKPOINT_MODE_EXACT		0x00000000
#घोषणा PPC_BREAKPOINT_MODE_RANGE_INCLUSIVE	0x00000001
#घोषणा PPC_BREAKPOINT_MODE_RANGE_EXCLUSIVE	0x00000002
#घोषणा PPC_BREAKPOINT_MODE_MASK		0x00000003

/*
 * Condition Mode
 */
#घोषणा PPC_BREAKPOINT_CONDITION_MODE	0x00000003
#घोषणा PPC_BREAKPOINT_CONDITION_NONE	0x00000000
#घोषणा PPC_BREAKPOINT_CONDITION_AND	0x00000001
#घोषणा PPC_BREAKPOINT_CONDITION_EXACT	PPC_BREAKPOINT_CONDITION_AND
#घोषणा PPC_BREAKPOINT_CONDITION_OR	0x00000002
#घोषणा PPC_BREAKPOINT_CONDITION_AND_OR	0x00000003
#घोषणा PPC_BREAKPOINT_CONDITION_BE_ALL	0x00ff0000
#घोषणा PPC_BREAKPOINT_CONDITION_BE_SHIFT	16
#घोषणा PPC_BREAKPOINT_CONDITION_BE(n)	\
	(1<<((n)+PPC_BREAKPOINT_CONDITION_BE_SHIFT))

#पूर्ण_अगर /* _UAPI_ASM_POWERPC_PTRACE_H */
