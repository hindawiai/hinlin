<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	kernel/crash_dump.c - Memory preserving reboot related code.
 *
 *	Created by: Simon Horman <horms@verge.net.au>
 *	Original code moved from kernel/crash.c
 *	Original code comment copied from the i386 version of this file
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/crash_dump.h>

#समावेश <यंत्र/page.h>
#समावेश <linux/uaccess.h>

/**
 * copy_oldmem_page - copy one page from "oldmem"
 * @pfn: page frame number to be copied
 * @buf: target memory address क्रम the copy; this can be in kernel address
 *	space or user address space (see @userbuf)
 * @csize: number of bytes to copy
 * @offset: offset in bytes पूर्णांकo the page (based on pfn) to begin the copy
 * @userbuf: अगर set, @buf is in user address space, use copy_to_user(),
 *	otherwise @buf is in kernel address space, use स_नकल().
 *
 * Copy a page from "oldmem". For this page, there is no pte mapped
 * in the current kernel. We stitch up a pte, similar to kmap_atomic.
 *
 * Calling copy_to_user() in atomic context is not desirable. Hence first
 * copying the data to a pre-allocated kernel page and then copying to user
 * space in non-atomic context.
 */
sमाप_प्रकार
copy_oldmem_page(अचिन्हित दीर्घ pfn, अक्षर *buf,
		माप_प्रकार csize, अचिन्हित दीर्घ offset, पूर्णांक userbuf)
अणु
	व्योम  *vaddr;

	अगर (!csize)
		वापस 0;
	vaddr = __va(pfn<<PAGE_SHIFT);
	अगर (userbuf) अणु
		अगर (copy_to_user(buf, (vaddr + offset), csize)) अणु
			वापस -EFAULT;
		पूर्ण
	पूर्ण अन्यथा
		स_नकल(buf, (vaddr + offset), csize);
	वापस csize;
पूर्ण

