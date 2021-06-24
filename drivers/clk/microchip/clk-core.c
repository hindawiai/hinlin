<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Purna Chandra Mandal,<purna.mandal@microchip.com>
 * Copyright (C) 2015 Microchip Technology Inc.  All rights reserved.
 */
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <यंत्र/mach-pic32/pic32.h>
#समावेश <यंत्र/traps.h>

#समावेश "clk-core.h"

/* OSCCON Reg fields */
#घोषणा OSC_CUR_MASK		0x07
#घोषणा OSC_CUR_SHIFT		12
#घोषणा OSC_NEW_MASK		0x07
#घोषणा OSC_NEW_SHIFT		8
#घोषणा OSC_SWEN		BIT(0)

/* SPLLCON Reg fields */
#घोषणा PLL_RANGE_MASK		0x07
#घोषणा PLL_RANGE_SHIFT		0
#घोषणा PLL_ICLK_MASK		0x01
#घोषणा PLL_ICLK_SHIFT		7
#घोषणा PLL_IDIV_MASK		0x07
#घोषणा PLL_IDIV_SHIFT		8
#घोषणा PLL_ODIV_MASK		0x07
#घोषणा PLL_ODIV_SHIFT		24
#घोषणा PLL_MULT_MASK		0x7F
#घोषणा PLL_MULT_SHIFT		16
#घोषणा PLL_MULT_MAX		128
#घोषणा PLL_ODIV_MIN		1
#घोषणा PLL_ODIV_MAX		5

/* Peripheral Bus Clock Reg Fields */
#घोषणा PB_DIV_MASK		0x7f
#घोषणा PB_DIV_SHIFT		0
#घोषणा PB_DIV_READY		BIT(11)
#घोषणा PB_DIV_ENABLE		BIT(15)
#घोषणा PB_DIV_MAX		128
#घोषणा PB_DIV_MIN		0

/* Reference Oscillator Control Reg fields */
#घोषणा REFO_SEL_MASK		0x0f
#घोषणा REFO_SEL_SHIFT		0
#घोषणा REFO_ACTIVE		BIT(8)
#घोषणा REFO_DIVSW_EN		BIT(9)
#घोषणा REFO_OE			BIT(12)
#घोषणा REFO_ON			BIT(15)
#घोषणा REFO_DIV_SHIFT		16
#घोषणा REFO_DIV_MASK		0x7fff

/* Reference Oscillator Trim Register Fields */
#घोषणा REFO_TRIM_REG		0x10
#घोषणा REFO_TRIM_MASK		0x1ff
#घोषणा REFO_TRIM_SHIFT		23
#घोषणा REFO_TRIM_MAX		511

/* Mux Slew Control Register fields */
#घोषणा SLEW_BUSY		BIT(0)
#घोषणा SLEW_DOWNEN		BIT(1)
#घोषणा SLEW_UPEN		BIT(2)
#घोषणा SLEW_DIV		0x07
#घोषणा SLEW_DIV_SHIFT		8
#घोषणा SLEW_SYSDIV		0x0f
#घोषणा SLEW_SYSDIV_SHIFT	20

/* Clock Poll Timeout */
#घोषणा LOCK_TIMEOUT_US         USEC_PER_MSEC

/* SoC specअगरic घड़ी needed during SPLL घड़ी rate चयन */
अटल काष्ठा clk_hw *pic32_sclk_hw;

/* add inकाष्ठाion pipeline delay जबतक CPU घड़ी is in-transition. */
#घोषणा cpu_nop5()			\
करो अणु					\
	__यंत्र__ __अस्थिर__("nop");	\
	__यंत्र__ __अस्थिर__("nop");	\
	__यंत्र__ __अस्थिर__("nop");	\
	__यंत्र__ __अस्थिर__("nop");	\
	__यंत्र__ __अस्थिर__("nop");	\
पूर्ण जबतक (0)

/* Perpheral bus घड़ीs */
काष्ठा pic32_periph_clk अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *ctrl_reg;
	काष्ठा pic32_clk_common *core;
पूर्ण;

#घोषणा clkhw_to_pbclk(_hw)	container_of(_hw, काष्ठा pic32_periph_clk, hw)

अटल पूर्णांक pbclk_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा pic32_periph_clk *pb = clkhw_to_pbclk(hw);

	वापस पढ़ोl(pb->ctrl_reg) & PB_DIV_ENABLE;
पूर्ण

अटल पूर्णांक pbclk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा pic32_periph_clk *pb = clkhw_to_pbclk(hw);

	ग_लिखोl(PB_DIV_ENABLE, PIC32_SET(pb->ctrl_reg));
	वापस 0;
पूर्ण

अटल व्योम pbclk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा pic32_periph_clk *pb = clkhw_to_pbclk(hw);

	ग_लिखोl(PB_DIV_ENABLE, PIC32_CLR(pb->ctrl_reg));
पूर्ण

