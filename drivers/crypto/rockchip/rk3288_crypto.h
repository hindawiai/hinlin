<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __RK3288_CRYPTO_H__
#घोषणा __RK3288_CRYPTO_H__

#समावेश <crypto/aes.h>
#समावेश <crypto/पूर्णांकernal/des.h>
#समावेश <crypto/algapi.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/scatterlist.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>

#समावेश <crypto/md5.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>

#घोषणा _SBF(v, f)			((v) << (f))

/* Crypto control रेजिस्टरs*/
#घोषणा RK_CRYPTO_INTSTS		0x0000
#घोषणा RK_CRYPTO_PKA_DONE_INT		BIT(5)
#घोषणा RK_CRYPTO_HASH_DONE_INT		BIT(4)
#घोषणा RK_CRYPTO_HRDMA_ERR_INT		BIT(3)
#घोषणा RK_CRYPTO_HRDMA_DONE_INT	BIT(2)
#घोषणा RK_CRYPTO_BCDMA_ERR_INT		BIT(1)
#घोषणा RK_CRYPTO_BCDMA_DONE_INT	BIT(0)

#घोषणा RK_CRYPTO_INTENA		0x0004
#घोषणा RK_CRYPTO_PKA_DONE_ENA		BIT(5)
#घोषणा RK_CRYPTO_HASH_DONE_ENA		BIT(4)
#घोषणा RK_CRYPTO_HRDMA_ERR_ENA		BIT(3)
#घोषणा RK_CRYPTO_HRDMA_DONE_ENA	BIT(2)
#घोषणा RK_CRYPTO_BCDMA_ERR_ENA		BIT(1)
#घोषणा RK_CRYPTO_BCDMA_DONE_ENA	BIT(0)

#घोषणा RK_CRYPTO_CTRL			0x0008
#घोषणा RK_CRYPTO_WRITE_MASK		_SBF(0xFFFF, 16)
#घोषणा RK_CRYPTO_TRNG_FLUSH		BIT(9)
#घोषणा RK_CRYPTO_TRNG_START		BIT(8)
#घोषणा RK_CRYPTO_PKA_FLUSH		BIT(7)
#घोषणा RK_CRYPTO_HASH_FLUSH		BIT(6)
#घोषणा RK_CRYPTO_BLOCK_FLUSH		BIT(5)
#घोषणा RK_CRYPTO_PKA_START		BIT(4)
#घोषणा RK_CRYPTO_HASH_START		BIT(3)
#घोषणा RK_CRYPTO_BLOCK_START		BIT(2)
#घोषणा RK_CRYPTO_TDES_START		BIT(1)
#घोषणा RK_CRYPTO_AES_START		BIT(0)

#घोषणा RK_CRYPTO_CONF			0x000c
/* HASH Receive DMA Address Mode:   fix | increment */
#घोषणा RK_CRYPTO_HR_ADDR_MODE		BIT(8)
/* Block Transmit DMA Address Mode: fix | increment */
#घोषणा RK_CRYPTO_BT_ADDR_MODE		BIT(7)
/* Block Receive DMA Address Mode:  fix | increment */
#घोषणा RK_CRYPTO_BR_ADDR_MODE		BIT(6)
#घोषणा RK_CRYPTO_BYTESWAP_HRFIFO	BIT(5)
#घोषणा RK_CRYPTO_BYTESWAP_BTFIFO	BIT(4)
#घोषणा RK_CRYPTO_BYTESWAP_BRFIFO	BIT(3)
/* AES = 0 OR DES = 1 */
#घोषणा RK_CRYPTO_DESSEL				BIT(2)
#घोषणा RK_CYYPTO_HASHINSEL_INDEPENDENT_SOURCE		_SBF(0x00, 0)
#घोषणा RK_CYYPTO_HASHINSEL_BLOCK_CIPHER_INPUT		_SBF(0x01, 0)
#घोषणा RK_CYYPTO_HASHINSEL_BLOCK_CIPHER_OUTPUT		_SBF(0x02, 0)

