<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * sun8i-ss.h - hardware cryptographic offloader क्रम
 * Allwinner A80/A83T SoC
 *
 * Copyright (C) 2016-2019 Corentin LABBE <clabbe.montjoie@gmail.com>
 */
#समावेश <crypto/aes.h>
#समावेश <crypto/des.h>
#समावेश <crypto/engine.h>
#समावेश <crypto/rng.h>
#समावेश <crypto/skcipher.h>
#समावेश <linux/atomic.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/crypto.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/md5.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>

#घोषणा SS_START	1

#घोषणा SS_ENCRYPTION		0
#घोषणा SS_DECRYPTION		BIT(6)

#घोषणा SS_ALG_AES		0
#घोषणा SS_ALG_DES		(1 << 2)
#घोषणा SS_ALG_3DES		(2 << 2)
#घोषणा SS_ALG_MD5		(3 << 2)
#घोषणा SS_ALG_PRNG		(4 << 2)
#घोषणा SS_ALG_SHA1		(6 << 2)
#घोषणा SS_ALG_SHA224		(7 << 2)
#घोषणा SS_ALG_SHA256		(8 << 2)

#घोषणा SS_CTL_REG		0x00
#घोषणा SS_INT_CTL_REG		0x04
#घोषणा SS_INT_STA_REG		0x08
#घोषणा SS_KEY_ADR_REG		0x10
#घोषणा SS_IV_ADR_REG		0x18
#घोषणा SS_SRC_ADR_REG		0x20
#घोषणा SS_DST_ADR_REG		0x28
#घोषणा SS_LEN_ADR_REG		0x30

#घोषणा SS_ID_NOTSUPP		0xFF

#घोषणा SS_ID_CIPHER_AES	0
#घोषणा SS_ID_CIPHER_DES	1
#घोषणा SS_ID_CIPHER_DES3	2
#घोषणा SS_ID_CIPHER_MAX	3

#घोषणा SS_ID_OP_ECB	0
#घोषणा SS_ID_OP_CBC	1
#घोषणा SS_ID_OP_MAX	2

#घोषणा SS_AES_128BITS 0
#घोषणा SS_AES_192BITS 1
#घोषणा SS_AES_256BITS 2

#घोषणा SS_OP_ECB	0
#घोषणा SS_OP_CBC	(1 << 13)

#घोषणा SS_ID_HASH_MD5	0
#घोषणा SS_ID_HASH_SHA1	1
#घोषणा SS_ID_HASH_SHA224	2
#घोषणा SS_ID_HASH_SHA256	3
#घोषणा SS_ID_HASH_MAX	4

#घोषणा SS_FLOW0	BIT(30)
#घोषणा SS_FLOW1	BIT(31)

#घोषणा SS_PRNG_CONTINUE	BIT(18)

#घोषणा MAX_SG 8

#घोषणा MAXFLOW 2

#घोषणा SS_MAX_CLOCKS 2

#घोषणा SS_DIE_ID_SHIFT	20
#घोषणा SS_DIE_ID_MASK	0x07

#घोषणा PRNG_DATA_SIZE (160 / 8)
#घोषणा PRNG_SEED_SIZE DIV_ROUND_UP(175, 8)

/*
 * काष्ठा ss_घड़ी - Describe घड़ीs used by sun8i-ss
 * @name:       Name of घड़ी needed by this variant
 * @freq:       Frequency to set क्रम each घड़ी
 * @max_freq:   Maximum frequency क्रम each घड़ी
 */
काष्ठा ss_घड़ी अणु
	स्थिर अक्षर *name;
	अचिन्हित दीर्घ freq;
	अचिन्हित दीर्घ max_freq;
पूर्ण;

/*
 * काष्ठा ss_variant - Describe SS capability क्रम each variant hardware
 * @alg_cipher:	list of supported ciphers. क्रम each SS_ID_ this will give the
 *              coresponding SS_ALG_XXX value
 * @alg_hash:	list of supported hashes. क्रम each SS_ID_ this will give the
 *              corresponding SS_ALG_XXX value
 * @op_mode:	list of supported block modes
 * @ss_clks:	list of घड़ी needed by this variant
 */
काष्ठा ss_variant अणु
	अक्षर alg_cipher[SS_ID_CIPHER_MAX];
	अक्षर alg_hash[SS_ID_HASH_MAX];
	u32 op_mode[SS_ID_OP_MAX];
	काष्ठा ss_घड़ी ss_clks[SS_MAX_CLOCKS];
पूर्ण;

काष्ठा sginfo अणु
	u32 addr;
	u32 len;
पूर्ण;

