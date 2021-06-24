<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Verअगरication of builtin signatures
 *
 * Copyright 2019 Google LLC
 */

#समावेश "fsverity_private.h"

#समावेश <linux/cred.h>
#समावेश <linux/key.h>
#समावेश <linux/slab.h>
#समावेश <linux/verअगरication.h>

/*
 * /proc/sys/fs/verity/require_signatures
 * If 1, all verity files must have a valid builtin signature.
 */
अटल पूर्णांक fsverity_require_signatures;

/*
 * Keyring that contains the trusted X.509 certअगरicates.
 *
 * Only root (kuid=0) can modअगरy this.  Also, root may use
 * keyctl_restrict_keyring() to prevent any more additions.
 */
अटल काष्ठा key *fsverity_keyring;

/**
 * fsverity_verअगरy_signature() - check a verity file's signature
 * @vi: the file's fsverity_info
 * @signature: the file's built-in signature
 * @sig_size: size of signature in bytes, or 0 अगर no signature
 *
 * If the file includes a signature of its fs-verity file digest, verअगरy it
 * against the certअगरicates in the fs-verity keyring.
 *
 * Return: 0 on success (signature valid or not required); -त्रुटि_सं on failure
 */
पूर्णांक fsverity_verअगरy_signature(स्थिर काष्ठा fsverity_info *vi,
			      स्थिर u8 *signature, माप_प्रकार sig_size)
अणु
	स्थिर काष्ठा inode *inode = vi->inode;
	स्थिर काष्ठा fsverity_hash_alg *hash_alg = vi->tree_params.hash_alg;
	काष्ठा fsverity_क्रमmatted_digest *d;
	पूर्णांक err;

	अगर (sig_size == 0) अणु
		अगर (fsverity_require_signatures) अणु
			fsverity_err(inode,
				     "require_signatures=1, rejecting unsigned file!");
			वापस -EPERM;
		पूर्ण
		वापस 0;
	पूर्ण

	d = kzalloc(माप(*d) + hash_alg->digest_size, GFP_KERNEL);
	अगर (!d)
		वापस -ENOMEM;
	स_नकल(d->magic, "FSVerity", 8);
	d->digest_algorithm = cpu_to_le16(hash_alg - fsverity_hash_algs);
	d->digest_size = cpu_to_le16(hash_alg->digest_size);
	स_नकल(d->digest, vi->file_digest, hash_alg->digest_size);

	err = verअगरy_pkcs7_signature(d, माप(*d) + hash_alg->digest_size,
				     signature, sig_size, fsverity_keyring,
				     VERIFYING_UNSPECIFIED_SIGNATURE,
				     शून्य, शून्य);
	kमुक्त(d);

	अगर (err) अणु
		अगर (err == -ENOKEY)
			fsverity_err(inode,
				     "File's signing cert isn't in the fs-verity keyring");
		अन्यथा अगर (err == -EKEYREJECTED)
			fsverity_err(inode, "Incorrect file signature");
		अन्यथा अगर (err == -EBADMSG)
			fsverity_err(inode, "Malformed file signature");
		अन्यथा
			fsverity_err(inode, "Error %d verifying file signature",
				     err);
		वापस err;
	पूर्ण

	pr_debug("Valid signature for file digest %s:%*phN\n",
		 hash_alg->name, hash_alg->digest_size, vi->file_digest);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SYSCTL
अटल काष्ठा ctl_table_header *fsverity_sysctl_header;

अटल स्थिर काष्ठा ctl_path fsverity_sysctl_path[] = अणु
	अणु .procname = "fs", पूर्ण,
	अणु .procname = "verity", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table fsverity_sysctl_table[] = अणु
	अणु
		.procname       = "require_signatures",
		.data           = &fsverity_require_signatures,
		.maxlen         = माप(पूर्णांक),
		.mode           = 0644,
		.proc_handler   = proc_करोपूर्णांकvec_minmax,
		.extra1         = SYSCTL_ZERO,
		.extra2         = SYSCTL_ONE,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक __init fsverity_sysctl_init(व्योम)
अणु
	fsverity_sysctl_header = रेजिस्टर_sysctl_paths(fsverity_sysctl_path,
						       fsverity_sysctl_table);
	अगर (!fsverity_sysctl_header) अणु
		pr_err("sysctl registration failed!\n");
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण
#अन्यथा /* !CONFIG_SYSCTL */
अटल अंतरभूत पूर्णांक __init fsverity_sysctl_init(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* !CONFIG_SYSCTL */

पूर्णांक __init fsverity_init_signature(व्योम)
अणु
	काष्ठा key *ring;
	पूर्णांक err;

	ring = keyring_alloc(".fs-verity", KUIDT_INIT(0), KGIDT_INIT(0),
			     current_cred(), KEY_POS_SEARCH |
				KEY_USR_VIEW | KEY_USR_READ | KEY_USR_WRITE |
				KEY_USR_SEARCH | KEY_USR_SETATTR,
			     KEY_ALLOC_NOT_IN_QUOTA, शून्य, शून्य);
	अगर (IS_ERR(ring))
		वापस PTR_ERR(ring);

	err = fsverity_sysctl_init();
	अगर (err)
		जाओ err_put_ring;

	fsverity_keyring = ring;
	वापस 0;

err_put_ring:
	key_put(ring);
	वापस err;
पूर्ण
