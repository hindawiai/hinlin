<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later WITH Linux-syscall-note */
/* Types and definitions क्रम AF_RXRPC.
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#अगर_अघोषित _UAPI_LINUX_RXRPC_H
#घोषणा _UAPI_LINUX_RXRPC_H

#समावेश <linux/types.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>

/*
 * RxRPC socket address
 */
काष्ठा sockaddr_rxrpc अणु
	__kernel_sa_family_t	srx_family;	/* address family */
	__u16			srx_service;	/* service desired */
	__u16			transport_type;	/* type of transport socket (SOCK_DGRAM) */
	__u16			transport_len;	/* length of transport address */
	जोड़ अणु
		__kernel_sa_family_t family;	/* transport address family */
		काष्ठा sockaddr_in sin;		/* IPv4 transport address */
		काष्ठा sockaddr_in6 sin6;	/* IPv6 transport address */
	पूर्ण transport;
पूर्ण;

/*
 * RxRPC socket options
 */
#घोषणा RXRPC_SECURITY_KEY		1	/* [clnt] set client security key */
#घोषणा RXRPC_SECURITY_KEYRING		2	/* [srvr] set ring of server security keys */
#घोषणा RXRPC_EXCLUSIVE_CONNECTION	3	/* Deprecated; use RXRPC_EXCLUSIVE_CALL instead */
#घोषणा RXRPC_MIN_SECURITY_LEVEL	4	/* minimum security level */
#घोषणा RXRPC_UPGRADEABLE_SERVICE	5	/* Upgrade service[0] -> service[1] */
#घोषणा RXRPC_SUPPORTED_CMSG		6	/* Get highest supported control message type */

/*
 * RxRPC control messages
 * - If neither पात or accept are specअगरied, the message is a data message.
 * - terminal messages mean that a user call ID tag can be recycled
 * - s/r/- indicate whether these are applicable to sendmsg() and/or recvmsg()
 */
क्रमागत rxrpc_cmsg_type अणु
	RXRPC_USER_CALL_ID	= 1,	/* sr: user call ID specअगरier */
	RXRPC_ABORT		= 2,	/* sr: पात request / notअगरication [terminal] */
	RXRPC_ACK		= 3,	/* -r: [Service] RPC op final ACK received [terminal] */
	RXRPC_NET_ERROR		= 5,	/* -r: network error received [terminal] */
	RXRPC_BUSY		= 6,	/* -r: server busy received [terminal] */
	RXRPC_LOCAL_ERROR	= 7,	/* -r: local error generated [terminal] */
	RXRPC_NEW_CALL		= 8,	/* -r: [Service] new incoming call notअगरication */
	RXRPC_EXCLUSIVE_CALL	= 10,	/* s-: Call should be on exclusive connection */
	RXRPC_UPGRADE_SERVICE	= 11,	/* s-: Request service upgrade क्रम client call */
	RXRPC_TX_LENGTH		= 12,	/* s-: Total length of Tx data */
	RXRPC_SET_CALL_TIMEOUT	= 13,	/* s-: Set one or more call समयouts */
	RXRPC_CHARGE_ACCEPT	= 14,	/* s-: Charge the accept pool with a user call ID */
	RXRPC__SUPPORTED
पूर्ण;

/*
 * RxRPC security levels
 */
#घोषणा RXRPC_SECURITY_PLAIN	0	/* plain secure-checksummed packets only */
#घोषणा RXRPC_SECURITY_AUTH	1	/* authenticated packets */
#घोषणा RXRPC_SECURITY_ENCRYPT	2	/* encrypted packets */

/*
 * RxRPC security indices
 */
#घोषणा RXRPC_SECURITY_NONE	0	/* no security protocol */
#घोषणा RXRPC_SECURITY_RXKAD	2	/* kaserver or kerberos 4 */
#घोषणा RXRPC_SECURITY_RXGK	4	/* gssapi-based */
#घोषणा RXRPC_SECURITY_RXK5	5	/* kerberos 5 */

/*
 * RxRPC-level पात codes
 */
#घोषणा RX_CALL_DEAD		-1	/* call/conn has been inactive and is shut करोwn */
#घोषणा RX_INVALID_OPERATION	-2	/* invalid operation requested / attempted */
#घोषणा RX_CALL_TIMEOUT		-3	/* call समयout exceeded */
#घोषणा RX_खातापूर्ण			-4	/* unexpected end of data on पढ़ो op */
#घोषणा RX_PROTOCOL_ERROR	-5	/* low-level protocol error */
#घोषणा RX_USER_ABORT		-6	/* generic user पात */
#घोषणा RX_ADDRINUSE		-7	/* UDP port in use */
#घोषणा RX_DEBUGI_BADTYPE	-8	/* bad debugging packet type */

/*
 * (un)marshalling पात codes (rxgen)
 */
#घोषणा RXGEN_CC_MARSHAL	-450
#घोषणा RXGEN_CC_UNMARSHAL	-451
#घोषणा RXGEN_SS_MARSHAL	-452
#घोषणा RXGEN_SS_UNMARSHAL	-453
#घोषणा RXGEN_DECODE		-454
#घोषणा RXGEN_OPCODE		-455
#घोषणा RXGEN_SS_XDRFREE	-456
#घोषणा RXGEN_CC_XDRFREE	-457

/*
 * Rx kerberos security पात codes
 * - unक्रमtunately we have no generalised security पात codes to say things
 *   like "unsupported security", so we have to use these instead and hope the
 *   other side understands
 */
#घोषणा RXKADINCONSISTENCY	19270400	/* security module काष्ठाure inconsistent */
#घोषणा RXKADPACKETSHORT	19270401	/* packet too लघु क्रम security challenge */
#घोषणा RXKADLEVELFAIL		19270402	/* security level negotiation failed */
#घोषणा RXKADTICKETLEN		19270403	/* ticket length too लघु or too दीर्घ */
#घोषणा RXKADOUTOFSEQUENCE	19270404	/* packet had bad sequence number */
#घोषणा RXKADNOAUTH		19270405	/* caller not authorised */
#घोषणा RXKADBADKEY		19270406	/* illegal key: bad parity or weak */
#घोषणा RXKADBADTICKET		19270407	/* security object was passed a bad ticket */
#घोषणा RXKADUNKNOWNKEY		19270408	/* ticket contained unknown key version number */
#घोषणा RXKADEXPIRED		19270409	/* authentication expired */
#घोषणा RXKADSEALEDINCON	19270410	/* sealed data inconsistent */
#घोषणा RXKADDATALEN		19270411	/* user data too दीर्घ */
#घोषणा RXKADILLEGALLEVEL	19270412	/* caller not authorised to use encrypted conns */

#पूर्ण_अगर /* _UAPI_LINUX_RXRPC_H */
