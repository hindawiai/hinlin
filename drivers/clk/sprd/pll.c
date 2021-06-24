<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Spपढ़ोtrum pll घड़ी driver
//
// Copyright (C) 2015~2017 Spपढ़ोtrum, Inc.
// Author: Chunyan Zhang <chunyan.zhang@spपढ़ोtrum.com>

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश "pll.h"

#घोषणा CLK_PLL_1M	1000000
#घोषणा CLK_PLL_10M	(CLK_PLL_1M * 10)

#घोषणा pindex(pll, member)		\
	(pll->factors[member].shअगरt / (8 * माप(pll->regs_num)))

#घोषणा pshअगरt(pll, member)		\
	(pll->factors[member].shअगरt % (8 * माप(pll->regs_num)))

#घोषणा pwidth(pll, member)		\
	pll->factors[member].width

#घोषणा pmask(pll, member)					\
	((pwidth(pll, member)) ?				\
	GENMASK(pwidth(pll, member) + pshअगरt(pll, member) - 1,	\
	pshअगरt(pll, member)) : 0)

#घोषणा pपूर्णांकernal(pll, cfg, member)	\
	(cfg[pindex(pll, member)] & pmask(pll, member))

#घोषणा pपूर्णांकernal_val(pll, cfg, member)	\
	(pपूर्णांकernal(pll, cfg, member) >> pshअगरt(pll, member))

अटल अंतरभूत अचिन्हित पूर्णांक
sprd_pll_पढ़ो(स्थिर काष्ठा sprd_pll *pll, u8 index)
अणु
	स्थिर काष्ठा sprd_clk_common *common = &pll->common;
	अचिन्हित पूर्णांक val = 0;

	अगर (WARN_ON(index >= pll->regs_num))
		वापस 0;

	regmap_पढ़ो(common->regmap, common->reg + index * 4, &val);

	वापस val;
पूर्ण

अटल अंतरभूत व्योम
sprd_pll_ग_लिखो(स्थिर काष्ठा sprd_pll *pll, u8 index,
				  u32 msk, u32 val)
अणु
	स्थिर काष्ठा sprd_clk_common *common = &pll->common;
	अचिन्हित पूर्णांक offset, reg;
	पूर्णांक ret = 0;

	अगर (WARN_ON(index >= pll->regs_num))
		वापस;

	offset = common->reg + index * 4;
	ret = regmap_पढ़ो(common->regmap, offset, &reg);
	अगर (!ret)
		regmap_ग_लिखो(common->regmap, offset, (reg & ~msk) | val);
पूर्ण

अटल अचिन्हित दीर्घ pll_get_refin(स्थिर काष्ठा sprd_pll *pll)
अणु
	u32 shअगरt, mask, index, refin_id = 3;
	स्थिर अचिन्हित दीर्घ refin[4] = अणु 2, 4, 13, 26 पूर्ण;

	अगर (pwidth(pll, PLL_REFIN)) अणु
		index = pindex(pll, PLL_REFIN);
		shअगरt = pshअगरt(pll, PLL_REFIN);
		mask = pmask(pll, PLL_REFIN);
		refin_id = (sprd_pll_पढ़ो(pll, index) & mask) >> shअगरt;
		अगर (refin_id > 3)
			refin_id = 3;
	पूर्ण

	वापस refin[refin_id];
पूर्ण

अटल u32 pll_get_ibias(u64 rate, स्थिर u64 *table)
अणु
	u32 i, num = table[0];

	/* table[0] indicates the number of items in this table */
	क्रम (i = 0; i < num; i++)
		अगर (rate <= table[i + 1])
			अवरोध;

	वापस i == num ? num - 1 : i;
पूर्ण

अटल अचिन्हित दीर्घ _sprd_pll_recalc_rate(स्थिर काष्ठा sprd_pll *pll,
					   अचिन्हित दीर्घ parent_rate)
अणु
	u32 *cfg;
	u32 i, mask, regs_num = pll->regs_num;
	अचिन्हित दीर्घ rate, nपूर्णांक, kपूर्णांक = 0;
	u64 refin;
	u16 k1, k2;

	cfg = kसुस्मृति(regs_num, माप(*cfg), GFP_KERNEL);
	अगर (!cfg)
		वापस parent_rate;

	क्रम (i = 0; i < regs_num; i++)
		cfg[i] = sprd_pll_पढ़ो(pll, i);

	refin = pll_get_refin(pll);

	अगर (pपूर्णांकernal(pll, cfg, PLL_PREDIV))
		refin = refin * 2;

	अगर (pwidth(pll, PLL_POSTDIV) &&
	    ((pll->fflag == 1 && pपूर्णांकernal(pll, cfg, PLL_POSTDIV)) ||
	     (!pll->fflag && !pपूर्णांकernal(pll, cfg, PLL_POSTDIV))))
		refin = refin / 2;

	अगर (!pपूर्णांकernal(pll, cfg, PLL_DIV_S)) अणु
		rate = refin * pपूर्णांकernal_val(pll, cfg, PLL_N) * CLK_PLL_10M;
	पूर्ण अन्यथा अणु
		nपूर्णांक = pपूर्णांकernal_val(pll, cfg, PLL_NINT);
		अगर (pपूर्णांकernal(pll, cfg, PLL_SDM_EN))
			kपूर्णांक = pपूर्णांकernal_val(pll, cfg, PLL_KINT);

		mask = pmask(pll, PLL_KINT);

		k1 = pll->k1;
		k2 = pll->k2;
		rate = DIV_ROUND_CLOSEST_ULL(refin * kपूर्णांक * k1,
					 ((mask >> __ffs(mask)) + 1)) *
					 k2 + refin * nपूर्णांक * CLK_PLL_1M;
	पूर्ण

	kमुक्त(cfg);
	वापस rate;
