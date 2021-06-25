<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Fast user context implementation of घड़ी_समय_लो, समय_लोofday, and समय.
 *
 * Copyright 2006 Andi Kleen, SUSE Lअसल.
 * Copyright 2019 ARM Limited
 *
 * 32 Bit compat layer by Stefani Seibold <stefani@seibold.net>
 *  sponsored by Rohde & Schwarz GmbH & Co. KG Munich/Germany
 */
#समावेश <linux/समय.स>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>

#समावेश "../../../../lib/vdso/gettimeofday.c"

बाह्य पूर्णांक __vdso_समय_लोofday(काष्ठा __kernel_old_समयval *tv, काष्ठा समयzone *tz);
बाह्य __kernel_old_समय_प्रकार __vdso_समय(__kernel_old_समय_प्रकार *t);

पूर्णांक __vdso_समय_लोofday(काष्ठा __kernel_old_समयval *tv, काष्ठा समयzone *tz)
अणु
	वापस __cvdso_समय_लोofday(tv, tz);
पूर्ण

पूर्णांक समय_लोofday(काष्ठा __kernel_old_समयval *, काष्ठा समयzone *)
	__attribute__((weak, alias("__vdso_gettimeofday")));

__kernel_old_समय_प्रकार __vdso_समय(__kernel_old_समय_प्रकार *t)
अणु
	वापस __cvdso_समय(t);
पूर्ण

__kernel_old_समय_प्रकार समय(__kernel_old_समय_प्रकार *t)	__attribute__((weak, alias("__vdso_time")));


#अगर defined(CONFIG_X86_64) && !defined(BUILD_VDSO32_64)
/* both 64-bit and x32 use these */
बाह्य पूर्णांक __vdso_घड़ी_समय_लो(घड़ीid_t घड़ी, काष्ठा __kernel_बारpec *ts);
बाह्य पूर्णांक __vdso_घड़ी_getres(घड़ीid_t घड़ी, काष्ठा __kernel_बारpec *res);

पूर्णांक __vdso_घड़ी_समय_लो(घड़ीid_t घड़ी, काष्ठा __kernel_बारpec *ts)
अणु
	वापस __cvdso_घड़ी_समय_लो(घड़ी, ts);
पूर्ण

पूर्णांक घड़ी_समय_लो(घड़ीid_t, काष्ठा __kernel_बारpec *)
	__attribute__((weak, alias("__vdso_clock_gettime")));

पूर्णांक __vdso_घड़ी_getres(घड़ीid_t घड़ी,
			काष्ठा __kernel_बारpec *res)
अणु
	वापस __cvdso_घड़ी_getres(घड़ी, res);
पूर्ण
पूर्णांक घड़ी_getres(घड़ीid_t, काष्ठा __kernel_बारpec *)
	__attribute__((weak, alias("__vdso_clock_getres")));

#अन्यथा
/* i386 only */
बाह्य पूर्णांक __vdso_घड़ी_समय_लो(घड़ीid_t घड़ी, काष्ठा old_बारpec32 *ts);
बाह्य पूर्णांक __vdso_घड़ी_getres(घड़ीid_t घड़ी, काष्ठा old_बारpec32 *res);

पूर्णांक __vdso_घड़ी_समय_लो(घड़ीid_t घड़ी, काष्ठा old_बारpec32 *ts)
अणु
	वापस __cvdso_घड़ी_समय_लो32(घड़ी, ts);
पूर्ण

पूर्णांक घड़ी_समय_लो(घड़ीid_t, काष्ठा old_बारpec32 *)
	__attribute__((weak, alias("__vdso_clock_gettime")));

पूर्णांक __vdso_घड़ी_समय_लो64(घड़ीid_t घड़ी, काष्ठा __kernel_बारpec *ts)
अणु
	वापस __cvdso_घड़ी_समय_लो(घड़ी, ts);
पूर्ण

पूर्णांक घड़ी_समय_लो64(घड़ीid_t, काष्ठा __kernel_बारpec *)
	__attribute__((weak, alias("__vdso_clock_gettime64")));

पूर्णांक __vdso_घड़ी_getres(घड़ीid_t घड़ी, काष्ठा old_बारpec32 *res)
अणु
	वापस __cvdso_घड़ी_getres_समय32(घड़ी, res);
पूर्ण

पूर्णांक घड़ी_getres(घड़ीid_t, काष्ठा old_बारpec32 *)
	__attribute__((weak, alias("__vdso_clock_getres")));
#पूर्ण_अगर
