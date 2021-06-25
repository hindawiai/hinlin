<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * psr.h: This file holds the macros क्रम masking off various parts of
 *        the processor status रेजिस्टर on the Sparc. This is valid
 *        क्रम Version 8. On the V9 this is नामd to the PSTATE
 *        रेजिस्टर and its members are accessed as fields like
 *        PSTATE.PRIV क्रम the current CPU privilege level.
 *
 * Copyright (C) 1994 David S. Miller (davem@caip.rutgers.edu)
 */
#अगर_अघोषित __LINUX_SPARC_PSR_H
#घोषणा __LINUX_SPARC_PSR_H

#समावेश <uapi/यंत्र/psr.h>


#अगर_अघोषित __ASSEMBLY__
/* Get the %psr रेजिस्टर. */
अटल अंतरभूत अचिन्हित पूर्णांक get_psr(व्योम)
अणु
	अचिन्हित पूर्णांक psr;
	__यंत्र__ __अस्थिर__(
		"rd	%%psr, %0\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
	: "=r" (psr)
	: /* no inमाला_दो */
	: "memory");

	वापस psr;
पूर्ण

अटल अंतरभूत व्योम put_psr(अचिन्हित पूर्णांक new_psr)
अणु
	__यंत्र__ __अस्थिर__(
		"wr	%0, 0x0, %%psr\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
	: /* no outमाला_दो */
	: "r" (new_psr)
	: "memory", "cc");
पूर्ण

/* Get the %fsr रेजिस्टर.  Be careful, make sure the भग्नing poपूर्णांक
 * enable bit is set in the %psr when you execute this or you will
 * incur a trap.
 */

बाह्य अचिन्हित पूर्णांक fsr_storage;

अटल अंतरभूत अचिन्हित पूर्णांक get_fsr(व्योम)
अणु
	अचिन्हित पूर्णांक fsr = 0;

	__यंत्र__ __अस्थिर__(
		"st	%%fsr, %1\n\t"
		"ld	%1, %0\n\t"
	: "=r" (fsr)
	: "m" (fsr_storage));

	वापस fsr;
पूर्ण

#पूर्ण_अगर /* !(__ASSEMBLY__) */

#पूर्ण_अगर /* !(__LINUX_SPARC_PSR_H) */
