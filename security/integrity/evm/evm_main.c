<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2005-2010 IBM Corporation
 *
 * Author:
 * Mimi Zohar <zohar@us.ibm.com>
 * Kylene Hall <kjhall@us.ibm.com>
 *
 * File: evm_मुख्य.c
 *	implements evm_inode_setxattr, evm_inode_post_setxattr,
 *	evm_inode_हटाओxattr, and evm_verअगरyxattr
 */

#समावेश <linux/init.h>
#समावेश <linux/crypto.h>
#समावेश <linux/audit.h>
#समावेश <linux/xattr.h>
#समावेश <linux/पूर्णांकegrity.h>
#समावेश <linux/evm.h>
#समावेश <linux/magic.h>

#समावेश <crypto/hash.h>
#समावेश <crypto/hash_info.h>
#समावेश <crypto/algapi.h>
#समावेश "evm.h"

पूर्णांक evm_initialized;

अटल स्थिर अक्षर * स्थिर पूर्णांकegrity_status_msg[] = अणु
	"pass", "pass_immutable", "fail", "no_label", "no_xattrs", "unknown"
पूर्ण;
पूर्णांक evm_hmac_attrs;

अटल काष्ठा xattr_list evm_config_शेष_xattrnames[] = अणु
#अगर_घोषित CONFIG_SECURITY_SELINUX
	अणु.name = XATTR_NAME_SELINUXपूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SECURITY_SMACK
	अणु.name = XATTR_NAME_SMACKपूर्ण,
#अगर_घोषित CONFIG_EVM_EXTRA_SMACK_XATTRS
	अणु.name = XATTR_NAME_SMACKEXECपूर्ण,
	अणु.name = XATTR_NAME_SMACKTRANSMUTEपूर्ण,
	अणु.name = XATTR_NAME_SMACKMMAPपूर्ण,
#पूर्ण_अगर
#पूर्ण_अगर
#अगर_घोषित CONFIG_SECURITY_APPARMOR
	अणु.name = XATTR_NAME_APPARMORपूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_IMA_APPRAISE
	अणु.name = XATTR_NAME_IMAपूर्ण,
#पूर्ण_अगर
	अणु.name = XATTR_NAME_CAPSपूर्ण,
पूर्ण;

LIST_HEAD(evm_config_xattrnames);

अटल पूर्णांक evm_fixmode;
अटल पूर्णांक __init evm_set_fixmode(अक्षर *str)
अणु
	अगर (म_भेदन(str, "fix", 3) == 0)
		evm_fixmode = 1;
	अन्यथा
		pr_err("invalid \"%s\" mode", str);

	वापस 0;
पूर्ण
__setup("evm=", evm_set_fixmode);

अटल व्योम __init evm_init_config(व्योम)
अणु
	पूर्णांक i, xattrs;

	xattrs = ARRAY_SIZE(evm_config_शेष_xattrnames);

	pr_info("Initialising EVM extended attributes:\n");
	क्रम (i = 0; i < xattrs; i++) अणु
		pr_info("%s\n", evm_config_शेष_xattrnames[i].name);
		list_add_tail(&evm_config_शेष_xattrnames[i].list,
			      &evm_config_xattrnames);
	पूर्ण

#अगर_घोषित CONFIG_EVM_ATTR_FSUUID
	evm_hmac_attrs |= EVM_ATTR_FSUUID;
#पूर्ण_अगर
	pr_info("HMAC attrs: 0x%x\n", evm_hmac_attrs);
पूर्ण

अटल bool evm_key_loaded(व्योम)
अणु
	वापस (bool)(evm_initialized & EVM_KEY_MASK);
पूर्ण

