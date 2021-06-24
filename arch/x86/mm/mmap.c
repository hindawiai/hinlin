<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Flexible mmap layout support
 *
 * Based on code by Ingo Molnar and Andi Kleen, copyrighted
 * as follows:
 *
 * Copyright 2003-2009 Red Hat Inc.
 * All Rights Reserved.
 * Copyright 2005 Andi Kleen, SUSE Lअसल.
 * Copyright 2007 Jiri Kosina, SUSE Lअसल.
 */

#समावेश <linux/personality.h>
#समावेश <linux/mm.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/mm.h>
#समावेश <linux/compat.h>
#समावेश <linux/elf-अक्रमomize.h>
#समावेश <यंत्र/elf.h>
#समावेश <यंत्र/पन.स>

#समावेश "physaddr.h"

काष्ठा va_alignment __पढ़ो_mostly va_align = अणु
	.flags = -1,
पूर्ण;

अचिन्हित दीर्घ task_size_32bit(व्योम)
अणु
	वापस IA32_PAGE_OFFSET;
पूर्ण

अचिन्हित दीर्घ task_size_64bit(पूर्णांक full_addr_space)
अणु
	वापस full_addr_space ? TASK_SIZE_MAX : DEFAULT_MAP_WINDOW;
पूर्ण

अटल अचिन्हित दीर्घ stack_maxअक्रमom_size(अचिन्हित दीर्घ task_size)
अणु
	अचिन्हित दीर्घ max = 0;
	अगर (current->flags & PF_RANDOMIZE) अणु
		max = (-1UL) & __STACK_RND_MASK(task_size == task_size_32bit());
		max <<= PAGE_SHIFT;
	पूर्ण

	वापस max;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
# define mmap32_rnd_bits  mmap_rnd_compat_bits
# define mmap64_rnd_bits  mmap_rnd_bits
#अन्यथा
# define mmap32_rnd_bits  mmap_rnd_bits
# define mmap64_rnd_bits  mmap_rnd_bits
#पूर्ण_अगर

#घोषणा SIZE_128M    (128 * 1024 * 1024UL)

अटल पूर्णांक mmap_is_legacy(व्योम)
अणु
	अगर (current->personality & ADDR_COMPAT_LAYOUT)
		वापस 1;

	वापस sysctl_legacy_va_layout;
पूर्ण

अटल अचिन्हित दीर्घ arch_rnd(अचिन्हित पूर्णांक rndbits)
अणु
	अगर (!(current->flags & PF_RANDOMIZE))
		वापस 0;
	वापस (get_अक्रमom_दीर्घ() & ((1UL << rndbits) - 1)) << PAGE_SHIFT;
पूर्ण

अचिन्हित दीर्घ arch_mmap_rnd(व्योम)
अणु
	वापस arch_rnd(mmap_is_ia32() ? mmap32_rnd_bits : mmap64_rnd_bits);
पूर्ण

अटल अचिन्हित दीर्घ mmap_base(अचिन्हित दीर्घ rnd, अचिन्हित दीर्घ task_size,
			       काष्ठा rlimit *rlim_stack)
अणु
	अचिन्हित दीर्घ gap = rlim_stack->rlim_cur;
	अचिन्हित दीर्घ pad = stack_maxअक्रमom_size(task_size) + stack_guard_gap;
	अचिन्हित दीर्घ gap_min, gap_max;

	/* Values बंद to RLIM_अनन्त can overflow. */
	अगर (gap + pad > gap)
		gap += pad;

	/*
	 * Top of mmap area (just below the process stack).
	 * Leave an at least ~128 MB hole with possible stack अक्रमomization.
	 */
	gap_min = SIZE_128M;
	gap_max = (task_size / 6) * 5;

	अगर (gap < gap_min)
		gap = gap_min;
	अन्यथा अगर (gap > gap_max)
		gap = gap_max;

	वापस PAGE_ALIGN(task_size - gap - rnd);
पूर्ण

अटल अचिन्हित दीर्घ mmap_legacy_base(अचिन्हित दीर्घ rnd,
				      अचिन्हित दीर्घ task_size)
अणु
	वापस __TASK_UNMAPPED_BASE(task_size) + rnd;
पूर्ण

/*
 * This function, called very early during the creation of a new
 * process VM image, sets up which VM layout function to use:
 */
अटल व्योम arch_pick_mmap_base(अचिन्हित दीर्घ *base, अचिन्हित दीर्घ *legacy_base,
		अचिन्हित दीर्घ अक्रमom_factor, अचिन्हित दीर्घ task_size,
		काष्ठा rlimit *rlim_stack)
अणु
	*legacy_base = mmap_legacy_base(अक्रमom_factor, task_size);
	अगर (mmap_is_legacy())
		*base = *legacy_base;
	अन्यथा
		*base = mmap_base(अक्रमom_factor, task_size, rlim_stack);
पूर्ण

