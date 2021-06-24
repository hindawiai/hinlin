<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2009-2013  Realtek Corporation.
 *
 * Contact Inक्रमmation:
 * wlanfae <wlanfae@realtek.com>
 * Realtek Corporation, No. 2, Innovation Road II, Hsinchu Science Park,
 * Hsinchu 300, Taiwan.
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 *****************************************************************************/
#समावेश "drv_types.h"
#समावेश <linux/types.h>

#अगर_अघोषित __RTL92C__FW__H__
#घोषणा __RTL92C__FW__H__

#घोषणा FW_8192C_START_ADDRESS		0x1000
#घोषणा FW_8192C_PAGE_SIZE			4096
#घोषणा FW_8192C_POLLING_DELAY		5

काष्ठा rtl92c_firmware_header अणु
	__le16 signature;
	u8 category;
	u8 function;
	u16 version;
	u8 subversion;
	u8 rsvd1;
	u8 month;
	u8 date;
	u8 hour;
	u8 minute;
	u16 ramcodesize;
	u16 rsvd2;
	u32 svnindex;
	u32 rsvd3;
	u32 rsvd4;
	u32 rsvd5;
पूर्ण;

पूर्णांक rtl88eu_करोwnload_fw(काष्ठा adapter *adapt);

#पूर्ण_अगर
