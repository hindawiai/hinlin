<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of the Linux kernel.
 *
 * Copyright (c) 2011-2014, Intel Corporation
 * Authors: Fenghua Yu <fenghua.yu@पूर्णांकel.com>,
 *          H. Peter Anvin <hpa@linux.पूर्णांकel.com>
 */

#अगर_अघोषित ASM_X86_ARCHRANDOM_H
#घोषणा ASM_X86_ARCHRANDOM_H

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/cpufeature.h>

#घोषणा RDRAND_RETRY_LOOPS	10

/* Unconditional execution of RDRAND and RDSEED */

अटल अंतरभूत bool __must_check rdअक्रम_दीर्घ(अचिन्हित दीर्घ *v)
अणु
	bool ok;
	अचिन्हित पूर्णांक retry = RDRAND_RETRY_LOOPS;
	करो अणु
		यंत्र अस्थिर("rdrand %[out]"
			     CC_SET(c)
			     : CC_OUT(c) (ok), [out] "=r" (*v));
		अगर (ok)
			वापस true;
	पूर्ण जबतक (--retry);
	वापस false;
पूर्ण

अटल अंतरभूत bool __must_check rdअक्रम_पूर्णांक(अचिन्हित पूर्णांक *v)
अणु
	bool ok;
	अचिन्हित पूर्णांक retry = RDRAND_RETRY_LOOPS;
	करो अणु
		यंत्र अस्थिर("rdrand %[out]"
			     CC_SET(c)
			     : CC_OUT(c) (ok), [out] "=r" (*v));
		अगर (ok)
			वापस true;
	पूर्ण जबतक (--retry);
	वापस false;
पूर्ण

अटल अंतरभूत bool __must_check rdseed_दीर्घ(अचिन्हित दीर्घ *v)
अणु
	bool ok;
	यंत्र अस्थिर("rdseed %[out]"
		     CC_SET(c)
		     : CC_OUT(c) (ok), [out] "=r" (*v));
	वापस ok;
पूर्ण

अटल अंतरभूत bool __must_check rdseed_पूर्णांक(अचिन्हित पूर्णांक *v)
अणु
	bool ok;
	यंत्र अस्थिर("rdseed %[out]"
		     CC_SET(c)
		     : CC_OUT(c) (ok), [out] "=r" (*v));
	वापस ok;
पूर्ण

/*
 * These are the generic पूर्णांकerfaces; they must not be declared अगर the
 * stubs in <linux/अक्रमom.h> are to be invoked,
 * i.e. CONFIG_ARCH_RANDOM is not defined.
 */
#अगर_घोषित CONFIG_ARCH_RANDOM

अटल अंतरभूत bool __must_check arch_get_अक्रमom_दीर्घ(अचिन्हित दीर्घ *v)
अणु
	वापस अटल_cpu_has(X86_FEATURE_RDRAND) ? rdअक्रम_दीर्घ(v) : false;
पूर्ण

अटल अंतरभूत bool __must_check arch_get_अक्रमom_पूर्णांक(अचिन्हित पूर्णांक *v)
अणु
	वापस अटल_cpu_has(X86_FEATURE_RDRAND) ? rdअक्रम_पूर्णांक(v) : false;
पूर्ण

अटल अंतरभूत bool __must_check arch_get_अक्रमom_seed_दीर्घ(अचिन्हित दीर्घ *v)
अणु
	वापस अटल_cpu_has(X86_FEATURE_RDSEED) ? rdseed_दीर्घ(v) : false;
पूर्ण

अटल अंतरभूत bool __must_check arch_get_अक्रमom_seed_पूर्णांक(अचिन्हित पूर्णांक *v)
अणु
	वापस अटल_cpu_has(X86_FEATURE_RDSEED) ? rdseed_पूर्णांक(v) : false;
पूर्ण

बाह्य व्योम x86_init_rdअक्रम(काष्ठा cpuinfo_x86 *c);

#अन्यथा  /* !CONFIG_ARCH_RANDOM */

अटल अंतरभूत व्योम x86_init_rdअक्रम(काष्ठा cpuinfo_x86 *c) अणु पूर्ण

#पूर्ण_अगर  /* !CONFIG_ARCH_RANDOM */

#पूर्ण_अगर /* ASM_X86_ARCHRANDOM_H */
