<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/file_table.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *  Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)
 */

#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/file.h>
#समावेश <linux/fdtable.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/security.h>
#समावेश <linux/cred.h>
#समावेश <linux/eventpoll.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/mount.h>
#समावेश <linux/capability.h>
#समावेश <linux/cdev.h>
#समावेश <linux/fsnotअगरy.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/percpu_counter.h>
#समावेश <linux/percpu.h>
#समावेश <linux/task_work.h>
#समावेश <linux/ima.h>
#समावेश <linux/swap.h>

#समावेश <linux/atomic.h>

#समावेश "internal.h"

/* sysctl tunables... */
काष्ठा files_stat_काष्ठा files_stat = अणु
	.max_files = NR_खाता
पूर्ण;

/* SLAB cache क्रम file काष्ठाures */
अटल काष्ठा kmem_cache *filp_cachep __पढ़ो_mostly;

अटल काष्ठा percpu_counter nr_files __cacheline_aligned_in_smp;

अटल व्योम file_मुक्त_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा file *f = container_of(head, काष्ठा file, f_u.fu_rcuhead);

	put_cred(f->f_cred);
	kmem_cache_मुक्त(filp_cachep, f);
पूर्ण

अटल अंतरभूत व्योम file_मुक्त(काष्ठा file *f)
अणु
	security_file_मुक्त(f);
	अगर (!(f->f_mode & FMODE_NOACCOUNT))
		percpu_counter_dec(&nr_files);
	call_rcu(&f->f_u.fu_rcuhead, file_मुक्त_rcu);
पूर्ण

/*
 * Return the total number of खोलो files in the प्रणाली
 */
अटल दीर्घ get_nr_files(व्योम)
अणु
	वापस percpu_counter_पढ़ो_positive(&nr_files);
पूर्ण

/*
 * Return the maximum number of खोलो files in the प्रणाली
 */
अचिन्हित दीर्घ get_max_files(व्योम)
अणु
	वापस files_stat.max_files;
पूर्ण
EXPORT_SYMBOL_GPL(get_max_files);

/*
 * Handle nr_files sysctl
 */
