<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/spinlock_types.h>
#समावेश <linux/slab.h>
#समावेश <linux/ioctl.h>

/* khandle stuff  ***********************************************************/

/*
 * The 2.9 core will put 64 bit handles in here like this:
 *    1234 0000 0000 5678
 * The 3.0 and beyond cores will put 128 bit handles in here like this:
 *    1234 5678 90AB CDEF
 * The kernel module will always use the first four bytes and
 * the last four bytes as an inum.
 */
काष्ठा orangefs_khandle अणु
	अचिन्हित अक्षर u[16];
पूर्ण  __aligned(8);

/*
 * kernel version of an object ref.
 */
काष्ठा orangefs_object_kref अणु
	काष्ठा orangefs_khandle khandle;
	__s32 fs_id;
	__s32 __pad1;
पूर्ण;

/*
 * compare 2 khandles assumes little endian thus from large address to
 * small address
 */
अटल अंतरभूत पूर्णांक ORANGEFS_khandle_cmp(स्थिर काष्ठा orangefs_khandle *kh1,
				   स्थिर काष्ठा orangefs_khandle *kh2)
अणु
	पूर्णांक i;

	क्रम (i = 15; i >= 0; i--) अणु
		अगर (kh1->u[i] > kh2->u[i])
			वापस 1;
		अगर (kh1->u[i] < kh2->u[i])
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ORANGEFS_khandle_to(स्थिर काष्ठा orangefs_khandle *kh,
				   व्योम *p, पूर्णांक size)
अणु

	स_नकल(p, kh->u, 16);
	स_रखो(p + 16, 0, size - 16);

पूर्ण

अटल अंतरभूत व्योम ORANGEFS_khandle_from(काष्ठा orangefs_khandle *kh,
				     व्योम *p, पूर्णांक size)
अणु
	स_रखो(kh, 0, 16);
	स_नकल(kh->u, p, 16);

पूर्ण

/* pvfs2-types.h ************************************************************/

#घोषणा ORANGEFS_SUPER_MAGIC 0x20030528

/*
 * ORANGEFS error codes are a चिन्हित 32-bit पूर्णांकeger. Error codes are negative, but
 * the sign is stripped beक्रमe decoding.
 */

/* Bit 31 is not used since it is the sign. */

/*
 * Bit 30 specअगरies that this is a ORANGEFS error. A ORANGEFS error is either an
 * encoded त्रुटि_सं value or a ORANGEFS protocol error.
 */
#घोषणा ORANGEFS_ERROR_BIT (1 << 30)

/*
 * Bit 29 specअगरies that this is a ORANGEFS protocol error and not an encoded
 * त्रुटि_सं value.
 */
#घोषणा ORANGEFS_NON_ERRNO_ERROR_BIT (1 << 29)

/*
 * Bits 9, 8, and 7 specअगरy the error class, which encodes the section of
 * server code the error originated in क्रम logging purposes. It is not used
 * in the kernel except to be masked out.
 */
#घोषणा ORANGEFS_ERROR_CLASS_BITS 0x380

/* Bits 6 - 0 are reserved क्रम the actual error code. */
#घोषणा ORANGEFS_ERROR_NUMBER_BITS 0x7f

/* Encoded त्रुटि_सं values decoded by PINT_त्रुटि_सं_mapping in orangefs-utils.c. */

/* Our own ORANGEFS protocol error codes. */
#घोषणा ORANGEFS_ECANCEL    (1|ORANGEFS_NON_ERRNO_ERROR_BIT|ORANGEFS_ERROR_BIT)
#घोषणा ORANGEFS_EDEVINIT   (2|ORANGEFS_NON_ERRNO_ERROR_BIT|ORANGEFS_ERROR_BIT)
#घोषणा ORANGEFS_EDETAIL    (3|ORANGEFS_NON_ERRNO_ERROR_BIT|ORANGEFS_ERROR_BIT)
#घोषणा ORANGEFS_EHOSTNTFD  (4|ORANGEFS_NON_ERRNO_ERROR_BIT|ORANGEFS_ERROR_BIT)
#घोषणा ORANGEFS_EADDRNTFD  (5|ORANGEFS_NON_ERRNO_ERROR_BIT|ORANGEFS_ERROR_BIT)
#घोषणा ORANGEFS_ENORECVR   (6|ORANGEFS_NON_ERRNO_ERROR_BIT|ORANGEFS_ERROR_BIT)
#घोषणा ORANGEFS_ETRYAGAIN  (7|ORANGEFS_NON_ERRNO_ERROR_BIT|ORANGEFS_ERROR_BIT)
#घोषणा ORANGEFS_ENOTPVFS   (8|ORANGEFS_NON_ERRNO_ERROR_BIT|ORANGEFS_ERROR_BIT)
#घोषणा ORANGEFS_ESECURITY  (9|ORANGEFS_NON_ERRNO_ERROR_BIT|ORANGEFS_ERROR_BIT)

