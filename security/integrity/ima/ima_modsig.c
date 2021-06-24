<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * IMA support क्रम appraising module-style appended signatures.
 *
 * Copyright (C) 2019  IBM Corporation
 *
 * Author:
 * Thiago Jung Bauermann <bauerman@linux.ibm.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/module_signature.h>
#समावेश <keys/asymmetric-type.h>
#समावेश <crypto/pkcs7.h>

#समावेश "ima.h"

काष्ठा modsig अणु
	काष्ठा pkcs7_message *pkcs7_msg;

	क्रमागत hash_algo hash_algo;

	/* This digest will go in the 'd-modsig' field of the IMA ढाँचा. */
	स्थिर u8 *digest;
	u32 digest_size;

	/*
	 * This is what will go to the measurement list अगर the ढाँचा requires
	 * storing the signature.
	 */
	पूर्णांक raw_pkcs7_len;
	u8 raw_pkcs7[];
पूर्ण;

/*
 * ima_पढ़ो_modsig - Read modsig from buf.
 *
 * Return: 0 on success, error code otherwise.
 */
पूर्णांक ima_पढ़ो_modsig(क्रमागत ima_hooks func, स्थिर व्योम *buf, loff_t buf_len,
		    काष्ठा modsig **modsig)
अणु
	स्थिर माप_प्रकार marker_len = म_माप(MODULE_SIG_STRING);
	स्थिर काष्ठा module_signature *sig;
	काष्ठा modsig *hdr;
	माप_प्रकार sig_len;
	स्थिर व्योम *p;
	पूर्णांक rc;

	अगर (buf_len <= marker_len + माप(*sig))
		वापस -ENOENT;

	p = buf + buf_len - marker_len;
	अगर (स_भेद(p, MODULE_SIG_STRING, marker_len))
		वापस -ENOENT;

	buf_len -= marker_len;
	sig = (स्थिर काष्ठा module_signature *)(p - माप(*sig));

	rc = mod_check_sig(sig, buf_len, func_tokens[func]);
	अगर (rc)
		वापस rc;

	sig_len = be32_to_cpu(sig->sig_len);
	buf_len -= sig_len + माप(*sig);

	/* Allocate sig_len additional bytes to hold the raw PKCS#7 data. */
	hdr = kzalloc(माप(*hdr) + sig_len, GFP_KERNEL);
	अगर (!hdr)
		वापस -ENOMEM;

	hdr->pkcs7_msg = pkcs7_parse_message(buf + buf_len, sig_len);
	अगर (IS_ERR(hdr->pkcs7_msg)) अणु
		rc = PTR_ERR(hdr->pkcs7_msg);
		kमुक्त(hdr);
		वापस rc;
	पूर्ण

	स_नकल(hdr->raw_pkcs7, buf + buf_len, sig_len);
	hdr->raw_pkcs7_len = sig_len;

	/* We करोn't know the hash algorithm yet. */
	hdr->hash_algo = HASH_ALGO__LAST;

	*modsig = hdr;

	वापस 0;
पूर्ण

/**
 * ima_collect_modsig - Calculate the file hash without the appended signature.
 *
 * Since the modsig is part of the file contents, the hash used in its signature
 * isn't the same one ordinarily calculated by IMA. Thereक्रमe PKCS7 code
 * calculates a separate one क्रम signature verअगरication.
 */
व्योम ima_collect_modsig(काष्ठा modsig *modsig, स्थिर व्योम *buf, loff_t size)
अणु
	पूर्णांक rc;

	/*
	 * Provide the file contents (minus the appended sig) so that the PKCS7
	 * code can calculate the file hash.
	 */
	size -= modsig->raw_pkcs7_len + म_माप(MODULE_SIG_STRING) +
		माप(काष्ठा module_signature);
	rc = pkcs7_supply_detached_data(modsig->pkcs7_msg, buf, size);
	अगर (rc)
		वापस;

	/* Ask the PKCS7 code to calculate the file hash. */
	rc = pkcs7_get_digest(modsig->pkcs7_msg, &modsig->digest,
			      &modsig->digest_size, &modsig->hash_algo);
पूर्ण

पूर्णांक ima_modsig_verअगरy(काष्ठा key *keyring, स्थिर काष्ठा modsig *modsig)
अणु
	वापस verअगरy_pkcs7_message_sig(शून्य, 0, modsig->pkcs7_msg, keyring,
					VERIFYING_MODULE_SIGNATURE, शून्य, शून्य);
पूर्ण

पूर्णांक ima_get_modsig_digest(स्थिर काष्ठा modsig *modsig, क्रमागत hash_algo *algo,
			  स्थिर u8 **digest, u32 *digest_size)
अणु
	*algo = modsig->hash_algo;
	*digest = modsig->digest;
	*digest_size = modsig->digest_size;

	वापस 0;
पूर्ण

पूर्णांक ima_get_raw_modsig(स्थिर काष्ठा modsig *modsig, स्थिर व्योम **data,
		       u32 *data_len)
अणु
	*data = &modsig->raw_pkcs7;
	*data_len = modsig->raw_pkcs7_len;

	वापस 0;
पूर्ण

व्योम ima_मुक्त_modsig(काष्ठा modsig *modsig)
अणु
	अगर (!modsig)
		वापस;

	pkcs7_मुक्त_message(modsig->pkcs7_msg);
	kमुक्त(modsig);
पूर्ण
