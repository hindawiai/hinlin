<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * linux/arch/arm/include/यंत्र/neon.h
 *
 * Copyright (C) 2013 Linaro Ltd <ard.biesheuvel@linaro.org>
 */

#समावेश <यंत्र/hwcap.h>

#घोषणा cpu_has_neon()		(!!(elf_hwcap & HWCAP_NEON))

#अगर_घोषित __ARM_NEON__

/*
 * If you are affected by the BUILD_BUG below, it probably means that you are
 * using NEON code /and/ calling the kernel_neon_begin() function from the same
 * compilation unit. To prevent issues that may arise from GCC reordering or
 * generating(1) NEON inकाष्ठाions outside of these begin/end functions, the
 * only supported way of using NEON code in the kernel is by isolating it in a
 * separate compilation unit, and calling it from another unit from inside a
 * kernel_neon_begin/kernel_neon_end pair.
 *
 * (1) Current GCC (4.7) might generate NEON inकाष्ठाions at O3 level अगर
 *     -mpfu=neon is set.
 */

#घोषणा kernel_neon_begin() \
	BUILD_BUG_ON_MSG(1, "kernel_neon_begin() called from NEON code")

#अन्यथा
व्योम kernel_neon_begin(व्योम);
#पूर्ण_अगर
व्योम kernel_neon_end(व्योम);
