<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * LPASS Audio CC and Always ON CC Glitch Free Mux घड़ी driver
 *
 * Copyright (c) 2020 Linaro Ltd.
 * Author: Srinivas Kandagatla <srinivas.kandagatla@linaro.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/pm_घड़ी.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_device.h>
#समावेश <dt-bindings/घड़ी/qcom,sm8250-lpass-audiocc.h>
#समावेश <dt-bindings/घड़ी/qcom,sm8250-lpass-aoncc.h>

काष्ठा lpass_gfm अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
पूर्ण;

काष्ठा clk_gfm अणु
	अचिन्हित पूर्णांक mux_reg;
	अचिन्हित पूर्णांक mux_mask;
	काष्ठा clk_hw	hw;
	काष्ठा lpass_gfm *priv;
	व्योम __iomem *gfm_mux;
पूर्ण;

#घोषणा to_clk_gfm(_hw) container_of(_hw, काष्ठा clk_gfm, hw)

अटल u8 clk_gfm_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_gfm *clk = to_clk_gfm(hw);

	वापस पढ़ोl(clk->gfm_mux) & clk->mux_mask;
पूर्ण

अटल पूर्णांक clk_gfm_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा clk_gfm *clk = to_clk_gfm(hw);
	अचिन्हित पूर्णांक val;

	val = पढ़ोl(clk->gfm_mux);

	अगर (index)
		val |= clk->mux_mask;
	अन्यथा
		val &= ~clk->mux_mask;


	ग_लिखोl(val, clk->gfm_mux);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_gfm_ops = अणु
	.get_parent = clk_gfm_get_parent,
	.set_parent = clk_gfm_set_parent,
	.determine_rate = __clk_mux_determine_rate,
पूर्ण;

अटल काष्ठा clk_gfm lpass_gfm_va_mclk = अणु
	.mux_reg = 0x20000,
	.mux_mask = BIT(0),
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "VA_MCLK",
		.ops = &clk_gfm_ops,
		.flags = CLK_SET_RATE_PARENT | CLK_OPS_PARENT_ENABLE,
		.num_parents = 2,
		.parent_data = (स्थिर काष्ठा clk_parent_data[])अणु
			अणु
				.index = 0,
				.fw_name = "LPASS_CLK_ID_TX_CORE_MCLK",
			पूर्ण, अणु
				.index = 1,
				.fw_name = "LPASS_CLK_ID_VA_CORE_MCLK",
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_gfm lpass_gfm_tx_npl = अणु
	.mux_reg = 0x20000,
	.mux_mask = BIT(0),
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "TX_NPL",
		.ops = &clk_gfm_ops,
		.flags = CLK_SET_RATE_PARENT | CLK_OPS_PARENT_ENABLE,
		.parent_data = (स्थिर काष्ठा clk_parent_data[])अणु
			अणु
				.index = 0,
				.fw_name = "LPASS_CLK_ID_TX_CORE_NPL_MCLK",
			पूर्ण, अणु
				.index = 1,
				.fw_name = "LPASS_CLK_ID_VA_CORE_2X_MCLK",
			पूर्ण,
		पूर्ण,
		.num_parents = 2,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_gfm lpass_gfm_wsa_mclk = अणु
	.mux_reg = 0x220d8,
	.mux_mask = BIT(0),
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "WSA_MCLK",
		.ops = &clk_gfm_ops,
		.flags = CLK_SET_RATE_PARENT | CLK_OPS_PARENT_ENABLE,
		.parent_data = (स्थिर काष्ठा clk_parent_data[])अणु
			अणु
				.index = 0,
				.fw_name = "LPASS_CLK_ID_TX_CORE_MCLK",
			पूर्ण, अणु
				.index = 1,
				.fw_name = "LPASS_CLK_ID_WSA_CORE_MCLK",
			पूर्ण,
		पूर्ण,
		.num_parents = 2,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_gfm lpass_gfm_wsa_npl = अणु
	.mux_reg = 0x220d8,
	.mux_mask = BIT(0),
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "WSA_NPL",
		.ops = &clk_gfm_ops,
		.flags = CLK_SET_RATE_PARENT | CLK_OPS_PARENT_ENABLE,
		.parent_data = (स्थिर काष्ठा clk_parent_data[])अणु
			अणु
				.index = 0,
				.fw_name = "LPASS_CLK_ID_TX_CORE_NPL_MCLK",
			पूर्ण, अणु
				.index = 1,
				.fw_name = "LPASS_CLK_ID_WSA_CORE_NPL_MCLK",
			पूर्ण,
		पूर्ण,
		.num_parents = 2,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_gfm lpass_gfm_rx_mclk_mclk2 = अणु
	.mux_reg = 0x240d8,
	.mux_mask = BIT(0),
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "RX_MCLK_MCLK2",
		.ops = &clk_gfm_ops,
		.flags = CLK_SET_RATE_PARENT | CLK_OPS_PARENT_ENABLE,
		.parent_data = (स्थिर काष्ठा clk_parent_data[])अणु
			अणु
				.index = 0,
				.fw_name = "LPASS_CLK_ID_TX_CORE_MCLK",
			पूर्ण, अणु
				.index = 1,
				.fw_name = "LPASS_CLK_ID_RX_CORE_MCLK",
			पूर्ण,
		पूर्ण,
		.num_parents = 2,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_gfm lpass_gfm_rx_npl = अणु
	.mux_reg = 0x240d8,
	.mux_mask = BIT(0),
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "RX_NPL",
		.ops = &clk_gfm_ops,
		.flags = CLK_SET_RATE_PARENT | CLK_OPS_PARENT_ENABLE,
		.parent_data = (स्थिर काष्ठा clk_parent_data[])अणु
			अणु
				.index = 0,
				.fw_name = "LPASS_CLK_ID_TX_CORE_NPL_MCLK",
			पूर्ण, अणु
				.index = 1,
				.fw_name = "LPASS_CLK_ID_RX_CORE_NPL_MCLK",
			पूर्ण,
		पूर्ण,
		.num_parents = 2,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_gfm *aoncc_gfm_clks[] = अणु
	[LPASS_CDC_VA_MCLK]		= &lpass_gfm_va_mclk,
	[LPASS_CDC_TX_NPL]		= &lpass_gfm_tx_npl,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data aoncc_hw_onecell_data = अणु
	.hws = अणु
		[LPASS_CDC_VA_MCLK]	= &lpass_gfm_va_mclk.hw,
		[LPASS_CDC_TX_NPL]	= &lpass_gfm_tx_npl.hw,
	पूर्ण,
	.num = ARRAY_SIZE(aoncc_gfm_clks),
