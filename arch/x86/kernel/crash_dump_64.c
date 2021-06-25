<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	Memory preserving reboot related code.
 *
 *	Created by: Hariprasad Nellitheertha (hari@in.ibm.com)
 *	Copyright (C) IBM Corporation, 2004. All rights reserved
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/crash_dump.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>

अटल sमाप_प्रकार __copy_oldmem_page(अचिन्हित दीर्घ pfn, अक्षर *buf, माप_प्रकार csize,
				  अचिन्हित दीर्घ offset, पूर्णांक userbuf,
				  bool encrypted)
अणु
	व्योम  *vaddr;

	अगर (!csize)
		वापस 0;

	अगर (encrypted)
		vaddr = (__क्रमce व्योम *)ioremap_encrypted(pfn << PAGE_SHIFT, PAGE_SIZE);
	अन्यथा
		vaddr = (__क्रमce व्योम *)ioremap_cache(pfn << PAGE_SHIFT, PAGE_SIZE);

	अगर (!vaddr)
		वापस -ENOMEM;

	अगर (userbuf) अणु
		अगर (copy_to_user((व्योम __user *)buf, vaddr + offset, csize)) अणु
			iounmap((व्योम __iomem *)vaddr);
			वापस -EFAULT;
		पूर्ण
	पूर्ण अन्यथा
		स_नकल(buf, vaddr + offset, csize);

	set_iounmap_nonlazy();
	iounmap((व्योम __iomem *)vaddr);
	वापस csize;
पूर्ण

/**
 * copy_oldmem_page - copy one page of memory
 * @pfn: page frame number to be copied
 * @buf: target memory address क्रम the copy; this can be in kernel address
 *	space or user address space (see @userbuf)
 * @csize: number of bytes to copy
 * @offset: offset in bytes पूर्णांकo the page (based on pfn) to begin the copy
 * @userbuf: अगर set, @buf is in user address space, use copy_to_user(),
 *	otherwise @buf is in kernel address space, use स_नकल().
 *
 * Copy a page from the old kernel's memory. For this page, there is no pte
 * mapped in the current kernel. We stitch up a pte, similar to kmap_atomic.
 */
sमाप_प्रकार copy_oldmem_page(अचिन्हित दीर्घ pfn, अक्षर *buf, माप_प्रकार csize,
			 अचिन्हित दीर्घ offset, पूर्णांक userbuf)
अणु
	वापस __copy_oldmem_page(pfn, buf, csize, offset, userbuf, false);
पूर्ण

/**
 * copy_oldmem_page_encrypted - same as copy_oldmem_page() above but ioremap the
 * memory with the encryption mask set to accommodate kdump on SME-enabled
 * machines.
 */
sमाप_प्रकार copy_oldmem_page_encrypted(अचिन्हित दीर्घ pfn, अक्षर *buf, माप_प्रकार csize,
				   अचिन्हित दीर्घ offset, पूर्णांक userbuf)
अणु
	वापस __copy_oldmem_page(pfn, buf, csize, offset, userbuf, true);
पूर्ण

sमाप_प्रकार elfcorehdr_पढ़ो(अक्षर *buf, माप_प्रकार count, u64 *ppos)
अणु
	वापस पढ़ो_from_oldmem(buf, count, ppos, 0, sev_active());
पूर्ण
