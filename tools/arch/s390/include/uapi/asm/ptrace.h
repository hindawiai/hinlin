<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 *  S390 version
 *    Copyright IBM Corp. 1999, 2000
 *    Author(s): Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com)
 */

#अगर_अघोषित _UAPI_S390_PTRACE_H
#घोषणा _UAPI_S390_PTRACE_H

/*
 * Offsets in the user_regs_काष्ठा. They are used क्रम the ptrace
 * प्रणाली call and in entry.S
 */
#अगर_अघोषित __s390x__

#घोषणा PT_PSWMASK  0x00
#घोषणा PT_PSWADDR  0x04
#घोषणा PT_GPR0     0x08
#घोषणा PT_GPR1     0x0C
#घोषणा PT_GPR2     0x10
#घोषणा PT_GPR3     0x14
#घोषणा PT_GPR4     0x18
#घोषणा PT_GPR5     0x1C
#घोषणा PT_GPR6     0x20
#घोषणा PT_GPR7     0x24
#घोषणा PT_GPR8     0x28
#घोषणा PT_GPR9     0x2C
#घोषणा PT_GPR10    0x30
#घोषणा PT_GPR11    0x34
#घोषणा PT_GPR12    0x38
#घोषणा PT_GPR13    0x3C
#घोषणा PT_GPR14    0x40
#घोषणा PT_GPR15    0x44
#घोषणा PT_ACR0     0x48
#घोषणा PT_ACR1     0x4C
#घोषणा PT_ACR2     0x50
#घोषणा PT_ACR3     0x54
#घोषणा PT_ACR4	    0x58
#घोषणा PT_ACR5	    0x5C
#घोषणा PT_ACR6	    0x60
#घोषणा PT_ACR7	    0x64
#घोषणा PT_ACR8	    0x68
#घोषणा PT_ACR9	    0x6C
#घोषणा PT_ACR10    0x70
#घोषणा PT_ACR11    0x74
#घोषणा PT_ACR12    0x78
#घोषणा PT_ACR13    0x7C
#घोषणा PT_ACR14    0x80
#घोषणा PT_ACR15    0x84
#घोषणा PT_ORIGGPR2 0x88
#घोषणा PT_FPC	    0x90
/*
 * A nasty fact of lअगरe that the ptrace api
 * only supports passing of दीर्घs.
 */
#घोषणा PT_FPR0_HI  0x98
#घोषणा PT_FPR0_LO  0x9C
#घोषणा PT_FPR1_HI  0xA0
#घोषणा PT_FPR1_LO  0xA4
#घोषणा PT_FPR2_HI  0xA8
#घोषणा PT_FPR2_LO  0xAC
#घोषणा PT_FPR3_HI  0xB0
#घोषणा PT_FPR3_LO  0xB4
#घोषणा PT_FPR4_HI  0xB8
#घोषणा PT_FPR4_LO  0xBC
#घोषणा PT_FPR5_HI  0xC0
#घोषणा PT_FPR5_LO  0xC4
#घोषणा PT_FPR6_HI  0xC8
#घोषणा PT_FPR6_LO  0xCC
#घोषणा PT_FPR7_HI  0xD0
#घोषणा PT_FPR7_LO  0xD4
#घोषणा PT_FPR8_HI  0xD8
#घोषणा PT_FPR8_LO  0XDC
#घोषणा PT_FPR9_HI  0xE0
#घोषणा PT_FPR9_LO  0xE4
#घोषणा PT_FPR10_HI 0xE8
#घोषणा PT_FPR10_LO 0xEC
#घोषणा PT_FPR11_HI 0xF0
#घोषणा PT_FPR11_LO 0xF4
#घोषणा PT_FPR12_HI 0xF8
#घोषणा PT_FPR12_LO 0xFC
#घोषणा PT_FPR13_HI 0x100
#घोषणा PT_FPR13_LO 0x104
#घोषणा PT_FPR14_HI 0x108
#घोषणा PT_FPR14_LO 0x10C
#घोषणा PT_FPR15_HI 0x110
#घोषणा PT_FPR15_LO 0x114
#घोषणा PT_CR_9	    0x118
#घोषणा PT_CR_10    0x11C
#घोषणा PT_CR_11    0x120
#घोषणा PT_IEEE_IP  0x13C
#घोषणा PT_LASTOFF  PT_IEEE_IP
#घोषणा PT_ENDREGS  0x140-1

