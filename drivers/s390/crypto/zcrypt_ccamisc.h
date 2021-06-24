<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 *  Copyright IBM Corp. 2019
 *  Author(s): Harald Freudenberger <freude@linux.ibm.com>
 *	       Ingo Franzki <अगरranzki@linux.ibm.com>
 *
 *  Collection of CCA misc functions used by zcrypt and pkey
 */

#अगर_अघोषित _ZCRYPT_CCAMISC_H_
#घोषणा _ZCRYPT_CCAMISC_H_

#समावेश <यंत्र/zcrypt.h>
#समावेश <यंत्र/pkey.h>

/* Key token types */
#घोषणा TOKTYPE_NON_CCA		 0x00 /* Non-CCA key token */
#घोषणा TOKTYPE_CCA_INTERNAL	 0x01 /* CCA पूर्णांकernal sym key token */
#घोषणा TOKTYPE_CCA_INTERNAL_PKA 0x1f /* CCA पूर्णांकernal asym key token */

/* For TOKTYPE_NON_CCA: */
#घोषणा TOKVER_PROTECTED_KEY	0x01 /* Protected key token */
#घोषणा TOKVER_CLEAR_KEY	0x02 /* Clear key token */

/* For TOKTYPE_CCA_INTERNAL: */
#घोषणा TOKVER_CCA_AES		0x04 /* CCA AES key token */
#घोषणा TOKVER_CCA_VLSC		0x05 /* var length sym cipher key token */

/* Max size of a cca variable length cipher key token */
#घोषणा MAXCCAVLSCTOKENSIZE 725

/* header part of a CCA key token */
काष्ठा keytoken_header अणु
	u8  type;     /* one of the TOKTYPE values */
	u8  res0[1];
	u16 len;      /* vlsc token: total length in bytes */
	u8  version;  /* one of the TOKVER values */
	u8  res1[3];
पूर्ण __packed;

/* inside view of a CCA secure key token (only type 0x01 version 0x04) */
काष्ठा secaeskeytoken अणु
	u8  type;     /* 0x01 क्रम पूर्णांकernal key token */
	u8  res0[3];
	u8  version;  /* should be 0x04 */
	u8  res1[1];
	u8  flag;     /* key flags */
	u8  res2[1];
	u64 mkvp;     /* master key verअगरication pattern */
	u8  key[32];  /* key value (encrypted) */
	u8  cv[8];    /* control vector */
	u16 bitsize;  /* key bit size */
	u16 keysize;  /* key byte size */
	u8  tvv[4];   /* token validation value */
पूर्ण __packed;

/* inside view of a variable length symmetric cipher AES key token */
काष्ठा cipherkeytoken अणु
	u8  type;     /* 0x01 क्रम पूर्णांकernal key token */
	u8  res0[1];
	u16 len;      /* total key token length in bytes */
	u8  version;  /* should be 0x05 */
	u8  res1[3];
	u8  kms;      /* key material state, 0x03 means wrapped with MK */
	u8  kvpt;     /* key verअगरication pattern type, should be 0x01 */
	u64 mkvp0;    /* master key verअगरication pattern, lo part */
	u64 mkvp1;    /* master key verअगरication pattern, hi part (unused) */
	u8  eskwm;    /* encrypted section key wrapping method */
	u8  hashalg;  /* hash algorithmus used क्रम wrapping key */
	u8  plfver;   /* pay load क्रमmat version */
	u8  res2[1];
	u8  adsver;   /* associated data section version */
	u8  res3[1];
	u16 adslen;   /* associated data section length */
	u8  kllen;    /* optional key label length */
	u8  ieaslen;  /* optional extended associated data length */
	u8  uadlen;   /* optional user definable associated data length */
	u8  res4[1];
	u16 wpllen;   /* wrapped payload length in bits: */
		      /*   plfver  0x00 0x01		 */
		      /*   AES-128  512  640		 */
		      /*   AES-192  576  640		 */
		      /*   AES-256  640  640		 */
	u8  res5[1];
	u8  algtype;  /* 0x02 क्रम AES cipher */
	u16 keytype;  /* 0x0001 क्रम 'cipher' */
	u8  kufc;     /* key usage field count */
	u16 kuf1;     /* key usage field 1 */
	u16 kuf2;     /* key usage field 2 */
	u8  kmfc;     /* key management field count */
	u16 kmf1;     /* key management field 1 */
	u16 kmf2;     /* key management field 2 */
	u16 kmf3;     /* key management field 3 */
	u8  vdata[]; /* variable part data follows */
पूर्ण __packed;

