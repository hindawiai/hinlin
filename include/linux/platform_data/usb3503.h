<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __USB3503_H__
#घोषणा __USB3503_H__

#घोषणा USB3503_I2C_NAME	"usb3503"

#घोषणा USB3503_OFF_PORT1	(1 << 1)
#घोषणा USB3503_OFF_PORT2	(1 << 2)
#घोषणा USB3503_OFF_PORT3	(1 << 3)

क्रमागत usb3503_mode अणु
	USB3503_MODE_UNKNOWN,
	USB3503_MODE_HUB,
	USB3503_MODE_STANDBY,
पूर्ण;

काष्ठा usb3503_platक्रमm_data अणु
	क्रमागत usb3503_mode	initial_mode;
	u8	port_off_mask;
पूर्ण;

#पूर्ण_अगर