#घोषणा GPR_SIZE	4
#घोषणा CR_SIZE		4

#घोषणा STACK_FRAME_OVERHEAD	96	/* size of minimum stack frame */

#अन्यथा /* __s390x__ */

#घोषणा PT_PSWMASK  0x00
#घोषणा PT_PSWADDR  0x08
#घोषणा PT_GPR0     0x10
#घोषणा PT_GPR1     0x18
#घोषणा PT_GPR2     0x20
#घोषणा PT_GPR3     0x28
#घोषणा PT_GPR4     0x30
#घोषणा PT_GPR5     0x38
#घोषणा PT_GPR6     0x40
#घोषणा PT_GPR7     0x48
#घोषणा PT_GPR8     0x50
#घोषणा PT_GPR9     0x58
#घोषणा PT_GPR10    0x60
#घोषणा PT_GPR11    0x68
#घोषणा PT_GPR12    0x70
#घोषणा PT_GPR13    0x78
#घोषणा PT_GPR14    0x80
#घोषणा PT_GPR15    0x88
#घोषणा PT_ACR0     0x90
#घोषणा PT_ACR1     0x94
#घोषणा PT_ACR2     0x98
#घोषणा PT_ACR3     0x9C
#घोषणा PT_ACR4	    0xA0
#घोषणा PT_ACR5	    0xA4
#घोषणा PT_ACR6	    0xA8
#घोषणा PT_ACR7	    0xAC
#घोषणा PT_ACR8	    0xB0
#घोषणा PT_ACR9	    0xB4
#घोषणा PT_ACR10    0xB8
#घोषणा PT_ACR11    0xBC
#घोषणा PT_ACR12    0xC0
#घोषणा PT_ACR13    0xC4
#घोषणा PT_ACR14    0xC8
#घोषणा PT_ACR15    0xCC
#घोषणा PT_ORIGGPR2 0xD0
#घोषणा PT_FPC	    0xD8
#घोषणा PT_FPR0     0xE0
#घोषणा PT_FPR1     0xE8
#घोषणा PT_FPR2     0xF0
#घोषणा PT_FPR3     0xF8
#घोषणा PT_FPR4     0x100
#घोषणा PT_FPR5     0x108
#घोषणा PT_FPR6     0x110
#घोषणा PT_FPR7     0x118
#घोषणा PT_FPR8     0x120
#घोषणा PT_FPR9     0x128
#घोषणा PT_FPR10    0x130
#घोषणा PT_FPR11    0x138
#घोषणा PT_FPR12    0x140
#घोषणा PT_FPR13    0x148
#घोषणा PT_FPR14    0x150
#घोषणा PT_FPR15    0x158
#घोषणा PT_CR_9     0x160
#घोषणा PT_CR_10    0x168
#घोषणा PT_CR_11    0x170
#घोषणा PT_IEEE_IP  0x1A8
#घोषणा PT_LASTOFF  PT_IEEE_IP
#घोषणा PT_ENDREGS  0x1B0-1

#घोषणा GPR_SIZE	8
#घोषणा CR_SIZE		8

#घोषणा STACK_FRAME_OVERHEAD	160	 /* size of minimum stack frame */

#पूर्ण_अगर /* __s390x__ */

#घोषणा NUM_GPRS	16
#घोषणा NUM_FPRS	16
#घोषणा NUM_CRS		16
#घोषणा NUM_ACRS	16

#घोषणा NUM_CR_WORDS	3

#घोषणा FPR_SIZE	8
#घोषणा FPC_SIZE	4
#घोषणा FPC_PAD_SIZE	4 /* gcc insists on aligning the fpregs */
#घोषणा ACR_SIZE	4


#घोषणा PTRACE_OLDSETOPTIONS		21
#घोषणा PTRACE_SYSEMU			31
#घोषणा PTRACE_SYSEMU_SINGLESTEP	32
#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/मानकघोष.स>
#समावेश <linux/types.h>

