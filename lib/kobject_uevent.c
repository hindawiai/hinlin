<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * kernel userspace event delivery
 *
 * Copyright (C) 2004 Red Hat, Inc.  All rights reserved.
 * Copyright (C) 2004 Novell, Inc.  All rights reserved.
 * Copyright (C) 2004 IBM, Inc. All rights reserved.
 *
 * Authors:
 *	Robert Love		<rml@novell.com>
 *	Kay Sievers		<kay.sievers@vrfy.org>
 *	Arjan van de Ven	<arjanv@redhat.com>
 *	Greg Kroah-Harपंचांगan	<greg@kroah.com>
 */

#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/kobject.h>
#समावेश <linux/export.h>
#समावेश <linux/kmod.h>
#समावेश <linux/slab.h>
#समावेश <linux/socket.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netlink.h>
#समावेश <linux/uidgid.h>
#समावेश <linux/uuid.h>
#समावेश <linux/प्रकार.स>
#समावेश <net/sock.h>
#समावेश <net/netlink.h>
#समावेश <net/net_namespace.h>


u64 uevent_seqnum;
#अगर_घोषित CONFIG_UEVENT_HELPER
अक्षर uevent_helper[UEVENT_HELPER_PATH_LEN] = CONFIG_UEVENT_HELPER_PATH;
#पूर्ण_अगर

काष्ठा uevent_sock अणु
	काष्ठा list_head list;
	काष्ठा sock *sk;
पूर्ण;

#अगर_घोषित CONFIG_NET
अटल LIST_HEAD(uevent_sock_list);
#पूर्ण_अगर

/* This lock protects uevent_seqnum and uevent_sock_list */
अटल DEFINE_MUTEX(uevent_sock_mutex);

/* the strings here must match the क्रमागत in include/linux/kobject.h */
अटल स्थिर अक्षर *kobject_actions[] = अणु
	[KOBJ_ADD] =		"add",
	[KOBJ_REMOVE] =		"remove",
	[KOBJ_CHANGE] =		"change",
	[KOBJ_MOVE] =		"move",
	[KOBJ_ONLINE] =		"online",
	[KOBJ_OFFLINE] =	"offline",
	[KOBJ_BIND] =		"bind",
	[KOBJ_UNBIND] =		"unbind",
पूर्ण;

अटल पूर्णांक kobject_action_type(स्थिर अक्षर *buf, माप_प्रकार count,
			       क्रमागत kobject_action *type,
			       स्थिर अक्षर **args)
अणु
	क्रमागत kobject_action action;
	माप_प्रकार count_first;
	स्थिर अक्षर *args_start;
	पूर्णांक ret = -EINVAL;

	अगर (count && (buf[count-1] == '\n' || buf[count-1] == '\0'))
		count--;

	अगर (!count)
		जाओ out;

	args_start = strnchr(buf, count, ' ');
	अगर (args_start) अणु
		count_first = args_start - buf;
		args_start = args_start + 1;
	पूर्ण अन्यथा
		count_first = count;

	क्रम (action = 0; action < ARRAY_SIZE(kobject_actions); action++) अणु
		अगर (म_भेदन(kobject_actions[action], buf, count_first) != 0)
			जारी;
		अगर (kobject_actions[action][count_first] != '\0')
			जारी;
		अगर (args)
			*args = args_start;
		*type = action;
		ret = 0;
		अवरोध;
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल स्थिर अक्षर *action_arg_word_end(स्थिर अक्षर *buf, स्थिर अक्षर *buf_end,
				       अक्षर delim)
अणु
	स्थिर अक्षर *next = buf;

	जबतक (next <= buf_end && *next != delim)
		अगर (!है_अक्षर_अंक(*next++))
			वापस शून्य;

	अगर (next == buf)
		वापस शून्य;

	वापस next;
पूर्ण

अटल पूर्णांक kobject_action_args(स्थिर अक्षर *buf, माप_प्रकार count,
			       काष्ठा kobj_uevent_env **ret_env)
अणु
	काष्ठा kobj_uevent_env *env = शून्य;
	स्थिर अक्षर *next, *buf_end, *key;
	पूर्णांक key_len;
	पूर्णांक r = -EINVAL;

	अगर (count && (buf[count - 1] == '\n' || buf[count - 1] == '\0'))
		count--;

	अगर (!count)
		वापस -EINVAL;

	env = kzalloc(माप(*env), GFP_KERNEL);
	अगर (!env)
		वापस -ENOMEM;

	/* first arg is UUID */
	अगर (count < UUID_STRING_LEN || !uuid_is_valid(buf) ||
	    add_uevent_var(env, "SYNTH_UUID=%.*s", UUID_STRING_LEN, buf))
		जाओ out;

	/*
	 * the rest are custom environment variables in KEY=VALUE
	 * क्रमmat with ' ' delimiter between each KEY=VALUE pair
	 */
	next = buf + UUID_STRING_LEN;
	buf_end = buf + count - 1;

	जबतक (next <= buf_end) अणु
		अगर (*next != ' ')
			जाओ out;

		/* skip the ' ', key must follow */
		key = ++next;
		अगर (key > buf_end)
			जाओ out;

		buf = next;
		next = action_arg_word_end(buf, buf_end, '=');
		अगर (!next || next > buf_end || *next != '=')
			जाओ out;
		key_len = next - buf;

		/* skip the '=', value must follow */
		अगर (++next > buf_end)
			जाओ out;

		buf = next;
		next = action_arg_word_end(buf, buf_end, ' ');
		अगर (!next)
			जाओ out;

		अगर (add_uevent_var(env, "SYNTH_ARG_%.*s=%.*s",
				   key_len, key, (पूर्णांक) (next - buf), buf))
			जाओ out;
	पूर्ण

	r = 0;
out:
	अगर (r)
		kमुक्त(env);
	अन्यथा
		*ret_env = env;
	वापस r;
पूर्ण

/**
 * kobject_synth_uevent - send synthetic uevent with arguments
 *
 * @kobj: काष्ठा kobject क्रम which synthetic uevent is to be generated
 * @buf: buffer containing action type and action args, newline is ignored
 * @count: length of buffer
 *
 * Returns 0 अगर kobject_synthetic_uevent() is completed with success or the
 * corresponding error when it fails.
 */
पूर्णांक kobject_synth_uevent(काष्ठा kobject *kobj, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अक्षर *no_uuid_envp[] = अणु "SYNTH_UUID=0", शून्य पूर्ण;
	क्रमागत kobject_action action;
	स्थिर अक्षर *action_args;
	काष्ठा kobj_uevent_env *env;
	स्थिर अक्षर *msg = शून्य, *devpath;
	पूर्णांक r;

	r = kobject_action_type(buf, count, &action, &action_args);
	अगर (r) अणु
		msg = "unknown uevent action string";
		जाओ out;
	पूर्ण

	अगर (!action_args) अणु
		r = kobject_uevent_env(kobj, action, no_uuid_envp);
		जाओ out;
	पूर्ण

	r = kobject_action_args(action_args,
				count - (action_args - buf), &env);
	अगर (r == -EINVAL) अणु
		msg = "incorrect uevent action arguments";
		जाओ out;
	पूर्ण

	अगर (r)
		जाओ out;

	r = kobject_uevent_env(kobj, action, env->envp);
	kमुक्त(env);
out:
	अगर (r) अणु
		devpath = kobject_get_path(kobj, GFP_KERNEL);
		pr_warn("synth uevent: %s: %s\n",
		       devpath ?: "unknown device",
		       msg ?: "failed to send uevent");
		kमुक्त(devpath);
	पूर्ण
	वापस r;
पूर्ण

#अगर_घोषित CONFIG_UEVENT_HELPER
अटल पूर्णांक kobj_usermode_filter(काष्ठा kobject *kobj)
अणु
	स्थिर काष्ठा kobj_ns_type_operations *ops;

	ops = kobj_ns_ops(kobj);
	अगर (ops) अणु
		स्थिर व्योम *init_ns, *ns;

		ns = kobj->ktype->namespace(kobj);
		init_ns = ops->initial_ns();
		वापस ns != init_ns;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक init_uevent_argv(काष्ठा kobj_uevent_env *env, स्थिर अक्षर *subप्रणाली)
अणु
	पूर्णांक buffer_size = माप(env->buf) - env->buflen;
	पूर्णांक len;

	len = strlcpy(&env->buf[env->buflen], subप्रणाली, buffer_size);
	अगर (len >= buffer_size) अणु
		pr_warn("init_uevent_argv: buffer size of %d too small, needed %d\n",
			buffer_size, len);
		वापस -ENOMEM;
	पूर्ण

	env->argv[0] = uevent_helper;
	env->argv[1] = &env->buf[env->buflen];
	env->argv[2] = शून्य;

	env->buflen += len + 1;
	वापस 0;
पूर्ण

अटल व्योम cleanup_uevent_env(काष्ठा subprocess_info *info)
अणु
	kमुक्त(info->data);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_NET
अटल काष्ठा sk_buff *alloc_uevent_skb(काष्ठा kobj_uevent_env *env,
					स्थिर अक्षर *action_string,
					स्थिर अक्षर *devpath)
अणु
	काष्ठा netlink_skb_parms *parms;
	काष्ठा sk_buff *skb = शून्य;
	अक्षर *scratch;
	माप_प्रकार len;

	/* allocate message with maximum possible size */
	len = म_माप(action_string) + म_माप(devpath) + 2;
	skb = alloc_skb(len + env->buflen, GFP_KERNEL);
	अगर (!skb)
		वापस शून्य;

	/* add header */
	scratch = skb_put(skb, len);
	प्र_लिखो(scratch, "%s@%s", action_string, devpath);

	skb_put_data(skb, env->buf, env->buflen);

	parms = &NETLINK_CB(skb);
	parms->creds.uid = GLOBAL_ROOT_UID;
	parms->creds.gid = GLOBAL_ROOT_GID;
	parms->dst_group = 1;
	parms->portid = 0;

	वापस skb;
पूर्ण

अटल पूर्णांक uevent_net_broadcast_untagged(काष्ठा kobj_uevent_env *env,
					 स्थिर अक्षर *action_string,
					 स्थिर अक्षर *devpath)
अणु
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा uevent_sock *ue_sk;
	पूर्णांक retval = 0;

	/* send netlink message */
	list_क्रम_each_entry(ue_sk, &uevent_sock_list, list) अणु
		काष्ठा sock *uevent_sock = ue_sk->sk;

		अगर (!netlink_has_listeners(uevent_sock, 1))
			जारी;

		अगर (!skb) अणु
			retval = -ENOMEM;
			skb = alloc_uevent_skb(env, action_string, devpath);
			अगर (!skb)
				जारी;
		पूर्ण

		retval = netlink_broadcast(uevent_sock, skb_get(skb), 0, 1,
					   GFP_KERNEL);
		/* ENOBUFS should be handled in userspace */
		अगर (retval == -ENOBUFS || retval == -ESRCH)
			retval = 0;
	पूर्ण
	consume_skb(skb);

	वापस retval;
पूर्ण

अटल पूर्णांक uevent_net_broadcast_tagged(काष्ठा sock *usk,
				       काष्ठा kobj_uevent_env *env,
				       स्थिर अक्षर *action_string,
				       स्थिर अक्षर *devpath)
अणु
	काष्ठा user_namespace *owning_user_ns = sock_net(usk)->user_ns;
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक ret = 0;

	skb = alloc_uevent_skb(env, action_string, devpath);
	अगर (!skb)
		वापस -ENOMEM;

	/* fix credentials */
	अगर (owning_user_ns != &init_user_ns) अणु
		काष्ठा netlink_skb_parms *parms = &NETLINK_CB(skb);
		kuid_t root_uid;
		kgid_t root_gid;

		/* fix uid */
		root_uid = make_kuid(owning_user_ns, 0);
		अगर (uid_valid(root_uid))
			parms->creds.uid = root_uid;

		/* fix gid */
		root_gid = make_kgid(owning_user_ns, 0);
		अगर (gid_valid(root_gid))
			parms->creds.gid = root_gid;
	पूर्ण

	ret = netlink_broadcast(usk, skb, 0, 1, GFP_KERNEL);
	/* ENOBUFS should be handled in userspace */
	अगर (ret == -ENOBUFS || ret == -ESRCH)
		ret = 0;

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक kobject_uevent_net_broadcast(काष्ठा kobject *kobj,
					काष्ठा kobj_uevent_env *env,
					स्थिर अक्षर *action_string,
					स्थिर अक्षर *devpath)
अणु
	पूर्णांक ret = 0;

#अगर_घोषित CONFIG_NET
	स्थिर काष्ठा kobj_ns_type_operations *ops;
	स्थिर काष्ठा net *net = शून्य;

	ops = kobj_ns_ops(kobj);
	अगर (!ops && kobj->kset) अणु
		काष्ठा kobject *ksobj = &kobj->kset->kobj;

		अगर (ksobj->parent != शून्य)
			ops = kobj_ns_ops(ksobj->parent);
	पूर्ण

	/* kobjects currently only carry network namespace tags and they
	 * are the only tag relevant here since we want to decide which
	 * network namespaces to broadcast the uevent पूर्णांकo.
	 */
	अगर (ops && ops->netlink_ns && kobj->ktype->namespace)
		अगर (ops->type == KOBJ_NS_TYPE_NET)
			net = kobj->ktype->namespace(kobj);

	अगर (!net)
		ret = uevent_net_broadcast_untagged(env, action_string,
						    devpath);
	अन्यथा
		ret = uevent_net_broadcast_tagged(net->uevent_sock->sk, env,
						  action_string, devpath);
#पूर्ण_अगर

	वापस ret;
पूर्ण

अटल व्योम zap_modalias_env(काष्ठा kobj_uevent_env *env)
अणु
	अटल स्थिर अक्षर modalias_prefix[] = "MODALIAS=";
	माप_प्रकार len;
	पूर्णांक i, j;

	क्रम (i = 0; i < env->envp_idx;) अणु
		अगर (म_भेदन(env->envp[i], modalias_prefix,
			    माप(modalias_prefix) - 1)) अणु
			i++;
			जारी;
		पूर्ण

		len = म_माप(env->envp[i]) + 1;

		अगर (i != env->envp_idx - 1) अणु
			स_हटाओ(env->envp[i], env->envp[i + 1],
				env->buflen - len);

			क्रम (j = i; j < env->envp_idx - 1; j++)
				env->envp[j] = env->envp[j + 1] - len;
		पूर्ण

		env->envp_idx--;
		env->buflen -= len;
	पूर्ण
पूर्ण

/**
 * kobject_uevent_env - send an uevent with environmental data
 *
 * @kobj: काष्ठा kobject that the action is happening to
 * @action: action that is happening
 * @envp_ext: poपूर्णांकer to environmental data
 *
 * Returns 0 अगर kobject_uevent_env() is completed with success or the
 * corresponding error when it fails.
 */
पूर्णांक kobject_uevent_env(काष्ठा kobject *kobj, क्रमागत kobject_action action,
		       अक्षर *envp_ext[])
अणु
	काष्ठा kobj_uevent_env *env;
	स्थिर अक्षर *action_string = kobject_actions[action];
	स्थिर अक्षर *devpath = शून्य;
	स्थिर अक्षर *subप्रणाली;
	काष्ठा kobject *top_kobj;
	काष्ठा kset *kset;
	स्थिर काष्ठा kset_uevent_ops *uevent_ops;
	पूर्णांक i = 0;
	पूर्णांक retval = 0;

	/*
	 * Mark "remove" event करोne regardless of result, क्रम some subप्रणालीs
	 * करो not want to re-trigger "remove" event via स्वतःmatic cleanup.
	 */
	अगर (action == KOBJ_REMOVE)
		kobj->state_हटाओ_uevent_sent = 1;

	pr_debug("kobject: '%s' (%p): %s\n",
		 kobject_name(kobj), kobj, __func__);

	/* search the kset we beदीर्घ to */
	top_kobj = kobj;
	जबतक (!top_kobj->kset && top_kobj->parent)
		top_kobj = top_kobj->parent;

	अगर (!top_kobj->kset) अणु
		pr_debug("kobject: '%s' (%p): %s: attempted to send uevent "
			 "without kset!\n", kobject_name(kobj), kobj,
			 __func__);
		वापस -EINVAL;
	पूर्ण

	kset = top_kobj->kset;
	uevent_ops = kset->uevent_ops;

	/* skip the event, अगर uevent_suppress is set*/
	अगर (kobj->uevent_suppress) अणु
		pr_debug("kobject: '%s' (%p): %s: uevent_suppress "
				 "caused the event to drop!\n",
				 kobject_name(kobj), kobj, __func__);
		वापस 0;
	पूर्ण
	/* skip the event, अगर the filter वापसs zero. */
	अगर (uevent_ops && uevent_ops->filter)
		अगर (!uevent_ops->filter(kset, kobj)) अणु
			pr_debug("kobject: '%s' (%p): %s: filter function "
				 "caused the event to drop!\n",
				 kobject_name(kobj), kobj, __func__);
			वापस 0;
		पूर्ण

	/* originating subप्रणाली */
	अगर (uevent_ops && uevent_ops->name)
		subप्रणाली = uevent_ops->name(kset, kobj);
	अन्यथा
		subप्रणाली = kobject_name(&kset->kobj);
	अगर (!subप्रणाली) अणु
		pr_debug("kobject: '%s' (%p): %s: unset subsystem caused the "
			 "event to drop!\n", kobject_name(kobj), kobj,
			 __func__);
		वापस 0;
	पूर्ण

	/* environment buffer */
	env = kzalloc(माप(काष्ठा kobj_uevent_env), GFP_KERNEL);
	अगर (!env)
		वापस -ENOMEM;

	/* complete object path */
	devpath = kobject_get_path(kobj, GFP_KERNEL);
	अगर (!devpath) अणु
		retval = -ENOENT;
		जाओ निकास;
	पूर्ण

	/* शेष keys */
	retval = add_uevent_var(env, "ACTION=%s", action_string);
	अगर (retval)
		जाओ निकास;
	retval = add_uevent_var(env, "DEVPATH=%s", devpath);
	अगर (retval)
		जाओ निकास;
	retval = add_uevent_var(env, "SUBSYSTEM=%s", subप्रणाली);
	अगर (retval)
		जाओ निकास;

	/* keys passed in from the caller */
	अगर (envp_ext) अणु
		क्रम (i = 0; envp_ext[i]; i++) अणु
			retval = add_uevent_var(env, "%s", envp_ext[i]);
			अगर (retval)
				जाओ निकास;
		पूर्ण
	पूर्ण

	/* let the kset specअगरic function add its stuff */
	अगर (uevent_ops && uevent_ops->uevent) अणु
		retval = uevent_ops->uevent(kset, kobj, env);
		अगर (retval) अणु
			pr_debug("kobject: '%s' (%p): %s: uevent() returned "
				 "%d\n", kobject_name(kobj), kobj,
				 __func__, retval);
			जाओ निकास;
		पूर्ण
	पूर्ण

	चयन (action) अणु
	हाल KOBJ_ADD:
		/*
		 * Mark "add" event so we can make sure we deliver "remove"
		 * event to userspace during स्वतःmatic cleanup. If
		 * the object did send an "add" event, "remove" will
		 * स्वतःmatically generated by the core, अगर not alपढ़ोy करोne
		 * by the caller.
		 */
		kobj->state_add_uevent_sent = 1;
		अवरोध;

	हाल KOBJ_UNBIND:
		zap_modalias_env(env);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	mutex_lock(&uevent_sock_mutex);
	/* we will send an event, so request a new sequence number */
	retval = add_uevent_var(env, "SEQNUM=%llu", ++uevent_seqnum);
	अगर (retval) अणु
		mutex_unlock(&uevent_sock_mutex);
		जाओ निकास;
	पूर्ण
	retval = kobject_uevent_net_broadcast(kobj, env, action_string,
					      devpath);
	mutex_unlock(&uevent_sock_mutex);

#अगर_घोषित CONFIG_UEVENT_HELPER
	/* call uevent_helper, usually only enabled during early boot */
	अगर (uevent_helper[0] && !kobj_usermode_filter(kobj)) अणु
		काष्ठा subprocess_info *info;

		retval = add_uevent_var(env, "HOME=/");
		अगर (retval)
			जाओ निकास;
		retval = add_uevent_var(env,
					"PATH=/sbin:/bin:/usr/sbin:/usr/bin");
		अगर (retval)
			जाओ निकास;
		retval = init_uevent_argv(env, subप्रणाली);
		अगर (retval)
			जाओ निकास;

		retval = -ENOMEM;
		info = call_usermodehelper_setup(env->argv[0], env->argv,
						 env->envp, GFP_KERNEL,
						 शून्य, cleanup_uevent_env, env);
		अगर (info) अणु
			retval = call_usermodehelper_exec(info, UMH_NO_WAIT);
			env = शून्य;	/* मुक्तd by cleanup_uevent_env */
		पूर्ण
	पूर्ण
#पूर्ण_अगर

निकास:
	kमुक्त(devpath);
	kमुक्त(env);
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(kobject_uevent_env);

/**
 * kobject_uevent - notअगरy userspace by sending an uevent
 *
 * @kobj: काष्ठा kobject that the action is happening to
 * @action: action that is happening
 *
 * Returns 0 अगर kobject_uevent() is completed with success or the
 * corresponding error when it fails.
 */
पूर्णांक kobject_uevent(काष्ठा kobject *kobj, क्रमागत kobject_action action)
अणु
	वापस kobject_uevent_env(kobj, action, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(kobject_uevent);

/**
 * add_uevent_var - add key value string to the environment buffer
 * @env: environment buffer काष्ठाure
 * @क्रमmat: म_लिखो क्रमmat क्रम the key=value pair
 *
 * Returns 0 अगर environment variable was added successfully or -ENOMEM
 * अगर no space was available.
 */
पूर्णांक add_uevent_var(काष्ठा kobj_uevent_env *env, स्थिर अक्षर *क्रमmat, ...)
अणु
	बहु_सूची args;
	पूर्णांक len;

	अगर (env->envp_idx >= ARRAY_SIZE(env->envp)) अणु
		WARN(1, KERN_ERR "add_uevent_var: too many keys\n");
		वापस -ENOMEM;
	पूर्ण

	बहु_शुरू(args, क्रमmat);
	len = vsnम_लिखो(&env->buf[env->buflen],
			माप(env->buf) - env->buflen,
			क्रमmat, args);
	बहु_पूर्ण(args);

	अगर (len >= (माप(env->buf) - env->buflen)) अणु
		WARN(1, KERN_ERR "add_uevent_var: buffer size too small\n");
		वापस -ENOMEM;
	पूर्ण

	env->envp[env->envp_idx++] = &env->buf[env->buflen];
	env->buflen += len + 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(add_uevent_var);

#अगर defined(CONFIG_NET)
अटल पूर्णांक uevent_net_broadcast(काष्ठा sock *usk, काष्ठा sk_buff *skb,
				काष्ठा netlink_ext_ack *extack)
अणु
	/* u64 to अक्षरs: 2^64 - 1 = 21 अक्षरs */
	अक्षर buf[माप("SEQNUM=") + 21];
	काष्ठा sk_buff *skbc;
	पूर्णांक ret;

	/* bump and prepare sequence number */
	ret = snम_लिखो(buf, माप(buf), "SEQNUM=%llu", ++uevent_seqnum);
	अगर (ret < 0 || (माप_प्रकार)ret >= माप(buf))
		वापस -ENOMEM;
	ret++;

	/* verअगरy message करोes not overflow */
	अगर ((skb->len + ret) > UEVENT_BUFFER_SIZE) अणु
		NL_SET_ERR_MSG(extack, "uevent message too big");
		वापस -EINVAL;
	पूर्ण

	/* copy skb and extend to accommodate sequence number */
	skbc = skb_copy_expand(skb, 0, ret, GFP_KERNEL);
	अगर (!skbc)
		वापस -ENOMEM;

	/* append sequence number */
	skb_put_data(skbc, buf, ret);

	/* हटाओ msg header */
	skb_pull(skbc, NLMSG_HDRLEN);

	/* set portid 0 to inक्रमm userspace message comes from kernel */
	NETLINK_CB(skbc).portid = 0;
	NETLINK_CB(skbc).dst_group = 1;

	ret = netlink_broadcast(usk, skbc, 0, 1, GFP_KERNEL);
	/* ENOBUFS should be handled in userspace */
	अगर (ret == -ENOBUFS || ret == -ESRCH)
		ret = 0;

	वापस ret;
पूर्ण

अटल पूर्णांक uevent_net_rcv_skb(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net;
	पूर्णांक ret;

	अगर (!nlmsg_data(nlh))
		वापस -EINVAL;

	/*
	 * Verअगरy that we are allowed to send messages to the target
	 * network namespace. The caller must have CAP_SYS_ADMIN in the
	 * owning user namespace of the target network namespace.
	 */
	net = sock_net(NETLINK_CB(skb).sk);
	अगर (!netlink_ns_capable(skb, net->user_ns, CAP_SYS_ADMIN)) अणु
		NL_SET_ERR_MSG(extack, "missing CAP_SYS_ADMIN capability");
		वापस -EPERM;
	पूर्ण

	mutex_lock(&uevent_sock_mutex);
	ret = uevent_net_broadcast(net->uevent_sock->sk, skb, extack);
	mutex_unlock(&uevent_sock_mutex);

	वापस ret;
पूर्ण

अटल व्योम uevent_net_rcv(काष्ठा sk_buff *skb)
अणु
	netlink_rcv_skb(skb, &uevent_net_rcv_skb);
पूर्ण

अटल पूर्णांक uevent_net_init(काष्ठा net *net)
अणु
	काष्ठा uevent_sock *ue_sk;
	काष्ठा netlink_kernel_cfg cfg = अणु
		.groups	= 1,
		.input = uevent_net_rcv,
		.flags	= NL_CFG_F_NONROOT_RECV
	पूर्ण;

	ue_sk = kzalloc(माप(*ue_sk), GFP_KERNEL);
	अगर (!ue_sk)
		वापस -ENOMEM;

	ue_sk->sk = netlink_kernel_create(net, NETLINK_KOBJECT_UEVENT, &cfg);
	अगर (!ue_sk->sk) अणु
		pr_err("kobject_uevent: unable to create netlink socket!\n");
		kमुक्त(ue_sk);
		वापस -ENODEV;
	पूर्ण

	net->uevent_sock = ue_sk;

	/* Restrict uevents to initial user namespace. */
	अगर (sock_net(ue_sk->sk)->user_ns == &init_user_ns) अणु
		mutex_lock(&uevent_sock_mutex);
		list_add_tail(&ue_sk->list, &uevent_sock_list);
		mutex_unlock(&uevent_sock_mutex);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम uevent_net_निकास(काष्ठा net *net)
अणु
	काष्ठा uevent_sock *ue_sk = net->uevent_sock;

	अगर (sock_net(ue_sk->sk)->user_ns == &init_user_ns) अणु
		mutex_lock(&uevent_sock_mutex);
		list_del(&ue_sk->list);
		mutex_unlock(&uevent_sock_mutex);
	पूर्ण

	netlink_kernel_release(ue_sk->sk);
	kमुक्त(ue_sk);
पूर्ण

अटल काष्ठा pernet_operations uevent_net_ops = अणु
	.init	= uevent_net_init,
	.निकास	= uevent_net_निकास,
पूर्ण;

अटल पूर्णांक __init kobject_uevent_init(व्योम)
अणु
	वापस रेजिस्टर_pernet_subsys(&uevent_net_ops);
पूर्ण


postcore_initcall(kobject_uevent_init);
#पूर्ण_अगर
