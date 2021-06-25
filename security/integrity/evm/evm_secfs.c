<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2010 IBM Corporation
 *
 * Authors:
 * Mimi Zohar <zohar@us.ibm.com>
 *
 * File: evm_secfs.c
 *	- Used to संकेत when key is on keyring
 *	- Get the key and enable EVM
 */

#समावेश <linux/audit.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/init.h>
#समावेश <linux/mutex.h>
#समावेश "evm.h"

अटल काष्ठा dentry *evm_dir;
अटल काष्ठा dentry *evm_init_tpm;
अटल काष्ठा dentry *evm_symlink;

#अगर_घोषित CONFIG_EVM_ADD_XATTRS
अटल काष्ठा dentry *evm_xattrs;
अटल DEFINE_MUTEX(xattr_list_mutex);
अटल पूर्णांक evm_xattrs_locked;
#पूर्ण_अगर

/**
 * evm_पढ़ो_key - पढ़ो() क्रम <securityfs>/evm
 *
 * @filp: file poपूर्णांकer, not actually used
 * @buf: where to put the result
 * @count: maximum to send aदीर्घ
 * @ppos: where to start
 *
 * Returns number of bytes पढ़ो or error code, as appropriate
 */
अटल sमाप_प्रकार evm_पढ़ो_key(काष्ठा file *filp, अक्षर __user *buf,
			    माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर temp[80];
	sमाप_प्रकार rc;

	अगर (*ppos != 0)
		वापस 0;

	प्र_लिखो(temp, "%d", (evm_initialized & ~EVM_SETUP_COMPLETE));
	rc = simple_पढ़ो_from_buffer(buf, count, ppos, temp, म_माप(temp));

	वापस rc;
पूर्ण

/**
 * evm_ग_लिखो_key - ग_लिखो() क्रम <securityfs>/evm
 * @file: file poपूर्णांकer, not actually used
 * @buf: where to get the data from
 * @count: bytes sent
 * @ppos: where to start
 *
 * Used to संकेत that key is on the kernel key ring.
 * - get the पूर्णांकegrity hmac key from the kernel key ring
 * - create list of hmac रक्षित extended attributes
 * Returns number of bytes written or error code, as appropriate
 */
अटल sमाप_प्रकार evm_ग_लिखो_key(काष्ठा file *file, स्थिर अक्षर __user *buf,
			     माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक i, ret;

	अगर (!capable(CAP_SYS_ADMIN) || (evm_initialized & EVM_SETUP_COMPLETE))
		वापस -EPERM;

	ret = kstrtoपूर्णांक_from_user(buf, count, 0, &i);

	अगर (ret)
		वापस ret;

	/* Reject invalid values */
	अगर (!i || (i & ~EVM_INIT_MASK) != 0)
		वापस -EINVAL;

	/* Don't allow a request to freshly enable metadata ग_लिखोs अगर
	 * keys are loaded.
	 */
	अगर ((i & EVM_ALLOW_METADATA_WRITES) &&
	    ((evm_initialized & EVM_KEY_MASK) != 0) &&
	    !(evm_initialized & EVM_ALLOW_METADATA_WRITES))
		वापस -EPERM;

	अगर (i & EVM_INIT_HMAC) अणु
		ret = evm_init_key();
		अगर (ret != 0)
			वापस ret;
		/* Forbid further ग_लिखोs after the symmetric key is loaded */
		i |= EVM_SETUP_COMPLETE;
	पूर्ण

	evm_initialized |= i;

	/* Don't allow रक्षित metadata modअगरication अगर a symmetric key
	 * is loaded
	 */
	अगर (evm_initialized & EVM_INIT_HMAC)
		evm_initialized &= ~(EVM_ALLOW_METADATA_WRITES);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations evm_key_ops = अणु
	.पढ़ो		= evm_पढ़ो_key,
	.ग_लिखो		= evm_ग_लिखो_key,
पूर्ण;

#अगर_घोषित CONFIG_EVM_ADD_XATTRS
/**
 * evm_पढ़ो_xattrs - पढ़ो() क्रम <securityfs>/evm_xattrs
 *
 * @filp: file poपूर्णांकer, not actually used
 * @buf: where to put the result
 * @count: maximum to send aदीर्घ
 * @ppos: where to start
 *
 * Returns number of bytes पढ़ो or error code, as appropriate
 */
अटल sमाप_प्रकार evm_पढ़ो_xattrs(काष्ठा file *filp, अक्षर __user *buf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर *temp;
	पूर्णांक offset = 0;
	sमाप_प्रकार rc, size = 0;
	काष्ठा xattr_list *xattr;

	अगर (*ppos != 0)
		वापस 0;

	rc = mutex_lock_पूर्णांकerruptible(&xattr_list_mutex);
	अगर (rc)
		वापस -ERESTARTSYS;

	list_क्रम_each_entry(xattr, &evm_config_xattrnames, list)
		size += म_माप(xattr->name) + 1;

	temp = kदो_स्मृति(size + 1, GFP_KERNEL);
	अगर (!temp) अणु
		mutex_unlock(&xattr_list_mutex);
		वापस -ENOMEM;
	पूर्ण

	list_क्रम_each_entry(xattr, &evm_config_xattrnames, list) अणु
		प्र_लिखो(temp + offset, "%s\n", xattr->name);
		offset += म_माप(xattr->name) + 1;
	पूर्ण

	mutex_unlock(&xattr_list_mutex);
	rc = simple_पढ़ो_from_buffer(buf, count, ppos, temp, म_माप(temp));

	kमुक्त(temp);

	वापस rc;
पूर्ण

/**
 * evm_ग_लिखो_xattrs - ग_लिखो() क्रम <securityfs>/evm_xattrs
 * @file: file poपूर्णांकer, not actually used
 * @buf: where to get the data from
 * @count: bytes sent
 * @ppos: where to start
 *
 * Returns number of bytes written or error code, as appropriate
 */
अटल sमाप_प्रकार evm_ग_लिखो_xattrs(काष्ठा file *file, स्थिर अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक len, err;
	काष्ठा xattr_list *xattr, *पंचांगp;
	काष्ठा audit_buffer *ab;
	काष्ठा iattr newattrs;
	काष्ठा inode *inode;

	अगर (!capable(CAP_SYS_ADMIN) || evm_xattrs_locked)
		वापस -EPERM;

	अगर (*ppos != 0)
		वापस -EINVAL;

	अगर (count > XATTR_NAME_MAX)
		वापस -E2BIG;

	ab = audit_log_start(audit_context(), GFP_KERNEL,
			     AUDIT_INTEGRITY_EVM_XATTR);
	अगर (!ab)
		वापस -ENOMEM;

	xattr = kदो_स्मृति(माप(काष्ठा xattr_list), GFP_KERNEL);
	अगर (!xattr) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	xattr->name = memdup_user_nul(buf, count);
	अगर (IS_ERR(xattr->name)) अणु
		err = PTR_ERR(xattr->name);
		xattr->name = शून्य;
		जाओ out;
	पूर्ण

	/* Remove any trailing newline */
	len = म_माप(xattr->name);
	अगर (len && xattr->name[len-1] == '\n')
		xattr->name[len-1] = '\0';

	audit_log_क्रमmat(ab, "xattr=");
	audit_log_untrustedstring(ab, xattr->name);

	अगर (म_भेद(xattr->name, ".") == 0) अणु
		evm_xattrs_locked = 1;
		newattrs.ia_mode = S_IFREG | 0440;
		newattrs.ia_valid = ATTR_MODE;
		inode = evm_xattrs->d_inode;
		inode_lock(inode);
		err = simple_setattr(&init_user_ns, evm_xattrs, &newattrs);
		inode_unlock(inode);
		अगर (!err)
			err = count;
		जाओ out;
	पूर्ण

	अगर (म_भेदन(xattr->name, XATTR_SECURITY_PREFIX,
		    XATTR_SECURITY_PREFIX_LEN) != 0) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	/*
	 * xattr_list_mutex guards against races in evm_पढ़ो_xattrs().
	 * Entries are only added to the evm_config_xattrnames list
	 * and never deleted. Thereक्रमe, the list is traversed
	 * using list_क्रम_each_entry_lockless() without holding
	 * the mutex in evm_calc_hmac_or_hash(), evm_find_रक्षित_xattrs()
	 * and evm_रक्षित_xattr().
	 */
	mutex_lock(&xattr_list_mutex);
	list_क्रम_each_entry(पंचांगp, &evm_config_xattrnames, list) अणु
		अगर (म_भेद(xattr->name, पंचांगp->name) == 0) अणु
			err = -EEXIST;
			mutex_unlock(&xattr_list_mutex);
			जाओ out;
		पूर्ण
	पूर्ण
	list_add_tail_rcu(&xattr->list, &evm_config_xattrnames);
	mutex_unlock(&xattr_list_mutex);

	audit_log_क्रमmat(ab, " res=0");
	audit_log_end(ab);
	वापस count;
out:
	audit_log_क्रमmat(ab, " res=%d", err);
	audit_log_end(ab);
	अगर (xattr) अणु
		kमुक्त(xattr->name);
		kमुक्त(xattr);
	पूर्ण
	वापस err;
पूर्ण

अटल स्थिर काष्ठा file_operations evm_xattr_ops = अणु
	.पढ़ो		= evm_पढ़ो_xattrs,
	.ग_लिखो		= evm_ग_लिखो_xattrs,
पूर्ण;

अटल पूर्णांक evm_init_xattrs(व्योम)
अणु
	evm_xattrs = securityfs_create_file("evm_xattrs", 0660, evm_dir, शून्य,
					    &evm_xattr_ops);
	अगर (!evm_xattrs || IS_ERR(evm_xattrs))
		वापस -EFAULT;

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक evm_init_xattrs(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

पूर्णांक __init evm_init_secfs(व्योम)
अणु
	पूर्णांक error = 0;

	evm_dir = securityfs_create_dir("evm", पूर्णांकegrity_dir);
	अगर (!evm_dir || IS_ERR(evm_dir))
		वापस -EFAULT;

	evm_init_tpm = securityfs_create_file("evm", 0660,
					      evm_dir, शून्य, &evm_key_ops);
	अगर (!evm_init_tpm || IS_ERR(evm_init_tpm)) अणु
		error = -EFAULT;
		जाओ out;
	पूर्ण

	evm_symlink = securityfs_create_symlink("evm", शून्य,
						"integrity/evm/evm", शून्य);
	अगर (!evm_symlink || IS_ERR(evm_symlink)) अणु
		error = -EFAULT;
		जाओ out;
	पूर्ण

	अगर (evm_init_xattrs() != 0) अणु
		error = -EFAULT;
		जाओ out;
	पूर्ण

	वापस 0;
out:
	securityfs_हटाओ(evm_symlink);
	securityfs_हटाओ(evm_init_tpm);
	securityfs_हटाओ(evm_dir);
	वापस error;
पूर्ण