अटल अचिन्हित दीर्घ calc_best_भागided_rate(अचिन्हित दीर्घ rate,
					    अचिन्हित दीर्घ parent_rate,
					    u32 भागider_max,
					    u32 भागider_min)
अणु
	अचिन्हित दीर्घ भागided_rate, भागided_rate_करोwn, best_rate;
	अचिन्हित दीर्घ भाग, भाग_up;

	/* eq. clk_rate = parent_rate / भागider.
	 *
	 * Find best भागider to produce बंदst of target भागided rate.
	 */
	भाग = parent_rate / rate;
	भाग = clamp_val(भाग, भागider_min, भागider_max);
	भाग_up = clamp_val(भाग + 1, भागider_min, भागider_max);

	भागided_rate = parent_rate / भाग;
	भागided_rate_करोwn = parent_rate / भाग_up;
	अगर (असल(rate - भागided_rate_करोwn) < असल(rate - भागided_rate))
		best_rate = भागided_rate_करोwn;
	अन्यथा
		best_rate = भागided_rate;

	वापस best_rate;
पूर्ण

अटल अंतरभूत u32 pbclk_पढ़ो_pbभाग(काष्ठा pic32_periph_clk *pb)
अणु
	वापस ((पढ़ोl(pb->ctrl_reg) >> PB_DIV_SHIFT) & PB_DIV_MASK) + 1;
पूर्ण

अटल अचिन्हित दीर्घ pbclk_recalc_rate(काष्ठा clk_hw *hw,
				       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा pic32_periph_clk *pb = clkhw_to_pbclk(hw);

	वापस parent_rate / pbclk_पढ़ो_pbभाग(pb);
पूर्ण

अटल दीर्घ pbclk_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			     अचिन्हित दीर्घ *parent_rate)
अणु
	वापस calc_best_भागided_rate(rate, *parent_rate,
				      PB_DIV_MAX, PB_DIV_MIN);
पूर्ण

अटल पूर्णांक pbclk_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा pic32_periph_clk *pb = clkhw_to_pbclk(hw);
	अचिन्हित दीर्घ flags;
	u32 v, भाग;
	पूर्णांक err;

	/* check & रुको क्रम DIV_READY */
	err = पढ़ोl_poll_समयout(pb->ctrl_reg, v, v & PB_DIV_READY,
				 1, LOCK_TIMEOUT_US);
	अगर (err)
		वापस err;

	/* calculate clkभाग and best rate */
	भाग = DIV_ROUND_CLOSEST(parent_rate, rate);

	spin_lock_irqsave(&pb->core->reg_lock, flags);

	/* apply new भाग */
	v = पढ़ोl(pb->ctrl_reg);
	v &= ~PB_DIV_MASK;
	v |= (भाग - 1);

	pic32_syskey_unlock();

	ग_लिखोl(v, pb->ctrl_reg);

	spin_unlock_irqrestore(&pb->core->reg_lock, flags);

	/* रुको again क्रम DIV_READY */
	err = पढ़ोl_poll_समयout(pb->ctrl_reg, v, v & PB_DIV_READY,
				 1, LOCK_TIMEOUT_US);
	अगर (err)
		वापस err;

	/* confirm that new भाग is applied correctly */
	वापस (pbclk_पढ़ो_pbभाग(pb) == भाग) ? 0 : -EBUSY;
पूर्ण

स्थिर काष्ठा clk_ops pic32_pbclk_ops = अणु
	.enable		= pbclk_enable,
	.disable	= pbclk_disable,
	.is_enabled	= pbclk_is_enabled,
	.recalc_rate	= pbclk_recalc_rate,
	.round_rate	= pbclk_round_rate,
	.set_rate	= pbclk_set_rate,
पूर्ण;

काष्ठा clk *pic32_periph_clk_रेजिस्टर(स्थिर काष्ठा pic32_periph_clk_data *desc,
				      काष्ठा pic32_clk_common *core)
अणु
	काष्ठा pic32_periph_clk *pbclk;
	काष्ठा clk *clk;

	pbclk = devm_kzalloc(core->dev, माप(*pbclk), GFP_KERNEL);
	अगर (!pbclk)
		वापस ERR_PTR(-ENOMEM);

	pbclk->hw.init = &desc->init_data;
	pbclk->core = core;
	pbclk->ctrl_reg = desc->ctrl_reg + core->iobase;

	clk = devm_clk_रेजिस्टर(core->dev, &pbclk->hw);
	अगर (IS_ERR(clk)) अणु
		dev_err(core->dev, "%s: clk_register() failed\n", __func__);
		devm_kमुक्त(core->dev, pbclk);
	पूर्ण

	वापस clk;
पूर्ण

/* Reference oscillator operations */
काष्ठा pic32_ref_osc अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *ctrl_reg;
	स्थिर u32 *parent_map;
	काष्ठा pic32_clk_common *core;
पूर्ण;

#घोषणा clkhw_to_refosc(_hw)	container_of(_hw, काष्ठा pic32_ref_osc, hw)

