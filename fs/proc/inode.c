<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/proc/inode.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */

#समावेश <linux/cache.h>
#समावेश <linux/समय.स>
#समावेश <linux/proc_fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pid_namespace.h>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <linux/स्थिति.स>
#समावेश <linux/completion.h>
#समावेश <linux/poll.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/file.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/mount.h>
#समावेश <linux/bug.h>

#समावेश <linux/uaccess.h>

#समावेश "internal.h"

अटल व्योम proc_evict_inode(काष्ठा inode *inode)
अणु
	काष्ठा proc_dir_entry *de;
	काष्ठा ctl_table_header *head;
	काष्ठा proc_inode *ei = PROC_I(inode);

	truncate_inode_pages_final(&inode->i_data);
	clear_inode(inode);

	/* Stop tracking associated processes */
	अगर (ei->pid) अणु
		proc_pid_evict_inode(ei);
		ei->pid = शून्य;
	पूर्ण

	/* Let go of any associated proc directory entry */
	de = ei->pde;
	अगर (de) अणु
		pde_put(de);
		ei->pde = शून्य;
	पूर्ण

	head = ei->sysctl;
	अगर (head) अणु
		RCU_INIT_POINTER(ei->sysctl, शून्य);
		proc_sys_evict_inode(inode, head);
	पूर्ण
पूर्ण

अटल काष्ठा kmem_cache *proc_inode_cachep __ro_after_init;
अटल काष्ठा kmem_cache *pde_खोलोer_cache __ro_after_init;

अटल काष्ठा inode *proc_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा proc_inode *ei;

	ei = kmem_cache_alloc(proc_inode_cachep, GFP_KERNEL);
	अगर (!ei)
		वापस शून्य;
	ei->pid = शून्य;
	ei->fd = 0;
	ei->op.proc_get_link = शून्य;
	ei->pde = शून्य;
	ei->sysctl = शून्य;
	ei->sysctl_entry = शून्य;
	INIT_HLIST_NODE(&ei->sibling_inodes);
	ei->ns_ops = शून्य;
	वापस &ei->vfs_inode;
पूर्ण

अटल व्योम proc_मुक्त_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(proc_inode_cachep, PROC_I(inode));
पूर्ण

अटल व्योम init_once(व्योम *foo)
अणु
	काष्ठा proc_inode *ei = (काष्ठा proc_inode *) foo;

	inode_init_once(&ei->vfs_inode);
पूर्ण

व्योम __init proc_init_kmemcache(व्योम)
अणु
	proc_inode_cachep = kmem_cache_create("proc_inode_cache",
					     माप(काष्ठा proc_inode),
					     0, (SLAB_RECLAIM_ACCOUNT|
						SLAB_MEM_SPREAD|SLAB_ACCOUNT|
						SLAB_PANIC),
					     init_once);
	pde_खोलोer_cache =
		kmem_cache_create("pde_opener", माप(काष्ठा pde_खोलोer), 0,
				  SLAB_ACCOUNT|SLAB_PANIC, शून्य);
	proc_dir_entry_cache = kmem_cache_create_usercopy(
		"proc_dir_entry", SIZखातापूर्ण_PDE, 0, SLAB_PANIC,
		दुरत्व(काष्ठा proc_dir_entry, अंतरभूत_name),
		SIZखातापूर्ण_PDE_INLINE_NAME, शून्य);
	BUILD_BUG_ON(माप(काष्ठा proc_dir_entry) >= SIZखातापूर्ण_PDE);
पूर्ण

