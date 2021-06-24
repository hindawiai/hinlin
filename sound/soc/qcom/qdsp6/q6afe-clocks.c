<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020, Linaro Limited

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश "q6afe.h"

#घोषणा Q6AFE_CLK(id) अणु					\
		.clk_id	= id,				\
		.afe_clk_id	= Q6AFE_##id,		\
		.name = #id,				\
		.rate = 19200000,			\
	पूर्ण

#घोषणा Q6AFE_VOTE_CLK(id, blkid, n) अणु			\
		.clk_id	= id,				\
		.afe_clk_id = blkid,			\
		.name = n,				\
	पूर्ण

काष्ठा q6afe_clk_init अणु
	पूर्णांक clk_id;
	पूर्णांक afe_clk_id;
	अक्षर *name;
	पूर्णांक rate;
पूर्ण;

काष्ठा q6afe_clk अणु
	काष्ठा device *dev;
	पूर्णांक afe_clk_id;
	पूर्णांक attributes;
	पूर्णांक rate;
	uपूर्णांक32_t handle;
	काष्ठा clk_hw hw;
पूर्ण;

#घोषणा to_q6afe_clk(_hw) container_of(_hw, काष्ठा q6afe_clk, hw)

काष्ठा q6afe_cc अणु
	काष्ठा device *dev;
	काष्ठा q6afe_clk *clks[Q6AFE_MAX_CLK_ID];
पूर्ण;

अटल पूर्णांक clk_q6afe_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा q6afe_clk *clk = to_q6afe_clk(hw);

	वापस q6afe_set_lpass_घड़ी(clk->dev, clk->afe_clk_id, clk->attributes,
				     Q6AFE_LPASS_CLK_ROOT_DEFAULT, clk->rate);
पूर्ण

अटल व्योम clk_q6afe_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा q6afe_clk *clk = to_q6afe_clk(hw);

	q6afe_set_lpass_घड़ी(clk->dev, clk->afe_clk_id, clk->attributes,
			      Q6AFE_LPASS_CLK_ROOT_DEFAULT, 0);
पूर्ण

अटल पूर्णांक clk_q6afe_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			      अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा q6afe_clk *clk = to_q6afe_clk(hw);

	clk->rate = rate;

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ clk_q6afe_recalc_rate(काष्ठा clk_hw *hw,
					   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा q6afe_clk *clk = to_q6afe_clk(hw);

	वापस clk->rate;
पूर्ण

अटल दीर्घ clk_q6afe_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				 अचिन्हित दीर्घ *parent_rate)
अणु
	वापस rate;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_q6afe_ops = अणु
	.prepare	= clk_q6afe_prepare,
	.unprepare	= clk_q6afe_unprepare,
	.set_rate	= clk_q6afe_set_rate,
	.round_rate	= clk_q6afe_round_rate,
	.recalc_rate	= clk_q6afe_recalc_rate,
पूर्ण;

अटल पूर्णांक clk_vote_q6afe_block(काष्ठा clk_hw *hw)
अणु
	काष्ठा q6afe_clk *clk = to_q6afe_clk(hw);

	वापस q6afe_vote_lpass_core_hw(clk->dev, clk->afe_clk_id,
					clk_hw_get_name(&clk->hw), &clk->handle);
पूर्ण

अटल व्योम clk_unvote_q6afe_block(काष्ठा clk_hw *hw)
अणु
	काष्ठा q6afe_clk *clk = to_q6afe_clk(hw);

	q6afe_unvote_lpass_core_hw(clk->dev, clk->afe_clk_id, clk->handle);
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_vote_q6afe_ops = अणु
	.prepare	= clk_vote_q6afe_block,
	.unprepare	= clk_unvote_q6afe_block,
पूर्ण;

