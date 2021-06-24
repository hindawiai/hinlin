<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * These are the खुला elements of the Linux kernel AX.25 code. A similar
 * file netrom.h exists क्रम the NET/ROM protocol.
 */

#अगर_अघोषित	AX25_KERNEL_H
#घोषणा	AX25_KERNEL_H

#समावेश <linux/socket.h>

#घोषणा AX25_MTU	256
#घोषणा AX25_MAX_DIGIS  8

#घोषणा AX25_WINDOW	1
#घोषणा AX25_T1		2
#घोषणा AX25_N2		3
#घोषणा AX25_T3		4
#घोषणा AX25_T2		5
#घोषणा	AX25_BACKOFF	6
#घोषणा	AX25_EXTSEQ	7
#घोषणा	AX25_PIDINCL	8
#घोषणा AX25_IDLE	9
#घोषणा AX25_PACLEN	10
#घोषणा AX25_IAMDIGI	12

#घोषणा AX25_KILL	99

#घोषणा SIOCAX25GETUID		(SIOCPROTOPRIVATE+0)
#घोषणा SIOCAX25ADDUID		(SIOCPROTOPRIVATE+1)
#घोषणा SIOCAX25DELUID		(SIOCPROTOPRIVATE+2)
#घोषणा SIOCAX25NOUID		(SIOCPROTOPRIVATE+3)
#घोषणा SIOCAX25OPTRT		(SIOCPROTOPRIVATE+7)
#घोषणा SIOCAX25CTLCON		(SIOCPROTOPRIVATE+8)
#घोषणा SIOCAX25GETINFOOLD	(SIOCPROTOPRIVATE+9)
#घोषणा SIOCAX25ADDFWD		(SIOCPROTOPRIVATE+10)
#घोषणा SIOCAX25DELFWD		(SIOCPROTOPRIVATE+11)
#घोषणा SIOCAX25DEVCTL          (SIOCPROTOPRIVATE+12)
#घोषणा SIOCAX25GETINFO         (SIOCPROTOPRIVATE+13)

#घोषणा AX25_SET_RT_IPMODE	2

#घोषणा AX25_NOUID_DEFAULT	0
#घोषणा AX25_NOUID_BLOCK	1

प्रकार काष्ठा अणु
	अक्षर		ax25_call[7];	/* 6 call + SSID (shअगरted ascii!) */
पूर्ण ax25_address;

काष्ठा sockaddr_ax25 अणु
	__kernel_sa_family_t sax25_family;
	ax25_address	sax25_call;
	पूर्णांक		sax25_ndigis;
	/* Digipeater ax25_address sets follow */
पूर्ण;

#घोषणा sax25_uid	sax25_ndigis

काष्ठा full_sockaddr_ax25 अणु
	काष्ठा sockaddr_ax25 fsa_ax25;
	ax25_address	fsa_digipeater[AX25_MAX_DIGIS];
पूर्ण;

काष्ठा ax25_routes_काष्ठा अणु
	ax25_address	port_addr;
	ax25_address	dest_addr;
	अचिन्हित अक्षर	digi_count;
	ax25_address	digi_addr[AX25_MAX_DIGIS];
पूर्ण;

काष्ठा ax25_route_opt_काष्ठा अणु
	ax25_address	port_addr;
	ax25_address	dest_addr;
	पूर्णांक		cmd;
	पूर्णांक		arg;
पूर्ण;

काष्ठा ax25_ctl_काष्ठा अणु
        ax25_address            port_addr;
        ax25_address            source_addr;
        ax25_address            dest_addr;
        अचिन्हित पूर्णांक            cmd;
        अचिन्हित दीर्घ           arg;
        अचिन्हित अक्षर           digi_count;
        ax25_address            digi_addr[AX25_MAX_DIGIS];
पूर्ण;

/* this will go away. Please करो not export to user land */
काष्ठा ax25_info_काष्ठा_deprecated अणु
	अचिन्हित पूर्णांक	n2, n2count;
	अचिन्हित पूर्णांक	t1, t1समयr;
	अचिन्हित पूर्णांक	t2, t2समयr;
	अचिन्हित पूर्णांक	t3, t3समयr;
	अचिन्हित पूर्णांक	idle, idleसमयr;
	अचिन्हित पूर्णांक	state;
	अचिन्हित पूर्णांक	rcv_q, snd_q;
पूर्ण;

काष्ठा ax25_info_काष्ठा अणु
	अचिन्हित पूर्णांक	n2, n2count;
	अचिन्हित पूर्णांक	t1, t1समयr;
	अचिन्हित पूर्णांक	t2, t2समयr;
	अचिन्हित पूर्णांक	t3, t3समयr;
	अचिन्हित पूर्णांक	idle, idleसमयr;
	अचिन्हित पूर्णांक	state;
	अचिन्हित पूर्णांक	rcv_q, snd_q;
	अचिन्हित पूर्णांक	vs, vr, va, vs_max;
	अचिन्हित पूर्णांक	paclen;
	अचिन्हित पूर्णांक	winकरोw;
पूर्ण;

काष्ठा ax25_fwd_काष्ठा अणु
	ax25_address	port_from;
	ax25_address	port_to;
पूर्ण;

#पूर्ण_अगर
