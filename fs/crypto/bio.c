<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This contains encryption functions क्रम per-file encryption.
 *
 * Copyright (C) 2015, Google, Inc.
 * Copyright (C) 2015, Motorola Mobility
 *
 * Written by Michael Halcrow, 2014.
 *
 * Filename encryption additions
 *	Uday Savagaonkar, 2014
 * Encryption policy handling additions
 *	Ildar Muslukhov, 2014
 * Add fscrypt_pullback_bio_page()
 *	Jaegeuk Kim, 2015.
 *
 * This has not yet undergone a rigorous security audit.
 *
 * The usage of AES-XTS should conक्रमm to recommendations in NIST
 * Special Publication 800-38E and IEEE P1619/D16.
 */

#समावेश <linux/pagemap.h>
#समावेश <linux/module.h>
#समावेश <linux/bपन.स>
#समावेश <linux/namei.h>
#समावेश "fscrypt_private.h"

व्योम fscrypt_decrypt_bio(काष्ठा bio *bio)
अणु
	काष्ठा bio_vec *bv;
	काष्ठा bvec_iter_all iter_all;

	bio_क्रम_each_segment_all(bv, bio, iter_all) अणु
		काष्ठा page *page = bv->bv_page;
		पूर्णांक ret = fscrypt_decrypt_pagecache_blocks(page, bv->bv_len,
							   bv->bv_offset);
		अगर (ret)
			SetPageError(page);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(fscrypt_decrypt_bio);

अटल पूर्णांक fscrypt_zeroout_range_अंतरभूत_crypt(स्थिर काष्ठा inode *inode,
					      pgoff_t lblk, sector_t pblk,
					      अचिन्हित पूर्णांक len)
अणु
	स्थिर अचिन्हित पूर्णांक blockbits = inode->i_blkbits;
	स्थिर अचिन्हित पूर्णांक blocks_per_page = 1 << (PAGE_SHIFT - blockbits);
	काष्ठा bio *bio;
	पूर्णांक ret, err = 0;
	पूर्णांक num_pages = 0;

	/* This always succeeds since __GFP_सूचीECT_RECLAIM is set. */
	bio = bio_alloc(GFP_NOFS, BIO_MAX_VECS);

	जबतक (len) अणु
		अचिन्हित पूर्णांक blocks_this_page = min(len, blocks_per_page);
		अचिन्हित पूर्णांक bytes_this_page = blocks_this_page << blockbits;

		अगर (num_pages == 0) अणु
			fscrypt_set_bio_crypt_ctx(bio, inode, lblk, GFP_NOFS);
			bio_set_dev(bio, inode->i_sb->s_bdev);
			bio->bi_iter.bi_sector =
					pblk << (blockbits - SECTOR_SHIFT);
			bio_set_op_attrs(bio, REQ_OP_WRITE, 0);
		पूर्ण
		ret = bio_add_page(bio, ZERO_PAGE(0), bytes_this_page, 0);
		अगर (WARN_ON(ret != bytes_this_page)) अणु
			err = -EIO;
			जाओ out;
		पूर्ण
		num_pages++;
		len -= blocks_this_page;
		lblk += blocks_this_page;
		pblk += blocks_this_page;
		अगर (num_pages == BIO_MAX_VECS || !len ||
		    !fscrypt_mergeable_bio(bio, inode, lblk)) अणु
			err = submit_bio_रुको(bio);
			अगर (err)
				जाओ out;
			bio_reset(bio);
			num_pages = 0;
		पूर्ण
	पूर्ण
out:
	bio_put(bio);
	वापस err;
पूर्ण

/**
 * fscrypt_zeroout_range() - zero out a range of blocks in an encrypted file
 * @inode: the file's inode
 * @lblk: the first file logical block to zero out
 * @pblk: the first fileप्रणाली physical block to zero out
 * @len: number of blocks to zero out
 *
 * Zero out fileप्रणाली blocks in an encrypted regular file on-disk, i.e. ग_लिखो
 * ciphertext blocks which decrypt to the all-zeroes block.  The blocks must be
 * both logically and physically contiguous.  It's also assumed that the
 * fileप्रणाली only uses a single block device, ->s_bdev.
 *
 * Note that since each block uses a dअगरferent IV, this involves writing a
 * dअगरferent ciphertext to each block; we can't simply reuse the same one.
 *
 * Return: 0 on success; -त्रुटि_सं on failure.
 */
