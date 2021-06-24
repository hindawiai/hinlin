<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/kernel/capability.c
 *
 * Copyright (C) 1997  Andrew Main <zefram@fysh.org>
 *
 * Integrated पूर्णांकo 2.1.97+,  Andrew G. Morgan <morgan@kernel.org>
 * 30 May 2002:	Cleanup, Robert M. Love <rml@tech9.net>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/audit.h>
#समावेश <linux/capability.h>
#समावेश <linux/mm.h>
#समावेश <linux/export.h>
#समावेश <linux/security.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/pid_namespace.h>
#समावेश <linux/user_namespace.h>
#समावेश <linux/uaccess.h>

/*
 * Leveraged क्रम setting/resetting capabilities
 */

स्थिर kernel_cap_t __cap_empty_set = CAP_EMPTY_SET;
EXPORT_SYMBOL(__cap_empty_set);

पूर्णांक file_caps_enabled = 1;

अटल पूर्णांक __init file_caps_disable(अक्षर *str)
अणु
	file_caps_enabled = 0;
	वापस 1;
पूर्ण
__setup("no_file_caps", file_caps_disable);

#अगर_घोषित CONFIG_MULTIUSER
/*
 * More recent versions of libcap are available from:
 *
 *   http://www.kernel.org/pub/linux/libs/security/linux-privs/
 */

अटल व्योम warn_legacy_capability_use(व्योम)
अणु
	अक्षर name[माप(current->comm)];

	pr_info_once("warning: `%s' uses 32-bit capabilities (legacy support in use)\n",
		     get_task_comm(name, current));
पूर्ण

/*
 * Version 2 capabilities worked fine, but the linux/capability.h file
 * that accompanied their पूर्णांकroduction encouraged their use without
 * the necessary user-space source code changes. As such, we have
 * created a version 3 with equivalent functionality to version 2, but
 * with a header change to protect legacy source code from using
 * version 2 when it wanted to use version 1. If your प्रणाली has code
 * that trips the following warning, it is using version 2 specअगरic
 * capabilities and may be करोing so insecurely.
 *
 * The remedy is to either upgrade your version of libcap (to 2.10+,
 * अगर the application is linked against it), or recompile your
 * application with modern kernel headers and this warning will go
 * away.
 */

अटल व्योम warn_deprecated_v2(व्योम)
अणु
	अक्षर name[माप(current->comm)];

	pr_info_once("warning: `%s' uses deprecated v2 capabilities in a way that may be insecure\n",
		     get_task_comm(name, current));
पूर्ण

/*
 * Version check. Return the number of u32s in each capability flag
 * array, or a negative value on error.
 */
अटल पूर्णांक cap_validate_magic(cap_user_header_t header, अचिन्हित *tocopy)
अणु
	__u32 version;

	अगर (get_user(version, &header->version))
		वापस -EFAULT;

	चयन (version) अणु
	हाल _LINUX_CAPABILITY_VERSION_1:
		warn_legacy_capability_use();
		*tocopy = _LINUX_CAPABILITY_U32S_1;
		अवरोध;
	हाल _LINUX_CAPABILITY_VERSION_2:
		warn_deprecated_v2();
		fallthrough;	/* v3 is otherwise equivalent to v2 */
	हाल _LINUX_CAPABILITY_VERSION_3:
		*tocopy = _LINUX_CAPABILITY_U32S_3;
		अवरोध;
	शेष:
		अगर (put_user((u32)_KERNEL_CAPABILITY_VERSION, &header->version))
			वापस -EFAULT;
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * The only thing that can change the capabilities of the current
 * process is the current process. As such, we can't be in this code
 * at the same समय as we are in the process of setting capabilities
 * in this process. The net result is that we can limit our use of
 * locks to when we are पढ़ोing the caps of another process.
 */
अटल अंतरभूत पूर्णांक cap_get_target_pid(pid_t pid, kernel_cap_t *pEp,
				     kernel_cap_t *pIp, kernel_cap_t *pPp)
अणु
	पूर्णांक ret;

	अगर (pid && (pid != task_pid_vnr(current))) अणु
		काष्ठा task_काष्ठा *target;

		rcu_पढ़ो_lock();

		target = find_task_by_vpid(pid);
		अगर (!target)
			ret = -ESRCH;
		अन्यथा
			ret = security_capget(target, pEp, pIp, pPp);

		rcu_पढ़ो_unlock();
	पूर्ण अन्यथा
		ret = security_capget(current, pEp, pIp, pPp);

	वापस ret;
पूर्ण

/**
 * sys_capget - get the capabilities of a given process.
 * @header: poपूर्णांकer to काष्ठा that contains capability version and
 *	target pid data
 * @dataptr: poपूर्णांकer to काष्ठा that contains the effective, permitted,
 *	and inheritable capabilities that are वापसed
 *
 * Returns 0 on success and < 0 on error.
 */
