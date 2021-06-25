<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा  _RTW_SECURITY_C_

#समावेश <linux/crc32poly.h>
#समावेश <drv_types.h>
#समावेश <rtw_debug.h>

अटल स्थिर अक्षर * स्थिर _security_type_str[] = अणु
	"N/A",
	"WEP40",
	"TKIP",
	"TKIP_WM",
	"AES",
	"WEP104",
	"SMS4",
	"WEP_WPA",
	"BIP",
पूर्ण;

स्थिर अक्षर *security_type_str(u8 value)
अणु
	अगर (value <= _BIP_)
		वापस _security_type_str[value];
	वापस शून्य;
पूर्ण

/* WEP related ===== */

काष्ठा arc4context अणु
	u32 x;
	u32 y;
	u8 state[256];
पूर्ण;


अटल व्योम arcfour_init(काष्ठा arc4context	*parc4ctx, u8 *key, u32 key_len)
अणु
	u32 t, u;
	u32 keyindex;
	u32 stateindex;
	u8 *state;
	u32 counter;

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

अटल u32 arcfour_byte(काष्ठा arc4context	*parc4ctx)
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
	u32 i;

	क्रम (i = 0; i < len; i++)
		dest[i] = src[i] ^ (अचिन्हित अक्षर)arcfour_byte(parc4ctx);
पूर्ण

अटल चिन्हित पूर्णांक bcrc32initialized;
अटल u32 crc32_table[256];


अटल u8 crc32_reverseBit(u8 data)
अणु
	वापस((u8)((data<<7)&0x80) | ((data<<5)&0x40) | ((data<<3)&0x20) | ((data<<1)&0x10) | ((data>>1)&0x08) | ((data>>3)&0x04) | ((data>>5)&0x02) | ((data>>7)&0x01));
पूर्ण

अटल व्योम crc32_init(व्योम)
अणु
	अगर (bcrc32initialized == 1)
		वापस;
	अन्यथा अणु
		चिन्हित पूर्णांक i, j;
		u32 c;
		u8 *p = (u8 *)&c, *p1;
		u8 k;

		c = 0x12340000;

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
पूर्ण

अटल __le32 अ_लोrc32(u8 *buf, चिन्हित पूर्णांक len)
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


/*
	Need to consider the fragment  situation
*/
व्योम rtw_wep_encrypt(काष्ठा adapter *padapter, u8 *pxmitframe)
अणु																	/*  exclude ICV */

	अचिन्हित अक्षर crc[4];
	काष्ठा arc4context	 mycontext;

	चिन्हित पूर्णांक	curfragnum, length;
	u32 keylength;

	u8 *pframe, *payload, *iv;    /* wepkey */
	u8 wepkey[16];
	u8 hw_hdr_offset = 0;
	काष्ठा pkt_attrib *pattrib = &((काष्ठा xmit_frame *)pxmitframe)->attrib;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;

	अगर (((काष्ठा xmit_frame *)pxmitframe)->buf_addr == शून्य)
		वापस;

	hw_hdr_offset = TXDESC_OFFSET;
	pframe = ((काष्ठा xmit_frame *)pxmitframe)->buf_addr + hw_hdr_offset;

	/* start to encrypt each fragment */
	अगर ((pattrib->encrypt == _WEP40_) || (pattrib->encrypt == _WEP104_)) अणु
		keylength = psecuritypriv->करोt11DefKeylen[psecuritypriv->करोt11PrivacyKeyIndex];

		क्रम (curfragnum = 0; curfragnum < pattrib->nr_frags; curfragnum++) अणु
			iv = pframe+pattrib->hdrlen;
			स_नकल(&wepkey[0], iv, 3);
			स_नकल(&wepkey[3], &psecuritypriv->करोt11DefKey[psecuritypriv->करोt11PrivacyKeyIndex].skey[0], keylength);
			payload = pframe+pattrib->iv_len+pattrib->hdrlen;

			अगर ((curfragnum+1) == pattrib->nr_frags) अणु	/* the last fragment */

				length = pattrib->last_txcmdsz-pattrib->hdrlen-pattrib->iv_len-pattrib->icv_len;

				*((__le32 *)crc) = अ_लोrc32(payload, length);

				arcfour_init(&mycontext, wepkey, 3+keylength);
				arcfour_encrypt(&mycontext, payload, payload, length);
				arcfour_encrypt(&mycontext, payload+length, crc, 4);

			पूर्ण अन्यथा अणु
				length = pxmitpriv->frag_len-pattrib->hdrlen-pattrib->iv_len-pattrib->icv_len;
				*((__le32 *)crc) = अ_लोrc32(payload, length);
				arcfour_init(&mycontext, wepkey, 3+keylength);
				arcfour_encrypt(&mycontext, payload, payload, length);
				arcfour_encrypt(&mycontext, payload+length, crc, 4);

				pframe += pxmitpriv->frag_len;
				pframe = (u8 *)round_up((SIZE_PTR)(pframe), 4);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम rtw_wep_decrypt(काष्ठा adapter  *padapter, u8 *precvframe)
अणु
	/*  exclude ICV */
	u8 crc[4];
	काष्ठा arc4context	 mycontext;
	चिन्हित पूर्णांक	length;
	u32 keylength;
	u8 *pframe, *payload, *iv, wepkey[16];
	u8  keyindex;
	काष्ठा	rx_pkt_attrib	 *prxattrib = &(((जोड़ recv_frame *)precvframe)->u.hdr.attrib);
	काष्ठा	security_priv *psecuritypriv = &padapter->securitypriv;

	pframe = (अचिन्हित अक्षर *)((जोड़ recv_frame *)precvframe)->u.hdr.rx_data;

	/* start to decrypt recvframe */
	अगर ((prxattrib->encrypt == _WEP40_) || (prxattrib->encrypt == _WEP104_)) अणु
		iv = pframe+prxattrib->hdrlen;
		/* keyindex =(iv[3]&0x3); */
		keyindex = prxattrib->key_index;
		keylength = psecuritypriv->करोt11DefKeylen[keyindex];
		स_नकल(&wepkey[0], iv, 3);
		/* स_नकल(&wepkey[3], &psecuritypriv->करोt11DefKey[psecuritypriv->करोt11PrivacyKeyIndex].skey[0], keylength); */
		स_नकल(&wepkey[3], &psecuritypriv->करोt11DefKey[keyindex].skey[0], keylength);
		length = ((जोड़ recv_frame *)precvframe)->u.hdr.len-prxattrib->hdrlen-prxattrib->iv_len;

		payload = pframe+prxattrib->iv_len+prxattrib->hdrlen;

		/* decrypt payload include icv */
		arcfour_init(&mycontext, wepkey, 3+keylength);
		arcfour_encrypt(&mycontext, payload, payload,  length);

		/* calculate icv and compare the icv */
		*((u32 *)crc) = le32_to_cpu(अ_लोrc32(payload, length-4));

	पूर्ण
पूर्ण

/* 3		=====TKIP related ===== */

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
		*p++ = (u8) (val & 0xff);
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
	pmicdata->M |= ((अचिन्हित दीर्घ)b) << (8*pmicdata->nBytesInM);
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
#घोषणा  TK16(N)     Mk16(tk[2*(N)+1], tk[2*(N)])

/* S-box lookup: 16 bits --> 16 bits */
#घोषणा _S_(v16)     (Sbox1[0][Lo8(v16)] ^ Sbox1[1][Hi8(v16)])

/* fixed algorithm "parameters" */
#घोषणा PHASE1_LOOP_CNT   8    /* this needs to be "big enough"     */
#घोषणा TA_SIZE           6    /*  48-bit transmitter address       */
#घोषणा TK_SIZE          16    /* 128-bit temporal key              */
#घोषणा P1K_SIZE         10    /*  80-bit Phase1 key                */
#घोषणा RC4_KEY_SIZE     16    /* 128-bit RC4KEY (104 bits unknown) */


/* 2-अचिन्हित अक्षर by 2-अचिन्हित अक्षर subset of the full AES S-box table */
अटल स्थिर अचिन्हित लघु Sbox1[2][256] = अणु      /* Sbox क्रम hash (can be in ROM)     */
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
	चिन्हित पूर्णांक  i;

	/* Initialize the 80 bits of P1K[] from IV32 and TA[0..5]     */
	p1k[0]      = Lo16(iv32);
	p1k[1]      = Hi16(iv32);
	p1k[2]      = Mk16(ta[1], ta[0]); /* use TA[] as little-endian */
	p1k[3]      = Mk16(ta[3], ta[2]);
	p1k[4]      = Mk16(ta[5], ta[4]);

	/* Now compute an unbalanced Feistel cipher with 80-bit block */
	/* size on the 80-bit block P1K[], using the 128-bit key TK[] */
	क्रम (i = 0; i < PHASE1_LOOP_CNT; i++) अणु
		/* Each add operation here is mod 2**16 */
		p1k[0] += _S_(p1k[4] ^ TK16((i&1)+0));
		p1k[1] += _S_(p1k[0] ^ TK16((i&1)+2));
		p1k[2] += _S_(p1k[1] ^ TK16((i&1)+4));
		p1k[3] += _S_(p1k[2] ^ TK16((i&1)+6));
		p1k[4] += _S_(p1k[3] ^ TK16((i&1)+0));
		p1k[4] +=  (अचिन्हित लघु)i;          /* aव्योम "slide attacks" */
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
*     The value अणुTA, IV32, IV16पूर्ण क्रम Phase1/Phase2 must be unique
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
	चिन्हित पूर्णांक  i;
	u16 PPK[6];                          /* temporary key क्रम mixing    */

	/* Note: all adds in the PPK[] equations below are mod 2**16         */
	क्रम (i = 0; i < 5; i++)
		PPK[i] = p1k[i];      /* first, copy P1K to PPK      */

	PPK[5]  =  p1k[4]+iv16;             /* next,  add in IV16          */

	/* Bijective non-linear mixing of the 96 bits of PPK[0..5]           */
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
	/*       is now a keyed permutation of अणुTA, IV32, IV16पूर्ण.               */

	/* Set RC4KEY[0..3], which includes "cleartext" portion of RC4 key   */
	rc4key[0] = Hi8(iv16);                /* RC4KEY[0..2] is the WEP IV  */
	rc4key[1] = (Hi8(iv16) | 0x20) & 0x7F; /* Help aव्योम weak (FMS) keys  */
	rc4key[2] = Lo8(iv16);
	rc4key[3] = Lo8((PPK[5] ^ TK16(0)) >> 1);


	/* Copy 96 bits of PPK[0..5] to RC4KEY[4..15]  (little-endian)       */
	क्रम (i = 0; i < 6; i++) अणु
		rc4key[4+2*i] = Lo8(PPK[i]);
		rc4key[5+2*i] = Hi8(PPK[i]);
	पूर्ण
