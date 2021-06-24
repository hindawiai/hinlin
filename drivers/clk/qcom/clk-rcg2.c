<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2013, 2018, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>
#समावेश <linux/err.h>
#समावेश <linux/bug.h>
#समावेश <linux/export.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/rational.h>
#समावेश <linux/regmap.h>
#समावेश <linux/math64.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/भाग64.h>

#समावेश "clk-rcg.h"
#समावेश "common.h"

#घोषणा CMD_REG			0x0
#घोषणा CMD_UPDATE		BIT(0)
#घोषणा CMD_ROOT_EN		BIT(1)
#घोषणा CMD_सूचीTY_CFG		BIT(4)
#घोषणा CMD_सूचीTY_N		BIT(5)
#घोषणा CMD_सूचीTY_M		BIT(6)
#घोषणा CMD_सूचीTY_D		BIT(7)
#घोषणा CMD_ROOT_OFF		BIT(31)

#घोषणा CFG_REG			0x4
#घोषणा CFG_SRC_DIV_SHIFT	0
#घोषणा CFG_SRC_SEL_SHIFT	8
#घोषणा CFG_SRC_SEL_MASK	(0x7 << CFG_SRC_SEL_SHIFT)
#घोषणा CFG_MODE_SHIFT		12
#घोषणा CFG_MODE_MASK		(0x3 << CFG_MODE_SHIFT)
#घोषणा CFG_MODE_DUAL_EDGE	(0x2 << CFG_MODE_SHIFT)
#घोषणा CFG_HW_CLK_CTRL_MASK	BIT(20)

#घोषणा M_REG			0x8
#घोषणा N_REG			0xc
#घोषणा D_REG			0x10

#घोषणा RCG_CFG_OFFSET(rcg)	((rcg)->cmd_rcgr + (rcg)->cfg_off + CFG_REG)
#घोषणा RCG_M_OFFSET(rcg)	((rcg)->cmd_rcgr + (rcg)->cfg_off + M_REG)
#घोषणा RCG_N_OFFSET(rcg)	((rcg)->cmd_rcgr + (rcg)->cfg_off + N_REG)
#घोषणा RCG_D_OFFSET(rcg)	((rcg)->cmd_rcgr + (rcg)->cfg_off + D_REG)

/* Dynamic Frequency Scaling */
#घोषणा MAX_PERF_LEVEL		8
#घोषणा SE_CMD_DFSR_OFFSET	0x14
#घोषणा SE_CMD_DFS_EN		BIT(0)
#घोषणा SE_PERF_DFSR(level)	(0x1c + 0x4 * (level))
#घोषणा SE_PERF_M_DFSR(level)	(0x5c + 0x4 * (level))
#घोषणा SE_PERF_N_DFSR(level)	(0x9c + 0x4 * (level))

क्रमागत freq_policy अणु
	FLOOR,
	CEIL,
पूर्ण;

अटल पूर्णांक clk_rcg2_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_rcg2 *rcg = to_clk_rcg2(hw);
	u32 cmd;
	पूर्णांक ret;

	ret = regmap_पढ़ो(rcg->clkr.regmap, rcg->cmd_rcgr + CMD_REG, &cmd);
	अगर (ret)
		वापस ret;

	वापस (cmd & CMD_ROOT_OFF) == 0;
पूर्ण

अटल u8 clk_rcg2_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_rcg2 *rcg = to_clk_rcg2(hw);
	पूर्णांक num_parents = clk_hw_get_num_parents(hw);
	u32 cfg;
	पूर्णांक i, ret;

	ret = regmap_पढ़ो(rcg->clkr.regmap, RCG_CFG_OFFSET(rcg), &cfg);
	अगर (ret)
		जाओ err;

	cfg &= CFG_SRC_SEL_MASK;
	cfg >>= CFG_SRC_SEL_SHIFT;

	क्रम (i = 0; i < num_parents; i++)
		अगर (cfg == rcg->parent_map[i].cfg)
			वापस i;

err:
	pr_debug("%s: Clock %s has invalid parent, using default.\n",
		 __func__, clk_hw_get_name(hw));
	वापस 0;
पूर्ण

अटल पूर्णांक update_config(काष्ठा clk_rcg2 *rcg)
अणु
	पूर्णांक count, ret;
	u32 cmd;
	काष्ठा clk_hw *hw = &rcg->clkr.hw;
	स्थिर अक्षर *name = clk_hw_get_name(hw);

	ret = regmap_update_bits(rcg->clkr.regmap, rcg->cmd_rcgr + CMD_REG,
				 CMD_UPDATE, CMD_UPDATE);
	अगर (ret)
		वापस ret;

	/* Wait क्रम update to take effect */
	क्रम (count = 500; count > 0; count--) अणु
		ret = regmap_पढ़ो(rcg->clkr.regmap, rcg->cmd_rcgr + CMD_REG, &cmd);
		अगर (ret)
			वापस ret;
		अगर (!(cmd & CMD_UPDATE))
			वापस 0;
		udelay(1);
	पूर्ण

	WARN(1, "%s: rcg didn't update its configuration.", name);
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक clk_rcg2_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा clk_rcg2 *rcg = to_clk_rcg2(hw);
	पूर्णांक ret;
	u32 cfg = rcg->parent_map[index].cfg << CFG_SRC_SEL_SHIFT;

	ret = regmap_update_bits(rcg->clkr.regmap, RCG_CFG_OFFSET(rcg),
				 CFG_SRC_SEL_MASK, cfg);
	अगर (ret)
		वापस ret;

	वापस update_config(rcg);
पूर्ण

/*
 * Calculate m/n:d rate
 *
 *          parent_rate     m
 *   rate = ----------- x  ---
 *            hid_भाग       n
 */
