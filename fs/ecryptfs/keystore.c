<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * eCryptfs: Linux fileप्रणाली encryption layer
 * In-kernel key management code.  Includes functions to parse and
 * ग_लिखो authentication token-related packets with the underlying
 * file.
 *
 * Copyright (C) 2004-2006 International Business Machines Corp.
 *   Author(s): Michael A. Halcrow <mhalcrow@us.ibm.com>
 *              Michael C. Thompson <mcthomps@us.ibm.com>
 *              Trevor S. Highland <trevor.highland@gmail.com>
 */

#समावेश <crypto/hash.h>
#समावेश <crypto/skcipher.h>
#समावेश <linux/माला.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/key.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>
#समावेश "ecryptfs_kernel.h"

/*
 * request_key वापसed an error instead of a valid key address;
 * determine the type of error, make appropriate log entries, and
 * वापस an error code.
 */
अटल पूर्णांक process_request_key_err(दीर्घ err_code)
अणु
	पूर्णांक rc = 0;

	चयन (err_code) अणु
	हाल -ENOKEY:
		ecryptfs_prपूर्णांकk(KERN_WARNING, "No key\n");
		rc = -ENOENT;
		अवरोध;
	हाल -EKEYEXPIRED:
		ecryptfs_prपूर्णांकk(KERN_WARNING, "Key expired\n");
		rc = -ETIME;
		अवरोध;
	हाल -EKEYREVOKED:
		ecryptfs_prपूर्णांकk(KERN_WARNING, "Key revoked\n");
		rc = -EINVAL;
		अवरोध;
	शेष:
		ecryptfs_prपूर्णांकk(KERN_WARNING, "Unknown error code: "
				"[0x%.16lx]\n", err_code);
		rc = -EINVAL;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक process_find_global_auth_tok_क्रम_sig_err(पूर्णांक err_code)
अणु
	पूर्णांक rc = err_code;

	चयन (err_code) अणु
	हाल -ENOENT:
		ecryptfs_prपूर्णांकk(KERN_WARNING, "Missing auth tok\n");
		अवरोध;
	हाल -EINVAL:
		ecryptfs_prपूर्णांकk(KERN_WARNING, "Invalid auth tok\n");
		अवरोध;
	शेष:
		rc = process_request_key_err(err_code);
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

/**
 * ecryptfs_parse_packet_length
 * @data: Poपूर्णांकer to memory containing length at offset
 * @size: This function ग_लिखोs the decoded size to this memory
 *        address; zero on error
 * @length_size: The number of bytes occupied by the encoded length
 *
 * Returns zero on success; non-zero on error
 */
पूर्णांक ecryptfs_parse_packet_length(अचिन्हित अक्षर *data, माप_प्रकार *size,
				 माप_प्रकार *length_size)
अणु
	पूर्णांक rc = 0;

	(*length_size) = 0;
	(*size) = 0;
	अगर (data[0] < 192) अणु
		/* One-byte length */
		(*size) = data[0];
		(*length_size) = 1;
	पूर्ण अन्यथा अगर (data[0] < 224) अणु
		/* Two-byte length */
		(*size) = (data[0] - 192) * 256;
		(*size) += data[1] + 192;
		(*length_size) = 2;
	पूर्ण अन्यथा अगर (data[0] == 255) अणु
		/* If support is added, adjust ECRYPTFS_MAX_PKT_LEN_SIZE */
		ecryptfs_prपूर्णांकk(KERN_ERR, "Five-byte packet length not "
				"supported\n");
		rc = -EINVAL;
		जाओ out;
	पूर्ण अन्यथा अणु
		ecryptfs_prपूर्णांकk(KERN_ERR, "Error parsing packet length\n");
		rc = -EINVAL;
		जाओ out;
	पूर्ण
out:
	वापस rc;
पूर्ण

/**
 * ecryptfs_ग_लिखो_packet_length
 * @dest: The byte array target पूर्णांकo which to ग_लिखो the length. Must
 *        have at least ECRYPTFS_MAX_PKT_LEN_SIZE bytes allocated.
 * @size: The length to ग_लिखो.
 * @packet_size_length: The number of bytes used to encode the packet
 *                      length is written to this address.
 *
 * Returns zero on success; non-zero on error.
 */
पूर्णांक ecryptfs_ग_लिखो_packet_length(अक्षर *dest, माप_प्रकार size,
				 माप_प्रकार *packet_size_length)
अणु
	पूर्णांक rc = 0;

	अगर (size < 192) अणु
		dest[0] = size;
		(*packet_size_length) = 1;
	पूर्ण अन्यथा अगर (size < 65536) अणु
		dest[0] = (((size - 192) / 256) + 192);
		dest[1] = ((size - 192) % 256);
		(*packet_size_length) = 2;
	पूर्ण अन्यथा अणु
		/* If support is added, adjust ECRYPTFS_MAX_PKT_LEN_SIZE */
		rc = -EINVAL;
		ecryptfs_prपूर्णांकk(KERN_WARNING,
				"Unsupported packet size: [%zd]\n", size);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक
ग_लिखो_tag_64_packet(अक्षर *signature, काष्ठा ecryptfs_session_key *session_key,
		    अक्षर **packet, माप_प्रकार *packet_len)
अणु
	माप_प्रकार i = 0;
	माप_प्रकार data_len;
	माप_प्रकार packet_size_len;
	अक्षर *message;
	पूर्णांक rc;

	/*
	 *              ***** TAG 64 Packet Format *****
	 *    | Content Type                       | 1 byte       |
	 *    | Key Identअगरier Size                | 1 or 2 bytes |
	 *    | Key Identअगरier                     | arbitrary    |
	 *    | Encrypted File Encryption Key Size | 1 or 2 bytes |
	 *    | Encrypted File Encryption Key      | arbitrary    |
	 */
	data_len = (5 + ECRYPTFS_SIG_SIZE_HEX
		    + session_key->encrypted_key_size);
	*packet = kदो_स्मृति(data_len, GFP_KERNEL);
	message = *packet;
	अगर (!message) अणु
		ecryptfs_prपूर्णांकk(KERN_ERR, "Unable to allocate memory\n");
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	message[i++] = ECRYPTFS_TAG_64_PACKET_TYPE;
	rc = ecryptfs_ग_लिखो_packet_length(&message[i], ECRYPTFS_SIG_SIZE_HEX,
					  &packet_size_len);
	अगर (rc) अणु
		ecryptfs_prपूर्णांकk(KERN_ERR, "Error generating tag 64 packet "
				"header; cannot generate packet length\n");
		जाओ out;
	पूर्ण
	i += packet_size_len;
	स_नकल(&message[i], signature, ECRYPTFS_SIG_SIZE_HEX);
	i += ECRYPTFS_SIG_SIZE_HEX;
	rc = ecryptfs_ग_लिखो_packet_length(&message[i],
					  session_key->encrypted_key_size,
					  &packet_size_len);
	अगर (rc) अणु
		ecryptfs_prपूर्णांकk(KERN_ERR, "Error generating tag 64 packet "
				"header; cannot generate packet length\n");
		जाओ out;
	पूर्ण
	i += packet_size_len;
	स_नकल(&message[i], session_key->encrypted_key,
	       session_key->encrypted_key_size);
	i += session_key->encrypted_key_size;
	*packet_len = i;
out:
	वापस rc;
पूर्ण

अटल पूर्णांक
parse_tag_65_packet(काष्ठा ecryptfs_session_key *session_key, u8 *cipher_code,
		    काष्ठा ecryptfs_message *msg)
अणु
	माप_प्रकार i = 0;
	अक्षर *data;
	माप_प्रकार data_len;
	माप_प्रकार m_size;
	माप_प्रकार message_len;
	u16 checksum = 0;
	u16 expected_checksum = 0;
	पूर्णांक rc;

	/*
	 *              ***** TAG 65 Packet Format *****
	 *         | Content Type             | 1 byte       |
	 *         | Status Indicator         | 1 byte       |
	 *         | File Encryption Key Size | 1 or 2 bytes |
	 *         | File Encryption Key      | arbitrary    |
	 */
	message_len = msg->data_len;
	data = msg->data;
	अगर (message_len < 4) अणु
		rc = -EIO;
		जाओ out;
	पूर्ण
	अगर (data[i++] != ECRYPTFS_TAG_65_PACKET_TYPE) अणु
		ecryptfs_prपूर्णांकk(KERN_ERR, "Type should be ECRYPTFS_TAG_65\n");
		rc = -EIO;
		जाओ out;
	पूर्ण
	अगर (data[i++]) अणु
		ecryptfs_prपूर्णांकk(KERN_ERR, "Status indicator has non-zero value "
				"[%d]\n", data[i-1]);
		rc = -EIO;
		जाओ out;
	पूर्ण
	rc = ecryptfs_parse_packet_length(&data[i], &m_size, &data_len);
	अगर (rc) अणु
		ecryptfs_prपूर्णांकk(KERN_WARNING, "Error parsing packet length; "
				"rc = [%d]\n", rc);
		जाओ out;
	पूर्ण
	i += data_len;
	अगर (message_len < (i + m_size)) अणु
		ecryptfs_prपूर्णांकk(KERN_ERR, "The message received from ecryptfsd "
				"is shorter than expected\n");
		rc = -EIO;
		जाओ out;
	पूर्ण
	अगर (m_size < 3) अणु
		ecryptfs_prपूर्णांकk(KERN_ERR,
				"The decrypted key is not long enough to "
				"include a cipher code and checksum\n");
		rc = -EIO;
		जाओ out;
	पूर्ण
	*cipher_code = data[i++];
	/* The decrypted key includes 1 byte cipher code and 2 byte checksum */
	session_key->decrypted_key_size = m_size - 3;
	अगर (session_key->decrypted_key_size > ECRYPTFS_MAX_KEY_BYTES) अणु
		ecryptfs_prपूर्णांकk(KERN_ERR, "key_size [%d] larger than "
				"the maximum key size [%d]\n",
				session_key->decrypted_key_size,
				ECRYPTFS_MAX_ENCRYPTED_KEY_BYTES);
		rc = -EIO;
		जाओ out;
	पूर्ण
	स_नकल(session_key->decrypted_key, &data[i],
	       session_key->decrypted_key_size);
	i += session_key->decrypted_key_size;
	expected_checksum += (अचिन्हित अक्षर)(data[i++]) << 8;
	expected_checksum += (अचिन्हित अक्षर)(data[i++]);
	क्रम (i = 0; i < session_key->decrypted_key_size; i++)
		checksum += session_key->decrypted_key[i];
	अगर (expected_checksum != checksum) अणु
		ecryptfs_prपूर्णांकk(KERN_ERR, "Invalid checksum for file "
				"encryption  key; expected [%x]; calculated "
				"[%x]\n", expected_checksum, checksum);
		rc = -EIO;
	पूर्ण
out:
	वापस rc;
पूर्ण


अटल पूर्णांक
ग_लिखो_tag_66_packet(अक्षर *signature, u8 cipher_code,
		    काष्ठा ecryptfs_crypt_stat *crypt_stat, अक्षर **packet,
		    माप_प्रकार *packet_len)
अणु
	माप_प्रकार i = 0;
	माप_प्रकार j;
	माप_प्रकार data_len;
	माप_प्रकार checksum = 0;
	माप_प्रकार packet_size_len;
	अक्षर *message;
	पूर्णांक rc;

	/*
	 *              ***** TAG 66 Packet Format *****
	 *         | Content Type             | 1 byte       |
	 *         | Key Identअगरier Size      | 1 or 2 bytes |
	 *         | Key Identअगरier           | arbitrary    |
	 *         | File Encryption Key Size | 1 or 2 bytes |
	 *         | File Encryption Key      | arbitrary    |
	 */
	data_len = (5 + ECRYPTFS_SIG_SIZE_HEX + crypt_stat->key_size);
	*packet = kदो_स्मृति(data_len, GFP_KERNEL);
	message = *packet;
	अगर (!message) अणु
		ecryptfs_prपूर्णांकk(KERN_ERR, "Unable to allocate memory\n");
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	message[i++] = ECRYPTFS_TAG_66_PACKET_TYPE;
	rc = ecryptfs_ग_लिखो_packet_length(&message[i], ECRYPTFS_SIG_SIZE_HEX,
					  &packet_size_len);
	अगर (rc) अणु
		ecryptfs_prपूर्णांकk(KERN_ERR, "Error generating tag 66 packet "
				"header; cannot generate packet length\n");
		जाओ out;
	पूर्ण
	i += packet_size_len;
	स_नकल(&message[i], signature, ECRYPTFS_SIG_SIZE_HEX);
	i += ECRYPTFS_SIG_SIZE_HEX;
	/* The encrypted key includes 1 byte cipher code and 2 byte checksum */
	rc = ecryptfs_ग_लिखो_packet_length(&message[i], crypt_stat->key_size + 3,
					  &packet_size_len);
	अगर (rc) अणु
		ecryptfs_prपूर्णांकk(KERN_ERR, "Error generating tag 66 packet "
				"header; cannot generate packet length\n");
		जाओ out;
	पूर्ण
	i += packet_size_len;
	message[i++] = cipher_code;
	स_नकल(&message[i], crypt_stat->key, crypt_stat->key_size);
	i += crypt_stat->key_size;
	क्रम (j = 0; j < crypt_stat->key_size; j++)
		checksum += crypt_stat->key[j];
	message[i++] = (checksum / 256) % 256;
	message[i++] = (checksum % 256);
	*packet_len = i;
out:
	वापस rc;
पूर्ण

अटल पूर्णांक
parse_tag_67_packet(काष्ठा ecryptfs_key_record *key_rec,
		    काष्ठा ecryptfs_message *msg)
