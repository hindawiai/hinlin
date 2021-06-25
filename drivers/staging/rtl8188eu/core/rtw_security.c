<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा  _RTW_SECURITY_C_

#समावेश <osdep_service.h>
#समावेश <drv_types.h>
#समावेश <wअगरi.h>
#समावेश <osdep_पूर्णांकf.h>
#समावेश <net/lib80211.h>

/* WEP related ===== */

#घोषणा CRC32_POLY 0x04c11db7

काष्ठा arc4context अणु
	u32 x;
	u32 y;
	u8 state[256];
पूर्ण;

अटल व्योम arcfour_init(काष्ठा arc4context *parc4ctx, u8 *key, u32	key_len)
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

अटल व्योम arcfour_encrypt(काष्ठा arc4context *parc4ctx, u8 *dest, u8 *src, u32 len)
अणु
	u32	i;

	क्रम (i = 0; i < len; i++)
		dest[i] = src[i] ^ (अचिन्हित अक्षर)arcfour_byte(parc4ctx);
पूर्ण

अटल पूर्णांक bcrc32initialized;
अटल u32 crc32_table[256];

अटल u8 crc32_reverseBit(u8 data)
अणु
	वापस (u8)((data << 7) & 0x80) | ((data << 5) & 0x40) | ((data << 3) & 0x20) |
		   ((data << 1) & 0x10) | ((data >> 1) & 0x08) | ((data >> 3) & 0x04) |
		   ((data >> 5) & 0x02) | ((data >> 7) & 0x01);
पूर्ण

अटल व्योम crc32_init(व्योम)
अणु
	पूर्णांक i, j;
	u32 c;
	u8 *p = (u8 *)&c, *p1;
	u8 k;

	अगर (bcrc32initialized == 1)
		वापस;

	c = 0x12340000;

	क्रम (i = 0; i < 256; ++i) अणु
		k = crc32_reverseBit((u8)i);
		क्रम (c = ((u32)k) << 24, j = 8; j > 0; --j)
			c = c & 0x80000000 ? (c << 1) ^ CRC32_POLY : (c << 1);
		p1 = (u8 *)&crc32_table[i];

		p1[0] = crc32_reverseBit(p[3]);
		p1[1] = crc32_reverseBit(p[2]);
		p1[2] = crc32_reverseBit(p[1]);
		p1[3] = crc32_reverseBit(p[0]);
	पूर्ण
	bcrc32initialized = 1;
पूर्ण

अटल __le32 अ_लोrc32(u8 *buf, पूर्णांक len)
अणु
	u8 *p;
	u32  crc;

	अगर (bcrc32initialized == 0)
		crc32_init();

	crc = 0xffffffff;       /* preload shअगरt रेजिस्टर, per CRC-32 spec */

	क्रम (p = buf; len > 0; ++p, --len)
		crc = crc32_table[(crc ^ *p) & 0xff] ^ (crc >> 8);
	वापस cpu_to_le32(~crc);    /* transmit complement, per CRC-32 spec */
पूर्ण

/* Need to consider the fragment  situation */
व्योम rtw_wep_encrypt(काष्ठा adapter *padapter, काष्ठा xmit_frame *pxmitframe)
अणु
	पूर्णांक	curfragnum, length;
	u8 *pframe;
	u8 hw_hdr_offset = 0;
	काष्ठा	pkt_attrib	 *pattrib = &pxmitframe->attrib;
	काष्ठा	security_priv	*psecuritypriv = &padapter->securitypriv;
	काष्ठा	xmit_priv		*pxmitpriv = &padapter->xmitpriv;
	स्थिर पूर्णांक keyindex = psecuritypriv->करोt11PrivacyKeyIndex;
	व्योम *crypto_निजी;
	काष्ठा sk_buff *skb;
	काष्ठा lib80211_crypto_ops *crypto_ops;

	अगर (!pxmitframe->buf_addr)
		वापस;

	अगर ((pattrib->encrypt != _WEP40_) && (pattrib->encrypt != _WEP104_))
		वापस;

	hw_hdr_offset = TXDESC_SIZE +
		 (pxmitframe->pkt_offset * PACKET_OFFSET_SZ);

	pframe = pxmitframe->buf_addr + hw_hdr_offset;

	crypto_ops = lib80211_get_crypto_ops("WEP");

	अगर (!crypto_ops)
		वापस;

	crypto_निजी = crypto_ops->init(keyindex);
	अगर (!crypto_निजी)
		वापस;

	अगर (crypto_ops->set_key(psecuritypriv->करोt11DefKey[keyindex].skey,
				psecuritypriv->करोt11DefKeylen[keyindex], शून्य, crypto_निजी) < 0)
		जाओ मुक्त_crypto_निजी;

	क्रम (curfragnum = 0; curfragnum < pattrib->nr_frags; curfragnum++) अणु
		अगर (curfragnum + 1 == pattrib->nr_frags)
			length = pattrib->last_txcmdsz;
		अन्यथा
			length = pxmitpriv->frag_len;
		skb = dev_alloc_skb(length);
		अगर (!skb)
			जाओ मुक्त_crypto_निजी;

		skb_put_data(skb, pframe, length);

		स_हटाओ(skb->data + 4, skb->data, pattrib->hdrlen);
		skb_pull(skb, 4);
		skb_trim(skb, skb->len - 4);

		अगर (crypto_ops->encrypt_mpdu(skb, pattrib->hdrlen, crypto_निजी)) अणु
			kमुक्त_skb(skb);
			जाओ मुक्त_crypto_निजी;
		पूर्ण

		स_नकल(pframe, skb->data, skb->len);

		pframe += skb->len;
		pframe = (u8 *)round_up((माप_प्रकार)(pframe), 4);

		kमुक्त_skb(skb);
	पूर्ण

