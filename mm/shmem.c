<शैली गुरु>
/*
 * Resizable भव memory fileप्रणाली क्रम Linux.
 *
 * Copyright (C) 2000 Linus Torvalds.
 *		 2000 Transmeta Corp.
 *		 2000-2001 Christoph Rohland
 *		 2000-2001 SAP AG
 *		 2002 Red Hat Inc.
 * Copyright (C) 2002-2011 Hugh Dickins.
 * Copyright (C) 2011 Google Inc.
 * Copyright (C) 2002-2005 VERITAS Software Corporation.
 * Copyright (C) 2004 Andi Kleen, SuSE Lअसल
 *
 * Extended attribute support क्रम पंचांगpfs:
 * Copyright (c) 2004, Luke Kenneth Casson Leighton <lkcl@lkcl.net>
 * Copyright (c) 2004 Red Hat, Inc., James Morris <jmorris@redhat.com>
 *
 * tiny-shmem:
 * Copyright (c) 2004, 2008 Matt Mackall <mpm@selenic.com>
 *
 * This file is released under the GPL.
 */

#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/vfs.h>
#समावेश <linux/mount.h>
#समावेश <linux/ramfs.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/file.h>
#समावेश <linux/mm.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/export.h>
#समावेश <linux/swap.h>
#समावेश <linux/uपन.स>
#समावेश <linux/khugepaged.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/frontswap.h>
#समावेश <linux/fs_parser.h>

#समावेश <यंत्र/tlbflush.h> /* क्रम arch/microblaze update_mmu_cache() */

अटल काष्ठा vfsmount *shm_mnt;

#अगर_घोषित CONFIG_SHMEM
/*
 * This भव memory fileप्रणाली is heavily based on the ramfs. It
 * extends ramfs by the ability to use swap and honor resource limits
 * which makes it a completely usable fileप्रणाली.
 */

#समावेश <linux/xattr.h>
#समावेश <linux/exportfs.h>
#समावेश <linux/posix_acl.h>
#समावेश <linux/posix_acl_xattr.h>
#समावेश <linux/mman.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/percpu_counter.h>
#समावेश <linux/fभाग.स>
#समावेश <linux/splice.h>
#समावेश <linux/security.h>
#समावेश <linux/swapops.h>
#समावेश <linux/mempolicy.h>
#समावेश <linux/namei.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/migrate.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/seq_file.h>
#समावेश <linux/magic.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/fcntl.h>
#समावेश <uapi/linux/memfd.h>
#समावेश <linux/userfaultfd_k.h>
#समावेश <linux/rmap.h>
#समावेश <linux/uuid.h>

#समावेश <linux/uaccess.h>

#समावेश "internal.h"

#घोषणा BLOCKS_PER_PAGE  (PAGE_SIZE/512)
#घोषणा VM_ACCT(size)    (PAGE_ALIGN(size) >> PAGE_SHIFT)

/* Pretend that each entry is of this size in directory's i_size */
#घोषणा BOGO_सूचीENT_SIZE 20

/* Symlink up to this size is kदो_स्मृति'ed instead of using a swappable page */
#घोषणा SHORT_SYMLINK_LEN 128

/*
 * shmem_fallocate communicates with shmem_fault or shmem_ग_लिखोpage via
 * inode->i_निजी (with i_mutex making sure that it has only one user at
 * a समय): we would prefer not to enlarge the shmem inode just क्रम that.
 */
काष्ठा shmem_falloc अणु
	रुको_queue_head_t *रुकोq; /* faults पूर्णांकo hole रुको क्रम punch to end */
	pgoff_t start;		/* start of range currently being fallocated */
	pgoff_t next;		/* the next page offset to be fallocated */
	pgoff_t nr_falloced;	/* how many new pages have been fallocated */
	pgoff_t nr_unswapped;	/* how often ग_लिखोpage refused to swap out */
पूर्ण;

काष्ठा shmem_options अणु
	अचिन्हित दीर्घ दीर्घ blocks;
	अचिन्हित दीर्घ दीर्घ inodes;
	काष्ठा mempolicy *mpol;
	kuid_t uid;
	kgid_t gid;
	umode_t mode;
	bool full_inums;
	पूर्णांक huge;
	पूर्णांक seen;
#घोषणा SHMEM_SEEN_BLOCKS 1
#घोषणा SHMEM_SEEN_INODES 2
#घोषणा SHMEM_SEEN_HUGE 4
#घोषणा SHMEM_SEEN_INUMS 8
पूर्ण;

#अगर_घोषित CONFIG_TMPFS
अटल अचिन्हित दीर्घ shmem_शेष_max_blocks(व्योम)
अणु
	वापस totalram_pages() / 2;
पूर्ण

अटल अचिन्हित दीर्घ shmem_शेष_max_inodes(व्योम)
अणु
	अचिन्हित दीर्घ nr_pages = totalram_pages();

	वापस min(nr_pages - totalhigh_pages(), nr_pages / 2);
पूर्ण
#पूर्ण_अगर

अटल bool shmem_should_replace_page(काष्ठा page *page, gfp_t gfp);
अटल पूर्णांक shmem_replace_page(काष्ठा page **pagep, gfp_t gfp,
				काष्ठा shmem_inode_info *info, pgoff_t index);
अटल पूर्णांक shmem_swapin_page(काष्ठा inode *inode, pgoff_t index,
			     काष्ठा page **pagep, क्रमागत sgp_type sgp,
			     gfp_t gfp, काष्ठा vm_area_काष्ठा *vma,
			     vm_fault_t *fault_type);
अटल पूर्णांक shmem_getpage_gfp(काष्ठा inode *inode, pgoff_t index,
		काष्ठा page **pagep, क्रमागत sgp_type sgp,
		gfp_t gfp, काष्ठा vm_area_काष्ठा *vma,
		काष्ठा vm_fault *vmf, vm_fault_t *fault_type);

पूर्णांक shmem_getpage(काष्ठा inode *inode, pgoff_t index,
		काष्ठा page **pagep, क्रमागत sgp_type sgp)
अणु
	वापस shmem_getpage_gfp(inode, index, pagep, sgp,
		mapping_gfp_mask(inode->i_mapping), शून्य, शून्य, शून्य);
पूर्ण

अटल अंतरभूत काष्ठा shmem_sb_info *SHMEM_SB(काष्ठा super_block *sb)
अणु
	वापस sb->s_fs_info;
पूर्ण

/*
 * shmem_file_setup pre-accounts the whole fixed size of a VM object,
 * क्रम shared memory and क्रम shared anonymous (/dev/zero) mappings
 * (unless MAP_NORESERVE and sysctl_overcommit_memory <= 1),
 * consistent with the pre-accounting of निजी mappings ...
 */
अटल अंतरभूत पूर्णांक shmem_acct_size(अचिन्हित दीर्घ flags, loff_t size)
अणु
	वापस (flags & VM_NORESERVE) ?
		0 : security_vm_enough_memory_mm(current->mm, VM_ACCT(size));
पूर्ण

अटल अंतरभूत व्योम shmem_unacct_size(अचिन्हित दीर्घ flags, loff_t size)
अणु
	अगर (!(flags & VM_NORESERVE))
		vm_unacct_memory(VM_ACCT(size));
पूर्ण

अटल अंतरभूत पूर्णांक shmem_reacct_size(अचिन्हित दीर्घ flags,
		loff_t oldsize, loff_t newsize)
अणु
	अगर (!(flags & VM_NORESERVE)) अणु
		अगर (VM_ACCT(newsize) > VM_ACCT(oldsize))
			वापस security_vm_enough_memory_mm(current->mm,
					VM_ACCT(newsize) - VM_ACCT(oldsize));
		अन्यथा अगर (VM_ACCT(newsize) < VM_ACCT(oldsize))
			vm_unacct_memory(VM_ACCT(oldsize) - VM_ACCT(newsize));
	पूर्ण
	वापस 0;
पूर्ण

/*
 * ... whereas पंचांगpfs objects are accounted incrementally as
 * pages are allocated, in order to allow large sparse files.
 * shmem_getpage reports shmem_acct_block failure as -ENOSPC not -ENOMEM,
 * so that a failure on a sparse पंचांगpfs mapping will give SIGBUS not OOM.
 */
अटल अंतरभूत पूर्णांक shmem_acct_block(अचिन्हित दीर्घ flags, दीर्घ pages)
अणु
	अगर (!(flags & VM_NORESERVE))
		वापस 0;

	वापस security_vm_enough_memory_mm(current->mm,
			pages * VM_ACCT(PAGE_SIZE));
पूर्ण

अटल अंतरभूत व्योम shmem_unacct_blocks(अचिन्हित दीर्घ flags, दीर्घ pages)
अणु
	अगर (flags & VM_NORESERVE)
		vm_unacct_memory(pages * VM_ACCT(PAGE_SIZE));
पूर्ण

अटल अंतरभूत bool shmem_inode_acct_block(काष्ठा inode *inode, दीर्घ pages)
अणु
	काष्ठा shmem_inode_info *info = SHMEM_I(inode);
	काष्ठा shmem_sb_info *sbinfo = SHMEM_SB(inode->i_sb);

	अगर (shmem_acct_block(info->flags, pages))
		वापस false;

	अगर (sbinfo->max_blocks) अणु
		अगर (percpu_counter_compare(&sbinfo->used_blocks,
					   sbinfo->max_blocks - pages) > 0)
			जाओ unacct;
		percpu_counter_add(&sbinfo->used_blocks, pages);
	पूर्ण

	वापस true;

unacct:
	shmem_unacct_blocks(info->flags, pages);
	वापस false;
पूर्ण

अटल अंतरभूत व्योम shmem_inode_unacct_blocks(काष्ठा inode *inode, दीर्घ pages)
अणु
	काष्ठा shmem_inode_info *info = SHMEM_I(inode);
	काष्ठा shmem_sb_info *sbinfo = SHMEM_SB(inode->i_sb);

	अगर (sbinfo->max_blocks)
		percpu_counter_sub(&sbinfo->used_blocks, pages);
	shmem_unacct_blocks(info->flags, pages);
पूर्ण

अटल स्थिर काष्ठा super_operations shmem_ops;
स्थिर काष्ठा address_space_operations shmem_aops;
अटल स्थिर काष्ठा file_operations shmem_file_operations;
अटल स्थिर काष्ठा inode_operations shmem_inode_operations;
अटल स्थिर काष्ठा inode_operations shmem_dir_inode_operations;
अटल स्थिर काष्ठा inode_operations shmem_special_inode_operations;
अटल स्थिर काष्ठा vm_operations_काष्ठा shmem_vm_ops;
अटल काष्ठा file_प्रणाली_type shmem_fs_type;

bool vma_is_shmem(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस vma->vm_ops == &shmem_vm_ops;
पूर्ण

अटल LIST_HEAD(shmem_swaplist);
अटल DEFINE_MUTEX(shmem_swaplist_mutex);

/*
 * shmem_reserve_inode() perक्रमms bookkeeping to reserve a shmem inode, and
 * produces a novel ino क्रम the newly allocated inode.
 *
 * It may also be called when making a hard link to permit the space needed by
 * each dentry. However, in that हाल, no new inode number is needed since that
 * पूर्णांकernally draws from another pool of inode numbers (currently global
 * get_next_ino()). This हाल is indicated by passing शून्य as inop.
 */
#घोषणा SHMEM_INO_BATCH 1024
अटल पूर्णांक shmem_reserve_inode(काष्ठा super_block *sb, ino_t *inop)
अणु
	काष्ठा shmem_sb_info *sbinfo = SHMEM_SB(sb);
	ino_t ino;

	अगर (!(sb->s_flags & SB_KERNMOUNT)) अणु
		spin_lock(&sbinfo->stat_lock);
		अगर (sbinfo->max_inodes) अणु
			अगर (!sbinfo->मुक्त_inodes) अणु
				spin_unlock(&sbinfo->stat_lock);
				वापस -ENOSPC;
			पूर्ण
			sbinfo->मुक्त_inodes--;
		पूर्ण
		अगर (inop) अणु
			ino = sbinfo->next_ino++;
			अगर (unlikely(is_zero_ino(ino)))
				ino = sbinfo->next_ino++;
			अगर (unlikely(!sbinfo->full_inums &&
				     ino > अच_पूर्णांक_उच्च)) अणु
				/*
				 * Emulate get_next_ino uपूर्णांक wraparound क्रम
				 * compatibility
				 */
				अगर (IS_ENABLED(CONFIG_64BIT))
					pr_warn("%s: inode number overflow on device %d, consider using inode64 mount option\n",
						__func__, MINOR(sb->s_dev));
				sbinfo->next_ino = 1;
				ino = sbinfo->next_ino++;
			पूर्ण
			*inop = ino;
		पूर्ण
		spin_unlock(&sbinfo->stat_lock);
	पूर्ण अन्यथा अगर (inop) अणु
		/*
		 * __shmem_file_setup, one of our callers, is lock-मुक्त: it
		 * करोesn't hold stat_lock in shmem_reserve_inode since
		 * max_inodes is always 0, and is called from potentially
		 * unknown contexts. As such, use a per-cpu batched allocator
		 * which करोesn't require the per-sb stat_lock unless we are at
		 * the batch boundary.
		 *
		 * We करोn't need to worry about inodeअणु32,64पूर्ण since SB_KERNMOUNT
		 * shmem mounts are not exposed to userspace, so we करोn't need
		 * to worry about things like glibc compatibility.
		 */
		ino_t *next_ino;
		next_ino = per_cpu_ptr(sbinfo->ino_batch, get_cpu());
		ino = *next_ino;
		अगर (unlikely(ino % SHMEM_INO_BATCH == 0)) अणु
			spin_lock(&sbinfo->stat_lock);
			ino = sbinfo->next_ino;
			sbinfo->next_ino += SHMEM_INO_BATCH;
			spin_unlock(&sbinfo->stat_lock);
			अगर (unlikely(is_zero_ino(ino)))
				ino++;
		पूर्ण
		*inop = ino;
		*next_ino = ++ino;
		put_cpu();
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम shmem_मुक्त_inode(काष्ठा super_block *sb)
अणु
	काष्ठा shmem_sb_info *sbinfo = SHMEM_SB(sb);
	अगर (sbinfo->max_inodes) अणु
		spin_lock(&sbinfo->stat_lock);
		sbinfo->मुक्त_inodes++;
		spin_unlock(&sbinfo->stat_lock);
	पूर्ण
पूर्ण

/**
 * shmem_recalc_inode - recalculate the block usage of an inode
 * @inode: inode to recalc
 *
 * We have to calculate the मुक्त blocks since the mm can drop
 * undirtied hole pages behind our back.
 *
 * But normally   info->alloced == inode->i_mapping->nrpages + info->swapped
 * So mm मुक्तd is info->alloced - (inode->i_mapping->nrpages + info->swapped)
 *
 * It has to be called with the spinlock held.
 */
अटल व्योम shmem_recalc_inode(काष्ठा inode *inode)
अणु
	काष्ठा shmem_inode_info *info = SHMEM_I(inode);
	दीर्घ मुक्तd;

	मुक्तd = info->alloced - info->swapped - inode->i_mapping->nrpages;
	अगर (मुक्तd > 0) अणु
		info->alloced -= मुक्तd;
		inode->i_blocks -= मुक्तd * BLOCKS_PER_PAGE;
		shmem_inode_unacct_blocks(inode, मुक्तd);
	पूर्ण
पूर्ण

bool shmem_अक्षरge(काष्ठा inode *inode, दीर्घ pages)
अणु
	काष्ठा shmem_inode_info *info = SHMEM_I(inode);
	अचिन्हित दीर्घ flags;

	अगर (!shmem_inode_acct_block(inode, pages))
		वापस false;

	/* nrpages adjusपंचांगent first, then shmem_recalc_inode() when balanced */
	inode->i_mapping->nrpages += pages;

	spin_lock_irqsave(&info->lock, flags);
	info->alloced += pages;
	inode->i_blocks += pages * BLOCKS_PER_PAGE;
	shmem_recalc_inode(inode);
	spin_unlock_irqrestore(&info->lock, flags);

	वापस true;
पूर्ण

व्योम shmem_unअक्षरge(काष्ठा inode *inode, दीर्घ pages)
अणु
	काष्ठा shmem_inode_info *info = SHMEM_I(inode);
	अचिन्हित दीर्घ flags;

	/* nrpages adjusपंचांगent करोne by __delete_from_page_cache() or caller */

	spin_lock_irqsave(&info->lock, flags);
	info->alloced -= pages;
	inode->i_blocks -= pages * BLOCKS_PER_PAGE;
	shmem_recalc_inode(inode);
	spin_unlock_irqrestore(&info->lock, flags);

	shmem_inode_unacct_blocks(inode, pages);
पूर्ण

/*
 * Replace item expected in xarray by a new item, जबतक holding xa_lock.
 */
अटल पूर्णांक shmem_replace_entry(काष्ठा address_space *mapping,
			pgoff_t index, व्योम *expected, व्योम *replacement)
अणु
	XA_STATE(xas, &mapping->i_pages, index);
	व्योम *item;

	VM_BUG_ON(!expected);
	VM_BUG_ON(!replacement);
	item = xas_load(&xas);
	अगर (item != expected)
		वापस -ENOENT;
	xas_store(&xas, replacement);
	वापस 0;
पूर्ण

/*
 * Someबार, beक्रमe we decide whether to proceed or to fail, we must check
 * that an entry was not alपढ़ोy brought back from swap by a racing thपढ़ो.
 *
 * Checking page is not enough: by the समय a SwapCache page is locked, it
 * might be reused, and again be SwapCache, using the same swap as beक्रमe.
 */
अटल bool shmem_confirm_swap(काष्ठा address_space *mapping,
			       pgoff_t index, swp_entry_t swap)
अणु
	वापस xa_load(&mapping->i_pages, index) == swp_to_radix_entry(swap);
पूर्ण

/*
 * Definitions क्रम "huge tmpfs": पंचांगpfs mounted with the huge= option
 *
 * SHMEM_HUGE_NEVER:
 *	disables huge pages क्रम the mount;
 * SHMEM_HUGE_ALWAYS:
 *	enables huge pages क्रम the mount;
 * SHMEM_HUGE_WITHIN_SIZE:
 *	only allocate huge pages अगर the page will be fully within i_size,
 *	also respect fadvise()/madvise() hपूर्णांकs;
 * SHMEM_HUGE_ADVISE:
 *	only allocate huge pages अगर requested with fadvise()/madvise();
 */

#घोषणा SHMEM_HUGE_NEVER	0
#घोषणा SHMEM_HUGE_ALWAYS	1
#घोषणा SHMEM_HUGE_WITHIN_SIZE	2
#घोषणा SHMEM_HUGE_ADVISE	3

/*
 * Special values.
 * Only can be set via /sys/kernel/mm/transparent_hugepage/shmem_enabled:
 *
 * SHMEM_HUGE_DENY:
 *	disables huge on shm_mnt and all mounts, क्रम emergency use;
 * SHMEM_HUGE_FORCE:
 *	enables huge on shm_mnt and all mounts, w/o needing option, क्रम testing;
 *
 */
#घोषणा SHMEM_HUGE_DENY		(-1)
#घोषणा SHMEM_HUGE_FORCE	(-2)

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
/* अगरdef here to aव्योम bloating shmem.o when not necessary */

अटल पूर्णांक shmem_huge __पढ़ो_mostly;

#अगर defined(CONFIG_SYSFS)
अटल पूर्णांक shmem_parse_huge(स्थिर अक्षर *str)
अणु
	अगर (!म_भेद(str, "never"))
		वापस SHMEM_HUGE_NEVER;
	अगर (!म_भेद(str, "always"))
		वापस SHMEM_HUGE_ALWAYS;
	अगर (!म_भेद(str, "within_size"))
		वापस SHMEM_HUGE_WITHIN_SIZE;
	अगर (!म_भेद(str, "advise"))
		वापस SHMEM_HUGE_ADVISE;
	अगर (!म_भेद(str, "deny"))
		वापस SHMEM_HUGE_DENY;
	अगर (!म_भेद(str, "force"))
		वापस SHMEM_HUGE_FORCE;
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_SYSFS) || defined(CONFIG_TMPFS)
अटल स्थिर अक्षर *shmem_क्रमmat_huge(पूर्णांक huge)
अणु
	चयन (huge) अणु
	हाल SHMEM_HUGE_NEVER:
		वापस "never";
	हाल SHMEM_HUGE_ALWAYS:
		वापस "always";
	हाल SHMEM_HUGE_WITHIN_SIZE:
		वापस "within_size";
	हाल SHMEM_HUGE_ADVISE:
		वापस "advise";
	हाल SHMEM_HUGE_DENY:
		वापस "deny";
	हाल SHMEM_HUGE_FORCE:
		वापस "force";
	शेष:
		VM_BUG_ON(1);
		वापस "bad_val";
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल अचिन्हित दीर्घ shmem_unused_huge_shrink(काष्ठा shmem_sb_info *sbinfo,
		काष्ठा shrink_control *sc, अचिन्हित दीर्घ nr_to_split)
