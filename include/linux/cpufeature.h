<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2014 Linaro Ltd. <ard.biesheuvel@linaro.org>
 */

#अगर_अघोषित __LINUX_CPUFEATURE_H
#घोषणा __LINUX_CPUFEATURE_H

#अगर_घोषित CONFIG_GENERIC_CPU_AUTOPROBE

#समावेश <linux/init.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <यंत्र/cpufeature.h>

/*
 * Macros imported from <यंत्र/cpufeature.h>:
 * - cpu_feature(x)		ordinal value of feature called 'x'
 * - cpu_have_feature(u32 n)	whether feature #n is available
 * - MAX_CPU_FEATURES		upper bound क्रम feature ordinal values
 * Optional:
 * - CPU_FEATURE_TYPEFMT	क्रमmat string fragment क्रम prपूर्णांकing the cpu type
 * - CPU_FEATURE_TYPEVAL	set of values matching the क्रमmat string above
 */

#अगर_अघोषित CPU_FEATURE_TYPEFMT
#घोषणा CPU_FEATURE_TYPEFMT	"%s"
#पूर्ण_अगर

#अगर_अघोषित CPU_FEATURE_TYPEVAL
#घोषणा CPU_FEATURE_TYPEVAL	ELF_PLATFORM
#पूर्ण_अगर

/*
 * Use module_cpu_feature_match(feature, module_init_function) to
 * declare that
 * a) the module shall be probed upon discovery of CPU feature 'feature'
 *    (typically at boot समय using udev)
 * b) the module must not be loaded अगर CPU feature 'feature' is not present
 *    (not even by manual insmod).
 *
 * For a list of legal values क्रम 'feature', please consult the file
 * 'asm/cpufeature.h' of your favorite architecture.
 */
#घोषणा module_cpu_feature_match(x, __initfunc)			\
अटल काष्ठा cpu_feature स्थिर __maybe_unused cpu_feature_match_ ## x[] = \
	अणु अणु .feature = cpu_feature(x) पूर्ण, अणु पूर्ण पूर्ण;			\
MODULE_DEVICE_TABLE(cpu, cpu_feature_match_ ## x);		\
								\
अटल पूर्णांक __init cpu_feature_match_ ## x ## _init(व्योम)	\
अणु								\
	अगर (!cpu_have_feature(cpu_feature(x)))			\
		वापस -ENODEV;					\
	वापस __initfunc();					\
पूर्ण								\
module_init(cpu_feature_match_ ## x ## _init)

#पूर्ण_अगर
#पूर्ण_अगर