अणु
	माप_प्रकार i = 0;
	अक्षर *data;
	माप_प्रकार data_len;
	माप_प्रकार message_len;
	पूर्णांक rc;

	/*
	 *              ***** TAG 65 Packet Format *****
	 *    | Content Type                       | 1 byte       |
	 *    | Status Indicator                   | 1 byte       |
	 *    | Encrypted File Encryption Key Size | 1 or 2 bytes |
	 *    | Encrypted File Encryption Key      | arbitrary    |
	 */
	message_len = msg->data_len;
	data = msg->data;
	/* verअगरy that everything through the encrypted FEK size is present */
	अगर (message_len < 4) अणु
		rc = -EIO;
		prपूर्णांकk(KERN_ERR "%s: message_len is [%zd]; minimum acceptable "
		       "message length is [%d]\n", __func__, message_len, 4);
		जाओ out;
	पूर्ण
	अगर (data[i++] != ECRYPTFS_TAG_67_PACKET_TYPE) अणु
		rc = -EIO;
		prपूर्णांकk(KERN_ERR "%s: Type should be ECRYPTFS_TAG_67\n",
		       __func__);
		जाओ out;
	पूर्ण
	अगर (data[i++]) अणु
		rc = -EIO;
		prपूर्णांकk(KERN_ERR "%s: Status indicator has non zero "
		       "value [%d]\n", __func__, data[i-1]);

		जाओ out;
	पूर्ण
	rc = ecryptfs_parse_packet_length(&data[i], &key_rec->enc_key_size,
					  &data_len);
	अगर (rc) अणु
		ecryptfs_prपूर्णांकk(KERN_WARNING, "Error parsing packet length; "
				"rc = [%d]\n", rc);
		जाओ out;
	पूर्ण
	i += data_len;
	अगर (message_len < (i + key_rec->enc_key_size)) अणु
		rc = -EIO;
		prपूर्णांकk(KERN_ERR "%s: message_len [%zd]; max len is [%zd]\n",
		       __func__, message_len, (i + key_rec->enc_key_size));
		जाओ out;
	पूर्ण
	अगर (key_rec->enc_key_size > ECRYPTFS_MAX_ENCRYPTED_KEY_BYTES) अणु
		rc = -EIO;
		prपूर्णांकk(KERN_ERR "%s: Encrypted key_size [%zd] larger than "
		       "the maximum key size [%d]\n", __func__,
		       key_rec->enc_key_size,
		       ECRYPTFS_MAX_ENCRYPTED_KEY_BYTES);
		जाओ out;
	पूर्ण
	स_नकल(key_rec->enc_key, &data[i], key_rec->enc_key_size);
out:
	वापस rc;
पूर्ण

/**
 * ecryptfs_verअगरy_version
 * @version: The version number to confirm
 *
 * Returns zero on good version; non-zero otherwise
 */
अटल पूर्णांक ecryptfs_verअगरy_version(u16 version)
अणु
	पूर्णांक rc = 0;
	अचिन्हित अक्षर major;
	अचिन्हित अक्षर minor;

	major = ((version >> 8) & 0xFF);
	minor = (version & 0xFF);
	अगर (major != ECRYPTFS_VERSION_MAJOR) अणु
		ecryptfs_prपूर्णांकk(KERN_ERR, "Major version number mismatch. "
				"Expected [%d]; got [%d]\n",
				ECRYPTFS_VERSION_MAJOR, major);
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	अगर (minor != ECRYPTFS_VERSION_MINOR) अणु
		ecryptfs_prपूर्णांकk(KERN_ERR, "Minor version number mismatch. "
				"Expected [%d]; got [%d]\n",
				ECRYPTFS_VERSION_MINOR, minor);
		rc = -EINVAL;
		जाओ out;
	पूर्ण
out:
	वापस rc;
पूर्ण

/**
 * ecryptfs_verअगरy_auth_tok_from_key
 * @auth_tok_key: key containing the authentication token
 * @auth_tok: authentication token
 *
 * Returns zero on valid auth tok; -EINVAL अगर the payload is invalid; or
 * -EKEYREVOKED अगर the key was revoked beक्रमe we acquired its semaphore.
 */
अटल पूर्णांक
ecryptfs_verअगरy_auth_tok_from_key(काष्ठा key *auth_tok_key,
				  काष्ठा ecryptfs_auth_tok **auth_tok)
अणु
	पूर्णांक rc = 0;

	(*auth_tok) = ecryptfs_get_key_payload_data(auth_tok_key);
	अगर (IS_ERR(*auth_tok)) अणु
		rc = PTR_ERR(*auth_tok);
		*auth_tok = शून्य;
		जाओ out;
	पूर्ण

	अगर (ecryptfs_verअगरy_version((*auth_tok)->version)) अणु
		prपूर्णांकk(KERN_ERR "Data structure version mismatch. Userspace "
		       "tools must match eCryptfs kernel module with major "
		       "version [%d] and minor version [%d]\n",
		       ECRYPTFS_VERSION_MAJOR, ECRYPTFS_VERSION_MINOR);
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	अगर ((*auth_tok)->token_type != ECRYPTFS_PASSWORD
	    && (*auth_tok)->token_type != ECRYPTFS_PRIVATE_KEY) अणु
		prपूर्णांकk(KERN_ERR "Invalid auth_tok structure "
		       "returned from key query\n");
		rc = -EINVAL;
		जाओ out;
	पूर्ण
out:
	वापस rc;
पूर्ण

अटल पूर्णांक
ecryptfs_find_global_auth_tok_क्रम_sig(
	काष्ठा key **auth_tok_key,
	काष्ठा ecryptfs_auth_tok **auth_tok,
	काष्ठा ecryptfs_mount_crypt_stat *mount_crypt_stat, अक्षर *sig)
अणु
	काष्ठा ecryptfs_global_auth_tok *walker;
	पूर्णांक rc = 0;

	(*auth_tok_key) = शून्य;
	(*auth_tok) = शून्य;
	mutex_lock(&mount_crypt_stat->global_auth_tok_list_mutex);
	list_क्रम_each_entry(walker,
			    &mount_crypt_stat->global_auth_tok_list,
			    mount_crypt_stat_list) अणु
		अगर (स_भेद(walker->sig, sig, ECRYPTFS_SIG_SIZE_HEX))
			जारी;

		अगर (walker->flags & ECRYPTFS_AUTH_TOK_INVALID) अणु
			rc = -EINVAL;
			जाओ out;
		पूर्ण

		rc = key_validate(walker->global_auth_tok_key);
		अगर (rc) अणु
			अगर (rc == -EKEYEXPIRED)
				जाओ out;
			जाओ out_invalid_auth_tok;
		पूर्ण

		करोwn_ग_लिखो(&(walker->global_auth_tok_key->sem));
		rc = ecryptfs_verअगरy_auth_tok_from_key(
				walker->global_auth_tok_key, auth_tok);
		अगर (rc)
			जाओ out_invalid_auth_tok_unlock;

		(*auth_tok_key) = walker->global_auth_tok_key;
		key_get(*auth_tok_key);
		जाओ out;
	पूर्ण
	rc = -ENOENT;
	जाओ out;
out_invalid_auth_tok_unlock:
	up_ग_लिखो(&(walker->global_auth_tok_key->sem));
out_invalid_auth_tok:
	prपूर्णांकk(KERN_WARNING "Invalidating auth tok with sig = [%s]\n", sig);
	walker->flags |= ECRYPTFS_AUTH_TOK_INVALID;
	key_put(walker->global_auth_tok_key);
	walker->global_auth_tok_key = शून्य;
out:
	mutex_unlock(&mount_crypt_stat->global_auth_tok_list_mutex);
	वापस rc;
पूर्ण

/**
 * ecryptfs_find_auth_tok_क्रम_sig
 * @auth_tok_key: key containing the authentication token
 * @auth_tok: Set to the matching auth_tok; शून्य अगर not found
 * @mount_crypt_stat: inode crypt_stat crypto context
 * @sig: Sig of auth_tok to find
 *
 * For now, this function simply looks at the रेजिस्टरed auth_tok's
 * linked off the mount_crypt_stat, so all the auth_toks that can be
 * used must be रेजिस्टरed at mount समय. This function could
 * potentially try a lot harder to find auth_tok's (e.g., by calling
 * out to ecryptfsd to dynamically retrieve an auth_tok object) so
 * that अटल registration of auth_tok's will no दीर्घer be necessary.
 *
 * Returns zero on no error; non-zero on error
 */
अटल पूर्णांक
ecryptfs_find_auth_tok_क्रम_sig(
	काष्ठा key **auth_tok_key,
	काष्ठा ecryptfs_auth_tok **auth_tok,
	काष्ठा ecryptfs_mount_crypt_stat *mount_crypt_stat,
	अक्षर *sig)
अणु
	पूर्णांक rc = 0;

	rc = ecryptfs_find_global_auth_tok_क्रम_sig(auth_tok_key, auth_tok,
						   mount_crypt_stat, sig);
	अगर (rc == -ENOENT) अणु
		/* अगर the flag ECRYPTFS_GLOBAL_MOUNT_AUTH_TOK_ONLY is set in the
		 * mount_crypt_stat काष्ठाure, we prevent to use auth toks that
		 * are not inserted through the ecryptfs_add_global_auth_tok
		 * function.
		 */
		अगर (mount_crypt_stat->flags
				& ECRYPTFS_GLOBAL_MOUNT_AUTH_TOK_ONLY)
			वापस -EINVAL;

		rc = ecryptfs_keyring_auth_tok_क्रम_sig(auth_tok_key, auth_tok,
						       sig);
	पूर्ण
	वापस rc;
पूर्ण

/*
 * ग_लिखो_tag_70_packet can gobble a lot of stack space. We stuff most
 * of the function's parameters in a kmalloc'd काष्ठा to help reduce
 * eCryptfs' overall stack usage.
 */
काष्ठा ecryptfs_ग_लिखो_tag_70_packet_silly_stack अणु
	u8 cipher_code;
	माप_प्रकार max_packet_size;
	माप_प्रकार packet_size_len;
	माप_प्रकार block_aligned_filename_size;
	माप_प्रकार block_size;
	माप_प्रकार i;
	माप_प्रकार j;
	माप_प्रकार num_अक्रम_bytes;
	काष्ठा mutex *tfm_mutex;
	अक्षर *block_aligned_filename;
	काष्ठा ecryptfs_auth_tok *auth_tok;
	काष्ठा scatterlist src_sg[2];
	काष्ठा scatterlist dst_sg[2];
	काष्ठा crypto_skcipher *skcipher_tfm;
	काष्ठा skcipher_request *skcipher_req;
	अक्षर iv[ECRYPTFS_MAX_IV_BYTES];
	अक्षर hash[ECRYPTFS_TAG_70_DIGEST_SIZE];
	अक्षर पंचांगp_hash[ECRYPTFS_TAG_70_DIGEST_SIZE];
	काष्ठा crypto_shash *hash_tfm;
	काष्ठा shash_desc *hash_desc;
पूर्ण;

/*
 * ग_लिखो_tag_70_packet - Write encrypted filename (EFN) packet against FNEK
 * @filename: शून्य-terminated filename string
 *
 * This is the simplest mechanism क्रम achieving filename encryption in
 * eCryptfs. It encrypts the given filename with the mount-wide
 * filename encryption key (FNEK) and stores it in a packet to @dest,
 * which the callee will encode and ग_लिखो directly पूर्णांकo the dentry
 * name.
 */
पूर्णांक
ecryptfs_ग_लिखो_tag_70_packet(अक्षर *dest, माप_प्रकार *reमुख्यing_bytes,
			     माप_प्रकार *packet_size,
			     काष्ठा ecryptfs_mount_crypt_stat *mount_crypt_stat,
			     अक्षर *filename, माप_प्रकार filename_size)
