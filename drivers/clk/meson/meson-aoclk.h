<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+ OR MIT) */
/*
 * Copyright (c) 2017 BayLibre, SAS
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 *
 * Copyright (c) 2018 Amlogic, inc.
 * Author: Qiufang Dai <qiufang.dai@amlogic.com>
 * Author: Yixun Lan <yixun.lan@amlogic.com>
 */

#अगर_अघोषित __MESON_AOCLK_H__
#घोषणा __MESON_AOCLK_H__

#समावेश <linux/clk-provider.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset-controller.h>

#समावेश "clk-regmap.h"

काष्ठा meson_aoclk_data अणु
	स्थिर अचिन्हित पूर्णांक			reset_reg;
	स्थिर पूर्णांक				num_reset;
	स्थिर अचिन्हित पूर्णांक			*reset;
	स्थिर पूर्णांक				num_clks;
	काष्ठा clk_regmap			**clks;
	स्थिर काष्ठा clk_hw_onecell_data	*hw_data;
पूर्ण;

काष्ठा meson_aoclk_reset_controller अणु
	काष्ठा reset_controller_dev		reset;
	स्थिर काष्ठा meson_aoclk_data		*data;
	काष्ठा regmap				*regmap;
पूर्ण;

पूर्णांक meson_aoclkc_probe(काष्ठा platक्रमm_device *pdev);
#पूर्ण_अगर
