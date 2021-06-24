<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * VirtualBox Shared Folders: host पूर्णांकerface definition.
 *
 * Copyright (C) 2006-2018 Oracle Corporation
 */

#अगर_अघोषित SHFL_HOSTINTF_H
#घोषणा SHFL_HOSTINTF_H

#समावेश <linux/vbox_vmmdev_types.h>

/* The max in/out buffer size क्रम a FN_READ or FN_WRITE call */
#घोषणा SHFL_MAX_RW_COUNT           (16 * SZ_1M)

/*
 * Structures shared between guest and the service
 * can be relocated and use offsets to poपूर्णांक to variable
 * length parts.
 *
 * Shared folders protocol works with handles.
 * Beक्रमe करोing any action on a file प्रणाली object,
 * one have to obtain the object handle via a SHFL_FN_CREATE
 * request. A handle must be बंदd with SHFL_FN_CLOSE.
 */

क्रमागत अणु
	SHFL_FN_QUERY_MAPPINGS = 1,	/* Query mappings changes. */
	SHFL_FN_QUERY_MAP_NAME = 2,	/* Query map name. */
	SHFL_FN_CREATE = 3,		/* Open/create object. */
	SHFL_FN_CLOSE = 4,		/* Close object handle. */
	SHFL_FN_READ = 5,		/* Read object content. */
	SHFL_FN_WRITE = 6,		/* Write new object content. */
	SHFL_FN_LOCK = 7,		/* Lock/unlock a range in the object. */
	SHFL_FN_LIST = 8,		/* List object content. */
	SHFL_FN_INFORMATION = 9,	/* Query/set object inक्रमmation. */
	/* Note function number 10 is not used! */
	SHFL_FN_REMOVE = 11,		/* Remove object */
	SHFL_FN_MAP_FOLDER_OLD = 12,	/* Map folder (legacy) */
	SHFL_FN_UNMAP_FOLDER = 13,	/* Unmap folder */
	SHFL_FN_RENAME = 14,		/* Rename object */
	SHFL_FN_FLUSH = 15,		/* Flush file */
	SHFL_FN_SET_UTF8 = 16,		/* Select UTF8 filename encoding */
	SHFL_FN_MAP_FOLDER = 17,	/* Map folder */
	SHFL_FN_READLINK = 18,		/* Read symlink dest (as of VBox 4.0) */
	SHFL_FN_SYMLINK = 19,		/* Create symlink (as of VBox 4.0) */
	SHFL_FN_SET_SYMLINKS = 20,	/* Ask host to show symlinks (4.0+) */
पूर्ण;

/* Root handles क्रम a mapping are of type u32, Root handles are unique. */
#घोषणा SHFL_ROOT_NIL		अच_पूर्णांक_उच्च

/* Shared folders handle क्रम an खोलोed object are of type u64. */
#घोषणा SHFL_HANDLE_NIL		ULदीर्घ_उच्च

/* Hardcoded maximum length (in अक्षरs) of a shared folder name. */
#घोषणा SHFL_MAX_LEN         (256)
/* Hardcoded maximum number of shared folder mapping available to the guest. */
#घोषणा SHFL_MAX_MAPPINGS    (64)

/** Shared folder string buffer काष्ठाure. */
काष्ठा shfl_string अणु
	/** Allocated size of the string member in bytes. */
	u16 size;

	/** Length of string without trailing nul in bytes. */
	u16 length;

	/** UTF-8 or UTF-16 string. Nul terminated. */
	जोड़ अणु
		u8 utf8[2];
		u16 utf16[1];
		u16 ucs2[1]; /* misnomer, use utf16. */
	पूर्ण string;
पूर्ण;
VMMDEV_ASSERT_SIZE(shfl_string, 6);

/* The size of shfl_string w/o the string part. */
#घोषणा SHFLSTRING_HEADER_SIZE  4

/* Calculate size of the string. */
अटल अंतरभूत u32 shfl_string_buf_size(स्थिर काष्ठा shfl_string *string)
अणु
	वापस string ? SHFLSTRING_HEADER_SIZE + string->size : 0;
पूर्ण

