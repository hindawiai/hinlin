<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/module.h>
#समावेश <linux/sunrpc/types.h>
#समावेश <linux/sunrpc/xdr.h>
#समावेश <linux/sunrpc/svcsock.h>
#समावेश <linux/sunrpc/svcauth.h>
#समावेश <linux/sunrpc/gss_api.h>
#समावेश <linux/sunrpc/addr.h>
#समावेश <linux/err.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/hash.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <net/sock.h>
#समावेश <net/ipv6.h>
#समावेश <linux/kernel.h>
#समावेश <linux/user_namespace.h>
#घोषणा RPCDBG_FACILITY	RPCDBG_AUTH


#समावेश "netns.h"

/*
 * AUTHUNIX and AUTHशून्य credentials are both handled here.
 * AUTHशून्य is treated just like AUTHUNIX except that the uid/gid
 * are always nobody (-2).  i.e. we करो the same IP address checks क्रम
 * AUTHशून्य as क्रम AUTHUNIX, and that is करोne here.
 */


काष्ठा unix_करोमुख्य अणु
	काष्ठा auth_करोमुख्य	h;
	/* other stuff later */
पूर्ण;

बाह्य काष्ठा auth_ops svcauth_null;
बाह्य काष्ठा auth_ops svcauth_unix;

अटल व्योम svcauth_unix_करोमुख्य_release_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा auth_करोमुख्य *करोm = container_of(head, काष्ठा auth_करोमुख्य, rcu_head);
	काष्ठा unix_करोमुख्य *ud = container_of(करोm, काष्ठा unix_करोमुख्य, h);

	kमुक्त(करोm->name);
	kमुक्त(ud);
पूर्ण

अटल व्योम svcauth_unix_करोमुख्य_release(काष्ठा auth_करोमुख्य *करोm)
अणु
	call_rcu(&करोm->rcu_head, svcauth_unix_करोमुख्य_release_rcu);
पूर्ण

काष्ठा auth_करोमुख्य *unix_करोमुख्य_find(अक्षर *name)
अणु
	काष्ठा auth_करोमुख्य *rv;
	काष्ठा unix_करोमुख्य *new = शून्य;

	rv = auth_करोमुख्य_find(name);
	जबतक(1) अणु
		अगर (rv) अणु
			अगर (new && rv != &new->h)
				svcauth_unix_करोमुख्य_release(&new->h);

			अगर (rv->flavour != &svcauth_unix) अणु
				auth_करोमुख्य_put(rv);
				वापस शून्य;
			पूर्ण
			वापस rv;
		पूर्ण

		new = kदो_स्मृति(माप(*new), GFP_KERNEL);
		अगर (new == शून्य)
			वापस शून्य;
		kref_init(&new->h.ref);
		new->h.name = kstrdup(name, GFP_KERNEL);
		अगर (new->h.name == शून्य) अणु
			kमुक्त(new);
			वापस शून्य;
		पूर्ण
		new->h.flavour = &svcauth_unix;
		rv = auth_करोमुख्य_lookup(name, &new->h);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(unix_करोमुख्य_find);


/**************************************************
 * cache क्रम IP address to unix_करोमुख्य
 * as needed by AUTH_UNIX
 */
#घोषणा	IP_HASHBITS	8
#घोषणा	IP_HASHMAX	(1<<IP_HASHBITS)

काष्ठा ip_map अणु
	काष्ठा cache_head	h;
	अक्षर			m_class[8]; /* e.g. "nfsd" */
	काष्ठा in6_addr		m_addr;
	काष्ठा unix_करोमुख्य	*m_client;
	काष्ठा rcu_head		m_rcu;
पूर्ण;

अटल व्योम ip_map_put(काष्ठा kref *kref)
अणु
	काष्ठा cache_head *item = container_of(kref, काष्ठा cache_head, ref);
	काष्ठा ip_map *im = container_of(item, काष्ठा ip_map,h);

	अगर (test_bit(CACHE_VALID, &item->flags) &&
	    !test_bit(CACHE_NEGATIVE, &item->flags))
		auth_करोमुख्य_put(&im->m_client->h);
	kमुक्त_rcu(im, m_rcu);
पूर्ण

अटल अंतरभूत पूर्णांक hash_ip6(स्थिर काष्ठा in6_addr *ip)
अणु
	वापस hash_32(ipv6_addr_hash(ip), IP_HASHBITS);
