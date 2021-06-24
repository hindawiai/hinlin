<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * xfrm algorithm पूर्णांकerface
 *
 * Copyright (c) 2002 James Morris <jmorris@पूर्णांकercode.com.au>
 */

#समावेश <crypto/hash.h>
#समावेश <crypto/skcipher.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pfkeyv2.h>
#समावेश <linux/crypto.h>
#समावेश <linux/scatterlist.h>
#समावेश <net/xfrm.h>
#अगर IS_ENABLED(CONFIG_INET_ESP) || IS_ENABLED(CONFIG_INET6_ESP)
#समावेश <net/esp.h>
#पूर्ण_अगर

/*
 * Algorithms supported by IPsec.  These entries contain properties which
 * are used in key negotiation and xfrm processing, and are used to verअगरy
 * that instantiated crypto transक्रमms have correct parameters क्रम IPsec
 * purposes.
 */
अटल काष्ठा xfrm_algo_desc aead_list[] = अणु
अणु
	.name = "rfc4106(gcm(aes))",

	.uinfo = अणु
		.aead = अणु
			.geniv = "seqiv",
			.icv_truncbits = 64,
		पूर्ण
	पूर्ण,

	.pfkey_supported = 1,

	.desc = अणु
		.sadb_alg_id = SADB_X_EALG_AES_GCM_ICV8,
		.sadb_alg_ivlen = 8,
		.sadb_alg_minbits = 128,
		.sadb_alg_maxbits = 256
	पूर्ण
पूर्ण,
अणु
	.name = "rfc4106(gcm(aes))",

	.uinfo = अणु
		.aead = अणु
			.geniv = "seqiv",
			.icv_truncbits = 96,
		पूर्ण
	पूर्ण,

	.pfkey_supported = 1,

	.desc = अणु
		.sadb_alg_id = SADB_X_EALG_AES_GCM_ICV12,
		.sadb_alg_ivlen = 8,
		.sadb_alg_minbits = 128,
		.sadb_alg_maxbits = 256
	पूर्ण
पूर्ण,
अणु
	.name = "rfc4106(gcm(aes))",

	.uinfo = अणु
		.aead = अणु
			.geniv = "seqiv",
			.icv_truncbits = 128,
		पूर्ण
	पूर्ण,

	.pfkey_supported = 1,

	.desc = अणु
		.sadb_alg_id = SADB_X_EALG_AES_GCM_ICV16,
		.sadb_alg_ivlen = 8,
		.sadb_alg_minbits = 128,
		.sadb_alg_maxbits = 256
	पूर्ण
पूर्ण,
अणु
	.name = "rfc4309(ccm(aes))",

	.uinfo = अणु
		.aead = अणु
			.geniv = "seqiv",
			.icv_truncbits = 64,
		पूर्ण
	पूर्ण,

	.pfkey_supported = 1,

	.desc = अणु
		.sadb_alg_id = SADB_X_EALG_AES_CCM_ICV8,
		.sadb_alg_ivlen = 8,
		.sadb_alg_minbits = 128,
		.sadb_alg_maxbits = 256
	पूर्ण
पूर्ण,
अणु
	.name = "rfc4309(ccm(aes))",

	.uinfo = अणु
		.aead = अणु
			.geniv = "seqiv",
			.icv_truncbits = 96,
		पूर्ण
	पूर्ण,

	.pfkey_supported = 1,

	.desc = अणु
		.sadb_alg_id = SADB_X_EALG_AES_CCM_ICV12,
		.sadb_alg_ivlen = 8,
		.sadb_alg_minbits = 128,
		.sadb_alg_maxbits = 256
	पूर्ण
पूर्ण,
अणु
	.name = "rfc4309(ccm(aes))",

	.uinfo = अणु
		.aead = अणु
			.geniv = "seqiv",
			.icv_truncbits = 128,
		पूर्ण
	पूर्ण,

	.pfkey_supported = 1,

	.desc = अणु
		.sadb_alg_id = SADB_X_EALG_AES_CCM_ICV16,
		.sadb_alg_ivlen = 8,
		.sadb_alg_minbits = 128,
		.sadb_alg_maxbits = 256
	पूर्ण
