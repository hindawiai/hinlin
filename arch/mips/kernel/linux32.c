<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Conversion between 32-bit and 64-bit native प्रणाली calls.
 *
 * Copyright (C) 2000 Silicon Graphics, Inc.
 * Written by Ulf Carlsson (ulfc@engr.sgi.com)
 */
#समावेश <linux/compiler.h>
#समावेश <linux/mm.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/file.h>
#समावेश <linux/highuid.h>
#समावेश <linux/resource.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/समय.स>
#समावेश <linux/बार.h>
#समावेश <linux/poll.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/filter.h>
#समावेश <linux/shm.h>
#समावेश <linux/sem.h>
#समावेश <linux/msg.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/uसमय.स>
#समावेश <linux/utsname.h>
#समावेश <linux/personality.h>
#समावेश <linux/dnotअगरy.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/security.h>
#समावेश <linux/compat.h>
#समावेश <linux/vfs.h>
#समावेश <linux/ipc.h>
#समावेश <linux/slab.h>

#समावेश <net/sock.h>
#समावेश <net/scm.h>

#समावेश <यंत्र/compat-संकेत.स>
#समावेश <यंत्र/sim.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/mman.h>

#अगर_घोषित __MIPSEB__
#घोषणा merge_64(r1, r2) ((((r1) & 0xffffffffUL) << 32) + ((r2) & 0xffffffffUL))
#पूर्ण_अगर
#अगर_घोषित __MIPSEL__
#घोषणा merge_64(r1, r2) ((((r2) & 0xffffffffUL) << 32) + ((r1) & 0xffffffffUL))
#पूर्ण_अगर

SYSCALL_DEFINE4(32_truncate64, स्थिर अक्षर __user *, path,
	अचिन्हित दीर्घ, __dummy, अचिन्हित दीर्घ, a2, अचिन्हित दीर्घ, a3)
अणु
	वापस ksys_truncate(path, merge_64(a2, a3));
पूर्ण

SYSCALL_DEFINE4(32_ftruncate64, अचिन्हित दीर्घ, fd, अचिन्हित दीर्घ, __dummy,
	अचिन्हित दीर्घ, a2, अचिन्हित दीर्घ, a3)
अणु
	वापस ksys_ftruncate(fd, merge_64(a2, a3));
पूर्ण

SYSCALL_DEFINE5(32_llseek, अचिन्हित पूर्णांक, fd, अचिन्हित पूर्णांक, offset_high,
		अचिन्हित पूर्णांक, offset_low, loff_t __user *, result,
		अचिन्हित पूर्णांक, origin)
अणु
	वापस sys_llseek(fd, offset_high, offset_low, result, origin);
पूर्ण

/* From the Single Unix Spec: pपढ़ो & pग_लिखो act like lseek to pos + op +
   lseek back to original location.  They fail just like lseek करोes on
   non-seekable files.	*/

SYSCALL_DEFINE6(32_pपढ़ो, अचिन्हित दीर्घ, fd, अक्षर __user *, buf, माप_प्रकार, count,
	अचिन्हित दीर्घ, unused, अचिन्हित दीर्घ, a4, अचिन्हित दीर्घ, a5)
अणु
	वापस ksys_pपढ़ो64(fd, buf, count, merge_64(a4, a5));
पूर्ण

SYSCALL_DEFINE6(32_pग_लिखो, अचिन्हित पूर्णांक, fd, स्थिर अक्षर __user *, buf,
	माप_प्रकार, count, u32, unused, u64, a4, u64, a5)
अणु
	वापस ksys_pग_लिखो64(fd, buf, count, merge_64(a4, a5));
पूर्ण

SYSCALL_DEFINE1(32_personality, अचिन्हित दीर्घ, personality)
अणु
	अचिन्हित पूर्णांक p = personality & 0xffffffff;
	पूर्णांक ret;

	अगर (personality(current->personality) == PER_LINUX32 &&
	    personality(p) == PER_LINUX)
		p = (p & ~PER_MASK) | PER_LINUX32;
	ret = sys_personality(p);
	अगर (ret != -1 && personality(ret) == PER_LINUX32)
		ret = (ret & ~PER_MASK) | PER_LINUX;
	वापस ret;
पूर्ण

यंत्रlinkage sमाप_प्रकार sys32_पढ़ोahead(पूर्णांक fd, u32 pad0, u64 a2, u64 a3,
				   माप_प्रकार count)
अणु
	वापस ksys_पढ़ोahead(fd, merge_64(a2, a3), count);
पूर्ण

यंत्रlinkage दीर्घ sys32_sync_file_range(पूर्णांक fd, पूर्णांक __pad,
	अचिन्हित दीर्घ a2, अचिन्हित दीर्घ a3,
	अचिन्हित दीर्घ a4, अचिन्हित दीर्घ a5,
	पूर्णांक flags)
अणु
	वापस ksys_sync_file_range(fd,
			merge_64(a2, a3), merge_64(a4, a5),
			flags);
पूर्ण

यंत्रlinkage दीर्घ sys32_fadvise64_64(पूर्णांक fd, पूर्णांक __pad,
	अचिन्हित दीर्घ a2, अचिन्हित दीर्घ a3,
	अचिन्हित दीर्घ a4, अचिन्हित दीर्घ a5,
	पूर्णांक flags)
अणु
	वापस ksys_fadvise64_64(fd,
			merge_64(a2, a3), merge_64(a4, a5),
			flags);
पूर्ण

यंत्रlinkage दीर्घ sys32_fallocate(पूर्णांक fd, पूर्णांक mode, अचिन्हित offset_a2,
	अचिन्हित offset_a3, अचिन्हित len_a4, अचिन्हित len_a5)
अणु
	वापस ksys_fallocate(fd, mode, merge_64(offset_a2, offset_a3),
			      merge_64(len_a4, len_a5));
पूर्ण