/* Set user id on execution (S_ISUID). */
#घोषणा SHFL_UNIX_ISUID             0004000U
/* Set group id on execution (S_ISGID). */
#घोषणा SHFL_UNIX_ISGID             0002000U
/* Sticky bit (S_ISVTX / S_ISTXT). */
#घोषणा SHFL_UNIX_ISTXT             0001000U

/* Owner पढ़ोable (S_IRUSR). */
#घोषणा SHFL_UNIX_IRUSR             0000400U
/* Owner writable (S_IWUSR). */
#घोषणा SHFL_UNIX_IWUSR             0000200U
/* Owner executable (S_IXUSR). */
#घोषणा SHFL_UNIX_IXUSR             0000100U

/* Group पढ़ोable (S_IRGRP). */
#घोषणा SHFL_UNIX_IRGRP             0000040U
/* Group writable (S_IWGRP). */
#घोषणा SHFL_UNIX_IWGRP             0000020U
/* Group executable (S_IXGRP). */
#घोषणा SHFL_UNIX_IXGRP             0000010U

/* Other पढ़ोable (S_IROTH). */
#घोषणा SHFL_UNIX_IROTH             0000004U
/* Other writable (S_IWOTH). */
#घोषणा SHFL_UNIX_IWOTH             0000002U
/* Other executable (S_IXOTH). */
#घोषणा SHFL_UNIX_IXOTH             0000001U

/* Named pipe (fअगरo) (S_IFIFO). */
#घोषणा SHFL_TYPE_FIFO              0010000U
/* Character device (S_IFCHR). */
#घोषणा SHFL_TYPE_DEV_CHAR          0020000U
/* Directory (S_IFसूची). */
#घोषणा SHFL_TYPE_सूचीECTORY         0040000U
/* Block device (S_IFBLK). */
#घोषणा SHFL_TYPE_DEV_BLOCK         0060000U
/* Regular file (S_IFREG). */
#घोषणा SHFL_TYPE_खाता              0100000U
/* Symbolic link (S_IFLNK). */
#घोषणा SHFL_TYPE_SYMLINK           0120000U
/* Socket (S_IFSOCK). */
#घोषणा SHFL_TYPE_SOCKET            0140000U
/* Whiteout (S_IFWHT). */
#घोषणा SHFL_TYPE_WHITEOUT          0160000U
/* Type mask (S_IFMT). */
#घोषणा SHFL_TYPE_MASK              0170000U

/* Checks the mode flags indicate a directory (S_ISसूची). */
#घोषणा SHFL_IS_सूचीECTORY(m)   (((m) & SHFL_TYPE_MASK) == SHFL_TYPE_सूचीECTORY)
/* Checks the mode flags indicate a symbolic link (S_ISLNK). */
#घोषणा SHFL_IS_SYMLINK(m)     (((m) & SHFL_TYPE_MASK) == SHFL_TYPE_SYMLINK)

/** The available additional inक्रमmation in a shfl_fsobjattr object. */
क्रमागत shfl_fsobjattr_add अणु
	/** No additional inक्रमmation is available / requested. */
	SHFLFSOBJATTRADD_NOTHING = 1,
	/**
	 * The additional unix attributes (shfl_fsobjattr::u::unix_attr) are
	 *  available / requested.
	 */
	SHFLFSOBJATTRADD_UNIX,
	/**
	 * The additional extended attribute size (shfl_fsobjattr::u::size) is
	 *  available / requested.
	 */
	SHFLFSOBJATTRADD_EASIZE,
	/**
	 * The last valid item (inclusive).
	 * The valid range is SHFLFSOBJATTRADD_NOTHING thru
	 * SHFLFSOBJATTRADD_LAST.
	 */
	SHFLFSOBJATTRADD_LAST = SHFLFSOBJATTRADD_EASIZE,

	/** The usual 32-bit hack. */
	SHFLFSOBJATTRADD_32BIT_SIZE_HACK = 0x7fffffff
पूर्ण;

/**
 * Additional unix Attributes, these are available when
 * shfl_fsobjattr.additional == SHFLFSOBJATTRADD_UNIX.
 */
