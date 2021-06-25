<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * File: rf.c
 *
 * Purpose: rf function code
 *
 * Author: Jerry Chen
 *
 * Date: Feb. 19, 2004
 *
 * Functions:
 *      IFRFbWriteEmbedded      - Embedded ग_लिखो RF रेजिस्टर via MAC
 *
 * Revision History:
 *	RobertYu 2005
 *	chester 2008
 *
 */

#समावेश "mac.h"
#समावेश "srom.h"
#समावेश "rf.h"
#समावेश "baseband.h"

#घोषणा BY_AL2230_REG_LEN     23 /* 24bit */
#घोषणा CB_AL2230_INIT_SEQ    15
#घोषणा SWITCH_CHANNEL_DELAY_AL2230 200 /* us */
#घोषणा AL2230_PWR_IDX_LEN    64

#घोषणा BY_AL7230_REG_LEN     23 /* 24bit */
#घोषणा CB_AL7230_INIT_SEQ    16
#घोषणा SWITCH_CHANNEL_DELAY_AL7230 200 /* us */
#घोषणा AL7230_PWR_IDX_LEN    64

अटल स्थिर अचिन्हित दीर्घ dwAL2230InitTable[CB_AL2230_INIT_SEQ] = अणु
	0x03F79000 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x03333100 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x01A00200 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x00FFF300 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x0005A400 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x0F4DC500 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x0805B600 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x0146C700 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x00068800 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x0403B900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x00DBBA00 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x00099B00 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x0BDFFC00 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x00000D00 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x00580F00 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ dwAL2230ChannelTable0[CB_MAX_CHANNEL] = अणु
	0x03F79000 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 1, Tf = 2412MHz */
	0x03F79000 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 2, Tf = 2417MHz */
	0x03E79000 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 3, Tf = 2422MHz */
	0x03E79000 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 4, Tf = 2427MHz */
	0x03F7A000 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 5, Tf = 2432MHz */
	0x03F7A000 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 6, Tf = 2437MHz */
	0x03E7A000 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 7, Tf = 2442MHz */
	0x03E7A000 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 8, Tf = 2447MHz */
	0x03F7B000 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 9, Tf = 2452MHz */
	0x03F7B000 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 10, Tf = 2457MHz */
	0x03E7B000 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 11, Tf = 2462MHz */
	0x03E7B000 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 12, Tf = 2467MHz */
	0x03F7C000 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 13, Tf = 2472MHz */
	0x03E7C000 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW  /* channel = 14, Tf = 2412M */
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ dwAL2230ChannelTable1[CB_MAX_CHANNEL] = अणु
	0x03333100 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 1, Tf = 2412MHz */
	0x0B333100 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 2, Tf = 2417MHz */
	0x03333100 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 3, Tf = 2422MHz */
	0x0B333100 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 4, Tf = 2427MHz */
	0x03333100 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 5, Tf = 2432MHz */
	0x0B333100 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 6, Tf = 2437MHz */
	0x03333100 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 7, Tf = 2442MHz */
	0x0B333100 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 8, Tf = 2447MHz */
	0x03333100 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 9, Tf = 2452MHz */
	0x0B333100 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 10, Tf = 2457MHz */
	0x03333100 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 11, Tf = 2462MHz */
	0x0B333100 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 12, Tf = 2467MHz */
	0x03333100 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 13, Tf = 2472MHz */
	0x06666100 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW  /* channel = 14, Tf = 2412M */
पूर्ण;

अटल अचिन्हित दीर्घ dwAL2230PowerTable[AL2230_PWR_IDX_LEN] = अणु
	0x04040900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04041900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04042900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04043900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04044900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04045900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04046900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04047900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04048900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04049900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x0404A900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x0404B900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x0404C900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x0404D900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x0404E900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x0404F900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04050900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04051900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04052900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04053900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04054900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04055900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04056900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04057900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04058900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04059900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x0405A900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x0405B900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x0405C900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x0405D900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x0405E900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x0405F900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04060900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04061900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04062900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04063900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04064900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04065900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04066900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04067900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04068900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04069900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x0406A900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x0406B900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x0406C900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x0406D900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x0406E900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x0406F900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04070900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04071900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04072900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04073900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04074900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04075900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04076900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04077900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04078900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x04079900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x0407A900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x0407B900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x0407C900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x0407D900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x0407E900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW,
	0x0407F900 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW
पूर्ण;

/* 40MHz reference frequency
 * Need to Pull PLLON(PE3) low when writing channel रेजिस्टरs through 3-wire.
 */
