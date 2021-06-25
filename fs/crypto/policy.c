<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Encryption policy functions क्रम per-file encryption support.
 *
 * Copyright (C) 2015, Google, Inc.
 * Copyright (C) 2015, Motorola Mobility.
 *
 * Originally written by Michael Halcrow, 2015.
 * Modअगरied by Jaegeuk Kim, 2015.
 * Modअगरied by Eric Biggers, 2019 क्रम v2 policy support.
 */

#समावेश <linux/अक्रमom.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/माला.स>
#समावेश <linux/mount.h>
#समावेश "fscrypt_private.h"

/**
 * fscrypt_policies_equal() - check whether two encryption policies are the same
 * @policy1: the first policy
 * @policy2: the second policy
 *
 * Return: %true अगर equal, अन्यथा %false
 */
bool fscrypt_policies_equal(स्थिर जोड़ fscrypt_policy *policy1,
			    स्थिर जोड़ fscrypt_policy *policy2)
अणु
	अगर (policy1->version != policy2->version)
		वापस false;

	वापस !स_भेद(policy1, policy2, fscrypt_policy_size(policy1));
पूर्ण

अटल स्थिर जोड़ fscrypt_policy *
fscrypt_get_dummy_policy(काष्ठा super_block *sb)
अणु
	अगर (!sb->s_cop->get_dummy_policy)
		वापस शून्य;
	वापस sb->s_cop->get_dummy_policy(sb);
पूर्ण

अटल bool fscrypt_valid_enc_modes(u32 contents_mode, u32 filenames_mode)
अणु
	अगर (contents_mode == FSCRYPT_MODE_AES_256_XTS &&
	    filenames_mode == FSCRYPT_MODE_AES_256_CTS)
		वापस true;

	अगर (contents_mode == FSCRYPT_MODE_AES_128_CBC &&
	    filenames_mode == FSCRYPT_MODE_AES_128_CTS)
		वापस true;

	अगर (contents_mode == FSCRYPT_MODE_ADIANTUM &&
	    filenames_mode == FSCRYPT_MODE_ADIANTUM)
		वापस true;

	वापस false;
पूर्ण

अटल bool supported_direct_key_modes(स्थिर काष्ठा inode *inode,
				       u32 contents_mode, u32 filenames_mode)
अणु
	स्थिर काष्ठा fscrypt_mode *mode;

	अगर (contents_mode != filenames_mode) अणु
		fscrypt_warn(inode,
			     "Direct key flag not allowed with different contents and filenames modes");
		वापस false;
	पूर्ण
	mode = &fscrypt_modes[contents_mode];

	अगर (mode->ivsize < दुरत्वend(जोड़ fscrypt_iv, nonce)) अणु
		fscrypt_warn(inode, "Direct key flag not allowed with %s",
			     mode->मित्रly_name);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल bool supported_iv_ino_lblk_policy(स्थिर काष्ठा fscrypt_policy_v2 *policy,
					 स्थिर काष्ठा inode *inode,
					 स्थिर अक्षर *type,
					 पूर्णांक max_ino_bits, पूर्णांक max_lblk_bits)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	पूर्णांक ino_bits = 64, lblk_bits = 64;

	/*
	 * IV_INO_LBLK_* exist only because of hardware limitations, and
	 * currently the only known use हाल क्रम them involves AES-256-XTS.
	 * That's also all we test currently.  For these reasons, क्रम now only
	 * allow AES-256-XTS here.  This can be relaxed later अगर a use हाल क्रम
	 * IV_INO_LBLK_* with other encryption modes arises.
	 */
	अगर (policy->contents_encryption_mode != FSCRYPT_MODE_AES_256_XTS) अणु
		fscrypt_warn(inode,
			     "Can't use %s policy with contents mode other than AES-256-XTS",
			     type);
		वापस false;
	पूर्ण

	/*
	 * It's unsafe to include inode numbers in the IVs अगर the fileप्रणाली can
	 * potentially rक्रमागतber inodes, e.g. via fileप्रणाली shrinking.
	 */
	अगर (!sb->s_cop->has_stable_inodes ||
	    !sb->s_cop->has_stable_inodes(sb)) अणु
		fscrypt_warn(inode,
			     "Can't use %s policy on filesystem '%s' because it doesn't have stable inode numbers",
			     type, sb->s_id);
		वापस false;
	पूर्ण
	अगर (sb->s_cop->get_ino_and_lblk_bits)
		sb->s_cop->get_ino_and_lblk_bits(sb, &ino_bits, &lblk_bits);
	अगर (ino_bits > max_ino_bits) अणु
		fscrypt_warn(inode,
			     "Can't use %s policy on filesystem '%s' because its inode numbers are too long",
			     type, sb->s_id);
		वापस false;
	पूर्ण
	अगर (lblk_bits > max_lblk_bits) अणु
		fscrypt_warn(inode,
			     "Can't use %s policy on filesystem '%s' because its block numbers are too long",
			     type, sb->s_id);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल bool fscrypt_supported_v1_policy(स्थिर काष्ठा fscrypt_policy_v1 *policy,
					स्थिर काष्ठा inode *inode)
