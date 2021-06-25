<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008 IBM Corporation
 *
 * Author: Mimi Zohar <zohar@us.ibm.com>
 *
 * File: ima_api.c
 *	Implements must_appउठाओ_or_measure, collect_measurement,
 *	appउठाओ_measurement, store_measurement and store_ढाँचा.
 */
#समावेश <linux/slab.h>
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/xattr.h>
#समावेश <linux/evm.h>
#समावेश <linux/iversion.h>

#समावेश "ima.h"

/*
 * ima_मुक्त_ढाँचा_entry - मुक्त an existing ढाँचा entry
 */
व्योम ima_मुक्त_ढाँचा_entry(काष्ठा ima_ढाँचा_entry *entry)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < entry->ढाँचा_desc->num_fields; i++)
		kमुक्त(entry->ढाँचा_data[i].data);

	kमुक्त(entry->digests);
	kमुक्त(entry);
पूर्ण

/*
 * ima_alloc_init_ढाँचा - create and initialize a new ढाँचा entry
 */
पूर्णांक ima_alloc_init_ढाँचा(काष्ठा ima_event_data *event_data,
			    काष्ठा ima_ढाँचा_entry **entry,
			    काष्ठा ima_ढाँचा_desc *desc)
अणु
	काष्ठा ima_ढाँचा_desc *ढाँचा_desc;
	काष्ठा tpm_digest *digests;
	पूर्णांक i, result = 0;

	अगर (desc)
		ढाँचा_desc = desc;
	अन्यथा
		ढाँचा_desc = ima_ढाँचा_desc_current();

	*entry = kzalloc(काष्ठा_size(*entry, ढाँचा_data,
				     ढाँचा_desc->num_fields), GFP_NOFS);
	अगर (!*entry)
		वापस -ENOMEM;

	digests = kसुस्मृति(NR_BANKS(ima_tpm_chip) + ima_extra_slots,
			  माप(*digests), GFP_NOFS);
	अगर (!digests) अणु
		kमुक्त(*entry);
		*entry = शून्य;
		वापस -ENOMEM;
	पूर्ण

	(*entry)->digests = digests;
	(*entry)->ढाँचा_desc = ढाँचा_desc;
	क्रम (i = 0; i < ढाँचा_desc->num_fields; i++) अणु
		स्थिर काष्ठा ima_ढाँचा_field *field =
			ढाँचा_desc->fields[i];
		u32 len;

		result = field->field_init(event_data,
					   &((*entry)->ढाँचा_data[i]));
		अगर (result != 0)
			जाओ out;

		len = (*entry)->ढाँचा_data[i].len;
		(*entry)->ढाँचा_data_len += माप(len);
		(*entry)->ढाँचा_data_len += len;
	पूर्ण
	वापस 0;
out:
	ima_मुक्त_ढाँचा_entry(*entry);
	*entry = शून्य;
	वापस result;
पूर्ण

/*
 * ima_store_ढाँचा - store ima ढाँचा measurements
 *
 * Calculate the hash of a ढाँचा entry, add the ढाँचा entry
 * to an ordered list of measurement entries मुख्यtained inside the kernel,
 * and also update the aggregate पूर्णांकegrity value (मुख्यtained inside the
 * configured TPM PCR) over the hashes of the current list of measurement
 * entries.
 *
 * Applications retrieve the current kernel-held measurement list through
 * the securityfs entries in /sys/kernel/security/ima. The चिन्हित aggregate
 * TPM PCR (called quote) can be retrieved using a TPM user space library
 * and is used to validate the measurement list.
 *
 * Returns 0 on success, error code otherwise
 */
पूर्णांक ima_store_ढाँचा(काष्ठा ima_ढाँचा_entry *entry,
		       पूर्णांक violation, काष्ठा inode *inode,
		       स्थिर अचिन्हित अक्षर *filename, पूर्णांक pcr)
