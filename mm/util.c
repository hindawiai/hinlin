<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/compiler.h>
#समावेश <linux/export.h>
#समावेश <linux/err.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/security.h>
#समावेश <linux/swap.h>
#समावेश <linux/swapops.h>
#समावेश <linux/mman.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/userfaultfd_k.h>
#समावेश <linux/elf.h>
#समावेश <linux/elf-अक्रमomize.h>
#समावेश <linux/personality.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/processor.h>
#समावेश <linux/sizes.h>
#समावेश <linux/compat.h>

#समावेश <linux/uaccess.h>

#समावेश "internal.h"

/**
 * kमुक्त_स्थिर - conditionally मुक्त memory
 * @x: poपूर्णांकer to the memory
 *
 * Function calls kमुक्त only अगर @x is not in .rodata section.
 */
व्योम kमुक्त_स्थिर(स्थिर व्योम *x)
अणु
	अगर (!is_kernel_rodata((अचिन्हित दीर्घ)x))
		kमुक्त(x);
पूर्ण
EXPORT_SYMBOL(kमुक्त_स्थिर);

/**
 * kstrdup - allocate space क्रम and copy an existing string
 * @s: the string to duplicate
 * @gfp: the GFP mask used in the kदो_स्मृति() call when allocating memory
 *
 * Return: newly allocated copy of @s or %शून्य in हाल of error
 */
अक्षर *kstrdup(स्थिर अक्षर *s, gfp_t gfp)
अणु
	माप_प्रकार len;
	अक्षर *buf;

	अगर (!s)
		वापस शून्य;

	len = म_माप(s) + 1;
	buf = kदो_स्मृति_track_caller(len, gfp);
	अगर (buf)
		स_नकल(buf, s, len);
	वापस buf;
पूर्ण
EXPORT_SYMBOL(kstrdup);

/**
 * kstrdup_स्थिर - conditionally duplicate an existing स्थिर string
 * @s: the string to duplicate
 * @gfp: the GFP mask used in the kदो_स्मृति() call when allocating memory
 *
 * Note: Strings allocated by kstrdup_स्थिर should be मुक्तd by kमुक्त_स्थिर and
 * must not be passed to kपुनः_स्मृति().
 *
 * Return: source string अगर it is in .rodata section otherwise
 * fallback to kstrdup.
 */
स्थिर अक्षर *kstrdup_स्थिर(स्थिर अक्षर *s, gfp_t gfp)
अणु
	अगर (is_kernel_rodata((अचिन्हित दीर्घ)s))
		वापस s;

	वापस kstrdup(s, gfp);
पूर्ण
EXPORT_SYMBOL(kstrdup_स्थिर);

/**
 * kstrndup - allocate space क्रम and copy an existing string
 * @s: the string to duplicate
 * @max: पढ़ो at most @max अक्षरs from @s
 * @gfp: the GFP mask used in the kदो_स्मृति() call when allocating memory
 *
 * Note: Use kmemdup_nul() instead अगर the size is known exactly.
 *
 * Return: newly allocated copy of @s or %शून्य in हाल of error
 */
अक्षर *kstrndup(स्थिर अक्षर *s, माप_प्रकार max, gfp_t gfp)
अणु
	माप_प्रकार len;
	अक्षर *buf;

	अगर (!s)
		वापस शून्य;

	len = strnlen(s, max);
	buf = kदो_स्मृति_track_caller(len+1, gfp);
	अगर (buf) अणु
		स_नकल(buf, s, len);
		buf[len] = '\0';
	पूर्ण
	वापस buf;
पूर्ण
EXPORT_SYMBOL(kstrndup);

/**
 * kmemdup - duplicate region of memory
 *
 * @src: memory region to duplicate
 * @len: memory region length
 * @gfp: GFP mask to use
 *
 * Return: newly allocated copy of @src or %शून्य in हाल of error
 */
व्योम *kmemdup(स्थिर व्योम *src, माप_प्रकार len, gfp_t gfp)
अणु
	व्योम *p;

	p = kदो_स्मृति_track_caller(len, gfp);
	अगर (p)
		स_नकल(p, src, len);
	वापस p;
पूर्ण
EXPORT_SYMBOL(kmemdup);

/**
 * kmemdup_nul - Create a NUL-terminated string from unterminated data
 * @s: The data to stringअगरy
 * @len: The size of the data
 * @gfp: the GFP mask used in the kदो_स्मृति() call when allocating memory
 *
 * Return: newly allocated copy of @s with NUL-termination or %शून्य in
 * हाल of error
 */
