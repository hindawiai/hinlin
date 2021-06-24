<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/स्थिति.स>
#समावेश <linux/sysctl.h>
#समावेश <linux/slab.h>
#समावेश <linux/cred.h>
#समावेश <linux/hash.h>
#समावेश <linux/kmemleak.h>
#समावेश <linux/user_namespace.h>

#घोषणा UCOUNTS_HASHTABLE_BITS 10
अटल काष्ठा hlist_head ucounts_hashtable[(1 << UCOUNTS_HASHTABLE_BITS)];
अटल DEFINE_SPINLOCK(ucounts_lock);

#घोषणा ucounts_hashfn(ns, uid)						\
	hash_दीर्घ((अचिन्हित दीर्घ)__kuid_val(uid) + (अचिन्हित दीर्घ)(ns), \
		  UCOUNTS_HASHTABLE_BITS)
#घोषणा ucounts_hashentry(ns, uid)	\
	(ucounts_hashtable + ucounts_hashfn(ns, uid))


#अगर_घोषित CONFIG_SYSCTL
अटल काष्ठा ctl_table_set *
set_lookup(काष्ठा ctl_table_root *root)
अणु
	वापस &current_user_ns()->set;
पूर्ण

अटल पूर्णांक set_is_seen(काष्ठा ctl_table_set *set)
अणु
	वापस &current_user_ns()->set == set;
पूर्ण

अटल पूर्णांक set_permissions(काष्ठा ctl_table_header *head,
				  काष्ठा ctl_table *table)
अणु
	काष्ठा user_namespace *user_ns =
		container_of(head->set, काष्ठा user_namespace, set);
	पूर्णांक mode;

	/* Allow users with CAP_SYS_RESOURCE unrestrained access */
	अगर (ns_capable(user_ns, CAP_SYS_RESOURCE))
		mode = (table->mode & S_IRWXU) >> 6;
	अन्यथा
	/* Allow all others at most पढ़ो-only access */
		mode = table->mode & S_IROTH;
	वापस (mode << 6) | (mode << 3) | mode;
पूर्ण

अटल काष्ठा ctl_table_root set_root = अणु
	.lookup = set_lookup,
	.permissions = set_permissions,
पूर्ण;

#घोषणा UCOUNT_ENTRY(name)				\
	अणु						\
		.procname	= name,			\
		.maxlen		= माप(पूर्णांक),		\
		.mode		= 0644,			\
		.proc_handler	= proc_करोपूर्णांकvec_minmax,	\
		.extra1		= SYSCTL_ZERO,		\
		.extra2		= SYSCTL_पूर्णांक_उच्च,	\
	पूर्ण
अटल काष्ठा ctl_table user_table[] = अणु
	UCOUNT_ENTRY("max_user_namespaces"),
	UCOUNT_ENTRY("max_pid_namespaces"),
	UCOUNT_ENTRY("max_uts_namespaces"),
	UCOUNT_ENTRY("max_ipc_namespaces"),
	UCOUNT_ENTRY("max_net_namespaces"),
	UCOUNT_ENTRY("max_mnt_namespaces"),
	UCOUNT_ENTRY("max_cgroup_namespaces"),
	UCOUNT_ENTRY("max_time_namespaces"),
#अगर_घोषित CONFIG_INOTIFY_USER
	UCOUNT_ENTRY("max_inotify_instances"),
	UCOUNT_ENTRY("max_inotify_watches"),
#पूर्ण_अगर
#अगर_घोषित CONFIG_FANOTIFY
	UCOUNT_ENTRY("max_fanotify_groups"),
	UCOUNT_ENTRY("max_fanotify_marks"),
#पूर्ण_अगर
	अणु पूर्ण
पूर्ण;
#पूर्ण_अगर /* CONFIG_SYSCTL */

bool setup_userns_sysctls(काष्ठा user_namespace *ns)
अणु
#अगर_घोषित CONFIG_SYSCTL
	काष्ठा ctl_table *tbl;

	BUILD_BUG_ON(ARRAY_SIZE(user_table) != UCOUNT_COUNTS + 1);
	setup_sysctl_set(&ns->set, &set_root, set_is_seen);
	tbl = kmemdup(user_table, माप(user_table), GFP_KERNEL);
	अगर (tbl) अणु
		पूर्णांक i;
		क्रम (i = 0; i < UCOUNT_COUNTS; i++) अणु
			tbl[i].data = &ns->ucount_max[i];
		पूर्ण
		ns->sysctls = __रेजिस्टर_sysctl_table(&ns->set, "user", tbl);
	पूर्ण
	अगर (!ns->sysctls) अणु
		kमुक्त(tbl);
		retire_sysctl_set(&ns->set);
		वापस false;
	पूर्ण
#पूर्ण_अगर
	वापस true;
पूर्ण