काष्ठा shfl_fsobjattr_unix अणु
	/**
	 * The user owning the fileप्रणाली object (st_uid).
	 * This field is ~0U अगर not supported.
	 */
	u32 uid;

	/**
	 * The group the fileप्रणाली object is asचिन्हित (st_gid).
	 * This field is ~0U अगर not supported.
	 */
	u32 gid;

	/**
	 * Number of hard links to this fileप्रणाली object (st_nlink).
	 * This field is 1 अगर the fileप्रणाली करोesn't support hardlinking or
	 * the inक्रमmation isn't available.
	 */
	u32 hardlinks;

	/**
	 * The device number of the device which this fileप्रणाली object resides
	 * on (st_dev). This field is 0 अगर this inक्रमmation is not available.
	 */
	u32 inode_id_device;

	/**
	 * The unique identअगरier (within the fileप्रणाली) of this fileप्रणाली
	 * object (st_ino). Together with inode_id_device, this field can be
	 * used as a OS wide unique id, when both their values are not 0.
	 * This field is 0 अगर the inक्रमmation is not available.
	 */
	u64 inode_id;

	/**
	 * User flags (st_flags).
	 * This field is 0 अगर this inक्रमmation is not available.
	 */
	u32 flags;

	/**
	 * The current generation number (st_gen).
	 * This field is 0 अगर this inक्रमmation is not available.
	 */
	u32 generation_id;

	/**
	 * The device number of a अक्षर. or block device type object (st_rdev).
	 * This field is 0 अगर the file isn't a अक्षर. or block device or when
	 * the OS करोesn't use the major+minor device idenfication scheme.
	 */
	u32 device;
पूर्ण __packed;

/** Extended attribute size. */
काष्ठा shfl_fsobjattr_easize अणु
	/** Size of EAs. */
	s64 cb;
पूर्ण __packed;

/** Shared folder fileप्रणाली object attributes. */
काष्ठा shfl_fsobjattr अणु
	/** Mode flags (st_mode). SHFL_UNIX_*, SHFL_TYPE_*, and SHFL_DOS_*. */
	u32 mode;

	/** The additional attributes available. */
	क्रमागत shfl_fsobjattr_add additional;

	/**
	 * Additional attributes.
	 *
	 * Unless explicitly specअगरied to an API, the API can provide additional
	 * data as it is provided by the underlying OS.
	 */
	जोड़ अणु
		काष्ठा shfl_fsobjattr_unix unix_attr;
		काष्ठा shfl_fsobjattr_easize size;
	पूर्ण __packed u;
पूर्ण __packed;
VMMDEV_ASSERT_SIZE(shfl_fsobjattr, 44);

काष्ठा shfl_बारpec अणु
	s64 ns_relative_to_unix_epoch;
पूर्ण;

/** Fileप्रणाली object inक्रमmation काष्ठाure. */
काष्ठा shfl_fsobjinfo अणु
	/**
	 * Logical size (st_size).
	 * For normal files this is the size of the file.
	 * For symbolic links, this is the length of the path name contained
	 * in the symbolic link.
	 * For other objects this fields needs to be specअगरied.
	 */
	s64 size;

	/** Disk allocation size (st_blocks * DEV_BSIZE). */
	s64 allocated;

	/** Time of last access (st_aसमय). */
	काष्ठा shfl_बारpec access_समय;

	/** Time of last data modअगरication (st_mसमय). */
	काष्ठा shfl_बारpec modअगरication_समय;

	/**
	 * Time of last status change (st_स_समय).
	 * If not available this is set to modअगरication_समय.
	 */
	काष्ठा shfl_बारpec change_समय;

	/**
	 * Time of file birth (st_birthसमय).
	 * If not available this is set to change_समय.
	 */
	काष्ठा shfl_बारpec birth_समय;

	/** Attributes. */
	काष्ठा shfl_fsobjattr attr;

पूर्ण __packed;
VMMDEV_ASSERT_SIZE(shfl_fsobjinfo, 92);

/**
 * result of an खोलो/create request.
 * Aदीर्घ with handle value the result code
 * identअगरies what has happened जबतक
 * trying to खोलो the object.
 */
