<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	crash_dump.c - Memory preserving reboot related code.
 *
 *	Created by: Hariprasad Nellitheertha (hari@in.ibm.com)
 *	Copyright (C) IBM Corporation, 2004. All rights reserved
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/crash_dump.h>
#समावेश <linux/पन.स>
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
 */
sमाप_प्रकार copy_oldmem_page(अचिन्हित दीर्घ pfn, अक्षर *buf,
                               माप_प्रकार csize, अचिन्हित दीर्घ offset, पूर्णांक userbuf)
अणु
	व्योम  *vaddr;

	अगर (!csize)
		वापस 0;

	vaddr = ioremap(pfn << PAGE_SHIFT, PAGE_SIZE);

	अगर (userbuf) अणु
		अगर (copy_to_user(buf, (vaddr + offset), csize)) अणु
			iounmap(vaddr);
			वापस -EFAULT;
		पूर्ण
	पूर्ण अन्यथा
	स_नकल(buf, (vaddr + offset), csize);

	iounmap(vaddr);
	वापस csize;
पूर्ण
