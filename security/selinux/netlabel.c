<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SELinux NetLabel Support
 *
 * This file provides the necessary glue to tie NetLabel पूर्णांकo the SELinux
 * subप्रणाली.
 *
 * Author: Paul Moore <paul@paul-moore.com>
 */

/*
 * (c) Copyright Hewlett-Packard Development Company, L.P., 2007, 2008
 */

#समावेश <linux/spinlock.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/gfp.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <net/sock.h>
#समावेश <net/netlabel.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>

#समावेश "objsec.h"
#समावेश "security.h"
#समावेश "netlabel.h"

/**
 * selinux_netlbl_sidlookup_cached - Cache a SID lookup
 * @skb: the packet
 * @secattr: the NetLabel security attributes
 * @sid: the SID
 *
 * Description:
 * Query the SELinux security server to lookup the correct SID क्रम the given
 * security attributes.  If the query is successful, cache the result to speed
 * up future lookups.  Returns zero on success, negative values on failure.
 *
 */
अटल पूर्णांक selinux_netlbl_sidlookup_cached(काष्ठा sk_buff *skb,
					   u16 family,
					   काष्ठा netlbl_lsm_secattr *secattr,
					   u32 *sid)
अणु
	पूर्णांक rc;

	rc = security_netlbl_secattr_to_sid(&selinux_state, secattr, sid);
	अगर (rc == 0 &&
	    (secattr->flags & NETLBL_SECATTR_CACHEABLE) &&
	    (secattr->flags & NETLBL_SECATTR_CACHE))
		netlbl_cache_add(skb, family, secattr);

	वापस rc;
पूर्ण

/**
 * selinux_netlbl_sock_genattr - Generate the NetLabel socket secattr
 * @sk: the socket
 *
 * Description:
 * Generate the NetLabel security attributes क्रम a socket, making full use of
 * the socket's attribute cache.  Returns a poपूर्णांकer to the security attributes
 * on success, शून्य on failure.
 *
 */
अटल काष्ठा netlbl_lsm_secattr *selinux_netlbl_sock_genattr(काष्ठा sock *sk)
अणु
	पूर्णांक rc;
	काष्ठा sk_security_काष्ठा *sksec = sk->sk_security;
	काष्ठा netlbl_lsm_secattr *secattr;

	अगर (sksec->nlbl_secattr != शून्य)
		वापस sksec->nlbl_secattr;

	secattr = netlbl_secattr_alloc(GFP_ATOMIC);
	अगर (secattr == शून्य)
		वापस शून्य;
	rc = security_netlbl_sid_to_secattr(&selinux_state, sksec->sid,
					    secattr);
	अगर (rc != 0) अणु
		netlbl_secattr_मुक्त(secattr);
		वापस शून्य;
	पूर्ण
	sksec->nlbl_secattr = secattr;

	वापस secattr;
पूर्ण

/**
 * selinux_netlbl_sock_getattr - Get the cached NetLabel secattr
 * @sk: the socket
 * @sid: the SID
 *
 * Query the socket's cached secattr and अगर the SID matches the cached value
 * वापस the cache, otherwise वापस शून्य.
 *
 */
अटल काष्ठा netlbl_lsm_secattr *selinux_netlbl_sock_getattr(
							स्थिर काष्ठा sock *sk,
							u32 sid)
अणु
	काष्ठा sk_security_काष्ठा *sksec = sk->sk_security;
	काष्ठा netlbl_lsm_secattr *secattr = sksec->nlbl_secattr;

	अगर (secattr == शून्य)
		वापस शून्य;

	अगर ((secattr->flags & NETLBL_SECATTR_SECID) &&
	    (secattr->attr.secid == sid))
		वापस secattr;

	वापस शून्य;
पूर्ण

/**
 * selinux_netlbl_cache_invalidate - Invalidate the NetLabel cache
 *
 * Description:
 * Invalidate the NetLabel security attribute mapping cache.
 *
 */
व्योम selinux_netlbl_cache_invalidate(व्योम)
अणु
	netlbl_cache_invalidate();
पूर्ण

/**
 * selinux_netlbl_err - Handle a NetLabel packet error
 * @skb: the packet
 * @error: the error code
 * @gateway: true अगर host is acting as a gateway, false otherwise
 *
 * Description:
 * When a packet is dropped due to a call to avc_has_perm() pass the error
 * code to the NetLabel subप्रणाली so any protocol specअगरic processing can be
 * करोne.  This is safe to call even अगर you are unsure अगर NetLabel labeling is
 * present on the packet, NetLabel is smart enough to only act when it should.
 *
 */
