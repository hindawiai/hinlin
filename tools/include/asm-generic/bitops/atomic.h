<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _TOOLS_LINUX_ASM_GENERIC_BITOPS_ATOMIC_H_
#घोषणा _TOOLS_LINUX_ASM_GENERIC_BITOPS_ATOMIC_H_

#समावेश <यंत्र/types.h>
#समावेश <यंत्र/bitsperदीर्घ.h>

अटल अंतरभूत व्योम set_bit(पूर्णांक nr, अचिन्हित दीर्घ *addr)
अणु
	addr[nr / __BITS_PER_LONG] |= 1UL << (nr % __BITS_PER_LONG);
पूर्ण

अटल अंतरभूत व्योम clear_bit(पूर्णांक nr, अचिन्हित दीर्घ *addr)
अणु
	addr[nr / __BITS_PER_LONG] &= ~(1UL << (nr % __BITS_PER_LONG));
पूर्ण

#पूर्ण_अगर /* _TOOLS_LINUX_ASM_GENERIC_BITOPS_ATOMIC_H_ */
