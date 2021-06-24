<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Zynq UltraScale+ MPSoC Divider support
 *
 *  Copyright (C) 2016-2019 Xilinx
 *
 * Adjustable भागider घड़ी implementation
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/slab.h>
#समावेश "clk-zynqmp.h"

/*
 * DOC: basic adjustable भागider घड़ी that cannot gate
 *
 * Traits of this घड़ी:
 * prepare - clk_prepare only ensures that parents are prepared
 * enable - clk_enable only ensures that parents are enabled
 * rate - rate is adjustable.  clk->rate = उच्चमानing(parent->rate / भागisor)
 * parent - fixed parent.  No clk_set_parent support
 */

#घोषणा to_zynqmp_clk_भागider(_hw)		\
	container_of(_hw, काष्ठा zynqmp_clk_भागider, hw)

#घोषणा CLK_FRAC		BIT(13) /* has a fractional parent */
#घोषणा CUSTOM_FLAG_CLK_FRAC	BIT(0) /* has a fractional parent in custom type flag */

/**
 * काष्ठा zynqmp_clk_भागider - adjustable भागider घड़ी
 * @hw:		handle between common and hardware-specअगरic पूर्णांकerfaces
 * @flags:	Hardware specअगरic flags
 * @is_frac:	The भागider is a fractional भागider
 * @clk_id:	Id of घड़ी
 * @भाग_प्रकारype:	भागisor type (TYPE_DIV1 or TYPE_DIV2)
 * @max_भाग:	maximum supported भागisor (fetched from firmware)
 */
काष्ठा zynqmp_clk_भागider अणु
	काष्ठा clk_hw hw;
	u8 flags;
	bool is_frac;
	u32 clk_id;
	u32 भाग_प्रकारype;
	u16 max_भाग;
पूर्ण;

अटल अंतरभूत पूर्णांक zynqmp_भागider_get_val(अचिन्हित दीर्घ parent_rate,
					 अचिन्हित दीर्घ rate, u16 flags)
अणु
	पूर्णांक up, करोwn;
	अचिन्हित दीर्घ up_rate, करोwn_rate;

	अगर (flags & CLK_DIVIDER_POWER_OF_TWO) अणु
		up = DIV_ROUND_UP_ULL((u64)parent_rate, rate);
		करोwn = DIV_ROUND_DOWN_ULL((u64)parent_rate, rate);

		up = __roundup_घात_of_two(up);
		करोwn = __roundकरोwn_घात_of_two(करोwn);

		up_rate = DIV_ROUND_UP_ULL((u64)parent_rate, up);
		करोwn_rate = DIV_ROUND_UP_ULL((u64)parent_rate, करोwn);

		वापस (rate - up_rate) <= (करोwn_rate - rate) ? up : करोwn;

	पूर्ण अन्यथा अणु
		वापस DIV_ROUND_CLOSEST(parent_rate, rate);
	पूर्ण
पूर्ण

/**
 * zynqmp_clk_भागider_recalc_rate() - Recalc rate of भागider घड़ी
 * @hw:			handle between common and hardware-specअगरic पूर्णांकerfaces
 * @parent_rate:	rate of parent घड़ी
 *
 * Return: 0 on success अन्यथा error+reason
 */
