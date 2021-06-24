<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/ipc/shm.c
 * Copyright (C) 1992, 1993 Krishna Balasubramanian
 *	 Many improvements/fixes by Bruno Haible.
 * Replaced `काष्ठा shm_desc' by `struct vm_area_struct', July 1994.
 * Fixed the shm swap deallocation (shm_unuse()), August 1998 Andrea Arcangeli.
 *
 * /proc/sysvipc/shm support (c) 1999 Dragos Acostachioaie <dragos@iname.com>
 * BIGMEM support, Andrea Arcangeli <andrea@suse.de>
 * SMP thपढ़ो shm, Jean-Luc Boyard <jean-luc.boyard@siemens.fr>
 * HIGHMEM support, Ingo Molnar <mingo@redhat.com>
 * Make shmmax, shmall, shmmni sysctl'able, Christoph Rohland <cr@sap.com>
 * Shared /dev/zero support, Kanoj Sarcar <kanoj@sgi.com>
 * Move the mm functionality over to mm/shmem.c, Christoph Rohland <cr@sap.com>
 *
 * support क्रम audit of ipc object properties and permission changes
 * Dustin Kirkland <dustin.kirkland@us.ibm.com>
 *
 * namespaces support
 * OpenVZ, SWsoft Inc.
 * Pavel Emelianov <xemul@खोलोvz.org>
 *
 * Better ipc lock (kern_ipc_perm.lock) handling
 * Davidlohr Bueso <davidlohr.bueso@hp.com>, June 2013.
 */

#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/shm.h>
#समावेश <linux/init.h>
#समावेश <linux/file.h>
#समावेश <linux/mman.h>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/security.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/audit.h>
#समावेश <linux/capability.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/mount.h>
#समावेश <linux/ipc_namespace.h>
#समावेश <linux/rhashtable.h>

#समावेश <linux/uaccess.h>

#समावेश "util.h"

काष्ठा shmid_kernel /* निजी to the kernel */
अणु
	काष्ठा kern_ipc_perm	shm_perm;
	काष्ठा file		*shm_file;
	अचिन्हित दीर्घ		shm_nattch;
	अचिन्हित दीर्घ		shm_segsz;
	समय64_t		shm_atim;
	समय64_t		shm_dtim;
	समय64_t		shm_ctim;
	काष्ठा pid		*shm_cprid;
	काष्ठा pid		*shm_lprid;
	काष्ठा user_काष्ठा	*mlock_user;

	/* The task created the shm object.  शून्य अगर the task is dead. */
	काष्ठा task_काष्ठा	*shm_creator;
	काष्ठा list_head	shm_clist;	/* list by creator */
पूर्ण __अक्रमomize_layout;

/* shm_mode upper byte flags */
#घोषणा SHM_DEST	01000	/* segment will be destroyed on last detach */
#घोषणा SHM_LOCKED	02000   /* segment will not be swapped */

काष्ठा shm_file_data अणु
	पूर्णांक id;
	काष्ठा ipc_namespace *ns;
	काष्ठा file *file;
	स्थिर काष्ठा vm_operations_काष्ठा *vm_ops;
पूर्ण;

#घोषणा shm_file_data(file) (*((काष्ठा shm_file_data **)&(file)->निजी_data))

अटल स्थिर काष्ठा file_operations shm_file_operations;
अटल स्थिर काष्ठा vm_operations_काष्ठा shm_vm_ops;

#घोषणा shm_ids(ns)	((ns)->ids[IPC_SHM_IDS])

#घोषणा shm_unlock(shp)			\
	ipc_unlock(&(shp)->shm_perm)

अटल पूर्णांक newseg(काष्ठा ipc_namespace *, काष्ठा ipc_params *);
अटल व्योम shm_खोलो(काष्ठा vm_area_काष्ठा *vma);
अटल व्योम shm_बंद(काष्ठा vm_area_काष्ठा *vma);
अटल व्योम shm_destroy(काष्ठा ipc_namespace *ns, काष्ठा shmid_kernel *shp);
#अगर_घोषित CONFIG_PROC_FS
अटल पूर्णांक sysvipc_shm_proc_show(काष्ठा seq_file *s, व्योम *it);
#पूर्ण_अगर

व्योम shm_init_ns(काष्ठा ipc_namespace *ns)
अणु
	ns->shm_ctlmax = SHMMAX;
	ns->shm_ctlall = SHMALL;
	ns->shm_ctlmni = SHMMNI;
	ns->shm_rmid_क्रमced = 0;
	ns->shm_tot = 0;
	ipc_init_ids(&shm_ids(ns));
पूर्ण

/*
 * Called with shm_ids.rwsem (ग_लिखोr) and the shp काष्ठाure locked.
 * Only shm_ids.rwsem reमुख्यs locked on निकास.
 */
अटल व्योम करो_shm_rmid(काष्ठा ipc_namespace *ns, काष्ठा kern_ipc_perm *ipcp)
अणु
	काष्ठा shmid_kernel *shp;

	shp = container_of(ipcp, काष्ठा shmid_kernel, shm_perm);

	अगर (shp->shm_nattch) अणु
		shp->shm_perm.mode |= SHM_DEST;
		/* Do not find it any more */
		ipc_set_key_निजी(&shm_ids(ns), &shp->shm_perm);
		shm_unlock(shp);
	पूर्ण अन्यथा
		shm_destroy(ns, shp);
पूर्ण

#अगर_घोषित CONFIG_IPC_NS
व्योम shm_निकास_ns(काष्ठा ipc_namespace *ns)
अणु
	मुक्त_ipcs(ns, &shm_ids(ns), करो_shm_rmid);
	idr_destroy(&ns->ids[IPC_SHM_IDS].ipcs_idr);
	rhashtable_destroy(&ns->ids[IPC_SHM_IDS].key_ht);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init ipc_ns_init(व्योम)
अणु
	shm_init_ns(&init_ipc_ns);
	वापस 0;
पूर्ण

pure_initcall(ipc_ns_init);

व्योम __init shm_init(व्योम)
अणु
	ipc_init_proc_पूर्णांकerface("sysvipc/shm",
#अगर BITS_PER_LONG <= 32
				"       key      shmid perms       size  cpid  lpid nattch   uid   gid  cuid  cgid      atime      dtime      ctime        rss       swap\n",
#अन्यथा
				"       key      shmid perms                  size  cpid  lpid nattch   uid   gid  cuid  cgid      atime      dtime      ctime                   rss                  swap\n",
#पूर्ण_अगर
				IPC_SHM_IDS, sysvipc_shm_proc_show);
पूर्ण

अटल अंतरभूत काष्ठा shmid_kernel *shm_obtain_object(काष्ठा ipc_namespace *ns, पूर्णांक id)
अणु
	काष्ठा kern_ipc_perm *ipcp = ipc_obtain_object_idr(&shm_ids(ns), id);

	अगर (IS_ERR(ipcp))
		वापस ERR_CAST(ipcp);

	वापस container_of(ipcp, काष्ठा shmid_kernel, shm_perm);
पूर्ण

अटल अंतरभूत काष्ठा shmid_kernel *shm_obtain_object_check(काष्ठा ipc_namespace *ns, पूर्णांक id)
अणु
	काष्ठा kern_ipc_perm *ipcp = ipc_obtain_object_check(&shm_ids(ns), id);

	अगर (IS_ERR(ipcp))
		वापस ERR_CAST(ipcp);

	वापस container_of(ipcp, काष्ठा shmid_kernel, shm_perm);
पूर्ण

/*
 * shm_lock_(check_) routines are called in the paths where the rwsem
 * is not necessarily held.
 */
अटल अंतरभूत काष्ठा shmid_kernel *shm_lock(काष्ठा ipc_namespace *ns, पूर्णांक id)
अणु
	काष्ठा kern_ipc_perm *ipcp;

	rcu_पढ़ो_lock();
	ipcp = ipc_obtain_object_idr(&shm_ids(ns), id);
	अगर (IS_ERR(ipcp))
		जाओ err;

	ipc_lock_object(ipcp);
	/*
	 * ipc_rmid() may have alपढ़ोy मुक्तd the ID जबतक ipc_lock_object()
	 * was spinning: here verअगरy that the काष्ठाure is still valid.
	 * Upon races with RMID, वापस -EIDRM, thus indicating that
	 * the ID poपूर्णांकs to a हटाओd identअगरier.
	 */
	अगर (ipc_valid_object(ipcp)) अणु
		/* वापस a locked ipc object upon success */
		वापस container_of(ipcp, काष्ठा shmid_kernel, shm_perm);
	पूर्ण

	ipc_unlock_object(ipcp);
	ipcp = ERR_PTR(-EIDRM);
