<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 * rtl871x_security.c
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 * Linux device driver क्रम RTL8192SU
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/

#घोषणा  _RTL871X_SECURITY_C_

#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/kref.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/circ_buf.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/atomic.h>
#समावेश <linux/crc32poly.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/ieee80211.h>

#समावेश "osdep_service.h"
#समावेश "drv_types.h"
#समावेश "osdep_intf.h"

/* =====WEP related===== */

काष्ठा arc4context अणु
	u32 x;
	u32 y;
	u8 state[256];
पूर्ण;

अटल व्योम arcfour_init(काष्ठा arc4context *parc4ctx, u8 *key, u32 key_len)
अणु
	u32	t, u;
	u32	keyindex;
	u32	stateindex;
	u8 *state;
	u32	counter;

	state = parc4ctx->state;
	parc4ctx->x = 0;
	parc4ctx->y = 0;
	क्रम (counter = 0; counter < 256; counter++)
		state[counter] = (u8)counter;
	keyindex = 0;
	stateindex = 0;
	क्रम (counter = 0; counter < 256; counter++) अणु
		t = state[counter];
		stateindex = (stateindex + key[keyindex] + t) & 0xff;
		u = state[stateindex];
		state[stateindex] = (u8)t;
		state[counter] = (u8)u;
		अगर (++keyindex >= key_len)
			keyindex = 0;
	पूर्ण
पूर्ण

अटल u32 arcfour_byte(काष्ठा arc4context *parc4ctx)
अणु
	u32 x;
	u32 y;
	u32 sx, sy;
	u8 *state;

	state = parc4ctx->state;
	x = (parc4ctx->x + 1) & 0xff;
	sx = state[x];
	y = (sx + parc4ctx->y) & 0xff;
	sy = state[y];
	parc4ctx->x = x;
	parc4ctx->y = y;
	state[y] = (u8)sx;
	state[x] = (u8)sy;
	वापस state[(sx + sy) & 0xff];
पूर्ण

अटल व्योम arcfour_encrypt(काष्ठा arc4context	*parc4ctx,
		     u8 *dest, u8 *src, u32 len)
अणु
	u32 i;

	क्रम (i = 0; i < len; i++)
		dest[i] = src[i] ^ (अचिन्हित अक्षर)arcfour_byte(parc4ctx);
पूर्ण

अटल sपूर्णांक bcrc32initialized;
अटल u32 crc32_table[256];

अटल u8 crc32_reverseBit(u8 data)
अणु
	वापस ((u8)(data << 7) & 0x80) | ((data << 5) & 0x40) | ((data << 3)
		 & 0x20) | ((data << 1) & 0x10) | ((data >> 1) & 0x08) |
		 ((data >> 3) & 0x04) | ((data >> 5) & 0x02) | ((data >> 7) &
		 0x01);
पूर्ण

अटल व्योम crc32_init(व्योम)
अणु
	sपूर्णांक i, j;
	u32 c;
	u8 *p = (u8 *)&c, *p1;
	u8 k;

	अगर (bcrc32initialized == 1)
		वापस;

	क्रम (i = 0; i < 256; ++i) अणु
		k = crc32_reverseBit((u8)i);
		क्रम (c = ((u32)k) << 24, j = 8; j > 0; --j)
			c = c & 0x80000000 ? (c << 1) ^ CRC32_POLY_BE : (c << 1);
		p1 = (u8 *)&crc32_table[i];
		p1[0] = crc32_reverseBit(p[3]);
		p1[1] = crc32_reverseBit(p[2]);
		p1[2] = crc32_reverseBit(p[1]);
		p1[3] = crc32_reverseBit(p[0]);
	पूर्ण
	bcrc32initialized = 1;
पूर्ण

अटल u32 अ_लोrc32(u8 *buf, u32 len)
अणु
	u8 *p;
	u32  crc;

	अगर (!bcrc32initialized)
		crc32_init();
	crc = 0xffffffff; /* preload shअगरt रेजिस्टर, per CRC-32 spec */
	क्रम (p = buf; len > 0; ++p, --len)
		crc = crc32_table[(crc ^ *p) & 0xff] ^ (crc >> 8);
	वापस ~crc;    /* transmit complement, per CRC-32 spec */
पूर्ण

/*
 * Need to consider the fragment situation
 */
व्योम r8712_wep_encrypt(काष्ठा _adapter *padapter, u8 *pxmitframe)
अणु	/* exclude ICV */
	अचिन्हित अक्षर	crc[4];
	काष्ठा arc4context  mycontext;
	u32 curfragnum, length, keylength, pki;
	u8 *pframe, *payload, *iv;    /*,*wepkey*/
	u8 wepkey[16];
	काष्ठा	pkt_attrib  *pattrib = &((काष्ठा xmit_frame *)
				       pxmitframe)->attrib;
	काष्ठा	security_priv *psecuritypriv = &padapter->securitypriv;
	काष्ठा	xmit_priv *pxmitpriv = &padapter->xmitpriv;

	अगर (((काष्ठा xmit_frame *)pxmitframe)->buf_addr == शून्य)
		वापस;
	pframe = ((काष्ठा xmit_frame *)pxmitframe)->buf_addr + TXDESC_OFFSET;
	/*start to encrypt each fragment*/
	अगर ((pattrib->encrypt == _WEP40_) || (pattrib->encrypt == _WEP104_)) अणु
		pki = psecuritypriv->PrivacyKeyIndex;
		keylength = psecuritypriv->DefKeylen[pki];
		क्रम (curfragnum = 0; curfragnum < pattrib->nr_frags;
		     curfragnum++) अणु
			iv = pframe + pattrib->hdrlen;
			स_नकल(&wepkey[0], iv, 3);
			स_नकल(&wepkey[3], &psecuritypriv->DefKey[
				psecuritypriv->PrivacyKeyIndex].skey[0],
				keylength);
			payload = pframe + pattrib->iv_len + pattrib->hdrlen;
			अगर ((curfragnum + 1) == pattrib->nr_frags) अणु
				length = pattrib->last_txcmdsz -
					pattrib->hdrlen -
					pattrib->iv_len -
					pattrib->icv_len;
				*((__le32 *)crc) = cpu_to_le32(अ_लोrc32(
						payload, length));
				arcfour_init(&mycontext, wepkey, 3 + keylength);
				arcfour_encrypt(&mycontext, payload, payload,
						length);
				arcfour_encrypt(&mycontext, payload + length,
						crc, 4);
			पूर्ण अन्यथा अणु
				length = pxmitpriv->frag_len -
					 pattrib->hdrlen - pattrib->iv_len -
					 pattrib->icv_len;
				*((__le32 *)crc) = cpu_to_le32(अ_लोrc32(
						payload, length));
				arcfour_init(&mycontext, wepkey, 3 + keylength);
				arcfour_encrypt(&mycontext, payload, payload,
						length);
				arcfour_encrypt(&mycontext, payload + length,
						crc, 4);
				pframe += pxmitpriv->frag_len;
				pframe = (u8 *)RND4((addr_t)(pframe));
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम r8712_wep_decrypt(काष्ठा _adapter  *padapter, u8 *precvframe)
अणु
	/* exclude ICV */
	u8 crc[4];
	काष्ठा arc4context  mycontext;
	u32 length, keylength;
	u8 *pframe, *payload, *iv, wepkey[16];
	u8  keyindex;
	काष्ठा rx_pkt_attrib  *prxattrib = &(((जोड़ recv_frame *)
					  precvframe)->u.hdr.attrib);
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;

	pframe = (अचिन्हित अक्षर *)((जोड़ recv_frame *)precvframe)->
		  u.hdr.rx_data;
	/* start to decrypt recvframe */
	अगर ((prxattrib->encrypt == _WEP40_) || (prxattrib->encrypt ==
	     _WEP104_)) अणु
		iv = pframe + prxattrib->hdrlen;
		keyindex = (iv[3] & 0x3);
		keylength = psecuritypriv->DefKeylen[keyindex];
		स_नकल(&wepkey[0], iv, 3);
		स_नकल(&wepkey[3], &psecuritypriv->DefKey[
			psecuritypriv->PrivacyKeyIndex].skey[0],
			keylength);
		length = ((जोड़ recv_frame *)precvframe)->
			   u.hdr.len - prxattrib->hdrlen - prxattrib->iv_len;
		payload = pframe + prxattrib->iv_len + prxattrib->hdrlen;
		/* decrypt payload include icv */
		arcfour_init(&mycontext, wepkey, 3 + keylength);
		arcfour_encrypt(&mycontext, payload, payload,  length);
		/* calculate icv and compare the icv */
		*((__le32 *)crc) = cpu_to_le32(अ_लोrc32(payload, length - 4));
	पूर्ण
