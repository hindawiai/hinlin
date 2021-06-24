<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/**
 * eCryptfs: Linux fileप्रणाली encryption layer
 * Kernel declarations.
 *
 * Copyright (C) 1997-2003 Erez Zaकरोk
 * Copyright (C) 2001-2003 Stony Brook University
 * Copyright (C) 2004-2008 International Business Machines Corp.
 *   Author(s): Michael A. Halcrow <mahalcro@us.ibm.com>
 *              Trevor S. Highland <trevor.highland@gmail.com>
 *              Tyler Hicks <code@tyhicks.com>
 */

#अगर_अघोषित ECRYPTFS_KERNEL_H
#घोषणा ECRYPTFS_KERNEL_H

#समावेश <crypto/skcipher.h>
#समावेश <keys/user-type.h>
#समावेश <keys/encrypted-type.h>
#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/fs_stack.h>
#समावेश <linux/namei.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/hash.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/ecryptfs.h>

#घोषणा ECRYPTFS_DEFAULT_IV_BYTES 16
#घोषणा ECRYPTFS_DEFAULT_EXTENT_SIZE 4096
#घोषणा ECRYPTFS_MINIMUM_HEADER_EXTENT_SIZE 8192
#घोषणा ECRYPTFS_DEFAULT_MSG_CTX_ELEMS 32
#घोषणा ECRYPTFS_DEFAULT_SEND_TIMEOUT HZ
#घोषणा ECRYPTFS_MAX_MSG_CTX_TTL (HZ*3)
#घोषणा ECRYPTFS_DEFAULT_NUM_USERS 4
#घोषणा ECRYPTFS_MAX_NUM_USERS 32768
#घोषणा ECRYPTFS_XATTR_NAME "user.ecryptfs"

व्योम ecryptfs_dump_auth_tok(काष्ठा ecryptfs_auth_tok *auth_tok);
अटल अंतरभूत व्योम
ecryptfs_to_hex(अक्षर *dst, अक्षर *src, माप_प्रकार src_size)
अणु
	अक्षर *end = bin2hex(dst, src, src_size);
	*end = '\0';
पूर्ण

बाह्य व्योम ecryptfs_from_hex(अक्षर *dst, अक्षर *src, पूर्णांक dst_size);

काष्ठा ecryptfs_key_record अणु
	अचिन्हित अक्षर type;
	माप_प्रकार enc_key_size;
	अचिन्हित अक्षर sig[ECRYPTFS_SIG_SIZE];
	अचिन्हित अक्षर enc_key[ECRYPTFS_MAX_ENCRYPTED_KEY_BYTES];
पूर्ण;

काष्ठा ecryptfs_auth_tok_list अणु
	काष्ठा ecryptfs_auth_tok *auth_tok;
	काष्ठा list_head list;
पूर्ण;

काष्ठा ecryptfs_crypt_stat;
काष्ठा ecryptfs_mount_crypt_stat;

काष्ठा ecryptfs_page_crypt_context अणु
	काष्ठा page *page;
#घोषणा ECRYPTFS_PREPARE_COMMIT_MODE 0
#घोषणा ECRYPTFS_WRITEPAGE_MODE      1
	अचिन्हित पूर्णांक mode;
	जोड़ अणु
		काष्ठा file *lower_file;
		काष्ठा ग_लिखोback_control *wbc;
	पूर्ण param;
पूर्ण;

#अगर defined(CONFIG_ENCRYPTED_KEYS) || defined(CONFIG_ENCRYPTED_KEYS_MODULE)
अटल अंतरभूत काष्ठा ecryptfs_auth_tok *
ecryptfs_get_encrypted_key_payload_data(काष्ठा key *key)
अणु
	काष्ठा encrypted_key_payload *payload;

	अगर (key->type != &key_type_encrypted)
		वापस शून्य;

	payload = key->payload.data[0];
	अगर (!payload)
		वापस ERR_PTR(-EKEYREVOKED);

	वापस (काष्ठा ecryptfs_auth_tok *)payload->payload_data;
पूर्ण

अटल अंतरभूत काष्ठा key *ecryptfs_get_encrypted_key(अक्षर *sig)
अणु
	वापस request_key(&key_type_encrypted, sig, शून्य);
पूर्ण

#अन्यथा
अटल अंतरभूत काष्ठा ecryptfs_auth_tok *
ecryptfs_get_encrypted_key_payload_data(काष्ठा key *key)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा key *ecryptfs_get_encrypted_key(अक्षर *sig)
अणु
	वापस ERR_PTR(-ENOKEY);
पूर्ण

#पूर्ण_अगर /* CONFIG_ENCRYPTED_KEYS */

अटल अंतरभूत काष्ठा ecryptfs_auth_tok *
ecryptfs_get_key_payload_data(काष्ठा key *key)
अणु
	काष्ठा ecryptfs_auth_tok *auth_tok;
	काष्ठा user_key_payload *ukp;

	auth_tok = ecryptfs_get_encrypted_key_payload_data(key);
	अगर (auth_tok)
		वापस auth_tok;

	ukp = user_key_payload_locked(key);
	अगर (!ukp)
		वापस ERR_PTR(-EKEYREVOKED);

	वापस (काष्ठा ecryptfs_auth_tok *)ukp->data;