अटल पूर्णांक roclk_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा pic32_ref_osc *refo = clkhw_to_refosc(hw);

	वापस पढ़ोl(refo->ctrl_reg) & REFO_ON;
पूर्ण

अटल पूर्णांक roclk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा pic32_ref_osc *refo = clkhw_to_refosc(hw);

	ग_लिखोl(REFO_ON | REFO_OE, PIC32_SET(refo->ctrl_reg));
	वापस 0;
पूर्ण

अटल व्योम roclk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा pic32_ref_osc *refo = clkhw_to_refosc(hw);

	ग_लिखोl(REFO_ON | REFO_OE, PIC32_CLR(refo->ctrl_reg));
पूर्ण

अटल पूर्णांक roclk_init(काष्ठा clk_hw *hw)
अणु
	/* initialize घड़ी in disabled state */
	roclk_disable(hw);

	वापस 0;
पूर्ण

अटल u8 roclk_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा pic32_ref_osc *refo = clkhw_to_refosc(hw);
	u32 v, i;

	v = (पढ़ोl(refo->ctrl_reg) >> REFO_SEL_SHIFT) & REFO_SEL_MASK;

	अगर (!refo->parent_map)
		वापस v;

	क्रम (i = 0; i < clk_hw_get_num_parents(hw); i++)
		अगर (refo->parent_map[i] == v)
			वापस i;

	वापस -EINVAL;
पूर्ण

अटल अचिन्हित दीर्घ roclk_calc_rate(अचिन्हित दीर्घ parent_rate,
				     u32 roभाग, u32 rotrim)
अणु
	u64 rate64;

	/* fout = fin / [2 * अणुभाग + (trim / 512)पूर्ण]
	 *	= fin * 512 / [1024 * भाग + 2 * trim]
	 *	= fin * 256 / (512 * भाग + trim)
	 *	= (fin << 8) / ((भाग << 9) + trim)
	 */
	अगर (rotrim) अणु
		roभाग = (roभाग << 9) + rotrim;
		rate64 = parent_rate;
		rate64 <<= 8;
		करो_भाग(rate64, roभाग);
	पूर्ण अन्यथा अगर (roभाग) अणु
		rate64 = parent_rate / (roभाग << 1);
	पूर्ण अन्यथा अणु
		rate64 = parent_rate;
	पूर्ण
	वापस rate64;
पूर्ण

अटल व्योम roclk_calc_भाग_प्रकारrim(अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate,
				u32 *roभाग_p, u32 *rotrim_p)
अणु
	u32 भाग, rotrim, roभाग;
	u64 frac;

	/* Find पूर्णांकeger approximation of भग्नing-poपूर्णांक arithmetic.
	 *      fout = fin / [2 * अणुroभाग + (rotrim / 512)पूर्ण] ... (1)
	 * i.e. fout = fin / 2 * DIV
	 *      whereas DIV = roभाग + (rotrim / 512)
	 *
	 * Since kernel करोes not perक्रमm भग्नing-poपूर्णांक arithmatic so
	 * (rotrim/512) will be zero. And DIV & roभाग will result same.
	 *
	 * ie. fout = (fin * 256) / [(512 * roभाग) + rotrim]  ... from (1)
	 * ie. rotrim = ((fin * 256) / fout) - (512 * DIV)
	 */
	अगर (parent_rate <= rate) अणु
		भाग = 0;
		frac = 0;
		roभाग = 0;
		rotrim = 0;
	पूर्ण अन्यथा अणु
		भाग = parent_rate / (rate << 1);
		frac = parent_rate;
		frac <<= 8;
		करो_भाग(frac, rate);
		frac -= (u64)(भाग << 9);

		roभाग = (भाग > REFO_DIV_MASK) ? REFO_DIV_MASK : भाग;
		rotrim = (frac >= REFO_TRIM_MAX) ? REFO_TRIM_MAX : frac;
	पूर्ण

	अगर (roभाग_p)
		*roभाग_p = roभाग;

	अगर (rotrim_p)
		*rotrim_p = rotrim;
पूर्ण

अटल अचिन्हित दीर्घ roclk_recalc_rate(काष्ठा clk_hw *hw,
				       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा pic32_ref_osc *refo = clkhw_to_refosc(hw);
	u32 v, roभाग, rotrim;

	/* get roभाग */
	v = पढ़ोl(refo->ctrl_reg);
	roभाग = (v >> REFO_DIV_SHIFT) & REFO_DIV_MASK;

	/* get trim */
	v = पढ़ोl(refo->ctrl_reg + REFO_TRIM_REG);
	rotrim = (v >> REFO_TRIM_SHIFT) & REFO_TRIM_MASK;

	वापस roclk_calc_rate(parent_rate, roभाग, rotrim);
पूर्ण

अटल दीर्घ roclk_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			     अचिन्हित दीर्घ *parent_rate)
अणु
	u32 rotrim, roभाग;

	/* calculate भागiders क्रम new rate */
	roclk_calc_भाग_प्रकारrim(rate, *parent_rate, &roभाग, &rotrim);

	/* caclulate new rate (rounding) based on new roभाग & rotrim */
	वापस roclk_calc_rate(*parent_rate, roभाग, rotrim);