अणु
	अगर (!fscrypt_valid_enc_modes(policy->contents_encryption_mode,
				     policy->filenames_encryption_mode)) अणु
		fscrypt_warn(inode,
			     "Unsupported encryption modes (contents %d, filenames %d)",
			     policy->contents_encryption_mode,
			     policy->filenames_encryption_mode);
		वापस false;
	पूर्ण

	अगर (policy->flags & ~(FSCRYPT_POLICY_FLAGS_PAD_MASK |
			      FSCRYPT_POLICY_FLAG_सूचीECT_KEY)) अणु
		fscrypt_warn(inode, "Unsupported encryption flags (0x%02x)",
			     policy->flags);
		वापस false;
	पूर्ण

	अगर ((policy->flags & FSCRYPT_POLICY_FLAG_सूचीECT_KEY) &&
	    !supported_direct_key_modes(inode, policy->contents_encryption_mode,
					policy->filenames_encryption_mode))
		वापस false;

	अगर (IS_CASEFOLDED(inode)) अणु
		/* With v1, there's no way to derive dirhash keys. */
		fscrypt_warn(inode,
			     "v1 policies can't be used on casefolded directories");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool fscrypt_supported_v2_policy(स्थिर काष्ठा fscrypt_policy_v2 *policy,
					स्थिर काष्ठा inode *inode)
अणु
	पूर्णांक count = 0;

	अगर (!fscrypt_valid_enc_modes(policy->contents_encryption_mode,
				     policy->filenames_encryption_mode)) अणु
		fscrypt_warn(inode,
			     "Unsupported encryption modes (contents %d, filenames %d)",
			     policy->contents_encryption_mode,
			     policy->filenames_encryption_mode);
		वापस false;
	पूर्ण

	अगर (policy->flags & ~(FSCRYPT_POLICY_FLAGS_PAD_MASK |
			      FSCRYPT_POLICY_FLAG_सूचीECT_KEY |
			      FSCRYPT_POLICY_FLAG_IV_INO_LBLK_64 |
			      FSCRYPT_POLICY_FLAG_IV_INO_LBLK_32)) अणु
		fscrypt_warn(inode, "Unsupported encryption flags (0x%02x)",
			     policy->flags);
		वापस false;
	पूर्ण

	count += !!(policy->flags & FSCRYPT_POLICY_FLAG_सूचीECT_KEY);
	count += !!(policy->flags & FSCRYPT_POLICY_FLAG_IV_INO_LBLK_64);
	count += !!(policy->flags & FSCRYPT_POLICY_FLAG_IV_INO_LBLK_32);
	अगर (count > 1) अणु
		fscrypt_warn(inode, "Mutually exclusive encryption flags (0x%02x)",
			     policy->flags);
		वापस false;
	पूर्ण

	अगर ((policy->flags & FSCRYPT_POLICY_FLAG_सूचीECT_KEY) &&
	    !supported_direct_key_modes(inode, policy->contents_encryption_mode,
					policy->filenames_encryption_mode))
		वापस false;

	अगर ((policy->flags & FSCRYPT_POLICY_FLAG_IV_INO_LBLK_64) &&
	    !supported_iv_ino_lblk_policy(policy, inode, "IV_INO_LBLK_64",
					  32, 32))
		वापस false;

	/*
	 * IV_INO_LBLK_32 hashes the inode number, so in principle it can
	 * support any ino_bits.  However, currently the inode number is gotten
	 * from inode::i_ino which is 'unsigned long'.  So क्रम now the
	 * implementation limit is 32 bits.
	 */
	अगर ((policy->flags & FSCRYPT_POLICY_FLAG_IV_INO_LBLK_32) &&
	    !supported_iv_ino_lblk_policy(policy, inode, "IV_INO_LBLK_32",
					  32, 32))
		वापस false;

	अगर (स_प्रथम_inv(policy->__reserved, 0, माप(policy->__reserved))) अणु
		fscrypt_warn(inode, "Reserved bits set in encryption policy");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/**
 * fscrypt_supported_policy() - check whether an encryption policy is supported
 * @policy_u: the encryption policy
 * @inode: the inode on which the policy will be used
 *
 * Given an encryption policy, check whether all its encryption modes and other
 * settings are supported by this kernel on the given inode.  (But we करोn't
 * currently करोn't check क्रम crypto API support here, so attempting to use an
 * algorithm not configured पूर्णांकo the crypto API will still fail later.)
 *
 * Return: %true अगर supported, अन्यथा %false
 */
