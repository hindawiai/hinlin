<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Opening fs-verity files
 *
 * Copyright 2019 Google LLC
 */

#समावेश "fsverity_private.h"

#समावेश <linux/slab.h>

अटल काष्ठा kmem_cache *fsverity_info_cachep;

/**
 * fsverity_init_merkle_tree_params() - initialize Merkle tree parameters
 * @params: the parameters काष्ठा to initialize
 * @inode: the inode क्रम which the Merkle tree is being built
 * @hash_algorithm: number of hash algorithm to use
 * @log_blocksize: log base 2 of block size to use
 * @salt: poपूर्णांकer to salt (optional)
 * @salt_size: size of salt, possibly 0
 *
 * Validate the hash algorithm and block size, then compute the tree topology
 * (num levels, num blocks in each level, etc.) and initialize @params.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
पूर्णांक fsverity_init_merkle_tree_params(काष्ठा merkle_tree_params *params,
				     स्थिर काष्ठा inode *inode,
				     अचिन्हित पूर्णांक hash_algorithm,
				     अचिन्हित पूर्णांक log_blocksize,
				     स्थिर u8 *salt, माप_प्रकार salt_size)
अणु
	काष्ठा fsverity_hash_alg *hash_alg;
	पूर्णांक err;
	u64 blocks;
	u64 offset;
	पूर्णांक level;

	स_रखो(params, 0, माप(*params));

	hash_alg = fsverity_get_hash_alg(inode, hash_algorithm);
	अगर (IS_ERR(hash_alg))
		वापस PTR_ERR(hash_alg);
	params->hash_alg = hash_alg;
	params->digest_size = hash_alg->digest_size;

	params->hashstate = fsverity_prepare_hash_state(hash_alg, salt,
							salt_size);
	अगर (IS_ERR(params->hashstate)) अणु
		err = PTR_ERR(params->hashstate);
		params->hashstate = शून्य;
		fsverity_err(inode, "Error %d preparing hash state", err);
		जाओ out_err;
	पूर्ण

	अगर (log_blocksize != PAGE_SHIFT) अणु
		fsverity_warn(inode, "Unsupported log_blocksize: %u",
			      log_blocksize);
		err = -EINVAL;
		जाओ out_err;
	पूर्ण
	params->log_blocksize = log_blocksize;
	params->block_size = 1 << log_blocksize;

	अगर (WARN_ON(!is_घातer_of_2(params->digest_size))) अणु
		err = -EINVAL;
		जाओ out_err;
	पूर्ण
	अगर (params->block_size < 2 * params->digest_size) अणु
		fsverity_warn(inode,
			      "Merkle tree block size (%u) too small for hash algorithm \"%s\"",
			      params->block_size, hash_alg->name);
		err = -EINVAL;
		जाओ out_err;
	पूर्ण
	params->log_arity = params->log_blocksize - ilog2(params->digest_size);
	params->hashes_per_block = 1 << params->log_arity;

	pr_debug("Merkle tree uses %s with %u-byte blocks (%u hashes/block), salt=%*phN\n",
		 hash_alg->name, params->block_size, params->hashes_per_block,
		 (पूर्णांक)salt_size, salt);

	/*
	 * Compute the number of levels in the Merkle tree and create a map from
	 * level to the starting block of that level.  Level 'num_levels - 1' is
	 * the root and is stored first.  Level 0 is the level directly "above"
	 * the data blocks and is stored last.
	 */

	/* Compute number of levels and the number of blocks in each level */
	blocks = (inode->i_size + params->block_size - 1) >> log_blocksize;
	pr_debug("Data is %lld bytes (%llu blocks)\n", inode->i_size, blocks);
	जबतक (blocks > 1) अणु
		अगर (params->num_levels >= FS_VERITY_MAX_LEVELS) अणु
			fsverity_err(inode, "Too many levels in Merkle tree");
			err = -EINVAL;
			जाओ out_err;
		पूर्ण
		blocks = (blocks + params->hashes_per_block - 1) >>
			 params->log_arity;
		/* temporarily using level_start[] to store blocks in level */
		params->level_start[params->num_levels++] = blocks;
	पूर्ण
	params->level0_blocks = params->level_start[0];

	/* Compute the starting block of each level */
	offset = 0;
	क्रम (level = (पूर्णांक)params->num_levels - 1; level >= 0; level--) अणु
		blocks = params->level_start[level];
		params->level_start[level] = offset;
		pr_debug("Level %d is %llu blocks starting at index %llu\n",
			 level, blocks, offset);
		offset += blocks;
	पूर्ण

	params->tree_size = offset << log_blocksize;
	वापस 0;

out_err:
	kमुक्त(params->hashstate);
	स_रखो(params, 0, माप(*params));
	वापस err;
पूर्ण

/*
 * Compute the file digest by hashing the fsverity_descriptor excluding the
 * signature and with the sig_size field set to 0.
 */
