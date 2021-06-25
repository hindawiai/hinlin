<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Maxime Ripard
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/spinlock.h>

#समावेश "ccu_frac.h"

bool ccu_frac_helper_is_enabled(काष्ठा ccu_common *common,
				काष्ठा ccu_frac_पूर्णांकernal *cf)
अणु
	अगर (!(common->features & CCU_FEATURE_FRACTIONAL))
		वापस false;

	वापस !(पढ़ोl(common->base + common->reg) & cf->enable);
पूर्ण

व्योम ccu_frac_helper_enable(काष्ठा ccu_common *common,
			    काष्ठा ccu_frac_पूर्णांकernal *cf)
अणु
	अचिन्हित दीर्घ flags;
	u32 reg;

	अगर (!(common->features & CCU_FEATURE_FRACTIONAL))
		वापस;

	spin_lock_irqsave(common->lock, flags);
	reg = पढ़ोl(common->base + common->reg);
	ग_लिखोl(reg & ~cf->enable, common->base + common->reg);
	spin_unlock_irqrestore(common->lock, flags);
पूर्ण

व्योम ccu_frac_helper_disable(काष्ठा ccu_common *common,
			     काष्ठा ccu_frac_पूर्णांकernal *cf)
अणु
	अचिन्हित दीर्घ flags;
	u32 reg;

	अगर (!(common->features & CCU_FEATURE_FRACTIONAL))
		वापस;

	spin_lock_irqsave(common->lock, flags);
	reg = पढ़ोl(common->base + common->reg);
	ग_लिखोl(reg | cf->enable, common->base + common->reg);
	spin_unlock_irqrestore(common->lock, flags);
पूर्ण

bool ccu_frac_helper_has_rate(काष्ठा ccu_common *common,
			      काष्ठा ccu_frac_पूर्णांकernal *cf,
			      अचिन्हित दीर्घ rate)
अणु
	अगर (!(common->features & CCU_FEATURE_FRACTIONAL))
		वापस false;

	वापस (cf->rates[0] == rate) || (cf->rates[1] == rate);
पूर्ण

अचिन्हित दीर्घ ccu_frac_helper_पढ़ो_rate(काष्ठा ccu_common *common,
					काष्ठा ccu_frac_पूर्णांकernal *cf)
अणु
	u32 reg;

	pr_debug("%s: Read fractional\n", clk_hw_get_name(&common->hw));

	अगर (!(common->features & CCU_FEATURE_FRACTIONAL))
		वापस 0;

	pr_debug("%s: clock is fractional (rates %lu and %lu)\n",
		 clk_hw_get_name(&common->hw), cf->rates[0], cf->rates[1]);

	reg = पढ़ोl(common->base + common->reg);

	pr_debug("%s: clock reg is 0x%x (select is 0x%x)\n",
		 clk_hw_get_name(&common->hw), reg, cf->select);

	वापस (reg & cf->select) ? cf->rates[1] : cf->rates[0];
पूर्ण

पूर्णांक ccu_frac_helper_set_rate(काष्ठा ccu_common *common,
			     काष्ठा ccu_frac_पूर्णांकernal *cf,
			     अचिन्हित दीर्घ rate, u32 lock)
अणु
	अचिन्हित दीर्घ flags;
	u32 reg, sel;

	अगर (!(common->features & CCU_FEATURE_FRACTIONAL))
		वापस -EINVAL;

	अगर (cf->rates[0] == rate)
		sel = 0;
	अन्यथा अगर (cf->rates[1] == rate)
		sel = cf->select;
	अन्यथा
		वापस -EINVAL;

	spin_lock_irqsave(common->lock, flags);
	reg = पढ़ोl(common->base + common->reg);
	reg &= ~cf->select;
	ग_लिखोl(reg | sel, common->base + common->reg);
	spin_unlock_irqrestore(common->lock, flags);

	ccu_helper_रुको_क्रम_lock(common, lock);

	वापस 0;
पूर्ण
