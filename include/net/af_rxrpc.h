<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* RxRPC kernel service पूर्णांकerface definitions
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#अगर_अघोषित _NET_RXRPC_H
#घोषणा _NET_RXRPC_H

#समावेश <linux/rxrpc.h>
#समावेश <linux/kसमय.स>

काष्ठा key;
काष्ठा sock;
काष्ठा socket;
काष्ठा rxrpc_call;

क्रमागत rxrpc_पूर्णांकerruptibility अणु
	RXRPC_INTERRUPTIBLE,	/* Call is पूर्णांकerruptible */
	RXRPC_PREINTERRUPTIBLE,	/* Call can be cancelled whilst रुकोing क्रम a slot */
	RXRPC_UNINTERRUPTIBLE,	/* Call should not be पूर्णांकerruptible at all */
पूर्ण;

/*
 * Debug ID counter क्रम tracing.
 */
बाह्य atomic_t rxrpc_debug_id;

प्रकार व्योम (*rxrpc_notअगरy_rx_t)(काष्ठा sock *, काष्ठा rxrpc_call *,
				  अचिन्हित दीर्घ);
प्रकार व्योम (*rxrpc_notअगरy_end_tx_t)(काष्ठा sock *, काष्ठा rxrpc_call *,
				      अचिन्हित दीर्घ);
प्रकार व्योम (*rxrpc_notअगरy_new_call_t)(काष्ठा sock *, काष्ठा rxrpc_call *,
					अचिन्हित दीर्घ);
प्रकार व्योम (*rxrpc_discard_new_call_t)(काष्ठा rxrpc_call *, अचिन्हित दीर्घ);
प्रकार व्योम (*rxrpc_user_attach_call_t)(काष्ठा rxrpc_call *, अचिन्हित दीर्घ);

व्योम rxrpc_kernel_new_call_notअगरication(काष्ठा socket *,
					rxrpc_notअगरy_new_call_t,
					rxrpc_discard_new_call_t);
काष्ठा rxrpc_call *rxrpc_kernel_begin_call(काष्ठा socket *,
					   काष्ठा sockaddr_rxrpc *,
					   काष्ठा key *,
					   अचिन्हित दीर्घ,
					   s64,
					   gfp_t,
					   rxrpc_notअगरy_rx_t,
					   bool,
					   क्रमागत rxrpc_पूर्णांकerruptibility,
					   अचिन्हित पूर्णांक);
पूर्णांक rxrpc_kernel_send_data(काष्ठा socket *, काष्ठा rxrpc_call *,
			   काष्ठा msghdr *, माप_प्रकार,
			   rxrpc_notअगरy_end_tx_t);
पूर्णांक rxrpc_kernel_recv_data(काष्ठा socket *, काष्ठा rxrpc_call *,
			   काष्ठा iov_iter *, माप_प्रकार *, bool, u32 *, u16 *);
bool rxrpc_kernel_पात_call(काष्ठा socket *, काष्ठा rxrpc_call *,
			     u32, पूर्णांक, स्थिर अक्षर *);
व्योम rxrpc_kernel_end_call(काष्ठा socket *, काष्ठा rxrpc_call *);
व्योम rxrpc_kernel_get_peer(काष्ठा socket *, काष्ठा rxrpc_call *,
			   काष्ठा sockaddr_rxrpc *);
bool rxrpc_kernel_get_srtt(काष्ठा socket *, काष्ठा rxrpc_call *, u32 *);
पूर्णांक rxrpc_kernel_अक्षरge_accept(काष्ठा socket *, rxrpc_notअगरy_rx_t,
			       rxrpc_user_attach_call_t, अचिन्हित दीर्घ, gfp_t,
			       अचिन्हित पूर्णांक);
व्योम rxrpc_kernel_set_tx_length(काष्ठा socket *, काष्ठा rxrpc_call *, s64);
bool rxrpc_kernel_check_lअगरe(स्थिर काष्ठा socket *, स्थिर काष्ठा rxrpc_call *);
u32 rxrpc_kernel_get_epoch(काष्ठा socket *, काष्ठा rxrpc_call *);
bool rxrpc_kernel_get_reply_समय(काष्ठा socket *, काष्ठा rxrpc_call *,
				 kसमय_प्रकार *);
bool rxrpc_kernel_call_is_complete(काष्ठा rxrpc_call *);
व्योम rxrpc_kernel_set_max_lअगरe(काष्ठा socket *, काष्ठा rxrpc_call *,
			       अचिन्हित दीर्घ);

पूर्णांक rxrpc_sock_set_min_security_level(काष्ठा sock *sk, अचिन्हित पूर्णांक val);

#पूर्ण_अगर /* _NET_RXRPC_H */
