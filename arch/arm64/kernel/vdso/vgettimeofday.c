<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ARM64 userspace implementations of समय_लोofday() and similar.
 *
 * Copyright (C) 2018 ARM Limited
 *
 */

पूर्णांक __kernel_घड़ी_समय_लो(घड़ीid_t घड़ी,
			   काष्ठा __kernel_बारpec *ts)
अणु
	वापस __cvdso_घड़ी_समय_लो(घड़ी, ts);
पूर्ण

पूर्णांक __kernel_समय_लोofday(काष्ठा __kernel_old_समयval *tv,
			  काष्ठा समयzone *tz)
अणु
	वापस __cvdso_समय_लोofday(tv, tz);
पूर्ण

पूर्णांक __kernel_घड़ी_getres(घड़ीid_t घड़ी_id,
			  काष्ठा __kernel_बारpec *res)
अणु
	वापस __cvdso_घड़ी_getres(घड़ी_id, res);
पूर्ण