/*
 * काष्ठा sun8i_ss_flow - Inक्रमmation used by each flow
 * @engine:	ptr to the crypto_engine क्रम this flow
 * @complete:	completion क्रम the current task on this flow
 * @status:	set to 1 by पूर्णांकerrupt अगर task is करोne
 * @stat_req:	number of request करोne by this flow
 */
काष्ठा sun8i_ss_flow अणु
	काष्ठा crypto_engine *engine;
	काष्ठा completion complete;
	पूर्णांक status;
#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_SS_DEBUG
	अचिन्हित दीर्घ stat_req;
#पूर्ण_अगर
पूर्ण;

/*
 * काष्ठा sun8i_ss_dev - मुख्य container क्रम all this driver inक्रमmation
 * @base:	base address of SS
 * @ssclks:	घड़ीs used by SS
 * @reset:	poपूर्णांकer to reset controller
 * @dev:	the platक्रमm device
 * @mlock:	Control access to device रेजिस्टरs
 * @flows:	array of all flow
 * @flow:	flow to use in next request
 * @variant:	poपूर्णांकer to variant specअगरic data
 * @dbgfs_dir:	Debugfs dentry क्रम statistic directory
 * @dbgfs_stats: Debugfs dentry क्रम statistic counters
 */
काष्ठा sun8i_ss_dev अणु
	व्योम __iomem *base;
	काष्ठा clk *ssclks[SS_MAX_CLOCKS];
	काष्ठा reset_control *reset;
	काष्ठा device *dev;
	काष्ठा mutex mlock;
	काष्ठा sun8i_ss_flow *flows;
	atomic_t flow;
	स्थिर काष्ठा ss_variant *variant;
#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_SS_DEBUG
	काष्ठा dentry *dbgfs_dir;
	काष्ठा dentry *dbgfs_stats;
#पूर्ण_अगर
पूर्ण;

/*
 * काष्ठा sun8i_cipher_req_ctx - context क्रम a skcipher request
 * @t_src:		list of mapped SGs with their size
 * @t_dst:		list of mapped SGs with their size
 * @p_key:		DMA address of the key
 * @p_iv:		DMA address of the IV
 * @method:		current algorithm क्रम this request
 * @op_mode:		op_mode क्रम this request
 * @op_dir:		direction (encrypt vs decrypt) क्रम this request
 * @flow:		the flow to use क्रम this request
 * @ivlen:		size of biv
 * @keylen:		keylen क्रम this request
 * @biv:		buffer which contain the IV
 * @fallback_req:	request काष्ठा क्रम invoking the fallback skcipher TFM
 */
काष्ठा sun8i_cipher_req_ctx अणु
	काष्ठा sginfo t_src[MAX_SG];
	काष्ठा sginfo t_dst[MAX_SG];
	u32 p_key;
	u32 p_iv;
	u32 method;
	u32 op_mode;
	u32 op_dir;
	पूर्णांक flow;
	अचिन्हित पूर्णांक ivlen;
	अचिन्हित पूर्णांक keylen;
	व्योम *biv;
	काष्ठा skcipher_request fallback_req;   // keep at the end
पूर्ण;

/*
 * काष्ठा sun8i_cipher_tfm_ctx - context क्रम a skcipher TFM
 * @enginectx:		crypto_engine used by this TFM
 * @key:		poपूर्णांकer to key data
 * @keylen:		len of the key
 * @ss:			poपूर्णांकer to the निजी data of driver handling this TFM
 * @fallback_tfm:	poपूर्णांकer to the fallback TFM
 *
 * enginectx must be the first element
 */
काष्ठा sun8i_cipher_tfm_ctx अणु
	काष्ठा crypto_engine_ctx enginectx;
	u32 *key;
	u32 keylen;
	काष्ठा sun8i_ss_dev *ss;
	काष्ठा crypto_skcipher *fallback_tfm;
पूर्ण;

/*
 * काष्ठा sun8i_ss_prng_ctx - context क्रम PRNG TFM
 * @seed:	The seed to use
 * @slen:	The size of the seed
 */
काष्ठा sun8i_ss_rng_tfm_ctx अणु
	व्योम *seed;
	अचिन्हित पूर्णांक slen;
पूर्ण;

/*
 * काष्ठा sun8i_ss_hash_tfm_ctx - context क्रम an ahash TFM
 * @enginectx:		crypto_engine used by this TFM
 * @fallback_tfm:	poपूर्णांकer to the fallback TFM
 * @ss:			poपूर्णांकer to the निजी data of driver handling this TFM
 *
 * enginectx must be the first element
 */
काष्ठा sun8i_ss_hash_tfm_ctx अणु
	काष्ठा crypto_engine_ctx enginectx;
	काष्ठा crypto_ahash *fallback_tfm;
	काष्ठा sun8i_ss_dev *ss;