पूर्ण;

अटल काष्ठा clk_gfm *audiocc_gfm_clks[] = अणु
	[LPASS_CDC_WSA_NPL]		= &lpass_gfm_wsa_npl,
	[LPASS_CDC_WSA_MCLK]		= &lpass_gfm_wsa_mclk,
	[LPASS_CDC_RX_NPL]		= &lpass_gfm_rx_npl,
	[LPASS_CDC_RX_MCLK_MCLK2]	= &lpass_gfm_rx_mclk_mclk2,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data audiocc_hw_onecell_data = अणु
	.hws = अणु
		[LPASS_CDC_WSA_NPL]	= &lpass_gfm_wsa_npl.hw,
		[LPASS_CDC_WSA_MCLK]	= &lpass_gfm_wsa_mclk.hw,
		[LPASS_CDC_RX_NPL]	= &lpass_gfm_rx_npl.hw,
		[LPASS_CDC_RX_MCLK_MCLK2] = &lpass_gfm_rx_mclk_mclk2.hw,
	पूर्ण,
	.num = ARRAY_SIZE(audiocc_gfm_clks),
पूर्ण;

काष्ठा lpass_gfm_data अणु
	काष्ठा clk_hw_onecell_data *onecell_data;
	काष्ठा clk_gfm **gfm_clks;
पूर्ण;

अटल काष्ठा lpass_gfm_data audiocc_data = अणु
	.onecell_data = &audiocc_hw_onecell_data,
	.gfm_clks = audiocc_gfm_clks,
पूर्ण;

अटल काष्ठा lpass_gfm_data aoncc_data = अणु
	.onecell_data = &aoncc_hw_onecell_data,
	.gfm_clks = aoncc_gfm_clks,
पूर्ण;

अटल पूर्णांक lpass_gfm_clk_driver_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा lpass_gfm_data *data;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा clk_gfm *gfm;
	काष्ठा lpass_gfm *cc;
	पूर्णांक err, i;

	data = of_device_get_match_data(dev);
	अगर (!data)
		वापस -EINVAL;

	cc = devm_kzalloc(dev, माप(*cc), GFP_KERNEL);
	अगर (!cc)
		वापस -ENOMEM;

	cc->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(cc->base))
		वापस PTR_ERR(cc->base);

	pm_runसमय_enable(dev);
	err = pm_clk_create(dev);
	अगर (err)
		जाओ pm_clk_err;

	err = of_pm_clk_add_clks(dev);
	अगर (err < 0) अणु
		dev_dbg(dev, "Failed to get lpass core voting clocks\n");
		जाओ clk_reg_err;
	पूर्ण

	क्रम (i = 0; i < data->onecell_data->num; i++) अणु
		अगर (!data->gfm_clks[i])
			जारी;

		gfm = data->gfm_clks[i];
		gfm->priv = cc;
		gfm->gfm_mux = cc->base;
		gfm->gfm_mux = gfm->gfm_mux + data->gfm_clks[i]->mux_reg;

		err = devm_clk_hw_रेजिस्टर(dev, &data->gfm_clks[i]->hw);
		अगर (err)
			जाओ clk_reg_err;

	पूर्ण

	err = devm_of_clk_add_hw_provider(dev, of_clk_hw_onecell_get,
					  data->onecell_data);
	अगर (err)
		जाओ clk_reg_err;

	वापस 0;

clk_reg_err:
	pm_clk_destroy(dev);
pm_clk_err:
	pm_runसमय_disable(dev);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा of_device_id lpass_gfm_clk_match_table[] = अणु
	अणु
		.compatible = "qcom,sm8250-lpass-aoncc",
		.data = &aoncc_data,
	पूर्ण,
	अणु
		.compatible = "qcom,sm8250-lpass-audiocc",
		.data = &audiocc_data,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lpass_gfm_clk_match_table);

अटल स्थिर काष्ठा dev_pm_ops lpass_gfm_pm_ops = अणु
	SET_RUNTIME_PM_OPS(pm_clk_suspend, pm_clk_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver lpass_gfm_clk_driver = अणु
	.probe		= lpass_gfm_clk_driver_probe,
	.driver		= अणु
		.name	= "lpass-gfm-clk",
		.of_match_table = lpass_gfm_clk_match_table,
		.pm = &lpass_gfm_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(lpass_gfm_clk_driver);
MODULE_LICENSE("GPL v2");
