<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _M68K_SWAB_H
#घोषणा _M68K_SWAB_H

#समावेश <linux/types.h>
#समावेश <linux/compiler.h>

#घोषणा __SWAB_64_THRU_32__

#अगर defined (__mcfisaaplus__) || defined (__mcfisac__)
अटल अंतरभूत __attribute_स्थिर__ __u32 __arch_swab32(__u32 val)
अणु
	__यंत्र__("byterev %0" : "=d" (val) : "0" (val));
	वापस val;
पूर्ण

#घोषणा __arch_swab32 __arch_swab32
#या_अगर !defined(__mcoldfire__)

अटल अंतरभूत __attribute_स्थिर__ __u32 __arch_swab32(__u32 val)
अणु
	__यंत्र__("rolw #8,%0; swap %0; rolw #8,%0" : "=d" (val) : "0" (val));
	वापस val;
पूर्ण
#घोषणा __arch_swab32 __arch_swab32
#पूर्ण_अगर

#पूर्ण_अगर /* _M68K_SWAB_H */
