<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * TI j721e Cadence MHDP8546 DP wrapper
 *
 * Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/
 * Author: Jyri Sarha <jsarha@ti.com>
 */

#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>

#समावेश "cdns-mhdp8546-j721e.h"

#घोषणा	REVISION			0x00
#घोषणा	DPTX_IPCFG			0x04
#घोषणा	ECC_MEM_CFG			0x08
#घोषणा	DPTX_DSC_CFG			0x0c
#घोषणा	DPTX_SRC_CFG			0x10
#घोषणा	DPTX_VIF_SECURE_MODE_CFG	0x14
#घोषणा	DPTX_VIF_CONN_STATUS		0x18
#घोषणा	PHY_CLK_STATUS			0x1c

#घोषणा DPTX_SRC_AIF_EN			BIT(16)
#घोषणा DPTX_SRC_VIF_3_IN30B		BIT(11)
#घोषणा DPTX_SRC_VIF_2_IN30B		BIT(10)
#घोषणा DPTX_SRC_VIF_1_IN30B		BIT(9)
#घोषणा DPTX_SRC_VIF_0_IN30B		BIT(8)
#घोषणा DPTX_SRC_VIF_3_SEL_DPI5		BIT(7)
#घोषणा DPTX_SRC_VIF_3_SEL_DPI3		0
#घोषणा DPTX_SRC_VIF_2_SEL_DPI4		BIT(6)
#घोषणा DPTX_SRC_VIF_2_SEL_DPI2		0
#घोषणा DPTX_SRC_VIF_1_SEL_DPI3		BIT(5)
#घोषणा DPTX_SRC_VIF_1_SEL_DPI1		0
#घोषणा DPTX_SRC_VIF_0_SEL_DPI2		BIT(4)
#घोषणा DPTX_SRC_VIF_0_SEL_DPI0		0
#घोषणा DPTX_SRC_VIF_3_EN		BIT(3)
#घोषणा DPTX_SRC_VIF_2_EN		BIT(2)
#घोषणा DPTX_SRC_VIF_1_EN		BIT(1)
#घोषणा DPTX_SRC_VIF_0_EN		BIT(0)

/* TODO turn DPTX_IPCFG fw_mem_clk_en at pm_runसमय_suspend. */

अटल पूर्णांक cdns_mhdp_j721e_init(काष्ठा cdns_mhdp_device *mhdp)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(mhdp->dev);

	mhdp->j721e_regs = devm_platक्रमm_ioremap_resource(pdev, 1);
	वापस PTR_ERR_OR_ZERO(mhdp->j721e_regs);
पूर्ण

अटल व्योम cdns_mhdp_j721e_enable(काष्ठा cdns_mhdp_device *mhdp)
अणु
	/*
	 * Enable VIF_0 and select DPI2 as its input. DSS0 DPI0 is connected
	 * to eDP DPI2. This is the only supported SST configuration on
	 * J721E.
	 */
	ग_लिखोl(DPTX_SRC_VIF_0_EN | DPTX_SRC_VIF_0_SEL_DPI2,
	       mhdp->j721e_regs + DPTX_SRC_CFG);
पूर्ण

अटल व्योम cdns_mhdp_j721e_disable(काष्ठा cdns_mhdp_device *mhdp)
अणु
	/* Put everything to शेषs  */
	ग_लिखोl(0, mhdp->j721e_regs + DPTX_DSC_CFG);
पूर्ण

स्थिर काष्ठा mhdp_platक्रमm_ops mhdp_ti_j721e_ops = अणु
	.init = cdns_mhdp_j721e_init,
	.enable = cdns_mhdp_j721e_enable,
	.disable = cdns_mhdp_j721e_disable,
पूर्ण;

स्थिर काष्ठा drm_bridge_timings mhdp_ti_j721e_bridge_timings = अणु
	.input_bus_flags = DRM_BUS_FLAG_PIXDATA_SAMPLE_NEGEDGE |
			   DRM_BUS_FLAG_SYNC_SAMPLE_NEGEDGE |
			   DRM_BUS_FLAG_DE_HIGH,
पूर्ण;
