<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 */

#अगर_अघोषित _ASM_RISCV_BITOPS_H
#घोषणा _ASM_RISCV_BITOPS_H

#अगर_अघोषित _LINUX_BITOPS_H
#त्रुटि "Only <linux/bitops.h> can be included directly"
#पूर्ण_अगर /* _LINUX_BITOPS_H */

#समावेश <linux/compiler.h>
#समावेश <linux/irqflags.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/bitsperदीर्घ.h>

#समावेश <यंत्र-generic/bitops/__ffs.h>
#समावेश <यंत्र-generic/bitops/ffz.h>
#समावेश <यंत्र-generic/bitops/fls.h>
#समावेश <यंत्र-generic/bitops/__fls.h>
#समावेश <यंत्र-generic/bitops/fls64.h>
#समावेश <यंत्र-generic/bitops/find.h>
#समावेश <यंत्र-generic/bitops/sched.h>
#समावेश <यंत्र-generic/bitops/ffs.h>

#समावेश <यंत्र-generic/bitops/hweight.h>

#अगर (BITS_PER_LONG == 64)
#घोषणा __AMO(op)	"amo" #op ".d"
#या_अगर (BITS_PER_LONG == 32)
#घोषणा __AMO(op)	"amo" #op ".w"
#अन्यथा
#त्रुटि "Unexpected BITS_PER_LONG"
#पूर्ण_अगर

#घोषणा __test_and_op_bit_ord(op, mod, nr, addr, ord)		\
(अणु								\
	अचिन्हित दीर्घ __res, __mask;				\
	__mask = BIT_MASK(nr);					\
	__यंत्र__ __अस्थिर__ (					\
		__AMO(op) #ord " %0, %2, %1"			\
		: "=r" (__res), "+A" (addr[BIT_WORD(nr)])	\
		: "r" (mod(__mask))				\
		: "memory");					\
	((__res & __mask) != 0);				\
पूर्ण)

#घोषणा __op_bit_ord(op, mod, nr, addr, ord)			\
	__यंत्र__ __अस्थिर__ (					\
		__AMO(op) #ord " zero, %1, %0"			\
		: "+A" (addr[BIT_WORD(nr)])			\
		: "r" (mod(BIT_MASK(nr)))			\
		: "memory");

#घोषणा __test_and_op_bit(op, mod, nr, addr) 			\
	__test_and_op_bit_ord(op, mod, nr, addr, .aqrl)
#घोषणा __op_bit(op, mod, nr, addr)				\
	__op_bit_ord(op, mod, nr, addr, )

/* Biपंचांगask modअगरiers */
#घोषणा __NOP(x)	(x)
#घोषणा __NOT(x)	(~(x))

/**
 * test_and_set_bit - Set a bit and वापस its old value
 * @nr: Bit to set
 * @addr: Address to count from
 *
 * This operation may be reordered on other architectures than x86.
 */
अटल अंतरभूत पूर्णांक test_and_set_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	वापस __test_and_op_bit(or, __NOP, nr, addr);
पूर्ण

/**
 * test_and_clear_bit - Clear a bit and वापस its old value
 * @nr: Bit to clear
 * @addr: Address to count from
 *
 * This operation can be reordered on other architectures other than x86.
 */
अटल अंतरभूत पूर्णांक test_and_clear_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	वापस __test_and_op_bit(and, __NOT, nr, addr);
पूर्ण

/**
 * test_and_change_bit - Change a bit and वापस its old value
 * @nr: Bit to change
 * @addr: Address to count from
 *
 * This operation is atomic and cannot be reordered.
 * It also implies a memory barrier.
 */
अटल अंतरभूत पूर्णांक test_and_change_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	वापस __test_and_op_bit(xor, __NOP, nr, addr);
पूर्ण

/**
 * set_bit - Atomically set a bit in memory
 * @nr: the bit to set
 * @addr: the address to start counting from
 *
 * Note: there are no guarantees that this function will not be reordered
 * on non x86 architectures, so अगर you are writing portable code,
 * make sure not to rely on its reordering guarantees.
 *
 * Note that @nr may be almost arbitrarily large; this function is not
 * restricted to acting on a single-word quantity.
 */
अटल अंतरभूत व्योम set_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	__op_bit(or, __NOP, nr, addr);
पूर्ण

/**
 * clear_bit - Clears a bit in memory
 * @nr: Bit to clear
 * @addr: Address to start counting from
 *
 * Note: there are no guarantees that this function will not be reordered
 * on non x86 architectures, so अगर you are writing portable code,
 * make sure not to rely on its reordering guarantees.
 */
अटल अंतरभूत व्योम clear_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	__op_bit(and, __NOT, nr, addr);
पूर्ण

/**
 * change_bit - Toggle a bit in memory
 * @nr: Bit to change
 * @addr: Address to start counting from
 *
 * change_bit()  may be reordered on other architectures than x86.
 * Note that @nr may be almost arbitrarily large; this function is not
 * restricted to acting on a single-word quantity.
 */
अटल अंतरभूत व्योम change_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	__op_bit(xor, __NOP, nr, addr);
पूर्ण

/**
 * test_and_set_bit_lock - Set a bit and वापस its old value, क्रम lock
 * @nr: Bit to set
 * @addr: Address to count from
 *
 * This operation is atomic and provides acquire barrier semantics.
 * It can be used to implement bit locks.
 */
अटल अंतरभूत पूर्णांक test_and_set_bit_lock(
	अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	वापस __test_and_op_bit_ord(or, __NOP, nr, addr, .aq);
पूर्ण

/**
 * clear_bit_unlock - Clear a bit in memory, क्रम unlock
 * @nr: the bit to set
 * @addr: the address to start counting from
 *
 * This operation is atomic and provides release barrier semantics.
 */
अटल अंतरभूत व्योम clear_bit_unlock(
	अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	__op_bit_ord(and, __NOT, nr, addr, .rl);
पूर्ण

/**
 * __clear_bit_unlock - Clear a bit in memory, क्रम unlock
 * @nr: the bit to set
 * @addr: the address to start counting from
 *
 * This operation is like clear_bit_unlock, however it is not atomic.
 * It करोes provide release barrier semantics so it can be used to unlock
 * a bit lock, however it would only be used अगर no other CPU can modअगरy
 * any bits in the memory until the lock is released (a good example is
 * अगर the bit lock itself protects access to the other bits in the word).
 *
 * On RISC-V प्रणालीs there seems to be no benefit to taking advantage of the
 * non-atomic property here: it's a lot more inकाष्ठाions and we still have to
 * provide release semantics anyway.
 */
अटल अंतरभूत व्योम __clear_bit_unlock(
	अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	clear_bit_unlock(nr, addr);
पूर्ण

#अघोषित __test_and_op_bit
#अघोषित __op_bit
#अघोषित __NOP
#अघोषित __NOT
#अघोषित __AMO

#समावेश <यंत्र-generic/bitops/non-atomic.h>
#समावेश <यंत्र-generic/bitops/le.h>
#समावेश <यंत्र-generic/bitops/ext2-atomic.h>

#पूर्ण_अगर /* _ASM_RISCV_BITOPS_H */