व्योम selinux_netlbl_err(काष्ठा sk_buff *skb, u16 family, पूर्णांक error, पूर्णांक gateway)
अणु
	netlbl_skbuff_err(skb, family, error, gateway);
पूर्ण

/**
 * selinux_netlbl_sk_security_मुक्त - Free the NetLabel fields
 * @sksec: the sk_security_काष्ठा
 *
 * Description:
 * Free all of the memory in the NetLabel fields of a sk_security_काष्ठा.
 *
 */
व्योम selinux_netlbl_sk_security_मुक्त(काष्ठा sk_security_काष्ठा *sksec)
अणु
	अगर (sksec->nlbl_secattr != शून्य)
		netlbl_secattr_मुक्त(sksec->nlbl_secattr);
पूर्ण

/**
 * selinux_netlbl_sk_security_reset - Reset the NetLabel fields
 * @sksec: the sk_security_काष्ठा
 * @family: the socket family
 *
 * Description:
 * Called when the NetLabel state of a sk_security_काष्ठा needs to be reset.
 * The caller is responsible क्रम all the NetLabel sk_security_काष्ठा locking.
 *
 */
व्योम selinux_netlbl_sk_security_reset(काष्ठा sk_security_काष्ठा *sksec)
अणु
	sksec->nlbl_state = NLBL_UNSET;
पूर्ण

/**
 * selinux_netlbl_skbuff_माला_लोid - Get the sid of a packet using NetLabel
 * @skb: the packet
 * @family: protocol family
 * @type: NetLabel labeling protocol type
 * @sid: the SID
 *
 * Description:
 * Call the NetLabel mechanism to get the security attributes of the given
 * packet and use those attributes to determine the correct context/SID to
 * assign to the packet.  Returns zero on success, negative values on failure.
 *
 */
पूर्णांक selinux_netlbl_skbuff_माला_लोid(काष्ठा sk_buff *skb,
				 u16 family,
				 u32 *type,
				 u32 *sid)
अणु
	पूर्णांक rc;
	काष्ठा netlbl_lsm_secattr secattr;

	अगर (!netlbl_enabled()) अणु
		*sid = SECSID_शून्य;
		वापस 0;
	पूर्ण

	netlbl_secattr_init(&secattr);
	rc = netlbl_skbuff_getattr(skb, family, &secattr);
	अगर (rc == 0 && secattr.flags != NETLBL_SECATTR_NONE)
		rc = selinux_netlbl_sidlookup_cached(skb, family,
						     &secattr, sid);
	अन्यथा
		*sid = SECSID_शून्य;
	*type = secattr.type;
	netlbl_secattr_destroy(&secattr);

	वापस rc;
पूर्ण

/**
 * selinux_netlbl_skbuff_setsid - Set the NetLabel on a packet given a sid
 * @skb: the packet
 * @family: protocol family
 * @sid: the SID
 *
 * Description
 * Call the NetLabel mechanism to set the label of a packet using @sid.
 * Returns zero on success, negative values on failure.
 *
 */
पूर्णांक selinux_netlbl_skbuff_setsid(काष्ठा sk_buff *skb,
				 u16 family,
				 u32 sid)
अणु
	पूर्णांक rc;
	काष्ठा netlbl_lsm_secattr secattr_storage;
	काष्ठा netlbl_lsm_secattr *secattr = शून्य;
	काष्ठा sock *sk;

	/* अगर this is a locally generated packet check to see अगर it is alपढ़ोy
	 * being labeled by it's parent socket, अगर it is just निकास */
	sk = skb_to_full_sk(skb);
	अगर (sk != शून्य) अणु
		काष्ठा sk_security_काष्ठा *sksec = sk->sk_security;

		अगर (sksec->nlbl_state != NLBL_REQSKB)
			वापस 0;
		secattr = selinux_netlbl_sock_getattr(sk, sid);
	पूर्ण
	अगर (secattr == शून्य) अणु
		secattr = &secattr_storage;
		netlbl_secattr_init(secattr);
		rc = security_netlbl_sid_to_secattr(&selinux_state, sid,
						    secattr);
		अगर (rc != 0)
			जाओ skbuff_setsid_वापस;
	पूर्ण

	rc = netlbl_skbuff_setattr(skb, family, secattr);

