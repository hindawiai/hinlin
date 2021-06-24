<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Ioctl to enable verity on a file
 *
 * Copyright 2019 Google LLC
 */

#समावेश "fsverity_private.h"

#समावेश <crypto/hash.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/mount.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/uaccess.h>

/*
 * Read a file data page क्रम Merkle tree स्थिरruction.  Do aggressive पढ़ोahead,
 * since we're sequentially पढ़ोing the entire file.
 */
अटल काष्ठा page *पढ़ो_file_data_page(काष्ठा file *filp, pgoff_t index,
					काष्ठा file_ra_state *ra,
					अचिन्हित दीर्घ reमुख्यing_pages)
अणु
	काष्ठा page *page;

	page = find_get_page_flags(filp->f_mapping, index, FGP_ACCESSED);
	अगर (!page || !PageUptodate(page)) अणु
		अगर (page)
			put_page(page);
		अन्यथा
			page_cache_sync_पढ़ोahead(filp->f_mapping, ra, filp,
						  index, reमुख्यing_pages);
		page = पढ़ो_mapping_page(filp->f_mapping, index, शून्य);
		अगर (IS_ERR(page))
			वापस page;
	पूर्ण
	अगर (PageReadahead(page))
		page_cache_async_पढ़ोahead(filp->f_mapping, ra, filp, page,
					   index, reमुख्यing_pages);
	वापस page;
पूर्ण

अटल पूर्णांक build_merkle_tree_level(काष्ठा file *filp, अचिन्हित पूर्णांक level,
				   u64 num_blocks_to_hash,
				   स्थिर काष्ठा merkle_tree_params *params,
				   u8 *pending_hashes,
				   काष्ठा ahash_request *req)
अणु
	काष्ठा inode *inode = file_inode(filp);
	स्थिर काष्ठा fsverity_operations *vops = inode->i_sb->s_vop;
	काष्ठा file_ra_state ra = अणु 0 पूर्ण;
	अचिन्हित पूर्णांक pending_size = 0;
	u64 dst_block_num;
	u64 i;
	पूर्णांक err;

	अगर (WARN_ON(params->block_size != PAGE_SIZE)) /* checked earlier too */
		वापस -EINVAL;

	अगर (level < params->num_levels) अणु
		dst_block_num = params->level_start[level];
	पूर्ण अन्यथा अणु
		अगर (WARN_ON(num_blocks_to_hash != 1))
			वापस -EINVAL;
		dst_block_num = 0; /* unused */
	पूर्ण

	file_ra_state_init(&ra, filp->f_mapping);

	क्रम (i = 0; i < num_blocks_to_hash; i++) अणु
		काष्ठा page *src_page;

		अगर ((pgoff_t)i % 10000 == 0 || i + 1 == num_blocks_to_hash)
			pr_debug("Hashing block %llu of %llu for level %u\n",
				 i + 1, num_blocks_to_hash, level);

		अगर (level == 0) अणु
			/* Leaf: hashing a data block */
			src_page = पढ़ो_file_data_page(filp, i, &ra,
						       num_blocks_to_hash - i);
			अगर (IS_ERR(src_page)) अणु
				err = PTR_ERR(src_page);
				fsverity_err(inode,
					     "Error %d reading data page %llu",
					     err, i);
				वापस err;
			पूर्ण
		पूर्ण अन्यथा अणु
			अचिन्हित दीर्घ num_ra_pages =
				min_t(अचिन्हित दीर्घ, num_blocks_to_hash - i,
				      inode->i_sb->s_bdi->io_pages);

			/* Non-leaf: hashing hash block from level below */
			src_page = vops->पढ़ो_merkle_tree_page(inode,
					params->level_start[level - 1] + i,
					num_ra_pages);
			अगर (IS_ERR(src_page)) अणु
				err = PTR_ERR(src_page);
				fsverity_err(inode,
					     "Error %d reading Merkle tree page %llu",
					     err, params->level_start[level - 1] + i);
				वापस err;
			पूर्ण
		पूर्ण

		err = fsverity_hash_page(params, inode, req, src_page,
					 &pending_hashes[pending_size]);
		put_page(src_page);
		अगर (err)
			वापस err;
		pending_size += params->digest_size;

		अगर (level == params->num_levels) /* Root hash? */
			वापस 0;

		अगर (pending_size + params->digest_size > params->block_size ||
		    i + 1 == num_blocks_to_hash) अणु
			/* Flush the pending hash block */
			स_रखो(&pending_hashes[pending_size], 0,
			       params->block_size - pending_size);
			err = vops->ग_लिखो_merkle_tree_block(inode,
					pending_hashes,
					dst_block_num,
					params->log_blocksize);
			अगर (err) अणु
				fsverity_err(inode,
					     "Error %d writing Merkle tree block %llu",
					     err, dst_block_num);
				वापस err;
			पूर्ण
			dst_block_num++;
			pending_size = 0;
		पूर्ण

		अगर (fatal_संकेत_pending(current))
			वापस -EINTR;
		cond_resched();
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Build the Merkle tree क्रम the given file using the given parameters, and
 * वापस the root hash in @root_hash.
 *
 * The tree is written to a fileप्रणाली-specअगरic location as determined by the
 * ->ग_लिखो_merkle_tree_block() method.  However, the blocks that comprise the
 * tree are the same क्रम all fileप्रणालीs.
 */
