<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * x_tables core - Backend क्रम अणुip,ip6,arpपूर्ण_tables
 *
 * Copyright (C) 2006-2006 Harald Welte <laक्रमge@netfilter.org>
 * Copyright (C) 2006-2012 Patrick McHardy <kaber@trash.net>
 *
 * Based on existing ip_tables code which is
 *   Copyright (C) 1999 Paul `Rusty' Russell & Michael J. Neuling
 *   Copyright (C) 2000-2005 Netfilter Core Team <coreteam@netfilter.org>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/socket.h>
#समावेश <linux/net.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/माला.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mutex.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/audit.h>
#समावेश <linux/user_namespace.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>

#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_arp.h>
#समावेश <linux/netfilter_ipv4/ip_tables.h>
#समावेश <linux/netfilter_ipv6/ip6_tables.h>
#समावेश <linux/netfilter_arp/arp_tables.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Harald Welte <laforge@netfilter.org>");
MODULE_DESCRIPTION("{ip,ip6,arp,eb}_tables backend module");

#घोषणा XT_PCPU_BLOCK_SIZE 4096
#घोषणा XT_MAX_TABLE_SIZE	(512 * 1024 * 1024)

काष्ठा xt_pernet अणु
	काष्ठा list_head tables[NFPROTO_NUMPROTO];
पूर्ण;

काष्ठा compat_delta अणु
	अचिन्हित पूर्णांक offset; /* offset in kernel */
	पूर्णांक delta; /* delta in 32bit user land */
पूर्ण;

काष्ठा xt_af अणु
	काष्ठा mutex mutex;
	काष्ठा list_head match;
	काष्ठा list_head target;
#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
	काष्ठा mutex compat_mutex;
	काष्ठा compat_delta *compat_tab;
	अचिन्हित पूर्णांक number; /* number of slots in compat_tab[] */
	अचिन्हित पूर्णांक cur; /* number of used slots in compat_tab[] */
#पूर्ण_अगर
पूर्ण;

अटल अचिन्हित पूर्णांक xt_pernet_id __पढ़ो_mostly;
अटल काष्ठा xt_af *xt __पढ़ो_mostly;

अटल स्थिर अक्षर *स्थिर xt_prefix[NFPROTO_NUMPROTO] = अणु
	[NFPROTO_UNSPEC] = "x",
	[NFPROTO_IPV4]   = "ip",
	[NFPROTO_ARP]    = "arp",
	[NFPROTO_BRIDGE] = "eb",
	[NFPROTO_IPV6]   = "ip6",
पूर्ण;

/* Registration hooks क्रम tarमाला_लो. */
पूर्णांक xt_रेजिस्टर_target(काष्ठा xt_target *target)
अणु
	u_पूर्णांक8_t af = target->family;

	mutex_lock(&xt[af].mutex);
	list_add(&target->list, &xt[af].target);
	mutex_unlock(&xt[af].mutex);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(xt_रेजिस्टर_target);

व्योम
xt_unरेजिस्टर_target(काष्ठा xt_target *target)
अणु
	u_पूर्णांक8_t af = target->family;

	mutex_lock(&xt[af].mutex);
	list_del(&target->list);
	mutex_unlock(&xt[af].mutex);
पूर्ण
EXPORT_SYMBOL(xt_unरेजिस्टर_target);

पूर्णांक
xt_रेजिस्टर_tarमाला_लो(काष्ठा xt_target *target, अचिन्हित पूर्णांक n)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err = 0;

	क्रम (i = 0; i < n; i++) अणु
		err = xt_रेजिस्टर_target(&target[i]);
		अगर (err)
			जाओ err;
	पूर्ण
	वापस err;

err:
	अगर (i > 0)
		xt_unरेजिस्टर_tarमाला_लो(target, i);
	वापस err;
पूर्ण
EXPORT_SYMBOL(xt_रेजिस्टर_tarमाला_लो);

व्योम
xt_unरेजिस्टर_tarमाला_लो(काष्ठा xt_target *target, अचिन्हित पूर्णांक n)
अणु
	जबतक (n-- > 0)
		xt_unरेजिस्टर_target(&target[n]);
पूर्ण
EXPORT_SYMBOL(xt_unरेजिस्टर_tarमाला_लो);

पूर्णांक xt_रेजिस्टर_match(काष्ठा xt_match *match)
अणु
	u_पूर्णांक8_t af = match->family;

	mutex_lock(&xt[af].mutex);
	list_add(&match->list, &xt[af].match);
	mutex_unlock(&xt[af].mutex);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(xt_रेजिस्टर_match);

व्योम
xt_unरेजिस्टर_match(काष्ठा xt_match *match)
अणु
	u_पूर्णांक8_t af = match->family;

	mutex_lock(&xt[af].mutex);
	list_del(&match->list);
	mutex_unlock(&xt[af].mutex);
पूर्ण
EXPORT_SYMBOL(xt_unरेजिस्टर_match);

पूर्णांक
xt_रेजिस्टर_matches(काष्ठा xt_match *match, अचिन्हित पूर्णांक n)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err = 0;

	क्रम (i = 0; i < n; i++) अणु
		err = xt_रेजिस्टर_match(&match[i]);
		अगर (err)
			जाओ err;
	पूर्ण
	वापस err;

err:
	अगर (i > 0)
		xt_unरेजिस्टर_matches(match, i);
	वापस err;
पूर्ण
EXPORT_SYMBOL(xt_रेजिस्टर_matches);

व्योम
xt_unरेजिस्टर_matches(काष्ठा xt_match *match, अचिन्हित पूर्णांक n)
अणु
	जबतक (n-- > 0)
		xt_unरेजिस्टर_match(&match[n]);
पूर्ण
EXPORT_SYMBOL(xt_unरेजिस्टर_matches);


/*
 * These are weird, but module loading must not be करोne with mutex
 * held (since they will रेजिस्टर), and we have to have a single
 * function to use.
 */

/* Find match, grअसल ref.  Returns ERR_PTR() on error. */
काष्ठा xt_match *xt_find_match(u8 af, स्थिर अक्षर *name, u8 revision)
अणु
	काष्ठा xt_match *m;
	पूर्णांक err = -ENOENT;

	अगर (strnlen(name, XT_EXTENSION_MAXNAMELEN) == XT_EXTENSION_MAXNAMELEN)
		वापस ERR_PTR(-EINVAL);

	mutex_lock(&xt[af].mutex);
	list_क्रम_each_entry(m, &xt[af].match, list) अणु
		अगर (म_भेद(m->name, name) == 0) अणु
			अगर (m->revision == revision) अणु
				अगर (try_module_get(m->me)) अणु
					mutex_unlock(&xt[af].mutex);
					वापस m;
				पूर्ण
			पूर्ण अन्यथा
				err = -EPROTOTYPE; /* Found something. */
		पूर्ण
	पूर्ण
	mutex_unlock(&xt[af].mutex);

	अगर (af != NFPROTO_UNSPEC)
		/* Try searching again in the family-independent list */
		वापस xt_find_match(NFPROTO_UNSPEC, name, revision);

	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL(xt_find_match);

काष्ठा xt_match *
xt_request_find_match(uपूर्णांक8_t nfproto, स्थिर अक्षर *name, uपूर्णांक8_t revision)
अणु
	काष्ठा xt_match *match;

	अगर (strnlen(name, XT_EXTENSION_MAXNAMELEN) == XT_EXTENSION_MAXNAMELEN)
		वापस ERR_PTR(-EINVAL);

	match = xt_find_match(nfproto, name, revision);
	अगर (IS_ERR(match)) अणु
		request_module("%st_%s", xt_prefix[nfproto], name);
		match = xt_find_match(nfproto, name, revision);
	पूर्ण

	वापस match;
पूर्ण
EXPORT_SYMBOL_GPL(xt_request_find_match);

/* Find target, grअसल ref.  Returns ERR_PTR() on error. */
अटल काष्ठा xt_target *xt_find_target(u8 af, स्थिर अक्षर *name, u8 revision)
अणु
	काष्ठा xt_target *t;
	पूर्णांक err = -ENOENT;

	अगर (strnlen(name, XT_EXTENSION_MAXNAMELEN) == XT_EXTENSION_MAXNAMELEN)
		वापस ERR_PTR(-EINVAL);

	mutex_lock(&xt[af].mutex);
	list_क्रम_each_entry(t, &xt[af].target, list) अणु
		अगर (म_भेद(t->name, name) == 0) अणु
			अगर (t->revision == revision) अणु
				अगर (try_module_get(t->me)) अणु
					mutex_unlock(&xt[af].mutex);
					वापस t;
				पूर्ण
			पूर्ण अन्यथा
				err = -EPROTOTYPE; /* Found something. */
		पूर्ण
	पूर्ण
	mutex_unlock(&xt[af].mutex);

	अगर (af != NFPROTO_UNSPEC)
		/* Try searching again in the family-independent list */
		वापस xt_find_target(NFPROTO_UNSPEC, name, revision);

	वापस ERR_PTR(err);
पूर्ण

काष्ठा xt_target *xt_request_find_target(u8 af, स्थिर अक्षर *name, u8 revision)
अणु
	काष्ठा xt_target *target;

	अगर (strnlen(name, XT_EXTENSION_MAXNAMELEN) == XT_EXTENSION_MAXNAMELEN)
		वापस ERR_PTR(-EINVAL);

	target = xt_find_target(af, name, revision);
	अगर (IS_ERR(target)) अणु
		request_module("%st_%s", xt_prefix[af], name);
		target = xt_find_target(af, name, revision);
	पूर्ण

	वापस target;
पूर्ण
EXPORT_SYMBOL_GPL(xt_request_find_target);


अटल पूर्णांक xt_obj_to_user(u16 __user *psize, u16 size,
			  व्योम __user *pname, स्थिर अक्षर *name,
			  u8 __user *prev, u8 rev)
अणु
	अगर (put_user(size, psize))
		वापस -EFAULT;
	अगर (copy_to_user(pname, name, म_माप(name) + 1))
		वापस -EFAULT;
	अगर (put_user(rev, prev))
		वापस -EFAULT;

	वापस 0;
पूर्ण

#घोषणा XT_OBJ_TO_USER(U, K, TYPE, C_SIZE)				\
	xt_obj_to_user(&U->u.TYPE##_size, C_SIZE ? : K->u.TYPE##_size,	\
		       U->u.user.name, K->u.kernel.TYPE->name,		\
		       &U->u.user.revision, K->u.kernel.TYPE->revision)

पूर्णांक xt_data_to_user(व्योम __user *dst, स्थिर व्योम *src,
		    पूर्णांक usersize, पूर्णांक size, पूर्णांक aligned_size)
अणु
	usersize = usersize ? : size;
	अगर (copy_to_user(dst, src, usersize))
		वापस -EFAULT;
	अगर (usersize != aligned_size &&
	    clear_user(dst + usersize, aligned_size - usersize))
		वापस -EFAULT;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xt_data_to_user);

#घोषणा XT_DATA_TO_USER(U, K, TYPE)					\
	xt_data_to_user(U->data, K->data,				\
			K->u.kernel.TYPE->usersize,			\
			K->u.kernel.TYPE->TYPE##size,			\
			XT_ALIGN(K->u.kernel.TYPE->TYPE##size))

पूर्णांक xt_match_to_user(स्थिर काष्ठा xt_entry_match *m,
		     काष्ठा xt_entry_match __user *u)
अणु
	वापस XT_OBJ_TO_USER(u, m, match, 0) ||
	       XT_DATA_TO_USER(u, m, match);
पूर्ण
EXPORT_SYMBOL_GPL(xt_match_to_user);

पूर्णांक xt_target_to_user(स्थिर काष्ठा xt_entry_target *t,
		      काष्ठा xt_entry_target __user *u)
अणु
	वापस XT_OBJ_TO_USER(u, t, target, 0) ||
	       XT_DATA_TO_USER(u, t, target);
पूर्ण
EXPORT_SYMBOL_GPL(xt_target_to_user);

अटल पूर्णांक match_revfn(u8 af, स्थिर अक्षर *name, u8 revision, पूर्णांक *bestp)
अणु
	स्थिर काष्ठा xt_match *m;
	पूर्णांक have_rev = 0;

	mutex_lock(&xt[af].mutex);
	list_क्रम_each_entry(m, &xt[af].match, list) अणु
		अगर (म_भेद(m->name, name) == 0) अणु
			अगर (m->revision > *bestp)
				*bestp = m->revision;
			अगर (m->revision == revision)
				have_rev = 1;
		पूर्ण
	पूर्ण
	mutex_unlock(&xt[af].mutex);

	अगर (af != NFPROTO_UNSPEC && !have_rev)
		वापस match_revfn(NFPROTO_UNSPEC, name, revision, bestp);

	वापस have_rev;
पूर्ण

अटल पूर्णांक target_revfn(u8 af, स्थिर अक्षर *name, u8 revision, पूर्णांक *bestp)
अणु
	स्थिर काष्ठा xt_target *t;
	पूर्णांक have_rev = 0;

	mutex_lock(&xt[af].mutex);
	list_क्रम_each_entry(t, &xt[af].target, list) अणु
		अगर (म_भेद(t->name, name) == 0) अणु
			अगर (t->revision > *bestp)
				*bestp = t->revision;
			अगर (t->revision == revision)
				have_rev = 1;
		पूर्ण
	पूर्ण
	mutex_unlock(&xt[af].mutex);

	अगर (af != NFPROTO_UNSPEC && !have_rev)
		वापस target_revfn(NFPROTO_UNSPEC, name, revision, bestp);

	वापस have_rev;
पूर्ण

/* Returns true or false (अगर no such extension at all) */
पूर्णांक xt_find_revision(u8 af, स्थिर अक्षर *name, u8 revision, पूर्णांक target,
		     पूर्णांक *err)
अणु
	पूर्णांक have_rev, best = -1;

	अगर (target == 1)
		have_rev = target_revfn(af, name, revision, &best);
	अन्यथा
		have_rev = match_revfn(af, name, revision, &best);

	/* Nothing at all?  Return 0 to try loading module. */
	अगर (best == -1) अणु
		*err = -ENOENT;
		वापस 0;
	पूर्ण

	*err = best;
	अगर (!have_rev)
		*err = -EPROTONOSUPPORT;
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(xt_find_revision);

अटल अक्षर *
textअगरy_hooks(अक्षर *buf, माप_प्रकार size, अचिन्हित पूर्णांक mask, uपूर्णांक8_t nfproto)
अणु
	अटल स्थिर अक्षर *स्थिर inetbr_names[] = अणु
		"PREROUTING", "INPUT", "FORWARD",
		"OUTPUT", "POSTROUTING", "BROUTING",
	पूर्ण;
	अटल स्थिर अक्षर *स्थिर arp_names[] = अणु
		"INPUT", "FORWARD", "OUTPUT",
	पूर्ण;
	स्थिर अक्षर *स्थिर *names;
	अचिन्हित पूर्णांक i, max;
	अक्षर *p = buf;
	bool np = false;
	पूर्णांक res;

	names = (nfproto == NFPROTO_ARP) ? arp_names : inetbr_names;
	max   = (nfproto == NFPROTO_ARP) ? ARRAY_SIZE(arp_names) :
	                                   ARRAY_SIZE(inetbr_names);
	*p = '\0';
	क्रम (i = 0; i < max; ++i) अणु
		अगर (!(mask & (1 << i)))
			जारी;
		res = snम_लिखो(p, size, "%s%s", np ? "/" : "", names[i]);
		अगर (res > 0) अणु
			size -= res;
			p += res;
		पूर्ण
		np = true;
	पूर्ण

	वापस buf;
पूर्ण

/**
 * xt_check_proc_name - check that name is suitable क्रम /proc file creation
 *
 * @name: file name candidate
 * @size: length of buffer
 *
 * some x_tables modules wish to create a file in /proc.
 * This function makes sure that the name is suitable क्रम this
 * purpose, it checks that name is NUL terminated and isn't a 'special'
 * name, like "..".
 *
 * वापसs negative number on error or 0 अगर name is useable.
 */
पूर्णांक xt_check_proc_name(स्थिर अक्षर *name, अचिन्हित पूर्णांक size)
अणु
	अगर (name[0] == '\0')
		वापस -EINVAL;

	अगर (strnlen(name, size) == size)
		वापस -ENAMETOOLONG;

	अगर (म_भेद(name, ".") == 0 ||
	    म_भेद(name, "..") == 0 ||
	    म_अक्षर(name, '/'))
		वापस -EINVAL;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(xt_check_proc_name);

पूर्णांक xt_check_match(काष्ठा xt_mtchk_param *par,
		   अचिन्हित पूर्णांक size, u16 proto, bool inv_proto)
अणु
	पूर्णांक ret;

	अगर (XT_ALIGN(par->match->matchsize) != size &&
	    par->match->matchsize != -1) अणु
		/*
		 * ebt_among is exempt from centralized matchsize checking
		 * because it uses a dynamic-size data set.
		 */
		pr_err_ratelimited("%s_tables: %s.%u match: invalid size %u (kernel) != (user) %u\n",
				   xt_prefix[par->family], par->match->name,
				   par->match->revision,
				   XT_ALIGN(par->match->matchsize), size);
		वापस -EINVAL;
	पूर्ण
	अगर (par->match->table != शून्य &&
	    म_भेद(par->match->table, par->table) != 0) अणु
		pr_info_ratelimited("%s_tables: %s match: only valid in %s table, not %s\n",
				    xt_prefix[par->family], par->match->name,
				    par->match->table, par->table);
		वापस -EINVAL;
	पूर्ण
	अगर (par->match->hooks && (par->hook_mask & ~par->match->hooks) != 0) अणु
		अक्षर used[64], allow[64];

		pr_info_ratelimited("%s_tables: %s match: used from hooks %s, but only valid from %s\n",
				    xt_prefix[par->family], par->match->name,
				    textअगरy_hooks(used, माप(used),
						  par->hook_mask, par->family),
				    textअगरy_hooks(allow, माप(allow),
						  par->match->hooks,
						  par->family));
		वापस -EINVAL;
	पूर्ण
	अगर (par->match->proto && (par->match->proto != proto || inv_proto)) अणु
		pr_info_ratelimited("%s_tables: %s match: only valid for protocol %u\n",
				    xt_prefix[par->family], par->match->name,
				    par->match->proto);
		वापस -EINVAL;
	पूर्ण
	अगर (par->match->checkentry != शून्य) अणु
		ret = par->match->checkentry(par);
		अगर (ret < 0)
			वापस ret;
		अन्यथा अगर (ret > 0)
			/* Flag up potential errors. */
			वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xt_check_match);

/** xt_check_entry_match - check that matches end beक्रमe start of target
 *
 * @match: beginning of xt_entry_match
 * @target: beginning of this rules target (alleged end of matches)
 * @alignment: alignment requirement of match काष्ठाures
 *
 * Validates that all matches add up to the beginning of the target,
 * and that each match covers at least the base काष्ठाure size.
 *
 * Return: 0 on success, negative त्रुटि_सं on failure.
 */
अटल पूर्णांक xt_check_entry_match(स्थिर अक्षर *match, स्थिर अक्षर *target,
				स्थिर माप_प्रकार alignment)
अणु
	स्थिर काष्ठा xt_entry_match *pos;
	पूर्णांक length = target - match;

	अगर (length == 0) /* no matches */
		वापस 0;

	pos = (काष्ठा xt_entry_match *)match;
	करो अणु
		अगर ((अचिन्हित दीर्घ)pos % alignment)
			वापस -EINVAL;

		अगर (length < (पूर्णांक)माप(काष्ठा xt_entry_match))
			वापस -EINVAL;

		अगर (pos->u.match_size < माप(काष्ठा xt_entry_match))
			वापस -EINVAL;

		अगर (pos->u.match_size > length)
			वापस -EINVAL;

		length -= pos->u.match_size;
		pos = ((व्योम *)((अक्षर *)(pos) + (pos)->u.match_size));
	पूर्ण जबतक (length > 0);

	वापस 0;
पूर्ण

/** xt_check_table_hooks - check hook entry poपूर्णांकs are sane
 *
 * @info xt_table_info to check
 * @valid_hooks - hook entry poपूर्णांकs that we can enter from
 *
 * Validates that the hook entry and underflows poपूर्णांकs are set up.
 *
 * Return: 0 on success, negative त्रुटि_सं on failure.
 */
पूर्णांक xt_check_table_hooks(स्थिर काष्ठा xt_table_info *info, अचिन्हित पूर्णांक valid_hooks)
अणु
	स्थिर अक्षर *err = "unsorted underflow";
	अचिन्हित पूर्णांक i, max_uflow, max_entry;
	bool check_hooks = false;

	BUILD_BUG_ON(ARRAY_SIZE(info->hook_entry) != ARRAY_SIZE(info->underflow));

	max_entry = 0;
	max_uflow = 0;

	क्रम (i = 0; i < ARRAY_SIZE(info->hook_entry); i++) अणु
		अगर (!(valid_hooks & (1 << i)))
			जारी;

		अगर (info->hook_entry[i] == 0xFFFFFFFF)
			वापस -EINVAL;
		अगर (info->underflow[i] == 0xFFFFFFFF)
			वापस -EINVAL;

		अगर (check_hooks) अणु
			अगर (max_uflow > info->underflow[i])
				जाओ error;

			अगर (max_uflow == info->underflow[i]) अणु
				err = "duplicate underflow";
				जाओ error;
			पूर्ण
			अगर (max_entry > info->hook_entry[i]) अणु
				err = "unsorted entry";
				जाओ error;
			पूर्ण
			अगर (max_entry == info->hook_entry[i]) अणु
				err = "duplicate entry";
				जाओ error;
			पूर्ण
		पूर्ण
		max_entry = info->hook_entry[i];
		max_uflow = info->underflow[i];
		check_hooks = true;
	पूर्ण

	वापस 0;
error:
	pr_err_ratelimited("%s at hook %d\n", err, i);
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(xt_check_table_hooks);

अटल bool verdict_ok(पूर्णांक verdict)
अणु
	अगर (verdict > 0)
		वापस true;

	अगर (verdict < 0) अणु
		पूर्णांक v = -verdict - 1;

		अगर (verdict == XT_RETURN)
			वापस true;

		चयन (v) अणु
		हाल NF_ACCEPT: वापस true;
		हाल NF_DROP: वापस true;
		हाल NF_QUEUE: वापस true;
		शेष:
			अवरोध;
		पूर्ण

		वापस false;
	पूर्ण

	वापस false;
पूर्ण

अटल bool error_tg_ok(अचिन्हित पूर्णांक usersize, अचिन्हित पूर्णांक kernsize,
			स्थिर अक्षर *msg, अचिन्हित पूर्णांक msglen)
अणु
	वापस usersize == kernsize && strnlen(msg, msglen) < msglen;
पूर्ण

#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
पूर्णांक xt_compat_add_offset(u_पूर्णांक8_t af, अचिन्हित पूर्णांक offset, पूर्णांक delta)
अणु
	काष्ठा xt_af *xp = &xt[af];

	WARN_ON(!mutex_is_locked(&xt[af].compat_mutex));

	अगर (WARN_ON(!xp->compat_tab))
		वापस -ENOMEM;

	अगर (xp->cur >= xp->number)
		वापस -EINVAL;

	अगर (xp->cur)
		delta += xp->compat_tab[xp->cur - 1].delta;
	xp->compat_tab[xp->cur].offset = offset;
	xp->compat_tab[xp->cur].delta = delta;
	xp->cur++;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xt_compat_add_offset);

व्योम xt_compat_flush_offsets(u_पूर्णांक8_t af)
अणु
	WARN_ON(!mutex_is_locked(&xt[af].compat_mutex));

	अगर (xt[af].compat_tab) अणु
		vमुक्त(xt[af].compat_tab);
		xt[af].compat_tab = शून्य;
		xt[af].number = 0;
		xt[af].cur = 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(xt_compat_flush_offsets);

पूर्णांक xt_compat_calc_jump(u_पूर्णांक8_t af, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा compat_delta *पंचांगp = xt[af].compat_tab;
	पूर्णांक mid, left = 0, right = xt[af].cur - 1;

	जबतक (left <= right) अणु
		mid = (left + right) >> 1;
		अगर (offset > पंचांगp[mid].offset)
			left = mid + 1;
		अन्यथा अगर (offset < पंचांगp[mid].offset)
			right = mid - 1;
		अन्यथा
			वापस mid ? पंचांगp[mid - 1].delta : 0;
	पूर्ण
	वापस left ? पंचांगp[left - 1].delta : 0;
पूर्ण
EXPORT_SYMBOL_GPL(xt_compat_calc_jump);

पूर्णांक xt_compat_init_offsets(u8 af, अचिन्हित पूर्णांक number)
अणु
	माप_प्रकार mem;

	WARN_ON(!mutex_is_locked(&xt[af].compat_mutex));

	अगर (!number || number > (पूर्णांक_उच्च / माप(काष्ठा compat_delta)))
		वापस -EINVAL;

	अगर (WARN_ON(xt[af].compat_tab))
		वापस -EINVAL;

	mem = माप(काष्ठा compat_delta) * number;
	अगर (mem > XT_MAX_TABLE_SIZE)
		वापस -ENOMEM;

	xt[af].compat_tab = vदो_स्मृति(mem);
	अगर (!xt[af].compat_tab)
		वापस -ENOMEM;

	xt[af].number = number;
	xt[af].cur = 0;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(xt_compat_init_offsets);

पूर्णांक xt_compat_match_offset(स्थिर काष्ठा xt_match *match)
अणु
	u_पूर्णांक16_t csize = match->compatsize ? : match->matchsize;
	वापस XT_ALIGN(match->matchsize) - COMPAT_XT_ALIGN(csize);
पूर्ण
EXPORT_SYMBOL_GPL(xt_compat_match_offset);

व्योम xt_compat_match_from_user(काष्ठा xt_entry_match *m, व्योम **dstptr,
			       अचिन्हित पूर्णांक *size)
अणु
	स्थिर काष्ठा xt_match *match = m->u.kernel.match;
	काष्ठा compat_xt_entry_match *cm = (काष्ठा compat_xt_entry_match *)m;
	पूर्णांक off = xt_compat_match_offset(match);
	u_पूर्णांक16_t msize = cm->u.user.match_size;
	अक्षर name[माप(m->u.user.name)];

	m = *dstptr;
	स_नकल(m, cm, माप(*cm));
	अगर (match->compat_from_user)
		match->compat_from_user(m->data, cm->data);
	अन्यथा
		स_नकल(m->data, cm->data, msize - माप(*cm));

	msize += off;
	m->u.user.match_size = msize;
	strlcpy(name, match->name, माप(name));
	module_put(match->me);
	म_नकलन(m->u.user.name, name, माप(m->u.user.name));

	*size += off;
	*dstptr += msize;
पूर्ण
EXPORT_SYMBOL_GPL(xt_compat_match_from_user);

#घोषणा COMPAT_XT_DATA_TO_USER(U, K, TYPE, C_SIZE)			\
	xt_data_to_user(U->data, K->data,				\
			K->u.kernel.TYPE->usersize,			\
			C_SIZE,						\
			COMPAT_XT_ALIGN(C_SIZE))

पूर्णांक xt_compat_match_to_user(स्थिर काष्ठा xt_entry_match *m,
			    व्योम __user **dstptr, अचिन्हित पूर्णांक *size)
अणु
	स्थिर काष्ठा xt_match *match = m->u.kernel.match;
	काष्ठा compat_xt_entry_match __user *cm = *dstptr;
	पूर्णांक off = xt_compat_match_offset(match);
	u_पूर्णांक16_t msize = m->u.user.match_size - off;

	अगर (XT_OBJ_TO_USER(cm, m, match, msize))
		वापस -EFAULT;

	अगर (match->compat_to_user) अणु
		अगर (match->compat_to_user((व्योम __user *)cm->data, m->data))
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		अगर (COMPAT_XT_DATA_TO_USER(cm, m, match, msize - माप(*cm)))
			वापस -EFAULT;
	पूर्ण

	*size -= off;
	*dstptr += msize;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xt_compat_match_to_user);

/* non-compat version may have padding after verdict */
काष्ठा compat_xt_standard_target अणु
	काष्ठा compat_xt_entry_target t;
	compat_uपूर्णांक_t verdict;
पूर्ण;

काष्ठा compat_xt_error_target अणु
	काष्ठा compat_xt_entry_target t;
	अक्षर errorname[XT_FUNCTION_MAXNAMELEN];
पूर्ण;

पूर्णांक xt_compat_check_entry_offsets(स्थिर व्योम *base, स्थिर अक्षर *elems,
				  अचिन्हित पूर्णांक target_offset,
				  अचिन्हित पूर्णांक next_offset)
अणु
	दीर्घ size_of_base_काष्ठा = elems - (स्थिर अक्षर *)base;
	स्थिर काष्ठा compat_xt_entry_target *t;
	स्थिर अक्षर *e = base;

	अगर (target_offset < size_of_base_काष्ठा)
		वापस -EINVAL;

	अगर (target_offset + माप(*t) > next_offset)
		वापस -EINVAL;

	t = (व्योम *)(e + target_offset);
	अगर (t->u.target_size < माप(*t))
		वापस -EINVAL;

	अगर (target_offset + t->u.target_size > next_offset)
		वापस -EINVAL;

	अगर (म_भेद(t->u.user.name, XT_STANDARD_TARGET) == 0) अणु
		स्थिर काष्ठा compat_xt_standard_target *st = (स्थिर व्योम *)t;

		अगर (COMPAT_XT_ALIGN(target_offset + माप(*st)) != next_offset)
			वापस -EINVAL;

		अगर (!verdict_ok(st->verdict))
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (म_भेद(t->u.user.name, XT_ERROR_TARGET) == 0) अणु
		स्थिर काष्ठा compat_xt_error_target *et = (स्थिर व्योम *)t;

		अगर (!error_tg_ok(t->u.target_size, माप(*et),
				 et->errorname, माप(et->errorname)))
			वापस -EINVAL;
	पूर्ण

	/* compat_xt_entry match has less strict alignment requirements,
	 * otherwise they are identical.  In हाल of padding dअगरferences
	 * we need to add compat version of xt_check_entry_match.
	 */
	BUILD_BUG_ON(माप(काष्ठा compat_xt_entry_match) != माप(काष्ठा xt_entry_match));

	वापस xt_check_entry_match(elems, base + target_offset,
				    __alignof__(काष्ठा compat_xt_entry_match));
पूर्ण
EXPORT_SYMBOL(xt_compat_check_entry_offsets);
#पूर्ण_अगर /* CONFIG_NETFILTER_XTABLES_COMPAT */

/**
 * xt_check_entry_offsets - validate arp/ip/ip6t_entry
 *
 * @base: poपूर्णांकer to arp/ip/ip6t_entry
 * @elems: poपूर्णांकer to first xt_entry_match, i.e. ip(6)t_entry->elems
 * @target_offset: the arp/ip/ip6_t->target_offset
 * @next_offset: the arp/ip/ip6_t->next_offset
 *
 * validates that target_offset and next_offset are sane and that all
 * match sizes (अगर any) align with the target offset.
 *
 * This function करोes not validate the tarमाला_लो or matches themselves, it
 * only tests that all the offsets and sizes are correct, that all
 * match काष्ठाures are aligned, and that the last काष्ठाure ends where
 * the target काष्ठाure begins.
 *
 * Also see xt_compat_check_entry_offsets क्रम CONFIG_NETFILTER_XTABLES_COMPAT version.
 *
 * The arp/ip/ip6t_entry काष्ठाure @base must have passed following tests:
 * - it must poपूर्णांक to a valid memory location
 * - base to base + next_offset must be accessible, i.e. not exceed allocated
 *   length.
 *
 * A well-क्रमmed entry looks like this:
 *
 * ip(6)t_entry   match [mtdata]  match [mtdata] target [tgdata] ip(6)t_entry
 * e->elems[]-----'                              |               |
 *                matchsize                      |               |
 *                                matchsize      |               |
 *                                               |               |
 * target_offset---------------------------------'               |
 * next_offset---------------------------------------------------'
 *
 * elems[]: flexible array member at end of ip(6)/arpt_entry काष्ठा.
 *          This is where matches (अगर any) and the target reside.
 * target_offset: beginning of target.
 * next_offset: start of the next rule; also: size of this rule.
 * Since tarमाला_लो have a minimum size, target_offset + minlen <= next_offset.
 *
 * Every match stores its size, sum of sizes must not exceed target_offset.
 *
 * Return: 0 on success, negative त्रुटि_सं on failure.
 */
पूर्णांक xt_check_entry_offsets(स्थिर व्योम *base,
			   स्थिर अक्षर *elems,
			   अचिन्हित पूर्णांक target_offset,
			   अचिन्हित पूर्णांक next_offset)
अणु
	दीर्घ size_of_base_काष्ठा = elems - (स्थिर अक्षर *)base;
	स्थिर काष्ठा xt_entry_target *t;
	स्थिर अक्षर *e = base;

	/* target start is within the ip/ip6/arpt_entry काष्ठा */
	अगर (target_offset < size_of_base_काष्ठा)
		वापस -EINVAL;

	अगर (target_offset + माप(*t) > next_offset)
		वापस -EINVAL;

	t = (व्योम *)(e + target_offset);
	अगर (t->u.target_size < माप(*t))
		वापस -EINVAL;

	अगर (target_offset + t->u.target_size > next_offset)
		वापस -EINVAL;

	अगर (म_भेद(t->u.user.name, XT_STANDARD_TARGET) == 0) अणु
		स्थिर काष्ठा xt_standard_target *st = (स्थिर व्योम *)t;

		अगर (XT_ALIGN(target_offset + माप(*st)) != next_offset)
			वापस -EINVAL;

		अगर (!verdict_ok(st->verdict))
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (म_भेद(t->u.user.name, XT_ERROR_TARGET) == 0) अणु
		स्थिर काष्ठा xt_error_target *et = (स्थिर व्योम *)t;

		अगर (!error_tg_ok(t->u.target_size, माप(*et),
				 et->errorname, माप(et->errorname)))
			वापस -EINVAL;
	पूर्ण

	वापस xt_check_entry_match(elems, base + target_offset,
				    __alignof__(काष्ठा xt_entry_match));
पूर्ण
EXPORT_SYMBOL(xt_check_entry_offsets);

/**
 * xt_alloc_entry_offsets - allocate array to store rule head offsets
 *
 * @size: number of entries
 *
 * Return: शून्य or zeroed kदो_स्मृति'd or vmalloc'd array
 */
अचिन्हित पूर्णांक *xt_alloc_entry_offsets(अचिन्हित पूर्णांक size)
अणु
	अगर (size > XT_MAX_TABLE_SIZE / माप(अचिन्हित पूर्णांक))
		वापस शून्य;

	वापस kvसुस्मृति(size, माप(अचिन्हित पूर्णांक), GFP_KERNEL);

पूर्ण
EXPORT_SYMBOL(xt_alloc_entry_offsets);

/**
 * xt_find_jump_offset - check अगर target is a valid jump offset
 *
 * @offsets: array containing all valid rule start offsets of a rule blob
 * @target: the jump target to search क्रम
 * @size: entries in @offset
 */
bool xt_find_jump_offset(स्थिर अचिन्हित पूर्णांक *offsets,
			 अचिन्हित पूर्णांक target, अचिन्हित पूर्णांक size)
अणु
	पूर्णांक m, low = 0, hi = size;

	जबतक (hi > low) अणु
		m = (low + hi) / 2u;

		अगर (offsets[m] > target)
			hi = m;
		अन्यथा अगर (offsets[m] < target)
			low = m + 1;
		अन्यथा
			वापस true;
	पूर्ण

	वापस false;
पूर्ण
EXPORT_SYMBOL(xt_find_jump_offset);

पूर्णांक xt_check_target(काष्ठा xt_tgchk_param *par,
		    अचिन्हित पूर्णांक size, u16 proto, bool inv_proto)
अणु
	पूर्णांक ret;

	अगर (XT_ALIGN(par->target->tarमाला_लोize) != size) अणु
		pr_err_ratelimited("%s_tables: %s.%u target: invalid size %u (kernel) != (user) %u\n",
				   xt_prefix[par->family], par->target->name,
				   par->target->revision,
				   XT_ALIGN(par->target->tarमाला_लोize), size);
		वापस -EINVAL;
	पूर्ण
	अगर (par->target->table != शून्य &&
	    म_भेद(par->target->table, par->table) != 0) अणु
		pr_info_ratelimited("%s_tables: %s target: only valid in %s table, not %s\n",
				    xt_prefix[par->family], par->target->name,
				    par->target->table, par->table);
		वापस -EINVAL;
	पूर्ण
	अगर (par->target->hooks && (par->hook_mask & ~par->target->hooks) != 0) अणु
		अक्षर used[64], allow[64];

		pr_info_ratelimited("%s_tables: %s target: used from hooks %s, but only usable from %s\n",
				    xt_prefix[par->family], par->target->name,
				    textअगरy_hooks(used, माप(used),
						  par->hook_mask, par->family),
				    textअगरy_hooks(allow, माप(allow),
						  par->target->hooks,
						  par->family));
		वापस -EINVAL;
	पूर्ण
	अगर (par->target->proto && (par->target->proto != proto || inv_proto)) अणु
		pr_info_ratelimited("%s_tables: %s target: only valid for protocol %u\n",
				    xt_prefix[par->family], par->target->name,
				    par->target->proto);
		वापस -EINVAL;
	पूर्ण
	अगर (par->target->checkentry != शून्य) अणु
		ret = par->target->checkentry(par);
		अगर (ret < 0)
			वापस ret;
		अन्यथा अगर (ret > 0)
			/* Flag up potential errors. */
			वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xt_check_target);

/**
 * xt_copy_counters - copy counters and metadata from a sockptr_t
 *
 * @arg: src sockptr
 * @len: alleged size of userspace memory
 * @info: where to store the xt_counters_info metadata
 *
 * Copies counter meta data from @user and stores it in @info.
 *
 * vदो_स्मृतिs memory to hold the counters, then copies the counter data
 * from @user to the new memory and वापसs a poपूर्णांकer to it.
 *
 * If called from a compat syscall, @info माला_लो converted स्वतःmatically to the
 * 64bit representation.
 *
 * The metadata associated with the counters is stored in @info.
 *
 * Return: वापसs poपूर्णांकer that caller has to test via IS_ERR().
 * If IS_ERR is false, caller has to vमुक्त the poपूर्णांकer.
 */
व्योम *xt_copy_counters(sockptr_t arg, अचिन्हित पूर्णांक len,
		       काष्ठा xt_counters_info *info)
अणु
	माप_प्रकार offset;
	व्योम *mem;
	u64 size;

#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
	अगर (in_compat_syscall()) अणु
		/* काष्ठाures only dअगरfer in size due to alignment */
		काष्ठा compat_xt_counters_info compat_पंचांगp;

		अगर (len <= माप(compat_पंचांगp))
			वापस ERR_PTR(-EINVAL);

		len -= माप(compat_पंचांगp);
		अगर (copy_from_sockptr(&compat_पंचांगp, arg, माप(compat_पंचांगp)) != 0)
			वापस ERR_PTR(-EFAULT);

		स_नकल(info->name, compat_पंचांगp.name, माप(info->name) - 1);
		info->num_counters = compat_पंचांगp.num_counters;
		offset = माप(compat_पंचांगp);
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		अगर (len <= माप(*info))
			वापस ERR_PTR(-EINVAL);

		len -= माप(*info);
		अगर (copy_from_sockptr(info, arg, माप(*info)) != 0)
			वापस ERR_PTR(-EFAULT);

		offset = माप(*info);
	पूर्ण
	info->name[माप(info->name) - 1] = '\0';

	size = माप(काष्ठा xt_counters);
	size *= info->num_counters;

	अगर (size != (u64)len)
		वापस ERR_PTR(-EINVAL);

	mem = vदो_स्मृति(len);
	अगर (!mem)
		वापस ERR_PTR(-ENOMEM);

	अगर (copy_from_sockptr_offset(mem, arg, offset, len) == 0)
		वापस mem;

	vमुक्त(mem);
	वापस ERR_PTR(-EFAULT);
पूर्ण
EXPORT_SYMBOL_GPL(xt_copy_counters);

#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
पूर्णांक xt_compat_target_offset(स्थिर काष्ठा xt_target *target)
अणु
	u_पूर्णांक16_t csize = target->compatsize ? : target->tarमाला_लोize;
	वापस XT_ALIGN(target->tarमाला_लोize) - COMPAT_XT_ALIGN(csize);
पूर्ण
EXPORT_SYMBOL_GPL(xt_compat_target_offset);

व्योम xt_compat_target_from_user(काष्ठा xt_entry_target *t, व्योम **dstptr,
				अचिन्हित पूर्णांक *size)
अणु
	स्थिर काष्ठा xt_target *target = t->u.kernel.target;
	काष्ठा compat_xt_entry_target *ct = (काष्ठा compat_xt_entry_target *)t;
	पूर्णांक off = xt_compat_target_offset(target);
	u_पूर्णांक16_t tsize = ct->u.user.target_size;
	अक्षर name[माप(t->u.user.name)];

	t = *dstptr;
	स_नकल(t, ct, माप(*ct));
	अगर (target->compat_from_user)
		target->compat_from_user(t->data, ct->data);
	अन्यथा
		स_नकल(t->data, ct->data, tsize - माप(*ct));

	tsize += off;
	t->u.user.target_size = tsize;
	strlcpy(name, target->name, माप(name));
	module_put(target->me);
	म_नकलन(t->u.user.name, name, माप(t->u.user.name));

	*size += off;
	*dstptr += tsize;
पूर्ण
EXPORT_SYMBOL_GPL(xt_compat_target_from_user);

पूर्णांक xt_compat_target_to_user(स्थिर काष्ठा xt_entry_target *t,
			     व्योम __user **dstptr, अचिन्हित पूर्णांक *size)
अणु
	स्थिर काष्ठा xt_target *target = t->u.kernel.target;
	काष्ठा compat_xt_entry_target __user *ct = *dstptr;
	पूर्णांक off = xt_compat_target_offset(target);
	u_पूर्णांक16_t tsize = t->u.user.target_size - off;

	अगर (XT_OBJ_TO_USER(ct, t, target, tsize))
		वापस -EFAULT;

	अगर (target->compat_to_user) अणु
		अगर (target->compat_to_user((व्योम __user *)ct->data, t->data))
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		अगर (COMPAT_XT_DATA_TO_USER(ct, t, target, tsize - माप(*ct)))
			वापस -EFAULT;
	पूर्ण

	*size -= off;
	*dstptr += tsize;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xt_compat_target_to_user);
#पूर्ण_अगर

काष्ठा xt_table_info *xt_alloc_table_info(अचिन्हित पूर्णांक size)
अणु
	काष्ठा xt_table_info *info = शून्य;
	माप_प्रकार sz = माप(*info) + size;

	अगर (sz < माप(*info) || sz >= XT_MAX_TABLE_SIZE)
		वापस शून्य;

	info = kvदो_स्मृति(sz, GFP_KERNEL_ACCOUNT);
	अगर (!info)
		वापस शून्य;

	स_रखो(info, 0, माप(*info));
	info->size = size;
	वापस info;
पूर्ण
EXPORT_SYMBOL(xt_alloc_table_info);

व्योम xt_मुक्त_table_info(काष्ठा xt_table_info *info)
अणु
	पूर्णांक cpu;

	अगर (info->jumpstack != शून्य) अणु
		क्रम_each_possible_cpu(cpu)
			kvमुक्त(info->jumpstack[cpu]);
		kvमुक्त(info->jumpstack);
	पूर्ण

	kvमुक्त(info);
पूर्ण
EXPORT_SYMBOL(xt_मुक्त_table_info);

काष्ठा xt_table *xt_find_table(काष्ठा net *net, u8 af, स्थिर अक्षर *name)
अणु
	काष्ठा xt_pernet *xt_net = net_generic(net, xt_pernet_id);
	काष्ठा xt_table *t;

	mutex_lock(&xt[af].mutex);
	list_क्रम_each_entry(t, &xt_net->tables[af], list) अणु
		अगर (म_भेद(t->name, name) == 0) अणु
			mutex_unlock(&xt[af].mutex);
			वापस t;
		पूर्ण
	पूर्ण
	mutex_unlock(&xt[af].mutex);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(xt_find_table);

/* Find table by name, grअसल mutex & ref.  Returns ERR_PTR on error. */
काष्ठा xt_table *xt_find_table_lock(काष्ठा net *net, u_पूर्णांक8_t af,
				    स्थिर अक्षर *name)
अणु
	काष्ठा xt_pernet *xt_net = net_generic(net, xt_pernet_id);
	काष्ठा xt_table *t, *found = शून्य;

	mutex_lock(&xt[af].mutex);
	list_क्रम_each_entry(t, &xt_net->tables[af], list)
		अगर (म_भेद(t->name, name) == 0 && try_module_get(t->me))
			वापस t;

	अगर (net == &init_net)
		जाओ out;

	/* Table करोesn't exist in this netns, re-try init */
	xt_net = net_generic(&init_net, xt_pernet_id);
	list_क्रम_each_entry(t, &xt_net->tables[af], list) अणु
		पूर्णांक err;

		अगर (म_भेद(t->name, name))
			जारी;
		अगर (!try_module_get(t->me))
			जाओ out;
		mutex_unlock(&xt[af].mutex);
		err = t->table_init(net);
		अगर (err < 0) अणु
			module_put(t->me);
			वापस ERR_PTR(err);
		पूर्ण

		found = t;

		mutex_lock(&xt[af].mutex);
		अवरोध;
	पूर्ण

	अगर (!found)
		जाओ out;

	xt_net = net_generic(net, xt_pernet_id);
	/* and once again: */
	list_क्रम_each_entry(t, &xt_net->tables[af], list)
		अगर (म_भेद(t->name, name) == 0)
			वापस t;

	module_put(found->me);
 out:
	mutex_unlock(&xt[af].mutex);
	वापस ERR_PTR(-ENOENT);
पूर्ण
EXPORT_SYMBOL_GPL(xt_find_table_lock);

काष्ठा xt_table *xt_request_find_table_lock(काष्ठा net *net, u_पूर्णांक8_t af,
					    स्थिर अक्षर *name)
अणु
	काष्ठा xt_table *t = xt_find_table_lock(net, af, name);

#अगर_घोषित CONFIG_MODULES
	अगर (IS_ERR(t)) अणु
		पूर्णांक err = request_module("%stable_%s", xt_prefix[af], name);
		अगर (err < 0)
			वापस ERR_PTR(err);
		t = xt_find_table_lock(net, af, name);
	पूर्ण
#पूर्ण_अगर

	वापस t;
पूर्ण
EXPORT_SYMBOL_GPL(xt_request_find_table_lock);

व्योम xt_table_unlock(काष्ठा xt_table *table)
अणु
	mutex_unlock(&xt[table->af].mutex);
पूर्ण
EXPORT_SYMBOL_GPL(xt_table_unlock);

#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
व्योम xt_compat_lock(u_पूर्णांक8_t af)
अणु
	mutex_lock(&xt[af].compat_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(xt_compat_lock);

व्योम xt_compat_unlock(u_पूर्णांक8_t af)
अणु
	mutex_unlock(&xt[af].compat_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(xt_compat_unlock);
#पूर्ण_अगर

DEFINE_PER_CPU(seqcount_t, xt_recseq);
EXPORT_PER_CPU_SYMBOL_GPL(xt_recseq);

काष्ठा अटल_key xt_tee_enabled __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(xt_tee_enabled);

अटल पूर्णांक xt_jumpstack_alloc(काष्ठा xt_table_info *i)
अणु
	अचिन्हित पूर्णांक size;
	पूर्णांक cpu;

	size = माप(व्योम **) * nr_cpu_ids;
	अगर (size > PAGE_SIZE)
		i->jumpstack = kvzalloc(size, GFP_KERNEL);
	अन्यथा
		i->jumpstack = kzalloc(size, GFP_KERNEL);
	अगर (i->jumpstack == शून्य)
		वापस -ENOMEM;

	/* ruleset without jumps -- no stack needed */
	अगर (i->stacksize == 0)
		वापस 0;

	/* Jumpstack needs to be able to record two full callchains, one
	 * from the first rule set traversal, plus one table reentrancy
	 * via -j TEE without clobbering the callchain that brought us to
	 * TEE target.
	 *
	 * This is करोne by allocating two jumpstacks per cpu, on reentry
	 * the upper half of the stack is used.
	 *
	 * see the jumpstack setup in ipt_करो_table() क्रम more details.
	 */
	size = माप(व्योम *) * i->stacksize * 2u;
	क्रम_each_possible_cpu(cpu) अणु
		i->jumpstack[cpu] = kvदो_स्मृति_node(size, GFP_KERNEL,
			cpu_to_node(cpu));
		अगर (i->jumpstack[cpu] == शून्य)
			/*
			 * Freeing will be करोne later on by the callers. The
			 * chain is: xt_replace_table -> __करो_replace ->
			 * करो_replace -> xt_मुक्त_table_info.
			 */
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा xt_counters *xt_counters_alloc(अचिन्हित पूर्णांक counters)
अणु
	काष्ठा xt_counters *mem;

	अगर (counters == 0 || counters > पूर्णांक_उच्च / माप(*mem))
		वापस शून्य;

	counters *= माप(*mem);
	अगर (counters > XT_MAX_TABLE_SIZE)
		वापस शून्य;

	वापस vzalloc(counters);
पूर्ण
EXPORT_SYMBOL(xt_counters_alloc);

काष्ठा xt_table_info *
xt_replace_table(काष्ठा xt_table *table,
	      अचिन्हित पूर्णांक num_counters,
	      काष्ठा xt_table_info *newinfo,
	      पूर्णांक *error)
अणु
	काष्ठा xt_table_info *निजी;
	अचिन्हित पूर्णांक cpu;
	पूर्णांक ret;

	ret = xt_jumpstack_alloc(newinfo);
	अगर (ret < 0) अणु
		*error = ret;
		वापस शून्य;
	पूर्ण

	/* Do the substitution. */
	local_bh_disable();
	निजी = table->निजी;

	/* Check inside lock: is the old number correct? */
	अगर (num_counters != निजी->number) अणु
		pr_debug("num_counters != table->private->number (%u/%u)\n",
			 num_counters, निजी->number);
		local_bh_enable();
		*error = -EAGAIN;
		वापस शून्य;
	पूर्ण

	newinfo->initial_entries = निजी->initial_entries;
	/*
	 * Ensure contents of newinfo are visible beक्रमe assigning to
	 * निजी.
	 */
	smp_wmb();
	table->निजी = newinfo;

	/* make sure all cpus see new ->निजी value */
	smp_mb();

	/*
	 * Even though table entries have now been swapped, other CPU's
	 * may still be using the old entries...
	 */
	local_bh_enable();

	/* ... so रुको क्रम even xt_recseq on all cpus */
	क्रम_each_possible_cpu(cpu) अणु
		seqcount_t *s = &per_cpu(xt_recseq, cpu);
		u32 seq = raw_पढ़ो_seqcount(s);

		अगर (seq & 1) अणु
			करो अणु
				cond_resched();
				cpu_relax();
			पूर्ण जबतक (seq == raw_पढ़ो_seqcount(s));
		पूर्ण
	पूर्ण

	audit_log_nfcfg(table->name, table->af, निजी->number,
			!निजी->number ? AUDIT_XT_OP_REGISTER :
					   AUDIT_XT_OP_REPLACE,
			GFP_KERNEL);
	वापस निजी;
पूर्ण
EXPORT_SYMBOL_GPL(xt_replace_table);

काष्ठा xt_table *xt_रेजिस्टर_table(काष्ठा net *net,
				   स्थिर काष्ठा xt_table *input_table,
				   काष्ठा xt_table_info *bootstrap,
				   काष्ठा xt_table_info *newinfo)
अणु
	काष्ठा xt_pernet *xt_net = net_generic(net, xt_pernet_id);
	काष्ठा xt_table_info *निजी;
	काष्ठा xt_table *t, *table;
	पूर्णांक ret;

	/* Don't add one object to multiple lists. */
	table = kmemdup(input_table, माप(काष्ठा xt_table), GFP_KERNEL);
	अगर (!table) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	mutex_lock(&xt[table->af].mutex);
	/* Don't autoload: we'd eat our tail... */
	list_क्रम_each_entry(t, &xt_net->tables[table->af], list) अणु
		अगर (म_भेद(t->name, table->name) == 0) अणु
			ret = -EEXIST;
			जाओ unlock;
		पूर्ण
	पूर्ण

	/* Simplअगरies replace_table code. */
	table->निजी = bootstrap;

	अगर (!xt_replace_table(table, 0, newinfo, &ret))
		जाओ unlock;

	निजी = table->निजी;
	pr_debug("table->private->number = %u\n", निजी->number);

	/* save number of initial entries */
	निजी->initial_entries = निजी->number;

	list_add(&table->list, &xt_net->tables[table->af]);
	mutex_unlock(&xt[table->af].mutex);
	वापस table;

unlock:
	mutex_unlock(&xt[table->af].mutex);
	kमुक्त(table);
out:
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(xt_रेजिस्टर_table);

व्योम *xt_unरेजिस्टर_table(काष्ठा xt_table *table)
अणु
	काष्ठा xt_table_info *निजी;

	mutex_lock(&xt[table->af].mutex);
	निजी = table->निजी;
	list_del(&table->list);
	mutex_unlock(&xt[table->af].mutex);
	audit_log_nfcfg(table->name, table->af, निजी->number,
			AUDIT_XT_OP_UNREGISTER, GFP_KERNEL);
	kमुक्त(table->ops);
	kमुक्त(table);

	वापस निजी;
पूर्ण
EXPORT_SYMBOL_GPL(xt_unरेजिस्टर_table);

#अगर_घोषित CONFIG_PROC_FS
अटल व्योम *xt_table_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	u8 af = (अचिन्हित दीर्घ)PDE_DATA(file_inode(seq->file));
	काष्ठा net *net = seq_file_net(seq);
	काष्ठा xt_pernet *xt_net;

	xt_net = net_generic(net, xt_pernet_id);

	mutex_lock(&xt[af].mutex);
	वापस seq_list_start(&xt_net->tables[af], *pos);
पूर्ण

अटल व्योम *xt_table_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	u8 af = (अचिन्हित दीर्घ)PDE_DATA(file_inode(seq->file));
	काष्ठा net *net = seq_file_net(seq);
	काष्ठा xt_pernet *xt_net;

	xt_net = net_generic(net, xt_pernet_id);

	वापस seq_list_next(v, &xt_net->tables[af], pos);
पूर्ण

अटल व्योम xt_table_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	u_पूर्णांक8_t af = (अचिन्हित दीर्घ)PDE_DATA(file_inode(seq->file));

	mutex_unlock(&xt[af].mutex);
पूर्ण

अटल पूर्णांक xt_table_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा xt_table *table = list_entry(v, काष्ठा xt_table, list);

	अगर (*table->name)
		seq_म_लिखो(seq, "%s\n", table->name);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations xt_table_seq_ops = अणु
	.start	= xt_table_seq_start,
	.next	= xt_table_seq_next,
	.stop	= xt_table_seq_stop,
	.show	= xt_table_seq_show,
पूर्ण;

/*
 * Traverse state क्रम ipअणु,6पूर्ण_अणुtables,matchesपूर्ण क्रम helping crossing
 * the multi-AF mutexes.
 */
काष्ठा nf_mttg_trav अणु
	काष्ठा list_head *head, *curr;
	uपूर्णांक8_t class;
पूर्ण;

क्रमागत अणु
	MTTG_TRAV_INIT,
	MTTG_TRAV_NFP_UNSPEC,
	MTTG_TRAV_NFP_SPEC,
	MTTG_TRAV_DONE,
पूर्ण;

अटल व्योम *xt_mttg_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *ppos,
    bool is_target)
अणु
	अटल स्थिर uपूर्णांक8_t next_class[] = अणु
		[MTTG_TRAV_NFP_UNSPEC] = MTTG_TRAV_NFP_SPEC,
		[MTTG_TRAV_NFP_SPEC]   = MTTG_TRAV_DONE,
	पूर्ण;
	uपूर्णांक8_t nfproto = (अचिन्हित दीर्घ)PDE_DATA(file_inode(seq->file));
	काष्ठा nf_mttg_trav *trav = seq->निजी;

	अगर (ppos != शून्य)
		++(*ppos);

	चयन (trav->class) अणु
	हाल MTTG_TRAV_INIT:
		trav->class = MTTG_TRAV_NFP_UNSPEC;
		mutex_lock(&xt[NFPROTO_UNSPEC].mutex);
		trav->head = trav->curr = is_target ?
			&xt[NFPROTO_UNSPEC].target : &xt[NFPROTO_UNSPEC].match;
 		अवरोध;
	हाल MTTG_TRAV_NFP_UNSPEC:
		trav->curr = trav->curr->next;
		अगर (trav->curr != trav->head)
			अवरोध;
		mutex_unlock(&xt[NFPROTO_UNSPEC].mutex);
		mutex_lock(&xt[nfproto].mutex);
		trav->head = trav->curr = is_target ?
			&xt[nfproto].target : &xt[nfproto].match;
		trav->class = next_class[trav->class];
		अवरोध;
	हाल MTTG_TRAV_NFP_SPEC:
		trav->curr = trav->curr->next;
		अगर (trav->curr != trav->head)
			अवरोध;
		fallthrough;
	शेष:
		वापस शून्य;
	पूर्ण
	वापस trav;
पूर्ण

अटल व्योम *xt_mttg_seq_start(काष्ठा seq_file *seq, loff_t *pos,
    bool is_target)
अणु
	काष्ठा nf_mttg_trav *trav = seq->निजी;
	अचिन्हित पूर्णांक j;

	trav->class = MTTG_TRAV_INIT;
	क्रम (j = 0; j < *pos; ++j)
		अगर (xt_mttg_seq_next(seq, शून्य, शून्य, is_target) == शून्य)
			वापस शून्य;
	वापस trav;
पूर्ण

अटल व्योम xt_mttg_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	uपूर्णांक8_t nfproto = (अचिन्हित दीर्घ)PDE_DATA(file_inode(seq->file));
	काष्ठा nf_mttg_trav *trav = seq->निजी;

	चयन (trav->class) अणु
	हाल MTTG_TRAV_NFP_UNSPEC:
		mutex_unlock(&xt[NFPROTO_UNSPEC].mutex);
		अवरोध;
	हाल MTTG_TRAV_NFP_SPEC:
		mutex_unlock(&xt[nfproto].mutex);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम *xt_match_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	वापस xt_mttg_seq_start(seq, pos, false);
पूर्ण

अटल व्योम *xt_match_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *ppos)
अणु
	वापस xt_mttg_seq_next(seq, v, ppos, false);
पूर्ण

अटल पूर्णांक xt_match_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	स्थिर काष्ठा nf_mttg_trav *trav = seq->निजी;
	स्थिर काष्ठा xt_match *match;

	चयन (trav->class) अणु
	हाल MTTG_TRAV_NFP_UNSPEC:
	हाल MTTG_TRAV_NFP_SPEC:
		अगर (trav->curr == trav->head)
			वापस 0;
		match = list_entry(trav->curr, काष्ठा xt_match, list);
		अगर (*match->name)
			seq_म_लिखो(seq, "%s\n", match->name);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations xt_match_seq_ops = अणु
	.start	= xt_match_seq_start,
	.next	= xt_match_seq_next,
	.stop	= xt_mttg_seq_stop,
	.show	= xt_match_seq_show,
पूर्ण;

अटल व्योम *xt_target_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	वापस xt_mttg_seq_start(seq, pos, true);
पूर्ण

अटल व्योम *xt_target_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *ppos)
अणु
	वापस xt_mttg_seq_next(seq, v, ppos, true);
पूर्ण

अटल पूर्णांक xt_target_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	स्थिर काष्ठा nf_mttg_trav *trav = seq->निजी;
	स्थिर काष्ठा xt_target *target;

	चयन (trav->class) अणु
	हाल MTTG_TRAV_NFP_UNSPEC:
	हाल MTTG_TRAV_NFP_SPEC:
		अगर (trav->curr == trav->head)
			वापस 0;
		target = list_entry(trav->curr, काष्ठा xt_target, list);
		अगर (*target->name)
			seq_म_लिखो(seq, "%s\n", target->name);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations xt_target_seq_ops = अणु
	.start	= xt_target_seq_start,
	.next	= xt_target_seq_next,
	.stop	= xt_mttg_seq_stop,
	.show	= xt_target_seq_show,
पूर्ण;

#घोषणा FORMAT_TABLES	"_tables_names"
#घोषणा	FORMAT_MATCHES	"_tables_matches"
#घोषणा FORMAT_TARGETS 	"_tables_targets"

#पूर्ण_अगर /* CONFIG_PROC_FS */

/**
 * xt_hook_ops_alloc - set up hooks क्रम a new table
 * @table:	table with metadata needed to set up hooks
 * @fn:		Hook function
 *
 * This function will create the nf_hook_ops that the x_table needs
 * to hand to xt_hook_link_net().
 */
काष्ठा nf_hook_ops *
xt_hook_ops_alloc(स्थिर काष्ठा xt_table *table, nf_hookfn *fn)
अणु
	अचिन्हित पूर्णांक hook_mask = table->valid_hooks;
	uपूर्णांक8_t i, num_hooks = hweight32(hook_mask);
	uपूर्णांक8_t hooknum;
	काष्ठा nf_hook_ops *ops;

	अगर (!num_hooks)
		वापस ERR_PTR(-EINVAL);

	ops = kसुस्मृति(num_hooks, माप(*ops), GFP_KERNEL);
	अगर (ops == शून्य)
		वापस ERR_PTR(-ENOMEM);

	क्रम (i = 0, hooknum = 0; i < num_hooks && hook_mask != 0;
	     hook_mask >>= 1, ++hooknum) अणु
		अगर (!(hook_mask & 1))
			जारी;
		ops[i].hook     = fn;
		ops[i].pf       = table->af;
		ops[i].hooknum  = hooknum;
		ops[i].priority = table->priority;
		++i;
	पूर्ण

	वापस ops;
पूर्ण
EXPORT_SYMBOL_GPL(xt_hook_ops_alloc);

पूर्णांक xt_proto_init(काष्ठा net *net, u_पूर्णांक8_t af)
अणु
#अगर_घोषित CONFIG_PROC_FS
	अक्षर buf[XT_FUNCTION_MAXNAMELEN];
	काष्ठा proc_dir_entry *proc;
	kuid_t root_uid;
	kgid_t root_gid;
#पूर्ण_अगर

	अगर (af >= ARRAY_SIZE(xt_prefix))
		वापस -EINVAL;


#अगर_घोषित CONFIG_PROC_FS
	root_uid = make_kuid(net->user_ns, 0);
	root_gid = make_kgid(net->user_ns, 0);

	strlcpy(buf, xt_prefix[af], माप(buf));
	strlcat(buf, FORMAT_TABLES, माप(buf));
	proc = proc_create_net_data(buf, 0440, net->proc_net, &xt_table_seq_ops,
			माप(काष्ठा seq_net_निजी),
			(व्योम *)(अचिन्हित दीर्घ)af);
	अगर (!proc)
		जाओ out;
	अगर (uid_valid(root_uid) && gid_valid(root_gid))
		proc_set_user(proc, root_uid, root_gid);

	strlcpy(buf, xt_prefix[af], माप(buf));
	strlcat(buf, FORMAT_MATCHES, माप(buf));
	proc = proc_create_seq_निजी(buf, 0440, net->proc_net,
			&xt_match_seq_ops, माप(काष्ठा nf_mttg_trav),
			(व्योम *)(अचिन्हित दीर्घ)af);
	अगर (!proc)
		जाओ out_हटाओ_tables;
	अगर (uid_valid(root_uid) && gid_valid(root_gid))
		proc_set_user(proc, root_uid, root_gid);

	strlcpy(buf, xt_prefix[af], माप(buf));
	strlcat(buf, FORMAT_TARGETS, माप(buf));
	proc = proc_create_seq_निजी(buf, 0440, net->proc_net,
			 &xt_target_seq_ops, माप(काष्ठा nf_mttg_trav),
			 (व्योम *)(अचिन्हित दीर्घ)af);
	अगर (!proc)
		जाओ out_हटाओ_matches;
	अगर (uid_valid(root_uid) && gid_valid(root_gid))
		proc_set_user(proc, root_uid, root_gid);
#पूर्ण_अगर

	वापस 0;

#अगर_घोषित CONFIG_PROC_FS
out_हटाओ_matches:
	strlcpy(buf, xt_prefix[af], माप(buf));
	strlcat(buf, FORMAT_MATCHES, माप(buf));
	हटाओ_proc_entry(buf, net->proc_net);

out_हटाओ_tables:
	strlcpy(buf, xt_prefix[af], माप(buf));
	strlcat(buf, FORMAT_TABLES, माप(buf));
	हटाओ_proc_entry(buf, net->proc_net);
out:
	वापस -1;
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL_GPL(xt_proto_init);

व्योम xt_proto_fini(काष्ठा net *net, u_पूर्णांक8_t af)
अणु
#अगर_घोषित CONFIG_PROC_FS
	अक्षर buf[XT_FUNCTION_MAXNAMELEN];

	strlcpy(buf, xt_prefix[af], माप(buf));
	strlcat(buf, FORMAT_TABLES, माप(buf));
	हटाओ_proc_entry(buf, net->proc_net);

	strlcpy(buf, xt_prefix[af], माप(buf));
	strlcat(buf, FORMAT_TARGETS, माप(buf));
	हटाओ_proc_entry(buf, net->proc_net);

	strlcpy(buf, xt_prefix[af], माप(buf));
	strlcat(buf, FORMAT_MATCHES, माप(buf));
	हटाओ_proc_entry(buf, net->proc_net);
#पूर्ण_अगर /*CONFIG_PROC_FS*/
पूर्ण
EXPORT_SYMBOL_GPL(xt_proto_fini);

/**
 * xt_percpu_counter_alloc - allocate x_tables rule counter
 *
 * @state: poपूर्णांकer to xt_percpu allocation state
 * @counter: poपूर्णांकer to counter काष्ठा inside the ip(6)/arpt_entry काष्ठा
 *
 * On SMP, the packet counter [ ip(6)t_entry->counters.pcnt ] will then
 * contain the address of the real (percpu) counter.
 *
 * Rule evaluation needs to use xt_get_this_cpu_counter() helper
 * to fetch the real percpu counter.
 *
 * To speed up allocation and improve data locality, a 4kb block is
 * allocated.  Freeing any counter may मुक्त an entire block, so all
 * counters allocated using the same state must be मुक्तd at the same
 * समय.
 *
 * xt_percpu_counter_alloc_state contains the base address of the
 * allocated page and the current sub-offset.
 *
 * वापसs false on error.
 */
bool xt_percpu_counter_alloc(काष्ठा xt_percpu_counter_alloc_state *state,
			     काष्ठा xt_counters *counter)
अणु
	BUILD_BUG_ON(XT_PCPU_BLOCK_SIZE < (माप(*counter) * 2));

	अगर (nr_cpu_ids <= 1)
		वापस true;

	अगर (!state->mem) अणु
		state->mem = __alloc_percpu(XT_PCPU_BLOCK_SIZE,
					    XT_PCPU_BLOCK_SIZE);
		अगर (!state->mem)
			वापस false;
	पूर्ण
	counter->pcnt = (__क्रमce अचिन्हित दीर्घ)(state->mem + state->off);
	state->off += माप(*counter);
	अगर (state->off > (XT_PCPU_BLOCK_SIZE - माप(*counter))) अणु
		state->mem = शून्य;
		state->off = 0;
	पूर्ण
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(xt_percpu_counter_alloc);

व्योम xt_percpu_counter_मुक्त(काष्ठा xt_counters *counters)
अणु
	अचिन्हित दीर्घ pcnt = counters->pcnt;

	अगर (nr_cpu_ids > 1 && (pcnt & (XT_PCPU_BLOCK_SIZE - 1)) == 0)
		मुक्त_percpu((व्योम __percpu *)pcnt);
पूर्ण
EXPORT_SYMBOL_GPL(xt_percpu_counter_मुक्त);

अटल पूर्णांक __net_init xt_net_init(काष्ठा net *net)
अणु
	काष्ठा xt_pernet *xt_net = net_generic(net, xt_pernet_id);
	पूर्णांक i;

	क्रम (i = 0; i < NFPROTO_NUMPROTO; i++)
		INIT_LIST_HEAD(&xt_net->tables[i]);
	वापस 0;
पूर्ण

अटल व्योम __net_निकास xt_net_निकास(काष्ठा net *net)
अणु
	काष्ठा xt_pernet *xt_net = net_generic(net, xt_pernet_id);
	पूर्णांक i;

	क्रम (i = 0; i < NFPROTO_NUMPROTO; i++)
		WARN_ON_ONCE(!list_empty(&xt_net->tables[i]));
पूर्ण

अटल काष्ठा pernet_operations xt_net_ops = अणु
	.init = xt_net_init,
	.निकास = xt_net_निकास,
	.id   = &xt_pernet_id,
	.size = माप(काष्ठा xt_pernet),
पूर्ण;

अटल पूर्णांक __init xt_init(व्योम)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक rv;

	क्रम_each_possible_cpu(i) अणु
		seqcount_init(&per_cpu(xt_recseq, i));
	पूर्ण

	xt = kसुस्मृति(NFPROTO_NUMPROTO, माप(काष्ठा xt_af), GFP_KERNEL);
	अगर (!xt)
		वापस -ENOMEM;

	क्रम (i = 0; i < NFPROTO_NUMPROTO; i++) अणु
		mutex_init(&xt[i].mutex);
#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
		mutex_init(&xt[i].compat_mutex);
		xt[i].compat_tab = शून्य;
#पूर्ण_अगर
		INIT_LIST_HEAD(&xt[i].target);
		INIT_LIST_HEAD(&xt[i].match);
	पूर्ण
	rv = रेजिस्टर_pernet_subsys(&xt_net_ops);
	अगर (rv < 0)
		kमुक्त(xt);
	वापस rv;
पूर्ण

अटल व्योम __निकास xt_fini(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&xt_net_ops);
	kमुक्त(xt);
पूर्ण

module_init(xt_init);
module_निकास(xt_fini);

