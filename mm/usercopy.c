<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This implements the various checks क्रम CONFIG_HARDENED_USERCOPY*,
 * which are deचिन्हित to protect kernel memory from needless exposure
 * and overग_लिखो under many unपूर्णांकended conditions. This code is based
 * on PAX_USERCOPY, which is:
 *
 * Copyright (C) 2001-2016 PaX Team, Bradley Spengler, Open Source
 * Security Inc.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/mm.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/thपढ़ो_info.h>
#समावेश <linux/atomic.h>
#समावेश <linux/jump_label.h>
#समावेश <यंत्र/sections.h>

/*
 * Checks अगर a given poपूर्णांकer and length is contained by the current
 * stack frame (अगर possible).
 *
 * Returns:
 *	NOT_STACK: not at all on the stack
 *	GOOD_FRAME: fully within a valid stack frame
 *	GOOD_STACK: fully on the stack (when can't करो frame-checking)
 *	BAD_STACK: error condition (invalid stack position or bad stack frame)
 */
अटल noअंतरभूत पूर्णांक check_stack_object(स्थिर व्योम *obj, अचिन्हित दीर्घ len)
अणु
	स्थिर व्योम * स्थिर stack = task_stack_page(current);
	स्थिर व्योम * स्थिर stackend = stack + THREAD_SIZE;
	पूर्णांक ret;

	/* Object is not on the stack at all. */
	अगर (obj + len <= stack || stackend <= obj)
		वापस NOT_STACK;

	/*
	 * Reject: object partially overlaps the stack (passing the
	 * check above means at least one end is within the stack,
	 * so अगर this check fails, the other end is outside the stack).
	 */
	अगर (obj < stack || stackend < obj + len)
		वापस BAD_STACK;

	/* Check अगर object is safely within a valid frame. */
	ret = arch_within_stack_frames(stack, stackend, obj, len);
	अगर (ret)
		वापस ret;

	वापस GOOD_STACK;
पूर्ण

/*
 * If these functions are reached, then CONFIG_HARDENED_USERCOPY has found
 * an unexpected state during a copy_from_user() or copy_to_user() call.
 * There are several checks being perक्रमmed on the buffer by the
 * __check_object_size() function. Normal stack buffer usage should never
 * trip the checks, and kernel text addressing will always trip the check.
 * For cache objects, it is checking that only the whitelisted range of
 * bytes क्रम a given cache is being accessed (via the cache's usersize and
 * useroffset fields). To adjust a cache whitelist, use the usercopy-aware
 * kmem_cache_create_usercopy() function to create the cache (and
 * carefully audit the whitelist range).
 */
व्योम usercopy_warn(स्थिर अक्षर *name, स्थिर अक्षर *detail, bool to_user,
		   अचिन्हित दीर्घ offset, अचिन्हित दीर्घ len)
अणु
	WARN_ONCE(1, "Bad or missing usercopy whitelist? Kernel memory %s attempt detected %s %s%s%s%s (offset %lu, size %lu)!\n",
		 to_user ? "exposure" : "overwrite",
		 to_user ? "from" : "to",
		 name ? : "unknown?!",
		 detail ? " '" : "", detail ? : "", detail ? "'" : "",
		 offset, len);
पूर्ण

व्योम __noवापस usercopy_पात(स्थिर अक्षर *name, स्थिर अक्षर *detail,
			       bool to_user, अचिन्हित दीर्घ offset,
			       अचिन्हित दीर्घ len)
अणु
	pr_emerg("Kernel memory %s attempt detected %s %s%s%s%s (offset %lu, size %lu)!\n",
		 to_user ? "exposure" : "overwrite",
		 to_user ? "from" : "to",
		 name ? : "unknown?!",
		 detail ? " '" : "", detail ? : "", detail ? "'" : "",
		 offset, len);

	/*
	 * For greater effect, it would be nice to करो करो_group_निकास(),
	 * but BUG() actually hooks all the lock-अवरोधing and per-arch
	 * Oops code, so that is used here instead.
	 */
	BUG();
पूर्ण

/* Returns true अगर any portion of [ptr,ptr+n) over laps with [low,high). */
अटल bool overlaps(स्थिर अचिन्हित दीर्घ ptr, अचिन्हित दीर्घ n,
		     अचिन्हित दीर्घ low, अचिन्हित दीर्घ high)