पूर्ण

#घोषणा ECRYPTFS_MAX_KEYSET_SIZE 1024
#घोषणा ECRYPTFS_MAX_CIPHER_NAME_SIZE 31
#घोषणा ECRYPTFS_MAX_NUM_ENC_KEYS 64
#घोषणा ECRYPTFS_MAX_IV_BYTES 16	/* 128 bits */
#घोषणा ECRYPTFS_SALT_BYTES 2
#घोषणा MAGIC_ECRYPTFS_MARKER 0x3c81b7f5
#घोषणा MAGIC_ECRYPTFS_MARKER_SIZE_BYTES 8	/* 4*2 */
#घोषणा ECRYPTFS_खाता_SIZE_BYTES (माप(u64))
#घोषणा ECRYPTFS_SIZE_AND_MARKER_BYTES (ECRYPTFS_खाता_SIZE_BYTES \
					+ MAGIC_ECRYPTFS_MARKER_SIZE_BYTES)
#घोषणा ECRYPTFS_DEFAULT_CIPHER "aes"
#घोषणा ECRYPTFS_DEFAULT_KEY_BYTES 16
#घोषणा ECRYPTFS_DEFAULT_HASH "md5"
#घोषणा ECRYPTFS_TAG_70_DIGEST ECRYPTFS_DEFAULT_HASH
#घोषणा ECRYPTFS_TAG_1_PACKET_TYPE 0x01
#घोषणा ECRYPTFS_TAG_3_PACKET_TYPE 0x8C
#घोषणा ECRYPTFS_TAG_11_PACKET_TYPE 0xED
#घोषणा ECRYPTFS_TAG_64_PACKET_TYPE 0x40
#घोषणा ECRYPTFS_TAG_65_PACKET_TYPE 0x41
#घोषणा ECRYPTFS_TAG_66_PACKET_TYPE 0x42
#घोषणा ECRYPTFS_TAG_67_PACKET_TYPE 0x43
#घोषणा ECRYPTFS_TAG_70_PACKET_TYPE 0x46 /* FNEK-encrypted filename
					  * as dentry name */
#घोषणा ECRYPTFS_TAG_71_PACKET_TYPE 0x47 /* FNEK-encrypted filename in
					  * metadata */
#घोषणा ECRYPTFS_TAG_72_PACKET_TYPE 0x48 /* FEK-encrypted filename as
					  * dentry name */
#घोषणा ECRYPTFS_TAG_73_PACKET_TYPE 0x49 /* FEK-encrypted filename as
					  * metadata */
#घोषणा ECRYPTFS_MIN_PKT_LEN_SIZE 1 /* Min size to specअगरy packet length */
#घोषणा ECRYPTFS_MAX_PKT_LEN_SIZE 2 /* Pass at least this many bytes to
				     * ecryptfs_parse_packet_length() and
				     * ecryptfs_ग_लिखो_packet_length()
				     */
/* Constraपूर्णांक: ECRYPTFS_खाताNAME_MIN_RANDOM_PREPEND_BYTES >=
 * ECRYPTFS_MAX_IV_BYTES */
#घोषणा ECRYPTFS_खाताNAME_MIN_RANDOM_PREPEND_BYTES 16
#घोषणा ECRYPTFS_NON_शून्य 0x42 /* A reasonable substitute क्रम शून्य */
#घोषणा MD5_DIGEST_SIZE 16
#घोषणा ECRYPTFS_TAG_70_DIGEST_SIZE MD5_DIGEST_SIZE
#घोषणा ECRYPTFS_TAG_70_MIN_METADATA_SIZE (1 + ECRYPTFS_MIN_PKT_LEN_SIZE \
					   + ECRYPTFS_SIG_SIZE + 1 + 1)
#घोषणा ECRYPTFS_TAG_70_MAX_METADATA_SIZE (1 + ECRYPTFS_MAX_PKT_LEN_SIZE \
					   + ECRYPTFS_SIG_SIZE + 1 + 1)
#घोषणा ECRYPTFS_FEK_ENCRYPTED_खाताNAME_PREFIX "ECRYPTFS_FEK_ENCRYPTED."
#घोषणा ECRYPTFS_FEK_ENCRYPTED_खाताNAME_PREFIX_SIZE 23
#घोषणा ECRYPTFS_FNEK_ENCRYPTED_खाताNAME_PREFIX "ECRYPTFS_FNEK_ENCRYPTED."
#घोषणा ECRYPTFS_FNEK_ENCRYPTED_खाताNAME_PREFIX_SIZE 24
#घोषणा ECRYPTFS_ENCRYPTED_DENTRY_NAME_LEN (18 + 1 + 4 + 1 + 32)

#अगर_घोषित CONFIG_ECRYPT_FS_MESSAGING
# define ECRYPTFS_VERSIONING_MASK_MESSAGING (ECRYPTFS_VERSIONING_DEVMISC \
					     | ECRYPTFS_VERSIONING_PUBKEY)
#अन्यथा
# define ECRYPTFS_VERSIONING_MASK_MESSAGING 0
#पूर्ण_अगर

