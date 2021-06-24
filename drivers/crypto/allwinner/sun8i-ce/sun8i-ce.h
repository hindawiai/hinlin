<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * sun8i-ce.h - hardware cryptographic offloader क्रम
 * Allwinner H3/A64/H5/H2+/H6 SoC
 *
 * Copyright (C) 2016-2019 Corentin LABBE <clabbe.montjoie@gmail.com>
 */
#समावेश <crypto/aes.h>
#समावेश <crypto/des.h>
#समावेश <crypto/engine.h>
#समावेश <crypto/skcipher.h>
#समावेश <linux/atomic.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/crypto.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/md5.h>
#समावेश <crypto/rng.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>

/* CE Registers */
#घोषणा CE_TDQ	0x00
#घोषणा CE_CTR	0x04
#घोषणा CE_ICR	0x08
#घोषणा CE_ISR	0x0C
#घोषणा CE_TLR	0x10
#घोषणा CE_TSR	0x14
#घोषणा CE_ESR	0x18
#घोषणा CE_CSSGR	0x1C
#घोषणा CE_CDSGR	0x20
#घोषणा CE_CSAR	0x24
#घोषणा CE_CDAR	0x28
#घोषणा CE_TPR	0x2C

/* Used in काष्ठा ce_task */
/* ce_task common */
#घोषणा CE_ENCRYPTION		0
#घोषणा CE_DECRYPTION		BIT(8)

#घोषणा CE_COMM_INT		BIT(31)

/* ce_task symmetric */
#घोषणा CE_AES_128BITS 0
#घोषणा CE_AES_192BITS 1
#घोषणा CE_AES_256BITS 2

#घोषणा CE_OP_ECB	0
#घोषणा CE_OP_CBC	(1 << 8)

#घोषणा CE_ALG_AES		0
#घोषणा CE_ALG_DES		1
#घोषणा CE_ALG_3DES		2
#घोषणा CE_ALG_MD5              16
#घोषणा CE_ALG_SHA1             17
#घोषणा CE_ALG_SHA224           18
#घोषणा CE_ALG_SHA256           19
#घोषणा CE_ALG_SHA384           20
#घोषणा CE_ALG_SHA512           21
#घोषणा CE_ALG_TRNG		48
#घोषणा CE_ALG_PRNG		49
#घोषणा CE_ALG_TRNG_V2		0x1c
#घोषणा CE_ALG_PRNG_V2		0x1d

/* Used in ce_variant */
#घोषणा CE_ID_NOTSUPP		0xFF

#घोषणा CE_ID_CIPHER_AES	0
#घोषणा CE_ID_CIPHER_DES	1
#घोषणा CE_ID_CIPHER_DES3	2
#घोषणा CE_ID_CIPHER_MAX	3

#घोषणा CE_ID_HASH_MD5		0
#घोषणा CE_ID_HASH_SHA1		1
#घोषणा CE_ID_HASH_SHA224	2
#घोषणा CE_ID_HASH_SHA256	3
#घोषणा CE_ID_HASH_SHA384	4
#घोषणा CE_ID_HASH_SHA512	5
#घोषणा CE_ID_HASH_MAX		6

#घोषणा CE_ID_OP_ECB	0
#घोषणा CE_ID_OP_CBC	1
#घोषणा CE_ID_OP_MAX	2

/* Used in CE रेजिस्टरs */
#घोषणा CE_ERR_ALGO_NOTSUP	BIT(0)
#घोषणा CE_ERR_DATALEN		BIT(1)
#घोषणा CE_ERR_KEYSRAM		BIT(2)
#घोषणा CE_ERR_ADDR_INVALID	BIT(5)
#घोषणा CE_ERR_KEYLADDER	BIT(6)

#घोषणा ESR_H3	0
#घोषणा ESR_A64	1
#घोषणा ESR_R40	2
#घोषणा ESR_H5	3
#घोषणा ESR_H6	4

#घोषणा PRNG_DATA_SIZE (160 / 8)
#घोषणा PRNG_SEED_SIZE DIV_ROUND_UP(175, 8)
#घोषणा PRNG_LD BIT(17)

#घोषणा CE_DIE_ID_SHIFT	16
#घोषणा CE_DIE_ID_MASK	0x07

#घोषणा MAX_SG 8

#घोषणा CE_MAX_CLOCKS 3

