<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * eCryptfs: Linux fileप्रणाली encryption layer
 *
 * Copyright (C) 1997-2004 Erez Zaकरोk
 * Copyright (C) 2001-2004 Stony Brook University
 * Copyright (C) 2004-2007 International Business Machines Corp.
 *   Author(s): Michael A. Halcrow <mahalcro@us.ibm.com>
 *   		Michael C. Thompson <mcthomps@us.ibm.com>
 */

#समावेश <crypto/hash.h>
#समावेश <crypto/skcipher.h>
#समावेश <linux/fs.h>
#समावेश <linux/mount.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/compiler.h>
#समावेश <linux/key.h>
#समावेश <linux/namei.h>
#समावेश <linux/file.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/kernel.h>
#समावेश <linux/xattr.h>
#समावेश "ecryptfs_kernel.h"

#घोषणा DECRYPT		0
#घोषणा ENCRYPT		1

/**
 * ecryptfs_from_hex
 * @dst: Buffer to take the bytes from src hex; must be at least of
 *       size (src_size / 2)
 * @src: Buffer to be converted from a hex string representation to raw value
 * @dst_size: size of dst buffer, or number of hex अक्षरacters pairs to convert
 */
व्योम ecryptfs_from_hex(अक्षर *dst, अक्षर *src, पूर्णांक dst_size)
अणु
	पूर्णांक x;
	अक्षर पंचांगp[3] = अणु 0, पूर्ण;

	क्रम (x = 0; x < dst_size; x++) अणु
		पंचांगp[0] = src[x * 2];
		पंचांगp[1] = src[x * 2 + 1];
		dst[x] = (अचिन्हित अक्षर)simple_म_से_दीर्घ(पंचांगp, शून्य, 16);
	पूर्ण
पूर्ण

/**
 * ecryptfs_calculate_md5 - calculates the md5 of @src
 * @dst: Poपूर्णांकer to 16 bytes of allocated memory
 * @crypt_stat: Poपूर्णांकer to crypt_stat काष्ठा क्रम the current inode
 * @src: Data to be md5'd
 * @len: Length of @src
 *
 * Uses the allocated crypto context that crypt_stat references to
 * generate the MD5 sum of the contents of src.
 */
अटल पूर्णांक ecryptfs_calculate_md5(अक्षर *dst,
				  काष्ठा ecryptfs_crypt_stat *crypt_stat,
				  अक्षर *src, पूर्णांक len)
अणु
	पूर्णांक rc = crypto_shash_tfm_digest(crypt_stat->hash_tfm, src, len, dst);

	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR
		       "%s: Error computing crypto hash; rc = [%d]\n",
		       __func__, rc);
		जाओ out;
	पूर्ण
out:
	वापस rc;
पूर्ण

अटल पूर्णांक ecryptfs_crypto_api_algअगरy_cipher_name(अक्षर **algअगरied_name,
						  अक्षर *cipher_name,
						  अक्षर *chaining_modअगरier)
अणु
	पूर्णांक cipher_name_len = म_माप(cipher_name);
	पूर्णांक chaining_modअगरier_len = म_माप(chaining_modअगरier);
	पूर्णांक algअगरied_name_len;
	पूर्णांक rc;

	algअगरied_name_len = (chaining_modअगरier_len + cipher_name_len + 3);
	(*algअगरied_name) = kदो_स्मृति(algअगरied_name_len, GFP_KERNEL);
	अगर (!(*algअगरied_name)) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	snम_लिखो((*algअगरied_name), algअगरied_name_len, "%s(%s)",
		 chaining_modअगरier, cipher_name);
	rc = 0;
out:
	वापस rc;
पूर्ण

/**
 * ecryptfs_derive_iv
 * @iv: destination क्रम the derived iv vale
 * @crypt_stat: Poपूर्णांकer to crypt_stat काष्ठा क्रम the current inode
 * @offset: Offset of the extent whose IV we are to derive
 *
 * Generate the initialization vector from the given root IV and page
 * offset.
 *
 * Returns zero on success; non-zero on error.
 */
पूर्णांक ecryptfs_derive_iv(अक्षर *iv, काष्ठा ecryptfs_crypt_stat *crypt_stat,
		       loff_t offset)
अणु
	पूर्णांक rc = 0;
	अक्षर dst[MD5_DIGEST_SIZE];
	अक्षर src[ECRYPTFS_MAX_IV_BYTES + 16];

	अगर (unlikely(ecryptfs_verbosity > 0)) अणु
		ecryptfs_prपूर्णांकk(KERN_DEBUG, "root iv:\n");
		ecryptfs_dump_hex(crypt_stat->root_iv, crypt_stat->iv_bytes);
	पूर्ण
	/* TODO: It is probably secure to just cast the least
	 * signअगरicant bits of the root IV पूर्णांकo an अचिन्हित दीर्घ and
	 * add the offset to that rather than go through all this
	 * hashing business. -Halcrow */
	स_नकल(src, crypt_stat->root_iv, crypt_stat->iv_bytes);
	स_रखो((src + crypt_stat->iv_bytes), 0, 16);
	snम_लिखो((src + crypt_stat->iv_bytes), 16, "%lld", offset);
	अगर (unlikely(ecryptfs_verbosity > 0)) अणु
		ecryptfs_prपूर्णांकk(KERN_DEBUG, "source:\n");
		ecryptfs_dump_hex(src, (crypt_stat->iv_bytes + 16));
	पूर्ण
	rc = ecryptfs_calculate_md5(dst, crypt_stat, src,
				    (crypt_stat->iv_bytes + 16));
	अगर (rc) अणु
		ecryptfs_prपूर्णांकk(KERN_WARNING, "Error attempting to compute "
				"MD5 while generating IV for a page\n");
		जाओ out;
	पूर्ण
	स_नकल(iv, dst, crypt_stat->iv_bytes);
	अगर (unlikely(ecryptfs_verbosity > 0)) अणु
		ecryptfs_prपूर्णांकk(KERN_DEBUG, "derived iv:\n");
		ecryptfs_dump_hex(iv, crypt_stat->iv_bytes);
	पूर्ण
out:
	वापस rc;
पूर्ण

/**
 * ecryptfs_init_crypt_stat
 * @crypt_stat: Poपूर्णांकer to the crypt_stat काष्ठा to initialize.
 *
 * Initialize the crypt_stat काष्ठाure.
 */
पूर्णांक ecryptfs_init_crypt_stat(काष्ठा ecryptfs_crypt_stat *crypt_stat)
अणु
	काष्ठा crypto_shash *tfm;
	पूर्णांक rc;

	tfm = crypto_alloc_shash(ECRYPTFS_DEFAULT_HASH, 0, 0);
	अगर (IS_ERR(tfm)) अणु
		rc = PTR_ERR(tfm);
		ecryptfs_prपूर्णांकk(KERN_ERR, "Error attempting to "
				"allocate crypto context; rc = [%d]\n",
				rc);
		वापस rc;
	पूर्ण

	स_रखो((व्योम *)crypt_stat, 0, माप(काष्ठा ecryptfs_crypt_stat));
	INIT_LIST_HEAD(&crypt_stat->keysig_list);
	mutex_init(&crypt_stat->keysig_list_mutex);
	mutex_init(&crypt_stat->cs_mutex);
	mutex_init(&crypt_stat->cs_tfm_mutex);
	crypt_stat->hash_tfm = tfm;
	crypt_stat->flags |= ECRYPTFS_STRUCT_INITIALIZED;

	वापस 0;
पूर्ण

/**
 * ecryptfs_destroy_crypt_stat
 * @crypt_stat: Poपूर्णांकer to the crypt_stat काष्ठा to initialize.
 *
 * Releases all memory associated with a crypt_stat काष्ठा.
 */
व्योम ecryptfs_destroy_crypt_stat(काष्ठा ecryptfs_crypt_stat *crypt_stat)
अणु
	काष्ठा ecryptfs_key_sig *key_sig, *key_sig_पंचांगp;

	crypto_मुक्त_skcipher(crypt_stat->tfm);
	crypto_मुक्त_shash(crypt_stat->hash_tfm);
	list_क्रम_each_entry_safe(key_sig, key_sig_पंचांगp,
				 &crypt_stat->keysig_list, crypt_stat_list) अणु
		list_del(&key_sig->crypt_stat_list);
		kmem_cache_मुक्त(ecryptfs_key_sig_cache, key_sig);
	पूर्ण
	स_रखो(crypt_stat, 0, माप(काष्ठा ecryptfs_crypt_stat));
पूर्ण

व्योम ecryptfs_destroy_mount_crypt_stat(
	काष्ठा ecryptfs_mount_crypt_stat *mount_crypt_stat)
अणु
	काष्ठा ecryptfs_global_auth_tok *auth_tok, *auth_tok_पंचांगp;

	अगर (!(mount_crypt_stat->flags & ECRYPTFS_MOUNT_CRYPT_STAT_INITIALIZED))
		वापस;
	mutex_lock(&mount_crypt_stat->global_auth_tok_list_mutex);
	list_क्रम_each_entry_safe(auth_tok, auth_tok_पंचांगp,
				 &mount_crypt_stat->global_auth_tok_list,
				 mount_crypt_stat_list) अणु
		list_del(&auth_tok->mount_crypt_stat_list);
		अगर (!(auth_tok->flags & ECRYPTFS_AUTH_TOK_INVALID))
			key_put(auth_tok->global_auth_tok_key);
		kmem_cache_मुक्त(ecryptfs_global_auth_tok_cache, auth_tok);
	पूर्ण
	mutex_unlock(&mount_crypt_stat->global_auth_tok_list_mutex);
	स_रखो(mount_crypt_stat, 0, माप(काष्ठा ecryptfs_mount_crypt_stat));
पूर्ण

/**
 * virt_to_scatterlist
 * @addr: Virtual address
 * @size: Size of data; should be an even multiple of the block size
 * @sg: Poपूर्णांकer to scatterlist array; set to शून्य to obtain only
 *      the number of scatterlist काष्ठाs required in array
 * @sg_size: Max array size
 *
 * Fills in a scatterlist array with page references क्रम a passed
 * भव address.
 *
 * Returns the number of scatterlist काष्ठाs in array used
 */
पूर्णांक virt_to_scatterlist(स्थिर व्योम *addr, पूर्णांक size, काष्ठा scatterlist *sg,
			पूर्णांक sg_size)
अणु
	पूर्णांक i = 0;
	काष्ठा page *pg;
	पूर्णांक offset;
	पूर्णांक reमुख्यder_of_page;

	sg_init_table(sg, sg_size);

	जबतक (size > 0 && i < sg_size) अणु
		pg = virt_to_page(addr);
		offset = offset_in_page(addr);
		sg_set_page(&sg[i], pg, 0, offset);
		reमुख्यder_of_page = PAGE_SIZE - offset;
		अगर (size >= reमुख्यder_of_page) अणु
			sg[i].length = reमुख्यder_of_page;
			addr += reमुख्यder_of_page;
			size -= reमुख्यder_of_page;
		पूर्ण अन्यथा अणु
			sg[i].length = size;
			addr += size;
			size = 0;
		पूर्ण
		i++;
	पूर्ण
	अगर (size > 0)
		वापस -ENOMEM;
	वापस i;
पूर्ण

काष्ठा extent_crypt_result अणु
	काष्ठा completion completion;
	पूर्णांक rc;
पूर्ण;

अटल व्योम extent_crypt_complete(काष्ठा crypto_async_request *req, पूर्णांक rc)
अणु
	काष्ठा extent_crypt_result *ecr = req->data;

	अगर (rc == -EINPROGRESS)
		वापस;

	ecr->rc = rc;
	complete(&ecr->completion);
