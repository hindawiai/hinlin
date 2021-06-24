<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_POWERPC_CPU_HAS_FEATURE_H
#घोषणा __ASM_POWERPC_CPU_HAS_FEATURE_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/bug.h>
#समावेश <यंत्र/cputable.h>

अटल __always_अंतरभूत bool early_cpu_has_feature(अचिन्हित दीर्घ feature)
अणु
	वापस !!((CPU_FTRS_ALWAYS & feature) ||
		  (CPU_FTRS_POSSIBLE & cur_cpu_spec->cpu_features & feature));
पूर्ण

#अगर_घोषित CONFIG_JUMP_LABEL_FEATURE_CHECKS
#समावेश <linux/jump_label.h>

#घोषणा NUM_CPU_FTR_KEYS	BITS_PER_LONG

बाह्य काष्ठा अटल_key_true cpu_feature_keys[NUM_CPU_FTR_KEYS];

अटल __always_अंतरभूत bool cpu_has_feature(अचिन्हित दीर्घ feature)
अणु
	पूर्णांक i;

#अगर_अघोषित __clang__ /* clang can't cope with this */
	BUILD_BUG_ON(!__builtin_स्थिरant_p(feature));
#पूर्ण_अगर

#अगर_घोषित CONFIG_JUMP_LABEL_FEATURE_CHECK_DEBUG
	अगर (!अटल_key_initialized) अणु
		prपूर्णांकk("Warning! cpu_has_feature() used prior to jump label init!\n");
		dump_stack();
		वापस early_cpu_has_feature(feature);
	पूर्ण
#पूर्ण_अगर

	अगर (CPU_FTRS_ALWAYS & feature)
		वापस true;

	अगर (!(CPU_FTRS_POSSIBLE & feature))
		वापस false;

	i = __builtin_ctzl(feature);
	वापस अटल_branch_likely(&cpu_feature_keys[i]);
पूर्ण
#अन्यथा
अटल __always_अंतरभूत bool cpu_has_feature(अचिन्हित दीर्घ feature)
अणु
	वापस early_cpu_has_feature(feature);
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* __ASM_POWERPC_CPU_HAS_FEATURE_H */