अणु
	LIST_HEAD(list), *pos, *next;
	LIST_HEAD(to_हटाओ);
	काष्ठा inode *inode;
	काष्ठा shmem_inode_info *info;
	काष्ठा page *page;
	अचिन्हित दीर्घ batch = sc ? sc->nr_to_scan : 128;
	पूर्णांक हटाओd = 0, split = 0;

	अगर (list_empty(&sbinfo->shrinklist))
		वापस SHRINK_STOP;

	spin_lock(&sbinfo->shrinklist_lock);
	list_क्रम_each_safe(pos, next, &sbinfo->shrinklist) अणु
		info = list_entry(pos, काष्ठा shmem_inode_info, shrinklist);

		/* pin the inode */
		inode = igrab(&info->vfs_inode);

		/* inode is about to be evicted */
		अगर (!inode) अणु
			list_del_init(&info->shrinklist);
			हटाओd++;
			जाओ next;
		पूर्ण

		/* Check अगर there's anything to gain */
		अगर (round_up(inode->i_size, PAGE_SIZE) ==
				round_up(inode->i_size, HPAGE_PMD_SIZE)) अणु
			list_move(&info->shrinklist, &to_हटाओ);
			हटाओd++;
			जाओ next;
		पूर्ण

		list_move(&info->shrinklist, &list);
next:
		अगर (!--batch)
			अवरोध;
	पूर्ण
	spin_unlock(&sbinfo->shrinklist_lock);

	list_क्रम_each_safe(pos, next, &to_हटाओ) अणु
		info = list_entry(pos, काष्ठा shmem_inode_info, shrinklist);
		inode = &info->vfs_inode;
		list_del_init(&info->shrinklist);
		iput(inode);
	पूर्ण

	list_क्रम_each_safe(pos, next, &list) अणु
		पूर्णांक ret;

		info = list_entry(pos, काष्ठा shmem_inode_info, shrinklist);
		inode = &info->vfs_inode;

		अगर (nr_to_split && split >= nr_to_split)
			जाओ leave;

		page = find_get_page(inode->i_mapping,
				(inode->i_size & HPAGE_PMD_MASK) >> PAGE_SHIFT);
		अगर (!page)
			जाओ drop;

		/* No huge page at the end of the file: nothing to split */
		अगर (!PageTransHuge(page)) अणु
			put_page(page);
			जाओ drop;
		पूर्ण

		/*
		 * Leave the inode on the list अगर we failed to lock
		 * the page at this समय.
		 *
		 * Waiting क्रम the lock may lead to deadlock in the
		 * reclaim path.
		 */
		अगर (!trylock_page(page)) अणु
			put_page(page);
			जाओ leave;
		पूर्ण

		ret = split_huge_page(page);
		unlock_page(page);
		put_page(page);

		/* If split failed leave the inode on the list */
		अगर (ret)
			जाओ leave;

		split++;
drop:
		list_del_init(&info->shrinklist);
		हटाओd++;
leave:
		iput(inode);
	पूर्ण

	spin_lock(&sbinfo->shrinklist_lock);
	list_splice_tail(&list, &sbinfo->shrinklist);
	sbinfo->shrinklist_len -= हटाओd;
	spin_unlock(&sbinfo->shrinklist_lock);

	वापस split;
पूर्ण

अटल दीर्घ shmem_unused_huge_scan(काष्ठा super_block *sb,
		काष्ठा shrink_control *sc)
अणु
	काष्ठा shmem_sb_info *sbinfo = SHMEM_SB(sb);

	अगर (!READ_ONCE(sbinfo->shrinklist_len))
		वापस SHRINK_STOP;

	वापस shmem_unused_huge_shrink(sbinfo, sc, 0);
पूर्ण

अटल दीर्घ shmem_unused_huge_count(काष्ठा super_block *sb,
		काष्ठा shrink_control *sc)
अणु
	काष्ठा shmem_sb_info *sbinfo = SHMEM_SB(sb);
	वापस READ_ONCE(sbinfo->shrinklist_len);
पूर्ण
#अन्यथा /* !CONFIG_TRANSPARENT_HUGEPAGE */

#घोषणा shmem_huge SHMEM_HUGE_DENY

अटल अचिन्हित दीर्घ shmem_unused_huge_shrink(काष्ठा shmem_sb_info *sbinfo,
		काष्ठा shrink_control *sc, अचिन्हित दीर्घ nr_to_split)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */

अटल अंतरभूत bool is_huge_enabled(काष्ठा shmem_sb_info *sbinfo)
अणु
	अगर (IS_ENABLED(CONFIG_TRANSPARENT_HUGEPAGE) &&
	    (shmem_huge == SHMEM_HUGE_FORCE || sbinfo->huge) &&
	    shmem_huge != SHMEM_HUGE_DENY)
		वापस true;
	वापस false;
पूर्ण

/*
 * Like add_to_page_cache_locked, but error अगर expected item has gone.
 */
अटल पूर्णांक shmem_add_to_page_cache(काष्ठा page *page,
				   काष्ठा address_space *mapping,
				   pgoff_t index, व्योम *expected, gfp_t gfp,
				   काष्ठा mm_काष्ठा *अक्षरge_mm)
अणु
	XA_STATE_ORDER(xas, &mapping->i_pages, index, compound_order(page));
	अचिन्हित दीर्घ i = 0;
	अचिन्हित दीर्घ nr = compound_nr(page);
	पूर्णांक error;

	VM_BUG_ON_PAGE(PageTail(page), page);
	VM_BUG_ON_PAGE(index != round_करोwn(index, nr), page);
	VM_BUG_ON_PAGE(!PageLocked(page), page);
	VM_BUG_ON_PAGE(!PageSwapBacked(page), page);
	VM_BUG_ON(expected && PageTransHuge(page));

	page_ref_add(page, nr);
	page->mapping = mapping;
	page->index = index;

	अगर (!PageSwapCache(page)) अणु
		error = mem_cgroup_अक्षरge(page, अक्षरge_mm, gfp);
		अगर (error) अणु
			अगर (PageTransHuge(page)) अणु
				count_vm_event(THP_खाता_FALLBACK);
				count_vm_event(THP_खाता_FALLBACK_CHARGE);
			पूर्ण
			जाओ error;
		पूर्ण
	पूर्ण
	cgroup_throttle_swaprate(page, gfp);

	करो अणु
		व्योम *entry;
		xas_lock_irq(&xas);
		entry = xas_find_conflict(&xas);
		अगर (entry != expected)
			xas_set_err(&xas, -EEXIST);
		xas_create_range(&xas);
		अगर (xas_error(&xas))
			जाओ unlock;
next:
		xas_store(&xas, page);
		अगर (++i < nr) अणु
			xas_next(&xas);
			जाओ next;
		पूर्ण
		अगर (PageTransHuge(page)) अणु
			count_vm_event(THP_खाता_ALLOC);
			__mod_lruvec_page_state(page, NR_SHMEM_THPS, nr);
		पूर्ण
		mapping->nrpages += nr;
		__mod_lruvec_page_state(page, NR_खाता_PAGES, nr);
		__mod_lruvec_page_state(page, NR_SHMEM, nr);
unlock:
		xas_unlock_irq(&xas);
	पूर्ण जबतक (xas_nomem(&xas, gfp));

	अगर (xas_error(&xas)) अणु
		error = xas_error(&xas);
		जाओ error;
	पूर्ण

	वापस 0;
error:
	page->mapping = शून्य;
	page_ref_sub(page, nr);
	वापस error;
पूर्ण

/*
 * Like delete_from_page_cache, but substitutes swap क्रम page.
 */
अटल व्योम shmem_delete_from_page_cache(काष्ठा page *page, व्योम *radswap)
अणु
	काष्ठा address_space *mapping = page->mapping;
	पूर्णांक error;

	VM_BUG_ON_PAGE(PageCompound(page), page);

	xa_lock_irq(&mapping->i_pages);
	error = shmem_replace_entry(mapping, page->index, page, radswap);
	page->mapping = शून्य;
	mapping->nrpages--;
	__dec_lruvec_page_state(page, NR_खाता_PAGES);
	__dec_lruvec_page_state(page, NR_SHMEM);
	xa_unlock_irq(&mapping->i_pages);
	put_page(page);
	BUG_ON(error);
पूर्ण

/*
 * Remove swap entry from page cache, मुक्त the swap and its page cache.
 */
अटल पूर्णांक shmem_मुक्त_swap(काष्ठा address_space *mapping,
			   pgoff_t index, व्योम *radswap)
अणु
	व्योम *old;

	old = xa_cmpxchg_irq(&mapping->i_pages, index, radswap, शून्य, 0);
	अगर (old != radswap)
		वापस -ENOENT;
	मुक्त_swap_and_cache(radix_to_swp_entry(radswap));
	वापस 0;
पूर्ण

/*
 * Determine (in bytes) how many of the shmem object's pages mapped by the
 * given offsets are swapped out.
 *
 * This is safe to call without i_mutex or the i_pages lock thanks to RCU,
 * as दीर्घ as the inode करोesn't go away and racy results are not a problem.
 */
अचिन्हित दीर्घ shmem_partial_swap_usage(काष्ठा address_space *mapping,
						pgoff_t start, pgoff_t end)
अणु
	XA_STATE(xas, &mapping->i_pages, start);
	काष्ठा page *page;
	अचिन्हित दीर्घ swapped = 0;

	rcu_पढ़ो_lock();
	xas_क्रम_each(&xas, page, end - 1) अणु
		अगर (xas_retry(&xas, page))
			जारी;
		अगर (xa_is_value(page))
			swapped++;

		अगर (need_resched()) अणु
			xas_छोड़ो(&xas);
			cond_resched_rcu();
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस swapped << PAGE_SHIFT;
पूर्ण

/*
 * Determine (in bytes) how many of the shmem object's pages mapped by the
 * given vma is swapped out.
 *
 * This is safe to call without i_mutex or the i_pages lock thanks to RCU,
 * as दीर्घ as the inode करोesn't go away and racy results are not a problem.
 */