पूर्ण

/**
 * crypt_scatterlist
 * @crypt_stat: Poपूर्णांकer to the crypt_stat काष्ठा to initialize.
 * @dst_sg: Destination of the data after perक्रमming the crypto operation
 * @src_sg: Data to be encrypted or decrypted
 * @size: Length of data
 * @iv: IV to use
 * @op: ENCRYPT or DECRYPT to indicate the desired operation
 *
 * Returns the number of bytes encrypted or decrypted; negative value on error
 */
अटल पूर्णांक crypt_scatterlist(काष्ठा ecryptfs_crypt_stat *crypt_stat,
			     काष्ठा scatterlist *dst_sg,
			     काष्ठा scatterlist *src_sg, पूर्णांक size,
			     अचिन्हित अक्षर *iv, पूर्णांक op)
अणु
	काष्ठा skcipher_request *req = शून्य;
	काष्ठा extent_crypt_result ecr;
	पूर्णांक rc = 0;

	अगर (unlikely(ecryptfs_verbosity > 0)) अणु
		ecryptfs_prपूर्णांकk(KERN_DEBUG, "Key size [%zd]; key:\n",
				crypt_stat->key_size);
		ecryptfs_dump_hex(crypt_stat->key,
				  crypt_stat->key_size);
	पूर्ण

	init_completion(&ecr.completion);

	mutex_lock(&crypt_stat->cs_tfm_mutex);
	req = skcipher_request_alloc(crypt_stat->tfm, GFP_NOFS);
	अगर (!req) अणु
		mutex_unlock(&crypt_stat->cs_tfm_mutex);
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	skcipher_request_set_callback(req,
			CRYPTO_TFM_REQ_MAY_BACKLOG | CRYPTO_TFM_REQ_MAY_SLEEP,
			extent_crypt_complete, &ecr);
	/* Consider करोing this once, when the file is खोलोed */
	अगर (!(crypt_stat->flags & ECRYPTFS_KEY_SET)) अणु
		rc = crypto_skcipher_setkey(crypt_stat->tfm, crypt_stat->key,
					    crypt_stat->key_size);
		अगर (rc) अणु
			ecryptfs_prपूर्णांकk(KERN_ERR,
					"Error setting key; rc = [%d]\n",
					rc);
			mutex_unlock(&crypt_stat->cs_tfm_mutex);
			rc = -EINVAL;
			जाओ out;
		पूर्ण
		crypt_stat->flags |= ECRYPTFS_KEY_SET;
	पूर्ण
	mutex_unlock(&crypt_stat->cs_tfm_mutex);
	skcipher_request_set_crypt(req, src_sg, dst_sg, size, iv);
	rc = op == ENCRYPT ? crypto_skcipher_encrypt(req) :
			     crypto_skcipher_decrypt(req);
	अगर (rc == -EINPROGRESS || rc == -EBUSY) अणु
		काष्ठा extent_crypt_result *ecr = req->base.data;

		रुको_क्रम_completion(&ecr->completion);
		rc = ecr->rc;
		reinit_completion(&ecr->completion);
	पूर्ण
out:
	skcipher_request_मुक्त(req);
	वापस rc;
पूर्ण

/*
 * lower_offset_क्रम_page
 *
 * Convert an eCryptfs page index पूर्णांकo a lower byte offset
 */
अटल loff_t lower_offset_क्रम_page(काष्ठा ecryptfs_crypt_stat *crypt_stat,
				    काष्ठा page *page)
अणु
	वापस ecryptfs_lower_header_size(crypt_stat) +
	       ((loff_t)page->index << PAGE_SHIFT);
पूर्ण

/**
 * crypt_extent
 * @crypt_stat: crypt_stat containing cryptographic context क्रम the
 *              encryption operation
 * @dst_page: The page to ग_लिखो the result पूर्णांकo
 * @src_page: The page to पढ़ो from
 * @extent_offset: Page extent offset क्रम use in generating IV
 * @op: ENCRYPT or DECRYPT to indicate the desired operation
 *
 * Encrypts or decrypts one extent of data.
 *
 * Return zero on success; non-zero otherwise
 */
अटल पूर्णांक crypt_extent(काष्ठा ecryptfs_crypt_stat *crypt_stat,
			काष्ठा page *dst_page,
			काष्ठा page *src_page,
			अचिन्हित दीर्घ extent_offset, पूर्णांक op)
अणु
	pgoff_t page_index = op == ENCRYPT ? src_page->index : dst_page->index;
	loff_t extent_base;
	अक्षर extent_iv[ECRYPTFS_MAX_IV_BYTES];
	काष्ठा scatterlist src_sg, dst_sg;
	माप_प्रकार extent_size = crypt_stat->extent_size;
	पूर्णांक rc;

	extent_base = (((loff_t)page_index) * (PAGE_SIZE / extent_size));
	rc = ecryptfs_derive_iv(extent_iv, crypt_stat,
				(extent_base + extent_offset));
	अगर (rc) अणु
		ecryptfs_prपूर्णांकk(KERN_ERR, "Error attempting to derive IV for "
			"extent [0x%.16llx]; rc = [%d]\n",
			(अचिन्हित दीर्घ दीर्घ)(extent_base + extent_offset), rc);
		जाओ out;
	पूर्ण

	sg_init_table(&src_sg, 1);
	sg_init_table(&dst_sg, 1);

	sg_set_page(&src_sg, src_page, extent_size,
		    extent_offset * extent_size);
	sg_set_page(&dst_sg, dst_page, extent_size,
		    extent_offset * extent_size);

	rc = crypt_scatterlist(crypt_stat, &dst_sg, &src_sg, extent_size,
			       extent_iv, op);
	अगर (rc < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: Error attempting to crypt page with "
		       "page_index = [%ld], extent_offset = [%ld]; "
		       "rc = [%d]\n", __func__, page_index, extent_offset, rc);
		जाओ out;
	पूर्ण
	rc = 0;
out:
	वापस rc;
पूर्ण

/**
 * ecryptfs_encrypt_page
 * @page: Page mapped from the eCryptfs inode क्रम the file; contains
 *        decrypted content that needs to be encrypted (to a temporary
 *        page; not in place) and written out to the lower file
 *
 * Encrypt an eCryptfs page. This is करोne on a per-extent basis. Note
 * that eCryptfs pages may straddle the lower pages -- क्रम instance,
 * अगर the file was created on a machine with an 8K page size
 * (resulting in an 8K header), and then the file is copied onto a
 * host with a 32K page size, then when पढ़ोing page 0 of the eCryptfs
 * file, 24K of page 0 of the lower file will be पढ़ो and decrypted,
 * and then 8K of page 1 of the lower file will be पढ़ो and decrypted.
 *
 * Returns zero on success; negative on error
 */
पूर्णांक ecryptfs_encrypt_page(काष्ठा page *page)
अणु
	काष्ठा inode *ecryptfs_inode;
	काष्ठा ecryptfs_crypt_stat *crypt_stat;
	अक्षर *enc_extent_virt;
	काष्ठा page *enc_extent_page = शून्य;
	loff_t extent_offset;
	loff_t lower_offset;
	पूर्णांक rc = 0;

	ecryptfs_inode = page->mapping->host;
	crypt_stat =
		&(ecryptfs_inode_to_निजी(ecryptfs_inode)->crypt_stat);
	BUG_ON(!(crypt_stat->flags & ECRYPTFS_ENCRYPTED));
	enc_extent_page = alloc_page(GFP_USER);
	अगर (!enc_extent_page) अणु
		rc = -ENOMEM;
		ecryptfs_prपूर्णांकk(KERN_ERR, "Error allocating memory for "
				"encrypted extent\n");
		जाओ out;
	पूर्ण

	क्रम (extent_offset = 0;
	     extent_offset < (PAGE_SIZE / crypt_stat->extent_size);
	     extent_offset++) अणु
		rc = crypt_extent(crypt_stat, enc_extent_page, page,
				  extent_offset, ENCRYPT);
		अगर (rc) अणु
			prपूर्णांकk(KERN_ERR "%s: Error encrypting extent; "
			       "rc = [%d]\n", __func__, rc);
			जाओ out;
		पूर्ण
	पूर्ण

	lower_offset = lower_offset_क्रम_page(crypt_stat, page);
	enc_extent_virt = kmap(enc_extent_page);
	rc = ecryptfs_ग_लिखो_lower(ecryptfs_inode, enc_extent_virt, lower_offset,
				  PAGE_SIZE);
	kunmap(enc_extent_page);
	अगर (rc < 0) अणु
		ecryptfs_prपूर्णांकk(KERN_ERR,
			"Error attempting to write lower page; rc = [%d]\n",
			rc);
		जाओ out;
	पूर्ण
	rc = 0;
out:
	अगर (enc_extent_page) अणु
		__मुक्त_page(enc_extent_page);
	पूर्ण
	वापस rc;
पूर्ण

/**
 * ecryptfs_decrypt_page
 * @page: Page mapped from the eCryptfs inode क्रम the file; data पढ़ो
 *        and decrypted from the lower file will be written पूर्णांकo this
 *        page
 *
 * Decrypt an eCryptfs page. This is करोne on a per-extent basis. Note
 * that eCryptfs pages may straddle the lower pages -- क्रम instance,
 * अगर the file was created on a machine with an 8K page size
 * (resulting in an 8K header), and then the file is copied onto a
 * host with a 32K page size, then when पढ़ोing page 0 of the eCryptfs
 * file, 24K of page 0 of the lower file will be पढ़ो and decrypted,
 * and then 8K of page 1 of the lower file will be पढ़ो and decrypted.
 *
 * Returns zero on success; negative on error
 */
पूर्णांक ecryptfs_decrypt_page(काष्ठा page *page)
अणु
	काष्ठा inode *ecryptfs_inode;
	काष्ठा ecryptfs_crypt_stat *crypt_stat;
	अक्षर *page_virt;
	अचिन्हित दीर्घ extent_offset;
	loff_t lower_offset;
	पूर्णांक rc = 0;

	ecryptfs_inode = page->mapping->host;
	crypt_stat =
		&(ecryptfs_inode_to_निजी(ecryptfs_inode)->crypt_stat);
	BUG_ON(!(crypt_stat->flags & ECRYPTFS_ENCRYPTED));

	lower_offset = lower_offset_क्रम_page(crypt_stat, page);
	page_virt = kmap(page);
	rc = ecryptfs_पढ़ो_lower(page_virt, lower_offset, PAGE_SIZE,
				 ecryptfs_inode);
	kunmap(page);
	अगर (rc < 0) अणु
		ecryptfs_prपूर्णांकk(KERN_ERR,
			"Error attempting to read lower page; rc = [%d]\n",
			rc);
		जाओ out;
	पूर्ण

	क्रम (extent_offset = 0;
	     extent_offset < (PAGE_SIZE / crypt_stat->extent_size);
	     extent_offset++) अणु
		rc = crypt_extent(crypt_stat, page, page,
				  extent_offset, DECRYPT);
		अगर (rc) अणु
			prपूर्णांकk(KERN_ERR "%s: Error decrypting extent; "
			       "rc = [%d]\n", __func__, rc);
			जाओ out;
		पूर्ण
	पूर्ण
out:
	वापस rc;
पूर्ण

#घोषणा ECRYPTFS_MAX_SCATTERLIST_LEN 4

/**
 * ecryptfs_init_crypt_ctx
 * @crypt_stat: Uninitialized crypt stats काष्ठाure
 *
 * Initialize the crypto context.
 *
 * TODO: Perक्रमmance: Keep a cache of initialized cipher contexts;
 * only init अगर needed
 */