अणु
	काष्ठा ecryptfs_ग_लिखो_tag_70_packet_silly_stack *s;
	काष्ठा key *auth_tok_key = शून्य;
	पूर्णांक rc = 0;

	s = kzalloc(माप(*s), GFP_KERNEL);
	अगर (!s)
		वापस -ENOMEM;

	(*packet_size) = 0;
	rc = ecryptfs_find_auth_tok_क्रम_sig(
		&auth_tok_key,
		&s->auth_tok, mount_crypt_stat,
		mount_crypt_stat->global_शेष_fnek_sig);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "%s: Error attempting to find auth tok for "
		       "fnek sig [%s]; rc = [%d]\n", __func__,
		       mount_crypt_stat->global_शेष_fnek_sig, rc);
		जाओ out;
	पूर्ण
	rc = ecryptfs_get_tfm_and_mutex_क्रम_cipher_name(
		&s->skcipher_tfm,
		&s->tfm_mutex, mount_crypt_stat->global_शेष_fn_cipher_name);
	अगर (unlikely(rc)) अणु
		prपूर्णांकk(KERN_ERR "Internal error whilst attempting to get "
		       "tfm and mutex for cipher name [%s]; rc = [%d]\n",
		       mount_crypt_stat->global_शेष_fn_cipher_name, rc);
		जाओ out;
	पूर्ण
	mutex_lock(s->tfm_mutex);
	s->block_size = crypto_skcipher_blocksize(s->skcipher_tfm);
	/* Plus one क्रम the \0 separator between the अक्रमom prefix
	 * and the plaपूर्णांकext filename */
	s->num_अक्रम_bytes = (ECRYPTFS_खाताNAME_MIN_RANDOM_PREPEND_BYTES + 1);
	s->block_aligned_filename_size = (s->num_अक्रम_bytes + filename_size);
	अगर ((s->block_aligned_filename_size % s->block_size) != 0) अणु
		s->num_अक्रम_bytes += (s->block_size
				      - (s->block_aligned_filename_size
					 % s->block_size));
		s->block_aligned_filename_size = (s->num_अक्रम_bytes
						  + filename_size);
	पूर्ण
	/* Octet 0: Tag 70 identअगरier
	 * Octets 1-N1: Tag 70 packet size (includes cipher identअगरier
	 *              and block-aligned encrypted filename size)
	 * Octets N1-N2: FNEK sig (ECRYPTFS_SIG_SIZE)
	 * Octet N2-N3: Cipher identअगरier (1 octet)
	 * Octets N3-N4: Block-aligned encrypted filename
	 *  - Consists of a minimum number of अक्रमom अक्षरacters, a \0
	 *    separator, and then the filename */
	s->max_packet_size = (ECRYPTFS_TAG_70_MAX_METADATA_SIZE
			      + s->block_aligned_filename_size);
	अगर (!dest) अणु
		(*packet_size) = s->max_packet_size;
		जाओ out_unlock;
	पूर्ण
	अगर (s->max_packet_size > (*reमुख्यing_bytes)) अणु
		prपूर्णांकk(KERN_WARNING "%s: Require [%zd] bytes to write; only "
		       "[%zd] available\n", __func__, s->max_packet_size,
		       (*reमुख्यing_bytes));
		rc = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	s->skcipher_req = skcipher_request_alloc(s->skcipher_tfm, GFP_KERNEL);
	अगर (!s->skcipher_req) अणु
		prपूर्णांकk(KERN_ERR "%s: Out of kernel memory whilst attempting to "
		       "skcipher_request_alloc for %s\n", __func__,
		       crypto_skcipher_driver_name(s->skcipher_tfm));
		rc = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	skcipher_request_set_callback(s->skcipher_req,
				      CRYPTO_TFM_REQ_MAY_SLEEP, शून्य, शून्य);

	s->block_aligned_filename = kzalloc(s->block_aligned_filename_size,
					    GFP_KERNEL);
	अगर (!s->block_aligned_filename) अणु
		rc = -ENOMEM;
		जाओ out_unlock;
	पूर्ण
	dest[s->i++] = ECRYPTFS_TAG_70_PACKET_TYPE;
	rc = ecryptfs_ग_लिखो_packet_length(&dest[s->i],
					  (ECRYPTFS_SIG_SIZE
					   + 1 /* Cipher code */
					   + s->block_aligned_filename_size),
					  &s->packet_size_len);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "%s: Error generating tag 70 packet "
		       "header; cannot generate packet length; rc = [%d]\n",
		       __func__, rc);
		जाओ out_मुक्त_unlock;
	पूर्ण
	s->i += s->packet_size_len;
	ecryptfs_from_hex(&dest[s->i],
			  mount_crypt_stat->global_शेष_fnek_sig,
			  ECRYPTFS_SIG_SIZE);
	s->i += ECRYPTFS_SIG_SIZE;
	s->cipher_code = ecryptfs_code_क्रम_cipher_string(
		mount_crypt_stat->global_शेष_fn_cipher_name,
		mount_crypt_stat->global_शेष_fn_cipher_key_bytes);
	अगर (s->cipher_code == 0) अणु
		prपूर्णांकk(KERN_WARNING "%s: Unable to generate code for "
		       "cipher [%s] with key bytes [%zd]\n", __func__,
		       mount_crypt_stat->global_शेष_fn_cipher_name,
		       mount_crypt_stat->global_शेष_fn_cipher_key_bytes);
		rc = -EINVAL;
		जाओ out_मुक्त_unlock;
	पूर्ण
	dest[s->i++] = s->cipher_code;
	/* TODO: Support other key modules than passphrase क्रम
	 * filename encryption */
	अगर (s->auth_tok->token_type != ECRYPTFS_PASSWORD) अणु
		rc = -EOPNOTSUPP;
		prपूर्णांकk(KERN_INFO "%s: Filename encryption only supports "
		       "password tokens\n", __func__);
		जाओ out_मुक्त_unlock;
	पूर्ण
	s->hash_tfm = crypto_alloc_shash(ECRYPTFS_TAG_70_DIGEST, 0, 0);
	अगर (IS_ERR(s->hash_tfm)) अणु
			rc = PTR_ERR(s->hash_tfm);
			prपूर्णांकk(KERN_ERR "%s: Error attempting to "
			       "allocate hash crypto context; rc = [%d]\n",
			       __func__, rc);
			जाओ out_मुक्त_unlock;
	पूर्ण

	s->hash_desc = kदो_स्मृति(माप(*s->hash_desc) +
			       crypto_shash_descsize(s->hash_tfm), GFP_KERNEL);
	अगर (!s->hash_desc) अणु
		rc = -ENOMEM;
		जाओ out_release_मुक्त_unlock;
	पूर्ण

	s->hash_desc->tfm = s->hash_tfm;

	rc = crypto_shash_digest(s->hash_desc,
				 (u8 *)s->auth_tok->token.password.session_key_encryption_key,
				 s->auth_tok->token.password.session_key_encryption_key_bytes,
				 s->hash);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR
		       "%s: Error computing crypto hash; rc = [%d]\n",
		       __func__, rc);
		जाओ out_release_मुक्त_unlock;
	पूर्ण
	क्रम (s->j = 0; s->j < (s->num_अक्रम_bytes - 1); s->j++) अणु
		s->block_aligned_filename[s->j] =
			s->hash[(s->j % ECRYPTFS_TAG_70_DIGEST_SIZE)];
		अगर ((s->j % ECRYPTFS_TAG_70_DIGEST_SIZE)
		    == (ECRYPTFS_TAG_70_DIGEST_SIZE - 1)) अणु
			rc = crypto_shash_digest(s->hash_desc, (u8 *)s->hash,
						ECRYPTFS_TAG_70_DIGEST_SIZE,
						s->पंचांगp_hash);
			अगर (rc) अणु
				prपूर्णांकk(KERN_ERR
				       "%s: Error computing crypto hash; "
				       "rc = [%d]\n", __func__, rc);
				जाओ out_release_मुक्त_unlock;
			पूर्ण
			स_नकल(s->hash, s->पंचांगp_hash,
			       ECRYPTFS_TAG_70_DIGEST_SIZE);
		पूर्ण
		अगर (s->block_aligned_filename[s->j] == '\0')
			s->block_aligned_filename[s->j] = ECRYPTFS_NON_शून्य;
	पूर्ण
	स_नकल(&s->block_aligned_filename[s->num_अक्रम_bytes], filename,
	       filename_size);
	rc = virt_to_scatterlist(s->block_aligned_filename,
				 s->block_aligned_filename_size, s->src_sg, 2);
	अगर (rc < 1) अणु
		prपूर्णांकk(KERN_ERR "%s: Internal error whilst attempting to "
		       "convert filename memory to scatterlist; rc = [%d]. "
		       "block_aligned_filename_size = [%zd]\n", __func__, rc,
		       s->block_aligned_filename_size);
		जाओ out_release_मुक्त_unlock;
	पूर्ण
	rc = virt_to_scatterlist(&dest[s->i], s->block_aligned_filename_size,
				 s->dst_sg, 2);
	अगर (rc < 1) अणु
		prपूर्णांकk(KERN_ERR "%s: Internal error whilst attempting to "
		       "convert encrypted filename memory to scatterlist; "
		       "rc = [%d]. block_aligned_filename_size = [%zd]\n",
		       __func__, rc, s->block_aligned_filename_size);
		जाओ out_release_मुक्त_unlock;
	पूर्ण
	/* The अक्षरacters in the first block effectively करो the job
	 * of the IV here, so we just use 0's क्रम the IV. Note the
	 * स्थिरraपूर्णांक that ECRYPTFS_खाताNAME_MIN_RANDOM_PREPEND_BYTES
	 * >= ECRYPTFS_MAX_IV_BYTES. */
	rc = crypto_skcipher_setkey(
		s->skcipher_tfm,
		s->auth_tok->token.password.session_key_encryption_key,
		mount_crypt_stat->global_शेष_fn_cipher_key_bytes);
	अगर (rc < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: Error setting key for crypto context; "
		       "rc = [%d]. s->auth_tok->token.password.session_key_"
		       "encryption_key = [0x%p]; mount_crypt_stat->"
		       "global_default_fn_cipher_key_bytes = [%zd]\n", __func__,
		       rc,
		       s->auth_tok->token.password.session_key_encryption_key,
		       mount_crypt_stat->global_शेष_fn_cipher_key_bytes);
		जाओ out_release_मुक्त_unlock;
	पूर्ण
	skcipher_request_set_crypt(s->skcipher_req, s->src_sg, s->dst_sg,
				   s->block_aligned_filename_size, s->iv);
	rc = crypto_skcipher_encrypt(s->skcipher_req);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "%s: Error attempting to encrypt filename; "
		       "rc = [%d]\n", __func__, rc);
		जाओ out_release_मुक्त_unlock;
	पूर्ण
	s->i += s->block_aligned_filename_size;
	(*packet_size) = s->i;
	(*reमुख्यing_bytes) -= (*packet_size);
out_release_मुक्त_unlock:
	crypto_मुक्त_shash(s->hash_tfm);
out_मुक्त_unlock:
	kमुक्त_sensitive(s->block_aligned_filename);
out_unlock:
	mutex_unlock(s->tfm_mutex);
out:
	अगर (auth_tok_key) अणु
		up_ग_लिखो(&(auth_tok_key->sem));
		key_put(auth_tok_key);
	पूर्ण
	skcipher_request_मुक्त(s->skcipher_req);
	kमुक्त_sensitive(s->hash_desc);
	kमुक्त(s);
	वापस rc;
पूर्ण

काष्ठा ecryptfs_parse_tag_70_packet_silly_stack अणु
	u8 cipher_code;
	माप_प्रकार max_packet_size;
	माप_प्रकार packet_size_len;
	माप_प्रकार parsed_tag_70_packet_size;
	माप_प्रकार block_aligned_filename_size;
	माप_प्रकार block_size;
	माप_प्रकार i;
	काष्ठा mutex *tfm_mutex;
	अक्षर *decrypted_filename;
	काष्ठा ecryptfs_auth_tok *auth_tok;
	काष्ठा scatterlist src_sg[2];
	काष्ठा scatterlist dst_sg[2];
	काष्ठा crypto_skcipher *skcipher_tfm;
	काष्ठा skcipher_request *skcipher_req;
	अक्षर fnek_sig_hex[ECRYPTFS_SIG_SIZE_HEX + 1];
	अक्षर iv[ECRYPTFS_MAX_IV_BYTES];
	अक्षर cipher_string[ECRYPTFS_MAX_CIPHER_NAME_SIZE + 1];
पूर्ण;

/**
 * ecryptfs_parse_tag_70_packet - Parse and process FNEK-encrypted passphrase packet
 * @filename: This function kदो_स्मृति's the memory क्रम the filename
 * @filename_size: This function sets this to the amount of memory
 *                 kदो_स्मृति'd क्रम the filename
 * @packet_size: This function sets this to the the number of octets
 *               in the packet parsed
 * @mount_crypt_stat: The mount-wide cryptographic context
 * @data: The memory location containing the start of the tag 70
 *        packet
 * @max_packet_size: The maximum legal size of the packet to be parsed
 *                   from @data
 *
 * Returns zero on success; non-zero otherwise
 */
पूर्णांक
ecryptfs_parse_tag_70_packet(अक्षर **filename, माप_प्रकार *filename_size,
			     माप_प्रकार *packet_size,
			     काष्ठा ecryptfs_mount_crypt_stat *mount_crypt_stat,
			     अक्षर *data, माप_प्रकार max_packet_size)
