<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/alpha/kernel/osf_sys.c
 *
 *  Copyright (C) 1995  Linus Torvalds
 */

/*
 * This file handles some of the stranger OSF/1 प्रणाली call पूर्णांकerfaces.
 * Some of the प्रणाली calls expect a non-C calling standard, others have
 * special parameter blocks..
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/sched/cpuसमय.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/syscalls.h>
#समावेश <linux/unistd.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/user.h>
#समावेश <linux/utsname.h>
#समावेश <linux/समय.स>
#समावेश <linux/समयx.h>
#समावेश <linux/major.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/mman.h>
#समावेश <linux/shm.h>
#समावेश <linux/poll.h>
#समावेश <linux/file.h>
#समावेश <linux/types.h>
#समावेश <linux/ipc.h>
#समावेश <linux/namei.h>
#समावेश <linux/uपन.स>
#समावेश <linux/vfs.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/fpu.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/sysinfo.h>
#समावेश <यंत्र/thपढ़ो_info.h>
#समावेश <यंत्र/hwrpb.h>
#समावेश <यंत्र/processor.h>

/*
 * Brk needs to वापस an error.  Still support Linux's brk(0) query idiom,
 * which OSF programs just shouldn't be doing.  We're still not quite
 * identical to OSF as we करोn't वापस 0 on success, but करोing otherwise
 * would require changes to libc.  Hopefully this is good enough.
 */
SYSCALL_DEFINE1(osf_brk, अचिन्हित दीर्घ, brk)
अणु
	अचिन्हित दीर्घ retval = sys_brk(brk);
	अगर (brk && brk != retval)
		retval = -ENOMEM;
	वापस retval;
पूर्ण
 
/*
 * This is pure guess-work..
 */
SYSCALL_DEFINE4(osf_set_program_attributes, अचिन्हित दीर्घ, text_start,
		अचिन्हित दीर्घ, text_len, अचिन्हित दीर्घ, bss_start,
		अचिन्हित दीर्घ, bss_len)
अणु
	काष्ठा mm_काष्ठा *mm;

	mm = current->mm;
	mm->end_code = bss_start + bss_len;
	mm->start_brk = bss_start + bss_len;
	mm->brk = bss_start + bss_len;
#अगर 0
	prपूर्णांकk("set_program_attributes(%lx %lx %lx %lx)\n",
		text_start, text_len, bss_start, bss_len);
#पूर्ण_अगर
	वापस 0;
पूर्ण

/*
 * OSF/1 directory handling functions...
 *
 * The "getdents()" पूर्णांकerface is much more sane: the "basep" stuff is
 * braindamage (it can't really handle fileप्रणालीs where the directory
 * offset dअगरferences aren't the same as "d_reclen").
 */
#घोषणा NAME_OFFSET	दुरत्व (काष्ठा osf_dirent, d_name)

काष्ठा osf_dirent अणु
	अचिन्हित पूर्णांक d_ino;
	अचिन्हित लघु d_reclen;
	अचिन्हित लघु d_namlen;
	अक्षर d_name[1];
पूर्ण;

काष्ठा osf_dirent_callback अणु
	काष्ठा dir_context ctx;
	काष्ठा osf_dirent __user *dirent;
	दीर्घ __user *basep;
	अचिन्हित पूर्णांक count;
	पूर्णांक error;
पूर्ण;

अटल पूर्णांक
osf_filldir(काष्ठा dir_context *ctx, स्थिर अक्षर *name, पूर्णांक namlen,
	    loff_t offset, u64 ino, अचिन्हित पूर्णांक d_type)
अणु
	काष्ठा osf_dirent __user *dirent;
	काष्ठा osf_dirent_callback *buf =
		container_of(ctx, काष्ठा osf_dirent_callback, ctx);
	अचिन्हित पूर्णांक reclen = ALIGN(NAME_OFFSET + namlen + 1, माप(u32));
	अचिन्हित पूर्णांक d_ino;

	buf->error = -EINVAL;	/* only used अगर we fail */
	अगर (reclen > buf->count)
		वापस -EINVAL;
	d_ino = ino;
	अगर (माप(d_ino) < माप(ino) && d_ino != ino) अणु
		buf->error = -EOVERFLOW;
		वापस -EOVERFLOW;
	पूर्ण
	अगर (buf->basep) अणु
		अगर (put_user(offset, buf->basep))
			जाओ Efault;
		buf->basep = शून्य;
	पूर्ण
	dirent = buf->dirent;
	अगर (put_user(d_ino, &dirent->d_ino) ||
	    put_user(namlen, &dirent->d_namlen) ||
	    put_user(reclen, &dirent->d_reclen) ||
	    copy_to_user(dirent->d_name, name, namlen) ||
	    put_user(0, dirent->d_name + namlen))
		जाओ Efault;
	dirent = (व्योम __user *)dirent + reclen;
	buf->dirent = dirent;
	buf->count -= reclen;
	वापस 0;
Efault:
	buf->error = -EFAULT;
	वापस -EFAULT;
पूर्ण

SYSCALL_DEFINE4(osf_getdirentries, अचिन्हित पूर्णांक, fd,
		काष्ठा osf_dirent __user *, dirent, अचिन्हित पूर्णांक, count,
		दीर्घ __user *, basep)
अणु
	पूर्णांक error;
	काष्ठा fd arg = fdget_pos(fd);
	काष्ठा osf_dirent_callback buf = अणु
		.ctx.actor = osf_filldir,
		.dirent = dirent,
		.basep = basep,
		.count = count
	पूर्ण;

	अगर (!arg.file)
		वापस -EBADF;

	error = iterate_dir(arg.file, &buf.ctx);
	अगर (error >= 0)
		error = buf.error;
	अगर (count != buf.count)
		error = count - buf.count;

	fdput_pos(arg);
	वापस error;
पूर्ण

#अघोषित NAME_OFFSET

SYSCALL_DEFINE6(osf_mmap, अचिन्हित दीर्घ, addr, अचिन्हित दीर्घ, len,
		अचिन्हित दीर्घ, prot, अचिन्हित दीर्घ, flags, अचिन्हित दीर्घ, fd,
		अचिन्हित दीर्घ, off)
अणु
	अचिन्हित दीर्घ ret = -EINVAL;

#अगर 0
	अगर (flags & (_MAP_HASSEMAPHORE | _MAP_INHERIT | _MAP_UNALIGNED))
		prपूर्णांकk("%s: unimplemented OSF mmap flags %04lx\n", 
			current->comm, flags);
#पूर्ण_अगर
	अगर ((off + PAGE_ALIGN(len)) < off)
		जाओ out;
	अगर (off & ~PAGE_MASK)
		जाओ out;
	ret = ksys_mmap_pgoff(addr, len, prot, flags, fd, off >> PAGE_SHIFT);
 out:
	वापस ret;
