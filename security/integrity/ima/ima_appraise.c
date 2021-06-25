<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011 IBM Corporation
 *
 * Author:
 * Mimi Zohar <zohar@us.ibm.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/xattr.h>
#समावेश <linux/magic.h>
#समावेश <linux/ima.h>
#समावेश <linux/evm.h>
#समावेश <keys/प्रणाली_keyring.h>

#समावेश "ima.h"

#अगर_घोषित CONFIG_IMA_APPRAISE_BOOTPARAM
अटल अक्षर *ima_appउठाओ_cmdline_शेष __initdata;
core_param(ima_appउठाओ, ima_appउठाओ_cmdline_शेष, अक्षरp, 0);

व्योम __init ima_appउठाओ_parse_cmdline(व्योम)
अणु
	स्थिर अक्षर *str = ima_appउठाओ_cmdline_शेष;
	bool sb_state = arch_ima_get_secureboot();
	पूर्णांक appraisal_state = ima_appउठाओ;

	अगर (!str)
		वापस;

	अगर (म_भेदन(str, "off", 3) == 0)
		appraisal_state = 0;
	अन्यथा अगर (म_भेदन(str, "log", 3) == 0)
		appraisal_state = IMA_APPRAISE_LOG;
	अन्यथा अगर (म_भेदन(str, "fix", 3) == 0)
		appraisal_state = IMA_APPRAISE_FIX;
	अन्यथा अगर (म_भेदन(str, "enforce", 7) == 0)
		appraisal_state = IMA_APPRAISE_ENFORCE;
	अन्यथा
		pr_err("invalid \"%s\" appraise option", str);

	/* If appraisal state was changed, but secure boot is enabled,
	 * keep its शेष */
	अगर (sb_state) अणु
		अगर (!(appraisal_state & IMA_APPRAISE_ENFORCE))
			pr_info("Secure boot enabled: ignoring ima_appraise=%s option",
				str);
	पूर्ण अन्यथा अणु
		ima_appउठाओ = appraisal_state;
	पूर्ण
पूर्ण
#पूर्ण_अगर

/*
 * is_ima_appउठाओ_enabled - वापस appउठाओ status
 *
 * Only वापस enabled, अगर not in ima_appउठाओ="fix" or "log" modes.
 */
bool is_ima_appउठाओ_enabled(व्योम)
अणु
	वापस ima_appउठाओ & IMA_APPRAISE_ENFORCE;
पूर्ण

/*
 * ima_must_appउठाओ - set appउठाओ flag
 *
 * Return 1 to appउठाओ or hash
 */
पूर्णांक ima_must_appउठाओ(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		      पूर्णांक mask, क्रमागत ima_hooks func)
अणु
	u32 secid;

	अगर (!ima_appउठाओ)
		वापस 0;

	security_task_माला_लोecid_subj(current, &secid);
	वापस ima_match_policy(mnt_userns, inode, current_cred(), secid, func,
				mask, IMA_APPRAISE | IMA_HASH, शून्य, शून्य, शून्य);
पूर्ण

अटल पूर्णांक ima_fix_xattr(काष्ठा dentry *dentry,
			 काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक)
अणु
	पूर्णांक rc, offset;
	u8 algo = iपूर्णांक->ima_hash->algo;

	अगर (algo <= HASH_ALGO_SHA1) अणु
		offset = 1;
		iपूर्णांक->ima_hash->xattr.sha1.type = IMA_XATTR_DIGEST;
	पूर्ण अन्यथा अणु
		offset = 0;
		iपूर्णांक->ima_hash->xattr.ng.type = IMA_XATTR_DIGEST_NG;
		iपूर्णांक->ima_hash->xattr.ng.algo = algo;
	पूर्ण
	rc = __vfs_setxattr_noperm(&init_user_ns, dentry, XATTR_NAME_IMA,
				   &iपूर्णांक->ima_hash->xattr.data[offset],
				   (माप(iपूर्णांक->ima_hash->xattr) - offset) +
				   iपूर्णांक->ima_hash->length, 0);
	वापस rc;
पूर्ण

/* Return specअगरic func appउठाओd cached result */
क्रमागत पूर्णांकegrity_status ima_get_cache_status(काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक,
					   क्रमागत ima_hooks func)