err:
	rcu_पढ़ो_unlock();
	/*
	 * Callers of shm_lock() must validate the status of the वापसed ipc
	 * object poपूर्णांकer and error out as appropriate.
	 */
	वापस ERR_CAST(ipcp);
पूर्ण

अटल अंतरभूत व्योम shm_lock_by_ptr(काष्ठा shmid_kernel *ipcp)
अणु
	rcu_पढ़ो_lock();
	ipc_lock_object(&ipcp->shm_perm);
पूर्ण

अटल व्योम shm_rcu_मुक्त(काष्ठा rcu_head *head)
अणु
	काष्ठा kern_ipc_perm *ptr = container_of(head, काष्ठा kern_ipc_perm,
							rcu);
	काष्ठा shmid_kernel *shp = container_of(ptr, काष्ठा shmid_kernel,
							shm_perm);
	security_shm_मुक्त(&shp->shm_perm);
	kvमुक्त(shp);
पूर्ण

अटल अंतरभूत व्योम shm_rmid(काष्ठा ipc_namespace *ns, काष्ठा shmid_kernel *s)
अणु
	list_del(&s->shm_clist);
	ipc_rmid(&shm_ids(ns), &s->shm_perm);
पूर्ण


अटल पूर्णांक __shm_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा file *file = vma->vm_file;
	काष्ठा shm_file_data *sfd = shm_file_data(file);
	काष्ठा shmid_kernel *shp;

	shp = shm_lock(sfd->ns, sfd->id);

	अगर (IS_ERR(shp))
		वापस PTR_ERR(shp);

	अगर (shp->shm_file != sfd->file) अणु
		/* ID was reused */
		shm_unlock(shp);
		वापस -EINVAL;
	पूर्ण

	shp->shm_atim = kसमय_get_real_seconds();
	ipc_update_pid(&shp->shm_lprid, task_tgid(current));
	shp->shm_nattch++;
	shm_unlock(shp);
	वापस 0;
पूर्ण

/* This is called by विभाजन, once क्रम every shm attach. */
अटल व्योम shm_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	पूर्णांक err = __shm_खोलो(vma);
	/*
	 * We raced in the idr lookup or with shm_destroy().
	 * Either way, the ID is busted.
	 */
	WARN_ON_ONCE(err);
पूर्ण

/*
 * shm_destroy - मुक्त the काष्ठा shmid_kernel
 *
 * @ns: namespace
 * @shp: काष्ठा to मुक्त
 *
 * It has to be called with shp and shm_ids.rwsem (ग_लिखोr) locked,
 * but वापसs with shp unlocked and मुक्तd.
 */
अटल व्योम shm_destroy(काष्ठा ipc_namespace *ns, काष्ठा shmid_kernel *shp)
अणु
	काष्ठा file *shm_file;

	shm_file = shp->shm_file;
	shp->shm_file = शून्य;
	ns->shm_tot -= (shp->shm_segsz + PAGE_SIZE - 1) >> PAGE_SHIFT;
	shm_rmid(ns, shp);
	shm_unlock(shp);
	अगर (!is_file_hugepages(shm_file))
		shmem_lock(shm_file, 0, shp->mlock_user);
	अन्यथा अगर (shp->mlock_user)
		user_shm_unlock(i_size_पढ़ो(file_inode(shm_file)),
				shp->mlock_user);
	fput(shm_file);
	ipc_update_pid(&shp->shm_cprid, शून्य);
	ipc_update_pid(&shp->shm_lprid, शून्य);
	ipc_rcu_putref(&shp->shm_perm, shm_rcu_मुक्त);
पूर्ण

/*
 * shm_may_destroy - identअगरies whether shm segment should be destroyed now
 *
 * Returns true अगर and only अगर there are no active users of the segment and
 * one of the following is true:
 *
 * 1) shmctl(id, IPC_RMID, शून्य) was called क्रम this shp
 *
 * 2) sysctl kernel.shm_rmid_क्रमced is set to 1.
 */
अटल bool shm_may_destroy(काष्ठा ipc_namespace *ns, काष्ठा shmid_kernel *shp)
अणु
	वापस (shp->shm_nattch == 0) &&
	       (ns->shm_rmid_क्रमced ||
		(shp->shm_perm.mode & SHM_DEST));
पूर्ण

/*
 * हटाओ the attach descriptor vma.
 * मुक्त memory क्रम segment अगर it is marked destroyed.
 * The descriptor has alपढ़ोy been हटाओd from the current->mm->mmap list
 * and will later be kमुक्त()d.
 */
अटल व्योम shm_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा file *file = vma->vm_file;
	काष्ठा shm_file_data *sfd = shm_file_data(file);
	काष्ठा shmid_kernel *shp;
	काष्ठा ipc_namespace *ns = sfd->ns;

	करोwn_ग_लिखो(&shm_ids(ns).rwsem);
	/* हटाओ from the list of attaches of the shm segment */
	shp = shm_lock(ns, sfd->id);

	/*
	 * We raced in the idr lookup or with shm_destroy().
	 * Either way, the ID is busted.
	 */
	अगर (WARN_ON_ONCE(IS_ERR(shp)))
		जाओ करोne; /* no-op */

	ipc_update_pid(&shp->shm_lprid, task_tgid(current));
	shp->shm_dtim = kसमय_get_real_seconds();
	shp->shm_nattch--;
	अगर (shm_may_destroy(ns, shp))
		shm_destroy(ns, shp);
	अन्यथा
		shm_unlock(shp);
करोne:
	up_ग_लिखो(&shm_ids(ns).rwsem);
पूर्ण

/* Called with ns->shm_ids(ns).rwsem locked */
अटल पूर्णांक shm_try_destroy_orphaned(पूर्णांक id, व्योम *p, व्योम *data)
अणु
	काष्ठा ipc_namespace *ns = data;
	काष्ठा kern_ipc_perm *ipcp = p;
	काष्ठा shmid_kernel *shp = container_of(ipcp, काष्ठा shmid_kernel, shm_perm);

	/*
	 * We want to destroy segments without users and with alपढ़ोy
	 * निकास'ed originating process.
	 *
	 * As shp->* are changed under rwsem, it's safe to skip shp locking.
	 */
	अगर (shp->shm_creator != शून्य)
		वापस 0;

	अगर (shm_may_destroy(ns, shp)) अणु
		shm_lock_by_ptr(shp);
		shm_destroy(ns, shp);
	पूर्ण
	वापस 0;
पूर्ण

व्योम shm_destroy_orphaned(काष्ठा ipc_namespace *ns)
अणु
	करोwn_ग_लिखो(&shm_ids(ns).rwsem);
	अगर (shm_ids(ns).in_use)
		idr_क्रम_each(&shm_ids(ns).ipcs_idr, &shm_try_destroy_orphaned, ns);
	up_ग_लिखो(&shm_ids(ns).rwsem);
पूर्ण

