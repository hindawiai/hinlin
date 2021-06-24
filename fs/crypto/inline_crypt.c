<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Inline encryption support क्रम fscrypt
 *
 * Copyright 2019 Google LLC
 */

/*
 * With "inline encryption", the block layer handles the decryption/encryption
 * as part of the bio, instead of the fileप्रणाली करोing the crypto itself via
 * crypto API.  See Documentation/block/अंतरभूत-encryption.rst.  fscrypt still
 * provides the key and IV to use.
 */

#समावेश <linux/blk-crypto.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/slab.h>

#समावेश "fscrypt_private.h"

काष्ठा fscrypt_blk_crypto_key अणु
	काष्ठा blk_crypto_key base;
	पूर्णांक num_devs;
	काष्ठा request_queue *devs[];
पूर्ण;

अटल पूर्णांक fscrypt_get_num_devices(काष्ठा super_block *sb)
अणु
	अगर (sb->s_cop->get_num_devices)
		वापस sb->s_cop->get_num_devices(sb);
	वापस 1;
पूर्ण

अटल व्योम fscrypt_get_devices(काष्ठा super_block *sb, पूर्णांक num_devs,
				काष्ठा request_queue **devs)
अणु
	अगर (num_devs == 1)
		devs[0] = bdev_get_queue(sb->s_bdev);
	अन्यथा
		sb->s_cop->get_devices(sb, devs);
पूर्ण

अटल अचिन्हित पूर्णांक fscrypt_get_dun_bytes(स्थिर काष्ठा fscrypt_info *ci)
अणु
	काष्ठा super_block *sb = ci->ci_inode->i_sb;
	अचिन्हित पूर्णांक flags = fscrypt_policy_flags(&ci->ci_policy);
	पूर्णांक ino_bits = 64, lblk_bits = 64;

	अगर (flags & FSCRYPT_POLICY_FLAG_सूचीECT_KEY)
		वापस दुरत्वend(जोड़ fscrypt_iv, nonce);

	अगर (flags & FSCRYPT_POLICY_FLAG_IV_INO_LBLK_64)
		वापस माप(__le64);

	अगर (flags & FSCRYPT_POLICY_FLAG_IV_INO_LBLK_32)
		वापस माप(__le32);

	/* Default हाल: IVs are just the file logical block number */
	अगर (sb->s_cop->get_ino_and_lblk_bits)
		sb->s_cop->get_ino_and_lblk_bits(sb, &ino_bits, &lblk_bits);
	वापस DIV_ROUND_UP(lblk_bits, 8);
पूर्ण

/* Enable अंतरभूत encryption क्रम this file अगर supported. */
पूर्णांक fscrypt_select_encryption_impl(काष्ठा fscrypt_info *ci)
अणु
	स्थिर काष्ठा inode *inode = ci->ci_inode;
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा blk_crypto_config crypto_cfg;
	पूर्णांक num_devs;
	काष्ठा request_queue **devs;
	पूर्णांक i;

	/* The file must need contents encryption, not filenames encryption */
	अगर (!S_ISREG(inode->i_mode))
		वापस 0;

	/* The crypto mode must have a blk-crypto counterpart */
	अगर (ci->ci_mode->blk_crypto_mode == BLK_ENCRYPTION_MODE_INVALID)
		वापस 0;

	/* The fileप्रणाली must be mounted with -o अंतरभूतcrypt */
	अगर (!(sb->s_flags & SB_INLINECRYPT))
		वापस 0;

	/*
	 * When a page contains multiple logically contiguous fileप्रणाली blocks,
	 * some fileप्रणाली code only calls fscrypt_mergeable_bio() क्रम the first
	 * block in the page. This is fine क्रम most of fscrypt's IV generation
	 * strategies, where contiguous blocks imply contiguous IVs. But it
	 * करोesn't work with IV_INO_LBLK_32. For now, simply exclude
	 * IV_INO_LBLK_32 with blocksize != PAGE_SIZE from अंतरभूत encryption.
	 */
	अगर ((fscrypt_policy_flags(&ci->ci_policy) &
	     FSCRYPT_POLICY_FLAG_IV_INO_LBLK_32) &&
	    sb->s_blocksize != PAGE_SIZE)
		वापस 0;

	/*
	 * On all the fileप्रणाली's devices, blk-crypto must support the crypto
	 * configuration that the file would use.
	 */
	crypto_cfg.crypto_mode = ci->ci_mode->blk_crypto_mode;
	crypto_cfg.data_unit_size = sb->s_blocksize;
	crypto_cfg.dun_bytes = fscrypt_get_dun_bytes(ci);
	num_devs = fscrypt_get_num_devices(sb);
	devs = kदो_स्मृति_array(num_devs, माप(*devs), GFP_KERNEL);
	अगर (!devs)
		वापस -ENOMEM;
	fscrypt_get_devices(sb, num_devs, devs);

	क्रम (i = 0; i < num_devs; i++) अणु
		अगर (!blk_crypto_config_supported(devs[i], &crypto_cfg))
			जाओ out_मुक्त_devs;
	पूर्ण

	ci->ci_अंतरभूतcrypt = true;
