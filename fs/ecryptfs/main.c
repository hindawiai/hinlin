<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * eCryptfs: Linux fileप्रणाली encryption layer
 *
 * Copyright (C) 1997-2003 Erez Zaकरोk
 * Copyright (C) 2001-2003 Stony Brook University
 * Copyright (C) 2004-2007 International Business Machines Corp.
 *   Author(s): Michael A. Halcrow <mahalcro@us.ibm.com>
 *              Michael C. Thompson <mcthomps@us.ibm.com>
 *              Tyler Hicks <code@tyhicks.com>
 */

#समावेश <linux/dcache.h>
#समावेश <linux/file.h>
#समावेश <linux/module.h>
#समावेश <linux/namei.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/mount.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/key.h>
#समावेश <linux/parser.h>
#समावेश <linux/fs_stack.h>
#समावेश <linux/slab.h>
#समावेश <linux/magic.h>
#समावेश "ecryptfs_kernel.h"

/*
 * Module parameter that defines the ecryptfs_verbosity level.
 */
पूर्णांक ecryptfs_verbosity = 0;

module_param(ecryptfs_verbosity, पूर्णांक, 0);
MODULE_PARM_DESC(ecryptfs_verbosity,
		 "Initial verbosity level (0 or 1; defaults to "
		 "0, which is Quiet)");

/*
 * Module parameter that defines the number of message buffer elements
 */
अचिन्हित पूर्णांक ecryptfs_message_buf_len = ECRYPTFS_DEFAULT_MSG_CTX_ELEMS;

module_param(ecryptfs_message_buf_len, uपूर्णांक, 0);
MODULE_PARM_DESC(ecryptfs_message_buf_len,
		 "Number of message buffer elements");

/*
 * Module parameter that defines the maximum guaranteed amount of समय to रुको
 * क्रम a response from ecryptfsd.  The actual sleep समय will be, more than
 * likely, a small amount greater than this specअगरied value, but only less अगर
 * the message successfully arrives.
 */
चिन्हित दीर्घ ecryptfs_message_रुको_समयout = ECRYPTFS_MAX_MSG_CTX_TTL / HZ;

module_param(ecryptfs_message_रुको_समयout, दीर्घ, 0);
MODULE_PARM_DESC(ecryptfs_message_रुको_समयout,
		 "Maximum number of seconds that an operation will "
		 "sleep while waiting for a message response from "
		 "userspace");

/*
 * Module parameter that is an estimate of the maximum number of users
 * that will be concurrently using eCryptfs. Set this to the right
 * value to balance perक्रमmance and memory use.
 */
अचिन्हित पूर्णांक ecryptfs_number_of_users = ECRYPTFS_DEFAULT_NUM_USERS;

module_param(ecryptfs_number_of_users, uपूर्णांक, 0);
MODULE_PARM_DESC(ecryptfs_number_of_users, "An estimate of the number of "
		 "concurrent users of eCryptfs");

व्योम __ecryptfs_prपूर्णांकk(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	बहु_शुरू(args, fmt);
	अगर (fmt[1] == '7') अणु /* KERN_DEBUG */
		अगर (ecryptfs_verbosity >= 1)
			vprपूर्णांकk(fmt, args);
	पूर्ण अन्यथा
		vprपूर्णांकk(fmt, args);
	बहु_पूर्ण(args);
पूर्ण

/*
 * ecryptfs_init_lower_file
 * @ecryptfs_dentry: Fully initialized eCryptfs dentry object, with
 *                   the lower dentry and the lower mount set
 *
 * eCryptfs only ever keeps a single खोलो file क्रम every lower
 * inode. All I/O operations to the lower inode occur through that
 * file. When the first eCryptfs dentry that पूर्णांकerposes with the first
 * lower dentry क्रम that inode is created, this function creates the
 * lower file काष्ठा and associates it with the eCryptfs
 * inode. When all eCryptfs files associated with the inode are released, the
 * file is बंदd.
 *
 * The lower file will be खोलोed with पढ़ो/ग_लिखो permissions, अगर
 * possible. Otherwise, it is खोलोed पढ़ो-only.
 *
 * This function करोes nothing अगर a lower file is alपढ़ोy
 * associated with the eCryptfs inode.
 *
 * Returns zero on success; non-zero otherwise
 */
अटल पूर्णांक ecryptfs_init_lower_file(काष्ठा dentry *dentry,
				    काष्ठा file **lower_file)
अणु
	स्थिर काष्ठा cred *cred = current_cred();
	काष्ठा path *path = ecryptfs_dentry_to_lower_path(dentry);
	पूर्णांक rc;

	rc = ecryptfs_privileged_खोलो(lower_file, path->dentry, path->mnt,
				      cred);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "Error opening lower file "
		       "for lower_dentry [0x%p] and lower_mnt [0x%p]; "
		       "rc = [%d]\n", path->dentry, path->mnt, rc);
		(*lower_file) = शून्य;
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक ecryptfs_get_lower_file(काष्ठा dentry *dentry, काष्ठा inode *inode)
अणु
	काष्ठा ecryptfs_inode_info *inode_info;
	पूर्णांक count, rc = 0;

	inode_info = ecryptfs_inode_to_निजी(inode);
	mutex_lock(&inode_info->lower_file_mutex);
	count = atomic_inc_वापस(&inode_info->lower_file_count);
	अगर (WARN_ON_ONCE(count < 1))
		rc = -EINVAL;
	अन्यथा अगर (count == 1) अणु
		rc = ecryptfs_init_lower_file(dentry,
					      &inode_info->lower_file);
		अगर (rc)
			atomic_set(&inode_info->lower_file_count, 0);
	पूर्ण
	mutex_unlock(&inode_info->lower_file_mutex);
	वापस rc;