मुक्त_crypto_निजी:
	crypto_ops->deinit(crypto_निजी);
पूर्ण

पूर्णांक rtw_wep_decrypt(काष्ठा adapter  *padapter, काष्ठा recv_frame *precvframe)
अणु
	काष्ठा	rx_pkt_attrib	 *prxattrib = &precvframe->attrib;

	अगर ((prxattrib->encrypt == _WEP40_) || (prxattrib->encrypt == _WEP104_)) अणु
		काष्ठा	security_priv	*psecuritypriv = &padapter->securitypriv;
		काष्ठा sk_buff *skb = precvframe->pkt;
		u8 *pframe = skb->data;
		व्योम *crypto_निजी = शून्य;
		पूर्णांक status = _SUCCESS;
		स्थिर पूर्णांक keyindex = prxattrib->key_index;
		काष्ठा lib80211_crypto_ops *crypto_ops = lib80211_get_crypto_ops("WEP");
		अक्षर iv[4], icv[4];

		अगर (!crypto_ops) अणु
			status = _FAIL;
			जाओ निकास;
		पूर्ण

		स_नकल(iv, pframe + prxattrib->hdrlen, 4);
		स_नकल(icv, pframe + skb->len - 4, 4);

		crypto_निजी = crypto_ops->init(keyindex);
		अगर (!crypto_निजी) अणु
			status = _FAIL;
			जाओ निकास;
		पूर्ण
		अगर (crypto_ops->set_key(psecuritypriv->करोt11DefKey[keyindex].skey,
					psecuritypriv->करोt11DefKeylen[keyindex], शून्य, crypto_निजी) < 0) अणु
			status = _FAIL;
			जाओ निकास;
		पूर्ण
		अगर (crypto_ops->decrypt_mpdu(skb, prxattrib->hdrlen, crypto_निजी)) अणु
			status = _FAIL;
			जाओ निकास;
		पूर्ण

		स_हटाओ(pframe, pframe + 4, prxattrib->hdrlen);
		skb_push(skb, 4);
		skb_put(skb, 4);

		स_नकल(pframe + prxattrib->hdrlen, iv, 4);
		स_नकल(pframe + skb->len - 4, icv, 4);

निकास:
		अगर (crypto_ops && crypto_निजी)
			crypto_ops->deinit(crypto_निजी);
		वापस status;
	पूर्ण

	वापस _FAIL;
पूर्ण

/* 3		===== TKIP related ===== */

अटल u32 secmicgetuपूर्णांक32(u8 *p)
/*  Convert from Byte[] to Us3232 in a portable way */
अणु
	s32 i;
	u32 res = 0;

	क्रम (i = 0; i < 4; i++)
		res |= ((u32)(*p++)) << (8 * i);
	वापस res;
पूर्ण

अटल व्योम secmicputuपूर्णांक32(u8 *p, u32 val)
/*  Convert from Us3232 to Byte[] in a portable way */
अणु
	दीर्घ i;

	क्रम (i = 0; i < 4; i++) अणु
		*p++ = (u8)(val & 0xff);
		val >>= 8;
	पूर्ण
पूर्ण

