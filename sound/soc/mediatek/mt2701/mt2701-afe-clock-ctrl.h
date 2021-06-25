<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * mt2701-afe-घड़ी-ctrl.h  --  Mediatek 2701 afe घड़ी ctrl definition
 *
 * Copyright (c) 2016 MediaTek Inc.
 * Author: Garlic Tseng <garlic.tseng@mediatek.com>
 *	   Ryder Lee <ryder.lee@mediatek.com>
 */

#अगर_अघोषित _MT2701_AFE_CLOCK_CTRL_H_
#घोषणा _MT2701_AFE_CLOCK_CTRL_H_

काष्ठा mtk_base_afe;
काष्ठा mt2701_i2s_path;

पूर्णांक mt2701_init_घड़ी(काष्ठा mtk_base_afe *afe);
पूर्णांक mt2701_afe_enable_घड़ी(काष्ठा mtk_base_afe *afe);
पूर्णांक mt2701_afe_disable_घड़ी(काष्ठा mtk_base_afe *afe);

पूर्णांक mt2701_afe_enable_i2s(काष्ठा mtk_base_afe *afe,
			  काष्ठा mt2701_i2s_path *i2s_path,
			  पूर्णांक dir);
व्योम mt2701_afe_disable_i2s(काष्ठा mtk_base_afe *afe,
			    काष्ठा mt2701_i2s_path *i2s_path,
			    पूर्णांक dir);
पूर्णांक mt2701_afe_enable_mclk(काष्ठा mtk_base_afe *afe, पूर्णांक id);
व्योम mt2701_afe_disable_mclk(काष्ठा mtk_base_afe *afe, पूर्णांक id);

पूर्णांक mt2701_enable_bपंचांगrg_clk(काष्ठा mtk_base_afe *afe);
व्योम mt2701_disable_bपंचांगrg_clk(काष्ठा mtk_base_afe *afe);

पूर्णांक mt2701_mclk_configuration(काष्ठा mtk_base_afe *afe, पूर्णांक id);

#पूर्ण_अगर
