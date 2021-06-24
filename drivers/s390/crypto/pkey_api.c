<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  pkey device driver
 *
 *  Copyright IBM Corp. 2017,2019
 *  Author(s): Harald Freudenberger
 */

#घोषणा KMSG_COMPONENT "pkey"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/cpufeature.h>
#समावेश <यंत्र/zcrypt.h>
#समावेश <यंत्र/cpacf.h>
#समावेश <यंत्र/pkey.h>
#समावेश <crypto/aes.h>

#समावेश "zcrypt_api.h"
#समावेश "zcrypt_ccamisc.h"
#समावेश "zcrypt_ep11misc.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("IBM Corporation");
MODULE_DESCRIPTION("s390 protected key interface");

#घोषणा KEYBLOBबफ_मानE 8192	/* key buffer size used क्रम पूर्णांकernal processing */
#घोषणा PROTKEYBLOBबफ_मानE 256	/* रक्षित key buffer size used पूर्णांकernal */
#घोषणा MAXAPQNSINLIST 64	/* max 64 apqns within a apqn list */

/*
 * debug feature data and functions
 */

अटल debug_info_t *debug_info;

#घोषणा DEBUG_DBG(...)	debug_प्र_लिखो_event(debug_info, 6, ##__VA_ARGS__)
#घोषणा DEBUG_INFO(...) debug_प्र_लिखो_event(debug_info, 5, ##__VA_ARGS__)
#घोषणा DEBUG_WARN(...) debug_प्र_लिखो_event(debug_info, 4, ##__VA_ARGS__)
#घोषणा DEBUG_ERR(...)	debug_प्र_लिखो_event(debug_info, 3, ##__VA_ARGS__)

अटल व्योम __init pkey_debug_init(व्योम)
अणु
	/* 5 arguments per dbf entry (including the क्रमmat string ptr) */
	debug_info = debug_रेजिस्टर("pkey", 1, 1, 5 * माप(दीर्घ));
	debug_रेजिस्टर_view(debug_info, &debug_प्र_लिखो_view);
	debug_set_level(debug_info, 3);
पूर्ण

अटल व्योम __निकास pkey_debug_निकास(व्योम)
अणु
	debug_unरेजिस्टर(debug_info);
पूर्ण

/* inside view of a रक्षित key token (only type 0x00 version 0x01) */
काष्ठा protaeskeytoken अणु
	u8  type;     /* 0x00 क्रम PAES specअगरic key tokens */
	u8  res0[3];
	u8  version;  /* should be 0x01 क्रम रक्षित AES key token */
	u8  res1[3];
	u32 keytype;  /* key type, one of the PKEY_KEYTYPE values */
	u32 len;      /* bytes actually stored in protkey[] */
	u8  protkey[MAXPROTKEYSIZE]; /* the रक्षित key blob */
पूर्ण __packed;

/* inside view of a clear key token (type 0x00 version 0x02) */
काष्ठा clearaeskeytoken अणु
	u8  type;	 /* 0x00 क्रम PAES specअगरic key tokens */
	u8  res0[3];
	u8  version;	 /* 0x02 क्रम clear AES key token */
	u8  res1[3];
	u32 keytype;	 /* key type, one of the PKEY_KEYTYPE values */
	u32 len;	 /* bytes actually stored in clearkey[] */
	u8  clearkey[]; /* clear key value */
पूर्ण __packed;

/*
 * Create a रक्षित key from a clear key value.
 */
अटल पूर्णांक pkey_clr2protkey(u32 keytype,
			    स्थिर काष्ठा pkey_clrkey *clrkey,
			    काष्ठा pkey_protkey *protkey)
अणु
	/* mask of available pckmo subfunctions */
	अटल cpacf_mask_t pckmo_functions;

	दीर्घ fc;
	पूर्णांक keysize;
	u8 paramblock[64];

	चयन (keytype) अणु
	हाल PKEY_KEYTYPE_AES_128:
		keysize = 16;
		fc = CPACF_PCKMO_ENC_AES_128_KEY;
		अवरोध;
	हाल PKEY_KEYTYPE_AES_192:
		keysize = 24;
		fc = CPACF_PCKMO_ENC_AES_192_KEY;
		अवरोध;
	हाल PKEY_KEYTYPE_AES_256:
		keysize = 32;
		fc = CPACF_PCKMO_ENC_AES_256_KEY;
		अवरोध;
	शेष:
		DEBUG_ERR("%s unknown/unsupported keytype %d\n",
			  __func__, keytype);
		वापस -EINVAL;
	पूर्ण

	/* Did we alपढ़ोy check क्रम PCKMO ? */
	अगर (!pckmo_functions.bytes[0]) अणु
		/* no, so check now */
		अगर (!cpacf_query(CPACF_PCKMO, &pckmo_functions))
			वापस -ENODEV;
	पूर्ण
	/* check क्रम the pckmo subfunction we need now */
	अगर (!cpacf_test_func(&pckmo_functions, fc)) अणु
		DEBUG_ERR("%s pckmo functions not available\n", __func__);
		वापस -ENODEV;
	पूर्ण

	/* prepare param block */
	स_रखो(paramblock, 0, माप(paramblock));
	स_नकल(paramblock, clrkey->clrkey, keysize);

	/* call the pckmo inकाष्ठाion */
	cpacf_pckmo(fc, paramblock);

	/* copy created रक्षित key */
	protkey->type = keytype;
	protkey->len = keysize + 32;
	स_नकल(protkey->protkey, paramblock, keysize + 32);

	वापस 0;
पूर्ण

/*
 * Find card and transक्रमm secure key पूर्णांकo रक्षित key.
 */
अटल पूर्णांक pkey_skey2pkey(स्थिर u8 *key, काष्ठा pkey_protkey *pkey)
अणु
	पूर्णांक rc, verअगरy;
	u16 cardnr, करोमुख्य;
	काष्ठा keytoken_header *hdr = (काष्ठा keytoken_header *)key;

	zcrypt_रुको_api_operational();

	/*
	 * The cca_xxx2protkey call may fail when a card has been
	 * addressed where the master key was changed after last fetch
	 * of the mkvp पूर्णांकo the cache. Try 3 बार: First witout verअगरy
	 * then with verअगरy and last round with verअगरy and old master
	 * key verअगरication pattern match not ignored.
	 */
	क्रम (verअगरy = 0; verअगरy < 3; verअगरy++) अणु
		rc = cca_findcard(key, &cardnr, &करोमुख्य, verअगरy);
		अगर (rc < 0)
			जारी;
		अगर (rc > 0 && verअगरy < 2)
			जारी;
		चयन (hdr->version) अणु
		हाल TOKVER_CCA_AES:
			rc = cca_sec2protkey(cardnr, करोमुख्य,
					     key, pkey->protkey,
					     &pkey->len, &pkey->type);
			अवरोध;
		हाल TOKVER_CCA_VLSC:
			rc = cca_cipher2protkey(cardnr, करोमुख्य,
						key, pkey->protkey,
						&pkey->len, &pkey->type);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अगर (rc == 0)
			अवरोध;
	पूर्ण

	अगर (rc)
		DEBUG_DBG("%s failed rc=%d\n", __func__, rc);

	वापस rc;
पूर्ण

/*
 * Conकाष्ठा EP11 key with given clear key value.
 */
अटल पूर्णांक pkey_clr2ep11key(स्थिर u8 *clrkey, माप_प्रकार clrkeylen,
			    u8 *keybuf, माप_प्रकार *keybuflen)
अणु
	पूर्णांक i, rc;
	u16 card, करोm;
	u32 nr_apqns, *apqns = शून्य;

	zcrypt_रुको_api_operational();

	/* build a list of apqns suitable क्रम ep11 keys with cpacf support */
	rc = ep11_findcard2(&apqns, &nr_apqns, 0xFFFF, 0xFFFF,
			    ZCRYPT_CEX7, EP11_API_V, शून्य);
	अगर (rc)
		जाओ out;

	/* go through the list of apqns and try to bild an ep11 key */
	क्रम (rc = -ENODEV, i = 0; i < nr_apqns; i++) अणु
		card = apqns[i] >> 16;
		करोm = apqns[i] & 0xFFFF;
		rc = ep11_clr2keyblob(card, करोm, clrkeylen * 8,
				      0, clrkey, keybuf, keybuflen);
		अगर (rc == 0)
			अवरोध;
	पूर्ण

out:
	kमुक्त(apqns);
	अगर (rc)
		DEBUG_DBG("%s failed rc=%d\n", __func__, rc);
	वापस rc;
पूर्ण

/*
 * Find card and transक्रमm EP11 secure key पूर्णांकo रक्षित key.
 */
अटल पूर्णांक pkey_ep11key2pkey(स्थिर u8 *key, काष्ठा pkey_protkey *pkey)
अणु
	पूर्णांक i, rc;
	u16 card, करोm;
	u32 nr_apqns, *apqns = शून्य;
	काष्ठा ep11keyblob *kb = (काष्ठा ep11keyblob *) key;

	zcrypt_रुको_api_operational();

	/* build a list of apqns suitable क्रम this key */
	rc = ep11_findcard2(&apqns, &nr_apqns, 0xFFFF, 0xFFFF,
			    ZCRYPT_CEX7, EP11_API_V, kb->wkvp);
	अगर (rc)
		जाओ out;

	/* go through the list of apqns and try to derive an pkey */
	क्रम (rc = -ENODEV, i = 0; i < nr_apqns; i++) अणु
		card = apqns[i] >> 16;
		करोm = apqns[i] & 0xFFFF;
		pkey->len = माप(pkey->protkey);
		rc = ep11_kblob2protkey(card, करोm, key, kb->head.len,
					pkey->protkey, &pkey->len, &pkey->type);
		अगर (rc == 0)
			अवरोध;
	पूर्ण

out:
	kमुक्त(apqns);
	अगर (rc)
		DEBUG_DBG("%s failed rc=%d\n", __func__, rc);
	वापस rc;
पूर्ण

/*
 * Verअगरy key and give back some info about the key.
 */
अटल पूर्णांक pkey_verअगरykey(स्थिर काष्ठा pkey_seckey *seckey,
			  u16 *pcardnr, u16 *pकरोमुख्य,
			  u16 *pkeysize, u32 *pattributes)
अणु
	काष्ठा secaeskeytoken *t = (काष्ठा secaeskeytoken *) seckey;
	u16 cardnr, करोमुख्य;
	पूर्णांक rc;

	/* check the secure key क्रम valid AES secure key */
	rc = cca_check_secaeskeytoken(debug_info, 3, (u8 *) seckey, 0);
	अगर (rc)
		जाओ out;
	अगर (pattributes)
		*pattributes = PKEY_VERIFY_ATTR_AES;
	अगर (pkeysize)
		*pkeysize = t->bitsize;

	/* try to find a card which can handle this key */
	rc = cca_findcard(seckey->seckey, &cardnr, &करोमुख्य, 1);
	अगर (rc < 0)
		जाओ out;

	अगर (rc > 0) अणु
		/* key mkvp matches to old master key mkvp */
		DEBUG_DBG("%s secure key has old mkvp\n", __func__);
		अगर (pattributes)
			*pattributes |= PKEY_VERIFY_ATTR_OLD_MKVP;
		rc = 0;
	पूर्ण

	अगर (pcardnr)
		*pcardnr = cardnr;
	अगर (pकरोमुख्य)
		*pकरोमुख्य = करोमुख्य;