पूर्णांक ecryptfs_init_crypt_ctx(काष्ठा ecryptfs_crypt_stat *crypt_stat)
अणु
	अक्षर *full_alg_name;
	पूर्णांक rc = -EINVAL;

	ecryptfs_prपूर्णांकk(KERN_DEBUG,
			"Initializing cipher [%s]; strlen = [%d]; "
			"key_size_bits = [%zd]\n",
			crypt_stat->cipher, (पूर्णांक)म_माप(crypt_stat->cipher),
			crypt_stat->key_size << 3);
	mutex_lock(&crypt_stat->cs_tfm_mutex);
	अगर (crypt_stat->tfm) अणु
		rc = 0;
		जाओ out_unlock;
	पूर्ण
	rc = ecryptfs_crypto_api_algअगरy_cipher_name(&full_alg_name,
						    crypt_stat->cipher, "cbc");
	अगर (rc)
		जाओ out_unlock;
	crypt_stat->tfm = crypto_alloc_skcipher(full_alg_name, 0, 0);
	अगर (IS_ERR(crypt_stat->tfm)) अणु
		rc = PTR_ERR(crypt_stat->tfm);
		crypt_stat->tfm = शून्य;
		ecryptfs_prपूर्णांकk(KERN_ERR, "cryptfs: init_crypt_ctx(): "
				"Error initializing cipher [%s]\n",
				full_alg_name);
		जाओ out_मुक्त;
	पूर्ण
	crypto_skcipher_set_flags(crypt_stat->tfm,
				  CRYPTO_TFM_REQ_FORBID_WEAK_KEYS);
	rc = 0;
out_मुक्त:
	kमुक्त(full_alg_name);
out_unlock:
	mutex_unlock(&crypt_stat->cs_tfm_mutex);
	वापस rc;
पूर्ण

अटल व्योम set_extent_mask_and_shअगरt(काष्ठा ecryptfs_crypt_stat *crypt_stat)
अणु
	पूर्णांक extent_माप_प्रकारmp;

	crypt_stat->extent_mask = 0xFFFFFFFF;
	crypt_stat->extent_shअगरt = 0;
	अगर (crypt_stat->extent_size == 0)
		वापस;
	extent_माप_प्रकारmp = crypt_stat->extent_size;
	जबतक ((extent_माप_प्रकारmp & 0x01) == 0) अणु
		extent_माप_प्रकारmp >>= 1;
		crypt_stat->extent_mask <<= 1;
		crypt_stat->extent_shअगरt++;
	पूर्ण
पूर्ण

व्योम ecryptfs_set_शेष_sizes(काष्ठा ecryptfs_crypt_stat *crypt_stat)
अणु
	/* Default values; may be overwritten as we are parsing the
	 * packets. */
	crypt_stat->extent_size = ECRYPTFS_DEFAULT_EXTENT_SIZE;
	set_extent_mask_and_shअगरt(crypt_stat);
	crypt_stat->iv_bytes = ECRYPTFS_DEFAULT_IV_BYTES;
	अगर (crypt_stat->flags & ECRYPTFS_METADATA_IN_XATTR)
		crypt_stat->metadata_size = ECRYPTFS_MINIMUM_HEADER_EXTENT_SIZE;
	अन्यथा अणु
		अगर (PAGE_SIZE <= ECRYPTFS_MINIMUM_HEADER_EXTENT_SIZE)
			crypt_stat->metadata_size =
				ECRYPTFS_MINIMUM_HEADER_EXTENT_SIZE;
		अन्यथा
			crypt_stat->metadata_size = PAGE_SIZE;
	पूर्ण
पूर्ण

/*
 * ecryptfs_compute_root_iv
 *
 * On error, sets the root IV to all 0's.
 */
पूर्णांक ecryptfs_compute_root_iv(काष्ठा ecryptfs_crypt_stat *crypt_stat)
अणु
	पूर्णांक rc = 0;
	अक्षर dst[MD5_DIGEST_SIZE];

	BUG_ON(crypt_stat->iv_bytes > MD5_DIGEST_SIZE);
	BUG_ON(crypt_stat->iv_bytes <= 0);
	अगर (!(crypt_stat->flags & ECRYPTFS_KEY_VALID)) अणु
		rc = -EINVAL;
		ecryptfs_prपूर्णांकk(KERN_WARNING, "Session key not valid; "
				"cannot generate root IV\n");
		जाओ out;
	पूर्ण
	rc = ecryptfs_calculate_md5(dst, crypt_stat, crypt_stat->key,
				    crypt_stat->key_size);
	अगर (rc) अणु
		ecryptfs_prपूर्णांकk(KERN_WARNING, "Error attempting to compute "
				"MD5 while generating root IV\n");
		जाओ out;
	पूर्ण
	स_नकल(crypt_stat->root_iv, dst, crypt_stat->iv_bytes);
out:
	अगर (rc) अणु
		स_रखो(crypt_stat->root_iv, 0, crypt_stat->iv_bytes);
		crypt_stat->flags |= ECRYPTFS_SECURITY_WARNING;
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम ecryptfs_generate_new_key(काष्ठा ecryptfs_crypt_stat *crypt_stat)
अणु
	get_अक्रमom_bytes(crypt_stat->key, crypt_stat->key_size);
	crypt_stat->flags |= ECRYPTFS_KEY_VALID;
	ecryptfs_compute_root_iv(crypt_stat);
	अगर (unlikely(ecryptfs_verbosity > 0)) अणु
		ecryptfs_prपूर्णांकk(KERN_DEBUG, "Generated new session key:\n");
		ecryptfs_dump_hex(crypt_stat->key,
				  crypt_stat->key_size);
	पूर्ण
पूर्ण

/**
 * ecryptfs_copy_mount_wide_flags_to_inode_flags
 * @crypt_stat: The inode's cryptographic context
 * @mount_crypt_stat: The mount poपूर्णांक's cryptographic context
 *
 * This function propagates the mount-wide flags to inभागidual inode
 * flags.
 */
अटल व्योम ecryptfs_copy_mount_wide_flags_to_inode_flags(
	काष्ठा ecryptfs_crypt_stat *crypt_stat,
	काष्ठा ecryptfs_mount_crypt_stat *mount_crypt_stat)
अणु
	अगर (mount_crypt_stat->flags & ECRYPTFS_XATTR_METADATA_ENABLED)
		crypt_stat->flags |= ECRYPTFS_METADATA_IN_XATTR;
	अगर (mount_crypt_stat->flags & ECRYPTFS_ENCRYPTED_VIEW_ENABLED)
		crypt_stat->flags |= ECRYPTFS_VIEW_AS_ENCRYPTED;
	अगर (mount_crypt_stat->flags & ECRYPTFS_GLOBAL_ENCRYPT_खाताNAMES) अणु
		crypt_stat->flags |= ECRYPTFS_ENCRYPT_खाताNAMES;
		अगर (mount_crypt_stat->flags
		    & ECRYPTFS_GLOBAL_ENCFN_USE_MOUNT_FNEK)
			crypt_stat->flags |= ECRYPTFS_ENCFN_USE_MOUNT_FNEK;
		अन्यथा अगर (mount_crypt_stat->flags
			 & ECRYPTFS_GLOBAL_ENCFN_USE_FEK)
			crypt_stat->flags |= ECRYPTFS_ENCFN_USE_FEK;
	पूर्ण
पूर्ण

अटल पूर्णांक ecryptfs_copy_mount_wide_sigs_to_inode_sigs(
	काष्ठा ecryptfs_crypt_stat *crypt_stat,
	काष्ठा ecryptfs_mount_crypt_stat *mount_crypt_stat)
अणु
	काष्ठा ecryptfs_global_auth_tok *global_auth_tok;
	पूर्णांक rc = 0;

	mutex_lock(&crypt_stat->keysig_list_mutex);
	mutex_lock(&mount_crypt_stat->global_auth_tok_list_mutex);

	list_क्रम_each_entry(global_auth_tok,
			    &mount_crypt_stat->global_auth_tok_list,
			    mount_crypt_stat_list) अणु
		अगर (global_auth_tok->flags & ECRYPTFS_AUTH_TOK_FNEK)
			जारी;
		rc = ecryptfs_add_keysig(crypt_stat, global_auth_tok->sig);
		अगर (rc) अणु
			prपूर्णांकk(KERN_ERR "Error adding keysig; rc = [%d]\n", rc);
			जाओ out;
		पूर्ण
	पूर्ण

out:
	mutex_unlock(&mount_crypt_stat->global_auth_tok_list_mutex);
	mutex_unlock(&crypt_stat->keysig_list_mutex);
	वापस rc;
पूर्ण

/**
 * ecryptfs_set_शेष_crypt_stat_vals
 * @crypt_stat: The inode's cryptographic context
 * @mount_crypt_stat: The mount poपूर्णांक's cryptographic context
 *
 * Default values in the event that policy करोes not override them.
 */
अटल व्योम ecryptfs_set_शेष_crypt_stat_vals(
	काष्ठा ecryptfs_crypt_stat *crypt_stat,
	काष्ठा ecryptfs_mount_crypt_stat *mount_crypt_stat)
अणु
	ecryptfs_copy_mount_wide_flags_to_inode_flags(crypt_stat,
						      mount_crypt_stat);
	ecryptfs_set_शेष_sizes(crypt_stat);
	म_नकल(crypt_stat->cipher, ECRYPTFS_DEFAULT_CIPHER);
	crypt_stat->key_size = ECRYPTFS_DEFAULT_KEY_BYTES;
	crypt_stat->flags &= ~(ECRYPTFS_KEY_VALID);
	crypt_stat->file_version = ECRYPTFS_खाता_VERSION;
	crypt_stat->mount_crypt_stat = mount_crypt_stat;
पूर्ण

/**
 * ecryptfs_new_file_context
 * @ecryptfs_inode: The eCryptfs inode
 *
 * If the crypto context क्रम the file has not yet been established,
 * this is where we करो that.  Establishing a new crypto context
 * involves the following decisions:
 *  - What cipher to use?
 *  - What set of authentication tokens to use?
 * Here we just worry about getting enough inक्रमmation पूर्णांकo the
 * authentication tokens so that we know that they are available.
 * We associate the available authentication tokens with the new file
 * via the set of signatures in the crypt_stat काष्ठा.  Later, when
 * the headers are actually written out, we may again defer to
 * userspace to perक्रमm the encryption of the session key; क्रम the
 * क्रमeseeable future, this will be the हाल with खुला key packets.
 *
 * Returns zero on success; non-zero otherwise
 */
