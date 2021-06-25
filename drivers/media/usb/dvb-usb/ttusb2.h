<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* DVB USB compliant linux driver क्रम Technotrend DVB USB boxes and clones
 * (e.g. Pinnacle 400e DVB-S USB2.0).
 *
 * Copyright (c) 2002 Holger Waechtler <holger@convergence.de>
 * Copyright (c) 2003 Felix Domke <पंचांगbinc@elitedvb.net>
 * Copyright (C) 2005-6 Patrick Boettcher <pb@linuxtv.de>
 *
 * see Documentation/driver-api/media/drivers/dvb-usb.rst क्रम more inक्रमmation
 */
#अगर_अघोषित _DVB_USB_TTUSB2_H_
#घोषणा _DVB_USB_TTUSB2_H_

/* TTUSB protocol
 *
 * always to messages (out/in)
 * out message:
 * 0xaa <id> <cmdbyte> <datalen> <data...>
 *
 * in message (complete block is always 0x40 bytes दीर्घ)
 * 0x55 <id> <cmdbyte> <datalen> <data...>
 *
 * id is incremented क्रम each transaction
 */

#घोषणा CMD_DSP_DOWNLOAD    0x13
/* out data: <byte>[28]
 * last block must be empty */

#घोषणा CMD_DSP_BOOT        0x14
/* out data: nothing */

#घोषणा CMD_POWER           0x15
/* out data: <on=1/off=0> */

#घोषणा CMD_LNB             0x16
/* out data: <घातer=1> <18V=0,13V=1> <tone> <??=1> <??=1> */

#घोषणा CMD_GET_VERSION     0x17
/* in  data: <version_byte>[5] */

#घोषणा CMD_DISEQC          0x18
/* out data: <master=0xff/burst=??> <cmdlen> <cmdbytes>[cmdlen] */

#घोषणा CMD_PID_ENABLE      0x22
/* out data: <index> <type: ts=1/sec=2> <pid msb> <pid lsb> */

#घोषणा CMD_PID_DISABLE     0x23
/* out data: <index> */

#घोषणा CMD_FILTER_ENABLE   0x24
/* out data: <index> <pid_idx> <filter>[12] <mask>[12] */

#घोषणा CMD_FILTER_DISABLE  0x25
/* out data: <index> */

#घोषणा CMD_GET_DSP_VERSION 0x26
/* in  data: <version_byte>[28] */

#घोषणा CMD_I2C_XFER        0x31
/* out data: <addr << 1> <sndlen> <rcvlen> <data>[sndlen]
 * in  data: <addr << 1> <sndlen> <rcvlen> <data>[rcvlen] */

#घोषणा CMD_I2C_BITRATE     0x32
/* out data: <शेष=0> */

#पूर्ण_अगर