पूर्ण


/* The hlen isn't include the IV */
u32 rtw_tkip_encrypt(काष्ठा adapter *padapter, u8 *pxmitframe)
अणु																	/*  exclude ICV */
	u16 pnl;
	u32 pnh;
	u8 rc4key[16];
	u8   ttkey[16];
	u8 crc[4];
	u8   hw_hdr_offset = 0;
	काष्ठा arc4context mycontext;
	चिन्हित पूर्णांक			curfragnum, length;

	u8 *pframe, *payload, *iv, *prwskey;
	जोड़ pn48 करोt11txpn;
	काष्ठा pkt_attrib *pattrib = &((काष्ठा xmit_frame *)pxmitframe)->attrib;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	u32 res = _SUCCESS;

	अगर (((काष्ठा xmit_frame *)pxmitframe)->buf_addr == शून्य)
		वापस _FAIL;

	hw_hdr_offset = TXDESC_OFFSET;
	pframe = ((काष्ठा xmit_frame *)pxmitframe)->buf_addr + hw_hdr_offset;

	/* 4 start to encrypt each fragment */
	अगर (pattrib->encrypt == _TKIP_) अणु

		अणु
			अगर (IS_MCAST(pattrib->ra))
				prwskey = psecuritypriv->करोt118021XGrpKey[psecuritypriv->करोt118021XGrpKeyid].skey;
			अन्यथा
				prwskey = pattrib->करोt118021x_UncstKey.skey;

			क्रम (curfragnum = 0; curfragnum < pattrib->nr_frags; curfragnum++) अणु
				iv = pframe+pattrib->hdrlen;
				payload = pframe+pattrib->iv_len+pattrib->hdrlen;

				GET_TKIP_PN(iv, करोt11txpn);

				pnl = (u16)(करोt11txpn.val);
				pnh = (u32)(करोt11txpn.val>>16);

				phase1((u16 *)&ttkey[0], prwskey, &pattrib->ta[0], pnh);

				phase2(&rc4key[0], prwskey, (u16 *)&ttkey[0], pnl);

				अगर ((curfragnum+1) == pattrib->nr_frags) अणु	/* 4 the last fragment */
					length = pattrib->last_txcmdsz-pattrib->hdrlen-pattrib->iv_len-pattrib->icv_len;
					*((__le32 *)crc) = अ_लोrc32(payload, length);/* modअगरied by Amy*/

					arcfour_init(&mycontext, rc4key, 16);
					arcfour_encrypt(&mycontext, payload, payload, length);
					arcfour_encrypt(&mycontext, payload+length, crc, 4);

				पूर्ण अन्यथा अणु
					length = pxmitpriv->frag_len-pattrib->hdrlen-pattrib->iv_len-pattrib->icv_len;
					*((__le32 *)crc) = अ_लोrc32(payload, length);/* modअगरied by Amy*/
					arcfour_init(&mycontext, rc4key, 16);
					arcfour_encrypt(&mycontext, payload, payload, length);
					arcfour_encrypt(&mycontext, payload+length, crc, 4);

					pframe += pxmitpriv->frag_len;
					pframe = (u8 *)round_up((SIZE_PTR)(pframe), 4);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	वापस res;
पूर्ण


/* The hlen isn't include the IV */
u32 rtw_tkip_decrypt(काष्ठा adapter *padapter, u8 *precvframe)
अणु																	/*  exclude ICV */
	u16 pnl;
	u32 pnh;
	u8   rc4key[16];
	u8   ttkey[16];
	u8 crc[4];
	काष्ठा arc4context mycontext;
	चिन्हित पूर्णांक			length;

	u8 *pframe, *payload, *iv, *prwskey;
	जोड़ pn48 करोt11txpn;
	काष्ठा sta_info *stainfo;
	काष्ठा rx_pkt_attrib *prxattrib = &((जोड़ recv_frame *)precvframe)->u.hdr.attrib;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	u32 res = _SUCCESS;

	pframe = (अचिन्हित अक्षर *)((जोड़ recv_frame *)precvframe)->u.hdr.rx_data;

	/* 4 start to decrypt recvframe */
	अगर (prxattrib->encrypt == _TKIP_) अणु
		stainfo = rtw_get_stainfo(&padapter->stapriv, &prxattrib->ta[0]);
		अगर (stainfo) अणु
			अगर (IS_MCAST(prxattrib->ra)) अणु
				अटल अचिन्हित दीर्घ start;
				अटल u32 no_gkey_bc_cnt;
				अटल u32 no_gkey_mc_cnt;

				अगर (!psecuritypriv->binstallGrpkey) अणु
					res = _FAIL;

					अगर (start == 0)
						start = jअगरfies;

					अगर (is_broadcast_mac_addr(prxattrib->ra))
						no_gkey_bc_cnt++;
					अन्यथा
						no_gkey_mc_cnt++;

					अगर (jअगरfies_to_msecs(jअगरfies - start) > 1000) अणु
						अगर (no_gkey_bc_cnt || no_gkey_mc_cnt) अणु
							netdev_dbg(padapter->pnetdev,
								   FUNC_ADPT_FMT " no_gkey_bc_cnt:%u, no_gkey_mc_cnt:%u\n",
								   FUNC_ADPT_ARG(padapter),
								   no_gkey_bc_cnt,
								   no_gkey_mc_cnt);
						पूर्ण
						start = jअगरfies;
						no_gkey_bc_cnt = 0;
						no_gkey_mc_cnt = 0;
					पूर्ण
					जाओ निकास;
				पूर्ण

				अगर (no_gkey_bc_cnt || no_gkey_mc_cnt) अणु
					netdev_dbg(padapter->pnetdev,
						   FUNC_ADPT_FMT " gkey installed. no_gkey_bc_cnt:%u, no_gkey_mc_cnt:%u\n",
						   FUNC_ADPT_ARG(padapter),
						   no_gkey_bc_cnt,
						   no_gkey_mc_cnt);
				पूर्ण
				start = 0;
				no_gkey_bc_cnt = 0;
				no_gkey_mc_cnt = 0;

				prwskey = psecuritypriv->करोt118021XGrpKey[prxattrib->key_index].skey;
			पूर्ण अन्यथा अणु
				prwskey = &stainfo->करोt118021x_UncstKey.skey[0];
			पूर्ण

			iv = pframe+prxattrib->hdrlen;
			payload = pframe+prxattrib->iv_len+prxattrib->hdrlen;
			length = ((जोड़ recv_frame *)precvframe)->u.hdr.len-prxattrib->hdrlen-prxattrib->iv_len;

			GET_TKIP_PN(iv, करोt11txpn);

			pnl = (u16)(करोt11txpn.val);
			pnh = (u32)(करोt11txpn.val>>16);

			phase1((u16 *)&ttkey[0], prwskey, &prxattrib->ta[0], pnh);
			phase2(&rc4key[0], prwskey, (अचिन्हित लघु *)&ttkey[0], pnl);

			/* 4 decrypt payload include icv */

			arcfour_init(&mycontext, rc4key, 16);
			arcfour_encrypt(&mycontext, payload, payload, length);

			*((u32 *)crc) = le32_to_cpu(अ_लोrc32(payload, length-4));

			अगर (crc[3] != payload[length - 1] || crc[2] != payload[length - 2] ||
			    crc[1] != payload[length - 3] || crc[0] != payload[length - 4])
				res = _FAIL;
		पूर्ण अन्यथा अणु
			res = _FAIL;
		पूर्ण
	पूर्ण
निकास:
	वापस res;
पूर्ण


/* 3			=====AES related ===== */



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

/*****************************/
/**** Function Prototypes ****/
/*****************************/

अटल व्योम bitwise_xor(u8 *ina, u8 *inb, u8 *out);
अटल व्योम स्थिरruct_mic_iv(u8 *mic_header1,
			     चिन्हित पूर्णांक qc_exists,
			     चिन्हित पूर्णांक a4_exists,
			     u8 *mpdu,
			     uपूर्णांक payload_length,
			     u8 *pn_vector,
			     uपूर्णांक frtype); /*  add क्रम CONFIG_IEEE80211W, none 11w also can use */
अटल व्योम स्थिरruct_mic_header1(u8 *mic_header1,
				  चिन्हित पूर्णांक header_length,
				  u8 *mpdu,
				  uपूर्णांक frtype); /* क्रम CONFIG_IEEE80211W, none 11w also can use */
अटल व्योम स्थिरruct_mic_header2(u8 *mic_header2,
				  u8 *mpdu,
				  चिन्हित पूर्णांक a4_exists,
				  चिन्हित पूर्णांक qc_exists);
अटल व्योम स्थिरruct_ctr_preload(u8 *ctr_preload,
				  चिन्हित पूर्णांक a4_exists,
				  चिन्हित पूर्णांक qc_exists,
				  u8 *mpdu,
				  u8 *pn_vector,
				  चिन्हित पूर्णांक c,
				  uपूर्णांक frtype); /* क्रम CONFIG_IEEE80211W, none 11w also can use */