पूर्णांक ecryptfs_new_file_context(काष्ठा inode *ecryptfs_inode)
अणु
	काष्ठा ecryptfs_crypt_stat *crypt_stat =
	    &ecryptfs_inode_to_निजी(ecryptfs_inode)->crypt_stat;
	काष्ठा ecryptfs_mount_crypt_stat *mount_crypt_stat =
	    &ecryptfs_superblock_to_निजी(
		    ecryptfs_inode->i_sb)->mount_crypt_stat;
	पूर्णांक cipher_name_len;
	पूर्णांक rc = 0;

	ecryptfs_set_शेष_crypt_stat_vals(crypt_stat, mount_crypt_stat);
	crypt_stat->flags |= (ECRYPTFS_ENCRYPTED | ECRYPTFS_KEY_VALID);
	ecryptfs_copy_mount_wide_flags_to_inode_flags(crypt_stat,
						      mount_crypt_stat);
	rc = ecryptfs_copy_mount_wide_sigs_to_inode_sigs(crypt_stat,
							 mount_crypt_stat);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "Error attempting to copy mount-wide key sigs "
		       "to the inode key sigs; rc = [%d]\n", rc);
		जाओ out;
	पूर्ण
	cipher_name_len =
		म_माप(mount_crypt_stat->global_शेष_cipher_name);
	स_नकल(crypt_stat->cipher,
	       mount_crypt_stat->global_शेष_cipher_name,
	       cipher_name_len);
	crypt_stat->cipher[cipher_name_len] = '\0';
	crypt_stat->key_size =
		mount_crypt_stat->global_शेष_cipher_key_size;
	ecryptfs_generate_new_key(crypt_stat);
	rc = ecryptfs_init_crypt_ctx(crypt_stat);
	अगर (rc)
		ecryptfs_prपूर्णांकk(KERN_ERR, "Error initializing cryptographic "
				"context for cipher [%s]: rc = [%d]\n",
				crypt_stat->cipher, rc);
out:
	वापस rc;
पूर्ण

/**
 * ecryptfs_validate_marker - check क्रम the ecryptfs marker
 * @data: The data block in which to check
 *
 * Returns zero अगर marker found; -EINVAL अगर not found
 */
अटल पूर्णांक ecryptfs_validate_marker(अक्षर *data)
अणु
	u32 m_1, m_2;

	m_1 = get_unaligned_be32(data);
	m_2 = get_unaligned_be32(data + 4);
	अगर ((m_1 ^ MAGIC_ECRYPTFS_MARKER) == m_2)
		वापस 0;
	ecryptfs_prपूर्णांकk(KERN_DEBUG, "m_1 = [0x%.8x]; m_2 = [0x%.8x]; "
			"MAGIC_ECRYPTFS_MARKER = [0x%.8x]\n", m_1, m_2,
			MAGIC_ECRYPTFS_MARKER);
	ecryptfs_prपूर्णांकk(KERN_DEBUG, "(m_1 ^ MAGIC_ECRYPTFS_MARKER) = "
			"[0x%.8x]\n", (m_1 ^ MAGIC_ECRYPTFS_MARKER));
	वापस -EINVAL;
पूर्ण

काष्ठा ecryptfs_flag_map_elem अणु
	u32 file_flag;
	u32 local_flag;
पूर्ण;

/* Add support क्रम additional flags by adding elements here. */
अटल काष्ठा ecryptfs_flag_map_elem ecryptfs_flag_map[] = अणु
	अणु0x00000001, ECRYPTFS_ENABLE_HMACपूर्ण,
	अणु0x00000002, ECRYPTFS_ENCRYPTEDपूर्ण,
	अणु0x00000004, ECRYPTFS_METADATA_IN_XATTRपूर्ण,
	अणु0x00000008, ECRYPTFS_ENCRYPT_खाताNAMESपूर्ण
पूर्ण;

/**
 * ecryptfs_process_flags
 * @crypt_stat: The cryptographic context
 * @page_virt: Source data to be parsed
 * @bytes_पढ़ो: Updated with the number of bytes पढ़ो
 */
अटल व्योम ecryptfs_process_flags(काष्ठा ecryptfs_crypt_stat *crypt_stat,
				  अक्षर *page_virt, पूर्णांक *bytes_पढ़ो)
अणु
	पूर्णांक i;
	u32 flags;

	flags = get_unaligned_be32(page_virt);
	क्रम (i = 0; i < ARRAY_SIZE(ecryptfs_flag_map); i++)
		अगर (flags & ecryptfs_flag_map[i].file_flag) अणु
			crypt_stat->flags |= ecryptfs_flag_map[i].local_flag;
		पूर्ण अन्यथा
			crypt_stat->flags &= ~(ecryptfs_flag_map[i].local_flag);
	/* Version is in top 8 bits of the 32-bit flag vector */
	crypt_stat->file_version = ((flags >> 24) & 0xFF);
	(*bytes_पढ़ो) = 4;
पूर्ण

/**
 * ग_लिखो_ecryptfs_marker
 * @page_virt: The poपूर्णांकer to in a page to begin writing the marker
 * @written: Number of bytes written
 *
 * Marker = 0x3c81b7f5
 */
अटल व्योम ग_लिखो_ecryptfs_marker(अक्षर *page_virt, माप_प्रकार *written)
अणु
	u32 m_1, m_2;

	get_अक्रमom_bytes(&m_1, (MAGIC_ECRYPTFS_MARKER_SIZE_BYTES / 2));
	m_2 = (m_1 ^ MAGIC_ECRYPTFS_MARKER);
	put_unaligned_be32(m_1, page_virt);
	page_virt += (MAGIC_ECRYPTFS_MARKER_SIZE_BYTES / 2);
	put_unaligned_be32(m_2, page_virt);
	(*written) = MAGIC_ECRYPTFS_MARKER_SIZE_BYTES;
पूर्ण

व्योम ecryptfs_ग_लिखो_crypt_stat_flags(अक्षर *page_virt,
				     काष्ठा ecryptfs_crypt_stat *crypt_stat,
				     माप_प्रकार *written)
अणु
	u32 flags = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ecryptfs_flag_map); i++)
		अगर (crypt_stat->flags & ecryptfs_flag_map[i].local_flag)
			flags |= ecryptfs_flag_map[i].file_flag;
	/* Version is in top 8 bits of the 32-bit flag vector */
	flags |= ((((u8)crypt_stat->file_version) << 24) & 0xFF000000);
	put_unaligned_be32(flags, page_virt);
	(*written) = 4;
पूर्ण

काष्ठा ecryptfs_cipher_code_str_map_elem अणु
	अक्षर cipher_str[16];
	u8 cipher_code;
पूर्ण;

/* Add support क्रम additional ciphers by adding elements here. The
 * cipher_code is whatever OpenPGP applications use to identअगरy the
 * ciphers. List in order of probability. */
अटल काष्ठा ecryptfs_cipher_code_str_map_elem
ecryptfs_cipher_code_str_map[] = अणु
	अणु"aes",RFC2440_CIPHER_AES_128 पूर्ण,
	अणु"blowfish", RFC2440_CIPHER_BLOWFISHपूर्ण,
	अणु"des3_ede", RFC2440_CIPHER_DES3_EDEपूर्ण,
	अणु"cast5", RFC2440_CIPHER_CAST_5पूर्ण,
	अणु"twofish", RFC2440_CIPHER_TWOFISHपूर्ण,
	अणु"cast6", RFC2440_CIPHER_CAST_6पूर्ण,
	अणु"aes", RFC2440_CIPHER_AES_192पूर्ण,
	अणु"aes", RFC2440_CIPHER_AES_256पूर्ण
पूर्ण;

/**
 * ecryptfs_code_क्रम_cipher_string
 * @cipher_name: The string alias क्रम the cipher
 * @key_bytes: Length of key in bytes; used क्रम AES code selection
 *
 * Returns zero on no match, or the cipher code on match
 */
u8 ecryptfs_code_क्रम_cipher_string(अक्षर *cipher_name, माप_प्रकार key_bytes)
अणु
	पूर्णांक i;
	u8 code = 0;
	काष्ठा ecryptfs_cipher_code_str_map_elem *map =
		ecryptfs_cipher_code_str_map;

	अगर (म_भेद(cipher_name, "aes") == 0) अणु
		चयन (key_bytes) अणु
		हाल 16:
			code = RFC2440_CIPHER_AES_128;
			अवरोध;
		हाल 24:
			code = RFC2440_CIPHER_AES_192;
			अवरोध;
		हाल 32:
			code = RFC2440_CIPHER_AES_256;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < ARRAY_SIZE(ecryptfs_cipher_code_str_map); i++)
			अगर (म_भेद(cipher_name, map[i].cipher_str) == 0) अणु
				code = map[i].cipher_code;
				अवरोध;
			पूर्ण
	पूर्ण
	वापस code;
पूर्ण

/**
 * ecryptfs_cipher_code_to_string
 * @str: Destination to ग_लिखो out the cipher name
 * @cipher_code: The code to convert to cipher name string
 *
 * Returns zero on success
 */
पूर्णांक ecryptfs_cipher_code_to_string(अक्षर *str, u8 cipher_code)
अणु
	पूर्णांक rc = 0;
	पूर्णांक i;

	str[0] = '\0';
	क्रम (i = 0; i < ARRAY_SIZE(ecryptfs_cipher_code_str_map); i++)
		अगर (cipher_code == ecryptfs_cipher_code_str_map[i].cipher_code)
			म_नकल(str, ecryptfs_cipher_code_str_map[i].cipher_str);
	अगर (str[0] == '\0') अणु
		ecryptfs_prपूर्णांकk(KERN_WARNING, "Cipher code not recognized: "
				"[%d]\n", cipher_code);
		rc = -EINVAL;
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक ecryptfs_पढ़ो_and_validate_header_region(काष्ठा inode *inode)
अणु
	u8 file_size[ECRYPTFS_SIZE_AND_MARKER_BYTES];
	u8 *marker = file_size + ECRYPTFS_खाता_SIZE_BYTES;
	पूर्णांक rc;

	rc = ecryptfs_पढ़ो_lower(file_size, 0, ECRYPTFS_SIZE_AND_MARKER_BYTES,
				 inode);
	अगर (rc < 0)
		वापस rc;
	अन्यथा अगर (rc < ECRYPTFS_SIZE_AND_MARKER_BYTES)
		वापस -EINVAL;
	rc = ecryptfs_validate_marker(marker);
	अगर (!rc)
		ecryptfs_i_size_init(file_size, inode);
	वापस rc;
पूर्ण

व्योम
ecryptfs_ग_लिखो_header_metadata(अक्षर *virt,
			       काष्ठा ecryptfs_crypt_stat *crypt_stat,
			       माप_प्रकार *written)
अणु
	u32 header_extent_size;
	u16 num_header_extents_at_front;

	header_extent_size = (u32)crypt_stat->extent_size;
	num_header_extents_at_front =
		(u16)(crypt_stat->metadata_size / crypt_stat->extent_size);
	put_unaligned_be32(header_extent_size, virt);
	virt += 4;
	put_unaligned_be16(num_header_extents_at_front, virt);
	(*written) = 6;
पूर्ण

काष्ठा kmem_cache *ecryptfs_header_cache;

/**
 * ecryptfs_ग_लिखो_headers_virt
 * @page_virt: The भव address to ग_लिखो the headers to
 * @max: The size of memory allocated at page_virt
 * @size: Set to the number of bytes written by this function
 * @crypt_stat: The cryptographic context
 * @ecryptfs_dentry: The eCryptfs dentry
 *
 * Format version: 1
 *
 *   Header Extent:
 *     Octets 0-7:        Unencrypted file size (big-endian)
 *     Octets 8-15:       eCryptfs special marker
 *     Octets 16-19:      Flags
 *      Octet 16:         File क्रमmat version number (between 0 and 255)
 *      Octets 17-18:     Reserved
 *      Octet 19:         Bit 1 (lsb): Reserved
 *                        Bit 2: Encrypted?
 *                        Bits 3-8: Reserved
 *     Octets 20-23:      Header extent size (big-endian)
 *     Octets 24-25:      Number of header extents at front of file
 *                        (big-endian)
 *     Octet  26:         Begin RFC 2440 authentication token packet set
 *   Data Extent 0:
 *     Lower data (CBC encrypted)
 *   Data Extent 1:
 *     Lower data (CBC encrypted)
 *   ...
 *
 * Returns zero on success
 */