अटल स्थिर काष्ठा q6afe_clk_init q6afe_clks[] = अणु
	Q6AFE_CLK(LPASS_CLK_ID_PRI_MI2S_IBIT),
	Q6AFE_CLK(LPASS_CLK_ID_PRI_MI2S_EBIT),
	Q6AFE_CLK(LPASS_CLK_ID_SEC_MI2S_IBIT),
	Q6AFE_CLK(LPASS_CLK_ID_SEC_MI2S_EBIT),
	Q6AFE_CLK(LPASS_CLK_ID_TER_MI2S_IBIT),
	Q6AFE_CLK(LPASS_CLK_ID_TER_MI2S_EBIT),
	Q6AFE_CLK(LPASS_CLK_ID_QUAD_MI2S_IBIT),
	Q6AFE_CLK(LPASS_CLK_ID_QUAD_MI2S_EBIT),
	Q6AFE_CLK(LPASS_CLK_ID_SPEAKER_I2S_IBIT),
	Q6AFE_CLK(LPASS_CLK_ID_SPEAKER_I2S_EBIT),
	Q6AFE_CLK(LPASS_CLK_ID_SPEAKER_I2S_OSR),
	Q6AFE_CLK(LPASS_CLK_ID_QUI_MI2S_IBIT),
	Q6AFE_CLK(LPASS_CLK_ID_QUI_MI2S_EBIT),
	Q6AFE_CLK(LPASS_CLK_ID_SEN_MI2S_IBIT),
	Q6AFE_CLK(LPASS_CLK_ID_SEN_MI2S_EBIT),
	Q6AFE_CLK(LPASS_CLK_ID_INT0_MI2S_IBIT),
	Q6AFE_CLK(LPASS_CLK_ID_INT1_MI2S_IBIT),
	Q6AFE_CLK(LPASS_CLK_ID_INT2_MI2S_IBIT),
	Q6AFE_CLK(LPASS_CLK_ID_INT3_MI2S_IBIT),
	Q6AFE_CLK(LPASS_CLK_ID_INT4_MI2S_IBIT),
	Q6AFE_CLK(LPASS_CLK_ID_INT5_MI2S_IBIT),
	Q6AFE_CLK(LPASS_CLK_ID_INT6_MI2S_IBIT),
	Q6AFE_CLK(LPASS_CLK_ID_QUI_MI2S_OSR),
	Q6AFE_CLK(LPASS_CLK_ID_PRI_PCM_IBIT),
	Q6AFE_CLK(LPASS_CLK_ID_PRI_PCM_EBIT),
	Q6AFE_CLK(LPASS_CLK_ID_SEC_PCM_IBIT),
	Q6AFE_CLK(LPASS_CLK_ID_SEC_PCM_EBIT),
	Q6AFE_CLK(LPASS_CLK_ID_TER_PCM_IBIT),
	Q6AFE_CLK(LPASS_CLK_ID_TER_PCM_EBIT),
	Q6AFE_CLK(LPASS_CLK_ID_QUAD_PCM_IBIT),
	Q6AFE_CLK(LPASS_CLK_ID_QUAD_PCM_EBIT),
	Q6AFE_CLK(LPASS_CLK_ID_QUIN_PCM_IBIT),
	Q6AFE_CLK(LPASS_CLK_ID_QUIN_PCM_EBIT),
	Q6AFE_CLK(LPASS_CLK_ID_QUI_PCM_OSR),
	Q6AFE_CLK(LPASS_CLK_ID_PRI_TDM_IBIT),
	Q6AFE_CLK(LPASS_CLK_ID_PRI_TDM_EBIT),
	Q6AFE_CLK(LPASS_CLK_ID_SEC_TDM_IBIT),
	Q6AFE_CLK(LPASS_CLK_ID_SEC_TDM_EBIT),
	Q6AFE_CLK(LPASS_CLK_ID_TER_TDM_IBIT),
	Q6AFE_CLK(LPASS_CLK_ID_TER_TDM_EBIT),
	Q6AFE_CLK(LPASS_CLK_ID_QUAD_TDM_IBIT),
	Q6AFE_CLK(LPASS_CLK_ID_QUAD_TDM_EBIT),
	Q6AFE_CLK(LPASS_CLK_ID_QUIN_TDM_IBIT),
	Q6AFE_CLK(LPASS_CLK_ID_QUIN_TDM_EBIT),
	Q6AFE_CLK(LPASS_CLK_ID_QUIN_TDM_OSR),
	Q6AFE_CLK(LPASS_CLK_ID_MCLK_1),
	Q6AFE_CLK(LPASS_CLK_ID_MCLK_2),
	Q6AFE_CLK(LPASS_CLK_ID_MCLK_3),
	Q6AFE_CLK(LPASS_CLK_ID_MCLK_4),
	Q6AFE_CLK(LPASS_CLK_ID_INTERNAL_DIGITAL_CODEC_CORE),
	Q6AFE_CLK(LPASS_CLK_ID_INT_MCLK_0),
	Q6AFE_CLK(LPASS_CLK_ID_INT_MCLK_1),
	Q6AFE_CLK(LPASS_CLK_ID_WSA_CORE_MCLK),
	Q6AFE_CLK(LPASS_CLK_ID_WSA_CORE_NPL_MCLK),
	Q6AFE_CLK(LPASS_CLK_ID_VA_CORE_MCLK),
	Q6AFE_CLK(LPASS_CLK_ID_TX_CORE_MCLK),
	Q6AFE_CLK(LPASS_CLK_ID_TX_CORE_NPL_MCLK),
	Q6AFE_CLK(LPASS_CLK_ID_RX_CORE_MCLK),
	Q6AFE_CLK(LPASS_CLK_ID_RX_CORE_NPL_MCLK),
	Q6AFE_CLK(LPASS_CLK_ID_VA_CORE_2X_MCLK),
	Q6AFE_VOTE_CLK(LPASS_HW_AVTIMER_VOTE,
		       Q6AFE_LPASS_CORE_AVTIMER_BLOCK,
		       "LPASS_AVTIMER_MACRO"),
	Q6AFE_VOTE_CLK(LPASS_HW_MACRO_VOTE,
		       Q6AFE_LPASS_CORE_HW_MACRO_BLOCK,
		       "LPASS_HW_MACRO"),
	Q6AFE_VOTE_CLK(LPASS_HW_DCODEC_VOTE,
		       Q6AFE_LPASS_CORE_HW_DCODEC_BLOCK,
		       "LPASS_HW_DCODEC"),
