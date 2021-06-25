<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/init.h>
#समावेश <linux/memblock.h>
#समावेश <linux/fs.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/kobject.h>
#समावेश <linux/memory_hotplug.h>
#समावेश <linux/mm.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/rmap.h>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/page_ext.h>
#समावेश <linux/page_idle.h>

#घोषणा BITMAP_CHUNK_SIZE	माप(u64)
#घोषणा BITMAP_CHUNK_BITS	(BITMAP_CHUNK_SIZE * BITS_PER_BYTE)

/*
 * Idle page tracking only considers user memory pages, क्रम other types of
 * pages the idle flag is always unset and an attempt to set it is silently
 * ignored.
 *
 * We treat a page as a user memory page अगर it is on an LRU list, because it is
 * always safe to pass such a page to rmap_walk(), which is essential क्रम idle
 * page tracking. With such an indicator of user pages we can skip isolated
 * pages, but since there are not usually many of them, it will hardly affect
 * the overall result.
 *
 * This function tries to get a user memory page by pfn as described above.
 */
अटल काष्ठा page *page_idle_get_page(अचिन्हित दीर्घ pfn)
अणु
	काष्ठा page *page = pfn_to_online_page(pfn);

	अगर (!page || !PageLRU(page) ||
	    !get_page_unless_zero(page))
		वापस शून्य;

	अगर (unlikely(!PageLRU(page))) अणु
		put_page(page);
		page = शून्य;
	पूर्ण
	वापस page;
पूर्ण

अटल bool page_idle_clear_pte_refs_one(काष्ठा page *page,
					काष्ठा vm_area_काष्ठा *vma,
					अचिन्हित दीर्घ addr, व्योम *arg)
अणु
	काष्ठा page_vma_mapped_walk pvmw = अणु
		.page = page,
		.vma = vma,
		.address = addr,
	पूर्ण;
	bool referenced = false;

	जबतक (page_vma_mapped_walk(&pvmw)) अणु
		addr = pvmw.address;
		अगर (pvmw.pte) अणु
			/*
			 * For PTE-mapped THP, one sub page is referenced,
			 * the whole THP is referenced.
			 */
			अगर (ptep_clear_young_notअगरy(vma, addr, pvmw.pte))
				referenced = true;
		पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_TRANSPARENT_HUGEPAGE)) अणु
			अगर (pmdp_clear_young_notअगरy(vma, addr, pvmw.pmd))
				referenced = true;
		पूर्ण अन्यथा अणु
			/* unexpected pmd-mapped page? */
			WARN_ON_ONCE(1);
		पूर्ण
	पूर्ण

	अगर (referenced) अणु
		clear_page_idle(page);
		/*
		 * We cleared the referenced bit in a mapping to this page. To
		 * aव्योम पूर्णांकerference with page reclaim, mark it young so that
		 * page_referenced() will वापस > 0.
		 */
		set_page_young(page);
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम page_idle_clear_pte_refs(काष्ठा page *page)
अणु
	/*
	 * Since rwc.arg is unused, rwc is effectively immutable, so we
	 * can make it अटल स्थिर to save some cycles and stack.
	 */
	अटल स्थिर काष्ठा rmap_walk_control rwc = अणु
		.rmap_one = page_idle_clear_pte_refs_one,
		.anon_lock = page_lock_anon_vma_पढ़ो,
	पूर्ण;
	bool need_lock;

	अगर (!page_mapped(page) ||
	    !page_rmapping(page))
		वापस;

	need_lock = !PageAnon(page) || PageKsm(page);
	अगर (need_lock && !trylock_page(page))
		वापस;

	rmap_walk(page, (काष्ठा rmap_walk_control *)&rwc);

	अगर (need_lock)
		unlock_page(page);
पूर्ण

अटल sमाप_प्रकार page_idle_biपंचांगap_पढ़ो(काष्ठा file *file, काष्ठा kobject *kobj,
				     काष्ठा bin_attribute *attr, अक्षर *buf,
				     loff_t pos, माप_प्रकार count)
