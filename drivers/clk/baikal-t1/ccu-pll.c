<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 BAIKAL ELECTRONICS, JSC
 *
 * Authors:
 *   Serge Semin <Sergey.Semin@baikalelectronics.ru>
 *   Dmitry Dunaev <dmitry.dunaev@baikalelectronics.ru>
 *
 * Baikal-T1 CCU PLL पूर्णांकerface driver
 */

#घोषणा pr_fmt(fmt) "bt1-ccu-pll: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/bits.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/regmap.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/समय64.h>
#समावेश <linux/rational.h>
#समावेश <linux/debugfs.h>

#समावेश "ccu-pll.h"

#घोषणा CCU_PLL_CTL			0x000
#घोषणा CCU_PLL_CTL_EN			BIT(0)
#घोषणा CCU_PLL_CTL_RST			BIT(1)
#घोषणा CCU_PLL_CTL_CLKR_FLD		2
#घोषणा CCU_PLL_CTL_CLKR_MASK		GENMASK(7, CCU_PLL_CTL_CLKR_FLD)
#घोषणा CCU_PLL_CTL_CLKF_FLD		8
#घोषणा CCU_PLL_CTL_CLKF_MASK		GENMASK(20, CCU_PLL_CTL_CLKF_FLD)
#घोषणा CCU_PLL_CTL_CLKOD_FLD		21
#घोषणा CCU_PLL_CTL_CLKOD_MASK		GENMASK(24, CCU_PLL_CTL_CLKOD_FLD)
#घोषणा CCU_PLL_CTL_BYPASS		BIT(30)
#घोषणा CCU_PLL_CTL_LOCK		BIT(31)
#घोषणा CCU_PLL_CTL1			0x004
#घोषणा CCU_PLL_CTL1_BWADJ_FLD		3
#घोषणा CCU_PLL_CTL1_BWADJ_MASK		GENMASK(14, CCU_PLL_CTL1_BWADJ_FLD)

#घोषणा CCU_PLL_LOCK_CHECK_RETRIES	50

#घोषणा CCU_PLL_NR_MAX \
	((CCU_PLL_CTL_CLKR_MASK >> CCU_PLL_CTL_CLKR_FLD) + 1)
#घोषणा CCU_PLL_NF_MAX \
	((CCU_PLL_CTL_CLKF_MASK >> (CCU_PLL_CTL_CLKF_FLD + 1)) + 1)
#घोषणा CCU_PLL_OD_MAX \
	((CCU_PLL_CTL_CLKOD_MASK >> CCU_PLL_CTL_CLKOD_FLD) + 1)
#घोषणा CCU_PLL_NB_MAX \
	((CCU_PLL_CTL1_BWADJ_MASK >> CCU_PLL_CTL1_BWADJ_FLD) + 1)
#घोषणा CCU_PLL_FDIV_MIN		427000UL
#घोषणा CCU_PLL_FDIV_MAX		3500000000UL
#घोषणा CCU_PLL_FOUT_MIN		200000000UL
#घोषणा CCU_PLL_FOUT_MAX		2500000000UL
#घोषणा CCU_PLL_FVCO_MIN		700000000UL
#घोषणा CCU_PLL_FVCO_MAX		3500000000UL
#घोषणा CCU_PLL_CLKOD_FACTOR		2

अटल अंतरभूत अचिन्हित दीर्घ ccu_pll_lock_delay_us(अचिन्हित दीर्घ ref_clk,
						  अचिन्हित दीर्घ nr)
अणु
	u64 us = 500ULL * nr * USEC_PER_SEC;

	करो_भाग(us, ref_clk);

	वापस us;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ ccu_pll_calc_freq(अचिन्हित दीर्घ ref_clk,
					      अचिन्हित दीर्घ nr,
					      अचिन्हित दीर्घ nf,
					      अचिन्हित दीर्घ od)
अणु
	u64 पंचांगp = ref_clk;

	करो_भाग(पंचांगp, nr);
	पंचांगp *= nf;
	करो_भाग(पंचांगp, od);

	वापस पंचांगp;
पूर्ण

