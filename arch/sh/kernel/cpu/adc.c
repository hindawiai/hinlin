<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/sh/kernel/adc.c -- SH3 on-chip ADC support
 *
 *  Copyright (C) 2004  Andriy Skulysh <askulysh@image.kiev.ua>
 */

#समावेश <linux/module.h>
#समावेश <यंत्र/adc.h>
#समावेश <यंत्र/पन.स>


पूर्णांक adc_single(अचिन्हित पूर्णांक channel)
अणु
	पूर्णांक off;
	अचिन्हित अक्षर csr;

	अगर (channel >= 8) वापस -1;

	off = (channel & 0x03) << 2;

	csr = __raw_पढ़ोb(ADCSR);
	csr = channel | ADCSR_ADST | ADCSR_CKS;
	__raw_ग_लिखोb(csr, ADCSR);

	करो अणु
		csr = __raw_पढ़ोb(ADCSR);
	पूर्ण जबतक ((csr & ADCSR_ADF) == 0);

	csr &= ~(ADCSR_ADF | ADCSR_ADST);
	__raw_ग_लिखोb(csr, ADCSR);

	वापस (((__raw_पढ़ोb(ADDRAH + off) << 8) |
		__raw_पढ़ोb(ADDRAL + off)) >> 6);
पूर्ण

EXPORT_SYMBOL(adc_single);
