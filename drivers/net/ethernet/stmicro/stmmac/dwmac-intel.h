<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2020, Intel Corporation
 * DWMAC Intel header file
 */

#अगर_अघोषित __DWMAC_INTEL_H__
#घोषणा __DWMAC_INTEL_H__

#घोषणा POLL_DELAY_US 8

/* SERDES Register */
#घोषणा SERDES_GSR0	0x5	/* Global Status Reg0 */
#घोषणा SERDES_GCR0	0xb	/* Global Configuration Reg0 */

/* SERDES defines */
#घोषणा SERDES_PLL_CLK		BIT(0)		/* PLL clk valid संकेत */
#घोषणा SERDES_PHY_RX_CLK	BIT(1)		/* PSE SGMII PHY rx clk */
#घोषणा SERDES_RST		BIT(2)		/* Serdes Reset */
#घोषणा SERDES_PWR_ST_MASK	GENMASK(6, 4)	/* Serdes Power state*/
#घोषणा SERDES_PWR_ST_SHIFT	4
#घोषणा SERDES_PWR_ST_P0	0x0
#घोषणा SERDES_PWR_ST_P3	0x3

#पूर्ण_अगर /* __DWMAC_INTEL_H__ */
