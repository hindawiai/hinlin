<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * eCryptfs: Linux fileप्रणाली encryption layer
 * Functions only useful क्रम debugging.
 *
 * Copyright (C) 2006 International Business Machines Corp.
 *   Author(s): Michael A. Halcrow <mahalcro@us.ibm.com>
 */

#समावेश "ecryptfs_kernel.h"

/*
 * ecryptfs_dump_auth_tok - debug function to prपूर्णांक auth toks
 *
 * This function will prपूर्णांक the contents of an ecryptfs authentication
 * token.
 */
व्योम ecryptfs_dump_auth_tok(काष्ठा ecryptfs_auth_tok *auth_tok)
अणु
	अक्षर salt[ECRYPTFS_SALT_SIZE * 2 + 1];
	अक्षर sig[ECRYPTFS_SIG_SIZE_HEX + 1];

	ecryptfs_prपूर्णांकk(KERN_DEBUG, "Auth tok at mem loc [%p]:\n",
			auth_tok);
	अगर (auth_tok->flags & ECRYPTFS_PRIVATE_KEY) अणु
		ecryptfs_prपूर्णांकk(KERN_DEBUG, " * private key type\n");
	पूर्ण अन्यथा अणु
		ecryptfs_prपूर्णांकk(KERN_DEBUG, " * passphrase type\n");
		ecryptfs_to_hex(salt, auth_tok->token.password.salt,
				ECRYPTFS_SALT_SIZE);
		salt[ECRYPTFS_SALT_SIZE * 2] = '\0';
		ecryptfs_prपूर्णांकk(KERN_DEBUG, " * salt = [%s]\n", salt);
		अगर (auth_tok->token.password.flags &
		    ECRYPTFS_PERSISTENT_PASSWORD) अणु
			ecryptfs_prपूर्णांकk(KERN_DEBUG, " * persistent\n");
		पूर्ण
		स_नकल(sig, auth_tok->token.password.signature,
		       ECRYPTFS_SIG_SIZE_HEX);
		sig[ECRYPTFS_SIG_SIZE_HEX] = '\0';
		ecryptfs_prपूर्णांकk(KERN_DEBUG, " * signature = [%s]\n", sig);
	पूर्ण
	ecryptfs_prपूर्णांकk(KERN_DEBUG, " * session_key.flags = [0x%x]\n",
			auth_tok->session_key.flags);
	अगर (auth_tok->session_key.flags
	    & ECRYPTFS_USERSPACE_SHOULD_TRY_TO_DECRYPT)
		ecryptfs_prपूर्णांकk(KERN_DEBUG,
				" * Userspace decrypt request set\n");
	अगर (auth_tok->session_key.flags
	    & ECRYPTFS_USERSPACE_SHOULD_TRY_TO_ENCRYPT)
		ecryptfs_prपूर्णांकk(KERN_DEBUG,
				" * Userspace encrypt request set\n");
	अगर (auth_tok->session_key.flags & ECRYPTFS_CONTAINS_DECRYPTED_KEY) अणु
		ecryptfs_prपूर्णांकk(KERN_DEBUG, " * Contains decrypted key\n");
		ecryptfs_prपूर्णांकk(KERN_DEBUG,
				" * session_key.decrypted_key_size = [0x%x]\n",
				auth_tok->session_key.decrypted_key_size);
		ecryptfs_prपूर्णांकk(KERN_DEBUG, " * Decrypted session key "
				"dump:\n");
		अगर (ecryptfs_verbosity > 0)
			ecryptfs_dump_hex(auth_tok->session_key.decrypted_key,
					  ECRYPTFS_DEFAULT_KEY_BYTES);
	पूर्ण
	अगर (auth_tok->session_key.flags & ECRYPTFS_CONTAINS_ENCRYPTED_KEY) अणु
		ecryptfs_prपूर्णांकk(KERN_DEBUG, " * Contains encrypted key\n");
		ecryptfs_prपूर्णांकk(KERN_DEBUG,
				" * session_key.encrypted_key_size = [0x%x]\n",
				auth_tok->session_key.encrypted_key_size);
		ecryptfs_prपूर्णांकk(KERN_DEBUG, " * Encrypted session key "
				"dump:\n");
		अगर (ecryptfs_verbosity > 0)
			ecryptfs_dump_hex(auth_tok->session_key.encrypted_key,
					  auth_tok->session_key.
					  encrypted_key_size);
	पूर्ण
पूर्ण

/**
 * ecryptfs_dump_hex - debug hex prपूर्णांकer
 * @data: string of bytes to be prपूर्णांकed
 * @bytes: number of bytes to prपूर्णांक
 *
 * Dump hexadecimal representation of अक्षर array
 */
व्योम ecryptfs_dump_hex(अक्षर *data, पूर्णांक bytes)
अणु
	अगर (ecryptfs_verbosity < 1)
		वापस;

	prपूर्णांक_hex_dump(KERN_DEBUG, "ecryptfs: ", DUMP_PREFIX_OFFSET, 16, 1,
		       data, bytes, false);
पूर्ण
