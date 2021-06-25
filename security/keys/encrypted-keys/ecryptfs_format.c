<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ecryptfs_क्रमmat.c: helper functions क्रम the encrypted key type
 *
 * Copyright (C) 2006 International Business Machines Corp.
 * Copyright (C) 2010 Politecnico di Torino, Italy
 *                    TORSEC group -- https://security.polito.it
 *
 * Authors:
 * Michael A. Halcrow <mahalcro@us.ibm.com>
 * Tyler Hicks <tyhicks@ou.edu>
 * Roberto Sassu <roberto.sassu@polito.it>
 */

#समावेश <linux/export.h>
#समावेश <linux/माला.स>
#समावेश "ecryptfs_format.h"

u8 *ecryptfs_get_auth_tok_key(काष्ठा ecryptfs_auth_tok *auth_tok)
अणु
	वापस auth_tok->token.password.session_key_encryption_key;
पूर्ण
EXPORT_SYMBOL(ecryptfs_get_auth_tok_key);

/*
 * ecryptfs_get_versions()
 *
 * Source code taken from the software 'ecryptfs-utils' version 83.
 *
 */
व्योम ecryptfs_get_versions(पूर्णांक *major, पूर्णांक *minor, पूर्णांक *file_version)
अणु
	*major = ECRYPTFS_VERSION_MAJOR;
	*minor = ECRYPTFS_VERSION_MINOR;
	अगर (file_version)
		*file_version = ECRYPTFS_SUPPORTED_खाता_VERSION;
पूर्ण
EXPORT_SYMBOL(ecryptfs_get_versions);

/*
 * ecryptfs_fill_auth_tok - fill the ecryptfs_auth_tok काष्ठाure
 *
 * Fill the ecryptfs_auth_tok काष्ठाure with required ecryptfs data.
 * The source code is inspired to the original function generate_payload()
 * shipped with the software 'ecryptfs-utils' version 83.
 *
 */
पूर्णांक ecryptfs_fill_auth_tok(काष्ठा ecryptfs_auth_tok *auth_tok,
			   स्थिर अक्षर *key_desc)
अणु
	पूर्णांक major, minor;

	ecryptfs_get_versions(&major, &minor, शून्य);
	auth_tok->version = (((uपूर्णांक16_t)(major << 8) & 0xFF00)
			     | ((uपूर्णांक16_t)minor & 0x00FF));
	auth_tok->token_type = ECRYPTFS_PASSWORD;
	म_नकलन((अक्षर *)auth_tok->token.password.signature, key_desc,
		ECRYPTFS_PASSWORD_SIG_SIZE);
	auth_tok->token.password.session_key_encryption_key_bytes =
		ECRYPTFS_MAX_KEY_BYTES;
	/*
	 * Removed auth_tok->token.password.salt and
	 * auth_tok->token.password.session_key_encryption_key
	 * initialization from the original code
	 */
	/* TODO: Make the hash parameterizable via policy */
	auth_tok->token.password.flags |=
		ECRYPTFS_SESSION_KEY_ENCRYPTION_KEY_SET;
	/* The kernel code will encrypt the session key. */
	auth_tok->session_key.encrypted_key[0] = 0;
	auth_tok->session_key.encrypted_key_size = 0;
	/* Default; subject to change by kernel eCryptfs */
	auth_tok->token.password.hash_algo = PGP_DIGEST_ALGO_SHA512;
	auth_tok->token.password.flags &= ~(ECRYPTFS_PERSISTENT_PASSWORD);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ecryptfs_fill_auth_tok);
