<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Internal procfs definitions
 *
 * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/proc_fs.h>
#समावेश <linux/proc_ns.h>
#समावेश <linux/refcount.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/atomic.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/sched/coredump.h>
#समावेश <linux/sched/task.h>

काष्ठा ctl_table_header;
काष्ठा mempolicy;

/*
 * This is not completely implemented yet. The idea is to
 * create an in-memory tree (like the actual /proc fileप्रणाली
 * tree) of these proc_dir_entries, so that we can dynamically
 * add new files to /proc.
 *
 * parent/subdir are used क्रम the directory काष्ठाure (every /proc file has a
 * parent, but "subdir" is empty क्रम all non-directory entries).
 * subdir_node is used to build the rb tree "subdir" of the parent.
 */
काष्ठा proc_dir_entry अणु
	/*
	 * number of callers पूर्णांकo module in progress;
	 * negative -> it's going away RSN
	 */
	atomic_t in_use;
	refcount_t refcnt;
	काष्ठा list_head pde_खोलोers;	/* who did ->खोलो, but not ->release */
	/* protects ->pde_खोलोers and all काष्ठा pde_खोलोer instances */
	spinlock_t pde_unload_lock;
	काष्ठा completion *pde_unload_completion;
	स्थिर काष्ठा inode_operations *proc_iops;
	जोड़ अणु
		स्थिर काष्ठा proc_ops *proc_ops;
		स्थिर काष्ठा file_operations *proc_dir_ops;
	पूर्ण;
	स्थिर काष्ठा dentry_operations *proc_करोps;
	जोड़ अणु
		स्थिर काष्ठा seq_operations *seq_ops;
		पूर्णांक (*single_show)(काष्ठा seq_file *, व्योम *);
	पूर्ण;
	proc_ग_लिखो_t ग_लिखो;
	व्योम *data;
	अचिन्हित पूर्णांक state_size;
	अचिन्हित पूर्णांक low_ino;
	nlink_t nlink;
	kuid_t uid;
	kgid_t gid;
	loff_t size;
	काष्ठा proc_dir_entry *parent;
	काष्ठा rb_root subdir;
	काष्ठा rb_node subdir_node;
	अक्षर *name;
	umode_t mode;
	u8 flags;
	u8 namelen;
	अक्षर अंतरभूत_name[];
पूर्ण __अक्रमomize_layout;

#घोषणा SIZखातापूर्ण_PDE	(				\
	माप(काष्ठा proc_dir_entry) < 128 ? 128 :	\
	माप(काष्ठा proc_dir_entry) < 192 ? 192 :	\
	माप(काष्ठा proc_dir_entry) < 256 ? 256 :	\
	माप(काष्ठा proc_dir_entry) < 512 ? 512 :	\
	0)
#घोषणा SIZखातापूर्ण_PDE_INLINE_NAME (SIZखातापूर्ण_PDE - माप(काष्ठा proc_dir_entry))

अटल अंतरभूत bool pde_is_permanent(स्थिर काष्ठा proc_dir_entry *pde)
अणु
	वापस pde->flags & PROC_ENTRY_PERMANENT;
पूर्ण

बाह्य काष्ठा kmem_cache *proc_dir_entry_cache;
व्योम pde_मुक्त(काष्ठा proc_dir_entry *pde);

जोड़ proc_op अणु
	पूर्णांक (*proc_get_link)(काष्ठा dentry *, काष्ठा path *);
	पूर्णांक (*proc_show)(काष्ठा seq_file *m,
		काष्ठा pid_namespace *ns, काष्ठा pid *pid,
		काष्ठा task_काष्ठा *task);
	स्थिर अक्षर *lsm;
पूर्ण;

काष्ठा proc_inode अणु
	काष्ठा pid *pid;
	अचिन्हित पूर्णांक fd;
	जोड़ proc_op op;
	काष्ठा proc_dir_entry *pde;
	काष्ठा ctl_table_header *sysctl;
	काष्ठा ctl_table *sysctl_entry;
	काष्ठा hlist_node sibling_inodes;
	स्थिर काष्ठा proc_ns_operations *ns_ops;
	काष्ठा inode vfs_inode;
पूर्ण __अक्रमomize_layout;

/*
 * General functions
 */
अटल अंतरभूत काष्ठा proc_inode *PROC_I(स्थिर काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा proc_inode, vfs_inode);
पूर्ण

अटल अंतरभूत काष्ठा proc_dir_entry *PDE(स्थिर काष्ठा inode *inode)
अणु
	वापस PROC_I(inode)->pde;
पूर्ण

अटल अंतरभूत व्योम *__PDE_DATA(स्थिर काष्ठा inode *inode)
अणु
	वापस PDE(inode)->data;
पूर्ण

अटल अंतरभूत काष्ठा pid *proc_pid(स्थिर काष्ठा inode *inode)
अणु
	वापस PROC_I(inode)->pid;