/* Locking assumes this will only be called with task == current */
व्योम निकास_shm(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा ipc_namespace *ns = task->nsproxy->ipc_ns;
	काष्ठा shmid_kernel *shp, *n;

	अगर (list_empty(&task->sysvshm.shm_clist))
		वापस;

	/*
	 * If kernel.shm_rmid_क्रमced is not set then only keep track of
	 * which shmids are orphaned, so that a later set of the sysctl
	 * can clean them up.
	 */
	अगर (!ns->shm_rmid_क्रमced) अणु
		करोwn_पढ़ो(&shm_ids(ns).rwsem);
		list_क्रम_each_entry(shp, &task->sysvshm.shm_clist, shm_clist)
			shp->shm_creator = शून्य;
		/*
		 * Only under पढ़ो lock but we are only called on current
		 * so no entry on the list will be shared.
		 */
		list_del(&task->sysvshm.shm_clist);
		up_पढ़ो(&shm_ids(ns).rwsem);
		वापस;
	पूर्ण

	/*
	 * Destroy all alपढ़ोy created segments, that were not yet mapped,
	 * and mark any mapped as orphan to cover the sysctl toggling.
	 * Destroy is skipped अगर shm_may_destroy() वापसs false.
	 */
	करोwn_ग_लिखो(&shm_ids(ns).rwsem);
	list_क्रम_each_entry_safe(shp, n, &task->sysvshm.shm_clist, shm_clist) अणु
		shp->shm_creator = शून्य;

		अगर (shm_may_destroy(ns, shp)) अणु
			shm_lock_by_ptr(shp);
			shm_destroy(ns, shp);
		पूर्ण
	पूर्ण

	/* Remove the list head from any segments still attached. */
	list_del(&task->sysvshm.shm_clist);
	up_ग_लिखो(&shm_ids(ns).rwsem);
पूर्ण

अटल vm_fault_t shm_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा file *file = vmf->vma->vm_file;
	काष्ठा shm_file_data *sfd = shm_file_data(file);

	वापस sfd->vm_ops->fault(vmf);
पूर्ण

अटल पूर्णांक shm_may_split(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr)
अणु
	काष्ठा file *file = vma->vm_file;
	काष्ठा shm_file_data *sfd = shm_file_data(file);

	अगर (sfd->vm_ops->may_split)
		वापस sfd->vm_ops->may_split(vma, addr);

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ shm_pagesize(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा file *file = vma->vm_file;
	काष्ठा shm_file_data *sfd = shm_file_data(file);

	अगर (sfd->vm_ops->pagesize)
		वापस sfd->vm_ops->pagesize(vma);

	वापस PAGE_SIZE;
पूर्ण

#अगर_घोषित CONFIG_NUMA
अटल पूर्णांक shm_set_policy(काष्ठा vm_area_काष्ठा *vma, काष्ठा mempolicy *new)
अणु
	काष्ठा file *file = vma->vm_file;
	काष्ठा shm_file_data *sfd = shm_file_data(file);
	पूर्णांक err = 0;

	अगर (sfd->vm_ops->set_policy)
		err = sfd->vm_ops->set_policy(vma, new);
	वापस err;
पूर्ण

अटल काष्ठा mempolicy *shm_get_policy(काष्ठा vm_area_काष्ठा *vma,
					अचिन्हित दीर्घ addr)
अणु
	काष्ठा file *file = vma->vm_file;
	काष्ठा shm_file_data *sfd = shm_file_data(file);
	काष्ठा mempolicy *pol = शून्य;

	अगर (sfd->vm_ops->get_policy)
		pol = sfd->vm_ops->get_policy(vma, addr);
	अन्यथा अगर (vma->vm_policy)
		pol = vma->vm_policy;

	वापस pol;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक shm_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा shm_file_data *sfd = shm_file_data(file);
	पूर्णांक ret;

	/*
	 * In हाल of remap_file_pages() emulation, the file can represent an
	 * IPC ID that was हटाओd, and possibly even reused by another shm
	 * segment alपढ़ोy.  Propagate this हाल as an error to caller.
	 */
	ret = __shm_खोलो(vma);
	अगर (ret)
		वापस ret;

	ret = call_mmap(sfd->file, vma);
	अगर (ret) अणु
		shm_बंद(vma);
		वापस ret;
	पूर्ण
	sfd->vm_ops = vma->vm_ops;
#अगर_घोषित CONFIG_MMU
	WARN_ON(!sfd->vm_ops->fault);
#पूर्ण_अगर
	vma->vm_ops = &shm_vm_ops;
	वापस 0;
पूर्ण

अटल पूर्णांक shm_release(काष्ठा inode *ino, काष्ठा file *file)
अणु
	काष्ठा shm_file_data *sfd = shm_file_data(file);

	put_ipc_ns(sfd->ns);
	fput(sfd->file);
	shm_file_data(file) = शून्य;
	kमुक्त(sfd);
	वापस 0;
पूर्ण

अटल पूर्णांक shm_fsync(काष्ठा file *file, loff_t start, loff_t end, पूर्णांक datasync)
अणु
	काष्ठा shm_file_data *sfd = shm_file_data(file);

	अगर (!sfd->file->f_op->fsync)
		वापस -EINVAL;
	वापस sfd->file->f_op->fsync(sfd->file, start, end, datasync);
पूर्ण

अटल दीर्घ shm_fallocate(काष्ठा file *file, पूर्णांक mode, loff_t offset,
			  loff_t len)
अणु
	काष्ठा shm_file_data *sfd = shm_file_data(file);

	अगर (!sfd->file->f_op->fallocate)
		वापस -EOPNOTSUPP;
	वापस sfd->file->f_op->fallocate(file, mode, offset, len);
पूर्ण

अटल अचिन्हित दीर्घ shm_get_unmapped_area(काष्ठा file *file,
	अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff,
	अचिन्हित दीर्घ flags)
अणु
	काष्ठा shm_file_data *sfd = shm_file_data(file);

	वापस sfd->file->f_op->get_unmapped_area(sfd->file, addr, len,
						pgoff, flags);
पूर्ण

अटल स्थिर काष्ठा file_operations shm_file_operations = अणु
	.mmap		= shm_mmap,
	.fsync		= shm_fsync,
	.release	= shm_release,
	.get_unmapped_area	= shm_get_unmapped_area,
	.llseek		= noop_llseek,
	.fallocate	= shm_fallocate,
पूर्ण;

/*
 * shm_file_operations_huge is now identical to shm_file_operations,
 * but we keep it distinct क्रम the sake of is_file_shm_hugepages().
 */
अटल स्थिर काष्ठा file_operations shm_file_operations_huge = अणु
	.mmap		= shm_mmap,
	.fsync		= shm_fsync,
	.release	= shm_release,
	.get_unmapped_area	= shm_get_unmapped_area,
	.llseek		= noop_llseek,
	.fallocate	= shm_fallocate,
पूर्ण;

bool is_file_shm_hugepages(काष्ठा file *file)
अणु
	वापस file->f_op == &shm_file_operations_huge;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा shm_vm_ops = अणु
	.खोलो	= shm_खोलो,	/* callback क्रम a new vm-area खोलो */
	.बंद	= shm_बंद,	/* callback क्रम when the vm-area is released */
	.fault	= shm_fault,
	.may_split = shm_may_split,
	.pagesize = shm_pagesize,
#अगर defined(CONFIG_NUMA)
	.set_policy = shm_set_policy,
	.get_policy = shm_get_policy,
#पूर्ण_अगर
पूर्ण;

/**
 * newseg - Create a new shared memory segment
 * @ns: namespace
 * @params: ptr to the काष्ठाure that contains key, size and shmflg
 *
 * Called with shm_ids.rwsem held as a ग_लिखोr.
 */
अटल पूर्णांक newseg(काष्ठा ipc_namespace *ns, काष्ठा ipc_params *params)
अणु
	key_t key = params->key;
	पूर्णांक shmflg = params->flg;
	माप_प्रकार size = params->u.size;
	पूर्णांक error;
	काष्ठा shmid_kernel *shp;
	माप_प्रकार numpages = (size + PAGE_SIZE - 1) >> PAGE_SHIFT;
	काष्ठा file *file;
	अक्षर name[13];
	vm_flags_t acctflag = 0;

	अगर (size < SHMMIN || size > ns->shm_ctlmax)
		वापस -EINVAL;

	अगर (numpages << PAGE_SHIFT < size)
		वापस -ENOSPC;

	अगर (ns->shm_tot + numpages < ns->shm_tot ||
			ns->shm_tot + numpages > ns->shm_ctlall)
		वापस -ENOSPC;

	shp = kvदो_स्मृति(माप(*shp), GFP_KERNEL);
	अगर (unlikely(!shp))
		वापस -ENOMEM;

	shp->shm_perm.key = key;
	shp->shm_perm.mode = (shmflg & S_IRWXUGO);
	shp->mlock_user = शून्य;

	shp->shm_perm.security = शून्य;
	error = security_shm_alloc(&shp->shm_perm);
	अगर (error) अणु
		kvमुक्त(shp);
		वापस error;
	पूर्ण

	प्र_लिखो(name, "SYSV%08x", key);
	अगर (shmflg & SHM_HUGETLB) अणु
		काष्ठा hstate *hs;
		माप_प्रकार hugesize;

		hs = hstate_sizelog((shmflg >> SHM_HUGE_SHIFT) & SHM_HUGE_MASK);
		अगर (!hs) अणु
			error = -EINVAL;
			जाओ no_file;
		पूर्ण
		hugesize = ALIGN(size, huge_page_size(hs));

		/* hugetlb_file_setup applies strict accounting */
		अगर (shmflg & SHM_NORESERVE)
			acctflag = VM_NORESERVE;
		file = hugetlb_file_setup(name, hugesize, acctflag,
				  &shp->mlock_user, HUGETLB_SHMFS_INODE,
				(shmflg >> SHM_HUGE_SHIFT) & SHM_HUGE_MASK);
	पूर्ण अन्यथा अणु
		/*
		 * Do not allow no accounting क्रम OVERCOMMIT_NEVER, even
		 * अगर it's asked क्रम.
		 */
		अगर  ((shmflg & SHM_NORESERVE) &&
				sysctl_overcommit_memory != OVERCOMMIT_NEVER)
			acctflag = VM_NORESERVE;
		file = shmem_kernel_file_setup(name, size, acctflag);
	पूर्ण
	error = PTR_ERR(file);
	अगर (IS_ERR(file))
		जाओ no_file;

	shp->shm_cprid = get_pid(task_tgid(current));
	shp->shm_lprid = शून्य;
	shp->shm_atim = shp->shm_dtim = 0;
	shp->shm_ctim = kसमय_get_real_seconds();
	shp->shm_segsz = size;
	shp->shm_nattch = 0;
	shp->shm_file = file;
	shp->shm_creator = current;

	/* ipc_addid() locks shp upon success. */
	error = ipc_addid(&shm_ids(ns), &shp->shm_perm, ns->shm_ctlmni);
	अगर (error < 0)
		जाओ no_id;

	list_add(&shp->shm_clist, &current->sysvshm.shm_clist);

	/*
	 * shmid माला_लो reported as "inode#" in /proc/pid/maps.
	 * proc-ps tools use this. Changing this will अवरोध them.
	 */
	file_inode(file)->i_ino = shp->shm_perm.id;

	ns->shm_tot += numpages;
	error = shp->shm_perm.id;

	ipc_unlock_object(&shp->shm_perm);
	rcu_पढ़ो_unlock();
	वापस error;

no_id:
	ipc_update_pid(&shp->shm_cprid, शून्य);
	ipc_update_pid(&shp->shm_lprid, शून्य);
	अगर (is_file_hugepages(file) && shp->mlock_user)
		user_shm_unlock(size, shp->mlock_user);
	fput(file);
	ipc_rcu_putref(&shp->shm_perm, shm_rcu_मुक्त);
	वापस error;
no_file:
	call_rcu(&shp->shm_perm.rcu, shm_rcu_मुक्त);
	वापस error;
पूर्ण

/*
 * Called with shm_ids.rwsem and ipcp locked.
 */
अटल पूर्णांक shm_more_checks(काष्ठा kern_ipc_perm *ipcp, काष्ठा ipc_params *params)
अणु
	काष्ठा shmid_kernel *shp;

	shp = container_of(ipcp, काष्ठा shmid_kernel, shm_perm);
	अगर (shp->shm_segsz < params->u.size)
		वापस -EINVAL;

	वापस 0;
पूर्ण

दीर्घ ksys_shmget(key_t key, माप_प्रकार size, पूर्णांक shmflg)
अणु
	काष्ठा ipc_namespace *ns;
	अटल स्थिर काष्ठा ipc_ops shm_ops = अणु
		.getnew = newseg,
		.associate = security_shm_associate,
		.more_checks = shm_more_checks,
	पूर्ण;
	काष्ठा ipc_params shm_params;

	ns = current->nsproxy->ipc_ns;

	shm_params.key = key;
	shm_params.flg = shmflg;
	shm_params.u.size = size;

	वापस ipcget(ns, &shm_ids(ns), &shm_ops, &shm_params);
पूर्ण

SYSCALL_DEFINE3(shmget, key_t, key, माप_प्रकार, size, पूर्णांक, shmflg)
अणु
	वापस ksys_shmget(key, size, shmflg);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ copy_shmid_to_user(व्योम __user *buf, काष्ठा shmid64_ds *in, पूर्णांक version)
अणु
	चयन (version) अणु
	हाल IPC_64:
		वापस copy_to_user(buf, in, माप(*in));
	हाल IPC_OLD:
	    अणु
		काष्ठा shmid_ds out;

		स_रखो(&out, 0, माप(out));
		ipc64_perm_to_ipc_perm(&in->shm_perm, &out.shm_perm);
		out.shm_segsz	= in->shm_segsz;
		out.shm_aसमय	= in->shm_aसमय;
		out.shm_dसमय	= in->shm_dसमय;
		out.shm_स_समय	= in->shm_स_समय;
		out.shm_cpid	= in->shm_cpid;
		out.shm_lpid	= in->shm_lpid;
		out.shm_nattch	= in->shm_nattch;

		वापस copy_to_user(buf, &out, माप(out));
	    पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
copy_shmid_from_user(काष्ठा shmid64_ds *out, व्योम __user *buf, पूर्णांक version)
अणु
	चयन (version) अणु
	हाल IPC_64:
		अगर (copy_from_user(out, buf, माप(*out)))
			वापस -EFAULT;
		वापस 0;
	हाल IPC_OLD:
	    अणु
		काष्ठा shmid_ds tbuf_old;

		अगर (copy_from_user(&tbuf_old, buf, माप(tbuf_old)))
			वापस -EFAULT;

		out->shm_perm.uid	= tbuf_old.shm_perm.uid;
		out->shm_perm.gid	= tbuf_old.shm_perm.gid;
		out->shm_perm.mode	= tbuf_old.shm_perm.mode;

		वापस 0;
	    पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ copy_shminfo_to_user(व्योम __user *buf, काष्ठा shminfo64 *in, पूर्णांक version)
अणु
	चयन (version) अणु
	हाल IPC_64:
		वापस copy_to_user(buf, in, माप(*in));
	हाल IPC_OLD:
	    अणु
		काष्ठा shminfo out;

		अगर (in->shmmax > पूर्णांक_उच्च)
			out.shmmax = पूर्णांक_उच्च;
		अन्यथा
			out.shmmax = (पूर्णांक)in->shmmax;

		out.shmmin	= in->shmmin;
		out.shmmni	= in->shmmni;
		out.shmseg	= in->shmseg;
		out.shmall	= in->shmall;

		वापस copy_to_user(buf, &out, माप(out));
	    पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/*
 * Calculate and add used RSS and swap pages of a shm.
 * Called with shm_ids.rwsem held as a पढ़ोer
 */
अटल व्योम shm_add_rss_swap(काष्ठा shmid_kernel *shp,
	अचिन्हित दीर्घ *rss_add, अचिन्हित दीर्घ *swp_add)
अणु
	काष्ठा inode *inode;

	inode = file_inode(shp->shm_file);

	अगर (is_file_hugepages(shp->shm_file)) अणु
		काष्ठा address_space *mapping = inode->i_mapping;
		काष्ठा hstate *h = hstate_file(shp->shm_file);
		*rss_add += pages_per_huge_page(h) * mapping->nrpages;
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_SHMEM
		काष्ठा shmem_inode_info *info = SHMEM_I(inode);

		spin_lock_irq(&info->lock);
		*rss_add += inode->i_mapping->nrpages;
		*swp_add += info->swapped;
		spin_unlock_irq(&info->lock);
#अन्यथा
		*rss_add += inode->i_mapping->nrpages;
#पूर्ण_अगर
	पूर्ण
पूर्ण

/*
 * Called with shm_ids.rwsem held as a पढ़ोer
 */
अटल व्योम shm_get_stat(काष्ठा ipc_namespace *ns, अचिन्हित दीर्घ *rss,
		अचिन्हित दीर्घ *swp)
अणु
	पूर्णांक next_id;
	पूर्णांक total, in_use;

	*rss = 0;
	*swp = 0;

	in_use = shm_ids(ns).in_use;

	क्रम (total = 0, next_id = 0; total < in_use; next_id++) अणु
		काष्ठा kern_ipc_perm *ipc;
		काष्ठा shmid_kernel *shp;

		ipc = idr_find(&shm_ids(ns).ipcs_idr, next_id);
		अगर (ipc == शून्य)
			जारी;
		shp = container_of(ipc, काष्ठा shmid_kernel, shm_perm);

		shm_add_rss_swap(shp, rss, swp);

		total++;
	पूर्ण
पूर्ण

/*
 * This function handles some shmctl commands which require the rwsem
 * to be held in ग_लिखो mode.
 * NOTE: no locks must be held, the rwsem is taken inside this function.
 */
अटल पूर्णांक shmctl_करोwn(काष्ठा ipc_namespace *ns, पूर्णांक shmid, पूर्णांक cmd,
		       काष्ठा shmid64_ds *shmid64)
अणु
	काष्ठा kern_ipc_perm *ipcp;
	काष्ठा shmid_kernel *shp;
	पूर्णांक err;

	करोwn_ग_लिखो(&shm_ids(ns).rwsem);
	rcu_पढ़ो_lock();

	ipcp = ipcctl_obtain_check(ns, &shm_ids(ns), shmid, cmd,
				      &shmid64->shm_perm, 0);
	अगर (IS_ERR(ipcp)) अणु
		err = PTR_ERR(ipcp);
		जाओ out_unlock1;
	पूर्ण

	shp = container_of(ipcp, काष्ठा shmid_kernel, shm_perm);

	err = security_shm_shmctl(&shp->shm_perm, cmd);
	अगर (err)
		जाओ out_unlock1;

	चयन (cmd) अणु
	हाल IPC_RMID:
		ipc_lock_object(&shp->shm_perm);
		/* करो_shm_rmid unlocks the ipc object and rcu */
		करो_shm_rmid(ns, ipcp);
		जाओ out_up;
	हाल IPC_SET:
		ipc_lock_object(&shp->shm_perm);
		err = ipc_update_perm(&shmid64->shm_perm, ipcp);
		अगर (err)
			जाओ out_unlock0;
		shp->shm_ctim = kसमय_get_real_seconds();
		अवरोध;
	शेष:
		err = -EINVAL;
		जाओ out_unlock1;
	पूर्ण

out_unlock0:
	ipc_unlock_object(&shp->shm_perm);
out_unlock1:
	rcu_पढ़ो_unlock();
out_up:
	up_ग_लिखो(&shm_ids(ns).rwsem);
	वापस err;
पूर्ण

अटल पूर्णांक shmctl_ipc_info(काष्ठा ipc_namespace *ns,
			   काष्ठा shminfo64 *shminfo)
अणु
	पूर्णांक err = security_shm_shmctl(शून्य, IPC_INFO);
	अगर (!err) अणु
		स_रखो(shminfo, 0, माप(*shminfo));
		shminfo->shmmni = shminfo->shmseg = ns->shm_ctlmni;
		shminfo->shmmax = ns->shm_ctlmax;
		shminfo->shmall = ns->shm_ctlall;
		shminfo->shmmin = SHMMIN;
		करोwn_पढ़ो(&shm_ids(ns).rwsem);
		err = ipc_get_maxidx(&shm_ids(ns));
		up_पढ़ो(&shm_ids(ns).rwsem);
		अगर (err < 0)
			err = 0;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक shmctl_shm_info(काष्ठा ipc_namespace *ns,
			   काष्ठा shm_info *shm_info)
अणु
	पूर्णांक err = security_shm_shmctl(शून्य, SHM_INFO);
	अगर (!err) अणु
		स_रखो(shm_info, 0, माप(*shm_info));
		करोwn_पढ़ो(&shm_ids(ns).rwsem);
		shm_info->used_ids = shm_ids(ns).in_use;
		shm_get_stat(ns, &shm_info->shm_rss, &shm_info->shm_swp);
		shm_info->shm_tot = ns->shm_tot;
		shm_info->swap_attempts = 0;
		shm_info->swap_successes = 0;
		err = ipc_get_maxidx(&shm_ids(ns));
		up_पढ़ो(&shm_ids(ns).rwsem);
		अगर (err < 0)
			err = 0;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक shmctl_stat(काष्ठा ipc_namespace *ns, पूर्णांक shmid,
			पूर्णांक cmd, काष्ठा shmid64_ds *tbuf)
अणु
	काष्ठा shmid_kernel *shp;
	पूर्णांक err;

	स_रखो(tbuf, 0, माप(*tbuf));

	rcu_पढ़ो_lock();
	अगर (cmd == SHM_STAT || cmd == SHM_STAT_ANY) अणु
		shp = shm_obtain_object(ns, shmid);
		अगर (IS_ERR(shp)) अणु
			err = PTR_ERR(shp);
			जाओ out_unlock;
		पूर्ण
	पूर्ण अन्यथा अणु /* IPC_STAT */
		shp = shm_obtain_object_check(ns, shmid);
		अगर (IS_ERR(shp)) अणु
			err = PTR_ERR(shp);
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	/*
	 * Semantically SHM_STAT_ANY ought to be identical to
	 * that functionality provided by the /proc/sysvipc/
	 * पूर्णांकerface. As such, only audit these calls and
	 * करो not करो traditional S_IRUGO permission checks on
	 * the ipc object.
	 */
	अगर (cmd == SHM_STAT_ANY)
		audit_ipc_obj(&shp->shm_perm);
	अन्यथा अणु
		err = -EACCES;
		अगर (ipcperms(ns, &shp->shm_perm, S_IRUGO))
			जाओ out_unlock;
	पूर्ण

	err = security_shm_shmctl(&shp->shm_perm, cmd);
	अगर (err)
		जाओ out_unlock;

	ipc_lock_object(&shp->shm_perm);

	अगर (!ipc_valid_object(&shp->shm_perm)) अणु
		ipc_unlock_object(&shp->shm_perm);
		err = -EIDRM;
		जाओ out_unlock;
	पूर्ण

	kernel_to_ipc64_perm(&shp->shm_perm, &tbuf->shm_perm);
	tbuf->shm_segsz	= shp->shm_segsz;
	tbuf->shm_aसमय	= shp->shm_atim;
	tbuf->shm_dसमय	= shp->shm_dtim;
	tbuf->shm_स_समय	= shp->shm_ctim;
#अगर_अघोषित CONFIG_64BIT
	tbuf->shm_aसमय_high = shp->shm_atim >> 32;
	tbuf->shm_dसमय_high = shp->shm_dtim >> 32;
	tbuf->shm_स_समय_high = shp->shm_ctim >> 32;
#पूर्ण_अगर
	tbuf->shm_cpid	= pid_vnr(shp->shm_cprid);
	tbuf->shm_lpid	= pid_vnr(shp->shm_lprid);
	tbuf->shm_nattch = shp->shm_nattch;

	अगर (cmd == IPC_STAT) अणु
		/*
		 * As defined in SUS:
		 * Return 0 on success
		 */
		err = 0;
	पूर्ण अन्यथा अणु
		/*
		 * SHM_STAT and SHM_STAT_ANY (both Linux specअगरic)
		 * Return the full id, including the sequence number
		 */
		err = shp->shm_perm.id;
	पूर्ण

	ipc_unlock_object(&shp->shm_perm);
out_unlock:
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण

अटल पूर्णांक shmctl_करो_lock(काष्ठा ipc_namespace *ns, पूर्णांक shmid, पूर्णांक cmd)
अणु
	काष्ठा shmid_kernel *shp;
	काष्ठा file *shm_file;
	पूर्णांक err;

	rcu_पढ़ो_lock();
	shp = shm_obtain_object_check(ns, shmid);
	अगर (IS_ERR(shp)) अणु
		err = PTR_ERR(shp);
		जाओ out_unlock1;
	पूर्ण

	audit_ipc_obj(&(shp->shm_perm));
	err = security_shm_shmctl(&shp->shm_perm, cmd);
	अगर (err)
		जाओ out_unlock1;

	ipc_lock_object(&shp->shm_perm);

	/* check अगर shm_destroy() is tearing करोwn shp */
	अगर (!ipc_valid_object(&shp->shm_perm)) अणु
		err = -EIDRM;
		जाओ out_unlock0;
	पूर्ण

	अगर (!ns_capable(ns->user_ns, CAP_IPC_LOCK)) अणु
		kuid_t euid = current_euid();

		अगर (!uid_eq(euid, shp->shm_perm.uid) &&
		    !uid_eq(euid, shp->shm_perm.cuid)) अणु
			err = -EPERM;
			जाओ out_unlock0;
		पूर्ण
		अगर (cmd == SHM_LOCK && !rlimit(RLIMIT_MEMLOCK)) अणु
			err = -EPERM;
			जाओ out_unlock0;
		पूर्ण
	पूर्ण

	shm_file = shp->shm_file;
	अगर (is_file_hugepages(shm_file))
		जाओ out_unlock0;

	अगर (cmd == SHM_LOCK) अणु
		काष्ठा user_काष्ठा *user = current_user();

		err = shmem_lock(shm_file, 1, user);
		अगर (!err && !(shp->shm_perm.mode & SHM_LOCKED)) अणु
			shp->shm_perm.mode |= SHM_LOCKED;
			shp->mlock_user = user;
		पूर्ण
		जाओ out_unlock0;
	पूर्ण

	/* SHM_UNLOCK */
	अगर (!(shp->shm_perm.mode & SHM_LOCKED))
		जाओ out_unlock0;
	shmem_lock(shm_file, 0, shp->mlock_user);
	shp->shm_perm.mode &= ~SHM_LOCKED;
	shp->mlock_user = शून्य;
	get_file(shm_file);
	ipc_unlock_object(&shp->shm_perm);
	rcu_पढ़ो_unlock();
	shmem_unlock_mapping(shm_file->f_mapping);

	fput(shm_file);
	वापस err;

out_unlock0:
	ipc_unlock_object(&shp->shm_perm);
out_unlock1:
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण

अटल दीर्घ ksys_shmctl(पूर्णांक shmid, पूर्णांक cmd, काष्ठा shmid_ds __user *buf, पूर्णांक version)
अणु
	पूर्णांक err;
	काष्ठा ipc_namespace *ns;
	काष्ठा shmid64_ds sem64;

	अगर (cmd < 0 || shmid < 0)
		वापस -EINVAL;

	ns = current->nsproxy->ipc_ns;

	चयन (cmd) अणु
	हाल IPC_INFO: अणु
		काष्ठा shminfo64 shminfo;
		err = shmctl_ipc_info(ns, &shminfo);
		अगर (err < 0)
			वापस err;
		अगर (copy_shminfo_to_user(buf, &shminfo, version))
			err = -EFAULT;
		वापस err;
	पूर्ण
	हाल SHM_INFO: अणु
		काष्ठा shm_info shm_info;
		err = shmctl_shm_info(ns, &shm_info);
		अगर (err < 0)
			वापस err;
		अगर (copy_to_user(buf, &shm_info, माप(shm_info)))
			err = -EFAULT;
		वापस err;
	पूर्ण
	हाल SHM_STAT:
	हाल SHM_STAT_ANY:
	हाल IPC_STAT: अणु
		err = shmctl_stat(ns, shmid, cmd, &sem64);
		अगर (err < 0)
			वापस err;
		अगर (copy_shmid_to_user(buf, &sem64, version))
			err = -EFAULT;
		वापस err;
	पूर्ण
	हाल IPC_SET:
		अगर (copy_shmid_from_user(&sem64, buf, version))
			वापस -EFAULT;
		fallthrough;
	हाल IPC_RMID:
		वापस shmctl_करोwn(ns, shmid, cmd, &sem64);
	हाल SHM_LOCK:
	हाल SHM_UNLOCK:
		वापस shmctl_करो_lock(ns, shmid, cmd);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

SYSCALL_DEFINE3(shmctl, पूर्णांक, shmid, पूर्णांक, cmd, काष्ठा shmid_ds __user *, buf)
अणु
	वापस ksys_shmctl(shmid, cmd, buf, IPC_64);
पूर्ण

#अगर_घोषित CONFIG_ARCH_WANT_IPC_PARSE_VERSION
दीर्घ ksys_old_shmctl(पूर्णांक shmid, पूर्णांक cmd, काष्ठा shmid_ds __user *buf)
अणु
	पूर्णांक version = ipc_parse_version(&cmd);

	वापस ksys_shmctl(shmid, cmd, buf, version);
पूर्ण

SYSCALL_DEFINE3(old_shmctl, पूर्णांक, shmid, पूर्णांक, cmd, काष्ठा shmid_ds __user *, buf)
अणु
	वापस ksys_old_shmctl(shmid, cmd, buf);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_COMPAT

काष्ठा compat_shmid_ds अणु
	काष्ठा compat_ipc_perm shm_perm;
	पूर्णांक shm_segsz;
	old_समय32_t shm_aसमय;
	old_समय32_t shm_dसमय;
	old_समय32_t shm_स_समय;
	compat_ipc_pid_t shm_cpid;
	compat_ipc_pid_t shm_lpid;
	अचिन्हित लघु shm_nattch;
	अचिन्हित लघु shm_unused;
	compat_uptr_t shm_unused2;
	compat_uptr_t shm_unused3;
पूर्ण;

काष्ठा compat_shminfo64 अणु
	compat_uदीर्घ_t shmmax;
	compat_uदीर्घ_t shmmin;
	compat_uदीर्घ_t shmmni;
	compat_uदीर्घ_t shmseg;
	compat_uदीर्घ_t shmall;
	compat_uदीर्घ_t __unused1;
	compat_uदीर्घ_t __unused2;
	compat_uदीर्घ_t __unused3;
	compat_uदीर्घ_t __unused4;
पूर्ण;

काष्ठा compat_shm_info अणु
	compat_पूर्णांक_t used_ids;
	compat_uदीर्घ_t shm_tot, shm_rss, shm_swp;
	compat_uदीर्घ_t swap_attempts, swap_successes;
पूर्ण;

अटल पूर्णांक copy_compat_shminfo_to_user(व्योम __user *buf, काष्ठा shminfo64 *in,
					पूर्णांक version)
अणु
	अगर (in->shmmax > पूर्णांक_उच्च)
		in->shmmax = पूर्णांक_उच्च;
	अगर (version == IPC_64) अणु
		काष्ठा compat_shminfo64 info;
		स_रखो(&info, 0, माप(info));
		info.shmmax = in->shmmax;
		info.shmmin = in->shmmin;
		info.shmmni = in->shmmni;
		info.shmseg = in->shmseg;
		info.shmall = in->shmall;
		वापस copy_to_user(buf, &info, माप(info));
	पूर्ण अन्यथा अणु
		काष्ठा shminfo info;
		स_रखो(&info, 0, माप(info));
		info.shmmax = in->shmmax;
		info.shmmin = in->shmmin;
		info.shmmni = in->shmmni;
		info.shmseg = in->shmseg;
		info.shmall = in->shmall;
		वापस copy_to_user(buf, &info, माप(info));
	पूर्ण
पूर्ण

अटल पूर्णांक put_compat_shm_info(काष्ठा shm_info *ip,
				काष्ठा compat_shm_info __user *uip)
अणु
	काष्ठा compat_shm_info info;

	स_रखो(&info, 0, माप(info));
	info.used_ids = ip->used_ids;
	info.shm_tot = ip->shm_tot;
	info.shm_rss = ip->shm_rss;
	info.shm_swp = ip->shm_swp;
	info.swap_attempts = ip->swap_attempts;
	info.swap_successes = ip->swap_successes;
	वापस copy_to_user(uip, &info, माप(info));
पूर्ण

अटल पूर्णांक copy_compat_shmid_to_user(व्योम __user *buf, काष्ठा shmid64_ds *in,
					पूर्णांक version)
अणु
	अगर (version == IPC_64) अणु
		काष्ठा compat_shmid64_ds v;
		स_रखो(&v, 0, माप(v));
		to_compat_ipc64_perm(&v.shm_perm, &in->shm_perm);
		v.shm_aसमय	 = lower_32_bits(in->shm_aसमय);
		v.shm_aसमय_high = upper_32_bits(in->shm_aसमय);
		v.shm_dसमय	 = lower_32_bits(in->shm_dसमय);
		v.shm_dसमय_high = upper_32_bits(in->shm_dसमय);
		v.shm_स_समय	 = lower_32_bits(in->shm_स_समय);
		v.shm_स_समय_high = upper_32_bits(in->shm_स_समय);
		v.shm_segsz = in->shm_segsz;
		v.shm_nattch = in->shm_nattch;
		v.shm_cpid = in->shm_cpid;
		v.shm_lpid = in->shm_lpid;
		वापस copy_to_user(buf, &v, माप(v));
	पूर्ण अन्यथा अणु
		काष्ठा compat_shmid_ds v;
		स_रखो(&v, 0, माप(v));
		to_compat_ipc_perm(&v.shm_perm, &in->shm_perm);
		v.shm_perm.key = in->shm_perm.key;
		v.shm_aसमय = in->shm_aसमय;
		v.shm_dसमय = in->shm_dसमय;
		v.shm_स_समय = in->shm_स_समय;
		v.shm_segsz = in->shm_segsz;
		v.shm_nattch = in->shm_nattch;
		v.shm_cpid = in->shm_cpid;
		v.shm_lpid = in->shm_lpid;
		वापस copy_to_user(buf, &v, माप(v));
	पूर्ण
पूर्ण

अटल पूर्णांक copy_compat_shmid_from_user(काष्ठा shmid64_ds *out, व्योम __user *buf,
					पूर्णांक version)
अणु
	स_रखो(out, 0, माप(*out));
	अगर (version == IPC_64) अणु
		काष्ठा compat_shmid64_ds __user *p = buf;
		वापस get_compat_ipc64_perm(&out->shm_perm, &p->shm_perm);
	पूर्ण अन्यथा अणु
		काष्ठा compat_shmid_ds __user *p = buf;
		वापस get_compat_ipc_perm(&out->shm_perm, &p->shm_perm);
	पूर्ण
पूर्ण

अटल दीर्घ compat_ksys_shmctl(पूर्णांक shmid, पूर्णांक cmd, व्योम __user *uptr, पूर्णांक version)
अणु
	काष्ठा ipc_namespace *ns;
	काष्ठा shmid64_ds sem64;
	पूर्णांक err;

	ns = current->nsproxy->ipc_ns;

	अगर (cmd < 0 || shmid < 0)
		वापस -EINVAL;

	चयन (cmd) अणु
	हाल IPC_INFO: अणु
		काष्ठा shminfo64 shminfo;
		err = shmctl_ipc_info(ns, &shminfo);
		अगर (err < 0)
			वापस err;
		अगर (copy_compat_shminfo_to_user(uptr, &shminfo, version))
			err = -EFAULT;
		वापस err;
	पूर्ण
	हाल SHM_INFO: अणु
		काष्ठा shm_info shm_info;
		err = shmctl_shm_info(ns, &shm_info);
		अगर (err < 0)
			वापस err;
		अगर (put_compat_shm_info(&shm_info, uptr))
			err = -EFAULT;
		वापस err;
	पूर्ण
	हाल IPC_STAT:
	हाल SHM_STAT_ANY:
	हाल SHM_STAT:
		err = shmctl_stat(ns, shmid, cmd, &sem64);
		अगर (err < 0)
			वापस err;
		अगर (copy_compat_shmid_to_user(uptr, &sem64, version))
			err = -EFAULT;
		वापस err;

	हाल IPC_SET:
		अगर (copy_compat_shmid_from_user(&sem64, uptr, version))
			वापस -EFAULT;
		fallthrough;
	हाल IPC_RMID:
		वापस shmctl_करोwn(ns, shmid, cmd, &sem64);
	हाल SHM_LOCK:
	हाल SHM_UNLOCK:
		वापस shmctl_करो_lock(ns, shmid, cmd);
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस err;
पूर्ण

COMPAT_SYSCALL_DEFINE3(shmctl, पूर्णांक, shmid, पूर्णांक, cmd, व्योम __user *, uptr)
अणु
	वापस compat_ksys_shmctl(shmid, cmd, uptr, IPC_64);
पूर्ण

#अगर_घोषित CONFIG_ARCH_WANT_COMPAT_IPC_PARSE_VERSION
दीर्घ compat_ksys_old_shmctl(पूर्णांक shmid, पूर्णांक cmd, व्योम __user *uptr)
अणु
	पूर्णांक version = compat_ipc_parse_version(&cmd);

	वापस compat_ksys_shmctl(shmid, cmd, uptr, version);
पूर्ण

COMPAT_SYSCALL_DEFINE3(old_shmctl, पूर्णांक, shmid, पूर्णांक, cmd, व्योम __user *, uptr)
अणु
	वापस compat_ksys_old_shmctl(shmid, cmd, uptr);
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

/*
 * Fix shmaddr, allocate descriptor, map shm, add attach descriptor to lists.
 *
 * NOTE! Despite the name, this is NOT a direct प्रणाली call entrypoपूर्णांक. The
 * "raddr" thing poपूर्णांकs to kernel space, and there has to be a wrapper around
 * this.
 */
दीर्घ करो_shmat(पूर्णांक shmid, अक्षर __user *shmaddr, पूर्णांक shmflg,
	      uदीर्घ *raddr, अचिन्हित दीर्घ shmlba)
अणु
	काष्ठा shmid_kernel *shp;
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)shmaddr;
	अचिन्हित दीर्घ size;
	काष्ठा file *file, *base;
	पूर्णांक    err;
	अचिन्हित दीर्घ flags = MAP_SHARED;
	अचिन्हित दीर्घ prot;
	पूर्णांक acc_mode;
	काष्ठा ipc_namespace *ns;
	काष्ठा shm_file_data *sfd;
	पूर्णांक f_flags;
	अचिन्हित दीर्घ populate = 0;

	err = -EINVAL;
	अगर (shmid < 0)
		जाओ out;

	अगर (addr) अणु
		अगर (addr & (shmlba - 1)) अणु
			अगर (shmflg & SHM_RND) अणु
				addr &= ~(shmlba - 1);  /* round करोwn */

				/*
				 * Ensure that the round-करोwn is non-nil
				 * when remapping. This can happen क्रम
				 * हालs when addr < shmlba.
				 */
				अगर (!addr && (shmflg & SHM_REMAP))
					जाओ out;
			पूर्ण अन्यथा
#अगर_अघोषित __ARCH_FORCE_SHMLBA
				अगर (addr & ~PAGE_MASK)
#पूर्ण_अगर
					जाओ out;
		पूर्ण

		flags |= MAP_FIXED;
	पूर्ण अन्यथा अगर ((shmflg & SHM_REMAP))
		जाओ out;

	अगर (shmflg & SHM_RDONLY) अणु
		prot = PROT_READ;
		acc_mode = S_IRUGO;
		f_flags = O_RDONLY;
	पूर्ण अन्यथा अणु
		prot = PROT_READ | PROT_WRITE;
		acc_mode = S_IRUGO | S_IWUGO;
		f_flags = O_RDWR;
	पूर्ण
	अगर (shmflg & SHM_EXEC) अणु
		prot |= PROT_EXEC;
		acc_mode |= S_IXUGO;
	पूर्ण

	/*
	 * We cannot rely on the fs check since SYSV IPC करोes have an
	 * additional creator id...
	 */
	ns = current->nsproxy->ipc_ns;
	rcu_पढ़ो_lock();
	shp = shm_obtain_object_check(ns, shmid);
	अगर (IS_ERR(shp)) अणु
		err = PTR_ERR(shp);
		जाओ out_unlock;
	पूर्ण

	err = -EACCES;
	अगर (ipcperms(ns, &shp->shm_perm, acc_mode))
		जाओ out_unlock;

	err = security_shm_shmat(&shp->shm_perm, shmaddr, shmflg);
	अगर (err)
		जाओ out_unlock;

	ipc_lock_object(&shp->shm_perm);

	/* check अगर shm_destroy() is tearing करोwn shp */
	अगर (!ipc_valid_object(&shp->shm_perm)) अणु
		ipc_unlock_object(&shp->shm_perm);
		err = -EIDRM;
		जाओ out_unlock;
	पूर्ण

	/*
	 * We need to take a reference to the real shm file to prevent the
	 * poपूर्णांकer from becoming stale in हालs where the lअगरeसमय of the outer
	 * file extends beyond that of the shm segment.  It's not usually
	 * possible, but it can happen during remap_file_pages() emulation as
	 * that unmaps the memory, then करोes ->mmap() via file reference only.
	 * We'll deny the ->mmap() अगर the shm segment was since हटाओd, but to
	 * detect shm ID reuse we need to compare the file poपूर्णांकers.
	 */
	base = get_file(shp->shm_file);
	shp->shm_nattch++;
	size = i_size_पढ़ो(file_inode(base));
	ipc_unlock_object(&shp->shm_perm);
	rcu_पढ़ो_unlock();

	err = -ENOMEM;
	sfd = kzalloc(माप(*sfd), GFP_KERNEL);
	अगर (!sfd) अणु
		fput(base);
		जाओ out_nattch;
	पूर्ण

	file = alloc_file_clone(base, f_flags,
			  is_file_hugepages(base) ?
				&shm_file_operations_huge :
				&shm_file_operations);
	err = PTR_ERR(file);
	अगर (IS_ERR(file)) अणु
		kमुक्त(sfd);
		fput(base);
		जाओ out_nattch;
	पूर्ण

	sfd->id = shp->shm_perm.id;
	sfd->ns = get_ipc_ns(ns);
	sfd->file = base;
	sfd->vm_ops = शून्य;
	file->निजी_data = sfd;

	err = security_mmap_file(file, prot, flags);
	अगर (err)
		जाओ out_fput;

	अगर (mmap_ग_लिखो_lock_समाप्तable(current->mm)) अणु
		err = -EINTR;
		जाओ out_fput;
	पूर्ण

	अगर (addr && !(shmflg & SHM_REMAP)) अणु
		err = -EINVAL;
		अगर (addr + size < addr)
			जाओ invalid;

		अगर (find_vma_पूर्णांकersection(current->mm, addr, addr + size))
			जाओ invalid;
	पूर्ण

	addr = करो_mmap(file, addr, size, prot, flags, 0, &populate, शून्य);
	*raddr = addr;
	err = 0;
	अगर (IS_ERR_VALUE(addr))
		err = (दीर्घ)addr;
invalid:
	mmap_ग_लिखो_unlock(current->mm);
	अगर (populate)
		mm_populate(addr, populate);

out_fput:
	fput(file);

out_nattch:
	करोwn_ग_लिखो(&shm_ids(ns).rwsem);
	shp = shm_lock(ns, shmid);
	shp->shm_nattch--;
	अगर (shm_may_destroy(ns, shp))
		shm_destroy(ns, shp);
	अन्यथा
		shm_unlock(shp);
	up_ग_लिखो(&shm_ids(ns).rwsem);
	वापस err;

out_unlock:
	rcu_पढ़ो_unlock();
out:
	वापस err;
पूर्ण

SYSCALL_DEFINE3(shmat, पूर्णांक, shmid, अक्षर __user *, shmaddr, पूर्णांक, shmflg)
अणु
	अचिन्हित दीर्घ ret;
	दीर्घ err;

	err = करो_shmat(shmid, shmaddr, shmflg, &ret, SHMLBA);
	अगर (err)
		वापस err;
	क्रमce_successful_syscall_वापस();
	वापस (दीर्घ)ret;
पूर्ण

#अगर_घोषित CONFIG_COMPAT

#अगर_अघोषित COMPAT_SHMLBA
#घोषणा COMPAT_SHMLBA	SHMLBA
#पूर्ण_अगर

COMPAT_SYSCALL_DEFINE3(shmat, पूर्णांक, shmid, compat_uptr_t, shmaddr, पूर्णांक, shmflg)
अणु
	अचिन्हित दीर्घ ret;
	दीर्घ err;

	err = करो_shmat(shmid, compat_ptr(shmaddr), shmflg, &ret, COMPAT_SHMLBA);
	अगर (err)
		वापस err;
	क्रमce_successful_syscall_वापस();
	वापस (दीर्घ)ret;
पूर्ण
#पूर्ण_अगर

/*
 * detach and समाप्त segment अगर marked destroyed.
 * The work is करोne in shm_बंद.
 */
दीर्घ ksys_shmdt(अक्षर __user *shmaddr)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)shmaddr;
	पूर्णांक retval = -EINVAL;