अणु
	अटल स्थिर अक्षर op[] = "add_template_measure";
	अटल स्थिर अक्षर audit_cause[] = "hashing_error";
	अक्षर *ढाँचा_name = entry->ढाँचा_desc->name;
	पूर्णांक result;

	अगर (!violation) अणु
		result = ima_calc_field_array_hash(&entry->ढाँचा_data[0],
						   entry);
		अगर (result < 0) अणु
			पूर्णांकegrity_audit_msg(AUDIT_INTEGRITY_PCR, inode,
					    ढाँचा_name, op,
					    audit_cause, result, 0);
			वापस result;
		पूर्ण
	पूर्ण
	entry->pcr = pcr;
	result = ima_add_ढाँचा_entry(entry, violation, op, inode, filename);
	वापस result;
पूर्ण

/*
 * ima_add_violation - add violation to measurement list.
 *
 * Violations are flagged in the measurement list with zero hash values.
 * By extending the PCR with 0xFF's instead of with zeroes, the PCR
 * value is invalidated.
 */
व्योम ima_add_violation(काष्ठा file *file, स्थिर अचिन्हित अक्षर *filename,
		       काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक,
		       स्थिर अक्षर *op, स्थिर अक्षर *cause)
अणु
	काष्ठा ima_ढाँचा_entry *entry;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा ima_event_data event_data = अणु .iपूर्णांक = iपूर्णांक,
					     .file = file,
					     .filename = filename,
					     .violation = cause पूर्ण;
	पूर्णांक violation = 1;
	पूर्णांक result;

	/* can overflow, only indicator */
	atomic_दीर्घ_inc(&ima_htable.violations);

	result = ima_alloc_init_ढाँचा(&event_data, &entry, शून्य);
	अगर (result < 0) अणु
		result = -ENOMEM;
		जाओ err_out;
	पूर्ण
	result = ima_store_ढाँचा(entry, violation, inode,
				    filename, CONFIG_IMA_MEASURE_PCR_IDX);
	अगर (result < 0)
		ima_मुक्त_ढाँचा_entry(entry);
err_out:
	पूर्णांकegrity_audit_msg(AUDIT_INTEGRITY_PCR, inode, filename,
			    op, cause, result, 0);
पूर्ण

/**
 * ima_get_action - appउठाओ & measure decision based on policy.
 * @mnt_userns:	user namespace of the mount the inode was found from
 * @inode: poपूर्णांकer to the inode associated with the object being validated
 * @cred: poपूर्णांकer to credentials काष्ठाure to validate
 * @secid: secid of the task being validated
 * @mask: contains the permission mask (MAY_READ, MAY_WRITE, MAY_EXEC,
 *        MAY_APPEND)
 * @func: caller identअगरier
 * @pcr: poपूर्णांकer filled in अगर matched measure policy sets pcr=
 * @ढाँचा_desc: poपूर्णांकer filled in अगर matched measure policy sets ढाँचा=
 * @func_data: func specअगरic data, may be शून्य
 *
 * The policy is defined in terms of keypairs:
 *		subj=, obj=, type=, func=, mask=, fsmagic=
 *	subj,obj, and type: are LSM specअगरic.
 *	func: खाता_CHECK | BPRM_CHECK | CREDS_CHECK | MMAP_CHECK | MODULE_CHECK
 *	| KEXEC_CMDLINE | KEY_CHECK | CRITICAL_DATA
 *	mask: contains the permission mask
 *	fsmagic: hex value
 *
 * Returns IMA_MEASURE, IMA_APPRAISE mask.
 *
 */
पूर्णांक ima_get_action(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		   स्थिर काष्ठा cred *cred, u32 secid, पूर्णांक mask,
		   क्रमागत ima_hooks func, पूर्णांक *pcr,
		   काष्ठा ima_ढाँचा_desc **ढाँचा_desc,
		   स्थिर अक्षर *func_data)
अणु
	पूर्णांक flags = IMA_MEASURE | IMA_AUDIT | IMA_APPRAISE | IMA_HASH;

	flags &= ima_policy_flag;

	वापस ima_match_policy(mnt_userns, inode, cred, secid, func, mask,
				flags, pcr, ढाँचा_desc, func_data);
पूर्ण