अटल व्योम secmicclear(काष्ठा mic_data *pmicdata)
अणु
/*  Reset the state to the empty message. */
	pmicdata->L = pmicdata->K0;
	pmicdata->R = pmicdata->K1;
	pmicdata->nBytesInM = 0;
	pmicdata->M = 0;
पूर्ण

व्योम rtw_secmicsetkey(काष्ठा mic_data *pmicdata, u8 *key)
अणु
	/*  Set the key */
	pmicdata->K0 = secmicgetuपूर्णांक32(key);
	pmicdata->K1 = secmicgetuपूर्णांक32(key + 4);
	/*  and reset the message */
	secmicclear(pmicdata);
पूर्ण

व्योम rtw_secmicappendbyte(काष्ठा mic_data *pmicdata, u8 b)
अणु
	/*  Append the byte to our word-sized buffer */
	pmicdata->M |= ((अचिन्हित दीर्घ)b) << (8 * pmicdata->nBytesInM);
	pmicdata->nBytesInM++;
	/*  Process the word अगर it is full. */
	अगर (pmicdata->nBytesInM >= 4) अणु
		pmicdata->L ^= pmicdata->M;
		pmicdata->R ^= ROL32(pmicdata->L, 17);
		pmicdata->L += pmicdata->R;
		pmicdata->R ^= ((pmicdata->L & 0xff00ff00) >> 8) | ((pmicdata->L & 0x00ff00ff) << 8);
		pmicdata->L += pmicdata->R;
		pmicdata->R ^= ROL32(pmicdata->L, 3);
		pmicdata->L += pmicdata->R;
		pmicdata->R ^= ROR32(pmicdata->L, 2);
		pmicdata->L += pmicdata->R;
		/*  Clear the buffer */
		pmicdata->M = 0;
		pmicdata->nBytesInM = 0;
	पूर्ण
पूर्ण

व्योम rtw_secmicappend(काष्ठा mic_data *pmicdata, u8 *src, u32 nbytes)
अणु
	/*  This is simple */
	जबतक (nbytes > 0) अणु
		rtw_secmicappendbyte(pmicdata, *src++);
		nbytes--;
	पूर्ण
पूर्ण

व्योम rtw_secgeपंचांगic(काष्ठा mic_data *pmicdata, u8 *dst)
अणु
	/*  Append the minimum padding */
	rtw_secmicappendbyte(pmicdata, 0x5a);
	rtw_secmicappendbyte(pmicdata, 0);
	rtw_secmicappendbyte(pmicdata, 0);
	rtw_secmicappendbyte(pmicdata, 0);
	rtw_secmicappendbyte(pmicdata, 0);
	/*  and then zeroes until the length is a multiple of 4 */
	जबतक (pmicdata->nBytesInM != 0)
		rtw_secmicappendbyte(pmicdata, 0);
	/*  The appendByte function has alपढ़ोy computed the result. */
	secmicputuपूर्णांक32(dst, pmicdata->L);
	secmicputuपूर्णांक32(dst + 4, pmicdata->R);
	/*  Reset to the empty message. */
	secmicclear(pmicdata);
पूर्ण

व्योम rtw_seccalctkipmic(u8 *key, u8 *header, u8 *data, u32 data_len, u8 *mic_code, u8 pri)
अणु
	काष्ठा mic_data	micdata;
	u8 priority[4] = अणु0x0, 0x0, 0x0, 0x0पूर्ण;

	rtw_secmicsetkey(&micdata, key);
	priority[0] = pri;

	/* Michael MIC pseuकरो header: DA, SA, 3 x 0, Priority */
	अगर (header[1] & 1) अणु   /* ToDS == 1 */
		rtw_secmicappend(&micdata, &header[16], 6);  /* DA */
		अगर (header[1] & 2)  /* From Ds == 1 */
			rtw_secmicappend(&micdata, &header[24], 6);
		अन्यथा
			rtw_secmicappend(&micdata, &header[10], 6);
	पूर्ण अन्यथा अणु	/* ToDS == 0 */
		rtw_secmicappend(&micdata, &header[4], 6);   /* DA */
		अगर (header[1] & 2)  /* From Ds == 1 */
			rtw_secmicappend(&micdata, &header[16], 6);
		अन्यथा
			rtw_secmicappend(&micdata, &header[10], 6);
	पूर्ण
	rtw_secmicappend(&micdata, &priority[0], 4);

	rtw_secmicappend(&micdata, data, data_len);

	rtw_secgeपंचांगic(&micdata, mic_code);