अणु
	चयन (func) अणु
	हाल MMAP_CHECK:
		वापस iपूर्णांक->ima_mmap_status;
	हाल BPRM_CHECK:
		वापस iपूर्णांक->ima_bprm_status;
	हाल CREDS_CHECK:
		वापस iपूर्णांक->ima_creds_status;
	हाल खाता_CHECK:
	हाल POST_SETATTR:
		वापस iपूर्णांक->ima_file_status;
	हाल MODULE_CHECK ... MAX_CHECK - 1:
	शेष:
		वापस iपूर्णांक->ima_पढ़ो_status;
	पूर्ण
पूर्ण

अटल व्योम ima_set_cache_status(काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक,
				 क्रमागत ima_hooks func,
				 क्रमागत पूर्णांकegrity_status status)
अणु
	चयन (func) अणु
	हाल MMAP_CHECK:
		iपूर्णांक->ima_mmap_status = status;
		अवरोध;
	हाल BPRM_CHECK:
		iपूर्णांक->ima_bprm_status = status;
		अवरोध;
	हाल CREDS_CHECK:
		iपूर्णांक->ima_creds_status = status;
		अवरोध;
	हाल खाता_CHECK:
	हाल POST_SETATTR:
		iपूर्णांक->ima_file_status = status;
		अवरोध;
	हाल MODULE_CHECK ... MAX_CHECK - 1:
	शेष:
		iपूर्णांक->ima_पढ़ो_status = status;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ima_cache_flags(काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक,
			     क्रमागत ima_hooks func)
अणु
	चयन (func) अणु
	हाल MMAP_CHECK:
		iपूर्णांक->flags |= (IMA_MMAP_APPRAISED | IMA_APPRAISED);
		अवरोध;
	हाल BPRM_CHECK:
		iपूर्णांक->flags |= (IMA_BPRM_APPRAISED | IMA_APPRAISED);
		अवरोध;
	हाल CREDS_CHECK:
		iपूर्णांक->flags |= (IMA_CREDS_APPRAISED | IMA_APPRAISED);
		अवरोध;
	हाल खाता_CHECK:
	हाल POST_SETATTR:
		iपूर्णांक->flags |= (IMA_खाता_APPRAISED | IMA_APPRAISED);
		अवरोध;
	हाल MODULE_CHECK ... MAX_CHECK - 1:
	शेष:
		iपूर्णांक->flags |= (IMA_READ_APPRAISED | IMA_APPRAISED);
		अवरोध;
	पूर्ण
पूर्ण

क्रमागत hash_algo ima_get_hash_algo(काष्ठा evm_ima_xattr_data *xattr_value,
				 पूर्णांक xattr_len)
अणु
	काष्ठा signature_v2_hdr *sig;
	क्रमागत hash_algo ret;

	अगर (!xattr_value || xattr_len < 2)
		/* वापस शेष hash algo */
		वापस ima_hash_algo;

	चयन (xattr_value->type) अणु
	हाल EVM_IMA_XATTR_DIGSIG:
		sig = (typeof(sig))xattr_value;
		अगर (sig->version != 2 || xattr_len <= माप(*sig))
			वापस ima_hash_algo;
		वापस sig->hash_algo;
		अवरोध;
	हाल IMA_XATTR_DIGEST_NG:
		/* first byte contains algorithm id */
		ret = xattr_value->data[0];
		अगर (ret < HASH_ALGO__LAST)
			वापस ret;
		अवरोध;
	हाल IMA_XATTR_DIGEST:
		/* this is क्रम backward compatibility */
		अगर (xattr_len == 21) अणु
			अचिन्हित पूर्णांक zero = 0;
			अगर (!स_भेद(&xattr_value->data[16], &zero, 4))
				वापस HASH_ALGO_MD5;
			अन्यथा
				वापस HASH_ALGO_SHA1;
		पूर्ण अन्यथा अगर (xattr_len == 17)
			वापस HASH_ALGO_MD5;
		अवरोध;
	पूर्ण

	/* वापस शेष hash algo */
	वापस ima_hash_algo;
पूर्ण

