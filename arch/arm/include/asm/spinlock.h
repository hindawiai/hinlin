<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SPINLOCK_H
#घोषणा __ASM_SPINLOCK_H

#अगर __LINUX_ARM_ARCH__ < 6
#त्रुटि SMP not supported on pre-ARMv6 CPUs
#पूर्ण_अगर

#समावेश <linux/prefetch.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/processor.h>

/*
 * sev and wfe are ARMv6K extensions.  Uniprocessor ARMv6 may not have the K
 * extensions, so when running on UP, we have to patch these inकाष्ठाions away.
 */
#अगर_घोषित CONFIG_THUMB2_KERNEL
/*
 * For Thumb-2, special care is needed to ensure that the conditional WFE
 * inकाष्ठाion really करोes assemble to exactly 4 bytes (as required by
 * the SMP_ON_UP fixup code).   By itself "wfene" might cause the
 * assembler to insert a extra (16-bit) IT inकाष्ठाion, depending on the
 * presence or असलence of neighbouring conditional inकाष्ठाions.
 *
 * To aव्योम this unpredictability, an appropriate IT is inserted explicitly:
 * the assembler won't change IT inकाष्ठाions which are explicitly present
 * in the input.
 */
#घोषणा WFE(cond)	__ALT_SMP_ASM(		\
	"it " cond "\n\t"			\
	"wfe" cond ".n",			\
						\
	"nop.w"					\
)
#अन्यथा
#घोषणा WFE(cond)	__ALT_SMP_ASM("wfe" cond, "nop")
#पूर्ण_अगर

#घोषणा SEV		__ALT_SMP_ASM(WASM(sev), WASM(nop))

अटल अंतरभूत व्योम dsb_sev(व्योम)
अणु

	dsb(ishst);
	__यंत्र__(SEV);
पूर्ण

/*
 * ARMv6 ticket-based spin-locking.
 *
 * A memory barrier is required after we get a lock, and beक्रमe we
 * release it, because V6 CPUs are assumed to have weakly ordered
 * memory.
 */

अटल अंतरभूत व्योम arch_spin_lock(arch_spinlock_t *lock)
अणु
	अचिन्हित दीर्घ पंचांगp;
	u32 newval;
	arch_spinlock_t lockval;

	prefetchw(&lock->slock);
	__यंत्र__ __अस्थिर__(
"1:	ldrex	%0, [%3]\n"
"	add	%1, %0, %4\n"
"	strex	%2, %1, [%3]\n"
"	teq	%2, #0\n"
"	bne	1b"
	: "=&r" (lockval), "=&r" (newval), "=&r" (पंचांगp)
	: "r" (&lock->slock), "I" (1 << TICKET_SHIFT)
	: "cc");

	जबतक (lockval.tickets.next != lockval.tickets.owner) अणु
		wfe();
		lockval.tickets.owner = READ_ONCE(lock->tickets.owner);
	पूर्ण

	smp_mb();
पूर्ण

अटल अंतरभूत पूर्णांक arch_spin_trylock(arch_spinlock_t *lock)
अणु
	अचिन्हित दीर्घ contended, res;
	u32 slock;

	prefetchw(&lock->slock);
	करो अणु
		__यंत्र__ __अस्थिर__(
		"	ldrex	%0, [%3]\n"
		"	mov	%2, #0\n"
		"	subs	%1, %0, %0, ror #16\n"
		"	addeq	%0, %0, %4\n"
		"	strexeq	%2, %0, [%3]"
		: "=&r" (slock), "=&r" (contended), "=&r" (res)
		: "r" (&lock->slock), "I" (1 << TICKET_SHIFT)
		: "cc");
	पूर्ण जबतक (res);

	अगर (!contended) अणु
		smp_mb();
		वापस 1;
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम arch_spin_unlock(arch_spinlock_t *lock)
अणु
	smp_mb();
	lock->tickets.owner++;
	dsb_sev();
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

/*
 * RWLOCKS
 *
 *
 * Write locks are easy - we just set bit 31.  When unlocking, we can
 * just ग_लिखो zero since the lock is exclusively held.
 */

