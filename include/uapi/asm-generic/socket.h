<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __ASM_GENERIC_SOCKET_H
#घोषणा __ASM_GENERIC_SOCKET_H

#समावेश <linux/posix_types.h>
#समावेश <यंत्र/sockios.h>

/* For setsockopt(2) */
#घोषणा SOL_SOCKET	1

#घोषणा SO_DEBUG	1
#घोषणा SO_REUSEADDR	2
#घोषणा SO_TYPE		3
#घोषणा SO_ERROR	4
#घोषणा SO_DONTROUTE	5
#घोषणा SO_BROADCAST	6
#घोषणा SO_SNDBUF	7
#घोषणा SO_RCVBUF	8
#घोषणा SO_SNDBUFFORCE	32
#घोषणा SO_RCVBUFFORCE	33
#घोषणा SO_KEEPALIVE	9
#घोषणा SO_OOBINLINE	10
#घोषणा SO_NO_CHECK	11
#घोषणा SO_PRIORITY	12
#घोषणा SO_LINGER	13
#घोषणा SO_BSDCOMPAT	14
#घोषणा SO_REUSEPORT	15
#अगर_अघोषित SO_PASSCRED /* घातerpc only dअगरfers in these */
#घोषणा SO_PASSCRED	16
#घोषणा SO_PEERCRED	17
#घोषणा SO_RCVLOWAT	18
#घोषणा SO_SNDLOWAT	19
#घोषणा SO_RCVTIMEO_OLD	20
#घोषणा SO_SNDTIMEO_OLD	21
#पूर्ण_अगर

/* Security levels - as per NRL IPv6 - करोn't actually करो anything */
#घोषणा SO_SECURITY_AUTHENTICATION		22
#घोषणा SO_SECURITY_ENCRYPTION_TRANSPORT	23
#घोषणा SO_SECURITY_ENCRYPTION_NETWORK		24

#घोषणा SO_BINDTODEVICE	25

/* Socket filtering */
#घोषणा SO_ATTACH_FILTER	26
#घोषणा SO_DETACH_FILTER	27
#घोषणा SO_GET_FILTER		SO_ATTACH_FILTER

#घोषणा SO_PEERNAME		28

#घोषणा SO_ACCEPTCONN		30

#घोषणा SO_PEERSEC		31
#घोषणा SO_PASSSEC		34

#घोषणा SO_MARK			36

#घोषणा SO_PROTOCOL		38
#घोषणा SO_DOMAIN		39

#घोषणा SO_RXQ_OVFL             40

#घोषणा SO_WIFI_STATUS		41
#घोषणा SCM_WIFI_STATUS	SO_WIFI_STATUS
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

#अगर __BITS_PER_LONG == 64 || (defined(__x86_64__) && defined(__ILP32__))
/* on 64-bit and x32, aव्योम the ?: चालक */
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

#घोषणा SCM_TIMESTAMP           SO_TIMESTAMP
#घोषणा SCM_TIMESTAMPNS         SO_TIMESTAMPNS
#घोषणा SCM_TIMESTAMPING        SO_TIMESTAMPING

#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_GENERIC_SOCKET_H */
