<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Intel Atom platक्रमm घड़ीs क्रम BayTrail and CherryTrail SoC.
 *
 * Copyright (C) 2016, Intel Corporation
 * Author: Irina Tirdea <irina.tirdea@पूर्णांकel.com>
 */

#अगर_अघोषित __PLATFORM_DATA_X86_CLK_PMC_ATOM_H
#घोषणा __PLATFORM_DATA_X86_CLK_PMC_ATOM_H

/**
 * काष्ठा pmc_clk - PMC platक्रमm घड़ी configuration
 *
 * @name:	identअगरied, typically pmc_plt_clk_<x>, x=[0..5]
 * @freq:	in Hz, 19.2MHz  and 25MHz (Baytrail only) supported
 * @parent_name: one of 'xtal' or 'osc'
 */
काष्ठा pmc_clk अणु
	स्थिर अक्षर *name;
	अचिन्हित दीर्घ freq;
	स्थिर अक्षर *parent_name;
पूर्ण;

/**
 * काष्ठा pmc_clk_data - common PMC घड़ी configuration
 *
 * @base:	PMC घड़ी रेजिस्टर base offset
 * @clks:	poपूर्णांकer to set of रेजिस्टरed घड़ीs, typically 0..5
 * @critical:	flag to indicate अगर firmware enabled pmc_plt_clks
 *		should be marked as critial or not
 */
काष्ठा pmc_clk_data अणु
	व्योम __iomem *base;
	स्थिर काष्ठा pmc_clk *clks;
	bool critical;
पूर्ण;

#पूर्ण_अगर /* __PLATFORM_DATA_X86_CLK_PMC_ATOM_H */