पूर्ण

व्योम ecryptfs_put_lower_file(काष्ठा inode *inode)
अणु
	काष्ठा ecryptfs_inode_info *inode_info;

	inode_info = ecryptfs_inode_to_निजी(inode);
	अगर (atomic_dec_and_mutex_lock(&inode_info->lower_file_count,
				      &inode_info->lower_file_mutex)) अणु
		filemap_ग_लिखो_and_रुको(inode->i_mapping);
		fput(inode_info->lower_file);
		inode_info->lower_file = शून्य;
		mutex_unlock(&inode_info->lower_file_mutex);
	पूर्ण
पूर्ण

क्रमागत अणु ecryptfs_opt_sig, ecryptfs_opt_ecryptfs_sig,
       ecryptfs_opt_cipher, ecryptfs_opt_ecryptfs_cipher,
       ecryptfs_opt_ecryptfs_key_bytes,
       ecryptfs_opt_passthrough, ecryptfs_opt_xattr_metadata,
       ecryptfs_opt_encrypted_view, ecryptfs_opt_fnek_sig,
       ecryptfs_opt_fn_cipher, ecryptfs_opt_fn_cipher_key_bytes,
       ecryptfs_opt_unlink_sigs, ecryptfs_opt_mount_auth_tok_only,
       ecryptfs_opt_check_dev_ruid,
       ecryptfs_opt_err पूर्ण;

अटल स्थिर match_table_t tokens = अणु
	अणुecryptfs_opt_sig, "sig=%s"पूर्ण,
	अणुecryptfs_opt_ecryptfs_sig, "ecryptfs_sig=%s"पूर्ण,
	अणुecryptfs_opt_cipher, "cipher=%s"पूर्ण,
	अणुecryptfs_opt_ecryptfs_cipher, "ecryptfs_cipher=%s"पूर्ण,
	अणुecryptfs_opt_ecryptfs_key_bytes, "ecryptfs_key_bytes=%u"पूर्ण,
	अणुecryptfs_opt_passthrough, "ecryptfs_passthrough"पूर्ण,
	अणुecryptfs_opt_xattr_metadata, "ecryptfs_xattr_metadata"पूर्ण,
	अणुecryptfs_opt_encrypted_view, "ecryptfs_encrypted_view"पूर्ण,
	अणुecryptfs_opt_fnek_sig, "ecryptfs_fnek_sig=%s"पूर्ण,
	अणुecryptfs_opt_fn_cipher, "ecryptfs_fn_cipher=%s"पूर्ण,
	अणुecryptfs_opt_fn_cipher_key_bytes, "ecryptfs_fn_key_bytes=%u"पूर्ण,
	अणुecryptfs_opt_unlink_sigs, "ecryptfs_unlink_sigs"पूर्ण,
	अणुecryptfs_opt_mount_auth_tok_only, "ecryptfs_mount_auth_tok_only"पूर्ण,
	अणुecryptfs_opt_check_dev_ruid, "ecryptfs_check_dev_ruid"पूर्ण,
	अणुecryptfs_opt_err, शून्यपूर्ण
पूर्ण;

अटल पूर्णांक ecryptfs_init_global_auth_toks(
	काष्ठा ecryptfs_mount_crypt_stat *mount_crypt_stat)
अणु
	काष्ठा ecryptfs_global_auth_tok *global_auth_tok;
	काष्ठा ecryptfs_auth_tok *auth_tok;
	पूर्णांक rc = 0;

	list_क्रम_each_entry(global_auth_tok,
			    &mount_crypt_stat->global_auth_tok_list,
			    mount_crypt_stat_list) अणु
		rc = ecryptfs_keyring_auth_tok_क्रम_sig(
			&global_auth_tok->global_auth_tok_key, &auth_tok,
			global_auth_tok->sig);
		अगर (rc) अणु
			prपूर्णांकk(KERN_ERR "Could not find valid key in user "
			       "session keyring for sig specified in mount "
			       "option: [%s]\n", global_auth_tok->sig);
			global_auth_tok->flags |= ECRYPTFS_AUTH_TOK_INVALID;
			जाओ out;
		पूर्ण अन्यथा अणु
			global_auth_tok->flags &= ~ECRYPTFS_AUTH_TOK_INVALID;
			up_ग_लिखो(&(global_auth_tok->global_auth_tok_key)->sem);
		पूर्ण
	पूर्ण
