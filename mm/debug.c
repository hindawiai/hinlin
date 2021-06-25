<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * mm/debug.c
 *
 * mm/ specअगरic debug routines.
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/trace_events.h>
#समावेश <linux/memcontrol.h>
#समावेश <trace/events/mmflags.h>
#समावेश <linux/migrate.h>
#समावेश <linux/page_owner.h>
#समावेश <linux/प्रकार.स>

#समावेश "internal.h"

स्थिर अक्षर *migrate_reason_names[MR_TYPES] = अणु
	"compaction",
	"memory_failure",
	"memory_hotplug",
	"syscall_or_cpuset",
	"mempolicy_mbind",
	"numa_misplaced",
	"cma",
पूर्ण;

स्थिर काष्ठा trace_prपूर्णांक_flags pageflag_names[] = अणु
	__def_pageflag_names,
	अणु0, शून्यपूर्ण
पूर्ण;

स्थिर काष्ठा trace_prपूर्णांक_flags gfpflag_names[] = अणु
	__def_gfpflag_names,
	अणु0, शून्यपूर्ण
पूर्ण;

स्थिर काष्ठा trace_prपूर्णांक_flags vmaflag_names[] = अणु
	__def_vmaflag_names,
	अणु0, शून्यपूर्ण
पूर्ण;

व्योम __dump_page(काष्ठा page *page, स्थिर अक्षर *reason)
अणु
	काष्ठा page *head = compound_head(page);
	काष्ठा address_space *mapping;
	bool page_poisoned = PagePoisoned(page);
	bool compound = PageCompound(page);
	/*
	 * Accessing the pageblock without the zone lock. It could change to
	 * "isolate" again in the meanसमय, but since we are just dumping the
	 * state क्रम debugging, it should be fine to accept a bit of
	 * inaccuracy here due to racing.
	 */
	bool page_cma = is_migrate_cma_page(page);
	पूर्णांक mapcount;
	अक्षर *type = "";

	/*
	 * If काष्ठा page is poisoned करोn't access Page*() functions as that
	 * leads to recursive loop. Page*() check क्रम poisoned pages, and calls
	 * dump_page() when detected.
	 */
	अगर (page_poisoned) अणु
		pr_warn("page:%px is uninitialized and poisoned", page);
		जाओ hex_only;
	पूर्ण

	अगर (page < head || (page >= head + MAX_ORDER_NR_PAGES)) अणु
		/*
		 * Corrupt page, so we cannot call page_mapping. Instead, करो a
		 * safe subset of the steps that page_mapping() करोes. Caution:
		 * this will be misleading क्रम tail pages, PageSwapCache pages,
		 * and potentially other situations. (See the page_mapping()
		 * implementation क्रम what's missing here.)
		 */
		अचिन्हित दीर्घ पंचांगp = (अचिन्हित दीर्घ)page->mapping;

		अगर (पंचांगp & PAGE_MAPPING_ANON)
			mapping = शून्य;
		अन्यथा
			mapping = (व्योम *)(पंचांगp & ~PAGE_MAPPING_FLAGS);
		head = page;
		compound = false;
	पूर्ण अन्यथा अणु
		mapping = page_mapping(page);
	पूर्ण

	/*
	 * Aव्योम VM_BUG_ON() in page_mapcount().
	 * page->_mapcount space in काष्ठा page is used by sl[aou]b pages to
	 * encode own info.
	 */
	mapcount = PageSlab(head) ? 0 : page_mapcount(page);

	pr_warn("page:%p refcount:%d mapcount:%d mapping:%p index:%#lx pfn:%#lx\n",
			page, page_ref_count(head), mapcount, mapping,
			page_to_pgoff(page), page_to_pfn(page));
	अगर (compound) अणु
		अगर (hpage_pincount_available(page)) अणु
			pr_warn("head:%p order:%u compound_mapcount:%d compound_pincount:%d\n",
					head, compound_order(head),
					head_compound_mapcount(head),
					head_compound_pincount(head));
		पूर्ण अन्यथा अणु
			pr_warn("head:%p order:%u compound_mapcount:%d\n",
					head, compound_order(head),
					head_compound_mapcount(head));
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_MEMCG
	अगर (head->memcg_data)
		pr_warn("memcg:%lx\n", head->memcg_data);
