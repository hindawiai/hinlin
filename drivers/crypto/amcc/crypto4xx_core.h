<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * AMCC SoC PPC4xx Crypto Driver
 *
 * Copyright (c) 2008 Applied Micro Circuits Corporation.
 * All rights reserved. James Hsiao <jhsiao@amcc.com>
 *
 * This is the header file क्रम AMCC Crypto offload Linux device driver क्रम
 * use with Linux CryptoAPI.

 */

#अगर_अघोषित __CRYPTO4XX_CORE_H__
#घोषणा __CRYPTO4XX_CORE_H__

#समावेश <linux/ratelimit.h>
#समावेश <linux/mutex.h>
#समावेश <linux/scatterlist.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/पूर्णांकernal/rng.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश "crypto4xx_reg_def.h"
#समावेश "crypto4xx_sa.h"

#घोषणा PPC460SX_SDR0_SRST                      0x201
#घोषणा PPC405EX_SDR0_SRST                      0x200
#घोषणा PPC460EX_SDR0_SRST                      0x201
#घोषणा PPC460EX_CE_RESET                       0x08000000
#घोषणा PPC460SX_CE_RESET                       0x20000000
#घोषणा PPC405EX_CE_RESET                       0x00000008

#घोषणा CRYPTO4XX_CRYPTO_PRIORITY		300
#घोषणा PPC4XX_NUM_PD				256
#घोषणा PPC4XX_LAST_PD				(PPC4XX_NUM_PD - 1)
#घोषणा PPC4XX_NUM_GD				1024
#घोषणा PPC4XX_LAST_GD				(PPC4XX_NUM_GD - 1)
#घोषणा PPC4XX_NUM_SD				256
#घोषणा PPC4XX_LAST_SD				(PPC4XX_NUM_SD - 1)
#घोषणा PPC4XX_SD_BUFFER_SIZE			2048

#घोषणा PD_ENTRY_BUSY				BIT(1)
#घोषणा PD_ENTRY_INUSE				BIT(0)
#घोषणा PD_ENTRY_FREE				0
#घोषणा ERING_WAS_FULL				0xffffffff

काष्ठा crypto4xx_device;

जोड़ shaकरोw_sa_buf अणु
	काष्ठा dynamic_sa_ctl sa;

	/* alloc 256 bytes which is enough क्रम any kind of dynamic sa */
	u8 buf[256];
पूर्ण __packed;

काष्ठा pd_uinfo अणु
	काष्ठा crypto4xx_device *dev;
	u32   state;
	u32 first_gd;		/* first gather discriptor
				used by this packet */
	u32 num_gd;             /* number of gather discriptor
				used by this packet */
	u32 first_sd;		/* first scatter discriptor
				used by this packet */
	u32 num_sd;		/* number of scatter discriptors
				used by this packet */
	काष्ठा dynamic_sa_ctl *sa_va;	/* shaकरोw sa */
	काष्ठा sa_state_record *sr_va;	/* state record क्रम shaकरोw sa */
	u32 sr_pa;
	काष्ठा scatterlist *dest_va;
	काष्ठा crypto_async_request *async_req; 	/* base crypto request
							क्रम this packet */
पूर्ण;

काष्ठा crypto4xx_device अणु
	काष्ठा crypto4xx_core_device *core_dev;
	व्योम __iomem *ce_base;
	व्योम __iomem *trng_base;

	काष्ठा ce_pd *pdr;	/* base address of packet descriptor ring */
	dma_addr_t pdr_pa;	/* physical address of pdr_base_रेजिस्टर */
	काष्ठा ce_gd *gdr;	/* gather descriptor ring */
	dma_addr_t gdr_pa;	/* physical address of gdr_base_रेजिस्टर */
	काष्ठा ce_sd *sdr;	/* scatter descriptor ring */
	dma_addr_t sdr_pa;	/* physical address of sdr_base_रेजिस्टर */
	व्योम *scatter_buffer_va;
	dma_addr_t scatter_buffer_pa;

	जोड़ shaकरोw_sa_buf *shaकरोw_sa_pool;
	dma_addr_t shaकरोw_sa_pool_pa;
	काष्ठा sa_state_record *shaकरोw_sr_pool;
	dma_addr_t shaकरोw_sr_pool_pa;
	u32 pdr_tail;
	u32 pdr_head;
	u32 gdr_tail;
	u32 gdr_head;
	u32 sdr_tail;
	u32 sdr_head;
	काष्ठा pd_uinfo *pdr_uinfo;
	काष्ठा list_head alg_list;	/* List of algorithm supported
					by this device */
	काष्ठा ratelimit_state aead_ratelimit;
	bool is_revb;
