<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
//
// OWL common घड़ी driver
//
// Copyright (c) 2014 Actions Semi Inc.
// Author: David Liu <liuwei@actions-semi.com>
//
// Copyright (c) 2018 Linaro Ltd.
// Author: Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>

#अगर_अघोषित _OWL_COMMON_H_
#घोषणा _OWL_COMMON_H_

#समावेश <linux/clk-provider.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/regmap.h>

काष्ठा device_node;

काष्ठा owl_clk_common अणु
	काष्ठा regmap			*regmap;
	काष्ठा clk_hw			hw;
पूर्ण;

काष्ठा owl_clk_desc अणु
	काष्ठा owl_clk_common		**clks;
	अचिन्हित दीर्घ			num_clks;
	काष्ठा clk_hw_onecell_data	*hw_clks;
	स्थिर काष्ठा owl_reset_map	*resets;
	अचिन्हित दीर्घ			num_resets;
	काष्ठा regmap			*regmap;
पूर्ण;

अटल अंतरभूत काष्ठा owl_clk_common *
	hw_to_owl_clk_common(स्थिर काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा owl_clk_common, hw);
पूर्ण

पूर्णांक owl_clk_regmap_init(काष्ठा platक्रमm_device *pdev,
			काष्ठा owl_clk_desc *desc);
पूर्णांक owl_clk_probe(काष्ठा device *dev, काष्ठा clk_hw_onecell_data *hw_clks);

#पूर्ण_अगर /* _OWL_COMMON_H_ */
