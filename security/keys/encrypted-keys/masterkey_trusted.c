<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2010 IBM Corporation
 * Copyright (C) 2010 Politecnico di Torino, Italy
 *                    TORSEC group -- https://security.polito.it
 *
 * Authors:
 * Mimi Zohar <zohar@us.ibm.com>
 * Roberto Sassu <roberto.sassu@polito.it>
 *
 * See Documentation/security/keys/trusted-encrypted.rst
 */

#समावेश <linux/uaccess.h>
#समावेश <linux/err.h>
#समावेश <keys/trusted-type.h>
#समावेश <keys/encrypted-type.h>
#समावेश "encrypted.h"

/*
 * request_trusted_key - request the trusted key
 *
 * Trusted keys are sealed to PCRs and other metadata. Although userspace
 * manages both trusted/encrypted key-types, like the encrypted key type
 * data, trusted key type data is not visible decrypted from userspace.
 */
काष्ठा key *request_trusted_key(स्थिर अक्षर *trusted_desc,
				स्थिर u8 **master_key, माप_प्रकार *master_keylen)
अणु
	काष्ठा trusted_key_payload *tpayload;
	काष्ठा key *tkey;

	tkey = request_key(&key_type_trusted, trusted_desc, शून्य);
	अगर (IS_ERR(tkey))
		जाओ error;

	करोwn_पढ़ो(&tkey->sem);
	tpayload = tkey->payload.data[0];
	*master_key = tpayload->key;
	*master_keylen = tpayload->key_len;
error:
	वापस tkey;
पूर्ण
