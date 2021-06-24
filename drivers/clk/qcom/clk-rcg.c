<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/regmap.h>

#समावेश <यंत्र/भाग64.h>

#समावेश "clk-rcg.h"
#समावेश "common.h"

अटल u32 ns_to_src(काष्ठा src_sel *s, u32 ns)
अणु
	ns >>= s->src_sel_shअगरt;
	ns &= SRC_SEL_MASK;
	वापस ns;
पूर्ण

अटल u32 src_to_ns(काष्ठा src_sel *s, u8 src, u32 ns)
अणु
	u32 mask;

	mask = SRC_SEL_MASK;
	mask <<= s->src_sel_shअगरt;
	ns &= ~mask;

	ns |= src << s->src_sel_shअगरt;
	वापस ns;
पूर्ण

अटल u8 clk_rcg_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_rcg *rcg = to_clk_rcg(hw);
	पूर्णांक num_parents = clk_hw_get_num_parents(hw);
	u32 ns;
	पूर्णांक i, ret;

	ret = regmap_पढ़ो(rcg->clkr.regmap, rcg->ns_reg, &ns);
	अगर (ret)
		जाओ err;
	ns = ns_to_src(&rcg->s, ns);
	क्रम (i = 0; i < num_parents; i++)
		अगर (ns == rcg->s.parent_map[i].cfg)
			वापस i;

err:
	pr_debug("%s: Clock %s has invalid parent, using default.\n",
		 __func__, clk_hw_get_name(hw));
	वापस 0;
पूर्ण

अटल पूर्णांक reg_to_bank(काष्ठा clk_dyn_rcg *rcg, u32 bank)
अणु
	bank &= BIT(rcg->mux_sel_bit);
	वापस !!bank;
पूर्ण

अटल u8 clk_dyn_rcg_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_dyn_rcg *rcg = to_clk_dyn_rcg(hw);
	पूर्णांक num_parents = clk_hw_get_num_parents(hw);
	u32 ns, reg;
	पूर्णांक bank;
	पूर्णांक i, ret;
	काष्ठा src_sel *s;

	ret = regmap_पढ़ो(rcg->clkr.regmap, rcg->bank_reg, &reg);
	अगर (ret)
		जाओ err;
	bank = reg_to_bank(rcg, reg);
	s = &rcg->s[bank];

	ret = regmap_पढ़ो(rcg->clkr.regmap, rcg->ns_reg[bank], &ns);
	अगर (ret)
		जाओ err;
	ns = ns_to_src(s, ns);

	क्रम (i = 0; i < num_parents; i++)
		अगर (ns == s->parent_map[i].cfg)
			वापस i;

err:
	pr_debug("%s: Clock %s has invalid parent, using default.\n",
		 __func__, clk_hw_get_name(hw));
	वापस 0;
पूर्ण

अटल पूर्णांक clk_rcg_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा clk_rcg *rcg = to_clk_rcg(hw);
	u32 ns;

	regmap_पढ़ो(rcg->clkr.regmap, rcg->ns_reg, &ns);
	ns = src_to_ns(&rcg->s, rcg->s.parent_map[index].cfg, ns);
	regmap_ग_लिखो(rcg->clkr.regmap, rcg->ns_reg, ns);

	वापस 0;
पूर्ण

अटल u32 md_to_m(काष्ठा mn *mn, u32 md)
अणु
	md >>= mn->m_val_shअगरt;
	md &= BIT(mn->width) - 1;
	वापस md;
पूर्ण

अटल u32 ns_to_pre_भाग(काष्ठा pre_भाग *p, u32 ns)
अणु
	ns >>= p->pre_भाग_shअगरt;
	ns &= BIT(p->pre_भाग_width) - 1;
	वापस ns;
पूर्ण

अटल u32 pre_भाग_प्रकारo_ns(काष्ठा pre_भाग *p, u8 pre_भाग, u32 ns)
अणु
	u32 mask;

	mask = BIT(p->pre_भाग_width) - 1;
	mask <<= p->pre_भाग_shअगरt;
	ns &= ~mask;

	ns |= pre_भाग << p->pre_भाग_shअगरt;
	वापस ns;
