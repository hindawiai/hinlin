<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/file.c
 *
 *  Copyright (C) 1998-1999, Stephen Tweedie and Bill Hawes
 *
 *  Manage the dynamic fd arrays in the process files_काष्ठा.
 */

#समावेश <linux/syscalls.h>
#समावेश <linux/export.h>
#समावेश <linux/fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/file.h>
#समावेश <linux/fdtable.h>
#समावेश <linux/bitops.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/बंद_range.h>
#समावेश <net/sock.h>

#समावेश "internal.h"

अचिन्हित पूर्णांक sysctl_nr_खोलो __पढ़ो_mostly = 1024*1024;
अचिन्हित पूर्णांक sysctl_nr_खोलो_min = BITS_PER_LONG;
/* our min() is unusable in स्थिरant expressions ;-/ */
#घोषणा __स्थिर_min(x, y) ((x) < (y) ? (x) : (y))
अचिन्हित पूर्णांक sysctl_nr_खोलो_max =
	__स्थिर_min(पूर्णांक_उच्च, ~(माप_प्रकार)0/माप(व्योम *)) & -BITS_PER_LONG;

अटल व्योम __मुक्त_fdtable(काष्ठा fdtable *fdt)
अणु
	kvमुक्त(fdt->fd);
	kvमुक्त(fdt->खोलो_fds);
	kमुक्त(fdt);
पूर्ण

अटल व्योम मुक्त_fdtable_rcu(काष्ठा rcu_head *rcu)
अणु
	__मुक्त_fdtable(container_of(rcu, काष्ठा fdtable, rcu));
पूर्ण

#घोषणा BITBIT_NR(nr)	BITS_TO_LONGS(BITS_TO_LONGS(nr))
#घोषणा BITBIT_SIZE(nr)	(BITBIT_NR(nr) * माप(दीर्घ))

/*
 * Copy 'count' fd bits from the old table to the new table and clear the extra
 * space अगर any.  This करोes not copy the file poपूर्णांकers.  Called with the files
 * spinlock held क्रम ग_लिखो.
 */
अटल व्योम copy_fd_biपंचांगaps(काष्ठा fdtable *nfdt, काष्ठा fdtable *ofdt,
			    अचिन्हित पूर्णांक count)
अणु
	अचिन्हित पूर्णांक cpy, set;

	cpy = count / BITS_PER_BYTE;
	set = (nfdt->max_fds - count) / BITS_PER_BYTE;
	स_नकल(nfdt->खोलो_fds, ofdt->खोलो_fds, cpy);
	स_रखो((अक्षर *)nfdt->खोलो_fds + cpy, 0, set);
	स_नकल(nfdt->बंद_on_exec, ofdt->बंद_on_exec, cpy);
	स_रखो((अक्षर *)nfdt->बंद_on_exec + cpy, 0, set);

	cpy = BITBIT_SIZE(count);
	set = BITBIT_SIZE(nfdt->max_fds) - cpy;
	स_नकल(nfdt->full_fds_bits, ofdt->full_fds_bits, cpy);
	स_रखो((अक्षर *)nfdt->full_fds_bits + cpy, 0, set);
पूर्ण

/*
 * Copy all file descriptors from the old table to the new, expanded table and
 * clear the extra space.  Called with the files spinlock held क्रम ग_लिखो.
 */
अटल व्योम copy_fdtable(काष्ठा fdtable *nfdt, काष्ठा fdtable *ofdt)
अणु
	माप_प्रकार cpy, set;

	BUG_ON(nfdt->max_fds < ofdt->max_fds);

	cpy = ofdt->max_fds * माप(काष्ठा file *);
	set = (nfdt->max_fds - ofdt->max_fds) * माप(काष्ठा file *);
	स_नकल(nfdt->fd, ofdt->fd, cpy);
	स_रखो((अक्षर *)nfdt->fd + cpy, 0, set);

	copy_fd_biपंचांगaps(nfdt, ofdt, ofdt->max_fds);
पूर्ण

अटल काष्ठा fdtable * alloc_fdtable(अचिन्हित पूर्णांक nr)
अणु
	काष्ठा fdtable *fdt;
	व्योम *data;

	/*
	 * Figure out how many fds we actually want to support in this fdtable.
	 * Allocation steps are keyed to the size of the fdarray, since it
	 * grows far faster than any of the other dynamic data. We try to fit
	 * the fdarray पूर्णांकo comक्रमtable page-tuned chunks: starting at 1024B
	 * and growing in घातers of two from there on.
	 */
	nr /= (1024 / माप(काष्ठा file *));
	nr = roundup_घात_of_two(nr + 1);
	nr *= (1024 / माप(काष्ठा file *));
	/*
	 * Note that this can drive nr *below* what we had passed अगर sysctl_nr_खोलो
	 * had been set lower between the check in expand_files() and here.  Deal
	 * with that in caller, it's cheaper that way.
	 *
	 * We make sure that nr reमुख्यs a multiple of BITS_PER_LONG - otherwise
	 * biपंचांगaps handling below becomes unpleasant, to put it mildly...
	 */
	अगर (unlikely(nr > sysctl_nr_खोलो))
		nr = ((sysctl_nr_खोलो - 1) | (BITS_PER_LONG - 1)) + 1;

	fdt = kदो_स्मृति(माप(काष्ठा fdtable), GFP_KERNEL_ACCOUNT);
	अगर (!fdt)
		जाओ out;
	fdt->max_fds = nr;
	data = kvदो_स्मृति_array(nr, माप(काष्ठा file *), GFP_KERNEL_ACCOUNT);
	अगर (!data)
		जाओ out_fdt;
	fdt->fd = data;

	data = kvदो_स्मृति(max_t(माप_प्रकार,
				 2 * nr / BITS_PER_BYTE + BITBIT_SIZE(nr), L1_CACHE_BYTES),
				 GFP_KERNEL_ACCOUNT);
	अगर (!data)
		जाओ out_arr;
	fdt->खोलो_fds = data;
	data += nr / BITS_PER_BYTE;
	fdt->बंद_on_exec = data;
	data += nr / BITS_PER_BYTE;
	fdt->full_fds_bits = data;

	वापस fdt;

