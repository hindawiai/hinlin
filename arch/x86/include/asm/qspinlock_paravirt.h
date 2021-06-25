<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_QSPINLOCK_PARAVIRT_H
#घोषणा __ASM_QSPINLOCK_PARAVIRT_H

/*
 * For x86-64, PV_CALLEE_SAVE_REGS_THUNK() saves and restores 8 64-bit
 * रेजिस्टरs. For i386, however, only 1 32-bit रेजिस्टर needs to be saved
 * and restored. So an optimized version of __pv_queued_spin_unlock() is
 * hand-coded क्रम 64-bit, but it isn't worthजबतक to करो it क्रम 32-bit.
 */
#अगर_घोषित CONFIG_64BIT

PV_CALLEE_SAVE_REGS_THUNK(__pv_queued_spin_unlock_slowpath);
#घोषणा __pv_queued_spin_unlock	__pv_queued_spin_unlock
#घोषणा PV_UNLOCK		"__raw_callee_save___pv_queued_spin_unlock"
#घोषणा PV_UNLOCK_SLOWPATH	"__raw_callee_save___pv_queued_spin_unlock_slowpath"

/*
 * Optimized assembly version of __raw_callee_save___pv_queued_spin_unlock
 * which combines the रेजिस्टरs saving trunk and the body of the following
 * C code:
 *
 * व्योम __pv_queued_spin_unlock(काष्ठा qspinlock *lock)
 * अणु
 *	u8 lockval = cmpxchg(&lock->locked, _Q_LOCKED_VAL, 0);
 *
 *	अगर (likely(lockval == _Q_LOCKED_VAL))
 *		वापस;
 *	pv_queued_spin_unlock_slowpath(lock, lockval);
 * पूर्ण
 *
 * For x86-64,
 *   rdi = lock              (first argument)
 *   rsi = lockval           (second argument)
 *   rdx = पूर्णांकernal variable (set to 0)
 */
यंत्र    (".pushsection .text;"
	".globl " PV_UNLOCK ";"
	".type " PV_UNLOCK ", @function;"
	".align 4,0x90;"
	PV_UNLOCK ": "
	FRAME_BEGIN
	"push  %rdx;"
	"mov   $0x1,%eax;"
	"xor   %edx,%edx;"
	LOCK_PREFIX "cmpxchg %dl,(%rdi);"
	"cmp   $0x1,%al;"
	"jne   .slowpath;"
	"pop   %rdx;"
	FRAME_END
	"ret;"
	".slowpath: "
	"push   %rsi;"
	"movzbl %al,%esi;"
	"call " PV_UNLOCK_SLOWPATH ";"
	"pop    %rsi;"
	"pop    %rdx;"
	FRAME_END
	"ret;"
	".size " PV_UNLOCK ", .-" PV_UNLOCK ";"
	".popsection");

#अन्यथा /* CONFIG_64BIT */

बाह्य व्योम __pv_queued_spin_unlock(काष्ठा qspinlock *lock);
PV_CALLEE_SAVE_REGS_THUNK(__pv_queued_spin_unlock);

#पूर्ण_अगर /* CONFIG_64BIT */
#पूर्ण_अगर
