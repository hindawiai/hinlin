<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Integrity Measurement Architecture
 *
 * Copyright (C) 2005,2006,2007,2008 IBM Corporation
 *
 * Authors:
 * Reiner Sailer <sailer@watson.ibm.com>
 * Serge Hallyn <serue@us.ibm.com>
 * Kylene Hall <kylene@us.ibm.com>
 * Mimi Zohar <zohar@us.ibm.com>
 *
 * File: ima_मुख्य.c
 *	implements the IMA hooks: ima_bprm_check, ima_file_mmap,
 *	and ima_file_check.
 */

#समावेश <linux/module.h>
#समावेश <linux/file.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/kernel_पढ़ो_file.h>
#समावेश <linux/mount.h>
#समावेश <linux/mman.h>
#समावेश <linux/slab.h>
#समावेश <linux/xattr.h>
#समावेश <linux/ima.h>
#समावेश <linux/iversion.h>
#समावेश <linux/fs.h>

#समावेश "ima.h"

#अगर_घोषित CONFIG_IMA_APPRAISE
पूर्णांक ima_appउठाओ = IMA_APPRAISE_ENFORCE;
#अन्यथा
पूर्णांक ima_appउठाओ;
#पूर्ण_अगर

पूर्णांक ima_hash_algo = HASH_ALGO_SHA1;
अटल पूर्णांक hash_setup_करोne;

अटल काष्ठा notअगरier_block ima_lsm_policy_notअगरier = अणु
	.notअगरier_call = ima_lsm_policy_change,
पूर्ण;

अटल पूर्णांक __init hash_setup(अक्षर *str)
अणु
	काष्ठा ima_ढाँचा_desc *ढाँचा_desc = ima_ढाँचा_desc_current();
	पूर्णांक i;

	अगर (hash_setup_करोne)
		वापस 1;

	अगर (म_भेद(ढाँचा_desc->name, IMA_TEMPLATE_IMA_NAME) == 0) अणु
		अगर (म_भेदन(str, "sha1", 4) == 0) अणु
			ima_hash_algo = HASH_ALGO_SHA1;
		पूर्ण अन्यथा अगर (म_भेदन(str, "md5", 3) == 0) अणु
			ima_hash_algo = HASH_ALGO_MD5;
		पूर्ण अन्यथा अणु
			pr_err("invalid hash algorithm \"%s\" for template \"%s\"",
				str, IMA_TEMPLATE_IMA_NAME);
			वापस 1;
		पूर्ण
		जाओ out;
	पूर्ण

	i = match_string(hash_algo_name, HASH_ALGO__LAST, str);
	अगर (i < 0) अणु
		pr_err("invalid hash algorithm \"%s\"", str);
		वापस 1;
	पूर्ण

	ima_hash_algo = i;
out:
	hash_setup_करोne = 1;
	वापस 1;
पूर्ण
__setup("ima_hash=", hash_setup);

/* Prevent mmap'ing a file execute that is already mmap'ed ग_लिखो */
अटल पूर्णांक mmap_violation_check(क्रमागत ima_hooks func, काष्ठा file *file,
				अक्षर **pathbuf, स्थिर अक्षर **pathname,
				अक्षर *filename)
अणु
	काष्ठा inode *inode;
	पूर्णांक rc = 0;

	अगर ((func == MMAP_CHECK) && mapping_writably_mapped(file->f_mapping)) अणु
		rc = -ETXTBSY;
		inode = file_inode(file);

		अगर (!*pathbuf)	/* ima_rdwr_violation possibly pre-fetched */
			*pathname = ima_d_path(&file->f_path, pathbuf,
					       filename);
		पूर्णांकegrity_audit_msg(AUDIT_INTEGRITY_DATA, inode, *pathname,
				    "mmap_file", "mmapped_writers", rc, 0);
	पूर्ण
	वापस rc;
पूर्ण

/*
 * ima_rdwr_violation_check
 *
 * Only invalidate the PCR क्रम measured files:
 *	- Opening a file क्रम ग_लिखो when alपढ़ोy खोलो क्रम पढ़ो,
 *	  results in a समय of measure, समय of use (ToMToU) error.
 *	- Opening a file क्रम पढ़ो when alपढ़ोy खोलो क्रम ग_लिखो,
 *	  could result in a file measurement error.
 *
 */
अटल व्योम ima_rdwr_violation_check(काष्ठा file *file,
				     काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक,
				     पूर्णांक must_measure,
				     अक्षर **pathbuf,
				     स्थिर अक्षर **pathname,
				     अक्षर *filename)
अणु
	काष्ठा inode *inode = file_inode(file);
	भ_शेषe_t mode = file->f_mode;
	bool send_tomtou = false, send_ग_लिखोrs = false;

	अगर (mode & FMODE_WRITE) अणु
		अगर (atomic_पढ़ो(&inode->i_पढ़ोcount) && IS_IMA(inode)) अणु
			अगर (!iपूर्णांक)
				iपूर्णांक = पूर्णांकegrity_iपूर्णांक_find(inode);
			/* IMA_MEASURE is set from पढ़ोer side */
			अगर (iपूर्णांक && test_bit(IMA_MUST_MEASURE,
						&iपूर्णांक->atomic_flags))
				send_tomtou = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (must_measure)
			set_bit(IMA_MUST_MEASURE, &iपूर्णांक->atomic_flags);
		अगर (inode_is_खोलो_क्रम_ग_लिखो(inode) && must_measure)
			send_ग_लिखोrs = true;
	पूर्ण

	अगर (!send_tomtou && !send_ग_लिखोrs)
		वापस;

	*pathname = ima_d_path(&file->f_path, pathbuf, filename);

	अगर (send_tomtou)
		ima_add_violation(file, *pathname, iपूर्णांक,
				  "invalid_pcr", "ToMToU");
	अगर (send_ग_लिखोrs)
		ima_add_violation(file, *pathname, iपूर्णांक,
				  "invalid_pcr", "open_writers");