पूर्ण,
अणु
	.name = "rfc4543(gcm(aes))",

	.uinfo = अणु
		.aead = अणु
			.geniv = "seqiv",
			.icv_truncbits = 128,
		पूर्ण
	पूर्ण,

	.pfkey_supported = 1,

	.desc = अणु
		.sadb_alg_id = SADB_X_EALG_शून्य_AES_GMAC,
		.sadb_alg_ivlen = 8,
		.sadb_alg_minbits = 128,
		.sadb_alg_maxbits = 256
	पूर्ण
पूर्ण,
अणु
	.name = "rfc7539esp(chacha20,poly1305)",

	.uinfo = अणु
		.aead = अणु
			.geniv = "seqiv",
			.icv_truncbits = 128,
		पूर्ण
	पूर्ण,

	.pfkey_supported = 0,
पूर्ण,
पूर्ण;

अटल काष्ठा xfrm_algo_desc aalg_list[] = अणु
अणु
	.name = "digest_null",

	.uinfo = अणु
		.auth = अणु
			.icv_truncbits = 0,
			.icv_fullbits = 0,
		पूर्ण
	पूर्ण,

	.pfkey_supported = 1,

	.desc = अणु
		.sadb_alg_id = SADB_X_AALG_शून्य,
		.sadb_alg_ivlen = 0,
		.sadb_alg_minbits = 0,
		.sadb_alg_maxbits = 0
	पूर्ण
पूर्ण,
अणु
	.name = "hmac(md5)",
	.compat = "md5",

	.uinfo = अणु
		.auth = अणु
			.icv_truncbits = 96,
			.icv_fullbits = 128,
		पूर्ण
	पूर्ण,

	.pfkey_supported = 1,

	.desc = अणु
		.sadb_alg_id = SADB_AALG_MD5HMAC,
		.sadb_alg_ivlen = 0,
		.sadb_alg_minbits = 128,
		.sadb_alg_maxbits = 128
	पूर्ण
पूर्ण,
अणु
	.name = "hmac(sha1)",
	.compat = "sha1",

	.uinfo = अणु
		.auth = अणु
			.icv_truncbits = 96,
			.icv_fullbits = 160,
		पूर्ण
	पूर्ण,

	.pfkey_supported = 1,

	.desc = अणु
		.sadb_alg_id = SADB_AALG_SHA1HMAC,
		.sadb_alg_ivlen = 0,
		.sadb_alg_minbits = 160,
		.sadb_alg_maxbits = 160
	पूर्ण
पूर्ण,
अणु
	.name = "hmac(sha256)",
	.compat = "sha256",

	.uinfo = अणु
		.auth = अणु
			.icv_truncbits = 96,
			.icv_fullbits = 256,
		पूर्ण
	पूर्ण,

	.pfkey_supported = 1,

	.desc = अणु
		.sadb_alg_id = SADB_X_AALG_SHA2_256HMAC,
		.sadb_alg_ivlen = 0,
		.sadb_alg_minbits = 256,
		.sadb_alg_maxbits = 256
	पूर्ण
पूर्ण,
अणु
	.name = "hmac(sha384)",

	.uinfo = अणु
		.auth = अणु
			.icv_truncbits = 192,
			.icv_fullbits = 384,
		पूर्ण
	पूर्ण,

	.pfkey_supported = 1,

	.desc = अणु
		.sadb_alg_id = SADB_X_AALG_SHA2_384HMAC,
		.sadb_alg_ivlen = 0,
		.sadb_alg_minbits = 384,
		.sadb_alg_maxbits = 384
	पूर्ण
पूर्ण,
अणु
	.name = "hmac(sha512)",

	.uinfo = अणु
		.auth = अणु
			.icv_truncbits = 256,
			.icv_fullbits = 512,
		पूर्ण
	पूर्ण,

	.pfkey_supported = 1,

	.desc = अणु
		.sadb_alg_id = SADB_X_AALG_SHA2_512HMAC,
		.sadb_alg_ivlen = 0,
		.sadb_alg_minbits = 512,
		.sadb_alg_maxbits = 512
	पूर्ण
पूर्ण,
अणु
	.name = "hmac(rmd160)",
	.compat = "rmd160",

	.uinfo = अणु
		.auth = अणु
			.icv_truncbits = 96,
			.icv_fullbits = 160,
		पूर्ण
	पूर्ण,

	.pfkey_supported = 1,

	.desc = अणु
		.sadb_alg_id = SADB_X_AALG_RIPEMD160HMAC,
		.sadb_alg_ivlen = 0,
		.sadb_alg_minbits = 160,
		.sadb_alg_maxbits = 160
	पूर्ण