#घोषणा ECRYPTFS_VERSIONING_MASK (ECRYPTFS_VERSIONING_PASSPHRASE \
				  | ECRYPTFS_VERSIONING_PLAINTEXT_PASSTHROUGH \
				  | ECRYPTFS_VERSIONING_XATTR \
				  | ECRYPTFS_VERSIONING_MULTKEY \
				  | ECRYPTFS_VERSIONING_MASK_MESSAGING \
				  | ECRYPTFS_VERSIONING_खाताNAME_ENCRYPTION)
काष्ठा ecryptfs_key_sig अणु
	काष्ठा list_head crypt_stat_list;
	अक्षर keysig[ECRYPTFS_SIG_SIZE_HEX + 1];
पूर्ण;

काष्ठा ecryptfs_filename अणु
	काष्ठा list_head crypt_stat_list;
#घोषणा ECRYPTFS_खाताNAME_CONTAINS_DECRYPTED 0x00000001
	u32 flags;
	u32 seq_no;
	अक्षर *filename;
	अक्षर *encrypted_filename;
	माप_प्रकार filename_size;
	माप_प्रकार encrypted_filename_size;
	अक्षर fnek_sig[ECRYPTFS_SIG_SIZE_HEX];
	अक्षर dentry_name[ECRYPTFS_ENCRYPTED_DENTRY_NAME_LEN + 1];
पूर्ण;

/**
 * This is the primary काष्ठा associated with each encrypted file.
 *
 * TODO: cache align/pack?
 */
काष्ठा ecryptfs_crypt_stat अणु
#घोषणा ECRYPTFS_STRUCT_INITIALIZED   0x00000001
#घोषणा ECRYPTFS_POLICY_APPLIED       0x00000002
#घोषणा ECRYPTFS_ENCRYPTED            0x00000004
#घोषणा ECRYPTFS_SECURITY_WARNING     0x00000008
#घोषणा ECRYPTFS_ENABLE_HMAC          0x00000010
#घोषणा ECRYPTFS_ENCRYPT_IV_PAGES     0x00000020
#घोषणा ECRYPTFS_KEY_VALID            0x00000040
#घोषणा ECRYPTFS_METADATA_IN_XATTR    0x00000080
#घोषणा ECRYPTFS_VIEW_AS_ENCRYPTED    0x00000100
#घोषणा ECRYPTFS_KEY_SET              0x00000200
#घोषणा ECRYPTFS_ENCRYPT_खाताNAMES    0x00000400
#घोषणा ECRYPTFS_ENCFN_USE_MOUNT_FNEK 0x00000800
#घोषणा ECRYPTFS_ENCFN_USE_FEK        0x00001000
#घोषणा ECRYPTFS_UNLINK_SIGS          0x00002000
#घोषणा ECRYPTFS_I_SIZE_INITIALIZED   0x00004000
	u32 flags;
	अचिन्हित पूर्णांक file_version;
	माप_प्रकार iv_bytes;
	माप_प्रकार metadata_size;
	माप_प्रकार extent_size; /* Data extent size; शेष is 4096 */
	माप_प्रकार key_size;
	माप_प्रकार extent_shअगरt;
	अचिन्हित पूर्णांक extent_mask;
	काष्ठा ecryptfs_mount_crypt_stat *mount_crypt_stat;
	काष्ठा crypto_skcipher *tfm;
	काष्ठा crypto_shash *hash_tfm; /* Crypto context क्रम generating
					* the initialization vectors */
	अचिन्हित अक्षर cipher[ECRYPTFS_MAX_CIPHER_NAME_SIZE + 1];
	अचिन्हित अक्षर key[ECRYPTFS_MAX_KEY_BYTES];
	अचिन्हित अक्षर root_iv[ECRYPTFS_MAX_IV_BYTES];
	काष्ठा list_head keysig_list;
	काष्ठा mutex keysig_list_mutex;
	काष्ठा mutex cs_tfm_mutex;
	काष्ठा mutex cs_mutex;
पूर्ण;

/* inode निजी data. */
काष्ठा ecryptfs_inode_info अणु
	काष्ठा inode vfs_inode;
	काष्ठा inode *wii_inode;
	काष्ठा mutex lower_file_mutex;
	atomic_t lower_file_count;
	काष्ठा file *lower_file;
	काष्ठा ecryptfs_crypt_stat crypt_stat;
पूर्ण;

/* dentry निजी data. Each dentry must keep track of a lower
 * vfsmount too. */
काष्ठा ecryptfs_dentry_info अणु
	काष्ठा path lower_path;
	काष्ठा rcu_head rcu;
पूर्ण;

/**
 * ecryptfs_global_auth_tok - A key used to encrypt all new files under the mountpoपूर्णांक
 * @flags: Status flags
 * @mount_crypt_stat_list: These auth_toks hang off the mount-wide
 *                         cryptographic context. Every समय a new
 *                         inode comes पूर्णांकo existence, eCryptfs copies
 *                         the auth_toks on that list to the set of
 *                         auth_toks on the inode's crypt_stat
 * @global_auth_tok_key: The key from the user's keyring क्रम the sig
 * @global_auth_tok: The key contents
 * @sig: The key identअगरier
 *
 * ecryptfs_global_auth_tok काष्ठाs refer to authentication token keys
 * in the user keyring that apply to newly created files. A list of
 * these objects hangs off of the mount_crypt_stat काष्ठा क्रम any
 * given eCryptfs mount. This काष्ठा मुख्यtains a reference to both the
 * key contents and the key itself so that the key can be put on
 * unmount.
 */