पूर्ण

काष्ठा osf_stat अणु
	पूर्णांक		st_dev;
	पूर्णांक		st_pad1;
	अचिन्हित	st_mode;
	अचिन्हित लघु	st_nlink;
	लघु		st_nlink_reserved;
	अचिन्हित	st_uid;
	अचिन्हित	st_gid;
	पूर्णांक		st_rdev;
	पूर्णांक		st_ldev;
	दीर्घ		st_size;
	पूर्णांक		st_pad2;
	पूर्णांक		st_uaसमय;
	पूर्णांक		st_pad3;
	पूर्णांक		st_umसमय;
	पूर्णांक		st_pad4;
	पूर्णांक		st_uस_समय;
	पूर्णांक		st_pad5;
	पूर्णांक		st_pad6;
	अचिन्हित	st_flags;
	अचिन्हित	st_gen;
	दीर्घ		st_spare[4];
	अचिन्हित	st_ino;
	पूर्णांक		st_ino_reserved;
	पूर्णांक		st_aसमय;
	पूर्णांक		st_aसमय_reserved;
	पूर्णांक		st_mसमय;
	पूर्णांक		st_mसमय_reserved;
	पूर्णांक		st_स_समय;
	पूर्णांक		st_स_समय_reserved;
	दीर्घ		st_blksize;
	दीर्घ		st_blocks;
पूर्ण;

/*
 * The OSF/1 statfs काष्ठाure is much larger, but this should
 * match the beginning, at least.
 */
काष्ठा osf_statfs अणु
	लघु f_type;
	लघु f_flags;
	पूर्णांक f_fsize;
	पूर्णांक f_bsize;
	पूर्णांक f_blocks;
	पूर्णांक f_bमुक्त;
	पूर्णांक f_bavail;
	पूर्णांक f_files;
	पूर्णांक f_fमुक्त;
	__kernel_fsid_t f_fsid;
पूर्ण;

काष्ठा osf_statfs64 अणु
	लघु f_type;
	लघु f_flags;
	पूर्णांक f_pad1;
	पूर्णांक f_pad2;
	पूर्णांक f_pad3;
	पूर्णांक f_pad4;
	पूर्णांक f_pad5;
	पूर्णांक f_pad6;
	पूर्णांक f_pad7;
	__kernel_fsid_t f_fsid;
	u_लघु f_namemax;
	लघु f_reserved1;
	पूर्णांक f_spare[8];
	अक्षर f_pad8[90];
	अक्षर f_pad9[90];
	दीर्घ mount_info[10];
	u_दीर्घ f_flags2;
	दीर्घ f_spare2[14];
	दीर्घ f_fsize;
	दीर्घ f_bsize;
	दीर्घ f_blocks;
	दीर्घ f_bमुक्त;
	दीर्घ f_bavail;
	दीर्घ f_files;
	दीर्घ f_fमुक्त;
पूर्ण;

अटल पूर्णांक
linux_to_osf_stat(काष्ठा kstat *lstat, काष्ठा osf_stat __user *osf_stat)
अणु
	काष्ठा osf_stat पंचांगp = अणु 0 पूर्ण;

	पंचांगp.st_dev	= lstat->dev;
	पंचांगp.st_mode	= lstat->mode;
	पंचांगp.st_nlink	= lstat->nlink;
	पंचांगp.st_uid	= from_kuid_munged(current_user_ns(), lstat->uid);
	पंचांगp.st_gid	= from_kgid_munged(current_user_ns(), lstat->gid);
	पंचांगp.st_rdev	= lstat->rdev;
	पंचांगp.st_ldev	= lstat->rdev;
	पंचांगp.st_size	= lstat->size;
	पंचांगp.st_uaसमय	= lstat->aसमय.tv_nsec / 1000;
	पंचांगp.st_umसमय	= lstat->mसमय.tv_nsec / 1000;
	पंचांगp.st_uस_समय	= lstat->स_समय.tv_nsec / 1000;
	पंचांगp.st_ino	= lstat->ino;
	पंचांगp.st_aसमय	= lstat->aसमय.tv_sec;
	पंचांगp.st_mसमय	= lstat->mसमय.tv_sec;
	पंचांगp.st_स_समय	= lstat->स_समय.tv_sec;
	पंचांगp.st_blksize	= lstat->blksize;
	पंचांगp.st_blocks	= lstat->blocks;

	वापस copy_to_user(osf_stat, &पंचांगp, माप(पंचांगp)) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक
linux_to_osf_statfs(काष्ठा kstatfs *linux_stat, काष्ठा osf_statfs __user *osf_stat,
		    अचिन्हित दीर्घ bufsiz)
अणु
	काष्ठा osf_statfs पंचांगp_stat;

	पंचांगp_stat.f_type = linux_stat->f_type;
	पंचांगp_stat.f_flags = 0;	/* mount flags */
	पंचांगp_stat.f_fsize = linux_stat->f_frsize;
	पंचांगp_stat.f_bsize = linux_stat->f_bsize;
	पंचांगp_stat.f_blocks = linux_stat->f_blocks;
	पंचांगp_stat.f_bमुक्त = linux_stat->f_bमुक्त;
	पंचांगp_stat.f_bavail = linux_stat->f_bavail;
	पंचांगp_stat.f_files = linux_stat->f_files;
	पंचांगp_stat.f_fमुक्त = linux_stat->f_fमुक्त;
	पंचांगp_stat.f_fsid = linux_stat->f_fsid;
	अगर (bufsiz > माप(पंचांगp_stat))
		bufsiz = माप(पंचांगp_stat);
	वापस copy_to_user(osf_stat, &पंचांगp_stat, bufsiz) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक
linux_to_osf_statfs64(काष्ठा kstatfs *linux_stat, काष्ठा osf_statfs64 __user *osf_stat,
		      अचिन्हित दीर्घ bufsiz)
अणु
	काष्ठा osf_statfs64 पंचांगp_stat = अणु 0 पूर्ण;

	पंचांगp_stat.f_type = linux_stat->f_type;
	पंचांगp_stat.f_fsize = linux_stat->f_frsize;
	पंचांगp_stat.f_bsize = linux_stat->f_bsize;
	पंचांगp_stat.f_blocks = linux_stat->f_blocks;
	पंचांगp_stat.f_bमुक्त = linux_stat->f_bमुक्त;
	पंचांगp_stat.f_bavail = linux_stat->f_bavail;
	पंचांगp_stat.f_files = linux_stat->f_files;
	पंचांगp_stat.f_fमुक्त = linux_stat->f_fमुक्त;
	पंचांगp_stat.f_fsid = linux_stat->f_fsid;
	अगर (bufsiz > माप(पंचांगp_stat))
		bufsiz = माप(पंचांगp_stat);
	वापस copy_to_user(osf_stat, &पंचांगp_stat, bufsiz) ? -EFAULT : 0;