पूर्ण
अटल पूर्णांक ip_map_match(काष्ठा cache_head *corig, काष्ठा cache_head *cnew)
अणु
	काष्ठा ip_map *orig = container_of(corig, काष्ठा ip_map, h);
	काष्ठा ip_map *new = container_of(cnew, काष्ठा ip_map, h);
	वापस म_भेद(orig->m_class, new->m_class) == 0 &&
	       ipv6_addr_equal(&orig->m_addr, &new->m_addr);
पूर्ण
अटल व्योम ip_map_init(काष्ठा cache_head *cnew, काष्ठा cache_head *citem)
अणु
	काष्ठा ip_map *new = container_of(cnew, काष्ठा ip_map, h);
	काष्ठा ip_map *item = container_of(citem, काष्ठा ip_map, h);

	म_नकल(new->m_class, item->m_class);
	new->m_addr = item->m_addr;
पूर्ण
अटल व्योम update(काष्ठा cache_head *cnew, काष्ठा cache_head *citem)
अणु
	काष्ठा ip_map *new = container_of(cnew, काष्ठा ip_map, h);
	काष्ठा ip_map *item = container_of(citem, काष्ठा ip_map, h);

	kref_get(&item->m_client->h.ref);
	new->m_client = item->m_client;
पूर्ण
अटल काष्ठा cache_head *ip_map_alloc(व्योम)
अणु
	काष्ठा ip_map *i = kदो_स्मृति(माप(*i), GFP_KERNEL);
	अगर (i)
		वापस &i->h;
	अन्यथा
		वापस शून्य;
पूर्ण

अटल पूर्णांक ip_map_upcall(काष्ठा cache_detail *cd, काष्ठा cache_head *h)
अणु
	वापस sunrpc_cache_pipe_upcall(cd, h);
पूर्ण

अटल व्योम ip_map_request(काष्ठा cache_detail *cd,
				  काष्ठा cache_head *h,
				  अक्षर **bpp, पूर्णांक *blen)
अणु
	अक्षर text_addr[40];
	काष्ठा ip_map *im = container_of(h, काष्ठा ip_map, h);

	अगर (ipv6_addr_v4mapped(&(im->m_addr))) अणु
		snम_लिखो(text_addr, 20, "%pI4", &im->m_addr.s6_addr32[3]);
	पूर्ण अन्यथा अणु
		snम_लिखो(text_addr, 40, "%pI6", &im->m_addr);
	पूर्ण
	qword_add(bpp, blen, im->m_class);
	qword_add(bpp, blen, text_addr);
	(*bpp)[-1] = '\n';
पूर्ण

अटल काष्ठा ip_map *__ip_map_lookup(काष्ठा cache_detail *cd, अक्षर *class, काष्ठा in6_addr *addr);
अटल पूर्णांक __ip_map_update(काष्ठा cache_detail *cd, काष्ठा ip_map *ipm, काष्ठा unix_करोमुख्य *uकरोm, समय64_t expiry);

अटल पूर्णांक ip_map_parse(काष्ठा cache_detail *cd,
			  अक्षर *mesg, पूर्णांक mlen)
अणु
	/* class ipaddress [करोमुख्यname] */
	/* should be safe just to use the start of the input buffer
	 * क्रम scratch: */
	अक्षर *buf = mesg;
	पूर्णांक len;
	अक्षर class[8];
	जोड़ अणु
		काष्ठा sockaddr		sa;
		काष्ठा sockaddr_in	s4;
		काष्ठा sockaddr_in6	s6;
	पूर्ण address;
	काष्ठा sockaddr_in6 sin6;
	पूर्णांक err;

	काष्ठा ip_map *ipmp;
	काष्ठा auth_करोमुख्य *करोm;
	समय64_t expiry;

	अगर (mesg[mlen-1] != '\n')
		वापस -EINVAL;
	mesg[mlen-1] = 0;

	/* class */
	len = qword_get(&mesg, class, माप(class));
	अगर (len <= 0) वापस -EINVAL;

	/* ip address */
	len = qword_get(&mesg, buf, mlen);
	अगर (len <= 0) वापस -EINVAL;

	अगर (rpc_pton(cd->net, buf, len, &address.sa, माप(address)) == 0)
		वापस -EINVAL;
	चयन (address.sa.sa_family) अणु
	हाल AF_INET:
		/* Form a mapped IPv4 address in sin6 */
		sin6.sin6_family = AF_INET6;
		ipv6_addr_set_v4mapped(address.s4.sin_addr.s_addr,
				&sin6.sin6_addr);
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6:
		स_नकल(&sin6, &address.s6, माप(sin6));
		अवरोध;