bool fscrypt_supported_policy(स्थिर जोड़ fscrypt_policy *policy_u,
			      स्थिर काष्ठा inode *inode)
अणु
	चयन (policy_u->version) अणु
	हाल FSCRYPT_POLICY_V1:
		वापस fscrypt_supported_v1_policy(&policy_u->v1, inode);
	हाल FSCRYPT_POLICY_V2:
		वापस fscrypt_supported_v2_policy(&policy_u->v2, inode);
	पूर्ण
	वापस false;
पूर्ण

/**
 * fscrypt_new_context() - create a new fscrypt_context
 * @ctx_u: output context
 * @policy_u: input policy
 * @nonce: nonce to use
 *
 * Create an fscrypt_context क्रम an inode that is being asचिन्हित the given
 * encryption policy.  @nonce must be a new अक्रमom nonce.
 *
 * Return: the size of the new context in bytes.
 */
अटल पूर्णांक fscrypt_new_context(जोड़ fscrypt_context *ctx_u,
			       स्थिर जोड़ fscrypt_policy *policy_u,
			       स्थिर u8 nonce[FSCRYPT_खाता_NONCE_SIZE])
अणु
	स_रखो(ctx_u, 0, माप(*ctx_u));

	चयन (policy_u->version) अणु
	हाल FSCRYPT_POLICY_V1: अणु
		स्थिर काष्ठा fscrypt_policy_v1 *policy = &policy_u->v1;
		काष्ठा fscrypt_context_v1 *ctx = &ctx_u->v1;

		ctx->version = FSCRYPT_CONTEXT_V1;
		ctx->contents_encryption_mode =
			policy->contents_encryption_mode;
		ctx->filenames_encryption_mode =
			policy->filenames_encryption_mode;
		ctx->flags = policy->flags;
		स_नकल(ctx->master_key_descriptor,
		       policy->master_key_descriptor,
		       माप(ctx->master_key_descriptor));
		स_नकल(ctx->nonce, nonce, FSCRYPT_खाता_NONCE_SIZE);
		वापस माप(*ctx);
	पूर्ण
	हाल FSCRYPT_POLICY_V2: अणु
		स्थिर काष्ठा fscrypt_policy_v2 *policy = &policy_u->v2;
		काष्ठा fscrypt_context_v2 *ctx = &ctx_u->v2;

		ctx->version = FSCRYPT_CONTEXT_V2;
		ctx->contents_encryption_mode =
			policy->contents_encryption_mode;
		ctx->filenames_encryption_mode =
			policy->filenames_encryption_mode;
		ctx->flags = policy->flags;
		स_नकल(ctx->master_key_identअगरier,
		       policy->master_key_identअगरier,
		       माप(ctx->master_key_identअगरier));
		स_नकल(ctx->nonce, nonce, FSCRYPT_खाता_NONCE_SIZE);
		वापस माप(*ctx);
	पूर्ण
	पूर्ण
	BUG();
पूर्ण