अटल पूर्णांक evm_find_रक्षित_xattrs(काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_backing_inode(dentry);
	काष्ठा xattr_list *xattr;
	पूर्णांक error;
	पूर्णांक count = 0;

	अगर (!(inode->i_opflags & IOP_XATTR))
		वापस -EOPNOTSUPP;

	list_क्रम_each_entry_lockless(xattr, &evm_config_xattrnames, list) अणु
		error = __vfs_getxattr(dentry, inode, xattr->name, शून्य, 0);
		अगर (error < 0) अणु
			अगर (error == -ENODATA)
				जारी;
			वापस error;
		पूर्ण
		count++;
	पूर्ण

	वापस count;
पूर्ण

/*
 * evm_verअगरy_hmac - calculate and compare the HMAC with the EVM xattr
 *
 * Compute the HMAC on the dentry's रक्षित set of extended attributes
 * and compare it against the stored security.evm xattr.
 *
 * For perक्रमmance:
 * - use the previoulsy retrieved xattr value and length to calculate the
 *   HMAC.)
 * - cache the verअगरication result in the iपूर्णांक, when available.
 *
 * Returns पूर्णांकegrity status
 */
अटल क्रमागत पूर्णांकegrity_status evm_verअगरy_hmac(काष्ठा dentry *dentry,
					     स्थिर अक्षर *xattr_name,
					     अक्षर *xattr_value,
					     माप_प्रकार xattr_value_len,
					     काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक)
अणु
	काष्ठा evm_ima_xattr_data *xattr_data = शून्य;
	काष्ठा signature_v2_hdr *hdr;
	क्रमागत पूर्णांकegrity_status evm_status = INTEGRITY_PASS;
	काष्ठा evm_digest digest;
	काष्ठा inode *inode;
	पूर्णांक rc, xattr_len;

	अगर (iपूर्णांक && (iपूर्णांक->evm_status == INTEGRITY_PASS ||
		     iपूर्णांक->evm_status == INTEGRITY_PASS_IMMUTABLE))
		वापस iपूर्णांक->evm_status;

	/* अगर status is not PASS, try to check again - against -ENOMEM */

	/* first need to know the sig type */
	rc = vfs_getxattr_alloc(&init_user_ns, dentry, XATTR_NAME_EVM,
				(अक्षर **)&xattr_data, 0, GFP_NOFS);
	अगर (rc <= 0) अणु
		evm_status = INTEGRITY_FAIL;
		अगर (rc == -ENODATA) अणु
			rc = evm_find_रक्षित_xattrs(dentry);
			अगर (rc > 0)
				evm_status = INTEGRITY_NOLABEL;
			अन्यथा अगर (rc == 0)
				evm_status = INTEGRITY_NOXATTRS; /* new file */
		पूर्ण अन्यथा अगर (rc == -EOPNOTSUPP) अणु
			evm_status = INTEGRITY_UNKNOWN;
		पूर्ण
		जाओ out;
	पूर्ण

	xattr_len = rc;

	/* check value type */
	चयन (xattr_data->type) अणु
	हाल EVM_XATTR_HMAC:
		अगर (xattr_len != माप(काष्ठा evm_xattr)) अणु
			evm_status = INTEGRITY_FAIL;
			जाओ out;
		पूर्ण

		digest.hdr.algo = HASH_ALGO_SHA1;
		rc = evm_calc_hmac(dentry, xattr_name, xattr_value,
				   xattr_value_len, &digest);
		अगर (rc)
			अवरोध;
		rc = crypto_memneq(xattr_data->data, digest.digest,
				   SHA1_DIGEST_SIZE);
		अगर (rc)
			rc = -EINVAL;
		अवरोध;
	हाल EVM_IMA_XATTR_DIGSIG:
	हाल EVM_XATTR_PORTABLE_DIGSIG:
		/* accept xattr with non-empty signature field */
		अगर (xattr_len <= माप(काष्ठा signature_v2_hdr)) अणु
			evm_status = INTEGRITY_FAIL;
			जाओ out;
		पूर्ण

		hdr = (काष्ठा signature_v2_hdr *)xattr_data;
		digest.hdr.algo = hdr->hash_algo;
		rc = evm_calc_hash(dentry, xattr_name, xattr_value,
				   xattr_value_len, xattr_data->type, &digest);
		अगर (rc)
			अवरोध;
		rc = पूर्णांकegrity_digsig_verअगरy(INTEGRITY_KEYRING_EVM,
					(स्थिर अक्षर *)xattr_data, xattr_len,
					digest.digest, digest.hdr.length);
		अगर (!rc) अणु
			inode = d_backing_inode(dentry);

			अगर (xattr_data->type == EVM_XATTR_PORTABLE_DIGSIG) अणु
				अगर (iपूर्णांक)
					iपूर्णांक->flags |= EVM_IMMUTABLE_DIGSIG;
				evm_status = INTEGRITY_PASS_IMMUTABLE;
			पूर्ण अन्यथा अगर (!IS_RDONLY(inode) &&
				   !(inode->i_sb->s_पढ़ोonly_remount) &&
				   !IS_IMMUTABLE(inode)) अणु
				evm_update_evmxattr(dentry, xattr_name,
						    xattr_value,
						    xattr_value_len);
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		rc = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (rc)
		evm_status = (rc == -ENODATA) ?
				INTEGRITY_NOXATTRS : INTEGRITY_FAIL;
out:
	अगर (iपूर्णांक)
		iपूर्णांक->evm_status = evm_status;
	kमुक्त(xattr_data);
	वापस evm_status;
पूर्ण

अटल पूर्णांक evm_रक्षित_xattr(स्थिर अक्षर *req_xattr_name)
अणु
	पूर्णांक namelen;
	पूर्णांक found = 0;
	काष्ठा xattr_list *xattr;

	namelen = म_माप(req_xattr_name);
	list_क्रम_each_entry_lockless(xattr, &evm_config_xattrnames, list) अणु
		अगर ((म_माप(xattr->name) == namelen)
		    && (म_भेदन(req_xattr_name, xattr->name, namelen) == 0)) अणु
			found = 1;
			अवरोध;
		पूर्ण
		अगर (म_भेदन(req_xattr_name,
			    xattr->name + XATTR_SECURITY_PREFIX_LEN,
			    म_माप(req_xattr_name)) == 0) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस found;
पूर्ण

/**
 * evm_verअगरyxattr - verअगरy the पूर्णांकegrity of the requested xattr
 * @dentry: object of the verअगरy xattr
 * @xattr_name: requested xattr
 * @xattr_value: requested xattr value
 * @xattr_value_len: requested xattr value length
 *
 * Calculate the HMAC क्रम the given dentry and verअगरy it against the stored
 * security.evm xattr. For perक्रमmance, use the xattr value and length
 * previously retrieved to calculate the HMAC.
 *
 * Returns the xattr पूर्णांकegrity status.
 *
 * This function requires the caller to lock the inode's i_mutex beक्रमe it
 * is executed.
 */
क्रमागत पूर्णांकegrity_status evm_verअगरyxattr(काष्ठा dentry *dentry,
				      स्थिर अक्षर *xattr_name,
				      व्योम *xattr_value, माप_प्रकार xattr_value_len,
				      काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक)
अणु
	अगर (!evm_key_loaded() || !evm_रक्षित_xattr(xattr_name))
		वापस INTEGRITY_UNKNOWN;

	अगर (!iपूर्णांक) अणु
		iपूर्णांक = पूर्णांकegrity_iपूर्णांक_find(d_backing_inode(dentry));
		अगर (!iपूर्णांक)
			वापस INTEGRITY_UNKNOWN;
	पूर्ण
	वापस evm_verअगरy_hmac(dentry, xattr_name, xattr_value,
				 xattr_value_len, iपूर्णांक);
पूर्ण
EXPORT_SYMBOL_GPL(evm_verअगरyxattr);

/*
 * evm_verअगरy_current_पूर्णांकegrity - verअगरy the dentry's metadata पूर्णांकegrity
 * @dentry: poपूर्णांकer to the affected dentry
 *
 * Verअगरy and वापस the dentry's metadata पूर्णांकegrity. The exceptions are
 * beक्रमe EVM is initialized or in 'fix' mode.
 */
अटल क्रमागत पूर्णांकegrity_status evm_verअगरy_current_पूर्णांकegrity(काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_backing_inode(dentry);

	अगर (!evm_key_loaded() || !S_ISREG(inode->i_mode) || evm_fixmode)
		वापस 0;
	वापस evm_verअगरy_hmac(dentry, शून्य, शून्य, 0, शून्य);
पूर्ण

/*
 * evm_protect_xattr - protect the EVM extended attribute
 *
 * Prevent security.evm from being modअगरied or हटाओd without the
 * necessary permissions or when the existing value is invalid.
 *
 * The posix xattr acls are 'system' prefixed, which normally would not
 * affect security.evm.  An पूर्णांकeresting side affect of writing posix xattr
 * acls is their modअगरying of the i_mode, which is included in security.evm.
 * For posix xattr acls only, permit security.evm, even अगर it currently
 * करोesn't exist, to be updated unless the EVM signature is immutable.
 */
अटल पूर्णांक evm_protect_xattr(काष्ठा dentry *dentry, स्थिर अक्षर *xattr_name,
			     स्थिर व्योम *xattr_value, माप_प्रकार xattr_value_len)
अणु
	क्रमागत पूर्णांकegrity_status evm_status;

	अगर (म_भेद(xattr_name, XATTR_NAME_EVM) == 0) अणु
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;
	पूर्ण अन्यथा अगर (!evm_रक्षित_xattr(xattr_name)) अणु
		अगर (!posix_xattr_acl(xattr_name))
			वापस 0;
		evm_status = evm_verअगरy_current_पूर्णांकegrity(dentry);
		अगर ((evm_status == INTEGRITY_PASS) ||
		    (evm_status == INTEGRITY_NOXATTRS))
			वापस 0;
		जाओ out;
	पूर्ण

	evm_status = evm_verअगरy_current_पूर्णांकegrity(dentry);
	अगर (evm_status == INTEGRITY_NOXATTRS) अणु
		काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक;

		iपूर्णांक = पूर्णांकegrity_iपूर्णांक_find(d_backing_inode(dentry));
		अगर (iपूर्णांक && (iपूर्णांक->flags & IMA_NEW_खाता))
			वापस 0;

		/* exception क्रम pseuकरो fileप्रणालीs */
		अगर (dentry->d_sb->s_magic == TMPFS_MAGIC
		    || dentry->d_sb->s_magic == SYSFS_MAGIC)
			वापस 0;

		पूर्णांकegrity_audit_msg(AUDIT_INTEGRITY_METADATA,
				    dentry->d_inode, dentry->d_name.name,
				    "update_metadata",
				    पूर्णांकegrity_status_msg[evm_status],
				    -EPERM, 0);
	पूर्ण
out:
	अगर (evm_status != INTEGRITY_PASS)
		पूर्णांकegrity_audit_msg(AUDIT_INTEGRITY_METADATA, d_backing_inode(dentry),
				    dentry->d_name.name, "appraise_metadata",
				    पूर्णांकegrity_status_msg[evm_status],
				    -EPERM, 0);
	वापस evm_status == INTEGRITY_PASS ? 0 : -EPERM;
पूर्ण

/**
 * evm_inode_setxattr - protect the EVM extended attribute
 * @dentry: poपूर्णांकer to the affected dentry
 * @xattr_name: poपूर्णांकer to the affected extended attribute name
 * @xattr_value: poपूर्णांकer to the new extended attribute value
 * @xattr_value_len: poपूर्णांकer to the new extended attribute value length
 *
 * Beक्रमe allowing the 'security.evm' रक्षित xattr to be updated,
 * verअगरy the existing value is valid.  As only the kernel should have
 * access to the EVM encrypted key needed to calculate the HMAC, prevent
 * userspace from writing HMAC value.  Writing 'security.evm' requires
 * requires CAP_SYS_ADMIN privileges.
 */
पूर्णांक evm_inode_setxattr(काष्ठा dentry *dentry, स्थिर अक्षर *xattr_name,
		       स्थिर व्योम *xattr_value, माप_प्रकार xattr_value_len)
अणु
	स्थिर काष्ठा evm_ima_xattr_data *xattr_data = xattr_value;

	/* Policy permits modअगरication of the रक्षित xattrs even though
	 * there's no HMAC key loaded
	 */
	अगर (evm_initialized & EVM_ALLOW_METADATA_WRITES)
		वापस 0;

	अगर (म_भेद(xattr_name, XATTR_NAME_EVM) == 0) अणु
		अगर (!xattr_value_len)
			वापस -EINVAL;
		अगर (xattr_data->type != EVM_IMA_XATTR_DIGSIG &&
		    xattr_data->type != EVM_XATTR_PORTABLE_DIGSIG)
			वापस -EPERM;
	पूर्ण
	वापस evm_protect_xattr(dentry, xattr_name, xattr_value,
				 xattr_value_len);
पूर्ण

/**
 * evm_inode_हटाओxattr - protect the EVM extended attribute
 * @dentry: poपूर्णांकer to the affected dentry
 * @xattr_name: poपूर्णांकer to the affected extended attribute name
 *
 * Removing 'security.evm' requires CAP_SYS_ADMIN privileges and that
 * the current value is valid.
 */
पूर्णांक evm_inode_हटाओxattr(काष्ठा dentry *dentry, स्थिर अक्षर *xattr_name)
अणु
	/* Policy permits modअगरication of the रक्षित xattrs even though
	 * there's no HMAC key loaded
	 */
	अगर (evm_initialized & EVM_ALLOW_METADATA_WRITES)
		वापस 0;

	वापस evm_protect_xattr(dentry, xattr_name, शून्य, 0);
पूर्ण

अटल व्योम evm_reset_status(काष्ठा inode *inode)
अणु
	काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक;

	iपूर्णांक = पूर्णांकegrity_iपूर्णांक_find(inode);
	अगर (iपूर्णांक)
		iपूर्णांक->evm_status = INTEGRITY_UNKNOWN;
पूर्ण

/**
 * evm_inode_post_setxattr - update 'security.evm' to reflect the changes
 * @dentry: poपूर्णांकer to the affected dentry
 * @xattr_name: poपूर्णांकer to the affected extended attribute name
 * @xattr_value: poपूर्णांकer to the new extended attribute value
 * @xattr_value_len: poपूर्णांकer to the new extended attribute value length
 *
 * Update the HMAC stored in 'security.evm' to reflect the change.
 *
 * No need to take the i_mutex lock here, as this function is called from
 * __vfs_setxattr_noperm().  The caller of which has taken the inode's
 * i_mutex lock.
 */
व्योम evm_inode_post_setxattr(काष्ठा dentry *dentry, स्थिर अक्षर *xattr_name,
			     स्थिर व्योम *xattr_value, माप_प्रकार xattr_value_len)
अणु
	अगर (!evm_key_loaded() || (!evm_रक्षित_xattr(xattr_name)
				  && !posix_xattr_acl(xattr_name)))
		वापस;

	evm_reset_status(dentry->d_inode);

	evm_update_evmxattr(dentry, xattr_name, xattr_value, xattr_value_len);
पूर्ण

/**
 * evm_inode_post_हटाओxattr - update 'security.evm' after removing the xattr
 * @dentry: poपूर्णांकer to the affected dentry
 * @xattr_name: poपूर्णांकer to the affected extended attribute name
 *
 * Update the HMAC stored in 'security.evm' to reflect removal of the xattr.
 *
 * No need to take the i_mutex lock here, as this function is called from
 * vfs_हटाओxattr() which takes the i_mutex.
 */
व्योम evm_inode_post_हटाओxattr(काष्ठा dentry *dentry, स्थिर अक्षर *xattr_name)
अणु
	अगर (!evm_key_loaded() || !evm_रक्षित_xattr(xattr_name))
		वापस;

	evm_reset_status(dentry->d_inode);

	evm_update_evmxattr(dentry, xattr_name, शून्य, 0);
पूर्ण

/**
 * evm_inode_setattr - prevent updating an invalid EVM extended attribute
 * @dentry: poपूर्णांकer to the affected dentry
 *
 * Permit update of file attributes when files have a valid EVM signature,
 * except in the हाल of them having an immutable portable signature.
 */
पूर्णांक evm_inode_setattr(काष्ठा dentry *dentry, काष्ठा iattr *attr)
अणु
	अचिन्हित पूर्णांक ia_valid = attr->ia_valid;
	क्रमागत पूर्णांकegrity_status evm_status;

	/* Policy permits modअगरication of the रक्षित attrs even though
	 * there's no HMAC key loaded
	 */
	अगर (evm_initialized & EVM_ALLOW_METADATA_WRITES)
		वापस 0;

	अगर (!(ia_valid & (ATTR_MODE | ATTR_UID | ATTR_GID)))
		वापस 0;
	evm_status = evm_verअगरy_current_पूर्णांकegrity(dentry);
	अगर ((evm_status == INTEGRITY_PASS) ||
	    (evm_status == INTEGRITY_NOXATTRS))
		वापस 0;
	पूर्णांकegrity_audit_msg(AUDIT_INTEGRITY_METADATA, d_backing_inode(dentry),
			    dentry->d_name.name, "appraise_metadata",
			    पूर्णांकegrity_status_msg[evm_status], -EPERM, 0);
	वापस -EPERM;
पूर्ण

/**
 * evm_inode_post_setattr - update 'security.evm' after modअगरying metadata
 * @dentry: poपूर्णांकer to the affected dentry
 * @ia_valid: क्रम the UID and GID status
 *
 * For now, update the HMAC stored in 'security.evm' to reflect UID/GID
 * changes.
 *
 * This function is called from notअगरy_change(), which expects the caller
 * to lock the inode's i_mutex.
 */
व्योम evm_inode_post_setattr(काष्ठा dentry *dentry, पूर्णांक ia_valid)
अणु
	अगर (!evm_key_loaded())
		वापस;

	अगर (ia_valid & (ATTR_MODE | ATTR_UID | ATTR_GID))
		evm_update_evmxattr(dentry, शून्य, शून्य, 0);
पूर्ण

/*
 * evm_inode_init_security - initializes security.evm
 */
पूर्णांक evm_inode_init_security(काष्ठा inode *inode,
				 स्थिर काष्ठा xattr *lsm_xattr,
				 काष्ठा xattr *evm_xattr)
अणु
	काष्ठा evm_xattr *xattr_data;
	पूर्णांक rc;

	अगर (!evm_key_loaded() || !evm_रक्षित_xattr(lsm_xattr->name))
		वापस 0;

	xattr_data = kzalloc(माप(*xattr_data), GFP_NOFS);
	अगर (!xattr_data)
		वापस -ENOMEM;

	xattr_data->data.type = EVM_XATTR_HMAC;
	rc = evm_init_hmac(inode, lsm_xattr, xattr_data->digest);
	अगर (rc < 0)
		जाओ out;

	evm_xattr->value = xattr_data;
	evm_xattr->value_len = माप(*xattr_data);
	evm_xattr->name = XATTR_EVM_SUFFIX;
	वापस 0;
out:
	kमुक्त(xattr_data);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(evm_inode_init_security);

#अगर_घोषित CONFIG_EVM_LOAD_X509
व्योम __init evm_load_x509(व्योम)
अणु
	पूर्णांक rc;

	rc = पूर्णांकegrity_load_x509(INTEGRITY_KEYRING_EVM, CONFIG_EVM_X509_PATH);
	अगर (!rc)
		evm_initialized |= EVM_INIT_X509;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init init_evm(व्योम)
अणु
	पूर्णांक error;
	काष्ठा list_head *pos, *q;

	evm_init_config();

	error = पूर्णांकegrity_init_keyring(INTEGRITY_KEYRING_EVM);
	अगर (error)
		जाओ error;

	error = evm_init_secfs();
	अगर (error < 0) अणु
		pr_info("Error registering secfs\n");
		जाओ error;
	पूर्ण

error:
	अगर (error != 0) अणु
		अगर (!list_empty(&evm_config_xattrnames)) अणु
			list_क्रम_each_safe(pos, q, &evm_config_xattrnames)
				list_del(pos);
		पूर्ण
	पूर्ण

	वापस error;
पूर्ण

late_initcall(init_evm);
