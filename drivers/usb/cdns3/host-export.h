<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Cadence USBSS and USBSSP DRD Driver - Host Export APIs
 *
 * Copyright (C) 2017-2018 NXP
 *
 * Authors: Peter Chen <peter.chen@nxp.com>
 */
#अगर_अघोषित __LINUX_CDNS3_HOST_EXPORT
#घोषणा __LINUX_CDNS3_HOST_EXPORT

#अगर IS_ENABLED(CONFIG_USB_CDNS_HOST)

पूर्णांक cdns_host_init(काष्ठा cdns *cdns);

#अन्यथा

अटल अंतरभूत पूर्णांक cdns_host_init(काष्ठा cdns *cdns)
अणु
	वापस -ENXIO;
पूर्ण

अटल अंतरभूत व्योम cdns_host_निकास(काष्ठा cdns *cdns) अणु पूर्ण

#पूर्ण_अगर /* USB_CDNS_HOST */

#पूर्ण_अगर /* __LINUX_CDNS3_HOST_EXPORT */
