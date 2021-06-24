<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Copyright 1997-1998 Transmeta Corporation - All Rights Reserved
 *  Copyright 2005-2006 Ian Kent <raven@themaw.net>
 */

/* Internal header file क्रम स्वतःfs */

#समावेश <linux/स्वतः_fs.h>
#समावेश <linux/स्वतः_dev-ioctl.h>

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/माला.स>
#समावेश <linux/रुको.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/mount.h>
#समावेश <linux/namei.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/list.h>
#समावेश <linux/completion.h>
#समावेश <linux/file.h>
#समावेश <linux/magic.h>

/* This is the range of ioctl() numbers we claim as ours */
#घोषणा AUTOFS_IOC_FIRST     AUTOFS_IOC_READY
#घोषणा AUTOFS_IOC_COUNT     32

#घोषणा AUTOFS_DEV_IOCTL_IOC_FIRST	(AUTOFS_DEV_IOCTL_VERSION)
#घोषणा AUTOFS_DEV_IOCTL_IOC_COUNT \
	(AUTOFS_DEV_IOCTL_ISMOUNTPOINT_CMD - AUTOFS_DEV_IOCTL_VERSION_CMD)

#अगर_घोषित pr_fmt
#अघोषित pr_fmt
#पूर्ण_अगर
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":pid:%d:%s: " fmt, current->pid, __func__

बाह्य काष्ठा file_प्रणाली_type स्वतःfs_fs_type;

/*
 * Unअगरied info काष्ठाure.  This is poपूर्णांकed to by both the dentry and
 * inode काष्ठाures.  Each file in the fileप्रणाली has an instance of this
 * काष्ठाure.  It holds a reference to the dentry, so dentries are never
 * flushed जबतक the file exists.  All name lookups are dealt with at the
 * dentry level, although the fileप्रणाली can पूर्णांकerfere in the validation
 * process.  Readdir is implemented by traversing the dentry lists.
 */
काष्ठा स्वतःfs_info अणु
	काष्ठा dentry	*dentry;
	काष्ठा inode	*inode;

	पूर्णांक		flags;

	काष्ठा completion expire_complete;

	काष्ठा list_head active;

	काष्ठा list_head expiring;

	काष्ठा स्वतःfs_sb_info *sbi;
	अचिन्हित दीर्घ last_used;
	पूर्णांक count;

	kuid_t uid;
	kgid_t gid;
	काष्ठा rcu_head rcu;
पूर्ण;

#घोषणा AUTOFS_INF_EXPIRING	(1<<0) /* dentry in the process of expiring */
#घोषणा AUTOFS_INF_WANT_EXPIRE	(1<<1) /* the dentry is being considered
					* क्रम expiry, so RCU_walk is
					* not permitted.  If it progresses to
					* actual expiry attempt, the flag is
					* not cleared when EXPIRING is set -
					* in that हाल it माला_लो cleared only
					* when it comes to clearing EXPIRING.
					*/
#घोषणा AUTOFS_INF_PENDING	(1<<2) /* dentry pending mount */

काष्ठा स्वतःfs_रुको_queue अणु
	रुको_queue_head_t queue;
	काष्ठा स्वतःfs_रुको_queue *next;
	स्वतःfs_wqt_t रुको_queue_token;
	/* We use the following to see what we are रुकोing क्रम */
	काष्ठा qstr name;
	u32 offset;
	u32 dev;
	u64 ino;
	kuid_t uid;
	kgid_t gid;
	pid_t pid;
	pid_t tgid;
	/* This is क्रम status reporting upon वापस */
	पूर्णांक status;
	अचिन्हित पूर्णांक रुको_ctr;
पूर्ण;

#घोषणा AUTOFS_SBI_MAGIC 0x6d4a556d

#घोषणा AUTOFS_SBI_CATATONIC	0x0001
#घोषणा AUTOFS_SBI_STRICTEXPIRE 0x0002
#घोषणा AUTOFS_SBI_IGNORE	0x0004

