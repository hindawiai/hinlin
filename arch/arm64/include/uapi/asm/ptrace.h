<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Based on arch/arm/include/यंत्र/ptrace.h
 *
 * Copyright (C) 1996-2003 Russell King
 * Copyright (C) 2012 ARM Ltd.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#अगर_अघोषित _UAPI__ASM_PTRACE_H
#घोषणा _UAPI__ASM_PTRACE_H

#समावेश <linux/types.h>

#समावेश <यंत्र/hwcap.h>
#समावेश <यंत्र/sve_context.h>


/*
 * PSR bits
 */
#घोषणा PSR_MODE_EL0t	0x00000000
#घोषणा PSR_MODE_EL1t	0x00000004
#घोषणा PSR_MODE_EL1h	0x00000005
#घोषणा PSR_MODE_EL2t	0x00000008
#घोषणा PSR_MODE_EL2h	0x00000009
#घोषणा PSR_MODE_EL3t	0x0000000c
#घोषणा PSR_MODE_EL3h	0x0000000d
#घोषणा PSR_MODE_MASK	0x0000000f

/* AArch32 CPSR bits */
#घोषणा PSR_MODE32_BIT		0x00000010

/* AArch64 SPSR bits */
#घोषणा PSR_F_BIT	0x00000040
#घोषणा PSR_I_BIT	0x00000080
#घोषणा PSR_A_BIT	0x00000100
#घोषणा PSR_D_BIT	0x00000200
#घोषणा PSR_BTYPE_MASK	0x00000c00
#घोषणा PSR_SSBS_BIT	0x00001000
#घोषणा PSR_PAN_BIT	0x00400000
#घोषणा PSR_UAO_BIT	0x00800000
#घोषणा PSR_DIT_BIT	0x01000000
#घोषणा PSR_TCO_BIT	0x02000000
#घोषणा PSR_V_BIT	0x10000000
#घोषणा PSR_C_BIT	0x20000000
#घोषणा PSR_Z_BIT	0x40000000
#घोषणा PSR_N_BIT	0x80000000

#घोषणा PSR_BTYPE_SHIFT		10

/*
 * Groups of PSR bits
 */
#घोषणा PSR_f		0xff000000	/* Flags		*/
#घोषणा PSR_s		0x00ff0000	/* Status		*/
#घोषणा PSR_x		0x0000ff00	/* Extension		*/
#घोषणा PSR_c		0x000000ff	/* Control		*/

/* Convenience names क्रम the values of PSTATE.BTYPE */
#घोषणा PSR_BTYPE_NONE		(0b00 << PSR_BTYPE_SHIFT)
#घोषणा PSR_BTYPE_JC		(0b01 << PSR_BTYPE_SHIFT)
#घोषणा PSR_BTYPE_C		(0b10 << PSR_BTYPE_SHIFT)
#घोषणा PSR_BTYPE_J		(0b11 << PSR_BTYPE_SHIFT)

/* syscall emulation path in ptrace */
#घोषणा PTRACE_SYSEMU		  31
#घोषणा PTRACE_SYSEMU_SINGLESTEP  32
/* MTE allocation tag access */
#घोषणा PTRACE_PEEKMTETAGS	  33
#घोषणा PTRACE_POKEMTETAGS	  34

#अगर_अघोषित __ASSEMBLY__

/*
 * User काष्ठाures क्रम general purpose, भग्नing poपूर्णांक and debug रेजिस्टरs.
 */
काष्ठा user_pt_regs अणु
	__u64		regs[31];
	__u64		sp;
	__u64		pc;
	__u64		pstate;
पूर्ण;

काष्ठा user_fpsimd_state अणु
	__uपूर्णांक128_t	vregs[32];
	__u32		fpsr;
	__u32		fpcr;
	__u32		__reserved[2];
पूर्ण;

काष्ठा user_hwdebug_state अणु
	__u32		dbg_info;
	__u32		pad;
	काष्ठा अणु
		__u64	addr;
		__u32	ctrl;
		__u32	pad;
	पूर्ण		dbg_regs[16];
पूर्ण;

/* SVE/FP/SIMD state (NT_ARM_SVE) */

