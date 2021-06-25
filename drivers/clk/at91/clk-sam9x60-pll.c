<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Copyright (C) 2019 Microchip Technology Inc.
 *
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk/at91_pmc.h>
#समावेश <linux/of.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>

#समावेश "pmc.h"

#घोषणा	PMC_PLL_CTRL0_DIV_MSK	GENMASK(7, 0)
#घोषणा	PMC_PLL_CTRL1_MUL_MSK	GENMASK(31, 24)
#घोषणा	PMC_PLL_CTRL1_FRACR_MSK	GENMASK(21, 0)

#घोषणा PLL_DIV_MAX		(FIELD_GET(PMC_PLL_CTRL0_DIV_MSK, अच_पूर्णांक_उच्च) + 1)
#घोषणा UPLL_DIV		2
#घोषणा PLL_MUL_MAX		(FIELD_GET(PMC_PLL_CTRL1_MUL_MSK, अच_पूर्णांक_उच्च) + 1)

#घोषणा FCORE_MIN		(600000000)
#घोषणा FCORE_MAX		(1200000000)

#घोषणा PLL_MAX_ID		7

काष्ठा sam9x60_pll_core अणु
	काष्ठा regmap *regmap;
	spinlock_t *lock;
	स्थिर काष्ठा clk_pll_अक्षरacteristics *अक्षरacteristics;
	स्थिर काष्ठा clk_pll_layout *layout;
	काष्ठा clk_hw hw;
	u8 id;
पूर्ण;

काष्ठा sam9x60_frac अणु
	काष्ठा sam9x60_pll_core core;
	u32 frac;
	u16 mul;
पूर्ण;

काष्ठा sam9x60_भाग अणु
	काष्ठा sam9x60_pll_core core;
	u8 भाग;
पूर्ण;

#घोषणा to_sam9x60_pll_core(hw)	container_of(hw, काष्ठा sam9x60_pll_core, hw)
#घोषणा to_sam9x60_frac(core)	container_of(core, काष्ठा sam9x60_frac, core)
#घोषणा to_sam9x60_भाग(core)	container_of(core, काष्ठा sam9x60_भाग, core)

अटल अंतरभूत bool sam9x60_pll_पढ़ोy(काष्ठा regmap *regmap, पूर्णांक id)
अणु
	अचिन्हित पूर्णांक status;

	regmap_पढ़ो(regmap, AT91_PMC_PLL_ISR0, &status);

	वापस !!(status & BIT(id));
पूर्ण

अटल bool sam9x60_frac_pll_पढ़ोy(काष्ठा regmap *regmap, u8 id)
अणु
	वापस sam9x60_pll_पढ़ोy(regmap, id);
पूर्ण

