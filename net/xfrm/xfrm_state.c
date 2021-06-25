<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * xfrm_state.c
 *
 * Changes:
 *	Mitsuru KANDA @USAGI
 * 	Kazunori MIYAZAWA @USAGI
 * 	Kunihiro Ishiguro <kunihiro@ipinfusion.com>
 * 		IPv6 support
 * 	YOSHIFUJI Hideaki @USAGI
 * 		Split up af-specअगरic functions
 *	Derek Atkins <derek@ihtfp.com>
 *		Add UDP Encapsulation
 *
 */

#समावेश <linux/workqueue.h>
#समावेश <net/xfrm.h>
#समावेश <linux/pfkeyv2.h>
#समावेश <linux/ipsec.h>
#समावेश <linux/module.h>
#समावेश <linux/cache.h>
#समावेश <linux/audit.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>

#समावेश <crypto/aead.h>

#समावेश "xfrm_hash.h"

#घोषणा xfrm_state_deref_prot(table, net) \
	rcu_dereference_रक्षित((table), lockdep_is_held(&(net)->xfrm.xfrm_state_lock))

अटल व्योम xfrm_state_gc_task(काष्ठा work_काष्ठा *work);

/* Each xfrm_state may be linked to two tables:

   1. Hash table by (spi,daddr,ah/esp) to find SA by SPI. (input,ctl)
   2. Hash table by (daddr,family,reqid) to find what SAs exist क्रम given
      destination/tunnel endpoपूर्णांक. (output)
 */

अटल अचिन्हित पूर्णांक xfrm_state_hashmax __पढ़ो_mostly = 1 * 1024 * 1024;
अटल काष्ठा kmem_cache *xfrm_state_cache __ro_after_init;

अटल DECLARE_WORK(xfrm_state_gc_work, xfrm_state_gc_task);
अटल HLIST_HEAD(xfrm_state_gc_list);

अटल अंतरभूत bool xfrm_state_hold_rcu(काष्ठा xfrm_state __rcu *x)
अणु
	वापस refcount_inc_not_zero(&x->refcnt);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक xfrm_dst_hash(काष्ठा net *net,
					 स्थिर xfrm_address_t *daddr,
					 स्थिर xfrm_address_t *saddr,
					 u32 reqid,
					 अचिन्हित लघु family)
अणु
	वापस __xfrm_dst_hash(daddr, saddr, reqid, family, net->xfrm.state_hmask);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक xfrm_src_hash(काष्ठा net *net,
					 स्थिर xfrm_address_t *daddr,
					 स्थिर xfrm_address_t *saddr,
					 अचिन्हित लघु family)
अणु
	वापस __xfrm_src_hash(daddr, saddr, family, net->xfrm.state_hmask);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
xfrm_spi_hash(काष्ठा net *net, स्थिर xfrm_address_t *daddr,
	      __be32 spi, u8 proto, अचिन्हित लघु family)
अणु
	वापस __xfrm_spi_hash(daddr, spi, proto, family, net->xfrm.state_hmask);
पूर्ण

अटल व्योम xfrm_hash_transfer(काष्ठा hlist_head *list,
			       काष्ठा hlist_head *ndsttable,
			       काष्ठा hlist_head *nsrctable,
			       काष्ठा hlist_head *nspitable,
			       अचिन्हित पूर्णांक nhashmask)
अणु
	काष्ठा hlist_node *पंचांगp;
	काष्ठा xfrm_state *x;

	hlist_क्रम_each_entry_safe(x, पंचांगp, list, bydst) अणु
		अचिन्हित पूर्णांक h;

		h = __xfrm_dst_hash(&x->id.daddr, &x->props.saddr,
				    x->props.reqid, x->props.family,
				    nhashmask);
		hlist_add_head_rcu(&x->bydst, ndsttable + h);

		h = __xfrm_src_hash(&x->id.daddr, &x->props.saddr,
				    x->props.family,
				    nhashmask);
		hlist_add_head_rcu(&x->bysrc, nsrctable + h);

		अगर (x->id.spi) अणु
			h = __xfrm_spi_hash(&x->id.daddr, x->id.spi,
					    x->id.proto, x->props.family,
					    nhashmask);
			hlist_add_head_rcu(&x->byspi, nspitable + h);
		पूर्ण
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ xfrm_hash_new_size(अचिन्हित पूर्णांक state_hmask)
अणु
	वापस ((state_hmask + 1) << 1) * माप(काष्ठा hlist_head);
पूर्ण