काष्ठा user_sve_header अणु
	__u32 size; /* total meaningful regset content in bytes */
	__u32 max_size; /* maxmium possible size क्रम this thपढ़ो */
	__u16 vl; /* current vector length */
	__u16 max_vl; /* maximum possible vector length */
	__u16 flags;
	__u16 __reserved;
पूर्ण;

/* Definitions क्रम user_sve_header.flags: */
#घोषणा SVE_PT_REGS_MASK		(1 << 0)

#घोषणा SVE_PT_REGS_FPSIMD		0
#घोषणा SVE_PT_REGS_SVE			SVE_PT_REGS_MASK

/*
 * Common SVE_PT_* flags:
 * These must be kept in sync with prctl पूर्णांकerface in <linux/prctl.h>
 */
#घोषणा SVE_PT_VL_INHERIT		((1 << 17) /* PR_SVE_VL_INHERIT */ >> 16)
#घोषणा SVE_PT_VL_ONEXEC		((1 << 18) /* PR_SVE_SET_VL_ONEXEC */ >> 16)


/*
 * The reमुख्यder of the SVE state follows काष्ठा user_sve_header.  The
 * total size of the SVE state (including header) depends on the
 * metadata in the header:  SVE_PT_SIZE(vq, flags) gives the total size
 * of the state in bytes, including the header.
 *
 * Refer to <यंत्र/sigcontext.h> क्रम details of how to pass the correct
 * "vq" argument to these macros.
 */

/* Offset from the start of काष्ठा user_sve_header to the रेजिस्टर data */
#घोषणा SVE_PT_REGS_OFFSET						\
	((माप(काष्ठा user_sve_header) + (__SVE_VQ_BYTES - 1))	\
		/ __SVE_VQ_BYTES * __SVE_VQ_BYTES)

/*
 * The रेजिस्टर data content and layout depends on the value of the
 * flags field.
 */

/*
 * (flags & SVE_PT_REGS_MASK) == SVE_PT_REGS_FPSIMD हाल:
 *
 * The payload starts at offset SVE_PT_FPSIMD_OFFSET, and is of type
 * काष्ठा user_fpsimd_state.  Additional data might be appended in the
 * future: use SVE_PT_FPSIMD_SIZE(vq, flags) to compute the total size.
 * SVE_PT_FPSIMD_SIZE(vq, flags) will never be less than
 * माप(काष्ठा user_fpsimd_state).
 */

#घोषणा SVE_PT_FPSIMD_OFFSET		SVE_PT_REGS_OFFSET

#घोषणा SVE_PT_FPSIMD_SIZE(vq, flags)	(माप(काष्ठा user_fpsimd_state))

/*
 * (flags & SVE_PT_REGS_MASK) == SVE_PT_REGS_SVE हाल:
 *
 * The payload starts at offset SVE_PT_SVE_OFFSET, and is of size
 * SVE_PT_SVE_SIZE(vq, flags).
 *
 * Additional macros describe the contents and layout of the payload.
 * For each, SVE_PT_SVE_x_OFFSET(args) is the start offset relative to
 * the start of काष्ठा user_sve_header, and SVE_PT_SVE_x_SIZE(args) is
 * the size in bytes:
 *
 *	x	type				description
 *	-	----				-----------
 *	ZREGS		\
 *	ZREG		|
 *	PREGS		| refer to <यंत्र/sigcontext.h>
 *	PREG		|
 *	FFR		/
 *
 *	FPSR	uपूर्णांक32_t			FPSR
 *	FPCR	uपूर्णांक32_t			FPCR
 *
 * Additional data might be appended in the future.
 *
 * The Z-, P- and FFR रेजिस्टरs are represented in memory in an endianness-
 * invariant layout which dअगरfers from the layout used क्रम the FPSIMD
 * V-रेजिस्टरs on big-endian प्रणालीs: see sigcontext.h क्रम more explanation.
 */

