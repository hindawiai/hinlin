<शैली गुरु>
/*
 * net/tipc/name_table.c: TIPC name table code
 *
 * Copyright (c) 2000-2006, 2014-2018, Ericsson AB
 * Copyright (c) 2004-2008, 2010-2014, Wind River Systems
 * Copyright (c) 2020-2021, Red Hat Inc
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the names of the copyright holders nor the names of its
 *    contributors may be used to enकरोrse or promote products derived from
 *    this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <net/sock.h>
#समावेश <linux/list_sort.h>
#समावेश <linux/rbtree_augmented.h>
#समावेश "core.h"
#समावेश "netlink.h"
#समावेश "name_table.h"
#समावेश "name_distr.h"
#समावेश "subscr.h"
#समावेश "bcast.h"
#समावेश "addr.h"
#समावेश "node.h"
#समावेश "group.h"

/**
 * काष्ठा service_range - container क्रम all bindings of a service range
 * @lower: service range lower bound
 * @upper: service range upper bound
 * @tree_node: member of service range RB tree
 * @max: largest 'upper' in this node subtree
 * @local_publ: list of identical खुलाations made from this node
 *   Used by बंदst_first lookup and multicast lookup algorithm
 * @all_publ: all खुलाations identical to this one, whatever node and scope
 *   Used by round-robin lookup algorithm
 */
काष्ठा service_range अणु
	u32 lower;
	u32 upper;
	काष्ठा rb_node tree_node;
	u32 max;
	काष्ठा list_head local_publ;
	काष्ठा list_head all_publ;
पूर्ण;

/**
 * काष्ठा tipc_service - container क्रम all published instances of a service type
 * @type: 32 bit 'type' value क्रम service
 * @publ_cnt: increasing counter क्रम खुलाations in this service
 * @ranges: rb tree containing all service ranges क्रम this service
 * @service_list: links to adjacent name ranges in hash chain
 * @subscriptions: list of subscriptions क्रम this service type
 * @lock: spinlock controlling access to pertaining service ranges/खुलाations
 * @rcu: RCU callback head used क्रम deferred मुक्तing
 */
काष्ठा tipc_service अणु
	u32 type;
	u32 publ_cnt;
	काष्ठा rb_root ranges;
	काष्ठा hlist_node service_list;
	काष्ठा list_head subscriptions;
	spinlock_t lock; /* Covers service range list */
	काष्ठा rcu_head rcu;
पूर्ण;

#घोषणा service_range_upper(sr) ((sr)->upper)
RB_DECLARE_CALLBACKS_MAX(अटल, sr_callbacks,
			 काष्ठा service_range, tree_node, u32, max,
			 service_range_upper)

#घोषणा service_range_entry(rbtree_node)				\
	(container_of(rbtree_node, काष्ठा service_range, tree_node))

#घोषणा service_range_overlap(sr, start, end)				\
	((sr)->lower <= (end) && (sr)->upper >= (start))

/**
 * service_range_क्रमeach_match - iterate over tipc service rbtree क्रम each
 *                               range match
 * @sr: the service range poपूर्णांकer as a loop cursor
 * @sc: the poपूर्णांकer to tipc service which holds the service range rbtree
 * @start: beginning of the search range (end >= start) क्रम matching
 * @end: end of the search range (end >= start) क्रम matching
 */
#घोषणा service_range_क्रमeach_match(sr, sc, start, end)			\
	क्रम (sr = service_range_match_first((sc)->ranges.rb_node,	\
					    start,			\
					    end);			\
	     sr;							\
	     sr = service_range_match_next(&(sr)->tree_node,		\
					   start,			\
					   end))

/**
 * service_range_match_first - find first service range matching a range
 * @n: the root node of service range rbtree क्रम searching
 * @start: beginning of the search range (end >= start) क्रम matching
 * @end: end of the search range (end >= start) क्रम matching
 *
 * Return: the lefपंचांगost service range node in the rbtree that overlaps the
 * specअगरic range अगर any. Otherwise, वापसs शून्य.
 */
अटल काष्ठा service_range *service_range_match_first(काष्ठा rb_node *n,
						       u32 start, u32 end)
अणु
	काष्ठा service_range *sr;
	काष्ठा rb_node *l, *r;

	/* Non overlaps in tree at all? */
	अगर (!n || service_range_entry(n)->max < start)
		वापस शून्य;

	जबतक (n) अणु
		l = n->rb_left;
		अगर (l && service_range_entry(l)->max >= start) अणु
			/* A lefपंचांगost overlap range node must be one in the left
			 * subtree. If not, it has lower > end, then nodes on
			 * the right side cannot satisfy the condition either.
			 */
			n = l;
			जारी;
		पूर्ण

		/* No one in the left subtree can match, वापस अगर this node is
		 * an overlap i.e. lefपंचांगost.
		 */
		sr = service_range_entry(n);
		अगर (service_range_overlap(sr, start, end))
			वापस sr;

		/* Ok, try to lookup on the right side */
		r = n->rb_right;
		अगर (sr->lower <= end &&
		    r && service_range_entry(r)->max >= start) अणु
			n = r;
			जारी;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * service_range_match_next - find next service range matching a range
 * @n: a node in service range rbtree from which the searching starts
 * @start: beginning of the search range (end >= start) क्रम matching
 * @end: end of the search range (end >= start) क्रम matching
 *
 * Return: the next service range node to the given node in the rbtree that
 * overlaps the specअगरic range अगर any. Otherwise, वापसs शून्य.
 */
