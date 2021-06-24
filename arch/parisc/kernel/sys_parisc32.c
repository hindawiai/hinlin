<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * sys_parisc32.c: Conversion between 32bit and 64bit native syscalls.
 *
 * Copyright (C) 2000-2001 Hewlett Packard Company
 * Copyright (C) 2000 John Marvin
 * Copyright (C) 2001 Matthew Wilcox
 * Copyright (C) 2014 Helge Deller <deller@gmx.de>
 *
 * These routines मुख्यtain argument size conversion between 32bit and 64bit
 * environment. Based heavily on sys_ia32.c and sys_sparc32.c.
 */

#समावेश <linux/compat.h>
#समावेश <linux/kernel.h>
#समावेश <linux/syscalls.h>


यंत्रlinkage दीर्घ sys32_unimplemented(पूर्णांक r26, पूर्णांक r25, पूर्णांक r24, पूर्णांक r23,
	पूर्णांक r22, पूर्णांक r21, पूर्णांक r20)
अणु
    prपूर्णांकk(KERN_ERR "%s(%d): Unimplemented 32 on 64 syscall #%d!\n", 
    	current->comm, current->pid, r20);
    वापस -ENOSYS;
पूर्ण

यंत्रlinkage दीर्घ sys32_fanotअगरy_mark(compat_पूर्णांक_t fanotअगरy_fd, compat_uपूर्णांक_t flags,
	compat_uपूर्णांक_t mask0, compat_uपूर्णांक_t mask1, compat_पूर्णांक_t dfd,
	स्थिर अक्षर  __user * pathname)
अणु
	वापस sys_fanotअगरy_mark(fanotअगरy_fd, flags,
			((__u64)mask1 << 32) | mask0,
			 dfd, pathname);
पूर्ण