अटल स्थिर अचिन्हित दीर्घ dwAL7230InitTable[CB_AL7230_INIT_SEQ] = अणु
	0x00379000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* Channel1 // Need modअगरy क्रम 11a */
	0x13333100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* Channel1 // Need modअगरy क्रम 11a */
	0x841FF200 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* Need modअगरy क्रम 11a: 451FE2 */
	0x3FDFA300 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* Need modअगरy क्रम 11a: 5FDFA3 */
	0x7FD78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* 11b/g    // Need modअगरy क्रम 11a */
	/* RoberYu:20050113, Rev0.47 Register Setting Guide */
	0x802B5500 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* Need modअगरy क्रम 11a: 8D1B55 */
	0x56AF3600 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW,
	0xCE020700 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* Need modअगरy क्रम 11a: 860207 */
	0x6EBC0800 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW,
	0x221BB900 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW,
	0xE0000A00 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* Need modअगरy क्रम 11a: E0600A */
	0x08031B00 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* init 0x080B1B00 => 0x080F1B00 क्रम 3 wire control TxGain(D10) */
	/* RoberYu:20050113, Rev0.47 Register Setting Guide */
	0x000A3C00 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* Need modअगरy क्रम 11a: 00143C */
	0xFFFFFD00 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW,
	0x00000E00 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW,
	0x1ABA8F00 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW  /* Need modअगरy क्रम 11a: 12BACF */
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ dwAL7230InitTableAMode[CB_AL7230_INIT_SEQ] = अणु
	0x0FF52000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* Channel184 // Need modअगरy क्रम 11b/g */
	0x00000100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* Channel184 // Need modअगरy क्रम 11b/g */
	0x451FE200 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* Need modअगरy क्रम 11b/g */
	0x5FDFA300 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* Need modअगरy क्रम 11b/g */
	0x67F78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* 11a    // Need modअगरy क्रम 11b/g */
	0x853F5500 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* Need modअगरy क्रम 11b/g, RoberYu:20050113 */
	0x56AF3600 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW,
	0xCE020700 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* Need modअगरy क्रम 11b/g */
	0x6EBC0800 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW,
	0x221BB900 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW,
	0xE0600A00 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* Need modअगरy क्रम 11b/g */
	0x08031B00 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* init 0x080B1B00 => 0x080F1B00 क्रम 3 wire control TxGain(D10) */
	0x00147C00 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* Need modअगरy क्रम 11b/g */
	0xFFFFFD00 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW,
	0x00000E00 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW,
	0x12BACF00 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW  /* Need modअगरy क्रम 11b/g */
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ dwAL7230ChannelTable0[CB_MAX_CHANNEL] = अणु
	0x00379000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  1, Tf = 2412MHz */
	0x00379000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  2, Tf = 2417MHz */
	0x00379000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  3, Tf = 2422MHz */
	0x00379000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  4, Tf = 2427MHz */
	0x0037A000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  5, Tf = 2432MHz */
	0x0037A000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  6, Tf = 2437MHz */
	0x0037A000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  7, Tf = 2442MHz */
	0x0037A000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  8, Tf = 2447MHz //RobertYu: 20050218, update क्रम APNode 0.49 */
	0x0037B000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  9, Tf = 2452MHz //RobertYu: 20050218, update क्रम APNode 0.49 */
	0x0037B000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 10, Tf = 2457MHz //RobertYu: 20050218, update क्रम APNode 0.49 */
	0x0037B000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 11, Tf = 2462MHz //RobertYu: 20050218, update क्रम APNode 0.49 */
	0x0037B000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 12, Tf = 2467MHz //RobertYu: 20050218, update क्रम APNode 0.49 */
	0x0037C000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 13, Tf = 2472MHz //RobertYu: 20050218, update क्रम APNode 0.49 */
	0x0037C000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 14, Tf = 2484MHz */

	/* 4.9G => Ch 183, 184, 185, 187, 188, 189, 192, 196  (Value:15 ~ 22) */
	0x0FF52000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 183, Tf = 4915MHz (15) */
	0x0FF52000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 184, Tf = 4920MHz (16) */
	0x0FF52000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 185, Tf = 4925MHz (17) */
	0x0FF52000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 187, Tf = 4935MHz (18) */
	0x0FF52000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 188, Tf = 4940MHz (19) */
	0x0FF52000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 189, Tf = 4945MHz (20) */
	0x0FF53000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 192, Tf = 4960MHz (21) */
	0x0FF53000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 196, Tf = 4980MHz (22) */

	/* 5G => Ch 7, 8, 9, 11, 12, 16, 34, 36, 38, 40, 42, 44, 46, 48, 52, 56, 60, 64,
	 * 100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140, 149, 153, 157, 161, 165  (Value 23 ~ 56)
	 */

	0x0FF54000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =   7, Tf = 5035MHz (23) */
	0x0FF54000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =   8, Tf = 5040MHz (24) */
	0x0FF54000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =   9, Tf = 5045MHz (25) */
	0x0FF54000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  11, Tf = 5055MHz (26) */
	0x0FF54000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  12, Tf = 5060MHz (27) */
	0x0FF55000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  16, Tf = 5080MHz (28) */
	0x0FF56000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  34, Tf = 5170MHz (29) */
	0x0FF56000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  36, Tf = 5180MHz (30) */
	0x0FF57000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  38, Tf = 5190MHz (31) //RobertYu: 20050218, update क्रम APNode 0.49 */
	0x0FF57000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  40, Tf = 5200MHz (32) */
	0x0FF57000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  42, Tf = 5210MHz (33) */
	0x0FF57000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  44, Tf = 5220MHz (34) */
	0x0FF57000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  46, Tf = 5230MHz (35) */
	0x0FF57000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  48, Tf = 5240MHz (36) */
	0x0FF58000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  52, Tf = 5260MHz (37) */
	0x0FF58000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  56, Tf = 5280MHz (38) */
	0x0FF58000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  60, Tf = 5300MHz (39) */
	0x0FF59000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  64, Tf = 5320MHz (40) */

	0x0FF5C000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 100, Tf = 5500MHz (41) */
	0x0FF5C000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 104, Tf = 5520MHz (42) */
	0x0FF5C000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 108, Tf = 5540MHz (43) */
	0x0FF5D000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 112, Tf = 5560MHz (44) */
	0x0FF5D000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 116, Tf = 5580MHz (45) */
	0x0FF5D000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 120, Tf = 5600MHz (46) */
	0x0FF5E000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 124, Tf = 5620MHz (47) */
	0x0FF5E000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 128, Tf = 5640MHz (48) */
	0x0FF5E000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 132, Tf = 5660MHz (49) */
	0x0FF5F000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 136, Tf = 5680MHz (50) */
	0x0FF5F000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 140, Tf = 5700MHz (51) */
	0x0FF60000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 149, Tf = 5745MHz (52) */
	0x0FF60000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 153, Tf = 5765MHz (53) */
	0x0FF60000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 157, Tf = 5785MHz (54) */
	0x0FF61000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 161, Tf = 5805MHz (55) */
	0x0FF61000 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW  /* channel = 165, Tf = 5825MHz (56) */
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ dwAL7230ChannelTable1[CB_MAX_CHANNEL] = अणु
	0x13333100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  1, Tf = 2412MHz */
	0x1B333100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  2, Tf = 2417MHz */
	0x03333100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  3, Tf = 2422MHz */
	0x0B333100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  4, Tf = 2427MHz */
	0x13333100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  5, Tf = 2432MHz */
	0x1B333100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  6, Tf = 2437MHz */
	0x03333100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  7, Tf = 2442MHz */
	0x0B333100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  8, Tf = 2447MHz */
	0x13333100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  9, Tf = 2452MHz */
	0x1B333100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 10, Tf = 2457MHz */
	0x03333100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 11, Tf = 2462MHz */
	0x0B333100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 12, Tf = 2467MHz */
	0x13333100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 13, Tf = 2472MHz */
	0x06666100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 14, Tf = 2484MHz */

	/* 4.9G => Ch 183, 184, 185, 187, 188, 189, 192, 196  (Value:15 ~ 22) */
	0x1D555100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 183, Tf = 4915MHz (15) */
	0x00000100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 184, Tf = 4920MHz (16) */
	0x02AAA100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 185, Tf = 4925MHz (17) */
	0x08000100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 187, Tf = 4935MHz (18) */
	0x0AAAA100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 188, Tf = 4940MHz (19) */
	0x0D555100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 189, Tf = 4945MHz (20) */
	0x15555100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 192, Tf = 4960MHz (21) */
	0x00000100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 196, Tf = 4980MHz (22) */

	/* 5G => Ch 7, 8, 9, 11, 12, 16, 34, 36, 38, 40, 42, 44, 46, 48, 52, 56, 60, 64,
	 * 100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140, 149, 153, 157, 161, 165  (Value 23 ~ 56)
	 */
	0x1D555100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =   7, Tf = 5035MHz (23) */
	0x00000100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =   8, Tf = 5040MHz (24) */
	0x02AAA100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =   9, Tf = 5045MHz (25) */
	0x08000100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  11, Tf = 5055MHz (26) */
	0x0AAAA100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  12, Tf = 5060MHz (27) */
	0x15555100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  16, Tf = 5080MHz (28) */
	0x05555100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  34, Tf = 5170MHz (29) */
	0x0AAAA100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  36, Tf = 5180MHz (30) */
	0x10000100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  38, Tf = 5190MHz (31) */
	0x15555100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  40, Tf = 5200MHz (32) */
	0x1AAAA100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  42, Tf = 5210MHz (33) */
	0x00000100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  44, Tf = 5220MHz (34) */
	0x05555100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  46, Tf = 5230MHz (35) */
	0x0AAAA100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  48, Tf = 5240MHz (36) */
	0x15555100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  52, Tf = 5260MHz (37) */
	0x00000100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  56, Tf = 5280MHz (38) */
	0x0AAAA100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  60, Tf = 5300MHz (39) */
	0x15555100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  64, Tf = 5320MHz (40) */
	0x15555100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 100, Tf = 5500MHz (41) */
	0x00000100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 104, Tf = 5520MHz (42) */
	0x0AAAA100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 108, Tf = 5540MHz (43) */
	0x15555100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 112, Tf = 5560MHz (44) */
	0x00000100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 116, Tf = 5580MHz (45) */
	0x0AAAA100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 120, Tf = 5600MHz (46) */
	0x15555100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 124, Tf = 5620MHz (47) */
	0x00000100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 128, Tf = 5640MHz (48) */
	0x0AAAA100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 132, Tf = 5660MHz (49) */
	0x15555100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 136, Tf = 5680MHz (50) */
	0x00000100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 140, Tf = 5700MHz (51) */
	0x18000100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 149, Tf = 5745MHz (52) */
	0x02AAA100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 153, Tf = 5765MHz (53) */
	0x0D555100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 157, Tf = 5785MHz (54) */
	0x18000100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 161, Tf = 5805MHz (55) */
	0x02AAA100 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW  /* channel = 165, Tf = 5825MHz (56) */
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ dwAL7230ChannelTable2[CB_MAX_CHANNEL] = अणु
	0x7FD78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  1, Tf = 2412MHz */
	0x7FD78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  2, Tf = 2417MHz */
	0x7FD78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  3, Tf = 2422MHz */
	0x7FD78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  4, Tf = 2427MHz */
	0x7FD78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  5, Tf = 2432MHz */
	0x7FD78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  6, Tf = 2437MHz */
	0x7FD78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  7, Tf = 2442MHz */
	0x7FD78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  8, Tf = 2447MHz */
	0x7FD78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  9, Tf = 2452MHz */
	0x7FD78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 10, Tf = 2457MHz */
	0x7FD78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 11, Tf = 2462MHz */
	0x7FD78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 12, Tf = 2467MHz */
	0x7FD78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 13, Tf = 2472MHz */
	0x7FD78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 14, Tf = 2484MHz */

	/* 4.9G => Ch 183, 184, 185, 187, 188, 189, 192, 196  (Value:15 ~ 22) */
	0x77D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 183, Tf = 4915MHz (15) */
	0x67D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 184, Tf = 4920MHz (16) */
	0x77D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 185, Tf = 4925MHz (17) */
	0x77D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 187, Tf = 4935MHz (18) */
	0x77D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 188, Tf = 4940MHz (19) */
	0x77D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 189, Tf = 4945MHz (20) */
	0x77D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 192, Tf = 4960MHz (21) */
	0x67D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 196, Tf = 4980MHz (22) */

	/* 5G => Ch 7, 8, 9, 11, 12, 16, 34, 36, 38, 40, 42, 44, 46, 48, 52, 56, 60, 64,
	 * 100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140, 149, 153, 157, 161, 165  (Value 23 ~ 56)
	 */
	0x77D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =   7, Tf = 5035MHz (23) */
	0x67D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =   8, Tf = 5040MHz (24) */
	0x77D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =   9, Tf = 5045MHz (25) */
	0x77D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  11, Tf = 5055MHz (26) */
	0x77D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  12, Tf = 5060MHz (27) */
	0x77D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  16, Tf = 5080MHz (28) */
	0x77D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  34, Tf = 5170MHz (29) */
	0x77D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  36, Tf = 5180MHz (30) */
	0x77D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  38, Tf = 5190MHz (31) */
	0x77D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  40, Tf = 5200MHz (32) */
	0x77D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  42, Tf = 5210MHz (33) */
	0x67D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  44, Tf = 5220MHz (34) */
	0x77D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  46, Tf = 5230MHz (35) */
	0x77D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  48, Tf = 5240MHz (36) */
	0x77D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  52, Tf = 5260MHz (37) */
	0x67D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  56, Tf = 5280MHz (38) */
	0x77D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  60, Tf = 5300MHz (39) */
	0x77D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel =  64, Tf = 5320MHz (40) */
	0x77D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 100, Tf = 5500MHz (41) */
	0x67D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 104, Tf = 5520MHz (42) */
	0x77D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 108, Tf = 5540MHz (43) */
	0x77D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 112, Tf = 5560MHz (44) */
	0x67D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 116, Tf = 5580MHz (45) */
	0x77D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 120, Tf = 5600MHz (46) */
	0x77D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 124, Tf = 5620MHz (47) */
	0x67D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 128, Tf = 5640MHz (48) */
	0x77D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 132, Tf = 5660MHz (49) */
	0x77D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 136, Tf = 5680MHz (50) */
	0x67D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 140, Tf = 5700MHz (51) */
	0x77D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 149, Tf = 5745MHz (52) */
	0x77D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 153, Tf = 5765MHz (53) */
	0x77D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 157, Tf = 5785MHz (54) */
	0x77D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW, /* channel = 161, Tf = 5805MHz (55) */
	0x77D78400 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW  /* channel = 165, Tf = 5825MHz (56) */