पूर्णांक fscrypt_zeroout_range(स्थिर काष्ठा inode *inode, pgoff_t lblk,
			  sector_t pblk, अचिन्हित पूर्णांक len)
अणु
	स्थिर अचिन्हित पूर्णांक blockbits = inode->i_blkbits;
	स्थिर अचिन्हित पूर्णांक blocksize = 1 << blockbits;
	स्थिर अचिन्हित पूर्णांक blocks_per_page_bits = PAGE_SHIFT - blockbits;
	स्थिर अचिन्हित पूर्णांक blocks_per_page = 1 << blocks_per_page_bits;
	काष्ठा page *pages[16]; /* ग_लिखो up to 16 pages at a समय */
	अचिन्हित पूर्णांक nr_pages;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक offset;
	काष्ठा bio *bio;
	पूर्णांक ret, err;

	अगर (len == 0)
		वापस 0;

	अगर (fscrypt_inode_uses_अंतरभूत_crypto(inode))
		वापस fscrypt_zeroout_range_अंतरभूत_crypt(inode, lblk, pblk,
							  len);

	BUILD_BUG_ON(ARRAY_SIZE(pages) > BIO_MAX_VECS);
	nr_pages = min_t(अचिन्हित पूर्णांक, ARRAY_SIZE(pages),
			 (len + blocks_per_page - 1) >> blocks_per_page_bits);

	/*
	 * We need at least one page क्रम ciphertext.  Allocate the first one
	 * from a mempool, with __GFP_सूचीECT_RECLAIM set so that it can't fail.
	 *
	 * Any additional page allocations are allowed to fail, as they only
	 * help perक्रमmance, and रुकोing on the mempool क्रम them could deadlock.
	 */
	क्रम (i = 0; i < nr_pages; i++) अणु
		pages[i] = fscrypt_alloc_bounce_page(i == 0 ? GFP_NOFS :
						     GFP_NOWAIT | __GFP_NOWARN);
		अगर (!pages[i])
			अवरोध;
	पूर्ण
	nr_pages = i;
	अगर (WARN_ON(nr_pages <= 0))
		वापस -EINVAL;

	/* This always succeeds since __GFP_सूचीECT_RECLAIM is set. */
	bio = bio_alloc(GFP_NOFS, nr_pages);

	करो अणु
		bio_set_dev(bio, inode->i_sb->s_bdev);
		bio->bi_iter.bi_sector = pblk << (blockbits - 9);
		bio_set_op_attrs(bio, REQ_OP_WRITE, 0);

		i = 0;
		offset = 0;
		करो अणु
			err = fscrypt_crypt_block(inode, FS_ENCRYPT, lblk,
						  ZERO_PAGE(0), pages[i],
						  blocksize, offset, GFP_NOFS);
			अगर (err)
				जाओ out;
			lblk++;
			pblk++;
			len--;
			offset += blocksize;
			अगर (offset == PAGE_SIZE || len == 0) अणु
				ret = bio_add_page(bio, pages[i++], offset, 0);
				अगर (WARN_ON(ret != offset)) अणु
					err = -EIO;
					जाओ out;
				पूर्ण
				offset = 0;
			पूर्ण
		पूर्ण जबतक (i != nr_pages && len != 0);

		err = submit_bio_रुको(bio);
		अगर (err)
			जाओ out;
		bio_reset(bio);
	पूर्ण जबतक (len != 0);
	err = 0;
out:
	bio_put(bio);
	क्रम (i = 0; i < nr_pages; i++)
		fscrypt_मुक्त_bounce_page(pages[i]);
	वापस err;
पूर्ण
EXPORT_SYMBOL(fscrypt_zeroout_range);