/*
 * ima_collect_measurement - collect file measurement
 *
 * Calculate the file hash, अगर it करोesn't alपढ़ोy exist,
 * storing the measurement and i_version in the iपूर्णांक.
 *
 * Must be called with iपूर्णांक->mutex held.
 *
 * Return 0 on success, error code otherwise
 */
पूर्णांक ima_collect_measurement(काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक,
			    काष्ठा file *file, व्योम *buf, loff_t size,
			    क्रमागत hash_algo algo, काष्ठा modsig *modsig)
अणु
	स्थिर अक्षर *audit_cause = "failed";
	काष्ठा inode *inode = file_inode(file);
	स्थिर अक्षर *filename = file->f_path.dentry->d_name.name;
	पूर्णांक result = 0;
	पूर्णांक length;
	व्योम *पंचांगpbuf;
	u64 i_version;
	काष्ठा अणु
		काष्ठा ima_digest_data hdr;
		अक्षर digest[IMA_MAX_DIGEST_SIZE];
	पूर्ण hash;

	/*
	 * Always collect the modsig, because IMA might have alपढ़ोy collected
	 * the file digest without collecting the modsig in a previous
	 * measurement rule.
	 */
	अगर (modsig)
		ima_collect_modsig(modsig, buf, size);

	अगर (iपूर्णांक->flags & IMA_COLLECTED)
		जाओ out;

	/*
	 * Dectecting file change is based on i_version. On fileप्रणालीs
	 * which करो not support i_version, support is limited to an initial
	 * measurement/appraisal/audit.
	 */
	i_version = inode_query_iversion(inode);
	hash.hdr.algo = algo;

	/* Initialize hash digest to 0's in हाल of failure */
	स_रखो(&hash.digest, 0, माप(hash.digest));

	अगर (buf)
		result = ima_calc_buffer_hash(buf, size, &hash.hdr);
	अन्यथा
		result = ima_calc_file_hash(file, &hash.hdr);

	अगर (result && result != -EBADF && result != -EINVAL)
		जाओ out;

	length = माप(hash.hdr) + hash.hdr.length;
	पंचांगpbuf = kपुनः_स्मृति(iपूर्णांक->ima_hash, length, GFP_NOFS);
	अगर (!पंचांगpbuf) अणु
		result = -ENOMEM;
		जाओ out;
	पूर्ण

	iपूर्णांक->ima_hash = पंचांगpbuf;
	स_नकल(iपूर्णांक->ima_hash, &hash, length);
	iपूर्णांक->version = i_version;

	/* Possibly temporary failure due to type of पढ़ो (eg. O_सूचीECT) */
	अगर (!result)
		iपूर्णांक->flags |= IMA_COLLECTED;
out:
	अगर (result) अणु
		अगर (file->f_flags & O_सूचीECT)
			audit_cause = "failed(directio)";

		पूर्णांकegrity_audit_msg(AUDIT_INTEGRITY_DATA, inode,
				    filename, "collect_data", audit_cause,
				    result, 0);
	पूर्ण
	वापस result;
पूर्ण

/*
 * ima_store_measurement - store file measurement
 *
 * Create an "ima" ढाँचा and then store the ढाँचा by calling
 * ima_store_ढाँचा.
 *
 * We only get here अगर the inode has not alपढ़ोy been measured,
 * but the measurement could alपढ़ोy exist:
 *	- multiple copies of the same file on either the same or
 *	  dअगरferent fileप्रणालीs.
 *	- the inode was previously flushed as well as the iपूर्णांक info,
 *	  containing the hashing info.
 *
 * Must be called with iपूर्णांक->mutex held.
 */
व्योम ima_store_measurement(काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक,
			   काष्ठा file *file, स्थिर अचिन्हित अक्षर *filename,
			   काष्ठा evm_ima_xattr_data *xattr_value,
			   पूर्णांक xattr_len, स्थिर काष्ठा modsig *modsig, पूर्णांक pcr,
			   काष्ठा ima_ढाँचा_desc *ढाँचा_desc)
