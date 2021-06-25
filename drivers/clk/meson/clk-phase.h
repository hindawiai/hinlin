<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2019 BayLibre, SAS.
 * Author: Jerome Brunet <jbrunet@baylibre.com>
 */

#अगर_अघोषित __MESON_CLK_PHASE_H
#घोषणा __MESON_CLK_PHASE_H

#समावेश <linux/clk-provider.h>
#समावेश "parm.h"

काष्ठा meson_clk_phase_data अणु
	काष्ठा parm ph;
पूर्ण;

काष्ठा meson_clk_triphase_data अणु
	काष्ठा parm ph0;
	काष्ठा parm ph1;
	काष्ठा parm ph2;
पूर्ण;

काष्ठा meson_sclk_ws_inv_data अणु
	काष्ठा parm ph;
	काष्ठा parm ws;
पूर्ण;

बाह्य स्थिर काष्ठा clk_ops meson_clk_phase_ops;
बाह्य स्थिर काष्ठा clk_ops meson_clk_triphase_ops;
बाह्य स्थिर काष्ठा clk_ops meson_sclk_ws_inv_ops;

#पूर्ण_अगर /* __MESON_CLK_PHASE_H */
