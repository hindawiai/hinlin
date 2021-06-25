<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  S390 version
 *    Copyright IBM Corp. 2000
 *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com),
 *               Gerhard Tonn (ton@de.ibm.com)   
 *               Thomas Spatzier (tspat@de.ibm.com)
 *
 *  Conversion between 31bit and 64bit native syscalls.
 *
 * Heavily inspired by the 32-bit Sparc compat code which is 
 * Copyright (C) 1997,1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 * Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)
 *
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
#समावेश <linux/uपन.स>
#समावेश <linux/quota.h>
#समावेश <linux/poll.h>
#समावेश <linux/personality.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/filter.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/mman.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/in.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/capability.h>
#समावेश <linux/compat.h>
#समावेश <linux/vfs.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/fadvise.h>
#समावेश <linux/ipc.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/types.h>
#समावेश <linux/uaccess.h>

#समावेश <net/scm.h>
#समावेश <net/sock.h>

#समावेश "compat_linux.h"

#अगर_घोषित CONFIG_SYSVIPC
COMPAT_SYSCALL_DEFINE5(s390_ipc, uपूर्णांक, call, पूर्णांक, first, compat_uदीर्घ_t, second,
		compat_uदीर्घ_t, third, compat_uptr_t, ptr)
अणु
	अगर (call >> 16)		/* hack क्रम backward compatibility */
		वापस -EINVAL;
	वापस compat_ksys_ipc(call, first, second, third, ptr, third);
पूर्ण
#पूर्ण_अगर

COMPAT_SYSCALL_DEFINE3(s390_truncate64, स्थिर अक्षर __user *, path, u32, high, u32, low)
अणु
	वापस ksys_truncate(path, (अचिन्हित दीर्घ)high << 32 | low);
पूर्ण

COMPAT_SYSCALL_DEFINE3(s390_ftruncate64, अचिन्हित पूर्णांक, fd, u32, high, u32, low)
अणु
	वापस ksys_ftruncate(fd, (अचिन्हित दीर्घ)high << 32 | low);
पूर्ण

COMPAT_SYSCALL_DEFINE5(s390_pपढ़ो64, अचिन्हित पूर्णांक, fd, अक्षर __user *, ubuf,
		       compat_माप_प्रकार, count, u32, high, u32, low)
अणु
	अगर ((compat_sमाप_प्रकार) count < 0)
		वापस -EINVAL;
	वापस ksys_pपढ़ो64(fd, ubuf, count, (अचिन्हित दीर्घ)high << 32 | low);
पूर्ण

COMPAT_SYSCALL_DEFINE5(s390_pग_लिखो64, अचिन्हित पूर्णांक, fd, स्थिर अक्षर __user *, ubuf,
		       compat_माप_प्रकार, count, u32, high, u32, low)
अणु
	अगर ((compat_sमाप_प्रकार) count < 0)
		वापस -EINVAL;
	वापस ksys_pग_लिखो64(fd, ubuf, count, (अचिन्हित दीर्घ)high << 32 | low);
पूर्ण

COMPAT_SYSCALL_DEFINE4(s390_पढ़ोahead, पूर्णांक, fd, u32, high, u32, low, s32, count)
अणु
	वापस ksys_पढ़ोahead(fd, (अचिन्हित दीर्घ)high << 32 | low, count);
पूर्ण

काष्ठा stat64_emu31 अणु
	अचिन्हित दीर्घ दीर्घ  st_dev;
	अचिन्हित पूर्णांक    __pad1;
#घोषणा STAT64_HAS_BROKEN_ST_INO        1
	u32             __st_ino;
	अचिन्हित पूर्णांक    st_mode;
	अचिन्हित पूर्णांक    st_nlink;
	u32             st_uid;
	u32             st_gid;
	अचिन्हित दीर्घ दीर्घ  st_rdev;
	अचिन्हित पूर्णांक    __pad3;
	दीर्घ            st_size;
	u32             st_blksize;
	अचिन्हित अक्षर   __pad4[4];
	u32             __pad5;     /* future possible st_blocks high bits */
	u32             st_blocks;  /* Number 512-byte blocks allocated. */
	u32             st_aसमय;
	u32             __pad6;
	u32             st_mसमय;
	u32             __pad7;
	u32             st_स_समय;
	u32             __pad8;     /* will be high 32 bits of स_समय someday */
	अचिन्हित दीर्घ   st_ino;
