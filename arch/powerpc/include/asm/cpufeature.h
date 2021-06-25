<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * CPU feature definitions क्रम module loading, used by
 * module_cpu_feature_match(), see यंत्र/cputable.h क्रम घातerpc CPU features.
 *
 * Copyright 2016 Alastair D'Silva, IBM Corporation.
 */

#अगर_अघोषित __ASM_POWERPC_CPUFEATURE_H
#घोषणा __ASM_POWERPC_CPUFEATURE_H

#समावेश <यंत्र/cputable.h>

/* Keep these in step with घातerpc/include/यंत्र/cputable.h */
#घोषणा MAX_CPU_FEATURES (2 * 32)

/*
 * Currently we करोn't have a need क्रम any of the feature bits defined in
 * cpu_user_features. When we करो, they should be defined such as:
 *
 * #घोषणा PPC_MODULE_FEATURE_32 (ilog2(PPC_FEATURE_32))
 */

#घोषणा PPC_MODULE_FEATURE_VEC_CRYPTO			(32 + ilog2(PPC_FEATURE2_VEC_CRYPTO))

#घोषणा cpu_feature(x)		(x)

अटल अंतरभूत bool cpu_have_feature(अचिन्हित पूर्णांक num)
अणु
	अगर (num < 32)
		वापस !!(cur_cpu_spec->cpu_user_features & 1UL << num);
	अन्यथा
		वापस !!(cur_cpu_spec->cpu_user_features2 & 1UL << (num - 32));
पूर्ण

#पूर्ण_अगर /* __ASM_POWERPC_CPUFEATURE_H */
