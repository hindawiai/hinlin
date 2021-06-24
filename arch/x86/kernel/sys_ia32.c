<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * sys_ia32.c: Conversion between 32bit and 64bit native syscalls. Based on
 *             sys_sparc32
 *
 * Copyright (C) 2000		VA Linux Co
 * Copyright (C) 2000		Don Dugger <n0ano@valinux.com>
 * Copyright (C) 1999		Arun Sharma <arun.sharma@पूर्णांकel.com>
 * Copyright (C) 1997,1998	Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 * Copyright (C) 1997		David S. Miller (davem@caip.rutgers.edu)
 * Copyright (C) 2000		Hewlett-Packard Co.
 * Copyright (C) 2000		David Mosberger-Tang <davidm@hpl.hp.com>
 * Copyright (C) 2000,2001,2002	Andi Kleen, SuSE Lअसल (x86-64 port)
 *
 * These routines मुख्यtain argument size conversion between 32bit and 64bit
 * environment. In 2.5 most of this should be moved to a generic directory.
 *
 * This file assumes that there is a hole at the end of user address space.
 *
 * Some of the functions are LE specअगरic currently. These are
 * hopefully all marked.  This should be fixed.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/syscalls.h>
#समावेश <linux/बार.h>
#समावेश <linux/utsname.h>
#समावेश <linux/mm.h>
#समावेश <linux/uपन.स>
#समावेश <linux/poll.h>
#समावेश <linux/personality.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/rwsem.h>
#समावेश <linux/compat.h>
#समावेश <linux/vfs.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/highuid.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/task.h>
#समावेश <यंत्र/mman.h>
#समावेश <यंत्र/types.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/vgtod.h>
#समावेश <यंत्र/ia32.h>

#घोषणा AA(__x)		((अचिन्हित दीर्घ)(__x))

SYSCALL_DEFINE3(ia32_truncate64, स्थिर अक्षर __user *, filename,
		अचिन्हित दीर्घ, offset_low, अचिन्हित दीर्घ, offset_high)
अणु
	वापस ksys_truncate(filename,
			    ((loff_t) offset_high << 32) | offset_low);
पूर्ण

SYSCALL_DEFINE3(ia32_ftruncate64, अचिन्हित पूर्णांक, fd,
		अचिन्हित दीर्घ, offset_low, अचिन्हित दीर्घ, offset_high)
अणु
	वापस ksys_ftruncate(fd, ((loff_t) offset_high << 32) | offset_low);
पूर्ण

/* warning: next two assume little endian */
SYSCALL_DEFINE5(ia32_pपढ़ो64, अचिन्हित पूर्णांक, fd, अक्षर __user *, ubuf,
		u32, count, u32, poslo, u32, poshi)
अणु
	वापस ksys_pपढ़ो64(fd, ubuf, count,
			    ((loff_t)AA(poshi) << 32) | AA(poslo));
पूर्ण

SYSCALL_DEFINE5(ia32_pग_लिखो64, अचिन्हित पूर्णांक, fd, स्थिर अक्षर __user *, ubuf,
		u32, count, u32, poslo, u32, poshi)
अणु
	वापस ksys_pग_लिखो64(fd, ubuf, count,
			     ((loff_t)AA(poshi) << 32) | AA(poslo));
पूर्ण


/*
 * Some प्रणाली calls that need sign extended arguments. This could be
 * करोne by a generic wrapper.
 */
SYSCALL_DEFINE6(ia32_fadvise64_64, पूर्णांक, fd, __u32, offset_low,
		__u32, offset_high, __u32, len_low, __u32, len_high,
		पूर्णांक, advice)
अणु
	वापस ksys_fadvise64_64(fd,
				 (((u64)offset_high)<<32) | offset_low,
				 (((u64)len_high)<<32) | len_low,
				 advice);
पूर्ण

SYSCALL_DEFINE4(ia32_पढ़ोahead, पूर्णांक, fd, अचिन्हित पूर्णांक, off_lo,
		अचिन्हित पूर्णांक, off_hi, माप_प्रकार, count)