out_मुक्त_devs:
	kमुक्त(devs);

	वापस 0;
पूर्ण

पूर्णांक fscrypt_prepare_अंतरभूत_crypt_key(काष्ठा fscrypt_prepared_key *prep_key,
				     स्थिर u8 *raw_key,
				     स्थिर काष्ठा fscrypt_info *ci)
अणु
	स्थिर काष्ठा inode *inode = ci->ci_inode;
	काष्ठा super_block *sb = inode->i_sb;
	क्रमागत blk_crypto_mode_num crypto_mode = ci->ci_mode->blk_crypto_mode;
	पूर्णांक num_devs = fscrypt_get_num_devices(sb);
	पूर्णांक queue_refs = 0;
	काष्ठा fscrypt_blk_crypto_key *blk_key;
	पूर्णांक err;
	पूर्णांक i;

	blk_key = kzalloc(काष्ठा_size(blk_key, devs, num_devs), GFP_KERNEL);
	अगर (!blk_key)
		वापस -ENOMEM;

	blk_key->num_devs = num_devs;
	fscrypt_get_devices(sb, num_devs, blk_key->devs);

	err = blk_crypto_init_key(&blk_key->base, raw_key, crypto_mode,
				  fscrypt_get_dun_bytes(ci), sb->s_blocksize);
	अगर (err) अणु
		fscrypt_err(inode, "error %d initializing blk-crypto key", err);
		जाओ fail;
	पूर्ण

	/*
	 * We have to start using blk-crypto on all the fileप्रणाली's devices.
	 * We also have to save all the request_queue's क्रम later so that the
	 * key can be evicted from them.  This is needed because some keys
	 * aren't destroyed until after the fileप्रणाली was alपढ़ोy unmounted
	 * (namely, the per-mode keys in काष्ठा fscrypt_master_key).
	 */
	क्रम (i = 0; i < num_devs; i++) अणु
		अगर (!blk_get_queue(blk_key->devs[i])) अणु
			fscrypt_err(inode, "couldn't get request_queue");
			err = -EAGAIN;
			जाओ fail;
		पूर्ण
		queue_refs++;

		err = blk_crypto_start_using_key(&blk_key->base,
						 blk_key->devs[i]);
		अगर (err) अणु
			fscrypt_err(inode,
				    "error %d starting to use blk-crypto", err);
			जाओ fail;
		पूर्ण
	पूर्ण
	/*
	 * Pairs with the smp_load_acquire() in fscrypt_is_key_prepared().
	 * I.e., here we publish ->blk_key with a RELEASE barrier so that
	 * concurrent tasks can ACQUIRE it.  Note that this concurrency is only
	 * possible क्रम per-mode keys, not क्रम per-file keys.
	 */
	smp_store_release(&prep_key->blk_key, blk_key);
	वापस 0;

fail:
	क्रम (i = 0; i < queue_refs; i++)
		blk_put_queue(blk_key->devs[i]);
	kमुक्त_sensitive(blk_key);
	वापस err;
पूर्ण