पूर्ण

अटल u32 mn_to_md(काष्ठा mn *mn, u32 m, u32 n, u32 md)
अणु
	u32 mask, mask_w;

	mask_w = BIT(mn->width) - 1;
	mask = (mask_w << mn->m_val_shअगरt) | mask_w;
	md &= ~mask;

	अगर (n) अणु
		m <<= mn->m_val_shअगरt;
		md |= m;
		md |= ~n & mask_w;
	पूर्ण

	वापस md;
पूर्ण

अटल u32 ns_m_to_n(काष्ठा mn *mn, u32 ns, u32 m)
अणु
	ns = ~ns >> mn->n_val_shअगरt;
	ns &= BIT(mn->width) - 1;
	वापस ns + m;
पूर्ण

अटल u32 reg_to_mnctr_mode(काष्ठा mn *mn, u32 val)
अणु
	val >>= mn->mnctr_mode_shअगरt;
	val &= MNCTR_MODE_MASK;
	वापस val;
पूर्ण

अटल u32 mn_to_ns(काष्ठा mn *mn, u32 m, u32 n, u32 ns)
अणु
	u32 mask;

	mask = BIT(mn->width) - 1;
	mask <<= mn->n_val_shअगरt;
	ns &= ~mask;

	अगर (n) अणु
		n = n - m;
		n = ~n;
		n &= BIT(mn->width) - 1;
		n <<= mn->n_val_shअगरt;
		ns |= n;
	पूर्ण

	वापस ns;
पूर्ण

अटल u32 mn_to_reg(काष्ठा mn *mn, u32 m, u32 n, u32 val)
अणु
	u32 mask;

	mask = MNCTR_MODE_MASK << mn->mnctr_mode_shअगरt;
	mask |= BIT(mn->mnctr_en_bit);
	val &= ~mask;

	अगर (n) अणु
		val |= BIT(mn->mnctr_en_bit);
		val |= MNCTR_MODE_DUAL << mn->mnctr_mode_shअगरt;
	पूर्ण

	वापस val;
पूर्ण

