<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_HUGETLB_H
#घोषणा _LINUX_HUGETLB_H

#समावेश <linux/mm_types.h>
#समावेश <linux/mmdebug.h>
#समावेश <linux/fs.h>
#समावेश <linux/hugetlb_अंतरभूत.h>
#समावेश <linux/cgroup.h>
#समावेश <linux/list.h>
#समावेश <linux/kref.h>
#समावेश <linux/pgtable.h>
#समावेश <linux/gfp.h>
#समावेश <linux/userfaultfd_k.h>

काष्ठा ctl_table;
काष्ठा user_काष्ठा;
काष्ठा mmu_gather;

#अगर_अघोषित is_hugepd
प्रकार काष्ठा अणु अचिन्हित दीर्घ pd; पूर्ण hugepd_t;
#घोषणा is_hugepd(hugepd) (0)
#घोषणा __hugepd(x) ((hugepd_t) अणु (x) पूर्ण)
#पूर्ण_अगर

#अगर_घोषित CONFIG_HUGETLB_PAGE

#समावेश <linux/mempolicy.h>
#समावेश <linux/shm.h>
#समावेश <यंत्र/tlbflush.h>

काष्ठा hugepage_subpool अणु
	spinlock_t lock;
	दीर्घ count;
	दीर्घ max_hpages;	/* Maximum huge pages or -1 अगर no maximum. */
	दीर्घ used_hpages;	/* Used count against maximum, includes */
				/* both alloced and reserved pages. */
	काष्ठा hstate *hstate;
	दीर्घ min_hpages;	/* Minimum huge pages or -1 अगर no minimum. */
	दीर्घ rsv_hpages;	/* Pages reserved against global pool to */
				/* satisfy minimum size. */
पूर्ण;

काष्ठा resv_map अणु
	काष्ठा kref refs;
	spinlock_t lock;
	काष्ठा list_head regions;
	दीर्घ adds_in_progress;
	काष्ठा list_head region_cache;
	दीर्घ region_cache_count;
#अगर_घोषित CONFIG_CGROUP_HUGETLB
	/*
	 * On निजी mappings, the counter to unअक्षरge reservations is stored
	 * here. If these fields are 0, then either the mapping is shared, or
	 * cgroup accounting is disabled क्रम this resv_map.
	 */
	काष्ठा page_counter *reservation_counter;
	अचिन्हित दीर्घ pages_per_hpage;
	काष्ठा cgroup_subsys_state *css;
#पूर्ण_अगर
पूर्ण;

/*
 * Region tracking -- allows tracking of reservations and instantiated pages
 *                    across the pages in a mapping.
 *
 * The region data काष्ठाures are embedded पूर्णांकo a resv_map and रक्षित
 * by a resv_map's lock.  The set of regions within the resv_map represent
 * reservations क्रम huge pages, or huge pages that have alपढ़ोy been
 * instantiated within the map.  The from and to elements are huge page
 * indicies पूर्णांकo the associated mapping.  from indicates the starting index
 * of the region.  to represents the first index past the end of  the region.
 *
 * For example, a file region काष्ठाure with from == 0 and to == 4 represents
 * four huge pages in a mapping.  It is important to note that the to element
 * represents the first element past the end of the region. This is used in
 * arithmetic as 4(to) - 0(from) = 4 huge pages in the region.
 *
 * Interval notation of the क्रमm [from, to) will be used to indicate that
 * the endpoपूर्णांक from is inclusive and to is exclusive.
 */
काष्ठा file_region अणु
	काष्ठा list_head link;
	दीर्घ from;
	दीर्घ to;
#अगर_घोषित CONFIG_CGROUP_HUGETLB
	/*
	 * On shared mappings, each reserved region appears as a काष्ठा
	 * file_region in resv_map. These fields hold the info needed to
	 * unअक्षरge each reservation.
	 */
	काष्ठा page_counter *reservation_counter;
	काष्ठा cgroup_subsys_state *css;
#पूर्ण_अगर
पूर्ण;

बाह्य काष्ठा resv_map *resv_map_alloc(व्योम);
व्योम resv_map_release(काष्ठा kref *ref);

बाह्य spinlock_t hugetlb_lock;
बाह्य पूर्णांक hugetlb_max_hstate __पढ़ो_mostly;
#घोषणा क्रम_each_hstate(h) \
	क्रम ((h) = hstates; (h) < &hstates[hugetlb_max_hstate]; (h)++)

काष्ठा hugepage_subpool *hugepage_new_subpool(काष्ठा hstate *h, दीर्घ max_hpages,
						दीर्घ min_hpages);
व्योम hugepage_put_subpool(काष्ठा hugepage_subpool *spool);

व्योम reset_vma_resv_huge_pages(काष्ठा vm_area_काष्ठा *vma);
पूर्णांक hugetlb_sysctl_handler(काष्ठा ctl_table *, पूर्णांक, व्योम *, माप_प्रकार *, loff_t *);
पूर्णांक hugetlb_overcommit_handler(काष्ठा ctl_table *, पूर्णांक, व्योम *, माप_प्रकार *,
		loff_t *);
पूर्णांक hugetlb_treat_movable_handler(काष्ठा ctl_table *, पूर्णांक, व्योम *, माप_प्रकार *,
		loff_t *);
