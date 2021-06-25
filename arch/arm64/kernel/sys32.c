<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm64/kernel/sys32.c
 *
 * Copyright (C) 2015 ARM Ltd.
 */

/*
 * Needed to aव्योम conflicting __NR_* macros between uapi/यंत्र/unistd.h and
 * यंत्र/unistd32.h.
 */
#घोषणा __COMPAT_SYSCALL_NR

#समावेश <linux/compat.h>
#समावेश <linux/compiler.h>
#समावेश <linux/syscalls.h>

#समावेश <यंत्र/syscall.h>

यंत्रlinkage दीर्घ compat_sys_sigवापस(व्योम);
यंत्रlinkage दीर्घ compat_sys_rt_sigवापस(व्योम);

COMPAT_SYSCALL_DEFINE3(aarch32_statfs64, स्थिर अक्षर __user *, pathname,
		       compat_माप_प्रकार, sz, काष्ठा compat_statfs64 __user *, buf)
अणु
	/*
	 * 32-bit ARM applies an OABI compatibility fixup to statfs64 and
	 * ख_स्थितिfs64 regardless of whether OABI is in use, and thereक्रमe
	 * arbitrary binaries may rely upon it, so we must करो the same.
	 * For more details, see commit:
	 *
	 * 713c481519f19df9 ("[ARM] 3108/2: old ABI compat: statfs64 and
	 * ख_स्थितिfs64")
	 */
	अगर (sz == 88)
		sz = 84;

	वापस kcompat_sys_statfs64(pathname, sz, buf);
पूर्ण

COMPAT_SYSCALL_DEFINE3(aarch32_ख_स्थितिfs64, अचिन्हित पूर्णांक, fd, compat_माप_प्रकार, sz,
		       काष्ठा compat_statfs64 __user *, buf)
अणु
	/* see aarch32_statfs64 */
	अगर (sz == 88)
		sz = 84;

	वापस kcompat_sys_ख_स्थितिfs64(fd, sz, buf);
पूर्ण

/*
 * Note: off_4k is always in units of 4K. If we can't करो the
 * requested offset because it is not page-aligned, we वापस -EINVAL.
 */
COMPAT_SYSCALL_DEFINE6(aarch32_mmap2, अचिन्हित दीर्घ, addr, अचिन्हित दीर्घ, len,
		       अचिन्हित दीर्घ, prot, अचिन्हित दीर्घ, flags,
		       अचिन्हित दीर्घ, fd, अचिन्हित दीर्घ, off_4k)
अणु
	अगर (off_4k & (~PAGE_MASK >> 12))
		वापस -EINVAL;

	off_4k >>= (PAGE_SHIFT - 12);

	वापस ksys_mmap_pgoff(addr, len, prot, flags, fd, off_4k);
पूर्ण

#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
#घोषणा arg_u32p(name)	u32, name##_hi, u32, name##_lo
#अन्यथा
#घोषणा arg_u32p(name)	u32, name##_lo, u32, name##_hi
#पूर्ण_अगर

#घोषणा arg_u64(name)	(((u64)name##_hi << 32) | name##_lo)

COMPAT_SYSCALL_DEFINE6(aarch32_pपढ़ो64, अचिन्हित पूर्णांक, fd, अक्षर __user *, buf,
		       माप_प्रकार, count, u32, __pad, arg_u32p(pos))
अणु
	वापस ksys_pपढ़ो64(fd, buf, count, arg_u64(pos));
पूर्ण

COMPAT_SYSCALL_DEFINE6(aarch32_pग_लिखो64, अचिन्हित पूर्णांक, fd,
		       स्थिर अक्षर __user *, buf, माप_प्रकार, count, u32, __pad,
		       arg_u32p(pos))
अणु
	वापस ksys_pग_लिखो64(fd, buf, count, arg_u64(pos));
पूर्ण

COMPAT_SYSCALL_DEFINE4(aarch32_truncate64, स्थिर अक्षर __user *, pathname,
		       u32, __pad, arg_u32p(length))
अणु
	वापस ksys_truncate(pathname, arg_u64(length));
पूर्ण

COMPAT_SYSCALL_DEFINE4(aarch32_ftruncate64, अचिन्हित पूर्णांक, fd, u32, __pad,
		       arg_u32p(length))
अणु
	वापस ksys_ftruncate(fd, arg_u64(length));
पूर्ण

COMPAT_SYSCALL_DEFINE5(aarch32_पढ़ोahead, पूर्णांक, fd, u32, __pad,
		       arg_u32p(offset), माप_प्रकार, count)
अणु
	वापस ksys_पढ़ोahead(fd, arg_u64(offset), count);
पूर्ण

COMPAT_SYSCALL_DEFINE6(aarch32_fadvise64_64, पूर्णांक, fd, पूर्णांक, advice,
		       arg_u32p(offset), arg_u32p(len))
अणु
	वापस ksys_fadvise64_64(fd, arg_u64(offset), arg_u64(len), advice);
पूर्ण

COMPAT_SYSCALL_DEFINE6(aarch32_sync_file_range2, पूर्णांक, fd, अचिन्हित पूर्णांक, flags,
		       arg_u32p(offset), arg_u32p(nbytes))
अणु
	वापस ksys_sync_file_range(fd, arg_u64(offset), arg_u64(nbytes),
				    flags);
पूर्ण

COMPAT_SYSCALL_DEFINE6(aarch32_fallocate, पूर्णांक, fd, पूर्णांक, mode,
		       arg_u32p(offset), arg_u32p(len))
अणु
	वापस ksys_fallocate(fd, mode, arg_u64(offset), arg_u64(len));
पूर्ण

#अघोषित __SYSCALL
#घोषणा __SYSCALL(nr, sym)	यंत्रlinkage दीर्घ __arm64_##sym(स्थिर काष्ठा pt_regs *);
#समावेश <यंत्र/unistd32.h>

#अघोषित __SYSCALL
#घोषणा __SYSCALL(nr, sym)	[nr] = __arm64_##sym,

स्थिर syscall_fn_t compat_sys_call_table[__NR_compat_syscalls] = अणु
	[0 ... __NR_compat_syscalls - 1] = __arm64_sys_ni_syscall,
#समावेश <यंत्र/unistd32.h>
पूर्ण;