out:
	DEBUG_DBG("%s rc=%d\n", __func__, rc);
	वापस rc;
पूर्ण

/*
 * Generate a अक्रमom रक्षित key
 */
अटल पूर्णांक pkey_genprotkey(u32 keytype, काष्ठा pkey_protkey *protkey)
अणु
	काष्ठा pkey_clrkey clrkey;
	पूर्णांक keysize;
	पूर्णांक rc;

	चयन (keytype) अणु
	हाल PKEY_KEYTYPE_AES_128:
		keysize = 16;
		अवरोध;
	हाल PKEY_KEYTYPE_AES_192:
		keysize = 24;
		अवरोध;
	हाल PKEY_KEYTYPE_AES_256:
		keysize = 32;
		अवरोध;
	शेष:
		DEBUG_ERR("%s unknown/unsupported keytype %d\n", __func__,
			  keytype);
		वापस -EINVAL;
	पूर्ण

	/* generate a dummy अक्रमom clear key */
	get_अक्रमom_bytes(clrkey.clrkey, keysize);

	/* convert it to a dummy रक्षित key */
	rc = pkey_clr2protkey(keytype, &clrkey, protkey);
	अगर (rc)
		वापस rc;

	/* replace the key part of the रक्षित key with अक्रमom bytes */
	get_अक्रमom_bytes(protkey->protkey, keysize);

	वापस 0;
पूर्ण

/*
 * Verअगरy अगर a रक्षित key is still valid
 */
अटल पूर्णांक pkey_verअगरyprotkey(स्थिर काष्ठा pkey_protkey *protkey)
अणु
	अचिन्हित दीर्घ fc;
	काष्ठा अणु
		u8 iv[AES_BLOCK_SIZE];
		u8 key[MAXPROTKEYSIZE];
	पूर्ण param;
	u8 null_msg[AES_BLOCK_SIZE];
	u8 dest_buf[AES_BLOCK_SIZE];
	अचिन्हित पूर्णांक k;

	चयन (protkey->type) अणु
	हाल PKEY_KEYTYPE_AES_128:
		fc = CPACF_KMC_PAES_128;
		अवरोध;
	हाल PKEY_KEYTYPE_AES_192:
		fc = CPACF_KMC_PAES_192;
		अवरोध;
	हाल PKEY_KEYTYPE_AES_256:
		fc = CPACF_KMC_PAES_256;
		अवरोध;
	शेष:
		DEBUG_ERR("%s unknown/unsupported keytype %d\n", __func__,
			  protkey->type);
		वापस -EINVAL;
	पूर्ण

	स_रखो(null_msg, 0, माप(null_msg));

	स_रखो(param.iv, 0, माप(param.iv));
	स_नकल(param.key, protkey->protkey, माप(param.key));

	k = cpacf_kmc(fc | CPACF_ENCRYPT, &param, null_msg, dest_buf,
		      माप(null_msg));
	अगर (k != माप(null_msg)) अणु
		DEBUG_ERR("%s protected key is not valid\n", __func__);
		वापस -EKEYREJECTED;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Transक्रमm a non-CCA key token पूर्णांकo a रक्षित key
 */
अटल पूर्णांक pkey_nonccatok2pkey(स्थिर u8 *key, u32 keylen,
			       काष्ठा pkey_protkey *protkey)
अणु
	पूर्णांक rc = -EINVAL;
	u8 *पंचांगpbuf = शून्य;
	काष्ठा keytoken_header *hdr = (काष्ठा keytoken_header *)key;

	चयन (hdr->version) अणु
	हाल TOKVER_PROTECTED_KEY: अणु
		काष्ठा protaeskeytoken *t;

		अगर (keylen != माप(काष्ठा protaeskeytoken))
			जाओ out;
		t = (काष्ठा protaeskeytoken *)key;
		protkey->len = t->len;
		protkey->type = t->keytype;
		स_नकल(protkey->protkey, t->protkey,
		       माप(protkey->protkey));
		rc = pkey_verअगरyprotkey(protkey);
		अवरोध;
	पूर्ण
	हाल TOKVER_CLEAR_KEY: अणु
		काष्ठा clearaeskeytoken *t;
		काष्ठा pkey_clrkey ckey;
		जोड़ u_पंचांगpbuf अणु
			u8 skey[SECKEYBLOBSIZE];
			u8 ep11key[MAXEP11AESKEYBLOBSIZE];
		पूर्ण;
		माप_प्रकार पंचांगpbuflen = माप(जोड़ u_पंचांगpbuf);

		अगर (keylen < माप(काष्ठा clearaeskeytoken))
			जाओ out;
		t = (काष्ठा clearaeskeytoken *)key;
		अगर (keylen != माप(*t) + t->len)
			जाओ out;
		अगर ((t->keytype == PKEY_KEYTYPE_AES_128 && t->len == 16)
		    || (t->keytype == PKEY_KEYTYPE_AES_192 && t->len == 24)
		    || (t->keytype == PKEY_KEYTYPE_AES_256 && t->len == 32))
			स_नकल(ckey.clrkey, t->clearkey, t->len);
		अन्यथा
			जाओ out;
		/* alloc temp key buffer space */
		पंचांगpbuf = kदो_स्मृति(पंचांगpbuflen, GFP_ATOMIC);
		अगर (!पंचांगpbuf) अणु
			rc = -ENOMEM;
			जाओ out;
		पूर्ण
		/* try direct way with the PCKMO inकाष्ठाion */
		rc = pkey_clr2protkey(t->keytype, &ckey, protkey);
		अगर (rc == 0)
			अवरोध;
		/* PCKMO failed, so try the CCA secure key way */
		zcrypt_रुको_api_operational();
		rc = cca_clr2seckey(0xFFFF, 0xFFFF, t->keytype,
				    ckey.clrkey, पंचांगpbuf);
		अगर (rc == 0)
			rc = pkey_skey2pkey(पंचांगpbuf, protkey);
		अगर (rc == 0)
			अवरोध;
		/* अगर the CCA way also failed, let's try via EP11 */
		rc = pkey_clr2ep11key(ckey.clrkey, t->len,
				      पंचांगpbuf, &पंचांगpbuflen);
		अगर (rc == 0)
			rc = pkey_ep11key2pkey(पंचांगpbuf, protkey);
		/* now we should really have an रक्षित key */
		DEBUG_ERR("%s unable to build protected key from clear",
			  __func__);
		अवरोध;
	पूर्ण
	हाल TOKVER_EP11_AES: अणु
		/* check ep11 key क्रम exportable as रक्षित key */
		rc = ep11_check_aes_key(debug_info, 3, key, keylen, 1);
		अगर (rc)
			जाओ out;
		rc = pkey_ep11key2pkey(key, protkey);
		अवरोध;
	पूर्ण
	हाल TOKVER_EP11_AES_WITH_HEADER:
		/* check ep11 key with header क्रम exportable as रक्षित key */
		rc = ep11_check_aes_key_with_hdr(debug_info, 3, key, keylen, 1);
		अगर (rc)
			जाओ out;
		rc = pkey_ep11key2pkey(key + माप(काष्ठा ep11kblob_header),
				       protkey);
		अवरोध;
	शेष:
		DEBUG_ERR("%s unknown/unsupported non-CCA token version %d\n",
			  __func__, hdr->version);
		rc = -EINVAL;
	पूर्ण

out:
	kमुक्त(पंचांगpbuf);
	वापस rc;
पूर्ण

/*
 * Transक्रमm a CCA पूर्णांकernal key token पूर्णांकo a रक्षित key
 */
अटल पूर्णांक pkey_ccaपूर्णांकtok2pkey(स्थिर u8 *key, u32 keylen,
			       काष्ठा pkey_protkey *protkey)
अणु
	काष्ठा keytoken_header *hdr = (काष्ठा keytoken_header *)key;

	चयन (hdr->version) अणु
	हाल TOKVER_CCA_AES:
		अगर (keylen != माप(काष्ठा secaeskeytoken))
			वापस -EINVAL;
		अवरोध;
	हाल TOKVER_CCA_VLSC:
		अगर (keylen < hdr->len || keylen > MAXCCAVLSCTOKENSIZE)
			वापस -EINVAL;
		अवरोध;
	शेष:
		DEBUG_ERR("%s unknown/unsupported CCA internal token version %d\n",
			  __func__, hdr->version);
		वापस -EINVAL;
	पूर्ण

	वापस pkey_skey2pkey(key, protkey);
पूर्ण

/*
 * Transक्रमm a key blob (of any type) पूर्णांकo a रक्षित key
 */
पूर्णांक pkey_keyblob2pkey(स्थिर u8 *key, u32 keylen,
		      काष्ठा pkey_protkey *protkey)
अणु
	पूर्णांक rc;
	काष्ठा keytoken_header *hdr = (काष्ठा keytoken_header *)key;

	अगर (keylen < माप(काष्ठा keytoken_header)) अणु
		DEBUG_ERR("%s invalid keylen %d\n", __func__, keylen);
		वापस -EINVAL;
	पूर्ण

	चयन (hdr->type) अणु
	हाल TOKTYPE_NON_CCA:
		rc = pkey_nonccatok2pkey(key, keylen, protkey);
		अवरोध;
	हाल TOKTYPE_CCA_INTERNAL:
		rc = pkey_ccaपूर्णांकtok2pkey(key, keylen, protkey);
		अवरोध;
	शेष:
		DEBUG_ERR("%s unknown/unsupported blob type %d\n",
			  __func__, hdr->type);
		वापस -EINVAL;
	पूर्ण

	DEBUG_DBG("%s rc=%d\n", __func__, rc);
	वापस rc;

पूर्ण
EXPORT_SYMBOL(pkey_keyblob2pkey);

अटल पूर्णांक pkey_genseckey2(स्थिर काष्ठा pkey_apqn *apqns, माप_प्रकार nr_apqns,
			   क्रमागत pkey_key_type ktype, क्रमागत pkey_key_size ksize,
			   u32 kflags, u8 *keybuf, माप_प्रकार *keybufsize)
अणु
	पूर्णांक i, card, करोm, rc;

	/* check क्रम at least one apqn given */
	अगर (!apqns || !nr_apqns)
		वापस -EINVAL;

	/* check key type and size */
	चयन (ktype) अणु
	हाल PKEY_TYPE_CCA_DATA:
	हाल PKEY_TYPE_CCA_CIPHER:
		अगर (*keybufsize < SECKEYBLOBSIZE)
			वापस -EINVAL;
		अवरोध;
	हाल PKEY_TYPE_EP11:
		अगर (*keybufsize < MINEP11AESKEYBLOBSIZE)
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	चयन (ksize) अणु
	हाल PKEY_SIZE_AES_128:
	हाल PKEY_SIZE_AES_192:
	हाल PKEY_SIZE_AES_256:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* simple try all apqns from the list */
	क्रम (i = 0, rc = -ENODEV; i < nr_apqns; i++) अणु
		card = apqns[i].card;
		करोm = apqns[i].करोमुख्य;
		अगर (ktype == PKEY_TYPE_EP11) अणु
			rc = ep11_genaeskey(card, करोm, ksize, kflags,
					    keybuf, keybufsize);
		पूर्ण अन्यथा अगर (ktype == PKEY_TYPE_CCA_DATA) अणु
			rc = cca_genseckey(card, करोm, ksize, keybuf);
			*keybufsize = (rc ? 0 : SECKEYBLOBSIZE);
		पूर्ण अन्यथा /* TOKVER_CCA_VLSC */
			rc = cca_gencipherkey(card, करोm, ksize, kflags,
					      keybuf, keybufsize);
		अगर (rc == 0)
			अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक pkey_clr2seckey2(स्थिर काष्ठा pkey_apqn *apqns, माप_प्रकार nr_apqns,
			    क्रमागत pkey_key_type ktype, क्रमागत pkey_key_size ksize,
			    u32 kflags, स्थिर u8 *clrkey,
			    u8 *keybuf, माप_प्रकार *keybufsize)
