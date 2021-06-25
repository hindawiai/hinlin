<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/*
 * Copyright 2018 NXP.
 *
 * This driver supports the SCCG plls found in the imx8m SOCs
 *
 * Documentation क्रम this SCCG pll can be found at:
 *   https://www.nxp.com/करोcs/en/reference-manual/IMX8MDQLQRM.pdf#page=834
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitfield.h>

#समावेश "clk.h"

/* PLL CFGs */
#घोषणा PLL_CFG0		0x0
#घोषणा PLL_CFG1		0x4
#घोषणा PLL_CFG2		0x8

#घोषणा PLL_DIVF1_MASK		GENMASK(18, 13)
#घोषणा PLL_DIVF2_MASK		GENMASK(12, 7)
#घोषणा PLL_DIVR1_MASK		GENMASK(27, 25)
#घोषणा PLL_DIVR2_MASK		GENMASK(24, 19)
#घोषणा PLL_DIVQ_MASK           GENMASK(6, 1)
#घोषणा PLL_REF_MASK		GENMASK(2, 0)

#घोषणा PLL_LOCK_MASK		BIT(31)
#घोषणा PLL_PD_MASK		BIT(7)

/* These are the specअगरication limits क्रम the SSCG PLL */
#घोषणा PLL_REF_MIN_FREQ		25000000UL
#घोषणा PLL_REF_MAX_FREQ		235000000UL

#घोषणा PLL_STAGE1_MIN_FREQ		1600000000UL
#घोषणा PLL_STAGE1_MAX_FREQ		2400000000UL

#घोषणा PLL_STAGE1_REF_MIN_FREQ		25000000UL
#घोषणा PLL_STAGE1_REF_MAX_FREQ		54000000UL

#घोषणा PLL_STAGE2_MIN_FREQ		1200000000UL
#घोषणा PLL_STAGE2_MAX_FREQ		2400000000UL

#घोषणा PLL_STAGE2_REF_MIN_FREQ		54000000UL
#घोषणा PLL_STAGE2_REF_MAX_FREQ		75000000UL

#घोषणा PLL_OUT_MIN_FREQ		20000000UL
#घोषणा PLL_OUT_MAX_FREQ		1200000000UL

#घोषणा PLL_DIVR1_MAX			7
#घोषणा PLL_DIVR2_MAX			63
#घोषणा PLL_DIVF1_MAX			63
#घोषणा PLL_DIVF2_MAX			63
#घोषणा PLL_DIVQ_MAX			63

#घोषणा PLL_BYPASS_NONE			0x0
#घोषणा PLL_BYPASS1			0x2
#घोषणा PLL_BYPASS2			0x1

#घोषणा SSCG_PLL_BYPASS1_MASK           BIT(5)
#घोषणा SSCG_PLL_BYPASS2_MASK           BIT(4)
#घोषणा SSCG_PLL_BYPASS_MASK		GENMASK(5, 4)

#घोषणा PLL_SCCG_LOCK_TIMEOUT		70

काष्ठा clk_sscg_pll_setup अणु
	पूर्णांक भागr1, भागf1;
	पूर्णांक भागr2, भागf2;
	पूर्णांक भागq;
	पूर्णांक bypass;
	uपूर्णांक64_t vco1;
	uपूर्णांक64_t vco2;
	uपूर्णांक64_t fout;
	uपूर्णांक64_t ref;
	uपूर्णांक64_t ref_भाग1;
	uपूर्णांक64_t ref_भाग2;
	uपूर्णांक64_t fout_request;
	पूर्णांक fout_error;
पूर्ण;

काष्ठा clk_sscg_pll अणु
	काष्ठा clk_hw	hw;
	स्थिर काष्ठा clk_ops  ops;
	व्योम __iomem *base;
	काष्ठा clk_sscg_pll_setup setup;
	u8 parent;
	u8 bypass1;
	u8 bypass2;
पूर्ण;

#घोषणा to_clk_sscg_pll(_hw) container_of(_hw, काष्ठा clk_sscg_pll, hw)