अटल व्योम xor_128(u8 *a, u8 *b, u8 *out);
अटल व्योम xor_32(u8 *a, u8 *b, u8 *out);
अटल u8 sbox(u8 a);
अटल व्योम next_key(u8 *key, चिन्हित पूर्णांक round);
अटल व्योम byte_sub(u8 *in, u8 *out);
अटल व्योम shअगरt_row(u8 *in, u8 *out);
अटल व्योम mix_column(u8 *in, u8 *out);
अटल व्योम aes128k128d(u8 *key, u8 *data, u8 *ciphertext);


/****************************************/
/* aes128k128d()                        */
/* Perक्रमms a 128 bit AES encrypt with  */
/* 128 bit data.                        */
/****************************************/
अटल व्योम xor_128(u8 *a, u8 *b, u8 *out)
अणु
		चिन्हित पूर्णांक i;

		क्रम (i = 0; i < 16; i++)
			out[i] = a[i] ^ b[i];
पूर्ण


अटल व्योम xor_32(u8 *a, u8 *b, u8 *out)
अणु
		चिन्हित पूर्णांक i;

		क्रम (i = 0; i < 4; i++)
			out[i] = a[i] ^ b[i];
पूर्ण


अटल u8 sbox(u8 a)
अणु
		वापस sbox_table[(चिन्हित पूर्णांक)a];
पूर्ण


अटल व्योम next_key(u8 *key, चिन्हित पूर्णांक round)
अणु
		u8 rcon;
		u8 sbox_key[4];
		अटल स्थिर u8 rcon_table[12] = अणु
			0x01, 0x02, 0x04, 0x08,
			0x10, 0x20, 0x40, 0x80,
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
		चिन्हित पूर्णांक i;

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
		चिन्हित पूर्णांक i;
		u8 add1b[4];
		u8 add1bf7[4];
		u8 rotl[4];
		u8 swap_halfs[4];
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

		swap_halfs[0] = in[2];    /* Swap halfs */
		swap_halfs[1] = in[3];
		swap_halfs[2] = in[0];
		swap_halfs[3] = in[1];

		rotl[0] = in[3];        /* Rotate left 8 bits */
		rotl[1] = in[0];
		rotl[2] = in[1];
		rotl[3] = in[2];

		andf7[0] = in[0] & 0x7f;
		andf7[1] = in[1] & 0x7f;
		andf7[2] = in[2] & 0x7f;
		andf7[3] = in[3] & 0x7f;

		क्रम (i = 3; i > 0; i--) अणु  /* logical shअगरt left 1 bit */
			andf7[i] = andf7[i] << 1;
			अगर ((andf7[i-1] & 0x80) == 0x80)
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
		xor_32(swap_halfs, rotl, tempb);
		xor_32(temp, tempb, out);
पूर्ण

अटल व्योम aes128k128d(u8 *key, u8 *data, u8 *ciphertext)
अणु
		चिन्हित पूर्णांक round;
		चिन्हित पूर्णांक i;
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
/* Baron think the function is स्थिरruct CCM    */
/* nonce                                        */
/************************************************/
अटल व्योम स्थिरruct_mic_iv(u8 *mic_iv,
			     चिन्हित पूर्णांक qc_exists,
			     चिन्हित पूर्णांक a4_exists,
			     u8 *mpdu,
			     uपूर्णांक payload_length,
			     u8 *pn_vector,
			     uपूर्णांक frtype) /* add क्रम CONFIG_IEEE80211W, none 11w also can use */
अणु
		चिन्हित पूर्णांक i;

		mic_iv[0] = 0x59;

		अगर (qc_exists && a4_exists)
			mic_iv[1] = mpdu[30] & 0x0f;    /* QoS_TC           */

		अगर (qc_exists && !a4_exists)
			mic_iv[1] = mpdu[24] & 0x0f;   /* mute bits 7-4    */

		अगर (!qc_exists)
			mic_iv[1] = 0x00;

		/* 802.11w management frame should set management bit(4) */
		अगर (frtype == WIFI_MGT_TYPE)
			mic_iv[1] |= BIT(4);

		क्रम (i = 2; i < 8; i++)
			mic_iv[i] = mpdu[i + 8];   /* mic_iv[2:7] = A2[0:5] = mpdu[10:15] */
		#अगर_घोषित CONSISTENT_PN_ORDER
		क्रम (i = 8; i < 14; i++)
			mic_iv[i] = pn_vector[i - 8];           /* mic_iv[8:13] = PN[0:5] */
		#अन्यथा
		क्रम (i = 8; i < 14; i++)
			mic_iv[i] = pn_vector[13 - i];          /* mic_iv[8:13] = PN[5:0] */
		#पूर्ण_अगर
		mic_iv[14] = (अचिन्हित अक्षर) (payload_length / 256);
		mic_iv[15] = (अचिन्हित अक्षर) (payload_length % 256);
पूर्ण

/************************************************/
/* स्थिरruct_mic_header1()                      */
/* Builds the first MIC header block from       */
/* header fields.                               */
/* Build AAD SC, A1, A2                           */
/************************************************/
अटल व्योम स्थिरruct_mic_header1(u8 *mic_header1,
				  चिन्हित पूर्णांक header_length,
				  u8 *mpdu,
				  uपूर्णांक frtype) /* क्रम CONFIG_IEEE80211W, none 11w also can use */
अणु
		mic_header1[0] = (u8)((header_length - 2) / 256);
		mic_header1[1] = (u8)((header_length - 2) % 256);

		/* 802.11w management frame करोn't AND subtype bits 4, 5, 6 of frame control field */
		अगर (frtype == WIFI_MGT_TYPE)
			mic_header1[2] = mpdu[0];
		अन्यथा
			mic_header1[2] = mpdu[0] & 0xcf;    /* Mute CF poll & CF ack bits */

		mic_header1[3] = mpdu[1] & 0xc7;    /* Mute retry, more data and pwr mgt bits */
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
अटल व्योम स्थिरruct_mic_header2(u8 *mic_header2,
				  u8 *mpdu,
				  चिन्हित पूर्णांक a4_exists,
				  चिन्हित पूर्णांक qc_exists)
अणु
		चिन्हित पूर्णांक i;

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

		अगर (!qc_exists && a4_exists) अणु
			क्रम (i = 0; i < 6; i++)
				mic_header2[8+i] = mpdu[24+i];   /* A4 */
		पूर्ण

		अगर (qc_exists && !a4_exists) अणु
			mic_header2[8] = mpdu[24] & 0x0f; /* mute bits 15 - 4 */
			mic_header2[9] = mpdu[25] & 0x00;
		पूर्ण

		अगर (qc_exists && a4_exists) अणु
			क्रम (i = 0; i < 6; i++)
				mic_header2[8+i] = mpdu[24+i];   /* A4 */

			mic_header2[14] = mpdu[30] & 0x0f;
			mic_header2[15] = mpdu[31] & 0x00;
		पूर्ण
पूर्ण

/************************************************/
/* स्थिरruct_mic_header2()                      */
/* Builds the last MIC header block from        */
/* header fields.                               */
/* Baron think the function is स्थिरruct CCM    */
/* nonce                                        */
/************************************************/
अटल व्योम स्थिरruct_ctr_preload(u8 *ctr_preload,
				  चिन्हित पूर्णांक a4_exists,
				  चिन्हित पूर्णांक qc_exists,
				  u8 *mpdu,
				  u8 *pn_vector,
				  चिन्हित पूर्णांक c,
				  uपूर्णांक frtype) /* क्रम CONFIG_IEEE80211W, none 11w also can use */
अणु
	चिन्हित पूर्णांक i = 0;

	क्रम (i = 0; i < 16; i++)
		ctr_preload[i] = 0x00;
	i = 0;

	ctr_preload[0] = 0x01;                                  /* flag */
	अगर (qc_exists && a4_exists)
		ctr_preload[1] = mpdu[30] & 0x0f;   /* QoC_Control */
	अगर (qc_exists && !a4_exists)
		ctr_preload[1] = mpdu[24] & 0x0f;

	/* 802.11w management frame should set management bit(4) */
	अगर (frtype == WIFI_MGT_TYPE)
		ctr_preload[1] |= BIT(4);

	क्रम (i = 2; i < 8; i++)
		ctr_preload[i] = mpdu[i + 8];                       /* ctr_preload[2:7] = A2[0:5] = mpdu[10:15] */
#अगर_घोषित CONSISTENT_PN_ORDER
	क्रम (i = 8; i < 14; i++)
		ctr_preload[i] =    pn_vector[i - 8];           /* ctr_preload[8:13] = PN[0:5] */
#अन्यथा
	क्रम (i = 8; i < 14; i++)
		ctr_preload[i] =    pn_vector[13 - i];          /* ctr_preload[8:13] = PN[5:0] */
#पूर्ण_अगर
	ctr_preload[14] =  (अचिन्हित अक्षर) (c / 256); /* Ctr */
	ctr_preload[15] =  (अचिन्हित अक्षर) (c % 256);
पूर्ण

/************************************/
/* bitwise_xor()                    */
/* A 128 bit, bitwise exclusive or  */
/************************************/
अटल व्योम bitwise_xor(u8 *ina, u8 *inb, u8 *out)
अणु
		चिन्हित पूर्णांक i;

		क्रम (i = 0; i < 16; i++)
			out[i] = ina[i] ^ inb[i];
पूर्ण

अटल चिन्हित पूर्णांक aes_cipher(u8 *key, uपूर्णांक	hdrlen,
			u8 *pframe, uपूर्णांक plen)