अटल काष्ठा service_range *service_range_match_next(काष्ठा rb_node *n,
						      u32 start, u32 end)
अणु
	काष्ठा service_range *sr;
	काष्ठा rb_node *p, *r;

	जबतक (n) अणु
		r = n->rb_right;
		अगर (r && service_range_entry(r)->max >= start)
			/* A next overlap range node must be one in the right
			 * subtree. If not, it has lower > end, then any next
			 * successor (- an ancestor) of this node cannot
			 * satisfy the condition either.
			 */
			वापस service_range_match_first(r, start, end);

		/* No one in the right subtree can match, go up to find an
		 * ancestor of this node which is parent of a left-hand child.
		 */
		जबतक ((p = rb_parent(n)) && n == p->rb_right)
			n = p;
		अगर (!p)
			अवरोध;

		/* Return अगर this ancestor is an overlap */
		sr = service_range_entry(p);
		अगर (service_range_overlap(sr, start, end))
			वापस sr;

		/* Ok, try to lookup more from this ancestor */
		अगर (sr->lower <= end) अणु
			n = p;
			जारी;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक hash(पूर्णांक x)
अणु
	वापस x & (TIPC_NAMETBL_SIZE - 1);
पूर्ण

/**
 * tipc_publ_create - create a खुलाation काष्ठाure
 * @ua: the service range the user is binding to
 * @sk: the address of the socket that is bound
 * @key: खुलाation key
 */
अटल काष्ठा खुलाation *tipc_publ_create(काष्ठा tipc_uaddr *ua,
					    काष्ठा tipc_socket_addr *sk,
					    u32 key)
अणु
	काष्ठा खुलाation *p = kzalloc(माप(*p), GFP_ATOMIC);

	अगर (!p)
		वापस शून्य;

	p->sr = ua->sr;
	p->sk = *sk;
	p->scope = ua->scope;
	p->key = key;
	INIT_LIST_HEAD(&p->binding_sock);
	INIT_LIST_HEAD(&p->binding_node);
	INIT_LIST_HEAD(&p->local_publ);
	INIT_LIST_HEAD(&p->all_publ);
	INIT_LIST_HEAD(&p->list);
	वापस p;
पूर्ण

/**
 * tipc_service_create - create a service काष्ठाure क्रम the specअगरied 'type'
 * @net: network namespace
 * @ua: address representing the service to be bound
 *
 * Allocates a single range काष्ठाure and sets it to all 0's.
 */
अटल काष्ठा tipc_service *tipc_service_create(काष्ठा net *net,
						काष्ठा tipc_uaddr *ua)
अणु
	काष्ठा name_table *nt = tipc_name_table(net);
	काष्ठा tipc_service *service;
	काष्ठा hlist_head *hd;

	service = kzalloc(माप(*service), GFP_ATOMIC);
	अगर (!service) अणु
		pr_warn("Service creation failed, no memory\n");
		वापस शून्य;
	पूर्ण

	spin_lock_init(&service->lock);
	service->type = ua->sr.type;
	service->ranges = RB_ROOT;
	INIT_HLIST_NODE(&service->service_list);
	INIT_LIST_HEAD(&service->subscriptions);
	hd = &nt->services[hash(ua->sr.type)];
	hlist_add_head_rcu(&service->service_list, hd);
	वापस service;
पूर्ण

/*  tipc_service_find_range - find service range matching खुलाation parameters
 */
अटल काष्ठा service_range *tipc_service_find_range(काष्ठा tipc_service *sc,
						     काष्ठा tipc_uaddr *ua)
अणु
	काष्ठा service_range *sr;

	service_range_क्रमeach_match(sr, sc, ua->sr.lower, ua->sr.upper) अणु
		/* Look क्रम exact match */
		अगर (sr->lower == ua->sr.lower && sr->upper == ua->sr.upper)
			वापस sr;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा service_range *tipc_service_create_range(काष्ठा tipc_service *sc,
						       काष्ठा खुलाation *p)
अणु
	काष्ठा rb_node **n, *parent = शून्य;
	काष्ठा service_range *sr;
	u32 lower = p->sr.lower;
	u32 upper = p->sr.upper;

	n = &sc->ranges.rb_node;
	जबतक (*n) अणु
		parent = *n;
		sr = service_range_entry(parent);
		अगर (lower == sr->lower && upper == sr->upper)
			वापस sr;
		अगर (sr->max < upper)
			sr->max = upper;
		अगर (lower <= sr->lower)
			n = &parent->rb_left;
		अन्यथा
			n = &parent->rb_right;
	पूर्ण
	sr = kzalloc(माप(*sr), GFP_ATOMIC);
	अगर (!sr)
		वापस शून्य;
	sr->lower = lower;
	sr->upper = upper;
	sr->max = upper;
	INIT_LIST_HEAD(&sr->local_publ);
	INIT_LIST_HEAD(&sr->all_publ);
	rb_link_node(&sr->tree_node, parent, n);
	rb_insert_augmented(&sr->tree_node, &sc->ranges, &sr_callbacks);
	वापस sr;
पूर्ण

अटल bool tipc_service_insert_publ(काष्ठा net *net,
				     काष्ठा tipc_service *sc,
				     काष्ठा खुलाation *p)
