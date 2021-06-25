<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* RxRPC security handling
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/module.h>
#समावेश <linux/net.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/udp.h>
#समावेश <linux/crypto.h>
#समावेश <net/sock.h>
#समावेश <net/af_rxrpc.h>
#समावेश <keys/rxrpc-type.h>
#समावेश "ar-internal.h"

अटल स्थिर काष्ठा rxrpc_security *rxrpc_security_types[] = अणु
	[RXRPC_SECURITY_NONE]	= &rxrpc_no_security,
#अगर_घोषित CONFIG_RXKAD
	[RXRPC_SECURITY_RXKAD]	= &rxkad,
#पूर्ण_अगर
पूर्ण;

पूर्णांक __init rxrpc_init_security(व्योम)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < ARRAY_SIZE(rxrpc_security_types); i++) अणु
		अगर (rxrpc_security_types[i]) अणु
			ret = rxrpc_security_types[i]->init();
			अगर (ret < 0)
				जाओ failed;
		पूर्ण
	पूर्ण

	वापस 0;

failed:
	क्रम (i--; i >= 0; i--)
		अगर (rxrpc_security_types[i])
			rxrpc_security_types[i]->निकास();
	वापस ret;
पूर्ण

व्योम rxrpc_निकास_security(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rxrpc_security_types); i++)
		अगर (rxrpc_security_types[i])
			rxrpc_security_types[i]->निकास();
पूर्ण

/*
 * look up an rxrpc security module
 */
स्थिर काष्ठा rxrpc_security *rxrpc_security_lookup(u8 security_index)
अणु
	अगर (security_index >= ARRAY_SIZE(rxrpc_security_types))
		वापस शून्य;
	वापस rxrpc_security_types[security_index];
पूर्ण

/*
 * initialise the security on a client connection
 */
पूर्णांक rxrpc_init_client_conn_security(काष्ठा rxrpc_connection *conn)
अणु
	स्थिर काष्ठा rxrpc_security *sec;
	काष्ठा rxrpc_key_token *token;
	काष्ठा key *key = conn->params.key;
	पूर्णांक ret;

	_enter("{%d},{%x}", conn->debug_id, key_serial(key));

	अगर (!key)
		वापस 0;

	ret = key_validate(key);
	अगर (ret < 0)
		वापस ret;

	क्रम (token = key->payload.data[0]; token; token = token->next) अणु
		sec = rxrpc_security_lookup(token->security_index);
		अगर (sec)
			जाओ found;
	पूर्ण
	वापस -EKEYREJECTED;

found:
	conn->security = sec;

	ret = conn->security->init_connection_security(conn, token);
	अगर (ret < 0) अणु
		conn->security = &rxrpc_no_security;
		वापस ret;
	पूर्ण

	_leave(" = 0");
	वापस 0;
पूर्ण

/*
 * Set the ops a server connection.
 */
स्थिर काष्ठा rxrpc_security *rxrpc_get_incoming_security(काष्ठा rxrpc_sock *rx,
							 काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा rxrpc_security *sec;
	काष्ठा rxrpc_skb_priv *sp = rxrpc_skb(skb);

	_enter("");

	sec = rxrpc_security_lookup(sp->hdr.securityIndex);
	अगर (!sec) अणु
		trace_rxrpc_पात(0, "SVS",
				  sp->hdr.cid, sp->hdr.callNumber, sp->hdr.seq,
				  RX_INVALID_OPERATION, EKEYREJECTED);
		skb->mark = RXRPC_SKB_MARK_REJECT_ABORT;
		skb->priority = RX_INVALID_OPERATION;
		वापस शून्य;
	पूर्ण

	अगर (sp->hdr.securityIndex != RXRPC_SECURITY_NONE &&
	    !rx->securities) अणु
		trace_rxrpc_पात(0, "SVR",
				  sp->hdr.cid, sp->hdr.callNumber, sp->hdr.seq,
				  RX_INVALID_OPERATION, EKEYREJECTED);
		skb->mark = RXRPC_SKB_MARK_REJECT_ABORT;
		skb->priority = sec->no_key_पात;
		वापस शून्य;
	पूर्ण

	वापस sec;
पूर्ण

/*
 * Find the security key क्रम a server connection.
 */
काष्ठा key *rxrpc_look_up_server_security(काष्ठा rxrpc_connection *conn,
					  काष्ठा sk_buff *skb,
					  u32 kvno, u32 enctype)
अणु
	काष्ठा rxrpc_skb_priv *sp = rxrpc_skb(skb);
	काष्ठा rxrpc_sock *rx;
	काष्ठा key *key = ERR_PTR(-EKEYREJECTED);
	key_ref_t kref = शून्य;
	अक्षर kdesc[5 + 1 + 3 + 1 + 12 + 1 + 12 + 1];
	पूर्णांक ret;

	_enter("");

	अगर (enctype)
		प्र_लिखो(kdesc, "%u:%u:%u:%u",
			sp->hdr.serviceId, sp->hdr.securityIndex, kvno, enctype);
	अन्यथा अगर (kvno)
		प्र_लिखो(kdesc, "%u:%u:%u",
			sp->hdr.serviceId, sp->hdr.securityIndex, kvno);
	अन्यथा
		प्र_लिखो(kdesc, "%u:%u",
			sp->hdr.serviceId, sp->hdr.securityIndex);

	rcu_पढ़ो_lock();

	rx = rcu_dereference(conn->params.local->service);
	अगर (!rx)
		जाओ out;

	/* look through the service's keyring */
	kref = keyring_search(make_key_ref(rx->securities, 1UL),
			      &key_type_rxrpc_s, kdesc, true);
	अगर (IS_ERR(kref)) अणु
		key = ERR_CAST(kref);
		जाओ out;
	पूर्ण

	key = key_ref_to_ptr(kref);

	ret = key_validate(key);
	अगर (ret < 0) अणु
		key_put(key);
		key = ERR_PTR(ret);
		जाओ out;
	पूर्ण

out:
	rcu_पढ़ो_unlock();
	वापस key;
पूर्ण
