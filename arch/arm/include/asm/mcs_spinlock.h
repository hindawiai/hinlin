<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_MCS_LOCK_H
#घोषणा __ASM_MCS_LOCK_H

#अगर_घोषित CONFIG_SMP
#समावेश <यंत्र/spinlock.h>

/* MCS spin-locking. */
#घोषणा arch_mcs_spin_lock_contended(lock)				\
करो अणु									\
	/* Ensure prior stores are observed beक्रमe we enter wfe. */	\
	smp_mb();							\
	जबतक (!(smp_load_acquire(lock)))				\
		wfe();							\
पूर्ण जबतक (0)								\

#घोषणा arch_mcs_spin_unlock_contended(lock)				\
करो अणु									\
	smp_store_release(lock, 1);					\
	dsb_sev();							\
पूर्ण जबतक (0)

#पूर्ण_अगर	/* CONFIG_SMP */
#पूर्ण_अगर	/* __ASM_MCS_LOCK_H */
