<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#अगर_अघोषित KVM_MMU_LOCK_H
#घोषणा KVM_MMU_LOCK_H 1

/*
 * Architectures can choose whether to use an rwlock or spinlock
 * क्रम the mmu_lock.  These macros, क्रम use in common code
 * only, aव्योमs using #अगर_घोषितs in places that must deal with
 * multiple architectures.
 */

#अगर_घोषित KVM_HAVE_MMU_RWLOCK
#घोषणा KVM_MMU_LOCK_INIT(kvm) rwlock_init(&(kvm)->mmu_lock)
#घोषणा KVM_MMU_LOCK(kvm)      ग_लिखो_lock(&(kvm)->mmu_lock)
#घोषणा KVM_MMU_UNLOCK(kvm)    ग_लिखो_unlock(&(kvm)->mmu_lock)
#अन्यथा
#घोषणा KVM_MMU_LOCK_INIT(kvm) spin_lock_init(&(kvm)->mmu_lock)
#घोषणा KVM_MMU_LOCK(kvm)      spin_lock(&(kvm)->mmu_lock)
#घोषणा KVM_MMU_UNLOCK(kvm)    spin_unlock(&(kvm)->mmu_lock)
#पूर्ण_अगर /* KVM_HAVE_MMU_RWLOCK */

#पूर्ण_अगर
