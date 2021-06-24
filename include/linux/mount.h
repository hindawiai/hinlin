<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *
 * Definitions क्रम mount पूर्णांकerface. This describes the in the kernel build 
 * linkedlist with mounted fileप्रणालीs.
 *
 * Author:  Marco van Wieringen <mvw@planets.elm.net>
 *
 */
#अगर_अघोषित _LINUX_MOUNT_H
#घोषणा _LINUX_MOUNT_H

#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/seqlock.h>
#समावेश <linux/atomic.h>

काष्ठा super_block;
काष्ठा vfsmount;
काष्ठा dentry;
काष्ठा mnt_namespace;
काष्ठा fs_context;

#घोषणा MNT_NOSUID	0x01
#घोषणा MNT_NODEV	0x02
#घोषणा MNT_NOEXEC	0x04
#घोषणा MNT_NOATIME	0x08
#घोषणा MNT_NOसूचीATIME	0x10
#घोषणा MNT_RELATIME	0x20
#घोषणा MNT_READONLY	0x40	/* करोes the user want this to be r/o? */
#घोषणा MNT_NOSYMFOLLOW	0x80

#घोषणा MNT_SHRINKABLE	0x100
#घोषणा MNT_WRITE_HOLD	0x200

#घोषणा MNT_SHARED	0x1000	/* अगर the vfsmount is a shared mount */
#घोषणा MNT_UNBINDABLE	0x2000	/* अगर the vfsmount is a unbindable mount */
/*
 * MNT_SHARED_MASK is the set of flags that should be cleared when a
 * mount becomes shared.  Currently, this is only the flag that says a
 * mount cannot be bind mounted, since this is how we create a mount
 * that shares events with another mount.  If you add a new MNT_*
 * flag, consider how it पूर्णांकeracts with shared mounts.
 */
#घोषणा MNT_SHARED_MASK	(MNT_UNBINDABLE)
#घोषणा MNT_USER_SETTABLE_MASK  (MNT_NOSUID | MNT_NODEV | MNT_NOEXEC \
				 | MNT_NOATIME | MNT_NOसूचीATIME | MNT_RELATIME \
				 | MNT_READONLY | MNT_NOSYMFOLLOW)
#घोषणा MNT_ATIME_MASK (MNT_NOATIME | MNT_NOसूचीATIME | MNT_RELATIME )

#घोषणा MNT_INTERNAL_FLAGS (MNT_SHARED | MNT_WRITE_HOLD | MNT_INTERNAL | \
			    MNT_DOOMED | MNT_SYNC_UMOUNT | MNT_MARKED | \
			    MNT_CURSOR)

#घोषणा MNT_INTERNAL	0x4000

#घोषणा MNT_LOCK_ATIME		0x040000
#घोषणा MNT_LOCK_NOEXEC		0x080000
#घोषणा MNT_LOCK_NOSUID		0x100000
#घोषणा MNT_LOCK_NODEV		0x200000
#घोषणा MNT_LOCK_READONLY	0x400000
#घोषणा MNT_LOCKED		0x800000
#घोषणा MNT_DOOMED		0x1000000
#घोषणा MNT_SYNC_UMOUNT		0x2000000
#घोषणा MNT_MARKED		0x4000000
#घोषणा MNT_UMOUNT		0x8000000
#घोषणा MNT_CURSOR		0x10000000

काष्ठा vfsmount अणु
	काष्ठा dentry *mnt_root;	/* root of the mounted tree */
	काष्ठा super_block *mnt_sb;	/* poपूर्णांकer to superblock */
	पूर्णांक mnt_flags;
	काष्ठा user_namespace *mnt_userns;
पूर्ण __अक्रमomize_layout;

अटल अंतरभूत काष्ठा user_namespace *mnt_user_ns(स्थिर काष्ठा vfsmount *mnt)
अणु
	/* Pairs with smp_store_release() in करो_idmap_mount(). */
	वापस smp_load_acquire(&mnt->mnt_userns);
पूर्ण

काष्ठा file; /* क्रमward dec */
काष्ठा path;

बाह्य पूर्णांक mnt_want_ग_लिखो(काष्ठा vfsmount *mnt);
बाह्य पूर्णांक mnt_want_ग_लिखो_file(काष्ठा file *file);
बाह्य व्योम mnt_drop_ग_लिखो(काष्ठा vfsmount *mnt);
बाह्य व्योम mnt_drop_ग_लिखो_file(काष्ठा file *file);
बाह्य व्योम mntput(काष्ठा vfsmount *mnt);
बाह्य काष्ठा vfsmount *mntget(काष्ठा vfsmount *mnt);
बाह्य काष्ठा vfsmount *mnt_clone_पूर्णांकernal(स्थिर काष्ठा path *path);
बाह्य bool __mnt_is_पढ़ोonly(काष्ठा vfsmount *mnt);
बाह्य bool mnt_may_suid(काष्ठा vfsmount *mnt);

काष्ठा path;
बाह्य काष्ठा vfsmount *clone_निजी_mount(स्थिर काष्ठा path *path);
बाह्य पूर्णांक __mnt_want_ग_लिखो(काष्ठा vfsmount *);
बाह्य व्योम __mnt_drop_ग_लिखो(काष्ठा vfsmount *);

काष्ठा file_प्रणाली_type;
बाह्य काष्ठा vfsmount *fc_mount(काष्ठा fs_context *fc);
बाह्य काष्ठा vfsmount *vfs_create_mount(काष्ठा fs_context *fc);
बाह्य काष्ठा vfsmount *vfs_kern_mount(काष्ठा file_प्रणाली_type *type,
				      पूर्णांक flags, स्थिर अक्षर *name,
				      व्योम *data);
बाह्य काष्ठा vfsmount *vfs_submount(स्थिर काष्ठा dentry *mountpoपूर्णांक,
				     काष्ठा file_प्रणाली_type *type,
				     स्थिर अक्षर *name, व्योम *data);

बाह्य व्योम mnt_set_expiry(काष्ठा vfsmount *mnt, काष्ठा list_head *expiry_list);
बाह्य व्योम mark_mounts_क्रम_expiry(काष्ठा list_head *mounts);

बाह्य dev_t name_to_dev_t(स्थिर अक्षर *name);

बाह्य अचिन्हित पूर्णांक sysctl_mount_max;

बाह्य bool path_is_mountpoपूर्णांक(स्थिर काष्ठा path *path);

बाह्य व्योम kern_unmount_array(काष्ठा vfsmount *mnt[], अचिन्हित पूर्णांक num);

#पूर्ण_अगर /* _LINUX_MOUNT_H */
