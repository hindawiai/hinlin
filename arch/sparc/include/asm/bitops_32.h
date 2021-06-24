<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * bitops.h: Bit string operations on the Sparc.
 *
 * Copyright 1995 David S. Miller (davem@caip.rutgers.edu)
 * Copyright 1996 Eddie C. Dost   (ecd@skynet.be)
 * Copyright 2001 Anton Blanअक्षरd (anton@samba.org)
 */

#अगर_अघोषित _SPARC_BITOPS_H
#घोषणा _SPARC_BITOPS_H

#समावेश <linux/compiler.h>
#समावेश <यंत्र/byteorder.h>

#अगर_घोषित __KERNEL__

#अगर_अघोषित _LINUX_BITOPS_H
#त्रुटि only <linux/bitops.h> can be included directly
#पूर्ण_अगर

अचिन्हित दीर्घ ___set_bit(अचिन्हित दीर्घ *addr, अचिन्हित दीर्घ mask);
अचिन्हित दीर्घ ___clear_bit(अचिन्हित दीर्घ *addr, अचिन्हित दीर्घ mask);
अचिन्हित दीर्घ ___change_bit(अचिन्हित दीर्घ *addr, अचिन्हित दीर्घ mask);

/*
 * Set bit 'nr' in 32-bit quantity at address 'addr' where bit '0'
 * is in the highest of the four bytes and bit '31' is the high bit
 * within the first byte. Sparc is BIG-Endian. Unless noted otherwise
 * all bit-ops वापस 0 अगर bit was previously clear and != 0 otherwise.
 */
अटल अंतरभूत पूर्णांक test_and_set_bit(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अचिन्हित दीर्घ *ADDR, mask;

	ADDR = ((अचिन्हित दीर्घ *) addr) + (nr >> 5);
	mask = 1 << (nr & 31);

	वापस ___set_bit(ADDR, mask) != 0;
पूर्ण

अटल अंतरभूत व्योम set_bit(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अचिन्हित दीर्घ *ADDR, mask;

	ADDR = ((अचिन्हित दीर्घ *) addr) + (nr >> 5);
	mask = 1 << (nr & 31);

	(व्योम) ___set_bit(ADDR, mask);
पूर्ण

अटल अंतरभूत पूर्णांक test_and_clear_bit(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अचिन्हित दीर्घ *ADDR, mask;

	ADDR = ((अचिन्हित दीर्घ *) addr) + (nr >> 5);
	mask = 1 << (nr & 31);

	वापस ___clear_bit(ADDR, mask) != 0;
पूर्ण

अटल अंतरभूत व्योम clear_bit(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अचिन्हित दीर्घ *ADDR, mask;

	ADDR = ((अचिन्हित दीर्घ *) addr) + (nr >> 5);
	mask = 1 << (nr & 31);

	(व्योम) ___clear_bit(ADDR, mask);
पूर्ण

अटल अंतरभूत पूर्णांक test_and_change_bit(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अचिन्हित दीर्घ *ADDR, mask;

	ADDR = ((अचिन्हित दीर्घ *) addr) + (nr >> 5);
	mask = 1 << (nr & 31);

	वापस ___change_bit(ADDR, mask) != 0;
पूर्ण

अटल अंतरभूत व्योम change_bit(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अचिन्हित दीर्घ *ADDR, mask;

	ADDR = ((अचिन्हित दीर्घ *) addr) + (nr >> 5);
	mask = 1 << (nr & 31);

	(व्योम) ___change_bit(ADDR, mask);
पूर्ण

#समावेश <यंत्र-generic/bitops/non-atomic.h>

#समावेश <यंत्र-generic/bitops/ffz.h>
#समावेश <यंत्र-generic/bitops/__ffs.h>
#समावेश <यंत्र-generic/bitops/sched.h>
#समावेश <यंत्र-generic/bitops/ffs.h>
#समावेश <यंत्र-generic/bitops/fls.h>
#समावेश <यंत्र-generic/bitops/__fls.h>
#समावेश <यंत्र-generic/bitops/fls64.h>
#समावेश <यंत्र-generic/bitops/hweight.h>
#समावेश <यंत्र-generic/bitops/lock.h>
#समावेश <यंत्र-generic/bitops/find.h>
#समावेश <यंत्र-generic/bitops/le.h>
#समावेश <यंत्र-generic/bitops/ext2-atomic.h>

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* defined(_SPARC_BITOPS_H) */