अणु
	पूर्णांक i, card, करोm, rc;

	/* check क्रम at least one apqn given */
	अगर (!apqns || !nr_apqns)
		वापस -EINVAL;

	/* check key type and size */
	चयन (ktype) अणु
	हाल PKEY_TYPE_CCA_DATA:
	हाल PKEY_TYPE_CCA_CIPHER:
		अगर (*keybufsize < SECKEYBLOBSIZE)
			वापस -EINVAL;
		अवरोध;
	हाल PKEY_TYPE_EP11:
		अगर (*keybufsize < MINEP11AESKEYBLOBSIZE)
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	चयन (ksize) अणु
	हाल PKEY_SIZE_AES_128:
	हाल PKEY_SIZE_AES_192:
	हाल PKEY_SIZE_AES_256:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	zcrypt_रुको_api_operational();

	/* simple try all apqns from the list */
	क्रम (i = 0, rc = -ENODEV; i < nr_apqns; i++) अणु
		card = apqns[i].card;
		करोm = apqns[i].करोमुख्य;
		अगर (ktype == PKEY_TYPE_EP11) अणु
			rc = ep11_clr2keyblob(card, करोm, ksize, kflags,
					      clrkey, keybuf, keybufsize);
		पूर्ण अन्यथा अगर (ktype == PKEY_TYPE_CCA_DATA) अणु
			rc = cca_clr2seckey(card, करोm, ksize,
					    clrkey, keybuf);
			*keybufsize = (rc ? 0 : SECKEYBLOBSIZE);
		पूर्ण अन्यथा /* TOKVER_CCA_VLSC */
			rc = cca_clr2cipherkey(card, करोm, ksize, kflags,
					       clrkey, keybuf, keybufsize);
		अगर (rc == 0)
			अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक pkey_verअगरykey2(स्थिर u8 *key, माप_प्रकार keylen,
			   u16 *cardnr, u16 *करोमुख्य,
			   क्रमागत pkey_key_type *ktype,
			   क्रमागत pkey_key_size *ksize, u32 *flags)
अणु
	पूर्णांक rc;
	u32 _nr_apqns, *_apqns = शून्य;
	काष्ठा keytoken_header *hdr = (काष्ठा keytoken_header *)key;

	अगर (keylen < माप(काष्ठा keytoken_header))
		वापस -EINVAL;

	अगर (hdr->type == TOKTYPE_CCA_INTERNAL
	    && hdr->version == TOKVER_CCA_AES) अणु
		काष्ठा secaeskeytoken *t = (काष्ठा secaeskeytoken *)key;

		rc = cca_check_secaeskeytoken(debug_info, 3, key, 0);
		अगर (rc)
			जाओ out;
		अगर (ktype)
			*ktype = PKEY_TYPE_CCA_DATA;
		अगर (ksize)
			*ksize = (क्रमागत pkey_key_size) t->bitsize;

		rc = cca_findcard2(&_apqns, &_nr_apqns, *cardnr, *करोमुख्य,
				   ZCRYPT_CEX3C, AES_MK_SET, t->mkvp, 0, 1);
		अगर (rc == 0 && flags)
			*flags = PKEY_FLAGS_MATCH_CUR_MKVP;
		अगर (rc == -ENODEV) अणु
			rc = cca_findcard2(&_apqns, &_nr_apqns,
					   *cardnr, *करोमुख्य,
					   ZCRYPT_CEX3C, AES_MK_SET,
					   0, t->mkvp, 1);
			अगर (rc == 0 && flags)
				*flags = PKEY_FLAGS_MATCH_ALT_MKVP;
		पूर्ण
		अगर (rc)
			जाओ out;

		*cardnr = ((काष्ठा pkey_apqn *)_apqns)->card;
		*करोमुख्य = ((काष्ठा pkey_apqn *)_apqns)->करोमुख्य;

	पूर्ण अन्यथा अगर (hdr->type == TOKTYPE_CCA_INTERNAL
		   && hdr->version == TOKVER_CCA_VLSC) अणु
		काष्ठा cipherkeytoken *t = (काष्ठा cipherkeytoken *)key;

		rc = cca_check_secaescipherkey(debug_info, 3, key, 0, 1);
		अगर (rc)
			जाओ out;
		अगर (ktype)
			*ktype = PKEY_TYPE_CCA_CIPHER;
		अगर (ksize) अणु
			*ksize = PKEY_SIZE_UNKNOWN;
			अगर (!t->plfver && t->wpllen == 512)
				*ksize = PKEY_SIZE_AES_128;
			अन्यथा अगर (!t->plfver && t->wpllen == 576)
				*ksize = PKEY_SIZE_AES_192;
			अन्यथा अगर (!t->plfver && t->wpllen == 640)
				*ksize = PKEY_SIZE_AES_256;
		पूर्ण

		rc = cca_findcard2(&_apqns, &_nr_apqns, *cardnr, *करोमुख्य,
				   ZCRYPT_CEX6, AES_MK_SET, t->mkvp0, 0, 1);
		अगर (rc == 0 && flags)
			*flags = PKEY_FLAGS_MATCH_CUR_MKVP;
		अगर (rc == -ENODEV) अणु
			rc = cca_findcard2(&_apqns, &_nr_apqns,
					   *cardnr, *करोमुख्य,
					   ZCRYPT_CEX6, AES_MK_SET,
					   0, t->mkvp0, 1);
			अगर (rc == 0 && flags)
				*flags = PKEY_FLAGS_MATCH_ALT_MKVP;
		पूर्ण
		अगर (rc)
			जाओ out;

		*cardnr = ((काष्ठा pkey_apqn *)_apqns)->card;
		*करोमुख्य = ((काष्ठा pkey_apqn *)_apqns)->करोमुख्य;

	पूर्ण अन्यथा अगर (hdr->type == TOKTYPE_NON_CCA
		   && hdr->version == TOKVER_EP11_AES) अणु
		काष्ठा ep11keyblob *kb = (काष्ठा ep11keyblob *)key;

		rc = ep11_check_aes_key(debug_info, 3, key, keylen, 1);
		अगर (rc)
			जाओ out;
		अगर (ktype)
			*ktype = PKEY_TYPE_EP11;
		अगर (ksize)
			*ksize = kb->head.keybitlen;

		rc = ep11_findcard2(&_apqns, &_nr_apqns, *cardnr, *करोमुख्य,
				    ZCRYPT_CEX7, EP11_API_V, kb->wkvp);
		अगर (rc)
			जाओ out;

		अगर (flags)
			*flags = PKEY_FLAGS_MATCH_CUR_MKVP;

		*cardnr = ((काष्ठा pkey_apqn *)_apqns)->card;
		*करोमुख्य = ((काष्ठा pkey_apqn *)_apqns)->करोमुख्य;

	पूर्ण अन्यथा
		rc = -EINVAL;

out:
	kमुक्त(_apqns);
	वापस rc;
पूर्ण

अटल पूर्णांक pkey_keyblob2pkey2(स्थिर काष्ठा pkey_apqn *apqns, माप_प्रकार nr_apqns,
			      स्थिर u8 *key, माप_प्रकार keylen,
			      काष्ठा pkey_protkey *pkey)
अणु
	पूर्णांक i, card, करोm, rc;
	काष्ठा keytoken_header *hdr = (काष्ठा keytoken_header *)key;

	/* check क्रम at least one apqn given */
	अगर (!apqns || !nr_apqns)
		वापस -EINVAL;

	अगर (keylen < माप(काष्ठा keytoken_header))
		वापस -EINVAL;

	अगर (hdr->type == TOKTYPE_CCA_INTERNAL) अणु
		अगर (hdr->version == TOKVER_CCA_AES) अणु
			अगर (keylen != माप(काष्ठा secaeskeytoken))
				वापस -EINVAL;
			अगर (cca_check_secaeskeytoken(debug_info, 3, key, 0))
				वापस -EINVAL;
		पूर्ण अन्यथा अगर (hdr->version == TOKVER_CCA_VLSC) अणु
			अगर (keylen < hdr->len || keylen > MAXCCAVLSCTOKENSIZE)
				वापस -EINVAL;
			अगर (cca_check_secaescipherkey(debug_info, 3, key, 0, 1))
				वापस -EINVAL;
		पूर्ण अन्यथा अणु
			DEBUG_ERR("%s unknown CCA internal token version %d\n",
				  __func__, hdr->version);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (hdr->type == TOKTYPE_NON_CCA) अणु
		अगर (hdr->version == TOKVER_EP11_AES) अणु
			अगर (keylen < माप(काष्ठा ep11keyblob))
				वापस -EINVAL;
			अगर (ep11_check_aes_key(debug_info, 3, key, keylen, 1))
				वापस -EINVAL;
		पूर्ण अन्यथा अणु
			वापस pkey_nonccatok2pkey(key, keylen, pkey);
		पूर्ण
	पूर्ण अन्यथा अणु
		DEBUG_ERR("%s unknown/unsupported blob type %d\n",
			  __func__, hdr->type);
		वापस -EINVAL;
	पूर्ण

	zcrypt_रुको_api_operational();

	/* simple try all apqns from the list */
	क्रम (i = 0, rc = -ENODEV; i < nr_apqns; i++) अणु
		card = apqns[i].card;
		करोm = apqns[i].करोमुख्य;
		अगर (hdr->type == TOKTYPE_CCA_INTERNAL
		    && hdr->version == TOKVER_CCA_AES)
			rc = cca_sec2protkey(card, करोm, key, pkey->protkey,
					     &pkey->len, &pkey->type);
		अन्यथा अगर (hdr->type == TOKTYPE_CCA_INTERNAL
			 && hdr->version == TOKVER_CCA_VLSC)
			rc = cca_cipher2protkey(card, करोm, key, pkey->protkey,
						&pkey->len, &pkey->type);
		अन्यथा अणु /* EP11 AES secure key blob */
			काष्ठा ep11keyblob *kb = (काष्ठा ep11keyblob *) key;

			pkey->len = माप(pkey->protkey);
			rc = ep11_kblob2protkey(card, करोm, key, kb->head.len,
						pkey->protkey, &pkey->len,
						&pkey->type);
		पूर्ण
		अगर (rc == 0)
			अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक pkey_apqns4key(स्थिर u8 *key, माप_प्रकार keylen, u32 flags,
			  काष्ठा pkey_apqn *apqns, माप_प्रकार *nr_apqns)
