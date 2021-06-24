<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * 10G controller driver क्रम Samsung Exynos SoCs
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Siva Reddy Kallam <siva.kallam@samsung.com>
 */
#अगर_अघोषित __SXGBE_PLATFORM_H__
#घोषणा __SXGBE_PLATFORM_H__

#समावेश <linux/phy.h>

/* MDC Clock Selection define*/
#घोषणा SXGBE_CSR_100_150M	0x0	/* MDC = clk_scr_i/62 */
#घोषणा SXGBE_CSR_150_250M	0x1	/* MDC = clk_scr_i/102 */
#घोषणा SXGBE_CSR_250_300M	0x2	/* MDC = clk_scr_i/122 */
#घोषणा SXGBE_CSR_300_350M	0x3	/* MDC = clk_scr_i/142 */
#घोषणा SXGBE_CSR_350_400M	0x4	/* MDC = clk_scr_i/162 */
#घोषणा SXGBE_CSR_400_500M	0x5	/* MDC = clk_scr_i/202 */

/* Platfrom data क्रम platक्रमm device काष्ठाure's
 * platक्रमm_data field
 */
काष्ठा sxgbe_mdio_bus_data अणु
	अचिन्हित पूर्णांक phy_mask;
	पूर्णांक *irqs;
	पूर्णांक probed_phy_irq;
पूर्ण;

काष्ठा sxgbe_dma_cfg अणु
	पूर्णांक pbl;
	पूर्णांक fixed_burst;
	पूर्णांक burst_map;
	पूर्णांक adv_addr_mode;
पूर्ण;

काष्ठा sxgbe_plat_data अणु
	अक्षर *phy_bus_name;
	पूर्णांक bus_id;
	पूर्णांक phy_addr;
	phy_पूर्णांकerface_t पूर्णांकerface;
	काष्ठा sxgbe_mdio_bus_data *mdio_bus_data;
	काष्ठा sxgbe_dma_cfg *dma_cfg;
	पूर्णांक clk_csr;
	पूर्णांक pmt;
	पूर्णांक क्रमce_sf_dma_mode;
	पूर्णांक क्रमce_thresh_dma_mode;
	पूर्णांक riwt_off;
पूर्ण;

#पूर्ण_अगर /* __SXGBE_PLATFORM_H__ */