अटल अचिन्हित दीर्घ
calc_rate(अचिन्हित दीर्घ rate, u32 m, u32 n, u32 mode, u32 hid_भाग)
अणु
	अगर (hid_भाग) अणु
		rate *= 2;
		rate /= hid_भाग + 1;
	पूर्ण

	अगर (mode) अणु
		u64 पंचांगp = rate;
		पंचांगp *= m;
		करो_भाग(पंचांगp, n);
		rate = पंचांगp;
	पूर्ण

	वापस rate;
पूर्ण

अटल अचिन्हित दीर्घ
clk_rcg2_recalc_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_rcg2 *rcg = to_clk_rcg2(hw);
	u32 cfg, hid_भाग, m = 0, n = 0, mode = 0, mask;

	regmap_पढ़ो(rcg->clkr.regmap, RCG_CFG_OFFSET(rcg), &cfg);

	अगर (rcg->mnd_width) अणु
		mask = BIT(rcg->mnd_width) - 1;
		regmap_पढ़ो(rcg->clkr.regmap, RCG_M_OFFSET(rcg), &m);
		m &= mask;
		regmap_पढ़ो(rcg->clkr.regmap, RCG_N_OFFSET(rcg), &n);
		n =  ~n;
		n &= mask;
		n += m;
		mode = cfg & CFG_MODE_MASK;
		mode >>= CFG_MODE_SHIFT;
	पूर्ण

	mask = BIT(rcg->hid_width) - 1;
	hid_भाग = cfg >> CFG_SRC_DIV_SHIFT;
	hid_भाग &= mask;

	वापस calc_rate(parent_rate, m, n, mode, hid_भाग);
पूर्ण

अटल पूर्णांक _freq_tbl_determine_rate(काष्ठा clk_hw *hw, स्थिर काष्ठा freq_tbl *f,
				    काष्ठा clk_rate_request *req,
				    क्रमागत freq_policy policy)
अणु
	अचिन्हित दीर्घ clk_flags, rate = req->rate;
	काष्ठा clk_hw *p;
	काष्ठा clk_rcg2 *rcg = to_clk_rcg2(hw);
	पूर्णांक index;

	चयन (policy) अणु
	हाल FLOOR:
		f = qcom_find_freq_न्यूनमान(f, rate);
		अवरोध;
	हाल CEIL:
		f = qcom_find_freq(f, rate);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (!f)
		वापस -EINVAL;

	index = qcom_find_src_index(hw, rcg->parent_map, f->src);
	अगर (index < 0)
		वापस index;

	clk_flags = clk_hw_get_flags(hw);
	p = clk_hw_get_parent_by_index(hw, index);
	अगर (!p)
		वापस -EINVAL;

	अगर (clk_flags & CLK_SET_RATE_PARENT) अणु
		rate = f->freq;
		अगर (f->pre_भाग) अणु
			अगर (!rate)
				rate = req->rate;
			rate /= 2;
			rate *= f->pre_भाग + 1;
		पूर्ण

		अगर (f->n) अणु
			u64 पंचांगp = rate;
			पंचांगp = पंचांगp * f->n;
			करो_भाग(पंचांगp, f->m);
			rate = पंचांगp;
		पूर्ण
	पूर्ण अन्यथा अणु
		rate =  clk_hw_get_rate(p);
	पूर्ण
	req->best_parent_hw = p;
	req->best_parent_rate = rate;
	req->rate = f->freq;

	वापस 0;
पूर्ण

अटल पूर्णांक clk_rcg2_determine_rate(काष्ठा clk_hw *hw,
				   काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_rcg2 *rcg = to_clk_rcg2(hw);

	वापस _freq_tbl_determine_rate(hw, rcg->freq_tbl, req, CEIL);
पूर्ण

अटल पूर्णांक clk_rcg2_determine_न्यूनमान_rate(काष्ठा clk_hw *hw,
					 काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_rcg2 *rcg = to_clk_rcg2(hw);

	वापस _freq_tbl_determine_rate(hw, rcg->freq_tbl, req, FLOOR);
पूर्ण

अटल पूर्णांक __clk_rcg2_configure(काष्ठा clk_rcg2 *rcg, स्थिर काष्ठा freq_tbl *f)
अणु
	u32 cfg, mask;
	काष्ठा clk_hw *hw = &rcg->clkr.hw;
	पूर्णांक ret, index = qcom_find_src_index(hw, rcg->parent_map, f->src);

	अगर (index < 0)
		वापस index;

	अगर (rcg->mnd_width && f->n) अणु
		mask = BIT(rcg->mnd_width) - 1;
		ret = regmap_update_bits(rcg->clkr.regmap,
				RCG_M_OFFSET(rcg), mask, f->m);
		अगर (ret)
			वापस ret;

		ret = regmap_update_bits(rcg->clkr.regmap,
				RCG_N_OFFSET(rcg), mask, ~(f->n - f->m));
		अगर (ret)
			वापस ret;

		ret = regmap_update_bits(rcg->clkr.regmap,
				RCG_D_OFFSET(rcg), mask, ~f->n);
		अगर (ret)
			वापस ret;
	पूर्ण

	mask = BIT(rcg->hid_width) - 1;
	mask |= CFG_SRC_SEL_MASK | CFG_MODE_MASK | CFG_HW_CLK_CTRL_MASK;
	cfg = f->pre_भाग << CFG_SRC_DIV_SHIFT;
	cfg |= rcg->parent_map[index].cfg << CFG_SRC_SEL_SHIFT;
	अगर (rcg->mnd_width && f->n && (f->m != f->n))
		cfg |= CFG_MODE_DUAL_EDGE;
	वापस regmap_update_bits(rcg->clkr.regmap, RCG_CFG_OFFSET(rcg),
					mask, cfg);
पूर्ण

अटल पूर्णांक clk_rcg2_configure(काष्ठा clk_rcg2 *rcg, स्थिर काष्ठा freq_tbl *f)
अणु
	पूर्णांक ret;

	ret = __clk_rcg2_configure(rcg, f);
	अगर (ret)
		वापस ret;

	वापस update_config(rcg);
पूर्ण

अटल पूर्णांक __clk_rcg2_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       क्रमागत freq_policy policy)
अणु
	काष्ठा clk_rcg2 *rcg = to_clk_rcg2(hw);
	स्थिर काष्ठा freq_tbl *f;

	चयन (policy) अणु
	हाल FLOOR:
		f = qcom_find_freq_न्यूनमान(rcg->freq_tbl, rate);
		अवरोध;
	हाल CEIL:
		f = qcom_find_freq(rcg->freq_tbl, rate);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (!f)
		वापस -EINVAL;

	वापस clk_rcg2_configure(rcg, f);
पूर्ण

अटल पूर्णांक clk_rcg2_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			    अचिन्हित दीर्घ parent_rate)
अणु
	वापस __clk_rcg2_set_rate(hw, rate, CEIL);
