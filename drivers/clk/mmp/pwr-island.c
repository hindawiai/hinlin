<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MMP PMU घातer island support
 *
 * Copyright (C) 2020 Lubomir Rपूर्णांकel <lkundrak@v3.sk>
 */

#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>

#समावेश "clk.h"

#घोषणा to_mmp_pm_करोमुख्य(genpd) container_of(genpd, काष्ठा mmp_pm_करोमुख्य, genpd)

काष्ठा mmp_pm_करोमुख्य अणु
	काष्ठा generic_pm_करोमुख्य genpd;
	व्योम __iomem *reg;
	spinlock_t *lock;
	u32 घातer_on;
	u32 reset;
	u32 घड़ी_enable;
	अचिन्हित पूर्णांक flags;
पूर्ण;

अटल पूर्णांक mmp_pm_करोमुख्य_घातer_on(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	काष्ठा mmp_pm_करोमुख्य *pm_करोमुख्य = to_mmp_pm_करोमुख्य(genpd);
	अचिन्हित दीर्घ flags = 0;
	u32 val;

	अगर (pm_करोमुख्य->lock)
		spin_lock_irqsave(pm_करोमुख्य->lock, flags);

	val = पढ़ोl(pm_करोमुख्य->reg);

	/* Turn on the घातer island */
	val |= pm_करोमुख्य->घातer_on;
	ग_लिखोl(val, pm_करोमुख्य->reg);

	/* Disable isolation */
	val |= 0x100;
	ग_लिखोl(val, pm_करोमुख्य->reg);

	/* Some blocks need to be reset after a घातer up */
	अगर (pm_करोमुख्य->reset || pm_करोमुख्य->घड़ी_enable) अणु
		u32 after_घातer_on = val;

		val &= ~pm_करोमुख्य->reset;
		ग_लिखोl(val, pm_करोमुख्य->reg);

		val |= pm_करोमुख्य->घड़ी_enable;
		ग_लिखोl(val, pm_करोमुख्य->reg);

		val |= pm_करोमुख्य->reset;
		ग_लिखोl(val, pm_करोमुख्य->reg);

		ग_लिखोl(after_घातer_on, pm_करोमुख्य->reg);
	पूर्ण

	अगर (pm_करोमुख्य->lock)
		spin_unlock_irqrestore(pm_करोमुख्य->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक mmp_pm_करोमुख्य_घातer_off(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	काष्ठा mmp_pm_करोमुख्य *pm_करोमुख्य = to_mmp_pm_करोमुख्य(genpd);
	अचिन्हित दीर्घ flags = 0;
	u32 val;

	अगर (pm_करोमुख्य->flags & MMP_PM_DOMAIN_NO_DISABLE)
		वापस 0;

	अगर (pm_करोमुख्य->lock)
		spin_lock_irqsave(pm_करोमुख्य->lock, flags);

	/* Turn off and isolate the the घातer island. */
	val = पढ़ोl(pm_करोमुख्य->reg);
	val &= ~pm_करोमुख्य->घातer_on;
	val &= ~0x100;
	ग_लिखोl(val, pm_करोमुख्य->reg);

	अगर (pm_करोमुख्य->lock)
		spin_unlock_irqrestore(pm_करोमुख्य->lock, flags);

	वापस 0;
पूर्ण

काष्ठा generic_pm_करोमुख्य *mmp_pm_करोमुख्य_रेजिस्टर(स्थिर अक्षर *name,
		व्योम __iomem *reg,
		u32 घातer_on, u32 reset, u32 घड़ी_enable,
		अचिन्हित पूर्णांक flags, spinlock_t *lock)
अणु
	काष्ठा mmp_pm_करोमुख्य *pm_करोमुख्य;

	pm_करोमुख्य = kzalloc(माप(*pm_करोमुख्य), GFP_KERNEL);
	अगर (!pm_करोमुख्य)
		वापस ERR_PTR(-ENOMEM);

	pm_करोमुख्य->reg = reg;
	pm_करोमुख्य->घातer_on = घातer_on;
	pm_करोमुख्य->reset = reset;
	pm_करोमुख्य->घड़ी_enable = घड़ी_enable;
	pm_करोमुख्य->flags = flags;
	pm_करोमुख्य->lock = lock;

	pm_genpd_init(&pm_करोमुख्य->genpd, शून्य, true);
	pm_करोमुख्य->genpd.name = name;
	pm_करोमुख्य->genpd.घातer_on = mmp_pm_करोमुख्य_घातer_on;
	pm_करोमुख्य->genpd.घातer_off = mmp_pm_करोमुख्य_घातer_off;

	वापस &pm_करोमुख्य->genpd;
पूर्ण