अटल अंतरभूत व्योम arch_ग_लिखो_lock(arch_rwlock_t *rw)
अणु
	अचिन्हित दीर्घ पंचांगp;

	prefetchw(&rw->lock);
	__यंत्र__ __अस्थिर__(
"1:	ldrex	%0, [%1]\n"
"	teq	%0, #0\n"
	WFE("ne")
"	strexeq	%0, %2, [%1]\n"
"	teq	%0, #0\n"
"	bne	1b"
	: "=&r" (पंचांगp)
	: "r" (&rw->lock), "r" (0x80000000)
	: "cc");

	smp_mb();
पूर्ण

अटल अंतरभूत पूर्णांक arch_ग_लिखो_trylock(arch_rwlock_t *rw)
अणु
	अचिन्हित दीर्घ contended, res;

	prefetchw(&rw->lock);
	करो अणु
		__यंत्र__ __अस्थिर__(
		"	ldrex	%0, [%2]\n"
		"	mov	%1, #0\n"
		"	teq	%0, #0\n"
		"	strexeq	%1, %3, [%2]"
		: "=&r" (contended), "=&r" (res)
		: "r" (&rw->lock), "r" (0x80000000)
		: "cc");
	पूर्ण जबतक (res);

	अगर (!contended) अणु
		smp_mb();
		वापस 1;
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम arch_ग_लिखो_unlock(arch_rwlock_t *rw)
अणु
	smp_mb();

	__यंत्र__ __अस्थिर__(
	"str	%1, [%0]\n"
	:
	: "r" (&rw->lock), "r" (0)
	: "cc");

	dsb_sev();
पूर्ण

/*
 * Read locks are a bit more hairy:
 *  - Exclusively load the lock value.
 *  - Increment it.
 *  - Store new lock value अगर positive, and we still own this location.
 *    If the value is negative, we've alपढ़ोy failed.
 *  - If we failed to store the value, we want a negative result.
 *  - If we failed, try again.
 * Unlocking is similarly hairy.  We may have multiple पढ़ो locks
 * currently active.  However, we know we won't have any ग_लिखो
 * locks.
 */
अटल अंतरभूत व्योम arch_पढ़ो_lock(arch_rwlock_t *rw)
अणु
	अचिन्हित दीर्घ पंचांगp, पंचांगp2;

	prefetchw(&rw->lock);
	__यंत्र__ __अस्थिर__(
"	.syntax unified\n"
"1:	ldrex	%0, [%2]\n"
"	adds	%0, %0, #1\n"
"	strexpl	%1, %0, [%2]\n"
	WFE("mi")
"	rsbspl	%0, %1, #0\n"
"	bmi	1b"
	: "=&r" (पंचांगp), "=&r" (पंचांगp2)
	: "r" (&rw->lock)
	: "cc");

	smp_mb();
पूर्ण

अटल अंतरभूत व्योम arch_पढ़ो_unlock(arch_rwlock_t *rw)
अणु
	अचिन्हित दीर्घ पंचांगp, पंचांगp2;

	smp_mb();

	prefetchw(&rw->lock);
	__यंत्र__ __अस्थिर__(
"1:	ldrex	%0, [%2]\n"
"	sub	%0, %0, #1\n"
"	strex	%1, %0, [%2]\n"
"	teq	%1, #0\n"
"	bne	1b"
	: "=&r" (पंचांगp), "=&r" (पंचांगp2)
	: "r" (&rw->lock)
	: "cc");

	अगर (पंचांगp == 0)
		dsb_sev();
पूर्ण

अटल अंतरभूत पूर्णांक arch_पढ़ो_trylock(arch_rwlock_t *rw)
अणु
	अचिन्हित दीर्घ contended, res;

	prefetchw(&rw->lock);
	करो अणु
		__यंत्र__ __अस्थिर__(
		"	ldrex	%0, [%2]\n"
		"	mov	%1, #0\n"
		"	adds	%0, %0, #1\n"
		"	strexpl	%1, %0, [%2]"
		: "=&r" (contended), "=&r" (res)
		: "r" (&rw->lock)
		: "cc");
	पूर्ण जबतक (res);

	/* If the lock is negative, then it is alपढ़ोy held क्रम ग_लिखो. */
	अगर (contended < 0x80000000) अणु
		smp_mb();
		वापस 1;
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण
पूर्ण

#पूर्ण_अगर /* __ASM_SPINLOCK_H */
