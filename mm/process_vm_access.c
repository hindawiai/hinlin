<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * linux/mm/process_vm_access.c
 *
 * Copyright (C) 2010-2011 Christopher Yeoh <cyeoh@au1.ibm.com>, IBM Corp.
 */

#समावेश <linux/compat.h>
#समावेश <linux/mm.h>
#समावेश <linux/uपन.स>
#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/slab.h>
#समावेश <linux/syscalls.h>

/**
 * process_vm_rw_pages - पढ़ो/ग_लिखो pages from task specअगरied
 * @pages: array of poपूर्णांकers to pages we want to copy
 * @offset: offset in page to start copying from/to
 * @len: number of bytes to copy
 * @iter: where to copy to/from locally
 * @vm_ग_लिखो: 0 means copy from, 1 means copy to
 * Returns 0 on success, error code otherwise
 */
अटल पूर्णांक process_vm_rw_pages(काष्ठा page **pages,
			       अचिन्हित offset,
			       माप_प्रकार len,
			       काष्ठा iov_iter *iter,
			       पूर्णांक vm_ग_लिखो)
अणु
	/* Do the copy क्रम each page */
	जबतक (len && iov_iter_count(iter)) अणु
		काष्ठा page *page = *pages++;
		माप_प्रकार copy = PAGE_SIZE - offset;
		माप_प्रकार copied;

		अगर (copy > len)
			copy = len;

		अगर (vm_ग_लिखो)
			copied = copy_page_from_iter(page, offset, copy, iter);
		अन्यथा
			copied = copy_page_to_iter(page, offset, copy, iter);

		len -= copied;
		अगर (copied < copy && iov_iter_count(iter))
			वापस -EFAULT;
		offset = 0;
	पूर्ण
	वापस 0;
पूर्ण

/* Maximum number of pages kदो_स्मृति'd to hold struct page's during copy */
#घोषणा PVM_MAX_KMALLOC_PAGES (PAGE_SIZE * 2)

/**
 * process_vm_rw_single_vec - पढ़ो/ग_लिखो pages from task specअगरied
 * @addr: start memory address of target process
 * @len: size of area to copy to/from
 * @iter: where to copy to/from locally
 * @process_pages: काष्ठा pages area that can store at least
 *  nr_pages_to_copy काष्ठा page poपूर्णांकers
 * @mm: mm क्रम task
 * @task: task to पढ़ो/ग_लिखो from
 * @vm_ग_लिखो: 0 means copy from, 1 means copy to
 * Returns 0 on success or on failure error code
 */
अटल पूर्णांक process_vm_rw_single_vec(अचिन्हित दीर्घ addr,
				    अचिन्हित दीर्घ len,
				    काष्ठा iov_iter *iter,
				    काष्ठा page **process_pages,
				    काष्ठा mm_काष्ठा *mm,
				    काष्ठा task_काष्ठा *task,
				    पूर्णांक vm_ग_लिखो)
अणु
	अचिन्हित दीर्घ pa = addr & PAGE_MASK;
	अचिन्हित दीर्घ start_offset = addr - pa;
	अचिन्हित दीर्घ nr_pages;
	sमाप_प्रकार rc = 0;
	अचिन्हित दीर्घ max_pages_per_loop = PVM_MAX_KMALLOC_PAGES
		/ माप(काष्ठा pages *);
	अचिन्हित पूर्णांक flags = 0;

	/* Work out address and page range required */
	अगर (len == 0)
		वापस 0;
	nr_pages = (addr + len - 1) / PAGE_SIZE - addr / PAGE_SIZE + 1;

	अगर (vm_ग_लिखो)
		flags |= FOLL_WRITE;

	जबतक (!rc && nr_pages && iov_iter_count(iter)) अणु
		पूर्णांक pinned_pages = min(nr_pages, max_pages_per_loop);
		पूर्णांक locked = 1;
		माप_प्रकार bytes;

		/*
		 * Get the pages we're पूर्णांकerested in.  We must
		 * access remotely because task/mm might not
		 * current/current->mm
		 */
		mmap_पढ़ो_lock(mm);
		pinned_pages = pin_user_pages_remote(mm, pa, pinned_pages,
						     flags, process_pages,
						     शून्य, &locked);
		अगर (locked)
			mmap_पढ़ो_unlock(mm);
		अगर (pinned_pages <= 0)
			वापस -EFAULT;

		bytes = pinned_pages * PAGE_SIZE - start_offset;
		अगर (bytes > len)
			bytes = len;

		rc = process_vm_rw_pages(process_pages,
					 start_offset, bytes, iter,
					 vm_ग_लिखो);
		len -= bytes;
		start_offset = 0;
		nr_pages -= pinned_pages;
		pa += pinned_pages * PAGE_SIZE;

		/* If vm_ग_लिखो is set, the pages need to be made dirty: */
		unpin_user_pages_dirty_lock(process_pages, pinned_pages,
					    vm_ग_लिखो);
	पूर्ण

	वापस rc;
