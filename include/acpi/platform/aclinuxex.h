<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: aclinuxex.h - Extra OS specअगरic defines, etc. क्रम Linux
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित __ACLINUXEX_H__
#घोषणा __ACLINUXEX_H__

#अगर_घोषित __KERNEL__

#अगर_अघोषित ACPI_USE_NATIVE_DIVIDE

#अगर_अघोषित ACPI_DIV_64_BY_32
#घोषणा ACPI_DIV_64_BY_32(n_hi, n_lo, d32, q32, r32) \
	करो अणु \
		u64 (__n) = ((u64) n_hi) << 32 | (n_lo); \
		(r32) = करो_भाग ((__n), (d32)); \
		(q32) = (u32) (__n); \
	पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_अघोषित ACPI_SHIFT_RIGHT_64
#घोषणा ACPI_SHIFT_RIGHT_64(n_hi, n_lo) \
	करो अणु \
		(n_lo) >>= 1; \
		(n_lo) |= (((n_hi) & 1) << 31); \
		(n_hi) >>= 1; \
	पूर्ण जबतक (0)
#पूर्ण_अगर

#पूर्ण_अगर

/*
 * Overrides क्रम in-kernel ACPICA
 */
acpi_status ACPI_INIT_FUNCTION acpi_os_initialize(व्योम);

acpi_status acpi_os_terminate(व्योम);

/*
 * The irqs_disabled() check is क्रम resume from RAM.
 * Interrupts are off during resume, just like they are क्रम boot.
 * However, boot has  (प्रणाली_state != SYSTEM_RUNNING)
 * to quiet __might_sleep() in kदो_स्मृति() and resume करोes not.
 */
अटल अंतरभूत व्योम *acpi_os_allocate(acpi_size size)
अणु
	वापस kदो_स्मृति(size, irqs_disabled()? GFP_ATOMIC : GFP_KERNEL);
पूर्ण

अटल अंतरभूत व्योम *acpi_os_allocate_zeroed(acpi_size size)
अणु
	वापस kzalloc(size, irqs_disabled()? GFP_ATOMIC : GFP_KERNEL);
पूर्ण

अटल अंतरभूत व्योम acpi_os_मुक्त(व्योम *memory)
अणु
	kमुक्त(memory);
पूर्ण

अटल अंतरभूत व्योम *acpi_os_acquire_object(acpi_cache_t * cache)
अणु
	वापस kmem_cache_zalloc(cache,
				 irqs_disabled()? GFP_ATOMIC : GFP_KERNEL);
पूर्ण

अटल अंतरभूत acpi_thपढ़ो_id acpi_os_get_thपढ़ो_id(व्योम)
अणु
	वापस (acpi_thपढ़ो_id) (अचिन्हित दीर्घ)current;
पूर्ण

/*
 * When lockdep is enabled, the spin_lock_init() macro stringअगरies it's
 * argument and uses that as a name क्रम the lock in debugging.
 * By executing spin_lock_init() in a macro the key changes from "lock" क्रम
 * all locks to the name of the argument of acpi_os_create_lock(), which
 * prevents lockdep from reporting false positives क्रम ACPICA locks.
 */
#घोषणा acpi_os_create_lock(__handle) \
	(अणु \
		spinlock_t *lock = ACPI_ALLOCATE(माप(*lock)); \
		अगर (lock) अणु \
			*(__handle) = lock; \
			spin_lock_init(*(__handle)); \
		पूर्ण \
		lock ? AE_OK : AE_NO_MEMORY; \
	पूर्ण)


#घोषणा acpi_os_create_raw_lock(__handle) \
	(अणु \
		raw_spinlock_t *lock = ACPI_ALLOCATE(माप(*lock)); \
		अगर (lock) अणु \
			*(__handle) = lock; \
			raw_spin_lock_init(*(__handle)); \
		पूर्ण \
		lock ? AE_OK : AE_NO_MEMORY; \
	पूर्ण)

अटल अंतरभूत acpi_cpu_flags acpi_os_acquire_raw_lock(acpi_raw_spinlock lockp)
अणु
	acpi_cpu_flags flags;

	raw_spin_lock_irqsave(lockp, flags);
	वापस flags;
पूर्ण

अटल अंतरभूत व्योम acpi_os_release_raw_lock(acpi_raw_spinlock lockp,
					    acpi_cpu_flags flags)
अणु
	raw_spin_unlock_irqrestore(lockp, flags);
पूर्ण

अटल अंतरभूत व्योम acpi_os_delete_raw_lock(acpi_raw_spinlock handle)
अणु
	ACPI_FREE(handle);
पूर्ण

अटल अंतरभूत u8 acpi_os_पढ़ोable(व्योम *poपूर्णांकer, acpi_size length)
अणु
	वापस TRUE;
पूर्ण

अटल अंतरभूत acpi_status acpi_os_initialize_debugger(व्योम)
अणु
	वापस AE_OK;
पूर्ण

अटल अंतरभूत व्योम acpi_os_terminate_debugger(व्योम)
अणु
	वापस;
पूर्ण

/*
 * OSL पूर्णांकerfaces added by Linux
 */

#पूर्ण_अगर				/* __KERNEL__ */

#पूर्ण_अगर				/* __ACLINUXEX_H__ */