क्रमागत shfl_create_result अणु
	SHFL_NO_RESULT,
	/** Specअगरied path करोes not exist. */
	SHFL_PATH_NOT_FOUND,
	/** Path to file exists, but the last component करोes not. */
	SHFL_खाता_NOT_FOUND,
	/** File alपढ़ोy exists and either has been खोलोed or not. */
	SHFL_खाता_EXISTS,
	/** New file was created. */
	SHFL_खाता_CREATED,
	/** Existing file was replaced or overwritten. */
	SHFL_खाता_REPLACED
पूर्ण;

/* No flags. Initialization value. */
#घोषणा SHFL_CF_NONE                  (0x00000000)

/*
 * Only lookup the object, करो not वापस a handle. When this is set all other
 * flags are ignored.
 */
#घोषणा SHFL_CF_LOOKUP                (0x00000001)

/*
 * Open parent directory of specअगरied object.
 * Useful क्रम the corresponding Winकरोws FSD flag
 * and क्रम खोलोing paths like \\dir\\*.* to search the 'dir'.
 */
#घोषणा SHFL_CF_OPEN_TARGET_सूचीECTORY (0x00000002)

/* Create/खोलो a directory. */
#घोषणा SHFL_CF_सूचीECTORY             (0x00000004)

/*
 *  Open/create action to करो अगर object exists
 *  and अगर the object करोes not exists.
 *  REPLACE file means atomically DELETE and CREATE.
 *  OVERWRITE file means truncating the file to 0 and
 *  setting new size.
 *  When खोलोing an existing directory REPLACE and OVERWRITE
 *  actions are considered invalid, and cause वापसing
 *  खाता_EXISTS with NIL handle.
 */
#घोषणा SHFL_CF_ACT_MASK_IF_EXISTS      (0x000000f0)
#घोषणा SHFL_CF_ACT_MASK_IF_NEW         (0x00000f00)

/* What to करो अगर object exists. */
#घोषणा SHFL_CF_ACT_OPEN_IF_EXISTS      (0x00000000)
#घोषणा SHFL_CF_ACT_FAIL_IF_EXISTS      (0x00000010)
#घोषणा SHFL_CF_ACT_REPLACE_IF_EXISTS   (0x00000020)
#घोषणा SHFL_CF_ACT_OVERWRITE_IF_EXISTS (0x00000030)

/* What to करो अगर object करोes not exist. */
#घोषणा SHFL_CF_ACT_CREATE_IF_NEW       (0x00000000)
#घोषणा SHFL_CF_ACT_FAIL_IF_NEW         (0x00000100)

/* Read/ग_लिखो requested access क्रम the object. */
#घोषणा SHFL_CF_ACCESS_MASK_RW          (0x00003000)

/* No access requested. */
#घोषणा SHFL_CF_ACCESS_NONE             (0x00000000)
/* Read access requested. */
#घोषणा SHFL_CF_ACCESS_READ             (0x00001000)
/* Write access requested. */
#घोषणा SHFL_CF_ACCESS_WRITE            (0x00002000)
/* Read/Write access requested. */
#घोषणा SHFL_CF_ACCESS_READWRITE	(0x00003000)

/* Requested share access क्रम the object. */
#घोषणा SHFL_CF_ACCESS_MASK_DENY        (0x0000c000)

/* Allow any access. */
#घोषणा SHFL_CF_ACCESS_DENYNONE         (0x00000000)
/* Do not allow पढ़ो. */
#घोषणा SHFL_CF_ACCESS_DENYREAD         (0x00004000)
/* Do not allow ग_लिखो. */
#घोषणा SHFL_CF_ACCESS_DENYWRITE        (0x00008000)
/* Do not allow access. */
#घोषणा SHFL_CF_ACCESS_DENYALL          (0x0000c000)

/* Requested access to attributes of the object. */
#घोषणा SHFL_CF_ACCESS_MASK_ATTR        (0x00030000)

/* No access requested. */
#घोषणा SHFL_CF_ACCESS_ATTR_NONE        (0x00000000)
/* Read access requested. */
#घोषणा SHFL_CF_ACCESS_ATTR_READ        (0x00010000)
/* Write access requested. */
#घोषणा SHFL_CF_ACCESS_ATTR_WRITE       (0x00020000)
/* Read/Write access requested. */
#घोषणा SHFL_CF_ACCESS_ATTR_READWRITE   (0x00030000)

