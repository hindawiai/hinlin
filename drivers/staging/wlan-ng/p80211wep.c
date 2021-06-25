<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MPL-1.1)
/* src/p80211/p80211wep.c
 *
 * WEP encode/decode क्रम P80211.
 *
 * Copyright (C) 2002 AbsoluteValue Systems, Inc.  All Rights Reserved.
 * --------------------------------------------------------------------
 *
 * linux-wlan
 *
 *   The contents of this file are subject to the Mozilla Public
 *   License Version 1.1 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.mozilla.org/MPL/
 *
 *   Software distributed under the License is distributed on an "AS
 *   IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
 *   implied. See the License क्रम the specअगरic language governing
 *   rights and limitations under the License.
 *
 *   Alternatively, the contents of this file may be used under the
 *   terms of the GNU Public License version 2 (the "GPL"), in which
 *   हाल the provisions of the GPL are applicable instead of the
 *   above.  If you wish to allow the use of your version of this file
 *   only under the terms of the GPL and not to allow others to use
 *   your version of this file under the MPL, indicate your decision
 *   by deleting the provisions above and replace them with the notice
 *   and other provisions required by the GPL.  If you करो not delete
 *   the provisions above, a recipient may use your version of this
 *   file under either the MPL or the GPL.
 *
 * --------------------------------------------------------------------
 *
 * Inquiries regarding the linux-wlan Open Source project can be
 * made directly to:
 *
 * AbsoluteValue Systems Inc.
 * info@linux-wlan.com
 * http://www.linux-wlan.com
 *
 * --------------------------------------------------------------------
 *
 * Portions of the development of this software were funded by
 * Intersil Corporation as part of PRISM(R) chipset product development.
 *
 * --------------------------------------------------------------------
 */

/*================================================================*/
/* System Includes */

#समावेश <linux/crc32.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/wireless.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/kernel.h>
#समावेश "p80211hdr.h"
#समावेश "p80211types.h"
#समावेश "p80211msg.h"
#समावेश "p80211conv.h"
#समावेश "p80211netdev.h"

#घोषणा WEP_KEY(x)       (((x) & 0xC0) >> 6)

/* keylen in bytes! */

पूर्णांक wep_change_key(काष्ठा wlandevice *wlandev, पूर्णांक keynum, u8 *key, पूर्णांक keylen)
अणु
	अगर (keylen < 0)
		वापस -1;
	अगर (keylen >= MAX_KEYLEN)
		वापस -1;
	अगर (!key)
		वापस -1;
	अगर (keynum < 0)
		वापस -1;
	अगर (keynum >= NUM_WEPKEYS)
		वापस -1;

	wlandev->wep_keylens[keynum] = keylen;
	स_नकल(wlandev->wep_keys[keynum], key, keylen);

	वापस 0;
पूर्ण

/*
 * 4-byte IV at start of buffer, 4-byte ICV at end of buffer.
 * अगर successful, buf start is payload begin, length -= 8;
 */
पूर्णांक wep_decrypt(काष्ठा wlandevice *wlandev, u8 *buf, u32 len, पूर्णांक key_override,
		u8 *iv, u8 *icv)
अणु
	u32 i, j, k, crc, keylen;
	u8 s[256], key[64], c_crc[4];
	u8 keyidx;

	/* Needs to be at least 8 bytes of payload */
	अगर (len <= 0)
		वापस -1;

	/* initialize the first bytes of the key from the IV */
	key[0] = iv[0];
	key[1] = iv[1];
	key[2] = iv[2];
	keyidx = WEP_KEY(iv[3]);

	अगर (key_override >= 0)
		keyidx = key_override;

	अगर (keyidx >= NUM_WEPKEYS)
		वापस -2;

	keylen = wlandev->wep_keylens[keyidx];

	अगर (keylen == 0)
		वापस -3;

	/* copy the rest of the key over from the designated key */
	स_नकल(key + 3, wlandev->wep_keys[keyidx], keylen);

	keylen += 3;		/* add in IV bytes */

	/* set up the RC4 state */
	क्रम (i = 0; i < 256; i++)
		s[i] = i;
	j = 0;
	क्रम (i = 0; i < 256; i++) अणु
		j = (j + s[i] + key[i % keylen]) & 0xff;
		swap(i, j);
	पूर्ण

	/* Apply the RC4 to the data, update the CRC32 */
	i = 0;
	j = 0;
	क्रम (k = 0; k < len; k++) अणु
		i = (i + 1) & 0xff;
		j = (j + s[i]) & 0xff;
		swap(i, j);
		buf[k] ^= s[(s[i] + s[j]) & 0xff];
	पूर्ण
	crc = ~crc32_le(~0, buf, len);

	/* now let's check the crc */
	c_crc[0] = crc;
	c_crc[1] = crc >> 8;
	c_crc[2] = crc >> 16;
	c_crc[3] = crc >> 24;

	क्रम (k = 0; k < 4; k++) अणु
		i = (i + 1) & 0xff;
		j = (j + s[i]) & 0xff;
		swap(i, j);
		अगर ((c_crc[k] ^ s[(s[i] + s[j]) & 0xff]) != icv[k])
			वापस -(4 | (k << 4));	/* ICV mismatch */
	पूर्ण

	वापस 0;
पूर्ण

/* encrypts in-place. */
पूर्णांक wep_encrypt(काष्ठा wlandevice *wlandev, u8 *buf,
		u8 *dst, u32 len, पूर्णांक keynum, u8 *iv, u8 *icv)
अणु
	u32 i, j, k, crc, keylen;
	u8 s[256], key[64];

	/* no poपूर्णांक in WEPping an empty frame */
	अगर (len <= 0)
		वापस -1;

	/* we need to have a real key.. */
	अगर (keynum >= NUM_WEPKEYS)
		वापस -2;
	keylen = wlandev->wep_keylens[keynum];
	अगर (keylen <= 0)
		वापस -3;

	/* use a अक्रमom IV.  And skip known weak ones. */
	get_अक्रमom_bytes(iv, 3);
	जबतक ((iv[1] == 0xff) && (iv[0] >= 3) && (iv[0] < keylen))
		get_अक्रमom_bytes(iv, 3);

	iv[3] = (keynum & 0x03) << 6;

	key[0] = iv[0];
	key[1] = iv[1];
	key[2] = iv[2];

	/* copy the rest of the key over from the designated key */
	स_नकल(key + 3, wlandev->wep_keys[keynum], keylen);

	keylen += 3;		/* add in IV bytes */

	/* set up the RC4 state */
	क्रम (i = 0; i < 256; i++)
		s[i] = i;
	j = 0;
	क्रम (i = 0; i < 256; i++) अणु
		j = (j + s[i] + key[i % keylen]) & 0xff;
		swap(i, j);
	पूर्ण

	/* Update CRC32 then apply RC4 to the data */
	i = 0;
	j = 0;
	क्रम (k = 0; k < len; k++) अणु
		i = (i + 1) & 0xff;
		j = (j + s[i]) & 0xff;
		swap(i, j);
		dst[k] = buf[k] ^ s[(s[i] + s[j]) & 0xff];
	पूर्ण
	crc = ~crc32_le(~0, buf, len);

	/* now let's encrypt the crc */
	icv[0] = crc;
	icv[1] = crc >> 8;
	icv[2] = crc >> 16;
	icv[3] = crc >> 24;

	क्रम (k = 0; k < 4; k++) अणु
		i = (i + 1) & 0xff;
		j = (j + s[i]) & 0xff;
		swap(i, j);
		icv[k] ^= s[(s[i] + s[j]) & 0xff];
	पूर्ण

	वापस 0;
पूर्ण
