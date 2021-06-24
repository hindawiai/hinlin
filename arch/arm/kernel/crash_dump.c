<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/kernel/crash_dump.c
 *
 * Copyright (C) 2010 Nokia Corporation.
 * Author: Mika Westerberg
 *
 * This code is taken from arch/x86/kernel/crash_dump_64.c
 *   Created by: Hariprasad Nellitheertha (hari@in.ibm.com)
 *   Copyright (C) IBM Corporation, 2004. All rights reserved
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/crash_dump.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>

/**
 * copy_oldmem_page() - copy one page from old kernel memory
 * @pfn: page frame number to be copied
 * @buf: buffer where the copied page is placed
 * @csize: number of bytes to copy
 * @offset: offset in bytes पूर्णांकo the page
 * @userbuf: अगर set, @buf is पूर्णांक he user address space
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

	vaddr = ioremap(__pfn_to_phys(pfn), PAGE_SIZE);
	अगर (!vaddr)
		वापस -ENOMEM;

	अगर (userbuf) अणु
		अगर (copy_to_user(buf, vaddr + offset, csize)) अणु
			iounmap(vaddr);
			वापस -EFAULT;
		पूर्ण
	पूर्ण अन्यथा अणु
		स_नकल(buf, vaddr + offset, csize);
	पूर्ण

	iounmap(vaddr);
	वापस csize;
पूर्ण
