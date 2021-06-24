<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MIPS64 and compat userspace implementations of समय_लोofday()
 * and similar.
 *
 * Copyright (C) 2015 Imagination Technologies
 * Copyright (C) 2018 ARM Limited
 *
 */
#समावेश <linux/समय.स>
#समावेश <linux/types.h>

#अगर _MIPS_SIM != _MIPS_SIM_ABI64
पूर्णांक __vdso_घड़ी_समय_लो(घड़ीid_t घड़ी,
			 काष्ठा old_बारpec32 *ts)
अणु
	वापस __cvdso_घड़ी_समय_लो32(घड़ी, ts);
पूर्ण

#अगर_घोषित CONFIG_MIPS_CLOCK_VSYSCALL

/*
 * This is behind the अगरdef so that we करोn't provide the symbol when there's no
 * possibility of there being a usable घड़ीsource, because there's nothing we
 * can करो without it. When libc fails the symbol lookup it should fall back on
 * the standard syscall path.
 */
पूर्णांक __vdso_समय_लोofday(काष्ठा __kernel_old_समयval *tv,
			काष्ठा समयzone *tz)
अणु
	वापस __cvdso_समय_लोofday(tv, tz);
पूर्ण

#पूर्ण_अगर /* CONFIG_MIPS_CLOCK_VSYSCALL */

पूर्णांक __vdso_घड़ी_getres(घड़ीid_t घड़ी_id,
			काष्ठा old_बारpec32 *res)
अणु
	वापस __cvdso_घड़ी_getres_समय32(घड़ी_id, res);
पूर्ण

पूर्णांक __vdso_घड़ी_समय_लो64(घड़ीid_t घड़ी,
			   काष्ठा __kernel_बारpec *ts)
अणु
	वापस __cvdso_घड़ी_समय_लो(घड़ी, ts);
पूर्ण

#अन्यथा

पूर्णांक __vdso_घड़ी_समय_लो(घड़ीid_t घड़ी,
			 काष्ठा __kernel_बारpec *ts)
अणु
	वापस __cvdso_घड़ी_समय_लो(घड़ी, ts);
पूर्ण

#अगर_घोषित CONFIG_MIPS_CLOCK_VSYSCALL

/*
 * This is behind the अगरdef so that we करोn't provide the symbol when there's no
 * possibility of there being a usable घड़ीsource, because there's nothing we
 * can करो without it. When libc fails the symbol lookup it should fall back on
 * the standard syscall path.
 */
पूर्णांक __vdso_समय_लोofday(काष्ठा __kernel_old_समयval *tv,
			काष्ठा समयzone *tz)
अणु
	वापस __cvdso_समय_लोofday(tv, tz);
पूर्ण

#पूर्ण_अगर /* CONFIG_MIPS_CLOCK_VSYSCALL */

पूर्णांक __vdso_घड़ी_getres(घड़ीid_t घड़ी_id,
			काष्ठा __kernel_बारpec *res)
अणु
	वापस __cvdso_घड़ी_getres(घड़ी_id, res);
पूर्ण

#पूर्ण_अगर
