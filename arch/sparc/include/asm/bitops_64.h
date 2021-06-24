<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * bitops.h: Bit string operations on the V9.
 *
 * Copyright 1996, 1997 David S. Miller (davem@caip.rutgers.edu)
 */

#अगर_अघोषित _SPARC64_BITOPS_H
#घोषणा _SPARC64_BITOPS_H

#अगर_अघोषित _LINUX_BITOPS_H
#त्रुटि only <linux/bitops.h> can be included directly
#पूर्ण_अगर

#समावेश <linux/compiler.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/barrier.h>

पूर्णांक test_and_set_bit(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr);
पूर्णांक test_and_clear_bit(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr);
पूर्णांक test_and_change_bit(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr);
व्योम set_bit(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr);
व्योम clear_bit(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr);
व्योम change_bit(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr);

पूर्णांक fls(अचिन्हित पूर्णांक word);
पूर्णांक __fls(अचिन्हित दीर्घ word);

#समावेश <यंत्र-generic/bitops/non-atomic.h>

#समावेश <यंत्र-generic/bitops/fls64.h>

#अगर_घोषित __KERNEL__

पूर्णांक ffs(पूर्णांक x);
अचिन्हित दीर्घ __ffs(अचिन्हित दीर्घ);

#समावेश <यंत्र-generic/bitops/ffz.h>
#समावेश <यंत्र-generic/bitops/sched.h>

/*
 * hweightN: वापसs the hamming weight (i.e. the number
 * of bits set) of a N-bit word
 */

अचिन्हित दीर्घ __arch_hweight64(__u64 w);
अचिन्हित पूर्णांक __arch_hweight32(अचिन्हित पूर्णांक w);
अचिन्हित पूर्णांक __arch_hweight16(अचिन्हित पूर्णांक w);
अचिन्हित पूर्णांक __arch_hweight8(अचिन्हित पूर्णांक w);

#समावेश <यंत्र-generic/bitops/स्थिर_hweight.h>
#समावेश <यंत्र-generic/bitops/lock.h>
#पूर्ण_अगर /* __KERNEL__ */

#समावेश <यंत्र-generic/bitops/find.h>

#अगर_घोषित __KERNEL__

#समावेश <यंत्र-generic/bitops/le.h>

#समावेश <यंत्र-generic/bitops/ext2-atomic-setbit.h>

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* defined(_SPARC64_BITOPS_H) */
