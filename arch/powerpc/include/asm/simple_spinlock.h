<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_POWERPC_SIMPLE_SPINLOCK_H
#घोषणा _ASM_POWERPC_SIMPLE_SPINLOCK_H

/*
 * Simple spin lock operations.
 *
 * Copyright (C) 2001-2004 Paul Mackerras <paulus@au.ibm.com>, IBM
 * Copyright (C) 2001 Anton Blanअक्षरd <anton@au.ibm.com>, IBM
 * Copyright (C) 2002 Dave Engebretsen <engebret@us.ibm.com>, IBM
 *	Rework to support भव processors
 *
 * Type of पूर्णांक is used as a full 64b word is not necessary.
 *
 * (the type definitions are in यंत्र/simple_spinlock_types.h)
 */
#समावेश <linux/irqflags.h>
#समावेश <यंत्र/paravirt.h>
#समावेश <यंत्र/paca.h>
#समावेश <यंत्र/synch.h>
#समावेश <यंत्र/ppc-opcode.h>

#अगर_घोषित CONFIG_PPC64
/* use 0x800000yy when locked, where yy == CPU number */
#अगर_घोषित __BIG_ENDIAN__
#घोषणा LOCK_TOKEN	(*(u32 *)(&get_paca()->lock_token))
#अन्यथा
#घोषणा LOCK_TOKEN	(*(u32 *)(&get_paca()->paca_index))
#पूर्ण_अगर
#अन्यथा
#घोषणा LOCK_TOKEN	1
#पूर्ण_अगर

अटल __always_अंतरभूत पूर्णांक arch_spin_value_unlocked(arch_spinlock_t lock)
अणु
	वापस lock.slock == 0;
पूर्ण

अटल अंतरभूत पूर्णांक arch_spin_is_locked(arch_spinlock_t *lock)
अणु
	वापस !arch_spin_value_unlocked(READ_ONCE(*lock));
पूर्ण

/*
 * This वापसs the old value in the lock, so we succeeded
 * in getting the lock अगर the वापस value is 0.
 */
अटल अंतरभूत अचिन्हित दीर्घ __arch_spin_trylock(arch_spinlock_t *lock)
अणु
	अचिन्हित दीर्घ पंचांगp, token;

	token = LOCK_TOKEN;
	__यंत्र__ __अस्थिर__(
"1:	" PPC_LWARX(%0,0,%2,1) "\न\
	cmpwi		0,%0,0\न\
	bne-		2f\न\
	stwcx.		%1,0,%2\न\
	bne-		1b\न"
	PPC_ACQUIRE_BARRIER
"2:"
	: "=&r" (पंचांगp)
	: "r" (token), "r" (&lock->slock)
	: "cr0", "memory");

	वापस पंचांगp;
पूर्ण

अटल अंतरभूत पूर्णांक arch_spin_trylock(arch_spinlock_t *lock)
अणु
	वापस __arch_spin_trylock(lock) == 0;
पूर्ण

/*
 * On a प्रणाली with shared processors (that is, where a physical
 * processor is multiplexed between several भव processors),
 * there is no poपूर्णांक spinning on a lock अगर the holder of the lock
 * isn't currently scheduled on a physical processor.  Instead
 * we detect this situation and ask the hypervisor to give the
 * rest of our बारlice to the lock holder.
 *
 * So that we can tell which भव processor is holding a lock,
 * we put 0x80000000 | smp_processor_id() in the lock when it is
 * held.  Conveniently, we have a word in the paca that holds this
 * value.
 */

#अगर defined(CONFIG_PPC_SPLPAR)
/* We only yield to the hypervisor अगर we are in shared processor mode */
व्योम splpar_spin_yield(arch_spinlock_t *lock);
व्योम splpar_rw_yield(arch_rwlock_t *lock);
#अन्यथा /* SPLPAR */
अटल अंतरभूत व्योम splpar_spin_yield(arch_spinlock_t *lock) अणुपूर्ण
अटल अंतरभूत व्योम splpar_rw_yield(arch_rwlock_t *lock) अणुपूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम spin_yield(arch_spinlock_t *lock)
अणु
	अगर (is_shared_processor())
		splpar_spin_yield(lock);
	अन्यथा
		barrier();
पूर्ण

अटल अंतरभूत व्योम rw_yield(arch_rwlock_t *lock)
अणु
	अगर (is_shared_processor())
		splpar_rw_yield(lock);
	अन्यथा
		barrier();
पूर्ण

अटल अंतरभूत व्योम arch_spin_lock(arch_spinlock_t *lock)
अणु
	जबतक (1) अणु
		अगर (likely(__arch_spin_trylock(lock) == 0))
			अवरोध;
		करो अणु
			HMT_low();
			अगर (is_shared_processor())
				splpar_spin_yield(lock);
		पूर्ण जबतक (unlikely(lock->slock != 0));
		HMT_medium();
	पूर्ण
पूर्ण

अटल अंतरभूत
व्योम arch_spin_lock_flags(arch_spinlock_t *lock, अचिन्हित दीर्घ flags)
अणु
	अचिन्हित दीर्घ flags_dis;

	जबतक (1) अणु
		अगर (likely(__arch_spin_trylock(lock) == 0))
			अवरोध;
		local_save_flags(flags_dis);
		local_irq_restore(flags);
		करो अणु
			HMT_low();
			अगर (is_shared_processor())
				splpar_spin_yield(lock);
		पूर्ण जबतक (unlikely(lock->slock != 0));
		HMT_medium();
		local_irq_restore(flags_dis);
	पूर्ण