/* Block Receiving DMA Start Address Register */
#घोषणा RK_CRYPTO_BRDMAS		0x0010
/* Block Transmitting DMA Start Address Register */
#घोषणा RK_CRYPTO_BTDMAS		0x0014
/* Block Receiving DMA Length Register */
#घोषणा RK_CRYPTO_BRDMAL		0x0018
/* Hash Receiving DMA Start Address Register */
#घोषणा RK_CRYPTO_HRDMAS		0x001c
/* Hash Receiving DMA Length Register */
#घोषणा RK_CRYPTO_HRDMAL		0x0020

/* AES रेजिस्टरs */
#घोषणा RK_CRYPTO_AES_CTRL			  0x0080
#घोषणा RK_CRYPTO_AES_BYTESWAP_CNT	BIT(11)
#घोषणा RK_CRYPTO_AES_BYTESWAP_KEY	BIT(10)
#घोषणा RK_CRYPTO_AES_BYTESWAP_IV	BIT(9)
#घोषणा RK_CRYPTO_AES_BYTESWAP_DO	BIT(8)
#घोषणा RK_CRYPTO_AES_BYTESWAP_DI	BIT(7)
#घोषणा RK_CRYPTO_AES_KEY_CHANGE	BIT(6)
#घोषणा RK_CRYPTO_AES_ECB_MODE		_SBF(0x00, 4)
#घोषणा RK_CRYPTO_AES_CBC_MODE		_SBF(0x01, 4)
#घोषणा RK_CRYPTO_AES_CTR_MODE		_SBF(0x02, 4)
#घोषणा RK_CRYPTO_AES_128BIT_key	_SBF(0x00, 2)
#घोषणा RK_CRYPTO_AES_192BIT_key	_SBF(0x01, 2)
#घोषणा RK_CRYPTO_AES_256BIT_key	_SBF(0x02, 2)
/* Slave = 0 / fअगरo = 1 */
#घोषणा RK_CRYPTO_AES_FIFO_MODE		BIT(1)
/* Encryption = 0 , Decryption = 1 */
#घोषणा RK_CRYPTO_AES_DEC		BIT(0)

#घोषणा RK_CRYPTO_AES_STS		0x0084
#घोषणा RK_CRYPTO_AES_DONE		BIT(0)

/* AES Input Data 0-3 Register */
#घोषणा RK_CRYPTO_AES_DIN_0		0x0088
#घोषणा RK_CRYPTO_AES_DIN_1		0x008c
#घोषणा RK_CRYPTO_AES_DIN_2		0x0090
#घोषणा RK_CRYPTO_AES_DIN_3		0x0094

/* AES output Data 0-3 Register */
#घोषणा RK_CRYPTO_AES_DOUT_0		0x0098
#घोषणा RK_CRYPTO_AES_DOUT_1		0x009c
#घोषणा RK_CRYPTO_AES_DOUT_2		0x00a0
#घोषणा RK_CRYPTO_AES_DOUT_3		0x00a4

/* AES IV Data 0-3 Register */
#घोषणा RK_CRYPTO_AES_IV_0		0x00a8
#घोषणा RK_CRYPTO_AES_IV_1		0x00ac
#घोषणा RK_CRYPTO_AES_IV_2		0x00b0
#घोषणा RK_CRYPTO_AES_IV_3		0x00b4

/* AES Key Data 0-3 Register */
#घोषणा RK_CRYPTO_AES_KEY_0		0x00b8
#घोषणा RK_CRYPTO_AES_KEY_1		0x00bc
#घोषणा RK_CRYPTO_AES_KEY_2		0x00c0
#घोषणा RK_CRYPTO_AES_KEY_3		0x00c4
#घोषणा RK_CRYPTO_AES_KEY_4		0x00c8
#घोषणा RK_CRYPTO_AES_KEY_5		0x00cc
#घोषणा RK_CRYPTO_AES_KEY_6		0x00d0
#घोषणा RK_CRYPTO_AES_KEY_7		0x00d4

