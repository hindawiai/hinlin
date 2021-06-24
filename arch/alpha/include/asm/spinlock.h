<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ALPHA_SPINLOCK_H
#घोषणा _ALPHA_SPINLOCK_H

#समावेश <linux/kernel.h>
#समावेश <यंत्र/current.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/processor.h>

/*
 * Simple spin lock operations.  There are two variants, one clears IRQ's
 * on the local processor, one करोes not.
 *
 * We make no fairness assumptions. They have a cost.
 */

#घोषणा arch_spin_is_locked(x)	((x)->lock != 0)

अटल अंतरभूत पूर्णांक arch_spin_value_unlocked(arch_spinlock_t lock)
अणु
        वापस lock.lock == 0;
पूर्ण

अटल अंतरभूत व्योम arch_spin_unlock(arch_spinlock_t * lock)
अणु
	mb();
	lock->lock = 0;
पूर्ण

अटल अंतरभूत व्योम arch_spin_lock(arch_spinlock_t * lock)
अणु
	दीर्घ पंचांगp;

	__यंत्र__ __अस्थिर__(
	"1:	ldl_l	%0,%1\n"
	"	bne	%0,2f\n"
	"	lda	%0,1\n"
	"	stl_c	%0,%1\n"
	"	beq	%0,2f\n"
	"	mb\n"
	".subsection 2\n"
	"2:	ldl	%0,%1\n"
	"	bne	%0,2b\n"
	"	br	1b\n"
	".previous"
	: "=&r" (पंचांगp), "=m" (lock->lock)
	: "m"(lock->lock) : "memory");
पूर्ण

अटल अंतरभूत पूर्णांक arch_spin_trylock(arch_spinlock_t *lock)
अणु
	वापस !test_and_set_bit(0, &lock->lock);
पूर्ण

/***********************************************************/

अटल अंतरभूत व्योम arch_पढ़ो_lock(arch_rwlock_t *lock)
अणु
	दीर्घ regx;

	__यंत्र__ __अस्थिर__(
	"1:	ldl_l	%1,%0\n"
	"	blbs	%1,6f\n"
	"	subl	%1,2,%1\n"
	"	stl_c	%1,%0\n"
	"	beq	%1,6f\n"
	"	mb\n"
	".subsection 2\n"
	"6:	ldl	%1,%0\n"
	"	blbs	%1,6b\n"
	"	br	1b\n"
	".previous"
	: "=m" (*lock), "=&r" (regx)
	: "m" (*lock) : "memory");
पूर्ण

अटल अंतरभूत व्योम arch_ग_लिखो_lock(arch_rwlock_t *lock)
अणु
	दीर्घ regx;

	__यंत्र__ __अस्थिर__(
	"1:	ldl_l	%1,%0\n"
	"	bne	%1,6f\n"
	"	lda	%1,1\n"
	"	stl_c	%1,%0\n"
	"	beq	%1,6f\n"
	"	mb\n"
	".subsection 2\n"
	"6:	ldl	%1,%0\n"
	"	bne	%1,6b\n"
	"	br	1b\n"
	".previous"
	: "=m" (*lock), "=&r" (regx)
	: "m" (*lock) : "memory");
पूर्ण

अटल अंतरभूत पूर्णांक arch_पढ़ो_trylock(arch_rwlock_t * lock)
अणु
	दीर्घ regx;
	पूर्णांक success;

	__यंत्र__ __अस्थिर__(
	"1:	ldl_l	%1,%0\n"
	"	lda	%2,0\n"
	"	blbs	%1,2f\n"
	"	subl	%1,2,%2\n"
	"	stl_c	%2,%0\n"
	"	beq	%2,6f\n"
	"2:	mb\n"
	".subsection 2\n"
	"6:	br	1b\n"
	".previous"
	: "=m" (*lock), "=&r" (regx), "=&r" (success)
	: "m" (*lock) : "memory");

	वापस success;
पूर्ण

अटल अंतरभूत पूर्णांक arch_ग_लिखो_trylock(arch_rwlock_t * lock)
अणु
	दीर्घ regx;
	पूर्णांक success;

	__यंत्र__ __अस्थिर__(
	"1:	ldl_l	%1,%0\n"
	"	lda	%2,0\n"
	"	bne	%1,2f\n"
	"	lda	%2,1\n"
	"	stl_c	%2,%0\n"
	"	beq	%2,6f\n"
	"2:	mb\n"
	".subsection 2\n"
	"6:	br	1b\n"
	".previous"
	: "=m" (*lock), "=&r" (regx), "=&r" (success)
	: "m" (*lock) : "memory");

	वापस success;
पूर्ण

अटल अंतरभूत व्योम arch_पढ़ो_unlock(arch_rwlock_t * lock)
अणु
	दीर्घ regx;
	__यंत्र__ __अस्थिर__(
	"	mb\n"
	"1:	ldl_l	%1,%0\n"
	"	addl	%1,2,%1\n"
	"	stl_c	%1,%0\n"
	"	beq	%1,6f\n"
	".subsection 2\n"
	"6:	br	1b\n"
	".previous"
	: "=m" (*lock), "=&r" (regx)
	: "m" (*lock) : "memory");
पूर्ण

अटल अंतरभूत व्योम arch_ग_लिखो_unlock(arch_rwlock_t * lock)
अणु
	mb();
	lock->lock = 0;
पूर्ण

#पूर्ण_अगर /* _ALPHA_SPINLOCK_H */
