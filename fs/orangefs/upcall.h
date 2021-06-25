<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * (C) 2001 Clemson University and The University of Chicago
 *
 * See COPYING in top-level directory.
 */

#अगर_अघोषित __UPCALL_H
#घोषणा __UPCALL_H

/*
 * Sanitized this header file to fix
 * 32-64 bit पूर्णांकeraction issues between
 * client-core and device
 */
काष्ठा orangefs_io_request_s अणु
	__s32 __pad1;
	__s32 buf_index;
	__s32 count;
	__s32 __pad2;
	__s64 offset;
	काष्ठा orangefs_object_kref refn;
	क्रमागत ORANGEFS_io_type io_type;
	__s32 पढ़ोahead_size;
पूर्ण;

काष्ठा orangefs_lookup_request_s अणु
	__s32 sym_follow;
	__s32 __pad1;
	काष्ठा orangefs_object_kref parent_refn;
	अक्षर d_name[ORANGEFS_NAME_MAX];
पूर्ण;

काष्ठा orangefs_create_request_s अणु
	काष्ठा orangefs_object_kref parent_refn;
	काष्ठा ORANGEFS_sys_attr_s attributes;
	अक्षर d_name[ORANGEFS_NAME_MAX];
पूर्ण;

काष्ठा orangefs_symlink_request_s अणु
	काष्ठा orangefs_object_kref parent_refn;
	काष्ठा ORANGEFS_sys_attr_s attributes;
	अक्षर entry_name[ORANGEFS_NAME_MAX];
	अक्षर target[ORANGEFS_NAME_MAX];
पूर्ण;

काष्ठा orangefs_getattr_request_s अणु
	काष्ठा orangefs_object_kref refn;
	__u32 mask;
	__u32 __pad1;
पूर्ण;

काष्ठा orangefs_setattr_request_s अणु
	काष्ठा orangefs_object_kref refn;
	काष्ठा ORANGEFS_sys_attr_s attributes;
पूर्ण;

काष्ठा orangefs_हटाओ_request_s अणु
	काष्ठा orangefs_object_kref parent_refn;
	अक्षर d_name[ORANGEFS_NAME_MAX];
पूर्ण;

काष्ठा orangefs_सूची_गढ़ो_request_s अणु
	काष्ठा orangefs_object_kref parent_refn;
	काष्ठा ORANGEFS_sys_attr_s attributes;
	अक्षर d_name[ORANGEFS_NAME_MAX];
पूर्ण;

काष्ठा orangefs_सूची_पढ़ो_request_s अणु
	काष्ठा orangefs_object_kref refn;
	__u64 token;
	__s32 max_dirent_count;
	__s32 buf_index;
पूर्ण;

काष्ठा orangefs_सूची_पढ़ोplus_request_s अणु
	काष्ठा orangefs_object_kref refn;
	__u64 token;
	__s32 max_dirent_count;
	__u32 mask;
	__s32 buf_index;
	__s32 __pad1;
पूर्ण;

काष्ठा orangefs_नाम_request_s अणु
	काष्ठा orangefs_object_kref old_parent_refn;
	काष्ठा orangefs_object_kref new_parent_refn;
	अक्षर d_old_name[ORANGEFS_NAME_MAX];
	अक्षर d_new_name[ORANGEFS_NAME_MAX];
पूर्ण;

काष्ठा orangefs_statfs_request_s अणु
	__s32 fs_id;
	__s32 __pad1;
पूर्ण;

काष्ठा orangefs_truncate_request_s अणु
	काष्ठा orangefs_object_kref refn;
	__s64 size;
पूर्ण;

काष्ठा orangefs_ra_cache_flush_request_s अणु
	काष्ठा orangefs_object_kref refn;
पूर्ण;

काष्ठा orangefs_fs_mount_request_s अणु
	अक्षर orangefs_config_server[ORANGEFS_MAX_SERVER_ADDR_LEN];
पूर्ण;

काष्ठा orangefs_fs_umount_request_s अणु
	__s32 id;
	__s32 fs_id;
	अक्षर orangefs_config_server[ORANGEFS_MAX_SERVER_ADDR_LEN];