अणु
	काष्ठा ecryptfs_parse_tag_70_packet_silly_stack *s;
	काष्ठा key *auth_tok_key = शून्य;
	पूर्णांक rc = 0;

	(*packet_size) = 0;
	(*filename_size) = 0;
	(*filename) = शून्य;
	s = kzalloc(माप(*s), GFP_KERNEL);
	अगर (!s)
		वापस -ENOMEM;

	अगर (max_packet_size < ECRYPTFS_TAG_70_MIN_METADATA_SIZE) अणु
		prपूर्णांकk(KERN_WARNING "%s: max_packet_size is [%zd]; it must be "
		       "at least [%d]\n", __func__, max_packet_size,
		       ECRYPTFS_TAG_70_MIN_METADATA_SIZE);
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	/* Octet 0: Tag 70 identअगरier
	 * Octets 1-N1: Tag 70 packet size (includes cipher identअगरier
	 *              and block-aligned encrypted filename size)
	 * Octets N1-N2: FNEK sig (ECRYPTFS_SIG_SIZE)
	 * Octet N2-N3: Cipher identअगरier (1 octet)
	 * Octets N3-N4: Block-aligned encrypted filename
	 *  - Consists of a minimum number of अक्रमom numbers, a \0
	 *    separator, and then the filename */
	अगर (data[(*packet_size)++] != ECRYPTFS_TAG_70_PACKET_TYPE) अणु
		prपूर्णांकk(KERN_WARNING "%s: Invalid packet tag [0x%.2x]; must be "
		       "tag [0x%.2x]\n", __func__,
		       data[((*packet_size) - 1)], ECRYPTFS_TAG_70_PACKET_TYPE);
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	rc = ecryptfs_parse_packet_length(&data[(*packet_size)],
					  &s->parsed_tag_70_packet_size,
					  &s->packet_size_len);
	अगर (rc) अणु
		prपूर्णांकk(KERN_WARNING "%s: Error parsing packet length; "
		       "rc = [%d]\n", __func__, rc);
		जाओ out;
	पूर्ण
	s->block_aligned_filename_size = (s->parsed_tag_70_packet_size
					  - ECRYPTFS_SIG_SIZE - 1);
	अगर ((1 + s->packet_size_len + s->parsed_tag_70_packet_size)
	    > max_packet_size) अणु
		prपूर्णांकk(KERN_WARNING "%s: max_packet_size is [%zd]; real packet "
		       "size is [%zd]\n", __func__, max_packet_size,
		       (1 + s->packet_size_len + 1
			+ s->block_aligned_filename_size));
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	(*packet_size) += s->packet_size_len;
	ecryptfs_to_hex(s->fnek_sig_hex, &data[(*packet_size)],
			ECRYPTFS_SIG_SIZE);
	s->fnek_sig_hex[ECRYPTFS_SIG_SIZE_HEX] = '\0';
	(*packet_size) += ECRYPTFS_SIG_SIZE;
	s->cipher_code = data[(*packet_size)++];
	rc = ecryptfs_cipher_code_to_string(s->cipher_string, s->cipher_code);
	अगर (rc) अणु
		prपूर्णांकk(KERN_WARNING "%s: Cipher code [%d] is invalid\n",
		       __func__, s->cipher_code);
		जाओ out;
	पूर्ण
	rc = ecryptfs_find_auth_tok_क्रम_sig(&auth_tok_key,
					    &s->auth_tok, mount_crypt_stat,
					    s->fnek_sig_hex);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "%s: Error attempting to find auth tok for "
		       "fnek sig [%s]; rc = [%d]\n", __func__, s->fnek_sig_hex,
		       rc);
		जाओ out;
	पूर्ण
	rc = ecryptfs_get_tfm_and_mutex_क्रम_cipher_name(&s->skcipher_tfm,
							&s->tfm_mutex,
							s->cipher_string);
	अगर (unlikely(rc)) अणु
		prपूर्णांकk(KERN_ERR "Internal error whilst attempting to get "
		       "tfm and mutex for cipher name [%s]; rc = [%d]\n",
		       s->cipher_string, rc);
		जाओ out;
	पूर्ण
	mutex_lock(s->tfm_mutex);
	rc = virt_to_scatterlist(&data[(*packet_size)],
				 s->block_aligned_filename_size, s->src_sg, 2);
	अगर (rc < 1) अणु
		prपूर्णांकk(KERN_ERR "%s: Internal error whilst attempting to "
		       "convert encrypted filename memory to scatterlist; "
		       "rc = [%d]. block_aligned_filename_size = [%zd]\n",
		       __func__, rc, s->block_aligned_filename_size);
		जाओ out_unlock;
	पूर्ण
	(*packet_size) += s->block_aligned_filename_size;
	s->decrypted_filename = kदो_स्मृति(s->block_aligned_filename_size,
					GFP_KERNEL);
	अगर (!s->decrypted_filename) अणु
		rc = -ENOMEM;
		जाओ out_unlock;
	पूर्ण
	rc = virt_to_scatterlist(s->decrypted_filename,
				 s->block_aligned_filename_size, s->dst_sg, 2);
	अगर (rc < 1) अणु
		prपूर्णांकk(KERN_ERR "%s: Internal error whilst attempting to "
		       "convert decrypted filename memory to scatterlist; "
		       "rc = [%d]. block_aligned_filename_size = [%zd]\n",
		       __func__, rc, s->block_aligned_filename_size);
		जाओ out_मुक्त_unlock;
	पूर्ण

	s->skcipher_req = skcipher_request_alloc(s->skcipher_tfm, GFP_KERNEL);
	अगर (!s->skcipher_req) अणु
		prपूर्णांकk(KERN_ERR "%s: Out of kernel memory whilst attempting to "
		       "skcipher_request_alloc for %s\n", __func__,
		       crypto_skcipher_driver_name(s->skcipher_tfm));
		rc = -ENOMEM;
		जाओ out_मुक्त_unlock;
	पूर्ण

	skcipher_request_set_callback(s->skcipher_req,
				      CRYPTO_TFM_REQ_MAY_SLEEP, शून्य, शून्य);

	/* The अक्षरacters in the first block effectively करो the job of
	 * the IV here, so we just use 0's क्रम the IV. Note the
	 * स्थिरraपूर्णांक that ECRYPTFS_खाताNAME_MIN_RANDOM_PREPEND_BYTES
	 * >= ECRYPTFS_MAX_IV_BYTES. */
	/* TODO: Support other key modules than passphrase क्रम
	 * filename encryption */
	अगर (s->auth_tok->token_type != ECRYPTFS_PASSWORD) अणु
		rc = -EOPNOTSUPP;
		prपूर्णांकk(KERN_INFO "%s: Filename encryption only supports "
		       "password tokens\n", __func__);
		जाओ out_मुक्त_unlock;
	पूर्ण
	rc = crypto_skcipher_setkey(
		s->skcipher_tfm,
		s->auth_tok->token.password.session_key_encryption_key,
		mount_crypt_stat->global_शेष_fn_cipher_key_bytes);
	अगर (rc < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: Error setting key for crypto context; "
		       "rc = [%d]. s->auth_tok->token.password.session_key_"
		       "encryption_key = [0x%p]; mount_crypt_stat->"
		       "global_default_fn_cipher_key_bytes = [%zd]\n", __func__,
		       rc,
		       s->auth_tok->token.password.session_key_encryption_key,
		       mount_crypt_stat->global_शेष_fn_cipher_key_bytes);
		जाओ out_मुक्त_unlock;
	पूर्ण
	skcipher_request_set_crypt(s->skcipher_req, s->src_sg, s->dst_sg,
				   s->block_aligned_filename_size, s->iv);
	rc = crypto_skcipher_decrypt(s->skcipher_req);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "%s: Error attempting to decrypt filename; "
		       "rc = [%d]\n", __func__, rc);
		जाओ out_मुक्त_unlock;
	पूर्ण

	जबतक (s->i < s->block_aligned_filename_size &&
	       s->decrypted_filename[s->i] != '\0')
		s->i++;
	अगर (s->i == s->block_aligned_filename_size) अणु
		prपूर्णांकk(KERN_WARNING "%s: Invalid tag 70 packet; could not "
		       "find valid separator between random characters and "
		       "the filename\n", __func__);
		rc = -EINVAL;
		जाओ out_मुक्त_unlock;
	पूर्ण
	s->i++;
	(*filename_size) = (s->block_aligned_filename_size - s->i);
	अगर (!((*filename_size) > 0 && (*filename_size < PATH_MAX))) अणु
		prपूर्णांकk(KERN_WARNING "%s: Filename size is [%zd], which is "
		       "invalid\n", __func__, (*filename_size));
		rc = -EINVAL;
		जाओ out_मुक्त_unlock;
	पूर्ण
	(*filename) = kदो_स्मृति(((*filename_size) + 1), GFP_KERNEL);
	अगर (!(*filename)) अणु
		rc = -ENOMEM;
		जाओ out_मुक्त_unlock;
	पूर्ण
	स_नकल((*filename), &s->decrypted_filename[s->i], (*filename_size));
	(*filename)[(*filename_size)] = '\0';
out_मुक्त_unlock:
	kमुक्त(s->decrypted_filename);
out_unlock:
	mutex_unlock(s->tfm_mutex);
out:
	अगर (rc) अणु
		(*packet_size) = 0;
		(*filename_size) = 0;
		(*filename) = शून्य;
	पूर्ण
	अगर (auth_tok_key) अणु
		up_ग_लिखो(&(auth_tok_key->sem));
		key_put(auth_tok_key);
	पूर्ण
	skcipher_request_मुक्त(s->skcipher_req);
	kमुक्त(s);
	वापस rc;
पूर्ण

अटल पूर्णांक
ecryptfs_get_auth_tok_sig(अक्षर **sig, काष्ठा ecryptfs_auth_tok *auth_tok)
अणु
	पूर्णांक rc = 0;

	(*sig) = शून्य;
	चयन (auth_tok->token_type) अणु
	हाल ECRYPTFS_PASSWORD:
		(*sig) = auth_tok->token.password.signature;
		अवरोध;
	हाल ECRYPTFS_PRIVATE_KEY:
		(*sig) = auth_tok->token.निजी_key.signature;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "Cannot get sig for auth_tok of type [%d]\n",
		       auth_tok->token_type);
		rc = -EINVAL;
	पूर्ण
	वापस rc;
पूर्ण

/**
 * decrypt_pki_encrypted_session_key - Decrypt the session key with the given auth_tok.
 * @auth_tok: The key authentication token used to decrypt the session key
 * @crypt_stat: The cryptographic context
 *
 * Returns zero on success; non-zero error otherwise.
 */
अटल पूर्णांक
decrypt_pki_encrypted_session_key(काष्ठा ecryptfs_auth_tok *auth_tok,
				  काष्ठा ecryptfs_crypt_stat *crypt_stat)
अणु
	u8 cipher_code = 0;
	काष्ठा ecryptfs_msg_ctx *msg_ctx;
	काष्ठा ecryptfs_message *msg = शून्य;
	अक्षर *auth_tok_sig;
	अक्षर *payload = शून्य;
	माप_प्रकार payload_len = 0;
	पूर्णांक rc;

	rc = ecryptfs_get_auth_tok_sig(&auth_tok_sig, auth_tok);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "Unrecognized auth tok type: [%d]\n",
		       auth_tok->token_type);
		जाओ out;
	पूर्ण
	rc = ग_लिखो_tag_64_packet(auth_tok_sig, &(auth_tok->session_key),
				 &payload, &payload_len);
	अगर (rc) अणु
		ecryptfs_prपूर्णांकk(KERN_ERR, "Failed to write tag 64 packet\n");
		जाओ out;
	पूर्ण
	rc = ecryptfs_send_message(payload, payload_len, &msg_ctx);
	अगर (rc) अणु
		ecryptfs_prपूर्णांकk(KERN_ERR, "Error sending message to "
				"ecryptfsd: %d\n", rc);
		जाओ out;
	पूर्ण
	rc = ecryptfs_रुको_क्रम_response(msg_ctx, &msg);
	अगर (rc) अणु
		ecryptfs_prपूर्णांकk(KERN_ERR, "Failed to receive tag 65 packet "
				"from the user space daemon\n");
		rc = -EIO;
		जाओ out;
	पूर्ण
	rc = parse_tag_65_packet(&(auth_tok->session_key),
				 &cipher_code, msg);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "Failed to parse tag 65 packet; rc = [%d]\n",
		       rc);
		जाओ out;
	पूर्ण
	auth_tok->session_key.flags |= ECRYPTFS_CONTAINS_DECRYPTED_KEY;
	स_नकल(crypt_stat->key, auth_tok->session_key.decrypted_key,
	       auth_tok->session_key.decrypted_key_size);
	crypt_stat->key_size = auth_tok->session_key.decrypted_key_size;
	rc = ecryptfs_cipher_code_to_string(crypt_stat->cipher, cipher_code);
	अगर (rc) अणु
		ecryptfs_prपूर्णांकk(KERN_ERR, "Cipher code [%d] is invalid\n",
				cipher_code);
		जाओ out;
	पूर्ण
	crypt_stat->flags |= ECRYPTFS_KEY_VALID;
	अगर (ecryptfs_verbosity > 0) अणु
		ecryptfs_prपूर्णांकk(KERN_DEBUG, "Decrypted session key:\n");
		ecryptfs_dump_hex(crypt_stat->key,
				  crypt_stat->key_size);
	पूर्ण
out:
	kमुक्त(msg);
	kमुक्त(payload);
	वापस rc;
पूर्ण

अटल व्योम wipe_auth_tok_list(काष्ठा list_head *auth_tok_list_head)
अणु
	काष्ठा ecryptfs_auth_tok_list_item *auth_tok_list_item;
	काष्ठा ecryptfs_auth_tok_list_item *auth_tok_list_item_पंचांगp;

	list_क्रम_each_entry_safe(auth_tok_list_item, auth_tok_list_item_पंचांगp,
				 auth_tok_list_head, list) अणु
		list_del(&auth_tok_list_item->list);
		kmem_cache_मुक्त(ecryptfs_auth_tok_list_item_cache,
				auth_tok_list_item);
	पूर्ण
पूर्ण

काष्ठा kmem_cache *ecryptfs_auth_tok_list_item_cache;

/**
 * parse_tag_1_packet
 * @crypt_stat: The cryptographic context to modअगरy based on packet contents
 * @data: The raw bytes of the packet.
 * @auth_tok_list: eCryptfs parses packets पूर्णांकo authentication tokens;
 *                 a new authentication token will be placed at the
 *                 end of this list क्रम this packet.
 * @new_auth_tok: Poपूर्णांकer to a poपूर्णांकer to memory that this function
 *                allocates; sets the memory address of the poपूर्णांकer to
 *                शून्य on error. This object is added to the
 *                auth_tok_list.
 * @packet_size: This function ग_लिखोs the size of the parsed packet
 *               पूर्णांकo this memory location; zero on error.
 * @max_packet_size: The maximum allowable packet size
 *
 * Returns zero on success; non-zero on error.
 */
अटल पूर्णांक
parse_tag_1_packet(काष्ठा ecryptfs_crypt_stat *crypt_stat,
		   अचिन्हित अक्षर *data, काष्ठा list_head *auth_tok_list,
		   काष्ठा ecryptfs_auth_tok **new_auth_tok,
		   माप_प्रकार *packet_size, माप_प्रकार max_packet_size)
अणु
	माप_प्रकार body_size;
	काष्ठा ecryptfs_auth_tok_list_item *auth_tok_list_item;
	माप_प्रकार length_size;
	पूर्णांक rc = 0;

	(*packet_size) = 0;
	(*new_auth_tok) = शून्य;
	/**
	 * This क्रमmat is inspired by OpenPGP; see RFC 2440
	 * packet tag 1
	 *
	 * Tag 1 identअगरier (1 byte)
	 * Max Tag 1 packet size (max 3 bytes)
	 * Version (1 byte)
	 * Key identअगरier (8 bytes; ECRYPTFS_SIG_SIZE)
	 * Cipher identअगरier (1 byte)
	 * Encrypted key size (arbitrary)
	 *
	 * 12 bytes minimum packet size
	 */
	अगर (unlikely(max_packet_size < 12)) अणु
		prपूर्णांकk(KERN_ERR "Invalid max packet size; must be >=12\n");
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	अगर (data[(*packet_size)++] != ECRYPTFS_TAG_1_PACKET_TYPE) अणु
		prपूर्णांकk(KERN_ERR "Enter w/ first byte != 0x%.2x\n",
		       ECRYPTFS_TAG_1_PACKET_TYPE);
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	/* Released: wipe_auth_tok_list called in ecryptfs_parse_packet_set or
	 * at end of function upon failure */
	auth_tok_list_item =
		kmem_cache_zalloc(ecryptfs_auth_tok_list_item_cache,
				  GFP_KERNEL);
	अगर (!auth_tok_list_item) अणु
		prपूर्णांकk(KERN_ERR "Unable to allocate memory\n");
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	(*new_auth_tok) = &auth_tok_list_item->auth_tok;
	rc = ecryptfs_parse_packet_length(&data[(*packet_size)], &body_size,
					  &length_size);
	अगर (rc) अणु
		prपूर्णांकk(KERN_WARNING "Error parsing packet length; "
		       "rc = [%d]\n", rc);
		जाओ out_मुक्त;
	पूर्ण
	अगर (unlikely(body_size < (ECRYPTFS_SIG_SIZE + 2))) अणु
		prपूर्णांकk(KERN_WARNING "Invalid body size ([%td])\n", body_size);
		rc = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण
	(*packet_size) += length_size;
	अगर (unlikely((*packet_size) + body_size > max_packet_size)) अणु
		prपूर्णांकk(KERN_WARNING "Packet size exceeds max\n");
		rc = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण
	अगर (unlikely(data[(*packet_size)++] != 0x03)) अणु
		prपूर्णांकk(KERN_WARNING "Unknown version number [%d]\n",
		       data[(*packet_size) - 1]);
		rc = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण
	ecryptfs_to_hex((*new_auth_tok)->token.निजी_key.signature,
			&data[(*packet_size)], ECRYPTFS_SIG_SIZE);
	*packet_size += ECRYPTFS_SIG_SIZE;
	/* This byte is skipped because the kernel करोes not need to
	 * know which खुला key encryption algorithm was used */
	(*packet_size)++;
	(*new_auth_tok)->session_key.encrypted_key_size =
		body_size - (ECRYPTFS_SIG_SIZE + 2);
	अगर ((*new_auth_tok)->session_key.encrypted_key_size
	    > ECRYPTFS_MAX_ENCRYPTED_KEY_BYTES) अणु
		prपूर्णांकk(KERN_WARNING "Tag 1 packet contains key larger "
		       "than ECRYPTFS_MAX_ENCRYPTED_KEY_BYTES\n");
		rc = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण
	स_नकल((*new_auth_tok)->session_key.encrypted_key,
	       &data[(*packet_size)], (body_size - (ECRYPTFS_SIG_SIZE + 2)));
	(*packet_size) += (*new_auth_tok)->session_key.encrypted_key_size;
	(*new_auth_tok)->session_key.flags &=
		~ECRYPTFS_CONTAINS_DECRYPTED_KEY;
	(*new_auth_tok)->session_key.flags |=
		ECRYPTFS_CONTAINS_ENCRYPTED_KEY;
	(*new_auth_tok)->token_type = ECRYPTFS_PRIVATE_KEY;
	(*new_auth_tok)->flags = 0;
	(*new_auth_tok)->session_key.flags &=
		~(ECRYPTFS_USERSPACE_SHOULD_TRY_TO_DECRYPT);
	(*new_auth_tok)->session_key.flags &=
		~(ECRYPTFS_USERSPACE_SHOULD_TRY_TO_ENCRYPT);
	list_add(&auth_tok_list_item->list, auth_tok_list);
	जाओ out;
