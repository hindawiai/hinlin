<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * device_cgroup.c - device cgroup subप्रणाली
 *
 * Copyright 2007 IBM Corp
 */

#समावेश <linux/device_cgroup.h>
#समावेश <linux/cgroup.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/list.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/mutex.h>

#अगर_घोषित CONFIG_CGROUP_DEVICE

अटल DEFINE_MUTEX(devcgroup_mutex);

क्रमागत devcg_behavior अणु
	DEVCG_DEFAULT_NONE,
	DEVCG_DEFAULT_ALLOW,
	DEVCG_DEFAULT_DENY,
पूर्ण;

/*
 * exception list locking rules:
 * hold devcgroup_mutex क्रम update/पढ़ो.
 * hold rcu_पढ़ो_lock() क्रम पढ़ो.
 */

काष्ठा dev_exception_item अणु
	u32 major, minor;
	लघु type;
	लघु access;
	काष्ठा list_head list;
	काष्ठा rcu_head rcu;
पूर्ण;

काष्ठा dev_cgroup अणु
	काष्ठा cgroup_subsys_state css;
	काष्ठा list_head exceptions;
	क्रमागत devcg_behavior behavior;
पूर्ण;

अटल अंतरभूत काष्ठा dev_cgroup *css_to_devcgroup(काष्ठा cgroup_subsys_state *s)
अणु
	वापस s ? container_of(s, काष्ठा dev_cgroup, css) : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा dev_cgroup *task_devcgroup(काष्ठा task_काष्ठा *task)
अणु
	वापस css_to_devcgroup(task_css(task, devices_cgrp_id));
पूर्ण

/*
 * called under devcgroup_mutex
 */
अटल पूर्णांक dev_exceptions_copy(काष्ठा list_head *dest, काष्ठा list_head *orig)
अणु
	काष्ठा dev_exception_item *ex, *पंचांगp, *new;

	lockdep_निश्चित_held(&devcgroup_mutex);

	list_क्रम_each_entry(ex, orig, list) अणु
		new = kmemdup(ex, माप(*ex), GFP_KERNEL);
		अगर (!new)
			जाओ मुक्त_and_निकास;
		list_add_tail(&new->list, dest);
	पूर्ण

	वापस 0;

मुक्त_and_निकास:
	list_क्रम_each_entry_safe(ex, पंचांगp, dest, list) अणु
		list_del(&ex->list);
		kमुक्त(ex);
	पूर्ण
	वापस -ENOMEM;
पूर्ण

/*
 * called under devcgroup_mutex
 */
अटल पूर्णांक dev_exception_add(काष्ठा dev_cgroup *dev_cgroup,
			     काष्ठा dev_exception_item *ex)
अणु
	काष्ठा dev_exception_item *excopy, *walk;

	lockdep_निश्चित_held(&devcgroup_mutex);

	excopy = kmemdup(ex, माप(*ex), GFP_KERNEL);
	अगर (!excopy)
		वापस -ENOMEM;

	list_क्रम_each_entry(walk, &dev_cgroup->exceptions, list) अणु
		अगर (walk->type != ex->type)
			जारी;
		अगर (walk->major != ex->major)
			जारी;
		अगर (walk->minor != ex->minor)
			जारी;

		walk->access |= ex->access;
		kमुक्त(excopy);
		excopy = शून्य;
	पूर्ण

	अगर (excopy != शून्य)
		list_add_tail_rcu(&excopy->list, &dev_cgroup->exceptions);
	वापस 0;
पूर्ण

/*
 * called under devcgroup_mutex
 */
अटल व्योम dev_exception_rm(काष्ठा dev_cgroup *dev_cgroup,
			     काष्ठा dev_exception_item *ex)
अणु
	काष्ठा dev_exception_item *walk, *पंचांगp;

	lockdep_निश्चित_held(&devcgroup_mutex);

	list_क्रम_each_entry_safe(walk, पंचांगp, &dev_cgroup->exceptions, list) अणु
		अगर (walk->type != ex->type)
			जारी;
		अगर (walk->major != ex->major)
			जारी;
		अगर (walk->minor != ex->minor)
			जारी;

		walk->access &= ~ex->access;
		अगर (!walk->access) अणु
			list_del_rcu(&walk->list);
			kमुक्त_rcu(walk, rcu);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __dev_exception_clean(काष्ठा dev_cgroup *dev_cgroup)