पूर्ण,
अणु
	.name = "xcbc(aes)",

	.uinfo = अणु
		.auth = अणु
			.icv_truncbits = 96,
			.icv_fullbits = 128,
		पूर्ण
	पूर्ण,

	.pfkey_supported = 1,

	.desc = अणु
		.sadb_alg_id = SADB_X_AALG_AES_XCBC_MAC,
		.sadb_alg_ivlen = 0,
		.sadb_alg_minbits = 128,
		.sadb_alg_maxbits = 128
	पूर्ण
पूर्ण,
अणु
	/* rfc4494 */
	.name = "cmac(aes)",

	.uinfo = अणु
		.auth = अणु
			.icv_truncbits = 96,
			.icv_fullbits = 128,
		पूर्ण
	पूर्ण,

	.pfkey_supported = 0,
पूर्ण,
पूर्ण;

अटल काष्ठा xfrm_algo_desc ealg_list[] = अणु
अणु
	.name = "ecb(cipher_null)",
	.compat = "cipher_null",

	.uinfo = अणु
		.encr = अणु
			.blockbits = 8,
			.defkeybits = 0,
		पूर्ण
	पूर्ण,

	.pfkey_supported = 1,

	.desc = अणु
		.sadb_alg_id =	SADB_EALG_शून्य,
		.sadb_alg_ivlen = 0,
		.sadb_alg_minbits = 0,
		.sadb_alg_maxbits = 0
	पूर्ण
पूर्ण,
अणु
	.name = "cbc(des)",
	.compat = "des",

	.uinfo = अणु
		.encr = अणु
			.geniv = "echainiv",
			.blockbits = 64,
			.defkeybits = 64,
		पूर्ण
	पूर्ण,

	.pfkey_supported = 1,

	.desc = अणु
		.sadb_alg_id = SADB_EALG_DESCBC,
		.sadb_alg_ivlen = 8,
		.sadb_alg_minbits = 64,
		.sadb_alg_maxbits = 64
	पूर्ण
पूर्ण,
अणु
	.name = "cbc(des3_ede)",
	.compat = "des3_ede",

	.uinfo = अणु
		.encr = अणु
			.geniv = "echainiv",
			.blockbits = 64,
			.defkeybits = 192,
		पूर्ण
	पूर्ण,

	.pfkey_supported = 1,

	.desc = अणु
		.sadb_alg_id = SADB_EALG_3DESCBC,
		.sadb_alg_ivlen = 8,
		.sadb_alg_minbits = 192,
		.sadb_alg_maxbits = 192
	पूर्ण
पूर्ण,
अणु
	.name = "cbc(cast5)",
	.compat = "cast5",

	.uinfo = अणु
		.encr = अणु
			.geniv = "echainiv",
			.blockbits = 64,
			.defkeybits = 128,
		पूर्ण
	पूर्ण,

	.pfkey_supported = 1,

	.desc = अणु
		.sadb_alg_id = SADB_X_EALG_CASTCBC,
		.sadb_alg_ivlen = 8,
		.sadb_alg_minbits = 40,
		.sadb_alg_maxbits = 128
	पूर्ण
पूर्ण,
अणु
	.name = "cbc(blowfish)",
	.compat = "blowfish",

	.uinfo = अणु
		.encr = अणु
			.geniv = "echainiv",
			.blockbits = 64,
			.defkeybits = 128,
		पूर्ण
	पूर्ण,

	.pfkey_supported = 1,

	.desc = अणु
		.sadb_alg_id = SADB_X_EALG_BLOWFISHCBC,
		.sadb_alg_ivlen = 8,
		.sadb_alg_minbits = 40,
		.sadb_alg_maxbits = 448
	पूर्ण
पूर्ण,
अणु
	.name = "cbc(aes)",
	.compat = "aes",

	.uinfo = अणु
		.encr = अणु
			.geniv = "echainiv",
			.blockbits = 128,
			.defkeybits = 128,
		पूर्ण
	पूर्ण,

	.pfkey_supported = 1,

	.desc = अणु
		.sadb_alg_id = SADB_X_EALG_AESCBC,
		.sadb_alg_ivlen = 8,
		.sadb_alg_minbits = 128,
		.sadb_alg_maxbits = 256
	पूर्ण
