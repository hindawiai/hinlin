<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * omap-mcbsp.h
 *
 * Copyright (C) 2008 Nokia Corporation
 *
 * Contact: Jarkko Nikula <jarkko.nikula@biपंचांगer.com>
 *          Peter Ujfalusi <peter.ujfalusi@ti.com>
 */

#अगर_अघोषित __OMAP_MCBSP_H__
#घोषणा __OMAP_MCBSP_H__

#समावेश <sound/dmaengine_pcm.h>

/* Source घड़ीs क्रम McBSP sample rate generator */
क्रमागत omap_mcbsp_clksrg_clk अणु
	OMAP_MCBSP_SYSCLK_CLKS_FCLK,	/* Internal FCLK */
	OMAP_MCBSP_SYSCLK_CLKS_EXT,	/* External CLKS pin */
	OMAP_MCBSP_SYSCLK_CLK,		/* Internal ICLK */
	OMAP_MCBSP_SYSCLK_CLKX_EXT,	/* External CLKX pin */
	OMAP_MCBSP_SYSCLK_CLKR_EXT,	/* External CLKR pin */
पूर्ण;

/* McBSP भागiders */
क्रमागत omap_mcbsp_भाग अणु
	OMAP_MCBSP_CLKGDV,		/* Sample rate generator भागider */
पूर्ण;

पूर्णांक omap_mcbsp_st_add_controls(काष्ठा snd_soc_pcm_runसमय *rtd, पूर्णांक port_id);

#पूर्ण_अगर /* __OMAP_MCBSP_H__ */