अणु
	काष्ठा dev_exception_item *ex, *पंचांगp;

	list_क्रम_each_entry_safe(ex, पंचांगp, &dev_cgroup->exceptions, list) अणु
		list_del_rcu(&ex->list);
		kमुक्त_rcu(ex, rcu);
	पूर्ण
पूर्ण

/**
 * dev_exception_clean - मुक्तs all entries of the exception list
 * @dev_cgroup: dev_cgroup with the exception list to be cleaned
 *
 * called under devcgroup_mutex
 */
अटल व्योम dev_exception_clean(काष्ठा dev_cgroup *dev_cgroup)
अणु
	lockdep_निश्चित_held(&devcgroup_mutex);

	__dev_exception_clean(dev_cgroup);
पूर्ण

अटल अंतरभूत bool is_devcg_online(स्थिर काष्ठा dev_cgroup *devcg)
अणु
	वापस (devcg->behavior != DEVCG_DEFAULT_NONE);
पूर्ण

/**
 * devcgroup_online - initializes devcgroup's behavior and exceptions based on
 * 		      parent's
 * @css: css getting online
 * वापसs 0 in हाल of success, error code otherwise
 */
अटल पूर्णांक devcgroup_online(काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा dev_cgroup *dev_cgroup = css_to_devcgroup(css);
	काष्ठा dev_cgroup *parent_dev_cgroup = css_to_devcgroup(css->parent);
	पूर्णांक ret = 0;

	mutex_lock(&devcgroup_mutex);

	अगर (parent_dev_cgroup == शून्य)
		dev_cgroup->behavior = DEVCG_DEFAULT_ALLOW;
	अन्यथा अणु
		ret = dev_exceptions_copy(&dev_cgroup->exceptions,
					  &parent_dev_cgroup->exceptions);
		अगर (!ret)
			dev_cgroup->behavior = parent_dev_cgroup->behavior;
	पूर्ण
	mutex_unlock(&devcgroup_mutex);

	वापस ret;
पूर्ण

अटल व्योम devcgroup_offline(काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा dev_cgroup *dev_cgroup = css_to_devcgroup(css);

	mutex_lock(&devcgroup_mutex);
	dev_cgroup->behavior = DEVCG_DEFAULT_NONE;
	mutex_unlock(&devcgroup_mutex);
पूर्ण

/*
 * called from kernel/cgroup.c with cgroup_lock() held.
 */
अटल काष्ठा cgroup_subsys_state *
devcgroup_css_alloc(काष्ठा cgroup_subsys_state *parent_css)
अणु
	काष्ठा dev_cgroup *dev_cgroup;

	dev_cgroup = kzalloc(माप(*dev_cgroup), GFP_KERNEL);
	अगर (!dev_cgroup)
		वापस ERR_PTR(-ENOMEM);
	INIT_LIST_HEAD(&dev_cgroup->exceptions);
	dev_cgroup->behavior = DEVCG_DEFAULT_NONE;

	वापस &dev_cgroup->css;
पूर्ण

अटल व्योम devcgroup_css_मुक्त(काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा dev_cgroup *dev_cgroup = css_to_devcgroup(css);

	__dev_exception_clean(dev_cgroup);
	kमुक्त(dev_cgroup);
पूर्ण

#घोषणा DEVCG_ALLOW 1
#घोषणा DEVCG_DENY 2
#घोषणा DEVCG_LIST 3

#घोषणा MAJMINLEN 13
#घोषणा ACCLEN 4

अटल व्योम set_access(अक्षर *acc, लघु access)
अणु
	पूर्णांक idx = 0;
	स_रखो(acc, 0, ACCLEN);
	अगर (access & DEVCG_ACC_READ)
		acc[idx++] = 'r';
	अगर (access & DEVCG_ACC_WRITE)
		acc[idx++] = 'w';
	अगर (access & DEVCG_ACC_MKNOD)
		acc[idx++] = 'm';
पूर्ण

अटल अक्षर type_to_अक्षर(लघु type)
अणु
	अगर (type == DEVCG_DEV_ALL)
		वापस 'a';
	अगर (type == DEVCG_DEV_CHAR)
		वापस 'c';
	अगर (type == DEVCG_DEV_BLOCK)
		वापस 'b';
	वापस 'X';
पूर्ण

अटल व्योम set_majmin(अक्षर *str, अचिन्हित m)
अणु
	अगर (m == ~0)
		म_नकल(str, "*");
	अन्यथा
		प्र_लिखो(str, "%u", m);
पूर्ण

अटल पूर्णांक devcgroup_seq_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा dev_cgroup *devcgroup = css_to_devcgroup(seq_css(m));
	काष्ठा dev_exception_item *ex;
	अक्षर maj[MAJMINLEN], min[MAJMINLEN], acc[ACCLEN];

	rcu_पढ़ो_lock();
	/*
	 * To preserve the compatibility:
	 * - Only show the "all devices" when the शेष policy is to allow
	 * - List the exceptions in हाल the शेष policy is to deny
	 * This way, the file reमुख्यs as a "whitelist of devices"
	 */
	अगर (devcgroup->behavior == DEVCG_DEFAULT_ALLOW) अणु
		set_access(acc, DEVCG_ACC_MASK);
		set_majmin(maj, ~0);
		set_majmin(min, ~0);
		seq_म_लिखो(m, "%c %s:%s %s\n", type_to_अक्षर(DEVCG_DEV_ALL),
			   maj, min, acc);
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry_rcu(ex, &devcgroup->exceptions, list) अणु
			set_access(acc, ex->access);
			set_majmin(maj, ex->major);
			set_majmin(min, ex->minor);
			seq_म_लिखो(m, "%c %s:%s %s\n", type_to_अक्षर(ex->type),
				   maj, min, acc);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

/**
 * match_exception	- iterates the exception list trying to find a complete match
 * @exceptions: list of exceptions
 * @type: device type (DEVCG_DEV_BLOCK or DEVCG_DEV_CHAR)
 * @major: device file major number, ~0 to match all
 * @minor: device file minor number, ~0 to match all
 * @access: permission mask (DEVCG_ACC_READ, DEVCG_ACC_WRITE, DEVCG_ACC_MKNOD)
 *
 * It is considered a complete match अगर an exception is found that will
 * contain the entire range of provided parameters.
 *
 * Return: true in हाल it matches an exception completely
 */
अटल bool match_exception(काष्ठा list_head *exceptions, लघु type,
			    u32 major, u32 minor, लघु access)
अणु
	काष्ठा dev_exception_item *ex;

	list_क्रम_each_entry_rcu(ex, exceptions, list) अणु
		अगर ((type & DEVCG_DEV_BLOCK) && !(ex->type & DEVCG_DEV_BLOCK))
			जारी;
		अगर ((type & DEVCG_DEV_CHAR) && !(ex->type & DEVCG_DEV_CHAR))
			जारी;
		अगर (ex->major != ~0 && ex->major != major)
			जारी;
		अगर (ex->minor != ~0 && ex->minor != minor)
			जारी;
		/* provided access cannot have more than the exception rule */
		अगर (access & (~ex->access))
			जारी;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * match_exception_partial - iterates the exception list trying to find a partial match
 * @exceptions: list of exceptions
 * @type: device type (DEVCG_DEV_BLOCK or DEVCG_DEV_CHAR)
 * @major: device file major number, ~0 to match all
 * @minor: device file minor number, ~0 to match all
 * @access: permission mask (DEVCG_ACC_READ, DEVCG_ACC_WRITE, DEVCG_ACC_MKNOD)
 *
 * It is considered a partial match अगर an exception's range is found to
 * contain *any* of the devices specअगरied by provided parameters. This is
 * used to make sure no extra access is being granted that is क्रमbidden by
 * any of the exception list.
 *
 * Return: true in हाल the provided range mat matches an exception completely
 */
अटल bool match_exception_partial(काष्ठा list_head *exceptions, लघु type,
				    u32 major, u32 minor, लघु access)
अणु
	काष्ठा dev_exception_item *ex;

	list_क्रम_each_entry_rcu(ex, exceptions, list,
				lockdep_is_held(&devcgroup_mutex)) अणु
		अगर ((type & DEVCG_DEV_BLOCK) && !(ex->type & DEVCG_DEV_BLOCK))
			जारी;
		अगर ((type & DEVCG_DEV_CHAR) && !(ex->type & DEVCG_DEV_CHAR))
			जारी;
		/*
		 * We must be sure that both the exception and the provided
		 * range aren't masking all devices
		 */
		अगर (ex->major != ~0 && major != ~0 && ex->major != major)
			जारी;
		अगर (ex->minor != ~0 && minor != ~0 && ex->minor != minor)
			जारी;
		/*
		 * In order to make sure the provided range isn't matching
		 * an exception, all its access bits shouldn't match the
		 * exception's access bits
		 */
		अगर (!(access & ex->access))
			जारी;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * verअगरy_new_ex - verअगरies अगर a new exception is allowed by parent cgroup's permissions
 * @dev_cgroup: dev cgroup to be tested against
 * @refex: new exception
 * @behavior: behavior of the exception's dev_cgroup
 *
 * This is used to make sure a child cgroup won't have more privileges
 * than its parent
 */
अटल bool verअगरy_new_ex(काष्ठा dev_cgroup *dev_cgroup,
		          काष्ठा dev_exception_item *refex,
		          क्रमागत devcg_behavior behavior)
अणु
	bool match = false;

	RCU_LOCKDEP_WARN(!rcu_पढ़ो_lock_held() &&
			 !lockdep_is_held(&devcgroup_mutex),
			 "device_cgroup:verify_new_ex called without proper synchronization");

	अगर (dev_cgroup->behavior == DEVCG_DEFAULT_ALLOW) अणु
		अगर (behavior == DEVCG_DEFAULT_ALLOW) अणु
			/*
			 * new exception in the child करोesn't matter, only
			 * adding extra restrictions
			 */ 
			वापस true;
		पूर्ण अन्यथा अणु
			/*
			 * new exception in the child will add more devices
			 * that can be acessed, so it can't match any of
			 * parent's exceptions, even slightly
			 */ 
			match = match_exception_partial(&dev_cgroup->exceptions,
							refex->type,
							refex->major,
							refex->minor,
							refex->access);

			अगर (match)
				वापस false;
			वापस true;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Only behavior == DEVCG_DEFAULT_DENY allowed here, thereक्रमe
		 * the new exception will add access to more devices and must
		 * be contained completely in an parent's exception to be
		 * allowed
		 */
		match = match_exception(&dev_cgroup->exceptions, refex->type,
					refex->major, refex->minor,
					refex->access);

		अगर (match)
			/* parent has an exception that matches the proposed */
			वापस true;
		अन्यथा
			वापस false;
	पूर्ण
	वापस false;
पूर्ण

/*
 * parent_has_perm:
 * when adding a new allow rule to a device exception list, the rule
 * must be allowed in the parent device
 */
अटल पूर्णांक parent_has_perm(काष्ठा dev_cgroup *childcg,
				  काष्ठा dev_exception_item *ex)
अणु
	काष्ठा dev_cgroup *parent = css_to_devcgroup(childcg->css.parent);

	अगर (!parent)
		वापस 1;
	वापस verअगरy_new_ex(parent, ex, childcg->behavior);
पूर्ण

/**
 * parent_allows_removal - verअगरy अगर it's ok to हटाओ an exception
 * @childcg: child cgroup from where the exception will be हटाओd
 * @ex: exception being हटाओd
 *
 * When removing an exception in cgroups with शेष ALLOW policy, it must
 * be checked अगर removing it will give the child cgroup more access than the
 * parent.
 *
 * Return: true अगर it's ok to हटाओ exception, false otherwise
 */
अटल bool parent_allows_removal(काष्ठा dev_cgroup *childcg,
				  काष्ठा dev_exception_item *ex)
अणु
	काष्ठा dev_cgroup *parent = css_to_devcgroup(childcg->css.parent);

	अगर (!parent)
		वापस true;

	/* It's always allowed to हटाओ access to devices */
	अगर (childcg->behavior == DEVCG_DEFAULT_DENY)
		वापस true;

	/*
	 * Make sure you're not removing part or a whole exception existing in
	 * the parent cgroup
	 */
	वापस !match_exception_partial(&parent->exceptions, ex->type,
					ex->major, ex->minor, ex->access);
पूर्ण

/**
 * may_allow_all - checks अगर it's possible to change the behavior to
 *		   allow based on parent's rules.
 * @parent: device cgroup's parent
 * वापसs: != 0 in हाल it's allowed, 0 otherwise
 */
अटल अंतरभूत पूर्णांक may_allow_all(काष्ठा dev_cgroup *parent)
अणु
	अगर (!parent)
		वापस 1;
	वापस parent->behavior == DEVCG_DEFAULT_ALLOW;
पूर्ण

/**
 * revalidate_active_exceptions - walks through the active exception list and
 * 				  revalidates the exceptions based on parent's
 * 				  behavior and exceptions. The exceptions that
 * 				  are no दीर्घer valid will be हटाओd.
 * 				  Called with devcgroup_mutex held.
 * @devcg: cgroup which exceptions will be checked
 *
 * This is one of the three key functions क्रम hierarchy implementation.
 * This function is responsible क्रम re-evaluating all the cgroup's active
 * exceptions due to a parent's exception change.
 * Refer to Documentation/admin-guide/cgroup-v1/devices.rst क्रम more details.
 */
अटल व्योम revalidate_active_exceptions(काष्ठा dev_cgroup *devcg)
अणु
	काष्ठा dev_exception_item *ex;
	काष्ठा list_head *this, *पंचांगp;

	list_क्रम_each_safe(this, पंचांगp, &devcg->exceptions) अणु
		ex = container_of(this, काष्ठा dev_exception_item, list);
		अगर (!parent_has_perm(devcg, ex))
			dev_exception_rm(devcg, ex);
	पूर्ण
पूर्ण

/**
 * propagate_exception - propagates a new exception to the children
 * @devcg_root: device cgroup that added a new exception
 * @ex: new exception to be propagated
 *
 * वापसs: 0 in हाल of success, != 0 in हाल of error
 */
अटल पूर्णांक propagate_exception(काष्ठा dev_cgroup *devcg_root,
			       काष्ठा dev_exception_item *ex)
अणु
	काष्ठा cgroup_subsys_state *pos;
	पूर्णांक rc = 0;

	rcu_पढ़ो_lock();

	css_क्रम_each_descendant_pre(pos, &devcg_root->css) अणु
		काष्ठा dev_cgroup *devcg = css_to_devcgroup(pos);

		/*
		 * Because devcgroup_mutex is held, no devcg will become
		 * online or offline during the tree walk (see on/offline
		 * methods), and online ones are safe to access outside RCU
		 * पढ़ो lock without bumping refcnt.
		 */
		अगर (pos == &devcg_root->css || !is_devcg_online(devcg))
			जारी;

		rcu_पढ़ो_unlock();

		/*
		 * in हाल both root's behavior and devcg is allow, a new
		 * restriction means adding to the exception list
		 */
		अगर (devcg_root->behavior == DEVCG_DEFAULT_ALLOW &&
		    devcg->behavior == DEVCG_DEFAULT_ALLOW) अणु
			rc = dev_exception_add(devcg, ex);
			अगर (rc)
				वापस rc;
		पूर्ण अन्यथा अणु
			/*
			 * in the other possible हालs:
			 * root's behavior: allow, devcg's: deny
			 * root's behavior: deny, devcg's: deny
			 * the exception will be हटाओd
			 */
			dev_exception_rm(devcg, ex);
		पूर्ण
		revalidate_active_exceptions(devcg);

		rcu_पढ़ो_lock();
	पूर्ण

	rcu_पढ़ो_unlock();
	वापस rc;
पूर्ण

/*
 * Modअगरy the exception list using allow/deny rules.
 * CAP_SYS_ADMIN is needed क्रम this.  It's at least separate from CAP_MKNOD
 * so we can give a container CAP_MKNOD to let it create devices but not
 * modअगरy the exception list.
 * It seems likely we'll want to add a CAP_CONTAINER capability to allow
 * us to also grant CAP_SYS_ADMIN to containers without giving away the
 * device exception list controls, but क्रम now we'll stick with CAP_SYS_ADMIN
 *
 * Taking rules away is always allowed (given CAP_SYS_ADMIN).  Granting
 * new access is only allowed अगर you're in the top-level cgroup, or your
 * parent cgroup has the access you're asking क्रम.
 */
अटल पूर्णांक devcgroup_update_access(काष्ठा dev_cgroup *devcgroup,
				   पूर्णांक filetype, अक्षर *buffer)
अणु
	स्थिर अक्षर *b;
	अक्षर temp[12];		/* 11 + 1 अक्षरacters needed क्रम a u32 */
	पूर्णांक count, rc = 0;
	काष्ठा dev_exception_item ex;
	काष्ठा dev_cgroup *parent = css_to_devcgroup(devcgroup->css.parent);

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	स_रखो(&ex, 0, माप(ex));
	b = buffer;

	चयन (*b) अणु
	हाल 'a':
		चयन (filetype) अणु
		हाल DEVCG_ALLOW:
			अगर (css_has_online_children(&devcgroup->css))
				वापस -EINVAL;

			अगर (!may_allow_all(parent))
				वापस -EPERM;
			dev_exception_clean(devcgroup);
			devcgroup->behavior = DEVCG_DEFAULT_ALLOW;
			अगर (!parent)
				अवरोध;

			rc = dev_exceptions_copy(&devcgroup->exceptions,
						 &parent->exceptions);
			अगर (rc)
				वापस rc;
			अवरोध;
		हाल DEVCG_DENY:
			अगर (css_has_online_children(&devcgroup->css))
				वापस -EINVAL;

			dev_exception_clean(devcgroup);
			devcgroup->behavior = DEVCG_DEFAULT_DENY;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		वापस 0;
	हाल 'b':
		ex.type = DEVCG_DEV_BLOCK;
		अवरोध;
	हाल 'c':
		ex.type = DEVCG_DEV_CHAR;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	b++;
	अगर (!है_खाली(*b))
		वापस -EINVAL;
	b++;
	अगर (*b == '*') अणु
		ex.major = ~0;
		b++;
	पूर्ण अन्यथा अगर (है_अंक(*b)) अणु
		स_रखो(temp, 0, माप(temp));
		क्रम (count = 0; count < माप(temp) - 1; count++) अणु
			temp[count] = *b;
			b++;
			अगर (!है_अंक(*b))
				अवरोध;
		पूर्ण
		rc = kstrtou32(temp, 10, &ex.major);
		अगर (rc)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
	अगर (*b != ':')
		वापस -EINVAL;
	b++;

	/* पढ़ो minor */
	अगर (*b == '*') अणु
		ex.minor = ~0;
		b++;
	पूर्ण अन्यथा अगर (है_अंक(*b)) अणु
		स_रखो(temp, 0, माप(temp));
		क्रम (count = 0; count < माप(temp) - 1; count++) अणु
			temp[count] = *b;
			b++;
			अगर (!है_अंक(*b))
				अवरोध;
		पूर्ण
		rc = kstrtou32(temp, 10, &ex.minor);
		अगर (rc)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
	अगर (!है_खाली(*b))
		वापस -EINVAL;
	क्रम (b++, count = 0; count < 3; count++, b++) अणु
		चयन (*b) अणु
		हाल 'r':
			ex.access |= DEVCG_ACC_READ;
			अवरोध;
		हाल 'w':
			ex.access |= DEVCG_ACC_WRITE;
			अवरोध;
		हाल 'm':
			ex.access |= DEVCG_ACC_MKNOD;
			अवरोध;
		हाल '\n':
		हाल '\0':
			count = 3;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	चयन (filetype) अणु
	हाल DEVCG_ALLOW:
		/*
		 * If the शेष policy is to allow by शेष, try to हटाओ
		 * an matching exception instead. And be silent about it: we
		 * करोn't want to अवरोध compatibility
		 */
		अगर (devcgroup->behavior == DEVCG_DEFAULT_ALLOW) अणु
			/* Check अगर the parent allows removing it first */
			अगर (!parent_allows_removal(devcgroup, &ex))
				वापस -EPERM;
			dev_exception_rm(devcgroup, &ex);
			अवरोध;
		पूर्ण

		अगर (!parent_has_perm(devcgroup, &ex))
			वापस -EPERM;
		rc = dev_exception_add(devcgroup, &ex);
		अवरोध;
	हाल DEVCG_DENY:
		/*
		 * If the शेष policy is to deny by शेष, try to हटाओ
		 * an matching exception instead. And be silent about it: we
		 * करोn't want to अवरोध compatibility
		 */
		अगर (devcgroup->behavior == DEVCG_DEFAULT_DENY)
			dev_exception_rm(devcgroup, &ex);
		अन्यथा
			rc = dev_exception_add(devcgroup, &ex);

		अगर (rc)
			अवरोध;
		/* we only propagate new restrictions */
		rc = propagate_exception(devcgroup, &ex);
		अवरोध;
	शेष:
		rc = -EINVAL;
	पूर्ण
	वापस rc;
पूर्ण

अटल sमाप_प्रकार devcgroup_access_ग_लिखो(काष्ठा kernfs_खोलो_file *of,
				      अक्षर *buf, माप_प्रकार nbytes, loff_t off)
अणु
	पूर्णांक retval;

	mutex_lock(&devcgroup_mutex);
	retval = devcgroup_update_access(css_to_devcgroup(of_css(of)),
					 of_cft(of)->निजी, म_मालाip(buf));
	mutex_unlock(&devcgroup_mutex);
	वापस retval ?: nbytes;
पूर्ण

अटल काष्ठा cftype dev_cgroup_files[] = अणु
	अणु
		.name = "allow",
		.ग_लिखो = devcgroup_access_ग_लिखो,
		.निजी = DEVCG_ALLOW,
	पूर्ण,
	अणु
		.name = "deny",
		.ग_लिखो = devcgroup_access_ग_लिखो,
		.निजी = DEVCG_DENY,
	पूर्ण,
	अणु
		.name = "list",
		.seq_show = devcgroup_seq_show,
		.निजी = DEVCG_LIST,
	पूर्ण,
	अणु पूर्ण	/* terminate */
पूर्ण;

काष्ठा cgroup_subsys devices_cgrp_subsys = अणु
	.css_alloc = devcgroup_css_alloc,
	.css_मुक्त = devcgroup_css_मुक्त,
	.css_online = devcgroup_online,
	.css_offline = devcgroup_offline,
	.legacy_cftypes = dev_cgroup_files,
पूर्ण;

/**
 * devcgroup_legacy_check_permission - checks अगर an inode operation is permitted
 * @dev_cgroup: the dev cgroup to be tested against
 * @type: device type
 * @major: device major number
 * @minor: device minor number
 * @access: combination of DEVCG_ACC_WRITE, DEVCG_ACC_READ and DEVCG_ACC_MKNOD
 *
 * वापसs 0 on success, -EPERM हाल the operation is not permitted
 */
अटल पूर्णांक devcgroup_legacy_check_permission(लघु type, u32 major, u32 minor,
					लघु access)
अणु
	काष्ठा dev_cgroup *dev_cgroup;
	bool rc;

	rcu_पढ़ो_lock();
	dev_cgroup = task_devcgroup(current);
	अगर (dev_cgroup->behavior == DEVCG_DEFAULT_ALLOW)
		/* Can't match any of the exceptions, even partially */
		rc = !match_exception_partial(&dev_cgroup->exceptions,
					      type, major, minor, access);
	अन्यथा
		/* Need to match completely one exception to be allowed */
		rc = match_exception(&dev_cgroup->exceptions, type, major,
				     minor, access);
	rcu_पढ़ो_unlock();

	अगर (!rc)
		वापस -EPERM;

	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_CGROUP_DEVICE */

#अगर defined(CONFIG_CGROUP_DEVICE) || defined(CONFIG_CGROUP_BPF)

पूर्णांक devcgroup_check_permission(लघु type, u32 major, u32 minor, लघु access)
अणु
	पूर्णांक rc = BPF_CGROUP_RUN_PROG_DEVICE_CGROUP(type, major, minor, access);

	अगर (rc)
		वापस -EPERM;

	#अगर_घोषित CONFIG_CGROUP_DEVICE
	वापस devcgroup_legacy_check_permission(type, major, minor, access);

	#अन्यथा /* CONFIG_CGROUP_DEVICE */
	वापस 0;

	#पूर्ण_अगर /* CONFIG_CGROUP_DEVICE */
पूर्ण
EXPORT_SYMBOL(devcgroup_check_permission);
#पूर्ण_अगर /* defined(CONFIG_CGROUP_DEVICE) || defined(CONFIG_CGROUP_BPF) */
