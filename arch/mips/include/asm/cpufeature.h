<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * CPU feature definitions क्रम module loading, used by
 * module_cpu_feature_match(), see uapi/यंत्र/hwcap.h क्रम MIPS CPU features.
 */

#अगर_अघोषित __ASM_CPUFEATURE_H
#घोषणा __ASM_CPUFEATURE_H

#समावेश <uapi/यंत्र/hwcap.h>
#समावेश <यंत्र/elf.h>

#घोषणा MAX_CPU_FEATURES (8 * माप(elf_hwcap))

#घोषणा cpu_feature(x)		ilog2(HWCAP_ ## x)

अटल अंतरभूत bool cpu_have_feature(अचिन्हित पूर्णांक num)
अणु
	वापस elf_hwcap & (1UL << num);
पूर्ण

#पूर्ण_अगर /* __ASM_CPUFEATURE_H */