व्योम fscrypt_destroy_अंतरभूत_crypt_key(काष्ठा fscrypt_prepared_key *prep_key)
अणु
	काष्ठा fscrypt_blk_crypto_key *blk_key = prep_key->blk_key;
	पूर्णांक i;

	अगर (blk_key) अणु
		क्रम (i = 0; i < blk_key->num_devs; i++) अणु
			blk_crypto_evict_key(blk_key->devs[i], &blk_key->base);
			blk_put_queue(blk_key->devs[i]);
		पूर्ण
		kमुक्त_sensitive(blk_key);
	पूर्ण
पूर्ण

bool __fscrypt_inode_uses_अंतरभूत_crypto(स्थिर काष्ठा inode *inode)
अणु
	वापस inode->i_crypt_info->ci_अंतरभूतcrypt;
पूर्ण
EXPORT_SYMBOL_GPL(__fscrypt_inode_uses_अंतरभूत_crypto);

अटल व्योम fscrypt_generate_dun(स्थिर काष्ठा fscrypt_info *ci, u64 lblk_num,
				 u64 dun[BLK_CRYPTO_DUN_ARRAY_SIZE])
अणु
	जोड़ fscrypt_iv iv;
	पूर्णांक i;

	fscrypt_generate_iv(&iv, lblk_num, ci);

	BUILD_BUG_ON(FSCRYPT_MAX_IV_SIZE > BLK_CRYPTO_MAX_IV_SIZE);
	स_रखो(dun, 0, BLK_CRYPTO_MAX_IV_SIZE);
	क्रम (i = 0; i < ci->ci_mode->ivsize/माप(dun[0]); i++)
		dun[i] = le64_to_cpu(iv.dun[i]);
पूर्ण

/**
 * fscrypt_set_bio_crypt_ctx() - prepare a file contents bio क्रम अंतरभूत crypto
 * @bio: a bio which will eventually be submitted to the file
 * @inode: the file's inode
 * @first_lblk: the first file logical block number in the I/O
 * @gfp_mask: memory allocation flags - these must be a रुकोing mask so that
 *					bio_crypt_set_ctx can't fail.
 *
 * If the contents of the file should be encrypted (or decrypted) with अंतरभूत
 * encryption, then assign the appropriate encryption context to the bio.
 *
 * Normally the bio should be newly allocated (i.e. no pages added yet), as
 * otherwise fscrypt_mergeable_bio() won't work as पूर्णांकended.
 *
 * The encryption context will be मुक्तd स्वतःmatically when the bio is मुक्तd.
 */
व्योम fscrypt_set_bio_crypt_ctx(काष्ठा bio *bio, स्थिर काष्ठा inode *inode,
			       u64 first_lblk, gfp_t gfp_mask)
अणु
	स्थिर काष्ठा fscrypt_info *ci;
	u64 dun[BLK_CRYPTO_DUN_ARRAY_SIZE];

	अगर (!fscrypt_inode_uses_अंतरभूत_crypto(inode))
		वापस;
	ci = inode->i_crypt_info;

	fscrypt_generate_dun(ci, first_lblk, dun);
	bio_crypt_set_ctx(bio, &ci->ci_enc_key.blk_key->base, dun, gfp_mask);
पूर्ण
EXPORT_SYMBOL_GPL(fscrypt_set_bio_crypt_ctx);

/* Extract the inode and logical block number from a buffer_head. */
अटल bool bh_get_inode_and_lblk_num(स्थिर काष्ठा buffer_head *bh,
				      स्थिर काष्ठा inode **inode_ret,
				      u64 *lblk_num_ret)
अणु
	काष्ठा page *page = bh->b_page;
	स्थिर काष्ठा address_space *mapping;
	स्थिर काष्ठा inode *inode;

	/*
	 * The ext4 journal (jbd2) can submit a buffer_head it directly created
	 * क्रम a non-pagecache page.  fscrypt करोesn't care about these.
	 */
	mapping = page_mapping(page);
	अगर (!mapping)
		वापस false;
	inode = mapping->host;

	*inode_ret = inode;
	*lblk_num_ret = ((u64)page->index << (PAGE_SHIFT - inode->i_blkbits)) +
			(bh_offset(bh) >> inode->i_blkbits);
	वापस true;
