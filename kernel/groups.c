<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Supplementary group IDs
 */
#समावेश <linux/cred.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/security.h>
#समावेश <linux/sort.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/user_namespace.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/uaccess.h>

काष्ठा group_info *groups_alloc(पूर्णांक gidsetsize)
अणु
	काष्ठा group_info *gi;
	gi = kvदो_स्मृति(काष्ठा_size(gi, gid, gidsetsize), GFP_KERNEL_ACCOUNT);
	अगर (!gi)
		वापस शून्य;

	atomic_set(&gi->usage, 1);
	gi->ngroups = gidsetsize;
	वापस gi;
पूर्ण

EXPORT_SYMBOL(groups_alloc);

व्योम groups_मुक्त(काष्ठा group_info *group_info)
अणु
	kvमुक्त(group_info);
पूर्ण

EXPORT_SYMBOL(groups_मुक्त);

/* export the group_info to a user-space array */
अटल पूर्णांक groups_to_user(gid_t __user *grouplist,
			  स्थिर काष्ठा group_info *group_info)
अणु
	काष्ठा user_namespace *user_ns = current_user_ns();
	पूर्णांक i;
	अचिन्हित पूर्णांक count = group_info->ngroups;

	क्रम (i = 0; i < count; i++) अणु
		gid_t gid;
		gid = from_kgid_munged(user_ns, group_info->gid[i]);
		अगर (put_user(gid, grouplist+i))
			वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

/* fill a group_info from a user-space array - it must be allocated alपढ़ोy */
अटल पूर्णांक groups_from_user(काष्ठा group_info *group_info,
    gid_t __user *grouplist)
अणु
	काष्ठा user_namespace *user_ns = current_user_ns();
	पूर्णांक i;
	अचिन्हित पूर्णांक count = group_info->ngroups;

	क्रम (i = 0; i < count; i++) अणु
		gid_t gid;
		kgid_t kgid;
		अगर (get_user(gid, grouplist+i))
			वापस -EFAULT;

		kgid = make_kgid(user_ns, gid);
		अगर (!gid_valid(kgid))
			वापस -EINVAL;

		group_info->gid[i] = kgid;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक gid_cmp(स्थिर व्योम *_a, स्थिर व्योम *_b)
अणु
	kgid_t a = *(kgid_t *)_a;
	kgid_t b = *(kgid_t *)_b;

	वापस gid_gt(a, b) - gid_lt(a, b);
पूर्ण

व्योम groups_sort(काष्ठा group_info *group_info)
अणु
	sort(group_info->gid, group_info->ngroups, माप(*group_info->gid),
	     gid_cmp, शून्य);
पूर्ण
EXPORT_SYMBOL(groups_sort);

/* a simple द्वा_खोज */
पूर्णांक groups_search(स्थिर काष्ठा group_info *group_info, kgid_t grp)
अणु
	अचिन्हित पूर्णांक left, right;

	अगर (!group_info)
		वापस 0;

	left = 0;
	right = group_info->ngroups;
	जबतक (left < right) अणु
		अचिन्हित पूर्णांक mid = (left+right)/2;
		अगर (gid_gt(grp, group_info->gid[mid]))
			left = mid + 1;
		अन्यथा अगर (gid_lt(grp, group_info->gid[mid]))
			right = mid;
		अन्यथा
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * set_groups - Change a group subscription in a set of credentials
 * @new: The newly prepared set of credentials to alter
 * @group_info: The group list to install
 */
व्योम set_groups(काष्ठा cred *new, काष्ठा group_info *group_info)
अणु
	put_group_info(new->group_info);
	get_group_info(group_info);
	new->group_info = group_info;
पूर्ण

EXPORT_SYMBOL(set_groups);

/**
 * set_current_groups - Change current's group subscription
 * @group_info: The group list to impose
 *
 * Validate a group subscription and, अगर valid, impose it upon current's task
 * security record.
 */
पूर्णांक set_current_groups(काष्ठा group_info *group_info)
अणु
	काष्ठा cred *new;

	new = prepare_creds();
	अगर (!new)
		वापस -ENOMEM;

	set_groups(new, group_info);
	वापस commit_creds(new);
पूर्ण

EXPORT_SYMBOL(set_current_groups);

SYSCALL_DEFINE2(getgroups, पूर्णांक, gidsetsize, gid_t __user *, grouplist)
अणु
	स्थिर काष्ठा cred *cred = current_cred();
	पूर्णांक i;

	अगर (gidsetsize < 0)
		वापस -EINVAL;

	/* no need to grab task_lock here; it cannot change */
	i = cred->group_info->ngroups;
	अगर (gidsetsize) अणु
		अगर (i > gidsetsize) अणु
			i = -EINVAL;
			जाओ out;
		पूर्ण
		अगर (groups_to_user(grouplist, cred->group_info)) अणु
			i = -EFAULT;
			जाओ out;
		पूर्ण
	पूर्ण
out:
	वापस i;
पूर्ण

bool may_setgroups(व्योम)
अणु
	काष्ठा user_namespace *user_ns = current_user_ns();

	वापस ns_capable_setid(user_ns, CAP_SETGID) &&
		userns_may_setgroups(user_ns);
पूर्ण

/*
 *	SMP: Our groups are copy-on-ग_लिखो. We can set them safely
 *	without another task पूर्णांकerfering.
 */

SYSCALL_DEFINE2(setgroups, पूर्णांक, gidsetsize, gid_t __user *, grouplist)
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
	retval = groups_from_user(group_info, grouplist);
	अगर (retval) अणु
		put_group_info(group_info);
		वापस retval;
	पूर्ण

	groups_sort(group_info);
	retval = set_current_groups(group_info);
	put_group_info(group_info);

	वापस retval;
पूर्ण

/*
 * Check whether we're fsgid/egid or in the supplemental group..
 */
पूर्णांक in_group_p(kgid_t grp)
अणु
	स्थिर काष्ठा cred *cred = current_cred();
	पूर्णांक retval = 1;

	अगर (!gid_eq(grp, cred->fsgid))
		retval = groups_search(cred->group_info, grp);
	वापस retval;
पूर्ण

EXPORT_SYMBOL(in_group_p);

पूर्णांक in_egroup_p(kgid_t grp)
अणु
	स्थिर काष्ठा cred *cred = current_cred();
	पूर्णांक retval = 1;

	अगर (!gid_eq(grp, cred->egid))
		retval = groups_search(cred->group_info, grp);
	वापस retval;
पूर्ण

EXPORT_SYMBOL(in_egroup_p);