out_मुक्त:
	(*new_auth_tok) = शून्य;
	स_रखो(auth_tok_list_item, 0,
	       माप(काष्ठा ecryptfs_auth_tok_list_item));
	kmem_cache_मुक्त(ecryptfs_auth_tok_list_item_cache,
			auth_tok_list_item);
out:
	अगर (rc)
		(*packet_size) = 0;
	वापस rc;
पूर्ण

/**
 * parse_tag_3_packet
 * @crypt_stat: The cryptographic context to modअगरy based on packet
 *              contents.
 * @data: The raw bytes of the packet.
 * @auth_tok_list: eCryptfs parses packets पूर्णांकo authentication tokens;
 *                 a new authentication token will be placed at the end
 *                 of this list क्रम this packet.
 * @new_auth_tok: Poपूर्णांकer to a poपूर्णांकer to memory that this function
 *                allocates; sets the memory address of the poपूर्णांकer to
 *                शून्य on error. This object is added to the
 *                auth_tok_list.
 * @packet_size: This function ग_लिखोs the size of the parsed packet
 *               पूर्णांकo this memory location; zero on error.
 * @max_packet_size: maximum number of bytes to parse
 *
 * Returns zero on success; non-zero on error.
 */
अटल पूर्णांक
parse_tag_3_packet(काष्ठा ecryptfs_crypt_stat *crypt_stat,
		   अचिन्हित अक्षर *data, काष्ठा list_head *auth_tok_list,
		   काष्ठा ecryptfs_auth_tok **new_auth_tok,
		   माप_प्रकार *packet_size, माप_प्रकार max_packet_size)
अणु
	माप_प्रकार body_size;
	काष्ठा ecryptfs_auth_tok_list_item *auth_tok_list_item;
	माप_प्रकार length_size;
	पूर्णांक rc = 0;

	(*packet_size) = 0;
	(*new_auth_tok) = शून्य;
	/**
	 *This क्रमmat is inspired by OpenPGP; see RFC 2440
	 * packet tag 3
	 *
	 * Tag 3 identअगरier (1 byte)
	 * Max Tag 3 packet size (max 3 bytes)
	 * Version (1 byte)
	 * Cipher code (1 byte)
	 * S2K specअगरier (1 byte)
	 * Hash identअगरier (1 byte)
	 * Salt (ECRYPTFS_SALT_SIZE)
	 * Hash iterations (1 byte)
	 * Encrypted key (arbitrary)
	 *
	 * (ECRYPTFS_SALT_SIZE + 7) minimum packet size
	 */
	अगर (max_packet_size < (ECRYPTFS_SALT_SIZE + 7)) अणु
		prपूर्णांकk(KERN_ERR "Max packet size too large\n");
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	अगर (data[(*packet_size)++] != ECRYPTFS_TAG_3_PACKET_TYPE) अणु
		prपूर्णांकk(KERN_ERR "First byte != 0x%.2x; invalid packet\n",
		       ECRYPTFS_TAG_3_PACKET_TYPE);
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	/* Released: wipe_auth_tok_list called in ecryptfs_parse_packet_set or
	 * at end of function upon failure */
	auth_tok_list_item =
	    kmem_cache_zalloc(ecryptfs_auth_tok_list_item_cache, GFP_KERNEL);
	अगर (!auth_tok_list_item) अणु
		prपूर्णांकk(KERN_ERR "Unable to allocate memory\n");
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	(*new_auth_tok) = &auth_tok_list_item->auth_tok;
	rc = ecryptfs_parse_packet_length(&data[(*packet_size)], &body_size,
					  &length_size);
	अगर (rc) अणु
		prपूर्णांकk(KERN_WARNING "Error parsing packet length; rc = [%d]\n",
		       rc);
		जाओ out_मुक्त;
	पूर्ण
	अगर (unlikely(body_size < (ECRYPTFS_SALT_SIZE + 5))) अणु
		prपूर्णांकk(KERN_WARNING "Invalid body size ([%td])\n", body_size);
		rc = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण
	(*packet_size) += length_size;
	अगर (unlikely((*packet_size) + body_size > max_packet_size)) अणु
		prपूर्णांकk(KERN_ERR "Packet size exceeds max\n");
		rc = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण
	(*new_auth_tok)->session_key.encrypted_key_size =
		(body_size - (ECRYPTFS_SALT_SIZE + 5));
	अगर ((*new_auth_tok)->session_key.encrypted_key_size
	    > ECRYPTFS_MAX_ENCRYPTED_KEY_BYTES) अणु
		prपूर्णांकk(KERN_WARNING "Tag 3 packet contains key larger "
		       "than ECRYPTFS_MAX_ENCRYPTED_KEY_BYTES\n");
		rc = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण
	अगर (unlikely(data[(*packet_size)++] != 0x04)) अणु
		prपूर्णांकk(KERN_WARNING "Unknown version number [%d]\n",
		       data[(*packet_size) - 1]);
		rc = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण
	rc = ecryptfs_cipher_code_to_string(crypt_stat->cipher,
					    (u16)data[(*packet_size)]);
	अगर (rc)
		जाओ out_मुक्त;
	/* A little extra work to dअगरferentiate among the AES key
	 * sizes; see RFC2440 */
	चयन(data[(*packet_size)++]) अणु
	हाल RFC2440_CIPHER_AES_192:
		crypt_stat->key_size = 24;
		अवरोध;
	शेष:
		crypt_stat->key_size =
			(*new_auth_tok)->session_key.encrypted_key_size;
	पूर्ण
	rc = ecryptfs_init_crypt_ctx(crypt_stat);
	अगर (rc)
		जाओ out_मुक्त;
	अगर (unlikely(data[(*packet_size)++] != 0x03)) अणु
		prपूर्णांकk(KERN_WARNING "Only S2K ID 3 is currently supported\n");
		rc = -ENOSYS;
		जाओ out_मुक्त;
	पूर्ण
	/* TODO: finish the hash mapping */
	चयन (data[(*packet_size)++]) अणु
	हाल 0x01: /* See RFC2440 क्रम these numbers and their mappings */
		/* Choose MD5 */
		स_नकल((*new_auth_tok)->token.password.salt,
		       &data[(*packet_size)], ECRYPTFS_SALT_SIZE);
		(*packet_size) += ECRYPTFS_SALT_SIZE;
		/* This conversion was taken straight from RFC2440 */
		(*new_auth_tok)->token.password.hash_iterations =
			((u32) 16 + (data[(*packet_size)] & 15))
				<< ((data[(*packet_size)] >> 4) + 6);
		(*packet_size)++;
		/* Friendly reminder:
		 * (*new_auth_tok)->session_key.encrypted_key_size =
		 *         (body_size - (ECRYPTFS_SALT_SIZE + 5)); */
		स_नकल((*new_auth_tok)->session_key.encrypted_key,
		       &data[(*packet_size)],
		       (*new_auth_tok)->session_key.encrypted_key_size);
		(*packet_size) +=
			(*new_auth_tok)->session_key.encrypted_key_size;
		(*new_auth_tok)->session_key.flags &=
			~ECRYPTFS_CONTAINS_DECRYPTED_KEY;
		(*new_auth_tok)->session_key.flags |=
			ECRYPTFS_CONTAINS_ENCRYPTED_KEY;
		(*new_auth_tok)->token.password.hash_algo = 0x01; /* MD5 */
		अवरोध;
	शेष:
		ecryptfs_prपूर्णांकk(KERN_ERR, "Unsupported hash algorithm: "
				"[%d]\n", data[(*packet_size) - 1]);
		rc = -ENOSYS;
		जाओ out_मुक्त;
	पूर्ण
	(*new_auth_tok)->token_type = ECRYPTFS_PASSWORD;
	/* TODO: Parametarize; we might actually want userspace to
	 * decrypt the session key. */
	(*new_auth_tok)->session_key.flags &=
			    ~(ECRYPTFS_USERSPACE_SHOULD_TRY_TO_DECRYPT);
	(*new_auth_tok)->session_key.flags &=
			    ~(ECRYPTFS_USERSPACE_SHOULD_TRY_TO_ENCRYPT);
	list_add(&auth_tok_list_item->list, auth_tok_list);
	जाओ out;
out_मुक्त:
	(*new_auth_tok) = शून्य;
	स_रखो(auth_tok_list_item, 0,
	       माप(काष्ठा ecryptfs_auth_tok_list_item));
	kmem_cache_मुक्त(ecryptfs_auth_tok_list_item_cache,
			auth_tok_list_item);
out:
	अगर (rc)
		(*packet_size) = 0;
	वापस rc;
पूर्ण

/**
 * parse_tag_11_packet
 * @data: The raw bytes of the packet
 * @contents: This function ग_लिखोs the data contents of the literal
 *            packet पूर्णांकo this memory location
 * @max_contents_bytes: The maximum number of bytes that this function
 *                      is allowed to ग_लिखो पूर्णांकo contents
 * @tag_11_contents_size: This function ग_लिखोs the size of the parsed
 *                        contents पूर्णांकo this memory location; zero on
 *                        error
 * @packet_size: This function ग_लिखोs the size of the parsed packet
 *               पूर्णांकo this memory location; zero on error
 * @max_packet_size: maximum number of bytes to parse
 *
 * Returns zero on success; non-zero on error.
 */
अटल पूर्णांक
parse_tag_11_packet(अचिन्हित अक्षर *data, अचिन्हित अक्षर *contents,
		    माप_प्रकार max_contents_bytes, माप_प्रकार *tag_11_contents_size,
		    माप_प्रकार *packet_size, माप_प्रकार max_packet_size)
अणु
	माप_प्रकार body_size;
	माप_प्रकार length_size;
	पूर्णांक rc = 0;

	(*packet_size) = 0;
	(*tag_11_contents_size) = 0;
	/* This क्रमmat is inspired by OpenPGP; see RFC 2440
	 * packet tag 11
	 *
	 * Tag 11 identअगरier (1 byte)
	 * Max Tag 11 packet size (max 3 bytes)
	 * Binary क्रमmat specअगरier (1 byte)
	 * Filename length (1 byte)
	 * Filename ("_CONSOLE") (8 bytes)
	 * Modअगरication date (4 bytes)
	 * Literal data (arbitrary)
	 *
	 * We need at least 16 bytes of data क्रम the packet to even be
	 * valid.
	 */
	अगर (max_packet_size < 16) अणु
		prपूर्णांकk(KERN_ERR "Maximum packet size too small\n");
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	अगर (data[(*packet_size)++] != ECRYPTFS_TAG_11_PACKET_TYPE) अणु
		prपूर्णांकk(KERN_WARNING "Invalid tag 11 packet format\n");
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	rc = ecryptfs_parse_packet_length(&data[(*packet_size)], &body_size,
					  &length_size);
	अगर (rc) अणु
		prपूर्णांकk(KERN_WARNING "Invalid tag 11 packet format\n");
		जाओ out;
	पूर्ण
	अगर (body_size < 14) अणु
		prपूर्णांकk(KERN_WARNING "Invalid body size ([%td])\n", body_size);
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	(*packet_size) += length_size;
	(*tag_11_contents_size) = (body_size - 14);
	अगर (unlikely((*packet_size) + body_size + 1 > max_packet_size)) अणु
		prपूर्णांकk(KERN_ERR "Packet size exceeds max\n");
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	अगर (unlikely((*tag_11_contents_size) > max_contents_bytes)) अणु
		prपूर्णांकk(KERN_ERR "Literal data section in tag 11 packet exceeds "
		       "expected size\n");
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	अगर (data[(*packet_size)++] != 0x62) अणु
		prपूर्णांकk(KERN_WARNING "Unrecognizable packet\n");
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	अगर (data[(*packet_size)++] != 0x08) अणु
		prपूर्णांकk(KERN_WARNING "Unrecognizable packet\n");
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	(*packet_size) += 12; /* Ignore filename and modअगरication date */
	स_नकल(contents, &data[(*packet_size)], (*tag_11_contents_size));
	(*packet_size) += (*tag_11_contents_size);