/**
 * fscrypt_policy_from_context() - convert an fscrypt_context to
 *				   an fscrypt_policy
 * @policy_u: output policy
 * @ctx_u: input context
 * @ctx_size: size of input context in bytes
 *
 * Given an fscrypt_context, build the corresponding fscrypt_policy.
 *
 * Return: 0 on success, or -EINVAL अगर the fscrypt_context has an unrecognized
 * version number or size.
 *
 * This करोes *not* validate the settings within the policy itself, e.g. the
 * modes, flags, and reserved bits.  Use fscrypt_supported_policy() क्रम that.
 */
पूर्णांक fscrypt_policy_from_context(जोड़ fscrypt_policy *policy_u,
				स्थिर जोड़ fscrypt_context *ctx_u,
				पूर्णांक ctx_size)
अणु
	स_रखो(policy_u, 0, माप(*policy_u));

	अगर (!fscrypt_context_is_valid(ctx_u, ctx_size))
		वापस -EINVAL;

	चयन (ctx_u->version) अणु
	हाल FSCRYPT_CONTEXT_V1: अणु
		स्थिर काष्ठा fscrypt_context_v1 *ctx = &ctx_u->v1;
		काष्ठा fscrypt_policy_v1 *policy = &policy_u->v1;

		policy->version = FSCRYPT_POLICY_V1;
		policy->contents_encryption_mode =
			ctx->contents_encryption_mode;
		policy->filenames_encryption_mode =
			ctx->filenames_encryption_mode;
		policy->flags = ctx->flags;
		स_नकल(policy->master_key_descriptor,
		       ctx->master_key_descriptor,
		       माप(policy->master_key_descriptor));
		वापस 0;
	पूर्ण
	हाल FSCRYPT_CONTEXT_V2: अणु
		स्थिर काष्ठा fscrypt_context_v2 *ctx = &ctx_u->v2;
		काष्ठा fscrypt_policy_v2 *policy = &policy_u->v2;

		policy->version = FSCRYPT_POLICY_V2;
		policy->contents_encryption_mode =
			ctx->contents_encryption_mode;
		policy->filenames_encryption_mode =
			ctx->filenames_encryption_mode;
		policy->flags = ctx->flags;
		स_नकल(policy->__reserved, ctx->__reserved,
		       माप(policy->__reserved));
		स_नकल(policy->master_key_identअगरier,
		       ctx->master_key_identअगरier,
		       माप(policy->master_key_identअगरier));
		वापस 0;
	पूर्ण
	पूर्ण
	/* unreachable */
	वापस -EINVAL;
पूर्ण

/* Retrieve an inode's encryption policy */
अटल पूर्णांक fscrypt_get_policy(काष्ठा inode *inode, जोड़ fscrypt_policy *policy)
अणु
	स्थिर काष्ठा fscrypt_info *ci;
	जोड़ fscrypt_context ctx;
	पूर्णांक ret;

	ci = fscrypt_get_info(inode);
	अगर (ci) अणु
		/* key available, use the cached policy */
		*policy = ci->ci_policy;
		वापस 0;
	पूर्ण

	अगर (!IS_ENCRYPTED(inode))
		वापस -ENODATA;

	ret = inode->i_sb->s_cop->get_context(inode, &ctx, माप(ctx));
	अगर (ret < 0)
		वापस (ret == -दुस्फल) ? -EINVAL : ret;

	वापस fscrypt_policy_from_context(policy, &ctx, ret);
पूर्ण

अटल पूर्णांक set_encryption_policy(काष्ठा inode *inode,
				 स्थिर जोड़ fscrypt_policy *policy)
