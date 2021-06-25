<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * sun4i-ss.h - hardware cryptographic accelerator क्रम Allwinner A20 SoC
 *
 * Copyright (C) 2013-2015 Corentin LABBE <clabbe.montjoie@gmail.com>
 *
 * Support AES cipher with 128,192,256 bits keysize.
 * Support MD5 and SHA1 hash algorithms.
 * Support DES and 3DES
 *
 * You could find the datasheet in Documentation/arm/sunxi.rst
 */

#समावेश <linux/clk.h>
#समावेश <linux/crypto.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <crypto/md5.h>
#समावेश <crypto/skcipher.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/पूर्णांकernal/des.h>
#समावेश <crypto/पूर्णांकernal/rng.h>
#समावेश <crypto/rng.h>

#घोषणा SS_CTL            0x00
#घोषणा SS_KEY0           0x04
#घोषणा SS_KEY1           0x08
#घोषणा SS_KEY2           0x0C
#घोषणा SS_KEY3           0x10
#घोषणा SS_KEY4           0x14
#घोषणा SS_KEY5           0x18
#घोषणा SS_KEY6           0x1C
#घोषणा SS_KEY7           0x20

#घोषणा SS_IV0            0x24
#घोषणा SS_IV1            0x28
#घोषणा SS_IV2            0x2C
#घोषणा SS_IV3            0x30

#घोषणा SS_FCSR           0x44

#घोषणा SS_MD0            0x4C
#घोषणा SS_MD1            0x50
#घोषणा SS_MD2            0x54
#घोषणा SS_MD3            0x58
#घोषणा SS_MD4            0x5C

#घोषणा SS_RXFIFO         0x200
#घोषणा SS_TXFIFO         0x204

/* SS_CTL configuration values */

/* PRNG generator mode - bit 15 */
#घोषणा SS_PRNG_ONESHOT		(0 << 15)
#घोषणा SS_PRNG_CONTINUE	(1 << 15)

/* IV mode क्रम hash */
#घोषणा SS_IV_ARBITRARY		(1 << 14)

/* SS operation mode - bits 12-13 */
#घोषणा SS_ECB			(0 << 12)
#घोषणा SS_CBC			(1 << 12)
#घोषणा SS_CTS			(3 << 12)

/* Counter width क्रम CNT mode - bits 10-11 */
#घोषणा SS_CNT_16BITS		(0 << 10)
#घोषणा SS_CNT_32BITS		(1 << 10)
#घोषणा SS_CNT_64BITS		(2 << 10)

/* Key size क्रम AES - bits 8-9 */
#घोषणा SS_AES_128BITS		(0 << 8)
#घोषणा SS_AES_192BITS		(1 << 8)
#घोषणा SS_AES_256BITS		(2 << 8)

/* Operation direction - bit 7 */
#घोषणा SS_ENCRYPTION		(0 << 7)
#घोषणा SS_DECRYPTION		(1 << 7)

/* SS Method - bits 4-6 */
#घोषणा SS_OP_AES		(0 << 4)
#घोषणा SS_OP_DES		(1 << 4)
#घोषणा SS_OP_3DES		(2 << 4)
#घोषणा SS_OP_SHA1		(3 << 4)
#घोषणा SS_OP_MD5		(4 << 4)
#घोषणा SS_OP_PRNG		(5 << 4)

/* Data end bit - bit 2 */
#घोषणा SS_DATA_END		(1 << 2)

/* PRNG start bit - bit 1 */
#घोषणा SS_PRNG_START		(1 << 1)

/* SS Enable bit - bit 0 */
#घोषणा SS_DISABLED		(0 << 0)
#घोषणा SS_ENABLED		(1 << 0)

/* SS_FCSR configuration values */
/* RX FIFO status - bit 30 */
#घोषणा SS_RXFIFO_FREE		(1 << 30)

/* RX FIFO empty spaces - bits 24-29 */
#घोषणा SS_RXFIFO_SPACES(val)	(((val) >> 24) & 0x3f)

/* TX FIFO status - bit 22 */
#घोषणा SS_TXFIFO_AVAILABLE	(1 << 22)

/* TX FIFO available spaces - bits 16-21 */
#घोषणा SS_TXFIFO_SPACES(val)	(((val) >> 16) & 0x3f)

#घोषणा SS_RX_MAX	32
#घोषणा SS_RX_DEFAULT	SS_RX_MAX
#घोषणा SS_TX_MAX	33

#घोषणा SS_RXFIFO_EMP_INT_PENDING	(1 << 10)
#घोषणा SS_TXFIFO_AVA_INT_PENDING	(1 << 8)
#घोषणा SS_RXFIFO_EMP_INT_ENABLE	(1 << 2)
#घोषणा SS_TXFIFO_AVA_INT_ENABLE	(1 << 0)

#घोषणा SS_SEED_LEN 192
#घोषणा SS_DATA_LEN 160

/*
 * काष्ठा ss_variant - Describe SS hardware variant
 * @sha1_in_be:		The SHA1 digest is given by SS in BE, and so need to be inverted.
 */
काष्ठा ss_variant अणु
	bool sha1_in_be;
पूर्ण;