#घोषणा MAXFLOW 4

/*
 * काष्ठा ce_घड़ी - Describe घड़ीs used by sun8i-ce
 * @name:	Name of घड़ी needed by this variant
 * @freq:	Frequency to set क्रम each घड़ी
 * @max_freq:	Maximum frequency क्रम each घड़ी (generally given by datasheet)
 */
काष्ठा ce_घड़ी अणु
	स्थिर अक्षर *name;
	अचिन्हित दीर्घ freq;
	अचिन्हित दीर्घ max_freq;
पूर्ण;

/*
 * काष्ठा ce_variant - Describe CE capability क्रम each variant hardware
 * @alg_cipher:	list of supported ciphers. क्रम each CE_ID_ this will give the
 *              coresponding CE_ALG_XXX value
 * @alg_hash:	list of supported hashes. क्रम each CE_ID_ this will give the
 *              corresponding CE_ALG_XXX value
 * @op_mode:	list of supported block modes
 * @cipher_t_dlen_in_bytes:	Does the request size क्रम cipher is in
 *				bytes or words
 * @hash_t_dlen_in_bytes:	Does the request size क्रम hash is in
 *				bits or words
 * @prng_t_dlen_in_bytes:	Does the request size क्रम PRNG is in
 *				bytes or words
 * @trng_t_dlen_in_bytes:	Does the request size क्रम TRNG is in
 *				bytes or words
 * @ce_clks:	list of घड़ीs needed by this variant
 * @esr:	The type of error रेजिस्टर
 * @prng:	The CE_ALG_XXX value क्रम the PRNG
 * @trng:	The CE_ALG_XXX value क्रम the TRNG
 */
काष्ठा ce_variant अणु
	अक्षर alg_cipher[CE_ID_CIPHER_MAX];
	अक्षर alg_hash[CE_ID_HASH_MAX];
	u32 op_mode[CE_ID_OP_MAX];
	bool cipher_t_dlen_in_bytes;
	bool hash_t_dlen_in_bits;
	bool prng_t_dlen_in_bytes;
	bool trng_t_dlen_in_bytes;
	काष्ठा ce_घड़ी ce_clks[CE_MAX_CLOCKS];
	पूर्णांक esr;
	अचिन्हित अक्षर prng;
	अचिन्हित अक्षर trng;
पूर्ण;

काष्ठा sginfo अणु
	__le32 addr;
	__le32 len;
पूर्ण __packed;

/*
 * काष्ठा ce_task - CE Task descriptor
 * The काष्ठाure of this descriptor could be found in the datasheet
 */
काष्ठा ce_task अणु
	__le32 t_id;
	__le32 t_common_ctl;
	__le32 t_sym_ctl;
	__le32 t_asym_ctl;
	__le32 t_key;
	__le32 t_iv;
	__le32 t_ctr;
	__le32 t_dlen;
	काष्ठा sginfo t_src[MAX_SG];
	काष्ठा sginfo t_dst[MAX_SG];
	__le32 next;
	__le32 reserved[3];
पूर्ण __packed __aligned(8);

/*
 * काष्ठा sun8i_ce_flow - Inक्रमmation used by each flow
 * @engine:	ptr to the crypto_engine क्रम this flow
 * @complete:	completion क्रम the current task on this flow
 * @status:	set to 1 by पूर्णांकerrupt अगर task is करोne
 * @t_phy:	Physical address of task
 * @tl:		poपूर्णांकer to the current ce_task क्रम this flow
 * @stat_req:	number of request करोne by this flow
 */
काष्ठा sun8i_ce_flow अणु
	काष्ठा crypto_engine *engine;
	काष्ठा completion complete;
	पूर्णांक status;
	dma_addr_t t_phy;
	पूर्णांक समयout;
	काष्ठा ce_task *tl;
#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_CE_DEBUG
	अचिन्हित दीर्घ stat_req;
#पूर्ण_अगर
पूर्ण;

/*
 * काष्ठा sun8i_ce_dev - मुख्य container क्रम all this driver inक्रमmation
 * @base:	base address of CE
 * @ceclks:	घड़ीs used by CE
 * @reset:	poपूर्णांकer to reset controller
 * @dev:	the platक्रमm device
 * @mlock:	Control access to device रेजिस्टरs
 * @rnglock:	Control access to the RNG (dedicated channel 3)
 * @chanlist:	array of all flow
 * @flow:	flow to use in next request
 * @variant:	poपूर्णांकer to variant specअगरic data
 * @dbgfs_dir:	Debugfs dentry क्रम statistic directory
 * @dbgfs_stats: Debugfs dentry क्रम statistic counters
 */