पूर्णांक ima_पढ़ो_xattr(काष्ठा dentry *dentry,
		   काष्ठा evm_ima_xattr_data **xattr_value)
अणु
	sमाप_प्रकार ret;

	ret = vfs_getxattr_alloc(&init_user_ns, dentry, XATTR_NAME_IMA,
				 (अक्षर **)xattr_value, 0, GFP_NOFS);
	अगर (ret == -EOPNOTSUPP)
		ret = 0;
	वापस ret;
पूर्ण

/*
 * xattr_verअगरy - verअगरy xattr digest or signature
 *
 * Verअगरy whether the hash or signature matches the file contents.
 *
 * Return 0 on success, error code otherwise.
 */
अटल पूर्णांक xattr_verअगरy(क्रमागत ima_hooks func, काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक,
			काष्ठा evm_ima_xattr_data *xattr_value, पूर्णांक xattr_len,
			क्रमागत पूर्णांकegrity_status *status, स्थिर अक्षर **cause)
अणु
	पूर्णांक rc = -EINVAL, hash_start = 0;

	चयन (xattr_value->type) अणु
	हाल IMA_XATTR_DIGEST_NG:
		/* first byte contains algorithm id */
		hash_start = 1;
		fallthrough;
	हाल IMA_XATTR_DIGEST:
		अगर (iपूर्णांक->flags & IMA_DIGSIG_REQUIRED) अणु
			*cause = "IMA-signature-required";
			*status = INTEGRITY_FAIL;
			अवरोध;
		पूर्ण
		clear_bit(IMA_DIGSIG, &iपूर्णांक->atomic_flags);
		अगर (xattr_len - माप(xattr_value->type) - hash_start >=
				iपूर्णांक->ima_hash->length)
			/*
			 * xattr length may be दीर्घer. md5 hash in previous
			 * version occupied 20 bytes in xattr, instead of 16
			 */
			rc = स_भेद(&xattr_value->data[hash_start],
				    iपूर्णांक->ima_hash->digest,
				    iपूर्णांक->ima_hash->length);
		अन्यथा
			rc = -EINVAL;
		अगर (rc) अणु
			*cause = "invalid-hash";
			*status = INTEGRITY_FAIL;
			अवरोध;
		पूर्ण
		*status = INTEGRITY_PASS;
		अवरोध;
	हाल EVM_IMA_XATTR_DIGSIG:
		set_bit(IMA_DIGSIG, &iपूर्णांक->atomic_flags);
		rc = पूर्णांकegrity_digsig_verअगरy(INTEGRITY_KEYRING_IMA,
					     (स्थिर अक्षर *)xattr_value,
					     xattr_len,
					     iपूर्णांक->ima_hash->digest,
					     iपूर्णांक->ima_hash->length);
		अगर (rc == -EOPNOTSUPP) अणु
			*status = INTEGRITY_UNKNOWN;
			अवरोध;
		पूर्ण
		अगर (IS_ENABLED(CONFIG_INTEGRITY_PLATFORM_KEYRING) && rc &&
		    func == KEXEC_KERNEL_CHECK)
			rc = पूर्णांकegrity_digsig_verअगरy(INTEGRITY_KEYRING_PLATFORM,
						     (स्थिर अक्षर *)xattr_value,
						     xattr_len,
						     iपूर्णांक->ima_hash->digest,
						     iपूर्णांक->ima_hash->length);
		अगर (rc) अणु
			*cause = "invalid-signature";
			*status = INTEGRITY_FAIL;
		पूर्ण अन्यथा अणु
			*status = INTEGRITY_PASS;
		पूर्ण
		अवरोध;
	शेष:
		*status = INTEGRITY_UNKNOWN;
		*cause = "unknown-ima-data";
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

/*
 * modsig_verअगरy - verअगरy modsig signature
 *
 * Verअगरy whether the signature matches the file contents.
 *
 * Return 0 on success, error code otherwise.
 */
अटल पूर्णांक modsig_verअगरy(क्रमागत ima_hooks func, स्थिर काष्ठा modsig *modsig,
			 क्रमागत पूर्णांकegrity_status *status, स्थिर अक्षर **cause)
