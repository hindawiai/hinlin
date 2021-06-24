<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * include/linux/platक्रमm_data/pxa_sdhci.h
 *
 * Copyright 2010 Marvell
 *	Zhangfei Gao <zhangfei.gao@marvell.com>
 *
 * PXA Platक्रमm - SDHCI platक्रमm data definitions
 */

#अगर_अघोषित _PXA_SDHCI_H_
#घोषणा _PXA_SDHCI_H_

/* pxa specअगरic flag */
/* Require घड़ी मुक्त running */
#घोषणा PXA_FLAG_ENABLE_CLOCK_GATING (1<<0)
/* card always wired to host, like on-chip emmc */
#घोषणा PXA_FLAG_CARD_PERMANENT	(1<<1)
/* Board design supports 8-bit data on SD/SDIO BUS */
#घोषणा PXA_FLAG_SD_8_BIT_CAPABLE_SLOT (1<<2)

/*
 * काष्ठा pxa_sdhci_platdata() - Platक्रमm device data क्रम PXA SDHCI
 * @flags: flags क्रम platक्रमm requirement
 * @clk_delay_cycles:
 *	mmp2: each step is roughly 100ps, 5bits width
 *	pxa910: each step is 1ns, 4bits width
 * @clk_delay_sel: select clk_delay, used on pxa910
 *	0: choose feedback clk
 *	1: choose feedback clk + delay value
 *	2: choose पूर्णांकernal clk
 * @clk_delay_enable: enable clk_delay or not, used on pxa910
 * @max_speed: the maximum speed supported
 * @host_caps: Standard MMC host capabilities bit field.
 * @quirks: quirks of platfrom
 * @quirks2: quirks2 of platfrom
 * @pm_caps: pm_caps of platfrom
 */
काष्ठा sdhci_pxa_platdata अणु
	अचिन्हित पूर्णांक	flags;
	अचिन्हित पूर्णांक	clk_delay_cycles;
	अचिन्हित पूर्णांक	clk_delay_sel;
	bool		clk_delay_enable;
	अचिन्हित पूर्णांक	max_speed;
	u32		host_caps;
	u32		host_caps2;
	अचिन्हित पूर्णांक	quirks;
	अचिन्हित पूर्णांक	quirks2;
	अचिन्हित पूर्णांक	pm_caps;
पूर्ण;
#पूर्ण_अगर /* _PXA_SDHCI_H_ */