out_arr:
	kvमुक्त(fdt->fd);
out_fdt:
	kमुक्त(fdt);
out:
	वापस शून्य;
पूर्ण

/*
 * Expand the file descriptor table.
 * This function will allocate a new fdtable and both fd array and fdset, of
 * the given size.
 * Return <0 error code on error; 1 on successful completion.
 * The files->file_lock should be held on entry, and will be held on निकास.
 */
अटल पूर्णांक expand_fdtable(काष्ठा files_काष्ठा *files, अचिन्हित पूर्णांक nr)
	__releases(files->file_lock)
	__acquires(files->file_lock)
अणु
	काष्ठा fdtable *new_fdt, *cur_fdt;

	spin_unlock(&files->file_lock);
	new_fdt = alloc_fdtable(nr);

	/* make sure all fd_install() have seen resize_in_progress
	 * or have finished their rcu_पढ़ो_lock_sched() section.
	 */
	अगर (atomic_पढ़ो(&files->count) > 1)
		synchronize_rcu();

	spin_lock(&files->file_lock);
	अगर (!new_fdt)
		वापस -ENOMEM;
	/*
	 * extremely unlikely race - sysctl_nr_खोलो decreased between the check in
	 * caller and alloc_fdtable().  Cheaper to catch it here...
	 */
	अगर (unlikely(new_fdt->max_fds <= nr)) अणु
		__मुक्त_fdtable(new_fdt);
		वापस -EMखाता;
	पूर्ण
	cur_fdt = files_fdtable(files);
	BUG_ON(nr < cur_fdt->max_fds);
	copy_fdtable(new_fdt, cur_fdt);
	rcu_assign_poपूर्णांकer(files->fdt, new_fdt);
	अगर (cur_fdt != &files->fdtab)
		call_rcu(&cur_fdt->rcu, मुक्त_fdtable_rcu);
	/* coupled with smp_rmb() in fd_install() */
	smp_wmb();
	वापस 1;
पूर्ण

/*
 * Expand files.
 * This function will expand the file काष्ठाures, अगर the requested size exceeds
 * the current capacity and there is room क्रम expansion.
 * Return <0 error code on error; 0 when nothing करोne; 1 when files were
 * expanded and execution may have blocked.
 * The files->file_lock should be held on entry, and will be held on निकास.
 */
अटल पूर्णांक expand_files(काष्ठा files_काष्ठा *files, अचिन्हित पूर्णांक nr)
	__releases(files->file_lock)
	__acquires(files->file_lock)
अणु
	काष्ठा fdtable *fdt;
	पूर्णांक expanded = 0;

repeat:
	fdt = files_fdtable(files);

	/* Do we need to expand? */
	अगर (nr < fdt->max_fds)
		वापस expanded;

	/* Can we expand? */
	अगर (nr >= sysctl_nr_खोलो)
		वापस -EMखाता;

	अगर (unlikely(files->resize_in_progress)) अणु
		spin_unlock(&files->file_lock);
		expanded = 1;
		रुको_event(files->resize_रुको, !files->resize_in_progress);
		spin_lock(&files->file_lock);
		जाओ repeat;
	पूर्ण

	/* All good, so we try */
	files->resize_in_progress = true;
	expanded = expand_fdtable(files, nr);
	files->resize_in_progress = false;

	wake_up_all(&files->resize_रुको);
	वापस expanded;
पूर्ण

अटल अंतरभूत व्योम __set_बंद_on_exec(अचिन्हित पूर्णांक fd, काष्ठा fdtable *fdt)
अणु
	__set_bit(fd, fdt->बंद_on_exec);
पूर्ण

अटल अंतरभूत व्योम __clear_बंद_on_exec(अचिन्हित पूर्णांक fd, काष्ठा fdtable *fdt)
अणु
	अगर (test_bit(fd, fdt->बंद_on_exec))
		__clear_bit(fd, fdt->बंद_on_exec);
पूर्ण

अटल अंतरभूत व्योम __set_खोलो_fd(अचिन्हित पूर्णांक fd, काष्ठा fdtable *fdt)
अणु
	__set_bit(fd, fdt->खोलो_fds);
	fd /= BITS_PER_LONG;
	अगर (!~fdt->खोलो_fds[fd])
		__set_bit(fd, fdt->full_fds_bits);
पूर्ण

अटल अंतरभूत व्योम __clear_खोलो_fd(अचिन्हित पूर्णांक fd, काष्ठा fdtable *fdt)
अणु
	__clear_bit(fd, fdt->खोलो_fds);
	__clear_bit(fd / BITS_PER_LONG, fdt->full_fds_bits);
पूर्ण

अटल अचिन्हित पूर्णांक count_खोलो_files(काष्ठा fdtable *fdt)
अणु
	अचिन्हित पूर्णांक size = fdt->max_fds;
	अचिन्हित पूर्णांक i;

	/* Find the last खोलो fd */
	क्रम (i = size / BITS_PER_LONG; i > 0; ) अणु
		अगर (fdt->खोलो_fds[--i])
			अवरोध;
	पूर्ण
	i = (i + 1) * BITS_PER_LONG;
	वापस i;
पूर्ण

अटल अचिन्हित पूर्णांक sane_fdtable_size(काष्ठा fdtable *fdt, अचिन्हित पूर्णांक max_fds)
अणु
	अचिन्हित पूर्णांक count;

	count = count_खोलो_files(fdt);
	अगर (max_fds < NR_OPEN_DEFAULT)
		max_fds = NR_OPEN_DEFAULT;
	वापस min(count, max_fds);
