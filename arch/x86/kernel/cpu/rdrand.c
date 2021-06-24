<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of the Linux kernel.
 *
 * Copyright (c) 2011, Intel Corporation
 * Authors: Fenghua Yu <fenghua.yu@पूर्णांकel.com>,
 *          H. Peter Anvin <hpa@linux.पूर्णांकel.com>
 */

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/archअक्रमom.h>
#समावेश <यंत्र/sections.h>

अटल पूर्णांक __init x86_rdअक्रम_setup(अक्षर *s)
अणु
	setup_clear_cpu_cap(X86_FEATURE_RDRAND);
	setup_clear_cpu_cap(X86_FEATURE_RDSEED);
	वापस 1;
पूर्ण
__setup("nordrand", x86_rdअक्रम_setup);

/*
 * RDRAND has Built-In-Self-Test (BIST) that runs on every invocation.
 * Run the inकाष्ठाion a few बार as a sanity check.
 * If it fails, it is simple to disable RDRAND here.
 */
#घोषणा SANITY_CHECK_LOOPS 8

#अगर_घोषित CONFIG_ARCH_RANDOM
व्योम x86_init_rdअक्रम(काष्ठा cpuinfo_x86 *c)
अणु
	अचिन्हित पूर्णांक changed = 0;
	अचिन्हित दीर्घ पंचांगp, prev;
	पूर्णांक i;

	अगर (!cpu_has(c, X86_FEATURE_RDRAND))
		वापस;

	क्रम (i = 0; i < SANITY_CHECK_LOOPS; i++) अणु
		अगर (!rdअक्रम_दीर्घ(&पंचांगp)) अणु
			clear_cpu_cap(c, X86_FEATURE_RDRAND);
			pr_warn_once("rdrand: disabled\n");
			वापस;
		पूर्ण
	पूर्ण

	/*
	 * Stupid sanity-check whether RDRAND करोes *actually* generate
	 * some at least अक्रमom-looking data.
	 */
	prev = पंचांगp;
	क्रम (i = 0; i < SANITY_CHECK_LOOPS; i++) अणु
		अगर (rdअक्रम_दीर्घ(&पंचांगp)) अणु
			अगर (prev != पंचांगp)
				changed++;

			prev = पंचांगp;
		पूर्ण
	पूर्ण

	अगर (WARN_ON_ONCE(!changed))
		pr_emerg(
"RDRAND gives funky smelling output, might consider not using it by booting with \"nordrand\"");

पूर्ण
#पूर्ण_अगर