अटल पूर्णांक build_merkle_tree(काष्ठा file *filp,
			     स्थिर काष्ठा merkle_tree_params *params,
			     u8 *root_hash)
अणु
	काष्ठा inode *inode = file_inode(filp);
	u8 *pending_hashes;
	काष्ठा ahash_request *req;
	u64 blocks;
	अचिन्हित पूर्णांक level;
	पूर्णांक err = -ENOMEM;

	अगर (inode->i_size == 0) अणु
		/* Empty file is a special हाल; root hash is all 0's */
		स_रखो(root_hash, 0, params->digest_size);
		वापस 0;
	पूर्ण

	/* This allocation never fails, since it's mempool-backed. */
	req = fsverity_alloc_hash_request(params->hash_alg, GFP_KERNEL);

	pending_hashes = kदो_स्मृति(params->block_size, GFP_KERNEL);
	अगर (!pending_hashes)
		जाओ out;

	/*
	 * Build each level of the Merkle tree, starting at the leaf level
	 * (level 0) and ascending to the root node (level 'num_levels - 1').
	 * Then at the end (level 'num_levels'), calculate the root hash.
	 */
	blocks = (inode->i_size + params->block_size - 1) >>
		 params->log_blocksize;
	क्रम (level = 0; level <= params->num_levels; level++) अणु
		err = build_merkle_tree_level(filp, level, blocks, params,
					      pending_hashes, req);
		अगर (err)
			जाओ out;
		blocks = (blocks + params->hashes_per_block - 1) >>
			 params->log_arity;
	पूर्ण
	स_नकल(root_hash, pending_hashes, params->digest_size);
	err = 0;
out:
	kमुक्त(pending_hashes);
	fsverity_मुक्त_hash_request(params->hash_alg, req);
	वापस err;
पूर्ण

