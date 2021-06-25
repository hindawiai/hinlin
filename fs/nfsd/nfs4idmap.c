<शैली गुरु>
/*
 *  Mapping of UID/GIDs to name and vice versa.
 *
 *  Copyright (c) 2002, 2003 The Regents of the University of
 *  Michigan.  All rights reserved.
 *
 *  Marius Aamodt Eriksen <marius@umich.edu>
 *
 *  Redistribution and use in source and binary क्रमms, with or without
 *  modअगरication, are permitted provided that the following conditions
 *  are met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary क्रमm must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     करोcumentation and/or other materials provided with the distribution.
 *  3. Neither the name of the University nor the names of its
 *     contributors may be used to enकरोrse or promote products derived
 *     from this software without specअगरic prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 *  FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 *  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <linux/module.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/sunrpc/svc_xprt.h>
#समावेश <net/net_namespace.h>
#समावेश "idmap.h"
#समावेश "nfsd.h"
#समावेश "netns.h"

/*
 * Turn off idmapping when using AUTH_SYS.
 */
अटल bool nfs4_disable_idmapping = true;
module_param(nfs4_disable_idmapping, bool, 0644);
MODULE_PARM_DESC(nfs4_disable_idmapping,
		"Turn off server's NFSv4 idmapping when using 'sec=sys'");

/*
 * Cache entry
 */

/*
 * XXX we know that IDMAP_NAMESZ < PAGE_SIZE, but it's ugly to rely on
 * that.
 */

काष्ठा ent अणु
	काष्ठा cache_head h;
	पूर्णांक               type;		       /* User / Group */
	u32               id;
	अक्षर              name[IDMAP_NAMESZ];
	अक्षर              authname[IDMAP_NAMESZ];
	काष्ठा rcu_head	  rcu_head;
पूर्ण;

/* Common entry handling */

#घोषणा ENT_HASHBITS          8
#घोषणा ENT_HASHMAX           (1 << ENT_HASHBITS)

अटल व्योम
ent_init(काष्ठा cache_head *cnew, काष्ठा cache_head *ciपंचांग)
अणु
	काष्ठा ent *new = container_of(cnew, काष्ठा ent, h);
	काष्ठा ent *iपंचांग = container_of(ciपंचांग, काष्ठा ent, h);

	new->id = iपंचांग->id;
	new->type = iपंचांग->type;

	strlcpy(new->name, iपंचांग->name, माप(new->name));
	strlcpy(new->authname, iपंचांग->authname, माप(new->authname));
पूर्ण

अटल व्योम
ent_put(काष्ठा kref *ref)
अणु
	काष्ठा ent *map = container_of(ref, काष्ठा ent, h.ref);
	kमुक्त_rcu(map, rcu_head);
पूर्ण

अटल काष्ठा cache_head *
ent_alloc(व्योम)
अणु
	काष्ठा ent *e = kदो_स्मृति(माप(*e), GFP_KERNEL);
	अगर (e)
		वापस &e->h;
	अन्यथा
		वापस शून्य;
पूर्ण

/*
 * ID -> Name cache
 */

अटल uपूर्णांक32_t
idtoname_hash(काष्ठा ent *ent)
अणु
	uपूर्णांक32_t hash;

	hash = hash_str(ent->authname, ENT_HASHBITS);
	hash = hash_दीर्घ(hash ^ ent->id, ENT_HASHBITS);

	/* Flip LSB क्रम user/group */
	अगर (ent->type == IDMAP_TYPE_GROUP)
		hash ^= 1;

	वापस hash;
पूर्ण

अटल पूर्णांक
idtoname_upcall(काष्ठा cache_detail *cd, काष्ठा cache_head *h)
अणु
	वापस sunrpc_cache_pipe_upcall_समयout(cd, h);
पूर्ण

अटल व्योम
idtoname_request(काष्ठा cache_detail *cd, काष्ठा cache_head *ch, अक्षर **bpp,
    पूर्णांक *blen)
अणु
 	काष्ठा ent *ent = container_of(ch, काष्ठा ent, h);
	अक्षर idstr[11];

	qword_add(bpp, blen, ent->authname);
	snम_लिखो(idstr, माप(idstr), "%u", ent->id);
	qword_add(bpp, blen, ent->type == IDMAP_TYPE_GROUP ? "group" : "user");
	qword_add(bpp, blen, idstr);

	(*bpp)[-1] = '\n';
