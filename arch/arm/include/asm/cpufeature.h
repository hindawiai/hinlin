<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2017 Linaro Ltd. <ard.biesheuvel@linaro.org>
 */

#अगर_अघोषित __ASM_CPUFEATURE_H
#घोषणा __ASM_CPUFEATURE_H

#समावेश <linux/log2.h>
#समावेश <यंत्र/hwcap.h>

/*
 * Due to the fact that ELF_HWCAP is a 32-bit type on ARM, and given the number
 * of optional CPU features it defines, ARM's CPU hardware capability bits have
 * been distributed over separate elf_hwcap and elf_hwcap2 variables, each of
 * which covers a subset of the available CPU features.
 *
 * Currently, only a few of those are suitable क्रम स्वतःmatic module loading
 * (which is the primary use हाल of this facility) and those happen to be all
 * covered by HWCAP2. So let's only cover those via the cpu_feature()
 * convenience macro क्रम now (which is used by module_cpu_feature_match()).
 * However, all capabilities are exposed via the modalias, and can be matched
 * using an explicit MODULE_DEVICE_TABLE() that uses __hwcap_feature() directly.
 */
#घोषणा MAX_CPU_FEATURES	64
#घोषणा __hwcap_feature(x)	ilog2(HWCAP_ ## x)
#घोषणा __hwcap2_feature(x)	(32 + ilog2(HWCAP2_ ## x))
#घोषणा cpu_feature(x)		__hwcap2_feature(x)

अटल अंतरभूत bool cpu_have_feature(अचिन्हित पूर्णांक num)
अणु
	वापस num < 32 ? elf_hwcap & BIT(num) : elf_hwcap2 & BIT(num - 32);
पूर्ण

#पूर्ण_अगर
