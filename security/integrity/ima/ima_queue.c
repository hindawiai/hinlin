<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2005,2006,2007,2008 IBM Corporation
 *
 * Authors:
 * Serge Hallyn <serue@us.ibm.com>
 * Reiner Sailer <sailer@watson.ibm.com>
 * Mimi Zohar <zohar@us.ibm.com>
 *
 * File: ima_queue.c
 *       Implements queues that store ढाँचा measurements and
 *       मुख्यtains aggregate over the stored measurements
 *       in the pre-configured TPM PCR (अगर available).
 *       The measurement list is append-only. No entry is
 *       ever हटाओd or changed during the boot-cycle.
 */

#समावेश <linux/rculist.h>
#समावेश <linux/slab.h>
#समावेश "ima.h"

#घोषणा AUDIT_CAUSE_LEN_MAX 32

/* pre-allocated array of tpm_digest काष्ठाures to extend a PCR */
अटल काष्ठा tpm_digest *digests;

LIST_HEAD(ima_measurements);	/* list of all measurements */
#अगर_घोषित CONFIG_IMA_KEXEC
अटल अचिन्हित दीर्घ binary_runसमय_size;
#अन्यथा
अटल अचिन्हित दीर्घ binary_runसमय_size = अच_दीर्घ_उच्च;
#पूर्ण_अगर

/* key: inode (beक्रमe secure-hashing a file) */
काष्ठा ima_h_table ima_htable = अणु
	.len = ATOMIC_LONG_INIT(0),
	.violations = ATOMIC_LONG_INIT(0),
	.queue[0 ... IMA_MEASURE_HTABLE_SIZE - 1] = HLIST_HEAD_INIT
पूर्ण;

/* mutex protects atomicity of extending measurement list
 * and extending the TPM PCR aggregate. Since tpm_extend can take
 * दीर्घ (and the tpm driver uses a mutex), we can't use the spinlock.
 */
अटल DEFINE_MUTEX(ima_extend_list_mutex);

/* lookup up the digest value in the hash table, and वापस the entry */
अटल काष्ठा ima_queue_entry *ima_lookup_digest_entry(u8 *digest_value,
						       पूर्णांक pcr)
अणु
	काष्ठा ima_queue_entry *qe, *ret = शून्य;
	अचिन्हित पूर्णांक key;
	पूर्णांक rc;

	key = ima_hash_key(digest_value);
	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(qe, &ima_htable.queue[key], hnext) अणु
		rc = स_भेद(qe->entry->digests[ima_hash_algo_idx].digest,
			    digest_value, hash_digest_size[ima_hash_algo]);
		अगर ((rc == 0) && (qe->entry->pcr == pcr)) अणु
			ret = qe;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

/*
 * Calculate the memory required क्रम serializing a single
 * binary_runसमय_measurement list entry, which contains a
 * couple of variable length fields (e.g ढाँचा name and data).
 */
अटल पूर्णांक get_binary_runसमय_size(काष्ठा ima_ढाँचा_entry *entry)
अणु
	पूर्णांक size = 0;

	size += माप(u32);	/* pcr */
	size += TPM_DIGEST_SIZE;
	size += माप(पूर्णांक);	/* ढाँचा name size field */
	size += म_माप(entry->ढाँचा_desc->name);
	size += माप(entry->ढाँचा_data_len);
	size += entry->ढाँचा_data_len;
	वापस size;
पूर्ण

/* ima_add_ढाँचा_entry helper function:
 * - Add ढाँचा entry to the measurement list and hash table, क्रम
 *   all entries except those carried across kexec.
 *
 * (Called with ima_extend_list_mutex held.)
 */
अटल पूर्णांक ima_add_digest_entry(काष्ठा ima_ढाँचा_entry *entry,
				bool update_htable)
अणु
	काष्ठा ima_queue_entry *qe;
	अचिन्हित पूर्णांक key;

	qe = kदो_स्मृति(माप(*qe), GFP_KERNEL);
	अगर (qe == शून्य) अणु
		pr_err("OUT OF MEMORY ERROR creating queue entry\n");
		वापस -ENOMEM;
	पूर्ण
	qe->entry = entry;

	INIT_LIST_HEAD(&qe->later);
	list_add_tail_rcu(&qe->later, &ima_measurements);

	atomic_दीर्घ_inc(&ima_htable.len);
	अगर (update_htable) अणु
		key = ima_hash_key(entry->digests[ima_hash_algo_idx].digest);
		hlist_add_head_rcu(&qe->hnext, &ima_htable.queue[key]);
	पूर्ण

	अगर (binary_runसमय_size != अच_दीर्घ_उच्च) अणु
		पूर्णांक size;

		size = get_binary_runसमय_size(entry);
		binary_runसमय_size = (binary_runसमय_size < अच_दीर्घ_उच्च - size) ?
		     binary_runसमय_size + size : अच_दीर्घ_उच्च;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Return the amount of memory required क्रम serializing the
 * entire binary_runसमय_measurement list, including the ima_kexec_hdr
 * काष्ठाure.
 */
