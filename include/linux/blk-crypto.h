<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2019 Google LLC
 */

#अगर_अघोषित __LINUX_BLK_CRYPTO_H
#घोषणा __LINUX_BLK_CRYPTO_H

#समावेश <linux/types.h>

क्रमागत blk_crypto_mode_num अणु
	BLK_ENCRYPTION_MODE_INVALID,
	BLK_ENCRYPTION_MODE_AES_256_XTS,
	BLK_ENCRYPTION_MODE_AES_128_CBC_ESSIV,
	BLK_ENCRYPTION_MODE_ADIANTUM,
	BLK_ENCRYPTION_MODE_MAX,
पूर्ण;

#घोषणा BLK_CRYPTO_MAX_KEY_SIZE		64
/**
 * काष्ठा blk_crypto_config - an अंतरभूत encryption key's crypto configuration
 * @crypto_mode: encryption algorithm this key is क्रम
 * @data_unit_size: the data unit size क्रम all encryption/decryptions with this
 *	key.  This is the size in bytes of each inभागidual plaपूर्णांकext and
 *	ciphertext.  This is always a घातer of 2.  It might be e.g. the
 *	fileप्रणाली block size or the disk sector size.
 * @dun_bytes: the maximum number of bytes of DUN used when using this key
 */
काष्ठा blk_crypto_config अणु
	क्रमागत blk_crypto_mode_num crypto_mode;
	अचिन्हित पूर्णांक data_unit_size;
	अचिन्हित पूर्णांक dun_bytes;
पूर्ण;

/**
 * काष्ठा blk_crypto_key - an अंतरभूत encryption key
 * @crypto_cfg: the crypto configuration (like crypto_mode, key size) क्रम this
 *		key
 * @data_unit_size_bits: log2 of data_unit_size
 * @size: size of this key in bytes (determined by @crypto_cfg.crypto_mode)
 * @raw: the raw bytes of this key.  Only the first @size bytes are used.
 *
 * A blk_crypto_key is immutable once created, and many bios can reference it at
 * the same समय.  It must not be मुक्तd until all bios using it have completed
 * and it has been evicted from all devices on which it may have been used.
 */
काष्ठा blk_crypto_key अणु
	काष्ठा blk_crypto_config crypto_cfg;
	अचिन्हित पूर्णांक data_unit_size_bits;
	अचिन्हित पूर्णांक size;
	u8 raw[BLK_CRYPTO_MAX_KEY_SIZE];
पूर्ण;

#घोषणा BLK_CRYPTO_MAX_IV_SIZE		32
#घोषणा BLK_CRYPTO_DUN_ARRAY_SIZE	(BLK_CRYPTO_MAX_IV_SIZE / माप(u64))

/**
 * काष्ठा bio_crypt_ctx - an अंतरभूत encryption context
 * @bc_key: the key, algorithm, and data unit size to use
 * @bc_dun: the data unit number (starting IV) to use
 *
 * A bio_crypt_ctx specअगरies that the contents of the bio will be encrypted (क्रम
 * ग_लिखो requests) or decrypted (क्रम पढ़ो requests) अंतरभूत by the storage device
 * or controller, or by the crypto API fallback.
 */
काष्ठा bio_crypt_ctx अणु
	स्थिर काष्ठा blk_crypto_key	*bc_key;
	u64				bc_dun[BLK_CRYPTO_DUN_ARRAY_SIZE];
पूर्ण;

#समावेश <linux/blk_types.h>
#समावेश <linux/blkdev.h>

काष्ठा request;
काष्ठा request_queue;

#अगर_घोषित CONFIG_BLK_INLINE_ENCRYPTION

अटल अंतरभूत bool bio_has_crypt_ctx(काष्ठा bio *bio)
अणु
	वापस bio->bi_crypt_context;
पूर्ण

व्योम bio_crypt_set_ctx(काष्ठा bio *bio, स्थिर काष्ठा blk_crypto_key *key,
		       स्थिर u64 dun[BLK_CRYPTO_DUN_ARRAY_SIZE],
		       gfp_t gfp_mask);

bool bio_crypt_dun_is_contiguous(स्थिर काष्ठा bio_crypt_ctx *bc,
				 अचिन्हित पूर्णांक bytes,
				 स्थिर u64 next_dun[BLK_CRYPTO_DUN_ARRAY_SIZE]);

पूर्णांक blk_crypto_init_key(काष्ठा blk_crypto_key *blk_key, स्थिर u8 *raw_key,
			क्रमागत blk_crypto_mode_num crypto_mode,
			अचिन्हित पूर्णांक dun_bytes,
			अचिन्हित पूर्णांक data_unit_size);

पूर्णांक blk_crypto_start_using_key(स्थिर काष्ठा blk_crypto_key *key,
			       काष्ठा request_queue *q);

पूर्णांक blk_crypto_evict_key(काष्ठा request_queue *q,
			 स्थिर काष्ठा blk_crypto_key *key);

bool blk_crypto_config_supported(काष्ठा request_queue *q,
				 स्थिर काष्ठा blk_crypto_config *cfg);

#अन्यथा /* CONFIG_BLK_INLINE_ENCRYPTION */

अटल अंतरभूत bool bio_has_crypt_ctx(काष्ठा bio *bio)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर /* CONFIG_BLK_INLINE_ENCRYPTION */

पूर्णांक __bio_crypt_clone(काष्ठा bio *dst, काष्ठा bio *src, gfp_t gfp_mask);
/**
 * bio_crypt_clone - clone bio encryption context
 * @dst: destination bio
 * @src: source bio
 * @gfp_mask: memory allocation flags
 *
 * If @src has an encryption context, clone it to @dst.
 *
 * Return: 0 on success, -ENOMEM अगर out of memory.  -ENOMEM is only possible अगर
 *	   @gfp_mask करोesn't include %__GFP_सूचीECT_RECLAIM.
 */
अटल अंतरभूत पूर्णांक bio_crypt_clone(काष्ठा bio *dst, काष्ठा bio *src,
				  gfp_t gfp_mask)
अणु
	अगर (bio_has_crypt_ctx(src))
		वापस __bio_crypt_clone(dst, src, gfp_mask);
	वापस 0;
पूर्ण

#पूर्ण_अगर /* __LINUX_BLK_CRYPTO_H */