पूर्ण,
अणु
	.name = "cbc(serpent)",
	.compat = "serpent",

	.uinfo = अणु
		.encr = अणु
			.geniv = "echainiv",
			.blockbits = 128,
			.defkeybits = 128,
		पूर्ण
	पूर्ण,

	.pfkey_supported = 1,

	.desc = अणु
		.sadb_alg_id = SADB_X_EALG_SERPENTCBC,
		.sadb_alg_ivlen = 8,
		.sadb_alg_minbits = 128,
		.sadb_alg_maxbits = 256,
	पूर्ण
पूर्ण,
अणु
	.name = "cbc(camellia)",
	.compat = "camellia",

	.uinfo = अणु
		.encr = अणु
			.geniv = "echainiv",
			.blockbits = 128,
			.defkeybits = 128,
		पूर्ण
	पूर्ण,

	.pfkey_supported = 1,

	.desc = अणु
		.sadb_alg_id = SADB_X_EALG_CAMELLIACBC,
		.sadb_alg_ivlen = 8,
		.sadb_alg_minbits = 128,
		.sadb_alg_maxbits = 256
	पूर्ण
पूर्ण,
अणु
	.name = "cbc(twofish)",
	.compat = "twofish",

	.uinfo = अणु
		.encr = अणु
			.geniv = "echainiv",
			.blockbits = 128,
			.defkeybits = 128,
		पूर्ण
	पूर्ण,

	.pfkey_supported = 1,

	.desc = अणु
		.sadb_alg_id = SADB_X_EALG_TWOFISHCBC,
		.sadb_alg_ivlen = 8,
		.sadb_alg_minbits = 128,
		.sadb_alg_maxbits = 256
	पूर्ण
पूर्ण,
अणु
	.name = "rfc3686(ctr(aes))",

	.uinfo = अणु
		.encr = अणु
			.geniv = "seqiv",
			.blockbits = 128,
			.defkeybits = 160, /* 128-bit key + 32-bit nonce */
		पूर्ण
	पूर्ण,

	.pfkey_supported = 1,

	.desc = अणु
		.sadb_alg_id = SADB_X_EALG_AESCTR,
		.sadb_alg_ivlen	= 8,
		.sadb_alg_minbits = 160,
		.sadb_alg_maxbits = 288
	पूर्ण
पूर्ण,
पूर्ण;

अटल काष्ठा xfrm_algo_desc calg_list[] = अणु
अणु
	.name = "deflate",
	.uinfo = अणु
		.comp = अणु
			.threshold = 90,
		पूर्ण
	पूर्ण,
	.pfkey_supported = 1,
	.desc = अणु .sadb_alg_id = SADB_X_CALG_DEFLATE पूर्ण
पूर्ण,
अणु
	.name = "lzs",
	.uinfo = अणु
		.comp = अणु
			.threshold = 90,
		पूर्ण
	पूर्ण,
	.pfkey_supported = 1,
	.desc = अणु .sadb_alg_id = SADB_X_CALG_LZS पूर्ण
पूर्ण,
अणु
	.name = "lzjh",
	.uinfo = अणु
		.comp = अणु
			.threshold = 50,
		पूर्ण
	पूर्ण,
	.pfkey_supported = 1,
	.desc = अणु .sadb_alg_id = SADB_X_CALG_LZJH पूर्ण
पूर्ण,
पूर्ण;

अटल अंतरभूत पूर्णांक aalg_entries(व्योम)
अणु
	वापस ARRAY_SIZE(aalg_list);
पूर्ण

अटल अंतरभूत पूर्णांक ealg_entries(व्योम)
अणु
	वापस ARRAY_SIZE(ealg_list);
पूर्ण

अटल अंतरभूत पूर्णांक calg_entries(व्योम)
अणु
	वापस ARRAY_SIZE(calg_list);
पूर्ण

काष्ठा xfrm_algo_list अणु
	काष्ठा xfrm_algo_desc *algs;
	पूर्णांक entries;
	u32 type;
	u32 mask;
पूर्ण;

अटल स्थिर काष्ठा xfrm_algo_list xfrm_aead_list = अणु
	.algs = aead_list,
	.entries = ARRAY_SIZE(aead_list),
	.type = CRYPTO_ALG_TYPE_AEAD,
	.mask = CRYPTO_ALG_TYPE_MASK,