पूर्ण;

/*
 * Description: AIROHA IFRF chip init function
 *
 * Parameters:
 *  In:
 *      iobase      - I/O base address
 *  Out:
 *      none
 *
 * Return Value: true अगर succeeded; false अगर failed.
 *
 */
अटल bool s_bAL7230Init(काष्ठा vnt_निजी *priv)
अणु
	व्योम __iomem *iobase = priv->PortOffset;
	पूर्णांक     ii;
	bool ret;

	ret = true;

	/* 3-wire control क्रम normal mode */
	VNSvOutPortB(iobase + MAC_REG_SOFTPWRCTL, 0);

	MACvWordRegBitsOn(iobase, MAC_REG_SOFTPWRCTL, (SOFTPWRCTL_SWPECTI  |
							 SOFTPWRCTL_TXPEINV));
	bb_घातer_save_mode_off(priv); /* RobertYu:20050106, have DC value क्रम Calibration */

	क्रम (ii = 0; ii < CB_AL7230_INIT_SEQ; ii++)
		ret &= IFRFbWriteEmbedded(priv, dwAL7230InitTable[ii]);

	/* PLL On */
	MACvWordRegBitsOn(iobase, MAC_REG_SOFTPWRCTL, SOFTPWRCTL_SWPE3);

	/* Calibration */
	MACvTimer0MicroSDelay(priv, 150);/* 150us */
	/* TXDCOC:active, RCK:disable */
	ret &= IFRFbWriteEmbedded(priv, (0x9ABA8F00 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW));
	MACvTimer0MicroSDelay(priv, 30);/* 30us */
	/* TXDCOC:disable, RCK:active */
	ret &= IFRFbWriteEmbedded(priv, (0x3ABA8F00 + (BY_AL7230_REG_LEN << 3) + IFREGCTL_REGW));
	MACvTimer0MicroSDelay(priv, 30);/* 30us */
	/* TXDCOC:disable, RCK:disable */
	ret &= IFRFbWriteEmbedded(priv, dwAL7230InitTable[CB_AL7230_INIT_SEQ - 1]);

	MACvWordRegBitsOn(iobase, MAC_REG_SOFTPWRCTL, (SOFTPWRCTL_SWPE3    |
							 SOFTPWRCTL_SWPE2    |
							 SOFTPWRCTL_SWPECTI  |
							 SOFTPWRCTL_TXPEINV));

	bb_घातer_save_mode_on(priv); /* RobertYu:20050106 */

	/* PE1: TX_ON, PE2: RX_ON, PE3: PLLON */
	/* 3-wire control क्रम घातer saving mode */
	VNSvOutPortB(iobase + MAC_REG_PSPWRSIG, (PSSIG_WPE3 | PSSIG_WPE2)); /* 1100 0000 */

	वापस ret;