पूर्ण

अटल व्योम ima_check_last_ग_लिखोr(काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक,
				  काष्ठा inode *inode, काष्ठा file *file)
अणु
	भ_शेषe_t mode = file->f_mode;
	bool update;

	अगर (!(mode & FMODE_WRITE))
		वापस;

	mutex_lock(&iपूर्णांक->mutex);
	अगर (atomic_पढ़ो(&inode->i_ग_लिखोcount) == 1) अणु
		update = test_and_clear_bit(IMA_UPDATE_XATTR,
					    &iपूर्णांक->atomic_flags);
		अगर (!IS_I_VERSION(inode) ||
		    !inode_eq_iversion(inode, iपूर्णांक->version) ||
		    (iपूर्णांक->flags & IMA_NEW_खाता)) अणु
			iपूर्णांक->flags &= ~(IMA_DONE_MASK | IMA_NEW_खाता);
			iपूर्णांक->measured_pcrs = 0;
			अगर (update)
				ima_update_xattr(iपूर्णांक, file);
		पूर्ण
	पूर्ण
	mutex_unlock(&iपूर्णांक->mutex);
पूर्ण

/**
 * ima_file_मुक्त - called on __fput()
 * @file: poपूर्णांकer to file काष्ठाure being मुक्तd
 *
 * Flag files that changed, based on i_version
 */
व्योम ima_file_मुक्त(काष्ठा file *file)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक;

	अगर (!ima_policy_flag || !S_ISREG(inode->i_mode))
		वापस;

	iपूर्णांक = पूर्णांकegrity_iपूर्णांक_find(inode);
	अगर (!iपूर्णांक)
		वापस;

	ima_check_last_ग_लिखोr(iपूर्णांक, inode, file);
पूर्ण