व्योम proc_invalidate_siblings_dcache(काष्ठा hlist_head *inodes, spinlock_t *lock)
अणु
	काष्ठा inode *inode;
	काष्ठा proc_inode *ei;
	काष्ठा hlist_node *node;
	काष्ठा super_block *old_sb = शून्य;

	rcu_पढ़ो_lock();
	क्रम (;;) अणु
		काष्ठा super_block *sb;
		node = hlist_first_rcu(inodes);
		अगर (!node)
			अवरोध;
		ei = hlist_entry(node, काष्ठा proc_inode, sibling_inodes);
		spin_lock(lock);
		hlist_del_init_rcu(&ei->sibling_inodes);
		spin_unlock(lock);

		inode = &ei->vfs_inode;
		sb = inode->i_sb;
		अगर ((sb != old_sb) && !atomic_inc_not_zero(&sb->s_active))
			जारी;
		inode = igrab(inode);
		rcu_पढ़ो_unlock();
		अगर (sb != old_sb) अणु
			अगर (old_sb)
				deactivate_super(old_sb);
			old_sb = sb;
		पूर्ण
		अगर (unlikely(!inode)) अणु
			rcu_पढ़ो_lock();
			जारी;
		पूर्ण

		अगर (S_ISसूची(inode->i_mode)) अणु
			काष्ठा dentry *dir = d_find_any_alias(inode);
			अगर (dir) अणु
				d_invalidate(dir);
				dput(dir);
			पूर्ण
		पूर्ण अन्यथा अणु
			काष्ठा dentry *dentry;
			जबतक ((dentry = d_find_alias(inode))) अणु
				d_invalidate(dentry);
				dput(dentry);
			पूर्ण
		पूर्ण
		iput(inode);

		rcu_पढ़ो_lock();
	पूर्ण
	rcu_पढ़ो_unlock();
	अगर (old_sb)
		deactivate_super(old_sb);
पूर्ण

अटल अंतरभूत स्थिर अक्षर *hidepid2str(क्रमागत proc_hidepid v)
अणु
	चयन (v) अणु
		हाल HIDEPID_OFF: वापस "off";
		हाल HIDEPID_NO_ACCESS: वापस "noaccess";
		हाल HIDEPID_INVISIBLE: वापस "invisible";
		हाल HIDEPID_NOT_PTRACEABLE: वापस "ptraceable";
	पूर्ण
	WARN_ONCE(1, "bad hide_pid value: %d\n", v);
	वापस "unknown";
पूर्ण

अटल पूर्णांक proc_show_options(काष्ठा seq_file *seq, काष्ठा dentry *root)
अणु
	काष्ठा proc_fs_info *fs_info = proc_sb_info(root->d_sb);

	अगर (!gid_eq(fs_info->pid_gid, GLOBAL_ROOT_GID))
		seq_म_लिखो(seq, ",gid=%u", from_kgid_munged(&init_user_ns, fs_info->pid_gid));
	अगर (fs_info->hide_pid != HIDEPID_OFF)
		seq_म_लिखो(seq, ",hidepid=%s", hidepid2str(fs_info->hide_pid));
	अगर (fs_info->piकरोnly != PROC_PIDONLY_OFF)
		seq_म_लिखो(seq, ",subset=pid");

	वापस 0;
पूर्ण

स्थिर काष्ठा super_operations proc_sops = अणु
	.alloc_inode	= proc_alloc_inode,
	.मुक्त_inode	= proc_मुक्त_inode,
	.drop_inode	= generic_delete_inode,
	.evict_inode	= proc_evict_inode,
	.statfs		= simple_statfs,
	.show_options	= proc_show_options,
पूर्ण;

क्रमागत अणुBIAS = -1U<<31पूर्ण;

अटल अंतरभूत पूर्णांक use_pde(काष्ठा proc_dir_entry *pde)
अणु
	वापस likely(atomic_inc_unless_negative(&pde->in_use));
पूर्ण

अटल व्योम unuse_pde(काष्ठा proc_dir_entry *pde)
अणु
	अगर (unlikely(atomic_dec_वापस(&pde->in_use) == BIAS))
		complete(pde->pde_unload_completion);
पूर्ण

/* pde is locked on entry, unlocked on निकास */
अटल व्योम बंद_pdeo(काष्ठा proc_dir_entry *pde, काष्ठा pde_खोलोer *pdeo)
	__releases(&pde->pde_unload_lock)
अणु
	/*
	 * बंद() (proc_reg_release()) can't delete an entry and proceed:
	 * ->release hook needs to be available at the right moment.
	 *
	 * rmmod (हटाओ_proc_entry() et al) can't delete an entry and proceed:
	 * "struct file" needs to be available at the right moment.
	 *
	 * Thereक्रमe, first process to enter this function करोes ->release() and
	 * संकेतs its completion to the other process which करोes nothing.
	 */
	अगर (pdeo->closing) अणु
		/* somebody अन्यथा is करोing that, just रुको */
		DECLARE_COMPLETION_ONSTACK(c);
		pdeo->c = &c;
		spin_unlock(&pde->pde_unload_lock);
		रुको_क्रम_completion(&c);
	पूर्ण अन्यथा अणु
		काष्ठा file *file;
		काष्ठा completion *c;

		pdeo->closing = true;
		spin_unlock(&pde->pde_unload_lock);
		file = pdeo->file;
		pde->proc_ops->proc_release(file_inode(file), file);
		spin_lock(&pde->pde_unload_lock);
		/* After ->release. */
		list_del(&pdeo->lh);
		c = pdeo->c;
		spin_unlock(&pde->pde_unload_lock);
		अगर (unlikely(c))
			complete(c);
		kmem_cache_मुक्त(pde_खोलोer_cache, pdeo);
	पूर्ण
