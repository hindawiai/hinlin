<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Zynq UltraScale+ MPSoC PLL driver
 *
 *  Copyright (C) 2016-2018 Xilinx
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/slab.h>
#समावेश "clk-zynqmp.h"

/**
 * काष्ठा zynqmp_pll - PLL घड़ी
 * @hw:		Handle between common and hardware-specअगरic पूर्णांकerfaces
 * @clk_id:	PLL घड़ी ID
 * @set_pll_mode:	Whether an IOCTL_SET_PLL_FRAC_MODE request be sent to ATF
 */
काष्ठा zynqmp_pll अणु
	काष्ठा clk_hw hw;
	u32 clk_id;
	bool set_pll_mode;
पूर्ण;

#घोषणा to_zynqmp_pll(_hw)	container_of(_hw, काष्ठा zynqmp_pll, hw)

#घोषणा PLL_FBDIV_MIN	25
#घोषणा PLL_FBDIV_MAX	125

#घोषणा PS_PLL_VCO_MIN 1500000000
#घोषणा PS_PLL_VCO_MAX 3000000000UL

क्रमागत pll_mode अणु
	PLL_MODE_INT,
	PLL_MODE_FRAC,
पूर्ण;

#घोषणा FRAC_OFFSET 0x8
#घोषणा PLLFCFG_FRAC_EN	BIT(31)
#घोषणा FRAC_DIV  BIT(16)  /* 2^16 */

/**
 * zynqmp_pll_get_mode() - Get mode of PLL
 * @hw:		Handle between common and hardware-specअगरic पूर्णांकerfaces
 *
 * Return: Mode of PLL
 */
अटल अंतरभूत क्रमागत pll_mode zynqmp_pll_get_mode(काष्ठा clk_hw *hw)
अणु
	काष्ठा zynqmp_pll *clk = to_zynqmp_pll(hw);
	u32 clk_id = clk->clk_id;
	स्थिर अक्षर *clk_name = clk_hw_get_name(hw);
	u32 ret_payload[PAYLOAD_ARG_CNT];
	पूर्णांक ret;

	ret = zynqmp_pm_get_pll_frac_mode(clk_id, ret_payload);
	अगर (ret)
		pr_warn_once("%s() PLL get frac mode failed for %s, ret = %d\n",
			     __func__, clk_name, ret);

	वापस ret_payload[1];
पूर्ण

/**
 * zynqmp_pll_set_mode() - Set the PLL mode
 * @hw:		Handle between common and hardware-specअगरic पूर्णांकerfaces
 * @on:		Flag to determine the mode
 */
अटल अंतरभूत व्योम zynqmp_pll_set_mode(काष्ठा clk_hw *hw, bool on)
अणु
	काष्ठा zynqmp_pll *clk = to_zynqmp_pll(hw);
	u32 clk_id = clk->clk_id;
	स्थिर अक्षर *clk_name = clk_hw_get_name(hw);
	पूर्णांक ret;
	u32 mode;

	अगर (on)
		mode = PLL_MODE_FRAC;
	अन्यथा
		mode = PLL_MODE_INT;

	ret = zynqmp_pm_set_pll_frac_mode(clk_id, mode);
	अगर (ret)
		pr_warn_once("%s() PLL set frac mode failed for %s, ret = %d\n",
			     __func__, clk_name, ret);
	अन्यथा
		clk->set_pll_mode = true;
पूर्ण

/**
 * zynqmp_pll_round_rate() - Round a घड़ी frequency
 * @hw:		Handle between common and hardware-specअगरic पूर्णांकerfaces
 * @rate:	Desired घड़ी frequency
 * @prate:	Clock frequency of parent घड़ी
 *
 * Return: Frequency बंदst to @rate the hardware can generate
 */
अटल दीर्घ zynqmp_pll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				  अचिन्हित दीर्घ *prate)
अणु
	u32 fbभाग;
	दीर्घ rate_भाग, f;

	/* Enable the fractional mode अगर needed */
	rate_भाग = (rate * FRAC_DIV) / *prate;
	f = rate_भाग % FRAC_DIV;
	अगर (f) अणु
		अगर (rate > PS_PLL_VCO_MAX) अणु
			fbभाग = rate / PS_PLL_VCO_MAX;
			rate = rate / (fbभाग + 1);
		पूर्ण
		अगर (rate < PS_PLL_VCO_MIN) अणु
			fbभाग = DIV_ROUND_UP(PS_PLL_VCO_MIN, rate);
			rate = rate * fbभाग;
		पूर्ण
		वापस rate;
	पूर्ण

	fbभाग = DIV_ROUND_CLOSEST(rate, *prate);
	fbभाग = clamp_t(u32, fbभाग, PLL_FBDIV_MIN, PLL_FBDIV_MAX);
	वापस *prate * fbभाग;