अणु
	uपूर्णांक	qc_exists, a4_exists, i, j, payload_reमुख्यder,
		num_blocks, payload_index;

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
	uपूर्णांक	frtype  = GetFrameType(pframe);
	uपूर्णांक	frsubtype  = GetFrameSubType(pframe);

	frsubtype = frsubtype>>4;

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

	अगर (((frtype|frsubtype) == WIFI_DATA_CFACK) ||
	    ((frtype|frsubtype) == WIFI_DATA_CFPOLL) ||
	    ((frtype|frsubtype) == WIFI_DATA_CFACKPOLL)) अणु
		qc_exists = 1;
		अगर (hdrlen !=  WLAN_HDR_A3_QOS_LEN)
			hdrlen += 2;

	पूर्ण अन्यथा अगर ((frtype == WIFI_DATA) && /*  add क्रम CONFIG_IEEE80211W, none 11w also can use */
		   ((frsubtype == 0x08) ||
		   (frsubtype == 0x09) ||
		   (frsubtype == 0x0a) ||
		   (frsubtype == 0x0b))) अणु
		अगर (hdrlen !=  WLAN_HDR_A3_QOS_LEN)
			hdrlen += 2;

		qc_exists = 1;
	पूर्ण अन्यथा अणु
		qc_exists = 0;
	पूर्ण

	pn_vector[0] = pframe[hdrlen];
	pn_vector[1] = pframe[hdrlen+1];
	pn_vector[2] = pframe[hdrlen+4];
	pn_vector[3] = pframe[hdrlen+5];
	pn_vector[4] = pframe[hdrlen+6];
	pn_vector[5] = pframe[hdrlen+7];

	स्थिरruct_mic_iv(mic_iv,
			 qc_exists,
			 a4_exists,
			 pframe,	 /* message, */
			 plen,
			 pn_vector,
			 frtype); /*  add क्रम CONFIG_IEEE80211W, none 11w also can use */

	स्थिरruct_mic_header1(mic_header1,
			      hdrlen,
			      pframe,	/* message */
			      frtype); /*  add क्रम CONFIG_IEEE80211W, none 11w also can use */

	स्थिरruct_mic_header2(mic_header2,
			      pframe,	/* message, */
			      a4_exists,
			      qc_exists);

	payload_reमुख्यder = plen % 16;
	num_blocks = plen / 16;

	/* Find start of payload */
	payload_index = (hdrlen + 8);

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

	क्रम (j = 0 ; j < 8; j++)
		mic[j] = aes_out[j];

	/* Insert MIC पूर्णांकo payload */
	क्रम (j = 0; j < 8; j++)
		pframe[payload_index+j] = mic[j];

	payload_index = hdrlen + 8;
	क्रम (i = 0; i < num_blocks; i++) अणु
		स्थिरruct_ctr_preload(ctr_preload, a4_exists, qc_exists, pframe, /* message, */
				      pn_vector, i+1, frtype);
		/*  add क्रम CONFIG_IEEE80211W, none 11w also can use */
		aes128k128d(key, ctr_preload, aes_out);
		bitwise_xor(aes_out, &pframe[payload_index], chain_buffer);
		क्रम (j = 0; j < 16; j++)
			pframe[payload_index++] = chain_buffer[j];
	पूर्ण

	अगर (payload_reमुख्यder > 0) अणु
		/* If there is a लघु final block, then pad it,*/
		/* encrypt it and copy the unpadded part back   */
		स्थिरruct_ctr_preload(ctr_preload, a4_exists, qc_exists, pframe, /* message, */
				      pn_vector, num_blocks+1, frtype);
		/*  add क्रम CONFIG_IEEE80211W, none 11w also can use */

		क्रम (j = 0; j < 16; j++)
			padded_buffer[j] = 0x00;
		क्रम (j = 0; j < payload_reमुख्यder; j++)
			padded_buffer[j] = pframe[payload_index+j];

		aes128k128d(key, ctr_preload, aes_out);
		bitwise_xor(aes_out, padded_buffer, chain_buffer);
		क्रम (j = 0; j < payload_reमुख्यder; j++)
			pframe[payload_index++] = chain_buffer[j];
	पूर्ण

	/* Encrypt the MIC */
	स्थिरruct_ctr_preload(ctr_preload, a4_exists, qc_exists, pframe, /* message, */
			      pn_vector, 0, frtype);
	/*  add क्रम CONFIG_IEEE80211W, none 11w also can use */

	क्रम (j = 0; j < 16; j++)
		padded_buffer[j] = 0x00;
	क्रम (j = 0; j < 8; j++)
		padded_buffer[j] = pframe[j+hdrlen+8+plen];

	aes128k128d(key, ctr_preload, aes_out);
	bitwise_xor(aes_out, padded_buffer, chain_buffer);
	क्रम (j = 0; j < 8; j++)
		pframe[payload_index++] = chain_buffer[j];

	वापस _SUCCESS;
पूर्ण

u32 rtw_aes_encrypt(काष्ठा adapter *padapter, u8 *pxmitframe)
अणु	/*  exclude ICV */

	/*अटल*/
	/* अचिन्हित अक्षर message[MAX_MSG_SIZE]; */

	/* Intermediate Buffers */
	चिन्हित पूर्णांक curfragnum, length;
	u8 *pframe, *prwskey;	/*  *payload,*iv */
	u8 hw_hdr_offset = 0;
	काष्ठा pkt_attrib *pattrib = &((काष्ठा xmit_frame *)pxmitframe)->attrib;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;

	u32 res = _SUCCESS;

	अगर (((काष्ठा xmit_frame *)pxmitframe)->buf_addr == शून्य)
		वापस _FAIL;

	hw_hdr_offset = TXDESC_OFFSET;
	pframe = ((काष्ठा xmit_frame *)pxmitframe)->buf_addr + hw_hdr_offset;

	/* 4 start to encrypt each fragment */
	अगर (pattrib->encrypt == _AES_) अणु
		अगर (IS_MCAST(pattrib->ra))
			prwskey = psecuritypriv->करोt118021XGrpKey[psecuritypriv->करोt118021XGrpKeyid].skey;
		अन्यथा
			prwskey = pattrib->करोt118021x_UncstKey.skey;

		क्रम (curfragnum = 0; curfragnum < pattrib->nr_frags; curfragnum++) अणु
			अगर ((curfragnum+1) == pattrib->nr_frags) अणु	/* 4 the last fragment */
				length = pattrib->last_txcmdsz-pattrib->hdrlen-pattrib->iv_len-pattrib->icv_len;

				aes_cipher(prwskey, pattrib->hdrlen, pframe, length);
			पूर्ण अन्यथा अणु
				length = pxmitpriv->frag_len-pattrib->hdrlen-pattrib->iv_len-pattrib->icv_len;

				aes_cipher(prwskey, pattrib->hdrlen, pframe, length);
				pframe += pxmitpriv->frag_len;
				pframe = (u8 *)round_up((SIZE_PTR)(pframe), 4);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस res;
पूर्ण

अटल चिन्हित पूर्णांक aes_decipher(u8 *key, uपूर्णांक	hdrlen,
			 u8 *pframe, uपूर्णांक plen)
