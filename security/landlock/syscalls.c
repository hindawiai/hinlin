<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Landlock LSM - System call implementations and user space पूर्णांकerfaces
 *
 * Copyright तऊ 2016-2020 Mickaथ+l Salaथञn <mic@digikod.net>
 * Copyright तऊ 2018-2020 ANSSI
 */

#समावेश <यंत्र/current.h>
#समावेश <linux/anon_inodes.h>
#समावेश <linux/build_bug.h>
#समावेश <linux/capability.h>
#समावेश <linux/compiler_types.h>
#समावेश <linux/dcache.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/mount.h>
#समावेश <linux/path.h>
#समावेश <linux/sched.h>
#समावेश <linux/security.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/syscalls.h>
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>
#समावेश <uapi/linux/landlock.h>

#समावेश "cred.h"
#समावेश "fs.h"
#समावेश "limits.h"
#समावेश "ruleset.h"
#समावेश "setup.h"

/**
 * copy_min_काष्ठा_from_user - Safe future-proof argument copying
 *
 * Extend copy_काष्ठा_from_user() to check क्रम consistent user buffer.
 *
 * @dst: Kernel space poपूर्णांकer or शून्य.
 * @ksize: Actual size of the data poपूर्णांकed to by @dst.
 * @ksize_min: Minimal required size to be copied.
 * @src: User space poपूर्णांकer or शून्य.
 * @usize: (Alleged) size of the data poपूर्णांकed to by @src.
 */
अटल __always_अंतरभूत पूर्णांक copy_min_काष्ठा_from_user(व्योम *स्थिर dst,
		स्थिर माप_प्रकार ksize, स्थिर माप_प्रकार ksize_min,
		स्थिर व्योम __user *स्थिर src, स्थिर माप_प्रकार usize)
अणु
	/* Checks buffer inconsistencies. */
	BUILD_BUG_ON(!dst);
	अगर (!src)
		वापस -EFAULT;

	/* Checks size ranges. */
	BUILD_BUG_ON(ksize <= 0);
	BUILD_BUG_ON(ksize < ksize_min);
	अगर (usize < ksize_min)
		वापस -EINVAL;
	अगर (usize > PAGE_SIZE)
		वापस -E2BIG;

	/* Copies user buffer and fills with zeros. */
	वापस copy_काष्ठा_from_user(dst, ksize, src, usize);
पूर्ण

/*
 * This function only contains arithmetic operations with स्थिरants, leading to
 * BUILD_BUG_ON().  The related code is evaluated and checked at build समय,
 * but it is then ignored thanks to compiler optimizations.
 */
अटल व्योम build_check_abi(व्योम)
अणु
	काष्ठा landlock_ruleset_attr ruleset_attr;
	काष्ठा landlock_path_beneath_attr path_beneath_attr;
	माप_प्रकार ruleset_size, path_beneath_size;

	/*
	 * For each user space ABI काष्ठाures, first checks that there is no
	 * hole in them, then checks that all architectures have the same
	 * काष्ठा size.
	 */
	ruleset_size = माप(ruleset_attr.handled_access_fs);
	BUILD_BUG_ON(माप(ruleset_attr) != ruleset_size);
	BUILD_BUG_ON(माप(ruleset_attr) != 8);

	path_beneath_size = माप(path_beneath_attr.allowed_access);
	path_beneath_size += माप(path_beneath_attr.parent_fd);
	BUILD_BUG_ON(माप(path_beneath_attr) != path_beneath_size);
	BUILD_BUG_ON(माप(path_beneath_attr) != 12);
पूर्ण

/* Ruleset handling */

अटल पूर्णांक fop_ruleset_release(काष्ठा inode *स्थिर inode,
		काष्ठा file *स्थिर filp)
अणु
	काष्ठा landlock_ruleset *ruleset = filp->निजी_data;

	landlock_put_ruleset(ruleset);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार fop_dummy_पढ़ो(काष्ठा file *स्थिर filp, अक्षर __user *स्थिर buf,
		स्थिर माप_प्रकार size, loff_t *स्थिर ppos)
अणु
	/* Dummy handler to enable FMODE_CAN_READ. */
	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार fop_dummy_ग_लिखो(काष्ठा file *स्थिर filp,
		स्थिर अक्षर __user *स्थिर buf, स्थिर माप_प्रकार size,
		loff_t *स्थिर ppos)
अणु
	/* Dummy handler to enable FMODE_CAN_WRITE. */
	वापस -EINVAL;
पूर्ण