अणु
	u8 nonce[FSCRYPT_खाता_NONCE_SIZE];
	जोड़ fscrypt_context ctx;
	पूर्णांक ctxsize;
	पूर्णांक err;

	अगर (!fscrypt_supported_policy(policy, inode))
		वापस -EINVAL;

	चयन (policy->version) अणु
	हाल FSCRYPT_POLICY_V1:
		/*
		 * The original encryption policy version provided no way of
		 * verअगरying that the correct master key was supplied, which was
		 * insecure in scenarios where multiple users have access to the
		 * same encrypted files (even just पढ़ो-only access).  The new
		 * encryption policy version fixes this and also implies use of
		 * an improved key derivation function and allows non-root users
		 * to securely हटाओ keys.  So as दीर्घ as compatibility with
		 * old kernels isn't required, it is recommended to use the new
		 * policy version क्रम all new encrypted directories.
		 */
		pr_warn_once("%s (pid %d) is setting deprecated v1 encryption policy; recommend upgrading to v2.\n",
			     current->comm, current->pid);
		अवरोध;
	हाल FSCRYPT_POLICY_V2:
		err = fscrypt_verअगरy_key_added(inode->i_sb,
					       policy->v2.master_key_identअगरier);
		अगर (err)
			वापस err;
		अगर (policy->v2.flags & FSCRYPT_POLICY_FLAG_IV_INO_LBLK_32)
			pr_warn_once("%s (pid %d) is setting an IV_INO_LBLK_32 encryption policy.  This should only be used if there are certain hardware limitations.\n",
				     current->comm, current->pid);
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	get_अक्रमom_bytes(nonce, FSCRYPT_खाता_NONCE_SIZE);
	ctxsize = fscrypt_new_context(&ctx, policy, nonce);

	वापस inode->i_sb->s_cop->set_context(inode, &ctx, ctxsize, शून्य);
पूर्ण

पूर्णांक fscrypt_ioctl_set_policy(काष्ठा file *filp, स्थिर व्योम __user *arg)
अणु
	जोड़ fscrypt_policy policy;
	जोड़ fscrypt_policy existing_policy;
	काष्ठा inode *inode = file_inode(filp);
	u8 version;
	पूर्णांक size;
	पूर्णांक ret;

	अगर (get_user(policy.version, (स्थिर u8 __user *)arg))
		वापस -EFAULT;

	size = fscrypt_policy_size(&policy);
	अगर (size <= 0)
		वापस -EINVAL;

	/*
	 * We should just copy the reमुख्यing 'size - 1' bytes here, but a
	 * bizarre bug in gcc 7 and earlier (fixed by gcc r255731) causes gcc to
	 * think that size can be 0 here (despite the check above!) *and* that
	 * it's a compile-समय स्थिरant.  Thus it would think copy_from_user()
	 * is passed compile-समय स्थिरant अच_दीर्घ_उच्च, causing the compile-समय
	 * buffer overflow check to fail, अवरोधing the build. This only occurred
	 * when building an i386 kernel with -Os and branch profiling enabled.
	 *
	 * Work around it by just copying the first byte again...
	 */
	version = policy.version;
	अगर (copy_from_user(&policy, arg, size))
		वापस -EFAULT;
	policy.version = version;

	अगर (!inode_owner_or_capable(&init_user_ns, inode))
		वापस -EACCES;

	ret = mnt_want_ग_लिखो_file(filp);
	अगर (ret)
		वापस ret;

	inode_lock(inode);

	ret = fscrypt_get_policy(inode, &existing_policy);
	अगर (ret == -ENODATA) अणु
		अगर (!S_ISसूची(inode->i_mode))
			ret = -ENOTसूची;
		अन्यथा अगर (IS_DEADसूची(inode))
			ret = -ENOENT;
		अन्यथा अगर (!inode->i_sb->s_cop->empty_dir(inode))
			ret = -ENOTEMPTY;
		अन्यथा
			ret = set_encryption_policy(inode, &policy);
	पूर्ण अन्यथा अगर (ret == -EINVAL ||
		   (ret == 0 && !fscrypt_policies_equal(&policy,
							&existing_policy))) अणु
		/* The file alपढ़ोy uses a dअगरferent encryption policy. */
		ret = -EEXIST;
	पूर्ण

	inode_unlock(inode);

	mnt_drop_ग_लिखो_file(filp);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(fscrypt_ioctl_set_policy);

/* Original ioctl version; can only get the original policy version */
पूर्णांक fscrypt_ioctl_get_policy(काष्ठा file *filp, व्योम __user *arg)
अणु
	जोड़ fscrypt_policy policy;
	पूर्णांक err;

	err = fscrypt_get_policy(file_inode(filp), &policy);
	अगर (err)
		वापस err;

	अगर (policy.version != FSCRYPT_POLICY_V1)
		वापस -EINVAL;

	अगर (copy_to_user(arg, &policy, माप(policy.v1)))
		वापस -EFAULT;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(fscrypt_ioctl_get_policy);

