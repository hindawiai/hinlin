<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* include/linux/platक्रमm_data/s3c-hsotg.h
 *
 * Copyright 2008 Openmoko, Inc.
 * Copyright 2008 Simtec Electronics
 *      Ben Dooks <ben@simtec.co.uk>
 *      http://armlinux.simtec.co.uk/
 *
 * S3C USB2.0 High-speed / OtG platक्रमm inक्रमmation
*/

#अगर_अघोषित __LINUX_USB_S3C_HSOTG_H
#घोषणा __LINUX_USB_S3C_HSOTG_H

काष्ठा platक्रमm_device;

क्रमागत dwc2_hsotg_dmamode अणु
	S3C_HSOTG_DMA_NONE,	/* करो not use DMA at-all */
	S3C_HSOTG_DMA_ONLY,	/* always use DMA */
	S3C_HSOTG_DMA_DRV,	/* DMA is chosen by driver */
पूर्ण;

/**
 * काष्ठा dwc2_hsotg_plat - platक्रमm data क्रम high-speed otg/udc
 * @dma: Whether to use DMA or not.
 * @is_osc: The घड़ी source is an oscillator, not a crystal
 */
काष्ठा dwc2_hsotg_plat अणु
	क्रमागत dwc2_hsotg_dmamode	dma;
	अचिन्हित पूर्णांक		is_osc:1;
	पूर्णांक                     phy_type;

	पूर्णांक (*phy_init)(काष्ठा platक्रमm_device *pdev, पूर्णांक type);
	पूर्णांक (*phy_निकास)(काष्ठा platक्रमm_device *pdev, पूर्णांक type);
पूर्ण;

बाह्य व्योम dwc2_hsotg_set_platdata(काष्ठा dwc2_hsotg_plat *pd);

#पूर्ण_अगर /* __LINUX_USB_S3C_HSOTG_H */
