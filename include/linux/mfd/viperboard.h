<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  include/linux/mfd/viperboard.h
 *
 *  Nano River Technologies viperboard definitions
 *
 *  (C) 2012 by Lemonage GmbH
 *  Author: Lars Poeschel <poeschel@lemonage.de>
 *  All rights reserved.
 */

#अगर_अघोषित __MFD_VIPERBOARD_H__
#घोषणा __MFD_VIPERBOARD_H__

#समावेश <linux/types.h>
#समावेश <linux/usb.h>

#घोषणा VPRBRD_EP_OUT               0x02
#घोषणा VPRBRD_EP_IN                0x86

#घोषणा VPRBRD_I2C_MSG_LEN          512 /* max length of a msg on USB level */

#घोषणा VPRBRD_I2C_FREQ_6MHZ        1                        /*   6 MBit/s */
#घोषणा VPRBRD_I2C_FREQ_3MHZ        2                        /*   3 MBit/s */
#घोषणा VPRBRD_I2C_FREQ_1MHZ        3                        /*   1 MBit/s */
#घोषणा VPRBRD_I2C_FREQ_FAST        4                        /* 400 kbit/s */
#घोषणा VPRBRD_I2C_FREQ_400KHZ      VPRBRD_I2C_FREQ_FAST
#घोषणा VPRBRD_I2C_FREQ_200KHZ      5                        /* 200 kbit/s */
#घोषणा VPRBRD_I2C_FREQ_STD         6                        /* 100 kbit/s */
#घोषणा VPRBRD_I2C_FREQ_100KHZ      VPRBRD_I2C_FREQ_STD
#घोषणा VPRBRD_I2C_FREQ_10KHZ       7                        /*  10 kbit/s */

#घोषणा VPRBRD_I2C_CMD_WRITE        0x00
#घोषणा VPRBRD_I2C_CMD_READ         0x01
#घोषणा VPRBRD_I2C_CMD_ADDR         0x02

#घोषणा VPRBRD_USB_TYPE_OUT	    0x40
#घोषणा VPRBRD_USB_TYPE_IN	    0xc0
#घोषणा VPRBRD_USB_TIMEOUT_MS       100
#घोषणा VPRBRD_USB_REQUEST_I2C_FREQ 0xe6
#घोषणा VPRBRD_USB_REQUEST_I2C      0xe9
#घोषणा VPRBRD_USB_REQUEST_MAJOR    0xea
#घोषणा VPRBRD_USB_REQUEST_MINOR    0xeb
#घोषणा VPRBRD_USB_REQUEST_ADC      0xec
#घोषणा VPRBRD_USB_REQUEST_GPIOA    0xed
#घोषणा VPRBRD_USB_REQUEST_GPIOB    0xdd

काष्ठा vprbrd_i2c_ग_लिखो_hdr अणु
	u8 cmd;
	u16 addr;
	u8 len1;
	u8 len2;
	u8 last;
	u8 chan;
	u16 spi;
पूर्ण __packed;

काष्ठा vprbrd_i2c_पढ़ो_hdr अणु
	u8 cmd;
	u16 addr;
	u8 len0;
	u8 len1;
	u8 len2;
	u8 len3;
	u8 len4;
	u8 len5;
	u16 tf1;                        /* transfer 1 length */
	u16 tf2;                        /* transfer 2 length */
पूर्ण __packed;

काष्ठा vprbrd_i2c_status अणु
	u8 unknown[11];
	u8 status;
पूर्ण __packed;

काष्ठा vprbrd_i2c_ग_लिखो_msg अणु
	काष्ठा vprbrd_i2c_ग_लिखो_hdr header;
	u8 data[VPRBRD_I2C_MSG_LEN
		- माप(काष्ठा vprbrd_i2c_ग_लिखो_hdr)];
पूर्ण __packed;

काष्ठा vprbrd_i2c_पढ़ो_msg अणु
	काष्ठा vprbrd_i2c_पढ़ो_hdr header;
	u8 data[VPRBRD_I2C_MSG_LEN
		- माप(काष्ठा vprbrd_i2c_पढ़ो_hdr)];
पूर्ण __packed;

काष्ठा vprbrd_i2c_addr_msg अणु
	u8 cmd;
	u8 addr;
	u8 unknown1;
	u16 len;
	u8 unknown2;
	u8 unknown3;
पूर्ण __packed;

/* Structure to hold all device specअगरic stuff */
काष्ठा vprbrd अणु
	काष्ठा usb_device *usb_dev; /* the usb device क्रम this device */
	काष्ठा mutex lock;
	u8 buf[माप(काष्ठा vprbrd_i2c_ग_लिखो_msg)];
	काष्ठा platक्रमm_device pdev;
पूर्ण;

#पूर्ण_अगर /* __MFD_VIPERBOARD_H__ */