काष्ठा स्वतःfs_sb_info अणु
	u32 magic;
	पूर्णांक pipefd;
	काष्ठा file *pipe;
	काष्ठा pid *oz_pgrp;
	पूर्णांक version;
	पूर्णांक sub_version;
	पूर्णांक min_proto;
	पूर्णांक max_proto;
	अचिन्हित पूर्णांक flags;
	अचिन्हित दीर्घ exp_समयout;
	अचिन्हित पूर्णांक type;
	काष्ठा super_block *sb;
	काष्ठा mutex wq_mutex;
	काष्ठा mutex pipe_mutex;
	spinlock_t fs_lock;
	काष्ठा स्वतःfs_रुको_queue *queues; /* Wait queue poपूर्णांकer */
	spinlock_t lookup_lock;
	काष्ठा list_head active_list;
	काष्ठा list_head expiring_list;
	काष्ठा rcu_head rcu;
पूर्ण;

अटल अंतरभूत काष्ठा स्वतःfs_sb_info *स्वतःfs_sbi(काष्ठा super_block *sb)
अणु
	वापस (काष्ठा स्वतःfs_sb_info *)(sb->s_fs_info);
पूर्ण

अटल अंतरभूत काष्ठा स्वतःfs_info *स्वतःfs_dentry_ino(काष्ठा dentry *dentry)
अणु
	वापस (काष्ठा स्वतःfs_info *)(dentry->d_fsdata);
पूर्ण

/* स्वतःfs_oz_mode(): करो we see the man behind the curtain?  (The
 * processes which करो manipulations क्रम us in user space sees the raw
 * fileप्रणाली without "magic".)
 */
अटल अंतरभूत पूर्णांक स्वतःfs_oz_mode(काष्ठा स्वतःfs_sb_info *sbi)
अणु
	वापस ((sbi->flags & AUTOFS_SBI_CATATONIC) ||
		 task_pgrp(current) == sbi->oz_pgrp);
पूर्ण

काष्ठा inode *स्वतःfs_get_inode(काष्ठा super_block *, umode_t);
व्योम स्वतःfs_मुक्त_ino(काष्ठा स्वतःfs_info *);

/* Expiration */
पूर्णांक is_स्वतःfs_dentry(काष्ठा dentry *);
पूर्णांक स्वतःfs_expire_रुको(स्थिर काष्ठा path *path, पूर्णांक rcu_walk);
पूर्णांक स्वतःfs_expire_run(काष्ठा super_block *, काष्ठा vfsmount *,
		      काष्ठा स्वतःfs_sb_info *,
		      काष्ठा स्वतःfs_packet_expire __user *);
पूर्णांक स्वतःfs_करो_expire_multi(काष्ठा super_block *sb, काष्ठा vfsmount *mnt,
			   काष्ठा स्वतःfs_sb_info *sbi, अचिन्हित पूर्णांक how);
पूर्णांक स्वतःfs_expire_multi(काष्ठा super_block *, काष्ठा vfsmount *,
			काष्ठा स्वतःfs_sb_info *, पूर्णांक __user *);

/* Device node initialization */

पूर्णांक स्वतःfs_dev_ioctl_init(व्योम);
व्योम स्वतःfs_dev_ioctl_निकास(व्योम);

/* Operations काष्ठाures */

बाह्य स्थिर काष्ठा inode_operations स्वतःfs_symlink_inode_operations;
बाह्य स्थिर काष्ठा inode_operations स्वतःfs_dir_inode_operations;
बाह्य स्थिर काष्ठा file_operations स्वतःfs_dir_operations;
बाह्य स्थिर काष्ठा file_operations स्वतःfs_root_operations;
बाह्य स्थिर काष्ठा dentry_operations स्वतःfs_dentry_operations;

/* VFS स्वतःmount flags management functions */
अटल अंतरभूत व्योम __managed_dentry_set_managed(काष्ठा dentry *dentry)
अणु
	dentry->d_flags |= (DCACHE_NEED_AUTOMOUNT|DCACHE_MANAGE_TRANSIT);
पूर्ण

अटल अंतरभूत व्योम managed_dentry_set_managed(काष्ठा dentry *dentry)
अणु
	spin_lock(&dentry->d_lock);
	__managed_dentry_set_managed(dentry);
	spin_unlock(&dentry->d_lock);