पूर्ण

/* Need to Pull PLLON low when writing channel रेजिस्टरs through
 * 3-wire पूर्णांकerface
 */
अटल bool s_bAL7230SelectChannel(काष्ठा vnt_निजी *priv, अचिन्हित अक्षर byChannel)
अणु
	व्योम __iomem *iobase = priv->PortOffset;
	bool ret;

	ret = true;

	/* PLLON Off */
	MACvWordRegBitsOff(iobase, MAC_REG_SOFTPWRCTL, SOFTPWRCTL_SWPE3);

	ret &= IFRFbWriteEmbedded(priv, dwAL7230ChannelTable0[byChannel - 1]);
	ret &= IFRFbWriteEmbedded(priv, dwAL7230ChannelTable1[byChannel - 1]);
	ret &= IFRFbWriteEmbedded(priv, dwAL7230ChannelTable2[byChannel - 1]);

	/* PLLOn On */
	MACvWordRegBitsOn(iobase, MAC_REG_SOFTPWRCTL, SOFTPWRCTL_SWPE3);

	/* Set Channel[7] = 0 to tell H/W channel is changing now. */
	VNSvOutPortB(iobase + MAC_REG_CHANNEL, (byChannel & 0x7F));
	MACvTimer0MicroSDelay(priv, SWITCH_CHANNEL_DELAY_AL7230);
	/* Set Channel[7] = 1 to tell H/W channel change is करोne. */
	VNSvOutPortB(iobase + MAC_REG_CHANNEL, (byChannel | 0x80));

	वापस ret;