अणु
	काष्ठा tipc_subscription *sub, *पंचांगp;
	काष्ठा service_range *sr;
	काष्ठा खुलाation *_p;
	u32 node = p->sk.node;
	bool first = false;
	bool res = false;
	u32 key = p->key;

	spin_lock_bh(&sc->lock);
	sr = tipc_service_create_range(sc, p);
	अगर (!sr)
		जाओ  निकास;

	first = list_empty(&sr->all_publ);

	/* Return अगर the खुलाation alपढ़ोy exists */
	list_क्रम_each_entry(_p, &sr->all_publ, all_publ) अणु
		अगर (_p->key == key && (!_p->sk.node || _p->sk.node == node)) अणु
			pr_debug("Failed to bind duplicate %u,%u,%u/%u:%u/%u\n",
				 p->sr.type, p->sr.lower, p->sr.upper,
				 node, p->sk.ref, key);
			जाओ निकास;
		पूर्ण
	पूर्ण

	अगर (in_own_node(net, p->sk.node))
		list_add(&p->local_publ, &sr->local_publ);
	list_add(&p->all_publ, &sr->all_publ);
	p->id = sc->publ_cnt++;

	/* Any subscriptions रुकोing क्रम notअगरication?  */
	list_क्रम_each_entry_safe(sub, पंचांगp, &sc->subscriptions, service_list) अणु
		tipc_sub_report_overlap(sub, p, TIPC_PUBLISHED, first);
	पूर्ण
	res = true;
निकास:
	अगर (!res)
		pr_warn("Failed to bind to %u,%u,%u\n",
			p->sr.type, p->sr.lower, p->sr.upper);
	spin_unlock_bh(&sc->lock);
	वापस res;
पूर्ण

/**
 * tipc_service_हटाओ_publ - हटाओ a खुलाation from a service
 * @r: service_range to हटाओ खुलाation from
 * @sk: address publishing socket
 * @key: target खुलाation key
 */
अटल काष्ठा खुलाation *tipc_service_हटाओ_publ(काष्ठा service_range *r,
						    काष्ठा tipc_socket_addr *sk,
						    u32 key)
अणु
	काष्ठा खुलाation *p;
	u32 node = sk->node;

	list_क्रम_each_entry(p, &r->all_publ, all_publ) अणु
		अगर (p->key != key || (node && node != p->sk.node))
			जारी;
		list_del(&p->all_publ);
		list_del(&p->local_publ);
		वापस p;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Code reused: समय_after32() क्रम the same purpose
 */
#घोषणा खुलाation_after(pa, pb) समय_after32((pa)->id, (pb)->id)
अटल पूर्णांक tipc_publ_sort(व्योम *priv, स्थिर काष्ठा list_head *a,
			  स्थिर काष्ठा list_head *b)
अणु
	काष्ठा खुलाation *pa, *pb;

	pa = container_of(a, काष्ठा खुलाation, list);
	pb = container_of(b, काष्ठा खुलाation, list);
	वापस खुलाation_after(pa, pb);
पूर्ण

/**
 * tipc_service_subscribe - attach a subscription, and optionally
 * issue the prescribed number of events अगर there is any service
 * range overlapping with the requested range
 * @service: the tipc_service to attach the @sub to
 * @sub: the subscription to attach
 */
अटल व्योम tipc_service_subscribe(काष्ठा tipc_service *service,
				   काष्ठा tipc_subscription *sub)
अणु
	काष्ठा खुलाation *p, *first, *पंचांगp;
	काष्ठा list_head publ_list;
	काष्ठा service_range *sr;
	u32 filter, lower, upper;

	filter = sub->s.filter;
	lower = sub->s.seq.lower;
	upper = sub->s.seq.upper;

	tipc_sub_get(sub);
	list_add(&sub->service_list, &service->subscriptions);

	अगर (filter & TIPC_SUB_NO_STATUS)
		वापस;

	INIT_LIST_HEAD(&publ_list);
	service_range_क्रमeach_match(sr, service, lower, upper) अणु
		first = शून्य;
		list_क्रम_each_entry(p, &sr->all_publ, all_publ) अणु
			अगर (filter & TIPC_SUB_PORTS)
				list_add_tail(&p->list, &publ_list);
			अन्यथा अगर (!first || खुलाation_after(first, p))
				/* Pick this range's *first* खुलाation */
				first = p;
		पूर्ण
		अगर (first)
			list_add_tail(&first->list, &publ_list);
	पूर्ण

	/* Sort the खुलाations beक्रमe reporting */
	list_sort(शून्य, &publ_list, tipc_publ_sort);
	list_क्रम_each_entry_safe(p, पंचांगp, &publ_list, list) अणु
		tipc_sub_report_overlap(sub, p, TIPC_PUBLISHED, true);
		list_del_init(&p->list);
	पूर्ण
पूर्ण

अटल काष्ठा tipc_service *tipc_service_find(काष्ठा net *net,
					      काष्ठा tipc_uaddr *ua)
अणु
	काष्ठा name_table *nt = tipc_name_table(net);
	काष्ठा hlist_head *service_head;
	काष्ठा tipc_service *service;

	service_head = &nt->services[hash(ua->sr.type)];
	hlist_क्रम_each_entry_rcu(service, service_head, service_list) अणु
		अगर (service->type == ua->sr.type)
			वापस service;
	पूर्ण
	वापस शून्य;
पूर्ण;

काष्ठा खुलाation *tipc_nametbl_insert_publ(काष्ठा net *net,
					     काष्ठा tipc_uaddr *ua,
					     काष्ठा tipc_socket_addr *sk,
					     u32 key)