पूर्ण

अटल पूर्णांक
idtoname_match(काष्ठा cache_head *ca, काष्ठा cache_head *cb)
अणु
	काष्ठा ent *a = container_of(ca, काष्ठा ent, h);
	काष्ठा ent *b = container_of(cb, काष्ठा ent, h);

	वापस (a->id == b->id && a->type == b->type &&
	    म_भेद(a->authname, b->authname) == 0);
पूर्ण

अटल पूर्णांक
idtoname_show(काष्ठा seq_file *m, काष्ठा cache_detail *cd, काष्ठा cache_head *h)
अणु
	काष्ठा ent *ent;

	अगर (h == शून्य) अणु
		seq_माला_दो(m, "#domain type id [name]\n");
		वापस 0;
	पूर्ण
	ent = container_of(h, काष्ठा ent, h);
	seq_म_लिखो(m, "%s %s %u", ent->authname,
			ent->type == IDMAP_TYPE_GROUP ? "group" : "user",
			ent->id);
	अगर (test_bit(CACHE_VALID, &h->flags))
		seq_म_लिखो(m, " %s", ent->name);
	seq_अ_दो(m, '\n');
	वापस 0;
पूर्ण

अटल व्योम
warn_no_idmapd(काष्ठा cache_detail *detail, पूर्णांक has_died)
अणु
	prपूर्णांकk("nfsd: nfsv4 idmapping failing: has idmapd %s?\n",
			has_died ? "died" : "not been started");
पूर्ण


अटल पूर्णांक         idtoname_parse(काष्ठा cache_detail *, अक्षर *, पूर्णांक);
अटल काष्ठा ent *idtoname_lookup(काष्ठा cache_detail *, काष्ठा ent *);
अटल काष्ठा ent *idtoname_update(काष्ठा cache_detail *, काष्ठा ent *,
				   काष्ठा ent *);

अटल स्थिर काष्ठा cache_detail idtoname_cache_ढाँचा = अणु
	.owner		= THIS_MODULE,
	.hash_size	= ENT_HASHMAX,
	.name		= "nfs4.idtoname",
	.cache_put	= ent_put,
	.cache_upcall	= idtoname_upcall,
	.cache_request	= idtoname_request,
	.cache_parse	= idtoname_parse,
	.cache_show	= idtoname_show,
	.warn_no_listener = warn_no_idmapd,
	.match		= idtoname_match,
	.init		= ent_init,
	.update		= ent_init,
	.alloc		= ent_alloc,
पूर्ण;

अटल पूर्णांक
idtoname_parse(काष्ठा cache_detail *cd, अक्षर *buf, पूर्णांक buflen)
अणु
	काष्ठा ent ent, *res;
	अक्षर *buf1, *bp;
	पूर्णांक len;
	पूर्णांक error = -EINVAL;

	अगर (buf[buflen - 1] != '\n')
		वापस (-EINVAL);
	buf[buflen - 1]= '\0';

	buf1 = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (buf1 == शून्य)
		वापस (-ENOMEM);

	स_रखो(&ent, 0, माप(ent));

	/* Authentication name */
	len = qword_get(&buf, buf1, PAGE_SIZE);
	अगर (len <= 0 || len >= IDMAP_NAMESZ)
		जाओ out;
	स_नकल(ent.authname, buf1, माप(ent.authname));

	/* Type */
	अगर (qword_get(&buf, buf1, PAGE_SIZE) <= 0)
		जाओ out;
	ent.type = म_भेद(buf1, "user") == 0 ?
		IDMAP_TYPE_USER : IDMAP_TYPE_GROUP;

	/* ID */
	अगर (qword_get(&buf, buf1, PAGE_SIZE) <= 0)
		जाओ out;
	ent.id = simple_म_से_अदीर्घ(buf1, &bp, 10);
	अगर (bp == buf1)
		जाओ out;

	/* expiry */
	ent.h.expiry_समय = get_expiry(&buf);
	अगर (ent.h.expiry_समय == 0)
		जाओ out;

	error = -ENOMEM;
	res = idtoname_lookup(cd, &ent);
	अगर (!res)
		जाओ out;

	/* Name */
	error = -EINVAL;
	len = qword_get(&buf, buf1, PAGE_SIZE);
	अगर (len < 0 || len >= IDMAP_NAMESZ)
		जाओ out;
	अगर (len == 0)
		set_bit(CACHE_NEGATIVE, &ent.h.flags);
	अन्यथा
		स_नकल(ent.name, buf1, माप(ent.name));
	error = -ENOMEM;
	res = idtoname_update(cd, &ent, res);
	अगर (res == शून्य)
		जाओ out;

	cache_put(&res->h, cd);
	error = 0;
