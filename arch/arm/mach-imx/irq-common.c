<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) BitBox Ltd 2010
 */

#समावेश <linux/module.h>
#समावेश <linux/irq.h>
#समावेश <linux/platक्रमm_data/asoc-imx-ssi.h>

#समावेश "irq-common.h"

पूर्णांक mxc_set_irq_fiq(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक type)
अणु
	काष्ठा irq_chip_generic *gc;
	काष्ठा mxc_extra_irq *exirq;
	पूर्णांक ret;

	ret = -ENOSYS;

	gc = irq_get_chip_data(irq);
	अगर (gc && gc->निजी) अणु
		exirq = gc->निजी;
		अगर (exirq->set_irq_fiq) अणु
			काष्ठा irq_data *d = irq_get_irq_data(irq);
			ret = exirq->set_irq_fiq(irqd_to_hwirq(d), type);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(mxc_set_irq_fiq);