अटल पूर्णांक configure_bank(काष्ठा clk_dyn_rcg *rcg, स्थिर काष्ठा freq_tbl *f)
अणु
	u32 ns, md, reg;
	पूर्णांक bank, new_bank, ret, index;
	काष्ठा mn *mn;
	काष्ठा pre_भाग *p;
	काष्ठा src_sel *s;
	bool enabled;
	u32 md_reg, ns_reg;
	bool banked_mn = !!rcg->mn[1].width;
	bool banked_p = !!rcg->p[1].pre_भाग_width;
	काष्ठा clk_hw *hw = &rcg->clkr.hw;

	enabled = __clk_is_enabled(hw->clk);

	ret = regmap_पढ़ो(rcg->clkr.regmap, rcg->bank_reg, &reg);
	अगर (ret)
		वापस ret;
	bank = reg_to_bank(rcg, reg);
	new_bank = enabled ? !bank : bank;

	ns_reg = rcg->ns_reg[new_bank];
	ret = regmap_पढ़ो(rcg->clkr.regmap, ns_reg, &ns);
	अगर (ret)
		वापस ret;

	अगर (banked_mn) अणु
		mn = &rcg->mn[new_bank];
		md_reg = rcg->md_reg[new_bank];

		ns |= BIT(mn->mnctr_reset_bit);
		ret = regmap_ग_लिखो(rcg->clkr.regmap, ns_reg, ns);
		अगर (ret)
			वापस ret;

		ret = regmap_पढ़ो(rcg->clkr.regmap, md_reg, &md);
		अगर (ret)
			वापस ret;
		md = mn_to_md(mn, f->m, f->n, md);
		ret = regmap_ग_लिखो(rcg->clkr.regmap, md_reg, md);
		अगर (ret)
			वापस ret;
		ns = mn_to_ns(mn, f->m, f->n, ns);
		ret = regmap_ग_लिखो(rcg->clkr.regmap, ns_reg, ns);
		अगर (ret)
			वापस ret;

		/* Two NS रेजिस्टरs means mode control is in NS रेजिस्टर */
		अगर (rcg->ns_reg[0] != rcg->ns_reg[1]) अणु
			ns = mn_to_reg(mn, f->m, f->n, ns);
			ret = regmap_ग_लिखो(rcg->clkr.regmap, ns_reg, ns);
			अगर (ret)
				वापस ret;
		पूर्ण अन्यथा अणु
			reg = mn_to_reg(mn, f->m, f->n, reg);
			ret = regmap_ग_लिखो(rcg->clkr.regmap, rcg->bank_reg,
					   reg);
			अगर (ret)
				वापस ret;
		पूर्ण

		ns &= ~BIT(mn->mnctr_reset_bit);
		ret = regmap_ग_लिखो(rcg->clkr.regmap, ns_reg, ns);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (banked_p) अणु
		p = &rcg->p[new_bank];
		ns = pre_भाग_प्रकारo_ns(p, f->pre_भाग - 1, ns);
	पूर्ण

	s = &rcg->s[new_bank];
	index = qcom_find_src_index(hw, s->parent_map, f->src);
	अगर (index < 0)
		वापस index;
	ns = src_to_ns(s, s->parent_map[index].cfg, ns);
	ret = regmap_ग_लिखो(rcg->clkr.regmap, ns_reg, ns);
	अगर (ret)
		वापस ret;

	अगर (enabled) अणु
		ret = regmap_पढ़ो(rcg->clkr.regmap, rcg->bank_reg, &reg);
		अगर (ret)
			वापस ret;
		reg ^= BIT(rcg->mux_sel_bit);
		ret = regmap_ग_लिखो(rcg->clkr.regmap, rcg->bank_reg, reg);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक clk_dyn_rcg_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा clk_dyn_rcg *rcg = to_clk_dyn_rcg(hw);
	u32 ns, md, reg;
	पूर्णांक bank;
	काष्ठा freq_tbl f = अणु 0 पूर्ण;
	bool banked_mn = !!rcg->mn[1].width;
	bool banked_p = !!rcg->p[1].pre_भाग_width;

	regmap_पढ़ो(rcg->clkr.regmap, rcg->bank_reg, &reg);
	bank = reg_to_bank(rcg, reg);

	regmap_पढ़ो(rcg->clkr.regmap, rcg->ns_reg[bank], &ns);

	अगर (banked_mn) अणु
		regmap_पढ़ो(rcg->clkr.regmap, rcg->md_reg[bank], &md);
		f.m = md_to_m(&rcg->mn[bank], md);
		f.n = ns_m_to_n(&rcg->mn[bank], ns, f.m);
	पूर्ण

	अगर (banked_p)
		f.pre_भाग = ns_to_pre_भाग(&rcg->p[bank], ns) + 1;

	f.src = qcom_find_src_index(hw, rcg->s[bank].parent_map, index);
	वापस configure_bank(rcg, &f);
पूर्ण

/*
 * Calculate m/n:d rate
 *
 *          parent_rate     m
 *   rate = ----------- x  ---
 *            pre_भाग       n
 */
अटल अचिन्हित दीर्घ
calc_rate(अचिन्हित दीर्घ rate, u32 m, u32 n, u32 mode, u32 pre_भाग)
अणु
	अगर (pre_भाग)
		rate /= pre_भाग + 1;

	अगर (mode) अणु
		u64 पंचांगp = rate;
		पंचांगp *= m;
		करो_भाग(पंचांगp, n);
		rate = पंचांगp;
	पूर्ण

	वापस rate;
पूर्ण