अटल पूर्णांक process_measurement(काष्ठा file *file, स्थिर काष्ठा cred *cred,
			       u32 secid, अक्षर *buf, loff_t size, पूर्णांक mask,
			       क्रमागत ima_hooks func)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक = शून्य;
	काष्ठा ima_ढाँचा_desc *ढाँचा_desc = शून्य;
	अक्षर *pathbuf = शून्य;
	अक्षर filename[NAME_MAX];
	स्थिर अक्षर *pathname = शून्य;
	पूर्णांक rc = 0, action, must_appउठाओ = 0;
	पूर्णांक pcr = CONFIG_IMA_MEASURE_PCR_IDX;
	काष्ठा evm_ima_xattr_data *xattr_value = शून्य;
	काष्ठा modsig *modsig = शून्य;
	पूर्णांक xattr_len = 0;
	bool violation_check;
	क्रमागत hash_algo hash_algo;

	अगर (!ima_policy_flag || !S_ISREG(inode->i_mode))
		वापस 0;

	/* Return an IMA_MEASURE, IMA_APPRAISE, IMA_AUDIT action
	 * biपंचांगask based on the appउठाओ/audit/measurement policy.
	 * Included is the appउठाओ submask.
	 */
	action = ima_get_action(file_mnt_user_ns(file), inode, cred, secid,
				mask, func, &pcr, &ढाँचा_desc, शून्य);
	violation_check = ((func == खाता_CHECK || func == MMAP_CHECK) &&
			   (ima_policy_flag & IMA_MEASURE));
	अगर (!action && !violation_check)
		वापस 0;

	must_appउठाओ = action & IMA_APPRAISE;

	/*  Is the appउठाओ rule hook specअगरic?  */
	अगर (action & IMA_खाता_APPRAISE)
		func = खाता_CHECK;

	inode_lock(inode);

	अगर (action) अणु
		iपूर्णांक = पूर्णांकegrity_inode_get(inode);
		अगर (!iपूर्णांक)
			rc = -ENOMEM;
	पूर्ण

	अगर (!rc && violation_check)
		ima_rdwr_violation_check(file, iपूर्णांक, action & IMA_MEASURE,
					 &pathbuf, &pathname, filename);

	inode_unlock(inode);

	अगर (rc)
		जाओ out;
	अगर (!action)
		जाओ out;

	mutex_lock(&iपूर्णांक->mutex);

	अगर (test_and_clear_bit(IMA_CHANGE_ATTR, &iपूर्णांक->atomic_flags))
		/* reset appraisal flags अगर ima_inode_post_setattr was called */
		iपूर्णांक->flags &= ~(IMA_APPRAISE | IMA_APPRAISED |
				 IMA_APPRAISE_SUBMASK | IMA_APPRAISED_SUBMASK |
				 IMA_ACTION_FLAGS);

	/*
	 * Re-evaulate the file अगर either the xattr has changed or the
	 * kernel has no way of detecting file change on the fileप्रणाली.
	 * (Limited to privileged mounted fileप्रणालीs.)
	 */
	अगर (test_and_clear_bit(IMA_CHANGE_XATTR, &iपूर्णांक->atomic_flags) ||
	    ((inode->i_sb->s_अगरlags & SB_I_IMA_UNVERIFIABLE_SIGNATURE) &&
	     !(inode->i_sb->s_अगरlags & SB_I_UNTRUSTED_MOUNTER) &&
	     !(action & IMA_FAIL_UNVERIFIABLE_SIGS))) अणु
		iपूर्णांक->flags &= ~IMA_DONE_MASK;
		iपूर्णांक->measured_pcrs = 0;
	पूर्ण

	/* Determine अगर alपढ़ोy appउठाओd/measured based on biपंचांगask
	 * (IMA_MEASURE, IMA_MEASURED, IMA_XXXX_APPRAISE, IMA_XXXX_APPRAISED,
	 *  IMA_AUDIT, IMA_AUDITED)
	 */
	iपूर्णांक->flags |= action;
	action &= IMA_DO_MASK;
	action &= ~((iपूर्णांक->flags & (IMA_DONE_MASK ^ IMA_MEASURED)) >> 1);

	/* If target pcr is alपढ़ोy measured, unset IMA_MEASURE action */
	अगर ((action & IMA_MEASURE) && (iपूर्णांक->measured_pcrs & (0x1 << pcr)))
		action ^= IMA_MEASURE;

	/* HASH sets the digital signature and update flags, nothing अन्यथा */
	अगर ((action & IMA_HASH) &&
	    !(test_bit(IMA_DIGSIG, &iपूर्णांक->atomic_flags))) अणु
		xattr_len = ima_पढ़ो_xattr(file_dentry(file), &xattr_value);
		अगर ((xattr_value && xattr_len > 2) &&
		    (xattr_value->type == EVM_IMA_XATTR_DIGSIG))
			set_bit(IMA_DIGSIG, &iपूर्णांक->atomic_flags);
		iपूर्णांक->flags |= IMA_HASHED;
		action ^= IMA_HASH;
		set_bit(IMA_UPDATE_XATTR, &iपूर्णांक->atomic_flags);
	पूर्ण

	/* Nothing to करो, just वापस existing appउठाओd status */
	अगर (!action) अणु
		अगर (must_appउठाओ) अणु
			rc = mmap_violation_check(func, file, &pathbuf,
						  &pathname, filename);
			अगर (!rc)
				rc = ima_get_cache_status(iपूर्णांक, func);
		पूर्ण
		जाओ out_locked;
	पूर्ण

	अगर ((action & IMA_APPRAISE_SUBMASK) ||
	    म_भेद(ढाँचा_desc->name, IMA_TEMPLATE_IMA_NAME) != 0) अणु
		/* पढ़ो 'security.ima' */
		xattr_len = ima_पढ़ो_xattr(file_dentry(file), &xattr_value);

		/*
		 * Read the appended modsig अगर allowed by the policy, and allow
		 * an additional measurement list entry, अगर needed, based on the
		 * ढाँचा क्रमmat and whether the file was alपढ़ोy measured.
		 */
		अगर (iपूर्णांक->flags & IMA_MODSIG_ALLOWED) अणु
			rc = ima_पढ़ो_modsig(func, buf, size, &modsig);

			अगर (!rc && ima_ढाँचा_has_modsig(ढाँचा_desc) &&
			    iपूर्णांक->flags & IMA_MEASURED)
				action |= IMA_MEASURE;
		पूर्ण
	पूर्ण

	hash_algo = ima_get_hash_algo(xattr_value, xattr_len);

	rc = ima_collect_measurement(iपूर्णांक, file, buf, size, hash_algo, modsig);
	अगर (rc != 0 && rc != -EBADF && rc != -EINVAL)
		जाओ out_locked;

	अगर (!pathbuf)	/* ima_rdwr_violation possibly pre-fetched */
		pathname = ima_d_path(&file->f_path, &pathbuf, filename);

	अगर (action & IMA_MEASURE)
		ima_store_measurement(iपूर्णांक, file, pathname,
				      xattr_value, xattr_len, modsig, pcr,
				      ढाँचा_desc);
	अगर (rc == 0 && (action & IMA_APPRAISE_SUBMASK)) अणु
		rc = ima_check_blacklist(iपूर्णांक, modsig, pcr);
		अगर (rc != -EPERM) अणु
			inode_lock(inode);
			rc = ima_appउठाओ_measurement(func, iपूर्णांक, file,
						      pathname, xattr_value,
						      xattr_len, modsig);
			inode_unlock(inode);
		पूर्ण
		अगर (!rc)
			rc = mmap_violation_check(func, file, &pathbuf,
						  &pathname, filename);
	पूर्ण
	अगर (action & IMA_AUDIT)
		ima_audit_measurement(iपूर्णांक, pathname);

	अगर ((file->f_flags & O_सूचीECT) && (iपूर्णांक->flags & IMA_PERMIT_सूचीECTIO))
		rc = 0;
out_locked:
	अगर ((mask & MAY_WRITE) && test_bit(IMA_DIGSIG, &iपूर्णांक->atomic_flags) &&
	     !(iपूर्णांक->flags & IMA_NEW_खाता))
		rc = -EACCES;
	mutex_unlock(&iपूर्णांक->mutex);
	kमुक्त(xattr_value);
	ima_मुक्त_modsig(modsig);
