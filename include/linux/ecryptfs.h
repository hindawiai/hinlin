<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_ECRYPTFS_H
#घोषणा _LINUX_ECRYPTFS_H

/* Version verअगरication क्रम shared data काष्ठाures w/ userspace */
#घोषणा ECRYPTFS_VERSION_MAJOR 0x00
#घोषणा ECRYPTFS_VERSION_MINOR 0x04
#घोषणा ECRYPTFS_SUPPORTED_खाता_VERSION 0x03
/* These flags indicate which features are supported by the kernel
 * module; userspace tools such as the mount helper पढ़ो the feature
 * bits from a sysfs handle in order to determine how to behave. */
#घोषणा ECRYPTFS_VERSIONING_PASSPHRASE            0x00000001
#घोषणा ECRYPTFS_VERSIONING_PUBKEY                0x00000002
#घोषणा ECRYPTFS_VERSIONING_PLAINTEXT_PASSTHROUGH 0x00000004
#घोषणा ECRYPTFS_VERSIONING_POLICY                0x00000008
#घोषणा ECRYPTFS_VERSIONING_XATTR                 0x00000010
#घोषणा ECRYPTFS_VERSIONING_MULTKEY               0x00000020
#घोषणा ECRYPTFS_VERSIONING_DEVMISC               0x00000040
#घोषणा ECRYPTFS_VERSIONING_HMAC                  0x00000080
#घोषणा ECRYPTFS_VERSIONING_खाताNAME_ENCRYPTION   0x00000100
#घोषणा ECRYPTFS_VERSIONING_GCM                   0x00000200
#घोषणा ECRYPTFS_MAX_PASSWORD_LENGTH 64
#घोषणा ECRYPTFS_MAX_PASSPHRASE_BYTES ECRYPTFS_MAX_PASSWORD_LENGTH
#घोषणा ECRYPTFS_SALT_SIZE 8
#घोषणा ECRYPTFS_SALT_SIZE_HEX (ECRYPTFS_SALT_SIZE*2)
/* The original signature size is only क्रम what is stored on disk; all
 * in-memory representations are expanded hex, so it better adapted to
 * be passed around or referenced on the command line */
#घोषणा ECRYPTFS_SIG_SIZE 8
#घोषणा ECRYPTFS_SIG_SIZE_HEX (ECRYPTFS_SIG_SIZE*2)
#घोषणा ECRYPTFS_PASSWORD_SIG_SIZE ECRYPTFS_SIG_SIZE_HEX
#घोषणा ECRYPTFS_MAX_KEY_BYTES 64
#घोषणा ECRYPTFS_MAX_ENCRYPTED_KEY_BYTES 512
#घोषणा ECRYPTFS_खाता_VERSION 0x03
#घोषणा ECRYPTFS_MAX_PKI_NAME_BYTES 16

#घोषणा RFC2440_CIPHER_DES3_EDE 0x02
#घोषणा RFC2440_CIPHER_CAST_5 0x03
#घोषणा RFC2440_CIPHER_BLOWFISH 0x04
#घोषणा RFC2440_CIPHER_AES_128 0x07
#घोषणा RFC2440_CIPHER_AES_192 0x08
#घोषणा RFC2440_CIPHER_AES_256 0x09
#घोषणा RFC2440_CIPHER_TWOFISH 0x0a
#घोषणा RFC2440_CIPHER_CAST_6 0x0b

#घोषणा RFC2440_CIPHER_RSA 0x01

/**
 * For convenience, we may need to pass around the encrypted session
 * key between kernel and userspace because the authentication token
 * may not be extractable.  For example, the TPM may not release the
 * निजी key, instead requiring the encrypted data and वापसing the
 * decrypted data.
 */
काष्ठा ecryptfs_session_key अणु
#घोषणा ECRYPTFS_USERSPACE_SHOULD_TRY_TO_DECRYPT 0x00000001
#घोषणा ECRYPTFS_USERSPACE_SHOULD_TRY_TO_ENCRYPT 0x00000002
#घोषणा ECRYPTFS_CONTAINS_DECRYPTED_KEY 0x00000004
#घोषणा ECRYPTFS_CONTAINS_ENCRYPTED_KEY 0x00000008
	u32 flags;
	u32 encrypted_key_size;
	u32 decrypted_key_size;
	u8 encrypted_key[ECRYPTFS_MAX_ENCRYPTED_KEY_BYTES];
	u8 decrypted_key[ECRYPTFS_MAX_KEY_BYTES];
पूर्ण;

काष्ठा ecryptfs_password अणु
	u32 password_bytes;
	s32 hash_algo;
	u32 hash_iterations;
	u32 session_key_encryption_key_bytes;
#घोषणा ECRYPTFS_PERSISTENT_PASSWORD 0x01
#घोषणा ECRYPTFS_SESSION_KEY_ENCRYPTION_KEY_SET 0x02
	u32 flags;
	/* Iterated-hash concatenation of salt and passphrase */
	u8 session_key_encryption_key[ECRYPTFS_MAX_KEY_BYTES];
	u8 signature[ECRYPTFS_PASSWORD_SIG_SIZE + 1];
	/* Always in expanded hex */
	u8 salt[ECRYPTFS_SALT_SIZE];
पूर्ण;

क्रमागत ecryptfs_token_types अणुECRYPTFS_PASSWORD, ECRYPTFS_PRIVATE_KEYपूर्ण;

काष्ठा ecryptfs_निजी_key अणु
	u32 key_size;
	u32 data_len;
	u8 signature[ECRYPTFS_PASSWORD_SIG_SIZE + 1];
	अक्षर pki_type[ECRYPTFS_MAX_PKI_NAME_BYTES + 1];
	u8 data[];
पूर्ण;

/* May be a password or a निजी key */
काष्ठा ecryptfs_auth_tok अणु
	u16 version; /* 8-bit major and 8-bit minor */
	u16 token_type;
#घोषणा ECRYPTFS_ENCRYPT_ONLY 0x00000001
	u32 flags;
	काष्ठा ecryptfs_session_key session_key;
	u8 reserved[32];
	जोड़ अणु
		काष्ठा ecryptfs_password password;
		काष्ठा ecryptfs_निजी_key निजी_key;
	पूर्ण token;
पूर्ण __attribute__ ((packed));

#पूर्ण_अगर /* _LINUX_ECRYPTFS_H */