व्योम arch_pick_mmap_layout(काष्ठा mm_काष्ठा *mm, काष्ठा rlimit *rlim_stack)
अणु
	अगर (mmap_is_legacy())
		mm->get_unmapped_area = arch_get_unmapped_area;
	अन्यथा
		mm->get_unmapped_area = arch_get_unmapped_area_topकरोwn;

	arch_pick_mmap_base(&mm->mmap_base, &mm->mmap_legacy_base,
			arch_rnd(mmap64_rnd_bits), task_size_64bit(0),
			rlim_stack);

#अगर_घोषित CONFIG_HAVE_ARCH_COMPAT_MMAP_BASES
	/*
	 * The mmap syscall mapping base decision depends solely on the
	 * syscall type (64-bit or compat). This applies क्रम 64bit
	 * applications and 32bit applications. The 64bit syscall uses
	 * mmap_base, the compat syscall uses mmap_compat_base.
	 */
	arch_pick_mmap_base(&mm->mmap_compat_base, &mm->mmap_compat_legacy_base,
			arch_rnd(mmap32_rnd_bits), task_size_32bit(),
			rlim_stack);
#पूर्ण_अगर
पूर्ण

अचिन्हित दीर्घ get_mmap_base(पूर्णांक is_legacy)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;

#अगर_घोषित CONFIG_HAVE_ARCH_COMPAT_MMAP_BASES
	अगर (in_32bit_syscall()) अणु
		वापस is_legacy ? mm->mmap_compat_legacy_base
				 : mm->mmap_compat_base;
	पूर्ण
#पूर्ण_अगर
	वापस is_legacy ? mm->mmap_legacy_base : mm->mmap_base;
पूर्ण

स्थिर अक्षर *arch_vma_name(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस शून्य;
पूर्ण

/**
 * mmap_address_hपूर्णांक_valid - Validate the address hपूर्णांक of mmap
 * @addr:	Address hपूर्णांक
 * @len:	Mapping length
 *
 * Check whether @addr and @addr + @len result in a valid mapping.
 *
 * On 32bit this only checks whether @addr + @len is <= TASK_SIZE.
 *
 * On 64bit with 5-level page tables another sanity check is required
 * because mappings requested by mmap(@addr, 0) which cross the 47-bit
 * भव address boundary can cause the following theoretical issue:
 *
 *  An application calls mmap(addr, 0), i.e. without MAP_FIXED, where @addr
 *  is below the border of the 47-bit address space and @addr + @len is
 *  above the border.
 *
 *  With 4-level paging this request succeeds, but the resulting mapping
 *  address will always be within the 47-bit भव address space, because
 *  the hपूर्णांक address करोes not result in a valid mapping and is
 *  ignored. Hence applications which are not prepared to handle भव
 *  addresses above 47-bit work correctly.
 *
 *  With 5-level paging this request would be granted and result in a
 *  mapping which crosses the border of the 47-bit भव address
 *  space. If the application cannot handle addresses above 47-bit this
 *  will lead to misbehaviour and hard to diagnose failures.
 *
 * Thereक्रमe ignore address hपूर्णांकs which would result in a mapping crossing
 * the 47-bit भव address boundary.
 *
 * Note, that in the same scenario with MAP_FIXED the behaviour is
 * dअगरferent. The request with @addr < 47-bit and @addr + @len > 47-bit
 * fails on a 4-level paging machine but succeeds on a 5-level paging
 * machine. It is reasonable to expect that an application करोes not rely on
 * the failure of such a fixed mapping request, so the restriction is not
 * applied.
 */
bool mmap_address_hपूर्णांक_valid(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len)
अणु
	अगर (TASK_SIZE - len < addr)
		वापस false;

	वापस (addr > DEFAULT_MAP_WINDOW) == (addr + len > DEFAULT_MAP_WINDOW);
पूर्ण

/* Can we access it क्रम direct पढ़ोing/writing? Must be RAM: */
पूर्णांक valid_phys_addr_range(phys_addr_t addr, माप_प्रकार count)
अणु
	वापस addr + count - 1 <= __pa(high_memory - 1);
पूर्ण

/* Can we access it through mmap? Must be a valid physical address: */
पूर्णांक valid_mmap_phys_addr_range(अचिन्हित दीर्घ pfn, माप_प्रकार count)
अणु
	phys_addr_t addr = (phys_addr_t)pfn << PAGE_SHIFT;

	वापस phys_addr_valid(addr + count - 1);
पूर्ण

/*
 * Only allow root to set high MMIO mappings to PROT_NONE.
 * This prevents an unpriv. user to set them to PROT_NONE and invert
 * them, then poपूर्णांकing to valid memory क्रम L1TF speculation.
 *
 * Note: क्रम locked करोwn kernels may want to disable the root override.
 */
bool pfn_modअगरy_allowed(अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	अगर (!boot_cpu_has_bug(X86_BUG_L1TF))
		वापस true;
	अगर (!__pte_needs_invert(pgprot_val(prot)))
		वापस true;
	/* If it's real memory always allow */
	अगर (pfn_valid(pfn))
		वापस true;
	अगर (pfn >= l1tf_pfn_limit() && !capable(CAP_SYS_ADMIN))
		वापस false;
	वापस true;
पूर्ण