#अगर_घोषित CONFIG_MMU
	loff_t size = 0;
	काष्ठा file *file;
	काष्ठा vm_area_काष्ठा *next;
#पूर्ण_अगर

	अगर (addr & ~PAGE_MASK)
		वापस retval;

	अगर (mmap_ग_लिखो_lock_समाप्तable(mm))
		वापस -EINTR;

	/*
	 * This function tries to be smart and unmap shm segments that
	 * were modअगरied by partial mlock or munmap calls:
	 * - It first determines the size of the shm segment that should be
	 *   unmapped: It searches क्रम a vma that is backed by shm and that
	 *   started at address shmaddr. It records it's size and then unmaps
	 *   it.
	 * - Then it unmaps all shm vmas that started at shmaddr and that
	 *   are within the initially determined size and that are from the
	 *   same shm segment from which we determined the size.
	 * Errors from करो_munmap are ignored: the function only fails अगर
	 * it's called with invalid parameters or if it's called to unmap
	 * a part of a vma. Both calls in this function are क्रम full vmas,
	 * the parameters are directly copied from the vma itself and always
	 * valid - thereक्रमe करो_munmap cannot fail. (famous last words?)
	 */
	/*
	 * If it had been mremap()'d, the starting address would not
	 * match the usual checks anyway. So assume all vma's are
	 * above the starting address given.
	 */
	vma = find_vma(mm, addr);

