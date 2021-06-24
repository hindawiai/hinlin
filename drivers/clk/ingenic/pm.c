<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 Paul Cercueil <paul@crapouillou.net>
 */

#समावेश "cgu.h"
#समावेश "pm.h"

#समावेश <linux/पन.स>
#समावेश <linux/syscore_ops.h>

#घोषणा CGU_REG_LCR		0x04

#घोषणा LCR_LOW_POWER_MODE	BIT(0)

अटल व्योम __iomem * __maybe_unused ingenic_cgu_base;

अटल पूर्णांक __maybe_unused ingenic_cgu_pm_suspend(व्योम)
अणु
	u32 val = पढ़ोl(ingenic_cgu_base + CGU_REG_LCR);

	ग_लिखोl(val | LCR_LOW_POWER_MODE, ingenic_cgu_base + CGU_REG_LCR);

	वापस 0;
पूर्ण

अटल व्योम __maybe_unused ingenic_cgu_pm_resume(व्योम)
अणु
	u32 val = पढ़ोl(ingenic_cgu_base + CGU_REG_LCR);

	ग_लिखोl(val & ~LCR_LOW_POWER_MODE, ingenic_cgu_base + CGU_REG_LCR);
पूर्ण

अटल काष्ठा syscore_ops __maybe_unused ingenic_cgu_pm_ops = अणु
	.suspend = ingenic_cgu_pm_suspend,
	.resume = ingenic_cgu_pm_resume,
पूर्ण;

व्योम ingenic_cgu_रेजिस्टर_syscore_ops(काष्ठा ingenic_cgu *cgu)
अणु
	अगर (IS_ENABLED(CONFIG_PM_SLEEP)) अणु
		ingenic_cgu_base = cgu->base;
		रेजिस्टर_syscore_ops(&ingenic_cgu_pm_ops);
	पूर्ण
पूर्ण
