<शैली गुरु>
/*
   BlueZ - Bluetooth protocol stack क्रम Linux
   Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).

   This program is मुक्त software; you can redistribute it and/or modअगरy
   it under the terms of the GNU General Public License version 2 as
   published by the Free Software Foundation;

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY
   CLAIM, OR ANY SPECIAL INसूचीECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES
   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS,
   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS
   SOFTWARE IS DISCLAIMED.
*/

#समावेश <linux/debugfs.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/crypto.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/kpp.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>
#समावेश <net/bluetooth/l2cap.h>
#समावेश <net/bluetooth/mgmt.h>

#समावेश "ecdh_helper.h"
#समावेश "smp.h"

#घोषणा SMP_DEV(hdev) \
	((काष्ठा smp_dev *)((काष्ठा l2cap_chan *)((hdev)->smp_data))->data)

/* Low-level debug macros to be used क्रम stuff that we करोn't want
 * accidentially in dmesg, i.e. the values of the various crypto keys
 * and the inमाला_दो & outमाला_दो of crypto functions.
 */
#अगर_घोषित DEBUG
#घोषणा SMP_DBG(fmt, ...) prपूर्णांकk(KERN_DEBUG "%s: " fmt, __func__, \
				 ##__VA_ARGS__)
#अन्यथा
#घोषणा SMP_DBG(fmt, ...) no_prपूर्णांकk(KERN_DEBUG "%s: " fmt, __func__, \
				    ##__VA_ARGS__)
#पूर्ण_अगर

#घोषणा SMP_ALLOW_CMD(smp, code)	set_bit(code, &smp->allow_cmd)

/* Keys which are not distributed with Secure Connections */
#घोषणा SMP_SC_NO_DIST (SMP_DIST_ENC_KEY | SMP_DIST_LINK_KEY)

#घोषणा SMP_TIMEOUT	msecs_to_jअगरfies(30000)

#घोषणा AUTH_REQ_MASK(dev)	(hci_dev_test_flag(dev, HCI_SC_ENABLED) ? \
				 0x3f : 0x07)
#घोषणा KEY_DIST_MASK		0x07

/* Maximum message length that can be passed to aes_cmac */
#घोषणा CMAC_MSG_MAX	80

क्रमागत अणु
	SMP_FLAG_TK_VALID,
	SMP_FLAG_CFM_PENDING,
	SMP_FLAG_MITM_AUTH,
	SMP_FLAG_COMPLETE,
	SMP_FLAG_INITIATOR,
	SMP_FLAG_SC,
	SMP_FLAG_REMOTE_PK,
	SMP_FLAG_DEBUG_KEY,
	SMP_FLAG_WAIT_USER,
	SMP_FLAG_DHKEY_PENDING,
	SMP_FLAG_REMOTE_OOB,
	SMP_FLAG_LOCAL_OOB,
	SMP_FLAG_CT2,
पूर्ण;

काष्ठा smp_dev अणु
	/* Secure Connections OOB data */
	bool			local_oob;
	u8			local_pk[64];
	u8			local_अक्रम[16];
	bool			debug_key;

	काष्ठा crypto_shash	*tfm_cmac;
	काष्ठा crypto_kpp	*tfm_ecdh;
पूर्ण;

काष्ठा smp_chan अणु
	काष्ठा l2cap_conn	*conn;
	काष्ठा delayed_work	security_समयr;
	अचिन्हित दीर्घ           allow_cmd; /* Biपंचांगask of allowed commands */

	u8		preq[7]; /* SMP Pairing Request */
	u8		prsp[7]; /* SMP Pairing Response */
	u8		prnd[16]; /* SMP Pairing Ranकरोm (local) */
	u8		rrnd[16]; /* SMP Pairing Ranकरोm (remote) */
	u8		pcnf[16]; /* SMP Pairing Confirm */
	u8		tk[16]; /* SMP Temporary Key */
	u8		rr[16]; /* Remote OOB ra/rb value */
	u8		lr[16]; /* Local OOB ra/rb value */
	u8		enc_key_size;
	u8		remote_key_dist;
	bdaddr_t	id_addr;
	u8		id_addr_type;
	u8		irk[16];
	काष्ठा smp_csrk	*csrk;
	काष्ठा smp_csrk	*slave_csrk;
	काष्ठा smp_ltk	*ltk;
	काष्ठा smp_ltk	*slave_ltk;
	काष्ठा smp_irk	*remote_irk;
	u8		*link_key;
	अचिन्हित दीर्घ	flags;
	u8		method;
	u8		passkey_round;

	/* Secure Connections variables */
	u8			local_pk[64];
	u8			remote_pk[64];
	u8			dhkey[32];
	u8			mackey[16];

	काष्ठा crypto_shash	*tfm_cmac;
	काष्ठा crypto_kpp	*tfm_ecdh;
पूर्ण;

/* These debug key values are defined in the SMP section of the core
 * specअगरication. debug_pk is the खुला debug key and debug_sk the
 * निजी debug key.
 */
अटल स्थिर u8 debug_pk[64] = अणु
		0xe6, 0x9d, 0x35, 0x0e, 0x48, 0x01, 0x03, 0xcc,
		0xdb, 0xfd, 0xf4, 0xac, 0x11, 0x91, 0xf4, 0xef,
		0xb9, 0xa5, 0xf9, 0xe9, 0xa7, 0x83, 0x2c, 0x5e,
		0x2c, 0xbe, 0x97, 0xf2, 0xd2, 0x03, 0xb0, 0x20,

		0x8b, 0xd2, 0x89, 0x15, 0xd0, 0x8e, 0x1c, 0x74,
		0x24, 0x30, 0xed, 0x8f, 0xc2, 0x45, 0x63, 0x76,
		0x5c, 0x15, 0x52, 0x5a, 0xbf, 0x9a, 0x32, 0x63,
		0x6d, 0xeb, 0x2a, 0x65, 0x49, 0x9c, 0x80, 0xdc,
पूर्ण;

अटल स्थिर u8 debug_sk[32] = अणु
		0xbd, 0x1a, 0x3c, 0xcd, 0xa6, 0xb8, 0x99, 0x58,
		0x99, 0xb7, 0x40, 0xeb, 0x7b, 0x60, 0xff, 0x4a,
		0x50, 0x3f, 0x10, 0xd2, 0xe3, 0xb3, 0xc9, 0x74,
		0x38, 0x5f, 0xc5, 0xa3, 0xd4, 0xf6, 0x49, 0x3f,
पूर्ण;

अटल अंतरभूत व्योम swap_buf(स्थिर u8 *src, u8 *dst, माप_प्रकार len)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < len; i++)
		dst[len - 1 - i] = src[i];
पूर्ण

/* The following functions map to the LE SC SMP crypto functions
 * AES-CMAC, f4, f5, f6, g2 and h6.
 */

अटल पूर्णांक aes_cmac(काष्ठा crypto_shash *tfm, स्थिर u8 k[16], स्थिर u8 *m,
		    माप_प्रकार len, u8 mac[16])
अणु
	uपूर्णांक8_t पंचांगp[16], mac_msb[16], msg_msb[CMAC_MSG_MAX];
	पूर्णांक err;

	अगर (len > CMAC_MSG_MAX)
		वापस -EFBIG;

	अगर (!tfm) अणु
		BT_ERR("tfm %p", tfm);
		वापस -EINVAL;
	पूर्ण

	/* Swap key and message from LSB to MSB */
	swap_buf(k, पंचांगp, 16);
	swap_buf(m, msg_msb, len);

	SMP_DBG("msg (len %zu) %*phN", len, (पूर्णांक) len, m);
	SMP_DBG("key %16phN", k);

	err = crypto_shash_setkey(tfm, पंचांगp, 16);
	अगर (err) अणु
		BT_ERR("cipher setkey failed: %d", err);
		वापस err;
	पूर्ण

	err = crypto_shash_tfm_digest(tfm, msg_msb, len, mac_msb);
	अगर (err) अणु
		BT_ERR("Hash computation error %d", err);
		वापस err;
	पूर्ण

	swap_buf(mac_msb, mac, 16);

	SMP_DBG("mac %16phN", mac);

	वापस 0;
पूर्ण

अटल पूर्णांक smp_f4(काष्ठा crypto_shash *tfm_cmac, स्थिर u8 u[32],
		  स्थिर u8 v[32], स्थिर u8 x[16], u8 z, u8 res[16])
अणु
	u8 m[65];
	पूर्णांक err;

	SMP_DBG("u %32phN", u);
	SMP_DBG("v %32phN", v);
	SMP_DBG("x %16phN z %02x", x, z);

	m[0] = z;
	स_नकल(m + 1, v, 32);
	स_नकल(m + 33, u, 32);

	err = aes_cmac(tfm_cmac, x, m, माप(m), res);
	अगर (err)
		वापस err;

	SMP_DBG("res %16phN", res);

	वापस err;
पूर्ण

अटल पूर्णांक smp_f5(काष्ठा crypto_shash *tfm_cmac, स्थिर u8 w[32],
		  स्थिर u8 n1[16], स्थिर u8 n2[16], स्थिर u8 a1[7],
		  स्थिर u8 a2[7], u8 mackey[16], u8 ltk[16])
अणु
	/* The btle, salt and length "magic" values are as defined in
	 * the SMP section of the Bluetooth core specअगरication. In ASCII
	 * the btle value ends up being 'btle'. The salt is just a
	 * अक्रमom number whereas length is the value 256 in little
	 * endian क्रमmat.
	 */
	स्थिर u8 btle[4] = अणु 0x65, 0x6c, 0x74, 0x62 पूर्ण;
	स्थिर u8 salt[16] = अणु 0xbe, 0x83, 0x60, 0x5a, 0xdb, 0x0b, 0x37, 0x60,
			      0x38, 0xa5, 0xf5, 0xaa, 0x91, 0x83, 0x88, 0x6c पूर्ण;
	स्थिर u8 length[2] = अणु 0x00, 0x01 पूर्ण;
	u8 m[53], t[16];
	पूर्णांक err;

	SMP_DBG("w %32phN", w);
	SMP_DBG("n1 %16phN n2 %16phN", n1, n2);
	SMP_DBG("a1 %7phN a2 %7phN", a1, a2);

	err = aes_cmac(tfm_cmac, salt, w, 32, t);
	अगर (err)
		वापस err;

	SMP_DBG("t %16phN", t);

	स_नकल(m, length, 2);
	स_नकल(m + 2, a2, 7);
	स_नकल(m + 9, a1, 7);
	स_नकल(m + 16, n2, 16);
	स_नकल(m + 32, n1, 16);
	स_नकल(m + 48, btle, 4);

	m[52] = 0; /* Counter */

	err = aes_cmac(tfm_cmac, t, m, माप(m), mackey);
	अगर (err)
		वापस err;

	SMP_DBG("mackey %16phN", mackey);

	m[52] = 1; /* Counter */

	err = aes_cmac(tfm_cmac, t, m, माप(m), ltk);
	अगर (err)
		वापस err;

	SMP_DBG("ltk %16phN", ltk);

	वापस 0;
पूर्ण

अटल पूर्णांक smp_f6(काष्ठा crypto_shash *tfm_cmac, स्थिर u8 w[16],
		  स्थिर u8 n1[16], स्थिर u8 n2[16], स्थिर u8 r[16],
		  स्थिर u8 io_cap[3], स्थिर u8 a1[7], स्थिर u8 a2[7],
		  u8 res[16])
अणु
	u8 m[65];
	पूर्णांक err;

	SMP_DBG("w %16phN", w);
	SMP_DBG("n1 %16phN n2 %16phN", n1, n2);
	SMP_DBG("r %16phN io_cap %3phN a1 %7phN a2 %7phN", r, io_cap, a1, a2);

	स_नकल(m, a2, 7);
	स_नकल(m + 7, a1, 7);
	स_नकल(m + 14, io_cap, 3);
	स_नकल(m + 17, r, 16);
	स_नकल(m + 33, n2, 16);
	स_नकल(m + 49, n1, 16);

	err = aes_cmac(tfm_cmac, w, m, माप(m), res);
	अगर (err)
		वापस err;

	SMP_DBG("res %16phN", res);

	वापस err;
पूर्ण

अटल पूर्णांक smp_g2(काष्ठा crypto_shash *tfm_cmac, स्थिर u8 u[32], स्थिर u8 v[32],
		  स्थिर u8 x[16], स्थिर u8 y[16], u32 *val)
अणु
	u8 m[80], पंचांगp[16];
	पूर्णांक err;

	SMP_DBG("u %32phN", u);
	SMP_DBG("v %32phN", v);
	SMP_DBG("x %16phN y %16phN", x, y);

	स_नकल(m, y, 16);
	स_नकल(m + 16, v, 32);
	स_नकल(m + 48, u, 32);

	err = aes_cmac(tfm_cmac, x, m, माप(m), पंचांगp);
	अगर (err)
		वापस err;

	*val = get_unaligned_le32(पंचांगp);
	*val %= 1000000;

	SMP_DBG("val %06u", *val);

	वापस 0;
पूर्ण

अटल पूर्णांक smp_h6(काष्ठा crypto_shash *tfm_cmac, स्थिर u8 w[16],
		  स्थिर u8 key_id[4], u8 res[16])
अणु
	पूर्णांक err;

	SMP_DBG("w %16phN key_id %4phN", w, key_id);

	err = aes_cmac(tfm_cmac, w, key_id, 4, res);
	अगर (err)
		वापस err;

	SMP_DBG("res %16phN", res);

	वापस err;
पूर्ण

अटल पूर्णांक smp_h7(काष्ठा crypto_shash *tfm_cmac, स्थिर u8 w[16],
		  स्थिर u8 salt[16], u8 res[16])
अणु
	पूर्णांक err;

	SMP_DBG("w %16phN salt %16phN", w, salt);

	err = aes_cmac(tfm_cmac, salt, w, 16, res);
	अगर (err)
		वापस err;

	SMP_DBG("res %16phN", res);

	वापस err;
पूर्ण

/* The following functions map to the legacy SMP crypto functions e, c1,
 * s1 and ah.
 */

अटल पूर्णांक smp_e(स्थिर u8 *k, u8 *r)
अणु
	काष्ठा crypto_aes_ctx ctx;
	uपूर्णांक8_t पंचांगp[16], data[16];
	पूर्णांक err;

	SMP_DBG("k %16phN r %16phN", k, r);

	/* The most signअगरicant octet of key corresponds to k[0] */
	swap_buf(k, पंचांगp, 16);

	err = aes_expandkey(&ctx, पंचांगp, 16);
	अगर (err) अणु
		BT_ERR("cipher setkey failed: %d", err);
		वापस err;
	पूर्ण

	/* Most signअगरicant octet of plaपूर्णांकextData corresponds to data[0] */
	swap_buf(r, data, 16);

	aes_encrypt(&ctx, data, data);

	/* Most signअगरicant octet of encryptedData corresponds to data[0] */
	swap_buf(data, r, 16);

	SMP_DBG("r %16phN", r);

	memzero_explicit(&ctx, माप(ctx));
	वापस err;
पूर्ण

अटल पूर्णांक smp_c1(स्थिर u8 k[16],
		  स्थिर u8 r[16], स्थिर u8 preq[7], स्थिर u8 pres[7], u8 _iat,
		  स्थिर bdaddr_t *ia, u8 _rat, स्थिर bdaddr_t *ra, u8 res[16])
अणु
	u8 p1[16], p2[16];
	पूर्णांक err;

	SMP_DBG("k %16phN r %16phN", k, r);
	SMP_DBG("iat %u ia %6phN rat %u ra %6phN", _iat, ia, _rat, ra);
	SMP_DBG("preq %7phN pres %7phN", preq, pres);

	स_रखो(p1, 0, 16);

	/* p1 = pres || preq || _rat || _iat */
	p1[0] = _iat;
	p1[1] = _rat;
	स_नकल(p1 + 2, preq, 7);
	स_नकल(p1 + 9, pres, 7);

	SMP_DBG("p1 %16phN", p1);

	/* res = r XOR p1 */
	crypto_xor_cpy(res, r, p1, माप(p1));

	/* res = e(k, res) */
	err = smp_e(k, res);
	अगर (err) अणु
		BT_ERR("Encrypt data error");
		वापस err;
	पूर्ण

	/* p2 = padding || ia || ra */
	स_नकल(p2, ra, 6);
	स_नकल(p2 + 6, ia, 6);
	स_रखो(p2 + 12, 0, 4);

	SMP_DBG("p2 %16phN", p2);

	/* res = res XOR p2 */
	crypto_xor(res, p2, माप(p2));

	/* res = e(k, res) */
	err = smp_e(k, res);
	अगर (err)
		BT_ERR("Encrypt data error");

	वापस err;
पूर्ण

अटल पूर्णांक smp_s1(स्थिर u8 k[16],
		  स्थिर u8 r1[16], स्थिर u8 r2[16], u8 _r[16])
अणु
	पूर्णांक err;

	/* Just least signअगरicant octets from r1 and r2 are considered */
	स_नकल(_r, r2, 8);
	स_नकल(_r + 8, r1, 8);

	err = smp_e(k, _r);
	अगर (err)
		BT_ERR("Encrypt data error");

	वापस err;
पूर्ण

अटल पूर्णांक smp_ah(स्थिर u8 irk[16], स्थिर u8 r[3], u8 res[3])
अणु
	u8 _res[16];
	पूर्णांक err;

	/* r' = padding || r */
	स_नकल(_res, r, 3);
	स_रखो(_res + 3, 0, 13);

	err = smp_e(irk, _res);
	अगर (err) अणु
		BT_ERR("Encrypt error");
		वापस err;
	पूर्ण

	/* The output of the अक्रमom address function ah is:
	 *	ah(k, r) = e(k, r') mod 2^24
	 * The output of the security function e is then truncated to 24 bits
	 * by taking the least signअगरicant 24 bits of the output of e as the
	 * result of ah.
	 */
	स_नकल(res, _res, 3);

	वापस 0;
पूर्ण

bool smp_irk_matches(काष्ठा hci_dev *hdev, स्थिर u8 irk[16],
		     स्थिर bdaddr_t *bdaddr)
अणु
	काष्ठा l2cap_chan *chan = hdev->smp_data;
	u8 hash[3];
	पूर्णांक err;

	अगर (!chan || !chan->data)
		वापस false;

	bt_dev_dbg(hdev, "RPA %pMR IRK %*phN", bdaddr, 16, irk);

	err = smp_ah(irk, &bdaddr->b[3], hash);
	अगर (err)
		वापस false;

	वापस !crypto_memneq(bdaddr->b, hash, 3);
पूर्ण

पूर्णांक smp_generate_rpa(काष्ठा hci_dev *hdev, स्थिर u8 irk[16], bdaddr_t *rpa)
अणु
	काष्ठा l2cap_chan *chan = hdev->smp_data;
	पूर्णांक err;

	अगर (!chan || !chan->data)
		वापस -EOPNOTSUPP;

	get_अक्रमom_bytes(&rpa->b[3], 3);

	rpa->b[5] &= 0x3f;	/* Clear two most signअगरicant bits */
	rpa->b[5] |= 0x40;	/* Set second most signअगरicant bit */

	err = smp_ah(irk, &rpa->b[3], rpa->b);
	अगर (err < 0)
		वापस err;

	bt_dev_dbg(hdev, "RPA %pMR", rpa);

	वापस 0;