पूर्ण
#घोषणा arch_spin_lock_flags arch_spin_lock_flags

अटल अंतरभूत व्योम arch_spin_unlock(arch_spinlock_t *lock)
अणु
	__यंत्र__ __अस्थिर__("# arch_spin_unlock\n\t"
				PPC_RELEASE_BARRIER: : :"memory");
	lock->slock = 0;
पूर्ण

/*
 * Read-ग_लिखो spinlocks, allowing multiple पढ़ोers
 * but only one ग_लिखोr.
 *
 * NOTE! it is quite common to have पढ़ोers in पूर्णांकerrupts
 * but no पूर्णांकerrupt ग_लिखोrs. For those circumstances we
 * can "mix" irq-safe locks - any ग_लिखोr needs to get a
 * irq-safe ग_लिखो-lock, but पढ़ोers can get non-irqsafe
 * पढ़ो-locks.
 */

#अगर_घोषित CONFIG_PPC64
#घोषणा __DO_SIGN_EXTEND	"extsw	%0,%0\n"
#घोषणा WRLOCK_TOKEN		LOCK_TOKEN	/* it's negative */
#अन्यथा
#घोषणा __DO_SIGN_EXTEND
#घोषणा WRLOCK_TOKEN		(-1)
#पूर्ण_अगर

/*
 * This वापसs the old value in the lock + 1,
 * so we got a पढ़ो lock अगर the वापस value is > 0.
 */
अटल अंतरभूत दीर्घ __arch_पढ़ो_trylock(arch_rwlock_t *rw)
अणु
	दीर्घ पंचांगp;

	__यंत्र__ __अस्थिर__(
"1:	" PPC_LWARX(%0,0,%1,1) "\n"
	__DO_SIGN_EXTEND
"	addic.		%0,%0,1\न\
	ble-		2f\न"
"	stwcx.		%0,0,%1\न\
	bne-		1b\न"
	PPC_ACQUIRE_BARRIER
"2:"	: "=&r" (पंचांगp)
	: "r" (&rw->lock)
	: "cr0", "xer", "memory");

	वापस पंचांगp;
पूर्ण

/*
 * This वापसs the old value in the lock,
 * so we got the ग_लिखो lock अगर the वापस value is 0.
 */
अटल अंतरभूत दीर्घ __arch_ग_लिखो_trylock(arch_rwlock_t *rw)
अणु
	दीर्घ पंचांगp, token;

	token = WRLOCK_TOKEN;
	__यंत्र__ __अस्थिर__(
"1:	" PPC_LWARX(%0,0,%2,1) "\न\
	cmpwi		0,%0,0\न\
	bne-		2f\न"
"	stwcx.		%1,0,%2\न\
	bne-		1b\न"
	PPC_ACQUIRE_BARRIER
"2:"	: "=&r" (पंचांगp)
	: "r" (token), "r" (&rw->lock)
	: "cr0", "memory");

	वापस पंचांगp;
पूर्ण

अटल अंतरभूत व्योम arch_पढ़ो_lock(arch_rwlock_t *rw)
अणु
	जबतक (1) अणु
		अगर (likely(__arch_पढ़ो_trylock(rw) > 0))
			अवरोध;
		करो अणु
			HMT_low();
			अगर (is_shared_processor())
				splpar_rw_yield(rw);
		पूर्ण जबतक (unlikely(rw->lock < 0));
		HMT_medium();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम arch_ग_लिखो_lock(arch_rwlock_t *rw)
अणु
	जबतक (1) अणु
		अगर (likely(__arch_ग_लिखो_trylock(rw) == 0))
			अवरोध;
		करो अणु
			HMT_low();
			अगर (is_shared_processor())
				splpar_rw_yield(rw);
		पूर्ण जबतक (unlikely(rw->lock != 0));
		HMT_medium();
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक arch_पढ़ो_trylock(arch_rwlock_t *rw)
अणु
	वापस __arch_पढ़ो_trylock(rw) > 0;
पूर्ण

अटल अंतरभूत पूर्णांक arch_ग_लिखो_trylock(arch_rwlock_t *rw)
अणु
	वापस __arch_ग_लिखो_trylock(rw) == 0;
पूर्ण

अटल अंतरभूत व्योम arch_पढ़ो_unlock(arch_rwlock_t *rw)
अणु
	दीर्घ पंचांगp;

	__यंत्र__ __अस्थिर__(
	"# read_unlock\n\t"
	PPC_RELEASE_BARRIER
"1:	lwarx		%0,0,%1\न\
	addic		%0,%0,-1\न"
"	stwcx.		%0,0,%1\न\
	bne-		1b"
	: "=&r"(पंचांगp)
	: "r"(&rw->lock)
	: "cr0", "xer", "memory");
पूर्ण

अटल अंतरभूत व्योम arch_ग_लिखो_unlock(arch_rwlock_t *rw)
अणु
	__यंत्र__ __अस्थिर__("# write_unlock\n\t"
				PPC_RELEASE_BARRIER: : :"memory");
	rw->lock = 0;
पूर्ण

#घोषणा arch_spin_relax(lock)	spin_yield(lock)
#घोषणा arch_पढ़ो_relax(lock)	rw_yield(lock)
#घोषणा arch_ग_लिखो_relax(lock)	rw_yield(lock)

#पूर्ण_अगर /* _ASM_POWERPC_SIMPLE_SPINLOCK_H */
