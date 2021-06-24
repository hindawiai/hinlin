<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This code comes from arch/arm64/kernel/crash_dump.c
 * Created by: AKASHI Takahiro <takahiro.akashi@linaro.org>
 * Copyright (C) 2017 Linaro Limited
 */

#समावेश <linux/crash_dump.h>
#समावेश <linux/पन.स>

/**
 * copy_oldmem_page() - copy one page from old kernel memory
 * @pfn: page frame number to be copied
 * @buf: buffer where the copied page is placed
 * @csize: number of bytes to copy
 * @offset: offset in bytes पूर्णांकo the page
 * @userbuf: अगर set, @buf is in a user address space
 *
 * This function copies one page from old kernel memory पूर्णांकo buffer poपूर्णांकed by
 * @buf. If @buf is in userspace, set @userbuf to %1. Returns number of bytes
 * copied or negative error in हाल of failure.
 */
sमाप_प्रकार copy_oldmem_page(अचिन्हित दीर्घ pfn, अक्षर *buf,
			 माप_प्रकार csize, अचिन्हित दीर्घ offset,
			 पूर्णांक userbuf)
अणु
	व्योम *vaddr;

	अगर (!csize)
		वापस 0;

	vaddr = memremap(__pfn_to_phys(pfn), PAGE_SIZE, MEMREMAP_WB);
	अगर (!vaddr)
		वापस -ENOMEM;

	अगर (userbuf) अणु
		अगर (copy_to_user((अक्षर __user *)buf, vaddr + offset, csize)) अणु
			memunmap(vaddr);
			वापस -EFAULT;
		पूर्ण
	पूर्ण अन्यथा
		स_नकल(buf, vaddr + offset, csize);

	memunmap(vaddr);
	वापस csize;
पूर्ण
