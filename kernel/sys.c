<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/kernel/sys.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */

#समावेश <linux/export.h>
#समावेश <linux/mm.h>
#समावेश <linux/utsname.h>
#समावेश <linux/mman.h>
#समावेश <linux/reboot.h>
#समावेश <linux/prctl.h>
#समावेश <linux/highuid.h>
#समावेश <linux/fs.h>
#समावेश <linux/kmod.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/resource.h>
#समावेश <linux/kernel.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/capability.h>
#समावेश <linux/device.h>
#समावेश <linux/key.h>
#समावेश <linux/बार.h>
#समावेश <linux/posix-समयrs.h>
#समावेश <linux/security.h>
#समावेश <linux/suspend.h>
#समावेश <linux/tty.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/cn_proc.h>
#समावेश <linux/अ_लोpu.h>
#समावेश <linux/task_io_accounting_ops.h>
#समावेश <linux/seccomp.h>
#समावेश <linux/cpu.h>
#समावेश <linux/personality.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/fs_काष्ठा.h>
#समावेश <linux/file.h>
#समावेश <linux/mount.h>
#समावेश <linux/gfp.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/version.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/syscall_user_dispatch.h>

#समावेश <linux/compat.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/user_namespace.h>
#समावेश <linux/समय_namespace.h>
#समावेश <linux/binfmts.h>

#समावेश <linux/sched.h>
#समावेश <linux/sched/स्वतःgroup.h>
#समावेश <linux/sched/loadavg.h>
#समावेश <linux/sched/स्थिति.स>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/coredump.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/cpuसमय.स>
#समावेश <linux/rcupdate.h>
#समावेश <linux/uidgid.h>
#समावेश <linux/cred.h>

#समावेश <linux/nospec.h>

#समावेश <linux/kmsg_dump.h>
/* Move somewhere अन्यथा to aव्योम recompiling? */
#समावेश <generated/utsrelease.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/unistd.h>

#समावेश "uid16.h"

#अगर_अघोषित SET_UNALIGN_CTL
# define SET_UNALIGN_CTL(a, b)	(-EINVAL)
#पूर्ण_अगर
#अगर_अघोषित GET_UNALIGN_CTL
# define GET_UNALIGN_CTL(a, b)	(-EINVAL)
#पूर्ण_अगर
#अगर_अघोषित SET_FPEMU_CTL
# define SET_FPEMU_CTL(a, b)	(-EINVAL)
#पूर्ण_अगर
#अगर_अघोषित GET_FPEMU_CTL
# define GET_FPEMU_CTL(a, b)	(-EINVAL)
#पूर्ण_अगर
#अगर_अघोषित SET_FPEXC_CTL
# define SET_FPEXC_CTL(a, b)	(-EINVAL)
#पूर्ण_अगर
#अगर_अघोषित GET_FPEXC_CTL
# define GET_FPEXC_CTL(a, b)	(-EINVAL)
#पूर्ण_अगर
#अगर_अघोषित GET_ENDIAN
# define GET_ENDIAN(a, b)	(-EINVAL)
#पूर्ण_अगर
#अगर_अघोषित SET_ENDIAN
# define SET_ENDIAN(a, b)	(-EINVAL)
#पूर्ण_अगर
#अगर_अघोषित GET_TSC_CTL
# define GET_TSC_CTL(a)		(-EINVAL)
#पूर्ण_अगर
#अगर_अघोषित SET_TSC_CTL
# define SET_TSC_CTL(a)		(-EINVAL)
#पूर्ण_अगर
#अगर_अघोषित GET_FP_MODE
# define GET_FP_MODE(a)		(-EINVAL)
#पूर्ण_अगर
#अगर_अघोषित SET_FP_MODE
# define SET_FP_MODE(a,b)	(-EINVAL)
#पूर्ण_अगर
#अगर_अघोषित SVE_SET_VL
# define SVE_SET_VL(a)		(-EINVAL)
#पूर्ण_अगर
#अगर_अघोषित SVE_GET_VL
# define SVE_GET_VL()		(-EINVAL)
#पूर्ण_अगर
#अगर_अघोषित PAC_RESET_KEYS
# define PAC_RESET_KEYS(a, b)	(-EINVAL)
#पूर्ण_अगर
#अगर_अघोषित PAC_SET_ENABLED_KEYS
# define PAC_SET_ENABLED_KEYS(a, b, c)	(-EINVAL)
#पूर्ण_अगर
#अगर_अघोषित PAC_GET_ENABLED_KEYS
# define PAC_GET_ENABLED_KEYS(a)	(-EINVAL)
#पूर्ण_अगर
#अगर_अघोषित SET_TAGGED_ADDR_CTRL
# define SET_TAGGED_ADDR_CTRL(a)	(-EINVAL)
#पूर्ण_अगर
#अगर_अघोषित GET_TAGGED_ADDR_CTRL
# define GET_TAGGED_ADDR_CTRL()		(-EINVAL)
#पूर्ण_अगर

/*
 * this is where the प्रणाली-wide overflow UID and GID are defined, क्रम
 * architectures that now have 32-bit UID/GID but didn't in the past
 */

पूर्णांक overflowuid = DEFAULT_OVERFLOWUID;
पूर्णांक overflowgid = DEFAULT_OVERFLOWGID;

EXPORT_SYMBOL(overflowuid);
EXPORT_SYMBOL(overflowgid);

/*
 * the same as above, but क्रम fileप्रणालीs which can only store a 16-bit
 * UID and GID. as such, this is needed on all architectures
 */

पूर्णांक fs_overflowuid = DEFAULT_FS_OVERFLOWUID;
पूर्णांक fs_overflowgid = DEFAULT_FS_OVERFLOWGID;

EXPORT_SYMBOL(fs_overflowuid);
EXPORT_SYMBOL(fs_overflowgid);

/*
 * Returns true अगर current's euid is same as p's uid or euid,
 * or has CAP_SYS_NICE to p's user_ns.
 *
 * Called with rcu_पढ़ो_lock, creds are safe
 */
अटल bool set_one_prio_perm(काष्ठा task_काष्ठा *p)
अणु
	स्थिर काष्ठा cred *cred = current_cred(), *pcred = __task_cred(p);

	अगर (uid_eq(pcred->uid,  cred->euid) ||
	    uid_eq(pcred->euid, cred->euid))
		वापस true;
	अगर (ns_capable(pcred->user_ns, CAP_SYS_NICE))
		वापस true;
	वापस false;
पूर्ण

/*
 * set the priority of a task
 * - the caller must hold the RCU पढ़ो lock
 */
अटल पूर्णांक set_one_prio(काष्ठा task_काष्ठा *p, पूर्णांक niceval, पूर्णांक error)
अणु
	पूर्णांक no_nice;

	अगर (!set_one_prio_perm(p)) अणु
		error = -EPERM;
		जाओ out;
	पूर्ण
	अगर (niceval < task_nice(p) && !can_nice(p, niceval)) अणु
		error = -EACCES;
		जाओ out;
	पूर्ण
	no_nice = security_task_setnice(p, niceval);
	अगर (no_nice) अणु
		error = no_nice;
		जाओ out;
	पूर्ण
	अगर (error == -ESRCH)
		error = 0;
	set_user_nice(p, niceval);
out:
	वापस error;
पूर्ण

SYSCALL_DEFINE3(setpriority, पूर्णांक, which, पूर्णांक, who, पूर्णांक, niceval)
अणु
	काष्ठा task_काष्ठा *g, *p;
	काष्ठा user_काष्ठा *user;
	स्थिर काष्ठा cred *cred = current_cred();
	पूर्णांक error = -EINVAL;
	काष्ठा pid *pgrp;
	kuid_t uid;

	अगर (which > PRIO_USER || which < PRIO_PROCESS)
		जाओ out;

	/* normalize: aव्योम चिन्हित भागision (rounding problems) */
	error = -ESRCH;
	अगर (niceval < MIN_NICE)
		niceval = MIN_NICE;
	अगर (niceval > MAX_NICE)
		niceval = MAX_NICE;

	rcu_पढ़ो_lock();
	पढ़ो_lock(&tasklist_lock);
	चयन (which) अणु
	हाल PRIO_PROCESS:
		अगर (who)
			p = find_task_by_vpid(who);
		अन्यथा
			p = current;
		अगर (p)
			error = set_one_prio(p, niceval, error);
		अवरोध;
	हाल PRIO_PGRP:
		अगर (who)
			pgrp = find_vpid(who);
		अन्यथा
			pgrp = task_pgrp(current);
		करो_each_pid_thपढ़ो(pgrp, PIDTYPE_PGID, p) अणु
			error = set_one_prio(p, niceval, error);
		पूर्ण जबतक_each_pid_thपढ़ो(pgrp, PIDTYPE_PGID, p);
		अवरोध;
	हाल PRIO_USER:
		uid = make_kuid(cred->user_ns, who);
		user = cred->user;
		अगर (!who)
			uid = cred->uid;
		अन्यथा अगर (!uid_eq(uid, cred->uid)) अणु
			user = find_user(uid);
			अगर (!user)
				जाओ out_unlock;	/* No processes क्रम this user */
		पूर्ण
		करो_each_thपढ़ो(g, p) अणु
			अगर (uid_eq(task_uid(p), uid) && task_pid_vnr(p))
				error = set_one_prio(p, niceval, error);
		पूर्ण जबतक_each_thपढ़ो(g, p);
		अगर (!uid_eq(uid, cred->uid))
			मुक्त_uid(user);		/* For find_user() */
		अवरोध;
	पूर्ण
out_unlock:
	पढ़ो_unlock(&tasklist_lock);
	rcu_पढ़ो_unlock();
out:
	वापस error;
पूर्ण

/*
 * Ugh. To aव्योम negative वापस values, "getpriority()" will
 * not वापस the normal nice-value, but a negated value that
 * has been offset by 20 (ie it वापसs 40..1 instead of -20..19)
 * to stay compatible.
 */
SYSCALL_DEFINE2(getpriority, पूर्णांक, which, पूर्णांक, who)
अणु
	काष्ठा task_काष्ठा *g, *p;
	काष्ठा user_काष्ठा *user;
	स्थिर काष्ठा cred *cred = current_cred();
	दीर्घ niceval, retval = -ESRCH;
	काष्ठा pid *pgrp;
	kuid_t uid;

	अगर (which > PRIO_USER || which < PRIO_PROCESS)
		वापस -EINVAL;

	rcu_पढ़ो_lock();
	पढ़ो_lock(&tasklist_lock);
	चयन (which) अणु
	हाल PRIO_PROCESS:
		अगर (who)
			p = find_task_by_vpid(who);
		अन्यथा
			p = current;
		अगर (p) अणु
			niceval = nice_to_rlimit(task_nice(p));
			अगर (niceval > retval)
				retval = niceval;
		पूर्ण
		अवरोध;
	हाल PRIO_PGRP:
		अगर (who)
			pgrp = find_vpid(who);
		अन्यथा
			pgrp = task_pgrp(current);
		करो_each_pid_thपढ़ो(pgrp, PIDTYPE_PGID, p) अणु
			niceval = nice_to_rlimit(task_nice(p));
			अगर (niceval > retval)
				retval = niceval;
		पूर्ण जबतक_each_pid_thपढ़ो(pgrp, PIDTYPE_PGID, p);
		अवरोध;
	हाल PRIO_USER:
		uid = make_kuid(cred->user_ns, who);
		user = cred->user;
		अगर (!who)
			uid = cred->uid;
		अन्यथा अगर (!uid_eq(uid, cred->uid)) अणु
			user = find_user(uid);
			अगर (!user)
				जाओ out_unlock;	/* No processes क्रम this user */
		पूर्ण
		करो_each_thपढ़ो(g, p) अणु
			अगर (uid_eq(task_uid(p), uid) && task_pid_vnr(p)) अणु
				niceval = nice_to_rlimit(task_nice(p));
				अगर (niceval > retval)
					retval = niceval;
			पूर्ण
		पूर्ण जबतक_each_thपढ़ो(g, p);
		अगर (!uid_eq(uid, cred->uid))
			मुक्त_uid(user);		/* क्रम find_user() */
		अवरोध;
	पूर्ण
out_unlock:
	पढ़ो_unlock(&tasklist_lock);
	rcu_पढ़ो_unlock();

	वापस retval;
पूर्ण

