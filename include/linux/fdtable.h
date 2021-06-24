<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * descriptor table पूर्णांकernals; you almost certainly want file.h instead.
 */

#अगर_अघोषित __LINUX_FDTABLE_H
#घोषणा __LINUX_FDTABLE_H

#समावेश <linux/posix_types.h>
#समावेश <linux/compiler.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/nospec.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>

#समावेश <linux/atomic.h>

/*
 * The शेष fd array needs to be at least BITS_PER_LONG,
 * as this is the granularity वापसed by copy_fdset().
 */
#घोषणा NR_OPEN_DEFAULT BITS_PER_LONG
#घोषणा NR_OPEN_MAX ~0U

काष्ठा fdtable अणु
	अचिन्हित पूर्णांक max_fds;
	काष्ठा file __rcu **fd;      /* current fd array */
	अचिन्हित दीर्घ *बंद_on_exec;
	अचिन्हित दीर्घ *खोलो_fds;
	अचिन्हित दीर्घ *full_fds_bits;
	काष्ठा rcu_head rcu;
पूर्ण;

अटल अंतरभूत bool बंद_on_exec(अचिन्हित पूर्णांक fd, स्थिर काष्ठा fdtable *fdt)
अणु
	वापस test_bit(fd, fdt->बंद_on_exec);
पूर्ण

अटल अंतरभूत bool fd_is_खोलो(अचिन्हित पूर्णांक fd, स्थिर काष्ठा fdtable *fdt)
अणु
	वापस test_bit(fd, fdt->खोलो_fds);
पूर्ण

/*
 * Open file table काष्ठाure
 */
काष्ठा files_काष्ठा अणु
  /*
   * पढ़ो mostly part
   */
	atomic_t count;
	bool resize_in_progress;
	रुको_queue_head_t resize_रुको;

	काष्ठा fdtable __rcu *fdt;
	काष्ठा fdtable fdtab;
  /*
   * written part on a separate cache line in SMP
   */
	spinlock_t file_lock ____cacheline_aligned_in_smp;
	अचिन्हित पूर्णांक next_fd;
	अचिन्हित दीर्घ बंद_on_exec_init[1];
	अचिन्हित दीर्घ खोलो_fds_init[1];
	अचिन्हित दीर्घ full_fds_bits_init[1];
	काष्ठा file __rcu * fd_array[NR_OPEN_DEFAULT];
पूर्ण;

काष्ठा file_operations;
काष्ठा vfsmount;
काष्ठा dentry;

#घोषणा rcu_dereference_check_fdtable(files, fdtfd) \
	rcu_dereference_check((fdtfd), lockdep_is_held(&(files)->file_lock))

#घोषणा files_fdtable(files) \
	rcu_dereference_check_fdtable((files), (files)->fdt)

/*
 * The caller must ensure that fd table isn't shared or hold rcu or file lock
 */
अटल अंतरभूत काष्ठा file *files_lookup_fd_raw(काष्ठा files_काष्ठा *files, अचिन्हित पूर्णांक fd)
अणु
	काष्ठा fdtable *fdt = rcu_dereference_raw(files->fdt);

	अगर (fd < fdt->max_fds) अणु
		fd = array_index_nospec(fd, fdt->max_fds);
		वापस rcu_dereference_raw(fdt->fd[fd]);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा file *files_lookup_fd_locked(काष्ठा files_काष्ठा *files, अचिन्हित पूर्णांक fd)
अणु
	RCU_LOCKDEP_WARN(!lockdep_is_held(&files->file_lock),
			   "suspicious rcu_dereference_check() usage");
	वापस files_lookup_fd_raw(files, fd);
पूर्ण

अटल अंतरभूत काष्ठा file *files_lookup_fd_rcu(काष्ठा files_काष्ठा *files, अचिन्हित पूर्णांक fd)
अणु
	RCU_LOCKDEP_WARN(!rcu_पढ़ो_lock_held(),
			   "suspicious rcu_dereference_check() usage");
	वापस files_lookup_fd_raw(files, fd);
पूर्ण

अटल अंतरभूत काष्ठा file *lookup_fd_rcu(अचिन्हित पूर्णांक fd)
अणु
	वापस files_lookup_fd_rcu(current->files, fd);
पूर्ण

काष्ठा file *task_lookup_fd_rcu(काष्ठा task_काष्ठा *task, अचिन्हित पूर्णांक fd);
काष्ठा file *task_lookup_next_fd_rcu(काष्ठा task_काष्ठा *task, अचिन्हित पूर्णांक *fd);

काष्ठा task_काष्ठा;

व्योम put_files_काष्ठा(काष्ठा files_काष्ठा *fs);
पूर्णांक unshare_files(व्योम);
काष्ठा files_काष्ठा *dup_fd(काष्ठा files_काष्ठा *, अचिन्हित, पूर्णांक *) __latent_entropy;
व्योम करो_बंद_on_exec(काष्ठा files_काष्ठा *);
पूर्णांक iterate_fd(काष्ठा files_काष्ठा *, अचिन्हित,
		पूर्णांक (*)(स्थिर व्योम *, काष्ठा file *, अचिन्हित),
		स्थिर व्योम *);

बाह्य पूर्णांक बंद_fd(अचिन्हित पूर्णांक fd);
बाह्य पूर्णांक __बंद_range(अचिन्हित पूर्णांक fd, अचिन्हित पूर्णांक max_fd, अचिन्हित पूर्णांक flags);
बाह्य पूर्णांक बंद_fd_get_file(अचिन्हित पूर्णांक fd, काष्ठा file **res);
बाह्य पूर्णांक unshare_fd(अचिन्हित दीर्घ unshare_flags, अचिन्हित पूर्णांक max_fds,
		      काष्ठा files_काष्ठा **new_fdp);

बाह्य काष्ठा kmem_cache *files_cachep;

#पूर्ण_अगर /* __LINUX_FDTABLE_H */