#पूर्ण_अगर
	शेष:
		वापस -EINVAL;
	पूर्ण

	expiry = get_expiry(&mesg);
	अगर (expiry ==0)
		वापस -EINVAL;

	/* करोमुख्यname, or empty क्रम NEGATIVE */
	len = qword_get(&mesg, buf, mlen);
	अगर (len < 0) वापस -EINVAL;

	अगर (len) अणु
		करोm = unix_करोमुख्य_find(buf);
		अगर (करोm == शून्य)
			वापस -ENOENT;
	पूर्ण अन्यथा
		करोm = शून्य;

	/* IPv6 scope IDs are ignored क्रम now */
	ipmp = __ip_map_lookup(cd, class, &sin6.sin6_addr);
	अगर (ipmp) अणु
		err = __ip_map_update(cd, ipmp,
			     container_of(करोm, काष्ठा unix_करोमुख्य, h),
			     expiry);
	पूर्ण अन्यथा
		err = -ENOMEM;

	अगर (करोm)
		auth_करोमुख्य_put(करोm);

	cache_flush();
	वापस err;
पूर्ण

अटल पूर्णांक ip_map_show(काष्ठा seq_file *m,
		       काष्ठा cache_detail *cd,
		       काष्ठा cache_head *h)
अणु
	काष्ठा ip_map *im;
	काष्ठा in6_addr addr;
	अक्षर *करोm = "-no-domain-";

	अगर (h == शून्य) अणु
		seq_माला_दो(m, "#class IP domain\n");
		वापस 0;
	पूर्ण
	im = container_of(h, काष्ठा ip_map, h);
	/* class addr करोमुख्य */
	addr = im->m_addr;

	अगर (test_bit(CACHE_VALID, &h->flags) &&
	    !test_bit(CACHE_NEGATIVE, &h->flags))
		करोm = im->m_client->h.name;

	अगर (ipv6_addr_v4mapped(&addr)) अणु
		seq_म_लिखो(m, "%s %pI4 %s\n",
			im->m_class, &addr.s6_addr32[3], करोm);
	पूर्ण अन्यथा अणु
		seq_म_लिखो(m, "%s %pI6 %s\n", im->m_class, &addr, करोm);
	पूर्ण
	वापस 0;
पूर्ण


अटल काष्ठा ip_map *__ip_map_lookup(काष्ठा cache_detail *cd, अक्षर *class,
		काष्ठा in6_addr *addr)
अणु
	काष्ठा ip_map ip;
	काष्ठा cache_head *ch;

	म_नकल(ip.m_class, class);
	ip.m_addr = *addr;
	ch = sunrpc_cache_lookup_rcu(cd, &ip.h,
				     hash_str(class, IP_HASHBITS) ^
				     hash_ip6(addr));

	अगर (ch)
		वापस container_of(ch, काष्ठा ip_map, h);
	अन्यथा
		वापस शून्य;
पूर्ण

अटल पूर्णांक __ip_map_update(काष्ठा cache_detail *cd, काष्ठा ip_map *ipm,
		काष्ठा unix_करोमुख्य *uकरोm, समय64_t expiry)
अणु
	काष्ठा ip_map ip;
	काष्ठा cache_head *ch;

	ip.m_client = uकरोm;
	ip.h.flags = 0;
	अगर (!uकरोm)
		set_bit(CACHE_NEGATIVE, &ip.h.flags);
	ip.h.expiry_समय = expiry;
	ch = sunrpc_cache_update(cd, &ip.h, &ipm->h,
				 hash_str(ipm->m_class, IP_HASHBITS) ^
				 hash_ip6(&ipm->m_addr));
	अगर (!ch)
		वापस -ENOMEM;
	cache_put(ch, cd);
	वापस 0;
पूर्ण

व्योम svcauth_unix_purge(काष्ठा net *net)
अणु
	काष्ठा sunrpc_net *sn;

	sn = net_generic(net, sunrpc_net_id);
	cache_purge(sn->ip_map_cache);
पूर्ण
EXPORT_SYMBOL_GPL(svcauth_unix_purge);

