<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* 
 * User address space access functions.
 *
 * Copyright 1997 Andi Kleen <ak@muc.de>
 * Copyright 1997 Linus Torvalds
 * Copyright 2002 Andi Kleen <ak@suse.de>
 */
#समावेश <linux/export.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/highस्मृति.स>

/*
 * Zero Userspace
 */

अचिन्हित दीर्घ __clear_user(व्योम __user *addr, अचिन्हित दीर्घ size)
अणु
	दीर्घ __d0;
	might_fault();
	/* no memory स्थिरraपूर्णांक because it करोesn't change any memory gcc knows
	   about */
	stac();
	यंत्र अस्थिर(
		"	testq  %[size8],%[size8]\n"
		"	jz     4f\n"
		"	.align 16\n"
		"0:	movq $0,(%[dst])\n"
		"	addq   $8,%[dst]\n"
		"	decl %%ecx ; jnz   0b\n"
		"4:	movq  %[size1],%%rcx\n"
		"	testl %%ecx,%%ecx\n"
		"	jz     2f\n"
		"1:	movb   $0,(%[dst])\n"
		"	incq   %[dst]\n"
		"	decl %%ecx ; jnz  1b\n"
		"2:\n"
		".section .fixup,\"ax\"\n"
		"3:	lea 0(%[size1],%[size8],8),%[size8]\n"
		"	jmp 2b\n"
		".previous\n"
		_ASM_EXTABLE_UA(0b, 3b)
		_ASM_EXTABLE_UA(1b, 2b)
		: [size8] "=&c"(size), [dst] "=&D" (__d0)
		: [size1] "r"(size & 7), "[size8]" (size / 8), "[dst]"(addr));
	clac();
	वापस size;
पूर्ण
EXPORT_SYMBOL(__clear_user);

अचिन्हित दीर्घ clear_user(व्योम __user *to, अचिन्हित दीर्घ n)
अणु
	अगर (access_ok(to, n))
		वापस __clear_user(to, n);
	वापस n;
पूर्ण
EXPORT_SYMBOL(clear_user);

#अगर_घोषित CONFIG_ARCH_HAS_UACCESS_FLUSHCACHE
/**
 * clean_cache_range - ग_लिखो back a cache range with CLWB
 * @vaddr:	भव start address
 * @size:	number of bytes to ग_लिखो back
 *
 * Write back a cache range using the CLWB (cache line ग_लिखो back)
 * inकाष्ठाion. Note that @size is पूर्णांकernally rounded up to be cache
 * line size aligned.
 */
अटल व्योम clean_cache_range(व्योम *addr, माप_प्रकार size)
अणु
	u16 x86_clflush_size = boot_cpu_data.x86_clflush_size;
	अचिन्हित दीर्घ clflush_mask = x86_clflush_size - 1;
	व्योम *vend = addr + size;
	व्योम *p;

	क्रम (p = (व्योम *)((अचिन्हित दीर्घ)addr & ~clflush_mask);
	     p < vend; p += x86_clflush_size)
		clwb(p);
पूर्ण

व्योम arch_wb_cache_pmem(व्योम *addr, माप_प्रकार size)
अणु
	clean_cache_range(addr, size);
पूर्ण
EXPORT_SYMBOL_GPL(arch_wb_cache_pmem);

दीर्घ __copy_user_flushcache(व्योम *dst, स्थिर व्योम __user *src, अचिन्हित size)
अणु
	अचिन्हित दीर्घ flushed, dest = (अचिन्हित दीर्घ) dst;
	दीर्घ rc = __copy_user_nocache(dst, src, size, 0);

	/*
	 * __copy_user_nocache() uses non-temporal stores क्रम the bulk
	 * of the transfer, but we need to manually flush अगर the
	 * transfer is unaligned. A cached memory copy is used when
	 * destination or size is not naturally aligned. That is:
	 *   - Require 8-byte alignment when size is 8 bytes or larger.
	 *   - Require 4-byte alignment when size is 4 bytes.
	 */
	अगर (size < 8) अणु
		अगर (!IS_ALIGNED(dest, 4) || size != 4)
			clean_cache_range(dst, size);
	पूर्ण अन्यथा अणु
		अगर (!IS_ALIGNED(dest, 8)) अणु
			dest = ALIGN(dest, boot_cpu_data.x86_clflush_size);
			clean_cache_range(dst, 1);
		पूर्ण

		flushed = dest - (अचिन्हित दीर्घ) dst;
		अगर (size > flushed && !IS_ALIGNED(size - flushed, 8))
			clean_cache_range(dst + size - 1, 1);
	पूर्ण

	वापस rc;
पूर्ण

व्योम __स_नकल_flushcache(व्योम *_dst, स्थिर व्योम *_src, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ dest = (अचिन्हित दीर्घ) _dst;
	अचिन्हित दीर्घ source = (अचिन्हित दीर्घ) _src;

	/* cache copy and flush to align dest */
	अगर (!IS_ALIGNED(dest, 8)) अणु
		अचिन्हित len = min_t(अचिन्हित, size, ALIGN(dest, 8) - dest);

		स_नकल((व्योम *) dest, (व्योम *) source, len);
		clean_cache_range((व्योम *) dest, len);
		dest += len;
		source += len;
		size -= len;
		अगर (!size)
			वापस;
	पूर्ण

	/* 4x8 movnti loop */
	जबतक (size >= 32) अणु
		यंत्र("movq    (%0), %%r8\n"
		    "movq   8(%0), %%r9\n"
		    "movq  16(%0), %%r10\n"
		    "movq  24(%0), %%r11\n"
		    "movnti  %%r8,   (%1)\n"
		    "movnti  %%r9,  8(%1)\n"
		    "movnti %%r10, 16(%1)\n"
		    "movnti %%r11, 24(%1)\n"
		    :: "r" (source), "r" (dest)
		    : "memory", "r8", "r9", "r10", "r11");
		dest += 32;
		source += 32;
		size -= 32;
	पूर्ण

	/* 1x8 movnti loop */
	जबतक (size >= 8) अणु
		यंत्र("movq    (%0), %%r8\n"
		    "movnti  %%r8,   (%1)\n"
		    :: "r" (source), "r" (dest)
		    : "memory", "r8");
		dest += 8;
		source += 8;
		size -= 8;
	पूर्ण

	/* 1x4 movnti loop */
	जबतक (size >= 4) अणु
		यंत्र("movl    (%0), %%r8d\n"
		    "movnti  %%r8d,   (%1)\n"
		    :: "r" (source), "r" (dest)
		    : "memory", "r8");
		dest += 4;
		source += 4;
		size -= 4;
	पूर्ण

	/* cache copy क्रम reमुख्यing bytes */
	अगर (size) अणु
		स_नकल((व्योम *) dest, (व्योम *) source, size);
		clean_cache_range((व्योम *) dest, size);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(__स_नकल_flushcache);

व्योम स_नकल_page_flushcache(अक्षर *to, काष्ठा page *page, माप_प्रकार offset,
		माप_प्रकार len)
अणु
	अक्षर *from = kmap_atomic(page);

	स_नकल_flushcache(to, from + offset, len);
	kunmap_atomic(from);
पूर्ण
#पूर्ण_अगर