पूर्ण;

/*
 * काष्ठा sun8i_ss_hash_reqctx - context क्रम an ahash request
 * @t_src:	list of DMA address and size क्रम source SGs
 * @t_dst:	list of DMA address and size क्रम destination SGs
 * @fallback_req:	pre-allocated fallback request
 * @method:	the रेजिस्टर value क्रम the algorithm used by this request
 * @flow:	the flow to use क्रम this request
 */
काष्ठा sun8i_ss_hash_reqctx अणु
	काष्ठा sginfo t_src[MAX_SG];
	काष्ठा sginfo t_dst[MAX_SG];
	काष्ठा ahash_request fallback_req;
	u32 method;
	पूर्णांक flow;
पूर्ण;

/*
 * काष्ठा sun8i_ss_alg_ढाँचा - crypto_alg ढाँचा
 * @type:		the CRYPTO_ALG_TYPE क्रम this ढाँचा
 * @ss_algo_id:		the SS_ID क्रम this ढाँचा
 * @ss_blockmode:	the type of block operation SS_ID
 * @ss:			poपूर्णांकer to the sun8i_ss_dev काष्ठाure associated with
 *			this ढाँचा
 * @alg:		one of sub काष्ठा must be used
 * @stat_req:		number of request करोne on this ढाँचा
 * @stat_fb:		number of request which has fallbacked
 * @stat_bytes:		total data size करोne by this ढाँचा
 */
काष्ठा sun8i_ss_alg_ढाँचा अणु
	u32 type;
	u32 ss_algo_id;
	u32 ss_blockmode;
	काष्ठा sun8i_ss_dev *ss;
	जोड़ अणु
		काष्ठा skcipher_alg skcipher;
		काष्ठा rng_alg rng;
		काष्ठा ahash_alg hash;
	पूर्ण alg;
#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_SS_DEBUG
	अचिन्हित दीर्घ stat_req;
	अचिन्हित दीर्घ stat_fb;
	अचिन्हित दीर्घ stat_bytes;
#पूर्ण_अगर
पूर्ण;

पूर्णांक sun8i_ss_enqueue(काष्ठा crypto_async_request *areq, u32 type);

पूर्णांक sun8i_ss_aes_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			अचिन्हित पूर्णांक keylen);
पूर्णांक sun8i_ss_des3_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			 अचिन्हित पूर्णांक keylen);
पूर्णांक sun8i_ss_cipher_init(काष्ठा crypto_tfm *tfm);
व्योम sun8i_ss_cipher_निकास(काष्ठा crypto_tfm *tfm);
पूर्णांक sun8i_ss_skdecrypt(काष्ठा skcipher_request *areq);
पूर्णांक sun8i_ss_skencrypt(काष्ठा skcipher_request *areq);

पूर्णांक sun8i_ss_get_engine_number(काष्ठा sun8i_ss_dev *ss);

पूर्णांक sun8i_ss_run_task(काष्ठा sun8i_ss_dev *ss, काष्ठा sun8i_cipher_req_ctx *rctx, स्थिर अक्षर *name);
पूर्णांक sun8i_ss_prng_generate(काष्ठा crypto_rng *tfm, स्थिर u8 *src,
			   अचिन्हित पूर्णांक slen, u8 *dst, अचिन्हित पूर्णांक dlen);
पूर्णांक sun8i_ss_prng_seed(काष्ठा crypto_rng *tfm, स्थिर u8 *seed, अचिन्हित पूर्णांक slen);
पूर्णांक sun8i_ss_prng_init(काष्ठा crypto_tfm *tfm);
व्योम sun8i_ss_prng_निकास(काष्ठा crypto_tfm *tfm);

पूर्णांक sun8i_ss_hash_crainit(काष्ठा crypto_tfm *tfm);
व्योम sun8i_ss_hash_craनिकास(काष्ठा crypto_tfm *tfm);
पूर्णांक sun8i_ss_hash_init(काष्ठा ahash_request *areq);
पूर्णांक sun8i_ss_hash_export(काष्ठा ahash_request *areq, व्योम *out);
पूर्णांक sun8i_ss_hash_import(काष्ठा ahash_request *areq, स्थिर व्योम *in);
पूर्णांक sun8i_ss_hash_final(काष्ठा ahash_request *areq);
पूर्णांक sun8i_ss_hash_update(काष्ठा ahash_request *areq);
पूर्णांक sun8i_ss_hash_finup(काष्ठा ahash_request *areq);
पूर्णांक sun8i_ss_hash_digest(काष्ठा ahash_request *areq);
पूर्णांक sun8i_ss_hash_run(काष्ठा crypto_engine *engine, व्योम *breq);