अटल अंतरभूत काष्ठा ip_map *
ip_map_cached_get(काष्ठा svc_xprt *xprt)
अणु
	काष्ठा ip_map *ipm = शून्य;
	काष्ठा sunrpc_net *sn;

	अगर (test_bit(XPT_CACHE_AUTH, &xprt->xpt_flags)) अणु
		spin_lock(&xprt->xpt_lock);
		ipm = xprt->xpt_auth_cache;
		अगर (ipm != शून्य) अणु
			sn = net_generic(xprt->xpt_net, sunrpc_net_id);
			अगर (cache_is_expired(sn->ip_map_cache, &ipm->h)) अणु
				/*
				 * The entry has been invalidated since it was
				 * remembered, e.g. by a second mount from the
				 * same IP address.
				 */
				xprt->xpt_auth_cache = शून्य;
				spin_unlock(&xprt->xpt_lock);
				cache_put(&ipm->h, sn->ip_map_cache);
				वापस शून्य;
			पूर्ण
			cache_get(&ipm->h);
		पूर्ण
		spin_unlock(&xprt->xpt_lock);
	पूर्ण
	वापस ipm;
पूर्ण

अटल अंतरभूत व्योम
ip_map_cached_put(काष्ठा svc_xprt *xprt, काष्ठा ip_map *ipm)
अणु
	अगर (test_bit(XPT_CACHE_AUTH, &xprt->xpt_flags)) अणु
		spin_lock(&xprt->xpt_lock);
		अगर (xprt->xpt_auth_cache == शून्य) अणु
			/* newly cached, keep the reference */
			xprt->xpt_auth_cache = ipm;
			ipm = शून्य;
		पूर्ण
		spin_unlock(&xprt->xpt_lock);
	पूर्ण
	अगर (ipm) अणु
		काष्ठा sunrpc_net *sn;

		sn = net_generic(xprt->xpt_net, sunrpc_net_id);
		cache_put(&ipm->h, sn->ip_map_cache);
	पूर्ण
पूर्ण

व्योम
svcauth_unix_info_release(काष्ठा svc_xprt *xpt)
अणु
	काष्ठा ip_map *ipm;

	ipm = xpt->xpt_auth_cache;
	अगर (ipm != शून्य) अणु
		काष्ठा sunrpc_net *sn;

		sn = net_generic(xpt->xpt_net, sunrpc_net_id);
		cache_put(&ipm->h, sn->ip_map_cache);
	पूर्ण
पूर्ण

/****************************************************************************
 * auth.unix.gid cache
 * simple cache to map a UID to a list of GIDs
 * because AUTH_UNIX aka AUTH_SYS has a max of UNX_NGROUPS
 */
#घोषणा	GID_HASHBITS	8
#घोषणा	GID_HASHMAX	(1<<GID_HASHBITS)

काष्ठा unix_gid अणु
	काष्ठा cache_head	h;
	kuid_t			uid;
	काष्ठा group_info	*gi;
	काष्ठा rcu_head		rcu;
पूर्ण;

अटल पूर्णांक unix_gid_hash(kuid_t uid)
अणु
	वापस hash_दीर्घ(from_kuid(&init_user_ns, uid), GID_HASHBITS);
पूर्ण

अटल व्योम unix_gid_put(काष्ठा kref *kref)
अणु
	काष्ठा cache_head *item = container_of(kref, काष्ठा cache_head, ref);
	काष्ठा unix_gid *ug = container_of(item, काष्ठा unix_gid, h);
	अगर (test_bit(CACHE_VALID, &item->flags) &&
	    !test_bit(CACHE_NEGATIVE, &item->flags))
		put_group_info(ug->gi);
	kमुक्त_rcu(ug, rcu);
पूर्ण

अटल पूर्णांक unix_gid_match(काष्ठा cache_head *corig, काष्ठा cache_head *cnew)
अणु
	काष्ठा unix_gid *orig = container_of(corig, काष्ठा unix_gid, h);
	काष्ठा unix_gid *new = container_of(cnew, काष्ठा unix_gid, h);
	वापस uid_eq(orig->uid, new->uid);
पूर्ण
अटल व्योम unix_gid_init(काष्ठा cache_head *cnew, काष्ठा cache_head *citem)
अणु
	काष्ठा unix_gid *new = container_of(cnew, काष्ठा unix_gid, h);
	काष्ठा unix_gid *item = container_of(citem, काष्ठा unix_gid, h);
	new->uid = item->uid;
पूर्ण
अटल व्योम unix_gid_update(काष्ठा cache_head *cnew, काष्ठा cache_head *citem)
अणु
	काष्ठा unix_gid *new = container_of(cnew, काष्ठा unix_gid, h);
	काष्ठा unix_gid *item = container_of(citem, काष्ठा unix_gid, h);

	get_group_info(item->gi);
	new->gi = item->gi;