/* Extended ioctl version; can get policies of any version */
पूर्णांक fscrypt_ioctl_get_policy_ex(काष्ठा file *filp, व्योम __user *uarg)
अणु
	काष्ठा fscrypt_get_policy_ex_arg arg;
	जोड़ fscrypt_policy *policy = (जोड़ fscrypt_policy *)&arg.policy;
	माप_प्रकार policy_size;
	पूर्णांक err;

	/* arg is policy_size, then policy */
	BUILD_BUG_ON(दुरत्व(typeof(arg), policy_size) != 0);
	BUILD_BUG_ON(दुरत्वend(typeof(arg), policy_size) !=
		     दुरत्व(typeof(arg), policy));
	BUILD_BUG_ON(माप(arg.policy) != माप(*policy));

	err = fscrypt_get_policy(file_inode(filp), policy);
	अगर (err)
		वापस err;
	policy_size = fscrypt_policy_size(policy);

	अगर (copy_from_user(&arg, uarg, माप(arg.policy_size)))
		वापस -EFAULT;

	अगर (policy_size > arg.policy_size)
		वापस -EOVERFLOW;
	arg.policy_size = policy_size;

	अगर (copy_to_user(uarg, &arg, माप(arg.policy_size) + policy_size))
		वापस -EFAULT;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(fscrypt_ioctl_get_policy_ex);

