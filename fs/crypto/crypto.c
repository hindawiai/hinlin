<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
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
#समावेश <linux/mempool.h>
#समावेश <linux/module.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/ratelimit.h>
#समावेश <crypto/skcipher.h>
#समावेश "fscrypt_private.h"

अटल अचिन्हित पूर्णांक num_pपुनः_स्मृति_crypto_pages = 32;

module_param(num_pपुनः_स्मृति_crypto_pages, uपूर्णांक, 0444);
MODULE_PARM_DESC(num_pपुनः_स्मृति_crypto_pages,
		"Number of crypto pages to preallocate");

अटल mempool_t *fscrypt_bounce_page_pool = शून्य;

अटल काष्ठा workqueue_काष्ठा *fscrypt_पढ़ो_workqueue;
अटल DEFINE_MUTEX(fscrypt_init_mutex);

काष्ठा kmem_cache *fscrypt_info_cachep;

व्योम fscrypt_enqueue_decrypt_work(काष्ठा work_काष्ठा *work)
अणु
	queue_work(fscrypt_पढ़ो_workqueue, work);
पूर्ण
EXPORT_SYMBOL(fscrypt_enqueue_decrypt_work);

काष्ठा page *fscrypt_alloc_bounce_page(gfp_t gfp_flags)
अणु
	वापस mempool_alloc(fscrypt_bounce_page_pool, gfp_flags);
पूर्ण

/**
 * fscrypt_मुक्त_bounce_page() - मुक्त a ciphertext bounce page
 * @bounce_page: the bounce page to मुक्त, or शून्य
 *
 * Free a bounce page that was allocated by fscrypt_encrypt_pagecache_blocks(),
 * or by fscrypt_alloc_bounce_page() directly.
 */
व्योम fscrypt_मुक्त_bounce_page(काष्ठा page *bounce_page)
अणु
	अगर (!bounce_page)
		वापस;
	set_page_निजी(bounce_page, (अचिन्हित दीर्घ)शून्य);
	ClearPagePrivate(bounce_page);
	mempool_मुक्त(bounce_page, fscrypt_bounce_page_pool);
पूर्ण
EXPORT_SYMBOL(fscrypt_मुक्त_bounce_page);

व्योम fscrypt_generate_iv(जोड़ fscrypt_iv *iv, u64 lblk_num,
			 स्थिर काष्ठा fscrypt_info *ci)
अणु
	u8 flags = fscrypt_policy_flags(&ci->ci_policy);

	स_रखो(iv, 0, ci->ci_mode->ivsize);

	अगर (flags & FSCRYPT_POLICY_FLAG_IV_INO_LBLK_64) अणु
		WARN_ON_ONCE(lblk_num > U32_MAX);
		WARN_ON_ONCE(ci->ci_inode->i_ino > U32_MAX);
		lblk_num |= (u64)ci->ci_inode->i_ino << 32;
	पूर्ण अन्यथा अगर (flags & FSCRYPT_POLICY_FLAG_IV_INO_LBLK_32) अणु
		WARN_ON_ONCE(lblk_num > U32_MAX);
		lblk_num = (u32)(ci->ci_hashed_ino + lblk_num);
	पूर्ण अन्यथा अगर (flags & FSCRYPT_POLICY_FLAG_सूचीECT_KEY) अणु
		स_नकल(iv->nonce, ci->ci_nonce, FSCRYPT_खाता_NONCE_SIZE);
	पूर्ण
	iv->lblk_num = cpu_to_le64(lblk_num);
पूर्ण

/* Encrypt or decrypt a single fileप्रणाली block of file contents */
पूर्णांक fscrypt_crypt_block(स्थिर काष्ठा inode *inode, fscrypt_direction_t rw,
			u64 lblk_num, काष्ठा page *src_page,
			काष्ठा page *dest_page, अचिन्हित पूर्णांक len,
			अचिन्हित पूर्णांक offs, gfp_t gfp_flags)
