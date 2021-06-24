<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	Wrapper functions क्रम 16bit uid back compatibility. All nicely tied
 *	together in the faपूर्णांक hope we can take the out in five years समय.
 */

#समावेश <linux/mm.h>
#समावेश <linux/mman.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/reboot.h>
#समावेश <linux/prctl.h>
#समावेश <linux/capability.h>
#समावेश <linux/init.h>
#समावेश <linux/highuid.h>
#समावेश <linux/security.h>
#समावेश <linux/cred.h>
#समावेश <linux/syscalls.h>

#समावेश <linux/uaccess.h>

#समावेश "uid16.h"

SYSCALL_DEFINE3(chown16, स्थिर अक्षर __user *, filename, old_uid_t, user, old_gid_t, group)
अणु
	वापस ksys_chown(filename, low2highuid(user), low2highgid(group));
पूर्ण

SYSCALL_DEFINE3(lchown16, स्थिर अक्षर __user *, filename, old_uid_t, user, old_gid_t, group)
अणु
	वापस ksys_lchown(filename, low2highuid(user), low2highgid(group));
पूर्ण

SYSCALL_DEFINE3(fchown16, अचिन्हित पूर्णांक, fd, old_uid_t, user, old_gid_t, group)
अणु
	वापस ksys_fchown(fd, low2highuid(user), low2highgid(group));
पूर्ण

SYSCALL_DEFINE2(setregid16, old_gid_t, rgid, old_gid_t, egid)
अणु
	वापस __sys_setregid(low2highgid(rgid), low2highgid(egid));
पूर्ण

SYSCALL_DEFINE1(setgid16, old_gid_t, gid)
अणु
	वापस __sys_setgid(low2highgid(gid));
पूर्ण

SYSCALL_DEFINE2(setreuid16, old_uid_t, ruid, old_uid_t, euid)
अणु
	वापस __sys_setreuid(low2highuid(ruid), low2highuid(euid));
पूर्ण

SYSCALL_DEFINE1(setuid16, old_uid_t, uid)
अणु
	वापस __sys_setuid(low2highuid(uid));
पूर्ण

SYSCALL_DEFINE3(setresuid16, old_uid_t, ruid, old_uid_t, euid, old_uid_t, suid)
अणु
	वापस __sys_setresuid(low2highuid(ruid), low2highuid(euid),
				 low2highuid(suid));
पूर्ण

SYSCALL_DEFINE3(getresuid16, old_uid_t __user *, ruidp, old_uid_t __user *, euidp, old_uid_t __user *, suidp)
अणु
	स्थिर काष्ठा cred *cred = current_cred();
	पूर्णांक retval;
	old_uid_t ruid, euid, suid;

	ruid = high2lowuid(from_kuid_munged(cred->user_ns, cred->uid));
	euid = high2lowuid(from_kuid_munged(cred->user_ns, cred->euid));
	suid = high2lowuid(from_kuid_munged(cred->user_ns, cred->suid));

	अगर (!(retval   = put_user(ruid, ruidp)) &&
	    !(retval   = put_user(euid, euidp)))
		retval = put_user(suid, suidp);

	वापस retval;
पूर्ण

SYSCALL_DEFINE3(setresgid16, old_gid_t, rgid, old_gid_t, egid, old_gid_t, sgid)
अणु
	वापस __sys_setresgid(low2highgid(rgid), low2highgid(egid),
				 low2highgid(sgid));
पूर्ण

SYSCALL_DEFINE3(getresgid16, old_gid_t __user *, rgidp, old_gid_t __user *, egidp, old_gid_t __user *, sgidp)
अणु
	स्थिर काष्ठा cred *cred = current_cred();
	पूर्णांक retval;
	old_gid_t rgid, egid, sgid;

	rgid = high2lowgid(from_kgid_munged(cred->user_ns, cred->gid));
	egid = high2lowgid(from_kgid_munged(cred->user_ns, cred->egid));
	sgid = high2lowgid(from_kgid_munged(cred->user_ns, cred->sgid));

	अगर (!(retval   = put_user(rgid, rgidp)) &&
	    !(retval   = put_user(egid, egidp)))
		retval = put_user(sgid, sgidp);

	वापस retval;