पूर्ण

/* macros क्रम extraction/creation of अचिन्हित अक्षर/अचिन्हित लघु values  */
#घोषणा RotR1(v16)   ((((v16) >> 1) & 0x7FFF) ^ (((v16) & 1) << 15))
#घोषणा   Lo8(v16)   ((u8)((v16)       & 0x00FF))
#घोषणा   Hi8(v16)   ((u8)(((v16) >> 8) & 0x00FF))
#घोषणा  Lo16(v32)   ((u16)((v32)       & 0xFFFF))
#घोषणा  Hi16(v32)   ((u16)(((v32) >> 16) & 0xFFFF))
#घोषणा  Mk16(hi, lo) ((lo) ^ (((u16)(hi)) << 8))

/* select the Nth 16-bit word of the temporal key अचिन्हित अक्षर array TK[]   */
#घोषणा  TK16(N)     Mk16(tk[2 * (N) + 1], tk[2 * (N)])

/* S-box lookup: 16 bits --> 16 bits */
#घोषणा _S_(v16)     (Sbox1[0][Lo8(v16)] ^ Sbox1[1][Hi8(v16)])

/* fixed algorithm "parameters" */
#घोषणा PHASE1_LOOP_CNT   8    /* this needs to be "big enough"     */
#घोषणा TA_SIZE	   6    /*  48-bit transmitter address       */
#घोषणा TK_SIZE	  16    /* 128-bit temporal key	      */
#घोषणा P1K_SIZE	 10    /*  80-bit Phase1 key		*/
#घोषणा RC4_KEY_SIZE     16    /* 128-bit RC4KEY (104 bits unknown) */

/* 2-अचिन्हित अक्षर by 2-अचिन्हित अक्षर subset of the full AES S-box table */
अटल स्थिर अचिन्हित लघु Sbox1[2][256] = अणु  /* Sbox क्रम hash (can be in ROM)     */
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

	अणु  /* second half of table is अचिन्हित अक्षर-reversed version of first! */
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

/**
 * phase1() - generate P1K, given TA, TK, IV32
 * @tk[]: temporal key [128 bits]
 * @ta[]: transmitter's MAC address [ 48 bits]
 * @iv32: upper 32 bits of IV [ 32 bits]
 *
 * This function only needs to be called every 2**16 packets,
 * although in theory it could be called every packet.
 *
 * Return: p1k[] - Phase 1 key [ 80 bits]
 */
अटल व्योम phase1(u16 *p1k, स्थिर u8 *tk, स्थिर u8 *ta, u32 iv32)
अणु
	पूर्णांक  i;
	/* Initialize the 80 bits of P1K[] from IV32 and TA[0..5]     */
	p1k[0]      = Lo16(iv32);
	p1k[1]      = Hi16(iv32);
	p1k[2]      = Mk16(ta[1], ta[0]); /* use TA[] as little-endian */
	p1k[3]      = Mk16(ta[3], ta[2]);
	p1k[4]      = Mk16(ta[5], ta[4]);

	/* Now compute an unbalanced Feistel cipher with 80-bit block */
	/* size on the 80-bit block P1K[], using the 128-bit key TK[] */
	क्रम (i = 0; i < PHASE1_LOOP_CNT; i++) अणु /* Each add operation here is mod 2**16 */
		p1k[0] += _S_(p1k[4] ^ TK16((i & 1) + 0));
		p1k[1] += _S_(p1k[0] ^ TK16((i & 1) + 2));
		p1k[2] += _S_(p1k[1] ^ TK16((i & 1) + 4));
		p1k[3] += _S_(p1k[2] ^ TK16((i & 1) + 6));
		p1k[4] += _S_(p1k[3] ^ TK16((i & 1) + 0));
		p1k[4] +=  (अचिन्हित लघु)i;   /* aव्योम "slide attacks" */
	पूर्ण
पूर्ण

/**
 * phase2() - generate RC4KEY, given TK, P1K, IV16
 * @tk[]: Temporal key [128 bits]
 * @p1k[]: Phase 1 output key [ 80 bits]
 * @iv16: low 16 bits of IV counter [ 16 bits]
 *
 * The value अणुTA, IV32, IV16पूर्ण क्रम Phase1/Phase2 must be unique
 * across all packets using the same key TK value. Then, क्रम a
 * given value of TK[], this TKIP48 स्थिरruction guarantees that
 * the final RC4KEY value is unique across all packets.
 *
 * Suggested implementation optimization: अगर PPK[] is "overlaid"
 * appropriately on RC4KEY[], there is no need क्रम the final
 * क्रम loop below that copies the PPK[] result पूर्णांकo RC4KEY[].
 *
 * Return: rc4key[] - the key used to encrypt the packet [128 bits]
 */
