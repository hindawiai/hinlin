<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2008 IBM Corp. 
 *
 * Based on arch/घातerpc/platक्रमms/pasemi/idle.c: 
 * Copyright (C) 2006-2007 PA Semi, Inc
 *
 * Added by: Jerone Young <jyoung5@us.ibm.com>
 */

#समावेश <linux/of.h>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/machdep.h>

अटल पूर्णांक mode_spin;

अटल व्योम ppc44x_idle(व्योम)
अणु
	अचिन्हित दीर्घ msr_save;

	msr_save = mfmsr();
	/* set रुको state MSR */
	mपंचांगsr(msr_save|MSR_WE|MSR_EE|MSR_CE|MSR_DE);
	isync();
	/* वापस to initial state */
	mपंचांगsr(msr_save);
	isync();
पूर्ण

पूर्णांक __init ppc44x_idle_init(व्योम)
अणु
	अगर (!mode_spin) अणु
		/* If we are not setting spin mode 
                   then we set to रुको mode */
		ppc_md.घातer_save = &ppc44x_idle;
	पूर्ण

	वापस 0;
पूर्ण

arch_initcall(ppc44x_idle_init);

अटल पूर्णांक __init idle_param(अक्षर *p)
अणु 

	अगर (!म_भेद("spin", p)) अणु
		mode_spin = 1;
		ppc_md.घातer_save = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

early_param("idle", idle_param);
