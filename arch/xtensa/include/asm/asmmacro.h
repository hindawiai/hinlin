<शैली गुरु>
/*
 * include/यंत्र-xtensa/यंत्रmacro.h
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2005 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_ASMMACRO_H
#घोषणा _XTENSA_ASMMACRO_H

#समावेश <यंत्र/core.h>

/*
 * Some little helpers क्रम loops. Use zero-overhead-loops
 * where applicable and अगर supported by the processor.
 *
 * __loopi ar, at, size, inc
 *         ar	रेजिस्टर initialized with the start address
 *	   at	scratch रेजिस्टर used by macro
 *	   size	size immediate value
 *	   inc	increment
 *
 * __loops ar, as, at, inc_log2[, mask_log2][, cond][, ncond]
 *	   ar	रेजिस्टर initialized with the start address
 *	   as	रेजिस्टर initialized with the size
 *	   at	scratch रेजिस्टर use by macro
 *	   inc_log2	increment [in log2]
 *	   mask_log2	mask [in log2]
 *	   cond		true condition (used in loop'cond')
 *	   ncond	false condition (used in b'ncond')
 *
 * __loop  as
 *	   restart loop. 'as' रेजिस्टर must not have been modअगरied!
 *
 * __endla ar, as, incr
 *	   ar	start address (modअगरied)
 *	   as	scratch रेजिस्टर used by __loops/__loopi macros or
 *		end address used by __loopt macro
 *	   inc	increment
 */

/*
 * loop क्रम given size as immediate
 */

	.macro	__loopi ar, at, size, incr

#अगर XCHAL_HAVE_LOOPS
		movi	\चt, ((\size + \incr - 1) / (\incr))
		loop	\चt, 99f
#अन्यथा
		addi	\चt, \चr, \size
		98:
#पूर्ण_अगर

	.endm

/*
 * loop क्रम given size in रेजिस्टर
 */

	.macro	__loops	ar, as, at, incr_log2, mask_log2, cond, ncond

#अगर XCHAL_HAVE_LOOPS
		.अगरgt \incr_log2 - 1
			addi	\चt, \चs, (1 << \incr_log2) - 1
			.अगरnc \mask_log2,
				extui	\चt, \चt, \incr_log2, \mask_log2
			.अन्यथा
				srli	\चt, \चt, \incr_log2
			.endअगर
		.endअगर
		loop\cond	\चt, 99f
#अन्यथा
		.अगरnc \mask_log2,
			extui	\चt, \चs, \incr_log2, \mask_log2
		.अन्यथा
			.अगरnc \नcond,
				srli	\चt, \चs, \incr_log2
			.endअगर
		.endअगर
		.अगरnc \नcond,
			b\नcond	\चt, 99f

		.endअगर
		.अगरnc \mask_log2,
			slli	\चt, \चt, \incr_log2
			add	\चt, \चr, \चt
		.अन्यथा
			add	\चt, \चr, \चs
		.endअगर
#पूर्ण_अगर
		98:

	.endm

/*
 * loop from ar to as
 */

	.macro	__loopt	ar, as, at, incr_log2

#अगर XCHAL_HAVE_LOOPS
		sub	\चt, \चs, \चr
		.अगरgt	\incr_log2 - 1
			addi	\चt, \चt, (1 << \incr_log2) - 1
			srli	\चt, \चt, \incr_log2
		.endअगर
		loop	\चt, 99f
#अन्यथा
		98:
#पूर्ण_अगर

	.endm

/*
 * restart loop. रेजिस्टरs must be unchanged
 */

	.macro	__loop	as

#अगर XCHAL_HAVE_LOOPS
		loop	\चs, 99f
#अन्यथा
		98:
#पूर्ण_अगर

	.endm

/*
 * end of loop with no increment of the address.
 */

	.macro	__endl	ar, as
#अगर !XCHAL_HAVE_LOOPS
		bltu	\चr, \चs, 98b
#पूर्ण_अगर
		99:
	.endm

/*
 * end of loop with increment of the address.
 */

	.macro	__endla	ar, as, incr
		addi	\चr, \चr, \incr
		__endl	\चr \चs
	.endm

/* Load or store inकाष्ठाions that may cause exceptions use the EX macro. */

#घोषणा EX(handler)				\
	.section __ex_table, "a";		\
	.word	97f, handler;			\
	.previous				\
97:


/*
 * Extract unaligned word that is split between two रेजिस्टरs w0 and w1
 * पूर्णांकo r regardless of machine endianness. SAR must be loaded with the
 * starting bit of the word (see __ssa8).
 */

	.macro __src_b	r, w0, w1
#अगर_घोषित __XTENSA_EB__
		src	\ल, \w0, \w1
#अन्यथा
		src	\ल, \w1, \w0
#पूर्ण_अगर
	.endm

/*
 * Load 2 lowest address bits of r पूर्णांकo SAR क्रम __src_b to extract unaligned
 * word starting at r from two रेजिस्टरs loaded from consecutive aligned
 * addresses covering r regardless of machine endianness.
 *
 *      r   0   1   2   3
 * LE SAR   0   8  16  24
 * BE SAR  32  24  16   8
 */

	.macro __ssa8	r
#अगर_घोषित __XTENSA_EB__
		ssa8b	\ल
#अन्यथा
		ssa8l	\ल
#पूर्ण_अगर
	.endm

#घोषणा XTENSA_STACK_ALIGNMENT		16

#अगर defined(__XTENSA_WINDOWED_ABI__)
#घोषणा XTENSA_FRAME_SIZE_RESERVE	16
#घोषणा XTENSA_SPILL_STACK_RESERVE	32

#घोषणा abi_entry(frame_size) \
	entry sp, (XTENSA_FRAME_SIZE_RESERVE + \
		   (((frame_size) + XTENSA_STACK_ALIGNMENT - 1) & \
		    -XTENSA_STACK_ALIGNMENT))
#घोषणा abi_entry_शेष abi_entry(0)

#घोषणा abi_ret(frame_size) retw
#घोषणा abi_ret_शेष retw

#या_अगर defined(__XTENSA_CALL0_ABI__)

#घोषणा XTENSA_SPILL_STACK_RESERVE	0

#घोषणा abi_entry(frame_size) __abi_entry (frame_size)

	.macro	__abi_entry frame_size
	.अगरgt \पrame_size
	addi sp, sp, -(((\पrame_size) + XTENSA_STACK_ALIGNMENT - 1) & \
		       -XTENSA_STACK_ALIGNMENT)
	.endअगर
	.endm

#घोषणा abi_entry_शेष

#घोषणा abi_ret(frame_size) __abi_ret (frame_size)

	.macro	__abi_ret frame_size
	.अगरgt \पrame_size
	addi sp, sp, (((\पrame_size) + XTENSA_STACK_ALIGNMENT - 1) & \
		      -XTENSA_STACK_ALIGNMENT)
	.endअगर
	ret
	.endm

#घोषणा abi_ret_शेष ret

#अन्यथा
#त्रुटि Unsupported Xtensa ABI
#पूर्ण_अगर

#घोषणा __XTENSA_HANDLER	.section ".exception.text", "ax"

#पूर्ण_अगर /* _XTENSA_ASMMACRO_H */