पूर्ण

/* 3 =====TKIP related===== */

अटल u32 secmicgetuपूर्णांक32(u8 *p)
/* Convert from Byte[] to Us4Byte32 in a portable way */
अणु
	s32 i;
	u32 res = 0;

	क्रम (i = 0; i < 4; i++)
		res |= ((u32)(*p++)) << (8 * i);
	वापस res;
पूर्ण

अटल व्योम secmicputuपूर्णांक32(u8 *p, u32 val)
/* Convert from Us4Byte32 to Byte[] in a portable way */
अणु
	दीर्घ i;

	क्रम (i = 0; i < 4; i++) अणु
		*p++ = (u8)(val & 0xff);
		val >>= 8;
	पूर्ण
पूर्ण

अटल व्योम secmicclear(काष्ठा mic_data *pmicdata)
अणु
/* Reset the state to the empty message. */
	pmicdata->L = pmicdata->K0;
	pmicdata->R = pmicdata->K1;
	pmicdata->nBytesInM = 0;
	pmicdata->M = 0;
पूर्ण

व्योम r8712_secmicsetkey(काष्ठा mic_data *pmicdata, u8 *key)
अणु
	/* Set the key */
	pmicdata->K0 = secmicgetuपूर्णांक32(key);
	pmicdata->K1 = secmicgetuपूर्णांक32(key + 4);
	/* and reset the message */
	secmicclear(pmicdata);
पूर्ण

अटल व्योम secmicappendbyte(काष्ठा mic_data *pmicdata, u8 b)
अणु
	/* Append the byte to our word-sized buffer */
	pmicdata->M |= ((u32)b) << (8 * pmicdata->nBytesInM);
	pmicdata->nBytesInM++;
	/* Process the word अगर it is full. */
	अगर (pmicdata->nBytesInM >= 4) अणु
		pmicdata->L ^= pmicdata->M;
		pmicdata->R ^= ROL32(pmicdata->L, 17);
		pmicdata->L += pmicdata->R;
		pmicdata->R ^= ((pmicdata->L & 0xff00ff00) >> 8) |
			       ((pmicdata->L & 0x00ff00ff) << 8);
		pmicdata->L += pmicdata->R;
		pmicdata->R ^= ROL32(pmicdata->L, 3);
		pmicdata->L += pmicdata->R;
		pmicdata->R ^= ROR32(pmicdata->L, 2);
		pmicdata->L += pmicdata->R;
		/* Clear the buffer */
		pmicdata->M = 0;
		pmicdata->nBytesInM = 0;
	पूर्ण
पूर्ण

व्योम r8712_secmicappend(काष्ठा mic_data *pmicdata, u8 *src, u32 nbytes)
अणु
	/* This is simple */
	जबतक (nbytes > 0) अणु
		secmicappendbyte(pmicdata, *src++);
		nbytes--;
	पूर्ण
पूर्ण

व्योम r8712_secgeपंचांगic(काष्ठा mic_data *pmicdata, u8 *dst)
अणु
	/* Append the minimum padding */
	secmicappendbyte(pmicdata, 0x5a);
	secmicappendbyte(pmicdata, 0);
	secmicappendbyte(pmicdata, 0);
	secmicappendbyte(pmicdata, 0);
	secmicappendbyte(pmicdata, 0);
	/* and then zeroes until the length is a multiple of 4 */
	जबतक (pmicdata->nBytesInM != 0)
		secmicappendbyte(pmicdata, 0);
	/* The appendByte function has alपढ़ोy computed the result. */
	secmicputuपूर्णांक32(dst, pmicdata->L);
	secmicputuपूर्णांक32(dst + 4, pmicdata->R);
	/* Reset to the empty message. */
	secmicclear(pmicdata);
पूर्ण

व्योम seccalctkipmic(u8 *key, u8 *header, u8 *data, u32 data_len, u8 *mic_code,
		    u8 pri)
अणु

	काष्ठा mic_data	micdata;
	u8 priority[4] = अणु0x0, 0x0, 0x0, 0x0पूर्ण;

	r8712_secmicsetkey(&micdata, key);
	priority[0] = pri;
	/* Michael MIC pseuकरो header: DA, SA, 3 x 0, Priority */
	अगर (header[1] & 1) अणु   /* ToDS==1 */
		r8712_secmicappend(&micdata, &header[16], 6);  /* DA */
		अगर (header[1] & 2)  /* From Ds==1 */
			r8712_secmicappend(&micdata, &header[24], 6);
		अन्यथा
			r8712_secmicappend(&micdata, &header[10], 6);
	पूर्ण अन्यथा अणु	/* ToDS==0 */
		r8712_secmicappend(&micdata, &header[4], 6);   /* DA */
		अगर (header[1] & 2)  /* From Ds==1 */
			r8712_secmicappend(&micdata, &header[16], 6);
		अन्यथा
			r8712_secmicappend(&micdata, &header[10], 6);
	पूर्ण
	r8712_secmicappend(&micdata, &priority[0], 4);
	r8712_secmicappend(&micdata, data, data_len);
	r8712_secgeपंचांगic(&micdata, mic_code);
पूर्ण

/* macros क्रम extraction/creation of अचिन्हित अक्षर/अचिन्हित लघु values  */
#घोषणा RotR1(v16)   ((((v16) >> 1) & 0x7FFF) ^ (((v16) & 1) << 15))
#घोषणा   Lo8(v16)   ((u8)((v16) & 0x00FF))
#घोषणा   Hi8(v16)   ((u8)(((v16) >> 8) & 0x00FF))
#घोषणा  Lo16(v32)   ((u16)((v32) & 0xFFFF))
#घोषणा  Hi16(v32)   ((u16)(((v32) >> 16) & 0xFFFF))
#घोषणा  Mk16(hi, lo) ((lo) ^ (((u16)(hi)) << 8))

/* select the Nth 16-bit word of the temporal key अचिन्हित अक्षर array TK[]   */
#घोषणा  TK16(N)  Mk16(tk[2 * (N) + 1], tk[2 * (N)])

/* S-box lookup: 16 bits --> 16 bits */
#घोषणा _S_(v16)  (Sbox1[0][Lo8(v16)] ^ Sbox1[1][Hi8(v16)])

/* fixed algorithm "parameters" */
#घोषणा PHASE1_LOOP_CNT   8    /* this needs to be "big enough"     */
#घोषणा TA_SIZE           6    /*  48-bit transmitter address       */
#घोषणा TK_SIZE          16    /* 128-bit temporal key              */
#घोषणा P1K_SIZE         10    /*  80-bit Phase1 key                */
#घोषणा RC4_KEY_SIZE     16    /* 128-bit RC4KEY (104 bits unknown) */