पूर्ण

SYSCALL_DEFINE3(osf_statfs, स्थिर अक्षर __user *, pathname,
		काष्ठा osf_statfs __user *, buffer, अचिन्हित दीर्घ, bufsiz)
अणु
	काष्ठा kstatfs linux_stat;
	पूर्णांक error = user_statfs(pathname, &linux_stat);
	अगर (!error)
		error = linux_to_osf_statfs(&linux_stat, buffer, bufsiz);
	वापस error;	
पूर्ण

SYSCALL_DEFINE2(osf_stat, अक्षर __user *, name, काष्ठा osf_stat __user *, buf)
अणु
	काष्ठा kstat stat;
	पूर्णांक error;

	error = vfs_stat(name, &stat);
	अगर (error)
		वापस error;

	वापस linux_to_osf_stat(&stat, buf);
पूर्ण

SYSCALL_DEFINE2(osf_lstat, अक्षर __user *, name, काष्ठा osf_stat __user *, buf)
अणु
	काष्ठा kstat stat;
	पूर्णांक error;

	error = vfs_lstat(name, &stat);
	अगर (error)
		वापस error;

	वापस linux_to_osf_stat(&stat, buf);
पूर्ण

SYSCALL_DEFINE2(osf_ख_स्थिति, पूर्णांक, fd, काष्ठा osf_stat __user *, buf)
अणु
	काष्ठा kstat stat;
	पूर्णांक error;

	error = vfs_ख_स्थिति(fd, &stat);
	अगर (error)
		वापस error;

	वापस linux_to_osf_stat(&stat, buf);
पूर्ण

SYSCALL_DEFINE3(osf_ख_स्थितिfs, अचिन्हित दीर्घ, fd,
		काष्ठा osf_statfs __user *, buffer, अचिन्हित दीर्घ, bufsiz)
अणु
	काष्ठा kstatfs linux_stat;
	पूर्णांक error = fd_statfs(fd, &linux_stat);
	अगर (!error)
		error = linux_to_osf_statfs(&linux_stat, buffer, bufsiz);
	वापस error;
पूर्ण

SYSCALL_DEFINE3(osf_statfs64, अक्षर __user *, pathname,
		काष्ठा osf_statfs64 __user *, buffer, अचिन्हित दीर्घ, bufsiz)
अणु
	काष्ठा kstatfs linux_stat;
	पूर्णांक error = user_statfs(pathname, &linux_stat);
	अगर (!error)
		error = linux_to_osf_statfs64(&linux_stat, buffer, bufsiz);
	वापस error;
पूर्ण

SYSCALL_DEFINE3(osf_ख_स्थितिfs64, अचिन्हित दीर्घ, fd,
		काष्ठा osf_statfs64 __user *, buffer, अचिन्हित दीर्घ, bufsiz)
अणु
	काष्ठा kstatfs linux_stat;
	पूर्णांक error = fd_statfs(fd, &linux_stat);
	अगर (!error)
		error = linux_to_osf_statfs64(&linux_stat, buffer, bufsiz);
	वापस error;
पूर्ण

/*
 * Uhh.. OSF/1 mount parameters aren't exactly obvious..
 *
 * Although to be frank, neither are the native Linux/i386 ones..
 */
काष्ठा ufs_args अणु
	अक्षर __user *devname;
	पूर्णांक flags;
	uid_t exroot;
पूर्ण;

काष्ठा cdfs_args अणु
	अक्षर __user *devname;
	पूर्णांक flags;
	uid_t exroot;

	/* This has lots more here, which Linux handles with the option block
	   but I'm too lazy to करो the translation पूर्णांकo ASCII.  */
पूर्ण;

काष्ठा procfs_args अणु
	अक्षर __user *devname;
	पूर्णांक flags;
	uid_t exroot;
पूर्ण;

/*
 * We can't actually handle ufs yet, so we translate UFS mounts to
 * ext2fs mounts. I wouldn't mind a UFS fileप्रणाली, but the UFS
 * layout is so braindead it's a major headache करोing it.
 *
 * Just how दीर्घ ago was it written? OTOH our UFS driver may be still
 * unhappy with OSF UFS. [CHECKME]
 */
अटल पूर्णांक
osf_ufs_mount(स्थिर अक्षर __user *स_नाम,
	      काष्ठा ufs_args __user *args, पूर्णांक flags)
अणु
	पूर्णांक retval;
	काष्ठा cdfs_args पंचांगp;
	काष्ठा filename *devname;

	retval = -EFAULT;
	अगर (copy_from_user(&पंचांगp, args, माप(पंचांगp)))
		जाओ out;
	devname = getname(पंचांगp.devname);
	retval = PTR_ERR(devname);
	अगर (IS_ERR(devname))
		जाओ out;
	retval = करो_mount(devname->name, स_नाम, "ext2", flags, शून्य);
	putname(devname);
 out:
	वापस retval;
पूर्ण

अटल पूर्णांक
osf_cdfs_mount(स्थिर अक्षर __user *स_नाम,
	       काष्ठा cdfs_args __user *args, पूर्णांक flags)
अणु
	पूर्णांक retval;
	काष्ठा cdfs_args पंचांगp;
	काष्ठा filename *devname;

	retval = -EFAULT;
	अगर (copy_from_user(&पंचांगp, args, माप(पंचांगp)))
		जाओ out;
	devname = getname(पंचांगp.devname);
	retval = PTR_ERR(devname);
	अगर (IS_ERR(devname))
		जाओ out;
	retval = करो_mount(devname->name, स_नाम, "iso9660", flags, शून्य);
	putname(devname);
 out:
	वापस retval;
पूर्ण

अटल पूर्णांक
osf_procfs_mount(स्थिर अक्षर __user *स_नाम,
		 काष्ठा procfs_args __user *args, पूर्णांक flags)
अणु
	काष्ठा procfs_args पंचांगp;

	अगर (copy_from_user(&पंचांगp, args, माप(पंचांगp)))
		वापस -EFAULT;

	वापस करो_mount("", स_नाम, "proc", flags, शून्य);
पूर्ण

SYSCALL_DEFINE4(osf_mount, अचिन्हित दीर्घ, typenr, स्थिर अक्षर __user *, path,
		पूर्णांक, flag, व्योम __user *, data)
अणु
	पूर्णांक retval;

	चयन (typenr) अणु
	हाल 1:
		retval = osf_ufs_mount(path, data, flag);
		अवरोध;
	हाल 6:
		retval = osf_cdfs_mount(path, data, flag);
		अवरोध;
	हाल 9:
		retval = osf_procfs_mount(path, data, flag);
		अवरोध;
	शेष:
		retval = -EINVAL;
		prपूर्णांकk("osf_mount(%ld, %x)\n", typenr, flag);
	पूर्ण

	वापस retval;