out:
	वापस rc;
पूर्ण

अटल व्योम ecryptfs_init_mount_crypt_stat(
	काष्ठा ecryptfs_mount_crypt_stat *mount_crypt_stat)
अणु
	स_रखो((व्योम *)mount_crypt_stat, 0,
	       माप(काष्ठा ecryptfs_mount_crypt_stat));
	INIT_LIST_HEAD(&mount_crypt_stat->global_auth_tok_list);
	mutex_init(&mount_crypt_stat->global_auth_tok_list_mutex);
	mount_crypt_stat->flags |= ECRYPTFS_MOUNT_CRYPT_STAT_INITIALIZED;
पूर्ण

/**
 * ecryptfs_parse_options
 * @sbi: The ecryptfs super block
 * @options: The options passed to the kernel
 * @check_ruid: set to 1 अगर device uid should be checked against the ruid
 *
 * Parse mount options:
 * debug=N 	   - ecryptfs_verbosity level क्रम debug output
 * sig=XXX	   - description(signature) of the key to use
 *
 * Returns the dentry object of the lower-level (lower/पूर्णांकerposed)
 * directory; We want to mount our stackable file प्रणाली on top of
 * that lower directory.
 *
 * The signature of the key to use must be the description of a key
 * alपढ़ोy in the keyring. Mounting will fail अगर the key can not be
 * found.
 *
 * Returns zero on success; non-zero on error
 */
अटल पूर्णांक ecryptfs_parse_options(काष्ठा ecryptfs_sb_info *sbi, अक्षर *options,
				  uid_t *check_ruid)
