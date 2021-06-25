<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/mm.h>
#समावेश <linux/file.h>
#समावेश <linux/fdtable.h>
#समावेश <linux/fs_काष्ठा.h>
#समावेश <linux/mount.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/slab.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/sched/mm.h>

#समावेश "internal.h"

/*
 * Logic: we've got two memory sums क्रम each process, "shared", and
 * "non-shared". Shared memory may get counted more than once, क्रम
 * each process that owns it. Non-shared memory is counted
 * accurately.
 */
व्योम task_mem(काष्ठा seq_file *m, काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा vm_region *region;
	काष्ठा rb_node *p;
	अचिन्हित दीर्घ bytes = 0, sbytes = 0, slack = 0, size;
        
	mmap_पढ़ो_lock(mm);
	क्रम (p = rb_first(&mm->mm_rb); p; p = rb_next(p)) अणु
		vma = rb_entry(p, काष्ठा vm_area_काष्ठा, vm_rb);

		bytes += kobjsize(vma);

		region = vma->vm_region;
		अगर (region) अणु
			size = kobjsize(region);
			size += region->vm_end - region->vm_start;
		पूर्ण अन्यथा अणु
			size = vma->vm_end - vma->vm_start;
		पूर्ण

		अगर (atomic_पढ़ो(&mm->mm_count) > 1 ||
		    vma->vm_flags & VM_MAYSHARE) अणु
			sbytes += size;
		पूर्ण अन्यथा अणु
			bytes += size;
			अगर (region)
				slack = region->vm_end - vma->vm_end;
		पूर्ण
	पूर्ण

	अगर (atomic_पढ़ो(&mm->mm_count) > 1)
		sbytes += kobjsize(mm);
	अन्यथा
		bytes += kobjsize(mm);
	
	अगर (current->fs && current->fs->users > 1)
		sbytes += kobjsize(current->fs);
	अन्यथा
		bytes += kobjsize(current->fs);

	अगर (current->files && atomic_पढ़ो(&current->files->count) > 1)
		sbytes += kobjsize(current->files);
	अन्यथा
		bytes += kobjsize(current->files);

	अगर (current->sighand && refcount_पढ़ो(&current->sighand->count) > 1)
		sbytes += kobjsize(current->sighand);
	अन्यथा
		bytes += kobjsize(current->sighand);

	bytes += kobjsize(current); /* includes kernel stack */

	seq_म_लिखो(m,
		"Mem:\t%8lu bytes\n"
		"Slack:\t%8lu bytes\n"
		"Shared:\t%8lu bytes\n",
		bytes, slack, sbytes);

	mmap_पढ़ो_unlock(mm);
पूर्ण

अचिन्हित दीर्घ task_vsize(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा rb_node *p;
	अचिन्हित दीर्घ vsize = 0;

	mmap_पढ़ो_lock(mm);
	क्रम (p = rb_first(&mm->mm_rb); p; p = rb_next(p)) अणु
		vma = rb_entry(p, काष्ठा vm_area_काष्ठा, vm_rb);
		vsize += vma->vm_end - vma->vm_start;
	पूर्ण
	mmap_पढ़ो_unlock(mm);
	वापस vsize;
पूर्ण

अचिन्हित दीर्घ task_staपंचांग(काष्ठा mm_काष्ठा *mm,
			 अचिन्हित दीर्घ *shared, अचिन्हित दीर्घ *text,
			 अचिन्हित दीर्घ *data, अचिन्हित दीर्घ *resident)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा vm_region *region;
	काष्ठा rb_node *p;
	अचिन्हित दीर्घ size = kobjsize(mm);

	mmap_पढ़ो_lock(mm);
	क्रम (p = rb_first(&mm->mm_rb); p; p = rb_next(p)) अणु
		vma = rb_entry(p, काष्ठा vm_area_काष्ठा, vm_rb);
		size += kobjsize(vma);
		region = vma->vm_region;
		अगर (region) अणु
			size += kobjsize(region);
			size += region->vm_end - region->vm_start;
		पूर्ण
	पूर्ण

	*text = (PAGE_ALIGN(mm->end_code) - (mm->start_code & PAGE_MASK))
		>> PAGE_SHIFT;
	*data = (PAGE_ALIGN(mm->start_stack) - (mm->start_data & PAGE_MASK))
		>> PAGE_SHIFT;
	mmap_पढ़ो_unlock(mm);
	size >>= PAGE_SHIFT;
	size += *text + *data;
	*resident = size;
	वापस size;
पूर्ण

अटल पूर्णांक is_stack(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;

	/*
	 * We make no efक्रमt to guess what a given thपढ़ो considers to be
	 * its "stack".  It's not even well-defined क्रम programs written
	 * languages like Go.
	 */
	वापस vma->vm_start <= mm->start_stack &&
		vma->vm_end >= mm->start_stack;
पूर्ण

/*
 * display a single VMA to a sequenced file
 */
अटल पूर्णांक nommu_vma_show(काष्ठा seq_file *m, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	अचिन्हित दीर्घ ino = 0;
	काष्ठा file *file;
	dev_t dev = 0;
	पूर्णांक flags;
	अचिन्हित दीर्घ दीर्घ pgoff = 0;

	flags = vma->vm_flags;
	file = vma->vm_file;

	अगर (file) अणु
		काष्ठा inode *inode = file_inode(vma->vm_file);
		dev = inode->i_sb->s_dev;
		ino = inode->i_ino;
		pgoff = (loff_t)vma->vm_pgoff << PAGE_SHIFT;
	पूर्ण

	seq_setwidth(m, 25 + माप(व्योम *) * 6 - 1);
	seq_म_लिखो(m,
		   "%08lx-%08lx %c%c%c%c %08llx %02x:%02x %lu ",
		   vma->vm_start,
		   vma->vm_end,
		   flags & VM_READ ? 'r' : '-',
		   flags & VM_WRITE ? 'w' : '-',
		   flags & VM_EXEC ? 'x' : '-',
		   flags & VM_MAYSHARE ? flags & VM_SHARED ? 'S' : 's' : 'p',
		   pgoff,
		   MAJOR(dev), MINOR(dev), ino);

	अगर (file) अणु
		seq_pad(m, ' ');
		seq_file_path(m, file, "");
	पूर्ण अन्यथा अगर (mm && is_stack(vma)) अणु
		seq_pad(m, ' ');
		seq_माला_दो(m, "[stack]");
	पूर्ण

	seq_अ_दो(m, '\n');
	वापस 0;
पूर्ण

/*
 * display mapping lines क्रम a particular process's /proc/pid/maps
 */
अटल पूर्णांक show_map(काष्ठा seq_file *m, व्योम *_p)
अणु
	काष्ठा rb_node *p = _p;

	वापस nommu_vma_show(m, rb_entry(p, काष्ठा vm_area_काष्ठा, vm_rb));
पूर्ण

अटल व्योम *m_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	काष्ठा proc_maps_निजी *priv = m->निजी;
	काष्ठा mm_काष्ठा *mm;
	काष्ठा rb_node *p;
	loff_t n = *pos;

	/* pin the task and mm whilst we play with them */
	priv->task = get_proc_task(priv->inode);
	अगर (!priv->task)
		वापस ERR_PTR(-ESRCH);

	mm = priv->mm;
	अगर (!mm || !mmget_not_zero(mm))
		वापस शून्य;

	अगर (mmap_पढ़ो_lock_समाप्तable(mm)) अणु
		mmput(mm);
		वापस ERR_PTR(-EINTR);
	पूर्ण

	/* start from the Nth VMA */
	क्रम (p = rb_first(&mm->mm_rb); p; p = rb_next(p))
		अगर (n-- == 0)
			वापस p;

	mmap_पढ़ो_unlock(mm);
	mmput(mm);
	वापस शून्य;
पूर्ण

अटल व्योम m_stop(काष्ठा seq_file *m, व्योम *_vml)
अणु
	काष्ठा proc_maps_निजी *priv = m->निजी;

	अगर (!IS_ERR_OR_शून्य(_vml)) अणु
		mmap_पढ़ो_unlock(priv->mm);
		mmput(priv->mm);
	पूर्ण
	अगर (priv->task) अणु
		put_task_काष्ठा(priv->task);
		priv->task = शून्य;
	पूर्ण
पूर्ण

अटल व्योम *m_next(काष्ठा seq_file *m, व्योम *_p, loff_t *pos)
अणु
	काष्ठा rb_node *p = _p;

	(*pos)++;
	वापस p ? rb_next(p) : शून्य;
पूर्ण

अटल स्थिर काष्ठा seq_operations proc_pid_maps_ops = अणु
	.start	= m_start,
	.next	= m_next,
	.stop	= m_stop,
	.show	= show_map
पूर्ण;

अटल पूर्णांक maps_खोलो(काष्ठा inode *inode, काष्ठा file *file,
		     स्थिर काष्ठा seq_operations *ops)
अणु
	काष्ठा proc_maps_निजी *priv;

	priv = __seq_खोलो_निजी(file, ops, माप(*priv));
	अगर (!priv)
		वापस -ENOMEM;

	priv->inode = inode;
	priv->mm = proc_mem_खोलो(inode, PTRACE_MODE_READ);
	अगर (IS_ERR(priv->mm)) अणु
		पूर्णांक err = PTR_ERR(priv->mm);

		seq_release_निजी(inode, file);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक map_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *seq = file->निजी_data;
	काष्ठा proc_maps_निजी *priv = seq->निजी;

	अगर (priv->mm)
		mmdrop(priv->mm);

	वापस seq_release_निजी(inode, file);
पूर्ण

अटल पूर्णांक pid_maps_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस maps_खोलो(inode, file, &proc_pid_maps_ops);
पूर्ण

स्थिर काष्ठा file_operations proc_pid_maps_operations = अणु
	.खोलो		= pid_maps_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= map_release,
पूर्ण;

