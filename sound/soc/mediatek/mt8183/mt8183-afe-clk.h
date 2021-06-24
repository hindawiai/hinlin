<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * mt8183-afe-clk.h  --  Mediatek 8183 afe घड़ी ctrl definition
 *
 * Copyright (c) 2018 MediaTek Inc.
 * Author: KaiChieh Chuang <kaichieh.chuang@mediatek.com>
 */

#अगर_अघोषित _MT8183_AFE_CLK_H_
#घोषणा _MT8183_AFE_CLK_H_

/* APLL */
#घोषणा APLL1_W_NAME "APLL1"
#घोषणा APLL2_W_NAME "APLL2"
क्रमागत अणु
	MT8183_APLL1 = 0,
	MT8183_APLL2,
पूर्ण;

काष्ठा mtk_base_afe;

पूर्णांक mt8183_init_घड़ी(काष्ठा mtk_base_afe *afe);
पूर्णांक mt8183_afe_enable_घड़ी(काष्ठा mtk_base_afe *afe);
पूर्णांक mt8183_afe_disable_घड़ी(काष्ठा mtk_base_afe *afe);

पूर्णांक mt8183_apll1_enable(काष्ठा mtk_base_afe *afe);
व्योम mt8183_apll1_disable(काष्ठा mtk_base_afe *afe);

पूर्णांक mt8183_apll2_enable(काष्ठा mtk_base_afe *afe);
व्योम mt8183_apll2_disable(काष्ठा mtk_base_afe *afe);

पूर्णांक mt8183_get_apll_rate(काष्ठा mtk_base_afe *afe, पूर्णांक apll);
पूर्णांक mt8183_get_apll_by_rate(काष्ठा mtk_base_afe *afe, पूर्णांक rate);
पूर्णांक mt8183_get_apll_by_name(काष्ठा mtk_base_afe *afe, स्थिर अक्षर *name);

पूर्णांक mt8183_mck_enable(काष्ठा mtk_base_afe *afe, पूर्णांक mck_id, पूर्णांक rate);
व्योम mt8183_mck_disable(काष्ठा mtk_base_afe *afe, पूर्णांक mck_id);
#पूर्ण_अगर
