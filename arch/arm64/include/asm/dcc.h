<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2014-2015 The Linux Foundation. All rights reserved.
 *
 * A call to __dcc_अक्षर_लो() or __dcc_अक्षर_दो() is typically followed by
 * a call to __dcc_माला_लोtatus().  We want to make sure that the CPU करोes
 * not speculative पढ़ो the DCC status beक्रमe executing the पढ़ो or ग_लिखो
 * inकाष्ठाion.  That's what the ISBs are क्रम.
 *
 * The 'volatile' ensures that the compiler करोes not cache the status bits,
 * and instead पढ़ोs the DCC रेजिस्टर every समय.
 */
#अगर_अघोषित __ASM_DCC_H
#घोषणा __ASM_DCC_H

#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/sysreg.h>

अटल अंतरभूत u32 __dcc_माला_लोtatus(व्योम)
अणु
	वापस पढ़ो_sysreg(mdccsr_el0);
पूर्ण

अटल अंतरभूत अक्षर __dcc_अक्षर_लो(व्योम)
अणु
	अक्षर c = पढ़ो_sysreg(dbgdtrrx_el0);
	isb();

	वापस c;
पूर्ण

अटल अंतरभूत व्योम __dcc_अक्षर_दो(अक्षर c)
अणु
	/*
	 * The typecast is to make असलolutely certain that 'c' is
	 * zero-extended.
	 */
	ग_लिखो_sysreg((अचिन्हित अक्षर)c, dbgdtrtx_el0);
	isb();
पूर्ण

#पूर्ण_अगर