पूर्ण;	

अटल पूर्णांक cp_stat64(काष्ठा stat64_emu31 __user *ubuf, काष्ठा kstat *stat)
अणु
	काष्ठा stat64_emu31 पंचांगp;

	स_रखो(&पंचांगp, 0, माप(पंचांगp));

	पंचांगp.st_dev = huge_encode_dev(stat->dev);
	पंचांगp.st_ino = stat->ino;
	पंचांगp.__st_ino = (u32)stat->ino;
	पंचांगp.st_mode = stat->mode;
	पंचांगp.st_nlink = (अचिन्हित पूर्णांक)stat->nlink;
	पंचांगp.st_uid = from_kuid_munged(current_user_ns(), stat->uid);
	पंचांगp.st_gid = from_kgid_munged(current_user_ns(), stat->gid);
	पंचांगp.st_rdev = huge_encode_dev(stat->rdev);
	पंचांगp.st_size = stat->size;
	पंचांगp.st_blksize = (u32)stat->blksize;
	पंचांगp.st_blocks = (u32)stat->blocks;
	पंचांगp.st_aसमय = (u32)stat->aसमय.tv_sec;
	पंचांगp.st_mसमय = (u32)stat->mसमय.tv_sec;
	पंचांगp.st_स_समय = (u32)stat->स_समय.tv_sec;

	वापस copy_to_user(ubuf,&पंचांगp,माप(पंचांगp)) ? -EFAULT : 0; 
पूर्ण

COMPAT_SYSCALL_DEFINE2(s390_stat64, स्थिर अक्षर __user *, filename, काष्ठा stat64_emu31 __user *, statbuf)
अणु
	काष्ठा kstat stat;
	पूर्णांक ret = vfs_stat(filename, &stat);
	अगर (!ret)
		ret = cp_stat64(statbuf, &stat);
	वापस ret;
पूर्ण

COMPAT_SYSCALL_DEFINE2(s390_lstat64, स्थिर अक्षर __user *, filename, काष्ठा stat64_emu31 __user *, statbuf)
अणु
	काष्ठा kstat stat;
	पूर्णांक ret = vfs_lstat(filename, &stat);
	अगर (!ret)
		ret = cp_stat64(statbuf, &stat);
	वापस ret;
पूर्ण

COMPAT_SYSCALL_DEFINE2(s390_ख_स्थिति64, अचिन्हित पूर्णांक, fd, काष्ठा stat64_emu31 __user *, statbuf)
अणु
	काष्ठा kstat stat;
	पूर्णांक ret = vfs_ख_स्थिति(fd, &stat);
	अगर (!ret)
		ret = cp_stat64(statbuf, &stat);
	वापस ret;
पूर्ण

COMPAT_SYSCALL_DEFINE4(s390_ख_स्थितिat64, अचिन्हित पूर्णांक, dfd, स्थिर अक्षर __user *, filename,
		       काष्ठा stat64_emu31 __user *, statbuf, पूर्णांक, flag)
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

काष्ठा mmap_arg_काष्ठा_emu31 अणु
	compat_uदीर्घ_t addr;
	compat_uदीर्घ_t len;
	compat_uदीर्घ_t prot;
	compat_uदीर्घ_t flags;
	compat_uदीर्घ_t fd;
	compat_uदीर्घ_t offset;
पूर्ण;