पूर्ण

अटल पूर्णांक roclk_determine_rate(काष्ठा clk_hw *hw,
				काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_hw *parent_clk, *best_parent_clk = शून्य;
	अचिन्हित पूर्णांक i, delta, best_delta = -1;
	अचिन्हित दीर्घ parent_rate, best_parent_rate = 0;
	अचिन्हित दीर्घ best = 0, nearest_rate;

	/* find a parent which can generate nearest clkrate >= rate */
	क्रम (i = 0; i < clk_hw_get_num_parents(hw); i++) अणु
		/* get parent */
		parent_clk = clk_hw_get_parent_by_index(hw, i);
		अगर (!parent_clk)
			जारी;

		/* skip अगर parent runs slower than target rate */
		parent_rate = clk_hw_get_rate(parent_clk);
		अगर (req->rate > parent_rate)
			जारी;

		nearest_rate = roclk_round_rate(hw, req->rate, &parent_rate);
		delta = असल(nearest_rate - req->rate);
		अगर ((nearest_rate >= req->rate) && (delta < best_delta)) अणु
			best_parent_clk = parent_clk;
			best_parent_rate = parent_rate;
			best = nearest_rate;
			best_delta = delta;

			अगर (delta == 0)
				अवरोध;
		पूर्ण
	पूर्ण

	/* अगर no match found, retain old rate */
	अगर (!best_parent_clk) अणु
		pr_err("%s:%s, no parent found for rate %lu.\n",
		       __func__, clk_hw_get_name(hw), req->rate);
		वापस clk_hw_get_rate(hw);
	पूर्ण

	pr_debug("%s,rate %lu, best_parent(%s, %lu), best %lu, delta %d\n",
		 clk_hw_get_name(hw), req->rate,
		 clk_hw_get_name(best_parent_clk), best_parent_rate,
		 best, best_delta);

	अगर (req->best_parent_rate)
		req->best_parent_rate = best_parent_rate;

	अगर (req->best_parent_hw)
		req->best_parent_hw = best_parent_clk;

	वापस best;
पूर्ण

अटल पूर्णांक roclk_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा pic32_ref_osc *refo = clkhw_to_refosc(hw);
	अचिन्हित दीर्घ flags;
	u32 v;
	पूर्णांक err;

	अगर (refo->parent_map)
		index = refo->parent_map[index];

	/* रुको until ACTIVE bit is zero or समयout */
	err = पढ़ोl_poll_समयout(refo->ctrl_reg, v, !(v & REFO_ACTIVE),
				 1, LOCK_TIMEOUT_US);
	अगर (err) अणु
		pr_err("%s: poll failed, clk active\n", clk_hw_get_name(hw));
		वापस err;
	पूर्ण

	spin_lock_irqsave(&refo->core->reg_lock, flags);

	pic32_syskey_unlock();

	/* calculate & apply new */
	v = पढ़ोl(refo->ctrl_reg);
	v &= ~(REFO_SEL_MASK << REFO_SEL_SHIFT);
	v |= index << REFO_SEL_SHIFT;

	ग_लिखोl(v, refo->ctrl_reg);

	spin_unlock_irqrestore(&refo->core->reg_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक roclk_set_rate_and_parent(काष्ठा clk_hw *hw,
				     अचिन्हित दीर्घ rate,
				     अचिन्हित दीर्घ parent_rate,
				     u8 index)
अणु
	काष्ठा pic32_ref_osc *refo = clkhw_to_refosc(hw);
	अचिन्हित दीर्घ flags;
	u32 trim, roभाग, v;
	पूर्णांक err;

	/* calculate new roभाग & rotrim क्रम new rate */
	roclk_calc_भाग_प्रकारrim(rate, parent_rate, &roभाग, &trim);

	pr_debug("parent_rate = %lu, rate = %lu, div = %d, trim = %d\n",
		 parent_rate, rate, roभाग, trim);

	/* रुको till source change is active */
	err = पढ़ोl_poll_समयout(refo->ctrl_reg, v,
				 !(v & (REFO_ACTIVE | REFO_DIVSW_EN)),
				 1, LOCK_TIMEOUT_US);
	अगर (err) अणु
		pr_err("%s: poll timedout, clock is still active\n", __func__);
		वापस err;
	पूर्ण

	spin_lock_irqsave(&refo->core->reg_lock, flags);
	v = पढ़ोl(refo->ctrl_reg);

	pic32_syskey_unlock();

	/* apply parent, अगर required */
	अगर (refo->parent_map)
		index = refo->parent_map[index];

	v &= ~(REFO_SEL_MASK << REFO_SEL_SHIFT);
	v |= index << REFO_SEL_SHIFT;

	/* apply RODIV */
	v &= ~(REFO_DIV_MASK << REFO_DIV_SHIFT);
	v |= roभाग << REFO_DIV_SHIFT;
	ग_लिखोl(v, refo->ctrl_reg);

	/* apply ROTRIM */
	v = पढ़ोl(refo->ctrl_reg + REFO_TRIM_REG);
	v &= ~(REFO_TRIM_MASK << REFO_TRIM_SHIFT);
	v |= trim << REFO_TRIM_SHIFT;
	ग_लिखोl(v, refo->ctrl_reg + REFO_TRIM_REG);

	/* enable & activate भागider चयनing */
	ग_लिखोl(REFO_ON | REFO_DIVSW_EN, PIC32_SET(refo->ctrl_reg));

	/* रुको till भागswen is in-progress */
	err = पढ़ोl_poll_समयout_atomic(refo->ctrl_reg, v, !(v & REFO_DIVSW_EN),
					1, LOCK_TIMEOUT_US);
	/* leave the clk gated as it was */
	ग_लिखोl(REFO_ON, PIC32_CLR(refo->ctrl_reg));

	spin_unlock_irqrestore(&refo->core->reg_lock, flags);

	वापस err;
पूर्ण

अटल पूर्णांक roclk_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			  अचिन्हित दीर्घ parent_rate)
अणु
	u8 index = roclk_get_parent(hw);

	वापस roclk_set_rate_and_parent(hw, rate, parent_rate, index);
पूर्ण

स्थिर काष्ठा clk_ops pic32_roclk_ops = अणु
	.enable			= roclk_enable,
	.disable		= roclk_disable,
	.is_enabled		= roclk_is_enabled,
	.get_parent		= roclk_get_parent,
	.set_parent		= roclk_set_parent,
	.determine_rate		= roclk_determine_rate,
	.recalc_rate		= roclk_recalc_rate,
	.set_rate_and_parent	= roclk_set_rate_and_parent,
	.set_rate		= roclk_set_rate,
	.init			= roclk_init,
पूर्ण;

काष्ठा clk *pic32_refo_clk_रेजिस्टर(स्थिर काष्ठा pic32_ref_osc_data *data,
				    काष्ठा pic32_clk_common *core)
अणु
	काष्ठा pic32_ref_osc *refo;
	काष्ठा clk *clk;

	refo = devm_kzalloc(core->dev, माप(*refo), GFP_KERNEL);
	अगर (!refo)
		वापस ERR_PTR(-ENOMEM);

	refo->core = core;
	refo->hw.init = &data->init_data;
	refo->ctrl_reg = data->ctrl_reg + core->iobase;
	refo->parent_map = data->parent_map;

	clk = devm_clk_रेजिस्टर(core->dev, &refo->hw);
	अगर (IS_ERR(clk))
		dev_err(core->dev, "%s: clk_register() failed\n", __func__);

	वापस clk;
पूर्ण

काष्ठा pic32_sys_pll अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *ctrl_reg;
	व्योम __iomem *status_reg;
	u32 lock_mask;
	u32 iभाग; /* PLL iclk भागider, treated fixed */
	काष्ठा pic32_clk_common *core;
पूर्ण;

#घोषणा clkhw_to_spll(_hw)	container_of(_hw, काष्ठा pic32_sys_pll, hw)

अटल अंतरभूत u32 spll_oभाग_प्रकारo_भागider(u32 oभाग)
अणु
	oभाग = clamp_val(oभाग, PLL_ODIV_MIN, PLL_ODIV_MAX);

	वापस 1 << oभाग;
पूर्ण

अटल अचिन्हित दीर्घ spll_calc_mult_भाग(काष्ठा pic32_sys_pll *pll,
					अचिन्हित दीर्घ rate,
					अचिन्हित दीर्घ parent_rate,
					u32 *mult_p, u32 *oभाग_p)
अणु
	u32 mul, भाग, best_mul = 1, best_भाग = 1;
	अचिन्हित दीर्घ new_rate, best_rate = rate;
	अचिन्हित पूर्णांक best_delta = -1, delta, match_found = 0;
	u64 rate64;

	parent_rate /= pll->iभाग;

	क्रम (mul = 1; mul <= PLL_MULT_MAX; mul++) अणु
		क्रम (भाग = PLL_ODIV_MIN; भाग <= PLL_ODIV_MAX; भाग++) अणु
			rate64 = parent_rate;
			rate64 *= mul;
			करो_भाग(rate64, 1 << भाग);
			new_rate = rate64;
			delta = असल(rate - new_rate);
			अगर ((new_rate >= rate) && (delta < best_delta)) अणु
				best_delta = delta;
				best_rate = new_rate;
				best_mul = mul;
				best_भाग = भाग;
				match_found = 1;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!match_found) अणु
		pr_warn("spll: no match found\n");
		वापस 0;
	पूर्ण

	pr_debug("rate %lu, par_rate %lu/mult %u, div %u, best_rate %lu\n",
		 rate, parent_rate, best_mul, best_भाग, best_rate);

	अगर (mult_p)
		*mult_p = best_mul - 1;

	अगर (oभाग_p)
		*oभाग_p = best_भाग;

	वापस best_rate;
