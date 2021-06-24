<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * SELinux पूर्णांकerface to the NetLabel subप्रणाली
 *
 * Author: Paul Moore <paul@paul-moore.com>
 */

/*
 * (c) Copyright Hewlett-Packard Development Company, L.P., 2006
 */

#अगर_अघोषित _SELINUX_NETLABEL_H_
#घोषणा _SELINUX_NETLABEL_H_

#समावेश <linux/types.h>
#समावेश <linux/fs.h>
#समावेश <linux/net.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <net/request_sock.h>
#समावेश <net/sctp/काष्ठाs.h>

#समावेश "avc.h"
#समावेश "objsec.h"

#अगर_घोषित CONFIG_NETLABEL
व्योम selinux_netlbl_cache_invalidate(व्योम);

व्योम selinux_netlbl_err(काष्ठा sk_buff *skb, u16 family, पूर्णांक error,
			पूर्णांक gateway);

व्योम selinux_netlbl_sk_security_मुक्त(काष्ठा sk_security_काष्ठा *sksec);
व्योम selinux_netlbl_sk_security_reset(काष्ठा sk_security_काष्ठा *sksec);

पूर्णांक selinux_netlbl_skbuff_माला_लोid(काष्ठा sk_buff *skb,
				 u16 family,
				 u32 *type,
				 u32 *sid);
पूर्णांक selinux_netlbl_skbuff_setsid(काष्ठा sk_buff *skb,
				 u16 family,
				 u32 sid);
पूर्णांक selinux_netlbl_sctp_assoc_request(काष्ठा sctp_endpoपूर्णांक *ep,
				     काष्ठा sk_buff *skb);
पूर्णांक selinux_netlbl_inet_conn_request(काष्ठा request_sock *req, u16 family);
व्योम selinux_netlbl_inet_csk_clone(काष्ठा sock *sk, u16 family);
व्योम selinux_netlbl_sctp_sk_clone(काष्ठा sock *sk, काष्ठा sock *newsk);
पूर्णांक selinux_netlbl_socket_post_create(काष्ठा sock *sk, u16 family);
पूर्णांक selinux_netlbl_sock_rcv_skb(काष्ठा sk_security_काष्ठा *sksec,
				काष्ठा sk_buff *skb,
				u16 family,
				काष्ठा common_audit_data *ad);
पूर्णांक selinux_netlbl_socket_setsockopt(काष्ठा socket *sock,
				     पूर्णांक level,
				     पूर्णांक optname);
पूर्णांक selinux_netlbl_socket_connect(काष्ठा sock *sk, काष्ठा sockaddr *addr);
पूर्णांक selinux_netlbl_socket_connect_locked(काष्ठा sock *sk,
					 काष्ठा sockaddr *addr);

#अन्यथा
अटल अंतरभूत व्योम selinux_netlbl_cache_invalidate(व्योम)
अणु
	वापस;
पूर्ण

अटल अंतरभूत व्योम selinux_netlbl_err(काष्ठा sk_buff *skb,
				      u16 family,
				      पूर्णांक error,
				      पूर्णांक gateway)
अणु
	वापस;
पूर्ण

अटल अंतरभूत व्योम selinux_netlbl_sk_security_मुक्त(
					       काष्ठा sk_security_काष्ठा *sksec)
अणु
	वापस;
पूर्ण

अटल अंतरभूत व्योम selinux_netlbl_sk_security_reset(
					       काष्ठा sk_security_काष्ठा *sksec)
अणु
	वापस;
पूर्ण

अटल अंतरभूत पूर्णांक selinux_netlbl_skbuff_माला_लोid(काष्ठा sk_buff *skb,
					       u16 family,
					       u32 *type,
					       u32 *sid)
अणु
	*type = NETLBL_NLTYPE_NONE;
	*sid = SECSID_शून्य;
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक selinux_netlbl_skbuff_setsid(काष्ठा sk_buff *skb,
					       u16 family,
					       u32 sid)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक selinux_netlbl_sctp_assoc_request(काष्ठा sctp_endpoपूर्णांक *ep,
						    काष्ठा sk_buff *skb)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक selinux_netlbl_inet_conn_request(काष्ठा request_sock *req,
						   u16 family)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम selinux_netlbl_inet_csk_clone(काष्ठा sock *sk, u16 family)
अणु
	वापस;
पूर्ण
अटल अंतरभूत व्योम selinux_netlbl_sctp_sk_clone(काष्ठा sock *sk,
						काष्ठा sock *newsk)
अणु
	वापस;
पूर्ण
अटल अंतरभूत पूर्णांक selinux_netlbl_socket_post_create(काष्ठा sock *sk,
						    u16 family)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक selinux_netlbl_sock_rcv_skb(काष्ठा sk_security_काष्ठा *sksec,
					      काष्ठा sk_buff *skb,
					      u16 family,
					      काष्ठा common_audit_data *ad)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक selinux_netlbl_socket_setsockopt(काष्ठा socket *sock,
						   पूर्णांक level,
						   पूर्णांक optname)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक selinux_netlbl_socket_connect(काष्ठा sock *sk,
						काष्ठा sockaddr *addr)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक selinux_netlbl_socket_connect_locked(काष्ठा sock *sk,
						       काष्ठा sockaddr *addr)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_NETLABEL */

#पूर्ण_अगर