पूर्ण

/*
 * Description: Write to IF/RF, by embedded programming
 *
 * Parameters:
 *  In:
 *      iobase      - I/O base address
 *      dwData      - data to ग_लिखो
 *  Out:
 *      none
 *
 * Return Value: true अगर succeeded; false अगर failed.
 *
 */
bool IFRFbWriteEmbedded(काष्ठा vnt_निजी *priv, अचिन्हित दीर्घ dwData)
अणु
	व्योम __iomem *iobase = priv->PortOffset;
	अचिन्हित लघु ww;
	अचिन्हित दीर्घ dwValue;

	VNSvOutPortD(iobase + MAC_REG_IFREGCTL, dwData);

	/* W_MAX_TIMEOUT is the समयout period */
	क्रम (ww = 0; ww < W_MAX_TIMEOUT; ww++) अणु
		VNSvInPortD(iobase + MAC_REG_IFREGCTL, &dwValue);
		अगर (dwValue & IFREGCTL_DONE)
			अवरोध;
	पूर्ण

	अगर (ww == W_MAX_TIMEOUT)
		वापस false;

	वापस true;
पूर्ण

/*
 * Description: AIROHA IFRF chip init function
 *
 * Parameters:
 *  In:
 *      iobase      - I/O base address
 *  Out:
 *      none
 *
 * Return Value: true अगर succeeded; false अगर failed.
 *
 */
