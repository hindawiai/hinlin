<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Aptina Sensor PLL Configuration
 *
 * Copyright (C) 2012 Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#अगर_अघोषित __APTINA_PLL_H
#घोषणा __APTINA_PLL_H

काष्ठा aptina_pll अणु
	अचिन्हित पूर्णांक ext_घड़ी;
	अचिन्हित पूर्णांक pix_घड़ी;

	अचिन्हित पूर्णांक n;
	अचिन्हित पूर्णांक m;
	अचिन्हित पूर्णांक p1;
पूर्ण;

काष्ठा aptina_pll_limits अणु
	अचिन्हित पूर्णांक ext_घड़ी_min;
	अचिन्हित पूर्णांक ext_घड़ी_max;
	अचिन्हित पूर्णांक पूर्णांक_घड़ी_min;
	अचिन्हित पूर्णांक पूर्णांक_घड़ी_max;
	अचिन्हित पूर्णांक out_घड़ी_min;
	अचिन्हित पूर्णांक out_घड़ी_max;
	अचिन्हित पूर्णांक pix_घड़ी_max;

	अचिन्हित पूर्णांक n_min;
	अचिन्हित पूर्णांक n_max;
	अचिन्हित पूर्णांक m_min;
	अचिन्हित पूर्णांक m_max;
	अचिन्हित पूर्णांक p1_min;
	अचिन्हित पूर्णांक p1_max;
पूर्ण;

काष्ठा device;

पूर्णांक aptina_pll_calculate(काष्ठा device *dev,
			 स्थिर काष्ठा aptina_pll_limits *limits,
			 काष्ठा aptina_pll *pll);

#पूर्ण_अगर /* __APTINA_PLL_H */
