<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_NF_CONNTRACK_TCP_H
#घोषणा _UAPI_NF_CONNTRACK_TCP_H
/* TCP tracking. */

#समावेश <linux/types.h>

/* This is exposed to userspace (ctnetlink) */
क्रमागत tcp_conntrack अणु
	TCP_CONNTRACK_NONE,
	TCP_CONNTRACK_SYN_SENT,
	TCP_CONNTRACK_SYN_RECV,
	TCP_CONNTRACK_ESTABLISHED,
	TCP_CONNTRACK_FIN_WAIT,
	TCP_CONNTRACK_CLOSE_WAIT,
	TCP_CONNTRACK_LAST_ACK,
	TCP_CONNTRACK_TIME_WAIT,
	TCP_CONNTRACK_CLOSE,
	TCP_CONNTRACK_LISTEN,	/* obsolete */
#घोषणा TCP_CONNTRACK_SYN_SENT2	TCP_CONNTRACK_LISTEN
	TCP_CONNTRACK_MAX,
	TCP_CONNTRACK_IGNORE,
	TCP_CONNTRACK_RETRANS,
	TCP_CONNTRACK_UNACK,
	TCP_CONNTRACK_TIMEOUT_MAX
पूर्ण;

/* Winकरोw scaling is advertised by the sender */
#घोषणा IP_CT_TCP_FLAG_WINDOW_SCALE		0x01

/* SACK is permitted by the sender */
#घोषणा IP_CT_TCP_FLAG_SACK_PERM		0x02

/* This sender sent FIN first */
#घोषणा IP_CT_TCP_FLAG_CLOSE_INIT		0x04

/* Be liberal in winकरोw checking */
#घोषणा IP_CT_TCP_FLAG_BE_LIBERAL		0x08

/* Has unacknowledged data */
#घोषणा IP_CT_TCP_FLAG_DATA_UNACKNOWLEDGED	0x10

/* The field td_maxack has been set */
#घोषणा IP_CT_TCP_FLAG_MAXACK_SET		0x20

/* Marks possibility क्रम expected RFC5961 challenge ACK */
#घोषणा IP_CT_EXP_CHALLENGE_ACK 		0x40

/* Simultaneous खोलो initialized */
#घोषणा IP_CT_TCP_SIMULTANEOUS_OPEN		0x80

काष्ठा nf_ct_tcp_flags अणु
	__u8 flags;
	__u8 mask;
पूर्ण;


#पूर्ण_अगर /* _UAPI_NF_CONNTRACK_TCP_H */