अणु
	काष्ठा tipc_service *sc;
	काष्ठा खुलाation *p;

	p = tipc_publ_create(ua, sk, key);
	अगर (!p)
		वापस शून्य;

	sc = tipc_service_find(net, ua);
	अगर (!sc)
		sc = tipc_service_create(net, ua);
	अगर (sc && tipc_service_insert_publ(net, sc, p))
		वापस p;
	kमुक्त(p);
	वापस शून्य;
पूर्ण

काष्ठा खुलाation *tipc_nametbl_हटाओ_publ(काष्ठा net *net,
					     काष्ठा tipc_uaddr *ua,
					     काष्ठा tipc_socket_addr *sk,
					     u32 key)
अणु
	काष्ठा tipc_subscription *sub, *पंचांगp;
	काष्ठा खुलाation *p = शून्य;
	काष्ठा service_range *sr;
	काष्ठा tipc_service *sc;
	bool last;

	sc = tipc_service_find(net, ua);
	अगर (!sc)
		जाओ निकास;

	spin_lock_bh(&sc->lock);
	sr = tipc_service_find_range(sc, ua);
	अगर (!sr)
		जाओ unlock;
	p = tipc_service_हटाओ_publ(sr, sk, key);
	अगर (!p)
		जाओ unlock;

	/* Notअगरy any रुकोing subscriptions */
	last = list_empty(&sr->all_publ);
	list_क्रम_each_entry_safe(sub, पंचांगp, &sc->subscriptions, service_list) अणु
		tipc_sub_report_overlap(sub, p, TIPC_WITHDRAWN, last);
	पूर्ण

	/* Remove service range item अगर this was its last खुलाation */
	अगर (list_empty(&sr->all_publ)) अणु
		rb_erase_augmented(&sr->tree_node, &sc->ranges, &sr_callbacks);
		kमुक्त(sr);
	पूर्ण

	/* Delete service item अगर no more खुलाations and subscriptions */
	अगर (RB_EMPTY_ROOT(&sc->ranges) && list_empty(&sc->subscriptions)) अणु
		hlist_del_init_rcu(&sc->service_list);
		kमुक्त_rcu(sc, rcu);
	पूर्ण
unlock:
	spin_unlock_bh(&sc->lock);
निकास:
	अगर (!p) अणु
		pr_err("Failed to remove unknown binding: %u,%u,%u/%u:%u/%u\n",
		       ua->sr.type, ua->sr.lower, ua->sr.upper,
		       sk->node, sk->ref, key);
	पूर्ण
	वापस p;
पूर्ण

/**
 * tipc_nametbl_lookup_anycast - perक्रमm service instance to socket translation
 * @net: network namespace
 * @ua: service address to look up
 * @sk: address to socket we want to find
 *
 * On entry, a non-zero 'sk->node' indicates the node where we want lookup to be
 * perक्रमmed, which may not be this one.
 *
 * On निकास:
 *
 * - If lookup is deferred to another node, leave 'sk->node' unchanged and
 *   वापस 'true'.
 * - If lookup is successful, set the 'sk->node' and 'sk->ref' (== portid) which
 *   represent the bound socket and वापस 'true'.
 * - If lookup fails, वापस 'false'
 *
 * Note that क्रम legacy users (node configured with Z.C.N address क्रमmat) the
 * 'closest-first' lookup algorithm must be मुख्यtained, i.e., अगर sk.node is 0
 * we must look in the local binding list first
 */
bool tipc_nametbl_lookup_anycast(काष्ठा net *net,
				 काष्ठा tipc_uaddr *ua,
				 काष्ठा tipc_socket_addr *sk)
अणु
	काष्ठा tipc_net *tn = tipc_net(net);
	bool legacy = tn->legacy_addr_क्रमmat;
	u32 self = tipc_own_addr(net);
	u32 inst = ua->sa.instance;
	काष्ठा service_range *r;
	काष्ठा tipc_service *sc;
	काष्ठा खुलाation *p;
	काष्ठा list_head *l;
	bool res = false;

	अगर (!tipc_in_scope(legacy, sk->node, self))
		वापस true;

	rcu_पढ़ो_lock();
	sc = tipc_service_find(net, ua);
	अगर (unlikely(!sc))
		जाओ निकास;

	spin_lock_bh(&sc->lock);
	service_range_क्रमeach_match(r, sc, inst, inst) अणु
		/* Select lookup algo: local, बंदst-first or round-robin */
		अगर (sk->node == self) अणु
			l = &r->local_publ;
			अगर (list_empty(l))
				जारी;
			p = list_first_entry(l, काष्ठा खुलाation, local_publ);
			list_move_tail(&p->local_publ, &r->local_publ);
		पूर्ण अन्यथा अगर (legacy && !sk->node && !list_empty(&r->local_publ)) अणु
			l = &r->local_publ;
			p = list_first_entry(l, काष्ठा खुलाation, local_publ);
			list_move_tail(&p->local_publ, &r->local_publ);
		पूर्ण अन्यथा अणु
			l = &r->all_publ;
			p = list_first_entry(l, काष्ठा खुलाation, all_publ);
			list_move_tail(&p->all_publ, &r->all_publ);
		पूर्ण
		*sk = p->sk;
		res = true;
		/* Toकरो: as क्रम legacy, pick the first matching range only, a
		 * "true" round-robin will be perक्रमmed as needed.
		 */
		अवरोध;
	पूर्ण
	spin_unlock_bh(&sc->lock);

निकास:
	rcu_पढ़ो_unlock();
	वापस res;