SYSCALL_DEFINE2(capget, cap_user_header_t, header, cap_user_data_t, dataptr)
अणु
	पूर्णांक ret = 0;
	pid_t pid;
	अचिन्हित tocopy;
	kernel_cap_t pE, pI, pP;

	ret = cap_validate_magic(header, &tocopy);
	अगर ((dataptr == शून्य) || (ret != 0))
		वापस ((dataptr == शून्य) && (ret == -EINVAL)) ? 0 : ret;

	अगर (get_user(pid, &header->pid))
		वापस -EFAULT;

	अगर (pid < 0)
		वापस -EINVAL;

	ret = cap_get_target_pid(pid, &pE, &pI, &pP);
	अगर (!ret) अणु
		काष्ठा __user_cap_data_काष्ठा kdata[_KERNEL_CAPABILITY_U32S];
		अचिन्हित i;

		क्रम (i = 0; i < tocopy; i++) अणु
			kdata[i].effective = pE.cap[i];
			kdata[i].permitted = pP.cap[i];
			kdata[i].inheritable = pI.cap[i];
		पूर्ण

		/*
		 * Note, in the हाल, tocopy < _KERNEL_CAPABILITY_U32S,
		 * we silently drop the upper capabilities here. This
		 * has the effect of making older libcap
		 * implementations implicitly drop upper capability
		 * bits when they perक्रमm a: capget/modअगरy/capset
		 * sequence.
		 *
		 * This behavior is considered fail-safe
		 * behavior. Upgrading the application to a newer
		 * version of libcap will enable access to the newer
		 * capabilities.
		 *
		 * An alternative would be to वापस an error here
		 * (-दुस्फल), but that causes legacy applications to
		 * unexpectedly fail; the capget/modअगरy/capset पातs
		 * beक्रमe modअगरication is attempted and the application
		 * fails.
		 */
		अगर (copy_to_user(dataptr, kdata, tocopy
				 * माप(काष्ठा __user_cap_data_काष्ठा))) अणु
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/**
 * sys_capset - set capabilities क्रम a process or (*) a group of processes
 * @header: poपूर्णांकer to काष्ठा that contains capability version and
 *	target pid data
 * @data: poपूर्णांकer to काष्ठा that contains the effective, permitted,
 *	and inheritable capabilities
 *
 * Set capabilities क्रम the current process only.  The ability to any other
 * process(es) has been deprecated and हटाओd.
 *
 * The restrictions on setting capabilities are specअगरied as:
 *
 * I: any उठाओd capabilities must be a subset of the old permitted
 * P: any उठाओd capabilities must be a subset of the old permitted
 * E: must be set to a subset of new permitted
 *
 * Returns 0 on success and < 0 on error.
 */
SYSCALL_DEFINE2(capset, cap_user_header_t, header, स्थिर cap_user_data_t, data)
अणु
	काष्ठा __user_cap_data_काष्ठा kdata[_KERNEL_CAPABILITY_U32S];
	अचिन्हित i, tocopy, copybytes;
	kernel_cap_t inheritable, permitted, effective;
	काष्ठा cred *new;
	पूर्णांक ret;
	pid_t pid;

	ret = cap_validate_magic(header, &tocopy);
	अगर (ret != 0)
		वापस ret;

	अगर (get_user(pid, &header->pid))
		वापस -EFAULT;

	/* may only affect current now */
	अगर (pid != 0 && pid != task_pid_vnr(current))
		वापस -EPERM;

	copybytes = tocopy * माप(काष्ठा __user_cap_data_काष्ठा);
	अगर (copybytes > माप(kdata))
		वापस -EFAULT;

	अगर (copy_from_user(&kdata, data, copybytes))
		वापस -EFAULT;

	क्रम (i = 0; i < tocopy; i++) अणु
		effective.cap[i] = kdata[i].effective;
		permitted.cap[i] = kdata[i].permitted;
		inheritable.cap[i] = kdata[i].inheritable;
	पूर्ण
	जबतक (i < _KERNEL_CAPABILITY_U32S) अणु
		effective.cap[i] = 0;
		permitted.cap[i] = 0;
		inheritable.cap[i] = 0;
		i++;
	पूर्ण

	effective.cap[CAP_LAST_U32] &= CAP_LAST_U32_VALID_MASK;
	permitted.cap[CAP_LAST_U32] &= CAP_LAST_U32_VALID_MASK;
	inheritable.cap[CAP_LAST_U32] &= CAP_LAST_U32_VALID_MASK;

	new = prepare_creds();
	अगर (!new)
		वापस -ENOMEM;

	ret = security_capset(new, current_cred(),
			      &effective, &inheritable, &permitted);
	अगर (ret < 0)
		जाओ error;

	audit_log_capset(new, current_cred());

	वापस commit_creds(new);

