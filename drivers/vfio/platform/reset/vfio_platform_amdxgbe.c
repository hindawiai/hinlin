<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VFIO platक्रमm driver specialized क्रम AMD xgbe reset
 * reset code is inherited from AMD xgbe native driver
 *
 * Copyright (c) 2015 Linaro Ltd.
 *              www.linaro.org
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <uapi/linux/mdपन.स>
#समावेश <linux/delay.h>

#समावेश "../vfio_platform_private.h"

#घोषणा DMA_MR			0x3000
#घोषणा MAC_VR			0x0110
#घोषणा DMA_ISR			0x3008
#घोषणा MAC_ISR			0x00b0
#घोषणा PCS_MMD_SELECT		0xff
#घोषणा MDIO_AN_INT		0x8002
#घोषणा MDIO_AN_INTMASK		0x8001

अटल अचिन्हित पूर्णांक xmdio_पढ़ो(व्योम __iomem *ioaddr, अचिन्हित पूर्णांक mmd,
			       अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित पूर्णांक mmd_address, value;

	mmd_address = (mmd << 16) | ((reg) & 0xffff);
	ioग_लिखो32(mmd_address >> 8, ioaddr + (PCS_MMD_SELECT << 2));
	value = ioपढ़ो32(ioaddr + ((mmd_address & 0xff) << 2));
	वापस value;
पूर्ण

अटल व्योम xmdio_ग_लिखो(व्योम __iomem *ioaddr, अचिन्हित पूर्णांक mmd,
			अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक value)
अणु
	अचिन्हित पूर्णांक mmd_address;

	mmd_address = (mmd << 16) | ((reg) & 0xffff);
	ioग_लिखो32(mmd_address >> 8, ioaddr + (PCS_MMD_SELECT << 2));
	ioग_लिखो32(value, ioaddr + ((mmd_address & 0xff) << 2));
पूर्ण

अटल पूर्णांक vfio_platक्रमm_amdxgbe_reset(काष्ठा vfio_platक्रमm_device *vdev)
अणु
	काष्ठा vfio_platक्रमm_region *xgmac_regs = &vdev->regions[0];
	काष्ठा vfio_platक्रमm_region *xpcs_regs = &vdev->regions[1];
	u32 dma_mr_value, pcs_value, value;
	अचिन्हित पूर्णांक count;

	अगर (!xgmac_regs->ioaddr) अणु
		xgmac_regs->ioaddr =
			ioremap(xgmac_regs->addr, xgmac_regs->size);
		अगर (!xgmac_regs->ioaddr)
			वापस -ENOMEM;
	पूर्ण
	अगर (!xpcs_regs->ioaddr) अणु
		xpcs_regs->ioaddr =
			ioremap(xpcs_regs->addr, xpcs_regs->size);
		अगर (!xpcs_regs->ioaddr)
			वापस -ENOMEM;
	पूर्ण

	/* reset the PHY through MDIO*/
	pcs_value = xmdio_पढ़ो(xpcs_regs->ioaddr, MDIO_MMD_PCS, MDIO_CTRL1);
	pcs_value |= MDIO_CTRL1_RESET;
	xmdio_ग_लिखो(xpcs_regs->ioaddr, MDIO_MMD_PCS, MDIO_CTRL1, pcs_value);

	count = 50;
	करो अणु
		msleep(20);
		pcs_value = xmdio_पढ़ो(xpcs_regs->ioaddr, MDIO_MMD_PCS,
					MDIO_CTRL1);
	पूर्ण जबतक ((pcs_value & MDIO_CTRL1_RESET) && --count);

	अगर (pcs_value & MDIO_CTRL1_RESET)
		dev_warn(vdev->device, "%s: XGBE PHY reset timeout\n",
			 __func__);

	/* disable स्वतः-negotiation */
	value = xmdio_पढ़ो(xpcs_regs->ioaddr, MDIO_MMD_AN, MDIO_CTRL1);
	value &= ~MDIO_AN_CTRL1_ENABLE;
	xmdio_ग_लिखो(xpcs_regs->ioaddr, MDIO_MMD_AN, MDIO_CTRL1, value);

	/* disable AN IRQ */
	xmdio_ग_लिखो(xpcs_regs->ioaddr, MDIO_MMD_AN, MDIO_AN_INTMASK, 0);

	/* clear AN IRQ */
	xmdio_ग_लिखो(xpcs_regs->ioaddr, MDIO_MMD_AN, MDIO_AN_INT, 0);

	/* MAC software reset */
	dma_mr_value = ioपढ़ो32(xgmac_regs->ioaddr + DMA_MR);
	dma_mr_value |= 0x1;
	ioग_लिखो32(dma_mr_value, xgmac_regs->ioaddr + DMA_MR);

	usleep_range(10, 15);

	count = 2000;
	जबतक (--count && (ioपढ़ो32(xgmac_regs->ioaddr + DMA_MR) & 1))
		usleep_range(500, 600);

	अगर (!count)
		dev_warn(vdev->device, "%s: MAC SW reset failed\n", __func__);

	वापस 0;
पूर्ण

module_vfio_reset_handler("amd,xgbe-seattle-v1a", vfio_platक्रमm_amdxgbe_reset);

MODULE_VERSION("0.1");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Eric Auger <eric.auger@linaro.org>");
MODULE_DESCRIPTION("Reset support for AMD xgbe vfio platform device");