अणु
	पूर्णांक rc;

	rc = पूर्णांकegrity_modsig_verअगरy(INTEGRITY_KEYRING_IMA, modsig);
	अगर (IS_ENABLED(CONFIG_INTEGRITY_PLATFORM_KEYRING) && rc &&
	    func == KEXEC_KERNEL_CHECK)
		rc = पूर्णांकegrity_modsig_verअगरy(INTEGRITY_KEYRING_PLATFORM,
					     modsig);
	अगर (rc) अणु
		*cause = "invalid-signature";
		*status = INTEGRITY_FAIL;
	पूर्ण अन्यथा अणु
		*status = INTEGRITY_PASS;
	पूर्ण

	वापस rc;
पूर्ण

/*
 * ima_check_blacklist - determine अगर the binary is blacklisted.
 *
 * Add the hash of the blacklisted binary to the measurement list, based
 * on policy.
 *
 * Returns -EPERM अगर the hash is blacklisted.
 */
पूर्णांक ima_check_blacklist(काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक,
			स्थिर काष्ठा modsig *modsig, पूर्णांक pcr)
अणु
	क्रमागत hash_algo hash_algo;
	स्थिर u8 *digest = शून्य;
	u32 digestsize = 0;
	पूर्णांक rc = 0;

	अगर (!(iपूर्णांक->flags & IMA_CHECK_BLACKLIST))
		वापस 0;

	अगर (iपूर्णांक->flags & IMA_MODSIG_ALLOWED && modsig) अणु
		ima_get_modsig_digest(modsig, &hash_algo, &digest, &digestsize);

		rc = is_binary_blacklisted(digest, digestsize);
		अगर ((rc == -EPERM) && (iपूर्णांक->flags & IMA_MEASURE))
			process_buffer_measurement(&init_user_ns, शून्य, digest, digestsize,
						   "blacklisted-hash", NONE,
						   pcr, शून्य, false);
	पूर्ण

	वापस rc;
पूर्ण

/*
 * ima_appउठाओ_measurement - appउठाओ file measurement
 *
 * Call evm_verअगरyxattr() to verअगरy the पूर्णांकegrity of 'security.ima'.
 * Assuming success, compare the xattr hash with the collected measurement.
 *
 * Return 0 on success, error code otherwise
 */
पूर्णांक ima_appउठाओ_measurement(क्रमागत ima_hooks func,
			     काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक,
			     काष्ठा file *file, स्थिर अचिन्हित अक्षर *filename,
			     काष्ठा evm_ima_xattr_data *xattr_value,
			     पूर्णांक xattr_len, स्थिर काष्ठा modsig *modsig)
अणु
	अटल स्थिर अक्षर op[] = "appraise_data";
	स्थिर अक्षर *cause = "unknown";
	काष्ठा dentry *dentry = file_dentry(file);
	काष्ठा inode *inode = d_backing_inode(dentry);
	क्रमागत पूर्णांकegrity_status status = INTEGRITY_UNKNOWN;
	पूर्णांक rc = xattr_len;
	bool try_modsig = iपूर्णांक->flags & IMA_MODSIG_ALLOWED && modsig;

	/* If not appraising a modsig, we need an xattr. */
	अगर (!(inode->i_opflags & IOP_XATTR) && !try_modsig)
		वापस INTEGRITY_UNKNOWN;

	/* If पढ़ोing the xattr failed and there's no modsig, error out. */
	अगर (rc <= 0 && !try_modsig) अणु
		अगर (rc && rc != -ENODATA)
			जाओ out;

		cause = iपूर्णांक->flags & IMA_DIGSIG_REQUIRED ?
				"IMA-signature-required" : "missing-hash";
		status = INTEGRITY_NOLABEL;
		अगर (file->f_mode & FMODE_CREATED)
			iपूर्णांक->flags |= IMA_NEW_खाता;
		अगर ((iपूर्णांक->flags & IMA_NEW_खाता) &&
		    (!(iपूर्णांक->flags & IMA_DIGSIG_REQUIRED) ||
		     (inode->i_size == 0)))
			status = INTEGRITY_PASS;
		जाओ out;
	पूर्ण

	status = evm_verअगरyxattr(dentry, XATTR_NAME_IMA, xattr_value, rc, iपूर्णांक);
	चयन (status) अणु
	हाल INTEGRITY_PASS:
	हाल INTEGRITY_PASS_IMMUTABLE:
	हाल INTEGRITY_UNKNOWN:
		अवरोध;
	हाल INTEGRITY_NOXATTRS:	/* No EVM रक्षित xattrs. */
		/* It's fine not to have xattrs when using a modsig. */
		अगर (try_modsig)
			अवरोध;
		fallthrough;
	हाल INTEGRITY_NOLABEL:		/* No security.evm xattr. */
		cause = "missing-HMAC";
		जाओ out;
	हाल INTEGRITY_FAIL:		/* Invalid HMAC/signature. */
		cause = "invalid-HMAC";
		जाओ out;
	शेष:
		WARN_ONCE(true, "Unexpected integrity status %d\n", status);
	पूर्ण

	अगर (xattr_value)
		rc = xattr_verअगरy(func, iपूर्णांक, xattr_value, xattr_len, &status,
				  &cause);

	/*
	 * If we have a modsig and either no imasig or the imasig's key isn't
	 * known, then try verअगरying the modsig.
	 */
	अगर (try_modsig &&
	    (!xattr_value || xattr_value->type == IMA_XATTR_DIGEST_NG ||
	     rc == -ENOKEY))
		rc = modsig_verअगरy(func, modsig, &status, &cause);

