<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * File: mac.c
 *
 * Purpose:  MAC routines
 *
 * Author: Tevin Chen
 *
 * Date: May 21, 1996
 *
 * Functions:
 *
 * Revision History:
 */

#समावेश <linux/etherdevice.h>

#समावेश "desc.h"
#समावेश "mac.h"
#समावेश "usbpipe.h"

पूर्णांक vnt_mac_set_filter(काष्ठा vnt_निजी *priv, u64 mc_filter)
अणु
	__le64 le_mc = cpu_to_le64(mc_filter);

	वापस vnt_control_out(priv, MESSAGE_TYPE_WRITE, MAC_REG_MAR0,
			       MESSAGE_REQUEST_MACREG, माप(le_mc),
			       (u8 *)&le_mc);
पूर्ण

पूर्णांक vnt_mac_shutकरोwn(काष्ठा vnt_निजी *priv)
अणु
	वापस vnt_control_out(priv, MESSAGE_TYPE_MACSHUTDOWN, 0, 0, 0, शून्य);
पूर्ण

पूर्णांक vnt_mac_set_bb_type(काष्ठा vnt_निजी *priv, u8 type)
अणु
	u8 data[2];

	data[0] = type;
	data[1] = EnCFG_BBType_MASK;

	वापस vnt_control_out(priv, MESSAGE_TYPE_WRITE_MASK, MAC_REG_ENCFG0,
			       MESSAGE_REQUEST_MACREG,	ARRAY_SIZE(data),
			       data);
पूर्ण

पूर्णांक vnt_mac_disable_keyentry(काष्ठा vnt_निजी *priv, u8 entry_idx)
अणु
	वापस vnt_control_out(priv, MESSAGE_TYPE_CLRKEYENTRY, 0, 0,
			       माप(entry_idx), &entry_idx);
पूर्ण

पूर्णांक vnt_mac_set_keyentry(काष्ठा vnt_निजी *priv, u16 key_ctl, u32 entry_idx,
			 u32 key_idx, u8 *addr, u8 *key)
अणु
	काष्ठा vnt_mac_set_key set_key;
	u16 offset;

	offset = MISCFIFO_KEYETRY0;
	offset += entry_idx * MISCFIFO_KEYENTRYSIZE;

	set_key.u.ग_लिखो.key_ctl = cpu_to_le16(key_ctl);
	ether_addr_copy(set_key.u.ग_लिखो.addr, addr);

	/* swap over swap[0] and swap[1] to get correct ग_लिखो order */
	swap(set_key.u.swap[0], set_key.u.swap[1]);

	स_नकल(set_key.key, key, WLAN_KEY_LEN_CCMP);

	dev_dbg(&priv->usb->dev, "offset %d key ctl %d set key %24ph\n",
		offset, key_ctl, (u8 *)&set_key);

	वापस vnt_control_out(priv, MESSAGE_TYPE_SETKEY, offset,
			       (u16)key_idx, माप(काष्ठा vnt_mac_set_key),
			       (u8 *)&set_key);
पूर्ण

पूर्णांक vnt_mac_reg_bits_off(काष्ठा vnt_निजी *priv, u8 reg_ofs, u8 bits)
अणु
	u8 data[2];

	data[0] = 0;
	data[1] = bits;

	वापस vnt_control_out(priv, MESSAGE_TYPE_WRITE_MASK, reg_ofs,
			       MESSAGE_REQUEST_MACREG, ARRAY_SIZE(data), data);
पूर्ण

पूर्णांक vnt_mac_reg_bits_on(काष्ठा vnt_निजी *priv, u8 reg_ofs, u8 bits)
अणु
	u8 data[2];

	data[0] = bits;
	data[1] = bits;

	वापस vnt_control_out(priv, MESSAGE_TYPE_WRITE_MASK, reg_ofs,
			       MESSAGE_REQUEST_MACREG, ARRAY_SIZE(data), data);
पूर्ण

पूर्णांक vnt_mac_ग_लिखो_word(काष्ठा vnt_निजी *priv, u8 reg_ofs, u16 word)
अणु
	u8 data[2];

	data[0] = (u8)(word & 0xff);
	data[1] = (u8)(word >> 8);

	वापस vnt_control_out(priv, MESSAGE_TYPE_WRITE, reg_ofs,
			       MESSAGE_REQUEST_MACREG, ARRAY_SIZE(data), data);
पूर्ण

पूर्णांक vnt_mac_set_bssid_addr(काष्ठा vnt_निजी *priv, u8 *addr)
अणु
	वापस vnt_control_out(priv, MESSAGE_TYPE_WRITE, MAC_REG_BSSID0,
			       MESSAGE_REQUEST_MACREG, ETH_ALEN, addr);
पूर्ण

पूर्णांक vnt_mac_enable_protect_mode(काष्ठा vnt_निजी *priv)
अणु
	u8 data[2];

	data[0] = EnCFG_ProtectMd;
	data[1] = EnCFG_ProtectMd;

	वापस vnt_control_out(priv, MESSAGE_TYPE_WRITE_MASK, MAC_REG_ENCFG0,
			       MESSAGE_REQUEST_MACREG, ARRAY_SIZE(data), data);
पूर्ण

पूर्णांक vnt_mac_disable_protect_mode(काष्ठा vnt_निजी *priv)
अणु
	u8 data[2];

	data[0] = 0;
	data[1] = EnCFG_ProtectMd;

	वापस vnt_control_out(priv, MESSAGE_TYPE_WRITE_MASK, MAC_REG_ENCFG0,
			       MESSAGE_REQUEST_MACREG, ARRAY_SIZE(data), data);
पूर्ण

पूर्णांक vnt_mac_enable_barker_preamble_mode(काष्ठा vnt_निजी *priv)
अणु
	u8 data[2];

	data[0] = EnCFG_BarkerPream;
	data[1] = EnCFG_BarkerPream;

	वापस vnt_control_out(priv, MESSAGE_TYPE_WRITE_MASK, MAC_REG_ENCFG2,
			       MESSAGE_REQUEST_MACREG, ARRAY_SIZE(data), data);
पूर्ण

पूर्णांक vnt_mac_disable_barker_preamble_mode(काष्ठा vnt_निजी *priv)
अणु
	u8 data[2];

	data[0] = 0;
	data[1] = EnCFG_BarkerPream;

	वापस vnt_control_out(priv, MESSAGE_TYPE_WRITE_MASK, MAC_REG_ENCFG2,
			       MESSAGE_REQUEST_MACREG, ARRAY_SIZE(data), data);
पूर्ण

पूर्णांक vnt_mac_set_beacon_पूर्णांकerval(काष्ठा vnt_निजी *priv, u16 पूर्णांकerval)
अणु
	u8 data[2];

	data[0] = (u8)(पूर्णांकerval & 0xff);
	data[1] = (u8)(पूर्णांकerval >> 8);

	वापस vnt_control_out(priv, MESSAGE_TYPE_WRITE, MAC_REG_BI,
			       MESSAGE_REQUEST_MACREG, ARRAY_SIZE(data), data);
पूर्ण

पूर्णांक vnt_mac_set_led(काष्ठा vnt_निजी *priv, u8 state, u8 led)
अणु
	u8 data[2];

	data[0] = led;
	data[1] = state;

	वापस vnt_control_out(priv, MESSAGE_TYPE_WRITE_MASK, MAC_REG_PAPEDELAY,
			       MESSAGE_REQUEST_MACREG, ARRAY_SIZE(data), data);
पूर्ण