अचिन्हित दीर्घ shmem_swap_usage(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा inode *inode = file_inode(vma->vm_file);
	काष्ठा shmem_inode_info *info = SHMEM_I(inode);
	काष्ठा address_space *mapping = inode->i_mapping;
	अचिन्हित दीर्घ swapped;

	/* Be careful as we करोn't hold info->lock */
	swapped = READ_ONCE(info->swapped);

	/*
	 * The easier हालs are when the shmem object has nothing in swap, or
	 * the vma maps it whole. Then we can simply use the stats that we
	 * alपढ़ोy track.
	 */
	अगर (!swapped)
		वापस 0;

	अगर (!vma->vm_pgoff && vma->vm_end - vma->vm_start >= inode->i_size)
		वापस swapped << PAGE_SHIFT;

	/* Here comes the more involved part */
	वापस shmem_partial_swap_usage(mapping,
			linear_page_index(vma, vma->vm_start),
			linear_page_index(vma, vma->vm_end));
पूर्ण

/*
 * SysV IPC SHM_UNLOCK restore Unevictable pages to their evictable lists.
 */
व्योम shmem_unlock_mapping(काष्ठा address_space *mapping)
अणु
	काष्ठा pagevec pvec;
	pgoff_t index = 0;

	pagevec_init(&pvec);
	/*
	 * Minor poपूर्णांक, but we might as well stop अगर someone अन्यथा SHM_LOCKs it.
	 */
	जबतक (!mapping_unevictable(mapping)) अणु
		अगर (!pagevec_lookup(&pvec, mapping, &index))
			अवरोध;
		check_move_unevictable_pages(&pvec);
		pagevec_release(&pvec);
		cond_resched();
	पूर्ण
पूर्ण

/*
 * Check whether a hole-punch or truncation needs to split a huge page,
 * वापसing true अगर no split was required, or the split has been successful.
 *
 * Eviction (or truncation to 0 size) should never need to split a huge page;
 * but in rare हालs might करो so, अगर shmem_unकरो_range() failed to trylock on
 * head, and then succeeded to trylock on tail.
 *
 * A split can only succeed when there are no additional references on the
 * huge page: so the split below relies upon find_get_entries() having stopped
 * when it found a subpage of the huge page, without getting further references.
 */
अटल bool shmem_punch_compound(काष्ठा page *page, pgoff_t start, pgoff_t end)
अणु
	अगर (!PageTransCompound(page))
		वापस true;

	/* Just proceed to delete a huge page wholly within the range punched */
	अगर (PageHead(page) &&
	    page->index >= start && page->index + HPAGE_PMD_NR <= end)
		वापस true;

	/* Try to split huge page, so we can truly punch the hole or truncate */
	वापस split_huge_page(page) >= 0;
पूर्ण

/*
 * Remove range of pages and swap entries from page cache, and मुक्त them.
 * If !unfalloc, truncate or punch hole; अगर unfalloc, unकरो failed fallocate.
 */
अटल व्योम shmem_unकरो_range(काष्ठा inode *inode, loff_t lstart, loff_t lend,
								 bool unfalloc)
अणु
	काष्ठा address_space *mapping = inode->i_mapping;
	काष्ठा shmem_inode_info *info = SHMEM_I(inode);
	pgoff_t start = (lstart + PAGE_SIZE - 1) >> PAGE_SHIFT;
	pgoff_t end = (lend + 1) >> PAGE_SHIFT;
	अचिन्हित पूर्णांक partial_start = lstart & (PAGE_SIZE - 1);
	अचिन्हित पूर्णांक partial_end = (lend + 1) & (PAGE_SIZE - 1);
	काष्ठा pagevec pvec;
	pgoff_t indices[PAGEVEC_SIZE];
	दीर्घ nr_swaps_मुक्तd = 0;
	pgoff_t index;
	पूर्णांक i;

	अगर (lend == -1)
		end = -1;	/* अचिन्हित, so actually very big */

	pagevec_init(&pvec);
	index = start;
	जबतक (index < end && find_lock_entries(mapping, index, end - 1,
			&pvec, indices)) अणु
		क्रम (i = 0; i < pagevec_count(&pvec); i++) अणु
			काष्ठा page *page = pvec.pages[i];

			index = indices[i];

			अगर (xa_is_value(page)) अणु
				अगर (unfalloc)
					जारी;
				nr_swaps_मुक्तd += !shmem_मुक्त_swap(mapping,
								index, page);
				जारी;
			पूर्ण
			index += thp_nr_pages(page) - 1;

			अगर (!unfalloc || !PageUptodate(page))
				truncate_inode_page(mapping, page);
			unlock_page(page);
		पूर्ण
		pagevec_हटाओ_exceptionals(&pvec);
		pagevec_release(&pvec);
		cond_resched();
		index++;
	पूर्ण

	अगर (partial_start) अणु
		काष्ठा page *page = शून्य;
		shmem_getpage(inode, start - 1, &page, SGP_READ);
		अगर (page) अणु
			अचिन्हित पूर्णांक top = PAGE_SIZE;
			अगर (start > end) अणु
				top = partial_end;
				partial_end = 0;
			पूर्ण
			zero_user_segment(page, partial_start, top);
			set_page_dirty(page);
			unlock_page(page);
			put_page(page);
		पूर्ण
	पूर्ण
	अगर (partial_end) अणु
		काष्ठा page *page = शून्य;
		shmem_getpage(inode, end, &page, SGP_READ);
		अगर (page) अणु
			zero_user_segment(page, 0, partial_end);
			set_page_dirty(page);
			unlock_page(page);
			put_page(page);
		पूर्ण
	पूर्ण
	अगर (start >= end)
		वापस;

	index = start;
	जबतक (index < end) अणु
		cond_resched();

		अगर (!find_get_entries(mapping, index, end - 1, &pvec,
				indices)) अणु
			/* If all gone or hole-punch or unfalloc, we're करोne */
			अगर (index == start || end != -1)
				अवरोध;
			/* But अगर truncating, restart to make sure all gone */
			index = start;
			जारी;
		पूर्ण
		क्रम (i = 0; i < pagevec_count(&pvec); i++) अणु
			काष्ठा page *page = pvec.pages[i];

			index = indices[i];
			अगर (xa_is_value(page)) अणु
				अगर (unfalloc)
					जारी;
				अगर (shmem_मुक्त_swap(mapping, index, page)) अणु
					/* Swap was replaced by page: retry */
					index--;
					अवरोध;
				पूर्ण
				nr_swaps_मुक्तd++;
				जारी;
			पूर्ण

			lock_page(page);

			अगर (!unfalloc || !PageUptodate(page)) अणु
				अगर (page_mapping(page) != mapping) अणु
					/* Page was replaced by swap: retry */
					unlock_page(page);
					index--;
					अवरोध;
				पूर्ण
				VM_BUG_ON_PAGE(PageWriteback(page), page);
				अगर (shmem_punch_compound(page, start, end))
					truncate_inode_page(mapping, page);
				अन्यथा अगर (IS_ENABLED(CONFIG_TRANSPARENT_HUGEPAGE)) अणु
					/* Wipe the page and करोn't get stuck */
					clear_highpage(page);
					flush_dcache_page(page);
					set_page_dirty(page);
					अगर (index <
					    round_up(start, HPAGE_PMD_NR))
						start = index + 1;
				पूर्ण
			पूर्ण
			unlock_page(page);
		पूर्ण
		pagevec_हटाओ_exceptionals(&pvec);
		pagevec_release(&pvec);
		index++;
	पूर्ण

	spin_lock_irq(&info->lock);
	info->swapped -= nr_swaps_मुक्तd;
	shmem_recalc_inode(inode);
	spin_unlock_irq(&info->lock);
पूर्ण

व्योम shmem_truncate_range(काष्ठा inode *inode, loff_t lstart, loff_t lend)
अणु
	shmem_unकरो_range(inode, lstart, lend, false);
	inode->i_स_समय = inode->i_mसमय = current_समय(inode);
पूर्ण
EXPORT_SYMBOL_GPL(shmem_truncate_range);

अटल पूर्णांक shmem_getattr(काष्ठा user_namespace *mnt_userns,
			 स्थिर काष्ठा path *path, काष्ठा kstat *stat,
			 u32 request_mask, अचिन्हित पूर्णांक query_flags)
अणु
	काष्ठा inode *inode = path->dentry->d_inode;
	काष्ठा shmem_inode_info *info = SHMEM_I(inode);
	काष्ठा shmem_sb_info *sb_info = SHMEM_SB(inode->i_sb);

	अगर (info->alloced - info->swapped != inode->i_mapping->nrpages) अणु
		spin_lock_irq(&info->lock);
		shmem_recalc_inode(inode);
		spin_unlock_irq(&info->lock);
	पूर्ण
	generic_fillattr(&init_user_ns, inode, stat);

	अगर (is_huge_enabled(sb_info))
		stat->blksize = HPAGE_PMD_SIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक shmem_setattr(काष्ठा user_namespace *mnt_userns,
			 काष्ठा dentry *dentry, काष्ठा iattr *attr)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा shmem_inode_info *info = SHMEM_I(inode);
	काष्ठा shmem_sb_info *sbinfo = SHMEM_SB(inode->i_sb);
	पूर्णांक error;

	error = setattr_prepare(&init_user_ns, dentry, attr);
	अगर (error)
		वापस error;

	अगर (S_ISREG(inode->i_mode) && (attr->ia_valid & ATTR_SIZE)) अणु
		loff_t oldsize = inode->i_size;
		loff_t newsize = attr->ia_size;

		/* रक्षित by i_mutex */
		अगर ((newsize < oldsize && (info->seals & F_SEAL_SHRINK)) ||
		    (newsize > oldsize && (info->seals & F_SEAL_GROW)))
			वापस -EPERM;

		अगर (newsize != oldsize) अणु
			error = shmem_reacct_size(SHMEM_I(inode)->flags,
					oldsize, newsize);
			अगर (error)
				वापस error;
			i_size_ग_लिखो(inode, newsize);
			inode->i_स_समय = inode->i_mसमय = current_समय(inode);
		पूर्ण
		अगर (newsize <= oldsize) अणु
			loff_t holebegin = round_up(newsize, PAGE_SIZE);
			अगर (oldsize > holebegin)
				unmap_mapping_range(inode->i_mapping,
							holebegin, 0, 1);
			अगर (info->alloced)
				shmem_truncate_range(inode,
							newsize, (loff_t)-1);
			/* unmap again to हटाओ racily COWed निजी pages */
			अगर (oldsize > holebegin)
				unmap_mapping_range(inode->i_mapping,
							holebegin, 0, 1);

			/*
			 * Part of the huge page can be beyond i_size: subject
			 * to shrink under memory pressure.
			 */
			अगर (IS_ENABLED(CONFIG_TRANSPARENT_HUGEPAGE)) अणु
				spin_lock(&sbinfo->shrinklist_lock);
				/*
				 * _careful to defend against unlocked access to
				 * ->shrink_list in shmem_unused_huge_shrink()
				 */
				अगर (list_empty_careful(&info->shrinklist)) अणु
					list_add_tail(&info->shrinklist,
							&sbinfo->shrinklist);
					sbinfo->shrinklist_len++;
				पूर्ण
				spin_unlock(&sbinfo->shrinklist_lock);
			पूर्ण
		पूर्ण
	पूर्ण

	setattr_copy(&init_user_ns, inode, attr);
	अगर (attr->ia_valid & ATTR_MODE)
		error = posix_acl_chmod(&init_user_ns, inode, inode->i_mode);
	वापस error;
पूर्ण

अटल व्योम shmem_evict_inode(काष्ठा inode *inode)
अणु
	काष्ठा shmem_inode_info *info = SHMEM_I(inode);
	काष्ठा shmem_sb_info *sbinfo = SHMEM_SB(inode->i_sb);

	अगर (shmem_mapping(inode->i_mapping)) अणु
		shmem_unacct_size(info->flags, inode->i_size);
		inode->i_size = 0;
		shmem_truncate_range(inode, 0, (loff_t)-1);
		अगर (!list_empty(&info->shrinklist)) अणु
			spin_lock(&sbinfo->shrinklist_lock);
			अगर (!list_empty(&info->shrinklist)) अणु
				list_del_init(&info->shrinklist);
				sbinfo->shrinklist_len--;
			पूर्ण
			spin_unlock(&sbinfo->shrinklist_lock);
		पूर्ण
		जबतक (!list_empty(&info->swaplist)) अणु
			/* Wait जबतक shmem_unuse() is scanning this inode... */
			रुको_var_event(&info->stop_eviction,
				       !atomic_पढ़ो(&info->stop_eviction));
			mutex_lock(&shmem_swaplist_mutex);
			/* ...but beware of the race अगर we peeked too early */
			अगर (!atomic_पढ़ो(&info->stop_eviction))
				list_del_init(&info->swaplist);
			mutex_unlock(&shmem_swaplist_mutex);
		पूर्ण
	पूर्ण

	simple_xattrs_मुक्त(&info->xattrs);
	WARN_ON(inode->i_blocks);
	shmem_मुक्त_inode(inode->i_sb);
	clear_inode(inode);
पूर्ण

बाह्य काष्ठा swap_info_काष्ठा *swap_info[];

अटल पूर्णांक shmem_find_swap_entries(काष्ठा address_space *mapping,
				   pgoff_t start, अचिन्हित पूर्णांक nr_entries,
				   काष्ठा page **entries, pgoff_t *indices,
				   अचिन्हित पूर्णांक type, bool frontswap)
अणु
	XA_STATE(xas, &mapping->i_pages, start);
	काष्ठा page *page;
	swp_entry_t entry;
	अचिन्हित पूर्णांक ret = 0;

	अगर (!nr_entries)
		वापस 0;

	rcu_पढ़ो_lock();
	xas_क्रम_each(&xas, page, अच_दीर्घ_उच्च) अणु
		अगर (xas_retry(&xas, page))
			जारी;

		अगर (!xa_is_value(page))
			जारी;

		entry = radix_to_swp_entry(page);
		अगर (swp_type(entry) != type)
			जारी;
		अगर (frontswap &&
		    !frontswap_test(swap_info[type], swp_offset(entry)))
			जारी;

		indices[ret] = xas.xa_index;
		entries[ret] = page;

		अगर (need_resched()) अणु
			xas_छोड़ो(&xas);
			cond_resched_rcu();
		पूर्ण
		अगर (++ret == nr_entries)
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

/*
 * Move the swapped pages क्रम an inode to page cache. Returns the count
 * of pages swapped in, or the error in हाल of failure.
 */
अटल पूर्णांक shmem_unuse_swap_entries(काष्ठा inode *inode, काष्ठा pagevec pvec,
				    pgoff_t *indices)
अणु
	पूर्णांक i = 0;
	पूर्णांक ret = 0;
	पूर्णांक error = 0;
	काष्ठा address_space *mapping = inode->i_mapping;

	क्रम (i = 0; i < pvec.nr; i++) अणु
		काष्ठा page *page = pvec.pages[i];

		अगर (!xa_is_value(page))
			जारी;
		error = shmem_swapin_page(inode, indices[i],
					  &page, SGP_CACHE,
					  mapping_gfp_mask(mapping),
					  शून्य, शून्य);
		अगर (error == 0) अणु
			unlock_page(page);
			put_page(page);
			ret++;
		पूर्ण
		अगर (error == -ENOMEM)
			अवरोध;
		error = 0;
	पूर्ण
	वापस error ? error : ret;
पूर्ण

/*
 * If swap found in inode, मुक्त it and move page from swapcache to filecache.
 */
अटल पूर्णांक shmem_unuse_inode(काष्ठा inode *inode, अचिन्हित पूर्णांक type,
			     bool frontswap, अचिन्हित दीर्घ *fs_pages_to_unuse)
अणु
	काष्ठा address_space *mapping = inode->i_mapping;
	pgoff_t start = 0;
	काष्ठा pagevec pvec;
	pgoff_t indices[PAGEVEC_SIZE];
	bool frontswap_partial = (frontswap && *fs_pages_to_unuse > 0);
	पूर्णांक ret = 0;

	pagevec_init(&pvec);
	करो अणु
		अचिन्हित पूर्णांक nr_entries = PAGEVEC_SIZE;

		अगर (frontswap_partial && *fs_pages_to_unuse < PAGEVEC_SIZE)
			nr_entries = *fs_pages_to_unuse;

		pvec.nr = shmem_find_swap_entries(mapping, start, nr_entries,
						  pvec.pages, indices,
						  type, frontswap);
		अगर (pvec.nr == 0) अणु
			ret = 0;
			अवरोध;
		पूर्ण

		ret = shmem_unuse_swap_entries(inode, pvec, indices);
		अगर (ret < 0)
			अवरोध;

		अगर (frontswap_partial) अणु
			*fs_pages_to_unuse -= ret;
			अगर (*fs_pages_to_unuse == 0) अणु
				ret = FRONTSWAP_PAGES_UNUSED;
				अवरोध;
			पूर्ण
		पूर्ण

		start = indices[pvec.nr - 1];
	पूर्ण जबतक (true);

	वापस ret;
पूर्ण

/*
 * Read all the shared memory data that resides in the swap
 * device 'type' back पूर्णांकo memory, so the swap device can be
 * unused.
 */
पूर्णांक shmem_unuse(अचिन्हित पूर्णांक type, bool frontswap,
		अचिन्हित दीर्घ *fs_pages_to_unuse)
अणु
	काष्ठा shmem_inode_info *info, *next;
	पूर्णांक error = 0;

	अगर (list_empty(&shmem_swaplist))
		वापस 0;

	mutex_lock(&shmem_swaplist_mutex);
	list_क्रम_each_entry_safe(info, next, &shmem_swaplist, swaplist) अणु
		अगर (!info->swapped) अणु
			list_del_init(&info->swaplist);
			जारी;
		पूर्ण
		/*
		 * Drop the swaplist mutex जबतक searching the inode क्रम swap;
		 * but beक्रमe करोing so, make sure shmem_evict_inode() will not
		 * हटाओ placeholder inode from swaplist, nor let it be मुक्तd
		 * (igrab() would protect from unlink, but not from unmount).
		 */
		atomic_inc(&info->stop_eviction);
		mutex_unlock(&shmem_swaplist_mutex);

		error = shmem_unuse_inode(&info->vfs_inode, type, frontswap,
					  fs_pages_to_unuse);
		cond_resched();

		mutex_lock(&shmem_swaplist_mutex);
		next = list_next_entry(info, swaplist);
		अगर (!info->swapped)
			list_del_init(&info->swaplist);
		अगर (atomic_dec_and_test(&info->stop_eviction))
			wake_up_var(&info->stop_eviction);
		अगर (error)
			अवरोध;
	पूर्ण
	mutex_unlock(&shmem_swaplist_mutex);

	वापस error;
पूर्ण

/*
 * Move the page from the page cache to the swap cache.
 */
अटल पूर्णांक shmem_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा shmem_inode_info *info;
	काष्ठा address_space *mapping;
	काष्ठा inode *inode;
	swp_entry_t swap;
	pgoff_t index;

	VM_BUG_ON_PAGE(PageCompound(page), page);
	BUG_ON(!PageLocked(page));
	mapping = page->mapping;
	index = page->index;
	inode = mapping->host;
	info = SHMEM_I(inode);
	अगर (info->flags & VM_LOCKED)
		जाओ redirty;
	अगर (!total_swap_pages)
		जाओ redirty;

	/*
	 * Our capabilities prevent regular ग_लिखोback or sync from ever calling
	 * shmem_ग_लिखोpage; but a stacking fileप्रणाली might use ->ग_लिखोpage of
	 * its underlying fileप्रणाली, in which हाल पंचांगpfs should ग_लिखो out to
	 * swap only in response to memory pressure, and not क्रम the ग_लिखोback
	 * thपढ़ोs or sync.
	 */
	अगर (!wbc->क्रम_reclaim) अणु
		WARN_ON_ONCE(1);	/* Still happens? Tell us about it! */
		जाओ redirty;
	पूर्ण

	/*
	 * This is somewhat ridiculous, but without plumbing a SWAP_MAP_FALLOC
	 * value पूर्णांकo swapfile.c, the only way we can correctly account क्रम a
	 * fallocated page arriving here is now to initialize it and ग_लिखो it.
	 *
	 * That's okay क्रम a page alपढ़ोy fallocated earlier, but अगर we have
	 * not yet completed the fallocation, then (a) we want to keep track
	 * of this page in हाल we have to unकरो it, and (b) it may not be a
	 * good idea to जारी anyway, once we're pushing पूर्णांकo swap.  So
	 * reactivate the page, and let shmem_fallocate() quit when too many.
	 */
	अगर (!PageUptodate(page)) अणु
		अगर (inode->i_निजी) अणु
			काष्ठा shmem_falloc *shmem_falloc;
			spin_lock(&inode->i_lock);
			shmem_falloc = inode->i_निजी;
			अगर (shmem_falloc &&
			    !shmem_falloc->रुकोq &&
			    index >= shmem_falloc->start &&
			    index < shmem_falloc->next)
				shmem_falloc->nr_unswapped++;
			अन्यथा
				shmem_falloc = शून्य;
			spin_unlock(&inode->i_lock);
			अगर (shmem_falloc)
				जाओ redirty;
		पूर्ण
		clear_highpage(page);
		flush_dcache_page(page);
		SetPageUptodate(page);
	पूर्ण

	swap = get_swap_page(page);
	अगर (!swap.val)
		जाओ redirty;

	/*
	 * Add inode to shmem_unuse()'s list of swapped-out inodes,
	 * अगर it's not alपढ़ोy there.  Do it now beक्रमe the page is
	 * moved to swap cache, when its pagelock no दीर्घer protects
	 * the inode from eviction.  But करोn't unlock the mutex until
	 * we've incremented swapped, because shmem_unuse_inode() will
	 * prune a !swapped inode from the swaplist under this mutex.
	 */
	mutex_lock(&shmem_swaplist_mutex);
	अगर (list_empty(&info->swaplist))
		list_add(&info->swaplist, &shmem_swaplist);

	अगर (add_to_swap_cache(page, swap,
			__GFP_HIGH | __GFP_NOMEMALLOC | __GFP_NOWARN,
			शून्य) == 0) अणु
		spin_lock_irq(&info->lock);
		shmem_recalc_inode(inode);
		info->swapped++;
		spin_unlock_irq(&info->lock);

		swap_shmem_alloc(swap);
		shmem_delete_from_page_cache(page, swp_to_radix_entry(swap));

		mutex_unlock(&shmem_swaplist_mutex);
		BUG_ON(page_mapped(page));
		swap_ग_लिखोpage(page, wbc);
		वापस 0;
	पूर्ण

	mutex_unlock(&shmem_swaplist_mutex);
	put_swap_page(page, swap);
redirty:
	set_page_dirty(page);
	अगर (wbc->क्रम_reclaim)
		वापस AOP_WRITEPAGE_ACTIVATE;	/* Return with page locked */
	unlock_page(page);
	वापस 0;
पूर्ण

#अगर defined(CONFIG_NUMA) && defined(CONFIG_TMPFS)
अटल व्योम shmem_show_mpol(काष्ठा seq_file *seq, काष्ठा mempolicy *mpol)
अणु
	अक्षर buffer[64];

	अगर (!mpol || mpol->mode == MPOL_DEFAULT)
		वापस;		/* show nothing */

	mpol_to_str(buffer, माप(buffer), mpol);

	seq_म_लिखो(seq, ",mpol=%s", buffer);
पूर्ण

अटल काष्ठा mempolicy *shmem_get_sbmpol(काष्ठा shmem_sb_info *sbinfo)
अणु
	काष्ठा mempolicy *mpol = शून्य;
	अगर (sbinfo->mpol) अणु
		spin_lock(&sbinfo->stat_lock);	/* prevent replace/use races */
		mpol = sbinfo->mpol;
		mpol_get(mpol);
		spin_unlock(&sbinfo->stat_lock);
	पूर्ण
	वापस mpol;
पूर्ण
#अन्यथा /* !CONFIG_NUMA || !CONFIG_TMPFS */
अटल अंतरभूत व्योम shmem_show_mpol(काष्ठा seq_file *seq, काष्ठा mempolicy *mpol)
अणु
पूर्ण
अटल अंतरभूत काष्ठा mempolicy *shmem_get_sbmpol(काष्ठा shmem_sb_info *sbinfo)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_NUMA && CONFIG_TMPFS */
#अगर_अघोषित CONFIG_NUMA
#घोषणा vm_policy vm_निजी_data
#पूर्ण_अगर

अटल व्योम shmem_pseuकरो_vma_init(काष्ठा vm_area_काष्ठा *vma,
		काष्ठा shmem_inode_info *info, pgoff_t index)
अणु
	/* Create a pseuकरो vma that just contains the policy */
	vma_init(vma, शून्य);
	/* Bias पूर्णांकerleave by inode number to distribute better across nodes */
	vma->vm_pgoff = index + info->vfs_inode.i_ino;
	vma->vm_policy = mpol_shared_policy_lookup(&info->policy, index);
पूर्ण

अटल व्योम shmem_pseuकरो_vma_destroy(काष्ठा vm_area_काष्ठा *vma)
अणु
	/* Drop reference taken by mpol_shared_policy_lookup() */
	mpol_cond_put(vma->vm_policy);
पूर्ण

अटल काष्ठा page *shmem_swapin(swp_entry_t swap, gfp_t gfp,
			काष्ठा shmem_inode_info *info, pgoff_t index)
अणु
	काष्ठा vm_area_काष्ठा pvma;
	काष्ठा page *page;
	काष्ठा vm_fault vmf = अणु
		.vma = &pvma,
	पूर्ण;

	shmem_pseuकरो_vma_init(&pvma, info, index);
	page = swap_cluster_पढ़ोahead(swap, gfp, &vmf);
	shmem_pseuकरो_vma_destroy(&pvma);

	वापस page;
पूर्ण

/*
 * Make sure huge_gfp is always more limited than limit_gfp.
 * Some of the flags set permissions, जबतक others set limitations.
 */
अटल gfp_t limit_gfp_mask(gfp_t huge_gfp, gfp_t limit_gfp)
अणु
	gfp_t allowflags = __GFP_IO | __GFP_FS | __GFP_RECLAIM;
	gfp_t denyflags = __GFP_NOWARN | __GFP_NORETRY;
	gfp_t zoneflags = limit_gfp & GFP_ZONEMASK;
	gfp_t result = huge_gfp & ~(allowflags | GFP_ZONEMASK);

	/* Allow allocations only from the originally specअगरied zones. */
	result |= zoneflags;

	/*
	 * Minimize the result gfp by taking the जोड़ with the deny flags,
	 * and the पूर्णांकersection of the allow flags.
	 */
	result |= (limit_gfp & denyflags);
	result |= (huge_gfp & limit_gfp) & allowflags;

	वापस result;
पूर्ण

अटल काष्ठा page *shmem_alloc_hugepage(gfp_t gfp,
		काष्ठा shmem_inode_info *info, pgoff_t index)
अणु
	काष्ठा vm_area_काष्ठा pvma;
	काष्ठा address_space *mapping = info->vfs_inode.i_mapping;
	pgoff_t hindex;
	काष्ठा page *page;

	hindex = round_करोwn(index, HPAGE_PMD_NR);
	अगर (xa_find(&mapping->i_pages, &hindex, hindex + HPAGE_PMD_NR - 1,
								XA_PRESENT))
		वापस शून्य;

	shmem_pseuकरो_vma_init(&pvma, info, hindex);
	page = alloc_pages_vma(gfp, HPAGE_PMD_ORDER, &pvma, 0, numa_node_id(),
			       true);
	shmem_pseuकरो_vma_destroy(&pvma);
	अगर (page)
		prep_transhuge_page(page);
	अन्यथा
		count_vm_event(THP_खाता_FALLBACK);
	वापस page;
पूर्ण

अटल काष्ठा page *shmem_alloc_page(gfp_t gfp,
			काष्ठा shmem_inode_info *info, pgoff_t index)
अणु
	काष्ठा vm_area_काष्ठा pvma;
	काष्ठा page *page;

	shmem_pseuकरो_vma_init(&pvma, info, index);
	page = alloc_page_vma(gfp, &pvma, 0);
	shmem_pseuकरो_vma_destroy(&pvma);

	वापस page;
पूर्ण

अटल काष्ठा page *shmem_alloc_and_acct_page(gfp_t gfp,
		काष्ठा inode *inode,
		pgoff_t index, bool huge)
अणु
	काष्ठा shmem_inode_info *info = SHMEM_I(inode);
	काष्ठा page *page;
	पूर्णांक nr;
	पूर्णांक err = -ENOSPC;

	अगर (!IS_ENABLED(CONFIG_TRANSPARENT_HUGEPAGE))
		huge = false;
	nr = huge ? HPAGE_PMD_NR : 1;

	अगर (!shmem_inode_acct_block(inode, nr))
		जाओ failed;

	अगर (huge)
		page = shmem_alloc_hugepage(gfp, info, index);
	अन्यथा
		page = shmem_alloc_page(gfp, info, index);
	अगर (page) अणु
		__SetPageLocked(page);
		__SetPageSwapBacked(page);
		वापस page;
	पूर्ण

	err = -ENOMEM;
	shmem_inode_unacct_blocks(inode, nr);
failed:
	वापस ERR_PTR(err);
पूर्ण

/*
 * When a page is moved from swapcache to shmem filecache (either by the
 * usual swapin of shmem_getpage_gfp(), or by the less common swapoff of
 * shmem_unuse_inode()), it may have been पढ़ो in earlier from swap, in
 * ignorance of the mapping it beदीर्घs to.  If that mapping has special
 * स्थिरraपूर्णांकs (like the gma500 GEM driver, which requires RAM below 4GB),
 * we may need to copy to a suitable page beक्रमe moving to filecache.
 *
 * In a future release, this may well be extended to respect cpuset and
 * NUMA mempolicy, and applied also to anonymous pages in करो_swap_page();
 * but क्रम now it is a simple matter of zone.
 */
अटल bool shmem_should_replace_page(काष्ठा page *page, gfp_t gfp)
अणु
	वापस page_zonक्रमागत(page) > gfp_zone(gfp);
पूर्ण

अटल पूर्णांक shmem_replace_page(काष्ठा page **pagep, gfp_t gfp,
				काष्ठा shmem_inode_info *info, pgoff_t index)
अणु
	काष्ठा page *oldpage, *newpage;
	काष्ठा address_space *swap_mapping;
	swp_entry_t entry;
	pgoff_t swap_index;
	पूर्णांक error;

	oldpage = *pagep;
	entry.val = page_निजी(oldpage);
	swap_index = swp_offset(entry);
	swap_mapping = page_mapping(oldpage);

	/*
	 * We have arrived here because our zones are स्थिरrained, so करोn't
	 * limit chance of success by further cpuset and node स्थिरraपूर्णांकs.
	 */
	gfp &= ~GFP_CONSTRAINT_MASK;
	newpage = shmem_alloc_page(gfp, info, index);
	अगर (!newpage)
		वापस -ENOMEM;

	get_page(newpage);
	copy_highpage(newpage, oldpage);
	flush_dcache_page(newpage);

	__SetPageLocked(newpage);
	__SetPageSwapBacked(newpage);
	SetPageUptodate(newpage);
	set_page_निजी(newpage, entry.val);
	SetPageSwapCache(newpage);

	/*
	 * Our caller will very soon move newpage out of swapcache, but it's
	 * a nice clean पूर्णांकerface क्रम us to replace oldpage by newpage there.
	 */
	xa_lock_irq(&swap_mapping->i_pages);
	error = shmem_replace_entry(swap_mapping, swap_index, oldpage, newpage);
	अगर (!error) अणु
		mem_cgroup_migrate(oldpage, newpage);
		__inc_lruvec_page_state(newpage, NR_खाता_PAGES);
		__dec_lruvec_page_state(oldpage, NR_खाता_PAGES);
	पूर्ण
	xa_unlock_irq(&swap_mapping->i_pages);

	अगर (unlikely(error)) अणु
		/*
		 * Is this possible?  I think not, now that our callers check
		 * both PageSwapCache and page_निजी after getting page lock;
		 * but be defensive.  Reverse old to newpage क्रम clear and मुक्त.
		 */
		oldpage = newpage;
	पूर्ण अन्यथा अणु
		lru_cache_add(newpage);
		*pagep = newpage;
	पूर्ण

	ClearPageSwapCache(oldpage);
	set_page_निजी(oldpage, 0);

	unlock_page(oldpage);
	put_page(oldpage);
	put_page(oldpage);
	वापस error;
पूर्ण

/*
 * Swap in the page poपूर्णांकed to by *pagep.
 * Caller has to make sure that *pagep contains a valid swapped page.
 * Returns 0 and the page in pagep अगर success. On failure, वापसs the
 * error code and शून्य in *pagep.
 */
अटल पूर्णांक shmem_swapin_page(काष्ठा inode *inode, pgoff_t index,
			     काष्ठा page **pagep, क्रमागत sgp_type sgp,
			     gfp_t gfp, काष्ठा vm_area_काष्ठा *vma,
			     vm_fault_t *fault_type)
अणु
	काष्ठा address_space *mapping = inode->i_mapping;
	काष्ठा shmem_inode_info *info = SHMEM_I(inode);
	काष्ठा mm_काष्ठा *अक्षरge_mm = vma ? vma->vm_mm : current->mm;
	काष्ठा page *page;
	swp_entry_t swap;
	पूर्णांक error;

	VM_BUG_ON(!*pagep || !xa_is_value(*pagep));
	swap = radix_to_swp_entry(*pagep);
	*pagep = शून्य;

	/* Look it up and पढ़ो it in.. */
	page = lookup_swap_cache(swap, शून्य, 0);
	अगर (!page) अणु
		/* Or update major stats only when swapin succeeds?? */
		अगर (fault_type) अणु
			*fault_type |= VM_FAULT_MAJOR;
			count_vm_event(PGMAJFAULT);
			count_memcg_event_mm(अक्षरge_mm, PGMAJFAULT);
		पूर्ण
		/* Here we actually start the io */
		page = shmem_swapin(swap, gfp, info, index);
		अगर (!page) अणु
			error = -ENOMEM;
			जाओ failed;
		पूर्ण
	पूर्ण

	/* We have to करो this with page locked to prevent races */
	lock_page(page);
	अगर (!PageSwapCache(page) || page_निजी(page) != swap.val ||
	    !shmem_confirm_swap(mapping, index, swap)) अणु
		error = -EEXIST;
		जाओ unlock;
	पूर्ण
	अगर (!PageUptodate(page)) अणु
		error = -EIO;
		जाओ failed;
	पूर्ण
	रुको_on_page_ग_लिखोback(page);

	/*
	 * Some architectures may have to restore extra metadata to the
	 * physical page after पढ़ोing from swap.
	 */
	arch_swap_restore(swap, page);

	अगर (shmem_should_replace_page(page, gfp)) अणु
		error = shmem_replace_page(&page, gfp, info, index);
		अगर (error)
			जाओ failed;
	पूर्ण

	error = shmem_add_to_page_cache(page, mapping, index,
					swp_to_radix_entry(swap), gfp,
					अक्षरge_mm);
	अगर (error)
		जाओ failed;

	spin_lock_irq(&info->lock);
	info->swapped--;
	shmem_recalc_inode(inode);
	spin_unlock_irq(&info->lock);

	अगर (sgp == SGP_WRITE)
		mark_page_accessed(page);

	delete_from_swap_cache(page);
	set_page_dirty(page);
	swap_मुक्त(swap);

	*pagep = page;
	वापस 0;
failed:
	अगर (!shmem_confirm_swap(mapping, index, swap))
		error = -EEXIST;
unlock:
	अगर (page) अणु
		unlock_page(page);
		put_page(page);
	पूर्ण

	वापस error;
पूर्ण

/*
 * shmem_getpage_gfp - find page in cache, or get from swap, or allocate
 *
 * If we allocate a new one we करो not mark it dirty. That's up to the
 * vm. If we swap it in we mark it dirty since we also मुक्त the swap
 * entry since a page cannot live in both the swap and page cache.
 *
 * vmf and fault_type are only supplied by shmem_fault:
 * otherwise they are शून्य.
 */
अटल पूर्णांक shmem_getpage_gfp(काष्ठा inode *inode, pgoff_t index,
	काष्ठा page **pagep, क्रमागत sgp_type sgp, gfp_t gfp,
	काष्ठा vm_area_काष्ठा *vma, काष्ठा vm_fault *vmf,
			vm_fault_t *fault_type)
अणु
	काष्ठा address_space *mapping = inode->i_mapping;
	काष्ठा shmem_inode_info *info = SHMEM_I(inode);
	काष्ठा shmem_sb_info *sbinfo;
	काष्ठा mm_काष्ठा *अक्षरge_mm;
	काष्ठा page *page;
	क्रमागत sgp_type sgp_huge = sgp;
	pgoff_t hindex = index;
	gfp_t huge_gfp;
	पूर्णांक error;
	पूर्णांक once = 0;
	पूर्णांक alloced = 0;

	अगर (index > (MAX_LFS_खाताSIZE >> PAGE_SHIFT))
		वापस -EFBIG;
	अगर (sgp == SGP_NOHUGE || sgp == SGP_HUGE)
		sgp = SGP_CACHE;
repeat:
	अगर (sgp <= SGP_CACHE &&
	    ((loff_t)index << PAGE_SHIFT) >= i_size_पढ़ो(inode)) अणु
		वापस -EINVAL;
	पूर्ण

	sbinfo = SHMEM_SB(inode->i_sb);
	अक्षरge_mm = vma ? vma->vm_mm : current->mm;

	page = pagecache_get_page(mapping, index,
					FGP_ENTRY | FGP_HEAD | FGP_LOCK, 0);
	अगर (xa_is_value(page)) अणु
		error = shmem_swapin_page(inode, index, &page,
					  sgp, gfp, vma, fault_type);
		अगर (error == -EEXIST)
			जाओ repeat;

		*pagep = page;
		वापस error;
	पूर्ण

	अगर (page)
		hindex = page->index;
	अगर (page && sgp == SGP_WRITE)
		mark_page_accessed(page);

	/* fallocated page? */
	अगर (page && !PageUptodate(page)) अणु
		अगर (sgp != SGP_READ)
			जाओ clear;
		unlock_page(page);
		put_page(page);
		page = शून्य;
		hindex = index;
	पूर्ण
	अगर (page || sgp == SGP_READ)
		जाओ out;

	/*
	 * Fast cache lookup did not find it:
	 * bring it back from swap or allocate.
	 */

	अगर (vma && userfaultfd_missing(vma)) अणु
		*fault_type = handle_userfault(vmf, VM_UFFD_MISSING);
		वापस 0;
	पूर्ण

	/* shmem_symlink() */
	अगर (!shmem_mapping(mapping))
		जाओ alloc_nohuge;
	अगर (shmem_huge == SHMEM_HUGE_DENY || sgp_huge == SGP_NOHUGE)
		जाओ alloc_nohuge;
	अगर (shmem_huge == SHMEM_HUGE_FORCE)
		जाओ alloc_huge;
	चयन (sbinfo->huge) अणु
	हाल SHMEM_HUGE_NEVER:
		जाओ alloc_nohuge;
	हाल SHMEM_HUGE_WITHIN_SIZE: अणु
		loff_t i_size;
		pgoff_t off;

		off = round_up(index, HPAGE_PMD_NR);
		i_size = round_up(i_size_पढ़ो(inode), PAGE_SIZE);
		अगर (i_size >= HPAGE_PMD_SIZE &&
		    i_size >> PAGE_SHIFT >= off)
			जाओ alloc_huge;

		fallthrough;
	पूर्ण
	हाल SHMEM_HUGE_ADVISE:
		अगर (sgp_huge == SGP_HUGE)
			जाओ alloc_huge;
		/* TODO: implement fadvise() hपूर्णांकs */
		जाओ alloc_nohuge;
	पूर्ण

alloc_huge:
	huge_gfp = vma_thp_gfp_mask(vma);
	huge_gfp = limit_gfp_mask(huge_gfp, gfp);
	page = shmem_alloc_and_acct_page(huge_gfp, inode, index, true);
	अगर (IS_ERR(page)) अणु
alloc_nohuge:
		page = shmem_alloc_and_acct_page(gfp, inode,
						 index, false);
	पूर्ण
	अगर (IS_ERR(page)) अणु
		पूर्णांक retry = 5;

		error = PTR_ERR(page);
		page = शून्य;
		अगर (error != -ENOSPC)
			जाओ unlock;
		/*
		 * Try to reclaim some space by splitting a huge page
		 * beyond i_size on the fileप्रणाली.
		 */
		जबतक (retry--) अणु
			पूर्णांक ret;

			ret = shmem_unused_huge_shrink(sbinfo, शून्य, 1);
			अगर (ret == SHRINK_STOP)
				अवरोध;
			अगर (ret)
				जाओ alloc_nohuge;
		पूर्ण
		जाओ unlock;
	पूर्ण

	अगर (PageTransHuge(page))
		hindex = round_करोwn(index, HPAGE_PMD_NR);
	अन्यथा
		hindex = index;

	अगर (sgp == SGP_WRITE)
		__SetPageReferenced(page);

	error = shmem_add_to_page_cache(page, mapping, hindex,
					शून्य, gfp & GFP_RECLAIM_MASK,
					अक्षरge_mm);
	अगर (error)
		जाओ unacct;
	lru_cache_add(page);

	spin_lock_irq(&info->lock);
	info->alloced += compound_nr(page);
	inode->i_blocks += BLOCKS_PER_PAGE << compound_order(page);
	shmem_recalc_inode(inode);
	spin_unlock_irq(&info->lock);
	alloced = true;

	अगर (PageTransHuge(page) &&
	    DIV_ROUND_UP(i_size_पढ़ो(inode), PAGE_SIZE) <
			hindex + HPAGE_PMD_NR - 1) अणु
		/*
		 * Part of the huge page is beyond i_size: subject
		 * to shrink under memory pressure.
		 */
		spin_lock(&sbinfo->shrinklist_lock);
		/*
		 * _careful to defend against unlocked access to
		 * ->shrink_list in shmem_unused_huge_shrink()
		 */
		अगर (list_empty_careful(&info->shrinklist)) अणु
			list_add_tail(&info->shrinklist,
				      &sbinfo->shrinklist);
			sbinfo->shrinklist_len++;
		पूर्ण
		spin_unlock(&sbinfo->shrinklist_lock);
	पूर्ण

	/*
	 * Let SGP_FALLOC use the SGP_WRITE optimization on a new page.
	 */
	अगर (sgp == SGP_FALLOC)
		sgp = SGP_WRITE;
clear:
	/*
	 * Let SGP_WRITE caller clear ends अगर ग_लिखो करोes not fill page;
	 * but SGP_FALLOC on a page fallocated earlier must initialize
	 * it now, lest unकरो on failure cancel our earlier guarantee.
	 */
	अगर (sgp != SGP_WRITE && !PageUptodate(page)) अणु
		पूर्णांक i;

		क्रम (i = 0; i < compound_nr(page); i++) अणु
			clear_highpage(page + i);
			flush_dcache_page(page + i);
		पूर्ण
		SetPageUptodate(page);
	पूर्ण

	/* Perhaps the file has been truncated since we checked */
	अगर (sgp <= SGP_CACHE &&
	    ((loff_t)index << PAGE_SHIFT) >= i_size_पढ़ो(inode)) अणु
		अगर (alloced) अणु
			ClearPageDirty(page);
			delete_from_page_cache(page);
			spin_lock_irq(&info->lock);
			shmem_recalc_inode(inode);
			spin_unlock_irq(&info->lock);
		पूर्ण
		error = -EINVAL;
		जाओ unlock;
	पूर्ण
out:
	*pagep = page + index - hindex;
	वापस 0;

	/*
	 * Error recovery.
	 */
unacct:
	shmem_inode_unacct_blocks(inode, compound_nr(page));

	अगर (PageTransHuge(page)) अणु
		unlock_page(page);
		put_page(page);
		जाओ alloc_nohuge;
	पूर्ण
unlock:
	अगर (page) अणु
		unlock_page(page);
		put_page(page);
	पूर्ण
	अगर (error == -ENOSPC && !once++) अणु
		spin_lock_irq(&info->lock);
		shmem_recalc_inode(inode);
		spin_unlock_irq(&info->lock);
		जाओ repeat;
	पूर्ण
	अगर (error == -EEXIST)
		जाओ repeat;
	वापस error;
पूर्ण

/*
 * This is like स्वतःहटाओ_wake_function, but it हटाओs the रुको queue
 * entry unconditionally - even अगर something अन्यथा had alपढ़ोy woken the
 * target.
 */
अटल पूर्णांक synchronous_wake_function(रुको_queue_entry_t *रुको, अचिन्हित mode, पूर्णांक sync, व्योम *key)
अणु
	पूर्णांक ret = शेष_wake_function(रुको, mode, sync, key);
	list_del_init(&रुको->entry);
	वापस ret;
पूर्ण

अटल vm_fault_t shmem_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा inode *inode = file_inode(vma->vm_file);
	gfp_t gfp = mapping_gfp_mask(inode->i_mapping);
	क्रमागत sgp_type sgp;
	पूर्णांक err;
	vm_fault_t ret = VM_FAULT_LOCKED;

	/*
	 * Trinity finds that probing a hole which पंचांगpfs is punching can
	 * prevent the hole-punch from ever completing: which in turn
	 * locks ग_लिखोrs out with its hold on i_mutex.  So refrain from
	 * faulting pages पूर्णांकo the hole जबतक it's being punched.  Although
	 * shmem_unकरो_range() करोes हटाओ the additions, it may be unable to
	 * keep up, as each new page needs its own unmap_mapping_range() call,
	 * and the i_mmap tree grows ever slower to scan अगर new vmas are added.
	 *
	 * It करोes not matter अगर we someबार reach this check just beक्रमe the
	 * hole-punch begins, so that one fault then races with the punch:
	 * we just need to make racing faults a rare हाल.
	 *
	 * The implementation below would be much simpler अगर we just used a
	 * standard mutex or completion: but we cannot take i_mutex in fault,
	 * and bloating every shmem inode क्रम this unlikely हाल would be sad.
	 */
	अगर (unlikely(inode->i_निजी)) अणु
		काष्ठा shmem_falloc *shmem_falloc;

		spin_lock(&inode->i_lock);
		shmem_falloc = inode->i_निजी;
		अगर (shmem_falloc &&
		    shmem_falloc->रुकोq &&
		    vmf->pgoff >= shmem_falloc->start &&
		    vmf->pgoff < shmem_falloc->next) अणु
			काष्ठा file *fpin;
			रुको_queue_head_t *shmem_falloc_रुकोq;
			DEFINE_WAIT_FUNC(shmem_fault_रुको, synchronous_wake_function);

			ret = VM_FAULT_NOPAGE;
			fpin = maybe_unlock_mmap_क्रम_io(vmf, शून्य);
			अगर (fpin)
				ret = VM_FAULT_RETRY;

			shmem_falloc_रुकोq = shmem_falloc->रुकोq;
			prepare_to_रुको(shmem_falloc_रुकोq, &shmem_fault_रुको,
					TASK_UNINTERRUPTIBLE);
			spin_unlock(&inode->i_lock);
			schedule();

			/*
			 * shmem_falloc_रुकोq poपूर्णांकs पूर्णांकo the shmem_fallocate()
			 * stack of the hole-punching task: shmem_falloc_रुकोq
			 * is usually invalid by the समय we reach here, but
			 * finish_रुको() करोes not dereference it in that हाल;
			 * though i_lock needed lest racing with wake_up_all().
			 */
			spin_lock(&inode->i_lock);
			finish_रुको(shmem_falloc_रुकोq, &shmem_fault_रुको);
			spin_unlock(&inode->i_lock);

			अगर (fpin)
				fput(fpin);
			वापस ret;
		पूर्ण
		spin_unlock(&inode->i_lock);
	पूर्ण

	sgp = SGP_CACHE;

	अगर ((vma->vm_flags & VM_NOHUGEPAGE) ||
	    test_bit(MMF_DISABLE_THP, &vma->vm_mm->flags))
		sgp = SGP_NOHUGE;
	अन्यथा अगर (vma->vm_flags & VM_HUGEPAGE)
		sgp = SGP_HUGE;

	err = shmem_getpage_gfp(inode, vmf->pgoff, &vmf->page, sgp,
				  gfp, vma, vmf, &ret);
	अगर (err)
		वापस vmf_error(err);
	वापस ret;
पूर्ण

अचिन्हित दीर्घ shmem_get_unmapped_area(काष्ठा file *file,
				      अचिन्हित दीर्घ uaddr, अचिन्हित दीर्घ len,
				      अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags)
अणु
	अचिन्हित दीर्घ (*get_area)(काष्ठा file *,
		अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित दीर्घ);
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ inflated_len;
	अचिन्हित दीर्घ inflated_addr;
	अचिन्हित दीर्घ inflated_offset;

	अगर (len > TASK_SIZE)
		वापस -ENOMEM;

	get_area = current->mm->get_unmapped_area;
	addr = get_area(file, uaddr, len, pgoff, flags);

	अगर (!IS_ENABLED(CONFIG_TRANSPARENT_HUGEPAGE))
		वापस addr;
	अगर (IS_ERR_VALUE(addr))
		वापस addr;
	अगर (addr & ~PAGE_MASK)
		वापस addr;
	अगर (addr > TASK_SIZE - len)
		वापस addr;

	अगर (shmem_huge == SHMEM_HUGE_DENY)
		वापस addr;
	अगर (len < HPAGE_PMD_SIZE)
		वापस addr;
	अगर (flags & MAP_FIXED)
		वापस addr;
	/*
	 * Our priority is to support MAP_SHARED mapped hugely;
	 * and support MAP_PRIVATE mapped hugely too, until it is COWed.
	 * But अगर caller specअगरied an address hपूर्णांक and we allocated area there
	 * successfully, respect that as beक्रमe.
	 */
	अगर (uaddr == addr)
		वापस addr;

	अगर (shmem_huge != SHMEM_HUGE_FORCE) अणु
		काष्ठा super_block *sb;

		अगर (file) अणु
			VM_BUG_ON(file->f_op != &shmem_file_operations);
			sb = file_inode(file)->i_sb;
		पूर्ण अन्यथा अणु
			/*
			 * Called directly from mm/mmap.c, or drivers/अक्षर/mem.c
			 * क्रम "/dev/zero", to create a shared anonymous object.
			 */
			अगर (IS_ERR(shm_mnt))
				वापस addr;
			sb = shm_mnt->mnt_sb;
		पूर्ण
		अगर (SHMEM_SB(sb)->huge == SHMEM_HUGE_NEVER)
			वापस addr;
	पूर्ण

	offset = (pgoff << PAGE_SHIFT) & (HPAGE_PMD_SIZE-1);
	अगर (offset && offset + len < 2 * HPAGE_PMD_SIZE)
		वापस addr;
	अगर ((addr & (HPAGE_PMD_SIZE-1)) == offset)
		वापस addr;

	inflated_len = len + HPAGE_PMD_SIZE - PAGE_SIZE;
	अगर (inflated_len > TASK_SIZE)
		वापस addr;
	अगर (inflated_len < len)
		वापस addr;

	inflated_addr = get_area(शून्य, uaddr, inflated_len, 0, flags);
	अगर (IS_ERR_VALUE(inflated_addr))
		वापस addr;
	अगर (inflated_addr & ~PAGE_MASK)
		वापस addr;

	inflated_offset = inflated_addr & (HPAGE_PMD_SIZE-1);
	inflated_addr += offset - inflated_offset;
	अगर (inflated_offset > offset)
		inflated_addr += HPAGE_PMD_SIZE;

	अगर (inflated_addr > TASK_SIZE - len)
		वापस addr;
	वापस inflated_addr;
पूर्ण

#अगर_घोषित CONFIG_NUMA
अटल पूर्णांक shmem_set_policy(काष्ठा vm_area_काष्ठा *vma, काष्ठा mempolicy *mpol)
अणु
	काष्ठा inode *inode = file_inode(vma->vm_file);
	वापस mpol_set_shared_policy(&SHMEM_I(inode)->policy, vma, mpol);
पूर्ण

अटल काष्ठा mempolicy *shmem_get_policy(काष्ठा vm_area_काष्ठा *vma,
					  अचिन्हित दीर्घ addr)
अणु
	काष्ठा inode *inode = file_inode(vma->vm_file);
	pgoff_t index;

	index = ((addr - vma->vm_start) >> PAGE_SHIFT) + vma->vm_pgoff;
	वापस mpol_shared_policy_lookup(&SHMEM_I(inode)->policy, index);
पूर्ण
#पूर्ण_अगर

पूर्णांक shmem_lock(काष्ठा file *file, पूर्णांक lock, काष्ठा user_काष्ठा *user)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा shmem_inode_info *info = SHMEM_I(inode);
	पूर्णांक retval = -ENOMEM;

	/*
	 * What serializes the accesses to info->flags?
	 * ipc_lock_object() when called from shmctl_करो_lock(),
	 * no serialization needed when called from shm_destroy().
	 */
	अगर (lock && !(info->flags & VM_LOCKED)) अणु
		अगर (!user_shm_lock(inode->i_size, user))
			जाओ out_nomem;
		info->flags |= VM_LOCKED;
		mapping_set_unevictable(file->f_mapping);
	पूर्ण
	अगर (!lock && (info->flags & VM_LOCKED) && user) अणु
		user_shm_unlock(inode->i_size, user);
		info->flags &= ~VM_LOCKED;
		mapping_clear_unevictable(file->f_mapping);
	पूर्ण
	retval = 0;

out_nomem:
	वापस retval;
पूर्ण

अटल पूर्णांक shmem_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा shmem_inode_info *info = SHMEM_I(file_inode(file));
	पूर्णांक ret;

	ret = seal_check_future_ग_लिखो(info->seals, vma);
	अगर (ret)
		वापस ret;

	/* arm64 - allow memory tagging on RAM-based files */
	vma->vm_flags |= VM_MTE_ALLOWED;

	file_accessed(file);
	vma->vm_ops = &shmem_vm_ops;
	अगर (IS_ENABLED(CONFIG_TRANSPARENT_HUGEPAGE) &&
			((vma->vm_start + ~HPAGE_PMD_MASK) & HPAGE_PMD_MASK) <
			(vma->vm_end & HPAGE_PMD_MASK)) अणु
		khugepaged_enter(vma, vma->vm_flags);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा inode *shmem_get_inode(काष्ठा super_block *sb, स्थिर काष्ठा inode *dir,
				     umode_t mode, dev_t dev, अचिन्हित दीर्घ flags)
अणु
	काष्ठा inode *inode;
	काष्ठा shmem_inode_info *info;
	काष्ठा shmem_sb_info *sbinfo = SHMEM_SB(sb);
	ino_t ino;

	अगर (shmem_reserve_inode(sb, &ino))
		वापस शून्य;

	inode = new_inode(sb);
	अगर (inode) अणु
		inode->i_ino = ino;
		inode_init_owner(&init_user_ns, inode, dir, mode);
		inode->i_blocks = 0;
		inode->i_aसमय = inode->i_mसमय = inode->i_स_समय = current_समय(inode);
		inode->i_generation = pअक्रमom_u32();
		info = SHMEM_I(inode);
		स_रखो(info, 0, (अक्षर *)inode - (अक्षर *)info);
		spin_lock_init(&info->lock);
		atomic_set(&info->stop_eviction, 0);
		info->seals = F_SEAL_SEAL;
		info->flags = flags & VM_NORESERVE;
		INIT_LIST_HEAD(&info->shrinklist);
		INIT_LIST_HEAD(&info->swaplist);
		simple_xattrs_init(&info->xattrs);
		cache_no_acl(inode);

		चयन (mode & S_IFMT) अणु
		शेष:
			inode->i_op = &shmem_special_inode_operations;
			init_special_inode(inode, mode, dev);
			अवरोध;
		हाल S_IFREG:
			inode->i_mapping->a_ops = &shmem_aops;
			inode->i_op = &shmem_inode_operations;
			inode->i_fop = &shmem_file_operations;
			mpol_shared_policy_init(&info->policy,
						 shmem_get_sbmpol(sbinfo));
			अवरोध;
		हाल S_IFसूची:
			inc_nlink(inode);
			/* Some things misbehave अगर size == 0 on a directory */
			inode->i_size = 2 * BOGO_सूचीENT_SIZE;
			inode->i_op = &shmem_dir_inode_operations;
			inode->i_fop = &simple_dir_operations;
			अवरोध;
		हाल S_IFLNK:
			/*
			 * Must not load anything in the rbtree,
			 * mpol_मुक्त_shared_policy will not be called.
			 */
			mpol_shared_policy_init(&info->policy, शून्य);
			अवरोध;
		पूर्ण

		lockdep_annotate_inode_mutex_key(inode);
	पूर्ण अन्यथा
		shmem_मुक्त_inode(sb);
	वापस inode;
पूर्ण

अटल पूर्णांक shmem_mfill_atomic_pte(काष्ठा mm_काष्ठा *dst_mm,
				  pmd_t *dst_pmd,
				  काष्ठा vm_area_काष्ठा *dst_vma,
				  अचिन्हित दीर्घ dst_addr,
				  अचिन्हित दीर्घ src_addr,
				  bool zeropage,
				  काष्ठा page **pagep)
अणु
	काष्ठा inode *inode = file_inode(dst_vma->vm_file);
	काष्ठा shmem_inode_info *info = SHMEM_I(inode);
	काष्ठा address_space *mapping = inode->i_mapping;
	gfp_t gfp = mapping_gfp_mask(mapping);
	pgoff_t pgoff = linear_page_index(dst_vma, dst_addr);
	spinlock_t *ptl;
	व्योम *page_kaddr;
	काष्ठा page *page;
	pte_t _dst_pte, *dst_pte;
	पूर्णांक ret;
	pgoff_t offset, max_off;

	ret = -ENOMEM;
	अगर (!shmem_inode_acct_block(inode, 1)) अणु
		/*
		 * We may have got a page, वापसed -ENOENT triggering a retry,
		 * and now we find ourselves with -ENOMEM. Release the page, to
		 * aव्योम a BUG_ON in our caller.
		 */
		अगर (unlikely(*pagep)) अणु
			put_page(*pagep);
			*pagep = शून्य;
		पूर्ण
		जाओ out;
	पूर्ण

	अगर (!*pagep) अणु
		page = shmem_alloc_page(gfp, info, pgoff);
		अगर (!page)
			जाओ out_unacct_blocks;

		अगर (!zeropage) अणु	/* mcopy_atomic */
			page_kaddr = kmap_atomic(page);
			ret = copy_from_user(page_kaddr,
					     (स्थिर व्योम __user *)src_addr,
					     PAGE_SIZE);
			kunmap_atomic(page_kaddr);

			/* fallback to copy_from_user outside mmap_lock */
			अगर (unlikely(ret)) अणु
				*pagep = page;
				shmem_inode_unacct_blocks(inode, 1);
				/* करोn't मुक्त the page */
				वापस -ENOENT;
			पूर्ण
		पूर्ण अन्यथा अणु		/* mfill_zeropage_atomic */
			clear_highpage(page);
		पूर्ण
	पूर्ण अन्यथा अणु
		page = *pagep;
		*pagep = शून्य;
	पूर्ण

	VM_BUG_ON(PageLocked(page) || PageSwapBacked(page));
	__SetPageLocked(page);
	__SetPageSwapBacked(page);
	__SetPageUptodate(page);

	ret = -EFAULT;
	offset = linear_page_index(dst_vma, dst_addr);
	max_off = DIV_ROUND_UP(i_size_पढ़ो(inode), PAGE_SIZE);
	अगर (unlikely(offset >= max_off))
		जाओ out_release;

	ret = shmem_add_to_page_cache(page, mapping, pgoff, शून्य,
				      gfp & GFP_RECLAIM_MASK, dst_mm);
	अगर (ret)
		जाओ out_release;

	_dst_pte = mk_pte(page, dst_vma->vm_page_prot);
	अगर (dst_vma->vm_flags & VM_WRITE)
		_dst_pte = pte_mkग_लिखो(pte_सूची_गढ़ोty(_dst_pte));
	अन्यथा अणु
		/*
		 * We करोn't set the pte dirty अगर the vma has no
		 * VM_WRITE permission, so mark the page dirty or it
		 * could be मुक्तd from under us. We could करो it
		 * unconditionally beक्रमe unlock_page(), but करोing it
		 * only अगर VM_WRITE is not set is faster.
		 */
		set_page_dirty(page);
	पूर्ण

	dst_pte = pte_offset_map_lock(dst_mm, dst_pmd, dst_addr, &ptl);

	ret = -EFAULT;
	max_off = DIV_ROUND_UP(i_size_पढ़ो(inode), PAGE_SIZE);
	अगर (unlikely(offset >= max_off))
		जाओ out_release_unlock;

	ret = -EEXIST;
	अगर (!pte_none(*dst_pte))
		जाओ out_release_unlock;

	lru_cache_add(page);

	spin_lock_irq(&info->lock);
	info->alloced++;
	inode->i_blocks += BLOCKS_PER_PAGE;
	shmem_recalc_inode(inode);
	spin_unlock_irq(&info->lock);

	inc_mm_counter(dst_mm, mm_counter_file(page));
	page_add_file_rmap(page, false);
	set_pte_at(dst_mm, dst_addr, dst_pte, _dst_pte);

	/* No need to invalidate - it was non-present beक्रमe */
	update_mmu_cache(dst_vma, dst_addr, dst_pte);
	pte_unmap_unlock(dst_pte, ptl);
	unlock_page(page);
	ret = 0;
out:
	वापस ret;
out_release_unlock:
	pte_unmap_unlock(dst_pte, ptl);
	ClearPageDirty(page);
	delete_from_page_cache(page);
out_release:
	unlock_page(page);
	put_page(page);
out_unacct_blocks:
	shmem_inode_unacct_blocks(inode, 1);
	जाओ out;
पूर्ण

पूर्णांक shmem_mcopy_atomic_pte(काष्ठा mm_काष्ठा *dst_mm,
			   pmd_t *dst_pmd,
			   काष्ठा vm_area_काष्ठा *dst_vma,
			   अचिन्हित दीर्घ dst_addr,
			   अचिन्हित दीर्घ src_addr,
			   काष्ठा page **pagep)
अणु
	वापस shmem_mfill_atomic_pte(dst_mm, dst_pmd, dst_vma,
				      dst_addr, src_addr, false, pagep);
पूर्ण

पूर्णांक shmem_mfill_zeropage_pte(काष्ठा mm_काष्ठा *dst_mm,
			     pmd_t *dst_pmd,
			     काष्ठा vm_area_काष्ठा *dst_vma,
			     अचिन्हित दीर्घ dst_addr)
अणु
	काष्ठा page *page = शून्य;

	वापस shmem_mfill_atomic_pte(dst_mm, dst_pmd, dst_vma,
				      dst_addr, 0, true, &page);
पूर्ण

#अगर_घोषित CONFIG_TMPFS
अटल स्थिर काष्ठा inode_operations shmem_symlink_inode_operations;
अटल स्थिर काष्ठा inode_operations shmem_लघु_symlink_operations;

#अगर_घोषित CONFIG_TMPFS_XATTR
अटल पूर्णांक shmem_initxattrs(काष्ठा inode *, स्थिर काष्ठा xattr *, व्योम *);
#अन्यथा
#घोषणा shmem_initxattrs शून्य
#पूर्ण_अगर

अटल पूर्णांक
shmem_ग_लिखो_begin(काष्ठा file *file, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित flags,
			काष्ठा page **pagep, व्योम **fsdata)
अणु
	काष्ठा inode *inode = mapping->host;
	काष्ठा shmem_inode_info *info = SHMEM_I(inode);
	pgoff_t index = pos >> PAGE_SHIFT;

	/* i_mutex is held by caller */
	अगर (unlikely(info->seals & (F_SEAL_GROW |
				   F_SEAL_WRITE | F_SEAL_FUTURE_WRITE))) अणु
		अगर (info->seals & (F_SEAL_WRITE | F_SEAL_FUTURE_WRITE))
			वापस -EPERM;
		अगर ((info->seals & F_SEAL_GROW) && pos + len > inode->i_size)
			वापस -EPERM;
	पूर्ण

	वापस shmem_getpage(inode, index, pagep, SGP_WRITE);
पूर्ण

अटल पूर्णांक
shmem_ग_लिखो_end(काष्ठा file *file, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित copied,
			काष्ठा page *page, व्योम *fsdata)
अणु
	काष्ठा inode *inode = mapping->host;

	अगर (pos + copied > inode->i_size)
		i_size_ग_लिखो(inode, pos + copied);

	अगर (!PageUptodate(page)) अणु
		काष्ठा page *head = compound_head(page);
		अगर (PageTransCompound(page)) अणु
			पूर्णांक i;

			क्रम (i = 0; i < HPAGE_PMD_NR; i++) अणु
				अगर (head + i == page)
					जारी;
				clear_highpage(head + i);
				flush_dcache_page(head + i);
			पूर्ण
		पूर्ण
		अगर (copied < PAGE_SIZE) अणु
			अचिन्हित from = pos & (PAGE_SIZE - 1);
			zero_user_segments(page, 0, from,
					from + copied, PAGE_SIZE);
		पूर्ण
		SetPageUptodate(head);
	पूर्ण
	set_page_dirty(page);
	unlock_page(page);
	put_page(page);

	वापस copied;
पूर्ण

अटल sमाप_प्रकार shmem_file_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा address_space *mapping = inode->i_mapping;
	pgoff_t index;
	अचिन्हित दीर्घ offset;
	क्रमागत sgp_type sgp = SGP_READ;
	पूर्णांक error = 0;
	sमाप_प्रकार retval = 0;
	loff_t *ppos = &iocb->ki_pos;

	/*
	 * Might this पढ़ो be क्रम a stacking fileप्रणाली?  Then when पढ़ोing
	 * holes of a sparse file, we actually need to allocate those pages,
	 * and even mark them dirty, so it cannot exceed the max_blocks limit.
	 */
	अगर (!iter_is_iovec(to))
		sgp = SGP_CACHE;

	index = *ppos >> PAGE_SHIFT;
	offset = *ppos & ~PAGE_MASK;

	क्रम (;;) अणु
		काष्ठा page *page = शून्य;
		pgoff_t end_index;
		अचिन्हित दीर्घ nr, ret;
		loff_t i_size = i_size_पढ़ो(inode);

		end_index = i_size >> PAGE_SHIFT;
		अगर (index > end_index)
			अवरोध;
		अगर (index == end_index) अणु
			nr = i_size & ~PAGE_MASK;
			अगर (nr <= offset)
				अवरोध;
		पूर्ण

		error = shmem_getpage(inode, index, &page, sgp);
		अगर (error) अणु
			अगर (error == -EINVAL)
				error = 0;
			अवरोध;
		पूर्ण
		अगर (page) अणु
			अगर (sgp == SGP_CACHE)
				set_page_dirty(page);
			unlock_page(page);
		पूर्ण

		/*
		 * We must evaluate after, since पढ़ोs (unlike ग_लिखोs)
		 * are called without i_mutex protection against truncate
		 */
		nr = PAGE_SIZE;
		i_size = i_size_पढ़ो(inode);
		end_index = i_size >> PAGE_SHIFT;
		अगर (index == end_index) अणु
			nr = i_size & ~PAGE_MASK;
			अगर (nr <= offset) अणु
				अगर (page)
					put_page(page);
				अवरोध;
			पूर्ण
		पूर्ण
		nr -= offset;

		अगर (page) अणु
			/*
			 * If users can be writing to this page using arbitrary
			 * भव addresses, take care about potential aliasing
			 * beक्रमe पढ़ोing the page on the kernel side.
			 */
			अगर (mapping_writably_mapped(mapping))
				flush_dcache_page(page);
			/*
			 * Mark the page accessed अगर we पढ़ो the beginning.
			 */
			अगर (!offset)
				mark_page_accessed(page);
		पूर्ण अन्यथा अणु
			page = ZERO_PAGE(0);
			get_page(page);
		पूर्ण

		/*
		 * Ok, we have the page, and it's up-to-date, so
		 * now we can copy it to user space...
		 */
		ret = copy_page_to_iter(page, offset, nr, to);
		retval += ret;
		offset += ret;
		index += offset >> PAGE_SHIFT;
		offset &= ~PAGE_MASK;

		put_page(page);
		अगर (!iov_iter_count(to))
			अवरोध;
		अगर (ret < nr) अणु
			error = -EFAULT;
			अवरोध;
		पूर्ण
		cond_resched();
	पूर्ण

	*ppos = ((loff_t) index << PAGE_SHIFT) + offset;
	file_accessed(file);
	वापस retval ? retval : error;
पूर्ण

अटल loff_t shmem_file_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	काष्ठा address_space *mapping = file->f_mapping;
	काष्ठा inode *inode = mapping->host;

	अगर (whence != SEEK_DATA && whence != SEEK_HOLE)
		वापस generic_file_llseek_size(file, offset, whence,
					MAX_LFS_खाताSIZE, i_size_पढ़ो(inode));
	अगर (offset < 0)
		वापस -ENXIO;

	inode_lock(inode);
	/* We're holding i_mutex so we can access i_size directly */
	offset = mapping_seek_hole_data(mapping, offset, inode->i_size, whence);
	अगर (offset >= 0)
		offset = vfs_setpos(file, offset, MAX_LFS_खाताSIZE);
	inode_unlock(inode);
	वापस offset;
पूर्ण

अटल दीर्घ shmem_fallocate(काष्ठा file *file, पूर्णांक mode, loff_t offset,
							 loff_t len)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा shmem_sb_info *sbinfo = SHMEM_SB(inode->i_sb);
	काष्ठा shmem_inode_info *info = SHMEM_I(inode);
	काष्ठा shmem_falloc shmem_falloc;
	pgoff_t start, index, end;
	पूर्णांक error;

	अगर (mode & ~(FALLOC_FL_KEEP_SIZE | FALLOC_FL_PUNCH_HOLE))
		वापस -EOPNOTSUPP;

	inode_lock(inode);

	अगर (mode & FALLOC_FL_PUNCH_HOLE) अणु
		काष्ठा address_space *mapping = file->f_mapping;
		loff_t unmap_start = round_up(offset, PAGE_SIZE);
		loff_t unmap_end = round_करोwn(offset + len, PAGE_SIZE) - 1;
		DECLARE_WAIT_QUEUE_HEAD_ONSTACK(shmem_falloc_रुकोq);

		/* रक्षित by i_mutex */
		अगर (info->seals & (F_SEAL_WRITE | F_SEAL_FUTURE_WRITE)) अणु
			error = -EPERM;
			जाओ out;
		पूर्ण

		shmem_falloc.रुकोq = &shmem_falloc_रुकोq;
		shmem_falloc.start = (u64)unmap_start >> PAGE_SHIFT;
		shmem_falloc.next = (unmap_end + 1) >> PAGE_SHIFT;
		spin_lock(&inode->i_lock);
		inode->i_निजी = &shmem_falloc;
		spin_unlock(&inode->i_lock);

		अगर ((u64)unmap_end > (u64)unmap_start)
			unmap_mapping_range(mapping, unmap_start,
					    1 + unmap_end - unmap_start, 0);
		shmem_truncate_range(inode, offset, offset + len - 1);
		/* No need to unmap again: hole-punching leaves COWed pages */

		spin_lock(&inode->i_lock);
		inode->i_निजी = शून्य;
		wake_up_all(&shmem_falloc_रुकोq);
		WARN_ON_ONCE(!list_empty(&shmem_falloc_रुकोq.head));
		spin_unlock(&inode->i_lock);
		error = 0;
		जाओ out;
	पूर्ण

	/* We need to check rlimit even when FALLOC_FL_KEEP_SIZE */
	error = inode_newsize_ok(inode, offset + len);
	अगर (error)
		जाओ out;

	अगर ((info->seals & F_SEAL_GROW) && offset + len > inode->i_size) अणु
		error = -EPERM;
		जाओ out;
	पूर्ण

	start = offset >> PAGE_SHIFT;
	end = (offset + len + PAGE_SIZE - 1) >> PAGE_SHIFT;
	/* Try to aव्योम a swapstorm अगर len is impossible to satisfy */
	अगर (sbinfo->max_blocks && end - start > sbinfo->max_blocks) अणु
		error = -ENOSPC;
		जाओ out;
	पूर्ण

	shmem_falloc.रुकोq = शून्य;
	shmem_falloc.start = start;
	shmem_falloc.next  = start;
	shmem_falloc.nr_falloced = 0;
	shmem_falloc.nr_unswapped = 0;
	spin_lock(&inode->i_lock);
	inode->i_निजी = &shmem_falloc;
	spin_unlock(&inode->i_lock);

	क्रम (index = start; index < end; index++) अणु
		काष्ठा page *page;

		/*
		 * Good, the fallocate(2) manpage permits EINTR: we may have
		 * been पूर्णांकerrupted because we are using up too much memory.
		 */
		अगर (संकेत_pending(current))
			error = -EINTR;
		अन्यथा अगर (shmem_falloc.nr_unswapped > shmem_falloc.nr_falloced)
			error = -ENOMEM;
		अन्यथा
			error = shmem_getpage(inode, index, &page, SGP_FALLOC);
		अगर (error) अणु
			/* Remove the !PageUptodate pages we added */
			अगर (index > start) अणु
				shmem_unकरो_range(inode,
				    (loff_t)start << PAGE_SHIFT,
				    ((loff_t)index << PAGE_SHIFT) - 1, true);
			पूर्ण
			जाओ unकरोne;
		पूर्ण

		/*
		 * Inक्रमm shmem_ग_लिखोpage() how far we have reached.
		 * No need क्रम lock or barrier: we have the page lock.
		 */
		shmem_falloc.next++;
		अगर (!PageUptodate(page))
			shmem_falloc.nr_falloced++;

		/*
		 * If !PageUptodate, leave it that way so that मुक्तable pages
		 * can be recognized अगर we need to rollback on error later.
		 * But set_page_dirty so that memory pressure will swap rather
		 * than मुक्त the pages we are allocating (and SGP_CACHE pages
		 * might still be clean: we now need to mark those dirty too).
		 */
		set_page_dirty(page);
		unlock_page(page);
		put_page(page);
		cond_resched();
	पूर्ण

	अगर (!(mode & FALLOC_FL_KEEP_SIZE) && offset + len > inode->i_size)
		i_size_ग_लिखो(inode, offset + len);
	inode->i_स_समय = current_समय(inode);
unकरोne:
	spin_lock(&inode->i_lock);
	inode->i_निजी = शून्य;
	spin_unlock(&inode->i_lock);
out:
	inode_unlock(inode);
	वापस error;
पूर्ण

अटल पूर्णांक shmem_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा shmem_sb_info *sbinfo = SHMEM_SB(dentry->d_sb);

	buf->f_type = TMPFS_MAGIC;
	buf->f_bsize = PAGE_SIZE;
	buf->f_namelen = NAME_MAX;
	अगर (sbinfo->max_blocks) अणु
		buf->f_blocks = sbinfo->max_blocks;
		buf->f_bavail =
		buf->f_bमुक्त  = sbinfo->max_blocks -
				percpu_counter_sum(&sbinfo->used_blocks);
	पूर्ण
	अगर (sbinfo->max_inodes) अणु
		buf->f_files = sbinfo->max_inodes;
		buf->f_fमुक्त = sbinfo->मुक्त_inodes;
	पूर्ण
	/* अन्यथा leave those fields 0 like simple_statfs */

	buf->f_fsid = uuid_to_fsid(dentry->d_sb->s_uuid.b);

	वापस 0;
पूर्ण

/*
 * File creation. Allocate an inode, and we're करोne..
 */
अटल पूर्णांक
shmem_mknod(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
	    काष्ठा dentry *dentry, umode_t mode, dev_t dev)
अणु
	काष्ठा inode *inode;
	पूर्णांक error = -ENOSPC;

	inode = shmem_get_inode(dir->i_sb, dir, mode, dev, VM_NORESERVE);
	अगर (inode) अणु
		error = simple_acl_create(dir, inode);
		अगर (error)
			जाओ out_iput;
		error = security_inode_init_security(inode, dir,
						     &dentry->d_name,
						     shmem_initxattrs, शून्य);
		अगर (error && error != -EOPNOTSUPP)
			जाओ out_iput;

		error = 0;
		dir->i_size += BOGO_सूचीENT_SIZE;
		dir->i_स_समय = dir->i_mसमय = current_समय(dir);
		d_instantiate(dentry, inode);
		dget(dentry); /* Extra count - pin the dentry in core */
	पूर्ण
	वापस error;
out_iput:
	iput(inode);
	वापस error;
पूर्ण

अटल पूर्णांक
shmem_क्षणिक_ख(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
	      काष्ठा dentry *dentry, umode_t mode)
अणु
	काष्ठा inode *inode;
	पूर्णांक error = -ENOSPC;

	inode = shmem_get_inode(dir->i_sb, dir, mode, 0, VM_NORESERVE);
	अगर (inode) अणु
		error = security_inode_init_security(inode, dir,
						     शून्य,
						     shmem_initxattrs, शून्य);
		अगर (error && error != -EOPNOTSUPP)
			जाओ out_iput;
		error = simple_acl_create(dir, inode);
		अगर (error)
			जाओ out_iput;
		d_क्षणिक_ख(dentry, inode);
	पूर्ण
	वापस error;
out_iput:
	iput(inode);
	वापस error;
पूर्ण

अटल पूर्णांक shmem_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		       काष्ठा dentry *dentry, umode_t mode)
अणु
	पूर्णांक error;

	अगर ((error = shmem_mknod(&init_user_ns, dir, dentry,
				 mode | S_IFसूची, 0)))
		वापस error;
	inc_nlink(dir);
	वापस 0;