/* permission bits */
#घोषणा ORANGEFS_O_EXECUTE (1 << 0)
#घोषणा ORANGEFS_O_WRITE   (1 << 1)
#घोषणा ORANGEFS_O_READ    (1 << 2)
#घोषणा ORANGEFS_G_EXECUTE (1 << 3)
#घोषणा ORANGEFS_G_WRITE   (1 << 4)
#घोषणा ORANGEFS_G_READ    (1 << 5)
#घोषणा ORANGEFS_U_EXECUTE (1 << 6)
#घोषणा ORANGEFS_U_WRITE   (1 << 7)
#घोषणा ORANGEFS_U_READ    (1 << 8)
/* no ORANGEFS_U_VTX (sticky bit) */
#घोषणा ORANGEFS_G_SGID    (1 << 10)
#घोषणा ORANGEFS_U_SUID    (1 << 11)

#घोषणा ORANGEFS_ITERATE_START    2147483646
#घोषणा ORANGEFS_ITERATE_END      2147483645
#घोषणा ORANGEFS_IMMUTABLE_FL FS_IMMUTABLE_FL
#घोषणा ORANGEFS_APPEND_FL    FS_APPEND_FL
#घोषणा ORANGEFS_NOATIME_FL   FS_NOATIME_FL
#घोषणा ORANGEFS_MIRROR_FL    0x01000000ULL
#घोषणा ORANGEFS_FS_ID_शून्य       ((__s32)0)
#घोषणा ORANGEFS_ATTR_SYS_UID                   (1 << 0)
#घोषणा ORANGEFS_ATTR_SYS_GID                   (1 << 1)
#घोषणा ORANGEFS_ATTR_SYS_PERM                  (1 << 2)
#घोषणा ORANGEFS_ATTR_SYS_ATIME                 (1 << 3)
#घोषणा ORANGEFS_ATTR_SYS_CTIME                 (1 << 4)
#घोषणा ORANGEFS_ATTR_SYS_MTIME                 (1 << 5)
#घोषणा ORANGEFS_ATTR_SYS_TYPE                  (1 << 6)
#घोषणा ORANGEFS_ATTR_SYS_ATIME_SET             (1 << 7)
#घोषणा ORANGEFS_ATTR_SYS_MTIME_SET             (1 << 8)
#घोषणा ORANGEFS_ATTR_SYS_SIZE                  (1 << 20)
#घोषणा ORANGEFS_ATTR_SYS_LNK_TARGET            (1 << 24)
#घोषणा ORANGEFS_ATTR_SYS_Dखाता_COUNT           (1 << 25)
#घोषणा ORANGEFS_ATTR_SYS_सूचीENT_COUNT          (1 << 26)
#घोषणा ORANGEFS_ATTR_SYS_BLKSIZE               (1 << 28)
#घोषणा ORANGEFS_ATTR_SYS_MIRROR_COPIES_COUNT   (1 << 29)
#घोषणा ORANGEFS_ATTR_SYS_COMMON_ALL	\
	(ORANGEFS_ATTR_SYS_UID	|	\
	 ORANGEFS_ATTR_SYS_GID	|	\
	 ORANGEFS_ATTR_SYS_PERM	|	\
	 ORANGEFS_ATTR_SYS_ATIME	|	\
	 ORANGEFS_ATTR_SYS_CTIME	|	\
	 ORANGEFS_ATTR_SYS_MTIME	|	\
	 ORANGEFS_ATTR_SYS_TYPE)

#घोषणा ORANGEFS_ATTR_SYS_ALL_SETABLE		\
(ORANGEFS_ATTR_SYS_COMMON_ALL-ORANGEFS_ATTR_SYS_TYPE)

#घोषणा ORANGEFS_ATTR_SYS_ALL_NOHINT			\
	(ORANGEFS_ATTR_SYS_COMMON_ALL		|	\
	 ORANGEFS_ATTR_SYS_SIZE			|	\
	 ORANGEFS_ATTR_SYS_LNK_TARGET		|	\
	 ORANGEFS_ATTR_SYS_Dखाता_COUNT		|	\
	 ORANGEFS_ATTR_SYS_MIRROR_COPIES_COUNT	|	\
	 ORANGEFS_ATTR_SYS_सूचीENT_COUNT		|	\
	 ORANGEFS_ATTR_SYS_BLKSIZE)

