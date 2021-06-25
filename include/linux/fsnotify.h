<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_FS_NOTIFY_H
#घोषणा _LINUX_FS_NOTIFY_H

/*
 * include/linux/fsnotअगरy.h - generic hooks क्रम fileप्रणाली notअगरication, to
 * reduce in-source duplication from both dnotअगरy and inotअगरy.
 *
 * We करोn't compile any of this away in some complicated menagerie of अगरdefs.
 * Instead, we rely on the code inside to optimize away as needed.
 *
 * (C) Copyright 2005 Robert Love
 */

#समावेश <linux/fsnotअगरy_backend.h>
#समावेश <linux/audit.h>
#समावेश <linux/slab.h>
#समावेश <linux/bug.h>

/*
 * Notअगरy this @dir inode about a change in a child directory entry.
 * The directory entry may have turned positive or negative or its inode may
 * have changed (i.e. नामd over).
 *
 * Unlike fsnotअगरy_parent(), the event will be reported regardless of the
 * FS_EVENT_ON_CHILD mask on the parent inode and will not be reported अगर only
 * the child is पूर्णांकerested and not the parent.
 */
अटल अंतरभूत व्योम fsnotअगरy_name(काष्ठा inode *dir, __u32 mask,
				 काष्ठा inode *child,
				 स्थिर काष्ठा qstr *name, u32 cookie)
अणु
	fsnotअगरy(mask, child, FSNOTIFY_EVENT_INODE, dir, name, शून्य, cookie);
पूर्ण

अटल अंतरभूत व्योम fsnotअगरy_dirent(काष्ठा inode *dir, काष्ठा dentry *dentry,
				   __u32 mask)
अणु
	fsnotअगरy_name(dir, mask, d_inode(dentry), &dentry->d_name, 0);
पूर्ण

अटल अंतरभूत व्योम fsnotअगरy_inode(काष्ठा inode *inode, __u32 mask)
अणु
	अगर (S_ISसूची(inode->i_mode))
		mask |= FS_ISसूची;

	fsnotअगरy(mask, inode, FSNOTIFY_EVENT_INODE, शून्य, शून्य, inode, 0);
पूर्ण

/* Notअगरy this dentry's parent about a child's events. */
अटल अंतरभूत पूर्णांक fsnotअगरy_parent(काष्ठा dentry *dentry, __u32 mask,
				  स्थिर व्योम *data, पूर्णांक data_type)
अणु
	काष्ठा inode *inode = d_inode(dentry);

	अगर (S_ISसूची(inode->i_mode)) अणु
		mask |= FS_ISसूची;

		/* sb/mount marks are not पूर्णांकerested in name of directory */
		अगर (!(dentry->d_flags & DCACHE_FSNOTIFY_PARENT_WATCHED))
			जाओ notअगरy_child;
	पूर्ण

	/* disconnected dentry cannot notअगरy parent */
	अगर (IS_ROOT(dentry))
		जाओ notअगरy_child;

	वापस __fsnotअगरy_parent(dentry, mask, data, data_type);

notअगरy_child:
	वापस fsnotअगरy(mask, data, data_type, शून्य, शून्य, inode, 0);
पूर्ण

/*
 * Simple wrappers to consolidate calls to fsnotअगरy_parent() when an event
 * is on a file/dentry.
 */
अटल अंतरभूत व्योम fsnotअगरy_dentry(काष्ठा dentry *dentry, __u32 mask)
अणु
	fsnotअगरy_parent(dentry, mask, d_inode(dentry), FSNOTIFY_EVENT_INODE);
पूर्ण

अटल अंतरभूत पूर्णांक fsnotअगरy_file(काष्ठा file *file, __u32 mask)
अणु
	स्थिर काष्ठा path *path = &file->f_path;

	अगर (file->f_mode & FMODE_NONOTIFY)
		वापस 0;

	वापस fsnotअगरy_parent(path->dentry, mask, path, FSNOTIFY_EVENT_PATH);
पूर्ण