पूर्णांक hugetlb_mempolicy_sysctl_handler(काष्ठा ctl_table *, पूर्णांक, व्योम *, माप_प्रकार *,
		loff_t *);

पूर्णांक copy_hugetlb_page_range(काष्ठा mm_काष्ठा *, काष्ठा mm_काष्ठा *, काष्ठा vm_area_काष्ठा *);
दीर्घ follow_hugetlb_page(काष्ठा mm_काष्ठा *, काष्ठा vm_area_काष्ठा *,
			 काष्ठा page **, काष्ठा vm_area_काष्ठा **,
			 अचिन्हित दीर्घ *, अचिन्हित दीर्घ *, दीर्घ, अचिन्हित पूर्णांक,
			 पूर्णांक *);
व्योम unmap_hugepage_range(काष्ठा vm_area_काष्ठा *,
			  अचिन्हित दीर्घ, अचिन्हित दीर्घ, काष्ठा page *);
व्योम __unmap_hugepage_range_final(काष्ठा mmu_gather *tlb,
			  काष्ठा vm_area_काष्ठा *vma,
			  अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
			  काष्ठा page *ref_page);
व्योम __unmap_hugepage_range(काष्ठा mmu_gather *tlb, काष्ठा vm_area_काष्ठा *vma,
				अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				काष्ठा page *ref_page);
व्योम hugetlb_report_meminfo(काष्ठा seq_file *);
पूर्णांक hugetlb_report_node_meminfo(अक्षर *buf, पूर्णांक len, पूर्णांक nid);
व्योम hugetlb_show_meminfo(व्योम);
अचिन्हित दीर्घ hugetlb_total_pages(व्योम);
vm_fault_t hugetlb_fault(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma,
			अचिन्हित दीर्घ address, अचिन्हित पूर्णांक flags);
#अगर_घोषित CONFIG_USERFAULTFD
पूर्णांक hugetlb_mcopy_atomic_pte(काष्ठा mm_काष्ठा *dst_mm, pte_t *dst_pte,
				काष्ठा vm_area_काष्ठा *dst_vma,
				अचिन्हित दीर्घ dst_addr,
				अचिन्हित दीर्घ src_addr,
				क्रमागत mcopy_atomic_mode mode,
				काष्ठा page **pagep);
#पूर्ण_अगर /* CONFIG_USERFAULTFD */
bool hugetlb_reserve_pages(काष्ठा inode *inode, दीर्घ from, दीर्घ to,
						काष्ठा vm_area_काष्ठा *vma,
						vm_flags_t vm_flags);
दीर्घ hugetlb_unreserve_pages(काष्ठा inode *inode, दीर्घ start, दीर्घ end,
						दीर्घ मुक्तd);
bool isolate_huge_page(काष्ठा page *page, काष्ठा list_head *list);
पूर्णांक get_hwpoison_huge_page(काष्ठा page *page, bool *hugetlb);
व्योम putback_active_hugepage(काष्ठा page *page);
व्योम move_hugetlb_state(काष्ठा page *oldpage, काष्ठा page *newpage, पूर्णांक reason);
व्योम मुक्त_huge_page(काष्ठा page *page);
व्योम hugetlb_fix_reserve_counts(काष्ठा inode *inode);
बाह्य काष्ठा mutex *hugetlb_fault_mutex_table;
u32 hugetlb_fault_mutex_hash(काष्ठा address_space *mapping, pgoff_t idx);

pte_t *huge_pmd_share(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma,
		      अचिन्हित दीर्घ addr, pud_t *pud);

काष्ठा address_space *hugetlb_page_mapping_lock_ग_लिखो(काष्ठा page *hpage);

बाह्य पूर्णांक sysctl_hugetlb_shm_group;
बाह्य काष्ठा list_head huge_boot_pages;

/* arch callbacks */

pte_t *huge_pte_alloc(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma,
			अचिन्हित दीर्घ addr, अचिन्हित दीर्घ sz);
pte_t *huge_pte_offset(काष्ठा mm_काष्ठा *mm,
		       अचिन्हित दीर्घ addr, अचिन्हित दीर्घ sz);
पूर्णांक huge_pmd_unshare(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma,
				अचिन्हित दीर्घ *addr, pte_t *ptep);
व्योम adjust_range_अगर_pmd_sharing_possible(काष्ठा vm_area_काष्ठा *vma,
				अचिन्हित दीर्घ *start, अचिन्हित दीर्घ *end);
काष्ठा page *follow_huge_addr(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ address,
			      पूर्णांक ग_लिखो);
काष्ठा page *follow_huge_pd(काष्ठा vm_area_काष्ठा *vma,
			    अचिन्हित दीर्घ address, hugepd_t hpd,
			    पूर्णांक flags, पूर्णांक pdshअगरt);
काष्ठा page *follow_huge_pmd(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ address,
				pmd_t *pmd, पूर्णांक flags);
काष्ठा page *follow_huge_pud(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ address,
				pud_t *pud, पूर्णांक flags);
काष्ठा page *follow_huge_pgd(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ address,
			     pgd_t *pgd, पूर्णांक flags);