पूर्ण

अटल पूर्णांक clk_rcg2_set_न्यूनमान_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				   अचिन्हित दीर्घ parent_rate)
अणु
	वापस __clk_rcg2_set_rate(hw, rate, FLOOR);
पूर्ण

अटल पूर्णांक clk_rcg2_set_rate_and_parent(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate, u8 index)
अणु
	वापस __clk_rcg2_set_rate(hw, rate, CEIL);
पूर्ण

अटल पूर्णांक clk_rcg2_set_न्यूनमान_rate_and_parent(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate, u8 index)
अणु
	वापस __clk_rcg2_set_rate(hw, rate, FLOOR);
पूर्ण

स्थिर काष्ठा clk_ops clk_rcg2_ops = अणु
	.is_enabled = clk_rcg2_is_enabled,
	.get_parent = clk_rcg2_get_parent,
	.set_parent = clk_rcg2_set_parent,
	.recalc_rate = clk_rcg2_recalc_rate,
	.determine_rate = clk_rcg2_determine_rate,
	.set_rate = clk_rcg2_set_rate,
	.set_rate_and_parent = clk_rcg2_set_rate_and_parent,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_rcg2_ops);

स्थिर काष्ठा clk_ops clk_rcg2_न्यूनमान_ops = अणु
	.is_enabled = clk_rcg2_is_enabled,
	.get_parent = clk_rcg2_get_parent,
	.set_parent = clk_rcg2_set_parent,
	.recalc_rate = clk_rcg2_recalc_rate,
	.determine_rate = clk_rcg2_determine_न्यूनमान_rate,
	.set_rate = clk_rcg2_set_न्यूनमान_rate,
	.set_rate_and_parent = clk_rcg2_set_न्यूनमान_rate_and_parent,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_rcg2_न्यूनमान_ops);

काष्ठा frac_entry अणु
	पूर्णांक num;
	पूर्णांक den;
पूर्ण;

अटल स्थिर काष्ठा frac_entry frac_table_675m[] = अणु	/* link rate of 270M */
	अणु 52, 295 पूर्ण,	/* 119 M */
	अणु 11, 57 पूर्ण,	/* 130.25 M */
	अणु 63, 307 पूर्ण,	/* 138.50 M */
	अणु 11, 50 पूर्ण,	/* 148.50 M */
	अणु 47, 206 पूर्ण,	/* 154 M */
	अणु 31, 100 पूर्ण,	/* 205.25 M */
	अणु 107, 269 पूर्ण,	/* 268.50 M */
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा frac_entry frac_table_810m[] = अणु /* Link rate of 162M */
	अणु 31, 211 पूर्ण,	/* 119 M */
	अणु 32, 199 पूर्ण,	/* 130.25 M */
	अणु 63, 307 पूर्ण,	/* 138.50 M */
	अणु 11, 60 पूर्ण,	/* 148.50 M */
	अणु 50, 263 पूर्ण,	/* 154 M */
	अणु 31, 120 पूर्ण,	/* 205.25 M */
	अणु 119, 359 पूर्ण,	/* 268.50 M */
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक clk_edp_pixel_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			      अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_rcg2 *rcg = to_clk_rcg2(hw);
	काष्ठा freq_tbl f = *rcg->freq_tbl;
	स्थिर काष्ठा frac_entry *frac;
	पूर्णांक delta = 100000;
	s64 src_rate = parent_rate;
	s64 request;
	u32 mask = BIT(rcg->hid_width) - 1;
	u32 hid_भाग;

	अगर (src_rate == 810000000)
		frac = frac_table_810m;
	अन्यथा
		frac = frac_table_675m;

	क्रम (; frac->num; frac++) अणु
		request = rate;
		request *= frac->den;
		request = भाग_s64(request, frac->num);
		अगर ((src_rate < (request - delta)) ||
		    (src_rate > (request + delta)))
			जारी;

		regmap_पढ़ो(rcg->clkr.regmap, rcg->cmd_rcgr + CFG_REG,
				&hid_भाग);
		f.pre_भाग = hid_भाग;
		f.pre_भाग >>= CFG_SRC_DIV_SHIFT;
		f.pre_भाग &= mask;
		f.m = frac->num;
		f.n = frac->den;

		वापस clk_rcg2_configure(rcg, &f);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक clk_edp_pixel_set_rate_and_parent(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate, u8 index)
अणु
	/* Parent index is set अटलally in frequency table */
	वापस clk_edp_pixel_set_rate(hw, rate, parent_rate);
पूर्ण

