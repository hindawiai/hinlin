<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/memblock.h>
#समावेश <linux/compiler.h>
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/ksm.h>
#समावेश <linux/mm.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/huge_mm.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/memcontrol.h>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/page_idle.h>
#समावेश <linux/kernel-page-flags.h>
#समावेश <linux/uaccess.h>
#समावेश "internal.h"

#घोषणा KPMSIZE माप(u64)
#घोषणा KPMMASK (KPMSIZE - 1)
#घोषणा KPMBITS (KPMSIZE * BITS_PER_BYTE)

अटल अंतरभूत अचिन्हित दीर्घ get_max_dump_pfn(व्योम)
अणु
#अगर_घोषित CONFIG_SPARSEMEM
	/*
	 * The memmap of early sections is completely populated and marked
	 * online even अगर max_pfn करोes not fall on a section boundary -
	 * pfn_to_online_page() will succeed on all pages. Allow inspecting
	 * these memmaps.
	 */
	वापस round_up(max_pfn, PAGES_PER_SECTION);
#अन्यथा
	वापस max_pfn;
#पूर्ण_अगर
पूर्ण

/* /proc/kpagecount - an array exposing page counts
 *
 * Each entry is a u64 representing the corresponding
 * physical page count.
 */
अटल sमाप_प्रकार kpagecount_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			     माप_प्रकार count, loff_t *ppos)
अणु
	स्थिर अचिन्हित दीर्घ max_dump_pfn = get_max_dump_pfn();
	u64 __user *out = (u64 __user *)buf;
	काष्ठा page *ppage;
	अचिन्हित दीर्घ src = *ppos;
	अचिन्हित दीर्घ pfn;
	sमाप_प्रकार ret = 0;
	u64 pcount;

	pfn = src / KPMSIZE;
	अगर (src & KPMMASK || count & KPMMASK)
		वापस -EINVAL;
	अगर (src >= max_dump_pfn * KPMSIZE)
		वापस 0;
	count = min_t(अचिन्हित दीर्घ, count, (max_dump_pfn * KPMSIZE) - src);

	जबतक (count > 0) अणु
		/*
		 * TODO: ZONE_DEVICE support requires to identअगरy
		 * memmaps that were actually initialized.
		 */
		ppage = pfn_to_online_page(pfn);

		अगर (!ppage || PageSlab(ppage) || page_has_type(ppage))
			pcount = 0;
		अन्यथा
			pcount = page_mapcount(ppage);

		अगर (put_user(pcount, out)) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण

		pfn++;
		out++;
		count -= KPMSIZE;

		cond_resched();
	पूर्ण

	*ppos += (अक्षर __user *)out - buf;
	अगर (!ret)
		ret = (अक्षर __user *)out - buf;
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा proc_ops kpagecount_proc_ops = अणु
	.proc_lseek	= mem_lseek,
	.proc_पढ़ो	= kpagecount_पढ़ो,
पूर्ण;

/* /proc/kpageflags - an array exposing page flags
 *
 * Each entry is a u64 representing the corresponding
 * physical page flags.
 */

अटल अंतरभूत u64 kpf_copy_bit(u64 kflags, पूर्णांक ubit, पूर्णांक kbit)
अणु
	वापस ((kflags >> kbit) & 1) << ubit;
पूर्ण