पूर्ण

अटल अंतरभूत काष्ठा task_काष्ठा *get_proc_task(स्थिर काष्ठा inode *inode)
अणु
	वापस get_pid_task(proc_pid(inode), PIDTYPE_PID);
पूर्ण

व्योम task_dump_owner(काष्ठा task_काष्ठा *task, umode_t mode,
		     kuid_t *ruid, kgid_t *rgid);

अचिन्हित name_to_पूर्णांक(स्थिर काष्ठा qstr *qstr);
/*
 * Offset of the first process in the /proc root directory..
 */
#घोषणा FIRST_PROCESS_ENTRY 256

/* Worst हाल buffer size needed क्रम holding an पूर्णांकeger. */
#घोषणा PROC_NUMBUF 13

/*
 * array.c
 */
बाह्य स्थिर काष्ठा file_operations proc_tid_children_operations;

बाह्य व्योम proc_task_name(काष्ठा seq_file *m, काष्ठा task_काष्ठा *p,
			   bool escape);
बाह्य पूर्णांक proc_tid_stat(काष्ठा seq_file *, काष्ठा pid_namespace *,
			 काष्ठा pid *, काष्ठा task_काष्ठा *);
बाह्य पूर्णांक proc_tgid_stat(काष्ठा seq_file *, काष्ठा pid_namespace *,
			  काष्ठा pid *, काष्ठा task_काष्ठा *);
बाह्य पूर्णांक proc_pid_status(काष्ठा seq_file *, काष्ठा pid_namespace *,
			   काष्ठा pid *, काष्ठा task_काष्ठा *);
बाह्य पूर्णांक proc_pid_staपंचांग(काष्ठा seq_file *, काष्ठा pid_namespace *,
			  काष्ठा pid *, काष्ठा task_काष्ठा *);

/*
 * base.c
 */
बाह्य स्थिर काष्ठा dentry_operations pid_dentry_operations;
बाह्य पूर्णांक pid_getattr(काष्ठा user_namespace *, स्थिर काष्ठा path *,
		       काष्ठा kstat *, u32, अचिन्हित पूर्णांक);
बाह्य पूर्णांक proc_setattr(काष्ठा user_namespace *, काष्ठा dentry *,
			काष्ठा iattr *);
बाह्य व्योम proc_pid_evict_inode(काष्ठा proc_inode *);
बाह्य काष्ठा inode *proc_pid_make_inode(काष्ठा super_block *, काष्ठा task_काष्ठा *, umode_t);
बाह्य व्योम pid_update_inode(काष्ठा task_काष्ठा *, काष्ठा inode *);
बाह्य पूर्णांक pid_delete_dentry(स्थिर काष्ठा dentry *);
बाह्य पूर्णांक proc_pid_सूची_पढ़ो(काष्ठा file *, काष्ठा dir_context *);
काष्ठा dentry *proc_pid_lookup(काष्ठा dentry *, अचिन्हित पूर्णांक);
बाह्य loff_t mem_lseek(काष्ठा file *, loff_t, पूर्णांक);

/* Lookups */
प्रकार काष्ठा dentry *instantiate_t(काष्ठा dentry *,
				     काष्ठा task_काष्ठा *, स्थिर व्योम *);
bool proc_fill_cache(काष्ठा file *, काष्ठा dir_context *, स्थिर अक्षर *, अचिन्हित पूर्णांक,
			   instantiate_t, काष्ठा task_काष्ठा *, स्थिर व्योम *);

/*
 * generic.c
 */
काष्ठा proc_dir_entry *proc_create_reg(स्थिर अक्षर *name, umode_t mode,
		काष्ठा proc_dir_entry **parent, व्योम *data);
काष्ठा proc_dir_entry *proc_रेजिस्टर(काष्ठा proc_dir_entry *dir,
		काष्ठा proc_dir_entry *dp);
बाह्य काष्ठा dentry *proc_lookup(काष्ठा inode *, काष्ठा dentry *, अचिन्हित पूर्णांक);
काष्ठा dentry *proc_lookup_de(काष्ठा inode *, काष्ठा dentry *, काष्ठा proc_dir_entry *);
बाह्य पूर्णांक proc_सूची_पढ़ो(काष्ठा file *, काष्ठा dir_context *);
पूर्णांक proc_सूची_पढ़ो_de(काष्ठा file *, काष्ठा dir_context *, काष्ठा proc_dir_entry *);

अटल अंतरभूत व्योम pde_get(काष्ठा proc_dir_entry *pde)
अणु
	refcount_inc(&pde->refcnt);
पूर्ण
बाह्य व्योम pde_put(काष्ठा proc_dir_entry *);

अटल अंतरभूत bool is_empty_pde(स्थिर काष्ठा proc_dir_entry *pde)
अणु
	वापस S_ISसूची(pde->mode) && !pde->proc_iops;