/* 2-अचिन्हित अक्षर by 2-अचिन्हित अक्षर subset of the full AES S-box table */
अटल स्थिर अचिन्हित लघु Sbox1[2][256] = अणु/* Sbox क्रम hash (can be in ROM) */
	अणु
	0xC6A5, 0xF884, 0xEE99, 0xF68D, 0xFF0D, 0xD6BD, 0xDEB1, 0x9154,
	0x6050, 0x0203, 0xCEA9, 0x567D, 0xE719, 0xB562, 0x4DE6, 0xEC9A,
	0x8F45, 0x1F9D, 0x8940, 0xFA87, 0xEF15, 0xB2EB, 0x8EC9, 0xFB0B,
	0x41EC, 0xB367, 0x5FFD, 0x45EA, 0x23BF, 0x53F7, 0xE496, 0x9B5B,
	0x75C2, 0xE11C, 0x3DAE, 0x4C6A, 0x6C5A, 0x7E41, 0xF502, 0x834F,
	0x685C, 0x51F4, 0xD134, 0xF908, 0xE293, 0xAB73, 0x6253, 0x2A3F,
	0x080C, 0x9552, 0x4665, 0x9D5E, 0x3028, 0x37A1, 0x0A0F, 0x2FB5,
	0x0E09, 0x2436, 0x1B9B, 0xDF3D, 0xCD26, 0x4E69, 0x7FCD, 0xEA9F,
	0x121B, 0x1D9E, 0x5874, 0x342E, 0x362D, 0xDCB2, 0xB4EE, 0x5BFB,
	0xA4F6, 0x764D, 0xB761, 0x7DCE, 0x527B, 0xDD3E, 0x5E71, 0x1397,
	0xA6F5, 0xB968, 0x0000, 0xC12C, 0x4060, 0xE31F, 0x79C8, 0xB6ED,
	0xD4BE, 0x8D46, 0x67D9, 0x724B, 0x94DE, 0x98D4, 0xB0E8, 0x854A,
	0xBB6B, 0xC52A, 0x4FE5, 0xED16, 0x86C5, 0x9AD7, 0x6655, 0x1194,
	0x8ACF, 0xE910, 0x0406, 0xFE81, 0xA0F0, 0x7844, 0x25BA, 0x4BE3,
	0xA2F3, 0x5DFE, 0x80C0, 0x058A, 0x3FAD, 0x21BC, 0x7048, 0xF104,
	0x63DF, 0x77C1, 0xAF75, 0x4263, 0x2030, 0xE51A, 0xFD0E, 0xBF6D,
	0x814C, 0x1814, 0x2635, 0xC32F, 0xBEE1, 0x35A2, 0x88CC, 0x2E39,
	0x9357, 0x55F2, 0xFC82, 0x7A47, 0xC8AC, 0xBAE7, 0x322B, 0xE695,
	0xC0A0, 0x1998, 0x9ED1, 0xA37F, 0x4466, 0x547E, 0x3BAB, 0x0B83,
	0x8CCA, 0xC729, 0x6BD3, 0x283C, 0xA779, 0xBCE2, 0x161D, 0xAD76,
	0xDB3B, 0x6456, 0x744E, 0x141E, 0x92DB, 0x0C0A, 0x486C, 0xB8E4,
	0x9F5D, 0xBD6E, 0x43EF, 0xC4A6, 0x39A8, 0x31A4, 0xD337, 0xF28B,
	0xD532, 0x8B43, 0x6E59, 0xDAB7, 0x018C, 0xB164, 0x9CD2, 0x49E0,
	0xD8B4, 0xACFA, 0xF307, 0xCF25, 0xCAAF, 0xF48E, 0x47E9, 0x1018,
	0x6FD5, 0xF088, 0x4A6F, 0x5C72, 0x3824, 0x57F1, 0x73C7, 0x9751,
	0xCB23, 0xA17C, 0xE89C, 0x3E21, 0x96DD, 0x61DC, 0x0D86, 0x0F85,
	0xE090, 0x7C42, 0x71C4, 0xCCAA, 0x90D8, 0x0605, 0xF701, 0x1C12,
	0xC2A3, 0x6A5F, 0xAEF9, 0x69D0, 0x1791, 0x9958, 0x3A27, 0x27B9,
	0xD938, 0xEB13, 0x2BB3, 0x2233, 0xD2BB, 0xA970, 0x0789, 0x33A7,
	0x2DB6, 0x3C22, 0x1592, 0xC920, 0x8749, 0xAAFF, 0x5078, 0xA57A,
	0x038F, 0x59F8, 0x0980, 0x1A17, 0x65DA, 0xD731, 0x84C6, 0xD0B8,
	0x82C3, 0x29B0, 0x5A77, 0x1E11, 0x7BCB, 0xA8FC, 0x6DD6, 0x2C3A,
	पूर्ण,
	अणु  /* second half is अचिन्हित अक्षर-reversed version of first! */
	0xA5C6, 0x84F8, 0x99EE, 0x8DF6, 0x0DFF, 0xBDD6, 0xB1DE, 0x5491,
	0x5060, 0x0302, 0xA9CE, 0x7D56, 0x19E7, 0x62B5, 0xE64D, 0x9AEC,
	0x458F, 0x9D1F, 0x4089, 0x87FA, 0x15EF, 0xEBB2, 0xC98E, 0x0BFB,
	0xEC41, 0x67B3, 0xFD5F, 0xEA45, 0xBF23, 0xF753, 0x96E4, 0x5B9B,
	0xC275, 0x1CE1, 0xAE3D, 0x6A4C, 0x5A6C, 0x417E, 0x02F5, 0x4F83,
	0x5C68, 0xF451, 0x34D1, 0x08F9, 0x93E2, 0x73AB, 0x5362, 0x3F2A,
	0x0C08, 0x5295, 0x6546, 0x5E9D, 0x2830, 0xA137, 0x0F0A, 0xB52F,
	0x090E, 0x3624, 0x9B1B, 0x3DDF, 0x26CD, 0x694E, 0xCD7F, 0x9FEA,
	0x1B12, 0x9E1D, 0x7458, 0x2E34, 0x2D36, 0xB2DC, 0xEEB4, 0xFB5B,
	0xF6A4, 0x4D76, 0x61B7, 0xCE7D, 0x7B52, 0x3EDD, 0x715E, 0x9713,
	0xF5A6, 0x68B9, 0x0000, 0x2CC1, 0x6040, 0x1FE3, 0xC879, 0xEDB6,
	0xBED4, 0x468D, 0xD967, 0x4B72, 0xDE94, 0xD498, 0xE8B0, 0x4A85,
	0x6BBB, 0x2AC5, 0xE54F, 0x16ED, 0xC586, 0xD79A, 0x5566, 0x9411,
	0xCF8A, 0x10E9, 0x0604, 0x81FE, 0xF0A0, 0x4478, 0xBA25, 0xE34B,
	0xF3A2, 0xFE5D, 0xC080, 0x8A05, 0xAD3F, 0xBC21, 0x4870, 0x04F1,
	0xDF63, 0xC177, 0x75AF, 0x6342, 0x3020, 0x1AE5, 0x0EFD, 0x6DBF,
	0x4C81, 0x1418, 0x3526, 0x2FC3, 0xE1BE, 0xA235, 0xCC88, 0x392E,
	0x5793, 0xF255, 0x82FC, 0x477A, 0xACC8, 0xE7BA, 0x2B32, 0x95E6,
	0xA0C0, 0x9819, 0xD19E, 0x7FA3, 0x6644, 0x7E54, 0xAB3B, 0x830B,
	0xCA8C, 0x29C7, 0xD36B, 0x3C28, 0x79A7, 0xE2BC, 0x1D16, 0x76AD,
	0x3BDB, 0x5664, 0x4E74, 0x1E14, 0xDB92, 0x0A0C, 0x6C48, 0xE4B8,
	0x5D9F, 0x6EBD, 0xEF43, 0xA6C4, 0xA839, 0xA431, 0x37D3, 0x8BF2,
	0x32D5, 0x438B, 0x596E, 0xB7DA, 0x8C01, 0x64B1, 0xD29C, 0xE049,
	0xB4D8, 0xFAAC, 0x07F3, 0x25CF, 0xAFCA, 0x8EF4, 0xE947, 0x1810,
	0xD56F, 0x88F0, 0x6F4A, 0x725C, 0x2438, 0xF157, 0xC773, 0x5197,
	0x23CB, 0x7CA1, 0x9CE8, 0x213E, 0xDD96, 0xDC61, 0x860D, 0x850F,
	0x90E0, 0x427C, 0xC471, 0xAACC, 0xD890, 0x0506, 0x01F7, 0x121C,
	0xA3C2, 0x5F6A, 0xF9AE, 0xD069, 0x9117, 0x5899, 0x273A, 0xB927,
	0x38D9, 0x13EB, 0xB32B, 0x3322, 0xBBD2, 0x70A9, 0x8907, 0xA733,
	0xB62D, 0x223C, 0x9215, 0x20C9, 0x4987, 0xFFAA, 0x7850, 0x7AA5,
	0x8F03, 0xF859, 0x8009, 0x171A, 0xDA65, 0x31D7, 0xC684, 0xB8D0,
	0xC382, 0xB029, 0x775A, 0x111E, 0xCB7B, 0xFCA8, 0xD66D, 0x3A2C,
	पूर्ण
पूर्ण;

/*
 **********************************************************************
 * Routine: Phase 1 -- generate P1K, given TA, TK, IV32
 *
 * Inमाला_दो:
 *     tk[]      = temporal key                         [128 bits]
 *     ta[]      = transmitter's MAC address            [ 48 bits]
 *     iv32      = upper 32 bits of IV                  [ 32 bits]
 * Output:
 *     p1k[]     = Phase 1 key                          [ 80 bits]
 *
 * Note:
 *     This function only needs to be called every 2**16 packets,
 *     although in theory it could be called every packet.
 *
 **********************************************************************
 */