out:
	अगर (pathbuf)
		__putname(pathbuf);
	अगर (must_appउठाओ) अणु
		अगर (rc && (ima_appउठाओ & IMA_APPRAISE_ENFORCE))
			वापस -EACCES;
		अगर (file->f_mode & FMODE_WRITE)
			set_bit(IMA_UPDATE_XATTR, &iपूर्णांक->atomic_flags);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ima_file_mmap - based on policy, collect/store measurement.
 * @file: poपूर्णांकer to the file to be measured (May be शून्य)
 * @prot: contains the protection that will be applied by the kernel.
 *
 * Measure files being mmapped executable based on the ima_must_measure()
 * policy decision.
 *
 * On success वापस 0.  On पूर्णांकegrity appraisal error, assuming the file
 * is in policy and IMA-appraisal is in enक्रमcing mode, वापस -EACCES.
 */
पूर्णांक ima_file_mmap(काष्ठा file *file, अचिन्हित दीर्घ prot)
अणु
	u32 secid;

	अगर (file && (prot & PROT_EXEC)) अणु
		security_task_माला_लोecid_subj(current, &secid);
		वापस process_measurement(file, current_cred(), secid, शून्य,
					   0, MAY_EXEC, MMAP_CHECK);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ima_file_mprotect - based on policy, limit mprotect change
 * @prot: contains the protection that will be applied by the kernel.
 *
 * Files can be mmap'ed पढ़ो/ग_लिखो and later changed to execute to circumvent
 * IMA's mmap appraisal policy rules.  Due to locking issues (mmap semaphore
 * would be taken beक्रमe i_mutex), files can not be measured or appउठाओd at
 * this poपूर्णांक.  Eliminate this पूर्णांकegrity gap by denying the mprotect
 * PROT_EXECUTE change, अगर an mmap appउठाओ policy rule exists.
 *
 * On mprotect change success, वापस 0.  On failure, वापस -EACESS.
 */
पूर्णांक ima_file_mprotect(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ prot)
अणु
	काष्ठा ima_ढाँचा_desc *ढाँचा = शून्य;
	काष्ठा file *file = vma->vm_file;
	अक्षर filename[NAME_MAX];
	अक्षर *pathbuf = शून्य;
	स्थिर अक्षर *pathname = शून्य;
	काष्ठा inode *inode;
	पूर्णांक result = 0;
	पूर्णांक action;
	u32 secid;
	पूर्णांक pcr;

	/* Is mprotect making an mmap'ed file executable? */
	अगर (!(ima_policy_flag & IMA_APPRAISE) || !vma->vm_file ||
	    !(prot & PROT_EXEC) || (vma->vm_flags & VM_EXEC))
		वापस 0;

	security_task_माला_लोecid_subj(current, &secid);
	inode = file_inode(vma->vm_file);
	action = ima_get_action(file_mnt_user_ns(vma->vm_file), inode,
				current_cred(), secid, MAY_EXEC, MMAP_CHECK,
				&pcr, &ढाँचा, 0);

	/* Is the mmap'ed file in policy? */
	अगर (!(action & (IMA_MEASURE | IMA_APPRAISE_SUBMASK)))
		वापस 0;

	अगर (action & IMA_APPRAISE_SUBMASK)
		result = -EPERM;

	file = vma->vm_file;
	pathname = ima_d_path(&file->f_path, &pathbuf, filename);
	पूर्णांकegrity_audit_msg(AUDIT_INTEGRITY_DATA, inode, pathname,
			    "collect_data", "failed-mprotect", result, 0);
	अगर (pathbuf)
		__putname(pathbuf);

	वापस result;
पूर्ण

/**
 * ima_bprm_check - based on policy, collect/store measurement.
 * @bprm: contains the linux_binprm काष्ठाure
 *
 * The OS protects against an executable file, alपढ़ोy खोलो क्रम ग_लिखो,
 * from being executed in deny_ग_लिखो_access() and an executable file,
 * alपढ़ोy खोलो क्रम execute, from being modअगरied in get_ग_लिखो_access().
 * So we can be certain that what we verअगरy and measure here is actually
 * what is being executed.
 *
 * On success वापस 0.  On पूर्णांकegrity appraisal error, assuming the file
 * is in policy and IMA-appraisal is in enक्रमcing mode, वापस -EACCES.
 */
पूर्णांक ima_bprm_check(काष्ठा linux_binprm *bprm)
अणु
	पूर्णांक ret;
	u32 secid;

	security_task_माला_लोecid_subj(current, &secid);
	ret = process_measurement(bprm->file, current_cred(), secid, शून्य, 0,
				  MAY_EXEC, BPRM_CHECK);
	अगर (ret)
		वापस ret;

	security_cred_माला_लोecid(bprm->cred, &secid);
	वापस process_measurement(bprm->file, bprm->cred, secid, शून्य, 0,
				   MAY_EXEC, CREDS_CHECK);
पूर्ण

/**
 * ima_file_check - based on policy, collect/store measurement.
 * @file: poपूर्णांकer to the file to be measured
 * @mask: contains MAY_READ, MAY_WRITE, MAY_EXEC or MAY_APPEND
 *
 * Measure files based on the ima_must_measure() policy decision.
 *
 * On success वापस 0.  On पूर्णांकegrity appraisal error, assuming the file
 * is in policy and IMA-appraisal is in enक्रमcing mode, वापस -EACCES.
 */