/*
 * The file is खोलोed in append mode.
 * Ignored अगर SHFL_CF_ACCESS_WRITE is not set.
 */
#घोषणा SHFL_CF_ACCESS_APPEND           (0x00040000)

/** Create parameters buffer काष्ठा क्रम SHFL_FN_CREATE call */
काष्ठा shfl_createparms अणु
	/** Returned handle of खोलोed object. */
	u64 handle;

	/** Returned result of the operation */
	क्रमागत shfl_create_result result;

	/** SHFL_CF_* */
	u32 create_flags;

	/**
	 * Attributes of object to create and
	 * वापसed actual attributes of खोलोed/created object.
	 */
	काष्ठा shfl_fsobjinfo info;
पूर्ण __packed;

/** Shared Folder directory inक्रमmation */
काष्ठा shfl_dirinfo अणु
	/** Full inक्रमmation about the object. */
	काष्ठा shfl_fsobjinfo info;
	/**
	 * The length of the लघु field (number of UTF16 अक्षरs).
	 * It is 16-bit क्रम reasons of alignment.
	 */
	u16 लघु_name_len;
	/**
	 * The लघु name क्रम 8.3 compatibility.
	 * Empty string अगर not available.
	 */
	u16 लघु_name[14];
	काष्ठा shfl_string name;
पूर्ण;

/** Shared folder fileप्रणाली properties. */
काष्ठा shfl_fsproperties अणु
	/**
	 * The maximum size of a fileप्रणाली object name.
	 * This करोes not include the '\\0'.
	 */
	u32 max_component_len;

	/**
	 * True अगर the fileप्रणाली is remote.
	 * False अगर the fileप्रणाली is local.
	 */
	bool remote;

	/**
	 * True अगर the fileप्रणाली is हाल sensitive.
	 * False अगर the fileप्रणाली is हाल insensitive.
	 */
	bool हाल_sensitive;

	/**
	 * True अगर the fileप्रणाली is mounted पढ़ो only.
	 * False अगर the fileप्रणाली is mounted पढ़ो ग_लिखो.
	 */
	bool पढ़ो_only;

	/**
	 * True अगर the fileप्रणाली can encode unicode object names.
	 * False अगर it can't.
	 */
	bool supports_unicode;

	/**
	 * True अगर the fileप्रणाली is compresses.
	 * False अगर it isn't or we don't know.
	 */
	bool compressed;

	/**
	 * True अगर the fileप्रणाली compresses of inभागidual files.
	 * False अगर it करोesn't or we don't know.
	 */
	bool file_compression;
पूर्ण;
VMMDEV_ASSERT_SIZE(shfl_fsproperties, 12);

काष्ठा shfl_volinfo अणु
	s64 total_allocation_bytes;
	s64 available_allocation_bytes;
	u32 bytes_per_allocation_unit;
	u32 bytes_per_sector;
	u32 serial;
	काष्ठा shfl_fsproperties properties;
पूर्ण;


/** SHFL_FN_MAP_FOLDER Parameters काष्ठाure. */
काष्ठा shfl_map_folder अणु
	/**
	 * poपूर्णांकer, in:
	 * Poपूर्णांकs to काष्ठा shfl_string buffer.
	 */
	काष्ठा vmmdev_hgcm_function_parameter path;

	/**
	 * poपूर्णांकer, out: SHFLROOT (u32)
	 * Root handle of the mapping which name is queried.
	 */
	काष्ठा vmmdev_hgcm_function_parameter root;

	/**
	 * poपूर्णांकer, in: UTF16
	 * Path delimiter
	 */
	काष्ठा vmmdev_hgcm_function_parameter delimiter;

	/**
	 * poपूर्णांकer, in: SHFLROOT (u32)
	 * Case senstive flag
	 */
	काष्ठा vmmdev_hgcm_function_parameter हाल_sensitive;

पूर्ण;