अटल पूर्णांक compute_file_digest(काष्ठा fsverity_hash_alg *hash_alg,
			       काष्ठा fsverity_descriptor *desc,
			       u8 *file_digest)
अणु
	__le32 sig_size = desc->sig_size;
	पूर्णांक err;

	desc->sig_size = 0;
	err = fsverity_hash_buffer(hash_alg, desc, माप(*desc), file_digest);
	desc->sig_size = sig_size;

	वापस err;
पूर्ण

/*
 * Create a new fsverity_info from the given fsverity_descriptor (with optional
 * appended signature), and check the signature अगर present.  The
 * fsverity_descriptor must have alपढ़ोy undergone basic validation.
 */
काष्ठा fsverity_info *fsverity_create_info(स्थिर काष्ठा inode *inode,
					   काष्ठा fsverity_descriptor *desc,
					   माप_प्रकार desc_size)
अणु
	काष्ठा fsverity_info *vi;
	पूर्णांक err;

	vi = kmem_cache_zalloc(fsverity_info_cachep, GFP_KERNEL);
	अगर (!vi)
		वापस ERR_PTR(-ENOMEM);
	vi->inode = inode;

	err = fsverity_init_merkle_tree_params(&vi->tree_params, inode,
					       desc->hash_algorithm,
					       desc->log_blocksize,
					       desc->salt, desc->salt_size);
	अगर (err) अणु
		fsverity_err(inode,
			     "Error %d initializing Merkle tree parameters",
			     err);
		जाओ out;
	पूर्ण

	स_नकल(vi->root_hash, desc->root_hash, vi->tree_params.digest_size);

	err = compute_file_digest(vi->tree_params.hash_alg, desc,
				  vi->file_digest);
	अगर (err) अणु
		fsverity_err(inode, "Error %d computing file digest", err);
		जाओ out;
	पूर्ण
	pr_debug("Computed file digest: %s:%*phN\n",
		 vi->tree_params.hash_alg->name,
		 vi->tree_params.digest_size, vi->file_digest);

	err = fsverity_verअगरy_signature(vi, desc->signature,
					le32_to_cpu(desc->sig_size));
out:
	अगर (err) अणु
		fsverity_मुक्त_info(vi);
		vi = ERR_PTR(err);
	पूर्ण
	वापस vi;
पूर्ण

व्योम fsverity_set_info(काष्ठा inode *inode, काष्ठा fsverity_info *vi)
अणु
	/*
	 * Multiple tasks may race to set ->i_verity_info, so use
	 * cmpxchg_release().  This pairs with the smp_load_acquire() in
	 * fsverity_get_info().  I.e., here we publish ->i_verity_info with a
	 * RELEASE barrier so that other tasks can ACQUIRE it.
	 */
	अगर (cmpxchg_release(&inode->i_verity_info, शून्य, vi) != शून्य) अणु
		/* Lost the race, so मुक्त the fsverity_info we allocated. */
		fsverity_मुक्त_info(vi);
		/*
		 * Afterwards, the caller may access ->i_verity_info directly,
		 * so make sure to ACQUIRE the winning fsverity_info.
		 */
		(व्योम)fsverity_get_info(inode);
	पूर्ण
पूर्ण

व्योम fsverity_मुक्त_info(काष्ठा fsverity_info *vi)
अणु
	अगर (!vi)
		वापस;
	kमुक्त(vi->tree_params.hashstate);
	kmem_cache_मुक्त(fsverity_info_cachep, vi);
पूर्ण

अटल bool validate_fsverity_descriptor(काष्ठा inode *inode,
					 स्थिर काष्ठा fsverity_descriptor *desc,
					 माप_प्रकार desc_size)
अणु
	अगर (desc_size < माप(*desc)) अणु
		fsverity_err(inode, "Unrecognized descriptor size: %zu bytes",
			     desc_size);
		वापस false;
	पूर्ण

	अगर (desc->version != 1) अणु
		fsverity_err(inode, "Unrecognized descriptor version: %u",
			     desc->version);
		वापस false;
	पूर्ण

	अगर (स_प्रथम_inv(desc->__reserved, 0, माप(desc->__reserved))) अणु
		fsverity_err(inode, "Reserved bits set in descriptor");
		वापस false;
	पूर्ण

	अगर (desc->salt_size > माप(desc->salt)) अणु
		fsverity_err(inode, "Invalid salt_size: %u", desc->salt_size);
		वापस false;
	पूर्ण

	अगर (le64_to_cpu(desc->data_size) != inode->i_size) अणु
		fsverity_err(inode,
			     "Wrong data_size: %llu (desc) != %lld (inode)",
			     le64_to_cpu(desc->data_size), inode->i_size);
		वापस false;
	पूर्ण

	अगर (le32_to_cpu(desc->sig_size) > desc_size - माप(*desc)) अणु
		fsverity_err(inode, "Signature overflows verity descriptor");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/*
 * Read the inode's fsverity_descriptor (with optional appended signature) from
 * the fileप्रणाली, and करो basic validation of it.
 */