अटल पूर्णांक clk_edp_pixel_determine_rate(काष्ठा clk_hw *hw,
					काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_rcg2 *rcg = to_clk_rcg2(hw);
	स्थिर काष्ठा freq_tbl *f = rcg->freq_tbl;
	स्थिर काष्ठा frac_entry *frac;
	पूर्णांक delta = 100000;
	s64 request;
	u32 mask = BIT(rcg->hid_width) - 1;
	u32 hid_भाग;
	पूर्णांक index = qcom_find_src_index(hw, rcg->parent_map, f->src);

	/* Force the correct parent */
	req->best_parent_hw = clk_hw_get_parent_by_index(hw, index);
	req->best_parent_rate = clk_hw_get_rate(req->best_parent_hw);

	अगर (req->best_parent_rate == 810000000)
		frac = frac_table_810m;
	अन्यथा
		frac = frac_table_675m;

	क्रम (; frac->num; frac++) अणु
		request = req->rate;
		request *= frac->den;
		request = भाग_s64(request, frac->num);
		अगर ((req->best_parent_rate < (request - delta)) ||
		    (req->best_parent_rate > (request + delta)))
			जारी;

		regmap_पढ़ो(rcg->clkr.regmap, rcg->cmd_rcgr + CFG_REG,
				&hid_भाग);
		hid_भाग >>= CFG_SRC_DIV_SHIFT;
		hid_भाग &= mask;

		req->rate = calc_rate(req->best_parent_rate,
				      frac->num, frac->den,
				      !!frac->den, hid_भाग);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

स्थिर काष्ठा clk_ops clk_edp_pixel_ops = अणु
	.is_enabled = clk_rcg2_is_enabled,
	.get_parent = clk_rcg2_get_parent,
	.set_parent = clk_rcg2_set_parent,
	.recalc_rate = clk_rcg2_recalc_rate,
	.set_rate = clk_edp_pixel_set_rate,
	.set_rate_and_parent = clk_edp_pixel_set_rate_and_parent,
	.determine_rate = clk_edp_pixel_determine_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_edp_pixel_ops);

अटल पूर्णांक clk_byte_determine_rate(काष्ठा clk_hw *hw,
				   काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_rcg2 *rcg = to_clk_rcg2(hw);
	स्थिर काष्ठा freq_tbl *f = rcg->freq_tbl;
	पूर्णांक index = qcom_find_src_index(hw, rcg->parent_map, f->src);
	अचिन्हित दीर्घ parent_rate, भाग;
	u32 mask = BIT(rcg->hid_width) - 1;
	काष्ठा clk_hw *p;

	अगर (req->rate == 0)
		वापस -EINVAL;

	req->best_parent_hw = p = clk_hw_get_parent_by_index(hw, index);
	req->best_parent_rate = parent_rate = clk_hw_round_rate(p, req->rate);

	भाग = DIV_ROUND_UP((2 * parent_rate), req->rate) - 1;
	भाग = min_t(u32, भाग, mask);

	req->rate = calc_rate(parent_rate, 0, 0, 0, भाग);

	वापस 0;
पूर्ण

अटल पूर्णांक clk_byte_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_rcg2 *rcg = to_clk_rcg2(hw);
	काष्ठा freq_tbl f = *rcg->freq_tbl;
	अचिन्हित दीर्घ भाग;
	u32 mask = BIT(rcg->hid_width) - 1;

	भाग = DIV_ROUND_UP((2 * parent_rate), rate) - 1;
	भाग = min_t(u32, भाग, mask);

	f.pre_भाग = भाग;

	वापस clk_rcg2_configure(rcg, &f);
पूर्ण

अटल पूर्णांक clk_byte_set_rate_and_parent(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate, u8 index)
अणु
	/* Parent index is set अटलally in frequency table */
	वापस clk_byte_set_rate(hw, rate, parent_rate);
पूर्ण

स्थिर काष्ठा clk_ops clk_byte_ops = अणु
	.is_enabled = clk_rcg2_is_enabled,
	.get_parent = clk_rcg2_get_parent,
	.set_parent = clk_rcg2_set_parent,
	.recalc_rate = clk_rcg2_recalc_rate,
	.set_rate = clk_byte_set_rate,
	.set_rate_and_parent = clk_byte_set_rate_and_parent,
	.determine_rate = clk_byte_determine_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_byte_ops);

अटल पूर्णांक clk_byte2_determine_rate(काष्ठा clk_hw *hw,
				    काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_rcg2 *rcg = to_clk_rcg2(hw);
	अचिन्हित दीर्घ parent_rate, भाग;
	u32 mask = BIT(rcg->hid_width) - 1;
	काष्ठा clk_hw *p;
	अचिन्हित दीर्घ rate = req->rate;

	अगर (rate == 0)
		वापस -EINVAL;

	p = req->best_parent_hw;
	req->best_parent_rate = parent_rate = clk_hw_round_rate(p, rate);

	भाग = DIV_ROUND_UP((2 * parent_rate), rate) - 1;
	भाग = min_t(u32, भाग, mask);

	req->rate = calc_rate(parent_rate, 0, 0, 0, भाग);

	वापस 0;
पूर्ण

अटल पूर्णांक clk_byte2_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_rcg2 *rcg = to_clk_rcg2(hw);
	काष्ठा freq_tbl f = अणु 0 पूर्ण;
	अचिन्हित दीर्घ भाग;
	पूर्णांक i, num_parents = clk_hw_get_num_parents(hw);
	u32 mask = BIT(rcg->hid_width) - 1;
	u32 cfg;

	भाग = DIV_ROUND_UP((2 * parent_rate), rate) - 1;
	भाग = min_t(u32, भाग, mask);

	f.pre_भाग = भाग;

	regmap_पढ़ो(rcg->clkr.regmap, rcg->cmd_rcgr + CFG_REG, &cfg);
	cfg &= CFG_SRC_SEL_MASK;
	cfg >>= CFG_SRC_SEL_SHIFT;

	क्रम (i = 0; i < num_parents; i++) अणु
		अगर (cfg == rcg->parent_map[i].cfg) अणु
			f.src = rcg->parent_map[i].src;
			वापस clk_rcg2_configure(rcg, &f);
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक clk_byte2_set_rate_and_parent(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate, u8 index)
अणु
	/* Read the hardware to determine parent during set_rate */
	वापस clk_byte2_set_rate(hw, rate, parent_rate);
पूर्ण

स्थिर काष्ठा clk_ops clk_byte2_ops = अणु
	.is_enabled = clk_rcg2_is_enabled,
	.get_parent = clk_rcg2_get_parent,
	.set_parent = clk_rcg2_set_parent,
	.recalc_rate = clk_rcg2_recalc_rate,
	.set_rate = clk_byte2_set_rate,
	.set_rate_and_parent = clk_byte2_set_rate_and_parent,
	.determine_rate = clk_byte2_determine_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_byte2_ops);

