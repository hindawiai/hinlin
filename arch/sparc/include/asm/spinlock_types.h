<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SPARC_SPINLOCK_TYPES_H
#घोषणा __SPARC_SPINLOCK_TYPES_H

#अगर_घोषित CONFIG_QUEUED_SPINLOCKS
#समावेश <यंत्र-generic/qspinlock_types.h>
#अन्यथा

प्रकार काष्ठा अणु
	अस्थिर अचिन्हित अक्षर lock;
पूर्ण arch_spinlock_t;

#घोषणा __ARCH_SPIN_LOCK_UNLOCKED	अणु 0 पूर्ण
#पूर्ण_अगर /* CONFIG_QUEUED_SPINLOCKS */

#अगर_घोषित CONFIG_QUEUED_RWLOCKS
#समावेश <यंत्र-generic/qrwlock_types.h>
#अन्यथा
प्रकार काष्ठा अणु
	अस्थिर अचिन्हित पूर्णांक lock;
पूर्ण arch_rwlock_t;

#घोषणा __ARCH_RW_LOCK_UNLOCKED		अणु 0 पूर्ण
#पूर्ण_अगर /* CONFIG_QUEUED_RWLOCKS */
#पूर्ण_अगर