पूर्ण

व्योम proc_entry_runकरोwn(काष्ठा proc_dir_entry *de)
अणु
	DECLARE_COMPLETION_ONSTACK(c);
	/* Wait until all existing callers पूर्णांकo module are करोne. */
	de->pde_unload_completion = &c;
	अगर (atomic_add_वापस(BIAS, &de->in_use) != BIAS)
		रुको_क्रम_completion(&c);

	/* ->pde_खोलोers list can't grow from now on. */

	spin_lock(&de->pde_unload_lock);
	जबतक (!list_empty(&de->pde_खोलोers)) अणु
		काष्ठा pde_खोलोer *pdeo;
		pdeo = list_first_entry(&de->pde_खोलोers, काष्ठा pde_खोलोer, lh);
		बंद_pdeo(de, pdeo);
		spin_lock(&de->pde_unload_lock);
	पूर्ण
	spin_unlock(&de->pde_unload_lock);
पूर्ण

अटल loff_t proc_reg_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	काष्ठा proc_dir_entry *pde = PDE(file_inode(file));
	loff_t rv = -EINVAL;

	अगर (pde_is_permanent(pde)) अणु
		वापस pde->proc_ops->proc_lseek(file, offset, whence);
	पूर्ण अन्यथा अगर (use_pde(pde)) अणु
		rv = pde->proc_ops->proc_lseek(file, offset, whence);
		unuse_pde(pde);
	पूर्ण
	वापस rv;
पूर्ण

अटल sमाप_प्रकार proc_reg_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	काष्ठा proc_dir_entry *pde = PDE(file_inode(iocb->ki_filp));
	sमाप_प्रकार ret;

	अगर (pde_is_permanent(pde))
		वापस pde->proc_ops->proc_पढ़ो_iter(iocb, iter);

	अगर (!use_pde(pde))
		वापस -EIO;
	ret = pde->proc_ops->proc_पढ़ो_iter(iocb, iter);
	unuse_pde(pde);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार pde_पढ़ो(काष्ठा proc_dir_entry *pde, काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count, loff_t *ppos)
अणु
	typeof_member(काष्ठा proc_ops, proc_पढ़ो) पढ़ो;

	पढ़ो = pde->proc_ops->proc_पढ़ो;
	अगर (पढ़ो)
		वापस पढ़ो(file, buf, count, ppos);
	वापस -EIO;
पूर्ण

अटल sमाप_प्रकार proc_reg_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा proc_dir_entry *pde = PDE(file_inode(file));
	sमाप_प्रकार rv = -EIO;

	अगर (pde_is_permanent(pde)) अणु
		वापस pde_पढ़ो(pde, file, buf, count, ppos);
	पूर्ण अन्यथा अगर (use_pde(pde)) अणु
		rv = pde_पढ़ो(pde, file, buf, count, ppos);
		unuse_pde(pde);
	पूर्ण
	वापस rv;
पूर्ण

अटल sमाप_प्रकार pde_ग_लिखो(काष्ठा proc_dir_entry *pde, काष्ठा file *file, स्थिर अक्षर __user *buf, माप_प्रकार count, loff_t *ppos)
अणु
	typeof_member(काष्ठा proc_ops, proc_ग_लिखो) ग_लिखो;

	ग_लिखो = pde->proc_ops->proc_ग_लिखो;
	अगर (ग_लिखो)
		वापस ग_लिखो(file, buf, count, ppos);
	वापस -EIO;
पूर्ण

अटल sमाप_प्रकार proc_reg_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा proc_dir_entry *pde = PDE(file_inode(file));
	sमाप_प्रकार rv = -EIO;

	अगर (pde_is_permanent(pde)) अणु
		वापस pde_ग_लिखो(pde, file, buf, count, ppos);
	पूर्ण अन्यथा अगर (use_pde(pde)) अणु
		rv = pde_ग_लिखो(pde, file, buf, count, ppos);
		unuse_pde(pde);
	पूर्ण
	वापस rv;
