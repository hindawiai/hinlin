<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2010 Freescale Semiconductor, Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/suspend.h>
#समावेश <linux/पन.स>
#समावेश "pm.h"

अटल पूर्णांक mxs_suspend_enter(suspend_state_t state)
अणु
	चयन (state) अणु
	हाल PM_SUSPEND_MEM:
		cpu_करो_idle();
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops mxs_suspend_ops = अणु
	.enter = mxs_suspend_enter,
	.valid = suspend_valid_only_mem,
पूर्ण;

व्योम __init mxs_pm_init(व्योम)
अणु
	suspend_set_ops(&mxs_suspend_ops);
पूर्ण