अटल अचिन्हित दीर्घ
clk_rcg_recalc_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_rcg *rcg = to_clk_rcg(hw);
	u32 pre_भाग, m = 0, n = 0, ns, md, mode = 0;
	काष्ठा mn *mn = &rcg->mn;

	regmap_पढ़ो(rcg->clkr.regmap, rcg->ns_reg, &ns);
	pre_भाग = ns_to_pre_भाग(&rcg->p, ns);

	अगर (rcg->mn.width) अणु
		regmap_पढ़ो(rcg->clkr.regmap, rcg->md_reg, &md);
		m = md_to_m(mn, md);
		n = ns_m_to_n(mn, ns, m);
		/* MN counter mode is in hw.enable_reg someबार */
		अगर (rcg->clkr.enable_reg != rcg->ns_reg)
			regmap_पढ़ो(rcg->clkr.regmap, rcg->clkr.enable_reg, &mode);
		अन्यथा
			mode = ns;
		mode = reg_to_mnctr_mode(mn, mode);
	पूर्ण

	वापस calc_rate(parent_rate, m, n, mode, pre_भाग);
पूर्ण

अटल अचिन्हित दीर्घ
clk_dyn_rcg_recalc_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_dyn_rcg *rcg = to_clk_dyn_rcg(hw);
	u32 m, n, pre_भाग, ns, md, mode, reg;
	पूर्णांक bank;
	काष्ठा mn *mn;
	bool banked_p = !!rcg->p[1].pre_भाग_width;
	bool banked_mn = !!rcg->mn[1].width;

	regmap_पढ़ो(rcg->clkr.regmap, rcg->bank_reg, &reg);
	bank = reg_to_bank(rcg, reg);

	regmap_पढ़ो(rcg->clkr.regmap, rcg->ns_reg[bank], &ns);
	m = n = pre_भाग = mode = 0;

	अगर (banked_mn) अणु
		mn = &rcg->mn[bank];
		regmap_पढ़ो(rcg->clkr.regmap, rcg->md_reg[bank], &md);
		m = md_to_m(mn, md);
		n = ns_m_to_n(mn, ns, m);
		/* Two NS रेजिस्टरs means mode control is in NS रेजिस्टर */
		अगर (rcg->ns_reg[0] != rcg->ns_reg[1])
			reg = ns;
		mode = reg_to_mnctr_mode(mn, reg);
	पूर्ण

	अगर (banked_p)
		pre_भाग = ns_to_pre_भाग(&rcg->p[bank], ns);

	वापस calc_rate(parent_rate, m, n, mode, pre_भाग);
पूर्ण

अटल पूर्णांक _freq_tbl_determine_rate(काष्ठा clk_hw *hw, स्थिर काष्ठा freq_tbl *f,
		काष्ठा clk_rate_request *req,
		स्थिर काष्ठा parent_map *parent_map)
अणु
	अचिन्हित दीर्घ clk_flags, rate = req->rate;
	काष्ठा clk_hw *p;
	पूर्णांक index;

	f = qcom_find_freq(f, rate);
	अगर (!f)
		वापस -EINVAL;

	index = qcom_find_src_index(hw, parent_map, f->src);
	अगर (index < 0)
		वापस index;

	clk_flags = clk_hw_get_flags(hw);
	p = clk_hw_get_parent_by_index(hw, index);
	अगर (clk_flags & CLK_SET_RATE_PARENT) अणु
		rate = rate * f->pre_भाग;
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