अणु
	अक्षर *p;
	पूर्णांक rc = 0;
	पूर्णांक sig_set = 0;
	पूर्णांक cipher_name_set = 0;
	पूर्णांक fn_cipher_name_set = 0;
	पूर्णांक cipher_key_bytes;
	पूर्णांक cipher_key_bytes_set = 0;
	पूर्णांक fn_cipher_key_bytes;
	पूर्णांक fn_cipher_key_bytes_set = 0;
	काष्ठा ecryptfs_mount_crypt_stat *mount_crypt_stat =
		&sbi->mount_crypt_stat;
	substring_t args[MAX_OPT_ARGS];
	पूर्णांक token;
	अक्षर *sig_src;
	अक्षर *cipher_name_dst;
	अक्षर *cipher_name_src;
	अक्षर *fn_cipher_name_dst;
	अक्षर *fn_cipher_name_src;
	अक्षर *fnek_dst;
	अक्षर *fnek_src;
	अक्षर *cipher_key_bytes_src;
	अक्षर *fn_cipher_key_bytes_src;
	u8 cipher_code;

	*check_ruid = 0;

	अगर (!options) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	ecryptfs_init_mount_crypt_stat(mount_crypt_stat);
	जबतक ((p = strsep(&options, ",")) != शून्य) अणु
		अगर (!*p)
			जारी;
		token = match_token(p, tokens, args);
		चयन (token) अणु
		हाल ecryptfs_opt_sig:
		हाल ecryptfs_opt_ecryptfs_sig:
			sig_src = args[0].from;
			rc = ecryptfs_add_global_auth_tok(mount_crypt_stat,
							  sig_src, 0);
			अगर (rc) अणु
				prपूर्णांकk(KERN_ERR "Error attempting to register "
				       "global sig; rc = [%d]\n", rc);
				जाओ out;
			पूर्ण
			sig_set = 1;
			अवरोध;
		हाल ecryptfs_opt_cipher:
		हाल ecryptfs_opt_ecryptfs_cipher:
			cipher_name_src = args[0].from;
			cipher_name_dst =
				mount_crypt_stat->
				global_शेष_cipher_name;
			म_नकलन(cipher_name_dst, cipher_name_src,
				ECRYPTFS_MAX_CIPHER_NAME_SIZE);
			cipher_name_dst[ECRYPTFS_MAX_CIPHER_NAME_SIZE] = '\0';
			cipher_name_set = 1;
			अवरोध;
		हाल ecryptfs_opt_ecryptfs_key_bytes:
			cipher_key_bytes_src = args[0].from;
			cipher_key_bytes =
				(पूर्णांक)simple_म_से_दीर्घ(cipher_key_bytes_src,
						   &cipher_key_bytes_src, 0);
			mount_crypt_stat->global_शेष_cipher_key_size =
				cipher_key_bytes;
			cipher_key_bytes_set = 1;
			अवरोध;
		हाल ecryptfs_opt_passthrough:
			mount_crypt_stat->flags |=
				ECRYPTFS_PLAINTEXT_PASSTHROUGH_ENABLED;
			अवरोध;
		हाल ecryptfs_opt_xattr_metadata:
			mount_crypt_stat->flags |=
				ECRYPTFS_XATTR_METADATA_ENABLED;
			अवरोध;
		हाल ecryptfs_opt_encrypted_view:
			mount_crypt_stat->flags |=
				ECRYPTFS_XATTR_METADATA_ENABLED;
			mount_crypt_stat->flags |=
				ECRYPTFS_ENCRYPTED_VIEW_ENABLED;
			अवरोध;
		हाल ecryptfs_opt_fnek_sig:
			fnek_src = args[0].from;
			fnek_dst =
				mount_crypt_stat->global_शेष_fnek_sig;
			म_नकलन(fnek_dst, fnek_src, ECRYPTFS_SIG_SIZE_HEX);
			mount_crypt_stat->global_शेष_fnek_sig[
				ECRYPTFS_SIG_SIZE_HEX] = '\0';
			rc = ecryptfs_add_global_auth_tok(
				mount_crypt_stat,
				mount_crypt_stat->global_शेष_fnek_sig,
				ECRYPTFS_AUTH_TOK_FNEK);
			अगर (rc) अणु
				prपूर्णांकk(KERN_ERR "Error attempting to register "
				       "global fnek sig [%s]; rc = [%d]\n",
				       mount_crypt_stat->global_शेष_fnek_sig,
				       rc);
				जाओ out;
			पूर्ण
			mount_crypt_stat->flags |=
				(ECRYPTFS_GLOBAL_ENCRYPT_खाताNAMES
				 | ECRYPTFS_GLOBAL_ENCFN_USE_MOUNT_FNEK);
			अवरोध;
		हाल ecryptfs_opt_fn_cipher:
			fn_cipher_name_src = args[0].from;
			fn_cipher_name_dst =
				mount_crypt_stat->global_शेष_fn_cipher_name;
			म_नकलन(fn_cipher_name_dst, fn_cipher_name_src,
				ECRYPTFS_MAX_CIPHER_NAME_SIZE);
			mount_crypt_stat->global_शेष_fn_cipher_name[
				ECRYPTFS_MAX_CIPHER_NAME_SIZE] = '\0';
			fn_cipher_name_set = 1;
			अवरोध;
		हाल ecryptfs_opt_fn_cipher_key_bytes:
			fn_cipher_key_bytes_src = args[0].from;
			fn_cipher_key_bytes =
				(पूर्णांक)simple_म_से_दीर्घ(fn_cipher_key_bytes_src,
						   &fn_cipher_key_bytes_src, 0);
			mount_crypt_stat->global_शेष_fn_cipher_key_bytes =
				fn_cipher_key_bytes;
			fn_cipher_key_bytes_set = 1;
			अवरोध;
		हाल ecryptfs_opt_unlink_sigs:
			mount_crypt_stat->flags |= ECRYPTFS_UNLINK_SIGS;
			अवरोध;
		हाल ecryptfs_opt_mount_auth_tok_only:
			mount_crypt_stat->flags |=
				ECRYPTFS_GLOBAL_MOUNT_AUTH_TOK_ONLY;
			अवरोध;
		हाल ecryptfs_opt_check_dev_ruid:
			*check_ruid = 1;
			अवरोध;
		हाल ecryptfs_opt_err:
		शेष:
			prपूर्णांकk(KERN_WARNING
			       "%s: eCryptfs: unrecognized option [%s]\n",
			       __func__, p);
		पूर्ण
	पूर्ण
	अगर (!sig_set) अणु
		rc = -EINVAL;
		ecryptfs_prपूर्णांकk(KERN_ERR, "You must supply at least one valid "
				"auth tok signature as a mount "
				"parameter; see the eCryptfs README\n");
		जाओ out;
	पूर्ण
	अगर (!cipher_name_set) अणु
		पूर्णांक cipher_name_len = म_माप(ECRYPTFS_DEFAULT_CIPHER);

		BUG_ON(cipher_name_len > ECRYPTFS_MAX_CIPHER_NAME_SIZE);
		म_नकल(mount_crypt_stat->global_शेष_cipher_name,
		       ECRYPTFS_DEFAULT_CIPHER);
	पूर्ण
	अगर ((mount_crypt_stat->flags & ECRYPTFS_GLOBAL_ENCRYPT_खाताNAMES)
	    && !fn_cipher_name_set)
		म_नकल(mount_crypt_stat->global_शेष_fn_cipher_name,
		       mount_crypt_stat->global_शेष_cipher_name);
	अगर (!cipher_key_bytes_set)
		mount_crypt_stat->global_शेष_cipher_key_size = 0;
	अगर ((mount_crypt_stat->flags & ECRYPTFS_GLOBAL_ENCRYPT_खाताNAMES)
	    && !fn_cipher_key_bytes_set)
		mount_crypt_stat->global_शेष_fn_cipher_key_bytes =
			mount_crypt_stat->global_शेष_cipher_key_size;

	cipher_code = ecryptfs_code_क्रम_cipher_string(
		mount_crypt_stat->global_शेष_cipher_name,
		mount_crypt_stat->global_शेष_cipher_key_size);
	अगर (!cipher_code) अणु
		ecryptfs_prपूर्णांकk(KERN_ERR,
				"eCryptfs doesn't support cipher: %s\n",
				mount_crypt_stat->global_शेष_cipher_name);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	mutex_lock(&key_tfm_list_mutex);
	अगर (!ecryptfs_tfm_exists(mount_crypt_stat->global_शेष_cipher_name,
				 शून्य)) अणु
		rc = ecryptfs_add_new_key_tfm(
			शून्य, mount_crypt_stat->global_शेष_cipher_name,
			mount_crypt_stat->global_शेष_cipher_key_size);
		अगर (rc) अणु
			prपूर्णांकk(KERN_ERR "Error attempting to initialize "
			       "cipher with name = [%s] and key size = [%td]; "
			       "rc = [%d]\n",
			       mount_crypt_stat->global_शेष_cipher_name,
			       mount_crypt_stat->global_शेष_cipher_key_size,
			       rc);
			rc = -EINVAL;
			mutex_unlock(&key_tfm_list_mutex);
			जाओ out;
		पूर्ण
	पूर्ण
	अगर ((mount_crypt_stat->flags & ECRYPTFS_GLOBAL_ENCRYPT_खाताNAMES)
	    && !ecryptfs_tfm_exists(
		    mount_crypt_stat->global_शेष_fn_cipher_name, शून्य)) अणु
		rc = ecryptfs_add_new_key_tfm(
			शून्य, mount_crypt_stat->global_शेष_fn_cipher_name,
			mount_crypt_stat->global_शेष_fn_cipher_key_bytes);
		अगर (rc) अणु
			prपूर्णांकk(KERN_ERR "Error attempting to initialize "
			       "cipher with name = [%s] and key size = [%td]; "
			       "rc = [%d]\n",
			       mount_crypt_stat->global_शेष_fn_cipher_name,
			       mount_crypt_stat->global_शेष_fn_cipher_key_bytes,
			       rc);
			rc = -EINVAL;
			mutex_unlock(&key_tfm_list_mutex);
			जाओ out;
		पूर्ण
	पूर्ण
	mutex_unlock(&key_tfm_list_mutex);
	rc = ecryptfs_init_global_auth_toks(mount_crypt_stat);
	अगर (rc)
		prपूर्णांकk(KERN_WARNING "One or more global auth toks could not "
		       "properly register; rc = [%d]\n", rc);