पूर्ण;

अटल स्थिर काष्ठा xfrm_algo_list xfrm_aalg_list = अणु
	.algs = aalg_list,
	.entries = ARRAY_SIZE(aalg_list),
	.type = CRYPTO_ALG_TYPE_HASH,
	.mask = CRYPTO_ALG_TYPE_HASH_MASK,
पूर्ण;

अटल स्थिर काष्ठा xfrm_algo_list xfrm_ealg_list = अणु
	.algs = ealg_list,
	.entries = ARRAY_SIZE(ealg_list),
	.type = CRYPTO_ALG_TYPE_SKCIPHER,
	.mask = CRYPTO_ALG_TYPE_MASK,
पूर्ण;

अटल स्थिर काष्ठा xfrm_algo_list xfrm_calg_list = अणु
	.algs = calg_list,
	.entries = ARRAY_SIZE(calg_list),
	.type = CRYPTO_ALG_TYPE_COMPRESS,
	.mask = CRYPTO_ALG_TYPE_MASK,
पूर्ण;

अटल काष्ठा xfrm_algo_desc *xfrm_find_algo(
	स्थिर काष्ठा xfrm_algo_list *algo_list,
	पूर्णांक match(स्थिर काष्ठा xfrm_algo_desc *entry, स्थिर व्योम *data),
	स्थिर व्योम *data, पूर्णांक probe)
अणु
	काष्ठा xfrm_algo_desc *list = algo_list->algs;
	पूर्णांक i, status;

	क्रम (i = 0; i < algo_list->entries; i++) अणु
		अगर (!match(list + i, data))
			जारी;

		अगर (list[i].available)
			वापस &list[i];

		अगर (!probe)
			अवरोध;

		status = crypto_has_alg(list[i].name, algo_list->type,
					algo_list->mask);
		अगर (!status)
			अवरोध;

		list[i].available = status;
		वापस &list[i];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक xfrm_alg_id_match(स्थिर काष्ठा xfrm_algo_desc *entry,
			     स्थिर व्योम *data)
अणु
	वापस entry->desc.sadb_alg_id == (अचिन्हित दीर्घ)data;
पूर्ण

काष्ठा xfrm_algo_desc *xfrm_aalg_get_byid(पूर्णांक alg_id)
अणु
	वापस xfrm_find_algo(&xfrm_aalg_list, xfrm_alg_id_match,
			      (व्योम *)(अचिन्हित दीर्घ)alg_id, 1);
पूर्ण
EXPORT_SYMBOL_GPL(xfrm_aalg_get_byid);

काष्ठा xfrm_algo_desc *xfrm_ealg_get_byid(पूर्णांक alg_id)
अणु
	वापस xfrm_find_algo(&xfrm_ealg_list, xfrm_alg_id_match,
			      (व्योम *)(अचिन्हित दीर्घ)alg_id, 1);
पूर्ण
EXPORT_SYMBOL_GPL(xfrm_ealg_get_byid);

काष्ठा xfrm_algo_desc *xfrm_calg_get_byid(पूर्णांक alg_id)
अणु
	वापस xfrm_find_algo(&xfrm_calg_list, xfrm_alg_id_match,
			      (व्योम *)(अचिन्हित दीर्घ)alg_id, 1);
पूर्ण
EXPORT_SYMBOL_GPL(xfrm_calg_get_byid);

अटल पूर्णांक xfrm_alg_name_match(स्थिर काष्ठा xfrm_algo_desc *entry,
			       स्थिर व्योम *data)
अणु
	स्थिर अक्षर *name = data;

	वापस name && (!म_भेद(name, entry->name) ||
			(entry->compat && !म_भेद(name, entry->compat)));
पूर्ण

काष्ठा xfrm_algo_desc *xfrm_aalg_get_byname(स्थिर अक्षर *name, पूर्णांक probe)
अणु
	वापस xfrm_find_algo(&xfrm_aalg_list, xfrm_alg_name_match, name,
			      probe);
पूर्ण
EXPORT_SYMBOL_GPL(xfrm_aalg_get_byname);

काष्ठा xfrm_algo_desc *xfrm_ealg_get_byname(स्थिर अक्षर *name, पूर्णांक probe)
अणु
	वापस xfrm_find_algo(&xfrm_ealg_list, xfrm_alg_name_match, name,
			      probe);