अटल स्थिर काष्ठा frac_entry frac_table_pixel[] = अणु
	अणु 3, 8 पूर्ण,
	अणु 2, 9 पूर्ण,
	अणु 4, 9 पूर्ण,
	अणु 1, 1 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक clk_pixel_determine_rate(काष्ठा clk_hw *hw,
				    काष्ठा clk_rate_request *req)
अणु
	अचिन्हित दीर्घ request, src_rate;
	पूर्णांक delta = 100000;
	स्थिर काष्ठा frac_entry *frac = frac_table_pixel;

	क्रम (; frac->num; frac++) अणु
		request = (req->rate * frac->den) / frac->num;

		src_rate = clk_hw_round_rate(req->best_parent_hw, request);
		अगर ((src_rate < (request - delta)) ||
			(src_rate > (request + delta)))
			जारी;

		req->best_parent_rate = src_rate;
		req->rate = (src_rate * frac->num) / frac->den;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक clk_pixel_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_rcg2 *rcg = to_clk_rcg2(hw);
	काष्ठा freq_tbl f = अणु 0 पूर्ण;
	स्थिर काष्ठा frac_entry *frac = frac_table_pixel;
	अचिन्हित दीर्घ request;
	पूर्णांक delta = 100000;
	u32 mask = BIT(rcg->hid_width) - 1;
	u32 hid_भाग, cfg;
	पूर्णांक i, num_parents = clk_hw_get_num_parents(hw);

	regmap_पढ़ो(rcg->clkr.regmap, rcg->cmd_rcgr + CFG_REG, &cfg);
	cfg &= CFG_SRC_SEL_MASK;
	cfg >>= CFG_SRC_SEL_SHIFT;

	क्रम (i = 0; i < num_parents; i++)
		अगर (cfg == rcg->parent_map[i].cfg) अणु
			f.src = rcg->parent_map[i].src;
			अवरोध;
		पूर्ण

	क्रम (; frac->num; frac++) अणु
		request = (rate * frac->den) / frac->num;

		अगर ((parent_rate < (request - delta)) ||
			(parent_rate > (request + delta)))
			जारी;

		regmap_पढ़ो(rcg->clkr.regmap, rcg->cmd_rcgr + CFG_REG,
				&hid_भाग);
		f.pre_भाग = hid_भाग;
		f.pre_भाग >>= CFG_SRC_DIV_SHIFT;
		f.pre_भाग &= mask;
		f.m = frac->num;
		f.n = frac->den;

		वापस clk_rcg2_configure(rcg, &f);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक clk_pixel_set_rate_and_parent(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ parent_rate, u8 index)
अणु
	वापस clk_pixel_set_rate(hw, rate, parent_rate);
पूर्ण

स्थिर काष्ठा clk_ops clk_pixel_ops = अणु
	.is_enabled = clk_rcg2_is_enabled,
	.get_parent = clk_rcg2_get_parent,
	.set_parent = clk_rcg2_set_parent,
	.recalc_rate = clk_rcg2_recalc_rate,
	.set_rate = clk_pixel_set_rate,
	.set_rate_and_parent = clk_pixel_set_rate_and_parent,
	.determine_rate = clk_pixel_determine_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_pixel_ops);

