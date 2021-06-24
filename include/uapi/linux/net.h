<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * NET		An implementation of the SOCKET network access protocol.
 *		This is the master header file क्रम the Linux NET layer,
 *		or, in plain English: the networking handling part of the
 *		kernel.
 *
 * Version:	@(#)net.h	1.0.3	05/25/93
 *
 * Authors:	Orest Zborowski, <obz@Kodak.COM>
 *		Ross Biro
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *
 *		This program is मुक्त software; you can redistribute it and/or
 *		modअगरy it under the terms of the GNU General Public License
 *		as published by the Free Software Foundation; either version
 *		2 of the License, or (at your option) any later version.
 */
#अगर_अघोषित _UAPI_LINUX_NET_H
#घोषणा _UAPI_LINUX_NET_H

#समावेश <linux/socket.h>
#समावेश <यंत्र/socket.h>

#घोषणा NPROTO		AF_MAX

#घोषणा SYS_SOCKET	1		/* sys_socket(2)		*/
#घोषणा SYS_BIND	2		/* sys_bind(2)			*/
#घोषणा SYS_CONNECT	3		/* sys_connect(2)		*/
#घोषणा SYS_LISTEN	4		/* sys_listen(2)		*/
#घोषणा SYS_ACCEPT	5		/* sys_accept(2)		*/
#घोषणा SYS_GETSOCKNAME	6		/* sys_माला_लोockname(2)		*/
#घोषणा SYS_GETPEERNAME	7		/* sys_getpeername(2)		*/
#घोषणा SYS_SOCKETPAIR	8		/* sys_socketpair(2)		*/
#घोषणा SYS_SEND	9		/* sys_send(2)			*/
#घोषणा SYS_RECV	10		/* sys_recv(2)			*/
#घोषणा SYS_SENDTO	11		/* sys_sendto(2)		*/
#घोषणा SYS_RECVFROM	12		/* sys_recvfrom(2)		*/
#घोषणा SYS_SHUTDOWN	13		/* sys_shutकरोwn(2)		*/
#घोषणा SYS_SETSOCKOPT	14		/* sys_setsockopt(2)		*/
#घोषणा SYS_GETSOCKOPT	15		/* sys_माला_लोockopt(2)		*/
#घोषणा SYS_SENDMSG	16		/* sys_sendmsg(2)		*/
#घोषणा SYS_RECVMSG	17		/* sys_recvmsg(2)		*/
#घोषणा SYS_ACCEPT4	18		/* sys_accept4(2)		*/
#घोषणा SYS_RECVMMSG	19		/* sys_recvmmsg(2)		*/
#घोषणा SYS_SENDMMSG	20		/* sys_sendmmsg(2)		*/

प्रकार क्रमागत अणु
	SS_FREE = 0,			/* not allocated		*/
	SS_UNCONNECTED,			/* unconnected to any socket	*/
	SS_CONNECTING,			/* in process of connecting	*/
	SS_CONNECTED,			/* connected to socket		*/
	SS_DISCONNECTING		/* in process of disconnecting	*/
पूर्ण socket_state;

#घोषणा __SO_ACCEPTCON	(1 << 16)	/* perक्रमmed a listen		*/

#पूर्ण_अगर /* _UAPI_LINUX_NET_H */