error:
	पात_creds(new);
	वापस ret;
पूर्ण

/**
 * has_ns_capability - Does a task have a capability in a specअगरic user ns
 * @t: The task in question
 * @ns: target user namespace
 * @cap: The capability to be tested क्रम
 *
 * Return true अगर the specअगरied task has the given superior capability
 * currently in effect to the specअगरied user namespace, false अगर not.
 *
 * Note that this करोes not set PF_SUPERPRIV on the task.
 */
bool has_ns_capability(काष्ठा task_काष्ठा *t,
		       काष्ठा user_namespace *ns, पूर्णांक cap)
अणु
	पूर्णांक ret;

	rcu_पढ़ो_lock();
	ret = security_capable(__task_cred(t), ns, cap, CAP_OPT_NONE);
	rcu_पढ़ो_unlock();

	वापस (ret == 0);
पूर्ण

/**
 * has_capability - Does a task have a capability in init_user_ns
 * @t: The task in question
 * @cap: The capability to be tested क्रम
 *
 * Return true अगर the specअगरied task has the given superior capability
 * currently in effect to the initial user namespace, false अगर not.
 *
 * Note that this करोes not set PF_SUPERPRIV on the task.
 */
bool has_capability(काष्ठा task_काष्ठा *t, पूर्णांक cap)
अणु
	वापस has_ns_capability(t, &init_user_ns, cap);
पूर्ण
EXPORT_SYMBOL(has_capability);

/**
 * has_ns_capability_noaudit - Does a task have a capability (unaudited)
 * in a specअगरic user ns.
 * @t: The task in question
 * @ns: target user namespace
 * @cap: The capability to be tested क्रम
 *
 * Return true अगर the specअगरied task has the given superior capability
 * currently in effect to the specअगरied user namespace, false अगर not.
 * Do not ग_लिखो an audit message क्रम the check.
 *
 * Note that this करोes not set PF_SUPERPRIV on the task.
 */
bool has_ns_capability_noaudit(काष्ठा task_काष्ठा *t,
			       काष्ठा user_namespace *ns, पूर्णांक cap)
अणु
	पूर्णांक ret;

	rcu_पढ़ो_lock();
	ret = security_capable(__task_cred(t), ns, cap, CAP_OPT_NOAUDIT);
	rcu_पढ़ो_unlock();

	वापस (ret == 0);
पूर्ण

/**
 * has_capability_noaudit - Does a task have a capability (unaudited) in the
 * initial user ns
 * @t: The task in question
 * @cap: The capability to be tested क्रम
 *
 * Return true अगर the specअगरied task has the given superior capability
 * currently in effect to init_user_ns, false अगर not.  Don't ग_लिखो an
 * audit message क्रम the check.
 *
 * Note that this करोes not set PF_SUPERPRIV on the task.
 */
bool has_capability_noaudit(काष्ठा task_काष्ठा *t, पूर्णांक cap)
अणु
	वापस has_ns_capability_noaudit(t, &init_user_ns, cap);
पूर्ण

अटल bool ns_capable_common(काष्ठा user_namespace *ns,
			      पूर्णांक cap,
			      अचिन्हित पूर्णांक opts)
अणु
	पूर्णांक capable;

	अगर (unlikely(!cap_valid(cap))) अणु
		pr_crit("capable() called with invalid cap=%u\n", cap);
		BUG();
	पूर्ण

	capable = security_capable(current_cred(), ns, cap, opts);
	अगर (capable == 0) अणु
		current->flags |= PF_SUPERPRIV;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * ns_capable - Determine अगर the current task has a superior capability in effect
 * @ns:  The usernamespace we want the capability in
 * @cap: The capability to be tested क्रम
 *
 * Return true अगर the current task has the given superior capability currently
 * available क्रम use, false अगर not.
 *
 * This sets PF_SUPERPRIV on the task अगर the capability is available on the
 * assumption that it's about to be used.
 */
bool ns_capable(काष्ठा user_namespace *ns, पूर्णांक cap)
अणु
	वापस ns_capable_common(ns, cap, CAP_OPT_NONE);
पूर्ण
EXPORT_SYMBOL(ns_capable);

/**
 * ns_capable_noaudit - Determine अगर the current task has a superior capability
 * (unaudited) in effect
 * @ns:  The usernamespace we want the capability in
 * @cap: The capability to be tested क्रम
 *
 * Return true अगर the current task has the given superior capability currently
 * available क्रम use, false अगर not.
 *
 * This sets PF_SUPERPRIV on the task अगर the capability is available on the
 * assumption that it's about to be used.
 */
bool ns_capable_noaudit(काष्ठा user_namespace *ns, पूर्णांक cap)
अणु
	वापस ns_capable_common(ns, cap, CAP_OPT_NOAUDIT);