पूर्णांक ima_file_check(काष्ठा file *file, पूर्णांक mask)
अणु
	u32 secid;

	security_task_माला_लोecid_subj(current, &secid);
	वापस process_measurement(file, current_cred(), secid, शून्य, 0,
				   mask & (MAY_READ | MAY_WRITE | MAY_EXEC |
					   MAY_APPEND), खाता_CHECK);
पूर्ण
EXPORT_SYMBOL_GPL(ima_file_check);

अटल पूर्णांक __ima_inode_hash(काष्ठा inode *inode, अक्षर *buf, माप_प्रकार buf_size)
अणु
	काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक;
	पूर्णांक hash_algo;

	अगर (!ima_policy_flag)
		वापस -EOPNOTSUPP;

	iपूर्णांक = पूर्णांकegrity_iपूर्णांक_find(inode);
	अगर (!iपूर्णांक)
		वापस -EOPNOTSUPP;

	mutex_lock(&iपूर्णांक->mutex);

	/*
	 * ima_file_hash can be called when ima_collect_measurement has still
	 * not been called, we might not always have a hash.
	 */
	अगर (!iपूर्णांक->ima_hash) अणु
		mutex_unlock(&iपूर्णांक->mutex);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (buf) अणु
		माप_प्रकार copied_size;

		copied_size = min_t(माप_प्रकार, iपूर्णांक->ima_hash->length, buf_size);
		स_नकल(buf, iपूर्णांक->ima_hash->digest, copied_size);
	पूर्ण
	hash_algo = iपूर्णांक->ima_hash->algo;
	mutex_unlock(&iपूर्णांक->mutex);

	वापस hash_algo;
पूर्ण

/**
 * ima_file_hash - वापस the stored measurement अगर a file has been hashed and
 * is in the iपूर्णांक cache.
 * @file: poपूर्णांकer to the file
 * @buf: buffer in which to store the hash
 * @buf_size: length of the buffer
 *
 * On success, वापस the hash algorithm (as defined in the क्रमागत hash_algo).
 * If buf is not शून्य, this function also outमाला_दो the hash पूर्णांकo buf.
 * If the hash is larger than buf_size, then only buf_size bytes will be copied.
 * It generally just makes sense to pass a buffer capable of holding the largest
 * possible hash: IMA_MAX_DIGEST_SIZE.
 * The file hash वापसed is based on the entire file, including the appended
 * signature.
 *
 * If IMA is disabled or अगर no measurement is available, वापस -EOPNOTSUPP.
 * If the parameters are incorrect, वापस -EINVAL.
 */
पूर्णांक ima_file_hash(काष्ठा file *file, अक्षर *buf, माप_प्रकार buf_size)
अणु
	अगर (!file)
		वापस -EINVAL;

	वापस __ima_inode_hash(file_inode(file), buf, buf_size);
पूर्ण
EXPORT_SYMBOL_GPL(ima_file_hash);

/**
 * ima_inode_hash - वापस the stored measurement अगर the inode has been hashed
 * and is in the iपूर्णांक cache.
 * @inode: poपूर्णांकer to the inode
 * @buf: buffer in which to store the hash
 * @buf_size: length of the buffer
 *
 * On success, वापस the hash algorithm (as defined in the क्रमागत hash_algo).
 * If buf is not शून्य, this function also outमाला_दो the hash पूर्णांकo buf.
 * If the hash is larger than buf_size, then only buf_size bytes will be copied.
 * It generally just makes sense to pass a buffer capable of holding the largest
 * possible hash: IMA_MAX_DIGEST_SIZE.
 * The hash वापसed is based on the entire contents, including the appended
 * signature.
 *
 * If IMA is disabled or अगर no measurement is available, वापस -EOPNOTSUPP.
 * If the parameters are incorrect, वापस -EINVAL.
 */
पूर्णांक ima_inode_hash(काष्ठा inode *inode, अक्षर *buf, माप_प्रकार buf_size)
अणु
	अगर (!inode)
		वापस -EINVAL;

	वापस __ima_inode_hash(inode, buf, buf_size);
पूर्ण
EXPORT_SYMBOL_GPL(ima_inode_hash);

/**
 * ima_post_create_क्षणिक_ख - mark newly created क्षणिक_ख as new
 * @mnt_userns:	user namespace of the mount the inode was found from
 * @file : newly created क्षणिक_ख
 *
 * No measuring, appraising or auditing of newly created क्षणिक_खs is needed.
 * Skip calling process_measurement(), but indicate which newly, created
 * क्षणिक_खs are in policy.
 */
व्योम ima_post_create_क्षणिक_ख(काष्ठा user_namespace *mnt_userns,
			     काष्ठा inode *inode)
अणु
	काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक;
	पूर्णांक must_appउठाओ;

	अगर (!ima_policy_flag || !S_ISREG(inode->i_mode))
		वापस;

	must_appउठाओ = ima_must_appउठाओ(mnt_userns, inode, MAY_ACCESS,
					  खाता_CHECK);
	अगर (!must_appउठाओ)
		वापस;

	/* Nothing to करो अगर we can't allocate memory */
	iपूर्णांक = पूर्णांकegrity_inode_get(inode);
	अगर (!iपूर्णांक)
		वापस;

	/* needed क्रम writing the security xattrs */
	set_bit(IMA_UPDATE_XATTR, &iपूर्णांक->atomic_flags);
	iपूर्णांक->ima_file_status = INTEGRITY_PASS;