#घोषणा SVE_PT_SVE_ZREG_SIZE(vq)	__SVE_ZREG_SIZE(vq)
#घोषणा SVE_PT_SVE_PREG_SIZE(vq)	__SVE_PREG_SIZE(vq)
#घोषणा SVE_PT_SVE_FFR_SIZE(vq)		__SVE_FFR_SIZE(vq)
#घोषणा SVE_PT_SVE_FPSR_SIZE		माप(__u32)
#घोषणा SVE_PT_SVE_FPCR_SIZE		माप(__u32)

#घोषणा SVE_PT_SVE_OFFSET		SVE_PT_REGS_OFFSET

#घोषणा SVE_PT_SVE_ZREGS_OFFSET \
	(SVE_PT_REGS_OFFSET + __SVE_ZREGS_OFFSET)
#घोषणा SVE_PT_SVE_ZREG_OFFSET(vq, n) \
	(SVE_PT_REGS_OFFSET + __SVE_ZREG_OFFSET(vq, n))
#घोषणा SVE_PT_SVE_ZREGS_SIZE(vq) \
	(SVE_PT_SVE_ZREG_OFFSET(vq, __SVE_NUM_ZREGS) - SVE_PT_SVE_ZREGS_OFFSET)

#घोषणा SVE_PT_SVE_PREGS_OFFSET(vq) \
	(SVE_PT_REGS_OFFSET + __SVE_PREGS_OFFSET(vq))
#घोषणा SVE_PT_SVE_PREG_OFFSET(vq, n) \
	(SVE_PT_REGS_OFFSET + __SVE_PREG_OFFSET(vq, n))
#घोषणा SVE_PT_SVE_PREGS_SIZE(vq) \
	(SVE_PT_SVE_PREG_OFFSET(vq, __SVE_NUM_PREGS) - \
		SVE_PT_SVE_PREGS_OFFSET(vq))

#घोषणा SVE_PT_SVE_FFR_OFFSET(vq) \
	(SVE_PT_REGS_OFFSET + __SVE_FFR_OFFSET(vq))

#घोषणा SVE_PT_SVE_FPSR_OFFSET(vq)				\
	((SVE_PT_SVE_FFR_OFFSET(vq) + SVE_PT_SVE_FFR_SIZE(vq) +	\
			(__SVE_VQ_BYTES - 1))			\
		/ __SVE_VQ_BYTES * __SVE_VQ_BYTES)
#घोषणा SVE_PT_SVE_FPCR_OFFSET(vq) \
	(SVE_PT_SVE_FPSR_OFFSET(vq) + SVE_PT_SVE_FPSR_SIZE)

/*
 * Any future extension appended after FPCR must be aligned to the next
 * 128-bit boundary.
 */

#घोषणा SVE_PT_SVE_SIZE(vq, flags)					\
	((SVE_PT_SVE_FPCR_OFFSET(vq) + SVE_PT_SVE_FPCR_SIZE		\
			- SVE_PT_SVE_OFFSET + (__SVE_VQ_BYTES - 1))	\
		/ __SVE_VQ_BYTES * __SVE_VQ_BYTES)

#घोषणा SVE_PT_SIZE(vq, flags)						\
	 (((flags) & SVE_PT_REGS_MASK) == SVE_PT_REGS_SVE ?		\
		  SVE_PT_SVE_OFFSET + SVE_PT_SVE_SIZE(vq, flags)	\
		: SVE_PT_FPSIMD_OFFSET + SVE_PT_FPSIMD_SIZE(vq, flags))

/* poपूर्णांकer authentication masks (NT_ARM_PAC_MASK) */

काष्ठा user_pac_mask अणु
	__u64		data_mask;
	__u64		insn_mask;
पूर्ण;

/* poपूर्णांकer authentication keys (NT_ARM_PACA_KEYS, NT_ARM_PACG_KEYS) */

काष्ठा user_pac_address_keys अणु
	__uपूर्णांक128_t	apiakey;
	__uपूर्णांक128_t	apibkey;
	__uपूर्णांक128_t	apdakey;
	__uपूर्णांक128_t	apdbkey;
पूर्ण;

काष्ठा user_pac_generic_keys अणु
	__uपूर्णांक128_t	apgakey;
पूर्ण;

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _UAPI__ASM_PTRACE_H */