व्योम retire_userns_sysctls(काष्ठा user_namespace *ns)
अणु
#अगर_घोषित CONFIG_SYSCTL
	काष्ठा ctl_table *tbl;

	tbl = ns->sysctls->ctl_table_arg;
	unरेजिस्टर_sysctl_table(ns->sysctls);
	retire_sysctl_set(&ns->set);
	kमुक्त(tbl);
#पूर्ण_अगर
पूर्ण

अटल काष्ठा ucounts *find_ucounts(काष्ठा user_namespace *ns, kuid_t uid, काष्ठा hlist_head *hashent)
अणु
	काष्ठा ucounts *ucounts;

	hlist_क्रम_each_entry(ucounts, hashent, node) अणु
		अगर (uid_eq(ucounts->uid, uid) && (ucounts->ns == ns))
			वापस ucounts;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा ucounts *get_ucounts(काष्ठा user_namespace *ns, kuid_t uid)
अणु
	काष्ठा hlist_head *hashent = ucounts_hashentry(ns, uid);
	काष्ठा ucounts *ucounts, *new;

	spin_lock_irq(&ucounts_lock);
	ucounts = find_ucounts(ns, uid, hashent);
	अगर (!ucounts) अणु
		spin_unlock_irq(&ucounts_lock);

		new = kzalloc(माप(*new), GFP_KERNEL);
		अगर (!new)
			वापस शून्य;

		new->ns = ns;
		new->uid = uid;
		new->count = 0;

		spin_lock_irq(&ucounts_lock);
		ucounts = find_ucounts(ns, uid, hashent);
		अगर (ucounts) अणु
			kमुक्त(new);
		पूर्ण अन्यथा अणु
			hlist_add_head(&new->node, hashent);
			ucounts = new;
		पूर्ण
	पूर्ण
	अगर (ucounts->count == पूर्णांक_उच्च)
		ucounts = शून्य;
	अन्यथा
		ucounts->count += 1;
	spin_unlock_irq(&ucounts_lock);
	वापस ucounts;
पूर्ण

अटल व्योम put_ucounts(काष्ठा ucounts *ucounts)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ucounts_lock, flags);
	ucounts->count -= 1;
	अगर (!ucounts->count)
		hlist_del_init(&ucounts->node);
	अन्यथा
		ucounts = शून्य;
	spin_unlock_irqrestore(&ucounts_lock, flags);

	kमुक्त(ucounts);
पूर्ण

अटल अंतरभूत bool atomic_inc_below(atomic_t *v, पूर्णांक u)
अणु
	पूर्णांक c, old;
	c = atomic_पढ़ो(v);
	क्रम (;;) अणु
		अगर (unlikely(c >= u))
			वापस false;
		old = atomic_cmpxchg(v, c, c+1);
		अगर (likely(old == c))
			वापस true;
		c = old;
	पूर्ण
पूर्ण

काष्ठा ucounts *inc_ucount(काष्ठा user_namespace *ns, kuid_t uid,
			   क्रमागत ucount_type type)
अणु
	काष्ठा ucounts *ucounts, *iter, *bad;
	काष्ठा user_namespace *tns;
	ucounts = get_ucounts(ns, uid);
	क्रम (iter = ucounts; iter; iter = tns->ucounts) अणु
		पूर्णांक max;
		tns = iter->ns;
		max = READ_ONCE(tns->ucount_max[type]);
		अगर (!atomic_inc_below(&iter->ucount[type], max))
			जाओ fail;
	पूर्ण
	वापस ucounts;
fail:
	bad = iter;
	क्रम (iter = ucounts; iter != bad; iter = iter->ns->ucounts)
		atomic_dec(&iter->ucount[type]);

	put_ucounts(ucounts);
	वापस शून्य;
पूर्ण

व्योम dec_ucount(काष्ठा ucounts *ucounts, क्रमागत ucount_type type)
अणु
	काष्ठा ucounts *iter;
	क्रम (iter = ucounts; iter; iter = iter->ns->ucounts) अणु
		पूर्णांक dec = atomic_dec_अगर_positive(&iter->ucount[type]);
		WARN_ON_ONCE(dec < 0);
	पूर्ण
	put_ucounts(ucounts);
पूर्ण

अटल __init पूर्णांक user_namespace_sysctl_init(व्योम)
अणु
#अगर_घोषित CONFIG_SYSCTL
	अटल काष्ठा ctl_table_header *user_header;
	अटल काष्ठा ctl_table empty[1];
	/*
	 * It is necessary to रेजिस्टर the user directory in the
	 * शेष set so that registrations in the child sets work
	 * properly.
	 */
	user_header = रेजिस्टर_sysctl("user", empty);
	kmemleak_ignore(user_header);
	BUG_ON(!user_header);
	BUG_ON(!setup_userns_sysctls(&init_user_ns));
#पूर्ण_अगर
	वापस 0;
पूर्ण
subsys_initcall(user_namespace_sysctl_init);