/* Number of parameters */
#घोषणा SHFL_CPARMS_MAP_FOLDER (4)


/** SHFL_FN_UNMAP_FOLDER Parameters काष्ठाure. */
काष्ठा shfl_unmap_folder अणु
	/**
	 * poपूर्णांकer, in: SHFLROOT (u32)
	 * Root handle of the mapping which name is queried.
	 */
	काष्ठा vmmdev_hgcm_function_parameter root;

पूर्ण;

/* Number of parameters */
#घोषणा SHFL_CPARMS_UNMAP_FOLDER (1)


/** SHFL_FN_CREATE Parameters काष्ठाure. */
काष्ठा shfl_create अणु
	/**
	 * poपूर्णांकer, in: SHFLROOT (u32)
	 * Root handle of the mapping which name is queried.
	 */
	काष्ठा vmmdev_hgcm_function_parameter root;

	/**
	 * poपूर्णांकer, in:
	 * Poपूर्णांकs to काष्ठा shfl_string buffer.
	 */
	काष्ठा vmmdev_hgcm_function_parameter path;

	/**
	 * poपूर्णांकer, in/out:
	 * Poपूर्णांकs to काष्ठा shfl_createparms buffer.
	 */
	काष्ठा vmmdev_hgcm_function_parameter parms;

पूर्ण;

/* Number of parameters */
#घोषणा SHFL_CPARMS_CREATE (3)


/** SHFL_FN_CLOSE Parameters काष्ठाure. */
काष्ठा shfl_बंद अणु
	/**
	 * poपूर्णांकer, in: SHFLROOT (u32)
	 * Root handle of the mapping which name is queried.
	 */
	काष्ठा vmmdev_hgcm_function_parameter root;

	/**
	 * value64, in:
	 * SHFLHANDLE (u64) of object to बंद.
	 */
	काष्ठा vmmdev_hgcm_function_parameter handle;

पूर्ण;

/* Number of parameters */
#घोषणा SHFL_CPARMS_CLOSE (2)


/** SHFL_FN_READ Parameters काष्ठाure. */
काष्ठा shfl_पढ़ो अणु
	/**
	 * poपूर्णांकer, in: SHFLROOT (u32)
	 * Root handle of the mapping which name is queried.
	 */
	काष्ठा vmmdev_hgcm_function_parameter root;

	/**
	 * value64, in:
	 * SHFLHANDLE (u64) of object to पढ़ो from.
	 */
	काष्ठा vmmdev_hgcm_function_parameter handle;

	/**
	 * value64, in:
	 * Offset to पढ़ो from.
	 */
	काष्ठा vmmdev_hgcm_function_parameter offset;

	/**
	 * value64, in/out:
	 * Bytes to पढ़ो/How many were पढ़ो.
	 */
	काष्ठा vmmdev_hgcm_function_parameter cb;

	/**
	 * poपूर्णांकer, out:
	 * Buffer to place data to.
	 */
	काष्ठा vmmdev_hgcm_function_parameter buffer;

पूर्ण;

/* Number of parameters */
#घोषणा SHFL_CPARMS_READ (5)


/** SHFL_FN_WRITE Parameters काष्ठाure. */
काष्ठा shfl_ग_लिखो अणु
	/**
	 * poपूर्णांकer, in: SHFLROOT (u32)
	 * Root handle of the mapping which name is queried.
	 */
	काष्ठा vmmdev_hgcm_function_parameter root;

	/**
	 * value64, in:
	 * SHFLHANDLE (u64) of object to ग_लिखो to.
	 */
	काष्ठा vmmdev_hgcm_function_parameter handle;

	/**
	 * value64, in:
	 * Offset to ग_लिखो to.
	 */
	काष्ठा vmmdev_hgcm_function_parameter offset;

	/**
	 * value64, in/out:
	 * Bytes to ग_लिखो/How many were written.
	 */
	काष्ठा vmmdev_hgcm_function_parameter cb;

	/**
	 * poपूर्णांकer, in:
	 * Data to ग_लिखो.
	 */
	काष्ठा vmmdev_hgcm_function_parameter buffer;

पूर्ण;

/* Number of parameters */
#घोषणा SHFL_CPARMS_WRITE (5)


