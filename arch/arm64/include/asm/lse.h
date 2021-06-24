<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_LSE_H
#घोषणा __ASM_LSE_H

#समावेश <यंत्र/atomic_ll_sc.h>

#अगर_घोषित CONFIG_ARM64_LSE_ATOMICS

#घोषणा __LSE_PREAMBLE	".arch_extension lse\n"

#समावेश <linux/compiler_types.h>
#समावेश <linux/export.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/stringअगरy.h>
#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/atomic_lse.h>
#समावेश <यंत्र/cpucaps.h>

बाह्य काष्ठा अटल_key_false cpu_hwcap_keys[ARM64_NCAPS];
बाह्य काष्ठा अटल_key_false arm64_स्थिर_caps_पढ़ोy;

अटल अंतरभूत bool प्रणाली_uses_lse_atomics(व्योम)
अणु
	वापस (अटल_branch_likely(&arm64_स्थिर_caps_पढ़ोy)) &&
		अटल_branch_likely(&cpu_hwcap_keys[ARM64_HAS_LSE_ATOMICS]);
पूर्ण

#घोषणा __lse_ll_sc_body(op, ...)					\
(अणु									\
	प्रणाली_uses_lse_atomics() ?					\
		__lse_##op(__VA_ARGS__) :				\
		__ll_sc_##op(__VA_ARGS__);				\
पूर्ण)

/* In-line patching at runसमय */
#घोषणा ARM64_LSE_ATOMIC_INSN(llsc, lse)				\
	ALTERNATIVE(llsc, __LSE_PREAMBLE lse, ARM64_HAS_LSE_ATOMICS)

#अन्यथा	/* CONFIG_ARM64_LSE_ATOMICS */

अटल अंतरभूत bool प्रणाली_uses_lse_atomics(व्योम) अणु वापस false; पूर्ण

#घोषणा __lse_ll_sc_body(op, ...)		__ll_sc_##op(__VA_ARGS__)

#घोषणा ARM64_LSE_ATOMIC_INSN(llsc, lse)	llsc

#पूर्ण_अगर	/* CONFIG_ARM64_LSE_ATOMICS */
#पूर्ण_अगर	/* __ASM_LSE_H */