अटल पूर्णांक clk_sscg_pll_रुको_lock(काष्ठा clk_sscg_pll *pll)
अणु
	u32 val;

	val = पढ़ोl_relaxed(pll->base + PLL_CFG0);

	/* करोn't रुको क्रम lock अगर all plls are bypassed */
	अगर (!(val & SSCG_PLL_BYPASS2_MASK))
		वापस पढ़ोl_poll_समयout(pll->base, val, val & PLL_LOCK_MASK,
						0, PLL_SCCG_LOCK_TIMEOUT);

	वापस 0;
पूर्ण

अटल पूर्णांक clk_sscg_pll2_check_match(काष्ठा clk_sscg_pll_setup *setup,
					काष्ठा clk_sscg_pll_setup *temp_setup)
अणु
	पूर्णांक new_dअगरf = temp_setup->fout - temp_setup->fout_request;
	पूर्णांक dअगरf = temp_setup->fout_error;

	अगर (असल(dअगरf) > असल(new_dअगरf)) अणु
		temp_setup->fout_error = new_dअगरf;
		स_नकल(setup, temp_setup, माप(काष्ठा clk_sscg_pll_setup));

		अगर (temp_setup->fout_request == temp_setup->fout)
			वापस 0;
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक clk_sscg_भागq_lookup(काष्ठा clk_sscg_pll_setup *setup,
				काष्ठा clk_sscg_pll_setup *temp_setup)
अणु
	पूर्णांक ret = -EINVAL;

	क्रम (temp_setup->भागq = 0; temp_setup->भागq <= PLL_DIVQ_MAX;
	     temp_setup->भागq++) अणु
		temp_setup->vco2 = temp_setup->vco1;
		करो_भाग(temp_setup->vco2, temp_setup->भागr2 + 1);
		temp_setup->vco2 *= 2;
		temp_setup->vco2 *= temp_setup->भागf2 + 1;
		अगर (temp_setup->vco2 >= PLL_STAGE2_MIN_FREQ &&
				temp_setup->vco2 <= PLL_STAGE2_MAX_FREQ) अणु
			temp_setup->fout = temp_setup->vco2;
			करो_भाग(temp_setup->fout, 2 * (temp_setup->भागq + 1));

			ret = clk_sscg_pll2_check_match(setup, temp_setup);
			अगर (!ret) अणु
				temp_setup->bypass = PLL_BYPASS1;
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक clk_sscg_भागf2_lookup(काष्ठा clk_sscg_pll_setup *setup,
					काष्ठा clk_sscg_pll_setup *temp_setup)
अणु
	पूर्णांक ret = -EINVAL;

	क्रम (temp_setup->भागf2 = 0; temp_setup->भागf2 <= PLL_DIVF2_MAX;
	     temp_setup->भागf2++) अणु
		ret = clk_sscg_भागq_lookup(setup, temp_setup);
		अगर (!ret)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक clk_sscg_भागr2_lookup(काष्ठा clk_sscg_pll_setup *setup,
				काष्ठा clk_sscg_pll_setup *temp_setup)