अटल व्योम phase2(u8 *rc4key, स्थिर u8 *tk, स्थिर u16 *p1k, u16 iv16)
अणु
	पूर्णांक  i;
	u16 PPK[6];			/* temporary key क्रम mixing    */
	/* Note: all adds in the PPK[] equations below are mod 2**16	 */
	क्रम (i = 0; i < 5; i++)
		PPK[i] = p1k[i];	/* first, copy P1K to PPK      */
	PPK[5]  =  p1k[4] + iv16;	/* next,  add in IV16	  */

	/* Bijective non-linear mixing of the 96 bits of PPK[0..5]	   */
	PPK[0] +=    _S_(PPK[5] ^ TK16(0));   /* Mix key in each "round"     */
	PPK[1] +=    _S_(PPK[0] ^ TK16(1));
	PPK[2] +=    _S_(PPK[1] ^ TK16(2));
	PPK[3] +=    _S_(PPK[2] ^ TK16(3));
	PPK[4] +=    _S_(PPK[3] ^ TK16(4));
	PPK[5] +=    _S_(PPK[4] ^ TK16(5));   /* Total # S-box lookups == 6  */

	/* Final sweep: bijective, "linear". Rotates समाप्त LSB correlations   */
	PPK[0] +=  RotR1(PPK[5] ^ TK16(6));
	PPK[1] +=  RotR1(PPK[0] ^ TK16(7));   /* Use all of TK[] in Phase2   */
	PPK[2] +=  RotR1(PPK[1]);
	PPK[3] +=  RotR1(PPK[2]);
	PPK[4] +=  RotR1(PPK[3]);
	PPK[5] +=  RotR1(PPK[4]);
	/* Note: At this poपूर्णांक, क्रम a given key TK[0..15], the 96-bit output */
	/*       value PPK[0..5] is guaranteed to be unique, as a function   */
	/*       of the 96-bit "input" value   अणुTA, IV32, IV16पूर्ण. That is, P1K  */
	/*       is now a keyed permutation of अणुTA, IV32, IV16पूर्ण.	       */

	/* Set RC4KEY[0..3], which includes "cleartext" portion of RC4 key   */
	rc4key[0] = Hi8(iv16);		/* RC4KEY[0..2] is the WEP IV  */
	rc4key[1] = (Hi8(iv16) | 0x20) & 0x7F; /* Help aव्योम weak (FMS) keys  */
	rc4key[2] = Lo8(iv16);
	rc4key[3] = Lo8((PPK[5] ^ TK16(0)) >> 1);

	/* Copy 96 bits of PPK[0..5] to RC4KEY[4..15]  (little-endian)       */
	क्रम (i = 0; i < 6; i++) अणु
		rc4key[4 + 2 * i] = Lo8(PPK[i]);
		rc4key[5 + 2 * i] = Hi8(PPK[i]);
	पूर्ण
पूर्ण