/*
 * Unprivileged users may change the real gid to the effective gid
 * or vice versa.  (BSD-style)
 *
 * If you set the real gid at all, or set the effective gid to a value not
 * equal to the real gid, then the saved gid is set to the new effective gid.
 *
 * This makes it possible क्रम a setgid program to completely drop its
 * privileges, which is often a useful निश्चितion to make when you are करोing
 * a security audit over a program.
 *
 * The general idea is that a program which uses just setregid() will be
 * 100% compatible with BSD.  A program which uses just setgid() will be
 * 100% compatible with POSIX with saved IDs.
 *
 * SMP: There are not races, the GIDs are checked only by fileप्रणाली
 *      operations (as far as semantic preservation is concerned).
 */
#अगर_घोषित CONFIG_MULTIUSER
दीर्घ __sys_setregid(gid_t rgid, gid_t egid)
अणु
	काष्ठा user_namespace *ns = current_user_ns();
	स्थिर काष्ठा cred *old;
	काष्ठा cred *new;
	पूर्णांक retval;
	kgid_t krgid, kegid;

	krgid = make_kgid(ns, rgid);
	kegid = make_kgid(ns, egid);

	अगर ((rgid != (gid_t) -1) && !gid_valid(krgid))
		वापस -EINVAL;
	अगर ((egid != (gid_t) -1) && !gid_valid(kegid))
		वापस -EINVAL;

	new = prepare_creds();
	अगर (!new)
		वापस -ENOMEM;
	old = current_cred();

	retval = -EPERM;
	अगर (rgid != (gid_t) -1) अणु
		अगर (gid_eq(old->gid, krgid) ||
		    gid_eq(old->egid, krgid) ||
		    ns_capable_setid(old->user_ns, CAP_SETGID))
			new->gid = krgid;
		अन्यथा
			जाओ error;
	पूर्ण
	अगर (egid != (gid_t) -1) अणु
		अगर (gid_eq(old->gid, kegid) ||
		    gid_eq(old->egid, kegid) ||
		    gid_eq(old->sgid, kegid) ||
		    ns_capable_setid(old->user_ns, CAP_SETGID))
			new->egid = kegid;
		अन्यथा
			जाओ error;
	पूर्ण

	अगर (rgid != (gid_t) -1 ||
	    (egid != (gid_t) -1 && !gid_eq(kegid, old->gid)))
		new->sgid = new->egid;
	new->fsgid = new->egid;

	retval = security_task_fix_setgid(new, old, LSM_SETID_RE);
	अगर (retval < 0)
		जाओ error;

	वापस commit_creds(new);

error:
	पात_creds(new);
	वापस retval;
पूर्ण

SYSCALL_DEFINE2(setregid, gid_t, rgid, gid_t, egid)
अणु
	वापस __sys_setregid(rgid, egid);
पूर्ण

/*
 * setgid() is implemented like SysV w/ SAVED_IDS
 *
 * SMP: Same implicit races as above.
 */
दीर्घ __sys_setgid(gid_t gid)
अणु
	काष्ठा user_namespace *ns = current_user_ns();
	स्थिर काष्ठा cred *old;
	काष्ठा cred *new;
	पूर्णांक retval;
	kgid_t kgid;

	kgid = make_kgid(ns, gid);
	अगर (!gid_valid(kgid))
		वापस -EINVAL;

	new = prepare_creds();
	अगर (!new)
		वापस -ENOMEM;
	old = current_cred();

	retval = -EPERM;
	अगर (ns_capable_setid(old->user_ns, CAP_SETGID))
		new->gid = new->egid = new->sgid = new->fsgid = kgid;
	अन्यथा अगर (gid_eq(kgid, old->gid) || gid_eq(kgid, old->sgid))
		new->egid = new->fsgid = kgid;
	अन्यथा
		जाओ error;

	retval = security_task_fix_setgid(new, old, LSM_SETID_ID);
	अगर (retval < 0)
		जाओ error;

	वापस commit_creds(new);

error:
	पात_creds(new);
	वापस retval;
पूर्ण

SYSCALL_DEFINE1(setgid, gid_t, gid)
अणु
	वापस __sys_setgid(gid);
पूर्ण

/*
 * change the user काष्ठा in a credentials set to match the new UID
 */
अटल पूर्णांक set_user(काष्ठा cred *new)
अणु
	काष्ठा user_काष्ठा *new_user;

	new_user = alloc_uid(new->uid);
	अगर (!new_user)
		वापस -EAGAIN;

	/*
	 * We करोn't fail in हाल of NPROC limit excess here because too many
	 * poorly written programs करोn't check set*uid() वापस code, assuming
	 * it never fails अगर called by root.  We may still enक्रमce NPROC limit
	 * क्रम programs करोing set*uid()+execve() by harmlessly deferring the
	 * failure to the execve() stage.
	 */
	अगर (atomic_पढ़ो(&new_user->processes) >= rlimit(RLIMIT_NPROC) &&
			new_user != INIT_USER)
		current->flags |= PF_NPROC_EXCEEDED;
	अन्यथा
		current->flags &= ~PF_NPROC_EXCEEDED;

	मुक्त_uid(new->user);
	new->user = new_user;
	वापस 0;
पूर्ण

/*
 * Unprivileged users may change the real uid to the effective uid
 * or vice versa.  (BSD-style)
 *
 * If you set the real uid at all, or set the effective uid to a value not
 * equal to the real uid, then the saved uid is set to the new effective uid.
 *
 * This makes it possible क्रम a setuid program to completely drop its
 * privileges, which is often a useful निश्चितion to make when you are करोing
 * a security audit over a program.
 *
 * The general idea is that a program which uses just setreuid() will be
 * 100% compatible with BSD.  A program which uses just setuid() will be
 * 100% compatible with POSIX with saved IDs.
 */
दीर्घ __sys_setreuid(uid_t ruid, uid_t euid)
अणु
	काष्ठा user_namespace *ns = current_user_ns();
	स्थिर काष्ठा cred *old;
	काष्ठा cred *new;
	पूर्णांक retval;
	kuid_t kruid, keuid;

	kruid = make_kuid(ns, ruid);
	keuid = make_kuid(ns, euid);

	अगर ((ruid != (uid_t) -1) && !uid_valid(kruid))
		वापस -EINVAL;
	अगर ((euid != (uid_t) -1) && !uid_valid(keuid))
		वापस -EINVAL;

	new = prepare_creds();
	अगर (!new)
		वापस -ENOMEM;
	old = current_cred();

	retval = -EPERM;
	अगर (ruid != (uid_t) -1) अणु
		new->uid = kruid;
		अगर (!uid_eq(old->uid, kruid) &&
		    !uid_eq(old->euid, kruid) &&
		    !ns_capable_setid(old->user_ns, CAP_SETUID))
			जाओ error;
	पूर्ण

	अगर (euid != (uid_t) -1) अणु
		new->euid = keuid;
		अगर (!uid_eq(old->uid, keuid) &&
		    !uid_eq(old->euid, keuid) &&
		    !uid_eq(old->suid, keuid) &&
		    !ns_capable_setid(old->user_ns, CAP_SETUID))
			जाओ error;
	पूर्ण

	अगर (!uid_eq(new->uid, old->uid)) अणु
		retval = set_user(new);
		अगर (retval < 0)
			जाओ error;
	पूर्ण
	अगर (ruid != (uid_t) -1 ||
	    (euid != (uid_t) -1 && !uid_eq(keuid, old->uid)))
		new->suid = new->euid;
	new->fsuid = new->euid;

	retval = security_task_fix_setuid(new, old, LSM_SETID_RE);
	अगर (retval < 0)
		जाओ error;

	वापस commit_creds(new);

error:
	पात_creds(new);
	वापस retval;
पूर्ण

SYSCALL_DEFINE2(setreuid, uid_t, ruid, uid_t, euid)
अणु
	वापस __sys_setreuid(ruid, euid);
पूर्ण

/*
 * setuid() is implemented like SysV with SAVED_IDS
 *
 * Note that SAVED_ID's is deficient in that a setuid root program
 * like sendmail, क्रम example, cannot set its uid to be a normal
 * user and then चयन back, because अगर you're root, setuid() sets
 * the saved uid too.  If you करोn't like this, blame the bright people
 * in the POSIX committee and/or USG.  Note that the BSD-style setreuid()
 * will allow a root program to temporarily drop privileges and be able to
 * regain them by swapping the real and effective uid.
 */
दीर्घ __sys_setuid(uid_t uid)
अणु
	काष्ठा user_namespace *ns = current_user_ns();
	स्थिर काष्ठा cred *old;
	काष्ठा cred *new;
	पूर्णांक retval;
	kuid_t kuid;

	kuid = make_kuid(ns, uid);
	अगर (!uid_valid(kuid))
		वापस -EINVAL;

	new = prepare_creds();
	अगर (!new)
		वापस -ENOMEM;
	old = current_cred();

	retval = -EPERM;
	अगर (ns_capable_setid(old->user_ns, CAP_SETUID)) अणु
		new->suid = new->uid = kuid;
		अगर (!uid_eq(kuid, old->uid)) अणु
			retval = set_user(new);
			अगर (retval < 0)
				जाओ error;
		पूर्ण
	पूर्ण अन्यथा अगर (!uid_eq(kuid, old->uid) && !uid_eq(kuid, new->suid)) अणु
		जाओ error;
	पूर्ण

	new->fsuid = new->euid = kuid;

	retval = security_task_fix_setuid(new, old, LSM_SETID_ID);
	अगर (retval < 0)
		जाओ error;

	वापस commit_creds(new);

error:
	पात_creds(new);
	वापस retval;
पूर्ण

SYSCALL_DEFINE1(setuid, uid_t, uid)
अणु
	वापस __sys_setuid(uid);
पूर्ण


/*
 * This function implements a generic ability to update ruid, euid,
 * and suid.  This allows you to implement the 4.4 compatible seteuid().
 */
दीर्घ __sys_setresuid(uid_t ruid, uid_t euid, uid_t suid)
अणु
	काष्ठा user_namespace *ns = current_user_ns();
	स्थिर काष्ठा cred *old;
	काष्ठा cred *new;
	पूर्णांक retval;
	kuid_t kruid, keuid, ksuid;

	kruid = make_kuid(ns, ruid);
	keuid = make_kuid(ns, euid);
	ksuid = make_kuid(ns, suid);

	अगर ((ruid != (uid_t) -1) && !uid_valid(kruid))
		वापस -EINVAL;

	अगर ((euid != (uid_t) -1) && !uid_valid(keuid))
		वापस -EINVAL;

	अगर ((suid != (uid_t) -1) && !uid_valid(ksuid))
		वापस -EINVAL;

	new = prepare_creds();
	अगर (!new)
		वापस -ENOMEM;

	old = current_cred();

	retval = -EPERM;
	अगर (!ns_capable_setid(old->user_ns, CAP_SETUID)) अणु
		अगर (ruid != (uid_t) -1        && !uid_eq(kruid, old->uid) &&
		    !uid_eq(kruid, old->euid) && !uid_eq(kruid, old->suid))
			जाओ error;
		अगर (euid != (uid_t) -1        && !uid_eq(keuid, old->uid) &&
		    !uid_eq(keuid, old->euid) && !uid_eq(keuid, old->suid))
			जाओ error;
		अगर (suid != (uid_t) -1        && !uid_eq(ksuid, old->uid) &&
		    !uid_eq(ksuid, old->euid) && !uid_eq(ksuid, old->suid))
			जाओ error;
	पूर्ण

	अगर (ruid != (uid_t) -1) अणु
		new->uid = kruid;
		अगर (!uid_eq(kruid, old->uid)) अणु
			retval = set_user(new);
			अगर (retval < 0)
				जाओ error;
		पूर्ण
	पूर्ण
	अगर (euid != (uid_t) -1)
		new->euid = keuid;
	अगर (suid != (uid_t) -1)
		new->suid = ksuid;
	new->fsuid = new->euid;

	retval = security_task_fix_setuid(new, old, LSM_SETID_RES);
	अगर (retval < 0)
		जाओ error;

	वापस commit_creds(new);

error:
	पात_creds(new);
	वापस retval;
पूर्ण

SYSCALL_DEFINE3(setresuid, uid_t, ruid, uid_t, euid, uid_t, suid)
अणु
	वापस __sys_setresuid(ruid, euid, suid);
पूर्ण

SYSCALL_DEFINE3(getresuid, uid_t __user *, ruidp, uid_t __user *, euidp, uid_t __user *, suidp)
अणु
	स्थिर काष्ठा cred *cred = current_cred();
	पूर्णांक retval;
	uid_t ruid, euid, suid;

	ruid = from_kuid_munged(cred->user_ns, cred->uid);
	euid = from_kuid_munged(cred->user_ns, cred->euid);
	suid = from_kuid_munged(cred->user_ns, cred->suid);

	retval = put_user(ruid, ruidp);
	अगर (!retval) अणु
		retval = put_user(euid, euidp);
		अगर (!retval)
			वापस put_user(suid, suidp);
	पूर्ण
	वापस retval;
