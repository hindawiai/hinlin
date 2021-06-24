<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/mm/mincore.c
 *
 * Copyright (C) 1994-2006  Linus Torvalds
 */

/*
 * The mincore() प्रणाली call.
 */
#समावेश <linux/pagemap.h>
#समावेश <linux/gfp.h>
#समावेश <linux/pagewalk.h>
#समावेश <linux/mman.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/swap.h>
#समावेश <linux/swapops.h>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/pgtable.h>

#समावेश <linux/uaccess.h>

अटल पूर्णांक mincore_hugetlb(pte_t *pte, अचिन्हित दीर्घ hmask, अचिन्हित दीर्घ addr,
			अचिन्हित दीर्घ end, काष्ठा mm_walk *walk)
अणु
#अगर_घोषित CONFIG_HUGETLB_PAGE
	अचिन्हित अक्षर present;
	अचिन्हित अक्षर *vec = walk->निजी;

	/*
	 * Hugepages under user process are always in RAM and never
	 * swapped out, but theoretically it needs to be checked.
	 */
	present = pte && !huge_pte_none(huge_ptep_get(pte));
	क्रम (; addr != end; vec++, addr += PAGE_SIZE)
		*vec = present;
	walk->निजी = vec;
#अन्यथा
	BUG();
#पूर्ण_अगर
	वापस 0;
पूर्ण

/*
 * Later we can get more picky about what "in core" means precisely.
 * For now, simply check to see अगर the page is in the page cache,
 * and is up to date; i.e. that no page-in operation would be required
 * at this समय अगर an application were to map and access this page.
 */
अटल अचिन्हित अक्षर mincore_page(काष्ठा address_space *mapping, pgoff_t index)
अणु
	अचिन्हित अक्षर present = 0;
	काष्ठा page *page;

	/*
	 * When पंचांगpfs swaps out a page from a file, any process mapping that
	 * file will not get a swp_entry_t in its pte, but rather it is like
	 * any other file mapping (ie. marked !present and faulted in with
	 * पंचांगpfs's .fault). So swapped out पंचांगpfs mappings are tested here.
	 */
	page = find_get_incore_page(mapping, index);
	अगर (page) अणु
		present = PageUptodate(page);
		put_page(page);
	पूर्ण

	वापस present;
पूर्ण

अटल पूर्णांक __mincore_unmapped_range(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
				काष्ठा vm_area_काष्ठा *vma, अचिन्हित अक्षर *vec)
अणु
	अचिन्हित दीर्घ nr = (end - addr) >> PAGE_SHIFT;
	पूर्णांक i;

	अगर (vma->vm_file) अणु
		pgoff_t pgoff;

		pgoff = linear_page_index(vma, addr);
		क्रम (i = 0; i < nr; i++, pgoff++)
			vec[i] = mincore_page(vma->vm_file->f_mapping, pgoff);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < nr; i++)
			vec[i] = 0;
	पूर्ण
	वापस nr;
पूर्ण

अटल पूर्णांक mincore_unmapped_range(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
				   __always_unused पूर्णांक depth,
				   काष्ठा mm_walk *walk)
अणु
	walk->निजी += __mincore_unmapped_range(addr, end,
						  walk->vma, walk->निजी);
	वापस 0;
पूर्ण

अटल पूर्णांक mincore_pte_range(pmd_t *pmd, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			काष्ठा mm_walk *walk)
अणु
	spinlock_t *ptl;
	काष्ठा vm_area_काष्ठा *vma = walk->vma;
	pte_t *ptep;
	अचिन्हित अक्षर *vec = walk->निजी;
	पूर्णांक nr = (end - addr) >> PAGE_SHIFT;

	ptl = pmd_trans_huge_lock(pmd, vma);
	अगर (ptl) अणु
		स_रखो(vec, 1, nr);
		spin_unlock(ptl);
		जाओ out;
	पूर्ण

	अगर (pmd_trans_unstable(pmd)) अणु
		__mincore_unmapped_range(addr, end, vma, vec);
		जाओ out;
	पूर्ण

	ptep = pte_offset_map_lock(walk->mm, pmd, addr, &ptl);
	क्रम (; addr != end; ptep++, addr += PAGE_SIZE) अणु
		pte_t pte = *ptep;

		अगर (pte_none(pte))
			__mincore_unmapped_range(addr, addr + PAGE_SIZE,
						 vma, vec);
		अन्यथा अगर (pte_present(pte))
			*vec = 1;
		अन्यथा अणु /* pte is a swap entry */
			swp_entry_t entry = pte_to_swp_entry(pte);

			अगर (non_swap_entry(entry)) अणु
				/*
				 * migration or hwpoison entries are always
				 * uptodate
				 */
				*vec = 1;
			पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_SWAP
				*vec = mincore_page(swap_address_space(entry),
						    swp_offset(entry));
#अन्यथा
				WARN_ON(1);
				*vec = 1;