/* The hlen isn't include the IV */
u32	rtw_tkip_encrypt(काष्ठा adapter *padapter, काष्ठा xmit_frame *pxmitframe)
अणु																	/*  exclude ICV */
	u16	pnl;
	u32	pnh;
	u8	rc4key[16];
	u8   ttkey[16];
	u8	crc[4];
	u8   hw_hdr_offset = 0;
	काष्ठा arc4context mycontext;
	पूर्णांक			curfragnum, length;

	u8	*pframe, *payload, *iv, *prwskey;
	जोड़ pn48 करोt11txpn;
	काष्ठा	sta_info		*stainfo;
	काष्ठा	pkt_attrib	 *pattrib = &pxmitframe->attrib;
	काष्ठा	security_priv	*psecuritypriv = &padapter->securitypriv;
	काष्ठा	xmit_priv		*pxmitpriv = &padapter->xmitpriv;
	u32	res = _SUCCESS;

	अगर (!pxmitframe->buf_addr)
		वापस _FAIL;

	hw_hdr_offset = TXDESC_SIZE +
		 (pxmitframe->pkt_offset * PACKET_OFFSET_SZ);
	pframe = pxmitframe->buf_addr + hw_hdr_offset;
	/* 4 start to encrypt each fragment */
	अगर (pattrib->encrypt == _TKIP_) अणु
		अगर (pattrib->psta)
			stainfo = pattrib->psta;
		अन्यथा
			stainfo = rtw_get_stainfo(&padapter->stapriv, &pattrib->ra[0]);

		अगर (stainfo) अणु
			RT_TRACE(_module_rtl871x_security_c_, _drv_err_, ("%s: stainfo!= NULL!!!\n", __func__));

			अगर (is_multicast_ether_addr(pattrib->ra))
				prwskey = psecuritypriv->करोt118021XGrpKey[psecuritypriv->करोt118021XGrpKeyid].skey;
			अन्यथा
				prwskey = &stainfo->करोt118021x_UncstKey.skey[0];

			क्रम (curfragnum = 0; curfragnum < pattrib->nr_frags; curfragnum++) अणु
				iv = pframe + pattrib->hdrlen;
				payload = pframe + pattrib->iv_len + pattrib->hdrlen;

				GET_TKIP_PN(iv, करोt11txpn);

				pnl = (u16)(करोt11txpn.val);
				pnh = (u32)(करोt11txpn.val >> 16);
				phase1((u16 *)&ttkey[0], prwskey, &pattrib->ta[0], pnh);
				phase2(&rc4key[0], prwskey, (u16 *)&ttkey[0], pnl);

				अगर ((curfragnum + 1) == pattrib->nr_frags) अणु	/* 4 the last fragment */
					length = pattrib->last_txcmdsz - pattrib->hdrlen - pattrib->iv_len - pattrib->icv_len;
					RT_TRACE(_module_rtl871x_security_c_, _drv_info_,
						 ("pattrib->iv_len=%x, pattrib->icv_len=%x\n",
						 pattrib->iv_len, pattrib->icv_len));
					*((__le32 *)crc) = अ_लोrc32(payload, length);/* modअगरied by Amy*/

					arcfour_init(&mycontext, rc4key, 16);
					arcfour_encrypt(&mycontext, payload, payload, length);
					arcfour_encrypt(&mycontext, payload + length, crc, 4);
				पूर्ण अन्यथा अणु
					length = pxmitpriv->frag_len - pattrib->hdrlen - pattrib->iv_len - pattrib->icv_len;
					*((__le32 *)crc) = अ_लोrc32(payload, length);/* modअगरied by Amy*/
					arcfour_init(&mycontext, rc4key, 16);
					arcfour_encrypt(&mycontext, payload, payload, length);
					arcfour_encrypt(&mycontext, payload + length, crc, 4);

					pframe += pxmitpriv->frag_len;
					pframe = (u8 *)round_up((माप_प्रकार)(pframe), 4);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			RT_TRACE(_module_rtl871x_security_c_, _drv_err_, ("%s: stainfo==NULL!!!\n", __func__));
			res = _FAIL;
		पूर्ण
	पूर्ण
	वापस res;
पूर्ण