काष्ठा ecryptfs_global_auth_tok अणु
#घोषणा ECRYPTFS_AUTH_TOK_INVALID 0x00000001
#घोषणा ECRYPTFS_AUTH_TOK_FNEK    0x00000002
	u32 flags;
	काष्ठा list_head mount_crypt_stat_list;
	काष्ठा key *global_auth_tok_key;
	अचिन्हित अक्षर sig[ECRYPTFS_SIG_SIZE_HEX + 1];
पूर्ण;

/**
 * ecryptfs_key_tfm - Persistent key tfm
 * @key_tfm: crypto API handle to the key
 * @key_size: Key size in bytes
 * @key_tfm_mutex: Mutex to ensure only one operation in eCryptfs is
 *                 using the persistent TFM at any poपूर्णांक in समय
 * @key_tfm_list: Handle to hang this off the module-wide TFM list
 * @cipher_name: String name क्रम the cipher क्रम this TFM
 *
 * Typically, eCryptfs will use the same ciphers repeatedly throughout
 * the course of its operations. In order to aव्योम unnecessarily
 * destroying and initializing the same cipher repeatedly, eCryptfs
 * keeps a list of crypto API contexts around to use when needed.
 */
काष्ठा ecryptfs_key_tfm अणु
	काष्ठा crypto_skcipher *key_tfm;
	माप_प्रकार key_size;
	काष्ठा mutex key_tfm_mutex;
	काष्ठा list_head key_tfm_list;
	अचिन्हित अक्षर cipher_name[ECRYPTFS_MAX_CIPHER_NAME_SIZE + 1];
पूर्ण;

बाह्य काष्ठा mutex key_tfm_list_mutex;

/**
 * This काष्ठा is to enable a mount-wide passphrase/salt combo. This
 * is more or less a stopgap to provide similar functionality to other
 * crypto fileप्रणालीs like EncFS or CFS until full policy support is
 * implemented in eCryptfs.
 */
काष्ठा ecryptfs_mount_crypt_stat अणु
	/* Poपूर्णांकers to memory we करो not own, करो not मुक्त these */
#घोषणा ECRYPTFS_PLAINTEXT_PASSTHROUGH_ENABLED 0x00000001
#घोषणा ECRYPTFS_XATTR_METADATA_ENABLED        0x00000002
#घोषणा ECRYPTFS_ENCRYPTED_VIEW_ENABLED        0x00000004
#घोषणा ECRYPTFS_MOUNT_CRYPT_STAT_INITIALIZED  0x00000008
#घोषणा ECRYPTFS_GLOBAL_ENCRYPT_खाताNAMES      0x00000010
#घोषणा ECRYPTFS_GLOBAL_ENCFN_USE_MOUNT_FNEK   0x00000020
#घोषणा ECRYPTFS_GLOBAL_ENCFN_USE_FEK          0x00000040
#घोषणा ECRYPTFS_GLOBAL_MOUNT_AUTH_TOK_ONLY    0x00000080
	u32 flags;
	काष्ठा list_head global_auth_tok_list;
	काष्ठा mutex global_auth_tok_list_mutex;
	माप_प्रकार global_शेष_cipher_key_size;
	माप_प्रकार global_शेष_fn_cipher_key_bytes;
	अचिन्हित अक्षर global_शेष_cipher_name[ECRYPTFS_MAX_CIPHER_NAME_SIZE
						 + 1];
	अचिन्हित अक्षर global_शेष_fn_cipher_name[
		ECRYPTFS_MAX_CIPHER_NAME_SIZE + 1];
	अक्षर global_शेष_fnek_sig[ECRYPTFS_SIG_SIZE_HEX + 1];
पूर्ण;

/* superblock निजी data. */
काष्ठा ecryptfs_sb_info अणु
	काष्ठा super_block *wsi_sb;
	काष्ठा ecryptfs_mount_crypt_stat mount_crypt_stat;
पूर्ण;

/* file निजी data. */
काष्ठा ecryptfs_file_info अणु
	काष्ठा file *wfi_file;
	काष्ठा ecryptfs_crypt_stat *crypt_stat;
पूर्ण;

/* auth_tok <=> encrypted_session_key mappings */
काष्ठा ecryptfs_auth_tok_list_item अणु
	अचिन्हित अक्षर encrypted_session_key[ECRYPTFS_MAX_KEY_BYTES];
	काष्ठा list_head list;
	काष्ठा ecryptfs_auth_tok auth_tok;
पूर्ण;

काष्ठा ecryptfs_message अणु
	/* Can never be greater than ecryptfs_message_buf_len */
	/* Used to find the parent msg_ctx */
	/* Inherits from msg_ctx->index */
	u32 index;
	u32 data_len;
	u8 data[];
पूर्ण;

