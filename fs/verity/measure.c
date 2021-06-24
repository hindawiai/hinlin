<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Ioctl to get a verity file's digest
 *
 * Copyright 2019 Google LLC
 */

#समावेश "fsverity_private.h"

#समावेश <linux/uaccess.h>

/**
 * fsverity_ioctl_measure() - get a verity file's digest
 * @filp: file to get digest of
 * @_uarg: user poपूर्णांकer to fsverity_digest
 *
 * Retrieve the file digest that the kernel is enक्रमcing क्रम पढ़ोs from a verity
 * file.  See the "FS_IOC_MEASURE_VERITY" section of
 * Documentation/fileप्रणालीs/fsverity.rst क्रम the करोcumentation.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
पूर्णांक fsverity_ioctl_measure(काष्ठा file *filp, व्योम __user *_uarg)
अणु
	स्थिर काष्ठा inode *inode = file_inode(filp);
	काष्ठा fsverity_digest __user *uarg = _uarg;
	स्थिर काष्ठा fsverity_info *vi;
	स्थिर काष्ठा fsverity_hash_alg *hash_alg;
	काष्ठा fsverity_digest arg;

	vi = fsverity_get_info(inode);
	अगर (!vi)
		वापस -ENODATA; /* not a verity file */
	hash_alg = vi->tree_params.hash_alg;

	/*
	 * The user specअगरies the digest_size their buffer has space क्रम; we can
	 * वापस the digest अगर it fits in the available space.  We ग_लिखो back
	 * the actual size, which may be लघुer than the user-specअगरied size.
	 */

	अगर (get_user(arg.digest_size, &uarg->digest_size))
		वापस -EFAULT;
	अगर (arg.digest_size < hash_alg->digest_size)
		वापस -EOVERFLOW;

	स_रखो(&arg, 0, माप(arg));
	arg.digest_algorithm = hash_alg - fsverity_hash_algs;
	arg.digest_size = hash_alg->digest_size;

	अगर (copy_to_user(uarg, &arg, माप(arg)))
		वापस -EFAULT;

	अगर (copy_to_user(uarg->digest, vi->file_digest, hash_alg->digest_size))
		वापस -EFAULT;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(fsverity_ioctl_measure);