पूर्ण;

काष्ठा crypto4xx_core_device अणु
	काष्ठा device *device;
	काष्ठा platक्रमm_device *ofdev;
	काष्ठा crypto4xx_device *dev;
	काष्ठा hwrng *trng;
	u32 पूर्णांक_status;
	u32 irq;
	काष्ठा tasklet_काष्ठा tasklet;
	spinlock_t lock;
	काष्ठा mutex rng_lock;
पूर्ण;

काष्ठा crypto4xx_ctx अणु
	काष्ठा crypto4xx_device *dev;
	काष्ठा dynamic_sa_ctl *sa_in;
	काष्ठा dynamic_sa_ctl *sa_out;
	__le32 iv_nonce;
	u32 sa_len;
	जोड़ अणु
		काष्ठा crypto_sync_skcipher *cipher;
		काष्ठा crypto_aead *aead;
	पूर्ण sw_cipher;
पूर्ण;

काष्ठा crypto4xx_aead_reqctx अणु
	काष्ठा scatterlist dst[2];
पूर्ण;

काष्ठा crypto4xx_alg_common अणु
	u32 type;
	जोड़ अणु
		काष्ठा skcipher_alg cipher;
		काष्ठा ahash_alg hash;
		काष्ठा aead_alg aead;
		काष्ठा rng_alg rng;
	पूर्ण u;
पूर्ण;

काष्ठा crypto4xx_alg अणु
	काष्ठा list_head  entry;
	काष्ठा crypto4xx_alg_common alg;
	काष्ठा crypto4xx_device *dev;
पूर्ण;

पूर्णांक crypto4xx_alloc_sa(काष्ठा crypto4xx_ctx *ctx, u32 size);
व्योम crypto4xx_मुक्त_sa(काष्ठा crypto4xx_ctx *ctx);
व्योम crypto4xx_मुक्त_ctx(काष्ठा crypto4xx_ctx *ctx);
पूर्णांक crypto4xx_build_pd(काष्ठा crypto_async_request *req,
		       काष्ठा crypto4xx_ctx *ctx,
		       काष्ठा scatterlist *src,
		       काष्ठा scatterlist *dst,
		       स्थिर अचिन्हित पूर्णांक datalen,
		       स्थिर __le32 *iv, स्थिर u32 iv_len,
		       स्थिर काष्ठा dynamic_sa_ctl *sa,
		       स्थिर अचिन्हित पूर्णांक sa_len,
		       स्थिर अचिन्हित पूर्णांक assoclen,
		       काष्ठा scatterlist *dst_पंचांगp);
पूर्णांक crypto4xx_setkey_aes_cbc(काष्ठा crypto_skcipher *cipher,
			     स्थिर u8 *key, अचिन्हित पूर्णांक keylen);
पूर्णांक crypto4xx_setkey_aes_cfb(काष्ठा crypto_skcipher *cipher,
			     स्थिर u8 *key, अचिन्हित पूर्णांक keylen);
पूर्णांक crypto4xx_setkey_aes_ctr(काष्ठा crypto_skcipher *cipher,
			     स्थिर u8 *key, अचिन्हित पूर्णांक keylen);
पूर्णांक crypto4xx_setkey_aes_ecb(काष्ठा crypto_skcipher *cipher,
			     स्थिर u8 *key, अचिन्हित पूर्णांक keylen);
पूर्णांक crypto4xx_setkey_aes_ofb(काष्ठा crypto_skcipher *cipher,
			     स्थिर u8 *key, अचिन्हित पूर्णांक keylen);
