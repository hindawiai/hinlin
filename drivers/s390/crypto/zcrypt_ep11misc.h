<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 *  Copyright IBM Corp. 2019
 *  Author(s): Harald Freudenberger <freude@linux.ibm.com>
 *
 *  Collection of EP11 misc functions used by zcrypt and pkey
 */

#अगर_अघोषित _ZCRYPT_EP11MISC_H_
#घोषणा _ZCRYPT_EP11MISC_H_

#समावेश <यंत्र/zcrypt.h>
#समावेश <यंत्र/pkey.h>

#घोषणा EP11_API_V 4  /* highest known and supported EP11 API version */
#घोषणा EP11_STRUCT_MAGIC 0x1234
#घोषणा EP11_BLOB_PKEY_EXTRACTABLE 0x00200000

/*
 * Internal used values क्रम the version field of the key header.
 * Should match to the क्रमागत pkey_key_type in pkey.h.
 */
#घोषणा TOKVER_EP11_AES  0x03  /* EP11 AES key blob (old style) */
#घोषणा TOKVER_EP11_AES_WITH_HEADER 0x06 /* EP11 AES key blob with header */
#घोषणा TOKVER_EP11_ECC_WITH_HEADER 0x07 /* EP11 ECC key blob with header */

/* inside view of an EP11 secure key blob */
काष्ठा ep11keyblob अणु
	जोड़ अणु
		u8 session[32];
		/* only used क्रम PKEY_TYPE_EP11: */
		काष्ठा अणु
			u8  type;      /* 0x00 (TOKTYPE_NON_CCA) */
			u8  res0;      /* unused */
			u16 len;       /* total length in bytes of this blob */
			u8  version;   /* 0x03 (TOKVER_EP11_AES) */
			u8  res1;      /* unused */
			u16 keybitlen; /* clear key bit len, 0 क्रम unknown */
		पूर्ण head;
	पूर्ण;
	u8  wkvp[16];  /* wrapping key verअगरication pattern */
	u64 attr;      /* boolean key attributes */
	u64 mode;      /* mode bits */
	u16 version;   /* 0x1234, EP11_STRUCT_MAGIC */
	u8  iv[14];
	u8  encrypted_key_data[144];
	u8  mac[32];
पूर्ण __packed;

/* check ep11 key magic to find out अगर this is an ep11 key blob */
अटल अंतरभूत bool is_ep11_keyblob(स्थिर u8 *key)
अणु
	काष्ठा ep11keyblob *kb = (काष्ठा ep11keyblob *) key;

	वापस (kb->version == EP11_STRUCT_MAGIC);
पूर्ण

/*
 * Simple check अगर the key blob is a valid EP11 AES key blob with header.
 * If checkcpacfexport is enabled, the key is also checked क्रम the
 * attributes needed to export this key क्रम CPACF use.
 * Returns 0 on success or त्रुटि_सं value on failure.
 */
पूर्णांक ep11_check_aes_key_with_hdr(debug_info_t *dbg, पूर्णांक dbflvl,
				स्थिर u8 *key, माप_प्रकार keylen, पूर्णांक checkcpacfexp);

/*
 * Simple check अगर the key blob is a valid EP11 ECC key blob with header.
 * If checkcpacfexport is enabled, the key is also checked क्रम the
 * attributes needed to export this key क्रम CPACF use.
 * Returns 0 on success or त्रुटि_सं value on failure.
 */
पूर्णांक ep11_check_ecc_key_with_hdr(debug_info_t *dbg, पूर्णांक dbflvl,
				स्थिर u8 *key, माप_प्रकार keylen, पूर्णांक checkcpacfexp);

/*
 * Simple check अगर the key blob is a valid EP11 AES key blob with
 * the header in the session field (old style EP11 AES key).
 * If checkcpacfexport is enabled, the key is also checked क्रम the
 * attributes needed to export this key क्रम CPACF use.
 * Returns 0 on success or त्रुटि_सं value on failure.
 */
पूर्णांक ep11_check_aes_key(debug_info_t *dbg, पूर्णांक dbflvl,
		       स्थिर u8 *key, माप_प्रकार keylen, पूर्णांक checkcpacfexp);