अटल पूर्णांक ccu_pll_reset(काष्ठा ccu_pll *pll, अचिन्हित दीर्घ ref_clk,
			 अचिन्हित दीर्घ nr)
अणु
	अचिन्हित दीर्घ ud, ut;
	u32 val;

	ud = ccu_pll_lock_delay_us(ref_clk, nr);
	ut = ud * CCU_PLL_LOCK_CHECK_RETRIES;

	regmap_update_bits(pll->sys_regs, pll->reg_ctl,
			   CCU_PLL_CTL_RST, CCU_PLL_CTL_RST);

	वापस regmap_पढ़ो_poll_समयout_atomic(pll->sys_regs, pll->reg_ctl, val,
					       val & CCU_PLL_CTL_LOCK, ud, ut);
पूर्ण

अटल पूर्णांक ccu_pll_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hw *parent_hw = clk_hw_get_parent(hw);
	काष्ठा ccu_pll *pll = to_ccu_pll(hw);
	अचिन्हित दीर्घ flags;
	u32 val = 0;
	पूर्णांक ret;

	अगर (!parent_hw) अणु
		pr_err("Can't enable '%s' with no parent", clk_hw_get_name(hw));
		वापस -EINVAL;
	पूर्ण

	regmap_पढ़ो(pll->sys_regs, pll->reg_ctl, &val);
	अगर (val & CCU_PLL_CTL_EN)
		वापस 0;

	spin_lock_irqsave(&pll->lock, flags);
	regmap_ग_लिखो(pll->sys_regs, pll->reg_ctl, val | CCU_PLL_CTL_EN);
	ret = ccu_pll_reset(pll, clk_hw_get_rate(parent_hw),
			    FIELD_GET(CCU_PLL_CTL_CLKR_MASK, val) + 1);
	spin_unlock_irqrestore(&pll->lock, flags);
	अगर (ret)
		pr_err("PLL '%s' reset timed out\n", clk_hw_get_name(hw));

	वापस ret;
पूर्ण

अटल व्योम ccu_pll_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_pll *pll = to_ccu_pll(hw);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pll->lock, flags);
	regmap_update_bits(pll->sys_regs, pll->reg_ctl, CCU_PLL_CTL_EN, 0);
	spin_unlock_irqrestore(&pll->lock, flags);
पूर्ण

अटल पूर्णांक ccu_pll_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_pll *pll = to_ccu_pll(hw);
	u32 val = 0;

	regmap_पढ़ो(pll->sys_regs, pll->reg_ctl, &val);

	वापस !!(val & CCU_PLL_CTL_EN);
पूर्ण