अटल अचिन्हित दीर्घ zynqmp_clk_भागider_recalc_rate(काष्ठा clk_hw *hw,
						    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा zynqmp_clk_भागider *भागider = to_zynqmp_clk_भागider(hw);
	स्थिर अक्षर *clk_name = clk_hw_get_name(hw);
	u32 clk_id = भागider->clk_id;
	u32 भाग_प्रकारype = भागider->भाग_प्रकारype;
	u32 भाग, value;
	पूर्णांक ret;

	ret = zynqmp_pm_घड़ी_getभागider(clk_id, &भाग);

	अगर (ret)
		pr_warn_once("%s() get divider failed for %s, ret = %d\n",
			     __func__, clk_name, ret);

	अगर (भाग_प्रकारype == TYPE_DIV1)
		value = भाग & 0xFFFF;
	अन्यथा
		value = भाग >> 16;

	अगर (भागider->flags & CLK_DIVIDER_POWER_OF_TWO)
		value = 1 << value;

	अगर (!value) अणु
		WARN(!(भागider->flags & CLK_DIVIDER_ALLOW_ZERO),
		     "%s: Zero divisor and CLK_DIVIDER_ALLOW_ZERO not set\n",
		     clk_name);
		वापस parent_rate;
	पूर्ण

	वापस DIV_ROUND_UP_ULL(parent_rate, value);
पूर्ण

अटल व्योम zynqmp_get_भागider2_val(काष्ठा clk_hw *hw,
				    अचिन्हित दीर्घ rate,
				    काष्ठा zynqmp_clk_भागider *भागider,
				    पूर्णांक *bestभाग)
अणु
	पूर्णांक भाग1;
	पूर्णांक भाग2;
	दीर्घ error = दीर्घ_उच्च;
	अचिन्हित दीर्घ भाग1_prate;
	काष्ठा clk_hw *भाग1_parent_hw;
	काष्ठा clk_hw *भाग2_parent_hw = clk_hw_get_parent(hw);
	काष्ठा zynqmp_clk_भागider *pभागider =
				to_zynqmp_clk_भागider(भाग2_parent_hw);

	अगर (!pभागider)
		वापस;

	भाग1_parent_hw = clk_hw_get_parent(भाग2_parent_hw);
	अगर (!भाग1_parent_hw)
		वापस;

	भाग1_prate = clk_hw_get_rate(भाग1_parent_hw);
	*bestभाग = 1;
	क्रम (भाग1 = 1; भाग1 <= pभागider->max_भाग;) अणु
		क्रम (भाग2 = 1; भाग2 <= भागider->max_भाग;) अणु
			दीर्घ new_error = ((भाग1_prate / भाग1) / भाग2) - rate;

			अगर (असल(new_error) < असल(error)) अणु
				*bestभाग = भाग2;
				error = new_error;
			पूर्ण
			अगर (भागider->flags & CLK_DIVIDER_POWER_OF_TWO)
				भाग2 = भाग2 << 1;
			अन्यथा
				भाग2++;
		पूर्ण
		अगर (pभागider->flags & CLK_DIVIDER_POWER_OF_TWO)
			भाग1 = भाग1 << 1;
		अन्यथा
			भाग1++;
	पूर्ण
पूर्ण

/**
 * zynqmp_clk_भागider_round_rate() - Round rate of भागider घड़ी
 * @hw:			handle between common and hardware-specअगरic पूर्णांकerfaces
 * @rate:		rate of घड़ी to be set
 * @prate:		rate of parent घड़ी
 *
 * Return: 0 on success अन्यथा error+reason
 */
अटल दीर्घ zynqmp_clk_भागider_round_rate(काष्ठा clk_hw *hw,
					  अचिन्हित दीर्घ rate,
					  अचिन्हित दीर्घ *prate)
अणु
	काष्ठा zynqmp_clk_भागider *भागider = to_zynqmp_clk_भागider(hw);
	स्थिर अक्षर *clk_name = clk_hw_get_name(hw);
	u32 clk_id = भागider->clk_id;
	u32 भाग_प्रकारype = भागider->भाग_प्रकारype;
	u32 bestभाग;
	पूर्णांक ret;

	/* अगर पढ़ो only, just वापस current value */
	अगर (भागider->flags & CLK_DIVIDER_READ_ONLY) अणु
		ret = zynqmp_pm_घड़ी_getभागider(clk_id, &bestभाग);

		अगर (ret)
			pr_warn_once("%s() get divider failed for %s, ret = %d\n",
				     __func__, clk_name, ret);
		अगर (भाग_प्रकारype == TYPE_DIV1)
			bestभाग = bestभाग & 0xFFFF;
		अन्यथा
			bestभाग  = bestभाग >> 16;

		अगर (भागider->flags & CLK_DIVIDER_POWER_OF_TWO)
			bestभाग = 1 << bestभाग;

		वापस DIV_ROUND_UP_ULL((u64)*prate, bestभाग);
	पूर्ण

	bestभाग = zynqmp_भागider_get_val(*prate, rate, भागider->flags);

	/*
	 * In हाल of two भागisors, compute best भागider values and वापस
	 * भागider2 value based on compute value. भाग1 will  be स्वतःmatically
	 * set to optimum based on required total भागider value.
	 */
	अगर (भाग_प्रकारype == TYPE_DIV2 &&
	    (clk_hw_get_flags(hw) & CLK_SET_RATE_PARENT)) अणु
		zynqmp_get_भागider2_val(hw, rate, भागider, &bestभाग);
	पूर्ण

	अगर ((clk_hw_get_flags(hw) & CLK_SET_RATE_PARENT) && भागider->is_frac)
		bestभाग = rate % *prate ? 1 : bestभाग;

	bestभाग = min_t(u32, bestभाग, भागider->max_भाग);
	*prate = rate * bestभाग;

	वापस rate;
पूर्ण

/**
 * zynqmp_clk_भागider_set_rate() - Set rate of भागider घड़ी
 * @hw:			handle between common and hardware-specअगरic पूर्णांकerfaces
 * @rate:		rate of घड़ी to be set
 * @parent_rate:	rate of parent घड़ी
 *
 * Return: 0 on success अन्यथा error+reason
 */
अटल पूर्णांक zynqmp_clk_भागider_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा zynqmp_clk_भागider *भागider = to_zynqmp_clk_भागider(hw);
	स्थिर अक्षर *clk_name = clk_hw_get_name(hw);
	u32 clk_id = भागider->clk_id;
	u32 भाग_प्रकारype = भागider->भाग_प्रकारype;
	u32 value, भाग;
	पूर्णांक ret;

	value = zynqmp_भागider_get_val(parent_rate, rate, भागider->flags);
	अगर (भाग_प्रकारype == TYPE_DIV1) अणु
		भाग = value & 0xFFFF;
		भाग |= 0xffff << 16;
	पूर्ण अन्यथा अणु
		भाग = 0xffff;
		भाग |= value << 16;
	पूर्ण

	अगर (भागider->flags & CLK_DIVIDER_POWER_OF_TWO)
		भाग = __ffs(भाग);

	ret = zynqmp_pm_घड़ी_setभागider(clk_id, भाग);

	अगर (ret)
		pr_warn_once("%s() set divider failed for %s, ret = %d\n",
			     __func__, clk_name, ret);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा clk_ops zynqmp_clk_भागider_ops = अणु
	.recalc_rate = zynqmp_clk_भागider_recalc_rate,
	.round_rate = zynqmp_clk_भागider_round_rate,
	.set_rate = zynqmp_clk_भागider_set_rate,
पूर्ण;

/**
 * zynqmp_clk_get_max_भागisor() - Get maximum supported भागisor from firmware.
 * @clk_id:		Id of घड़ी
 * @type:		Divider type
 *
 * Return: Maximum भागisor of a घड़ी अगर query data is successful
 *	   U16_MAX in हाल of query data is not success
 */
अटल u32 zynqmp_clk_get_max_भागisor(u32 clk_id, u32 type)
अणु
	काष्ठा zynqmp_pm_query_data qdata = अणु0पूर्ण;
	u32 ret_payload[PAYLOAD_ARG_CNT];
	पूर्णांक ret;

	qdata.qid = PM_QID_CLOCK_GET_MAX_DIVISOR;
	qdata.arg1 = clk_id;
	qdata.arg2 = type;
	ret = zynqmp_pm_query_data(qdata, ret_payload);
	/*
	 * To मुख्यtain backward compatibility वापस maximum possible value
	 * (0xFFFF) अगर query क्रम max भागisor is not successful.
	 */
	अगर (ret)
		वापस U16_MAX;

	वापस ret_payload[1];
पूर्ण

/**
 * zynqmp_clk_रेजिस्टर_भागider() - Register a भागider घड़ी
 * @name:		Name of this घड़ी
 * @clk_id:		Id of घड़ी
 * @parents:		Name of this घड़ी's parents
 * @num_parents:	Number of parents
 * @nodes:		Clock topology node
 *
 * Return: घड़ी hardware to रेजिस्टरed घड़ी भागider
 */
काष्ठा clk_hw *zynqmp_clk_रेजिस्टर_भागider(स्थिर अक्षर *name,
					   u32 clk_id,
					   स्थिर अक्षर * स्थिर *parents,
					   u8 num_parents,
					   स्थिर काष्ठा घड़ी_प्रकारopology *nodes)
अणु
	काष्ठा zynqmp_clk_भागider *भाग;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	/* allocate the भागider */
	भाग = kzalloc(माप(*भाग), GFP_KERNEL);
	अगर (!भाग)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &zynqmp_clk_भागider_ops;
	/* CLK_FRAC is not defined in the common clk framework */
	init.flags = nodes->flag & ~CLK_FRAC;
	init.parent_names = parents;
	init.num_parents = 1;

	/* काष्ठा clk_भागider assignments */
	भाग->is_frac = !!((nodes->flag & CLK_FRAC) |
			  (nodes->custom_type_flag & CUSTOM_FLAG_CLK_FRAC));
	भाग->flags = nodes->type_flag;
	भाग->hw.init = &init;
	भाग->clk_id = clk_id;
	भाग->भाग_प्रकारype = nodes->type;

	/*
	 * To achieve best possible rate, maximum limit of भागider is required
	 * जबतक computation.
	 */
	भाग->max_भाग = zynqmp_clk_get_max_भागisor(clk_id, nodes->type);

	hw = &भाग->hw;
	ret = clk_hw_रेजिस्टर(शून्य, hw);
	अगर (ret) अणु
		kमुक्त(भाग);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण
