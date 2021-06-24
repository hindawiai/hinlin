<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * stackglue.c
 *
 * Code which implements an OCFS2 specअगरic पूर्णांकerface to underlying
 * cluster stacks.
 *
 * Copyright (C) 2007, 2009 Oracle.  All rights reserved.
 */

#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/kmod.h>
#समावेश <linux/fs.h>
#समावेश <linux/kobject.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/sysctl.h>

#समावेश "ocfs2_fs.h"

#समावेश "stackglue.h"

#घोषणा OCFS2_STACK_PLUGIN_O2CB		"o2cb"
#घोषणा OCFS2_STACK_PLUGIN_USER		"user"
#घोषणा OCFS2_MAX_HB_CTL_PATH		256

अटल काष्ठा ocfs2_protocol_version locking_max_version;
अटल DEFINE_SPINLOCK(ocfs2_stack_lock);
अटल LIST_HEAD(ocfs2_stack_list);
अटल अक्षर cluster_stack_name[OCFS2_STACK_LABEL_LEN + 1];
अटल अक्षर ocfs2_hb_ctl_path[OCFS2_MAX_HB_CTL_PATH] = "/sbin/ocfs2_hb_ctl";

/*
 * The stack currently in use.  If not null, active_stack->sp_count > 0,
 * the module is pinned, and the locking protocol cannot be changed.
 */
अटल काष्ठा ocfs2_stack_plugin *active_stack;

अटल काष्ठा ocfs2_stack_plugin *ocfs2_stack_lookup(स्थिर अक्षर *name)
अणु
	काष्ठा ocfs2_stack_plugin *p;

	निश्चित_spin_locked(&ocfs2_stack_lock);

	list_क्रम_each_entry(p, &ocfs2_stack_list, sp_list) अणु
		अगर (!म_भेद(p->sp_name, name))
			वापस p;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक ocfs2_stack_driver_request(स्थिर अक्षर *stack_name,
				      स्थिर अक्षर *plugin_name)
अणु
	पूर्णांक rc;
	काष्ठा ocfs2_stack_plugin *p;

	spin_lock(&ocfs2_stack_lock);

	/*
	 * If the stack passed by the fileप्रणाली isn't the selected one,
	 * we can't जारी.
	 */
	अगर (म_भेद(stack_name, cluster_stack_name)) अणु
		rc = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (active_stack) अणु
		/*
		 * If the active stack isn't the one we want, it cannot
		 * be selected right now.
		 */
		अगर (!म_भेद(active_stack->sp_name, plugin_name))
			rc = 0;
		अन्यथा
			rc = -EBUSY;
		जाओ out;
	पूर्ण

	p = ocfs2_stack_lookup(plugin_name);
	अगर (!p || !try_module_get(p->sp_owner)) अणु
		rc = -ENOENT;
		जाओ out;
	पूर्ण

	active_stack = p;
	rc = 0;

out:
	/* If we found it, pin it */
	अगर (!rc)
		active_stack->sp_count++;

	spin_unlock(&ocfs2_stack_lock);
	वापस rc;
पूर्ण

/*
 * This function looks up the appropriate stack and makes it active.  If
 * there is no stack, it tries to load it.  It will fail अगर the stack still
 * cannot be found.  It will also fail अगर a dअगरferent stack is in use.
 */
अटल पूर्णांक ocfs2_stack_driver_get(स्थिर अक्षर *stack_name)
अणु
	पूर्णांक rc;
	अक्षर *plugin_name = OCFS2_STACK_PLUGIN_O2CB;

	/*
	 * Classic stack करोes not pass in a stack name.  This is
	 * compatible with older tools as well.
	 */
	अगर (!stack_name || !*stack_name)
		stack_name = OCFS2_STACK_PLUGIN_O2CB;

	अगर (म_माप(stack_name) != OCFS2_STACK_LABEL_LEN) अणु
		prपूर्णांकk(KERN_ERR
		       "ocfs2 passed an invalid cluster stack label: \"%s\"\n",
		       stack_name);
		वापस -EINVAL;
	पूर्ण

	/* Anything that isn't the classic stack is a user stack */
	अगर (म_भेद(stack_name, OCFS2_STACK_PLUGIN_O2CB))
		plugin_name = OCFS2_STACK_PLUGIN_USER;

	rc = ocfs2_stack_driver_request(stack_name, plugin_name);
	अगर (rc == -ENOENT) अणु
		request_module("ocfs2_stack_%s", plugin_name);
		rc = ocfs2_stack_driver_request(stack_name, plugin_name);
	पूर्ण

	अगर (rc == -ENOENT) अणु
		prपूर्णांकk(KERN_ERR
		       "ocfs2: Cluster stack driver \"%s\" cannot be found\n",
		       plugin_name);
	पूर्ण अन्यथा अगर (rc == -EBUSY) अणु
		prपूर्णांकk(KERN_ERR
		       "ocfs2: A different cluster stack is in use\n");
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम ocfs2_stack_driver_put(व्योम)
अणु
	spin_lock(&ocfs2_stack_lock);
	BUG_ON(active_stack == शून्य);
	BUG_ON(active_stack->sp_count == 0);

	active_stack->sp_count--;
	अगर (!active_stack->sp_count) अणु
		module_put(active_stack->sp_owner);
		active_stack = शून्य;
	पूर्ण
	spin_unlock(&ocfs2_stack_lock);
पूर्ण

पूर्णांक ocfs2_stack_glue_रेजिस्टर(काष्ठा ocfs2_stack_plugin *plugin)
अणु
	पूर्णांक rc;

	spin_lock(&ocfs2_stack_lock);
	अगर (!ocfs2_stack_lookup(plugin->sp_name)) अणु
		plugin->sp_count = 0;
		plugin->sp_max_proto = locking_max_version;
		list_add(&plugin->sp_list, &ocfs2_stack_list);
		prपूर्णांकk(KERN_INFO "ocfs2: Registered cluster interface %s\n",
		       plugin->sp_name);
		rc = 0;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "ocfs2: Stack \"%s\" already registered\n",
		       plugin->sp_name);
		rc = -EEXIST;
	पूर्ण
	spin_unlock(&ocfs2_stack_lock);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(ocfs2_stack_glue_रेजिस्टर);

व्योम ocfs2_stack_glue_unरेजिस्टर(काष्ठा ocfs2_stack_plugin *plugin)
अणु
	काष्ठा ocfs2_stack_plugin *p;

	spin_lock(&ocfs2_stack_lock);
	p = ocfs2_stack_lookup(plugin->sp_name);
	अगर (p) अणु
		BUG_ON(p != plugin);
		BUG_ON(plugin == active_stack);
		BUG_ON(plugin->sp_count != 0);
		list_del_init(&plugin->sp_list);
		prपूर्णांकk(KERN_INFO "ocfs2: Unregistered cluster interface %s\n",
		       plugin->sp_name);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "Stack \"%s\" is not registered\n",
		       plugin->sp_name);
	पूर्ण
	spin_unlock(&ocfs2_stack_lock);
पूर्ण
EXPORT_SYMBOL_GPL(ocfs2_stack_glue_unरेजिस्टर);

व्योम ocfs2_stack_glue_set_max_proto_version(काष्ठा ocfs2_protocol_version *max_proto)
अणु
	काष्ठा ocfs2_stack_plugin *p;

	spin_lock(&ocfs2_stack_lock);
	अगर (स_भेद(max_proto, &locking_max_version,
		   माप(काष्ठा ocfs2_protocol_version))) अणु
		BUG_ON(locking_max_version.pv_major != 0);

		locking_max_version = *max_proto;
		list_क्रम_each_entry(p, &ocfs2_stack_list, sp_list) अणु
			p->sp_max_proto = locking_max_version;
		पूर्ण
	पूर्ण
	spin_unlock(&ocfs2_stack_lock);
पूर्ण
EXPORT_SYMBOL_GPL(ocfs2_stack_glue_set_max_proto_version);


/*
 * The ocfs2_dlm_lock() and ocfs2_dlm_unlock() functions take no argument
 * क्रम the ast and bast functions.  They will pass the lksb to the ast
 * and bast.  The caller can wrap the lksb with their own काष्ठाure to
 * get more inक्रमmation.
 */
पूर्णांक ocfs2_dlm_lock(काष्ठा ocfs2_cluster_connection *conn,
		   पूर्णांक mode,
		   काष्ठा ocfs2_dlm_lksb *lksb,
		   u32 flags,
		   व्योम *name,
		   अचिन्हित पूर्णांक namelen)
अणु
	अगर (!lksb->lksb_conn)
		lksb->lksb_conn = conn;
	अन्यथा
		BUG_ON(lksb->lksb_conn != conn);
	वापस active_stack->sp_ops->dlm_lock(conn, mode, lksb, flags,
					      name, namelen);
पूर्ण
EXPORT_SYMBOL_GPL(ocfs2_dlm_lock);

पूर्णांक ocfs2_dlm_unlock(काष्ठा ocfs2_cluster_connection *conn,
		     काष्ठा ocfs2_dlm_lksb *lksb,
		     u32 flags)
अणु
	BUG_ON(lksb->lksb_conn == शून्य);

	वापस active_stack->sp_ops->dlm_unlock(conn, lksb, flags);
पूर्ण
EXPORT_SYMBOL_GPL(ocfs2_dlm_unlock);

पूर्णांक ocfs2_dlm_lock_status(काष्ठा ocfs2_dlm_lksb *lksb)
अणु
	वापस active_stack->sp_ops->lock_status(lksb);
पूर्ण
EXPORT_SYMBOL_GPL(ocfs2_dlm_lock_status);

पूर्णांक ocfs2_dlm_lvb_valid(काष्ठा ocfs2_dlm_lksb *lksb)
अणु
	वापस active_stack->sp_ops->lvb_valid(lksb);
पूर्ण
EXPORT_SYMBOL_GPL(ocfs2_dlm_lvb_valid);

व्योम *ocfs2_dlm_lvb(काष्ठा ocfs2_dlm_lksb *lksb)
अणु
	वापस active_stack->sp_ops->lock_lvb(lksb);
पूर्ण
EXPORT_SYMBOL_GPL(ocfs2_dlm_lvb);

व्योम ocfs2_dlm_dump_lksb(काष्ठा ocfs2_dlm_lksb *lksb)
अणु
	active_stack->sp_ops->dump_lksb(lksb);
पूर्ण
EXPORT_SYMBOL_GPL(ocfs2_dlm_dump_lksb);

पूर्णांक ocfs2_stack_supports_plocks(व्योम)
अणु
	वापस active_stack && active_stack->sp_ops->plock;
पूर्ण
EXPORT_SYMBOL_GPL(ocfs2_stack_supports_plocks);

/*
 * ocfs2_plock() can only be safely called अगर
 * ocfs2_stack_supports_plocks() वापसed true
 */
पूर्णांक ocfs2_plock(काष्ठा ocfs2_cluster_connection *conn, u64 ino,
		काष्ठा file *file, पूर्णांक cmd, काष्ठा file_lock *fl)
अणु
	WARN_ON_ONCE(active_stack->sp_ops->plock == शून्य);
	अगर (active_stack->sp_ops->plock)
		वापस active_stack->sp_ops->plock(conn, ino, file, cmd, fl);
	वापस -EOPNOTSUPP;
पूर्ण
EXPORT_SYMBOL_GPL(ocfs2_plock);

पूर्णांक ocfs2_cluster_connect(स्थिर अक्षर *stack_name,
			  स्थिर अक्षर *cluster_name,
			  पूर्णांक cluster_name_len,
			  स्थिर अक्षर *group,
			  पूर्णांक grouplen,
			  काष्ठा ocfs2_locking_protocol *lproto,
			  व्योम (*recovery_handler)(पूर्णांक node_num,
						   व्योम *recovery_data),
			  व्योम *recovery_data,
			  काष्ठा ocfs2_cluster_connection **conn)
अणु
	पूर्णांक rc = 0;
	काष्ठा ocfs2_cluster_connection *new_conn;

	BUG_ON(group == शून्य);
	BUG_ON(conn == शून्य);
	BUG_ON(recovery_handler == शून्य);

	अगर (grouplen > GROUP_NAME_MAX) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (स_भेद(&lproto->lp_max_version, &locking_max_version,
		   माप(काष्ठा ocfs2_protocol_version))) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	new_conn = kzalloc(माप(काष्ठा ocfs2_cluster_connection),
			   GFP_KERNEL);
	अगर (!new_conn) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	strlcpy(new_conn->cc_name, group, GROUP_NAME_MAX + 1);
	new_conn->cc_namelen = grouplen;
	अगर (cluster_name_len)
		strlcpy(new_conn->cc_cluster_name, cluster_name,
			CLUSTER_NAME_MAX + 1);
	new_conn->cc_cluster_name_len = cluster_name_len;
	new_conn->cc_recovery_handler = recovery_handler;
	new_conn->cc_recovery_data = recovery_data;

	new_conn->cc_proto = lproto;
	/* Start the new connection at our maximum compatibility level */
	new_conn->cc_version = lproto->lp_max_version;

	/* This will pin the stack driver अगर successful */
	rc = ocfs2_stack_driver_get(stack_name);
	अगर (rc)
		जाओ out_मुक्त;

	rc = active_stack->sp_ops->connect(new_conn);
	अगर (rc) अणु
		ocfs2_stack_driver_put();
		जाओ out_मुक्त;
	पूर्ण

	*conn = new_conn;

out_मुक्त:
	अगर (rc)
		kमुक्त(new_conn);

out:
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(ocfs2_cluster_connect);

/* The caller will ensure all nodes have the same cluster stack */
पूर्णांक ocfs2_cluster_connect_agnostic(स्थिर अक्षर *group,
				   पूर्णांक grouplen,
				   काष्ठा ocfs2_locking_protocol *lproto,
				   व्योम (*recovery_handler)(पूर्णांक node_num,
							    व्योम *recovery_data),
				   व्योम *recovery_data,
				   काष्ठा ocfs2_cluster_connection **conn)
अणु
	अक्षर *stack_name = शून्य;

	अगर (cluster_stack_name[0])
		stack_name = cluster_stack_name;
	वापस ocfs2_cluster_connect(stack_name, शून्य, 0, group, grouplen,
				     lproto, recovery_handler, recovery_data,
				     conn);
पूर्ण
EXPORT_SYMBOL_GPL(ocfs2_cluster_connect_agnostic);

/* If hangup_pending is 0, the stack driver will be dropped */
पूर्णांक ocfs2_cluster_disconnect(काष्ठा ocfs2_cluster_connection *conn,
			     पूर्णांक hangup_pending)
अणु
	पूर्णांक ret;

	BUG_ON(conn == शून्य);

	ret = active_stack->sp_ops->disconnect(conn);

	/* XXX Should we मुक्त it anyway? */
	अगर (!ret) अणु
		kमुक्त(conn);
		अगर (!hangup_pending)
			ocfs2_stack_driver_put();
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ocfs2_cluster_disconnect);

/*
 * Leave the group क्रम this fileप्रणाली.  This is executed by a userspace
 * program (stored in ocfs2_hb_ctl_path).
 */
अटल व्योम ocfs2_leave_group(स्थिर अक्षर *group)
अणु
	पूर्णांक ret;
	अक्षर *argv[5], *envp[3];

	argv[0] = ocfs2_hb_ctl_path;
	argv[1] = "-K";
	argv[2] = "-u";
	argv[3] = (अक्षर *)group;
	argv[4] = शून्य;

	/* minimal command environment taken from cpu_run_sbin_hotplug */
	envp[0] = "HOME=/";
	envp[1] = "PATH=/sbin:/bin:/usr/sbin:/usr/bin";
	envp[2] = शून्य;

	ret = call_usermodehelper(argv[0], argv, envp, UMH_WAIT_PROC);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR
		       "ocfs2: Error %d running user helper "
		       "\"%s %s %s %s\"\n",
		       ret, argv[0], argv[1], argv[2], argv[3]);
	पूर्ण
पूर्ण

/*
 * Hangup is a required post-umount.  ocfs2-tools software expects the
 * fileप्रणाली to call "ocfs2_hb_ctl" during unmount.  This happens
 * regardless of whether the DLM got started, so we can't करो it
 * in ocfs2_cluster_disconnect().  The ocfs2_leave_group() function करोes
 * the actual work.
 */
व्योम ocfs2_cluster_hangup(स्थिर अक्षर *group, पूर्णांक grouplen)
अणु
	BUG_ON(group == शून्य);
	BUG_ON(group[grouplen] != '\0');

	ocfs2_leave_group(group);

	/* cluster_disconnect() was called with hangup_pending==1 */
	ocfs2_stack_driver_put();
पूर्ण
EXPORT_SYMBOL_GPL(ocfs2_cluster_hangup);

पूर्णांक ocfs2_cluster_this_node(काष्ठा ocfs2_cluster_connection *conn,
			    अचिन्हित पूर्णांक *node)
अणु
	वापस active_stack->sp_ops->this_node(conn, node);
पूर्ण
EXPORT_SYMBOL_GPL(ocfs2_cluster_this_node);


/*
 * Sysfs bits
 */

अटल sमाप_प्रकार ocfs2_max_locking_protocol_show(काष्ठा kobject *kobj,
					       काष्ठा kobj_attribute *attr,
					       अक्षर *buf)
अणु
	sमाप_प्रकार ret = 0;

	spin_lock(&ocfs2_stack_lock);
	अगर (locking_max_version.pv_major)
		ret = snम_लिखो(buf, PAGE_SIZE, "%u.%u\n",
			       locking_max_version.pv_major,
			       locking_max_version.pv_minor);
	spin_unlock(&ocfs2_stack_lock);

	वापस ret;
पूर्ण

अटल काष्ठा kobj_attribute ocfs2_attr_max_locking_protocol =
	__ATTR(max_locking_protocol, S_IRUGO,
	       ocfs2_max_locking_protocol_show, शून्य);

अटल sमाप_प्रकार ocfs2_loaded_cluster_plugins_show(काष्ठा kobject *kobj,
						 काष्ठा kobj_attribute *attr,
						 अक्षर *buf)
अणु
	sमाप_प्रकार ret = 0, total = 0, reमुख्य = PAGE_SIZE;
	काष्ठा ocfs2_stack_plugin *p;

	spin_lock(&ocfs2_stack_lock);
	list_क्रम_each_entry(p, &ocfs2_stack_list, sp_list) अणु
		ret = snम_लिखो(buf, reमुख्य, "%s\n",
			       p->sp_name);
		अगर (ret < 0) अणु
			total = ret;
			अवरोध;
		पूर्ण
		अगर (ret == reमुख्य) अणु
			/* snम_लिखो() didn't fit */
			total = -E2BIG;
			अवरोध;
		पूर्ण
		total += ret;
		reमुख्य -= ret;
	पूर्ण
	spin_unlock(&ocfs2_stack_lock);

	वापस total;
पूर्ण

अटल काष्ठा kobj_attribute ocfs2_attr_loaded_cluster_plugins =
	__ATTR(loaded_cluster_plugins, S_IRUGO,
	       ocfs2_loaded_cluster_plugins_show, शून्य);

अटल sमाप_प्रकार ocfs2_active_cluster_plugin_show(काष्ठा kobject *kobj,
						काष्ठा kobj_attribute *attr,
						अक्षर *buf)
अणु
	sमाप_प्रकार ret = 0;

	spin_lock(&ocfs2_stack_lock);
	अगर (active_stack) अणु
		ret = snम_लिखो(buf, PAGE_SIZE, "%s\n",
			       active_stack->sp_name);
		अगर (ret == PAGE_SIZE)
			ret = -E2BIG;
	पूर्ण
	spin_unlock(&ocfs2_stack_lock);

	वापस ret;
पूर्ण

अटल काष्ठा kobj_attribute ocfs2_attr_active_cluster_plugin =
	__ATTR(active_cluster_plugin, S_IRUGO,
	       ocfs2_active_cluster_plugin_show, शून्य);

अटल sमाप_प्रकार ocfs2_cluster_stack_show(काष्ठा kobject *kobj,
					काष्ठा kobj_attribute *attr,
					अक्षर *buf)
अणु
	sमाप_प्रकार ret;
	spin_lock(&ocfs2_stack_lock);
	ret = snम_लिखो(buf, PAGE_SIZE, "%s\n", cluster_stack_name);
	spin_unlock(&ocfs2_stack_lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार ocfs2_cluster_stack_store(काष्ठा kobject *kobj,
					 काष्ठा kobj_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	माप_प्रकार len = count;
	sमाप_प्रकार ret;

	अगर (len == 0)
		वापस len;

	अगर (buf[len - 1] == '\n')
		len--;

	अगर ((len != OCFS2_STACK_LABEL_LEN) ||
	    (strnlen(buf, len) != len))
		वापस -EINVAL;

	spin_lock(&ocfs2_stack_lock);
	अगर (active_stack) अणु
		अगर (!म_भेदन(buf, cluster_stack_name, len))
			ret = count;
		अन्यथा
			ret = -EBUSY;
	पूर्ण अन्यथा अणु
		स_नकल(cluster_stack_name, buf, len);
		ret = count;
	पूर्ण
	spin_unlock(&ocfs2_stack_lock);

	वापस ret;
पूर्ण


अटल काष्ठा kobj_attribute ocfs2_attr_cluster_stack =
	__ATTR(cluster_stack, S_IRUGO | S_IWUSR,
	       ocfs2_cluster_stack_show,
	       ocfs2_cluster_stack_store);



अटल sमाप_प्रकार ocfs2_dlm_recover_show(काष्ठा kobject *kobj,
					काष्ठा kobj_attribute *attr,
					अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "1\n");
पूर्ण

अटल काष्ठा kobj_attribute ocfs2_attr_dlm_recover_support =
	__ATTR(dlm_recover_callback_support, S_IRUGO,
	       ocfs2_dlm_recover_show, शून्य);

अटल काष्ठा attribute *ocfs2_attrs[] = अणु
	&ocfs2_attr_max_locking_protocol.attr,
	&ocfs2_attr_loaded_cluster_plugins.attr,
	&ocfs2_attr_active_cluster_plugin.attr,
	&ocfs2_attr_cluster_stack.attr,
	&ocfs2_attr_dlm_recover_support.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ocfs2_attr_group = अणु
	.attrs = ocfs2_attrs,
पूर्ण;

काष्ठा kset *ocfs2_kset;
EXPORT_SYMBOL_GPL(ocfs2_kset);

अटल व्योम ocfs2_sysfs_निकास(व्योम)
अणु
	kset_unरेजिस्टर(ocfs2_kset);
पूर्ण

अटल पूर्णांक ocfs2_sysfs_init(व्योम)
अणु
	पूर्णांक ret;

	ocfs2_kset = kset_create_and_add("ocfs2", शून्य, fs_kobj);
	अगर (!ocfs2_kset)
		वापस -ENOMEM;

	ret = sysfs_create_group(&ocfs2_kset->kobj, &ocfs2_attr_group);
	अगर (ret)
		जाओ error;

	वापस 0;

error:
	kset_unरेजिस्टर(ocfs2_kset);
	वापस ret;
पूर्ण

/*
 * Sysctl bits
 *
 * The sysctl lives at /proc/sys/fs/ocfs2/nm/hb_ctl_path.  The 'nm' doesn't
 * make as much sense in a multiple cluster stack world, but it's safer
 * and easier to preserve the name.
 */

अटल काष्ठा ctl_table ocfs2_nm_table[] = अणु
	अणु
		.procname	= "hb_ctl_path",
		.data		= ocfs2_hb_ctl_path,
		.maxlen		= OCFS2_MAX_HB_CTL_PATH,
		.mode		= 0644,
		.proc_handler	= proc_करोstring,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table ocfs2_mod_table[] = अणु
	अणु
		.procname	= "nm",
		.data		= शून्य,
		.maxlen		= 0,
		.mode		= 0555,
		.child		= ocfs2_nm_table
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table ocfs2_kern_table[] = अणु
	अणु
		.procname	= "ocfs2",
		.data		= शून्य,
		.maxlen		= 0,
		.mode		= 0555,
		.child		= ocfs2_mod_table
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table ocfs2_root_table[] = अणु
	अणु
		.procname	= "fs",
		.data		= शून्य,
		.maxlen		= 0,
		.mode		= 0555,
		.child		= ocfs2_kern_table
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table_header *ocfs2_table_header;


/*
 * Initialization
 */

अटल पूर्णांक __init ocfs2_stack_glue_init(व्योम)
अणु
	म_नकल(cluster_stack_name, OCFS2_STACK_PLUGIN_O2CB);

	ocfs2_table_header = रेजिस्टर_sysctl_table(ocfs2_root_table);
	अगर (!ocfs2_table_header) अणु
		prपूर्णांकk(KERN_ERR
		       "ocfs2 stack glue: unable to register sysctl\n");
		वापस -ENOMEM; /* or something. */
	पूर्ण

	वापस ocfs2_sysfs_init();
पूर्ण

अटल व्योम __निकास ocfs2_stack_glue_निकास(व्योम)
अणु
	स_रखो(&locking_max_version, 0,
	       माप(काष्ठा ocfs2_protocol_version));
	ocfs2_sysfs_निकास();
	अगर (ocfs2_table_header)
		unरेजिस्टर_sysctl_table(ocfs2_table_header);
पूर्ण

MODULE_AUTHOR("Oracle");
MODULE_DESCRIPTION("ocfs2 cluster stack glue layer");
MODULE_LICENSE("GPL");
module_init(ocfs2_stack_glue_init);
module_निकास(ocfs2_stack_glue_निकास);