skbuff_setsid_वापस:
	अगर (secattr == &secattr_storage)
		netlbl_secattr_destroy(secattr);
	वापस rc;
पूर्ण

/**
 * selinux_netlbl_sctp_assoc_request - Label an incoming sctp association.
 * @ep: incoming association endpoपूर्णांक.
 * @skb: the packet.
 *
 * Description:
 * A new incoming connection is represented by @ep, ......
 * Returns zero on success, negative values on failure.
 *
 */
पूर्णांक selinux_netlbl_sctp_assoc_request(काष्ठा sctp_endpoपूर्णांक *ep,
				     काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc;
	काष्ठा netlbl_lsm_secattr secattr;
	काष्ठा sk_security_काष्ठा *sksec = ep->base.sk->sk_security;
	काष्ठा sockaddr_in addr4;
	काष्ठा sockaddr_in6 addr6;

	अगर (ep->base.sk->sk_family != PF_INET &&
				ep->base.sk->sk_family != PF_INET6)
		वापस 0;

	netlbl_secattr_init(&secattr);
	rc = security_netlbl_sid_to_secattr(&selinux_state,
					    ep->secid, &secattr);
	अगर (rc != 0)
		जाओ assoc_request_वापस;

	/* Move skb hdr address info to a काष्ठा sockaddr and then call
	 * netlbl_conn_setattr().
	 */
	अगर (ip_hdr(skb)->version == 4) अणु
		addr4.sin_family = AF_INET;
		addr4.sin_addr.s_addr = ip_hdr(skb)->saddr;
		rc = netlbl_conn_setattr(ep->base.sk, (व्योम *)&addr4, &secattr);
	पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_IPV6) && ip_hdr(skb)->version == 6) अणु
		addr6.sin6_family = AF_INET6;
		addr6.sin6_addr = ipv6_hdr(skb)->saddr;
		rc = netlbl_conn_setattr(ep->base.sk, (व्योम *)&addr6, &secattr);
	पूर्ण अन्यथा अणु
		rc = -EAFNOSUPPORT;
	पूर्ण

	अगर (rc == 0)
		sksec->nlbl_state = NLBL_LABELED;

assoc_request_वापस:
	netlbl_secattr_destroy(&secattr);
	वापस rc;
पूर्ण

/**
 * selinux_netlbl_inet_conn_request - Label an incoming stream connection
 * @req: incoming connection request socket
 *
 * Description:
 * A new incoming connection request is represented by @req, we need to label
 * the new request_sock here and the stack will ensure the on-the-wire label
 * will get preserved when a full sock is created once the connection handshake
 * is complete.  Returns zero on success, negative values on failure.
 *
 */
पूर्णांक selinux_netlbl_inet_conn_request(काष्ठा request_sock *req, u16 family)
अणु
	पूर्णांक rc;
	काष्ठा netlbl_lsm_secattr secattr;

	अगर (family != PF_INET && family != PF_INET6)
		वापस 0;

	netlbl_secattr_init(&secattr);
	rc = security_netlbl_sid_to_secattr(&selinux_state, req->secid,
					    &secattr);
	अगर (rc != 0)
		जाओ inet_conn_request_वापस;
	rc = netlbl_req_setattr(req, &secattr);
inet_conn_request_वापस:
	netlbl_secattr_destroy(&secattr);
	वापस rc;
पूर्ण

/**
 * selinux_netlbl_inet_csk_clone - Initialize the newly created sock
 * @sk: the new sock
 *
 * Description:
 * A new connection has been established using @sk, we've alपढ़ोy labeled the
 * socket via the request_sock काष्ठा in selinux_netlbl_inet_conn_request() but
 * we need to set the NetLabel state here since we now have a sock काष्ठाure.
 *
 */
व्योम selinux_netlbl_inet_csk_clone(काष्ठा sock *sk, u16 family)
अणु
	काष्ठा sk_security_काष्ठा *sksec = sk->sk_security;

	अगर (family == PF_INET)
		sksec->nlbl_state = NLBL_LABELED;
	अन्यथा
		sksec->nlbl_state = NLBL_UNSET;
पूर्ण

/**
 * selinux_netlbl_sctp_sk_clone - Copy state to the newly created sock
 * @sk: current sock
 * @newsk: the new sock
 *
 * Description:
 * Called whenever a new socket is created by accept(2) or sctp_peeloff(3).
 */
