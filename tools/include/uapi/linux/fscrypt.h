<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * fscrypt user API
 *
 * These ioctls can be used on fileप्रणालीs that support fscrypt.  See the
 * "User API" section of Documentation/fileप्रणालीs/fscrypt.rst.
 */
#अगर_अघोषित _UAPI_LINUX_FSCRYPT_H
#घोषणा _UAPI_LINUX_FSCRYPT_H

#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>

/* Encryption policy flags */
#घोषणा FSCRYPT_POLICY_FLAGS_PAD_4		0x00
#घोषणा FSCRYPT_POLICY_FLAGS_PAD_8		0x01
#घोषणा FSCRYPT_POLICY_FLAGS_PAD_16		0x02
#घोषणा FSCRYPT_POLICY_FLAGS_PAD_32		0x03
#घोषणा FSCRYPT_POLICY_FLAGS_PAD_MASK		0x03
#घोषणा FSCRYPT_POLICY_FLAG_सूचीECT_KEY		0x04
#घोषणा FSCRYPT_POLICY_FLAG_IV_INO_LBLK_64	0x08
#घोषणा FSCRYPT_POLICY_FLAG_IV_INO_LBLK_32	0x10

/* Encryption algorithms */
#घोषणा FSCRYPT_MODE_AES_256_XTS		1
#घोषणा FSCRYPT_MODE_AES_256_CTS		4
#घोषणा FSCRYPT_MODE_AES_128_CBC		5
#घोषणा FSCRYPT_MODE_AES_128_CTS		6
#घोषणा FSCRYPT_MODE_ADIANTUM			9
/* If adding a mode number > 9, update FSCRYPT_MODE_MAX in fscrypt_निजी.h */

/*
 * Legacy policy version; ad-hoc KDF and no key verअगरication.
 * For new encrypted directories, use fscrypt_policy_v2 instead.
 *
 * Careful: the .version field क्रम this is actually 0, not 1.
 */
#घोषणा FSCRYPT_POLICY_V1		0
#घोषणा FSCRYPT_KEY_DESCRIPTOR_SIZE	8
काष्ठा fscrypt_policy_v1 अणु
	__u8 version;
	__u8 contents_encryption_mode;
	__u8 filenames_encryption_mode;
	__u8 flags;
	__u8 master_key_descriptor[FSCRYPT_KEY_DESCRIPTOR_SIZE];
पूर्ण;

/*
 * Process-subscribed "logon" key description prefix and payload क्रमmat.
 * Deprecated; prefer FS_IOC_ADD_ENCRYPTION_KEY instead.
 */
#घोषणा FSCRYPT_KEY_DESC_PREFIX		"fscrypt:"
#घोषणा FSCRYPT_KEY_DESC_PREFIX_SIZE	8
#घोषणा FSCRYPT_MAX_KEY_SIZE		64
काष्ठा fscrypt_key अणु
	__u32 mode;
	__u8 raw[FSCRYPT_MAX_KEY_SIZE];
	__u32 size;
पूर्ण;

/*
 * New policy version with HKDF and key verअगरication (recommended).
 */
#घोषणा FSCRYPT_POLICY_V2		2
#घोषणा FSCRYPT_KEY_IDENTIFIER_SIZE	16
काष्ठा fscrypt_policy_v2 अणु
	__u8 version;
	__u8 contents_encryption_mode;
	__u8 filenames_encryption_mode;
	__u8 flags;
	__u8 __reserved[4];
	__u8 master_key_identअगरier[FSCRYPT_KEY_IDENTIFIER_SIZE];
पूर्ण;

/* Struct passed to FS_IOC_GET_ENCRYPTION_POLICY_EX */
काष्ठा fscrypt_get_policy_ex_arg अणु
	__u64 policy_size; /* input/output */
	जोड़ अणु
		__u8 version;
		काष्ठा fscrypt_policy_v1 v1;
		काष्ठा fscrypt_policy_v2 v2;
	पूर्ण policy; /* output */
पूर्ण;

/*
 * v1 policy keys are specअगरied by an arbitrary 8-byte key "descriptor",
 * matching fscrypt_policy_v1::master_key_descriptor.
 */
#घोषणा FSCRYPT_KEY_SPEC_TYPE_DESCRIPTOR	1

/*
 * v2 policy keys are specअगरied by a 16-byte key "identifier" which the kernel
 * calculates as a cryptographic hash of the key itself,
 * matching fscrypt_policy_v2::master_key_identअगरier.
 */
#घोषणा FSCRYPT_KEY_SPEC_TYPE_IDENTIFIER	2

/*
 * Specअगरies a key, either क्रम v1 or v2 policies.  This करोesn't contain the
 * actual key itself; this is just the "name" of the key.
 */
काष्ठा fscrypt_key_specअगरier अणु
	__u32 type;	/* one of FSCRYPT_KEY_SPEC_TYPE_* */
	__u32 __reserved;
	जोड़ अणु
		__u8 __reserved[32]; /* reserve some extra space */
		__u8 descriptor[FSCRYPT_KEY_DESCRIPTOR_SIZE];
		__u8 identअगरier[FSCRYPT_KEY_IDENTIFIER_SIZE];
	पूर्ण u;
पूर्ण;

/*
 * Payload of Linux keyring key of type "fscrypt-provisioning", referenced by
 * fscrypt_add_key_arg::key_id as an alternative to fscrypt_add_key_arg::raw.
 */
काष्ठा fscrypt_provisioning_key_payload अणु
	__u32 type;
	__u32 __reserved;
	__u8 raw[];
पूर्ण;

/* Struct passed to FS_IOC_ADD_ENCRYPTION_KEY */
काष्ठा fscrypt_add_key_arg अणु
	काष्ठा fscrypt_key_specअगरier key_spec;
	__u32 raw_size;
	__u32 key_id;
	__u32 __reserved[8];
	__u8 raw[];