अणु
	वापस ksys_पढ़ोahead(fd, ((u64)off_hi << 32) | off_lo, count);
पूर्ण

SYSCALL_DEFINE6(ia32_sync_file_range, पूर्णांक, fd, अचिन्हित पूर्णांक, off_low,
		अचिन्हित पूर्णांक, off_hi, अचिन्हित पूर्णांक, n_low,
		अचिन्हित पूर्णांक, n_hi, पूर्णांक, flags)
अणु
	वापस ksys_sync_file_range(fd,
				    ((u64)off_hi << 32) | off_low,
				    ((u64)n_hi << 32) | n_low, flags);
पूर्ण

SYSCALL_DEFINE5(ia32_fadvise64, पूर्णांक, fd, अचिन्हित पूर्णांक, offset_lo,
		अचिन्हित पूर्णांक, offset_hi, माप_प्रकार, len, पूर्णांक, advice)
अणु
	वापस ksys_fadvise64_64(fd, ((u64)offset_hi << 32) | offset_lo,
				 len, advice);
पूर्ण

SYSCALL_DEFINE6(ia32_fallocate, पूर्णांक, fd, पूर्णांक, mode,
		अचिन्हित पूर्णांक, offset_lo, अचिन्हित पूर्णांक, offset_hi,
		अचिन्हित पूर्णांक, len_lo, अचिन्हित पूर्णांक, len_hi)
अणु
	वापस ksys_fallocate(fd, mode, ((u64)offset_hi << 32) | offset_lo,
			      ((u64)len_hi << 32) | len_lo);
पूर्ण

#अगर_घोषित CONFIG_IA32_EMULATION
/*
 * Another set क्रम IA32/LFS -- x86_64 काष्ठा stat is dअगरferent due to
 * support क्रम 64bit inode numbers.
 */
अटल पूर्णांक cp_stat64(काष्ठा stat64 __user *ubuf, काष्ठा kstat *stat)
अणु
	typeof(ubuf->st_uid) uid = 0;
	typeof(ubuf->st_gid) gid = 0;
	SET_UID(uid, from_kuid_munged(current_user_ns(), stat->uid));
	SET_GID(gid, from_kgid_munged(current_user_ns(), stat->gid));
	अगर (!user_ग_लिखो_access_begin(ubuf, माप(काष्ठा stat64)))
		वापस -EFAULT;
	unsafe_put_user(huge_encode_dev(stat->dev), &ubuf->st_dev, Efault);
	unsafe_put_user(stat->ino, &ubuf->__st_ino, Efault);
	unsafe_put_user(stat->ino, &ubuf->st_ino, Efault);
	unsafe_put_user(stat->mode, &ubuf->st_mode, Efault);
	unsafe_put_user(stat->nlink, &ubuf->st_nlink, Efault);
	unsafe_put_user(uid, &ubuf->st_uid, Efault);
	unsafe_put_user(gid, &ubuf->st_gid, Efault);
	unsafe_put_user(huge_encode_dev(stat->rdev), &ubuf->st_rdev, Efault);
	unsafe_put_user(stat->size, &ubuf->st_size, Efault);
	unsafe_put_user(stat->aसमय.tv_sec, &ubuf->st_aसमय, Efault);
	unsafe_put_user(stat->aसमय.tv_nsec, &ubuf->st_aसमय_nsec, Efault);
	unsafe_put_user(stat->mसमय.tv_sec, &ubuf->st_mसमय, Efault);
	unsafe_put_user(stat->mसमय.tv_nsec, &ubuf->st_mसमय_nsec, Efault);
	unsafe_put_user(stat->स_समय.tv_sec, &ubuf->st_स_समय, Efault);
	unsafe_put_user(stat->स_समय.tv_nsec, &ubuf->st_स_समय_nsec, Efault);
	unsafe_put_user(stat->blksize, &ubuf->st_blksize, Efault);
	unsafe_put_user(stat->blocks, &ubuf->st_blocks, Efault);
	user_access_end();
	वापस 0;
