<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// mt6797-afe-clk.c  --  Mediatek 6797 afe घड़ी ctrl
//
// Copyright (c) 2018 MediaTek Inc.
// Author: KaiChieh Chuang <kaichieh.chuang@mediatek.com>

#समावेश <linux/clk.h>

#समावेश "mt6797-afe-common.h"
#समावेश "mt6797-afe-clk.h"

क्रमागत अणु
	CLK_INFRA_SYS_AUD,
	CLK_INFRA_SYS_AUD_26M,
	CLK_TOP_MUX_AUD,
	CLK_TOP_MUX_AUD_BUS,
	CLK_TOP_SYSPLL3_D4,
	CLK_TOP_SYSPLL1_D4,
	CLK_CLK26M,
	CLK_NUM
पूर्ण;

अटल स्थिर अक्षर *aud_clks[CLK_NUM] = अणु
	[CLK_INFRA_SYS_AUD] = "infra_sys_audio_clk",
	[CLK_INFRA_SYS_AUD_26M] = "infra_sys_audio_26m",
	[CLK_TOP_MUX_AUD] = "top_mux_audio",
	[CLK_TOP_MUX_AUD_BUS] = "top_mux_aud_intbus",
	[CLK_TOP_SYSPLL3_D4] = "top_sys_pll3_d4",
	[CLK_TOP_SYSPLL1_D4] = "top_sys_pll1_d4",
	[CLK_CLK26M] = "top_clk26m_clk",
पूर्ण;

पूर्णांक mt6797_init_घड़ी(काष्ठा mtk_base_afe *afe)
अणु
	काष्ठा mt6797_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक i;

	afe_priv->clk = devm_kसुस्मृति(afe->dev, CLK_NUM, माप(*afe_priv->clk),
				     GFP_KERNEL);
	अगर (!afe_priv->clk)
		वापस -ENOMEM;

	क्रम (i = 0; i < CLK_NUM; i++) अणु
		afe_priv->clk[i] = devm_clk_get(afe->dev, aud_clks[i]);
		अगर (IS_ERR(afe_priv->clk[i])) अणु
			dev_err(afe->dev, "%s(), devm_clk_get %s fail, ret %ld\n",
				__func__, aud_clks[i],
				PTR_ERR(afe_priv->clk[i]));
			वापस PTR_ERR(afe_priv->clk[i]);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mt6797_afe_enable_घड़ी(काष्ठा mtk_base_afe *afe)
अणु
	काष्ठा mt6797_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक ret;

	ret = clk_prepare_enable(afe_priv->clk[CLK_INFRA_SYS_AUD]);
	अगर (ret) अणु
		dev_err(afe->dev, "%s(), clk_prepare_enable %s fail %d\n",
			__func__, aud_clks[CLK_INFRA_SYS_AUD], ret);
		जाओ CLK_INFRA_SYS_AUDIO_ERR;
	पूर्ण

	ret = clk_prepare_enable(afe_priv->clk[CLK_INFRA_SYS_AUD_26M]);
	अगर (ret) अणु
		dev_err(afe->dev, "%s(), clk_prepare_enable %s fail %d\n",
			__func__, aud_clks[CLK_INFRA_SYS_AUD_26M], ret);
		जाओ CLK_INFRA_SYS_AUD_26M_ERR;
	पूर्ण

	ret = clk_prepare_enable(afe_priv->clk[CLK_TOP_MUX_AUD]);
	अगर (ret) अणु
		dev_err(afe->dev, "%s(), clk_prepare_enable %s fail %d\n",
			__func__, aud_clks[CLK_TOP_MUX_AUD], ret);
		जाओ CLK_MUX_AUDIO_ERR;
	पूर्ण

	ret = clk_set_parent(afe_priv->clk[CLK_TOP_MUX_AUD],
			     afe_priv->clk[CLK_CLK26M]);
	अगर (ret) अणु
		dev_err(afe->dev, "%s(), clk_set_parent %s-%s fail %d\n",
			__func__, aud_clks[CLK_TOP_MUX_AUD],
			aud_clks[CLK_CLK26M], ret);
		जाओ CLK_MUX_AUDIO_ERR;
	पूर्ण

	ret = clk_prepare_enable(afe_priv->clk[CLK_TOP_MUX_AUD_BUS]);
	अगर (ret) अणु
		dev_err(afe->dev, "%s(), clk_prepare_enable %s fail %d\n",
			__func__, aud_clks[CLK_TOP_MUX_AUD_BUS], ret);
		जाओ CLK_MUX_AUDIO_INTBUS_ERR;
	पूर्ण

	वापस ret;

CLK_MUX_AUDIO_INTBUS_ERR:
	clk_disable_unprepare(afe_priv->clk[CLK_TOP_MUX_AUD_BUS]);
CLK_MUX_AUDIO_ERR:
	clk_disable_unprepare(afe_priv->clk[CLK_TOP_MUX_AUD]);
CLK_INFRA_SYS_AUD_26M_ERR:
	clk_disable_unprepare(afe_priv->clk[CLK_INFRA_SYS_AUD_26M]);
CLK_INFRA_SYS_AUDIO_ERR:
	clk_disable_unprepare(afe_priv->clk[CLK_INFRA_SYS_AUD]);

	वापस 0;
पूर्ण

पूर्णांक mt6797_afe_disable_घड़ी(काष्ठा mtk_base_afe *afe)
अणु
	काष्ठा mt6797_afe_निजी *afe_priv = afe->platक्रमm_priv;

	clk_disable_unprepare(afe_priv->clk[CLK_TOP_MUX_AUD_BUS]);
	clk_disable_unprepare(afe_priv->clk[CLK_TOP_MUX_AUD]);
	clk_disable_unprepare(afe_priv->clk[CLK_INFRA_SYS_AUD_26M]);
	clk_disable_unprepare(afe_priv->clk[CLK_INFRA_SYS_AUD]);

	वापस 0;
पूर्ण