पूर्ण

अटल अंतरभूत व्योम __managed_dentry_clear_managed(काष्ठा dentry *dentry)
अणु
	dentry->d_flags &= ~(DCACHE_NEED_AUTOMOUNT|DCACHE_MANAGE_TRANSIT);
पूर्ण

अटल अंतरभूत व्योम managed_dentry_clear_managed(काष्ठा dentry *dentry)
अणु
	spin_lock(&dentry->d_lock);
	__managed_dentry_clear_managed(dentry);
	spin_unlock(&dentry->d_lock);
पूर्ण

/* Initializing function */

पूर्णांक स्वतःfs_fill_super(काष्ठा super_block *, व्योम *, पूर्णांक);
काष्ठा स्वतःfs_info *स्वतःfs_new_ino(काष्ठा स्वतःfs_sb_info *);
व्योम स्वतःfs_clean_ino(काष्ठा स्वतःfs_info *);

अटल अंतरभूत पूर्णांक स्वतःfs_prepare_pipe(काष्ठा file *pipe)
अणु
	अगर (!(pipe->f_mode & FMODE_CAN_WRITE))
		वापस -EINVAL;
	अगर (!S_ISFIFO(file_inode(pipe)->i_mode))
		वापस -EINVAL;
	/* We want a packet pipe */
	pipe->f_flags |= O_सूचीECT;
	/* We करोn't expect -EAGAIN */
	pipe->f_flags &= ~O_NONBLOCK;
	वापस 0;
पूर्ण

/* Queue management functions */

पूर्णांक स्वतःfs_रुको(काष्ठा स्वतःfs_sb_info *,
		 स्थिर काष्ठा path *, क्रमागत स्वतःfs_notअगरy);
पूर्णांक स्वतःfs_रुको_release(काष्ठा स्वतःfs_sb_info *, स्वतःfs_wqt_t, पूर्णांक);
व्योम स्वतःfs_catatonic_mode(काष्ठा स्वतःfs_sb_info *);

अटल अंतरभूत u32 स्वतःfs_get_dev(काष्ठा स्वतःfs_sb_info *sbi)
अणु
	वापस new_encode_dev(sbi->sb->s_dev);
पूर्ण

अटल अंतरभूत u64 स्वतःfs_get_ino(काष्ठा स्वतःfs_sb_info *sbi)
अणु
	वापस d_inode(sbi->sb->s_root)->i_ino;
पूर्ण

अटल अंतरभूत व्योम __स्वतःfs_add_expiring(काष्ठा dentry *dentry)
अणु
	काष्ठा स्वतःfs_sb_info *sbi = स्वतःfs_sbi(dentry->d_sb);
	काष्ठा स्वतःfs_info *ino = स्वतःfs_dentry_ino(dentry);

	अगर (ino) अणु
		अगर (list_empty(&ino->expiring))
			list_add(&ino->expiring, &sbi->expiring_list);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम स्वतःfs_add_expiring(काष्ठा dentry *dentry)
अणु
	काष्ठा स्वतःfs_sb_info *sbi = स्वतःfs_sbi(dentry->d_sb);
	काष्ठा स्वतःfs_info *ino = स्वतःfs_dentry_ino(dentry);

	अगर (ino) अणु
		spin_lock(&sbi->lookup_lock);
		अगर (list_empty(&ino->expiring))
			list_add(&ino->expiring, &sbi->expiring_list);
		spin_unlock(&sbi->lookup_lock);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम स्वतःfs_del_expiring(काष्ठा dentry *dentry)
अणु
	काष्ठा स्वतःfs_sb_info *sbi = स्वतःfs_sbi(dentry->d_sb);
	काष्ठा स्वतःfs_info *ino = स्वतःfs_dentry_ino(dentry);

	अगर (ino) अणु
		spin_lock(&sbi->lookup_lock);
		अगर (!list_empty(&ino->expiring))
			list_del_init(&ino->expiring);
		spin_unlock(&sbi->lookup_lock);
	पूर्ण
पूर्ण

व्योम स्वतःfs_समाप्त_sb(काष्ठा super_block *);