व्योम selinux_netlbl_sctp_sk_clone(काष्ठा sock *sk, काष्ठा sock *newsk)
अणु
	काष्ठा sk_security_काष्ठा *sksec = sk->sk_security;
	काष्ठा sk_security_काष्ठा *newsksec = newsk->sk_security;

	newsksec->nlbl_state = sksec->nlbl_state;
पूर्ण

/**
 * selinux_netlbl_socket_post_create - Label a socket using NetLabel
 * @sock: the socket to label
 * @family: protocol family
 *
 * Description:
 * Attempt to label a socket using the NetLabel mechanism using the given
 * SID.  Returns zero values on success, negative values on failure.
 *
 */
पूर्णांक selinux_netlbl_socket_post_create(काष्ठा sock *sk, u16 family)
अणु
	पूर्णांक rc;
	काष्ठा sk_security_काष्ठा *sksec = sk->sk_security;
	काष्ठा netlbl_lsm_secattr *secattr;

	अगर (family != PF_INET && family != PF_INET6)
		वापस 0;

	secattr = selinux_netlbl_sock_genattr(sk);
	अगर (secattr == शून्य)
		वापस -ENOMEM;
	rc = netlbl_sock_setattr(sk, family, secattr);
	चयन (rc) अणु
	हाल 0:
		sksec->nlbl_state = NLBL_LABELED;
		अवरोध;
	हाल -EDESTADDRREQ:
		sksec->nlbl_state = NLBL_REQSKB;
		rc = 0;
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

/**
 * selinux_netlbl_sock_rcv_skb - Do an inbound access check using NetLabel
 * @sksec: the sock's sk_security_काष्ठा
 * @skb: the packet
 * @family: protocol family
 * @ad: the audit data
 *
 * Description:
 * Fetch the NetLabel security attributes from @skb and perक्रमm an access check
 * against the receiving socket.  Returns zero on success, negative values on
 * error.
 *
 */
पूर्णांक selinux_netlbl_sock_rcv_skb(काष्ठा sk_security_काष्ठा *sksec,
				काष्ठा sk_buff *skb,
				u16 family,
				काष्ठा common_audit_data *ad)
अणु
	पूर्णांक rc;
	u32 nlbl_sid;
	u32 perm;
	काष्ठा netlbl_lsm_secattr secattr;

	अगर (!netlbl_enabled())
		वापस 0;

	netlbl_secattr_init(&secattr);
	rc = netlbl_skbuff_getattr(skb, family, &secattr);
	अगर (rc == 0 && secattr.flags != NETLBL_SECATTR_NONE)
		rc = selinux_netlbl_sidlookup_cached(skb, family,
						     &secattr, &nlbl_sid);
	अन्यथा
		nlbl_sid = SECINITSID_UNLABELED;
	netlbl_secattr_destroy(&secattr);
	अगर (rc != 0)
		वापस rc;

	चयन (sksec->sclass) अणु
	हाल SECCLASS_UDP_SOCKET:
		perm = UDP_SOCKET__RECVFROM;
		अवरोध;
	हाल SECCLASS_TCP_SOCKET:
		perm = TCP_SOCKET__RECVFROM;
		अवरोध;
	शेष:
		perm = RAWIP_SOCKET__RECVFROM;
	पूर्ण

	rc = avc_has_perm(&selinux_state,
			  sksec->sid, nlbl_sid, sksec->sclass, perm, ad);
	अगर (rc == 0)
		वापस 0;

	अगर (nlbl_sid != SECINITSID_UNLABELED)
		netlbl_skbuff_err(skb, family, rc, 0);
	वापस rc;
पूर्ण

/**
 * selinux_netlbl_option - Is this a NetLabel option
 * @level: the socket level or protocol
 * @optname: the socket option name
 *
 * Description:
 * Returns true अगर @level and @optname refer to a NetLabel option.
 * Helper क्रम selinux_netlbl_socket_setsockopt().
 */
अटल अंतरभूत पूर्णांक selinux_netlbl_option(पूर्णांक level, पूर्णांक optname)
अणु
	वापस (level == IPPROTO_IP && optname == IP_OPTIONS) ||
		(level == IPPROTO_IPV6 && optname == IPV6_HOPOPTS);
पूर्ण

