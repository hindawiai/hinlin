<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * A stand-alone ticket spinlock implementation क्रम use by the non-VHE
 * KVM hypervisor code running at EL2.
 *
 * Copyright (C) 2020 Google LLC
 * Author: Will Deacon <will@kernel.org>
 *
 * Heavily based on the implementation हटाओd by c11090474d70 which was:
 * Copyright (C) 2012 ARM Ltd.
 */

#अगर_अघोषित __ARM64_KVM_NVHE_SPINLOCK_H__
#घोषणा __ARM64_KVM_NVHE_SPINLOCK_H__

#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/lse.h>

प्रकार जोड़ hyp_spinlock अणु
	u32	__val;
	काष्ठा अणु
#अगर_घोषित __AARCH64EB__
		u16 next, owner;
#अन्यथा
		u16 owner, next;
#पूर्ण_अगर
	पूर्ण;
पूर्ण hyp_spinlock_t;

#घोषणा hyp_spin_lock_init(l)						\
करो अणु									\
	*(l) = (hyp_spinlock_t)अणु .__val = 0 पूर्ण;				\
पूर्ण जबतक (0)

अटल अंतरभूत व्योम hyp_spin_lock(hyp_spinlock_t *lock)
अणु
	u32 पंचांगp;
	hyp_spinlock_t lockval, newval;

	यंत्र अस्थिर(
	/* Atomically increment the next ticket. */
	ARM64_LSE_ATOMIC_INSN(
	/* LL/SC */
"	prfm	pstl1strm, %3\n"
"1:	ldaxr	%w0, %3\n"
"	add	%w1, %w0, #(1 << 16)\n"
"	stxr	%w2, %w1, %3\n"
"	cbnz	%w2, 1b\n",
	/* LSE atomics */
"	mov	%w2, #(1 << 16)\n"
"	ldadda	%w2, %w0, %3\n"
	__nops(3))

	/* Did we get the lock? */
"	eor	%w1, %w0, %w0, ror #16\n"
"	cbz	%w1, 3f\n"
	/*
	 * No: spin on the owner. Send a local event to aव्योम missing an
	 * unlock beक्रमe the exclusive load.
	 */
"	sevl\n"
"2:	wfe\n"
"	ldaxrh	%w2, %4\n"
"	eor	%w1, %w2, %w0, lsr #16\n"
"	cbnz	%w1, 2b\n"
	/* We got the lock. Critical section starts here. */
"3:"
	: "=&r" (lockval), "=&r" (newval), "=&r" (पंचांगp), "+Q" (*lock)
	: "Q" (lock->owner)
	: "memory");
पूर्ण

अटल अंतरभूत व्योम hyp_spin_unlock(hyp_spinlock_t *lock)
अणु
	u64 पंचांगp;

	यंत्र अस्थिर(
	ARM64_LSE_ATOMIC_INSN(
	/* LL/SC */
	"	ldrh	%w1, %0\n"
	"	add	%w1, %w1, #1\n"
	"	stlrh	%w1, %0",
	/* LSE atomics */
	"	mov	%w1, #1\n"
	"	staddlh	%w1, %0\n"
	__nops(1))
	: "=Q" (lock->owner), "=&r" (पंचांगp)
	:
	: "memory");
पूर्ण

#पूर्ण_अगर /* __ARM64_KVM_NVHE_SPINLOCK_H__ */