अटल bool RFbAL2230Init(काष्ठा vnt_निजी *priv)
अणु
	व्योम __iomem *iobase = priv->PortOffset;
	पूर्णांक     ii;
	bool ret;

	ret = true;

	/* 3-wire control क्रम normal mode */
	VNSvOutPortB(iobase + MAC_REG_SOFTPWRCTL, 0);

	MACvWordRegBitsOn(iobase, MAC_REG_SOFTPWRCTL, (SOFTPWRCTL_SWPECTI  |
							 SOFTPWRCTL_TXPEINV));
	/* PLL  Off */
	MACvWordRegBitsOff(iobase, MAC_REG_SOFTPWRCTL, SOFTPWRCTL_SWPE3);

	/* patch abnormal AL2230 frequency output */
	IFRFbWriteEmbedded(priv, (0x07168700 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW));

	क्रम (ii = 0; ii < CB_AL2230_INIT_SEQ; ii++)
		ret &= IFRFbWriteEmbedded(priv, dwAL2230InitTable[ii]);
	MACvTimer0MicroSDelay(priv, 30); /* delay 30 us */

	/* PLL On */
	MACvWordRegBitsOn(iobase, MAC_REG_SOFTPWRCTL, SOFTPWRCTL_SWPE3);

	MACvTimer0MicroSDelay(priv, 150);/* 150us */
	ret &= IFRFbWriteEmbedded(priv, (0x00d80f00 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW));
	MACvTimer0MicroSDelay(priv, 30);/* 30us */
	ret &= IFRFbWriteEmbedded(priv, (0x00780f00 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW));
	MACvTimer0MicroSDelay(priv, 30);/* 30us */
	ret &= IFRFbWriteEmbedded(priv,
				  dwAL2230InitTable[CB_AL2230_INIT_SEQ - 1]);

	MACvWordRegBitsOn(iobase, MAC_REG_SOFTPWRCTL, (SOFTPWRCTL_SWPE3    |
							 SOFTPWRCTL_SWPE2    |
							 SOFTPWRCTL_SWPECTI  |
							 SOFTPWRCTL_TXPEINV));

	/* 3-wire control क्रम घातer saving mode */
	VNSvOutPortB(iobase + MAC_REG_PSPWRSIG, (PSSIG_WPE3 | PSSIG_WPE2)); /* 1100 0000 */

	वापस ret;
पूर्ण

अटल bool RFbAL2230SelectChannel(काष्ठा vnt_निजी *priv, अचिन्हित अक्षर byChannel)
अणु
	व्योम __iomem *iobase = priv->PortOffset;
	bool ret;

	ret = true;

	ret &= IFRFbWriteEmbedded(priv, dwAL2230ChannelTable0[byChannel - 1]);
	ret &= IFRFbWriteEmbedded(priv, dwAL2230ChannelTable1[byChannel - 1]);

	/* Set Channel[7] = 0 to tell H/W channel is changing now. */
	VNSvOutPortB(iobase + MAC_REG_CHANNEL, (byChannel & 0x7F));
	MACvTimer0MicroSDelay(priv, SWITCH_CHANNEL_DELAY_AL2230);
	/* Set Channel[7] = 1 to tell H/W channel change is करोne. */
	VNSvOutPortB(iobase + MAC_REG_CHANNEL, (byChannel | 0x80));

	वापस ret;
पूर्ण

/*
 * Description: RF init function
 *
 * Parameters:
 *  In:
 *      byBBType
 *      byRFType
 *  Out:
 *      none
 *
 * Return Value: true अगर succeeded; false अगर failed.
 *
 */
bool RFbInit(काष्ठा vnt_निजी *priv)
अणु
	bool ret = true;

	चयन (priv->byRFType) अणु
	हाल RF_AIROHA:
	हाल RF_AL2230S:
		priv->byMaxPwrLevel = AL2230_PWR_IDX_LEN;
		ret = RFbAL2230Init(priv);
		अवरोध;
	हाल RF_AIROHA7230:
		priv->byMaxPwrLevel = AL7230_PWR_IDX_LEN;
		ret = s_bAL7230Init(priv);
		अवरोध;
	हाल RF_NOTHING:
		ret = true;
		अवरोध;
	शेष:
		ret = false;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Description: Select channel
 *
 * Parameters:
 *  In:
 *      byRFType
 *      byChannel    - Channel number
 *  Out:
 *      none
 *
 * Return Value: true अगर succeeded; false अगर failed.
 *
 */
bool RFbSelectChannel(काष्ठा vnt_निजी *priv, अचिन्हित अक्षर byRFType,
		      u16 byChannel)
अणु
	bool ret = true;

	चयन (byRFType) अणु
	हाल RF_AIROHA:
	हाल RF_AL2230S:
		ret = RFbAL2230SelectChannel(priv, byChannel);
		अवरोध;
		/*अणुअणु RobertYu: 20050104 */
	हाल RF_AIROHA7230:
		ret = s_bAL7230SelectChannel(priv, byChannel);
		अवरोध;
		/*पूर्णपूर्ण RobertYu */
	हाल RF_NOTHING:
		ret = true;
		अवरोध;
	शेष:
		ret = false;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Description: Write WakeProgSyn
 *
 * Parameters:
 *  In:
 *      iobase      - I/O base address
 *      uChannel    - channel number
 *      bySleepCnt  - SleepProgSyn count
 *
 * Return Value: None.
 *
 */
bool RFvWriteWakeProgSyn(काष्ठा vnt_निजी *priv, अचिन्हित अक्षर byRFType,
			 u16 uChannel)