/* inside view of an CCA secure ECC निजी key */
काष्ठा eccprivkeytoken अणु
	u8  type;     /* 0x1f क्रम पूर्णांकernal asym key token */
	u8  version;  /* should be 0x00 */
	u16 len;      /* total key token length in bytes */
	u8  res1[4];
	u8  secid;    /* 0x20 क्रम ECC priv key section marker */
	u8  secver;   /* section version */
	u16 seclen;   /* section length */
	u8  wtype;    /* wrapping method, 0x00 clear, 0x01 AES */
	u8  htype;    /* hash method, 0x02 क्रम SHA-256 */
	u8  res2[2];
	u8  kutc;     /* key usage and translation control */
	u8  ctype;    /* curve type */
	u8  kfs;      /* key क्रमmat and security */
	u8  ksrc;     /* key source */
	u16 pbitlen;  /* length of prime p in bits */
	u16 ibmadlen; /* IBM associated data length in bytes */
	u64 mkvp;     /* master key verअगरication pattern */
	u8  opk[48];  /* encrypted object protection key data */
	u16 adatalen; /* associated data length in bytes */
	u16 fseclen;  /* क्रमmated section length in bytes */
	u8  more_data[]; /* more data follows */
पूर्ण __packed;

/* Some defines क्रम the CCA AES cipherkeytoken kmf1 field */
#घोषणा KMF1_XPRT_SYM  0x8000
#घोषणा KMF1_XPRT_UASY 0x4000
#घोषणा KMF1_XPRT_AASY 0x2000
#घोषणा KMF1_XPRT_RAW  0x1000
#घोषणा KMF1_XPRT_CPAC 0x0800
#घोषणा KMF1_XPRT_DES  0x0080
#घोषणा KMF1_XPRT_AES  0x0040
#घोषणा KMF1_XPRT_RSA  0x0008

/*
 * Simple check अगर the token is a valid CCA secure AES data key
 * token. If keybitsize is given, the bitsize of the key is
 * also checked. Returns 0 on success or त्रुटि_सं value on failure.
 */
पूर्णांक cca_check_secaeskeytoken(debug_info_t *dbg, पूर्णांक dbflvl,
			     स्थिर u8 *token, पूर्णांक keybitsize);

/*
 * Simple check अगर the token is a valid CCA secure AES cipher key
 * token. If keybitsize is given, the bitsize of the key is
 * also checked. If checkcpacfexport is enabled, the key is also
 * checked क्रम the export flag to allow CPACF export.
 * Returns 0 on success or त्रुटि_सं value on failure.
 */
पूर्णांक cca_check_secaescipherkey(debug_info_t *dbg, पूर्णांक dbflvl,
			      स्थिर u8 *token, पूर्णांक keybitsize,
			      पूर्णांक checkcpacfexport);

/*
 * Simple check अगर the token is a valid CCA secure ECC निजी
 * key token. Returns 0 on success or त्रुटि_सं value on failure.
 */
पूर्णांक cca_check_sececckeytoken(debug_info_t *dbg, पूर्णांक dbflvl,
			     स्थिर u8 *token, माप_प्रकार keysize,
			     पूर्णांक checkcpacfexport);

/*
 * Generate (अक्रमom) CCA AES DATA secure key.
 */
पूर्णांक cca_genseckey(u16 cardnr, u16 करोमुख्य, u32 keybitsize, u8 *seckey);

/*
 * Generate CCA AES DATA secure key with given clear key value.
 */
पूर्णांक cca_clr2seckey(u16 cardnr, u16 करोमुख्य, u32 keybitsize,
		   स्थिर u8 *clrkey, u8 *seckey);

/*
 * Derive proteced key from an CCA AES DATA secure key.
 */
पूर्णांक cca_sec2protkey(u16 cardnr, u16 करोमुख्य,
		    स्थिर u8 seckey[SECKEYBLOBSIZE],
		    u8 *protkey, u32 *protkeylen, u32 *protkeytype);

/*
 * Generate (अक्रमom) CCA AES CIPHER secure key.
 */
पूर्णांक cca_gencipherkey(u16 cardnr, u16 करोमुख्य, u32 keybitsize, u32 keygenflags,
		     u8 *keybuf, माप_प्रकार *keybufsize);

/*
 * Derive proteced key from CCA AES cipher secure key.
 */
पूर्णांक cca_cipher2protkey(u16 cardnr, u16 करोमुख्य, स्थिर u8 *ckey,
		       u8 *protkey, u32 *protkeylen, u32 *protkeytype);

/*
 * Build CCA AES CIPHER secure key with a given clear key value.
 */
पूर्णांक cca_clr2cipherkey(u16 cardnr, u16 करोमुख्य, u32 keybitsize, u32 keygenflags,
		      स्थिर u8 *clrkey, u8 *keybuf, माप_प्रकार *keybufsize);