पूर्ण

/**
 * fscrypt_set_bio_crypt_ctx_bh() - prepare a file contents bio क्रम अंतरभूत
 *				    crypto
 * @bio: a bio which will eventually be submitted to the file
 * @first_bh: the first buffer_head क्रम which I/O will be submitted
 * @gfp_mask: memory allocation flags
 *
 * Same as fscrypt_set_bio_crypt_ctx(), except this takes a buffer_head instead
 * of an inode and block number directly.
 */
व्योम fscrypt_set_bio_crypt_ctx_bh(काष्ठा bio *bio,
				  स्थिर काष्ठा buffer_head *first_bh,
				  gfp_t gfp_mask)
अणु
	स्थिर काष्ठा inode *inode;
	u64 first_lblk;

	अगर (bh_get_inode_and_lblk_num(first_bh, &inode, &first_lblk))
		fscrypt_set_bio_crypt_ctx(bio, inode, first_lblk, gfp_mask);
पूर्ण
EXPORT_SYMBOL_GPL(fscrypt_set_bio_crypt_ctx_bh);

/**
 * fscrypt_mergeable_bio() - test whether data can be added to a bio
 * @bio: the bio being built up
 * @inode: the inode क्रम the next part of the I/O
 * @next_lblk: the next file logical block number in the I/O
 *
 * When building a bio which may contain data which should undergo अंतरभूत
 * encryption (or decryption) via fscrypt, fileप्रणालीs should call this function
 * to ensure that the resulting bio contains only contiguous data unit numbers.
 * This will वापस false अगर the next part of the I/O cannot be merged with the
 * bio because either the encryption key would be dअगरferent or the encryption
 * data unit numbers would be discontiguous.
 *
 * fscrypt_set_bio_crypt_ctx() must have alपढ़ोy been called on the bio.
 *
 * Return: true अगरf the I/O is mergeable
 */
bool fscrypt_mergeable_bio(काष्ठा bio *bio, स्थिर काष्ठा inode *inode,
			   u64 next_lblk)
अणु
	स्थिर काष्ठा bio_crypt_ctx *bc = bio->bi_crypt_context;
	u64 next_dun[BLK_CRYPTO_DUN_ARRAY_SIZE];

	अगर (!!bc != fscrypt_inode_uses_अंतरभूत_crypto(inode))
		वापस false;
	अगर (!bc)
		वापस true;

	/*
	 * Comparing the key poपूर्णांकers is good enough, as all I/O क्रम each key
	 * uses the same poपूर्णांकer.  I.e., there's currently no need to support
	 * merging requests where the keys are the same but the poपूर्णांकers dअगरfer.
	 */
	अगर (bc->bc_key != &inode->i_crypt_info->ci_enc_key.blk_key->base)
		वापस false;

	fscrypt_generate_dun(inode->i_crypt_info, next_lblk, next_dun);
	वापस bio_crypt_dun_is_contiguous(bc, bio->bi_iter.bi_size, next_dun);
पूर्ण
EXPORT_SYMBOL_GPL(fscrypt_mergeable_bio);

/**
 * fscrypt_mergeable_bio_bh() - test whether data can be added to a bio
 * @bio: the bio being built up
 * @next_bh: the next buffer_head क्रम which I/O will be submitted
 *
 * Same as fscrypt_mergeable_bio(), except this takes a buffer_head instead of
 * an inode and block number directly.
 *
 * Return: true अगरf the I/O is mergeable
 */
bool fscrypt_mergeable_bio_bh(काष्ठा bio *bio,
			      स्थिर काष्ठा buffer_head *next_bh)
अणु
	स्थिर काष्ठा inode *inode;
	u64 next_lblk;

	अगर (!bh_get_inode_and_lblk_num(next_bh, &inode, &next_lblk))
		वापस !bio->bi_crypt_context;

	वापस fscrypt_mergeable_bio(bio, inode, next_lblk);
पूर्ण
EXPORT_SYMBOL_GPL(fscrypt_mergeable_bio_bh);