#घोषणा ORANGEFS_XATTR_REPLACE 0x2
#घोषणा ORANGEFS_XATTR_CREATE  0x1
#घोषणा ORANGEFS_MAX_SERVER_ADDR_LEN 256
#घोषणा ORANGEFS_NAME_MAX                256
/*
 * max extended attribute name len as imposed by the VFS and exploited क्रम the
 * upcall request types.
 * NOTE: Please retain them as multiples of 8 even अगर you wish to change them
 * This is *NECESSARY* क्रम supporting 32 bit user-space binaries on a 64-bit
 * kernel. Due to implementation within DBPF, this really needs to be
 * ORANGEFS_NAME_MAX, which it was the same value as, but no reason to let it
 * अवरोध अगर that changes in the future.
 */
#घोषणा ORANGEFS_MAX_XATTR_NAMELEN   ORANGEFS_NAME_MAX	/* Not the same as
						 * XATTR_NAME_MAX defined
						 * by <linux/xattr.h>
						 */
#घोषणा ORANGEFS_MAX_XATTR_VALUELEN  8192	/* Not the same as XATTR_SIZE_MAX
					 * defined by <linux/xattr.h>
					 */
#घोषणा ORANGEFS_MAX_XATTR_LISTLEN   16	/* Not the same as XATTR_LIST_MAX
					 * defined by <linux/xattr.h>
					 */
/*
 * ORANGEFS I/O operation types, used in both प्रणाली and server पूर्णांकerfaces.
 */
क्रमागत ORANGEFS_io_type अणु
	ORANGEFS_IO_READ = 1,
	ORANGEFS_IO_WRITE = 2
पूर्ण;

/*
 * If this क्रमागत is modअगरied the server parameters related to the precreate pool
 * batch and low threshold sizes may need to be modअगरied  to reflect this
 * change.
 */
क्रमागत orangefs_ds_type अणु
	ORANGEFS_TYPE_NONE = 0,
	ORANGEFS_TYPE_METAखाता = (1 << 0),
	ORANGEFS_TYPE_DATAखाता = (1 << 1),
	ORANGEFS_TYPE_सूचीECTORY = (1 << 2),
	ORANGEFS_TYPE_SYMLINK = (1 << 3),
	ORANGEFS_TYPE_सूचीDATA = (1 << 4),
	ORANGEFS_TYPE_INTERNAL = (1 << 5)	/* क्रम the server's निजी use */
पूर्ण;

/* This काष्ठाure is used by the VFS-client पूर्णांकeraction alone */
काष्ठा ORANGEFS_keyval_pair अणु
	अक्षर key[ORANGEFS_MAX_XATTR_NAMELEN];
	__s32 key_sz;	/* __s32 क्रम portable, fixed-size काष्ठाures */
	__s32 val_sz;
	अक्षर val[ORANGEFS_MAX_XATTR_VALUELEN];
पूर्ण;

/* pvfs2-sysपूर्णांक.h ***********************************************************/
/* Describes attributes क्रम a file, directory, or symlink. */
काष्ठा ORANGEFS_sys_attr_s अणु
	__u32 owner;
	__u32 group;
	__u32 perms;
	__u64 aसमय;
	__u64 mसमय;
	__u64 स_समय;
	__s64 size;

	/* NOTE: caller must मुक्त अगर valid */
	अक्षर *link_target;

	/* Changed to __s32 so that size of काष्ठाure करोes not change */
	__s32 dfile_count;

	/* Changed to __s32 so that size of काष्ठाure करोes not change */
	__s32 distr_dir_servers_initial;

	/* Changed to __s32 so that size of काष्ठाure करोes not change */
	__s32 distr_dir_servers_max;

	/* Changed to __s32 so that size of काष्ठाure करोes not change */
	__s32 distr_dir_split_size;

	__u32 mirror_copies_count;

	/* NOTE: caller must मुक्त अगर valid */
	अक्षर *dist_name;

	/* NOTE: caller must मुक्त अगर valid */
	अक्षर *dist_params;

	__s64 dirent_count;
	क्रमागत orangefs_ds_type objtype;
	__u64 flags;
	__u32 mask;
	__s64 blksize;
पूर्ण;

#घोषणा ORANGEFS_LOOKUP_LINK_NO_FOLLOW 0

/* pपूर्णांक-dev.h ***************************************************************/

/* parameter काष्ठाure used in ORANGEFS_DEV_DEBUG ioctl command */
काष्ठा dev_mask_info_s अणु
	क्रमागत अणु
		KERNEL_MASK,
		CLIENT_MASK,
	पूर्ण mask_type;
	__u64 mask_value;
