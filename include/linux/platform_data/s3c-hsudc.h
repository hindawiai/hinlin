<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * S3C24XX USB 2.0 High-speed USB controller gadget driver
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * The S3C24XX USB 2.0 high-speed USB controller supports upto 9 endpoपूर्णांकs.
 * Each endpoपूर्णांक can be configured as either in or out endpoपूर्णांक. Endpoपूर्णांकs
 * can be configured क्रम Bulk or Interrupt transfer mode.
*/

#अगर_अघोषित __LINUX_USB_S3C_HSUDC_H
#घोषणा __LINUX_USB_S3C_HSUDC_H

/**
 * s3c24xx_hsudc_platdata - Platक्रमm data क्रम USB High-Speed gadget controller.
 * @epnum: Number of endpoपूर्णांकs to be instantiated by the controller driver.
 * @gpio_init: Platक्रमm specअगरic USB related GPIO initialization.
 * @gpio_uninit: Platक्रमm specअगरic USB releted GPIO uninitialzation.
 *
 * Representation of platक्रमm data क्रम the S3C24XX USB 2.0 High Speed gadget
 * controllers.
 */
काष्ठा s3c24xx_hsudc_platdata अणु
	अचिन्हित पूर्णांक	epnum;
	व्योम		(*gpio_init)(व्योम);
	व्योम		(*gpio_uninit)(व्योम);
	व्योम		(*phy_init)(व्योम);
	व्योम		(*phy_uninit)(व्योम);
पूर्ण;

#पूर्ण_अगर	/* __LINUX_USB_S3C_HSUDC_H */