अणु
	जोड़ fscrypt_iv iv;
	काष्ठा skcipher_request *req = शून्य;
	DECLARE_CRYPTO_WAIT(रुको);
	काष्ठा scatterlist dst, src;
	काष्ठा fscrypt_info *ci = inode->i_crypt_info;
	काष्ठा crypto_skcipher *tfm = ci->ci_enc_key.tfm;
	पूर्णांक res = 0;

	अगर (WARN_ON_ONCE(len <= 0))
		वापस -EINVAL;
	अगर (WARN_ON_ONCE(len % FS_CRYPTO_BLOCK_SIZE != 0))
		वापस -EINVAL;

	fscrypt_generate_iv(&iv, lblk_num, ci);

	req = skcipher_request_alloc(tfm, gfp_flags);
	अगर (!req)
		वापस -ENOMEM;

	skcipher_request_set_callback(
		req, CRYPTO_TFM_REQ_MAY_BACKLOG | CRYPTO_TFM_REQ_MAY_SLEEP,
		crypto_req_करोne, &रुको);

	sg_init_table(&dst, 1);
	sg_set_page(&dst, dest_page, len, offs);
	sg_init_table(&src, 1);
	sg_set_page(&src, src_page, len, offs);
	skcipher_request_set_crypt(req, &src, &dst, len, &iv);
	अगर (rw == FS_DECRYPT)
		res = crypto_रुको_req(crypto_skcipher_decrypt(req), &रुको);
	अन्यथा
		res = crypto_रुको_req(crypto_skcipher_encrypt(req), &रुको);
	skcipher_request_मुक्त(req);
	अगर (res) अणु
		fscrypt_err(inode, "%scryption failed for block %llu: %d",
			    (rw == FS_DECRYPT ? "De" : "En"), lblk_num, res);
		वापस res;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * fscrypt_encrypt_pagecache_blocks() - Encrypt fileप्रणाली blocks from a
 *					pagecache page
 * @page:      The locked pagecache page containing the block(s) to encrypt
 * @len:       Total size of the block(s) to encrypt.  Must be a nonzero
 *		multiple of the fileप्रणाली's block size.
 * @offs:      Byte offset within @page of the first block to encrypt.  Must be
 *		a multiple of the fileप्रणाली's block size.
 * @gfp_flags: Memory allocation flags.  See details below.
 *
 * A new bounce page is allocated, and the specअगरied block(s) are encrypted पूर्णांकo
 * it.  In the bounce page, the ciphertext block(s) will be located at the same
 * offsets at which the plaपूर्णांकext block(s) were located in the source page; any
 * other parts of the bounce page will be left uninitialized.  However, normally
 * blocksize == PAGE_SIZE and the whole page is encrypted at once.
 *
 * This is क्रम use by the fileप्रणाली's ->ग_लिखोpages() method.
 *
 * The bounce page allocation is mempool-backed, so it will always succeed when
 * @gfp_flags includes __GFP_सूचीECT_RECLAIM, e.g. when it's GFP_NOFS.  However,
 * only the first page of each bio can be allocated this way.  To prevent
 * deadlocks, क्रम any additional pages a mask like GFP_NOWAIT must be used.
 *
 * Return: the new encrypted bounce page on success; an ERR_PTR() on failure
 */
काष्ठा page *fscrypt_encrypt_pagecache_blocks(काष्ठा page *page,
					      अचिन्हित पूर्णांक len,
					      अचिन्हित पूर्णांक offs,
					      gfp_t gfp_flags)

अणु
	स्थिर काष्ठा inode *inode = page->mapping->host;
	स्थिर अचिन्हित पूर्णांक blockbits = inode->i_blkbits;
	स्थिर अचिन्हित पूर्णांक blocksize = 1 << blockbits;
	काष्ठा page *ciphertext_page;
	u64 lblk_num = ((u64)page->index << (PAGE_SHIFT - blockbits)) +
		       (offs >> blockbits);
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	अगर (WARN_ON_ONCE(!PageLocked(page)))
		वापस ERR_PTR(-EINVAL);

	अगर (WARN_ON_ONCE(len <= 0 || !IS_ALIGNED(len | offs, blocksize)))
		वापस ERR_PTR(-EINVAL);

	ciphertext_page = fscrypt_alloc_bounce_page(gfp_flags);
	अगर (!ciphertext_page)
		वापस ERR_PTR(-ENOMEM);

	क्रम (i = offs; i < offs + len; i += blocksize, lblk_num++) अणु
		err = fscrypt_crypt_block(inode, FS_ENCRYPT, lblk_num,
					  page, ciphertext_page,
					  blocksize, i, gfp_flags);
		अगर (err) अणु
			fscrypt_मुक्त_bounce_page(ciphertext_page);
			वापस ERR_PTR(err);
		पूर्ण
	पूर्ण
	SetPagePrivate(ciphertext_page);
	set_page_निजी(ciphertext_page, (अचिन्हित दीर्घ)page);
	वापस ciphertext_page;