पूर्ण

SYSCALL_DEFINE1(osf_utsname, अक्षर __user *, name)
अणु
	अक्षर पंचांगp[5 * 32];

	करोwn_पढ़ो(&uts_sem);
	स_नकल(पंचांगp + 0 * 32, utsname()->sysname, 32);
	स_नकल(पंचांगp + 1 * 32, utsname()->nodename, 32);
	स_नकल(पंचांगp + 2 * 32, utsname()->release, 32);
	स_नकल(पंचांगp + 3 * 32, utsname()->version, 32);
	स_नकल(पंचांगp + 4 * 32, utsname()->machine, 32);
	up_पढ़ो(&uts_sem);

	अगर (copy_to_user(name, पंचांगp, माप(पंचांगp)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

SYSCALL_DEFINE0(getpagesize)
अणु
	वापस PAGE_SIZE;
पूर्ण

SYSCALL_DEFINE0(getdtablesize)
अणु
	वापस sysctl_nr_खोलो;
पूर्ण

/*
 * For compatibility with OSF/1 only.  Use utsname(2) instead.
 */
SYSCALL_DEFINE2(osf_getकरोमुख्यname, अक्षर __user *, name, पूर्णांक, namelen)
अणु
	पूर्णांक len;
	अक्षर *kname;
	अक्षर पंचांगp[32];

	अगर (namelen < 0 || namelen > 32)
		namelen = 32;

	करोwn_पढ़ो(&uts_sem);
	kname = utsname()->करोमुख्यname;
	len = strnlen(kname, namelen);
	len = min(len + 1, namelen);
	स_नकल(पंचांगp, kname, len);
	up_पढ़ो(&uts_sem);

	अगर (copy_to_user(name, पंचांगp, len))
		वापस -EFAULT;
	वापस 0;
पूर्ण

/*
 * The following stuff should move पूर्णांकo a header file should it ever
 * be labeled "officially supported."  Right now, there is just enough
 * support to aव्योम applications (such as tar) prपूर्णांकing error
 * messages.  The attributes are not really implemented.
 */

/*
 * Values क्रम Property list entry flag
 */
#घोषणा PLE_PROPAGATE_ON_COPY		0x1	/* cp(1) will copy entry
						   by शेष */
#घोषणा PLE_FLAG_MASK			0x1	/* Valid flag values */
#घोषणा PLE_FLAG_ALL			-1	/* All flag value */

काष्ठा proplistname_args अणु
	अचिन्हित पूर्णांक pl_mask;
	अचिन्हित पूर्णांक pl_numnames;
	अक्षर **pl_names;
पूर्ण;

जोड़ pl_args अणु
	काष्ठा setargs अणु
		अक्षर __user *path;
		दीर्घ follow;
		दीर्घ nbytes;
		अक्षर __user *buf;
	पूर्ण set;
	काष्ठा fsetargs अणु
		दीर्घ fd;
		दीर्घ nbytes;
		अक्षर __user *buf;
	पूर्ण fset;
	काष्ठा getargs अणु
		अक्षर __user *path;
		दीर्घ follow;
		काष्ठा proplistname_args __user *name_args;
		दीर्घ nbytes;
		अक्षर __user *buf;
		पूर्णांक __user *min_buf_size;
	पूर्ण get;
	काष्ठा fgetargs अणु
		दीर्घ fd;
		काष्ठा proplistname_args __user *name_args;
		दीर्घ nbytes;
		अक्षर __user *buf;
		पूर्णांक __user *min_buf_size;
	पूर्ण fget;
	काष्ठा delargs अणु
		अक्षर __user *path;
		दीर्घ follow;
		काष्ठा proplistname_args __user *name_args;
	पूर्ण del;
	काष्ठा fdelargs अणु
		दीर्घ fd;
		काष्ठा proplistname_args __user *name_args;
	पूर्ण fdel;
पूर्ण;

क्रमागत pl_code अणु
	PL_SET = 1, PL_FSET = 2,
	PL_GET = 3, PL_FGET = 4,
	PL_DEL = 5, PL_FDEL = 6
पूर्ण;

SYSCALL_DEFINE2(osf_proplist_syscall, क्रमागत pl_code, code,
		जोड़ pl_args __user *, args)
अणु
	दीर्घ error;
	पूर्णांक __user *min_buf_size_ptr;

	चयन (code) अणु
	हाल PL_SET:
		अगर (get_user(error, &args->set.nbytes))
			error = -EFAULT;
		अवरोध;
	हाल PL_FSET:
		अगर (get_user(error, &args->fset.nbytes))
			error = -EFAULT;
		अवरोध;
	हाल PL_GET:
		error = get_user(min_buf_size_ptr, &args->get.min_buf_size);
		अगर (error)
			अवरोध;
		error = put_user(0, min_buf_size_ptr);
		अवरोध;
	हाल PL_FGET:
		error = get_user(min_buf_size_ptr, &args->fget.min_buf_size);
		अगर (error)
			अवरोध;
		error = put_user(0, min_buf_size_ptr);
		अवरोध;
	हाल PL_DEL:
	हाल PL_FDEL:
		error = 0;
		अवरोध;
	शेष:
		error = -EOPNOTSUPP;
		अवरोध;
	पूर्ण
	वापस error;
पूर्ण

SYSCALL_DEFINE2(osf_sigstack, काष्ठा sigstack __user *, uss,
		काष्ठा sigstack __user *, uoss)
अणु
	अचिन्हित दीर्घ usp = rdusp();
	अचिन्हित दीर्घ oss_sp = current->sas_ss_sp + current->sas_ss_size;
	अचिन्हित दीर्घ oss_os = on_sig_stack(usp);
	पूर्णांक error;

	अगर (uss) अणु
		व्योम __user *ss_sp;

		error = -EFAULT;
		अगर (get_user(ss_sp, &uss->ss_sp))
			जाओ out;

		/* If the current stack was set with sigaltstack, करोn't
		   swap stacks जबतक we are on it.  */
		error = -EPERM;
		अगर (current->sas_ss_sp && on_sig_stack(usp))
			जाओ out;

		/* Since we करोn't know the extent of the stack, and we don't
		   track onstack-ness, but rather calculate it, we must 
		   presume a size.  Ho hum this पूर्णांकerface is lossy.  */
		current->sas_ss_sp = (अचिन्हित दीर्घ)ss_sp - SIGSTKSZ;
		current->sas_ss_size = SIGSTKSZ;
	पूर्ण

	अगर (uoss) अणु
		error = -EFAULT;
		अगर (put_user(oss_sp, &uoss->ss_sp) ||
		    put_user(oss_os, &uoss->ss_onstack))
			जाओ out;
	पूर्ण

	error = 0;
 out:
	वापस error;
पूर्ण

SYSCALL_DEFINE3(osf_sysinfo, पूर्णांक, command, अक्षर __user *, buf, दीर्घ, count)
अणु
	स्थिर अक्षर *sysinfo_table[] = अणु
		utsname()->sysname,
		utsname()->nodename,
		utsname()->release,
		utsname()->version,
		utsname()->machine,
		"alpha",	/* inकाष्ठाion set architecture */
		"dummy",	/* hardware serial number */
		"dummy",	/* hardware manufacturer */
		"dummy",	/* secure RPC करोमुख्य */
	पूर्ण;
	अचिन्हित दीर्घ offset;
	स्थिर अक्षर *res;
	दीर्घ len;
	अक्षर पंचांगp[__NEW_UTS_LEN + 1];

	offset = command-1;
	अगर (offset >= ARRAY_SIZE(sysinfo_table)) अणु
		/* Digital UNIX has a few unpublished पूर्णांकerfaces here */
		prपूर्णांकk("sysinfo(%d)", command);
		वापस -EINVAL;
	पूर्ण

	करोwn_पढ़ो(&uts_sem);
	res = sysinfo_table[offset];
	len = म_माप(res)+1;
	अगर ((अचिन्हित दीर्घ)len > (अचिन्हित दीर्घ)count)
		len = count;
	स_नकल(पंचांगp, res, len);
	up_पढ़ो(&uts_sem);
	अगर (copy_to_user(buf, पंचांगp, len))
		वापस -EFAULT;
	वापस 0;
पूर्ण

SYSCALL_DEFINE5(osf_माला_लोysinfo, अचिन्हित दीर्घ, op, व्योम __user *, buffer,
		अचिन्हित दीर्घ, nbytes, पूर्णांक __user *, start, व्योम __user *, arg)
अणु
	अचिन्हित दीर्घ w;
	काष्ठा percpu_काष्ठा *cpu;

	चयन (op) अणु
	हाल GSI_IEEE_FP_CONTROL:
		/* Return current software fp control & status bits.  */
		/* Note that DU करोesn't verअगरy available space here.  */

 		w = current_thपढ़ो_info()->ieee_state & IEEE_SW_MASK;
 		w = swcr_update_status(w, rdfpcr());
		अगर (put_user(w, (अचिन्हित दीर्घ __user *) buffer))
			वापस -EFAULT;
		वापस 0;

	हाल GSI_IEEE_STATE_AT_SIGNAL:
		/*
		 * Not sure anybody will ever use this weird stuff.  These
		 * ops can be used (under OSF/1) to set the fpcr that should
		 * be used when a संकेत handler starts executing.
		 */
		अवरोध;

 	हाल GSI_UACPROC:
		अगर (nbytes < माप(अचिन्हित पूर्णांक))
			वापस -EINVAL;
		w = current_thपढ़ो_info()->status & UAC_BITMASK;
		अगर (put_user(w, (अचिन्हित पूर्णांक __user *)buffer))
			वापस -EFAULT;
 		वापस 1;

	हाल GSI_PROC_TYPE:
		अगर (nbytes < माप(अचिन्हित दीर्घ))
			वापस -EINVAL;
		cpu = (काष्ठा percpu_काष्ठा*)
		  ((अक्षर*)hwrpb + hwrpb->processor_offset);
		w = cpu->type;
		अगर (put_user(w, (अचिन्हित दीर्घ  __user*)buffer))
			वापस -EFAULT;
		वापस 1;

	हाल GSI_GET_HWRPB:
		अगर (nbytes > माप(*hwrpb))
			वापस -EINVAL;
		अगर (copy_to_user(buffer, hwrpb, nbytes) != 0)
			वापस -EFAULT;
		वापस 1;

	शेष:
		अवरोध;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

SYSCALL_DEFINE5(osf_setsysinfo, अचिन्हित दीर्घ, op, व्योम __user *, buffer,
		अचिन्हित दीर्घ, nbytes, पूर्णांक __user *, start, व्योम __user *, arg)
अणु
	चयन (op) अणु
	हाल SSI_IEEE_FP_CONTROL: अणु
		अचिन्हित दीर्घ swcr, fpcr;
		अचिन्हित पूर्णांक *state;

		/* 
		 * Alpha Architecture Handbook 4.7.7.3:
		 * To be fully IEEE compiant, we must track the current IEEE
		 * exception state in software, because spurious bits can be
		 * set in the trap shaकरोw of a software-complete insn.
		 */

		अगर (get_user(swcr, (अचिन्हित दीर्घ __user *)buffer))
			वापस -EFAULT;
		state = &current_thपढ़ो_info()->ieee_state;

		/* Update softare trap enable bits.  */
		*state = (*state & ~IEEE_SW_MASK) | (swcr & IEEE_SW_MASK);

		/* Update the real fpcr.  */
		fpcr = rdfpcr() & FPCR_DYN_MASK;
		fpcr |= ieee_swcr_to_fpcr(swcr);
		wrfpcr(fpcr);

		वापस 0;
	पूर्ण

	हाल SSI_IEEE_RAISE_EXCEPTION: अणु
		अचिन्हित दीर्घ exc, swcr, fpcr, fex;
		अचिन्हित पूर्णांक *state;

		अगर (get_user(exc, (अचिन्हित दीर्घ __user *)buffer))
			वापस -EFAULT;
		state = &current_thपढ़ो_info()->ieee_state;
		exc &= IEEE_STATUS_MASK;

		/* Update softare trap enable bits.  */
 		swcr = (*state & IEEE_SW_MASK) | exc;
		*state |= exc;

		/* Update the real fpcr.  */
		fpcr = rdfpcr();
		fpcr |= ieee_swcr_to_fpcr(swcr);
		wrfpcr(fpcr);

 		/* If any exceptions set by this call, and are unmasked,
		   send a संकेत.  Old exceptions are not संकेतed.  */
		fex = (exc >> IEEE_STATUS_TO_EXCSUM_SHIFT) & swcr;
 		अगर (fex) अणु
			पूर्णांक si_code = FPE_FLTUNK;

			अगर (fex & IEEE_TRAP_ENABLE_DNO) si_code = FPE_FLTUND;
			अगर (fex & IEEE_TRAP_ENABLE_INE) si_code = FPE_FLTRES;
			अगर (fex & IEEE_TRAP_ENABLE_UNF) si_code = FPE_FLTUND;
			अगर (fex & IEEE_TRAP_ENABLE_OVF) si_code = FPE_FLTOVF;
			अगर (fex & IEEE_TRAP_ENABLE_DZE) si_code = FPE_FLTDIV;
			अगर (fex & IEEE_TRAP_ENABLE_INV) si_code = FPE_FLTINV;

			send_sig_fault(संक_भ_त्रुटि, si_code,
				       (व्योम __user *)शून्य,  /* FIXME */
				       0, current);
 		पूर्ण
		वापस 0;
	पूर्ण

	हाल SSI_IEEE_STATE_AT_SIGNAL:
	हाल SSI_IEEE_IGNORE_STATE_AT_SIGNAL:
		/*
		 * Not sure anybody will ever use this weird stuff.  These
		 * ops can be used (under OSF/1) to set the fpcr that should
		 * be used when a संकेत handler starts executing.
		 */
		अवरोध;

 	हाल SSI_NVPAIRS: अणु
		अचिन्हित __user *p = buffer;
		अचिन्हित i;
		
		क्रम (i = 0, p = buffer; i < nbytes; ++i, p += 2) अणु
			अचिन्हित v, w, status;

			अगर (get_user(v, p) || get_user(w, p + 1))
 				वापस -EFAULT;
 			चयन (v) अणु
 			हाल SSIN_UACPROC:
				w &= UAC_BITMASK;
				status = current_thपढ़ो_info()->status;
				status = (status & ~UAC_BITMASK) | w;
				current_thपढ़ो_info()->status = status;
 				अवरोध;
 
 			शेष:
 				वापस -EOPNOTSUPP;
 			पूर्ण
 		पूर्ण
 		वापस 0;
	पूर्ण
 
	हाल SSI_LMF:
		वापस 0;

	शेष:
		अवरोध;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

/* Translations due to the fact that OSF's समय_प्रकार is an पूर्णांक.  Which
   affects all sorts of things, like समयval and iसमयrval.  */

बाह्य काष्ठा समयzone sys_tz;

काष्ठा समयval32
अणु
    पूर्णांक tv_sec, tv_usec;
पूर्ण;

काष्ठा iसमयrval32
अणु
    काष्ठा समयval32 it_पूर्णांकerval;
    काष्ठा समयval32 it_value;
पूर्ण;

अटल अंतरभूत दीर्घ
get_tv32(काष्ठा बारpec64 *o, काष्ठा समयval32 __user *i)
अणु
	काष्ठा समयval32 tv;
	अगर (copy_from_user(&tv, i, माप(काष्ठा समयval32)))
		वापस -EFAULT;
	o->tv_sec = tv.tv_sec;
	o->tv_nsec = tv.tv_usec * NSEC_PER_USEC;
	वापस 0;
पूर्ण

अटल अंतरभूत दीर्घ
put_tv32(काष्ठा समयval32 __user *o, काष्ठा बारpec64 *i)
अणु
	वापस copy_to_user(o, &(काष्ठा समयval32)अणु
				.tv_sec = i->tv_sec,
				.tv_usec = i->tv_nsec / NSEC_PER_USECपूर्ण,
			    माप(काष्ठा समयval32));
पूर्ण

अटल अंतरभूत दीर्घ
put_tv_to_tv32(काष्ठा समयval32 __user *o, काष्ठा __kernel_old_समयval *i)
अणु
	वापस copy_to_user(o, &(काष्ठा समयval32)अणु
				.tv_sec = i->tv_sec,
				.tv_usec = i->tv_usecपूर्ण,
			    माप(काष्ठा समयval32));
पूर्ण

अटल अंतरभूत व्योम
jअगरfies_to_समयval32(अचिन्हित दीर्घ jअगरfies, काष्ठा समयval32 *value)
अणु
	value->tv_usec = (jअगरfies % HZ) * (1000000L / HZ);
	value->tv_sec = jअगरfies / HZ;
पूर्ण

SYSCALL_DEFINE2(osf_समय_लोofday, काष्ठा समयval32 __user *, tv,
		काष्ठा समयzone __user *, tz)
अणु
	अगर (tv) अणु
		काष्ठा बारpec64 kts;

		kसमय_get_real_ts64(&kts);
		अगर (put_tv32(tv, &kts))
			वापस -EFAULT;
	पूर्ण
	अगर (tz) अणु
		अगर (copy_to_user(tz, &sys_tz, माप(sys_tz)))
			वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

SYSCALL_DEFINE2(osf_समय_रखोofday, काष्ठा समयval32 __user *, tv,
		काष्ठा समयzone __user *, tz)
अणु
	काष्ठा बारpec64 kts;
	काष्ठा समयzone ktz;

 	अगर (tv) अणु
		अगर (get_tv32(&kts, tv))
			वापस -EFAULT;
	पूर्ण
	अगर (tz) अणु
		अगर (copy_from_user(&ktz, tz, माप(*tz)))
			वापस -EFAULT;
	पूर्ण

	वापस करो_sys_समय_रखोofday64(tv ? &kts : शून्य, tz ? &ktz : शून्य);
पूर्ण

यंत्रlinkage दीर्घ sys_ni_posix_समयrs(व्योम);

SYSCALL_DEFINE2(osf_uबार, स्थिर अक्षर __user *, filename,
		काष्ठा समयval32 __user *, tvs)
अणु
	काष्ठा बारpec64 tv[2];

	अगर (tvs) अणु
		अगर (get_tv32(&tv[0], &tvs[0]) ||
		    get_tv32(&tv[1], &tvs[1]))
			वापस -EFAULT;

		अगर (tv[0].tv_nsec < 0 || tv[0].tv_nsec >= 1000000000 ||
		    tv[1].tv_nsec < 0 || tv[1].tv_nsec >= 1000000000)
			वापस -EINVAL;
	पूर्ण

	वापस करो_uबार(AT_FDCWD, filename, tvs ? tv : शून्य, 0);
पूर्ण

SYSCALL_DEFINE5(osf_select, पूर्णांक, n, fd_set __user *, inp, fd_set __user *, outp,
		fd_set __user *, exp, काष्ठा समयval32 __user *, tvp)
अणु
	काष्ठा बारpec64 end_समय, *to = शून्य;
	अगर (tvp) अणु
		काष्ठा बारpec64 tv;
		to = &end_समय;

		अगर (get_tv32(&tv, tvp))
		    	वापस -EFAULT;

		अगर (tv.tv_sec < 0 || tv.tv_nsec < 0)
			वापस -EINVAL;

		अगर (poll_select_set_समयout(to, tv.tv_sec, tv.tv_nsec))
			वापस -EINVAL;		

	पूर्ण

	/* OSF करोes not copy back the reमुख्यing समय.  */
	वापस core_sys_select(n, inp, outp, exp, to);
पूर्ण

काष्ठा rusage32 अणु
	काष्ठा समयval32 ru_uसमय;	/* user समय used */
	काष्ठा समयval32 ru_sसमय;	/* प्रणाली समय used */
	दीर्घ	ru_maxrss;		/* maximum resident set size */
	दीर्घ	ru_ixrss;		/* पूर्णांकegral shared memory size */
	दीर्घ	ru_idrss;		/* पूर्णांकegral unshared data size */
	दीर्घ	ru_isrss;		/* पूर्णांकegral unshared stack size */
	दीर्घ	ru_minflt;		/* page reclaims */
	दीर्घ	ru_majflt;		/* page faults */
	दीर्घ	ru_nswap;		/* swaps */
	दीर्घ	ru_inblock;		/* block input operations */
	दीर्घ	ru_oublock;		/* block output operations */
	दीर्घ	ru_msgsnd;		/* messages sent */
	दीर्घ	ru_msgrcv;		/* messages received */
	दीर्घ	ru_nसंकेतs;		/* संकेतs received */
	दीर्घ	ru_nvcsw;		/* voluntary context चयनes */
	दीर्घ	ru_nivcsw;		/* involuntary " */
पूर्ण;

SYSCALL_DEFINE2(osf_getrusage, पूर्णांक, who, काष्ठा rusage32 __user *, ru)
अणु
	काष्ठा rusage32 r;
	u64 uसमय, sसमय;
	अचिन्हित दीर्घ uसमय_jअगरfies, sसमय_jअगरfies;

	अगर (who != RUSAGE_SELF && who != RUSAGE_CHILDREN)
		वापस -EINVAL;

	स_रखो(&r, 0, माप(r));
	चयन (who) अणु
	हाल RUSAGE_SELF:
		task_cpuसमय(current, &uसमय, &sसमय);
		uसमय_jअगरfies = nsecs_to_jअगरfies(uसमय);
		sसमय_jअगरfies = nsecs_to_jअगरfies(sसमय);
		jअगरfies_to_समयval32(uसमय_jअगरfies, &r.ru_uसमय);
		jअगरfies_to_समयval32(sसमय_jअगरfies, &r.ru_sसमय);
		r.ru_minflt = current->min_flt;
		r.ru_majflt = current->maj_flt;
		अवरोध;
	हाल RUSAGE_CHILDREN:
		uसमय_jअगरfies = nsecs_to_jअगरfies(current->संकेत->cuसमय);
		sसमय_jअगरfies = nsecs_to_jअगरfies(current->संकेत->csसमय);
		jअगरfies_to_समयval32(uसमय_jअगरfies, &r.ru_uसमय);
		jअगरfies_to_समयval32(sसमय_jअगरfies, &r.ru_sसमय);
		r.ru_minflt = current->संकेत->cmin_flt;
		r.ru_majflt = current->संकेत->cmaj_flt;
		अवरोध;
	पूर्ण

	वापस copy_to_user(ru, &r, माप(r)) ? -EFAULT : 0;
पूर्ण

SYSCALL_DEFINE4(osf_रुको4, pid_t, pid, पूर्णांक __user *, ustatus, पूर्णांक, options,
		काष्ठा rusage32 __user *, ur)
अणु
	काष्ठा rusage r;
	दीर्घ err = kernel_रुको4(pid, ustatus, options, &r);
	अगर (err <= 0)
		वापस err;
	अगर (!ur)
		वापस err;
	अगर (put_tv_to_tv32(&ur->ru_uसमय, &r.ru_uसमय))
		वापस -EFAULT;
	अगर (put_tv_to_tv32(&ur->ru_sसमय, &r.ru_sसमय))
		वापस -EFAULT;
	अगर (copy_to_user(&ur->ru_maxrss, &r.ru_maxrss,
	      माप(काष्ठा rusage32) - दुरत्व(काष्ठा rusage32, ru_maxrss)))
		वापस -EFAULT;
	वापस err;
पूर्ण

/*
 * I करोn't know what the parameters are: the first one
 * seems to be a समयval poपूर्णांकer, and I suspect the second
 * one is the समय reमुख्यing.. Ho humm.. No करोcumentation.
 */
SYSCALL_DEFINE2(osf_usleep_thपढ़ो, काष्ठा समयval32 __user *, sleep,
		काष्ठा समयval32 __user *, reमुख्य)
अणु
	काष्ठा बारpec64 पंचांगp;
	अचिन्हित दीर्घ ticks;

	अगर (get_tv32(&पंचांगp, sleep))
		जाओ fault;

	ticks = बारpec64_to_jअगरfies(&पंचांगp);

	ticks = schedule_समयout_पूर्णांकerruptible(ticks);

	अगर (reमुख्य) अणु
		jअगरfies_to_बारpec64(ticks, &पंचांगp);
		अगर (put_tv32(reमुख्य, &पंचांगp))
			जाओ fault;
	पूर्ण
	
	वापस 0;
 fault:
	वापस -EFAULT;
पूर्ण


काष्ठा समयx32 अणु
	अचिन्हित पूर्णांक modes;	/* mode selector */
	दीर्घ offset;		/* समय offset (usec) */
	दीर्घ freq;		/* frequency offset (scaled ppm) */
	दीर्घ maxerror;		/* maximum error (usec) */
	दीर्घ esterror;		/* estimated error (usec) */
	पूर्णांक status;		/* घड़ी command/status */
	दीर्घ स्थिरant;		/* pll समय स्थिरant */
	दीर्घ precision;		/* घड़ी precision (usec) (पढ़ो only) */
	दीर्घ tolerance;		/* घड़ी frequency tolerance (ppm)
				 * (पढ़ो only)
				 */
	काष्ठा समयval32 समय;	/* (पढ़ो only) */
	दीर्घ tick;		/* (modअगरied) usecs between घड़ी ticks */

	दीर्घ ppsfreq;           /* pps frequency (scaled ppm) (ro) */
	दीर्घ jitter;            /* pps jitter (us) (ro) */
	पूर्णांक shअगरt;              /* पूर्णांकerval duration (s) (shअगरt) (ro) */
	दीर्घ stabil;            /* pps stability (scaled ppm) (ro) */
	दीर्घ jitcnt;            /* jitter limit exceeded (ro) */
	दीर्घ calcnt;            /* calibration पूर्णांकervals (ro) */
	दीर्घ errcnt;            /* calibration errors (ro) */
	दीर्घ stbcnt;            /* stability limit exceeded (ro) */

	पूर्णांक  :32; पूर्णांक  :32; पूर्णांक  :32; पूर्णांक  :32;
	पूर्णांक  :32; पूर्णांक  :32; पूर्णांक  :32; पूर्णांक  :32;
	पूर्णांक  :32; पूर्णांक  :32; पूर्णांक  :32; पूर्णांक  :32;
पूर्ण;

SYSCALL_DEFINE1(old_adjसमयx, काष्ठा समयx32 __user *, txc_p)
अणु
	काष्ठा __kernel_समयx txc;
	पूर्णांक ret;

	/* copy relevant bits of काष्ठा समयx. */
	अगर (copy_from_user(&txc, txc_p, दुरत्व(काष्ठा समयx32, समय)) ||
	    copy_from_user(&txc.tick, &txc_p->tick, माप(काष्ठा समयx32) - 
			   दुरत्व(काष्ठा समयx32, tick)))
	  वापस -EFAULT;

	ret = करो_adjसमयx(&txc);	
	अगर (ret < 0)
	  वापस ret;
	
	/* copy back to समयx32 */
	अगर (copy_to_user(txc_p, &txc, दुरत्व(काष्ठा समयx32, समय)) ||
	    (copy_to_user(&txc_p->tick, &txc.tick, माप(काष्ठा समयx32) - 
			  दुरत्व(काष्ठा समयx32, tick))) ||
	    (put_user(txc.समय.tv_sec, &txc_p->समय.tv_sec)) ||
	    (put_user(txc.समय.tv_usec, &txc_p->समय.tv_usec)))
	  वापस -EFAULT;

	वापस ret;
पूर्ण

/* Get an address range which is currently unmapped.  Similar to the
   generic version except that we know how to honor ADDR_LIMIT_32BIT.  */

अटल अचिन्हित दीर्घ
arch_get_unmapped_area_1(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
		         अचिन्हित दीर्घ limit)
अणु
	काष्ठा vm_unmapped_area_info info;

	info.flags = 0;
	info.length = len;
	info.low_limit = addr;
	info.high_limit = limit;
	info.align_mask = 0;
	info.align_offset = 0;
	वापस vm_unmapped_area(&info);
पूर्ण

अचिन्हित दीर्घ
arch_get_unmapped_area(काष्ठा file *filp, अचिन्हित दीर्घ addr,
		       अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff,
		       अचिन्हित दीर्घ flags)
अणु
	अचिन्हित दीर्घ limit;

	/* "32 bit" actually means 31 bit, since poपूर्णांकers sign extend.  */
	अगर (current->personality & ADDR_LIMIT_32BIT)
		limit = 0x80000000;
	अन्यथा
		limit = TASK_SIZE;

	अगर (len > limit)
		वापस -ENOMEM;

	अगर (flags & MAP_FIXED)
		वापस addr;

	/* First, see अगर the given suggestion fits.

	   The OSF/1 loader (/sbin/loader) relies on us वापसing an
	   address larger than the requested अगर one exists, which is
	   a terribly broken way to program.

	   That said, I can see the use in being able to suggest not
	   merely specअगरic addresses, but regions of memory -- perhaps
	   this feature should be incorporated पूर्णांकo all ports?  */

	अगर (addr) अणु
		addr = arch_get_unmapped_area_1 (PAGE_ALIGN(addr), len, limit);
		अगर (addr != (अचिन्हित दीर्घ) -ENOMEM)
			वापस addr;
	पूर्ण

	/* Next, try allocating at TASK_UNMAPPED_BASE.  */
	addr = arch_get_unmapped_area_1 (PAGE_ALIGN(TASK_UNMAPPED_BASE),
					 len, limit);
	अगर (addr != (अचिन्हित दीर्घ) -ENOMEM)
		वापस addr;

	/* Finally, try allocating in low memory.  */
	addr = arch_get_unmapped_area_1 (PAGE_SIZE, len, limit);

	वापस addr;
पूर्ण

#अगर_घोषित CONFIG_OSF4_COMPAT
/* Clear top 32 bits of iov_len in the user's buffer क्रम
   compatibility with old versions of OSF/1 where iov_len
   was defined as पूर्णांक. */
अटल पूर्णांक
osf_fix_iov_len(स्थिर काष्ठा iovec __user *iov, अचिन्हित दीर्घ count)
अणु
	अचिन्हित दीर्घ i;

	क्रम (i = 0 ; i < count ; i++) अणु
		पूर्णांक __user *iov_len_high = (पूर्णांक __user *)&iov[i].iov_len + 1;

		अगर (put_user(0, iov_len_high))
			वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

SYSCALL_DEFINE3(osf_पढ़ोv, अचिन्हित दीर्घ, fd,
		स्थिर काष्ठा iovec __user *, vector, अचिन्हित दीर्घ, count)
अणु
#अगर_घोषित CONFIG_OSF4_COMPAT
	अगर (unlikely(personality(current->personality) == PER_OSF4))
		अगर (osf_fix_iov_len(vector, count))
			वापस -EFAULT;
#पूर्ण_अगर

	वापस sys_पढ़ोv(fd, vector, count);
पूर्ण

SYSCALL_DEFINE3(osf_ग_लिखोv, अचिन्हित दीर्घ, fd,
		स्थिर काष्ठा iovec __user *, vector, अचिन्हित दीर्घ, count)
अणु
#अगर_घोषित CONFIG_OSF4_COMPAT
	अगर (unlikely(personality(current->personality) == PER_OSF4))
		अगर (osf_fix_iov_len(vector, count))
			वापस -EFAULT;
#पूर्ण_अगर
	वापस sys_ग_लिखोv(fd, vector, count);
पूर्ण

SYSCALL_DEFINE2(osf_getpriority, पूर्णांक, which, पूर्णांक, who)
अणु
	पूर्णांक prio = sys_getpriority(which, who);
	अगर (prio >= 0) अणु
		/* Return value is the unbiased priority, i.e. 20 - prio.
		   This करोes result in negative वापस values, so संकेत
		   no error */
		क्रमce_successful_syscall_वापस();
		prio = 20 - prio;
	पूर्ण
	वापस prio;
पूर्ण

SYSCALL_DEFINE0(getxuid)
अणु
	current_pt_regs()->r20 = sys_geteuid();
	वापस sys_getuid();
पूर्ण

SYSCALL_DEFINE0(getxgid)
अणु
	current_pt_regs()->r20 = sys_getegid();
	वापस sys_getgid();
पूर्ण

SYSCALL_DEFINE0(getxpid)
अणु
	current_pt_regs()->r20 = sys_getppid();
	वापस sys_getpid();
पूर्ण

SYSCALL_DEFINE0(alpha_pipe)
अणु
	पूर्णांक fd[2];
	पूर्णांक res = करो_pipe_flags(fd, 0);
	अगर (!res) अणु
		/* The वापस values are in $0 and $20.  */
		current_pt_regs()->r20 = fd[1];
		res = fd[0];
	पूर्ण
	वापस res;
पूर्ण

SYSCALL_DEFINE1(sethae, अचिन्हित दीर्घ, val)
अणु
	current_pt_regs()->hae = val;
	वापस 0;
पूर्ण