पूर्ण
अटल काष्ठा cache_head *unix_gid_alloc(व्योम)
अणु
	काष्ठा unix_gid *g = kदो_स्मृति(माप(*g), GFP_KERNEL);
	अगर (g)
		वापस &g->h;
	अन्यथा
		वापस शून्य;
पूर्ण

अटल पूर्णांक unix_gid_upcall(काष्ठा cache_detail *cd, काष्ठा cache_head *h)
अणु
	वापस sunrpc_cache_pipe_upcall_समयout(cd, h);
पूर्ण

अटल व्योम unix_gid_request(काष्ठा cache_detail *cd,
			     काष्ठा cache_head *h,
			     अक्षर **bpp, पूर्णांक *blen)
अणु
	अक्षर tuid[20];
	काष्ठा unix_gid *ug = container_of(h, काष्ठा unix_gid, h);

	snम_लिखो(tuid, 20, "%u", from_kuid(&init_user_ns, ug->uid));
	qword_add(bpp, blen, tuid);
	(*bpp)[-1] = '\n';
पूर्ण

अटल काष्ठा unix_gid *unix_gid_lookup(काष्ठा cache_detail *cd, kuid_t uid);

अटल पूर्णांक unix_gid_parse(काष्ठा cache_detail *cd,
			अक्षर *mesg, पूर्णांक mlen)
अणु
	/* uid expiry Ngid gid0 gid1 ... gidN-1 */
	पूर्णांक id;
	kuid_t uid;
	पूर्णांक gids;
	पूर्णांक rv;
	पूर्णांक i;
	पूर्णांक err;
	समय64_t expiry;
	काष्ठा unix_gid ug, *ugp;

	अगर (mesg[mlen - 1] != '\n')
		वापस -EINVAL;
	mesg[mlen-1] = 0;

	rv = get_पूर्णांक(&mesg, &id);
	अगर (rv)
		वापस -EINVAL;
	uid = make_kuid(current_user_ns(), id);
	ug.uid = uid;

	expiry = get_expiry(&mesg);
	अगर (expiry == 0)
		वापस -EINVAL;

	rv = get_पूर्णांक(&mesg, &gids);
	अगर (rv || gids < 0 || gids > 8192)
		वापस -EINVAL;

	ug.gi = groups_alloc(gids);
	अगर (!ug.gi)
		वापस -ENOMEM;

	क्रम (i = 0 ; i < gids ; i++) अणु
		पूर्णांक gid;
		kgid_t kgid;
		rv = get_पूर्णांक(&mesg, &gid);
		err = -EINVAL;
		अगर (rv)
			जाओ out;
		kgid = make_kgid(current_user_ns(), gid);
		अगर (!gid_valid(kgid))
			जाओ out;
		ug.gi->gid[i] = kgid;
	पूर्ण

	groups_sort(ug.gi);
	ugp = unix_gid_lookup(cd, uid);
	अगर (ugp) अणु
		काष्ठा cache_head *ch;
		ug.h.flags = 0;
		ug.h.expiry_समय = expiry;
		ch = sunrpc_cache_update(cd,
					 &ug.h, &ugp->h,
					 unix_gid_hash(uid));
		अगर (!ch)
			err = -ENOMEM;
		अन्यथा अणु
			err = 0;
			cache_put(ch, cd);
		पूर्ण
	पूर्ण अन्यथा
		err = -ENOMEM;
 out:
	अगर (ug.gi)
		put_group_info(ug.gi);
	वापस err;
पूर्ण

अटल पूर्णांक unix_gid_show(काष्ठा seq_file *m,
			 काष्ठा cache_detail *cd,
			 काष्ठा cache_head *h)