पूर्ण

/**
 * ima_post_path_mknod - mark as a new inode
 * @mnt_userns:	user namespace of the mount the inode was found from
 * @dentry: newly created dentry
 *
 * Mark files created via the mknodat syscall as new, so that the
 * file data can be written later.
 */
व्योम ima_post_path_mknod(काष्ठा user_namespace *mnt_userns,
			 काष्ठा dentry *dentry)
अणु
	काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक;
	काष्ठा inode *inode = dentry->d_inode;
	पूर्णांक must_appउठाओ;

	अगर (!ima_policy_flag || !S_ISREG(inode->i_mode))
		वापस;

	must_appउठाओ = ima_must_appउठाओ(mnt_userns, inode, MAY_ACCESS,
					  खाता_CHECK);
	अगर (!must_appउठाओ)
		वापस;

	/* Nothing to करो अगर we can't allocate memory */
	iपूर्णांक = पूर्णांकegrity_inode_get(inode);
	अगर (!iपूर्णांक)
		वापस;

	/* needed क्रम re-खोलोing empty files */
	iपूर्णांक->flags |= IMA_NEW_खाता;
पूर्ण

/**
 * ima_पढ़ो_file - pre-measure/appउठाओ hook decision based on policy
 * @file: poपूर्णांकer to the file to be measured/appउठाओd/audit
 * @पढ़ो_id: caller identअगरier
 * @contents: whether a subsequent call will be made to ima_post_पढ़ो_file()
 *
 * Permit पढ़ोing a file based on policy. The policy rules are written
 * in terms of the policy identअगरier.  Appraising the पूर्णांकegrity of
 * a file requires a file descriptor.
 *
 * For permission वापस 0, otherwise वापस -EACCES.
 */
पूर्णांक ima_पढ़ो_file(काष्ठा file *file, क्रमागत kernel_पढ़ो_file_id पढ़ो_id,
		  bool contents)
अणु
	क्रमागत ima_hooks func;
	u32 secid;

	/*
	 * Do devices using pre-allocated memory run the risk of the
	 * firmware being accessible to the device prior to the completion
	 * of IMA's signature verअगरication any more than when using two
	 * buffers? It may be desirable to include the buffer address
	 * in this API and walk all the dma_map_single() mappings to check.
	 */

	/*
	 * There will be a call made to ima_post_पढ़ो_file() with
	 * a filled buffer, so we करोn't need to perक्रमm an extra
	 * पढ़ो early here.
	 */
	अगर (contents)
		वापस 0;

	/* Read entire file क्रम all partial पढ़ोs. */
	func = पढ़ो_idmap[पढ़ो_id] ?: खाता_CHECK;
	security_task_माला_लोecid_subj(current, &secid);
	वापस process_measurement(file, current_cred(), secid, शून्य,
				   0, MAY_READ, func);
पूर्ण

स्थिर पूर्णांक पढ़ो_idmap[READING_MAX_ID] = अणु
	[READING_FIRMWARE] = FIRMWARE_CHECK,
	[READING_MODULE] = MODULE_CHECK,
	[READING_KEXEC_IMAGE] = KEXEC_KERNEL_CHECK,
	[READING_KEXEC_INITRAMFS] = KEXEC_INITRAMFS_CHECK,
	[READING_POLICY] = POLICY_CHECK
पूर्ण;

/**
 * ima_post_पढ़ो_file - in memory collect/appउठाओ/audit measurement
 * @file: poपूर्णांकer to the file to be measured/appउठाओd/audit
 * @buf: poपूर्णांकer to in memory file contents
 * @size: size of in memory file contents
 * @पढ़ो_id: caller identअगरier
 *
 * Measure/appउठाओ/audit in memory file based on policy.  Policy rules
 * are written in terms of a policy identअगरier.
 *
 * On success वापस 0.  On पूर्णांकegrity appraisal error, assuming the file
 * is in policy and IMA-appraisal is in enक्रमcing mode, वापस -EACCES.
 */
पूर्णांक ima_post_पढ़ो_file(काष्ठा file *file, व्योम *buf, loff_t size,
		       क्रमागत kernel_पढ़ो_file_id पढ़ो_id)
अणु
	क्रमागत ima_hooks func;
	u32 secid;

	/* permit चिन्हित certs */
	अगर (!file && पढ़ो_id == READING_X509_CERTIFICATE)
		वापस 0;

	अगर (!file || !buf || size == 0) अणु /* should never happen */
		अगर (ima_appउठाओ & IMA_APPRAISE_ENFORCE)
			वापस -EACCES;
		वापस 0;
	पूर्ण

	func = पढ़ो_idmap[पढ़ो_id] ?: खाता_CHECK;
	security_task_माला_लोecid_subj(current, &secid);
	वापस process_measurement(file, current_cred(), secid, buf, size,
				   MAY_READ, func);
पूर्ण

/**
 * ima_load_data - appउठाओ decision based on policy
 * @id: kernel load data caller identअगरier
 * @contents: whether the full contents will be available in a later
 *	      call to ima_post_load_data().
 *
 * Callers of this LSM hook can not measure, appउठाओ, or audit the
 * data provided by userspace.  Enक्रमce policy rules requring a file
 * signature (eg. kexec'ed kernel image).
 *
 * For permission वापस 0, otherwise वापस -EACCES.
 */