पूर्ण

SYSCALL_DEFINE1(setfsuid16, old_uid_t, uid)
अणु
	वापस __sys_setfsuid(low2highuid(uid));
पूर्ण

SYSCALL_DEFINE1(setfsgid16, old_gid_t, gid)
अणु
	वापस __sys_setfsgid(low2highgid(gid));
पूर्ण

अटल पूर्णांक groups16_to_user(old_gid_t __user *grouplist,
    काष्ठा group_info *group_info)
अणु
	काष्ठा user_namespace *user_ns = current_user_ns();
	पूर्णांक i;
	old_gid_t group;
	kgid_t kgid;

	क्रम (i = 0; i < group_info->ngroups; i++) अणु
		kgid = group_info->gid[i];
		group = high2lowgid(from_kgid_munged(user_ns, kgid));
		अगर (put_user(group, grouplist+i))
			वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक groups16_from_user(काष्ठा group_info *group_info,
    old_gid_t __user *grouplist)
अणु
	काष्ठा user_namespace *user_ns = current_user_ns();
	पूर्णांक i;
	old_gid_t group;
	kgid_t kgid;

	क्रम (i = 0; i < group_info->ngroups; i++) अणु
		अगर (get_user(group, grouplist+i))
			वापस  -EFAULT;

		kgid = make_kgid(user_ns, low2highgid(group));
		अगर (!gid_valid(kgid))
			वापस -EINVAL;

		group_info->gid[i] = kgid;
	पूर्ण

	वापस 0;
पूर्ण

SYSCALL_DEFINE2(getgroups16, पूर्णांक, gidsetsize, old_gid_t __user *, grouplist)
अणु
	स्थिर काष्ठा cred *cred = current_cred();
	पूर्णांक i;

	अगर (gidsetsize < 0)
		वापस -EINVAL;

	i = cred->group_info->ngroups;
	अगर (gidsetsize) अणु
		अगर (i > gidsetsize) अणु
			i = -EINVAL;
			जाओ out;
		पूर्ण
		अगर (groups16_to_user(grouplist, cred->group_info)) अणु
			i = -EFAULT;
			जाओ out;
		पूर्ण
	पूर्ण
out:
	वापस i;
पूर्ण

SYSCALL_DEFINE2(setgroups16, पूर्णांक, gidsetsize, old_gid_t __user *, grouplist)
अणु
	काष्ठा group_info *group_info;
	पूर्णांक retval;

	अगर (!may_setgroups())
		वापस -EPERM;
	अगर ((अचिन्हित)gidsetsize > NGROUPS_MAX)
		वापस -EINVAL;

	group_info = groups_alloc(gidsetsize);
	अगर (!group_info)
		वापस -ENOMEM;
	retval = groups16_from_user(group_info, grouplist);
	अगर (retval) अणु
		put_group_info(group_info);
		वापस retval;
	पूर्ण

	groups_sort(group_info);
	retval = set_current_groups(group_info);
	put_group_info(group_info);

	वापस retval;
पूर्ण

SYSCALL_DEFINE0(getuid16)
अणु
	वापस high2lowuid(from_kuid_munged(current_user_ns(), current_uid()));
पूर्ण

SYSCALL_DEFINE0(geteuid16)
अणु
	वापस high2lowuid(from_kuid_munged(current_user_ns(), current_euid()));
पूर्ण

SYSCALL_DEFINE0(getgid16)
अणु
	वापस high2lowgid(from_kgid_munged(current_user_ns(), current_gid()));
पूर्ण

SYSCALL_DEFINE0(getegid16)
अणु
	वापस high2lowgid(from_kgid_munged(current_user_ns(), current_egid()));
पूर्ण