अटल पूर्णांक clk_gfx3d_determine_rate(काष्ठा clk_hw *hw,
				    काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_rate_request parent_req = अणु पूर्ण;
	काष्ठा clk_rcg2_gfx3d *cgfx = to_clk_rcg2_gfx3d(hw);
	काष्ठा clk_hw *xo, *p0, *p1, *p2;
	अचिन्हित दीर्घ p0_rate;
	u8 mux_भाग = cgfx->भाग;
	पूर्णांक ret;

	p0 = cgfx->hws[0];
	p1 = cgfx->hws[1];
	p2 = cgfx->hws[2];
	/*
	 * This function करोes ping-pong the RCG between PLLs: अगर we करोn't
	 * have at least one fixed PLL and two variable ones,
	 * then it's not going to work correctly.
	 */
	अगर (WARN_ON(!p0 || !p1 || !p2))
		वापस -EINVAL;

	xo = clk_hw_get_parent_by_index(hw, 0);
	अगर (req->rate == clk_hw_get_rate(xo)) अणु
		req->best_parent_hw = xo;
		वापस 0;
	पूर्ण

	अगर (mux_भाग == 0)
		mux_भाग = 1;

	parent_req.rate = req->rate * mux_भाग;

	/* This has to be a fixed rate PLL */
	p0_rate = clk_hw_get_rate(p0);

	अगर (parent_req.rate == p0_rate) अणु
		req->rate = req->best_parent_rate = p0_rate;
		req->best_parent_hw = p0;
		वापस 0;
	पूर्ण

	अगर (req->best_parent_hw == p0) अणु
		/* Are we going back to a previously used rate? */
		अगर (clk_hw_get_rate(p2) == parent_req.rate)
			req->best_parent_hw = p2;
		अन्यथा
			req->best_parent_hw = p1;
	पूर्ण अन्यथा अगर (req->best_parent_hw == p2) अणु
		req->best_parent_hw = p1;
	पूर्ण अन्यथा अणु
		req->best_parent_hw = p2;
	पूर्ण

	ret = __clk_determine_rate(req->best_parent_hw, &parent_req);
	अगर (ret)
		वापस ret;

	req->rate = req->best_parent_rate = parent_req.rate;
	req->rate /= mux_भाग;

	वापस 0;
पूर्ण

अटल पूर्णांक clk_gfx3d_set_rate_and_parent(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ parent_rate, u8 index)
अणु
	काष्ठा clk_rcg2_gfx3d *cgfx = to_clk_rcg2_gfx3d(hw);
	काष्ठा clk_rcg2 *rcg = &cgfx->rcg;
	u32 cfg;
	पूर्णांक ret;

	cfg = rcg->parent_map[index].cfg << CFG_SRC_SEL_SHIFT;
	/* On some tarमाला_लो, the GFX3D RCG may need to भागide PLL frequency */
	अगर (cgfx->भाग > 1)
		cfg |= ((2 * cgfx->भाग) - 1) << CFG_SRC_DIV_SHIFT;

	ret = regmap_ग_लिखो(rcg->clkr.regmap, rcg->cmd_rcgr + CFG_REG, cfg);
	अगर (ret)
		वापस ret;

	वापस update_config(rcg);
पूर्ण

अटल पूर्णांक clk_gfx3d_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			      अचिन्हित दीर्घ parent_rate)
अणु
	/*
	 * We should never get here; clk_gfx3d_determine_rate() should always
	 * make us use a dअगरferent parent than what we're currently using, so
	 * clk_gfx3d_set_rate_and_parent() should always be called.
	 */
	वापस 0;
पूर्ण

स्थिर काष्ठा clk_ops clk_gfx3d_ops = अणु
	.is_enabled = clk_rcg2_is_enabled,
	.get_parent = clk_rcg2_get_parent,
	.set_parent = clk_rcg2_set_parent,
	.recalc_rate = clk_rcg2_recalc_rate,
	.set_rate = clk_gfx3d_set_rate,
	.set_rate_and_parent = clk_gfx3d_set_rate_and_parent,
	.determine_rate = clk_gfx3d_determine_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_gfx3d_ops);

अटल पूर्णांक clk_rcg2_set_क्रमce_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_rcg2 *rcg = to_clk_rcg2(hw);
	स्थिर अक्षर *name = clk_hw_get_name(hw);
	पूर्णांक ret, count;

	ret = regmap_update_bits(rcg->clkr.regmap, rcg->cmd_rcgr + CMD_REG,
				 CMD_ROOT_EN, CMD_ROOT_EN);
	अगर (ret)
		वापस ret;

	/* रुको क्रम RCG to turn ON */
	क्रम (count = 500; count > 0; count--) अणु
		अगर (clk_rcg2_is_enabled(hw))
			वापस 0;

		udelay(1);
	पूर्ण

	pr_err("%s: RCG did not turn on\n", name);
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक clk_rcg2_clear_क्रमce_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_rcg2 *rcg = to_clk_rcg2(hw);

	वापस regmap_update_bits(rcg->clkr.regmap, rcg->cmd_rcgr + CMD_REG,
					CMD_ROOT_EN, 0);
पूर्ण

अटल पूर्णांक
clk_rcg2_shared_क्रमce_enable_clear(काष्ठा clk_hw *hw, स्थिर काष्ठा freq_tbl *f)
अणु
	काष्ठा clk_rcg2 *rcg = to_clk_rcg2(hw);
	पूर्णांक ret;

	ret = clk_rcg2_set_क्रमce_enable(hw);
	अगर (ret)
		वापस ret;

	ret = clk_rcg2_configure(rcg, f);
	अगर (ret)
		वापस ret;

	वापस clk_rcg2_clear_क्रमce_enable(hw);
पूर्ण

अटल पूर्णांक clk_rcg2_shared_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_rcg2 *rcg = to_clk_rcg2(hw);
	स्थिर काष्ठा freq_tbl *f;

	f = qcom_find_freq(rcg->freq_tbl, rate);
	अगर (!f)
		वापस -EINVAL;

	/*
	 * In हाल घड़ी is disabled, update the CFG, M, N and D रेजिस्टरs
	 * and करोn't hit the update bit of CMD रेजिस्टर.
	 */
	अगर (!__clk_is_enabled(hw->clk))
		वापस __clk_rcg2_configure(rcg, f);

	वापस clk_rcg2_shared_क्रमce_enable_clear(hw, f);
पूर्ण

अटल पूर्णांक clk_rcg2_shared_set_rate_and_parent(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate, u8 index)
अणु
	वापस clk_rcg2_shared_set_rate(hw, rate, parent_rate);
पूर्ण

अटल पूर्णांक clk_rcg2_shared_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_rcg2 *rcg = to_clk_rcg2(hw);
	पूर्णांक ret;

	/*
	 * Set the update bit because required configuration has alपढ़ोy
	 * been written in clk_rcg2_shared_set_rate()
	 */
	ret = clk_rcg2_set_क्रमce_enable(hw);
	अगर (ret)
		वापस ret;

	ret = update_config(rcg);
	अगर (ret)
		वापस ret;

	वापस clk_rcg2_clear_क्रमce_enable(hw);
पूर्ण

