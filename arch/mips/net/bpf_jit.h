<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Just-In-Time compiler क्रम BPF filters on MIPS
 *
 * Copyright (c) 2014 Imagination Technologies Ltd.
 * Author: Markos Chandras <markos.chandras@imgtec.com>
 */

#अगर_अघोषित BPF_JIT_MIPS_OP_H
#घोषणा BPF_JIT_MIPS_OP_H

/* Registers used by JIT */
#घोषणा MIPS_R_ZERO	0
#घोषणा MIPS_R_V0	2
#घोषणा MIPS_R_A0	4
#घोषणा MIPS_R_A1	5
#घोषणा MIPS_R_T4	12
#घोषणा MIPS_R_T5	13
#घोषणा MIPS_R_T6	14
#घोषणा MIPS_R_T7	15
#घोषणा MIPS_R_S0	16
#घोषणा MIPS_R_S1	17
#घोषणा MIPS_R_S2	18
#घोषणा MIPS_R_S3	19
#घोषणा MIPS_R_S4	20
#घोषणा MIPS_R_S5	21
#घोषणा MIPS_R_S6	22
#घोषणा MIPS_R_S7	23
#घोषणा MIPS_R_SP	29
#घोषणा MIPS_R_RA	31

/* Conditional codes */
#घोषणा MIPS_COND_EQ	0x1
#घोषणा MIPS_COND_GE	(0x1 << 1)
#घोषणा MIPS_COND_GT	(0x1 << 2)
#घोषणा MIPS_COND_NE	(0x1 << 3)
#घोषणा MIPS_COND_ALL	(0x1 << 4)
/* Conditionals on X रेजिस्टर or K immediate */
#घोषणा MIPS_COND_X	(0x1 << 5)
#घोषणा MIPS_COND_K	(0x1 << 6)

#घोषणा r_ret	MIPS_R_V0

/*
 * Use 2 scratch रेजिस्टरs to aव्योम pipeline पूर्णांकerlocks.
 * There is no overhead during epilogue and prologue since
 * any of the $s0-$s6 रेजिस्टरs will only be preserved अगर
 * they are going to actually be used.
 */
#घोषणा r_skb_hl	MIPS_R_S0 /* skb header length */
#घोषणा r_skb_data	MIPS_R_S1 /* skb actual data */
#घोषणा r_off		MIPS_R_S2
#घोषणा r_A		MIPS_R_S3
#घोषणा r_X		MIPS_R_S4
#घोषणा r_skb		MIPS_R_S5
#घोषणा r_M		MIPS_R_S6
#घोषणा r_skb_len	MIPS_R_S7
#घोषणा r_s0		MIPS_R_T4 /* scratch reg 1 */
#घोषणा r_s1		MIPS_R_T5 /* scratch reg 2 */
#घोषणा r_पंचांगp_imm	MIPS_R_T6 /* No need to preserve this */
#घोषणा r_पंचांगp		MIPS_R_T7 /* No need to preserve this */
#घोषणा r_zero		MIPS_R_ZERO
#घोषणा r_sp		MIPS_R_SP
#घोषणा r_ra		MIPS_R_RA

#अगर_अघोषित __ASSEMBLY__

/* Declare ASM helpers */

#घोषणा DECLARE_LOAD_FUNC(func) \
	बाह्य u8 func(अचिन्हित दीर्घ *skb, पूर्णांक offset); \
	बाह्य u8 func##_negative(अचिन्हित दीर्घ *skb, पूर्णांक offset); \
	बाह्य u8 func##_positive(अचिन्हित दीर्घ *skb, पूर्णांक offset)

DECLARE_LOAD_FUNC(sk_load_word);
DECLARE_LOAD_FUNC(sk_load_half);
DECLARE_LOAD_FUNC(sk_load_byte);

#पूर्ण_अगर

#पूर्ण_अगर /* BPF_JIT_MIPS_OP_H */