अटल व्योम phase1(u16 *p1k, स्थिर u8 *tk, स्थिर u8 *ta, u32 iv32)
अणु
	sपूर्णांक  i;

	/* Initialize the 80 bits of P1K[] from IV32 and TA[0..5]     */
	p1k[0] = Lo16(iv32);
	p1k[1] = Hi16(iv32);
	p1k[2] = Mk16(ta[1], ta[0]); /* use TA[] as little-endian */
	p1k[3] = Mk16(ta[3], ta[2]);
	p1k[4] = Mk16(ta[5], ta[4]);
	/* Now compute an unbalanced Feistel cipher with 80-bit block */
	/* size on the 80-bit block P1K[], using the 128-bit key TK[] */
	क्रम (i = 0; i < PHASE1_LOOP_CNT; i++) अणु  /* Each add is mod 2**16 */
		p1k[0] += _S_(p1k[4] ^ TK16((i & 1) + 0));
		p1k[1] += _S_(p1k[0] ^ TK16((i & 1) + 2));
		p1k[2] += _S_(p1k[1] ^ TK16((i & 1) + 4));
		p1k[3] += _S_(p1k[2] ^ TK16((i & 1) + 6));
		p1k[4] += _S_(p1k[3] ^ TK16((i & 1) + 0));
		p1k[4] +=  (अचिन्हित लघु)i;	/* aव्योम "slide attacks" */
	पूर्ण
पूर्ण

/*
 **********************************************************************
 * Routine: Phase 2 -- generate RC4KEY, given TK, P1K, IV16
 *
 * Inमाला_दो:
 *     tk[]      = Temporal key                         [128 bits]
 *     p1k[]     = Phase 1 output key                   [ 80 bits]
 *     iv16      = low 16 bits of IV counter            [ 16 bits]
 * Output:
 *     rc4key[]  = the key used to encrypt the packet   [128 bits]
 *
 * Note:
 *     The value अणुTA,IV32,IV16पूर्ण क्रम Phase1/Phase2 must be unique
 *     across all packets using the same key TK value. Then, क्रम a
 *     given value of TK[], this TKIP48 स्थिरruction guarantees that
 *     the final RC4KEY value is unique across all packets.
 *
 * Suggested implementation optimization: अगर PPK[] is "overlaid"
 *     appropriately on RC4KEY[], there is no need क्रम the final
 *     क्रम loop below that copies the PPK[] result पूर्णांकo RC4KEY[].
 *
 **********************************************************************
 */
अटल व्योम phase2(u8 *rc4key, स्थिर u8 *tk, स्थिर u16 *p1k, u16 iv16)
अणु
	sपूर्णांक  i;
	u16 PPK[6];			/* temporary key क्रम mixing    */

	/* Note: all adds in the PPK[] equations below are mod 2**16 */
	क्रम (i = 0; i < 5; i++)
		PPK[i] = p1k[i]; /* first, copy P1K to PPK */
	PPK[5]  =  p1k[4] + iv16; /* next,  add in IV16 */
	/* Bijective non-linear mixing of the 96 bits of PPK[0..5] */
	PPK[0] += _S_(PPK[5] ^ TK16(0));   /* Mix key in each "round" */
	PPK[1] += _S_(PPK[0] ^ TK16(1));
	PPK[2] += _S_(PPK[1] ^ TK16(2));
	PPK[3] += _S_(PPK[2] ^ TK16(3));
	PPK[4] += _S_(PPK[3] ^ TK16(4));
	PPK[5] += _S_(PPK[4] ^ TK16(5));   /* Total # S-box lookups == 6  */
	/* Final sweep: bijective, "linear". Rotates समाप्त LSB correlations   */
	PPK[0] +=  RotR1(PPK[5] ^ TK16(6));
	PPK[1] +=  RotR1(PPK[0] ^ TK16(7));   /* Use all of TK[] in Phase2   */
	PPK[2] +=  RotR1(PPK[1]);
	PPK[3] +=  RotR1(PPK[2]);
	PPK[4] +=  RotR1(PPK[3]);
	PPK[5] +=  RotR1(PPK[4]);
	/* Note: At this poपूर्णांक, क्रम a given key TK[0..15], the 96-bit output */
	/* value PPK[0..5] is guaranteed to be unique, as a function   */
	/* of the 96-bit "input" value   अणुTA,IV32,IV16पूर्ण. That is, P1K  */
	/* is now a keyed permutation of अणुTA,IV32,IV16पूर्ण. */
	/* Set RC4KEY[0..3], which includes "cleartext" portion of RC4 key   */
	rc4key[0] = Hi8(iv16); /* RC4KEY[0..2] is the WEP IV  */
	rc4key[1] = (Hi8(iv16) | 0x20) & 0x7F; /* Help aव्योम weak (FMS) keys  */
	rc4key[2] = Lo8(iv16);
	rc4key[3] = Lo8((PPK[5] ^ TK16(0)) >> 1);
	/* Copy 96 bits of PPK[0..5] to RC4KEY[4..15]  (little-endian) */
	क्रम (i = 0; i < 6; i++) अणु
		rc4key[4 + 2 * i] = Lo8(PPK[i]);
		rc4key[5 + 2 * i] = Hi8(PPK[i]);
	पूर्ण
पूर्ण

/*The hlen isn't include the IV*/
u32 r8712_tkip_encrypt(काष्ठा _adapter *padapter, u8 *pxmitframe)
अणु	/*  exclude ICV */
	u16 pnl;
	u32 pnh;
	u8 rc4key[16];
	u8 ttkey[16];
	u8 crc[4];
	काष्ठा arc4context mycontext;
	u32 curfragnum, length;

	u8 *pframe, *payload, *iv, *prwskey;
	जोड़ pn48 txpn;
	काष्ठा sta_info *stainfo;
	काष्ठा pkt_attrib *pattrib = &((काष्ठा xmit_frame *)pxmitframe)->attrib;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	u32 res = _SUCCESS;

	अगर (((काष्ठा xmit_frame *)pxmitframe)->buf_addr == शून्य)
		वापस _FAIL;

	pframe = ((काष्ठा xmit_frame *)pxmitframe)->buf_addr + TXDESC_OFFSET;
	/* 4 start to encrypt each fragment */
	अगर (pattrib->encrypt == _TKIP_) अणु
		अगर (pattrib->psta)
			stainfo = pattrib->psta;
		अन्यथा
			stainfo = r8712_get_stainfo(&padapter->stapriv,
				  &pattrib->ra[0]);
		अगर (stainfo) अणु
			prwskey = &stainfo->x_UncstKey.skey[0];
			क्रम (curfragnum = 0; curfragnum < pattrib->nr_frags;
			     curfragnum++) अणु
				iv = pframe + pattrib->hdrlen;
				payload = pframe + pattrib->iv_len +
					  pattrib->hdrlen;
				GET_TKIP_PN(iv, txpn);
				pnl = (u16)(txpn.val);
				pnh = (u32)(txpn.val >> 16);
				phase1((u16 *)&ttkey[0], prwskey,
				       &pattrib->ta[0], pnh);
				phase2(&rc4key[0], prwskey, (u16 *)&ttkey[0],
				       pnl);
				अगर ((curfragnum + 1) == pattrib->nr_frags) अणु
					/* 4 the last fragment */
					length = pattrib->last_txcmdsz -
					     pattrib->hdrlen -
					     pattrib->iv_len -
					     pattrib->icv_len;
					*((__le32 *)crc) = cpu_to_le32(
						अ_लोrc32(payload, length));
					arcfour_init(&mycontext, rc4key, 16);
					arcfour_encrypt(&mycontext, payload,
							payload, length);
					arcfour_encrypt(&mycontext, payload +
							length, crc, 4);
				पूर्ण अन्यथा अणु
					length = pxmitpriv->frag_len -
						 pattrib->hdrlen -
						 pattrib->iv_len -
						 pattrib->icv_len;
					*((__le32 *)crc) = cpu_to_le32(अ_लोrc32(
							payload, length));
					arcfour_init(&mycontext, rc4key, 16);
					arcfour_encrypt(&mycontext, payload,
							 payload, length);
					arcfour_encrypt(&mycontext,
							payload + length, crc,
							4);
					pframe += pxmitpriv->frag_len;
					pframe = (u8 *)RND4((addr_t)(pframe));
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			res = _FAIL;
		पूर्ण
	पूर्ण
	वापस res;