पूर्णांक ima_load_data(क्रमागत kernel_load_data_id id, bool contents)
अणु
	bool ima_enक्रमce, sig_enक्रमce;

	ima_enक्रमce =
		(ima_appउठाओ & IMA_APPRAISE_ENFORCE) == IMA_APPRAISE_ENFORCE;

	चयन (id) अणु
	हाल LOADING_KEXEC_IMAGE:
		अगर (IS_ENABLED(CONFIG_KEXEC_SIG)
		    && arch_ima_get_secureboot()) अणु
			pr_err("impossible to appraise a kernel image without a file descriptor; try using kexec_file_load syscall.\n");
			वापस -EACCES;
		पूर्ण

		अगर (ima_enक्रमce && (ima_appउठाओ & IMA_APPRAISE_KEXEC)) अणु
			pr_err("impossible to appraise a kernel image without a file descriptor; try using kexec_file_load syscall.\n");
			वापस -EACCES;	/* INTEGRITY_UNKNOWN */
		पूर्ण
		अवरोध;
	हाल LOADING_FIRMWARE:
		अगर (ima_enक्रमce && (ima_appउठाओ & IMA_APPRAISE_FIRMWARE) && !contents) अणु
			pr_err("Prevent firmware sysfs fallback loading.\n");
			वापस -EACCES;	/* INTEGRITY_UNKNOWN */
		पूर्ण
		अवरोध;
	हाल LOADING_MODULE:
		sig_enक्रमce = is_module_sig_enक्रमced();

		अगर (ima_enक्रमce && (!sig_enक्रमce
				    && (ima_appउठाओ & IMA_APPRAISE_MODULES))) अणु
			pr_err("impossible to appraise a module without a file descriptor. sig_enforce kernel parameter might help\n");
			वापस -EACCES;	/* INTEGRITY_UNKNOWN */
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ima_post_load_data - appउठाओ decision based on policy
 * @buf: poपूर्णांकer to in memory file contents
 * @size: size of in memory file contents
 * @id: kernel load data caller identअगरier
 * @description: @id-specअगरic description of contents
 *
 * Measure/appउठाओ/audit in memory buffer based on policy.  Policy rules
 * are written in terms of a policy identअगरier.
 *
 * On success वापस 0.  On पूर्णांकegrity appraisal error, assuming the file
 * is in policy and IMA-appraisal is in enक्रमcing mode, वापस -EACCES.
 */
पूर्णांक ima_post_load_data(अक्षर *buf, loff_t size,
		       क्रमागत kernel_load_data_id load_id,
		       अक्षर *description)
अणु
	अगर (load_id == LOADING_FIRMWARE) अणु
		अगर ((ima_appउठाओ & IMA_APPRAISE_FIRMWARE) &&
		    (ima_appउठाओ & IMA_APPRAISE_ENFORCE)) अणु
			pr_err("Prevent firmware loading_store.\n");
			वापस -EACCES; /* INTEGRITY_UNKNOWN */
		पूर्ण
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * process_buffer_measurement - Measure the buffer or the buffer data hash
 * @mnt_userns:	user namespace of the mount the inode was found from
 * @inode: inode associated with the object being measured (शून्य क्रम KEY_CHECK)
 * @buf: poपूर्णांकer to the buffer that needs to be added to the log.
 * @size: size of buffer(in bytes).
 * @eventname: event name to be used क्रम the buffer entry.
 * @func: IMA hook
 * @pcr: pcr to extend the measurement
 * @func_data: func specअगरic data, may be शून्य
 * @buf_hash: measure buffer data hash
 *
 * Based on policy, either the buffer data or buffer data hash is measured
 */
व्योम process_buffer_measurement(काष्ठा user_namespace *mnt_userns,
				काष्ठा inode *inode, स्थिर व्योम *buf, पूर्णांक size,
				स्थिर अक्षर *eventname, क्रमागत ima_hooks func,
				पूर्णांक pcr, स्थिर अक्षर *func_data,
				bool buf_hash)
