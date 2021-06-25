<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/fcntl.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */

#समावेश <linux/syscalls.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/fdtable.h>
#समावेश <linux/capability.h>
#समावेश <linux/dnotअगरy.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/pipe_fs_i.h>
#समावेश <linux/security.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/rcupdate.h>
#समावेश <linux/pid_namespace.h>
#समावेश <linux/user_namespace.h>
#समावेश <linux/memfd.h>
#समावेश <linux/compat.h>
#समावेश <linux/mount.h>

#समावेश <linux/poll.h>
#समावेश <यंत्र/siginfo.h>
#समावेश <linux/uaccess.h>

#घोषणा SETFL_MASK (O_APPEND | O_NONBLOCK | O_NDELAY | O_सूचीECT | O_NOATIME)

अटल पूर्णांक setfl(पूर्णांक fd, काष्ठा file * filp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode * inode = file_inode(filp);
	पूर्णांक error = 0;

	/*
	 * O_APPEND cannot be cleared अगर the file is marked as append-only
	 * and the file is खोलो क्रम ग_लिखो.
	 */
	अगर (((arg ^ filp->f_flags) & O_APPEND) && IS_APPEND(inode))
		वापस -EPERM;

	/* O_NOATIME can only be set by the owner or superuser */
	अगर ((arg & O_NOATIME) && !(filp->f_flags & O_NOATIME))
		अगर (!inode_owner_or_capable(file_mnt_user_ns(filp), inode))
			वापस -EPERM;

	/* required क्रम strict SunOS emulation */
	अगर (O_NONBLOCK != O_NDELAY)
	       अगर (arg & O_NDELAY)
		   arg |= O_NONBLOCK;

	/* Pipe packetized mode is controlled by O_सूचीECT flag */
	अगर (!S_ISFIFO(inode->i_mode) && (arg & O_सूचीECT)) अणु
		अगर (!filp->f_mapping || !filp->f_mapping->a_ops ||
			!filp->f_mapping->a_ops->direct_IO)
				वापस -EINVAL;
	पूर्ण

	अगर (filp->f_op->check_flags)
		error = filp->f_op->check_flags(arg);
	अगर (error)
		वापस error;

	/*
	 * ->fasync() is responsible क्रम setting the FASYNC bit.
	 */
	अगर (((arg ^ filp->f_flags) & FASYNC) && filp->f_op->fasync) अणु
		error = filp->f_op->fasync(fd, filp, (arg & FASYNC) != 0);
		अगर (error < 0)
			जाओ out;
		अगर (error > 0)
			error = 0;
	पूर्ण
	spin_lock(&filp->f_lock);
	filp->f_flags = (arg & SETFL_MASK) | (filp->f_flags & ~SETFL_MASK);
	spin_unlock(&filp->f_lock);

 out:
	वापस error;
पूर्ण

अटल व्योम f_moकरोwn(काष्ठा file *filp, काष्ठा pid *pid, क्रमागत pid_type type,
                     पूर्णांक क्रमce)
अणु
	ग_लिखो_lock_irq(&filp->f_owner.lock);
	अगर (क्रमce || !filp->f_owner.pid) अणु
		put_pid(filp->f_owner.pid);
		filp->f_owner.pid = get_pid(pid);
		filp->f_owner.pid_type = type;

		अगर (pid) अणु
			स्थिर काष्ठा cred *cred = current_cred();
			filp->f_owner.uid = cred->uid;
			filp->f_owner.euid = cred->euid;
		पूर्ण
	पूर्ण
	ग_लिखो_unlock_irq(&filp->f_owner.lock);
पूर्ण

व्योम __f_setown(काष्ठा file *filp, काष्ठा pid *pid, क्रमागत pid_type type,
		पूर्णांक क्रमce)
अणु
	security_file_set_fowner(filp);
	f_moकरोwn(filp, pid, type, क्रमce);
पूर्ण
EXPORT_SYMBOL(__f_setown);

पूर्णांक f_setown(काष्ठा file *filp, अचिन्हित दीर्घ arg, पूर्णांक क्रमce)
अणु
	क्रमागत pid_type type;
	काष्ठा pid *pid = शून्य;
	पूर्णांक who = arg, ret = 0;

	type = PIDTYPE_TGID;
	अगर (who < 0) अणु
		/* aव्योम overflow below */
		अगर (who == पूर्णांक_न्यून)
			वापस -EINVAL;

		type = PIDTYPE_PGID;
		who = -who;
	पूर्ण

	rcu_पढ़ो_lock();
	अगर (who) अणु
		pid = find_vpid(who);
		अगर (!pid)
			ret = -ESRCH;
	पूर्ण

	अगर (!ret)
		__f_setown(filp, pid, type, क्रमce);
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण
EXPORT_SYMBOL(f_setown);

व्योम f_delown(काष्ठा file *filp)
अणु
	f_moकरोwn(filp, शून्य, PIDTYPE_TGID, 1);
पूर्ण

pid_t f_getown(काष्ठा file *filp)
अणु
	pid_t pid = 0;
	पढ़ो_lock(&filp->f_owner.lock);
	rcu_पढ़ो_lock();
	अगर (pid_task(filp->f_owner.pid, filp->f_owner.pid_type)) अणु
		pid = pid_vnr(filp->f_owner.pid);
		अगर (filp->f_owner.pid_type == PIDTYPE_PGID)
			pid = -pid;
	पूर्ण
	rcu_पढ़ो_unlock();
	पढ़ो_unlock(&filp->f_owner.lock);
	वापस pid;
पूर्ण

अटल पूर्णांक f_setown_ex(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा f_owner_ex __user *owner_p = (व्योम __user *)arg;
	काष्ठा f_owner_ex owner;
	काष्ठा pid *pid;
	पूर्णांक type;
	पूर्णांक ret;

	ret = copy_from_user(&owner, owner_p, माप(owner));
	अगर (ret)
		वापस -EFAULT;

	चयन (owner.type) अणु
	हाल F_OWNER_TID:
		type = PIDTYPE_PID;
		अवरोध;

	हाल F_OWNER_PID:
		type = PIDTYPE_TGID;
		अवरोध;

	हाल F_OWNER_PGRP:
		type = PIDTYPE_PGID;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	rcu_पढ़ो_lock();
	pid = find_vpid(owner.pid);
	अगर (owner.pid && !pid)
		ret = -ESRCH;
	अन्यथा
		 __f_setown(filp, pid, type, 1);
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

अटल पूर्णांक f_getown_ex(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा f_owner_ex __user *owner_p = (व्योम __user *)arg;
	काष्ठा f_owner_ex owner = अणुपूर्ण;
	पूर्णांक ret = 0;

	पढ़ो_lock(&filp->f_owner.lock);
	rcu_पढ़ो_lock();
	अगर (pid_task(filp->f_owner.pid, filp->f_owner.pid_type))
		owner.pid = pid_vnr(filp->f_owner.pid);
	rcu_पढ़ो_unlock();
	चयन (filp->f_owner.pid_type) अणु
	हाल PIDTYPE_PID:
		owner.type = F_OWNER_TID;
		अवरोध;

	हाल PIDTYPE_TGID:
		owner.type = F_OWNER_PID;
		अवरोध;

	हाल PIDTYPE_PGID:
		owner.type = F_OWNER_PGRP;
		अवरोध;

	शेष:
		WARN_ON(1);
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	पढ़ो_unlock(&filp->f_owner.lock);

	अगर (!ret) अणु
		ret = copy_to_user(owner_p, &owner, माप(owner));
		अगर (ret)
			ret = -EFAULT;
	पूर्ण
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_CHECKPOINT_RESTORE
अटल पूर्णांक f_getowner_uids(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा user_namespace *user_ns = current_user_ns();
	uid_t __user *dst = (व्योम __user *)arg;
	uid_t src[2];
	पूर्णांक err;

	पढ़ो_lock(&filp->f_owner.lock);
	src[0] = from_kuid(user_ns, filp->f_owner.uid);
	src[1] = from_kuid(user_ns, filp->f_owner.euid);
	पढ़ो_unlock(&filp->f_owner.lock);

	err  = put_user(src[0], &dst[0]);
	err |= put_user(src[1], &dst[1]);

	वापस err;
पूर्ण
#अन्यथा
अटल पूर्णांक f_getowner_uids(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

अटल bool rw_hपूर्णांक_valid(क्रमागत rw_hपूर्णांक hपूर्णांक)
अणु
	चयन (hपूर्णांक) अणु
	हाल RWH_WRITE_LIFE_NOT_SET:
	हाल RWH_WRITE_LIFE_NONE:
	हाल RWH_WRITE_LIFE_SHORT:
	हाल RWH_WRITE_LIFE_MEDIUM:
	हाल RWH_WRITE_LIFE_LONG:
	हाल RWH_WRITE_LIFE_EXTREME:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल दीर्घ fcntl_rw_hपूर्णांक(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			  अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(file);
	u64 __user *argp = (u64 __user *)arg;
	क्रमागत rw_hपूर्णांक hपूर्णांक;
	u64 h;

	चयन (cmd) अणु
	हाल F_GET_खाता_RW_HINT:
		h = file_ग_लिखो_hपूर्णांक(file);
		अगर (copy_to_user(argp, &h, माप(*argp)))
			वापस -EFAULT;
		वापस 0;
	हाल F_SET_खाता_RW_HINT:
		अगर (copy_from_user(&h, argp, माप(h)))
			वापस -EFAULT;
		hपूर्णांक = (क्रमागत rw_hपूर्णांक) h;
		अगर (!rw_hपूर्णांक_valid(hपूर्णांक))
			वापस -EINVAL;

		spin_lock(&file->f_lock);
		file->f_ग_लिखो_hपूर्णांक = hपूर्णांक;
		spin_unlock(&file->f_lock);
		वापस 0;
	हाल F_GET_RW_HINT:
		h = inode->i_ग_लिखो_hपूर्णांक;
		अगर (copy_to_user(argp, &h, माप(*argp)))
			वापस -EFAULT;
		वापस 0;
	हाल F_SET_RW_HINT:
		अगर (copy_from_user(&h, argp, माप(h)))
			वापस -EFAULT;
		hपूर्णांक = (क्रमागत rw_hपूर्णांक) h;
		अगर (!rw_hपूर्णांक_valid(hपूर्णांक))
			वापस -EINVAL;

		inode_lock(inode);
		inode->i_ग_लिखो_hपूर्णांक = hपूर्णांक;
		inode_unlock(inode);
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल दीर्घ करो_fcntl(पूर्णांक fd, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg,
		काष्ठा file *filp)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	काष्ठा flock flock;
	दीर्घ err = -EINVAL;

	चयन (cmd) अणु
	हाल F_DUPFD:
		err = f_dupfd(arg, filp, 0);
		अवरोध;
	हाल F_DUPFD_CLOEXEC:
		err = f_dupfd(arg, filp, O_CLOEXEC);
		अवरोध;
	हाल F_GETFD:
		err = get_बंद_on_exec(fd) ? FD_CLOEXEC : 0;
		अवरोध;
	हाल F_SETFD:
		err = 0;
		set_बंद_on_exec(fd, arg & FD_CLOEXEC);
		अवरोध;
	हाल F_GETFL:
		err = filp->f_flags;
		अवरोध;
	हाल F_SETFL:
		err = setfl(fd, filp, arg);
		अवरोध;
#अगर BITS_PER_LONG != 32
	/* 32-bit arches must use fcntl64() */
	हाल F_OFD_GETLK:
#पूर्ण_अगर
	हाल F_GETLK:
		अगर (copy_from_user(&flock, argp, माप(flock)))
			वापस -EFAULT;
		err = fcntl_getlk(filp, cmd, &flock);
		अगर (!err && copy_to_user(argp, &flock, माप(flock)))
			वापस -EFAULT;
		अवरोध;
#अगर BITS_PER_LONG != 32
	/* 32-bit arches must use fcntl64() */
	हाल F_OFD_SETLK:
	हाल F_OFD_SETLKW:
#पूर्ण_अगर
		fallthrough;
	हाल F_SETLK:
	हाल F_SETLKW:
		अगर (copy_from_user(&flock, argp, माप(flock)))
			वापस -EFAULT;
		err = fcntl_setlk(fd, filp, cmd, &flock);
		अवरोध;
	हाल F_GETOWN:
		/*
		 * XXX If f_owner is a process group, the
		 * negative वापस value will get converted
		 * पूर्णांकo an error.  Oops.  If we keep the
		 * current syscall conventions, the only way
		 * to fix this will be in libc.
		 */
		err = f_getown(filp);
		क्रमce_successful_syscall_वापस();
		अवरोध;
	हाल F_SETOWN:
		err = f_setown(filp, arg, 1);
		अवरोध;
	हाल F_GETOWN_EX:
		err = f_getown_ex(filp, arg);
		अवरोध;
	हाल F_SETOWN_EX:
		err = f_setown_ex(filp, arg);
		अवरोध;
	हाल F_GETOWNER_UIDS:
		err = f_getowner_uids(filp, arg);
		अवरोध;
	हाल F_GETSIG:
		err = filp->f_owner.signum;
		अवरोध;
	हाल F_SETSIG:
		/* arg == 0 restores शेष behaviour. */
		अगर (!valid_संकेत(arg)) अणु
			अवरोध;
		पूर्ण
		err = 0;
		filp->f_owner.signum = arg;
		अवरोध;
	हाल F_GETLEASE:
		err = fcntl_getlease(filp);
		अवरोध;
	हाल F_SETLEASE:
		err = fcntl_setlease(fd, filp, arg);
		अवरोध;
	हाल F_NOTIFY:
		err = fcntl_dirnotअगरy(fd, filp, arg);
		अवरोध;
	हाल F_SETPIPE_SZ:
	हाल F_GETPIPE_SZ:
		err = pipe_fcntl(filp, cmd, arg);
		अवरोध;
	हाल F_ADD_SEALS:
	हाल F_GET_SEALS:
		err = memfd_fcntl(filp, cmd, arg);
		अवरोध;
	हाल F_GET_RW_HINT:
	हाल F_SET_RW_HINT:
	हाल F_GET_खाता_RW_HINT:
	हाल F_SET_खाता_RW_HINT:
		err = fcntl_rw_hपूर्णांक(filp, cmd, arg);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक check_fcntl_cmd(अचिन्हित cmd)
अणु
	चयन (cmd) अणु
	हाल F_DUPFD:
	हाल F_DUPFD_CLOEXEC:
	हाल F_GETFD:
	हाल F_SETFD:
	हाल F_GETFL:
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

SYSCALL_DEFINE3(fcntl, अचिन्हित पूर्णांक, fd, अचिन्हित पूर्णांक, cmd, अचिन्हित दीर्घ, arg)
अणु	
	काष्ठा fd f = fdget_raw(fd);
	दीर्घ err = -EBADF;

	अगर (!f.file)
		जाओ out;

	अगर (unlikely(f.file->f_mode & FMODE_PATH)) अणु
		अगर (!check_fcntl_cmd(cmd))
			जाओ out1;
	पूर्ण

	err = security_file_fcntl(f.file, cmd, arg);
	अगर (!err)
		err = करो_fcntl(fd, cmd, arg, f.file);

out1:
 	fdput(f);
out:
	वापस err;
पूर्ण

#अगर BITS_PER_LONG == 32
SYSCALL_DEFINE3(fcntl64, अचिन्हित पूर्णांक, fd, अचिन्हित पूर्णांक, cmd,
		अचिन्हित दीर्घ, arg)
अणु	
	व्योम __user *argp = (व्योम __user *)arg;
	काष्ठा fd f = fdget_raw(fd);
	काष्ठा flock64 flock;
	दीर्घ err = -EBADF;

	अगर (!f.file)
		जाओ out;

	अगर (unlikely(f.file->f_mode & FMODE_PATH)) अणु
		अगर (!check_fcntl_cmd(cmd))
			जाओ out1;
	पूर्ण

	err = security_file_fcntl(f.file, cmd, arg);
	अगर (err)
		जाओ out1;
	
	चयन (cmd) अणु
	हाल F_GETLK64:
	हाल F_OFD_GETLK:
		err = -EFAULT;
		अगर (copy_from_user(&flock, argp, माप(flock)))
			अवरोध;
		err = fcntl_getlk64(f.file, cmd, &flock);
		अगर (!err && copy_to_user(argp, &flock, माप(flock)))
			err = -EFAULT;
		अवरोध;
	हाल F_SETLK64:
	हाल F_SETLKW64:
	हाल F_OFD_SETLK:
	हाल F_OFD_SETLKW:
		err = -EFAULT;
		अगर (copy_from_user(&flock, argp, माप(flock)))
			अवरोध;
		err = fcntl_setlk64(fd, f.file, cmd, &flock);
		अवरोध;
	शेष:
		err = करो_fcntl(fd, cmd, arg, f.file);
		अवरोध;
	पूर्ण
out1:
	fdput(f);
out:
	वापस err;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_COMPAT
/* careful - करोn't use anywhere अन्यथा */
#घोषणा copy_flock_fields(dst, src)		\
	(dst)->l_type = (src)->l_type;		\
	(dst)->l_whence = (src)->l_whence;	\
	(dst)->l_start = (src)->l_start;	\
	(dst)->l_len = (src)->l_len;		\
	(dst)->l_pid = (src)->l_pid;

अटल पूर्णांक get_compat_flock(काष्ठा flock *kfl, स्थिर काष्ठा compat_flock __user *ufl)
अणु
	काष्ठा compat_flock fl;

	अगर (copy_from_user(&fl, ufl, माप(काष्ठा compat_flock)))
		वापस -EFAULT;
	copy_flock_fields(kfl, &fl);
	वापस 0;
पूर्ण

अटल पूर्णांक get_compat_flock64(काष्ठा flock *kfl, स्थिर काष्ठा compat_flock64 __user *ufl)
अणु
	काष्ठा compat_flock64 fl;

	अगर (copy_from_user(&fl, ufl, माप(काष्ठा compat_flock64)))
		वापस -EFAULT;
	copy_flock_fields(kfl, &fl);
	वापस 0;
पूर्ण

अटल पूर्णांक put_compat_flock(स्थिर काष्ठा flock *kfl, काष्ठा compat_flock __user *ufl)
अणु
	काष्ठा compat_flock fl;

	स_रखो(&fl, 0, माप(काष्ठा compat_flock));
	copy_flock_fields(&fl, kfl);
	अगर (copy_to_user(ufl, &fl, माप(काष्ठा compat_flock)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक put_compat_flock64(स्थिर काष्ठा flock *kfl, काष्ठा compat_flock64 __user *ufl)
अणु
	काष्ठा compat_flock64 fl;

	BUILD_BUG_ON(माप(kfl->l_start) > माप(ufl->l_start));
	BUILD_BUG_ON(माप(kfl->l_len) > माप(ufl->l_len));

	स_रखो(&fl, 0, माप(काष्ठा compat_flock64));
	copy_flock_fields(&fl, kfl);
	अगर (copy_to_user(ufl, &fl, माप(काष्ठा compat_flock64)))
		वापस -EFAULT;
	वापस 0;
पूर्ण
#अघोषित copy_flock_fields

अटल अचिन्हित पूर्णांक
convert_fcntl_cmd(अचिन्हित पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	हाल F_GETLK64:
		वापस F_GETLK;
	हाल F_SETLK64:
		वापस F_SETLK;
	हाल F_SETLKW64:
		वापस F_SETLKW;
	पूर्ण

	वापस cmd;
पूर्ण

/*
 * GETLK was successful and we need to वापस the data, but it needs to fit in
 * the compat काष्ठाure.
 * l_start shouldn't be too big, unless the original start + end is greater than
 * COMPAT_OFF_T_MAX, in which हाल the app was asking क्रम trouble, so we वापस
 * -EOVERFLOW in that हाल.  l_len could be too big, in which हाल we just
 * truncate it, and only allow the app to see that part of the conflicting lock
 * that might make sense to it anyway
 */
अटल पूर्णांक fixup_compat_flock(काष्ठा flock *flock)
अणु
	अगर (flock->l_start > COMPAT_OFF_T_MAX)
		वापस -EOVERFLOW;
	अगर (flock->l_len > COMPAT_OFF_T_MAX)
		flock->l_len = COMPAT_OFF_T_MAX;
	वापस 0;
पूर्ण

अटल दीर्घ करो_compat_fcntl64(अचिन्हित पूर्णांक fd, अचिन्हित पूर्णांक cmd,
			     compat_uदीर्घ_t arg)
अणु
	काष्ठा fd f = fdget_raw(fd);
	काष्ठा flock flock;
	दीर्घ err = -EBADF;

	अगर (!f.file)
		वापस err;

	अगर (unlikely(f.file->f_mode & FMODE_PATH)) अणु
		अगर (!check_fcntl_cmd(cmd))
			जाओ out_put;
	पूर्ण

	err = security_file_fcntl(f.file, cmd, arg);
	अगर (err)
		जाओ out_put;

	चयन (cmd) अणु
	हाल F_GETLK:
		err = get_compat_flock(&flock, compat_ptr(arg));
		अगर (err)
			अवरोध;
		err = fcntl_getlk(f.file, convert_fcntl_cmd(cmd), &flock);
		अगर (err)
			अवरोध;
		err = fixup_compat_flock(&flock);
		अगर (!err)
			err = put_compat_flock(&flock, compat_ptr(arg));
		अवरोध;
	हाल F_GETLK64:
	हाल F_OFD_GETLK:
		err = get_compat_flock64(&flock, compat_ptr(arg));
		अगर (err)
			अवरोध;
		err = fcntl_getlk(f.file, convert_fcntl_cmd(cmd), &flock);
		अगर (!err)
			err = put_compat_flock64(&flock, compat_ptr(arg));
		अवरोध;
	हाल F_SETLK:
	हाल F_SETLKW:
		err = get_compat_flock(&flock, compat_ptr(arg));
		अगर (err)
			अवरोध;
		err = fcntl_setlk(fd, f.file, convert_fcntl_cmd(cmd), &flock);
		अवरोध;
	हाल F_SETLK64:
	हाल F_SETLKW64:
	हाल F_OFD_SETLK:
	हाल F_OFD_SETLKW:
		err = get_compat_flock64(&flock, compat_ptr(arg));
		अगर (err)
			अवरोध;
		err = fcntl_setlk(fd, f.file, convert_fcntl_cmd(cmd), &flock);
		अवरोध;
	शेष:
		err = करो_fcntl(fd, cmd, arg, f.file);
		अवरोध;
	पूर्ण
out_put:
	fdput(f);
	वापस err;
पूर्ण

COMPAT_SYSCALL_DEFINE3(fcntl64, अचिन्हित पूर्णांक, fd, अचिन्हित पूर्णांक, cmd,
		       compat_uदीर्घ_t, arg)
अणु
	वापस करो_compat_fcntl64(fd, cmd, arg);
पूर्ण

COMPAT_SYSCALL_DEFINE3(fcntl, अचिन्हित पूर्णांक, fd, अचिन्हित पूर्णांक, cmd,
		       compat_uदीर्घ_t, arg)
अणु
	चयन (cmd) अणु
	हाल F_GETLK64:
	हाल F_SETLK64:
	हाल F_SETLKW64:
	हाल F_OFD_GETLK:
	हाल F_OFD_SETLK:
	हाल F_OFD_SETLKW:
		वापस -EINVAL;
	पूर्ण
	वापस करो_compat_fcntl64(fd, cmd, arg);
पूर्ण
#पूर्ण_अगर

/* Table to convert sigio संकेत codes पूर्णांकo poll band biपंचांगaps */

अटल स्थिर __poll_t band_table[NSIGPOLL] = अणु
	EPOLLIN | EPOLLRDNORM,			/* POLL_IN */
	EPOLLOUT | EPOLLWRNORM | EPOLLWRBAND,	/* POLL_OUT */
	EPOLLIN | EPOLLRDNORM | EPOLLMSG,		/* POLL_MSG */
	EPOLLERR,				/* POLL_ERR */
	EPOLLPRI | EPOLLRDBAND,			/* POLL_PRI */
	EPOLLHUP | EPOLLERR			/* POLL_HUP */
पूर्ण;

अटल अंतरभूत पूर्णांक sigio_perm(काष्ठा task_काष्ठा *p,
                             काष्ठा fown_काष्ठा *fown, पूर्णांक sig)
अणु
	स्थिर काष्ठा cred *cred;
	पूर्णांक ret;

	rcu_पढ़ो_lock();
	cred = __task_cred(p);
	ret = ((uid_eq(fown->euid, GLOBAL_ROOT_UID) ||
		uid_eq(fown->euid, cred->suid) || uid_eq(fown->euid, cred->uid) ||
		uid_eq(fown->uid,  cred->suid) || uid_eq(fown->uid,  cred->uid)) &&
	       !security_file_send_sigiotask(p, fown, sig));
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल व्योम send_sigio_to_task(काष्ठा task_काष्ठा *p,
			       काष्ठा fown_काष्ठा *fown,
			       पूर्णांक fd, पूर्णांक reason, क्रमागत pid_type type)
अणु
	/*
	 * F_SETSIG can change ->signum lockless in parallel, make
	 * sure we पढ़ो it once and use the same value throughout.
	 */
	पूर्णांक signum = READ_ONCE(fown->signum);

	अगर (!sigio_perm(p, fown, signum))
		वापस;

	चयन (signum) अणु
		शेष: अणु
			kernel_siginfo_t si;

			/* Queue a rt संकेत with the appropriate fd as its
			   value.  We use SI_SIGIO as the source, not 
			   SI_KERNEL, since kernel संकेतs always get 
			   delivered even अगर we can't queue.  Failure to
			   queue in this हाल _should_ be reported; we fall
			   back to SIGIO in that हाल. --sct */
			clear_siginfo(&si);
			si.si_signo = signum;
			si.si_त्रुटि_सं = 0;
		        si.si_code  = reason;
			/*
			 * Posix definies POLL_IN and मित्रs to be संकेत
			 * specअगरic si_codes क्रम SIG_POLL.  Linux extended
			 * these si_codes to other संकेतs in a way that is
			 * ambiguous अगर other संकेतs also have संकेत
			 * specअगरic si_codes.  In that हाल use SI_SIGIO instead
			 * to हटाओ the ambiguity.
			 */
			अगर ((signum != SIGPOLL) && sig_specअगरic_sicodes(signum))
				si.si_code = SI_SIGIO;

			/* Make sure we are called with one of the POLL_*
			   reasons, otherwise we could leak kernel stack पूर्णांकo
			   userspace.  */
			BUG_ON((reason < POLL_IN) || ((reason - POLL_IN) >= NSIGPOLL));
			अगर (reason - POLL_IN >= NSIGPOLL)
				si.si_band  = ~0L;
			अन्यथा
				si.si_band = mangle_poll(band_table[reason - POLL_IN]);
			si.si_fd    = fd;
			अगर (!करो_send_sig_info(signum, &si, p, type))
				अवरोध;
		पूर्ण
			fallthrough;	/* fall back on the old plain SIGIO संकेत */
		हाल 0:
			करो_send_sig_info(SIGIO, SEND_SIG_PRIV, p, type);
	पूर्ण
पूर्ण

व्योम send_sigio(काष्ठा fown_काष्ठा *fown, पूर्णांक fd, पूर्णांक band)
अणु
	काष्ठा task_काष्ठा *p;
	क्रमागत pid_type type;
	अचिन्हित दीर्घ flags;
	काष्ठा pid *pid;
	
	पढ़ो_lock_irqsave(&fown->lock, flags);

	type = fown->pid_type;
	pid = fown->pid;
	अगर (!pid)
		जाओ out_unlock_fown;

	अगर (type <= PIDTYPE_TGID) अणु
		rcu_पढ़ो_lock();
		p = pid_task(pid, PIDTYPE_PID);
		अगर (p)
			send_sigio_to_task(p, fown, fd, band, type);
		rcu_पढ़ो_unlock();
	पूर्ण अन्यथा अणु
		पढ़ो_lock(&tasklist_lock);
		करो_each_pid_task(pid, type, p) अणु
			send_sigio_to_task(p, fown, fd, band, type);
		पूर्ण जबतक_each_pid_task(pid, type, p);
		पढ़ो_unlock(&tasklist_lock);
	पूर्ण
 out_unlock_fown:
	पढ़ो_unlock_irqrestore(&fown->lock, flags);
पूर्ण

अटल व्योम send_sigurg_to_task(काष्ठा task_काष्ठा *p,
				काष्ठा fown_काष्ठा *fown, क्रमागत pid_type type)
अणु
	अगर (sigio_perm(p, fown, SIGURG))
		करो_send_sig_info(SIGURG, SEND_SIG_PRIV, p, type);
पूर्ण

पूर्णांक send_sigurg(काष्ठा fown_काष्ठा *fown)
अणु
	काष्ठा task_काष्ठा *p;
	क्रमागत pid_type type;
	काष्ठा pid *pid;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;
	
	पढ़ो_lock_irqsave(&fown->lock, flags);

	type = fown->pid_type;
	pid = fown->pid;
	अगर (!pid)
		जाओ out_unlock_fown;

	ret = 1;

	अगर (type <= PIDTYPE_TGID) अणु
		rcu_पढ़ो_lock();
		p = pid_task(pid, PIDTYPE_PID);
		अगर (p)
			send_sigurg_to_task(p, fown, type);
		rcu_पढ़ो_unlock();
	पूर्ण अन्यथा अणु
		पढ़ो_lock(&tasklist_lock);
		करो_each_pid_task(pid, type, p) अणु
			send_sigurg_to_task(p, fown, type);
		पूर्ण जबतक_each_pid_task(pid, type, p);
		पढ़ो_unlock(&tasklist_lock);
	पूर्ण
 out_unlock_fown:
	पढ़ो_unlock_irqrestore(&fown->lock, flags);
	वापस ret;
पूर्ण

अटल DEFINE_SPINLOCK(fasync_lock);
अटल काष्ठा kmem_cache *fasync_cache __पढ़ो_mostly;

अटल व्योम fasync_मुक्त_rcu(काष्ठा rcu_head *head)
अणु
	kmem_cache_मुक्त(fasync_cache,
			container_of(head, काष्ठा fasync_काष्ठा, fa_rcu));
पूर्ण

/*
 * Remove a fasync entry. If successfully हटाओd, वापस
 * positive and clear the FASYNC flag. If no entry exists,
 * करो nothing and वापस 0.
 *
 * NOTE! It is very important that the FASYNC flag always
 * match the state "is the filp on a fasync list".
 *
 */
पूर्णांक fasync_हटाओ_entry(काष्ठा file *filp, काष्ठा fasync_काष्ठा **fapp)
अणु
	काष्ठा fasync_काष्ठा *fa, **fp;
	पूर्णांक result = 0;

	spin_lock(&filp->f_lock);
	spin_lock(&fasync_lock);
	क्रम (fp = fapp; (fa = *fp) != शून्य; fp = &fa->fa_next) अणु
		अगर (fa->fa_file != filp)
			जारी;

		ग_लिखो_lock_irq(&fa->fa_lock);
		fa->fa_file = शून्य;
		ग_लिखो_unlock_irq(&fa->fa_lock);

		*fp = fa->fa_next;
		call_rcu(&fa->fa_rcu, fasync_मुक्त_rcu);
		filp->f_flags &= ~FASYNC;
		result = 1;
		अवरोध;
	पूर्ण
	spin_unlock(&fasync_lock);
	spin_unlock(&filp->f_lock);
	वापस result;
पूर्ण

काष्ठा fasync_काष्ठा *fasync_alloc(व्योम)
अणु
	वापस kmem_cache_alloc(fasync_cache, GFP_KERNEL);
पूर्ण

/*
 * NOTE! This can be used only क्रम unused fasync entries:
 * entries that actually got inserted on the fasync list
 * need to be released by rcu - see fasync_हटाओ_entry.
 */
व्योम fasync_मुक्त(काष्ठा fasync_काष्ठा *new)
अणु
	kmem_cache_मुक्त(fasync_cache, new);
पूर्ण

/*
 * Insert a new entry पूर्णांकo the fasync list.  Return the poपूर्णांकer to the
 * old one अगर we didn't use the new one.
 *
 * NOTE! It is very important that the FASYNC flag always
 * match the state "is the filp on a fasync list".
 */
काष्ठा fasync_काष्ठा *fasync_insert_entry(पूर्णांक fd, काष्ठा file *filp, काष्ठा fasync_काष्ठा **fapp, काष्ठा fasync_काष्ठा *new)
अणु
        काष्ठा fasync_काष्ठा *fa, **fp;

	spin_lock(&filp->f_lock);
	spin_lock(&fasync_lock);
	क्रम (fp = fapp; (fa = *fp) != शून्य; fp = &fa->fa_next) अणु
		अगर (fa->fa_file != filp)
			जारी;

		ग_लिखो_lock_irq(&fa->fa_lock);
		fa->fa_fd = fd;
		ग_लिखो_unlock_irq(&fa->fa_lock);
		जाओ out;
	पूर्ण

	rwlock_init(&new->fa_lock);
	new->magic = FASYNC_MAGIC;
	new->fa_file = filp;
	new->fa_fd = fd;
	new->fa_next = *fapp;
	rcu_assign_poपूर्णांकer(*fapp, new);
	filp->f_flags |= FASYNC;

out:
	spin_unlock(&fasync_lock);
	spin_unlock(&filp->f_lock);
	वापस fa;
पूर्ण

/*
 * Add a fasync entry. Return negative on error, positive अगर
 * added, and zero अगर did nothing but change an existing one.
 */
अटल पूर्णांक fasync_add_entry(पूर्णांक fd, काष्ठा file *filp, काष्ठा fasync_काष्ठा **fapp)
अणु
	काष्ठा fasync_काष्ठा *new;

	new = fasync_alloc();
	अगर (!new)
		वापस -ENOMEM;

	/*
	 * fasync_insert_entry() वापसs the old (update) entry अगर
	 * it existed.
	 *
	 * So मुक्त the (unused) new entry and वापस 0 to let the
	 * caller know that we didn't add any new fasync entries.
	 */
	अगर (fasync_insert_entry(fd, filp, fapp, new)) अणु
		fasync_मुक्त(new);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/*
 * fasync_helper() is used by almost all अक्षरacter device drivers
 * to set up the fasync queue, and क्रम regular files by the file
 * lease code. It वापसs negative on error, 0 अगर it did no changes
 * and positive अगर it added/deleted the entry.
 */
पूर्णांक fasync_helper(पूर्णांक fd, काष्ठा file * filp, पूर्णांक on, काष्ठा fasync_काष्ठा **fapp)
अणु
	अगर (!on)
		वापस fasync_हटाओ_entry(filp, fapp);
	वापस fasync_add_entry(fd, filp, fapp);
पूर्ण

EXPORT_SYMBOL(fasync_helper);

/*
 * rcu_पढ़ो_lock() is held
 */
अटल व्योम समाप्त_fasync_rcu(काष्ठा fasync_काष्ठा *fa, पूर्णांक sig, पूर्णांक band)
अणु
	जबतक (fa) अणु
		काष्ठा fown_काष्ठा *fown;

		अगर (fa->magic != FASYNC_MAGIC) अणु
			prपूर्णांकk(KERN_ERR "kill_fasync: bad magic number in "
			       "fasync_struct!\n");
			वापस;
		पूर्ण
		पढ़ो_lock(&fa->fa_lock);
		अगर (fa->fa_file) अणु
			fown = &fa->fa_file->f_owner;
			/* Don't send SIGURG to processes which have not set a
			   queued signum: SIGURG has its own शेष संकेतling
			   mechanism. */
			अगर (!(sig == SIGURG && fown->signum == 0))
				send_sigio(fown, fa->fa_fd, band);
		पूर्ण
		पढ़ो_unlock(&fa->fa_lock);
		fa = rcu_dereference(fa->fa_next);
	पूर्ण
पूर्ण

व्योम समाप्त_fasync(काष्ठा fasync_काष्ठा **fp, पूर्णांक sig, पूर्णांक band)
अणु
	/* First a quick test without locking: usually
	 * the list is empty.
	 */
	अगर (*fp) अणु
		rcu_पढ़ो_lock();
		समाप्त_fasync_rcu(rcu_dereference(*fp), sig, band);
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण
EXPORT_SYMBOL(समाप्त_fasync);

अटल पूर्णांक __init fcntl_init(व्योम)
अणु
	/*
	 * Please add new bits here to ensure allocation uniqueness.
	 * Exceptions: O_NONBLOCK is a two bit define on parisc; O_NDELAY
	 * is defined as O_NONBLOCK on some platक्रमms and not on others.
	 */
	BUILD_BUG_ON(21 - 1 /* क्रम O_RDONLY being 0 */ !=
		HWEIGHT32(
			(VALID_OPEN_FLAGS & ~(O_NONBLOCK | O_NDELAY)) |
			__FMODE_EXEC | __FMODE_NONOTIFY));

	fasync_cache = kmem_cache_create("fasync_cache",
		माप(काष्ठा fasync_काष्ठा), 0, SLAB_PANIC, शून्य);
	वापस 0;
पूर्ण

module_init(fcntl_init)