अणु
	व्योम __iomem *iobase = priv->PortOffset;
	पूर्णांक   ii;
	अचिन्हित अक्षर byInitCount = 0;
	अचिन्हित अक्षर bySleepCount = 0;

	VNSvOutPortW(iobase + MAC_REG_MISCFFNDEX, 0);
	चयन (byRFType) अणु
	हाल RF_AIROHA:
	हाल RF_AL2230S:

		अगर (uChannel > CB_MAX_CHANNEL_24G)
			वापस false;

		 /* Init Reg + Channel Reg (2) */
		byInitCount = CB_AL2230_INIT_SEQ + 2;
		bySleepCount = 0;
		अगर (byInitCount > (MISCFIFO_SYNDATASIZE - bySleepCount))
			वापस false;

		क्रम (ii = 0; ii < CB_AL2230_INIT_SEQ; ii++)
			MACvSetMISCFअगरo(priv, (अचिन्हित लघु)(MISCFIFO_SYNDATA_IDX + ii), dwAL2230InitTable[ii]);

		MACvSetMISCFअगरo(priv, (अचिन्हित लघु)(MISCFIFO_SYNDATA_IDX + ii), dwAL2230ChannelTable0[uChannel - 1]);
		ii++;
		MACvSetMISCFअगरo(priv, (अचिन्हित लघु)(MISCFIFO_SYNDATA_IDX + ii), dwAL2230ChannelTable1[uChannel - 1]);
		अवरोध;

		/* Need to check, PLLON need to be low क्रम channel setting */
	हाल RF_AIROHA7230:
		 /* Init Reg + Channel Reg (3) */
		byInitCount = CB_AL7230_INIT_SEQ + 3;
		bySleepCount = 0;
		अगर (byInitCount > (MISCFIFO_SYNDATASIZE - bySleepCount))
			वापस false;

		अगर (uChannel <= CB_MAX_CHANNEL_24G) अणु
			क्रम (ii = 0; ii < CB_AL7230_INIT_SEQ; ii++)
				MACvSetMISCFअगरo(priv, (अचिन्हित लघु)(MISCFIFO_SYNDATA_IDX + ii), dwAL7230InitTable[ii]);
		पूर्ण अन्यथा अणु
			क्रम (ii = 0; ii < CB_AL7230_INIT_SEQ; ii++)
				MACvSetMISCFअगरo(priv, (अचिन्हित लघु)(MISCFIFO_SYNDATA_IDX + ii), dwAL7230InitTableAMode[ii]);
		पूर्ण

		MACvSetMISCFअगरo(priv, (अचिन्हित लघु)(MISCFIFO_SYNDATA_IDX + ii), dwAL7230ChannelTable0[uChannel - 1]);
		ii++;
		MACvSetMISCFअगरo(priv, (अचिन्हित लघु)(MISCFIFO_SYNDATA_IDX + ii), dwAL7230ChannelTable1[uChannel - 1]);
		ii++;
		MACvSetMISCFअगरo(priv, (अचिन्हित लघु)(MISCFIFO_SYNDATA_IDX + ii), dwAL7230ChannelTable2[uChannel - 1]);
		अवरोध;

	हाल RF_NOTHING:
		वापस true;

	शेष:
		वापस false;
	पूर्ण

	MACvSetMISCFअगरo(priv, MISCFIFO_SYNINFO_IDX, (अचिन्हित दीर्घ)MAKEWORD(bySleepCount, byInitCount));

	वापस true;
पूर्ण

/*
 * Description: Set Tx घातer
 *
 * Parameters:
 *  In:
 *      iobase         - I/O base address
 *      dwRFPowerTable - RF Tx Power Setting
 *  Out:
 *      none
 *
 * Return Value: true अगर succeeded; false अगर failed.
 *
 */
bool RFbSetPower(काष्ठा vnt_निजी *priv, अचिन्हित पूर्णांक rate, u16 uCH)
अणु
	bool ret;
	अचिन्हित अक्षर byPwr = 0;
	अचिन्हित अक्षर byDec = 0;

	अगर (priv->dwDiagRefCount != 0)
		वापस true;

	अगर ((uCH < 1) || (uCH > CB_MAX_CHANNEL))
		वापस false;

	चयन (rate) अणु
	हाल RATE_1M:
	हाल RATE_2M:
	हाल RATE_5M:
	हाल RATE_11M:
		अगर (uCH > CB_MAX_CHANNEL_24G)
			वापस false;

		byPwr = priv->abyCCKPwrTbl[uCH];
		अवरोध;
	हाल RATE_6M:
	हाल RATE_9M:
	हाल RATE_12M:
	हाल RATE_18M:
		byPwr = priv->abyOFDMPwrTbl[uCH];
		अगर (priv->byRFType == RF_UW2452)
			byDec = byPwr + 14;
		अन्यथा
			byDec = byPwr + 10;

		अगर (byDec >= priv->byMaxPwrLevel)
			byDec = priv->byMaxPwrLevel - 1;

		byPwr = byDec;
		अवरोध;
	हाल RATE_24M:
	हाल RATE_36M:
	हाल RATE_48M:
	हाल RATE_54M:
		byPwr = priv->abyOFDMPwrTbl[uCH];
		अवरोध;
	पूर्ण

	अगर (priv->byCurPwr == byPwr)
		वापस true;

	ret = RFbRawSetPower(priv, byPwr, rate);
	अगर (ret)
		priv->byCurPwr = byPwr;

	वापस ret;
पूर्ण

/*
 * Description: Set Tx घातer
 *
 * Parameters:
 *  In:
 *      iobase         - I/O base address
 *      dwRFPowerTable - RF Tx Power Setting
 *  Out:
 *      none
 *
 * Return Value: true अगर succeeded; false अगर failed.
 *
 */