अणु
	पूर्णांक rc;
	u32 _nr_apqns, *_apqns = शून्य;
	काष्ठा keytoken_header *hdr = (काष्ठा keytoken_header *)key;

	अगर (keylen < माप(काष्ठा keytoken_header) || flags == 0)
		वापस -EINVAL;

	zcrypt_रुको_api_operational();

	अगर (hdr->type == TOKTYPE_NON_CCA
	    && (hdr->version == TOKVER_EP11_AES_WITH_HEADER
		|| hdr->version == TOKVER_EP11_ECC_WITH_HEADER)
	    && is_ep11_keyblob(key + माप(काष्ठा ep11kblob_header))) अणु
		पूर्णांक minhwtype = 0, api = 0;
		काष्ठा ep11keyblob *kb = (काष्ठा ep11keyblob *)
			(key + माप(काष्ठा ep11kblob_header));

		अगर (flags != PKEY_FLAGS_MATCH_CUR_MKVP)
			वापस -EINVAL;
		अगर (kb->attr & EP11_BLOB_PKEY_EXTRACTABLE) अणु
			minhwtype = ZCRYPT_CEX7;
			api = EP11_API_V;
		पूर्ण
		rc = ep11_findcard2(&_apqns, &_nr_apqns, 0xFFFF, 0xFFFF,
				    minhwtype, api, kb->wkvp);
		अगर (rc)
			जाओ out;
	पूर्ण अन्यथा अगर (hdr->type == TOKTYPE_NON_CCA
		   && hdr->version == TOKVER_EP11_AES
		   && is_ep11_keyblob(key)) अणु
		पूर्णांक minhwtype = 0, api = 0;
		काष्ठा ep11keyblob *kb = (काष्ठा ep11keyblob *) key;

		अगर (flags != PKEY_FLAGS_MATCH_CUR_MKVP)
			वापस -EINVAL;
		अगर (kb->attr & EP11_BLOB_PKEY_EXTRACTABLE) अणु
			minhwtype = ZCRYPT_CEX7;
			api = EP11_API_V;
		पूर्ण
		rc = ep11_findcard2(&_apqns, &_nr_apqns, 0xFFFF, 0xFFFF,
				    minhwtype, api, kb->wkvp);
		अगर (rc)
			जाओ out;
	पूर्ण अन्यथा अगर (hdr->type == TOKTYPE_CCA_INTERNAL) अणु
		पूर्णांक minhwtype = ZCRYPT_CEX3C;
		u64 cur_mkvp = 0, old_mkvp = 0;

		अगर (hdr->version == TOKVER_CCA_AES) अणु
			काष्ठा secaeskeytoken *t = (काष्ठा secaeskeytoken *)key;

			अगर (flags & PKEY_FLAGS_MATCH_CUR_MKVP)
				cur_mkvp = t->mkvp;
			अगर (flags & PKEY_FLAGS_MATCH_ALT_MKVP)
				old_mkvp = t->mkvp;
		पूर्ण अन्यथा अगर (hdr->version == TOKVER_CCA_VLSC) अणु
			काष्ठा cipherkeytoken *t = (काष्ठा cipherkeytoken *)key;

			minhwtype = ZCRYPT_CEX6;
			अगर (flags & PKEY_FLAGS_MATCH_CUR_MKVP)
				cur_mkvp = t->mkvp0;
			अगर (flags & PKEY_FLAGS_MATCH_ALT_MKVP)
				old_mkvp = t->mkvp0;
		पूर्ण अन्यथा अणु
			/* unknown cca पूर्णांकernal token type */
			वापस -EINVAL;
		पूर्ण
		rc = cca_findcard2(&_apqns, &_nr_apqns, 0xFFFF, 0xFFFF,
				   minhwtype, AES_MK_SET,
				   cur_mkvp, old_mkvp, 1);
		अगर (rc)
			जाओ out;
	पूर्ण अन्यथा अगर (hdr->type == TOKTYPE_CCA_INTERNAL_PKA) अणु
		u64 cur_mkvp = 0, old_mkvp = 0;
		काष्ठा eccprivkeytoken *t = (काष्ठा eccprivkeytoken *)key;

		अगर (t->secid == 0x20) अणु
			अगर (flags & PKEY_FLAGS_MATCH_CUR_MKVP)
				cur_mkvp = t->mkvp;
			अगर (flags & PKEY_FLAGS_MATCH_ALT_MKVP)
				old_mkvp = t->mkvp;
		पूर्ण अन्यथा अणु
			/* unknown cca पूर्णांकernal 2 token type */
			वापस -EINVAL;
		पूर्ण
		rc = cca_findcard2(&_apqns, &_nr_apqns, 0xFFFF, 0xFFFF,
				   ZCRYPT_CEX7, APKA_MK_SET,
				   cur_mkvp, old_mkvp, 1);
		अगर (rc)
			जाओ out;
	पूर्ण अन्यथा
		वापस -EINVAL;

	अगर (apqns) अणु
		अगर (*nr_apqns < _nr_apqns)
			rc = -ENOSPC;
		अन्यथा
			स_नकल(apqns, _apqns, _nr_apqns * माप(u32));
	पूर्ण
	*nr_apqns = _nr_apqns;

out:
	kमुक्त(_apqns);
	वापस rc;
पूर्ण

अटल पूर्णांक pkey_apqns4keytype(क्रमागत pkey_key_type ktype,
			      u8 cur_mkvp[32], u8 alt_mkvp[32], u32 flags,
			      काष्ठा pkey_apqn *apqns, माप_प्रकार *nr_apqns)
अणु
	पूर्णांक rc;
	u32 _nr_apqns, *_apqns = शून्य;

	zcrypt_रुको_api_operational();

	अगर (ktype == PKEY_TYPE_CCA_DATA || ktype == PKEY_TYPE_CCA_CIPHER) अणु
		u64 cur_mkvp = 0, old_mkvp = 0;
		पूर्णांक minhwtype = ZCRYPT_CEX3C;

		अगर (flags & PKEY_FLAGS_MATCH_CUR_MKVP)
			cur_mkvp = *((u64 *) cur_mkvp);
		अगर (flags & PKEY_FLAGS_MATCH_ALT_MKVP)
			old_mkvp = *((u64 *) alt_mkvp);
		अगर (ktype == PKEY_TYPE_CCA_CIPHER)
			minhwtype = ZCRYPT_CEX6;
		rc = cca_findcard2(&_apqns, &_nr_apqns, 0xFFFF, 0xFFFF,
				   minhwtype, AES_MK_SET,
				   cur_mkvp, old_mkvp, 1);
		अगर (rc)
			जाओ out;
	पूर्ण अन्यथा अगर (ktype == PKEY_TYPE_CCA_ECC) अणु
		u64 cur_mkvp = 0, old_mkvp = 0;

		अगर (flags & PKEY_FLAGS_MATCH_CUR_MKVP)
			cur_mkvp = *((u64 *) cur_mkvp);
		अगर (flags & PKEY_FLAGS_MATCH_ALT_MKVP)
			old_mkvp = *((u64 *) alt_mkvp);
		rc = cca_findcard2(&_apqns, &_nr_apqns, 0xFFFF, 0xFFFF,
				   ZCRYPT_CEX7, APKA_MK_SET,
				   cur_mkvp, old_mkvp, 1);
		अगर (rc)
			जाओ out;

	पूर्ण अन्यथा अगर (ktype == PKEY_TYPE_EP11 ||
		   ktype == PKEY_TYPE_EP11_AES ||
		   ktype == PKEY_TYPE_EP11_ECC) अणु
		u8 *wkvp = शून्य;

		अगर (flags & PKEY_FLAGS_MATCH_CUR_MKVP)
			wkvp = cur_mkvp;
		rc = ep11_findcard2(&_apqns, &_nr_apqns, 0xFFFF, 0xFFFF,
				    ZCRYPT_CEX7, EP11_API_V, wkvp);
		अगर (rc)
			जाओ out;

	पूर्ण अन्यथा
		वापस -EINVAL;

	अगर (apqns) अणु
		अगर (*nr_apqns < _nr_apqns)
			rc = -ENOSPC;
		अन्यथा
			स_नकल(apqns, _apqns, _nr_apqns * माप(u32));
	पूर्ण
	*nr_apqns = _nr_apqns;

out:
	kमुक्त(_apqns);
	वापस rc;
पूर्ण

अटल पूर्णांक pkey_keyblob2pkey3(स्थिर काष्ठा pkey_apqn *apqns, माप_प्रकार nr_apqns,
			      स्थिर u8 *key, माप_प्रकार keylen, u32 *protkeytype,
			      u8 *protkey, u32 *protkeylen)
अणु
	पूर्णांक i, card, करोm, rc;
	काष्ठा keytoken_header *hdr = (काष्ठा keytoken_header *)key;

	/* check क्रम at least one apqn given */
	अगर (!apqns || !nr_apqns)
		वापस -EINVAL;

	अगर (keylen < माप(काष्ठा keytoken_header))
		वापस -EINVAL;

	अगर (hdr->type == TOKTYPE_NON_CCA
	    && hdr->version == TOKVER_EP11_AES_WITH_HEADER
	    && is_ep11_keyblob(key + माप(काष्ठा ep11kblob_header))) अणु
		/* EP11 AES key blob with header */
		अगर (ep11_check_aes_key_with_hdr(debug_info, 3, key, keylen, 1))
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (hdr->type == TOKTYPE_NON_CCA
		   && hdr->version == TOKVER_EP11_ECC_WITH_HEADER
		   && is_ep11_keyblob(key + माप(काष्ठा ep11kblob_header))) अणु
		/* EP11 ECC key blob with header */
		अगर (ep11_check_ecc_key_with_hdr(debug_info, 3, key, keylen, 1))
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (hdr->type == TOKTYPE_NON_CCA
		   && hdr->version == TOKVER_EP11_AES
		   && is_ep11_keyblob(key)) अणु
		/* EP11 AES key blob with header in session field */
		अगर (ep11_check_aes_key(debug_info, 3, key, keylen, 1))
			वापस -EINVAL;
	पूर्ण अन्यथा	अगर (hdr->type == TOKTYPE_CCA_INTERNAL) अणु
		अगर (hdr->version == TOKVER_CCA_AES) अणु
			/* CCA AES data key */
			अगर (keylen != माप(काष्ठा secaeskeytoken))
				वापस -EINVAL;
			अगर (cca_check_secaeskeytoken(debug_info, 3, key, 0))
				वापस -EINVAL;
		पूर्ण अन्यथा अगर (hdr->version == TOKVER_CCA_VLSC) अणु
			/* CCA AES cipher key */
			अगर (keylen < hdr->len || keylen > MAXCCAVLSCTOKENSIZE)
				वापस -EINVAL;
			अगर (cca_check_secaescipherkey(debug_info, 3, key, 0, 1))
				वापस -EINVAL;
		पूर्ण अन्यथा अणु
			DEBUG_ERR("%s unknown CCA internal token version %d\n",
				  __func__, hdr->version);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (hdr->type == TOKTYPE_CCA_INTERNAL_PKA) अणु
		/* CCA ECC (निजी) key */
		अगर (keylen < माप(काष्ठा eccprivkeytoken))
			वापस -EINVAL;
		अगर (cca_check_sececckeytoken(debug_info, 3, key, keylen, 1))
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (hdr->type == TOKTYPE_NON_CCA) अणु
		काष्ठा pkey_protkey pkey;

		rc = pkey_nonccatok2pkey(key, keylen, &pkey);
		अगर (rc)
			वापस rc;
		स_नकल(protkey, pkey.protkey, pkey.len);
		*protkeylen = pkey.len;
		*protkeytype = pkey.type;
		वापस 0;
	पूर्ण अन्यथा अणु
		DEBUG_ERR("%s unknown/unsupported blob type %d\n",
			  __func__, hdr->type);
		वापस -EINVAL;
	पूर्ण

	/* simple try all apqns from the list */
	क्रम (rc = -ENODEV, i = 0; rc && i < nr_apqns; i++) अणु
		card = apqns[i].card;
		करोm = apqns[i].करोमुख्य;
		अगर (hdr->type == TOKTYPE_NON_CCA
		    && (hdr->version == TOKVER_EP11_AES_WITH_HEADER
			|| hdr->version == TOKVER_EP11_ECC_WITH_HEADER)
		    && is_ep11_keyblob(key + माप(काष्ठा ep11kblob_header)))
			rc = ep11_kblob2protkey(card, करोm, key, hdr->len,
						protkey, protkeylen, protkeytype);
		अन्यथा अगर (hdr->type == TOKTYPE_NON_CCA
			 && hdr->version == TOKVER_EP11_AES
			 && is_ep11_keyblob(key))
			rc = ep11_kblob2protkey(card, करोm, key, hdr->len,
						protkey, protkeylen, protkeytype);
		अन्यथा अगर (hdr->type == TOKTYPE_CCA_INTERNAL &&
			 hdr->version == TOKVER_CCA_AES)
			rc = cca_sec2protkey(card, करोm, key, protkey,
					     protkeylen, protkeytype);
		अन्यथा अगर (hdr->type == TOKTYPE_CCA_INTERNAL &&
			 hdr->version == TOKVER_CCA_VLSC)
			rc = cca_cipher2protkey(card, करोm, key, protkey,
						protkeylen, protkeytype);
		अन्यथा अगर (hdr->type == TOKTYPE_CCA_INTERNAL_PKA)
			rc = cca_ecc2protkey(card, करोm, key, protkey,
					     protkeylen, protkeytype);
		अन्यथा
			वापस -EINVAL;
	पूर्ण

	वापस rc;
