<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Ioctl to पढ़ो verity metadata
 *
 * Copyright 2021 Google LLC
 */

#समावेश "fsverity_private.h"

#समावेश <linux/backing-dev.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/uaccess.h>

अटल पूर्णांक fsverity_पढ़ो_merkle_tree(काष्ठा inode *inode,
				     स्थिर काष्ठा fsverity_info *vi,
				     व्योम __user *buf, u64 offset, पूर्णांक length)
अणु
	स्थिर काष्ठा fsverity_operations *vops = inode->i_sb->s_vop;
	u64 end_offset;
	अचिन्हित पूर्णांक offs_in_page;
	pgoff_t index, last_index;
	पूर्णांक retval = 0;
	पूर्णांक err = 0;

	end_offset = min(offset + length, vi->tree_params.tree_size);
	अगर (offset >= end_offset)
		वापस 0;
	offs_in_page = offset_in_page(offset);
	last_index = (end_offset - 1) >> PAGE_SHIFT;

	/*
	 * Iterate through each Merkle tree page in the requested range and copy
	 * the requested portion to userspace.  Note that the Merkle tree block
	 * size isn't important here, as we are वापसing a byte stream; i.e.,
	 * we can just work with pages even अगर the tree block size != PAGE_SIZE.
	 */
	क्रम (index = offset >> PAGE_SHIFT; index <= last_index; index++) अणु
		अचिन्हित दीर्घ num_ra_pages =
			min_t(अचिन्हित दीर्घ, last_index - index + 1,
			      inode->i_sb->s_bdi->io_pages);
		अचिन्हित पूर्णांक bytes_to_copy = min_t(u64, end_offset - offset,
						   PAGE_SIZE - offs_in_page);
		काष्ठा page *page;
		स्थिर व्योम *virt;

		page = vops->पढ़ो_merkle_tree_page(inode, index, num_ra_pages);
		अगर (IS_ERR(page)) अणु
			err = PTR_ERR(page);
			fsverity_err(inode,
				     "Error %d reading Merkle tree page %lu",
				     err, index);
			अवरोध;
		पूर्ण

		virt = kmap(page);
		अगर (copy_to_user(buf, virt + offs_in_page, bytes_to_copy)) अणु
			kunmap(page);
			put_page(page);
			err = -EFAULT;
			अवरोध;
		पूर्ण
		kunmap(page);
		put_page(page);

		retval += bytes_to_copy;
		buf += bytes_to_copy;
		offset += bytes_to_copy;

		अगर (fatal_संकेत_pending(current))  अणु
			err = -EINTR;
			अवरोध;
		पूर्ण
		cond_resched();
		offs_in_page = 0;
	पूर्ण
	वापस retval ? retval : err;
पूर्ण

/* Copy the requested portion of the buffer to userspace. */
अटल पूर्णांक fsverity_पढ़ो_buffer(व्योम __user *dst, u64 offset, पूर्णांक length,
				स्थिर व्योम *src, माप_प्रकार src_length)
अणु
	अगर (offset >= src_length)
		वापस 0;
	src += offset;
	src_length -= offset;

	length = min_t(माप_प्रकार, length, src_length);

	अगर (copy_to_user(dst, src, length))
		वापस -EFAULT;

	वापस length;
पूर्ण

अटल पूर्णांक fsverity_पढ़ो_descriptor(काष्ठा inode *inode,
				    व्योम __user *buf, u64 offset, पूर्णांक length)
अणु
	काष्ठा fsverity_descriptor *desc;
	माप_प्रकार desc_size;
	पूर्णांक res;

	res = fsverity_get_descriptor(inode, &desc, &desc_size);
	अगर (res)
		वापस res;

	/* करोn't include the signature */
	desc_size = दुरत्व(काष्ठा fsverity_descriptor, signature);
	desc->sig_size = 0;

	res = fsverity_पढ़ो_buffer(buf, offset, length, desc, desc_size);

	kमुक्त(desc);
	वापस res;
पूर्ण

अटल पूर्णांक fsverity_पढ़ो_signature(काष्ठा inode *inode,
				   व्योम __user *buf, u64 offset, पूर्णांक length)
अणु
	काष्ठा fsverity_descriptor *desc;
	माप_प्रकार desc_size;
	पूर्णांक res;

	res = fsverity_get_descriptor(inode, &desc, &desc_size);
	अगर (res)
		वापस res;

	अगर (desc->sig_size == 0) अणु
		res = -ENODATA;
		जाओ out;
	पूर्ण

	/*
	 * Include only the signature.  Note that fsverity_get_descriptor()
	 * alपढ़ोy verअगरied that sig_size is in-bounds.
	 */
	res = fsverity_पढ़ो_buffer(buf, offset, length, desc->signature,
				   le32_to_cpu(desc->sig_size));
out:
	kमुक्त(desc);
	वापस res;
पूर्ण

/**
 * fsverity_ioctl_पढ़ो_metadata() - पढ़ो verity metadata from a file
 * @filp: file to पढ़ो the metadata from
 * @uarg: user poपूर्णांकer to fsverity_पढ़ो_metadata_arg
 *
 * Return: length पढ़ो on success, 0 on खातापूर्ण, -त्रुटि_सं on failure
 */
पूर्णांक fsverity_ioctl_पढ़ो_metadata(काष्ठा file *filp, स्थिर व्योम __user *uarg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	स्थिर काष्ठा fsverity_info *vi;
	काष्ठा fsverity_पढ़ो_metadata_arg arg;
	पूर्णांक length;
	व्योम __user *buf;

	vi = fsverity_get_info(inode);
	अगर (!vi)
		वापस -ENODATA; /* not a verity file */
	/*
	 * Note that we करोn't have to explicitly check that the file is खोलो क्रम
	 * पढ़ोing, since verity files can only be खोलोed क्रम पढ़ोing.
	 */

	अगर (copy_from_user(&arg, uarg, माप(arg)))
		वापस -EFAULT;

	अगर (arg.__reserved)
		वापस -EINVAL;

	/* offset + length must not overflow. */
	अगर (arg.offset + arg.length < arg.offset)
		वापस -EINVAL;

	/* Ensure that the वापस value will fit in पूर्णांक_उच्च. */
	length = min_t(u64, arg.length, पूर्णांक_उच्च);

	buf = u64_to_user_ptr(arg.buf_ptr);

	चयन (arg.metadata_type) अणु
	हाल FS_VERITY_METADATA_TYPE_MERKLE_TREE:
		वापस fsverity_पढ़ो_merkle_tree(inode, vi, buf, arg.offset,
						 length);
	हाल FS_VERITY_METADATA_TYPE_DESCRIPTOR:
		वापस fsverity_पढ़ो_descriptor(inode, buf, arg.offset, length);
	हाल FS_VERITY_METADATA_TYPE_SIGNATURE:
		वापस fsverity_पढ़ो_signature(inode, buf, arg.offset, length);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(fsverity_ioctl_पढ़ो_metadata);