पूर्णांक crypto4xx_setkey_rfc3686(काष्ठा crypto_skcipher *cipher,
			     स्थिर u8 *key, अचिन्हित पूर्णांक keylen);
पूर्णांक crypto4xx_encrypt_ctr(काष्ठा skcipher_request *req);
पूर्णांक crypto4xx_decrypt_ctr(काष्ठा skcipher_request *req);
पूर्णांक crypto4xx_encrypt_iv_stream(काष्ठा skcipher_request *req);
पूर्णांक crypto4xx_decrypt_iv_stream(काष्ठा skcipher_request *req);
पूर्णांक crypto4xx_encrypt_iv_block(काष्ठा skcipher_request *req);
पूर्णांक crypto4xx_decrypt_iv_block(काष्ठा skcipher_request *req);
पूर्णांक crypto4xx_encrypt_noiv_block(काष्ठा skcipher_request *req);
पूर्णांक crypto4xx_decrypt_noiv_block(काष्ठा skcipher_request *req);
पूर्णांक crypto4xx_rfc3686_encrypt(काष्ठा skcipher_request *req);
पूर्णांक crypto4xx_rfc3686_decrypt(काष्ठा skcipher_request *req);
पूर्णांक crypto4xx_sha1_alg_init(काष्ठा crypto_tfm *tfm);
पूर्णांक crypto4xx_hash_digest(काष्ठा ahash_request *req);
पूर्णांक crypto4xx_hash_final(काष्ठा ahash_request *req);
पूर्णांक crypto4xx_hash_update(काष्ठा ahash_request *req);
पूर्णांक crypto4xx_hash_init(काष्ठा ahash_request *req);

/*
 * Note: Only use this function to copy items that is word aligned.
 */
अटल अंतरभूत व्योम crypto4xx_स_नकल_swab32(u32 *dst, स्थिर व्योम *buf,
					   माप_प्रकार len)
अणु
	क्रम (; len >= 4; buf += 4, len -= 4)
		*dst++ = __swab32p((u32 *) buf);

	अगर (len) अणु
		स्थिर u8 *पंचांगp = (u8 *)buf;

		चयन (len) अणु
		हाल 3:
			*dst = (पंचांगp[2] << 16) |
			       (पंचांगp[1] << 8) |
			       पंचांगp[0];
			अवरोध;
		हाल 2:
			*dst = (पंचांगp[1] << 8) |
			       पंचांगp[0];
			अवरोध;
		हाल 1:
			*dst = पंचांगp[0];
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम crypto4xx_स_नकल_from_le32(u32 *dst, स्थिर व्योम *buf,
					      माप_प्रकार len)
अणु
	crypto4xx_स_नकल_swab32(dst, buf, len);
पूर्ण

अटल अंतरभूत व्योम crypto4xx_स_नकल_to_le32(__le32 *dst, स्थिर व्योम *buf,
					    माप_प्रकार len)
अणु
	crypto4xx_स_नकल_swab32((u32 *)dst, buf, len);
पूर्ण

पूर्णांक crypto4xx_setauthsize_aead(काष्ठा crypto_aead *ciper,
			       अचिन्हित पूर्णांक authsize);
पूर्णांक crypto4xx_setkey_aes_ccm(काष्ठा crypto_aead *cipher,
			     स्थिर u8 *key, अचिन्हित पूर्णांक keylen);
पूर्णांक crypto4xx_encrypt_aes_ccm(काष्ठा aead_request *req);
पूर्णांक crypto4xx_decrypt_aes_ccm(काष्ठा aead_request *req);
पूर्णांक crypto4xx_setkey_aes_gcm(काष्ठा crypto_aead *cipher,
			     स्थिर u8 *key, अचिन्हित पूर्णांक keylen);
पूर्णांक crypto4xx_encrypt_aes_gcm(काष्ठा aead_request *req);
पूर्णांक crypto4xx_decrypt_aes_gcm(काष्ठा aead_request *req);

#पूर्ण_अगर