अटल अचिन्हित दीर्घ ccu_pll_recalc_rate(काष्ठा clk_hw *hw,
					 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ccu_pll *pll = to_ccu_pll(hw);
	अचिन्हित दीर्घ nr, nf, od;
	u32 val = 0;

	regmap_पढ़ो(pll->sys_regs, pll->reg_ctl, &val);
	nr = FIELD_GET(CCU_PLL_CTL_CLKR_MASK, val) + 1;
	nf = FIELD_GET(CCU_PLL_CTL_CLKF_MASK, val) + 1;
	od = FIELD_GET(CCU_PLL_CTL_CLKOD_MASK, val) + 1;

	वापस ccu_pll_calc_freq(parent_rate, nr, nf, od);
पूर्ण

अटल व्योम ccu_pll_calc_factors(अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate,
				 अचिन्हित दीर्घ *nr, अचिन्हित दीर्घ *nf,
				 अचिन्हित दीर्घ *od)
अणु
	अचिन्हित दीर्घ err, freq, min_err = अच_दीर्घ_उच्च;
	अचिन्हित दीर्घ num, denom, n1, d1, nri;
	अचिन्हित दीर्घ nr_max, nf_max, od_max;

	/*
	 * Make sure PLL is working with valid input संकेत (Fभाग). If
	 * you want to speed the function up just reduce CCU_PLL_NR_MAX.
	 * This will cause a worse approximation though.
	 */
	nri = (parent_rate / CCU_PLL_FDIV_MAX) + 1;
	nr_max = min(parent_rate / CCU_PLL_FDIV_MIN, CCU_PLL_NR_MAX);

	/*
	 * Find a बंदst [nr;nf;od] vector taking पूर्णांकo account the
	 * limitations like: 1) 700MHz <= Fvco <= 3.5GHz, 2) PLL Od is
	 * either 1 or even number within the acceptable range (alas 1s
	 * is also excluded by the next loop).
	 */
	क्रम (; nri <= nr_max; ++nri) अणु
		/* Use Od factor to fulfill the limitation 2). */
		num = CCU_PLL_CLKOD_FACTOR * rate;
		denom = parent_rate / nri;

		/*
		 * Make sure Fvco is within the acceptable range to fulfill
		 * the condition 1). Note due to the CCU_PLL_CLKOD_FACTOR value
		 * the actual upper limit is also भागided by that factor.
		 * It's not big problem क्रम us since practically there is no
		 * need in घड़ीs with that high frequency.
		 */
		nf_max = min(CCU_PLL_FVCO_MAX / denom, CCU_PLL_NF_MAX);
		od_max = CCU_PLL_OD_MAX / CCU_PLL_CLKOD_FACTOR;

		/*
		 * Bypass the out-of-bound values, which can't be properly
		 * handled by the rational fraction approximation algorithm.
		 */
		अगर (num / denom >= nf_max) अणु
			n1 = nf_max;
			d1 = 1;
		पूर्ण अन्यथा अगर (denom / num >= od_max) अणु
			n1 = 1;
			d1 = od_max;
		पूर्ण अन्यथा अणु
			rational_best_approximation(num, denom, nf_max, od_max,
						    &n1, &d1);
		पूर्ण

		/* Select the best approximation of the target rate. */
		freq = ccu_pll_calc_freq(parent_rate, nri, n1, d1);
		err = असल((पूर्णांक64_t)freq - num);
		अगर (err < min_err) अणु
			min_err = err;
			*nr = nri;
			*nf = n1;
			*od = CCU_PLL_CLKOD_FACTOR * d1;
		पूर्ण
	पूर्ण
पूर्ण

अटल दीर्घ ccu_pll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ *parent_rate)
अणु
	अचिन्हित दीर्घ nr = 1, nf = 1, od = 1;

	ccu_pll_calc_factors(rate, *parent_rate, &nr, &nf, &od);

	वापस ccu_pll_calc_freq(*parent_rate, nr, nf, od);
पूर्ण

/*
 * This method is used क्रम PLLs, which support the on-the-fly भागiders
 * adjusपंचांगent. So there is no need in gating such घड़ीs.
 */
