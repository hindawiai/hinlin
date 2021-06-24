<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * TerraTec Cinergy T2/qanu USB2 DVB-T adapter.
 *
 * Copyright (C) 2007 Tomi Orava (tomimo@ncircle.nullnet.fi)
 *
 * Based on the dvb-usb-framework code and the
 * original Terratec Cinergy T2 driver by:
 *
 * Copyright (C) 2004 Daniel Mack <daniel@qanu.de> and
 *                  Holger Waechtler <holger@qanu.de>
 *
 *  Protocol Spec published on http://qanu.de/specs/terratec_cinergyT2.pdf
 */

#अगर_अघोषित _DVB_USB_CINERGYT2_H_
#घोषणा _DVB_USB_CINERGYT2_H_

#समावेश <linux/usb/input.h>

#घोषणा DVB_USB_LOG_PREFIX "cinergyT2"
#समावेश "dvb-usb.h"

#घोषणा DRIVER_NAME "TerraTec/qanu USB2.0 Highspeed DVB-T Receiver"

बाह्य पूर्णांक dvb_usb_cinergyt2_debug;

#घोषणा deb_info(args...)  dprपूर्णांकk(dvb_usb_cinergyt2_debug,  0x001, args)
#घोषणा deb_xfer(args...)  dprपूर्णांकk(dvb_usb_cinergyt2_debug,  0x002, args)
#घोषणा deb_pll(args...)   dprपूर्णांकk(dvb_usb_cinergyt2_debug,  0x004, args)
#घोषणा deb_ts(args...)    dprपूर्णांकk(dvb_usb_cinergyt2_debug,  0x008, args)
#घोषणा deb_err(args...)   dprपूर्णांकk(dvb_usb_cinergyt2_debug,  0x010, args)
#घोषणा deb_rc(args...)    dprपूर्णांकk(dvb_usb_cinergyt2_debug,  0x020, args)
#घोषणा deb_fw(args...)    dprपूर्णांकk(dvb_usb_cinergyt2_debug,  0x040, args)
#घोषणा deb_mem(args...)   dprपूर्णांकk(dvb_usb_cinergyt2_debug,  0x080, args)
#घोषणा deb_uxfer(args...) dprपूर्णांकk(dvb_usb_cinergyt2_debug,  0x100, args)



क्रमागत cinergyt2_ep1_cmd अणु
	CINERGYT2_EP1_PID_TABLE_RESET		= 0x01,
	CINERGYT2_EP1_PID_SETUP			= 0x02,
	CINERGYT2_EP1_CONTROL_STREAM_TRANSFER	= 0x03,
	CINERGYT2_EP1_SET_TUNER_PARAMETERS	= 0x04,
	CINERGYT2_EP1_GET_TUNER_STATUS		= 0x05,
	CINERGYT2_EP1_START_SCAN		= 0x06,
	CINERGYT2_EP1_CONTINUE_SCAN		= 0x07,
	CINERGYT2_EP1_GET_RC_EVENTS		= 0x08,
	CINERGYT2_EP1_SLEEP_MODE		= 0x09,
	CINERGYT2_EP1_GET_FIRMWARE_VERSION	= 0x0A
पूर्ण;


काष्ठा dvbt_get_status_msg अणु
	uपूर्णांक32_t freq;
	uपूर्णांक8_t bandwidth;
	uपूर्णांक16_t tps;
	uपूर्णांक8_t flags;
	__le16 gain;
	uपूर्णांक8_t snr;
	__le32 viterbi_error_rate;
	uपूर्णांक32_t rs_error_rate;
	__le32 uncorrected_block_count;
	uपूर्णांक8_t lock_bits;
	uपूर्णांक8_t prev_lock_bits;
पूर्ण __attribute__((packed));


काष्ठा dvbt_set_parameters_msg अणु
	uपूर्णांक8_t cmd;
	__le32 freq;
	uपूर्णांक8_t bandwidth;
	__le16 tps;
	uपूर्णांक8_t flags;
पूर्ण __attribute__((packed));


बाह्य काष्ठा dvb_frontend *cinergyt2_fe_attach(काष्ठा dvb_usb_device *d);

#पूर्ण_अगर /* _DVB_USB_CINERGYT2_H_ */