पूर्ण;

/* Struct passed to FS_IOC_REMOVE_ENCRYPTION_KEY */
काष्ठा fscrypt_हटाओ_key_arg अणु
	काष्ठा fscrypt_key_specअगरier key_spec;
#घोषणा FSCRYPT_KEY_REMOVAL_STATUS_FLAG_खाताS_BUSY	0x00000001
#घोषणा FSCRYPT_KEY_REMOVAL_STATUS_FLAG_OTHER_USERS	0x00000002
	__u32 removal_status_flags;	/* output */
	__u32 __reserved[5];
पूर्ण;

/* Struct passed to FS_IOC_GET_ENCRYPTION_KEY_STATUS */
काष्ठा fscrypt_get_key_status_arg अणु
	/* input */
	काष्ठा fscrypt_key_specअगरier key_spec;
	__u32 __reserved[6];

	/* output */
#घोषणा FSCRYPT_KEY_STATUS_ABSENT		1
#घोषणा FSCRYPT_KEY_STATUS_PRESENT		2
#घोषणा FSCRYPT_KEY_STATUS_INCOMPLETELY_REMOVED	3
	__u32 status;
#घोषणा FSCRYPT_KEY_STATUS_FLAG_ADDED_BY_SELF   0x00000001
	__u32 status_flags;
	__u32 user_count;
	__u32 __out_reserved[13];
पूर्ण;

#घोषणा FS_IOC_SET_ENCRYPTION_POLICY		_IOR('f', 19, काष्ठा fscrypt_policy_v1)
#घोषणा FS_IOC_GET_ENCRYPTION_PWSALT		_IOW('f', 20, __u8[16])
#घोषणा FS_IOC_GET_ENCRYPTION_POLICY		_IOW('f', 21, काष्ठा fscrypt_policy_v1)
#घोषणा FS_IOC_GET_ENCRYPTION_POLICY_EX		_IOWR('f', 22, __u8[9]) /* size + version */
#घोषणा FS_IOC_ADD_ENCRYPTION_KEY		_IOWR('f', 23, काष्ठा fscrypt_add_key_arg)
#घोषणा FS_IOC_REMOVE_ENCRYPTION_KEY		_IOWR('f', 24, काष्ठा fscrypt_हटाओ_key_arg)
#घोषणा FS_IOC_REMOVE_ENCRYPTION_KEY_ALL_USERS	_IOWR('f', 25, काष्ठा fscrypt_हटाओ_key_arg)
#घोषणा FS_IOC_GET_ENCRYPTION_KEY_STATUS	_IOWR('f', 26, काष्ठा fscrypt_get_key_status_arg)
#घोषणा FS_IOC_GET_ENCRYPTION_NONCE		_IOR('f', 27, __u8[16])

/**********************************************************************/

/* old names; करोn't add anything new here! */
#अगर_अघोषित __KERNEL__
#घोषणा fscrypt_policy			fscrypt_policy_v1
#घोषणा FS_KEY_DESCRIPTOR_SIZE		FSCRYPT_KEY_DESCRIPTOR_SIZE
#घोषणा FS_POLICY_FLAGS_PAD_4		FSCRYPT_POLICY_FLAGS_PAD_4
#घोषणा FS_POLICY_FLAGS_PAD_8		FSCRYPT_POLICY_FLAGS_PAD_8
#घोषणा FS_POLICY_FLAGS_PAD_16		FSCRYPT_POLICY_FLAGS_PAD_16
#घोषणा FS_POLICY_FLAGS_PAD_32		FSCRYPT_POLICY_FLAGS_PAD_32
#घोषणा FS_POLICY_FLAGS_PAD_MASK	FSCRYPT_POLICY_FLAGS_PAD_MASK
#घोषणा FS_POLICY_FLAG_सूचीECT_KEY	FSCRYPT_POLICY_FLAG_सूचीECT_KEY
#घोषणा FS_POLICY_FLAGS_VALID		0x07	/* contains old flags only */
#घोषणा FS_ENCRYPTION_MODE_INVALID	0	/* never used */
#घोषणा FS_ENCRYPTION_MODE_AES_256_XTS	FSCRYPT_MODE_AES_256_XTS
#घोषणा FS_ENCRYPTION_MODE_AES_256_GCM	2	/* never used */
#घोषणा FS_ENCRYPTION_MODE_AES_256_CBC	3	/* never used */
#घोषणा FS_ENCRYPTION_MODE_AES_256_CTS	FSCRYPT_MODE_AES_256_CTS
#घोषणा FS_ENCRYPTION_MODE_AES_128_CBC	FSCRYPT_MODE_AES_128_CBC
#घोषणा FS_ENCRYPTION_MODE_AES_128_CTS	FSCRYPT_MODE_AES_128_CTS
#घोषणा FS_ENCRYPTION_MODE_SPECK128_256_XTS	7	/* हटाओd */
#घोषणा FS_ENCRYPTION_MODE_SPECK128_256_CTS	8	/* हटाओd */
#घोषणा FS_ENCRYPTION_MODE_ADIANTUM	FSCRYPT_MODE_ADIANTUM
#घोषणा FS_KEY_DESC_PREFIX		FSCRYPT_KEY_DESC_PREFIX
#घोषणा FS_KEY_DESC_PREFIX_SIZE		FSCRYPT_KEY_DESC_PREFIX_SIZE
#घोषणा FS_MAX_KEY_SIZE			FSCRYPT_MAX_KEY_SIZE
#पूर्ण_अगर /* !__KERNEL__ */

#पूर्ण_अगर /* _UAPI_LINUX_FSCRYPT_H */
