<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ASM_SOCKET_H
#घोषणा _ASM_SOCKET_H

#समावेश <linux/posix_types.h>
#समावेश <यंत्र/sockios.h>

/* For setsockopt(2) */
#घोषणा SOL_SOCKET	0xffff

#घोषणा SO_DEBUG	0x0001
#घोषणा SO_PASSCRED	0x0002
#घोषणा SO_REUSEADDR	0x0004
#घोषणा SO_KEEPALIVE	0x0008
#घोषणा SO_DONTROUTE	0x0010
#घोषणा SO_BROADCAST	0x0020
#घोषणा SO_PEERCRED	0x0040
#घोषणा SO_LINGER	0x0080
#घोषणा SO_OOBINLINE	0x0100
#घोषणा SO_REUSEPORT	0x0200
#घोषणा SO_BSDCOMPAT    0x0400
#घोषणा SO_RCVLOWAT     0x0800
#घोषणा SO_SNDLOWAT     0x1000
#घोषणा SO_RCVTIMEO_OLD     0x2000
#घोषणा SO_SNDTIMEO_OLD     0x4000
#घोषणा SO_ACCEPTCONN	0x8000

#घोषणा SO_SNDBUF	0x1001
#घोषणा SO_RCVBUF	0x1002
#घोषणा SO_SNDBUFFORCE	0x100a
#घोषणा SO_RCVBUFFORCE	0x100b
#घोषणा SO_ERROR	0x1007
#घोषणा SO_TYPE		0x1008
#घोषणा SO_PROTOCOL	0x1028
#घोषणा SO_DOMAIN	0x1029

/* Linux specअगरic, keep the same. */
#घोषणा SO_NO_CHECK	0x000b
#घोषणा SO_PRIORITY	0x000c

#घोषणा SO_BINDTODEVICE 0x000d

#घोषणा SO_ATTACH_FILTER	0x001a
#घोषणा SO_DETACH_FILTER        0x001b
#घोषणा SO_GET_FILTER		SO_ATTACH_FILTER

#घोषणा SO_PEERNAME		0x001c

#घोषणा SO_PEERSEC		0x001e
#घोषणा SO_PASSSEC		0x001f

#घोषणा SO_MARK			0x0022

#घोषणा SO_RXQ_OVFL             0x0024

#घोषणा SO_WIFI_STATUS		0x0025
#घोषणा SCM_WIFI_STATUS		SO_WIFI_STATUS
#घोषणा SO_PEEK_OFF		0x0026

/* Inकाष्ठा lower device to use last 4-bytes of skb data as FCS */
#घोषणा SO_NOFCS		0x0027

#घोषणा SO_LOCK_FILTER		0x0028

#घोषणा SO_SELECT_ERR_QUEUE	0x0029

#घोषणा SO_BUSY_POLL		0x0030

#घोषणा SO_MAX_PACING_RATE	0x0031

#घोषणा SO_BPF_EXTENSIONS	0x0032

#घोषणा SO_INCOMING_CPU		0x0033

#घोषणा SO_ATTACH_BPF		0x0034
#घोषणा SO_DETACH_BPF		SO_DETACH_FILTER

#घोषणा SO_ATTACH_REUSEPORT_CBPF	0x0035
#घोषणा SO_ATTACH_REUSEPORT_EBPF	0x0036

#घोषणा SO_CNX_ADVICE		0x0037

#घोषणा SCM_TIMESTAMPING_OPT_STATS	0x0038

#घोषणा SO_MEMINFO		0x0039

#घोषणा SO_INCOMING_NAPI_ID	0x003a

#घोषणा SO_COOKIE		0x003b

#घोषणा SCM_TIMESTAMPING_PKTINFO	0x003c

#घोषणा SO_PEERGROUPS		0x003d

#घोषणा SO_ZEROCOPY		0x003e

#घोषणा SO_TXTIME		0x003f
#घोषणा SCM_TXTIME		SO_TXTIME

#घोषणा SO_BINDTOIFINDEX	0x0041

/* Security levels - as per NRL IPv6 - करोn't actually करो anything */
#घोषणा SO_SECURITY_AUTHENTICATION		0x5001
#घोषणा SO_SECURITY_ENCRYPTION_TRANSPORT	0x5002
#घोषणा SO_SECURITY_ENCRYPTION_NETWORK		0x5004

#घोषणा SO_TIMESTAMP_OLD         0x001d
#घोषणा SO_TIMESTAMPNS_OLD       0x0021
#घोषणा SO_TIMESTAMPING_OLD      0x0023

#घोषणा SO_TIMESTAMP_NEW         0x0046
#घोषणा SO_TIMESTAMPNS_NEW       0x0042
#घोषणा SO_TIMESTAMPING_NEW      0x0043

#घोषणा SO_RCVTIMEO_NEW          0x0044
#घोषणा SO_SNDTIMEO_NEW          0x0045

#घोषणा SO_DETACH_REUSEPORT_BPF  0x0047

#घोषणा SO_PREFER_BUSY_POLL	 0x0048
#घोषणा SO_BUSY_POLL_BUDGET	 0x0049

#अगर !defined(__KERNEL__)


#अगर __BITS_PER_LONG == 64
#घोषणा SO_TIMESTAMP		SO_TIMESTAMP_OLD
#घोषणा SO_TIMESTAMPNS		SO_TIMESTAMPNS_OLD
#घोषणा SO_TIMESTAMPING		SO_TIMESTAMPING_OLD

#घोषणा SO_RCVTIMEO		SO_RCVTIMEO_OLD
#घोषणा SO_SNDTIMEO		SO_SNDTIMEO_OLD
#अन्यथा
#घोषणा SO_TIMESTAMP (माप(समय_प्रकार) == माप(__kernel_दीर्घ_t) ? SO_TIMESTAMP_OLD : SO_TIMESTAMP_NEW)
#घोषणा SO_TIMESTAMPNS (माप(समय_प्रकार) == माप(__kernel_दीर्घ_t) ? SO_TIMESTAMPNS_OLD : SO_TIMESTAMPNS_NEW)
#घोषणा SO_TIMESTAMPING (माप(समय_प्रकार) == माप(__kernel_दीर्घ_t) ? SO_TIMESTAMPING_OLD : SO_TIMESTAMPING_NEW)

#घोषणा SO_RCVTIMEO (माप(समय_प्रकार) == माप(__kernel_दीर्घ_t) ? SO_RCVTIMEO_OLD : SO_RCVTIMEO_NEW)
#घोषणा SO_SNDTIMEO (माप(समय_प्रकार) == माप(__kernel_दीर्घ_t) ? SO_SNDTIMEO_OLD : SO_SNDTIMEO_NEW)
#पूर्ण_अगर

#घोषणा SCM_TIMESTAMP          SO_TIMESTAMP
#घोषणा SCM_TIMESTAMPNS        SO_TIMESTAMPNS
#घोषणा SCM_TIMESTAMPING       SO_TIMESTAMPING

#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_SOCKET_H */