/* des/tdes */
#घोषणा RK_CRYPTO_TDES_CTRL		0x0100
#घोषणा RK_CRYPTO_TDES_BYTESWAP_KEY	BIT(8)
#घोषणा RK_CRYPTO_TDES_BYTESWAP_IV	BIT(7)
#घोषणा RK_CRYPTO_TDES_BYTESWAP_DO	BIT(6)
#घोषणा RK_CRYPTO_TDES_BYTESWAP_DI	BIT(5)
/* 0: ECB, 1: CBC */
#घोषणा RK_CRYPTO_TDES_CHAINMODE_CBC	BIT(4)
/* TDES Key Mode, 0 : EDE, 1 : EEE */
#घोषणा RK_CRYPTO_TDES_EEE		BIT(3)
/* 0: DES, 1:TDES */
#घोषणा RK_CRYPTO_TDES_SELECT		BIT(2)
/* 0: Slave, 1:Fअगरo */
#घोषणा RK_CRYPTO_TDES_FIFO_MODE	BIT(1)
/* Encryption = 0 , Decryption = 1 */
#घोषणा RK_CRYPTO_TDES_DEC		BIT(0)

#घोषणा RK_CRYPTO_TDES_STS		0x0104
#घोषणा RK_CRYPTO_TDES_DONE		BIT(0)

#घोषणा RK_CRYPTO_TDES_DIN_0		0x0108
#घोषणा RK_CRYPTO_TDES_DIN_1		0x010c
#घोषणा RK_CRYPTO_TDES_DOUT_0		0x0110
#घोषणा RK_CRYPTO_TDES_DOUT_1		0x0114
#घोषणा RK_CRYPTO_TDES_IV_0		0x0118
#घोषणा RK_CRYPTO_TDES_IV_1		0x011c
#घोषणा RK_CRYPTO_TDES_KEY1_0		0x0120
#घोषणा RK_CRYPTO_TDES_KEY1_1		0x0124
#घोषणा RK_CRYPTO_TDES_KEY2_0		0x0128
#घोषणा RK_CRYPTO_TDES_KEY2_1		0x012c
#घोषणा RK_CRYPTO_TDES_KEY3_0		0x0130
#घोषणा RK_CRYPTO_TDES_KEY3_1		0x0134

/* HASH */
#घोषणा RK_CRYPTO_HASH_CTRL		0x0180
#घोषणा RK_CRYPTO_HASH_SWAP_DO		BIT(3)
#घोषणा RK_CRYPTO_HASH_SWAP_DI		BIT(2)
#घोषणा RK_CRYPTO_HASH_SHA1		_SBF(0x00, 0)
#घोषणा RK_CRYPTO_HASH_MD5		_SBF(0x01, 0)
#घोषणा RK_CRYPTO_HASH_SHA256		_SBF(0x02, 0)
#घोषणा RK_CRYPTO_HASH_PRNG		_SBF(0x03, 0)

#घोषणा RK_CRYPTO_HASH_STS		0x0184
#घोषणा RK_CRYPTO_HASH_DONE		BIT(0)

#घोषणा RK_CRYPTO_HASH_MSG_LEN		0x0188
#घोषणा RK_CRYPTO_HASH_DOUT_0		0x018c
#घोषणा RK_CRYPTO_HASH_DOUT_1		0x0190
#घोषणा RK_CRYPTO_HASH_DOUT_2		0x0194
#घोषणा RK_CRYPTO_HASH_DOUT_3		0x0198
#घोषणा RK_CRYPTO_HASH_DOUT_4		0x019c
#घोषणा RK_CRYPTO_HASH_DOUT_5		0x01a0
#घोषणा RK_CRYPTO_HASH_DOUT_6		0x01a4
#घोषणा RK_CRYPTO_HASH_DOUT_7		0x01a8

#घोषणा CRYPTO_READ(dev, offset)		  \
		पढ़ोl_relaxed(((dev)->reg + (offset)))
#घोषणा CRYPTO_WRITE(dev, offset, val)	  \
		ग_लिखोl_relaxed((val), ((dev)->reg + (offset)))