अटल पूर्णांक clk_rcg_determine_rate(काष्ठा clk_hw *hw,
				  काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_rcg *rcg = to_clk_rcg(hw);

	वापस _freq_tbl_determine_rate(hw, rcg->freq_tbl, req,
					rcg->s.parent_map);
पूर्ण

अटल पूर्णांक clk_dyn_rcg_determine_rate(काष्ठा clk_hw *hw,
				      काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_dyn_rcg *rcg = to_clk_dyn_rcg(hw);
	u32 reg;
	पूर्णांक bank;
	काष्ठा src_sel *s;

	regmap_पढ़ो(rcg->clkr.regmap, rcg->bank_reg, &reg);
	bank = reg_to_bank(rcg, reg);
	s = &rcg->s[bank];

	वापस _freq_tbl_determine_rate(hw, rcg->freq_tbl, req, s->parent_map);
पूर्ण

अटल पूर्णांक clk_rcg_bypass_determine_rate(काष्ठा clk_hw *hw,
					 काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_rcg *rcg = to_clk_rcg(hw);
	स्थिर काष्ठा freq_tbl *f = rcg->freq_tbl;
	काष्ठा clk_hw *p;
	पूर्णांक index = qcom_find_src_index(hw, rcg->s.parent_map, f->src);

	req->best_parent_hw = p = clk_hw_get_parent_by_index(hw, index);
	req->best_parent_rate = clk_hw_round_rate(p, req->rate);
	req->rate = req->best_parent_rate;

	वापस 0;
पूर्ण

अटल पूर्णांक __clk_rcg_set_rate(काष्ठा clk_rcg *rcg, स्थिर काष्ठा freq_tbl *f)
अणु
	u32 ns, md, ctl;
	काष्ठा mn *mn = &rcg->mn;
	u32 mask = 0;
	अचिन्हित पूर्णांक reset_reg;

	अगर (rcg->mn.reset_in_cc)
		reset_reg = rcg->clkr.enable_reg;
	अन्यथा
		reset_reg = rcg->ns_reg;

	अगर (rcg->mn.width) अणु
		mask = BIT(mn->mnctr_reset_bit);
		regmap_update_bits(rcg->clkr.regmap, reset_reg, mask, mask);

		regmap_पढ़ो(rcg->clkr.regmap, rcg->md_reg, &md);
		md = mn_to_md(mn, f->m, f->n, md);
		regmap_ग_लिखो(rcg->clkr.regmap, rcg->md_reg, md);

		regmap_पढ़ो(rcg->clkr.regmap, rcg->ns_reg, &ns);
		/* MN counter mode is in hw.enable_reg someबार */
		अगर (rcg->clkr.enable_reg != rcg->ns_reg) अणु
			regmap_पढ़ो(rcg->clkr.regmap, rcg->clkr.enable_reg, &ctl);
			ctl = mn_to_reg(mn, f->m, f->n, ctl);
			regmap_ग_लिखो(rcg->clkr.regmap, rcg->clkr.enable_reg, ctl);
		पूर्ण अन्यथा अणु
			ns = mn_to_reg(mn, f->m, f->n, ns);
		पूर्ण
		ns = mn_to_ns(mn, f->m, f->n, ns);
	पूर्ण अन्यथा अणु
		regmap_पढ़ो(rcg->clkr.regmap, rcg->ns_reg, &ns);
	पूर्ण

	ns = pre_भाग_प्रकारo_ns(&rcg->p, f->pre_भाग - 1, ns);
	regmap_ग_लिखो(rcg->clkr.regmap, rcg->ns_reg, ns);

	regmap_update_bits(rcg->clkr.regmap, reset_reg, mask, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक clk_rcg_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_rcg *rcg = to_clk_rcg(hw);
	स्थिर काष्ठा freq_tbl *f;

	f = qcom_find_freq(rcg->freq_tbl, rate);
	अगर (!f)
		वापस -EINVAL;

	वापस __clk_rcg_set_rate(rcg, f);
पूर्ण

अटल पूर्णांक clk_rcg_bypass_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_rcg *rcg = to_clk_rcg(hw);

	वापस __clk_rcg_set_rate(rcg, rcg->freq_tbl);
पूर्ण

अटल पूर्णांक clk_rcg_bypass2_determine_rate(काष्ठा clk_hw *hw,
				काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_hw *p;

	p = req->best_parent_hw;
	req->best_parent_rate = clk_hw_round_rate(p, req->rate);
	req->rate = req->best_parent_rate;

	वापस 0;
पूर्ण

अटल पूर्णांक clk_rcg_bypass2_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_rcg *rcg = to_clk_rcg(hw);
	काष्ठा freq_tbl f = अणु 0 पूर्ण;
	u32 ns, src;
	पूर्णांक i, ret, num_parents = clk_hw_get_num_parents(hw);

	ret = regmap_पढ़ो(rcg->clkr.regmap, rcg->ns_reg, &ns);
	अगर (ret)
		वापस ret;

	src = ns_to_src(&rcg->s, ns);
	f.pre_भाग = ns_to_pre_भाग(&rcg->p, ns) + 1;

	क्रम (i = 0; i < num_parents; i++) अणु
		अगर (src == rcg->s.parent_map[i].cfg) अणु
			f.src = rcg->s.parent_map[i].src;
			वापस __clk_rcg_set_rate(rcg, &f);
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक clk_rcg_bypass2_set_rate_and_parent(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate, u8 index)
अणु
	/* Read the hardware to determine parent during set_rate */
	वापस clk_rcg_bypass2_set_rate(hw, rate, parent_rate);
पूर्ण

काष्ठा frac_entry अणु
	पूर्णांक num;
	पूर्णांक den;
पूर्ण;

अटल स्थिर काष्ठा frac_entry pixel_table[] = अणु
	अणु 1, 2 पूर्ण,
	अणु 1, 3 पूर्ण,
	अणु 3, 16 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक clk_rcg_pixel_determine_rate(काष्ठा clk_hw *hw,
		काष्ठा clk_rate_request *req)
अणु
	पूर्णांक delta = 100000;
	स्थिर काष्ठा frac_entry *frac = pixel_table;
	अचिन्हित दीर्घ request, src_rate;

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

अटल पूर्णांक clk_rcg_pixel_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_rcg *rcg = to_clk_rcg(hw);
	पूर्णांक delta = 100000;
	स्थिर काष्ठा frac_entry *frac = pixel_table;
	अचिन्हित दीर्घ request;
	काष्ठा freq_tbl f = अणु 0 पूर्ण;
	u32 ns, src;
	पूर्णांक i, ret, num_parents = clk_hw_get_num_parents(hw);

	ret = regmap_पढ़ो(rcg->clkr.regmap, rcg->ns_reg, &ns);
	अगर (ret)
		वापस ret;

	src = ns_to_src(&rcg->s, ns);

	क्रम (i = 0; i < num_parents; i++) अणु
		अगर (src == rcg->s.parent_map[i].cfg) अणु
			f.src = rcg->s.parent_map[i].src;
			अवरोध;
		पूर्ण
	पूर्ण

	/* bypass the pre भागider */
	f.pre_भाग = 1;

	/* let us find appropriate m/n values क्रम this */
	क्रम (; frac->num; frac++) अणु
		request = (rate * frac->den) / frac->num;

		अगर ((parent_rate < (request - delta)) ||
			(parent_rate > (request + delta)))
			जारी;

		f.m = frac->num;
		f.n = frac->den;

		वापस __clk_rcg_set_rate(rcg, &f);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक clk_rcg_pixel_set_rate_and_parent(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate, u8 index)
अणु
	वापस clk_rcg_pixel_set_rate(hw, rate, parent_rate);
पूर्ण

अटल पूर्णांक clk_rcg_esc_determine_rate(काष्ठा clk_hw *hw,
		काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_rcg *rcg = to_clk_rcg(hw);
	पूर्णांक pre_भाग_max = BIT(rcg->p.pre_भाग_width);
	पूर्णांक भाग;
	अचिन्हित दीर्घ src_rate;

	अगर (req->rate == 0)
		वापस -EINVAL;

	src_rate = clk_hw_get_rate(req->best_parent_hw);

	भाग = src_rate / req->rate;

	अगर (भाग >= 1 && भाग <= pre_भाग_max) अणु
		req->best_parent_rate = src_rate;
		req->rate = src_rate / भाग;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक clk_rcg_esc_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_rcg *rcg = to_clk_rcg(hw);
	काष्ठा freq_tbl f = अणु 0 पूर्ण;
	पूर्णांक pre_भाग_max = BIT(rcg->p.pre_भाग_width);
	पूर्णांक भाग;
	u32 ns;
	पूर्णांक i, ret, num_parents = clk_hw_get_num_parents(hw);

	अगर (rate == 0)
		वापस -EINVAL;

	ret = regmap_पढ़ो(rcg->clkr.regmap, rcg->ns_reg, &ns);
	अगर (ret)
		वापस ret;

	ns = ns_to_src(&rcg->s, ns);

	क्रम (i = 0; i < num_parents; i++) अणु
		अगर (ns == rcg->s.parent_map[i].cfg) अणु
			f.src = rcg->s.parent_map[i].src;
			अवरोध;
		पूर्ण
	पूर्ण

	भाग = parent_rate / rate;

	अगर (भाग >= 1 && भाग <= pre_भाग_max) अणु
		f.pre_भाग = भाग;
		वापस __clk_rcg_set_rate(rcg, &f);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक clk_rcg_esc_set_rate_and_parent(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate, u8 index)
अणु
	वापस clk_rcg_esc_set_rate(hw, rate, parent_rate);
पूर्ण

/*
 * This type of घड़ी has a glitch-मुक्त mux that चयनes between the output of
 * the M/N counter and an always on घड़ी source (XO). When clk_set_rate() is
 * called we need to make sure that we करोn't चयन to the M/N counter अगर it
 * isn't घड़ीing because the mux will get stuck and the घड़ी will stop
 * outputting a घड़ी. This can happen अगर the framework isn't aware that this
 * घड़ी is on and so clk_set_rate() करोesn't turn on the new parent. To fix
 * this we चयन the mux in the enable/disable ops and reprogram the M/N
 * counter in the set_rate op. We also make sure to चयन away from the M/N
 * counter in set_rate अगर software thinks the घड़ी is off.
 */
अटल पूर्णांक clk_rcg_lcc_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_rcg *rcg = to_clk_rcg(hw);
	स्थिर काष्ठा freq_tbl *f;
	पूर्णांक ret;
	u32 gfm = BIT(10);

	f = qcom_find_freq(rcg->freq_tbl, rate);
	अगर (!f)
		वापस -EINVAL;

	/* Switch to XO to aव्योम glitches */
	regmap_update_bits(rcg->clkr.regmap, rcg->ns_reg, gfm, 0);
	ret = __clk_rcg_set_rate(rcg, f);
	/* Switch back to M/N अगर it's घड़ीing */
	अगर (__clk_is_enabled(hw->clk))
		regmap_update_bits(rcg->clkr.regmap, rcg->ns_reg, gfm, gfm);

	वापस ret;
पूर्ण

अटल पूर्णांक clk_rcg_lcc_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_rcg *rcg = to_clk_rcg(hw);
	u32 gfm = BIT(10);

	/* Use M/N */
	वापस regmap_update_bits(rcg->clkr.regmap, rcg->ns_reg, gfm, gfm);
पूर्ण

अटल व्योम clk_rcg_lcc_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_rcg *rcg = to_clk_rcg(hw);
	u32 gfm = BIT(10);

	/* Use XO */
	regmap_update_bits(rcg->clkr.regmap, rcg->ns_reg, gfm, 0);
पूर्ण

अटल पूर्णांक __clk_dyn_rcg_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate)
अणु
	काष्ठा clk_dyn_rcg *rcg = to_clk_dyn_rcg(hw);
	स्थिर काष्ठा freq_tbl *f;

	f = qcom_find_freq(rcg->freq_tbl, rate);
	अगर (!f)
		वापस -EINVAL;

	वापस configure_bank(rcg, f);
पूर्ण

अटल पूर्णांक clk_dyn_rcg_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			    अचिन्हित दीर्घ parent_rate)
अणु
	वापस __clk_dyn_rcg_set_rate(hw, rate);
पूर्ण

अटल पूर्णांक clk_dyn_rcg_set_rate_and_parent(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate, u8 index)
अणु
	वापस __clk_dyn_rcg_set_rate(hw, rate);
पूर्ण

स्थिर काष्ठा clk_ops clk_rcg_ops = अणु
	.enable = clk_enable_regmap,
	.disable = clk_disable_regmap,
	.get_parent = clk_rcg_get_parent,
	.set_parent = clk_rcg_set_parent,
	.recalc_rate = clk_rcg_recalc_rate,
	.determine_rate = clk_rcg_determine_rate,
	.set_rate = clk_rcg_set_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_rcg_ops);

स्थिर काष्ठा clk_ops clk_rcg_bypass_ops = अणु
	.enable = clk_enable_regmap,
	.disable = clk_disable_regmap,
	.get_parent = clk_rcg_get_parent,
	.set_parent = clk_rcg_set_parent,
	.recalc_rate = clk_rcg_recalc_rate,
	.determine_rate = clk_rcg_bypass_determine_rate,
	.set_rate = clk_rcg_bypass_set_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_rcg_bypass_ops);

स्थिर काष्ठा clk_ops clk_rcg_bypass2_ops = अणु
	.enable = clk_enable_regmap,
	.disable = clk_disable_regmap,
	.get_parent = clk_rcg_get_parent,
	.set_parent = clk_rcg_set_parent,
	.recalc_rate = clk_rcg_recalc_rate,
	.determine_rate = clk_rcg_bypass2_determine_rate,
	.set_rate = clk_rcg_bypass2_set_rate,
	.set_rate_and_parent = clk_rcg_bypass2_set_rate_and_parent,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_rcg_bypass2_ops);

स्थिर काष्ठा clk_ops clk_rcg_pixel_ops = अणु
	.enable = clk_enable_regmap,
	.disable = clk_disable_regmap,
	.get_parent = clk_rcg_get_parent,
	.set_parent = clk_rcg_set_parent,
	.recalc_rate = clk_rcg_recalc_rate,
	.determine_rate = clk_rcg_pixel_determine_rate,
	.set_rate = clk_rcg_pixel_set_rate,
	.set_rate_and_parent = clk_rcg_pixel_set_rate_and_parent,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_rcg_pixel_ops);