#पूर्ण_अगर
			पूर्ण
		पूर्ण
		vec++;
	पूर्ण
	pte_unmap_unlock(ptep - 1, ptl);
out:
	walk->निजी += nr;
	cond_resched();
	वापस 0;
पूर्ण

अटल अंतरभूत bool can_करो_mincore(काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (vma_is_anonymous(vma))
		वापस true;
	अगर (!vma->vm_file)
		वापस false;
	/*
	 * Reveal pagecache inक्रमmation only क्रम non-anonymous mappings that
	 * correspond to the files the calling process could (अगर tried) खोलो
	 * क्रम writing; otherwise we'd be including shared non-exclusive
	 * mappings, which खोलोs a side channel.
	 */
	वापस inode_owner_or_capable(&init_user_ns,
				      file_inode(vma->vm_file)) ||
	       file_permission(vma->vm_file, MAY_WRITE) == 0;
पूर्ण

अटल स्थिर काष्ठा mm_walk_ops mincore_walk_ops = अणु
	.pmd_entry		= mincore_pte_range,
	.pte_hole		= mincore_unmapped_range,
	.hugetlb_entry		= mincore_hugetlb,
पूर्ण;

/*
 * Do a chunk of "sys_mincore()". We've alपढ़ोy checked
 * all the arguments, we hold the mmap semaphore: we should
 * just वापस the amount of info we're asked क्रम.
 */
अटल दीर्घ करो_mincore(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ pages, अचिन्हित अक्षर *vec)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ end;
	पूर्णांक err;

	vma = find_vma(current->mm, addr);
	अगर (!vma || addr < vma->vm_start)
		वापस -ENOMEM;
	end = min(vma->vm_end, addr + (pages << PAGE_SHIFT));
	अगर (!can_करो_mincore(vma)) अणु
		अचिन्हित दीर्घ pages = DIV_ROUND_UP(end - addr, PAGE_SIZE);
		स_रखो(vec, 1, pages);
		वापस pages;
	पूर्ण
	err = walk_page_range(vma->vm_mm, addr, end, &mincore_walk_ops, vec);
	अगर (err < 0)
		वापस err;
	वापस (end - addr) >> PAGE_SHIFT;
पूर्ण

/*
 * The mincore(2) प्रणाली call.
 *
 * mincore() वापसs the memory residency status of the pages in the
 * current process's address space specअगरied by [addr, addr + len).
 * The status is वापसed in a vector of bytes.  The least signअगरicant
 * bit of each byte is 1 अगर the referenced page is in memory, otherwise
 * it is zero.
 *
 * Because the status of a page can change after mincore() checks it
 * but beक्रमe it वापसs to the application, the वापसed vector may
 * contain stale inक्रमmation.  Only locked pages are guaranteed to
 * reमुख्य in memory.
 *
 * वापस values:
 *  zero    - success
 *  -EFAULT - vec poपूर्णांकs to an illegal address
 *  -EINVAL - addr is not a multiple of PAGE_SIZE
 *  -ENOMEM - Addresses in the range [addr, addr + len] are
 *		invalid क्रम the address space of this process, or
 *		specअगरy one or more pages which are not currently
 *		mapped
 *  -EAGAIN - A kernel resource was temporarily unavailable.
 */
SYSCALL_DEFINE3(mincore, अचिन्हित दीर्घ, start, माप_प्रकार, len,
		अचिन्हित अक्षर __user *, vec)
अणु
	दीर्घ retval;
	अचिन्हित दीर्घ pages;
	अचिन्हित अक्षर *पंचांगp;

	start = untagged_addr(start);

	/* Check the start address: needs to be page-aligned.. */
	अगर (start & ~PAGE_MASK)
		वापस -EINVAL;

	/* ..and we need to be passed a valid user-space range */
	अगर (!access_ok((व्योम __user *) start, len))
		वापस -ENOMEM;

	/* This also aव्योमs any overflows on PAGE_ALIGN */
	pages = len >> PAGE_SHIFT;
	pages += (offset_in_page(len)) != 0;

	अगर (!access_ok(vec, pages))
		वापस -EFAULT;

	पंचांगp = (व्योम *) __get_मुक्त_page(GFP_USER);
	अगर (!पंचांगp)
		वापस -EAGAIN;

	retval = 0;
	जबतक (pages) अणु
		/*
		 * Do at most PAGE_SIZE entries per iteration, due to
		 * the temporary buffer size.
		 */
		mmap_पढ़ो_lock(current->mm);
		retval = करो_mincore(start, min(pages, PAGE_SIZE), पंचांगp);
		mmap_पढ़ो_unlock(current->mm);

		अगर (retval <= 0)
			अवरोध;
		अगर (copy_to_user(vec, पंचांगp, retval)) अणु
			retval = -EFAULT;
			अवरोध;
		पूर्ण
		pages -= retval;
		vec += retval;
		start += retval << PAGE_SHIFT;
		retval = 0;
	पूर्ण
	मुक्त_page((अचिन्हित दीर्घ) पंचांगp);
	वापस retval;
पूर्ण