पूर्ण

/*
 * File io functions
 */

अटल व्योम *_copy_key_from_user(व्योम __user *ukey, माप_प्रकार keylen)
अणु
	अगर (!ukey || keylen < MINKEYBLOBSIZE || keylen > KEYBLOBबफ_मानE)
		वापस ERR_PTR(-EINVAL);

	वापस memdup_user(ukey, keylen);
पूर्ण

अटल व्योम *_copy_apqns_from_user(व्योम __user *uapqns, माप_प्रकार nr_apqns)
अणु
	अगर (!uapqns || nr_apqns == 0)
		वापस शून्य;

	वापस memdup_user(uapqns, nr_apqns * माप(काष्ठा pkey_apqn));
पूर्ण

अटल दीर्घ pkey_unlocked_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु
	पूर्णांक rc;

	चयन (cmd) अणु
	हाल PKEY_GENSECK: अणु
		काष्ठा pkey_genseck __user *ugs = (व्योम __user *) arg;
		काष्ठा pkey_genseck kgs;

		अगर (copy_from_user(&kgs, ugs, माप(kgs)))
			वापस -EFAULT;
		rc = cca_genseckey(kgs.cardnr, kgs.करोमुख्य,
				   kgs.keytype, kgs.seckey.seckey);
		DEBUG_DBG("%s cca_genseckey()=%d\n", __func__, rc);
		अगर (rc)
			अवरोध;
		अगर (copy_to_user(ugs, &kgs, माप(kgs)))
			वापस -EFAULT;
		अवरोध;
	पूर्ण
	हाल PKEY_CLR2SECK: अणु
		काष्ठा pkey_clr2seck __user *ucs = (व्योम __user *) arg;
		काष्ठा pkey_clr2seck kcs;

		अगर (copy_from_user(&kcs, ucs, माप(kcs)))
			वापस -EFAULT;
		rc = cca_clr2seckey(kcs.cardnr, kcs.करोमुख्य, kcs.keytype,
				    kcs.clrkey.clrkey, kcs.seckey.seckey);
		DEBUG_DBG("%s cca_clr2seckey()=%d\n", __func__, rc);
		अगर (rc)
			अवरोध;
		अगर (copy_to_user(ucs, &kcs, माप(kcs)))
			वापस -EFAULT;
		memzero_explicit(&kcs, माप(kcs));
		अवरोध;
	पूर्ण
	हाल PKEY_SEC2PROTK: अणु
		काष्ठा pkey_sec2protk __user *usp = (व्योम __user *) arg;
		काष्ठा pkey_sec2protk ksp;

		अगर (copy_from_user(&ksp, usp, माप(ksp)))
			वापस -EFAULT;
		rc = cca_sec2protkey(ksp.cardnr, ksp.करोमुख्य,
				     ksp.seckey.seckey, ksp.protkey.protkey,
				     &ksp.protkey.len, &ksp.protkey.type);
		DEBUG_DBG("%s cca_sec2protkey()=%d\n", __func__, rc);
		अगर (rc)
			अवरोध;
		अगर (copy_to_user(usp, &ksp, माप(ksp)))
			वापस -EFAULT;
		अवरोध;
	पूर्ण
	हाल PKEY_CLR2PROTK: अणु
		काष्ठा pkey_clr2protk __user *ucp = (व्योम __user *) arg;
		काष्ठा pkey_clr2protk kcp;

		अगर (copy_from_user(&kcp, ucp, माप(kcp)))
			वापस -EFAULT;
		rc = pkey_clr2protkey(kcp.keytype,
				      &kcp.clrkey, &kcp.protkey);
		DEBUG_DBG("%s pkey_clr2protkey()=%d\n", __func__, rc);
		अगर (rc)
			अवरोध;
		अगर (copy_to_user(ucp, &kcp, माप(kcp)))
			वापस -EFAULT;
		memzero_explicit(&kcp, माप(kcp));
		अवरोध;
	पूर्ण
	हाल PKEY_FINDCARD: अणु
		काष्ठा pkey_findcard __user *ufc = (व्योम __user *) arg;
		काष्ठा pkey_findcard kfc;

		अगर (copy_from_user(&kfc, ufc, माप(kfc)))
			वापस -EFAULT;
		rc = cca_findcard(kfc.seckey.seckey,
				  &kfc.cardnr, &kfc.करोमुख्य, 1);
		DEBUG_DBG("%s cca_findcard()=%d\n", __func__, rc);
		अगर (rc < 0)
			अवरोध;
		अगर (copy_to_user(ufc, &kfc, माप(kfc)))
			वापस -EFAULT;
		अवरोध;
	पूर्ण
	हाल PKEY_SKEY2PKEY: अणु
		काष्ठा pkey_skey2pkey __user *usp = (व्योम __user *) arg;
		काष्ठा pkey_skey2pkey ksp;

		अगर (copy_from_user(&ksp, usp, माप(ksp)))
			वापस -EFAULT;
		rc = pkey_skey2pkey(ksp.seckey.seckey, &ksp.protkey);
		DEBUG_DBG("%s pkey_skey2pkey()=%d\n", __func__, rc);
		अगर (rc)
			अवरोध;
		अगर (copy_to_user(usp, &ksp, माप(ksp)))
			वापस -EFAULT;
		अवरोध;
	पूर्ण
	हाल PKEY_VERIFYKEY: अणु
		काष्ठा pkey_verअगरykey __user *uvk = (व्योम __user *) arg;
		काष्ठा pkey_verअगरykey kvk;

		अगर (copy_from_user(&kvk, uvk, माप(kvk)))
			वापस -EFAULT;
		rc = pkey_verअगरykey(&kvk.seckey, &kvk.cardnr, &kvk.करोमुख्य,
				    &kvk.keysize, &kvk.attributes);
		DEBUG_DBG("%s pkey_verifykey()=%d\n", __func__, rc);
		अगर (rc)
			अवरोध;
		अगर (copy_to_user(uvk, &kvk, माप(kvk)))
			वापस -EFAULT;
		अवरोध;
	पूर्ण
	हाल PKEY_GENPROTK: अणु
		काष्ठा pkey_genprotk __user *ugp = (व्योम __user *) arg;
		काष्ठा pkey_genprotk kgp;

		अगर (copy_from_user(&kgp, ugp, माप(kgp)))
			वापस -EFAULT;
		rc = pkey_genprotkey(kgp.keytype, &kgp.protkey);
		DEBUG_DBG("%s pkey_genprotkey()=%d\n", __func__, rc);
		अगर (rc)
			अवरोध;
		अगर (copy_to_user(ugp, &kgp, माप(kgp)))
			वापस -EFAULT;
		अवरोध;
	पूर्ण
	हाल PKEY_VERIFYPROTK: अणु
		काष्ठा pkey_verअगरyprotk __user *uvp = (व्योम __user *) arg;
		काष्ठा pkey_verअगरyprotk kvp;

		अगर (copy_from_user(&kvp, uvp, माप(kvp)))
			वापस -EFAULT;
		rc = pkey_verअगरyprotkey(&kvp.protkey);
		DEBUG_DBG("%s pkey_verifyprotkey()=%d\n", __func__, rc);
		अवरोध;
	पूर्ण
	हाल PKEY_KBLOB2PROTK: अणु
		काष्ठा pkey_kblob2pkey __user *utp = (व्योम __user *) arg;
		काष्ठा pkey_kblob2pkey ktp;
		u8 *kkey;

		अगर (copy_from_user(&ktp, utp, माप(ktp)))
			वापस -EFAULT;
		kkey = _copy_key_from_user(ktp.key, ktp.keylen);
		अगर (IS_ERR(kkey))
			वापस PTR_ERR(kkey);
		rc = pkey_keyblob2pkey(kkey, ktp.keylen, &ktp.protkey);
		DEBUG_DBG("%s pkey_keyblob2pkey()=%d\n", __func__, rc);
		kमुक्त(kkey);
		अगर (rc)
			अवरोध;
		अगर (copy_to_user(utp, &ktp, माप(ktp)))
			वापस -EFAULT;
		अवरोध;
	पूर्ण
	हाल PKEY_GENSECK2: अणु
		काष्ठा pkey_genseck2 __user *ugs = (व्योम __user *) arg;
		काष्ठा pkey_genseck2 kgs;
		काष्ठा pkey_apqn *apqns;
		माप_प्रकार klen = KEYBLOBबफ_मानE;
		u8 *kkey;

		अगर (copy_from_user(&kgs, ugs, माप(kgs)))
			वापस -EFAULT;
		apqns = _copy_apqns_from_user(kgs.apqns, kgs.apqn_entries);
		अगर (IS_ERR(apqns))
			वापस PTR_ERR(apqns);
		kkey = kदो_स्मृति(klen, GFP_KERNEL);
		अगर (!kkey) अणु
			kमुक्त(apqns);
			वापस -ENOMEM;
		पूर्ण
		rc = pkey_genseckey2(apqns, kgs.apqn_entries,
				     kgs.type, kgs.size, kgs.keygenflags,
				     kkey, &klen);
		DEBUG_DBG("%s pkey_genseckey2()=%d\n", __func__, rc);
		kमुक्त(apqns);
		अगर (rc) अणु
			kमुक्त(kkey);
			अवरोध;
		पूर्ण
		अगर (kgs.key) अणु
			अगर (kgs.keylen < klen) अणु
				kमुक्त(kkey);
				वापस -EINVAL;
			पूर्ण
			अगर (copy_to_user(kgs.key, kkey, klen)) अणु
				kमुक्त(kkey);
				वापस -EFAULT;
			पूर्ण
		पूर्ण
		kgs.keylen = klen;
		अगर (copy_to_user(ugs, &kgs, माप(kgs)))
			rc = -EFAULT;
		kमुक्त(kkey);
		अवरोध;
	पूर्ण
	हाल PKEY_CLR2SECK2: अणु
		काष्ठा pkey_clr2seck2 __user *ucs = (व्योम __user *) arg;
		काष्ठा pkey_clr2seck2 kcs;
		काष्ठा pkey_apqn *apqns;
		माप_प्रकार klen = KEYBLOBबफ_मानE;
		u8 *kkey;

		अगर (copy_from_user(&kcs, ucs, माप(kcs)))
			वापस -EFAULT;
		apqns = _copy_apqns_from_user(kcs.apqns, kcs.apqn_entries);
		अगर (IS_ERR(apqns))
			वापस PTR_ERR(apqns);
		kkey = kदो_स्मृति(klen, GFP_KERNEL);
		अगर (!kkey) अणु
			kमुक्त(apqns);
			वापस -ENOMEM;
		पूर्ण
		rc = pkey_clr2seckey2(apqns, kcs.apqn_entries,
				      kcs.type, kcs.size, kcs.keygenflags,
				      kcs.clrkey.clrkey, kkey, &klen);
		DEBUG_DBG("%s pkey_clr2seckey2()=%d\n", __func__, rc);
		kमुक्त(apqns);
		अगर (rc) अणु
			kमुक्त(kkey);
			अवरोध;
		पूर्ण
		अगर (kcs.key) अणु
			अगर (kcs.keylen < klen) अणु
				kमुक्त(kkey);
				वापस -EINVAL;
			पूर्ण
			अगर (copy_to_user(kcs.key, kkey, klen)) अणु
				kमुक्त(kkey);
				वापस -EFAULT;
			पूर्ण
		पूर्ण
		kcs.keylen = klen;
		अगर (copy_to_user(ucs, &kcs, माप(kcs)))
			rc = -EFAULT;
		memzero_explicit(&kcs, माप(kcs));
		kमुक्त(kkey);
		अवरोध;
	पूर्ण
	हाल PKEY_VERIFYKEY2: अणु
		काष्ठा pkey_verअगरykey2 __user *uvk = (व्योम __user *) arg;
		काष्ठा pkey_verअगरykey2 kvk;
		u8 *kkey;

		अगर (copy_from_user(&kvk, uvk, माप(kvk)))
			वापस -EFAULT;
		kkey = _copy_key_from_user(kvk.key, kvk.keylen);
		अगर (IS_ERR(kkey))
			वापस PTR_ERR(kkey);
		rc = pkey_verअगरykey2(kkey, kvk.keylen,
				     &kvk.cardnr, &kvk.करोमुख्य,
				     &kvk.type, &kvk.size, &kvk.flags);
		DEBUG_DBG("%s pkey_verifykey2()=%d\n", __func__, rc);
		kमुक्त(kkey);
		अगर (rc)
			अवरोध;
		अगर (copy_to_user(uvk, &kvk, माप(kvk)))
			वापस -EFAULT;
		अवरोध;
	पूर्ण
	हाल PKEY_KBLOB2PROTK2: अणु
		काष्ठा pkey_kblob2pkey2 __user *utp = (व्योम __user *) arg;
		काष्ठा pkey_kblob2pkey2 ktp;
		काष्ठा pkey_apqn *apqns = शून्य;
		u8 *kkey;

		अगर (copy_from_user(&ktp, utp, माप(ktp)))
			वापस -EFAULT;
		apqns = _copy_apqns_from_user(ktp.apqns, ktp.apqn_entries);
		अगर (IS_ERR(apqns))
			वापस PTR_ERR(apqns);
		kkey = _copy_key_from_user(ktp.key, ktp.keylen);
		अगर (IS_ERR(kkey)) अणु
			kमुक्त(apqns);
			वापस PTR_ERR(kkey);
		पूर्ण
		rc = pkey_keyblob2pkey2(apqns, ktp.apqn_entries,
					kkey, ktp.keylen, &ktp.protkey);
		DEBUG_DBG("%s pkey_keyblob2pkey2()=%d\n", __func__, rc);
		kमुक्त(apqns);
		kमुक्त(kkey);
		अगर (rc)
			अवरोध;
		अगर (copy_to_user(utp, &ktp, माप(ktp)))
			वापस -EFAULT;
		अवरोध;
	पूर्ण
	हाल PKEY_APQNS4K: अणु
		काष्ठा pkey_apqns4key __user *uak = (व्योम __user *) arg;
		काष्ठा pkey_apqns4key kak;
		काष्ठा pkey_apqn *apqns = शून्य;
		माप_प्रकार nr_apqns, len;
		u8 *kkey;

		अगर (copy_from_user(&kak, uak, माप(kak)))
			वापस -EFAULT;
		nr_apqns = kak.apqn_entries;
		अगर (nr_apqns) अणु
			apqns = kदो_स्मृति_array(nr_apqns,
					      माप(काष्ठा pkey_apqn),
					      GFP_KERNEL);
			अगर (!apqns)
				वापस -ENOMEM;
		पूर्ण
		kkey = _copy_key_from_user(kak.key, kak.keylen);
		अगर (IS_ERR(kkey)) अणु
			kमुक्त(apqns);
			वापस PTR_ERR(kkey);
		पूर्ण
		rc = pkey_apqns4key(kkey, kak.keylen, kak.flags,
				    apqns, &nr_apqns);
		DEBUG_DBG("%s pkey_apqns4key()=%d\n", __func__, rc);
		kमुक्त(kkey);
		अगर (rc && rc != -ENOSPC) अणु
			kमुक्त(apqns);
			अवरोध;
		पूर्ण
		अगर (!rc && kak.apqns) अणु
			अगर (nr_apqns > kak.apqn_entries) अणु
				kमुक्त(apqns);
				वापस -EINVAL;
			पूर्ण
			len = nr_apqns * माप(काष्ठा pkey_apqn);
			अगर (len) अणु
				अगर (copy_to_user(kak.apqns, apqns, len)) अणु
					kमुक्त(apqns);
					वापस -EFAULT;
				पूर्ण
			पूर्ण
		पूर्ण
		kak.apqn_entries = nr_apqns;
		अगर (copy_to_user(uak, &kak, माप(kak)))
			rc = -EFAULT;
		kमुक्त(apqns);
		अवरोध;
	पूर्ण
	हाल PKEY_APQNS4KT: अणु
		काष्ठा pkey_apqns4keytype __user *uat = (व्योम __user *) arg;
		काष्ठा pkey_apqns4keytype kat;
		काष्ठा pkey_apqn *apqns = शून्य;
		माप_प्रकार nr_apqns, len;

		अगर (copy_from_user(&kat, uat, माप(kat)))
			वापस -EFAULT;
		nr_apqns = kat.apqn_entries;
		अगर (nr_apqns) अणु
			apqns = kदो_स्मृति_array(nr_apqns,
					      माप(काष्ठा pkey_apqn),
					      GFP_KERNEL);
			अगर (!apqns)
				वापस -ENOMEM;
		पूर्ण
		rc = pkey_apqns4keytype(kat.type, kat.cur_mkvp, kat.alt_mkvp,
					kat.flags, apqns, &nr_apqns);
		DEBUG_DBG("%s pkey_apqns4keytype()=%d\n", __func__, rc);
		अगर (rc && rc != -ENOSPC) अणु
			kमुक्त(apqns);
			अवरोध;
		पूर्ण
		अगर (!rc && kat.apqns) अणु
			अगर (nr_apqns > kat.apqn_entries) अणु
				kमुक्त(apqns);
				वापस -EINVAL;
			पूर्ण
			len = nr_apqns * माप(काष्ठा pkey_apqn);
			अगर (len) अणु
				अगर (copy_to_user(kat.apqns, apqns, len)) अणु
					kमुक्त(apqns);
					वापस -EFAULT;
				पूर्ण
			पूर्ण
		पूर्ण
		kat.apqn_entries = nr_apqns;
		अगर (copy_to_user(uat, &kat, माप(kat)))
			rc = -EFAULT;
		kमुक्त(apqns);
		अवरोध;
	पूर्ण
	हाल PKEY_KBLOB2PROTK3: अणु
		काष्ठा pkey_kblob2pkey3 __user *utp = (व्योम __user *) arg;
		काष्ठा pkey_kblob2pkey3 ktp;
		काष्ठा pkey_apqn *apqns = शून्य;
		u32 protkeylen = PROTKEYBLOBबफ_मानE;
		u8 *kkey, *protkey;

		अगर (copy_from_user(&ktp, utp, माप(ktp)))
			वापस -EFAULT;
		apqns = _copy_apqns_from_user(ktp.apqns, ktp.apqn_entries);
		अगर (IS_ERR(apqns))
			वापस PTR_ERR(apqns);
		kkey = _copy_key_from_user(ktp.key, ktp.keylen);
		अगर (IS_ERR(kkey)) अणु
			kमुक्त(apqns);
			वापस PTR_ERR(kkey);
		पूर्ण
		protkey = kदो_स्मृति(protkeylen, GFP_KERNEL);
		अगर (!protkey) अणु
			kमुक्त(apqns);
			kमुक्त(kkey);
			वापस -ENOMEM;
		पूर्ण
		rc = pkey_keyblob2pkey3(apqns, ktp.apqn_entries, kkey,
					ktp.keylen, &ktp.pkeytype,
					protkey, &protkeylen);
		DEBUG_DBG("%s pkey_keyblob2pkey3()=%d\n", __func__, rc);
		kमुक्त(apqns);
		kमुक्त(kkey);
		अगर (rc) अणु
			kमुक्त(protkey);
			अवरोध;
		पूर्ण
		अगर (ktp.pkey && ktp.pkeylen) अणु
			अगर (protkeylen > ktp.pkeylen) अणु
				kमुक्त(protkey);
				वापस -EINVAL;
			पूर्ण
			अगर (copy_to_user(ktp.pkey, protkey, protkeylen)) अणु
				kमुक्त(protkey);
				वापस -EFAULT;
			पूर्ण
		पूर्ण
		kमुक्त(protkey);
		ktp.pkeylen = protkeylen;
		अगर (copy_to_user(utp, &ktp, माप(ktp)))
			वापस -EFAULT;
		अवरोध;
	पूर्ण
	शेष:
		/* unknown/unsupported ioctl cmd */
		वापस -ENOTTY;
	पूर्ण

	वापस rc;