पूर्ण
EXPORT_SYMBOL(ns_capable_noaudit);

/**
 * ns_capable_setid - Determine अगर the current task has a superior capability
 * in effect, जबतक संकेतling that this check is being करोne from within a
 * setid or setgroups syscall.
 * @ns:  The usernamespace we want the capability in
 * @cap: The capability to be tested क्रम
 *
 * Return true अगर the current task has the given superior capability currently
 * available क्रम use, false अगर not.
 *
 * This sets PF_SUPERPRIV on the task अगर the capability is available on the
 * assumption that it's about to be used.
 */
bool ns_capable_setid(काष्ठा user_namespace *ns, पूर्णांक cap)
अणु
	वापस ns_capable_common(ns, cap, CAP_OPT_INSETID);
पूर्ण
EXPORT_SYMBOL(ns_capable_setid);

/**
 * capable - Determine अगर the current task has a superior capability in effect
 * @cap: The capability to be tested क्रम
 *
 * Return true अगर the current task has the given superior capability currently
 * available क्रम use, false अगर not.
 *
 * This sets PF_SUPERPRIV on the task अगर the capability is available on the
 * assumption that it's about to be used.
 */
bool capable(पूर्णांक cap)
अणु
	वापस ns_capable(&init_user_ns, cap);
पूर्ण
EXPORT_SYMBOL(capable);
#पूर्ण_अगर /* CONFIG_MULTIUSER */

/**
 * file_ns_capable - Determine अगर the file's खोलोer had a capability in effect
 * @file:  The file we want to check
 * @ns:  The usernamespace we want the capability in
 * @cap: The capability to be tested क्रम
 *
 * Return true अगर task that खोलोed the file had a capability in effect
 * when the file was खोलोed.
 *
 * This करोes not set PF_SUPERPRIV because the caller may not
 * actually be privileged.
 */
bool file_ns_capable(स्थिर काष्ठा file *file, काष्ठा user_namespace *ns,
		     पूर्णांक cap)
अणु

	अगर (WARN_ON_ONCE(!cap_valid(cap)))
		वापस false;

	अगर (security_capable(file->f_cred, ns, cap, CAP_OPT_NONE) == 0)
		वापस true;

	वापस false;
पूर्ण
EXPORT_SYMBOL(file_ns_capable);

/**
 * privileged_wrt_inode_uidgid - Do capabilities in the namespace work over the inode?
 * @ns: The user namespace in question
 * @inode: The inode in question
 *
 * Return true अगर the inode uid and gid are within the namespace.
 */
bool privileged_wrt_inode_uidgid(काष्ठा user_namespace *ns,
				 काष्ठा user_namespace *mnt_userns,
				 स्थिर काष्ठा inode *inode)
अणु
	वापस kuid_has_mapping(ns, i_uid_पूर्णांकo_mnt(mnt_userns, inode)) &&
	       kgid_has_mapping(ns, i_gid_पूर्णांकo_mnt(mnt_userns, inode));
पूर्ण

/**
 * capable_wrt_inode_uidgid - Check nsown_capable and uid and gid mapped
 * @inode: The inode in question
 * @cap: The capability in question
 *
 * Return true अगर the current task has the given capability targeted at
 * its own user namespace and that the given inode's uid and gid are
 * mapped पूर्णांकo the current user namespace.
 */
bool capable_wrt_inode_uidgid(काष्ठा user_namespace *mnt_userns,
			      स्थिर काष्ठा inode *inode, पूर्णांक cap)
अणु
	काष्ठा user_namespace *ns = current_user_ns();

	वापस ns_capable(ns, cap) &&
	       privileged_wrt_inode_uidgid(ns, mnt_userns, inode);
पूर्ण
EXPORT_SYMBOL(capable_wrt_inode_uidgid);

/**
 * ptracer_capable - Determine अगर the ptracer holds CAP_SYS_PTRACE in the namespace
 * @tsk: The task that may be ptraced
 * @ns: The user namespace to search क्रम CAP_SYS_PTRACE in
 *
 * Return true अगर the task that is ptracing the current task had CAP_SYS_PTRACE
 * in the specअगरied user namespace.
 */
bool ptracer_capable(काष्ठा task_काष्ठा *tsk, काष्ठा user_namespace *ns)
अणु
	पूर्णांक ret = 0;  /* An असलent tracer adds no restrictions */
	स्थिर काष्ठा cred *cred;

	rcu_पढ़ो_lock();
	cred = rcu_dereference(tsk->ptracer_cred);
	अगर (cred)
		ret = security_capable(cred, ns, CAP_SYS_PTRACE,
				       CAP_OPT_NOAUDIT);
	rcu_पढ़ो_unlock();
	वापस (ret == 0);
पूर्ण