out:
	वापस rc;
पूर्ण

काष्ठा kmem_cache *ecryptfs_sb_info_cache;
अटल काष्ठा file_प्रणाली_type ecryptfs_fs_type;

/*
 * ecryptfs_mount
 * @fs_type: The fileप्रणाली type that the superblock should beदीर्घ to
 * @flags: The flags associated with the mount
 * @dev_name: The path to mount over
 * @raw_data: The options passed पूर्णांकo the kernel
 */
अटल काष्ठा dentry *ecryptfs_mount(काष्ठा file_प्रणाली_type *fs_type, पूर्णांक flags,
			स्थिर अक्षर *dev_name, व्योम *raw_data)
अणु
	काष्ठा super_block *s;
	काष्ठा ecryptfs_sb_info *sbi;
	काष्ठा ecryptfs_mount_crypt_stat *mount_crypt_stat;
	काष्ठा ecryptfs_dentry_info *root_info;
	स्थिर अक्षर *err = "Getting sb failed";
	काष्ठा inode *inode;
	काष्ठा path path;
	uid_t check_ruid;
	पूर्णांक rc;

	sbi = kmem_cache_zalloc(ecryptfs_sb_info_cache, GFP_KERNEL);
	अगर (!sbi) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (!dev_name) अणु
		rc = -EINVAL;
		err = "Device name cannot be null";
		जाओ out;
	पूर्ण

	rc = ecryptfs_parse_options(sbi, raw_data, &check_ruid);
	अगर (rc) अणु
		err = "Error parsing options";
		जाओ out;
	पूर्ण
	mount_crypt_stat = &sbi->mount_crypt_stat;

	s = sget(fs_type, शून्य, set_anon_super, flags, शून्य);
	अगर (IS_ERR(s)) अणु
		rc = PTR_ERR(s);
		जाओ out;
	पूर्ण

	rc = super_setup_bdi(s);
	अगर (rc)
		जाओ out1;

	ecryptfs_set_superblock_निजी(s, sbi);

	/* ->समाप्त_sb() will take care of sbi after that poपूर्णांक */
	sbi = शून्य;
	s->s_op = &ecryptfs_sops;
	s->s_xattr = ecryptfs_xattr_handlers;
	s->s_d_op = &ecryptfs_करोps;

	err = "Reading sb failed";
	rc = kern_path(dev_name, LOOKUP_FOLLOW | LOOKUP_सूचीECTORY, &path);
	अगर (rc) अणु
		ecryptfs_prपूर्णांकk(KERN_WARNING, "kern_path() failed\n");
		जाओ out1;
	पूर्ण
	अगर (path.dentry->d_sb->s_type == &ecryptfs_fs_type) अणु
		rc = -EINVAL;
		prपूर्णांकk(KERN_ERR "Mount on filesystem of type "
			"eCryptfs explicitly disallowed due to "
			"known incompatibilities\n");
		जाओ out_मुक्त;
	पूर्ण

	अगर (mnt_user_ns(path.mnt) != &init_user_ns) अणु
		rc = -EINVAL;
		prपूर्णांकk(KERN_ERR "Mounting on idmapped mounts currently disallowed\n");
		जाओ out_मुक्त;
	पूर्ण

	अगर (check_ruid && !uid_eq(d_inode(path.dentry)->i_uid, current_uid())) अणु
		rc = -EPERM;
		prपूर्णांकk(KERN_ERR "Mount of device (uid: %d) not owned by "
		       "requested user (uid: %d)\n",
			i_uid_पढ़ो(d_inode(path.dentry)),
			from_kuid(&init_user_ns, current_uid()));
		जाओ out_मुक्त;
	पूर्ण

	ecryptfs_set_superblock_lower(s, path.dentry->d_sb);

	/**
	 * Set the POSIX ACL flag based on whether they're enabled in the lower
	 * mount.
	 */
	s->s_flags = flags & ~SB_POSIXACL;
	s->s_flags |= path.dentry->d_sb->s_flags & SB_POSIXACL;

	/**
	 * Force a पढ़ो-only eCryptfs mount when:
	 *   1) The lower mount is ro
	 *   2) The ecryptfs_encrypted_view mount option is specअगरied
	 */
	अगर (sb_rकरोnly(path.dentry->d_sb) || mount_crypt_stat->flags & ECRYPTFS_ENCRYPTED_VIEW_ENABLED)
		s->s_flags |= SB_RDONLY;

	s->s_maxbytes = path.dentry->d_sb->s_maxbytes;
	s->s_blocksize = path.dentry->d_sb->s_blocksize;
	s->s_magic = ECRYPTFS_SUPER_MAGIC;
	s->s_stack_depth = path.dentry->d_sb->s_stack_depth + 1;

	rc = -EINVAL;
	अगर (s->s_stack_depth > खाताSYSTEM_MAX_STACK_DEPTH) अणु
		pr_err("eCryptfs: maximum fs stacking depth exceeded\n");
		जाओ out_मुक्त;
	पूर्ण

	inode = ecryptfs_get_inode(d_inode(path.dentry), s);
	rc = PTR_ERR(inode);
	अगर (IS_ERR(inode))
		जाओ out_मुक्त;

	s->s_root = d_make_root(inode);
	अगर (!s->s_root) अणु
		rc = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण

	rc = -ENOMEM;
	root_info = kmem_cache_zalloc(ecryptfs_dentry_info_cache, GFP_KERNEL);
	अगर (!root_info)
		जाओ out_मुक्त;

	/* ->समाप्त_sb() will take care of root_info */
	ecryptfs_set_dentry_निजी(s->s_root, root_info);
	root_info->lower_path = path;

	s->s_flags |= SB_ACTIVE;
	वापस dget(s->s_root);

