<शैली गुरु>
/*
 * Copyright (C) 2007-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2007-2009 PetaLogix
 * Copyright (C) 2007 John Williams <john.williams@petalogix.com>
 *
 * Copyright (C) 2006 Aपंचांगark Techno, Inc.
 *	Yasushi SHOJI <yashi@aपंचांगark-techno.com>
 *	Tetsuya OHKAWA <tetsuya@aपंचांगark-techno.com>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/sem.h>
#समावेश <linux/msg.h>
#समावेश <linux/shm.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/mman.h>
#समावेश <linux/sys.h>
#समावेश <linux/ipc.h>
#समावेश <linux/file.h>
#समावेश <linux/err.h>
#समावेश <linux/fs.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/unistd.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/syscalls.h>

SYSCALL_DEFINE6(mmap, अचिन्हित दीर्घ, addr, अचिन्हित दीर्घ, len,
		अचिन्हित दीर्घ, prot, अचिन्हित दीर्घ, flags, अचिन्हित दीर्घ, fd,
		off_t, pgoff)
अणु
	अगर (pgoff & ~PAGE_MASK)
		वापस -EINVAL;

	वापस ksys_mmap_pgoff(addr, len, prot, flags, fd, pgoff >> PAGE_SHIFT);
पूर्ण

SYSCALL_DEFINE6(mmap2, अचिन्हित दीर्घ, addr, अचिन्हित दीर्घ, len,
		अचिन्हित दीर्घ, prot, अचिन्हित दीर्घ, flags, अचिन्हित दीर्घ, fd,
		अचिन्हित दीर्घ, pgoff)
अणु
	अगर (pgoff & (~PAGE_MASK >> 12))
		वापस -EINVAL;

	वापस ksys_mmap_pgoff(addr, len, prot, flags, fd,
			       pgoff >> (PAGE_SHIFT - 12));
पूर्ण