अटल पूर्णांक ccu_pll_set_rate_reset(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ccu_pll *pll = to_ccu_pll(hw);
	अचिन्हित दीर्घ nr, nf, od;
	अचिन्हित दीर्घ flags;
	u32 mask, val;
	पूर्णांक ret;

	ccu_pll_calc_factors(rate, parent_rate, &nr, &nf, &od);

	mask = CCU_PLL_CTL_CLKR_MASK | CCU_PLL_CTL_CLKF_MASK |
	       CCU_PLL_CTL_CLKOD_MASK;
	val = FIELD_PREP(CCU_PLL_CTL_CLKR_MASK, nr - 1) |
	      FIELD_PREP(CCU_PLL_CTL_CLKF_MASK, nf - 1) |
	      FIELD_PREP(CCU_PLL_CTL_CLKOD_MASK, od - 1);

	spin_lock_irqsave(&pll->lock, flags);
	regmap_update_bits(pll->sys_regs, pll->reg_ctl, mask, val);
	ret = ccu_pll_reset(pll, parent_rate, nr);
	spin_unlock_irqrestore(&pll->lock, flags);
	अगर (ret)
		pr_err("PLL '%s' reset timed out\n", clk_hw_get_name(hw));

	वापस ret;
पूर्ण

/*
 * This method is used क्रम PLLs, which करोn't support the on-the-fly भागiders
 * adjusपंचांगent. So the corresponding घड़ीs are supposed to be gated first.
 */
अटल पूर्णांक ccu_pll_set_rate_norst(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ccu_pll *pll = to_ccu_pll(hw);
	अचिन्हित दीर्घ nr, nf, od;
	अचिन्हित दीर्घ flags;
	u32 mask, val;

	ccu_pll_calc_factors(rate, parent_rate, &nr, &nf, &od);

	/*
	 * Disable PLL अगर it was enabled by शेष or left enabled by the
	 * प्रणाली bootloader.
	 */
	mask = CCU_PLL_CTL_CLKR_MASK | CCU_PLL_CTL_CLKF_MASK |
	       CCU_PLL_CTL_CLKOD_MASK | CCU_PLL_CTL_EN;
	val = FIELD_PREP(CCU_PLL_CTL_CLKR_MASK, nr - 1) |
	      FIELD_PREP(CCU_PLL_CTL_CLKF_MASK, nf - 1) |
	      FIELD_PREP(CCU_PLL_CTL_CLKOD_MASK, od - 1);

	spin_lock_irqsave(&pll->lock, flags);
	regmap_update_bits(pll->sys_regs, pll->reg_ctl, mask, val);
	spin_unlock_irqrestore(&pll->lock, flags);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS

काष्ठा ccu_pll_dbgfs_bit अणु
	काष्ठा ccu_pll *pll;
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक reg;
	u32 mask;
पूर्ण;

काष्ठा ccu_pll_dbgfs_fld अणु
	काष्ठा ccu_pll *pll;
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक lsb;
	u32 mask;
	u32 min;
	u32 max;
पूर्ण;

#घोषणा CCU_PLL_DBGFS_BIT_ATTR(_name, _reg, _mask)	\
	अणु						\
		.name = _name,				\
		.reg = _reg,				\
		.mask = _mask				\
	पूर्ण

#घोषणा CCU_PLL_DBGFS_FLD_ATTR(_name, _reg, _lsb, _mask, _min, _max)	\
	अणु								\
		.name = _name,						\
		.reg = _reg,						\
		.lsb = _lsb,						\
		.mask = _mask,						\
		.min = _min,						\
		.max = _max						\
	पूर्ण

अटल स्थिर काष्ठा ccu_pll_dbgfs_bit ccu_pll_bits[] = अणु
	CCU_PLL_DBGFS_BIT_ATTR("pll_en", CCU_PLL_CTL, CCU_PLL_CTL_EN),
	CCU_PLL_DBGFS_BIT_ATTR("pll_rst", CCU_PLL_CTL, CCU_PLL_CTL_RST),
	CCU_PLL_DBGFS_BIT_ATTR("pll_bypass", CCU_PLL_CTL, CCU_PLL_CTL_BYPASS),
	CCU_PLL_DBGFS_BIT_ATTR("pll_lock", CCU_PLL_CTL, CCU_PLL_CTL_LOCK)
पूर्ण;

#घोषणा CCU_PLL_DBGFS_BIT_NUM	ARRAY_SIZE(ccu_pll_bits)

अटल स्थिर काष्ठा ccu_pll_dbgfs_fld ccu_pll_flds[] = अणु
	CCU_PLL_DBGFS_FLD_ATTR("pll_nr", CCU_PLL_CTL, CCU_PLL_CTL_CLKR_FLD,
				CCU_PLL_CTL_CLKR_MASK, 1, CCU_PLL_NR_MAX),
	CCU_PLL_DBGFS_FLD_ATTR("pll_nf", CCU_PLL_CTL, CCU_PLL_CTL_CLKF_FLD,
				CCU_PLL_CTL_CLKF_MASK, 1, CCU_PLL_NF_MAX),
	CCU_PLL_DBGFS_FLD_ATTR("pll_od", CCU_PLL_CTL, CCU_PLL_CTL_CLKOD_FLD,
				CCU_PLL_CTL_CLKOD_MASK, 1, CCU_PLL_OD_MAX),
	CCU_PLL_DBGFS_FLD_ATTR("pll_nb", CCU_PLL_CTL1, CCU_PLL_CTL1_BWADJ_FLD,
				CCU_PLL_CTL1_BWADJ_MASK, 1, CCU_PLL_NB_MAX)
पूर्ण;

#घोषणा CCU_PLL_DBGFS_FLD_NUM	ARRAY_SIZE(ccu_pll_flds)

/*
 * It can be dangerous to change the PLL settings behind घड़ी framework back,
 * thereक्रमe we करोn't provide any kernel config based compile समय option क्रम
 * this feature to enable.
 */
#अघोषित CCU_PLL_ALLOW_WRITE_DEBUGFS
#अगर_घोषित CCU_PLL_ALLOW_WRITE_DEBUGFS

अटल पूर्णांक ccu_pll_dbgfs_bit_set(व्योम *priv, u64 val)
अणु
	स्थिर काष्ठा ccu_pll_dbgfs_bit *bit = priv;
	काष्ठा ccu_pll *pll = bit->pll;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pll->lock, flags);
	regmap_update_bits(pll->sys_regs, pll->reg_ctl + bit->reg,
			   bit->mask, val ? bit->mask : 0);
	spin_unlock_irqrestore(&pll->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ccu_pll_dbgfs_fld_set(व्योम *priv, u64 val)
अणु
	काष्ठा ccu_pll_dbgfs_fld *fld = priv;
	काष्ठा ccu_pll *pll = fld->pll;
	अचिन्हित दीर्घ flags;
	u32 data;

	val = clamp_t(u64, val, fld->min, fld->max);
	data = ((val - 1) << fld->lsb) & fld->mask;

	spin_lock_irqsave(&pll->lock, flags);
	regmap_update_bits(pll->sys_regs, pll->reg_ctl + fld->reg, fld->mask,
			   data);
	spin_unlock_irqrestore(&pll->lock, flags);

	वापस 0;
पूर्ण

#घोषणा ccu_pll_dbgfs_mode	0644

#अन्यथा /* !CCU_PLL_ALLOW_WRITE_DEBUGFS */

#घोषणा ccu_pll_dbgfs_bit_set	शून्य
#घोषणा ccu_pll_dbgfs_fld_set	शून्य
#घोषणा ccu_pll_dbgfs_mode	0444

#पूर्ण_अगर /* !CCU_PLL_ALLOW_WRITE_DEBUGFS */

अटल पूर्णांक ccu_pll_dbgfs_bit_get(व्योम *priv, u64 *val)
अणु
	काष्ठा ccu_pll_dbgfs_bit *bit = priv;
	काष्ठा ccu_pll *pll = bit->pll;
	u32 data = 0;

	regmap_पढ़ो(pll->sys_regs, pll->reg_ctl + bit->reg, &data);
	*val = !!(data & bit->mask);

	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(ccu_pll_dbgfs_bit_fops,
	ccu_pll_dbgfs_bit_get, ccu_pll_dbgfs_bit_set, "%llu\n");

अटल पूर्णांक ccu_pll_dbgfs_fld_get(व्योम *priv, u64 *val)
अणु
	काष्ठा ccu_pll_dbgfs_fld *fld = priv;
	काष्ठा ccu_pll *pll = fld->pll;
	u32 data = 0;

	regmap_पढ़ो(pll->sys_regs, pll->reg_ctl + fld->reg, &data);
	*val = ((data & fld->mask) >> fld->lsb) + 1;

	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(ccu_pll_dbgfs_fld_fops,
	ccu_pll_dbgfs_fld_get, ccu_pll_dbgfs_fld_set, "%llu\n");

अटल व्योम ccu_pll_debug_init(काष्ठा clk_hw *hw, काष्ठा dentry *dentry)
अणु
	काष्ठा ccu_pll *pll = to_ccu_pll(hw);
	काष्ठा ccu_pll_dbgfs_bit *bits;
	काष्ठा ccu_pll_dbgfs_fld *flds;
	पूर्णांक idx;

	bits = kसुस्मृति(CCU_PLL_DBGFS_BIT_NUM, माप(*bits), GFP_KERNEL);
	अगर (!bits)
		वापस;

	क्रम (idx = 0; idx < CCU_PLL_DBGFS_BIT_NUM; ++idx) अणु
		bits[idx] = ccu_pll_bits[idx];
		bits[idx].pll = pll;

		debugfs_create_file_unsafe(bits[idx].name, ccu_pll_dbgfs_mode,
					   dentry, &bits[idx],
					   &ccu_pll_dbgfs_bit_fops);
	पूर्ण

	flds = kसुस्मृति(CCU_PLL_DBGFS_FLD_NUM, माप(*flds), GFP_KERNEL);
	अगर (!flds)
		वापस;

	क्रम (idx = 0; idx < CCU_PLL_DBGFS_FLD_NUM; ++idx) अणु
		flds[idx] = ccu_pll_flds[idx];
		flds[idx].pll = pll;

		debugfs_create_file_unsafe(flds[idx].name, ccu_pll_dbgfs_mode,
					   dentry, &flds[idx],
					   &ccu_pll_dbgfs_fld_fops);
	पूर्ण
पूर्ण

#अन्यथा /* !CONFIG_DEBUG_FS */

#घोषणा ccu_pll_debug_init शून्य

#पूर्ण_अगर /* !CONFIG_DEBUG_FS */

अटल स्थिर काष्ठा clk_ops ccu_pll_gate_to_set_ops = अणु
	.enable = ccu_pll_enable,
	.disable = ccu_pll_disable,
	.is_enabled = ccu_pll_is_enabled,
	.recalc_rate = ccu_pll_recalc_rate,
	.round_rate = ccu_pll_round_rate,
	.set_rate = ccu_pll_set_rate_norst,
	.debug_init = ccu_pll_debug_init
पूर्ण;

अटल स्थिर काष्ठा clk_ops ccu_pll_straight_set_ops = अणु
	.enable = ccu_pll_enable,
	.disable = ccu_pll_disable,
	.is_enabled = ccu_pll_is_enabled,
	.recalc_rate = ccu_pll_recalc_rate,
	.round_rate = ccu_pll_round_rate,
	.set_rate = ccu_pll_set_rate_reset,
	.debug_init = ccu_pll_debug_init
पूर्ण;

काष्ठा ccu_pll *ccu_pll_hw_रेजिस्टर(स्थिर काष्ठा ccu_pll_init_data *pll_init)
अणु
	काष्ठा clk_parent_data parent_data = अणु पूर्ण;
	काष्ठा clk_init_data hw_init = अणु पूर्ण;
	काष्ठा ccu_pll *pll;
	पूर्णांक ret;

	अगर (!pll_init)
		वापस ERR_PTR(-EINVAL);

	pll = kzalloc(माप(*pll), GFP_KERNEL);
	अगर (!pll)
		वापस ERR_PTR(-ENOMEM);

	/*
	 * Note since Baikal-T1 System Controller रेजिस्टरs are MMIO-backed
	 * we won't check the regmap IO operations वापस status, because it
	 * must be zero anyway.
	 */
	pll->hw.init = &hw_init;
	pll->reg_ctl = pll_init->base + CCU_PLL_CTL;
	pll->reg_ctl1 = pll_init->base + CCU_PLL_CTL1;
	pll->sys_regs = pll_init->sys_regs;
	pll->id = pll_init->id;
	spin_lock_init(&pll->lock);

	hw_init.name = pll_init->name;
	hw_init.flags = pll_init->flags;

	अगर (hw_init.flags & CLK_SET_RATE_GATE)
		hw_init.ops = &ccu_pll_gate_to_set_ops;
	अन्यथा
		hw_init.ops = &ccu_pll_straight_set_ops;

	अगर (!pll_init->parent_name) अणु
		ret = -EINVAL;
		जाओ err_मुक्त_pll;
	पूर्ण
	parent_data.fw_name = pll_init->parent_name;
	hw_init.parent_data = &parent_data;
	hw_init.num_parents = 1;

	ret = of_clk_hw_रेजिस्टर(pll_init->np, &pll->hw);
	अगर (ret)
		जाओ err_मुक्त_pll;

	वापस pll;

err_मुक्त_pll:
	kमुक्त(pll);

	वापस ERR_PTR(ret);
पूर्ण

व्योम ccu_pll_hw_unरेजिस्टर(काष्ठा ccu_pll *pll)
अणु
	clk_hw_unरेजिस्टर(&pll->hw);

	kमुक्त(pll);
पूर्ण
