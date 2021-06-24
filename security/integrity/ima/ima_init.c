<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2005,2006,2007,2008 IBM Corporation
 *
 * Authors:
 * Reiner Sailer      <sailer@watson.ibm.com>
 * Leendert van Doorn <leendert@watson.ibm.com>
 * Mimi Zohar         <zohar@us.ibm.com>
 *
 * File: ima_init.c
 *             initialization and cleanup functions
 */

#समावेश <linux/init.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/ima.h>
#समावेश <generated/utsrelease.h>

#समावेश "ima.h"

/* name क्रम boot aggregate entry */
स्थिर अक्षर boot_aggregate_name[] = "boot_aggregate";
काष्ठा tpm_chip *ima_tpm_chip;

/* Add the boot aggregate to the IMA measurement list and extend
 * the PCR रेजिस्टर.
 *
 * Calculate the boot aggregate, a hash over tpm रेजिस्टरs 0-7,
 * assuming a TPM chip exists, and zeroes अगर the TPM chip करोes not
 * exist.  Add the boot aggregate measurement to the measurement
 * list and extend the PCR रेजिस्टर.
 *
 * If a tpm chip करोes not exist, indicate the core root of trust is
 * not hardware based by invalidating the aggregate PCR value.
 * (The aggregate PCR value is invalidated by adding one value to
 * the measurement list and extending the aggregate PCR value with
 * a dअगरferent value.) Violations add a zero entry to the measurement
 * list and extend the aggregate PCR value with ff...ff's.
 */
अटल पूर्णांक __init ima_add_boot_aggregate(व्योम)
अणु
	अटल स्थिर अक्षर op[] = "add_boot_aggregate";
	स्थिर अक्षर *audit_cause = "ENOMEM";
	काष्ठा ima_ढाँचा_entry *entry;
	काष्ठा पूर्णांकegrity_iपूर्णांक_cache पंचांगp_iपूर्णांक, *iपूर्णांक = &पंचांगp_iपूर्णांक;
	काष्ठा ima_event_data event_data = अणु .iपूर्णांक = iपूर्णांक,
					     .filename = boot_aggregate_name पूर्ण;
	पूर्णांक result = -ENOMEM;
	पूर्णांक violation = 0;
	काष्ठा अणु
		काष्ठा ima_digest_data hdr;
		अक्षर digest[TPM_MAX_DIGEST_SIZE];
	पूर्ण hash;

	स_रखो(iपूर्णांक, 0, माप(*iपूर्णांक));
	स_रखो(&hash, 0, माप(hash));
	iपूर्णांक->ima_hash = &hash.hdr;
	iपूर्णांक->ima_hash->algo = ima_hash_algo;
	iपूर्णांक->ima_hash->length = hash_digest_size[ima_hash_algo];

	/*
	 * With TPM 2.0 hash agility, TPM chips could support multiple TPM
	 * PCR banks, allowing firmware to configure and enable dअगरferent
	 * banks.  The SHA1 bank is not necessarily enabled.
	 *
	 * Use the same hash algorithm क्रम पढ़ोing the TPM PCRs as क्रम
	 * calculating the boot aggregate digest.  Preference is given to
	 * the configured IMA शेष hash algorithm.  Otherwise, use the
	 * TCG required banks - SHA256 क्रम TPM 2.0, SHA1 क्रम TPM 1.2.
	 * Ultimately select SHA1 also क्रम TPM 2.0 अगर the SHA256 PCR bank
	 * is not found.
	 */
	अगर (ima_tpm_chip) अणु
		result = ima_calc_boot_aggregate(&hash.hdr);
		अगर (result < 0) अणु
			audit_cause = "hashing_error";
			जाओ err_out;
		पूर्ण
	पूर्ण

	result = ima_alloc_init_ढाँचा(&event_data, &entry, शून्य);
	अगर (result < 0) अणु
		audit_cause = "alloc_entry";
		जाओ err_out;
	पूर्ण

	result = ima_store_ढाँचा(entry, violation, शून्य,
				    boot_aggregate_name,
				    CONFIG_IMA_MEASURE_PCR_IDX);
	अगर (result < 0) अणु
		ima_मुक्त_ढाँचा_entry(entry);
		audit_cause = "store_entry";
		जाओ err_out;
	पूर्ण
	वापस 0;
err_out:
	पूर्णांकegrity_audit_msg(AUDIT_INTEGRITY_PCR, शून्य, boot_aggregate_name, op,
			    audit_cause, result, 0);
	वापस result;
पूर्ण

#अगर_घोषित CONFIG_IMA_LOAD_X509
व्योम __init ima_load_x509(व्योम)
अणु
	पूर्णांक unset_flags = ima_policy_flag & IMA_APPRAISE;

	ima_policy_flag &= ~unset_flags;
	पूर्णांकegrity_load_x509(INTEGRITY_KEYRING_IMA, CONFIG_IMA_X509_PATH);
	ima_policy_flag |= unset_flags;
पूर्ण
#पूर्ण_अगर

पूर्णांक __init ima_init(व्योम)
अणु
	पूर्णांक rc;

	ima_tpm_chip = tpm_शेष_chip();
	अगर (!ima_tpm_chip)
		pr_info("No TPM chip found, activating TPM-bypass!\n");

	rc = पूर्णांकegrity_init_keyring(INTEGRITY_KEYRING_IMA);
	अगर (rc)
		वापस rc;

	rc = ima_init_crypto();
	अगर (rc)
		वापस rc;
	rc = ima_init_ढाँचा();
	अगर (rc != 0)
		वापस rc;

	/* It can be called beक्रमe ima_init_digests(), it करोes not use TPM. */
	ima_load_kexec_buffer();

	rc = ima_init_digests();
	अगर (rc != 0)
		वापस rc;
	rc = ima_add_boot_aggregate();	/* boot aggregate must be first entry */
	अगर (rc != 0)
		वापस rc;

	ima_init_policy();

	rc = ima_fs_init();
	अगर (rc != 0)
		वापस rc;

	ima_init_key_queue();

	ima_measure_critical_data("kernel_info", "kernel_version",
				  UTS_RELEASE, म_माप(UTS_RELEASE), false);

	वापस rc;
पूर्ण