प्रकार जोड़ अणु
	भग्न	f;
	द्विगुन	d;
	__u64	ui;
	काष्ठा
	अणु
		__u32 hi;
		__u32 lo;
	पूर्ण fp;
पूर्ण freg_t;

प्रकार काष्ठा अणु
	__u32	fpc;
	__u32	pad;
	freg_t	fprs[NUM_FPRS];
पूर्ण s390_fp_regs;

#घोषणा FPC_EXCEPTION_MASK	0xF8000000
#घोषणा FPC_FLAGS_MASK		0x00F80000
#घोषणा FPC_DXC_MASK		0x0000FF00
#घोषणा FPC_RM_MASK		0x00000003

/* this प्रकार defines how a Program Status Word looks like */
प्रकार काष्ठा अणु
	अचिन्हित दीर्घ mask;
	अचिन्हित दीर्घ addr;
पूर्ण __attribute__ ((aligned(8))) psw_t;

#अगर_अघोषित __s390x__

#घोषणा PSW_MASK_PER		0x40000000UL
#घोषणा PSW_MASK_DAT		0x04000000UL
#घोषणा PSW_MASK_IO		0x02000000UL
#घोषणा PSW_MASK_EXT		0x01000000UL
#घोषणा PSW_MASK_KEY		0x00F00000UL
#घोषणा PSW_MASK_BASE		0x00080000UL	/* always one */
#घोषणा PSW_MASK_MCHECK		0x00040000UL
#घोषणा PSW_MASK_WAIT		0x00020000UL
#घोषणा PSW_MASK_PSTATE		0x00010000UL
#घोषणा PSW_MASK_ASC		0x0000C000UL
#घोषणा PSW_MASK_CC		0x00003000UL
#घोषणा PSW_MASK_PM		0x00000F00UL
#घोषणा PSW_MASK_RI		0x00000000UL
#घोषणा PSW_MASK_EA		0x00000000UL
#घोषणा PSW_MASK_BA		0x00000000UL

#घोषणा PSW_MASK_USER		0x0000FF00UL

#घोषणा PSW_ADDR_AMODE		0x80000000UL
#घोषणा PSW_ADDR_INSN		0x7FFFFFFFUL

#घोषणा PSW_DEFAULT_KEY		(((अचिन्हित दीर्घ) PAGE_DEFAULT_ACC) << 20)

#घोषणा PSW_ASC_PRIMARY		0x00000000UL
#घोषणा PSW_ASC_ACCREG		0x00004000UL
#घोषणा PSW_ASC_SECONDARY	0x00008000UL
#घोषणा PSW_ASC_HOME		0x0000C000UL

#अन्यथा /* __s390x__ */

#घोषणा PSW_MASK_PER		0x4000000000000000UL
#घोषणा PSW_MASK_DAT		0x0400000000000000UL
#घोषणा PSW_MASK_IO		0x0200000000000000UL
#घोषणा PSW_MASK_EXT		0x0100000000000000UL
#घोषणा PSW_MASK_BASE		0x0000000000000000UL
#घोषणा PSW_MASK_KEY		0x00F0000000000000UL
#घोषणा PSW_MASK_MCHECK		0x0004000000000000UL
#घोषणा PSW_MASK_WAIT		0x0002000000000000UL
#घोषणा PSW_MASK_PSTATE		0x0001000000000000UL
#घोषणा PSW_MASK_ASC		0x0000C00000000000UL
#घोषणा PSW_MASK_CC		0x0000300000000000UL
#घोषणा PSW_MASK_PM		0x00000F0000000000UL
#घोषणा PSW_MASK_RI		0x0000008000000000UL
#घोषणा PSW_MASK_EA		0x0000000100000000UL
#घोषणा PSW_MASK_BA		0x0000000080000000UL

#घोषणा PSW_MASK_USER		0x0000FF0180000000UL

#घोषणा PSW_ADDR_AMODE		0x0000000000000000UL
#घोषणा PSW_ADDR_INSN		0xFFFFFFFFFFFFFFFFUL

#घोषणा PSW_DEFAULT_KEY		(((अचिन्हित दीर्घ) PAGE_DEFAULT_ACC) << 52)