पूर्ण

/* The hlen करोesn't include the IV */
व्योम r8712_tkip_decrypt(काष्ठा _adapter *padapter, u8 *precvframe)
अणु	/* exclude ICV */
	u16 pnl;
	u32 pnh;
	u8 rc4key[16];
	u8 ttkey[16];
	u8 crc[4];
	काष्ठा arc4context mycontext;
	u32 length;
	u8 *pframe, *payload, *iv, *prwskey, idx = 0;
	जोड़ pn48 txpn;
	काष्ठा	sta_info *stainfo;
	काष्ठा	rx_pkt_attrib *prxattrib = &((जोड़ recv_frame *)
					   precvframe)->u.hdr.attrib;
	काष्ठा	security_priv	*psecuritypriv = &padapter->securitypriv;

	pframe = (अचिन्हित अक्षर *)((जोड़ recv_frame *)
				   precvframe)->u.hdr.rx_data;
	/* 4 start to decrypt recvframe */
	अगर (prxattrib->encrypt == _TKIP_) अणु
		stainfo = r8712_get_stainfo(&padapter->stapriv,
					    &prxattrib->ta[0]);
		अगर (stainfo) अणु
			iv = pframe + prxattrib->hdrlen;
			payload = pframe + prxattrib->iv_len +
				  prxattrib->hdrlen;
			length = ((जोड़ recv_frame *)precvframe)->
				 u.hdr.len - prxattrib->hdrlen -
				 prxattrib->iv_len;
			अगर (is_multicast_ether_addr(prxattrib->ra)) अणु
				idx = iv[3];
				prwskey = &psecuritypriv->XGrpKey[
					 ((idx >> 6) & 0x3) - 1].skey[0];
				अगर (!psecuritypriv->binstallGrpkey)
					वापस;
			पूर्ण अन्यथा अणु
				prwskey = &stainfo->x_UncstKey.skey[0];
			पूर्ण
			GET_TKIP_PN(iv, txpn);
			pnl = (u16)(txpn.val);
			pnh = (u32)(txpn.val >> 16);
			phase1((u16 *)&ttkey[0], prwskey, &prxattrib->ta[0],
				pnh);
			phase2(&rc4key[0], prwskey, (अचिन्हित लघु *)
			       &ttkey[0], pnl);
			/* 4 decrypt payload include icv */
			arcfour_init(&mycontext, rc4key, 16);
			arcfour_encrypt(&mycontext, payload, payload, length);
			*((__le32 *)crc) = cpu_to_le32(अ_लोrc32(payload,
					length - 4));
		पूर्ण
	पूर्ण
पूर्ण

/* 3 =====AES related===== */

#घोषणा MAX_MSG_SIZE	2048
/*****************************/
/******** SBOX Table *********/
/*****************************/

अटल स्थिर u8 sbox_table[256] = अणु
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5,
	0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0,
	0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc,
	0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a,
	0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0,
	0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b,
	0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85,
	0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5,
	0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17,
	0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88,
	0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c,
	0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9,
	0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6,
	0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e,
	0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94,
	0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68,
	0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
पूर्ण;

/****************************************/
/* aes128k128d()                        */
/* Perक्रमms a 128 bit AES encrypt with  */
/* 128 bit data.                        */
/****************************************/
अटल व्योम xor_128(u8 *a, u8 *b, u8 *out)
अणु
	sपूर्णांक i;

	क्रम (i = 0; i < 16; i++)
		out[i] = a[i] ^ b[i];
पूर्ण

अटल व्योम xor_32(u8 *a, u8 *b, u8 *out)
अणु
	sपूर्णांक i;

	क्रम (i = 0; i < 4; i++)
		out[i] = a[i] ^ b[i];
पूर्ण

अटल u8 sbox(u8 a)
अणु
	वापस sbox_table[(sपूर्णांक)a];
पूर्ण

अटल व्योम next_key(u8 *key, sपूर्णांक round)
अणु
	u8 rcon;
	u8 sbox_key[4];
	अटल स्थिर u8 rcon_table[12] = अणु
		0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80,
		0x1b, 0x36, 0x36, 0x36
	पूर्ण;

	sbox_key[0] = sbox(key[13]);
	sbox_key[1] = sbox(key[14]);
	sbox_key[2] = sbox(key[15]);
	sbox_key[3] = sbox(key[12]);
	rcon = rcon_table[round];
	xor_32(&key[0], sbox_key, &key[0]);
	key[0] = key[0] ^ rcon;
	xor_32(&key[4], &key[0], &key[4]);
	xor_32(&key[8], &key[4], &key[8]);
	xor_32(&key[12], &key[8], &key[12]);
पूर्ण

अटल व्योम byte_sub(u8 *in, u8 *out)
अणु
	sपूर्णांक i;

	क्रम (i = 0; i < 16; i++)
		out[i] = sbox(in[i]);
पूर्ण

अटल व्योम shअगरt_row(u8 *in, u8 *out)
अणु
	out[0] =  in[0];
	out[1] =  in[5];
	out[2] =  in[10];
	out[3] =  in[15];
	out[4] =  in[4];
	out[5] =  in[9];
	out[6] =  in[14];
	out[7] =  in[3];
	out[8] =  in[8];
	out[9] =  in[13];
	out[10] = in[2];
	out[11] = in[7];
	out[12] = in[12];
	out[13] = in[1];
	out[14] = in[6];
	out[15] = in[11];
पूर्ण

अटल व्योम mix_column(u8 *in, u8 *out)
अणु
	sपूर्णांक i;
	u8 add1b[4];
	u8 add1bf7[4];
	u8 rotl[4];
	u8 swap_halves[4];
	u8 andf7[4];
	u8 rotr[4];
	u8 temp[4];
	u8 tempb[4];

	क्रम (i = 0; i < 4; i++) अणु
		अगर ((in[i] & 0x80) == 0x80)
			add1b[i] = 0x1b;
		अन्यथा
			add1b[i] = 0x00;
	पूर्ण
	swap_halves[0] = in[2];    /* Swap halves */
	swap_halves[1] = in[3];
	swap_halves[2] = in[0];
	swap_halves[3] = in[1];
	rotl[0] = in[3];        /* Rotate left 8 bits */
	rotl[1] = in[0];
	rotl[2] = in[1];
	rotl[3] = in[2];
	andf7[0] = in[0] & 0x7f;
	andf7[1] = in[1] & 0x7f;
	andf7[2] = in[2] & 0x7f;
	andf7[3] = in[3] & 0x7f;
	क्रम (i = 3; i > 0; i--) अणु   /* logical shअगरt left 1 bit */
		andf7[i] = andf7[i] << 1;
		अगर ((andf7[i - 1] & 0x80) == 0x80)
			andf7[i] = (andf7[i] | 0x01);
	पूर्ण
	andf7[0] = andf7[0] << 1;
	andf7[0] = andf7[0] & 0xfe;
	xor_32(add1b, andf7, add1bf7);
	xor_32(in, add1bf7, rotr);
	temp[0] = rotr[0];         /* Rotate right 8 bits */
	rotr[0] = rotr[1];
	rotr[1] = rotr[2];
	rotr[2] = rotr[3];
	rotr[3] = temp[0];
	xor_32(add1bf7, rotr, temp);
	xor_32(swap_halves, rotl, tempb);
	xor_32(temp, tempb, out);
पूर्ण

अटल व्योम aes128k128d(u8 *key, u8 *data, u8 *ciphertext)
अणु
	sपूर्णांक round;
	sपूर्णांक i;
	u8 पूर्णांकermediatea[16];
	u8 पूर्णांकermediateb[16];
	u8 round_key[16];

	क्रम (i = 0; i < 16; i++)
		round_key[i] = key[i];
	क्रम (round = 0; round < 11; round++) अणु
		अगर (round == 0) अणु
			xor_128(round_key, data, ciphertext);
			next_key(round_key, round);
		पूर्ण अन्यथा अगर (round == 10) अणु
			byte_sub(ciphertext, पूर्णांकermediatea);
			shअगरt_row(पूर्णांकermediatea, पूर्णांकermediateb);
			xor_128(पूर्णांकermediateb, round_key, ciphertext);
		पूर्ण अन्यथा अणु   /* 1 - 9 */
			byte_sub(ciphertext, पूर्णांकermediatea);
			shअगरt_row(पूर्णांकermediatea, पूर्णांकermediateb);
			mix_column(&पूर्णांकermediateb[0], &पूर्णांकermediatea[0]);
			mix_column(&पूर्णांकermediateb[4], &पूर्णांकermediatea[4]);
			mix_column(&पूर्णांकermediateb[8], &पूर्णांकermediatea[8]);
			mix_column(&पूर्णांकermediateb[12], &पूर्णांकermediatea[12]);
			xor_128(पूर्णांकermediatea, round_key, ciphertext);
			next_key(round_key, round);
		पूर्ण
	पूर्ण