पूर्ण

/*
 * Sysfs and file io operations
 */

/*
 * Sysfs attribute पढ़ो function क्रम all रक्षित key binary attributes.
 * The implementation can not deal with partial पढ़ोs, because a new अक्रमom
 * रक्षित key blob is generated with each पढ़ो. In हाल of partial पढ़ोs
 * (i.e. off != 0 or count < key blob size) -EINVAL is वापसed.
 */
अटल sमाप_प्रकार pkey_protkey_aes_attr_पढ़ो(u32 keytype, bool is_xts, अक्षर *buf,
					  loff_t off, माप_प्रकार count)
अणु
	काष्ठा protaeskeytoken protkeytoken;
	काष्ठा pkey_protkey protkey;
	पूर्णांक rc;

	अगर (off != 0 || count < माप(protkeytoken))
		वापस -EINVAL;
	अगर (is_xts)
		अगर (count < 2 * माप(protkeytoken))
			वापस -EINVAL;

	स_रखो(&protkeytoken, 0, माप(protkeytoken));
	protkeytoken.type = TOKTYPE_NON_CCA;
	protkeytoken.version = TOKVER_PROTECTED_KEY;
	protkeytoken.keytype = keytype;

	rc = pkey_genprotkey(protkeytoken.keytype, &protkey);
	अगर (rc)
		वापस rc;

	protkeytoken.len = protkey.len;
	स_नकल(&protkeytoken.protkey, &protkey.protkey, protkey.len);

	स_नकल(buf, &protkeytoken, माप(protkeytoken));

	अगर (is_xts) अणु
		rc = pkey_genprotkey(protkeytoken.keytype, &protkey);
		अगर (rc)
			वापस rc;

		protkeytoken.len = protkey.len;
		स_नकल(&protkeytoken.protkey, &protkey.protkey, protkey.len);

		स_नकल(buf + माप(protkeytoken), &protkeytoken,
		       माप(protkeytoken));

		वापस 2 * माप(protkeytoken);
	पूर्ण

	वापस माप(protkeytoken);