अचिन्हित दीर्घ ima_get_binary_runसमय_size(व्योम)
अणु
	अगर (binary_runसमय_size >= (अच_दीर्घ_उच्च - माप(काष्ठा ima_kexec_hdr)))
		वापस अच_दीर्घ_उच्च;
	अन्यथा
		वापस binary_runसमय_size + माप(काष्ठा ima_kexec_hdr);
पूर्ण

अटल पूर्णांक ima_pcr_extend(काष्ठा tpm_digest *digests_arg, पूर्णांक pcr)
अणु
	पूर्णांक result = 0;

	अगर (!ima_tpm_chip)
		वापस result;

	result = tpm_pcr_extend(ima_tpm_chip, pcr, digests_arg);
	अगर (result != 0)
		pr_err("Error Communicating to TPM chip, result: %d\n", result);
	वापस result;
पूर्ण

/*
 * Add ढाँचा entry to the measurement list and hash table, and
 * extend the pcr.
 *
 * On प्रणालीs which support carrying the IMA measurement list across
 * kexec, मुख्यtain the total memory size required क्रम serializing the
 * binary_runसमय_measurements.
 */
पूर्णांक ima_add_ढाँचा_entry(काष्ठा ima_ढाँचा_entry *entry, पूर्णांक violation,
			   स्थिर अक्षर *op, काष्ठा inode *inode,
			   स्थिर अचिन्हित अक्षर *filename)
अणु
	u8 *digest = entry->digests[ima_hash_algo_idx].digest;
	काष्ठा tpm_digest *digests_arg = entry->digests;
	स्थिर अक्षर *audit_cause = "hash_added";
	अक्षर tpm_audit_cause[AUDIT_CAUSE_LEN_MAX];
	पूर्णांक audit_info = 1;
	पूर्णांक result = 0, tpmresult = 0;

	mutex_lock(&ima_extend_list_mutex);
	अगर (!violation) अणु
		अगर (ima_lookup_digest_entry(digest, entry->pcr)) अणु
			audit_cause = "hash_exists";
			result = -EEXIST;
			जाओ out;
		पूर्ण
	पूर्ण

	result = ima_add_digest_entry(entry, 1);
	अगर (result < 0) अणु
		audit_cause = "ENOMEM";
		audit_info = 0;
		जाओ out;
	पूर्ण

	अगर (violation)		/* invalidate pcr */
		digests_arg = digests;

	tpmresult = ima_pcr_extend(digests_arg, entry->pcr);
	अगर (tpmresult != 0) अणु
		snम_लिखो(tpm_audit_cause, AUDIT_CAUSE_LEN_MAX, "TPM_error(%d)",
			 tpmresult);
		audit_cause = tpm_audit_cause;
		audit_info = 0;
	पूर्ण
out:
	mutex_unlock(&ima_extend_list_mutex);
	पूर्णांकegrity_audit_msg(AUDIT_INTEGRITY_PCR, inode, filename,
			    op, audit_cause, result, audit_info);
	वापस result;
पूर्ण

पूर्णांक ima_restore_measurement_entry(काष्ठा ima_ढाँचा_entry *entry)
अणु
	पूर्णांक result = 0;

	mutex_lock(&ima_extend_list_mutex);
	result = ima_add_digest_entry(entry, 0);
	mutex_unlock(&ima_extend_list_mutex);
	वापस result;
पूर्ण

पूर्णांक __init ima_init_digests(व्योम)
अणु
	u16 digest_size;
	u16 crypto_id;
	पूर्णांक i;

	अगर (!ima_tpm_chip)
		वापस 0;

	digests = kसुस्मृति(ima_tpm_chip->nr_allocated_banks, माप(*digests),
			  GFP_NOFS);
	अगर (!digests)
		वापस -ENOMEM;

	क्रम (i = 0; i < ima_tpm_chip->nr_allocated_banks; i++) अणु
		digests[i].alg_id = ima_tpm_chip->allocated_banks[i].alg_id;
		digest_size = ima_tpm_chip->allocated_banks[i].digest_size;
		crypto_id = ima_tpm_chip->allocated_banks[i].crypto_id;

		/* क्रम unmapped TPM algorithms digest is still a padded SHA1 */
		अगर (crypto_id == HASH_ALGO__LAST)
			digest_size = SHA1_DIGEST_SIZE;

		स_रखो(digests[i].digest, 0xff, digest_size);
	पूर्ण

	वापस 0;
पूर्ण