अणु
	अटल u8 message[MAX_MSG_SIZE];
	uपूर्णांक qc_exists, a4_exists, i, j, payload_reमुख्यder,
			num_blocks, payload_index;
	चिन्हित पूर्णांक res = _SUCCESS;
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

	frsubtype = frsubtype>>4;

	स_रखो((व्योम *)mic_iv, 0, 16);
	स_रखो((व्योम *)mic_header1, 0, 16);
	स_रखो((व्योम *)mic_header2, 0, 16);
	स_रखो((व्योम *)ctr_preload, 0, 16);
	स_रखो((व्योम *)chain_buffer, 0, 16);
	स_रखो((व्योम *)aes_out, 0, 16);
	स_रखो((व्योम *)padded_buffer, 0, 16);

	/* start to decrypt the payload */

	num_blocks = (plen-8) / 16; /* plen including LLC, payload_length and mic) */

	payload_reमुख्यder = (plen-8) % 16;

	pn_vector[0]  = pframe[hdrlen];
	pn_vector[1]  = pframe[hdrlen + 1];
	pn_vector[2]  = pframe[hdrlen + 4];
	pn_vector[3]  = pframe[hdrlen + 5];
	pn_vector[4]  = pframe[hdrlen + 6];
	pn_vector[5]  = pframe[hdrlen + 7];

	अगर ((hdrlen == WLAN_HDR_A3_LEN) || (hdrlen ==  WLAN_HDR_A3_QOS_LEN))
		a4_exists = 0;
	अन्यथा
		a4_exists = 1;

	अगर (((frtype|frsubtype) == WIFI_DATA_CFACK) ||
	    ((frtype|frsubtype) == WIFI_DATA_CFPOLL) ||
	    ((frtype|frsubtype) == WIFI_DATA_CFACKPOLL)) अणु
		qc_exists = 1;
		अगर (hdrlen !=  WLAN_HDR_A3_QOS_LEN)
			hdrlen += 2;

	पूर्ण अन्यथा अगर ((frtype == WIFI_DATA) && /* only क्रम data packet . add क्रम CONFIG_IEEE80211W, none 11w also can use */
		   ((frsubtype == 0x08) ||
		   (frsubtype == 0x09) ||
		   (frsubtype == 0x0a) ||
		   (frsubtype == 0x0b))) अणु
		अगर (hdrlen !=  WLAN_HDR_A3_QOS_LEN)
			hdrlen += 2;

		qc_exists = 1;
	पूर्ण अन्यथा अणु
		qc_exists = 0;
	पूर्ण

	/*  now, decrypt pframe with hdrlen offset and plen दीर्घ */

	payload_index = hdrlen + 8; /*  8 is क्रम extiv */

	क्रम (i = 0; i < num_blocks; i++) अणु
		स्थिरruct_ctr_preload(ctr_preload, a4_exists,
				      qc_exists, pframe,
				      pn_vector, i + 1,
				      frtype); /*  add क्रम CONFIG_IEEE80211W, none 11w also can use */

		aes128k128d(key, ctr_preload, aes_out);
		bitwise_xor(aes_out, &pframe[payload_index], chain_buffer);

		क्रम (j = 0; j < 16; j++)
			pframe[payload_index++] = chain_buffer[j];
	पूर्ण

	अगर (payload_reमुख्यder > 0) अणु
		/* If there is a लघु final block, then pad it,*/
		/* encrypt it and copy the unpadded part back   */
		स्थिरruct_ctr_preload(ctr_preload, a4_exists, qc_exists, pframe, pn_vector,
				      num_blocks+1, frtype);
		/*  add क्रम CONFIG_IEEE80211W, none 11w also can use */

		क्रम (j = 0; j < 16; j++)
			padded_buffer[j] = 0x00;
		क्रम (j = 0; j < payload_reमुख्यder; j++)
			padded_buffer[j] = pframe[payload_index+j];

		aes128k128d(key, ctr_preload, aes_out);
		bitwise_xor(aes_out, padded_buffer, chain_buffer);
		क्रम (j = 0; j < payload_reमुख्यder; j++)
			pframe[payload_index++] = chain_buffer[j];
	पूर्ण

	/* start to calculate the mic */
	अगर ((hdrlen + plen+8) <= MAX_MSG_SIZE)
		स_नकल((व्योम *)message, pframe, (hdrlen + plen+8)); /* 8 is क्रम ext iv len */

	pn_vector[0] = pframe[hdrlen];
	pn_vector[1] = pframe[hdrlen+1];
	pn_vector[2] = pframe[hdrlen+4];
	pn_vector[3] = pframe[hdrlen+5];
	pn_vector[4] = pframe[hdrlen+6];
	pn_vector[5] = pframe[hdrlen+7];

	स्थिरruct_mic_iv(mic_iv, qc_exists, a4_exists, message, plen-8, pn_vector, frtype);
	/*  add क्रम CONFIG_IEEE80211W, none 11w also can use */

	स्थिरruct_mic_header1(mic_header1, hdrlen, message, frtype);
	/*  add क्रम CONFIG_IEEE80211W, none 11w also can use */
	स्थिरruct_mic_header2(mic_header2, message, a4_exists, qc_exists);

	payload_reमुख्यder = (plen-8) % 16;
	num_blocks = (plen-8) / 16;

	/* Find start of payload */
	payload_index = (hdrlen + 8);

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
		message[payload_index+j] = mic[j];

	payload_index = hdrlen + 8;
	क्रम (i = 0; i < num_blocks; i++) अणु
		स्थिरruct_ctr_preload(ctr_preload, a4_exists, qc_exists, message, pn_vector, i+1,
				      frtype);
		/*  add क्रम CONFIG_IEEE80211W, none 11w also can use */
		aes128k128d(key, ctr_preload, aes_out);
		bitwise_xor(aes_out, &message[payload_index], chain_buffer);
		क्रम (j = 0; j < 16; j++)
			message[payload_index++] = chain_buffer[j];
	पूर्ण

	अगर (payload_reमुख्यder > 0) अणु
		/* If there is a लघु final block, then pad it,*/
		/* encrypt it and copy the unpadded part back   */
		स्थिरruct_ctr_preload(ctr_preload, a4_exists, qc_exists, message, pn_vector,
				      num_blocks+1, frtype);
		/*  add क्रम CONFIG_IEEE80211W, none 11w also can use */

		क्रम (j = 0; j < 16; j++)
			padded_buffer[j] = 0x00;
		क्रम (j = 0; j < payload_reमुख्यder; j++)
			padded_buffer[j] = message[payload_index+j];

		aes128k128d(key, ctr_preload, aes_out);
		bitwise_xor(aes_out, padded_buffer, chain_buffer);
		क्रम (j = 0; j < payload_reमुख्यder; j++)
			message[payload_index++] = chain_buffer[j];
	पूर्ण

	/* Encrypt the MIC */
	स्थिरruct_ctr_preload(ctr_preload, a4_exists, qc_exists, message, pn_vector, 0, frtype);
	/*  add क्रम CONFIG_IEEE80211W, none 11w also can use */

	क्रम (j = 0; j < 16; j++)
		padded_buffer[j] = 0x00;
	क्रम (j = 0; j < 8; j++)
		padded_buffer[j] = message[j+hdrlen+8+plen-8];

	aes128k128d(key, ctr_preload, aes_out);
	bitwise_xor(aes_out, padded_buffer, chain_buffer);
	क्रम (j = 0; j < 8; j++)
		message[payload_index++] = chain_buffer[j];

	/* compare the mic */
	क्रम (i = 0; i < 8; i++) अणु
		अगर (pframe[hdrlen + 8 + plen - 8 + i] != message[hdrlen + 8 + plen - 8 + i])
			res = _FAIL;
	पूर्ण
	वापस res;
पूर्ण

u32 rtw_aes_decrypt(काष्ठा adapter *padapter, u8 *precvframe)
अणु	/*  exclude ICV */

	/*अटल*/
	/* अचिन्हित अक्षर message[MAX_MSG_SIZE]; */

	/* Intermediate Buffers */

	चिन्हित पूर्णांक length;
	u8 *pframe, *prwskey;	/*  *payload,*iv */
	काष्ठा sta_info *stainfo;
	काष्ठा rx_pkt_attrib *prxattrib = &((जोड़ recv_frame *)precvframe)->u.hdr.attrib;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	u32 res = _SUCCESS;

	pframe = (अचिन्हित अक्षर *)((जोड़ recv_frame *)precvframe)->u.hdr.rx_data;
	/* 4 start to encrypt each fragment */
	अगर (prxattrib->encrypt == _AES_) अणु
		stainfo = rtw_get_stainfo(&padapter->stapriv, &prxattrib->ta[0]);
		अगर (stainfo) अणु
			अगर (IS_MCAST(prxattrib->ra)) अणु
				अटल अचिन्हित दीर्घ start;
				अटल u32 no_gkey_bc_cnt;
				अटल u32 no_gkey_mc_cnt;

				अगर (!psecuritypriv->binstallGrpkey) अणु
					res = _FAIL;

					अगर (start == 0)
						start = jअगरfies;

					अगर (is_broadcast_mac_addr(prxattrib->ra))
						no_gkey_bc_cnt++;
					अन्यथा
						no_gkey_mc_cnt++;

					अगर (jअगरfies_to_msecs(jअगरfies - start) > 1000) अणु
						अगर (no_gkey_bc_cnt || no_gkey_mc_cnt) अणु
							netdev_dbg(padapter->pnetdev,
								   FUNC_ADPT_FMT " no_gkey_bc_cnt:%u, no_gkey_mc_cnt:%u\n",
								   FUNC_ADPT_ARG(padapter),
								   no_gkey_bc_cnt,
								   no_gkey_mc_cnt);
						पूर्ण
						start = jअगरfies;
						no_gkey_bc_cnt = 0;
						no_gkey_mc_cnt = 0;
					पूर्ण

					जाओ निकास;
				पूर्ण

				अगर (no_gkey_bc_cnt || no_gkey_mc_cnt) अणु
					netdev_dbg(padapter->pnetdev,
						   FUNC_ADPT_FMT " gkey installed. no_gkey_bc_cnt:%u, no_gkey_mc_cnt:%u\n",
						   FUNC_ADPT_ARG(padapter),
						   no_gkey_bc_cnt,
						   no_gkey_mc_cnt);
				पूर्ण
				start = 0;
				no_gkey_bc_cnt = 0;
				no_gkey_mc_cnt = 0;

				prwskey = psecuritypriv->करोt118021XGrpKey[prxattrib->key_index].skey;
				अगर (psecuritypriv->करोt118021XGrpKeyid != prxattrib->key_index) अणु
					res = _FAIL;
					जाओ निकास;
				पूर्ण
			पूर्ण अन्यथा अणु
				prwskey = &stainfo->करोt118021x_UncstKey.skey[0];
			पूर्ण

			length = ((जोड़ recv_frame *)precvframe)->u.hdr.len-prxattrib->hdrlen-prxattrib->iv_len;

			res = aes_decipher(prwskey, prxattrib->hdrlen, pframe, length);

		पूर्ण अन्यथा अणु
			res = _FAIL;
		पूर्ण
	पूर्ण
निकास:
	वापस res;
पूर्ण

u32 rtw_BIP_verअगरy(काष्ठा adapter *padapter, u8 *precvframe)
अणु
	काष्ठा rx_pkt_attrib *pattrib = &((जोड़ recv_frame *)precvframe)->u.hdr.attrib;
	u8 *pframe;
	u8 *BIP_AAD, *p;
	u32 res = _FAIL;
	uपूर्णांक len, ori_len;
	काष्ठा ieee80211_hdr *pwlanhdr;
	u8 mic[16];
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	__le16 le_पंचांगp;
	__le64 le_पंचांगp64;

	ori_len = pattrib->pkt_len-WLAN_HDR_A3_LEN+BIP_AAD_SIZE;
	BIP_AAD = rtw_zदो_स्मृति(ori_len);

	अगर (!BIP_AAD)
		वापस _FAIL;

	/* PKT start */
	pframe = (अचिन्हित अक्षर *)((जोड़ recv_frame *)precvframe)->u.hdr.rx_data;
	/* mapping to wlan header */
	pwlanhdr = (काष्ठा ieee80211_hdr *)pframe;
	/* save the frame body + MME */
	स_नकल(BIP_AAD+BIP_AAD_SIZE, pframe+WLAN_HDR_A3_LEN, pattrib->pkt_len-WLAN_HDR_A3_LEN);
	/* find MME IE poपूर्णांकer */
	p = rtw_get_ie(BIP_AAD+BIP_AAD_SIZE, WLAN_EID_MMIE, &len, pattrib->pkt_len-WLAN_HDR_A3_LEN);
	/* Baron */
	अगर (p) अणु
		u16 keyid = 0;
		u64 temp_ipn = 0;
		/* save packet number */
		स_नकल(&le_पंचांगp64, p+4, 6);
		temp_ipn = le64_to_cpu(le_पंचांगp64);
		/* BIP packet number should bigger than previous BIP packet */
		अगर (temp_ipn <= pmlmeext->mgnt_80211w_IPN_rx)
			जाओ BIP_निकास;

		/* copy key index */
		स_नकल(&le_पंचांगp, p+2, 2);
		keyid = le16_to_cpu(le_पंचांगp);
		अगर (keyid != padapter->securitypriv.करोt11wBIPKeyid)
			जाओ BIP_निकास;

		/* clear the MIC field of MME to zero */
		स_रखो(p+2+len-8, 0, 8);

		/* conscruct AAD, copy frame control field */
		स_नकल(BIP_AAD, &pwlanhdr->frame_control, 2);
		ClearRetry(BIP_AAD);
		ClearPwrMgt(BIP_AAD);
		ClearMData(BIP_AAD);
		/* conscruct AAD, copy address 1 to address 3 */
		स_नकल(BIP_AAD+2, pwlanhdr->addr1, 18);

		अगर (omac1_aes_128(padapter->securitypriv.करोt11wBIPKey[padapter->securitypriv.करोt11wBIPKeyid].skey
			, BIP_AAD, ori_len, mic))
			जाओ BIP_निकास;

		/* MIC field should be last 8 bytes of packet (packet without FCS) */
		अगर (!स_भेद(mic, pframe+pattrib->pkt_len-8, 8)) अणु
			pmlmeext->mgnt_80211w_IPN_rx = temp_ipn;
			res = _SUCCESS;
		पूर्ण अन्यथा अणु
		पूर्ण

	पूर्ण अन्यथा अणु
		res = RTW_RX_HANDLED;
	पूर्ण