पूर्णांक fsverity_get_descriptor(काष्ठा inode *inode,
			    काष्ठा fsverity_descriptor **desc_ret,
			    माप_प्रकार *desc_size_ret)
अणु
	पूर्णांक res;
	काष्ठा fsverity_descriptor *desc;

	res = inode->i_sb->s_vop->get_verity_descriptor(inode, शून्य, 0);
	अगर (res < 0) अणु
		fsverity_err(inode,
			     "Error %d getting verity descriptor size", res);
		वापस res;
	पूर्ण
	अगर (res > FS_VERITY_MAX_DESCRIPTOR_SIZE) अणु
		fsverity_err(inode, "Verity descriptor is too large (%d bytes)",
			     res);
		वापस -EMSGSIZE;
	पूर्ण
	desc = kदो_स्मृति(res, GFP_KERNEL);
	अगर (!desc)
		वापस -ENOMEM;
	res = inode->i_sb->s_vop->get_verity_descriptor(inode, desc, res);
	अगर (res < 0) अणु
		fsverity_err(inode, "Error %d reading verity descriptor", res);
		kमुक्त(desc);
		वापस res;
	पूर्ण

	अगर (!validate_fsverity_descriptor(inode, desc, res)) अणु
		kमुक्त(desc);
		वापस -EINVAL;
	पूर्ण

	*desc_ret = desc;
	*desc_size_ret = res;
	वापस 0;
पूर्ण

/* Ensure the inode has an ->i_verity_info */
अटल पूर्णांक ensure_verity_info(काष्ठा inode *inode)
अणु
	काष्ठा fsverity_info *vi = fsverity_get_info(inode);
	काष्ठा fsverity_descriptor *desc;
	माप_प्रकार desc_size;
	पूर्णांक err;

	अगर (vi)
		वापस 0;

	err = fsverity_get_descriptor(inode, &desc, &desc_size);
	अगर (err)
		वापस err;

	vi = fsverity_create_info(inode, desc, desc_size);
	अगर (IS_ERR(vi)) अणु
		err = PTR_ERR(vi);
		जाओ out_मुक्त_desc;
	पूर्ण

	fsverity_set_info(inode, vi);
	err = 0;
out_मुक्त_desc:
	kमुक्त(desc);
	वापस err;
पूर्ण

/**
 * fsverity_file_खोलो() - prepare to खोलो a verity file
 * @inode: the inode being खोलोed
 * @filp: the काष्ठा file being set up
 *
 * When खोलोing a verity file, deny the खोलो अगर it is क्रम writing.  Otherwise,
 * set up the inode's ->i_verity_info अगर not alपढ़ोy करोne.
 *
 * When combined with fscrypt, this must be called after fscrypt_file_खोलो().
 * Otherwise, we won't have the key set up to decrypt the verity metadata.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
पूर्णांक fsverity_file_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	अगर (!IS_VERITY(inode))
		वापस 0;

	अगर (filp->f_mode & FMODE_WRITE) अणु
		pr_debug("Denying opening verity file (ino %lu) for write\n",
			 inode->i_ino);
		वापस -EPERM;
	पूर्ण

	वापस ensure_verity_info(inode);
पूर्ण
EXPORT_SYMBOL_GPL(fsverity_file_खोलो);

/**
 * fsverity_prepare_setattr() - prepare to change a verity inode's attributes
 * @dentry: dentry through which the inode is being changed
 * @attr: attributes to change
 *
 * Verity files are immutable, so deny truncates.  This isn't covered by the
 * खोलो-समय check because sys_truncate() takes a path, not a file descriptor.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
पूर्णांक fsverity_prepare_setattr(काष्ठा dentry *dentry, काष्ठा iattr *attr)
अणु
	अगर (IS_VERITY(d_inode(dentry)) && (attr->ia_valid & ATTR_SIZE)) अणु
		pr_debug("Denying truncate of verity file (ino %lu)\n",
			 d_inode(dentry)->i_ino);
		वापस -EPERM;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(fsverity_prepare_setattr);

/**
 * fsverity_cleanup_inode() - मुक्त the inode's verity info, अगर present
 * @inode: an inode being evicted
 *
 * Fileप्रणालीs must call this on inode eviction to मुक्त ->i_verity_info.
 */
व्योम fsverity_cleanup_inode(काष्ठा inode *inode)
अणु
	fsverity_मुक्त_info(inode->i_verity_info);
	inode->i_verity_info = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(fsverity_cleanup_inode);

पूर्णांक __init fsverity_init_info_cache(व्योम)
अणु
	fsverity_info_cachep = KMEM_CACHE_USERCOPY(fsverity_info,
						   SLAB_RECLAIM_ACCOUNT,
						   file_digest);
	अगर (!fsverity_info_cachep)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम __init fsverity_निकास_info_cache(व्योम)
अणु
	kmem_cache_destroy(fsverity_info_cachep);
	fsverity_info_cachep = शून्य;
पूर्ण