पूर्ण

/* tipc_nametbl_lookup_group(): lookup destinaton(s) in a communication group
 * Returns a list of one (== group anycast) or more (== group multicast)
 * destination socket/node pairs matching the given address.
 * The requester may or may not want to exclude himself from the list.
 */
bool tipc_nametbl_lookup_group(काष्ठा net *net, काष्ठा tipc_uaddr *ua,
			       काष्ठा list_head *dsts, पूर्णांक *dstcnt,
			       u32 exclude, bool mcast)
अणु
	u32 self = tipc_own_addr(net);
	u32 inst = ua->sa.instance;
	काष्ठा service_range *sr;
	काष्ठा tipc_service *sc;
	काष्ठा खुलाation *p;

	*dstcnt = 0;
	rcu_पढ़ो_lock();
	sc = tipc_service_find(net, ua);
	अगर (unlikely(!sc))
		जाओ निकास;

	spin_lock_bh(&sc->lock);

	/* Toकरो: a full search i.e. service_range_क्रमeach_match() instead? */
	sr = service_range_match_first(sc->ranges.rb_node, inst, inst);
	अगर (!sr)
		जाओ no_match;

	list_क्रम_each_entry(p, &sr->all_publ, all_publ) अणु
		अगर (p->scope != ua->scope)
			जारी;
		अगर (p->sk.ref == exclude && p->sk.node == self)
			जारी;
		tipc_dest_push(dsts, p->sk.node, p->sk.ref);
		(*dstcnt)++;
		अगर (mcast)
			जारी;
		list_move_tail(&p->all_publ, &sr->all_publ);
		अवरोध;
	पूर्ण
no_match:
	spin_unlock_bh(&sc->lock);
निकास:
	rcu_पढ़ो_unlock();
	वापस !list_empty(dsts);
पूर्ण

/* tipc_nametbl_lookup_mcast_sockets(): look up node local destinaton sockets
 *                                      matching the given address
 * Used on nodes which have received a multicast/broadcast message
 * Returns a list of local sockets
 */
व्योम tipc_nametbl_lookup_mcast_sockets(काष्ठा net *net, काष्ठा tipc_uaddr *ua,
				       bool exact, काष्ठा list_head *dports)
अणु
	काष्ठा service_range *sr;
	काष्ठा tipc_service *sc;
	काष्ठा खुलाation *p;
	u32 scope = ua->scope;

	rcu_पढ़ो_lock();
	sc = tipc_service_find(net, ua);
	अगर (!sc)
		जाओ निकास;

	spin_lock_bh(&sc->lock);
	service_range_क्रमeach_match(sr, sc, ua->sr.lower, ua->sr.upper) अणु
		list_क्रम_each_entry(p, &sr->local_publ, local_publ) अणु
			अगर (p->scope == scope || (!exact && p->scope < scope))
				tipc_dest_push(dports, 0, p->sk.ref);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&sc->lock);
निकास:
	rcu_पढ़ो_unlock();
पूर्ण

/* tipc_nametbl_lookup_mcast_nodes(): look up all destination nodes matching
 *                                    the given address. Used in sending node.
 * Used on nodes which are sending out a multicast/broadcast message
 * Returns a list of nodes, including own node अगर applicable
 */
व्योम tipc_nametbl_lookup_mcast_nodes(काष्ठा net *net, काष्ठा tipc_uaddr *ua,
				     काष्ठा tipc_nlist *nodes)
अणु
	काष्ठा service_range *sr;
	काष्ठा tipc_service *sc;
	काष्ठा खुलाation *p;

	rcu_पढ़ो_lock();
	sc = tipc_service_find(net, ua);
	अगर (!sc)
		जाओ निकास;

	spin_lock_bh(&sc->lock);
	service_range_क्रमeach_match(sr, sc, ua->sr.lower, ua->sr.upper) अणु
		list_क्रम_each_entry(p, &sr->all_publ, all_publ) अणु
			tipc_nlist_add(nodes, p->sk.node);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&sc->lock);
निकास:
	rcu_पढ़ो_unlock();
पूर्ण

/* tipc_nametbl_build_group - build list of communication group members
 */
व्योम tipc_nametbl_build_group(काष्ठा net *net, काष्ठा tipc_group *grp,
			      काष्ठा tipc_uaddr *ua)
अणु
	काष्ठा service_range *sr;
	काष्ठा tipc_service *sc;
	काष्ठा खुलाation *p;
	काष्ठा rb_node *n;

	rcu_पढ़ो_lock();
	sc = tipc_service_find(net, ua);
	अगर (!sc)
		जाओ निकास;

	spin_lock_bh(&sc->lock);
	क्रम (n = rb_first(&sc->ranges); n; n = rb_next(n)) अणु
		sr = container_of(n, काष्ठा service_range, tree_node);
		list_क्रम_each_entry(p, &sr->all_publ, all_publ) अणु
			अगर (p->scope != ua->scope)
				जारी;
			tipc_group_add_member(grp, p->sk.node, p->sk.ref,
					      p->sr.lower);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&sc->lock);
निकास:
	rcu_पढ़ो_unlock();
पूर्ण

/* tipc_nametbl_publish - add service binding to name table
 */
काष्ठा खुलाation *tipc_nametbl_publish(काष्ठा net *net, काष्ठा tipc_uaddr *ua,
					 काष्ठा tipc_socket_addr *sk, u32 key)