Efault:
	user_ग_लिखो_access_end();
	वापस -EFAULT;
पूर्ण

COMPAT_SYSCALL_DEFINE2(ia32_stat64, स्थिर अक्षर __user *, filename,
		       काष्ठा stat64 __user *, statbuf)
अणु
	काष्ठा kstat stat;
	पूर्णांक ret = vfs_stat(filename, &stat);

	अगर (!ret)
		ret = cp_stat64(statbuf, &stat);
	वापस ret;
पूर्ण

COMPAT_SYSCALL_DEFINE2(ia32_lstat64, स्थिर अक्षर __user *, filename,
		       काष्ठा stat64 __user *, statbuf)
अणु
	काष्ठा kstat stat;
	पूर्णांक ret = vfs_lstat(filename, &stat);
	अगर (!ret)
		ret = cp_stat64(statbuf, &stat);
	वापस ret;
पूर्ण

COMPAT_SYSCALL_DEFINE2(ia32_ख_स्थिति64, अचिन्हित पूर्णांक, fd,
		       काष्ठा stat64 __user *, statbuf)
अणु
	काष्ठा kstat stat;
	पूर्णांक ret = vfs_ख_स्थिति(fd, &stat);
	अगर (!ret)
		ret = cp_stat64(statbuf, &stat);
	वापस ret;
पूर्ण

COMPAT_SYSCALL_DEFINE4(ia32_ख_स्थितिat64, अचिन्हित पूर्णांक, dfd,
		       स्थिर अक्षर __user *, filename,
		       काष्ठा stat64 __user *, statbuf, पूर्णांक, flag)
अणु
	काष्ठा kstat stat;
	पूर्णांक error;

	error = vfs_ख_स्थितिat(dfd, filename, &stat, flag);
	अगर (error)
		वापस error;
	वापस cp_stat64(statbuf, &stat);
पूर्ण

/*
 * Linux/i386 didn't use to be able to handle more than
 * 4 प्रणाली call parameters, so these प्रणाली calls used a memory
 * block क्रम parameter passing..
 */

काष्ठा mmap_arg_काष्ठा32 अणु
	अचिन्हित पूर्णांक addr;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक prot;
	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक fd;
	अचिन्हित पूर्णांक offset;
पूर्ण;

COMPAT_SYSCALL_DEFINE1(ia32_mmap, काष्ठा mmap_arg_काष्ठा32 __user *, arg)
अणु
	काष्ठा mmap_arg_काष्ठा32 a;

	अगर (copy_from_user(&a, arg, माप(a)))
		वापस -EFAULT;

	अगर (a.offset & ~PAGE_MASK)
		वापस -EINVAL;

	वापस ksys_mmap_pgoff(a.addr, a.len, a.prot, a.flags, a.fd,
			       a.offset>>PAGE_SHIFT);
पूर्ण

/*
 * The 32-bit clone ABI is CONFIG_CLONE_BACKWARDS
 */
COMPAT_SYSCALL_DEFINE5(ia32_clone, अचिन्हित दीर्घ, clone_flags,
		       अचिन्हित दीर्घ, newsp, पूर्णांक __user *, parent_tidptr,
		       अचिन्हित दीर्घ, tls_val, पूर्णांक __user *, child_tidptr)
अणु
	काष्ठा kernel_clone_args args = अणु
		.flags		= (clone_flags & ~CSIGNAL),
		.pidfd		= parent_tidptr,
		.child_tid	= child_tidptr,
		.parent_tid	= parent_tidptr,
		.निकास_संकेत	= (clone_flags & CSIGNAL),
		.stack		= newsp,
		.tls		= tls_val,
	पूर्ण;

	वापस kernel_clone(&args);
पूर्ण
#पूर्ण_अगर /* CONFIG_IA32_EMULATION */
