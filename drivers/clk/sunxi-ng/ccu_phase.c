<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Maxime Ripard
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/spinlock.h>

#समावेश "ccu_phase.h"

अटल पूर्णांक ccu_phase_get_phase(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_phase *phase = hw_to_ccu_phase(hw);
	काष्ठा clk_hw *parent, *gअक्रमparent;
	अचिन्हित पूर्णांक parent_rate, gअक्रमparent_rate;
	u16 step, parent_भाग;
	u32 reg;
	u8 delay;

	reg = पढ़ोl(phase->common.base + phase->common.reg);
	delay = (reg >> phase->shअगरt);
	delay &= (1 << phase->width) - 1;

	अगर (!delay)
		वापस 180;

	/* Get our parent घड़ी, it's the one that can adjust its rate */
	parent = clk_hw_get_parent(hw);
	अगर (!parent)
		वापस -EINVAL;

	/* And its rate */
	parent_rate = clk_hw_get_rate(parent);
	अगर (!parent_rate)
		वापस -EINVAL;

	/* Now, get our parent's parent (most likely some PLL) */
	gअक्रमparent = clk_hw_get_parent(parent);
	अगर (!gअक्रमparent)
		वापस -EINVAL;

	/* And its rate */
	gअक्रमparent_rate = clk_hw_get_rate(gअक्रमparent);
	अगर (!gअक्रमparent_rate)
		वापस -EINVAL;

	/* Get our parent घड़ी भागider */
	parent_भाग = gअक्रमparent_rate / parent_rate;

	step = DIV_ROUND_CLOSEST(360, parent_भाग);
	वापस delay * step;
पूर्ण

अटल पूर्णांक ccu_phase_set_phase(काष्ठा clk_hw *hw, पूर्णांक degrees)
अणु
	काष्ठा ccu_phase *phase = hw_to_ccu_phase(hw);
	काष्ठा clk_hw *parent, *gअक्रमparent;
	अचिन्हित पूर्णांक parent_rate, gअक्रमparent_rate;
	अचिन्हित दीर्घ flags;
	u32 reg;
	u8 delay;

	/* Get our parent घड़ी, it's the one that can adjust its rate */
	parent = clk_hw_get_parent(hw);
	अगर (!parent)
		वापस -EINVAL;

	/* And its rate */
	parent_rate = clk_hw_get_rate(parent);
	अगर (!parent_rate)
		वापस -EINVAL;

	/* Now, get our parent's parent (most likely some PLL) */
	gअक्रमparent = clk_hw_get_parent(parent);
	अगर (!gअक्रमparent)
		वापस -EINVAL;

	/* And its rate */
	gअक्रमparent_rate = clk_hw_get_rate(gअक्रमparent);
	अगर (!gअक्रमparent_rate)
		वापस -EINVAL;

	अगर (degrees != 180) अणु
		u16 step, parent_भाग;

		/* Get our parent भागider */
		parent_भाग = gअक्रमparent_rate / parent_rate;

		/*
		 * We can only outphase the घड़ीs by multiple of the
		 * PLL's period.
		 *
		 * Since our parent घड़ी is only a भागider, and the
		 * क्रमmula to get the outphasing in degrees is deg =
		 * 360 * delta / period
		 *
		 * If we simplअगरy this क्रमmula, we can see that the
		 * only thing that we're concerned about is the number
		 * of period we want to outphase our घड़ी from, and
		 * the भागider set by our parent घड़ी.
		 */
		step = DIV_ROUND_CLOSEST(360, parent_भाग);
		delay = DIV_ROUND_CLOSEST(degrees, step);
	पूर्ण अन्यथा अणु
		delay = 0;
	पूर्ण

	spin_lock_irqsave(phase->common.lock, flags);
	reg = पढ़ोl(phase->common.base + phase->common.reg);
	reg &= ~GENMASK(phase->width + phase->shअगरt - 1, phase->shअगरt);
	ग_लिखोl(reg | (delay << phase->shअगरt),
	       phase->common.base + phase->common.reg);
	spin_unlock_irqrestore(phase->common.lock, flags);

	वापस 0;
पूर्ण

स्थिर काष्ठा clk_ops ccu_phase_ops = अणु
	.get_phase	= ccu_phase_get_phase,
	.set_phase	= ccu_phase_set_phase,
पूर्ण;