u64 stable_page_flags(काष्ठा page *page)
अणु
	u64 k;
	u64 u;

	/*
	 * pseuकरो flag: KPF_NOPAGE
	 * it dअगरferentiates a memory hole from a page with no flags
	 */
	अगर (!page)
		वापस 1 << KPF_NOPAGE;

	k = page->flags;
	u = 0;

	/*
	 * pseuकरो flags क्रम the well known (anonymous) memory mapped pages
	 *
	 * Note that page->_mapcount is overloaded in SLOB/SLUB/SLQB, so the
	 * simple test in page_mapped() is not enough.
	 */
	अगर (!PageSlab(page) && page_mapped(page))
		u |= 1 << KPF_MMAP;
	अगर (PageAnon(page))
		u |= 1 << KPF_ANON;
	अगर (PageKsm(page))
		u |= 1 << KPF_KSM;

	/*
	 * compound pages: export both head/tail info
	 * they together define a compound page's start/end pos and order
	 */
	अगर (PageHead(page))
		u |= 1 << KPF_COMPOUND_HEAD;
	अगर (PageTail(page))
		u |= 1 << KPF_COMPOUND_TAIL;
	अगर (PageHuge(page))
		u |= 1 << KPF_HUGE;
	/*
	 * PageTransCompound can be true क्रम non-huge compound pages (slab
	 * pages or pages allocated by drivers with __GFP_COMP) because it
	 * just checks PG_head/PG_tail, so we need to check PageLRU/PageAnon
	 * to make sure a given page is a thp, not a non-huge compound page.
	 */
	अन्यथा अगर (PageTransCompound(page)) अणु
		काष्ठा page *head = compound_head(page);

		अगर (PageLRU(head) || PageAnon(head))
			u |= 1 << KPF_THP;
		अन्यथा अगर (is_huge_zero_page(head)) अणु
			u |= 1 << KPF_ZERO_PAGE;
			u |= 1 << KPF_THP;
		पूर्ण
	पूर्ण अन्यथा अगर (is_zero_pfn(page_to_pfn(page)))
		u |= 1 << KPF_ZERO_PAGE;


	/*
	 * Caveats on high order pages: page->_refcount will only be set
	 * -1 on the head page; SLUB/SLQB करो the same क्रम PG_slab;
	 * SLOB won't set PG_slab at all on compound pages.
	 */
	अगर (PageBuddy(page))
		u |= 1 << KPF_BUDDY;
	अन्यथा अगर (page_count(page) == 0 && is_मुक्त_buddy_page(page))
		u |= 1 << KPF_BUDDY;

	अगर (PageOffline(page))
		u |= 1 << KPF_OFFLINE;
	अगर (PageTable(page))
		u |= 1 << KPF_PGTABLE;

	अगर (page_is_idle(page))
		u |= 1 << KPF_IDLE;

	u |= kpf_copy_bit(k, KPF_LOCKED,	PG_locked);

	u |= kpf_copy_bit(k, KPF_SLAB,		PG_slab);
	अगर (PageTail(page) && PageSlab(compound_head(page)))
		u |= 1 << KPF_SLAB;

	u |= kpf_copy_bit(k, KPF_ERROR,		PG_error);
	u |= kpf_copy_bit(k, KPF_सूचीTY,		PG_dirty);
	u |= kpf_copy_bit(k, KPF_UPTODATE,	PG_uptodate);
	u |= kpf_copy_bit(k, KPF_WRITEBACK,	PG_ग_लिखोback);

	u |= kpf_copy_bit(k, KPF_LRU,		PG_lru);
	u |= kpf_copy_bit(k, KPF_REFERENCED,	PG_referenced);
	u |= kpf_copy_bit(k, KPF_ACTIVE,	PG_active);
	u |= kpf_copy_bit(k, KPF_RECLAIM,	PG_reclaim);

	अगर (PageSwapCache(page))
		u |= 1 << KPF_SWAPCACHE;
	u |= kpf_copy_bit(k, KPF_SWAPBACKED,	PG_swapbacked);

	u |= kpf_copy_bit(k, KPF_UNEVICTABLE,	PG_unevictable);
	u |= kpf_copy_bit(k, KPF_MLOCKED,	PG_mlocked);

#अगर_घोषित CONFIG_MEMORY_FAILURE
	u |= kpf_copy_bit(k, KPF_HWPOISON,	PG_hwpoison);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_USES_PG_UNCACHED
	u |= kpf_copy_bit(k, KPF_UNCACHED,	PG_uncached);
#पूर्ण_अगर

	u |= kpf_copy_bit(k, KPF_RESERVED,	PG_reserved);
	u |= kpf_copy_bit(k, KPF_MAPPEDTODISK,	PG_mappedtodisk);
	u |= kpf_copy_bit(k, KPF_PRIVATE,	PG_निजी);
	u |= kpf_copy_bit(k, KPF_PRIVATE_2,	PG_निजी_2);
	u |= kpf_copy_bit(k, KPF_OWNER_PRIVATE,	PG_owner_priv_1);
	u |= kpf_copy_bit(k, KPF_ARCH,		PG_arch_1);