पूर्ण

/* Maximum number of entries क्रम process pages array
   which lives on stack */
#घोषणा PVM_MAX_PP_ARRAY_COUNT 16

/**
 * process_vm_rw_core - core of पढ़ोing/writing pages from task specअगरied
 * @pid: PID of process to पढ़ो/ग_लिखो from/to
 * @iter: where to copy to/from locally
 * @rvec: iovec array specअगरying where to copy to/from in the other process
 * @riovcnt: size of rvec array
 * @flags: currently unused
 * @vm_ग_लिखो: 0 अगर पढ़ोing from other process, 1 अगर writing to other process
 *
 * Returns the number of bytes पढ़ो/written or error code. May
 *  वापस less bytes than expected अगर an error occurs during the copying
 *  process.
 */
अटल sमाप_प्रकार process_vm_rw_core(pid_t pid, काष्ठा iov_iter *iter,
				  स्थिर काष्ठा iovec *rvec,
				  अचिन्हित दीर्घ riovcnt,
				  अचिन्हित दीर्घ flags, पूर्णांक vm_ग_लिखो)
अणु
	काष्ठा task_काष्ठा *task;
	काष्ठा page *pp_stack[PVM_MAX_PP_ARRAY_COUNT];
	काष्ठा page **process_pages = pp_stack;
	काष्ठा mm_काष्ठा *mm;
	अचिन्हित दीर्घ i;
	sमाप_प्रकार rc = 0;
	अचिन्हित दीर्घ nr_pages = 0;
	अचिन्हित दीर्घ nr_pages_iov;
	sमाप_प्रकार iov_len;
	माप_प्रकार total_len = iov_iter_count(iter);

	/*
	 * Work out how many pages of काष्ठा pages we're going to need
	 * when eventually calling get_user_pages
	 */
	क्रम (i = 0; i < riovcnt; i++) अणु
		iov_len = rvec[i].iov_len;
		अगर (iov_len > 0) अणु
			nr_pages_iov = ((अचिन्हित दीर्घ)rvec[i].iov_base
					+ iov_len)
				/ PAGE_SIZE - (अचिन्हित दीर्घ)rvec[i].iov_base
				/ PAGE_SIZE + 1;
			nr_pages = max(nr_pages, nr_pages_iov);
		पूर्ण
	पूर्ण

	अगर (nr_pages == 0)
		वापस 0;

	अगर (nr_pages > PVM_MAX_PP_ARRAY_COUNT) अणु
		/* For reliability करोn't try to kदो_स्मृति more than
		   2 pages worth */
		process_pages = kदो_स्मृति(min_t(माप_प्रकार, PVM_MAX_KMALLOC_PAGES,
					      माप(काष्ठा pages *)*nr_pages),
					GFP_KERNEL);

		अगर (!process_pages)
			वापस -ENOMEM;
	पूर्ण

	/* Get process inक्रमmation */
	task = find_get_task_by_vpid(pid);
	अगर (!task) अणु
		rc = -ESRCH;
		जाओ मुक्त_proc_pages;
	पूर्ण

	mm = mm_access(task, PTRACE_MODE_ATTACH_REALCREDS);
	अगर (!mm || IS_ERR(mm)) अणु
		rc = IS_ERR(mm) ? PTR_ERR(mm) : -ESRCH;
		/*
		 * Explicitly map EACCES to EPERM as EPERM is a more
		 * appropriate error code क्रम process_vw_पढ़ोv/ग_लिखोv
		 */
		अगर (rc == -EACCES)
			rc = -EPERM;
		जाओ put_task_काष्ठा;
	पूर्ण

	क्रम (i = 0; i < riovcnt && iov_iter_count(iter) && !rc; i++)
		rc = process_vm_rw_single_vec(
			(अचिन्हित दीर्घ)rvec[i].iov_base, rvec[i].iov_len,
			iter, process_pages, mm, task, vm_ग_लिखो);

	/* copied = space beक्रमe - space after */
	total_len -= iov_iter_count(iter);

	/* If we have managed to copy any data at all then
	   we वापस the number of bytes copied. Otherwise
	   we वापस the error code */
	अगर (total_len)
		rc = total_len;

	mmput(mm);