/*
 * A ruleset file descriptor enables to build a ruleset by adding (i.e.
 * writing) rule after rule, without relying on the task's context.  This
 * reentrant design is also used in a पढ़ो way to enक्रमce the ruleset on the
 * current task.
 */
अटल स्थिर काष्ठा file_operations ruleset_fops = अणु
	.release = fop_ruleset_release,
	.पढ़ो = fop_dummy_पढ़ो,
	.ग_लिखो = fop_dummy_ग_लिखो,
पूर्ण;

#घोषणा LANDLOCK_ABI_VERSION	1

/**
 * sys_landlock_create_ruleset - Create a new ruleset
 *
 * @attr: Poपूर्णांकer to a &काष्ठा landlock_ruleset_attr identअगरying the scope of
 *        the new ruleset.
 * @size: Size of the poपूर्णांकed &काष्ठा landlock_ruleset_attr (needed क्रम
 *        backward and क्रमward compatibility).
 * @flags: Supported value: %LANDLOCK_CREATE_RULESET_VERSION.
 *
 * This प्रणाली call enables to create a new Landlock ruleset, and वापसs the
 * related file descriptor on success.
 *
 * If @flags is %LANDLOCK_CREATE_RULESET_VERSION and @attr is शून्य and @size is
 * 0, then the वापसed value is the highest supported Landlock ABI version
 * (starting at 1).
 *
 * Possible वापसed errors are:
 *
 * - EOPNOTSUPP: Landlock is supported by the kernel but disabled at boot समय;
 * - EINVAL: unknown @flags, or unknown access, or too small @size;
 * - E2BIG or EFAULT: @attr or @size inconsistencies;
 * - ENOMSG: empty &landlock_ruleset_attr.handled_access_fs.
 */
SYSCALL_DEFINE3(landlock_create_ruleset,
		स्थिर काष्ठा landlock_ruleset_attr __user *स्थिर, attr,
		स्थिर माप_प्रकार, size, स्थिर __u32, flags)
अणु
	काष्ठा landlock_ruleset_attr ruleset_attr;
	काष्ठा landlock_ruleset *ruleset;
	पूर्णांक err, ruleset_fd;

	/* Build-समय checks. */
	build_check_abi();

	अगर (!landlock_initialized)
		वापस -EOPNOTSUPP;

	अगर (flags) अणु
		अगर ((flags == LANDLOCK_CREATE_RULESET_VERSION)
				&& !attr && !size)
			वापस LANDLOCK_ABI_VERSION;
		वापस -EINVAL;
	पूर्ण

	/* Copies raw user space buffer. */
	err = copy_min_काष्ठा_from_user(&ruleset_attr, माप(ruleset_attr),
			दुरत्वend(typeof(ruleset_attr), handled_access_fs),
			attr, size);
	अगर (err)
		वापस err;

	/* Checks content (and 32-bits cast). */
	अगर ((ruleset_attr.handled_access_fs | LANDLOCK_MASK_ACCESS_FS) !=
			LANDLOCK_MASK_ACCESS_FS)
		वापस -EINVAL;

	/* Checks arguments and transक्रमms to kernel काष्ठा. */
	ruleset = landlock_create_ruleset(ruleset_attr.handled_access_fs);
	अगर (IS_ERR(ruleset))
		वापस PTR_ERR(ruleset);

	/* Creates anonymous FD referring to the ruleset. */
	ruleset_fd = anon_inode_getfd("landlock-ruleset", &ruleset_fops,
			ruleset, O_RDWR | O_CLOEXEC);
	अगर (ruleset_fd < 0)
		landlock_put_ruleset(ruleset);
	वापस ruleset_fd;
पूर्ण

/*
 * Returns an owned ruleset from a FD. It is thus needed to call
 * landlock_put_ruleset() on the वापस value.
 */
अटल काष्ठा landlock_ruleset *get_ruleset_from_fd(स्थिर पूर्णांक fd,
		स्थिर भ_शेषe_t mode)
अणु
	काष्ठा fd ruleset_f;
	काष्ठा landlock_ruleset *ruleset;

	ruleset_f = fdget(fd);
	अगर (!ruleset_f.file)
		वापस ERR_PTR(-EBADF);

	/* Checks FD type and access right. */
	अगर (ruleset_f.file->f_op != &ruleset_fops) अणु
		ruleset = ERR_PTR(-EBADFD);
		जाओ out_fdput;
	पूर्ण
	अगर (!(ruleset_f.file->f_mode & mode)) अणु
		ruleset = ERR_PTR(-EPERM);
		जाओ out_fdput;
	पूर्ण
	ruleset = ruleset_f.file->निजी_data;
	अगर (WARN_ON_ONCE(ruleset->num_layers != 1)) अणु
		ruleset = ERR_PTR(-EINVAL);
		जाओ out_fdput;
	पूर्ण
	landlock_get_ruleset(ruleset);

