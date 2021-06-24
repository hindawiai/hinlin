<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright IBM Corp. 2001,2008
 *
 * This file contains the IRQ specअगरic code क्रम hvc_console
 *
 */

#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "hvc_console.h"

अटल irqवापस_t hvc_handle_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	/* अगर hvc_poll request a repoll, then kick the hvcd thपढ़ो */
	अगर (hvc_poll(dev_instance))
		hvc_kick();

	/*
	 * We're safe to always वापस IRQ_HANDLED as the hvcd thपढ़ो will
	 * iterate through each hvc_काष्ठा.
	 */
	वापस IRQ_HANDLED;
पूर्ण

/*
 * For IRQ based प्रणालीs these callbacks can be used
 */
पूर्णांक notअगरier_add_irq(काष्ठा hvc_काष्ठा *hp, पूर्णांक irq)
अणु
	पूर्णांक rc;

	अगर (!irq) अणु
		hp->irq_requested = 0;
		वापस 0;
	पूर्ण
	rc = request_irq(irq, hvc_handle_पूर्णांकerrupt, hp->flags,
			"hvc_console", hp);
	अगर (!rc)
		hp->irq_requested = 1;
	वापस rc;
पूर्ण

व्योम notअगरier_del_irq(काष्ठा hvc_काष्ठा *hp, पूर्णांक irq)
अणु
	अगर (!hp->irq_requested)
		वापस;
	मुक्त_irq(irq, hp);
	hp->irq_requested = 0;
पूर्ण

व्योम notअगरier_hangup_irq(काष्ठा hvc_काष्ठा *hp, पूर्णांक irq)
अणु
	notअगरier_del_irq(hp, irq);
पूर्ण