अटल पूर्णांक ecryptfs_ग_लिखो_headers_virt(अक्षर *page_virt, माप_प्रकार max,
				       माप_प्रकार *size,
				       काष्ठा ecryptfs_crypt_stat *crypt_stat,
				       काष्ठा dentry *ecryptfs_dentry)
अणु
	पूर्णांक rc;
	माप_प्रकार written;
	माप_प्रकार offset;

	offset = ECRYPTFS_खाता_SIZE_BYTES;
	ग_लिखो_ecryptfs_marker((page_virt + offset), &written);
	offset += written;
	ecryptfs_ग_लिखो_crypt_stat_flags((page_virt + offset), crypt_stat,
					&written);
	offset += written;
	ecryptfs_ग_लिखो_header_metadata((page_virt + offset), crypt_stat,
				       &written);
	offset += written;
	rc = ecryptfs_generate_key_packet_set((page_virt + offset), crypt_stat,
					      ecryptfs_dentry, &written,
					      max - offset);
	अगर (rc)
		ecryptfs_prपूर्णांकk(KERN_WARNING, "Error generating key packet "
				"set; rc = [%d]\n", rc);
	अगर (size) अणु
		offset += written;
		*size = offset;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक
ecryptfs_ग_लिखो_metadata_to_contents(काष्ठा inode *ecryptfs_inode,
				    अक्षर *virt, माप_प्रकार virt_len)
अणु
	पूर्णांक rc;

	rc = ecryptfs_ग_लिखो_lower(ecryptfs_inode, virt,
				  0, virt_len);
	अगर (rc < 0)
		prपूर्णांकk(KERN_ERR "%s: Error attempting to write header "
		       "information to lower file; rc = [%d]\n", __func__, rc);
	अन्यथा
		rc = 0;
	वापस rc;
पूर्ण

अटल पूर्णांक
ecryptfs_ग_लिखो_metadata_to_xattr(काष्ठा dentry *ecryptfs_dentry,
				 काष्ठा inode *ecryptfs_inode,
				 अक्षर *page_virt, माप_प्रकार size)
अणु
	पूर्णांक rc;
	काष्ठा dentry *lower_dentry = ecryptfs_dentry_to_lower(ecryptfs_dentry);
	काष्ठा inode *lower_inode = d_inode(lower_dentry);

	अगर (!(lower_inode->i_opflags & IOP_XATTR)) अणु
		rc = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	inode_lock(lower_inode);
	rc = __vfs_setxattr(&init_user_ns, lower_dentry, lower_inode,
			    ECRYPTFS_XATTR_NAME, page_virt, size, 0);
	अगर (!rc && ecryptfs_inode)
		fsstack_copy_attr_all(ecryptfs_inode, lower_inode);
	inode_unlock(lower_inode);
out:
	वापस rc;
पूर्ण

अटल अचिन्हित दीर्घ ecryptfs_get_zeroed_pages(gfp_t gfp_mask,
					       अचिन्हित पूर्णांक order)
अणु
	काष्ठा page *page;

	page = alloc_pages(gfp_mask | __GFP_ZERO, order);
	अगर (page)
		वापस (अचिन्हित दीर्घ) page_address(page);
	वापस 0;
पूर्ण

/**
 * ecryptfs_ग_लिखो_metadata
 * @ecryptfs_dentry: The eCryptfs dentry, which should be negative
 * @ecryptfs_inode: The newly created eCryptfs inode
 *
 * Write the file headers out.  This will likely involve a userspace
 * callout, in which the session key is encrypted with one or more
 * खुला keys and/or the passphrase necessary to करो the encryption is
 * retrieved via a prompt.  Exactly what happens at this poपूर्णांक should
 * be policy-dependent.
 *
 * Returns zero on success; non-zero on error
 */
पूर्णांक ecryptfs_ग_लिखो_metadata(काष्ठा dentry *ecryptfs_dentry,
			    काष्ठा inode *ecryptfs_inode)
अणु
	काष्ठा ecryptfs_crypt_stat *crypt_stat =
		&ecryptfs_inode_to_निजी(ecryptfs_inode)->crypt_stat;
	अचिन्हित पूर्णांक order;
	अक्षर *virt;
	माप_प्रकार virt_len;
	माप_प्रकार size = 0;
	पूर्णांक rc = 0;

	अगर (likely(crypt_stat->flags & ECRYPTFS_ENCRYPTED)) अणु
		अगर (!(crypt_stat->flags & ECRYPTFS_KEY_VALID)) अणु
			prपूर्णांकk(KERN_ERR "Key is invalid; bailing out\n");
			rc = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_WARNING "%s: Encrypted flag not set\n",
		       __func__);
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	virt_len = crypt_stat->metadata_size;
	order = get_order(virt_len);
	/* Released in this function */
	virt = (अक्षर *)ecryptfs_get_zeroed_pages(GFP_KERNEL, order);
	अगर (!virt) अणु
		prपूर्णांकk(KERN_ERR "%s: Out of memory\n", __func__);
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	/* Zeroed page ensures the in-header unencrypted i_size is set to 0 */
	rc = ecryptfs_ग_लिखो_headers_virt(virt, virt_len, &size, crypt_stat,
					 ecryptfs_dentry);
	अगर (unlikely(rc)) अणु
		prपूर्णांकk(KERN_ERR "%s: Error whilst writing headers; rc = [%d]\n",
		       __func__, rc);
		जाओ out_मुक्त;
	पूर्ण
	अगर (crypt_stat->flags & ECRYPTFS_METADATA_IN_XATTR)
		rc = ecryptfs_ग_लिखो_metadata_to_xattr(ecryptfs_dentry, ecryptfs_inode,
						      virt, size);
	अन्यथा
		rc = ecryptfs_ग_लिखो_metadata_to_contents(ecryptfs_inode, virt,
							 virt_len);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "%s: Error writing metadata out to lower file; "
		       "rc = [%d]\n", __func__, rc);
		जाओ out_मुक्त;
	पूर्ण
out_मुक्त:
	मुक्त_pages((अचिन्हित दीर्घ)virt, order);
out:
	वापस rc;
पूर्ण

#घोषणा ECRYPTFS_DONT_VALIDATE_HEADER_SIZE 0
#घोषणा ECRYPTFS_VALIDATE_HEADER_SIZE 1
अटल पूर्णांक parse_header_metadata(काष्ठा ecryptfs_crypt_stat *crypt_stat,
				 अक्षर *virt, पूर्णांक *bytes_पढ़ो,
				 पूर्णांक validate_header_size)
अणु
	पूर्णांक rc = 0;
	u32 header_extent_size;
	u16 num_header_extents_at_front;

	header_extent_size = get_unaligned_be32(virt);
	virt += माप(__be32);
	num_header_extents_at_front = get_unaligned_be16(virt);
	crypt_stat->metadata_size = (((माप_प्रकार)num_header_extents_at_front
				     * (माप_प्रकार)header_extent_size));
	(*bytes_पढ़ो) = (माप(__be32) + माप(__be16));
	अगर ((validate_header_size == ECRYPTFS_VALIDATE_HEADER_SIZE)
	    && (crypt_stat->metadata_size
		< ECRYPTFS_MINIMUM_HEADER_EXTENT_SIZE)) अणु
		rc = -EINVAL;
		prपूर्णांकk(KERN_WARNING "Invalid header size: [%zd]\n",
		       crypt_stat->metadata_size);
	पूर्ण
	वापस rc;
पूर्ण

/**
 * set_शेष_header_data
 * @crypt_stat: The cryptographic context
 *
 * For version 0 file क्रमmat; this function is only क्रम backwards
 * compatibility क्रम files created with the prior versions of
 * eCryptfs.
 */
अटल व्योम set_शेष_header_data(काष्ठा ecryptfs_crypt_stat *crypt_stat)
अणु
	crypt_stat->metadata_size = ECRYPTFS_MINIMUM_HEADER_EXTENT_SIZE;
पूर्ण

व्योम ecryptfs_i_size_init(स्थिर अक्षर *page_virt, काष्ठा inode *inode)
अणु
	काष्ठा ecryptfs_mount_crypt_stat *mount_crypt_stat;
	काष्ठा ecryptfs_crypt_stat *crypt_stat;
	u64 file_size;

	crypt_stat = &ecryptfs_inode_to_निजी(inode)->crypt_stat;
	mount_crypt_stat =
		&ecryptfs_superblock_to_निजी(inode->i_sb)->mount_crypt_stat;
	अगर (mount_crypt_stat->flags & ECRYPTFS_ENCRYPTED_VIEW_ENABLED) अणु
		file_size = i_size_पढ़ो(ecryptfs_inode_to_lower(inode));
		अगर (crypt_stat->flags & ECRYPTFS_METADATA_IN_XATTR)
			file_size += crypt_stat->metadata_size;
	पूर्ण अन्यथा
		file_size = get_unaligned_be64(page_virt);
	i_size_ग_लिखो(inode, (loff_t)file_size);
	crypt_stat->flags |= ECRYPTFS_I_SIZE_INITIALIZED;
पूर्ण

/**
 * ecryptfs_पढ़ो_headers_virt
 * @page_virt: The भव address पूर्णांकo which to पढ़ो the headers
 * @crypt_stat: The cryptographic context
 * @ecryptfs_dentry: The eCryptfs dentry
 * @validate_header_size: Whether to validate the header size जबतक पढ़ोing
 *
 * Read/parse the header data. The header क्रमmat is detailed in the
 * comment block क्रम the ecryptfs_ग_लिखो_headers_virt() function.
 *
 * Returns zero on success
 */
अटल पूर्णांक ecryptfs_पढ़ो_headers_virt(अक्षर *page_virt,
				      काष्ठा ecryptfs_crypt_stat *crypt_stat,
				      काष्ठा dentry *ecryptfs_dentry,
				      पूर्णांक validate_header_size)
अणु
	पूर्णांक rc = 0;
	पूर्णांक offset;
	पूर्णांक bytes_पढ़ो;

	ecryptfs_set_शेष_sizes(crypt_stat);
	crypt_stat->mount_crypt_stat = &ecryptfs_superblock_to_निजी(
		ecryptfs_dentry->d_sb)->mount_crypt_stat;
	offset = ECRYPTFS_खाता_SIZE_BYTES;
	rc = ecryptfs_validate_marker(page_virt + offset);
	अगर (rc)
		जाओ out;
	अगर (!(crypt_stat->flags & ECRYPTFS_I_SIZE_INITIALIZED))
		ecryptfs_i_size_init(page_virt, d_inode(ecryptfs_dentry));
	offset += MAGIC_ECRYPTFS_MARKER_SIZE_BYTES;
	ecryptfs_process_flags(crypt_stat, (page_virt + offset), &bytes_पढ़ो);
	अगर (crypt_stat->file_version > ECRYPTFS_SUPPORTED_खाता_VERSION) अणु
		ecryptfs_prपूर्णांकk(KERN_WARNING, "File version is [%d]; only "
				"file version [%d] is supported by this "
				"version of eCryptfs\n",
				crypt_stat->file_version,
				ECRYPTFS_SUPPORTED_खाता_VERSION);
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	offset += bytes_पढ़ो;
	अगर (crypt_stat->file_version >= 1) अणु
		rc = parse_header_metadata(crypt_stat, (page_virt + offset),
					   &bytes_पढ़ो, validate_header_size);
		अगर (rc) अणु
			ecryptfs_prपूर्णांकk(KERN_WARNING, "Error reading header "
					"metadata; rc = [%d]\n", rc);
		पूर्ण
		offset += bytes_पढ़ो;
	पूर्ण अन्यथा
		set_शेष_header_data(crypt_stat);
	rc = ecryptfs_parse_packet_set(crypt_stat, (page_virt + offset),
				       ecryptfs_dentry);
