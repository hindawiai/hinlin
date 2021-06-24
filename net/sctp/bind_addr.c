<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* SCTP kernel implementation
 * (C) Copyright IBM Corp. 2001, 2003
 * Copyright (c) Cisco 1999,2000
 * Copyright (c) Motorola 1999,2000,2001
 * Copyright (c) La Monte H.P. Yarroll 2001
 *
 * This file is part of the SCTP kernel implementation.
 *
 * A collection class to handle the storage of transport addresses.
 *
 * Please send any bug reports or fixes you make to the
 * email address(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *    La Monte H.P. Yarroll <piggy@acm.org>
 *    Karl Knutson          <karl@athena.chicago.il.us>
 *    Jon Grimm             <jgrimm@us.ibm.com>
 *    Daisy Chang           <daisyc@us.ibm.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/in.h>
#समावेश <net/sock.h>
#समावेश <net/ipv6.h>
#समावेश <net/अगर_inet6.h>
#समावेश <net/sctp/sctp.h>
#समावेश <net/sctp/sm.h>

/* Forward declarations क्रम पूर्णांकernal helpers. */
अटल पूर्णांक sctp_copy_one_addr(काष्ठा net *net, काष्ठा sctp_bind_addr *dest,
			      जोड़ sctp_addr *addr, क्रमागत sctp_scope scope,
			      gfp_t gfp, पूर्णांक flags);
अटल व्योम sctp_bind_addr_clean(काष्ठा sctp_bind_addr *);

/* First Level Abstractions. */

/* Copy 'src' to 'dest' taking 'scope' पूर्णांकo account.  Omit addresses
 * in 'src' which have a broader scope than 'scope'.
 */
पूर्णांक sctp_bind_addr_copy(काष्ठा net *net, काष्ठा sctp_bind_addr *dest,
			स्थिर काष्ठा sctp_bind_addr *src,
			क्रमागत sctp_scope scope, gfp_t gfp,
			पूर्णांक flags)
अणु
	काष्ठा sctp_sockaddr_entry *addr;
	पूर्णांक error = 0;

	/* All addresses share the same port.  */
	dest->port = src->port;

	/* Extract the addresses which are relevant क्रम this scope.  */
	list_क्रम_each_entry(addr, &src->address_list, list) अणु
		error = sctp_copy_one_addr(net, dest, &addr->a, scope,
					   gfp, flags);
		अगर (error < 0)
			जाओ out;
	पूर्ण

	/* If there are no addresses matching the scope and
	 * this is global scope, try to get a link scope address, with
	 * the assumption that we must be sitting behind a NAT.
	 */
	अगर (list_empty(&dest->address_list) && (SCTP_SCOPE_GLOBAL == scope)) अणु
		list_क्रम_each_entry(addr, &src->address_list, list) अणु
			error = sctp_copy_one_addr(net, dest, &addr->a,
						   SCTP_SCOPE_LINK, gfp,
						   flags);
			अगर (error < 0)
				जाओ out;
		पूर्ण
	पूर्ण

out:
	अगर (error)
		sctp_bind_addr_clean(dest);

	वापस error;
पूर्ण

/* Exactly duplicate the address lists.  This is necessary when करोing
 * peer-offs and accepts.  We करोn't want to put all the current प्रणाली
 * addresses पूर्णांकo the endpoपूर्णांक.  That's useless.  But we करो want duplicat
 * the list of bound addresses that the older endpoपूर्णांक used.
 */
पूर्णांक sctp_bind_addr_dup(काष्ठा sctp_bind_addr *dest,
			स्थिर काष्ठा sctp_bind_addr *src,
			gfp_t gfp)
अणु
	काष्ठा sctp_sockaddr_entry *addr;
	पूर्णांक error = 0;

	/* All addresses share the same port.  */
	dest->port = src->port;

	list_क्रम_each_entry(addr, &src->address_list, list) अणु
		error = sctp_add_bind_addr(dest, &addr->a, माप(addr->a),
					   1, gfp);
		अगर (error < 0)
			अवरोध;
	पूर्ण

	वापस error;
पूर्ण

/* Initialize the SCTP_bind_addr काष्ठाure क्रम either an endpoपूर्णांक or
 * an association.
 */
व्योम sctp_bind_addr_init(काष्ठा sctp_bind_addr *bp, __u16 port)
अणु
	INIT_LIST_HEAD(&bp->address_list);
	bp->port = port;
पूर्ण

/* Dispose of the address list. */
अटल व्योम sctp_bind_addr_clean(काष्ठा sctp_bind_addr *bp)
अणु
	काष्ठा sctp_sockaddr_entry *addr, *temp;

	/* Empty the bind address list. */
	list_क्रम_each_entry_safe(addr, temp, &bp->address_list, list) अणु
		list_del_rcu(&addr->list);
		kमुक्त_rcu(addr, rcu);
		SCTP_DBG_OBJCNT_DEC(addr);
	पूर्ण
पूर्ण

/* Dispose of an SCTP_bind_addr काष्ठाure  */
व्योम sctp_bind_addr_मुक्त(काष्ठा sctp_bind_addr *bp)
अणु
	/* Empty the bind address list. */
	sctp_bind_addr_clean(bp);
पूर्ण

/* Add an address to the bind address list in the SCTP_bind_addr काष्ठाure. */
पूर्णांक sctp_add_bind_addr(काष्ठा sctp_bind_addr *bp, जोड़ sctp_addr *new,
		       पूर्णांक new_size, __u8 addr_state, gfp_t gfp)
अणु
	काष्ठा sctp_sockaddr_entry *addr;

	/* Add the address to the bind address list.  */
	addr = kzalloc(माप(*addr), gfp);
	अगर (!addr)
		वापस -ENOMEM;

	स_नकल(&addr->a, new, min_t(माप_प्रकार, माप(*new), new_size));

	/* Fix up the port अगर it has not yet been set.
	 * Both v4 and v6 have the port at the same offset.
	 */
	अगर (!addr->a.v4.sin_port)
		addr->a.v4.sin_port = htons(bp->port);

	addr->state = addr_state;
	addr->valid = 1;

	INIT_LIST_HEAD(&addr->list);

	/* We always hold a socket lock when calling this function,
	 * and that acts as a ग_लिखोr synchronizing lock.
	 */
	list_add_tail_rcu(&addr->list, &bp->address_list);
	SCTP_DBG_OBJCNT_INC(addr);

	वापस 0;
पूर्ण

/* Delete an address from the bind address list in the SCTP_bind_addr
 * काष्ठाure.
 */
पूर्णांक sctp_del_bind_addr(काष्ठा sctp_bind_addr *bp, जोड़ sctp_addr *del_addr)
अणु
	काष्ठा sctp_sockaddr_entry *addr, *temp;
	पूर्णांक found = 0;

	/* We hold the socket lock when calling this function,
	 * and that acts as a ग_लिखोr synchronizing lock.
	 */
	list_क्रम_each_entry_safe(addr, temp, &bp->address_list, list) अणु
		अगर (sctp_cmp_addr_exact(&addr->a, del_addr)) अणु
			/* Found the exact match. */
			found = 1;
			addr->valid = 0;
			list_del_rcu(&addr->list);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (found) अणु
		kमुक्त_rcu(addr, rcu);
		SCTP_DBG_OBJCNT_DEC(addr);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/* Create a network byte-order representation of all the addresses
 * क्रमmated as SCTP parameters.
 *
 * The second argument is the वापस value क्रम the length.
 */
जोड़ sctp_params sctp_bind_addrs_to_raw(स्थिर काष्ठा sctp_bind_addr *bp,
					 पूर्णांक *addrs_len,
					 gfp_t gfp)
अणु
	जोड़ sctp_params addrparms;
	जोड़ sctp_params retval;
	पूर्णांक addrparms_len;
	जोड़ sctp_addr_param rawaddr;
	पूर्णांक len;
	काष्ठा sctp_sockaddr_entry *addr;
	काष्ठा list_head *pos;
	काष्ठा sctp_af *af;

	addrparms_len = 0;
	len = 0;

	/* Allocate enough memory at once. */
	list_क्रम_each(pos, &bp->address_list) अणु
		len += माप(जोड़ sctp_addr_param);
	पूर्ण

	/* Don't even bother embedding an address अगर there
	 * is only one.
	 */
	अगर (len == माप(जोड़ sctp_addr_param)) अणु
		retval.v = शून्य;
		जाओ end_raw;
	पूर्ण

	retval.v = kदो_स्मृति(len, gfp);
	अगर (!retval.v)
		जाओ end_raw;

	addrparms = retval;

	list_क्रम_each_entry(addr, &bp->address_list, list) अणु
		af = sctp_get_af_specअगरic(addr->a.v4.sin_family);
		len = af->to_addr_param(&addr->a, &rawaddr);
		स_नकल(addrparms.v, &rawaddr, len);
		addrparms.v += len;
		addrparms_len += len;
	पूर्ण

end_raw:
	*addrs_len = addrparms_len;
	वापस retval;
पूर्ण

/*
 * Create an address list out of the raw address list क्रमmat (IPv4 and IPv6
 * address parameters).
 */
पूर्णांक sctp_raw_to_bind_addrs(काष्ठा sctp_bind_addr *bp, __u8 *raw_addr_list,
			   पूर्णांक addrs_len, __u16 port, gfp_t gfp)
अणु
	जोड़ sctp_addr_param *rawaddr;
	काष्ठा sctp_paramhdr *param;
	जोड़ sctp_addr addr;
	पूर्णांक retval = 0;
	पूर्णांक len;
	काष्ठा sctp_af *af;

	/* Convert the raw address to standard address क्रमmat */
	जबतक (addrs_len) अणु
		param = (काष्ठा sctp_paramhdr *)raw_addr_list;
		rawaddr = (जोड़ sctp_addr_param *)raw_addr_list;

		af = sctp_get_af_specअगरic(param_type2af(param->type));
		अगर (unlikely(!af)) अणु
			retval = -EINVAL;
			sctp_bind_addr_clean(bp);
			अवरोध;
		पूर्ण

		af->from_addr_param(&addr, rawaddr, htons(port), 0);
		अगर (sctp_bind_addr_state(bp, &addr) != -1)
			जाओ next;
		retval = sctp_add_bind_addr(bp, &addr, माप(addr),
					    SCTP_ADDR_SRC, gfp);
		अगर (retval) अणु
			/* Can't finish building the list, clean up. */
			sctp_bind_addr_clean(bp);
			अवरोध;
		पूर्ण

next:
		len = ntohs(param->length);
		addrs_len -= len;
		raw_addr_list += len;
	पूर्ण

	वापस retval;
पूर्ण

/********************************************************************
 * 2nd Level Abstractions
 ********************************************************************/

/* Does this contain a specअगरied address?  Allow wildcarding. */
पूर्णांक sctp_bind_addr_match(काष्ठा sctp_bind_addr *bp,
			 स्थिर जोड़ sctp_addr *addr,
			 काष्ठा sctp_sock *opt)
अणु
	काष्ठा sctp_sockaddr_entry *laddr;
	पूर्णांक match = 0;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(laddr, &bp->address_list, list) अणु
		अगर (!laddr->valid)
			जारी;
		अगर (opt->pf->cmp_addr(&laddr->a, addr, opt)) अणु
			match = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस match;
पूर्ण

पूर्णांक sctp_bind_addrs_check(काष्ठा sctp_sock *sp,
			  काष्ठा sctp_sock *sp2, पूर्णांक cnt2)
अणु
	काष्ठा sctp_bind_addr *bp2 = &sp2->ep->base.bind_addr;
	काष्ठा sctp_bind_addr *bp = &sp->ep->base.bind_addr;
	काष्ठा sctp_sockaddr_entry *laddr, *laddr2;
	bool exist = false;
	पूर्णांक cnt = 0;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(laddr, &bp->address_list, list) अणु
		list_क्रम_each_entry_rcu(laddr2, &bp2->address_list, list) अणु
			अगर (sp->pf->af->cmp_addr(&laddr->a, &laddr2->a) &&
			    laddr->valid && laddr2->valid) अणु
				exist = true;
				जाओ next;
			पूर्ण
		पूर्ण
		cnt = 0;
		अवरोध;
next:
		cnt++;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस (cnt == cnt2) ? 0 : (exist ? -EEXIST : 1);
पूर्ण

/* Does the address 'addr' conflict with any addresses in
 * the bp.
 */
पूर्णांक sctp_bind_addr_conflict(काष्ठा sctp_bind_addr *bp,
			    स्थिर जोड़ sctp_addr *addr,
			    काष्ठा sctp_sock *bp_sp,
			    काष्ठा sctp_sock *addr_sp)
अणु
	काष्ठा sctp_sockaddr_entry *laddr;
	पूर्णांक conflict = 0;
	काष्ठा sctp_sock *sp;

	/* Pick the IPv6 socket as the basis of comparison
	 * since it's usually a superset of the IPv4.
	 * If there is no IPv6 socket, then शेष to bind_addr.
	 */
	अगर (sctp_opt2sk(bp_sp)->sk_family == AF_INET6)
		sp = bp_sp;
	अन्यथा अगर (sctp_opt2sk(addr_sp)->sk_family == AF_INET6)
		sp = addr_sp;
	अन्यथा
		sp = bp_sp;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(laddr, &bp->address_list, list) अणु
		अगर (!laddr->valid)
			जारी;

		conflict = sp->pf->cmp_addr(&laddr->a, addr, sp);
		अगर (conflict)
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस conflict;
पूर्ण

/* Get the state of the entry in the bind_addr_list */
पूर्णांक sctp_bind_addr_state(स्थिर काष्ठा sctp_bind_addr *bp,
			 स्थिर जोड़ sctp_addr *addr)
अणु
	काष्ठा sctp_sockaddr_entry *laddr;
	काष्ठा sctp_af *af;

	af = sctp_get_af_specअगरic(addr->sa.sa_family);
	अगर (unlikely(!af))
		वापस -1;

	list_क्रम_each_entry_rcu(laddr, &bp->address_list, list) अणु
		अगर (!laddr->valid)
			जारी;
		अगर (af->cmp_addr(&laddr->a, addr))
			वापस laddr->state;
	पूर्ण

	वापस -1;
पूर्ण

/* Find the first address in the bind address list that is not present in
 * the addrs packed array.
 */
जोड़ sctp_addr *sctp_find_unmatch_addr(काष्ठा sctp_bind_addr	*bp,
					स्थिर जोड़ sctp_addr	*addrs,
					पूर्णांक			addrcnt,
					काष्ठा sctp_sock	*opt)
अणु
	काष्ठा sctp_sockaddr_entry	*laddr;
	जोड़ sctp_addr			*addr;
	व्योम 				*addr_buf;
	काष्ठा sctp_af			*af;
	पूर्णांक				i;

	/* This is only called sctp_send_asconf_del_ip() and we hold
	 * the socket lock in that code patch, so that address list
	 * can't change.
	 */
	list_क्रम_each_entry(laddr, &bp->address_list, list) अणु
		addr_buf = (जोड़ sctp_addr *)addrs;
		क्रम (i = 0; i < addrcnt; i++) अणु
			addr = addr_buf;
			af = sctp_get_af_specअगरic(addr->v4.sin_family);
			अगर (!af)
				अवरोध;

			अगर (opt->pf->cmp_addr(&laddr->a, addr, opt))
				अवरोध;

			addr_buf += af->sockaddr_len;
		पूर्ण
		अगर (i == addrcnt)
			वापस &laddr->a;
	पूर्ण

	वापस शून्य;
पूर्ण

/* Copy out addresses from the global local address list. */
अटल पूर्णांक sctp_copy_one_addr(काष्ठा net *net, काष्ठा sctp_bind_addr *dest,
			      जोड़ sctp_addr *addr, क्रमागत sctp_scope scope,
			      gfp_t gfp, पूर्णांक flags)
अणु
	पूर्णांक error = 0;

	अगर (sctp_is_any(शून्य, addr)) अणु
		error = sctp_copy_local_addr_list(net, dest, scope, gfp, flags);
	पूर्ण अन्यथा अगर (sctp_in_scope(net, addr, scope)) अणु
		/* Now that the address is in scope, check to see अगर
		 * the address type is supported by local sock as
		 * well as the remote peer.
		 */
		अगर ((((AF_INET == addr->sa.sa_family) &&
		      (flags & SCTP_ADDR4_ALLOWED) &&
		      (flags & SCTP_ADDR4_PEERSUPP))) ||
		    (((AF_INET6 == addr->sa.sa_family) &&
		      (flags & SCTP_ADDR6_ALLOWED) &&
		      (flags & SCTP_ADDR6_PEERSUPP))))
			error = sctp_add_bind_addr(dest, addr, माप(*addr),
						   SCTP_ADDR_SRC, gfp);
	पूर्ण

	वापस error;
पूर्ण

/* Is this a wildcard address?  */
पूर्णांक sctp_is_any(काष्ठा sock *sk, स्थिर जोड़ sctp_addr *addr)
अणु
	अचिन्हित लघु fam = 0;
	काष्ठा sctp_af *af;

	/* Try to get the right address family */
	अगर (addr->sa.sa_family != AF_UNSPEC)
		fam = addr->sa.sa_family;
	अन्यथा अगर (sk)
		fam = sk->sk_family;

	af = sctp_get_af_specअगरic(fam);
	अगर (!af)
		वापस 0;

	वापस af->is_any(addr);
पूर्ण

/* Is 'addr' valid for 'scope'?  */
पूर्णांक sctp_in_scope(काष्ठा net *net, स्थिर जोड़ sctp_addr *addr,
		  क्रमागत sctp_scope scope)
अणु
	क्रमागत sctp_scope addr_scope = sctp_scope(addr);

	/* The unusable SCTP addresses will not be considered with
	 * any defined scopes.
	 */
	अगर (SCTP_SCOPE_UNUSABLE == addr_scope)
		वापस 0;
	/*
	 * For INIT and INIT-ACK address list, let L be the level of
	 * requested destination address, sender and receiver
	 * SHOULD include all of its addresses with level greater
	 * than or equal to L.
	 *
	 * Address scoping can be selectively controlled via sysctl
	 * option
	 */
	चयन (net->sctp.scope_policy) अणु
	हाल SCTP_SCOPE_POLICY_DISABLE:
		वापस 1;
	हाल SCTP_SCOPE_POLICY_ENABLE:
		अगर (addr_scope <= scope)
			वापस 1;
		अवरोध;
	हाल SCTP_SCOPE_POLICY_PRIVATE:
		अगर (addr_scope <= scope || SCTP_SCOPE_PRIVATE == addr_scope)
			वापस 1;
		अवरोध;
	हाल SCTP_SCOPE_POLICY_LINK:
		अगर (addr_scope <= scope || SCTP_SCOPE_LINK == addr_scope)
			वापस 1;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक sctp_is_ep_boundall(काष्ठा sock *sk)
अणु
	काष्ठा sctp_bind_addr *bp;
	काष्ठा sctp_sockaddr_entry *addr;

	bp = &sctp_sk(sk)->ep->base.bind_addr;
	अगर (sctp_list_single_entry(&bp->address_list)) अणु
		addr = list_entry(bp->address_list.next,
				  काष्ठा sctp_sockaddr_entry, list);
		अगर (sctp_is_any(sk, &addr->a))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/********************************************************************
 * 3rd Level Abstractions
 ********************************************************************/

/* What is the scope of 'addr'?  */
क्रमागत sctp_scope sctp_scope(स्थिर जोड़ sctp_addr *addr)
अणु
	काष्ठा sctp_af *af;

	af = sctp_get_af_specअगरic(addr->sa.sa_family);
	अगर (!af)
		वापस SCTP_SCOPE_UNUSABLE;

	वापस af->scope((जोड़ sctp_addr *)addr);
पूर्ण