पूर्ण

अटल __poll_t pde_poll(काष्ठा proc_dir_entry *pde, काष्ठा file *file, काष्ठा poll_table_काष्ठा *pts)
अणु
	typeof_member(काष्ठा proc_ops, proc_poll) poll;

	poll = pde->proc_ops->proc_poll;
	अगर (poll)
		वापस poll(file, pts);
	वापस DEFAULT_POLLMASK;
पूर्ण

अटल __poll_t proc_reg_poll(काष्ठा file *file, काष्ठा poll_table_काष्ठा *pts)
अणु
	काष्ठा proc_dir_entry *pde = PDE(file_inode(file));
	__poll_t rv = DEFAULT_POLLMASK;

	अगर (pde_is_permanent(pde)) अणु
		वापस pde_poll(pde, file, pts);
	पूर्ण अन्यथा अगर (use_pde(pde)) अणु
		rv = pde_poll(pde, file, pts);
		unuse_pde(pde);
	पूर्ण
	वापस rv;
पूर्ण

अटल दीर्घ pde_ioctl(काष्ठा proc_dir_entry *pde, काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	typeof_member(काष्ठा proc_ops, proc_ioctl) ioctl;

	ioctl = pde->proc_ops->proc_ioctl;
	अगर (ioctl)
		वापस ioctl(file, cmd, arg);
	वापस -ENOTTY;
पूर्ण

अटल दीर्घ proc_reg_unlocked_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा proc_dir_entry *pde = PDE(file_inode(file));
	दीर्घ rv = -ENOTTY;

	अगर (pde_is_permanent(pde)) अणु
		वापस pde_ioctl(pde, file, cmd, arg);
	पूर्ण अन्यथा अगर (use_pde(pde)) अणु
		rv = pde_ioctl(pde, file, cmd, arg);
		unuse_pde(pde);
	पूर्ण
	वापस rv;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ pde_compat_ioctl(काष्ठा proc_dir_entry *pde, काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	typeof_member(काष्ठा proc_ops, proc_compat_ioctl) compat_ioctl;

	compat_ioctl = pde->proc_ops->proc_compat_ioctl;
	अगर (compat_ioctl)
		वापस compat_ioctl(file, cmd, arg);
	वापस -ENOTTY;
पूर्ण

अटल दीर्घ proc_reg_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा proc_dir_entry *pde = PDE(file_inode(file));
	दीर्घ rv = -ENOTTY;
	अगर (pde_is_permanent(pde)) अणु
		वापस pde_compat_ioctl(pde, file, cmd, arg);
	पूर्ण अन्यथा अगर (use_pde(pde)) अणु
		rv = pde_compat_ioctl(pde, file, cmd, arg);
		unuse_pde(pde);
	पूर्ण
	वापस rv;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक pde_mmap(काष्ठा proc_dir_entry *pde, काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	typeof_member(काष्ठा proc_ops, proc_mmap) mmap;

	mmap = pde->proc_ops->proc_mmap;
	अगर (mmap)
		वापस mmap(file, vma);
	वापस -EIO;
पूर्ण

अटल पूर्णांक proc_reg_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा proc_dir_entry *pde = PDE(file_inode(file));
	पूर्णांक rv = -EIO;

	अगर (pde_is_permanent(pde)) अणु
		वापस pde_mmap(pde, file, vma);
	पूर्ण अन्यथा अगर (use_pde(pde)) अणु
		rv = pde_mmap(pde, file, vma);
		unuse_pde(pde);
	पूर्ण
	वापस rv;
पूर्ण

अटल अचिन्हित दीर्घ
pde_get_unmapped_area(काष्ठा proc_dir_entry *pde, काष्ठा file *file, अचिन्हित दीर्घ orig_addr,
			   अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff,
			   अचिन्हित दीर्घ flags)
अणु
	typeof_member(काष्ठा proc_ops, proc_get_unmapped_area) get_area;

	get_area = pde->proc_ops->proc_get_unmapped_area;
#अगर_घोषित CONFIG_MMU
	अगर (!get_area)
		get_area = current->mm->get_unmapped_area;
#पूर्ण_अगर
	अगर (get_area)
		वापस get_area(file, orig_addr, len, pgoff, flags);
	वापस orig_addr;
पूर्ण

अटल अचिन्हित दीर्घ
proc_reg_get_unmapped_area(काष्ठा file *file, अचिन्हित दीर्घ orig_addr,
			   अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff,
			   अचिन्हित दीर्घ flags)
अणु
	काष्ठा proc_dir_entry *pde = PDE(file_inode(file));
	अचिन्हित दीर्घ rv = -EIO;

	अगर (pde_is_permanent(pde)) अणु
		वापस pde_get_unmapped_area(pde, file, orig_addr, len, pgoff, flags);
	पूर्ण अन्यथा अगर (use_pde(pde)) अणु
		rv = pde_get_unmapped_area(pde, file, orig_addr, len, pgoff, flags);
		unuse_pde(pde);
	पूर्ण
	वापस rv;
पूर्ण

अटल पूर्णांक proc_reg_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा proc_dir_entry *pde = PDE(inode);
	पूर्णांक rv = 0;
	typeof_member(काष्ठा proc_ops, proc_खोलो) खोलो;
	typeof_member(काष्ठा proc_ops, proc_release) release;
	काष्ठा pde_खोलोer *pdeo;

	अगर (pde_is_permanent(pde)) अणु
		खोलो = pde->proc_ops->proc_खोलो;
		अगर (खोलो)
			rv = खोलो(inode, file);
		वापस rv;
	पूर्ण

	/*
	 * Ensure that
	 * 1) PDE's ->release hook will be called no matter what
	 *    either normally by बंद()/->release, or क्रमcefully by
	 *    rmmod/हटाओ_proc_entry.
	 *
	 * 2) rmmod isn't blocked by खोलोing file in /proc and sitting on
	 *    the descriptor (including "rmmod foo </proc/foo" scenario).
	 *
	 * Save every "struct file" with custom ->release hook.
	 */
	अगर (!use_pde(pde))
		वापस -ENOENT;

	release = pde->proc_ops->proc_release;
	अगर (release) अणु
		pdeo = kmem_cache_alloc(pde_खोलोer_cache, GFP_KERNEL);
		अगर (!pdeo) अणु
			rv = -ENOMEM;
			जाओ out_unuse;
		पूर्ण
	पूर्ण

	खोलो = pde->proc_ops->proc_खोलो;
	अगर (खोलो)
		rv = खोलो(inode, file);

	अगर (release) अणु
		अगर (rv == 0) अणु
			/* To know what to release. */
			pdeo->file = file;
			pdeo->closing = false;
			pdeo->c = शून्य;
			spin_lock(&pde->pde_unload_lock);
			list_add(&pdeo->lh, &pde->pde_खोलोers);
			spin_unlock(&pde->pde_unload_lock);
		पूर्ण अन्यथा
			kmem_cache_मुक्त(pde_खोलोer_cache, pdeo);
	पूर्ण

out_unuse:
	unuse_pde(pde);
	वापस rv;
पूर्ण

अटल पूर्णांक proc_reg_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा proc_dir_entry *pde = PDE(inode);
	काष्ठा pde_खोलोer *pdeo;

	अगर (pde_is_permanent(pde)) अणु
		typeof_member(काष्ठा proc_ops, proc_release) release;

		release = pde->proc_ops->proc_release;
		अगर (release) अणु
			वापस release(inode, file);
		पूर्ण
		वापस 0;
	पूर्ण

	spin_lock(&pde->pde_unload_lock);
	list_क्रम_each_entry(pdeo, &pde->pde_खोलोers, lh) अणु
		अगर (pdeo->file == file) अणु
			बंद_pdeo(pde, pdeo);
			वापस 0;
		पूर्ण
	पूर्ण
	spin_unlock(&pde->pde_unload_lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations proc_reg_file_ops = अणु
	.llseek		= proc_reg_llseek,
	.पढ़ो		= proc_reg_पढ़ो,
	.ग_लिखो		= proc_reg_ग_लिखो,
	.poll		= proc_reg_poll,
	.unlocked_ioctl	= proc_reg_unlocked_ioctl,
	.mmap		= proc_reg_mmap,
	.get_unmapped_area = proc_reg_get_unmapped_area,
	.खोलो		= proc_reg_खोलो,
	.release	= proc_reg_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations proc_iter_file_ops = अणु
	.llseek		= proc_reg_llseek,
	.पढ़ो_iter	= proc_reg_पढ़ो_iter,
	.ग_लिखो		= proc_reg_ग_लिखो,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
	.poll		= proc_reg_poll,
	.unlocked_ioctl	= proc_reg_unlocked_ioctl,
	.mmap		= proc_reg_mmap,
	.get_unmapped_area = proc_reg_get_unmapped_area,
	.खोलो		= proc_reg_खोलो,
	.release	= proc_reg_release,
पूर्ण;

#अगर_घोषित CONFIG_COMPAT
अटल स्थिर काष्ठा file_operations proc_reg_file_ops_compat = अणु
	.llseek		= proc_reg_llseek,
	.पढ़ो		= proc_reg_पढ़ो,
	.ग_लिखो		= proc_reg_ग_लिखो,
	.poll		= proc_reg_poll,
	.unlocked_ioctl	= proc_reg_unlocked_ioctl,
	.compat_ioctl	= proc_reg_compat_ioctl,
	.mmap		= proc_reg_mmap,
	.get_unmapped_area = proc_reg_get_unmapped_area,
	.खोलो		= proc_reg_खोलो,
	.release	= proc_reg_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations proc_iter_file_ops_compat = अणु
	.llseek		= proc_reg_llseek,
	.पढ़ो_iter	= proc_reg_पढ़ो_iter,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
	.ग_लिखो		= proc_reg_ग_लिखो,
	.poll		= proc_reg_poll,
	.unlocked_ioctl	= proc_reg_unlocked_ioctl,
	.compat_ioctl	= proc_reg_compat_ioctl,
	.mmap		= proc_reg_mmap,
	.get_unmapped_area = proc_reg_get_unmapped_area,
	.खोलो		= proc_reg_खोलो,
	.release	= proc_reg_release,
पूर्ण;
#पूर्ण_अगर

अटल व्योम proc_put_link(व्योम *p)
अणु
	unuse_pde(p);
पूर्ण

अटल स्थिर अक्षर *proc_get_link(काष्ठा dentry *dentry,
				 काष्ठा inode *inode,
				 काष्ठा delayed_call *करोne)
अणु
	काष्ठा proc_dir_entry *pde = PDE(inode);
	अगर (!use_pde(pde))
		वापस ERR_PTR(-EINVAL);
	set_delayed_call(करोne, proc_put_link, pde);
	वापस pde->data;
पूर्ण

स्थिर काष्ठा inode_operations proc_link_inode_operations = अणु
	.get_link	= proc_get_link,
पूर्ण;

काष्ठा inode *proc_get_inode(काष्ठा super_block *sb, काष्ठा proc_dir_entry *de)
अणु
	काष्ठा inode *inode = new_inode(sb);

	अगर (!inode) अणु
		pde_put(de);
		वापस शून्य;
	पूर्ण

	inode->i_ino = de->low_ino;
	inode->i_mसमय = inode->i_aसमय = inode->i_स_समय = current_समय(inode);
	PROC_I(inode)->pde = de;
	अगर (is_empty_pde(de)) अणु
		make_empty_dir_inode(inode);
		वापस inode;
	पूर्ण

	अगर (de->mode) अणु
		inode->i_mode = de->mode;
		inode->i_uid = de->uid;
		inode->i_gid = de->gid;
	पूर्ण
	अगर (de->size)
		inode->i_size = de->size;
	अगर (de->nlink)
		set_nlink(inode, de->nlink);

	अगर (S_ISREG(inode->i_mode)) अणु
		inode->i_op = de->proc_iops;
		अगर (de->proc_ops->proc_पढ़ो_iter)
			inode->i_fop = &proc_iter_file_ops;
		अन्यथा
			inode->i_fop = &proc_reg_file_ops;
#अगर_घोषित CONFIG_COMPAT
		अगर (de->proc_ops->proc_compat_ioctl) अणु
			अगर (de->proc_ops->proc_पढ़ो_iter)
				inode->i_fop = &proc_iter_file_ops_compat;
			अन्यथा
				inode->i_fop = &proc_reg_file_ops_compat;
		पूर्ण
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (S_ISसूची(inode->i_mode)) अणु
		inode->i_op = de->proc_iops;
		inode->i_fop = de->proc_dir_ops;
	पूर्ण अन्यथा अगर (S_ISLNK(inode->i_mode)) अणु
		inode->i_op = de->proc_iops;
		inode->i_fop = शून्य;
	पूर्ण अन्यथा अणु
		BUG();
	पूर्ण
	वापस inode;
पूर्ण