अणु
	स्थिर अचिन्हित दीर्घ check_low = ptr;
	अचिन्हित दीर्घ check_high = check_low + n;

	/* Does not overlap अगर entirely above or entirely below. */
	अगर (check_low >= high || check_high <= low)
		वापस false;

	वापस true;
पूर्ण

/* Is this address range in the kernel text area? */
अटल अंतरभूत व्योम check_kernel_text_object(स्थिर अचिन्हित दीर्घ ptr,
					    अचिन्हित दीर्घ n, bool to_user)
अणु
	अचिन्हित दीर्घ textlow = (अचिन्हित दीर्घ)_stext;
	अचिन्हित दीर्घ texthigh = (अचिन्हित दीर्घ)_etext;
	अचिन्हित दीर्घ textlow_linear, texthigh_linear;

	अगर (overlaps(ptr, n, textlow, texthigh))
		usercopy_पात("kernel text", शून्य, to_user, ptr - textlow, n);

	/*
	 * Some architectures have भव memory mappings with a secondary
	 * mapping of the kernel text, i.e. there is more than one भव
	 * kernel address that poपूर्णांकs to the kernel image. It is usually
	 * when there is a separate linear physical memory mapping, in that
	 * __pa() is not just the reverse of __va(). This can be detected
	 * and checked:
	 */
	textlow_linear = (अचिन्हित दीर्घ)lm_alias(textlow);
	/* No dअगरferent mapping: we're करोne. */
	अगर (textlow_linear == textlow)
		वापस;

	/* Check the secondary mapping... */
	texthigh_linear = (अचिन्हित दीर्घ)lm_alias(texthigh);
	अगर (overlaps(ptr, n, textlow_linear, texthigh_linear))
		usercopy_पात("linear kernel text", शून्य, to_user,
			       ptr - textlow_linear, n);
पूर्ण

अटल अंतरभूत व्योम check_bogus_address(स्थिर अचिन्हित दीर्घ ptr, अचिन्हित दीर्घ n,
				       bool to_user)
अणु
	/* Reject अगर object wraps past end of memory. */
	अगर (ptr + (n - 1) < ptr)
		usercopy_पात("wrapped address", शून्य, to_user, 0, ptr + n);

	/* Reject अगर शून्य or ZERO-allocation. */
	अगर (ZERO_OR_शून्य_PTR(ptr))
		usercopy_पात("null address", शून्य, to_user, ptr, n);
पूर्ण

/* Checks क्रम allocs that are marked in some way as spanning multiple pages. */
अटल अंतरभूत व्योम check_page_span(स्थिर व्योम *ptr, अचिन्हित दीर्घ n,
				   काष्ठा page *page, bool to_user)
अणु
#अगर_घोषित CONFIG_HARDENED_USERCOPY_PAGESPAN
	स्थिर व्योम *end = ptr + n - 1;
	काष्ठा page *endpage;
	bool is_reserved, is_cma;

	/*
	 * Someबार the kernel data regions are not marked Reserved (see
	 * check below). And someबार [_sdata,_edata) करोes not cover
	 * rodata and/or bss, so check each range explicitly.
	 */

	/* Allow पढ़ोs of kernel rodata region (अगर not marked as Reserved). */
	अगर (ptr >= (स्थिर व्योम *)__start_rodata &&
	    end <= (स्थिर व्योम *)__end_rodata) अणु
		अगर (!to_user)
			usercopy_पात("rodata", शून्य, to_user, 0, n);
		वापस;
	पूर्ण

	/* Allow kernel data region (अगर not marked as Reserved). */
	अगर (ptr >= (स्थिर व्योम *)_sdata && end <= (स्थिर व्योम *)_edata)
		वापस;

	/* Allow kernel bss region (अगर not marked as Reserved). */
	अगर (ptr >= (स्थिर व्योम *)__bss_start &&
	    end <= (स्थिर व्योम *)__bss_stop)
		वापस;

	/* Is the object wholly within one base page? */
	अगर (likely(((अचिन्हित दीर्घ)ptr & (अचिन्हित दीर्घ)PAGE_MASK) ==
		   ((अचिन्हित दीर्घ)end & (अचिन्हित दीर्घ)PAGE_MASK)))
		वापस;

	/* Allow अगर fully inside the same compound (__GFP_COMP) page. */
	endpage = virt_to_head_page(end);
	अगर (likely(endpage == page))
		वापस;

	/*
	 * Reject अगर range is entirely either Reserved (i.e. special or
	 * device memory), or CMA. Otherwise, reject since the object spans
	 * several independently allocated pages.
	 */
	is_reserved = PageReserved(page);
	is_cma = is_migrate_cma_page(page);
	अगर (!is_reserved && !is_cma)
		usercopy_पात("spans multiple pages", शून्य, to_user, 0, n);

	क्रम (ptr += PAGE_SIZE; ptr <= end; ptr += PAGE_SIZE) अणु
		page = virt_to_head_page(ptr);
		अगर (is_reserved && !PageReserved(page))
			usercopy_पात("spans Reserved and non-Reserved pages",
				       शून्य, to_user, 0, n);
		अगर (is_cma && !is_migrate_cma_page(page))
			usercopy_पात("spans CMA and non-CMA pages", शून्य,
				       to_user, 0, n);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम check_heap_object(स्थिर व्योम *ptr, अचिन्हित दीर्घ n,
				     bool to_user)
