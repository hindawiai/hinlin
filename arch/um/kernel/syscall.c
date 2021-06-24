<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/utsname.h>
#समावेश <linux/syscalls.h>
#समावेश <यंत्र/current.h>
#समावेश <यंत्र/mman.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/unistd.h>

दीर्घ old_mmap(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
	      अचिन्हित दीर्घ prot, अचिन्हित दीर्घ flags,
	      अचिन्हित दीर्घ fd, अचिन्हित दीर्घ offset)
अणु
	दीर्घ err = -EINVAL;
	अगर (offset & ~PAGE_MASK)
		जाओ out;

	err = ksys_mmap_pgoff(addr, len, prot, flags, fd, offset >> PAGE_SHIFT);
 out:
	वापस err;
पूर्ण
