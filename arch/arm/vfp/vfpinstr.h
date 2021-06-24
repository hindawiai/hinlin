<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/arch/arm/vfp/vfpinstr.h
 *
 *  Copyright (C) 2004 ARM Limited.
 *  Written by Deep Blue Solutions Limited.
 *
 * VFP inकाष्ठाion masks.
 */
#घोषणा INST_CPRTDO(inst)	(((inst) & 0x0f000000) == 0x0e000000)
#घोषणा INST_CPRT(inst)		((inst) & (1 << 4))
#घोषणा INST_CPRT_L(inst)	((inst) & (1 << 20))
#घोषणा INST_CPRT_Rd(inst)	(((inst) & (15 << 12)) >> 12)
#घोषणा INST_CPRT_OP(inst)	(((inst) >> 21) & 7)
#घोषणा INST_CPNUM(inst)	((inst) & 0xf00)
#घोषणा CPNUM(cp)		((cp) << 8)

#घोषणा FOP_MASK	(0x00b00040)
#घोषणा FOP_FMAC	(0x00000000)
#घोषणा FOP_FNMAC	(0x00000040)
#घोषणा FOP_FMSC	(0x00100000)
#घोषणा FOP_FNMSC	(0x00100040)
#घोषणा FOP_FMUL	(0x00200000)
#घोषणा FOP_FNMUL	(0x00200040)
#घोषणा FOP_FADD	(0x00300000)
#घोषणा FOP_FSUB	(0x00300040)
#घोषणा FOP_FDIV	(0x00800000)
#घोषणा FOP_EXT		(0x00b00040)

#घोषणा FOP_TO_IDX(inst)	((inst & 0x00b00000) >> 20 | (inst & (1 << 6)) >> 4)

#घोषणा FEXT_MASK	(0x000f0080)
#घोषणा FEXT_FCPY	(0x00000000)
#घोषणा FEXT_FABS	(0x00000080)
#घोषणा FEXT_FNEG	(0x00010000)
#घोषणा FEXT_FSQRT	(0x00010080)
#घोषणा FEXT_FCMP	(0x00040000)
#घोषणा FEXT_FCMPE	(0x00040080)
#घोषणा FEXT_FCMPZ	(0x00050000)
#घोषणा FEXT_FCMPEZ	(0x00050080)
#घोषणा FEXT_FCVT	(0x00070080)
#घोषणा FEXT_FUITO	(0x00080000)
#घोषणा FEXT_FSITO	(0x00080080)
#घोषणा FEXT_FTOUI	(0x000c0000)
#घोषणा FEXT_FTOUIZ	(0x000c0080)
#घोषणा FEXT_FTOSI	(0x000d0000)
#घोषणा FEXT_FTOSIZ	(0x000d0080)

#घोषणा FEXT_TO_IDX(inst)	((inst & 0x000f0000) >> 15 | (inst & (1 << 7)) >> 7)

#घोषणा vfp_get_sd(inst)	((inst & 0x0000f000) >> 11 | (inst & (1 << 22)) >> 22)
#घोषणा vfp_get_dd(inst)	((inst & 0x0000f000) >> 12 | (inst & (1 << 22)) >> 18)
#घोषणा vfp_get_sm(inst)	((inst & 0x0000000f) << 1 | (inst & (1 << 5)) >> 5)
#घोषणा vfp_get_dm(inst)	((inst & 0x0000000f) | (inst & (1 << 5)) >> 1)
#घोषणा vfp_get_sn(inst)	((inst & 0x000f0000) >> 15 | (inst & (1 << 7)) >> 7)
#घोषणा vfp_get_dn(inst)	((inst & 0x000f0000) >> 16 | (inst & (1 << 7)) >> 3)

#घोषणा vfp_single(inst)	(((inst) & 0x0000f00) == 0xa00)

#घोषणा FPSCR_N	(1 << 31)
#घोषणा FPSCR_Z	(1 << 30)
#घोषणा FPSCR_C (1 << 29)
#घोषणा FPSCR_V	(1 << 28)

#अगर_घोषित CONFIG_AS_VFP_VMRS_FPINST

#घोषणा fmrx(_vfp_) (अणु			\
	u32 __v;			\
	यंत्र(".fpu	vfpv2\n"	\
	    "vmrs	%0, " #_vfp_	\
	    : "=r" (__v) : : "cc");	\
	__v;				\
 पूर्ण)

#घोषणा fmxr(_vfp_,_var_)		\
	यंत्र(".fpu	vfpv2\n"	\
	    "vmsr	" #_vfp_ ", %0"	\
	   : : "r" (_var_) : "cc")

#अन्यथा

#घोषणा vfpreg(_vfp_) #_vfp_

#घोषणा fmrx(_vfp_) (अणु			\
	u32 __v;			\
	यंत्र("mrc p10, 7, %0, " vfpreg(_vfp_) ", cr0, 0 @ fmrx	%0, " #_vfp_	\
	    : "=r" (__v) : : "cc");	\
	__v;				\
 पूर्ण)

#घोषणा fmxr(_vfp_,_var_)		\
	यंत्र("mcr p10, 7, %0, " vfpreg(_vfp_) ", cr0, 0 @ fmxr	" #_vfp_ ", %0"	\
	   : : "r" (_var_) : "cc")

#पूर्ण_अगर

u32 vfp_single_cpकरो(u32 inst, u32 fpscr);
u32 vfp_single_cprt(u32 inst, u32 fpscr, काष्ठा pt_regs *regs);

u32 vfp_द्विगुन_cpकरो(u32 inst, u32 fpscr);
