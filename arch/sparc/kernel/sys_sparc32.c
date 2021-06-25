<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* sys_sparc32.c: Conversion between 32bit and 64bit native syscalls.
 *
 * Copyright (C) 1997,1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 * Copyright (C) 1997, 2007 David S. Miller (davem@davemloft.net)
 *
 * These routines मुख्यtain argument size conversion between 32bit and 64bit
 * environment.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/capability.h>
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
#समावेश <linux/highuid.h>
#समावेश <linux/mman.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/in.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/dnotअगरy.h>
#समावेश <linux/security.h>
#समावेश <linux/compat.h>
#समावेश <linux/vfs.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/types.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/fpumacro.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/compat_संकेत.स>

#समावेश "systbls.h"

COMPAT_SYSCALL_DEFINE3(truncate64, स्थिर अक्षर __user *, path, u32, high, u32, low)
अणु
	वापस ksys_truncate(path, ((u64)high << 32) | low);
पूर्ण

COMPAT_SYSCALL_DEFINE3(ftruncate64, अचिन्हित पूर्णांक, fd, u32, high, u32, low)
अणु
	वापस ksys_ftruncate(fd, ((u64)high << 32) | low);
पूर्ण

अटल पूर्णांक cp_compat_stat64(काष्ठा kstat *stat,
			    काष्ठा compat_stat64 __user *statbuf)
अणु
	पूर्णांक err;

	err  = put_user(huge_encode_dev(stat->dev), &statbuf->st_dev);
	err |= put_user(stat->ino, &statbuf->st_ino);
	err |= put_user(stat->mode, &statbuf->st_mode);
	err |= put_user(stat->nlink, &statbuf->st_nlink);
	err |= put_user(from_kuid_munged(current_user_ns(), stat->uid), &statbuf->st_uid);
	err |= put_user(from_kgid_munged(current_user_ns(), stat->gid), &statbuf->st_gid);
	err |= put_user(huge_encode_dev(stat->rdev), &statbuf->st_rdev);
	err |= put_user(0, (अचिन्हित दीर्घ __user *) &statbuf->__pad3[0]);
	err |= put_user(stat->size, &statbuf->st_size);
	err |= put_user(stat->blksize, &statbuf->st_blksize);
	err |= put_user(0, (अचिन्हित पूर्णांक __user *) &statbuf->__pad4[0]);
	err |= put_user(0, (अचिन्हित पूर्णांक __user *) &statbuf->__pad4[4]);
	err |= put_user(stat->blocks, &statbuf->st_blocks);
	err |= put_user(stat->aसमय.tv_sec, &statbuf->st_aसमय);
	err |= put_user(stat->aसमय.tv_nsec, &statbuf->st_aसमय_nsec);
	err |= put_user(stat->mसमय.tv_sec, &statbuf->st_mसमय);
	err |= put_user(stat->mसमय.tv_nsec, &statbuf->st_mसमय_nsec);
	err |= put_user(stat->स_समय.tv_sec, &statbuf->st_स_समय);
	err |= put_user(stat->स_समय.tv_nsec, &statbuf->st_स_समय_nsec);
	err |= put_user(0, &statbuf->__unused4);
	err |= put_user(0, &statbuf->__unused5);

	वापस err;
पूर्ण

COMPAT_SYSCALL_DEFINE2(stat64, स्थिर अक्षर __user *, filename,
		काष्ठा compat_stat64 __user *, statbuf)
अणु
	काष्ठा kstat stat;
	पूर्णांक error = vfs_stat(filename, &stat);

	अगर (!error)
		error = cp_compat_stat64(&stat, statbuf);
	वापस error;
पूर्ण

COMPAT_SYSCALL_DEFINE2(lstat64, स्थिर अक्षर __user *, filename,
		काष्ठा compat_stat64 __user *, statbuf)
अणु
	काष्ठा kstat stat;
	पूर्णांक error = vfs_lstat(filename, &stat);

	अगर (!error)
		error = cp_compat_stat64(&stat, statbuf);
	वापस error;
पूर्ण

COMPAT_SYSCALL_DEFINE2(ख_स्थिति64, अचिन्हित पूर्णांक, fd,
		काष्ठा compat_stat64 __user *, statbuf)
अणु
	काष्ठा kstat stat;
	पूर्णांक error = vfs_ख_स्थिति(fd, &stat);

	अगर (!error)
		error = cp_compat_stat64(&stat, statbuf);
	वापस error;
पूर्ण

COMPAT_SYSCALL_DEFINE4(ख_स्थितिat64, अचिन्हित पूर्णांक, dfd,
		स्थिर अक्षर __user *, filename,
		काष्ठा compat_stat64 __user *, statbuf, पूर्णांक, flag)
अणु
	काष्ठा kstat stat;
	पूर्णांक error;

	error = vfs_ख_स्थितिat(dfd, filename, &stat, flag);
	अगर (error)
		वापस error;
	वापस cp_compat_stat64(&stat, statbuf);
