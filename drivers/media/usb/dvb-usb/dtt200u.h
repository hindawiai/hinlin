<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Common header file of Linux driver क्रम the WideView/ Yakumo/ Hama/
 * Typhoon/ Yuan DVB-T USB2.0 receiver.
 *
 * Copyright (C) 2004-5 Patrick Boettcher (patrick.boettcher@posteo.de)
 *
 * see Documentation/driver-api/media/drivers/dvb-usb.rst क्रम more inक्रमmation
 */
#अगर_अघोषित _DVB_USB_DTT200U_H_
#घोषणा _DVB_USB_DTT200U_H_

#घोषणा DVB_USB_LOG_PREFIX "dtt200u"

#समावेश "dvb-usb.h"

बाह्य पूर्णांक dvb_usb_dtt200u_debug;
#घोषणा deb_info(args...) dprपूर्णांकk(dvb_usb_dtt200u_debug,0x01,args)
#घोषणा deb_xfer(args...) dprपूर्णांकk(dvb_usb_dtt200u_debug,0x02,args)

/* guessed protocol description (reverse engineered):
 * पढ़ो
 *  00 - USB type 0x02 क्रम usb2.0, 0x01 क्रम usb1.1
 *  88 - locking 2 bytes (0x80 0x40 == no संकेत, 0x89 0x20 == nice संकेत)
 */

#घोषणा GET_SPEED		0x00
#घोषणा GET_TUNE_STATUS		0x81
#घोषणा GET_RC_CODE		0x84
#घोषणा GET_CONFIGURATION	0x88
#घोषणा GET_AGC			0x89
#घोषणा GET_SNR			0x8a
#घोषणा GET_VIT_ERR_CNT		0x8c
#घोषणा GET_RS_ERR_CNT		0x8d
#घोषणा GET_RS_UNCOR_BLK_CNT	0x8e

/* ग_लिखो
 *  01 - init
 *  02 - frequency (भागided by 250000)
 *  03 - bandwidth
 *  04 - pid table (index pid(7:0) pid(12:8))
 *  05 - reset the pid table
 *  08 - transfer चयन
 */

#घोषणा SET_INIT		0x01
#घोषणा SET_RF_FREQ		0x02
#घोषणा SET_BANDWIDTH		0x03
#घोषणा SET_PID_FILTER		0x04
#घोषणा RESET_PID_FILTER	0x05
#घोषणा SET_STREAMING		0x08

बाह्य काष्ठा dvb_frontend * dtt200u_fe_attach(काष्ठा dvb_usb_device *d);

#पूर्ण_अगर