BIP_निकास:

	kमुक्त(BIP_AAD);
	वापस res;
पूर्ण

/* AES tables*/
स्थिर u32 Te0[256] = अणु
	0xc66363a5U, 0xf87c7c84U, 0xee777799U, 0xf67b7b8dU,
	0xfff2f20dU, 0xd66b6bbdU, 0xde6f6fb1U, 0x91c5c554U,
	0x60303050U, 0x02010103U, 0xce6767a9U, 0x562b2b7dU,
	0xe7fefe19U, 0xb5d7d762U, 0x4dababe6U, 0xec76769aU,
	0x8fcaca45U, 0x1f82829dU, 0x89c9c940U, 0xfa7d7d87U,
	0xeffafa15U, 0xb25959ebU, 0x8e4747c9U, 0xfbf0f00bU,
	0x41adadecU, 0xb3d4d467U, 0x5fa2a2fdU, 0x45afafeaU,
	0x239c9cbfU, 0x53a4a4f7U, 0xe4727296U, 0x9bc0c05bU,
	0x75b7b7c2U, 0xe1fdfd1cU, 0x3d9393aeU, 0x4c26266aU,
	0x6c36365aU, 0x7e3f3f41U, 0xf5f7f702U, 0x83cccc4fU,
	0x6834345cU, 0x51a5a5f4U, 0xd1e5e534U, 0xf9f1f108U,
	0xe2717193U, 0xabd8d873U, 0x62313153U, 0x2a15153fU,
	0x0804040cU, 0x95c7c752U, 0x46232365U, 0x9dc3c35eU,
	0x30181828U, 0x379696a1U, 0x0a05050fU, 0x2f9a9ab5U,
	0x0e070709U, 0x24121236U, 0x1b80809bU, 0xdfe2e23dU,
	0xcdebeb26U, 0x4e272769U, 0x7fb2b2cdU, 0xea75759fU,
	0x1209091bU, 0x1d83839eU, 0x582c2c74U, 0x341a1a2eU,
	0x361b1b2dU, 0xdc6e6eb2U, 0xb45a5aeeU, 0x5ba0a0fbU,
	0xa45252f6U, 0x763b3b4dU, 0xb7d6d661U, 0x7db3b3ceU,
	0x5229297bU, 0xdde3e33eU, 0x5e2f2f71U, 0x13848497U,
	0xa65353f5U, 0xb9d1d168U, 0x00000000U, 0xc1eded2cU,
	0x40202060U, 0xe3fcfc1fU, 0x79b1b1c8U, 0xb65b5bedU,
	0xd46a6abeU, 0x8dcbcb46U, 0x67bebed9U, 0x7239394bU,
	0x944a4adeU, 0x984c4cd4U, 0xb05858e8U, 0x85cfcf4aU,
	0xbbd0d06bU, 0xc5efef2aU, 0x4faaaae5U, 0xedfbfb16U,
	0x864343c5U, 0x9a4d4dd7U, 0x66333355U, 0x11858594U,
	0x8a4545cfU, 0xe9f9f910U, 0x04020206U, 0xfe7f7f81U,
	0xa05050f0U, 0x783c3c44U, 0x259f9fbaU, 0x4ba8a8e3U,
	0xa25151f3U, 0x5da3a3feU, 0x804040c0U, 0x058f8f8aU,
	0x3f9292adU, 0x219d9dbcU, 0x70383848U, 0xf1f5f504U,
	0x63bcbcdfU, 0x77b6b6c1U, 0xafdada75U, 0x42212163U,
	0x20101030U, 0xe5ffff1aU, 0xfdf3f30eU, 0xbfd2d26dU,
	0x81cdcd4cU, 0x180c0c14U, 0x26131335U, 0xc3ecec2fU,
	0xbe5f5fe1U, 0x359797a2U, 0x884444ccU, 0x2e171739U,
	0x93c4c457U, 0x55a7a7f2U, 0xfc7e7e82U, 0x7a3d3d47U,
	0xc86464acU, 0xba5d5de7U, 0x3219192bU, 0xe6737395U,
	0xc06060a0U, 0x19818198U, 0x9e4f4fd1U, 0xa3dcdc7fU,
	0x44222266U, 0x542a2a7eU, 0x3b9090abU, 0x0b888883U,
	0x8c4646caU, 0xc7eeee29U, 0x6bb8b8d3U, 0x2814143cU,
	0xa7dede79U, 0xbc5e5ee2U, 0x160b0b1dU, 0xaddbdb76U,
	0xdbe0e03bU, 0x64323256U, 0x743a3a4eU, 0x140a0a1eU,
	0x924949dbU, 0x0c06060aU, 0x4824246cU, 0xb85c5ce4U,
	0x9fc2c25dU, 0xbdd3d36eU, 0x43acacefU, 0xc46262a6U,
	0x399191a8U, 0x319595a4U, 0xd3e4e437U, 0xf279798bU,
	0xd5e7e732U, 0x8bc8c843U, 0x6e373759U, 0xda6d6db7U,
	0x018d8d8cU, 0xb1d5d564U, 0x9c4e4ed2U, 0x49a9a9e0U,
	0xd86c6cb4U, 0xac5656faU, 0xf3f4f407U, 0xcfeaea25U,
	0xca6565afU, 0xf47a7a8eU, 0x47aeaee9U, 0x10080818U,
	0x6fbabad5U, 0xf0787888U, 0x4a25256fU, 0x5c2e2e72U,
	0x381c1c24U, 0x57a6a6f1U, 0x73b4b4c7U, 0x97c6c651U,
	0xcbe8e823U, 0xa1dddd7cU, 0xe874749cU, 0x3e1f1f21U,
	0x964b4bddU, 0x61bdbddcU, 0x0d8b8b86U, 0x0f8a8a85U,
	0xe0707090U, 0x7c3e3e42U, 0x71b5b5c4U, 0xcc6666aaU,
	0x904848d8U, 0x06030305U, 0xf7f6f601U, 0x1c0e0e12U,
	0xc26161a3U, 0x6a35355fU, 0xae5757f9U, 0x69b9b9d0U,
	0x17868691U, 0x99c1c158U, 0x3a1d1d27U, 0x279e9eb9U,
	0xd9e1e138U, 0xebf8f813U, 0x2b9898b3U, 0x22111133U,
	0xd26969bbU, 0xa9d9d970U, 0x078e8e89U, 0x339494a7U,
	0x2d9b9bb6U, 0x3c1e1e22U, 0x15878792U, 0xc9e9e920U,
	0x87cece49U, 0xaa5555ffU, 0x50282878U, 0xa5dfdf7aU,
	0x038c8c8fU, 0x59a1a1f8U, 0x09898980U, 0x1a0d0d17U,
	0x65bfbfdaU, 0xd7e6e631U, 0x844242c6U, 0xd06868b8U,
	0x824141c3U, 0x299999b0U, 0x5a2d2d77U, 0x1e0f0f11U,
	0x7bb0b0cbU, 0xa85454fcU, 0x6dbbbbd6U, 0x2c16163aU,
पूर्ण;