काष्ठा sun4i_ss_ctx अणु
	स्थिर काष्ठा ss_variant *variant;
	व्योम __iomem *base;
	पूर्णांक irq;
	काष्ठा clk *busclk;
	काष्ठा clk *ssclk;
	काष्ठा reset_control *reset;
	काष्ठा device *dev;
	काष्ठा resource *res;
	अक्षर buf[4 * SS_RX_MAX];/* buffer क्रम linearize SG src */
	अक्षर bufo[4 * SS_TX_MAX]; /* buffer क्रम linearize SG dst */
	spinlock_t slock; /* control the use of the device */
#अगर_घोषित CONFIG_CRYPTO_DEV_SUN4I_SS_PRNG
	u32 seed[SS_SEED_LEN / BITS_PER_LONG];
#पूर्ण_अगर
	काष्ठा dentry *dbgfs_dir;
	काष्ठा dentry *dbgfs_stats;
पूर्ण;

काष्ठा sun4i_ss_alg_ढाँचा अणु
	u32 type;
	u32 mode;
	जोड़ अणु
		काष्ठा skcipher_alg crypto;
		काष्ठा ahash_alg hash;
		काष्ठा rng_alg rng;
	पूर्ण alg;
	काष्ठा sun4i_ss_ctx *ss;
	अचिन्हित दीर्घ stat_req;
	अचिन्हित दीर्घ stat_fb;
	अचिन्हित दीर्घ stat_bytes;
	अचिन्हित दीर्घ stat_opti;
पूर्ण;

काष्ठा sun4i_tfm_ctx अणु
	u32 key[AES_MAX_KEY_SIZE / 4];/* भागided by माप(u32) */
	u32 keylen;
	u32 keymode;
	काष्ठा sun4i_ss_ctx *ss;
	काष्ठा crypto_skcipher *fallback_tfm;
पूर्ण;

काष्ठा sun4i_cipher_req_ctx अणु
	u32 mode;
	काष्ठा skcipher_request fallback_req;   // keep at the end
पूर्ण;

काष्ठा sun4i_req_ctx अणु
	u32 mode;
	u64 byte_count; /* number of bytes "uploaded" to the device */
	u32 hash[5]; /* क्रम storing SS_IVx रेजिस्टर */
	अक्षर buf[64];
	अचिन्हित पूर्णांक len;
	पूर्णांक flags;
पूर्ण;

पूर्णांक sun4i_hash_crainit(काष्ठा crypto_tfm *tfm);
व्योम sun4i_hash_craनिकास(काष्ठा crypto_tfm *tfm);
पूर्णांक sun4i_hash_init(काष्ठा ahash_request *areq);
पूर्णांक sun4i_hash_update(काष्ठा ahash_request *areq);
पूर्णांक sun4i_hash_final(काष्ठा ahash_request *areq);
पूर्णांक sun4i_hash_finup(काष्ठा ahash_request *areq);
पूर्णांक sun4i_hash_digest(काष्ठा ahash_request *areq);
पूर्णांक sun4i_hash_export_md5(काष्ठा ahash_request *areq, व्योम *out);
पूर्णांक sun4i_hash_import_md5(काष्ठा ahash_request *areq, स्थिर व्योम *in);
पूर्णांक sun4i_hash_export_sha1(काष्ठा ahash_request *areq, व्योम *out);
पूर्णांक sun4i_hash_import_sha1(काष्ठा ahash_request *areq, स्थिर व्योम *in);

पूर्णांक sun4i_ss_cbc_aes_encrypt(काष्ठा skcipher_request *areq);
पूर्णांक sun4i_ss_cbc_aes_decrypt(काष्ठा skcipher_request *areq);
पूर्णांक sun4i_ss_ecb_aes_encrypt(काष्ठा skcipher_request *areq);
पूर्णांक sun4i_ss_ecb_aes_decrypt(काष्ठा skcipher_request *areq);

पूर्णांक sun4i_ss_cbc_des_encrypt(काष्ठा skcipher_request *areq);
पूर्णांक sun4i_ss_cbc_des_decrypt(काष्ठा skcipher_request *areq);
पूर्णांक sun4i_ss_ecb_des_encrypt(काष्ठा skcipher_request *areq);
पूर्णांक sun4i_ss_ecb_des_decrypt(काष्ठा skcipher_request *areq);

पूर्णांक sun4i_ss_cbc_des3_encrypt(काष्ठा skcipher_request *areq);
पूर्णांक sun4i_ss_cbc_des3_decrypt(काष्ठा skcipher_request *areq);
पूर्णांक sun4i_ss_ecb_des3_encrypt(काष्ठा skcipher_request *areq);
पूर्णांक sun4i_ss_ecb_des3_decrypt(काष्ठा skcipher_request *areq);

पूर्णांक sun4i_ss_cipher_init(काष्ठा crypto_tfm *tfm);
व्योम sun4i_ss_cipher_निकास(काष्ठा crypto_tfm *tfm);
पूर्णांक sun4i_ss_aes_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			अचिन्हित पूर्णांक keylen);
पूर्णांक sun4i_ss_des_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			अचिन्हित पूर्णांक keylen);
पूर्णांक sun4i_ss_des3_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			 अचिन्हित पूर्णांक keylen);
पूर्णांक sun4i_ss_prng_generate(काष्ठा crypto_rng *tfm, स्थिर u8 *src,
			   अचिन्हित पूर्णांक slen, u8 *dst, अचिन्हित पूर्णांक dlen);
पूर्णांक sun4i_ss_prng_seed(काष्ठा crypto_rng *tfm, स्थिर u8 *seed, अचिन्हित पूर्णांक slen);
