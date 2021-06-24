<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_SPINLOCK_H
#घोषणा __ASM_CSKY_SPINLOCK_H

#समावेश <linux/spinlock_types.h>
#समावेश <यंत्र/barrier.h>

/*
 * Ticket-based spin-locking.
 */
अटल अंतरभूत व्योम arch_spin_lock(arch_spinlock_t *lock)
अणु
	arch_spinlock_t lockval;
	u32 ticket_next = 1 << TICKET_NEXT;
	u32 *p = &lock->lock;
	u32 पंचांगp;

	यंत्र अस्थिर (
		"1:	ldex.w		%0, (%2) \n"
		"	mov		%1, %0	 \n"
		"	add		%0, %3	 \n"
		"	stex.w		%0, (%2) \n"
		"	bez		%0, 1b   \n"
		: "=&r" (पंचांगp), "=&r" (lockval)
		: "r"(p), "r"(ticket_next)
		: "cc");

	जबतक (lockval.tickets.next != lockval.tickets.owner)
		lockval.tickets.owner = READ_ONCE(lock->tickets.owner);

	smp_mb();
पूर्ण

अटल अंतरभूत पूर्णांक arch_spin_trylock(arch_spinlock_t *lock)
अणु
	u32 पंचांगp, contended, res;
	u32 ticket_next = 1 << TICKET_NEXT;
	u32 *p = &lock->lock;

	करो अणु
		यंत्र अस्थिर (
		"	ldex.w		%0, (%3)   \n"
		"	movi		%2, 1	   \n"
		"	rotli		%1, %0, 16 \n"
		"	cmpne		%1, %0     \n"
		"	bt		1f         \n"
		"	movi		%2, 0	   \n"
		"	add		%0, %0, %4 \n"
		"	stex.w		%0, (%3)   \n"
		"1:				   \n"
		: "=&r" (res), "=&r" (पंचांगp), "=&r" (contended)
		: "r"(p), "r"(ticket_next)
		: "cc");
	पूर्ण जबतक (!res);

	अगर (!contended)
		smp_mb();

	वापस !contended;
पूर्ण

अटल अंतरभूत व्योम arch_spin_unlock(arch_spinlock_t *lock)
अणु
	smp_mb();
	WRITE_ONCE(lock->tickets.owner, lock->tickets.owner + 1);
पूर्ण

अटल अंतरभूत पूर्णांक arch_spin_value_unlocked(arch_spinlock_t lock)
अणु
	वापस lock.tickets.owner == lock.tickets.next;
पूर्ण

अटल अंतरभूत पूर्णांक arch_spin_is_locked(arch_spinlock_t *lock)
अणु
	वापस !arch_spin_value_unlocked(READ_ONCE(*lock));
पूर्ण

अटल अंतरभूत पूर्णांक arch_spin_is_contended(arch_spinlock_t *lock)
अणु
	काष्ठा __raw_tickets tickets = READ_ONCE(lock->tickets);

	वापस (tickets.next - tickets.owner) > 1;
पूर्ण
#घोषणा arch_spin_is_contended	arch_spin_is_contended

#समावेश <यंत्र/qrwlock.h>

#पूर्ण_अगर /* __ASM_CSKY_SPINLOCK_H */