पूर्ण

/**
 * zynqmp_pll_recalc_rate() - Recalculate घड़ी frequency
 * @hw:			Handle between common and hardware-specअगरic पूर्णांकerfaces
 * @parent_rate:	Clock frequency of parent घड़ी
 *
 * Return: Current घड़ी frequency
 */
अटल अचिन्हित दीर्घ zynqmp_pll_recalc_rate(काष्ठा clk_hw *hw,
					    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा zynqmp_pll *clk = to_zynqmp_pll(hw);
	u32 clk_id = clk->clk_id;
	स्थिर अक्षर *clk_name = clk_hw_get_name(hw);
	u32 fbभाग, data;
	अचिन्हित दीर्घ rate, frac;
	u32 ret_payload[PAYLOAD_ARG_CNT];
	पूर्णांक ret;

	ret = zynqmp_pm_घड़ी_getभागider(clk_id, &fbभाग);
	अगर (ret)
		pr_warn_once("%s() get divider failed for %s, ret = %d\n",
			     __func__, clk_name, ret);

	rate =  parent_rate * fbभाग;
	अगर (zynqmp_pll_get_mode(hw) == PLL_MODE_FRAC) अणु
		zynqmp_pm_get_pll_frac_data(clk_id, ret_payload);
		data = ret_payload[1];
		frac = (parent_rate * data) / FRAC_DIV;
		rate = rate + frac;
	पूर्ण

	वापस rate;
पूर्ण

/**
 * zynqmp_pll_set_rate() - Set rate of PLL
 * @hw:			Handle between common and hardware-specअगरic पूर्णांकerfaces
 * @rate:		Frequency of घड़ी to be set
 * @parent_rate:	Clock frequency of parent घड़ी
 *
 * Set PLL भागider to set desired rate.
 *
 * Returns:            rate which is set on success अन्यथा error code
 */
अटल पूर्णांक zynqmp_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा zynqmp_pll *clk = to_zynqmp_pll(hw);
	u32 clk_id = clk->clk_id;
	स्थिर अक्षर *clk_name = clk_hw_get_name(hw);
	u32 fbभाग;
	दीर्घ rate_भाग, frac, m, f;
	पूर्णांक ret;

	rate_भाग = (rate * FRAC_DIV) / parent_rate;
	f = rate_भाग % FRAC_DIV;
	zynqmp_pll_set_mode(hw, !!f);

	अगर (f) अणु
		m = rate_भाग / FRAC_DIV;
		m = clamp_t(u32, m, (PLL_FBDIV_MIN), (PLL_FBDIV_MAX));
		rate = parent_rate * m;
		frac = (parent_rate * f) / FRAC_DIV;

		ret = zynqmp_pm_घड़ी_setभागider(clk_id, m);
		अगर (ret == -EUSERS)
			WARN(1, "More than allowed devices are using the %s, which is forbidden\n",
			     clk_name);
		अन्यथा अगर (ret)
			pr_warn_once("%s() set divider failed for %s, ret = %d\n",
				     __func__, clk_name, ret);
		zynqmp_pm_set_pll_frac_data(clk_id, f);

		वापस rate + frac;
	पूर्ण

	fbभाग = DIV_ROUND_CLOSEST(rate, parent_rate);
	fbभाग = clamp_t(u32, fbभाग, PLL_FBDIV_MIN, PLL_FBDIV_MAX);
	ret = zynqmp_pm_घड़ी_setभागider(clk_id, fbभाग);
	अगर (ret)
		pr_warn_once("%s() set divider failed for %s, ret = %d\n",
			     __func__, clk_name, ret);

	वापस parent_rate * fbभाग;
पूर्ण

/**
 * zynqmp_pll_is_enabled() - Check अगर a घड़ी is enabled
 * @hw:		Handle between common and hardware-specअगरic पूर्णांकerfaces
 *
 * Return: 1 अगर the घड़ी is enabled, 0 otherwise
 */
अटल पूर्णांक zynqmp_pll_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा zynqmp_pll *clk = to_zynqmp_pll(hw);
	स्थिर अक्षर *clk_name = clk_hw_get_name(hw);
	u32 clk_id = clk->clk_id;
	अचिन्हित पूर्णांक state;
	पूर्णांक ret;

	ret = zynqmp_pm_घड़ी_माला_लोtate(clk_id, &state);
	अगर (ret) अणु
		pr_warn_once("%s() clock get state failed for %s, ret = %d\n",
			     __func__, clk_name, ret);
		वापस -EIO;
	पूर्ण

	वापस state ? 1 : 0;
पूर्ण

/**
 * zynqmp_pll_enable() - Enable घड़ी
 * @hw:		Handle between common and hardware-specअगरic पूर्णांकerfaces
 *
 * Return: 0 on success अन्यथा error code
 */
अटल पूर्णांक zynqmp_pll_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा zynqmp_pll *clk = to_zynqmp_pll(hw);
	स्थिर अक्षर *clk_name = clk_hw_get_name(hw);
	u32 clk_id = clk->clk_id;
	पूर्णांक ret;

	/*
	 * Don't skip enabling घड़ी अगर there is an IOCTL_SET_PLL_FRAC_MODE request
	 * that has been sent to ATF.
	 */
	अगर (zynqmp_pll_is_enabled(hw) && (!clk->set_pll_mode))
		वापस 0;

	clk->set_pll_mode = false;

	ret = zynqmp_pm_घड़ी_enable(clk_id);
	अगर (ret)
		pr_warn_once("%s() clock enable failed for %s, ret = %d\n",
			     __func__, clk_name, ret);

	वापस ret;
पूर्ण

/**
 * zynqmp_pll_disable() - Disable घड़ी
 * @hw:		Handle between common and hardware-specअगरic पूर्णांकerfaces
 */
अटल व्योम zynqmp_pll_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा zynqmp_pll *clk = to_zynqmp_pll(hw);
	स्थिर अक्षर *clk_name = clk_hw_get_name(hw);
	u32 clk_id = clk->clk_id;
	पूर्णांक ret;

	अगर (!zynqmp_pll_is_enabled(hw))
		वापस;

	ret = zynqmp_pm_घड़ी_disable(clk_id);
	अगर (ret)
		pr_warn_once("%s() clock disable failed for %s, ret = %d\n",
			     __func__, clk_name, ret);
पूर्ण

अटल स्थिर काष्ठा clk_ops zynqmp_pll_ops = अणु
	.enable = zynqmp_pll_enable,
	.disable = zynqmp_pll_disable,
	.is_enabled = zynqmp_pll_is_enabled,
	.round_rate = zynqmp_pll_round_rate,
	.recalc_rate = zynqmp_pll_recalc_rate,
	.set_rate = zynqmp_pll_set_rate,
पूर्ण;

/**
 * zynqmp_clk_रेजिस्टर_pll() - Register PLL with the घड़ी framework
 * @name:		PLL name
 * @clk_id:		Clock ID
 * @parents:		Name of this घड़ी's parents
 * @num_parents:	Number of parents
 * @nodes:		Clock topology node
 *
 * Return: घड़ी hardware to the रेजिस्टरed घड़ी
 */
काष्ठा clk_hw *zynqmp_clk_रेजिस्टर_pll(स्थिर अक्षर *name, u32 clk_id,
				       स्थिर अक्षर * स्थिर *parents,
				       u8 num_parents,
				       स्थिर काष्ठा घड़ी_प्रकारopology *nodes)
अणु
	काष्ठा zynqmp_pll *pll;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	init.name = name;
	init.ops = &zynqmp_pll_ops;
	init.flags = nodes->flag;
	init.parent_names = parents;
	init.num_parents = 1;

	pll = kzalloc(माप(*pll), GFP_KERNEL);
	अगर (!pll)
		वापस ERR_PTR(-ENOMEM);

	pll->hw.init = &init;
	pll->clk_id = clk_id;

	hw = &pll->hw;
	ret = clk_hw_रेजिस्टर(शून्य, hw);
	अगर (ret) अणु
		kमुक्त(pll);
		वापस ERR_PTR(ret);
	पूर्ण

	clk_hw_set_rate_range(hw, PS_PLL_VCO_MIN, PS_PLL_VCO_MAX);
	अगर (ret < 0)
		pr_err("%s:ERROR clk_set_rate_range failed %d\n", name, ret);

	वापस hw;
पूर्ण