#अगर defined(CONFIG_SYSCTL) && defined(CONFIG_PROC_FS)
पूर्णांक proc_nr_files(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
                     व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	files_stat.nr_files = get_nr_files();
	वापस proc_करोuदीर्घvec_minmax(table, ग_लिखो, buffer, lenp, ppos);
पूर्ण
#अन्यथा
पूर्णांक proc_nr_files(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
                     व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	वापस -ENOSYS;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा file *__alloc_file(पूर्णांक flags, स्थिर काष्ठा cred *cred)
अणु
	काष्ठा file *f;
	पूर्णांक error;

	f = kmem_cache_zalloc(filp_cachep, GFP_KERNEL);
	अगर (unlikely(!f))
		वापस ERR_PTR(-ENOMEM);

	f->f_cred = get_cred(cred);
	error = security_file_alloc(f);
	अगर (unlikely(error)) अणु
		file_मुक्त_rcu(&f->f_u.fu_rcuhead);
		वापस ERR_PTR(error);
	पूर्ण

	atomic_दीर्घ_set(&f->f_count, 1);
	rwlock_init(&f->f_owner.lock);
	spin_lock_init(&f->f_lock);
	mutex_init(&f->f_pos_lock);
	f->f_flags = flags;
	f->f_mode = OPEN_FMODE(flags);
	/* f->f_version: 0 */

	वापस f;
पूर्ण

/* Find an unused file काष्ठाure and वापस a poपूर्णांकer to it.
 * Returns an error poपूर्णांकer अगर some error happend e.g. we over file
 * काष्ठाures limit, run out of memory or operation is not permitted.
 *
 * Be very careful using this.  You are responsible क्रम
 * getting ग_लिखो access to any mount that you might assign
 * to this filp, अगर it is खोलोed क्रम ग_लिखो.  If this is not
 * करोne, you will imbalance पूर्णांक the mount's ग_लिखोr count
 * and a warning at __fput() समय.
 */
काष्ठा file *alloc_empty_file(पूर्णांक flags, स्थिर काष्ठा cred *cred)
अणु
	अटल दीर्घ old_max;
	काष्ठा file *f;

	/*
	 * Privileged users can go above max_files
	 */
	अगर (get_nr_files() >= files_stat.max_files && !capable(CAP_SYS_ADMIN)) अणु
		/*
		 * percpu_counters are inaccurate.  Do an expensive check beक्रमe
		 * we go and fail.
		 */
		अगर (percpu_counter_sum_positive(&nr_files) >= files_stat.max_files)
			जाओ over;
	पूर्ण

	f = __alloc_file(flags, cred);
	अगर (!IS_ERR(f))
		percpu_counter_inc(&nr_files);

	वापस f;

over:
	/* Ran out of filps - report that */
	अगर (get_nr_files() > old_max) अणु
		pr_info("VFS: file-max limit %lu reached\n", get_max_files());
		old_max = get_nr_files();
	पूर्ण
	वापस ERR_PTR(-ENखाता);
पूर्ण

/*
 * Variant of alloc_empty_file() that करोesn't check and modअगरy nr_files.
 *
 * Should not be used unless there's a very good reason to करो so.
 */
काष्ठा file *alloc_empty_file_noaccount(पूर्णांक flags, स्थिर काष्ठा cred *cred)
अणु
	काष्ठा file *f = __alloc_file(flags, cred);

	अगर (!IS_ERR(f))
		f->f_mode |= FMODE_NOACCOUNT;

	वापस f;
पूर्ण

/**
 * alloc_file - allocate and initialize a 'struct file'
 *
 * @path: the (dentry, vfsmount) pair क्रम the new file
 * @flags: O_... flags with which the new file will be खोलोed
 * @fop: the 'struct file_operations' क्रम the new file
 */
अटल काष्ठा file *alloc_file(स्थिर काष्ठा path *path, पूर्णांक flags,
		स्थिर काष्ठा file_operations *fop)
अणु
	काष्ठा file *file;

	file = alloc_empty_file(flags, current_cred());
	अगर (IS_ERR(file))
		वापस file;

	file->f_path = *path;
	file->f_inode = path->dentry->d_inode;
	file->f_mapping = path->dentry->d_inode->i_mapping;
	file->f_wb_err = filemap_sample_wb_err(file->f_mapping);
	file->f_sb_err = file_sample_sb_err(file);
	अगर ((file->f_mode & FMODE_READ) &&
	     likely(fop->पढ़ो || fop->पढ़ो_iter))
		file->f_mode |= FMODE_CAN_READ;
	अगर ((file->f_mode & FMODE_WRITE) &&
	     likely(fop->ग_लिखो || fop->ग_लिखो_iter))
		file->f_mode |= FMODE_CAN_WRITE;
	file->f_mode |= FMODE_OPENED;
	file->f_op = fop;
	अगर ((file->f_mode & (FMODE_READ | FMODE_WRITE)) == FMODE_READ)
		i_पढ़ोcount_inc(path->dentry->d_inode);
	वापस file;
पूर्ण

काष्ठा file *alloc_file_pseuकरो(काष्ठा inode *inode, काष्ठा vfsmount *mnt,
				स्थिर अक्षर *name, पूर्णांक flags,
				स्थिर काष्ठा file_operations *fops)
अणु
	अटल स्थिर काष्ठा dentry_operations anon_ops = अणु
		.d_dname = simple_dname
	पूर्ण;
	काष्ठा qstr this = QSTR_INIT(name, म_माप(name));
	काष्ठा path path;
	काष्ठा file *file;

	path.dentry = d_alloc_pseuकरो(mnt->mnt_sb, &this);
	अगर (!path.dentry)
		वापस ERR_PTR(-ENOMEM);
	अगर (!mnt->mnt_sb->s_d_op)
		d_set_d_op(path.dentry, &anon_ops);
	path.mnt = mntget(mnt);
	d_instantiate(path.dentry, inode);
	file = alloc_file(&path, flags, fops);
	अगर (IS_ERR(file)) अणु
		ihold(inode);
		path_put(&path);
	पूर्ण
	वापस file;
पूर्ण
EXPORT_SYMBOL(alloc_file_pseuकरो);

काष्ठा file *alloc_file_clone(काष्ठा file *base, पूर्णांक flags,
				स्थिर काष्ठा file_operations *fops)
अणु
	काष्ठा file *f = alloc_file(&base->f_path, flags, fops);
	अगर (!IS_ERR(f)) अणु
		path_get(&f->f_path);
		f->f_mapping = base->f_mapping;
	पूर्ण
	वापस f;
पूर्ण

/* the real guts of fput() - releasing the last reference to file
 */
अटल व्योम __fput(काष्ठा file *file)
अणु
	काष्ठा dentry *dentry = file->f_path.dentry;
	काष्ठा vfsmount *mnt = file->f_path.mnt;
	काष्ठा inode *inode = file->f_inode;
	भ_शेषe_t mode = file->f_mode;

	अगर (unlikely(!(file->f_mode & FMODE_OPENED)))
		जाओ out;

	might_sleep();

	fsnotअगरy_बंद(file);
	/*
	 * The function eventpoll_release() should be the first called
	 * in the file cleanup chain.
	 */
	eventpoll_release(file);
	locks_हटाओ_file(file);

	ima_file_मुक्त(file);
	अगर (unlikely(file->f_flags & FASYNC)) अणु
		अगर (file->f_op->fasync)
			file->f_op->fasync(-1, file, 0);
	पूर्ण
	अगर (file->f_op->release)
		file->f_op->release(inode, file);
	अगर (unlikely(S_ISCHR(inode->i_mode) && inode->i_cdev != शून्य &&
		     !(mode & FMODE_PATH))) अणु
		cdev_put(inode->i_cdev);
	पूर्ण
	fops_put(file->f_op);
	put_pid(file->f_owner.pid);
	अगर ((mode & (FMODE_READ | FMODE_WRITE)) == FMODE_READ)
		i_पढ़ोcount_dec(inode);
	अगर (mode & FMODE_WRITER) अणु
		put_ग_लिखो_access(inode);
		__mnt_drop_ग_लिखो(mnt);
	पूर्ण
	dput(dentry);
	अगर (unlikely(mode & FMODE_NEED_UNMOUNT))
		dissolve_on_fput(mnt);
	mntput(mnt);
out:
	file_मुक्त(file);
पूर्ण

अटल LLIST_HEAD(delayed_fput_list);
अटल व्योम delayed_fput(काष्ठा work_काष्ठा *unused)
अणु
	काष्ठा llist_node *node = llist_del_all(&delayed_fput_list);
	काष्ठा file *f, *t;

	llist_क्रम_each_entry_safe(f, t, node, f_u.fu_llist)
		__fput(f);
पूर्ण

अटल व्योम ____fput(काष्ठा callback_head *work)
अणु
	__fput(container_of(work, काष्ठा file, f_u.fu_rcuhead));
पूर्ण

/*
 * If kernel thपढ़ो really needs to have the final fput() it has करोne
 * to complete, call this.  The only user right now is the boot - we
 * *करो* need to make sure our ग_लिखोs to binaries on initramfs has
 * not left us with खोलोed काष्ठा file रुकोing क्रम __fput() - execve()
 * won't work without that.  Please, don't add more callers without
 * very good reasons; in particular, never call that with locks
 * held and never call that from a thपढ़ो that might need to करो
 * some work on any kind of umount.
 */
व्योम flush_delayed_fput(व्योम)
अणु
	delayed_fput(शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(flush_delayed_fput);

अटल DECLARE_DELAYED_WORK(delayed_fput_work, delayed_fput);

व्योम fput_many(काष्ठा file *file, अचिन्हित पूर्णांक refs)
अणु
	अगर (atomic_दीर्घ_sub_and_test(refs, &file->f_count)) अणु
		काष्ठा task_काष्ठा *task = current;

		अगर (likely(!in_पूर्णांकerrupt() && !(task->flags & PF_KTHREAD))) अणु
			init_task_work(&file->f_u.fu_rcuhead, ____fput);
			अगर (!task_work_add(task, &file->f_u.fu_rcuhead, TWA_RESUME))
				वापस;
			/*
			 * After this task has run निकास_task_work(),
			 * task_work_add() will fail.  Fall through to delayed
			 * fput to aव्योम leaking *file.
			 */
		पूर्ण

		अगर (llist_add(&file->f_u.fu_llist, &delayed_fput_list))
			schedule_delayed_work(&delayed_fput_work, 1);
	पूर्ण
पूर्ण

व्योम fput(काष्ठा file *file)
अणु
	fput_many(file, 1);
पूर्ण

/*
 * synchronous analog of fput(); क्रम kernel thपढ़ोs that might be needed
 * in some umount() (and thus can't use flush_delayed_fput() without
 * risking deadlocks), need to रुको क्रम completion of __fput() and know
 * क्रम this specअगरic काष्ठा file it won't involve anything that would
 * need them.  Use only अगर you really need it - at the very least,
 * करोn't blindly convert fput() by kernel thपढ़ो to that.
 */
व्योम __fput_sync(काष्ठा file *file)
अणु
	अगर (atomic_दीर्घ_dec_and_test(&file->f_count)) अणु
		काष्ठा task_काष्ठा *task = current;
		BUG_ON(!(task->flags & PF_KTHREAD));
		__fput(file);
	पूर्ण
पूर्ण

EXPORT_SYMBOL(fput);

व्योम __init files_init(व्योम)
अणु
	filp_cachep = kmem_cache_create("filp", माप(काष्ठा file), 0,
			SLAB_HWCACHE_ALIGN | SLAB_PANIC | SLAB_ACCOUNT, शून्य);
	percpu_counter_init(&nr_files, 0, GFP_KERNEL);
पूर्ण

/*
 * One file with associated inode and dcache is very roughly 1K. Per शेष
 * करो not use more than 10% of our memory क्रम files.
 */
व्योम __init files_maxfiles_init(व्योम)
अणु
	अचिन्हित दीर्घ n;
	अचिन्हित दीर्घ nr_pages = totalram_pages();
	अचिन्हित दीर्घ memreserve = (nr_pages - nr_मुक्त_pages()) * 3/2;

	memreserve = min(memreserve, nr_pages - 1);
	n = ((nr_pages - memreserve) * (PAGE_SIZE / 1024)) / 10;

	files_stat.max_files = max_t(अचिन्हित दीर्घ, n, NR_खाता);
पूर्ण