पूर्ण
बाह्य sमाप_प्रकार proc_simple_ग_लिखो(काष्ठा file *, स्थिर अक्षर __user *, माप_प्रकार, loff_t *);

/*
 * inode.c
 */
काष्ठा pde_खोलोer अणु
	काष्ठा list_head lh;
	काष्ठा file *file;
	bool closing;
	काष्ठा completion *c;
पूर्ण __अक्रमomize_layout;
बाह्य स्थिर काष्ठा inode_operations proc_link_inode_operations;
बाह्य स्थिर काष्ठा inode_operations proc_pid_link_inode_operations;
बाह्य स्थिर काष्ठा super_operations proc_sops;

व्योम proc_init_kmemcache(व्योम);
व्योम proc_invalidate_siblings_dcache(काष्ठा hlist_head *inodes, spinlock_t *lock);
व्योम set_proc_pid_nlink(व्योम);
बाह्य काष्ठा inode *proc_get_inode(काष्ठा super_block *, काष्ठा proc_dir_entry *);
बाह्य व्योम proc_entry_runकरोwn(काष्ठा proc_dir_entry *);

/*
 * proc_namespaces.c
 */
बाह्य स्थिर काष्ठा inode_operations proc_ns_dir_inode_operations;
बाह्य स्थिर काष्ठा file_operations proc_ns_dir_operations;

/*
 * proc_net.c
 */
बाह्य स्थिर काष्ठा file_operations proc_net_operations;
बाह्य स्थिर काष्ठा inode_operations proc_net_inode_operations;

#अगर_घोषित CONFIG_NET
बाह्य पूर्णांक proc_net_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक proc_net_init(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

/*
 * proc_self.c
 */
बाह्य पूर्णांक proc_setup_self(काष्ठा super_block *);

/*
 * proc_thपढ़ो_self.c
 */
बाह्य पूर्णांक proc_setup_thपढ़ो_self(काष्ठा super_block *);
बाह्य व्योम proc_thपढ़ो_self_init(व्योम);

/*
 * proc_sysctl.c
 */
#अगर_घोषित CONFIG_PROC_SYSCTL
बाह्य पूर्णांक proc_sys_init(व्योम);
बाह्य व्योम proc_sys_evict_inode(काष्ठा inode *inode,
				 काष्ठा ctl_table_header *head);
#अन्यथा
अटल अंतरभूत व्योम proc_sys_init(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम proc_sys_evict_inode(काष्ठा  inode *inode,
					काष्ठा ctl_table_header *head) अणु पूर्ण
#पूर्ण_अगर

/*
 * proc_tty.c
 */
#अगर_घोषित CONFIG_TTY
बाह्य व्योम proc_tty_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम proc_tty_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/*
 * root.c
 */
बाह्य काष्ठा proc_dir_entry proc_root;

बाह्य व्योम proc_self_init(व्योम);

/*
 * task_[no]mmu.c
 */
काष्ठा mem_size_stats;
काष्ठा proc_maps_निजी अणु
	काष्ठा inode *inode;
	काष्ठा task_काष्ठा *task;
	काष्ठा mm_काष्ठा *mm;
#अगर_घोषित CONFIG_MMU
	काष्ठा vm_area_काष्ठा *tail_vma;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NUMA
	काष्ठा mempolicy *task_mempolicy;
#पूर्ण_अगर
पूर्ण __अक्रमomize_layout;

काष्ठा mm_काष्ठा *proc_mem_खोलो(काष्ठा inode *inode, अचिन्हित पूर्णांक mode);

बाह्य स्थिर काष्ठा file_operations proc_pid_maps_operations;
बाह्य स्थिर काष्ठा file_operations proc_pid_numa_maps_operations;
बाह्य स्थिर काष्ठा file_operations proc_pid_smaps_operations;
बाह्य स्थिर काष्ठा file_operations proc_pid_smaps_rollup_operations;
बाह्य स्थिर काष्ठा file_operations proc_clear_refs_operations;
बाह्य स्थिर काष्ठा file_operations proc_pagemap_operations;

बाह्य अचिन्हित दीर्घ task_vsize(काष्ठा mm_काष्ठा *);
बाह्य अचिन्हित दीर्घ task_staपंचांग(काष्ठा mm_काष्ठा *,
				अचिन्हित दीर्घ *, अचिन्हित दीर्घ *,
				अचिन्हित दीर्घ *, अचिन्हित दीर्घ *);
बाह्य व्योम task_mem(काष्ठा seq_file *, काष्ठा mm_काष्ठा *);

बाह्य स्थिर काष्ठा dentry_operations proc_net_dentry_ops;
अटल अंतरभूत व्योम pde_क्रमce_lookup(काष्ठा proc_dir_entry *pde)
अणु
	/* /proc/net/ entries can be changed under us by setns(CLONE_NEWNET) */
	pde->proc_करोps = &proc_net_dentry_ops;
पूर्ण
