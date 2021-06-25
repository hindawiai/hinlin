<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Null security operations.
 *
 * Copyright (C) 2016 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <net/af_rxrpc.h>
#समावेश "ar-internal.h"

अटल पूर्णांक none_init_connection_security(काष्ठा rxrpc_connection *conn,
					 काष्ठा rxrpc_key_token *token)
अणु
	वापस 0;
पूर्ण

/*
 * Work out how much data we can put in an unsecured packet.
 */
अटल पूर्णांक none_how_much_data(काष्ठा rxrpc_call *call, माप_प्रकार reमुख्य,
			       माप_प्रकार *_buf_size, माप_प्रकार *_data_size, माप_प्रकार *_offset)
अणु
	*_buf_size = *_data_size = min_t(माप_प्रकार, reमुख्य, RXRPC_JUMBO_DATALEN);
	*_offset = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक none_secure_packet(काष्ठा rxrpc_call *call, काष्ठा sk_buff *skb,
			      माप_प्रकार data_size)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक none_verअगरy_packet(काष्ठा rxrpc_call *call, काष्ठा sk_buff *skb,
			      अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक len,
			      rxrpc_seq_t seq, u16 expected_cksum)
अणु
	वापस 0;
पूर्ण

अटल व्योम none_मुक्त_call_crypto(काष्ठा rxrpc_call *call)
अणु
पूर्ण

अटल व्योम none_locate_data(काष्ठा rxrpc_call *call, काष्ठा sk_buff *skb,
			     अचिन्हित पूर्णांक *_offset, अचिन्हित पूर्णांक *_len)
अणु
पूर्ण

अटल पूर्णांक none_respond_to_challenge(काष्ठा rxrpc_connection *conn,
				     काष्ठा sk_buff *skb,
				     u32 *_पात_code)
अणु
	काष्ठा rxrpc_skb_priv *sp = rxrpc_skb(skb);

	trace_rxrpc_rx_eproto(शून्य, sp->hdr.serial,
			      tracepoपूर्णांक_string("chall_none"));
	वापस -EPROTO;
पूर्ण

अटल पूर्णांक none_verअगरy_response(काष्ठा rxrpc_connection *conn,
				काष्ठा sk_buff *skb,
				u32 *_पात_code)
अणु
	काष्ठा rxrpc_skb_priv *sp = rxrpc_skb(skb);

	trace_rxrpc_rx_eproto(शून्य, sp->hdr.serial,
			      tracepoपूर्णांक_string("resp_none"));
	वापस -EPROTO;
पूर्ण

अटल व्योम none_clear(काष्ठा rxrpc_connection *conn)
अणु
पूर्ण

अटल पूर्णांक none_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम none_निकास(व्योम)
अणु
पूर्ण

/*
 * RxRPC Kerberos-based security
 */
स्थिर काष्ठा rxrpc_security rxrpc_no_security = अणु
	.name				= "none",
	.security_index			= RXRPC_SECURITY_NONE,
	.init				= none_init,
	.निकास				= none_निकास,
	.init_connection_security	= none_init_connection_security,
	.मुक्त_call_crypto		= none_मुक्त_call_crypto,
	.how_much_data			= none_how_much_data,
	.secure_packet			= none_secure_packet,
	.verअगरy_packet			= none_verअगरy_packet,
	.locate_data			= none_locate_data,
	.respond_to_challenge		= none_respond_to_challenge,
	.verअगरy_response		= none_verअगरy_response,
	.clear				= none_clear,
पूर्ण;