out:
	वापस rc;
पूर्ण

/**
 * ecryptfs_पढ़ो_xattr_region
 * @page_virt: The vitual address पूर्णांकo which to पढ़ो the xattr data
 * @ecryptfs_inode: The eCryptfs inode
 *
 * Attempts to पढ़ो the crypto metadata from the extended attribute
 * region of the lower file.
 *
 * Returns zero on success; non-zero on error
 */
पूर्णांक ecryptfs_पढ़ो_xattr_region(अक्षर *page_virt, काष्ठा inode *ecryptfs_inode)
अणु
	काष्ठा dentry *lower_dentry =
		ecryptfs_inode_to_निजी(ecryptfs_inode)->lower_file->f_path.dentry;
	sमाप_प्रकार size;
	पूर्णांक rc = 0;

	size = ecryptfs_getxattr_lower(lower_dentry,
				       ecryptfs_inode_to_lower(ecryptfs_inode),
				       ECRYPTFS_XATTR_NAME,
				       page_virt, ECRYPTFS_DEFAULT_EXTENT_SIZE);
	अगर (size < 0) अणु
		अगर (unlikely(ecryptfs_verbosity > 0))
			prपूर्णांकk(KERN_INFO "Error attempting to read the [%s] "
			       "xattr from the lower file; return value = "
			       "[%zd]\n", ECRYPTFS_XATTR_NAME, size);
		rc = -EINVAL;
		जाओ out;
	पूर्ण
out:
	वापस rc;
पूर्ण

पूर्णांक ecryptfs_पढ़ो_and_validate_xattr_region(काष्ठा dentry *dentry,
					    काष्ठा inode *inode)
अणु
	u8 file_size[ECRYPTFS_SIZE_AND_MARKER_BYTES];
	u8 *marker = file_size + ECRYPTFS_खाता_SIZE_BYTES;
	पूर्णांक rc;

	rc = ecryptfs_getxattr_lower(ecryptfs_dentry_to_lower(dentry),
				     ecryptfs_inode_to_lower(inode),
				     ECRYPTFS_XATTR_NAME, file_size,
				     ECRYPTFS_SIZE_AND_MARKER_BYTES);
	अगर (rc < 0)
		वापस rc;
	अन्यथा अगर (rc < ECRYPTFS_SIZE_AND_MARKER_BYTES)
		वापस -EINVAL;
	rc = ecryptfs_validate_marker(marker);
	अगर (!rc)
		ecryptfs_i_size_init(file_size, inode);
	वापस rc;
पूर्ण

/*
 * ecryptfs_पढ़ो_metadata
 *
 * Common entry poपूर्णांक क्रम पढ़ोing file metadata. From here, we could
 * retrieve the header inक्रमmation from the header region of the file,
 * the xattr region of the file, or some other repository that is
 * stored separately from the file itself. The current implementation
 * supports retrieving the metadata inक्रमmation from the file contents
 * and from the xattr region.
 *
 * Returns zero अगर valid headers found and parsed; non-zero otherwise
 */
पूर्णांक ecryptfs_पढ़ो_metadata(काष्ठा dentry *ecryptfs_dentry)
अणु
	पूर्णांक rc;
	अक्षर *page_virt;
	काष्ठा inode *ecryptfs_inode = d_inode(ecryptfs_dentry);
	काष्ठा ecryptfs_crypt_stat *crypt_stat =
	    &ecryptfs_inode_to_निजी(ecryptfs_inode)->crypt_stat;
	काष्ठा ecryptfs_mount_crypt_stat *mount_crypt_stat =
		&ecryptfs_superblock_to_निजी(
			ecryptfs_dentry->d_sb)->mount_crypt_stat;

	ecryptfs_copy_mount_wide_flags_to_inode_flags(crypt_stat,
						      mount_crypt_stat);
	/* Read the first page from the underlying file */
	page_virt = kmem_cache_alloc(ecryptfs_header_cache, GFP_USER);
	अगर (!page_virt) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	rc = ecryptfs_पढ़ो_lower(page_virt, 0, crypt_stat->extent_size,
				 ecryptfs_inode);
	अगर (rc >= 0)
		rc = ecryptfs_पढ़ो_headers_virt(page_virt, crypt_stat,
						ecryptfs_dentry,
						ECRYPTFS_VALIDATE_HEADER_SIZE);
	अगर (rc) अणु
		/* metadata is not in the file header, so try xattrs */
		स_रखो(page_virt, 0, PAGE_SIZE);
		rc = ecryptfs_पढ़ो_xattr_region(page_virt, ecryptfs_inode);
		अगर (rc) अणु
			prपूर्णांकk(KERN_DEBUG "Valid eCryptfs headers not found in "
			       "file header region or xattr region, inode %lu\n",
				ecryptfs_inode->i_ino);
			rc = -EINVAL;
			जाओ out;
		पूर्ण
		rc = ecryptfs_पढ़ो_headers_virt(page_virt, crypt_stat,
						ecryptfs_dentry,
						ECRYPTFS_DONT_VALIDATE_HEADER_SIZE);
		अगर (rc) अणु
			prपूर्णांकk(KERN_DEBUG "Valid eCryptfs headers not found in "
			       "file xattr region either, inode %lu\n",
				ecryptfs_inode->i_ino);
			rc = -EINVAL;
		पूर्ण
		अगर (crypt_stat->mount_crypt_stat->flags
		    & ECRYPTFS_XATTR_METADATA_ENABLED) अणु
			crypt_stat->flags |= ECRYPTFS_METADATA_IN_XATTR;
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_WARNING "Attempt to access file with "
			       "crypto metadata only in the extended attribute "
			       "region, but eCryptfs was mounted without "
			       "xattr support enabled. eCryptfs will not treat "
			       "this like an encrypted file, inode %lu\n",
				ecryptfs_inode->i_ino);
			rc = -EINVAL;
		पूर्ण
	पूर्ण
out:
	अगर (page_virt) अणु
		स_रखो(page_virt, 0, PAGE_SIZE);
		kmem_cache_मुक्त(ecryptfs_header_cache, page_virt);
	पूर्ण
	वापस rc;
पूर्ण

/*
 * ecryptfs_encrypt_filename - encrypt filename
 *
 * CBC-encrypts the filename. We करो not want to encrypt the same
 * filename with the same key and IV, which may happen with hard
 * links, so we prepend अक्रमom bits to each filename.
 *
 * Returns zero on success; non-zero otherwise
 */
अटल पूर्णांक
ecryptfs_encrypt_filename(काष्ठा ecryptfs_filename *filename,
			  काष्ठा ecryptfs_mount_crypt_stat *mount_crypt_stat)
अणु
	पूर्णांक rc = 0;

	filename->encrypted_filename = शून्य;
	filename->encrypted_filename_size = 0;
	अगर (mount_crypt_stat && (mount_crypt_stat->flags
				     & ECRYPTFS_GLOBAL_ENCFN_USE_MOUNT_FNEK)) अणु
		माप_प्रकार packet_size;
		माप_प्रकार reमुख्यing_bytes;

		rc = ecryptfs_ग_लिखो_tag_70_packet(
			शून्य, शून्य,
			&filename->encrypted_filename_size,
			mount_crypt_stat, शून्य,
			filename->filename_size);
		अगर (rc) अणु
			prपूर्णांकk(KERN_ERR "%s: Error attempting to get packet "
			       "size for tag 72; rc = [%d]\n", __func__,
			       rc);
			filename->encrypted_filename_size = 0;
			जाओ out;
		पूर्ण
		filename->encrypted_filename =
			kदो_स्मृति(filename->encrypted_filename_size, GFP_KERNEL);
		अगर (!filename->encrypted_filename) अणु
			rc = -ENOMEM;
			जाओ out;
		पूर्ण
		reमुख्यing_bytes = filename->encrypted_filename_size;
		rc = ecryptfs_ग_लिखो_tag_70_packet(filename->encrypted_filename,
						  &reमुख्यing_bytes,
						  &packet_size,
						  mount_crypt_stat,
						  filename->filename,
						  filename->filename_size);
		अगर (rc) अणु
			prपूर्णांकk(KERN_ERR "%s: Error attempting to generate "
			       "tag 70 packet; rc = [%d]\n", __func__,
			       rc);
			kमुक्त(filename->encrypted_filename);
			filename->encrypted_filename = शून्य;
			filename->encrypted_filename_size = 0;
			जाओ out;
		पूर्ण
		filename->encrypted_filename_size = packet_size;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "%s: No support for requested filename "
		       "encryption method in this release\n", __func__);
		rc = -EOPNOTSUPP;
		जाओ out;
	पूर्ण
out:
	वापस rc;
पूर्ण

अटल पूर्णांक ecryptfs_copy_filename(अक्षर **copied_name, माप_प्रकार *copied_name_size,
				  स्थिर अक्षर *name, माप_प्रकार name_size)
अणु
	पूर्णांक rc = 0;

	(*copied_name) = kदो_स्मृति((name_size + 1), GFP_KERNEL);
	अगर (!(*copied_name)) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	स_नकल((व्योम *)(*copied_name), (व्योम *)name, name_size);
	(*copied_name)[(name_size)] = '\0';	/* Only क्रम convenience
						 * in prपूर्णांकing out the
						 * string in debug
						 * messages */
	(*copied_name_size) = name_size;
out:
	वापस rc;
पूर्ण

/**
 * ecryptfs_process_key_cipher - Perक्रमm key cipher initialization.
 * @key_tfm: Crypto context क्रम key material, set by this function
 * @cipher_name: Name of the cipher
 * @key_size: Size of the key in bytes
 *
 * Returns zero on success. Any crypto_tfm काष्ठाs allocated here
 * should be released by other functions, such as on a superblock put
 * event, regardless of whether this function succeeds क्रम fails.
 */
अटल पूर्णांक
ecryptfs_process_key_cipher(काष्ठा crypto_skcipher **key_tfm,
			    अक्षर *cipher_name, माप_प्रकार *key_size)
अणु
	अक्षर dummy_key[ECRYPTFS_MAX_KEY_BYTES];
	अक्षर *full_alg_name = शून्य;
	पूर्णांक rc;

	*key_tfm = शून्य;
	अगर (*key_size > ECRYPTFS_MAX_KEY_BYTES) अणु
		rc = -EINVAL;
		prपूर्णांकk(KERN_ERR "Requested key size is [%zd] bytes; maximum "
		      "allowable is [%d]\n", *key_size, ECRYPTFS_MAX_KEY_BYTES);
		जाओ out;
	पूर्ण
	rc = ecryptfs_crypto_api_algअगरy_cipher_name(&full_alg_name, cipher_name,
						    "ecb");
	अगर (rc)
		जाओ out;
	*key_tfm = crypto_alloc_skcipher(full_alg_name, 0, CRYPTO_ALG_ASYNC);
	अगर (IS_ERR(*key_tfm)) अणु
		rc = PTR_ERR(*key_tfm);
		prपूर्णांकk(KERN_ERR "Unable to allocate crypto cipher with name "
		       "[%s]; rc = [%d]\n", full_alg_name, rc);
		जाओ out;
	पूर्ण
	crypto_skcipher_set_flags(*key_tfm, CRYPTO_TFM_REQ_FORBID_WEAK_KEYS);
	अगर (*key_size == 0)
		*key_size = crypto_skcipher_max_keysize(*key_tfm);
	get_अक्रमom_bytes(dummy_key, *key_size);
	rc = crypto_skcipher_setkey(*key_tfm, dummy_key, *key_size);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "Error attempting to set key of size [%zd] for "
		       "cipher [%s]; rc = [%d]\n", *key_size, full_alg_name,
		       rc);
		rc = -EINVAL;
		जाओ out;
	पूर्ण
