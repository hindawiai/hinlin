<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _DVB_USB_VP7021_H_
#घोषणा _DVB_USB_VP7021_H_

#घोषणा DVB_USB_LOG_PREFIX "vp702x"
#समावेश "dvb-usb.h"

बाह्य पूर्णांक dvb_usb_vp702x_debug;
#घोषणा deb_info(args...) dprपूर्णांकk(dvb_usb_vp702x_debug,0x01,args)
#घोषणा deb_xfer(args...) dprपूर्णांकk(dvb_usb_vp702x_debug,0x02,args)
#घोषणा deb_rc(args...)   dprपूर्णांकk(dvb_usb_vp702x_debug,0x04,args)
#घोषणा deb_fe(args...)   dprपूर्णांकk(dvb_usb_vp702x_debug,0x08,args)

/* commands are पढ़ो and written with USB control messages */

/* consecutive पढ़ो/ग_लिखो operation */
#घोषणा REQUEST_OUT		0xB2
#घोषणा REQUEST_IN		0xB3

/* the out-buffer of these consecutive operations contain sub-commands when b[0] = 0
 * request: 0xB2; i: 0; v: 0; b[0] = 0, b[1] = subcmd, additional buffer
 * the वापसing buffer looks as follows
 * request: 0xB3; i: 0; v: 0; b[0] = 0xB3, additional buffer */

#घोषणा GET_TUNER_STATUS	0x05
/* additional in buffer:
 * 0   1   2    3              4   5   6               7       8
 * N/A N/A 0x05 संकेत-quality N/A N/A संकेत-strength lock==0 N/A */

#घोषणा GET_SYSTEM_STRING	0x06
/* additional in buffer:
 * 0   1   2   3   4   5   6   7   8
 * N/A 'U' 'S' 'B' '7' '0' '2' 'X' N/A */

#घोषणा SET_DISEQC_CMD		0x08
/* additional out buffer:
 * 0    1  2  3  4
 * len  X1 X2 X3 X4
 * additional in buffer:
 * 0   1 2
 * N/A 0 0   b[1] == b[2] == 0 -> success, failure otherwise */

#घोषणा SET_LNB_POWER		0x09
/* additional out buffer:
 * 0    1    2
 * 0x00 0xff 1 = on, 0 = off
 * additional in buffer:
 * 0   1 2
 * N/A 0 0   b[1] == b[2] == 0 -> success failure otherwise */

#घोषणा GET_MAC_ADDRESS		0x0A
/* #घोषणा GET_MAC_ADDRESS   0x0B */
/* additional in buffer:
 * 0   1   2            3    4    5    6    7    8
 * N/A N/A 0x0A or 0x0B MAC0 MAC1 MAC2 MAC3 MAC4 MAC5 */

#घोषणा SET_PID_FILTER		0x11
/* additional in buffer:
 * 0        1        ... 14       15       16
 * PID0_MSB PID0_LSB ... PID7_MSB PID7_LSB PID_active (bits) */

/* request: 0xB2; i: 0; v: 0;
 * b[0] != 0 -> tune and lock a channel
 * 0     1     2       3      4      5      6    7
 * freq0 freq1 भागstep srate0 srate1 srate2 flag chksum
 */

/* one direction requests */
#घोषणा READ_REMOTE_REQ		0xB4
/* IN  i: 0; v: 0; b[0] == request, b[1] == key */

#घोषणा READ_PID_NUMBER_REQ	0xB5
/* IN  i: 0; v: 0; b[0] == request, b[1] == 0, b[2] = pid number */

#घोषणा WRITE_EEPROM_REQ	0xB6
/* OUT i: offset; v: value to ग_लिखो; no extra buffer */

#घोषणा READ_EEPROM_REQ		0xB7
/* IN  i: bufferlen; v: offset; buffer with bufferlen bytes */

#घोषणा READ_STATUS		0xB8
/* IN  i: 0; v: 0; bufferlen 10 */

#घोषणा READ_TUNER_REG_REQ	0xB9
/* IN  i: 0; v: रेजिस्टर; b[0] = value */

#घोषणा READ_FX2_REG_REQ	0xBA
/* IN  i: offset; v: 0; b[0] = value */

#घोषणा WRITE_FX2_REG_REQ	0xBB
/* OUT i: offset; v: value to ग_लिखो; 1 byte extra buffer */

#घोषणा SET_TUNER_POWER_REQ	0xBC
/* IN  i: 0 = घातer off, 1 = घातer on */

#घोषणा WRITE_TUNER_REG_REQ	0xBD
/* IN  i: रेजिस्टर, v: value to ग_लिखो, no extra buffer */

#घोषणा RESET_TUNER		0xBE
/* IN  i: 0, v: 0, no extra buffer */

काष्ठा vp702x_device_state अणु
	काष्ठा mutex buf_mutex;
	पूर्णांक buf_len;
	u8 *buf;
पूर्ण;


बाह्य काष्ठा dvb_frontend * vp702x_fe_attach(काष्ठा dvb_usb_device *d);

बाह्य पूर्णांक vp702x_usb_inout_op(काष्ठा dvb_usb_device *d, u8 *o, पूर्णांक olen, u8 *i, पूर्णांक ilen, पूर्णांक msec);
बाह्य पूर्णांक vp702x_usb_in_op(काष्ठा dvb_usb_device *d, u8 req, u16 value, u16 index, u8 *b, पूर्णांक blen);

#पूर्ण_अगर