out_fdput:
	fdput(ruleset_f);
	वापस ruleset;
पूर्ण

/* Path handling */

/*
 * @path: Must call put_path(@path) after the call अगर it succeeded.
 */
अटल पूर्णांक get_path_from_fd(स्थिर s32 fd, काष्ठा path *स्थिर path)
अणु
	काष्ठा fd f;
	पूर्णांक err = 0;

	BUILD_BUG_ON(!__same_type(fd,
		((काष्ठा landlock_path_beneath_attr *)शून्य)->parent_fd));

	/* Handles O_PATH. */
	f = fdget_raw(fd);
	अगर (!f.file)
		वापस -EBADF;
	/*
	 * Forbids ruleset FDs, पूर्णांकernal fileप्रणालीs (e.g. nsfs), including
	 * pseuकरो fileप्रणालीs that will never be mountable (e.g. sockfs,
	 * pipefs).
	 */
	अगर ((f.file->f_op == &ruleset_fops) ||
			(f.file->f_path.mnt->mnt_flags & MNT_INTERNAL) ||
			(f.file->f_path.dentry->d_sb->s_flags & SB_NOUSER) ||
			d_is_negative(f.file->f_path.dentry) ||
			IS_PRIVATE(d_backing_inode(f.file->f_path.dentry))) अणु
		err = -EBADFD;
		जाओ out_fdput;
	पूर्ण
	*path = f.file->f_path;
	path_get(path);

out_fdput:
	fdput(f);
	वापस err;
पूर्ण

/**
 * sys_landlock_add_rule - Add a new rule to a ruleset
 *
 * @ruleset_fd: File descriptor tied to the ruleset that should be extended
 *		with the new rule.
 * @rule_type: Identअगरy the काष्ठाure type poपूर्णांकed to by @rule_attr (only
 *             LANDLOCK_RULE_PATH_BENEATH क्रम now).
 * @rule_attr: Poपूर्णांकer to a rule (only of type &काष्ठा
 *             landlock_path_beneath_attr क्रम now).
 * @flags: Must be 0.
 *
 * This प्रणाली call enables to define a new rule and add it to an existing
 * ruleset.
 *
 * Possible वापसed errors are:
 *
 * - EOPNOTSUPP: Landlock is supported by the kernel but disabled at boot समय;
 * - EINVAL: @flags is not 0, or inconsistent access in the rule (i.e.
 *   &landlock_path_beneath_attr.allowed_access is not a subset of the rule's
 *   accesses);
 * - ENOMSG: Empty accesses (e.g. &landlock_path_beneath_attr.allowed_access);
 * - EBADF: @ruleset_fd is not a file descriptor क्रम the current thपढ़ो, or a
 *   member of @rule_attr is not a file descriptor as expected;
 * - EBADFD: @ruleset_fd is not a ruleset file descriptor, or a member of
 *   @rule_attr is not the expected file descriptor type (e.g. file खोलो
 *   without O_PATH);
 * - EPERM: @ruleset_fd has no ग_लिखो access to the underlying ruleset;
 * - EFAULT: @rule_attr inconsistency.
 */
SYSCALL_DEFINE4(landlock_add_rule,
		स्थिर पूर्णांक, ruleset_fd, स्थिर क्रमागत landlock_rule_type, rule_type,
		स्थिर व्योम __user *स्थिर, rule_attr, स्थिर __u32, flags)