पूर्ण

/*
 * Same as above, but क्रम rgid, egid, sgid.
 */
दीर्घ __sys_setresgid(gid_t rgid, gid_t egid, gid_t sgid)
अणु
	काष्ठा user_namespace *ns = current_user_ns();
	स्थिर काष्ठा cred *old;
	काष्ठा cred *new;
	पूर्णांक retval;
	kgid_t krgid, kegid, ksgid;

	krgid = make_kgid(ns, rgid);
	kegid = make_kgid(ns, egid);
	ksgid = make_kgid(ns, sgid);

	अगर ((rgid != (gid_t) -1) && !gid_valid(krgid))
		वापस -EINVAL;
	अगर ((egid != (gid_t) -1) && !gid_valid(kegid))
		वापस -EINVAL;
	अगर ((sgid != (gid_t) -1) && !gid_valid(ksgid))
		वापस -EINVAL;

	new = prepare_creds();
	अगर (!new)
		वापस -ENOMEM;
	old = current_cred();

	retval = -EPERM;
	अगर (!ns_capable_setid(old->user_ns, CAP_SETGID)) अणु
		अगर (rgid != (gid_t) -1        && !gid_eq(krgid, old->gid) &&
		    !gid_eq(krgid, old->egid) && !gid_eq(krgid, old->sgid))
			जाओ error;
		अगर (egid != (gid_t) -1        && !gid_eq(kegid, old->gid) &&
		    !gid_eq(kegid, old->egid) && !gid_eq(kegid, old->sgid))
			जाओ error;
		अगर (sgid != (gid_t) -1        && !gid_eq(ksgid, old->gid) &&
		    !gid_eq(ksgid, old->egid) && !gid_eq(ksgid, old->sgid))
			जाओ error;
	पूर्ण

	अगर (rgid != (gid_t) -1)
		new->gid = krgid;
	अगर (egid != (gid_t) -1)
		new->egid = kegid;
	अगर (sgid != (gid_t) -1)
		new->sgid = ksgid;
	new->fsgid = new->egid;

	retval = security_task_fix_setgid(new, old, LSM_SETID_RES);
	अगर (retval < 0)
		जाओ error;

	वापस commit_creds(new);

error:
	पात_creds(new);
	वापस retval;
पूर्ण

SYSCALL_DEFINE3(setresgid, gid_t, rgid, gid_t, egid, gid_t, sgid)
अणु
	वापस __sys_setresgid(rgid, egid, sgid);
पूर्ण

SYSCALL_DEFINE3(getresgid, gid_t __user *, rgidp, gid_t __user *, egidp, gid_t __user *, sgidp)
अणु
	स्थिर काष्ठा cred *cred = current_cred();
	पूर्णांक retval;
	gid_t rgid, egid, sgid;

	rgid = from_kgid_munged(cred->user_ns, cred->gid);
	egid = from_kgid_munged(cred->user_ns, cred->egid);
	sgid = from_kgid_munged(cred->user_ns, cred->sgid);

	retval = put_user(rgid, rgidp);
	अगर (!retval) अणु
		retval = put_user(egid, egidp);
		अगर (!retval)
			retval = put_user(sgid, sgidp);
	पूर्ण

	वापस retval;
पूर्ण


/*
 * "setfsuid()" sets the fsuid - the uid used क्रम fileप्रणाली checks. This
 * is used क्रम "access()" and क्रम the NFS daemon (letting nfsd stay at
 * whatever uid it wants to). It normally shaकरोws "euid", except when
 * explicitly set by setfsuid() or क्रम access..
 */
दीर्घ __sys_setfsuid(uid_t uid)
अणु
	स्थिर काष्ठा cred *old;
	काष्ठा cred *new;
	uid_t old_fsuid;
	kuid_t kuid;

	old = current_cred();
	old_fsuid = from_kuid_munged(old->user_ns, old->fsuid);

	kuid = make_kuid(old->user_ns, uid);
	अगर (!uid_valid(kuid))
		वापस old_fsuid;

	new = prepare_creds();
	अगर (!new)
		वापस old_fsuid;

	अगर (uid_eq(kuid, old->uid)  || uid_eq(kuid, old->euid)  ||
	    uid_eq(kuid, old->suid) || uid_eq(kuid, old->fsuid) ||
	    ns_capable_setid(old->user_ns, CAP_SETUID)) अणु
		अगर (!uid_eq(kuid, old->fsuid)) अणु
			new->fsuid = kuid;
			अगर (security_task_fix_setuid(new, old, LSM_SETID_FS) == 0)
				जाओ change_okay;
		पूर्ण
	पूर्ण

	पात_creds(new);
	वापस old_fsuid;

change_okay:
	commit_creds(new);
	वापस old_fsuid;
पूर्ण

SYSCALL_DEFINE1(setfsuid, uid_t, uid)
अणु
	वापस __sys_setfsuid(uid);
पूर्ण

/*
 * Samma pथआ svenska..
 */
दीर्घ __sys_setfsgid(gid_t gid)
अणु
	स्थिर काष्ठा cred *old;
	काष्ठा cred *new;
	gid_t old_fsgid;
	kgid_t kgid;

	old = current_cred();
	old_fsgid = from_kgid_munged(old->user_ns, old->fsgid);

	kgid = make_kgid(old->user_ns, gid);
	अगर (!gid_valid(kgid))
		वापस old_fsgid;

	new = prepare_creds();
	अगर (!new)
		वापस old_fsgid;

	अगर (gid_eq(kgid, old->gid)  || gid_eq(kgid, old->egid)  ||
	    gid_eq(kgid, old->sgid) || gid_eq(kgid, old->fsgid) ||
	    ns_capable_setid(old->user_ns, CAP_SETGID)) अणु
		अगर (!gid_eq(kgid, old->fsgid)) अणु
			new->fsgid = kgid;
			अगर (security_task_fix_setgid(new,old,LSM_SETID_FS) == 0)
				जाओ change_okay;
		पूर्ण
	पूर्ण

	पात_creds(new);
	वापस old_fsgid;

change_okay:
	commit_creds(new);
	वापस old_fsgid;
पूर्ण

SYSCALL_DEFINE1(setfsgid, gid_t, gid)
अणु
	वापस __sys_setfsgid(gid);
पूर्ण
#पूर्ण_अगर /* CONFIG_MULTIUSER */

/**
 * sys_getpid - वापस the thपढ़ो group id of the current process
 *
 * Note, despite the name, this वापसs the tgid not the pid.  The tgid and
 * the pid are identical unless CLONE_THREAD was specअगरied on clone() in
 * which हाल the tgid is the same in all thपढ़ोs of the same group.
 *
 * This is SMP safe as current->tgid करोes not change.
 */
SYSCALL_DEFINE0(getpid)
अणु
	वापस task_tgid_vnr(current);
पूर्ण

/* Thपढ़ो ID - the पूर्णांकernal kernel "pid" */
SYSCALL_DEFINE0(gettid)
अणु
	वापस task_pid_vnr(current);
पूर्ण

/*
 * Accessing ->real_parent is not SMP-safe, it could
 * change from under us. However, we can use a stale
 * value of ->real_parent under rcu_पढ़ो_lock(), see
 * release_task()->call_rcu(delayed_put_task_काष्ठा).
 */
SYSCALL_DEFINE0(getppid)
अणु
	पूर्णांक pid;

	rcu_पढ़ो_lock();
	pid = task_tgid_vnr(rcu_dereference(current->real_parent));
	rcu_पढ़ो_unlock();

	वापस pid;
पूर्ण

SYSCALL_DEFINE0(getuid)
अणु
	/* Only we change this so SMP safe */
	वापस from_kuid_munged(current_user_ns(), current_uid());
पूर्ण

SYSCALL_DEFINE0(geteuid)
अणु
	/* Only we change this so SMP safe */
	वापस from_kuid_munged(current_user_ns(), current_euid());
पूर्ण

SYSCALL_DEFINE0(getgid)
अणु
	/* Only we change this so SMP safe */
	वापस from_kgid_munged(current_user_ns(), current_gid());
पूर्ण

SYSCALL_DEFINE0(getegid)
अणु
	/* Only we change this so SMP safe */
	वापस from_kgid_munged(current_user_ns(), current_egid());
पूर्ण

अटल व्योम करो_sys_बार(काष्ठा पंचांगs *पंचांगs)
अणु
	u64 tguसमय, tgsसमय, cuसमय, csसमय;

	thपढ़ो_group_cpuसमय_adjusted(current, &tguसमय, &tgsसमय);
	cuसमय = current->संकेत->cuसमय;
	csसमय = current->संकेत->csसमय;
	पंचांगs->पंचांगs_uसमय = nsec_to_घड़ी_प्रकार(tguसमय);
	पंचांगs->पंचांगs_sसमय = nsec_to_घड़ी_प्रकार(tgsसमय);
	पंचांगs->पंचांगs_cuसमय = nsec_to_घड़ी_प्रकार(cuसमय);
	पंचांगs->पंचांगs_csसमय = nsec_to_घड़ी_प्रकार(csसमय);
पूर्ण

SYSCALL_DEFINE1(बार, काष्ठा पंचांगs __user *, tbuf)
अणु
	अगर (tbuf) अणु
		काष्ठा पंचांगs पंचांगp;

		करो_sys_बार(&पंचांगp);
		अगर (copy_to_user(tbuf, &पंचांगp, माप(काष्ठा पंचांगs)))
			वापस -EFAULT;
	पूर्ण
	क्रमce_successful_syscall_वापस();
	वापस (दीर्घ) jअगरfies_64_to_घड़ी_प्रकार(get_jअगरfies_64());
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल compat_घड़ी_प्रकार घड़ी_प्रकार_to_compat_घड़ी_प्रकार(घड़ी_प्रकार x)
अणु
	वापस compat_jअगरfies_to_घड़ी_प्रकार(घड़ी_प्रकार_to_jअगरfies(x));
पूर्ण

COMPAT_SYSCALL_DEFINE1(बार, काष्ठा compat_पंचांगs __user *, tbuf)
अणु
	अगर (tbuf) अणु
		काष्ठा पंचांगs पंचांगs;
		काष्ठा compat_पंचांगs पंचांगp;

		करो_sys_बार(&पंचांगs);
		/* Convert our काष्ठा पंचांगs to the compat version. */
		पंचांगp.पंचांगs_uसमय = घड़ी_प्रकार_to_compat_घड़ी_प्रकार(पंचांगs.पंचांगs_uसमय);
		पंचांगp.पंचांगs_sसमय = घड़ी_प्रकार_to_compat_घड़ी_प्रकार(पंचांगs.पंचांगs_sसमय);
		पंचांगp.पंचांगs_cuसमय = घड़ी_प्रकार_to_compat_घड़ी_प्रकार(पंचांगs.पंचांगs_cuसमय);
		पंचांगp.पंचांगs_csसमय = घड़ी_प्रकार_to_compat_घड़ी_प्रकार(पंचांगs.पंचांगs_csसमय);
		अगर (copy_to_user(tbuf, &पंचांगp, माप(पंचांगp)))
			वापस -EFAULT;
	पूर्ण
	क्रमce_successful_syscall_वापस();
	वापस compat_jअगरfies_to_घड़ी_प्रकार(jअगरfies);
पूर्ण
#पूर्ण_अगर

/*
 * This needs some heavy checking ...
 * I just haven't the stomach for it. I also don't fully
 * understand sessions/pgrp etc. Let somebody who करोes explain it.
 *
 * OK, I think I have the protection semantics right.... this is really
 * only important on a multi-user प्रणाली anyway, to make sure one user
 * can't send a संकेत to a process owned by another.  -TYT, 12/12/91
 *
 * !PF_FORKNOEXEC check to conक्रमm completely to POSIX.
 */
