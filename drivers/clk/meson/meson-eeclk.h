<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2019 BayLibre, SAS.
 * Author: Jerome Brunet <jbrunet@baylibre.com>
 */

#अगर_अघोषित __MESON_CLKC_H
#घोषणा __MESON_CLKC_H

#समावेश <linux/clk-provider.h>
#समावेश "clk-regmap.h"

काष्ठा platक्रमm_device;

काष्ठा meson_eeclkc_data अणु
	काष्ठा clk_regmap *स्थिर	*regmap_clks;
	अचिन्हित पूर्णांक			regmap_clk_num;
	स्थिर काष्ठा reg_sequence	*init_regs;
	अचिन्हित पूर्णांक			init_count;
	काष्ठा clk_hw_onecell_data	*hw_onecell_data;
पूर्ण;

पूर्णांक meson_eeclkc_probe(काष्ठा platक्रमm_device *pdev);

#पूर्ण_अगर /* __MESON_CLKC_H */