/*
 * SHFL_FN_LIST
 * Listing inक्रमmation includes variable length RTसूचीENTRY[EX] काष्ठाures.
 */

#घोषणा SHFL_LIST_NONE			0
#घोषणा SHFL_LIST_RETURN_ONE		1

/** SHFL_FN_LIST Parameters काष्ठाure. */
काष्ठा shfl_list अणु
	/**
	 * poपूर्णांकer, in: SHFLROOT (u32)
	 * Root handle of the mapping which name is queried.
	 */
	काष्ठा vmmdev_hgcm_function_parameter root;

	/**
	 * value64, in:
	 * SHFLHANDLE (u64) of object to be listed.
	 */
	काष्ठा vmmdev_hgcm_function_parameter handle;

	/**
	 * value32, in:
	 * List flags SHFL_LIST_*.
	 */
	काष्ठा vmmdev_hgcm_function_parameter flags;

	/**
	 * value32, in/out:
	 * Bytes to be used क्रम listing inक्रमmation/How many bytes were used.
	 */
	काष्ठा vmmdev_hgcm_function_parameter cb;

	/**
	 * poपूर्णांकer, in/optional
	 * Poपूर्णांकs to काष्ठा shfl_string buffer that specअगरies a search path.
	 */
	काष्ठा vmmdev_hgcm_function_parameter path;

	/**
	 * poपूर्णांकer, out:
	 * Buffer to place listing inक्रमmation to. (काष्ठा shfl_dirinfo)
	 */
	काष्ठा vmmdev_hgcm_function_parameter buffer;

	/**
	 * value32, in/out:
	 * Indicates a key where the listing must be resumed.
	 * in: 0 means start from begin of object.
	 * out: 0 means listing completed.
	 */
	काष्ठा vmmdev_hgcm_function_parameter resume_poपूर्णांक;

	/**
	 * poपूर्णांकer, out:
	 * Number of files वापसed
	 */
	काष्ठा vmmdev_hgcm_function_parameter file_count;
पूर्ण;

/* Number of parameters */
#घोषणा SHFL_CPARMS_LIST (8)


/** SHFL_FN_READLINK Parameters काष्ठाure. */
काष्ठा shfl_पढ़ोLink अणु
	/**
	 * poपूर्णांकer, in: SHFLROOT (u32)
	 * Root handle of the mapping which name is queried.
	 */
	काष्ठा vmmdev_hgcm_function_parameter root;

	/**
	 * poपूर्णांकer, in:
	 * Poपूर्णांकs to काष्ठा shfl_string buffer.
	 */
	काष्ठा vmmdev_hgcm_function_parameter path;

	/**
	 * poपूर्णांकer, out:
	 * Buffer to place data to.
	 */
	काष्ठा vmmdev_hgcm_function_parameter buffer;

पूर्ण;

/* Number of parameters */
#घोषणा SHFL_CPARMS_READLINK (3)


/* SHFL_FN_INFORMATION */

/* Mask of Set/Get bit. */
#घोषणा SHFL_INFO_MODE_MASK    (0x1)
/* Get inक्रमmation */
#घोषणा SHFL_INFO_GET          (0x0)
/* Set inक्रमmation */
#घोषणा SHFL_INFO_SET          (0x1)

/* Get name of the object. */
#घोषणा SHFL_INFO_NAME         (0x2)
/* Set size of object (extend/trucate); only applies to file objects */
#घोषणा SHFL_INFO_SIZE         (0x4)
/* Get/Set file object info. */
#घोषणा SHFL_INFO_खाता         (0x8)
/* Get volume inक्रमmation. */
#घोषणा SHFL_INFO_VOLUME       (0x10)

