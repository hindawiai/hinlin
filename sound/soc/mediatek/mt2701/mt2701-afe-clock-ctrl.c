<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * mt2701-afe-घड़ी-ctrl.c  --  Mediatek 2701 afe घड़ी ctrl
 *
 * Copyright (c) 2016 MediaTek Inc.
 * Author: Garlic Tseng <garlic.tseng@mediatek.com>
 *	   Ryder Lee <ryder.lee@mediatek.com>
 */

#समावेश "mt2701-afe-common.h"
#समावेश "mt2701-afe-clock-ctrl.h"

अटल स्थिर अक्षर *स्थिर base_clks[] = अणु
	[MT2701_INFRA_SYS_AUDIO] = "infra_sys_audio_clk",
	[MT2701_TOP_AUD_MCLK_SRC0] = "top_audio_mux1_sel",
	[MT2701_TOP_AUD_MCLK_SRC1] = "top_audio_mux2_sel",
	[MT2701_TOP_AUD_A1SYS] = "top_audio_a1sys_hp",
	[MT2701_TOP_AUD_A2SYS] = "top_audio_a2sys_hp",
	[MT2701_AUDSYS_AFE] = "audio_afe_pd",
	[MT2701_AUDSYS_AFE_CONN] = "audio_afe_conn_pd",
	[MT2701_AUDSYS_A1SYS] = "audio_a1sys_pd",
	[MT2701_AUDSYS_A2SYS] = "audio_a2sys_pd",
पूर्ण;