#पूर्ण_अगर
	अगर (PageKsm(page))
		type = "ksm ";
	अन्यथा अगर (PageAnon(page))
		type = "anon ";
	अन्यथा अगर (mapping) अणु
		काष्ठा inode *host;
		स्थिर काष्ठा address_space_operations *a_ops;
		काष्ठा hlist_node *dentry_first;
		काष्ठा dentry *dentry_ptr;
		काष्ठा dentry dentry;
		अचिन्हित दीर्घ ino;

		/*
		 * mapping can be invalid poपूर्णांकer and we करोn't want to crash
		 * accessing it, so probe everything depending on it carefully
		 */
		अगर (get_kernel_nofault(host, &mapping->host) ||
		    get_kernel_nofault(a_ops, &mapping->a_ops)) अणु
			pr_warn("failed to read mapping contents, not a valid kernel address?\n");
			जाओ out_mapping;
		पूर्ण

		अगर (!host) अणु
			pr_warn("aops:%ps\n", a_ops);
			जाओ out_mapping;
		पूर्ण

		अगर (get_kernel_nofault(dentry_first, &host->i_dentry.first) ||
		    get_kernel_nofault(ino, &host->i_ino)) अणु
			pr_warn("aops:%ps with invalid host inode %px\n",
					a_ops, host);
			जाओ out_mapping;
		पूर्ण

		अगर (!dentry_first) अणु
			pr_warn("aops:%ps ino:%lx\n", a_ops, ino);
			जाओ out_mapping;
		पूर्ण

		dentry_ptr = container_of(dentry_first, काष्ठा dentry, d_u.d_alias);
		अगर (get_kernel_nofault(dentry, dentry_ptr)) अणु
			pr_warn("aops:%ps ino:%lx with invalid dentry %px\n",
					a_ops, ino, dentry_ptr);
		पूर्ण अन्यथा अणु
			/*
			 * अगर dentry is corrupted, the %pd handler may still
			 * crash, but it's unlikely that we reach here with a
			 * corrupted काष्ठा page
			 */
			pr_warn("aops:%ps ino:%lx dentry name:\"%pd\"\n",
					a_ops, ino, &dentry);
		पूर्ण
	पूर्ण
out_mapping:
	BUILD_BUG_ON(ARRAY_SIZE(pageflag_names) != __NR_PAGEFLAGS + 1);

	pr_warn("%sflags: %#lx(%pGp)%s\n", type, head->flags, &head->flags,
		page_cma ? " CMA" : "");

hex_only:
	prपूर्णांक_hex_dump(KERN_WARNING, "raw: ", DUMP_PREFIX_NONE, 32,
			माप(अचिन्हित दीर्घ), page,
			माप(काष्ठा page), false);
	अगर (head != page)
		prपूर्णांक_hex_dump(KERN_WARNING, "head: ", DUMP_PREFIX_NONE, 32,
			माप(अचिन्हित दीर्घ), head,
			माप(काष्ठा page), false);

	अगर (reason)
		pr_warn("page dumped because: %s\n", reason);
पूर्ण

व्योम dump_page(काष्ठा page *page, स्थिर अक्षर *reason)
अणु
	__dump_page(page, reason);
	dump_page_owner(page);
पूर्ण
EXPORT_SYMBOL(dump_page);

#अगर_घोषित CONFIG_DEBUG_VM

व्योम dump_vma(स्थिर काष्ठा vm_area_काष्ठा *vma)
अणु
	pr_emerg("vma %px start %px end %px\n"
		"next %px prev %px mm %px\n"
		"prot %lx anon_vma %px vm_ops %px\n"
		"pgoff %lx file %px private_data %px\n"
		"flags: %#lx(%pGv)\n",
		vma, (व्योम *)vma->vm_start, (व्योम *)vma->vm_end, vma->vm_next,
		vma->vm_prev, vma->vm_mm,
		(अचिन्हित दीर्घ)pgprot_val(vma->vm_page_prot),
		vma->anon_vma, vma->vm_ops, vma->vm_pgoff,
		vma->vm_file, vma->vm_निजी_data,
		vma->vm_flags, &vma->vm_flags);
पूर्ण
EXPORT_SYMBOL(dump_vma);

