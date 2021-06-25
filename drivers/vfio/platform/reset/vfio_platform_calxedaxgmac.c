<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VFIO platक्रमm driver specialized क्रम Calxeda xgmac reset
 * reset code is inherited from calxeda xgmac native driver
 *
 * Copyright 2010-2011 Calxeda, Inc.
 * Copyright (c) 2015 Linaro Ltd.
 *              www.linaro.org
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>

#समावेश "../vfio_platform_private.h"

#घोषणा DRIVER_VERSION  "0.1"
#घोषणा DRIVER_AUTHOR   "Eric Auger <eric.auger@linaro.org>"
#घोषणा DRIVER_DESC     "Reset support for Calxeda xgmac vfio platform device"

/* XGMAC Register definitions */
#घोषणा XGMAC_CONTROL           0x00000000      /* MAC Configuration */

/* DMA Control and Status Registers */
#घोषणा XGMAC_DMA_CONTROL       0x00000f18      /* Ctrl (Operational Mode) */
#घोषणा XGMAC_DMA_INTR_ENA      0x00000f1c      /* Interrupt Enable */

/* DMA Control रेजिस्टर defines */
#घोषणा DMA_CONTROL_ST          0x00002000      /* Start/Stop Transmission */
#घोषणा DMA_CONTROL_SR          0x00000002      /* Start/Stop Receive */

/* Common MAC defines */
#घोषणा MAC_ENABLE_TX           0x00000008      /* Transmitter Enable */
#घोषणा MAC_ENABLE_RX           0x00000004      /* Receiver Enable */

अटल अंतरभूत व्योम xgmac_mac_disable(व्योम __iomem *ioaddr)
अणु
	u32 value = पढ़ोl(ioaddr + XGMAC_DMA_CONTROL);

	value &= ~(DMA_CONTROL_ST | DMA_CONTROL_SR);
	ग_लिखोl(value, ioaddr + XGMAC_DMA_CONTROL);

	value = पढ़ोl(ioaddr + XGMAC_CONTROL);
	value &= ~(MAC_ENABLE_TX | MAC_ENABLE_RX);
	ग_लिखोl(value, ioaddr + XGMAC_CONTROL);
पूर्ण

अटल पूर्णांक vfio_platक्रमm_calxedaxgmac_reset(काष्ठा vfio_platक्रमm_device *vdev)
अणु
	काष्ठा vfio_platक्रमm_region *reg = &vdev->regions[0];

	अगर (!reg->ioaddr) अणु
		reg->ioaddr =
			ioremap(reg->addr, reg->size);
		अगर (!reg->ioaddr)
			वापस -ENOMEM;
	पूर्ण

	/* disable IRQ */
	ग_लिखोl(0, reg->ioaddr + XGMAC_DMA_INTR_ENA);

	/* Disable the MAC core */
	xgmac_mac_disable(reg->ioaddr);

	वापस 0;
पूर्ण

module_vfio_reset_handler("calxeda,hb-xgmac", vfio_platक्रमm_calxedaxgmac_reset);

MODULE_VERSION(DRIVER_VERSION);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