पूर्ण;

काष्ठा orangefs_getxattr_request_s अणु
	काष्ठा orangefs_object_kref refn;
	__s32 key_sz;
	__s32 __pad1;
	अक्षर key[ORANGEFS_MAX_XATTR_NAMELEN];
पूर्ण;

काष्ठा orangefs_setxattr_request_s अणु
	काष्ठा orangefs_object_kref refn;
	काष्ठा ORANGEFS_keyval_pair keyval;
	__s32 flags;
	__s32 __pad1;
पूर्ण;

काष्ठा orangefs_listxattr_request_s अणु
	काष्ठा orangefs_object_kref refn;
	__s32 requested_count;
	__s32 __pad1;
	__u64 token;
पूर्ण;

काष्ठा orangefs_हटाओxattr_request_s अणु
	काष्ठा orangefs_object_kref refn;
	__s32 key_sz;
	__s32 __pad1;
	अक्षर key[ORANGEFS_MAX_XATTR_NAMELEN];
पूर्ण;

काष्ठा orangefs_op_cancel_s अणु
	__u64 op_tag;
पूर्ण;

काष्ठा orangefs_fsync_request_s अणु
	काष्ठा orangefs_object_kref refn;
पूर्ण;

क्रमागत orangefs_param_request_type अणु
	ORANGEFS_PARAM_REQUEST_SET = 1,
	ORANGEFS_PARAM_REQUEST_GET = 2
पूर्ण;

क्रमागत orangefs_param_request_op अणु
	ORANGEFS_PARAM_REQUEST_OP_ACACHE_TIMEOUT_MSECS = 1,
	ORANGEFS_PARAM_REQUEST_OP_ACACHE_HARD_LIMIT = 2,
	ORANGEFS_PARAM_REQUEST_OP_ACACHE_SOFT_LIMIT = 3,
	ORANGEFS_PARAM_REQUEST_OP_ACACHE_RECLAIM_PERCENTAGE = 4,
	ORANGEFS_PARAM_REQUEST_OP_PERF_TIME_INTERVAL_SECS = 5,
	ORANGEFS_PARAM_REQUEST_OP_PERF_HISTORY_SIZE = 6,
	ORANGEFS_PARAM_REQUEST_OP_PERF_RESET = 7,
	ORANGEFS_PARAM_REQUEST_OP_NCACHE_TIMEOUT_MSECS = 8,
	ORANGEFS_PARAM_REQUEST_OP_NCACHE_HARD_LIMIT = 9,
	ORANGEFS_PARAM_REQUEST_OP_NCACHE_SOFT_LIMIT = 10,
	ORANGEFS_PARAM_REQUEST_OP_NCACHE_RECLAIM_PERCENTAGE = 11,
	ORANGEFS_PARAM_REQUEST_OP_STATIC_ACACHE_TIMEOUT_MSECS = 12,
	ORANGEFS_PARAM_REQUEST_OP_STATIC_ACACHE_HARD_LIMIT = 13,
	ORANGEFS_PARAM_REQUEST_OP_STATIC_ACACHE_SOFT_LIMIT = 14,
	ORANGEFS_PARAM_REQUEST_OP_STATIC_ACACHE_RECLAIM_PERCENTAGE = 15,
	ORANGEFS_PARAM_REQUEST_OP_CLIENT_DEBUG = 16,
	ORANGEFS_PARAM_REQUEST_OP_CCACHE_TIMEOUT_SECS = 17,
	ORANGEFS_PARAM_REQUEST_OP_CCACHE_HARD_LIMIT = 18,
	ORANGEFS_PARAM_REQUEST_OP_CCACHE_SOFT_LIMIT = 19,
	ORANGEFS_PARAM_REQUEST_OP_CCACHE_RECLAIM_PERCENTAGE = 20,
	ORANGEFS_PARAM_REQUEST_OP_CAPCACHE_TIMEOUT_SECS = 21,
	ORANGEFS_PARAM_REQUEST_OP_CAPCACHE_HARD_LIMIT = 22,
	ORANGEFS_PARAM_REQUEST_OP_CAPCACHE_SOFT_LIMIT = 23,
	ORANGEFS_PARAM_REQUEST_OP_CAPCACHE_RECLAIM_PERCENTAGE = 24,
	ORANGEFS_PARAM_REQUEST_OP_TWO_MASK_VALUES = 25,
	ORANGEFS_PARAM_REQUEST_OP_READAHEAD_SIZE = 26,
	ORANGEFS_PARAM_REQUEST_OP_READAHEAD_COUNT = 27,
	ORANGEFS_PARAM_REQUEST_OP_READAHEAD_COUNT_SIZE = 28,
	ORANGEFS_PARAM_REQUEST_OP_READAHEAD_READCNT = 29,