out:
	अगर (rc) अणु
		(*packet_size) = 0;
		(*tag_11_contents_size) = 0;
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक ecryptfs_keyring_auth_tok_क्रम_sig(काष्ठा key **auth_tok_key,
				      काष्ठा ecryptfs_auth_tok **auth_tok,
				      अक्षर *sig)
अणु
	पूर्णांक rc = 0;

	(*auth_tok_key) = request_key(&key_type_user, sig, शून्य);
	अगर (IS_ERR(*auth_tok_key)) अणु
		(*auth_tok_key) = ecryptfs_get_encrypted_key(sig);
		अगर (IS_ERR(*auth_tok_key)) अणु
			prपूर्णांकk(KERN_ERR "Could not find key with description: [%s]\n",
			      sig);
			rc = process_request_key_err(PTR_ERR(*auth_tok_key));
			(*auth_tok_key) = शून्य;
			जाओ out;
		पूर्ण
	पूर्ण
	करोwn_ग_लिखो(&(*auth_tok_key)->sem);
	rc = ecryptfs_verअगरy_auth_tok_from_key(*auth_tok_key, auth_tok);
	अगर (rc) अणु
		up_ग_लिखो(&(*auth_tok_key)->sem);
		key_put(*auth_tok_key);
		(*auth_tok_key) = शून्य;
		जाओ out;
	पूर्ण
out:
	वापस rc;
पूर्ण

/**
 * decrypt_passphrase_encrypted_session_key - Decrypt the session key with the given auth_tok.
 * @auth_tok: The passphrase authentication token to use to encrypt the FEK
 * @crypt_stat: The cryptographic context
 *
 * Returns zero on success; non-zero error otherwise
 */
अटल पूर्णांक
decrypt_passphrase_encrypted_session_key(काष्ठा ecryptfs_auth_tok *auth_tok,
					 काष्ठा ecryptfs_crypt_stat *crypt_stat)
अणु
	काष्ठा scatterlist dst_sg[2];
	काष्ठा scatterlist src_sg[2];
	काष्ठा mutex *tfm_mutex;
	काष्ठा crypto_skcipher *tfm;
	काष्ठा skcipher_request *req = शून्य;
	पूर्णांक rc = 0;

	अगर (unlikely(ecryptfs_verbosity > 0)) अणु
		ecryptfs_prपूर्णांकk(
			KERN_DEBUG, "Session key encryption key (size [%d]):\n",
			auth_tok->token.password.session_key_encryption_key_bytes);
		ecryptfs_dump_hex(
			auth_tok->token.password.session_key_encryption_key,
			auth_tok->token.password.session_key_encryption_key_bytes);
	पूर्ण
	rc = ecryptfs_get_tfm_and_mutex_क्रम_cipher_name(&tfm, &tfm_mutex,
							crypt_stat->cipher);
	अगर (unlikely(rc)) अणु
		prपूर्णांकk(KERN_ERR "Internal error whilst attempting to get "
		       "tfm and mutex for cipher name [%s]; rc = [%d]\n",
		       crypt_stat->cipher, rc);
		जाओ out;
	पूर्ण
	rc = virt_to_scatterlist(auth_tok->session_key.encrypted_key,
				 auth_tok->session_key.encrypted_key_size,
				 src_sg, 2);
	अगर (rc < 1 || rc > 2) अणु
		prपूर्णांकk(KERN_ERR "Internal error whilst attempting to convert "
			"auth_tok->session_key.encrypted_key to scatterlist; "
			"expected rc = 1; got rc = [%d]. "
		       "auth_tok->session_key.encrypted_key_size = [%d]\n", rc,
			auth_tok->session_key.encrypted_key_size);
		जाओ out;
	पूर्ण
	auth_tok->session_key.decrypted_key_size =
		auth_tok->session_key.encrypted_key_size;
	rc = virt_to_scatterlist(auth_tok->session_key.decrypted_key,
				 auth_tok->session_key.decrypted_key_size,
				 dst_sg, 2);
	अगर (rc < 1 || rc > 2) अणु
		prपूर्णांकk(KERN_ERR "Internal error whilst attempting to convert "
			"auth_tok->session_key.decrypted_key to scatterlist; "
			"expected rc = 1; got rc = [%d]\n", rc);
		जाओ out;
	पूर्ण
	mutex_lock(tfm_mutex);
	req = skcipher_request_alloc(tfm, GFP_KERNEL);
	अगर (!req) अणु
		mutex_unlock(tfm_mutex);
		prपूर्णांकk(KERN_ERR "%s: Out of kernel memory whilst attempting to "
		       "skcipher_request_alloc for %s\n", __func__,
		       crypto_skcipher_driver_name(tfm));
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	skcipher_request_set_callback(req, CRYPTO_TFM_REQ_MAY_SLEEP,
				      शून्य, शून्य);
	rc = crypto_skcipher_setkey(
		tfm, auth_tok->token.password.session_key_encryption_key,
		crypt_stat->key_size);
	अगर (unlikely(rc < 0)) अणु
		mutex_unlock(tfm_mutex);
		prपूर्णांकk(KERN_ERR "Error setting key for crypto context\n");
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	skcipher_request_set_crypt(req, src_sg, dst_sg,
				   auth_tok->session_key.encrypted_key_size,
				   शून्य);
	rc = crypto_skcipher_decrypt(req);
	mutex_unlock(tfm_mutex);
	अगर (unlikely(rc)) अणु
		prपूर्णांकk(KERN_ERR "Error decrypting; rc = [%d]\n", rc);
		जाओ out;
	पूर्ण
	auth_tok->session_key.flags |= ECRYPTFS_CONTAINS_DECRYPTED_KEY;
	स_नकल(crypt_stat->key, auth_tok->session_key.decrypted_key,
	       auth_tok->session_key.decrypted_key_size);
	crypt_stat->flags |= ECRYPTFS_KEY_VALID;
	अगर (unlikely(ecryptfs_verbosity > 0)) अणु
		ecryptfs_prपूर्णांकk(KERN_DEBUG, "FEK of size [%zd]:\n",
				crypt_stat->key_size);
		ecryptfs_dump_hex(crypt_stat->key,
				  crypt_stat->key_size);
	पूर्ण
out:
	skcipher_request_मुक्त(req);
	वापस rc;
पूर्ण

/**
 * ecryptfs_parse_packet_set
 * @crypt_stat: The cryptographic context
 * @src: Virtual address of region of memory containing the packets
 * @ecryptfs_dentry: The eCryptfs dentry associated with the packet set
 *
 * Get crypt_stat to have the file's session key अगर the requisite key
 * is available to decrypt the session key.
 *
 * Returns Zero अगर a valid authentication token was retrieved and
 * processed; negative value क्रम file not encrypted or क्रम error
 * conditions.
 */
पूर्णांक ecryptfs_parse_packet_set(काष्ठा ecryptfs_crypt_stat *crypt_stat,
			      अचिन्हित अक्षर *src,
			      काष्ठा dentry *ecryptfs_dentry)
अणु
	माप_प्रकार i = 0;
	माप_प्रकार found_auth_tok;
	माप_प्रकार next_packet_is_auth_tok_packet;
	काष्ठा list_head auth_tok_list;
	काष्ठा ecryptfs_auth_tok *matching_auth_tok;
	काष्ठा ecryptfs_auth_tok *candidate_auth_tok;
	अक्षर *candidate_auth_tok_sig;
	माप_प्रकार packet_size;
	काष्ठा ecryptfs_auth_tok *new_auth_tok;
	अचिन्हित अक्षर sig_पंचांगp_space[ECRYPTFS_SIG_SIZE];
	काष्ठा ecryptfs_auth_tok_list_item *auth_tok_list_item;
	माप_प्रकार tag_11_contents_size;
	माप_प्रकार tag_11_packet_size;
	काष्ठा key *auth_tok_key = शून्य;
	पूर्णांक rc = 0;

	INIT_LIST_HEAD(&auth_tok_list);
	/* Parse the header to find as many packets as we can; these will be
	 * added the our &auth_tok_list */
	next_packet_is_auth_tok_packet = 1;
	जबतक (next_packet_is_auth_tok_packet) अणु
		माप_प्रकार max_packet_size = ((PAGE_SIZE - 8) - i);

		चयन (src[i]) अणु
		हाल ECRYPTFS_TAG_3_PACKET_TYPE:
			rc = parse_tag_3_packet(crypt_stat,
						(अचिन्हित अक्षर *)&src[i],
						&auth_tok_list, &new_auth_tok,
						&packet_size, max_packet_size);
			अगर (rc) अणु
				ecryptfs_prपूर्णांकk(KERN_ERR, "Error parsing "
						"tag 3 packet\n");
				rc = -EIO;
				जाओ out_wipe_list;
			पूर्ण
			i += packet_size;
			rc = parse_tag_11_packet((अचिन्हित अक्षर *)&src[i],
						 sig_पंचांगp_space,
						 ECRYPTFS_SIG_SIZE,
						 &tag_11_contents_size,
						 &tag_11_packet_size,
						 max_packet_size);
			अगर (rc) अणु
				ecryptfs_prपूर्णांकk(KERN_ERR, "No valid "
						"(ecryptfs-specific) literal "
						"packet containing "
						"authentication token "
						"signature found after "
						"tag 3 packet\n");
				rc = -EIO;
				जाओ out_wipe_list;
			पूर्ण
			i += tag_11_packet_size;
			अगर (ECRYPTFS_SIG_SIZE != tag_11_contents_size) अणु
				ecryptfs_prपूर्णांकk(KERN_ERR, "Expected "
						"signature of size [%d]; "
						"read size [%zd]\n",
						ECRYPTFS_SIG_SIZE,
						tag_11_contents_size);
				rc = -EIO;
				जाओ out_wipe_list;
			पूर्ण
			ecryptfs_to_hex(new_auth_tok->token.password.signature,
					sig_पंचांगp_space, tag_11_contents_size);
			new_auth_tok->token.password.signature[
				ECRYPTFS_PASSWORD_SIG_SIZE] = '\0';
			crypt_stat->flags |= ECRYPTFS_ENCRYPTED;
			अवरोध;
		हाल ECRYPTFS_TAG_1_PACKET_TYPE:
			rc = parse_tag_1_packet(crypt_stat,
						(अचिन्हित अक्षर *)&src[i],
						&auth_tok_list, &new_auth_tok,
						&packet_size, max_packet_size);
			अगर (rc) अणु
				ecryptfs_prपूर्णांकk(KERN_ERR, "Error parsing "
						"tag 1 packet\n");
				rc = -EIO;
				जाओ out_wipe_list;
			पूर्ण
			i += packet_size;
			crypt_stat->flags |= ECRYPTFS_ENCRYPTED;
			अवरोध;
		हाल ECRYPTFS_TAG_11_PACKET_TYPE:
			ecryptfs_prपूर्णांकk(KERN_WARNING, "Invalid packet set "
					"(Tag 11 not allowed by itself)\n");
			rc = -EIO;
			जाओ out_wipe_list;
		शेष:
			ecryptfs_prपूर्णांकk(KERN_DEBUG, "No packet at offset [%zd] "
					"of the file header; hex value of "
					"character is [0x%.2x]\n", i, src[i]);
			next_packet_is_auth_tok_packet = 0;
		पूर्ण
	पूर्ण
	अगर (list_empty(&auth_tok_list)) अणु
		prपूर्णांकk(KERN_ERR "The lower file appears to be a non-encrypted "
		       "eCryptfs file; this is not supported in this version "
		       "of the eCryptfs kernel module\n");
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	/* auth_tok_list contains the set of authentication tokens
	 * parsed from the metadata. We need to find a matching
	 * authentication token that has the secret component(s)
	 * necessary to decrypt the EFEK in the auth_tok parsed from
	 * the metadata. There may be several potential matches, but
	 * just one will be sufficient to decrypt to get the FEK. */
find_next_matching_auth_tok:
	found_auth_tok = 0;
	list_क्रम_each_entry(auth_tok_list_item, &auth_tok_list, list) अणु
		candidate_auth_tok = &auth_tok_list_item->auth_tok;
		अगर (unlikely(ecryptfs_verbosity > 0)) अणु
			ecryptfs_prपूर्णांकk(KERN_DEBUG,
					"Considering candidate auth tok:\n");
			ecryptfs_dump_auth_tok(candidate_auth_tok);
		पूर्ण
		rc = ecryptfs_get_auth_tok_sig(&candidate_auth_tok_sig,
					       candidate_auth_tok);
		अगर (rc) अणु
			prपूर्णांकk(KERN_ERR
			       "Unrecognized candidate auth tok type: [%d]\n",
			       candidate_auth_tok->token_type);
			rc = -EINVAL;
			जाओ out_wipe_list;
		पूर्ण
		rc = ecryptfs_find_auth_tok_क्रम_sig(&auth_tok_key,
					       &matching_auth_tok,
					       crypt_stat->mount_crypt_stat,
					       candidate_auth_tok_sig);
		अगर (!rc) अणु
			found_auth_tok = 1;
			जाओ found_matching_auth_tok;
		पूर्ण
	पूर्ण
	अगर (!found_auth_tok) अणु
		ecryptfs_prपूर्णांकk(KERN_ERR, "Could not find a usable "
				"authentication token\n");
		rc = -EIO;
		जाओ out_wipe_list;
	पूर्ण
