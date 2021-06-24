<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Dummy IRQ handler driver.
 *
 * This module only रेजिस्टरs itself as a handler that is specअगरied to it
 * by the 'irq' parameter.
 *
 * The sole purpose of this module is to help with debugging of प्रणालीs on
 * which spurious IRQs would happen on disabled IRQ vector.
 *
 * Copyright (C) 2013 Jiri Kosina
 */

#समावेश <linux/module.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>

अटल पूर्णांक irq = -1;

अटल irqवापस_t dummy_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	अटल पूर्णांक count = 0;

	अगर (count == 0) अणु
		prपूर्णांकk(KERN_INFO "dummy-irq: interrupt occurred on IRQ %d\n",
				irq);
		count++;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक __init dummy_irq_init(व्योम)
अणु
	अगर (irq < 0) अणु
		prपूर्णांकk(KERN_ERR "dummy-irq: no IRQ given.  Use irq=N\n");
		वापस -EIO;
	पूर्ण
	अगर (request_irq(irq, &dummy_पूर्णांकerrupt, IRQF_SHARED, "dummy_irq", &irq)) अणु
		prपूर्णांकk(KERN_ERR "dummy-irq: cannot register IRQ %d\n", irq);
		वापस -EIO;
	पूर्ण
	prपूर्णांकk(KERN_INFO "dummy-irq: registered for IRQ %d\n", irq);
	वापस 0;
पूर्ण

अटल व्योम __निकास dummy_irq_निकास(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "dummy-irq unloaded\n");
	मुक्त_irq(irq, &irq);
पूर्ण

module_init(dummy_irq_init);
module_निकास(dummy_irq_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jiri Kosina");
module_param_hw(irq, uपूर्णांक, irq, 0444);
MODULE_PARM_DESC(irq, "The IRQ to register for");
MODULE_DESCRIPTION("Dummy IRQ handler driver");