अक्षर *kmemdup_nul(स्थिर अक्षर *s, माप_प्रकार len, gfp_t gfp)
अणु
	अक्षर *buf;

	अगर (!s)
		वापस शून्य;

	buf = kदो_स्मृति_track_caller(len + 1, gfp);
	अगर (buf) अणु
		स_नकल(buf, s, len);
		buf[len] = '\0';
	पूर्ण
	वापस buf;
पूर्ण
EXPORT_SYMBOL(kmemdup_nul);

/**
 * memdup_user - duplicate memory region from user space
 *
 * @src: source address in user space
 * @len: number of bytes to copy
 *
 * Return: an ERR_PTR() on failure.  Result is physically
 * contiguous, to be मुक्तd by kमुक्त().
 */
व्योम *memdup_user(स्थिर व्योम __user *src, माप_प्रकार len)
अणु
	व्योम *p;

	p = kदो_स्मृति_track_caller(len, GFP_USER | __GFP_NOWARN);
	अगर (!p)
		वापस ERR_PTR(-ENOMEM);

	अगर (copy_from_user(p, src, len)) अणु
		kमुक्त(p);
		वापस ERR_PTR(-EFAULT);
	पूर्ण

	वापस p;
पूर्ण
EXPORT_SYMBOL(memdup_user);

/**
 * vmemdup_user - duplicate memory region from user space
 *
 * @src: source address in user space
 * @len: number of bytes to copy
 *
 * Return: an ERR_PTR() on failure.  Result may be not
 * physically contiguous.  Use kvमुक्त() to मुक्त.
 */
व्योम *vmemdup_user(स्थिर व्योम __user *src, माप_प्रकार len)
अणु
	व्योम *p;

	p = kvदो_स्मृति(len, GFP_USER);
	अगर (!p)
		वापस ERR_PTR(-ENOMEM);

	अगर (copy_from_user(p, src, len)) अणु
		kvमुक्त(p);
		वापस ERR_PTR(-EFAULT);
	पूर्ण

	वापस p;
पूर्ण
EXPORT_SYMBOL(vmemdup_user);

/**
 * strndup_user - duplicate an existing string from user space
 * @s: The string to duplicate
 * @n: Maximum number of bytes to copy, including the trailing NUL.
 *
 * Return: newly allocated copy of @s or an ERR_PTR() in हाल of error
 */
अक्षर *strndup_user(स्थिर अक्षर __user *s, दीर्घ n)
अणु
	अक्षर *p;
	दीर्घ length;

	length = strnlen_user(s, n);

	अगर (!length)
		वापस ERR_PTR(-EFAULT);

	अगर (length > n)
		वापस ERR_PTR(-EINVAL);

	p = memdup_user(s, length);

	अगर (IS_ERR(p))
		वापस p;

	p[length - 1] = '\0';

	वापस p;
पूर्ण
EXPORT_SYMBOL(strndup_user);

/**
 * memdup_user_nul - duplicate memory region from user space and NUL-terminate
 *
 * @src: source address in user space
 * @len: number of bytes to copy
 *
 * Return: an ERR_PTR() on failure.
 */
व्योम *memdup_user_nul(स्थिर व्योम __user *src, माप_प्रकार len)
अणु
	अक्षर *p;

	/*
	 * Always use GFP_KERNEL, since copy_from_user() can sleep and
	 * cause pagefault, which makes it poपूर्णांकless to use GFP_NOFS
	 * or GFP_ATOMIC.
	 */
	p = kदो_स्मृति_track_caller(len + 1, GFP_KERNEL);
	अगर (!p)
		वापस ERR_PTR(-ENOMEM);

	अगर (copy_from_user(p, src, len)) अणु
		kमुक्त(p);
		वापस ERR_PTR(-EFAULT);
	पूर्ण
	p[len] = '\0';

	वापस p;
पूर्ण
EXPORT_SYMBOL(memdup_user_nul);

व्योम __vma_link_list(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma,
		काष्ठा vm_area_काष्ठा *prev)
अणु
	काष्ठा vm_area_काष्ठा *next;

	vma->vm_prev = prev;
	अगर (prev) अणु
		next = prev->vm_next;
		prev->vm_next = vma;
	पूर्ण अन्यथा अणु
		next = mm->mmap;
		mm->mmap = vma;
	पूर्ण
	vma->vm_next = next;
	अगर (next)
		next->vm_prev = vma;
पूर्ण

