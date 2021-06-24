<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Split spinlock implementation out पूर्णांकo its own file, so it can be
 * compiled in a FTRACE-compatible way.
 */
#समावेश <linux/spinlock.h>
#समावेश <linux/export.h>
#समावेश <linux/jump_label.h>

#समावेश <यंत्र/paravirt.h>

__visible व्योम __native_queued_spin_unlock(काष्ठा qspinlock *lock)
अणु
	native_queued_spin_unlock(lock);
पूर्ण
PV_CALLEE_SAVE_REGS_THUNK(__native_queued_spin_unlock);

bool pv_is_native_spin_unlock(व्योम)
अणु
	वापस pv_ops.lock.queued_spin_unlock.func ==
		__raw_callee_save___native_queued_spin_unlock;
पूर्ण

__visible bool __native_vcpu_is_preempted(दीर्घ cpu)
अणु
	वापस false;
पूर्ण
PV_CALLEE_SAVE_REGS_THUNK(__native_vcpu_is_preempted);

bool pv_is_native_vcpu_is_preempted(व्योम)
अणु
	वापस pv_ops.lock.vcpu_is_preempted.func ==
		__raw_callee_save___native_vcpu_is_preempted;
पूर्ण

व्योम __init paravirt_set_cap(व्योम)
अणु
	अगर (!pv_is_native_spin_unlock())
		setup_क्रमce_cpu_cap(X86_FEATURE_PVUNLOCK);

	अगर (!pv_is_native_vcpu_is_preempted())
		setup_क्रमce_cpu_cap(X86_FEATURE_VCPUPREEMPT);
पूर्ण