अटल अचिन्हित दीर्घ sam9x60_frac_pll_recalc_rate(काष्ठा clk_hw *hw,
						  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा sam9x60_pll_core *core = to_sam9x60_pll_core(hw);
	काष्ठा sam9x60_frac *frac = to_sam9x60_frac(core);

	वापस (parent_rate * (frac->mul + 1) +
		((u64)parent_rate * frac->frac >> 22));
पूर्ण

अटल पूर्णांक sam9x60_frac_pll_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा sam9x60_pll_core *core = to_sam9x60_pll_core(hw);
	काष्ठा sam9x60_frac *frac = to_sam9x60_frac(core);
	काष्ठा regmap *regmap = core->regmap;
	अचिन्हित पूर्णांक val, cfrac, cmul;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(core->lock, flags);

	regmap_update_bits(regmap, AT91_PMC_PLL_UPDT,
			   AT91_PMC_PLL_UPDT_ID_MSK, core->id);
	regmap_पढ़ो(regmap, AT91_PMC_PLL_CTRL1, &val);
	cmul = (val & core->layout->mul_mask) >> core->layout->mul_shअगरt;
	cfrac = (val & core->layout->frac_mask) >> core->layout->frac_shअगरt;

	अगर (sam9x60_frac_pll_पढ़ोy(regmap, core->id) &&
	    (cmul == frac->mul && cfrac == frac->frac))
		जाओ unlock;

	/* Recommended value क्रम PMC_PLL_ACR */
	अगर (core->अक्षरacteristics->upll)
		val = AT91_PMC_PLL_ACR_DEFAULT_UPLL;
	अन्यथा
		val = AT91_PMC_PLL_ACR_DEFAULT_PLLA;
	regmap_ग_लिखो(regmap, AT91_PMC_PLL_ACR, val);

	regmap_ग_लिखो(regmap, AT91_PMC_PLL_CTRL1,
		     (frac->mul << core->layout->mul_shअगरt) |
		     (frac->frac << core->layout->frac_shअगरt));

	अगर (core->अक्षरacteristics->upll) अणु
		/* Enable the UTMI पूर्णांकernal bandgap */
		val |= AT91_PMC_PLL_ACR_UTMIBG;
		regmap_ग_लिखो(regmap, AT91_PMC_PLL_ACR, val);

		udelay(10);

		/* Enable the UTMI पूर्णांकernal regulator */
		val |= AT91_PMC_PLL_ACR_UTMIVR;
		regmap_ग_लिखो(regmap, AT91_PMC_PLL_ACR, val);

		udelay(10);
	पूर्ण

	regmap_update_bits(regmap, AT91_PMC_PLL_UPDT,
			   AT91_PMC_PLL_UPDT_UPDATE | AT91_PMC_PLL_UPDT_ID_MSK,
			   AT91_PMC_PLL_UPDT_UPDATE | core->id);

	regmap_update_bits(regmap, AT91_PMC_PLL_CTRL0,
			   AT91_PMC_PLL_CTRL0_ENLOCK | AT91_PMC_PLL_CTRL0_ENPLL,
			   AT91_PMC_PLL_CTRL0_ENLOCK | AT91_PMC_PLL_CTRL0_ENPLL);

	regmap_update_bits(regmap, AT91_PMC_PLL_UPDT,
			   AT91_PMC_PLL_UPDT_UPDATE | AT91_PMC_PLL_UPDT_ID_MSK,
			   AT91_PMC_PLL_UPDT_UPDATE | core->id);

	जबतक (!sam9x60_pll_पढ़ोy(regmap, core->id))
		cpu_relax();

unlock:
	spin_unlock_irqrestore(core->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम sam9x60_frac_pll_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा sam9x60_pll_core *core = to_sam9x60_pll_core(hw);
	काष्ठा regmap *regmap = core->regmap;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(core->lock, flags);

	regmap_update_bits(regmap, AT91_PMC_PLL_UPDT,
			   AT91_PMC_PLL_UPDT_ID_MSK, core->id);

	regmap_update_bits(regmap, AT91_PMC_PLL_CTRL0, AT91_PMC_PLL_CTRL0_ENPLL, 0);

	अगर (core->अक्षरacteristics->upll)
		regmap_update_bits(regmap, AT91_PMC_PLL_ACR,
				   AT91_PMC_PLL_ACR_UTMIBG | AT91_PMC_PLL_ACR_UTMIVR, 0);

	regmap_update_bits(regmap, AT91_PMC_PLL_UPDT,
			   AT91_PMC_PLL_UPDT_UPDATE | AT91_PMC_PLL_UPDT_ID_MSK,
			   AT91_PMC_PLL_UPDT_UPDATE | core->id);

	spin_unlock_irqrestore(core->lock, flags);
पूर्ण

अटल पूर्णांक sam9x60_frac_pll_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा sam9x60_pll_core *core = to_sam9x60_pll_core(hw);

	वापस sam9x60_pll_पढ़ोy(core->regmap, core->id);
पूर्ण

अटल दीर्घ sam9x60_frac_pll_compute_mul_frac(काष्ठा sam9x60_pll_core *core,
					      अचिन्हित दीर्घ rate,
					      अचिन्हित दीर्घ parent_rate,
					      bool update)
अणु
	काष्ठा sam9x60_frac *frac = to_sam9x60_frac(core);
	अचिन्हित दीर्घ पंचांगprate, reमुख्यder;
	अचिन्हित दीर्घ nmul = 0;
	अचिन्हित दीर्घ nfrac = 0;

	अगर (rate < FCORE_MIN || rate > FCORE_MAX)
		वापस -दुस्फल;

	/*
	 * Calculate the multiplier associated with the current
	 * भागider that provide the बंदst rate to the requested one.
	 */
	nmul = mult_frac(rate, 1, parent_rate);
	पंचांगprate = mult_frac(parent_rate, nmul, 1);
	reमुख्यder = rate - पंचांगprate;

	अगर (reमुख्यder) अणु
		nfrac = DIV_ROUND_CLOSEST_ULL((u64)reमुख्यder * (1 << 22),
					      parent_rate);

		पंचांगprate += DIV_ROUND_CLOSEST_ULL((u64)nfrac * parent_rate,
						 (1 << 22));
	पूर्ण

	/* Check अगर resulted rate is a valid.  */
	अगर (पंचांगprate < FCORE_MIN || पंचांगprate > FCORE_MAX)
		वापस -दुस्फल;

	अगर (update) अणु
		frac->mul = nmul - 1;
		frac->frac = nfrac;
	पूर्ण

	वापस पंचांगprate;
पूर्ण

अटल दीर्घ sam9x60_frac_pll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
					अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा sam9x60_pll_core *core = to_sam9x60_pll_core(hw);

	वापस sam9x60_frac_pll_compute_mul_frac(core, rate, *parent_rate, false);
पूर्ण

अटल पूर्णांक sam9x60_frac_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा sam9x60_pll_core *core = to_sam9x60_pll_core(hw);

	वापस sam9x60_frac_pll_compute_mul_frac(core, rate, parent_rate, true);
पूर्ण

अटल पूर्णांक sam9x60_frac_pll_set_rate_chg(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
					 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा sam9x60_pll_core *core = to_sam9x60_pll_core(hw);
	काष्ठा sam9x60_frac *frac = to_sam9x60_frac(core);
	काष्ठा regmap *regmap = core->regmap;
	अचिन्हित दीर्घ irqflags;
	अचिन्हित पूर्णांक val, cfrac, cmul;
	दीर्घ ret;

	ret = sam9x60_frac_pll_compute_mul_frac(core, rate, parent_rate, true);
	अगर (ret <= 0)
		वापस ret;

	spin_lock_irqsave(core->lock, irqflags);

	regmap_update_bits(regmap, AT91_PMC_PLL_UPDT, AT91_PMC_PLL_UPDT_ID_MSK,
			   core->id);
	regmap_पढ़ो(regmap, AT91_PMC_PLL_CTRL1, &val);
	cmul = (val & core->layout->mul_mask) >> core->layout->mul_shअगरt;
	cfrac = (val & core->layout->frac_mask) >> core->layout->frac_shअगरt;

	अगर (cmul == frac->mul && cfrac == frac->frac)
		जाओ unlock;

	regmap_ग_लिखो(regmap, AT91_PMC_PLL_CTRL1,
		     (frac->mul << core->layout->mul_shअगरt) |
		     (frac->frac << core->layout->frac_shअगरt));

	regmap_update_bits(regmap, AT91_PMC_PLL_UPDT,
			   AT91_PMC_PLL_UPDT_UPDATE | AT91_PMC_PLL_UPDT_ID_MSK,
			   AT91_PMC_PLL_UPDT_UPDATE | core->id);

	regmap_update_bits(regmap, AT91_PMC_PLL_CTRL0,
			   AT91_PMC_PLL_CTRL0_ENLOCK | AT91_PMC_PLL_CTRL0_ENPLL,
			   AT91_PMC_PLL_CTRL0_ENLOCK |
			   AT91_PMC_PLL_CTRL0_ENPLL);

	regmap_update_bits(regmap, AT91_PMC_PLL_UPDT,
			   AT91_PMC_PLL_UPDT_UPDATE | AT91_PMC_PLL_UPDT_ID_MSK,
			   AT91_PMC_PLL_UPDT_UPDATE | core->id);

	जबतक (!sam9x60_pll_पढ़ोy(regmap, core->id))
		cpu_relax();

unlock:
	spin_unlock_irqrestore(core->lock, irqflags);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा clk_ops sam9x60_frac_pll_ops = अणु
	.prepare = sam9x60_frac_pll_prepare,
	.unprepare = sam9x60_frac_pll_unprepare,
	.is_prepared = sam9x60_frac_pll_is_prepared,
	.recalc_rate = sam9x60_frac_pll_recalc_rate,
	.round_rate = sam9x60_frac_pll_round_rate,
	.set_rate = sam9x60_frac_pll_set_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops sam9x60_frac_pll_ops_chg = अणु
	.prepare = sam9x60_frac_pll_prepare,
	.unprepare = sam9x60_frac_pll_unprepare,
	.is_prepared = sam9x60_frac_pll_is_prepared,
	.recalc_rate = sam9x60_frac_pll_recalc_rate,
	.round_rate = sam9x60_frac_pll_round_rate,
	.set_rate = sam9x60_frac_pll_set_rate_chg,
पूर्ण;

अटल पूर्णांक sam9x60_भाग_pll_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा sam9x60_pll_core *core = to_sam9x60_pll_core(hw);
	काष्ठा sam9x60_भाग *भाग = to_sam9x60_भाग(core);
	काष्ठा regmap *regmap = core->regmap;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक val, cभाग;

	spin_lock_irqsave(core->lock, flags);
	regmap_update_bits(regmap, AT91_PMC_PLL_UPDT,
			   AT91_PMC_PLL_UPDT_ID_MSK, core->id);
	regmap_पढ़ो(regmap, AT91_PMC_PLL_CTRL0, &val);
	cभाग = (val & core->layout->भाग_mask) >> core->layout->भाग_shअगरt;

	/* Stop अगर enabled an nothing changed. */
	अगर (!!(val & core->layout->enभाग_mask) && cभाग == भाग->भाग)
		जाओ unlock;

	regmap_update_bits(regmap, AT91_PMC_PLL_CTRL0,
			   core->layout->भाग_mask | core->layout->enभाग_mask,
			   (भाग->भाग << core->layout->भाग_shअगरt) |
			   (1 << core->layout->enभाग_shअगरt));

	regmap_update_bits(regmap, AT91_PMC_PLL_UPDT,
			   AT91_PMC_PLL_UPDT_UPDATE | AT91_PMC_PLL_UPDT_ID_MSK,
			   AT91_PMC_PLL_UPDT_UPDATE | core->id);

	जबतक (!sam9x60_pll_पढ़ोy(regmap, core->id))
		cpu_relax();

unlock:
	spin_unlock_irqrestore(core->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम sam9x60_भाग_pll_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा sam9x60_pll_core *core = to_sam9x60_pll_core(hw);
	काष्ठा regmap *regmap = core->regmap;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(core->lock, flags);

	regmap_update_bits(regmap, AT91_PMC_PLL_UPDT,
			   AT91_PMC_PLL_UPDT_ID_MSK, core->id);

	regmap_update_bits(regmap, AT91_PMC_PLL_CTRL0,
			   core->layout->enभाग_mask, 0);

	regmap_update_bits(regmap, AT91_PMC_PLL_UPDT,
			   AT91_PMC_PLL_UPDT_UPDATE | AT91_PMC_PLL_UPDT_ID_MSK,
			   AT91_PMC_PLL_UPDT_UPDATE | core->id);

	spin_unlock_irqrestore(core->lock, flags);
पूर्ण

अटल पूर्णांक sam9x60_भाग_pll_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा sam9x60_pll_core *core = to_sam9x60_pll_core(hw);
	काष्ठा regmap *regmap = core->regmap;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक val;

	spin_lock_irqsave(core->lock, flags);

	regmap_update_bits(regmap, AT91_PMC_PLL_UPDT,
			   AT91_PMC_PLL_UPDT_ID_MSK, core->id);
	regmap_पढ़ो(regmap, AT91_PMC_PLL_CTRL0, &val);

	spin_unlock_irqrestore(core->lock, flags);

	वापस !!(val & core->layout->enभाग_mask);
पूर्ण

अटल अचिन्हित दीर्घ sam9x60_भाग_pll_recalc_rate(काष्ठा clk_hw *hw,
						 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा sam9x60_pll_core *core = to_sam9x60_pll_core(hw);
	काष्ठा sam9x60_भाग *भाग = to_sam9x60_भाग(core);

	वापस DIV_ROUND_CLOSEST_ULL(parent_rate, (भाग->भाग + 1));
पूर्ण

अटल दीर्घ sam9x60_भाग_pll_compute_भाग(काष्ठा sam9x60_pll_core *core,
					अचिन्हित दीर्घ *parent_rate,
					अचिन्हित दीर्घ rate)
अणु
	स्थिर काष्ठा clk_pll_अक्षरacteristics *अक्षरacteristics =
							core->अक्षरacteristics;
	काष्ठा clk_hw *parent = clk_hw_get_parent(&core->hw);
	अचिन्हित दीर्घ पंचांगp_rate, पंचांगp_parent_rate, पंचांगp_dअगरf;
	दीर्घ best_dअगरf = -1, best_rate = -EINVAL;
	u32 भागid;

	अगर (!rate)
		वापस 0;

	अगर (rate < अक्षरacteristics->output[0].min ||
	    rate > अक्षरacteristics->output[0].max)
		वापस -दुस्फल;

	क्रम (भागid = 1; भागid < core->layout->भाग_mask; भागid++) अणु
		पंचांगp_parent_rate = clk_hw_round_rate(parent, rate * भागid);
		अगर (!पंचांगp_parent_rate)
			जारी;

		पंचांगp_rate = DIV_ROUND_CLOSEST_ULL(पंचांगp_parent_rate, भागid);
		पंचांगp_dअगरf = असल(rate - पंचांगp_rate);

		अगर (best_dअगरf < 0 || best_dअगरf > पंचांगp_dअगरf) अणु
			*parent_rate = पंचांगp_parent_rate;
			best_rate = पंचांगp_rate;
			best_dअगरf = पंचांगp_dअगरf;
		पूर्ण

		अगर (!best_dअगरf)
			अवरोध;
	पूर्ण

	अगर (best_rate < अक्षरacteristics->output[0].min ||
	    best_rate > अक्षरacteristics->output[0].max)
		वापस -दुस्फल;

	वापस best_rate;
पूर्ण

अटल दीर्घ sam9x60_भाग_pll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				       अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा sam9x60_pll_core *core = to_sam9x60_pll_core(hw);

	वापस sam9x60_भाग_pll_compute_भाग(core, parent_rate, rate);
पूर्ण

अटल पूर्णांक sam9x60_भाग_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा sam9x60_pll_core *core = to_sam9x60_pll_core(hw);
	काष्ठा sam9x60_भाग *भाग = to_sam9x60_भाग(core);

	भाग->भाग = DIV_ROUND_CLOSEST(parent_rate, rate) - 1;

	वापस 0;
पूर्ण

अटल पूर्णांक sam9x60_भाग_pll_set_rate_chg(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
					अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा sam9x60_pll_core *core = to_sam9x60_pll_core(hw);
	काष्ठा sam9x60_भाग *भाग = to_sam9x60_भाग(core);
	काष्ठा regmap *regmap = core->regmap;
	अचिन्हित दीर्घ irqflags;
	अचिन्हित पूर्णांक val, cभाग;

	भाग->भाग = DIV_ROUND_CLOSEST(parent_rate, rate) - 1;

	spin_lock_irqsave(core->lock, irqflags);
	regmap_update_bits(regmap, AT91_PMC_PLL_UPDT, AT91_PMC_PLL_UPDT_ID_MSK,
			   core->id);
	regmap_पढ़ो(regmap, AT91_PMC_PLL_CTRL0, &val);
	cभाग = (val & core->layout->भाग_mask) >> core->layout->भाग_shअगरt;

	/* Stop अगर nothing changed. */
	अगर (cभाग == भाग->भाग)
		जाओ unlock;

	regmap_update_bits(regmap, AT91_PMC_PLL_CTRL0,
			   core->layout->भाग_mask,
			   (भाग->भाग << core->layout->भाग_shअगरt));

	regmap_update_bits(regmap, AT91_PMC_PLL_UPDT,
			   AT91_PMC_PLL_UPDT_UPDATE | AT91_PMC_PLL_UPDT_ID_MSK,
			   AT91_PMC_PLL_UPDT_UPDATE | core->id);

	जबतक (!sam9x60_pll_पढ़ोy(regmap, core->id))
		cpu_relax();

unlock:
	spin_unlock_irqrestore(core->lock, irqflags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops sam9x60_भाग_pll_ops = अणु
	.prepare = sam9x60_भाग_pll_prepare,
	.unprepare = sam9x60_भाग_pll_unprepare,
	.is_prepared = sam9x60_भाग_pll_is_prepared,
	.recalc_rate = sam9x60_भाग_pll_recalc_rate,
	.round_rate = sam9x60_भाग_pll_round_rate,
	.set_rate = sam9x60_भाग_pll_set_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops sam9x60_भाग_pll_ops_chg = अणु
	.prepare = sam9x60_भाग_pll_prepare,
	.unprepare = sam9x60_भाग_pll_unprepare,
	.is_prepared = sam9x60_भाग_pll_is_prepared,
	.recalc_rate = sam9x60_भाग_pll_recalc_rate,
	.round_rate = sam9x60_भाग_pll_round_rate,
	.set_rate = sam9x60_भाग_pll_set_rate_chg,
पूर्ण;

काष्ठा clk_hw * __init
sam9x60_clk_रेजिस्टर_frac_pll(काष्ठा regmap *regmap, spinlock_t *lock,
			      स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
			      काष्ठा clk_hw *parent_hw, u8 id,
			      स्थिर काष्ठा clk_pll_अक्षरacteristics *अक्षरacteristics,
			      स्थिर काष्ठा clk_pll_layout *layout, u32 flags)
अणु
	काष्ठा sam9x60_frac *frac;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	अचिन्हित दीर्घ parent_rate, irqflags;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	अगर (id > PLL_MAX_ID || !lock || !parent_hw)
		वापस ERR_PTR(-EINVAL);

	frac = kzalloc(माप(*frac), GFP_KERNEL);
	अगर (!frac)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.parent_names = &parent_name;
	init.num_parents = 1;
	अगर (flags & CLK_SET_RATE_GATE)
		init.ops = &sam9x60_frac_pll_ops;
	अन्यथा
		init.ops = &sam9x60_frac_pll_ops_chg;

	init.flags = flags;

	frac->core.id = id;
	frac->core.hw.init = &init;
	frac->core.अक्षरacteristics = अक्षरacteristics;
	frac->core.layout = layout;
	frac->core.regmap = regmap;
	frac->core.lock = lock;

	spin_lock_irqsave(frac->core.lock, irqflags);
	अगर (sam9x60_pll_पढ़ोy(regmap, id)) अणु
		regmap_update_bits(regmap, AT91_PMC_PLL_UPDT,
				   AT91_PMC_PLL_UPDT_ID_MSK, id);
		regmap_पढ़ो(regmap, AT91_PMC_PLL_CTRL1, &val);
		frac->mul = FIELD_GET(PMC_PLL_CTRL1_MUL_MSK, val);
		frac->frac = FIELD_GET(PMC_PLL_CTRL1_FRACR_MSK, val);
	पूर्ण अन्यथा अणु
		/*
		 * This means the PLL is not setup by bootloaders. In this
		 * हाल we need to set the minimum rate क्रम it. Otherwise
		 * a घड़ी child of this PLL may be enabled beक्रमe setting
		 * its rate leading to enabling this PLL with unsupported
		 * rate. This will lead to PLL not being locked at all.
		 */
		parent_rate = clk_hw_get_rate(parent_hw);
		अगर (!parent_rate) अणु
			hw = ERR_PTR(-EINVAL);
			जाओ मुक्त;
		पूर्ण

		ret = sam9x60_frac_pll_compute_mul_frac(&frac->core, FCORE_MIN,
							parent_rate, true);
		अगर (ret <= 0) अणु
			hw = ERR_PTR(ret);
			जाओ मुक्त;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(frac->core.lock, irqflags);

	hw = &frac->core.hw;
	ret = clk_hw_रेजिस्टर(शून्य, hw);
	अगर (ret) अणु
		kमुक्त(frac);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;

मुक्त:
	spin_unlock_irqrestore(frac->core.lock, irqflags);
	kमुक्त(frac);
	वापस hw;
पूर्ण

काष्ठा clk_hw * __init
sam9x60_clk_रेजिस्टर_भाग_pll(काष्ठा regmap *regmap, spinlock_t *lock,
			     स्थिर अक्षर *name, स्थिर अक्षर *parent_name, u8 id,
			     स्थिर काष्ठा clk_pll_अक्षरacteristics *अक्षरacteristics,
			     स्थिर काष्ठा clk_pll_layout *layout, u32 flags)
अणु
	काष्ठा sam9x60_भाग *भाग;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	अचिन्हित दीर्घ irqflags;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	अगर (id > PLL_MAX_ID || !lock)
		वापस ERR_PTR(-EINVAL);

	भाग = kzalloc(माप(*भाग), GFP_KERNEL);
	अगर (!भाग)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.parent_names = &parent_name;
	init.num_parents = 1;
	अगर (flags & CLK_SET_RATE_GATE)
		init.ops = &sam9x60_भाग_pll_ops;
	अन्यथा
		init.ops = &sam9x60_भाग_pll_ops_chg;
	init.flags = flags;

	भाग->core.id = id;
	भाग->core.hw.init = &init;
	भाग->core.अक्षरacteristics = अक्षरacteristics;
	भाग->core.layout = layout;
	भाग->core.regmap = regmap;
	भाग->core.lock = lock;

	spin_lock_irqsave(भाग->core.lock, irqflags);

	regmap_update_bits(regmap, AT91_PMC_PLL_UPDT,
			   AT91_PMC_PLL_UPDT_ID_MSK, id);
	regmap_पढ़ो(regmap, AT91_PMC_PLL_CTRL0, &val);
	भाग->भाग = FIELD_GET(PMC_PLL_CTRL0_DIV_MSK, val);

	spin_unlock_irqrestore(भाग->core.lock, irqflags);

	hw = &भाग->core.hw;
	ret = clk_hw_रेजिस्टर(शून्य, hw);
	अगर (ret) अणु
		kमुक्त(भाग);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण

