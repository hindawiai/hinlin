<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright(c) 2015-17 Intel Corporation

/*
 *  skl-ssp-clk.c - ASoC skylake ssp घड़ी driver
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <sound/पूर्णांकel-nhlt.h>
#समावेश "skl.h"
#समावेश "skl-ssp-clk.h"
#समावेश "skl-topology.h"

#घोषणा to_skl_clk(_hw)	container_of(_hw, काष्ठा skl_clk, hw)

काष्ठा skl_clk_parent अणु
	काष्ठा clk_hw *hw;
	काष्ठा clk_lookup *lookup;
पूर्ण;

काष्ठा skl_clk अणु
	काष्ठा clk_hw hw;
	काष्ठा clk_lookup *lookup;
	अचिन्हित दीर्घ rate;
	काष्ठा skl_clk_pdata *pdata;
	u32 id;
पूर्ण;

काष्ठा skl_clk_data अणु
	काष्ठा skl_clk_parent parent[SKL_MAX_CLK_SRC];
	काष्ठा skl_clk *clk[SKL_MAX_CLK_CNT];
	u8 avail_clk_cnt;
पूर्ण;

अटल पूर्णांक skl_get_clk_type(u32 index)
अणु
	चयन (index) अणु
	हाल 0 ... (SKL_SCLK_OFS - 1):
		वापस SKL_MCLK;

	हाल SKL_SCLK_OFS ... (SKL_SCLKFS_OFS - 1):
		वापस SKL_SCLK;

	हाल SKL_SCLKFS_OFS ... (SKL_MAX_CLK_CNT - 1):
		वापस SKL_SCLK_FS;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक skl_get_vbus_id(u32 index, u8 clk_type)
अणु
	चयन (clk_type) अणु
	हाल SKL_MCLK:
		वापस index;

	हाल SKL_SCLK:
		वापस index - SKL_SCLK_OFS;

	हाल SKL_SCLK_FS:
		वापस index - SKL_SCLKFS_OFS;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम skl_fill_clk_ipc(काष्ठा skl_clk_rate_cfg_table *rcfg, u8 clk_type)
अणु
	काष्ठा nhlt_fmt_cfg *fmt_cfg;
	जोड़ skl_clk_ctrl_ipc *ipc;
	काष्ठा wav_fmt *wfmt;

	अगर (!rcfg)
		वापस;

	ipc = &rcfg->dma_ctl_ipc;
	अगर (clk_type == SKL_SCLK_FS) अणु
		fmt_cfg = (काष्ठा nhlt_fmt_cfg *)rcfg->config;
		wfmt = &fmt_cfg->fmt_ext.fmt;

		/* Remove TLV Header size */
		ipc->sclk_fs.hdr.size = माप(काष्ठा skl_dmactrl_sclkfs_cfg) -
						माप(काष्ठा skl_tlv_hdr);
		ipc->sclk_fs.sampling_frequency = wfmt->samples_per_sec;
		ipc->sclk_fs.bit_depth = wfmt->bits_per_sample;
		ipc->sclk_fs.valid_bit_depth =
			fmt_cfg->fmt_ext.sample.valid_bits_per_sample;
		ipc->sclk_fs.number_of_channels = wfmt->channels;
	पूर्ण अन्यथा अणु
		ipc->mclk.hdr.type = DMA_CLK_CONTROLS;
		/* Remove TLV Header size */
		ipc->mclk.hdr.size = माप(काष्ठा skl_dmactrl_mclk_cfg) -
						माप(काष्ठा skl_tlv_hdr);
	पूर्ण
पूर्ण

/* Sends dma control IPC to turn the घड़ी ON/OFF */
अटल पूर्णांक skl_send_clk_dma_control(काष्ठा skl_dev *skl,
				काष्ठा skl_clk_rate_cfg_table *rcfg,
				u32 vbus_id, u8 clk_type,
				bool enable)
