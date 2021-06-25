<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  linux/drivers/net/netconsole.c
 *
 *  Copyright (C) 2001  Ingo Molnar <mingo@redhat.com>
 *
 *  This file contains the implementation of an IRQ-safe, crash-safe
 *  kernel console implementation that outमाला_दो kernel messages to the
 *  network.
 *
 * Modअगरication history:
 *
 * 2001-09-17    started by Ingo Molnar.
 * 2003-08-11    2.6 port by Matt Mackall
 *               simplअगरied options
 *               generic card hooks
 *               works non-modular
 * 2003-09-07    rewritten with netpoll api
 */

/****************************************************************
 *
 ****************************************************************/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/console.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/netpoll.h>
#समावेश <linux/inet.h>
#समावेश <linux/configfs.h>
#समावेश <linux/etherdevice.h>

MODULE_AUTHOR("Maintainer: Matt Mackall <mpm@selenic.com>");
MODULE_DESCRIPTION("Console driver for network interfaces");
MODULE_LICENSE("GPL");

#घोषणा MAX_PARAM_LENGTH	256
#घोषणा MAX_PRINT_CHUNK		1000

अटल अक्षर config[MAX_PARAM_LENGTH];
module_param_string(netconsole, config, MAX_PARAM_LENGTH, 0);
MODULE_PARM_DESC(netconsole, " netconsole=[src-port]@[src-ip]/[dev],[tgt-port]@<tgt-ip>/[tgt-macaddr]");

अटल bool oops_only = false;
module_param(oops_only, bool, 0600);
MODULE_PARM_DESC(oops_only, "Only log oops messages");

#अगर_अघोषित	MODULE
अटल पूर्णांक __init option_setup(अक्षर *opt)
अणु
	strlcpy(config, opt, MAX_PARAM_LENGTH);
	वापस 1;
पूर्ण
__setup("netconsole=", option_setup);
#पूर्ण_अगर	/* MODULE */

/* Linked list of all configured tarमाला_लो */
अटल LIST_HEAD(target_list);

/* This needs to be a spinlock because ग_लिखो_msg() cannot sleep */
अटल DEFINE_SPINLOCK(target_list_lock);

/*
 * Console driver क्रम extended netconsoles.  Registered on the first use to
 * aव्योम unnecessarily enabling ext message क्रमmatting.
 */
अटल काष्ठा console netconsole_ext;

/**
 * काष्ठा netconsole_target - Represents a configured netconsole target.
 * @list:	Links this target पूर्णांकo the target_list.
 * @item:	Links us पूर्णांकo the configfs subप्रणाली hierarchy.
 * @enabled:	On / off knob to enable / disable target.
 *		Visible from userspace (पढ़ो-ग_लिखो).
 *		We मुख्यtain a strict 1:1 correspondence between this and
 *		whether the corresponding netpoll is active or inactive.
 *		Also, other parameters of a target may be modअगरied at
 *		runसमय only when it is disabled (enabled == 0).
 * @extended:	Denotes whether console is extended or not.
 * @np:		The netpoll काष्ठाure क्रम this target.
 *		Contains the other userspace visible parameters:
 *		dev_name	(पढ़ो-ग_लिखो)
 *		local_port	(पढ़ो-ग_लिखो)
 *		remote_port	(पढ़ो-ग_लिखो)
 *		local_ip	(पढ़ो-ग_लिखो)
 *		remote_ip	(पढ़ो-ग_लिखो)
 *		local_mac	(पढ़ो-only)
 *		remote_mac	(पढ़ो-ग_लिखो)
 */
काष्ठा netconsole_target अणु
	काष्ठा list_head	list;
#अगर_घोषित	CONFIG_NETCONSOLE_DYNAMIC
	काष्ठा config_item	item;
#पूर्ण_अगर
	bool			enabled;
	bool			extended;
	काष्ठा netpoll		np;
पूर्ण;

#अगर_घोषित	CONFIG_NETCONSOLE_DYNAMIC

अटल काष्ठा configfs_subप्रणाली netconsole_subsys;
अटल DEFINE_MUTEX(dynamic_netconsole_mutex);

अटल पूर्णांक __init dynamic_netconsole_init(व्योम)
अणु
	config_group_init(&netconsole_subsys.su_group);
	mutex_init(&netconsole_subsys.su_mutex);
	वापस configfs_रेजिस्टर_subप्रणाली(&netconsole_subsys);
पूर्ण

अटल व्योम __निकास dynamic_netconsole_निकास(व्योम)
अणु
	configfs_unरेजिस्टर_subप्रणाली(&netconsole_subsys);
पूर्ण

/*
 * Tarमाला_लो that were created by parsing the boot/module option string
 * करो not exist in the configfs hierarchy (and have शून्य names) and will
 * never go away, so make these a no-op क्रम them.
 */
अटल व्योम netconsole_target_get(काष्ठा netconsole_target *nt)
अणु
	अगर (config_item_name(&nt->item))
		config_item_get(&nt->item);
पूर्ण

अटल व्योम netconsole_target_put(काष्ठा netconsole_target *nt)
अणु
	अगर (config_item_name(&nt->item))
		config_item_put(&nt->item);
पूर्ण

#अन्यथा	/* !CONFIG_NETCONSOLE_DYNAMIC */

अटल पूर्णांक __init dynamic_netconsole_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम __निकास dynamic_netconsole_निकास(व्योम)
अणु
पूर्ण

/*
 * No danger of tarमाला_लो going away from under us when dynamic
 * reconfigurability is off.
 */
अटल व्योम netconsole_target_get(काष्ठा netconsole_target *nt)
अणु
पूर्ण

अटल व्योम netconsole_target_put(काष्ठा netconsole_target *nt)
अणु
पूर्ण

#पूर्ण_अगर	/* CONFIG_NETCONSOLE_DYNAMIC */

/* Allocate new target (from boot/module param) and setup netpoll क्रम it */
अटल काष्ठा netconsole_target *alloc_param_target(अक्षर *target_config)
अणु
	पूर्णांक err = -ENOMEM;
	काष्ठा netconsole_target *nt;

	/*
	 * Allocate and initialize with शेषs.
	 * Note that these tarमाला_लो get their config_item fields zeroed-out.
	 */
	nt = kzalloc(माप(*nt), GFP_KERNEL);
	अगर (!nt)
		जाओ fail;

	nt->np.name = "netconsole";
	strlcpy(nt->np.dev_name, "eth0", IFNAMSIZ);
	nt->np.local_port = 6665;
	nt->np.remote_port = 6666;
	eth_broadcast_addr(nt->np.remote_mac);

	अगर (*target_config == '+') अणु
		nt->extended = true;
		target_config++;
	पूर्ण

	/* Parse parameters and setup netpoll */
	err = netpoll_parse_options(&nt->np, target_config);
	अगर (err)
		जाओ fail;

	err = netpoll_setup(&nt->np);
	अगर (err)
		जाओ fail;

	nt->enabled = true;

	वापस nt;

fail:
	kमुक्त(nt);
	वापस ERR_PTR(err);
पूर्ण

/* Cleanup netpoll क्रम given target (from boot/module param) and मुक्त it */
अटल व्योम मुक्त_param_target(काष्ठा netconsole_target *nt)
अणु
	netpoll_cleanup(&nt->np);
	kमुक्त(nt);
पूर्ण

#अगर_घोषित	CONFIG_NETCONSOLE_DYNAMIC

/*
 * Our subप्रणाली hierarchy is:
 *
 * /sys/kernel/config/netconsole/
 *				|
 *				<target>/
 *				|	enabled
 *				|	dev_name
 *				|	local_port
 *				|	remote_port
 *				|	local_ip
 *				|	remote_ip
 *				|	local_mac
 *				|	remote_mac
 *				|
 *				<target>/...
 */

अटल काष्ठा netconsole_target *to_target(काष्ठा config_item *item)
अणु
	वापस item ?
		container_of(item, काष्ठा netconsole_target, item) :
		शून्य;
पूर्ण

/*
 * Attribute operations क्रम netconsole_target.
 */