व्योम __vma_unlink_list(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा vm_area_काष्ठा *prev, *next;

	next = vma->vm_next;
	prev = vma->vm_prev;
	अगर (prev)
		prev->vm_next = next;
	अन्यथा
		mm->mmap = next;
	अगर (next)
		next->vm_prev = prev;
पूर्ण

/* Check अगर the vma is being used as a stack by this task */
पूर्णांक vma_is_stack_क्रम_current(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा task_काष्ठा * __maybe_unused t = current;

	वापस (vma->vm_start <= KSTK_ESP(t) && vma->vm_end >= KSTK_ESP(t));
पूर्ण

/*
 * Change backing file, only valid to use during initial VMA setup.
 */
व्योम vma_set_file(काष्ठा vm_area_काष्ठा *vma, काष्ठा file *file)
अणु
	/* Changing an anonymous vma with this is illegal */
	get_file(file);
	swap(vma->vm_file, file);
	fput(file);
पूर्ण
EXPORT_SYMBOL(vma_set_file);

#अगर_अघोषित STACK_RND_MASK
#घोषणा STACK_RND_MASK (0x7ff >> (PAGE_SHIFT - 12))     /* 8MB of VA */
#पूर्ण_अगर

अचिन्हित दीर्घ अक्रमomize_stack_top(अचिन्हित दीर्घ stack_top)
अणु
	अचिन्हित दीर्घ अक्रमom_variable = 0;

	अगर (current->flags & PF_RANDOMIZE) अणु
		अक्रमom_variable = get_अक्रमom_दीर्घ();
		अक्रमom_variable &= STACK_RND_MASK;
		अक्रमom_variable <<= PAGE_SHIFT;
	पूर्ण
#अगर_घोषित CONFIG_STACK_GROWSUP
	वापस PAGE_ALIGN(stack_top) + अक्रमom_variable;
#अन्यथा
	वापस PAGE_ALIGN(stack_top) - अक्रमom_variable;
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_ARCH_WANT_DEFAULT_TOPDOWN_MMAP_LAYOUT
अचिन्हित दीर्घ arch_अक्रमomize_brk(काष्ठा mm_काष्ठा *mm)
अणु
	/* Is the current task 32bit ? */
	अगर (!IS_ENABLED(CONFIG_64BIT) || is_compat_task())
		वापस अक्रमomize_page(mm->brk, SZ_32M);

	वापस अक्रमomize_page(mm->brk, SZ_1G);
पूर्ण

अचिन्हित दीर्घ arch_mmap_rnd(व्योम)
अणु
	अचिन्हित दीर्घ rnd;

#अगर_घोषित CONFIG_HAVE_ARCH_MMAP_RND_COMPAT_BITS
	अगर (is_compat_task())
		rnd = get_अक्रमom_दीर्घ() & ((1UL << mmap_rnd_compat_bits) - 1);
	अन्यथा
#पूर्ण_अगर /* CONFIG_HAVE_ARCH_MMAP_RND_COMPAT_BITS */
		rnd = get_अक्रमom_दीर्घ() & ((1UL << mmap_rnd_bits) - 1);

	वापस rnd << PAGE_SHIFT;
पूर्ण

अटल पूर्णांक mmap_is_legacy(काष्ठा rlimit *rlim_stack)
अणु
	अगर (current->personality & ADDR_COMPAT_LAYOUT)
		वापस 1;

	अगर (rlim_stack->rlim_cur == RLIM_अनन्त)
		वापस 1;

	वापस sysctl_legacy_va_layout;
पूर्ण

/*
 * Leave enough space between the mmap area and the stack to honour ulimit in
 * the face of अक्रमomisation.
 */
#घोषणा MIN_GAP		(SZ_128M)
#घोषणा MAX_GAP		(STACK_TOP / 6 * 5)

अटल अचिन्हित दीर्घ mmap_base(अचिन्हित दीर्घ rnd, काष्ठा rlimit *rlim_stack)
अणु
	अचिन्हित दीर्घ gap = rlim_stack->rlim_cur;
	अचिन्हित दीर्घ pad = stack_guard_gap;

	/* Account क्रम stack अक्रमomization अगर necessary */
	अगर (current->flags & PF_RANDOMIZE)
		pad += (STACK_RND_MASK << PAGE_SHIFT);

	/* Values बंद to RLIM_अनन्त can overflow. */
	अगर (gap + pad > gap)
		gap += pad;

	अगर (gap < MIN_GAP)
		gap = MIN_GAP;
	अन्यथा अगर (gap > MAX_GAP)
		gap = MAX_GAP;

	वापस PAGE_ALIGN(STACK_TOP - gap - rnd);
पूर्ण

व्योम arch_pick_mmap_layout(काष्ठा mm_काष्ठा *mm, काष्ठा rlimit *rlim_stack)
अणु
	अचिन्हित दीर्घ अक्रमom_factor = 0UL;

	अगर (current->flags & PF_RANDOMIZE)
		अक्रमom_factor = arch_mmap_rnd();

	अगर (mmap_is_legacy(rlim_stack)) अणु
		mm->mmap_base = TASK_UNMAPPED_BASE + अक्रमom_factor;
		mm->get_unmapped_area = arch_get_unmapped_area;
	पूर्ण अन्यथा अणु
		mm->mmap_base = mmap_base(अक्रमom_factor, rlim_stack);
		mm->get_unmapped_area = arch_get_unmapped_area_topकरोwn;
	पूर्ण
पूर्ण
#या_अगर defined(CONFIG_MMU) && !defined(HAVE_ARCH_PICK_MMAP_LAYOUT)
व्योम arch_pick_mmap_layout(काष्ठा mm_काष्ठा *mm, काष्ठा rlimit *rlim_stack)
अणु
	mm->mmap_base = TASK_UNMAPPED_BASE;
	mm->get_unmapped_area = arch_get_unmapped_area;
पूर्ण
#पूर्ण_अगर

/**
 * __account_locked_vm - account locked pages to an mm's locked_vm
 * @mm:          mm to account against
 * @pages:       number of pages to account
 * @inc:         %true अगर @pages should be considered positive, %false अगर not
 * @task:        task used to check RLIMIT_MEMLOCK
 * @bypass_rlim: %true अगर checking RLIMIT_MEMLOCK should be skipped
 *
 * Assumes @task and @mm are valid (i.e. at least one reference on each), and
 * that mmap_lock is held as ग_लिखोr.
 *
 * Return:
 * * 0       on success
 * * -ENOMEM अगर RLIMIT_MEMLOCK would be exceeded.
 */
पूर्णांक __account_locked_vm(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ pages, bool inc,
			काष्ठा task_काष्ठा *task, bool bypass_rlim)
अणु
	अचिन्हित दीर्घ locked_vm, limit;
	पूर्णांक ret = 0;

	mmap_निश्चित_ग_लिखो_locked(mm);

	locked_vm = mm->locked_vm;
	अगर (inc) अणु
		अगर (!bypass_rlim) अणु
			limit = task_rlimit(task, RLIMIT_MEMLOCK) >> PAGE_SHIFT;
			अगर (locked_vm + pages > limit)
				ret = -ENOMEM;
		पूर्ण
		अगर (!ret)
			mm->locked_vm = locked_vm + pages;
	पूर्ण अन्यथा अणु
		WARN_ON_ONCE(pages > locked_vm);
		mm->locked_vm = locked_vm - pages;
	पूर्ण

	pr_debug("%s: [%d] caller %ps %c%lu %lu/%lu%s\n", __func__, task->pid,
		 (व्योम *)_RET_IP_, (inc) ? '+' : '-', pages << PAGE_SHIFT,
		 locked_vm << PAGE_SHIFT, task_rlimit(task, RLIMIT_MEMLOCK),
		 ret ? " - exceeded" : "");

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__account_locked_vm);

/**
 * account_locked_vm - account locked pages to an mm's locked_vm
 * @mm:          mm to account against, may be शून्य
 * @pages:       number of pages to account
 * @inc:         %true अगर @pages should be considered positive, %false अगर not
 *
 * Assumes a non-शून्य @mm is valid (i.e. at least one reference on it).
 *
 * Return:
 * * 0       on success, or अगर mm is शून्य
 * * -ENOMEM अगर RLIMIT_MEMLOCK would be exceeded.
 */
पूर्णांक account_locked_vm(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ pages, bool inc)
अणु
	पूर्णांक ret;

	अगर (pages == 0 || !mm)
		वापस 0;

	mmap_ग_लिखो_lock(mm);
	ret = __account_locked_vm(mm, pages, inc, current,
				  capable(CAP_IPC_LOCK));
	mmap_ग_लिखो_unlock(mm);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(account_locked_vm);

अचिन्हित दीर्घ vm_mmap_pgoff(काष्ठा file *file, अचिन्हित दीर्घ addr,
	अचिन्हित दीर्घ len, अचिन्हित दीर्घ prot,
	अचिन्हित दीर्घ flag, अचिन्हित दीर्घ pgoff)
अणु
	अचिन्हित दीर्घ ret;
	काष्ठा mm_काष्ठा *mm = current->mm;
	अचिन्हित दीर्घ populate;
	LIST_HEAD(uf);

	ret = security_mmap_file(file, prot, flag);
	अगर (!ret) अणु
		अगर (mmap_ग_लिखो_lock_समाप्तable(mm))
			वापस -EINTR;
		ret = करो_mmap(file, addr, len, prot, flag, pgoff, &populate,
			      &uf);
		mmap_ग_लिखो_unlock(mm);
		userfaultfd_unmap_complete(mm, &uf);
		अगर (populate)
			mm_populate(ret, populate);
	पूर्ण
	वापस ret;
पूर्ण

अचिन्हित दीर्घ vm_mmap(काष्ठा file *file, अचिन्हित दीर्घ addr,
	अचिन्हित दीर्घ len, अचिन्हित दीर्घ prot,
	अचिन्हित दीर्घ flag, अचिन्हित दीर्घ offset)
अणु
	अगर (unlikely(offset + PAGE_ALIGN(len) < offset))
		वापस -EINVAL;
	अगर (unlikely(offset_in_page(offset)))
		वापस -EINVAL;

	वापस vm_mmap_pgoff(file, addr, len, prot, flag, offset >> PAGE_SHIFT);
पूर्ण
EXPORT_SYMBOL(vm_mmap);

/**
 * kvदो_स्मृति_node - attempt to allocate physically contiguous memory, but upon
 * failure, fall back to non-contiguous (vदो_स्मृति) allocation.
 * @size: size of the request.
 * @flags: gfp mask क्रम the allocation - must be compatible (superset) with GFP_KERNEL.
 * @node: numa node to allocate from
 *
 * Uses kदो_स्मृति to get the memory but अगर the allocation fails then falls back
 * to the vदो_स्मृति allocator. Use kvमुक्त क्रम मुक्तing the memory.
 *
 * Reclaim modअगरiers - __GFP_NORETRY and __GFP_NOFAIL are not supported.
 * __GFP_RETRY_MAYFAIL is supported, and it should be used only अगर kदो_स्मृति is
 * preferable to the vदो_स्मृति fallback, due to visible perक्रमmance drawbacks.
 *
 * Please note that any use of gfp flags outside of GFP_KERNEL is careful to not
 * fall back to vदो_स्मृति.
 *
 * Return: poपूर्णांकer to the allocated memory of %शून्य in हाल of failure
 */
व्योम *kvदो_स्मृति_node(माप_प्रकार size, gfp_t flags, पूर्णांक node)
अणु
	gfp_t kदो_स्मृति_flags = flags;
	व्योम *ret;

	/*
	 * vदो_स्मृति uses GFP_KERNEL क्रम some पूर्णांकernal allocations (e.g page tables)
	 * so the given set of flags has to be compatible.
	 */
	अगर ((flags & GFP_KERNEL) != GFP_KERNEL)
		वापस kदो_स्मृति_node(size, flags, node);

	/*
	 * We want to attempt a large physically contiguous block first because
	 * it is less likely to fragment multiple larger blocks and thereक्रमe
	 * contribute to a दीर्घ term fragmentation less than vदो_स्मृति fallback.
	 * However make sure that larger requests are not too disruptive - no
	 * OOM समाप्तer and no allocation failure warnings as we have a fallback.
	 */
	अगर (size > PAGE_SIZE) अणु
		kदो_स्मृति_flags |= __GFP_NOWARN;

		अगर (!(kदो_स्मृति_flags & __GFP_RETRY_MAYFAIL))
			kदो_स्मृति_flags |= __GFP_NORETRY;
	पूर्ण

	ret = kदो_स्मृति_node(size, kदो_स्मृति_flags, node);

	/*
	 * It करोesn't really make sense to fallback to vदो_स्मृति क्रम sub page
	 * requests
	 */
	अगर (ret || size <= PAGE_SIZE)
		वापस ret;

	वापस __vदो_स्मृति_node(size, 1, flags, node,
			__builtin_वापस_address(0));
पूर्ण
EXPORT_SYMBOL(kvदो_स्मृति_node);

/**
 * kvमुक्त() - Free memory.
 * @addr: Poपूर्णांकer to allocated memory.
 *
 * kvमुक्त मुक्तs memory allocated by any of vदो_स्मृति(), kदो_स्मृति() or kvदो_स्मृति().
 * It is slightly more efficient to use kमुक्त() or vमुक्त() अगर you are certain
 * that you know which one to use.
 *
 * Context: Either preemptible task context or not-NMI पूर्णांकerrupt.
 */
व्योम kvमुक्त(स्थिर व्योम *addr)
अणु
	अगर (is_vदो_स्मृति_addr(addr))
		vमुक्त(addr);
	अन्यथा
		kमुक्त(addr);
पूर्ण
EXPORT_SYMBOL(kvमुक्त);

/**
 * kvमुक्त_sensitive - Free a data object containing sensitive inक्रमmation.
 * @addr: address of the data object to be मुक्तd.
 * @len: length of the data object.
 *
 * Use the special memzero_explicit() function to clear the content of a
 * kvदो_स्मृति'ed object containing sensitive data to make sure that the
 * compiler won't optimize out the data clearing.
 */
व्योम kvमुक्त_sensitive(स्थिर व्योम *addr, माप_प्रकार len)
अणु
	अगर (likely(!ZERO_OR_शून्य_PTR(addr))) अणु
		memzero_explicit((व्योम *)addr, len);
		kvमुक्त(addr);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(kvमुक्त_sensitive);

अटल अंतरभूत व्योम *__page_rmapping(काष्ठा page *page)
अणु
	अचिन्हित दीर्घ mapping;

	mapping = (अचिन्हित दीर्घ)page->mapping;
	mapping &= ~PAGE_MAPPING_FLAGS;

	वापस (व्योम *)mapping;
पूर्ण

/* Neutral page->mapping poपूर्णांकer to address_space or anon_vma or other */
व्योम *page_rmapping(काष्ठा page *page)
अणु
	page = compound_head(page);
	वापस __page_rmapping(page);
पूर्ण

/*
 * Return true अगर this page is mapped पूर्णांकo pagetables.
 * For compound page it वापसs true अगर any subpage of compound page is mapped.
 */
bool page_mapped(काष्ठा page *page)
अणु
	पूर्णांक i;

	अगर (likely(!PageCompound(page)))
		वापस atomic_पढ़ो(&page->_mapcount) >= 0;
	page = compound_head(page);
	अगर (atomic_पढ़ो(compound_mapcount_ptr(page)) >= 0)
		वापस true;
	अगर (PageHuge(page))
		वापस false;
	क्रम (i = 0; i < compound_nr(page); i++) अणु
		अगर (atomic_पढ़ो(&page[i]._mapcount) >= 0)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण
EXPORT_SYMBOL(page_mapped);

काष्ठा anon_vma *page_anon_vma(काष्ठा page *page)
अणु
	अचिन्हित दीर्घ mapping;

	page = compound_head(page);
	mapping = (अचिन्हित दीर्घ)page->mapping;
	अगर ((mapping & PAGE_MAPPING_FLAGS) != PAGE_MAPPING_ANON)
		वापस शून्य;
	वापस __page_rmapping(page);
पूर्ण

काष्ठा address_space *page_mapping(काष्ठा page *page)
अणु
	काष्ठा address_space *mapping;

	page = compound_head(page);

	/* This happens अगर someone calls flush_dcache_page on slab page */
	अगर (unlikely(PageSlab(page)))
		वापस शून्य;

	अगर (unlikely(PageSwapCache(page))) अणु
		swp_entry_t entry;

		entry.val = page_निजी(page);
		वापस swap_address_space(entry);
	पूर्ण

	mapping = page->mapping;
	अगर ((अचिन्हित दीर्घ)mapping & PAGE_MAPPING_ANON)
		वापस शून्य;

	वापस (व्योम *)((अचिन्हित दीर्घ)mapping & ~PAGE_MAPPING_FLAGS);
पूर्ण
EXPORT_SYMBOL(page_mapping);

/* Slow path of page_mapcount() क्रम compound pages */
पूर्णांक __page_mapcount(काष्ठा page *page)
अणु
	पूर्णांक ret;

	ret = atomic_पढ़ो(&page->_mapcount) + 1;
	/*
	 * For file THP page->_mapcount contains total number of mapping
	 * of the page: no need to look पूर्णांकo compound_mapcount.
	 */
	अगर (!PageAnon(page) && !PageHuge(page))
		वापस ret;
	page = compound_head(page);
	ret += atomic_पढ़ो(compound_mapcount_ptr(page)) + 1;
	अगर (PageDoubleMap(page))
		ret--;
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__page_mapcount);