SYSCALL_DEFINE2(setpgid, pid_t, pid, pid_t, pgid)
अणु
	काष्ठा task_काष्ठा *p;
	काष्ठा task_काष्ठा *group_leader = current->group_leader;
	काष्ठा pid *pgrp;
	पूर्णांक err;

	अगर (!pid)
		pid = task_pid_vnr(group_leader);
	अगर (!pgid)
		pgid = pid;
	अगर (pgid < 0)
		वापस -EINVAL;
	rcu_पढ़ो_lock();

	/* From this poपूर्णांक क्रमward we keep holding onto the tasklist lock
	 * so that our parent करोes not change from under us. -DaveM
	 */
	ग_लिखो_lock_irq(&tasklist_lock);

	err = -ESRCH;
	p = find_task_by_vpid(pid);
	अगर (!p)
		जाओ out;

	err = -EINVAL;
	अगर (!thपढ़ो_group_leader(p))
		जाओ out;

	अगर (same_thपढ़ो_group(p->real_parent, group_leader)) अणु
		err = -EPERM;
		अगर (task_session(p) != task_session(group_leader))
			जाओ out;
		err = -EACCES;
		अगर (!(p->flags & PF_FORKNOEXEC))
			जाओ out;
	पूर्ण अन्यथा अणु
		err = -ESRCH;
		अगर (p != group_leader)
			जाओ out;
	पूर्ण

	err = -EPERM;
	अगर (p->संकेत->leader)
		जाओ out;

	pgrp = task_pid(p);
	अगर (pgid != pid) अणु
		काष्ठा task_काष्ठा *g;

		pgrp = find_vpid(pgid);
		g = pid_task(pgrp, PIDTYPE_PGID);
		अगर (!g || task_session(g) != task_session(group_leader))
			जाओ out;
	पूर्ण

	err = security_task_setpgid(p, pgid);
	अगर (err)
		जाओ out;

	अगर (task_pgrp(p) != pgrp)
		change_pid(p, PIDTYPE_PGID, pgrp);

	err = 0;
out:
	/* All paths lead to here, thus we are safe. -DaveM */
	ग_लिखो_unlock_irq(&tasklist_lock);
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण

अटल पूर्णांक करो_getpgid(pid_t pid)
अणु
	काष्ठा task_काष्ठा *p;
	काष्ठा pid *grp;
	पूर्णांक retval;

	rcu_पढ़ो_lock();
	अगर (!pid)
		grp = task_pgrp(current);
	अन्यथा अणु
		retval = -ESRCH;
		p = find_task_by_vpid(pid);
		अगर (!p)
			जाओ out;
		grp = task_pgrp(p);
		अगर (!grp)
			जाओ out;

		retval = security_task_getpgid(p);
		अगर (retval)
			जाओ out;
	पूर्ण
	retval = pid_vnr(grp);
out:
	rcu_पढ़ो_unlock();
	वापस retval;
पूर्ण

SYSCALL_DEFINE1(getpgid, pid_t, pid)
अणु
	वापस करो_getpgid(pid);
पूर्ण

#अगर_घोषित __ARCH_WANT_SYS_GETPGRP

SYSCALL_DEFINE0(getpgrp)
अणु
	वापस करो_getpgid(0);
पूर्ण

#पूर्ण_अगर

SYSCALL_DEFINE1(माला_लोid, pid_t, pid)
अणु
	काष्ठा task_काष्ठा *p;
	काष्ठा pid *sid;
	पूर्णांक retval;

	rcu_पढ़ो_lock();
	अगर (!pid)
		sid = task_session(current);
	अन्यथा अणु
		retval = -ESRCH;
		p = find_task_by_vpid(pid);
		अगर (!p)
			जाओ out;
		sid = task_session(p);
		अगर (!sid)
			जाओ out;

		retval = security_task_माला_लोid(p);
		अगर (retval)
			जाओ out;
	पूर्ण
	retval = pid_vnr(sid);
out:
	rcu_पढ़ो_unlock();
	वापस retval;
पूर्ण

अटल व्योम set_special_pids(काष्ठा pid *pid)
अणु
	काष्ठा task_काष्ठा *curr = current->group_leader;

	अगर (task_session(curr) != pid)
		change_pid(curr, PIDTYPE_SID, pid);

	अगर (task_pgrp(curr) != pid)
		change_pid(curr, PIDTYPE_PGID, pid);
पूर्ण

पूर्णांक ksys_setsid(व्योम)
अणु
	काष्ठा task_काष्ठा *group_leader = current->group_leader;
	काष्ठा pid *sid = task_pid(group_leader);
	pid_t session = pid_vnr(sid);
	पूर्णांक err = -EPERM;

	ग_लिखो_lock_irq(&tasklist_lock);
	/* Fail अगर I am alपढ़ोy a session leader */
	अगर (group_leader->संकेत->leader)
		जाओ out;

	/* Fail अगर a process group id alपढ़ोy exists that equals the
	 * proposed session id.
	 */
	अगर (pid_task(sid, PIDTYPE_PGID))
		जाओ out;

	group_leader->संकेत->leader = 1;
	set_special_pids(sid);

	proc_clear_tty(group_leader);

	err = session;
out:
	ग_लिखो_unlock_irq(&tasklist_lock);
	अगर (err > 0) अणु
		proc_sid_connector(group_leader);
		sched_स्वतःgroup_create_attach(group_leader);
	पूर्ण
	वापस err;
पूर्ण

SYSCALL_DEFINE0(setsid)
अणु
	वापस ksys_setsid();
पूर्ण

DECLARE_RWSEM(uts_sem);

#अगर_घोषित COMPAT_UTS_MACHINE
#घोषणा override_architecture(name) \
	(personality(current->personality) == PER_LINUX32 && \
	 copy_to_user(name->machine, COMPAT_UTS_MACHINE, \
		      माप(COMPAT_UTS_MACHINE)))
#अन्यथा
#घोषणा override_architecture(name)	0
#पूर्ण_अगर

/*
 * Work around broken programs that cannot handle "Linux 3.0".
 * Instead we map 3.x to 2.6.40+x, so e.g. 3.0 would be 2.6.40
 * And we map 4.x and later versions to 2.6.60+x, so 4.0/5.0/6.0/... would be
 * 2.6.60.
 */
अटल पूर्णांक override_release(अक्षर __user *release, माप_प्रकार len)
अणु
	पूर्णांक ret = 0;

	अगर (current->personality & UNAME26) अणु
		स्थिर अक्षर *rest = UTS_RELEASE;
		अक्षर buf[65] = अणु 0 पूर्ण;
		पूर्णांक nकरोts = 0;
		अचिन्हित v;
		माप_प्रकार copy;

		जबतक (*rest) अणु
			अगर (*rest == '.' && ++nकरोts >= 3)
				अवरोध;
			अगर (!है_अंक(*rest) && *rest != '.')
				अवरोध;
			rest++;
		पूर्ण
		v = LINUX_VERSION_PATCHLEVEL + 60;
		copy = clamp_t(माप_प्रकार, len, 1, माप(buf));
		copy = scnम_लिखो(buf, copy, "2.6.%u%s", v, rest);
		ret = copy_to_user(release, buf, copy + 1);
	पूर्ण
	वापस ret;
पूर्ण

SYSCALL_DEFINE1(newuname, काष्ठा new_utsname __user *, name)
अणु
	काष्ठा new_utsname पंचांगp;

	करोwn_पढ़ो(&uts_sem);
	स_नकल(&पंचांगp, utsname(), माप(पंचांगp));
	up_पढ़ो(&uts_sem);
	अगर (copy_to_user(name, &पंचांगp, माप(पंचांगp)))
		वापस -EFAULT;

	अगर (override_release(name->release, माप(name->release)))
		वापस -EFAULT;
	अगर (override_architecture(name))
		वापस -EFAULT;
	वापस 0;
पूर्ण

#अगर_घोषित __ARCH_WANT_SYS_OLD_UNAME
/*
 * Old cruft
 */
SYSCALL_DEFINE1(uname, काष्ठा old_utsname __user *, name)
अणु
	काष्ठा old_utsname पंचांगp;

	अगर (!name)
		वापस -EFAULT;

	करोwn_पढ़ो(&uts_sem);
	स_नकल(&पंचांगp, utsname(), माप(पंचांगp));
	up_पढ़ो(&uts_sem);
	अगर (copy_to_user(name, &पंचांगp, माप(पंचांगp)))
		वापस -EFAULT;

	अगर (override_release(name->release, माप(name->release)))
		वापस -EFAULT;
	अगर (override_architecture(name))
		वापस -EFAULT;
	वापस 0;
पूर्ण

SYSCALL_DEFINE1(olduname, काष्ठा olकरोld_utsname __user *, name)
अणु
	काष्ठा olकरोld_utsname पंचांगp;

	अगर (!name)
		वापस -EFAULT;

	स_रखो(&पंचांगp, 0, माप(पंचांगp));

	करोwn_पढ़ो(&uts_sem);
	स_नकल(&पंचांगp.sysname, &utsname()->sysname, __OLD_UTS_LEN);
	स_नकल(&पंचांगp.nodename, &utsname()->nodename, __OLD_UTS_LEN);
	स_नकल(&पंचांगp.release, &utsname()->release, __OLD_UTS_LEN);
	स_नकल(&पंचांगp.version, &utsname()->version, __OLD_UTS_LEN);
	स_नकल(&पंचांगp.machine, &utsname()->machine, __OLD_UTS_LEN);
	up_पढ़ो(&uts_sem);
	अगर (copy_to_user(name, &पंचांगp, माप(पंचांगp)))
		वापस -EFAULT;

	अगर (override_architecture(name))
		वापस -EFAULT;
	अगर (override_release(name->release, माप(name->release)))
		वापस -EFAULT;
	वापस 0;
पूर्ण
#पूर्ण_अगर