पूर्ण;

अटल काष्ठा clk_hw *q6afe_of_clk_hw_get(काष्ठा of_phandle_args *clkspec,
					  व्योम *data)
अणु
	काष्ठा q6afe_cc *cc = data;
	अचिन्हित पूर्णांक idx = clkspec->args[0];
	अचिन्हित पूर्णांक attr = clkspec->args[1];

	अगर (idx >= Q6AFE_MAX_CLK_ID || attr > LPASS_CLK_ATTRIBUTE_COUPLE_DIVISOR) अणु
		dev_err(cc->dev, "Invalid clk specifier (%d, %d)\n", idx, attr);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (cc->clks[idx]) अणु
		cc->clks[idx]->attributes = attr;
		वापस &cc->clks[idx]->hw;
	पूर्ण

	वापस ERR_PTR(-ENOENT);
पूर्ण

अटल पूर्णांक q6afe_घड़ी_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा q6afe_cc *cc;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक i, ret;

	cc = devm_kzalloc(dev, माप(*cc), GFP_KERNEL);
	अगर (!cc)
		वापस -ENOMEM;

	cc->dev = dev;
	क्रम (i = 0; i < ARRAY_SIZE(q6afe_clks); i++) अणु
		अचिन्हित पूर्णांक id = q6afe_clks[i].clk_id;
		काष्ठा clk_init_data init = अणु
			.name =  q6afe_clks[i].name,
		पूर्ण;
		काष्ठा q6afe_clk *clk;

		clk = devm_kzalloc(dev, माप(*clk), GFP_KERNEL);
		अगर (!clk)
			वापस -ENOMEM;

		clk->dev = dev;
		clk->afe_clk_id = q6afe_clks[i].afe_clk_id;
		clk->rate = q6afe_clks[i].rate;
		clk->hw.init = &init;

		अगर (clk->rate)
			init.ops = &clk_q6afe_ops;
		अन्यथा
			init.ops = &clk_vote_q6afe_ops;

		cc->clks[id] = clk;

		ret = devm_clk_hw_रेजिस्टर(dev, &clk->hw);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = devm_of_clk_add_hw_provider(dev, q6afe_of_clk_hw_get, cc);
	अगर (ret)
		वापस ret;

	dev_set_drvdata(dev, cc);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id q6afe_घड़ी_device_id[] = अणु
	अणु .compatible = "qcom,q6afe-clocks" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, q6afe_घड़ी_device_id);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver q6afe_घड़ी_platक्रमm_driver = अणु
	.driver = अणु
		.name = "q6afe-clock",
		.of_match_table = of_match_ptr(q6afe_घड़ी_device_id),
	पूर्ण,
	.probe = q6afe_घड़ी_dev_probe,
पूर्ण;
module_platक्रमm_driver(q6afe_घड़ी_platक्रमm_driver);

MODULE_DESCRIPTION("Q6 Audio Frontend clock driver");
MODULE_LICENSE("GPL v2");