पूर्णांक sysctl_overcommit_memory __पढ़ो_mostly = OVERCOMMIT_GUESS;
पूर्णांक sysctl_overcommit_ratio __पढ़ो_mostly = 50;
अचिन्हित दीर्घ sysctl_overcommit_kbytes __पढ़ो_mostly;
पूर्णांक sysctl_max_map_count __पढ़ो_mostly = DEFAULT_MAX_MAP_COUNT;
अचिन्हित दीर्घ sysctl_user_reserve_kbytes __पढ़ो_mostly = 1UL << 17; /* 128MB */
अचिन्हित दीर्घ sysctl_admin_reserve_kbytes __पढ़ो_mostly = 1UL << 13; /* 8MB */

पूर्णांक overcommit_ratio_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो, व्योम *buffer,
		माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक ret;

	ret = proc_करोपूर्णांकvec(table, ग_लिखो, buffer, lenp, ppos);
	अगर (ret == 0 && ग_लिखो)
		sysctl_overcommit_kbytes = 0;
	वापस ret;
पूर्ण

अटल व्योम sync_overcommit_as(काष्ठा work_काष्ठा *dummy)
अणु
	percpu_counter_sync(&vm_committed_as);
पूर्ण

पूर्णांक overcommit_policy_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो, व्योम *buffer,
		माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा ctl_table t;
	पूर्णांक new_policy;
	पूर्णांक ret;

	/*
	 * The deviation of sync_overcommit_as could be big with loose policy
	 * like OVERCOMMIT_ALWAYS/OVERCOMMIT_GUESS. When changing policy to
	 * strict OVERCOMMIT_NEVER, we need to reduce the deviation to comply
	 * with the strict "NEVER", and to aव्योम possible race condition (even
	 * though user usually won't too frequently करो the चयनing to policy
	 * OVERCOMMIT_NEVER), the चयन is करोne in the following order:
	 *	1. changing the batch
	 *	2. sync percpu count on each CPU
	 *	3. चयन the policy
	 */
	अगर (ग_लिखो) अणु
		t = *table;
		t.data = &new_policy;
		ret = proc_करोपूर्णांकvec_minmax(&t, ग_लिखो, buffer, lenp, ppos);
		अगर (ret)
			वापस ret;

		mm_compute_batch(new_policy);
		अगर (new_policy == OVERCOMMIT_NEVER)
			schedule_on_each_cpu(sync_overcommit_as);
		sysctl_overcommit_memory = new_policy;
	पूर्ण अन्यथा अणु
		ret = proc_करोपूर्णांकvec_minmax(table, ग_लिखो, buffer, lenp, ppos);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक overcommit_kbytes_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो, व्योम *buffer,
		माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक ret;

	ret = proc_करोuदीर्घvec_minmax(table, ग_लिखो, buffer, lenp, ppos);
	अगर (ret == 0 && ग_लिखो)
		sysctl_overcommit_ratio = 0;
	वापस ret;
