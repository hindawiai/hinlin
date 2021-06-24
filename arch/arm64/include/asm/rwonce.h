<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2020 Google LLC.
 */
#अगर_अघोषित __ASM_RWONCE_H
#घोषणा __ASM_RWONCE_H

#अगर_घोषित CONFIG_LTO

#समावेश <linux/compiler_types.h>
#समावेश <यंत्र/alternative-macros.h>

#अगर_अघोषित BUILD_VDSO

#अगर_घोषित CONFIG_AS_HAS_LDAPR
#घोषणा __LOAD_RCPC(sfx, regs...)					\
	ALTERNATIVE(							\
		"ldar"	#sfx "\t" #regs,				\
		".arch_extension rcpc\n"				\
		"ldapr"	#sfx "\t" #regs,				\
	ARM64_HAS_LDAPR)
#अन्यथा
#घोषणा __LOAD_RCPC(sfx, regs...)	"ldar" #sfx "\t" #regs
#पूर्ण_अगर /* CONFIG_AS_HAS_LDAPR */

/*
 * When building with LTO, there is an increased risk of the compiler
 * converting an address dependency headed by a READ_ONCE() invocation
 * पूर्णांकo a control dependency and consequently allowing क्रम harmful
 * reordering by the CPU.
 *
 * Ensure that such transक्रमmations are harmless by overriding the generic
 * READ_ONCE() definition with one that provides RCpc acquire semantics
 * when building with LTO.
 */
#घोषणा __READ_ONCE(x)							\
(अणु									\
	typeof(&(x)) __x = &(x);					\
	पूर्णांक atomic = 1;							\
	जोड़ अणु __unqual_scalar_typeof(*__x) __val; अक्षर __c[1]; पूर्ण __u;	\
	चयन (माप(x)) अणु						\
	हाल 1:								\
		यंत्र अस्थिर(__LOAD_RCPC(b, %w0, %1)			\
			: "=r" (*(__u8 *)__u.__c)			\
			: "Q" (*__x) : "memory");			\
		अवरोध;							\
	हाल 2:								\
		यंत्र अस्थिर(__LOAD_RCPC(h, %w0, %1)			\
			: "=r" (*(__u16 *)__u.__c)			\
			: "Q" (*__x) : "memory");			\
		अवरोध;							\
	हाल 4:								\
		यंत्र अस्थिर(__LOAD_RCPC(, %w0, %1)			\
			: "=r" (*(__u32 *)__u.__c)			\
			: "Q" (*__x) : "memory");			\
		अवरोध;							\
	हाल 8:								\
		यंत्र अस्थिर(__LOAD_RCPC(, %0, %1)			\
			: "=r" (*(__u64 *)__u.__c)			\
			: "Q" (*__x) : "memory");			\
		अवरोध;							\
	शेष:							\
		atomic = 0;						\
	पूर्ण								\
	atomic ? (typeof(*__x))__u.__val : (*(अस्थिर typeof(__x))__x);\
पूर्ण)

#पूर्ण_अगर	/* !BUILD_VDSO */
#पूर्ण_अगर	/* CONFIG_LTO */

#समावेश <यंत्र-generic/rwonce.h>

#पूर्ण_अगर	/* __ASM_RWONCE_H */