पूर्ण

अटल sमाप_प्रकार protkey_aes_128_पढ़ो(काष्ठा file *filp,
				    काष्ठा kobject *kobj,
				    काष्ठा bin_attribute *attr,
				    अक्षर *buf, loff_t off,
				    माप_प्रकार count)
अणु
	वापस pkey_protkey_aes_attr_पढ़ो(PKEY_KEYTYPE_AES_128, false, buf,
					  off, count);
पूर्ण

अटल sमाप_प्रकार protkey_aes_192_पढ़ो(काष्ठा file *filp,
				    काष्ठा kobject *kobj,
				    काष्ठा bin_attribute *attr,
				    अक्षर *buf, loff_t off,
				    माप_प्रकार count)
अणु
	वापस pkey_protkey_aes_attr_पढ़ो(PKEY_KEYTYPE_AES_192, false, buf,
					  off, count);
पूर्ण

अटल sमाप_प्रकार protkey_aes_256_पढ़ो(काष्ठा file *filp,
				    काष्ठा kobject *kobj,
				    काष्ठा bin_attribute *attr,
				    अक्षर *buf, loff_t off,
				    माप_प्रकार count)
अणु
	वापस pkey_protkey_aes_attr_पढ़ो(PKEY_KEYTYPE_AES_256, false, buf,
					  off, count);
पूर्ण

अटल sमाप_प्रकार protkey_aes_128_xts_पढ़ो(काष्ठा file *filp,
					काष्ठा kobject *kobj,
					काष्ठा bin_attribute *attr,
					अक्षर *buf, loff_t off,
					माप_प्रकार count)
अणु
	वापस pkey_protkey_aes_attr_पढ़ो(PKEY_KEYTYPE_AES_128, true, buf,
					  off, count);
पूर्ण

अटल sमाप_प्रकार protkey_aes_256_xts_पढ़ो(काष्ठा file *filp,
					काष्ठा kobject *kobj,
					काष्ठा bin_attribute *attr,
					अक्षर *buf, loff_t off,
					माप_प्रकार count)
अणु
	वापस pkey_protkey_aes_attr_पढ़ो(PKEY_KEYTYPE_AES_256, true, buf,
					  off, count);
पूर्ण

अटल BIN_ATTR_RO(protkey_aes_128, माप(काष्ठा protaeskeytoken));
अटल BIN_ATTR_RO(protkey_aes_192, माप(काष्ठा protaeskeytoken));
अटल BIN_ATTR_RO(protkey_aes_256, माप(काष्ठा protaeskeytoken));
अटल BIN_ATTR_RO(protkey_aes_128_xts, 2 * माप(काष्ठा protaeskeytoken));
अटल BIN_ATTR_RO(protkey_aes_256_xts, 2 * माप(काष्ठा protaeskeytoken));

अटल काष्ठा bin_attribute *protkey_attrs[] = अणु
	&bin_attr_protkey_aes_128,
	&bin_attr_protkey_aes_192,
	&bin_attr_protkey_aes_256,
	&bin_attr_protkey_aes_128_xts,
	&bin_attr_protkey_aes_256_xts,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group protkey_attr_group = अणु
	.name	   = "protkey",
	.bin_attrs = protkey_attrs,
पूर्ण;

/*
 * Sysfs attribute पढ़ो function क्रम all secure key ccadata binary attributes.
 * The implementation can not deal with partial पढ़ोs, because a new अक्रमom
 * रक्षित key blob is generated with each पढ़ो. In हाल of partial पढ़ोs
 * (i.e. off != 0 or count < key blob size) -EINVAL is वापसed.
 */
अटल sमाप_प्रकार pkey_ccadata_aes_attr_पढ़ो(u32 keytype, bool is_xts, अक्षर *buf,
					  loff_t off, माप_प्रकार count)
अणु
	पूर्णांक rc;
	काष्ठा pkey_seckey *seckey = (काष्ठा pkey_seckey *) buf;

	अगर (off != 0 || count < माप(काष्ठा secaeskeytoken))
		वापस -EINVAL;
	अगर (is_xts)
		अगर (count < 2 * माप(काष्ठा secaeskeytoken))
			वापस -EINVAL;

	rc = cca_genseckey(-1, -1, keytype, seckey->seckey);
	अगर (rc)
		वापस rc;

	अगर (is_xts) अणु
		seckey++;
		rc = cca_genseckey(-1, -1, keytype, seckey->seckey);
		अगर (rc)
			वापस rc;

		वापस 2 * माप(काष्ठा secaeskeytoken);
	पूर्ण

	वापस माप(काष्ठा secaeskeytoken);
पूर्ण

अटल sमाप_प्रकार ccadata_aes_128_पढ़ो(काष्ठा file *filp,
				    काष्ठा kobject *kobj,
				    काष्ठा bin_attribute *attr,
				    अक्षर *buf, loff_t off,
				    माप_प्रकार count)
अणु
	वापस pkey_ccadata_aes_attr_पढ़ो(PKEY_KEYTYPE_AES_128, false, buf,
					  off, count);
पूर्ण

अटल sमाप_प्रकार ccadata_aes_192_पढ़ो(काष्ठा file *filp,
				    काष्ठा kobject *kobj,
				    काष्ठा bin_attribute *attr,
				    अक्षर *buf, loff_t off,
				    माप_प्रकार count)
अणु
	वापस pkey_ccadata_aes_attr_पढ़ो(PKEY_KEYTYPE_AES_192, false, buf,
					  off, count);
पूर्ण

अटल sमाप_प्रकार ccadata_aes_256_पढ़ो(काष्ठा file *filp,
				    काष्ठा kobject *kobj,
				    काष्ठा bin_attribute *attr,
				    अक्षर *buf, loff_t off,
				    माप_प्रकार count)
अणु
	वापस pkey_ccadata_aes_attr_पढ़ो(PKEY_KEYTYPE_AES_256, false, buf,
					  off, count);
पूर्ण

अटल sमाप_प्रकार ccadata_aes_128_xts_पढ़ो(काष्ठा file *filp,
					काष्ठा kobject *kobj,
					काष्ठा bin_attribute *attr,
					अक्षर *buf, loff_t off,
					माप_प्रकार count)
अणु
	वापस pkey_ccadata_aes_attr_पढ़ो(PKEY_KEYTYPE_AES_128, true, buf,
					  off, count);
पूर्ण

अटल sमाप_प्रकार ccadata_aes_256_xts_पढ़ो(काष्ठा file *filp,
					काष्ठा kobject *kobj,
					काष्ठा bin_attribute *attr,
					अक्षर *buf, loff_t off,
					माप_प्रकार count)
अणु
	वापस pkey_ccadata_aes_attr_पढ़ो(PKEY_KEYTYPE_AES_256, true, buf,
					  off, count);
पूर्ण

अटल BIN_ATTR_RO(ccadata_aes_128, माप(काष्ठा secaeskeytoken));
अटल BIN_ATTR_RO(ccadata_aes_192, माप(काष्ठा secaeskeytoken));
अटल BIN_ATTR_RO(ccadata_aes_256, माप(काष्ठा secaeskeytoken));
अटल BIN_ATTR_RO(ccadata_aes_128_xts, 2 * माप(काष्ठा secaeskeytoken));
अटल BIN_ATTR_RO(ccadata_aes_256_xts, 2 * माप(काष्ठा secaeskeytoken));

अटल काष्ठा bin_attribute *ccadata_attrs[] = अणु
	&bin_attr_ccadata_aes_128,
	&bin_attr_ccadata_aes_192,
	&bin_attr_ccadata_aes_256,
	&bin_attr_ccadata_aes_128_xts,
	&bin_attr_ccadata_aes_256_xts,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group ccadata_attr_group = अणु
	.name	   = "ccadata",
	.bin_attrs = ccadata_attrs,
पूर्ण;

#घोषणा CCACIPHERTOKENSIZE	(माप(काष्ठा cipherkeytoken) + 80)

/*
 * Sysfs attribute पढ़ो function क्रम all secure key ccacipher binary attributes.
 * The implementation can not deal with partial पढ़ोs, because a new अक्रमom
 * secure key blob is generated with each पढ़ो. In हाल of partial पढ़ोs
 * (i.e. off != 0 or count < key blob size) -EINVAL is वापसed.
 */
अटल sमाप_प्रकार pkey_ccacipher_aes_attr_पढ़ो(क्रमागत pkey_key_size keybits,
					    bool is_xts, अक्षर *buf, loff_t off,
					    माप_प्रकार count)
अणु
	पूर्णांक i, rc, card, करोm;
	u32 nr_apqns, *apqns = शून्य;
	माप_प्रकार keysize = CCACIPHERTOKENSIZE;

	अगर (off != 0 || count < CCACIPHERTOKENSIZE)
		वापस -EINVAL;
	अगर (is_xts)
		अगर (count < 2 * CCACIPHERTOKENSIZE)
			वापस -EINVAL;

	/* build a list of apqns able to generate an cipher key */
	rc = cca_findcard2(&apqns, &nr_apqns, 0xFFFF, 0xFFFF,
			   ZCRYPT_CEX6, 0, 0, 0, 0);
	अगर (rc)
		वापस rc;

	स_रखो(buf, 0, is_xts ? 2 * keysize : keysize);

	/* simple try all apqns from the list */
	क्रम (i = 0, rc = -ENODEV; i < nr_apqns; i++) अणु
		card = apqns[i] >> 16;
		करोm = apqns[i] & 0xFFFF;
		rc = cca_gencipherkey(card, करोm, keybits, 0, buf, &keysize);
		अगर (rc == 0)
			अवरोध;
	पूर्ण
	अगर (rc)
		वापस rc;

	अगर (is_xts) अणु
		keysize = CCACIPHERTOKENSIZE;
		buf += CCACIPHERTOKENSIZE;
		rc = cca_gencipherkey(card, करोm, keybits, 0, buf, &keysize);
		अगर (rc == 0)
			वापस 2 * CCACIPHERTOKENSIZE;
	पूर्ण

	वापस CCACIPHERTOKENSIZE;
