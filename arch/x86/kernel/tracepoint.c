<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Code क्रम supporting irq vector tracepoपूर्णांकs.
 *
 * Copyright (C) 2013 Seiji Aguchi <seiji.aguchi@hds.com>
 *
 */
#समावेश <linux/jump_label.h>
#समावेश <linux/atomic.h>

#समावेश <यंत्र/hw_irq.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/trace/exceptions.h>
#समावेश <यंत्र/trace/irq_vectors.h>

DEFINE_STATIC_KEY_FALSE(trace_pagefault_key);

पूर्णांक trace_pagefault_reg(व्योम)
अणु
	अटल_branch_inc(&trace_pagefault_key);
	वापस 0;
पूर्ण

व्योम trace_pagefault_unreg(व्योम)
अणु
	अटल_branch_dec(&trace_pagefault_key);
पूर्ण
