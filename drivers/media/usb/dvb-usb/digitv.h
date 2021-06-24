<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _DVB_USB_DIGITV_H_
#घोषणा _DVB_USB_DIGITV_H_

#घोषणा DVB_USB_LOG_PREFIX "digitv"
#समावेश "dvb-usb.h"

काष्ठा digitv_state अणु
	पूर्णांक is_nxt6000;

	अचिन्हित अक्षर sndbuf[7];
	अचिन्हित अक्षर rcvbuf[7];
पूर्ण;

/* protocol (from usblogging and the SDK:
 *
 * Always 7 bytes bulk message(s) क्रम controlling
 *
 * First byte describes the command. Reads are 2 consecutive transfer (as always).
 *
 * General काष्ठाure:
 *
 * ग_लिखो or first message of a पढ़ो:
 * <cmdbyte> VV <len> B0 B1 B2 B3
 *
 * second message of a पढ़ो
 * <cmdbyte> VV <len> R0 R1 R2 R3
 *
 * whereas 0 < len <= 4
 *
 * I2C address is stored somewhere inside the device.
 *
 * 0x01 पढ़ो from EEPROM
 *  VV = offset; B* = 0; R* = value(s)
 *
 * 0x02 पढ़ो रेजिस्टर of the COFDM
 *  VV = रेजिस्टर; B* = 0; R* = value(s)
 *
 * 0x05 ग_लिखो रेजिस्टर of the COFDM
 *  VV = रेजिस्टर; B* = value(s);
 *
 * 0x06 ग_लिखो to the tuner (only क्रम NXT6000)
 *  VV = 0; B* = PLL data; len = 4;
 *
 * 0x03 पढ़ो remote control
 *  VV = 0; B* = 0; len = 4; R* = key
 *
 * 0x07 ग_लिखो to the remote (करोn't know why one should this, resetting ?)
 *  VV = 0; B* = key; len = 4;
 *
 * 0x08 ग_लिखो remote type
 *  VV = 0; B[0] = 0x01, len = 4
 *
 * 0x09 ग_लिखो device init
 *  TODO
 */
#घोषणा USB_READ_EEPROM         1

#घोषणा USB_READ_COFDM          2
#घोषणा USB_WRITE_COFDM         5

#घोषणा USB_WRITE_TUNER         6

#घोषणा USB_READ_REMOTE         3
#घोषणा USB_WRITE_REMOTE        7
#घोषणा USB_WRITE_REMOTE_TYPE   8

#घोषणा USB_DEV_INIT            9

#पूर्ण_अगर