पूर्ण

अटल पूर्णांक shmem_create(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			काष्ठा dentry *dentry, umode_t mode, bool excl)
अणु
	वापस shmem_mknod(&init_user_ns, dir, dentry, mode | S_IFREG, 0);
पूर्ण

/*
 * Link a file..
 */
अटल पूर्णांक shmem_link(काष्ठा dentry *old_dentry, काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(old_dentry);
	पूर्णांक ret = 0;

	/*
	 * No ordinary (disk based) fileप्रणाली counts links as inodes;
	 * but each new link needs a new dentry, pinning lowmem, and
	 * पंचांगpfs dentries cannot be pruned until they are unlinked.
	 * But अगर an O_TMPखाता file is linked पूर्णांकo the पंचांगpfs, the
	 * first link must skip that, to get the accounting right.
	 */
	अगर (inode->i_nlink) अणु
		ret = shmem_reserve_inode(inode->i_sb, शून्य);
		अगर (ret)
			जाओ out;
	पूर्ण

	dir->i_size += BOGO_सूचीENT_SIZE;
	inode->i_स_समय = dir->i_स_समय = dir->i_mसमय = current_समय(inode);
	inc_nlink(inode);
	ihold(inode);	/* New dentry reference */
	dget(dentry);		/* Extra pinning count क्रम the created dentry */
	d_instantiate(dentry, inode);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक shmem_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(dentry);

	अगर (inode->i_nlink > 1 && !S_ISसूची(inode->i_mode))
		shmem_मुक्त_inode(inode->i_sb);

	dir->i_size -= BOGO_सूचीENT_SIZE;
	inode->i_स_समय = dir->i_स_समय = dir->i_mसमय = current_समय(inode);
	drop_nlink(inode);
	dput(dentry);	/* Unकरो the count from "create" - this करोes all the work */
	वापस 0;
पूर्ण

अटल पूर्णांक shmem_सूची_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	अगर (!simple_empty(dentry))
		वापस -ENOTEMPTY;

	drop_nlink(d_inode(dentry));
	drop_nlink(dir);
	वापस shmem_unlink(dir, dentry);
पूर्ण

अटल पूर्णांक shmem_exchange(काष्ठा inode *old_dir, काष्ठा dentry *old_dentry, काष्ठा inode *new_dir, काष्ठा dentry *new_dentry)
अणु
	bool old_is_dir = d_is_dir(old_dentry);
	bool new_is_dir = d_is_dir(new_dentry);

	अगर (old_dir != new_dir && old_is_dir != new_is_dir) अणु
		अगर (old_is_dir) अणु
			drop_nlink(old_dir);
			inc_nlink(new_dir);
		पूर्ण अन्यथा अणु
			drop_nlink(new_dir);
			inc_nlink(old_dir);
		पूर्ण
	पूर्ण
	old_dir->i_स_समय = old_dir->i_mसमय =
	new_dir->i_स_समय = new_dir->i_mसमय =
	d_inode(old_dentry)->i_स_समय =
	d_inode(new_dentry)->i_स_समय = current_समय(old_dir);

	वापस 0;
पूर्ण

अटल पूर्णांक shmem_whiteout(काष्ठा user_namespace *mnt_userns,
			  काष्ठा inode *old_dir, काष्ठा dentry *old_dentry)
अणु
	काष्ठा dentry *whiteout;
	पूर्णांक error;

	whiteout = d_alloc(old_dentry->d_parent, &old_dentry->d_name);
	अगर (!whiteout)
		वापस -ENOMEM;

	error = shmem_mknod(&init_user_ns, old_dir, whiteout,
			    S_IFCHR | WHITEOUT_MODE, WHITEOUT_DEV);
	dput(whiteout);
	अगर (error)
		वापस error;

	/*
	 * Cheat and hash the whiteout जबतक the old dentry is still in
	 * place, instead of playing games with FS_RENAME_DOES_D_MOVE.
	 *
	 * d_lookup() will consistently find one of them at this poपूर्णांक,
	 * not sure which one, but that isn't even important.
	 */
	d_rehash(whiteout);
	वापस 0;
पूर्ण

/*
 * The VFS layer alपढ़ोy करोes all the dentry stuff क्रम नाम,
 * we just have to decrement the usage count क्रम the target अगर
 * it exists so that the VFS layer correctly मुक्त's it when it
 * माला_लो overwritten.
 */
अटल पूर्णांक shmem_नाम2(काष्ठा user_namespace *mnt_userns,
			 काष्ठा inode *old_dir, काष्ठा dentry *old_dentry,
			 काष्ठा inode *new_dir, काष्ठा dentry *new_dentry,
			 अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *inode = d_inode(old_dentry);
	पूर्णांक they_are_dirs = S_ISसूची(inode->i_mode);

	अगर (flags & ~(RENAME_NOREPLACE | RENAME_EXCHANGE | RENAME_WHITEOUT))
		वापस -EINVAL;

	अगर (flags & RENAME_EXCHANGE)
		वापस shmem_exchange(old_dir, old_dentry, new_dir, new_dentry);

	अगर (!simple_empty(new_dentry))
		वापस -ENOTEMPTY;

	अगर (flags & RENAME_WHITEOUT) अणु
		पूर्णांक error;

		error = shmem_whiteout(&init_user_ns, old_dir, old_dentry);
		अगर (error)
			वापस error;
	पूर्ण

	अगर (d_really_is_positive(new_dentry)) अणु
		(व्योम) shmem_unlink(new_dir, new_dentry);
		अगर (they_are_dirs) अणु
			drop_nlink(d_inode(new_dentry));
			drop_nlink(old_dir);
		पूर्ण
	पूर्ण अन्यथा अगर (they_are_dirs) अणु
		drop_nlink(old_dir);
		inc_nlink(new_dir);
	पूर्ण

	old_dir->i_size -= BOGO_सूचीENT_SIZE;
	new_dir->i_size += BOGO_सूचीENT_SIZE;
	old_dir->i_स_समय = old_dir->i_mसमय =
	new_dir->i_स_समय = new_dir->i_mसमय =
	inode->i_स_समय = current_समय(old_dir);
	वापस 0;
पूर्ण

अटल पूर्णांक shmem_symlink(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			 काष्ठा dentry *dentry, स्थिर अक्षर *symname)
अणु
	पूर्णांक error;
	पूर्णांक len;
	काष्ठा inode *inode;
	काष्ठा page *page;

	len = म_माप(symname) + 1;
	अगर (len > PAGE_SIZE)
		वापस -ENAMETOOLONG;

	inode = shmem_get_inode(dir->i_sb, dir, S_IFLNK | 0777, 0,
				VM_NORESERVE);
	अगर (!inode)
		वापस -ENOSPC;

	error = security_inode_init_security(inode, dir, &dentry->d_name,
					     shmem_initxattrs, शून्य);
	अगर (error && error != -EOPNOTSUPP) अणु
		iput(inode);
		वापस error;
	पूर्ण

	inode->i_size = len-1;
	अगर (len <= SHORT_SYMLINK_LEN) अणु
		inode->i_link = kmemdup(symname, len, GFP_KERNEL);
		अगर (!inode->i_link) अणु
			iput(inode);
			वापस -ENOMEM;
		पूर्ण
		inode->i_op = &shmem_लघु_symlink_operations;
	पूर्ण अन्यथा अणु
		inode_nohighmem(inode);
		error = shmem_getpage(inode, 0, &page, SGP_WRITE);
		अगर (error) अणु
			iput(inode);
			वापस error;
		पूर्ण
		inode->i_mapping->a_ops = &shmem_aops;
		inode->i_op = &shmem_symlink_inode_operations;
		स_नकल(page_address(page), symname, len);
		SetPageUptodate(page);
		set_page_dirty(page);
		unlock_page(page);
		put_page(page);
	पूर्ण
	dir->i_size += BOGO_सूचीENT_SIZE;
	dir->i_स_समय = dir->i_mसमय = current_समय(dir);
	d_instantiate(dentry, inode);
	dget(dentry);
	वापस 0;
पूर्ण

अटल व्योम shmem_put_link(व्योम *arg)
अणु
	mark_page_accessed(arg);
	put_page(arg);
पूर्ण

अटल स्थिर अक्षर *shmem_get_link(काष्ठा dentry *dentry,
				  काष्ठा inode *inode,
				  काष्ठा delayed_call *करोne)
अणु
	काष्ठा page *page = शून्य;
	पूर्णांक error;
	अगर (!dentry) अणु
		page = find_get_page(inode->i_mapping, 0);
		अगर (!page)
			वापस ERR_PTR(-ECHILD);
		अगर (!PageUptodate(page)) अणु
			put_page(page);
			वापस ERR_PTR(-ECHILD);
		पूर्ण
	पूर्ण अन्यथा अणु
		error = shmem_getpage(inode, 0, &page, SGP_READ);
		अगर (error)
			वापस ERR_PTR(error);
		unlock_page(page);
	पूर्ण
	set_delayed_call(करोne, shmem_put_link, page);
	वापस page_address(page);
पूर्ण

#अगर_घोषित CONFIG_TMPFS_XATTR
/*
 * Superblocks without xattr inode operations may get some security.* xattr
 * support from the LSM "for free". As soon as we have any other xattrs
 * like ACLs, we also need to implement the security.* handlers at
 * fileप्रणाली level, though.
 */

/*
 * Callback क्रम security_inode_init_security() क्रम acquiring xattrs.
 */
अटल पूर्णांक shmem_initxattrs(काष्ठा inode *inode,
			    स्थिर काष्ठा xattr *xattr_array,
			    व्योम *fs_info)
अणु
	काष्ठा shmem_inode_info *info = SHMEM_I(inode);
	स्थिर काष्ठा xattr *xattr;
	काष्ठा simple_xattr *new_xattr;
	माप_प्रकार len;

	क्रम (xattr = xattr_array; xattr->name != शून्य; xattr++) अणु
		new_xattr = simple_xattr_alloc(xattr->value, xattr->value_len);
		अगर (!new_xattr)
			वापस -ENOMEM;

		len = म_माप(xattr->name) + 1;
		new_xattr->name = kदो_स्मृति(XATTR_SECURITY_PREFIX_LEN + len,
					  GFP_KERNEL);
		अगर (!new_xattr->name) अणु
			kvमुक्त(new_xattr);
			वापस -ENOMEM;
		पूर्ण

		स_नकल(new_xattr->name, XATTR_SECURITY_PREFIX,
		       XATTR_SECURITY_PREFIX_LEN);
		स_नकल(new_xattr->name + XATTR_SECURITY_PREFIX_LEN,
		       xattr->name, len);

		simple_xattr_list_add(&info->xattrs, new_xattr);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक shmem_xattr_handler_get(स्थिर काष्ठा xattr_handler *handler,
				   काष्ठा dentry *unused, काष्ठा inode *inode,
				   स्थिर अक्षर *name, व्योम *buffer, माप_प्रकार size)
अणु
	काष्ठा shmem_inode_info *info = SHMEM_I(inode);

	name = xattr_full_name(handler, name);
	वापस simple_xattr_get(&info->xattrs, name, buffer, size);
पूर्ण

अटल पूर्णांक shmem_xattr_handler_set(स्थिर काष्ठा xattr_handler *handler,
				   काष्ठा user_namespace *mnt_userns,
				   काष्ठा dentry *unused, काष्ठा inode *inode,
				   स्थिर अक्षर *name, स्थिर व्योम *value,
				   माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा shmem_inode_info *info = SHMEM_I(inode);

	name = xattr_full_name(handler, name);
	वापस simple_xattr_set(&info->xattrs, name, value, size, flags, शून्य);
पूर्ण

अटल स्थिर काष्ठा xattr_handler shmem_security_xattr_handler = अणु
	.prefix = XATTR_SECURITY_PREFIX,
	.get = shmem_xattr_handler_get,
	.set = shmem_xattr_handler_set,
पूर्ण;

अटल स्थिर काष्ठा xattr_handler shmem_trusted_xattr_handler = अणु
	.prefix = XATTR_TRUSTED_PREFIX,
	.get = shmem_xattr_handler_get,
	.set = shmem_xattr_handler_set,
पूर्ण;

अटल स्थिर काष्ठा xattr_handler *shmem_xattr_handlers[] = अणु
#अगर_घोषित CONFIG_TMPFS_POSIX_ACL
	&posix_acl_access_xattr_handler,
	&posix_acl_शेष_xattr_handler,
#पूर्ण_अगर
	&shmem_security_xattr_handler,
	&shmem_trusted_xattr_handler,
	शून्य
पूर्ण;

अटल sमाप_प्रकार shmem_listxattr(काष्ठा dentry *dentry, अक्षर *buffer, माप_प्रकार size)
अणु
	काष्ठा shmem_inode_info *info = SHMEM_I(d_inode(dentry));
	वापस simple_xattr_list(d_inode(dentry), &info->xattrs, buffer, size);
पूर्ण
#पूर्ण_अगर /* CONFIG_TMPFS_XATTR */

अटल स्थिर काष्ठा inode_operations shmem_लघु_symlink_operations = अणु
	.get_link	= simple_get_link,
#अगर_घोषित CONFIG_TMPFS_XATTR
	.listxattr	= shmem_listxattr,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा inode_operations shmem_symlink_inode_operations = अणु
	.get_link	= shmem_get_link,
#अगर_घोषित CONFIG_TMPFS_XATTR
	.listxattr	= shmem_listxattr,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा dentry *shmem_get_parent(काष्ठा dentry *child)
अणु
	वापस ERR_PTR(-ESTALE);
पूर्ण

अटल पूर्णांक shmem_match(काष्ठा inode *ino, व्योम *vfh)
अणु
	__u32 *fh = vfh;
	__u64 inum = fh[2];
	inum = (inum << 32) | fh[1];
	वापस ino->i_ino == inum && fh[0] == ino->i_generation;
पूर्ण

/* Find any alias of inode, but prefer a hashed alias */
अटल काष्ठा dentry *shmem_find_alias(काष्ठा inode *inode)
अणु
	काष्ठा dentry *alias = d_find_alias(inode);

	वापस alias ?: d_find_any_alias(inode);
पूर्ण


अटल काष्ठा dentry *shmem_fh_to_dentry(काष्ठा super_block *sb,
		काष्ठा fid *fid, पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	काष्ठा inode *inode;
	काष्ठा dentry *dentry = शून्य;
	u64 inum;

	अगर (fh_len < 3)
		वापस शून्य;

	inum = fid->raw[2];
	inum = (inum << 32) | fid->raw[1];

	inode = ilookup5(sb, (अचिन्हित दीर्घ)(inum + fid->raw[0]),
			shmem_match, fid->raw);
	अगर (inode) अणु
		dentry = shmem_find_alias(inode);
		iput(inode);
	पूर्ण

	वापस dentry;
पूर्ण

अटल पूर्णांक shmem_encode_fh(काष्ठा inode *inode, __u32 *fh, पूर्णांक *len,
				काष्ठा inode *parent)
अणु
	अगर (*len < 3) अणु
		*len = 3;
		वापस खाताID_INVALID;
	पूर्ण

	अगर (inode_unhashed(inode)) अणु
		/* Unक्रमtunately insert_inode_hash is not idempotent,
		 * so as we hash inodes here rather than at creation
		 * समय, we need a lock to ensure we only try
		 * to करो it once
		 */
		अटल DEFINE_SPINLOCK(lock);
		spin_lock(&lock);
		अगर (inode_unhashed(inode))
			__insert_inode_hash(inode,
					    inode->i_ino + inode->i_generation);
		spin_unlock(&lock);
	पूर्ण

	fh[0] = inode->i_generation;
	fh[1] = inode->i_ino;
	fh[2] = ((__u64)inode->i_ino) >> 32;

	*len = 3;
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा export_operations shmem_export_ops = अणु
	.get_parent     = shmem_get_parent,
	.encode_fh      = shmem_encode_fh,
	.fh_to_dentry	= shmem_fh_to_dentry,
पूर्ण;

क्रमागत shmem_param अणु
	Opt_gid,
	Opt_huge,
	Opt_mode,
	Opt_mpol,
	Opt_nr_blocks,
	Opt_nr_inodes,
	Opt_size,
	Opt_uid,
	Opt_inode32,
	Opt_inode64,
पूर्ण;

अटल स्थिर काष्ठा स्थिरant_table shmem_param_क्रमागतs_huge[] = अणु
	अणु"never",	SHMEM_HUGE_NEVER पूर्ण,
	अणु"always",	SHMEM_HUGE_ALWAYS पूर्ण,
	अणु"within_size",	SHMEM_HUGE_WITHIN_SIZE पूर्ण,
	अणु"advise",	SHMEM_HUGE_ADVISE पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा fs_parameter_spec shmem_fs_parameters[] = अणु
	fsparam_u32   ("gid",		Opt_gid),
	fsparam_क्रमागत  ("huge",		Opt_huge,  shmem_param_क्रमागतs_huge),
	fsparam_u32oct("mode",		Opt_mode),
	fsparam_string("mpol",		Opt_mpol),
	fsparam_string("nr_blocks",	Opt_nr_blocks),
	fsparam_string("nr_inodes",	Opt_nr_inodes),
	fsparam_string("size",		Opt_size),
	fsparam_u32   ("uid",		Opt_uid),
	fsparam_flag  ("inode32",	Opt_inode32),
	fsparam_flag  ("inode64",	Opt_inode64),
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक shmem_parse_one(काष्ठा fs_context *fc, काष्ठा fs_parameter *param)
अणु
	काष्ठा shmem_options *ctx = fc->fs_निजी;
	काष्ठा fs_parse_result result;
	अचिन्हित दीर्घ दीर्घ size;
	अक्षर *rest;
	पूर्णांक opt;

	opt = fs_parse(fc, shmem_fs_parameters, param, &result);
	अगर (opt < 0)
		वापस opt;

	चयन (opt) अणु
	हाल Opt_size:
		size = memparse(param->string, &rest);
		अगर (*rest == '%') अणु
			size <<= PAGE_SHIFT;
			size *= totalram_pages();
			करो_भाग(size, 100);
			rest++;
		पूर्ण
		अगर (*rest)
			जाओ bad_value;
		ctx->blocks = DIV_ROUND_UP(size, PAGE_SIZE);
		ctx->seen |= SHMEM_SEEN_BLOCKS;
		अवरोध;
	हाल Opt_nr_blocks:
		ctx->blocks = memparse(param->string, &rest);
		अगर (*rest)
			जाओ bad_value;
		ctx->seen |= SHMEM_SEEN_BLOCKS;
		अवरोध;
	हाल Opt_nr_inodes:
		ctx->inodes = memparse(param->string, &rest);
		अगर (*rest)
			जाओ bad_value;
		ctx->seen |= SHMEM_SEEN_INODES;
		अवरोध;
	हाल Opt_mode:
		ctx->mode = result.uपूर्णांक_32 & 07777;
		अवरोध;
	हाल Opt_uid:
		ctx->uid = make_kuid(current_user_ns(), result.uपूर्णांक_32);
		अगर (!uid_valid(ctx->uid))
			जाओ bad_value;
		अवरोध;
	हाल Opt_gid:
		ctx->gid = make_kgid(current_user_ns(), result.uपूर्णांक_32);
		अगर (!gid_valid(ctx->gid))
			जाओ bad_value;
		अवरोध;
	हाल Opt_huge:
		ctx->huge = result.uपूर्णांक_32;
		अगर (ctx->huge != SHMEM_HUGE_NEVER &&
		    !(IS_ENABLED(CONFIG_TRANSPARENT_HUGEPAGE) &&
		      has_transparent_hugepage()))
			जाओ unsupported_parameter;
		ctx->seen |= SHMEM_SEEN_HUGE;
		अवरोध;
	हाल Opt_mpol:
		अगर (IS_ENABLED(CONFIG_NUMA)) अणु
			mpol_put(ctx->mpol);
			ctx->mpol = शून्य;
			अगर (mpol_parse_str(param->string, &ctx->mpol))
				जाओ bad_value;
			अवरोध;
		पूर्ण
		जाओ unsupported_parameter;
	हाल Opt_inode32:
		ctx->full_inums = false;
		ctx->seen |= SHMEM_SEEN_INUMS;
		अवरोध;
	हाल Opt_inode64:
		अगर (माप(ino_t) < 8) अणु
			वापस invalfc(fc,
				       "Cannot use inode64 with <64bit inums in kernel\n");
		पूर्ण
		ctx->full_inums = true;
		ctx->seen |= SHMEM_SEEN_INUMS;
		अवरोध;
	पूर्ण
	वापस 0;

unsupported_parameter:
	वापस invalfc(fc, "Unsupported parameter '%s'", param->key);
bad_value:
	वापस invalfc(fc, "Bad value for '%s'", param->key);
पूर्ण

अटल पूर्णांक shmem_parse_options(काष्ठा fs_context *fc, व्योम *data)
अणु
	अक्षर *options = data;

	अगर (options) अणु
		पूर्णांक err = security_sb_eat_lsm_opts(options, &fc->security);
		अगर (err)
			वापस err;
	पूर्ण

	जबतक (options != शून्य) अणु
		अक्षर *this_अक्षर = options;
		क्रम (;;) अणु
			/*
			 * NUL-terminate this option: unक्रमtunately,
			 * mount options क्रमm a comma-separated list,
			 * but mpol's nodelist may also contain commas.
			 */
			options = म_अक्षर(options, ',');
			अगर (options == शून्य)
				अवरोध;
			options++;
			अगर (!है_अंक(*options)) अणु
				options[-1] = '\0';
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (*this_अक्षर) अणु
			अक्षर *value = म_अक्षर(this_अक्षर, '=');
			माप_प्रकार len = 0;
			पूर्णांक err;

			अगर (value) अणु
				*value++ = '\0';
				len = म_माप(value);
			पूर्ण
			err = vfs_parse_fs_string(fc, this_अक्षर, value, len);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Reconfigure a shmem fileप्रणाली.
 *
 * Note that we disallow change from limited->unlimited blocks/inodes जबतक any
 * are in use; but we must separately disallow unlimited->limited, because in
 * that हाल we have no record of how much is alपढ़ोy in use.
 */
अटल पूर्णांक shmem_reconfigure(काष्ठा fs_context *fc)
अणु
	काष्ठा shmem_options *ctx = fc->fs_निजी;
	काष्ठा shmem_sb_info *sbinfo = SHMEM_SB(fc->root->d_sb);
	अचिन्हित दीर्घ inodes;
	स्थिर अक्षर *err;

	spin_lock(&sbinfo->stat_lock);
	inodes = sbinfo->max_inodes - sbinfo->मुक्त_inodes;
	अगर ((ctx->seen & SHMEM_SEEN_BLOCKS) && ctx->blocks) अणु
		अगर (!sbinfo->max_blocks) अणु
			err = "Cannot retroactively limit size";
			जाओ out;
		पूर्ण
		अगर (percpu_counter_compare(&sbinfo->used_blocks,
					   ctx->blocks) > 0) अणु
			err = "Too small a size for current use";
			जाओ out;
		पूर्ण
	पूर्ण
	अगर ((ctx->seen & SHMEM_SEEN_INODES) && ctx->inodes) अणु
		अगर (!sbinfo->max_inodes) अणु
			err = "Cannot retroactively limit inodes";
			जाओ out;
		पूर्ण
		अगर (ctx->inodes < inodes) अणु
			err = "Too few inodes for current use";
			जाओ out;
		पूर्ण
	पूर्ण

	अगर ((ctx->seen & SHMEM_SEEN_INUMS) && !ctx->full_inums &&
	    sbinfo->next_ino > अच_पूर्णांक_उच्च) अणु
		err = "Current inum too high to switch to 32-bit inums";
		जाओ out;
	पूर्ण

	अगर (ctx->seen & SHMEM_SEEN_HUGE)
		sbinfo->huge = ctx->huge;
	अगर (ctx->seen & SHMEM_SEEN_INUMS)
		sbinfo->full_inums = ctx->full_inums;
	अगर (ctx->seen & SHMEM_SEEN_BLOCKS)
		sbinfo->max_blocks  = ctx->blocks;
	अगर (ctx->seen & SHMEM_SEEN_INODES) अणु
		sbinfo->max_inodes  = ctx->inodes;
		sbinfo->मुक्त_inodes = ctx->inodes - inodes;
	पूर्ण

	/*
	 * Preserve previous mempolicy unless mpol remount option was specअगरied.
	 */
	अगर (ctx->mpol) अणु
		mpol_put(sbinfo->mpol);
		sbinfo->mpol = ctx->mpol;	/* transfers initial ref */
		ctx->mpol = शून्य;
	पूर्ण
	spin_unlock(&sbinfo->stat_lock);
	वापस 0;
out:
	spin_unlock(&sbinfo->stat_lock);
	वापस invalfc(fc, "%s", err);
पूर्ण

अटल पूर्णांक shmem_show_options(काष्ठा seq_file *seq, काष्ठा dentry *root)
अणु
	काष्ठा shmem_sb_info *sbinfo = SHMEM_SB(root->d_sb);

	अगर (sbinfo->max_blocks != shmem_शेष_max_blocks())
		seq_म_लिखो(seq, ",size=%luk",
			sbinfo->max_blocks << (PAGE_SHIFT - 10));
	अगर (sbinfo->max_inodes != shmem_शेष_max_inodes())
		seq_म_लिखो(seq, ",nr_inodes=%lu", sbinfo->max_inodes);
	अगर (sbinfo->mode != (0777 | S_ISVTX))
		seq_म_लिखो(seq, ",mode=%03ho", sbinfo->mode);
	अगर (!uid_eq(sbinfo->uid, GLOBAL_ROOT_UID))
		seq_म_लिखो(seq, ",uid=%u",
				from_kuid_munged(&init_user_ns, sbinfo->uid));
	अगर (!gid_eq(sbinfo->gid, GLOBAL_ROOT_GID))
		seq_म_लिखो(seq, ",gid=%u",
				from_kgid_munged(&init_user_ns, sbinfo->gid));

	/*
	 * Showing inodeअणु64,32पूर्ण might be useful even अगर it's the प्रणाली शेष,
	 * since then people करोn't have to resort to checking both here and
	 * /proc/config.gz to confirm 64-bit inums were successfully applied
	 * (which may not even exist अगर IKCONFIG_PROC isn't enabled).
	 *
	 * We hide it when inode64 isn't the शेष and we are using 32-bit
	 * inodes, since that probably just means the feature isn't even under
	 * consideration.
	 *
	 * As such:
	 *
	 *                     +-----------------+-----------------+
	 *                     | TMPFS_INODE64=y | TMPFS_INODE64=n |
	 *  +------------------+-----------------+-----------------+
	 *  | full_inums=true  | show            | show            |
	 *  | full_inums=false | show            | hide            |
	 *  +------------------+-----------------+-----------------+
	 *
	 */
	अगर (IS_ENABLED(CONFIG_TMPFS_INODE64) || sbinfo->full_inums)
		seq_म_लिखो(seq, ",inode%d", (sbinfo->full_inums ? 64 : 32));
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
	/* Rightly or wrongly, show huge mount option unmasked by shmem_huge */
	अगर (sbinfo->huge)
		seq_म_लिखो(seq, ",huge=%s", shmem_क्रमmat_huge(sbinfo->huge));
#पूर्ण_अगर
	shmem_show_mpol(seq, sbinfo->mpol);
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_TMPFS */

अटल व्योम shmem_put_super(काष्ठा super_block *sb)
अणु
	काष्ठा shmem_sb_info *sbinfo = SHMEM_SB(sb);

	मुक्त_percpu(sbinfo->ino_batch);
	percpu_counter_destroy(&sbinfo->used_blocks);
	mpol_put(sbinfo->mpol);
	kमुक्त(sbinfo);
	sb->s_fs_info = शून्य;
पूर्ण

अटल पूर्णांक shmem_fill_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	काष्ठा shmem_options *ctx = fc->fs_निजी;
	काष्ठा inode *inode;
	काष्ठा shmem_sb_info *sbinfo;
	पूर्णांक err = -ENOMEM;

	/* Round up to L1_CACHE_BYTES to resist false sharing */
	sbinfo = kzalloc(max((पूर्णांक)माप(काष्ठा shmem_sb_info),
				L1_CACHE_BYTES), GFP_KERNEL);
	अगर (!sbinfo)
		वापस -ENOMEM;

	sb->s_fs_info = sbinfo;

#अगर_घोषित CONFIG_TMPFS
	/*
	 * Per शेष we only allow half of the physical ram per
	 * पंचांगpfs instance, limiting inodes to one per page of lowmem;
	 * but the पूर्णांकernal instance is left unlimited.
	 */
	अगर (!(sb->s_flags & SB_KERNMOUNT)) अणु
		अगर (!(ctx->seen & SHMEM_SEEN_BLOCKS))
			ctx->blocks = shmem_शेष_max_blocks();
		अगर (!(ctx->seen & SHMEM_SEEN_INODES))
			ctx->inodes = shmem_शेष_max_inodes();
		अगर (!(ctx->seen & SHMEM_SEEN_INUMS))
			ctx->full_inums = IS_ENABLED(CONFIG_TMPFS_INODE64);
	पूर्ण अन्यथा अणु
		sb->s_flags |= SB_NOUSER;
	पूर्ण
	sb->s_export_op = &shmem_export_ops;
	sb->s_flags |= SB_NOSEC;
#अन्यथा
	sb->s_flags |= SB_NOUSER;
#पूर्ण_अगर
	sbinfo->max_blocks = ctx->blocks;
	sbinfo->मुक्त_inodes = sbinfo->max_inodes = ctx->inodes;
	अगर (sb->s_flags & SB_KERNMOUNT) अणु
		sbinfo->ino_batch = alloc_percpu(ino_t);
		अगर (!sbinfo->ino_batch)
			जाओ failed;
	पूर्ण
	sbinfo->uid = ctx->uid;
	sbinfo->gid = ctx->gid;
	sbinfo->full_inums = ctx->full_inums;
	sbinfo->mode = ctx->mode;
	sbinfo->huge = ctx->huge;
	sbinfo->mpol = ctx->mpol;
	ctx->mpol = शून्य;

	spin_lock_init(&sbinfo->stat_lock);
	अगर (percpu_counter_init(&sbinfo->used_blocks, 0, GFP_KERNEL))
		जाओ failed;
	spin_lock_init(&sbinfo->shrinklist_lock);
	INIT_LIST_HEAD(&sbinfo->shrinklist);

	sb->s_maxbytes = MAX_LFS_खाताSIZE;
	sb->s_blocksize = PAGE_SIZE;
	sb->s_blocksize_bits = PAGE_SHIFT;
	sb->s_magic = TMPFS_MAGIC;
	sb->s_op = &shmem_ops;
	sb->s_समय_gran = 1;
#अगर_घोषित CONFIG_TMPFS_XATTR
	sb->s_xattr = shmem_xattr_handlers;
#पूर्ण_अगर
#अगर_घोषित CONFIG_TMPFS_POSIX_ACL
	sb->s_flags |= SB_POSIXACL;
#पूर्ण_अगर
	uuid_gen(&sb->s_uuid);

	inode = shmem_get_inode(sb, शून्य, S_IFसूची | sbinfo->mode, 0, VM_NORESERVE);
	अगर (!inode)
		जाओ failed;
	inode->i_uid = sbinfo->uid;
	inode->i_gid = sbinfo->gid;
	sb->s_root = d_make_root(inode);
	अगर (!sb->s_root)
		जाओ failed;
	वापस 0;

failed:
	shmem_put_super(sb);
	वापस err;
पूर्ण

अटल पूर्णांक shmem_get_tree(काष्ठा fs_context *fc)
अणु
	वापस get_tree_nodev(fc, shmem_fill_super);
पूर्ण

अटल व्योम shmem_मुक्त_fc(काष्ठा fs_context *fc)
अणु
	काष्ठा shmem_options *ctx = fc->fs_निजी;

	अगर (ctx) अणु
		mpol_put(ctx->mpol);
		kमुक्त(ctx);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा fs_context_operations shmem_fs_context_ops = अणु
	.मुक्त			= shmem_मुक्त_fc,
	.get_tree		= shmem_get_tree,
#अगर_घोषित CONFIG_TMPFS
	.parse_monolithic	= shmem_parse_options,
	.parse_param		= shmem_parse_one,
	.reconfigure		= shmem_reconfigure,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा kmem_cache *shmem_inode_cachep;

अटल काष्ठा inode *shmem_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा shmem_inode_info *info;
	info = kmem_cache_alloc(shmem_inode_cachep, GFP_KERNEL);
	अगर (!info)
		वापस शून्य;
	वापस &info->vfs_inode;
पूर्ण

अटल व्योम shmem_मुक्त_in_core_inode(काष्ठा inode *inode)
अणु
	अगर (S_ISLNK(inode->i_mode))
		kमुक्त(inode->i_link);
	kmem_cache_मुक्त(shmem_inode_cachep, SHMEM_I(inode));
पूर्ण

अटल व्योम shmem_destroy_inode(काष्ठा inode *inode)
अणु
	अगर (S_ISREG(inode->i_mode))
		mpol_मुक्त_shared_policy(&SHMEM_I(inode)->policy);
पूर्ण

अटल व्योम shmem_init_inode(व्योम *foo)
अणु
	काष्ठा shmem_inode_info *info = foo;
	inode_init_once(&info->vfs_inode);
पूर्ण

अटल व्योम shmem_init_inodecache(व्योम)
अणु
	shmem_inode_cachep = kmem_cache_create("shmem_inode_cache",
				माप(काष्ठा shmem_inode_info),
				0, SLAB_PANIC|SLAB_ACCOUNT, shmem_init_inode);
पूर्ण

अटल व्योम shmem_destroy_inodecache(व्योम)
अणु
	kmem_cache_destroy(shmem_inode_cachep);
पूर्ण

स्थिर काष्ठा address_space_operations shmem_aops = अणु
	.ग_लिखोpage	= shmem_ग_लिखोpage,
	.set_page_dirty	= __set_page_dirty_no_ग_लिखोback,
#अगर_घोषित CONFIG_TMPFS
	.ग_लिखो_begin	= shmem_ग_लिखो_begin,
	.ग_लिखो_end	= shmem_ग_लिखो_end,
#पूर्ण_अगर
#अगर_घोषित CONFIG_MIGRATION
	.migratepage	= migrate_page,
#पूर्ण_अगर
	.error_हटाओ_page = generic_error_हटाओ_page,
पूर्ण;
EXPORT_SYMBOL(shmem_aops);

अटल स्थिर काष्ठा file_operations shmem_file_operations = अणु
	.mmap		= shmem_mmap,
	.get_unmapped_area = shmem_get_unmapped_area,
#अगर_घोषित CONFIG_TMPFS
	.llseek		= shmem_file_llseek,
	.पढ़ो_iter	= shmem_file_पढ़ो_iter,
	.ग_लिखो_iter	= generic_file_ग_लिखो_iter,
	.fsync		= noop_fsync,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
	.splice_ग_लिखो	= iter_file_splice_ग_लिखो,
	.fallocate	= shmem_fallocate,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा inode_operations shmem_inode_operations = अणु
	.getattr	= shmem_getattr,
	.setattr	= shmem_setattr,
#अगर_घोषित CONFIG_TMPFS_XATTR
	.listxattr	= shmem_listxattr,
	.set_acl	= simple_set_acl,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा inode_operations shmem_dir_inode_operations = अणु
#अगर_घोषित CONFIG_TMPFS
	.create		= shmem_create,
	.lookup		= simple_lookup,
	.link		= shmem_link,
	.unlink		= shmem_unlink,
	.symlink	= shmem_symlink,
	.सूची_गढ़ो		= shmem_सूची_गढ़ो,
	.सूची_हटाओ		= shmem_सूची_हटाओ,
	.mknod		= shmem_mknod,
	.नाम		= shmem_नाम2,
	.क्षणिक_ख	= shmem_क्षणिक_ख,
#पूर्ण_अगर
#अगर_घोषित CONFIG_TMPFS_XATTR
	.listxattr	= shmem_listxattr,
#पूर्ण_अगर
#अगर_घोषित CONFIG_TMPFS_POSIX_ACL
	.setattr	= shmem_setattr,
	.set_acl	= simple_set_acl,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा inode_operations shmem_special_inode_operations = अणु
#अगर_घोषित CONFIG_TMPFS_XATTR
	.listxattr	= shmem_listxattr,
#पूर्ण_अगर
#अगर_घोषित CONFIG_TMPFS_POSIX_ACL
	.setattr	= shmem_setattr,
	.set_acl	= simple_set_acl,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा super_operations shmem_ops = अणु
	.alloc_inode	= shmem_alloc_inode,
	.मुक्त_inode	= shmem_मुक्त_in_core_inode,
	.destroy_inode	= shmem_destroy_inode,
#अगर_घोषित CONFIG_TMPFS
	.statfs		= shmem_statfs,
	.show_options	= shmem_show_options,
#पूर्ण_अगर
	.evict_inode	= shmem_evict_inode,
	.drop_inode	= generic_delete_inode,
	.put_super	= shmem_put_super,
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
	.nr_cached_objects	= shmem_unused_huge_count,
	.मुक्त_cached_objects	= shmem_unused_huge_scan,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा vm_operations_काष्ठा shmem_vm_ops = अणु
	.fault		= shmem_fault,
	.map_pages	= filemap_map_pages,
#अगर_घोषित CONFIG_NUMA
	.set_policy     = shmem_set_policy,
	.get_policy     = shmem_get_policy,
#पूर्ण_अगर
पूर्ण;

पूर्णांक shmem_init_fs_context(काष्ठा fs_context *fc)
अणु
	काष्ठा shmem_options *ctx;

	ctx = kzalloc(माप(काष्ठा shmem_options), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->mode = 0777 | S_ISVTX;
	ctx->uid = current_fsuid();
	ctx->gid = current_fsgid();

	fc->fs_निजी = ctx;
	fc->ops = &shmem_fs_context_ops;
	वापस 0;
पूर्ण

अटल काष्ठा file_प्रणाली_type shmem_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "tmpfs",
	.init_fs_context = shmem_init_fs_context,
#अगर_घोषित CONFIG_TMPFS
	.parameters	= shmem_fs_parameters,
#पूर्ण_अगर
	.समाप्त_sb	= समाप्त_litter_super,
	.fs_flags	= FS_USERNS_MOUNT | FS_THP_SUPPORT,
पूर्ण;

पूर्णांक __init shmem_init(व्योम)
अणु
	पूर्णांक error;

	shmem_init_inodecache();

	error = रेजिस्टर_fileप्रणाली(&shmem_fs_type);
	अगर (error) अणु
		pr_err("Could not register tmpfs\n");
		जाओ out2;
	पूर्ण

	shm_mnt = kern_mount(&shmem_fs_type);
	अगर (IS_ERR(shm_mnt)) अणु
		error = PTR_ERR(shm_mnt);
		pr_err("Could not kern_mount tmpfs\n");
		जाओ out1;
	पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
	अगर (has_transparent_hugepage() && shmem_huge > SHMEM_HUGE_DENY)
		SHMEM_SB(shm_mnt->mnt_sb)->huge = shmem_huge;
	अन्यथा
		shmem_huge = 0; /* just in हाल it was patched */
#पूर्ण_अगर
	वापस 0;

out1:
	unरेजिस्टर_fileप्रणाली(&shmem_fs_type);
out2:
	shmem_destroy_inodecache();
	shm_mnt = ERR_PTR(error);
	वापस error;
पूर्ण

#अगर defined(CONFIG_TRANSPARENT_HUGEPAGE) && defined(CONFIG_SYSFS)
अटल sमाप_प्रकार shmem_enabled_show(काष्ठा kobject *kobj,
				  काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	अटल स्थिर पूर्णांक values[] = अणु
		SHMEM_HUGE_ALWAYS,
		SHMEM_HUGE_WITHIN_SIZE,
		SHMEM_HUGE_ADVISE,
		SHMEM_HUGE_NEVER,
		SHMEM_HUGE_DENY,
		SHMEM_HUGE_FORCE,
	पूर्ण;
	पूर्णांक len = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(values); i++) अणु
		len += sysfs_emit_at(buf, len,
				     shmem_huge == values[i] ? "%s[%s]" : "%s%s",
				     i ? " " : "",
				     shmem_क्रमmat_huge(values[i]));
	पूर्ण

	len += sysfs_emit_at(buf, len, "\n");

	वापस len;
पूर्ण

अटल sमाप_प्रकार shmem_enabled_store(काष्ठा kobject *kobj,
		काष्ठा kobj_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अक्षर पंचांगp[16];
	पूर्णांक huge;

	अगर (count + 1 > माप(पंचांगp))
		वापस -EINVAL;
	स_नकल(पंचांगp, buf, count);
	पंचांगp[count] = '\0';
	अगर (count && पंचांगp[count - 1] == '\n')
		पंचांगp[count - 1] = '\0';

	huge = shmem_parse_huge(पंचांगp);
	अगर (huge == -EINVAL)
		वापस -EINVAL;
	अगर (!has_transparent_hugepage() &&
			huge != SHMEM_HUGE_NEVER && huge != SHMEM_HUGE_DENY)
		वापस -EINVAL;

	shmem_huge = huge;
	अगर (shmem_huge > SHMEM_HUGE_DENY)
		SHMEM_SB(shm_mnt->mnt_sb)->huge = shmem_huge;
	वापस count;
पूर्ण

काष्ठा kobj_attribute shmem_enabled_attr =
	__ATTR(shmem_enabled, 0644, shmem_enabled_show, shmem_enabled_store);
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE && CONFIG_SYSFS */

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
bool shmem_huge_enabled(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा inode *inode = file_inode(vma->vm_file);
	काष्ठा shmem_sb_info *sbinfo = SHMEM_SB(inode->i_sb);
	loff_t i_size;
	pgoff_t off;

	अगर ((vma->vm_flags & VM_NOHUGEPAGE) ||
	    test_bit(MMF_DISABLE_THP, &vma->vm_mm->flags))
		वापस false;
	अगर (shmem_huge == SHMEM_HUGE_FORCE)
		वापस true;
	अगर (shmem_huge == SHMEM_HUGE_DENY)
		वापस false;
	चयन (sbinfo->huge) अणु
		हाल SHMEM_HUGE_NEVER:
			वापस false;
		हाल SHMEM_HUGE_ALWAYS:
			वापस true;
		हाल SHMEM_HUGE_WITHIN_SIZE:
			off = round_up(vma->vm_pgoff, HPAGE_PMD_NR);
			i_size = round_up(i_size_पढ़ो(inode), PAGE_SIZE);
			अगर (i_size >= HPAGE_PMD_SIZE &&
					i_size >> PAGE_SHIFT >= off)
				वापस true;
			fallthrough;
		हाल SHMEM_HUGE_ADVISE:
			/* TODO: implement fadvise() hपूर्णांकs */
			वापस (vma->vm_flags & VM_HUGEPAGE);
		शेष:
			VM_BUG_ON(1);
			वापस false;
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */

#अन्यथा /* !CONFIG_SHMEM */

/*
 * tiny-shmem: simple shmemfs and पंचांगpfs using ramfs code
 *
 * This is पूर्णांकended क्रम small प्रणाली where the benefits of the full
 * shmem code (swap-backed and resource-limited) are outweighed by
 * their complनिकासy. On प्रणालीs without swap this code should be
 * effectively equivalent, but much lighter weight.
 */

अटल काष्ठा file_प्रणाली_type shmem_fs_type = अणु
	.name		= "tmpfs",
	.init_fs_context = ramfs_init_fs_context,
	.parameters	= ramfs_fs_parameters,
	.समाप्त_sb	= समाप्त_litter_super,
	.fs_flags	= FS_USERNS_MOUNT,
पूर्ण;

पूर्णांक __init shmem_init(व्योम)
अणु
	BUG_ON(रेजिस्टर_fileप्रणाली(&shmem_fs_type) != 0);

	shm_mnt = kern_mount(&shmem_fs_type);
	BUG_ON(IS_ERR(shm_mnt));

	वापस 0;
पूर्ण

पूर्णांक shmem_unuse(अचिन्हित पूर्णांक type, bool frontswap,
		अचिन्हित दीर्घ *fs_pages_to_unuse)
अणु
	वापस 0;
पूर्ण

पूर्णांक shmem_lock(काष्ठा file *file, पूर्णांक lock, काष्ठा user_काष्ठा *user)
अणु
	वापस 0;
पूर्ण

व्योम shmem_unlock_mapping(काष्ठा address_space *mapping)
अणु
पूर्ण

#अगर_घोषित CONFIG_MMU
अचिन्हित दीर्घ shmem_get_unmapped_area(काष्ठा file *file,
				      अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
				      अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags)
अणु
	वापस current->mm->get_unmapped_area(file, addr, len, pgoff, flags);
पूर्ण
#पूर्ण_अगर

व्योम shmem_truncate_range(काष्ठा inode *inode, loff_t lstart, loff_t lend)
अणु
	truncate_inode_pages_range(inode->i_mapping, lstart, lend);
पूर्ण
EXPORT_SYMBOL_GPL(shmem_truncate_range);

#घोषणा shmem_vm_ops				generic_file_vm_ops
#घोषणा shmem_file_operations			ramfs_file_operations
#घोषणा shmem_get_inode(sb, dir, mode, dev, flags)	ramfs_get_inode(sb, dir, mode, dev)
#घोषणा shmem_acct_size(flags, size)		0
#घोषणा shmem_unacct_size(flags, size)		करो अणुपूर्ण जबतक (0)

#पूर्ण_अगर /* CONFIG_SHMEM */

/* common code */

अटल काष्ठा file *__shmem_file_setup(काष्ठा vfsmount *mnt, स्थिर अक्षर *name, loff_t size,
				       अचिन्हित दीर्घ flags, अचिन्हित पूर्णांक i_flags)
अणु
	काष्ठा inode *inode;
	काष्ठा file *res;

	अगर (IS_ERR(mnt))
		वापस ERR_CAST(mnt);

	अगर (size < 0 || size > MAX_LFS_खाताSIZE)
		वापस ERR_PTR(-EINVAL);

	अगर (shmem_acct_size(flags, size))
		वापस ERR_PTR(-ENOMEM);

	inode = shmem_get_inode(mnt->mnt_sb, शून्य, S_IFREG | S_IRWXUGO, 0,
				flags);
	अगर (unlikely(!inode)) अणु
		shmem_unacct_size(flags, size);
		वापस ERR_PTR(-ENOSPC);
	पूर्ण
	inode->i_flags |= i_flags;
	inode->i_size = size;
	clear_nlink(inode);	/* It is unlinked */
	res = ERR_PTR(ramfs_nommu_expand_क्रम_mapping(inode, size));
	अगर (!IS_ERR(res))
		res = alloc_file_pseuकरो(inode, mnt, name, O_RDWR,
				&shmem_file_operations);
	अगर (IS_ERR(res))
		iput(inode);
	वापस res;
पूर्ण

/**
 * shmem_kernel_file_setup - get an unlinked file living in पंचांगpfs which must be
 * 	kernel पूर्णांकernal.  There will be NO LSM permission checks against the
 * 	underlying inode.  So users of this पूर्णांकerface must करो LSM checks at a
 *	higher layer.  The users are the big_key and shm implementations.  LSM
 *	checks are provided at the key or shm level rather than the inode.
 * @name: name क्रम dentry (to be seen in /proc/<pid>/maps
 * @size: size to be set क्रम the file
 * @flags: VM_NORESERVE suppresses pre-accounting of the entire object size
 */
काष्ठा file *shmem_kernel_file_setup(स्थिर अक्षर *name, loff_t size, अचिन्हित दीर्घ flags)
अणु
	वापस __shmem_file_setup(shm_mnt, name, size, flags, S_PRIVATE);
पूर्ण

/**
 * shmem_file_setup - get an unlinked file living in पंचांगpfs
 * @name: name क्रम dentry (to be seen in /proc/<pid>/maps
 * @size: size to be set क्रम the file
 * @flags: VM_NORESERVE suppresses pre-accounting of the entire object size
 */
काष्ठा file *shmem_file_setup(स्थिर अक्षर *name, loff_t size, अचिन्हित दीर्घ flags)
अणु
	वापस __shmem_file_setup(shm_mnt, name, size, flags, 0);
पूर्ण
EXPORT_SYMBOL_GPL(shmem_file_setup);

/**
 * shmem_file_setup_with_mnt - get an unlinked file living in पंचांगpfs
 * @mnt: the पंचांगpfs mount where the file will be created
 * @name: name क्रम dentry (to be seen in /proc/<pid>/maps
 * @size: size to be set क्रम the file
 * @flags: VM_NORESERVE suppresses pre-accounting of the entire object size
 */
काष्ठा file *shmem_file_setup_with_mnt(काष्ठा vfsmount *mnt, स्थिर अक्षर *name,
				       loff_t size, अचिन्हित दीर्घ flags)
अणु
	वापस __shmem_file_setup(mnt, name, size, flags, 0);
पूर्ण
EXPORT_SYMBOL_GPL(shmem_file_setup_with_mnt);

/**
 * shmem_zero_setup - setup a shared anonymous mapping
 * @vma: the vma to be mmapped is prepared by करो_mmap
 */
पूर्णांक shmem_zero_setup(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा file *file;
	loff_t size = vma->vm_end - vma->vm_start;

	/*
	 * Cloning a new file under mmap_lock leads to a lock ordering conflict
	 * between XFS directory पढ़ोing and selinux: since this file is only
	 * accessible to the user through its mapping, use S_PRIVATE flag to
	 * bypass file security, in the same way as shmem_kernel_file_setup().
	 */
	file = shmem_kernel_file_setup("dev/zero", size, vma->vm_flags);
	अगर (IS_ERR(file))
		वापस PTR_ERR(file);

	अगर (vma->vm_file)
		fput(vma->vm_file);
	vma->vm_file = file;
	vma->vm_ops = &shmem_vm_ops;

	अगर (IS_ENABLED(CONFIG_TRANSPARENT_HUGEPAGE) &&
			((vma->vm_start + ~HPAGE_PMD_MASK) & HPAGE_PMD_MASK) <
			(vma->vm_end & HPAGE_PMD_MASK)) अणु
		khugepaged_enter(vma, vma->vm_flags);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * shmem_पढ़ो_mapping_page_gfp - पढ़ो पूर्णांकo page cache, using specअगरied page allocation flags.
 * @mapping:	the page's address_space
 * @index:	the page index
 * @gfp:	the page allocator flags to use अगर allocating
 *
 * This behaves as a पंचांगpfs "read_cache_page_gfp(mapping, index, gfp)",
 * with any new page allocations करोne using the specअगरied allocation flags.
 * But पढ़ो_cache_page_gfp() uses the ->पढ़ोpage() method: which करोes not
 * suit पंचांगpfs, since it may have pages in swapcache, and needs to find those
 * क्रम itself; although drivers/gpu/drm i915 and tपंचांग rely upon this support.
 *
 * i915_gem_object_get_pages_gtt() mixes __GFP_NORETRY | __GFP_NOWARN in
 * with the mapping_gfp_mask(), to aव्योम OOMing the machine unnecessarily.
 */
काष्ठा page *shmem_पढ़ो_mapping_page_gfp(काष्ठा address_space *mapping,
					 pgoff_t index, gfp_t gfp)
अणु
#अगर_घोषित CONFIG_SHMEM
	काष्ठा inode *inode = mapping->host;
	काष्ठा page *page;
	पूर्णांक error;

	BUG_ON(!shmem_mapping(mapping));
	error = shmem_getpage_gfp(inode, index, &page, SGP_CACHE,
				  gfp, शून्य, शून्य, शून्य);
	अगर (error)
		page = ERR_PTR(error);
	अन्यथा
		unlock_page(page);
	वापस page;
#अन्यथा
	/*
	 * The tiny !SHMEM हाल uses ramfs without swap
	 */
	वापस पढ़ो_cache_page_gfp(mapping, index, gfp);
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL_GPL(shmem_पढ़ो_mapping_page_gfp);
