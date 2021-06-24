<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Header file क्रम all dibusb-based-receivers.
 *
 * Copyright (C) 2004-5 Patrick Boettcher (patrick.boettcher@posteo.de)
 *
 * see Documentation/driver-api/media/drivers/dvb-usb.rst क्रम more inक्रमmation
 */
#अगर_अघोषित _DVB_USB_DIBUSB_H_
#घोषणा _DVB_USB_DIBUSB_H_

#अगर_अघोषित DVB_USB_LOG_PREFIX
 #घोषणा DVB_USB_LOG_PREFIX "dibusb"
#पूर्ण_अगर
#समावेश "dvb-usb.h"

#समावेश "dib3000.h"
#समावेश "dib3000mc.h"
#समावेश "mt2060.h"

/*
 * protocol of all dibusb related devices
 */

/*
 * bulk msg to/from endpoपूर्णांक 0x01
 *
 * general काष्ठाure:
 * request_byte parameter_bytes
 */

#घोषणा DIBUSB_REQ_START_READ			0x00
#घोषणा DIBUSB_REQ_START_DEMOD			0x01

/*
 * i2c पढ़ो
 * bulk ग_लिखो: 0x02 ((7bit i2c_addr << 1) | 0x01) रेजिस्टर_bytes length_word
 * bulk पढ़ो:  byte_buffer (length_word bytes)
 */
#घोषणा DIBUSB_REQ_I2C_READ			0x02

/*
 * i2c ग_लिखो
 * bulk ग_लिखो: 0x03 (7bit i2c_addr << 1) रेजिस्टर_bytes value_bytes
 */
#घोषणा DIBUSB_REQ_I2C_WRITE			0x03

/*
 * polling the value of the remote control
 * bulk ग_लिखो: 0x04
 * bulk पढ़ो:  byte_buffer (5 bytes)
 */
#घोषणा DIBUSB_REQ_POLL_REMOTE       0x04

/* additional status values क्रम Hauppauge Remote Control Protocol */
#घोषणा DIBUSB_RC_HAUPPAUGE_KEY_PRESSED	0x01
#घोषणा DIBUSB_RC_HAUPPAUGE_KEY_EMPTY	0x03

/* streaming mode:
 * bulk ग_लिखो: 0x05 mode_byte
 *
 * mode_byte is mostly 0x00
 */
#घोषणा DIBUSB_REQ_SET_STREAMING_MODE	0x05

/* पूर्णांकerrupt the पूर्णांकernal पढ़ो loop, when blocking */
#घोषणा DIBUSB_REQ_INTR_READ			0x06

/* io control
 * 0x07 cmd_byte param_bytes
 *
 * param_bytes can be up to 32 bytes
 *
 * cmd_byte function    parameter name
 * 0x00     घातer mode
 *                      0x00      sleep
 *                      0x01      wakeup
 *
 * 0x01     enable streaming
 * 0x02     disable streaming
 *
 *
 */
#घोषणा DIBUSB_REQ_SET_IOCTL			0x07

/* IOCTL commands */

/* change the घातer mode in firmware */
#घोषणा DIBUSB_IOCTL_CMD_POWER_MODE		0x00
#घोषणा DIBUSB_IOCTL_POWER_SLEEP			0x00
#घोषणा DIBUSB_IOCTL_POWER_WAKEUP			0x01

/* modअगरy streaming of the FX2 */
#घोषणा DIBUSB_IOCTL_CMD_ENABLE_STREAM	0x01
#घोषणा DIBUSB_IOCTL_CMD_DISABLE_STREAM	0x02

/* Max transfer size करोne by I2C transfer functions */
#घोषणा MAX_XFER_SIZE  64

काष्ठा dibusb_state अणु
	काष्ठा dib_fe_xfer_ops ops;
	पूर्णांक mt2060_present;
	u8 tuner_addr;
पूर्ण;

काष्ठा dibusb_device_state अणु
	/* क्रम RC5 remote control */
	पूर्णांक old_toggle;
	पूर्णांक last_repeat_count;
पूर्ण;

बाह्य काष्ठा i2c_algorithm dibusb_i2c_algo;

बाह्य पूर्णांक dibusb_dib3000mc_frontend_attach(काष्ठा dvb_usb_adapter *);
बाह्य पूर्णांक dibusb_dib3000mc_tuner_attach (काष्ठा dvb_usb_adapter *);

बाह्य पूर्णांक dibusb_streaming_ctrl(काष्ठा dvb_usb_adapter *, पूर्णांक);
बाह्य पूर्णांक dibusb_pid_filter(काष्ठा dvb_usb_adapter *, पूर्णांक, u16, पूर्णांक);
बाह्य पूर्णांक dibusb_pid_filter_ctrl(काष्ठा dvb_usb_adapter *, पूर्णांक);
बाह्य पूर्णांक dibusb2_0_streaming_ctrl(काष्ठा dvb_usb_adapter *, पूर्णांक);

बाह्य पूर्णांक dibusb_घातer_ctrl(काष्ठा dvb_usb_device *, पूर्णांक);
बाह्य पूर्णांक dibusb2_0_घातer_ctrl(काष्ठा dvb_usb_device *, पूर्णांक);

#घोषणा DEFAULT_RC_INTERVAL 150
//#घोषणा DEFAULT_RC_INTERVAL 100000

बाह्य काष्ठा rc_map_table rc_map_dibusb_table[];
बाह्य पूर्णांक dibusb_rc_query(काष्ठा dvb_usb_device *, u32 *, पूर्णांक *);
बाह्य पूर्णांक dibusb_पढ़ो_eeprom_byte(काष्ठा dvb_usb_device *, u8, u8 *);

#पूर्ण_अगर