पूर्ण

#घोषणा SPRD_PLL_WRITE_CHECK(pll, i, mask, val)		\
	(((sprd_pll_पढ़ो(pll, i) & mask) == val) ? 0 : (-EFAULT))

अटल पूर्णांक _sprd_pll_set_rate(स्थिर काष्ठा sprd_pll *pll,
			      अचिन्हित दीर्घ rate,
			      अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा reg_cfg *cfg;
	पूर्णांक ret = 0;
	u32 mask, shअगरt, width, ibias_val, index;
	u32 regs_num = pll->regs_num, i = 0;
	अचिन्हित दीर्घ kपूर्णांक, nपूर्णांक;
	u64 पंचांगp, refin, fvco = rate;

	cfg = kसुस्मृति(regs_num, माप(*cfg), GFP_KERNEL);
	अगर (!cfg)
		वापस -ENOMEM;

	refin = pll_get_refin(pll);

	mask = pmask(pll, PLL_PREDIV);
	index = pindex(pll, PLL_PREDIV);
	width = pwidth(pll, PLL_PREDIV);
	अगर (width && (sprd_pll_पढ़ो(pll, index) & mask))
		refin = refin * 2;

	mask = pmask(pll, PLL_POSTDIV);
	index = pindex(pll, PLL_POSTDIV);
	width = pwidth(pll, PLL_POSTDIV);
	cfg[index].msk = mask;
	अगर (width && ((pll->fflag == 1 && fvco <= pll->fvco) ||
		      (pll->fflag == 0 && fvco > pll->fvco)))
		cfg[index].val |= mask;

	अगर (width && fvco <= pll->fvco)
		fvco = fvco * 2;

	mask = pmask(pll, PLL_DIV_S);
	index = pindex(pll, PLL_DIV_S);
	cfg[index].val |= mask;
	cfg[index].msk |= mask;

	mask = pmask(pll, PLL_SDM_EN);
	index = pindex(pll, PLL_SDM_EN);
	cfg[index].val |= mask;
	cfg[index].msk |= mask;

	nपूर्णांक = करो_भाग(fvco, refin * CLK_PLL_1M);
	mask = pmask(pll, PLL_NINT);
	index = pindex(pll, PLL_NINT);
	shअगरt = pshअगरt(pll, PLL_NINT);
	cfg[index].val |= (nपूर्णांक << shअगरt) & mask;
	cfg[index].msk |= mask;

	mask = pmask(pll, PLL_KINT);
	index = pindex(pll, PLL_KINT);
	width = pwidth(pll, PLL_KINT);
	shअगरt = pshअगरt(pll, PLL_KINT);
	पंचांगp = fvco - refin * nपूर्णांक * CLK_PLL_1M;
	पंचांगp = करो_भाग(पंचांगp, 10000) * ((mask >> shअगरt) + 1);
	kपूर्णांक = DIV_ROUND_CLOSEST_ULL(पंचांगp, refin * 100);
	cfg[index].val |= (kपूर्णांक << shअगरt) & mask;
	cfg[index].msk |= mask;

	ibias_val = pll_get_ibias(fvco, pll->itable);

	mask = pmask(pll, PLL_IBIAS);
	index = pindex(pll, PLL_IBIAS);
	shअगरt = pshअगरt(pll, PLL_IBIAS);
	cfg[index].val |= ibias_val << shअगरt & mask;
	cfg[index].msk |= mask;

	क्रम (i = 0; i < regs_num; i++) अणु
		अगर (cfg[i].msk) अणु
			sprd_pll_ग_लिखो(pll, i, cfg[i].msk, cfg[i].val);
			ret |= SPRD_PLL_WRITE_CHECK(pll, i, cfg[i].msk,
						   cfg[i].val);
		पूर्ण
	पूर्ण

	अगर (!ret)
		udelay(pll->udelay);

	kमुक्त(cfg);
	वापस ret;
पूर्ण

अटल अचिन्हित दीर्घ sprd_pll_recalc_rate(काष्ठा clk_hw *hw,
					  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा sprd_pll *pll = hw_to_sprd_pll(hw);

	वापस _sprd_pll_recalc_rate(pll, parent_rate);
पूर्ण

अटल पूर्णांक sprd_pll_set_rate(काष्ठा clk_hw *hw,
			     अचिन्हित दीर्घ rate,
			     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा sprd_pll *pll = hw_to_sprd_pll(hw);

	वापस _sprd_pll_set_rate(pll, rate, parent_rate);
पूर्ण

अटल पूर्णांक sprd_pll_clk_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा sprd_pll *pll = hw_to_sprd_pll(hw);

	udelay(pll->udelay);

	वापस 0;
पूर्ण

अटल दीर्घ sprd_pll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ *prate)
अणु
	वापस rate;
पूर्ण

स्थिर काष्ठा clk_ops sprd_pll_ops = अणु
	.prepare = sprd_pll_clk_prepare,
	.recalc_rate = sprd_pll_recalc_rate,
	.round_rate = sprd_pll_round_rate,
	.set_rate = sprd_pll_set_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(sprd_pll_ops);
