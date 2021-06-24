<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/mm/msync.c
 *
 * Copyright (C) 1994-1999  Linus Torvalds
 */

/*
 * The msync() प्रणाली call.
 */
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/mman.h>
#समावेश <linux/file.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/sched.h>

/*
 * MS_SYNC syncs the entire file - including mappings.
 *
 * MS_ASYNC करोes not start I/O (it used to, up to 2.5.67).
 * Nor करोes it marks the relevant pages dirty (it used to up to 2.6.17).
 * Now it करोesn't करो anything, since dirty pages are properly tracked.
 *
 * The application may now run fsync() to
 * ग_लिखो out the dirty pages and रुको on the ग_लिखोout and check the result.
 * Or the application may run fadvise(FADV_DONTNEED) against the fd to start
 * async ग_लिखोout immediately.
 * So by _not_ starting I/O in MS_ASYNC we provide complete flexibility to
 * applications.
 */
SYSCALL_DEFINE3(msync, अचिन्हित दीर्घ, start, माप_प्रकार, len, पूर्णांक, flags)
अणु
	अचिन्हित दीर्घ end;
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma;
	पूर्णांक unmapped_error = 0;
	पूर्णांक error = -EINVAL;

	start = untagged_addr(start);

	अगर (flags & ~(MS_ASYNC | MS_INVALIDATE | MS_SYNC))
		जाओ out;
	अगर (offset_in_page(start))
		जाओ out;
	अगर ((flags & MS_ASYNC) && (flags & MS_SYNC))
		जाओ out;
	error = -ENOMEM;
	len = (len + ~PAGE_MASK) & PAGE_MASK;
	end = start + len;
	अगर (end < start)
		जाओ out;
	error = 0;
	अगर (end == start)
		जाओ out;
	/*
	 * If the पूर्णांकerval [start,end) covers some unmapped address ranges,
	 * just ignore them, but वापस -ENOMEM at the end. Besides, अगर the
	 * flag is MS_ASYNC (w/o MS_INVALIDATE) the result would be -ENOMEM
	 * anyway and there is nothing left to करो, so वापस immediately.
	 */
	mmap_पढ़ो_lock(mm);
	vma = find_vma(mm, start);
	क्रम (;;) अणु
		काष्ठा file *file;
		loff_t fstart, fend;

		/* Still start < end. */
		error = -ENOMEM;
		अगर (!vma)
			जाओ out_unlock;
		/* Here start < vma->vm_end. */
		अगर (start < vma->vm_start) अणु
			अगर (flags == MS_ASYNC)
				जाओ out_unlock;
			start = vma->vm_start;
			अगर (start >= end)
				जाओ out_unlock;
			unmapped_error = -ENOMEM;
		पूर्ण
		/* Here vma->vm_start <= start < vma->vm_end. */
		अगर ((flags & MS_INVALIDATE) &&
				(vma->vm_flags & VM_LOCKED)) अणु
			error = -EBUSY;
			जाओ out_unlock;
		पूर्ण
		file = vma->vm_file;
		fstart = (start - vma->vm_start) +
			 ((loff_t)vma->vm_pgoff << PAGE_SHIFT);
		fend = fstart + (min(end, vma->vm_end) - start) - 1;
		start = vma->vm_end;
		अगर ((flags & MS_SYNC) && file &&
				(vma->vm_flags & VM_SHARED)) अणु
			get_file(file);
			mmap_पढ़ो_unlock(mm);
			error = vfs_fsync_range(file, fstart, fend, 1);
			fput(file);
			अगर (error || start >= end)
				जाओ out;
			mmap_पढ़ो_lock(mm);
			vma = find_vma(mm, start);
		पूर्ण अन्यथा अणु
			अगर (start >= end) अणु
				error = 0;
				जाओ out_unlock;
			पूर्ण
			vma = vma->vm_next;
		पूर्ण
	पूर्ण
out_unlock:
	mmap_पढ़ो_unlock(mm);
out:
	वापस error ? : unmapped_error;
पूर्ण
