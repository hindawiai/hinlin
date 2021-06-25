<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* DVB USB compliant Linux driver क्रम the
 *  - GENPIX 8pks/qpsk/DCII USB2.0 DVB-S module
 *
 * Copyright (C) 2006 Alan Nisota (alannisota@gmail.com)
 * Copyright (C) 2006,2007 Alan Nisota (alannisota@gmail.com)
 *
 * Thanks to GENPIX क्रम the sample code used to implement this module.
 *
 * This module is based off the vp7045 and vp702x modules
 *
 * see Documentation/driver-api/media/drivers/dvb-usb.rst क्रम more inक्रमmation
 */
#अगर_अघोषित _DVB_USB_GP8PSK_H_
#घोषणा _DVB_USB_GP8PSK_H_

#घोषणा DVB_USB_LOG_PREFIX "gp8psk"
#समावेश "dvb-usb.h"

बाह्य पूर्णांक dvb_usb_gp8psk_debug;
#घोषणा deb_info(args...) dprपूर्णांकk(dvb_usb_gp8psk_debug,0x01,args)
#घोषणा deb_xfer(args...) dprपूर्णांकk(dvb_usb_gp8psk_debug,0x02,args)
#घोषणा deb_rc(args...)   dprपूर्णांकk(dvb_usb_gp8psk_debug,0x04,args)

#घोषणा GET_USB_SPEED                     0x07

#घोषणा RESET_FX2                         0x13

#घोषणा FW_VERSION_READ                   0x0B
#घोषणा VENDOR_STRING_READ                0x0C
#घोषणा PRODUCT_STRING_READ               0x0D
#घोषणा FW_BCD_VERSION_READ               0x14

#पूर्ण_अगर