पूर्ण

/************************************************/
/* स्थिरruct_mic_iv()                           */
/* Builds the MIC IV from header fields and PN  */
/************************************************/
अटल व्योम स्थिरruct_mic_iv(u8 *mic_iv, sपूर्णांक qc_exists, sपूर्णांक a4_exists,
			     u8 *mpdu, uपूर्णांक payload_length, u8 *pn_vector)
अणु
	sपूर्णांक i;

	mic_iv[0] = 0x59;
	अगर (qc_exists && a4_exists)
		mic_iv[1] = mpdu[30] & 0x0f;    /* QoS_TC           */
	अगर (qc_exists && !a4_exists)
		mic_iv[1] = mpdu[24] & 0x0f;   /* mute bits 7-4    */
	अगर (!qc_exists)
		mic_iv[1] = 0x00;
	क्रम (i = 2; i < 8; i++)
		mic_iv[i] = mpdu[i + 8];
	क्रम (i = 8; i < 14; i++)
		mic_iv[i] = pn_vector[13 - i]; /* mic_iv[8:13] = PN[5:0] */
	mic_iv[14] = (अचिन्हित अक्षर)(payload_length / 256);
	mic_iv[15] = (अचिन्हित अक्षर)(payload_length % 256);
पूर्ण

/************************************************/
/* स्थिरruct_mic_header1()                      */
/* Builds the first MIC header block from       */
/* header fields.                               */
/************************************************/
अटल व्योम स्थिरruct_mic_header1(u8 *mic_header1, sपूर्णांक header_length, u8 *mpdu)
अणु
	mic_header1[0] = (u8)((header_length - 2) / 256);
	mic_header1[1] = (u8)((header_length - 2) % 256);
	mic_header1[2] = mpdu[0] & 0xcf;    /* Mute CF poll & CF ack bits */
	/* Mute retry, more data and pwr mgt bits */
	mic_header1[3] = mpdu[1] & 0xc7;
	mic_header1[4] = mpdu[4];       /* A1 */
	mic_header1[5] = mpdu[5];
	mic_header1[6] = mpdu[6];
	mic_header1[7] = mpdu[7];
	mic_header1[8] = mpdu[8];
	mic_header1[9] = mpdu[9];
	mic_header1[10] = mpdu[10];     /* A2 */
	mic_header1[11] = mpdu[11];
	mic_header1[12] = mpdu[12];
	mic_header1[13] = mpdu[13];
	mic_header1[14] = mpdu[14];
	mic_header1[15] = mpdu[15];
पूर्ण

/************************************************/
/* स्थिरruct_mic_header2()                      */
/* Builds the last MIC header block from        */
/* header fields.                               */
/************************************************/
अटल व्योम स्थिरruct_mic_header2(u8 *mic_header2, u8 *mpdu, sपूर्णांक a4_exists,
			   sपूर्णांक qc_exists)
अणु
	sपूर्णांक i;

	क्रम (i = 0; i < 16; i++)
		mic_header2[i] = 0x00;
	mic_header2[0] = mpdu[16];    /* A3 */
	mic_header2[1] = mpdu[17];
	mic_header2[2] = mpdu[18];
	mic_header2[3] = mpdu[19];
	mic_header2[4] = mpdu[20];
	mic_header2[5] = mpdu[21];
	mic_header2[6] = 0x00;
	mic_header2[7] = 0x00; /* mpdu[23]; */
	अगर (!qc_exists && a4_exists)
		क्रम (i = 0; i < 6; i++)
			mic_header2[8 + i] = mpdu[24 + i];   /* A4 */
	अगर (qc_exists && !a4_exists) अणु
		mic_header2[8] = mpdu[24] & 0x0f; /* mute bits 15 - 4 */
		mic_header2[9] = mpdu[25] & 0x00;
	पूर्ण
	अगर (qc_exists && a4_exists) अणु
		क्रम (i = 0; i < 6; i++)
			mic_header2[8 + i] = mpdu[24 + i];   /* A4 */
		mic_header2[14] = mpdu[30] & 0x0f;
		mic_header2[15] = mpdu[31] & 0x00;
	पूर्ण
पूर्ण

/************************************************/
/* स्थिरruct_mic_header2()                      */
/* Builds the last MIC header block from        */
/* header fields.                               */
/************************************************/
अटल व्योम स्थिरruct_ctr_preload(u8 *ctr_preload,
				  sपूर्णांक a4_exists, sपूर्णांक qc_exists,
				  u8 *mpdu, u8 *pn_vector, sपूर्णांक c)
अणु
	sपूर्णांक i;

	क्रम (i = 0; i < 16; i++)
		ctr_preload[i] = 0x00;
	i = 0;
	ctr_preload[0] = 0x01;    /* flag */
	अगर (qc_exists && a4_exists)
		ctr_preload[1] = mpdu[30] & 0x0f;
	अगर (qc_exists && !a4_exists)
		ctr_preload[1] = mpdu[24] & 0x0f;
	क्रम (i = 2; i < 8; i++)
		ctr_preload[i] = mpdu[i + 8];
	क्रम (i = 8; i < 14; i++)
		ctr_preload[i] = pn_vector[13 - i];
	ctr_preload[14] = (अचिन्हित अक्षर)(c / 256); /* Ctr */
	ctr_preload[15] = (अचिन्हित अक्षर)(c % 256);
पूर्ण

/************************************/
/* bitwise_xor()                    */
/* A 128 bit, bitwise exclusive or  */
/************************************/
अटल व्योम bitwise_xor(u8 *ina, u8 *inb, u8 *out)
अणु
	sपूर्णांक i;

	क्रम (i = 0; i < 16; i++)
		out[i] = ina[i] ^ inb[i];
पूर्ण

अटल व्योम aes_cipher(u8 *key, uपूर्णांक hdrlen,
		       u8 *pframe, uपूर्णांक plen)