पूर्ण

पूर्णांक smp_generate_oob(काष्ठा hci_dev *hdev, u8 hash[16], u8 अक्रम[16])
अणु
	काष्ठा l2cap_chan *chan = hdev->smp_data;
	काष्ठा smp_dev *smp;
	पूर्णांक err;

	अगर (!chan || !chan->data)
		वापस -EOPNOTSUPP;

	smp = chan->data;

	अगर (hci_dev_test_flag(hdev, HCI_USE_DEBUG_KEYS)) अणु
		bt_dev_dbg(hdev, "Using debug keys");
		err = set_ecdh_privkey(smp->tfm_ecdh, debug_sk);
		अगर (err)
			वापस err;
		स_नकल(smp->local_pk, debug_pk, 64);
		smp->debug_key = true;
	पूर्ण अन्यथा अणु
		जबतक (true) अणु
			/* Generate key pair क्रम Secure Connections */
			err = generate_ecdh_keys(smp->tfm_ecdh, smp->local_pk);
			अगर (err)
				वापस err;

			/* This is unlikely, but we need to check that
			 * we didn't accidentially generate a debug key.
			 */
			अगर (crypto_memneq(smp->local_pk, debug_pk, 64))
				अवरोध;
		पूर्ण
		smp->debug_key = false;
	पूर्ण

	SMP_DBG("OOB Public Key X: %32phN", smp->local_pk);
	SMP_DBG("OOB Public Key Y: %32phN", smp->local_pk + 32);

	get_अक्रमom_bytes(smp->local_अक्रम, 16);

	err = smp_f4(smp->tfm_cmac, smp->local_pk, smp->local_pk,
		     smp->local_अक्रम, 0, hash);
	अगर (err < 0)
		वापस err;

	स_नकल(अक्रम, smp->local_अक्रम, 16);

	smp->local_oob = true;

	वापस 0;
पूर्ण

अटल व्योम smp_send_cmd(काष्ठा l2cap_conn *conn, u8 code, u16 len, व्योम *data)
अणु
	काष्ठा l2cap_chan *chan = conn->smp;
	काष्ठा smp_chan *smp;
	काष्ठा kvec iv[2];
	काष्ठा msghdr msg;

	अगर (!chan)
		वापस;

	bt_dev_dbg(conn->hcon->hdev, "code 0x%2.2x", code);

	iv[0].iov_base = &code;
	iv[0].iov_len = 1;

	iv[1].iov_base = data;
	iv[1].iov_len = len;

	स_रखो(&msg, 0, माप(msg));

	iov_iter_kvec(&msg.msg_iter, WRITE, iv, 2, 1 + len);

	l2cap_chan_send(chan, &msg, 1 + len);

	अगर (!chan->data)
		वापस;

	smp = chan->data;

	cancel_delayed_work_sync(&smp->security_समयr);
	schedule_delayed_work(&smp->security_समयr, SMP_TIMEOUT);
पूर्ण

अटल u8 authreq_to_seclevel(u8 authreq)
अणु
	अगर (authreq & SMP_AUTH_MITM) अणु
		अगर (authreq & SMP_AUTH_SC)
			वापस BT_SECURITY_FIPS;
		अन्यथा
			वापस BT_SECURITY_HIGH;
	पूर्ण अन्यथा अणु
		वापस BT_SECURITY_MEDIUM;
	पूर्ण
पूर्ण

अटल __u8 seclevel_to_authreq(__u8 sec_level)
अणु
	चयन (sec_level) अणु
	हाल BT_SECURITY_FIPS:
	हाल BT_SECURITY_HIGH:
		वापस SMP_AUTH_MITM | SMP_AUTH_BONDING;
	हाल BT_SECURITY_MEDIUM:
		वापस SMP_AUTH_BONDING;
	शेष:
		वापस SMP_AUTH_NONE;
	पूर्ण
पूर्ण

अटल व्योम build_pairing_cmd(काष्ठा l2cap_conn *conn,
			      काष्ठा smp_cmd_pairing *req,
			      काष्ठा smp_cmd_pairing *rsp, __u8 authreq)
अणु
	काष्ठा l2cap_chan *chan = conn->smp;
	काष्ठा smp_chan *smp = chan->data;
	काष्ठा hci_conn *hcon = conn->hcon;
	काष्ठा hci_dev *hdev = hcon->hdev;
	u8 local_dist = 0, remote_dist = 0, oob_flag = SMP_OOB_NOT_PRESENT;

	अगर (hci_dev_test_flag(hdev, HCI_BONDABLE)) अणु
		local_dist = SMP_DIST_ENC_KEY | SMP_DIST_SIGN;
		remote_dist = SMP_DIST_ENC_KEY | SMP_DIST_SIGN;
		authreq |= SMP_AUTH_BONDING;
	पूर्ण अन्यथा अणु
		authreq &= ~SMP_AUTH_BONDING;
	पूर्ण

	अगर (hci_dev_test_flag(hdev, HCI_RPA_RESOLVING))
		remote_dist |= SMP_DIST_ID_KEY;

	अगर (hci_dev_test_flag(hdev, HCI_PRIVACY))
		local_dist |= SMP_DIST_ID_KEY;

	अगर (hci_dev_test_flag(hdev, HCI_SC_ENABLED) &&
	    (authreq & SMP_AUTH_SC)) अणु
		काष्ठा oob_data *oob_data;
		u8 bdaddr_type;

		अगर (hci_dev_test_flag(hdev, HCI_SSP_ENABLED)) अणु
			local_dist |= SMP_DIST_LINK_KEY;
			remote_dist |= SMP_DIST_LINK_KEY;
		पूर्ण

		अगर (hcon->dst_type == ADDR_LE_DEV_PUBLIC)
			bdaddr_type = BDADDR_LE_PUBLIC;
		अन्यथा
			bdaddr_type = BDADDR_LE_RANDOM;

		oob_data = hci_find_remote_oob_data(hdev, &hcon->dst,
						    bdaddr_type);
		अगर (oob_data && oob_data->present) अणु
			set_bit(SMP_FLAG_REMOTE_OOB, &smp->flags);
			oob_flag = SMP_OOB_PRESENT;
			स_नकल(smp->rr, oob_data->अक्रम256, 16);
			स_नकल(smp->pcnf, oob_data->hash256, 16);
			SMP_DBG("OOB Remote Confirmation: %16phN", smp->pcnf);
			SMP_DBG("OOB Remote Random: %16phN", smp->rr);
		पूर्ण

	पूर्ण अन्यथा अणु
		authreq &= ~SMP_AUTH_SC;
	पूर्ण

	अगर (rsp == शून्य) अणु
		req->io_capability = conn->hcon->io_capability;
		req->oob_flag = oob_flag;
		req->max_key_size = hdev->le_max_key_size;
		req->init_key_dist = local_dist;
		req->resp_key_dist = remote_dist;
		req->auth_req = (authreq & AUTH_REQ_MASK(hdev));

		smp->remote_key_dist = remote_dist;
		वापस;
	पूर्ण

	rsp->io_capability = conn->hcon->io_capability;
	rsp->oob_flag = oob_flag;
	rsp->max_key_size = hdev->le_max_key_size;
	rsp->init_key_dist = req->init_key_dist & remote_dist;
	rsp->resp_key_dist = req->resp_key_dist & local_dist;
	rsp->auth_req = (authreq & AUTH_REQ_MASK(hdev));

	smp->remote_key_dist = rsp->init_key_dist;
पूर्ण

अटल u8 check_enc_key_size(काष्ठा l2cap_conn *conn, __u8 max_key_size)
अणु
	काष्ठा l2cap_chan *chan = conn->smp;
	काष्ठा hci_dev *hdev = conn->hcon->hdev;
	काष्ठा smp_chan *smp = chan->data;

	अगर (conn->hcon->pending_sec_level == BT_SECURITY_FIPS &&
	    max_key_size != SMP_MAX_ENC_KEY_SIZE)
		वापस SMP_ENC_KEY_SIZE;

	अगर (max_key_size > hdev->le_max_key_size ||
	    max_key_size < SMP_MIN_ENC_KEY_SIZE)
		वापस SMP_ENC_KEY_SIZE;

	smp->enc_key_size = max_key_size;

	वापस 0;
पूर्ण

अटल व्योम smp_chan_destroy(काष्ठा l2cap_conn *conn)
अणु
	काष्ठा l2cap_chan *chan = conn->smp;
	काष्ठा smp_chan *smp = chan->data;
	काष्ठा hci_conn *hcon = conn->hcon;
	bool complete;

	BUG_ON(!smp);

	cancel_delayed_work_sync(&smp->security_समयr);

	complete = test_bit(SMP_FLAG_COMPLETE, &smp->flags);
	mgmt_smp_complete(hcon, complete);

	kमुक्त_sensitive(smp->csrk);
	kमुक्त_sensitive(smp->slave_csrk);
	kमुक्त_sensitive(smp->link_key);

	crypto_मुक्त_shash(smp->tfm_cmac);
	crypto_मुक्त_kpp(smp->tfm_ecdh);

	/* Ensure that we करोn't leave any debug key around अगर debug key
	 * support hasn't been explicitly enabled.
	 */
	अगर (smp->ltk && smp->ltk->type == SMP_LTK_P256_DEBUG &&
	    !hci_dev_test_flag(hcon->hdev, HCI_KEEP_DEBUG_KEYS)) अणु
		list_del_rcu(&smp->ltk->list);
		kमुक्त_rcu(smp->ltk, rcu);
		smp->ltk = शून्य;
	पूर्ण

	/* If pairing failed clean up any keys we might have */
	अगर (!complete) अणु
		अगर (smp->ltk) अणु
			list_del_rcu(&smp->ltk->list);
			kमुक्त_rcu(smp->ltk, rcu);
		पूर्ण

		अगर (smp->slave_ltk) अणु
			list_del_rcu(&smp->slave_ltk->list);
			kमुक्त_rcu(smp->slave_ltk, rcu);
		पूर्ण

		अगर (smp->remote_irk) अणु
			list_del_rcu(&smp->remote_irk->list);
			kमुक्त_rcu(smp->remote_irk, rcu);
		पूर्ण
	पूर्ण

	chan->data = शून्य;
	kमुक्त_sensitive(smp);
	hci_conn_drop(hcon);
पूर्ण

अटल व्योम smp_failure(काष्ठा l2cap_conn *conn, u8 reason)
अणु
	काष्ठा hci_conn *hcon = conn->hcon;
	काष्ठा l2cap_chan *chan = conn->smp;

	अगर (reason)
		smp_send_cmd(conn, SMP_CMD_PAIRING_FAIL, माप(reason),
			     &reason);

	mgmt_auth_failed(hcon, HCI_ERROR_AUTH_FAILURE);

	अगर (chan->data)
		smp_chan_destroy(conn);
पूर्ण

#घोषणा JUST_WORKS	0x00
#घोषणा JUST_CFM	0x01
#घोषणा REQ_PASSKEY	0x02
#घोषणा CFM_PASSKEY	0x03
#घोषणा REQ_OOB		0x04
#घोषणा DSP_PASSKEY	0x05
#घोषणा OVERLAP		0xFF

अटल स्थिर u8 gen_method[5][5] = अणु
	अणु JUST_WORKS,  JUST_CFM,    REQ_PASSKEY, JUST_WORKS, REQ_PASSKEY पूर्ण,
	अणु JUST_WORKS,  JUST_CFM,    REQ_PASSKEY, JUST_WORKS, REQ_PASSKEY पूर्ण,
	अणु CFM_PASSKEY, CFM_PASSKEY, REQ_PASSKEY, JUST_WORKS, CFM_PASSKEY पूर्ण,
	अणु JUST_WORKS,  JUST_CFM,    JUST_WORKS,  JUST_WORKS, JUST_CFM    पूर्ण,
	अणु CFM_PASSKEY, CFM_PASSKEY, REQ_PASSKEY, JUST_WORKS, OVERLAP     पूर्ण,
पूर्ण;

अटल स्थिर u8 sc_method[5][5] = अणु
	अणु JUST_WORKS,  JUST_CFM,    REQ_PASSKEY, JUST_WORKS, REQ_PASSKEY पूर्ण,
	अणु JUST_WORKS,  CFM_PASSKEY, REQ_PASSKEY, JUST_WORKS, CFM_PASSKEY पूर्ण,
	अणु DSP_PASSKEY, DSP_PASSKEY, REQ_PASSKEY, JUST_WORKS, DSP_PASSKEY पूर्ण,
	अणु JUST_WORKS,  JUST_CFM,    JUST_WORKS,  JUST_WORKS, JUST_CFM    पूर्ण,
	अणु DSP_PASSKEY, CFM_PASSKEY, REQ_PASSKEY, JUST_WORKS, CFM_PASSKEY पूर्ण,
पूर्ण;

अटल u8 get_auth_method(काष्ठा smp_chan *smp, u8 local_io, u8 remote_io)
अणु
	/* If either side has unknown io_caps, use JUST_CFM (which माला_लो
	 * converted later to JUST_WORKS अगर we're initiators.
	 */
	अगर (local_io > SMP_IO_KEYBOARD_DISPLAY ||
	    remote_io > SMP_IO_KEYBOARD_DISPLAY)
		वापस JUST_CFM;

	अगर (test_bit(SMP_FLAG_SC, &smp->flags))
		वापस sc_method[remote_io][local_io];

	वापस gen_method[remote_io][local_io];
पूर्ण

अटल पूर्णांक tk_request(काष्ठा l2cap_conn *conn, u8 remote_oob, u8 auth,
						u8 local_io, u8 remote_io)
अणु
	काष्ठा hci_conn *hcon = conn->hcon;
	काष्ठा l2cap_chan *chan = conn->smp;
	काष्ठा smp_chan *smp = chan->data;
	u32 passkey = 0;
	पूर्णांक ret;

	/* Initialize key क्रम JUST WORKS */
	स_रखो(smp->tk, 0, माप(smp->tk));
	clear_bit(SMP_FLAG_TK_VALID, &smp->flags);

	bt_dev_dbg(hcon->hdev, "auth:%d lcl:%d rem:%d", auth, local_io,
		   remote_io);

	/* If neither side wants MITM, either "just" confirm an incoming
	 * request or use just-works क्रम outgoing ones. The JUST_CFM
	 * will be converted to JUST_WORKS अगर necessary later in this
	 * function. If either side has MITM look up the method from the
	 * table.
	 */
	अगर (!(auth & SMP_AUTH_MITM))
		smp->method = JUST_CFM;
	अन्यथा
		smp->method = get_auth_method(smp, local_io, remote_io);

	/* Don't confirm locally initiated pairing attempts */
	अगर (smp->method == JUST_CFM && test_bit(SMP_FLAG_INITIATOR,
						&smp->flags))
		smp->method = JUST_WORKS;

	/* Don't bother user space with no IO capabilities */
	अगर (smp->method == JUST_CFM &&
	    hcon->io_capability == HCI_IO_NO_INPUT_OUTPUT)
		smp->method = JUST_WORKS;

	/* If Just Works, Continue with Zero TK and ask user-space क्रम
	 * confirmation */
	अगर (smp->method == JUST_WORKS) अणु
		ret = mgmt_user_confirm_request(hcon->hdev, &hcon->dst,
						hcon->type,
						hcon->dst_type,
						passkey, 1);
		अगर (ret)
			वापस ret;
		set_bit(SMP_FLAG_WAIT_USER, &smp->flags);
		वापस 0;
	पूर्ण

	/* If this function is used क्रम SC -> legacy fallback we
	 * can only recover the just-works हाल.
	 */
	अगर (test_bit(SMP_FLAG_SC, &smp->flags))
		वापस -EINVAL;

	/* Not Just Works/Confirm results in MITM Authentication */
	अगर (smp->method != JUST_CFM) अणु
		set_bit(SMP_FLAG_MITM_AUTH, &smp->flags);
		अगर (hcon->pending_sec_level < BT_SECURITY_HIGH)
			hcon->pending_sec_level = BT_SECURITY_HIGH;
	पूर्ण

	/* If both devices have Keyoard-Display I/O, the master
	 * Confirms and the slave Enters the passkey.
	 */
	अगर (smp->method == OVERLAP) अणु
		अगर (hcon->role == HCI_ROLE_MASTER)
			smp->method = CFM_PASSKEY;
		अन्यथा
			smp->method = REQ_PASSKEY;
	पूर्ण

	/* Generate अक्रमom passkey. */
	अगर (smp->method == CFM_PASSKEY) अणु
		स_रखो(smp->tk, 0, माप(smp->tk));
		get_अक्रमom_bytes(&passkey, माप(passkey));
		passkey %= 1000000;
		put_unaligned_le32(passkey, smp->tk);
		bt_dev_dbg(hcon->hdev, "PassKey: %d", passkey);
		set_bit(SMP_FLAG_TK_VALID, &smp->flags);
	पूर्ण

	अगर (smp->method == REQ_PASSKEY)
		ret = mgmt_user_passkey_request(hcon->hdev, &hcon->dst,
						hcon->type, hcon->dst_type);
	अन्यथा अगर (smp->method == JUST_CFM)
		ret = mgmt_user_confirm_request(hcon->hdev, &hcon->dst,
						hcon->type, hcon->dst_type,
						passkey, 1);
	अन्यथा
		ret = mgmt_user_passkey_notअगरy(hcon->hdev, &hcon->dst,
						hcon->type, hcon->dst_type,
						passkey, 0);

	वापस ret;
पूर्ण

अटल u8 smp_confirm(काष्ठा smp_chan *smp)
अणु
	काष्ठा l2cap_conn *conn = smp->conn;
	काष्ठा smp_cmd_pairing_confirm cp;
	पूर्णांक ret;

	bt_dev_dbg(conn->hcon->hdev, "conn %p", conn);

	ret = smp_c1(smp->tk, smp->prnd, smp->preq, smp->prsp,
		     conn->hcon->init_addr_type, &conn->hcon->init_addr,
		     conn->hcon->resp_addr_type, &conn->hcon->resp_addr,
		     cp.confirm_val);
	अगर (ret)
		वापस SMP_UNSPECIFIED;

	clear_bit(SMP_FLAG_CFM_PENDING, &smp->flags);

	smp_send_cmd(smp->conn, SMP_CMD_PAIRING_CONFIRM, माप(cp), &cp);

	अगर (conn->hcon->out)
		SMP_ALLOW_CMD(smp, SMP_CMD_PAIRING_CONFIRM);
	अन्यथा
		SMP_ALLOW_CMD(smp, SMP_CMD_PAIRING_RANDOM);

	वापस 0;
पूर्ण