पूर्णांक pmd_huge(pmd_t pmd);
पूर्णांक pud_huge(pud_t pud);
अचिन्हित दीर्घ hugetlb_change_protection(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ address, अचिन्हित दीर्घ end, pgprot_t newprot);

bool is_hugetlb_entry_migration(pte_t pte);
व्योम hugetlb_unshare_all_pmds(काष्ठा vm_area_काष्ठा *vma);

#अन्यथा /* !CONFIG_HUGETLB_PAGE */

अटल अंतरभूत व्योम reset_vma_resv_huge_pages(काष्ठा vm_area_काष्ठा *vma)
अणु
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ hugetlb_total_pages(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा address_space *hugetlb_page_mapping_lock_ग_लिखो(
							काष्ठा page *hpage)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक huge_pmd_unshare(काष्ठा mm_काष्ठा *mm,
					काष्ठा vm_area_काष्ठा *vma,
					अचिन्हित दीर्घ *addr, pte_t *ptep)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम adjust_range_अगर_pmd_sharing_possible(
				काष्ठा vm_area_काष्ठा *vma,
				अचिन्हित दीर्घ *start, अचिन्हित दीर्घ *end)
अणु
पूर्ण

अटल अंतरभूत दीर्घ follow_hugetlb_page(काष्ठा mm_काष्ठा *mm,
			काष्ठा vm_area_काष्ठा *vma, काष्ठा page **pages,
			काष्ठा vm_area_काष्ठा **vmas, अचिन्हित दीर्घ *position,
			अचिन्हित दीर्घ *nr_pages, दीर्घ i, अचिन्हित पूर्णांक flags,
			पूर्णांक *nonblocking)
अणु
	BUG();
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा page *follow_huge_addr(काष्ठा mm_काष्ठा *mm,
					अचिन्हित दीर्घ address, पूर्णांक ग_लिखो)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल अंतरभूत पूर्णांक copy_hugetlb_page_range(काष्ठा mm_काष्ठा *dst,
			काष्ठा mm_काष्ठा *src, काष्ठा vm_area_काष्ठा *vma)
अणु
	BUG();
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम hugetlb_report_meminfo(काष्ठा seq_file *m)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक hugetlb_report_node_meminfo(अक्षर *buf, पूर्णांक len, पूर्णांक nid)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम hugetlb_show_meminfo(व्योम)
अणु
पूर्ण

अटल अंतरभूत काष्ठा page *follow_huge_pd(काष्ठा vm_area_काष्ठा *vma,
				अचिन्हित दीर्घ address, hugepd_t hpd, पूर्णांक flags,
				पूर्णांक pdshअगरt)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा page *follow_huge_pmd(काष्ठा mm_काष्ठा *mm,
				अचिन्हित दीर्घ address, pmd_t *pmd, पूर्णांक flags)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा page *follow_huge_pud(काष्ठा mm_काष्ठा *mm,
				अचिन्हित दीर्घ address, pud_t *pud, पूर्णांक flags)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा page *follow_huge_pgd(काष्ठा mm_काष्ठा *mm,
				अचिन्हित दीर्घ address, pgd_t *pgd, पूर्णांक flags)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक prepare_hugepage_range(काष्ठा file *file,
				अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक pmd_huge(pmd_t pmd)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pud_huge(pud_t pud)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक is_hugepage_only_range(काष्ठा mm_काष्ठा *mm,
					अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम hugetlb_मुक्त_pgd_range(काष्ठा mmu_gather *tlb,
				अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
				अचिन्हित दीर्घ न्यूनमान, अचिन्हित दीर्घ उच्चमानing)
अणु
	BUG();
पूर्ण

#अगर_घोषित CONFIG_USERFAULTFD
अटल अंतरभूत पूर्णांक hugetlb_mcopy_atomic_pte(काष्ठा mm_काष्ठा *dst_mm,
						pte_t *dst_pte,
						काष्ठा vm_area_काष्ठा *dst_vma,
						अचिन्हित दीर्घ dst_addr,
						अचिन्हित दीर्घ src_addr,
						क्रमागत mcopy_atomic_mode mode,
						काष्ठा page **pagep)
अणु
	BUG();
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_USERFAULTFD */

अटल अंतरभूत pte_t *huge_pte_offset(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
					अचिन्हित दीर्घ sz)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत bool isolate_huge_page(काष्ठा page *page, काष्ठा list_head *list)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक get_hwpoison_huge_page(काष्ठा page *page, bool *hugetlb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम putback_active_hugepage(काष्ठा page *page)
अणु
पूर्ण

अटल अंतरभूत व्योम move_hugetlb_state(काष्ठा page *oldpage,
					काष्ठा page *newpage, पूर्णांक reason)
अणु
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ hugetlb_change_protection(
			काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
			अचिन्हित दीर्घ end, pgprot_t newprot)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम __unmap_hugepage_range_final(काष्ठा mmu_gather *tlb,
			काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
			अचिन्हित दीर्घ end, काष्ठा page *ref_page)
अणु
	BUG();
पूर्ण

अटल अंतरभूत व्योम __unmap_hugepage_range(काष्ठा mmu_gather *tlb,
			काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
			अचिन्हित दीर्घ end, काष्ठा page *ref_page)
अणु
	BUG();
पूर्ण

अटल अंतरभूत vm_fault_t hugetlb_fault(काष्ठा mm_काष्ठा *mm,
			काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
			अचिन्हित पूर्णांक flags)
अणु
	BUG();
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम hugetlb_unshare_all_pmds(काष्ठा vm_area_काष्ठा *vma) अणु पूर्ण

#पूर्ण_अगर /* !CONFIG_HUGETLB_PAGE */
/*
 * hugepages at page global directory. If arch support
 * hugepages at pgd level, they need to define this.
 */
#अगर_अघोषित pgd_huge
#घोषणा pgd_huge(x)	0
#पूर्ण_अगर
#अगर_अघोषित p4d_huge
#घोषणा p4d_huge(x)	0
#पूर्ण_अगर

#अगर_अघोषित pgd_ग_लिखो
अटल अंतरभूत पूर्णांक pgd_ग_लिखो(pgd_t pgd)
अणु
	BUG();
	वापस 0;
पूर्ण
#पूर्ण_अगर

#घोषणा HUGETLB_ANON_खाता "anon_hugepage"

क्रमागत अणु
	/*
	 * The file will be used as an shm file so shmfs accounting rules
	 * apply
	 */
	HUGETLB_SHMFS_INODE     = 1,
	/*
	 * The file is being created on the पूर्णांकernal vfs mount and shmfs
	 * accounting rules करो not apply
	 */
	HUGETLB_ANONHUGE_INODE  = 2,
पूर्ण;

#अगर_घोषित CONFIG_HUGETLBFS
काष्ठा hugetlbfs_sb_info अणु
	दीर्घ	max_inodes;   /* inodes allowed */
	दीर्घ	मुक्त_inodes;  /* inodes मुक्त */
	spinlock_t	stat_lock;
	काष्ठा hstate *hstate;
	काष्ठा hugepage_subpool *spool;
	kuid_t	uid;
	kgid_t	gid;
	umode_t mode;
पूर्ण;

अटल अंतरभूत काष्ठा hugetlbfs_sb_info *HUGETLBFS_SB(काष्ठा super_block *sb)
अणु
	वापस sb->s_fs_info;
पूर्ण

काष्ठा hugetlbfs_inode_info अणु
	काष्ठा shared_policy policy;
	काष्ठा inode vfs_inode;
	अचिन्हित पूर्णांक seals;
पूर्ण;

अटल अंतरभूत काष्ठा hugetlbfs_inode_info *HUGETLBFS_I(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा hugetlbfs_inode_info, vfs_inode);
पूर्ण

बाह्य स्थिर काष्ठा file_operations hugetlbfs_file_operations;
बाह्य स्थिर काष्ठा vm_operations_काष्ठा hugetlb_vm_ops;
काष्ठा file *hugetlb_file_setup(स्थिर अक्षर *name, माप_प्रकार size, vm_flags_t acct,
				काष्ठा user_काष्ठा **user, पूर्णांक creat_flags,
				पूर्णांक page_size_log);

अटल अंतरभूत bool is_file_hugepages(काष्ठा file *file)
अणु
	अगर (file->f_op == &hugetlbfs_file_operations)
		वापस true;

	वापस is_file_shm_hugepages(file);
पूर्ण

अटल अंतरभूत काष्ठा hstate *hstate_inode(काष्ठा inode *i)
अणु
	वापस HUGETLBFS_SB(i->i_sb)->hstate;
पूर्ण
#अन्यथा /* !CONFIG_HUGETLBFS */

#घोषणा is_file_hugepages(file)			false
अटल अंतरभूत काष्ठा file *
hugetlb_file_setup(स्थिर अक्षर *name, माप_प्रकार size, vm_flags_t acctflag,
		काष्ठा user_काष्ठा **user, पूर्णांक creat_flags,
		पूर्णांक page_size_log)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

अटल अंतरभूत काष्ठा hstate *hstate_inode(काष्ठा inode *i)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* !CONFIG_HUGETLBFS */

#अगर_घोषित HAVE_ARCH_HUGETLB_UNMAPPED_AREA
अचिन्हित दीर्घ hugetlb_get_unmapped_area(काष्ठा file *file, अचिन्हित दीर्घ addr,
					अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff,
					अचिन्हित दीर्घ flags);
#पूर्ण_अगर /* HAVE_ARCH_HUGETLB_UNMAPPED_AREA */

/*
 * huegtlb page specअगरic state flags.  These flags are located in page.निजी
 * of the hugetlb head page.  Functions created via the below macros should be
 * used to manipulate these flags.
 *
 * HPG_restore_reserve - Set when a hugetlb page consumes a reservation at
 *	allocation समय.  Cleared when page is fully instantiated.  Free
 *	routine checks flag to restore a reservation on error paths.
 *	Synchronization:  Examined or modअगरied by code that knows it has
 *	the only reference to page.  i.e. After allocation but beक्रमe use
 *	or when the page is being मुक्तd.
 * HPG_migratable  - Set after a newly allocated page is added to the page
 *	cache and/or page tables.  Indicates the page is a candidate क्रम
 *	migration.
 *	Synchronization:  Initially set after new page allocation with no
 *	locking.  When examined and modअगरied during migration processing
 *	(isolate, migrate, putback) the hugetlb_lock is held.
 * HPG_temporary - - Set on a page that is temporarily allocated from the buddy
 *	allocator.  Typically used क्रम migration target pages when no pages
 *	are available in the pool.  The hugetlb मुक्त page path will
 *	immediately मुक्त pages with this flag set to the buddy allocator.
 *	Synchronization: Can be set after huge page allocation from buddy when
 *	code knows it has only reference.  All other examinations and
 *	modअगरications require hugetlb_lock.
 * HPG_मुक्तd - Set when page is on the मुक्त lists.
 *	Synchronization: hugetlb_lock held क्रम examination and modअगरication.
 */
क्रमागत hugetlb_page_flags अणु
	HPG_restore_reserve = 0,
	HPG_migratable,
	HPG_temporary,
	HPG_मुक्तd,
	__NR_HPAGEFLAGS,
पूर्ण;

/*
 * Macros to create test, set and clear function definitions क्रम
 * hugetlb specअगरic page flags.
 */
#अगर_घोषित CONFIG_HUGETLB_PAGE
#घोषणा TESTHPAGEFLAG(uname, flname)				\
अटल अंतरभूत पूर्णांक HPage##uname(काष्ठा page *page)		\
	अणु वापस test_bit(HPG_##flname, &(page->निजी)); पूर्ण

#घोषणा SETHPAGEFLAG(uname, flname)				\
अटल अंतरभूत व्योम SetHPage##uname(काष्ठा page *page)		\
	अणु set_bit(HPG_##flname, &(page->निजी)); पूर्ण

#घोषणा CLEARHPAGEFLAG(uname, flname)				\
अटल अंतरभूत व्योम ClearHPage##uname(काष्ठा page *page)		\
	अणु clear_bit(HPG_##flname, &(page->निजी)); पूर्ण
#अन्यथा
#घोषणा TESTHPAGEFLAG(uname, flname)				\
अटल अंतरभूत पूर्णांक HPage##uname(काष्ठा page *page)		\
	अणु वापस 0; पूर्ण

#घोषणा SETHPAGEFLAG(uname, flname)				\
अटल अंतरभूत व्योम SetHPage##uname(काष्ठा page *page)		\
	अणु पूर्ण

#घोषणा CLEARHPAGEFLAG(uname, flname)				\
अटल अंतरभूत व्योम ClearHPage##uname(काष्ठा page *page)		\
	अणु पूर्ण
#पूर्ण_अगर

#घोषणा HPAGEFLAG(uname, flname)				\
	TESTHPAGEFLAG(uname, flname)				\
	SETHPAGEFLAG(uname, flname)				\
	CLEARHPAGEFLAG(uname, flname)				\

/*
 * Create functions associated with hugetlb page flags
 */
HPAGEFLAG(RestoreReserve, restore_reserve)
HPAGEFLAG(Migratable, migratable)
HPAGEFLAG(Temporary, temporary)
HPAGEFLAG(Freed, मुक्तd)

#अगर_घोषित CONFIG_HUGETLB_PAGE

#घोषणा HSTATE_NAME_LEN 32
/* Defines one hugetlb page size */
काष्ठा hstate अणु
	काष्ठा mutex resize_lock;
	पूर्णांक next_nid_to_alloc;
	पूर्णांक next_nid_to_मुक्त;
	अचिन्हित पूर्णांक order;
	अचिन्हित दीर्घ mask;
	अचिन्हित दीर्घ max_huge_pages;
	अचिन्हित दीर्घ nr_huge_pages;
	अचिन्हित दीर्घ मुक्त_huge_pages;
	अचिन्हित दीर्घ resv_huge_pages;
	अचिन्हित दीर्घ surplus_huge_pages;
	अचिन्हित दीर्घ nr_overcommit_huge_pages;
	काष्ठा list_head hugepage_activelist;
	काष्ठा list_head hugepage_मुक्तlists[MAX_NUMNODES];
	अचिन्हित पूर्णांक nr_huge_pages_node[MAX_NUMNODES];
	अचिन्हित पूर्णांक मुक्त_huge_pages_node[MAX_NUMNODES];
	अचिन्हित पूर्णांक surplus_huge_pages_node[MAX_NUMNODES];
#अगर_घोषित CONFIG_CGROUP_HUGETLB
	/* cgroup control files */
	काष्ठा cftype cgroup_files_dfl[7];
	काष्ठा cftype cgroup_files_legacy[9];
#पूर्ण_अगर
	अक्षर name[HSTATE_NAME_LEN];
पूर्ण;

काष्ठा huge_booपंचांगem_page अणु
	काष्ठा list_head list;
	काष्ठा hstate *hstate;
पूर्ण;

पूर्णांक isolate_or_dissolve_huge_page(काष्ठा page *page, काष्ठा list_head *list);
काष्ठा page *alloc_huge_page(काष्ठा vm_area_काष्ठा *vma,
				अचिन्हित दीर्घ addr, पूर्णांक aव्योम_reserve);
काष्ठा page *alloc_huge_page_nodemask(काष्ठा hstate *h, पूर्णांक preferred_nid,
				nodemask_t *nmask, gfp_t gfp_mask);
काष्ठा page *alloc_huge_page_vma(काष्ठा hstate *h, काष्ठा vm_area_काष्ठा *vma,
				अचिन्हित दीर्घ address);
पूर्णांक huge_add_to_page_cache(काष्ठा page *page, काष्ठा address_space *mapping,
			pgoff_t idx);
व्योम restore_reserve_on_error(काष्ठा hstate *h, काष्ठा vm_area_काष्ठा *vma,
				अचिन्हित दीर्घ address, काष्ठा page *page);

/* arch callback */
पूर्णांक __init __alloc_booपंचांगem_huge_page(काष्ठा hstate *h);
पूर्णांक __init alloc_booपंचांगem_huge_page(काष्ठा hstate *h);

व्योम __init hugetlb_add_hstate(अचिन्हित order);
bool __init arch_hugetlb_valid_size(अचिन्हित दीर्घ size);
काष्ठा hstate *माप_प्रकारo_hstate(अचिन्हित दीर्घ size);

#अगर_अघोषित HUGE_MAX_HSTATE
#घोषणा HUGE_MAX_HSTATE 1
#पूर्ण_अगर

बाह्य काष्ठा hstate hstates[HUGE_MAX_HSTATE];
बाह्य अचिन्हित पूर्णांक शेष_hstate_idx;

#घोषणा शेष_hstate (hstates[शेष_hstate_idx])

/*
 * hugetlb page subpool poपूर्णांकer located in hpage[1].निजी
 */
अटल अंतरभूत काष्ठा hugepage_subpool *hugetlb_page_subpool(काष्ठा page *hpage)
अणु
	वापस (काष्ठा hugepage_subpool *)(hpage+1)->निजी;
पूर्ण

अटल अंतरभूत व्योम hugetlb_set_page_subpool(काष्ठा page *hpage,
					काष्ठा hugepage_subpool *subpool)
अणु
	set_page_निजी(hpage+1, (अचिन्हित दीर्घ)subpool);
पूर्ण

अटल अंतरभूत काष्ठा hstate *hstate_file(काष्ठा file *f)
अणु
	वापस hstate_inode(file_inode(f));
पूर्ण

अटल अंतरभूत काष्ठा hstate *hstate_sizelog(पूर्णांक page_size_log)
अणु
	अगर (!page_size_log)
		वापस &शेष_hstate;

	वापस माप_प्रकारo_hstate(1UL << page_size_log);
पूर्ण

अटल अंतरभूत काष्ठा hstate *hstate_vma(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस hstate_file(vma->vm_file);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ huge_page_size(काष्ठा hstate *h)
अणु
	वापस (अचिन्हित दीर्घ)PAGE_SIZE << h->order;
पूर्ण

बाह्य अचिन्हित दीर्घ vma_kernel_pagesize(काष्ठा vm_area_काष्ठा *vma);

बाह्य अचिन्हित दीर्घ vma_mmu_pagesize(काष्ठा vm_area_काष्ठा *vma);

अटल अंतरभूत अचिन्हित दीर्घ huge_page_mask(काष्ठा hstate *h)
अणु
	वापस h->mask;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक huge_page_order(काष्ठा hstate *h)
अणु
	वापस h->order;
पूर्ण

अटल अंतरभूत अचिन्हित huge_page_shअगरt(काष्ठा hstate *h)
अणु
	वापस h->order + PAGE_SHIFT;
पूर्ण

अटल अंतरभूत bool hstate_is_gigantic(काष्ठा hstate *h)
अणु
	वापस huge_page_order(h) >= MAX_ORDER;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक pages_per_huge_page(काष्ठा hstate *h)
अणु
	वापस 1 << h->order;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक blocks_per_huge_page(काष्ठा hstate *h)
अणु
	वापस huge_page_size(h) / 512;
पूर्ण

#समावेश <यंत्र/hugetlb.h>

#अगर_अघोषित is_hugepage_only_range
अटल अंतरभूत पूर्णांक is_hugepage_only_range(काष्ठा mm_काष्ठा *mm,
					अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len)
अणु
	वापस 0;
पूर्ण
#घोषणा is_hugepage_only_range is_hugepage_only_range
#पूर्ण_अगर

#अगर_अघोषित arch_clear_hugepage_flags
अटल अंतरभूत व्योम arch_clear_hugepage_flags(काष्ठा page *page) अणु पूर्ण
#घोषणा arch_clear_hugepage_flags arch_clear_hugepage_flags
#पूर्ण_अगर

#अगर_अघोषित arch_make_huge_pte
अटल अंतरभूत pte_t arch_make_huge_pte(pte_t entry, काष्ठा vm_area_काष्ठा *vma,
				       काष्ठा page *page, पूर्णांक writable)
अणु
	वापस entry;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत काष्ठा hstate *page_hstate(काष्ठा page *page)
अणु
	VM_BUG_ON_PAGE(!PageHuge(page), page);
	वापस माप_प्रकारo_hstate(page_size(page));
पूर्ण

अटल अंतरभूत अचिन्हित hstate_index_to_shअगरt(अचिन्हित index)
अणु
	वापस hstates[index].order + PAGE_SHIFT;
पूर्ण

अटल अंतरभूत पूर्णांक hstate_index(काष्ठा hstate *h)
अणु
	वापस h - hstates;
पूर्ण

pgoff_t __basepage_index(काष्ठा page *page);

/* Return page->index in PAGE_SIZE units */
अटल अंतरभूत pgoff_t basepage_index(काष्ठा page *page)
अणु
	अगर (!PageCompound(page))
		वापस page->index;

	वापस __basepage_index(page);
पूर्ण

बाह्य पूर्णांक dissolve_मुक्त_huge_page(काष्ठा page *page);
बाह्य पूर्णांक dissolve_मुक्त_huge_pages(अचिन्हित दीर्घ start_pfn,
				    अचिन्हित दीर्घ end_pfn);

#अगर_घोषित CONFIG_ARCH_ENABLE_HUGEPAGE_MIGRATION
#अगर_अघोषित arch_hugetlb_migration_supported
अटल अंतरभूत bool arch_hugetlb_migration_supported(काष्ठा hstate *h)
अणु
	अगर ((huge_page_shअगरt(h) == PMD_SHIFT) ||
		(huge_page_shअगरt(h) == PUD_SHIFT) ||
			(huge_page_shअगरt(h) == PGसूची_SHIFT))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण
#पूर्ण_अगर
#अन्यथा
अटल अंतरभूत bool arch_hugetlb_migration_supported(काष्ठा hstate *h)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool hugepage_migration_supported(काष्ठा hstate *h)
अणु
	वापस arch_hugetlb_migration_supported(h);
पूर्ण

/*
 * Movability check is dअगरferent as compared to migration check.
 * It determines whether or not a huge page should be placed on
 * movable zone or not. Movability of any huge page should be
 * required only अगर huge page size is supported क्रम migration.
 * There wont be any reason क्रम the huge page to be movable अगर
 * it is not migratable to start with. Also the size of the huge
 * page should be large enough to be placed under a movable zone
 * and still feasible enough to be migratable. Just the presence
 * in movable zone करोes not make the migration feasible.
 *
 * So even though large huge page sizes like the gigantic ones
 * are migratable they should not be movable because its not
 * feasible to migrate them from movable zone.
 */
अटल अंतरभूत bool hugepage_movable_supported(काष्ठा hstate *h)
अणु
	अगर (!hugepage_migration_supported(h))
		वापस false;

	अगर (hstate_is_gigantic(h))
		वापस false;
	वापस true;
पूर्ण

/* Movability of hugepages depends on migration support. */
अटल अंतरभूत gfp_t htlb_alloc_mask(काष्ठा hstate *h)
अणु
	अगर (hugepage_movable_supported(h))
		वापस GFP_HIGHUSER_MOVABLE;
	अन्यथा
		वापस GFP_HIGHUSER;
पूर्ण

अटल अंतरभूत gfp_t htlb_modअगरy_alloc_mask(काष्ठा hstate *h, gfp_t gfp_mask)
अणु
	gfp_t modअगरied_mask = htlb_alloc_mask(h);

	/* Some callers might want to enक्रमce node */
	modअगरied_mask |= (gfp_mask & __GFP_THISNODE);

	modअगरied_mask |= (gfp_mask & __GFP_NOWARN);

	वापस modअगरied_mask;
पूर्ण

अटल अंतरभूत spinlock_t *huge_pte_lockptr(काष्ठा hstate *h,
					   काष्ठा mm_काष्ठा *mm, pte_t *pte)
अणु
	अगर (huge_page_size(h) == PMD_SIZE)
		वापस pmd_lockptr(mm, (pmd_t *) pte);
	VM_BUG_ON(huge_page_size(h) == PAGE_SIZE);
	वापस &mm->page_table_lock;
पूर्ण

#अगर_अघोषित hugepages_supported
/*
 * Some platक्रमm decide whether they support huge pages at boot
 * समय. Some of them, such as घातerpc, set HPAGE_SHIFT to 0
 * when there is no such support
 */
#घोषणा hugepages_supported() (HPAGE_SHIFT != 0)
#पूर्ण_अगर

व्योम hugetlb_report_usage(काष्ठा seq_file *m, काष्ठा mm_काष्ठा *mm);

अटल अंतरभूत व्योम hugetlb_count_add(दीर्घ l, काष्ठा mm_काष्ठा *mm)
अणु
	atomic_दीर्घ_add(l, &mm->hugetlb_usage);
पूर्ण

अटल अंतरभूत व्योम hugetlb_count_sub(दीर्घ l, काष्ठा mm_काष्ठा *mm)
अणु
	atomic_दीर्घ_sub(l, &mm->hugetlb_usage);
पूर्ण

#अगर_अघोषित set_huge_swap_pte_at
अटल अंतरभूत व्योम set_huge_swap_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
					pte_t *ptep, pte_t pte, अचिन्हित दीर्घ sz)
अणु
	set_huge_pte_at(mm, addr, ptep, pte);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित huge_ptep_modअगरy_prot_start
#घोषणा huge_ptep_modअगरy_prot_start huge_ptep_modअगरy_prot_start
अटल अंतरभूत pte_t huge_ptep_modअगरy_prot_start(काष्ठा vm_area_काष्ठा *vma,
						अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	वापस huge_ptep_get_and_clear(vma->vm_mm, addr, ptep);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित huge_ptep_modअगरy_prot_commit
#घोषणा huge_ptep_modअगरy_prot_commit huge_ptep_modअगरy_prot_commit
अटल अंतरभूत व्योम huge_ptep_modअगरy_prot_commit(काष्ठा vm_area_काष्ठा *vma,
						अचिन्हित दीर्घ addr, pte_t *ptep,
						pte_t old_pte, pte_t pte)
अणु
	set_huge_pte_at(vma->vm_mm, addr, ptep, pte);
पूर्ण
#पूर्ण_अगर

#अन्यथा	/* CONFIG_HUGETLB_PAGE */
काष्ठा hstate अणुपूर्ण;

अटल अंतरभूत पूर्णांक isolate_or_dissolve_huge_page(काष्ठा page *page,
						काष्ठा list_head *list)
अणु
	वापस -ENOMEM;
पूर्ण

अटल अंतरभूत काष्ठा page *alloc_huge_page(काष्ठा vm_area_काष्ठा *vma,
					   अचिन्हित दीर्घ addr,
					   पूर्णांक aव्योम_reserve)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा page *
alloc_huge_page_nodemask(काष्ठा hstate *h, पूर्णांक preferred_nid,
			nodemask_t *nmask, gfp_t gfp_mask)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा page *alloc_huge_page_vma(काष्ठा hstate *h,
					       काष्ठा vm_area_काष्ठा *vma,
					       अचिन्हित दीर्घ address)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक __alloc_booपंचांगem_huge_page(काष्ठा hstate *h)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा hstate *hstate_file(काष्ठा file *f)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा hstate *hstate_sizelog(पूर्णांक page_size_log)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा hstate *hstate_vma(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा hstate *page_hstate(काष्ठा page *page)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ huge_page_size(काष्ठा hstate *h)
अणु
	वापस PAGE_SIZE;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ huge_page_mask(काष्ठा hstate *h)
अणु
	वापस PAGE_MASK;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ vma_kernel_pagesize(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस PAGE_SIZE;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ vma_mmu_pagesize(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस PAGE_SIZE;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक huge_page_order(काष्ठा hstate *h)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक huge_page_shअगरt(काष्ठा hstate *h)
अणु
	वापस PAGE_SHIFT;
पूर्ण

अटल अंतरभूत bool hstate_is_gigantic(काष्ठा hstate *h)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक pages_per_huge_page(काष्ठा hstate *h)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत अचिन्हित hstate_index_to_shअगरt(अचिन्हित index)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक hstate_index(काष्ठा hstate *h)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत pgoff_t basepage_index(काष्ठा page *page)
अणु
	वापस page->index;
पूर्ण

अटल अंतरभूत पूर्णांक dissolve_मुक्त_huge_page(काष्ठा page *page)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक dissolve_मुक्त_huge_pages(अचिन्हित दीर्घ start_pfn,
					   अचिन्हित दीर्घ end_pfn)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool hugepage_migration_supported(काष्ठा hstate *h)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool hugepage_movable_supported(काष्ठा hstate *h)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत gfp_t htlb_alloc_mask(काष्ठा hstate *h)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत gfp_t htlb_modअगरy_alloc_mask(काष्ठा hstate *h, gfp_t gfp_mask)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत spinlock_t *huge_pte_lockptr(काष्ठा hstate *h,
					   काष्ठा mm_काष्ठा *mm, pte_t *pte)
अणु
	वापस &mm->page_table_lock;
पूर्ण

अटल अंतरभूत व्योम hugetlb_report_usage(काष्ठा seq_file *f, काष्ठा mm_काष्ठा *m)
अणु
पूर्ण

अटल अंतरभूत व्योम hugetlb_count_sub(दीर्घ l, काष्ठा mm_काष्ठा *mm)
अणु
पूर्ण

अटल अंतरभूत व्योम set_huge_swap_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
					pte_t *ptep, pte_t pte, अचिन्हित दीर्घ sz)
अणु
पूर्ण
#पूर्ण_अगर	/* CONFIG_HUGETLB_PAGE */

अटल अंतरभूत spinlock_t *huge_pte_lock(काष्ठा hstate *h,
					काष्ठा mm_काष्ठा *mm, pte_t *pte)
अणु
	spinlock_t *ptl;

	ptl = huge_pte_lockptr(h, mm, pte);
	spin_lock(ptl);
	वापस ptl;
पूर्ण

#अगर defined(CONFIG_HUGETLB_PAGE) && defined(CONFIG_CMA)
बाह्य व्योम __init hugetlb_cma_reserve(पूर्णांक order);
बाह्य व्योम __init hugetlb_cma_check(व्योम);
#अन्यथा
अटल अंतरभूत __init व्योम hugetlb_cma_reserve(पूर्णांक order)
अणु
पूर्ण
अटल अंतरभूत __init व्योम hugetlb_cma_check(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

bool want_pmd_share(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr);

#अगर_अघोषित __HAVE_ARCH_FLUSH_HUGETLB_TLB_RANGE
/*
 * ARCHes with special requirements क्रम evicting HUGETLB backing TLB entries can
 * implement this.
 */
#घोषणा flush_hugetlb_tlb_range(vma, addr, end)	flush_tlb_range(vma, addr, end)
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_HUGETLB_H */
