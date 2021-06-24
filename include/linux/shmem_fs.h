<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SHMEM_FS_H
#घोषणा __SHMEM_FS_H

#समावेश <linux/file.h>
#समावेश <linux/swap.h>
#समावेश <linux/mempolicy.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/percpu_counter.h>
#समावेश <linux/xattr.h>
#समावेश <linux/fs_parser.h>

/* inode in-kernel data */

काष्ठा shmem_inode_info अणु
	spinlock_t		lock;
	अचिन्हित पूर्णांक		seals;		/* shmem seals */
	अचिन्हित दीर्घ		flags;
	अचिन्हित दीर्घ		alloced;	/* data pages alloced to file */
	अचिन्हित दीर्घ		swapped;	/* subtotal asचिन्हित to swap */
	काष्ठा list_head        shrinklist;     /* shrinkable hpage inodes */
	काष्ठा list_head	swaplist;	/* chain of maybes on swap */
	काष्ठा shared_policy	policy;		/* NUMA memory alloc policy */
	काष्ठा simple_xattrs	xattrs;		/* list of xattrs */
	atomic_t		stop_eviction;	/* hold when working on inode */
	काष्ठा inode		vfs_inode;
पूर्ण;

काष्ठा shmem_sb_info अणु
	अचिन्हित दीर्घ max_blocks;   /* How many blocks are allowed */
	काष्ठा percpu_counter used_blocks;  /* How many are allocated */
	अचिन्हित दीर्घ max_inodes;   /* How many inodes are allowed */
	अचिन्हित दीर्घ मुक्त_inodes;  /* How many are left क्रम allocation */
	spinlock_t stat_lock;	    /* Serialize shmem_sb_info changes */
	umode_t mode;		    /* Mount mode क्रम root directory */
	अचिन्हित अक्षर huge;	    /* Whether to try क्रम hugepages */
	kuid_t uid;		    /* Mount uid क्रम root directory */
	kgid_t gid;		    /* Mount gid क्रम root directory */
	bool full_inums;	    /* If i_ino should be uपूर्णांक or ino_t */
	ino_t next_ino;		    /* The next per-sb inode number to use */
	ino_t __percpu *ino_batch;  /* The next per-cpu inode number to use */
	काष्ठा mempolicy *mpol;     /* शेष memory policy क्रम mappings */
	spinlock_t shrinklist_lock;   /* Protects shrinklist */
	काष्ठा list_head shrinklist;  /* List of shinkable inodes */
	अचिन्हित दीर्घ shrinklist_len; /* Length of shrinklist */
पूर्ण;

अटल अंतरभूत काष्ठा shmem_inode_info *SHMEM_I(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा shmem_inode_info, vfs_inode);
पूर्ण

/*
 * Functions in mm/shmem.c called directly from अन्यथाwhere:
 */
बाह्य स्थिर काष्ठा fs_parameter_spec shmem_fs_parameters[];
बाह्य पूर्णांक shmem_init(व्योम);
बाह्य पूर्णांक shmem_init_fs_context(काष्ठा fs_context *fc);
बाह्य काष्ठा file *shmem_file_setup(स्थिर अक्षर *name,
					loff_t size, अचिन्हित दीर्घ flags);
बाह्य काष्ठा file *shmem_kernel_file_setup(स्थिर अक्षर *name, loff_t size,
					    अचिन्हित दीर्घ flags);
बाह्य काष्ठा file *shmem_file_setup_with_mnt(काष्ठा vfsmount *mnt,
		स्थिर अक्षर *name, loff_t size, अचिन्हित दीर्घ flags);
बाह्य पूर्णांक shmem_zero_setup(काष्ठा vm_area_काष्ठा *);
बाह्य अचिन्हित दीर्घ shmem_get_unmapped_area(काष्ठा file *, अचिन्हित दीर्घ addr,
		अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags);
बाह्य पूर्णांक shmem_lock(काष्ठा file *file, पूर्णांक lock, काष्ठा user_काष्ठा *user);
#अगर_घोषित CONFIG_SHMEM
बाह्य स्थिर काष्ठा address_space_operations shmem_aops;
अटल अंतरभूत bool shmem_mapping(काष्ठा address_space *mapping)
अणु
	वापस mapping->a_ops == &shmem_aops;
