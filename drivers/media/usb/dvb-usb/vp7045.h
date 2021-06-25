<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Common header-file of the Linux driver क्रम the TwinhanDTV Alpha/MagicBoxII
 * USB2.0 DVB-T receiver.
 *
 * Copyright (C) 2004-5 Patrick Boettcher (patrick.boettcher@posteo.de)
 *
 * Thanks to Twinhan who kindly provided hardware and inक्रमmation.
 *
 * see Documentation/driver-api/media/drivers/dvb-usb.rst क्रम more inक्रमmation
 */
#अगर_अघोषित _DVB_USB_VP7045_H_
#घोषणा _DVB_USB_VP7045_H_

#घोषणा DVB_USB_LOG_PREFIX "vp7045"
#समावेश "dvb-usb.h"

/* vp7045 commands */

/* Twinhan Venकरोr requests */
#घोषणा TH_COMMAND_IN                     0xC0
#घोषणा TH_COMMAND_OUT                    0xC1

/* command bytes */
#घोषणा TUNER_REG_READ                    0x03
#घोषणा TUNER_REG_WRITE                   0x04

#घोषणा RC_VAL_READ                       0x05
 #घोषणा RC_NO_KEY                        0x44

#घोषणा SET_TUNER_POWER                   0x06
#घोषणा CHECK_TUNER_POWER                 0x12
 #घोषणा Tuner_Power_ON                   1
 #घोषणा Tuner_Power_OFF                  0

#घोषणा GET_USB_SPEED                     0x07

#घोषणा LOCK_TUNER_COMMAND                0x09

#घोषणा TUNER_SIGNAL_READ                 0x0A

/* FX2 eeprom */
#घोषणा SET_EE_VALUE                      0x10
#घोषणा GET_EE_VALUE                      0x11
 #घोषणा FX2_ID_ADDR                      0x00
 #घोषणा VID_MSB_ADDR                     0x02
 #घोषणा VID_LSB_ADDR                     0x01
 #घोषणा PID_MSB_ADDR                     0x04
 #घोषणा PID_LSB_ADDR                     0x03
 #घोषणा MAC_0_ADDR                       0x07
 #घोषणा MAC_1_ADDR                       0x08
 #घोषणा MAC_2_ADDR                       0x09
 #घोषणा MAC_3_ADDR                       0x0a
 #घोषणा MAC_4_ADDR                       0x0b
 #घोषणा MAC_5_ADDR                       0x0c

#घोषणा RESET_FX2                         0x13

#घोषणा FW_VERSION_READ                   0x0B
#घोषणा VENDOR_STRING_READ                0x0C
#घोषणा PRODUCT_STRING_READ               0x0D
#घोषणा FW_BCD_VERSION_READ               0x14

बाह्य काष्ठा dvb_frontend * vp7045_fe_attach(काष्ठा dvb_usb_device *d);
बाह्य पूर्णांक vp7045_usb_op(काष्ठा dvb_usb_device *d, u8 cmd, u8 *out, पूर्णांक outlen, u8 *in, पूर्णांक inlen,पूर्णांक msec);
बाह्य u8 vp7045_पढ़ो_reg(काष्ठा dvb_usb_device *d, u8 reg);

#पूर्ण_अगर