पूर्ण

/*
 * Committed memory limit enक्रमced when OVERCOMMIT_NEVER policy is used
 */
अचिन्हित दीर्घ vm_commit_limit(व्योम)
अणु
	अचिन्हित दीर्घ allowed;

	अगर (sysctl_overcommit_kbytes)
		allowed = sysctl_overcommit_kbytes >> (PAGE_SHIFT - 10);
	अन्यथा
		allowed = ((totalram_pages() - hugetlb_total_pages())
			   * sysctl_overcommit_ratio / 100);
	allowed += total_swap_pages;

	वापस allowed;
पूर्ण

/*
 * Make sure vm_committed_as in one cacheline and not cacheline shared with
 * other variables. It can be updated by several CPUs frequently.
 */
काष्ठा percpu_counter vm_committed_as ____cacheline_aligned_in_smp;

/*
 * The global memory commiपंचांगent made in the प्रणाली can be a metric
 * that can be used to drive ballooning decisions when Linux is hosted
 * as a guest. On Hyper-V, the host implements a policy engine क्रम dynamically
 * balancing memory across competing भव machines that are hosted.
 * Several metrics drive this policy engine including the guest reported
 * memory commiपंचांगent.
 *
 * The समय cost of this is very low क्रम small platक्रमms, and क्रम big
 * platक्रमm like a 2S/36C/72T Skylake server, in worst हाल where
 * vm_committed_as's spinlock is under severe contention, the समय cost
 * could be about 30~40 microseconds.
 */
