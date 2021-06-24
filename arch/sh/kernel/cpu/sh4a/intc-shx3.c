<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Shared support क्रम SH-X3 पूर्णांकerrupt controllers.
 *
 *  Copyright (C) 2009 - 2010  Paul Mundt
 */
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/init.h>

#घोषणा INTACK		0xfe4100b8
#घोषणा INTACKCLR	0xfe4100bc
#घोषणा INTC_USERIMASK	0xfe411000

#अगर_घोषित CONFIG_INTC_BALANCING
अचिन्हित पूर्णांक irq_lookup(अचिन्हित पूर्णांक irq)
अणु
	वापस __raw_पढ़ोl(INTACK) & 1 ? irq : NO_IRQ_IGNORE;
पूर्ण

व्योम irq_finish(अचिन्हित पूर्णांक irq)
अणु
	__raw_ग_लिखोl(irq2evt(irq), INTACKCLR);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init shx3_irq_setup(व्योम)
अणु
	वापस रेजिस्टर_पूर्णांकc_userimask(INTC_USERIMASK);
पूर्ण
arch_initcall(shx3_irq_setup);
