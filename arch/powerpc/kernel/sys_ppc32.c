<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * sys_ppc32.c: Conversion between 32bit and 64bit native syscalls.
 *
 * Copyright (C) 2001 IBM
 * Copyright (C) 1997,1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 * Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)
 *
 * These routines मुख्यtain argument size conversion between 32bit and 64bit
 * environment.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/fs.h> 
#समावेश <linux/mm.h> 
#समावेश <linux/file.h> 
#समावेश <linux/संकेत.स>
#समावेश <linux/resource.h>
#समावेश <linux/बार.h>
#समावेश <linux/smp.h>
#समावेश <linux/sem.h>
#समावेश <linux/msg.h>
#समावेश <linux/shm.h>
#समावेश <linux/poll.h>
#समावेश <linux/personality.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/mman.h>
#समावेश <linux/in.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/unistd.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/security.h>
#समावेश <linux/compat.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/elf.h>
#समावेश <linux/ipc.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/types.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/ppc-pci.h>
#समावेश <यंत्र/syscalls.h>
#समावेश <यंत्र/चयन_to.h>

अचिन्हित दीर्घ compat_sys_mmap2(अचिन्हित दीर्घ addr, माप_प्रकार len,
			  अचिन्हित दीर्घ prot, अचिन्हित दीर्घ flags,
			  अचिन्हित दीर्घ fd, अचिन्हित दीर्घ pgoff)
अणु
	/* This should reमुख्य 12 even अगर PAGE_SIZE changes */
	वापस sys_mmap(addr, len, prot, flags, fd, pgoff << 12);
पूर्ण

/* 
 * दीर्घ दीर्घ munging:
 * The 32 bit ABI passes दीर्घ दीर्घs in an odd even रेजिस्टर pair.
 * High and low parts are swapped depending on endian mode,
 * so define a macro (similar to mips linux32) to handle that.
 */
#अगर_घोषित __LITTLE_ENDIAN__
#घोषणा merge_64(low, high) ((u64)high << 32) | low
#अन्यथा
#घोषणा merge_64(high, low) ((u64)high << 32) | low
#पूर्ण_अगर

compat_sमाप_प्रकार compat_sys_pपढ़ो64(अचिन्हित पूर्णांक fd, अक्षर __user *ubuf, compat_माप_प्रकार count,
			     u32 reg6, u32 pos1, u32 pos2)
अणु
	वापस ksys_pपढ़ो64(fd, ubuf, count, merge_64(pos1, pos2));
पूर्ण

compat_sमाप_प्रकार compat_sys_pग_लिखो64(अचिन्हित पूर्णांक fd, स्थिर अक्षर __user *ubuf, compat_माप_प्रकार count,
			      u32 reg6, u32 pos1, u32 pos2)
अणु
	वापस ksys_pग_लिखो64(fd, ubuf, count, merge_64(pos1, pos2));
पूर्ण

compat_sमाप_प्रकार compat_sys_पढ़ोahead(पूर्णांक fd, u32 r4, u32 offset1, u32 offset2, u32 count)
अणु
	वापस ksys_पढ़ोahead(fd, merge_64(offset1, offset2), count);
पूर्ण

यंत्रlinkage पूर्णांक compat_sys_truncate64(स्थिर अक्षर __user * path, u32 reg4,
				अचिन्हित दीर्घ len1, अचिन्हित दीर्घ len2)
अणु
	वापस ksys_truncate(path, merge_64(len1, len2));
पूर्ण

यंत्रlinkage दीर्घ compat_sys_fallocate(पूर्णांक fd, पूर्णांक mode, u32 offset1, u32 offset2,
				     u32 len1, u32 len2)
अणु
	वापस ksys_fallocate(fd, mode, ((loff_t)offset1 << 32) | offset2,
			     merge_64(len1, len2));
पूर्ण

यंत्रlinkage पूर्णांक compat_sys_ftruncate64(अचिन्हित पूर्णांक fd, u32 reg4, अचिन्हित दीर्घ len1,
				 अचिन्हित दीर्घ len2)
अणु
	वापस ksys_ftruncate(fd, merge_64(len1, len2));
पूर्ण

दीर्घ ppc32_fadvise64(पूर्णांक fd, u32 unused, u32 offset1, u32 offset2,
		     माप_प्रकार len, पूर्णांक advice)
अणु
	वापस ksys_fadvise64_64(fd, merge_64(offset1, offset2), len,
				 advice);
पूर्ण

यंत्रlinkage दीर्घ compat_sys_sync_file_range2(पूर्णांक fd, अचिन्हित पूर्णांक flags,
				   अचिन्हित offset1, अचिन्हित offset2,
				   अचिन्हित nbytes1, अचिन्हित nbytes2)
अणु
	loff_t offset = merge_64(offset1, offset2);
	loff_t nbytes = merge_64(nbytes1, nbytes2);

	वापस ksys_sync_file_range(fd, offset, nbytes, flags);
पूर्ण