अचिन्हित दीर्घ vm_memory_committed(व्योम)
अणु
	वापस percpu_counter_sum_positive(&vm_committed_as);
पूर्ण
EXPORT_SYMBOL_GPL(vm_memory_committed);

/*
 * Check that a process has enough memory to allocate a new भव
 * mapping. 0 means there is enough memory क्रम the allocation to
 * succeed and -ENOMEM implies there is not.
 *
 * We currently support three overcommit policies, which are set via the
 * vm.overcommit_memory sysctl.  See Documentation/vm/overcommit-accounting.rst
 *
 * Strict overcommit modes added 2002 Feb 26 by Alan Cox.
 * Additional code 2002 Jul 20 by Robert Love.
 *
 * cap_sys_admin is 1 अगर the process has admin privileges, 0 otherwise.
 *
 * Note this is a helper function पूर्णांकended to be used by LSMs which
 * wish to use this logic.
 */
पूर्णांक __vm_enough_memory(काष्ठा mm_काष्ठा *mm, दीर्घ pages, पूर्णांक cap_sys_admin)
अणु
	दीर्घ allowed;

	vm_acct_memory(pages);

	/*
	 * Someबार we want to use more memory than we have
	 */
	अगर (sysctl_overcommit_memory == OVERCOMMIT_ALWAYS)
		वापस 0;

	अगर (sysctl_overcommit_memory == OVERCOMMIT_GUESS) अणु
		अगर (pages > totalram_pages() + total_swap_pages)
			जाओ error;
		वापस 0;
	पूर्ण

	allowed = vm_commit_limit();
	/*
	 * Reserve some क्रम root
	 */
	अगर (!cap_sys_admin)
		allowed -= sysctl_admin_reserve_kbytes >> (PAGE_SHIFT - 10);

	/*
	 * Don't let a single process grow so big a user can't recover
	 */
	अगर (mm) अणु
		दीर्घ reserve = sysctl_user_reserve_kbytes >> (PAGE_SHIFT - 10);

		allowed -= min_t(दीर्घ, mm->total_vm / 32, reserve);
	पूर्ण

	अगर (percpu_counter_पढ़ो_positive(&vm_committed_as) < allowed)
		वापस 0;
