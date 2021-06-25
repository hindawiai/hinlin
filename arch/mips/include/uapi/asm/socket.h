<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1997, 1999, 2000, 2001 Ralf Baechle
 * Copyright (C) 2000, 2001 Silicon Graphics, Inc.
 */
#अगर_अघोषित _UAPI_ASM_SOCKET_H
#घोषणा _UAPI_ASM_SOCKET_H

#समावेश <linux/posix_types.h>
#समावेश <यंत्र/sockios.h>

/*
 * For setsockopt(2)
 *
 * This defines are ABI conक्रमmant as far as Linux supports these ...
 */
#घोषणा SOL_SOCKET	0xffff

#घोषणा SO_DEBUG	0x0001	/* Record debugging inक्रमmation.  */
#घोषणा SO_REUSEADDR	0x0004	/* Allow reuse of local addresses.  */
#घोषणा SO_KEEPALIVE	0x0008	/* Keep connections alive and send
				   SIGPIPE when they die.  */
#घोषणा SO_DONTROUTE	0x0010	/* Don't करो local routing.  */
#घोषणा SO_BROADCAST	0x0020	/* Allow transmission of
				   broadcast messages.	*/
#घोषणा SO_LINGER	0x0080	/* Block on बंद of a reliable
				   socket to transmit pending data.  */
#घोषणा SO_OOBINLINE 0x0100	/* Receive out-of-band data in-band.  */
#घोषणा SO_REUSEPORT 0x0200	/* Allow local address and port reuse.  */

#घोषणा SO_TYPE		0x1008	/* Compatible name क्रम SO_STYLE.  */
#घोषणा SO_STYLE	SO_TYPE /* Synonym */
#घोषणा SO_ERROR	0x1007	/* get error status and clear */
#घोषणा SO_SNDBUF	0x1001	/* Send buffer size. */
#घोषणा SO_RCVBUF	0x1002	/* Receive buffer. */
#घोषणा SO_SNDLOWAT	0x1003	/* send low-water mark */
#घोषणा SO_RCVLOWAT	0x1004	/* receive low-water mark */
#घोषणा SO_SNDTIMEO_OLD	0x1005	/* send समयout */
#घोषणा SO_RCVTIMEO_OLD	0x1006	/* receive समयout */
#घोषणा SO_ACCEPTCONN	0x1009
#घोषणा SO_PROTOCOL	0x1028	/* protocol type */
#घोषणा SO_DOMAIN	0x1029	/* करोमुख्य/socket family */

/* linux-specअगरic, might as well be the same as on i386 */
#घोषणा SO_NO_CHECK	11
#घोषणा SO_PRIORITY	12
#घोषणा SO_BSDCOMPAT	14

#घोषणा SO_PASSCRED	17
#घोषणा SO_PEERCRED	18

/* Security levels - as per NRL IPv6 - करोn't actually करो anything */
#घोषणा SO_SECURITY_AUTHENTICATION		22
#घोषणा SO_SECURITY_ENCRYPTION_TRANSPORT	23
#घोषणा SO_SECURITY_ENCRYPTION_NETWORK		24

#घोषणा SO_BINDTODEVICE		25

/* Socket filtering */
#घोषणा SO_ATTACH_FILTER	26
#घोषणा SO_DETACH_FILTER	27
#घोषणा SO_GET_FILTER		SO_ATTACH_FILTER

#घोषणा SO_PEERNAME		28

#घोषणा SO_PEERSEC		30
#घोषणा SO_SNDBUFFORCE		31
#घोषणा SO_RCVBUFFORCE		33
#घोषणा SO_PASSSEC		34

#घोषणा SO_MARK			36

#घोषणा SO_RXQ_OVFL		40

#घोषणा SO_WIFI_STATUS		41
#घोषणा SCM_WIFI_STATUS		SO_WIFI_STATUS
#घोषणा SO_PEEK_OFF		42

/* Inकाष्ठा lower device to use last 4-bytes of skb data as FCS */
#घोषणा SO_NOFCS		43