out:
	kमुक्त(buf1);
	वापस error;
पूर्ण

अटल काष्ठा ent *
idtoname_lookup(काष्ठा cache_detail *cd, काष्ठा ent *item)
अणु
	काष्ठा cache_head *ch = sunrpc_cache_lookup_rcu(cd, &item->h,
							idtoname_hash(item));
	अगर (ch)
		वापस container_of(ch, काष्ठा ent, h);
	अन्यथा
		वापस शून्य;
पूर्ण

अटल काष्ठा ent *
idtoname_update(काष्ठा cache_detail *cd, काष्ठा ent *new, काष्ठा ent *old)
अणु
	काष्ठा cache_head *ch = sunrpc_cache_update(cd, &new->h, &old->h,
						    idtoname_hash(new));
	अगर (ch)
		वापस container_of(ch, काष्ठा ent, h);
	अन्यथा
		वापस शून्य;
पूर्ण


/*
 * Name -> ID cache
 */

अटल अंतरभूत पूर्णांक
nametoid_hash(काष्ठा ent *ent)
अणु
	वापस hash_str(ent->name, ENT_HASHBITS);
पूर्ण

अटल पूर्णांक
nametoid_upcall(काष्ठा cache_detail *cd, काष्ठा cache_head *h)
अणु
	वापस sunrpc_cache_pipe_upcall_समयout(cd, h);
पूर्ण

अटल व्योम
nametoid_request(काष्ठा cache_detail *cd, काष्ठा cache_head *ch, अक्षर **bpp,
    पूर्णांक *blen)
अणु
 	काष्ठा ent *ent = container_of(ch, काष्ठा ent, h);

	qword_add(bpp, blen, ent->authname);
	qword_add(bpp, blen, ent->type == IDMAP_TYPE_GROUP ? "group" : "user");
	qword_add(bpp, blen, ent->name);

	(*bpp)[-1] = '\n';
पूर्ण

अटल पूर्णांक
nametoid_match(काष्ठा cache_head *ca, काष्ठा cache_head *cb)
अणु
	काष्ठा ent *a = container_of(ca, काष्ठा ent, h);
	काष्ठा ent *b = container_of(cb, काष्ठा ent, h);

	वापस (a->type == b->type && म_भेद(a->name, b->name) == 0 &&
	    म_भेद(a->authname, b->authname) == 0);
पूर्ण

अटल पूर्णांक
nametoid_show(काष्ठा seq_file *m, काष्ठा cache_detail *cd, काष्ठा cache_head *h)
अणु
	काष्ठा ent *ent;

	अगर (h == शून्य) अणु
		seq_माला_दो(m, "#domain type name [id]\n");
		वापस 0;
	पूर्ण
	ent = container_of(h, काष्ठा ent, h);
	seq_म_लिखो(m, "%s %s %s", ent->authname,
			ent->type == IDMAP_TYPE_GROUP ? "group" : "user",
			ent->name);
	अगर (test_bit(CACHE_VALID, &h->flags))
		seq_म_लिखो(m, " %u", ent->id);
	seq_अ_दो(m, '\n');
	वापस 0;
पूर्ण

अटल काष्ठा ent *nametoid_lookup(काष्ठा cache_detail *, काष्ठा ent *);
अटल काष्ठा ent *nametoid_update(काष्ठा cache_detail *, काष्ठा ent *,
				   काष्ठा ent *);
अटल पूर्णांक         nametoid_parse(काष्ठा cache_detail *, अक्षर *, पूर्णांक);