पूर्ण

COMPAT_SYSCALL_DEFINE3(sparc_sigaction, पूर्णांक, sig,
			काष्ठा compat_old_sigaction __user *,act,
			काष्ठा compat_old_sigaction __user *,oact)
अणु
	WARN_ON_ONCE(sig >= 0);
	वापस compat_sys_sigaction(-sig, act, oact);
पूर्ण

COMPAT_SYSCALL_DEFINE5(rt_sigaction, पूर्णांक, sig,
			काष्ठा compat_sigaction __user *,act,
			काष्ठा compat_sigaction __user *,oact,
			व्योम __user *,restorer,
			compat_माप_प्रकार,sigsetsize)
अणु
        काष्ठा k_sigaction new_ka, old_ka;
        पूर्णांक ret;

        /* XXX: Don't preclude handling different sized sigset_t's.  */
        अगर (sigsetsize != माप(compat_sigset_t))
                वापस -EINVAL;

        अगर (act) अणु
		u32 u_handler, u_restorer;

		new_ka.ka_restorer = restorer;
		ret = get_user(u_handler, &act->sa_handler);
		new_ka.sa.sa_handler =  compat_ptr(u_handler);
		ret |= get_compat_sigset(&new_ka.sa.sa_mask, &act->sa_mask);
		ret |= get_user(new_ka.sa.sa_flags, &act->sa_flags);
		ret |= get_user(u_restorer, &act->sa_restorer);
		new_ka.sa.sa_restorer = compat_ptr(u_restorer);
                अगर (ret)
                	वापस -EFAULT;
	पूर्ण

	ret = करो_sigaction(sig, act ? &new_ka : शून्य, oact ? &old_ka : शून्य);

	अगर (!ret && oact) अणु
		ret = put_user(ptr_to_compat(old_ka.sa.sa_handler), &oact->sa_handler);
		ret |= put_compat_sigset(&oact->sa_mask, &old_ka.sa.sa_mask,
					 माप(oact->sa_mask));
		ret |= put_user(old_ka.sa.sa_flags, &oact->sa_flags);
		ret |= put_user(ptr_to_compat(old_ka.sa.sa_restorer), &oact->sa_restorer);
		अगर (ret)
			ret = -EFAULT;
        पूर्ण

        वापस ret;
पूर्ण

COMPAT_SYSCALL_DEFINE5(pपढ़ो64, अचिन्हित पूर्णांक, fd, अक्षर __user *, ubuf,
			compat_माप_प्रकार, count, u32, poshi, u32, poslo)
अणु
	वापस ksys_pपढ़ो64(fd, ubuf, count, ((u64)poshi << 32) | poslo);
पूर्ण

COMPAT_SYSCALL_DEFINE5(pग_लिखो64, अचिन्हित पूर्णांक, fd, अक्षर __user *, ubuf,
			compat_माप_प्रकार, count, u32, poshi, u32, poslo)
अणु
	वापस ksys_pग_लिखो64(fd, ubuf, count, ((u64)poshi << 32) | poslo);
पूर्ण

COMPAT_SYSCALL_DEFINE4(पढ़ोahead, पूर्णांक, fd, u32, offhi, u32, offlo,
		     compat_माप_प्रकार, count)
अणु
	वापस ksys_पढ़ोahead(fd, ((u64)offhi << 32) | offlo, count);
पूर्ण

COMPAT_SYSCALL_DEFINE5(fadvise64, पूर्णांक, fd, u32, offhi, u32, offlo,
			  compat_माप_प्रकार, len, पूर्णांक, advice)
अणु
	वापस ksys_fadvise64_64(fd, ((u64)offhi << 32) | offlo, len, advice);
पूर्ण

COMPAT_SYSCALL_DEFINE6(fadvise64_64, पूर्णांक, fd, u32, offhi, u32, offlo,
			     u32, lenhi, u32, lenlo, पूर्णांक, advice)
अणु
	वापस ksys_fadvise64_64(fd,
				 ((u64)offhi << 32) | offlo,
				 ((u64)lenhi << 32) | lenlo,
				 advice);
पूर्ण

COMPAT_SYSCALL_DEFINE6(sync_file_range, अचिन्हित पूर्णांक, fd, u32, off_high, u32, off_low,
			u32, nb_high, u32, nb_low, अचिन्हित पूर्णांक, flags)
अणु
	वापस ksys_sync_file_range(fd,
				    ((u64)off_high << 32) | off_low,
				    ((u64)nb_high << 32) | nb_low,
				    flags);
पूर्ण

COMPAT_SYSCALL_DEFINE6(fallocate, पूर्णांक, fd, पूर्णांक, mode, u32, offhi, u32, offlo,
				     u32, lenhi, u32, lenlo)
अणु
	वापस ksys_fallocate(fd, mode, ((loff_t)offhi << 32) | offlo,
			      ((loff_t)lenhi << 32) | lenlo);
पूर्ण
