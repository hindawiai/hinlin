<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Red Hat, Inc.
 * Copyright (C) 2015 Google, Inc.
 *
 * Author: Mikulas Patocka <mpatocka@redhat.com>
 *
 * Based on Chromium dm-verity driver (C) 2011 The Chromium OS Authors
 */

#अगर_अघोषित DM_VERITY_H
#घोषणा DM_VERITY_H

#समावेश <linux/dm-bufपन.स>
#समावेश <linux/device-mapper.h>
#समावेश <crypto/hash.h>

#घोषणा DM_VERITY_MAX_LEVELS		63

क्रमागत verity_mode अणु
	DM_VERITY_MODE_EIO,
	DM_VERITY_MODE_LOGGING,
	DM_VERITY_MODE_RESTART,
	DM_VERITY_MODE_PANIC
पूर्ण;

क्रमागत verity_block_type अणु
	DM_VERITY_BLOCK_TYPE_DATA,
	DM_VERITY_BLOCK_TYPE_METADATA
पूर्ण;

काष्ठा dm_verity_fec;

काष्ठा dm_verity अणु
	काष्ठा dm_dev *data_dev;
	काष्ठा dm_dev *hash_dev;
	काष्ठा dm_target *ti;
	काष्ठा dm_bufio_client *bufio;
	अक्षर *alg_name;
	काष्ठा crypto_ahash *tfm;
	u8 *root_digest;	/* digest of the root block */
	u8 *salt;		/* salt: its size is salt_size */
	u8 *zero_digest;	/* digest क्रम a zero block */
	अचिन्हित salt_size;
	sector_t data_start;	/* data offset in 512-byte sectors */
	sector_t hash_start;	/* hash start in blocks */
	sector_t data_blocks;	/* the number of data blocks */
	sector_t hash_blocks;	/* the number of hash blocks */
	अचिन्हित अक्षर data_dev_block_bits;	/* log2(data blocksize) */
	अचिन्हित अक्षर hash_dev_block_bits;	/* log2(hash blocksize) */
	अचिन्हित अक्षर hash_per_block_bits;	/* log2(hashes in hash block) */
	अचिन्हित अक्षर levels;	/* the number of tree levels */
	अचिन्हित अक्षर version;
	अचिन्हित digest_size;	/* digest size क्रम the current hash algorithm */
	अचिन्हित पूर्णांक ahash_reqsize;/* the size of temporary space क्रम crypto */
	पूर्णांक hash_failed;	/* set to 1 अगर hash of any block failed */
	क्रमागत verity_mode mode;	/* mode क्रम handling verअगरication errors */
	अचिन्हित corrupted_errs;/* Number of errors क्रम corrupted blocks */

	काष्ठा workqueue_काष्ठा *verअगरy_wq;

	/* starting blocks क्रम each tree level. 0 is the lowest level. */
	sector_t hash_level_block[DM_VERITY_MAX_LEVELS];

	काष्ठा dm_verity_fec *fec;	/* क्रमward error correction */
	अचिन्हित दीर्घ *validated_blocks; /* bitset blocks validated */

	अक्षर *signature_key_desc; /* signature keyring reference */
पूर्ण;

काष्ठा dm_verity_io अणु
	काष्ठा dm_verity *v;

	/* original value of bio->bi_end_io */
	bio_end_io_t *orig_bi_end_io;

	sector_t block;
	अचिन्हित n_blocks;

	काष्ठा bvec_iter iter;

	काष्ठा work_काष्ठा work;

	/*
	 * Three variably-size fields follow this काष्ठा:
	 *
	 * u8 hash_req[v->ahash_reqsize];
	 * u8 real_digest[v->digest_size];
	 * u8 want_digest[v->digest_size];
	 *
	 * To access them use: verity_io_hash_req(), verity_io_real_digest()
	 * and verity_io_want_digest().
	 */
पूर्ण;

अटल अंतरभूत काष्ठा ahash_request *verity_io_hash_req(काष्ठा dm_verity *v,
						     काष्ठा dm_verity_io *io)
अणु
	वापस (काष्ठा ahash_request *)(io + 1);
पूर्ण

अटल अंतरभूत u8 *verity_io_real_digest(काष्ठा dm_verity *v,
					काष्ठा dm_verity_io *io)
अणु
	वापस (u8 *)(io + 1) + v->ahash_reqsize;
पूर्ण

अटल अंतरभूत u8 *verity_io_want_digest(काष्ठा dm_verity *v,
					काष्ठा dm_verity_io *io)
अणु
	वापस (u8 *)(io + 1) + v->ahash_reqsize + v->digest_size;
पूर्ण

अटल अंतरभूत u8 *verity_io_digest_end(काष्ठा dm_verity *v,
				       काष्ठा dm_verity_io *io)
अणु
	वापस verity_io_want_digest(v, io) + v->digest_size;
पूर्ण

बाह्य पूर्णांक verity_क्रम_bv_block(काष्ठा dm_verity *v, काष्ठा dm_verity_io *io,
			       काष्ठा bvec_iter *iter,
			       पूर्णांक (*process)(काष्ठा dm_verity *v,
					      काष्ठा dm_verity_io *io,
					      u8 *data, माप_प्रकार len));

बाह्य पूर्णांक verity_hash(काष्ठा dm_verity *v, काष्ठा ahash_request *req,
		       स्थिर u8 *data, माप_प्रकार len, u8 *digest);

बाह्य पूर्णांक verity_hash_क्रम_block(काष्ठा dm_verity *v, काष्ठा dm_verity_io *io,
				 sector_t block, u8 *digest, bool *is_zero);

#पूर्ण_अगर /* DM_VERITY_H */