अटल स्थिर काष्ठा cache_detail nametoid_cache_ढाँचा = अणु
	.owner		= THIS_MODULE,
	.hash_size	= ENT_HASHMAX,
	.name		= "nfs4.nametoid",
	.cache_put	= ent_put,
	.cache_upcall	= nametoid_upcall,
	.cache_request	= nametoid_request,
	.cache_parse	= nametoid_parse,
	.cache_show	= nametoid_show,
	.warn_no_listener = warn_no_idmapd,
	.match		= nametoid_match,
	.init		= ent_init,
	.update		= ent_init,
	.alloc		= ent_alloc,
पूर्ण;

अटल पूर्णांक
nametoid_parse(काष्ठा cache_detail *cd, अक्षर *buf, पूर्णांक buflen)
अणु
	काष्ठा ent ent, *res;
	अक्षर *buf1;
	पूर्णांक len, error = -EINVAL;

	अगर (buf[buflen - 1] != '\n')
		वापस (-EINVAL);
	buf[buflen - 1]= '\0';

	buf1 = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (buf1 == शून्य)
		वापस (-ENOMEM);

	स_रखो(&ent, 0, माप(ent));

	/* Authentication name */
	len = qword_get(&buf, buf1, PAGE_SIZE);
	अगर (len <= 0 || len >= IDMAP_NAMESZ)
		जाओ out;
	स_नकल(ent.authname, buf1, माप(ent.authname));

	/* Type */
	अगर (qword_get(&buf, buf1, PAGE_SIZE) <= 0)
		जाओ out;
	ent.type = म_भेद(buf1, "user") == 0 ?
		IDMAP_TYPE_USER : IDMAP_TYPE_GROUP;

	/* Name */
	len = qword_get(&buf, buf1, PAGE_SIZE);
	अगर (len <= 0 || len >= IDMAP_NAMESZ)
		जाओ out;
	स_नकल(ent.name, buf1, माप(ent.name));

	/* expiry */
	ent.h.expiry_समय = get_expiry(&buf);
	अगर (ent.h.expiry_समय == 0)
		जाओ out;

	/* ID */
	error = get_पूर्णांक(&buf, &ent.id);
	अगर (error == -EINVAL)
		जाओ out;
	अगर (error == -ENOENT)
		set_bit(CACHE_NEGATIVE, &ent.h.flags);

	error = -ENOMEM;
	res = nametoid_lookup(cd, &ent);
	अगर (res == शून्य)
		जाओ out;
	res = nametoid_update(cd, &ent, res);
	अगर (res == शून्य)
		जाओ out;

	cache_put(&res->h, cd);
	error = 0;
out:
	kमुक्त(buf1);
	वापस (error);
पूर्ण


अटल काष्ठा ent *
nametoid_lookup(काष्ठा cache_detail *cd, काष्ठा ent *item)
अणु
	काष्ठा cache_head *ch = sunrpc_cache_lookup_rcu(cd, &item->h,
							nametoid_hash(item));
	अगर (ch)
		वापस container_of(ch, काष्ठा ent, h);
	अन्यथा
		वापस शून्य;
पूर्ण

अटल काष्ठा ent *
nametoid_update(काष्ठा cache_detail *cd, काष्ठा ent *new, काष्ठा ent *old)
अणु
	काष्ठा cache_head *ch = sunrpc_cache_update(cd, &new->h, &old->h,
						    nametoid_hash(new));
	अगर (ch)
		वापस container_of(ch, काष्ठा ent, h);
	अन्यथा
		वापस शून्य;
पूर्ण

/*
 * Exported API
 */

पूर्णांक
nfsd_idmap_init(काष्ठा net *net)
अणु
	पूर्णांक rv;
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	nn->idtoname_cache = cache_create_net(&idtoname_cache_ढाँचा, net);
	अगर (IS_ERR(nn->idtoname_cache))
		वापस PTR_ERR(nn->idtoname_cache);
	rv = cache_रेजिस्टर_net(nn->idtoname_cache, net);
	अगर (rv)
		जाओ destroy_idtoname_cache;
	nn->nametoid_cache = cache_create_net(&nametoid_cache_ढाँचा, net);
	अगर (IS_ERR(nn->nametoid_cache)) अणु
		rv = PTR_ERR(nn->nametoid_cache);
		जाओ unरेजिस्टर_idtoname_cache;
	पूर्ण
	rv = cache_रेजिस्टर_net(nn->nametoid_cache, net);
	अगर (rv)
		जाओ destroy_nametoid_cache;
	वापस 0;

destroy_nametoid_cache:
	cache_destroy_net(nn->nametoid_cache, net);
unरेजिस्टर_idtoname_cache:
	cache_unरेजिस्टर_net(nn->idtoname_cache, net);
destroy_idtoname_cache:
	cache_destroy_net(nn->idtoname_cache, net);
	वापस rv;
पूर्ण

व्योम
nfsd_idmap_shutकरोwn(काष्ठा net *net)
अणु
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	cache_unरेजिस्टर_net(nn->idtoname_cache, net);
	cache_unरेजिस्टर_net(nn->nametoid_cache, net);
	cache_destroy_net(nn->idtoname_cache, net);
	cache_destroy_net(nn->nametoid_cache, net);
पूर्ण

अटल पूर्णांक
idmap_lookup(काष्ठा svc_rqst *rqstp,
		काष्ठा ent *(*lookup_fn)(काष्ठा cache_detail *, काष्ठा ent *),
		काष्ठा ent *key, काष्ठा cache_detail *detail, काष्ठा ent **item)
अणु
	पूर्णांक ret;

	*item = lookup_fn(detail, key);
	अगर (!*item)
		वापस -ENOMEM;
 retry:
	ret = cache_check(detail, &(*item)->h, &rqstp->rq_chandle);

	अगर (ret == -ETIMEDOUT) अणु
		काष्ठा ent *prev_item = *item;
		*item = lookup_fn(detail, key);
		अगर (*item != prev_item)
			जाओ retry;
		cache_put(&(*item)->h, detail);
	पूर्ण
	वापस ret;
पूर्ण

अटल अक्षर *
rqst_authname(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा auth_करोमुख्य *clp;

	clp = rqstp->rq_gssclient ? rqstp->rq_gssclient : rqstp->rq_client;
	वापस clp->name;
पूर्ण

अटल __be32
idmap_name_to_id(काष्ठा svc_rqst *rqstp, पूर्णांक type, स्थिर अक्षर *name, u32 namelen,
		u32 *id)
अणु
	काष्ठा ent *item, key = अणु
		.type = type,
	पूर्ण;
	पूर्णांक ret;
	काष्ठा nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);

	अगर (namelen + 1 > माप(key.name))
		वापस nfserr_baकरोwner;
	स_नकल(key.name, name, namelen);
	key.name[namelen] = '\0';
	strlcpy(key.authname, rqst_authname(rqstp), माप(key.authname));
	ret = idmap_lookup(rqstp, nametoid_lookup, &key, nn->nametoid_cache, &item);
	अगर (ret == -ENOENT)
		वापस nfserr_baकरोwner;
	अगर (ret)
		वापस nfsत्रुटि_सं(ret);
	*id = item->id;
	cache_put(&item->h, nn->nametoid_cache);
	वापस 0;
पूर्ण

अटल __be32 encode_ascii_id(काष्ठा xdr_stream *xdr, u32 id)
अणु
	अक्षर buf[11];
	पूर्णांक len;
	__be32 *p;

	len = प्र_लिखो(buf, "%u", id);
	p = xdr_reserve_space(xdr, len + 4);
	अगर (!p)
		वापस nfserr_resource;
	p = xdr_encode_opaque(p, buf, len);
	वापस 0;
पूर्ण

अटल __be32 idmap_id_to_name(काष्ठा xdr_stream *xdr,
			       काष्ठा svc_rqst *rqstp, पूर्णांक type, u32 id)
अणु
	काष्ठा ent *item, key = अणु
		.id = id,
		.type = type,
	पूर्ण;
	__be32 *p;
	पूर्णांक ret;
	काष्ठा nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);

	strlcpy(key.authname, rqst_authname(rqstp), माप(key.authname));
	ret = idmap_lookup(rqstp, idtoname_lookup, &key, nn->idtoname_cache, &item);
	अगर (ret == -ENOENT)
		वापस encode_ascii_id(xdr, id);
	अगर (ret)
		वापस nfsत्रुटि_सं(ret);
	ret = म_माप(item->name);
	WARN_ON_ONCE(ret > IDMAP_NAMESZ);
	p = xdr_reserve_space(xdr, ret + 4);
	अगर (!p)
		वापस nfserr_resource;
	p = xdr_encode_opaque(p, item->name, ret);
	cache_put(&item->h, nn->idtoname_cache);
	वापस 0;
पूर्ण

अटल bool
numeric_name_to_id(काष्ठा svc_rqst *rqstp, पूर्णांक type, स्थिर अक्षर *name, u32 namelen, u32 *id)
अणु
	पूर्णांक ret;
	अक्षर buf[11];

	अगर (namelen + 1 > माप(buf))
		/* too दीर्घ to represent a 32-bit id: */
		वापस false;
	/* Just to make sure it's null-terminated: */
	स_नकल(buf, name, namelen);
	buf[namelen] = '\0';
	ret = kstrtouपूर्णांक(buf, 10, id);
	वापस ret == 0;
पूर्ण

अटल __be32
करो_name_to_id(काष्ठा svc_rqst *rqstp, पूर्णांक type, स्थिर अक्षर *name, u32 namelen, u32 *id)
अणु
	अगर (nfs4_disable_idmapping && rqstp->rq_cred.cr_flavor < RPC_AUTH_GSS)
		अगर (numeric_name_to_id(rqstp, type, name, namelen, id))
			वापस 0;
		/*
		 * otherwise, fall through and try idmapping, क्रम
		 * backwards compatibility with clients sending names:
		 */
	वापस idmap_name_to_id(rqstp, type, name, namelen, id);
पूर्ण

अटल __be32 encode_name_from_id(काष्ठा xdr_stream *xdr,
				  काष्ठा svc_rqst *rqstp, पूर्णांक type, u32 id)
अणु
	अगर (nfs4_disable_idmapping && rqstp->rq_cred.cr_flavor < RPC_AUTH_GSS)
		वापस encode_ascii_id(xdr, id);
	वापस idmap_id_to_name(xdr, rqstp, type, id);
पूर्ण

__be32
nfsd_map_name_to_uid(काष्ठा svc_rqst *rqstp, स्थिर अक्षर *name, माप_प्रकार namelen,
		kuid_t *uid)
अणु
	__be32 status;
	u32 id = -1;

	अगर (name == शून्य || namelen == 0)
		वापस nfserr_inval;

	status = करो_name_to_id(rqstp, IDMAP_TYPE_USER, name, namelen, &id);
	*uid = make_kuid(nfsd_user_namespace(rqstp), id);
	अगर (!uid_valid(*uid))
		status = nfserr_baकरोwner;
	वापस status;
पूर्ण

__be32
nfsd_map_name_to_gid(काष्ठा svc_rqst *rqstp, स्थिर अक्षर *name, माप_प्रकार namelen,
		kgid_t *gid)
अणु
	__be32 status;
	u32 id = -1;

	अगर (name == शून्य || namelen == 0)
		वापस nfserr_inval;

	status = करो_name_to_id(rqstp, IDMAP_TYPE_GROUP, name, namelen, &id);
	*gid = make_kgid(nfsd_user_namespace(rqstp), id);
	अगर (!gid_valid(*gid))
		status = nfserr_baकरोwner;
	वापस status;
पूर्ण

__be32 nfsd4_encode_user(काष्ठा xdr_stream *xdr, काष्ठा svc_rqst *rqstp,
			 kuid_t uid)
अणु
	u32 id = from_kuid_munged(nfsd_user_namespace(rqstp), uid);
	वापस encode_name_from_id(xdr, rqstp, IDMAP_TYPE_USER, id);
पूर्ण

__be32 nfsd4_encode_group(काष्ठा xdr_stream *xdr, काष्ठा svc_rqst *rqstp,
			  kgid_t gid)
अणु
	u32 id = from_kgid_munged(nfsd_user_namespace(rqstp), gid);
	वापस encode_name_from_id(xdr, rqstp, IDMAP_TYPE_GROUP, id);
पूर्ण