पूर्ण
EXPORT_SYMBOL(fscrypt_encrypt_pagecache_blocks);

/**
 * fscrypt_encrypt_block_inplace() - Encrypt a fileप्रणाली block in-place
 * @inode:     The inode to which this block beदीर्घs
 * @page:      The page containing the block to encrypt
 * @len:       Size of block to encrypt.  Doesn't need to be a multiple of the
 *		fs block size, but must be a multiple of FS_CRYPTO_BLOCK_SIZE.
 * @offs:      Byte offset within @page at which the block to encrypt begins
 * @lblk_num:  Fileप्रणाली logical block number of the block, i.e. the 0-based
 *		number of the block within the file
 * @gfp_flags: Memory allocation flags
 *
 * Encrypt a possibly-compressed fileप्रणाली block that is located in an
 * arbitrary page, not necessarily in the original pagecache page.  The @inode
 * and @lblk_num must be specअगरied, as they can't be determined from @page.
 *
 * Return: 0 on success; -त्रुटि_सं on failure
 */
पूर्णांक fscrypt_encrypt_block_inplace(स्थिर काष्ठा inode *inode, काष्ठा page *page,
				  अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक offs,
				  u64 lblk_num, gfp_t gfp_flags)
अणु
	वापस fscrypt_crypt_block(inode, FS_ENCRYPT, lblk_num, page, page,
				   len, offs, gfp_flags);
पूर्ण
EXPORT_SYMBOL(fscrypt_encrypt_block_inplace);

/**
 * fscrypt_decrypt_pagecache_blocks() - Decrypt fileप्रणाली blocks in a
 *					pagecache page
 * @page:      The locked pagecache page containing the block(s) to decrypt
 * @len:       Total size of the block(s) to decrypt.  Must be a nonzero
 *		multiple of the fileप्रणाली's block size.
 * @offs:      Byte offset within @page of the first block to decrypt.  Must be
 *		a multiple of the fileप्रणाली's block size.
 *
 * The specअगरied block(s) are decrypted in-place within the pagecache page,
 * which must still be locked and not uptodate.  Normally, blocksize ==
 * PAGE_SIZE and the whole page is decrypted at once.
 *
 * This is क्रम use by the fileप्रणाली's ->पढ़ोpages() method.
 *
 * Return: 0 on success; -त्रुटि_सं on failure
 */
पूर्णांक fscrypt_decrypt_pagecache_blocks(काष्ठा page *page, अचिन्हित पूर्णांक len,
				     अचिन्हित पूर्णांक offs)
अणु
	स्थिर काष्ठा inode *inode = page->mapping->host;
	स्थिर अचिन्हित पूर्णांक blockbits = inode->i_blkbits;
	स्थिर अचिन्हित पूर्णांक blocksize = 1 << blockbits;
	u64 lblk_num = ((u64)page->index << (PAGE_SHIFT - blockbits)) +
		       (offs >> blockbits);
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	अगर (WARN_ON_ONCE(!PageLocked(page)))
		वापस -EINVAL;

	अगर (WARN_ON_ONCE(len <= 0 || !IS_ALIGNED(len | offs, blocksize)))
		वापस -EINVAL;

	क्रम (i = offs; i < offs + len; i += blocksize, lblk_num++) अणु
		err = fscrypt_crypt_block(inode, FS_DECRYPT, lblk_num, page,
					  page, blocksize, i, GFP_NOFS);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(fscrypt_decrypt_pagecache_blocks);

/**
 * fscrypt_decrypt_block_inplace() - Decrypt a fileप्रणाली block in-place
 * @inode:     The inode to which this block beदीर्घs
 * @page:      The page containing the block to decrypt
 * @len:       Size of block to decrypt.  Doesn't need to be a multiple of the
 *		fs block size, but must be a multiple of FS_CRYPTO_BLOCK_SIZE.
 * @offs:      Byte offset within @page at which the block to decrypt begins
 * @lblk_num:  Fileप्रणाली logical block number of the block, i.e. the 0-based
 *		number of the block within the file
 *
 * Decrypt a possibly-compressed fileप्रणाली block that is located in an
 * arbitrary page, not necessarily in the original pagecache page.  The @inode
 * and @lblk_num must be specअगरied, as they can't be determined from @page.
 *
 * Return: 0 on success; -त्रुटि_सं on failure
 */