/*
 * Derive proteced key from CCA ECC secure निजी key.
 */
पूर्णांक cca_ecc2protkey(u16 cardnr, u16 करोमुख्य, स्थिर u8 *key,
		    u8 *protkey, u32 *protkeylen, u32 *protkeytype);

/*
 * Query cryptographic facility from CCA adapter
 */
पूर्णांक cca_query_crypto_facility(u16 cardnr, u16 करोमुख्य,
			      स्थिर अक्षर *keyword,
			      u8 *rarray, माप_प्रकार *rarraylen,
			      u8 *varray, माप_प्रकार *varraylen);

/*
 * Search क्रम a matching crypto card based on the Master Key
 * Verअगरication Pattern provided inside a secure key.
 * Works with CCA AES data and cipher keys.
 * Returns < 0 on failure, 0 अगर CURRENT MKVP matches and
 * 1 अगर OLD MKVP matches.
 */
पूर्णांक cca_findcard(स्थिर u8 *key, u16 *pcardnr, u16 *pकरोमुख्य, पूर्णांक verअगरy);

/*
 * Build a list of cca apqns meeting the following स्थिरrains:
 * - apqn is online and is in fact a CCA apqn
 * - अगर cardnr is not FFFF only apqns with this cardnr
 * - अगर करोमुख्य is not FFFF only apqns with this करोमुख्यnr
 * - अगर minhwtype > 0 only apqns with hwtype >= minhwtype
 * - अगर cur_mkvp != 0 only apqns where cur_mkvp == mkvp
 * - अगर old_mkvp != 0 only apqns where old_mkvp == mkvp
 * - अगर verअगरy is enabled and a cur_mkvp and/or old_mkvp
 *   value is given, then refetch the cca_info and make sure the current
 *   cur_mkvp or old_mkvp values of the apqn are used.
 * The mktype determines which set of master keys to use:
 *   0 = AES_MK_SET - AES MK set, 1 = APKA MK_SET - APKA MK set
 * The array of apqn entries is allocated with kदो_स्मृति and वापसed in *apqns;
 * the number of apqns stored पूर्णांकo the list is वापसed in *nr_apqns. One apqn
 * entry is simple a 32 bit value with 16 bit cardnr and 16 bit करोमुख्य nr and
 * may be casted to काष्ठा pkey_apqn. The वापस value is either 0 क्रम success
 * or a negative त्रुटि_सं value. If no apqn meeting the criterias is found,
 * -ENODEV is वापसed.
 */
पूर्णांक cca_findcard2(u32 **apqns, u32 *nr_apqns, u16 cardnr, u16 करोमुख्य,
		  पूर्णांक minhwtype, पूर्णांक mktype, u64 cur_mkvp, u64 old_mkvp,
		  पूर्णांक verअगरy);

#घोषणा AES_MK_SET  0
#घोषणा APKA_MK_SET 1

/* काष्ठा to hold info क्रम each CCA queue */
काष्ठा cca_info अणु
	पूर्णांक  hwtype;		/* one of the defined AP_DEVICE_TYPE_* */
	अक्षर new_aes_mk_state;	/* '1' empty, '2' partially full, '3' full */
	अक्षर cur_aes_mk_state;	/* '1' invalid, '2' valid */
	अक्षर old_aes_mk_state;	/* '1' invalid, '2' valid */
	अक्षर new_apka_mk_state; /* '1' empty, '2' partially full, '3' full */
	अक्षर cur_apka_mk_state; /* '1' invalid, '2' valid */
	अक्षर old_apka_mk_state; /* '1' invalid, '2' valid */
	u64  new_aes_mkvp;	/* truncated sha256 of new aes master key */
	u64  cur_aes_mkvp;	/* truncated sha256 of current aes master key */
	u64  old_aes_mkvp;	/* truncated sha256 of old aes master key */
	u64  new_apka_mkvp;	/* truncated sha256 of new apka master key */
	u64  cur_apka_mkvp;	/* truncated sha256 of current apka mk */
	u64  old_apka_mkvp;	/* truncated sha256 of old apka mk */
	अक्षर serial[9];		/* serial number (8 ascii numbers + 0x00) */
पूर्ण;

/*
 * Fetch cca inक्रमmation about an CCA queue.
 */
पूर्णांक cca_get_info(u16 card, u16 करोm, काष्ठा cca_info *ci, पूर्णांक verअगरy);

व्योम zcrypt_ccamisc_निकास(व्योम);

#पूर्ण_अगर /* _ZCRYPT_CCAMISC_H_ */