अटल u8 smp_अक्रमom(काष्ठा smp_chan *smp)
अणु
	काष्ठा l2cap_conn *conn = smp->conn;
	काष्ठा hci_conn *hcon = conn->hcon;
	u8 confirm[16];
	पूर्णांक ret;

	bt_dev_dbg(conn->hcon->hdev, "conn %p %s", conn,
		   conn->hcon->out ? "master" : "slave");

	ret = smp_c1(smp->tk, smp->rrnd, smp->preq, smp->prsp,
		     hcon->init_addr_type, &hcon->init_addr,
		     hcon->resp_addr_type, &hcon->resp_addr, confirm);
	अगर (ret)
		वापस SMP_UNSPECIFIED;

	अगर (crypto_memneq(smp->pcnf, confirm, माप(smp->pcnf))) अणु
		bt_dev_err(hcon->hdev, "pairing failed "
			   "(confirmation values mismatch)");
		वापस SMP_CONFIRM_FAILED;
	पूर्ण

	अगर (hcon->out) अणु
		u8 stk[16];
		__le64 अक्रम = 0;
		__le16 eभाग = 0;

		smp_s1(smp->tk, smp->rrnd, smp->prnd, stk);

		अगर (test_and_set_bit(HCI_CONN_ENCRYPT_PEND, &hcon->flags))
			वापस SMP_UNSPECIFIED;

		hci_le_start_enc(hcon, eभाग, अक्रम, stk, smp->enc_key_size);
		hcon->enc_key_size = smp->enc_key_size;
		set_bit(HCI_CONN_STK_ENCRYPT, &hcon->flags);
	पूर्ण अन्यथा अणु
		u8 stk[16], auth;
		__le64 अक्रम = 0;
		__le16 eभाग = 0;

		smp_send_cmd(conn, SMP_CMD_PAIRING_RANDOM, माप(smp->prnd),
			     smp->prnd);

		smp_s1(smp->tk, smp->prnd, smp->rrnd, stk);

		अगर (hcon->pending_sec_level == BT_SECURITY_HIGH)
			auth = 1;
		अन्यथा
			auth = 0;

		/* Even though there's no _SLAVE suffix this is the
		 * slave STK we're adding क्रम later lookup (the master
		 * STK never needs to be stored).
		 */
		hci_add_ltk(hcon->hdev, &hcon->dst, hcon->dst_type,
			    SMP_STK, auth, stk, smp->enc_key_size, eभाग, अक्रम);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम smp_notअगरy_keys(काष्ठा l2cap_conn *conn)
अणु
	काष्ठा l2cap_chan *chan = conn->smp;
	काष्ठा smp_chan *smp = chan->data;
	काष्ठा hci_conn *hcon = conn->hcon;
	काष्ठा hci_dev *hdev = hcon->hdev;
	काष्ठा smp_cmd_pairing *req = (व्योम *) &smp->preq[1];
	काष्ठा smp_cmd_pairing *rsp = (व्योम *) &smp->prsp[1];
	bool persistent;

	अगर (hcon->type == ACL_LINK) अणु
		अगर (hcon->key_type == HCI_LK_DEBUG_COMBINATION)
			persistent = false;
		अन्यथा
			persistent = !test_bit(HCI_CONN_FLUSH_KEY,
					       &hcon->flags);
	पूर्ण अन्यथा अणु
		/* The LTKs, IRKs and CSRKs should be persistent only अगर
		 * both sides had the bonding bit set in their
		 * authentication requests.
		 */
		persistent = !!((req->auth_req & rsp->auth_req) &
				SMP_AUTH_BONDING);
	पूर्ण

	अगर (smp->remote_irk) अणु
		mgmt_new_irk(hdev, smp->remote_irk, persistent);

		/* Now that user space can be considered to know the
		 * identity address track the connection based on it
		 * from now on (assuming this is an LE link).
		 */
		अगर (hcon->type == LE_LINK) अणु
			bacpy(&hcon->dst, &smp->remote_irk->bdaddr);
			hcon->dst_type = smp->remote_irk->addr_type;
			queue_work(hdev->workqueue, &conn->id_addr_update_work);
		पूर्ण
	पूर्ण

	अगर (smp->csrk) अणु
		smp->csrk->bdaddr_type = hcon->dst_type;
		bacpy(&smp->csrk->bdaddr, &hcon->dst);
		mgmt_new_csrk(hdev, smp->csrk, persistent);
	पूर्ण

	अगर (smp->slave_csrk) अणु
		smp->slave_csrk->bdaddr_type = hcon->dst_type;
		bacpy(&smp->slave_csrk->bdaddr, &hcon->dst);
		mgmt_new_csrk(hdev, smp->slave_csrk, persistent);
	पूर्ण

	अगर (smp->ltk) अणु
		smp->ltk->bdaddr_type = hcon->dst_type;
		bacpy(&smp->ltk->bdaddr, &hcon->dst);
		mgmt_new_ltk(hdev, smp->ltk, persistent);
	पूर्ण

	अगर (smp->slave_ltk) अणु
		smp->slave_ltk->bdaddr_type = hcon->dst_type;
		bacpy(&smp->slave_ltk->bdaddr, &hcon->dst);
		mgmt_new_ltk(hdev, smp->slave_ltk, persistent);
	पूर्ण

	अगर (smp->link_key) अणु
		काष्ठा link_key *key;
		u8 type;

		अगर (test_bit(SMP_FLAG_DEBUG_KEY, &smp->flags))
			type = HCI_LK_DEBUG_COMBINATION;
		अन्यथा अगर (hcon->sec_level == BT_SECURITY_FIPS)
			type = HCI_LK_AUTH_COMBINATION_P256;
		अन्यथा
			type = HCI_LK_UNAUTH_COMBINATION_P256;

		key = hci_add_link_key(hdev, smp->conn->hcon, &hcon->dst,
				       smp->link_key, type, 0, &persistent);
		अगर (key) अणु
			mgmt_new_link_key(hdev, key, persistent);

			/* Don't keep debug keys around अगर the relevant
			 * flag is not set.
			 */
			अगर (!hci_dev_test_flag(hdev, HCI_KEEP_DEBUG_KEYS) &&
			    key->type == HCI_LK_DEBUG_COMBINATION) अणु
				list_del_rcu(&key->list);
				kमुक्त_rcu(key, rcu);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम sc_add_ltk(काष्ठा smp_chan *smp)
अणु
	काष्ठा hci_conn *hcon = smp->conn->hcon;
	u8 key_type, auth;

	अगर (test_bit(SMP_FLAG_DEBUG_KEY, &smp->flags))
		key_type = SMP_LTK_P256_DEBUG;
	अन्यथा
		key_type = SMP_LTK_P256;

	अगर (hcon->pending_sec_level == BT_SECURITY_FIPS)
		auth = 1;
	अन्यथा
		auth = 0;

	smp->ltk = hci_add_ltk(hcon->hdev, &hcon->dst, hcon->dst_type,
			       key_type, auth, smp->tk, smp->enc_key_size,
			       0, 0);
पूर्ण

अटल व्योम sc_generate_link_key(काष्ठा smp_chan *smp)
अणु
	/* From core spec. Spells out in ASCII as 'lebr'. */
	स्थिर u8 lebr[4] = अणु 0x72, 0x62, 0x65, 0x6c पूर्ण;

	smp->link_key = kzalloc(16, GFP_KERNEL);
	अगर (!smp->link_key)
		वापस;

	अगर (test_bit(SMP_FLAG_CT2, &smp->flags)) अणु
		/* SALT = 0x000000000000000000000000746D7031 */
		स्थिर u8 salt[16] = अणु 0x31, 0x70, 0x6d, 0x74 पूर्ण;

		अगर (smp_h7(smp->tfm_cmac, smp->tk, salt, smp->link_key)) अणु
			kमुक्त_sensitive(smp->link_key);
			smp->link_key = शून्य;
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* From core spec. Spells out in ASCII as 'tmp1'. */
		स्थिर u8 पंचांगp1[4] = अणु 0x31, 0x70, 0x6d, 0x74 पूर्ण;

		अगर (smp_h6(smp->tfm_cmac, smp->tk, पंचांगp1, smp->link_key)) अणु
			kमुक्त_sensitive(smp->link_key);
			smp->link_key = शून्य;
			वापस;
		पूर्ण
	पूर्ण

	अगर (smp_h6(smp->tfm_cmac, smp->link_key, lebr, smp->link_key)) अणु
		kमुक्त_sensitive(smp->link_key);
		smp->link_key = शून्य;
		वापस;
	पूर्ण
पूर्ण

अटल व्योम smp_allow_key_dist(काष्ठा smp_chan *smp)
अणु
	/* Allow the first expected phase 3 PDU. The rest of the PDUs
	 * will be allowed in each PDU handler to ensure we receive
	 * them in the correct order.
	 */
	अगर (smp->remote_key_dist & SMP_DIST_ENC_KEY)
		SMP_ALLOW_CMD(smp, SMP_CMD_ENCRYPT_INFO);
	अन्यथा अगर (smp->remote_key_dist & SMP_DIST_ID_KEY)
		SMP_ALLOW_CMD(smp, SMP_CMD_IDENT_INFO);
	अन्यथा अगर (smp->remote_key_dist & SMP_DIST_SIGN)
		SMP_ALLOW_CMD(smp, SMP_CMD_SIGN_INFO);
पूर्ण

अटल व्योम sc_generate_ltk(काष्ठा smp_chan *smp)
अणु
	/* From core spec. Spells out in ASCII as 'brle'. */
	स्थिर u8 brle[4] = अणु 0x65, 0x6c, 0x72, 0x62 पूर्ण;
	काष्ठा hci_conn *hcon = smp->conn->hcon;
	काष्ठा hci_dev *hdev = hcon->hdev;
	काष्ठा link_key *key;

	key = hci_find_link_key(hdev, &hcon->dst);
	अगर (!key) अणु
		bt_dev_err(hdev, "no Link Key found to generate LTK");
		वापस;
	पूर्ण

	अगर (key->type == HCI_LK_DEBUG_COMBINATION)
		set_bit(SMP_FLAG_DEBUG_KEY, &smp->flags);

	अगर (test_bit(SMP_FLAG_CT2, &smp->flags)) अणु
		/* SALT = 0x000000000000000000000000746D7032 */
		स्थिर u8 salt[16] = अणु 0x32, 0x70, 0x6d, 0x74 पूर्ण;

		अगर (smp_h7(smp->tfm_cmac, key->val, salt, smp->tk))
			वापस;
	पूर्ण अन्यथा अणु
		/* From core spec. Spells out in ASCII as 'tmp2'. */
		स्थिर u8 पंचांगp2[4] = अणु 0x32, 0x70, 0x6d, 0x74 पूर्ण;

		अगर (smp_h6(smp->tfm_cmac, key->val, पंचांगp2, smp->tk))
			वापस;
	पूर्ण

	अगर (smp_h6(smp->tfm_cmac, smp->tk, brle, smp->tk))
		वापस;

	sc_add_ltk(smp);
पूर्ण

अटल व्योम smp_distribute_keys(काष्ठा smp_chan *smp)
अणु
	काष्ठा smp_cmd_pairing *req, *rsp;
	काष्ठा l2cap_conn *conn = smp->conn;
	काष्ठा hci_conn *hcon = conn->hcon;
	काष्ठा hci_dev *hdev = hcon->hdev;
	__u8 *keydist;

	bt_dev_dbg(hdev, "conn %p", conn);

	rsp = (व्योम *) &smp->prsp[1];

	/* The responder sends its keys first */
	अगर (hcon->out && (smp->remote_key_dist & KEY_DIST_MASK)) अणु
		smp_allow_key_dist(smp);
		वापस;
	पूर्ण

	req = (व्योम *) &smp->preq[1];

	अगर (hcon->out) अणु
		keydist = &rsp->init_key_dist;
		*keydist &= req->init_key_dist;
	पूर्ण अन्यथा अणु
		keydist = &rsp->resp_key_dist;
		*keydist &= req->resp_key_dist;
	पूर्ण

	अगर (test_bit(SMP_FLAG_SC, &smp->flags)) अणु
		अगर (hcon->type == LE_LINK && (*keydist & SMP_DIST_LINK_KEY))
			sc_generate_link_key(smp);
		अगर (hcon->type == ACL_LINK && (*keydist & SMP_DIST_ENC_KEY))
			sc_generate_ltk(smp);

		/* Clear the keys which are generated but not distributed */
		*keydist &= ~SMP_SC_NO_DIST;
	पूर्ण

	bt_dev_dbg(hdev, "keydist 0x%x", *keydist);

	अगर (*keydist & SMP_DIST_ENC_KEY) अणु
		काष्ठा smp_cmd_encrypt_info enc;
		काष्ठा smp_cmd_master_ident ident;
		काष्ठा smp_ltk *ltk;
		u8 authenticated;
		__le16 eभाग;
		__le64 अक्रम;

		/* Make sure we generate only the signअगरicant amount of
		 * bytes based on the encryption key size, and set the rest
		 * of the value to zeroes.
		 */
		get_अक्रमom_bytes(enc.ltk, smp->enc_key_size);
		स_रखो(enc.ltk + smp->enc_key_size, 0,
		       माप(enc.ltk) - smp->enc_key_size);

		get_अक्रमom_bytes(&eभाग, माप(eभाग));
		get_अक्रमom_bytes(&अक्रम, माप(अक्रम));

		smp_send_cmd(conn, SMP_CMD_ENCRYPT_INFO, माप(enc), &enc);

		authenticated = hcon->sec_level == BT_SECURITY_HIGH;
		ltk = hci_add_ltk(hdev, &hcon->dst, hcon->dst_type,
				  SMP_LTK_SLAVE, authenticated, enc.ltk,
				  smp->enc_key_size, eभाग, अक्रम);
		smp->slave_ltk = ltk;

		ident.eभाग = eभाग;
		ident.अक्रम = अक्रम;

		smp_send_cmd(conn, SMP_CMD_MASTER_IDENT, माप(ident), &ident);

		*keydist &= ~SMP_DIST_ENC_KEY;
	पूर्ण

	अगर (*keydist & SMP_DIST_ID_KEY) अणु
		काष्ठा smp_cmd_ident_addr_info addrinfo;
		काष्ठा smp_cmd_ident_info idinfo;

		स_नकल(idinfo.irk, hdev->irk, माप(idinfo.irk));

		smp_send_cmd(conn, SMP_CMD_IDENT_INFO, माप(idinfo), &idinfo);

		/* The hci_conn contains the local identity address
		 * after the connection has been established.
		 *
		 * This is true even when the connection has been
		 * established using a resolvable अक्रमom address.
		 */
		bacpy(&addrinfo.bdaddr, &hcon->src);
		addrinfo.addr_type = hcon->src_type;

		smp_send_cmd(conn, SMP_CMD_IDENT_ADDR_INFO, माप(addrinfo),
			     &addrinfo);

		*keydist &= ~SMP_DIST_ID_KEY;
	पूर्ण

	अगर (*keydist & SMP_DIST_SIGN) अणु
		काष्ठा smp_cmd_sign_info sign;
		काष्ठा smp_csrk *csrk;

		/* Generate a new अक्रमom key */
		get_अक्रमom_bytes(sign.csrk, माप(sign.csrk));

		csrk = kzalloc(माप(*csrk), GFP_KERNEL);
		अगर (csrk) अणु
			अगर (hcon->sec_level > BT_SECURITY_MEDIUM)
				csrk->type = MGMT_CSRK_LOCAL_AUTHENTICATED;
			अन्यथा
				csrk->type = MGMT_CSRK_LOCAL_UNAUTHENTICATED;
			स_नकल(csrk->val, sign.csrk, माप(csrk->val));
		पूर्ण
		smp->slave_csrk = csrk;

		smp_send_cmd(conn, SMP_CMD_SIGN_INFO, माप(sign), &sign);

		*keydist &= ~SMP_DIST_SIGN;
	पूर्ण

	/* If there are still keys to be received रुको क्रम them */
	अगर (smp->remote_key_dist & KEY_DIST_MASK) अणु
		smp_allow_key_dist(smp);
		वापस;
	पूर्ण

	set_bit(SMP_FLAG_COMPLETE, &smp->flags);
	smp_notअगरy_keys(conn);

	smp_chan_destroy(conn);
पूर्ण