/* EP11 card info काष्ठा */
काष्ठा ep11_card_info अणु
	u32  API_ord_nr;    /* API ordinal number */
	u16  FW_version;    /* Firmware major and minor version */
	अक्षर serial[16];    /* serial number string (16 ascii, no 0x00 !) */
	u64  op_mode;	    /* card operational mode(s) */
पूर्ण;

/* EP11 करोमुख्य info काष्ठा */
काष्ठा ep11_करोमुख्य_info अणु
	अक्षर cur_wk_state;  /* '0' invalid, '1' valid */
	अक्षर new_wk_state;  /* '0' empty, '1' uncommitted, '2' committed */
	u8   cur_wkvp[32];  /* current wrapping key verअगरication pattern */
	u8   new_wkvp[32];  /* new wrapping key verअगरication pattern */
	u64  op_mode;	    /* करोमुख्य operational mode(s) */
पूर्ण;

/*
 * Provide inक्रमmation about an EP11 card.
 */
पूर्णांक ep11_get_card_info(u16 card, काष्ठा ep11_card_info *info, पूर्णांक verअगरy);

/*
 * Provide inक्रमmation about a करोमुख्य within an EP11 card.
 */
पूर्णांक ep11_get_करोमुख्य_info(u16 card, u16 करोमुख्य, काष्ठा ep11_करोमुख्य_info *info);

/*
 * Generate (अक्रमom) EP11 AES secure key.
 */
पूर्णांक ep11_genaeskey(u16 card, u16 करोमुख्य, u32 keybitsize, u32 keygenflags,
		   u8 *keybuf, माप_प्रकार *keybufsize);

/*
 * Generate EP11 AES secure key with given clear key value.
 */
पूर्णांक ep11_clr2keyblob(u16 cardnr, u16 करोमुख्य, u32 keybitsize, u32 keygenflags,
		     स्थिर u8 *clrkey, u8 *keybuf, माप_प्रकार *keybufsize);

/*
 * Build a list of ep11 apqns meeting the following स्थिरrains:
 * - apqn is online and is in fact an EP11 apqn
 * - अगर cardnr is not FFFF only apqns with this cardnr
 * - अगर करोमुख्य is not FFFF only apqns with this करोमुख्यnr
 * - अगर minhwtype > 0 only apqns with hwtype >= minhwtype
 * - अगर minapi > 0 only apqns with API_ord_nr >= minapi
 * - अगर wkvp != शून्य only apqns where the wkvp (EP11_WKVPLEN bytes) matches
 *   to the first EP11_WKVPLEN bytes of the wkvp of the current wrapping
 *   key क्रम this करोमुख्य. When a wkvp is given there will aways be a re-fetch
 *   of the करोमुख्य info क्रम the potential apqn - so this triggers an request
 *   reply to each apqn eligible.
 * The array of apqn entries is allocated with kदो_स्मृति and वापसed in *apqns;
 * the number of apqns stored पूर्णांकo the list is वापसed in *nr_apqns. One apqn
 * entry is simple a 32 bit value with 16 bit cardnr and 16 bit करोमुख्य nr and
 * may be casted to काष्ठा pkey_apqn. The वापस value is either 0 क्रम success
 * or a negative त्रुटि_सं value. If no apqn meeting the criterias is found,
 * -ENODEV is वापसed.
 */
पूर्णांक ep11_findcard2(u32 **apqns, u32 *nr_apqns, u16 cardnr, u16 करोमुख्य,
		   पूर्णांक minhwtype, पूर्णांक minapi, स्थिर u8 *wkvp);

/*
 * Derive proteced key from EP11 key blob (AES and ECC keys).
 */
पूर्णांक ep11_kblob2protkey(u16 card, u16 करोm, स्थिर u8 *key, माप_प्रकार keylen,
		       u8 *protkey, u32 *protkeylen, u32 *protkeytype);

व्योम zcrypt_ep11misc_निकास(व्योम);

#पूर्ण_अगर /* _ZCRYPT_EP11MISC_H_ */