अणु
	काष्ठा name_table *nt = tipc_name_table(net);
	काष्ठा tipc_net *tn = tipc_net(net);
	काष्ठा खुलाation *p = शून्य;
	काष्ठा sk_buff *skb = शून्य;
	u32 rc_dests;

	spin_lock_bh(&tn->nametbl_lock);

	अगर (nt->local_publ_count >= TIPC_MAX_PUBL) अणु
		pr_warn("Bind failed, max limit %u reached\n", TIPC_MAX_PUBL);
		जाओ निकास;
	पूर्ण

	p = tipc_nametbl_insert_publ(net, ua, sk, key);
	अगर (p) अणु
		nt->local_publ_count++;
		skb = tipc_named_publish(net, p);
	पूर्ण
	rc_dests = nt->rc_dests;
निकास:
	spin_unlock_bh(&tn->nametbl_lock);

	अगर (skb)
		tipc_node_broadcast(net, skb, rc_dests);
	वापस p;

पूर्ण

/**
 * tipc_nametbl_withdraw - withdraw a service binding
 * @net: network namespace
 * @ua: service address/range being unbound
 * @sk: address of the socket being unbound from
 * @key: target खुलाation key
 */
व्योम tipc_nametbl_withdraw(काष्ठा net *net, काष्ठा tipc_uaddr *ua,
			   काष्ठा tipc_socket_addr *sk, u32 key)
अणु
	काष्ठा name_table *nt = tipc_name_table(net);
	काष्ठा tipc_net *tn = tipc_net(net);
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा खुलाation *p;
	u32 rc_dests;

	spin_lock_bh(&tn->nametbl_lock);

	p = tipc_nametbl_हटाओ_publ(net, ua, sk, key);
	अगर (p) अणु
		nt->local_publ_count--;
		skb = tipc_named_withdraw(net, p);
		list_del_init(&p->binding_sock);
		kमुक्त_rcu(p, rcu);
	पूर्ण
	rc_dests = nt->rc_dests;
	spin_unlock_bh(&tn->nametbl_lock);

	अगर (skb)
		tipc_node_broadcast(net, skb, rc_dests);
पूर्ण

/**
 * tipc_nametbl_subscribe - add a subscription object to the name table
 * @sub: subscription to add
 */
bool tipc_nametbl_subscribe(काष्ठा tipc_subscription *sub)
अणु
	काष्ठा tipc_net *tn = tipc_net(sub->net);
	u32 type = sub->s.seq.type;
	काष्ठा tipc_service *sc;
	काष्ठा tipc_uaddr ua;
	bool res = true;

	tipc_uaddr(&ua, TIPC_SERVICE_RANGE, TIPC_NODE_SCOPE, type,
		   sub->s.seq.lower, sub->s.seq.upper);
	spin_lock_bh(&tn->nametbl_lock);
	sc = tipc_service_find(sub->net, &ua);
	अगर (!sc)
		sc = tipc_service_create(sub->net, &ua);
	अगर (sc) अणु
		spin_lock_bh(&sc->lock);
		tipc_service_subscribe(sc, sub);
		spin_unlock_bh(&sc->lock);
	पूर्ण अन्यथा अणु
		pr_warn("Failed to subscribe for {%u,%u,%u}\n",
			type, sub->s.seq.lower, sub->s.seq.upper);
		res = false;
	पूर्ण
	spin_unlock_bh(&tn->nametbl_lock);
	वापस res;
पूर्ण

/**
 * tipc_nametbl_unsubscribe - हटाओ a subscription object from name table
 * @sub: subscription to हटाओ
 */
व्योम tipc_nametbl_unsubscribe(काष्ठा tipc_subscription *sub)
अणु
	काष्ठा tipc_net *tn = tipc_net(sub->net);
	काष्ठा tipc_service *sc;
	काष्ठा tipc_uaddr ua;

	tipc_uaddr(&ua, TIPC_SERVICE_RANGE, TIPC_NODE_SCOPE,
		   sub->s.seq.type, sub->s.seq.lower, sub->s.seq.upper);
	spin_lock_bh(&tn->nametbl_lock);
	sc = tipc_service_find(sub->net, &ua);
	अगर (!sc)
		जाओ निकास;

	spin_lock_bh(&sc->lock);
	list_del_init(&sub->service_list);
	tipc_sub_put(sub);

	/* Delete service item अगर no more खुलाations and subscriptions */
	अगर (RB_EMPTY_ROOT(&sc->ranges) && list_empty(&sc->subscriptions)) अणु
		hlist_del_init_rcu(&sc->service_list);
		kमुक्त_rcu(sc, rcu);
	पूर्ण
	spin_unlock_bh(&sc->lock);
निकास:
	spin_unlock_bh(&tn->nametbl_lock);
पूर्ण

पूर्णांक tipc_nametbl_init(काष्ठा net *net)
अणु
	काष्ठा tipc_net *tn = tipc_net(net);
	काष्ठा name_table *nt;
	पूर्णांक i;

	nt = kzalloc(माप(*nt), GFP_KERNEL);
	अगर (!nt)
		वापस -ENOMEM;

	क्रम (i = 0; i < TIPC_NAMETBL_SIZE; i++)
		INIT_HLIST_HEAD(&nt->services[i]);

	INIT_LIST_HEAD(&nt->node_scope);
	INIT_LIST_HEAD(&nt->cluster_scope);
	rwlock_init(&nt->cluster_scope_lock);
	tn->nametbl = nt;
	spin_lock_init(&tn->nametbl_lock);
	वापस 0;
