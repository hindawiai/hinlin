<शैली गुरु>
/*
 * Copyright (C) 2003 Jana Saout <jana@saout.de>
 * Copyright (C) 2004 Clemens Fruhwirth <clemens@enकरोrphin.org>
 * Copyright (C) 2006-2020 Red Hat, Inc. All rights reserved.
 * Copyright (C) 2013-2020 Milan Broz <gmazyland@gmail.com>
 *
 * This file is released under the GPL.
 */

#समावेश <linux/completion.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/key.h>
#समावेश <linux/bपन.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/mempool.h>
#समावेश <linux/slab.h>
#समावेश <linux/crypto.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/atomic.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/प्रकार.स>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/md5.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/skcipher.h>
#समावेश <crypto/aead.h>
#समावेश <crypto/authenc.h>
#समावेश <linux/rtnetlink.h> /* क्रम काष्ठा rtattr and RTA macros only */
#समावेश <linux/key-type.h>
#समावेश <keys/user-type.h>
#समावेश <keys/encrypted-type.h>
#समावेश <keys/trusted-type.h>

#समावेश <linux/device-mapper.h>

#घोषणा DM_MSG_PREFIX "crypt"

/*
 * context holding the current state of a multi-part conversion
 */
काष्ठा convert_context अणु
	काष्ठा completion restart;
	काष्ठा bio *bio_in;
	काष्ठा bio *bio_out;
	काष्ठा bvec_iter iter_in;
	काष्ठा bvec_iter iter_out;
	u64 cc_sector;
	atomic_t cc_pending;
	जोड़ अणु
		काष्ठा skcipher_request *req;
		काष्ठा aead_request *req_aead;
	पूर्ण r;

पूर्ण;

/*
 * per bio निजी data
 */
काष्ठा dm_crypt_io अणु
	काष्ठा crypt_config *cc;
	काष्ठा bio *base_bio;
	u8 *पूर्णांकegrity_metadata;
	bool पूर्णांकegrity_metadata_from_pool;
	काष्ठा work_काष्ठा work;
	काष्ठा tasklet_काष्ठा tasklet;

	काष्ठा convert_context ctx;

	atomic_t io_pending;
	blk_status_t error;
	sector_t sector;

	काष्ठा rb_node rb_node;
पूर्ण CRYPTO_MINALIGN_ATTR;

काष्ठा dm_crypt_request अणु
	काष्ठा convert_context *ctx;
	काष्ठा scatterlist sg_in[4];
	काष्ठा scatterlist sg_out[4];
	u64 iv_sector;
पूर्ण;

काष्ठा crypt_config;

काष्ठा crypt_iv_operations अणु
	पूर्णांक (*ctr)(काष्ठा crypt_config *cc, काष्ठा dm_target *ti,
		   स्थिर अक्षर *opts);
	व्योम (*dtr)(काष्ठा crypt_config *cc);
	पूर्णांक (*init)(काष्ठा crypt_config *cc);
	पूर्णांक (*wipe)(काष्ठा crypt_config *cc);
	पूर्णांक (*generator)(काष्ठा crypt_config *cc, u8 *iv,
			 काष्ठा dm_crypt_request *dmreq);
	पूर्णांक (*post)(काष्ठा crypt_config *cc, u8 *iv,
		    काष्ठा dm_crypt_request *dmreq);
पूर्ण;

काष्ठा iv_benbi_निजी अणु
	पूर्णांक shअगरt;
पूर्ण;

#घोषणा LMK_SEED_SIZE 64 /* hash + 0 */
काष्ठा iv_lmk_निजी अणु
	काष्ठा crypto_shash *hash_tfm;
	u8 *seed;
पूर्ण;

#घोषणा TCW_WHITENING_SIZE 16
काष्ठा iv_tcw_निजी अणु
	काष्ठा crypto_shash *crc32_tfm;
	u8 *iv_seed;
	u8 *whitening;
पूर्ण;

#घोषणा ELEPHANT_MAX_KEY_SIZE 32
काष्ठा iv_elephant_निजी अणु
	काष्ठा crypto_skcipher *tfm;
पूर्ण;

/*
 * Crypt: maps a linear range of a block device
 * and encrypts / decrypts at the same समय.
 */
क्रमागत flags अणु DM_CRYPT_SUSPENDED, DM_CRYPT_KEY_VALID,
	     DM_CRYPT_SAME_CPU, DM_CRYPT_NO_OFFLOAD,
	     DM_CRYPT_NO_READ_WORKQUEUE, DM_CRYPT_NO_WRITE_WORKQUEUE,
	     DM_CRYPT_WRITE_INLINE पूर्ण;

क्रमागत cipher_flags अणु
	CRYPT_MODE_INTEGRITY_AEAD,	/* Use authenticated mode क्रम cipher */
	CRYPT_IV_LARGE_SECTORS,		/* Calculate IV from sector_size, not 512B sectors */
	CRYPT_ENCRYPT_PREPROCESS,	/* Must preprocess data क्रम encryption (elephant) */
पूर्ण;

/*
 * The fields in here must be पढ़ो only after initialization.
 */
काष्ठा crypt_config अणु
	काष्ठा dm_dev *dev;
	sector_t start;

	काष्ठा percpu_counter n_allocated_pages;

	काष्ठा workqueue_काष्ठा *io_queue;
	काष्ठा workqueue_काष्ठा *crypt_queue;

	spinlock_t ग_लिखो_thपढ़ो_lock;
	काष्ठा task_काष्ठा *ग_लिखो_thपढ़ो;
	काष्ठा rb_root ग_लिखो_tree;

	अक्षर *cipher_string;
	अक्षर *cipher_auth;
	अक्षर *key_string;

	स्थिर काष्ठा crypt_iv_operations *iv_gen_ops;
	जोड़ अणु
		काष्ठा iv_benbi_निजी benbi;
		काष्ठा iv_lmk_निजी lmk;
		काष्ठा iv_tcw_निजी tcw;
		काष्ठा iv_elephant_निजी elephant;
	पूर्ण iv_gen_निजी;
	u64 iv_offset;
	अचिन्हित पूर्णांक iv_size;
	अचिन्हित लघु पूर्णांक sector_size;
	अचिन्हित अक्षर sector_shअगरt;

	जोड़ अणु
		काष्ठा crypto_skcipher **tfms;
		काष्ठा crypto_aead **tfms_aead;
	पूर्ण cipher_tfm;
	अचिन्हित tfms_count;
	अचिन्हित दीर्घ cipher_flags;

	/*
	 * Layout of each crypto request:
	 *
	 *   काष्ठा skcipher_request
	 *      context
	 *      padding
	 *   काष्ठा dm_crypt_request
	 *      padding
	 *   IV
	 *
	 * The padding is added so that dm_crypt_request and the IV are
	 * correctly aligned.
	 */
	अचिन्हित पूर्णांक dmreq_start;

	अचिन्हित पूर्णांक per_bio_data_size;

	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक key_size;
	अचिन्हित पूर्णांक key_parts;      /* independent parts in key buffer */
	अचिन्हित पूर्णांक key_extra_size; /* additional keys length */
	अचिन्हित पूर्णांक key_mac_size;   /* MAC key size क्रम authenc(...) */

	अचिन्हित पूर्णांक पूर्णांकegrity_tag_size;
	अचिन्हित पूर्णांक पूर्णांकegrity_iv_size;
	अचिन्हित पूर्णांक on_disk_tag_size;

	/*
	 * pool क्रम per bio निजी data, crypto requests,
	 * encryption requeusts/buffer pages and पूर्णांकegrity tags
	 */
	अचिन्हित tag_pool_max_sectors;
	mempool_t tag_pool;
	mempool_t req_pool;
	mempool_t page_pool;

	काष्ठा bio_set bs;
	काष्ठा mutex bio_alloc_lock;

	u8 *authenc_key; /* space क्रम keys in authenc() क्रमmat (अगर used) */
	u8 key[];
पूर्ण;

#घोषणा MIN_IOS		64
#घोषणा MAX_TAG_SIZE	480
#घोषणा POOL_ENTRY_SIZE	512

अटल DEFINE_SPINLOCK(dm_crypt_clients_lock);
अटल अचिन्हित dm_crypt_clients_n = 0;
अटल अस्थिर अचिन्हित दीर्घ dm_crypt_pages_per_client;
#घोषणा DM_CRYPT_MEMORY_PERCENT			2
#घोषणा DM_CRYPT_MIN_PAGES_PER_CLIENT		(BIO_MAX_VECS * 16)

अटल व्योम clone_init(काष्ठा dm_crypt_io *, काष्ठा bio *);
अटल व्योम kcryptd_queue_crypt(काष्ठा dm_crypt_io *io);
अटल काष्ठा scatterlist *crypt_get_sg_data(काष्ठा crypt_config *cc,
					     काष्ठा scatterlist *sg);

अटल bool crypt_पूर्णांकegrity_aead(काष्ठा crypt_config *cc);

/*
 * Use this to access cipher attributes that are independent of the key.
 */
अटल काष्ठा crypto_skcipher *any_tfm(काष्ठा crypt_config *cc)
अणु
	वापस cc->cipher_tfm.tfms[0];
पूर्ण

अटल काष्ठा crypto_aead *any_tfm_aead(काष्ठा crypt_config *cc)
अणु
	वापस cc->cipher_tfm.tfms_aead[0];
पूर्ण

/*
 * Dअगरferent IV generation algorithms:
 *
 * plain: the initial vector is the 32-bit little-endian version of the sector
 *        number, padded with zeros अगर necessary.
 *
 * plain64: the initial vector is the 64-bit little-endian version of the sector
 *        number, padded with zeros अगर necessary.
 *
 * plain64be: the initial vector is the 64-bit big-endian version of the sector
 *        number, padded with zeros अगर necessary.
 *
 * essiv: "encrypted sector|salt initial vector", the sector number is
 *        encrypted with the bulk cipher using a salt as key. The salt
 *        should be derived from the bulk cipher's key via hashing.
 *
 * benbi: the 64-bit "big-endian 'narrow block'-count", starting at 1
 *        (needed क्रम LRW-32-AES and possible other narrow block modes)
 *
 * null: the initial vector is always zero.  Provides compatibility with
 *       obsolete loop_fish2 devices.  Do not use क्रम new devices.
 *
 * lmk:  Compatible implementation of the block chaining mode used
 *       by the Loop-AES block device encryption प्रणाली
 *       deचिन्हित by Jari Ruusu. See http://loop-aes.sourceक्रमge.net/
 *       It operates on full 512 byte sectors and uses CBC
 *       with an IV derived from the sector number, the data and
 *       optionally extra IV seed.
 *       This means that after decryption the first block
 *       of sector must be tweaked according to decrypted data.
 *       Loop-AES can use three encryption schemes:
 *         version 1: is plain aes-cbc mode
 *         version 2: uses 64 multikey scheme with lmk IV generator
 *         version 3: the same as version 2 with additional IV seed
 *                   (it uses 65 keys, last key is used as IV seed)
 *
 * tcw:  Compatible implementation of the block chaining mode used
 *       by the TrueCrypt device encryption प्रणाली (prior to version 4.1).
 *       For more info see: https://gitlab.com/cryptsetup/cryptsetup/wikis/TrueCryptOnDiskFormat
 *       It operates on full 512 byte sectors and uses CBC
 *       with an IV derived from initial key and the sector number.
 *       In addition, whitening value is applied on every sector, whitening
 *       is calculated from initial key, sector number and mixed using CRC32.
 *       Note that this encryption scheme is vulnerable to watermarking attacks
 *       and should be used क्रम old compatible containers access only.
 *
 * eboiv: Encrypted byte-offset IV (used in Bitlocker in CBC mode)
 *        The IV is encrypted little-endian byte-offset (with the same key
 *        and cipher as the volume).
 *
 * elephant: The extended version of eboiv with additional Elephant dअगरfuser
 *           used with Bitlocker CBC mode.
 *           This mode was used in older Winकरोws प्रणालीs
 *           https://करोwnload.microsoft.com/करोwnload/0/2/3/0238acaf-d3bf-4a6d-b3d6-0a0be4bbb36e/bitlockercipher200608.pdf
 */

अटल पूर्णांक crypt_iv_plain_gen(काष्ठा crypt_config *cc, u8 *iv,
			      काष्ठा dm_crypt_request *dmreq)
अणु
	स_रखो(iv, 0, cc->iv_size);
	*(__le32 *)iv = cpu_to_le32(dmreq->iv_sector & 0xffffffff);

	वापस 0;
पूर्ण

अटल पूर्णांक crypt_iv_plain64_gen(काष्ठा crypt_config *cc, u8 *iv,
				काष्ठा dm_crypt_request *dmreq)
अणु
	स_रखो(iv, 0, cc->iv_size);
	*(__le64 *)iv = cpu_to_le64(dmreq->iv_sector);

	वापस 0;
पूर्ण

अटल पूर्णांक crypt_iv_plain64be_gen(काष्ठा crypt_config *cc, u8 *iv,
				  काष्ठा dm_crypt_request *dmreq)
अणु
	स_रखो(iv, 0, cc->iv_size);
	/* iv_size is at least of size u64; usually it is 16 bytes */
	*(__be64 *)&iv[cc->iv_size - माप(u64)] = cpu_to_be64(dmreq->iv_sector);

	वापस 0;
पूर्ण

अटल पूर्णांक crypt_iv_essiv_gen(काष्ठा crypt_config *cc, u8 *iv,
			      काष्ठा dm_crypt_request *dmreq)
अणु
	/*
	 * ESSIV encryption of the IV is now handled by the crypto API,
	 * so just pass the plain sector number here.
	 */
	स_रखो(iv, 0, cc->iv_size);
	*(__le64 *)iv = cpu_to_le64(dmreq->iv_sector);

	वापस 0;
पूर्ण

अटल पूर्णांक crypt_iv_benbi_ctr(काष्ठा crypt_config *cc, काष्ठा dm_target *ti,
			      स्थिर अक्षर *opts)
अणु
	अचिन्हित bs;
	पूर्णांक log;

	अगर (crypt_पूर्णांकegrity_aead(cc))
		bs = crypto_aead_blocksize(any_tfm_aead(cc));
	अन्यथा
		bs = crypto_skcipher_blocksize(any_tfm(cc));
	log = ilog2(bs);

	/* we need to calculate how far we must shअगरt the sector count
	 * to get the cipher block count, we use this shअगरt in _gen */

	अगर (1 << log != bs) अणु
		ti->error = "cypher blocksize is not a power of 2";
		वापस -EINVAL;
	पूर्ण

	अगर (log > 9) अणु
		ti->error = "cypher blocksize is > 512";
		वापस -EINVAL;
	पूर्ण

	cc->iv_gen_निजी.benbi.shअगरt = 9 - log;

	वापस 0;
पूर्ण

अटल व्योम crypt_iv_benbi_dtr(काष्ठा crypt_config *cc)
अणु
पूर्ण

अटल पूर्णांक crypt_iv_benbi_gen(काष्ठा crypt_config *cc, u8 *iv,
			      काष्ठा dm_crypt_request *dmreq)
अणु
	__be64 val;

	स_रखो(iv, 0, cc->iv_size - माप(u64)); /* rest is cleared below */

	val = cpu_to_be64(((u64)dmreq->iv_sector << cc->iv_gen_निजी.benbi.shअगरt) + 1);
	put_unaligned(val, (__be64 *)(iv + cc->iv_size - माप(u64)));

	वापस 0;
पूर्ण

अटल पूर्णांक crypt_iv_null_gen(काष्ठा crypt_config *cc, u8 *iv,
			     काष्ठा dm_crypt_request *dmreq)
अणु
	स_रखो(iv, 0, cc->iv_size);

	वापस 0;
पूर्ण

अटल व्योम crypt_iv_lmk_dtr(काष्ठा crypt_config *cc)
अणु
	काष्ठा iv_lmk_निजी *lmk = &cc->iv_gen_निजी.lmk;

	अगर (lmk->hash_tfm && !IS_ERR(lmk->hash_tfm))
		crypto_मुक्त_shash(lmk->hash_tfm);
	lmk->hash_tfm = शून्य;

	kमुक्त_sensitive(lmk->seed);
	lmk->seed = शून्य;
पूर्ण

अटल पूर्णांक crypt_iv_lmk_ctr(काष्ठा crypt_config *cc, काष्ठा dm_target *ti,
			    स्थिर अक्षर *opts)
अणु
	काष्ठा iv_lmk_निजी *lmk = &cc->iv_gen_निजी.lmk;

	अगर (cc->sector_size != (1 << SECTOR_SHIFT)) अणु
		ti->error = "Unsupported sector size for LMK";
		वापस -EINVAL;
	पूर्ण

	lmk->hash_tfm = crypto_alloc_shash("md5", 0,
					   CRYPTO_ALG_ALLOCATES_MEMORY);
	अगर (IS_ERR(lmk->hash_tfm)) अणु
		ti->error = "Error initializing LMK hash";
		वापस PTR_ERR(lmk->hash_tfm);
	पूर्ण

	/* No seed in LMK version 2 */
	अगर (cc->key_parts == cc->tfms_count) अणु
		lmk->seed = शून्य;
		वापस 0;
	पूर्ण

	lmk->seed = kzalloc(LMK_SEED_SIZE, GFP_KERNEL);
	अगर (!lmk->seed) अणु
		crypt_iv_lmk_dtr(cc);
		ti->error = "Error kmallocing seed storage in LMK";
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक crypt_iv_lmk_init(काष्ठा crypt_config *cc)
अणु
	काष्ठा iv_lmk_निजी *lmk = &cc->iv_gen_निजी.lmk;
	पूर्णांक subkey_size = cc->key_size / cc->key_parts;

	/* LMK seed is on the position of LMK_KEYS + 1 key */
	अगर (lmk->seed)
		स_नकल(lmk->seed, cc->key + (cc->tfms_count * subkey_size),
		       crypto_shash_digestsize(lmk->hash_tfm));

	वापस 0;
पूर्ण