/* The hlen isn't include the IV */
u32 rtw_tkip_decrypt(काष्ठा adapter *padapter, काष्ठा recv_frame *precvframe)
अणु																	/*  exclude ICV */
	u16 pnl;
	u32 pnh;
	u8   rc4key[16];
	u8   ttkey[16];
	u8	crc[4];
	काष्ठा arc4context mycontext;
	पूर्णांक			length;
	u8	*pframe, *payload, *iv, *prwskey;
	जोड़ pn48 करोt11txpn;
	काष्ठा	sta_info		*stainfo;
	काष्ठा	rx_pkt_attrib	 *prxattrib = &precvframe->attrib;
	काष्ठा	security_priv	*psecuritypriv = &padapter->securitypriv;
	u32		res = _SUCCESS;

	pframe = (अचिन्हित अक्षर *)precvframe->pkt->data;

	/* 4 start to decrypt recvframe */
	अगर (prxattrib->encrypt == _TKIP_) अणु
		stainfo = rtw_get_stainfo(&padapter->stapriv, &prxattrib->ta[0]);
		अगर (stainfo) अणु
			अगर (is_multicast_ether_addr(prxattrib->ra)) अणु
				अगर (!psecuritypriv->binstallGrpkey) अणु
					res = _FAIL;
					DBG_88E("%s:rx bc/mc packets, but didn't install group key!!!!!!!!!!\n", __func__);
					जाओ निकास;
				पूर्ण
				prwskey = psecuritypriv->करोt118021XGrpKey[prxattrib->key_index].skey;
			पूर्ण अन्यथा अणु
				RT_TRACE(_module_rtl871x_security_c_, _drv_err_, ("%s: stainfo!= NULL!!!\n", __func__));
				prwskey = &stainfo->करोt118021x_UncstKey.skey[0];
			पूर्ण

			iv = pframe + prxattrib->hdrlen;
			payload = pframe + prxattrib->iv_len + prxattrib->hdrlen;
			length = precvframe->pkt->len - prxattrib->hdrlen - prxattrib->iv_len;

			GET_TKIP_PN(iv, करोt11txpn);

			pnl = (u16)(करोt11txpn.val);
			pnh = (u32)(करोt11txpn.val >> 16);

			phase1((u16 *)&ttkey[0], prwskey, &prxattrib->ta[0], pnh);
			phase2(&rc4key[0], prwskey, (अचिन्हित लघु *)&ttkey[0], pnl);

			/* 4 decrypt payload include icv */

			arcfour_init(&mycontext, rc4key, 16);
			arcfour_encrypt(&mycontext, payload, payload, length);

			*((__le32 *)crc) = अ_लोrc32(payload, length - 4);

			अगर (crc[3] != payload[length - 1] ||
			    crc[2] != payload[length - 2] ||
			    crc[1] != payload[length - 3] ||
			    crc[0] != payload[length - 4]) अणु
				RT_TRACE(_module_rtl871x_security_c_, _drv_err_,
					 ("rtw_wep_decrypt:icv error crc (%4ph)!=payload (%4ph)\n",
					 &crc, &payload[length - 4]));
				res = _FAIL;
			पूर्ण
		पूर्ण अन्यथा अणु
			RT_TRACE(_module_rtl871x_security_c_, _drv_err_, ("%s: stainfo==NULL!!!\n", __func__));
			res = _FAIL;
		पूर्ण
	पूर्ण
निकास:
	वापस res;
पूर्ण

u32 rtw_aes_encrypt(काष्ठा adapter *padapter, काष्ठा xmit_frame *pxmitframe)
अणु
	पूर्णांक curfragnum, length;
	u8 *pframe; /*  *payload,*iv */
	u8 hw_hdr_offset = 0;
	काष्ठा sta_info *stainfo;
	काष्ठा pkt_attrib *pattrib = &pxmitframe->attrib;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	u32 res = _SUCCESS;
	व्योम *crypto_निजी;
	काष्ठा sk_buff *skb;
	काष्ठा lib80211_crypto_ops *crypto_ops;
	स्थिर पूर्णांक key_idx = is_multicast_ether_addr(pattrib->ra) ? psecuritypriv->करोt118021XGrpKeyid : 0;
	स्थिर पूर्णांक key_length = 16;
	u8 *key;

	अगर (!pxmitframe->buf_addr)
		वापस _FAIL;

	hw_hdr_offset = TXDESC_SIZE +
		 (pxmitframe->pkt_offset * PACKET_OFFSET_SZ);

	pframe = pxmitframe->buf_addr + hw_hdr_offset;

	/* 4 start to encrypt each fragment */
	अगर (pattrib->encrypt != _AES_)
		वापस res;

	अगर (pattrib->psta)
		stainfo = pattrib->psta;
	अन्यथा
		stainfo = rtw_get_stainfo(&padapter->stapriv, &pattrib->ra[0]);

	अगर (!stainfo) अणु
		RT_TRACE(_module_rtl871x_security_c_, _drv_err_, ("%s: stainfo==NULL!!!\n", __func__));
		वापस _FAIL;
	पूर्ण

	crypto_ops = lib80211_get_crypto_ops("CCMP");

	अगर (is_multicast_ether_addr(pattrib->ra))
		key = psecuritypriv->करोt118021XGrpKey[key_idx].skey;
	अन्यथा
		key = stainfo->करोt118021x_UncstKey.skey;

	अगर (!crypto_ops) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	crypto_निजी = crypto_ops->init(key_idx);
	अगर (!crypto_निजी) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	अगर (crypto_ops->set_key(key, key_length, शून्य, crypto_निजी) < 0) अणु
		res = _FAIL;
		जाओ निकास_crypto_ops_deinit;
	पूर्ण

	RT_TRACE(_module_rtl871x_security_c_, _drv_err_, ("%s: stainfo!= NULL!!!\n", __func__));

	क्रम (curfragnum = 0; curfragnum < pattrib->nr_frags; curfragnum++) अणु
		अगर (curfragnum + 1 == pattrib->nr_frags)
			length = pattrib->last_txcmdsz;
		अन्यथा
			length = pxmitpriv->frag_len;

		skb = dev_alloc_skb(length);
		अगर (!skb) अणु
			res = _FAIL;
			जाओ निकास_crypto_ops_deinit;
		पूर्ण

		skb_put_data(skb, pframe, length);

		स_हटाओ(skb->data + pattrib->iv_len, skb->data, pattrib->hdrlen);
		skb_pull(skb, pattrib->iv_len);
		skb_trim(skb, skb->len - pattrib->icv_len);

		अगर (crypto_ops->encrypt_mpdu(skb, pattrib->hdrlen, crypto_निजी)) अणु
			kमुक्त_skb(skb);
			res = _FAIL;
			जाओ निकास_crypto_ops_deinit;
		पूर्ण

		स_नकल(pframe, skb->data, skb->len);

		pframe += skb->len;
		pframe = (u8 *)round_up((माप_प्रकार)(pframe), 8);

		kमुक्त_skb(skb);
	पूर्ण