अणु
	काष्ठा nhlt_specअगरic_cfg *sp_cfg;
	u32 i2s_config_size, node_id = 0;
	काष्ठा nhlt_fmt_cfg *fmt_cfg;
	जोड़ skl_clk_ctrl_ipc *ipc;
	व्योम *i2s_config = शून्य;
	u8 *data, size;
	पूर्णांक ret;

	अगर (!rcfg)
		वापस -EIO;

	ipc = &rcfg->dma_ctl_ipc;
	fmt_cfg = (काष्ठा nhlt_fmt_cfg *)rcfg->config;
	sp_cfg = &fmt_cfg->config;

	अगर (clk_type == SKL_SCLK_FS) अणु
		ipc->sclk_fs.hdr.type =
			enable ? DMA_TRANSMITION_START : DMA_TRANSMITION_STOP;
		data = (u8 *)&ipc->sclk_fs;
		size = माप(काष्ठा skl_dmactrl_sclkfs_cfg);
	पूर्ण अन्यथा अणु
		/* 1 to enable mclk, 0 to enable sclk */
		अगर (clk_type == SKL_SCLK)
			ipc->mclk.mclk = 0;
		अन्यथा
			ipc->mclk.mclk = 1;

		ipc->mclk.keep_running = enable;
		ipc->mclk.warm_up_over = enable;
		ipc->mclk.clk_stop_over = !enable;
		data = (u8 *)&ipc->mclk;
		size = माप(काष्ठा skl_dmactrl_mclk_cfg);
	पूर्ण

	i2s_config_size = sp_cfg->size + size;
	i2s_config = kzalloc(i2s_config_size, GFP_KERNEL);
	अगर (!i2s_config)
		वापस -ENOMEM;

	/* copy blob */
	स_नकल(i2s_config, sp_cfg->caps, sp_cfg->size);

	/* copy additional dma controls inक्रमmation */
	स_नकल(i2s_config + sp_cfg->size, data, size);

	node_id = ((SKL_DMA_I2S_LINK_INPUT_CLASS << 8) | (vbus_id << 4));
	ret = skl_dsp_set_dma_control(skl, (u32 *)i2s_config,
					i2s_config_size, node_id);
	kमुक्त(i2s_config);

	वापस ret;
पूर्ण

अटल काष्ठा skl_clk_rate_cfg_table *skl_get_rate_cfg(
		काष्ठा skl_clk_rate_cfg_table *rcfg,
				अचिन्हित दीर्घ rate)
अणु
	पूर्णांक i;

	क्रम (i = 0; (i < SKL_MAX_CLK_RATES) && rcfg[i].rate; i++) अणु
		अगर (rcfg[i].rate == rate)
			वापस &rcfg[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक skl_clk_change_status(काष्ठा skl_clk *clkdev,
				bool enable)
अणु
	काष्ठा skl_clk_rate_cfg_table *rcfg;
	पूर्णांक vbus_id, clk_type;

	clk_type = skl_get_clk_type(clkdev->id);
	अगर (clk_type < 0)
		वापस clk_type;

	vbus_id = skl_get_vbus_id(clkdev->id, clk_type);
	अगर (vbus_id < 0)
		वापस vbus_id;

	rcfg = skl_get_rate_cfg(clkdev->pdata->ssp_clks[clkdev->id].rate_cfg,
						clkdev->rate);
	अगर (!rcfg)
		वापस -EINVAL;

	वापस skl_send_clk_dma_control(clkdev->pdata->pvt_data, rcfg,
					vbus_id, clk_type, enable);
पूर्ण

अटल पूर्णांक skl_clk_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा skl_clk *clkdev = to_skl_clk(hw);

	वापस skl_clk_change_status(clkdev, true);
पूर्ण

अटल व्योम skl_clk_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा skl_clk *clkdev = to_skl_clk(hw);

	skl_clk_change_status(clkdev, false);
पूर्ण

अटल पूर्णांक skl_clk_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
					अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा skl_clk *clkdev = to_skl_clk(hw);
	काष्ठा skl_clk_rate_cfg_table *rcfg;
	पूर्णांक clk_type;

	अगर (!rate)
		वापस -EINVAL;

	rcfg = skl_get_rate_cfg(clkdev->pdata->ssp_clks[clkdev->id].rate_cfg,
							rate);
	अगर (!rcfg)
		वापस -EINVAL;

	clk_type = skl_get_clk_type(clkdev->id);
	अगर (clk_type < 0)
		वापस clk_type;

	skl_fill_clk_ipc(rcfg, clk_type);
	clkdev->rate = rate;

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ skl_clk_recalc_rate(काष्ठा clk_hw *hw,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा skl_clk *clkdev = to_skl_clk(hw);

	अगर (clkdev->rate)
		वापस clkdev->rate;

	वापस 0;
पूर्ण

/* Not supported by clk driver. Implemented to satisfy clk fw */
अटल दीर्घ skl_clk_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ *parent_rate)
अणु
	वापस rate;
पूर्ण

/*
 * prepare/unprepare are used instead of enable/disable as IPC will be sent
 * in non-atomic context.
 */
अटल स्थिर काष्ठा clk_ops skl_clk_ops = अणु
	.prepare = skl_clk_prepare,
	.unprepare = skl_clk_unprepare,
	.set_rate = skl_clk_set_rate,
	.round_rate = skl_clk_round_rate,
	.recalc_rate = skl_clk_recalc_rate,
पूर्ण;

अटल व्योम unरेजिस्टर_parent_src_clk(काष्ठा skl_clk_parent *pclk,
					अचिन्हित पूर्णांक id)
अणु
	जबतक (id--) अणु
		clkdev_drop(pclk[id].lookup);
		clk_hw_unरेजिस्टर_fixed_rate(pclk[id].hw);
	पूर्ण
पूर्ण

अटल व्योम unरेजिस्टर_src_clk(काष्ठा skl_clk_data *dclk)
अणु
	जबतक (dclk->avail_clk_cnt--)
		clkdev_drop(dclk->clk[dclk->avail_clk_cnt]->lookup);
पूर्ण

अटल पूर्णांक skl_रेजिस्टर_parent_clks(काष्ठा device *dev,
			काष्ठा skl_clk_parent *parent,
			काष्ठा skl_clk_parent_src *pclk)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < SKL_MAX_CLK_SRC; i++) अणु

		/* Register Parent घड़ी */
		parent[i].hw = clk_hw_रेजिस्टर_fixed_rate(dev, pclk[i].name,
				pclk[i].parent_name, 0, pclk[i].rate);
		अगर (IS_ERR(parent[i].hw)) अणु
			ret = PTR_ERR(parent[i].hw);
			जाओ err;
		पूर्ण

		parent[i].lookup = clkdev_hw_create(parent[i].hw, pclk[i].name,
									शून्य);
		अगर (!parent[i].lookup) अणु
			clk_hw_unरेजिस्टर_fixed_rate(parent[i].hw);
			ret = -ENOMEM;
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;
err:
	unरेजिस्टर_parent_src_clk(parent, i);
	वापस ret;
