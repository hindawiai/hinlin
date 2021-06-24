<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
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
#अगर_अघोषित _UAPI__ASM_SIGCONTEXT_H
#घोषणा _UAPI__ASM_SIGCONTEXT_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/types.h>

/*
 * Signal context काष्ठाure - contains all info to करो with the state
 * beक्रमe the संकेत handler was invoked.
 */
काष्ठा sigcontext अणु
	__u64 fault_address;
	/* AArch64 रेजिस्टरs */
	__u64 regs[31];
	__u64 sp;
	__u64 pc;
	__u64 pstate;
	/* 4K reserved क्रम FP/SIMD state and future expansion */
	__u8 __reserved[4096] __attribute__((__aligned__(16)));
पूर्ण;

/*
 * Allocation of __reserved[]:
 * (Note: records करो not necessarily occur in the order shown here.)
 *
 *	size		description
 *
 *	0x210		fpsimd_context
 *	 0x10		esr_context
 *	0x8a0		sve_context (vl <= 64) (optional)
 *	 0x20		extra_context (optional)
 *	 0x10		terminator (null _aarch64_ctx)
 *
 *	0x510		(reserved क्रम future allocation)
 *
 * New records that can exceed this space need to be opt-in क्रम userspace, so
 * that an expanded संकेत frame is not generated unexpectedly.  The mechanism
 * क्रम opting in will depend on the extension that generates each new record.
 * The above table करोcuments the maximum set and sizes of records than can be
 * generated when userspace करोes not opt in क्रम any such extension.
 */

/*
 * Header to be used at the beginning of काष्ठाures extending the user
 * context. Such काष्ठाures must be placed after the rt_sigframe on the stack
 * and be 16-byte aligned. The last काष्ठाure must be a dummy one with the
 * magic and size set to 0.
 */
काष्ठा _aarch64_ctx अणु
	__u32 magic;
	__u32 size;
पूर्ण;

#घोषणा FPSIMD_MAGIC	0x46508001

काष्ठा fpsimd_context अणु
	काष्ठा _aarch64_ctx head;
	__u32 fpsr;
	__u32 fpcr;
	__uपूर्णांक128_t vregs[32];
पूर्ण;

/*
 * Note: similarly to all other पूर्णांकeger fields, each V-रेजिस्टर is stored in an
 * endianness-dependent क्रमmat, with the byte at offset i from the start of the
 * in-memory representation of the रेजिस्टर value containing
 *
 *    bits [(7 + 8 * i) : (8 * i)] of the रेजिस्टर on little-endian hosts; or
 *    bits [(127 - 8 * i) : (120 - 8 * i)] on big-endian hosts.
 */

/* ESR_EL1 context */
#घोषणा ESR_MAGIC	0x45535201

काष्ठा esr_context अणु
	काष्ठा _aarch64_ctx head;
	__u64 esr;
पूर्ण;

/*
 * extra_context: describes extra space in the संकेत frame क्रम
 * additional काष्ठाures that करोn't fit in sigcontext.__reserved[].
 *
 * Note:
 *
 * 1) fpsimd_context, esr_context and extra_context must be placed in
 * sigcontext.__reserved[] अगर present.  They cannot be placed in the
 * extra space.  Any other record can be placed either in the extra
 * space or in sigcontext.__reserved[], unless otherwise specअगरied in
 * this file.
 *
 * 2) There must not be more than one extra_context.
 *
 * 3) If extra_context is present, it must be followed immediately in
 * sigcontext.__reserved[] by the terminating null _aarch64_ctx.
 *
 * 4) The extra space to which datap poपूर्णांकs must start at the first
 * 16-byte aligned address immediately after the terminating null
 * _aarch64_ctx that follows the extra_context काष्ठाure in
 * __reserved[].  The extra space may overrun the end of __reserved[],
 * as indicated by a sufficiently large value क्रम the size field.
 *
 * 5) The extra space must itself be terminated with a null
 * _aarch64_ctx.
 */
#घोषणा EXTRA_MAGIC	0x45585401

काष्ठा extra_context अणु
	काष्ठा _aarch64_ctx head;
	__u64 datap; /* 16-byte aligned poपूर्णांकer to extra space cast to __u64 */
	__u32 size; /* size in bytes of the extra space */
	__u32 __reserved[3];
पूर्ण;

#घोषणा SVE_MAGIC	0x53564501

काष्ठा sve_context अणु
	काष्ठा _aarch64_ctx head;
	__u16 vl;
	__u16 __reserved[3];
पूर्ण;

#पूर्ण_अगर /* !__ASSEMBLY__ */

#समावेश <यंत्र/sve_context.h>

/*
 * The SVE architecture leaves space क्रम future expansion of the
 * vector length beyond its initial architectural limit of 2048 bits
 * (16 quadwords).
 *
 * See linux/Documentation/arm64/sve.rst क्रम a description of the VL/VQ
 * terminology.
 */
#घोषणा SVE_VQ_BYTES		__SVE_VQ_BYTES	/* bytes per quadword */

#घोषणा SVE_VQ_MIN		__SVE_VQ_MIN
#घोषणा SVE_VQ_MAX		__SVE_VQ_MAX

#घोषणा SVE_VL_MIN		__SVE_VL_MIN
#घोषणा SVE_VL_MAX		__SVE_VL_MAX

#घोषणा SVE_NUM_ZREGS		__SVE_NUM_ZREGS
#घोषणा SVE_NUM_PREGS		__SVE_NUM_PREGS

