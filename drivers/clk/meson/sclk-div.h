<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2018 BayLibre, SAS.
 * Author: Jerome Brunet <jbrunet@baylibre.com>
 */

#अगर_अघोषित __MESON_SCLK_DIV_H
#घोषणा __MESON_SCLK_DIV_H

#समावेश <linux/clk-provider.h>
#समावेश "parm.h"

काष्ठा meson_sclk_भाग_data अणु
	काष्ठा parm भाग;
	काष्ठा parm hi;
	अचिन्हित पूर्णांक cached_भाग;
	काष्ठा clk_duty cached_duty;
पूर्ण;

बाह्य स्थिर काष्ठा clk_ops meson_sclk_भाग_ops;

#पूर्ण_अगर /* __MESON_SCLK_DIV_H */
