<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Landlock - User space API
 *
 * Copyright तऊ 2017-2020 Mickaथ+l Salaथञn <mic@digikod.net>
 * Copyright तऊ 2018-2020 ANSSI
 */

#अगर_अघोषित _UAPI_LINUX_LANDLOCK_H
#घोषणा _UAPI_LINUX_LANDLOCK_H

#समावेश <linux/types.h>

/**
 * काष्ठा landlock_ruleset_attr - Ruleset definition
 *
 * Argument of sys_landlock_create_ruleset().  This काष्ठाure can grow in
 * future versions.
 */
काष्ठा landlock_ruleset_attr अणु
	/**
	 * @handled_access_fs: Biपंचांगask of actions (cf. `Fileप्रणाली flags`_)
	 * that is handled by this ruleset and should then be क्रमbidden अगर no
	 * rule explicitly allow them.  This is needed क्रम backward
	 * compatibility reasons.
	 */
	__u64 handled_access_fs;
पूर्ण;

/*
 * sys_landlock_create_ruleset() flags:
 *
 * - %LANDLOCK_CREATE_RULESET_VERSION: Get the highest supported Landlock ABI
 *   version.
 */
#घोषणा LANDLOCK_CREATE_RULESET_VERSION			(1U << 0)

/**
 * क्रमागत landlock_rule_type - Landlock rule type
 *
 * Argument of sys_landlock_add_rule().
 */
क्रमागत landlock_rule_type अणु
	/**
	 * @LANDLOCK_RULE_PATH_BENEATH: Type of a &काष्ठा
	 * landlock_path_beneath_attr .
	 */
	LANDLOCK_RULE_PATH_BENEATH = 1,
पूर्ण;

/**
 * काष्ठा landlock_path_beneath_attr - Path hierarchy definition
 *
 * Argument of sys_landlock_add_rule().
 */
काष्ठा landlock_path_beneath_attr अणु
	/**
	 * @allowed_access: Biपंचांगask of allowed actions क्रम this file hierarchy
	 * (cf. `Fileप्रणाली flags`_).
	 */
	__u64 allowed_access;
	/**
	 * @parent_fd: File descriptor, खोलो with ``O_PATH``, which identअगरies
	 * the parent directory of a file hierarchy, or just a file.
	 */
	__s32 parent_fd;
	/*
	 * This काष्ठा is packed to aव्योम trailing reserved members.
	 * Cf. security/landlock/syscalls.c:build_check_abi()
	 */
पूर्ण __attribute__((packed));

/**
 * DOC: fs_access
 *
 * A set of actions on kernel objects may be defined by an attribute (e.g.
 * &काष्ठा landlock_path_beneath_attr) including a biपंचांगask of access.
 *
 * Fileप्रणाली flags
 * ~~~~~~~~~~~~~~~~
 *
 * These flags enable to restrict a sandboxed process to a set of actions on
 * files and directories.  Files or directories खोलोed beक्रमe the sandboxing
 * are not subject to these restrictions.
 *
 * A file can only receive these access rights:
 *
 * - %LANDLOCK_ACCESS_FS_EXECUTE: Execute a file.
 * - %LANDLOCK_ACCESS_FS_WRITE_खाता: Open a file with ग_लिखो access.
 * - %LANDLOCK_ACCESS_FS_READ_खाता: Open a file with पढ़ो access.
 *
 * A directory can receive access rights related to files or directories.  The
 * following access right is applied to the directory itself, and the
 * directories beneath it:
 *
 * - %LANDLOCK_ACCESS_FS_READ_सूची: Open a directory or list its content.
 *
 * However, the following access rights only apply to the content of a
 * directory, not the directory itself:
 *
 * - %LANDLOCK_ACCESS_FS_REMOVE_सूची: Remove an empty directory or नाम one.
 * - %LANDLOCK_ACCESS_FS_REMOVE_खाता: Unlink (or नाम) a file.
 * - %LANDLOCK_ACCESS_FS_MAKE_CHAR: Create (or नाम or link) a अक्षरacter
 *   device.
 * - %LANDLOCK_ACCESS_FS_MAKE_सूची: Create (or नाम) a directory.
 * - %LANDLOCK_ACCESS_FS_MAKE_REG: Create (or नाम or link) a regular file.
 * - %LANDLOCK_ACCESS_FS_MAKE_SOCK: Create (or नाम or link) a UNIX करोमुख्य
 *   socket.
 * - %LANDLOCK_ACCESS_FS_MAKE_FIFO: Create (or नाम or link) a named pipe.
 * - %LANDLOCK_ACCESS_FS_MAKE_BLOCK: Create (or नाम or link) a block device.
 * - %LANDLOCK_ACCESS_FS_MAKE_SYM: Create (or नाम or link) a symbolic link.
 *
 * .. warning::
 *
 *   It is currently not possible to restrict some file-related actions
 *   accessible through these syscall families: :manpage:`स_बदलो(2)`,
 *   :manpage:`truncate(2)`, :manpage:`stat(2)`, :manpage:`flock(2)`,
 *   :manpage:`chmod(2)`, :manpage:`chown(2)`, :manpage:`setxattr(2)`,
 *   :manpage:`uसमय(2)`, :manpage:`ioctl(2)`, :manpage:`fcntl(2)`,
 *   :manpage:`access(2)`.
 *   Future Landlock evolutions will enable to restrict them.
 */
#घोषणा LANDLOCK_ACCESS_FS_EXECUTE			(1ULL << 0)
#घोषणा LANDLOCK_ACCESS_FS_WRITE_खाता			(1ULL << 1)
#घोषणा LANDLOCK_ACCESS_FS_READ_खाता			(1ULL << 2)
#घोषणा LANDLOCK_ACCESS_FS_READ_सूची			(1ULL << 3)
#घोषणा LANDLOCK_ACCESS_FS_REMOVE_सूची			(1ULL << 4)
#घोषणा LANDLOCK_ACCESS_FS_REMOVE_खाता			(1ULL << 5)
#घोषणा LANDLOCK_ACCESS_FS_MAKE_CHAR			(1ULL << 6)
#घोषणा LANDLOCK_ACCESS_FS_MAKE_सूची			(1ULL << 7)
#घोषणा LANDLOCK_ACCESS_FS_MAKE_REG			(1ULL << 8)
#घोषणा LANDLOCK_ACCESS_FS_MAKE_SOCK			(1ULL << 9)
#घोषणा LANDLOCK_ACCESS_FS_MAKE_FIFO			(1ULL << 10)
#घोषणा LANDLOCK_ACCESS_FS_MAKE_BLOCK			(1ULL << 11)
#घोषणा LANDLOCK_ACCESS_FS_MAKE_SYM			(1ULL << 12)

#पूर्ण_अगर /* _UAPI_LINUX_LANDLOCK_H */