अणु
	uपूर्णांक qc_exists, a4_exists, i, j, payload_reमुख्यder;
	uपूर्णांक num_blocks, payload_index;

	u8 pn_vector[6];
	u8 mic_iv[16];
	u8 mic_header1[16];
	u8 mic_header2[16];
	u8 ctr_preload[16];

	/* Intermediate Buffers */
	u8 chain_buffer[16];
	u8 aes_out[16];
	u8 padded_buffer[16];
	u8 mic[8];
	u16 frtype  = GetFrameType(pframe);
	u16 frsubtype  = GetFrameSubType(pframe);

	frsubtype >>= 4;
	स_रखो((व्योम *)mic_iv, 0, 16);
	स_रखो((व्योम *)mic_header1, 0, 16);
	स_रखो((व्योम *)mic_header2, 0, 16);
	स_रखो((व्योम *)ctr_preload, 0, 16);
	स_रखो((व्योम *)chain_buffer, 0, 16);
	स_रखो((व्योम *)aes_out, 0, 16);
	स_रखो((व्योम *)padded_buffer, 0, 16);

	अगर ((hdrlen == WLAN_HDR_A3_LEN) || (hdrlen ==  WLAN_HDR_A3_QOS_LEN))
		a4_exists = 0;
	अन्यथा
		a4_exists = 1;

	अगर ((frtype == IEEE80211_STYPE_DATA_CFACK) ||
	    (frtype == IEEE80211_STYPE_DATA_CFPOLL) ||
	    (frtype == IEEE80211_STYPE_DATA_CFACKPOLL)) अणु
		qc_exists = 1;
		अगर (hdrlen !=  WLAN_HDR_A3_QOS_LEN)
			hdrlen += 2;
	पूर्ण अन्यथा अगर ((frsubtype == 0x08) ||
		   (frsubtype == 0x09) ||
		   (frsubtype == 0x0a) ||
		   (frsubtype == 0x0b)) अणु
		अगर (hdrlen !=  WLAN_HDR_A3_QOS_LEN)
			hdrlen += 2;
		qc_exists = 1;
	पूर्ण अन्यथा अणु
		qc_exists = 0;
	पूर्ण
	pn_vector[0] = pframe[hdrlen];
	pn_vector[1] = pframe[hdrlen + 1];
	pn_vector[2] = pframe[hdrlen + 4];
	pn_vector[3] = pframe[hdrlen + 5];
	pn_vector[4] = pframe[hdrlen + 6];
	pn_vector[5] = pframe[hdrlen + 7];
	स्थिरruct_mic_iv(mic_iv, qc_exists, a4_exists, pframe, plen, pn_vector);
	स्थिरruct_mic_header1(mic_header1, hdrlen, pframe);
	स्थिरruct_mic_header2(mic_header2, pframe, a4_exists, qc_exists);
	payload_reमुख्यder = plen % 16;
	num_blocks = plen / 16;
	/* Find start of payload */
	payload_index = hdrlen + 8;
	/* Calculate MIC */
	aes128k128d(key, mic_iv, aes_out);
	bitwise_xor(aes_out, mic_header1, chain_buffer);
	aes128k128d(key, chain_buffer, aes_out);
	bitwise_xor(aes_out, mic_header2, chain_buffer);
	aes128k128d(key, chain_buffer, aes_out);
	क्रम (i = 0; i < num_blocks; i++) अणु
		bitwise_xor(aes_out, &pframe[payload_index], chain_buffer);
		payload_index += 16;
		aes128k128d(key, chain_buffer, aes_out);
	पूर्ण
	/* Add on the final payload block अगर it needs padding */
	अगर (payload_reमुख्यder > 0) अणु
		क्रम (j = 0; j < 16; j++)
			padded_buffer[j] = 0x00;
		क्रम (j = 0; j < payload_reमुख्यder; j++)
			padded_buffer[j] = pframe[payload_index++];
		bitwise_xor(aes_out, padded_buffer, chain_buffer);
		aes128k128d(key, chain_buffer, aes_out);
	पूर्ण
	क्रम (j = 0; j < 8; j++)
		mic[j] = aes_out[j];
	/* Insert MIC पूर्णांकo payload */
	क्रम (j = 0; j < 8; j++)
		pframe[payload_index + j] = mic[j];
	payload_index = hdrlen + 8;
	क्रम (i = 0; i < num_blocks; i++) अणु
		स्थिरruct_ctr_preload(ctr_preload, a4_exists, qc_exists,
				      pframe, pn_vector, i + 1);
		aes128k128d(key, ctr_preload, aes_out);
		bitwise_xor(aes_out, &pframe[payload_index], chain_buffer);
		क्रम (j = 0; j < 16; j++)
			pframe[payload_index++] = chain_buffer[j];
	पूर्ण
	अगर (payload_reमुख्यder > 0) अणु  /* If लघु final block, then pad it,*/
				      /* encrypt and copy unpadded part back */
		स्थिरruct_ctr_preload(ctr_preload, a4_exists, qc_exists,
				      pframe, pn_vector, num_blocks + 1);
		क्रम (j = 0; j < 16; j++)
			padded_buffer[j] = 0x00;
		क्रम (j = 0; j < payload_reमुख्यder; j++)
			padded_buffer[j] = pframe[payload_index + j];
		aes128k128d(key, ctr_preload, aes_out);
		bitwise_xor(aes_out, padded_buffer, chain_buffer);
		क्रम (j = 0; j < payload_reमुख्यder; j++)
			pframe[payload_index++] = chain_buffer[j];
	पूर्ण
	/* Encrypt the MIC */
	स्थिरruct_ctr_preload(ctr_preload, a4_exists, qc_exists,
			      pframe, pn_vector, 0);
	क्रम (j = 0; j < 16; j++)
		padded_buffer[j] = 0x00;
	क्रम (j = 0; j < 8; j++)
		padded_buffer[j] = pframe[j + hdrlen + 8 + plen];
	aes128k128d(key, ctr_preload, aes_out);
	bitwise_xor(aes_out, padded_buffer, chain_buffer);
	क्रम (j = 0; j < 8; j++)
		pframe[payload_index++] = chain_buffer[j];
पूर्ण

u32 r8712_aes_encrypt(काष्ठा _adapter *padapter, u8 *pxmitframe)
अणु	/* exclude ICV */
	/* Intermediate Buffers */
	sपूर्णांक	curfragnum, length;
	u8	*pframe, *prwskey;
	काष्ठा	sta_info *stainfo;
	काष्ठा	pkt_attrib  *pattrib = &((काष्ठा xmit_frame *)
				       pxmitframe)->attrib;
	काष्ठा	xmit_priv *pxmitpriv = &padapter->xmitpriv;
	u32 res = _SUCCESS;

	अगर (((काष्ठा xmit_frame *)pxmitframe)->buf_addr == शून्य)
		वापस _FAIL;
	pframe = ((काष्ठा xmit_frame *)pxmitframe)->buf_addr + TXDESC_OFFSET;
	/* 4 start to encrypt each fragment */
	अगर (pattrib->encrypt == _AES_) अणु
		अगर (pattrib->psta)
			stainfo = pattrib->psta;
		अन्यथा
			stainfo = r8712_get_stainfo(&padapter->stapriv,
				  &pattrib->ra[0]);
		अगर (stainfo) अणु
			prwskey = &stainfo->x_UncstKey.skey[0];
			क्रम (curfragnum = 0; curfragnum < pattrib->nr_frags;
			     curfragnum++) अणु
				अगर ((curfragnum + 1) == pattrib->nr_frags) अणु
					length = pattrib->last_txcmdsz -
						 pattrib->hdrlen -
						 pattrib->iv_len -
						 pattrib->icv_len;
					aes_cipher(prwskey, pattrib->hdrlen,
						   pframe, length);
				पूर्ण अन्यथा अणु
					length = pxmitpriv->frag_len -
						 pattrib->hdrlen -
						 pattrib->iv_len -
						 pattrib->icv_len;
					aes_cipher(prwskey, pattrib->hdrlen,
						   pframe, length);
					pframe += pxmitpriv->frag_len;
					pframe = (u8 *)RND4((addr_t)(pframe));
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			res = _FAIL;
		पूर्ण
	पूर्ण
	वापस res;
पूर्ण

अटल व्योम aes_decipher(u8 *key, uपूर्णांक hdrlen,
			 u8 *pframe, uपूर्णांक plen)