found_matching_auth_tok:
	अगर (candidate_auth_tok->token_type == ECRYPTFS_PRIVATE_KEY) अणु
		स_नकल(&(candidate_auth_tok->token.निजी_key),
		       &(matching_auth_tok->token.निजी_key),
		       माप(काष्ठा ecryptfs_निजी_key));
		up_ग_लिखो(&(auth_tok_key->sem));
		key_put(auth_tok_key);
		rc = decrypt_pki_encrypted_session_key(candidate_auth_tok,
						       crypt_stat);
	पूर्ण अन्यथा अगर (candidate_auth_tok->token_type == ECRYPTFS_PASSWORD) अणु
		स_नकल(&(candidate_auth_tok->token.password),
		       &(matching_auth_tok->token.password),
		       माप(काष्ठा ecryptfs_password));
		up_ग_लिखो(&(auth_tok_key->sem));
		key_put(auth_tok_key);
		rc = decrypt_passphrase_encrypted_session_key(
			candidate_auth_tok, crypt_stat);
	पूर्ण अन्यथा अणु
		up_ग_लिखो(&(auth_tok_key->sem));
		key_put(auth_tok_key);
		rc = -EINVAL;
	पूर्ण
	अगर (rc) अणु
		काष्ठा ecryptfs_auth_tok_list_item *auth_tok_list_item_पंचांगp;

		ecryptfs_prपूर्णांकk(KERN_WARNING, "Error decrypting the "
				"session key for authentication token with sig "
				"[%.*s]; rc = [%d]. Removing auth tok "
				"candidate from the list and searching for "
				"the next match.\n", ECRYPTFS_SIG_SIZE_HEX,
				candidate_auth_tok_sig,	rc);
		list_क्रम_each_entry_safe(auth_tok_list_item,
					 auth_tok_list_item_पंचांगp,
					 &auth_tok_list, list) अणु
			अगर (candidate_auth_tok
			    == &auth_tok_list_item->auth_tok) अणु
				list_del(&auth_tok_list_item->list);
				kmem_cache_मुक्त(
					ecryptfs_auth_tok_list_item_cache,
					auth_tok_list_item);
				जाओ find_next_matching_auth_tok;
			पूर्ण
		पूर्ण
		BUG();
	पूर्ण
	rc = ecryptfs_compute_root_iv(crypt_stat);
	अगर (rc) अणु
		ecryptfs_prपूर्णांकk(KERN_ERR, "Error computing "
				"the root IV\n");
		जाओ out_wipe_list;
	पूर्ण
	rc = ecryptfs_init_crypt_ctx(crypt_stat);
	अगर (rc) अणु
		ecryptfs_prपूर्णांकk(KERN_ERR, "Error initializing crypto "
				"context for cipher [%s]; rc = [%d]\n",
				crypt_stat->cipher, rc);
	पूर्ण
out_wipe_list:
	wipe_auth_tok_list(&auth_tok_list);
out:
	वापस rc;
पूर्ण

अटल पूर्णांक
pki_encrypt_session_key(काष्ठा key *auth_tok_key,
			काष्ठा ecryptfs_auth_tok *auth_tok,
			काष्ठा ecryptfs_crypt_stat *crypt_stat,
			काष्ठा ecryptfs_key_record *key_rec)
अणु
	काष्ठा ecryptfs_msg_ctx *msg_ctx = शून्य;
	अक्षर *payload = शून्य;
	माप_प्रकार payload_len = 0;
	काष्ठा ecryptfs_message *msg;
	पूर्णांक rc;

	rc = ग_लिखो_tag_66_packet(auth_tok->token.निजी_key.signature,
				 ecryptfs_code_क्रम_cipher_string(
					 crypt_stat->cipher,
					 crypt_stat->key_size),
				 crypt_stat, &payload, &payload_len);
	up_ग_लिखो(&(auth_tok_key->sem));
	key_put(auth_tok_key);
	अगर (rc) अणु
		ecryptfs_prपूर्णांकk(KERN_ERR, "Error generating tag 66 packet\n");
		जाओ out;
	पूर्ण
	rc = ecryptfs_send_message(payload, payload_len, &msg_ctx);
	अगर (rc) अणु
		ecryptfs_prपूर्णांकk(KERN_ERR, "Error sending message to "
				"ecryptfsd: %d\n", rc);
		जाओ out;
	पूर्ण
	rc = ecryptfs_रुको_क्रम_response(msg_ctx, &msg);
	अगर (rc) अणु
		ecryptfs_prपूर्णांकk(KERN_ERR, "Failed to receive tag 67 packet "
				"from the user space daemon\n");
		rc = -EIO;
		जाओ out;
	पूर्ण
	rc = parse_tag_67_packet(key_rec, msg);
	अगर (rc)
		ecryptfs_prपूर्णांकk(KERN_ERR, "Error parsing tag 67 packet\n");
	kमुक्त(msg);
out:
	kमुक्त(payload);
	वापस rc;
पूर्ण
/**
 * ग_लिखो_tag_1_packet - Write an RFC2440-compatible tag 1 (खुला key) packet
 * @dest: Buffer पूर्णांकo which to ग_लिखो the packet
 * @reमुख्यing_bytes: Maximum number of bytes that can be writtn
 * @auth_tok_key: The authentication token key to unlock and put when करोne with
 *                @auth_tok
 * @auth_tok: The authentication token used क्रम generating the tag 1 packet
 * @crypt_stat: The cryptographic context
 * @key_rec: The key record काष्ठा क्रम the tag 1 packet
 * @packet_size: This function will ग_लिखो the number of bytes that end
 *               up स्थिरituting the packet; set to zero on error
 *
 * Returns zero on success; non-zero on error.
 */
अटल पूर्णांक
ग_लिखो_tag_1_packet(अक्षर *dest, माप_प्रकार *reमुख्यing_bytes,
		   काष्ठा key *auth_tok_key, काष्ठा ecryptfs_auth_tok *auth_tok,
		   काष्ठा ecryptfs_crypt_stat *crypt_stat,
		   काष्ठा ecryptfs_key_record *key_rec, माप_प्रकार *packet_size)
अणु
	माप_प्रकार i;
	माप_प्रकार encrypted_session_key_valid = 0;
	माप_प्रकार packet_size_length;
	माप_प्रकार max_packet_size;
	पूर्णांक rc = 0;

	(*packet_size) = 0;
	ecryptfs_from_hex(key_rec->sig, auth_tok->token.निजी_key.signature,
			  ECRYPTFS_SIG_SIZE);
	encrypted_session_key_valid = 0;
	क्रम (i = 0; i < crypt_stat->key_size; i++)
		encrypted_session_key_valid |=
			auth_tok->session_key.encrypted_key[i];
	अगर (encrypted_session_key_valid) अणु
		स_नकल(key_rec->enc_key,
		       auth_tok->session_key.encrypted_key,
		       auth_tok->session_key.encrypted_key_size);
		up_ग_लिखो(&(auth_tok_key->sem));
		key_put(auth_tok_key);
		जाओ encrypted_session_key_set;
	पूर्ण
	अगर (auth_tok->session_key.encrypted_key_size == 0)
		auth_tok->session_key.encrypted_key_size =
			auth_tok->token.निजी_key.key_size;
	rc = pki_encrypt_session_key(auth_tok_key, auth_tok, crypt_stat,
				     key_rec);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "Failed to encrypt session key via a key "
		       "module; rc = [%d]\n", rc);
		जाओ out;
	पूर्ण
	अगर (ecryptfs_verbosity > 0) अणु
		ecryptfs_prपूर्णांकk(KERN_DEBUG, "Encrypted key:\n");
		ecryptfs_dump_hex(key_rec->enc_key, key_rec->enc_key_size);
	पूर्ण
encrypted_session_key_set:
	/* This क्रमmat is inspired by OpenPGP; see RFC 2440
	 * packet tag 1 */
	max_packet_size = (1                         /* Tag 1 identअगरier */
			   + 3                       /* Max Tag 1 packet size */
			   + 1                       /* Version */
			   + ECRYPTFS_SIG_SIZE       /* Key identअगरier */
			   + 1                       /* Cipher identअगरier */
			   + key_rec->enc_key_size); /* Encrypted key size */
	अगर (max_packet_size > (*reमुख्यing_bytes)) अणु
		prपूर्णांकk(KERN_ERR "Packet length larger than maximum allowable; "
		       "need up to [%td] bytes, but there are only [%td] "
		       "available\n", max_packet_size, (*reमुख्यing_bytes));
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	dest[(*packet_size)++] = ECRYPTFS_TAG_1_PACKET_TYPE;
	rc = ecryptfs_ग_लिखो_packet_length(&dest[(*packet_size)],
					  (max_packet_size - 4),
					  &packet_size_length);
	अगर (rc) अणु
		ecryptfs_prपूर्णांकk(KERN_ERR, "Error generating tag 1 packet "
				"header; cannot generate packet length\n");
		जाओ out;
	पूर्ण
	(*packet_size) += packet_size_length;
	dest[(*packet_size)++] = 0x03; /* version 3 */
	स_नकल(&dest[(*packet_size)], key_rec->sig, ECRYPTFS_SIG_SIZE);
	(*packet_size) += ECRYPTFS_SIG_SIZE;
	dest[(*packet_size)++] = RFC2440_CIPHER_RSA;
	स_नकल(&dest[(*packet_size)], key_rec->enc_key,
	       key_rec->enc_key_size);
	(*packet_size) += key_rec->enc_key_size;
out:
	अगर (rc)
		(*packet_size) = 0;
	अन्यथा
		(*reमुख्यing_bytes) -= (*packet_size);
	वापस rc;
पूर्ण

/**
 * ग_लिखो_tag_11_packet
 * @dest: Target पूर्णांकo which Tag 11 packet is to be written
 * @reमुख्यing_bytes: Maximum packet length
 * @contents: Byte array of contents to copy in
 * @contents_length: Number of bytes in contents
 * @packet_length: Length of the Tag 11 packet written; zero on error
 *
 * Returns zero on success; non-zero on error.
 */
अटल पूर्णांक
ग_लिखो_tag_11_packet(अक्षर *dest, माप_प्रकार *reमुख्यing_bytes, अक्षर *contents,
		    माप_प्रकार contents_length, माप_प्रकार *packet_length)
अणु
	माप_प्रकार packet_size_length;
	माप_प्रकार max_packet_size;
	पूर्णांक rc = 0;

	(*packet_length) = 0;
	/* This क्रमmat is inspired by OpenPGP; see RFC 2440
	 * packet tag 11 */
	max_packet_size = (1                   /* Tag 11 identअगरier */
			   + 3                 /* Max Tag 11 packet size */
			   + 1                 /* Binary क्रमmat specअगरier */
			   + 1                 /* Filename length */
			   + 8                 /* Filename ("_CONSOLE") */
			   + 4                 /* Modअगरication date */
			   + contents_length); /* Literal data */
	अगर (max_packet_size > (*reमुख्यing_bytes)) अणु
		prपूर्णांकk(KERN_ERR "Packet length larger than maximum allowable; "
		       "need up to [%td] bytes, but there are only [%td] "
		       "available\n", max_packet_size, (*reमुख्यing_bytes));
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	dest[(*packet_length)++] = ECRYPTFS_TAG_11_PACKET_TYPE;
	rc = ecryptfs_ग_लिखो_packet_length(&dest[(*packet_length)],
					  (max_packet_size - 4),
					  &packet_size_length);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "Error generating tag 11 packet header; cannot "
		       "generate packet length. rc = [%d]\n", rc);
		जाओ out;
	पूर्ण
	(*packet_length) += packet_size_length;
	dest[(*packet_length)++] = 0x62; /* binary data क्रमmat specअगरier */
	dest[(*packet_length)++] = 8;
	स_नकल(&dest[(*packet_length)], "_CONSOLE", 8);
	(*packet_length) += 8;
	स_रखो(&dest[(*packet_length)], 0x00, 4);
	(*packet_length) += 4;
	स_नकल(&dest[(*packet_length)], contents, contents_length);
	(*packet_length) += contents_length;
 out:
	अगर (rc)
		(*packet_length) = 0;
	अन्यथा
		(*reमुख्यing_bytes) -= (*packet_length);
	वापस rc;
पूर्ण

/**
 * ग_लिखो_tag_3_packet
 * @dest: Buffer पूर्णांकo which to ग_लिखो the packet
 * @reमुख्यing_bytes: Maximum number of bytes that can be written
 * @auth_tok: Authentication token
 * @crypt_stat: The cryptographic context
 * @key_rec: encrypted key
 * @packet_size: This function will ग_लिखो the number of bytes that end
 *               up स्थिरituting the packet; set to zero on error
 *
 * Returns zero on success; non-zero on error.
 */
अटल पूर्णांक
ग_लिखो_tag_3_packet(अक्षर *dest, माप_प्रकार *reमुख्यing_bytes,
		   काष्ठा ecryptfs_auth_tok *auth_tok,
		   काष्ठा ecryptfs_crypt_stat *crypt_stat,
		   काष्ठा ecryptfs_key_record *key_rec, माप_प्रकार *packet_size)