#अगर_घोषित CONFIG_MMU
	जबतक (vma) अणु
		next = vma->vm_next;

		/*
		 * Check अगर the starting address would match, i.e. it's
		 * a fragment created by mprotect() and/or munmap(), or it
		 * otherwise it starts at this address with no hassles.
		 */
		अगर ((vma->vm_ops == &shm_vm_ops) &&
			(vma->vm_start - addr)/PAGE_SIZE == vma->vm_pgoff) अणु

			/*
			 * Record the file of the shm segment being
			 * unmapped.  With mremap(), someone could place
			 * page from another segment but with equal offsets
			 * in the range we are unmapping.
			 */
			file = vma->vm_file;
			size = i_size_पढ़ो(file_inode(vma->vm_file));
			करो_munmap(mm, vma->vm_start, vma->vm_end - vma->vm_start, शून्य);
			/*
			 * We discovered the size of the shm segment, so
			 * अवरोध out of here and fall through to the next
			 * loop that uses the size inक्रमmation to stop
			 * searching क्रम matching vma's.
			 */
			retval = 0;
			vma = next;
			अवरोध;
		पूर्ण
		vma = next;
	पूर्ण

	/*
	 * We need look no further than the maximum address a fragment
	 * could possibly have landed at. Also cast things to loff_t to
	 * prevent overflows and make comparisons vs. equal-width types.
	 */
	size = PAGE_ALIGN(size);
	जबतक (vma && (loff_t)(vma->vm_end - addr) <= size) अणु
		next = vma->vm_next;

		/* finding a matching vma now करोes not alter retval */
		अगर ((vma->vm_ops == &shm_vm_ops) &&
		    ((vma->vm_start - addr)/PAGE_SIZE == vma->vm_pgoff) &&
		    (vma->vm_file == file))
			करो_munmap(mm, vma->vm_start, vma->vm_end - vma->vm_start, शून्य);
		vma = next;
	पूर्ण