अटल sमाप_प्रकार enabled_show(काष्ठा config_item *item, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", to_target(item)->enabled);
पूर्ण

अटल sमाप_प्रकार extended_show(काष्ठा config_item *item, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", to_target(item)->extended);
पूर्ण

अटल sमाप_प्रकार dev_name_show(काष्ठा config_item *item, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", to_target(item)->np.dev_name);
पूर्ण

अटल sमाप_प्रकार local_port_show(काष्ठा config_item *item, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", to_target(item)->np.local_port);
पूर्ण

अटल sमाप_प्रकार remote_port_show(काष्ठा config_item *item, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", to_target(item)->np.remote_port);
पूर्ण

अटल sमाप_प्रकार local_ip_show(काष्ठा config_item *item, अक्षर *buf)
अणु
	काष्ठा netconsole_target *nt = to_target(item);

	अगर (nt->np.ipv6)
		वापस snम_लिखो(buf, PAGE_SIZE, "%pI6c\n", &nt->np.local_ip.in6);
	अन्यथा
		वापस snम_लिखो(buf, PAGE_SIZE, "%pI4\n", &nt->np.local_ip);
पूर्ण

अटल sमाप_प्रकार remote_ip_show(काष्ठा config_item *item, अक्षर *buf)
अणु
	काष्ठा netconsole_target *nt = to_target(item);

	अगर (nt->np.ipv6)
		वापस snम_लिखो(buf, PAGE_SIZE, "%pI6c\n", &nt->np.remote_ip.in6);
	अन्यथा
		वापस snम_लिखो(buf, PAGE_SIZE, "%pI4\n", &nt->np.remote_ip);
पूर्ण

अटल sमाप_प्रकार local_mac_show(काष्ठा config_item *item, अक्षर *buf)
अणु
	काष्ठा net_device *dev = to_target(item)->np.dev;
	अटल स्थिर u8 bcast[ETH_ALEN] = अणु 0xff, 0xff, 0xff, 0xff, 0xff, 0xff पूर्ण;

	वापस snम_लिखो(buf, PAGE_SIZE, "%pM\n", dev ? dev->dev_addr : bcast);
पूर्ण

अटल sमाप_प्रकार remote_mac_show(काष्ठा config_item *item, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%pM\n", to_target(item)->np.remote_mac);
पूर्ण

/*
 * This one is special -- tarमाला_लो created through the configfs पूर्णांकerface
 * are not enabled (and the corresponding netpoll activated) by शेष.
 * The user is expected to set the desired parameters first (which
 * would enable him to dynamically add new netpoll tarमाला_लो क्रम new
 * network पूर्णांकerfaces as and when they come up).
 */
अटल sमाप_प्रकार enabled_store(काष्ठा config_item *item,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा netconsole_target *nt = to_target(item);
	अचिन्हित दीर्घ flags;
	पूर्णांक enabled;
	पूर्णांक err;

	mutex_lock(&dynamic_netconsole_mutex);
	err = kstrtoपूर्णांक(buf, 10, &enabled);
	अगर (err < 0)
		जाओ out_unlock;

	err = -EINVAL;
	अगर (enabled < 0 || enabled > 1)
		जाओ out_unlock;
	अगर ((bool)enabled == nt->enabled) अणु
		pr_info("network logging has already %s\n",
			nt->enabled ? "started" : "stopped");
		जाओ out_unlock;
	पूर्ण

	अगर (enabled) अणु	/* true */
		अगर (nt->extended && !(netconsole_ext.flags & CON_ENABLED)) अणु
			netconsole_ext.flags |= CON_ENABLED;
			रेजिस्टर_console(&netconsole_ext);
		पूर्ण

		/*
		 * Skip netpoll_parse_options() -- all the attributes are
		 * alपढ़ोy configured via configfs. Just prपूर्णांक them out.
		 */
		netpoll_prपूर्णांक_options(&nt->np);

		err = netpoll_setup(&nt->np);
		अगर (err)
			जाओ out_unlock;

		pr_info("network logging started\n");
	पूर्ण अन्यथा अणु	/* false */
		/* We need to disable the netconsole beक्रमe cleaning it up
		 * otherwise we might end up in ग_लिखो_msg() with
		 * nt->np.dev == शून्य and nt->enabled == true
		 */
		spin_lock_irqsave(&target_list_lock, flags);
		nt->enabled = false;
		spin_unlock_irqrestore(&target_list_lock, flags);
		netpoll_cleanup(&nt->np);
	पूर्ण

	nt->enabled = enabled;

	mutex_unlock(&dynamic_netconsole_mutex);
	वापस strnlen(buf, count);
out_unlock:
	mutex_unlock(&dynamic_netconsole_mutex);
	वापस err;
पूर्ण

अटल sमाप_प्रकार extended_store(काष्ठा config_item *item, स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	काष्ठा netconsole_target *nt = to_target(item);
	पूर्णांक extended;
	पूर्णांक err;

	mutex_lock(&dynamic_netconsole_mutex);
	अगर (nt->enabled) अणु
		pr_err("target (%s) is enabled, disable to update parameters\n",
		       config_item_name(&nt->item));
		err = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	err = kstrtoपूर्णांक(buf, 10, &extended);
	अगर (err < 0)
		जाओ out_unlock;
	अगर (extended < 0 || extended > 1) अणु
		err = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	nt->extended = extended;

	mutex_unlock(&dynamic_netconsole_mutex);
	वापस strnlen(buf, count);
out_unlock:
	mutex_unlock(&dynamic_netconsole_mutex);
	वापस err;
पूर्ण

अटल sमाप_प्रकार dev_name_store(काष्ठा config_item *item, स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	काष्ठा netconsole_target *nt = to_target(item);
	माप_प्रकार len;

	mutex_lock(&dynamic_netconsole_mutex);
	अगर (nt->enabled) अणु
		pr_err("target (%s) is enabled, disable to update parameters\n",
		       config_item_name(&nt->item));
		mutex_unlock(&dynamic_netconsole_mutex);
		वापस -EINVAL;
	पूर्ण

	strlcpy(nt->np.dev_name, buf, IFNAMSIZ);

	/* Get rid of possible trailing newline from echo(1) */
	len = strnlen(nt->np.dev_name, IFNAMSIZ);
	अगर (nt->np.dev_name[len - 1] == '\n')
		nt->np.dev_name[len - 1] = '\0';

	mutex_unlock(&dynamic_netconsole_mutex);
	वापस strnlen(buf, count);
पूर्ण

अटल sमाप_प्रकार local_port_store(काष्ठा config_item *item, स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	काष्ठा netconsole_target *nt = to_target(item);
	पूर्णांक rv = -EINVAL;

	mutex_lock(&dynamic_netconsole_mutex);
	अगर (nt->enabled) अणु
		pr_err("target (%s) is enabled, disable to update parameters\n",
		       config_item_name(&nt->item));
		जाओ out_unlock;
	पूर्ण

	rv = kstrtou16(buf, 10, &nt->np.local_port);
	अगर (rv < 0)
		जाओ out_unlock;
	mutex_unlock(&dynamic_netconsole_mutex);
	वापस strnlen(buf, count);
out_unlock:
	mutex_unlock(&dynamic_netconsole_mutex);
	वापस rv;
पूर्ण

अटल sमाप_प्रकार remote_port_store(काष्ठा config_item *item,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा netconsole_target *nt = to_target(item);
	पूर्णांक rv = -EINVAL;

	mutex_lock(&dynamic_netconsole_mutex);
	अगर (nt->enabled) अणु
		pr_err("target (%s) is enabled, disable to update parameters\n",
		       config_item_name(&nt->item));
		जाओ out_unlock;
	पूर्ण

	rv = kstrtou16(buf, 10, &nt->np.remote_port);
	अगर (rv < 0)
		जाओ out_unlock;
	mutex_unlock(&dynamic_netconsole_mutex);
	वापस strnlen(buf, count);
out_unlock:
	mutex_unlock(&dynamic_netconsole_mutex);
	वापस rv;
पूर्ण

अटल sमाप_प्रकार local_ip_store(काष्ठा config_item *item, स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	काष्ठा netconsole_target *nt = to_target(item);

	mutex_lock(&dynamic_netconsole_mutex);
	अगर (nt->enabled) अणु
		pr_err("target (%s) is enabled, disable to update parameters\n",
		       config_item_name(&nt->item));
		जाओ out_unlock;
	पूर्ण

	अगर (strnchr(buf, count, ':')) अणु
		स्थिर अक्षर *end;
		अगर (in6_pton(buf, count, nt->np.local_ip.in6.s6_addr, -1, &end) > 0) अणु
			अगर (*end && *end != '\n') अणु
				pr_err("invalid IPv6 address at: <%c>\n", *end);
				जाओ out_unlock;
			पूर्ण
			nt->np.ipv6 = true;
		पूर्ण अन्यथा
			जाओ out_unlock;
	पूर्ण अन्यथा अणु
		अगर (!nt->np.ipv6) अणु
			nt->np.local_ip.ip = in_aton(buf);
		पूर्ण अन्यथा
			जाओ out_unlock;
	पूर्ण

	mutex_unlock(&dynamic_netconsole_mutex);
	वापस strnlen(buf, count);
out_unlock:
	mutex_unlock(&dynamic_netconsole_mutex);
	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार remote_ip_store(काष्ठा config_item *item, स्थिर अक्षर *buf,
	       माप_प्रकार count)
अणु
	काष्ठा netconsole_target *nt = to_target(item);

	mutex_lock(&dynamic_netconsole_mutex);
	अगर (nt->enabled) अणु
		pr_err("target (%s) is enabled, disable to update parameters\n",
		       config_item_name(&nt->item));
		जाओ out_unlock;
	पूर्ण

	अगर (strnchr(buf, count, ':')) अणु
		स्थिर अक्षर *end;
		अगर (in6_pton(buf, count, nt->np.remote_ip.in6.s6_addr, -1, &end) > 0) अणु
			अगर (*end && *end != '\n') अणु
				pr_err("invalid IPv6 address at: <%c>\n", *end);
				जाओ out_unlock;
			पूर्ण
			nt->np.ipv6 = true;
		पूर्ण अन्यथा
			जाओ out_unlock;
	पूर्ण अन्यथा अणु
		अगर (!nt->np.ipv6) अणु
			nt->np.remote_ip.ip = in_aton(buf);
		पूर्ण अन्यथा
			जाओ out_unlock;
	पूर्ण

	mutex_unlock(&dynamic_netconsole_mutex);
	वापस strnlen(buf, count);
out_unlock:
	mutex_unlock(&dynamic_netconsole_mutex);
	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार remote_mac_store(काष्ठा config_item *item, स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	काष्ठा netconsole_target *nt = to_target(item);
	u8 remote_mac[ETH_ALEN];

	mutex_lock(&dynamic_netconsole_mutex);
	अगर (nt->enabled) अणु
		pr_err("target (%s) is enabled, disable to update parameters\n",
		       config_item_name(&nt->item));
		जाओ out_unlock;
	पूर्ण

	अगर (!mac_pton(buf, remote_mac))
		जाओ out_unlock;
	अगर (buf[3 * ETH_ALEN - 1] && buf[3 * ETH_ALEN - 1] != '\n')
		जाओ out_unlock;
	स_नकल(nt->np.remote_mac, remote_mac, ETH_ALEN);

	mutex_unlock(&dynamic_netconsole_mutex);
	वापस strnlen(buf, count);
out_unlock:
	mutex_unlock(&dynamic_netconsole_mutex);
	वापस -EINVAL;
पूर्ण

CONFIGFS_ATTR(, enabled);
CONFIGFS_ATTR(, extended);
CONFIGFS_ATTR(, dev_name);
CONFIGFS_ATTR(, local_port);
CONFIGFS_ATTR(, remote_port);
CONFIGFS_ATTR(, local_ip);
CONFIGFS_ATTR(, remote_ip);
CONFIGFS_ATTR_RO(, local_mac);
CONFIGFS_ATTR(, remote_mac);

अटल काष्ठा configfs_attribute *netconsole_target_attrs[] = अणु
	&attr_enabled,
	&attr_extended,
	&attr_dev_name,
	&attr_local_port,
	&attr_remote_port,
	&attr_local_ip,
	&attr_remote_ip,
	&attr_local_mac,
	&attr_remote_mac,
	शून्य,
पूर्ण;

/*
 * Item operations and type क्रम netconsole_target.
 */

अटल व्योम netconsole_target_release(काष्ठा config_item *item)
अणु
	kमुक्त(to_target(item));
पूर्ण

अटल काष्ठा configfs_item_operations netconsole_target_item_ops = अणु
	.release		= netconsole_target_release,
पूर्ण;

अटल स्थिर काष्ठा config_item_type netconsole_target_type = अणु
	.ct_attrs		= netconsole_target_attrs,
	.ct_item_ops		= &netconsole_target_item_ops,
	.ct_owner		= THIS_MODULE,
पूर्ण;

/*
 * Group operations and type क्रम netconsole_subsys.
 */

अटल काष्ठा config_item *make_netconsole_target(काष्ठा config_group *group,
						  स्थिर अक्षर *name)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा netconsole_target *nt;

	/*
	 * Allocate and initialize with शेषs.
	 * Target is disabled at creation (!enabled).
	 */
	nt = kzalloc(माप(*nt), GFP_KERNEL);
	अगर (!nt)
		वापस ERR_PTR(-ENOMEM);

	nt->np.name = "netconsole";
	strlcpy(nt->np.dev_name, "eth0", IFNAMSIZ);
	nt->np.local_port = 6665;
	nt->np.remote_port = 6666;
	eth_broadcast_addr(nt->np.remote_mac);

	/* Initialize the config_item member */
	config_item_init_type_name(&nt->item, name, &netconsole_target_type);

	/* Adding, but it is disabled */
	spin_lock_irqsave(&target_list_lock, flags);
	list_add(&nt->list, &target_list);
	spin_unlock_irqrestore(&target_list_lock, flags);

	वापस &nt->item;
पूर्ण

अटल व्योम drop_netconsole_target(काष्ठा config_group *group,
				   काष्ठा config_item *item)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा netconsole_target *nt = to_target(item);

	spin_lock_irqsave(&target_list_lock, flags);
	list_del(&nt->list);
	spin_unlock_irqrestore(&target_list_lock, flags);

	/*
	 * The target may have never been enabled, or was manually disabled
	 * beक्रमe being हटाओd so netpoll may have alपढ़ोy been cleaned up.
	 */
	अगर (nt->enabled)
		netpoll_cleanup(&nt->np);

	config_item_put(&nt->item);
पूर्ण

अटल काष्ठा configfs_group_operations netconsole_subsys_group_ops = अणु
	.make_item	= make_netconsole_target,
	.drop_item	= drop_netconsole_target,
पूर्ण;

अटल स्थिर काष्ठा config_item_type netconsole_subsys_type = अणु
	.ct_group_ops	= &netconsole_subsys_group_ops,
	.ct_owner	= THIS_MODULE,
पूर्ण;

/* The netconsole configfs subप्रणाली */
अटल काष्ठा configfs_subप्रणाली netconsole_subsys = अणु
	.su_group	= अणु
		.cg_item	= अणु
			.ci_namebuf	= "netconsole",
			.ci_type	= &netconsole_subsys_type,
		पूर्ण,
	पूर्ण,
पूर्ण;

#पूर्ण_अगर	/* CONFIG_NETCONSOLE_DYNAMIC */

/* Handle network पूर्णांकerface device notअगरications */
अटल पूर्णांक netconsole_netdev_event(काष्ठा notअगरier_block *this,
				   अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा netconsole_target *nt;
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	bool stopped = false;

	अगर (!(event == NETDEV_CHANGENAME || event == NETDEV_UNREGISTER ||
	      event == NETDEV_RELEASE || event == NETDEV_JOIN))
		जाओ करोne;

	spin_lock_irqsave(&target_list_lock, flags);
restart:
	list_क्रम_each_entry(nt, &target_list, list) अणु
		netconsole_target_get(nt);
		अगर (nt->np.dev == dev) अणु
			चयन (event) अणु
			हाल NETDEV_CHANGENAME:
				strlcpy(nt->np.dev_name, dev->name, IFNAMSIZ);
				अवरोध;
			हाल NETDEV_RELEASE:
			हाल NETDEV_JOIN:
			हाल NETDEV_UNREGISTER:
				/* rtnl_lock alपढ़ोy held
				 * we might sleep in __netpoll_cleanup()
				 */
				spin_unlock_irqrestore(&target_list_lock, flags);

				__netpoll_cleanup(&nt->np);

				spin_lock_irqsave(&target_list_lock, flags);
				dev_put(nt->np.dev);
				nt->np.dev = शून्य;
				nt->enabled = false;
				stopped = true;
				netconsole_target_put(nt);
				जाओ restart;
			पूर्ण
		पूर्ण
		netconsole_target_put(nt);
	पूर्ण
	spin_unlock_irqrestore(&target_list_lock, flags);
	अगर (stopped) अणु
		स्थिर अक्षर *msg = "had an event";
		चयन (event) अणु
		हाल NETDEV_UNREGISTER:
			msg = "unregistered";
			अवरोध;
		हाल NETDEV_RELEASE:
			msg = "released slaves";
			अवरोध;
		हाल NETDEV_JOIN:
			msg = "is joining a master device";
			अवरोध;
		पूर्ण
		pr_info("network logging stopped on interface %s as it %s\n",
			dev->name, msg);
	पूर्ण

करोne:
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block netconsole_netdev_notअगरier = अणु
	.notअगरier_call  = netconsole_netdev_event,
पूर्ण;

/**
 * send_ext_msg_udp - send extended log message to target
 * @nt: target to send message to
 * @msg: extended log message to send
 * @msg_len: length of message
 *
 * Transfer extended log @msg to @nt.  If @msg is दीर्घer than
 * MAX_PRINT_CHUNK, it'll be split and transmitted in multiple chunks with
 * ncfrag header field added to identअगरy them.
 */
अटल व्योम send_ext_msg_udp(काष्ठा netconsole_target *nt, स्थिर अक्षर *msg,
			     पूर्णांक msg_len)
अणु
	अटल अक्षर buf[MAX_PRINT_CHUNK]; /* रक्षित by target_list_lock */
	स्थिर अक्षर *header, *body;
	पूर्णांक offset = 0;
	पूर्णांक header_len, body_len;

	अगर (msg_len <= MAX_PRINT_CHUNK) अणु
		netpoll_send_udp(&nt->np, msg, msg_len);
		वापस;
	पूर्ण

	/* need to insert extra header fields, detect header and body */
	header = msg;
	body = स_प्रथम(msg, ';', msg_len);
	अगर (WARN_ON_ONCE(!body))
		वापस;

	header_len = body - header;
	body_len = msg_len - header_len - 1;
	body++;

	/*
	 * Transfer multiple chunks with the following extra header.
	 * "ncfrag=<byte-offset>/<total-bytes>"
	 */
	स_नकल(buf, header, header_len);

	जबतक (offset < body_len) अणु
		पूर्णांक this_header = header_len;
		पूर्णांक this_chunk;

		this_header += scnम_लिखो(buf + this_header,
					 माप(buf) - this_header,
					 ",ncfrag=%d/%d;", offset, body_len);

		this_chunk = min(body_len - offset,
				 MAX_PRINT_CHUNK - this_header);
		अगर (WARN_ON_ONCE(this_chunk <= 0))
			वापस;

		स_नकल(buf + this_header, body + offset, this_chunk);

		netpoll_send_udp(&nt->np, buf, this_header + this_chunk);

		offset += this_chunk;
	पूर्ण
पूर्ण

अटल व्योम ग_लिखो_ext_msg(काष्ठा console *con, स्थिर अक्षर *msg,
			  अचिन्हित पूर्णांक len)
अणु
	काष्ठा netconsole_target *nt;
	अचिन्हित दीर्घ flags;

	अगर ((oops_only && !oops_in_progress) || list_empty(&target_list))
		वापस;

	spin_lock_irqsave(&target_list_lock, flags);
	list_क्रम_each_entry(nt, &target_list, list)
		अगर (nt->extended && nt->enabled && netअगर_running(nt->np.dev))
			send_ext_msg_udp(nt, msg, len);
	spin_unlock_irqrestore(&target_list_lock, flags);
पूर्ण

अटल व्योम ग_लिखो_msg(काष्ठा console *con, स्थिर अक्षर *msg, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक frag, left;
	अचिन्हित दीर्घ flags;
	काष्ठा netconsole_target *nt;
	स्थिर अक्षर *पंचांगp;

	अगर (oops_only && !oops_in_progress)
		वापस;
	/* Aव्योम taking lock and disabling पूर्णांकerrupts unnecessarily */
	अगर (list_empty(&target_list))
		वापस;

	spin_lock_irqsave(&target_list_lock, flags);
	list_क्रम_each_entry(nt, &target_list, list) अणु
		अगर (!nt->extended && nt->enabled && netअगर_running(nt->np.dev)) अणु
			/*
			 * We nest this inside the क्रम-each-target loop above
			 * so that we're able to get as much logging out to
			 * at least one target अगर we die inside here, instead
			 * of unnecessarily keeping all tarमाला_लो in lock-step.
			 */
			पंचांगp = msg;
			क्रम (left = len; left;) अणु
				frag = min(left, MAX_PRINT_CHUNK);
				netpoll_send_udp(&nt->np, पंचांगp, frag);
				पंचांगp += frag;
				left -= frag;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&target_list_lock, flags);
पूर्ण

अटल काष्ठा console netconsole_ext = अणु
	.name	= "netcon_ext",
	.flags	= CON_EXTENDED,	/* starts disabled, रेजिस्टरed on first use */
	.ग_लिखो	= ग_लिखो_ext_msg,
पूर्ण;

अटल काष्ठा console netconsole = अणु
	.name	= "netcon",
	.flags	= CON_ENABLED,
	.ग_लिखो	= ग_लिखो_msg,
पूर्ण;

अटल पूर्णांक __init init_netconsole(व्योम)
अणु
	पूर्णांक err;
	काष्ठा netconsole_target *nt, *पंचांगp;
	अचिन्हित दीर्घ flags;
	अक्षर *target_config;
	अक्षर *input = config;

	अगर (strnlen(input, MAX_PARAM_LENGTH)) अणु
		जबतक ((target_config = strsep(&input, ";"))) अणु
			nt = alloc_param_target(target_config);
			अगर (IS_ERR(nt)) अणु
				err = PTR_ERR(nt);
				जाओ fail;
			पूर्ण
			/* Dump existing prपूर्णांकks when we रेजिस्टर */
			अगर (nt->extended)
				netconsole_ext.flags |= CON_PRINTBUFFER |
							CON_ENABLED;
			अन्यथा
				netconsole.flags |= CON_PRINTBUFFER;

			spin_lock_irqsave(&target_list_lock, flags);
			list_add(&nt->list, &target_list);
			spin_unlock_irqrestore(&target_list_lock, flags);
		पूर्ण
	पूर्ण

	err = रेजिस्टर_netdevice_notअगरier(&netconsole_netdev_notअगरier);
	अगर (err)
		जाओ fail;

	err = dynamic_netconsole_init();
	अगर (err)
		जाओ unकरोnotअगरier;

	अगर (netconsole_ext.flags & CON_ENABLED)
		रेजिस्टर_console(&netconsole_ext);
	रेजिस्टर_console(&netconsole);
	pr_info("network logging started\n");

	वापस err;

unकरोnotअगरier:
	unरेजिस्टर_netdevice_notअगरier(&netconsole_netdev_notअगरier);

fail:
	pr_err("cleaning up\n");

	/*
	 * Remove all tarमाला_लो and destroy them (only tarमाला_लो created
	 * from the boot/module option exist here). Skipping the list
	 * lock is safe here, and netpoll_cleanup() will sleep.
	 */
	list_क्रम_each_entry_safe(nt, पंचांगp, &target_list, list) अणु
		list_del(&nt->list);
		मुक्त_param_target(nt);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम __निकास cleanup_netconsole(व्योम)
अणु
	काष्ठा netconsole_target *nt, *पंचांगp;

	unरेजिस्टर_console(&netconsole_ext);
	unरेजिस्टर_console(&netconsole);
	dynamic_netconsole_निकास();
	unरेजिस्टर_netdevice_notअगरier(&netconsole_netdev_notअगरier);

	/*
	 * Tarमाला_लो created via configfs pin references on our module
	 * and would first be सूची_हटाओ(2)'ed from userspace. We reach
	 * here only when they are alपढ़ोy destroyed, and only those
	 * created from the boot/module option are left, so हटाओ and
	 * destroy them. Skipping the list lock is safe here, and
	 * netpoll_cleanup() will sleep.
	 */
	list_क्रम_each_entry_safe(nt, पंचांगp, &target_list, list) अणु
		list_del(&nt->list);
		मुक्त_param_target(nt);
	पूर्ण
पूर्ण

/*
 * Use late_initcall to ensure netconsole is
 * initialized after network device driver अगर built-in.
 *
 * late_initcall() and module_init() are identical अगर built as module.
 */
late_initcall(init_netconsole);
module_निकास(cleanup_netconsole);