अटल व्योम clk_rcg2_shared_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_rcg2 *rcg = to_clk_rcg2(hw);
	u32 cfg;

	/*
	 * Store current configuration as चयनing to safe source would clear
	 * the SRC and DIV of CFG रेजिस्टर
	 */
	regmap_पढ़ो(rcg->clkr.regmap, rcg->cmd_rcgr + CFG_REG, &cfg);

	/*
	 * Park the RCG at a safe configuration - sourced off of safe source.
	 * Force enable and disable the RCG जबतक configuring it to safeguard
	 * against any update संकेत coming from the करोwnstream घड़ी.
	 * The current parent is still prepared and enabled at this poपूर्णांक, and
	 * the safe source is always on जबतक application processor subप्रणाली
	 * is online. Thereक्रमe, the RCG can safely चयन its parent.
	 */
	clk_rcg2_set_क्रमce_enable(hw);

	regmap_ग_लिखो(rcg->clkr.regmap, rcg->cmd_rcgr + CFG_REG,
		     rcg->safe_src_index << CFG_SRC_SEL_SHIFT);

	update_config(rcg);

	clk_rcg2_clear_क्रमce_enable(hw);

	/* Write back the stored configuration corresponding to current rate */
	regmap_ग_लिखो(rcg->clkr.regmap, rcg->cmd_rcgr + CFG_REG, cfg);
पूर्ण

स्थिर काष्ठा clk_ops clk_rcg2_shared_ops = अणु
	.enable = clk_rcg2_shared_enable,
	.disable = clk_rcg2_shared_disable,
	.get_parent = clk_rcg2_get_parent,
	.set_parent = clk_rcg2_set_parent,
	.recalc_rate = clk_rcg2_recalc_rate,
	.determine_rate = clk_rcg2_determine_rate,
	.set_rate = clk_rcg2_shared_set_rate,
	.set_rate_and_parent = clk_rcg2_shared_set_rate_and_parent,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_rcg2_shared_ops);

/* Common APIs to be used क्रम DFS based RCGR */
अटल व्योम clk_rcg2_dfs_populate_freq(काष्ठा clk_hw *hw, अचिन्हित पूर्णांक l,
				       काष्ठा freq_tbl *f)
अणु
	काष्ठा clk_rcg2 *rcg = to_clk_rcg2(hw);
	काष्ठा clk_hw *p;
	अचिन्हित दीर्घ prate = 0;
	u32 val, mask, cfg, mode, src;
	पूर्णांक i, num_parents;

	regmap_पढ़ो(rcg->clkr.regmap, rcg->cmd_rcgr + SE_PERF_DFSR(l), &cfg);

	mask = BIT(rcg->hid_width) - 1;
	f->pre_भाग = 1;
	अगर (cfg & mask)
		f->pre_भाग = cfg & mask;

	src = cfg & CFG_SRC_SEL_MASK;
	src >>= CFG_SRC_SEL_SHIFT;

	num_parents = clk_hw_get_num_parents(hw);
	क्रम (i = 0; i < num_parents; i++) अणु
		अगर (src == rcg->parent_map[i].cfg) अणु
			f->src = rcg->parent_map[i].src;
			p = clk_hw_get_parent_by_index(&rcg->clkr.hw, i);
			prate = clk_hw_get_rate(p);
		पूर्ण
	पूर्ण

	mode = cfg & CFG_MODE_MASK;
	mode >>= CFG_MODE_SHIFT;
	अगर (mode) अणु
		mask = BIT(rcg->mnd_width) - 1;
		regmap_पढ़ो(rcg->clkr.regmap, rcg->cmd_rcgr + SE_PERF_M_DFSR(l),
			    &val);
		val &= mask;
		f->m = val;

		regmap_पढ़ो(rcg->clkr.regmap, rcg->cmd_rcgr + SE_PERF_N_DFSR(l),
			    &val);
		val = ~val;
		val &= mask;
		val += f->m;
		f->n = val;
	पूर्ण

	f->freq = calc_rate(prate, f->m, f->n, mode, f->pre_भाग);
पूर्ण

अटल पूर्णांक clk_rcg2_dfs_populate_freq_table(काष्ठा clk_rcg2 *rcg)
अणु
	काष्ठा freq_tbl *freq_tbl;
	पूर्णांक i;

	/* Allocate space क्रम 1 extra since table is शून्य terminated */
	freq_tbl = kसुस्मृति(MAX_PERF_LEVEL + 1, माप(*freq_tbl), GFP_KERNEL);
	अगर (!freq_tbl)
		वापस -ENOMEM;
	rcg->freq_tbl = freq_tbl;

	क्रम (i = 0; i < MAX_PERF_LEVEL; i++)
		clk_rcg2_dfs_populate_freq(&rcg->clkr.hw, i, freq_tbl + i);

	वापस 0;
पूर्ण

