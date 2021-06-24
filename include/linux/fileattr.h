<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _LINUX_खाताATTR_H
#घोषणा _LINUX_खाताATTR_H

/* Flags shared betwen flags/xflags */
#घोषणा FS_COMMON_FL \
	(FS_SYNC_FL | FS_IMMUTABLE_FL | FS_APPEND_FL | \
	 FS_NODUMP_FL |	FS_NOATIME_FL | FS_DAX_FL | \
	 FS_PROJINHERIT_FL)

#घोषणा FS_XFLAG_COMMON \
	(FS_XFLAG_SYNC | FS_XFLAG_IMMUTABLE | FS_XFLAG_APPEND | \
	 FS_XFLAG_NODUMP | FS_XFLAG_NOATIME | FS_XFLAG_DAX | \
	 FS_XFLAG_PROJINHERIT)

/*
 * Merged पूर्णांकerface क्रम miscellaneous file attributes.  'flags' originates from
 * ext* and 'fsx_flags' from xfs.  There's some overlap between the two, which
 * is handled by the VFS helpers, so fileप्रणालीs are मुक्त to implement just one
 * or both of these sub-पूर्णांकerfaces.
 */
काष्ठा fileattr अणु
	u32	flags;		/* flags (FS_IOC_GETFLAGS/FS_IOC_SETFLAGS) */
	/* काष्ठा fsxattr: */
	u32	fsx_xflags;	/* xflags field value (get/set) */
	u32	fsx_extsize;	/* extsize field value (get/set)*/
	u32	fsx_nextents;	/* nextents field value (get)	*/
	u32	fsx_projid;	/* project identअगरier (get/set) */
	u32	fsx_cowextsize;	/* CoW extsize field value (get/set)*/
	/* selectors: */
	bool	flags_valid:1;
	bool	fsx_valid:1;
पूर्ण;

पूर्णांक copy_fsxattr_to_user(स्थिर काष्ठा fileattr *fa, काष्ठा fsxattr __user *ufa);

व्योम fileattr_fill_xflags(काष्ठा fileattr *fa, u32 xflags);
व्योम fileattr_fill_flags(काष्ठा fileattr *fa, u32 flags);

/**
 * fileattr_has_fsx - check क्रम extended flags/attributes
 * @fa:		fileattr poपूर्णांकer
 *
 * Return: true अगर any attributes are present that are not represented in
 * ->flags.
 */
अटल अंतरभूत bool fileattr_has_fsx(स्थिर काष्ठा fileattr *fa)
अणु
	वापस fa->fsx_valid &&
		((fa->fsx_xflags & ~FS_XFLAG_COMMON) || fa->fsx_extsize != 0 ||
		 fa->fsx_projid != 0 ||	fa->fsx_cowextsize != 0);
पूर्ण

पूर्णांक vfs_fileattr_get(काष्ठा dentry *dentry, काष्ठा fileattr *fa);
पूर्णांक vfs_fileattr_set(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		     काष्ठा fileattr *fa);

#पूर्ण_अगर /* _LINUX_खाताATTR_H */