काष्ठा sun8i_ce_dev अणु
	व्योम __iomem *base;
	काष्ठा clk *ceclks[CE_MAX_CLOCKS];
	काष्ठा reset_control *reset;
	काष्ठा device *dev;
	काष्ठा mutex mlock;
	काष्ठा mutex rnglock;
	काष्ठा sun8i_ce_flow *chanlist;
	atomic_t flow;
	स्थिर काष्ठा ce_variant *variant;
#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_CE_DEBUG
	काष्ठा dentry *dbgfs_dir;
	काष्ठा dentry *dbgfs_stats;
#पूर्ण_अगर
#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_CE_TRNG
	काष्ठा hwrng trng;
#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_CE_DEBUG
	अचिन्हित दीर्घ hwrng_stat_req;
	अचिन्हित दीर्घ hwrng_stat_bytes;
#पूर्ण_अगर
#पूर्ण_अगर
पूर्ण;

/*
 * काष्ठा sun8i_cipher_req_ctx - context क्रम a skcipher request
 * @op_dir:		direction (encrypt vs decrypt) क्रम this request
 * @flow:		the flow to use क्रम this request
 * @backup_iv:		buffer which contain the next IV to store
 * @bounce_iv:		buffer which contain the IV
 * @ivlen:		size of bounce_iv
 * @nr_sgs:		The number of source SG (as given by dma_map_sg())
 * @nr_sgd:		The number of destination SG (as given by dma_map_sg())
 * @addr_iv:		The IV addr वापसed by dma_map_single, need to unmap later
 * @addr_key:		The key addr वापसed by dma_map_single, need to unmap later
 * @fallback_req:	request काष्ठा क्रम invoking the fallback skcipher TFM
 */
काष्ठा sun8i_cipher_req_ctx अणु
	u32 op_dir;
	पूर्णांक flow;
	व्योम *backup_iv;
	व्योम *bounce_iv;
	अचिन्हित पूर्णांक ivlen;
	पूर्णांक nr_sgs;
	पूर्णांक nr_sgd;
	dma_addr_t addr_iv;
	dma_addr_t addr_key;
	काष्ठा skcipher_request fallback_req;   // keep at the end
पूर्ण;

/*
 * काष्ठा sun8i_cipher_tfm_ctx - context क्रम a skcipher TFM
 * @enginectx:		crypto_engine used by this TFM
 * @key:		poपूर्णांकer to key data
 * @keylen:		len of the key
 * @ce:			poपूर्णांकer to the निजी data of driver handling this TFM
 * @fallback_tfm:	poपूर्णांकer to the fallback TFM
 */
काष्ठा sun8i_cipher_tfm_ctx अणु
	काष्ठा crypto_engine_ctx enginectx;
	u32 *key;
	u32 keylen;
	काष्ठा sun8i_ce_dev *ce;
	काष्ठा crypto_skcipher *fallback_tfm;
पूर्ण;

/*
 * काष्ठा sun8i_ce_hash_tfm_ctx - context क्रम an ahash TFM
 * @enginectx:		crypto_engine used by this TFM
 * @ce:			poपूर्णांकer to the निजी data of driver handling this TFM
 * @fallback_tfm:	poपूर्णांकer to the fallback TFM
 */
काष्ठा sun8i_ce_hash_tfm_ctx अणु
	काष्ठा crypto_engine_ctx enginectx;
	काष्ठा sun8i_ce_dev *ce;
	काष्ठा crypto_ahash *fallback_tfm;
पूर्ण;

/*
 * काष्ठा sun8i_ce_hash_reqctx - context क्रम an ahash request
 * @fallback_req:	pre-allocated fallback request
 * @flow:	the flow to use क्रम this request
 */
काष्ठा sun8i_ce_hash_reqctx अणु
	काष्ठा ahash_request fallback_req;
	पूर्णांक flow;
पूर्ण;

/*
 * काष्ठा sun8i_ce_prng_ctx - context क्रम PRNG TFM
 * @seed:	The seed to use
 * @slen:	The size of the seed
 */