अटल पूर्णांक crypt_iv_lmk_wipe(काष्ठा crypt_config *cc)
अणु
	काष्ठा iv_lmk_निजी *lmk = &cc->iv_gen_निजी.lmk;

	अगर (lmk->seed)
		स_रखो(lmk->seed, 0, LMK_SEED_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक crypt_iv_lmk_one(काष्ठा crypt_config *cc, u8 *iv,
			    काष्ठा dm_crypt_request *dmreq,
			    u8 *data)
अणु
	काष्ठा iv_lmk_निजी *lmk = &cc->iv_gen_निजी.lmk;
	SHASH_DESC_ON_STACK(desc, lmk->hash_tfm);
	काष्ठा md5_state md5state;
	__le32 buf[4];
	पूर्णांक i, r;

	desc->tfm = lmk->hash_tfm;

	r = crypto_shash_init(desc);
	अगर (r)
		वापस r;

	अगर (lmk->seed) अणु
		r = crypto_shash_update(desc, lmk->seed, LMK_SEED_SIZE);
		अगर (r)
			वापस r;
	पूर्ण

	/* Sector is always 512B, block size 16, add data of blocks 1-31 */
	r = crypto_shash_update(desc, data + 16, 16 * 31);
	अगर (r)
		वापस r;

	/* Sector is cropped to 56 bits here */
	buf[0] = cpu_to_le32(dmreq->iv_sector & 0xFFFFFFFF);
	buf[1] = cpu_to_le32((((u64)dmreq->iv_sector >> 32) & 0x00FFFFFF) | 0x80000000);
	buf[2] = cpu_to_le32(4024);
	buf[3] = 0;
	r = crypto_shash_update(desc, (u8 *)buf, माप(buf));
	अगर (r)
		वापस r;

	/* No MD5 padding here */
	r = crypto_shash_export(desc, &md5state);
	अगर (r)
		वापस r;

	क्रम (i = 0; i < MD5_HASH_WORDS; i++)
		__cpu_to_le32s(&md5state.hash[i]);
	स_नकल(iv, &md5state.hash, cc->iv_size);

	वापस 0;
पूर्ण

अटल पूर्णांक crypt_iv_lmk_gen(काष्ठा crypt_config *cc, u8 *iv,
			    काष्ठा dm_crypt_request *dmreq)
अणु
	काष्ठा scatterlist *sg;
	u8 *src;
	पूर्णांक r = 0;

	अगर (bio_data_dir(dmreq->ctx->bio_in) == WRITE) अणु
		sg = crypt_get_sg_data(cc, dmreq->sg_in);
		src = kmap_atomic(sg_page(sg));
		r = crypt_iv_lmk_one(cc, iv, dmreq, src + sg->offset);
		kunmap_atomic(src);
	पूर्ण अन्यथा
		स_रखो(iv, 0, cc->iv_size);

	वापस r;
पूर्ण

अटल पूर्णांक crypt_iv_lmk_post(काष्ठा crypt_config *cc, u8 *iv,
			     काष्ठा dm_crypt_request *dmreq)
अणु
	काष्ठा scatterlist *sg;
	u8 *dst;
	पूर्णांक r;

	अगर (bio_data_dir(dmreq->ctx->bio_in) == WRITE)
		वापस 0;

	sg = crypt_get_sg_data(cc, dmreq->sg_out);
	dst = kmap_atomic(sg_page(sg));
	r = crypt_iv_lmk_one(cc, iv, dmreq, dst + sg->offset);

	/* Tweak the first block of plaपूर्णांकext sector */
	अगर (!r)
		crypto_xor(dst + sg->offset, iv, cc->iv_size);

	kunmap_atomic(dst);
	वापस r;
पूर्ण

अटल व्योम crypt_iv_tcw_dtr(काष्ठा crypt_config *cc)
अणु
	काष्ठा iv_tcw_निजी *tcw = &cc->iv_gen_निजी.tcw;

	kमुक्त_sensitive(tcw->iv_seed);
	tcw->iv_seed = शून्य;
	kमुक्त_sensitive(tcw->whitening);
	tcw->whitening = शून्य;

	अगर (tcw->crc32_tfm && !IS_ERR(tcw->crc32_tfm))
		crypto_मुक्त_shash(tcw->crc32_tfm);
	tcw->crc32_tfm = शून्य;
पूर्ण

अटल पूर्णांक crypt_iv_tcw_ctr(काष्ठा crypt_config *cc, काष्ठा dm_target *ti,
			    स्थिर अक्षर *opts)
अणु
	काष्ठा iv_tcw_निजी *tcw = &cc->iv_gen_निजी.tcw;

	अगर (cc->sector_size != (1 << SECTOR_SHIFT)) अणु
		ti->error = "Unsupported sector size for TCW";
		वापस -EINVAL;
	पूर्ण

	अगर (cc->key_size <= (cc->iv_size + TCW_WHITENING_SIZE)) अणु
		ti->error = "Wrong key size for TCW";
		वापस -EINVAL;
	पूर्ण

	tcw->crc32_tfm = crypto_alloc_shash("crc32", 0,
					    CRYPTO_ALG_ALLOCATES_MEMORY);
	अगर (IS_ERR(tcw->crc32_tfm)) अणु
		ti->error = "Error initializing CRC32 in TCW";
		वापस PTR_ERR(tcw->crc32_tfm);
	पूर्ण

	tcw->iv_seed = kzalloc(cc->iv_size, GFP_KERNEL);
	tcw->whitening = kzalloc(TCW_WHITENING_SIZE, GFP_KERNEL);
	अगर (!tcw->iv_seed || !tcw->whitening) अणु
		crypt_iv_tcw_dtr(cc);
		ti->error = "Error allocating seed storage in TCW";
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक crypt_iv_tcw_init(काष्ठा crypt_config *cc)
अणु
	काष्ठा iv_tcw_निजी *tcw = &cc->iv_gen_निजी.tcw;
	पूर्णांक key_offset = cc->key_size - cc->iv_size - TCW_WHITENING_SIZE;

	स_नकल(tcw->iv_seed, &cc->key[key_offset], cc->iv_size);
	स_नकल(tcw->whitening, &cc->key[key_offset + cc->iv_size],
	       TCW_WHITENING_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक crypt_iv_tcw_wipe(काष्ठा crypt_config *cc)
अणु
	काष्ठा iv_tcw_निजी *tcw = &cc->iv_gen_निजी.tcw;

	स_रखो(tcw->iv_seed, 0, cc->iv_size);
	स_रखो(tcw->whitening, 0, TCW_WHITENING_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक crypt_iv_tcw_whitening(काष्ठा crypt_config *cc,
				  काष्ठा dm_crypt_request *dmreq,
				  u8 *data)
अणु
	काष्ठा iv_tcw_निजी *tcw = &cc->iv_gen_निजी.tcw;
	__le64 sector = cpu_to_le64(dmreq->iv_sector);
	u8 buf[TCW_WHITENING_SIZE];
	SHASH_DESC_ON_STACK(desc, tcw->crc32_tfm);
	पूर्णांक i, r;

	/* xor whitening with sector number */
	crypto_xor_cpy(buf, tcw->whitening, (u8 *)&sector, 8);
	crypto_xor_cpy(&buf[8], tcw->whitening + 8, (u8 *)&sector, 8);

	/* calculate crc32 क्रम every 32bit part and xor it */
	desc->tfm = tcw->crc32_tfm;
	क्रम (i = 0; i < 4; i++) अणु
		r = crypto_shash_init(desc);
		अगर (r)
			जाओ out;
		r = crypto_shash_update(desc, &buf[i * 4], 4);
		अगर (r)
			जाओ out;
		r = crypto_shash_final(desc, &buf[i * 4]);
		अगर (r)
			जाओ out;
	पूर्ण
	crypto_xor(&buf[0], &buf[12], 4);
	crypto_xor(&buf[4], &buf[8], 4);

	/* apply whitening (8 bytes) to whole sector */
	क्रम (i = 0; i < ((1 << SECTOR_SHIFT) / 8); i++)
		crypto_xor(data + i * 8, buf, 8);
out:
	memzero_explicit(buf, माप(buf));
	वापस r;
पूर्ण

अटल पूर्णांक crypt_iv_tcw_gen(काष्ठा crypt_config *cc, u8 *iv,
			    काष्ठा dm_crypt_request *dmreq)
अणु
	काष्ठा scatterlist *sg;
	काष्ठा iv_tcw_निजी *tcw = &cc->iv_gen_निजी.tcw;
	__le64 sector = cpu_to_le64(dmreq->iv_sector);
	u8 *src;
	पूर्णांक r = 0;

	/* Remove whitening from ciphertext */
	अगर (bio_data_dir(dmreq->ctx->bio_in) != WRITE) अणु
		sg = crypt_get_sg_data(cc, dmreq->sg_in);
		src = kmap_atomic(sg_page(sg));
		r = crypt_iv_tcw_whitening(cc, dmreq, src + sg->offset);
		kunmap_atomic(src);
	पूर्ण

	/* Calculate IV */
	crypto_xor_cpy(iv, tcw->iv_seed, (u8 *)&sector, 8);
	अगर (cc->iv_size > 8)
		crypto_xor_cpy(&iv[8], tcw->iv_seed + 8, (u8 *)&sector,
			       cc->iv_size - 8);

	वापस r;
पूर्ण

अटल पूर्णांक crypt_iv_tcw_post(काष्ठा crypt_config *cc, u8 *iv,
			     काष्ठा dm_crypt_request *dmreq)
अणु
	काष्ठा scatterlist *sg;
	u8 *dst;
	पूर्णांक r;

	अगर (bio_data_dir(dmreq->ctx->bio_in) != WRITE)
		वापस 0;

	/* Apply whitening on ciphertext */
	sg = crypt_get_sg_data(cc, dmreq->sg_out);
	dst = kmap_atomic(sg_page(sg));
	r = crypt_iv_tcw_whitening(cc, dmreq, dst + sg->offset);
	kunmap_atomic(dst);

	वापस r;
पूर्ण

अटल पूर्णांक crypt_iv_अक्रमom_gen(काष्ठा crypt_config *cc, u8 *iv,
				काष्ठा dm_crypt_request *dmreq)
अणु
	/* Used only क्रम ग_लिखोs, there must be an additional space to store IV */
	get_अक्रमom_bytes(iv, cc->iv_size);
	वापस 0;
पूर्ण

अटल पूर्णांक crypt_iv_eboiv_ctr(काष्ठा crypt_config *cc, काष्ठा dm_target *ti,
			    स्थिर अक्षर *opts)
अणु
	अगर (crypt_पूर्णांकegrity_aead(cc)) अणु
		ti->error = "AEAD transforms not supported for EBOIV";
		वापस -EINVAL;
	पूर्ण

	अगर (crypto_skcipher_blocksize(any_tfm(cc)) != cc->iv_size) अणु
		ti->error = "Block size of EBOIV cipher does "
			    "not match IV size of block cipher";
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक crypt_iv_eboiv_gen(काष्ठा crypt_config *cc, u8 *iv,
			    काष्ठा dm_crypt_request *dmreq)
अणु
	u8 buf[MAX_CIPHER_BLOCKSIZE] __aligned(__alignof__(__le64));
	काष्ठा skcipher_request *req;
	काष्ठा scatterlist src, dst;
	DECLARE_CRYPTO_WAIT(रुको);
	पूर्णांक err;

	req = skcipher_request_alloc(any_tfm(cc), GFP_NOIO);
	अगर (!req)
		वापस -ENOMEM;

	स_रखो(buf, 0, cc->iv_size);
	*(__le64 *)buf = cpu_to_le64(dmreq->iv_sector * cc->sector_size);

	sg_init_one(&src, page_address(ZERO_PAGE(0)), cc->iv_size);
	sg_init_one(&dst, iv, cc->iv_size);
	skcipher_request_set_crypt(req, &src, &dst, cc->iv_size, buf);
	skcipher_request_set_callback(req, 0, crypto_req_करोne, &रुको);
	err = crypto_रुको_req(crypto_skcipher_encrypt(req), &रुको);
	skcipher_request_मुक्त(req);

	वापस err;
पूर्ण

अटल व्योम crypt_iv_elephant_dtr(काष्ठा crypt_config *cc)
अणु
	काष्ठा iv_elephant_निजी *elephant = &cc->iv_gen_निजी.elephant;

	crypto_मुक्त_skcipher(elephant->tfm);
	elephant->tfm = शून्य;
पूर्ण

अटल पूर्णांक crypt_iv_elephant_ctr(काष्ठा crypt_config *cc, काष्ठा dm_target *ti,
			    स्थिर अक्षर *opts)
अणु
	काष्ठा iv_elephant_निजी *elephant = &cc->iv_gen_निजी.elephant;
	पूर्णांक r;

	elephant->tfm = crypto_alloc_skcipher("ecb(aes)", 0,
					      CRYPTO_ALG_ALLOCATES_MEMORY);
	अगर (IS_ERR(elephant->tfm)) अणु
		r = PTR_ERR(elephant->tfm);
		elephant->tfm = शून्य;
		वापस r;
	पूर्ण

	r = crypt_iv_eboiv_ctr(cc, ti, शून्य);
	अगर (r)
		crypt_iv_elephant_dtr(cc);
	वापस r;
पूर्ण

अटल व्योम dअगरfuser_disk_to_cpu(u32 *d, माप_प्रकार n)
अणु
#अगर_अघोषित __LITTLE_ENDIAN
	पूर्णांक i;

	क्रम (i = 0; i < n; i++)
		d[i] = le32_to_cpu((__le32)d[i]);
#पूर्ण_अगर
पूर्ण

अटल व्योम dअगरfuser_cpu_to_disk(__le32 *d, माप_प्रकार n)
अणु
#अगर_अघोषित __LITTLE_ENDIAN
	पूर्णांक i;

	क्रम (i = 0; i < n; i++)
		d[i] = cpu_to_le32((u32)d[i]);
#पूर्ण_अगर
पूर्ण

अटल व्योम dअगरfuser_a_decrypt(u32 *d, माप_प्रकार n)
अणु
	पूर्णांक i, i1, i2, i3;

	क्रम (i = 0; i < 5; i++) अणु
		i1 = 0;
		i2 = n - 2;
		i3 = n - 5;

		जबतक (i1 < (n - 1)) अणु
			d[i1] += d[i2] ^ (d[i3] << 9 | d[i3] >> 23);
			i1++; i2++; i3++;

			अगर (i3 >= n)
				i3 -= n;

			d[i1] += d[i2] ^ d[i3];
			i1++; i2++; i3++;

			अगर (i2 >= n)
				i2 -= n;

			d[i1] += d[i2] ^ (d[i3] << 13 | d[i3] >> 19);
			i1++; i2++; i3++;

			d[i1] += d[i2] ^ d[i3];
			i1++; i2++; i3++;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dअगरfuser_a_encrypt(u32 *d, माप_प्रकार n)
अणु
	पूर्णांक i, i1, i2, i3;

	क्रम (i = 0; i < 5; i++) अणु
		i1 = n - 1;
		i2 = n - 2 - 1;
		i3 = n - 5 - 1;

		जबतक (i1 > 0) अणु
			d[i1] -= d[i2] ^ d[i3];
			i1--; i2--; i3--;

			d[i1] -= d[i2] ^ (d[i3] << 13 | d[i3] >> 19);
			i1--; i2--; i3--;

			अगर (i2 < 0)
				i2 += n;

			d[i1] -= d[i2] ^ d[i3];
			i1--; i2--; i3--;

			अगर (i3 < 0)
				i3 += n;

			d[i1] -= d[i2] ^ (d[i3] << 9 | d[i3] >> 23);
			i1--; i2--; i3--;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dअगरfuser_b_decrypt(u32 *d, माप_प्रकार n)
अणु
	पूर्णांक i, i1, i2, i3;

	क्रम (i = 0; i < 3; i++) अणु
		i1 = 0;
		i2 = 2;
		i3 = 5;

		जबतक (i1 < (n - 1)) अणु
			d[i1] += d[i2] ^ d[i3];
			i1++; i2++; i3++;

			d[i1] += d[i2] ^ (d[i3] << 10 | d[i3] >> 22);
			i1++; i2++; i3++;

			अगर (i2 >= n)
				i2 -= n;

			d[i1] += d[i2] ^ d[i3];
			i1++; i2++; i3++;

			अगर (i3 >= n)
				i3 -= n;

			d[i1] += d[i2] ^ (d[i3] << 25 | d[i3] >> 7);
			i1++; i2++; i3++;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dअगरfuser_b_encrypt(u32 *d, माप_प्रकार n)
अणु
	पूर्णांक i, i1, i2, i3;

	क्रम (i = 0; i < 3; i++) अणु
		i1 = n - 1;
		i2 = 2 - 1;
		i3 = 5 - 1;

		जबतक (i1 > 0) अणु
			d[i1] -= d[i2] ^ (d[i3] << 25 | d[i3] >> 7);
			i1--; i2--; i3--;

			अगर (i3 < 0)
				i3 += n;

			d[i1] -= d[i2] ^ d[i3];
			i1--; i2--; i3--;

			अगर (i2 < 0)
				i2 += n;

			d[i1] -= d[i2] ^ (d[i3] << 10 | d[i3] >> 22);
			i1--; i2--; i3--;

			d[i1] -= d[i2] ^ d[i3];
			i1--; i2--; i3--;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक crypt_iv_elephant(काष्ठा crypt_config *cc, काष्ठा dm_crypt_request *dmreq)
अणु
	काष्ठा iv_elephant_निजी *elephant = &cc->iv_gen_निजी.elephant;
	u8 *es, *ks, *data, *data2, *data_offset;
	काष्ठा skcipher_request *req;
	काष्ठा scatterlist *sg, *sg2, src, dst;
	DECLARE_CRYPTO_WAIT(रुको);
	पूर्णांक i, r;

	req = skcipher_request_alloc(elephant->tfm, GFP_NOIO);
	es = kzalloc(16, GFP_NOIO); /* Key क्रम AES */
	ks = kzalloc(32, GFP_NOIO); /* Elephant sector key */

	अगर (!req || !es || !ks) अणु
		r = -ENOMEM;
		जाओ out;
	पूर्ण

	*(__le64 *)es = cpu_to_le64(dmreq->iv_sector * cc->sector_size);

	/* E(Ks, e(s)) */
	sg_init_one(&src, es, 16);
	sg_init_one(&dst, ks, 16);
	skcipher_request_set_crypt(req, &src, &dst, 16, शून्य);
	skcipher_request_set_callback(req, 0, crypto_req_करोne, &रुको);
	r = crypto_रुको_req(crypto_skcipher_encrypt(req), &रुको);
	अगर (r)
		जाओ out;

	/* E(Ks, e'(s)) */
	es[15] = 0x80;
	sg_init_one(&dst, &ks[16], 16);
	r = crypto_रुको_req(crypto_skcipher_encrypt(req), &रुको);
	अगर (r)
		जाओ out;

	sg = crypt_get_sg_data(cc, dmreq->sg_out);
	data = kmap_atomic(sg_page(sg));
	data_offset = data + sg->offset;

	/* Cannot modअगरy original bio, copy to sg_out and apply Elephant to it */
	अगर (bio_data_dir(dmreq->ctx->bio_in) == WRITE) अणु
		sg2 = crypt_get_sg_data(cc, dmreq->sg_in);
		data2 = kmap_atomic(sg_page(sg2));
		स_नकल(data_offset, data2 + sg2->offset, cc->sector_size);
		kunmap_atomic(data2);
	पूर्ण

	अगर (bio_data_dir(dmreq->ctx->bio_in) != WRITE) अणु
		dअगरfuser_disk_to_cpu((u32*)data_offset, cc->sector_size / माप(u32));
		dअगरfuser_b_decrypt((u32*)data_offset, cc->sector_size / माप(u32));
		dअगरfuser_a_decrypt((u32*)data_offset, cc->sector_size / माप(u32));
		dअगरfuser_cpu_to_disk((__le32*)data_offset, cc->sector_size / माप(u32));
	पूर्ण

	क्रम (i = 0; i < (cc->sector_size / 32); i++)
		crypto_xor(data_offset + i * 32, ks, 32);

	अगर (bio_data_dir(dmreq->ctx->bio_in) == WRITE) अणु
		dअगरfuser_disk_to_cpu((u32*)data_offset, cc->sector_size / माप(u32));
		dअगरfuser_a_encrypt((u32*)data_offset, cc->sector_size / माप(u32));
		dअगरfuser_b_encrypt((u32*)data_offset, cc->sector_size / माप(u32));
		dअगरfuser_cpu_to_disk((__le32*)data_offset, cc->sector_size / माप(u32));
	पूर्ण

	kunmap_atomic(data);
out:
	kमुक्त_sensitive(ks);
	kमुक्त_sensitive(es);
	skcipher_request_मुक्त(req);
	वापस r;
पूर्ण

अटल पूर्णांक crypt_iv_elephant_gen(काष्ठा crypt_config *cc, u8 *iv,
			    काष्ठा dm_crypt_request *dmreq)
अणु
	पूर्णांक r;

	अगर (bio_data_dir(dmreq->ctx->bio_in) == WRITE) अणु
		r = crypt_iv_elephant(cc, dmreq);
		अगर (r)
			वापस r;
	पूर्ण

	वापस crypt_iv_eboiv_gen(cc, iv, dmreq);
पूर्ण

अटल पूर्णांक crypt_iv_elephant_post(काष्ठा crypt_config *cc, u8 *iv,
				  काष्ठा dm_crypt_request *dmreq)
अणु
	अगर (bio_data_dir(dmreq->ctx->bio_in) != WRITE)
		वापस crypt_iv_elephant(cc, dmreq);

	वापस 0;
पूर्ण

अटल पूर्णांक crypt_iv_elephant_init(काष्ठा crypt_config *cc)
अणु
	काष्ठा iv_elephant_निजी *elephant = &cc->iv_gen_निजी.elephant;
	पूर्णांक key_offset = cc->key_size - cc->key_extra_size;

	वापस crypto_skcipher_setkey(elephant->tfm, &cc->key[key_offset], cc->key_extra_size);
पूर्ण

अटल पूर्णांक crypt_iv_elephant_wipe(काष्ठा crypt_config *cc)
अणु
	काष्ठा iv_elephant_निजी *elephant = &cc->iv_gen_निजी.elephant;
	u8 key[ELEPHANT_MAX_KEY_SIZE];

	स_रखो(key, 0, cc->key_extra_size);
	वापस crypto_skcipher_setkey(elephant->tfm, key, cc->key_extra_size);
पूर्ण

अटल स्थिर काष्ठा crypt_iv_operations crypt_iv_plain_ops = अणु
	.generator = crypt_iv_plain_gen
पूर्ण;

अटल स्थिर काष्ठा crypt_iv_operations crypt_iv_plain64_ops = अणु
	.generator = crypt_iv_plain64_gen
पूर्ण;

अटल स्थिर काष्ठा crypt_iv_operations crypt_iv_plain64be_ops = अणु
	.generator = crypt_iv_plain64be_gen
पूर्ण;

अटल स्थिर काष्ठा crypt_iv_operations crypt_iv_essiv_ops = अणु
	.generator = crypt_iv_essiv_gen
पूर्ण;

अटल स्थिर काष्ठा crypt_iv_operations crypt_iv_benbi_ops = अणु
	.ctr	   = crypt_iv_benbi_ctr,
	.dtr	   = crypt_iv_benbi_dtr,
	.generator = crypt_iv_benbi_gen
पूर्ण;

अटल स्थिर काष्ठा crypt_iv_operations crypt_iv_null_ops = अणु
	.generator = crypt_iv_null_gen
पूर्ण;

अटल स्थिर काष्ठा crypt_iv_operations crypt_iv_lmk_ops = अणु
	.ctr	   = crypt_iv_lmk_ctr,
	.dtr	   = crypt_iv_lmk_dtr,
	.init	   = crypt_iv_lmk_init,
	.wipe	   = crypt_iv_lmk_wipe,
	.generator = crypt_iv_lmk_gen,
	.post	   = crypt_iv_lmk_post
पूर्ण;

अटल स्थिर काष्ठा crypt_iv_operations crypt_iv_tcw_ops = अणु
	.ctr	   = crypt_iv_tcw_ctr,
	.dtr	   = crypt_iv_tcw_dtr,
	.init	   = crypt_iv_tcw_init,
	.wipe	   = crypt_iv_tcw_wipe,
	.generator = crypt_iv_tcw_gen,
	.post	   = crypt_iv_tcw_post
पूर्ण;

अटल स्थिर काष्ठा crypt_iv_operations crypt_iv_अक्रमom_ops = अणु
	.generator = crypt_iv_अक्रमom_gen
पूर्ण;

अटल स्थिर काष्ठा crypt_iv_operations crypt_iv_eboiv_ops = अणु
	.ctr	   = crypt_iv_eboiv_ctr,
	.generator = crypt_iv_eboiv_gen
पूर्ण;

अटल स्थिर काष्ठा crypt_iv_operations crypt_iv_elephant_ops = अणु
	.ctr	   = crypt_iv_elephant_ctr,
	.dtr	   = crypt_iv_elephant_dtr,
	.init	   = crypt_iv_elephant_init,
	.wipe	   = crypt_iv_elephant_wipe,
	.generator = crypt_iv_elephant_gen,
	.post	   = crypt_iv_elephant_post
पूर्ण;

/*
 * Integrity extensions
 */
अटल bool crypt_पूर्णांकegrity_aead(काष्ठा crypt_config *cc)
अणु
	वापस test_bit(CRYPT_MODE_INTEGRITY_AEAD, &cc->cipher_flags);
पूर्ण

अटल bool crypt_पूर्णांकegrity_hmac(काष्ठा crypt_config *cc)
अणु
	वापस crypt_पूर्णांकegrity_aead(cc) && cc->key_mac_size;
पूर्ण

/* Get sg containing data */
अटल काष्ठा scatterlist *crypt_get_sg_data(काष्ठा crypt_config *cc,
					     काष्ठा scatterlist *sg)
अणु
	अगर (unlikely(crypt_पूर्णांकegrity_aead(cc)))
		वापस &sg[2];

	वापस sg;
पूर्ण

अटल पूर्णांक dm_crypt_पूर्णांकegrity_io_alloc(काष्ठा dm_crypt_io *io, काष्ठा bio *bio)
अणु
	काष्ठा bio_पूर्णांकegrity_payload *bip;
	अचिन्हित पूर्णांक tag_len;
	पूर्णांक ret;

	अगर (!bio_sectors(bio) || !io->cc->on_disk_tag_size)
		वापस 0;

	bip = bio_पूर्णांकegrity_alloc(bio, GFP_NOIO, 1);
	अगर (IS_ERR(bip))
		वापस PTR_ERR(bip);

	tag_len = io->cc->on_disk_tag_size * (bio_sectors(bio) >> io->cc->sector_shअगरt);

	bip->bip_iter.bi_size = tag_len;
	bip->bip_iter.bi_sector = io->cc->start + io->sector;

	ret = bio_पूर्णांकegrity_add_page(bio, virt_to_page(io->पूर्णांकegrity_metadata),
				     tag_len, offset_in_page(io->पूर्णांकegrity_metadata));
	अगर (unlikely(ret != tag_len))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक crypt_पूर्णांकegrity_ctr(काष्ठा crypt_config *cc, काष्ठा dm_target *ti)
अणु
#अगर_घोषित CONFIG_BLK_DEV_INTEGRITY
	काष्ठा blk_पूर्णांकegrity *bi = blk_get_पूर्णांकegrity(cc->dev->bdev->bd_disk);
	काष्ठा mapped_device *md = dm_table_get_md(ti->table);

	/* From now we require underlying device with our पूर्णांकegrity profile */
	अगर (!bi || strहालcmp(bi->profile->name, "DM-DIF-EXT-TAG")) अणु
		ti->error = "Integrity profile not supported.";
		वापस -EINVAL;
	पूर्ण

	अगर (bi->tag_size != cc->on_disk_tag_size ||
	    bi->tuple_size != cc->on_disk_tag_size) अणु
		ti->error = "Integrity profile tag size mismatch.";
		वापस -EINVAL;
	पूर्ण
	अगर (1 << bi->पूर्णांकerval_exp != cc->sector_size) अणु
		ti->error = "Integrity profile sector size mismatch.";
		वापस -EINVAL;
	पूर्ण

	अगर (crypt_पूर्णांकegrity_aead(cc)) अणु
		cc->पूर्णांकegrity_tag_size = cc->on_disk_tag_size - cc->पूर्णांकegrity_iv_size;
		DMDEBUG("%s: Integrity AEAD, tag size %u, IV size %u.", dm_device_name(md),
		       cc->पूर्णांकegrity_tag_size, cc->पूर्णांकegrity_iv_size);

		अगर (crypto_aead_setauthsize(any_tfm_aead(cc), cc->पूर्णांकegrity_tag_size)) अणु
			ti->error = "Integrity AEAD auth tag size is not supported.";
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (cc->पूर्णांकegrity_iv_size)
		DMDEBUG("%s: Additional per-sector space %u bytes for IV.", dm_device_name(md),
		       cc->पूर्णांकegrity_iv_size);

	अगर ((cc->पूर्णांकegrity_tag_size + cc->पूर्णांकegrity_iv_size) != bi->tag_size) अणु
		ti->error = "Not enough space for integrity tag in the profile.";
		वापस -EINVAL;
	पूर्ण

	वापस 0;
#अन्यथा
	ti->error = "Integrity profile not supported.";
	वापस -EINVAL;
#पूर्ण_अगर
पूर्ण

अटल व्योम crypt_convert_init(काष्ठा crypt_config *cc,
			       काष्ठा convert_context *ctx,
			       काष्ठा bio *bio_out, काष्ठा bio *bio_in,
			       sector_t sector)
अणु
	ctx->bio_in = bio_in;
	ctx->bio_out = bio_out;
	अगर (bio_in)
		ctx->iter_in = bio_in->bi_iter;
	अगर (bio_out)
		ctx->iter_out = bio_out->bi_iter;
	ctx->cc_sector = sector + cc->iv_offset;
	init_completion(&ctx->restart);
पूर्ण

अटल काष्ठा dm_crypt_request *dmreq_of_req(काष्ठा crypt_config *cc,
					     व्योम *req)
अणु
	वापस (काष्ठा dm_crypt_request *)((अक्षर *)req + cc->dmreq_start);
पूर्ण

अटल व्योम *req_of_dmreq(काष्ठा crypt_config *cc, काष्ठा dm_crypt_request *dmreq)
अणु
	वापस (व्योम *)((अक्षर *)dmreq - cc->dmreq_start);
पूर्ण

अटल u8 *iv_of_dmreq(काष्ठा crypt_config *cc,
		       काष्ठा dm_crypt_request *dmreq)
अणु
	अगर (crypt_पूर्णांकegrity_aead(cc))
		वापस (u8 *)ALIGN((अचिन्हित दीर्घ)(dmreq + 1),
			crypto_aead_alignmask(any_tfm_aead(cc)) + 1);
	अन्यथा
		वापस (u8 *)ALIGN((अचिन्हित दीर्घ)(dmreq + 1),
			crypto_skcipher_alignmask(any_tfm(cc)) + 1);
पूर्ण

अटल u8 *org_iv_of_dmreq(काष्ठा crypt_config *cc,
		       काष्ठा dm_crypt_request *dmreq)
अणु
	वापस iv_of_dmreq(cc, dmreq) + cc->iv_size;
पूर्ण

अटल __le64 *org_sector_of_dmreq(काष्ठा crypt_config *cc,
		       काष्ठा dm_crypt_request *dmreq)
अणु
	u8 *ptr = iv_of_dmreq(cc, dmreq) + cc->iv_size + cc->iv_size;
	वापस (__le64 *) ptr;
पूर्ण

अटल अचिन्हित पूर्णांक *org_tag_of_dmreq(काष्ठा crypt_config *cc,
		       काष्ठा dm_crypt_request *dmreq)
अणु
	u8 *ptr = iv_of_dmreq(cc, dmreq) + cc->iv_size +
		  cc->iv_size + माप(uपूर्णांक64_t);
	वापस (अचिन्हित पूर्णांक*)ptr;
पूर्ण

अटल व्योम *tag_from_dmreq(काष्ठा crypt_config *cc,
				काष्ठा dm_crypt_request *dmreq)
अणु
	काष्ठा convert_context *ctx = dmreq->ctx;
	काष्ठा dm_crypt_io *io = container_of(ctx, काष्ठा dm_crypt_io, ctx);

	वापस &io->पूर्णांकegrity_metadata[*org_tag_of_dmreq(cc, dmreq) *
		cc->on_disk_tag_size];
पूर्ण

अटल व्योम *iv_tag_from_dmreq(काष्ठा crypt_config *cc,
			       काष्ठा dm_crypt_request *dmreq)
अणु
	वापस tag_from_dmreq(cc, dmreq) + cc->पूर्णांकegrity_tag_size;
पूर्ण

अटल पूर्णांक crypt_convert_block_aead(काष्ठा crypt_config *cc,
				     काष्ठा convert_context *ctx,
				     काष्ठा aead_request *req,
				     अचिन्हित पूर्णांक tag_offset)
अणु
	काष्ठा bio_vec bv_in = bio_iter_iovec(ctx->bio_in, ctx->iter_in);
	काष्ठा bio_vec bv_out = bio_iter_iovec(ctx->bio_out, ctx->iter_out);
	काष्ठा dm_crypt_request *dmreq;
	u8 *iv, *org_iv, *tag_iv, *tag;
	__le64 *sector;
	पूर्णांक r = 0;

	BUG_ON(cc->पूर्णांकegrity_iv_size && cc->पूर्णांकegrity_iv_size != cc->iv_size);

	/* Reject unexpected unaligned bio. */
	अगर (unlikely(bv_in.bv_len & (cc->sector_size - 1)))
		वापस -EIO;

	dmreq = dmreq_of_req(cc, req);
	dmreq->iv_sector = ctx->cc_sector;
	अगर (test_bit(CRYPT_IV_LARGE_SECTORS, &cc->cipher_flags))
		dmreq->iv_sector >>= cc->sector_shअगरt;
	dmreq->ctx = ctx;

	*org_tag_of_dmreq(cc, dmreq) = tag_offset;

	sector = org_sector_of_dmreq(cc, dmreq);
	*sector = cpu_to_le64(ctx->cc_sector - cc->iv_offset);

	iv = iv_of_dmreq(cc, dmreq);
	org_iv = org_iv_of_dmreq(cc, dmreq);
	tag = tag_from_dmreq(cc, dmreq);
	tag_iv = iv_tag_from_dmreq(cc, dmreq);

	/* AEAD request:
	 *  |----- AAD -------|------ DATA -------|-- AUTH TAG --|
	 *  | (authenticated) | (auth+encryption) |              |
	 *  | sector_LE |  IV |  sector in/out    |  tag in/out  |
	 */
	sg_init_table(dmreq->sg_in, 4);
	sg_set_buf(&dmreq->sg_in[0], sector, माप(uपूर्णांक64_t));
	sg_set_buf(&dmreq->sg_in[1], org_iv, cc->iv_size);
	sg_set_page(&dmreq->sg_in[2], bv_in.bv_page, cc->sector_size, bv_in.bv_offset);
	sg_set_buf(&dmreq->sg_in[3], tag, cc->पूर्णांकegrity_tag_size);

	sg_init_table(dmreq->sg_out, 4);
	sg_set_buf(&dmreq->sg_out[0], sector, माप(uपूर्णांक64_t));
	sg_set_buf(&dmreq->sg_out[1], org_iv, cc->iv_size);
	sg_set_page(&dmreq->sg_out[2], bv_out.bv_page, cc->sector_size, bv_out.bv_offset);
	sg_set_buf(&dmreq->sg_out[3], tag, cc->पूर्णांकegrity_tag_size);

	अगर (cc->iv_gen_ops) अणु
		/* For READs use IV stored in पूर्णांकegrity metadata */
		अगर (cc->पूर्णांकegrity_iv_size && bio_data_dir(ctx->bio_in) != WRITE) अणु
			स_नकल(org_iv, tag_iv, cc->iv_size);
		पूर्ण अन्यथा अणु
			r = cc->iv_gen_ops->generator(cc, org_iv, dmreq);
			अगर (r < 0)
				वापस r;
			/* Store generated IV in पूर्णांकegrity metadata */
			अगर (cc->पूर्णांकegrity_iv_size)
				स_नकल(tag_iv, org_iv, cc->iv_size);
		पूर्ण
		/* Working copy of IV, to be modअगरied in crypto API */
		स_नकल(iv, org_iv, cc->iv_size);
	पूर्ण

	aead_request_set_ad(req, माप(uपूर्णांक64_t) + cc->iv_size);
	अगर (bio_data_dir(ctx->bio_in) == WRITE) अणु
		aead_request_set_crypt(req, dmreq->sg_in, dmreq->sg_out,
				       cc->sector_size, iv);
		r = crypto_aead_encrypt(req);
		अगर (cc->पूर्णांकegrity_tag_size + cc->पूर्णांकegrity_iv_size != cc->on_disk_tag_size)
			स_रखो(tag + cc->पूर्णांकegrity_tag_size + cc->पूर्णांकegrity_iv_size, 0,
			       cc->on_disk_tag_size - (cc->पूर्णांकegrity_tag_size + cc->पूर्णांकegrity_iv_size));
	पूर्ण अन्यथा अणु
		aead_request_set_crypt(req, dmreq->sg_in, dmreq->sg_out,
				       cc->sector_size + cc->पूर्णांकegrity_tag_size, iv);
		r = crypto_aead_decrypt(req);
	पूर्ण

	अगर (r == -EBADMSG) अणु
		अक्षर b[BDEVNAME_SIZE];
		DMERR_LIMIT("%s: INTEGRITY AEAD ERROR, sector %llu", bio_devname(ctx->bio_in, b),
			    (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(*sector));
	पूर्ण

	अगर (!r && cc->iv_gen_ops && cc->iv_gen_ops->post)
		r = cc->iv_gen_ops->post(cc, org_iv, dmreq);

	bio_advance_iter(ctx->bio_in, &ctx->iter_in, cc->sector_size);
	bio_advance_iter(ctx->bio_out, &ctx->iter_out, cc->sector_size);

	वापस r;
पूर्ण

अटल पूर्णांक crypt_convert_block_skcipher(काष्ठा crypt_config *cc,
					काष्ठा convert_context *ctx,
					काष्ठा skcipher_request *req,
					अचिन्हित पूर्णांक tag_offset)
अणु
	काष्ठा bio_vec bv_in = bio_iter_iovec(ctx->bio_in, ctx->iter_in);
	काष्ठा bio_vec bv_out = bio_iter_iovec(ctx->bio_out, ctx->iter_out);
	काष्ठा scatterlist *sg_in, *sg_out;
	काष्ठा dm_crypt_request *dmreq;
	u8 *iv, *org_iv, *tag_iv;
	__le64 *sector;
	पूर्णांक r = 0;

	/* Reject unexpected unaligned bio. */
	अगर (unlikely(bv_in.bv_len & (cc->sector_size - 1)))
		वापस -EIO;

	dmreq = dmreq_of_req(cc, req);
	dmreq->iv_sector = ctx->cc_sector;
	अगर (test_bit(CRYPT_IV_LARGE_SECTORS, &cc->cipher_flags))
		dmreq->iv_sector >>= cc->sector_shअगरt;
	dmreq->ctx = ctx;

	*org_tag_of_dmreq(cc, dmreq) = tag_offset;

	iv = iv_of_dmreq(cc, dmreq);
	org_iv = org_iv_of_dmreq(cc, dmreq);
	tag_iv = iv_tag_from_dmreq(cc, dmreq);

	sector = org_sector_of_dmreq(cc, dmreq);
	*sector = cpu_to_le64(ctx->cc_sector - cc->iv_offset);

	/* For skcipher we use only the first sg item */
	sg_in  = &dmreq->sg_in[0];
	sg_out = &dmreq->sg_out[0];

	sg_init_table(sg_in, 1);
	sg_set_page(sg_in, bv_in.bv_page, cc->sector_size, bv_in.bv_offset);

	sg_init_table(sg_out, 1);
	sg_set_page(sg_out, bv_out.bv_page, cc->sector_size, bv_out.bv_offset);

	अगर (cc->iv_gen_ops) अणु
		/* For READs use IV stored in पूर्णांकegrity metadata */
		अगर (cc->पूर्णांकegrity_iv_size && bio_data_dir(ctx->bio_in) != WRITE) अणु
			स_नकल(org_iv, tag_iv, cc->पूर्णांकegrity_iv_size);
		पूर्ण अन्यथा अणु
			r = cc->iv_gen_ops->generator(cc, org_iv, dmreq);
			अगर (r < 0)
				वापस r;
			/* Data can be alपढ़ोy preprocessed in generator */
			अगर (test_bit(CRYPT_ENCRYPT_PREPROCESS, &cc->cipher_flags))
				sg_in = sg_out;
			/* Store generated IV in पूर्णांकegrity metadata */
			अगर (cc->पूर्णांकegrity_iv_size)
				स_नकल(tag_iv, org_iv, cc->पूर्णांकegrity_iv_size);
		पूर्ण
		/* Working copy of IV, to be modअगरied in crypto API */
		स_नकल(iv, org_iv, cc->iv_size);
	पूर्ण

	skcipher_request_set_crypt(req, sg_in, sg_out, cc->sector_size, iv);

	अगर (bio_data_dir(ctx->bio_in) == WRITE)
		r = crypto_skcipher_encrypt(req);
	अन्यथा
		r = crypto_skcipher_decrypt(req);

	अगर (!r && cc->iv_gen_ops && cc->iv_gen_ops->post)
		r = cc->iv_gen_ops->post(cc, org_iv, dmreq);

	bio_advance_iter(ctx->bio_in, &ctx->iter_in, cc->sector_size);
	bio_advance_iter(ctx->bio_out, &ctx->iter_out, cc->sector_size);

	वापस r;
पूर्ण

अटल व्योम kcryptd_async_करोne(काष्ठा crypto_async_request *async_req,
			       पूर्णांक error);

अटल पूर्णांक crypt_alloc_req_skcipher(काष्ठा crypt_config *cc,
				     काष्ठा convert_context *ctx)
अणु
	अचिन्हित key_index = ctx->cc_sector & (cc->tfms_count - 1);

	अगर (!ctx->r.req) अणु
		ctx->r.req = mempool_alloc(&cc->req_pool, in_पूर्णांकerrupt() ? GFP_ATOMIC : GFP_NOIO);
		अगर (!ctx->r.req)
			वापस -ENOMEM;
	पूर्ण

	skcipher_request_set_tfm(ctx->r.req, cc->cipher_tfm.tfms[key_index]);

	/*
	 * Use REQ_MAY_BACKLOG so a cipher driver पूर्णांकernally backlogs
	 * requests अगर driver request queue is full.
	 */
	skcipher_request_set_callback(ctx->r.req,
	    CRYPTO_TFM_REQ_MAY_BACKLOG,
	    kcryptd_async_करोne, dmreq_of_req(cc, ctx->r.req));

	वापस 0;
पूर्ण

अटल पूर्णांक crypt_alloc_req_aead(काष्ठा crypt_config *cc,
				 काष्ठा convert_context *ctx)
अणु
	अगर (!ctx->r.req_aead) अणु
		ctx->r.req_aead = mempool_alloc(&cc->req_pool, in_पूर्णांकerrupt() ? GFP_ATOMIC : GFP_NOIO);
		अगर (!ctx->r.req_aead)
			वापस -ENOMEM;
	पूर्ण

	aead_request_set_tfm(ctx->r.req_aead, cc->cipher_tfm.tfms_aead[0]);

	/*
	 * Use REQ_MAY_BACKLOG so a cipher driver पूर्णांकernally backlogs
	 * requests अगर driver request queue is full.
	 */
	aead_request_set_callback(ctx->r.req_aead,
	    CRYPTO_TFM_REQ_MAY_BACKLOG,
	    kcryptd_async_करोne, dmreq_of_req(cc, ctx->r.req_aead));

	वापस 0;
पूर्ण

अटल पूर्णांक crypt_alloc_req(काष्ठा crypt_config *cc,
			    काष्ठा convert_context *ctx)
अणु
	अगर (crypt_पूर्णांकegrity_aead(cc))
		वापस crypt_alloc_req_aead(cc, ctx);
	अन्यथा
		वापस crypt_alloc_req_skcipher(cc, ctx);
पूर्ण

अटल व्योम crypt_मुक्त_req_skcipher(काष्ठा crypt_config *cc,
				    काष्ठा skcipher_request *req, काष्ठा bio *base_bio)
अणु
	काष्ठा dm_crypt_io *io = dm_per_bio_data(base_bio, cc->per_bio_data_size);

	अगर ((काष्ठा skcipher_request *)(io + 1) != req)
		mempool_मुक्त(req, &cc->req_pool);
पूर्ण

अटल व्योम crypt_मुक्त_req_aead(काष्ठा crypt_config *cc,
				काष्ठा aead_request *req, काष्ठा bio *base_bio)
अणु
	काष्ठा dm_crypt_io *io = dm_per_bio_data(base_bio, cc->per_bio_data_size);

	अगर ((काष्ठा aead_request *)(io + 1) != req)
		mempool_मुक्त(req, &cc->req_pool);
पूर्ण

अटल व्योम crypt_मुक्त_req(काष्ठा crypt_config *cc, व्योम *req, काष्ठा bio *base_bio)
अणु
	अगर (crypt_पूर्णांकegrity_aead(cc))
		crypt_मुक्त_req_aead(cc, req, base_bio);
	अन्यथा
		crypt_मुक्त_req_skcipher(cc, req, base_bio);
पूर्ण

/*
 * Encrypt / decrypt data from one bio to another one (can be the same one)
 */
अटल blk_status_t crypt_convert(काष्ठा crypt_config *cc,
			 काष्ठा convert_context *ctx, bool atomic, bool reset_pending)
अणु
	अचिन्हित पूर्णांक tag_offset = 0;
	अचिन्हित पूर्णांक sector_step = cc->sector_size >> SECTOR_SHIFT;
	पूर्णांक r;

	/*
	 * अगर reset_pending is set we are dealing with the bio क्रम the first समय,
	 * अन्यथा we're continuing to work on the previous bio, so don't mess with
	 * the cc_pending counter
	 */
	अगर (reset_pending)
		atomic_set(&ctx->cc_pending, 1);

	जबतक (ctx->iter_in.bi_size && ctx->iter_out.bi_size) अणु

		r = crypt_alloc_req(cc, ctx);
		अगर (r) अणु
			complete(&ctx->restart);
			वापस BLK_STS_DEV_RESOURCE;
		पूर्ण

		atomic_inc(&ctx->cc_pending);

		अगर (crypt_पूर्णांकegrity_aead(cc))
			r = crypt_convert_block_aead(cc, ctx, ctx->r.req_aead, tag_offset);
		अन्यथा
			r = crypt_convert_block_skcipher(cc, ctx, ctx->r.req, tag_offset);

		चयन (r) अणु
		/*
		 * The request was queued by a crypto driver
		 * but the driver request queue is full, let's रुको.
		 */
		हाल -EBUSY:
			अगर (in_पूर्णांकerrupt()) अणु
				अगर (try_रुको_क्रम_completion(&ctx->restart)) अणु
					/*
					 * we करोn't have to block to रुको क्रम completion,
					 * so proceed
					 */
				पूर्ण अन्यथा अणु
					/*
					 * we can't रुको क्रम completion without blocking
					 * निकास and जारी processing in a workqueue
					 */
					ctx->r.req = शून्य;
					ctx->cc_sector += sector_step;
					tag_offset++;
					वापस BLK_STS_DEV_RESOURCE;
				पूर्ण
			पूर्ण अन्यथा अणु
				रुको_क्रम_completion(&ctx->restart);
			पूर्ण
			reinit_completion(&ctx->restart);
			fallthrough;
		/*
		 * The request is queued and processed asynchronously,
		 * completion function kcryptd_async_करोne() will be called.
		 */
		हाल -EINPROGRESS:
			ctx->r.req = शून्य;
			ctx->cc_sector += sector_step;
			tag_offset++;
			जारी;
		/*
		 * The request was alपढ़ोy processed (synchronously).
		 */
		हाल 0:
			atomic_dec(&ctx->cc_pending);
			ctx->cc_sector += sector_step;
			tag_offset++;
			अगर (!atomic)
				cond_resched();
			जारी;
		/*
		 * There was a data पूर्णांकegrity error.
		 */
		हाल -EBADMSG:
			atomic_dec(&ctx->cc_pending);
			वापस BLK_STS_PROTECTION;
		/*
		 * There was an error जबतक processing the request.
		 */
		शेष:
			atomic_dec(&ctx->cc_pending);
			वापस BLK_STS_IOERR;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम crypt_मुक्त_buffer_pages(काष्ठा crypt_config *cc, काष्ठा bio *clone);

/*
 * Generate a new unfragmented bio with the given size
 * This should never violate the device limitations (but only because
 * max_segment_size is being स्थिरrained to PAGE_SIZE).
 *
 * This function may be called concurrently. If we allocate from the mempool
 * concurrently, there is a possibility of deadlock. For example, अगर we have
 * mempool of 256 pages, two processes, each wanting 256, pages allocate from
 * the mempool concurrently, it may deadlock in a situation where both processes
 * have allocated 128 pages and the mempool is exhausted.
 *
 * In order to aव्योम this scenario we allocate the pages under a mutex.
 *
 * In order to not degrade perक्रमmance with excessive locking, we try
 * non-blocking allocations without a mutex first but on failure we fallback
 * to blocking allocations with a mutex.
 */
अटल काष्ठा bio *crypt_alloc_buffer(काष्ठा dm_crypt_io *io, अचिन्हित size)
अणु
	काष्ठा crypt_config *cc = io->cc;
	काष्ठा bio *clone;
	अचिन्हित पूर्णांक nr_iovecs = (size + PAGE_SIZE - 1) >> PAGE_SHIFT;
	gfp_t gfp_mask = GFP_NOWAIT | __GFP_HIGHMEM;
	अचिन्हित i, len, reमुख्यing_size;
	काष्ठा page *page;

retry:
	अगर (unlikely(gfp_mask & __GFP_सूचीECT_RECLAIM))
		mutex_lock(&cc->bio_alloc_lock);

	clone = bio_alloc_bioset(GFP_NOIO, nr_iovecs, &cc->bs);
	अगर (!clone)
		जाओ out;

	clone_init(io, clone);

	reमुख्यing_size = size;

	क्रम (i = 0; i < nr_iovecs; i++) अणु
		page = mempool_alloc(&cc->page_pool, gfp_mask);
		अगर (!page) अणु
			crypt_मुक्त_buffer_pages(cc, clone);
			bio_put(clone);
			gfp_mask |= __GFP_सूचीECT_RECLAIM;
			जाओ retry;
		पूर्ण

		len = (reमुख्यing_size > PAGE_SIZE) ? PAGE_SIZE : reमुख्यing_size;

		bio_add_page(clone, page, len, 0);

		reमुख्यing_size -= len;
	पूर्ण

	/* Allocate space क्रम पूर्णांकegrity tags */
	अगर (dm_crypt_पूर्णांकegrity_io_alloc(io, clone)) अणु
		crypt_मुक्त_buffer_pages(cc, clone);
		bio_put(clone);
		clone = शून्य;
	पूर्ण
out:
	अगर (unlikely(gfp_mask & __GFP_सूचीECT_RECLAIM))
		mutex_unlock(&cc->bio_alloc_lock);

	वापस clone;
पूर्ण

अटल व्योम crypt_मुक्त_buffer_pages(काष्ठा crypt_config *cc, काष्ठा bio *clone)
अणु
	काष्ठा bio_vec *bv;
	काष्ठा bvec_iter_all iter_all;

	bio_क्रम_each_segment_all(bv, clone, iter_all) अणु
		BUG_ON(!bv->bv_page);
		mempool_मुक्त(bv->bv_page, &cc->page_pool);
	पूर्ण
पूर्ण

अटल व्योम crypt_io_init(काष्ठा dm_crypt_io *io, काष्ठा crypt_config *cc,
			  काष्ठा bio *bio, sector_t sector)
अणु
	io->cc = cc;
	io->base_bio = bio;
	io->sector = sector;
	io->error = 0;
	io->ctx.r.req = शून्य;
	io->पूर्णांकegrity_metadata = शून्य;
	io->पूर्णांकegrity_metadata_from_pool = false;
	atomic_set(&io->io_pending, 0);
पूर्ण

अटल व्योम crypt_inc_pending(काष्ठा dm_crypt_io *io)
अणु
	atomic_inc(&io->io_pending);
पूर्ण

अटल व्योम kcryptd_io_bio_endio(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dm_crypt_io *io = container_of(work, काष्ठा dm_crypt_io, work);
	bio_endio(io->base_bio);
पूर्ण

/*
 * One of the bios was finished. Check क्रम completion of
 * the whole request and correctly clean up the buffer.
 */
अटल व्योम crypt_dec_pending(काष्ठा dm_crypt_io *io)
अणु
	काष्ठा crypt_config *cc = io->cc;
	काष्ठा bio *base_bio = io->base_bio;
	blk_status_t error = io->error;

	अगर (!atomic_dec_and_test(&io->io_pending))
		वापस;

	अगर (io->ctx.r.req)
		crypt_मुक्त_req(cc, io->ctx.r.req, base_bio);

	अगर (unlikely(io->पूर्णांकegrity_metadata_from_pool))
		mempool_मुक्त(io->पूर्णांकegrity_metadata, &io->cc->tag_pool);
	अन्यथा
		kमुक्त(io->पूर्णांकegrity_metadata);

	base_bio->bi_status = error;

	/*
	 * If we are running this function from our tasklet,
	 * we can't call bio_endio() here, because it will call
	 * clone_endio() from dm.c, which in turn will
	 * मुक्त the current काष्ठा dm_crypt_io काष्ठाure with
	 * our tasklet. In this हाल we need to delay bio_endio()
	 * execution to after the tasklet is करोne and dequeued.
	 */
	अगर (tasklet_trylock(&io->tasklet)) अणु
		tasklet_unlock(&io->tasklet);
		bio_endio(base_bio);
		वापस;
	पूर्ण

	INIT_WORK(&io->work, kcryptd_io_bio_endio);
	queue_work(cc->io_queue, &io->work);
पूर्ण

/*
 * kcryptd/kcryptd_io:
 *
 * Needed because it would be very unwise to करो decryption in an
 * पूर्णांकerrupt context.
 *
 * kcryptd perक्रमms the actual encryption or decryption.
 *
 * kcryptd_io perक्रमms the IO submission.
 *
 * They must be separated as otherwise the final stages could be
 * starved by new requests which can block in the first stages due
 * to memory allocation.
 *
 * The work is करोne per CPU global क्रम all dm-crypt instances.
 * They should not depend on each other and करो not block.
 */
अटल व्योम crypt_endio(काष्ठा bio *clone)
अणु
	काष्ठा dm_crypt_io *io = clone->bi_निजी;
	काष्ठा crypt_config *cc = io->cc;
	अचिन्हित rw = bio_data_dir(clone);
	blk_status_t error;

	/*
	 * मुक्त the processed pages
	 */
	अगर (rw == WRITE)
		crypt_मुक्त_buffer_pages(cc, clone);

	error = clone->bi_status;
	bio_put(clone);

	अगर (rw == READ && !error) अणु
		kcryptd_queue_crypt(io);
		वापस;
	पूर्ण

	अगर (unlikely(error))
		io->error = error;

	crypt_dec_pending(io);
पूर्ण

अटल व्योम clone_init(काष्ठा dm_crypt_io *io, काष्ठा bio *clone)
अणु
	काष्ठा crypt_config *cc = io->cc;

	clone->bi_निजी = io;
	clone->bi_end_io  = crypt_endio;
	bio_set_dev(clone, cc->dev->bdev);
	clone->bi_opf	  = io->base_bio->bi_opf;
पूर्ण

अटल पूर्णांक kcryptd_io_पढ़ो(काष्ठा dm_crypt_io *io, gfp_t gfp)
अणु
	काष्ठा crypt_config *cc = io->cc;
	काष्ठा bio *clone;

	/*
	 * We need the original biovec array in order to decrypt
	 * the whole bio data *afterwards* -- thanks to immutable
	 * biovecs we करोn't need to worry about the block layer
	 * modअगरying the biovec array; so leverage bio_clone_fast().
	 */
	clone = bio_clone_fast(io->base_bio, gfp, &cc->bs);
	अगर (!clone)
		वापस 1;

	crypt_inc_pending(io);

	clone_init(io, clone);
	clone->bi_iter.bi_sector = cc->start + io->sector;

	अगर (dm_crypt_पूर्णांकegrity_io_alloc(io, clone)) अणु
		crypt_dec_pending(io);
		bio_put(clone);
		वापस 1;
	पूर्ण

	submit_bio_noacct(clone);
	वापस 0;
पूर्ण

अटल व्योम kcryptd_io_पढ़ो_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dm_crypt_io *io = container_of(work, काष्ठा dm_crypt_io, work);

	crypt_inc_pending(io);
	अगर (kcryptd_io_पढ़ो(io, GFP_NOIO))
		io->error = BLK_STS_RESOURCE;
	crypt_dec_pending(io);
पूर्ण

अटल व्योम kcryptd_queue_पढ़ो(काष्ठा dm_crypt_io *io)
अणु
	काष्ठा crypt_config *cc = io->cc;

	INIT_WORK(&io->work, kcryptd_io_पढ़ो_work);
	queue_work(cc->io_queue, &io->work);
पूर्ण

अटल व्योम kcryptd_io_ग_लिखो(काष्ठा dm_crypt_io *io)
अणु
	काष्ठा bio *clone = io->ctx.bio_out;

	submit_bio_noacct(clone);
पूर्ण

#घोषणा crypt_io_from_node(node) rb_entry((node), काष्ठा dm_crypt_io, rb_node)

अटल पूर्णांक dmcrypt_ग_लिखो(व्योम *data)
अणु
	काष्ठा crypt_config *cc = data;
	काष्ठा dm_crypt_io *io;

	जबतक (1) अणु
		काष्ठा rb_root ग_लिखो_tree;
		काष्ठा blk_plug plug;

		spin_lock_irq(&cc->ग_लिखो_thपढ़ो_lock);
जारी_locked:

		अगर (!RB_EMPTY_ROOT(&cc->ग_लिखो_tree))
			जाओ pop_from_list;

		set_current_state(TASK_INTERRUPTIBLE);

		spin_unlock_irq(&cc->ग_लिखो_thपढ़ो_lock);

		अगर (unlikely(kthपढ़ो_should_stop())) अणु
			set_current_state(TASK_RUNNING);
			अवरोध;
		पूर्ण

		schedule();

		set_current_state(TASK_RUNNING);
		spin_lock_irq(&cc->ग_लिखो_thपढ़ो_lock);
		जाओ जारी_locked;

pop_from_list:
		ग_लिखो_tree = cc->ग_लिखो_tree;
		cc->ग_लिखो_tree = RB_ROOT;
		spin_unlock_irq(&cc->ग_लिखो_thपढ़ो_lock);

		BUG_ON(rb_parent(ग_लिखो_tree.rb_node));

		/*
		 * Note: we cannot walk the tree here with rb_next because
		 * the काष्ठाures may be मुक्तd when kcryptd_io_ग_लिखो is called.
		 */
		blk_start_plug(&plug);
		करो अणु
			io = crypt_io_from_node(rb_first(&ग_लिखो_tree));
			rb_erase(&io->rb_node, &ग_लिखो_tree);
			kcryptd_io_ग_लिखो(io);
		पूर्ण जबतक (!RB_EMPTY_ROOT(&ग_लिखो_tree));
		blk_finish_plug(&plug);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम kcryptd_crypt_ग_लिखो_io_submit(काष्ठा dm_crypt_io *io, पूर्णांक async)
अणु
	काष्ठा bio *clone = io->ctx.bio_out;
	काष्ठा crypt_config *cc = io->cc;
	अचिन्हित दीर्घ flags;
	sector_t sector;
	काष्ठा rb_node **rbp, *parent;

	अगर (unlikely(io->error)) अणु
		crypt_मुक्त_buffer_pages(cc, clone);
		bio_put(clone);
		crypt_dec_pending(io);
		वापस;
	पूर्ण

	/* crypt_convert should have filled the clone bio */
	BUG_ON(io->ctx.iter_out.bi_size);

	clone->bi_iter.bi_sector = cc->start + io->sector;

	अगर ((likely(!async) && test_bit(DM_CRYPT_NO_OFFLOAD, &cc->flags)) ||
	    test_bit(DM_CRYPT_NO_WRITE_WORKQUEUE, &cc->flags)) अणु
		submit_bio_noacct(clone);
		वापस;
	पूर्ण

	spin_lock_irqsave(&cc->ग_लिखो_thपढ़ो_lock, flags);
	अगर (RB_EMPTY_ROOT(&cc->ग_लिखो_tree))
		wake_up_process(cc->ग_लिखो_thपढ़ो);
	rbp = &cc->ग_लिखो_tree.rb_node;
	parent = शून्य;
	sector = io->sector;
	जबतक (*rbp) अणु
		parent = *rbp;
		अगर (sector < crypt_io_from_node(parent)->sector)
			rbp = &(*rbp)->rb_left;
		अन्यथा
			rbp = &(*rbp)->rb_right;
	पूर्ण
	rb_link_node(&io->rb_node, parent, rbp);
	rb_insert_color(&io->rb_node, &cc->ग_लिखो_tree);
	spin_unlock_irqrestore(&cc->ग_लिखो_thपढ़ो_lock, flags);
पूर्ण

अटल bool kcryptd_crypt_ग_लिखो_अंतरभूत(काष्ठा crypt_config *cc,
				       काष्ठा convert_context *ctx)

अणु
	अगर (!test_bit(DM_CRYPT_WRITE_INLINE, &cc->flags))
		वापस false;

	/*
	 * Note: zone append ग_लिखोs (REQ_OP_ZONE_APPEND) करो not have ordering
	 * स्थिरraपूर्णांकs so they करो not need to be issued अंतरभूत by
	 * kcryptd_crypt_ग_लिखो_convert().
	 */
	चयन (bio_op(ctx->bio_in)) अणु
	हाल REQ_OP_WRITE:
	हाल REQ_OP_WRITE_SAME:
	हाल REQ_OP_WRITE_ZEROES:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम kcryptd_crypt_ग_लिखो_जारी(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dm_crypt_io *io = container_of(work, काष्ठा dm_crypt_io, work);
	काष्ठा crypt_config *cc = io->cc;
	काष्ठा convert_context *ctx = &io->ctx;
	पूर्णांक crypt_finished;
	sector_t sector = io->sector;
	blk_status_t r;

	रुको_क्रम_completion(&ctx->restart);
	reinit_completion(&ctx->restart);

	r = crypt_convert(cc, &io->ctx, true, false);
	अगर (r)
		io->error = r;
	crypt_finished = atomic_dec_and_test(&ctx->cc_pending);
	अगर (!crypt_finished && kcryptd_crypt_ग_लिखो_अंतरभूत(cc, ctx)) अणु
		/* Wait क्रम completion संकेतed by kcryptd_async_करोne() */
		रुको_क्रम_completion(&ctx->restart);
		crypt_finished = 1;
	पूर्ण

	/* Encryption was alपढ़ोy finished, submit io now */
	अगर (crypt_finished) अणु
		kcryptd_crypt_ग_लिखो_io_submit(io, 0);
		io->sector = sector;
	पूर्ण

	crypt_dec_pending(io);
पूर्ण

अटल व्योम kcryptd_crypt_ग_लिखो_convert(काष्ठा dm_crypt_io *io)
अणु
	काष्ठा crypt_config *cc = io->cc;
	काष्ठा convert_context *ctx = &io->ctx;
	काष्ठा bio *clone;
	पूर्णांक crypt_finished;
	sector_t sector = io->sector;
	blk_status_t r;

	/*
	 * Prevent io from disappearing until this function completes.
	 */
	crypt_inc_pending(io);
	crypt_convert_init(cc, ctx, शून्य, io->base_bio, sector);

	clone = crypt_alloc_buffer(io, io->base_bio->bi_iter.bi_size);
	अगर (unlikely(!clone)) अणु
		io->error = BLK_STS_IOERR;
		जाओ dec;
	पूर्ण

	io->ctx.bio_out = clone;
	io->ctx.iter_out = clone->bi_iter;

	sector += bio_sectors(clone);

	crypt_inc_pending(io);
	r = crypt_convert(cc, ctx,
			  test_bit(DM_CRYPT_NO_WRITE_WORKQUEUE, &cc->flags), true);
	/*
	 * Crypto API backlogged the request, because its queue was full
	 * and we're in softirq context, so जारी from a workqueue
	 * (TODO: is it actually possible to be in softirq in the ग_लिखो path?)
	 */
	अगर (r == BLK_STS_DEV_RESOURCE) अणु
		INIT_WORK(&io->work, kcryptd_crypt_ग_लिखो_जारी);
		queue_work(cc->crypt_queue, &io->work);
		वापस;
	पूर्ण
	अगर (r)
		io->error = r;
	crypt_finished = atomic_dec_and_test(&ctx->cc_pending);
	अगर (!crypt_finished && kcryptd_crypt_ग_लिखो_अंतरभूत(cc, ctx)) अणु
		/* Wait क्रम completion संकेतed by kcryptd_async_करोne() */
		रुको_क्रम_completion(&ctx->restart);
		crypt_finished = 1;
	पूर्ण

	/* Encryption was alपढ़ोy finished, submit io now */
	अगर (crypt_finished) अणु
		kcryptd_crypt_ग_लिखो_io_submit(io, 0);
		io->sector = sector;
	पूर्ण

dec:
	crypt_dec_pending(io);
पूर्ण

अटल व्योम kcryptd_crypt_पढ़ो_करोne(काष्ठा dm_crypt_io *io)
अणु
	crypt_dec_pending(io);
पूर्ण

अटल व्योम kcryptd_crypt_पढ़ो_जारी(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dm_crypt_io *io = container_of(work, काष्ठा dm_crypt_io, work);
	काष्ठा crypt_config *cc = io->cc;
	blk_status_t r;

	रुको_क्रम_completion(&io->ctx.restart);
	reinit_completion(&io->ctx.restart);

	r = crypt_convert(cc, &io->ctx, true, false);
	अगर (r)
		io->error = r;

	अगर (atomic_dec_and_test(&io->ctx.cc_pending))
		kcryptd_crypt_पढ़ो_करोne(io);

	crypt_dec_pending(io);
पूर्ण

अटल व्योम kcryptd_crypt_पढ़ो_convert(काष्ठा dm_crypt_io *io)
अणु
	काष्ठा crypt_config *cc = io->cc;
	blk_status_t r;

	crypt_inc_pending(io);

	crypt_convert_init(cc, &io->ctx, io->base_bio, io->base_bio,
			   io->sector);

	r = crypt_convert(cc, &io->ctx,
			  test_bit(DM_CRYPT_NO_READ_WORKQUEUE, &cc->flags), true);
	/*
	 * Crypto API backlogged the request, because its queue was full
	 * and we're in softirq context, so जारी from a workqueue
	 */
	अगर (r == BLK_STS_DEV_RESOURCE) अणु
		INIT_WORK(&io->work, kcryptd_crypt_पढ़ो_जारी);
		queue_work(cc->crypt_queue, &io->work);
		वापस;
	पूर्ण
	अगर (r)
		io->error = r;

	अगर (atomic_dec_and_test(&io->ctx.cc_pending))
		kcryptd_crypt_पढ़ो_करोne(io);

	crypt_dec_pending(io);
पूर्ण

अटल व्योम kcryptd_async_करोne(काष्ठा crypto_async_request *async_req,
			       पूर्णांक error)
अणु
	काष्ठा dm_crypt_request *dmreq = async_req->data;
	काष्ठा convert_context *ctx = dmreq->ctx;
	काष्ठा dm_crypt_io *io = container_of(ctx, काष्ठा dm_crypt_io, ctx);
	काष्ठा crypt_config *cc = io->cc;

	/*
	 * A request from crypto driver backlog is going to be processed now,
	 * finish the completion and जारी in crypt_convert().
	 * (Callback will be called क्रम the second समय क्रम this request.)
	 */
	अगर (error == -EINPROGRESS) अणु
		complete(&ctx->restart);
		वापस;
	पूर्ण

	अगर (!error && cc->iv_gen_ops && cc->iv_gen_ops->post)
		error = cc->iv_gen_ops->post(cc, org_iv_of_dmreq(cc, dmreq), dmreq);

	अगर (error == -EBADMSG) अणु
		अक्षर b[BDEVNAME_SIZE];
		DMERR_LIMIT("%s: INTEGRITY AEAD ERROR, sector %llu", bio_devname(ctx->bio_in, b),
			    (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(*org_sector_of_dmreq(cc, dmreq)));
		io->error = BLK_STS_PROTECTION;
	पूर्ण अन्यथा अगर (error < 0)
		io->error = BLK_STS_IOERR;

	crypt_मुक्त_req(cc, req_of_dmreq(cc, dmreq), io->base_bio);

	अगर (!atomic_dec_and_test(&ctx->cc_pending))
		वापस;

	/*
	 * The request is fully completed: क्रम अंतरभूत ग_लिखोs, let
	 * kcryptd_crypt_ग_लिखो_convert() करो the IO submission.
	 */
	अगर (bio_data_dir(io->base_bio) == READ) अणु
		kcryptd_crypt_पढ़ो_करोne(io);
		वापस;
	पूर्ण

	अगर (kcryptd_crypt_ग_लिखो_अंतरभूत(cc, ctx)) अणु
		complete(&ctx->restart);
		वापस;
	पूर्ण

	kcryptd_crypt_ग_लिखो_io_submit(io, 1);
पूर्ण

अटल व्योम kcryptd_crypt(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dm_crypt_io *io = container_of(work, काष्ठा dm_crypt_io, work);

	अगर (bio_data_dir(io->base_bio) == READ)
		kcryptd_crypt_पढ़ो_convert(io);
	अन्यथा
		kcryptd_crypt_ग_लिखो_convert(io);
पूर्ण

अटल व्योम kcryptd_crypt_tasklet(अचिन्हित दीर्घ work)
अणु
	kcryptd_crypt((काष्ठा work_काष्ठा *)work);
पूर्ण

अटल व्योम kcryptd_queue_crypt(काष्ठा dm_crypt_io *io)
अणु
	काष्ठा crypt_config *cc = io->cc;

	अगर ((bio_data_dir(io->base_bio) == READ && test_bit(DM_CRYPT_NO_READ_WORKQUEUE, &cc->flags)) ||
	    (bio_data_dir(io->base_bio) == WRITE && test_bit(DM_CRYPT_NO_WRITE_WORKQUEUE, &cc->flags))) अणु
		/*
		 * in_irq(): Crypto API's skcipher_walk_first() refuses to work in hard IRQ context.
		 * irqs_disabled(): the kernel may run some IO completion from the idle thपढ़ो, but
		 * it is being executed with irqs disabled.
		 */
		अगर (in_irq() || irqs_disabled()) अणु
			tasklet_init(&io->tasklet, kcryptd_crypt_tasklet, (अचिन्हित दीर्घ)&io->work);
			tasklet_schedule(&io->tasklet);
			वापस;
		पूर्ण

		kcryptd_crypt(&io->work);
		वापस;
	पूर्ण

	INIT_WORK(&io->work, kcryptd_crypt);
	queue_work(cc->crypt_queue, &io->work);
पूर्ण

अटल व्योम crypt_मुक्त_tfms_aead(काष्ठा crypt_config *cc)
अणु
	अगर (!cc->cipher_tfm.tfms_aead)
		वापस;

	अगर (cc->cipher_tfm.tfms_aead[0] && !IS_ERR(cc->cipher_tfm.tfms_aead[0])) अणु
		crypto_मुक्त_aead(cc->cipher_tfm.tfms_aead[0]);
		cc->cipher_tfm.tfms_aead[0] = शून्य;
	पूर्ण

	kमुक्त(cc->cipher_tfm.tfms_aead);
	cc->cipher_tfm.tfms_aead = शून्य;
पूर्ण

अटल व्योम crypt_मुक्त_tfms_skcipher(काष्ठा crypt_config *cc)
अणु
	अचिन्हित i;

	अगर (!cc->cipher_tfm.tfms)
		वापस;

	क्रम (i = 0; i < cc->tfms_count; i++)
		अगर (cc->cipher_tfm.tfms[i] && !IS_ERR(cc->cipher_tfm.tfms[i])) अणु
			crypto_मुक्त_skcipher(cc->cipher_tfm.tfms[i]);
			cc->cipher_tfm.tfms[i] = शून्य;
		पूर्ण

	kमुक्त(cc->cipher_tfm.tfms);
	cc->cipher_tfm.tfms = शून्य;
पूर्ण

अटल व्योम crypt_मुक्त_tfms(काष्ठा crypt_config *cc)
अणु
	अगर (crypt_पूर्णांकegrity_aead(cc))
		crypt_मुक्त_tfms_aead(cc);
	अन्यथा
		crypt_मुक्त_tfms_skcipher(cc);
पूर्ण

अटल पूर्णांक crypt_alloc_tfms_skcipher(काष्ठा crypt_config *cc, अक्षर *ciphermode)
अणु
	अचिन्हित i;
	पूर्णांक err;

	cc->cipher_tfm.tfms = kसुस्मृति(cc->tfms_count,
				      माप(काष्ठा crypto_skcipher *),
				      GFP_KERNEL);
	अगर (!cc->cipher_tfm.tfms)
		वापस -ENOMEM;

	क्रम (i = 0; i < cc->tfms_count; i++) अणु
		cc->cipher_tfm.tfms[i] = crypto_alloc_skcipher(ciphermode, 0,
						CRYPTO_ALG_ALLOCATES_MEMORY);
		अगर (IS_ERR(cc->cipher_tfm.tfms[i])) अणु
			err = PTR_ERR(cc->cipher_tfm.tfms[i]);
			crypt_मुक्त_tfms(cc);
			वापस err;
		पूर्ण
	पूर्ण

	/*
	 * dm-crypt perक्रमmance can vary greatly depending on which crypto
	 * algorithm implementation is used.  Help people debug perक्रमmance
	 * problems by logging the ->cra_driver_name.
	 */
	DMDEBUG_LIMIT("%s using implementation \"%s\"", ciphermode,
	       crypto_skcipher_alg(any_tfm(cc))->base.cra_driver_name);
	वापस 0;
पूर्ण

अटल पूर्णांक crypt_alloc_tfms_aead(काष्ठा crypt_config *cc, अक्षर *ciphermode)
अणु
	पूर्णांक err;

	cc->cipher_tfm.tfms = kदो_स्मृति(माप(काष्ठा crypto_aead *), GFP_KERNEL);
	अगर (!cc->cipher_tfm.tfms)
		वापस -ENOMEM;

	cc->cipher_tfm.tfms_aead[0] = crypto_alloc_aead(ciphermode, 0,
						CRYPTO_ALG_ALLOCATES_MEMORY);
	अगर (IS_ERR(cc->cipher_tfm.tfms_aead[0])) अणु
		err = PTR_ERR(cc->cipher_tfm.tfms_aead[0]);
		crypt_मुक्त_tfms(cc);
		वापस err;
	पूर्ण

	DMDEBUG_LIMIT("%s using implementation \"%s\"", ciphermode,
	       crypto_aead_alg(any_tfm_aead(cc))->base.cra_driver_name);
	वापस 0;
पूर्ण

अटल पूर्णांक crypt_alloc_tfms(काष्ठा crypt_config *cc, अक्षर *ciphermode)
अणु
	अगर (crypt_पूर्णांकegrity_aead(cc))
		वापस crypt_alloc_tfms_aead(cc, ciphermode);
	अन्यथा
		वापस crypt_alloc_tfms_skcipher(cc, ciphermode);
पूर्ण

अटल अचिन्हित crypt_subkey_size(काष्ठा crypt_config *cc)
अणु
	वापस (cc->key_size - cc->key_extra_size) >> ilog2(cc->tfms_count);
पूर्ण

अटल अचिन्हित crypt_authenckey_size(काष्ठा crypt_config *cc)
अणु
	वापस crypt_subkey_size(cc) + RTA_SPACE(माप(काष्ठा crypto_authenc_key_param));
पूर्ण

/*
 * If AEAD is composed like authenc(hmac(sha256),xts(aes)),
 * the key must be क्रम some reason in special क्रमmat.
 * This funcion converts cc->key to this special क्रमmat.
 */
अटल व्योम crypt_copy_authenckey(अक्षर *p, स्थिर व्योम *key,
				  अचिन्हित enckeylen, अचिन्हित authkeylen)
अणु
	काष्ठा crypto_authenc_key_param *param;
	काष्ठा rtattr *rta;

	rta = (काष्ठा rtattr *)p;
	param = RTA_DATA(rta);
	param->enckeylen = cpu_to_be32(enckeylen);
	rta->rta_len = RTA_LENGTH(माप(*param));
	rta->rta_type = CRYPTO_AUTHENC_KEYA_PARAM;
	p += RTA_SPACE(माप(*param));
	स_नकल(p, key + enckeylen, authkeylen);
	p += authkeylen;
	स_नकल(p, key, enckeylen);
पूर्ण

अटल पूर्णांक crypt_setkey(काष्ठा crypt_config *cc)
अणु
	अचिन्हित subkey_size;
	पूर्णांक err = 0, i, r;

	/* Ignore extra keys (which are used क्रम IV etc) */
	subkey_size = crypt_subkey_size(cc);

	अगर (crypt_पूर्णांकegrity_hmac(cc)) अणु
		अगर (subkey_size < cc->key_mac_size)
			वापस -EINVAL;

		crypt_copy_authenckey(cc->authenc_key, cc->key,
				      subkey_size - cc->key_mac_size,
				      cc->key_mac_size);
	पूर्ण

	क्रम (i = 0; i < cc->tfms_count; i++) अणु
		अगर (crypt_पूर्णांकegrity_hmac(cc))
			r = crypto_aead_setkey(cc->cipher_tfm.tfms_aead[i],
				cc->authenc_key, crypt_authenckey_size(cc));
		अन्यथा अगर (crypt_पूर्णांकegrity_aead(cc))
			r = crypto_aead_setkey(cc->cipher_tfm.tfms_aead[i],
					       cc->key + (i * subkey_size),
					       subkey_size);
		अन्यथा
			r = crypto_skcipher_setkey(cc->cipher_tfm.tfms[i],
						   cc->key + (i * subkey_size),
						   subkey_size);
		अगर (r)
			err = r;
	पूर्ण

	अगर (crypt_पूर्णांकegrity_hmac(cc))
		memzero_explicit(cc->authenc_key, crypt_authenckey_size(cc));

	वापस err;
पूर्ण

#अगर_घोषित CONFIG_KEYS

अटल bool contains_whitespace(स्थिर अक्षर *str)
अणु
	जबतक (*str)
		अगर (है_खाली(*str++))
			वापस true;
	वापस false;
पूर्ण

अटल पूर्णांक set_key_user(काष्ठा crypt_config *cc, काष्ठा key *key)
अणु
	स्थिर काष्ठा user_key_payload *ukp;

	ukp = user_key_payload_locked(key);
	अगर (!ukp)
		वापस -EKEYREVOKED;

	अगर (cc->key_size != ukp->datalen)
		वापस -EINVAL;

	स_नकल(cc->key, ukp->data, cc->key_size);

	वापस 0;
पूर्ण

अटल पूर्णांक set_key_encrypted(काष्ठा crypt_config *cc, काष्ठा key *key)
अणु
	स्थिर काष्ठा encrypted_key_payload *ekp;

	ekp = key->payload.data[0];
	अगर (!ekp)
		वापस -EKEYREVOKED;

	अगर (cc->key_size != ekp->decrypted_datalen)
		वापस -EINVAL;

	स_नकल(cc->key, ekp->decrypted_data, cc->key_size);

	वापस 0;
पूर्ण

अटल पूर्णांक set_key_trusted(काष्ठा crypt_config *cc, काष्ठा key *key)
अणु
	स्थिर काष्ठा trusted_key_payload *tkp;

	tkp = key->payload.data[0];
	अगर (!tkp)
		वापस -EKEYREVOKED;

	अगर (cc->key_size != tkp->key_len)
		वापस -EINVAL;

	स_नकल(cc->key, tkp->key, cc->key_size);

	वापस 0;
पूर्ण

अटल पूर्णांक crypt_set_keyring_key(काष्ठा crypt_config *cc, स्थिर अक्षर *key_string)
अणु
	अक्षर *new_key_string, *key_desc;
	पूर्णांक ret;
	काष्ठा key_type *type;
	काष्ठा key *key;
	पूर्णांक (*set_key)(काष्ठा crypt_config *cc, काष्ठा key *key);

	/*
	 * Reject key_string with whitespace. dm core currently lacks code क्रम
	 * proper whitespace escaping in arguments on DM_TABLE_STATUS path.
	 */
	अगर (contains_whitespace(key_string)) अणु
		DMERR("whitespace chars not allowed in key string");
		वापस -EINVAL;
	पूर्ण

	/* look क्रम next ':' separating key_type from key_description */
	key_desc = strpbrk(key_string, ":");
	अगर (!key_desc || key_desc == key_string || !म_माप(key_desc + 1))
		वापस -EINVAL;

	अगर (!म_भेदन(key_string, "logon:", key_desc - key_string + 1)) अणु
		type = &key_type_logon;
		set_key = set_key_user;
	पूर्ण अन्यथा अगर (!म_भेदन(key_string, "user:", key_desc - key_string + 1)) अणु
		type = &key_type_user;
		set_key = set_key_user;
	पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_ENCRYPTED_KEYS) &&
		   !म_भेदन(key_string, "encrypted:", key_desc - key_string + 1)) अणु
		type = &key_type_encrypted;
		set_key = set_key_encrypted;
	पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_TRUSTED_KEYS) &&
	           !म_भेदन(key_string, "trusted:", key_desc - key_string + 1)) अणु
		type = &key_type_trusted;
		set_key = set_key_trusted;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	new_key_string = kstrdup(key_string, GFP_KERNEL);
	अगर (!new_key_string)
		वापस -ENOMEM;

	key = request_key(type, key_desc + 1, शून्य);
	अगर (IS_ERR(key)) अणु
		kमुक्त_sensitive(new_key_string);
		वापस PTR_ERR(key);
	पूर्ण

	करोwn_पढ़ो(&key->sem);

	ret = set_key(cc, key);
	अगर (ret < 0) अणु
		up_पढ़ो(&key->sem);
		key_put(key);
		kमुक्त_sensitive(new_key_string);
		वापस ret;
	पूर्ण

	up_पढ़ो(&key->sem);
	key_put(key);

	/* clear the flag since following operations may invalidate previously valid key */
	clear_bit(DM_CRYPT_KEY_VALID, &cc->flags);

	ret = crypt_setkey(cc);

	अगर (!ret) अणु
		set_bit(DM_CRYPT_KEY_VALID, &cc->flags);
		kमुक्त_sensitive(cc->key_string);
		cc->key_string = new_key_string;
	पूर्ण अन्यथा
		kमुक्त_sensitive(new_key_string);

	वापस ret;
पूर्ण

अटल पूर्णांक get_key_size(अक्षर **key_string)
अणु
	अक्षर *colon, dummy;
	पूर्णांक ret;

	अगर (*key_string[0] != ':')
		वापस म_माप(*key_string) >> 1;

	/* look क्रम next ':' in key string */
	colon = strpbrk(*key_string + 1, ":");
	अगर (!colon)
		वापस -EINVAL;

	अगर (माला_पूछो(*key_string + 1, "%u%c", &ret, &dummy) != 2 || dummy != ':')
		वापस -EINVAL;

	*key_string = colon;

	/* reमुख्यing key string should be :<logon|user>:<key_desc> */

	वापस ret;
पूर्ण

#अन्यथा

अटल पूर्णांक crypt_set_keyring_key(काष्ठा crypt_config *cc, स्थिर अक्षर *key_string)
अणु
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक get_key_size(अक्षर **key_string)
अणु
	वापस (*key_string[0] == ':') ? -EINVAL : म_माप(*key_string) >> 1;
पूर्ण

#पूर्ण_अगर /* CONFIG_KEYS */

अटल पूर्णांक crypt_set_key(काष्ठा crypt_config *cc, अक्षर *key)
अणु
	पूर्णांक r = -EINVAL;
	पूर्णांक key_string_len = म_माप(key);

	/* Hyphen (which gives a key_size of zero) means there is no key. */
	अगर (!cc->key_size && म_भेद(key, "-"))
		जाओ out;

	/* ':' means the key is in kernel keyring, लघु-circuit normal key processing */
	अगर (key[0] == ':') अणु
		r = crypt_set_keyring_key(cc, key + 1);
		जाओ out;
	पूर्ण

	/* clear the flag since following operations may invalidate previously valid key */
	clear_bit(DM_CRYPT_KEY_VALID, &cc->flags);

	/* wipe references to any kernel keyring key */
	kमुक्त_sensitive(cc->key_string);
	cc->key_string = शून्य;

	/* Decode key from its hex representation. */
	अगर (cc->key_size && hex2bin(cc->key, key, cc->key_size) < 0)
		जाओ out;

	r = crypt_setkey(cc);
	अगर (!r)
		set_bit(DM_CRYPT_KEY_VALID, &cc->flags);

out:
	/* Hex key string not needed after here, so wipe it. */
	स_रखो(key, '0', key_string_len);

	वापस r;
पूर्ण

अटल पूर्णांक crypt_wipe_key(काष्ठा crypt_config *cc)
अणु
	पूर्णांक r;

	clear_bit(DM_CRYPT_KEY_VALID, &cc->flags);
	get_अक्रमom_bytes(&cc->key, cc->key_size);

	/* Wipe IV निजी keys */
	अगर (cc->iv_gen_ops && cc->iv_gen_ops->wipe) अणु
		r = cc->iv_gen_ops->wipe(cc);
		अगर (r)
			वापस r;
	पूर्ण

	kमुक्त_sensitive(cc->key_string);
	cc->key_string = शून्य;
	r = crypt_setkey(cc);
	स_रखो(&cc->key, 0, cc->key_size * माप(u8));

	वापस r;
पूर्ण

अटल व्योम crypt_calculate_pages_per_client(व्योम)
अणु
	अचिन्हित दीर्घ pages = (totalram_pages() - totalhigh_pages()) * DM_CRYPT_MEMORY_PERCENT / 100;

	अगर (!dm_crypt_clients_n)
		वापस;

	pages /= dm_crypt_clients_n;
	अगर (pages < DM_CRYPT_MIN_PAGES_PER_CLIENT)
		pages = DM_CRYPT_MIN_PAGES_PER_CLIENT;
	dm_crypt_pages_per_client = pages;
पूर्ण

अटल व्योम *crypt_page_alloc(gfp_t gfp_mask, व्योम *pool_data)
अणु
	काष्ठा crypt_config *cc = pool_data;
	काष्ठा page *page;

	अगर (unlikely(percpu_counter_compare(&cc->n_allocated_pages, dm_crypt_pages_per_client) >= 0) &&
	    likely(gfp_mask & __GFP_NORETRY))
		वापस शून्य;

	page = alloc_page(gfp_mask);
	अगर (likely(page != शून्य))
		percpu_counter_add(&cc->n_allocated_pages, 1);

	वापस page;
पूर्ण

अटल व्योम crypt_page_मुक्त(व्योम *page, व्योम *pool_data)
अणु
	काष्ठा crypt_config *cc = pool_data;

	__मुक्त_page(page);
	percpu_counter_sub(&cc->n_allocated_pages, 1);
पूर्ण

अटल व्योम crypt_dtr(काष्ठा dm_target *ti)
अणु
	काष्ठा crypt_config *cc = ti->निजी;

	ti->निजी = शून्य;

	अगर (!cc)
		वापस;

	अगर (cc->ग_लिखो_thपढ़ो)
		kthपढ़ो_stop(cc->ग_लिखो_thपढ़ो);

	अगर (cc->io_queue)
		destroy_workqueue(cc->io_queue);
	अगर (cc->crypt_queue)
		destroy_workqueue(cc->crypt_queue);

	crypt_मुक्त_tfms(cc);

	bioset_निकास(&cc->bs);

	mempool_निकास(&cc->page_pool);
	mempool_निकास(&cc->req_pool);
	mempool_निकास(&cc->tag_pool);

	WARN_ON(percpu_counter_sum(&cc->n_allocated_pages) != 0);
	percpu_counter_destroy(&cc->n_allocated_pages);

	अगर (cc->iv_gen_ops && cc->iv_gen_ops->dtr)
		cc->iv_gen_ops->dtr(cc);

	अगर (cc->dev)
		dm_put_device(ti, cc->dev);

	kमुक्त_sensitive(cc->cipher_string);
	kमुक्त_sensitive(cc->key_string);
	kमुक्त_sensitive(cc->cipher_auth);
	kमुक्त_sensitive(cc->authenc_key);

	mutex_destroy(&cc->bio_alloc_lock);

	/* Must zero key material beक्रमe मुक्तing */
	kमुक्त_sensitive(cc);

	spin_lock(&dm_crypt_clients_lock);
	WARN_ON(!dm_crypt_clients_n);
	dm_crypt_clients_n--;
	crypt_calculate_pages_per_client();
	spin_unlock(&dm_crypt_clients_lock);
पूर्ण

अटल पूर्णांक crypt_ctr_ivmode(काष्ठा dm_target *ti, स्थिर अक्षर *ivmode)
अणु
	काष्ठा crypt_config *cc = ti->निजी;

	अगर (crypt_पूर्णांकegrity_aead(cc))
		cc->iv_size = crypto_aead_ivsize(any_tfm_aead(cc));
	अन्यथा
		cc->iv_size = crypto_skcipher_ivsize(any_tfm(cc));

	अगर (cc->iv_size)
		/* at least a 64 bit sector number should fit in our buffer */
		cc->iv_size = max(cc->iv_size,
				  (अचिन्हित पूर्णांक)(माप(u64) / माप(u8)));
	अन्यथा अगर (ivmode) अणु
		DMWARN("Selected cipher does not support IVs");
		ivmode = शून्य;
	पूर्ण

	/* Choose ivmode, see comments at iv code. */
	अगर (ivmode == शून्य)
		cc->iv_gen_ops = शून्य;
	अन्यथा अगर (म_भेद(ivmode, "plain") == 0)
		cc->iv_gen_ops = &crypt_iv_plain_ops;
	अन्यथा अगर (म_भेद(ivmode, "plain64") == 0)
		cc->iv_gen_ops = &crypt_iv_plain64_ops;
	अन्यथा अगर (म_भेद(ivmode, "plain64be") == 0)
		cc->iv_gen_ops = &crypt_iv_plain64be_ops;
	अन्यथा अगर (म_भेद(ivmode, "essiv") == 0)
		cc->iv_gen_ops = &crypt_iv_essiv_ops;
	अन्यथा अगर (म_भेद(ivmode, "benbi") == 0)
		cc->iv_gen_ops = &crypt_iv_benbi_ops;
	अन्यथा अगर (म_भेद(ivmode, "null") == 0)
		cc->iv_gen_ops = &crypt_iv_null_ops;
	अन्यथा अगर (म_भेद(ivmode, "eboiv") == 0)
		cc->iv_gen_ops = &crypt_iv_eboiv_ops;
	अन्यथा अगर (म_भेद(ivmode, "elephant") == 0) अणु
		cc->iv_gen_ops = &crypt_iv_elephant_ops;
		cc->key_parts = 2;
		cc->key_extra_size = cc->key_size / 2;
		अगर (cc->key_extra_size > ELEPHANT_MAX_KEY_SIZE)
			वापस -EINVAL;
		set_bit(CRYPT_ENCRYPT_PREPROCESS, &cc->cipher_flags);
	पूर्ण अन्यथा अगर (म_भेद(ivmode, "lmk") == 0) अणु
		cc->iv_gen_ops = &crypt_iv_lmk_ops;
		/*
		 * Version 2 and 3 is recognised according
		 * to length of provided multi-key string.
		 * If present (version 3), last key is used as IV seed.
		 * All keys (including IV seed) are always the same size.
		 */
		अगर (cc->key_size % cc->key_parts) अणु
			cc->key_parts++;
			cc->key_extra_size = cc->key_size / cc->key_parts;
		पूर्ण
	पूर्ण अन्यथा अगर (म_भेद(ivmode, "tcw") == 0) अणु
		cc->iv_gen_ops = &crypt_iv_tcw_ops;
		cc->key_parts += 2; /* IV + whitening */
		cc->key_extra_size = cc->iv_size + TCW_WHITENING_SIZE;
	पूर्ण अन्यथा अगर (म_भेद(ivmode, "random") == 0) अणु
		cc->iv_gen_ops = &crypt_iv_अक्रमom_ops;
		/* Need storage space in पूर्णांकegrity fields. */
		cc->पूर्णांकegrity_iv_size = cc->iv_size;
	पूर्ण अन्यथा अणु
		ti->error = "Invalid IV mode";
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Workaround to parse HMAC algorithm from AEAD crypto API spec.
 * The HMAC is needed to calculate tag size (HMAC digest size).
 * This should be probably करोne by crypto-api calls (once available...)
 */
अटल पूर्णांक crypt_ctr_auth_cipher(काष्ठा crypt_config *cc, अक्षर *cipher_api)
अणु
	अक्षर *start, *end, *mac_alg = शून्य;
	काष्ठा crypto_ahash *mac;

	अगर (!strstarts(cipher_api, "authenc("))
		वापस 0;

	start = म_अक्षर(cipher_api, '(');
	end = म_अक्षर(cipher_api, ',');
	अगर (!start || !end || ++start > end)
		वापस -EINVAL;

	mac_alg = kzalloc(end - start + 1, GFP_KERNEL);
	अगर (!mac_alg)
		वापस -ENOMEM;
	म_नकलन(mac_alg, start, end - start);

	mac = crypto_alloc_ahash(mac_alg, 0, CRYPTO_ALG_ALLOCATES_MEMORY);
	kमुक्त(mac_alg);

	अगर (IS_ERR(mac))
		वापस PTR_ERR(mac);

	cc->key_mac_size = crypto_ahash_digestsize(mac);
	crypto_मुक्त_ahash(mac);

	cc->authenc_key = kदो_स्मृति(crypt_authenckey_size(cc), GFP_KERNEL);
	अगर (!cc->authenc_key)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक crypt_ctr_cipher_new(काष्ठा dm_target *ti, अक्षर *cipher_in, अक्षर *key,
				अक्षर **ivmode, अक्षर **ivopts)
अणु
	काष्ठा crypt_config *cc = ti->निजी;
	अक्षर *पंचांगp, *cipher_api, buf[CRYPTO_MAX_ALG_NAME];
	पूर्णांक ret = -EINVAL;

	cc->tfms_count = 1;

	/*
	 * New क्रमmat (capi: prefix)
	 * capi:cipher_api_spec-iv:ivopts
	 */
	पंचांगp = &cipher_in[म_माप("capi:")];

	/* Separate IV options अगर present, it can contain another '-' in hash name */
	*ivopts = म_खोजप(पंचांगp, ':');
	अगर (*ivopts) अणु
		**ivopts = '\0';
		(*ivopts)++;
	पूर्ण
	/* Parse IV mode */
	*ivmode = म_खोजप(पंचांगp, '-');
	अगर (*ivmode) अणु
		**ivmode = '\0';
		(*ivmode)++;
	पूर्ण
	/* The rest is crypto API spec */
	cipher_api = पंचांगp;

	/* Alloc AEAD, can be used only in new क्रमmat. */
	अगर (crypt_पूर्णांकegrity_aead(cc)) अणु
		ret = crypt_ctr_auth_cipher(cc, cipher_api);
		अगर (ret < 0) अणु
			ti->error = "Invalid AEAD cipher spec";
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	अगर (*ivmode && !म_भेद(*ivmode, "lmk"))
		cc->tfms_count = 64;

	अगर (*ivmode && !म_भेद(*ivmode, "essiv")) अणु
		अगर (!*ivopts) अणु
			ti->error = "Digest algorithm missing for ESSIV mode";
			वापस -EINVAL;
		पूर्ण
		ret = snम_लिखो(buf, CRYPTO_MAX_ALG_NAME, "essiv(%s,%s)",
			       cipher_api, *ivopts);
		अगर (ret < 0 || ret >= CRYPTO_MAX_ALG_NAME) अणु
			ti->error = "Cannot allocate cipher string";
			वापस -ENOMEM;
		पूर्ण
		cipher_api = buf;
	पूर्ण

	cc->key_parts = cc->tfms_count;

	/* Allocate cipher */
	ret = crypt_alloc_tfms(cc, cipher_api);
	अगर (ret < 0) अणु
		ti->error = "Error allocating crypto tfm";
		वापस ret;
	पूर्ण

	अगर (crypt_पूर्णांकegrity_aead(cc))
		cc->iv_size = crypto_aead_ivsize(any_tfm_aead(cc));
	अन्यथा
		cc->iv_size = crypto_skcipher_ivsize(any_tfm(cc));

	वापस 0;
पूर्ण

अटल पूर्णांक crypt_ctr_cipher_old(काष्ठा dm_target *ti, अक्षर *cipher_in, अक्षर *key,
				अक्षर **ivmode, अक्षर **ivopts)
अणु
	काष्ठा crypt_config *cc = ti->निजी;
	अक्षर *पंचांगp, *cipher, *chainmode, *keycount;
	अक्षर *cipher_api = शून्य;
	पूर्णांक ret = -EINVAL;
	अक्षर dummy;

	अगर (म_अक्षर(cipher_in, '(') || crypt_पूर्णांकegrity_aead(cc)) अणु
		ti->error = "Bad cipher specification";
		वापस -EINVAL;
	पूर्ण

	/*
	 * Legacy dm-crypt cipher specअगरication
	 * cipher[:keycount]-mode-iv:ivopts
	 */
	पंचांगp = cipher_in;
	keycount = strsep(&पंचांगp, "-");
	cipher = strsep(&keycount, ":");

	अगर (!keycount)
		cc->tfms_count = 1;
	अन्यथा अगर (माला_पूछो(keycount, "%u%c", &cc->tfms_count, &dummy) != 1 ||
		 !is_घातer_of_2(cc->tfms_count)) अणु
		ti->error = "Bad cipher key count specification";
		वापस -EINVAL;
	पूर्ण
	cc->key_parts = cc->tfms_count;

	chainmode = strsep(&पंचांगp, "-");
	*ivmode = strsep(&पंचांगp, ":");
	*ivopts = पंचांगp;

	/*
	 * For compatibility with the original dm-crypt mapping क्रमmat, अगर
	 * only the cipher name is supplied, use cbc-plain.
	 */
	अगर (!chainmode || (!म_भेद(chainmode, "plain") && !*ivmode)) अणु
		chainmode = "cbc";
		*ivmode = "plain";
	पूर्ण

	अगर (म_भेद(chainmode, "ecb") && !*ivmode) अणु
		ti->error = "IV mechanism required";
		वापस -EINVAL;
	पूर्ण

	cipher_api = kदो_स्मृति(CRYPTO_MAX_ALG_NAME, GFP_KERNEL);
	अगर (!cipher_api)
		जाओ bad_mem;

	अगर (*ivmode && !म_भेद(*ivmode, "essiv")) अणु
		अगर (!*ivopts) अणु
			ti->error = "Digest algorithm missing for ESSIV mode";
			kमुक्त(cipher_api);
			वापस -EINVAL;
		पूर्ण
		ret = snम_लिखो(cipher_api, CRYPTO_MAX_ALG_NAME,
			       "essiv(%s(%s),%s)", chainmode, cipher, *ivopts);
	पूर्ण अन्यथा अणु
		ret = snम_लिखो(cipher_api, CRYPTO_MAX_ALG_NAME,
			       "%s(%s)", chainmode, cipher);
	पूर्ण
	अगर (ret < 0 || ret >= CRYPTO_MAX_ALG_NAME) अणु
		kमुक्त(cipher_api);
		जाओ bad_mem;
	पूर्ण

	/* Allocate cipher */
	ret = crypt_alloc_tfms(cc, cipher_api);
	अगर (ret < 0) अणु
		ti->error = "Error allocating crypto tfm";
		kमुक्त(cipher_api);
		वापस ret;
	पूर्ण
	kमुक्त(cipher_api);

	वापस 0;
bad_mem:
	ti->error = "Cannot allocate cipher strings";
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक crypt_ctr_cipher(काष्ठा dm_target *ti, अक्षर *cipher_in, अक्षर *key)
अणु
	काष्ठा crypt_config *cc = ti->निजी;
	अक्षर *ivmode = शून्य, *ivopts = शून्य;
	पूर्णांक ret;

	cc->cipher_string = kstrdup(cipher_in, GFP_KERNEL);
	अगर (!cc->cipher_string) अणु
		ti->error = "Cannot allocate cipher strings";
		वापस -ENOMEM;
	पूर्ण

	अगर (strstarts(cipher_in, "capi:"))
		ret = crypt_ctr_cipher_new(ti, cipher_in, key, &ivmode, &ivopts);
	अन्यथा
		ret = crypt_ctr_cipher_old(ti, cipher_in, key, &ivmode, &ivopts);
	अगर (ret)
		वापस ret;

	/* Initialize IV */
	ret = crypt_ctr_ivmode(ti, ivmode);
	अगर (ret < 0)
		वापस ret;

	/* Initialize and set key */
	ret = crypt_set_key(cc, key);
	अगर (ret < 0) अणु
		ti->error = "Error decoding and setting key";
		वापस ret;
	पूर्ण

	/* Allocate IV */
	अगर (cc->iv_gen_ops && cc->iv_gen_ops->ctr) अणु
		ret = cc->iv_gen_ops->ctr(cc, ti, ivopts);
		अगर (ret < 0) अणु
			ti->error = "Error creating IV";
			वापस ret;
		पूर्ण
	पूर्ण

	/* Initialize IV (set keys क्रम ESSIV etc) */
	अगर (cc->iv_gen_ops && cc->iv_gen_ops->init) अणु
		ret = cc->iv_gen_ops->init(cc);
		अगर (ret < 0) अणु
			ti->error = "Error initialising IV";
			वापस ret;
		पूर्ण
	पूर्ण

	/* wipe the kernel key payload copy */
	अगर (cc->key_string)
		स_रखो(cc->key, 0, cc->key_size * माप(u8));

	वापस ret;
पूर्ण

अटल पूर्णांक crypt_ctr_optional(काष्ठा dm_target *ti, अचिन्हित पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा crypt_config *cc = ti->निजी;
	काष्ठा dm_arg_set as;
	अटल स्थिर काष्ठा dm_arg _args[] = अणु
		अणु0, 8, "Invalid number of feature args"पूर्ण,
	पूर्ण;
	अचिन्हित पूर्णांक opt_params, val;
	स्थिर अक्षर *opt_string, *sval;
	अक्षर dummy;
	पूर्णांक ret;

	/* Optional parameters */
	as.argc = argc;
	as.argv = argv;

	ret = dm_पढ़ो_arg_group(_args, &as, &opt_params, &ti->error);
	अगर (ret)
		वापस ret;

	जबतक (opt_params--) अणु
		opt_string = dm_shअगरt_arg(&as);
		अगर (!opt_string) अणु
			ti->error = "Not enough feature arguments";
			वापस -EINVAL;
		पूर्ण

		अगर (!strहालcmp(opt_string, "allow_discards"))
			ti->num_discard_bios = 1;

		अन्यथा अगर (!strहालcmp(opt_string, "same_cpu_crypt"))
			set_bit(DM_CRYPT_SAME_CPU, &cc->flags);

		अन्यथा अगर (!strहालcmp(opt_string, "submit_from_crypt_cpus"))
			set_bit(DM_CRYPT_NO_OFFLOAD, &cc->flags);
		अन्यथा अगर (!strहालcmp(opt_string, "no_read_workqueue"))
			set_bit(DM_CRYPT_NO_READ_WORKQUEUE, &cc->flags);
		अन्यथा अगर (!strहालcmp(opt_string, "no_write_workqueue"))
			set_bit(DM_CRYPT_NO_WRITE_WORKQUEUE, &cc->flags);
		अन्यथा अगर (माला_पूछो(opt_string, "integrity:%u:", &val) == 1) अणु
			अगर (val == 0 || val > MAX_TAG_SIZE) अणु
				ti->error = "Invalid integrity arguments";
				वापस -EINVAL;
			पूर्ण
			cc->on_disk_tag_size = val;
			sval = म_अक्षर(opt_string + म_माप("integrity:"), ':') + 1;
			अगर (!strहालcmp(sval, "aead")) अणु
				set_bit(CRYPT_MODE_INTEGRITY_AEAD, &cc->cipher_flags);
			पूर्ण अन्यथा  अगर (strहालcmp(sval, "none")) अणु
				ti->error = "Unknown integrity profile";
				वापस -EINVAL;
			पूर्ण

			cc->cipher_auth = kstrdup(sval, GFP_KERNEL);
			अगर (!cc->cipher_auth)
				वापस -ENOMEM;
		पूर्ण अन्यथा अगर (माला_पूछो(opt_string, "sector_size:%hu%c", &cc->sector_size, &dummy) == 1) अणु
			अगर (cc->sector_size < (1 << SECTOR_SHIFT) ||
			    cc->sector_size > 4096 ||
			    (cc->sector_size & (cc->sector_size - 1))) अणु
				ti->error = "Invalid feature value for sector_size";
				वापस -EINVAL;
			पूर्ण
			अगर (ti->len & ((cc->sector_size >> SECTOR_SHIFT) - 1)) अणु
				ti->error = "Device size is not multiple of sector_size feature";
				वापस -EINVAL;
			पूर्ण
			cc->sector_shअगरt = __ffs(cc->sector_size) - SECTOR_SHIFT;
		पूर्ण अन्यथा अगर (!strहालcmp(opt_string, "iv_large_sectors"))
			set_bit(CRYPT_IV_LARGE_SECTORS, &cc->cipher_flags);
		अन्यथा अणु
			ti->error = "Invalid feature arguments";
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_BLK_DEV_ZONED
अटल पूर्णांक crypt_report_zones(काष्ठा dm_target *ti,
		काष्ठा dm_report_zones_args *args, अचिन्हित पूर्णांक nr_zones)
अणु
	काष्ठा crypt_config *cc = ti->निजी;
	sector_t sector = cc->start + dm_target_offset(ti, args->next_sector);

	args->start = cc->start;
	वापस blkdev_report_zones(cc->dev->bdev, sector, nr_zones,
				   dm_report_zones_cb, args);
पूर्ण
#अन्यथा
#घोषणा crypt_report_zones शून्य
#पूर्ण_अगर

/*
 * Conकाष्ठा an encryption mapping:
 * <cipher> [<key>|:<key_size>:<user|logon>:<key_description>] <iv_offset> <dev_path> <start>
 */
अटल पूर्णांक crypt_ctr(काष्ठा dm_target *ti, अचिन्हित पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा crypt_config *cc;
	स्थिर अक्षर *devname = dm_table_device_name(ti->table);
	पूर्णांक key_size;
	अचिन्हित पूर्णांक align_mask;
	अचिन्हित दीर्घ दीर्घ पंचांगpll;
	पूर्णांक ret;
	माप_प्रकार iv_size_padding, additional_req_size;
	अक्षर dummy;

	अगर (argc < 5) अणु
		ti->error = "Not enough arguments";
		वापस -EINVAL;
	पूर्ण

	key_size = get_key_size(&argv[1]);
	अगर (key_size < 0) अणु
		ti->error = "Cannot parse key size";
		वापस -EINVAL;
	पूर्ण

	cc = kzalloc(काष्ठा_size(cc, key, key_size), GFP_KERNEL);
	अगर (!cc) अणु
		ti->error = "Cannot allocate encryption context";
		वापस -ENOMEM;
	पूर्ण
	cc->key_size = key_size;
	cc->sector_size = (1 << SECTOR_SHIFT);
	cc->sector_shअगरt = 0;

	ti->निजी = cc;

	spin_lock(&dm_crypt_clients_lock);
	dm_crypt_clients_n++;
	crypt_calculate_pages_per_client();
	spin_unlock(&dm_crypt_clients_lock);

	ret = percpu_counter_init(&cc->n_allocated_pages, 0, GFP_KERNEL);
	अगर (ret < 0)
		जाओ bad;

	/* Optional parameters need to be पढ़ो beक्रमe cipher स्थिरructor */
	अगर (argc > 5) अणु
		ret = crypt_ctr_optional(ti, argc - 5, &argv[5]);
		अगर (ret)
			जाओ bad;
	पूर्ण

	ret = crypt_ctr_cipher(ti, argv[0], argv[1]);
	अगर (ret < 0)
		जाओ bad;

	अगर (crypt_पूर्णांकegrity_aead(cc)) अणु
		cc->dmreq_start = माप(काष्ठा aead_request);
		cc->dmreq_start += crypto_aead_reqsize(any_tfm_aead(cc));
		align_mask = crypto_aead_alignmask(any_tfm_aead(cc));
	पूर्ण अन्यथा अणु
		cc->dmreq_start = माप(काष्ठा skcipher_request);
		cc->dmreq_start += crypto_skcipher_reqsize(any_tfm(cc));
		align_mask = crypto_skcipher_alignmask(any_tfm(cc));
	पूर्ण
	cc->dmreq_start = ALIGN(cc->dmreq_start, __alignof__(काष्ठा dm_crypt_request));

	अगर (align_mask < CRYPTO_MINALIGN) अणु
		/* Allocate the padding exactly */
		iv_size_padding = -(cc->dmreq_start + माप(काष्ठा dm_crypt_request))
				& align_mask;
	पूर्ण अन्यथा अणु
		/*
		 * If the cipher requires greater alignment than kदो_स्मृति
		 * alignment, we करोn't know the exact position of the
		 * initialization vector. We must assume worst हाल.
		 */
		iv_size_padding = align_mask;
	पूर्ण

	/*  ...| IV + padding | original IV | original sec. number | bio tag offset | */
	additional_req_size = माप(काष्ठा dm_crypt_request) +
		iv_size_padding + cc->iv_size +
		cc->iv_size +
		माप(uपूर्णांक64_t) +
		माप(अचिन्हित पूर्णांक);

	ret = mempool_init_kदो_स्मृति_pool(&cc->req_pool, MIN_IOS, cc->dmreq_start + additional_req_size);
	अगर (ret) अणु
		ti->error = "Cannot allocate crypt request mempool";
		जाओ bad;
	पूर्ण

	cc->per_bio_data_size = ti->per_io_data_size =
		ALIGN(माप(काष्ठा dm_crypt_io) + cc->dmreq_start + additional_req_size,
		      ARCH_KMALLOC_MINALIGN);

	ret = mempool_init(&cc->page_pool, BIO_MAX_VECS, crypt_page_alloc, crypt_page_मुक्त, cc);
	अगर (ret) अणु
		ti->error = "Cannot allocate page mempool";
		जाओ bad;
	पूर्ण

	ret = bioset_init(&cc->bs, MIN_IOS, 0, BIOSET_NEED_BVECS);
	अगर (ret) अणु
		ti->error = "Cannot allocate crypt bioset";
		जाओ bad;
	पूर्ण

	mutex_init(&cc->bio_alloc_lock);

	ret = -EINVAL;
	अगर ((माला_पूछो(argv[2], "%llu%c", &पंचांगpll, &dummy) != 1) ||
	    (पंचांगpll & ((cc->sector_size >> SECTOR_SHIFT) - 1))) अणु
		ti->error = "Invalid iv_offset sector";
		जाओ bad;
	पूर्ण
	cc->iv_offset = पंचांगpll;

	ret = dm_get_device(ti, argv[3], dm_table_get_mode(ti->table), &cc->dev);
	अगर (ret) अणु
		ti->error = "Device lookup failed";
		जाओ bad;
	पूर्ण

	ret = -EINVAL;
	अगर (माला_पूछो(argv[4], "%llu%c", &पंचांगpll, &dummy) != 1 || पंचांगpll != (sector_t)पंचांगpll) अणु
		ti->error = "Invalid device sector";
		जाओ bad;
	पूर्ण
	cc->start = पंचांगpll;

	/*
	 * For zoned block devices, we need to preserve the issuer ग_लिखो
	 * ordering. To करो so, disable ग_लिखो workqueues and क्रमce अंतरभूत
	 * encryption completion.
	 */
	अगर (bdev_is_zoned(cc->dev->bdev)) अणु
		set_bit(DM_CRYPT_NO_WRITE_WORKQUEUE, &cc->flags);
		set_bit(DM_CRYPT_WRITE_INLINE, &cc->flags);
	पूर्ण

	अगर (crypt_पूर्णांकegrity_aead(cc) || cc->पूर्णांकegrity_iv_size) अणु
		ret = crypt_पूर्णांकegrity_ctr(cc, ti);
		अगर (ret)
			जाओ bad;

		cc->tag_pool_max_sectors = POOL_ENTRY_SIZE / cc->on_disk_tag_size;
		अगर (!cc->tag_pool_max_sectors)
			cc->tag_pool_max_sectors = 1;

		ret = mempool_init_kदो_स्मृति_pool(&cc->tag_pool, MIN_IOS,
			cc->tag_pool_max_sectors * cc->on_disk_tag_size);
		अगर (ret) अणु
			ti->error = "Cannot allocate integrity tags mempool";
			जाओ bad;
		पूर्ण

		cc->tag_pool_max_sectors <<= cc->sector_shअगरt;
	पूर्ण

	ret = -ENOMEM;
	cc->io_queue = alloc_workqueue("kcryptd_io/%s", WQ_MEM_RECLAIM, 1, devname);
	अगर (!cc->io_queue) अणु
		ti->error = "Couldn't create kcryptd io queue";
		जाओ bad;
	पूर्ण

	अगर (test_bit(DM_CRYPT_SAME_CPU, &cc->flags))
		cc->crypt_queue = alloc_workqueue("kcryptd/%s", WQ_CPU_INTENSIVE | WQ_MEM_RECLAIM,
						  1, devname);
	अन्यथा
		cc->crypt_queue = alloc_workqueue("kcryptd/%s",
						  WQ_CPU_INTENSIVE | WQ_MEM_RECLAIM | WQ_UNBOUND,
						  num_online_cpus(), devname);
	अगर (!cc->crypt_queue) अणु
		ti->error = "Couldn't create kcryptd queue";
		जाओ bad;
	पूर्ण

	spin_lock_init(&cc->ग_लिखो_thपढ़ो_lock);
	cc->ग_लिखो_tree = RB_ROOT;

	cc->ग_लिखो_thपढ़ो = kthपढ़ो_create(dmcrypt_ग_लिखो, cc, "dmcrypt_write/%s", devname);
	अगर (IS_ERR(cc->ग_लिखो_thपढ़ो)) अणु
		ret = PTR_ERR(cc->ग_लिखो_thपढ़ो);
		cc->ग_लिखो_thपढ़ो = शून्य;
		ti->error = "Couldn't spawn write thread";
		जाओ bad;
	पूर्ण
	wake_up_process(cc->ग_लिखो_thपढ़ो);

	ti->num_flush_bios = 1;
	ti->limit_swap_bios = true;

	वापस 0;

bad:
	crypt_dtr(ti);
	वापस ret;
पूर्ण

अटल पूर्णांक crypt_map(काष्ठा dm_target *ti, काष्ठा bio *bio)
अणु
	काष्ठा dm_crypt_io *io;
	काष्ठा crypt_config *cc = ti->निजी;

	/*
	 * If bio is REQ_PREFLUSH or REQ_OP_DISCARD, just bypass crypt queues.
	 * - क्रम REQ_PREFLUSH device-mapper core ensures that no IO is in-flight
	 * - क्रम REQ_OP_DISCARD caller must use flush अगर IO ordering matters
	 */
	अगर (unlikely(bio->bi_opf & REQ_PREFLUSH ||
	    bio_op(bio) == REQ_OP_DISCARD)) अणु
		bio_set_dev(bio, cc->dev->bdev);
		अगर (bio_sectors(bio))
			bio->bi_iter.bi_sector = cc->start +
				dm_target_offset(ti, bio->bi_iter.bi_sector);
		वापस DM_MAPIO_REMAPPED;
	पूर्ण

	/*
	 * Check अगर bio is too large, split as needed.
	 */
	अगर (unlikely(bio->bi_iter.bi_size > (BIO_MAX_VECS << PAGE_SHIFT)) &&
	    (bio_data_dir(bio) == WRITE || cc->on_disk_tag_size))
		dm_accept_partial_bio(bio, ((BIO_MAX_VECS << PAGE_SHIFT) >> SECTOR_SHIFT));

	/*
	 * Ensure that bio is a multiple of पूर्णांकernal sector encryption size
	 * and is aligned to this size as defined in IO hपूर्णांकs.
	 */
	अगर (unlikely((bio->bi_iter.bi_sector & ((cc->sector_size >> SECTOR_SHIFT) - 1)) != 0))
		वापस DM_MAPIO_KILL;

	अगर (unlikely(bio->bi_iter.bi_size & (cc->sector_size - 1)))
		वापस DM_MAPIO_KILL;

	io = dm_per_bio_data(bio, cc->per_bio_data_size);
	crypt_io_init(io, cc, bio, dm_target_offset(ti, bio->bi_iter.bi_sector));

	अगर (cc->on_disk_tag_size) अणु
		अचिन्हित tag_len = cc->on_disk_tag_size * (bio_sectors(bio) >> cc->sector_shअगरt);

		अगर (unlikely(tag_len > KMALLOC_MAX_SIZE) ||
		    unlikely(!(io->पूर्णांकegrity_metadata = kदो_स्मृति(tag_len,
				GFP_NOIO | __GFP_NORETRY | __GFP_NOMEMALLOC | __GFP_NOWARN)))) अणु
			अगर (bio_sectors(bio) > cc->tag_pool_max_sectors)
				dm_accept_partial_bio(bio, cc->tag_pool_max_sectors);
			io->पूर्णांकegrity_metadata = mempool_alloc(&cc->tag_pool, GFP_NOIO);
			io->पूर्णांकegrity_metadata_from_pool = true;
		पूर्ण
	पूर्ण

	अगर (crypt_पूर्णांकegrity_aead(cc))
		io->ctx.r.req_aead = (काष्ठा aead_request *)(io + 1);
	अन्यथा
		io->ctx.r.req = (काष्ठा skcipher_request *)(io + 1);

	अगर (bio_data_dir(io->base_bio) == READ) अणु
		अगर (kcryptd_io_पढ़ो(io, GFP_NOWAIT))
			kcryptd_queue_पढ़ो(io);
	पूर्ण अन्यथा
		kcryptd_queue_crypt(io);

	वापस DM_MAPIO_SUBMITTED;
पूर्ण

अटल व्योम crypt_status(काष्ठा dm_target *ti, status_type_t type,
			 अचिन्हित status_flags, अक्षर *result, अचिन्हित maxlen)
अणु
	काष्ठा crypt_config *cc = ti->निजी;
	अचिन्हित i, sz = 0;
	पूर्णांक num_feature_args = 0;

	चयन (type) अणु
	हाल STATUSTYPE_INFO:
		result[0] = '\0';
		अवरोध;

	हाल STATUSTYPE_TABLE:
		DMEMIT("%s ", cc->cipher_string);

		अगर (cc->key_size > 0) अणु
			अगर (cc->key_string)
				DMEMIT(":%u:%s", cc->key_size, cc->key_string);
			अन्यथा
				क्रम (i = 0; i < cc->key_size; i++)
					DMEMIT("%02x", cc->key[i]);
		पूर्ण अन्यथा
			DMEMIT("-");

		DMEMIT(" %llu %s %llu", (अचिन्हित दीर्घ दीर्घ)cc->iv_offset,
				cc->dev->name, (अचिन्हित दीर्घ दीर्घ)cc->start);

		num_feature_args += !!ti->num_discard_bios;
		num_feature_args += test_bit(DM_CRYPT_SAME_CPU, &cc->flags);
		num_feature_args += test_bit(DM_CRYPT_NO_OFFLOAD, &cc->flags);
		num_feature_args += test_bit(DM_CRYPT_NO_READ_WORKQUEUE, &cc->flags);
		num_feature_args += test_bit(DM_CRYPT_NO_WRITE_WORKQUEUE, &cc->flags);
		num_feature_args += cc->sector_size != (1 << SECTOR_SHIFT);
		num_feature_args += test_bit(CRYPT_IV_LARGE_SECTORS, &cc->cipher_flags);
		अगर (cc->on_disk_tag_size)
			num_feature_args++;
		अगर (num_feature_args) अणु
			DMEMIT(" %d", num_feature_args);
			अगर (ti->num_discard_bios)
				DMEMIT(" allow_discards");
			अगर (test_bit(DM_CRYPT_SAME_CPU, &cc->flags))
				DMEMIT(" same_cpu_crypt");
			अगर (test_bit(DM_CRYPT_NO_OFFLOAD, &cc->flags))
				DMEMIT(" submit_from_crypt_cpus");
			अगर (test_bit(DM_CRYPT_NO_READ_WORKQUEUE, &cc->flags))
				DMEMIT(" no_read_workqueue");
			अगर (test_bit(DM_CRYPT_NO_WRITE_WORKQUEUE, &cc->flags))
				DMEMIT(" no_write_workqueue");
			अगर (cc->on_disk_tag_size)
				DMEMIT(" integrity:%u:%s", cc->on_disk_tag_size, cc->cipher_auth);
			अगर (cc->sector_size != (1 << SECTOR_SHIFT))
				DMEMIT(" sector_size:%d", cc->sector_size);
			अगर (test_bit(CRYPT_IV_LARGE_SECTORS, &cc->cipher_flags))
				DMEMIT(" iv_large_sectors");
		पूर्ण

		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम crypt_postsuspend(काष्ठा dm_target *ti)
अणु
	काष्ठा crypt_config *cc = ti->निजी;

	set_bit(DM_CRYPT_SUSPENDED, &cc->flags);
पूर्ण

अटल पूर्णांक crypt_preresume(काष्ठा dm_target *ti)
अणु
	काष्ठा crypt_config *cc = ti->निजी;

	अगर (!test_bit(DM_CRYPT_KEY_VALID, &cc->flags)) अणु
		DMERR("aborting resume - crypt key is not set.");
		वापस -EAGAIN;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम crypt_resume(काष्ठा dm_target *ti)
अणु
	काष्ठा crypt_config *cc = ti->निजी;

	clear_bit(DM_CRYPT_SUSPENDED, &cc->flags);
पूर्ण

/* Message पूर्णांकerface
 *	key set <key>
 *	key wipe
 */
अटल पूर्णांक crypt_message(काष्ठा dm_target *ti, अचिन्हित argc, अक्षर **argv,
			 अक्षर *result, अचिन्हित maxlen)
अणु
	काष्ठा crypt_config *cc = ti->निजी;
	पूर्णांक key_size, ret = -EINVAL;

	अगर (argc < 2)
		जाओ error;

	अगर (!strहालcmp(argv[0], "key")) अणु
		अगर (!test_bit(DM_CRYPT_SUSPENDED, &cc->flags)) अणु
			DMWARN("not suspended during key manipulation.");
			वापस -EINVAL;
		पूर्ण
		अगर (argc == 3 && !strहालcmp(argv[1], "set")) अणु
			/* The key size may not be changed. */
			key_size = get_key_size(&argv[2]);
			अगर (key_size < 0 || cc->key_size != key_size) अणु
				स_रखो(argv[2], '0', म_माप(argv[2]));
				वापस -EINVAL;
			पूर्ण

			ret = crypt_set_key(cc, argv[2]);
			अगर (ret)
				वापस ret;
			अगर (cc->iv_gen_ops && cc->iv_gen_ops->init)
				ret = cc->iv_gen_ops->init(cc);
			/* wipe the kernel key payload copy */
			अगर (cc->key_string)
				स_रखो(cc->key, 0, cc->key_size * माप(u8));
			वापस ret;
		पूर्ण
		अगर (argc == 2 && !strहालcmp(argv[1], "wipe"))
			वापस crypt_wipe_key(cc);
	पूर्ण

error:
	DMWARN("unrecognised message received.");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक crypt_iterate_devices(काष्ठा dm_target *ti,
				 iterate_devices_callout_fn fn, व्योम *data)
अणु
	काष्ठा crypt_config *cc = ti->निजी;

	वापस fn(ti, cc->dev, cc->start, ti->len, data);
पूर्ण

अटल व्योम crypt_io_hपूर्णांकs(काष्ठा dm_target *ti, काष्ठा queue_limits *limits)
अणु
	काष्ठा crypt_config *cc = ti->निजी;

	/*
	 * Unक्रमtunate स्थिरraपूर्णांक that is required to aव्योम the potential
	 * क्रम exceeding underlying device's max_segments limits -- due to
	 * crypt_alloc_buffer() possibly allocating pages क्रम the encryption
	 * bio that are not as physically contiguous as the original bio.
	 */
	limits->max_segment_size = PAGE_SIZE;

	limits->logical_block_size =
		max_t(अचिन्हित, limits->logical_block_size, cc->sector_size);
	limits->physical_block_size =
		max_t(अचिन्हित, limits->physical_block_size, cc->sector_size);
	limits->io_min = max_t(अचिन्हित, limits->io_min, cc->sector_size);
पूर्ण

अटल काष्ठा target_type crypt_target = अणु
	.name   = "crypt",
	.version = अणु1, 23, 0पूर्ण,
	.module = THIS_MODULE,
	.ctr    = crypt_ctr,
	.dtr    = crypt_dtr,
	.features = DM_TARGET_ZONED_HM,
	.report_zones = crypt_report_zones,
	.map    = crypt_map,
	.status = crypt_status,
	.postsuspend = crypt_postsuspend,
	.preresume = crypt_preresume,
	.resume = crypt_resume,
	.message = crypt_message,
	.iterate_devices = crypt_iterate_devices,
	.io_hपूर्णांकs = crypt_io_hपूर्णांकs,
पूर्ण;

अटल पूर्णांक __init dm_crypt_init(व्योम)
अणु
	पूर्णांक r;

	r = dm_रेजिस्टर_target(&crypt_target);
	अगर (r < 0)
		DMERR("register failed %d", r);

	वापस r;
पूर्ण

अटल व्योम __निकास dm_crypt_निकास(व्योम)
अणु
	dm_unरेजिस्टर_target(&crypt_target);
पूर्ण

module_init(dm_crypt_init);
module_निकास(dm_crypt_निकास);

MODULE_AUTHOR("Jana Saout <jana@saout.de>");
MODULE_DESCRIPTION(DM_NAME " target for transparent encryption / decryption");
MODULE_LICENSE("GPL");