out:
	/*
	 * File signatures on some fileप्रणालीs can not be properly verअगरied.
	 * When such fileप्रणालीs are mounted by an untrusted mounter or on a
	 * प्रणाली not willing to accept such a risk, fail the file signature
	 * verअगरication.
	 */
	अगर ((inode->i_sb->s_अगरlags & SB_I_IMA_UNVERIFIABLE_SIGNATURE) &&
	    ((inode->i_sb->s_अगरlags & SB_I_UNTRUSTED_MOUNTER) ||
	     (iपूर्णांक->flags & IMA_FAIL_UNVERIFIABLE_SIGS))) अणु
		status = INTEGRITY_FAIL;
		cause = "unverifiable-signature";
		पूर्णांकegrity_audit_msg(AUDIT_INTEGRITY_DATA, inode, filename,
				    op, cause, rc, 0);
	पूर्ण अन्यथा अगर (status != INTEGRITY_PASS) अणु
		/* Fix mode, but करोn't replace file signatures. */
		अगर ((ima_appउठाओ & IMA_APPRAISE_FIX) && !try_modsig &&
		    (!xattr_value ||
		     xattr_value->type != EVM_IMA_XATTR_DIGSIG)) अणु
			अगर (!ima_fix_xattr(dentry, iपूर्णांक))
				status = INTEGRITY_PASS;
		पूर्ण

		/* Permit new files with file signatures, but without data. */
		अगर (inode->i_size == 0 && iपूर्णांक->flags & IMA_NEW_खाता &&
		    xattr_value && xattr_value->type == EVM_IMA_XATTR_DIGSIG) अणु
			status = INTEGRITY_PASS;
		पूर्ण

		पूर्णांकegrity_audit_msg(AUDIT_INTEGRITY_DATA, inode, filename,
				    op, cause, rc, 0);
	पूर्ण अन्यथा अणु
		ima_cache_flags(iपूर्णांक, func);
	पूर्ण

	ima_set_cache_status(iपूर्णांक, func, status);
	वापस status;
पूर्ण

/*
 * ima_update_xattr - update 'security.ima' hash value
 */
व्योम ima_update_xattr(काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक, काष्ठा file *file)
अणु
	काष्ठा dentry *dentry = file_dentry(file);
	पूर्णांक rc = 0;

	/* करो not collect and update hash क्रम digital signatures */
	अगर (test_bit(IMA_DIGSIG, &iपूर्णांक->atomic_flags))
		वापस;

	अगर ((iपूर्णांक->ima_file_status != INTEGRITY_PASS) &&
	    !(iपूर्णांक->flags & IMA_HASH))
		वापस;

	rc = ima_collect_measurement(iपूर्णांक, file, शून्य, 0, ima_hash_algo, शून्य);
	अगर (rc < 0)
		वापस;

	inode_lock(file_inode(file));
	ima_fix_xattr(dentry, iपूर्णांक);
	inode_unlock(file_inode(file));
