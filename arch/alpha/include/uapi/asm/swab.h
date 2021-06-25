<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ALPHA_SWAB_H
#घोषणा _ALPHA_SWAB_H

#समावेश <linux/types.h>
#समावेश <linux/compiler.h>
#समावेश <यंत्र/compiler.h>

#अगर_घोषित __GNUC__

अटल अंतरभूत __attribute_स्थिर__ __u32 __arch_swab32(__u32 x)
अणु
	/*
	 * Unक्रमtunately, we can't use the 6 inकाष्ठाion sequence
	 * on ev6 since the latency of the UNPKBW is 3, which is
	 * pretty hard to hide.  Just in हाल a future implementation
	 * has a lower latency, here's the sequence (also by Mike Burrows)
	 *
	 * UNPKBW a0, v0       v0: 00AA00BB00CC00DD
	 * SLL v0, 24, a0      a0: BB00CC00DD000000
	 * BIS v0, a0, a0      a0: BBAACCBBDDCC00DD
	 * EXTWL a0, 6, v0     v0: 000000000000BBAA
	 * ZAP a0, 0xf3, a0    a0: 00000000DDCC0000
	 * ADDL a0, v0, v0     v0: ssssssssDDCCBBAA
	 */

	__u64 t0, t1, t2, t3;

	t0 = __kernel_inslh(x, 7);	/* t0 : 0000000000AABBCC */
	t1 = __kernel_inswl(x, 3);	/* t1 : 000000CCDD000000 */
	t1 |= t0;			/* t1 : 000000CCDDAABBCC */
	t2 = t1 >> 16;			/* t2 : 0000000000CCDDAA */
	t0 = t1 & 0xFF00FF00;		/* t0 : 00000000DD00BB00 */
	t3 = t2 & 0x00FF00FF;		/* t3 : 0000000000CC00AA */
	t1 = t0 + t3;			/* t1 : ssssssssDDCCBBAA */

	वापस t1;
पूर्ण
#घोषणा __arch_swab32 __arch_swab32

#पूर्ण_अगर /* __GNUC__ */

#पूर्ण_अगर /* _ALPHA_SWAB_H */