अटल पूर्णांक enable_verity(काष्ठा file *filp,
			 स्थिर काष्ठा fsverity_enable_arg *arg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	स्थिर काष्ठा fsverity_operations *vops = inode->i_sb->s_vop;
	काष्ठा merkle_tree_params params = अणु पूर्ण;
	काष्ठा fsverity_descriptor *desc;
	माप_प्रकार desc_size = माप(*desc) + arg->sig_size;
	काष्ठा fsverity_info *vi;
	पूर्णांक err;

	/* Start initializing the fsverity_descriptor */
	desc = kzalloc(desc_size, GFP_KERNEL);
	अगर (!desc)
		वापस -ENOMEM;
	desc->version = 1;
	desc->hash_algorithm = arg->hash_algorithm;
	desc->log_blocksize = ilog2(arg->block_size);

	/* Get the salt अगर the user provided one */
	अगर (arg->salt_size &&
	    copy_from_user(desc->salt, u64_to_user_ptr(arg->salt_ptr),
			   arg->salt_size)) अणु
		err = -EFAULT;
		जाओ out;
	पूर्ण
	desc->salt_size = arg->salt_size;

	/* Get the signature अगर the user provided one */
	अगर (arg->sig_size &&
	    copy_from_user(desc->signature, u64_to_user_ptr(arg->sig_ptr),
			   arg->sig_size)) अणु
		err = -EFAULT;
		जाओ out;
	पूर्ण
	desc->sig_size = cpu_to_le32(arg->sig_size);

	desc->data_size = cpu_to_le64(inode->i_size);

	/* Prepare the Merkle tree parameters */
	err = fsverity_init_merkle_tree_params(&params, inode,
					       arg->hash_algorithm,
					       desc->log_blocksize,
					       desc->salt, desc->salt_size);
	अगर (err)
		जाओ out;

	/*
	 * Start enabling verity on this file, serialized by the inode lock.
	 * Fail अगर verity is alपढ़ोy enabled or is alपढ़ोy being enabled.
	 */
	inode_lock(inode);
	अगर (IS_VERITY(inode))
		err = -EEXIST;
	अन्यथा
		err = vops->begin_enable_verity(filp);
	inode_unlock(inode);
	अगर (err)
		जाओ out;

	/*
	 * Build the Merkle tree.  Don't hold the inode lock during this, since
	 * on huge files this may take a very दीर्घ समय and we करोn't want to
	 * क्रमce unrelated syscalls like chown() to block क्रमever.  We करोn't
	 * need the inode lock here because deny_ग_लिखो_access() alपढ़ोy prevents
	 * the file from being written to or truncated, and we still serialize
	 * ->begin_enable_verity() and ->end_enable_verity() using the inode
	 * lock and only allow one process to be here at a समय on a given file.
	 */
	pr_debug("Building Merkle tree...\n");
	BUILD_BUG_ON(माप(desc->root_hash) < FS_VERITY_MAX_DIGEST_SIZE);
	err = build_merkle_tree(filp, &params, desc->root_hash);
	अगर (err) अणु
		fsverity_err(inode, "Error %d building Merkle tree", err);
		जाओ rollback;
	पूर्ण
	pr_debug("Done building Merkle tree.  Root hash is %s:%*phN\n",
		 params.hash_alg->name, params.digest_size, desc->root_hash);

	/*
	 * Create the fsverity_info.  Don't bother trying to save work by
	 * reusing the merkle_tree_params from above.  Instead, just create the
	 * fsverity_info from the fsverity_descriptor as अगर it were just loaded
	 * from disk.  This is simpler, and it serves as an extra check that the
	 * metadata we're writing is valid beक्रमe actually enabling verity.
	 */
	vi = fsverity_create_info(inode, desc, desc_size);
	अगर (IS_ERR(vi)) अणु
		err = PTR_ERR(vi);
		जाओ rollback;
	पूर्ण

	अगर (arg->sig_size)
		pr_debug("Storing a %u-byte PKCS#7 signature alongside the file\n",
			 arg->sig_size);

	/*
	 * Tell the fileप्रणाली to finish enabling verity on the file.
	 * Serialized with ->begin_enable_verity() by the inode lock.
	 */
	inode_lock(inode);
	err = vops->end_enable_verity(filp, desc, desc_size, params.tree_size);
	inode_unlock(inode);
	अगर (err) अणु
		fsverity_err(inode, "%ps() failed with err %d",
			     vops->end_enable_verity, err);
		fsverity_मुक्त_info(vi);
	पूर्ण अन्यथा अगर (WARN_ON(!IS_VERITY(inode))) अणु
		err = -EINVAL;
		fsverity_मुक्त_info(vi);
	पूर्ण अन्यथा अणु
		/* Successfully enabled verity */

		/*
		 * Readers can start using ->i_verity_info immediately, so it
		 * can't be rolled back once set.  So don't set it until just
		 * after the fileप्रणाली has successfully enabled verity.
		 */
		fsverity_set_info(inode, vi);
	पूर्ण
out:
	kमुक्त(params.hashstate);
	kमुक्त(desc);
	वापस err;

rollback:
	inode_lock(inode);
	(व्योम)vops->end_enable_verity(filp, शून्य, 0, params.tree_size);
	inode_unlock(inode);
	जाओ out;
पूर्ण

/**
 * fsverity_ioctl_enable() - enable verity on a file
 * @filp: file to enable verity on
 * @uarg: user poपूर्णांकer to fsverity_enable_arg
 *
 * Enable fs-verity on a file.  See the "FS_IOC_ENABLE_VERITY" section of
 * Documentation/fileप्रणालीs/fsverity.rst क्रम the करोcumentation.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
पूर्णांक fsverity_ioctl_enable(काष्ठा file *filp, स्थिर व्योम __user *uarg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा fsverity_enable_arg arg;
	पूर्णांक err;

	अगर (copy_from_user(&arg, uarg, माप(arg)))
		वापस -EFAULT;

	अगर (arg.version != 1)
		वापस -EINVAL;

	अगर (arg.__reserved1 ||
	    स_प्रथम_inv(arg.__reserved2, 0, माप(arg.__reserved2)))
		वापस -EINVAL;

	अगर (arg.block_size != PAGE_SIZE)
		वापस -EINVAL;

	अगर (arg.salt_size > माप_field(काष्ठा fsverity_descriptor, salt))
		वापस -EMSGSIZE;

	अगर (arg.sig_size > FS_VERITY_MAX_SIGNATURE_SIZE)
		वापस -EMSGSIZE;

	/*
	 * Require a regular file with ग_लिखो access.  But the actual fd must
	 * still be पढ़ोonly so that we can lock out all ग_लिखोrs.  This is
	 * needed to guarantee that no writable fds exist to the file once it
	 * has verity enabled, and to stabilize the data being hashed.
	 */

	err = file_permission(filp, MAY_WRITE);
	अगर (err)
		वापस err;

	अगर (IS_APPEND(inode))
		वापस -EPERM;

	अगर (S_ISसूची(inode->i_mode))
		वापस -EISसूची;

	अगर (!S_ISREG(inode->i_mode))
		वापस -EINVAL;

	err = mnt_want_ग_लिखो_file(filp);
	अगर (err) /* -EROFS */
		वापस err;

	err = deny_ग_लिखो_access(filp);
	अगर (err) /* -ETXTBSY */
		जाओ out_drop_ग_लिखो;

	err = enable_verity(filp, &arg);
	अगर (err)
		जाओ out_allow_ग_लिखो_access;

	/*
	 * Some pages of the file may have been evicted from pagecache after
	 * being used in the Merkle tree स्थिरruction, then पढ़ो पूर्णांकo pagecache
	 * again by another process पढ़ोing from the file concurrently.  Since
	 * these pages didn't undergo verअगरication against the file digest which
	 * fs-verity now claims to be enक्रमcing, we have to wipe the pagecache
	 * to ensure that all future पढ़ोs are verअगरied.
	 */
	filemap_ग_लिखो_and_रुको(inode->i_mapping);
	invalidate_inode_pages2(inode->i_mapping);

	/*
	 * allow_ग_लिखो_access() is needed to pair with deny_ग_लिखो_access().
	 * Regardless, the fileप्रणाली won't allow writing to verity files.
	 */
out_allow_ग_लिखो_access:
	allow_ग_लिखो_access(filp);
out_drop_ग_लिखो:
	mnt_drop_ग_लिखो_file(filp);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(fsverity_ioctl_enable);
