<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * fs-verity user API
 *
 * These ioctls can be used on fileप्रणालीs that support fs-verity.  See the
 * "User API" section of Documentation/fileप्रणालीs/fsverity.rst.
 *
 * Copyright 2019 Google LLC
 */
#अगर_अघोषित _UAPI_LINUX_FSVERITY_H
#घोषणा _UAPI_LINUX_FSVERITY_H

#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>

#घोषणा FS_VERITY_HASH_ALG_SHA256	1
#घोषणा FS_VERITY_HASH_ALG_SHA512	2

काष्ठा fsverity_enable_arg अणु
	__u32 version;
	__u32 hash_algorithm;
	__u32 block_size;
	__u32 salt_size;
	__u64 salt_ptr;
	__u32 sig_size;
	__u32 __reserved1;
	__u64 sig_ptr;
	__u64 __reserved2[11];
पूर्ण;

काष्ठा fsverity_digest अणु
	__u16 digest_algorithm;
	__u16 digest_size; /* input/output */
	__u8 digest[];
पूर्ण;

/*
 * Struct containing a file's Merkle tree properties.  The fs-verity file digest
 * is the hash of this काष्ठा.  A userspace program needs this काष्ठा only अगर it
 * needs to compute fs-verity file digests itself, e.g. in order to sign files.
 * It isn't needed just to enable fs-verity on a file.
 *
 * Note: when computing the file digest, 'sig_size' and 'signature' must be left
 * zero and empty, respectively.  These fields are present only because some
 * fileप्रणालीs reuse this काष्ठा as part of their on-disk क्रमmat.
 */
काष्ठा fsverity_descriptor अणु
	__u8 version;		/* must be 1 */
	__u8 hash_algorithm;	/* Merkle tree hash algorithm */
	__u8 log_blocksize;	/* log2 of size of data and tree blocks */
	__u8 salt_size;		/* size of salt in bytes; 0 अगर none */
#अगर_घोषित __KERNEL__
	__le32 sig_size;
#अन्यथा
	__le32 __reserved_0x04;	/* must be 0 */
#पूर्ण_अगर
	__le64 data_size;	/* size of file the Merkle tree is built over */
	__u8 root_hash[64];	/* Merkle tree root hash */
	__u8 salt[32];		/* salt prepended to each hashed block */
	__u8 __reserved[144];	/* must be 0's */
#अगर_घोषित __KERNEL__
	__u8 signature[];
#पूर्ण_अगर
पूर्ण;

/*
 * Format in which fs-verity file digests are चिन्हित in built-in signatures.
 * This is the same as 'struct fsverity_digest', except here some magic bytes
 * are prepended to provide some context about what is being चिन्हित in हाल the
 * same key is used क्रम non-fsverity purposes, and here the fields have fixed
 * endianness.
 *
 * This काष्ठा is specअगरic to the built-in signature verअगरication support, which
 * is optional.  fs-verity users may also verअगरy signatures in userspace, in
 * which हाल userspace is responsible क्रम deciding on what bytes are चिन्हित.
 * This काष्ठा may still be used, but it करोesn't have to be.  For example,
 * userspace could instead use a string like "sha256:$digest_as_hex_string".
 */
काष्ठा fsverity_क्रमmatted_digest अणु
	अक्षर magic[8];			/* must be "FSVerity" */
	__le16 digest_algorithm;
	__le16 digest_size;
	__u8 digest[];
पूर्ण;

#घोषणा FS_VERITY_METADATA_TYPE_MERKLE_TREE	1
#घोषणा FS_VERITY_METADATA_TYPE_DESCRIPTOR	2
#घोषणा FS_VERITY_METADATA_TYPE_SIGNATURE	3

काष्ठा fsverity_पढ़ो_metadata_arg अणु
	__u64 metadata_type;
	__u64 offset;
	__u64 length;
	__u64 buf_ptr;
	__u64 __reserved;
पूर्ण;

#घोषणा FS_IOC_ENABLE_VERITY	_IOW('f', 133, काष्ठा fsverity_enable_arg)
#घोषणा FS_IOC_MEASURE_VERITY	_IOWR('f', 134, काष्ठा fsverity_digest)
#घोषणा FS_IOC_READ_VERITY_METADATA \
	_IOWR('f', 135, काष्ठा fsverity_पढ़ो_metadata_arg)

#पूर्ण_अगर /* _UAPI_LINUX_FSVERITY_H */