अणु
	काष्ठा user_namespace *user_ns = m->file->f_cred->user_ns;
	काष्ठा unix_gid *ug;
	पूर्णांक i;
	पूर्णांक glen;

	अगर (h == शून्य) अणु
		seq_माला_दो(m, "#uid cnt: gids...\n");
		वापस 0;
	पूर्ण
	ug = container_of(h, काष्ठा unix_gid, h);
	अगर (test_bit(CACHE_VALID, &h->flags) &&
	    !test_bit(CACHE_NEGATIVE, &h->flags))
		glen = ug->gi->ngroups;
	अन्यथा
		glen = 0;

	seq_म_लिखो(m, "%u %d:", from_kuid_munged(user_ns, ug->uid), glen);
	क्रम (i = 0; i < glen; i++)
		seq_म_लिखो(m, " %d", from_kgid_munged(user_ns, ug->gi->gid[i]));
	seq_म_लिखो(m, "\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cache_detail unix_gid_cache_ढाँचा = अणु
	.owner		= THIS_MODULE,
	.hash_size	= GID_HASHMAX,
	.name		= "auth.unix.gid",
	.cache_put	= unix_gid_put,
	.cache_upcall	= unix_gid_upcall,
	.cache_request	= unix_gid_request,
	.cache_parse	= unix_gid_parse,
	.cache_show	= unix_gid_show,
	.match		= unix_gid_match,
	.init		= unix_gid_init,
	.update		= unix_gid_update,
	.alloc		= unix_gid_alloc,
पूर्ण;

पूर्णांक unix_gid_cache_create(काष्ठा net *net)
अणु
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);
	काष्ठा cache_detail *cd;
	पूर्णांक err;

	cd = cache_create_net(&unix_gid_cache_ढाँचा, net);
	अगर (IS_ERR(cd))
		वापस PTR_ERR(cd);
	err = cache_रेजिस्टर_net(cd, net);
	अगर (err) अणु
		cache_destroy_net(cd, net);
		वापस err;
	पूर्ण
	sn->unix_gid_cache = cd;
	वापस 0;
पूर्ण

व्योम unix_gid_cache_destroy(काष्ठा net *net)
अणु
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);
	काष्ठा cache_detail *cd = sn->unix_gid_cache;

	sn->unix_gid_cache = शून्य;
	cache_purge(cd);
	cache_unरेजिस्टर_net(cd, net);
	cache_destroy_net(cd, net);
पूर्ण

अटल काष्ठा unix_gid *unix_gid_lookup(काष्ठा cache_detail *cd, kuid_t uid)
अणु
	काष्ठा unix_gid ug;
	काष्ठा cache_head *ch;

	ug.uid = uid;
	ch = sunrpc_cache_lookup_rcu(cd, &ug.h, unix_gid_hash(uid));
	अगर (ch)
		वापस container_of(ch, काष्ठा unix_gid, h);
	अन्यथा
		वापस शून्य;
पूर्ण