error:
	vm_unacct_memory(pages);

	वापस -ENOMEM;
पूर्ण

/**
 * get_cmdline() - copy the cmdline value to a buffer.
 * @task:     the task whose cmdline value to copy.
 * @buffer:   the buffer to copy to.
 * @buflen:   the length of the buffer. Larger cmdline values are truncated
 *            to this length.
 *
 * Return: the size of the cmdline field copied. Note that the copy करोes
 * not guarantee an ending शून्य byte.
 */
पूर्णांक get_cmdline(काष्ठा task_काष्ठा *task, अक्षर *buffer, पूर्णांक buflen)
अणु
	पूर्णांक res = 0;
	अचिन्हित पूर्णांक len;
	काष्ठा mm_काष्ठा *mm = get_task_mm(task);
	अचिन्हित दीर्घ arg_start, arg_end, env_start, env_end;
	अगर (!mm)
		जाओ out;
	अगर (!mm->arg_end)
		जाओ out_mm;	/* Shh! No looking beक्रमe we're करोne */

	spin_lock(&mm->arg_lock);
	arg_start = mm->arg_start;
	arg_end = mm->arg_end;
	env_start = mm->env_start;
	env_end = mm->env_end;
	spin_unlock(&mm->arg_lock);

	len = arg_end - arg_start;

	अगर (len > buflen)
		len = buflen;

	res = access_process_vm(task, arg_start, buffer, len, FOLL_FORCE);

	/*
	 * If the nul at the end of args has been overwritten, then
	 * assume application is using setproctitle(3).
	 */
	अगर (res > 0 && buffer[res-1] != '\0' && len < buflen) अणु
		len = strnlen(buffer, res);
		अगर (len < res) अणु
			res = len;
		पूर्ण अन्यथा अणु
			len = env_end - env_start;
			अगर (len > buflen - res)
				len = buflen - res;
			res += access_process_vm(task, env_start,
						 buffer+res, len,
						 FOLL_FORCE);
			res = strnlen(buffer, res);
		पूर्ण
	पूर्ण