अणु
	काष्ठा page *page;

	अगर (!virt_addr_valid(ptr))
		वापस;

	/*
	 * When CONFIG_HIGHMEM=y, kmap_to_page() will give either the
	 * highmem page or fallback to virt_to_page(). The following
	 * is effectively a highmem-aware virt_to_head_page().
	 */
	page = compound_head(kmap_to_page((व्योम *)ptr));

	अगर (PageSlab(page)) अणु
		/* Check slab allocator क्रम flags and size. */
		__check_heap_object(ptr, n, page, to_user);
	पूर्ण अन्यथा अणु
		/* Verअगरy object करोes not incorrectly span multiple pages. */
		check_page_span(ptr, n, page, to_user);
	पूर्ण
पूर्ण

अटल DEFINE_STATIC_KEY_FALSE_RO(bypass_usercopy_checks);

/*
 * Validates that the given object is:
 * - not bogus address
 * - fully contained by stack (or stack frame, when available)
 * - fully within SLAB object (or object whitelist area, when available)
 * - not in kernel text
 */
व्योम __check_object_size(स्थिर व्योम *ptr, अचिन्हित दीर्घ n, bool to_user)
अणु
	अगर (अटल_branch_unlikely(&bypass_usercopy_checks))
		वापस;

	/* Skip all tests अगर size is zero. */
	अगर (!n)
		वापस;

	/* Check क्रम invalid addresses. */
	check_bogus_address((स्थिर अचिन्हित दीर्घ)ptr, n, to_user);

	/* Check क्रम bad stack object. */
	चयन (check_stack_object(ptr, n)) अणु
	हाल NOT_STACK:
		/* Object is not touching the current process stack. */
		अवरोध;
	हाल GOOD_FRAME:
	हाल GOOD_STACK:
		/*
		 * Object is either in the correct frame (when it
		 * is possible to check) or just generally on the
		 * process stack (when frame checking not available).
		 */
		वापस;
	शेष:
		usercopy_पात("process stack", शून्य, to_user, 0, n);
	पूर्ण

	/* Check क्रम bad heap object. */
	check_heap_object(ptr, n, to_user);

	/* Check क्रम object in kernel to aव्योम text exposure. */
	check_kernel_text_object((स्थिर अचिन्हित दीर्घ)ptr, n, to_user);
पूर्ण
EXPORT_SYMBOL(__check_object_size);

अटल bool enable_checks __initdata = true;

अटल पूर्णांक __init parse_hardened_usercopy(अक्षर *str)
अणु
	वापस strtobool(str, &enable_checks);
पूर्ण

__setup("hardened_usercopy=", parse_hardened_usercopy);

अटल पूर्णांक __init set_hardened_usercopy(व्योम)
अणु
	अगर (enable_checks == false)
		अटल_branch_enable(&bypass_usercopy_checks);
	वापस 1;
पूर्ण

late_initcall(set_hardened_usercopy);