out_मुक्त:
	path_put(&path);
out1:
	deactivate_locked_super(s);
out:
	अगर (sbi) अणु
		ecryptfs_destroy_mount_crypt_stat(&sbi->mount_crypt_stat);
		kmem_cache_मुक्त(ecryptfs_sb_info_cache, sbi);
	पूर्ण
	prपूर्णांकk(KERN_ERR "%s; rc = [%d]\n", err, rc);
	वापस ERR_PTR(rc);
पूर्ण

/**
 * ecryptfs_समाप्त_block_super
 * @sb: The ecryptfs super block
 *
 * Used to bring the superblock करोwn and मुक्त the निजी data.
 */
अटल व्योम ecryptfs_समाप्त_block_super(काष्ठा super_block *sb)
अणु
	काष्ठा ecryptfs_sb_info *sb_info = ecryptfs_superblock_to_निजी(sb);
	समाप्त_anon_super(sb);
	अगर (!sb_info)
		वापस;
	ecryptfs_destroy_mount_crypt_stat(&sb_info->mount_crypt_stat);
	kmem_cache_मुक्त(ecryptfs_sb_info_cache, sb_info);
पूर्ण

अटल काष्ठा file_प्रणाली_type ecryptfs_fs_type = अणु
	.owner = THIS_MODULE,
	.name = "ecryptfs",
	.mount = ecryptfs_mount,
	.समाप्त_sb = ecryptfs_समाप्त_block_super,
	.fs_flags = 0