out:
	kमुक्त(full_alg_name);
	वापस rc;
पूर्ण

काष्ठा kmem_cache *ecryptfs_key_tfm_cache;
अटल काष्ठा list_head key_tfm_list;
DEFINE_MUTEX(key_tfm_list_mutex);

पूर्णांक __init ecryptfs_init_crypto(व्योम)
अणु
	INIT_LIST_HEAD(&key_tfm_list);
	वापस 0;
पूर्ण

/**
 * ecryptfs_destroy_crypto - मुक्त all cached key_tfms on key_tfm_list
 *
 * Called only at module unload समय
 */
पूर्णांक ecryptfs_destroy_crypto(व्योम)
अणु
	काष्ठा ecryptfs_key_tfm *key_tfm, *key_tfm_पंचांगp;

	mutex_lock(&key_tfm_list_mutex);
	list_क्रम_each_entry_safe(key_tfm, key_tfm_पंचांगp, &key_tfm_list,
				 key_tfm_list) अणु
		list_del(&key_tfm->key_tfm_list);
		crypto_मुक्त_skcipher(key_tfm->key_tfm);
		kmem_cache_मुक्त(ecryptfs_key_tfm_cache, key_tfm);
	पूर्ण
	mutex_unlock(&key_tfm_list_mutex);
	वापस 0;
पूर्ण

पूर्णांक
ecryptfs_add_new_key_tfm(काष्ठा ecryptfs_key_tfm **key_tfm, अक्षर *cipher_name,
			 माप_प्रकार key_size)
अणु
	काष्ठा ecryptfs_key_tfm *पंचांगp_tfm;
	पूर्णांक rc = 0;

	BUG_ON(!mutex_is_locked(&key_tfm_list_mutex));

	पंचांगp_tfm = kmem_cache_alloc(ecryptfs_key_tfm_cache, GFP_KERNEL);
	अगर (key_tfm)
		(*key_tfm) = पंचांगp_tfm;
	अगर (!पंचांगp_tfm) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	mutex_init(&पंचांगp_tfm->key_tfm_mutex);
	म_नकलन(पंचांगp_tfm->cipher_name, cipher_name,
		ECRYPTFS_MAX_CIPHER_NAME_SIZE);
	पंचांगp_tfm->cipher_name[ECRYPTFS_MAX_CIPHER_NAME_SIZE] = '\0';
	पंचांगp_tfm->key_size = key_size;
	rc = ecryptfs_process_key_cipher(&पंचांगp_tfm->key_tfm,
					 पंचांगp_tfm->cipher_name,
					 &पंचांगp_tfm->key_size);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "Error attempting to initialize key TFM "
		       "cipher with name = [%s]; rc = [%d]\n",
		       पंचांगp_tfm->cipher_name, rc);
		kmem_cache_मुक्त(ecryptfs_key_tfm_cache, पंचांगp_tfm);
		अगर (key_tfm)
			(*key_tfm) = शून्य;
		जाओ out;
	पूर्ण
	list_add(&पंचांगp_tfm->key_tfm_list, &key_tfm_list);
out:
	वापस rc;
पूर्ण

/**
 * ecryptfs_tfm_exists - Search क्रम existing tfm क्रम cipher_name.
 * @cipher_name: the name of the cipher to search क्रम
 * @key_tfm: set to corresponding tfm अगर found
 *
 * Searches क्रम cached key_tfm matching @cipher_name
 * Must be called with &key_tfm_list_mutex held
 * Returns 1 अगर found, with @key_tfm set
 * Returns 0 अगर not found, with @key_tfm set to शून्य
 */
पूर्णांक ecryptfs_tfm_exists(अक्षर *cipher_name, काष्ठा ecryptfs_key_tfm **key_tfm)
अणु
	काष्ठा ecryptfs_key_tfm *पंचांगp_key_tfm;

	BUG_ON(!mutex_is_locked(&key_tfm_list_mutex));

	list_क्रम_each_entry(पंचांगp_key_tfm, &key_tfm_list, key_tfm_list) अणु
		अगर (म_भेद(पंचांगp_key_tfm->cipher_name, cipher_name) == 0) अणु
			अगर (key_tfm)
				(*key_tfm) = पंचांगp_key_tfm;
			वापस 1;
		पूर्ण
	पूर्ण
	अगर (key_tfm)
		(*key_tfm) = शून्य;
	वापस 0;
पूर्ण

/**
 * ecryptfs_get_tfm_and_mutex_क्रम_cipher_name
 *
 * @tfm: set to cached tfm found, or new tfm created
 * @tfm_mutex: set to mutex क्रम cached tfm found, or new tfm created
 * @cipher_name: the name of the cipher to search क्रम and/or add
 *
 * Sets poपूर्णांकers to @tfm & @tfm_mutex matching @cipher_name.
 * Searches क्रम cached item first, and creates new अगर not found.
 * Returns 0 on success, non-zero अगर adding new cipher failed
 */
पूर्णांक ecryptfs_get_tfm_and_mutex_क्रम_cipher_name(काष्ठा crypto_skcipher **tfm,
					       काष्ठा mutex **tfm_mutex,
					       अक्षर *cipher_name)
अणु
	काष्ठा ecryptfs_key_tfm *key_tfm;
	पूर्णांक rc = 0;

	(*tfm) = शून्य;
	(*tfm_mutex) = शून्य;

	mutex_lock(&key_tfm_list_mutex);
	अगर (!ecryptfs_tfm_exists(cipher_name, &key_tfm)) अणु
		rc = ecryptfs_add_new_key_tfm(&key_tfm, cipher_name, 0);
		अगर (rc) अणु
			prपूर्णांकk(KERN_ERR "Error adding new key_tfm to list; "
					"rc = [%d]\n", rc);
			जाओ out;
		पूर्ण
	पूर्ण
	(*tfm) = key_tfm->key_tfm;
	(*tfm_mutex) = &key_tfm->key_tfm_mutex;
out:
	mutex_unlock(&key_tfm_list_mutex);
	वापस rc;
पूर्ण

/* 64 अक्षरacters क्रमming a 6-bit target field */
अटल अचिन्हित अक्षर *portable_filename_अक्षरs = ("-.0123456789ABCD"
						 "EFGHIJKLMNOPQRST"
						 "UVWXYZabcdefghij"
						 "klmnopqrstuvwxyz");

/* We could either offset on every reverse map or just pad some 0x00's
 * at the front here */
अटल स्थिर अचिन्हित अक्षर filename_rev_map[256] = अणु
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 7 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 15 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 23 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 31 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 39 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, /* 47 */
	0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, /* 55 */
	0x0A, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 63 */
	0x00, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, /* 71 */
	0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, /* 79 */
	0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, /* 87 */
	0x23, 0x24, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, /* 95 */
	0x00, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, /* 103 */
	0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, /* 111 */
	0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, /* 119 */
	0x3D, 0x3E, 0x3F /* 123 - 255 initialized to 0x00 */
पूर्ण;

/**
 * ecryptfs_encode_क्रम_filename
 * @dst: Destination location क्रम encoded filename
 * @dst_size: Size of the encoded filename in bytes
 * @src: Source location क्रम the filename to encode
 * @src_size: Size of the source in bytes
 */
अटल व्योम ecryptfs_encode_क्रम_filename(अचिन्हित अक्षर *dst, माप_प्रकार *dst_size,
				  अचिन्हित अक्षर *src, माप_प्रकार src_size)
अणु
	माप_प्रकार num_blocks;
	माप_प्रकार block_num = 0;
	माप_प्रकार dst_offset = 0;
	अचिन्हित अक्षर last_block[3];

	अगर (src_size == 0) अणु
		(*dst_size) = 0;
		जाओ out;
	पूर्ण
	num_blocks = (src_size / 3);
	अगर ((src_size % 3) == 0) अणु
		स_नकल(last_block, (&src[src_size - 3]), 3);
	पूर्ण अन्यथा अणु
		num_blocks++;
		last_block[2] = 0x00;
		चयन (src_size % 3) अणु
		हाल 1:
			last_block[0] = src[src_size - 1];
			last_block[1] = 0x00;
			अवरोध;
		हाल 2:
			last_block[0] = src[src_size - 2];
			last_block[1] = src[src_size - 1];
		पूर्ण
	पूर्ण
	(*dst_size) = (num_blocks * 4);
	अगर (!dst)
		जाओ out;
	जबतक (block_num < num_blocks) अणु
		अचिन्हित अक्षर *src_block;
		अचिन्हित अक्षर dst_block[4];

		अगर (block_num == (num_blocks - 1))
			src_block = last_block;
		अन्यथा
			src_block = &src[block_num * 3];
		dst_block[0] = ((src_block[0] >> 2) & 0x3F);
		dst_block[1] = (((src_block[0] << 4) & 0x30)
				| ((src_block[1] >> 4) & 0x0F));
		dst_block[2] = (((src_block[1] << 2) & 0x3C)
				| ((src_block[2] >> 6) & 0x03));
		dst_block[3] = (src_block[2] & 0x3F);
		dst[dst_offset++] = portable_filename_अक्षरs[dst_block[0]];
		dst[dst_offset++] = portable_filename_अक्षरs[dst_block[1]];
		dst[dst_offset++] = portable_filename_अक्षरs[dst_block[2]];
		dst[dst_offset++] = portable_filename_अक्षरs[dst_block[3]];
		block_num++;
	पूर्ण
out:
	वापस;
पूर्ण

अटल माप_प्रकार ecryptfs_max_decoded_size(माप_प्रकार encoded_size)
अणु
	/* Not exact; conservatively दीर्घ. Every block of 4
	 * encoded अक्षरacters decodes पूर्णांकo a block of 3
	 * decoded अक्षरacters. This segment of code provides
	 * the caller with the maximum amount of allocated
	 * space that @dst will need to poपूर्णांक to in a
	 * subsequent call. */
	वापस ((encoded_size + 1) * 3) / 4;
पूर्ण

/**
 * ecryptfs_decode_from_filename
 * @dst: If शून्य, this function only sets @dst_size and वापसs. If
 *       non-शून्य, this function decodes the encoded octets in @src
 *       पूर्णांकo the memory that @dst poपूर्णांकs to.
 * @dst_size: Set to the size of the decoded string.
 * @src: The encoded set of octets to decode.
 * @src_size: The size of the encoded set of octets to decode.
 */
अटल व्योम
ecryptfs_decode_from_filename(अचिन्हित अक्षर *dst, माप_प्रकार *dst_size,
			      स्थिर अचिन्हित अक्षर *src, माप_प्रकार src_size)
अणु
	u8 current_bit_offset = 0;
	माप_प्रकार src_byte_offset = 0;
	माप_प्रकार dst_byte_offset = 0;

	अगर (!dst) अणु
		(*dst_size) = ecryptfs_max_decoded_size(src_size);
		जाओ out;
	पूर्ण
	जबतक (src_byte_offset < src_size) अणु
		अचिन्हित अक्षर src_byte =
				filename_rev_map[(पूर्णांक)src[src_byte_offset]];

		चयन (current_bit_offset) अणु
		हाल 0:
			dst[dst_byte_offset] = (src_byte << 2);
			current_bit_offset = 6;
			अवरोध;
		हाल 6:
			dst[dst_byte_offset++] |= (src_byte >> 4);
			dst[dst_byte_offset] = ((src_byte & 0xF)
						 << 4);
			current_bit_offset = 4;
			अवरोध;
		हाल 4:
			dst[dst_byte_offset++] |= (src_byte >> 2);
			dst[dst_byte_offset] = (src_byte << 6);
			current_bit_offset = 2;
			अवरोध;
		हाल 2:
			dst[dst_byte_offset++] |= (src_byte);
			current_bit_offset = 0;
			अवरोध;
		पूर्ण
		src_byte_offset++;
	पूर्ण
	(*dst_size) = dst_byte_offset;
