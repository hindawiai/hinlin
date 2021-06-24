<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/export.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/task.h>
#समावेश <linux/fs.h>
#समावेश <linux/path.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs_काष्ठा.h>
#समावेश "internal.h"

/*
 * Replace the fs->अणुrooपंचांगnt,rootपूर्ण with अणुmnt,dentryपूर्ण. Put the old values.
 * It can block.
 */
व्योम set_fs_root(काष्ठा fs_काष्ठा *fs, स्थिर काष्ठा path *path)
अणु
	काष्ठा path old_root;

	path_get(path);
	spin_lock(&fs->lock);
	ग_लिखो_seqcount_begin(&fs->seq);
	old_root = fs->root;
	fs->root = *path;
	ग_लिखो_seqcount_end(&fs->seq);
	spin_unlock(&fs->lock);
	अगर (old_root.dentry)
		path_put(&old_root);
पूर्ण

/*
 * Replace the fs->अणुpwdmnt,pwdपूर्ण with अणुmnt,dentryपूर्ण. Put the old values.
 * It can block.
 */
व्योम set_fs_pwd(काष्ठा fs_काष्ठा *fs, स्थिर काष्ठा path *path)
अणु
	काष्ठा path old_pwd;

	path_get(path);
	spin_lock(&fs->lock);
	ग_लिखो_seqcount_begin(&fs->seq);
	old_pwd = fs->pwd;
	fs->pwd = *path;
	ग_लिखो_seqcount_end(&fs->seq);
	spin_unlock(&fs->lock);

	अगर (old_pwd.dentry)
		path_put(&old_pwd);
पूर्ण

अटल अंतरभूत पूर्णांक replace_path(काष्ठा path *p, स्थिर काष्ठा path *old, स्थिर काष्ठा path *new)
अणु
	अगर (likely(p->dentry != old->dentry || p->mnt != old->mnt))
		वापस 0;
	*p = *new;
	वापस 1;
पूर्ण

व्योम chroot_fs_refs(स्थिर काष्ठा path *old_root, स्थिर काष्ठा path *new_root)
अणु
	काष्ठा task_काष्ठा *g, *p;
	काष्ठा fs_काष्ठा *fs;
	पूर्णांक count = 0;

	पढ़ो_lock(&tasklist_lock);
	करो_each_thपढ़ो(g, p) अणु
		task_lock(p);
		fs = p->fs;
		अगर (fs) अणु
			पूर्णांक hits = 0;
			spin_lock(&fs->lock);
			ग_लिखो_seqcount_begin(&fs->seq);
			hits += replace_path(&fs->root, old_root, new_root);
			hits += replace_path(&fs->pwd, old_root, new_root);
			ग_लिखो_seqcount_end(&fs->seq);
			जबतक (hits--) अणु
				count++;
				path_get(new_root);
			पूर्ण
			spin_unlock(&fs->lock);
		पूर्ण
		task_unlock(p);
	पूर्ण जबतक_each_thपढ़ो(g, p);
	पढ़ो_unlock(&tasklist_lock);
	जबतक (count--)
		path_put(old_root);
पूर्ण

व्योम मुक्त_fs_काष्ठा(काष्ठा fs_काष्ठा *fs)
अणु
	path_put(&fs->root);
	path_put(&fs->pwd);
	kmem_cache_मुक्त(fs_cachep, fs);
पूर्ण

व्योम निकास_fs(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा fs_काष्ठा *fs = tsk->fs;

	अगर (fs) अणु
		पूर्णांक समाप्त;
		task_lock(tsk);
		spin_lock(&fs->lock);
		tsk->fs = शून्य;
		समाप्त = !--fs->users;
		spin_unlock(&fs->lock);
		task_unlock(tsk);
		अगर (समाप्त)
			मुक्त_fs_काष्ठा(fs);
	पूर्ण
पूर्ण

काष्ठा fs_काष्ठा *copy_fs_काष्ठा(काष्ठा fs_काष्ठा *old)
अणु
	काष्ठा fs_काष्ठा *fs = kmem_cache_alloc(fs_cachep, GFP_KERNEL);
	/* We करोn't need to lock fs - think why ;-) */
	अगर (fs) अणु
		fs->users = 1;
		fs->in_exec = 0;
		spin_lock_init(&fs->lock);
		seqcount_spinlock_init(&fs->seq, &fs->lock);
		fs->umask = old->umask;

		spin_lock(&old->lock);
		fs->root = old->root;
		path_get(&fs->root);
		fs->pwd = old->pwd;
		path_get(&fs->pwd);
		spin_unlock(&old->lock);
	पूर्ण
	वापस fs;
पूर्ण

पूर्णांक unshare_fs_काष्ठा(व्योम)
अणु
	काष्ठा fs_काष्ठा *fs = current->fs;
	काष्ठा fs_काष्ठा *new_fs = copy_fs_काष्ठा(fs);
	पूर्णांक समाप्त;

	अगर (!new_fs)
		वापस -ENOMEM;

	task_lock(current);
	spin_lock(&fs->lock);
	समाप्त = !--fs->users;
	current->fs = new_fs;
	spin_unlock(&fs->lock);
	task_unlock(current);

	अगर (समाप्त)
		मुक्त_fs_काष्ठा(fs);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(unshare_fs_काष्ठा);

पूर्णांक current_umask(व्योम)
अणु
	वापस current->fs->umask;
पूर्ण
EXPORT_SYMBOL(current_umask);

/* to be mentioned only in INIT_TASK */
काष्ठा fs_काष्ठा init_fs = अणु
	.users		= 1,
	.lock		= __SPIN_LOCK_UNLOCKED(init_fs.lock),
	.seq		= SEQCNT_SPINLOCK_ZERO(init_fs.seq, &init_fs.lock),
	.umask		= 0022,
पूर्ण;
