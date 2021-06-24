<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ASM_IA64_SWAB_H
#घोषणा _ASM_IA64_SWAB_H

/*
 * Modअगरied 1998, 1999
 *	David Mosberger-Tang <davidm@hpl.hp.com>, Hewlett-Packard Co.
 */

#समावेश <linux/types.h>
#समावेश <यंत्र/पूर्णांकrinsics.h>
#समावेश <linux/compiler.h>

अटल __अंतरभूत__ __attribute_स्थिर__ __u64 __arch_swab64(__u64 x)
अणु
	__u64 result;

	result = ia64_mux1(x, ia64_mux1_rev);
	वापस result;
पूर्ण
#घोषणा __arch_swab64 __arch_swab64

अटल __अंतरभूत__ __attribute_स्थिर__ __u32 __arch_swab32(__u32 x)
अणु
	वापस __arch_swab64(x) >> 32;
पूर्ण
#घोषणा __arch_swab32 __arch_swab32

अटल __अंतरभूत__ __attribute_स्थिर__ __u16 __arch_swab16(__u16 x)
अणु
	वापस __arch_swab64(x) >> 48;
पूर्ण
#घोषणा __arch_swab16 __arch_swab16

#पूर्ण_अगर /* _ASM_IA64_SWAB_H */