out_mm:
	mmput(mm);
out:
	वापस res;
पूर्ण

पूर्णांक __weak स_भेद_pages(काष्ठा page *page1, काष्ठा page *page2)
अणु
	अक्षर *addr1, *addr2;
	पूर्णांक ret;

	addr1 = kmap_atomic(page1);
	addr2 = kmap_atomic(page2);
	ret = स_भेद(addr1, addr2, PAGE_SIZE);
	kunmap_atomic(addr2);
	kunmap_atomic(addr1);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PRINTK
/**
 * mem_dump_obj - Prपूर्णांक available provenance inक्रमmation
 * @object: object क्रम which to find provenance inक्रमmation.
 *
 * This function uses pr_cont(), so that the caller is expected to have
 * prपूर्णांकed out whatever preamble is appropriate.  The provenance inक्रमmation
 * depends on the type of object and on how much debugging is enabled.
 * For example, क्रम a slab-cache object, the slab name is prपूर्णांकed, and,
 * अगर available, the वापस address and stack trace from the allocation
 * of that object.
 */
व्योम mem_dump_obj(व्योम *object)
अणु
	स्थिर अक्षर *type;

	अगर (kmem_valid_obj(object)) अणु
		kmem_dump_obj(object);
		वापस;
	पूर्ण

	अगर (vदो_स्मृति_dump_obj(object))
		वापस;

	अगर (virt_addr_valid(object))
		type = "non-slab/vmalloc memory";
	अन्यथा अगर (object == शून्य)
		type = "NULL pointer";
	अन्यथा अगर (object == ZERO_SIZE_PTR)
		type = "zero-size pointer";
	अन्यथा
		type = "non-paged memory";

	pr_cont(" %s\n", type);
पूर्ण
EXPORT_SYMBOL_GPL(mem_dump_obj);
#पूर्ण_अगर