#घोषणा sve_vl_valid(vl)	__sve_vl_valid(vl)
#घोषणा sve_vq_from_vl(vl)	__sve_vq_from_vl(vl)
#घोषणा sve_vl_from_vq(vq)	__sve_vl_from_vq(vq)

/*
 * If the SVE रेजिस्टरs are currently live क्रम the thपढ़ो at संकेत delivery,
 * sve_context.head.size >=
 *	SVE_SIG_CONTEXT_SIZE(sve_vq_from_vl(sve_context.vl))
 * and the रेजिस्टर data may be accessed using the SVE_SIG_*() macros.
 *
 * If sve_context.head.size <
 *	SVE_SIG_CONTEXT_SIZE(sve_vq_from_vl(sve_context.vl)),
 * the SVE रेजिस्टरs were not live क्रम the thपढ़ो and no रेजिस्टर data
 * is included: in this हाल, the SVE_SIG_*() macros should not be
 * used except क्रम this check.
 *
 * The same convention applies when वापसing from a संकेत: a caller
 * will need to हटाओ or resize the sve_context block अगर it wants to
 * make the SVE रेजिस्टरs live when they were previously non-live or
 * vice-versa.  This may require the caller to allocate fresh
 * memory and/or move other context blocks in the संकेत frame.
 *
 * Changing the vector length during संकेत वापस is not permitted:
 * sve_context.vl must equal the thपढ़ो's current vector length when
 * करोing a sigवापस.
 *
 *
 * Note: क्रम all these macros, the "vq" argument denotes the SVE
 * vector length in quadwords (i.e., units of 128 bits).
 *
 * The correct way to obtain vq is to use sve_vq_from_vl(vl).  The
 * result is valid अगर and only अगर sve_vl_valid(vl) is true.  This is
 * guaranteed क्रम a काष्ठा sve_context written by the kernel.
 *
 *
 * Additional macros describe the contents and layout of the payload.
 * For each, SVE_SIG_x_OFFSET(args) is the start offset relative to
 * the start of काष्ठा sve_context, and SVE_SIG_x_SIZE(args) is the
 * size in bytes:
 *
 *	x	type				description
 *	-	----				-----------
 *	REGS					the entire SVE context
 *
 *	ZREGS	__uपूर्णांक128_t[SVE_NUM_ZREGS][vq]	all Z-रेजिस्टरs
 *	ZREG	__uपूर्णांक128_t[vq]			inभागidual Z-रेजिस्टर Zn
 *
 *	PREGS	uपूर्णांक16_t[SVE_NUM_PREGS][vq]	all P-रेजिस्टरs
 *	PREG	uपूर्णांक16_t[vq]			inभागidual P-रेजिस्टर Pn
 *
 *	FFR	uपूर्णांक16_t[vq]			first-fault status रेजिस्टर
 *
 * Additional data might be appended in the future.
 *
 * Unlike vregs[] in fpsimd_context, each SVE scalable रेजिस्टर (Z-, P- or FFR)
 * is encoded in memory in an endianness-invariant क्रमmat, with the byte at
 * offset i from the start of the in-memory representation containing bits
 * [(7 + 8 * i) : (8 * i)] of the रेजिस्टर value.
 */

#घोषणा SVE_SIG_ZREG_SIZE(vq)	__SVE_ZREG_SIZE(vq)
#घोषणा SVE_SIG_PREG_SIZE(vq)	__SVE_PREG_SIZE(vq)
#घोषणा SVE_SIG_FFR_SIZE(vq)	__SVE_FFR_SIZE(vq)

#घोषणा SVE_SIG_REGS_OFFSET					\
	((माप(काष्ठा sve_context) + (__SVE_VQ_BYTES - 1))	\
		/ __SVE_VQ_BYTES * __SVE_VQ_BYTES)

#घोषणा SVE_SIG_ZREGS_OFFSET \
		(SVE_SIG_REGS_OFFSET + __SVE_ZREGS_OFFSET)
#घोषणा SVE_SIG_ZREG_OFFSET(vq, n) \
		(SVE_SIG_REGS_OFFSET + __SVE_ZREG_OFFSET(vq, n))
#घोषणा SVE_SIG_ZREGS_SIZE(vq) __SVE_ZREGS_SIZE(vq)

#घोषणा SVE_SIG_PREGS_OFFSET(vq) \
		(SVE_SIG_REGS_OFFSET + __SVE_PREGS_OFFSET(vq))
#घोषणा SVE_SIG_PREG_OFFSET(vq, n) \
		(SVE_SIG_REGS_OFFSET + __SVE_PREG_OFFSET(vq, n))
#घोषणा SVE_SIG_PREGS_SIZE(vq) __SVE_PREGS_SIZE(vq)

#घोषणा SVE_SIG_FFR_OFFSET(vq) \
		(SVE_SIG_REGS_OFFSET + __SVE_FFR_OFFSET(vq))

#घोषणा SVE_SIG_REGS_SIZE(vq) \
		(__SVE_FFR_OFFSET(vq) + __SVE_FFR_SIZE(vq))

#घोषणा SVE_SIG_CONTEXT_SIZE(vq) \
		(SVE_SIG_REGS_OFFSET + SVE_SIG_REGS_SIZE(vq))

#पूर्ण_अगर /* _UAPI__ASM_SIGCONTEXT_H */