अणु
	काष्ठा landlock_path_beneath_attr path_beneath_attr;
	काष्ठा path path;
	काष्ठा landlock_ruleset *ruleset;
	पूर्णांक res, err;

	अगर (!landlock_initialized)
		वापस -EOPNOTSUPP;

	/* No flag क्रम now. */
	अगर (flags)
		वापस -EINVAL;

	अगर (rule_type != LANDLOCK_RULE_PATH_BENEATH)
		वापस -EINVAL;

	/* Copies raw user space buffer, only one type क्रम now. */
	res = copy_from_user(&path_beneath_attr, rule_attr,
			माप(path_beneath_attr));
	अगर (res)
		वापस -EFAULT;

	/* Gets and checks the ruleset. */
	ruleset = get_ruleset_from_fd(ruleset_fd, FMODE_CAN_WRITE);
	अगर (IS_ERR(ruleset))
		वापस PTR_ERR(ruleset);

	/*
	 * Inक्रमms about useless rule: empty allowed_access (i.e. deny rules)
	 * are ignored in path walks.
	 */
	अगर (!path_beneath_attr.allowed_access) अणु
		err = -ENOMSG;
		जाओ out_put_ruleset;
	पूर्ण
	/*
	 * Checks that allowed_access matches the @ruleset स्थिरraपूर्णांकs
	 * (ruleset->fs_access_masks[0] is स्वतःmatically upgraded to 64-bits).
	 */
	अगर ((path_beneath_attr.allowed_access | ruleset->fs_access_masks[0]) !=
			ruleset->fs_access_masks[0]) अणु
		err = -EINVAL;
		जाओ out_put_ruleset;
	पूर्ण

	/* Gets and checks the new rule. */
	err = get_path_from_fd(path_beneath_attr.parent_fd, &path);
	अगर (err)
		जाओ out_put_ruleset;

	/* Imports the new rule. */
	err = landlock_append_fs_rule(ruleset, &path,
			path_beneath_attr.allowed_access);
	path_put(&path);

out_put_ruleset:
	landlock_put_ruleset(ruleset);
	वापस err;
पूर्ण

/* Enक्रमcement */

/**
 * sys_landlock_restrict_self - Enक्रमce a ruleset on the calling thपढ़ो
 *
 * @ruleset_fd: File descriptor tied to the ruleset to merge with the target.
 * @flags: Must be 0.
 *
 * This प्रणाली call enables to enक्रमce a Landlock ruleset on the current
 * thपढ़ो.  Enक्रमcing a ruleset requires that the task has CAP_SYS_ADMIN in its
 * namespace or is running with no_new_privs.  This aव्योमs scenarios where
 * unprivileged tasks can affect the behavior of privileged children.
 *
 * Possible वापसed errors are:
 *
 * - EOPNOTSUPP: Landlock is supported by the kernel but disabled at boot समय;
 * - EINVAL: @flags is not 0.
 * - EBADF: @ruleset_fd is not a file descriptor क्रम the current thपढ़ो;
 * - EBADFD: @ruleset_fd is not a ruleset file descriptor;
 * - EPERM: @ruleset_fd has no पढ़ो access to the underlying ruleset, or the
 *   current thपढ़ो is not running with no_new_privs, or it करोesn't have
 *   CAP_SYS_ADMIN in its namespace.
 * - E2BIG: The maximum number of stacked rulesets is reached क्रम the current
 *   thपढ़ो.
 */
SYSCALL_DEFINE2(landlock_restrict_self,
		स्थिर पूर्णांक, ruleset_fd, स्थिर __u32, flags)
अणु
	काष्ठा landlock_ruleset *new_करोm, *ruleset;
	काष्ठा cred *new_cred;
	काष्ठा landlock_cred_security *new_llcred;
	पूर्णांक err;

	अगर (!landlock_initialized)
		वापस -EOPNOTSUPP;

	/* No flag क्रम now. */
	अगर (flags)
		वापस -EINVAL;

	/*
	 * Similar checks as क्रम seccomp(2), except that an -EPERM may be
	 * वापसed.
	 */
	अगर (!task_no_new_privs(current) &&
			!ns_capable_noaudit(current_user_ns(), CAP_SYS_ADMIN))
		वापस -EPERM;

	/* Gets and checks the ruleset. */
	ruleset = get_ruleset_from_fd(ruleset_fd, FMODE_CAN_READ);
	अगर (IS_ERR(ruleset))
		वापस PTR_ERR(ruleset);

	/* Prepares new credentials. */
	new_cred = prepare_creds();
	अगर (!new_cred) अणु
		err = -ENOMEM;
		जाओ out_put_ruleset;
	पूर्ण
	new_llcred = landlock_cred(new_cred);

	/*
	 * There is no possible race condition जबतक copying and manipulating
	 * the current credentials because they are dedicated per thपढ़ो.
	 */
	new_करोm = landlock_merge_ruleset(new_llcred->करोमुख्य, ruleset);
	अगर (IS_ERR(new_करोm)) अणु
		err = PTR_ERR(new_करोm);
		जाओ out_put_creds;
	पूर्ण

	/* Replaces the old (prepared) करोमुख्य. */
	landlock_put_ruleset(new_llcred->करोमुख्य);
	new_llcred->करोमुख्य = new_करोm;

	landlock_put_ruleset(ruleset);
	वापस commit_creds(new_cred);

out_put_creds:
	पात_creds(new_cred);

out_put_ruleset:
	landlock_put_ruleset(ruleset);
	वापस err;
पूर्ण