bool RFbRawSetPower(काष्ठा vnt_निजी *priv, अचिन्हित अक्षर byPwr,
		    अचिन्हित पूर्णांक rate)
अणु
	bool ret = true;
	अचिन्हित दीर्घ dwMax7230Pwr = 0;

	अगर (byPwr >=  priv->byMaxPwrLevel)
		वापस false;

	चयन (priv->byRFType) अणु
	हाल RF_AIROHA:
		ret &= IFRFbWriteEmbedded(priv, dwAL2230PowerTable[byPwr]);
		अगर (rate <= RATE_11M)
			ret &= IFRFbWriteEmbedded(priv, 0x0001B400 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW);
		अन्यथा
			ret &= IFRFbWriteEmbedded(priv, 0x0005A400 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW);

		अवरोध;

	हाल RF_AL2230S:
		ret &= IFRFbWriteEmbedded(priv, dwAL2230PowerTable[byPwr]);
		अगर (rate <= RATE_11M) अणु
			ret &= IFRFbWriteEmbedded(priv, 0x040C1400 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW);
			ret &= IFRFbWriteEmbedded(priv, 0x00299B00 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW);
		पूर्ण अन्यथा अणु
			ret &= IFRFbWriteEmbedded(priv, 0x0005A400 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW);
			ret &= IFRFbWriteEmbedded(priv, 0x00099B00 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW);
		पूर्ण

		अवरोध;

	हाल RF_AIROHA7230:
		/* 0x080F1B00 क्रम 3 wire control TxGain(D10)
		 * and 0x31 as TX Gain value
		 */
		dwMax7230Pwr = 0x080C0B00 | ((byPwr) << 12) |
			(BY_AL7230_REG_LEN << 3)  | IFREGCTL_REGW;

		ret &= IFRFbWriteEmbedded(priv, dwMax7230Pwr);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

/*
 *
 * Routine Description:
 *     Translate RSSI to dBm
 *
 * Parameters:
 *  In:
 *      priv         - The adapter to be translated
 *      byCurrRSSI      - RSSI to be translated
 *  Out:
 *      pdwdbm          - Translated dbm number
 *
 * Return Value: none
 *
 */
व्योम
RFvRSSITodBm(काष्ठा vnt_निजी *priv, अचिन्हित अक्षर byCurrRSSI, दीर्घ *pldBm)
अणु
	अचिन्हित अक्षर byIdx = (((byCurrRSSI & 0xC0) >> 6) & 0x03);
	दीर्घ b = (byCurrRSSI & 0x3F);
	दीर्घ a = 0;
	अचिन्हित अक्षर abyAIROHARF[4] = अणु0, 18, 0, 40पूर्ण;

	चयन (priv->byRFType) अणु
	हाल RF_AIROHA:
	हाल RF_AL2230S:
	हाल RF_AIROHA7230:
		a = abyAIROHARF[byIdx];
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	*pldBm = -1 * (a + b * 2);
पूर्ण

/* Post processing क्रम the 11b/g and 11a.
 * क्रम save समय on changing Reg2,3,5,7,10,12,15
 */
bool RFbAL7230SelectChannelPostProcess(काष्ठा vnt_निजी *priv,
				       u16 byOldChannel,
				       u16 byNewChannel)
अणु
	bool ret;

	ret = true;

	/* अगर change between 11 b/g and 11a need to update the following
	 * रेजिस्टर
	 * Channel Index 1~14
	 */
	अगर ((byOldChannel <= CB_MAX_CHANNEL_24G) && (byNewChannel > CB_MAX_CHANNEL_24G)) अणु
		/* Change from 2.4G to 5G [Reg] */
		ret &= IFRFbWriteEmbedded(priv, dwAL7230InitTableAMode[2]);
		ret &= IFRFbWriteEmbedded(priv, dwAL7230InitTableAMode[3]);
		ret &= IFRFbWriteEmbedded(priv, dwAL7230InitTableAMode[5]);
		ret &= IFRFbWriteEmbedded(priv, dwAL7230InitTableAMode[7]);
		ret &= IFRFbWriteEmbedded(priv, dwAL7230InitTableAMode[10]);
		ret &= IFRFbWriteEmbedded(priv, dwAL7230InitTableAMode[12]);
		ret &= IFRFbWriteEmbedded(priv, dwAL7230InitTableAMode[15]);
	पूर्ण अन्यथा अगर ((byOldChannel > CB_MAX_CHANNEL_24G) && (byNewChannel <= CB_MAX_CHANNEL_24G)) अणु
		/* Change from 5G to 2.4G [Reg] */
		ret &= IFRFbWriteEmbedded(priv, dwAL7230InitTable[2]);
		ret &= IFRFbWriteEmbedded(priv, dwAL7230InitTable[3]);
		ret &= IFRFbWriteEmbedded(priv, dwAL7230InitTable[5]);
		ret &= IFRFbWriteEmbedded(priv, dwAL7230InitTable[7]);
		ret &= IFRFbWriteEmbedded(priv, dwAL7230InitTable[10]);
		ret &= IFRFbWriteEmbedded(priv, dwAL7230InitTable[12]);
		ret &= IFRFbWriteEmbedded(priv, dwAL7230InitTable[15]);
	पूर्ण

	वापस ret;
पूर्ण