अटल व्योम smp_समयout(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा smp_chan *smp = container_of(work, काष्ठा smp_chan,
					    security_समयr.work);
	काष्ठा l2cap_conn *conn = smp->conn;

	bt_dev_dbg(conn->hcon->hdev, "conn %p", conn);

	hci_disconnect(conn->hcon, HCI_ERROR_REMOTE_USER_TERM);
पूर्ण

अटल काष्ठा smp_chan *smp_chan_create(काष्ठा l2cap_conn *conn)
अणु
	काष्ठा hci_conn *hcon = conn->hcon;
	काष्ठा l2cap_chan *chan = conn->smp;
	काष्ठा smp_chan *smp;

	smp = kzalloc(माप(*smp), GFP_ATOMIC);
	अगर (!smp)
		वापस शून्य;

	smp->tfm_cmac = crypto_alloc_shash("cmac(aes)", 0, 0);
	अगर (IS_ERR(smp->tfm_cmac)) अणु
		bt_dev_err(hcon->hdev, "Unable to create CMAC crypto context");
		जाओ zमुक्त_smp;
	पूर्ण

	smp->tfm_ecdh = crypto_alloc_kpp("ecdh-nist-p256", 0, 0);
	अगर (IS_ERR(smp->tfm_ecdh)) अणु
		bt_dev_err(hcon->hdev, "Unable to create ECDH crypto context");
		जाओ मुक्त_shash;
	पूर्ण

	smp->conn = conn;
	chan->data = smp;

	SMP_ALLOW_CMD(smp, SMP_CMD_PAIRING_FAIL);

	INIT_DELAYED_WORK(&smp->security_समयr, smp_समयout);

	hci_conn_hold(hcon);

	वापस smp;

मुक्त_shash:
	crypto_मुक्त_shash(smp->tfm_cmac);
zमुक्त_smp:
	kमुक्त_sensitive(smp);
	वापस शून्य;
पूर्ण

अटल पूर्णांक sc_mackey_and_ltk(काष्ठा smp_chan *smp, u8 mackey[16], u8 ltk[16])
अणु
	काष्ठा hci_conn *hcon = smp->conn->hcon;
	u8 *na, *nb, a[7], b[7];

	अगर (hcon->out) अणु
		na   = smp->prnd;
		nb   = smp->rrnd;
	पूर्ण अन्यथा अणु
		na   = smp->rrnd;
		nb   = smp->prnd;
	पूर्ण

	स_नकल(a, &hcon->init_addr, 6);
	स_नकल(b, &hcon->resp_addr, 6);
	a[6] = hcon->init_addr_type;
	b[6] = hcon->resp_addr_type;

	वापस smp_f5(smp->tfm_cmac, smp->dhkey, na, nb, a, b, mackey, ltk);
पूर्ण

अटल व्योम sc_dhkey_check(काष्ठा smp_chan *smp)
अणु
	काष्ठा hci_conn *hcon = smp->conn->hcon;
	काष्ठा smp_cmd_dhkey_check check;
	u8 a[7], b[7], *local_addr, *remote_addr;
	u8 io_cap[3], r[16];

	स_नकल(a, &hcon->init_addr, 6);
	स_नकल(b, &hcon->resp_addr, 6);
	a[6] = hcon->init_addr_type;
	b[6] = hcon->resp_addr_type;

	अगर (hcon->out) अणु
		local_addr = a;
		remote_addr = b;
		स_नकल(io_cap, &smp->preq[1], 3);
	पूर्ण अन्यथा अणु
		local_addr = b;
		remote_addr = a;
		स_नकल(io_cap, &smp->prsp[1], 3);
	पूर्ण

	स_रखो(r, 0, माप(r));

	अगर (smp->method == REQ_PASSKEY || smp->method == DSP_PASSKEY)
		put_unaligned_le32(hcon->passkey_notअगरy, r);

	अगर (smp->method == REQ_OOB)
		स_नकल(r, smp->rr, 16);

	smp_f6(smp->tfm_cmac, smp->mackey, smp->prnd, smp->rrnd, r, io_cap,
	       local_addr, remote_addr, check.e);

	smp_send_cmd(smp->conn, SMP_CMD_DHKEY_CHECK, माप(check), &check);
पूर्ण

अटल u8 sc_passkey_send_confirm(काष्ठा smp_chan *smp)
अणु
	काष्ठा l2cap_conn *conn = smp->conn;
	काष्ठा hci_conn *hcon = conn->hcon;
	काष्ठा smp_cmd_pairing_confirm cfm;
	u8 r;

	r = ((hcon->passkey_notअगरy >> smp->passkey_round) & 0x01);
	r |= 0x80;

	get_अक्रमom_bytes(smp->prnd, माप(smp->prnd));

	अगर (smp_f4(smp->tfm_cmac, smp->local_pk, smp->remote_pk, smp->prnd, r,
		   cfm.confirm_val))
		वापस SMP_UNSPECIFIED;

	smp_send_cmd(conn, SMP_CMD_PAIRING_CONFIRM, माप(cfm), &cfm);

	वापस 0;
पूर्ण

अटल u8 sc_passkey_round(काष्ठा smp_chan *smp, u8 smp_op)
अणु
	काष्ठा l2cap_conn *conn = smp->conn;
	काष्ठा hci_conn *hcon = conn->hcon;
	काष्ठा hci_dev *hdev = hcon->hdev;
	u8 cfm[16], r;

	/* Ignore the PDU अगर we've alपढ़ोy करोne 20 rounds (0 - 19) */
	अगर (smp->passkey_round >= 20)
		वापस 0;

	चयन (smp_op) अणु
	हाल SMP_CMD_PAIRING_RANDOM:
		r = ((hcon->passkey_notअगरy >> smp->passkey_round) & 0x01);
		r |= 0x80;

		अगर (smp_f4(smp->tfm_cmac, smp->remote_pk, smp->local_pk,
			   smp->rrnd, r, cfm))
			वापस SMP_UNSPECIFIED;

		अगर (crypto_memneq(smp->pcnf, cfm, 16))
			वापस SMP_CONFIRM_FAILED;

		smp->passkey_round++;

		अगर (smp->passkey_round == 20) अणु
			/* Generate MacKey and LTK */
			अगर (sc_mackey_and_ltk(smp, smp->mackey, smp->tk))
				वापस SMP_UNSPECIFIED;
		पूर्ण

		/* The round is only complete when the initiator
		 * receives pairing अक्रमom.
		 */
		अगर (!hcon->out) अणु
			smp_send_cmd(conn, SMP_CMD_PAIRING_RANDOM,
				     माप(smp->prnd), smp->prnd);
			अगर (smp->passkey_round == 20)
				SMP_ALLOW_CMD(smp, SMP_CMD_DHKEY_CHECK);
			अन्यथा
				SMP_ALLOW_CMD(smp, SMP_CMD_PAIRING_CONFIRM);
			वापस 0;
		पूर्ण

		/* Start the next round */
		अगर (smp->passkey_round != 20)
			वापस sc_passkey_round(smp, 0);

		/* Passkey rounds are complete - start DHKey Check */
		sc_dhkey_check(smp);
		SMP_ALLOW_CMD(smp, SMP_CMD_DHKEY_CHECK);

		अवरोध;

	हाल SMP_CMD_PAIRING_CONFIRM:
		अगर (test_bit(SMP_FLAG_WAIT_USER, &smp->flags)) अणु
			set_bit(SMP_FLAG_CFM_PENDING, &smp->flags);
			वापस 0;
		पूर्ण

		SMP_ALLOW_CMD(smp, SMP_CMD_PAIRING_RANDOM);

		अगर (hcon->out) अणु
			smp_send_cmd(conn, SMP_CMD_PAIRING_RANDOM,
				     माप(smp->prnd), smp->prnd);
			वापस 0;
		पूर्ण

		वापस sc_passkey_send_confirm(smp);

	हाल SMP_CMD_PUBLIC_KEY:
	शेष:
		/* Initiating device starts the round */
		अगर (!hcon->out)
			वापस 0;

		bt_dev_dbg(hdev, "Starting passkey round %u",
			   smp->passkey_round + 1);

		SMP_ALLOW_CMD(smp, SMP_CMD_PAIRING_CONFIRM);

		वापस sc_passkey_send_confirm(smp);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sc_user_reply(काष्ठा smp_chan *smp, u16 mgmt_op, __le32 passkey)
अणु
	काष्ठा l2cap_conn *conn = smp->conn;
	काष्ठा hci_conn *hcon = conn->hcon;
	u8 smp_op;

	clear_bit(SMP_FLAG_WAIT_USER, &smp->flags);

	चयन (mgmt_op) अणु
	हाल MGMT_OP_USER_PASSKEY_NEG_REPLY:
		smp_failure(smp->conn, SMP_PASSKEY_ENTRY_FAILED);
		वापस 0;
	हाल MGMT_OP_USER_CONFIRM_NEG_REPLY:
		smp_failure(smp->conn, SMP_NUMERIC_COMP_FAILED);
		वापस 0;
	हाल MGMT_OP_USER_PASSKEY_REPLY:
		hcon->passkey_notअगरy = le32_to_cpu(passkey);
		smp->passkey_round = 0;

		अगर (test_and_clear_bit(SMP_FLAG_CFM_PENDING, &smp->flags))
			smp_op = SMP_CMD_PAIRING_CONFIRM;
		अन्यथा
			smp_op = 0;

		अगर (sc_passkey_round(smp, smp_op))
			वापस -EIO;

		वापस 0;
	पूर्ण

	/* Initiator sends DHKey check first */
	अगर (hcon->out) अणु
		sc_dhkey_check(smp);
		SMP_ALLOW_CMD(smp, SMP_CMD_DHKEY_CHECK);
	पूर्ण अन्यथा अगर (test_and_clear_bit(SMP_FLAG_DHKEY_PENDING, &smp->flags)) अणु
		sc_dhkey_check(smp);
		sc_add_ltk(smp);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक smp_user_confirm_reply(काष्ठा hci_conn *hcon, u16 mgmt_op, __le32 passkey)
अणु
	काष्ठा l2cap_conn *conn = hcon->l2cap_data;
	काष्ठा l2cap_chan *chan;
	काष्ठा smp_chan *smp;
	u32 value;
	पूर्णांक err;

	अगर (!conn)
		वापस -ENOTCONN;

	bt_dev_dbg(conn->hcon->hdev, "");

	chan = conn->smp;
	अगर (!chan)
		वापस -ENOTCONN;

	l2cap_chan_lock(chan);
	अगर (!chan->data) अणु
		err = -ENOTCONN;
		जाओ unlock;
	पूर्ण

	smp = chan->data;

	अगर (test_bit(SMP_FLAG_SC, &smp->flags)) अणु
		err = sc_user_reply(smp, mgmt_op, passkey);
		जाओ unlock;
	पूर्ण

	चयन (mgmt_op) अणु
	हाल MGMT_OP_USER_PASSKEY_REPLY:
		value = le32_to_cpu(passkey);
		स_रखो(smp->tk, 0, माप(smp->tk));
		bt_dev_dbg(conn->hcon->hdev, "PassKey: %d", value);
		put_unaligned_le32(value, smp->tk);
		fallthrough;
	हाल MGMT_OP_USER_CONFIRM_REPLY:
		set_bit(SMP_FLAG_TK_VALID, &smp->flags);
		अवरोध;
	हाल MGMT_OP_USER_PASSKEY_NEG_REPLY:
	हाल MGMT_OP_USER_CONFIRM_NEG_REPLY:
		smp_failure(conn, SMP_PASSKEY_ENTRY_FAILED);
		err = 0;
		जाओ unlock;
	शेष:
		smp_failure(conn, SMP_PASSKEY_ENTRY_FAILED);
		err = -EOPNOTSUPP;
		जाओ unlock;
	पूर्ण

	err = 0;

	/* If it is our turn to send Pairing Confirm, करो so now */
	अगर (test_bit(SMP_FLAG_CFM_PENDING, &smp->flags)) अणु
		u8 rsp = smp_confirm(smp);
		अगर (rsp)
			smp_failure(conn, rsp);
	पूर्ण

unlock:
	l2cap_chan_unlock(chan);
	वापस err;
पूर्ण

अटल व्योम build_bredr_pairing_cmd(काष्ठा smp_chan *smp,
				    काष्ठा smp_cmd_pairing *req,
				    काष्ठा smp_cmd_pairing *rsp)
अणु
	काष्ठा l2cap_conn *conn = smp->conn;
	काष्ठा hci_dev *hdev = conn->hcon->hdev;
	u8 local_dist = 0, remote_dist = 0;

	अगर (hci_dev_test_flag(hdev, HCI_BONDABLE)) अणु
		local_dist = SMP_DIST_ENC_KEY | SMP_DIST_SIGN;
		remote_dist = SMP_DIST_ENC_KEY | SMP_DIST_SIGN;
	पूर्ण

	अगर (hci_dev_test_flag(hdev, HCI_RPA_RESOLVING))
		remote_dist |= SMP_DIST_ID_KEY;

	अगर (hci_dev_test_flag(hdev, HCI_PRIVACY))
		local_dist |= SMP_DIST_ID_KEY;

	अगर (!rsp) अणु
		स_रखो(req, 0, माप(*req));

		req->auth_req        = SMP_AUTH_CT2;
		req->init_key_dist   = local_dist;
		req->resp_key_dist   = remote_dist;
		req->max_key_size    = conn->hcon->enc_key_size;

		smp->remote_key_dist = remote_dist;

		वापस;
	पूर्ण

	स_रखो(rsp, 0, माप(*rsp));

	rsp->auth_req        = SMP_AUTH_CT2;
	rsp->max_key_size    = conn->hcon->enc_key_size;
	rsp->init_key_dist   = req->init_key_dist & remote_dist;
	rsp->resp_key_dist   = req->resp_key_dist & local_dist;

	smp->remote_key_dist = rsp->init_key_dist;
पूर्ण

अटल u8 smp_cmd_pairing_req(काष्ठा l2cap_conn *conn, काष्ठा sk_buff *skb)
अणु
	काष्ठा smp_cmd_pairing rsp, *req = (व्योम *) skb->data;
	काष्ठा l2cap_chan *chan = conn->smp;
	काष्ठा hci_dev *hdev = conn->hcon->hdev;
	काष्ठा smp_chan *smp;
	u8 key_size, auth, sec_level;
	पूर्णांक ret;

	bt_dev_dbg(hdev, "conn %p", conn);

	अगर (skb->len < माप(*req))
		वापस SMP_INVALID_PARAMS;

	अगर (conn->hcon->role != HCI_ROLE_SLAVE)
		वापस SMP_CMD_NOTSUPP;

	अगर (!chan->data)
		smp = smp_chan_create(conn);
	अन्यथा
		smp = chan->data;

	अगर (!smp)
		वापस SMP_UNSPECIFIED;

	/* We didn't start the pairing, so match remote */
	auth = req->auth_req & AUTH_REQ_MASK(hdev);

	अगर (!hci_dev_test_flag(hdev, HCI_BONDABLE) &&
	    (auth & SMP_AUTH_BONDING))
		वापस SMP_PAIRING_NOTSUPP;

	अगर (hci_dev_test_flag(hdev, HCI_SC_ONLY) && !(auth & SMP_AUTH_SC))
		वापस SMP_AUTH_REQUIREMENTS;

	smp->preq[0] = SMP_CMD_PAIRING_REQ;
	स_नकल(&smp->preq[1], req, माप(*req));
	skb_pull(skb, माप(*req));

	/* If the remote side's OOB flag is set it means it has
	 * successfully received our local OOB data - thereक्रमe set the
	 * flag to indicate that local OOB is in use.
	 */
	अगर (req->oob_flag == SMP_OOB_PRESENT && SMP_DEV(hdev)->local_oob)
		set_bit(SMP_FLAG_LOCAL_OOB, &smp->flags);

	/* SMP over BR/EDR requires special treaपंचांगent */
	अगर (conn->hcon->type == ACL_LINK) अणु
		/* We must have a BR/EDR SC link */
		अगर (!test_bit(HCI_CONN_AES_CCM, &conn->hcon->flags) &&
		    !hci_dev_test_flag(hdev, HCI_FORCE_BREDR_SMP))
			वापस SMP_CROSS_TRANSP_NOT_ALLOWED;

		set_bit(SMP_FLAG_SC, &smp->flags);

		build_bredr_pairing_cmd(smp, req, &rsp);

		अगर (req->auth_req & SMP_AUTH_CT2)
			set_bit(SMP_FLAG_CT2, &smp->flags);

		key_size = min(req->max_key_size, rsp.max_key_size);
		अगर (check_enc_key_size(conn, key_size))
			वापस SMP_ENC_KEY_SIZE;

		/* Clear bits which are generated but not distributed */
		smp->remote_key_dist &= ~SMP_SC_NO_DIST;

		smp->prsp[0] = SMP_CMD_PAIRING_RSP;
		स_नकल(&smp->prsp[1], &rsp, माप(rsp));
		smp_send_cmd(conn, SMP_CMD_PAIRING_RSP, माप(rsp), &rsp);

		smp_distribute_keys(smp);
		वापस 0;
	पूर्ण

	build_pairing_cmd(conn, req, &rsp, auth);

	अगर (rsp.auth_req & SMP_AUTH_SC) अणु
		set_bit(SMP_FLAG_SC, &smp->flags);

		अगर (rsp.auth_req & SMP_AUTH_CT2)
			set_bit(SMP_FLAG_CT2, &smp->flags);
	पूर्ण

	अगर (conn->hcon->io_capability == HCI_IO_NO_INPUT_OUTPUT)
		sec_level = BT_SECURITY_MEDIUM;
	अन्यथा
		sec_level = authreq_to_seclevel(auth);

	अगर (sec_level > conn->hcon->pending_sec_level)
		conn->hcon->pending_sec_level = sec_level;

	/* If we need MITM check that it can be achieved */
	अगर (conn->hcon->pending_sec_level >= BT_SECURITY_HIGH) अणु
		u8 method;

		method = get_auth_method(smp, conn->hcon->io_capability,
					 req->io_capability);
		अगर (method == JUST_WORKS || method == JUST_CFM)
			वापस SMP_AUTH_REQUIREMENTS;
	पूर्ण

	key_size = min(req->max_key_size, rsp.max_key_size);
	अगर (check_enc_key_size(conn, key_size))
		वापस SMP_ENC_KEY_SIZE;

	get_अक्रमom_bytes(smp->prnd, माप(smp->prnd));

	smp->prsp[0] = SMP_CMD_PAIRING_RSP;
	स_नकल(&smp->prsp[1], &rsp, माप(rsp));

	smp_send_cmd(conn, SMP_CMD_PAIRING_RSP, माप(rsp), &rsp);

	clear_bit(SMP_FLAG_INITIATOR, &smp->flags);

	/* Strictly speaking we shouldn't allow Pairing Confirm क्रम the
	 * SC हाल, however some implementations incorrectly copy RFU auth
	 * req bits from our security request, which may create a false
	 * positive SC enablement.
	 */
	SMP_ALLOW_CMD(smp, SMP_CMD_PAIRING_CONFIRM);

	अगर (test_bit(SMP_FLAG_SC, &smp->flags)) अणु
		SMP_ALLOW_CMD(smp, SMP_CMD_PUBLIC_KEY);
		/* Clear bits which are generated but not distributed */
		smp->remote_key_dist &= ~SMP_SC_NO_DIST;
		/* Wait क्रम Public Key from Initiating Device */
		वापस 0;
	पूर्ण

	/* Request setup of TK */
	ret = tk_request(conn, 0, auth, rsp.io_capability, req->io_capability);
	अगर (ret)
		वापस SMP_UNSPECIFIED;

	वापस 0;
पूर्ण

अटल u8 sc_send_खुला_key(काष्ठा smp_chan *smp)
अणु
	काष्ठा hci_dev *hdev = smp->conn->hcon->hdev;

	bt_dev_dbg(hdev, "");

	अगर (test_bit(SMP_FLAG_LOCAL_OOB, &smp->flags)) अणु
		काष्ठा l2cap_chan *chan = hdev->smp_data;
		काष्ठा smp_dev *smp_dev;

		अगर (!chan || !chan->data)
			वापस SMP_UNSPECIFIED;

		smp_dev = chan->data;

		स_नकल(smp->local_pk, smp_dev->local_pk, 64);
		स_नकल(smp->lr, smp_dev->local_अक्रम, 16);

		अगर (smp_dev->debug_key)
			set_bit(SMP_FLAG_DEBUG_KEY, &smp->flags);

		जाओ करोne;
	पूर्ण

	अगर (hci_dev_test_flag(hdev, HCI_USE_DEBUG_KEYS)) अणु
		bt_dev_dbg(hdev, "Using debug keys");
		अगर (set_ecdh_privkey(smp->tfm_ecdh, debug_sk))
			वापस SMP_UNSPECIFIED;
		स_नकल(smp->local_pk, debug_pk, 64);
		set_bit(SMP_FLAG_DEBUG_KEY, &smp->flags);
	पूर्ण अन्यथा अणु
		जबतक (true) अणु
			/* Generate key pair क्रम Secure Connections */
			अगर (generate_ecdh_keys(smp->tfm_ecdh, smp->local_pk))
				वापस SMP_UNSPECIFIED;

			/* This is unlikely, but we need to check that
			 * we didn't accidentially generate a debug key.
			 */
			अगर (crypto_memneq(smp->local_pk, debug_pk, 64))
				अवरोध;
		पूर्ण
	पूर्ण

करोne:
	SMP_DBG("Local Public Key X: %32phN", smp->local_pk);
	SMP_DBG("Local Public Key Y: %32phN", smp->local_pk + 32);

	smp_send_cmd(smp->conn, SMP_CMD_PUBLIC_KEY, 64, smp->local_pk);

	वापस 0;
पूर्ण

अटल u8 smp_cmd_pairing_rsp(काष्ठा l2cap_conn *conn, काष्ठा sk_buff *skb)
अणु
	काष्ठा smp_cmd_pairing *req, *rsp = (व्योम *) skb->data;
	काष्ठा l2cap_chan *chan = conn->smp;
	काष्ठा smp_chan *smp = chan->data;
	काष्ठा hci_dev *hdev = conn->hcon->hdev;
	u8 key_size, auth;
	पूर्णांक ret;

	bt_dev_dbg(hdev, "conn %p", conn);

	अगर (skb->len < माप(*rsp))
		वापस SMP_INVALID_PARAMS;

	अगर (conn->hcon->role != HCI_ROLE_MASTER)
		वापस SMP_CMD_NOTSUPP;

	skb_pull(skb, माप(*rsp));

	req = (व्योम *) &smp->preq[1];

	key_size = min(req->max_key_size, rsp->max_key_size);
	अगर (check_enc_key_size(conn, key_size))
		वापस SMP_ENC_KEY_SIZE;

	auth = rsp->auth_req & AUTH_REQ_MASK(hdev);

	अगर (hci_dev_test_flag(hdev, HCI_SC_ONLY) && !(auth & SMP_AUTH_SC))
		वापस SMP_AUTH_REQUIREMENTS;

	/* If the remote side's OOB flag is set it means it has
	 * successfully received our local OOB data - thereक्रमe set the
	 * flag to indicate that local OOB is in use.
	 */
	अगर (rsp->oob_flag == SMP_OOB_PRESENT && SMP_DEV(hdev)->local_oob)
		set_bit(SMP_FLAG_LOCAL_OOB, &smp->flags);

	smp->prsp[0] = SMP_CMD_PAIRING_RSP;
	स_नकल(&smp->prsp[1], rsp, माप(*rsp));

	/* Update remote key distribution in हाल the remote cleared
	 * some bits that we had enabled in our request.
	 */
	smp->remote_key_dist &= rsp->resp_key_dist;

	अगर ((req->auth_req & SMP_AUTH_CT2) && (auth & SMP_AUTH_CT2))
		set_bit(SMP_FLAG_CT2, &smp->flags);

	/* For BR/EDR this means we're करोne and can start phase 3 */
	अगर (conn->hcon->type == ACL_LINK) अणु
		/* Clear bits which are generated but not distributed */
		smp->remote_key_dist &= ~SMP_SC_NO_DIST;
		smp_distribute_keys(smp);
		वापस 0;
	पूर्ण

	अगर ((req->auth_req & SMP_AUTH_SC) && (auth & SMP_AUTH_SC))
		set_bit(SMP_FLAG_SC, &smp->flags);
	अन्यथा अगर (conn->hcon->pending_sec_level > BT_SECURITY_HIGH)
		conn->hcon->pending_sec_level = BT_SECURITY_HIGH;

	/* If we need MITM check that it can be achieved */
	अगर (conn->hcon->pending_sec_level >= BT_SECURITY_HIGH) अणु
		u8 method;

		method = get_auth_method(smp, req->io_capability,
					 rsp->io_capability);
		अगर (method == JUST_WORKS || method == JUST_CFM)
			वापस SMP_AUTH_REQUIREMENTS;
	पूर्ण

	get_अक्रमom_bytes(smp->prnd, माप(smp->prnd));

	/* Update remote key distribution in हाल the remote cleared
	 * some bits that we had enabled in our request.
	 */
	smp->remote_key_dist &= rsp->resp_key_dist;

	अगर (test_bit(SMP_FLAG_SC, &smp->flags)) अणु
		/* Clear bits which are generated but not distributed */
		smp->remote_key_dist &= ~SMP_SC_NO_DIST;
		SMP_ALLOW_CMD(smp, SMP_CMD_PUBLIC_KEY);
		वापस sc_send_खुला_key(smp);
	पूर्ण

	auth |= req->auth_req;

	ret = tk_request(conn, 0, auth, req->io_capability, rsp->io_capability);
	अगर (ret)
		वापस SMP_UNSPECIFIED;

	set_bit(SMP_FLAG_CFM_PENDING, &smp->flags);

	/* Can't compose response until we have been confirmed */
	अगर (test_bit(SMP_FLAG_TK_VALID, &smp->flags))
		वापस smp_confirm(smp);

	वापस 0;
पूर्ण

अटल u8 sc_check_confirm(काष्ठा smp_chan *smp)
अणु
	काष्ठा l2cap_conn *conn = smp->conn;

	bt_dev_dbg(conn->hcon->hdev, "");

	अगर (smp->method == REQ_PASSKEY || smp->method == DSP_PASSKEY)
		वापस sc_passkey_round(smp, SMP_CMD_PAIRING_CONFIRM);

	अगर (conn->hcon->out) अणु
		smp_send_cmd(conn, SMP_CMD_PAIRING_RANDOM, माप(smp->prnd),
			     smp->prnd);
		SMP_ALLOW_CMD(smp, SMP_CMD_PAIRING_RANDOM);
	पूर्ण

	वापस 0;
पूर्ण

/* Work-around क्रम some implementations that incorrectly copy RFU bits
 * from our security request and thereby create the impression that
 * we're doing SC when in fact the remote doesn't support it.
 */
अटल पूर्णांक fixup_sc_false_positive(काष्ठा smp_chan *smp)
अणु
	काष्ठा l2cap_conn *conn = smp->conn;
	काष्ठा hci_conn *hcon = conn->hcon;
	काष्ठा hci_dev *hdev = hcon->hdev;
	काष्ठा smp_cmd_pairing *req, *rsp;
	u8 auth;

	/* The issue is only observed when we're in slave role */
	अगर (hcon->out)
		वापस SMP_UNSPECIFIED;

	अगर (hci_dev_test_flag(hdev, HCI_SC_ONLY)) अणु
		bt_dev_err(hdev, "refusing legacy fallback in SC-only mode");
		वापस SMP_UNSPECIFIED;
	पूर्ण

	bt_dev_err(hdev, "trying to fall back to legacy SMP");

	req = (व्योम *) &smp->preq[1];
	rsp = (व्योम *) &smp->prsp[1];

	/* Rebuild key dist flags which may have been cleared क्रम SC */
	smp->remote_key_dist = (req->init_key_dist & rsp->resp_key_dist);

	auth = req->auth_req & AUTH_REQ_MASK(hdev);

	अगर (tk_request(conn, 0, auth, rsp->io_capability, req->io_capability)) अणु
		bt_dev_err(hdev, "failed to fall back to legacy SMP");
		वापस SMP_UNSPECIFIED;
	पूर्ण

	clear_bit(SMP_FLAG_SC, &smp->flags);

	वापस 0;
पूर्ण

अटल u8 smp_cmd_pairing_confirm(काष्ठा l2cap_conn *conn, काष्ठा sk_buff *skb)
अणु
	काष्ठा l2cap_chan *chan = conn->smp;
	काष्ठा smp_chan *smp = chan->data;
	काष्ठा hci_conn *hcon = conn->hcon;
	काष्ठा hci_dev *hdev = hcon->hdev;

	bt_dev_dbg(hdev, "conn %p %s", conn, hcon->out ? "master" : "slave");

	अगर (skb->len < माप(smp->pcnf))
		वापस SMP_INVALID_PARAMS;

	स_नकल(smp->pcnf, skb->data, माप(smp->pcnf));
	skb_pull(skb, माप(smp->pcnf));

	अगर (test_bit(SMP_FLAG_SC, &smp->flags)) अणु
		पूर्णांक ret;

		/* Public Key exchange must happen beक्रमe any other steps */
		अगर (test_bit(SMP_FLAG_REMOTE_PK, &smp->flags))
			वापस sc_check_confirm(smp);

		bt_dev_err(hdev, "Unexpected SMP Pairing Confirm");

		ret = fixup_sc_false_positive(smp);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (conn->hcon->out) अणु
		smp_send_cmd(conn, SMP_CMD_PAIRING_RANDOM, माप(smp->prnd),
			     smp->prnd);
		SMP_ALLOW_CMD(smp, SMP_CMD_PAIRING_RANDOM);
		वापस 0;
	पूर्ण

	अगर (test_bit(SMP_FLAG_TK_VALID, &smp->flags))
		वापस smp_confirm(smp);

	set_bit(SMP_FLAG_CFM_PENDING, &smp->flags);

	वापस 0;
पूर्ण

अटल u8 smp_cmd_pairing_अक्रमom(काष्ठा l2cap_conn *conn, काष्ठा sk_buff *skb)
अणु
	काष्ठा l2cap_chan *chan = conn->smp;
	काष्ठा smp_chan *smp = chan->data;
	काष्ठा hci_conn *hcon = conn->hcon;
	u8 *pkax, *pkbx, *na, *nb, confirm_hपूर्णांक;
	u32 passkey;
	पूर्णांक err;

	bt_dev_dbg(hcon->hdev, "conn %p", conn);

	अगर (skb->len < माप(smp->rrnd))
		वापस SMP_INVALID_PARAMS;

	स_नकल(smp->rrnd, skb->data, माप(smp->rrnd));
	skb_pull(skb, माप(smp->rrnd));

	अगर (!test_bit(SMP_FLAG_SC, &smp->flags))
		वापस smp_अक्रमom(smp);

	अगर (hcon->out) अणु
		pkax = smp->local_pk;
		pkbx = smp->remote_pk;
		na   = smp->prnd;
		nb   = smp->rrnd;
	पूर्ण अन्यथा अणु
		pkax = smp->remote_pk;
		pkbx = smp->local_pk;
		na   = smp->rrnd;
		nb   = smp->prnd;
	पूर्ण

	अगर (smp->method == REQ_OOB) अणु
		अगर (!hcon->out)
			smp_send_cmd(conn, SMP_CMD_PAIRING_RANDOM,
				     माप(smp->prnd), smp->prnd);
		SMP_ALLOW_CMD(smp, SMP_CMD_DHKEY_CHECK);
		जाओ mackey_and_ltk;
	पूर्ण

	/* Passkey entry has special treaपंचांगent */
	अगर (smp->method == REQ_PASSKEY || smp->method == DSP_PASSKEY)
		वापस sc_passkey_round(smp, SMP_CMD_PAIRING_RANDOM);

	अगर (hcon->out) अणु
		u8 cfm[16];

		err = smp_f4(smp->tfm_cmac, smp->remote_pk, smp->local_pk,
			     smp->rrnd, 0, cfm);
		अगर (err)
			वापस SMP_UNSPECIFIED;

		अगर (crypto_memneq(smp->pcnf, cfm, 16))
			वापस SMP_CONFIRM_FAILED;
	पूर्ण अन्यथा अणु
		smp_send_cmd(conn, SMP_CMD_PAIRING_RANDOM, माप(smp->prnd),
			     smp->prnd);
		SMP_ALLOW_CMD(smp, SMP_CMD_DHKEY_CHECK);

		/* Only Just-Works pairing requires extra checks */
		अगर (smp->method != JUST_WORKS)
			जाओ mackey_and_ltk;

		/* If there alपढ़ोy exists दीर्घ term key in local host, leave
		 * the decision to user space since the remote device could
		 * be legitimate or malicious.
		 */
		अगर (hci_find_ltk(hcon->hdev, &hcon->dst, hcon->dst_type,
				 hcon->role)) अणु
			/* Set passkey to 0. The value can be any number since
			 * it'll be ignored anyway.
			 */
			passkey = 0;
			confirm_hपूर्णांक = 1;
			जाओ confirm;
		पूर्ण
	पूर्ण

mackey_and_ltk:
	/* Generate MacKey and LTK */
	err = sc_mackey_and_ltk(smp, smp->mackey, smp->tk);
	अगर (err)
		वापस SMP_UNSPECIFIED;

	अगर (smp->method == REQ_OOB) अणु
		अगर (hcon->out) अणु
			sc_dhkey_check(smp);
			SMP_ALLOW_CMD(smp, SMP_CMD_DHKEY_CHECK);
		पूर्ण
		वापस 0;
	पूर्ण

	err = smp_g2(smp->tfm_cmac, pkax, pkbx, na, nb, &passkey);
	अगर (err)
		वापस SMP_UNSPECIFIED;

	confirm_hपूर्णांक = 0;

confirm:
	अगर (smp->method == JUST_WORKS)
		confirm_hपूर्णांक = 1;

	err = mgmt_user_confirm_request(hcon->hdev, &hcon->dst, hcon->type,
					hcon->dst_type, passkey, confirm_hपूर्णांक);
	अगर (err)
		वापस SMP_UNSPECIFIED;

	set_bit(SMP_FLAG_WAIT_USER, &smp->flags);

	वापस 0;
पूर्ण

अटल bool smp_ltk_encrypt(काष्ठा l2cap_conn *conn, u8 sec_level)
अणु
	काष्ठा smp_ltk *key;
	काष्ठा hci_conn *hcon = conn->hcon;

	key = hci_find_ltk(hcon->hdev, &hcon->dst, hcon->dst_type, hcon->role);
	अगर (!key)
		वापस false;

	अगर (smp_ltk_sec_level(key) < sec_level)
		वापस false;

	अगर (test_and_set_bit(HCI_CONN_ENCRYPT_PEND, &hcon->flags))
		वापस true;

	hci_le_start_enc(hcon, key->eभाग, key->अक्रम, key->val, key->enc_size);
	hcon->enc_key_size = key->enc_size;

	/* We never store STKs क्रम master role, so clear this flag */
	clear_bit(HCI_CONN_STK_ENCRYPT, &hcon->flags);

	वापस true;
पूर्ण

bool smp_sufficient_security(काष्ठा hci_conn *hcon, u8 sec_level,
			     क्रमागत smp_key_pref key_pref)
अणु
	अगर (sec_level == BT_SECURITY_LOW)
		वापस true;

	/* If we're encrypted with an STK but the caller prefers using
	 * LTK claim insufficient security. This way we allow the
	 * connection to be re-encrypted with an LTK, even अगर the LTK
	 * provides the same level of security. Only exception is अगर we
	 * करोn't have an LTK (e.g. because of key distribution bits).
	 */
	अगर (key_pref == SMP_USE_LTK &&
	    test_bit(HCI_CONN_STK_ENCRYPT, &hcon->flags) &&
	    hci_find_ltk(hcon->hdev, &hcon->dst, hcon->dst_type, hcon->role))
		वापस false;

	अगर (hcon->sec_level >= sec_level)
		वापस true;

	वापस false;
पूर्ण

अटल u8 smp_cmd_security_req(काष्ठा l2cap_conn *conn, काष्ठा sk_buff *skb)
अणु
	काष्ठा smp_cmd_security_req *rp = (व्योम *) skb->data;
	काष्ठा smp_cmd_pairing cp;
	काष्ठा hci_conn *hcon = conn->hcon;
	काष्ठा hci_dev *hdev = hcon->hdev;
	काष्ठा smp_chan *smp;
	u8 sec_level, auth;

	bt_dev_dbg(hdev, "conn %p", conn);

	अगर (skb->len < माप(*rp))
		वापस SMP_INVALID_PARAMS;

	अगर (hcon->role != HCI_ROLE_MASTER)
		वापस SMP_CMD_NOTSUPP;

	auth = rp->auth_req & AUTH_REQ_MASK(hdev);

	अगर (hci_dev_test_flag(hdev, HCI_SC_ONLY) && !(auth & SMP_AUTH_SC))
		वापस SMP_AUTH_REQUIREMENTS;

	अगर (hcon->io_capability == HCI_IO_NO_INPUT_OUTPUT)
		sec_level = BT_SECURITY_MEDIUM;
	अन्यथा
		sec_level = authreq_to_seclevel(auth);

	अगर (smp_sufficient_security(hcon, sec_level, SMP_USE_LTK)) अणु
		/* If link is alपढ़ोy encrypted with sufficient security we
		 * still need refresh encryption as per Core Spec 5.0 Vol 3,
		 * Part H 2.4.6
		 */
		smp_ltk_encrypt(conn, hcon->sec_level);
		वापस 0;
	पूर्ण

	अगर (sec_level > hcon->pending_sec_level)
		hcon->pending_sec_level = sec_level;

	अगर (smp_ltk_encrypt(conn, hcon->pending_sec_level))
		वापस 0;

	smp = smp_chan_create(conn);
	अगर (!smp)
		वापस SMP_UNSPECIFIED;

	अगर (!hci_dev_test_flag(hdev, HCI_BONDABLE) &&
	    (auth & SMP_AUTH_BONDING))
		वापस SMP_PAIRING_NOTSUPP;

	skb_pull(skb, माप(*rp));

	स_रखो(&cp, 0, माप(cp));
	build_pairing_cmd(conn, &cp, शून्य, auth);

	smp->preq[0] = SMP_CMD_PAIRING_REQ;
	स_नकल(&smp->preq[1], &cp, माप(cp));

	smp_send_cmd(conn, SMP_CMD_PAIRING_REQ, माप(cp), &cp);
	SMP_ALLOW_CMD(smp, SMP_CMD_PAIRING_RSP);

	वापस 0;
पूर्ण

पूर्णांक smp_conn_security(काष्ठा hci_conn *hcon, __u8 sec_level)
अणु
	काष्ठा l2cap_conn *conn = hcon->l2cap_data;
	काष्ठा l2cap_chan *chan;
	काष्ठा smp_chan *smp;
	__u8 authreq;
	पूर्णांक ret;

	bt_dev_dbg(hcon->hdev, "conn %p hcon %p level 0x%2.2x", conn, hcon,
		   sec_level);

	/* This may be शून्य अगर there's an unexpected disconnection */
	अगर (!conn)
		वापस 1;

	अगर (!hci_dev_test_flag(hcon->hdev, HCI_LE_ENABLED))
		वापस 1;

	अगर (smp_sufficient_security(hcon, sec_level, SMP_USE_LTK))
		वापस 1;

	अगर (sec_level > hcon->pending_sec_level)
		hcon->pending_sec_level = sec_level;

	अगर (hcon->role == HCI_ROLE_MASTER)
		अगर (smp_ltk_encrypt(conn, hcon->pending_sec_level))
			वापस 0;

	chan = conn->smp;
	अगर (!chan) अणु
		bt_dev_err(hcon->hdev, "security requested but not available");
		वापस 1;
	पूर्ण

	l2cap_chan_lock(chan);

	/* If SMP is alपढ़ोy in progress ignore this request */
	अगर (chan->data) अणु
		ret = 0;
		जाओ unlock;
	पूर्ण

	smp = smp_chan_create(conn);
	अगर (!smp) अणु
		ret = 1;
		जाओ unlock;
	पूर्ण

	authreq = seclevel_to_authreq(sec_level);

	अगर (hci_dev_test_flag(hcon->hdev, HCI_SC_ENABLED)) अणु
		authreq |= SMP_AUTH_SC;
		अगर (hci_dev_test_flag(hcon->hdev, HCI_SSP_ENABLED))
			authreq |= SMP_AUTH_CT2;
	पूर्ण

	/* Don't attempt to set MITM अगर setting is overridden by debugfs
	 * Needed to pass certअगरication test SM/MAS/PKE/BV-01-C
	 */
	अगर (!hci_dev_test_flag(hcon->hdev, HCI_FORCE_NO_MITM)) अणु
		/* Require MITM अगर IO Capability allows or the security level
		 * requires it.
		 */
		अगर (hcon->io_capability != HCI_IO_NO_INPUT_OUTPUT ||
		    hcon->pending_sec_level > BT_SECURITY_MEDIUM)
			authreq |= SMP_AUTH_MITM;
	पूर्ण

	अगर (hcon->role == HCI_ROLE_MASTER) अणु
		काष्ठा smp_cmd_pairing cp;

		build_pairing_cmd(conn, &cp, शून्य, authreq);
		smp->preq[0] = SMP_CMD_PAIRING_REQ;
		स_नकल(&smp->preq[1], &cp, माप(cp));

		smp_send_cmd(conn, SMP_CMD_PAIRING_REQ, माप(cp), &cp);
		SMP_ALLOW_CMD(smp, SMP_CMD_PAIRING_RSP);
	पूर्ण अन्यथा अणु
		काष्ठा smp_cmd_security_req cp;
		cp.auth_req = authreq;
		smp_send_cmd(conn, SMP_CMD_SECURITY_REQ, माप(cp), &cp);
		SMP_ALLOW_CMD(smp, SMP_CMD_PAIRING_REQ);
	पूर्ण

	set_bit(SMP_FLAG_INITIATOR, &smp->flags);
	ret = 0;

unlock:
	l2cap_chan_unlock(chan);
	वापस ret;
पूर्ण

पूर्णांक smp_cancel_and_हटाओ_pairing(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
				  u8 addr_type)
अणु
	काष्ठा hci_conn *hcon;
	काष्ठा l2cap_conn *conn;
	काष्ठा l2cap_chan *chan;
	काष्ठा smp_chan *smp;
	पूर्णांक err;

	err = hci_हटाओ_ltk(hdev, bdaddr, addr_type);
	hci_हटाओ_irk(hdev, bdaddr, addr_type);

	hcon = hci_conn_hash_lookup_le(hdev, bdaddr, addr_type);
	अगर (!hcon)
		जाओ करोne;

	conn = hcon->l2cap_data;
	अगर (!conn)
		जाओ करोne;

	chan = conn->smp;
	अगर (!chan)
		जाओ करोne;

	l2cap_chan_lock(chan);

	smp = chan->data;
	अगर (smp) अणु
		/* Set keys to शून्य to make sure smp_failure() करोes not try to
		 * हटाओ and मुक्त alपढ़ोy invalidated rcu list entries. */
		smp->ltk = शून्य;
		smp->slave_ltk = शून्य;
		smp->remote_irk = शून्य;

		अगर (test_bit(SMP_FLAG_COMPLETE, &smp->flags))
			smp_failure(conn, 0);
		अन्यथा
			smp_failure(conn, SMP_UNSPECIFIED);
		err = 0;
	पूर्ण

	l2cap_chan_unlock(chan);

करोne:
	वापस err;
पूर्ण

अटल पूर्णांक smp_cmd_encrypt_info(काष्ठा l2cap_conn *conn, काष्ठा sk_buff *skb)
अणु
	काष्ठा smp_cmd_encrypt_info *rp = (व्योम *) skb->data;
	काष्ठा l2cap_chan *chan = conn->smp;
	काष्ठा smp_chan *smp = chan->data;

	bt_dev_dbg(conn->hcon->hdev, "conn %p", conn);

	अगर (skb->len < माप(*rp))
		वापस SMP_INVALID_PARAMS;

	/* Pairing is पातed अगर any blocked keys are distributed */
	अगर (hci_is_blocked_key(conn->hcon->hdev, HCI_BLOCKED_KEY_TYPE_LTK,
			       rp->ltk)) अणु
		bt_dev_warn_ratelimited(conn->hcon->hdev,
					"LTK blocked for %pMR",
					&conn->hcon->dst);
		वापस SMP_INVALID_PARAMS;
	पूर्ण

	SMP_ALLOW_CMD(smp, SMP_CMD_MASTER_IDENT);

	skb_pull(skb, माप(*rp));

	स_नकल(smp->tk, rp->ltk, माप(smp->tk));

	वापस 0;
पूर्ण

अटल पूर्णांक smp_cmd_master_ident(काष्ठा l2cap_conn *conn, काष्ठा sk_buff *skb)
अणु
	काष्ठा smp_cmd_master_ident *rp = (व्योम *) skb->data;
	काष्ठा l2cap_chan *chan = conn->smp;
	काष्ठा smp_chan *smp = chan->data;
	काष्ठा hci_dev *hdev = conn->hcon->hdev;
	काष्ठा hci_conn *hcon = conn->hcon;
	काष्ठा smp_ltk *ltk;
	u8 authenticated;

	bt_dev_dbg(hdev, "conn %p", conn);

	अगर (skb->len < माप(*rp))
		वापस SMP_INVALID_PARAMS;

	/* Mark the inक्रमmation as received */
	smp->remote_key_dist &= ~SMP_DIST_ENC_KEY;

	अगर (smp->remote_key_dist & SMP_DIST_ID_KEY)
		SMP_ALLOW_CMD(smp, SMP_CMD_IDENT_INFO);
	अन्यथा अगर (smp->remote_key_dist & SMP_DIST_SIGN)
		SMP_ALLOW_CMD(smp, SMP_CMD_SIGN_INFO);

	skb_pull(skb, माप(*rp));

	authenticated = (hcon->sec_level == BT_SECURITY_HIGH);
	ltk = hci_add_ltk(hdev, &hcon->dst, hcon->dst_type, SMP_LTK,
			  authenticated, smp->tk, smp->enc_key_size,
			  rp->eभाग, rp->अक्रम);
	smp->ltk = ltk;
	अगर (!(smp->remote_key_dist & KEY_DIST_MASK))
		smp_distribute_keys(smp);

	वापस 0;
पूर्ण

अटल पूर्णांक smp_cmd_ident_info(काष्ठा l2cap_conn *conn, काष्ठा sk_buff *skb)
अणु
	काष्ठा smp_cmd_ident_info *info = (व्योम *) skb->data;
	काष्ठा l2cap_chan *chan = conn->smp;
	काष्ठा smp_chan *smp = chan->data;

	bt_dev_dbg(conn->hcon->hdev, "");

	अगर (skb->len < माप(*info))
		वापस SMP_INVALID_PARAMS;

	/* Pairing is पातed अगर any blocked keys are distributed */
	अगर (hci_is_blocked_key(conn->hcon->hdev, HCI_BLOCKED_KEY_TYPE_IRK,
			       info->irk)) अणु
		bt_dev_warn_ratelimited(conn->hcon->hdev,
					"Identity key blocked for %pMR",
					&conn->hcon->dst);
		वापस SMP_INVALID_PARAMS;
	पूर्ण

	SMP_ALLOW_CMD(smp, SMP_CMD_IDENT_ADDR_INFO);

	skb_pull(skb, माप(*info));

	स_नकल(smp->irk, info->irk, 16);

	वापस 0;
पूर्ण

अटल पूर्णांक smp_cmd_ident_addr_info(काष्ठा l2cap_conn *conn,
				   काष्ठा sk_buff *skb)
अणु
	काष्ठा smp_cmd_ident_addr_info *info = (व्योम *) skb->data;
	काष्ठा l2cap_chan *chan = conn->smp;
	काष्ठा smp_chan *smp = chan->data;
	काष्ठा hci_conn *hcon = conn->hcon;
	bdaddr_t rpa;

	bt_dev_dbg(hcon->hdev, "");

	अगर (skb->len < माप(*info))
		वापस SMP_INVALID_PARAMS;

	/* Mark the inक्रमmation as received */
	smp->remote_key_dist &= ~SMP_DIST_ID_KEY;

	अगर (smp->remote_key_dist & SMP_DIST_SIGN)
		SMP_ALLOW_CMD(smp, SMP_CMD_SIGN_INFO);

	skb_pull(skb, माप(*info));

	/* Strictly speaking the Core Specअगरication (4.1) allows sending
	 * an empty address which would क्रमce us to rely on just the IRK
	 * as "identity information". However, since such
	 * implementations are not known of and in order to not over
	 * complicate our implementation, simply pretend that we never
	 * received an IRK क्रम such a device.
	 *
	 * The Identity Address must also be a Static Ranकरोm or Public
	 * Address, which hci_is_identity_address() checks क्रम.
	 */
	अगर (!bacmp(&info->bdaddr, BDADDR_ANY) ||
	    !hci_is_identity_address(&info->bdaddr, info->addr_type)) अणु
		bt_dev_err(hcon->hdev, "ignoring IRK with no identity address");
		जाओ distribute;
	पूर्ण

	/* Drop IRK अगर peer is using identity address during pairing but is
	 * providing dअगरferent address as identity inक्रमmation.
	 *
	 * Microsoft Surface Precision Mouse is known to have this bug.
	 */
	अगर (hci_is_identity_address(&hcon->dst, hcon->dst_type) &&
	    (bacmp(&info->bdaddr, &hcon->dst) ||
	     info->addr_type != hcon->dst_type)) अणु
		bt_dev_err(hcon->hdev,
			   "ignoring IRK with invalid identity address");
		जाओ distribute;
	पूर्ण

	bacpy(&smp->id_addr, &info->bdaddr);
	smp->id_addr_type = info->addr_type;

	अगर (hci_bdaddr_is_rpa(&hcon->dst, hcon->dst_type))
		bacpy(&rpa, &hcon->dst);
	अन्यथा
		bacpy(&rpa, BDADDR_ANY);

	smp->remote_irk = hci_add_irk(conn->hcon->hdev, &smp->id_addr,
				      smp->id_addr_type, smp->irk, &rpa);

distribute:
	अगर (!(smp->remote_key_dist & KEY_DIST_MASK))
		smp_distribute_keys(smp);

	वापस 0;
पूर्ण

अटल पूर्णांक smp_cmd_sign_info(काष्ठा l2cap_conn *conn, काष्ठा sk_buff *skb)
अणु
	काष्ठा smp_cmd_sign_info *rp = (व्योम *) skb->data;
	काष्ठा l2cap_chan *chan = conn->smp;
	काष्ठा smp_chan *smp = chan->data;
	काष्ठा smp_csrk *csrk;

	bt_dev_dbg(conn->hcon->hdev, "conn %p", conn);

	अगर (skb->len < माप(*rp))
		वापस SMP_INVALID_PARAMS;

	/* Mark the inक्रमmation as received */
	smp->remote_key_dist &= ~SMP_DIST_SIGN;

	skb_pull(skb, माप(*rp));

	csrk = kzalloc(माप(*csrk), GFP_KERNEL);
	अगर (csrk) अणु
		अगर (conn->hcon->sec_level > BT_SECURITY_MEDIUM)
			csrk->type = MGMT_CSRK_REMOTE_AUTHENTICATED;
		अन्यथा
			csrk->type = MGMT_CSRK_REMOTE_UNAUTHENTICATED;
		स_नकल(csrk->val, rp->csrk, माप(csrk->val));
	पूर्ण
	smp->csrk = csrk;
	smp_distribute_keys(smp);

	वापस 0;
पूर्ण

अटल u8 sc_select_method(काष्ठा smp_chan *smp)
अणु
	काष्ठा l2cap_conn *conn = smp->conn;
	काष्ठा hci_conn *hcon = conn->hcon;
	काष्ठा smp_cmd_pairing *local, *remote;
	u8 local_miपंचांग, remote_miपंचांग, local_io, remote_io, method;

	अगर (test_bit(SMP_FLAG_REMOTE_OOB, &smp->flags) ||
	    test_bit(SMP_FLAG_LOCAL_OOB, &smp->flags))
		वापस REQ_OOB;

	/* The preq/prsp contain the raw Pairing Request/Response PDUs
	 * which are needed as inमाला_दो to some crypto functions. To get
	 * the "struct smp_cmd_pairing" from them we need to skip the
	 * first byte which contains the opcode.
	 */
	अगर (hcon->out) अणु
		local = (व्योम *) &smp->preq[1];
		remote = (व्योम *) &smp->prsp[1];
	पूर्ण अन्यथा अणु
		local = (व्योम *) &smp->prsp[1];
		remote = (व्योम *) &smp->preq[1];
	पूर्ण

	local_io = local->io_capability;
	remote_io = remote->io_capability;

	local_miपंचांग = (local->auth_req & SMP_AUTH_MITM);
	remote_miपंचांग = (remote->auth_req & SMP_AUTH_MITM);

	/* If either side wants MITM, look up the method from the table,
	 * otherwise use JUST WORKS.
	 */
	अगर (local_miपंचांग || remote_miपंचांग)
		method = get_auth_method(smp, local_io, remote_io);
	अन्यथा
		method = JUST_WORKS;

	/* Don't confirm locally initiated pairing attempts */
	अगर (method == JUST_CFM && test_bit(SMP_FLAG_INITIATOR, &smp->flags))
		method = JUST_WORKS;

	वापस method;
पूर्ण

अटल पूर्णांक smp_cmd_खुला_key(काष्ठा l2cap_conn *conn, काष्ठा sk_buff *skb)
अणु
	काष्ठा smp_cmd_खुला_key *key = (व्योम *) skb->data;
	काष्ठा hci_conn *hcon = conn->hcon;
	काष्ठा l2cap_chan *chan = conn->smp;
	काष्ठा smp_chan *smp = chan->data;
	काष्ठा hci_dev *hdev = hcon->hdev;
	काष्ठा crypto_kpp *tfm_ecdh;
	काष्ठा smp_cmd_pairing_confirm cfm;
	पूर्णांक err;

	bt_dev_dbg(hdev, "conn %p", conn);

	अगर (skb->len < माप(*key))
		वापस SMP_INVALID_PARAMS;

	/* Check अगर remote and local खुला keys are the same and debug key is
	 * not in use.
	 */
	अगर (!test_bit(SMP_FLAG_DEBUG_KEY, &smp->flags) &&
	    !crypto_memneq(key, smp->local_pk, 64)) अणु
		bt_dev_err(hdev, "Remote and local public keys are identical");
		वापस SMP_UNSPECIFIED;
	पूर्ण

	स_नकल(smp->remote_pk, key, 64);

	अगर (test_bit(SMP_FLAG_REMOTE_OOB, &smp->flags)) अणु
		err = smp_f4(smp->tfm_cmac, smp->remote_pk, smp->remote_pk,
			     smp->rr, 0, cfm.confirm_val);
		अगर (err)
			वापस SMP_UNSPECIFIED;

		अगर (crypto_memneq(cfm.confirm_val, smp->pcnf, 16))
			वापस SMP_CONFIRM_FAILED;
	पूर्ण

	/* Non-initiating device sends its खुला key after receiving
	 * the key from the initiating device.
	 */
	अगर (!hcon->out) अणु
		err = sc_send_खुला_key(smp);
		अगर (err)
			वापस err;
	पूर्ण

	SMP_DBG("Remote Public Key X: %32phN", smp->remote_pk);
	SMP_DBG("Remote Public Key Y: %32phN", smp->remote_pk + 32);

	/* Compute the shared secret on the same crypto tfm on which the निजी
	 * key was set/generated.
	 */
	अगर (test_bit(SMP_FLAG_LOCAL_OOB, &smp->flags)) अणु
		काष्ठा l2cap_chan *hchan = hdev->smp_data;
		काष्ठा smp_dev *smp_dev;

		अगर (!hchan || !hchan->data)
			वापस SMP_UNSPECIFIED;

		smp_dev = hchan->data;

		tfm_ecdh = smp_dev->tfm_ecdh;
	पूर्ण अन्यथा अणु
		tfm_ecdh = smp->tfm_ecdh;
	पूर्ण

	अगर (compute_ecdh_secret(tfm_ecdh, smp->remote_pk, smp->dhkey))
		वापस SMP_UNSPECIFIED;

	SMP_DBG("DHKey %32phN", smp->dhkey);

	set_bit(SMP_FLAG_REMOTE_PK, &smp->flags);

	smp->method = sc_select_method(smp);

	bt_dev_dbg(hdev, "selected method 0x%02x", smp->method);

	/* JUST_WORKS and JUST_CFM result in an unauthenticated key */
	अगर (smp->method == JUST_WORKS || smp->method == JUST_CFM)
		hcon->pending_sec_level = BT_SECURITY_MEDIUM;
	अन्यथा
		hcon->pending_sec_level = BT_SECURITY_FIPS;

	अगर (!crypto_memneq(debug_pk, smp->remote_pk, 64))
		set_bit(SMP_FLAG_DEBUG_KEY, &smp->flags);

	अगर (smp->method == DSP_PASSKEY) अणु
		get_अक्रमom_bytes(&hcon->passkey_notअगरy,
				 माप(hcon->passkey_notअगरy));
		hcon->passkey_notअगरy %= 1000000;
		hcon->passkey_entered = 0;
		smp->passkey_round = 0;
		अगर (mgmt_user_passkey_notअगरy(hdev, &hcon->dst, hcon->type,
					     hcon->dst_type,
					     hcon->passkey_notअगरy,
					     hcon->passkey_entered))
			वापस SMP_UNSPECIFIED;
		SMP_ALLOW_CMD(smp, SMP_CMD_PAIRING_CONFIRM);
		वापस sc_passkey_round(smp, SMP_CMD_PUBLIC_KEY);
	पूर्ण

	अगर (smp->method == REQ_OOB) अणु
		अगर (hcon->out)
			smp_send_cmd(conn, SMP_CMD_PAIRING_RANDOM,
				     माप(smp->prnd), smp->prnd);

		SMP_ALLOW_CMD(smp, SMP_CMD_PAIRING_RANDOM);

		वापस 0;
	पूर्ण

	अगर (hcon->out)
		SMP_ALLOW_CMD(smp, SMP_CMD_PAIRING_CONFIRM);

	अगर (smp->method == REQ_PASSKEY) अणु
		अगर (mgmt_user_passkey_request(hdev, &hcon->dst, hcon->type,
					      hcon->dst_type))
			वापस SMP_UNSPECIFIED;
		SMP_ALLOW_CMD(smp, SMP_CMD_PAIRING_CONFIRM);
		set_bit(SMP_FLAG_WAIT_USER, &smp->flags);
		वापस 0;
	पूर्ण

	/* The Initiating device रुकोs क्रम the non-initiating device to
	 * send the confirm value.
	 */
	अगर (conn->hcon->out)
		वापस 0;

	err = smp_f4(smp->tfm_cmac, smp->local_pk, smp->remote_pk, smp->prnd,
		     0, cfm.confirm_val);
	अगर (err)
		वापस SMP_UNSPECIFIED;

	smp_send_cmd(conn, SMP_CMD_PAIRING_CONFIRM, माप(cfm), &cfm);
	SMP_ALLOW_CMD(smp, SMP_CMD_PAIRING_RANDOM);

	वापस 0;
पूर्ण

अटल पूर्णांक smp_cmd_dhkey_check(काष्ठा l2cap_conn *conn, काष्ठा sk_buff *skb)
अणु
	काष्ठा smp_cmd_dhkey_check *check = (व्योम *) skb->data;
	काष्ठा l2cap_chan *chan = conn->smp;
	काष्ठा hci_conn *hcon = conn->hcon;
	काष्ठा smp_chan *smp = chan->data;
	u8 a[7], b[7], *local_addr, *remote_addr;
	u8 io_cap[3], r[16], e[16];
	पूर्णांक err;

	bt_dev_dbg(hcon->hdev, "conn %p", conn);

	अगर (skb->len < माप(*check))
		वापस SMP_INVALID_PARAMS;

	स_नकल(a, &hcon->init_addr, 6);
	स_नकल(b, &hcon->resp_addr, 6);
	a[6] = hcon->init_addr_type;
	b[6] = hcon->resp_addr_type;

	अगर (hcon->out) अणु
		local_addr = a;
		remote_addr = b;
		स_नकल(io_cap, &smp->prsp[1], 3);
	पूर्ण अन्यथा अणु
		local_addr = b;
		remote_addr = a;
		स_नकल(io_cap, &smp->preq[1], 3);
	पूर्ण

	स_रखो(r, 0, माप(r));

	अगर (smp->method == REQ_PASSKEY || smp->method == DSP_PASSKEY)
		put_unaligned_le32(hcon->passkey_notअगरy, r);
	अन्यथा अगर (smp->method == REQ_OOB)
		स_नकल(r, smp->lr, 16);

	err = smp_f6(smp->tfm_cmac, smp->mackey, smp->rrnd, smp->prnd, r,
		     io_cap, remote_addr, local_addr, e);
	अगर (err)
		वापस SMP_UNSPECIFIED;

	अगर (crypto_memneq(check->e, e, 16))
		वापस SMP_DHKEY_CHECK_FAILED;

	अगर (!hcon->out) अणु
		अगर (test_bit(SMP_FLAG_WAIT_USER, &smp->flags)) अणु
			set_bit(SMP_FLAG_DHKEY_PENDING, &smp->flags);
			वापस 0;
		पूर्ण

		/* Slave sends DHKey check as response to master */
		sc_dhkey_check(smp);
	पूर्ण

	sc_add_ltk(smp);

	अगर (hcon->out) अणु
		hci_le_start_enc(hcon, 0, 0, smp->tk, smp->enc_key_size);
		hcon->enc_key_size = smp->enc_key_size;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smp_cmd_keypress_notअगरy(काष्ठा l2cap_conn *conn,
				   काष्ठा sk_buff *skb)
अणु
	काष्ठा smp_cmd_keypress_notअगरy *kp = (व्योम *) skb->data;

	bt_dev_dbg(conn->hcon->hdev, "value 0x%02x", kp->value);

	वापस 0;
पूर्ण

अटल पूर्णांक smp_sig_channel(काष्ठा l2cap_chan *chan, काष्ठा sk_buff *skb)
अणु
	काष्ठा l2cap_conn *conn = chan->conn;
	काष्ठा hci_conn *hcon = conn->hcon;
	काष्ठा smp_chan *smp;
	__u8 code, reason;
	पूर्णांक err = 0;

	अगर (skb->len < 1)
		वापस -EILSEQ;

	अगर (!hci_dev_test_flag(hcon->hdev, HCI_LE_ENABLED)) अणु
		reason = SMP_PAIRING_NOTSUPP;
		जाओ करोne;
	पूर्ण

	code = skb->data[0];
	skb_pull(skb, माप(code));

	smp = chan->data;

	अगर (code > SMP_CMD_MAX)
		जाओ drop;

	अगर (smp && !test_and_clear_bit(code, &smp->allow_cmd))
		जाओ drop;

	/* If we करोn't have a context the only allowed commands are
	 * pairing request and security request.
	 */
	अगर (!smp && code != SMP_CMD_PAIRING_REQ && code != SMP_CMD_SECURITY_REQ)
		जाओ drop;

	चयन (code) अणु
	हाल SMP_CMD_PAIRING_REQ:
		reason = smp_cmd_pairing_req(conn, skb);
		अवरोध;

	हाल SMP_CMD_PAIRING_FAIL:
		smp_failure(conn, 0);
		err = -EPERM;
		अवरोध;

	हाल SMP_CMD_PAIRING_RSP:
		reason = smp_cmd_pairing_rsp(conn, skb);
		अवरोध;

	हाल SMP_CMD_SECURITY_REQ:
		reason = smp_cmd_security_req(conn, skb);
		अवरोध;

	हाल SMP_CMD_PAIRING_CONFIRM:
		reason = smp_cmd_pairing_confirm(conn, skb);
		अवरोध;

	हाल SMP_CMD_PAIRING_RANDOM:
		reason = smp_cmd_pairing_अक्रमom(conn, skb);
		अवरोध;

	हाल SMP_CMD_ENCRYPT_INFO:
		reason = smp_cmd_encrypt_info(conn, skb);
		अवरोध;

	हाल SMP_CMD_MASTER_IDENT:
		reason = smp_cmd_master_ident(conn, skb);
		अवरोध;

	हाल SMP_CMD_IDENT_INFO:
		reason = smp_cmd_ident_info(conn, skb);
		अवरोध;

	हाल SMP_CMD_IDENT_ADDR_INFO:
		reason = smp_cmd_ident_addr_info(conn, skb);
		अवरोध;

	हाल SMP_CMD_SIGN_INFO:
		reason = smp_cmd_sign_info(conn, skb);
		अवरोध;

	हाल SMP_CMD_PUBLIC_KEY:
		reason = smp_cmd_खुला_key(conn, skb);
		अवरोध;

	हाल SMP_CMD_DHKEY_CHECK:
		reason = smp_cmd_dhkey_check(conn, skb);
		अवरोध;

	हाल SMP_CMD_KEYPRESS_NOTIFY:
		reason = smp_cmd_keypress_notअगरy(conn, skb);
		अवरोध;

	शेष:
		bt_dev_dbg(hcon->hdev, "Unknown command code 0x%2.2x", code);
		reason = SMP_CMD_NOTSUPP;
		जाओ करोne;
	पूर्ण

करोne:
	अगर (!err) अणु
		अगर (reason)
			smp_failure(conn, reason);
		kमुक्त_skb(skb);
	पूर्ण

	वापस err;

drop:
	bt_dev_err(hcon->hdev, "unexpected SMP command 0x%02x from %pMR",
		   code, &hcon->dst);
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल व्योम smp_tearकरोwn_cb(काष्ठा l2cap_chan *chan, पूर्णांक err)
अणु
	काष्ठा l2cap_conn *conn = chan->conn;

	bt_dev_dbg(conn->hcon->hdev, "chan %p", chan);

	अगर (chan->data)
		smp_chan_destroy(conn);

	conn->smp = शून्य;
	l2cap_chan_put(chan);
पूर्ण

अटल व्योम bredr_pairing(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा l2cap_conn *conn = chan->conn;
	काष्ठा hci_conn *hcon = conn->hcon;
	काष्ठा hci_dev *hdev = hcon->hdev;
	काष्ठा smp_cmd_pairing req;
	काष्ठा smp_chan *smp;

	bt_dev_dbg(hdev, "chan %p", chan);

	/* Only new pairings are पूर्णांकeresting */
	अगर (!test_bit(HCI_CONN_NEW_LINK_KEY, &hcon->flags))
		वापस;

	/* Don't bother if we're not encrypted */
	अगर (!test_bit(HCI_CONN_ENCRYPT, &hcon->flags))
		वापस;

	/* Only master may initiate SMP over BR/EDR */
	अगर (hcon->role != HCI_ROLE_MASTER)
		वापस;

	/* Secure Connections support must be enabled */
	अगर (!hci_dev_test_flag(hdev, HCI_SC_ENABLED))
		वापस;

	/* BR/EDR must use Secure Connections क्रम SMP */
	अगर (!test_bit(HCI_CONN_AES_CCM, &hcon->flags) &&
	    !hci_dev_test_flag(hdev, HCI_FORCE_BREDR_SMP))
		वापस;

	/* If our LE support is not enabled करोn't करो anything */
	अगर (!hci_dev_test_flag(hdev, HCI_LE_ENABLED))
		वापस;

	/* Don't bother अगर remote LE support is not enabled */
	अगर (!lmp_host_le_capable(hcon))
		वापस;

	/* Remote must support SMP fixed chan क्रम BR/EDR */
	अगर (!(conn->remote_fixed_chan & L2CAP_FC_SMP_BREDR))
		वापस;

	/* Don't bother अगर SMP is alपढ़ोy ongoing */
	अगर (chan->data)
		वापस;

	smp = smp_chan_create(conn);
	अगर (!smp) अणु
		bt_dev_err(hdev, "unable to create SMP context for BR/EDR");
		वापस;
	पूर्ण

	set_bit(SMP_FLAG_SC, &smp->flags);

	bt_dev_dbg(hdev, "starting SMP over BR/EDR");

	/* Prepare and send the BR/EDR SMP Pairing Request */
	build_bredr_pairing_cmd(smp, &req, शून्य);

	smp->preq[0] = SMP_CMD_PAIRING_REQ;
	स_नकल(&smp->preq[1], &req, माप(req));

	smp_send_cmd(conn, SMP_CMD_PAIRING_REQ, माप(req), &req);
	SMP_ALLOW_CMD(smp, SMP_CMD_PAIRING_RSP);
पूर्ण

अटल व्योम smp_resume_cb(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा smp_chan *smp = chan->data;
	काष्ठा l2cap_conn *conn = chan->conn;
	काष्ठा hci_conn *hcon = conn->hcon;

	bt_dev_dbg(hcon->hdev, "chan %p", chan);

	अगर (hcon->type == ACL_LINK) अणु
		bredr_pairing(chan);
		वापस;
	पूर्ण

	अगर (!smp)
		वापस;

	अगर (!test_bit(HCI_CONN_ENCRYPT, &hcon->flags))
		वापस;

	cancel_delayed_work(&smp->security_समयr);

	smp_distribute_keys(smp);
पूर्ण

अटल व्योम smp_पढ़ोy_cb(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा l2cap_conn *conn = chan->conn;
	काष्ठा hci_conn *hcon = conn->hcon;

	bt_dev_dbg(hcon->hdev, "chan %p", chan);

	/* No need to call l2cap_chan_hold() here since we alपढ़ोy own
	 * the reference taken in smp_new_conn_cb(). This is just the
	 * first समय that we tie it to a specअगरic poपूर्णांकer. The code in
	 * l2cap_core.c ensures that there's no risk this function wont
	 * get called अगर smp_new_conn_cb was previously called.
	 */
	conn->smp = chan;

	अगर (hcon->type == ACL_LINK && test_bit(HCI_CONN_ENCRYPT, &hcon->flags))
		bredr_pairing(chan);
पूर्ण

अटल पूर्णांक smp_recv_cb(काष्ठा l2cap_chan *chan, काष्ठा sk_buff *skb)
अणु
	पूर्णांक err;

	bt_dev_dbg(chan->conn->hcon->hdev, "chan %p", chan);

	err = smp_sig_channel(chan, skb);
	अगर (err) अणु
		काष्ठा smp_chan *smp = chan->data;

		अगर (smp)
			cancel_delayed_work_sync(&smp->security_समयr);

		hci_disconnect(chan->conn->hcon, HCI_ERROR_AUTH_FAILURE);
	पूर्ण

	वापस err;
पूर्ण

अटल काष्ठा sk_buff *smp_alloc_skb_cb(काष्ठा l2cap_chan *chan,
					अचिन्हित दीर्घ hdr_len,
					अचिन्हित दीर्घ len, पूर्णांक nb)
अणु
	काष्ठा sk_buff *skb;

	skb = bt_skb_alloc(hdr_len + len, GFP_KERNEL);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	skb->priority = HCI_PRIO_MAX;
	bt_cb(skb)->l2cap.chan = chan;

	वापस skb;
पूर्ण

अटल स्थिर काष्ठा l2cap_ops smp_chan_ops = अणु
	.name			= "Security Manager",
	.पढ़ोy			= smp_पढ़ोy_cb,
	.recv			= smp_recv_cb,
	.alloc_skb		= smp_alloc_skb_cb,
	.tearकरोwn		= smp_tearकरोwn_cb,
	.resume			= smp_resume_cb,

	.new_connection		= l2cap_chan_no_new_connection,
	.state_change		= l2cap_chan_no_state_change,
	.बंद			= l2cap_chan_no_बंद,
	.defer			= l2cap_chan_no_defer,
	.suspend		= l2cap_chan_no_suspend,
	.set_shutकरोwn		= l2cap_chan_no_set_shutकरोwn,
	.get_sndसमयo		= l2cap_chan_no_get_sndसमयo,
पूर्ण;

अटल अंतरभूत काष्ठा l2cap_chan *smp_new_conn_cb(काष्ठा l2cap_chan *pchan)
अणु
	काष्ठा l2cap_chan *chan;

	BT_DBG("pchan %p", pchan);

	chan = l2cap_chan_create();
	अगर (!chan)
		वापस शून्य;

	chan->chan_type	= pchan->chan_type;
	chan->ops	= &smp_chan_ops;
	chan->scid	= pchan->scid;
	chan->dcid	= chan->scid;
	chan->imtu	= pchan->imtu;
	chan->omtu	= pchan->omtu;
	chan->mode	= pchan->mode;

	/* Other L2CAP channels may request SMP routines in order to
	 * change the security level. This means that the SMP channel
	 * lock must be considered in its own category to aव्योम lockdep
	 * warnings.
	 */
	atomic_set(&chan->nesting, L2CAP_NESTING_SMP);

	BT_DBG("created chan %p", chan);

	वापस chan;
पूर्ण

अटल स्थिर काष्ठा l2cap_ops smp_root_chan_ops = अणु
	.name			= "Security Manager Root",
	.new_connection		= smp_new_conn_cb,

	/* None of these are implemented क्रम the root channel */
	.बंद			= l2cap_chan_no_बंद,
	.alloc_skb		= l2cap_chan_no_alloc_skb,
	.recv			= l2cap_chan_no_recv,
	.state_change		= l2cap_chan_no_state_change,
	.tearकरोwn		= l2cap_chan_no_tearकरोwn,
	.पढ़ोy			= l2cap_chan_no_पढ़ोy,
	.defer			= l2cap_chan_no_defer,
	.suspend		= l2cap_chan_no_suspend,
	.resume			= l2cap_chan_no_resume,
	.set_shutकरोwn		= l2cap_chan_no_set_shutकरोwn,
	.get_sndसमयo		= l2cap_chan_no_get_sndसमयo,
पूर्ण;

अटल काष्ठा l2cap_chan *smp_add_cid(काष्ठा hci_dev *hdev, u16 cid)
अणु
	काष्ठा l2cap_chan *chan;
	काष्ठा smp_dev *smp;
	काष्ठा crypto_shash *tfm_cmac;
	काष्ठा crypto_kpp *tfm_ecdh;

	अगर (cid == L2CAP_CID_SMP_BREDR) अणु
		smp = शून्य;
		जाओ create_chan;
	पूर्ण

	smp = kzalloc(माप(*smp), GFP_KERNEL);
	अगर (!smp)
		वापस ERR_PTR(-ENOMEM);

	tfm_cmac = crypto_alloc_shash("cmac(aes)", 0, 0);
	अगर (IS_ERR(tfm_cmac)) अणु
		bt_dev_err(hdev, "Unable to create CMAC crypto context");
		kमुक्त_sensitive(smp);
		वापस ERR_CAST(tfm_cmac);
	पूर्ण

	tfm_ecdh = crypto_alloc_kpp("ecdh-nist-p256", 0, 0);
	अगर (IS_ERR(tfm_ecdh)) अणु
		bt_dev_err(hdev, "Unable to create ECDH crypto context");
		crypto_मुक्त_shash(tfm_cmac);
		kमुक्त_sensitive(smp);
		वापस ERR_CAST(tfm_ecdh);
	पूर्ण

	smp->local_oob = false;
	smp->tfm_cmac = tfm_cmac;
	smp->tfm_ecdh = tfm_ecdh;

create_chan:
	chan = l2cap_chan_create();
	अगर (!chan) अणु
		अगर (smp) अणु
			crypto_मुक्त_shash(smp->tfm_cmac);
			crypto_मुक्त_kpp(smp->tfm_ecdh);
			kमुक्त_sensitive(smp);
		पूर्ण
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	chan->data = smp;

	l2cap_add_scid(chan, cid);

	l2cap_chan_set_शेषs(chan);

	अगर (cid == L2CAP_CID_SMP) अणु
		u8 bdaddr_type;

		hci_copy_identity_address(hdev, &chan->src, &bdaddr_type);

		अगर (bdaddr_type == ADDR_LE_DEV_PUBLIC)
			chan->src_type = BDADDR_LE_PUBLIC;
		अन्यथा
			chan->src_type = BDADDR_LE_RANDOM;
	पूर्ण अन्यथा अणु
		bacpy(&chan->src, &hdev->bdaddr);
		chan->src_type = BDADDR_BREDR;
	पूर्ण

	chan->state = BT_LISTEN;
	chan->mode = L2CAP_MODE_BASIC;
	chan->imtu = L2CAP_DEFAULT_MTU;
	chan->ops = &smp_root_chan_ops;

	/* Set correct nesting level क्रम a parent/listening channel */
	atomic_set(&chan->nesting, L2CAP_NESTING_PARENT);

	वापस chan;
पूर्ण

अटल व्योम smp_del_chan(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा smp_dev *smp;

	BT_DBG("chan %p", chan);

	smp = chan->data;
	अगर (smp) अणु
		chan->data = शून्य;
		crypto_मुक्त_shash(smp->tfm_cmac);
		crypto_मुक्त_kpp(smp->tfm_ecdh);
		kमुक्त_sensitive(smp);
	पूर्ण

	l2cap_chan_put(chan);
पूर्ण

पूर्णांक smp_क्रमce_bredr(काष्ठा hci_dev *hdev, bool enable)
अणु
	अगर (enable == hci_dev_test_flag(hdev, HCI_FORCE_BREDR_SMP))
		वापस -EALREADY;

	अगर (enable) अणु
		काष्ठा l2cap_chan *chan;

		chan = smp_add_cid(hdev, L2CAP_CID_SMP_BREDR);
		अगर (IS_ERR(chan))
			वापस PTR_ERR(chan);

		hdev->smp_bredr_data = chan;
	पूर्ण अन्यथा अणु
		काष्ठा l2cap_chan *chan;

		chan = hdev->smp_bredr_data;
		hdev->smp_bredr_data = शून्य;
		smp_del_chan(chan);
	पूर्ण

	hci_dev_change_flag(hdev, HCI_FORCE_BREDR_SMP);

	वापस 0;
पूर्ण

पूर्णांक smp_रेजिस्टर(काष्ठा hci_dev *hdev)
अणु
	काष्ठा l2cap_chan *chan;

	bt_dev_dbg(hdev, "");

	/* If the controller करोes not support Low Energy operation, then
	 * there is also no need to रेजिस्टर any SMP channel.
	 */
	अगर (!lmp_le_capable(hdev))
		वापस 0;

	अगर (WARN_ON(hdev->smp_data)) अणु
		chan = hdev->smp_data;
		hdev->smp_data = शून्य;
		smp_del_chan(chan);
	पूर्ण

	chan = smp_add_cid(hdev, L2CAP_CID_SMP);
	अगर (IS_ERR(chan))
		वापस PTR_ERR(chan);

	hdev->smp_data = chan;

	अगर (!lmp_sc_capable(hdev)) अणु
		/* Flag can be alपढ़ोy set here (due to घातer toggle) */
		अगर (!hci_dev_test_flag(hdev, HCI_FORCE_BREDR_SMP))
			वापस 0;
	पूर्ण

	अगर (WARN_ON(hdev->smp_bredr_data)) अणु
		chan = hdev->smp_bredr_data;
		hdev->smp_bredr_data = शून्य;
		smp_del_chan(chan);
	पूर्ण

	chan = smp_add_cid(hdev, L2CAP_CID_SMP_BREDR);
	अगर (IS_ERR(chan)) अणु
		पूर्णांक err = PTR_ERR(chan);
		chan = hdev->smp_data;
		hdev->smp_data = शून्य;
		smp_del_chan(chan);
		वापस err;
	पूर्ण

	hdev->smp_bredr_data = chan;

	वापस 0;
पूर्ण

व्योम smp_unरेजिस्टर(काष्ठा hci_dev *hdev)
अणु
	काष्ठा l2cap_chan *chan;

	अगर (hdev->smp_bredr_data) अणु
		chan = hdev->smp_bredr_data;
		hdev->smp_bredr_data = शून्य;
		smp_del_chan(chan);
	पूर्ण

	अगर (hdev->smp_data) अणु
		chan = hdev->smp_data;
		hdev->smp_data = शून्य;
		smp_del_chan(chan);
	पूर्ण
पूर्ण

#अगर IS_ENABLED(CONFIG_BT_SELFTEST_SMP)

अटल पूर्णांक __init test_debug_key(काष्ठा crypto_kpp *tfm_ecdh)
अणु
	u8 pk[64];
	पूर्णांक err;

	err = set_ecdh_privkey(tfm_ecdh, debug_sk);
	अगर (err)
		वापस err;

	err = generate_ecdh_खुला_key(tfm_ecdh, pk);
	अगर (err)
		वापस err;

	अगर (crypto_memneq(pk, debug_pk, 64))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक __init test_ah(व्योम)
अणु
	स्थिर u8 irk[16] = अणु
			0x9b, 0x7d, 0x39, 0x0a, 0xa6, 0x10, 0x10, 0x34,
			0x05, 0xad, 0xc8, 0x57, 0xa3, 0x34, 0x02, 0xec पूर्ण;
	स्थिर u8 r[3] = अणु 0x94, 0x81, 0x70 पूर्ण;
	स्थिर u8 exp[3] = अणु 0xaa, 0xfb, 0x0d पूर्ण;
	u8 res[3];
	पूर्णांक err;

	err = smp_ah(irk, r, res);
	अगर (err)
		वापस err;

	अगर (crypto_memneq(res, exp, 3))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक __init test_c1(व्योम)
अणु
	स्थिर u8 k[16] = अणु
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 पूर्ण;
	स्थिर u8 r[16] = अणु
			0xe0, 0x2e, 0x70, 0xc6, 0x4e, 0x27, 0x88, 0x63,
			0x0e, 0x6f, 0xad, 0x56, 0x21, 0xd5, 0x83, 0x57 पूर्ण;
	स्थिर u8 preq[7] = अणु 0x01, 0x01, 0x00, 0x00, 0x10, 0x07, 0x07 पूर्ण;
	स्थिर u8 pres[7] = अणु 0x02, 0x03, 0x00, 0x00, 0x08, 0x00, 0x05 पूर्ण;
	स्थिर u8 _iat = 0x01;
	स्थिर u8 _rat = 0x00;
	स्थिर bdaddr_t ra = अणु अणु 0xb6, 0xb5, 0xb4, 0xb3, 0xb2, 0xb1 पूर्ण पूर्ण;
	स्थिर bdaddr_t ia = अणु अणु 0xa6, 0xa5, 0xa4, 0xa3, 0xa2, 0xa1 पूर्ण पूर्ण;
	स्थिर u8 exp[16] = अणु
			0x86, 0x3b, 0xf1, 0xbe, 0xc5, 0x4d, 0xa7, 0xd2,
			0xea, 0x88, 0x89, 0x87, 0xef, 0x3f, 0x1e, 0x1e पूर्ण;
	u8 res[16];
	पूर्णांक err;

	err = smp_c1(k, r, preq, pres, _iat, &ia, _rat, &ra, res);
	अगर (err)
		वापस err;

	अगर (crypto_memneq(res, exp, 16))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक __init test_s1(व्योम)
अणु
	स्थिर u8 k[16] = अणु
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 पूर्ण;
	स्थिर u8 r1[16] = अणु
			0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11 पूर्ण;
	स्थिर u8 r2[16] = अणु
			0x00, 0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99 पूर्ण;
	स्थिर u8 exp[16] = अणु
			0x62, 0xa0, 0x6d, 0x79, 0xae, 0x16, 0x42, 0x5b,
			0x9b, 0xf4, 0xb0, 0xe8, 0xf0, 0xe1, 0x1f, 0x9a पूर्ण;
	u8 res[16];
	पूर्णांक err;

	err = smp_s1(k, r1, r2, res);
	अगर (err)
		वापस err;

	अगर (crypto_memneq(res, exp, 16))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक __init test_f4(काष्ठा crypto_shash *tfm_cmac)
अणु
	स्थिर u8 u[32] = अणु
			0xe6, 0x9d, 0x35, 0x0e, 0x48, 0x01, 0x03, 0xcc,
			0xdb, 0xfd, 0xf4, 0xac, 0x11, 0x91, 0xf4, 0xef,
			0xb9, 0xa5, 0xf9, 0xe9, 0xa7, 0x83, 0x2c, 0x5e,
			0x2c, 0xbe, 0x97, 0xf2, 0xd2, 0x03, 0xb0, 0x20 पूर्ण;
	स्थिर u8 v[32] = अणु
			0xfd, 0xc5, 0x7f, 0xf4, 0x49, 0xdd, 0x4f, 0x6b,
			0xfb, 0x7c, 0x9d, 0xf1, 0xc2, 0x9a, 0xcb, 0x59,
			0x2a, 0xe7, 0xd4, 0xee, 0xfb, 0xfc, 0x0a, 0x90,
			0x9a, 0xbb, 0xf6, 0x32, 0x3d, 0x8b, 0x18, 0x55 पूर्ण;
	स्थिर u8 x[16] = अणु
			0xab, 0xae, 0x2b, 0x71, 0xec, 0xb2, 0xff, 0xff,
			0x3e, 0x73, 0x77, 0xd1, 0x54, 0x84, 0xcb, 0xd5 पूर्ण;
	स्थिर u8 z = 0x00;
	स्थिर u8 exp[16] = अणु
			0x2d, 0x87, 0x74, 0xa9, 0xbe, 0xa1, 0xed, 0xf1,
			0x1c, 0xbd, 0xa9, 0x07, 0xf1, 0x16, 0xc9, 0xf2 पूर्ण;
	u8 res[16];
	पूर्णांक err;

	err = smp_f4(tfm_cmac, u, v, x, z, res);
	अगर (err)
		वापस err;

	अगर (crypto_memneq(res, exp, 16))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक __init test_f5(काष्ठा crypto_shash *tfm_cmac)
अणु
	स्थिर u8 w[32] = अणु
			0x98, 0xa6, 0xbf, 0x73, 0xf3, 0x34, 0x8d, 0x86,
			0xf1, 0x66, 0xf8, 0xb4, 0x13, 0x6b, 0x79, 0x99,
			0x9b, 0x7d, 0x39, 0x0a, 0xa6, 0x10, 0x10, 0x34,
			0x05, 0xad, 0xc8, 0x57, 0xa3, 0x34, 0x02, 0xec पूर्ण;
	स्थिर u8 n1[16] = अणु
			0xab, 0xae, 0x2b, 0x71, 0xec, 0xb2, 0xff, 0xff,
			0x3e, 0x73, 0x77, 0xd1, 0x54, 0x84, 0xcb, 0xd5 पूर्ण;
	स्थिर u8 n2[16] = अणु
			0xcf, 0xc4, 0x3d, 0xff, 0xf7, 0x83, 0x65, 0x21,
			0x6e, 0x5f, 0xa7, 0x25, 0xcc, 0xe7, 0xe8, 0xa6 पूर्ण;
	स्थिर u8 a1[7] = अणु 0xce, 0xbf, 0x37, 0x37, 0x12, 0x56, 0x00 पूर्ण;
	स्थिर u8 a2[7] = अणु 0xc1, 0xcf, 0x2d, 0x70, 0x13, 0xa7, 0x00 पूर्ण;
	स्थिर u8 exp_ltk[16] = अणु
			0x38, 0x0a, 0x75, 0x94, 0xb5, 0x22, 0x05, 0x98,
			0x23, 0xcd, 0xd7, 0x69, 0x11, 0x79, 0x86, 0x69 पूर्ण;
	स्थिर u8 exp_mackey[16] = अणु
			0x20, 0x6e, 0x63, 0xce, 0x20, 0x6a, 0x3f, 0xfd,
			0x02, 0x4a, 0x08, 0xa1, 0x76, 0xf1, 0x65, 0x29 पूर्ण;
	u8 mackey[16], ltk[16];
	पूर्णांक err;

	err = smp_f5(tfm_cmac, w, n1, n2, a1, a2, mackey, ltk);
	अगर (err)
		वापस err;

	अगर (crypto_memneq(mackey, exp_mackey, 16))
		वापस -EINVAL;

	अगर (crypto_memneq(ltk, exp_ltk, 16))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक __init test_f6(काष्ठा crypto_shash *tfm_cmac)
अणु
	स्थिर u8 w[16] = अणु
			0x20, 0x6e, 0x63, 0xce, 0x20, 0x6a, 0x3f, 0xfd,
			0x02, 0x4a, 0x08, 0xa1, 0x76, 0xf1, 0x65, 0x29 पूर्ण;
	स्थिर u8 n1[16] = अणु
			0xab, 0xae, 0x2b, 0x71, 0xec, 0xb2, 0xff, 0xff,
			0x3e, 0x73, 0x77, 0xd1, 0x54, 0x84, 0xcb, 0xd5 पूर्ण;
	स्थिर u8 n2[16] = अणु
			0xcf, 0xc4, 0x3d, 0xff, 0xf7, 0x83, 0x65, 0x21,
			0x6e, 0x5f, 0xa7, 0x25, 0xcc, 0xe7, 0xe8, 0xa6 पूर्ण;
	स्थिर u8 r[16] = अणु
			0xc8, 0x0f, 0x2d, 0x0c, 0xd2, 0x42, 0xda, 0x08,
			0x54, 0xbb, 0x53, 0xb4, 0x3b, 0x34, 0xa3, 0x12 पूर्ण;
	स्थिर u8 io_cap[3] = अणु 0x02, 0x01, 0x01 पूर्ण;
	स्थिर u8 a1[7] = अणु 0xce, 0xbf, 0x37, 0x37, 0x12, 0x56, 0x00 पूर्ण;
	स्थिर u8 a2[7] = अणु 0xc1, 0xcf, 0x2d, 0x70, 0x13, 0xa7, 0x00 पूर्ण;
	स्थिर u8 exp[16] = अणु
			0x61, 0x8f, 0x95, 0xda, 0x09, 0x0b, 0x6c, 0xd2,
			0xc5, 0xe8, 0xd0, 0x9c, 0x98, 0x73, 0xc4, 0xe3 पूर्ण;
	u8 res[16];
	पूर्णांक err;

	err = smp_f6(tfm_cmac, w, n1, n2, r, io_cap, a1, a2, res);
	अगर (err)
		वापस err;

	अगर (crypto_memneq(res, exp, 16))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक __init test_g2(काष्ठा crypto_shash *tfm_cmac)
अणु
	स्थिर u8 u[32] = अणु
			0xe6, 0x9d, 0x35, 0x0e, 0x48, 0x01, 0x03, 0xcc,
			0xdb, 0xfd, 0xf4, 0xac, 0x11, 0x91, 0xf4, 0xef,
			0xb9, 0xa5, 0xf9, 0xe9, 0xa7, 0x83, 0x2c, 0x5e,
			0x2c, 0xbe, 0x97, 0xf2, 0xd2, 0x03, 0xb0, 0x20 पूर्ण;
	स्थिर u8 v[32] = अणु
			0xfd, 0xc5, 0x7f, 0xf4, 0x49, 0xdd, 0x4f, 0x6b,
			0xfb, 0x7c, 0x9d, 0xf1, 0xc2, 0x9a, 0xcb, 0x59,
			0x2a, 0xe7, 0xd4, 0xee, 0xfb, 0xfc, 0x0a, 0x90,
			0x9a, 0xbb, 0xf6, 0x32, 0x3d, 0x8b, 0x18, 0x55 पूर्ण;
	स्थिर u8 x[16] = अणु
			0xab, 0xae, 0x2b, 0x71, 0xec, 0xb2, 0xff, 0xff,
			0x3e, 0x73, 0x77, 0xd1, 0x54, 0x84, 0xcb, 0xd5 पूर्ण;
	स्थिर u8 y[16] = अणु
			0xcf, 0xc4, 0x3d, 0xff, 0xf7, 0x83, 0x65, 0x21,
			0x6e, 0x5f, 0xa7, 0x25, 0xcc, 0xe7, 0xe8, 0xa6 पूर्ण;
	स्थिर u32 exp_val = 0x2f9ed5ba % 1000000;
	u32 val;
	पूर्णांक err;

	err = smp_g2(tfm_cmac, u, v, x, y, &val);
	अगर (err)
		वापस err;

	अगर (val != exp_val)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक __init test_h6(काष्ठा crypto_shash *tfm_cmac)
अणु
	स्थिर u8 w[16] = अणु
			0x9b, 0x7d, 0x39, 0x0a, 0xa6, 0x10, 0x10, 0x34,
			0x05, 0xad, 0xc8, 0x57, 0xa3, 0x34, 0x02, 0xec पूर्ण;
	स्थिर u8 key_id[4] = अणु 0x72, 0x62, 0x65, 0x6c पूर्ण;
	स्थिर u8 exp[16] = अणु
			0x99, 0x63, 0xb1, 0x80, 0xe2, 0xa9, 0xd3, 0xe8,
			0x1c, 0xc9, 0x6d, 0xe7, 0x02, 0xe1, 0x9a, 0x2d पूर्ण;
	u8 res[16];
	पूर्णांक err;

	err = smp_h6(tfm_cmac, w, key_id, res);
	अगर (err)
		वापस err;

	अगर (crypto_memneq(res, exp, 16))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल अक्षर test_smp_buffer[32];

अटल sमाप_प्रकार test_smp_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
			     माप_प्रकार count, loff_t *ppos)
अणु
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, test_smp_buffer,
				       म_माप(test_smp_buffer));
पूर्ण

अटल स्थिर काष्ठा file_operations test_smp_fops = अणु
	.खोलो		= simple_खोलो,
	.पढ़ो		= test_smp_पढ़ो,
	.llseek		= शेष_llseek,
पूर्ण;

अटल पूर्णांक __init run_selftests(काष्ठा crypto_shash *tfm_cmac,
				काष्ठा crypto_kpp *tfm_ecdh)
अणु
	kसमय_प्रकार callसमय, delta, retसमय;
	अचिन्हित दीर्घ दीर्घ duration;
	पूर्णांक err;

	callसमय = kसमय_get();

	err = test_debug_key(tfm_ecdh);
	अगर (err) अणु
		BT_ERR("debug_key test failed");
		जाओ करोne;
	पूर्ण

	err = test_ah();
	अगर (err) अणु
		BT_ERR("smp_ah test failed");
		जाओ करोne;
	पूर्ण

	err = test_c1();
	अगर (err) अणु
		BT_ERR("smp_c1 test failed");
		जाओ करोne;
	पूर्ण

	err = test_s1();
	अगर (err) अणु
		BT_ERR("smp_s1 test failed");
		जाओ करोne;
	पूर्ण

	err = test_f4(tfm_cmac);
	अगर (err) अणु
		BT_ERR("smp_f4 test failed");
		जाओ करोne;
	पूर्ण

	err = test_f5(tfm_cmac);
	अगर (err) अणु
		BT_ERR("smp_f5 test failed");
		जाओ करोne;
	पूर्ण

	err = test_f6(tfm_cmac);
	अगर (err) अणु
		BT_ERR("smp_f6 test failed");
		जाओ करोne;
	पूर्ण

	err = test_g2(tfm_cmac);
	अगर (err) अणु
		BT_ERR("smp_g2 test failed");
		जाओ करोne;
	पूर्ण

	err = test_h6(tfm_cmac);
	अगर (err) अणु
		BT_ERR("smp_h6 test failed");
		जाओ करोne;
	पूर्ण

	retसमय = kसमय_get();
	delta = kसमय_sub(retसमय, callसमय);
	duration = (अचिन्हित दीर्घ दीर्घ) kसमय_प्रकारo_ns(delta) >> 10;

	BT_INFO("SMP test passed in %llu usecs", duration);

करोne:
	अगर (!err)
		snम_लिखो(test_smp_buffer, माप(test_smp_buffer),
			 "PASS (%llu usecs)\n", duration);
	अन्यथा
		snम_लिखो(test_smp_buffer, माप(test_smp_buffer), "FAIL\n");

	debugfs_create_file("selftest_smp", 0444, bt_debugfs, शून्य,
			    &test_smp_fops);

	वापस err;
पूर्ण

पूर्णांक __init bt_selftest_smp(व्योम)
अणु
	काष्ठा crypto_shash *tfm_cmac;
	काष्ठा crypto_kpp *tfm_ecdh;
	पूर्णांक err;

	tfm_cmac = crypto_alloc_shash("cmac(aes)", 0, 0);
	अगर (IS_ERR(tfm_cmac)) अणु
		BT_ERR("Unable to create CMAC crypto context");
		वापस PTR_ERR(tfm_cmac);
	पूर्ण

	tfm_ecdh = crypto_alloc_kpp("ecdh-nist-p256", 0, 0);
	अगर (IS_ERR(tfm_ecdh)) अणु
		BT_ERR("Unable to create ECDH crypto context");
		crypto_मुक्त_shash(tfm_cmac);
		वापस PTR_ERR(tfm_ecdh);
	पूर्ण

	err = run_selftests(tfm_cmac, tfm_ecdh);

	crypto_मुक्त_shash(tfm_cmac);
	crypto_मुक्त_kpp(tfm_ecdh);

	वापस err;
पूर्ण

#पूर्ण_अगर