पूर्णांक mt2701_init_घड़ी(काष्ठा mtk_base_afe *afe)
अणु
	काष्ठा mt2701_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक i;

	क्रम (i = 0; i < MT2701_BASE_CLK_NUM; i++) अणु
		afe_priv->base_ck[i] = devm_clk_get(afe->dev, base_clks[i]);
		अगर (IS_ERR(afe_priv->base_ck[i])) अणु
			dev_err(afe->dev, "failed to get %s\n", base_clks[i]);
			वापस PTR_ERR(afe_priv->base_ck[i]);
		पूर्ण
	पूर्ण

	/* Get I2S related घड़ीs */
	क्रम (i = 0; i < afe_priv->soc->i2s_num; i++) अणु
		काष्ठा mt2701_i2s_path *i2s_path = &afe_priv->i2s_path[i];
		काष्ठा clk *i2s_ck;
		अक्षर name[13];

		snम_लिखो(name, माप(name), "i2s%d_src_sel", i);
		i2s_path->sel_ck = devm_clk_get(afe->dev, name);
		अगर (IS_ERR(i2s_path->sel_ck)) अणु
			dev_err(afe->dev, "failed to get %s\n", name);
			वापस PTR_ERR(i2s_path->sel_ck);
		पूर्ण

		snम_लिखो(name, माप(name), "i2s%d_src_div", i);
		i2s_path->भाग_ck = devm_clk_get(afe->dev, name);
		अगर (IS_ERR(i2s_path->भाग_ck)) अणु
			dev_err(afe->dev, "failed to get %s\n", name);
			वापस PTR_ERR(i2s_path->भाग_ck);
		पूर्ण

		snम_लिखो(name, माप(name), "i2s%d_mclk_en", i);
		i2s_path->mclk_ck = devm_clk_get(afe->dev, name);
		अगर (IS_ERR(i2s_path->mclk_ck)) अणु
			dev_err(afe->dev, "failed to get %s\n", name);
			वापस PTR_ERR(i2s_path->mclk_ck);
		पूर्ण

		snम_लिखो(name, माप(name), "i2so%d_hop_ck", i);
		i2s_ck = devm_clk_get(afe->dev, name);
		अगर (IS_ERR(i2s_ck)) अणु
			dev_err(afe->dev, "failed to get %s\n", name);
			वापस PTR_ERR(i2s_ck);
		पूर्ण
		i2s_path->hop_ck[SNDRV_PCM_STREAM_PLAYBACK] = i2s_ck;

		snम_लिखो(name, माप(name), "i2si%d_hop_ck", i);
		i2s_ck = devm_clk_get(afe->dev, name);
		अगर (IS_ERR(i2s_ck)) अणु
			dev_err(afe->dev, "failed to get %s\n", name);
			वापस PTR_ERR(i2s_ck);
		पूर्ण
		i2s_path->hop_ck[SNDRV_PCM_STREAM_CAPTURE] = i2s_ck;

		snम_लिखो(name, माप(name), "asrc%d_out_ck", i);
		i2s_path->asrco_ck = devm_clk_get(afe->dev, name);
		अगर (IS_ERR(i2s_path->asrco_ck)) अणु
			dev_err(afe->dev, "failed to get %s\n", name);
			वापस PTR_ERR(i2s_path->asrco_ck);
		पूर्ण
	पूर्ण

	/* Some platक्रमms may support BT path */
	afe_priv->mrgअगर_ck = devm_clk_get(afe->dev, "audio_mrgif_pd");
	अगर (IS_ERR(afe_priv->mrgअगर_ck)) अणु
		अगर (PTR_ERR(afe_priv->mrgअगर_ck) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;

		afe_priv->mrgअगर_ck = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mt2701_afe_enable_i2s(काष्ठा mtk_base_afe *afe,
			  काष्ठा mt2701_i2s_path *i2s_path,
			  पूर्णांक dir)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(i2s_path->asrco_ck);
	अगर (ret) अणु
		dev_err(afe->dev, "failed to enable ASRC clock %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(i2s_path->hop_ck[dir]);
	अगर (ret) अणु
		dev_err(afe->dev, "failed to enable I2S clock %d\n", ret);
		जाओ err_hop_ck;
	पूर्ण

	वापस 0;

err_hop_ck:
	clk_disable_unprepare(i2s_path->asrco_ck);

	वापस ret;
पूर्ण

व्योम mt2701_afe_disable_i2s(काष्ठा mtk_base_afe *afe,
			    काष्ठा mt2701_i2s_path *i2s_path,
			    पूर्णांक dir)
अणु
	clk_disable_unprepare(i2s_path->hop_ck[dir]);
	clk_disable_unprepare(i2s_path->asrco_ck);
पूर्ण

पूर्णांक mt2701_afe_enable_mclk(काष्ठा mtk_base_afe *afe, पूर्णांक id)
अणु
	काष्ठा mt2701_afe_निजी *afe_priv = afe->platक्रमm_priv;
	काष्ठा mt2701_i2s_path *i2s_path = &afe_priv->i2s_path[id];

	वापस clk_prepare_enable(i2s_path->mclk_ck);
पूर्ण

व्योम mt2701_afe_disable_mclk(काष्ठा mtk_base_afe *afe, पूर्णांक id)
अणु
	काष्ठा mt2701_afe_निजी *afe_priv = afe->platक्रमm_priv;
	काष्ठा mt2701_i2s_path *i2s_path = &afe_priv->i2s_path[id];

	clk_disable_unprepare(i2s_path->mclk_ck);
पूर्ण

पूर्णांक mt2701_enable_bपंचांगrg_clk(काष्ठा mtk_base_afe *afe)
अणु
	काष्ठा mt2701_afe_निजी *afe_priv = afe->platक्रमm_priv;

	वापस clk_prepare_enable(afe_priv->mrgअगर_ck);
पूर्ण

व्योम mt2701_disable_bपंचांगrg_clk(काष्ठा mtk_base_afe *afe)
अणु
	काष्ठा mt2701_afe_निजी *afe_priv = afe->platक्रमm_priv;

	clk_disable_unprepare(afe_priv->mrgअगर_ck);
पूर्ण

अटल पूर्णांक mt2701_afe_enable_audsys(काष्ठा mtk_base_afe *afe)
अणु
	काष्ठा mt2701_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक ret;

	/* Enable infra घड़ी gate */
	ret = clk_prepare_enable(afe_priv->base_ck[MT2701_INFRA_SYS_AUDIO]);
	अगर (ret)
		वापस ret;

	/* Enable top a1sys घड़ी gate */
	ret = clk_prepare_enable(afe_priv->base_ck[MT2701_TOP_AUD_A1SYS]);
	अगर (ret)
		जाओ err_a1sys;

	/* Enable top a2sys घड़ी gate */
	ret = clk_prepare_enable(afe_priv->base_ck[MT2701_TOP_AUD_A2SYS]);
	अगर (ret)
		जाओ err_a2sys;

	/* Internal घड़ी gates */
	ret = clk_prepare_enable(afe_priv->base_ck[MT2701_AUDSYS_AFE]);
	अगर (ret)
		जाओ err_afe;

	ret = clk_prepare_enable(afe_priv->base_ck[MT2701_AUDSYS_A1SYS]);
	अगर (ret)
		जाओ err_audio_a1sys;

	ret = clk_prepare_enable(afe_priv->base_ck[MT2701_AUDSYS_A2SYS]);
	अगर (ret)
		जाओ err_audio_a2sys;

	ret = clk_prepare_enable(afe_priv->base_ck[MT2701_AUDSYS_AFE_CONN]);
	अगर (ret)
		जाओ err_afe_conn;

	वापस 0;

err_afe_conn:
	clk_disable_unprepare(afe_priv->base_ck[MT2701_AUDSYS_A2SYS]);
err_audio_a2sys:
	clk_disable_unprepare(afe_priv->base_ck[MT2701_AUDSYS_A1SYS]);
err_audio_a1sys:
	clk_disable_unprepare(afe_priv->base_ck[MT2701_AUDSYS_AFE]);
err_afe:
	clk_disable_unprepare(afe_priv->base_ck[MT2701_TOP_AUD_A2SYS]);
err_a2sys:
	clk_disable_unprepare(afe_priv->base_ck[MT2701_TOP_AUD_A1SYS]);
err_a1sys:
	clk_disable_unprepare(afe_priv->base_ck[MT2701_INFRA_SYS_AUDIO]);

	वापस ret;
पूर्ण

अटल व्योम mt2701_afe_disable_audsys(काष्ठा mtk_base_afe *afe)
अणु
	काष्ठा mt2701_afe_निजी *afe_priv = afe->platक्रमm_priv;

	clk_disable_unprepare(afe_priv->base_ck[MT2701_AUDSYS_AFE_CONN]);
	clk_disable_unprepare(afe_priv->base_ck[MT2701_AUDSYS_A2SYS]);
	clk_disable_unprepare(afe_priv->base_ck[MT2701_AUDSYS_A1SYS]);
	clk_disable_unprepare(afe_priv->base_ck[MT2701_AUDSYS_AFE]);
	clk_disable_unprepare(afe_priv->base_ck[MT2701_TOP_AUD_A1SYS]);
	clk_disable_unprepare(afe_priv->base_ck[MT2701_TOP_AUD_A2SYS]);
	clk_disable_unprepare(afe_priv->base_ck[MT2701_INFRA_SYS_AUDIO]);
पूर्ण

पूर्णांक mt2701_afe_enable_घड़ी(काष्ठा mtk_base_afe *afe)
अणु
	पूर्णांक ret;

	/* Enable audio प्रणाली */
	ret = mt2701_afe_enable_audsys(afe);
	अगर (ret) अणु
		dev_err(afe->dev, "failed to enable audio system %d\n", ret);
		वापस ret;
	पूर्ण

	regmap_update_bits(afe->regmap, ASYS_TOP_CON,
			   ASYS_TOP_CON_ASYS_TIMING_ON,
			   ASYS_TOP_CON_ASYS_TIMING_ON);
	regmap_update_bits(afe->regmap, AFE_DAC_CON0,
			   AFE_DAC_CON0_AFE_ON,
			   AFE_DAC_CON0_AFE_ON);

	/* Configure ASRC */
	regmap_ग_लिखो(afe->regmap, PWR1_ASM_CON1, PWR1_ASM_CON1_INIT_VAL);
	regmap_ग_लिखो(afe->regmap, PWR2_ASM_CON1, PWR2_ASM_CON1_INIT_VAL);

	वापस 0;
पूर्ण

पूर्णांक mt2701_afe_disable_घड़ी(काष्ठा mtk_base_afe *afe)
अणु
	regmap_update_bits(afe->regmap, ASYS_TOP_CON,
			   ASYS_TOP_CON_ASYS_TIMING_ON, 0);
	regmap_update_bits(afe->regmap, AFE_DAC_CON0,
			   AFE_DAC_CON0_AFE_ON, 0);

	mt2701_afe_disable_audsys(afe);

	वापस 0;
पूर्ण

पूर्णांक mt2701_mclk_configuration(काष्ठा mtk_base_afe *afe, पूर्णांक id)

अणु
	काष्ठा mt2701_afe_निजी *priv = afe->platक्रमm_priv;
	काष्ठा mt2701_i2s_path *i2s_path = &priv->i2s_path[id];
	पूर्णांक ret = -EINVAL;

	/* Set mclk source */
	अगर (!(MT2701_PLL_DOMAIN_0_RATE % i2s_path->mclk_rate))
		ret = clk_set_parent(i2s_path->sel_ck,
				     priv->base_ck[MT2701_TOP_AUD_MCLK_SRC0]);
	अन्यथा अगर (!(MT2701_PLL_DOMAIN_1_RATE % i2s_path->mclk_rate))
		ret = clk_set_parent(i2s_path->sel_ck,
				     priv->base_ck[MT2701_TOP_AUD_MCLK_SRC1]);

	अगर (ret) अणु
		dev_err(afe->dev, "failed to set mclk source\n");
		वापस ret;
	पूर्ण

	/* Set mclk भागider */
	ret = clk_set_rate(i2s_path->भाग_ck, i2s_path->mclk_rate);
	अगर (ret) अणु
		dev_err(afe->dev, "failed to set mclk divider %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