स्थिर u32 Td0[256] = अणु
	0x51f4a750U, 0x7e416553U, 0x1a17a4c3U, 0x3a275e96U,
	0x3bab6bcbU, 0x1f9d45f1U, 0xacfa58abU, 0x4be30393U,
	0x2030fa55U, 0xad766df6U, 0x88cc7691U, 0xf5024c25U,
	0x4fe5d7fcU, 0xc52acbd7U, 0x26354480U, 0xb562a38fU,
	0xdeb15a49U, 0x25ba1b67U, 0x45ea0e98U, 0x5dfec0e1U,
	0xc32f7502U, 0x814cf012U, 0x8d4697a3U, 0x6bd3f9c6U,
	0x038f5fe7U, 0x15929c95U, 0xbf6d7aebU, 0x955259daU,
	0xd4be832dU, 0x587421d3U, 0x49e06929U, 0x8ec9c844U,
	0x75c2896aU, 0xf48e7978U, 0x99583e6bU, 0x27b971ddU,
	0xbee14fb6U, 0xf088ad17U, 0xc920ac66U, 0x7dce3ab4U,
	0x63df4a18U, 0xe51a3182U, 0x97513360U, 0x62537f45U,
	0xb16477e0U, 0xbb6bae84U, 0xfe81a01cU, 0xf9082b94U,
	0x70486858U, 0x8f45fd19U, 0x94de6c87U, 0x527bf8b7U,
	0xab73d323U, 0x724b02e2U, 0xe31f8f57U, 0x6655ab2aU,
	0xb2eb2807U, 0x2fb5c203U, 0x86c57b9aU, 0xd33708a5U,
	0x302887f2U, 0x23bfa5b2U, 0x02036abaU, 0xed16825cU,
	0x8acf1c2bU, 0xa779b492U, 0xf307f2f0U, 0x4e69e2a1U,
	0x65daf4cdU, 0x0605bed5U, 0xd134621fU, 0xc4a6fe8aU,
	0x342e539dU, 0xa2f355a0U, 0x058ae132U, 0xa4f6eb75U,
	0x0b83ec39U, 0x4060efaaU, 0x5e719f06U, 0xbd6e1051U,
	0x3e218af9U, 0x96dd063dU, 0xdd3e05aeU, 0x4de6bd46U,
	0x91548db5U, 0x71c45d05U, 0x0406d46fU, 0x605015ffU,
	0x1998fb24U, 0xd6bde997U, 0x894043ccU, 0x67d99e77U,
	0xb0e842bdU, 0x07898b88U, 0xe7195b38U, 0x79c8eedbU,
	0xa17c0a47U, 0x7c420fe9U, 0xf8841ec9U, 0x00000000U,
	0x09808683U, 0x322bed48U, 0x1e1170acU, 0x6c5a724eU,
	0xfd0efffbU, 0x0f853856U, 0x3daed51eU, 0x362d3927U,
	0x0a0fd964U, 0x685ca621U, 0x9b5b54d1U, 0x24362e3aU,
	0x0c0a67b1U, 0x9357e70fU, 0xb4ee96d2U, 0x1b9b919eU,
	0x80c0c54fU, 0x61dc20a2U, 0x5a774b69U, 0x1c121a16U,
	0xe293ba0aU, 0xc0a02ae5U, 0x3c22e043U, 0x121b171dU,
	0x0e090d0bU, 0xf28bc7adU, 0x2db6a8b9U, 0x141ea9c8U,
	0x57f11985U, 0xaf75074cU, 0xee99ddbbU, 0xa37f60fdU,
	0xf701269fU, 0x5c72f5bcU, 0x44663bc5U, 0x5bfb7e34U,
	0x8b432976U, 0xcb23c6dcU, 0xb6edfc68U, 0xb8e4f163U,
	0xd731dccaU, 0x42638510U, 0x13972240U, 0x84c61120U,
	0x854a247dU, 0xd2bb3df8U, 0xaef93211U, 0xc729a16dU,
	0x1d9e2f4bU, 0xdcb230f3U, 0x0d8652ecU, 0x77c1e3d0U,
	0x2bb3166cU, 0xa970b999U, 0x119448faU, 0x47e96422U,
	0xa8fc8cc4U, 0xa0f03f1aU, 0x567d2cd8U, 0x223390efU,
	0x87494ec7U, 0xd938d1c1U, 0x8ccaa2feU, 0x98d40b36U,
	0xa6f581cfU, 0xa57ade28U, 0xdab78e26U, 0x3fadbfa4U,
	0x2c3a9de4U, 0x5078920dU, 0x6a5fcc9bU, 0x547e4662U,
	0xf68d13c2U, 0x90d8b8e8U, 0x2e39f75eU, 0x82c3aff5U,
	0x9f5d80beU, 0x69d0937cU, 0x6fd52da9U, 0xcf2512b3U,
	0xc8ac993bU, 0x10187da7U, 0xe89c636eU, 0xdb3bbb7bU,
	0xcd267809U, 0x6e5918f4U, 0xec9ab701U, 0x834f9aa8U,
	0xe6956e65U, 0xaaffe67eU, 0x21bccf08U, 0xef15e8e6U,
	0xbae79bd9U, 0x4a6f36ceU, 0xea9f09d4U, 0x29b07cd6U,
	0x31a4b2afU, 0x2a3f2331U, 0xc6a59430U, 0x35a266c0U,
	0x744ebc37U, 0xfc82caa6U, 0xe090d0b0U, 0x33a7d815U,
	0xf104984aU, 0x41ecdaf7U, 0x7fcd500eU, 0x1791f62fU,
	0x764dd68dU, 0x43efb04dU, 0xccaa4d54U, 0xe49604dfU,
	0x9ed1b5e3U, 0x4c6a881bU, 0xc12c1fb8U, 0x4665517fU,
	0x9d5eea04U, 0x018c355dU, 0xfa877473U, 0xfb0b412eU,
	0xb3671d5aU, 0x92dbd252U, 0xe9105633U, 0x6dd64713U,
	0x9ad7618cU, 0x37a10c7aU, 0x59f8148eU, 0xeb133c89U,
	0xcea927eeU, 0xb761c935U, 0xe11ce5edU, 0x7a47b13cU,
	0x9cd2df59U, 0x55f2733fU, 0x1814ce79U, 0x73c737bfU,
	0x53f7cdeaU, 0x5ffdaa5bU, 0xdf3d6f14U, 0x7844db86U,
	0xcaaff381U, 0xb968c43eU, 0x3824342cU, 0xc2a3405fU,
	0x161dc372U, 0xbce2250cU, 0x283c498bU, 0xff0d9541U,
	0x39a80171U, 0x080cb3deU, 0xd8b4e49cU, 0x6456c190U,
	0x7bcb8461U, 0xd532b670U, 0x486c5c74U, 0xd0b85742U,
पूर्ण;

स्थिर u8 Td4s[256] = अणु
	0x52U, 0x09U, 0x6aU, 0xd5U, 0x30U, 0x36U, 0xa5U, 0x38U,
	0xbfU, 0x40U, 0xa3U, 0x9eU, 0x81U, 0xf3U, 0xd7U, 0xfbU,
	0x7cU, 0xe3U, 0x39U, 0x82U, 0x9bU, 0x2fU, 0xffU, 0x87U,
	0x34U, 0x8eU, 0x43U, 0x44U, 0xc4U, 0xdeU, 0xe9U, 0xcbU,
	0x54U, 0x7bU, 0x94U, 0x32U, 0xa6U, 0xc2U, 0x23U, 0x3dU,
	0xeeU, 0x4cU, 0x95U, 0x0bU, 0x42U, 0xfaU, 0xc3U, 0x4eU,
	0x08U, 0x2eU, 0xa1U, 0x66U, 0x28U, 0xd9U, 0x24U, 0xb2U,
	0x76U, 0x5bU, 0xa2U, 0x49U, 0x6dU, 0x8bU, 0xd1U, 0x25U,
	0x72U, 0xf8U, 0xf6U, 0x64U, 0x86U, 0x68U, 0x98U, 0x16U,
	0xd4U, 0xa4U, 0x5cU, 0xccU, 0x5dU, 0x65U, 0xb6U, 0x92U,
	0x6cU, 0x70U, 0x48U, 0x50U, 0xfdU, 0xedU, 0xb9U, 0xdaU,
	0x5eU, 0x15U, 0x46U, 0x57U, 0xa7U, 0x8dU, 0x9dU, 0x84U,
	0x90U, 0xd8U, 0xabU, 0x00U, 0x8cU, 0xbcU, 0xd3U, 0x0aU,
	0xf7U, 0xe4U, 0x58U, 0x05U, 0xb8U, 0xb3U, 0x45U, 0x06U,
	0xd0U, 0x2cU, 0x1eU, 0x8fU, 0xcaU, 0x3fU, 0x0fU, 0x02U,
	0xc1U, 0xafU, 0xbdU, 0x03U, 0x01U, 0x13U, 0x8aU, 0x6bU,
	0x3aU, 0x91U, 0x11U, 0x41U, 0x4fU, 0x67U, 0xdcU, 0xeaU,
	0x97U, 0xf2U, 0xcfU, 0xceU, 0xf0U, 0xb4U, 0xe6U, 0x73U,
	0x96U, 0xacU, 0x74U, 0x22U, 0xe7U, 0xadU, 0x35U, 0x85U,
	0xe2U, 0xf9U, 0x37U, 0xe8U, 0x1cU, 0x75U, 0xdfU, 0x6eU,
	0x47U, 0xf1U, 0x1aU, 0x71U, 0x1dU, 0x29U, 0xc5U, 0x89U,
	0x6fU, 0xb7U, 0x62U, 0x0eU, 0xaaU, 0x18U, 0xbeU, 0x1bU,
	0xfcU, 0x56U, 0x3eU, 0x4bU, 0xc6U, 0xd2U, 0x79U, 0x20U,
	0x9aU, 0xdbU, 0xc0U, 0xfeU, 0x78U, 0xcdU, 0x5aU, 0xf4U,
	0x1fU, 0xddU, 0xa8U, 0x33U, 0x88U, 0x07U, 0xc7U, 0x31U,
	0xb1U, 0x12U, 0x10U, 0x59U, 0x27U, 0x80U, 0xecU, 0x5fU,
	0x60U, 0x51U, 0x7fU, 0xa9U, 0x19U, 0xb5U, 0x4aU, 0x0dU,
	0x2dU, 0xe5U, 0x7aU, 0x9fU, 0x93U, 0xc9U, 0x9cU, 0xefU,
	0xa0U, 0xe0U, 0x3bU, 0x4dU, 0xaeU, 0x2aU, 0xf5U, 0xb0U,
	0xc8U, 0xebU, 0xbbU, 0x3cU, 0x83U, 0x53U, 0x99U, 0x61U,
	0x17U, 0x2bU, 0x04U, 0x7eU, 0xbaU, 0x77U, 0xd6U, 0x26U,
	0xe1U, 0x69U, 0x14U, 0x63U, 0x55U, 0x21U, 0x0cU, 0x7dU,
पूर्ण;

स्थिर u8 rcons[] = अणु
	0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36
	/* क्रम 128-bit blocks, Rijndael never uses more than 10 rcon values */
पूर्ण;

/**
 * Expand the cipher key पूर्णांकo the encryption key schedule.
 *
 * @वापस	the number of rounds क्रम the given cipher key size.
 */