#अगर_घोषित CONFIG_64BIT
	u |= kpf_copy_bit(k, KPF_ARCH_2,	PG_arch_2);
#पूर्ण_अगर

	वापस u;
पूर्ण;

अटल sमाप_प्रकार kpageflags_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			     माप_प्रकार count, loff_t *ppos)
अणु
	स्थिर अचिन्हित दीर्घ max_dump_pfn = get_max_dump_pfn();
	u64 __user *out = (u64 __user *)buf;
	काष्ठा page *ppage;
	अचिन्हित दीर्घ src = *ppos;
	अचिन्हित दीर्घ pfn;
	sमाप_प्रकार ret = 0;

	pfn = src / KPMSIZE;
	अगर (src & KPMMASK || count & KPMMASK)
		वापस -EINVAL;
	अगर (src >= max_dump_pfn * KPMSIZE)
		वापस 0;
	count = min_t(अचिन्हित दीर्घ, count, (max_dump_pfn * KPMSIZE) - src);

	जबतक (count > 0) अणु
		/*
		 * TODO: ZONE_DEVICE support requires to identअगरy
		 * memmaps that were actually initialized.
		 */
		ppage = pfn_to_online_page(pfn);

		अगर (put_user(stable_page_flags(ppage), out)) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण

		pfn++;
		out++;
		count -= KPMSIZE;

		cond_resched();
	पूर्ण

	*ppos += (अक्षर __user *)out - buf;
	अगर (!ret)
		ret = (अक्षर __user *)out - buf;
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा proc_ops kpageflags_proc_ops = अणु
	.proc_lseek	= mem_lseek,
	.proc_पढ़ो	= kpageflags_पढ़ो,
पूर्ण;

#अगर_घोषित CONFIG_MEMCG
अटल sमाप_प्रकार kpagecgroup_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	स्थिर अचिन्हित दीर्घ max_dump_pfn = get_max_dump_pfn();
	u64 __user *out = (u64 __user *)buf;
	काष्ठा page *ppage;
	अचिन्हित दीर्घ src = *ppos;
	अचिन्हित दीर्घ pfn;
	sमाप_प्रकार ret = 0;
	u64 ino;

	pfn = src / KPMSIZE;
	अगर (src & KPMMASK || count & KPMMASK)
		वापस -EINVAL;
	अगर (src >= max_dump_pfn * KPMSIZE)
		वापस 0;
	count = min_t(अचिन्हित दीर्घ, count, (max_dump_pfn * KPMSIZE) - src);

	जबतक (count > 0) अणु
		/*
		 * TODO: ZONE_DEVICE support requires to identअगरy
		 * memmaps that were actually initialized.
		 */
		ppage = pfn_to_online_page(pfn);

		अगर (ppage)
			ino = page_cgroup_ino(ppage);
		अन्यथा
			ino = 0;

		अगर (put_user(ino, out)) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण

		pfn++;
		out++;
		count -= KPMSIZE;

		cond_resched();
	पूर्ण

	*ppos += (अक्षर __user *)out - buf;
	अगर (!ret)
		ret = (अक्षर __user *)out - buf;
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा proc_ops kpagecgroup_proc_ops = अणु
	.proc_lseek	= mem_lseek,
	.proc_पढ़ो	= kpagecgroup_पढ़ो,
पूर्ण;
#पूर्ण_अगर /* CONFIG_MEMCG */

अटल पूर्णांक __init proc_page_init(व्योम)
अणु
	proc_create("kpagecount", S_IRUSR, शून्य, &kpagecount_proc_ops);
	proc_create("kpageflags", S_IRUSR, शून्य, &kpageflags_proc_ops);
#अगर_घोषित CONFIG_MEMCG
	proc_create("kpagecgroup", S_IRUSR, शून्य, &kpagecgroup_proc_ops);
#पूर्ण_अगर
	वापस 0;
पूर्ण
fs_initcall(proc_page_init);
