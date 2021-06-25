<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2016 NXP Semiconductors
 */

#समावेश <linux/kernel.h>
#समावेश <linux/suspend.h>
#समावेश <linux/पन.स>

अटल पूर्णांक imx25_suspend_enter(suspend_state_t state)
अणु
	अगर (!IS_ENABLED(CONFIG_PM))
		वापस 0;

	चयन (state) अणु
	हाल PM_SUSPEND_MEM:
		cpu_करो_idle();
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops imx25_suspend_ops = अणु
	.enter = imx25_suspend_enter,
	.valid = suspend_valid_only_mem,
पूर्ण;

व्योम __init imx25_pm_init(व्योम)
अणु
	suspend_set_ops(&imx25_suspend_ops);
पूर्ण