पूर्ण

/**
 * ima_inode_post_setattr - reflect file metadata changes
 * @mnt_userns:	user namespace of the mount the inode was found from
 * @dentry: poपूर्णांकer to the affected dentry
 *
 * Changes to a dentry's metadata might result in needing to appउठाओ.
 *
 * This function is called from notअगरy_change(), which expects the caller
 * to lock the inode's i_mutex.
 */
व्योम ima_inode_post_setattr(काष्ठा user_namespace *mnt_userns,
			    काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_backing_inode(dentry);
	काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक;
	पूर्णांक action;

	अगर (!(ima_policy_flag & IMA_APPRAISE) || !S_ISREG(inode->i_mode)
	    || !(inode->i_opflags & IOP_XATTR))
		वापस;

	action = ima_must_appउठाओ(mnt_userns, inode, MAY_ACCESS, POST_SETATTR);
	अगर (!action)
		__vfs_हटाओxattr(&init_user_ns, dentry, XATTR_NAME_IMA);
	iपूर्णांक = पूर्णांकegrity_iपूर्णांक_find(inode);
	अगर (iपूर्णांक) अणु
		set_bit(IMA_CHANGE_ATTR, &iपूर्णांक->atomic_flags);
		अगर (!action)
			clear_bit(IMA_UPDATE_XATTR, &iपूर्णांक->atomic_flags);
	पूर्ण
पूर्ण

/*
 * ima_protect_xattr - protect 'security.ima'
 *
 * Ensure that not just anyone can modअगरy or हटाओ 'security.ima'.
 */
अटल पूर्णांक ima_protect_xattr(काष्ठा dentry *dentry, स्थिर अक्षर *xattr_name,
			     स्थिर व्योम *xattr_value, माप_प्रकार xattr_value_len)
अणु
	अगर (म_भेद(xattr_name, XATTR_NAME_IMA) == 0) अणु
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ima_reset_appउठाओ_flags(काष्ठा inode *inode, पूर्णांक digsig)
अणु
	काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक;

	अगर (!(ima_policy_flag & IMA_APPRAISE) || !S_ISREG(inode->i_mode))
		वापस;

	iपूर्णांक = पूर्णांकegrity_iपूर्णांक_find(inode);
	अगर (!iपूर्णांक)
		वापस;
	iपूर्णांक->measured_pcrs = 0;
	set_bit(IMA_CHANGE_XATTR, &iपूर्णांक->atomic_flags);
	अगर (digsig)
		set_bit(IMA_DIGSIG, &iपूर्णांक->atomic_flags);
	अन्यथा
		clear_bit(IMA_DIGSIG, &iपूर्णांक->atomic_flags);
पूर्ण

पूर्णांक ima_inode_setxattr(काष्ठा dentry *dentry, स्थिर अक्षर *xattr_name,
		       स्थिर व्योम *xattr_value, माप_प्रकार xattr_value_len)
अणु
	स्थिर काष्ठा evm_ima_xattr_data *xvalue = xattr_value;
	पूर्णांक result;

	result = ima_protect_xattr(dentry, xattr_name, xattr_value,
				   xattr_value_len);
	अगर (result == 1) अणु
		अगर (!xattr_value_len || (xvalue->type >= IMA_XATTR_LAST))
			वापस -EINVAL;
		ima_reset_appउठाओ_flags(d_backing_inode(dentry),
			xvalue->type == EVM_IMA_XATTR_DIGSIG);
		result = 0;
	पूर्ण
	वापस result;
पूर्ण

पूर्णांक ima_inode_हटाओxattr(काष्ठा dentry *dentry, स्थिर अक्षर *xattr_name)
अणु
	पूर्णांक result;

	result = ima_protect_xattr(dentry, xattr_name, शून्य, 0);
	अगर (result == 1) अणु
		ima_reset_appउठाओ_flags(d_backing_inode(dentry), 0);
		result = 0;
	पूर्ण
	वापस result;
पूर्ण
