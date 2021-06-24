<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* -*- linux-c -*-
 * sysctl_net.c: sysctl पूर्णांकerface to net subप्रणाली.
 *
 * Begun April 1, 1996, Mike Shaver.
 * Added /proc/sys/net directories क्रम each protocol family. [MS]
 *
 * Revision 1.2  1996/05/08  20:24:40  shaver
 * Added bits क्रम NET_BRIDGE and the NET_IPV4_ARP stuff and
 * NET_IPV4_IP_FORWARD.
 *
 *
 */

#समावेश <linux/mm.h>
#समावेश <linux/export.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/nsproxy.h>

#समावेश <net/sock.h>

#अगर_घोषित CONFIG_INET
#समावेश <net/ip.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_NET
#समावेश <linux/अगर_ether.h>
#पूर्ण_अगर

अटल काष्ठा ctl_table_set *
net_ctl_header_lookup(काष्ठा ctl_table_root *root)
अणु
	वापस &current->nsproxy->net_ns->sysctls;
पूर्ण

अटल पूर्णांक is_seen(काष्ठा ctl_table_set *set)
अणु
	वापस &current->nsproxy->net_ns->sysctls == set;
पूर्ण

/* Return standard mode bits क्रम table entry. */
अटल पूर्णांक net_ctl_permissions(काष्ठा ctl_table_header *head,
			       काष्ठा ctl_table *table)
अणु
	काष्ठा net *net = container_of(head->set, काष्ठा net, sysctls);

	/* Allow network administrator to have same access as root. */
	अगर (ns_capable_noaudit(net->user_ns, CAP_NET_ADMIN)) अणु
		पूर्णांक mode = (table->mode >> 6) & 7;
		वापस (mode << 6) | (mode << 3) | mode;
	पूर्ण

	वापस table->mode;
पूर्ण

अटल व्योम net_ctl_set_ownership(काष्ठा ctl_table_header *head,
				  काष्ठा ctl_table *table,
				  kuid_t *uid, kgid_t *gid)
अणु
	काष्ठा net *net = container_of(head->set, काष्ठा net, sysctls);
	kuid_t ns_root_uid;
	kgid_t ns_root_gid;

	ns_root_uid = make_kuid(net->user_ns, 0);
	अगर (uid_valid(ns_root_uid))
		*uid = ns_root_uid;

	ns_root_gid = make_kgid(net->user_ns, 0);
	अगर (gid_valid(ns_root_gid))
		*gid = ns_root_gid;
पूर्ण

अटल काष्ठा ctl_table_root net_sysctl_root = अणु
	.lookup = net_ctl_header_lookup,
	.permissions = net_ctl_permissions,
	.set_ownership = net_ctl_set_ownership,
पूर्ण;

अटल पूर्णांक __net_init sysctl_net_init(काष्ठा net *net)
अणु
	setup_sysctl_set(&net->sysctls, &net_sysctl_root, is_seen);
	वापस 0;
पूर्ण

अटल व्योम __net_निकास sysctl_net_निकास(काष्ठा net *net)
अणु
	retire_sysctl_set(&net->sysctls);
पूर्ण

अटल काष्ठा pernet_operations sysctl_pernet_ops = अणु
	.init = sysctl_net_init,
	.निकास = sysctl_net_निकास,
पूर्ण;

अटल काष्ठा ctl_table_header *net_header;
__init पूर्णांक net_sysctl_init(व्योम)
अणु
	अटल काष्ठा ctl_table empty[1];
	पूर्णांक ret = -ENOMEM;
	/* Aव्योम limitations in the sysctl implementation by
	 * रेजिस्टरing "/proc/sys/net" as an empty directory not in a
	 * network namespace.
	 */
	net_header = रेजिस्टर_sysctl("net", empty);
	अगर (!net_header)
		जाओ out;
	ret = रेजिस्टर_pernet_subsys(&sysctl_pernet_ops);
	अगर (ret)
		जाओ out1;
out:
	वापस ret;
out1:
	unरेजिस्टर_sysctl_table(net_header);
	net_header = शून्य;
	जाओ out;
पूर्ण

/* Verअगरy that sysctls क्रम non-init netns are safe by either:
 * 1) being पढ़ो-only, or
 * 2) having a data poपूर्णांकer which poपूर्णांकs outside of the global kernel/module
 *    data segment, and rather पूर्णांकo the heap where a per-net object was
 *    allocated.
 */
अटल व्योम ensure_safe_net_sysctl(काष्ठा net *net, स्थिर अक्षर *path,
				   काष्ठा ctl_table *table)
अणु
	काष्ठा ctl_table *ent;

	pr_debug("Registering net sysctl (net %p): %s\n", net, path);
	क्रम (ent = table; ent->procname; ent++) अणु
		अचिन्हित दीर्घ addr;
		स्थिर अक्षर *where;

		pr_debug("  procname=%s mode=%o proc_handler=%ps data=%p\n",
			 ent->procname, ent->mode, ent->proc_handler, ent->data);

		/* If it's not writable inside the netns, then it can't hurt. */
		अगर ((ent->mode & 0222) == 0) अणु
			pr_debug("    Not writable by anyone\n");
			जारी;
		पूर्ण

		/* Where करोes data poपूर्णांक? */
		addr = (अचिन्हित दीर्घ)ent->data;
		अगर (is_module_address(addr))
			where = "module";
		अन्यथा अगर (core_kernel_data(addr))
			where = "kernel";
		अन्यथा
			जारी;

		/* If it is writable and poपूर्णांकs to kernel/module global
		 * data, then it's probably a netns leak.
		 */
		WARN(1, "sysctl %s/%s: data points to %s global data: %ps\n",
		     path, ent->procname, where, ent->data);

		/* Make it "safe" by dropping writable perms */
		ent->mode &= ~0222;
	पूर्ण
पूर्ण

काष्ठा ctl_table_header *रेजिस्टर_net_sysctl(काष्ठा net *net,
	स्थिर अक्षर *path, काष्ठा ctl_table *table)
अणु
	अगर (!net_eq(net, &init_net))
		ensure_safe_net_sysctl(net, path, table);

	वापस __रेजिस्टर_sysctl_table(&net->sysctls, path, table);
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_net_sysctl);

व्योम unरेजिस्टर_net_sysctl_table(काष्ठा ctl_table_header *header)
अणु
	unरेजिस्टर_sysctl_table(header);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_net_sysctl_table);