पूर्ण

/*
 * Allocate a new files काष्ठाure and copy contents from the
 * passed in files काष्ठाure.
 * errorp will be valid only when the वापसed files_काष्ठा is शून्य.
 */
काष्ठा files_काष्ठा *dup_fd(काष्ठा files_काष्ठा *oldf, अचिन्हित पूर्णांक max_fds, पूर्णांक *errorp)
अणु
	काष्ठा files_काष्ठा *newf;
	काष्ठा file **old_fds, **new_fds;
	अचिन्हित पूर्णांक खोलो_files, i;
	काष्ठा fdtable *old_fdt, *new_fdt;

	*errorp = -ENOMEM;
	newf = kmem_cache_alloc(files_cachep, GFP_KERNEL);
	अगर (!newf)
		जाओ out;

	atomic_set(&newf->count, 1);

	spin_lock_init(&newf->file_lock);
	newf->resize_in_progress = false;
	init_रुकोqueue_head(&newf->resize_रुको);
	newf->next_fd = 0;
	new_fdt = &newf->fdtab;
	new_fdt->max_fds = NR_OPEN_DEFAULT;
	new_fdt->बंद_on_exec = newf->बंद_on_exec_init;
	new_fdt->खोलो_fds = newf->खोलो_fds_init;
	new_fdt->full_fds_bits = newf->full_fds_bits_init;
	new_fdt->fd = &newf->fd_array[0];

	spin_lock(&oldf->file_lock);
	old_fdt = files_fdtable(oldf);
	खोलो_files = sane_fdtable_size(old_fdt, max_fds);

	/*
	 * Check whether we need to allocate a larger fd array and fd set.
	 */
	जबतक (unlikely(खोलो_files > new_fdt->max_fds)) अणु
		spin_unlock(&oldf->file_lock);

		अगर (new_fdt != &newf->fdtab)
			__मुक्त_fdtable(new_fdt);

		new_fdt = alloc_fdtable(खोलो_files - 1);
		अगर (!new_fdt) अणु
			*errorp = -ENOMEM;
			जाओ out_release;
		पूर्ण

		/* beyond sysctl_nr_खोलो; nothing to करो */
		अगर (unlikely(new_fdt->max_fds < खोलो_files)) अणु
			__मुक्त_fdtable(new_fdt);
			*errorp = -EMखाता;
			जाओ out_release;
		पूर्ण

		/*
		 * Reacquire the oldf lock and a poपूर्णांकer to its fd table
		 * who knows it may have a new bigger fd table. We need
		 * the latest poपूर्णांकer.
		 */
		spin_lock(&oldf->file_lock);
		old_fdt = files_fdtable(oldf);
		खोलो_files = sane_fdtable_size(old_fdt, max_fds);
	पूर्ण

	copy_fd_biपंचांगaps(new_fdt, old_fdt, खोलो_files);

	old_fds = old_fdt->fd;
	new_fds = new_fdt->fd;

	क्रम (i = खोलो_files; i != 0; i--) अणु
		काष्ठा file *f = *old_fds++;
		अगर (f) अणु
			get_file(f);
		पूर्ण अन्यथा अणु
			/*
			 * The fd may be claimed in the fd biपंचांगap but not yet
			 * instantiated in the files array अगर a sibling thपढ़ो
			 * is partway through खोलो().  So make sure that this
			 * fd is available to the new process.
			 */
			__clear_खोलो_fd(खोलो_files - i, new_fdt);
		पूर्ण
		rcu_assign_poपूर्णांकer(*new_fds++, f);
	पूर्ण
	spin_unlock(&oldf->file_lock);

	/* clear the reमुख्यder */
	स_रखो(new_fds, 0, (new_fdt->max_fds - खोलो_files) * माप(काष्ठा file *));

	rcu_assign_poपूर्णांकer(newf->fdt, new_fdt);

	वापस newf;

out_release:
	kmem_cache_मुक्त(files_cachep, newf);
out:
	वापस शून्य;
पूर्ण

अटल काष्ठा fdtable *बंद_files(काष्ठा files_काष्ठा * files)
अणु
	/*
	 * It is safe to dereference the fd table without RCU or
	 * ->file_lock because this is the last reference to the
	 * files काष्ठाure.
	 */
	काष्ठा fdtable *fdt = rcu_dereference_raw(files->fdt);
	अचिन्हित पूर्णांक i, j = 0;

	क्रम (;;) अणु
		अचिन्हित दीर्घ set;
		i = j * BITS_PER_LONG;
		अगर (i >= fdt->max_fds)
			अवरोध;
		set = fdt->खोलो_fds[j++];
		जबतक (set) अणु
			अगर (set & 1) अणु
				काष्ठा file * file = xchg(&fdt->fd[i], शून्य);
				अगर (file) अणु
					filp_बंद(file, files);
					cond_resched();
				पूर्ण
			पूर्ण
			i++;
			set >>= 1;
		पूर्ण
	पूर्ण

	वापस fdt;
पूर्ण

व्योम put_files_काष्ठा(काष्ठा files_काष्ठा *files)
अणु
	अगर (atomic_dec_and_test(&files->count)) अणु
		काष्ठा fdtable *fdt = बंद_files(files);

		/* मुक्त the arrays अगर they are not embedded */
		अगर (fdt != &files->fdtab)
			__मुक्त_fdtable(fdt);
		kmem_cache_मुक्त(files_cachep, files);
	पूर्ण
पूर्ण