काष्ठा ecryptfs_msg_ctx अणु
#घोषणा ECRYPTFS_MSG_CTX_STATE_FREE     0x01
#घोषणा ECRYPTFS_MSG_CTX_STATE_PENDING  0x02
#घोषणा ECRYPTFS_MSG_CTX_STATE_DONE     0x03
#घोषणा ECRYPTFS_MSG_CTX_STATE_NO_REPLY 0x04
	u8 state;
#घोषणा ECRYPTFS_MSG_HELO 100
#घोषणा ECRYPTFS_MSG_QUIT 101
#घोषणा ECRYPTFS_MSG_REQUEST 102
#घोषणा ECRYPTFS_MSG_RESPONSE 103
	u8 type;
	u32 index;
	/* Counter converts to a sequence number. Each message sent
	 * out क्रम which we expect a response has an associated
	 * sequence number. The response must have the same sequence
	 * number as the counter क्रम the msg_stc क्रम the message to be
	 * valid. */
	u32 counter;
	माप_प्रकार msg_size;
	काष्ठा ecryptfs_message *msg;
	काष्ठा task_काष्ठा *task;
	काष्ठा list_head node;
	काष्ठा list_head daemon_out_list;
	काष्ठा mutex mux;
पूर्ण;

काष्ठा ecryptfs_daemon अणु
#घोषणा ECRYPTFS_DAEMON_IN_READ      0x00000001
#घोषणा ECRYPTFS_DAEMON_IN_POLL      0x00000002
#घोषणा ECRYPTFS_DAEMON_ZOMBIE       0x00000004
#घोषणा ECRYPTFS_DAEMON_MISCDEV_OPEN 0x00000008
	u32 flags;
	u32 num_queued_msg_ctx;
	काष्ठा file *file;
	काष्ठा mutex mux;
	काष्ठा list_head msg_ctx_out_queue;
	रुको_queue_head_t रुको;
	काष्ठा hlist_node euid_chain;
पूर्ण;

#अगर_घोषित CONFIG_ECRYPT_FS_MESSAGING
बाह्य काष्ठा mutex ecryptfs_daemon_hash_mux;
#पूर्ण_अगर

अटल अंतरभूत माप_प्रकार
ecryptfs_lower_header_size(काष्ठा ecryptfs_crypt_stat *crypt_stat)
अणु
	अगर (crypt_stat->flags & ECRYPTFS_METADATA_IN_XATTR)
		वापस 0;
	वापस crypt_stat->metadata_size;
पूर्ण

अटल अंतरभूत काष्ठा ecryptfs_file_info *
ecryptfs_file_to_निजी(काष्ठा file *file)
अणु
	वापस file->निजी_data;
पूर्ण

अटल अंतरभूत व्योम
ecryptfs_set_file_निजी(काष्ठा file *file,
			  काष्ठा ecryptfs_file_info *file_info)
अणु
	file->निजी_data = file_info;
पूर्ण

अटल अंतरभूत काष्ठा file *ecryptfs_file_to_lower(काष्ठा file *file)
अणु
	वापस ((काष्ठा ecryptfs_file_info *)file->निजी_data)->wfi_file;
पूर्ण

अटल अंतरभूत व्योम
ecryptfs_set_file_lower(काष्ठा file *file, काष्ठा file *lower_file)
अणु
	((काष्ठा ecryptfs_file_info *)file->निजी_data)->wfi_file =
		lower_file;
पूर्ण

अटल अंतरभूत काष्ठा ecryptfs_inode_info *
ecryptfs_inode_to_निजी(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा ecryptfs_inode_info, vfs_inode);
पूर्ण

अटल अंतरभूत काष्ठा inode *ecryptfs_inode_to_lower(काष्ठा inode *inode)
अणु
	वापस ecryptfs_inode_to_निजी(inode)->wii_inode;
पूर्ण

अटल अंतरभूत व्योम
ecryptfs_set_inode_lower(काष्ठा inode *inode, काष्ठा inode *lower_inode)
अणु
	ecryptfs_inode_to_निजी(inode)->wii_inode = lower_inode;
पूर्ण

अटल अंतरभूत काष्ठा ecryptfs_sb_info *
ecryptfs_superblock_to_निजी(काष्ठा super_block *sb)
अणु
	वापस (काष्ठा ecryptfs_sb_info *)sb->s_fs_info;
पूर्ण

अटल अंतरभूत व्योम
ecryptfs_set_superblock_निजी(काष्ठा super_block *sb,
				काष्ठा ecryptfs_sb_info *sb_info)
अणु
	sb->s_fs_info = sb_info;
पूर्ण

अटल अंतरभूत काष्ठा super_block *
ecryptfs_superblock_to_lower(काष्ठा super_block *sb)
अणु
	वापस ((काष्ठा ecryptfs_sb_info *)sb->s_fs_info)->wsi_sb;
पूर्ण

अटल अंतरभूत व्योम
ecryptfs_set_superblock_lower(काष्ठा super_block *sb,
			      काष्ठा super_block *lower_sb)
अणु
	((काष्ठा ecryptfs_sb_info *)sb->s_fs_info)->wsi_sb = lower_sb;
पूर्ण