पूर्ण
EXPORT_SYMBOL_GPL(xfrm_ealg_get_byname);

काष्ठा xfrm_algo_desc *xfrm_calg_get_byname(स्थिर अक्षर *name, पूर्णांक probe)
अणु
	वापस xfrm_find_algo(&xfrm_calg_list, xfrm_alg_name_match, name,
			      probe);
पूर्ण
EXPORT_SYMBOL_GPL(xfrm_calg_get_byname);

काष्ठा xfrm_aead_name अणु
	स्थिर अक्षर *name;
	पूर्णांक icvbits;
पूर्ण;

अटल पूर्णांक xfrm_aead_name_match(स्थिर काष्ठा xfrm_algo_desc *entry,
				स्थिर व्योम *data)
अणु
	स्थिर काष्ठा xfrm_aead_name *aead = data;
	स्थिर अक्षर *name = aead->name;

	वापस aead->icvbits == entry->uinfo.aead.icv_truncbits && name &&
	       !म_भेद(name, entry->name);
पूर्ण

काष्ठा xfrm_algo_desc *xfrm_aead_get_byname(स्थिर अक्षर *name, पूर्णांक icv_len, पूर्णांक probe)
अणु
	काष्ठा xfrm_aead_name data = अणु
		.name = name,
		.icvbits = icv_len,
	पूर्ण;

	वापस xfrm_find_algo(&xfrm_aead_list, xfrm_aead_name_match, &data,
			      probe);
पूर्ण
EXPORT_SYMBOL_GPL(xfrm_aead_get_byname);

काष्ठा xfrm_algo_desc *xfrm_aalg_get_byidx(अचिन्हित पूर्णांक idx)
अणु
	अगर (idx >= aalg_entries())
		वापस शून्य;

	वापस &aalg_list[idx];
पूर्ण
EXPORT_SYMBOL_GPL(xfrm_aalg_get_byidx);

काष्ठा xfrm_algo_desc *xfrm_ealg_get_byidx(अचिन्हित पूर्णांक idx)
अणु
	अगर (idx >= ealg_entries())
		वापस शून्य;

	वापस &ealg_list[idx];
पूर्ण
EXPORT_SYMBOL_GPL(xfrm_ealg_get_byidx);

/*
 * Probe क्रम the availability of crypto algorithms, and set the available
 * flag क्रम any algorithms found on the प्रणाली.  This is typically called by
 * pfkey during userspace SA add, update or रेजिस्टर.
 */
व्योम xfrm_probe_algs(व्योम)
अणु
	पूर्णांक i, status;

	BUG_ON(in_softirq());

	क्रम (i = 0; i < aalg_entries(); i++) अणु
		status = crypto_has_ahash(aalg_list[i].name, 0, 0);
		अगर (aalg_list[i].available != status)
			aalg_list[i].available = status;
	पूर्ण

	क्रम (i = 0; i < ealg_entries(); i++) अणु
		status = crypto_has_skcipher(ealg_list[i].name, 0, 0);
		अगर (ealg_list[i].available != status)
			ealg_list[i].available = status;
	पूर्ण

	क्रम (i = 0; i < calg_entries(); i++) अणु
		status = crypto_has_comp(calg_list[i].name, 0,
					 CRYPTO_ALG_ASYNC);
		अगर (calg_list[i].available != status)
			calg_list[i].available = status;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(xfrm_probe_algs);

पूर्णांक xfrm_count_pfkey_auth_supported(व्योम)
अणु
	पूर्णांक i, n;

	क्रम (i = 0, n = 0; i < aalg_entries(); i++)
		अगर (aalg_list[i].available && aalg_list[i].pfkey_supported)
			n++;
	वापस n;
पूर्ण
EXPORT_SYMBOL_GPL(xfrm_count_pfkey_auth_supported);

पूर्णांक xfrm_count_pfkey_enc_supported(व्योम)
अणु
	पूर्णांक i, n;

	क्रम (i = 0, n = 0; i < ealg_entries(); i++)
		अगर (ealg_list[i].available && ealg_list[i].pfkey_supported)
			n++;
	वापस n;
पूर्ण
EXPORT_SYMBOL_GPL(xfrm_count_pfkey_enc_supported);

MODULE_LICENSE("GPL");
