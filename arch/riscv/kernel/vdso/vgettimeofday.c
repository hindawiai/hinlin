<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copied from arch/arm64/kernel/vdso/vसमय_लोofday.c
 *
 * Copyright (C) 2018 ARM Ltd.
 * Copyright (C) 2020 SiFive
 */

#समावेश <linux/समय.स>
#समावेश <linux/types.h>

बाह्य
पूर्णांक __vdso_घड़ी_समय_लो(घड़ीid_t घड़ी, काष्ठा __kernel_बारpec *ts);
पूर्णांक __vdso_घड़ी_समय_लो(घड़ीid_t घड़ी, काष्ठा __kernel_बारpec *ts)
अणु
	वापस __cvdso_घड़ी_समय_लो(घड़ी, ts);
पूर्ण

बाह्य
पूर्णांक __vdso_समय_लोofday(काष्ठा __kernel_old_समयval *tv, काष्ठा समयzone *tz);
पूर्णांक __vdso_समय_लोofday(काष्ठा __kernel_old_समयval *tv, काष्ठा समयzone *tz)
अणु
	वापस __cvdso_समय_लोofday(tv, tz);
पूर्ण

बाह्य
पूर्णांक __vdso_घड़ी_getres(घड़ीid_t घड़ी_id, काष्ठा __kernel_बारpec *res);
पूर्णांक __vdso_घड़ी_getres(घड़ीid_t घड़ी_id, काष्ठा __kernel_बारpec *res)
अणु
	वापस __cvdso_घड़ी_getres(घड़ी_id, res);
पूर्ण