पूर्णांक fscrypt_decrypt_block_inplace(स्थिर काष्ठा inode *inode, काष्ठा page *page,
				  अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक offs,
				  u64 lblk_num)
अणु
	वापस fscrypt_crypt_block(inode, FS_DECRYPT, lblk_num, page, page,
				   len, offs, GFP_NOFS);
पूर्ण
EXPORT_SYMBOL(fscrypt_decrypt_block_inplace);

/**
 * fscrypt_initialize() - allocate major buffers क्रम fs encryption.
 * @cop_flags:  fscrypt operations flags
 *
 * We only call this when we start accessing encrypted files, since it
 * results in memory getting allocated that wouldn't otherwise be used.
 *
 * Return: 0 on success; -त्रुटि_सं on failure
 */
पूर्णांक fscrypt_initialize(अचिन्हित पूर्णांक cop_flags)
अणु
	पूर्णांक err = 0;

	/* No need to allocate a bounce page pool अगर this FS won't use it. */
	अगर (cop_flags & FS_CFLG_OWN_PAGES)
		वापस 0;

	mutex_lock(&fscrypt_init_mutex);
	अगर (fscrypt_bounce_page_pool)
		जाओ out_unlock;

	err = -ENOMEM;
	fscrypt_bounce_page_pool =
		mempool_create_page_pool(num_pपुनः_स्मृति_crypto_pages, 0);
	अगर (!fscrypt_bounce_page_pool)
		जाओ out_unlock;

	err = 0;
out_unlock:
	mutex_unlock(&fscrypt_init_mutex);
	वापस err;
पूर्ण

व्योम fscrypt_msg(स्थिर काष्ठा inode *inode, स्थिर अक्षर *level,
		 स्थिर अक्षर *fmt, ...)
अणु
	अटल DEFINE_RATELIMIT_STATE(rs, DEFAULT_RATELIMIT_INTERVAL,
				      DEFAULT_RATELIMIT_BURST);
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	अगर (!__ratelimit(&rs))
		वापस;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	अगर (inode && inode->i_ino)
		prपूर्णांकk("%sfscrypt (%s, inode %lu): %pV\n",
		       level, inode->i_sb->s_id, inode->i_ino, &vaf);
	अन्यथा अगर (inode)
		prपूर्णांकk("%sfscrypt (%s): %pV\n", level, inode->i_sb->s_id, &vaf);
	अन्यथा
		prपूर्णांकk("%sfscrypt: %pV\n", level, &vaf);
	बहु_पूर्ण(args);
पूर्ण

/**
 * fscrypt_init() - Set up क्रम fs encryption.
 *
 * Return: 0 on success; -त्रुटि_सं on failure
 */
अटल पूर्णांक __init fscrypt_init(व्योम)
अणु
	पूर्णांक err = -ENOMEM;

	/*
	 * Use an unbound workqueue to allow bios to be decrypted in parallel
	 * even when they happen to complete on the same CPU.  This sacrअगरices
	 * locality, but it's worthजबतक since decryption is CPU-पूर्णांकensive.
	 *
	 * Also use a high-priority workqueue to prioritize decryption work,
	 * which blocks पढ़ोs from completing, over regular application tasks.
	 */
	fscrypt_पढ़ो_workqueue = alloc_workqueue("fscrypt_read_queue",
						 WQ_UNBOUND | WQ_HIGHPRI,
						 num_online_cpus());
	अगर (!fscrypt_पढ़ो_workqueue)
		जाओ fail;

	fscrypt_info_cachep = KMEM_CACHE(fscrypt_info, SLAB_RECLAIM_ACCOUNT);
	अगर (!fscrypt_info_cachep)
		जाओ fail_मुक्त_queue;

	err = fscrypt_init_keyring();
	अगर (err)
		जाओ fail_मुक्त_info;

	वापस 0;

fail_मुक्त_info:
	kmem_cache_destroy(fscrypt_info_cachep);
fail_मुक्त_queue:
	destroy_workqueue(fscrypt_पढ़ो_workqueue);
fail:
	वापस err;
पूर्ण
late_initcall(fscrypt_init)