अणु
	माप_प्रकार i;
	माप_प्रकार encrypted_session_key_valid = 0;
	अक्षर session_key_encryption_key[ECRYPTFS_MAX_KEY_BYTES];
	काष्ठा scatterlist dst_sg[2];
	काष्ठा scatterlist src_sg[2];
	काष्ठा mutex *tfm_mutex = शून्य;
	u8 cipher_code;
	माप_प्रकार packet_size_length;
	माप_प्रकार max_packet_size;
	काष्ठा ecryptfs_mount_crypt_stat *mount_crypt_stat =
		crypt_stat->mount_crypt_stat;
	काष्ठा crypto_skcipher *tfm;
	काष्ठा skcipher_request *req;
	पूर्णांक rc = 0;

	(*packet_size) = 0;
	ecryptfs_from_hex(key_rec->sig, auth_tok->token.password.signature,
			  ECRYPTFS_SIG_SIZE);
	rc = ecryptfs_get_tfm_and_mutex_क्रम_cipher_name(&tfm, &tfm_mutex,
							crypt_stat->cipher);
	अगर (unlikely(rc)) अणु
		prपूर्णांकk(KERN_ERR "Internal error whilst attempting to get "
		       "tfm and mutex for cipher name [%s]; rc = [%d]\n",
		       crypt_stat->cipher, rc);
		जाओ out;
	पूर्ण
	अगर (mount_crypt_stat->global_शेष_cipher_key_size == 0) अणु
		prपूर्णांकk(KERN_WARNING "No key size specified at mount; "
		       "defaulting to [%d]\n",
		       crypto_skcipher_max_keysize(tfm));
		mount_crypt_stat->global_शेष_cipher_key_size =
			crypto_skcipher_max_keysize(tfm);
	पूर्ण
	अगर (crypt_stat->key_size == 0)
		crypt_stat->key_size =
			mount_crypt_stat->global_शेष_cipher_key_size;
	अगर (auth_tok->session_key.encrypted_key_size == 0)
		auth_tok->session_key.encrypted_key_size =
			crypt_stat->key_size;
	अगर (crypt_stat->key_size == 24
	    && म_भेद("aes", crypt_stat->cipher) == 0) अणु
		स_रखो((crypt_stat->key + 24), 0, 8);
		auth_tok->session_key.encrypted_key_size = 32;
	पूर्ण अन्यथा
		auth_tok->session_key.encrypted_key_size = crypt_stat->key_size;
	key_rec->enc_key_size =
		auth_tok->session_key.encrypted_key_size;
	encrypted_session_key_valid = 0;
	क्रम (i = 0; i < auth_tok->session_key.encrypted_key_size; i++)
		encrypted_session_key_valid |=
			auth_tok->session_key.encrypted_key[i];
	अगर (encrypted_session_key_valid) अणु
		ecryptfs_prपूर्णांकk(KERN_DEBUG, "encrypted_session_key_valid != 0; "
				"using auth_tok->session_key.encrypted_key, "
				"where key_rec->enc_key_size = [%zd]\n",
				key_rec->enc_key_size);
		स_नकल(key_rec->enc_key,
		       auth_tok->session_key.encrypted_key,
		       key_rec->enc_key_size);
		जाओ encrypted_session_key_set;
	पूर्ण
	अगर (auth_tok->token.password.flags &
	    ECRYPTFS_SESSION_KEY_ENCRYPTION_KEY_SET) अणु
		ecryptfs_prपूर्णांकk(KERN_DEBUG, "Using previously generated "
				"session key encryption key of size [%d]\n",
				auth_tok->token.password.
				session_key_encryption_key_bytes);
		स_नकल(session_key_encryption_key,
		       auth_tok->token.password.session_key_encryption_key,
		       crypt_stat->key_size);
		ecryptfs_prपूर्णांकk(KERN_DEBUG,
				"Cached session key encryption key:\n");
		अगर (ecryptfs_verbosity > 0)
			ecryptfs_dump_hex(session_key_encryption_key, 16);
	पूर्ण
	अगर (unlikely(ecryptfs_verbosity > 0)) अणु
		ecryptfs_prपूर्णांकk(KERN_DEBUG, "Session key encryption key:\n");
		ecryptfs_dump_hex(session_key_encryption_key, 16);
	पूर्ण
	rc = virt_to_scatterlist(crypt_stat->key, key_rec->enc_key_size,
				 src_sg, 2);
	अगर (rc < 1 || rc > 2) अणु
		ecryptfs_prपूर्णांकk(KERN_ERR, "Error generating scatterlist "
				"for crypt_stat session key; expected rc = 1; "
				"got rc = [%d]. key_rec->enc_key_size = [%zd]\n",
				rc, key_rec->enc_key_size);
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	rc = virt_to_scatterlist(key_rec->enc_key, key_rec->enc_key_size,
				 dst_sg, 2);
	अगर (rc < 1 || rc > 2) अणु
		ecryptfs_prपूर्णांकk(KERN_ERR, "Error generating scatterlist "
				"for crypt_stat encrypted session key; "
				"expected rc = 1; got rc = [%d]. "
				"key_rec->enc_key_size = [%zd]\n", rc,
				key_rec->enc_key_size);
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	mutex_lock(tfm_mutex);
	rc = crypto_skcipher_setkey(tfm, session_key_encryption_key,
				    crypt_stat->key_size);
	अगर (rc < 0) अणु
		mutex_unlock(tfm_mutex);
		ecryptfs_prपूर्णांकk(KERN_ERR, "Error setting key for crypto "
				"context; rc = [%d]\n", rc);
		जाओ out;
	पूर्ण

	req = skcipher_request_alloc(tfm, GFP_KERNEL);
	अगर (!req) अणु
		mutex_unlock(tfm_mutex);
		ecryptfs_prपूर्णांकk(KERN_ERR, "Out of kernel memory whilst "
				"attempting to skcipher_request_alloc for "
				"%s\n", crypto_skcipher_driver_name(tfm));
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	skcipher_request_set_callback(req, CRYPTO_TFM_REQ_MAY_SLEEP,
				      शून्य, शून्य);

	rc = 0;
	ecryptfs_prपूर्णांकk(KERN_DEBUG, "Encrypting [%zd] bytes of the key\n",
			crypt_stat->key_size);
	skcipher_request_set_crypt(req, src_sg, dst_sg,
				   (*key_rec).enc_key_size, शून्य);
	rc = crypto_skcipher_encrypt(req);
	mutex_unlock(tfm_mutex);
	skcipher_request_मुक्त(req);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "Error encrypting; rc = [%d]\n", rc);
		जाओ out;
	पूर्ण
	ecryptfs_prपूर्णांकk(KERN_DEBUG, "This should be the encrypted key:\n");
	अगर (ecryptfs_verbosity > 0) अणु
		ecryptfs_prपूर्णांकk(KERN_DEBUG, "EFEK of size [%zd]:\n",
				key_rec->enc_key_size);
		ecryptfs_dump_hex(key_rec->enc_key,
				  key_rec->enc_key_size);
	पूर्ण
encrypted_session_key_set:
	/* This क्रमmat is inspired by OpenPGP; see RFC 2440
	 * packet tag 3 */
	max_packet_size = (1                         /* Tag 3 identअगरier */
			   + 3                       /* Max Tag 3 packet size */
			   + 1                       /* Version */
			   + 1                       /* Cipher code */
			   + 1                       /* S2K specअगरier */
			   + 1                       /* Hash identअगरier */
			   + ECRYPTFS_SALT_SIZE      /* Salt */
			   + 1                       /* Hash iterations */
			   + key_rec->enc_key_size); /* Encrypted key size */
	अगर (max_packet_size > (*reमुख्यing_bytes)) अणु
		prपूर्णांकk(KERN_ERR "Packet too large; need up to [%td] bytes, but "
		       "there are only [%td] available\n", max_packet_size,
		       (*reमुख्यing_bytes));
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	dest[(*packet_size)++] = ECRYPTFS_TAG_3_PACKET_TYPE;
	/* Chop off the Tag 3 identअगरier(1) and Tag 3 packet size(3)
	 * to get the number of octets in the actual Tag 3 packet */
	rc = ecryptfs_ग_लिखो_packet_length(&dest[(*packet_size)],
					  (max_packet_size - 4),
					  &packet_size_length);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "Error generating tag 3 packet header; cannot "
		       "generate packet length. rc = [%d]\n", rc);
		जाओ out;
	पूर्ण
	(*packet_size) += packet_size_length;
	dest[(*packet_size)++] = 0x04; /* version 4 */
	/* TODO: Break from RFC2440 so that arbitrary ciphers can be
	 * specअगरied with strings */
	cipher_code = ecryptfs_code_क्रम_cipher_string(crypt_stat->cipher,
						      crypt_stat->key_size);
	अगर (cipher_code == 0) अणु
		ecryptfs_prपूर्णांकk(KERN_WARNING, "Unable to generate code for "
				"cipher [%s]\n", crypt_stat->cipher);
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	dest[(*packet_size)++] = cipher_code;
	dest[(*packet_size)++] = 0x03;	/* S2K */
	dest[(*packet_size)++] = 0x01;	/* MD5 (TODO: parameterize) */
	स_नकल(&dest[(*packet_size)], auth_tok->token.password.salt,
	       ECRYPTFS_SALT_SIZE);
	(*packet_size) += ECRYPTFS_SALT_SIZE;	/* salt */
	dest[(*packet_size)++] = 0x60;	/* hash iterations (65536) */
	स_नकल(&dest[(*packet_size)], key_rec->enc_key,
	       key_rec->enc_key_size);
	(*packet_size) += key_rec->enc_key_size;
out:
	अगर (rc)
		(*packet_size) = 0;
	अन्यथा
		(*reमुख्यing_bytes) -= (*packet_size);
	वापस rc;
पूर्ण

काष्ठा kmem_cache *ecryptfs_key_record_cache;

/**
 * ecryptfs_generate_key_packet_set
 * @dest_base: Virtual address from which to ग_लिखो the key record set
 * @crypt_stat: The cryptographic context from which the
 *              authentication tokens will be retrieved
 * @ecryptfs_dentry: The dentry, used to retrieve the mount crypt stat
 *                   क्रम the global parameters
 * @len: The amount written
 * @max: The maximum amount of data allowed to be written
 *
 * Generates a key packet set and ग_लिखोs it to the भव address
 * passed in.
 *
 * Returns zero on success; non-zero on error.
 */
पूर्णांक
ecryptfs_generate_key_packet_set(अक्षर *dest_base,
				 काष्ठा ecryptfs_crypt_stat *crypt_stat,
				 काष्ठा dentry *ecryptfs_dentry, माप_प्रकार *len,
				 माप_प्रकार max)
अणु
	काष्ठा ecryptfs_auth_tok *auth_tok;
	काष्ठा key *auth_tok_key = शून्य;
	काष्ठा ecryptfs_mount_crypt_stat *mount_crypt_stat =
		&ecryptfs_superblock_to_निजी(
			ecryptfs_dentry->d_sb)->mount_crypt_stat;
	माप_प्रकार written;
	काष्ठा ecryptfs_key_record *key_rec;
	काष्ठा ecryptfs_key_sig *key_sig;
	पूर्णांक rc = 0;

	(*len) = 0;
	mutex_lock(&crypt_stat->keysig_list_mutex);
	key_rec = kmem_cache_alloc(ecryptfs_key_record_cache, GFP_KERNEL);
	अगर (!key_rec) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	list_क्रम_each_entry(key_sig, &crypt_stat->keysig_list,
			    crypt_stat_list) अणु
		स_रखो(key_rec, 0, माप(*key_rec));
		rc = ecryptfs_find_global_auth_tok_क्रम_sig(&auth_tok_key,
							   &auth_tok,
							   mount_crypt_stat,
							   key_sig->keysig);
		अगर (rc) अणु
			prपूर्णांकk(KERN_WARNING "Unable to retrieve auth tok with "
			       "sig = [%s]\n", key_sig->keysig);
			rc = process_find_global_auth_tok_क्रम_sig_err(rc);
			जाओ out_मुक्त;
		पूर्ण
		अगर (auth_tok->token_type == ECRYPTFS_PASSWORD) अणु
			rc = ग_लिखो_tag_3_packet((dest_base + (*len)),
						&max, auth_tok,
						crypt_stat, key_rec,
						&written);
			up_ग_लिखो(&(auth_tok_key->sem));
			key_put(auth_tok_key);
			अगर (rc) अणु
				ecryptfs_prपूर्णांकk(KERN_WARNING, "Error "
						"writing tag 3 packet\n");
				जाओ out_मुक्त;
			पूर्ण
			(*len) += written;
			/* Write auth tok signature packet */
			rc = ग_लिखो_tag_11_packet((dest_base + (*len)), &max,
						 key_rec->sig,
						 ECRYPTFS_SIG_SIZE, &written);
			अगर (rc) अणु
				ecryptfs_prपूर्णांकk(KERN_ERR, "Error writing "
						"auth tok signature packet\n");
				जाओ out_मुक्त;
			पूर्ण
			(*len) += written;
		पूर्ण अन्यथा अगर (auth_tok->token_type == ECRYPTFS_PRIVATE_KEY) अणु
			rc = ग_लिखो_tag_1_packet(dest_base + (*len), &max,
						auth_tok_key, auth_tok,
						crypt_stat, key_rec, &written);
			अगर (rc) अणु
				ecryptfs_prपूर्णांकk(KERN_WARNING, "Error "
						"writing tag 1 packet\n");
				जाओ out_मुक्त;
			पूर्ण
			(*len) += written;
		पूर्ण अन्यथा अणु
			up_ग_लिखो(&(auth_tok_key->sem));
			key_put(auth_tok_key);
			ecryptfs_prपूर्णांकk(KERN_WARNING, "Unsupported "
					"authentication token type\n");
			rc = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
	पूर्ण
	अगर (likely(max > 0)) अणु
		dest_base[(*len)] = 0x00;
	पूर्ण अन्यथा अणु
		ecryptfs_prपूर्णांकk(KERN_ERR, "Error writing boundary byte\n");
		rc = -EIO;
	पूर्ण
out_मुक्त:
	kmem_cache_मुक्त(ecryptfs_key_record_cache, key_rec);
out:
	अगर (rc)
		(*len) = 0;
	mutex_unlock(&crypt_stat->keysig_list_mutex);
	वापस rc;
पूर्ण

काष्ठा kmem_cache *ecryptfs_key_sig_cache;

पूर्णांक ecryptfs_add_keysig(काष्ठा ecryptfs_crypt_stat *crypt_stat, अक्षर *sig)
अणु
	काष्ठा ecryptfs_key_sig *new_key_sig;

	new_key_sig = kmem_cache_alloc(ecryptfs_key_sig_cache, GFP_KERNEL);
	अगर (!new_key_sig)
		वापस -ENOMEM;

	स_नकल(new_key_sig->keysig, sig, ECRYPTFS_SIG_SIZE_HEX);
	new_key_sig->keysig[ECRYPTFS_SIG_SIZE_HEX] = '\0';
	/* Caller must hold keysig_list_mutex */
	list_add(&new_key_sig->crypt_stat_list, &crypt_stat->keysig_list);

	वापस 0;
पूर्ण

काष्ठा kmem_cache *ecryptfs_global_auth_tok_cache;

पूर्णांक
ecryptfs_add_global_auth_tok(काष्ठा ecryptfs_mount_crypt_stat *mount_crypt_stat,
			     अक्षर *sig, u32 global_auth_tok_flags)
अणु
	काष्ठा ecryptfs_global_auth_tok *new_auth_tok;

	new_auth_tok = kmem_cache_zalloc(ecryptfs_global_auth_tok_cache,
					GFP_KERNEL);
	अगर (!new_auth_tok)
		वापस -ENOMEM;

	स_नकल(new_auth_tok->sig, sig, ECRYPTFS_SIG_SIZE_HEX);
	new_auth_tok->flags = global_auth_tok_flags;
	new_auth_tok->sig[ECRYPTFS_SIG_SIZE_HEX] = '\0';
	mutex_lock(&mount_crypt_stat->global_auth_tok_list_mutex);
	list_add(&new_auth_tok->mount_crypt_stat_list,
		 &mount_crypt_stat->global_auth_tok_list);
	mutex_unlock(&mount_crypt_stat->global_auth_tok_list_mutex);
	वापस 0;
पूर्ण