SYSCALL_DEFINE2(sethostname, अक्षर __user *, name, पूर्णांक, len)
अणु
	पूर्णांक त्रुटि_सं;
	अक्षर पंचांगp[__NEW_UTS_LEN];

	अगर (!ns_capable(current->nsproxy->uts_ns->user_ns, CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (len < 0 || len > __NEW_UTS_LEN)
		वापस -EINVAL;
	त्रुटि_सं = -EFAULT;
	अगर (!copy_from_user(पंचांगp, name, len)) अणु
		काष्ठा new_utsname *u;

		करोwn_ग_लिखो(&uts_sem);
		u = utsname();
		स_नकल(u->nodename, पंचांगp, len);
		स_रखो(u->nodename + len, 0, माप(u->nodename) - len);
		त्रुटि_सं = 0;
		uts_proc_notअगरy(UTS_PROC_HOSTNAME);
		up_ग_लिखो(&uts_sem);
	पूर्ण
	वापस त्रुटि_सं;
पूर्ण

#अगर_घोषित __ARCH_WANT_SYS_GETHOSTNAME

SYSCALL_DEFINE2(gethostname, अक्षर __user *, name, पूर्णांक, len)
अणु
	पूर्णांक i;
	काष्ठा new_utsname *u;
	अक्षर पंचांगp[__NEW_UTS_LEN + 1];

	अगर (len < 0)
		वापस -EINVAL;
	करोwn_पढ़ो(&uts_sem);
	u = utsname();
	i = 1 + म_माप(u->nodename);
	अगर (i > len)
		i = len;
	स_नकल(पंचांगp, u->nodename, i);
	up_पढ़ो(&uts_sem);
	अगर (copy_to_user(name, पंचांगp, i))
		वापस -EFAULT;
	वापस 0;
पूर्ण

#पूर्ण_अगर

/*
 * Only setकरोमुख्यname; getकरोमुख्यname can be implemented by calling
 * uname()
 */
SYSCALL_DEFINE2(setकरोमुख्यname, अक्षर __user *, name, पूर्णांक, len)
अणु
	पूर्णांक त्रुटि_सं;
	अक्षर पंचांगp[__NEW_UTS_LEN];

	अगर (!ns_capable(current->nsproxy->uts_ns->user_ns, CAP_SYS_ADMIN))
		वापस -EPERM;
	अगर (len < 0 || len > __NEW_UTS_LEN)
		वापस -EINVAL;

	त्रुटि_सं = -EFAULT;
	अगर (!copy_from_user(पंचांगp, name, len)) अणु
		काष्ठा new_utsname *u;

		करोwn_ग_लिखो(&uts_sem);
		u = utsname();
		स_नकल(u->करोमुख्यname, पंचांगp, len);
		स_रखो(u->करोमुख्यname + len, 0, माप(u->करोमुख्यname) - len);
		त्रुटि_सं = 0;
		uts_proc_notअगरy(UTS_PROC_DOMAINNAME);
		up_ग_लिखो(&uts_sem);
	पूर्ण
	वापस त्रुटि_सं;
पूर्ण

SYSCALL_DEFINE2(getrlimit, अचिन्हित पूर्णांक, resource, काष्ठा rlimit __user *, rlim)
अणु
	काष्ठा rlimit value;
	पूर्णांक ret;

	ret = करो_prlimit(current, resource, शून्य, &value);
	अगर (!ret)
		ret = copy_to_user(rlim, &value, माप(*rlim)) ? -EFAULT : 0;

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_COMPAT

COMPAT_SYSCALL_DEFINE2(setrlimit, अचिन्हित पूर्णांक, resource,
		       काष्ठा compat_rlimit __user *, rlim)
अणु
	काष्ठा rlimit r;
	काष्ठा compat_rlimit r32;

	अगर (copy_from_user(&r32, rlim, माप(काष्ठा compat_rlimit)))
		वापस -EFAULT;

	अगर (r32.rlim_cur == COMPAT_RLIM_अनन्त)
		r.rlim_cur = RLIM_अनन्त;
	अन्यथा
		r.rlim_cur = r32.rlim_cur;
	अगर (r32.rlim_max == COMPAT_RLIM_अनन्त)
		r.rlim_max = RLIM_अनन्त;
	अन्यथा
		r.rlim_max = r32.rlim_max;
	वापस करो_prlimit(current, resource, &r, शून्य);
पूर्ण

COMPAT_SYSCALL_DEFINE2(getrlimit, अचिन्हित पूर्णांक, resource,
		       काष्ठा compat_rlimit __user *, rlim)
अणु
	काष्ठा rlimit r;
	पूर्णांक ret;

	ret = करो_prlimit(current, resource, शून्य, &r);
	अगर (!ret) अणु
		काष्ठा compat_rlimit r32;
		अगर (r.rlim_cur > COMPAT_RLIM_अनन्त)
			r32.rlim_cur = COMPAT_RLIM_अनन्त;
		अन्यथा
			r32.rlim_cur = r.rlim_cur;
		अगर (r.rlim_max > COMPAT_RLIM_अनन्त)
			r32.rlim_max = COMPAT_RLIM_अनन्त;
		अन्यथा
			r32.rlim_max = r.rlim_max;

		अगर (copy_to_user(rlim, &r32, माप(काष्ठा compat_rlimit)))
			वापस -EFAULT;
	पूर्ण
	वापस ret;
पूर्ण

#पूर्ण_अगर

#अगर_घोषित __ARCH_WANT_SYS_OLD_GETRLIMIT

/*
 *	Back compatibility क्रम getrlimit. Needed क्रम some apps.
 */
SYSCALL_DEFINE2(old_getrlimit, अचिन्हित पूर्णांक, resource,
		काष्ठा rlimit __user *, rlim)
अणु
	काष्ठा rlimit x;
	अगर (resource >= RLIM_NLIMITS)
		वापस -EINVAL;

	resource = array_index_nospec(resource, RLIM_NLIMITS);
	task_lock(current->group_leader);
	x = current->संकेत->rlim[resource];
	task_unlock(current->group_leader);
	अगर (x.rlim_cur > 0x7FFFFFFF)
		x.rlim_cur = 0x7FFFFFFF;
	अगर (x.rlim_max > 0x7FFFFFFF)
		x.rlim_max = 0x7FFFFFFF;
	वापस copy_to_user(rlim, &x, माप(x)) ? -EFAULT : 0;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
COMPAT_SYSCALL_DEFINE2(old_getrlimit, अचिन्हित पूर्णांक, resource,
		       काष्ठा compat_rlimit __user *, rlim)
अणु
	काष्ठा rlimit r;

	अगर (resource >= RLIM_NLIMITS)
		वापस -EINVAL;

	resource = array_index_nospec(resource, RLIM_NLIMITS);
	task_lock(current->group_leader);
	r = current->संकेत->rlim[resource];
	task_unlock(current->group_leader);
	अगर (r.rlim_cur > 0x7FFFFFFF)
		r.rlim_cur = 0x7FFFFFFF;
	अगर (r.rlim_max > 0x7FFFFFFF)
		r.rlim_max = 0x7FFFFFFF;

	अगर (put_user(r.rlim_cur, &rlim->rlim_cur) ||
	    put_user(r.rlim_max, &rlim->rlim_max))
		वापस -EFAULT;
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर

अटल अंतरभूत bool rlim64_is_infinity(__u64 rlim64)
अणु
#अगर BITS_PER_LONG < 64
	वापस rlim64 >= अच_दीर्घ_उच्च;
#अन्यथा
	वापस rlim64 == RLIM64_अनन्त;
#पूर्ण_अगर
पूर्ण

अटल व्योम rlim_to_rlim64(स्थिर काष्ठा rlimit *rlim, काष्ठा rlimit64 *rlim64)
अणु
	अगर (rlim->rlim_cur == RLIM_अनन्त)
		rlim64->rlim_cur = RLIM64_अनन्त;
	अन्यथा
		rlim64->rlim_cur = rlim->rlim_cur;
	अगर (rlim->rlim_max == RLIM_अनन्त)
		rlim64->rlim_max = RLIM64_अनन्त;
	अन्यथा
		rlim64->rlim_max = rlim->rlim_max;
पूर्ण

अटल व्योम rlim64_to_rlim(स्थिर काष्ठा rlimit64 *rlim64, काष्ठा rlimit *rlim)
अणु
	अगर (rlim64_is_infinity(rlim64->rlim_cur))
		rlim->rlim_cur = RLIM_अनन्त;
	अन्यथा
		rlim->rlim_cur = (अचिन्हित दीर्घ)rlim64->rlim_cur;
	अगर (rlim64_is_infinity(rlim64->rlim_max))
		rlim->rlim_max = RLIM_अनन्त;
	अन्यथा
		rlim->rlim_max = (अचिन्हित दीर्घ)rlim64->rlim_max;
पूर्ण

/* make sure you are allowed to change @tsk limits beक्रमe calling this */
पूर्णांक करो_prlimit(काष्ठा task_काष्ठा *tsk, अचिन्हित पूर्णांक resource,
		काष्ठा rlimit *new_rlim, काष्ठा rlimit *old_rlim)
अणु
	काष्ठा rlimit *rlim;
	पूर्णांक retval = 0;

	अगर (resource >= RLIM_NLIMITS)
		वापस -EINVAL;
	अगर (new_rlim) अणु
		अगर (new_rlim->rlim_cur > new_rlim->rlim_max)
			वापस -EINVAL;
		अगर (resource == RLIMIT_NOखाता &&
				new_rlim->rlim_max > sysctl_nr_खोलो)
			वापस -EPERM;
	पूर्ण

	/* protect tsk->संकेत and tsk->sighand from disappearing */
	पढ़ो_lock(&tasklist_lock);
	अगर (!tsk->sighand) अणु
		retval = -ESRCH;
		जाओ out;
	पूर्ण

	rlim = tsk->संकेत->rlim + resource;
	task_lock(tsk->group_leader);
	अगर (new_rlim) अणु
		/* Keep the capable check against init_user_ns until
		   cgroups can contain all limits */
		अगर (new_rlim->rlim_max > rlim->rlim_max &&
				!capable(CAP_SYS_RESOURCE))
			retval = -EPERM;
		अगर (!retval)
			retval = security_task_setrlimit(tsk, resource, new_rlim);
	पूर्ण
	अगर (!retval) अणु
		अगर (old_rlim)
			*old_rlim = *rlim;
		अगर (new_rlim)
			*rlim = *new_rlim;
	पूर्ण
	task_unlock(tsk->group_leader);

	/*
	 * RLIMIT_CPU handling. Arm the posix CPU समयr अगर the limit is not
	 * infinite. In हाल of RLIM_अनन्त the posix CPU समयr code
	 * ignores the rlimit.
	 */
	 अगर (!retval && new_rlim && resource == RLIMIT_CPU &&
	     new_rlim->rlim_cur != RLIM_अनन्त &&
	     IS_ENABLED(CONFIG_POSIX_TIMERS))
		update_rlimit_cpu(tsk, new_rlim->rlim_cur);
out:
	पढ़ो_unlock(&tasklist_lock);
	वापस retval;
पूर्ण

/* rcu lock must be held */
अटल पूर्णांक check_prlimit_permission(काष्ठा task_काष्ठा *task,
				    अचिन्हित पूर्णांक flags)
अणु
	स्थिर काष्ठा cred *cred = current_cred(), *tcred;
	bool id_match;

	अगर (current == task)
		वापस 0;

	tcred = __task_cred(task);
	id_match = (uid_eq(cred->uid, tcred->euid) &&
		    uid_eq(cred->uid, tcred->suid) &&
		    uid_eq(cred->uid, tcred->uid)  &&
		    gid_eq(cred->gid, tcred->egid) &&
		    gid_eq(cred->gid, tcred->sgid) &&
		    gid_eq(cred->gid, tcred->gid));
	अगर (!id_match && !ns_capable(tcred->user_ns, CAP_SYS_RESOURCE))
		वापस -EPERM;

	वापस security_task_prlimit(cred, tcred, flags);
पूर्ण

SYSCALL_DEFINE4(prlimit64, pid_t, pid, अचिन्हित पूर्णांक, resource,
		स्थिर काष्ठा rlimit64 __user *, new_rlim,
		काष्ठा rlimit64 __user *, old_rlim)
अणु
	काष्ठा rlimit64 old64, new64;
	काष्ठा rlimit old, new;
	काष्ठा task_काष्ठा *tsk;
	अचिन्हित पूर्णांक checkflags = 0;
	पूर्णांक ret;

	अगर (old_rlim)
		checkflags |= LSM_PRLIMIT_READ;

	अगर (new_rlim) अणु
		अगर (copy_from_user(&new64, new_rlim, माप(new64)))
			वापस -EFAULT;
		rlim64_to_rlim(&new64, &new);
		checkflags |= LSM_PRLIMIT_WRITE;
	पूर्ण

	rcu_पढ़ो_lock();
	tsk = pid ? find_task_by_vpid(pid) : current;
	अगर (!tsk) अणु
		rcu_पढ़ो_unlock();
		वापस -ESRCH;
	पूर्ण
	ret = check_prlimit_permission(tsk, checkflags);
	अगर (ret) अणु
		rcu_पढ़ो_unlock();
		वापस ret;
	पूर्ण
	get_task_काष्ठा(tsk);
	rcu_पढ़ो_unlock();

	ret = करो_prlimit(tsk, resource, new_rlim ? &new : शून्य,
			old_rlim ? &old : शून्य);

	अगर (!ret && old_rlim) अणु
		rlim_to_rlim64(&old, &old64);
		अगर (copy_to_user(old_rlim, &old64, माप(old64)))
			ret = -EFAULT;
	पूर्ण

	put_task_काष्ठा(tsk);
	वापस ret;
पूर्ण

SYSCALL_DEFINE2(setrlimit, अचिन्हित पूर्णांक, resource, काष्ठा rlimit __user *, rlim)
अणु
	काष्ठा rlimit new_rlim;

	अगर (copy_from_user(&new_rlim, rlim, माप(*rlim)))
		वापस -EFAULT;
	वापस करो_prlimit(current, resource, &new_rlim, शून्य);
पूर्ण

/*
 * It would make sense to put काष्ठा rusage in the task_काष्ठा,
 * except that would make the task_काष्ठा be *really big*.  After
 * task_काष्ठा माला_लो moved पूर्णांकo दो_स्मृति'ed memory, it would
 * make sense to करो this.  It will make moving the rest of the inक्रमmation
 * a lot simpler!  (Which we're not doing right now because we're not
 * measuring them yet).
 *
 * When sampling multiple thपढ़ोs क्रम RUSAGE_SELF, under SMP we might have
 * races with thपढ़ोs incrementing their own counters.  But since word
 * पढ़ोs are atomic, we either get new values or old values and we करोn't
 * care which क्रम the sums.  We always take the siglock to protect पढ़ोing
 * the c* fields from p->संकेत from races with निकास.c updating those
 * fields when reaping, so a sample either माला_लो all the additions of a
 * given child after it's reaped, or none so this sample is beक्रमe reaping.
 *
 * Locking:
 * We need to take the siglock क्रम CHILDEREN, SELF and BOTH
 * क्रम  the हालs current multithपढ़ोed, non-current single thपढ़ोed
 * non-current multithपढ़ोed.  Thपढ़ो traversal is now safe with
 * the siglock held.
 * Strictly speaking, we करोnot need to take the siglock अगर we are current and
 * single thपढ़ोed,  as no one अन्यथा can take our संकेत_काष्ठा away, no one
 * अन्यथा can  reap the  children to update संकेत->c* counters, and no one अन्यथा
 * can race with the संकेत-> fields. If we करो not take any lock, the
 * संकेत-> fields could be पढ़ो out of order जबतक another thपढ़ो was just
 * निकासing. So we should  place a पढ़ो memory barrier when we aव्योम the lock.
 * On the ग_लिखोr side,  ग_लिखो memory barrier is implied in  __निकास_संकेत
 * as __निकास_संकेत releases  the siglock spinlock after updating the संकेत->
 * fields. But we करोn't करो this yet to keep things simple.
 *
 */

अटल व्योम accumulate_thपढ़ो_rusage(काष्ठा task_काष्ठा *t, काष्ठा rusage *r)
अणु
	r->ru_nvcsw += t->nvcsw;
	r->ru_nivcsw += t->nivcsw;
	r->ru_minflt += t->min_flt;
	r->ru_majflt += t->maj_flt;
	r->ru_inblock += task_io_get_inblock(t);
	r->ru_oublock += task_io_get_oublock(t);
पूर्ण

व्योम getrusage(काष्ठा task_काष्ठा *p, पूर्णांक who, काष्ठा rusage *r)
अणु
	काष्ठा task_काष्ठा *t;
	अचिन्हित दीर्घ flags;
	u64 tguसमय, tgsसमय, uसमय, sसमय;
	अचिन्हित दीर्घ maxrss = 0;

	स_रखो((अक्षर *)r, 0, माप (*r));
	uसमय = sसमय = 0;

	अगर (who == RUSAGE_THREAD) अणु
		task_cpuसमय_adjusted(current, &uसमय, &sसमय);
		accumulate_thपढ़ो_rusage(p, r);
		maxrss = p->संकेत->maxrss;
		जाओ out;
	पूर्ण

	अगर (!lock_task_sighand(p, &flags))
		वापस;

	चयन (who) अणु
	हाल RUSAGE_BOTH:
	हाल RUSAGE_CHILDREN:
		uसमय = p->संकेत->cuसमय;
		sसमय = p->संकेत->csसमय;
		r->ru_nvcsw = p->संकेत->cnvcsw;
		r->ru_nivcsw = p->संकेत->cnivcsw;
		r->ru_minflt = p->संकेत->cmin_flt;
		r->ru_majflt = p->संकेत->cmaj_flt;
		r->ru_inblock = p->संकेत->cinblock;
		r->ru_oublock = p->संकेत->coublock;
		maxrss = p->संकेत->cmaxrss;

		अगर (who == RUSAGE_CHILDREN)
			अवरोध;
		fallthrough;

	हाल RUSAGE_SELF:
		thपढ़ो_group_cpuसमय_adjusted(p, &tguसमय, &tgsसमय);
		uसमय += tguसमय;
		sसमय += tgsसमय;
		r->ru_nvcsw += p->संकेत->nvcsw;
		r->ru_nivcsw += p->संकेत->nivcsw;
		r->ru_minflt += p->संकेत->min_flt;
		r->ru_majflt += p->संकेत->maj_flt;
		r->ru_inblock += p->संकेत->inblock;
		r->ru_oublock += p->संकेत->oublock;
		अगर (maxrss < p->संकेत->maxrss)
			maxrss = p->संकेत->maxrss;
		t = p;
		करो अणु
			accumulate_thपढ़ो_rusage(t, r);
		पूर्ण जबतक_each_thपढ़ो(p, t);
		अवरोध;

	शेष:
		BUG();
	पूर्ण
	unlock_task_sighand(p, &flags);

out:
	r->ru_uसमय = ns_to_kernel_old_समयval(uसमय);
	r->ru_sसमय = ns_to_kernel_old_समयval(sसमय);

	अगर (who != RUSAGE_CHILDREN) अणु
		काष्ठा mm_काष्ठा *mm = get_task_mm(p);

		अगर (mm) अणु
			seपंचांगax_mm_hiwater_rss(&maxrss, mm);
			mmput(mm);
		पूर्ण
	पूर्ण
	r->ru_maxrss = maxrss * (PAGE_SIZE / 1024); /* convert pages to KBs */
पूर्ण

SYSCALL_DEFINE2(getrusage, पूर्णांक, who, काष्ठा rusage __user *, ru)
अणु
	काष्ठा rusage r;

	अगर (who != RUSAGE_SELF && who != RUSAGE_CHILDREN &&
	    who != RUSAGE_THREAD)
		वापस -EINVAL;

	getrusage(current, who, &r);
	वापस copy_to_user(ru, &r, माप(r)) ? -EFAULT : 0;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
COMPAT_SYSCALL_DEFINE2(getrusage, पूर्णांक, who, काष्ठा compat_rusage __user *, ru)
अणु
	काष्ठा rusage r;

	अगर (who != RUSAGE_SELF && who != RUSAGE_CHILDREN &&
	    who != RUSAGE_THREAD)
		वापस -EINVAL;

	getrusage(current, who, &r);
	वापस put_compat_rusage(&r, ru);
पूर्ण
#पूर्ण_अगर

SYSCALL_DEFINE1(umask, पूर्णांक, mask)
अणु
	mask = xchg(&current->fs->umask, mask & S_IRWXUGO);
	वापस mask;
पूर्ण

अटल पूर्णांक prctl_set_mm_exe_file(काष्ठा mm_काष्ठा *mm, अचिन्हित पूर्णांक fd)
अणु
	काष्ठा fd exe;
	काष्ठा file *old_exe, *exe_file;
	काष्ठा inode *inode;
	पूर्णांक err;

	exe = fdget(fd);
	अगर (!exe.file)
		वापस -EBADF;

	inode = file_inode(exe.file);

	/*
	 * Because the original mm->exe_file poपूर्णांकs to executable file, make
	 * sure that this one is executable as well, to aव्योम अवरोधing an
	 * overall picture.
	 */
	err = -EACCES;
	अगर (!S_ISREG(inode->i_mode) || path_noexec(&exe.file->f_path))
		जाओ निकास;

	err = file_permission(exe.file, MAY_EXEC);
	अगर (err)
		जाओ निकास;

	/*
	 * Forbid mm->exe_file change अगर old file still mapped.
	 */
	exe_file = get_mm_exe_file(mm);
	err = -EBUSY;
	अगर (exe_file) अणु
		काष्ठा vm_area_काष्ठा *vma;

		mmap_पढ़ो_lock(mm);
		क्रम (vma = mm->mmap; vma; vma = vma->vm_next) अणु
			अगर (!vma->vm_file)
				जारी;
			अगर (path_equal(&vma->vm_file->f_path,
				       &exe_file->f_path))
				जाओ निकास_err;
		पूर्ण

		mmap_पढ़ो_unlock(mm);
		fput(exe_file);
	पूर्ण

	err = 0;
	/* set the new file, lockless */
	get_file(exe.file);
	old_exe = xchg(&mm->exe_file, exe.file);
	अगर (old_exe)
		fput(old_exe);
निकास:
	fdput(exe);
	वापस err;
निकास_err:
	mmap_पढ़ो_unlock(mm);
	fput(exe_file);
	जाओ निकास;
पूर्ण

/*
 * Check arithmetic relations of passed addresses.
 *
 * WARNING: we करोn't require any capability here so be very careful
 * in what is allowed क्रम modअगरication from userspace.
 */
अटल पूर्णांक validate_prctl_map_addr(काष्ठा prctl_mm_map *prctl_map)
अणु
	अचिन्हित दीर्घ mmap_max_addr = TASK_SIZE;
	पूर्णांक error = -EINVAL, i;

	अटल स्थिर अचिन्हित अक्षर offsets[] = अणु
		दुरत्व(काष्ठा prctl_mm_map, start_code),
		दुरत्व(काष्ठा prctl_mm_map, end_code),
		दुरत्व(काष्ठा prctl_mm_map, start_data),
		दुरत्व(काष्ठा prctl_mm_map, end_data),
		दुरत्व(काष्ठा prctl_mm_map, start_brk),
		दुरत्व(काष्ठा prctl_mm_map, brk),
		दुरत्व(काष्ठा prctl_mm_map, start_stack),
		दुरत्व(काष्ठा prctl_mm_map, arg_start),
		दुरत्व(काष्ठा prctl_mm_map, arg_end),
		दुरत्व(काष्ठा prctl_mm_map, env_start),
		दुरत्व(काष्ठा prctl_mm_map, env_end),
	पूर्ण;

	/*
	 * Make sure the members are not somewhere outside
	 * of allowed address space.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(offsets); i++) अणु
		u64 val = *(u64 *)((अक्षर *)prctl_map + offsets[i]);

		अगर ((अचिन्हित दीर्घ)val >= mmap_max_addr ||
		    (अचिन्हित दीर्घ)val < mmap_min_addr)
			जाओ out;
	पूर्ण

	/*
	 * Make sure the pairs are ordered.
	 */
#घोषणा __prctl_check_order(__m1, __op, __m2)				\
	((अचिन्हित दीर्घ)prctl_map->__m1 __op				\
	 (अचिन्हित दीर्घ)prctl_map->__m2) ? 0 : -EINVAL
	error  = __prctl_check_order(start_code, <, end_code);
	error |= __prctl_check_order(start_data,<=, end_data);
	error |= __prctl_check_order(start_brk, <=, brk);
	error |= __prctl_check_order(arg_start, <=, arg_end);
	error |= __prctl_check_order(env_start, <=, env_end);
	अगर (error)
		जाओ out;
#अघोषित __prctl_check_order

	error = -EINVAL;

	/*
	 * @brk should be after @end_data in traditional maps.
	 */
	अगर (prctl_map->start_brk <= prctl_map->end_data ||
	    prctl_map->brk <= prctl_map->end_data)
		जाओ out;

	/*
	 * Neither we should allow to override limits अगर they set.
	 */
	अगर (check_data_rlimit(rlimit(RLIMIT_DATA), prctl_map->brk,
			      prctl_map->start_brk, prctl_map->end_data,
			      prctl_map->start_data))
			जाओ out;

	error = 0;
out:
	वापस error;
पूर्ण

#अगर_घोषित CONFIG_CHECKPOINT_RESTORE
अटल पूर्णांक prctl_set_mm_map(पूर्णांक opt, स्थिर व्योम __user *addr, अचिन्हित दीर्घ data_size)
अणु
	काष्ठा prctl_mm_map prctl_map = अणु .exe_fd = (u32)-1, पूर्ण;
	अचिन्हित दीर्घ user_auxv[AT_VECTOR_SIZE];
	काष्ठा mm_काष्ठा *mm = current->mm;
	पूर्णांक error;

	BUILD_BUG_ON(माप(user_auxv) != माप(mm->saved_auxv));
	BUILD_BUG_ON(माप(काष्ठा prctl_mm_map) > 256);

	अगर (opt == PR_SET_MM_MAP_SIZE)
		वापस put_user((अचिन्हित पूर्णांक)माप(prctl_map),
				(अचिन्हित पूर्णांक __user *)addr);

	अगर (data_size != माप(prctl_map))
		वापस -EINVAL;

	अगर (copy_from_user(&prctl_map, addr, माप(prctl_map)))
		वापस -EFAULT;

	error = validate_prctl_map_addr(&prctl_map);
	अगर (error)
		वापस error;

	अगर (prctl_map.auxv_size) अणु
		/*
		 * Someone is trying to cheat the auxv vector.
		 */
		अगर (!prctl_map.auxv ||
				prctl_map.auxv_size > माप(mm->saved_auxv))
			वापस -EINVAL;

		स_रखो(user_auxv, 0, माप(user_auxv));
		अगर (copy_from_user(user_auxv,
				   (स्थिर व्योम __user *)prctl_map.auxv,
				   prctl_map.auxv_size))
			वापस -EFAULT;

		/* Last entry must be AT_शून्य as specअगरication requires */
		user_auxv[AT_VECTOR_SIZE - 2] = AT_शून्य;
		user_auxv[AT_VECTOR_SIZE - 1] = AT_शून्य;
	पूर्ण

	अगर (prctl_map.exe_fd != (u32)-1) अणु
		/*
		 * Check अगर the current user is checkpoपूर्णांक/restore capable.
		 * At the समय of this writing, it checks क्रम CAP_SYS_ADMIN
		 * or CAP_CHECKPOINT_RESTORE.
		 * Note that a user with access to ptrace can masquerade an
		 * arbitrary program as any executable, even setuid ones.
		 * This may have implications in the tomoyo subप्रणाली.
		 */
		अगर (!checkpoपूर्णांक_restore_ns_capable(current_user_ns()))
			वापस -EPERM;

		error = prctl_set_mm_exe_file(mm, prctl_map.exe_fd);
		अगर (error)
			वापस error;
	पूर्ण

	/*
	 * arg_lock protects concurrent updates but we still need mmap_lock क्रम
	 * पढ़ो to exclude races with sys_brk.
	 */
	mmap_पढ़ो_lock(mm);

	/*
	 * We करोn't validate अगर these members are poपूर्णांकing to
	 * real present VMAs because application may have correspond
	 * VMAs alपढ़ोy unmapped and kernel uses these members क्रम statistics
	 * output in procfs mostly, except
	 *
	 *  - @start_brk/@brk which are used in करो_brk_flags but kernel lookups
	 *    क्रम VMAs when updating these members so anything wrong written
	 *    here cause kernel to swear at userspace program but won't lead
	 *    to any problem in kernel itself
	 */

	spin_lock(&mm->arg_lock);
	mm->start_code	= prctl_map.start_code;
	mm->end_code	= prctl_map.end_code;
	mm->start_data	= prctl_map.start_data;
	mm->end_data	= prctl_map.end_data;
	mm->start_brk	= prctl_map.start_brk;
	mm->brk		= prctl_map.brk;
	mm->start_stack	= prctl_map.start_stack;
	mm->arg_start	= prctl_map.arg_start;
	mm->arg_end	= prctl_map.arg_end;
	mm->env_start	= prctl_map.env_start;
	mm->env_end	= prctl_map.env_end;
	spin_unlock(&mm->arg_lock);

	/*
	 * Note this update of @saved_auxv is lockless thus
	 * अगर someone पढ़ोs this member in procfs जबतक we're
	 * updating -- it may get partly updated results. It's
	 * known and acceptable trade off: we leave it as is to
	 * not पूर्णांकroduce additional locks here making the kernel
	 * more complex.
	 */
	अगर (prctl_map.auxv_size)
		स_नकल(mm->saved_auxv, user_auxv, माप(user_auxv));

	mmap_पढ़ो_unlock(mm);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_CHECKPOINT_RESTORE */

अटल पूर्णांक prctl_set_auxv(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			  अचिन्हित दीर्घ len)
अणु
	/*
	 * This करोesn't move the auxiliary vector itself since it's pinned to
	 * mm_काष्ठा, but it permits filling the vector with new values.  It's
	 * up to the caller to provide sane values here, otherwise userspace
	 * tools which use this vector might be unhappy.
	 */
	अचिन्हित दीर्घ user_auxv[AT_VECTOR_SIZE] = अणुपूर्ण;

	अगर (len > माप(user_auxv))
		वापस -EINVAL;

	अगर (copy_from_user(user_auxv, (स्थिर व्योम __user *)addr, len))
		वापस -EFAULT;

	/* Make sure the last entry is always AT_शून्य */
	user_auxv[AT_VECTOR_SIZE - 2] = 0;
	user_auxv[AT_VECTOR_SIZE - 1] = 0;

	BUILD_BUG_ON(माप(user_auxv) != माप(mm->saved_auxv));

	task_lock(current);
	स_नकल(mm->saved_auxv, user_auxv, len);
	task_unlock(current);

	वापस 0;
पूर्ण

अटल पूर्णांक prctl_set_mm(पूर्णांक opt, अचिन्हित दीर्घ addr,
			अचिन्हित दीर्घ arg4, अचिन्हित दीर्घ arg5)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा prctl_mm_map prctl_map = अणु
		.auxv = शून्य,
		.auxv_size = 0,
		.exe_fd = -1,
	पूर्ण;
	काष्ठा vm_area_काष्ठा *vma;
	पूर्णांक error;

	अगर (arg5 || (arg4 && (opt != PR_SET_MM_AUXV &&
			      opt != PR_SET_MM_MAP &&
			      opt != PR_SET_MM_MAP_SIZE)))
		वापस -EINVAL;

#अगर_घोषित CONFIG_CHECKPOINT_RESTORE
	अगर (opt == PR_SET_MM_MAP || opt == PR_SET_MM_MAP_SIZE)
		वापस prctl_set_mm_map(opt, (स्थिर व्योम __user *)addr, arg4);
#पूर्ण_अगर

	अगर (!capable(CAP_SYS_RESOURCE))
		वापस -EPERM;

	अगर (opt == PR_SET_MM_EXE_खाता)
		वापस prctl_set_mm_exe_file(mm, (अचिन्हित पूर्णांक)addr);

	अगर (opt == PR_SET_MM_AUXV)
		वापस prctl_set_auxv(mm, addr, arg4);

	अगर (addr >= TASK_SIZE || addr < mmap_min_addr)
		वापस -EINVAL;

	error = -EINVAL;

	/*
	 * arg_lock protects concurrent updates of arg boundaries, we need
	 * mmap_lock क्रम a) concurrent sys_brk, b) finding VMA क्रम addr
	 * validation.
	 */
	mmap_पढ़ो_lock(mm);
	vma = find_vma(mm, addr);

	spin_lock(&mm->arg_lock);
	prctl_map.start_code	= mm->start_code;
	prctl_map.end_code	= mm->end_code;
	prctl_map.start_data	= mm->start_data;
	prctl_map.end_data	= mm->end_data;
	prctl_map.start_brk	= mm->start_brk;
	prctl_map.brk		= mm->brk;
	prctl_map.start_stack	= mm->start_stack;
	prctl_map.arg_start	= mm->arg_start;
	prctl_map.arg_end	= mm->arg_end;
	prctl_map.env_start	= mm->env_start;
	prctl_map.env_end	= mm->env_end;

	चयन (opt) अणु
	हाल PR_SET_MM_START_CODE:
		prctl_map.start_code = addr;
		अवरोध;
	हाल PR_SET_MM_END_CODE:
		prctl_map.end_code = addr;
		अवरोध;
	हाल PR_SET_MM_START_DATA:
		prctl_map.start_data = addr;
		अवरोध;
	हाल PR_SET_MM_END_DATA:
		prctl_map.end_data = addr;
		अवरोध;
	हाल PR_SET_MM_START_STACK:
		prctl_map.start_stack = addr;
		अवरोध;
	हाल PR_SET_MM_START_BRK:
		prctl_map.start_brk = addr;
		अवरोध;
	हाल PR_SET_MM_BRK:
		prctl_map.brk = addr;
		अवरोध;
	हाल PR_SET_MM_ARG_START:
		prctl_map.arg_start = addr;
		अवरोध;
	हाल PR_SET_MM_ARG_END:
		prctl_map.arg_end = addr;
		अवरोध;
	हाल PR_SET_MM_ENV_START:
		prctl_map.env_start = addr;
		अवरोध;
	हाल PR_SET_MM_ENV_END:
		prctl_map.env_end = addr;
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	error = validate_prctl_map_addr(&prctl_map);
	अगर (error)
		जाओ out;

	चयन (opt) अणु
	/*
	 * If command line arguments and environment
	 * are placed somewhere अन्यथा on stack, we can
	 * set them up here, ARG_START/END to setup
	 * command line arguments and ENV_START/END
	 * क्रम environment.
	 */
	हाल PR_SET_MM_START_STACK:
	हाल PR_SET_MM_ARG_START:
	हाल PR_SET_MM_ARG_END:
	हाल PR_SET_MM_ENV_START:
	हाल PR_SET_MM_ENV_END:
		अगर (!vma) अणु
			error = -EFAULT;
			जाओ out;
		पूर्ण
	पूर्ण

	mm->start_code	= prctl_map.start_code;
	mm->end_code	= prctl_map.end_code;
	mm->start_data	= prctl_map.start_data;
	mm->end_data	= prctl_map.end_data;
	mm->start_brk	= prctl_map.start_brk;
	mm->brk		= prctl_map.brk;
	mm->start_stack	= prctl_map.start_stack;
	mm->arg_start	= prctl_map.arg_start;
	mm->arg_end	= prctl_map.arg_end;
	mm->env_start	= prctl_map.env_start;
	mm->env_end	= prctl_map.env_end;

	error = 0;
out:
	spin_unlock(&mm->arg_lock);
	mmap_पढ़ो_unlock(mm);
	वापस error;
पूर्ण

#अगर_घोषित CONFIG_CHECKPOINT_RESTORE
अटल पूर्णांक prctl_get_tid_address(काष्ठा task_काष्ठा *me, पूर्णांक __user * __user *tid_addr)
अणु
	वापस put_user(me->clear_child_tid, tid_addr);
पूर्ण
#अन्यथा
अटल पूर्णांक prctl_get_tid_address(काष्ठा task_काष्ठा *me, पूर्णांक __user * __user *tid_addr)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक propagate_has_child_subreaper(काष्ठा task_काष्ठा *p, व्योम *data)
अणु
	/*
	 * If task has has_child_subreaper - all its descendants
	 * alपढ़ोy have these flag too and new descendants will
	 * inherit it on विभाजन, skip them.
	 *
	 * If we've found child_reaper - skip descendants in
	 * it's subtree as they will never get out pidns.
	 */
	अगर (p->संकेत->has_child_subreaper ||
	    is_child_reaper(task_pid(p)))
		वापस 0;

	p->संकेत->has_child_subreaper = 1;
	वापस 1;
पूर्ण

पूर्णांक __weak arch_prctl_spec_ctrl_get(काष्ठा task_काष्ठा *t, अचिन्हित दीर्घ which)
अणु
	वापस -EINVAL;
पूर्ण

पूर्णांक __weak arch_prctl_spec_ctrl_set(काष्ठा task_काष्ठा *t, अचिन्हित दीर्घ which,
				    अचिन्हित दीर्घ ctrl)
अणु
	वापस -EINVAL;
पूर्ण

#घोषणा PR_IO_FLUSHER (PF_MEMALLOC_NOIO | PF_LOCAL_THROTTLE)

SYSCALL_DEFINE5(prctl, पूर्णांक, option, अचिन्हित दीर्घ, arg2, अचिन्हित दीर्घ, arg3,
		अचिन्हित दीर्घ, arg4, अचिन्हित दीर्घ, arg5)
अणु
	काष्ठा task_काष्ठा *me = current;
	अचिन्हित अक्षर comm[माप(me->comm)];
	दीर्घ error;

	error = security_task_prctl(option, arg2, arg3, arg4, arg5);
	अगर (error != -ENOSYS)
		वापस error;

	error = 0;
	चयन (option) अणु
	हाल PR_SET_PDEATHSIG:
		अगर (!valid_संकेत(arg2)) अणु
			error = -EINVAL;
			अवरोध;
		पूर्ण
		me->pdeath_संकेत = arg2;
		अवरोध;
	हाल PR_GET_PDEATHSIG:
		error = put_user(me->pdeath_संकेत, (पूर्णांक __user *)arg2);
		अवरोध;
	हाल PR_GET_DUMPABLE:
		error = get_dumpable(me->mm);
		अवरोध;
	हाल PR_SET_DUMPABLE:
		अगर (arg2 != SUID_DUMP_DISABLE && arg2 != SUID_DUMP_USER) अणु
			error = -EINVAL;
			अवरोध;
		पूर्ण
		set_dumpable(me->mm, arg2);
		अवरोध;

	हाल PR_SET_UNALIGN:
		error = SET_UNALIGN_CTL(me, arg2);
		अवरोध;
	हाल PR_GET_UNALIGN:
		error = GET_UNALIGN_CTL(me, arg2);
		अवरोध;
	हाल PR_SET_FPEMU:
		error = SET_FPEMU_CTL(me, arg2);
		अवरोध;
	हाल PR_GET_FPEMU:
		error = GET_FPEMU_CTL(me, arg2);
		अवरोध;
	हाल PR_SET_FPEXC:
		error = SET_FPEXC_CTL(me, arg2);
		अवरोध;
	हाल PR_GET_FPEXC:
		error = GET_FPEXC_CTL(me, arg2);
		अवरोध;
	हाल PR_GET_TIMING:
		error = PR_TIMING_STATISTICAL;
		अवरोध;
	हाल PR_SET_TIMING:
		अगर (arg2 != PR_TIMING_STATISTICAL)
			error = -EINVAL;
		अवरोध;
	हाल PR_SET_NAME:
		comm[माप(me->comm) - 1] = 0;
		अगर (म_नकलन_from_user(comm, (अक्षर __user *)arg2,
				      माप(me->comm) - 1) < 0)
			वापस -EFAULT;
		set_task_comm(me, comm);
		proc_comm_connector(me);
		अवरोध;
	हाल PR_GET_NAME:
		get_task_comm(comm, me);
		अगर (copy_to_user((अक्षर __user *)arg2, comm, माप(comm)))
			वापस -EFAULT;
		अवरोध;
	हाल PR_GET_ENDIAN:
		error = GET_ENDIAN(me, arg2);
		अवरोध;
	हाल PR_SET_ENDIAN:
		error = SET_ENDIAN(me, arg2);
		अवरोध;
	हाल PR_GET_SECCOMP:
		error = prctl_get_seccomp();
		अवरोध;
	हाल PR_SET_SECCOMP:
		error = prctl_set_seccomp(arg2, (अक्षर __user *)arg3);
		अवरोध;
	हाल PR_GET_TSC:
		error = GET_TSC_CTL(arg2);
		अवरोध;
	हाल PR_SET_TSC:
		error = SET_TSC_CTL(arg2);
		अवरोध;
	हाल PR_TASK_PERF_EVENTS_DISABLE:
		error = perf_event_task_disable();
		अवरोध;
	हाल PR_TASK_PERF_EVENTS_ENABLE:
		error = perf_event_task_enable();
		अवरोध;
	हाल PR_GET_TIMERSLACK:
		अगर (current->समयr_slack_ns > अच_दीर्घ_उच्च)
			error = अच_दीर्घ_उच्च;
		अन्यथा
			error = current->समयr_slack_ns;
		अवरोध;
	हाल PR_SET_TIMERSLACK:
		अगर (arg2 <= 0)
			current->समयr_slack_ns =
					current->शेष_समयr_slack_ns;
		अन्यथा
			current->समयr_slack_ns = arg2;
		अवरोध;
	हाल PR_MCE_KILL:
		अगर (arg4 | arg5)
			वापस -EINVAL;
		चयन (arg2) अणु
		हाल PR_MCE_KILL_CLEAR:
			अगर (arg3 != 0)
				वापस -EINVAL;
			current->flags &= ~PF_MCE_PROCESS;
			अवरोध;
		हाल PR_MCE_KILL_SET:
			current->flags |= PF_MCE_PROCESS;
			अगर (arg3 == PR_MCE_KILL_EARLY)
				current->flags |= PF_MCE_EARLY;
			अन्यथा अगर (arg3 == PR_MCE_KILL_LATE)
				current->flags &= ~PF_MCE_EARLY;
			अन्यथा अगर (arg3 == PR_MCE_KILL_DEFAULT)
				current->flags &=
						~(PF_MCE_EARLY|PF_MCE_PROCESS);
			अन्यथा
				वापस -EINVAL;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PR_MCE_KILL_GET:
		अगर (arg2 | arg3 | arg4 | arg5)
			वापस -EINVAL;
		अगर (current->flags & PF_MCE_PROCESS)
			error = (current->flags & PF_MCE_EARLY) ?
				PR_MCE_KILL_EARLY : PR_MCE_KILL_LATE;
		अन्यथा
			error = PR_MCE_KILL_DEFAULT;
		अवरोध;
	हाल PR_SET_MM:
		error = prctl_set_mm(arg2, arg3, arg4, arg5);
		अवरोध;
	हाल PR_GET_TID_ADDRESS:
		error = prctl_get_tid_address(me, (पूर्णांक __user * __user *)arg2);
		अवरोध;
	हाल PR_SET_CHILD_SUBREAPER:
		me->संकेत->is_child_subreaper = !!arg2;
		अगर (!arg2)
			अवरोध;

		walk_process_tree(me, propagate_has_child_subreaper, शून्य);
		अवरोध;
	हाल PR_GET_CHILD_SUBREAPER:
		error = put_user(me->संकेत->is_child_subreaper,
				 (पूर्णांक __user *)arg2);
		अवरोध;
	हाल PR_SET_NO_NEW_PRIVS:
		अगर (arg2 != 1 || arg3 || arg4 || arg5)
			वापस -EINVAL;

		task_set_no_new_privs(current);
		अवरोध;
	हाल PR_GET_NO_NEW_PRIVS:
		अगर (arg2 || arg3 || arg4 || arg5)
			वापस -EINVAL;
		वापस task_no_new_privs(current) ? 1 : 0;
	हाल PR_GET_THP_DISABLE:
		अगर (arg2 || arg3 || arg4 || arg5)
			वापस -EINVAL;
		error = !!test_bit(MMF_DISABLE_THP, &me->mm->flags);
		अवरोध;
	हाल PR_SET_THP_DISABLE:
		अगर (arg3 || arg4 || arg5)
			वापस -EINVAL;
		अगर (mmap_ग_लिखो_lock_समाप्तable(me->mm))
			वापस -EINTR;
		अगर (arg2)
			set_bit(MMF_DISABLE_THP, &me->mm->flags);
		अन्यथा
			clear_bit(MMF_DISABLE_THP, &me->mm->flags);
		mmap_ग_लिखो_unlock(me->mm);
		अवरोध;
	हाल PR_MPX_ENABLE_MANAGEMENT:
	हाल PR_MPX_DISABLE_MANAGEMENT:
		/* No दीर्घer implemented: */
		वापस -EINVAL;
	हाल PR_SET_FP_MODE:
		error = SET_FP_MODE(me, arg2);
		अवरोध;
	हाल PR_GET_FP_MODE:
		error = GET_FP_MODE(me);
		अवरोध;
	हाल PR_SVE_SET_VL:
		error = SVE_SET_VL(arg2);
		अवरोध;
	हाल PR_SVE_GET_VL:
		error = SVE_GET_VL();
		अवरोध;
	हाल PR_GET_SPECULATION_CTRL:
		अगर (arg3 || arg4 || arg5)
			वापस -EINVAL;
		error = arch_prctl_spec_ctrl_get(me, arg2);
		अवरोध;
	हाल PR_SET_SPECULATION_CTRL:
		अगर (arg4 || arg5)
			वापस -EINVAL;
		error = arch_prctl_spec_ctrl_set(me, arg2, arg3);
		अवरोध;
	हाल PR_PAC_RESET_KEYS:
		अगर (arg3 || arg4 || arg5)
			वापस -EINVAL;
		error = PAC_RESET_KEYS(me, arg2);
		अवरोध;
	हाल PR_PAC_SET_ENABLED_KEYS:
		अगर (arg4 || arg5)
			वापस -EINVAL;
		error = PAC_SET_ENABLED_KEYS(me, arg2, arg3);
		अवरोध;
	हाल PR_PAC_GET_ENABLED_KEYS:
		अगर (arg2 || arg3 || arg4 || arg5)
			वापस -EINVAL;
		error = PAC_GET_ENABLED_KEYS(me);
		अवरोध;
	हाल PR_SET_TAGGED_ADDR_CTRL:
		अगर (arg3 || arg4 || arg5)
			वापस -EINVAL;
		error = SET_TAGGED_ADDR_CTRL(arg2);
		अवरोध;
	हाल PR_GET_TAGGED_ADDR_CTRL:
		अगर (arg2 || arg3 || arg4 || arg5)
			वापस -EINVAL;
		error = GET_TAGGED_ADDR_CTRL();
		अवरोध;
	हाल PR_SET_IO_FLUSHER:
		अगर (!capable(CAP_SYS_RESOURCE))
			वापस -EPERM;

		अगर (arg3 || arg4 || arg5)
			वापस -EINVAL;

		अगर (arg2 == 1)
			current->flags |= PR_IO_FLUSHER;
		अन्यथा अगर (!arg2)
			current->flags &= ~PR_IO_FLUSHER;
		अन्यथा
			वापस -EINVAL;
		अवरोध;
	हाल PR_GET_IO_FLUSHER:
		अगर (!capable(CAP_SYS_RESOURCE))
			वापस -EPERM;

		अगर (arg2 || arg3 || arg4 || arg5)
			वापस -EINVAL;

		error = (current->flags & PR_IO_FLUSHER) == PR_IO_FLUSHER;
		अवरोध;
	हाल PR_SET_SYSCALL_USER_DISPATCH:
		error = set_syscall_user_dispatch(arg2, arg3, arg4,
						  (अक्षर __user *) arg5);
		अवरोध;
	शेष:
		error = -EINVAL;
		अवरोध;
	पूर्ण
	वापस error;
पूर्ण

SYSCALL_DEFINE3(अ_लोpu, अचिन्हित __user *, cpup, अचिन्हित __user *, nodep,
		काष्ठा अ_लोpu_cache __user *, unused)
अणु
	पूर्णांक err = 0;
	पूर्णांक cpu = raw_smp_processor_id();

	अगर (cpup)
		err |= put_user(cpu, cpup);
	अगर (nodep)
		err |= put_user(cpu_to_node(cpu), nodep);
	वापस err ? -EFAULT : 0;
पूर्ण

/**
 * करो_sysinfo - fill in sysinfo काष्ठा
 * @info: poपूर्णांकer to buffer to fill
 */
अटल पूर्णांक करो_sysinfo(काष्ठा sysinfo *info)
अणु
	अचिन्हित दीर्घ mem_total, sav_total;
	अचिन्हित पूर्णांक mem_unit, bitcount;
	काष्ठा बारpec64 tp;

	स_रखो(info, 0, माप(काष्ठा sysinfo));

	kसमय_get_bootसमय_प्रकारs64(&tp);
	समयns_add_bootसमय(&tp);
	info->upसमय = tp.tv_sec + (tp.tv_nsec ? 1 : 0);

	get_avenrun(info->loads, 0, SI_LOAD_SHIFT - FSHIFT);

	info->procs = nr_thपढ़ोs;

	si_meminfo(info);
	si_swapinfo(info);

	/*
	 * If the sum of all the available memory (i.e. ram + swap)
	 * is less than can be stored in a 32 bit अचिन्हित दीर्घ then
	 * we can be binary compatible with 2.2.x kernels.  If not,
	 * well, in that हाल 2.2.x was broken anyways...
	 *
	 *  -Erik Andersen <andersee@debian.org>
	 */

	mem_total = info->totalram + info->totalswap;
	अगर (mem_total < info->totalram || mem_total < info->totalswap)
		जाओ out;
	bitcount = 0;
	mem_unit = info->mem_unit;
	जबतक (mem_unit > 1) अणु
		bitcount++;
		mem_unit >>= 1;
		sav_total = mem_total;
		mem_total <<= 1;
		अगर (mem_total < sav_total)
			जाओ out;
	पूर्ण

	/*
	 * If mem_total did not overflow, multiply all memory values by
	 * info->mem_unit and set it to 1.  This leaves things compatible
	 * with 2.2.x, and also retains compatibility with earlier 2.4.x
	 * kernels...
	 */

	info->mem_unit = 1;
	info->totalram <<= bitcount;
	info->मुक्तram <<= bitcount;
	info->sharedram <<= bitcount;
	info->bufferram <<= bitcount;
	info->totalswap <<= bitcount;
	info->मुक्तswap <<= bitcount;
	info->totalhigh <<= bitcount;
	info->मुक्तhigh <<= bitcount;

out:
	वापस 0;
पूर्ण

SYSCALL_DEFINE1(sysinfo, काष्ठा sysinfo __user *, info)
अणु
	काष्ठा sysinfo val;

	करो_sysinfo(&val);

	अगर (copy_to_user(info, &val, माप(काष्ठा sysinfo)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
काष्ठा compat_sysinfo अणु
	s32 upसमय;
	u32 loads[3];
	u32 totalram;
	u32 मुक्तram;
	u32 sharedram;
	u32 bufferram;
	u32 totalswap;
	u32 मुक्तswap;
	u16 procs;
	u16 pad;
	u32 totalhigh;
	u32 मुक्तhigh;
	u32 mem_unit;
	अक्षर _f[20-2*माप(u32)-माप(पूर्णांक)];
पूर्ण;

COMPAT_SYSCALL_DEFINE1(sysinfo, काष्ठा compat_sysinfo __user *, info)
अणु
	काष्ठा sysinfo s;
	काष्ठा compat_sysinfo s_32;

	करो_sysinfo(&s);

	/* Check to see अगर any memory value is too large क्रम 32-bit and scale
	 *  करोwn अगर needed
	 */
	अगर (upper_32_bits(s.totalram) || upper_32_bits(s.totalswap)) अणु
		पूर्णांक bitcount = 0;

		जबतक (s.mem_unit < PAGE_SIZE) अणु
			s.mem_unit <<= 1;
			bitcount++;
		पूर्ण

		s.totalram >>= bitcount;
		s.मुक्तram >>= bitcount;
		s.sharedram >>= bitcount;
		s.bufferram >>= bitcount;
		s.totalswap >>= bitcount;
		s.मुक्तswap >>= bitcount;
		s.totalhigh >>= bitcount;
		s.मुक्तhigh >>= bitcount;
	पूर्ण

	स_रखो(&s_32, 0, माप(s_32));
	s_32.upसमय = s.upसमय;
	s_32.loads[0] = s.loads[0];
	s_32.loads[1] = s.loads[1];
	s_32.loads[2] = s.loads[2];
	s_32.totalram = s.totalram;
	s_32.मुक्तram = s.मुक्तram;
	s_32.sharedram = s.sharedram;
	s_32.bufferram = s.bufferram;
	s_32.totalswap = s.totalswap;
	s_32.मुक्तswap = s.मुक्तswap;
	s_32.procs = s.procs;
	s_32.totalhigh = s.totalhigh;
	s_32.मुक्तhigh = s.मुक्तhigh;
	s_32.mem_unit = s.mem_unit;
	अगर (copy_to_user(info, &s_32, माप(s_32)))
		वापस -EFAULT;
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_COMPAT */