अणु
	पूर्णांक ret = -EINVAL;

	क्रम (temp_setup->भागr2 = 0; temp_setup->भागr2 <= PLL_DIVR2_MAX;
	     temp_setup->भागr2++) अणु
		temp_setup->ref_भाग2 = temp_setup->vco1;
		करो_भाग(temp_setup->ref_भाग2, temp_setup->भागr2 + 1);
		अगर (temp_setup->ref_भाग2 >= PLL_STAGE2_REF_MIN_FREQ &&
		    temp_setup->ref_भाग2 <= PLL_STAGE2_REF_MAX_FREQ) अणु
			ret = clk_sscg_भागf2_lookup(setup, temp_setup);
			अगर (!ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक clk_sscg_pll2_find_setup(काष्ठा clk_sscg_pll_setup *setup,
					काष्ठा clk_sscg_pll_setup *temp_setup,
					uपूर्णांक64_t ref)
अणु
	पूर्णांक ret;

	अगर (ref < PLL_STAGE1_MIN_FREQ || ref > PLL_STAGE1_MAX_FREQ)
		वापस -EINVAL;

	temp_setup->vco1 = ref;

	ret = clk_sscg_भागr2_lookup(setup, temp_setup);
	वापस ret;
पूर्ण

अटल पूर्णांक clk_sscg_भागf1_lookup(काष्ठा clk_sscg_pll_setup *setup,
				काष्ठा clk_sscg_pll_setup *temp_setup)
अणु
	पूर्णांक ret = -EINVAL;

	क्रम (temp_setup->भागf1 = 0; temp_setup->भागf1 <= PLL_DIVF1_MAX;
	     temp_setup->भागf1++) अणु
		uपूर्णांक64_t vco1 = temp_setup->ref;

		करो_भाग(vco1, temp_setup->भागr1 + 1);
		vco1 *= 2;
		vco1 *= temp_setup->भागf1 + 1;

		ret = clk_sscg_pll2_find_setup(setup, temp_setup, vco1);
		अगर (!ret) अणु
			temp_setup->bypass = PLL_BYPASS_NONE;
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक clk_sscg_भागr1_lookup(काष्ठा clk_sscg_pll_setup *setup,
				काष्ठा clk_sscg_pll_setup *temp_setup)
अणु
	पूर्णांक ret = -EINVAL;

	क्रम (temp_setup->भागr1 = 0; temp_setup->भागr1 <= PLL_DIVR1_MAX;
	     temp_setup->भागr1++) अणु
		temp_setup->ref_भाग1 = temp_setup->ref;
		करो_भाग(temp_setup->ref_भाग1, temp_setup->भागr1 + 1);
		अगर (temp_setup->ref_भाग1 >= PLL_STAGE1_REF_MIN_FREQ &&
		    temp_setup->ref_भाग1 <= PLL_STAGE1_REF_MAX_FREQ) अणु
			ret = clk_sscg_भागf1_lookup(setup, temp_setup);
			अगर (!ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक clk_sscg_pll1_find_setup(काष्ठा clk_sscg_pll_setup *setup,
					काष्ठा clk_sscg_pll_setup *temp_setup,
					uपूर्णांक64_t ref)
अणु
	पूर्णांक ret;

	अगर (ref < PLL_REF_MIN_FREQ || ref > PLL_REF_MAX_FREQ)
		वापस -EINVAL;

	temp_setup->ref = ref;

	ret = clk_sscg_भागr1_lookup(setup, temp_setup);

	वापस ret;
पूर्ण

अटल पूर्णांक clk_sscg_pll_find_setup(काष्ठा clk_sscg_pll_setup *setup,
					uपूर्णांक64_t prate,
					uपूर्णांक64_t rate, पूर्णांक try_bypass)
अणु
	काष्ठा clk_sscg_pll_setup temp_setup;
	पूर्णांक ret = -EINVAL;

	स_रखो(&temp_setup, 0, माप(काष्ठा clk_sscg_pll_setup));
	स_रखो(setup, 0, माप(काष्ठा clk_sscg_pll_setup));

	temp_setup.fout_error = PLL_OUT_MAX_FREQ;
	temp_setup.fout_request = rate;

	चयन (try_bypass) अणु
	हाल PLL_BYPASS2:
		अगर (prate == rate) अणु
			setup->bypass = PLL_BYPASS2;
			setup->fout = rate;
			ret = 0;
		पूर्ण
		अवरोध;
	हाल PLL_BYPASS1:
		ret = clk_sscg_pll2_find_setup(setup, &temp_setup, prate);
		अवरोध;
	हाल PLL_BYPASS_NONE:
		ret = clk_sscg_pll1_find_setup(setup, &temp_setup, prate);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक clk_sscg_pll_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_sscg_pll *pll = to_clk_sscg_pll(hw);

	u32 val = पढ़ोl_relaxed(pll->base + PLL_CFG0);

	वापस (val & PLL_PD_MASK) ? 0 : 1;
पूर्ण

अटल पूर्णांक clk_sscg_pll_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_sscg_pll *pll = to_clk_sscg_pll(hw);
	u32 val;

	val = पढ़ोl_relaxed(pll->base + PLL_CFG0);
	val &= ~PLL_PD_MASK;
	ग_लिखोl_relaxed(val, pll->base + PLL_CFG0);

	वापस clk_sscg_pll_रुको_lock(pll);
पूर्ण

अटल व्योम clk_sscg_pll_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_sscg_pll *pll = to_clk_sscg_pll(hw);
	u32 val;

	val = पढ़ोl_relaxed(pll->base + PLL_CFG0);
	val |= PLL_PD_MASK;
	ग_लिखोl_relaxed(val, pll->base + PLL_CFG0);
पूर्ण

अटल अचिन्हित दीर्घ clk_sscg_pll_recalc_rate(काष्ठा clk_hw *hw,
					 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_sscg_pll *pll = to_clk_sscg_pll(hw);
	u32 val, भागr1, भागf1, भागr2, भागf2, भागq;
	u64 temp64;

	val = पढ़ोl_relaxed(pll->base + PLL_CFG2);
	भागr1 = FIELD_GET(PLL_DIVR1_MASK, val);
	भागr2 = FIELD_GET(PLL_DIVR2_MASK, val);
	भागf1 = FIELD_GET(PLL_DIVF1_MASK, val);
	भागf2 = FIELD_GET(PLL_DIVF2_MASK, val);
	भागq = FIELD_GET(PLL_DIVQ_MASK, val);

	temp64 = parent_rate;

	val = पढ़ोl(pll->base + PLL_CFG0);
	अगर (val & SSCG_PLL_BYPASS2_MASK) अणु
		temp64 = parent_rate;
	पूर्ण अन्यथा अगर (val & SSCG_PLL_BYPASS1_MASK) अणु
		temp64 *= भागf2;
		करो_भाग(temp64, (भागr2 + 1) * (भागq + 1));
	पूर्ण अन्यथा अणु
		temp64 *= 2;
		temp64 *= (भागf1 + 1) * (भागf2 + 1);
		करो_भाग(temp64, (भागr1 + 1) * (भागr2 + 1) * (भागq + 1));
	पूर्ण

	वापस temp64;
पूर्ण

अटल पूर्णांक clk_sscg_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_sscg_pll *pll = to_clk_sscg_pll(hw);
	काष्ठा clk_sscg_pll_setup *setup = &pll->setup;
	u32 val;

	/* set bypass here too since the parent might be the same */
	val = पढ़ोl(pll->base + PLL_CFG0);
	val &= ~SSCG_PLL_BYPASS_MASK;
	val |= FIELD_PREP(SSCG_PLL_BYPASS_MASK, setup->bypass);
	ग_लिखोl(val, pll->base + PLL_CFG0);

	val = पढ़ोl_relaxed(pll->base + PLL_CFG2);
	val &= ~(PLL_DIVF1_MASK | PLL_DIVF2_MASK);
	val &= ~(PLL_DIVR1_MASK | PLL_DIVR2_MASK | PLL_DIVQ_MASK);
	val |= FIELD_PREP(PLL_DIVF1_MASK, setup->भागf1);
	val |= FIELD_PREP(PLL_DIVF2_MASK, setup->भागf2);
	val |= FIELD_PREP(PLL_DIVR1_MASK, setup->भागr1);
	val |= FIELD_PREP(PLL_DIVR2_MASK, setup->भागr2);
	val |= FIELD_PREP(PLL_DIVQ_MASK, setup->भागq);
	ग_लिखोl_relaxed(val, pll->base + PLL_CFG2);

	वापस clk_sscg_pll_रुको_lock(pll);
पूर्ण

अटल u8 clk_sscg_pll_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_sscg_pll *pll = to_clk_sscg_pll(hw);
	u32 val;
	u8 ret = pll->parent;

	val = पढ़ोl(pll->base + PLL_CFG0);
	अगर (val & SSCG_PLL_BYPASS2_MASK)
		ret = pll->bypass2;
	अन्यथा अगर (val & SSCG_PLL_BYPASS1_MASK)
		ret = pll->bypass1;
	वापस ret;
पूर्ण

अटल पूर्णांक clk_sscg_pll_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा clk_sscg_pll *pll = to_clk_sscg_pll(hw);
	u32 val;

	val = पढ़ोl(pll->base + PLL_CFG0);
	val &= ~SSCG_PLL_BYPASS_MASK;
	val |= FIELD_PREP(SSCG_PLL_BYPASS_MASK, pll->setup.bypass);
	ग_लिखोl(val, pll->base + PLL_CFG0);

	वापस clk_sscg_pll_रुको_lock(pll);
पूर्ण

अटल पूर्णांक __clk_sscg_pll_determine_rate(काष्ठा clk_hw *hw,
					काष्ठा clk_rate_request *req,
					uपूर्णांक64_t min,
					uपूर्णांक64_t max,
					uपूर्णांक64_t rate,
					पूर्णांक bypass)
अणु
	काष्ठा clk_sscg_pll *pll = to_clk_sscg_pll(hw);
	काष्ठा clk_sscg_pll_setup *setup = &pll->setup;
	काष्ठा clk_hw *parent_hw = शून्य;
	पूर्णांक bypass_parent_index;
	पूर्णांक ret;

	req->max_rate = max;
	req->min_rate = min;

	चयन (bypass) अणु
	हाल PLL_BYPASS2:
		bypass_parent_index = pll->bypass2;
		अवरोध;
	हाल PLL_BYPASS1:
		bypass_parent_index = pll->bypass1;
		अवरोध;
	शेष:
		bypass_parent_index = pll->parent;
		अवरोध;
	पूर्ण

	parent_hw = clk_hw_get_parent_by_index(hw, bypass_parent_index);
	ret = __clk_determine_rate(parent_hw, req);
	अगर (!ret) अणु
		ret = clk_sscg_pll_find_setup(setup, req->rate,
						rate, bypass);
	पूर्ण

	req->best_parent_hw = parent_hw;
	req->best_parent_rate = req->rate;
	req->rate = setup->fout;

	वापस ret;
पूर्ण

अटल पूर्णांक clk_sscg_pll_determine_rate(काष्ठा clk_hw *hw,
				       काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_sscg_pll *pll = to_clk_sscg_pll(hw);
	काष्ठा clk_sscg_pll_setup *setup = &pll->setup;
	uपूर्णांक64_t rate = req->rate;
	uपूर्णांक64_t min = req->min_rate;
	uपूर्णांक64_t max = req->max_rate;
	पूर्णांक ret;

	अगर (rate < PLL_OUT_MIN_FREQ || rate > PLL_OUT_MAX_FREQ)
		वापस -EINVAL;

	ret = __clk_sscg_pll_determine_rate(hw, req, req->rate, req->rate,
						rate, PLL_BYPASS2);
	अगर (!ret)
		वापस ret;

	ret = __clk_sscg_pll_determine_rate(hw, req, PLL_STAGE1_REF_MIN_FREQ,
						PLL_STAGE1_REF_MAX_FREQ, rate,
						PLL_BYPASS1);
	अगर (!ret)
		वापस ret;

	ret = __clk_sscg_pll_determine_rate(hw, req, PLL_REF_MIN_FREQ,
						PLL_REF_MAX_FREQ, rate,
						PLL_BYPASS_NONE);
	अगर (!ret)
		वापस ret;

	अगर (setup->fout >= min && setup->fout <= max)
		ret = 0;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_sscg_pll_ops = अणु
	.prepare	= clk_sscg_pll_prepare,
	.unprepare	= clk_sscg_pll_unprepare,
	.is_prepared	= clk_sscg_pll_is_prepared,
	.recalc_rate	= clk_sscg_pll_recalc_rate,
	.set_rate	= clk_sscg_pll_set_rate,
	.set_parent	= clk_sscg_pll_set_parent,
	.get_parent	= clk_sscg_pll_get_parent,
	.determine_rate	= clk_sscg_pll_determine_rate,
पूर्ण;

काष्ठा clk_hw *imx_clk_hw_sscg_pll(स्थिर अक्षर *name,
				स्थिर अक्षर * स्थिर *parent_names,
				u8 num_parents,
				u8 parent, u8 bypass1, u8 bypass2,
				व्योम __iomem *base,
				अचिन्हित दीर्घ flags)
अणु
	काष्ठा clk_sscg_pll *pll;
	काष्ठा clk_init_data init;
	काष्ठा clk_hw *hw;
	पूर्णांक ret;

	pll = kzalloc(माप(*pll), GFP_KERNEL);
	अगर (!pll)
		वापस ERR_PTR(-ENOMEM);

	pll->parent = parent;
	pll->bypass1 = bypass1;
	pll->bypass2 = bypass2;

	pll->base = base;
	init.name = name;
	init.ops = &clk_sscg_pll_ops;

	init.flags = flags;
	init.parent_names = parent_names;
	init.num_parents = num_parents;

	pll->base = base;
	pll->hw.init = &init;

	hw = &pll->hw;

	ret = clk_hw_रेजिस्टर(शून्य, hw);
	अगर (ret) अणु
		kमुक्त(pll);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण
EXPORT_SYMBOL_GPL(imx_clk_hw_sscg_pll);
