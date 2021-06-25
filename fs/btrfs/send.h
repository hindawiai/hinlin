<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2012 Alexander Block.  All rights reserved.
 * Copyright (C) 2012 STRATO.  All rights reserved.
 */

#अगर_अघोषित BTRFS_SEND_H
#घोषणा BTRFS_SEND_H

#समावेश "ctree.h"

#घोषणा BTRFS_SEND_STREAM_MAGIC "btrfs-stream"
#घोषणा BTRFS_SEND_STREAM_VERSION 1

#घोषणा BTRFS_SEND_BUF_SIZE SZ_64K

क्रमागत btrfs_tlv_type अणु
	BTRFS_TLV_U8,
	BTRFS_TLV_U16,
	BTRFS_TLV_U32,
	BTRFS_TLV_U64,
	BTRFS_TLV_BINARY,
	BTRFS_TLV_STRING,
	BTRFS_TLV_UUID,
	BTRFS_TLV_TIMESPEC,
पूर्ण;

काष्ठा btrfs_stream_header अणु
	अक्षर magic[माप(BTRFS_SEND_STREAM_MAGIC)];
	__le32 version;
पूर्ण __attribute__ ((__packed__));

काष्ठा btrfs_cmd_header अणु
	/* len excluding the header */
	__le32 len;
	__le16 cmd;
	/* crc including the header with zero crc field */
	__le32 crc;
पूर्ण __attribute__ ((__packed__));

काष्ठा btrfs_tlv_header अणु
	__le16 tlv_type;
	/* len excluding the header */
	__le16 tlv_len;
पूर्ण __attribute__ ((__packed__));

/* commands */
क्रमागत btrfs_send_cmd अणु
	BTRFS_SEND_C_UNSPEC,

	BTRFS_SEND_C_SUBVOL,
	BTRFS_SEND_C_SNAPSHOT,

	BTRFS_SEND_C_MKखाता,
	BTRFS_SEND_C_MKसूची,
	BTRFS_SEND_C_MKNOD,
	BTRFS_SEND_C_MKFIFO,
	BTRFS_SEND_C_MKSOCK,
	BTRFS_SEND_C_SYMLINK,

	BTRFS_SEND_C_RENAME,
	BTRFS_SEND_C_LINK,
	BTRFS_SEND_C_UNLINK,
	BTRFS_SEND_C_RMसूची,

	BTRFS_SEND_C_SET_XATTR,
	BTRFS_SEND_C_REMOVE_XATTR,

	BTRFS_SEND_C_WRITE,
	BTRFS_SEND_C_CLONE,

	BTRFS_SEND_C_TRUNCATE,
	BTRFS_SEND_C_CHMOD,
	BTRFS_SEND_C_CHOWN,
	BTRFS_SEND_C_UTIMES,

	BTRFS_SEND_C_END,
	BTRFS_SEND_C_UPDATE_EXTENT,
	__BTRFS_SEND_C_MAX,
पूर्ण;
#घोषणा BTRFS_SEND_C_MAX (__BTRFS_SEND_C_MAX - 1)

/* attributes in send stream */
क्रमागत अणु
	BTRFS_SEND_A_UNSPEC,

	BTRFS_SEND_A_UUID,
	BTRFS_SEND_A_CTRANSID,

	BTRFS_SEND_A_INO,
	BTRFS_SEND_A_SIZE,
	BTRFS_SEND_A_MODE,
	BTRFS_SEND_A_UID,
	BTRFS_SEND_A_GID,
	BTRFS_SEND_A_RDEV,
	BTRFS_SEND_A_CTIME,
	BTRFS_SEND_A_MTIME,
	BTRFS_SEND_A_ATIME,
	BTRFS_SEND_A_OTIME,

	BTRFS_SEND_A_XATTR_NAME,
	BTRFS_SEND_A_XATTR_DATA,

	BTRFS_SEND_A_PATH,
	BTRFS_SEND_A_PATH_TO,
	BTRFS_SEND_A_PATH_LINK,

	BTRFS_SEND_A_खाता_OFFSET,
	BTRFS_SEND_A_DATA,

	BTRFS_SEND_A_CLONE_UUID,
	BTRFS_SEND_A_CLONE_CTRANSID,
	BTRFS_SEND_A_CLONE_PATH,
	BTRFS_SEND_A_CLONE_OFFSET,
	BTRFS_SEND_A_CLONE_LEN,

	__BTRFS_SEND_A_MAX,
पूर्ण;
#घोषणा BTRFS_SEND_A_MAX (__BTRFS_SEND_A_MAX - 1)

#अगर_घोषित __KERNEL__
दीर्घ btrfs_ioctl_send(काष्ठा file *mnt_file, काष्ठा btrfs_ioctl_send_args *arg);
#पूर्ण_अगर

#पूर्ण_अगर
