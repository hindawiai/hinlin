<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Cadence USBSS and USBSSP DRD Driver - Gadget Export APIs.
 *
 * Copyright (C) 2017 NXP
 * Copyright (C) 2017-2018 NXP
 *
 * Authors: Peter Chen <peter.chen@nxp.com>
 */
#अगर_अघोषित __LINUX_CDNS3_GADGET_EXPORT
#घोषणा __LINUX_CDNS3_GADGET_EXPORT

#अगर IS_ENABLED(CONFIG_USB_CDNSP_GADGET)

पूर्णांक cdnsp_gadget_init(काष्ठा cdns *cdns);
#अन्यथा

अटल अंतरभूत पूर्णांक cdnsp_gadget_init(काष्ठा cdns *cdns)
अणु
	वापस -ENXIO;
पूर्ण

#पूर्ण_अगर /* CONFIG_USB_CDNSP_GADGET */

#अगर IS_ENABLED(CONFIG_USB_CDNS3_GADGET)

पूर्णांक cdns3_gadget_init(काष्ठा cdns *cdns);
#अन्यथा

अटल अंतरभूत पूर्णांक cdns3_gadget_init(काष्ठा cdns *cdns)
अणु
	वापस -ENXIO;
पूर्ण

#पूर्ण_अगर /* CONFIG_USB_CDNS3_GADGET */

#पूर्ण_अगर /* __LINUX_CDNS3_GADGET_EXPORT */