पूर्ण

अटल अचिन्हित दीर्घ spll_clk_recalc_rate(काष्ठा clk_hw *hw,
					  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा pic32_sys_pll *pll = clkhw_to_spll(hw);
	अचिन्हित दीर्घ pll_in_rate;
	u32 mult, oभाग, भाग, v;
	u64 rate64;

	v = पढ़ोl(pll->ctrl_reg);
	oभाग = ((v >> PLL_ODIV_SHIFT) & PLL_ODIV_MASK);
	mult = ((v >> PLL_MULT_SHIFT) & PLL_MULT_MASK) + 1;
	भाग = spll_oभाग_प्रकारo_भागider(oभाग);

	/* pll_in_rate = parent_rate / iभाग
	 * pll_out_rate = pll_in_rate * mult / भाग;
	 */
	pll_in_rate = parent_rate / pll->iभाग;
	rate64 = pll_in_rate;
	rate64 *= mult;
	करो_भाग(rate64, भाग);

	वापस rate64;
पूर्ण

अटल दीर्घ spll_clk_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा pic32_sys_pll *pll = clkhw_to_spll(hw);

	वापस spll_calc_mult_भाग(pll, rate, *parent_rate, शून्य, शून्य);
पूर्ण

अटल पूर्णांक spll_clk_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा pic32_sys_pll *pll = clkhw_to_spll(hw);
	अचिन्हित दीर्घ ret, flags;
	u32 mult, oभाग, v;
	पूर्णांक err;

	ret = spll_calc_mult_भाग(pll, rate, parent_rate, &mult, &oभाग);
	अगर (!ret)
		वापस -EINVAL;

	/*
	 * We can't change SPLL counters when it is in-active use
	 * by SYSCLK. So check beक्रमe applying new counters/rate.
	 */

	/* Is spll_clk active parent of sys_clk ? */
	अगर (unlikely(clk_hw_get_parent(pic32_sclk_hw) == hw)) अणु
		pr_err("%s: failed, clk in-use\n", __func__);
		वापस -EBUSY;
	पूर्ण

	spin_lock_irqsave(&pll->core->reg_lock, flags);

	/* apply new multiplier & भागisor */
	v = पढ़ोl(pll->ctrl_reg);
	v &= ~(PLL_MULT_MASK << PLL_MULT_SHIFT);
	v &= ~(PLL_ODIV_MASK << PLL_ODIV_SHIFT);
	v |= (mult << PLL_MULT_SHIFT) | (oभाग << PLL_ODIV_SHIFT);

	/* sys unlock beक्रमe ग_लिखो */
	pic32_syskey_unlock();

	ग_लिखोl(v, pll->ctrl_reg);
	cpu_relax();

	/* insert few nops (5-stage) to ensure CPU करोes not hang */
	cpu_nop5();
	cpu_nop5();

	/* Wait until PLL is locked (maximum 100 usecs). */
	err = पढ़ोl_poll_समयout_atomic(pll->status_reg, v,
					v & pll->lock_mask, 1, 100);
	spin_unlock_irqrestore(&pll->core->reg_lock, flags);

	वापस err;
पूर्ण

/* SPLL घड़ी operation */
स्थिर काष्ठा clk_ops pic32_spll_ops = अणु
	.recalc_rate	= spll_clk_recalc_rate,
	.round_rate	= spll_clk_round_rate,
	.set_rate	= spll_clk_set_rate,
पूर्ण;

काष्ठा clk *pic32_spll_clk_रेजिस्टर(स्थिर काष्ठा pic32_sys_pll_data *data,
				    काष्ठा pic32_clk_common *core)
अणु
	काष्ठा pic32_sys_pll *spll;
	काष्ठा clk *clk;

	spll = devm_kzalloc(core->dev, माप(*spll), GFP_KERNEL);
	अगर (!spll)
		वापस ERR_PTR(-ENOMEM);

	spll->core = core;
	spll->hw.init = &data->init_data;
	spll->ctrl_reg = data->ctrl_reg + core->iobase;
	spll->status_reg = data->status_reg + core->iobase;
	spll->lock_mask = data->lock_mask;

	/* cache PLL iभाग; PLL driver uses it as स्थिरant.*/
	spll->iभाग = (पढ़ोl(spll->ctrl_reg) >> PLL_IDIV_SHIFT) & PLL_IDIV_MASK;
	spll->iभाग += 1;

	clk = devm_clk_रेजिस्टर(core->dev, &spll->hw);
	अगर (IS_ERR(clk))
		dev_err(core->dev, "sys_pll: clk_register() failed\n");

	वापस clk;
पूर्ण

/* System mux घड़ी(aka SCLK) */

काष्ठा pic32_sys_clk अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *mux_reg;
	व्योम __iomem *slew_reg;
	u32 slew_भाग;
	स्थिर u32 *parent_map;
	काष्ठा pic32_clk_common *core;
पूर्ण;

#घोषणा clkhw_to_sys_clk(_hw)	container_of(_hw, काष्ठा pic32_sys_clk, hw)

अटल अचिन्हित दीर्घ sclk_get_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा pic32_sys_clk *sclk = clkhw_to_sys_clk(hw);
	u32 भाग;

	भाग = (पढ़ोl(sclk->slew_reg) >> SLEW_SYSDIV_SHIFT) & SLEW_SYSDIV;
	भाग += 1; /* sys-भाग to भागider */

	वापस parent_rate / भाग;
पूर्ण

अटल दीर्घ sclk_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			    अचिन्हित दीर्घ *parent_rate)
अणु
	वापस calc_best_भागided_rate(rate, *parent_rate, SLEW_SYSDIV, 1);