COMPAT_SYSCALL_DEFINE1(s390_old_mmap, काष्ठा mmap_arg_काष्ठा_emu31 __user *, arg)
अणु
	काष्ठा mmap_arg_काष्ठा_emu31 a;

	अगर (copy_from_user(&a, arg, माप(a)))
		वापस -EFAULT;
	अगर (a.offset & ~PAGE_MASK)
		वापस -EINVAL;
	वापस ksys_mmap_pgoff(a.addr, a.len, a.prot, a.flags, a.fd,
			       a.offset >> PAGE_SHIFT);
पूर्ण

COMPAT_SYSCALL_DEFINE1(s390_mmap2, काष्ठा mmap_arg_काष्ठा_emu31 __user *, arg)
अणु
	काष्ठा mmap_arg_काष्ठा_emu31 a;

	अगर (copy_from_user(&a, arg, माप(a)))
		वापस -EFAULT;
	वापस ksys_mmap_pgoff(a.addr, a.len, a.prot, a.flags, a.fd, a.offset);
पूर्ण

COMPAT_SYSCALL_DEFINE3(s390_पढ़ो, अचिन्हित पूर्णांक, fd, अक्षर __user *, buf, compat_माप_प्रकार, count)
अणु
	अगर ((compat_sमाप_प्रकार) count < 0)
		वापस -EINVAL; 

	वापस ksys_पढ़ो(fd, buf, count);
पूर्ण

COMPAT_SYSCALL_DEFINE3(s390_ग_लिखो, अचिन्हित पूर्णांक, fd, स्थिर अक्षर __user *, buf, compat_माप_प्रकार, count)
अणु
	अगर ((compat_sमाप_प्रकार) count < 0)
		वापस -EINVAL; 

	वापस ksys_ग_लिखो(fd, buf, count);
पूर्ण

/*
 * 31 bit emulation wrapper functions क्रम sys_fadvise64/fadvise64_64.
 * These need to reग_लिखो the advise values क्रम POSIX_FADV_अणुDONTNEED,NOREUSEपूर्ण
 * because the 31 bit values dअगरfer from the 64 bit values.
 */

COMPAT_SYSCALL_DEFINE5(s390_fadvise64, पूर्णांक, fd, u32, high, u32, low, compat_माप_प्रकार, len, पूर्णांक, advise)
अणु
	अगर (advise == 4)
		advise = POSIX_FADV_DONTNEED;
	अन्यथा अगर (advise == 5)
		advise = POSIX_FADV_NOREUSE;
	वापस ksys_fadvise64_64(fd, (अचिन्हित दीर्घ)high << 32 | low, len,
				 advise);
पूर्ण

काष्ठा fadvise64_64_args अणु
	पूर्णांक fd;
	दीर्घ दीर्घ offset;
	दीर्घ दीर्घ len;
	पूर्णांक advice;
पूर्ण;

COMPAT_SYSCALL_DEFINE1(s390_fadvise64_64, काष्ठा fadvise64_64_args __user *, args)
अणु
	काष्ठा fadvise64_64_args a;

	अगर ( copy_from_user(&a, args, माप(a)) )
		वापस -EFAULT;
	अगर (a.advice == 4)
		a.advice = POSIX_FADV_DONTNEED;
	अन्यथा अगर (a.advice == 5)
		a.advice = POSIX_FADV_NOREUSE;
	वापस ksys_fadvise64_64(a.fd, a.offset, a.len, a.advice);
पूर्ण

COMPAT_SYSCALL_DEFINE6(s390_sync_file_range, पूर्णांक, fd, u32, offhigh, u32, offlow,
		       u32, nhigh, u32, nlow, अचिन्हित पूर्णांक, flags)
अणु
	वापस ksys_sync_file_range(fd, ((loff_t)offhigh << 32) + offlow,
				   ((u64)nhigh << 32) + nlow, flags);
पूर्ण

COMPAT_SYSCALL_DEFINE6(s390_fallocate, पूर्णांक, fd, पूर्णांक, mode, u32, offhigh, u32, offlow,
		       u32, lenhigh, u32, lenlow)
अणु
	वापस ksys_fallocate(fd, mode, ((loff_t)offhigh << 32) + offlow,
			      ((u64)lenhigh << 32) + lenlow);
पूर्ण
