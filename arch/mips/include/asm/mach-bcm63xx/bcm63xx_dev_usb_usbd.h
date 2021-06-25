<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित BCM63XX_DEV_USB_USBD_H_
#घोषणा BCM63XX_DEV_USB_USBD_H_

/*
 * usb device platक्रमm data
 */
काष्ठा bcm63xx_usbd_platक्रमm_data अणु
	/* board can only support full speed (USB 1.1) */
	पूर्णांक use_fullspeed;

	/* 0-based port index, क्रम chips with >1 USB PHY */
	पूर्णांक port_no;
पूर्ण;

पूर्णांक bcm63xx_usbd_रेजिस्टर(स्थिर काष्ठा bcm63xx_usbd_platक्रमm_data *pd);

#पूर्ण_अगर /* BCM63XX_DEV_USB_USBD_H_ */
