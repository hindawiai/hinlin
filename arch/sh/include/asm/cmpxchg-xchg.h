<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_CMPXCHG_XCHG_H
#घोषणा __ASM_SH_CMPXCHG_XCHG_H

/*
 * Copyright (C) 2016 Red Hat, Inc.
 * Author: Michael S. Tsirkin <mst@redhat.com>
 */
#समावेश <linux/bits.h>
#समावेश <linux/compiler.h>
#समावेश <यंत्र/byteorder.h>

/*
 * Portable implementations of 1 and 2 byte xchg using a 4 byte cmpxchg.
 * Note: this header isn't self-contained: beक्रमe including it, __cmpxchg_u32
 * must be defined first.
 */
अटल अंतरभूत u32 __xchg_cmpxchg(अस्थिर व्योम *ptr, u32 x, पूर्णांक size)
अणु
	पूर्णांक off = (अचिन्हित दीर्घ)ptr % माप(u32);
	अस्थिर u32 *p = ptr - off;
#अगर_घोषित __BIG_ENDIAN
	पूर्णांक bitoff = (माप(u32) - size - off) * BITS_PER_BYTE;
#अन्यथा
	पूर्णांक bitoff = off * BITS_PER_BYTE;
#पूर्ण_अगर
	u32 biपंचांगask = ((0x1 << size * BITS_PER_BYTE) - 1) << bitoff;
	u32 oldv, newv;
	u32 ret;

	करो अणु
		oldv = READ_ONCE(*p);
		ret = (oldv & biपंचांगask) >> bitoff;
		newv = (oldv & ~biपंचांगask) | (x << bitoff);
	पूर्ण जबतक (__cmpxchg_u32(p, oldv, newv) != oldv);

	वापस ret;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ xchg_u16(अस्थिर u16 *m, अचिन्हित दीर्घ val)
अणु
	वापस __xchg_cmpxchg(m, val, माप *m);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ xchg_u8(अस्थिर u8 *m, अचिन्हित दीर्घ val)
अणु
	वापस __xchg_cmpxchg(m, val, माप *m);
पूर्ण

#पूर्ण_अगर /* __ASM_SH_CMPXCHG_XCHG_H */
