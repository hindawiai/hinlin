<शैली गुरु>
/*
 *   fs/cअगरs/cअगरs_fs_sb.h
 *
 *   Copyright (c) International Business Machines  Corp., 2002,2004
 *   Author(s): Steve French (sfrench@us.ibm.com)
 *
 *   This library is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of the GNU Lesser General Public License as published
 *   by the Free Software Foundation; either version 2.1 of the License, or
 *   (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
 *   the GNU Lesser General Public License क्रम more details.
 *
 */
#समावेश <linux/rbtree.h>

#अगर_अघोषित _CIFS_FS_SB_H
#घोषणा _CIFS_FS_SB_H

#समावेश <linux/backing-dev.h>

#घोषणा CIFS_MOUNT_NO_PERM      1 /* करो not करो client vfs_perm check */
#घोषणा CIFS_MOUNT_SET_UID      2 /* set current's euid in create etc. */
#घोषणा CIFS_MOUNT_SERVER_INUM  4 /* inode numbers from uniqueid from server  */
#घोषणा CIFS_MOUNT_सूचीECT_IO    8 /* करो not ग_लिखो nor पढ़ो through page cache */
#घोषणा CIFS_MOUNT_NO_XATTR     0x10  /* अगर set - disable xattr support       */
#घोषणा CIFS_MOUNT_MAP_SPECIAL_CHR 0x20 /* remap illegal अक्षरs in filenames   */
#घोषणा CIFS_MOUNT_POSIX_PATHS  0x40  /* Negotiate posix pathnames अगर possible*/
#घोषणा CIFS_MOUNT_UNX_EMUL     0x80  /* Network compat with SFUnix emulation */
#घोषणा CIFS_MOUNT_NO_BRL       0x100 /* No sending byte range locks to srv   */
#घोषणा CIFS_MOUNT_CIFS_ACL     0x200 /* send ACL requests to non-POSIX srv   */
#घोषणा CIFS_MOUNT_OVERR_UID    0x400 /* override uid वापसed from server    */
#घोषणा CIFS_MOUNT_OVERR_GID    0x800 /* override gid वापसed from server    */
#घोषणा CIFS_MOUNT_DYNPERM      0x1000 /* allow in-memory only mode setting   */
#घोषणा CIFS_MOUNT_NOPOSIXBRL   0x2000 /* mandatory not posix byte range lock */
#घोषणा CIFS_MOUNT_NOSSYNC      0x4000 /* करोn't करो slow SMBflush on every sync*/
#घोषणा CIFS_MOUNT_FSCACHE	0x8000 /* local caching enabled */
#घोषणा CIFS_MOUNT_MF_SYMLINKS	0x10000 /* Minshall+French Symlinks enabled */
#घोषणा CIFS_MOUNT_MULTIUSER	0x20000 /* multiuser mount */
#घोषणा CIFS_MOUNT_STRICT_IO	0x40000 /* strict cache mode */
#घोषणा CIFS_MOUNT_RWPIDFORWARD	0x80000 /* use pid क्रमwarding क्रम rw */
#घोषणा CIFS_MOUNT_POSIXACL	0x100000 /* mirror of SB_POSIXACL in mnt_cअगरs_flags */
#घोषणा CIFS_MOUNT_CIFS_BACKUPUID 0x200000 /* backup पूर्णांकent bit क्रम a user */
#घोषणा CIFS_MOUNT_CIFS_BACKUPGID 0x400000 /* backup पूर्णांकent bit क्रम a group */
#घोषणा CIFS_MOUNT_MAP_SFM_CHR	0x800000 /* SFM/MAC mapping क्रम illegal अक्षरs */
#घोषणा CIFS_MOUNT_USE_PREFIX_PATH 0x1000000 /* make subpath with unaccessible
					      * root mountable
					      */
#घोषणा CIFS_MOUNT_UID_FROM_ACL 0x2000000 /* try to get UID via special SID */
#घोषणा CIFS_MOUNT_NO_HANDLE_CACHE 0x4000000 /* disable caching dir handles */
#घोषणा CIFS_MOUNT_NO_DFS 0x8000000 /* disable DFS resolving */
#घोषणा CIFS_MOUNT_MODE_FROM_SID 0x10000000 /* retrieve mode from special ACE */
#घोषणा CIFS_MOUNT_RO_CACHE	0x20000000  /* assumes share will not change */
#घोषणा CIFS_MOUNT_RW_CACHE	0x40000000  /* assumes only client accessing */
#घोषणा CIFS_MOUNT_SHUTDOWN	0x80000000

काष्ठा cअगरs_sb_info अणु
	काष्ठा rb_root tlink_tree;
	spinlock_t tlink_tree_lock;
	काष्ठा tcon_link *master_tlink;
	काष्ठा nls_table *local_nls;
	काष्ठा smb3_fs_context *ctx;
	atomic_t active;
	अचिन्हित पूर्णांक mnt_cअगरs_flags;
	काष्ठा delayed_work prune_tlinks;
	काष्ठा rcu_head rcu;

	/* only used when CIFS_MOUNT_USE_PREFIX_PATH is set */
	अक्षर *prepath;

	/*
	 * Path initially provided by the mount call. We might connect
	 * to something dअगरferent via DFS but we want to keep it to करो
	 * failover properly.
	 */
	अक्षर *origin_fullpath; /* \\HOST\SHARE\[OPTIONAL PATH] */
	/*
	 * Indicate whether serverino option was turned off later
	 * (cअगरs_स्वतःdisable_serverino) in order to match new mounts.
	 */
	bool mnt_cअगरs_serverino_स्वतःdisabled;
	/*
	 * Available once the mount has completed.
	 */
	काष्ठा dentry *root;
पूर्ण;
#पूर्ण_अगर				/* _CIFS_FS_SB_H */
