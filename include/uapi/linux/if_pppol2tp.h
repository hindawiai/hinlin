<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/***************************************************************************
 * Linux PPP over L2TP (PPPoL2TP) Socket Implementation (RFC 2661)
 *
 * This file supplies definitions required by the PPP over L2TP driver
 * (l2tp_ppp.c).  All version inक्रमmation wrt this file is located in l2tp_ppp.c
 *
 * License:
 *		This program is मुक्त software; you can redistribute it and/or
 *		modअगरy it under the terms of the GNU General Public License
 *		as published by the Free Software Foundation; either version
 *		2 of the License, or (at your option) any later version.
 *
 */

#अगर_अघोषित _UAPI__LINUX_IF_PPPOL2TP_H
#घोषणा _UAPI__LINUX_IF_PPPOL2TP_H

#समावेश <linux/types.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <linux/l2tp.h>

/* Structure used to connect() the socket to a particular tunnel UDP
 * socket over IPv4.
 */
काष्ठा pppol2tp_addr अणु
	__kernel_pid_t	pid;		/* pid that owns the fd.
					 * 0 => current */
	पूर्णांक	fd;			/* FD of UDP socket to use */

	काष्ठा sockaddr_in addr;	/* IP address and port to send to */

	__u16 s_tunnel, s_session;	/* For matching incoming packets */
	__u16 d_tunnel, d_session;	/* For sending outgoing packets */
पूर्ण;

/* Structure used to connect() the socket to a particular tunnel UDP
 * socket over IPv6.
 */
काष्ठा pppol2tpin6_addr अणु
	__kernel_pid_t	pid;		/* pid that owns the fd.
					 * 0 => current */
	पूर्णांक	fd;			/* FD of UDP socket to use */

	__u16 s_tunnel, s_session;	/* For matching incoming packets */
	__u16 d_tunnel, d_session;	/* For sending outgoing packets */

	काष्ठा sockaddr_in6 addr;	/* IP address and port to send to */
पूर्ण;

/* The L2TPv3 protocol changes tunnel and session ids from 16 to 32
 * bits. So we need a dअगरferent sockaddr काष्ठाure.
 */
काष्ठा pppol2tpv3_addr अणु
	__kernel_pid_t	pid;		/* pid that owns the fd.
					 * 0 => current */
	पूर्णांक	fd;			/* FD of UDP or IP socket to use */

	काष्ठा sockaddr_in addr;	/* IP address and port to send to */

	__u32 s_tunnel, s_session;	/* For matching incoming packets */
	__u32 d_tunnel, d_session;	/* For sending outgoing packets */
पूर्ण;

काष्ठा pppol2tpv3in6_addr अणु
	__kernel_pid_t	pid;		/* pid that owns the fd.
					 * 0 => current */
	पूर्णांक	fd;			/* FD of UDP or IP socket to use */

	__u32 s_tunnel, s_session;	/* For matching incoming packets */
	__u32 d_tunnel, d_session;	/* For sending outgoing packets */

	काष्ठा sockaddr_in6 addr;	/* IP address and port to send to */
पूर्ण;

/* Socket options:
 * DEBUG	- biपंचांगask of debug message categories (not used)
 * SENDSEQ	- 0 => करोn't send packets with sequence numbers
 *		  1 => send packets with sequence numbers
 * RECVSEQ	- 0 => receive packet sequence numbers are optional
 *		  1 => drop receive packets without sequence numbers
 * LNSMODE	- 0 => act as LAC.
 *		  1 => act as LNS.
 * REORDERTO	- reorder समयout (in millisecs). If 0, करोn't try to reorder.
 */
क्रमागत अणु
	PPPOL2TP_SO_DEBUG	= 1,
	PPPOL2TP_SO_RECVSEQ	= 2,
	PPPOL2TP_SO_SENDSEQ	= 3,
	PPPOL2TP_SO_LNSMODE	= 4,
	PPPOL2TP_SO_REORDERTO	= 5,
पूर्ण;

/* Debug message categories क्रम the DEBUG socket option (deprecated) */
क्रमागत अणु
	PPPOL2TP_MSG_DEBUG	= L2TP_MSG_DEBUG,
	PPPOL2TP_MSG_CONTROL	= L2TP_MSG_CONTROL,
	PPPOL2TP_MSG_SEQ	= L2TP_MSG_SEQ,
	PPPOL2TP_MSG_DATA	= L2TP_MSG_DATA,
पूर्ण;



#पूर्ण_अगर /* _UAPI__LINUX_IF_PPPOL2TP_H */