पूर्ण;

काष्ठा orangefs_param_request_s अणु
	क्रमागत orangefs_param_request_type type;
	क्रमागत orangefs_param_request_op op;
	जोड़ अणु
		__s64 value64;
		__s32 value32[2];
	पूर्ण u;
	अक्षर s_value[ORANGEFS_MAX_DEBUG_STRING_LEN];
पूर्ण;

क्रमागत orangefs_perf_count_request_type अणु
	ORANGEFS_PERF_COUNT_REQUEST_ACACHE = 1,
	ORANGEFS_PERF_COUNT_REQUEST_NCACHE = 2,
	ORANGEFS_PERF_COUNT_REQUEST_CAPCACHE = 3,
पूर्ण;

काष्ठा orangefs_perf_count_request_s अणु
	क्रमागत orangefs_perf_count_request_type type;
	__s32 __pad1;
पूर्ण;

काष्ठा orangefs_fs_key_request_s अणु
	__s32 fsid;
	__s32 __pad1;
पूर्ण;

/* 2.9.6 */
काष्ठा orangefs_features_request_s अणु
	__u64 features;
पूर्ण;

काष्ठा orangefs_upcall_s अणु
	__s32 type;
	__u32 uid;
	__u32 gid;
	पूर्णांक pid;
	पूर्णांक tgid;
	/* Trailers unused but must be retained क्रम protocol compatibility. */
	__s64 trailer_size;
	अक्षर *trailer_buf;

	जोड़ अणु
		काष्ठा orangefs_io_request_s io;
		काष्ठा orangefs_lookup_request_s lookup;
		काष्ठा orangefs_create_request_s create;
		काष्ठा orangefs_symlink_request_s sym;
		काष्ठा orangefs_getattr_request_s getattr;
		काष्ठा orangefs_setattr_request_s setattr;
		काष्ठा orangefs_हटाओ_request_s हटाओ;
		काष्ठा orangefs_सूची_गढ़ो_request_s सूची_गढ़ो;
		काष्ठा orangefs_सूची_पढ़ो_request_s सूची_पढ़ो;
		काष्ठा orangefs_सूची_पढ़ोplus_request_s सूची_पढ़ोplus;
		काष्ठा orangefs_नाम_request_s नाम;
		काष्ठा orangefs_statfs_request_s statfs;
		काष्ठा orangefs_truncate_request_s truncate;
		काष्ठा orangefs_ra_cache_flush_request_s ra_cache_flush;
		काष्ठा orangefs_fs_mount_request_s fs_mount;
		काष्ठा orangefs_fs_umount_request_s fs_umount;
		काष्ठा orangefs_getxattr_request_s getxattr;
		काष्ठा orangefs_setxattr_request_s setxattr;
		काष्ठा orangefs_listxattr_request_s listxattr;
		काष्ठा orangefs_हटाओxattr_request_s हटाओxattr;
		काष्ठा orangefs_op_cancel_s cancel;
		काष्ठा orangefs_fsync_request_s fsync;
		काष्ठा orangefs_param_request_s param;
		काष्ठा orangefs_perf_count_request_s perf_count;
		काष्ठा orangefs_fs_key_request_s fs_key;
		काष्ठा orangefs_features_request_s features;
	पूर्ण req;
पूर्ण;

#पूर्ण_अगर /* __UPCALL_H */
