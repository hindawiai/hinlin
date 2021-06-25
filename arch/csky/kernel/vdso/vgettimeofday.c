<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/समय.स>
#समावेश <linux/types.h>

पूर्णांक __vdso_घड़ी_समय_लो(घड़ीid_t घड़ी,
			 काष्ठा old_बारpec32 *ts)
अणु
	वापस __cvdso_घड़ी_समय_लो32(घड़ी, ts);
पूर्ण

पूर्णांक __vdso_घड़ी_समय_लो64(घड़ीid_t घड़ी,
			   काष्ठा __kernel_बारpec *ts)
अणु
	वापस __cvdso_घड़ी_समय_लो(घड़ी, ts);
पूर्ण

पूर्णांक __vdso_समय_लोofday(काष्ठा __kernel_old_समयval *tv,
			काष्ठा समयzone *tz)
अणु
	वापस __cvdso_समय_लोofday(tv, tz);
पूर्ण

पूर्णांक __vdso_घड़ी_getres(घड़ीid_t घड़ी_id,
			काष्ठा old_बारpec32 *res)
अणु
	वापस __cvdso_घड़ी_getres_समय32(घड़ी_id, res);
पूर्ण