अटल व्योम xfrm_hash_resize(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा net *net = container_of(work, काष्ठा net, xfrm.state_hash_work);
	काष्ठा hlist_head *ndst, *nsrc, *nspi, *odst, *osrc, *ospi;
	अचिन्हित दीर्घ nsize, osize;
	अचिन्हित पूर्णांक nhashmask, ohashmask;
	पूर्णांक i;

	nsize = xfrm_hash_new_size(net->xfrm.state_hmask);
	ndst = xfrm_hash_alloc(nsize);
	अगर (!ndst)
		वापस;
	nsrc = xfrm_hash_alloc(nsize);
	अगर (!nsrc) अणु
		xfrm_hash_मुक्त(ndst, nsize);
		वापस;
	पूर्ण
	nspi = xfrm_hash_alloc(nsize);
	अगर (!nspi) अणु
		xfrm_hash_मुक्त(ndst, nsize);
		xfrm_hash_मुक्त(nsrc, nsize);
		वापस;
	पूर्ण

	spin_lock_bh(&net->xfrm.xfrm_state_lock);
	ग_लिखो_seqcount_begin(&net->xfrm.xfrm_state_hash_generation);

	nhashmask = (nsize / माप(काष्ठा hlist_head)) - 1U;
	odst = xfrm_state_deref_prot(net->xfrm.state_bydst, net);
	क्रम (i = net->xfrm.state_hmask; i >= 0; i--)
		xfrm_hash_transfer(odst + i, ndst, nsrc, nspi, nhashmask);

	osrc = xfrm_state_deref_prot(net->xfrm.state_bysrc, net);
	ospi = xfrm_state_deref_prot(net->xfrm.state_byspi, net);
	ohashmask = net->xfrm.state_hmask;

	rcu_assign_poपूर्णांकer(net->xfrm.state_bydst, ndst);
	rcu_assign_poपूर्णांकer(net->xfrm.state_bysrc, nsrc);
	rcu_assign_poपूर्णांकer(net->xfrm.state_byspi, nspi);
	net->xfrm.state_hmask = nhashmask;

	ग_लिखो_seqcount_end(&net->xfrm.xfrm_state_hash_generation);
	spin_unlock_bh(&net->xfrm.xfrm_state_lock);

	osize = (ohashmask + 1) * माप(काष्ठा hlist_head);

	synchronize_rcu();

	xfrm_hash_मुक्त(odst, osize);
	xfrm_hash_मुक्त(osrc, osize);
	xfrm_hash_मुक्त(ospi, osize);
पूर्ण

अटल DEFINE_SPINLOCK(xfrm_state_afinfo_lock);
अटल काष्ठा xfrm_state_afinfo __rcu *xfrm_state_afinfo[NPROTO];

अटल DEFINE_SPINLOCK(xfrm_state_gc_lock);

पूर्णांक __xfrm_state_delete(काष्ठा xfrm_state *x);

पूर्णांक km_query(काष्ठा xfrm_state *x, काष्ठा xfrm_पंचांगpl *t, काष्ठा xfrm_policy *pol);
अटल bool km_is_alive(स्थिर काष्ठा km_event *c);
व्योम km_state_expired(काष्ठा xfrm_state *x, पूर्णांक hard, u32 portid);

पूर्णांक xfrm_रेजिस्टर_type(स्थिर काष्ठा xfrm_type *type, अचिन्हित लघु family)
अणु
	काष्ठा xfrm_state_afinfo *afinfo = xfrm_state_get_afinfo(family);
	पूर्णांक err = 0;

	अगर (!afinfo)
		वापस -EAFNOSUPPORT;

#घोषणा X(afi, T, name) करो अणु			\
		WARN_ON((afi)->type_ ## name);	\
		(afi)->type_ ## name = (T);	\
	पूर्ण जबतक (0)

	चयन (type->proto) अणु
	हाल IPPROTO_COMP:
		X(afinfo, type, comp);
		अवरोध;
	हाल IPPROTO_AH:
		X(afinfo, type, ah);
		अवरोध;
	हाल IPPROTO_ESP:
		X(afinfo, type, esp);
		अवरोध;
	हाल IPPROTO_IPIP:
		X(afinfo, type, ipip);
		अवरोध;
	हाल IPPROTO_DSTOPTS:
		X(afinfo, type, dstopts);
		अवरोध;
	हाल IPPROTO_ROUTING:
		X(afinfo, type, routing);
		अवरोध;
	हाल IPPROTO_IPV6:
		X(afinfo, type, ipip6);
		अवरोध;
	शेष:
		WARN_ON(1);
		err = -EPROTONOSUPPORT;
		अवरोध;
	पूर्ण
#अघोषित X
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण
EXPORT_SYMBOL(xfrm_रेजिस्टर_type);

व्योम xfrm_unरेजिस्टर_type(स्थिर काष्ठा xfrm_type *type, अचिन्हित लघु family)
अणु
	काष्ठा xfrm_state_afinfo *afinfo = xfrm_state_get_afinfo(family);

	अगर (unlikely(afinfo == शून्य))
		वापस;

#घोषणा X(afi, T, name) करो अणु				\
		WARN_ON((afi)->type_ ## name != (T));	\
		(afi)->type_ ## name = शून्य;		\
	पूर्ण जबतक (0)

	चयन (type->proto) अणु
	हाल IPPROTO_COMP:
		X(afinfo, type, comp);
		अवरोध;
	हाल IPPROTO_AH:
		X(afinfo, type, ah);
		अवरोध;
	हाल IPPROTO_ESP:
		X(afinfo, type, esp);
		अवरोध;
	हाल IPPROTO_IPIP:
		X(afinfo, type, ipip);
		अवरोध;
	हाल IPPROTO_DSTOPTS:
		X(afinfo, type, dstopts);
		अवरोध;
	हाल IPPROTO_ROUTING:
		X(afinfo, type, routing);
		अवरोध;
	हाल IPPROTO_IPV6:
		X(afinfo, type, ipip6);
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण
#अघोषित X
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(xfrm_unरेजिस्टर_type);

अटल स्थिर काष्ठा xfrm_type *xfrm_get_type(u8 proto, अचिन्हित लघु family)
अणु
	स्थिर काष्ठा xfrm_type *type = शून्य;
	काष्ठा xfrm_state_afinfo *afinfo;
	पूर्णांक modload_attempted = 0;

retry:
	afinfo = xfrm_state_get_afinfo(family);
	अगर (unlikely(afinfo == शून्य))
		वापस शून्य;

	चयन (proto) अणु
	हाल IPPROTO_COMP:
		type = afinfo->type_comp;
		अवरोध;
	हाल IPPROTO_AH:
		type = afinfo->type_ah;
		अवरोध;
	हाल IPPROTO_ESP:
		type = afinfo->type_esp;
		अवरोध;
	हाल IPPROTO_IPIP:
		type = afinfo->type_ipip;
		अवरोध;
	हाल IPPROTO_DSTOPTS:
		type = afinfo->type_dstopts;
		अवरोध;
	हाल IPPROTO_ROUTING:
		type = afinfo->type_routing;
		अवरोध;
	हाल IPPROTO_IPV6:
		type = afinfo->type_ipip6;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (unlikely(type && !try_module_get(type->owner)))
		type = शून्य;

	rcu_पढ़ो_unlock();

	अगर (!type && !modload_attempted) अणु
		request_module("xfrm-type-%d-%d", family, proto);
		modload_attempted = 1;
		जाओ retry;
	पूर्ण

	वापस type;
पूर्ण

अटल व्योम xfrm_put_type(स्थिर काष्ठा xfrm_type *type)
अणु
	module_put(type->owner);
पूर्ण

पूर्णांक xfrm_रेजिस्टर_type_offload(स्थिर काष्ठा xfrm_type_offload *type,
			       अचिन्हित लघु family)
अणु
	काष्ठा xfrm_state_afinfo *afinfo = xfrm_state_get_afinfo(family);
	पूर्णांक err = 0;

	अगर (unlikely(afinfo == शून्य))
		वापस -EAFNOSUPPORT;

	चयन (type->proto) अणु
	हाल IPPROTO_ESP:
		WARN_ON(afinfo->type_offload_esp);
		afinfo->type_offload_esp = type;
		अवरोध;
	शेष:
		WARN_ON(1);
		err = -EPROTONOSUPPORT;
		अवरोध;
	पूर्ण

	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण
EXPORT_SYMBOL(xfrm_रेजिस्टर_type_offload);

व्योम xfrm_unरेजिस्टर_type_offload(स्थिर काष्ठा xfrm_type_offload *type,
				  अचिन्हित लघु family)
अणु
	काष्ठा xfrm_state_afinfo *afinfo = xfrm_state_get_afinfo(family);

	अगर (unlikely(afinfo == शून्य))
		वापस;

	चयन (type->proto) अणु
	हाल IPPROTO_ESP:
		WARN_ON(afinfo->type_offload_esp != type);
		afinfo->type_offload_esp = शून्य;
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(xfrm_unरेजिस्टर_type_offload);

अटल स्थिर काष्ठा xfrm_type_offload *
xfrm_get_type_offload(u8 proto, अचिन्हित लघु family, bool try_load)
अणु
	स्थिर काष्ठा xfrm_type_offload *type = शून्य;
	काष्ठा xfrm_state_afinfo *afinfo;

retry:
	afinfo = xfrm_state_get_afinfo(family);
	अगर (unlikely(afinfo == शून्य))
		वापस शून्य;

	चयन (proto) अणु
	हाल IPPROTO_ESP:
		type = afinfo->type_offload_esp;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर ((type && !try_module_get(type->owner)))
		type = शून्य;

	rcu_पढ़ो_unlock();

	अगर (!type && try_load) अणु
		request_module("xfrm-offload-%d-%d", family, proto);
		try_load = false;
		जाओ retry;
	पूर्ण

	वापस type;
पूर्ण

अटल व्योम xfrm_put_type_offload(स्थिर काष्ठा xfrm_type_offload *type)
अणु
	module_put(type->owner);
पूर्ण

अटल स्थिर काष्ठा xfrm_mode xfrm4_mode_map[XFRM_MODE_MAX] = अणु
	[XFRM_MODE_BEET] = अणु
		.encap = XFRM_MODE_BEET,
		.flags = XFRM_MODE_FLAG_TUNNEL,
		.family = AF_INET,
	पूर्ण,
	[XFRM_MODE_TRANSPORT] = अणु
		.encap = XFRM_MODE_TRANSPORT,
		.family = AF_INET,
	पूर्ण,
	[XFRM_MODE_TUNNEL] = अणु
		.encap = XFRM_MODE_TUNNEL,
		.flags = XFRM_MODE_FLAG_TUNNEL,
		.family = AF_INET,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा xfrm_mode xfrm6_mode_map[XFRM_MODE_MAX] = अणु
	[XFRM_MODE_BEET] = अणु
		.encap = XFRM_MODE_BEET,
		.flags = XFRM_MODE_FLAG_TUNNEL,
		.family = AF_INET6,
	पूर्ण,
	[XFRM_MODE_ROUTEOPTIMIZATION] = अणु
		.encap = XFRM_MODE_ROUTEOPTIMIZATION,
		.family = AF_INET6,
	पूर्ण,
	[XFRM_MODE_TRANSPORT] = अणु
		.encap = XFRM_MODE_TRANSPORT,
		.family = AF_INET6,
	पूर्ण,
	[XFRM_MODE_TUNNEL] = अणु
		.encap = XFRM_MODE_TUNNEL,
		.flags = XFRM_MODE_FLAG_TUNNEL,
		.family = AF_INET6,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा xfrm_mode *xfrm_get_mode(अचिन्हित पूर्णांक encap, पूर्णांक family)
अणु
	स्थिर काष्ठा xfrm_mode *mode;

	अगर (unlikely(encap >= XFRM_MODE_MAX))
		वापस शून्य;

	चयन (family) अणु
	हाल AF_INET:
		mode = &xfrm4_mode_map[encap];
		अगर (mode->family == family)
			वापस mode;
		अवरोध;
	हाल AF_INET6:
		mode = &xfrm6_mode_map[encap];
		अगर (mode->family == family)
			वापस mode;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम xfrm_state_मुक्त(काष्ठा xfrm_state *x)
अणु
	kmem_cache_मुक्त(xfrm_state_cache, x);
पूर्ण
EXPORT_SYMBOL(xfrm_state_मुक्त);

अटल व्योम ___xfrm_state_destroy(काष्ठा xfrm_state *x)
अणु
	hrसमयr_cancel(&x->mसमयr);
	del_समयr_sync(&x->rसमयr);
	kमुक्त(x->aead);
	kमुक्त(x->aalg);
	kमुक्त(x->ealg);
	kमुक्त(x->calg);
	kमुक्त(x->encap);
	kमुक्त(x->coaddr);
	kमुक्त(x->replay_esn);
	kमुक्त(x->preplay_esn);
	अगर (x->type_offload)
		xfrm_put_type_offload(x->type_offload);
	अगर (x->type) अणु
		x->type->deकाष्ठाor(x);
		xfrm_put_type(x->type);
	पूर्ण
	अगर (x->xfrag.page)
		put_page(x->xfrag.page);
	xfrm_dev_state_मुक्त(x);
	security_xfrm_state_मुक्त(x);
	xfrm_state_मुक्त(x);
पूर्ण

अटल व्योम xfrm_state_gc_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा xfrm_state *x;
	काष्ठा hlist_node *पंचांगp;
	काष्ठा hlist_head gc_list;

	spin_lock_bh(&xfrm_state_gc_lock);
	hlist_move_list(&xfrm_state_gc_list, &gc_list);
	spin_unlock_bh(&xfrm_state_gc_lock);

	synchronize_rcu();

	hlist_क्रम_each_entry_safe(x, पंचांगp, &gc_list, gclist)
		___xfrm_state_destroy(x);
पूर्ण

अटल क्रमागत hrसमयr_restart xfrm_समयr_handler(काष्ठा hrसमयr *me)
अणु
	काष्ठा xfrm_state *x = container_of(me, काष्ठा xfrm_state, mसमयr);
	क्रमागत hrसमयr_restart ret = HRTIMER_NORESTART;
	समय64_t now = kसमय_get_real_seconds();
	समय64_t next = TIME64_MAX;
	पूर्णांक warn = 0;
	पूर्णांक err = 0;

	spin_lock(&x->lock);
	अगर (x->km.state == XFRM_STATE_DEAD)
		जाओ out;
	अगर (x->km.state == XFRM_STATE_EXPIRED)
		जाओ expired;
	अगर (x->lft.hard_add_expires_seconds) अणु
		दीर्घ पंचांगo = x->lft.hard_add_expires_seconds +
			x->curlft.add_समय - now;
		अगर (पंचांगo <= 0) अणु
			अगर (x->xflags & XFRM_SOFT_EXPIRE) अणु
				/* enter hard expire without soft expire first?!
				 * setting a new date could trigger this.
				 * workaround: fix x->curflt.add_समय by below:
				 */
				x->curlft.add_समय = now - x->saved_पंचांगo - 1;
				पंचांगo = x->lft.hard_add_expires_seconds - x->saved_पंचांगo;
			पूर्ण अन्यथा
				जाओ expired;
		पूर्ण
		अगर (पंचांगo < next)
			next = पंचांगo;
	पूर्ण
	अगर (x->lft.hard_use_expires_seconds) अणु
		दीर्घ पंचांगo = x->lft.hard_use_expires_seconds +
			(x->curlft.use_समय ? : now) - now;
		अगर (पंचांगo <= 0)
			जाओ expired;
		अगर (पंचांगo < next)
			next = पंचांगo;
	पूर्ण
	अगर (x->km.dying)
		जाओ resched;
	अगर (x->lft.soft_add_expires_seconds) अणु
		दीर्घ पंचांगo = x->lft.soft_add_expires_seconds +
			x->curlft.add_समय - now;
		अगर (पंचांगo <= 0) अणु
			warn = 1;
			x->xflags &= ~XFRM_SOFT_EXPIRE;
		पूर्ण अन्यथा अगर (पंचांगo < next) अणु
			next = पंचांगo;
			x->xflags |= XFRM_SOFT_EXPIRE;
			x->saved_पंचांगo = पंचांगo;
		पूर्ण
	पूर्ण
	अगर (x->lft.soft_use_expires_seconds) अणु
		दीर्घ पंचांगo = x->lft.soft_use_expires_seconds +
			(x->curlft.use_समय ? : now) - now;
		अगर (पंचांगo <= 0)
			warn = 1;
		अन्यथा अगर (पंचांगo < next)
			next = पंचांगo;
	पूर्ण

	x->km.dying = warn;
	अगर (warn)
		km_state_expired(x, 0, 0);
resched:
	अगर (next != TIME64_MAX) अणु
		hrसमयr_क्रमward_now(&x->mसमयr, kसमय_set(next, 0));
		ret = HRTIMER_RESTART;
	पूर्ण

	जाओ out;

expired:
	अगर (x->km.state == XFRM_STATE_ACQ && x->id.spi == 0)
		x->km.state = XFRM_STATE_EXPIRED;

	err = __xfrm_state_delete(x);
	अगर (!err)
		km_state_expired(x, 1, 0);

	xfrm_audit_state_delete(x, err ? 0 : 1, true);

out:
	spin_unlock(&x->lock);
	वापस ret;
पूर्ण

अटल व्योम xfrm_replay_समयr_handler(काष्ठा समयr_list *t);

काष्ठा xfrm_state *xfrm_state_alloc(काष्ठा net *net)
अणु
	काष्ठा xfrm_state *x;

	x = kmem_cache_zalloc(xfrm_state_cache, GFP_ATOMIC);

	अगर (x) अणु
		ग_लिखो_pnet(&x->xs_net, net);
		refcount_set(&x->refcnt, 1);
		atomic_set(&x->tunnel_users, 0);
		INIT_LIST_HEAD(&x->km.all);
		INIT_HLIST_NODE(&x->bydst);
		INIT_HLIST_NODE(&x->bysrc);
		INIT_HLIST_NODE(&x->byspi);
		hrसमयr_init(&x->mसमयr, CLOCK_BOOTTIME, HRTIMER_MODE_ABS_SOFT);
		x->mसमयr.function = xfrm_समयr_handler;
		समयr_setup(&x->rसमयr, xfrm_replay_समयr_handler, 0);
		x->curlft.add_समय = kसमय_get_real_seconds();
		x->lft.soft_byte_limit = XFRM_INF;
		x->lft.soft_packet_limit = XFRM_INF;
		x->lft.hard_byte_limit = XFRM_INF;
		x->lft.hard_packet_limit = XFRM_INF;
		x->replay_maxage = 0;
		x->replay_maxdअगरf = 0;
		spin_lock_init(&x->lock);
	पूर्ण
	वापस x;
पूर्ण
EXPORT_SYMBOL(xfrm_state_alloc);

व्योम __xfrm_state_destroy(काष्ठा xfrm_state *x, bool sync)
अणु
	WARN_ON(x->km.state != XFRM_STATE_DEAD);

	अगर (sync) अणु
		synchronize_rcu();
		___xfrm_state_destroy(x);
	पूर्ण अन्यथा अणु
		spin_lock_bh(&xfrm_state_gc_lock);
		hlist_add_head(&x->gclist, &xfrm_state_gc_list);
		spin_unlock_bh(&xfrm_state_gc_lock);
		schedule_work(&xfrm_state_gc_work);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__xfrm_state_destroy);

पूर्णांक __xfrm_state_delete(काष्ठा xfrm_state *x)
अणु
	काष्ठा net *net = xs_net(x);
	पूर्णांक err = -ESRCH;

	अगर (x->km.state != XFRM_STATE_DEAD) अणु
		x->km.state = XFRM_STATE_DEAD;
		spin_lock(&net->xfrm.xfrm_state_lock);
		list_del(&x->km.all);
		hlist_del_rcu(&x->bydst);
		hlist_del_rcu(&x->bysrc);
		अगर (x->id.spi)
			hlist_del_rcu(&x->byspi);
		net->xfrm.state_num--;
		spin_unlock(&net->xfrm.xfrm_state_lock);

		अगर (x->encap_sk)
			sock_put(rcu_dereference_raw(x->encap_sk));

		xfrm_dev_state_delete(x);

		/* All xfrm_state objects are created by xfrm_state_alloc.
		 * The xfrm_state_alloc call gives a reference, and that
		 * is what we are dropping here.
		 */
		xfrm_state_put(x);
		err = 0;
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL(__xfrm_state_delete);

पूर्णांक xfrm_state_delete(काष्ठा xfrm_state *x)
अणु
	पूर्णांक err;

	spin_lock_bh(&x->lock);
	err = __xfrm_state_delete(x);
	spin_unlock_bh(&x->lock);

	वापस err;
पूर्ण
EXPORT_SYMBOL(xfrm_state_delete);

#अगर_घोषित CONFIG_SECURITY_NETWORK_XFRM
अटल अंतरभूत पूर्णांक
xfrm_state_flush_secctx_check(काष्ठा net *net, u8 proto, bool task_valid)
अणु
	पूर्णांक i, err = 0;

	क्रम (i = 0; i <= net->xfrm.state_hmask; i++) अणु
		काष्ठा xfrm_state *x;

		hlist_क्रम_each_entry(x, net->xfrm.state_bydst+i, bydst) अणु
			अगर (xfrm_id_proto_match(x->id.proto, proto) &&
			   (err = security_xfrm_state_delete(x)) != 0) अणु
				xfrm_audit_state_delete(x, 0, task_valid);
				वापस err;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक
xfrm_dev_state_flush_secctx_check(काष्ठा net *net, काष्ठा net_device *dev, bool task_valid)
अणु
	पूर्णांक i, err = 0;

	क्रम (i = 0; i <= net->xfrm.state_hmask; i++) अणु
		काष्ठा xfrm_state *x;
		काष्ठा xfrm_state_offload *xso;

		hlist_क्रम_each_entry(x, net->xfrm.state_bydst+i, bydst) अणु
			xso = &x->xso;

			अगर (xso->dev == dev &&
			   (err = security_xfrm_state_delete(x)) != 0) अणु
				xfrm_audit_state_delete(x, 0, task_valid);
				वापस err;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक
xfrm_state_flush_secctx_check(काष्ठा net *net, u8 proto, bool task_valid)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
xfrm_dev_state_flush_secctx_check(काष्ठा net *net, काष्ठा net_device *dev, bool task_valid)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

पूर्णांक xfrm_state_flush(काष्ठा net *net, u8 proto, bool task_valid, bool sync)
अणु
	पूर्णांक i, err = 0, cnt = 0;

	spin_lock_bh(&net->xfrm.xfrm_state_lock);
	err = xfrm_state_flush_secctx_check(net, proto, task_valid);
	अगर (err)
		जाओ out;

	err = -ESRCH;
	क्रम (i = 0; i <= net->xfrm.state_hmask; i++) अणु
		काष्ठा xfrm_state *x;
restart:
		hlist_क्रम_each_entry(x, net->xfrm.state_bydst+i, bydst) अणु
			अगर (!xfrm_state_kern(x) &&
			    xfrm_id_proto_match(x->id.proto, proto)) अणु
				xfrm_state_hold(x);
				spin_unlock_bh(&net->xfrm.xfrm_state_lock);

				err = xfrm_state_delete(x);
				xfrm_audit_state_delete(x, err ? 0 : 1,
							task_valid);
				अगर (sync)
					xfrm_state_put_sync(x);
				अन्यथा
					xfrm_state_put(x);
				अगर (!err)
					cnt++;

				spin_lock_bh(&net->xfrm.xfrm_state_lock);
				जाओ restart;
			पूर्ण
		पूर्ण
	पूर्ण
out:
	spin_unlock_bh(&net->xfrm.xfrm_state_lock);
	अगर (cnt)
		err = 0;

	वापस err;
पूर्ण
EXPORT_SYMBOL(xfrm_state_flush);

पूर्णांक xfrm_dev_state_flush(काष्ठा net *net, काष्ठा net_device *dev, bool task_valid)
अणु
	पूर्णांक i, err = 0, cnt = 0;

	spin_lock_bh(&net->xfrm.xfrm_state_lock);
	err = xfrm_dev_state_flush_secctx_check(net, dev, task_valid);
	अगर (err)
		जाओ out;

	err = -ESRCH;
	क्रम (i = 0; i <= net->xfrm.state_hmask; i++) अणु
		काष्ठा xfrm_state *x;
		काष्ठा xfrm_state_offload *xso;
restart:
		hlist_क्रम_each_entry(x, net->xfrm.state_bydst+i, bydst) अणु
			xso = &x->xso;

			अगर (!xfrm_state_kern(x) && xso->dev == dev) अणु
				xfrm_state_hold(x);
				spin_unlock_bh(&net->xfrm.xfrm_state_lock);

				err = xfrm_state_delete(x);
				xfrm_audit_state_delete(x, err ? 0 : 1,
							task_valid);
				xfrm_state_put(x);
				अगर (!err)
					cnt++;

				spin_lock_bh(&net->xfrm.xfrm_state_lock);
				जाओ restart;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (cnt)
		err = 0;

out:
	spin_unlock_bh(&net->xfrm.xfrm_state_lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL(xfrm_dev_state_flush);

व्योम xfrm_sad_getinfo(काष्ठा net *net, काष्ठा xfrmk_sadinfo *si)
अणु
	spin_lock_bh(&net->xfrm.xfrm_state_lock);
	si->sadcnt = net->xfrm.state_num;
	si->sadhcnt = net->xfrm.state_hmask + 1;
	si->sadhmcnt = xfrm_state_hashmax;
	spin_unlock_bh(&net->xfrm.xfrm_state_lock);
पूर्ण
EXPORT_SYMBOL(xfrm_sad_getinfo);

अटल व्योम
__xfrm4_init_tempsel(काष्ठा xfrm_selector *sel, स्थिर काष्ठा flowi *fl)
अणु
	स्थिर काष्ठा flowi4 *fl4 = &fl->u.ip4;

	sel->daddr.a4 = fl4->daddr;
	sel->saddr.a4 = fl4->saddr;
	sel->dport = xfrm_flowi_dport(fl, &fl4->uli);
	sel->dport_mask = htons(0xffff);
	sel->sport = xfrm_flowi_sport(fl, &fl4->uli);
	sel->sport_mask = htons(0xffff);
	sel->family = AF_INET;
	sel->prefixlen_d = 32;
	sel->prefixlen_s = 32;
	sel->proto = fl4->flowi4_proto;
	sel->अगरindex = fl4->flowi4_oअगर;
पूर्ण

अटल व्योम
__xfrm6_init_tempsel(काष्ठा xfrm_selector *sel, स्थिर काष्ठा flowi *fl)
अणु
	स्थिर काष्ठा flowi6 *fl6 = &fl->u.ip6;

	/* Initialize temporary selector matching only to current session. */
	*(काष्ठा in6_addr *)&sel->daddr = fl6->daddr;
	*(काष्ठा in6_addr *)&sel->saddr = fl6->saddr;
	sel->dport = xfrm_flowi_dport(fl, &fl6->uli);
	sel->dport_mask = htons(0xffff);
	sel->sport = xfrm_flowi_sport(fl, &fl6->uli);
	sel->sport_mask = htons(0xffff);
	sel->family = AF_INET6;
	sel->prefixlen_d = 128;
	sel->prefixlen_s = 128;
	sel->proto = fl6->flowi6_proto;
	sel->अगरindex = fl6->flowi6_oअगर;
पूर्ण

अटल व्योम
xfrm_init_tempstate(काष्ठा xfrm_state *x, स्थिर काष्ठा flowi *fl,
		    स्थिर काष्ठा xfrm_पंचांगpl *पंचांगpl,
		    स्थिर xfrm_address_t *daddr, स्थिर xfrm_address_t *saddr,
		    अचिन्हित लघु family)
अणु
	चयन (family) अणु
	हाल AF_INET:
		__xfrm4_init_tempsel(&x->sel, fl);
		अवरोध;
	हाल AF_INET6:
		__xfrm6_init_tempsel(&x->sel, fl);
		अवरोध;
	पूर्ण

	x->id = पंचांगpl->id;

	चयन (पंचांगpl->encap_family) अणु
	हाल AF_INET:
		अगर (x->id.daddr.a4 == 0)
			x->id.daddr.a4 = daddr->a4;
		x->props.saddr = पंचांगpl->saddr;
		अगर (x->props.saddr.a4 == 0)
			x->props.saddr.a4 = saddr->a4;
		अवरोध;
	हाल AF_INET6:
		अगर (ipv6_addr_any((काष्ठा in6_addr *)&x->id.daddr))
			स_नकल(&x->id.daddr, daddr, माप(x->sel.daddr));
		स_नकल(&x->props.saddr, &पंचांगpl->saddr, माप(x->props.saddr));
		अगर (ipv6_addr_any((काष्ठा in6_addr *)&x->props.saddr))
			स_नकल(&x->props.saddr, saddr, माप(x->props.saddr));
		अवरोध;
	पूर्ण

	x->props.mode = पंचांगpl->mode;
	x->props.reqid = पंचांगpl->reqid;
	x->props.family = पंचांगpl->encap_family;
पूर्ण

अटल काष्ठा xfrm_state *__xfrm_state_lookup(काष्ठा net *net, u32 mark,
					      स्थिर xfrm_address_t *daddr,
					      __be32 spi, u8 proto,
					      अचिन्हित लघु family)
अणु
	अचिन्हित पूर्णांक h = xfrm_spi_hash(net, daddr, spi, proto, family);
	काष्ठा xfrm_state *x;

	hlist_क्रम_each_entry_rcu(x, net->xfrm.state_byspi + h, byspi) अणु
		अगर (x->props.family != family ||
		    x->id.spi       != spi ||
		    x->id.proto     != proto ||
		    !xfrm_addr_equal(&x->id.daddr, daddr, family))
			जारी;

		अगर ((mark & x->mark.m) != x->mark.v)
			जारी;
		अगर (!xfrm_state_hold_rcu(x))
			जारी;
		वापस x;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा xfrm_state *__xfrm_state_lookup_byaddr(काष्ठा net *net, u32 mark,
						     स्थिर xfrm_address_t *daddr,
						     स्थिर xfrm_address_t *saddr,
						     u8 proto, अचिन्हित लघु family)
अणु
	अचिन्हित पूर्णांक h = xfrm_src_hash(net, daddr, saddr, family);
	काष्ठा xfrm_state *x;

	hlist_क्रम_each_entry_rcu(x, net->xfrm.state_bysrc + h, bysrc) अणु
		अगर (x->props.family != family ||
		    x->id.proto     != proto ||
		    !xfrm_addr_equal(&x->id.daddr, daddr, family) ||
		    !xfrm_addr_equal(&x->props.saddr, saddr, family))
			जारी;

		अगर ((mark & x->mark.m) != x->mark.v)
			जारी;
		अगर (!xfrm_state_hold_rcu(x))
			जारी;
		वापस x;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा xfrm_state *
__xfrm_state_locate(काष्ठा xfrm_state *x, पूर्णांक use_spi, पूर्णांक family)
अणु
	काष्ठा net *net = xs_net(x);
	u32 mark = x->mark.v & x->mark.m;

	अगर (use_spi)
		वापस __xfrm_state_lookup(net, mark, &x->id.daddr,
					   x->id.spi, x->id.proto, family);
	अन्यथा
		वापस __xfrm_state_lookup_byaddr(net, mark,
						  &x->id.daddr,
						  &x->props.saddr,
						  x->id.proto, family);
पूर्ण

अटल व्योम xfrm_hash_grow_check(काष्ठा net *net, पूर्णांक have_hash_collision)
अणु
	अगर (have_hash_collision &&
	    (net->xfrm.state_hmask + 1) < xfrm_state_hashmax &&
	    net->xfrm.state_num > net->xfrm.state_hmask)
		schedule_work(&net->xfrm.state_hash_work);
पूर्ण

अटल व्योम xfrm_state_look_at(काष्ठा xfrm_policy *pol, काष्ठा xfrm_state *x,
			       स्थिर काष्ठा flowi *fl, अचिन्हित लघु family,
			       काष्ठा xfrm_state **best, पूर्णांक *acq_in_progress,
			       पूर्णांक *error)
अणु
	/* Resolution logic:
	 * 1. There is a valid state with matching selector. Done.
	 * 2. Valid state with inappropriate selector. Skip.
	 *
	 * Entering area of "sysdeps".
	 *
	 * 3. If state is not valid, selector is temporary, it selects
	 *    only session which triggered previous resolution. Key
	 *    manager will करो something to install a state with proper
	 *    selector.
	 */
	अगर (x->km.state == XFRM_STATE_VALID) अणु
		अगर ((x->sel.family &&
		     (x->sel.family != family ||
		      !xfrm_selector_match(&x->sel, fl, family))) ||
		    !security_xfrm_state_pol_flow_match(x, pol,
							&fl->u.__fl_common))
			वापस;

		अगर (!*best ||
		    (*best)->km.dying > x->km.dying ||
		    ((*best)->km.dying == x->km.dying &&
		     (*best)->curlft.add_समय < x->curlft.add_समय))
			*best = x;
	पूर्ण अन्यथा अगर (x->km.state == XFRM_STATE_ACQ) अणु
		*acq_in_progress = 1;
	पूर्ण अन्यथा अगर (x->km.state == XFRM_STATE_ERROR ||
		   x->km.state == XFRM_STATE_EXPIRED) अणु
		अगर ((!x->sel.family ||
		     (x->sel.family == family &&
		      xfrm_selector_match(&x->sel, fl, family))) &&
		    security_xfrm_state_pol_flow_match(x, pol,
						       &fl->u.__fl_common))
			*error = -ESRCH;
	पूर्ण
पूर्ण

काष्ठा xfrm_state *
xfrm_state_find(स्थिर xfrm_address_t *daddr, स्थिर xfrm_address_t *saddr,
		स्थिर काष्ठा flowi *fl, काष्ठा xfrm_पंचांगpl *पंचांगpl,
		काष्ठा xfrm_policy *pol, पूर्णांक *err,
		अचिन्हित लघु family, u32 अगर_id)
अणु
	अटल xfrm_address_t saddr_wildcard = अणु पूर्ण;
	काष्ठा net *net = xp_net(pol);
	अचिन्हित पूर्णांक h, h_wildcard;
	काष्ठा xfrm_state *x, *x0, *to_put;
	पूर्णांक acquire_in_progress = 0;
	पूर्णांक error = 0;
	काष्ठा xfrm_state *best = शून्य;
	u32 mark = pol->mark.v & pol->mark.m;
	अचिन्हित लघु encap_family = पंचांगpl->encap_family;
	अचिन्हित पूर्णांक sequence;
	काष्ठा km_event c;

	to_put = शून्य;

	sequence = पढ़ो_seqcount_begin(&net->xfrm.xfrm_state_hash_generation);

	rcu_पढ़ो_lock();
	h = xfrm_dst_hash(net, daddr, saddr, पंचांगpl->reqid, encap_family);
	hlist_क्रम_each_entry_rcu(x, net->xfrm.state_bydst + h, bydst) अणु
		अगर (x->props.family == encap_family &&
		    x->props.reqid == पंचांगpl->reqid &&
		    (mark & x->mark.m) == x->mark.v &&
		    x->अगर_id == अगर_id &&
		    !(x->props.flags & XFRM_STATE_WILDRECV) &&
		    xfrm_state_addr_check(x, daddr, saddr, encap_family) &&
		    पंचांगpl->mode == x->props.mode &&
		    पंचांगpl->id.proto == x->id.proto &&
		    (पंचांगpl->id.spi == x->id.spi || !पंचांगpl->id.spi))
			xfrm_state_look_at(pol, x, fl, family,
					   &best, &acquire_in_progress, &error);
	पूर्ण
	अगर (best || acquire_in_progress)
		जाओ found;

	h_wildcard = xfrm_dst_hash(net, daddr, &saddr_wildcard, पंचांगpl->reqid, encap_family);
	hlist_क्रम_each_entry_rcu(x, net->xfrm.state_bydst + h_wildcard, bydst) अणु
		अगर (x->props.family == encap_family &&
		    x->props.reqid == पंचांगpl->reqid &&
		    (mark & x->mark.m) == x->mark.v &&
		    x->अगर_id == अगर_id &&
		    !(x->props.flags & XFRM_STATE_WILDRECV) &&
		    xfrm_addr_equal(&x->id.daddr, daddr, encap_family) &&
		    पंचांगpl->mode == x->props.mode &&
		    पंचांगpl->id.proto == x->id.proto &&
		    (पंचांगpl->id.spi == x->id.spi || !पंचांगpl->id.spi))
			xfrm_state_look_at(pol, x, fl, family,
					   &best, &acquire_in_progress, &error);
	पूर्ण

found:
	x = best;
	अगर (!x && !error && !acquire_in_progress) अणु
		अगर (पंचांगpl->id.spi &&
		    (x0 = __xfrm_state_lookup(net, mark, daddr, पंचांगpl->id.spi,
					      पंचांगpl->id.proto, encap_family)) != शून्य) अणु
			to_put = x0;
			error = -EEXIST;
			जाओ out;
		पूर्ण

		c.net = net;
		/* If the KMs have no listeners (yet...), aव्योम allocating an SA
		 * क्रम each and every packet - garbage collection might not
		 * handle the flood.
		 */
		अगर (!km_is_alive(&c)) अणु
			error = -ESRCH;
			जाओ out;
		पूर्ण

		x = xfrm_state_alloc(net);
		अगर (x == शून्य) अणु
			error = -ENOMEM;
			जाओ out;
		पूर्ण
		/* Initialize temporary state matching only
		 * to current session. */
		xfrm_init_tempstate(x, fl, पंचांगpl, daddr, saddr, family);
		स_नकल(&x->mark, &pol->mark, माप(x->mark));
		x->अगर_id = अगर_id;

		error = security_xfrm_state_alloc_acquire(x, pol->security, fl->flowi_secid);
		अगर (error) अणु
			x->km.state = XFRM_STATE_DEAD;
			to_put = x;
			x = शून्य;
			जाओ out;
		पूर्ण

		अगर (km_query(x, पंचांगpl, pol) == 0) अणु
			spin_lock_bh(&net->xfrm.xfrm_state_lock);
			x->km.state = XFRM_STATE_ACQ;
			list_add(&x->km.all, &net->xfrm.state_all);
			hlist_add_head_rcu(&x->bydst, net->xfrm.state_bydst + h);
			h = xfrm_src_hash(net, daddr, saddr, encap_family);
			hlist_add_head_rcu(&x->bysrc, net->xfrm.state_bysrc + h);
			अगर (x->id.spi) अणु
				h = xfrm_spi_hash(net, &x->id.daddr, x->id.spi, x->id.proto, encap_family);
				hlist_add_head_rcu(&x->byspi, net->xfrm.state_byspi + h);
			पूर्ण
			x->lft.hard_add_expires_seconds = net->xfrm.sysctl_acq_expires;
			hrसमयr_start(&x->mसमयr,
				      kसमय_set(net->xfrm.sysctl_acq_expires, 0),
				      HRTIMER_MODE_REL_SOFT);
			net->xfrm.state_num++;
			xfrm_hash_grow_check(net, x->bydst.next != शून्य);
			spin_unlock_bh(&net->xfrm.xfrm_state_lock);
		पूर्ण अन्यथा अणु
			x->km.state = XFRM_STATE_DEAD;
			to_put = x;
			x = शून्य;
			error = -ESRCH;
		पूर्ण
	पूर्ण
out:
	अगर (x) अणु
		अगर (!xfrm_state_hold_rcu(x)) अणु
			*err = -EAGAIN;
			x = शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		*err = acquire_in_progress ? -EAGAIN : error;
	पूर्ण
	rcu_पढ़ो_unlock();
	अगर (to_put)
		xfrm_state_put(to_put);

	अगर (पढ़ो_seqcount_retry(&net->xfrm.xfrm_state_hash_generation, sequence)) अणु
		*err = -EAGAIN;
		अगर (x) अणु
			xfrm_state_put(x);
			x = शून्य;
		पूर्ण
	पूर्ण

	वापस x;
पूर्ण

काष्ठा xfrm_state *
xfrm_stateonly_find(काष्ठा net *net, u32 mark, u32 अगर_id,
		    xfrm_address_t *daddr, xfrm_address_t *saddr,
		    अचिन्हित लघु family, u8 mode, u8 proto, u32 reqid)
अणु
	अचिन्हित पूर्णांक h;
	काष्ठा xfrm_state *rx = शून्य, *x = शून्य;

	spin_lock_bh(&net->xfrm.xfrm_state_lock);
	h = xfrm_dst_hash(net, daddr, saddr, reqid, family);
	hlist_क्रम_each_entry(x, net->xfrm.state_bydst+h, bydst) अणु
		अगर (x->props.family == family &&
		    x->props.reqid == reqid &&
		    (mark & x->mark.m) == x->mark.v &&
		    x->अगर_id == अगर_id &&
		    !(x->props.flags & XFRM_STATE_WILDRECV) &&
		    xfrm_state_addr_check(x, daddr, saddr, family) &&
		    mode == x->props.mode &&
		    proto == x->id.proto &&
		    x->km.state == XFRM_STATE_VALID) अणु
			rx = x;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (rx)
		xfrm_state_hold(rx);
	spin_unlock_bh(&net->xfrm.xfrm_state_lock);


	वापस rx;
पूर्ण
EXPORT_SYMBOL(xfrm_stateonly_find);

काष्ठा xfrm_state *xfrm_state_lookup_byspi(काष्ठा net *net, __be32 spi,
					      अचिन्हित लघु family)
अणु
	काष्ठा xfrm_state *x;
	काष्ठा xfrm_state_walk *w;

	spin_lock_bh(&net->xfrm.xfrm_state_lock);
	list_क्रम_each_entry(w, &net->xfrm.state_all, all) अणु
		x = container_of(w, काष्ठा xfrm_state, km);
		अगर (x->props.family != family ||
			x->id.spi != spi)
			जारी;

		xfrm_state_hold(x);
		spin_unlock_bh(&net->xfrm.xfrm_state_lock);
		वापस x;
	पूर्ण
	spin_unlock_bh(&net->xfrm.xfrm_state_lock);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(xfrm_state_lookup_byspi);

अटल व्योम __xfrm_state_insert(काष्ठा xfrm_state *x)
अणु
	काष्ठा net *net = xs_net(x);
	अचिन्हित पूर्णांक h;

	list_add(&x->km.all, &net->xfrm.state_all);

	h = xfrm_dst_hash(net, &x->id.daddr, &x->props.saddr,
			  x->props.reqid, x->props.family);
	hlist_add_head_rcu(&x->bydst, net->xfrm.state_bydst + h);

	h = xfrm_src_hash(net, &x->id.daddr, &x->props.saddr, x->props.family);
	hlist_add_head_rcu(&x->bysrc, net->xfrm.state_bysrc + h);

	अगर (x->id.spi) अणु
		h = xfrm_spi_hash(net, &x->id.daddr, x->id.spi, x->id.proto,
				  x->props.family);

		hlist_add_head_rcu(&x->byspi, net->xfrm.state_byspi + h);
	पूर्ण

	hrसमयr_start(&x->mसमयr, kसमय_set(1, 0), HRTIMER_MODE_REL_SOFT);
	अगर (x->replay_maxage)
		mod_समयr(&x->rसमयr, jअगरfies + x->replay_maxage);

	net->xfrm.state_num++;

	xfrm_hash_grow_check(net, x->bydst.next != शून्य);
पूर्ण

/* net->xfrm.xfrm_state_lock is held */
अटल व्योम __xfrm_state_bump_genids(काष्ठा xfrm_state *xnew)
अणु
	काष्ठा net *net = xs_net(xnew);
	अचिन्हित लघु family = xnew->props.family;
	u32 reqid = xnew->props.reqid;
	काष्ठा xfrm_state *x;
	अचिन्हित पूर्णांक h;
	u32 mark = xnew->mark.v & xnew->mark.m;
	u32 अगर_id = xnew->अगर_id;

	h = xfrm_dst_hash(net, &xnew->id.daddr, &xnew->props.saddr, reqid, family);
	hlist_क्रम_each_entry(x, net->xfrm.state_bydst+h, bydst) अणु
		अगर (x->props.family	== family &&
		    x->props.reqid	== reqid &&
		    x->अगर_id		== अगर_id &&
		    (mark & x->mark.m) == x->mark.v &&
		    xfrm_addr_equal(&x->id.daddr, &xnew->id.daddr, family) &&
		    xfrm_addr_equal(&x->props.saddr, &xnew->props.saddr, family))
			x->genid++;
	पूर्ण
पूर्ण

व्योम xfrm_state_insert(काष्ठा xfrm_state *x)
अणु
	काष्ठा net *net = xs_net(x);

	spin_lock_bh(&net->xfrm.xfrm_state_lock);
	__xfrm_state_bump_genids(x);
	__xfrm_state_insert(x);
	spin_unlock_bh(&net->xfrm.xfrm_state_lock);
पूर्ण
EXPORT_SYMBOL(xfrm_state_insert);

/* net->xfrm.xfrm_state_lock is held */
अटल काष्ठा xfrm_state *__find_acq_core(काष्ठा net *net,
					  स्थिर काष्ठा xfrm_mark *m,
					  अचिन्हित लघु family, u8 mode,
					  u32 reqid, u32 अगर_id, u8 proto,
					  स्थिर xfrm_address_t *daddr,
					  स्थिर xfrm_address_t *saddr,
					  पूर्णांक create)
अणु
	अचिन्हित पूर्णांक h = xfrm_dst_hash(net, daddr, saddr, reqid, family);
	काष्ठा xfrm_state *x;
	u32 mark = m->v & m->m;

	hlist_क्रम_each_entry(x, net->xfrm.state_bydst+h, bydst) अणु
		अगर (x->props.reqid  != reqid ||
		    x->props.mode   != mode ||
		    x->props.family != family ||
		    x->km.state     != XFRM_STATE_ACQ ||
		    x->id.spi       != 0 ||
		    x->id.proto	    != proto ||
		    (mark & x->mark.m) != x->mark.v ||
		    !xfrm_addr_equal(&x->id.daddr, daddr, family) ||
		    !xfrm_addr_equal(&x->props.saddr, saddr, family))
			जारी;

		xfrm_state_hold(x);
		वापस x;
	पूर्ण

	अगर (!create)
		वापस शून्य;

	x = xfrm_state_alloc(net);
	अगर (likely(x)) अणु
		चयन (family) अणु
		हाल AF_INET:
			x->sel.daddr.a4 = daddr->a4;
			x->sel.saddr.a4 = saddr->a4;
			x->sel.prefixlen_d = 32;
			x->sel.prefixlen_s = 32;
			x->props.saddr.a4 = saddr->a4;
			x->id.daddr.a4 = daddr->a4;
			अवरोध;

		हाल AF_INET6:
			x->sel.daddr.in6 = daddr->in6;
			x->sel.saddr.in6 = saddr->in6;
			x->sel.prefixlen_d = 128;
			x->sel.prefixlen_s = 128;
			x->props.saddr.in6 = saddr->in6;
			x->id.daddr.in6 = daddr->in6;
			अवरोध;
		पूर्ण

		x->km.state = XFRM_STATE_ACQ;
		x->id.proto = proto;
		x->props.family = family;
		x->props.mode = mode;
		x->props.reqid = reqid;
		x->अगर_id = अगर_id;
		x->mark.v = m->v;
		x->mark.m = m->m;
		x->lft.hard_add_expires_seconds = net->xfrm.sysctl_acq_expires;
		xfrm_state_hold(x);
		hrसमयr_start(&x->mसमयr,
			      kसमय_set(net->xfrm.sysctl_acq_expires, 0),
			      HRTIMER_MODE_REL_SOFT);
		list_add(&x->km.all, &net->xfrm.state_all);
		hlist_add_head_rcu(&x->bydst, net->xfrm.state_bydst + h);
		h = xfrm_src_hash(net, daddr, saddr, family);
		hlist_add_head_rcu(&x->bysrc, net->xfrm.state_bysrc + h);

		net->xfrm.state_num++;

		xfrm_hash_grow_check(net, x->bydst.next != शून्य);
	पूर्ण

	वापस x;
पूर्ण

अटल काष्ठा xfrm_state *__xfrm_find_acq_byseq(काष्ठा net *net, u32 mark, u32 seq);

पूर्णांक xfrm_state_add(काष्ठा xfrm_state *x)
अणु
	काष्ठा net *net = xs_net(x);
	काष्ठा xfrm_state *x1, *to_put;
	पूर्णांक family;
	पूर्णांक err;
	u32 mark = x->mark.v & x->mark.m;
	पूर्णांक use_spi = xfrm_id_proto_match(x->id.proto, IPSEC_PROTO_ANY);

	family = x->props.family;

	to_put = शून्य;

	spin_lock_bh(&net->xfrm.xfrm_state_lock);

	x1 = __xfrm_state_locate(x, use_spi, family);
	अगर (x1) अणु
		to_put = x1;
		x1 = शून्य;
		err = -EEXIST;
		जाओ out;
	पूर्ण

	अगर (use_spi && x->km.seq) अणु
		x1 = __xfrm_find_acq_byseq(net, mark, x->km.seq);
		अगर (x1 && ((x1->id.proto != x->id.proto) ||
		    !xfrm_addr_equal(&x1->id.daddr, &x->id.daddr, family))) अणु
			to_put = x1;
			x1 = शून्य;
		पूर्ण
	पूर्ण

	अगर (use_spi && !x1)
		x1 = __find_acq_core(net, &x->mark, family, x->props.mode,
				     x->props.reqid, x->अगर_id, x->id.proto,
				     &x->id.daddr, &x->props.saddr, 0);

	__xfrm_state_bump_genids(x);
	__xfrm_state_insert(x);
	err = 0;

out:
	spin_unlock_bh(&net->xfrm.xfrm_state_lock);

	अगर (x1) अणु
		xfrm_state_delete(x1);
		xfrm_state_put(x1);
	पूर्ण

	अगर (to_put)
		xfrm_state_put(to_put);

	वापस err;
पूर्ण
EXPORT_SYMBOL(xfrm_state_add);

#अगर_घोषित CONFIG_XFRM_MIGRATE
अटल अंतरभूत पूर्णांक clone_security(काष्ठा xfrm_state *x, काष्ठा xfrm_sec_ctx *security)
अणु
	काष्ठा xfrm_user_sec_ctx *uctx;
	पूर्णांक size = माप(*uctx) + security->ctx_len;
	पूर्णांक err;

	uctx = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!uctx)
		वापस -ENOMEM;

	uctx->exttype = XFRMA_SEC_CTX;
	uctx->len = size;
	uctx->ctx_करोi = security->ctx_करोi;
	uctx->ctx_alg = security->ctx_alg;
	uctx->ctx_len = security->ctx_len;
	स_नकल(uctx + 1, security->ctx_str, security->ctx_len);
	err = security_xfrm_state_alloc(x, uctx);
	kमुक्त(uctx);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल काष्ठा xfrm_state *xfrm_state_clone(काष्ठा xfrm_state *orig,
					   काष्ठा xfrm_encap_पंचांगpl *encap)
अणु
	काष्ठा net *net = xs_net(orig);
	काष्ठा xfrm_state *x = xfrm_state_alloc(net);
	अगर (!x)
		जाओ out;

	स_नकल(&x->id, &orig->id, माप(x->id));
	स_नकल(&x->sel, &orig->sel, माप(x->sel));
	स_नकल(&x->lft, &orig->lft, माप(x->lft));
	x->props.mode = orig->props.mode;
	x->props.replay_winकरोw = orig->props.replay_winकरोw;
	x->props.reqid = orig->props.reqid;
	x->props.family = orig->props.family;
	x->props.saddr = orig->props.saddr;

	अगर (orig->aalg) अणु
		x->aalg = xfrm_algo_auth_clone(orig->aalg);
		अगर (!x->aalg)
			जाओ error;
	पूर्ण
	x->props.aalgo = orig->props.aalgo;

	अगर (orig->aead) अणु
		x->aead = xfrm_algo_aead_clone(orig->aead);
		x->geniv = orig->geniv;
		अगर (!x->aead)
			जाओ error;
	पूर्ण
	अगर (orig->ealg) अणु
		x->ealg = xfrm_algo_clone(orig->ealg);
		अगर (!x->ealg)
			जाओ error;
	पूर्ण
	x->props.ealgo = orig->props.ealgo;

	अगर (orig->calg) अणु
		x->calg = xfrm_algo_clone(orig->calg);
		अगर (!x->calg)
			जाओ error;
	पूर्ण
	x->props.calgo = orig->props.calgo;

	अगर (encap || orig->encap) अणु
		अगर (encap)
			x->encap = kmemdup(encap, माप(*x->encap),
					GFP_KERNEL);
		अन्यथा
			x->encap = kmemdup(orig->encap, माप(*x->encap),
					GFP_KERNEL);

		अगर (!x->encap)
			जाओ error;
	पूर्ण

	अगर (orig->security)
		अगर (clone_security(x, orig->security))
			जाओ error;

	अगर (orig->coaddr) अणु
		x->coaddr = kmemdup(orig->coaddr, माप(*x->coaddr),
				    GFP_KERNEL);
		अगर (!x->coaddr)
			जाओ error;
	पूर्ण

	अगर (orig->replay_esn) अणु
		अगर (xfrm_replay_clone(x, orig))
			जाओ error;
	पूर्ण

	स_नकल(&x->mark, &orig->mark, माप(x->mark));
	स_नकल(&x->props.smark, &orig->props.smark, माप(x->props.smark));

	अगर (xfrm_init_state(x) < 0)
		जाओ error;

	x->props.flags = orig->props.flags;
	x->props.extra_flags = orig->props.extra_flags;

	x->अगर_id = orig->अगर_id;
	x->tfcpad = orig->tfcpad;
	x->replay_maxdअगरf = orig->replay_maxdअगरf;
	x->replay_maxage = orig->replay_maxage;
	स_नकल(&x->curlft, &orig->curlft, माप(x->curlft));
	x->km.state = orig->km.state;
	x->km.seq = orig->km.seq;
	x->replay = orig->replay;
	x->preplay = orig->preplay;

	वापस x;

 error:
	xfrm_state_put(x);
out:
	वापस शून्य;
पूर्ण

काष्ठा xfrm_state *xfrm_migrate_state_find(काष्ठा xfrm_migrate *m, काष्ठा net *net)
अणु
	अचिन्हित पूर्णांक h;
	काष्ठा xfrm_state *x = शून्य;

	spin_lock_bh(&net->xfrm.xfrm_state_lock);

	अगर (m->reqid) अणु
		h = xfrm_dst_hash(net, &m->old_daddr, &m->old_saddr,
				  m->reqid, m->old_family);
		hlist_क्रम_each_entry(x, net->xfrm.state_bydst+h, bydst) अणु
			अगर (x->props.mode != m->mode ||
			    x->id.proto != m->proto)
				जारी;
			अगर (m->reqid && x->props.reqid != m->reqid)
				जारी;
			अगर (!xfrm_addr_equal(&x->id.daddr, &m->old_daddr,
					     m->old_family) ||
			    !xfrm_addr_equal(&x->props.saddr, &m->old_saddr,
					     m->old_family))
				जारी;
			xfrm_state_hold(x);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		h = xfrm_src_hash(net, &m->old_daddr, &m->old_saddr,
				  m->old_family);
		hlist_क्रम_each_entry(x, net->xfrm.state_bysrc+h, bysrc) अणु
			अगर (x->props.mode != m->mode ||
			    x->id.proto != m->proto)
				जारी;
			अगर (!xfrm_addr_equal(&x->id.daddr, &m->old_daddr,
					     m->old_family) ||
			    !xfrm_addr_equal(&x->props.saddr, &m->old_saddr,
					     m->old_family))
				जारी;
			xfrm_state_hold(x);
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_bh(&net->xfrm.xfrm_state_lock);

	वापस x;
पूर्ण
EXPORT_SYMBOL(xfrm_migrate_state_find);

काष्ठा xfrm_state *xfrm_state_migrate(काष्ठा xfrm_state *x,
				      काष्ठा xfrm_migrate *m,
				      काष्ठा xfrm_encap_पंचांगpl *encap)
अणु
	काष्ठा xfrm_state *xc;

	xc = xfrm_state_clone(x, encap);
	अगर (!xc)
		वापस शून्य;

	स_नकल(&xc->id.daddr, &m->new_daddr, माप(xc->id.daddr));
	स_नकल(&xc->props.saddr, &m->new_saddr, माप(xc->props.saddr));

	/* add state */
	अगर (xfrm_addr_equal(&x->id.daddr, &m->new_daddr, m->new_family)) अणु
		/* a care is needed when the destination address of the
		   state is to be updated as it is a part of triplet */
		xfrm_state_insert(xc);
	पूर्ण अन्यथा अणु
		अगर (xfrm_state_add(xc) < 0)
			जाओ error;
	पूर्ण

	वापस xc;
error:
	xfrm_state_put(xc);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(xfrm_state_migrate);
#पूर्ण_अगर

पूर्णांक xfrm_state_update(काष्ठा xfrm_state *x)
अणु
	काष्ठा xfrm_state *x1, *to_put;
	पूर्णांक err;
	पूर्णांक use_spi = xfrm_id_proto_match(x->id.proto, IPSEC_PROTO_ANY);
	काष्ठा net *net = xs_net(x);

	to_put = शून्य;

	spin_lock_bh(&net->xfrm.xfrm_state_lock);
	x1 = __xfrm_state_locate(x, use_spi, x->props.family);

	err = -ESRCH;
	अगर (!x1)
		जाओ out;

	अगर (xfrm_state_kern(x1)) अणु
		to_put = x1;
		err = -EEXIST;
		जाओ out;
	पूर्ण

	अगर (x1->km.state == XFRM_STATE_ACQ) अणु
		__xfrm_state_insert(x);
		x = शून्य;
	पूर्ण
	err = 0;

out:
	spin_unlock_bh(&net->xfrm.xfrm_state_lock);

	अगर (to_put)
		xfrm_state_put(to_put);

	अगर (err)
		वापस err;

	अगर (!x) अणु
		xfrm_state_delete(x1);
		xfrm_state_put(x1);
		वापस 0;
	पूर्ण

	err = -EINVAL;
	spin_lock_bh(&x1->lock);
	अगर (likely(x1->km.state == XFRM_STATE_VALID)) अणु
		अगर (x->encap && x1->encap &&
		    x->encap->encap_type == x1->encap->encap_type)
			स_नकल(x1->encap, x->encap, माप(*x1->encap));
		अन्यथा अगर (x->encap || x1->encap)
			जाओ fail;

		अगर (x->coaddr && x1->coaddr) अणु
			स_नकल(x1->coaddr, x->coaddr, माप(*x1->coaddr));
		पूर्ण
		अगर (!use_spi && स_भेद(&x1->sel, &x->sel, माप(x1->sel)))
			स_नकल(&x1->sel, &x->sel, माप(x1->sel));
		स_नकल(&x1->lft, &x->lft, माप(x1->lft));
		x1->km.dying = 0;

		hrसमयr_start(&x1->mसमयr, kसमय_set(1, 0),
			      HRTIMER_MODE_REL_SOFT);
		अगर (x1->curlft.use_समय)
			xfrm_state_check_expire(x1);

		अगर (x->props.smark.m || x->props.smark.v || x->अगर_id) अणु
			spin_lock_bh(&net->xfrm.xfrm_state_lock);

			अगर (x->props.smark.m || x->props.smark.v)
				x1->props.smark = x->props.smark;

			अगर (x->अगर_id)
				x1->अगर_id = x->अगर_id;

			__xfrm_state_bump_genids(x1);
			spin_unlock_bh(&net->xfrm.xfrm_state_lock);
		पूर्ण

		err = 0;
		x->km.state = XFRM_STATE_DEAD;
		__xfrm_state_put(x);
	पूर्ण

fail:
	spin_unlock_bh(&x1->lock);

	xfrm_state_put(x1);

	वापस err;
पूर्ण
EXPORT_SYMBOL(xfrm_state_update);

पूर्णांक xfrm_state_check_expire(काष्ठा xfrm_state *x)
अणु
	अगर (!x->curlft.use_समय)
		x->curlft.use_समय = kसमय_get_real_seconds();

	अगर (x->curlft.bytes >= x->lft.hard_byte_limit ||
	    x->curlft.packets >= x->lft.hard_packet_limit) अणु
		x->km.state = XFRM_STATE_EXPIRED;
		hrसमयr_start(&x->mसमयr, 0, HRTIMER_MODE_REL_SOFT);
		वापस -EINVAL;
	पूर्ण

	अगर (!x->km.dying &&
	    (x->curlft.bytes >= x->lft.soft_byte_limit ||
	     x->curlft.packets >= x->lft.soft_packet_limit)) अणु
		x->km.dying = 1;
		km_state_expired(x, 0, 0);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(xfrm_state_check_expire);

काष्ठा xfrm_state *
xfrm_state_lookup(काष्ठा net *net, u32 mark, स्थिर xfrm_address_t *daddr, __be32 spi,
		  u8 proto, अचिन्हित लघु family)
अणु
	काष्ठा xfrm_state *x;

	rcu_पढ़ो_lock();
	x = __xfrm_state_lookup(net, mark, daddr, spi, proto, family);
	rcu_पढ़ो_unlock();
	वापस x;
पूर्ण
EXPORT_SYMBOL(xfrm_state_lookup);

काष्ठा xfrm_state *
xfrm_state_lookup_byaddr(काष्ठा net *net, u32 mark,
			 स्थिर xfrm_address_t *daddr, स्थिर xfrm_address_t *saddr,
			 u8 proto, अचिन्हित लघु family)
अणु
	काष्ठा xfrm_state *x;

	spin_lock_bh(&net->xfrm.xfrm_state_lock);
	x = __xfrm_state_lookup_byaddr(net, mark, daddr, saddr, proto, family);
	spin_unlock_bh(&net->xfrm.xfrm_state_lock);
	वापस x;
पूर्ण
EXPORT_SYMBOL(xfrm_state_lookup_byaddr);

काष्ठा xfrm_state *
xfrm_find_acq(काष्ठा net *net, स्थिर काष्ठा xfrm_mark *mark, u8 mode, u32 reqid,
	      u32 अगर_id, u8 proto, स्थिर xfrm_address_t *daddr,
	      स्थिर xfrm_address_t *saddr, पूर्णांक create, अचिन्हित लघु family)
अणु
	काष्ठा xfrm_state *x;

	spin_lock_bh(&net->xfrm.xfrm_state_lock);
	x = __find_acq_core(net, mark, family, mode, reqid, अगर_id, proto, daddr, saddr, create);
	spin_unlock_bh(&net->xfrm.xfrm_state_lock);

	वापस x;
पूर्ण
EXPORT_SYMBOL(xfrm_find_acq);

#अगर_घोषित CONFIG_XFRM_SUB_POLICY
#अगर IS_ENABLED(CONFIG_IPV6)
/* distribution counting sort function क्रम xfrm_state and xfrm_पंचांगpl */
अटल व्योम
__xfrm6_sort(व्योम **dst, व्योम **src, पूर्णांक n,
	     पूर्णांक (*cmp)(स्थिर व्योम *p), पूर्णांक maxclass)
अणु
	पूर्णांक count[XFRM_MAX_DEPTH] = अणु पूर्ण;
	पूर्णांक class[XFRM_MAX_DEPTH];
	पूर्णांक i;

	क्रम (i = 0; i < n; i++) अणु
		पूर्णांक c = cmp(src[i]);

		class[i] = c;
		count[c]++;
	पूर्ण

	क्रम (i = 2; i < maxclass; i++)
		count[i] += count[i - 1];

	क्रम (i = 0; i < n; i++) अणु
		dst[count[class[i] - 1]++] = src[i];
		src[i] = शून्य;
	पूर्ण
पूर्ण

/* Rule क्रम xfrm_state:
 *
 * rule 1: select IPsec transport except AH
 * rule 2: select MIPv6 RO or inbound trigger
 * rule 3: select IPsec transport AH
 * rule 4: select IPsec tunnel
 * rule 5: others
 */
अटल पूर्णांक __xfrm6_state_sort_cmp(स्थिर व्योम *p)
अणु
	स्थिर काष्ठा xfrm_state *v = p;

	चयन (v->props.mode) अणु
	हाल XFRM_MODE_TRANSPORT:
		अगर (v->id.proto != IPPROTO_AH)
			वापस 1;
		अन्यथा
			वापस 3;
#अगर IS_ENABLED(CONFIG_IPV6_MIP6)
	हाल XFRM_MODE_ROUTEOPTIMIZATION:
	हाल XFRM_MODE_IN_TRIGGER:
		वापस 2;
#पूर्ण_अगर
	हाल XFRM_MODE_TUNNEL:
	हाल XFRM_MODE_BEET:
		वापस 4;
	पूर्ण
	वापस 5;
पूर्ण

/* Rule क्रम xfrm_पंचांगpl:
 *
 * rule 1: select IPsec transport
 * rule 2: select MIPv6 RO or inbound trigger
 * rule 3: select IPsec tunnel
 * rule 4: others
 */
अटल पूर्णांक __xfrm6_पंचांगpl_sort_cmp(स्थिर व्योम *p)
अणु
	स्थिर काष्ठा xfrm_पंचांगpl *v = p;

	चयन (v->mode) अणु
	हाल XFRM_MODE_TRANSPORT:
		वापस 1;
#अगर IS_ENABLED(CONFIG_IPV6_MIP6)
	हाल XFRM_MODE_ROUTEOPTIMIZATION:
	हाल XFRM_MODE_IN_TRIGGER:
		वापस 2;
#पूर्ण_अगर
	हाल XFRM_MODE_TUNNEL:
	हाल XFRM_MODE_BEET:
		वापस 3;
	पूर्ण
	वापस 4;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक __xfrm6_state_sort_cmp(स्थिर व्योम *p) अणु वापस 5; पूर्ण
अटल अंतरभूत पूर्णांक __xfrm6_पंचांगpl_sort_cmp(स्थिर व्योम *p) अणु वापस 4; पूर्ण

अटल अंतरभूत व्योम
__xfrm6_sort(व्योम **dst, व्योम **src, पूर्णांक n,
	     पूर्णांक (*cmp)(स्थिर व्योम *p), पूर्णांक maxclass)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n; i++)
		dst[i] = src[i];
पूर्ण
#पूर्ण_अगर /* CONFIG_IPV6 */

व्योम
xfrm_पंचांगpl_sort(काष्ठा xfrm_पंचांगpl **dst, काष्ठा xfrm_पंचांगpl **src, पूर्णांक n,
	       अचिन्हित लघु family)
अणु
	पूर्णांक i;

	अगर (family == AF_INET6)
		__xfrm6_sort((व्योम **)dst, (व्योम **)src, n,
			     __xfrm6_पंचांगpl_sort_cmp, 5);
	अन्यथा
		क्रम (i = 0; i < n; i++)
			dst[i] = src[i];
पूर्ण

व्योम
xfrm_state_sort(काष्ठा xfrm_state **dst, काष्ठा xfrm_state **src, पूर्णांक n,
		अचिन्हित लघु family)
अणु
	पूर्णांक i;

	अगर (family == AF_INET6)
		__xfrm6_sort((व्योम **)dst, (व्योम **)src, n,
			     __xfrm6_state_sort_cmp, 6);
	अन्यथा
		क्रम (i = 0; i < n; i++)
			dst[i] = src[i];
पूर्ण
#पूर्ण_अगर

/* Silly enough, but I'm lazy to build resolution list */

अटल काष्ठा xfrm_state *__xfrm_find_acq_byseq(काष्ठा net *net, u32 mark, u32 seq)
अणु
	पूर्णांक i;

	क्रम (i = 0; i <= net->xfrm.state_hmask; i++) अणु
		काष्ठा xfrm_state *x;

		hlist_क्रम_each_entry(x, net->xfrm.state_bydst+i, bydst) अणु
			अगर (x->km.seq == seq &&
			    (mark & x->mark.m) == x->mark.v &&
			    x->km.state == XFRM_STATE_ACQ) अणु
				xfrm_state_hold(x);
				वापस x;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा xfrm_state *xfrm_find_acq_byseq(काष्ठा net *net, u32 mark, u32 seq)
अणु
	काष्ठा xfrm_state *x;

	spin_lock_bh(&net->xfrm.xfrm_state_lock);
	x = __xfrm_find_acq_byseq(net, mark, seq);
	spin_unlock_bh(&net->xfrm.xfrm_state_lock);
	वापस x;
पूर्ण
EXPORT_SYMBOL(xfrm_find_acq_byseq);

u32 xfrm_get_acqseq(व्योम)
अणु
	u32 res;
	अटल atomic_t acqseq;

	करो अणु
		res = atomic_inc_वापस(&acqseq);
	पूर्ण जबतक (!res);

	वापस res;
पूर्ण
EXPORT_SYMBOL(xfrm_get_acqseq);

पूर्णांक verअगरy_spi_info(u8 proto, u32 min, u32 max)
अणु
	चयन (proto) अणु
	हाल IPPROTO_AH:
	हाल IPPROTO_ESP:
		अवरोध;

	हाल IPPROTO_COMP:
		/* IPCOMP spi is 16-bits. */
		अगर (max >= 0x10000)
			वापस -EINVAL;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (min > max)
		वापस -EINVAL;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(verअगरy_spi_info);

पूर्णांक xfrm_alloc_spi(काष्ठा xfrm_state *x, u32 low, u32 high)
अणु
	काष्ठा net *net = xs_net(x);
	अचिन्हित पूर्णांक h;
	काष्ठा xfrm_state *x0;
	पूर्णांक err = -ENOENT;
	__be32 minspi = htonl(low);
	__be32 maxspi = htonl(high);
	__be32 newspi = 0;
	u32 mark = x->mark.v & x->mark.m;

	spin_lock_bh(&x->lock);
	अगर (x->km.state == XFRM_STATE_DEAD)
		जाओ unlock;

	err = 0;
	अगर (x->id.spi)
		जाओ unlock;

	err = -ENOENT;

	अगर (minspi == maxspi) अणु
		x0 = xfrm_state_lookup(net, mark, &x->id.daddr, minspi, x->id.proto, x->props.family);
		अगर (x0) अणु
			xfrm_state_put(x0);
			जाओ unlock;
		पूर्ण
		newspi = minspi;
	पूर्ण अन्यथा अणु
		u32 spi = 0;
		क्रम (h = 0; h < high-low+1; h++) अणु
			spi = low + pअक्रमom_u32()%(high-low+1);
			x0 = xfrm_state_lookup(net, mark, &x->id.daddr, htonl(spi), x->id.proto, x->props.family);
			अगर (x0 == शून्य) अणु
				newspi = htonl(spi);
				अवरोध;
			पूर्ण
			xfrm_state_put(x0);
		पूर्ण
	पूर्ण
	अगर (newspi) अणु
		spin_lock_bh(&net->xfrm.xfrm_state_lock);
		x->id.spi = newspi;
		h = xfrm_spi_hash(net, &x->id.daddr, x->id.spi, x->id.proto, x->props.family);
		hlist_add_head_rcu(&x->byspi, net->xfrm.state_byspi + h);
		spin_unlock_bh(&net->xfrm.xfrm_state_lock);

		err = 0;
	पूर्ण

unlock:
	spin_unlock_bh(&x->lock);

	वापस err;
पूर्ण
EXPORT_SYMBOL(xfrm_alloc_spi);

अटल bool __xfrm_state_filter_match(काष्ठा xfrm_state *x,
				      काष्ठा xfrm_address_filter *filter)
अणु
	अगर (filter) अणु
		अगर ((filter->family == AF_INET ||
		     filter->family == AF_INET6) &&
		    x->props.family != filter->family)
			वापस false;

		वापस addr_match(&x->props.saddr, &filter->saddr,
				  filter->splen) &&
		       addr_match(&x->id.daddr, &filter->daddr,
				  filter->dplen);
	पूर्ण
	वापस true;
पूर्ण

पूर्णांक xfrm_state_walk(काष्ठा net *net, काष्ठा xfrm_state_walk *walk,
		    पूर्णांक (*func)(काष्ठा xfrm_state *, पूर्णांक, व्योम*),
		    व्योम *data)
अणु
	काष्ठा xfrm_state *state;
	काष्ठा xfrm_state_walk *x;
	पूर्णांक err = 0;

	अगर (walk->seq != 0 && list_empty(&walk->all))
		वापस 0;

	spin_lock_bh(&net->xfrm.xfrm_state_lock);
	अगर (list_empty(&walk->all))
		x = list_first_entry(&net->xfrm.state_all, काष्ठा xfrm_state_walk, all);
	अन्यथा
		x = list_first_entry(&walk->all, काष्ठा xfrm_state_walk, all);
	list_क्रम_each_entry_from(x, &net->xfrm.state_all, all) अणु
		अगर (x->state == XFRM_STATE_DEAD)
			जारी;
		state = container_of(x, काष्ठा xfrm_state, km);
		अगर (!xfrm_id_proto_match(state->id.proto, walk->proto))
			जारी;
		अगर (!__xfrm_state_filter_match(state, walk->filter))
			जारी;
		err = func(state, walk->seq, data);
		अगर (err) अणु
			list_move_tail(&walk->all, &x->all);
			जाओ out;
		पूर्ण
		walk->seq++;
	पूर्ण
	अगर (walk->seq == 0) अणु
		err = -ENOENT;
		जाओ out;
	पूर्ण
	list_del_init(&walk->all);
out:
	spin_unlock_bh(&net->xfrm.xfrm_state_lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL(xfrm_state_walk);

व्योम xfrm_state_walk_init(काष्ठा xfrm_state_walk *walk, u8 proto,
			  काष्ठा xfrm_address_filter *filter)
अणु
	INIT_LIST_HEAD(&walk->all);
	walk->proto = proto;
	walk->state = XFRM_STATE_DEAD;
	walk->seq = 0;
	walk->filter = filter;
पूर्ण
EXPORT_SYMBOL(xfrm_state_walk_init);

व्योम xfrm_state_walk_करोne(काष्ठा xfrm_state_walk *walk, काष्ठा net *net)
अणु
	kमुक्त(walk->filter);

	अगर (list_empty(&walk->all))
		वापस;

	spin_lock_bh(&net->xfrm.xfrm_state_lock);
	list_del(&walk->all);
	spin_unlock_bh(&net->xfrm.xfrm_state_lock);
पूर्ण
EXPORT_SYMBOL(xfrm_state_walk_करोne);

अटल व्योम xfrm_replay_समयr_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा xfrm_state *x = from_समयr(x, t, rसमयr);

	spin_lock(&x->lock);

	अगर (x->km.state == XFRM_STATE_VALID) अणु
		अगर (xfrm_aevent_is_on(xs_net(x)))
			x->repl->notअगरy(x, XFRM_REPLAY_TIMEOUT);
		अन्यथा
			x->xflags |= XFRM_TIME_DEFER;
	पूर्ण

	spin_unlock(&x->lock);
पूर्ण

अटल LIST_HEAD(xfrm_km_list);

व्योम km_policy_notअगरy(काष्ठा xfrm_policy *xp, पूर्णांक dir, स्थिर काष्ठा km_event *c)
अणु
	काष्ठा xfrm_mgr *km;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(km, &xfrm_km_list, list)
		अगर (km->notअगरy_policy)
			km->notअगरy_policy(xp, dir, c);
	rcu_पढ़ो_unlock();
पूर्ण

व्योम km_state_notअगरy(काष्ठा xfrm_state *x, स्थिर काष्ठा km_event *c)
अणु
	काष्ठा xfrm_mgr *km;
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(km, &xfrm_km_list, list)
		अगर (km->notअगरy)
			km->notअगरy(x, c);
	rcu_पढ़ो_unlock();
पूर्ण

EXPORT_SYMBOL(km_policy_notअगरy);
EXPORT_SYMBOL(km_state_notअगरy);

व्योम km_state_expired(काष्ठा xfrm_state *x, पूर्णांक hard, u32 portid)
अणु
	काष्ठा km_event c;

	c.data.hard = hard;
	c.portid = portid;
	c.event = XFRM_MSG_EXPIRE;
	km_state_notअगरy(x, &c);
पूर्ण

EXPORT_SYMBOL(km_state_expired);
/*
 * We send to all रेजिस्टरed managers regardless of failure
 * We are happy with one success
*/
पूर्णांक km_query(काष्ठा xfrm_state *x, काष्ठा xfrm_पंचांगpl *t, काष्ठा xfrm_policy *pol)
अणु
	पूर्णांक err = -EINVAL, acqret;
	काष्ठा xfrm_mgr *km;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(km, &xfrm_km_list, list) अणु
		acqret = km->acquire(x, t, pol);
		अगर (!acqret)
			err = acqret;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण
EXPORT_SYMBOL(km_query);

पूर्णांक km_new_mapping(काष्ठा xfrm_state *x, xfrm_address_t *ipaddr, __be16 sport)
अणु
	पूर्णांक err = -EINVAL;
	काष्ठा xfrm_mgr *km;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(km, &xfrm_km_list, list) अणु
		अगर (km->new_mapping)
			err = km->new_mapping(x, ipaddr, sport);
		अगर (!err)
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण
EXPORT_SYMBOL(km_new_mapping);

व्योम km_policy_expired(काष्ठा xfrm_policy *pol, पूर्णांक dir, पूर्णांक hard, u32 portid)
अणु
	काष्ठा km_event c;

	c.data.hard = hard;
	c.portid = portid;
	c.event = XFRM_MSG_POLEXPIRE;
	km_policy_notअगरy(pol, dir, &c);
पूर्ण
EXPORT_SYMBOL(km_policy_expired);

#अगर_घोषित CONFIG_XFRM_MIGRATE
पूर्णांक km_migrate(स्थिर काष्ठा xfrm_selector *sel, u8 dir, u8 type,
	       स्थिर काष्ठा xfrm_migrate *m, पूर्णांक num_migrate,
	       स्थिर काष्ठा xfrm_kmaddress *k,
	       स्थिर काष्ठा xfrm_encap_पंचांगpl *encap)
अणु
	पूर्णांक err = -EINVAL;
	पूर्णांक ret;
	काष्ठा xfrm_mgr *km;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(km, &xfrm_km_list, list) अणु
		अगर (km->migrate) अणु
			ret = km->migrate(sel, dir, type, m, num_migrate, k,
					  encap);
			अगर (!ret)
				err = ret;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण
EXPORT_SYMBOL(km_migrate);
#पूर्ण_अगर

पूर्णांक km_report(काष्ठा net *net, u8 proto, काष्ठा xfrm_selector *sel, xfrm_address_t *addr)
अणु
	पूर्णांक err = -EINVAL;
	पूर्णांक ret;
	काष्ठा xfrm_mgr *km;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(km, &xfrm_km_list, list) अणु
		अगर (km->report) अणु
			ret = km->report(net, proto, sel, addr);
			अगर (!ret)
				err = ret;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण
EXPORT_SYMBOL(km_report);

अटल bool km_is_alive(स्थिर काष्ठा km_event *c)
अणु
	काष्ठा xfrm_mgr *km;
	bool is_alive = false;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(km, &xfrm_km_list, list) अणु
		अगर (km->is_alive && km->is_alive(c)) अणु
			is_alive = true;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस is_alive;
पूर्ण

#अगर IS_ENABLED(CONFIG_XFRM_USER_COMPAT)
अटल DEFINE_SPINLOCK(xfrm_translator_lock);
अटल काष्ठा xfrm_translator __rcu *xfrm_translator;

काष्ठा xfrm_translator *xfrm_get_translator(व्योम)
अणु
	काष्ठा xfrm_translator *xtr;

	rcu_पढ़ो_lock();
	xtr = rcu_dereference(xfrm_translator);
	अगर (unlikely(!xtr))
		जाओ out;
	अगर (!try_module_get(xtr->owner))
		xtr = शून्य;
out:
	rcu_पढ़ो_unlock();
	वापस xtr;
पूर्ण
EXPORT_SYMBOL_GPL(xfrm_get_translator);

व्योम xfrm_put_translator(काष्ठा xfrm_translator *xtr)
अणु
	module_put(xtr->owner);
पूर्ण
EXPORT_SYMBOL_GPL(xfrm_put_translator);

पूर्णांक xfrm_रेजिस्टर_translator(काष्ठा xfrm_translator *xtr)
अणु
	पूर्णांक err = 0;

	spin_lock_bh(&xfrm_translator_lock);
	अगर (unlikely(xfrm_translator != शून्य))
		err = -EEXIST;
	अन्यथा
		rcu_assign_poपूर्णांकer(xfrm_translator, xtr);
	spin_unlock_bh(&xfrm_translator_lock);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(xfrm_रेजिस्टर_translator);

पूर्णांक xfrm_unरेजिस्टर_translator(काष्ठा xfrm_translator *xtr)
अणु
	पूर्णांक err = 0;

	spin_lock_bh(&xfrm_translator_lock);
	अगर (likely(xfrm_translator != शून्य)) अणु
		अगर (rcu_access_poपूर्णांकer(xfrm_translator) != xtr)
			err = -EINVAL;
		अन्यथा
			RCU_INIT_POINTER(xfrm_translator, शून्य);
	पूर्ण
	spin_unlock_bh(&xfrm_translator_lock);
	synchronize_rcu();

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(xfrm_unरेजिस्टर_translator);
#पूर्ण_अगर

पूर्णांक xfrm_user_policy(काष्ठा sock *sk, पूर्णांक optname, sockptr_t optval, पूर्णांक optlen)
अणु
	पूर्णांक err;
	u8 *data;
	काष्ठा xfrm_mgr *km;
	काष्ठा xfrm_policy *pol = शून्य;

	अगर (sockptr_is_null(optval) && !optlen) अणु
		xfrm_sk_policy_insert(sk, XFRM_POLICY_IN, शून्य);
		xfrm_sk_policy_insert(sk, XFRM_POLICY_OUT, शून्य);
		__sk_dst_reset(sk);
		वापस 0;
	पूर्ण

	अगर (optlen <= 0 || optlen > PAGE_SIZE)
		वापस -EMSGSIZE;

	data = memdup_sockptr(optval, optlen);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	अगर (in_compat_syscall()) अणु
		काष्ठा xfrm_translator *xtr = xfrm_get_translator();

		अगर (!xtr) अणु
			kमुक्त(data);
			वापस -EOPNOTSUPP;
		पूर्ण

		err = xtr->xlate_user_policy_sockptr(&data, optlen);
		xfrm_put_translator(xtr);
		अगर (err) अणु
			kमुक्त(data);
			वापस err;
		पूर्ण
	पूर्ण

	err = -EINVAL;
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(km, &xfrm_km_list, list) अणु
		pol = km->compile_policy(sk, optname, data,
					 optlen, &err);
		अगर (err >= 0)
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (err >= 0) अणु
		xfrm_sk_policy_insert(sk, err, pol);
		xfrm_pol_put(pol);
		__sk_dst_reset(sk);
		err = 0;
	पूर्ण

	kमुक्त(data);
	वापस err;
पूर्ण
EXPORT_SYMBOL(xfrm_user_policy);

अटल DEFINE_SPINLOCK(xfrm_km_lock);

पूर्णांक xfrm_रेजिस्टर_km(काष्ठा xfrm_mgr *km)
अणु
	spin_lock_bh(&xfrm_km_lock);
	list_add_tail_rcu(&km->list, &xfrm_km_list);
	spin_unlock_bh(&xfrm_km_lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(xfrm_रेजिस्टर_km);

पूर्णांक xfrm_unरेजिस्टर_km(काष्ठा xfrm_mgr *km)
अणु
	spin_lock_bh(&xfrm_km_lock);
	list_del_rcu(&km->list);
	spin_unlock_bh(&xfrm_km_lock);
	synchronize_rcu();
	वापस 0;
पूर्ण
EXPORT_SYMBOL(xfrm_unरेजिस्टर_km);

पूर्णांक xfrm_state_रेजिस्टर_afinfo(काष्ठा xfrm_state_afinfo *afinfo)
अणु
	पूर्णांक err = 0;

	अगर (WARN_ON(afinfo->family >= NPROTO))
		वापस -EAFNOSUPPORT;

	spin_lock_bh(&xfrm_state_afinfo_lock);
	अगर (unlikely(xfrm_state_afinfo[afinfo->family] != शून्य))
		err = -EEXIST;
	अन्यथा
		rcu_assign_poपूर्णांकer(xfrm_state_afinfo[afinfo->family], afinfo);
	spin_unlock_bh(&xfrm_state_afinfo_lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL(xfrm_state_रेजिस्टर_afinfo);

पूर्णांक xfrm_state_unरेजिस्टर_afinfo(काष्ठा xfrm_state_afinfo *afinfo)
अणु
	पूर्णांक err = 0, family = afinfo->family;

	अगर (WARN_ON(family >= NPROTO))
		वापस -EAFNOSUPPORT;

	spin_lock_bh(&xfrm_state_afinfo_lock);
	अगर (likely(xfrm_state_afinfo[afinfo->family] != शून्य)) अणु
		अगर (rcu_access_poपूर्णांकer(xfrm_state_afinfo[family]) != afinfo)
			err = -EINVAL;
		अन्यथा
			RCU_INIT_POINTER(xfrm_state_afinfo[afinfo->family], शून्य);
	पूर्ण
	spin_unlock_bh(&xfrm_state_afinfo_lock);
	synchronize_rcu();
	वापस err;
पूर्ण
EXPORT_SYMBOL(xfrm_state_unरेजिस्टर_afinfo);

काष्ठा xfrm_state_afinfo *xfrm_state_afinfo_get_rcu(अचिन्हित पूर्णांक family)
अणु
	अगर (unlikely(family >= NPROTO))
		वापस शून्य;

	वापस rcu_dereference(xfrm_state_afinfo[family]);
पूर्ण
EXPORT_SYMBOL_GPL(xfrm_state_afinfo_get_rcu);

काष्ठा xfrm_state_afinfo *xfrm_state_get_afinfo(अचिन्हित पूर्णांक family)
अणु
	काष्ठा xfrm_state_afinfo *afinfo;
	अगर (unlikely(family >= NPROTO))
		वापस शून्य;
	rcu_पढ़ो_lock();
	afinfo = rcu_dereference(xfrm_state_afinfo[family]);
	अगर (unlikely(!afinfo))
		rcu_पढ़ो_unlock();
	वापस afinfo;
पूर्ण

व्योम xfrm_flush_gc(व्योम)
अणु
	flush_work(&xfrm_state_gc_work);
पूर्ण
EXPORT_SYMBOL(xfrm_flush_gc);

/* Temporarily located here until net/xfrm/xfrm_tunnel.c is created */
व्योम xfrm_state_delete_tunnel(काष्ठा xfrm_state *x)
अणु
	अगर (x->tunnel) अणु
		काष्ठा xfrm_state *t = x->tunnel;

		अगर (atomic_पढ़ो(&t->tunnel_users) == 2)
			xfrm_state_delete(t);
		atomic_dec(&t->tunnel_users);
		xfrm_state_put_sync(t);
		x->tunnel = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(xfrm_state_delete_tunnel);

u32 xfrm_state_mtu(काष्ठा xfrm_state *x, पूर्णांक mtu)
अणु
	स्थिर काष्ठा xfrm_type *type = READ_ONCE(x->type);
	काष्ठा crypto_aead *aead;
	u32 blksize, net_adj = 0;

	अगर (x->km.state != XFRM_STATE_VALID ||
	    !type || type->proto != IPPROTO_ESP)
		वापस mtu - x->props.header_len;

	aead = x->data;
	blksize = ALIGN(crypto_aead_blocksize(aead), 4);

	चयन (x->props.mode) अणु
	हाल XFRM_MODE_TRANSPORT:
	हाल XFRM_MODE_BEET:
		अगर (x->props.family == AF_INET)
			net_adj = माप(काष्ठा iphdr);
		अन्यथा अगर (x->props.family == AF_INET6)
			net_adj = माप(काष्ठा ipv6hdr);
		अवरोध;
	हाल XFRM_MODE_TUNNEL:
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		अवरोध;
	पूर्ण

	वापस ((mtu - x->props.header_len - crypto_aead_authsize(aead) -
		 net_adj) & ~(blksize - 1)) + net_adj - 2;
पूर्ण
EXPORT_SYMBOL_GPL(xfrm_state_mtu);

पूर्णांक __xfrm_init_state(काष्ठा xfrm_state *x, bool init_replay, bool offload)
अणु
	स्थिर काष्ठा xfrm_mode *inner_mode;
	स्थिर काष्ठा xfrm_mode *outer_mode;
	पूर्णांक family = x->props.family;
	पूर्णांक err;

	अगर (family == AF_INET &&
	    xs_net(x)->ipv4.sysctl_ip_no_pmtu_disc)
		x->props.flags |= XFRM_STATE_NOPMTUDISC;

	err = -EPROTONOSUPPORT;

	अगर (x->sel.family != AF_UNSPEC) अणु
		inner_mode = xfrm_get_mode(x->props.mode, x->sel.family);
		अगर (inner_mode == शून्य)
			जाओ error;

		अगर (!(inner_mode->flags & XFRM_MODE_FLAG_TUNNEL) &&
		    family != x->sel.family)
			जाओ error;

		x->inner_mode = *inner_mode;
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा xfrm_mode *inner_mode_iaf;
		पूर्णांक iafamily = AF_INET;

		inner_mode = xfrm_get_mode(x->props.mode, x->props.family);
		अगर (inner_mode == शून्य)
			जाओ error;

		अगर (!(inner_mode->flags & XFRM_MODE_FLAG_TUNNEL))
			जाओ error;

		x->inner_mode = *inner_mode;

		अगर (x->props.family == AF_INET)
			iafamily = AF_INET6;

		inner_mode_iaf = xfrm_get_mode(x->props.mode, iafamily);
		अगर (inner_mode_iaf) अणु
			अगर (inner_mode_iaf->flags & XFRM_MODE_FLAG_TUNNEL)
				x->inner_mode_iaf = *inner_mode_iaf;
		पूर्ण
	पूर्ण

	x->type = xfrm_get_type(x->id.proto, family);
	अगर (x->type == शून्य)
		जाओ error;

	x->type_offload = xfrm_get_type_offload(x->id.proto, family, offload);

	err = x->type->init_state(x);
	अगर (err)
		जाओ error;

	outer_mode = xfrm_get_mode(x->props.mode, family);
	अगर (!outer_mode) अणु
		err = -EPROTONOSUPPORT;
		जाओ error;
	पूर्ण

	x->outer_mode = *outer_mode;
	अगर (init_replay) अणु
		err = xfrm_init_replay(x);
		अगर (err)
			जाओ error;
	पूर्ण

error:
	वापस err;
पूर्ण

EXPORT_SYMBOL(__xfrm_init_state);

पूर्णांक xfrm_init_state(काष्ठा xfrm_state *x)
अणु
	पूर्णांक err;

	err = __xfrm_init_state(x, true, false);
	अगर (!err)
		x->km.state = XFRM_STATE_VALID;

	वापस err;
पूर्ण

EXPORT_SYMBOL(xfrm_init_state);

पूर्णांक __net_init xfrm_state_init(काष्ठा net *net)
अणु
	अचिन्हित पूर्णांक sz;

	अगर (net_eq(net, &init_net))
		xfrm_state_cache = KMEM_CACHE(xfrm_state,
					      SLAB_HWCACHE_ALIGN | SLAB_PANIC);

	INIT_LIST_HEAD(&net->xfrm.state_all);

	sz = माप(काष्ठा hlist_head) * 8;

	net->xfrm.state_bydst = xfrm_hash_alloc(sz);
	अगर (!net->xfrm.state_bydst)
		जाओ out_bydst;
	net->xfrm.state_bysrc = xfrm_hash_alloc(sz);
	अगर (!net->xfrm.state_bysrc)
		जाओ out_bysrc;
	net->xfrm.state_byspi = xfrm_hash_alloc(sz);
	अगर (!net->xfrm.state_byspi)
		जाओ out_byspi;
	net->xfrm.state_hmask = ((sz / माप(काष्ठा hlist_head)) - 1);

	net->xfrm.state_num = 0;
	INIT_WORK(&net->xfrm.state_hash_work, xfrm_hash_resize);
	spin_lock_init(&net->xfrm.xfrm_state_lock);
	seqcount_spinlock_init(&net->xfrm.xfrm_state_hash_generation,
			       &net->xfrm.xfrm_state_lock);
	वापस 0;

out_byspi:
	xfrm_hash_मुक्त(net->xfrm.state_bysrc, sz);
out_bysrc:
	xfrm_hash_मुक्त(net->xfrm.state_bydst, sz);
out_bydst:
	वापस -ENOMEM;
पूर्ण

व्योम xfrm_state_fini(काष्ठा net *net)
अणु
	अचिन्हित पूर्णांक sz;

	flush_work(&net->xfrm.state_hash_work);
	flush_work(&xfrm_state_gc_work);
	xfrm_state_flush(net, 0, false, true);

	WARN_ON(!list_empty(&net->xfrm.state_all));

	sz = (net->xfrm.state_hmask + 1) * माप(काष्ठा hlist_head);
	WARN_ON(!hlist_empty(net->xfrm.state_byspi));
	xfrm_hash_मुक्त(net->xfrm.state_byspi, sz);
	WARN_ON(!hlist_empty(net->xfrm.state_bysrc));
	xfrm_hash_मुक्त(net->xfrm.state_bysrc, sz);
	WARN_ON(!hlist_empty(net->xfrm.state_bydst));
	xfrm_hash_मुक्त(net->xfrm.state_bydst, sz);
पूर्ण

#अगर_घोषित CONFIG_AUDITSYSCALL
अटल व्योम xfrm_audit_helper_sainfo(काष्ठा xfrm_state *x,
				     काष्ठा audit_buffer *audit_buf)
अणु
	काष्ठा xfrm_sec_ctx *ctx = x->security;
	u32 spi = ntohl(x->id.spi);

	अगर (ctx)
		audit_log_क्रमmat(audit_buf, " sec_alg=%u sec_doi=%u sec_obj=%s",
				 ctx->ctx_alg, ctx->ctx_करोi, ctx->ctx_str);

	चयन (x->props.family) अणु
	हाल AF_INET:
		audit_log_क्रमmat(audit_buf, " src=%pI4 dst=%pI4",
				 &x->props.saddr.a4, &x->id.daddr.a4);
		अवरोध;
	हाल AF_INET6:
		audit_log_क्रमmat(audit_buf, " src=%pI6 dst=%pI6",
				 x->props.saddr.a6, x->id.daddr.a6);
		अवरोध;
	पूर्ण

	audit_log_क्रमmat(audit_buf, " spi=%u(0x%x)", spi, spi);
पूर्ण

अटल व्योम xfrm_audit_helper_pktinfo(काष्ठा sk_buff *skb, u16 family,
				      काष्ठा audit_buffer *audit_buf)
अणु
	स्थिर काष्ठा iphdr *iph4;
	स्थिर काष्ठा ipv6hdr *iph6;

	चयन (family) अणु
	हाल AF_INET:
		iph4 = ip_hdr(skb);
		audit_log_क्रमmat(audit_buf, " src=%pI4 dst=%pI4",
				 &iph4->saddr, &iph4->daddr);
		अवरोध;
	हाल AF_INET6:
		iph6 = ipv6_hdr(skb);
		audit_log_क्रमmat(audit_buf,
				 " src=%pI6 dst=%pI6 flowlbl=0x%x%02x%02x",
				 &iph6->saddr, &iph6->daddr,
				 iph6->flow_lbl[0] & 0x0f,
				 iph6->flow_lbl[1],
				 iph6->flow_lbl[2]);
		अवरोध;
	पूर्ण
पूर्ण

व्योम xfrm_audit_state_add(काष्ठा xfrm_state *x, पूर्णांक result, bool task_valid)
अणु
	काष्ठा audit_buffer *audit_buf;

	audit_buf = xfrm_audit_start("SAD-add");
	अगर (audit_buf == शून्य)
		वापस;
	xfrm_audit_helper_usrinfo(task_valid, audit_buf);
	xfrm_audit_helper_sainfo(x, audit_buf);
	audit_log_क्रमmat(audit_buf, " res=%u", result);
	audit_log_end(audit_buf);
पूर्ण
EXPORT_SYMBOL_GPL(xfrm_audit_state_add);

व्योम xfrm_audit_state_delete(काष्ठा xfrm_state *x, पूर्णांक result, bool task_valid)
अणु
	काष्ठा audit_buffer *audit_buf;

	audit_buf = xfrm_audit_start("SAD-delete");
	अगर (audit_buf == शून्य)
		वापस;
	xfrm_audit_helper_usrinfo(task_valid, audit_buf);
	xfrm_audit_helper_sainfo(x, audit_buf);
	audit_log_क्रमmat(audit_buf, " res=%u", result);
	audit_log_end(audit_buf);
पूर्ण
EXPORT_SYMBOL_GPL(xfrm_audit_state_delete);

व्योम xfrm_audit_state_replay_overflow(काष्ठा xfrm_state *x,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा audit_buffer *audit_buf;
	u32 spi;

	audit_buf = xfrm_audit_start("SA-replay-overflow");
	अगर (audit_buf == शून्य)
		वापस;
	xfrm_audit_helper_pktinfo(skb, x->props.family, audit_buf);
	/* करोn't record the sequence number because it's inherent in this kind
	 * of audit message */
	spi = ntohl(x->id.spi);
	audit_log_क्रमmat(audit_buf, " spi=%u(0x%x)", spi, spi);
	audit_log_end(audit_buf);
पूर्ण
EXPORT_SYMBOL_GPL(xfrm_audit_state_replay_overflow);

व्योम xfrm_audit_state_replay(काष्ठा xfrm_state *x,
			     काष्ठा sk_buff *skb, __be32 net_seq)
अणु
	काष्ठा audit_buffer *audit_buf;
	u32 spi;

	audit_buf = xfrm_audit_start("SA-replayed-pkt");
	अगर (audit_buf == शून्य)
		वापस;
	xfrm_audit_helper_pktinfo(skb, x->props.family, audit_buf);
	spi = ntohl(x->id.spi);
	audit_log_क्रमmat(audit_buf, " spi=%u(0x%x) seqno=%u",
			 spi, spi, ntohl(net_seq));
	audit_log_end(audit_buf);
पूर्ण
EXPORT_SYMBOL_GPL(xfrm_audit_state_replay);

व्योम xfrm_audit_state_notfound_simple(काष्ठा sk_buff *skb, u16 family)
अणु
	काष्ठा audit_buffer *audit_buf;

	audit_buf = xfrm_audit_start("SA-notfound");
	अगर (audit_buf == शून्य)
		वापस;
	xfrm_audit_helper_pktinfo(skb, family, audit_buf);
	audit_log_end(audit_buf);
पूर्ण
EXPORT_SYMBOL_GPL(xfrm_audit_state_notfound_simple);

व्योम xfrm_audit_state_notfound(काष्ठा sk_buff *skb, u16 family,
			       __be32 net_spi, __be32 net_seq)
अणु
	काष्ठा audit_buffer *audit_buf;
	u32 spi;

	audit_buf = xfrm_audit_start("SA-notfound");
	अगर (audit_buf == शून्य)
		वापस;
	xfrm_audit_helper_pktinfo(skb, family, audit_buf);
	spi = ntohl(net_spi);
	audit_log_क्रमmat(audit_buf, " spi=%u(0x%x) seqno=%u",
			 spi, spi, ntohl(net_seq));
	audit_log_end(audit_buf);
पूर्ण
EXPORT_SYMBOL_GPL(xfrm_audit_state_notfound);

व्योम xfrm_audit_state_icvfail(काष्ठा xfrm_state *x,
			      काष्ठा sk_buff *skb, u8 proto)
अणु
	काष्ठा audit_buffer *audit_buf;
	__be32 net_spi;
	__be32 net_seq;

	audit_buf = xfrm_audit_start("SA-icv-failure");
	अगर (audit_buf == शून्य)
		वापस;
	xfrm_audit_helper_pktinfo(skb, x->props.family, audit_buf);
	अगर (xfrm_parse_spi(skb, proto, &net_spi, &net_seq) == 0) अणु
		u32 spi = ntohl(net_spi);
		audit_log_क्रमmat(audit_buf, " spi=%u(0x%x) seqno=%u",
				 spi, spi, ntohl(net_seq));
	पूर्ण
	audit_log_end(audit_buf);
पूर्ण
EXPORT_SYMBOL_GPL(xfrm_audit_state_icvfail);
#पूर्ण_अगर /* CONFIG_AUDITSYSCALL */