पूर्ण

/* Assign fmt_config to clk_data */
अटल काष्ठा skl_clk *रेजिस्टर_skl_clk(काष्ठा device *dev,
			काष्ठा skl_ssp_clk *clk,
			काष्ठा skl_clk_pdata *clk_pdata, पूर्णांक id)
अणु
	काष्ठा clk_init_data init;
	काष्ठा skl_clk *clkdev;
	पूर्णांक ret;

	clkdev = devm_kzalloc(dev, माप(*clkdev), GFP_KERNEL);
	अगर (!clkdev)
		वापस ERR_PTR(-ENOMEM);

	init.name = clk->name;
	init.ops = &skl_clk_ops;
	init.flags = CLK_SET_RATE_GATE;
	init.parent_names = &clk->parent_name;
	init.num_parents = 1;
	clkdev->hw.init = &init;
	clkdev->pdata = clk_pdata;

	clkdev->id = id;
	ret = devm_clk_hw_रेजिस्टर(dev, &clkdev->hw);
	अगर (ret) अणु
		clkdev = ERR_PTR(ret);
		वापस clkdev;
	पूर्ण

	clkdev->lookup = clkdev_hw_create(&clkdev->hw, init.name, शून्य);
	अगर (!clkdev->lookup)
		clkdev = ERR_PTR(-ENOMEM);

	वापस clkdev;
पूर्ण

अटल पूर्णांक skl_clk_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device *parent_dev = dev->parent;
	काष्ठा skl_clk_parent_src *parent_clks;
	काष्ठा skl_clk_pdata *clk_pdata;
	काष्ठा skl_clk_data *data;
	काष्ठा skl_ssp_clk *clks;
	पूर्णांक ret, i;

	clk_pdata = dev_get_platdata(&pdev->dev);
	parent_clks = clk_pdata->parent_clks;
	clks = clk_pdata->ssp_clks;
	अगर (!parent_clks || !clks)
		वापस -EIO;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	/* Register Parent घड़ी */
	ret = skl_रेजिस्टर_parent_clks(parent_dev, data->parent, parent_clks);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < clk_pdata->num_clks; i++) अणु
		/*
		 * Only रेजिस्टर valid घड़ीs
		 * i.e. क्रम which nhlt entry is present.
		 */
		अगर (clks[i].rate_cfg[0].rate == 0)
			जारी;

		data->clk[data->avail_clk_cnt] = रेजिस्टर_skl_clk(dev,
				&clks[i], clk_pdata, i);

		अगर (IS_ERR(data->clk[data->avail_clk_cnt])) अणु
			ret = PTR_ERR(data->clk[data->avail_clk_cnt]);
			जाओ err_unreg_skl_clk;
		पूर्ण

		data->avail_clk_cnt++;
	पूर्ण

	platक्रमm_set_drvdata(pdev, data);

	वापस 0;

err_unreg_skl_clk:
	unरेजिस्टर_src_clk(data);
	unरेजिस्टर_parent_src_clk(data->parent, SKL_MAX_CLK_SRC);

	वापस ret;
पूर्ण

अटल पूर्णांक skl_clk_dev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा skl_clk_data *data;

	data = platक्रमm_get_drvdata(pdev);
	unरेजिस्टर_src_clk(data);
	unरेजिस्टर_parent_src_clk(data->parent, SKL_MAX_CLK_SRC);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver skl_clk_driver = अणु
	.driver = अणु
		.name = "skl-ssp-clk",
	पूर्ण,
	.probe = skl_clk_dev_probe,
	.हटाओ = skl_clk_dev_हटाओ,
पूर्ण;

module_platक्रमm_driver(skl_clk_driver);

MODULE_DESCRIPTION("Skylake clock driver");
MODULE_AUTHOR("Jaikrishna Nemallapudi <jaikrishnax.nemallapudi@intel.com>");
MODULE_AUTHOR("Subhransu S. Prusty <subhransu.s.prusty@intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:skl-ssp-clk");