/* Simple call site क्रम access decisions */
अटल अंतरभूत पूर्णांक fsnotअगरy_perm(काष्ठा file *file, पूर्णांक mask)
अणु
	पूर्णांक ret;
	__u32 fsnotअगरy_mask = 0;

	अगर (!(mask & (MAY_READ | MAY_OPEN)))
		वापस 0;

	अगर (mask & MAY_OPEN) अणु
		fsnotअगरy_mask = FS_OPEN_PERM;

		अगर (file->f_flags & __FMODE_EXEC) अणु
			ret = fsnotअगरy_file(file, FS_OPEN_EXEC_PERM);

			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण अन्यथा अगर (mask & MAY_READ) अणु
		fsnotअगरy_mask = FS_ACCESS_PERM;
	पूर्ण

	वापस fsnotअगरy_file(file, fsnotअगरy_mask);
पूर्ण

/*
 * fsnotअगरy_link_count - inode's link count changed
 */
अटल अंतरभूत व्योम fsnotअगरy_link_count(काष्ठा inode *inode)
अणु
	fsnotअगरy_inode(inode, FS_ATTRIB);
पूर्ण

/*
 * fsnotअगरy_move - file old_name at old_dir was moved to new_name at new_dir
 */
अटल अंतरभूत व्योम fsnotअगरy_move(काष्ठा inode *old_dir, काष्ठा inode *new_dir,
				 स्थिर काष्ठा qstr *old_name,
				 पूर्णांक isdir, काष्ठा inode *target,
				 काष्ठा dentry *moved)
अणु
	काष्ठा inode *source = moved->d_inode;
	u32 fs_cookie = fsnotअगरy_get_cookie();
	__u32 old_dir_mask = FS_MOVED_FROM;
	__u32 new_dir_mask = FS_MOVED_TO;
	स्थिर काष्ठा qstr *new_name = &moved->d_name;

	अगर (old_dir == new_dir)
		old_dir_mask |= FS_DN_RENAME;

	अगर (isdir) अणु
		old_dir_mask |= FS_ISसूची;
		new_dir_mask |= FS_ISसूची;
	पूर्ण

	fsnotअगरy_name(old_dir, old_dir_mask, source, old_name, fs_cookie);
	fsnotअगरy_name(new_dir, new_dir_mask, source, new_name, fs_cookie);

	अगर (target)
		fsnotअगरy_link_count(target);
	fsnotअगरy_inode(source, FS_MOVE_SELF);
	audit_inode_child(new_dir, moved, AUDIT_TYPE_CHILD_CREATE);
पूर्ण

/*
 * fsnotअगरy_inode_delete - and inode is being evicted from cache, clean up is needed
 */
अटल अंतरभूत व्योम fsnotअगरy_inode_delete(काष्ठा inode *inode)
अणु
	__fsnotअगरy_inode_delete(inode);
पूर्ण

/*
 * fsnotअगरy_vfsmount_delete - a vfsmount is being destroyed, clean up is needed
 */
अटल अंतरभूत व्योम fsnotअगरy_vfsmount_delete(काष्ठा vfsmount *mnt)
अणु
	__fsnotअगरy_vfsmount_delete(mnt);
पूर्ण

/*
 * fsnotअगरy_inodeहटाओ - an inode is going away
 */
अटल अंतरभूत व्योम fsnotअगरy_inodeहटाओ(काष्ठा inode *inode)
अणु
	fsnotअगरy_inode(inode, FS_DELETE_SELF);
	__fsnotअगरy_inode_delete(inode);
पूर्ण

/*
 * fsnotअगरy_create - 'name' was linked in
 */
अटल अंतरभूत व्योम fsnotअगरy_create(काष्ठा inode *inode, काष्ठा dentry *dentry)
अणु
	audit_inode_child(inode, dentry, AUDIT_TYPE_CHILD_CREATE);

	fsnotअगरy_dirent(inode, dentry, FS_CREATE);
पूर्ण

/*
 * fsnotअगरy_link - new hardlink in 'inode' directory
 * Note: We have to pass also the linked inode ptr as some fileप्रणालीs leave
 *   new_dentry->d_inode शून्य and instantiate inode poपूर्णांकer later
 */
अटल अंतरभूत व्योम fsnotअगरy_link(काष्ठा inode *dir, काष्ठा inode *inode,
				 काष्ठा dentry *new_dentry)
अणु
	fsnotअगरy_link_count(inode);
	audit_inode_child(dir, new_dentry, AUDIT_TYPE_CHILD_CREATE);

	fsnotअगरy_name(dir, FS_CREATE, inode, &new_dentry->d_name, 0);
