<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2011 Marvell International Ltd. All rights reserved.
 */

#अगर_अघोषित __MV_PLATFORM_USB_H
#घोषणा __MV_PLATFORM_USB_H

क्रमागत अणु
	MV_USB_MODE_OTG,
	MV_USB_MODE_HOST,
पूर्ण;

क्रमागत अणु
	VBUS_LOW	= 0,
	VBUS_HIGH	= 1 << 0,
पूर्ण;

काष्ठा mv_usb_adकरोn_irq अणु
	अचिन्हित पूर्णांक	irq;
	पूर्णांक		(*poll)(व्योम);
पूर्ण;

काष्ठा mv_usb_platक्रमm_data अणु
	काष्ठा mv_usb_adकरोn_irq	*id;	/* Only valid क्रम OTG. ID pin change*/
	काष्ठा mv_usb_adकरोn_irq	*vbus;	/* valid क्रम OTG/UDC. VBUS change*/

	/* only valid क्रम HCD. OTG or Host only*/
	अचिन्हित पूर्णांक		mode;

	/* This flag is used क्रम that needs id pin checked by otg */
	अचिन्हित पूर्णांक    disable_otg_घड़ी_gating:1;
	/* Force a_bus_req to be निश्चितed */
	 अचिन्हित पूर्णांक    otg_क्रमce_a_bus_req:1;

	पूर्णांक	(*phy_init)(व्योम __iomem *regbase);
	व्योम	(*phy_deinit)(व्योम __iomem *regbase);
	पूर्णांक	(*set_vbus)(अचिन्हित पूर्णांक vbus);
पूर्ण;
#पूर्ण_अगर