/**
 * selinux_netlbl_socket_setsockopt - Do not allow users to हटाओ a NetLabel
 * @sock: the socket
 * @level: the socket level or protocol
 * @optname: the socket option name
 *
 * Description:
 * Check the setsockopt() call and अगर the user is trying to replace the IP
 * options on a socket and a NetLabel is in place क्रम the socket deny the
 * access; otherwise allow the access.  Returns zero when the access is
 * allowed, -EACCES when denied, and other negative values on error.
 *
 */
पूर्णांक selinux_netlbl_socket_setsockopt(काष्ठा socket *sock,
				     पूर्णांक level,
				     पूर्णांक optname)
अणु
	पूर्णांक rc = 0;
	काष्ठा sock *sk = sock->sk;
	काष्ठा sk_security_काष्ठा *sksec = sk->sk_security;
	काष्ठा netlbl_lsm_secattr secattr;

	अगर (selinux_netlbl_option(level, optname) &&
	    (sksec->nlbl_state == NLBL_LABELED ||
	     sksec->nlbl_state == NLBL_CONNLABELED)) अणु
		netlbl_secattr_init(&secattr);
		lock_sock(sk);
		/* call the netlabel function directly as we want to see the
		 * on-the-wire label that is asचिन्हित via the socket's options
		 * and not the cached netlabel/lsm attributes */
		rc = netlbl_sock_getattr(sk, &secattr);
		release_sock(sk);
		अगर (rc == 0)
			rc = -EACCES;
		अन्यथा अगर (rc == -ENOMSG)
			rc = 0;
		netlbl_secattr_destroy(&secattr);
	पूर्ण

	वापस rc;
पूर्ण

/**
 * selinux_netlbl_socket_connect_helper - Help label a client-side socket on
 * connect
 * @sk: the socket to label
 * @addr: the destination address
 *
 * Description:
 * Attempt to label a connected socket with NetLabel using the given address.
 * Returns zero values on success, negative values on failure.
 *
 */
अटल पूर्णांक selinux_netlbl_socket_connect_helper(काष्ठा sock *sk,
						काष्ठा sockaddr *addr)
अणु
	पूर्णांक rc;
	काष्ठा sk_security_काष्ठा *sksec = sk->sk_security;
	काष्ठा netlbl_lsm_secattr *secattr;

	/* connected sockets are allowed to disconnect when the address family
	 * is set to AF_UNSPEC, अगर that is what is happening we want to reset
	 * the socket */
	अगर (addr->sa_family == AF_UNSPEC) अणु
		netlbl_sock_delattr(sk);
		sksec->nlbl_state = NLBL_REQSKB;
		rc = 0;
		वापस rc;
	पूर्ण
	secattr = selinux_netlbl_sock_genattr(sk);
	अगर (secattr == शून्य) अणु
		rc = -ENOMEM;
		वापस rc;
	पूर्ण
	rc = netlbl_conn_setattr(sk, addr, secattr);
	अगर (rc == 0)
		sksec->nlbl_state = NLBL_CONNLABELED;

	वापस rc;
पूर्ण

/**
 * selinux_netlbl_socket_connect_locked - Label a client-side socket on
 * connect
 * @sk: the socket to label
 * @addr: the destination address
 *
 * Description:
 * Attempt to label a connected socket that alपढ़ोy has the socket locked
 * with NetLabel using the given address.
 * Returns zero values on success, negative values on failure.
 *
 */
पूर्णांक selinux_netlbl_socket_connect_locked(काष्ठा sock *sk,
					 काष्ठा sockaddr *addr)
अणु
	काष्ठा sk_security_काष्ठा *sksec = sk->sk_security;

	अगर (sksec->nlbl_state != NLBL_REQSKB &&
	    sksec->nlbl_state != NLBL_CONNLABELED)
		वापस 0;

	वापस selinux_netlbl_socket_connect_helper(sk, addr);
पूर्ण

/**
 * selinux_netlbl_socket_connect - Label a client-side socket on connect
 * @sk: the socket to label
 * @addr: the destination address
 *
 * Description:
 * Attempt to label a connected socket with NetLabel using the given address.
 * Returns zero values on success, negative values on failure.
 *
 */
पूर्णांक selinux_netlbl_socket_connect(काष्ठा sock *sk, काष्ठा sockaddr *addr)
अणु
	पूर्णांक rc;

	lock_sock(sk);
	rc = selinux_netlbl_socket_connect_locked(sk, addr);
	release_sock(sk);

	वापस rc;
पूर्ण