अटल अंतरभूत व्योम
ecryptfs_set_dentry_निजी(काष्ठा dentry *dentry,
			    काष्ठा ecryptfs_dentry_info *dentry_info)
अणु
	dentry->d_fsdata = dentry_info;
पूर्ण

अटल अंतरभूत काष्ठा dentry *
ecryptfs_dentry_to_lower(काष्ठा dentry *dentry)
अणु
	वापस ((काष्ठा ecryptfs_dentry_info *)dentry->d_fsdata)->lower_path.dentry;
पूर्ण

अटल अंतरभूत काष्ठा path *
ecryptfs_dentry_to_lower_path(काष्ठा dentry *dentry)
अणु
	वापस &((काष्ठा ecryptfs_dentry_info *)dentry->d_fsdata)->lower_path;
पूर्ण

#घोषणा ecryptfs_prपूर्णांकk(type, fmt, arg...) \
        __ecryptfs_prपूर्णांकk(type "%s: " fmt, __func__, ## arg)
__म_लिखो(1, 2)
व्योम __ecryptfs_prपूर्णांकk(स्थिर अक्षर *fmt, ...);

बाह्य स्थिर काष्ठा file_operations ecryptfs_मुख्य_fops;
बाह्य स्थिर काष्ठा file_operations ecryptfs_dir_fops;
बाह्य स्थिर काष्ठा inode_operations ecryptfs_मुख्य_iops;
बाह्य स्थिर काष्ठा inode_operations ecryptfs_dir_iops;
बाह्य स्थिर काष्ठा inode_operations ecryptfs_symlink_iops;
बाह्य स्थिर काष्ठा super_operations ecryptfs_sops;
बाह्य स्थिर काष्ठा dentry_operations ecryptfs_करोps;
बाह्य स्थिर काष्ठा address_space_operations ecryptfs_aops;
बाह्य पूर्णांक ecryptfs_verbosity;
बाह्य अचिन्हित पूर्णांक ecryptfs_message_buf_len;
बाह्य चिन्हित दीर्घ ecryptfs_message_रुको_समयout;
बाह्य अचिन्हित पूर्णांक ecryptfs_number_of_users;

बाह्य काष्ठा kmem_cache *ecryptfs_auth_tok_list_item_cache;
बाह्य काष्ठा kmem_cache *ecryptfs_file_info_cache;
बाह्य काष्ठा kmem_cache *ecryptfs_dentry_info_cache;
बाह्य काष्ठा kmem_cache *ecryptfs_inode_info_cache;
बाह्य काष्ठा kmem_cache *ecryptfs_sb_info_cache;
बाह्य काष्ठा kmem_cache *ecryptfs_header_cache;
बाह्य काष्ठा kmem_cache *ecryptfs_xattr_cache;
बाह्य काष्ठा kmem_cache *ecryptfs_key_record_cache;
बाह्य काष्ठा kmem_cache *ecryptfs_key_sig_cache;
बाह्य काष्ठा kmem_cache *ecryptfs_global_auth_tok_cache;
बाह्य काष्ठा kmem_cache *ecryptfs_key_tfm_cache;

काष्ठा inode *ecryptfs_get_inode(काष्ठा inode *lower_inode,
				 काष्ठा super_block *sb);
व्योम ecryptfs_i_size_init(स्थिर अक्षर *page_virt, काष्ठा inode *inode);
पूर्णांक ecryptfs_initialize_file(काष्ठा dentry *ecryptfs_dentry,
			     काष्ठा inode *ecryptfs_inode);
पूर्णांक ecryptfs_decode_and_decrypt_filename(अक्षर **decrypted_name,
					 माप_प्रकार *decrypted_name_size,
					 काष्ठा super_block *sb,
					 स्थिर अक्षर *name, माप_प्रकार name_size);
पूर्णांक ecryptfs_fill_zeros(काष्ठा file *file, loff_t new_length);
पूर्णांक ecryptfs_encrypt_and_encode_filename(
	अक्षर **encoded_name,
	माप_प्रकार *encoded_name_size,
	काष्ठा ecryptfs_mount_crypt_stat *mount_crypt_stat,
	स्थिर अक्षर *name, माप_प्रकार name_size);
काष्ठा dentry *ecryptfs_lower_dentry(काष्ठा dentry *this_dentry);
व्योम ecryptfs_dump_hex(अक्षर *data, पूर्णांक bytes);
पूर्णांक virt_to_scatterlist(स्थिर व्योम *addr, पूर्णांक size, काष्ठा scatterlist *sg,
			पूर्णांक sg_size);
पूर्णांक ecryptfs_compute_root_iv(काष्ठा ecryptfs_crypt_stat *crypt_stat);
व्योम ecryptfs_rotate_iv(अचिन्हित अक्षर *iv);
पूर्णांक ecryptfs_init_crypt_stat(काष्ठा ecryptfs_crypt_stat *crypt_stat);
व्योम ecryptfs_destroy_crypt_stat(काष्ठा ecryptfs_crypt_stat *crypt_stat);
व्योम ecryptfs_destroy_mount_crypt_stat(
	काष्ठा ecryptfs_mount_crypt_stat *mount_crypt_stat);
पूर्णांक ecryptfs_init_crypt_ctx(काष्ठा ecryptfs_crypt_stat *crypt_stat);
पूर्णांक ecryptfs_ग_लिखो_inode_माप_प्रकारo_metadata(काष्ठा inode *ecryptfs_inode);
पूर्णांक ecryptfs_encrypt_page(काष्ठा page *page);
पूर्णांक ecryptfs_decrypt_page(काष्ठा page *page);
पूर्णांक ecryptfs_ग_लिखो_metadata(काष्ठा dentry *ecryptfs_dentry,
			    काष्ठा inode *ecryptfs_inode);
पूर्णांक ecryptfs_पढ़ो_metadata(काष्ठा dentry *ecryptfs_dentry);
पूर्णांक ecryptfs_new_file_context(काष्ठा inode *ecryptfs_inode);
व्योम ecryptfs_ग_लिखो_crypt_stat_flags(अक्षर *page_virt,
				     काष्ठा ecryptfs_crypt_stat *crypt_stat,
				     माप_प्रकार *written);
पूर्णांक ecryptfs_पढ़ो_and_validate_header_region(काष्ठा inode *inode);
पूर्णांक ecryptfs_पढ़ो_and_validate_xattr_region(काष्ठा dentry *dentry,
					    काष्ठा inode *inode);
u8 ecryptfs_code_क्रम_cipher_string(अक्षर *cipher_name, माप_प्रकार key_bytes);
पूर्णांक ecryptfs_cipher_code_to_string(अक्षर *str, u8 cipher_code);
व्योम ecryptfs_set_शेष_sizes(काष्ठा ecryptfs_crypt_stat *crypt_stat);
पूर्णांक ecryptfs_generate_key_packet_set(अक्षर *dest_base,
				     काष्ठा ecryptfs_crypt_stat *crypt_stat,
				     काष्ठा dentry *ecryptfs_dentry,
				     माप_प्रकार *len, माप_प्रकार max);
पूर्णांक
ecryptfs_parse_packet_set(काष्ठा ecryptfs_crypt_stat *crypt_stat,
			  अचिन्हित अक्षर *src, काष्ठा dentry *ecryptfs_dentry);
पूर्णांक ecryptfs_truncate(काष्ठा dentry *dentry, loff_t new_length);
sमाप_प्रकार
ecryptfs_getxattr_lower(काष्ठा dentry *lower_dentry, काष्ठा inode *lower_inode,
			स्थिर अक्षर *name, व्योम *value, माप_प्रकार size);
पूर्णांक
ecryptfs_setxattr(काष्ठा dentry *dentry, काष्ठा inode *inode, स्थिर अक्षर *name,
		  स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags);
पूर्णांक ecryptfs_पढ़ो_xattr_region(अक्षर *page_virt, काष्ठा inode *ecryptfs_inode);
#अगर_घोषित CONFIG_ECRYPT_FS_MESSAGING
पूर्णांक ecryptfs_process_response(काष्ठा ecryptfs_daemon *daemon,
			      काष्ठा ecryptfs_message *msg, u32 seq);
पूर्णांक ecryptfs_send_message(अक्षर *data, पूर्णांक data_len,
			  काष्ठा ecryptfs_msg_ctx **msg_ctx);
पूर्णांक ecryptfs_रुको_क्रम_response(काष्ठा ecryptfs_msg_ctx *msg_ctx,
			       काष्ठा ecryptfs_message **emsg);
पूर्णांक ecryptfs_init_messaging(व्योम);
व्योम ecryptfs_release_messaging(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक ecryptfs_init_messaging(व्योम)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम ecryptfs_release_messaging(व्योम)
अणु पूर्ण
अटल अंतरभूत पूर्णांक ecryptfs_send_message(अक्षर *data, पूर्णांक data_len,
					काष्ठा ecryptfs_msg_ctx **msg_ctx)
अणु
	वापस -ENOTCONN;
पूर्ण
अटल अंतरभूत पूर्णांक ecryptfs_रुको_क्रम_response(काष्ठा ecryptfs_msg_ctx *msg_ctx,
					     काष्ठा ecryptfs_message **emsg)
अणु
	वापस -ENOMSG;
पूर्ण
#पूर्ण_अगर

व्योम
ecryptfs_ग_लिखो_header_metadata(अक्षर *virt,
			       काष्ठा ecryptfs_crypt_stat *crypt_stat,
			       माप_प्रकार *written);
पूर्णांक ecryptfs_add_keysig(काष्ठा ecryptfs_crypt_stat *crypt_stat, अक्षर *sig);
पूर्णांक
ecryptfs_add_global_auth_tok(काष्ठा ecryptfs_mount_crypt_stat *mount_crypt_stat,
			   अक्षर *sig, u32 global_auth_tok_flags);
पूर्णांक ecryptfs_get_global_auth_tok_क्रम_sig(
	काष्ठा ecryptfs_global_auth_tok **global_auth_tok,
	काष्ठा ecryptfs_mount_crypt_stat *mount_crypt_stat, अक्षर *sig);
पूर्णांक
ecryptfs_add_new_key_tfm(काष्ठा ecryptfs_key_tfm **key_tfm, अक्षर *cipher_name,
			 माप_प्रकार key_size);
पूर्णांक ecryptfs_init_crypto(व्योम);
पूर्णांक ecryptfs_destroy_crypto(व्योम);
पूर्णांक ecryptfs_tfm_exists(अक्षर *cipher_name, काष्ठा ecryptfs_key_tfm **key_tfm);
पूर्णांक ecryptfs_get_tfm_and_mutex_क्रम_cipher_name(काष्ठा crypto_skcipher **tfm,
					       काष्ठा mutex **tfm_mutex,
					       अक्षर *cipher_name);
पूर्णांक ecryptfs_keyring_auth_tok_क्रम_sig(काष्ठा key **auth_tok_key,
				      काष्ठा ecryptfs_auth_tok **auth_tok,
				      अक्षर *sig);
पूर्णांक ecryptfs_ग_लिखो_lower(काष्ठा inode *ecryptfs_inode, अक्षर *data,
			 loff_t offset, माप_प्रकार size);
पूर्णांक ecryptfs_ग_लिखो_lower_page_segment(काष्ठा inode *ecryptfs_inode,
				      काष्ठा page *page_क्रम_lower,
				      माप_प्रकार offset_in_page, माप_प्रकार size);
पूर्णांक ecryptfs_ग_लिखो(काष्ठा inode *inode, अक्षर *data, loff_t offset, माप_प्रकार size);
पूर्णांक ecryptfs_पढ़ो_lower(अक्षर *data, loff_t offset, माप_प्रकार size,
			काष्ठा inode *ecryptfs_inode);
पूर्णांक ecryptfs_पढ़ो_lower_page_segment(काष्ठा page *page_क्रम_ecryptfs,
				     pgoff_t page_index,
				     माप_प्रकार offset_in_page, माप_प्रकार size,
				     काष्ठा inode *ecryptfs_inode);
काष्ठा page *ecryptfs_get_locked_page(काष्ठा inode *inode, loff_t index);
पूर्णांक ecryptfs_parse_packet_length(अचिन्हित अक्षर *data, माप_प्रकार *size,
				 माप_प्रकार *length_size);
पूर्णांक ecryptfs_ग_लिखो_packet_length(अक्षर *dest, माप_प्रकार size,
				 माप_प्रकार *packet_size_length);
#अगर_घोषित CONFIG_ECRYPT_FS_MESSAGING
पूर्णांक ecryptfs_init_ecryptfs_miscdev(व्योम);
व्योम ecryptfs_destroy_ecryptfs_miscdev(व्योम);
पूर्णांक ecryptfs_send_miscdev(अक्षर *data, माप_प्रकार data_size,
			  काष्ठा ecryptfs_msg_ctx *msg_ctx, u8 msg_type,
			  u16 msg_flags, काष्ठा ecryptfs_daemon *daemon);
व्योम ecryptfs_msg_ctx_alloc_to_मुक्त(काष्ठा ecryptfs_msg_ctx *msg_ctx);
पूर्णांक
ecryptfs_spawn_daemon(काष्ठा ecryptfs_daemon **daemon, काष्ठा file *file);
पूर्णांक ecryptfs_exorcise_daemon(काष्ठा ecryptfs_daemon *daemon);
पूर्णांक ecryptfs_find_daemon_by_euid(काष्ठा ecryptfs_daemon **daemon);
#पूर्ण_अगर
पूर्णांक ecryptfs_init_kthपढ़ो(व्योम);
व्योम ecryptfs_destroy_kthपढ़ो(व्योम);
पूर्णांक ecryptfs_privileged_खोलो(काष्ठा file **lower_file,
			     काष्ठा dentry *lower_dentry,
			     काष्ठा vfsmount *lower_mnt,
			     स्थिर काष्ठा cred *cred);
पूर्णांक ecryptfs_get_lower_file(काष्ठा dentry *dentry, काष्ठा inode *inode);
व्योम ecryptfs_put_lower_file(काष्ठा inode *inode);
पूर्णांक
ecryptfs_ग_लिखो_tag_70_packet(अक्षर *dest, माप_प्रकार *reमुख्यing_bytes,
			     माप_प्रकार *packet_size,
			     काष्ठा ecryptfs_mount_crypt_stat *mount_crypt_stat,
			     अक्षर *filename, माप_प्रकार filename_size);
पूर्णांक
ecryptfs_parse_tag_70_packet(अक्षर **filename, माप_प्रकार *filename_size,
			     माप_प्रकार *packet_size,
			     काष्ठा ecryptfs_mount_crypt_stat *mount_crypt_stat,
			     अक्षर *data, माप_प्रकार max_packet_size);
पूर्णांक ecryptfs_set_f_namelen(दीर्घ *namelen, दीर्घ lower_namelen,
			   काष्ठा ecryptfs_mount_crypt_stat *mount_crypt_stat);
पूर्णांक ecryptfs_derive_iv(अक्षर *iv, काष्ठा ecryptfs_crypt_stat *crypt_stat,
		       loff_t offset);

बाह्य स्थिर काष्ठा xattr_handler *ecryptfs_xattr_handlers[];

#पूर्ण_अगर /* #अगर_अघोषित ECRYPTFS_KERNEL_H */