अणु
	अटल स्थिर अक्षर op[] = "add_template_measure";
	अटल स्थिर अक्षर audit_cause[] = "ENOMEM";
	पूर्णांक result = -ENOMEM;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा ima_ढाँचा_entry *entry;
	काष्ठा ima_event_data event_data = अणु .iपूर्णांक = iपूर्णांक,
					     .file = file,
					     .filename = filename,
					     .xattr_value = xattr_value,
					     .xattr_len = xattr_len,
					     .modsig = modsig पूर्ण;
	पूर्णांक violation = 0;

	/*
	 * We still need to store the measurement in the हाल of MODSIG because
	 * we only have its contents to put in the list at the समय of
	 * appraisal, but a file measurement from earlier might alपढ़ोy exist in
	 * the measurement list.
	 */
	अगर (iपूर्णांक->measured_pcrs & (0x1 << pcr) && !modsig)
		वापस;

	result = ima_alloc_init_ढाँचा(&event_data, &entry, ढाँचा_desc);
	अगर (result < 0) अणु
		पूर्णांकegrity_audit_msg(AUDIT_INTEGRITY_PCR, inode, filename,
				    op, audit_cause, result, 0);
		वापस;
	पूर्ण

	result = ima_store_ढाँचा(entry, violation, inode, filename, pcr);
	अगर ((!result || result == -EEXIST) && !(file->f_flags & O_सूचीECT)) अणु
		iपूर्णांक->flags |= IMA_MEASURED;
		iपूर्णांक->measured_pcrs |= (0x1 << pcr);
	पूर्ण
	अगर (result < 0)
		ima_मुक्त_ढाँचा_entry(entry);
पूर्ण

व्योम ima_audit_measurement(काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक,
			   स्थिर अचिन्हित अक्षर *filename)
अणु
	काष्ठा audit_buffer *ab;
	अक्षर *hash;
	स्थिर अक्षर *algo_name = hash_algo_name[iपूर्णांक->ima_hash->algo];
	पूर्णांक i;

	अगर (iपूर्णांक->flags & IMA_AUDITED)
		वापस;

	hash = kzalloc((iपूर्णांक->ima_hash->length * 2) + 1, GFP_KERNEL);
	अगर (!hash)
		वापस;

	क्रम (i = 0; i < iपूर्णांक->ima_hash->length; i++)
		hex_byte_pack(hash + (i * 2), iपूर्णांक->ima_hash->digest[i]);
	hash[i * 2] = '\0';

	ab = audit_log_start(audit_context(), GFP_KERNEL,
			     AUDIT_INTEGRITY_RULE);
	अगर (!ab)
		जाओ out;

	audit_log_क्रमmat(ab, "file=");
	audit_log_untrustedstring(ab, filename);
	audit_log_क्रमmat(ab, " hash=\"%s:%s\"", algo_name, hash);

	audit_log_task_info(ab);
	audit_log_end(ab);

	iपूर्णांक->flags |= IMA_AUDITED;
out:
	kमुक्त(hash);
	वापस;
पूर्ण

/*
 * ima_d_path - वापस a poपूर्णांकer to the full pathname
 *
 * Attempt to वापस a poपूर्णांकer to the full pathname क्रम use in the
 * IMA measurement list, IMA audit records, and auditing logs.
 *
 * On failure, वापस a poपूर्णांकer to a copy of the filename, not dname.
 * Returning a poपूर्णांकer to dname, could result in using the poपूर्णांकer
 * after the memory has been मुक्तd.
 */
स्थिर अक्षर *ima_d_path(स्थिर काष्ठा path *path, अक्षर **pathbuf, अक्षर *namebuf)
अणु
	अक्षर *pathname = शून्य;

	*pathbuf = __getname();
	अगर (*pathbuf) अणु
		pathname = d_असलolute_path(path, *pathbuf, PATH_MAX);
		अगर (IS_ERR(pathname)) अणु
			__putname(*pathbuf);
			*pathbuf = शून्य;
			pathname = शून्य;
		पूर्ण
	पूर्ण

	अगर (!pathname) अणु
		strlcpy(namebuf, path->dentry->d_name.name, NAME_MAX);
		pathname = namebuf;
	पूर्ण

	वापस pathname;
पूर्ण
