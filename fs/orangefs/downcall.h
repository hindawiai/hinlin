<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * (C) 2001 Clemson University and The University of Chicago
 *
 * See COPYING in top-level directory.
 */

/*
 *  Definitions of करोwncalls used in Linux kernel module.
 */

#अगर_अघोषित __DOWNCALL_H
#घोषणा __DOWNCALL_H

/*
 * Sanitized the device-client core पूर्णांकeraction
 * क्रम clean 32-64 bit usage
 */
काष्ठा orangefs_io_response अणु
	__s64 amt_complete;
पूर्ण;

काष्ठा orangefs_lookup_response अणु
	काष्ठा orangefs_object_kref refn;
पूर्ण;

काष्ठा orangefs_create_response अणु
	काष्ठा orangefs_object_kref refn;
पूर्ण;

काष्ठा orangefs_symlink_response अणु
	काष्ठा orangefs_object_kref refn;
पूर्ण;

काष्ठा orangefs_getattr_response अणु
	काष्ठा ORANGEFS_sys_attr_s attributes;
	अक्षर link_target[ORANGEFS_NAME_MAX];
पूर्ण;

काष्ठा orangefs_सूची_गढ़ो_response अणु
	काष्ठा orangefs_object_kref refn;
पूर्ण;

काष्ठा orangefs_statfs_response अणु
	__s64 block_size;
	__s64 blocks_total;
	__s64 blocks_avail;
	__s64 files_total;
	__s64 files_avail;
पूर्ण;

काष्ठा orangefs_fs_mount_response अणु
	__s32 fs_id;
	__s32 id;
	काष्ठा orangefs_khandle root_khandle;
पूर्ण;

/* the getxattr response is the attribute value */
काष्ठा orangefs_getxattr_response अणु
	__s32 val_sz;
	__s32 __pad1;
	अक्षर val[ORANGEFS_MAX_XATTR_VALUELEN];
पूर्ण;

/* the listxattr response is an array of attribute names */
काष्ठा orangefs_listxattr_response अणु
	__s32 वापसed_count;
	__s32 __pad1;
	__u64 token;
	अक्षर key[ORANGEFS_MAX_XATTR_LISTLEN * ORANGEFS_MAX_XATTR_NAMELEN];
	__s32 keylen;
	__s32 __pad2;
	__s32 lengths[ORANGEFS_MAX_XATTR_LISTLEN];
पूर्ण;

काष्ठा orangefs_param_response अणु
	जोड़ अणु
		__s64 value64;
		__s32 value32[2];
	पूर्ण u;
पूर्ण;

#घोषणा PERF_COUNT_BUF_SIZE 4096
काष्ठा orangefs_perf_count_response अणु
	अक्षर buffer[PERF_COUNT_BUF_SIZE];
पूर्ण;

#घोषणा FS_KEY_BUF_SIZE 4096
काष्ठा orangefs_fs_key_response अणु
	__s32 fs_keylen;
	__s32 __pad1;
	अक्षर fs_key[FS_KEY_BUF_SIZE];
पूर्ण;

/* 2.9.6 */
काष्ठा orangefs_features_response अणु
	__u64 features;
पूर्ण;

काष्ठा orangefs_करोwncall_s अणु
	__s32 type;
	__s32 status;
	/* currently trailer is used only by सूची_पढ़ो */
	__s64 trailer_size;
	अक्षर *trailer_buf;

	जोड़ अणु
		काष्ठा orangefs_io_response io;
		काष्ठा orangefs_lookup_response lookup;
		काष्ठा orangefs_create_response create;
		काष्ठा orangefs_symlink_response sym;
		काष्ठा orangefs_getattr_response getattr;
		काष्ठा orangefs_सूची_गढ़ो_response सूची_गढ़ो;
		काष्ठा orangefs_statfs_response statfs;
		काष्ठा orangefs_fs_mount_response fs_mount;
		काष्ठा orangefs_getxattr_response getxattr;
		काष्ठा orangefs_listxattr_response listxattr;
		काष्ठा orangefs_param_response param;
		काष्ठा orangefs_perf_count_response perf_count;
		काष्ठा orangefs_fs_key_response fs_key;
		काष्ठा orangefs_features_response features;
	पूर्ण resp;
पूर्ण;

/*
 * The सूची_पढ़ो response comes in the trailer.  It is followed by the
 * directory entries as described in dir.c.
 */

काष्ठा orangefs_सूची_पढ़ो_response_s अणु
	__u64 token;
	__u64 directory_version;
	__u32 __pad2;
	__u32 orangefs_dirent_outcount;
पूर्ण;

#पूर्ण_अगर /* __DOWNCALL_H */