काष्ठा rk_crypto_info अणु
	काष्ठा device			*dev;
	काष्ठा clk			*aclk;
	काष्ठा clk			*hclk;
	काष्ठा clk			*sclk;
	काष्ठा clk			*dmaclk;
	काष्ठा reset_control		*rst;
	व्योम __iomem			*reg;
	पूर्णांक				irq;
	काष्ठा crypto_queue		queue;
	काष्ठा tasklet_काष्ठा		queue_task;
	काष्ठा tasklet_काष्ठा		करोne_task;
	काष्ठा crypto_async_request	*async_req;
	पूर्णांक 				err;
	/* device lock */
	spinlock_t			lock;

	/* the खुला variable */
	काष्ठा scatterlist		*sg_src;
	काष्ठा scatterlist		*sg_dst;
	काष्ठा scatterlist		sg_पंचांगp;
	काष्ठा scatterlist		*first;
	अचिन्हित पूर्णांक			left_bytes;
	व्योम				*addr_vir;
	पूर्णांक				aligned;
	पूर्णांक				align_size;
	माप_प्रकार				src_nents;
	माप_प्रकार				dst_nents;
	अचिन्हित पूर्णांक			total;
	अचिन्हित पूर्णांक			count;
	dma_addr_t			addr_in;
	dma_addr_t			addr_out;
	bool				busy;
	पूर्णांक (*start)(काष्ठा rk_crypto_info *dev);
	पूर्णांक (*update)(काष्ठा rk_crypto_info *dev);
	व्योम (*complete)(काष्ठा crypto_async_request *base, पूर्णांक err);
	पूर्णांक (*enable_clk)(काष्ठा rk_crypto_info *dev);
	व्योम (*disable_clk)(काष्ठा rk_crypto_info *dev);
	पूर्णांक (*load_data)(काष्ठा rk_crypto_info *dev,
			 काष्ठा scatterlist *sg_src,
			 काष्ठा scatterlist *sg_dst);
	व्योम (*unload_data)(काष्ठा rk_crypto_info *dev);
	पूर्णांक (*enqueue)(काष्ठा rk_crypto_info *dev,
		       काष्ठा crypto_async_request *async_req);
पूर्ण;

/* the निजी variable of hash */
काष्ठा rk_ahash_ctx अणु
	काष्ठा rk_crypto_info		*dev;
	/* क्रम fallback */
	काष्ठा crypto_ahash		*fallback_tfm;
पूर्ण;

/* the privete variable of hash क्रम fallback */
काष्ठा rk_ahash_rctx अणु
	काष्ठा ahash_request		fallback_req;
	u32				mode;
पूर्ण;

/* the निजी variable of cipher */
काष्ठा rk_cipher_ctx अणु
	काष्ठा rk_crypto_info		*dev;
	अचिन्हित पूर्णांक			keylen;
	u32				mode;
	u8				iv[AES_BLOCK_SIZE];
पूर्ण;

क्रमागत alg_type अणु
	ALG_TYPE_HASH,
	ALG_TYPE_CIPHER,
पूर्ण;

काष्ठा rk_crypto_पंचांगp अणु
	काष्ठा rk_crypto_info		*dev;
	जोड़ अणु
		काष्ठा skcipher_alg	skcipher;
		काष्ठा ahash_alg	hash;
	पूर्ण alg;
	क्रमागत alg_type			type;
पूर्ण;

बाह्य काष्ठा rk_crypto_पंचांगp rk_ecb_aes_alg;
बाह्य काष्ठा rk_crypto_पंचांगp rk_cbc_aes_alg;
बाह्य काष्ठा rk_crypto_पंचांगp rk_ecb_des_alg;
बाह्य काष्ठा rk_crypto_पंचांगp rk_cbc_des_alg;
बाह्य काष्ठा rk_crypto_पंचांगp rk_ecb_des3_ede_alg;
बाह्य काष्ठा rk_crypto_पंचांगp rk_cbc_des3_ede_alg;

बाह्य काष्ठा rk_crypto_पंचांगp rk_ahash_sha1;
बाह्य काष्ठा rk_crypto_पंचांगp rk_ahash_sha256;
बाह्य काष्ठा rk_crypto_पंचांगp rk_ahash_md5;

#पूर्ण_अगर