अणु
	अटल u8 message[MAX_MSG_SIZE];
	uपूर्णांक qc_exists, a4_exists, i, j, payload_reमुख्यder;
	uपूर्णांक num_blocks, payload_index;
	u8 pn_vector[6];
	u8 mic_iv[16];
	u8 mic_header1[16];
	u8 mic_header2[16];
	u8 ctr_preload[16];
	/* Intermediate Buffers */
	u8 chain_buffer[16];
	u8 aes_out[16];
	u8 padded_buffer[16];
	u8 mic[8];
	uपूर्णांक frtype  = GetFrameType(pframe);
	uपूर्णांक frsubtype  = GetFrameSubType(pframe);

	frsubtype >>= 4;
	स_रखो((व्योम *)mic_iv, 0, 16);
	स_रखो((व्योम *)mic_header1, 0, 16);
	स_रखो((व्योम *)mic_header2, 0, 16);
	स_रखो((व्योम *)ctr_preload, 0, 16);
	स_रखो((व्योम *)chain_buffer, 0, 16);
	स_रखो((व्योम *)aes_out, 0, 16);
	स_रखो((व्योम *)padded_buffer, 0, 16);
	/* start to decrypt the payload */
	/*(plen including llc, payload and mic) */
	num_blocks = (plen - 8) / 16;
	payload_reमुख्यder = (plen - 8) % 16;
	pn_vector[0] = pframe[hdrlen];
	pn_vector[1] = pframe[hdrlen + 1];
	pn_vector[2] = pframe[hdrlen + 4];
	pn_vector[3] = pframe[hdrlen + 5];
	pn_vector[4] = pframe[hdrlen + 6];
	pn_vector[5] = pframe[hdrlen + 7];
	अगर ((hdrlen == WLAN_HDR_A3_LEN) || (hdrlen ==  WLAN_HDR_A3_QOS_LEN))
		a4_exists = 0;
	अन्यथा
		a4_exists = 1;
	अगर ((frtype == IEEE80211_STYPE_DATA_CFACK) ||
	    (frtype == IEEE80211_STYPE_DATA_CFPOLL) ||
	    (frtype == IEEE80211_STYPE_DATA_CFACKPOLL)) अणु
		qc_exists = 1;
		अगर (hdrlen != WLAN_HDR_A3_QOS_LEN)
			hdrlen += 2;
	पूर्ण अन्यथा अगर ((frsubtype == 0x08) ||
		   (frsubtype == 0x09) ||
		   (frsubtype == 0x0a) ||
		   (frsubtype == 0x0b)) अणु
		अगर (hdrlen != WLAN_HDR_A3_QOS_LEN)
			hdrlen += 2;
		qc_exists = 1;
	पूर्ण अन्यथा अणु
		qc_exists = 0;
	पूर्ण
	/* now, decrypt pframe with hdrlen offset and plen दीर्घ */
	payload_index = hdrlen + 8; /* 8 is क्रम extiv */
	क्रम (i = 0; i < num_blocks; i++) अणु
		स्थिरruct_ctr_preload(ctr_preload, a4_exists, qc_exists,
				      pframe, pn_vector, i + 1);
		aes128k128d(key, ctr_preload, aes_out);
		bitwise_xor(aes_out, &pframe[payload_index], chain_buffer);
		क्रम (j = 0; j < 16; j++)
			pframe[payload_index++] = chain_buffer[j];
	पूर्ण
	अगर (payload_reमुख्यder > 0) अणु  /* If लघु final block, pad it,*/
		/* encrypt it and copy the unpadded part back   */
		स्थिरruct_ctr_preload(ctr_preload, a4_exists, qc_exists,
				      pframe, pn_vector, num_blocks + 1);
		क्रम (j = 0; j < 16; j++)
			padded_buffer[j] = 0x00;
		क्रम (j = 0; j < payload_reमुख्यder; j++)
			padded_buffer[j] = pframe[payload_index + j];
		aes128k128d(key, ctr_preload, aes_out);
		bitwise_xor(aes_out, padded_buffer, chain_buffer);
		क्रम (j = 0; j < payload_reमुख्यder; j++)
			pframe[payload_index++] = chain_buffer[j];
	पूर्ण
	/* start to calculate the mic */
	स_नकल((व्योम *)message, pframe, (hdrlen + plen + 8));
	pn_vector[0] = pframe[hdrlen];
	pn_vector[1] = pframe[hdrlen + 1];
	pn_vector[2] = pframe[hdrlen + 4];
	pn_vector[3] = pframe[hdrlen + 5];
	pn_vector[4] = pframe[hdrlen + 6];
	pn_vector[5] = pframe[hdrlen + 7];
	स्थिरruct_mic_iv(mic_iv, qc_exists, a4_exists, message, plen - 8,
			 pn_vector);
	स्थिरruct_mic_header1(mic_header1, hdrlen, message);
	स्थिरruct_mic_header2(mic_header2, message, a4_exists, qc_exists);
	payload_reमुख्यder = (plen - 8) % 16;
	num_blocks = (plen - 8) / 16;
	/* Find start of payload */
	payload_index = hdrlen + 8;
	/* Calculate MIC */
	aes128k128d(key, mic_iv, aes_out);
	bitwise_xor(aes_out, mic_header1, chain_buffer);
	aes128k128d(key, chain_buffer, aes_out);
	bitwise_xor(aes_out, mic_header2, chain_buffer);
	aes128k128d(key, chain_buffer, aes_out);
	क्रम (i = 0; i < num_blocks; i++) अणु
		bitwise_xor(aes_out, &message[payload_index], chain_buffer);
		payload_index += 16;
		aes128k128d(key, chain_buffer, aes_out);
	पूर्ण
	/* Add on the final payload block अगर it needs padding */
	अगर (payload_reमुख्यder > 0) अणु
		क्रम (j = 0; j < 16; j++)
			padded_buffer[j] = 0x00;
		क्रम (j = 0; j < payload_reमुख्यder; j++)
			padded_buffer[j] = message[payload_index++];
		bitwise_xor(aes_out, padded_buffer, chain_buffer);
		aes128k128d(key, chain_buffer, aes_out);
	पूर्ण
	क्रम (j = 0; j < 8; j++)
		mic[j] = aes_out[j];
	/* Insert MIC पूर्णांकo payload */
	क्रम (j = 0; j < 8; j++)
		message[payload_index + j] = mic[j];
	payload_index = hdrlen + 8;
	क्रम (i = 0; i < num_blocks; i++) अणु
		स्थिरruct_ctr_preload(ctr_preload, a4_exists, qc_exists,
				      message, pn_vector, i + 1);
		aes128k128d(key, ctr_preload, aes_out);
		bitwise_xor(aes_out, &message[payload_index], chain_buffer);
		क्रम (j = 0; j < 16; j++)
			message[payload_index++] = chain_buffer[j];
	पूर्ण
	अगर (payload_reमुख्यder > 0) अणु /* If लघु final block, pad it,*/
				     /* encrypt and copy unpadded part back */
		स्थिरruct_ctr_preload(ctr_preload, a4_exists, qc_exists,
				      message, pn_vector, num_blocks + 1);
		क्रम (j = 0; j < 16; j++)
			padded_buffer[j] = 0x00;
		क्रम (j = 0; j < payload_reमुख्यder; j++)
			padded_buffer[j] = message[payload_index + j];
		aes128k128d(key, ctr_preload, aes_out);
		bitwise_xor(aes_out, padded_buffer, chain_buffer);
		क्रम (j = 0; j < payload_reमुख्यder; j++)
			message[payload_index++] = chain_buffer[j];
	पूर्ण
	/* Encrypt the MIC */
	स्थिरruct_ctr_preload(ctr_preload, a4_exists, qc_exists, message,
			      pn_vector, 0);
	क्रम (j = 0; j < 16; j++)
		padded_buffer[j] = 0x00;
	क्रम (j = 0; j < 8; j++)
		padded_buffer[j] = message[j + hdrlen + plen];
	aes128k128d(key, ctr_preload, aes_out);
	bitwise_xor(aes_out, padded_buffer, chain_buffer);
	क्रम (j = 0; j < 8; j++)
		message[payload_index++] = chain_buffer[j];
	/* compare the mic */
पूर्ण

व्योम r8712_aes_decrypt(काष्ठा _adapter *padapter, u8 *precvframe)
अणु	/* exclude ICV */
	/* Intermediate Buffers */
	sपूर्णांक		length;
	u8	*pframe, *prwskey, *iv, idx;
	काष्ठा	sta_info *stainfo;
	काष्ठा	rx_pkt_attrib *prxattrib = &((जोड़ recv_frame *)
					   precvframe)->u.hdr.attrib;
	काष्ठा	security_priv *psecuritypriv = &padapter->securitypriv;

	pframe = (अचिन्हित अक्षर *)((जोड़ recv_frame *)precvframe)->
		 u.hdr.rx_data;
	/* 4 start to encrypt each fragment */
	अगर (prxattrib->encrypt == _AES_) अणु
		stainfo = r8712_get_stainfo(&padapter->stapriv,
					    &prxattrib->ta[0]);
		अगर (stainfo) अणु
			अगर (is_multicast_ether_addr(prxattrib->ra)) अणु
				iv = pframe + prxattrib->hdrlen;
				idx = iv[3];
				prwskey = &psecuritypriv->XGrpKey[
					  ((idx >> 6) & 0x3) - 1].skey[0];
				अगर (!psecuritypriv->binstallGrpkey)
					वापस;

			पूर्ण अन्यथा अणु
				prwskey = &stainfo->x_UncstKey.skey[0];
			पूर्ण
			length = ((जोड़ recv_frame *)precvframe)->
				 u.hdr.len - prxattrib->hdrlen -
				 prxattrib->iv_len;
			aes_decipher(prwskey, prxattrib->hdrlen, pframe,
				     length);
		पूर्ण
	पूर्ण
पूर्ण

व्योम r8712_use_tkipkey_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा _adapter *padapter =
		from_समयr(padapter, t, securitypriv.tkip_समयr);

	padapter->securitypriv.busetkipkey = true;
पूर्ण