अटल व्योम rijndaelKeySetupEnc(u32 rk[/*44*/], स्थिर u8 cipherKey[])
अणु
	पूर्णांक i;
	u32 temp;

	rk[0] = GETU32(cipherKey);
	rk[1] = GETU32(cipherKey +  4);
	rk[2] = GETU32(cipherKey +  8);
	rk[3] = GETU32(cipherKey + 12);
	क्रम (i = 0; i < 10; i++) अणु
		temp  = rk[3];
		rk[4] = rk[0] ^
			TE421(temp) ^ TE432(temp) ^ TE443(temp) ^ TE414(temp) ^
			RCON(i);
		rk[5] = rk[1] ^ rk[4];
		rk[6] = rk[2] ^ rk[5];
		rk[7] = rk[3] ^ rk[6];
		rk += 4;
	पूर्ण
पूर्ण

अटल व्योम rijndaelEncrypt(u32 rk[/*44*/], u8 pt[16], u8 ct[16])
अणु
	u32 s0, s1, s2, s3, t0, t1, t2, t3;
	पूर्णांक Nr = 10;
	पूर्णांक r;

	/*
	 * map byte array block to cipher state
	 * and add initial round key:
	 */
	s0 = GETU32(pt) ^ rk[0];
	s1 = GETU32(pt +  4) ^ rk[1];
	s2 = GETU32(pt +  8) ^ rk[2];
	s3 = GETU32(pt + 12) ^ rk[3];

#घोषणा ROUND(i, d, s) \
	करो अणु \
		d##0 = TE0(s##0) ^ TE1(s##1) ^ TE2(s##2) ^ TE3(s##3) ^ rk[4 * i]; \
		d##1 = TE0(s##1) ^ TE1(s##2) ^ TE2(s##3) ^ TE3(s##0) ^ rk[4 * i + 1]; \
		d##2 = TE0(s##2) ^ TE1(s##3) ^ TE2(s##0) ^ TE3(s##1) ^ rk[4 * i + 2]; \
		d##3 = TE0(s##3) ^ TE1(s##0) ^ TE2(s##1) ^ TE3(s##2) ^ rk[4 * i + 3]; \
	पूर्ण जबतक (0)

	/* Nr - 1 full rounds: */
	r = Nr >> 1;
	क्रम (;;) अणु
		ROUND(1, t, s);
		rk += 8;
		अगर (--r == 0)
			अवरोध;
		ROUND(0, s, t);
	पूर्ण

#अघोषित ROUND

	/*
	 * apply last round and
	 * map cipher state to byte array block:
	 */
	s0 = TE41(t0) ^ TE42(t1) ^ TE43(t2) ^ TE44(t3) ^ rk[0];
	PUTU32(ct, s0);
	s1 = TE41(t1) ^ TE42(t2) ^ TE43(t3) ^ TE44(t0) ^ rk[1];
	PUTU32(ct +  4, s1);
	s2 = TE41(t2) ^ TE42(t3) ^ TE43(t0) ^ TE44(t1) ^ rk[2];
	PUTU32(ct +  8, s2);
	s3 = TE41(t3) ^ TE42(t0) ^ TE43(t1) ^ TE44(t2) ^ rk[3];
	PUTU32(ct + 12, s3);
पूर्ण

अटल व्योम *aes_encrypt_init(u8 *key, माप_प्रकार len)
अणु
	u32 *rk;

	अगर (len != 16)
		वापस शून्य;
	rk = rtw_दो_स्मृति(AES_PRIV_SIZE);
	अगर (rk == शून्य)
		वापस शून्य;
	rijndaelKeySetupEnc(rk, key);
	वापस rk;
पूर्ण

अटल व्योम aes_128_encrypt(व्योम *ctx, u8 *plain, u8 *crypt)
अणु
	rijndaelEncrypt(ctx, plain, crypt);
पूर्ण

अटल व्योम gf_mulx(u8 *pad)
अणु
	पूर्णांक i, carry;

	carry = pad[0] & 0x80;
	क्रम (i = 0; i < AES_BLOCK_SIZE - 1; i++)
		pad[i] = (pad[i] << 1) | (pad[i + 1] >> 7);

	pad[AES_BLOCK_SIZE - 1] <<= 1;
	अगर (carry)
		pad[AES_BLOCK_SIZE - 1] ^= 0x87;
पूर्ण

अटल व्योम aes_encrypt_deinit(व्योम *ctx)
अणु
	kमुक्त_sensitive(ctx);
पूर्ण

/**
 * omac1_aes_128_vector - One-Key CBC MAC (OMAC1) hash with AES-128
 * @key: 128-bit key क्रम the hash operation
 * @num_elem: Number of elements in the data vector
 * @addr: Poपूर्णांकers to the data areas
 * @len: Lengths of the data blocks
 * @mac: Buffer क्रम MAC (128 bits, i.e., 16 bytes)
 * Returns: 0 on success, -1 on failure
 *
 * This is a mode क्रम using block cipher (AES in this हाल) क्रम authentication.
 * OMAC1 was standardized with the name CMAC by NIST in a Special Publication
 * (SP) 800-38B.
 */
अटल पूर्णांक omac1_aes_128_vector(u8 *key, माप_प्रकार num_elem,
							 u8 *addr[], माप_प्रकार *len, u8 *mac)
अणु
	व्योम *ctx;
	u8 cbc[AES_BLOCK_SIZE], pad[AES_BLOCK_SIZE];
	u8 *pos, *end;
	माप_प्रकार i, e, left, total_len;

	ctx = aes_encrypt_init(key, 16);
	अगर (ctx == शून्य)
		वापस -1;
	स_रखो(cbc, 0, AES_BLOCK_SIZE);

	total_len = 0;
	क्रम (e = 0; e < num_elem; e++)
		total_len += len[e];
	left = total_len;

	e = 0;
	pos = addr[0];
	end = pos + len[0];

	जबतक (left >= AES_BLOCK_SIZE) अणु
		क्रम (i = 0; i < AES_BLOCK_SIZE; i++) अणु
			cbc[i] ^= *pos++;
			अगर (pos >= end) अणु
				e++;
				pos = addr[e];
				end = pos + len[e];
			पूर्ण
		पूर्ण
		अगर (left > AES_BLOCK_SIZE)
			aes_128_encrypt(ctx, cbc, cbc);
		left -= AES_BLOCK_SIZE;
	पूर्ण

	स_रखो(pad, 0, AES_BLOCK_SIZE);
	aes_128_encrypt(ctx, pad, pad);
	gf_mulx(pad);

	अगर (left || total_len == 0) अणु
		क्रम (i = 0; i < left; i++) अणु
			cbc[i] ^= *pos++;
			अगर (pos >= end) अणु
				e++;
				pos = addr[e];
				end = pos + len[e];
			पूर्ण
		पूर्ण
		cbc[left] ^= 0x80;
		gf_mulx(pad);
	पूर्ण

	क्रम (i = 0; i < AES_BLOCK_SIZE; i++)
		pad[i] ^= cbc[i];
	aes_128_encrypt(ctx, pad, mac);
	aes_encrypt_deinit(ctx);
	वापस 0;
पूर्ण

/**
 * omac1_aes_128 - One-Key CBC MAC (OMAC1) hash with AES-128 (aka AES-CMAC)
 * @key: 128-bit key क्रम the hash operation
 * @data: Data buffer क्रम which a MAC is determined
 * @data_len: Length of data buffer in bytes
 * @mac: Buffer क्रम MAC (128 bits, i.e., 16 bytes)
 * Returns: 0 on success, -1 on failure
 *
 * This is a mode क्रम using block cipher (AES in this हाल) क्रम authentication.
 * OMAC1 was standardized with the name CMAC by NIST in a Special Publication
 * (SP) 800-38B.
 * modअगरy क्रम CONFIG_IEEE80211W */
पूर्णांक omac1_aes_128(u8 *key, u8 *data, माप_प्रकार data_len, u8 *mac)
अणु
	वापस omac1_aes_128_vector(key, 1, &data, &data_len, mac);
पूर्ण

/* Restore HW wep key setting according to key_mask */
व्योम rtw_sec_restore_wep_key(काष्ठा adapter *adapter)
अणु
	काष्ठा security_priv *securitypriv = &(adapter->securitypriv);
	चिन्हित पूर्णांक keyid;

	अगर ((_WEP40_ == securitypriv->करोt11PrivacyAlgrthm) || (_WEP104_ == securitypriv->करोt11PrivacyAlgrthm)) अणु
		क्रम (keyid = 0; keyid < 4; keyid++) अणु
			अगर (securitypriv->key_mask & BIT(keyid)) अणु
				अगर (keyid == securitypriv->करोt11PrivacyKeyIndex)
					rtw_set_key(adapter, securitypriv, keyid, 1, false);
				अन्यथा
					rtw_set_key(adapter, securitypriv, keyid, 0, false);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

u8 rtw_handle_tkip_countermeasure(काष्ठा adapter *adapter, स्थिर अक्षर *caller)
अणु
	काष्ठा security_priv *securitypriv = &(adapter->securitypriv);
	u8 status = _SUCCESS;

	अगर (securitypriv->btkip_countermeasure) अणु
		अचिन्हित दीर्घ passing_ms = jअगरfies_to_msecs(jअगरfies - securitypriv->btkip_countermeasure_समय);

		अगर (passing_ms > 60*1000) अणु
			netdev_dbg(adapter->pnetdev,
				   "%s(%s) countermeasure time:%lus > 60s\n",
				   caller, ADPT_ARG(adapter),
				   passing_ms / 1000);
			securitypriv->btkip_countermeasure = false;
			securitypriv->btkip_countermeasure_समय = 0;
		पूर्ण अन्यथा अणु
			netdev_dbg(adapter->pnetdev,
				   "%s(%s) countermeasure time:%lus < 60s\n",
				   caller, ADPT_ARG(adapter),
				   passing_ms / 1000);
			status = _FAIL;
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण
