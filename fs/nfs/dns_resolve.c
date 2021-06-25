<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/nfs/dns_resolve.c
 *
 * Copyright (c) 2009 Trond Myklebust <Trond.Myklebust@netapp.com>
 *
 * Resolves DNS hostnames पूर्णांकo valid ip addresses
 */

#अगर_घोषित CONFIG_NFS_USE_KERNEL_DNS

#समावेश <linux/module.h>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/sunrpc/addr.h>
#समावेश <linux/dns_resolver.h>
#समावेश "dns_resolve.h"

sमाप_प्रकार nfs_dns_resolve_name(काष्ठा net *net, अक्षर *name, माप_प्रकार namelen,
		काष्ठा sockaddr *sa, माप_प्रकार salen)
अणु
	sमाप_प्रकार ret;
	अक्षर *ip_addr = शून्य;
	पूर्णांक ip_len;

	ip_len = dns_query(net, शून्य, name, namelen, शून्य, &ip_addr, शून्य,
			   false);
	अगर (ip_len > 0)
		ret = rpc_pton(net, ip_addr, ip_len, sa, salen);
	अन्यथा
		ret = -ESRCH;
	kमुक्त(ip_addr);
	वापस ret;
पूर्ण

#अन्यथा

#समावेश <linux/module.h>
#समावेश <linux/hash.h>
#समावेश <linux/माला.स>
#समावेश <linux/kmod.h>
#समावेश <linux/slab.h>
#समावेश <linux/socket.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/inet.h>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/sunrpc/addr.h>
#समावेश <linux/sunrpc/cache.h>
#समावेश <linux/sunrpc/svcauth.h>
#समावेश <linux/sunrpc/rpc_pipe_fs.h>
#समावेश <linux/nfs_fs.h>

#समावेश "nfs4_fs.h"
#समावेश "dns_resolve.h"
#समावेश "cache_lib.h"
#समावेश "netns.h"

#घोषणा NFS_DNS_HASHBITS 4
#घोषणा NFS_DNS_HASHTBL_SIZE (1 << NFS_DNS_HASHBITS)

काष्ठा nfs_dns_ent अणु
	काष्ठा cache_head h;

	अक्षर *hostname;
	माप_प्रकार namelen;

	काष्ठा sockaddr_storage addr;
	माप_प्रकार addrlen;
	काष्ठा rcu_head rcu_head;
पूर्ण;


अटल व्योम nfs_dns_ent_update(काष्ठा cache_head *cnew,
		काष्ठा cache_head *ckey)
अणु
	काष्ठा nfs_dns_ent *new;
	काष्ठा nfs_dns_ent *key;

	new = container_of(cnew, काष्ठा nfs_dns_ent, h);
	key = container_of(ckey, काष्ठा nfs_dns_ent, h);

	स_नकल(&new->addr, &key->addr, key->addrlen);
	new->addrlen = key->addrlen;
पूर्ण

अटल व्योम nfs_dns_ent_init(काष्ठा cache_head *cnew,
		काष्ठा cache_head *ckey)
अणु
	काष्ठा nfs_dns_ent *new;
	काष्ठा nfs_dns_ent *key;

	new = container_of(cnew, काष्ठा nfs_dns_ent, h);
	key = container_of(ckey, काष्ठा nfs_dns_ent, h);

	kमुक्त(new->hostname);
	new->hostname = kmemdup_nul(key->hostname, key->namelen, GFP_KERNEL);
	अगर (new->hostname) अणु
		new->namelen = key->namelen;
		nfs_dns_ent_update(cnew, ckey);
	पूर्ण अन्यथा अणु
		new->namelen = 0;
		new->addrlen = 0;
	पूर्ण
पूर्ण

अटल व्योम nfs_dns_ent_मुक्त_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा nfs_dns_ent *item;

	item = container_of(head, काष्ठा nfs_dns_ent, rcu_head);
	kमुक्त(item->hostname);
	kमुक्त(item);
पूर्ण

अटल व्योम nfs_dns_ent_put(काष्ठा kref *ref)
अणु
	काष्ठा nfs_dns_ent *item;

	item = container_of(ref, काष्ठा nfs_dns_ent, h.ref);
	call_rcu(&item->rcu_head, nfs_dns_ent_मुक्त_rcu);
पूर्ण

अटल काष्ठा cache_head *nfs_dns_ent_alloc(व्योम)
अणु
	काष्ठा nfs_dns_ent *item = kदो_स्मृति(माप(*item), GFP_KERNEL);

	अगर (item != शून्य) अणु
		item->hostname = शून्य;
		item->namelen = 0;
		item->addrlen = 0;
		वापस &item->h;
	पूर्ण
	वापस शून्य;
पूर्ण;

अटल अचिन्हित पूर्णांक nfs_dns_hash(स्थिर काष्ठा nfs_dns_ent *key)
अणु
	वापस hash_str(key->hostname, NFS_DNS_HASHBITS);
पूर्ण

अटल व्योम nfs_dns_request(काष्ठा cache_detail *cd,
		काष्ठा cache_head *ch,
		अक्षर **bpp, पूर्णांक *blen)
अणु
	काष्ठा nfs_dns_ent *key = container_of(ch, काष्ठा nfs_dns_ent, h);

	qword_add(bpp, blen, key->hostname);
	(*bpp)[-1] = '\n';
पूर्ण

अटल पूर्णांक nfs_dns_upcall(काष्ठा cache_detail *cd,
		काष्ठा cache_head *ch)
अणु
	काष्ठा nfs_dns_ent *key = container_of(ch, काष्ठा nfs_dns_ent, h);

	अगर (test_and_set_bit(CACHE_PENDING, &ch->flags))
		वापस 0;
	अगर (!nfs_cache_upcall(cd, key->hostname))
		वापस 0;
	clear_bit(CACHE_PENDING, &ch->flags);
	वापस sunrpc_cache_pipe_upcall_समयout(cd, ch);
पूर्ण

अटल पूर्णांक nfs_dns_match(काष्ठा cache_head *ca,
		काष्ठा cache_head *cb)
अणु
	काष्ठा nfs_dns_ent *a;
	काष्ठा nfs_dns_ent *b;

	a = container_of(ca, काष्ठा nfs_dns_ent, h);
	b = container_of(cb, काष्ठा nfs_dns_ent, h);

	अगर (a->namelen == 0 || a->namelen != b->namelen)
		वापस 0;
	वापस स_भेद(a->hostname, b->hostname, a->namelen) == 0;
पूर्ण

अटल पूर्णांक nfs_dns_show(काष्ठा seq_file *m, काष्ठा cache_detail *cd,
		काष्ठा cache_head *h)
अणु
	काष्ठा nfs_dns_ent *item;
	दीर्घ ttl;

	अगर (h == शून्य) अणु
		seq_माला_दो(m, "# ip address      hostname        ttl\n");
		वापस 0;
	पूर्ण
	item = container_of(h, काष्ठा nfs_dns_ent, h);
	ttl = item->h.expiry_समय - seconds_since_boot();
	अगर (ttl < 0)
		ttl = 0;

	अगर (!test_bit(CACHE_NEGATIVE, &h->flags)) अणु
		अक्षर buf[INET6_ADDRSTRLEN+IPV6_SCOPE_ID_LEN+1];

		rpc_ntop((काष्ठा sockaddr *)&item->addr, buf, माप(buf));
		seq_म_लिखो(m, "%15s ", buf);
	पूर्ण अन्यथा
		seq_माला_दो(m, "<none>          ");
	seq_म_लिखो(m, "%15s %ld\n", item->hostname, ttl);
	वापस 0;
पूर्ण

अटल काष्ठा nfs_dns_ent *nfs_dns_lookup(काष्ठा cache_detail *cd,
		काष्ठा nfs_dns_ent *key)
अणु
	काष्ठा cache_head *ch;

	ch = sunrpc_cache_lookup_rcu(cd,
			&key->h,
			nfs_dns_hash(key));
	अगर (!ch)
		वापस शून्य;
	वापस container_of(ch, काष्ठा nfs_dns_ent, h);
पूर्ण

अटल काष्ठा nfs_dns_ent *nfs_dns_update(काष्ठा cache_detail *cd,
		काष्ठा nfs_dns_ent *new,
		काष्ठा nfs_dns_ent *key)
अणु
	काष्ठा cache_head *ch;

	ch = sunrpc_cache_update(cd,
			&new->h, &key->h,
			nfs_dns_hash(key));
	अगर (!ch)
		वापस शून्य;
	वापस container_of(ch, काष्ठा nfs_dns_ent, h);
पूर्ण

अटल पूर्णांक nfs_dns_parse(काष्ठा cache_detail *cd, अक्षर *buf, पूर्णांक buflen)
अणु
	अक्षर buf1[NFS_DNS_HOSTNAME_MAXLEN+1];
	काष्ठा nfs_dns_ent key, *item;
	अचिन्हित पूर्णांक ttl;
	sमाप_प्रकार len;
	पूर्णांक ret = -EINVAL;

	अगर (buf[buflen-1] != '\n')
		जाओ out;
	buf[buflen-1] = '\0';

	len = qword_get(&buf, buf1, माप(buf1));
	अगर (len <= 0)
		जाओ out;
	key.addrlen = rpc_pton(cd->net, buf1, len,
			(काष्ठा sockaddr *)&key.addr,
			माप(key.addr));

	len = qword_get(&buf, buf1, माप(buf1));
	अगर (len <= 0)
		जाओ out;

	key.hostname = buf1;
	key.namelen = len;
	स_रखो(&key.h, 0, माप(key.h));

	अगर (get_uपूर्णांक(&buf, &ttl) < 0)
		जाओ out;
	अगर (ttl == 0)
		जाओ out;
	key.h.expiry_समय = ttl + seconds_since_boot();

	ret = -ENOMEM;
	item = nfs_dns_lookup(cd, &key);
	अगर (item == शून्य)
		जाओ out;

	अगर (key.addrlen == 0)
		set_bit(CACHE_NEGATIVE, &key.h.flags);

	item = nfs_dns_update(cd, &key, item);
	अगर (item == शून्य)
		जाओ out;

	ret = 0;
	cache_put(&item->h, cd);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक करो_cache_lookup(काष्ठा cache_detail *cd,
		काष्ठा nfs_dns_ent *key,
		काष्ठा nfs_dns_ent **item,
		काष्ठा nfs_cache_defer_req *dreq)
अणु
	पूर्णांक ret = -ENOMEM;

	*item = nfs_dns_lookup(cd, key);
	अगर (*item) अणु
		ret = cache_check(cd, &(*item)->h, &dreq->req);
		अगर (ret)
			*item = शून्य;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक करो_cache_lookup_noरुको(काष्ठा cache_detail *cd,
		काष्ठा nfs_dns_ent *key,
		काष्ठा nfs_dns_ent **item)
अणु
	पूर्णांक ret = -ENOMEM;

	*item = nfs_dns_lookup(cd, key);
	अगर (!*item)
		जाओ out_err;
	ret = -ETIMEDOUT;
	अगर (!test_bit(CACHE_VALID, &(*item)->h.flags)
			|| (*item)->h.expiry_समय < seconds_since_boot()
			|| cd->flush_समय > (*item)->h.last_refresh)
		जाओ out_put;
	ret = -ENOENT;
	अगर (test_bit(CACHE_NEGATIVE, &(*item)->h.flags))
		जाओ out_put;
	वापस 0;
out_put:
	cache_put(&(*item)->h, cd);
out_err:
	*item = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक करो_cache_lookup_रुको(काष्ठा cache_detail *cd,
		काष्ठा nfs_dns_ent *key,
		काष्ठा nfs_dns_ent **item)
अणु
	काष्ठा nfs_cache_defer_req *dreq;
	पूर्णांक ret = -ENOMEM;

	dreq = nfs_cache_defer_req_alloc();
	अगर (!dreq)
		जाओ out;
	ret = करो_cache_lookup(cd, key, item, dreq);
	अगर (ret == -EAGAIN) अणु
		ret = nfs_cache_रुको_क्रम_upcall(dreq);
		अगर (!ret)
			ret = करो_cache_lookup_noरुको(cd, key, item);
	पूर्ण
	nfs_cache_defer_req_put(dreq);
out:
	वापस ret;
पूर्ण

sमाप_प्रकार nfs_dns_resolve_name(काष्ठा net *net, अक्षर *name,
		माप_प्रकार namelen, काष्ठा sockaddr *sa, माप_प्रकार salen)
अणु
	काष्ठा nfs_dns_ent key = अणु
		.hostname = name,
		.namelen = namelen,
	पूर्ण;
	काष्ठा nfs_dns_ent *item = शून्य;
	sमाप_प्रकार ret;
	काष्ठा nfs_net *nn = net_generic(net, nfs_net_id);

	ret = करो_cache_lookup_रुको(nn->nfs_dns_resolve, &key, &item);
	अगर (ret == 0) अणु
		अगर (salen >= item->addrlen) अणु
			स_नकल(sa, &item->addr, item->addrlen);
			ret = item->addrlen;
		पूर्ण अन्यथा
			ret = -EOVERFLOW;
		cache_put(&item->h, nn->nfs_dns_resolve);
	पूर्ण अन्यथा अगर (ret == -ENOENT)
		ret = -ESRCH;
	वापस ret;
पूर्ण

अटल काष्ठा cache_detail nfs_dns_resolve_ढाँचा = अणु
	.owner		= THIS_MODULE,
	.hash_size	= NFS_DNS_HASHTBL_SIZE,
	.name		= "dns_resolve",
	.cache_put	= nfs_dns_ent_put,
	.cache_upcall	= nfs_dns_upcall,
	.cache_request	= nfs_dns_request,
	.cache_parse	= nfs_dns_parse,
	.cache_show	= nfs_dns_show,
	.match		= nfs_dns_match,
	.init		= nfs_dns_ent_init,
	.update		= nfs_dns_ent_update,
	.alloc		= nfs_dns_ent_alloc,
पूर्ण;


पूर्णांक nfs_dns_resolver_cache_init(काष्ठा net *net)
अणु
	पूर्णांक err;
	काष्ठा nfs_net *nn = net_generic(net, nfs_net_id);

	nn->nfs_dns_resolve = cache_create_net(&nfs_dns_resolve_ढाँचा, net);
	अगर (IS_ERR(nn->nfs_dns_resolve))
		वापस PTR_ERR(nn->nfs_dns_resolve);

	err = nfs_cache_रेजिस्टर_net(net, nn->nfs_dns_resolve);
	अगर (err)
		जाओ err_reg;
	वापस 0;

err_reg:
	cache_destroy_net(nn->nfs_dns_resolve, net);
	वापस err;
पूर्ण

व्योम nfs_dns_resolver_cache_destroy(काष्ठा net *net)
अणु
	काष्ठा nfs_net *nn = net_generic(net, nfs_net_id);

	nfs_cache_unरेजिस्टर_net(net, nn->nfs_dns_resolve);
	cache_destroy_net(nn->nfs_dns_resolve, net);
पूर्ण

अटल पूर्णांक nfs4_dns_net_init(काष्ठा net *net)
अणु
	वापस nfs_dns_resolver_cache_init(net);
पूर्ण

अटल व्योम nfs4_dns_net_निकास(काष्ठा net *net)
अणु
	nfs_dns_resolver_cache_destroy(net);
पूर्ण

अटल काष्ठा pernet_operations nfs4_dns_resolver_ops = अणु
	.init = nfs4_dns_net_init,
	.निकास = nfs4_dns_net_निकास,
पूर्ण;

अटल पूर्णांक rpc_pipefs_event(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event,
			   व्योम *ptr)
अणु
	काष्ठा super_block *sb = ptr;
	काष्ठा net *net = sb->s_fs_info;
	काष्ठा nfs_net *nn = net_generic(net, nfs_net_id);
	काष्ठा cache_detail *cd = nn->nfs_dns_resolve;
	पूर्णांक ret = 0;

	अगर (cd == शून्य)
		वापस 0;

	अगर (!try_module_get(THIS_MODULE))
		वापस 0;

	चयन (event) अणु
	हाल RPC_PIPEFS_MOUNT:
		ret = nfs_cache_रेजिस्टर_sb(sb, cd);
		अवरोध;
	हाल RPC_PIPEFS_UMOUNT:
		nfs_cache_unरेजिस्टर_sb(sb, cd);
		अवरोध;
	शेष:
		ret = -ENOTSUPP;
		अवरोध;
	पूर्ण
	module_put(THIS_MODULE);
	वापस ret;
पूर्ण

अटल काष्ठा notअगरier_block nfs_dns_resolver_block = अणु
	.notअगरier_call	= rpc_pipefs_event,
पूर्ण;

पूर्णांक nfs_dns_resolver_init(व्योम)
अणु
	पूर्णांक err;

	err = रेजिस्टर_pernet_subsys(&nfs4_dns_resolver_ops);
	अगर (err < 0)
		जाओ out;
	err = rpc_pipefs_notअगरier_रेजिस्टर(&nfs_dns_resolver_block);
	अगर (err < 0)
		जाओ out1;
	वापस 0;
out1:
	unरेजिस्टर_pernet_subsys(&nfs4_dns_resolver_ops);
out:
	वापस err;
पूर्ण

व्योम nfs_dns_resolver_destroy(व्योम)
अणु
	rpc_pipefs_notअगरier_unरेजिस्टर(&nfs_dns_resolver_block);
	unरेजिस्टर_pernet_subsys(&nfs4_dns_resolver_ops);
पूर्ण
#पूर्ण_अगर