व्योम dump_mm(स्थिर काष्ठा mm_काष्ठा *mm)
अणु
	pr_emerg("mm %px mmap %px seqnum %llu task_size %lu\n"
#अगर_घोषित CONFIG_MMU
		"get_unmapped_area %px\n"
#पूर्ण_अगर
		"mmap_base %lu mmap_legacy_base %lu highest_vm_end %lu\n"
		"pgd %px mm_users %d mm_count %d pgtables_bytes %lu map_count %d\n"
		"hiwater_rss %lx hiwater_vm %lx total_vm %lx locked_vm %lx\n"
		"pinned_vm %llx data_vm %lx exec_vm %lx stack_vm %lx\n"
		"start_code %lx end_code %lx start_data %lx end_data %lx\n"
		"start_brk %lx brk %lx start_stack %lx\n"
		"arg_start %lx arg_end %lx env_start %lx env_end %lx\n"
		"binfmt %px flags %lx core_state %px\n"
#अगर_घोषित CONFIG_AIO
		"ioctx_table %px\n"
#पूर्ण_अगर
#अगर_घोषित CONFIG_MEMCG
		"owner %px "
#पूर्ण_अगर
		"exe_file %px\n"
#अगर_घोषित CONFIG_MMU_NOTIFIER
		"notifier_subscriptions %px\n"
#पूर्ण_अगर
#अगर_घोषित CONFIG_NUMA_BALANCING
		"numa_next_scan %lu numa_scan_offset %lu numa_scan_seq %d\n"
#पूर्ण_अगर
		"tlb_flush_pending %d\n"
		"def_flags: %#lx(%pGv)\n",

		mm, mm->mmap, (दीर्घ दीर्घ) mm->vmacache_seqnum, mm->task_size,
#अगर_घोषित CONFIG_MMU
		mm->get_unmapped_area,
#पूर्ण_अगर
		mm->mmap_base, mm->mmap_legacy_base, mm->highest_vm_end,
		mm->pgd, atomic_पढ़ो(&mm->mm_users),
		atomic_पढ़ो(&mm->mm_count),
		mm_pgtables_bytes(mm),
		mm->map_count,
		mm->hiwater_rss, mm->hiwater_vm, mm->total_vm, mm->locked_vm,
		(u64)atomic64_पढ़ो(&mm->pinned_vm),
		mm->data_vm, mm->exec_vm, mm->stack_vm,
		mm->start_code, mm->end_code, mm->start_data, mm->end_data,
		mm->start_brk, mm->brk, mm->start_stack,
		mm->arg_start, mm->arg_end, mm->env_start, mm->env_end,
		mm->binfmt, mm->flags, mm->core_state,
#अगर_घोषित CONFIG_AIO
		mm->ioctx_table,
#पूर्ण_अगर
#अगर_घोषित CONFIG_MEMCG
		mm->owner,
#पूर्ण_अगर
		mm->exe_file,
#अगर_घोषित CONFIG_MMU_NOTIFIER
		mm->notअगरier_subscriptions,
#पूर्ण_अगर
#अगर_घोषित CONFIG_NUMA_BALANCING
		mm->numa_next_scan, mm->numa_scan_offset, mm->numa_scan_seq,
#पूर्ण_अगर
		atomic_पढ़ो(&mm->tlb_flush_pending),
		mm->def_flags, &mm->def_flags
	);
पूर्ण

अटल bool page_init_poisoning __पढ़ो_mostly = true;

अटल पूर्णांक __init setup_vm_debug(अक्षर *str)
अणु
	bool __page_init_poisoning = true;

	/*
	 * Calling vm_debug with no arguments is equivalent to requesting
	 * to enable all debugging options we can control.
	 */
	अगर (*str++ != '=' || !*str)
		जाओ out;

	__page_init_poisoning = false;
	अगर (*str == '-')
		जाओ out;

	जबतक (*str) अणु
		चयन (छोटे(*str)) अणु
		हाल'p':
			__page_init_poisoning = true;
			अवरोध;
		शेष:
			pr_err("vm_debug option '%c' unknown. skipped\n",
			       *str);
		पूर्ण

		str++;
	पूर्ण
out:
	अगर (page_init_poisoning && !__page_init_poisoning)
		pr_warn("Page struct poisoning disabled by kernel command line option 'vm_debug'\n");

	page_init_poisoning = __page_init_poisoning;

	वापस 1;
पूर्ण
__setup("vm_debug", setup_vm_debug);

व्योम page_init_poison(काष्ठा page *page, माप_प्रकार size)
अणु
	अगर (page_init_poisoning)
		स_रखो(page, PAGE_POISON_PATTERN, size);
पूर्ण
EXPORT_SYMBOL_GPL(page_init_poison);
#पूर्ण_अगर		/* CONFIG_DEBUG_VM */
