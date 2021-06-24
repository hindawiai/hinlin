<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _TIMEKEEPING_INTERNAL_H
#घोषणा _TIMEKEEPING_INTERNAL_H

#समावेश <linux/घड़ीsource.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/समय.स>

/*
 * समयkeeping debug functions
 */
#अगर_घोषित CONFIG_DEBUG_FS
बाह्य व्योम tk_debug_account_sleep_समय(स्थिर काष्ठा बारpec64 *t);
#अन्यथा
#घोषणा tk_debug_account_sleep_समय(x)
#पूर्ण_अगर

#अगर_घोषित CONFIG_CLOCKSOURCE_VALIDATE_LAST_CYCLE
अटल अंतरभूत u64 घड़ीsource_delta(u64 now, u64 last, u64 mask)
अणु
	u64 ret = (now - last) & mask;

	/*
	 * Prevent समय going backwards by checking the MSB of mask in
	 * the result. If set, वापस 0.
	 */
	वापस ret & ~(mask >> 1) ? 0 : ret;
पूर्ण
#अन्यथा
अटल अंतरभूत u64 घड़ीsource_delta(u64 now, u64 last, u64 mask)
अणु
	वापस (now - last) & mask;
पूर्ण
#पूर्ण_अगर

/* Semi खुला क्रम serialization of non समयkeeper VDSO updates. */
बाह्य raw_spinlock_t समयkeeper_lock;

#पूर्ण_अगर /* _TIMEKEEPING_INTERNAL_H */