अणु
	u64 *out = (u64 *)buf;
	काष्ठा page *page;
	अचिन्हित दीर्घ pfn, end_pfn;
	पूर्णांक bit;

	अगर (pos % BITMAP_CHUNK_SIZE || count % BITMAP_CHUNK_SIZE)
		वापस -EINVAL;

	pfn = pos * BITS_PER_BYTE;
	अगर (pfn >= max_pfn)
		वापस 0;

	end_pfn = pfn + count * BITS_PER_BYTE;
	अगर (end_pfn > max_pfn)
		end_pfn = max_pfn;

	क्रम (; pfn < end_pfn; pfn++) अणु
		bit = pfn % BITMAP_CHUNK_BITS;
		अगर (!bit)
			*out = 0ULL;
		page = page_idle_get_page(pfn);
		अगर (page) अणु
			अगर (page_is_idle(page)) अणु
				/*
				 * The page might have been referenced via a
				 * pte, in which हाल it is not idle. Clear
				 * refs and recheck.
				 */
				page_idle_clear_pte_refs(page);
				अगर (page_is_idle(page))
					*out |= 1ULL << bit;
			पूर्ण
			put_page(page);
		पूर्ण
		अगर (bit == BITMAP_CHUNK_BITS - 1)
			out++;
		cond_resched();
	पूर्ण
	वापस (अक्षर *)out - buf;
पूर्ण

अटल sमाप_प्रकार page_idle_biपंचांगap_ग_लिखो(काष्ठा file *file, काष्ठा kobject *kobj,
				      काष्ठा bin_attribute *attr, अक्षर *buf,
				      loff_t pos, माप_प्रकार count)
अणु
	स्थिर u64 *in = (u64 *)buf;
	काष्ठा page *page;
	अचिन्हित दीर्घ pfn, end_pfn;
	पूर्णांक bit;

	अगर (pos % BITMAP_CHUNK_SIZE || count % BITMAP_CHUNK_SIZE)
		वापस -EINVAL;

	pfn = pos * BITS_PER_BYTE;
	अगर (pfn >= max_pfn)
		वापस -ENXIO;

	end_pfn = pfn + count * BITS_PER_BYTE;
	अगर (end_pfn > max_pfn)
		end_pfn = max_pfn;

	क्रम (; pfn < end_pfn; pfn++) अणु
		bit = pfn % BITMAP_CHUNK_BITS;
		अगर ((*in >> bit) & 1) अणु
			page = page_idle_get_page(pfn);
			अगर (page) अणु
				page_idle_clear_pte_refs(page);
				set_page_idle(page);
				put_page(page);
			पूर्ण
		पूर्ण
		अगर (bit == BITMAP_CHUNK_BITS - 1)
			in++;
		cond_resched();
	पूर्ण
	वापस (अक्षर *)in - buf;
पूर्ण

अटल काष्ठा bin_attribute page_idle_biपंचांगap_attr =
		__BIN_ATTR(biपंचांगap, 0600,
			   page_idle_biपंचांगap_पढ़ो, page_idle_biपंचांगap_ग_लिखो, 0);

अटल काष्ठा bin_attribute *page_idle_bin_attrs[] = अणु
	&page_idle_biपंचांगap_attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group page_idle_attr_group = अणु
	.bin_attrs = page_idle_bin_attrs,
	.name = "page_idle",
पूर्ण;

#अगर_अघोषित CONFIG_64BIT
अटल bool need_page_idle(व्योम)
अणु
	वापस true;
पूर्ण
काष्ठा page_ext_operations page_idle_ops = अणु
	.need = need_page_idle,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init page_idle_init(व्योम)
अणु
	पूर्णांक err;

	err = sysfs_create_group(mm_kobj, &page_idle_attr_group);
	अगर (err) अणु
		pr_err("page_idle: register sysfs failed\n");
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण
subsys_initcall(page_idle_init);
