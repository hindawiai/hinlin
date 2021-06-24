<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2019 BayLibre, SAS.
 * Author: Jerome Brunet <jbrunet@baylibre.com>
 */

#अगर_अघोषित __MESON_CLK_DUALDIV_H
#घोषणा __MESON_CLK_DUALDIV_H

#समावेश <linux/clk-provider.h>
#समावेश "parm.h"

काष्ठा meson_clk_duaद_भाग_param अणु
	अचिन्हित पूर्णांक n1;
	अचिन्हित पूर्णांक n2;
	अचिन्हित पूर्णांक m1;
	अचिन्हित पूर्णांक m2;
	अचिन्हित पूर्णांक dual;
पूर्ण;

काष्ठा meson_clk_duaद_भाग_data अणु
	काष्ठा parm n1;
	काष्ठा parm n2;
	काष्ठा parm m1;
	काष्ठा parm m2;
	काष्ठा parm dual;
	स्थिर काष्ठा meson_clk_duaद_भाग_param *table;
पूर्ण;

बाह्य स्थिर काष्ठा clk_ops meson_clk_duaद_भाग_ops;
बाह्य स्थिर काष्ठा clk_ops meson_clk_duaद_भाग_ro_ops;

#पूर्ण_अगर /* __MESON_CLK_DUALDIV_H */