पूर्ण

/*
 * fsnotअगरy_unlink - 'name' was unlinked
 *
 * Caller must make sure that dentry->d_name is stable.
 */
अटल अंतरभूत व्योम fsnotअगरy_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	/* Expected to be called beक्रमe d_delete() */
	WARN_ON_ONCE(d_is_negative(dentry));

	fsnotअगरy_dirent(dir, dentry, FS_DELETE);
पूर्ण

/*
 * fsnotअगरy_सूची_गढ़ो - directory 'name' was created
 */
अटल अंतरभूत व्योम fsnotअगरy_सूची_गढ़ो(काष्ठा inode *inode, काष्ठा dentry *dentry)
अणु
	audit_inode_child(inode, dentry, AUDIT_TYPE_CHILD_CREATE);

	fsnotअगरy_dirent(inode, dentry, FS_CREATE | FS_ISसूची);
पूर्ण

/*
 * fsnotअगरy_सूची_हटाओ - directory 'name' was हटाओd
 *
 * Caller must make sure that dentry->d_name is stable.
 */
अटल अंतरभूत व्योम fsnotअगरy_सूची_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	/* Expected to be called beक्रमe d_delete() */
	WARN_ON_ONCE(d_is_negative(dentry));

	fsnotअगरy_dirent(dir, dentry, FS_DELETE | FS_ISसूची);
पूर्ण

/*
 * fsnotअगरy_access - file was पढ़ो
 */
अटल अंतरभूत व्योम fsnotअगरy_access(काष्ठा file *file)
अणु
	fsnotअगरy_file(file, FS_ACCESS);
पूर्ण

/*
 * fsnotअगरy_modअगरy - file was modअगरied
 */
अटल अंतरभूत व्योम fsnotअगरy_modअगरy(काष्ठा file *file)
अणु
	fsnotअगरy_file(file, FS_MODIFY);
पूर्ण

/*
 * fsnotअगरy_खोलो - file was खोलोed
 */
अटल अंतरभूत व्योम fsnotअगरy_खोलो(काष्ठा file *file)
अणु
	__u32 mask = FS_OPEN;

	अगर (file->f_flags & __FMODE_EXEC)
		mask |= FS_OPEN_EXEC;

	fsnotअगरy_file(file, mask);
पूर्ण

/*
 * fsnotअगरy_बंद - file was बंदd
 */
अटल अंतरभूत व्योम fsnotअगरy_बंद(काष्ठा file *file)
अणु
	__u32 mask = (file->f_mode & FMODE_WRITE) ? FS_CLOSE_WRITE :
						    FS_CLOSE_NOWRITE;

	fsnotअगरy_file(file, mask);
पूर्ण

/*
 * fsnotअगरy_xattr - extended attributes were changed
 */
अटल अंतरभूत व्योम fsnotअगरy_xattr(काष्ठा dentry *dentry)
अणु
	fsnotअगरy_dentry(dentry, FS_ATTRIB);
पूर्ण

/*
 * fsnotअगरy_change - notअगरy_change event.  file was modअगरied and/or metadata
 * was changed.
 */
अटल अंतरभूत व्योम fsnotअगरy_change(काष्ठा dentry *dentry, अचिन्हित पूर्णांक ia_valid)
अणु
	__u32 mask = 0;

	अगर (ia_valid & ATTR_UID)
		mask |= FS_ATTRIB;
	अगर (ia_valid & ATTR_GID)
		mask |= FS_ATTRIB;
	अगर (ia_valid & ATTR_SIZE)
		mask |= FS_MODIFY;

	/* both बार implies a uसमय(s) call */
	अगर ((ia_valid & (ATTR_ATIME | ATTR_MTIME)) == (ATTR_ATIME | ATTR_MTIME))
		mask |= FS_ATTRIB;
	अन्यथा अगर (ia_valid & ATTR_ATIME)
		mask |= FS_ACCESS;
	अन्यथा अगर (ia_valid & ATTR_MTIME)
		mask |= FS_MODIFY;

	अगर (ia_valid & ATTR_MODE)
		mask |= FS_ATTRIB;

	अगर (mask)
		fsnotअगरy_dentry(dentry, mask);
पूर्ण

#पूर्ण_अगर	/* _LINUX_FS_NOTIFY_H */