अटल पूर्णांक clk_rcg2_dfs_determine_rate(काष्ठा clk_hw *hw,
				   काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_rcg2 *rcg = to_clk_rcg2(hw);
	पूर्णांक ret;

	अगर (!rcg->freq_tbl) अणु
		ret = clk_rcg2_dfs_populate_freq_table(rcg);
		अगर (ret) अणु
			pr_err("Failed to update DFS tables for %s\n",
					clk_hw_get_name(hw));
			वापस ret;
		पूर्ण
	पूर्ण

	वापस clk_rcg2_determine_rate(hw, req);
पूर्ण

अटल अचिन्हित दीर्घ
clk_rcg2_dfs_recalc_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_rcg2 *rcg = to_clk_rcg2(hw);
	u32 level, mask, cfg, m = 0, n = 0, mode, pre_भाग;

	regmap_पढ़ो(rcg->clkr.regmap,
		    rcg->cmd_rcgr + SE_CMD_DFSR_OFFSET, &level);
	level &= GENMASK(4, 1);
	level >>= 1;

	अगर (rcg->freq_tbl)
		वापस rcg->freq_tbl[level].freq;

	/*
	 * Assume that parent_rate is actually the parent because
	 * we can't करो any better at figuring it out when the table
	 * hasn't been populated yet. We only populate the table
	 * in determine_rate because we can't guarantee the parents
	 * will be रेजिस्टरed with the framework until then.
	 */
	regmap_पढ़ो(rcg->clkr.regmap, rcg->cmd_rcgr + SE_PERF_DFSR(level),
		    &cfg);

	mask = BIT(rcg->hid_width) - 1;
	pre_भाग = 1;
	अगर (cfg & mask)
		pre_भाग = cfg & mask;

	mode = cfg & CFG_MODE_MASK;
	mode >>= CFG_MODE_SHIFT;
	अगर (mode) अणु
		mask = BIT(rcg->mnd_width) - 1;
		regmap_पढ़ो(rcg->clkr.regmap,
			    rcg->cmd_rcgr + SE_PERF_M_DFSR(level), &m);
		m &= mask;

		regmap_पढ़ो(rcg->clkr.regmap,
			    rcg->cmd_rcgr + SE_PERF_N_DFSR(level), &n);
		n = ~n;
		n &= mask;
		n += m;
	पूर्ण

	वापस calc_rate(parent_rate, m, n, mode, pre_भाग);
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_rcg2_dfs_ops = अणु
	.is_enabled = clk_rcg2_is_enabled,
	.get_parent = clk_rcg2_get_parent,
	.determine_rate = clk_rcg2_dfs_determine_rate,
	.recalc_rate = clk_rcg2_dfs_recalc_rate,
पूर्ण;

अटल पूर्णांक clk_rcg2_enable_dfs(स्थिर काष्ठा clk_rcg_dfs_data *data,
			       काष्ठा regmap *regmap)
अणु
	काष्ठा clk_rcg2 *rcg = data->rcg;
	काष्ठा clk_init_data *init = data->init;
	u32 val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, rcg->cmd_rcgr + SE_CMD_DFSR_OFFSET, &val);
	अगर (ret)
		वापस -EINVAL;

	अगर (!(val & SE_CMD_DFS_EN))
		वापस 0;

	/*
	 * Rate changes with consumer writing a रेजिस्टर in
	 * their own I/O region
	 */
	init->flags |= CLK_GET_RATE_NOCACHE;
	init->ops = &clk_rcg2_dfs_ops;

	rcg->freq_tbl = शून्य;

	वापस 0;
पूर्ण

पूर्णांक qcom_cc_रेजिस्टर_rcg_dfs(काष्ठा regmap *regmap,
			     स्थिर काष्ठा clk_rcg_dfs_data *rcgs, माप_प्रकार len)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < len; i++) अणु
		ret = clk_rcg2_enable_dfs(&rcgs[i], regmap);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(qcom_cc_रेजिस्टर_rcg_dfs);

अटल पूर्णांक clk_rcg2_dp_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_rcg2 *rcg = to_clk_rcg2(hw);
	काष्ठा freq_tbl f = अणु 0 पूर्ण;
	u32 mask = BIT(rcg->hid_width) - 1;
	u32 hid_भाग, cfg;
	पूर्णांक i, num_parents = clk_hw_get_num_parents(hw);
	अचिन्हित दीर्घ num, den;

	rational_best_approximation(parent_rate, rate,
			GENMASK(rcg->mnd_width - 1, 0),
			GENMASK(rcg->mnd_width - 1, 0), &den, &num);

	अगर (!num || !den)
		वापस -EINVAL;

	regmap_पढ़ो(rcg->clkr.regmap, rcg->cmd_rcgr + CFG_REG, &cfg);
	hid_भाग = cfg;
	cfg &= CFG_SRC_SEL_MASK;
	cfg >>= CFG_SRC_SEL_SHIFT;

	क्रम (i = 0; i < num_parents; i++) अणु
		अगर (cfg == rcg->parent_map[i].cfg) अणु
			f.src = rcg->parent_map[i].src;
			अवरोध;
		पूर्ण
	पूर्ण

	f.pre_भाग = hid_भाग;
	f.pre_भाग >>= CFG_SRC_DIV_SHIFT;
	f.pre_भाग &= mask;

	अगर (num != den) अणु
		f.m = num;
		f.n = den;
	पूर्ण अन्यथा अणु
		f.m = 0;
		f.n = 0;
	पूर्ण

	वापस clk_rcg2_configure(rcg, &f);
पूर्ण

अटल पूर्णांक clk_rcg2_dp_set_rate_and_parent(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate, u8 index)
अणु
	वापस clk_rcg2_dp_set_rate(hw, rate, parent_rate);
पूर्ण

अटल पूर्णांक clk_rcg2_dp_determine_rate(काष्ठा clk_hw *hw,
				काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_rcg2 *rcg = to_clk_rcg2(hw);
	अचिन्हित दीर्घ num, den;
	u64 पंचांगp;

	/* Parent rate is a fixed phy link rate */
	rational_best_approximation(req->best_parent_rate, req->rate,
			GENMASK(rcg->mnd_width - 1, 0),
			GENMASK(rcg->mnd_width - 1, 0), &den, &num);

	अगर (!num || !den)
		वापस -EINVAL;

	पंचांगp = req->best_parent_rate * num;
	करो_भाग(पंचांगp, den);
	req->rate = पंचांगp;

	वापस 0;
पूर्ण

स्थिर काष्ठा clk_ops clk_dp_ops = अणु
	.is_enabled = clk_rcg2_is_enabled,
	.get_parent = clk_rcg2_get_parent,
	.set_parent = clk_rcg2_set_parent,
	.recalc_rate = clk_rcg2_recalc_rate,
	.set_rate = clk_rcg2_dp_set_rate,
	.set_rate_and_parent = clk_rcg2_dp_set_rate_and_parent,
	.determine_rate = clk_rcg2_dp_determine_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_dp_ops);