पूर्ण;

काष्ठा dev_mask2_info_s अणु
	__u64 mask1_value;
	__u64 mask2_value;
पूर्ण;

/* pvfs2-util.h *************************************************************/
__s32 ORANGEFS_util_translate_mode(पूर्णांक mode);

/* pvfs2-debug.h ************************************************************/
#समावेश "orangefs-debug.h"

/* pvfs2-पूर्णांकernal.h *********************************************************/
#घोषणा llu(x) (अचिन्हित दीर्घ दीर्घ)(x)
#घोषणा lld(x) (दीर्घ दीर्घ)(x)

/* pपूर्णांक-dev-shared.h ********************************************************/
#घोषणा ORANGEFS_DEV_MAGIC 'k'

#घोषणा ORANGEFS_READसूची_DEFAULT_DESC_COUNT  5

#घोषणा DEV_GET_MAGIC           0x1
#घोषणा DEV_GET_MAX_UPSIZE      0x2
#घोषणा DEV_GET_MAX_DOWNSIZE    0x3
#घोषणा DEV_MAP                 0x4
#घोषणा DEV_REMOUNT_ALL         0x5
#घोषणा DEV_DEBUG               0x6
#घोषणा DEV_UPSTREAM            0x7
#घोषणा DEV_CLIENT_MASK         0x8
#घोषणा DEV_CLIENT_STRING       0x9
#घोषणा DEV_MAX_NR              0xa

/* supported ioctls, codes are with respect to user-space */
क्रमागत अणु
	ORANGEFS_DEV_GET_MAGIC = _IOW(ORANGEFS_DEV_MAGIC, DEV_GET_MAGIC, __s32),
	ORANGEFS_DEV_GET_MAX_UPSIZE =
	    _IOW(ORANGEFS_DEV_MAGIC, DEV_GET_MAX_UPSIZE, __s32),
	ORANGEFS_DEV_GET_MAX_DOWNSIZE =
	    _IOW(ORANGEFS_DEV_MAGIC, DEV_GET_MAX_DOWNSIZE, __s32),
	ORANGEFS_DEV_MAP = _IO(ORANGEFS_DEV_MAGIC, DEV_MAP),
	ORANGEFS_DEV_REMOUNT_ALL = _IO(ORANGEFS_DEV_MAGIC, DEV_REMOUNT_ALL),
	ORANGEFS_DEV_DEBUG = _IOR(ORANGEFS_DEV_MAGIC, DEV_DEBUG, __s32),
	ORANGEFS_DEV_UPSTREAM = _IOW(ORANGEFS_DEV_MAGIC, DEV_UPSTREAM, पूर्णांक),
	ORANGEFS_DEV_CLIENT_MASK = _IOW(ORANGEFS_DEV_MAGIC,
				    DEV_CLIENT_MASK,
				    काष्ठा dev_mask2_info_s),
	ORANGEFS_DEV_CLIENT_STRING = _IOW(ORANGEFS_DEV_MAGIC,
				      DEV_CLIENT_STRING,
				      अक्षर *),
	ORANGEFS_DEV_MAXNR = DEV_MAX_NR,
पूर्ण;

/*
 * version number क्रम use in communicating between kernel space and user
 * space. Zero signअगरies the upstream version of the kernel module.
 */
#घोषणा ORANGEFS_KERNEL_PROTO_VERSION 0
#घोषणा ORANGEFS_MINIMUM_USERSPACE_VERSION 20903

/*
 * describes memory regions to map in the ORANGEFS_DEV_MAP ioctl.
 * NOTE: See devorangefs-req.c क्रम 32 bit compat काष्ठाure.
 * Since this काष्ठाure has a variable-sized layout that is dअगरferent
 * on 32 and 64 bit platक्रमms, we need to normalize to a 64 bit layout
 * on such प्रणालीs beक्रमe servicing ioctl calls from user-space binaries
 * that may be 32 bit!
 */
काष्ठा ORANGEFS_dev_map_desc अणु
	व्योम __user *ptr;
	__s32 total_size;
	__s32 size;
	__s32 count;
पूर्ण;

/* gossip.h *****************************************************************/

बाह्य __u64 orangefs_gossip_debug_mask;

/* try to aव्योम function call overhead by checking masks in macro */
#घोषणा gossip_debug(mask, fmt, ...)					\
करो अणु									\
	अगर (orangefs_gossip_debug_mask & (mask))			\
		prपूर्णांकk(KERN_DEBUG fmt, ##__VA_ARGS__);			\
पूर्ण जबतक (0)

#घोषणा gossip_err pr_err
