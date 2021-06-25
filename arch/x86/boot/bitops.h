<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* -*- linux-c -*- ------------------------------------------------------- *
 *
 *   Copyright (C) 1991, 1992 Linus Torvalds
 *   Copyright 2007 rPath, Inc. - All Rights Reserved
 *
 * ----------------------------------------------------------------------- */

/*
 * Very simple bitops क्रम the boot code.
 */

#अगर_अघोषित BOOT_BITOPS_H
#घोषणा BOOT_BITOPS_H
#घोषणा _LINUX_BITOPS_H		/* Inhibit inclusion of <linux/bitops.h> */

#समावेश <linux/types.h>
#समावेश <यंत्र/यंत्र.h>

अटल अंतरभूत bool स्थिरant_test_bit(पूर्णांक nr, स्थिर व्योम *addr)
अणु
	स्थिर u32 *p = (स्थिर u32 *)addr;
	वापस ((1UL << (nr & 31)) & (p[nr >> 5])) != 0;
पूर्ण
अटल अंतरभूत bool variable_test_bit(पूर्णांक nr, स्थिर व्योम *addr)
अणु
	bool v;
	स्थिर u32 *p = (स्थिर u32 *)addr;

	यंत्र("btl %2,%1" CC_SET(c) : CC_OUT(c) (v) : "m" (*p), "Ir" (nr));
	वापस v;
पूर्ण

#घोषणा test_bit(nr,addr) \
(__builtin_स्थिरant_p(nr) ? \
 स्थिरant_test_bit((nr),(addr)) : \
 variable_test_bit((nr),(addr)))

अटल अंतरभूत व्योम set_bit(पूर्णांक nr, व्योम *addr)
अणु
	यंत्र("btsl %1,%0" : "+m" (*(u32 *)addr) : "Ir" (nr));
पूर्ण

#पूर्ण_अगर /* BOOT_BITOPS_H */