#अन्यथा	/* CONFIG_MMU */
	/* under NOMMU conditions, the exact address to be destroyed must be
	 * given
	 */
	अगर (vma && vma->vm_start == addr && vma->vm_ops == &shm_vm_ops) अणु
		करो_munmap(mm, vma->vm_start, vma->vm_end - vma->vm_start, शून्य);
		retval = 0;
	पूर्ण

#पूर्ण_अगर

	mmap_ग_लिखो_unlock(mm);
	वापस retval;
पूर्ण

SYSCALL_DEFINE1(shmdt, अक्षर __user *, shmaddr)
अणु
	वापस ksys_shmdt(shmaddr);
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
अटल पूर्णांक sysvipc_shm_proc_show(काष्ठा seq_file *s, व्योम *it)
अणु
	काष्ठा pid_namespace *pid_ns = ipc_seq_pid_ns(s);
	काष्ठा user_namespace *user_ns = seq_user_ns(s);
	काष्ठा kern_ipc_perm *ipcp = it;
	काष्ठा shmid_kernel *shp;
	अचिन्हित दीर्घ rss = 0, swp = 0;

	shp = container_of(ipcp, काष्ठा shmid_kernel, shm_perm);
	shm_add_rss_swap(shp, &rss, &swp);

#अगर BITS_PER_LONG <= 32
#घोषणा SIZE_SPEC "%10lu"
#अन्यथा
#घोषणा SIZE_SPEC "%21lu"
#पूर्ण_अगर

	seq_म_लिखो(s,
		   "%10d %10d  %4o " SIZE_SPEC " %5u %5u  "
		   "%5lu %5u %5u %5u %5u %10llu %10llu %10llu "
		   SIZE_SPEC " " SIZE_SPEC "\n",
		   shp->shm_perm.key,
		   shp->shm_perm.id,
		   shp->shm_perm.mode,
		   shp->shm_segsz,
		   pid_nr_ns(shp->shm_cprid, pid_ns),
		   pid_nr_ns(shp->shm_lprid, pid_ns),
		   shp->shm_nattch,
		   from_kuid_munged(user_ns, shp->shm_perm.uid),
		   from_kgid_munged(user_ns, shp->shm_perm.gid),
		   from_kuid_munged(user_ns, shp->shm_perm.cuid),
		   from_kgid_munged(user_ns, shp->shm_perm.cgid),
		   shp->shm_atim,
		   shp->shm_dtim,
		   shp->shm_ctim,
		   rss * PAGE_SIZE,
		   swp * PAGE_SIZE);

	वापस 0;
पूर्ण
#पूर्ण_अगर