#घोषणा SO_LOCK_FILTER		44

#घोषणा SO_SELECT_ERR_QUEUE	45

#घोषणा SO_BUSY_POLL		46

#घोषणा SO_MAX_PACING_RATE	47

#घोषणा SO_BPF_EXTENSIONS	48

#घोषणा SO_INCOMING_CPU		49

#घोषणा SO_ATTACH_BPF		50
#घोषणा SO_DETACH_BPF		SO_DETACH_FILTER

#घोषणा SO_ATTACH_REUSEPORT_CBPF	51
#घोषणा SO_ATTACH_REUSEPORT_EBPF	52

#घोषणा SO_CNX_ADVICE		53

#घोषणा SCM_TIMESTAMPING_OPT_STATS	54

#घोषणा SO_MEMINFO		55

#घोषणा SO_INCOMING_NAPI_ID	56

#घोषणा SO_COOKIE		57

#घोषणा SCM_TIMESTAMPING_PKTINFO	58

#घोषणा SO_PEERGROUPS		59

#घोषणा SO_ZEROCOPY		60

#घोषणा SO_TXTIME		61
#घोषणा SCM_TXTIME		SO_TXTIME

#घोषणा SO_BINDTOIFINDEX	62

#घोषणा SO_TIMESTAMP_OLD        29
#घोषणा SO_TIMESTAMPNS_OLD      35
#घोषणा SO_TIMESTAMPING_OLD     37

#घोषणा SO_TIMESTAMP_NEW        63
#घोषणा SO_TIMESTAMPNS_NEW      64
#घोषणा SO_TIMESTAMPING_NEW     65

#घोषणा SO_RCVTIMEO_NEW         66
#घोषणा SO_SNDTIMEO_NEW         67

#घोषणा SO_DETACH_REUSEPORT_BPF 68

#घोषणा SO_PREFER_BUSY_POLL	69
#घोषणा SO_BUSY_POLL_BUDGET	70

#अगर !defined(__KERNEL__)

#अगर __BITS_PER_LONG == 64
#घोषणा SO_TIMESTAMP		SO_TIMESTAMP_OLD
#घोषणा SO_TIMESTAMPNS		SO_TIMESTAMPNS_OLD
#घोषणा SO_TIMESTAMPING		SO_TIMESTAMPING_OLD

#घोषणा SO_RCVTIMEO             SO_RCVTIMEO_OLD
#घोषणा SO_SNDTIMEO             SO_SNDTIMEO_OLD
#अन्यथा
#घोषणा SO_TIMESTAMP (माप(समय_प्रकार) == माप(__kernel_दीर्घ_t) ? SO_TIMESTAMP_OLD : SO_TIMESTAMP_NEW)
#घोषणा SO_TIMESTAMPNS (माप(समय_प्रकार) == माप(__kernel_दीर्घ_t) ? SO_TIMESTAMPNS_OLD : SO_TIMESTAMPNS_NEW)
#घोषणा SO_TIMESTAMPING (माप(समय_प्रकार) == माप(__kernel_दीर्घ_t) ? SO_TIMESTAMPING_OLD : SO_TIMESTAMPING_NEW)

#घोषणा SO_RCVTIMEO (माप(समय_प्रकार) == माप(__kernel_दीर्घ_t) ? SO_RCVTIMEO_OLD : SO_RCVTIMEO_NEW)
#घोषणा SO_SNDTIMEO (माप(समय_प्रकार) == माप(__kernel_दीर्घ_t) ? SO_SNDTIMEO_OLD : SO_SNDTIMEO_NEW)
#पूर्ण_अगर

#घोषणा SCM_TIMESTAMP           SO_TIMESTAMP
#घोषणा SCM_TIMESTAMPNS         SO_TIMESTAMPNS
#घोषणा SCM_TIMESTAMPING        SO_TIMESTAMPING

#पूर्ण_अगर

#पूर्ण_अगर /* _UAPI_ASM_SOCKET_H */