स्थिर काष्ठा clk_ops clk_rcg_esc_ops = अणु
	.enable = clk_enable_regmap,
	.disable = clk_disable_regmap,
	.get_parent = clk_rcg_get_parent,
	.set_parent = clk_rcg_set_parent,
	.recalc_rate = clk_rcg_recalc_rate,
	.determine_rate = clk_rcg_esc_determine_rate,
	.set_rate = clk_rcg_esc_set_rate,
	.set_rate_and_parent = clk_rcg_esc_set_rate_and_parent,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_rcg_esc_ops);

स्थिर काष्ठा clk_ops clk_rcg_lcc_ops = अणु
	.enable = clk_rcg_lcc_enable,
	.disable = clk_rcg_lcc_disable,
	.get_parent = clk_rcg_get_parent,
	.set_parent = clk_rcg_set_parent,
	.recalc_rate = clk_rcg_recalc_rate,
	.determine_rate = clk_rcg_determine_rate,
	.set_rate = clk_rcg_lcc_set_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_rcg_lcc_ops);

स्थिर काष्ठा clk_ops clk_dyn_rcg_ops = अणु
	.enable = clk_enable_regmap,
	.is_enabled = clk_is_enabled_regmap,
	.disable = clk_disable_regmap,
	.get_parent = clk_dyn_rcg_get_parent,
	.set_parent = clk_dyn_rcg_set_parent,
	.recalc_rate = clk_dyn_rcg_recalc_rate,
	.determine_rate = clk_dyn_rcg_determine_rate,
	.set_rate = clk_dyn_rcg_set_rate,
	.set_rate_and_parent = clk_dyn_rcg_set_rate_and_parent,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_dyn_rcg_ops);