put_task_काष्ठा:
	put_task_काष्ठा(task);

मुक्त_proc_pages:
	अगर (process_pages != pp_stack)
		kमुक्त(process_pages);
	वापस rc;
पूर्ण

/**
 * process_vm_rw - check iovecs beक्रमe calling core routine
 * @pid: PID of process to पढ़ो/ग_लिखो from/to
 * @lvec: iovec array specअगरying where to copy to/from locally
 * @liovcnt: size of lvec array
 * @rvec: iovec array specअगरying where to copy to/from in the other process
 * @riovcnt: size of rvec array
 * @flags: currently unused
 * @vm_ग_लिखो: 0 अगर पढ़ोing from other process, 1 अगर writing to other process
 *
 * Returns the number of bytes पढ़ो/written or error code. May
 *  वापस less bytes than expected अगर an error occurs during the copying
 *  process.
 */
अटल sमाप_प्रकार process_vm_rw(pid_t pid,
			     स्थिर काष्ठा iovec __user *lvec,
			     अचिन्हित दीर्घ liovcnt,
			     स्थिर काष्ठा iovec __user *rvec,
			     अचिन्हित दीर्घ riovcnt,
			     अचिन्हित दीर्घ flags, पूर्णांक vm_ग_लिखो)
अणु
	काष्ठा iovec iovstack_l[UIO_FASTIOV];
	काष्ठा iovec iovstack_r[UIO_FASTIOV];
	काष्ठा iovec *iov_l = iovstack_l;
	काष्ठा iovec *iov_r;
	काष्ठा iov_iter iter;
	sमाप_प्रकार rc;
	पूर्णांक dir = vm_ग_लिखो ? WRITE : READ;

	अगर (flags != 0)
		वापस -EINVAL;

	/* Check iovecs */
	rc = import_iovec(dir, lvec, liovcnt, UIO_FASTIOV, &iov_l, &iter);
	अगर (rc < 0)
		वापस rc;
	अगर (!iov_iter_count(&iter))
		जाओ मुक्त_iov_l;
	iov_r = iovec_from_user(rvec, riovcnt, UIO_FASTIOV, iovstack_r,
				in_compat_syscall());
	अगर (IS_ERR(iov_r)) अणु
		rc = PTR_ERR(iov_r);
		जाओ मुक्त_iov_l;
	पूर्ण
	rc = process_vm_rw_core(pid, &iter, iov_r, riovcnt, flags, vm_ग_लिखो);
	अगर (iov_r != iovstack_r)
		kमुक्त(iov_r);
मुक्त_iov_l:
	kमुक्त(iov_l);
	वापस rc;
पूर्ण

SYSCALL_DEFINE6(process_vm_पढ़ोv, pid_t, pid, स्थिर काष्ठा iovec __user *, lvec,
		अचिन्हित दीर्घ, liovcnt, स्थिर काष्ठा iovec __user *, rvec,
		अचिन्हित दीर्घ, riovcnt,	अचिन्हित दीर्घ, flags)
अणु
	वापस process_vm_rw(pid, lvec, liovcnt, rvec, riovcnt, flags, 0);
पूर्ण

SYSCALL_DEFINE6(process_vm_ग_लिखोv, pid_t, pid,
		स्थिर काष्ठा iovec __user *, lvec,
		अचिन्हित दीर्घ, liovcnt, स्थिर काष्ठा iovec __user *, rvec,
		अचिन्हित दीर्घ, riovcnt,	अचिन्हित दीर्घ, flags)
अणु
	वापस process_vm_rw(pid, lvec, liovcnt, rvec, riovcnt, flags, 1);
पूर्ण