पूर्ण;
MODULE_ALIAS_FS("ecryptfs");

/*
 * inode_info_init_once
 *
 * Initializes the ecryptfs_inode_info_cache when it is created
 */
अटल व्योम
inode_info_init_once(व्योम *vptr)
अणु
	काष्ठा ecryptfs_inode_info *ei = (काष्ठा ecryptfs_inode_info *)vptr;

	inode_init_once(&ei->vfs_inode);
पूर्ण

अटल काष्ठा ecryptfs_cache_info अणु
	काष्ठा kmem_cache **cache;
	स्थिर अक्षर *name;
	माप_प्रकार size;
	slab_flags_t flags;
	व्योम (*ctor)(व्योम *obj);
पूर्ण ecryptfs_cache_infos[] = अणु
	अणु
		.cache = &ecryptfs_auth_tok_list_item_cache,
		.name = "ecryptfs_auth_tok_list_item",
		.size = माप(काष्ठा ecryptfs_auth_tok_list_item),
	पूर्ण,
	अणु
		.cache = &ecryptfs_file_info_cache,
		.name = "ecryptfs_file_cache",
		.size = माप(काष्ठा ecryptfs_file_info),
	पूर्ण,
	अणु
		.cache = &ecryptfs_dentry_info_cache,
		.name = "ecryptfs_dentry_info_cache",
		.size = माप(काष्ठा ecryptfs_dentry_info),
	पूर्ण,
	अणु
		.cache = &ecryptfs_inode_info_cache,
		.name = "ecryptfs_inode_cache",
		.size = माप(काष्ठा ecryptfs_inode_info),
		.flags = SLAB_ACCOUNT,
		.ctor = inode_info_init_once,
	पूर्ण,
	अणु
		.cache = &ecryptfs_sb_info_cache,
		.name = "ecryptfs_sb_cache",
		.size = माप(काष्ठा ecryptfs_sb_info),
	पूर्ण,
	अणु
		.cache = &ecryptfs_header_cache,
		.name = "ecryptfs_headers",
		.size = PAGE_SIZE,
	पूर्ण,
	अणु
		.cache = &ecryptfs_xattr_cache,
		.name = "ecryptfs_xattr_cache",
		.size = PAGE_SIZE,
	पूर्ण,
	अणु
		.cache = &ecryptfs_key_record_cache,
		.name = "ecryptfs_key_record_cache",
		.size = माप(काष्ठा ecryptfs_key_record),
	पूर्ण,
	अणु
		.cache = &ecryptfs_key_sig_cache,
		.name = "ecryptfs_key_sig_cache",
		.size = माप(काष्ठा ecryptfs_key_sig),
	पूर्ण,
	अणु
		.cache = &ecryptfs_global_auth_tok_cache,
		.name = "ecryptfs_global_auth_tok_cache",
		.size = माप(काष्ठा ecryptfs_global_auth_tok),
	पूर्ण,
	अणु
		.cache = &ecryptfs_key_tfm_cache,
		.name = "ecryptfs_key_tfm_cache",
		.size = माप(काष्ठा ecryptfs_key_tfm),
	पूर्ण,
पूर्ण;

अटल व्योम ecryptfs_मुक्त_kmem_caches(व्योम)
अणु
	पूर्णांक i;

	/*
	 * Make sure all delayed rcu मुक्त inodes are flushed beक्रमe we
	 * destroy cache.
	 */
	rcu_barrier();

	क्रम (i = 0; i < ARRAY_SIZE(ecryptfs_cache_infos); i++) अणु
		काष्ठा ecryptfs_cache_info *info;

		info = &ecryptfs_cache_infos[i];
		kmem_cache_destroy(*(info->cache));
	पूर्ण
पूर्ण

/**
 * ecryptfs_init_kmem_caches
 *
 * Returns zero on success; non-zero otherwise
 */
अटल पूर्णांक ecryptfs_init_kmem_caches(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ecryptfs_cache_infos); i++) अणु
		काष्ठा ecryptfs_cache_info *info;

		info = &ecryptfs_cache_infos[i];
		*(info->cache) = kmem_cache_create(info->name, info->size, 0,
				SLAB_HWCACHE_ALIGN | info->flags, info->ctor);
		अगर (!*(info->cache)) अणु
			ecryptfs_मुक्त_kmem_caches();
			ecryptfs_prपूर्णांकk(KERN_WARNING, "%s: "
					"kmem_cache_create failed\n",
					info->name);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा kobject *ecryptfs_kobj;