पूर्ण
#अन्यथा
अटल अंतरभूत bool shmem_mapping(काष्ठा address_space *mapping)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_SHMEM */
बाह्य व्योम shmem_unlock_mapping(काष्ठा address_space *mapping);
बाह्य काष्ठा page *shmem_पढ़ो_mapping_page_gfp(काष्ठा address_space *mapping,
					pgoff_t index, gfp_t gfp_mask);
बाह्य व्योम shmem_truncate_range(काष्ठा inode *inode, loff_t start, loff_t end);
बाह्य पूर्णांक shmem_unuse(अचिन्हित पूर्णांक type, bool frontswap,
		       अचिन्हित दीर्घ *fs_pages_to_unuse);

बाह्य bool shmem_huge_enabled(काष्ठा vm_area_काष्ठा *vma);
बाह्य अचिन्हित दीर्घ shmem_swap_usage(काष्ठा vm_area_काष्ठा *vma);
बाह्य अचिन्हित दीर्घ shmem_partial_swap_usage(काष्ठा address_space *mapping,
						pgoff_t start, pgoff_t end);

/* Flag allocation requirements to shmem_getpage */
क्रमागत sgp_type अणु
	SGP_READ,	/* करोn't exceed i_size, don't allocate page */
	SGP_CACHE,	/* करोn't exceed i_size, may allocate page */
	SGP_NOHUGE,	/* like SGP_CACHE, but no huge pages */
	SGP_HUGE,	/* like SGP_CACHE, huge pages preferred */
	SGP_WRITE,	/* may exceed i_size, may allocate !Uptodate page */
	SGP_FALLOC,	/* like SGP_WRITE, but make existing page Uptodate */
पूर्ण;

बाह्य पूर्णांक shmem_getpage(काष्ठा inode *inode, pgoff_t index,
		काष्ठा page **pagep, क्रमागत sgp_type sgp);

अटल अंतरभूत काष्ठा page *shmem_पढ़ो_mapping_page(
				काष्ठा address_space *mapping, pgoff_t index)
अणु
	वापस shmem_पढ़ो_mapping_page_gfp(mapping, index,
					mapping_gfp_mask(mapping));
पूर्ण

अटल अंतरभूत bool shmem_file(काष्ठा file *file)
अणु
	अगर (!IS_ENABLED(CONFIG_SHMEM))
		वापस false;
	अगर (!file || !file->f_mapping)
		वापस false;
	वापस shmem_mapping(file->f_mapping);
पूर्ण

बाह्य bool shmem_अक्षरge(काष्ठा inode *inode, दीर्घ pages);
बाह्य व्योम shmem_unअक्षरge(काष्ठा inode *inode, दीर्घ pages);

#अगर_घोषित CONFIG_SHMEM
बाह्य पूर्णांक shmem_mcopy_atomic_pte(काष्ठा mm_काष्ठा *dst_mm, pmd_t *dst_pmd,
				  काष्ठा vm_area_काष्ठा *dst_vma,
				  अचिन्हित दीर्घ dst_addr,
				  अचिन्हित दीर्घ src_addr,
				  काष्ठा page **pagep);
बाह्य पूर्णांक shmem_mfill_zeropage_pte(काष्ठा mm_काष्ठा *dst_mm,
				    pmd_t *dst_pmd,
				    काष्ठा vm_area_काष्ठा *dst_vma,
				    अचिन्हित दीर्घ dst_addr);
#अन्यथा
#घोषणा shmem_mcopy_atomic_pte(dst_mm, dst_pte, dst_vma, dst_addr, \
			       src_addr, pagep)        (अणु BUG(); 0; पूर्ण)
#घोषणा shmem_mfill_zeropage_pte(dst_mm, dst_pmd, dst_vma, \
				 dst_addr)      (अणु BUG(); 0; पूर्ण)
#पूर्ण_अगर

#पूर्ण_अगर