पूर्ण

अटल पूर्णांक sclk_set_rate(काष्ठा clk_hw *hw,
			 अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा pic32_sys_clk *sclk = clkhw_to_sys_clk(hw);
	अचिन्हित दीर्घ flags;
	u32 v, भाग;
	पूर्णांक err;

	भाग = parent_rate / rate;

	spin_lock_irqsave(&sclk->core->reg_lock, flags);

	/* apply new भाग */
	v = पढ़ोl(sclk->slew_reg);
	v &= ~(SLEW_SYSDIV << SLEW_SYSDIV_SHIFT);
	v |= (भाग - 1) << SLEW_SYSDIV_SHIFT;

	pic32_syskey_unlock();

	ग_लिखोl(v, sclk->slew_reg);

	/* रुको until BUSY is cleared */
	err = पढ़ोl_poll_समयout_atomic(sclk->slew_reg, v,
					!(v & SLEW_BUSY), 1, LOCK_TIMEOUT_US);

	spin_unlock_irqrestore(&sclk->core->reg_lock, flags);

	वापस err;
पूर्ण

अटल u8 sclk_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा pic32_sys_clk *sclk = clkhw_to_sys_clk(hw);
	u32 i, v;

	v = (पढ़ोl(sclk->mux_reg) >> OSC_CUR_SHIFT) & OSC_CUR_MASK;

	अगर (!sclk->parent_map)
		वापस v;

	क्रम (i = 0; i < clk_hw_get_num_parents(hw); i++)
		अगर (sclk->parent_map[i] == v)
			वापस i;
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sclk_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा pic32_sys_clk *sclk = clkhw_to_sys_clk(hw);
	अचिन्हित दीर्घ flags;
	u32 nosc, cosc, v;
	पूर्णांक err;

	spin_lock_irqsave(&sclk->core->reg_lock, flags);

	/* find new_osc */
	nosc = sclk->parent_map ? sclk->parent_map[index] : index;

	/* set new parent */
	v = पढ़ोl(sclk->mux_reg);
	v &= ~(OSC_NEW_MASK << OSC_NEW_SHIFT);
	v |= nosc << OSC_NEW_SHIFT;

	pic32_syskey_unlock();

	ग_लिखोl(v, sclk->mux_reg);

	/* initate चयन */
	ग_लिखोl(OSC_SWEN, PIC32_SET(sclk->mux_reg));
	cpu_relax();

	/* add nop to flush pipeline (as cpu_clk is in-flux) */
	cpu_nop5();

	/* रुको क्रम SWEN bit to clear */
	err = पढ़ोl_poll_समयout_atomic(sclk->slew_reg, v,
					!(v & OSC_SWEN), 1, LOCK_TIMEOUT_US);

	spin_unlock_irqrestore(&sclk->core->reg_lock, flags);

	/*
	 * SCLK घड़ी-चयनing logic might reject a घड़ी चयनing request
	 * अगर pre-requisites (like new clk_src not present or unstable) are
	 * not met.
	 * So confirm beक्रमe claiming success.
	 */
	cosc = (पढ़ोl(sclk->mux_reg) >> OSC_CUR_SHIFT) & OSC_CUR_MASK;
	अगर (cosc != nosc) अणु
		pr_err("%s: err, failed to set_parent() to %d, current %d\n",
		       clk_hw_get_name(hw), nosc, cosc);
		err = -EBUSY;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक sclk_init(काष्ठा clk_hw *hw)
अणु
	काष्ठा pic32_sys_clk *sclk = clkhw_to_sys_clk(hw);
	अचिन्हित दीर्घ flags;
	u32 v;

	/* Maपूर्णांकain reference to this clk, required in spll_clk_set_rate() */
	pic32_sclk_hw = hw;

	/* apply slew भागider on both up and करोwn scaling */
	अगर (sclk->slew_भाग) अणु
		spin_lock_irqsave(&sclk->core->reg_lock, flags);
		v = पढ़ोl(sclk->slew_reg);
		v &= ~(SLEW_DIV << SLEW_DIV_SHIFT);
		v |= sclk->slew_भाग << SLEW_DIV_SHIFT;
		v |= SLEW_DOWNEN | SLEW_UPEN;
		ग_लिखोl(v, sclk->slew_reg);
		spin_unlock_irqrestore(&sclk->core->reg_lock, flags);
	पूर्ण

	वापस 0;
पूर्ण

/* sclk with post-भागider */
स्थिर काष्ठा clk_ops pic32_sclk_ops = अणु
	.get_parent	= sclk_get_parent,
	.set_parent	= sclk_set_parent,
	.round_rate	= sclk_round_rate,
	.set_rate	= sclk_set_rate,
	.recalc_rate	= sclk_get_rate,
	.init		= sclk_init,
	.determine_rate = __clk_mux_determine_rate,
पूर्ण;

/* sclk with no slew and no post-भागider */
स्थिर काष्ठा clk_ops pic32_sclk_no_भाग_ops = अणु
	.get_parent	= sclk_get_parent,
	.set_parent	= sclk_set_parent,
	.init		= sclk_init,
	.determine_rate = __clk_mux_determine_rate,
पूर्ण;

काष्ठा clk *pic32_sys_clk_रेजिस्टर(स्थिर काष्ठा pic32_sys_clk_data *data,
				   काष्ठा pic32_clk_common *core)
अणु
	काष्ठा pic32_sys_clk *sclk;
	काष्ठा clk *clk;

	sclk = devm_kzalloc(core->dev, माप(*sclk), GFP_KERNEL);
	अगर (!sclk)
		वापस ERR_PTR(-ENOMEM);

	sclk->core = core;
	sclk->hw.init = &data->init_data;
	sclk->mux_reg = data->mux_reg + core->iobase;
	sclk->slew_reg = data->slew_reg + core->iobase;
	sclk->slew_भाग = data->slew_भाग;
	sclk->parent_map = data->parent_map;

	clk = devm_clk_रेजिस्टर(core->dev, &sclk->hw);
	अगर (IS_ERR(clk))
		dev_err(core->dev, "%s: clk register failed\n", __func__);

	वापस clk;
पूर्ण

/* secondary oscillator */
काष्ठा pic32_sec_osc अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *enable_reg;
	व्योम __iomem *status_reg;
	u32 enable_mask;
	u32 status_mask;
	अचिन्हित दीर्घ fixed_rate;
	काष्ठा pic32_clk_common *core;
पूर्ण;

#घोषणा clkhw_to_sosc(_hw)	container_of(_hw, काष्ठा pic32_sec_osc, hw)
अटल पूर्णांक sosc_clk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा pic32_sec_osc *sosc = clkhw_to_sosc(hw);
	u32 v;

	/* enable SOSC */
	pic32_syskey_unlock();
	ग_लिखोl(sosc->enable_mask, PIC32_SET(sosc->enable_reg));

	/* रुको till warm-up period expires or पढ़ोy-status is updated */
	वापस पढ़ोl_poll_समयout_atomic(sosc->status_reg, v,
					 v & sosc->status_mask, 1, 100);
पूर्ण

अटल व्योम sosc_clk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा pic32_sec_osc *sosc = clkhw_to_sosc(hw);

	pic32_syskey_unlock();
	ग_लिखोl(sosc->enable_mask, PIC32_CLR(sosc->enable_reg));
पूर्ण

अटल पूर्णांक sosc_clk_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा pic32_sec_osc *sosc = clkhw_to_sosc(hw);
	u32 enabled, पढ़ोy;

	/* check enabled and पढ़ोy status */
	enabled = पढ़ोl(sosc->enable_reg) & sosc->enable_mask;
	पढ़ोy = पढ़ोl(sosc->status_reg) & sosc->status_mask;

	वापस enabled && पढ़ोy;
पूर्ण

अटल अचिन्हित दीर्घ sosc_clk_calc_rate(काष्ठा clk_hw *hw,
					अचिन्हित दीर्घ parent_rate)
अणु
	वापस clkhw_to_sosc(hw)->fixed_rate;
पूर्ण

स्थिर काष्ठा clk_ops pic32_sosc_ops = अणु
	.enable = sosc_clk_enable,
	.disable = sosc_clk_disable,
	.is_enabled = sosc_clk_is_enabled,
	.recalc_rate = sosc_clk_calc_rate,
पूर्ण;

काष्ठा clk *pic32_sosc_clk_रेजिस्टर(स्थिर काष्ठा pic32_sec_osc_data *data,
				    काष्ठा pic32_clk_common *core)
अणु
	काष्ठा pic32_sec_osc *sosc;

	sosc = devm_kzalloc(core->dev, माप(*sosc), GFP_KERNEL);
	अगर (!sosc)
		वापस ERR_PTR(-ENOMEM);

	sosc->core = core;
	sosc->hw.init = &data->init_data;
	sosc->fixed_rate = data->fixed_rate;
	sosc->enable_mask = data->enable_mask;
	sosc->status_mask = data->status_mask;
	sosc->enable_reg = data->enable_reg + core->iobase;
	sosc->status_reg = data->status_reg + core->iobase;

	वापस devm_clk_रेजिस्टर(core->dev, &sosc->hw);
पूर्ण