अणु
	पूर्णांक ret = 0;
	स्थिर अक्षर *audit_cause = "ENOMEM";
	काष्ठा ima_ढाँचा_entry *entry = शून्य;
	काष्ठा पूर्णांकegrity_iपूर्णांक_cache iपूर्णांक = अणुपूर्ण;
	काष्ठा ima_event_data event_data = अणु.iपूर्णांक = &iपूर्णांक,
					    .filename = eventname,
					    .buf = buf,
					    .buf_len = sizeपूर्ण;
	काष्ठा ima_ढाँचा_desc *ढाँचा;
	काष्ठा अणु
		काष्ठा ima_digest_data hdr;
		अक्षर digest[IMA_MAX_DIGEST_SIZE];
	पूर्ण hash = अणुपूर्ण;
	अक्षर digest_hash[IMA_MAX_DIGEST_SIZE];
	पूर्णांक digest_hash_len = hash_digest_size[ima_hash_algo];
	पूर्णांक violation = 0;
	पूर्णांक action = 0;
	u32 secid;

	अगर (!ima_policy_flag)
		वापस;

	ढाँचा = ima_ढाँचा_desc_buf();
	अगर (!ढाँचा) अणु
		ret = -EINVAL;
		audit_cause = "ima_template_desc_buf";
		जाओ out;
	पूर्ण

	/*
	 * Both LSM hooks and auxilary based buffer measurements are
	 * based on policy.  To aव्योम code duplication, dअगरferentiate
	 * between the LSM hooks and auxilary buffer measurements,
	 * retrieving the policy rule inक्रमmation only क्रम the LSM hook
	 * buffer measurements.
	 */
	अगर (func) अणु
		security_task_माला_लोecid_subj(current, &secid);
		action = ima_get_action(mnt_userns, inode, current_cred(),
					secid, 0, func, &pcr, &ढाँचा,
					func_data);
		अगर (!(action & IMA_MEASURE))
			वापस;
	पूर्ण

	अगर (!pcr)
		pcr = CONFIG_IMA_MEASURE_PCR_IDX;

	iपूर्णांक.ima_hash = &hash.hdr;
	iपूर्णांक.ima_hash->algo = ima_hash_algo;
	iपूर्णांक.ima_hash->length = hash_digest_size[ima_hash_algo];

	ret = ima_calc_buffer_hash(buf, size, iपूर्णांक.ima_hash);
	अगर (ret < 0) अणु
		audit_cause = "hashing_error";
		जाओ out;
	पूर्ण

	अगर (buf_hash) अणु
		स_नकल(digest_hash, hash.hdr.digest, digest_hash_len);

		ret = ima_calc_buffer_hash(digest_hash, digest_hash_len,
					   iपूर्णांक.ima_hash);
		अगर (ret < 0) अणु
			audit_cause = "hashing_error";
			जाओ out;
		पूर्ण

		event_data.buf = digest_hash;
		event_data.buf_len = digest_hash_len;
	पूर्ण

	ret = ima_alloc_init_ढाँचा(&event_data, &entry, ढाँचा);
	अगर (ret < 0) अणु
		audit_cause = "alloc_entry";
		जाओ out;
	पूर्ण

	ret = ima_store_ढाँचा(entry, violation, शून्य, event_data.buf, pcr);
	अगर (ret < 0) अणु
		audit_cause = "store_entry";
		ima_मुक्त_ढाँचा_entry(entry);
	पूर्ण

out:
	अगर (ret < 0)
		पूर्णांकegrity_audit_message(AUDIT_INTEGRITY_PCR, शून्य, eventname,
					func_measure_str(func),
					audit_cause, ret, 0, ret);

	वापस;
पूर्ण

/**
 * ima_kexec_cmdline - measure kexec cmdline boot args
 * @kernel_fd: file descriptor of the kexec kernel being loaded
 * @buf: poपूर्णांकer to buffer
 * @size: size of buffer
 *
 * Buffers can only be measured, not appउठाओd.
 */
व्योम ima_kexec_cmdline(पूर्णांक kernel_fd, स्थिर व्योम *buf, पूर्णांक size)
अणु
	काष्ठा fd f;

	अगर (!buf || !size)
		वापस;

	f = fdget(kernel_fd);
	अगर (!f.file)
		वापस;

	process_buffer_measurement(file_mnt_user_ns(f.file), file_inode(f.file),
				   buf, size, "kexec-cmdline", KEXEC_CMDLINE, 0,
				   शून्य, false);
	fdput(f);
पूर्ण

/**
 * ima_measure_critical_data - measure kernel पूर्णांकegrity critical data
 * @event_label: unique event label क्रम grouping and limiting critical data
 * @event_name: event name क्रम the record in the IMA measurement list
 * @buf: poपूर्णांकer to buffer data
 * @buf_len: length of buffer data (in bytes)
 * @hash: measure buffer data hash
 *
 * Measure data critical to the पूर्णांकegrity of the kernel पूर्णांकo the IMA log
 * and extend the pcr.  Examples of critical data could be various data
 * काष्ठाures, policies, and states stored in kernel memory that can
 * impact the पूर्णांकegrity of the प्रणाली.
 */
व्योम ima_measure_critical_data(स्थिर अक्षर *event_label,
			       स्थिर अक्षर *event_name,
			       स्थिर व्योम *buf, माप_प्रकार buf_len,
			       bool hash)
अणु
	अगर (!event_name || !event_label || !buf || !buf_len)
		वापस;

	process_buffer_measurement(&init_user_ns, शून्य, buf, buf_len, event_name,
				   CRITICAL_DATA, 0, event_label,
				   hash);
पूर्ण

अटल पूर्णांक __init init_ima(व्योम)
अणु
	पूर्णांक error;

	ima_appउठाओ_parse_cmdline();
	ima_init_ढाँचा_list();
	hash_setup(CONFIG_IMA_DEFAULT_HASH);
	error = ima_init();

	अगर (error && म_भेद(hash_algo_name[ima_hash_algo],
			    CONFIG_IMA_DEFAULT_HASH) != 0) अणु
		pr_info("Allocating %s failed, going to use default hash algorithm %s\n",
			hash_algo_name[ima_hash_algo], CONFIG_IMA_DEFAULT_HASH);
		hash_setup_करोne = 0;
		hash_setup(CONFIG_IMA_DEFAULT_HASH);
		error = ima_init();
	पूर्ण

	अगर (error)
		वापस error;

	error = रेजिस्टर_blocking_lsm_notअगरier(&ima_lsm_policy_notअगरier);
	अगर (error)
		pr_warn("Couldn't register LSM notifier, error %d\n", error);

	अगर (!error)
		ima_update_policy_flag();

	वापस error;
पूर्ण

late_initcall(init_ima);	/* Start IMA after the TPM is available */
