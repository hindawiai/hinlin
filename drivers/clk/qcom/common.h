<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2014, The Linux Foundation. All rights reserved. */

#अगर_अघोषित __QCOM_CLK_COMMON_H__
#घोषणा __QCOM_CLK_COMMON_H__

काष्ठा platक्रमm_device;
काष्ठा regmap_config;
काष्ठा clk_regmap;
काष्ठा qcom_reset_map;
काष्ठा regmap;
काष्ठा freq_tbl;
काष्ठा clk_hw;

#घोषणा PLL_LOCK_COUNT_SHIFT	8
#घोषणा PLL_LOCK_COUNT_MASK	0x3f
#घोषणा PLL_BIAS_COUNT_SHIFT	14
#घोषणा PLL_BIAS_COUNT_MASK	0x3f
#घोषणा PLL_VOTE_FSM_ENA	BIT(20)
#घोषणा PLL_VOTE_FSM_RESET	BIT(21)

काष्ठा qcom_cc_desc अणु
	स्थिर काष्ठा regmap_config *config;
	काष्ठा clk_regmap **clks;
	माप_प्रकार num_clks;
	स्थिर काष्ठा qcom_reset_map *resets;
	माप_प्रकार num_resets;
	काष्ठा gdsc **gdscs;
	माप_प्रकार num_gdscs;
	काष्ठा clk_hw **clk_hws;
	माप_प्रकार num_clk_hws;
पूर्ण;

/**
 * काष्ठा parent_map - map table क्रम source select configuration values
 * @src: source
 * @cfg: configuration value
 */
काष्ठा parent_map अणु
	u8 src;
	u8 cfg;
पूर्ण;

बाह्य स्थिर काष्ठा freq_tbl *qcom_find_freq(स्थिर काष्ठा freq_tbl *f,
					     अचिन्हित दीर्घ rate);
बाह्य स्थिर काष्ठा freq_tbl *qcom_find_freq_न्यूनमान(स्थिर काष्ठा freq_tbl *f,
						   अचिन्हित दीर्घ rate);
बाह्य व्योम
qcom_pll_set_fsm_mode(काष्ठा regmap *m, u32 reg, u8 bias_count, u8 lock_count);
बाह्य पूर्णांक qcom_find_src_index(काष्ठा clk_hw *hw, स्थिर काष्ठा parent_map *map,
			       u8 src);

बाह्य पूर्णांक qcom_cc_रेजिस्टर_board_clk(काष्ठा device *dev, स्थिर अक्षर *path,
				      स्थिर अक्षर *name, अचिन्हित दीर्घ rate);
बाह्य पूर्णांक qcom_cc_रेजिस्टर_sleep_clk(काष्ठा device *dev);

बाह्य काष्ठा regmap *qcom_cc_map(काष्ठा platक्रमm_device *pdev,
				  स्थिर काष्ठा qcom_cc_desc *desc);
बाह्य पूर्णांक qcom_cc_really_probe(काष्ठा platक्रमm_device *pdev,
				स्थिर काष्ठा qcom_cc_desc *desc,
				काष्ठा regmap *regmap);
बाह्य पूर्णांक qcom_cc_probe(काष्ठा platक्रमm_device *pdev,
			 स्थिर काष्ठा qcom_cc_desc *desc);
बाह्य पूर्णांक qcom_cc_probe_by_index(काष्ठा platक्रमm_device *pdev, पूर्णांक index,
				  स्थिर काष्ठा qcom_cc_desc *desc);

#पूर्ण_अगर