पूर्ण

/**
 * tipc_service_delete - purge all खुलाations क्रम a service and delete it
 * @net: the associated network namespace
 * @sc: tipc_service to delete
 */
अटल व्योम tipc_service_delete(काष्ठा net *net, काष्ठा tipc_service *sc)
अणु
	काष्ठा service_range *sr, *पंचांगpr;
	काष्ठा खुलाation *p, *पंचांगp;

	spin_lock_bh(&sc->lock);
	rbtree_postorder_क्रम_each_entry_safe(sr, पंचांगpr, &sc->ranges, tree_node) अणु
		list_क्रम_each_entry_safe(p, पंचांगp, &sr->all_publ, all_publ) अणु
			tipc_service_हटाओ_publ(sr, &p->sk, p->key);
			kमुक्त_rcu(p, rcu);
		पूर्ण
		rb_erase_augmented(&sr->tree_node, &sc->ranges, &sr_callbacks);
		kमुक्त(sr);
	पूर्ण
	hlist_del_init_rcu(&sc->service_list);
	spin_unlock_bh(&sc->lock);
	kमुक्त_rcu(sc, rcu);
पूर्ण

व्योम tipc_nametbl_stop(काष्ठा net *net)
अणु
	काष्ठा name_table *nt = tipc_name_table(net);
	काष्ठा tipc_net *tn = tipc_net(net);
	काष्ठा hlist_head *service_head;
	काष्ठा tipc_service *service;
	u32 i;

	/* Verअगरy name table is empty and purge any lingering
	 * खुलाations, then release the name table
	 */
	spin_lock_bh(&tn->nametbl_lock);
	क्रम (i = 0; i < TIPC_NAMETBL_SIZE; i++) अणु
		अगर (hlist_empty(&nt->services[i]))
			जारी;
		service_head = &nt->services[i];
		hlist_क्रम_each_entry_rcu(service, service_head, service_list) अणु
			tipc_service_delete(net, service);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&tn->nametbl_lock);

	synchronize_net();
	kमुक्त(nt);
पूर्ण

अटल पूर्णांक __tipc_nl_add_nametable_publ(काष्ठा tipc_nl_msg *msg,
					काष्ठा tipc_service *service,
					काष्ठा service_range *sr,
					u32 *last_key)
अणु
	काष्ठा खुलाation *p;
	काष्ठा nlattr *attrs;
	काष्ठा nlattr *b;
	व्योम *hdr;

	अगर (*last_key) अणु
		list_क्रम_each_entry(p, &sr->all_publ, all_publ)
			अगर (p->key == *last_key)
				अवरोध;
		अगर (p->key != *last_key)
			वापस -EPIPE;
	पूर्ण अन्यथा अणु
		p = list_first_entry(&sr->all_publ,
				     काष्ठा खुलाation,
				     all_publ);
	पूर्ण

	list_क्रम_each_entry_from(p, &sr->all_publ, all_publ) अणु
		*last_key = p->key;

		hdr = genlmsg_put(msg->skb, msg->portid, msg->seq,
				  &tipc_genl_family, NLM_F_MULTI,
				  TIPC_NL_NAME_TABLE_GET);
		अगर (!hdr)
			वापस -EMSGSIZE;

		attrs = nla_nest_start_noflag(msg->skb, TIPC_NLA_NAME_TABLE);
		अगर (!attrs)
			जाओ msg_full;

		b = nla_nest_start_noflag(msg->skb, TIPC_NLA_NAME_TABLE_PUBL);
		अगर (!b)
			जाओ attr_msg_full;

		अगर (nla_put_u32(msg->skb, TIPC_NLA_PUBL_TYPE, service->type))
			जाओ publ_msg_full;
		अगर (nla_put_u32(msg->skb, TIPC_NLA_PUBL_LOWER, sr->lower))
			जाओ publ_msg_full;
		अगर (nla_put_u32(msg->skb, TIPC_NLA_PUBL_UPPER, sr->upper))
			जाओ publ_msg_full;
		अगर (nla_put_u32(msg->skb, TIPC_NLA_PUBL_SCOPE, p->scope))
			जाओ publ_msg_full;
		अगर (nla_put_u32(msg->skb, TIPC_NLA_PUBL_NODE, p->sk.node))
			जाओ publ_msg_full;
		अगर (nla_put_u32(msg->skb, TIPC_NLA_PUBL_REF, p->sk.ref))
			जाओ publ_msg_full;
		अगर (nla_put_u32(msg->skb, TIPC_NLA_PUBL_KEY, p->key))
			जाओ publ_msg_full;

		nla_nest_end(msg->skb, b);
		nla_nest_end(msg->skb, attrs);
		genlmsg_end(msg->skb, hdr);
	पूर्ण
	*last_key = 0;

	वापस 0;

publ_msg_full:
	nla_nest_cancel(msg->skb, b);
attr_msg_full:
	nla_nest_cancel(msg->skb, attrs);
msg_full:
	genlmsg_cancel(msg->skb, hdr);

	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक __tipc_nl_service_range_list(काष्ठा tipc_nl_msg *msg,
					काष्ठा tipc_service *sc,
					u32 *last_lower, u32 *last_key)