काष्ठा sun8i_ce_rng_tfm_ctx अणु
	व्योम *seed;
	अचिन्हित पूर्णांक slen;
पूर्ण;

/*
 * काष्ठा sun8i_ce_alg_ढाँचा - crypto_alg ढाँचा
 * @type:		the CRYPTO_ALG_TYPE क्रम this ढाँचा
 * @ce_algo_id:		the CE_ID क्रम this ढाँचा
 * @ce_blockmode:	the type of block operation CE_ID
 * @ce:			poपूर्णांकer to the sun8i_ce_dev काष्ठाure associated with
 *			this ढाँचा
 * @alg:		one of sub काष्ठा must be used
 * @stat_req:		number of request करोne on this ढाँचा
 * @stat_fb:		number of request which has fallbacked
 * @stat_bytes:		total data size करोne by this ढाँचा
 */
काष्ठा sun8i_ce_alg_ढाँचा अणु
	u32 type;
	u32 ce_algo_id;
	u32 ce_blockmode;
	काष्ठा sun8i_ce_dev *ce;
	जोड़ अणु
		काष्ठा skcipher_alg skcipher;
		काष्ठा ahash_alg hash;
		काष्ठा rng_alg rng;
	पूर्ण alg;
#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_CE_DEBUG
	अचिन्हित दीर्घ stat_req;
	अचिन्हित दीर्घ stat_fb;
	अचिन्हित दीर्घ stat_bytes;
#पूर्ण_अगर
पूर्ण;

पूर्णांक sun8i_ce_enqueue(काष्ठा crypto_async_request *areq, u32 type);

पूर्णांक sun8i_ce_aes_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			अचिन्हित पूर्णांक keylen);
पूर्णांक sun8i_ce_des3_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			 अचिन्हित पूर्णांक keylen);
पूर्णांक sun8i_ce_cipher_init(काष्ठा crypto_tfm *tfm);
व्योम sun8i_ce_cipher_निकास(काष्ठा crypto_tfm *tfm);
पूर्णांक sun8i_ce_skdecrypt(काष्ठा skcipher_request *areq);
पूर्णांक sun8i_ce_skencrypt(काष्ठा skcipher_request *areq);

पूर्णांक sun8i_ce_get_engine_number(काष्ठा sun8i_ce_dev *ce);

पूर्णांक sun8i_ce_run_task(काष्ठा sun8i_ce_dev *ce, पूर्णांक flow, स्थिर अक्षर *name);

पूर्णांक sun8i_ce_hash_crainit(काष्ठा crypto_tfm *tfm);
व्योम sun8i_ce_hash_craनिकास(काष्ठा crypto_tfm *tfm);
पूर्णांक sun8i_ce_hash_init(काष्ठा ahash_request *areq);
पूर्णांक sun8i_ce_hash_export(काष्ठा ahash_request *areq, व्योम *out);
पूर्णांक sun8i_ce_hash_import(काष्ठा ahash_request *areq, स्थिर व्योम *in);
पूर्णांक sun8i_ce_hash(काष्ठा ahash_request *areq);
पूर्णांक sun8i_ce_hash_final(काष्ठा ahash_request *areq);
पूर्णांक sun8i_ce_hash_update(काष्ठा ahash_request *areq);
पूर्णांक sun8i_ce_hash_finup(काष्ठा ahash_request *areq);
पूर्णांक sun8i_ce_hash_digest(काष्ठा ahash_request *areq);
पूर्णांक sun8i_ce_hash_run(काष्ठा crypto_engine *engine, व्योम *breq);

पूर्णांक sun8i_ce_prng_generate(काष्ठा crypto_rng *tfm, स्थिर u8 *src,
			   अचिन्हित पूर्णांक slen, u8 *dst, अचिन्हित पूर्णांक dlen);
पूर्णांक sun8i_ce_prng_seed(काष्ठा crypto_rng *tfm, स्थिर u8 *seed, अचिन्हित पूर्णांक slen);
व्योम sun8i_ce_prng_निकास(काष्ठा crypto_tfm *tfm);
पूर्णांक sun8i_ce_prng_init(काष्ठा crypto_tfm *tfm);

पूर्णांक sun8i_ce_hwrng_रेजिस्टर(काष्ठा sun8i_ce_dev *ce);
व्योम sun8i_ce_hwrng_unरेजिस्टर(काष्ठा sun8i_ce_dev *ce);