#घोषणा PSW_ASC_PRIMARY		0x0000000000000000UL
#घोषणा PSW_ASC_ACCREG		0x0000400000000000UL
#घोषणा PSW_ASC_SECONDARY	0x0000800000000000UL
#घोषणा PSW_ASC_HOME		0x0000C00000000000UL

#पूर्ण_अगर /* __s390x__ */


/*
 * The s390_regs काष्ठाure is used to define the elf_gregset_t.
 */
प्रकार काष्ठा अणु
	psw_t psw;
	अचिन्हित दीर्घ gprs[NUM_GPRS];
	अचिन्हित पूर्णांक  acrs[NUM_ACRS];
	अचिन्हित दीर्घ orig_gpr2;
पूर्ण s390_regs;

/*
 * The user_pt_regs काष्ठाure exports the beginning of
 * the in-kernel pt_regs काष्ठाure to user space.
 */
प्रकार काष्ठा अणु
	अचिन्हित दीर्घ args[1];
	psw_t psw;
	अचिन्हित दीर्घ gprs[NUM_GPRS];
पूर्ण user_pt_regs;

/*
 * Now क्रम the user space program event recording (trace) definitions.
 * The following काष्ठाures are used only क्रम the ptrace पूर्णांकerface, करोn't
 * touch or even look at it अगर you करोn't want to modअगरy the user-space
 * ptrace पूर्णांकerface. In particular stay away from it क्रम in-kernel PER.
 */
प्रकार काष्ठा अणु
	अचिन्हित दीर्घ cr[NUM_CR_WORDS];
पूर्ण per_cr_words;

#घोषणा PER_EM_MASK 0xE8000000UL

प्रकार काष्ठा अणु
#अगर_घोषित __s390x__
	अचिन्हित		       : 32;
#पूर्ण_अगर /* __s390x__ */
	अचिन्हित em_branching	       : 1;
	अचिन्हित em_inकाष्ठाion_fetch  : 1;
	/*
	 * Switching on storage alteration स्वतःmatically fixes
	 * the storage alteration event bit in the users std.
	 */
	अचिन्हित em_storage_alteration : 1;
	अचिन्हित em_gpr_alt_unused     : 1;
	अचिन्हित em_store_real_address : 1;
	अचिन्हित		       : 3;
	अचिन्हित branch_addr_ctl       : 1;
	अचिन्हित		       : 1;
	अचिन्हित storage_alt_space_ctl : 1;
	अचिन्हित		       : 21;
	अचिन्हित दीर्घ starting_addr;
	अचिन्हित दीर्घ ending_addr;
पूर्ण per_cr_bits;

प्रकार काष्ठा अणु
	अचिन्हित लघु perc_aपंचांगid;
	अचिन्हित दीर्घ address;
	अचिन्हित अक्षर access_id;
पूर्ण per_lowcore_words;

प्रकार काष्ठा अणु
	अचिन्हित perc_branching		 : 1;
	अचिन्हित perc_inकाष्ठाion_fetch  : 1;
	अचिन्हित perc_storage_alteration : 1;
	अचिन्हित perc_gpr_alt_unused	 : 1;
	अचिन्हित perc_store_real_address : 1;
	अचिन्हित			 : 3;
	अचिन्हित aपंचांगid_psw_bit_31	 : 1;
	अचिन्हित aपंचांगid_validity_bit	 : 1;
	अचिन्हित aपंचांगid_psw_bit_32	 : 1;
	अचिन्हित aपंचांगid_psw_bit_5	 : 1;
	अचिन्हित aपंचांगid_psw_bit_16	 : 1;
	अचिन्हित aपंचांगid_psw_bit_17	 : 1;
	अचिन्हित si			 : 2;
	अचिन्हित दीर्घ address;
	अचिन्हित			 : 4;
	अचिन्हित access_id		 : 4;
पूर्ण per_lowcore_bits;