/** SHFL_FN_INFORMATION Parameters काष्ठाure. */
काष्ठा shfl_inक्रमmation अणु
	/**
	 * poपूर्णांकer, in: SHFLROOT (u32)
	 * Root handle of the mapping which name is queried.
	 */
	काष्ठा vmmdev_hgcm_function_parameter root;

	/**
	 * value64, in:
	 * SHFLHANDLE (u64) of object to be listed.
	 */
	काष्ठा vmmdev_hgcm_function_parameter handle;

	/**
	 * value32, in:
	 * SHFL_INFO_*
	 */
	काष्ठा vmmdev_hgcm_function_parameter flags;

	/**
	 * value32, in/out:
	 * Bytes to be used क्रम inक्रमmation/How many bytes were used.
	 */
	काष्ठा vmmdev_hgcm_function_parameter cb;

	/**
	 * poपूर्णांकer, in/out:
	 * Inक्रमmation to be set/get (shfl_fsobjinfo or shfl_string). Do not
	 * क्रमget to set the shfl_fsobjinfo::attr::additional क्रम a get
	 * operation as well.
	 */
	काष्ठा vmmdev_hgcm_function_parameter info;

पूर्ण;

/* Number of parameters */
#घोषणा SHFL_CPARMS_INFORMATION (5)


/* SHFL_FN_REMOVE */

#घोषणा SHFL_REMOVE_खाता        (0x1)
#घोषणा SHFL_REMOVE_सूची         (0x2)
#घोषणा SHFL_REMOVE_SYMLINK     (0x4)

/** SHFL_FN_REMOVE Parameters काष्ठाure. */
काष्ठा shfl_हटाओ अणु
	/**
	 * poपूर्णांकer, in: SHFLROOT (u32)
	 * Root handle of the mapping which name is queried.
	 */
	काष्ठा vmmdev_hgcm_function_parameter root;

	/**
	 * poपूर्णांकer, in:
	 * Poपूर्णांकs to काष्ठा shfl_string buffer.
	 */
	काष्ठा vmmdev_hgcm_function_parameter path;

	/**
	 * value32, in:
	 * हटाओ flags (file/directory)
	 */
	काष्ठा vmmdev_hgcm_function_parameter flags;

पूर्ण;

#घोषणा SHFL_CPARMS_REMOVE  (3)


/* SHFL_FN_RENAME */

#घोषणा SHFL_RENAME_खाता                (0x1)
#घोषणा SHFL_RENAME_सूची                 (0x2)
#घोषणा SHFL_RENAME_REPLACE_IF_EXISTS   (0x4)

/** SHFL_FN_RENAME Parameters काष्ठाure. */
काष्ठा shfl_नाम अणु
	/**
	 * poपूर्णांकer, in: SHFLROOT (u32)
	 * Root handle of the mapping which name is queried.
	 */
	काष्ठा vmmdev_hgcm_function_parameter root;

	/**
	 * poपूर्णांकer, in:
	 * Poपूर्णांकs to काष्ठा shfl_string src.
	 */
	काष्ठा vmmdev_hgcm_function_parameter src;

	/**
	 * poपूर्णांकer, in:
	 * Poपूर्णांकs to काष्ठा shfl_string dest.
	 */
	काष्ठा vmmdev_hgcm_function_parameter dest;

	/**
	 * value32, in:
	 * नाम flags (file/directory)
	 */
	काष्ठा vmmdev_hgcm_function_parameter flags;

पूर्ण;

#घोषणा SHFL_CPARMS_RENAME  (4)


/** SHFL_FN_SYMLINK Parameters काष्ठाure. */
काष्ठा shfl_symlink अणु
	/**
	 * poपूर्णांकer, in: SHFLROOT (u32)
	 * Root handle of the mapping which name is queried.
	 */
	काष्ठा vmmdev_hgcm_function_parameter root;

	/**
	 * poपूर्णांकer, in:
	 * Poपूर्णांकs to काष्ठा shfl_string of path क्रम the new symlink.
	 */
	काष्ठा vmmdev_hgcm_function_parameter new_path;

	/**
	 * poपूर्णांकer, in:
	 * Poपूर्णांकs to काष्ठा shfl_string of destination क्रम symlink.
	 */
	काष्ठा vmmdev_hgcm_function_parameter old_path;

	/**
	 * poपूर्णांकer, out:
	 * Inक्रमmation about created symlink.
	 */
	काष्ठा vmmdev_hgcm_function_parameter info;

पूर्ण;

#घोषणा SHFL_CPARMS_SYMLINK  (4)

#पूर्ण_अगर