व्योम निकास_files(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा files_काष्ठा * files = tsk->files;

	अगर (files) अणु
		task_lock(tsk);
		tsk->files = शून्य;
		task_unlock(tsk);
		put_files_काष्ठा(files);
	पूर्ण
पूर्ण

काष्ठा files_काष्ठा init_files = अणु
	.count		= ATOMIC_INIT(1),
	.fdt		= &init_files.fdtab,
	.fdtab		= अणु
		.max_fds	= NR_OPEN_DEFAULT,
		.fd		= &init_files.fd_array[0],
		.बंद_on_exec	= init_files.बंद_on_exec_init,
		.खोलो_fds	= init_files.खोलो_fds_init,
		.full_fds_bits	= init_files.full_fds_bits_init,
	पूर्ण,
	.file_lock	= __SPIN_LOCK_UNLOCKED(init_files.file_lock),
	.resize_रुको	= __WAIT_QUEUE_HEAD_INITIALIZER(init_files.resize_रुको),
पूर्ण;

अटल अचिन्हित पूर्णांक find_next_fd(काष्ठा fdtable *fdt, अचिन्हित पूर्णांक start)
अणु
	अचिन्हित पूर्णांक maxfd = fdt->max_fds;
	अचिन्हित पूर्णांक maxbit = maxfd / BITS_PER_LONG;
	अचिन्हित पूर्णांक bitbit = start / BITS_PER_LONG;

	bitbit = find_next_zero_bit(fdt->full_fds_bits, maxbit, bitbit) * BITS_PER_LONG;
	अगर (bitbit > maxfd)
		वापस maxfd;
	अगर (bitbit > start)
		start = bitbit;
	वापस find_next_zero_bit(fdt->खोलो_fds, maxfd, start);
पूर्ण

/*
 * allocate a file descriptor, mark it busy.
 */
अटल पूर्णांक alloc_fd(अचिन्हित start, अचिन्हित end, अचिन्हित flags)
अणु
	काष्ठा files_काष्ठा *files = current->files;
	अचिन्हित पूर्णांक fd;
	पूर्णांक error;
	काष्ठा fdtable *fdt;

	spin_lock(&files->file_lock);
repeat:
	fdt = files_fdtable(files);
	fd = start;
	अगर (fd < files->next_fd)
		fd = files->next_fd;

	अगर (fd < fdt->max_fds)
		fd = find_next_fd(fdt, fd);

	/*
	 * N.B. For clone tasks sharing a files काष्ठाure, this test
	 * will limit the total number of files that can be खोलोed.
	 */
	error = -EMखाता;
	अगर (fd >= end)
		जाओ out;

	error = expand_files(files, fd);
	अगर (error < 0)
		जाओ out;

	/*
	 * If we needed to expand the fs array we
	 * might have blocked - try again.
	 */
	अगर (error)
		जाओ repeat;

	अगर (start <= files->next_fd)
		files->next_fd = fd + 1;

	__set_खोलो_fd(fd, fdt);
	अगर (flags & O_CLOEXEC)
		__set_बंद_on_exec(fd, fdt);
	अन्यथा
		__clear_बंद_on_exec(fd, fdt);
	error = fd;
#अगर 1
	/* Sanity check */
	अगर (rcu_access_poपूर्णांकer(fdt->fd[fd]) != शून्य) अणु
		prपूर्णांकk(KERN_WARNING "alloc_fd: slot %d not NULL!\n", fd);
		rcu_assign_poपूर्णांकer(fdt->fd[fd], शून्य);
	पूर्ण
#पूर्ण_अगर

out:
	spin_unlock(&files->file_lock);
	वापस error;
पूर्ण

पूर्णांक __get_unused_fd_flags(अचिन्हित flags, अचिन्हित दीर्घ nofile)
अणु
	वापस alloc_fd(0, nofile, flags);
पूर्ण

पूर्णांक get_unused_fd_flags(अचिन्हित flags)
अणु
	वापस __get_unused_fd_flags(flags, rlimit(RLIMIT_NOखाता));
पूर्ण
EXPORT_SYMBOL(get_unused_fd_flags);

अटल व्योम __put_unused_fd(काष्ठा files_काष्ठा *files, अचिन्हित पूर्णांक fd)
अणु
	काष्ठा fdtable *fdt = files_fdtable(files);
	__clear_खोलो_fd(fd, fdt);
	अगर (fd < files->next_fd)
		files->next_fd = fd;
पूर्ण

व्योम put_unused_fd(अचिन्हित पूर्णांक fd)
अणु
	काष्ठा files_काष्ठा *files = current->files;
	spin_lock(&files->file_lock);
	__put_unused_fd(files, fd);
	spin_unlock(&files->file_lock);
पूर्ण

EXPORT_SYMBOL(put_unused_fd);

/*
 * Install a file poपूर्णांकer in the fd array.
 *
 * The VFS is full of places where we drop the files lock between
 * setting the खोलो_fds biपंचांगap and installing the file in the file
 * array.  At any such poपूर्णांक, we are vulnerable to a dup2() race
 * installing a file in the array beक्रमe us.  We need to detect this and
 * fput() the काष्ठा file we are about to overग_लिखो in this हाल.
 *
 * It should never happen - अगर we allow dup2() करो it, _really_ bad things
 * will follow.
 *
 * This consumes the "file" refcount, so callers should treat it
 * as अगर they had called fput(file).
 */

व्योम fd_install(अचिन्हित पूर्णांक fd, काष्ठा file *file)
अणु
	काष्ठा files_काष्ठा *files = current->files;
	काष्ठा fdtable *fdt;

	rcu_पढ़ो_lock_sched();

	अगर (unlikely(files->resize_in_progress)) अणु
		rcu_पढ़ो_unlock_sched();
		spin_lock(&files->file_lock);
		fdt = files_fdtable(files);
		BUG_ON(fdt->fd[fd] != शून्य);
		rcu_assign_poपूर्णांकer(fdt->fd[fd], file);
		spin_unlock(&files->file_lock);
		वापस;
	पूर्ण
	/* coupled with smp_wmb() in expand_fdtable() */
	smp_rmb();
	fdt = rcu_dereference_sched(files->fdt);
	BUG_ON(fdt->fd[fd] != शून्य);
	rcu_assign_poपूर्णांकer(fdt->fd[fd], file);
	rcu_पढ़ो_unlock_sched();
पूर्ण

EXPORT_SYMBOL(fd_install);

अटल काष्ठा file *pick_file(काष्ठा files_काष्ठा *files, अचिन्हित fd)
अणु
	काष्ठा file *file = शून्य;
	काष्ठा fdtable *fdt;

	spin_lock(&files->file_lock);
	fdt = files_fdtable(files);
	अगर (fd >= fdt->max_fds)
		जाओ out_unlock;
	file = fdt->fd[fd];
	अगर (!file)
		जाओ out_unlock;
	rcu_assign_poपूर्णांकer(fdt->fd[fd], शून्य);
	__put_unused_fd(files, fd);

out_unlock:
	spin_unlock(&files->file_lock);
	वापस file;
पूर्ण

पूर्णांक बंद_fd(अचिन्हित fd)
अणु
	काष्ठा files_काष्ठा *files = current->files;
	काष्ठा file *file;

	file = pick_file(files, fd);
	अगर (!file)
		वापस -EBADF;

	वापस filp_बंद(file, files);
पूर्ण
EXPORT_SYMBOL(बंद_fd); /* क्रम ksys_बंद() */

/**
 * last_fd - वापस last valid index पूर्णांकo fd table
 * @cur_fds: files काष्ठा
 *
 * Context: Either rcu पढ़ो lock or files_lock must be held.
 *
 * Returns: Last valid index पूर्णांकo fdtable.
 */
अटल अंतरभूत अचिन्हित last_fd(काष्ठा fdtable *fdt)
अणु
	वापस fdt->max_fds - 1;
पूर्ण

अटल अंतरभूत व्योम __range_cloexec(काष्ठा files_काष्ठा *cur_fds,
				   अचिन्हित पूर्णांक fd, अचिन्हित पूर्णांक max_fd)
अणु
	काष्ठा fdtable *fdt;

	/* make sure we're using the correct maximum value */
	spin_lock(&cur_fds->file_lock);
	fdt = files_fdtable(cur_fds);
	max_fd = min(last_fd(fdt), max_fd);
	अगर (fd <= max_fd)
		biपंचांगap_set(fdt->बंद_on_exec, fd, max_fd - fd + 1);
	spin_unlock(&cur_fds->file_lock);
पूर्ण

अटल अंतरभूत व्योम __range_बंद(काष्ठा files_काष्ठा *cur_fds, अचिन्हित पूर्णांक fd,
				 अचिन्हित पूर्णांक max_fd)
अणु
	जबतक (fd <= max_fd) अणु
		काष्ठा file *file;

		file = pick_file(cur_fds, fd++);
		अगर (!file)
			जारी;

		filp_बंद(file, cur_fds);
		cond_resched();
	पूर्ण
पूर्ण

/**
 * __बंद_range() - Close all file descriptors in a given range.
 *
 * @fd:     starting file descriptor to बंद
 * @max_fd: last file descriptor to बंद
 *
 * This बंदs a range of file descriptors. All file descriptors
 * from @fd up to and including @max_fd are बंदd.
 */
पूर्णांक __बंद_range(अचिन्हित fd, अचिन्हित max_fd, अचिन्हित पूर्णांक flags)
अणु
	अचिन्हित पूर्णांक cur_max;
	काष्ठा task_काष्ठा *me = current;
	काष्ठा files_काष्ठा *cur_fds = me->files, *fds = शून्य;

	अगर (flags & ~(CLOSE_RANGE_UNSHARE | CLOSE_RANGE_CLOEXEC))
		वापस -EINVAL;

	अगर (fd > max_fd)
		वापस -EINVAL;

	rcu_पढ़ो_lock();
	cur_max = files_fdtable(cur_fds)->max_fds;
	rcu_पढ़ो_unlock();

	/* cap to last valid index पूर्णांकo fdtable */
	cur_max--;

	अगर (flags & CLOSE_RANGE_UNSHARE) अणु
		पूर्णांक ret;
		अचिन्हित पूर्णांक max_unshare_fds = NR_OPEN_MAX;

		/*
		 * If the requested range is greater than the current maximum,
		 * we're closing everything so only copy all file descriptors
		 * beneath the lowest file descriptor.
		 * If the caller requested all fds to be made cloexec copy all
		 * of the file descriptors since they still want to use them.
		 */
		अगर (!(flags & CLOSE_RANGE_CLOEXEC) && (max_fd >= cur_max))
			max_unshare_fds = fd;

		ret = unshare_fd(CLONE_खाताS, max_unshare_fds, &fds);
		अगर (ret)
			वापस ret;

		/*
		 * We used to share our file descriptor table, and have now
		 * created a निजी one, make sure we're using it below.
		 */
		अगर (fds)
			swap(cur_fds, fds);
	पूर्ण

	max_fd = min(max_fd, cur_max);

	अगर (flags & CLOSE_RANGE_CLOEXEC)
		__range_cloexec(cur_fds, fd, max_fd);
	अन्यथा
		__range_बंद(cur_fds, fd, max_fd);

	अगर (fds) अणु
		/*
		 * We're करोne closing the files we were supposed to. Time to install
		 * the new file descriptor table and drop the old one.
		 */
		task_lock(me);
		me->files = cur_fds;
		task_unlock(me);
		put_files_काष्ठा(fds);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * See बंद_fd_get_file() below, this variant assumes current->files->file_lock
 * is held.
 */
पूर्णांक __बंद_fd_get_file(अचिन्हित पूर्णांक fd, काष्ठा file **res)
अणु
	काष्ठा files_काष्ठा *files = current->files;
	काष्ठा file *file;
	काष्ठा fdtable *fdt;

	fdt = files_fdtable(files);
	अगर (fd >= fdt->max_fds)
		जाओ out_err;
	file = fdt->fd[fd];
	अगर (!file)
		जाओ out_err;
	rcu_assign_poपूर्णांकer(fdt->fd[fd], शून्य);
	__put_unused_fd(files, fd);
	get_file(file);
	*res = file;
	वापस 0;
out_err:
	*res = शून्य;
	वापस -ENOENT;
पूर्ण

/*
 * variant of बंद_fd that माला_लो a ref on the file क्रम later fput.
 * The caller must ensure that filp_बंद() called on the file, and then
 * an fput().
 */
पूर्णांक बंद_fd_get_file(अचिन्हित पूर्णांक fd, काष्ठा file **res)
अणु
	काष्ठा files_काष्ठा *files = current->files;
	पूर्णांक ret;

	spin_lock(&files->file_lock);
	ret = __बंद_fd_get_file(fd, res);
	spin_unlock(&files->file_lock);

	वापस ret;
पूर्ण

व्योम करो_बंद_on_exec(काष्ठा files_काष्ठा *files)
अणु
	अचिन्हित i;
	काष्ठा fdtable *fdt;

	/* exec unshares first */
	spin_lock(&files->file_lock);
	क्रम (i = 0; ; i++) अणु
		अचिन्हित दीर्घ set;
		अचिन्हित fd = i * BITS_PER_LONG;
		fdt = files_fdtable(files);
		अगर (fd >= fdt->max_fds)
			अवरोध;
		set = fdt->बंद_on_exec[i];
		अगर (!set)
			जारी;
		fdt->बंद_on_exec[i] = 0;
		क्रम ( ; set ; fd++, set >>= 1) अणु
			काष्ठा file *file;
			अगर (!(set & 1))
				जारी;
			file = fdt->fd[fd];
			अगर (!file)
				जारी;
			rcu_assign_poपूर्णांकer(fdt->fd[fd], शून्य);
			__put_unused_fd(files, fd);
			spin_unlock(&files->file_lock);
			filp_बंद(file, files);
			cond_resched();
			spin_lock(&files->file_lock);
		पूर्ण

	पूर्ण
	spin_unlock(&files->file_lock);
पूर्ण

अटल काष्ठा file *__fget_files(काष्ठा files_काष्ठा *files, अचिन्हित पूर्णांक fd,
				 भ_शेषe_t mask, अचिन्हित पूर्णांक refs)
अणु
	काष्ठा file *file;

	rcu_पढ़ो_lock();
loop:
	file = files_lookup_fd_rcu(files, fd);
	अगर (file) अणु
		/* File object ref couldn't be taken.
		 * dup2() atomicity guarantee is the reason
		 * we loop to catch the new file (or शून्य poपूर्णांकer)
		 */
		अगर (file->f_mode & mask)
			file = शून्य;
		अन्यथा अगर (!get_file_rcu_many(file, refs))
			जाओ loop;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस file;
पूर्ण

अटल अंतरभूत काष्ठा file *__fget(अचिन्हित पूर्णांक fd, भ_शेषe_t mask,
				  अचिन्हित पूर्णांक refs)
अणु
	वापस __fget_files(current->files, fd, mask, refs);
पूर्ण

काष्ठा file *fget_many(अचिन्हित पूर्णांक fd, अचिन्हित पूर्णांक refs)
अणु
	वापस __fget(fd, FMODE_PATH, refs);
पूर्ण

काष्ठा file *fget(अचिन्हित पूर्णांक fd)
अणु
	वापस __fget(fd, FMODE_PATH, 1);
पूर्ण
EXPORT_SYMBOL(fget);

काष्ठा file *fget_raw(अचिन्हित पूर्णांक fd)
अणु
	वापस __fget(fd, 0, 1);
पूर्ण
EXPORT_SYMBOL(fget_raw);

काष्ठा file *fget_task(काष्ठा task_काष्ठा *task, अचिन्हित पूर्णांक fd)
अणु
	काष्ठा file *file = शून्य;

	task_lock(task);
	अगर (task->files)
		file = __fget_files(task->files, fd, 0, 1);
	task_unlock(task);

	वापस file;
पूर्ण

काष्ठा file *task_lookup_fd_rcu(काष्ठा task_काष्ठा *task, अचिन्हित पूर्णांक fd)
अणु
	/* Must be called with rcu_पढ़ो_lock held */
	काष्ठा files_काष्ठा *files;
	काष्ठा file *file = शून्य;

	task_lock(task);
	files = task->files;
	अगर (files)
		file = files_lookup_fd_rcu(files, fd);
	task_unlock(task);

	वापस file;
पूर्ण

काष्ठा file *task_lookup_next_fd_rcu(काष्ठा task_काष्ठा *task, अचिन्हित पूर्णांक *ret_fd)
अणु
	/* Must be called with rcu_पढ़ो_lock held */
	काष्ठा files_काष्ठा *files;
	अचिन्हित पूर्णांक fd = *ret_fd;
	काष्ठा file *file = शून्य;

	task_lock(task);
	files = task->files;
	अगर (files) अणु
		क्रम (; fd < files_fdtable(files)->max_fds; fd++) अणु
			file = files_lookup_fd_rcu(files, fd);
			अगर (file)
				अवरोध;
		पूर्ण
	पूर्ण
	task_unlock(task);
	*ret_fd = fd;
	वापस file;
पूर्ण

/*
 * Lightweight file lookup - no refcnt increment अगर fd table isn't shared.
 *
 * You can use this instead of fget अगर you satisfy all of the following
 * conditions:
 * 1) You must call fput_light beक्रमe निकासing the syscall and वापसing control
 *    to userspace (i.e. you cannot remember the वापसed काष्ठा file * after
 *    वापसing to userspace).
 * 2) You must not call filp_बंद on the वापसed काष्ठा file * in between
 *    calls to fget_light and fput_light.
 * 3) You must not clone the current task in between the calls to fget_light
 *    and fput_light.
 *
 * The fput_needed flag वापसed by fget_light should be passed to the
 * corresponding fput_light.
 */
अटल अचिन्हित दीर्घ __fget_light(अचिन्हित पूर्णांक fd, भ_शेषe_t mask)
अणु
	काष्ठा files_काष्ठा *files = current->files;
	काष्ठा file *file;

	अगर (atomic_पढ़ो(&files->count) == 1) अणु
		file = files_lookup_fd_raw(files, fd);
		अगर (!file || unlikely(file->f_mode & mask))
			वापस 0;
		वापस (अचिन्हित दीर्घ)file;
	पूर्ण अन्यथा अणु
		file = __fget(fd, mask, 1);
		अगर (!file)
			वापस 0;
		वापस FDPUT_FPUT | (अचिन्हित दीर्घ)file;
	पूर्ण
पूर्ण
अचिन्हित दीर्घ __fdget(अचिन्हित पूर्णांक fd)
अणु
	वापस __fget_light(fd, FMODE_PATH);
पूर्ण
EXPORT_SYMBOL(__fdget);

अचिन्हित दीर्घ __fdget_raw(अचिन्हित पूर्णांक fd)
अणु
	वापस __fget_light(fd, 0);
पूर्ण

अचिन्हित दीर्घ __fdget_pos(अचिन्हित पूर्णांक fd)
अणु
	अचिन्हित दीर्घ v = __fdget(fd);
	काष्ठा file *file = (काष्ठा file *)(v & ~3);

	अगर (file && (file->f_mode & FMODE_ATOMIC_POS)) अणु
		अगर (file_count(file) > 1) अणु
			v |= FDPUT_POS_UNLOCK;
			mutex_lock(&file->f_pos_lock);
		पूर्ण
	पूर्ण
	वापस v;
पूर्ण

व्योम __f_unlock_pos(काष्ठा file *f)
अणु
	mutex_unlock(&f->f_pos_lock);
पूर्ण

/*
 * We only lock f_pos अगर we have thपढ़ोs or अगर the file might be
 * shared with another process. In both हालs we'll have an elevated
 * file count (करोne either by fdget() or by विभाजन()).
 */

व्योम set_बंद_on_exec(अचिन्हित पूर्णांक fd, पूर्णांक flag)
अणु
	काष्ठा files_काष्ठा *files = current->files;
	काष्ठा fdtable *fdt;
	spin_lock(&files->file_lock);
	fdt = files_fdtable(files);
	अगर (flag)
		__set_बंद_on_exec(fd, fdt);
	अन्यथा
		__clear_बंद_on_exec(fd, fdt);
	spin_unlock(&files->file_lock);
पूर्ण

bool get_बंद_on_exec(अचिन्हित पूर्णांक fd)
अणु
	काष्ठा files_काष्ठा *files = current->files;
	काष्ठा fdtable *fdt;
	bool res;
	rcu_पढ़ो_lock();
	fdt = files_fdtable(files);
	res = बंद_on_exec(fd, fdt);
	rcu_पढ़ो_unlock();
	वापस res;
पूर्ण

अटल पूर्णांक करो_dup2(काष्ठा files_काष्ठा *files,
	काष्ठा file *file, अचिन्हित fd, अचिन्हित flags)
__releases(&files->file_lock)
अणु
	काष्ठा file *toमुक्त;
	काष्ठा fdtable *fdt;

	/*
	 * We need to detect attempts to करो dup2() over allocated but still
	 * not finished descriptor.  NB: OpenBSD aव्योमs that at the price of
	 * extra work in their equivalent of fget() - they insert काष्ठा
	 * file immediately after grabbing descriptor, mark it larval अगर
	 * more work (e.g. actual खोलोing) is needed and make sure that
	 * fget() treats larval files as असलent.  Potentially पूर्णांकeresting,
	 * but जबतक extra work in fget() is trivial, locking implications
	 * and amount of surgery on खोलो()-related paths in VFS are not.
	 * FreeBSD fails with -EBADF in the same situation, NetBSD "solution"
	 * deadlocks in rather amusing ways, AFAICS.  All of that is out of
	 * scope of POSIX or SUS, since neither considers shared descriptor
	 * tables and this condition करोes not arise without those.
	 */
	fdt = files_fdtable(files);
	toमुक्त = fdt->fd[fd];
	अगर (!toमुक्त && fd_is_खोलो(fd, fdt))
		जाओ Ebusy;
	get_file(file);
	rcu_assign_poपूर्णांकer(fdt->fd[fd], file);
	__set_खोलो_fd(fd, fdt);
	अगर (flags & O_CLOEXEC)
		__set_बंद_on_exec(fd, fdt);
	अन्यथा
		__clear_बंद_on_exec(fd, fdt);
	spin_unlock(&files->file_lock);

	अगर (toमुक्त)
		filp_बंद(toमुक्त, files);

	वापस fd;

Ebusy:
	spin_unlock(&files->file_lock);
	वापस -EBUSY;
पूर्ण

पूर्णांक replace_fd(अचिन्हित fd, काष्ठा file *file, अचिन्हित flags)
अणु
	पूर्णांक err;
	काष्ठा files_काष्ठा *files = current->files;

	अगर (!file)
		वापस बंद_fd(fd);

	अगर (fd >= rlimit(RLIMIT_NOखाता))
		वापस -EBADF;

	spin_lock(&files->file_lock);
	err = expand_files(files, fd);
	अगर (unlikely(err < 0))
		जाओ out_unlock;
	वापस करो_dup2(files, file, fd, flags);

out_unlock:
	spin_unlock(&files->file_lock);
	वापस err;
पूर्ण

/**
 * __receive_fd() - Install received file पूर्णांकo file descriptor table
 * @file: काष्ठा file that was received from another process
 * @ufd: __user poपूर्णांकer to ग_लिखो new fd number to
 * @o_flags: the O_* flags to apply to the new fd entry
 *
 * Installs a received file पूर्णांकo the file descriptor table, with appropriate
 * checks and count updates. Optionally ग_लिखोs the fd number to userspace, अगर
 * @ufd is non-शून्य.
 *
 * This helper handles its own reference counting of the incoming
 * काष्ठा file.
 *
 * Returns newly install fd or -ve on error.
 */
पूर्णांक __receive_fd(काष्ठा file *file, पूर्णांक __user *ufd, अचिन्हित पूर्णांक o_flags)
अणु
	पूर्णांक new_fd;
	पूर्णांक error;

	error = security_file_receive(file);
	अगर (error)
		वापस error;

	new_fd = get_unused_fd_flags(o_flags);
	अगर (new_fd < 0)
		वापस new_fd;

	अगर (ufd) अणु
		error = put_user(new_fd, ufd);
		अगर (error) अणु
			put_unused_fd(new_fd);
			वापस error;
		पूर्ण
	पूर्ण

	fd_install(new_fd, get_file(file));
	__receive_sock(file);
	वापस new_fd;
पूर्ण

पूर्णांक receive_fd_replace(पूर्णांक new_fd, काष्ठा file *file, अचिन्हित पूर्णांक o_flags)
अणु
	पूर्णांक error;

	error = security_file_receive(file);
	अगर (error)
		वापस error;
	error = replace_fd(new_fd, file, o_flags);
	अगर (error)
		वापस error;
	__receive_sock(file);
	वापस new_fd;
पूर्ण

अटल पूर्णांक ksys_dup3(अचिन्हित पूर्णांक oldfd, अचिन्हित पूर्णांक newfd, पूर्णांक flags)
अणु
	पूर्णांक err = -EBADF;
	काष्ठा file *file;
	काष्ठा files_काष्ठा *files = current->files;

	अगर ((flags & ~O_CLOEXEC) != 0)
		वापस -EINVAL;

	अगर (unlikely(oldfd == newfd))
		वापस -EINVAL;

	अगर (newfd >= rlimit(RLIMIT_NOखाता))
		वापस -EBADF;

	spin_lock(&files->file_lock);
	err = expand_files(files, newfd);
	file = files_lookup_fd_locked(files, oldfd);
	अगर (unlikely(!file))
		जाओ Ebadf;
	अगर (unlikely(err < 0)) अणु
		अगर (err == -EMखाता)
			जाओ Ebadf;
		जाओ out_unlock;
	पूर्ण
	वापस करो_dup2(files, file, newfd, flags);

Ebadf:
	err = -EBADF;
out_unlock:
	spin_unlock(&files->file_lock);
	वापस err;
पूर्ण

SYSCALL_DEFINE3(dup3, अचिन्हित पूर्णांक, oldfd, अचिन्हित पूर्णांक, newfd, पूर्णांक, flags)
अणु
	वापस ksys_dup3(oldfd, newfd, flags);
पूर्ण

SYSCALL_DEFINE2(dup2, अचिन्हित पूर्णांक, oldfd, अचिन्हित पूर्णांक, newfd)
अणु
	अगर (unlikely(newfd == oldfd)) अणु /* corner हाल */
		काष्ठा files_काष्ठा *files = current->files;
		पूर्णांक retval = oldfd;

		rcu_पढ़ो_lock();
		अगर (!files_lookup_fd_rcu(files, oldfd))
			retval = -EBADF;
		rcu_पढ़ो_unlock();
		वापस retval;
	पूर्ण
	वापस ksys_dup3(oldfd, newfd, 0);
पूर्ण

SYSCALL_DEFINE1(dup, अचिन्हित पूर्णांक, fildes)
अणु
	पूर्णांक ret = -EBADF;
	काष्ठा file *file = fget_raw(fildes);

	अगर (file) अणु
		ret = get_unused_fd_flags(0);
		अगर (ret >= 0)
			fd_install(ret, file);
		अन्यथा
			fput(file);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक f_dupfd(अचिन्हित पूर्णांक from, काष्ठा file *file, अचिन्हित flags)
अणु
	अचिन्हित दीर्घ nofile = rlimit(RLIMIT_NOखाता);
	पूर्णांक err;
	अगर (from >= nofile)
		वापस -EINVAL;
	err = alloc_fd(from, nofile, flags);
	अगर (err >= 0) अणु
		get_file(file);
		fd_install(err, file);
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक iterate_fd(काष्ठा files_काष्ठा *files, अचिन्हित n,
		पूर्णांक (*f)(स्थिर व्योम *, काष्ठा file *, अचिन्हित),
		स्थिर व्योम *p)
अणु
	काष्ठा fdtable *fdt;
	पूर्णांक res = 0;
	अगर (!files)
		वापस 0;
	spin_lock(&files->file_lock);
	क्रम (fdt = files_fdtable(files); n < fdt->max_fds; n++) अणु
		काष्ठा file *file;
		file = rcu_dereference_check_fdtable(files, fdt->fd[n]);
		अगर (!file)
			जारी;
		res = f(p, file, n);
		अगर (res)
			अवरोध;
	पूर्ण
	spin_unlock(&files->file_lock);
	वापस res;
पूर्ण
EXPORT_SYMBOL(iterate_fd);
