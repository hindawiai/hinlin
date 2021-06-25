<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __ASM_SPINLOCK_H
#घोषणा __ASM_SPINLOCK_H
#अगर_घोषित __KERNEL__

#अगर_घोषित CONFIG_PPC_QUEUED_SPINLOCKS
#समावेश <यंत्र/qspinlock.h>
#समावेश <यंत्र/qrwlock.h>
#अन्यथा
#समावेश <यंत्र/simple_spinlock.h>
#पूर्ण_अगर

/* See include/linux/spinlock.h */
#घोषणा smp_mb__after_spinlock()	smp_mb()

#अगर_अघोषित CONFIG_PARAVIRT_SPINLOCKS
अटल अंतरभूत व्योम pv_spinlocks_init(व्योम) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* __ASM_SPINLOCK_H */
