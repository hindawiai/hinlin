<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "../../../../lib/vdso/gettimeofday.c"
#समावेश "vdso.h"

पूर्णांक __s390_vdso_समय_लोofday(काष्ठा __kernel_old_समयval *tv,
			     काष्ठा समयzone *tz)
अणु
	वापस __cvdso_समय_लोofday(tv, tz);
पूर्ण

पूर्णांक __s390_vdso_घड़ी_समय_लो(घड़ीid_t घड़ी, काष्ठा __kernel_बारpec *ts)
अणु
	वापस __cvdso_घड़ी_समय_लो(घड़ी, ts);
पूर्ण

पूर्णांक __s390_vdso_घड़ी_getres(घड़ीid_t घड़ी, काष्ठा __kernel_बारpec *ts)
अणु
	वापस __cvdso_घड़ी_getres(घड़ी, ts);
पूर्ण