अणु
	काष्ठा service_range *sr;
	काष्ठा rb_node *n;
	पूर्णांक err;

	क्रम (n = rb_first(&sc->ranges); n; n = rb_next(n)) अणु
		sr = container_of(n, काष्ठा service_range, tree_node);
		अगर (sr->lower < *last_lower)
			जारी;
		err = __tipc_nl_add_nametable_publ(msg, sc, sr, last_key);
		अगर (err) अणु
			*last_lower = sr->lower;
			वापस err;
		पूर्ण
	पूर्ण
	*last_lower = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक tipc_nl_service_list(काष्ठा net *net, काष्ठा tipc_nl_msg *msg,
				u32 *last_type, u32 *last_lower, u32 *last_key)
अणु
	काष्ठा tipc_net *tn = tipc_net(net);
	काष्ठा tipc_service *service = शून्य;
	काष्ठा hlist_head *head;
	काष्ठा tipc_uaddr ua;
	पूर्णांक err;
	पूर्णांक i;

	अगर (*last_type)
		i = hash(*last_type);
	अन्यथा
		i = 0;

	क्रम (; i < TIPC_NAMETBL_SIZE; i++) अणु
		head = &tn->nametbl->services[i];

		अगर (*last_type ||
		    (!i && *last_key && (*last_lower == *last_key))) अणु
			tipc_uaddr(&ua, TIPC_SERVICE_RANGE, TIPC_NODE_SCOPE,
				   *last_type, *last_lower, *last_lower);
			service = tipc_service_find(net, &ua);
			अगर (!service)
				वापस -EPIPE;
		पूर्ण अन्यथा अणु
			hlist_क्रम_each_entry_rcu(service, head, service_list)
				अवरोध;
			अगर (!service)
				जारी;
		पूर्ण

		hlist_क्रम_each_entry_from_rcu(service, service_list) अणु
			spin_lock_bh(&service->lock);
			err = __tipc_nl_service_range_list(msg, service,
							   last_lower,
							   last_key);

			अगर (err) अणु
				*last_type = service->type;
				spin_unlock_bh(&service->lock);
				वापस err;
			पूर्ण
			spin_unlock_bh(&service->lock);
		पूर्ण
		*last_type = 0;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक tipc_nl_name_table_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	u32 last_type = cb->args[0];
	u32 last_lower = cb->args[1];
	u32 last_key = cb->args[2];
	पूर्णांक करोne = cb->args[3];
	काष्ठा tipc_nl_msg msg;
	पूर्णांक err;

	अगर (करोne)
		वापस 0;

	msg.skb = skb;
	msg.portid = NETLINK_CB(cb->skb).portid;
	msg.seq = cb->nlh->nlmsg_seq;

	rcu_पढ़ो_lock();
	err = tipc_nl_service_list(net, &msg, &last_type,
				   &last_lower, &last_key);
	अगर (!err) अणु
		करोne = 1;
	पूर्ण अन्यथा अगर (err != -EMSGSIZE) अणु
		/* We never set seq or call nl_dump_check_consistent() this
		 * means that setting prev_seq here will cause the consistence
		 * check to fail in the netlink callback handler. Resulting in
		 * the NLMSG_DONE message having the NLM_F_DUMP_INTR flag set अगर
		 * we got an error.
		 */
		cb->prev_seq = 1;
	पूर्ण
	rcu_पढ़ो_unlock();

	cb->args[0] = last_type;
	cb->args[1] = last_lower;
	cb->args[2] = last_key;
	cb->args[3] = करोne;

	वापस skb->len;
पूर्ण

काष्ठा tipc_dest *tipc_dest_find(काष्ठा list_head *l, u32 node, u32 port)
अणु
	काष्ठा tipc_dest *dst;

	list_क्रम_each_entry(dst, l, list) अणु
		अगर (dst->node == node && dst->port == port)
			वापस dst;
	पूर्ण
	वापस शून्य;
पूर्ण

bool tipc_dest_push(काष्ठा list_head *l, u32 node, u32 port)
अणु
	काष्ठा tipc_dest *dst;

	अगर (tipc_dest_find(l, node, port))
		वापस false;

	dst = kदो_स्मृति(माप(*dst), GFP_ATOMIC);
	अगर (unlikely(!dst))
		वापस false;
	dst->node = node;
	dst->port = port;
	list_add(&dst->list, l);
	वापस true;
पूर्ण

bool tipc_dest_pop(काष्ठा list_head *l, u32 *node, u32 *port)
अणु
	काष्ठा tipc_dest *dst;

	अगर (list_empty(l))
		वापस false;
	dst = list_first_entry(l, typeof(*dst), list);
	अगर (port)
		*port = dst->port;
	अगर (node)
		*node = dst->node;
	list_del(&dst->list);
	kमुक्त(dst);
	वापस true;
पूर्ण

bool tipc_dest_del(काष्ठा list_head *l, u32 node, u32 port)
अणु
	काष्ठा tipc_dest *dst;

	dst = tipc_dest_find(l, node, port);
	अगर (!dst)
		वापस false;
	list_del(&dst->list);
	kमुक्त(dst);
	वापस true;
पूर्ण

व्योम tipc_dest_list_purge(काष्ठा list_head *l)
अणु
	काष्ठा tipc_dest *dst, *पंचांगp;

	list_क्रम_each_entry_safe(dst, पंचांगp, l, list) अणु
		list_del(&dst->list);
		kमुक्त(dst);
	पूर्ण
पूर्ण

पूर्णांक tipc_dest_list_len(काष्ठा list_head *l)
अणु
	काष्ठा tipc_dest *dst;
	पूर्णांक i = 0;

	list_क्रम_each_entry(dst, l, list) अणु
		i++;
	पूर्ण
	वापस i;
पूर्ण
