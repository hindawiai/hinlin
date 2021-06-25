<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_USB_NOP_XCEIV_H
#घोषणा __LINUX_USB_NOP_XCEIV_H

#समावेश <linux/usb/otg.h>

#अगर IS_ENABLED(CONFIG_NOP_USB_XCEIV)
/* someबार transceivers are accessed only through e.g. ULPI */
बाह्य काष्ठा platक्रमm_device *usb_phy_generic_रेजिस्टर(व्योम);
बाह्य व्योम usb_phy_generic_unरेजिस्टर(काष्ठा platक्रमm_device *);
#अन्यथा
अटल अंतरभूत काष्ठा platक्रमm_device *usb_phy_generic_रेजिस्टर(व्योम)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम usb_phy_generic_unरेजिस्टर(काष्ठा platक्रमm_device *pdev)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __LINUX_USB_NOP_XCEIV_H */