अटल sमाप_प्रकार version_show(काष्ठा kobject *kobj,
			    काष्ठा kobj_attribute *attr, अक्षर *buff)
अणु
	वापस snम_लिखो(buff, PAGE_SIZE, "%d\n", ECRYPTFS_VERSIONING_MASK);
पूर्ण

अटल काष्ठा kobj_attribute version_attr = __ATTR_RO(version);

अटल काष्ठा attribute *attributes[] = अणु
	&version_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group attr_group = अणु
	.attrs = attributes,
पूर्ण;

अटल पूर्णांक करो_sysfs_registration(व्योम)
अणु
	पूर्णांक rc;

	ecryptfs_kobj = kobject_create_and_add("ecryptfs", fs_kobj);
	अगर (!ecryptfs_kobj) अणु
		prपूर्णांकk(KERN_ERR "Unable to create ecryptfs kset\n");
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	rc = sysfs_create_group(ecryptfs_kobj, &attr_group);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR
		       "Unable to create ecryptfs version attributes\n");
		kobject_put(ecryptfs_kobj);
	पूर्ण
out:
	वापस rc;
पूर्ण

अटल व्योम करो_sysfs_unregistration(व्योम)
अणु
	sysfs_हटाओ_group(ecryptfs_kobj, &attr_group);
	kobject_put(ecryptfs_kobj);
पूर्ण

अटल पूर्णांक __init ecryptfs_init(व्योम)
अणु
	पूर्णांक rc;

	अगर (ECRYPTFS_DEFAULT_EXTENT_SIZE > PAGE_SIZE) अणु
		rc = -EINVAL;
		ecryptfs_prपूर्णांकk(KERN_ERR, "The eCryptfs extent size is "
				"larger than the host's page size, and so "
				"eCryptfs cannot run on this system. The "
				"default eCryptfs extent size is [%u] bytes; "
				"the page size is [%lu] bytes.\n",
				ECRYPTFS_DEFAULT_EXTENT_SIZE,
				(अचिन्हित दीर्घ)PAGE_SIZE);
		जाओ out;
	पूर्ण
	rc = ecryptfs_init_kmem_caches();
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR
		       "Failed to allocate one or more kmem_cache objects\n");
		जाओ out;
	पूर्ण
	rc = करो_sysfs_registration();
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "sysfs registration failed\n");
		जाओ out_मुक्त_kmem_caches;
	पूर्ण
	rc = ecryptfs_init_kthपढ़ो();
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "%s: kthread initialization failed; "
		       "rc = [%d]\n", __func__, rc);
		जाओ out_करो_sysfs_unregistration;
	पूर्ण
	rc = ecryptfs_init_messaging();
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "Failure occurred while attempting to "
				"initialize the communications channel to "
				"ecryptfsd\n");
		जाओ out_destroy_kthपढ़ो;
	पूर्ण
	rc = ecryptfs_init_crypto();
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "Failure whilst attempting to init crypto; "
		       "rc = [%d]\n", rc);
		जाओ out_release_messaging;
	पूर्ण
	rc = रेजिस्टर_fileप्रणाली(&ecryptfs_fs_type);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "Failed to register filesystem\n");
		जाओ out_destroy_crypto;
	पूर्ण
	अगर (ecryptfs_verbosity > 0)
		prपूर्णांकk(KERN_CRIT "eCryptfs verbosity set to %d. Secret values "
			"will be written to the syslog!\n", ecryptfs_verbosity);

	जाओ out;
out_destroy_crypto:
	ecryptfs_destroy_crypto();
out_release_messaging:
	ecryptfs_release_messaging();
out_destroy_kthपढ़ो:
	ecryptfs_destroy_kthपढ़ो();
out_करो_sysfs_unregistration:
	करो_sysfs_unregistration();
out_मुक्त_kmem_caches:
	ecryptfs_मुक्त_kmem_caches();
out:
	वापस rc;
पूर्ण

अटल व्योम __निकास ecryptfs_निकास(व्योम)
अणु
	पूर्णांक rc;

	rc = ecryptfs_destroy_crypto();
	अगर (rc)
		prपूर्णांकk(KERN_ERR "Failure whilst attempting to destroy crypto; "
		       "rc = [%d]\n", rc);
	ecryptfs_release_messaging();
	ecryptfs_destroy_kthपढ़ो();
	करो_sysfs_unregistration();
	unरेजिस्टर_fileप्रणाली(&ecryptfs_fs_type);
	ecryptfs_मुक्त_kmem_caches();
पूर्ण

MODULE_AUTHOR("Michael A. Halcrow <mhalcrow@us.ibm.com>");
MODULE_DESCRIPTION("eCryptfs");

MODULE_LICENSE("GPL");

module_init(ecryptfs_init)
module_निकास(ecryptfs_निकास)