/* FS_IOC_GET_ENCRYPTION_NONCE: retrieve file's encryption nonce क्रम testing */
पूर्णांक fscrypt_ioctl_get_nonce(काष्ठा file *filp, व्योम __user *arg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	जोड़ fscrypt_context ctx;
	पूर्णांक ret;

	ret = inode->i_sb->s_cop->get_context(inode, &ctx, माप(ctx));
	अगर (ret < 0)
		वापस ret;
	अगर (!fscrypt_context_is_valid(&ctx, ret))
		वापस -EINVAL;
	अगर (copy_to_user(arg, fscrypt_context_nonce(&ctx),
			 FSCRYPT_खाता_NONCE_SIZE))
		वापस -EFAULT;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(fscrypt_ioctl_get_nonce);

/**
 * fscrypt_has_permitted_context() - is a file's encryption policy permitted
 *				     within its directory?
 *
 * @parent: inode क्रम parent directory
 * @child: inode क्रम file being looked up, खोलोed, or linked पूर्णांकo @parent
 *
 * Fileप्रणालीs must call this beक्रमe permitting access to an inode in a
 * situation where the parent directory is encrypted (either beक्रमe allowing
 * ->lookup() to succeed, or क्रम a regular file beक्रमe allowing it to be खोलोed)
 * and beक्रमe any operation that involves linking an inode पूर्णांकo an encrypted
 * directory, including link, नाम, and cross नाम.  It enक्रमces the
 * स्थिरraपूर्णांक that within a given encrypted directory tree, all files use the
 * same encryption policy.  The pre-access check is needed to detect potentially
 * malicious offline violations of this स्थिरraपूर्णांक, जबतक the link and नाम
 * checks are needed to prevent online violations of this स्थिरraपूर्णांक.
 *
 * Return: 1 अगर permitted, 0 अगर क्रमbidden.
 */
पूर्णांक fscrypt_has_permitted_context(काष्ठा inode *parent, काष्ठा inode *child)
अणु
	जोड़ fscrypt_policy parent_policy, child_policy;
	पूर्णांक err, err1, err2;

	/* No restrictions on file types which are never encrypted */
	अगर (!S_ISREG(child->i_mode) && !S_ISसूची(child->i_mode) &&
	    !S_ISLNK(child->i_mode))
		वापस 1;

	/* No restrictions अगर the parent directory is unencrypted */
	अगर (!IS_ENCRYPTED(parent))
		वापस 1;

	/* Encrypted directories must not contain unencrypted files */
	अगर (!IS_ENCRYPTED(child))
		वापस 0;

	/*
	 * Both parent and child are encrypted, so verअगरy they use the same
	 * encryption policy.  Compare the fscrypt_info काष्ठाs अगर the keys are
	 * available, otherwise retrieve and compare the fscrypt_contexts.
	 *
	 * Note that the fscrypt_context retrieval will be required frequently
	 * when accessing an encrypted directory tree without the key.
	 * Perक्रमmance-wise this is not a big deal because we alपढ़ोy करोn't
	 * really optimize क्रम file access without the key (to the extent that
	 * such access is even possible), given that any attempted access
	 * alपढ़ोy causes a fscrypt_context retrieval and keyring search.
	 *
	 * In any हाल, अगर an unexpected error occurs, fall back to "forbidden".
	 */

	err = fscrypt_get_encryption_info(parent, true);
	अगर (err)
		वापस 0;
	err = fscrypt_get_encryption_info(child, true);
	अगर (err)
		वापस 0;

	err1 = fscrypt_get_policy(parent, &parent_policy);
	err2 = fscrypt_get_policy(child, &child_policy);

	/*
	 * Allow the हाल where the parent and child both have an unrecognized
	 * encryption policy, so that files with an unrecognized encryption
	 * policy can be deleted.
	 */
	अगर (err1 == -EINVAL && err2 == -EINVAL)
		वापस 1;

	अगर (err1 || err2)
		वापस 0;

	वापस fscrypt_policies_equal(&parent_policy, &child_policy);
पूर्ण
EXPORT_SYMBOL(fscrypt_has_permitted_context);

/*
 * Return the encryption policy that new files in the directory will inherit, or
 * शून्य अगर none, or an ERR_PTR() on error.  If the directory is encrypted, also
 * ensure that its key is set up, so that the new filename can be encrypted.
 */
स्थिर जोड़ fscrypt_policy *fscrypt_policy_to_inherit(काष्ठा inode *dir)
अणु
	पूर्णांक err;

	अगर (IS_ENCRYPTED(dir)) अणु
		err = fscrypt_require_key(dir);
		अगर (err)
			वापस ERR_PTR(err);
		वापस &dir->i_crypt_info->ci_policy;
	पूर्ण

	वापस fscrypt_get_dummy_policy(dir->i_sb);
पूर्ण

/**
 * fscrypt_set_context() - Set the fscrypt context of a new inode
 * @inode: a new inode
 * @fs_data: निजी data given by FS and passed to ->set_context()
 *
 * This should be called after fscrypt_prepare_new_inode(), generally during a
 * fileप्रणाली transaction.  Everything here must be %GFP_NOFS-safe.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
पूर्णांक fscrypt_set_context(काष्ठा inode *inode, व्योम *fs_data)
अणु
	काष्ठा fscrypt_info *ci = inode->i_crypt_info;
	जोड़ fscrypt_context ctx;
	पूर्णांक ctxsize;

	/* fscrypt_prepare_new_inode() should have set up the key alपढ़ोy. */
	अगर (WARN_ON_ONCE(!ci))
		वापस -ENOKEY;

	BUILD_BUG_ON(माप(ctx) != FSCRYPT_SET_CONTEXT_MAX_SIZE);
	ctxsize = fscrypt_new_context(&ctx, &ci->ci_policy, ci->ci_nonce);

	/*
	 * This may be the first समय the inode number is available, so करो any
	 * delayed key setup that requires the inode number.
	 */
	अगर (ci->ci_policy.version == FSCRYPT_POLICY_V2 &&
	    (ci->ci_policy.v2.flags & FSCRYPT_POLICY_FLAG_IV_INO_LBLK_32)) अणु
		स्थिर काष्ठा fscrypt_master_key *mk =
			ci->ci_master_key->payload.data[0];

		fscrypt_hash_inode_number(ci, mk);
	पूर्ण

	वापस inode->i_sb->s_cop->set_context(inode, &ctx, ctxsize, fs_data);
पूर्ण
EXPORT_SYMBOL_GPL(fscrypt_set_context);

/**
 * fscrypt_set_test_dummy_encryption() - handle '-o test_dummy_encryption'
 * @sb: the fileप्रणाली on which test_dummy_encryption is being specअगरied
 * @arg: the argument to the test_dummy_encryption option.  May be शून्य.
 * @dummy_policy: the fileप्रणाली's current dummy policy (input/output, see
 *		  below)
 *
 * Handle the test_dummy_encryption mount option by creating a dummy encryption
 * policy, saving it in @dummy_policy, and adding the corresponding dummy
 * encryption key to the fileप्रणाली.  If the @dummy_policy is alपढ़ोy set, then
 * instead validate that it matches @arg.  Don't support changing it via
 * remount, as that is dअगरficult to करो safely.
 *
 * Return: 0 on success (dummy policy set, or the same policy is alपढ़ोy set);
 *         -EEXIST अगर a dअगरferent dummy policy is alपढ़ोy set;
 *         or another -त्रुटि_सं value.
 */
पूर्णांक fscrypt_set_test_dummy_encryption(काष्ठा super_block *sb, स्थिर अक्षर *arg,
				      काष्ठा fscrypt_dummy_policy *dummy_policy)
अणु
	काष्ठा fscrypt_key_specअगरier key_spec = अणु 0 पूर्ण;
	पूर्णांक version;
	जोड़ fscrypt_policy *policy = शून्य;
	पूर्णांक err;

	अगर (!arg)
		arg = "v2";

	अगर (!म_भेद(arg, "v1")) अणु
		version = FSCRYPT_POLICY_V1;
		key_spec.type = FSCRYPT_KEY_SPEC_TYPE_DESCRIPTOR;
		स_रखो(key_spec.u.descriptor, 0x42,
		       FSCRYPT_KEY_DESCRIPTOR_SIZE);
	पूर्ण अन्यथा अगर (!म_भेद(arg, "v2")) अणु
		version = FSCRYPT_POLICY_V2;
		key_spec.type = FSCRYPT_KEY_SPEC_TYPE_IDENTIFIER;
		/* key_spec.u.identअगरier माला_लो filled in when adding the key */
	पूर्ण अन्यथा अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	policy = kzalloc(माप(*policy), GFP_KERNEL);
	अगर (!policy) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	err = fscrypt_add_test_dummy_key(sb, &key_spec);
	अगर (err)
		जाओ out;

	policy->version = version;
	चयन (policy->version) अणु
	हाल FSCRYPT_POLICY_V1:
		policy->v1.contents_encryption_mode = FSCRYPT_MODE_AES_256_XTS;
		policy->v1.filenames_encryption_mode = FSCRYPT_MODE_AES_256_CTS;
		स_नकल(policy->v1.master_key_descriptor, key_spec.u.descriptor,
		       FSCRYPT_KEY_DESCRIPTOR_SIZE);
		अवरोध;
	हाल FSCRYPT_POLICY_V2:
		policy->v2.contents_encryption_mode = FSCRYPT_MODE_AES_256_XTS;
		policy->v2.filenames_encryption_mode = FSCRYPT_MODE_AES_256_CTS;
		स_नकल(policy->v2.master_key_identअगरier, key_spec.u.identअगरier,
		       FSCRYPT_KEY_IDENTIFIER_SIZE);
		अवरोध;
	शेष:
		WARN_ON(1);
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (dummy_policy->policy) अणु
		अगर (fscrypt_policies_equal(policy, dummy_policy->policy))
			err = 0;
		अन्यथा
			err = -EEXIST;
		जाओ out;
	पूर्ण
	dummy_policy->policy = policy;
	policy = शून्य;
	err = 0;
out:
	kमुक्त(policy);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(fscrypt_set_test_dummy_encryption);

/**
 * fscrypt_show_test_dummy_encryption() - show '-o test_dummy_encryption'
 * @seq: the seq_file to prपूर्णांक the option to
 * @sep: the separator अक्षरacter to use
 * @sb: the fileप्रणाली whose options are being shown
 *
 * Show the test_dummy_encryption mount option, अगर it was specअगरied.
 * This is मुख्यly used क्रम /proc/mounts.
 */
व्योम fscrypt_show_test_dummy_encryption(काष्ठा seq_file *seq, अक्षर sep,
					काष्ठा super_block *sb)
अणु
	स्थिर जोड़ fscrypt_policy *policy = fscrypt_get_dummy_policy(sb);
	पूर्णांक vers;

	अगर (!policy)
		वापस;

	vers = policy->version;
	अगर (vers == FSCRYPT_POLICY_V1) /* Handle numbering quirk */
		vers = 1;

	seq_म_लिखो(seq, "%ctest_dummy_encryption=v%d", sep, vers);
पूर्ण
EXPORT_SYMBOL_GPL(fscrypt_show_test_dummy_encryption);