प्रकार काष्ठा अणु
	जोड़ अणु
		per_cr_words   words;
		per_cr_bits    bits;
	पूर्ण control_regs;
	/*
	 * The single_step and inकाष्ठाion_fetch bits are obsolete,
	 * the kernel always sets them to zero. To enable single
	 * stepping use ptrace(PTRACE_SINGLESTEP) instead.
	 */
	अचिन्हित  single_step	    : 1;
	अचिन्हित  inकाष्ठाion_fetch : 1;
	अचिन्हित		    : 30;
	/*
	 * These addresses are copied पूर्णांकo cr10 & cr11 अगर single
	 * stepping is चयनed off
	 */
	अचिन्हित दीर्घ starting_addr;
	अचिन्हित दीर्घ ending_addr;
	जोड़ अणु
		per_lowcore_words words;
		per_lowcore_bits  bits;
	पूर्ण lowcore;
पूर्ण per_काष्ठा;

प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक  len;
	अचिन्हित दीर्घ kernel_addr;
	अचिन्हित दीर्घ process_addr;
पूर्ण ptrace_area;

/*
 * S/390 specअगरic non posix ptrace requests. I chose unusual values so
 * they are unlikely to clash with future ptrace definitions.
 */
#घोषणा PTRACE_PEEKUSR_AREA	      0x5000
#घोषणा PTRACE_POKEUSR_AREA	      0x5001
#घोषणा PTRACE_PEEKTEXT_AREA	      0x5002
#घोषणा PTRACE_PEEKDATA_AREA	      0x5003
#घोषणा PTRACE_POKETEXT_AREA	      0x5004
#घोषणा PTRACE_POKEDATA_AREA	      0x5005
#घोषणा PTRACE_GET_LAST_BREAK	      0x5006
#घोषणा PTRACE_PEEK_SYSTEM_CALL       0x5007
#घोषणा PTRACE_POKE_SYSTEM_CALL	      0x5008
#घोषणा PTRACE_ENABLE_TE	      0x5009
#घोषणा PTRACE_DISABLE_TE	      0x5010
#घोषणा PTRACE_TE_ABORT_RAND	      0x5011

/*
 * The numbers chosen here are somewhat arbitrary but असलolutely MUST
 * not overlap with any of the number asचिन्हित in <linux/ptrace.h>.
 */
#घोषणा PTRACE_SINGLEBLOCK	12	/* resume execution until next branch */

/*
 * PT_PROT definition is loosely based on hppa bsd definition in
 * gdb/hppab-nat.c
 */
#घोषणा PTRACE_PROT			  21

प्रकार क्रमागत अणु
	ptprot_set_access_watchpoपूर्णांक,
	ptprot_set_ग_लिखो_watchpoपूर्णांक,
	ptprot_disable_watchpoपूर्णांक
पूर्ण ptprot_flags;

प्रकार काष्ठा अणु
	अचिन्हित दीर्घ lowaddr;
	अचिन्हित दीर्घ hiaddr;
	ptprot_flags prot;
पूर्ण ptprot_area;

/* Sequence of bytes क्रम अवरोधpoपूर्णांक illegal inकाष्ठाion.  */
#घोषणा S390_BREAKPOINT     अणु0x0,0x1पूर्ण
#घोषणा S390_BREAKPOINT_U16 ((__u16)0x0001)
#घोषणा S390_SYSCALL_OPCODE ((__u16)0x0a00)
#घोषणा S390_SYSCALL_SIZE   2

/*
 * The user_regs_काष्ठा defines the way the user रेजिस्टरs are
 * store on the stack क्रम संकेत handling.
 */
काष्ठा user_regs_काष्ठा अणु
	psw_t psw;
	अचिन्हित दीर्घ gprs[NUM_GPRS];
	अचिन्हित पूर्णांक  acrs[NUM_ACRS];
	अचिन्हित दीर्घ orig_gpr2;
	s390_fp_regs fp_regs;
	/*
	 * These per रेजिस्टरs are in here so that gdb can modअगरy them
	 * itself as there is no "official" ptrace पूर्णांकerface क्रम hardware
	 * watchpoपूर्णांकs. This is the way पूर्णांकel करोes it.
	 */
	per_काष्ठा per_info;
	अचिन्हित दीर्घ ieee_inकाष्ठाion_poपूर्णांकer;	/* obsolete, always 0 */
पूर्ण;

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _UAPI_S390_PTRACE_H */
