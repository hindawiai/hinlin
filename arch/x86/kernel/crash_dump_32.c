<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	Memory preserving reboot related code.
 *
 *	Created by: Hariprasad Nellitheertha (hari@in.ibm.com)
 *	Copyright (C) IBM Corporation, 2004. All rights reserved
 */

#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/crash_dump.h>

#समावेश <linux/uaccess.h>

अटल अंतरभूत bool is_crashed_pfn_valid(अचिन्हित दीर्घ pfn)
अणु
#अगर_अघोषित CONFIG_X86_PAE
	/*
	 * non-PAE kdump kernel executed from a PAE one will crop high pte
	 * bits and poke unwanted space counting again from address 0, we
	 * करोn't want that. pte must fit पूर्णांकo अचिन्हित दीर्घ. In fact the
	 * test checks high 12 bits क्रम being zero (pfn will be shअगरted left
	 * by PAGE_SHIFT).
	 */
	वापस pte_pfn(pfn_pte(pfn, __pgprot(0))) == pfn;
#अन्यथा
	वापस true;
#पूर्ण_अगर
पूर्ण

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
 * Copy a page from "oldmem". For this page, there might be no pte mapped
 * in the current kernel.
 */
sमाप_प्रकार copy_oldmem_page(अचिन्हित दीर्घ pfn, अक्षर *buf, माप_प्रकार csize,
			 अचिन्हित दीर्घ offset, पूर्णांक userbuf)
अणु
	व्योम  *vaddr;

	अगर (!csize)
		वापस 0;

	अगर (!is_crashed_pfn_valid(pfn))
		वापस -EFAULT;

	vaddr = kmap_local_pfn(pfn);

	अगर (!userbuf) अणु
		स_नकल(buf, vaddr + offset, csize);
	पूर्ण अन्यथा अणु
		अगर (copy_to_user(buf, vaddr + offset, csize))
			csize = -EFAULT;
	पूर्ण

	kunmap_local(vaddr);

	वापस csize;
पूर्ण
