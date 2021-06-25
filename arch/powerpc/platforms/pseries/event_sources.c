<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2001 Dave Engebretsen IBM Corporation
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_irq.h>

#समावेश "pseries.h"

व्योम request_event_sources_irqs(काष्ठा device_node *np,
				irq_handler_t handler,
				स्थिर अक्षर *name)
अणु
	पूर्णांक i, virq, rc;

	क्रम (i = 0; i < 16; i++) अणु
		virq = of_irq_get(np, i);
		अगर (virq < 0)
			वापस;
		अगर (WARN(!virq, "event-sources: Unable to allocate "
			        "interrupt number for %pOF\n", np))
			जारी;

		rc = request_irq(virq, handler, 0, name, शून्य);
		अगर (WARN(rc, "event-sources: Unable to request interrupt %d for %pOF\n",
		    virq, np))
			वापस;
	पूर्ण
पूर्ण