out:
	वापस;
पूर्ण

/**
 * ecryptfs_encrypt_and_encode_filename - converts a plaपूर्णांकext file name to cipher text
 * @encoded_name: The encrypted name
 * @encoded_name_size: Length of the encrypted name
 * @mount_crypt_stat: The crypt_stat काष्ठा associated with the file name to encode
 * @name: The plaपूर्णांकext name
 * @name_size: The length of the plaपूर्णांकext name
 *
 * Encrypts and encodes a filename पूर्णांकo something that स्थिरitutes a
 * valid filename क्रम a fileप्रणाली, with prपूर्णांकable अक्षरacters.
 *
 * We assume that we have a properly initialized crypto context,
 * poपूर्णांकed to by crypt_stat->tfm.
 *
 * Returns zero on success; non-zero on otherwise
 */
पूर्णांक ecryptfs_encrypt_and_encode_filename(
	अक्षर **encoded_name,
	माप_प्रकार *encoded_name_size,
	काष्ठा ecryptfs_mount_crypt_stat *mount_crypt_stat,
	स्थिर अक्षर *name, माप_प्रकार name_size)
अणु
	माप_प्रकार encoded_name_no_prefix_size;
	पूर्णांक rc = 0;

	(*encoded_name) = शून्य;
	(*encoded_name_size) = 0;
	अगर (mount_crypt_stat && (mount_crypt_stat->flags
				     & ECRYPTFS_GLOBAL_ENCRYPT_खाताNAMES)) अणु
		काष्ठा ecryptfs_filename *filename;

		filename = kzalloc(माप(*filename), GFP_KERNEL);
		अगर (!filename) अणु
			rc = -ENOMEM;
			जाओ out;
		पूर्ण
		filename->filename = (अक्षर *)name;
		filename->filename_size = name_size;
		rc = ecryptfs_encrypt_filename(filename, mount_crypt_stat);
		अगर (rc) अणु
			prपूर्णांकk(KERN_ERR "%s: Error attempting to encrypt "
			       "filename; rc = [%d]\n", __func__, rc);
			kमुक्त(filename);
			जाओ out;
		पूर्ण
		ecryptfs_encode_क्रम_filename(
			शून्य, &encoded_name_no_prefix_size,
			filename->encrypted_filename,
			filename->encrypted_filename_size);
		अगर (mount_crypt_stat
			&& (mount_crypt_stat->flags
			    & ECRYPTFS_GLOBAL_ENCFN_USE_MOUNT_FNEK))
			(*encoded_name_size) =
				(ECRYPTFS_FNEK_ENCRYPTED_खाताNAME_PREFIX_SIZE
				 + encoded_name_no_prefix_size);
		अन्यथा
			(*encoded_name_size) =
				(ECRYPTFS_FEK_ENCRYPTED_खाताNAME_PREFIX_SIZE
				 + encoded_name_no_prefix_size);
		(*encoded_name) = kदो_स्मृति((*encoded_name_size) + 1, GFP_KERNEL);
		अगर (!(*encoded_name)) अणु
			rc = -ENOMEM;
			kमुक्त(filename->encrypted_filename);
			kमुक्त(filename);
			जाओ out;
		पूर्ण
		अगर (mount_crypt_stat
			&& (mount_crypt_stat->flags
			    & ECRYPTFS_GLOBAL_ENCFN_USE_MOUNT_FNEK)) अणु
			स_नकल((*encoded_name),
			       ECRYPTFS_FNEK_ENCRYPTED_खाताNAME_PREFIX,
			       ECRYPTFS_FNEK_ENCRYPTED_खाताNAME_PREFIX_SIZE);
			ecryptfs_encode_क्रम_filename(
			    ((*encoded_name)
			     + ECRYPTFS_FNEK_ENCRYPTED_खाताNAME_PREFIX_SIZE),
			    &encoded_name_no_prefix_size,
			    filename->encrypted_filename,
			    filename->encrypted_filename_size);
			(*encoded_name_size) =
				(ECRYPTFS_FNEK_ENCRYPTED_खाताNAME_PREFIX_SIZE
				 + encoded_name_no_prefix_size);
			(*encoded_name)[(*encoded_name_size)] = '\0';
		पूर्ण अन्यथा अणु
			rc = -EOPNOTSUPP;
		पूर्ण
		अगर (rc) अणु
			prपूर्णांकk(KERN_ERR "%s: Error attempting to encode "
			       "encrypted filename; rc = [%d]\n", __func__,
			       rc);
			kमुक्त((*encoded_name));
			(*encoded_name) = शून्य;
			(*encoded_name_size) = 0;
		पूर्ण
		kमुक्त(filename->encrypted_filename);
		kमुक्त(filename);
	पूर्ण अन्यथा अणु
		rc = ecryptfs_copy_filename(encoded_name,
					    encoded_name_size,
					    name, name_size);
	पूर्ण
out:
	वापस rc;
पूर्ण

अटल bool is_करोt_करोtकरोt(स्थिर अक्षर *name, माप_प्रकार name_size)
अणु
	अगर (name_size == 1 && name[0] == '.')
		वापस true;
	अन्यथा अगर (name_size == 2 && name[0] == '.' && name[1] == '.')
		वापस true;

	वापस false;
पूर्ण

/**
 * ecryptfs_decode_and_decrypt_filename - converts the encoded cipher text name to decoded plaपूर्णांकext
 * @plaपूर्णांकext_name: The plaपूर्णांकext name
 * @plaपूर्णांकext_name_size: The plaपूर्णांकext name size
 * @sb: Ecryptfs's super_block
 * @name: The filename in cipher text
 * @name_size: The cipher text name size
 *
 * Decrypts and decodes the filename.
 *
 * Returns zero on error; non-zero otherwise
 */
पूर्णांक ecryptfs_decode_and_decrypt_filename(अक्षर **plaपूर्णांकext_name,
					 माप_प्रकार *plaपूर्णांकext_name_size,
					 काष्ठा super_block *sb,
					 स्थिर अक्षर *name, माप_प्रकार name_size)
अणु
	काष्ठा ecryptfs_mount_crypt_stat *mount_crypt_stat =
		&ecryptfs_superblock_to_निजी(sb)->mount_crypt_stat;
	अक्षर *decoded_name;
	माप_प्रकार decoded_name_size;
	माप_प्रकार packet_size;
	पूर्णांक rc = 0;

	अगर ((mount_crypt_stat->flags & ECRYPTFS_GLOBAL_ENCRYPT_खाताNAMES) &&
	    !(mount_crypt_stat->flags & ECRYPTFS_ENCRYPTED_VIEW_ENABLED)) अणु
		अगर (is_करोt_करोtकरोt(name, name_size)) अणु
			rc = ecryptfs_copy_filename(plaपूर्णांकext_name,
						    plaपूर्णांकext_name_size,
						    name, name_size);
			जाओ out;
		पूर्ण

		अगर (name_size <= ECRYPTFS_FNEK_ENCRYPTED_खाताNAME_PREFIX_SIZE ||
		    म_भेदन(name, ECRYPTFS_FNEK_ENCRYPTED_खाताNAME_PREFIX,
			    ECRYPTFS_FNEK_ENCRYPTED_खाताNAME_PREFIX_SIZE)) अणु
			rc = -EINVAL;
			जाओ out;
		पूर्ण

		name += ECRYPTFS_FNEK_ENCRYPTED_खाताNAME_PREFIX_SIZE;
		name_size -= ECRYPTFS_FNEK_ENCRYPTED_खाताNAME_PREFIX_SIZE;
		ecryptfs_decode_from_filename(शून्य, &decoded_name_size,
					      name, name_size);
		decoded_name = kदो_स्मृति(decoded_name_size, GFP_KERNEL);
		अगर (!decoded_name) अणु
			rc = -ENOMEM;
			जाओ out;
		पूर्ण
		ecryptfs_decode_from_filename(decoded_name, &decoded_name_size,
					      name, name_size);
		rc = ecryptfs_parse_tag_70_packet(plaपूर्णांकext_name,
						  plaपूर्णांकext_name_size,
						  &packet_size,
						  mount_crypt_stat,
						  decoded_name,
						  decoded_name_size);
		अगर (rc) अणु
			ecryptfs_prपूर्णांकk(KERN_DEBUG,
					"%s: Could not parse tag 70 packet from filename\n",
					__func__);
			जाओ out_मुक्त;
		पूर्ण
	पूर्ण अन्यथा अणु
		rc = ecryptfs_copy_filename(plaपूर्णांकext_name,
					    plaपूर्णांकext_name_size,
					    name, name_size);
		जाओ out;
	पूर्ण
out_मुक्त:
	kमुक्त(decoded_name);
out:
	वापस rc;
पूर्ण

#घोषणा ENC_NAME_MAX_BLOCKLEN_8_OR_16	143

पूर्णांक ecryptfs_set_f_namelen(दीर्घ *namelen, दीर्घ lower_namelen,
			   काष्ठा ecryptfs_mount_crypt_stat *mount_crypt_stat)
अणु
	काष्ठा crypto_skcipher *tfm;
	काष्ठा mutex *tfm_mutex;
	माप_प्रकार cipher_blocksize;
	पूर्णांक rc;

	अगर (!(mount_crypt_stat->flags & ECRYPTFS_GLOBAL_ENCRYPT_खाताNAMES)) अणु
		(*namelen) = lower_namelen;
		वापस 0;
	पूर्ण

	rc = ecryptfs_get_tfm_and_mutex_क्रम_cipher_name(&tfm, &tfm_mutex,
			mount_crypt_stat->global_शेष_fn_cipher_name);
	अगर (unlikely(rc)) अणु
		(*namelen) = 0;
		वापस rc;
	पूर्ण

	mutex_lock(tfm_mutex);
	cipher_blocksize = crypto_skcipher_blocksize(tfm);
	mutex_unlock(tfm_mutex);

	/* Return an exact amount क्रम the common हालs */
	अगर (lower_namelen == NAME_MAX
	    && (cipher_blocksize == 8 || cipher_blocksize == 16)) अणु
		(*namelen) = ENC_NAME_MAX_BLOCKLEN_8_OR_16;
		वापस 0;
	पूर्ण

	/* Return a safe estimate क्रम the uncommon हालs */
	(*namelen) = lower_namelen;
	(*namelen) -= ECRYPTFS_FNEK_ENCRYPTED_खाताNAME_PREFIX_SIZE;
	/* Since this is the max decoded size, subtract 1 "decoded block" len */
	(*namelen) = ecryptfs_max_decoded_size(*namelen) - 3;
	(*namelen) -= ECRYPTFS_TAG_70_MAX_METADATA_SIZE;
	(*namelen) -= ECRYPTFS_खाताNAME_MIN_RANDOM_PREPEND_BYTES;
	/* Worst हाल is that the filename is padded nearly a full block size */
	(*namelen) -= cipher_blocksize - 1;

	अगर ((*namelen) < 0)
		(*namelen) = 0;

	वापस 0;
पूर्ण