पूर्ण

अटल sमाप_प्रकार ccacipher_aes_128_पढ़ो(काष्ठा file *filp,
				      काष्ठा kobject *kobj,
				      काष्ठा bin_attribute *attr,
				      अक्षर *buf, loff_t off,
				      माप_प्रकार count)
अणु
	वापस pkey_ccacipher_aes_attr_पढ़ो(PKEY_SIZE_AES_128, false, buf,
					    off, count);
पूर्ण

अटल sमाप_प्रकार ccacipher_aes_192_पढ़ो(काष्ठा file *filp,
				      काष्ठा kobject *kobj,
				      काष्ठा bin_attribute *attr,
				      अक्षर *buf, loff_t off,
				      माप_प्रकार count)
अणु
	वापस pkey_ccacipher_aes_attr_पढ़ो(PKEY_SIZE_AES_192, false, buf,
					    off, count);
पूर्ण

अटल sमाप_प्रकार ccacipher_aes_256_पढ़ो(काष्ठा file *filp,
				      काष्ठा kobject *kobj,
				      काष्ठा bin_attribute *attr,
				      अक्षर *buf, loff_t off,
				      माप_प्रकार count)
अणु
	वापस pkey_ccacipher_aes_attr_पढ़ो(PKEY_SIZE_AES_256, false, buf,
					    off, count);
पूर्ण

अटल sमाप_प्रकार ccacipher_aes_128_xts_पढ़ो(काष्ठा file *filp,
					  काष्ठा kobject *kobj,
					  काष्ठा bin_attribute *attr,
					  अक्षर *buf, loff_t off,
					  माप_प्रकार count)
अणु
	वापस pkey_ccacipher_aes_attr_पढ़ो(PKEY_SIZE_AES_128, true, buf,
					    off, count);
पूर्ण

अटल sमाप_प्रकार ccacipher_aes_256_xts_पढ़ो(काष्ठा file *filp,
					  काष्ठा kobject *kobj,
					  काष्ठा bin_attribute *attr,
					  अक्षर *buf, loff_t off,
					  माप_प्रकार count)
अणु
	वापस pkey_ccacipher_aes_attr_पढ़ो(PKEY_SIZE_AES_256, true, buf,
					    off, count);
पूर्ण

अटल BIN_ATTR_RO(ccacipher_aes_128, CCACIPHERTOKENSIZE);
अटल BIN_ATTR_RO(ccacipher_aes_192, CCACIPHERTOKENSIZE);
अटल BIN_ATTR_RO(ccacipher_aes_256, CCACIPHERTOKENSIZE);
अटल BIN_ATTR_RO(ccacipher_aes_128_xts, 2 * CCACIPHERTOKENSIZE);
अटल BIN_ATTR_RO(ccacipher_aes_256_xts, 2 * CCACIPHERTOKENSIZE);

अटल काष्ठा bin_attribute *ccacipher_attrs[] = अणु
	&bin_attr_ccacipher_aes_128,
	&bin_attr_ccacipher_aes_192,
	&bin_attr_ccacipher_aes_256,
	&bin_attr_ccacipher_aes_128_xts,
	&bin_attr_ccacipher_aes_256_xts,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group ccacipher_attr_group = अणु
	.name	   = "ccacipher",
	.bin_attrs = ccacipher_attrs,
पूर्ण;

/*
 * Sysfs attribute पढ़ो function क्रम all ep11 aes key binary attributes.
 * The implementation can not deal with partial पढ़ोs, because a new अक्रमom
 * secure key blob is generated with each पढ़ो. In हाल of partial पढ़ोs
 * (i.e. off != 0 or count < key blob size) -EINVAL is वापसed.
 * This function and the sysfs attributes using it provide EP11 key blobs
 * padded to the upper limit of MAXEP11AESKEYBLOBSIZE which is currently
 * 320 bytes.
 */
अटल sमाप_प्रकार pkey_ep11_aes_attr_पढ़ो(क्रमागत pkey_key_size keybits,
				       bool is_xts, अक्षर *buf, loff_t off,
				       माप_प्रकार count)
अणु
	पूर्णांक i, rc, card, करोm;
	u32 nr_apqns, *apqns = शून्य;
	माप_प्रकार keysize = MAXEP11AESKEYBLOBSIZE;

	अगर (off != 0 || count < MAXEP11AESKEYBLOBSIZE)
		वापस -EINVAL;
	अगर (is_xts)
		अगर (count < 2 * MAXEP11AESKEYBLOBSIZE)
			वापस -EINVAL;

	/* build a list of apqns able to generate an cipher key */
	rc = ep11_findcard2(&apqns, &nr_apqns, 0xFFFF, 0xFFFF,
			    ZCRYPT_CEX7, EP11_API_V, शून्य);
	अगर (rc)
		वापस rc;

	स_रखो(buf, 0, is_xts ? 2 * keysize : keysize);

	/* simple try all apqns from the list */
	क्रम (i = 0, rc = -ENODEV; i < nr_apqns; i++) अणु
		card = apqns[i] >> 16;
		करोm = apqns[i] & 0xFFFF;
		rc = ep11_genaeskey(card, करोm, keybits, 0, buf, &keysize);
		अगर (rc == 0)
			अवरोध;
	पूर्ण
	अगर (rc)
		वापस rc;

	अगर (is_xts) अणु
		keysize = MAXEP11AESKEYBLOBSIZE;
		buf += MAXEP11AESKEYBLOBSIZE;
		rc = ep11_genaeskey(card, करोm, keybits, 0, buf, &keysize);
		अगर (rc == 0)
			वापस 2 * MAXEP11AESKEYBLOBSIZE;
	पूर्ण

	वापस MAXEP11AESKEYBLOBSIZE;
पूर्ण

अटल sमाप_प्रकार ep11_aes_128_पढ़ो(काष्ठा file *filp,
				 काष्ठा kobject *kobj,
				 काष्ठा bin_attribute *attr,
				 अक्षर *buf, loff_t off,
				 माप_प्रकार count)
अणु
	वापस pkey_ep11_aes_attr_पढ़ो(PKEY_SIZE_AES_128, false, buf,
				       off, count);
पूर्ण

अटल sमाप_प्रकार ep11_aes_192_पढ़ो(काष्ठा file *filp,
				 काष्ठा kobject *kobj,
				 काष्ठा bin_attribute *attr,
				 अक्षर *buf, loff_t off,
				 माप_प्रकार count)
अणु
	वापस pkey_ep11_aes_attr_पढ़ो(PKEY_SIZE_AES_192, false, buf,
				       off, count);
पूर्ण

अटल sमाप_प्रकार ep11_aes_256_पढ़ो(काष्ठा file *filp,
				 काष्ठा kobject *kobj,
				 काष्ठा bin_attribute *attr,
				 अक्षर *buf, loff_t off,
				 माप_प्रकार count)
अणु
	वापस pkey_ep11_aes_attr_पढ़ो(PKEY_SIZE_AES_256, false, buf,
				       off, count);
पूर्ण

अटल sमाप_प्रकार ep11_aes_128_xts_पढ़ो(काष्ठा file *filp,
				     काष्ठा kobject *kobj,
				     काष्ठा bin_attribute *attr,
				     अक्षर *buf, loff_t off,
				     माप_प्रकार count)
अणु
	वापस pkey_ep11_aes_attr_पढ़ो(PKEY_SIZE_AES_128, true, buf,
				       off, count);
पूर्ण

अटल sमाप_प्रकार ep11_aes_256_xts_पढ़ो(काष्ठा file *filp,
				     काष्ठा kobject *kobj,
				     काष्ठा bin_attribute *attr,
				     अक्षर *buf, loff_t off,
				     माप_प्रकार count)
अणु
	वापस pkey_ep11_aes_attr_पढ़ो(PKEY_SIZE_AES_256, true, buf,
				       off, count);
पूर्ण

अटल BIN_ATTR_RO(ep11_aes_128, MAXEP11AESKEYBLOBSIZE);
अटल BIN_ATTR_RO(ep11_aes_192, MAXEP11AESKEYBLOBSIZE);
अटल BIN_ATTR_RO(ep11_aes_256, MAXEP11AESKEYBLOBSIZE);
अटल BIN_ATTR_RO(ep11_aes_128_xts, 2 * MAXEP11AESKEYBLOBSIZE);
अटल BIN_ATTR_RO(ep11_aes_256_xts, 2 * MAXEP11AESKEYBLOBSIZE);

अटल काष्ठा bin_attribute *ep11_attrs[] = अणु
	&bin_attr_ep11_aes_128,
	&bin_attr_ep11_aes_192,
	&bin_attr_ep11_aes_256,
	&bin_attr_ep11_aes_128_xts,
	&bin_attr_ep11_aes_256_xts,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group ep11_attr_group = अणु
	.name	   = "ep11",
	.bin_attrs = ep11_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *pkey_attr_groups[] = अणु
	&protkey_attr_group,
	&ccadata_attr_group,
	&ccacipher_attr_group,
	&ep11_attr_group,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा file_operations pkey_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= nonseekable_खोलो,
	.llseek		= no_llseek,
	.unlocked_ioctl = pkey_unlocked_ioctl,
पूर्ण;

अटल काष्ठा miscdevice pkey_dev = अणु
	.name	= "pkey",
	.minor	= MISC_DYNAMIC_MINOR,
	.mode	= 0666,
	.fops	= &pkey_fops,
	.groups = pkey_attr_groups,
पूर्ण;

/*
 * Module init
 */
अटल पूर्णांक __init pkey_init(व्योम)
अणु
	cpacf_mask_t func_mask;

	/*
	 * The pckmo inकाष्ठाion should be available - even अगर we करोn't
	 * actually invoke it. This inकाष्ठाion comes with MSA 3 which
	 * is also the minimum level क्रम the kmc inकाष्ठाions which
	 * are able to work with रक्षित keys.
	 */
	अगर (!cpacf_query(CPACF_PCKMO, &func_mask))
		वापस -ENODEV;

	/* check क्रम kmc inकाष्ठाions available */
	अगर (!cpacf_query(CPACF_KMC, &func_mask))
		वापस -ENODEV;
	अगर (!cpacf_test_func(&func_mask, CPACF_KMC_PAES_128) ||
	    !cpacf_test_func(&func_mask, CPACF_KMC_PAES_192) ||
	    !cpacf_test_func(&func_mask, CPACF_KMC_PAES_256))
		वापस -ENODEV;

	pkey_debug_init();

	वापस misc_रेजिस्टर(&pkey_dev);
पूर्ण

/*
 * Module निकास
 */
अटल व्योम __निकास pkey_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&pkey_dev);
	pkey_debug_निकास();
पूर्ण

module_cpu_feature_match(MSA, pkey_init);
module_निकास(pkey_निकास);