अटल काष्ठा group_info *unix_gid_find(kuid_t uid, काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा unix_gid *ug;
	काष्ठा group_info *gi;
	पूर्णांक ret;
	काष्ठा sunrpc_net *sn = net_generic(rqstp->rq_xprt->xpt_net,
					    sunrpc_net_id);

	ug = unix_gid_lookup(sn->unix_gid_cache, uid);
	अगर (!ug)
		वापस ERR_PTR(-EAGAIN);
	ret = cache_check(sn->unix_gid_cache, &ug->h, &rqstp->rq_chandle);
	चयन (ret) अणु
	हाल -ENOENT:
		वापस ERR_PTR(-ENOENT);
	हाल -ETIMEDOUT:
		वापस ERR_PTR(-ESHUTDOWN);
	हाल 0:
		gi = get_group_info(ug->gi);
		cache_put(&ug->h, sn->unix_gid_cache);
		वापस gi;
	शेष:
		वापस ERR_PTR(-EAGAIN);
	पूर्ण
पूर्ण

पूर्णांक
svcauth_unix_set_client(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा sockaddr_in *sin;
	काष्ठा sockaddr_in6 *sin6, sin6_storage;
	काष्ठा ip_map *ipm;
	काष्ठा group_info *gi;
	काष्ठा svc_cred *cred = &rqstp->rq_cred;
	काष्ठा svc_xprt *xprt = rqstp->rq_xprt;
	काष्ठा net *net = xprt->xpt_net;
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);

	चयन (rqstp->rq_addr.ss_family) अणु
	हाल AF_INET:
		sin = svc_addr_in(rqstp);
		sin6 = &sin6_storage;
		ipv6_addr_set_v4mapped(sin->sin_addr.s_addr, &sin6->sin6_addr);
		अवरोध;
	हाल AF_INET6:
		sin6 = svc_addr_in6(rqstp);
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	rqstp->rq_client = शून्य;
	अगर (rqstp->rq_proc == 0)
		वापस SVC_OK;

	ipm = ip_map_cached_get(xprt);
	अगर (ipm == शून्य)
		ipm = __ip_map_lookup(sn->ip_map_cache, rqstp->rq_server->sv_program->pg_class,
				    &sin6->sin6_addr);

	अगर (ipm == शून्य)
		वापस SVC_DENIED;

	चयन (cache_check(sn->ip_map_cache, &ipm->h, &rqstp->rq_chandle)) अणु
		शेष:
			BUG();
		हाल -ETIMEDOUT:
			वापस SVC_CLOSE;
		हाल -EAGAIN:
			वापस SVC_DROP;
		हाल -ENOENT:
			वापस SVC_DENIED;
		हाल 0:
			rqstp->rq_client = &ipm->m_client->h;
			kref_get(&rqstp->rq_client->ref);
			ip_map_cached_put(xprt, ipm);
			अवरोध;
	पूर्ण

	gi = unix_gid_find(cred->cr_uid, rqstp);
	चयन (PTR_ERR(gi)) अणु
	हाल -EAGAIN:
		वापस SVC_DROP;
	हाल -ESHUTDOWN:
		वापस SVC_CLOSE;
	हाल -ENOENT:
		अवरोध;
	शेष:
		put_group_info(cred->cr_group_info);
		cred->cr_group_info = gi;
	पूर्ण
	वापस SVC_OK;
पूर्ण

EXPORT_SYMBOL_GPL(svcauth_unix_set_client);

अटल पूर्णांक
svcauth_null_accept(काष्ठा svc_rqst *rqstp, __be32 *authp)
अणु
	काष्ठा kvec	*argv = &rqstp->rq_arg.head[0];
	काष्ठा kvec	*resv = &rqstp->rq_res.head[0];
	काष्ठा svc_cred	*cred = &rqstp->rq_cred;

	अगर (argv->iov_len < 3*4)
		वापस SVC_GARBAGE;

	अगर (svc_getu32(argv) != 0) अणु
		dprपूर्णांकk("svc: bad null cred\n");
		*authp = rpc_autherr_badcred;
		वापस SVC_DENIED;
	पूर्ण
	अगर (svc_getu32(argv) != htonl(RPC_AUTH_शून्य) || svc_getu32(argv) != 0) अणु
		dprपूर्णांकk("svc: bad null verf\n");
		*authp = rpc_autherr_badverf;
		वापस SVC_DENIED;
	पूर्ण

	/* Signal that mapping to nobody uid/gid is required */
	cred->cr_uid = INVALID_UID;
	cred->cr_gid = INVALID_GID;
	cred->cr_group_info = groups_alloc(0);
	अगर (cred->cr_group_info == शून्य)
		वापस SVC_CLOSE; /* kदो_स्मृति failure - client must retry */

	/* Put शून्य verअगरier */
	svc_putnl(resv, RPC_AUTH_शून्य);
	svc_putnl(resv, 0);

	rqstp->rq_cred.cr_flavor = RPC_AUTH_शून्य;
	वापस SVC_OK;
पूर्ण

अटल पूर्णांक
svcauth_null_release(काष्ठा svc_rqst *rqstp)
अणु
	अगर (rqstp->rq_client)
		auth_करोमुख्य_put(rqstp->rq_client);
	rqstp->rq_client = शून्य;
	अगर (rqstp->rq_cred.cr_group_info)
		put_group_info(rqstp->rq_cred.cr_group_info);
	rqstp->rq_cred.cr_group_info = शून्य;

	वापस 0; /* करोn't drop */
पूर्ण


काष्ठा auth_ops svcauth_null = अणु
	.name		= "null",
	.owner		= THIS_MODULE,
	.flavour	= RPC_AUTH_शून्य,
	.accept 	= svcauth_null_accept,
	.release	= svcauth_null_release,
	.set_client	= svcauth_unix_set_client,
पूर्ण;


अटल पूर्णांक
svcauth_unix_accept(काष्ठा svc_rqst *rqstp, __be32 *authp)
अणु
	काष्ठा kvec	*argv = &rqstp->rq_arg.head[0];
	काष्ठा kvec	*resv = &rqstp->rq_res.head[0];
	काष्ठा svc_cred	*cred = &rqstp->rq_cred;
	काष्ठा user_namespace *userns;
	u32		slen, i;
	पूर्णांक		len   = argv->iov_len;

	अगर ((len -= 3*4) < 0)
		वापस SVC_GARBAGE;

	svc_getu32(argv);			/* length */
	svc_getu32(argv);			/* समय stamp */
	slen = XDR_QUADLEN(svc_getnl(argv));	/* machname length */
	अगर (slen > 64 || (len -= (slen + 3)*4) < 0)
		जाओ badcred;
	argv->iov_base = (व्योम*)((__be32*)argv->iov_base + slen);	/* skip machname */
	argv->iov_len -= slen*4;
	/*
	 * Note: we skip uid_valid()/gid_valid() checks here क्रम
	 * backwards compatibility with clients that use -1 id's.
	 * Instead, -1 uid or gid is later mapped to the
	 * (export-specअगरic) anonymous id by nfsd_setuser.
	 * Supplementary gid's will be left alone.
	 */
	userns = (rqstp->rq_xprt && rqstp->rq_xprt->xpt_cred) ?
		rqstp->rq_xprt->xpt_cred->user_ns : &init_user_ns;
	cred->cr_uid = make_kuid(userns, svc_getnl(argv)); /* uid */
	cred->cr_gid = make_kgid(userns, svc_getnl(argv)); /* gid */
	slen = svc_getnl(argv);			/* gids length */
	अगर (slen > UNX_NGROUPS || (len -= (slen + 2)*4) < 0)
		जाओ badcred;
	cred->cr_group_info = groups_alloc(slen);
	अगर (cred->cr_group_info == शून्य)
		वापस SVC_CLOSE;
	क्रम (i = 0; i < slen; i++) अणु
		kgid_t kgid = make_kgid(userns, svc_getnl(argv));
		cred->cr_group_info->gid[i] = kgid;
	पूर्ण
	groups_sort(cred->cr_group_info);
	अगर (svc_getu32(argv) != htonl(RPC_AUTH_शून्य) || svc_getu32(argv) != 0) अणु
		*authp = rpc_autherr_badverf;
		वापस SVC_DENIED;
	पूर्ण

	/* Put शून्य verअगरier */
	svc_putnl(resv, RPC_AUTH_शून्य);
	svc_putnl(resv, 0);

	rqstp->rq_cred.cr_flavor = RPC_AUTH_UNIX;
	वापस SVC_OK;

badcred:
	*authp = rpc_autherr_badcred;
	वापस SVC_DENIED;
पूर्ण

अटल पूर्णांक
svcauth_unix_release(काष्ठा svc_rqst *rqstp)
अणु
	/* Verअगरier (such as it is) is alपढ़ोy in place.
	 */
	अगर (rqstp->rq_client)
		auth_करोमुख्य_put(rqstp->rq_client);
	rqstp->rq_client = शून्य;
	अगर (rqstp->rq_cred.cr_group_info)
		put_group_info(rqstp->rq_cred.cr_group_info);
	rqstp->rq_cred.cr_group_info = शून्य;

	वापस 0;
पूर्ण


काष्ठा auth_ops svcauth_unix = अणु
	.name		= "unix",
	.owner		= THIS_MODULE,
	.flavour	= RPC_AUTH_UNIX,
	.accept 	= svcauth_unix_accept,
	.release	= svcauth_unix_release,
	.करोमुख्य_release	= svcauth_unix_करोमुख्य_release,
	.set_client	= svcauth_unix_set_client,
पूर्ण;

अटल स्थिर काष्ठा cache_detail ip_map_cache_ढाँचा = अणु
	.owner		= THIS_MODULE,
	.hash_size	= IP_HASHMAX,
	.name		= "auth.unix.ip",
	.cache_put	= ip_map_put,
	.cache_upcall	= ip_map_upcall,
	.cache_request	= ip_map_request,
	.cache_parse	= ip_map_parse,
	.cache_show	= ip_map_show,
	.match		= ip_map_match,
	.init		= ip_map_init,
	.update		= update,
	.alloc		= ip_map_alloc,
पूर्ण;

पूर्णांक ip_map_cache_create(काष्ठा net *net)
अणु
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);
	काष्ठा cache_detail *cd;
	पूर्णांक err;

	cd = cache_create_net(&ip_map_cache_ढाँचा, net);
	अगर (IS_ERR(cd))
		वापस PTR_ERR(cd);
	err = cache_रेजिस्टर_net(cd, net);
	अगर (err) अणु
		cache_destroy_net(cd, net);
		वापस err;
	पूर्ण
	sn->ip_map_cache = cd;
	वापस 0;
पूर्ण

व्योम ip_map_cache_destroy(काष्ठा net *net)
अणु
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);
	काष्ठा cache_detail *cd = sn->ip_map_cache;

	sn->ip_map_cache = शून्य;
	cache_purge(cd);
	cache_unरेजिस्टर_net(cd, net);
	cache_destroy_net(cd, net);
पूर्ण