निकास_crypto_ops_deinit:
	crypto_ops->deinit(crypto_निजी);

निकास:
	वापस res;
पूर्ण

u32 rtw_aes_decrypt(काष्ठा adapter *padapter, काष्ठा recv_frame *precvframe)
अणु
	काष्ठा rx_pkt_attrib *prxattrib = &precvframe->attrib;
	u32 res = _SUCCESS;

	/* 4 start to encrypt each fragment */
	अगर (prxattrib->encrypt == _AES_) अणु
		काष्ठा sta_info *stainfo = rtw_get_stainfo(&padapter->stapriv, &prxattrib->ta[0]);

		अगर (stainfo) अणु
			पूर्णांक key_idx;
			स्थिर पूर्णांक key_length = 16, iv_len = 8, icv_len = 8;
			काष्ठा sk_buff *skb = precvframe->pkt;
			व्योम *crypto_निजी = शून्य;
			u8 *key, *pframe = skb->data;
			काष्ठा lib80211_crypto_ops *crypto_ops = lib80211_get_crypto_ops("CCMP");
			काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
			अक्षर iv[8], icv[8];

			अगर (is_multicast_ether_addr(prxattrib->ra)) अणु
				/* in concurrent we should use sw descrypt in group key, so we हटाओ this message */
				अगर (!psecuritypriv->binstallGrpkey) अणु
					res = _FAIL;
					DBG_88E("%s:rx bc/mc packets, but didn't install group key!!!!!!!!!!\n", __func__);
					जाओ निकास;
				पूर्ण
				key_idx = psecuritypriv->करोt118021XGrpKeyid;
				key = psecuritypriv->करोt118021XGrpKey[key_idx].skey;
			पूर्ण अन्यथा अणु
				key_idx = 0;
				key = stainfo->करोt118021x_UncstKey.skey;
			पूर्ण

			अगर (!crypto_ops) अणु
				res = _FAIL;
				जाओ निकास_lib80211_ccmp;
			पूर्ण

			स_नकल(iv, pframe + prxattrib->hdrlen, iv_len);
			स_नकल(icv, pframe + skb->len - icv_len, icv_len);

			crypto_निजी = crypto_ops->init(key_idx);
			अगर (!crypto_निजी) अणु
				res = _FAIL;
				जाओ निकास_lib80211_ccmp;
			पूर्ण
			अगर (crypto_ops->set_key(key, key_length, शून्य, crypto_निजी) < 0) अणु
				res = _FAIL;
				जाओ निकास_lib80211_ccmp;
			पूर्ण
			अगर (crypto_ops->decrypt_mpdu(skb, prxattrib->hdrlen, crypto_निजी)) अणु
				res = _FAIL;
				जाओ निकास_lib80211_ccmp;
			पूर्ण

			स_हटाओ(pframe, pframe + iv_len, prxattrib->hdrlen);
			skb_push(skb, iv_len);
			skb_put(skb, icv_len);

			स_नकल(pframe + prxattrib->hdrlen, iv, iv_len);
			स_नकल(pframe + skb->len - icv_len, icv, icv_len);

निकास_lib80211_ccmp:
			अगर (crypto_ops && crypto_निजी)
				crypto_ops->deinit(crypto_निजी);
		पूर्ण अन्यथा अणु
			RT_TRACE(_module_rtl871x_security_c_, _drv_err_, ("rtw_aes_encrypt: stainfo==NULL!!!\n"));
			res = _FAIL;
		पूर्ण
	पूर्ण
निकास:
	वापस res;
पूर्ण
