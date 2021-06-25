<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Powerpc userspace implementations of समय_लोofday() and similar.
 */
#समावेश <linux/types.h>

पूर्णांक __c_kernel_घड़ी_समय_लो(घड़ीid_t घड़ी, काष्ठा old_बारpec32 *ts,
			     स्थिर काष्ठा vdso_data *vd)
अणु
	वापस __cvdso_घड़ी_समय_लो32_data(vd, घड़ी, ts);
पूर्ण

पूर्णांक __c_kernel_घड़ी_समय_लो64(घड़ीid_t घड़ी, काष्ठा __kernel_बारpec *ts,
			       स्थिर काष्ठा vdso_data *vd)
अणु
	वापस __cvdso_घड़ी_समय_लो_data(vd, घड़ी, ts);
पूर्ण

पूर्णांक __c_kernel_समय_लोofday(काष्ठा __kernel_old_समयval *tv, काष्ठा समयzone *tz,
			    स्थिर काष्ठा vdso_data *vd)
अणु
	वापस __cvdso_समय_लोofday_data(vd, tv, tz);
पूर्ण

पूर्णांक __c_kernel_घड़ी_getres(घड़ीid_t घड़ी_id, काष्ठा old_बारpec32 *res,
			    स्थिर काष्ठा vdso_data *vd)
अणु
	वापस __cvdso_घड़ी_getres_समय32_data(vd, घड़ी_id, res);
पूर्ण

__kernel_old_समय_प्रकार __c_kernel_समय(__kernel_old_समय_प्रकार *समय, स्थिर काष्ठा vdso_data *vd)
अणु
	वापस __cvdso_समय_data(vd, समय);
पूर्ण
