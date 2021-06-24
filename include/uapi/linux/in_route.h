<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _LINUX_IN_ROUTE_H
#घोषणा _LINUX_IN_ROUTE_H

/* IPv4 routing cache flags */

#घोषणा RTCF_DEAD	RTNH_F_DEAD
#घोषणा RTCF_ONLINK	RTNH_F_ONLINK

/* Obsolete flag. About to be deleted */
#घोषणा RTCF_NOPMTUDISC RTM_F_NOPMTUDISC

#घोषणा RTCF_NOTIFY	0x00010000
#घोषणा RTCF_सूचीECTDST	0x00020000 /* unused */
#घोषणा RTCF_REसूचीECTED	0x00040000
#घोषणा RTCF_TPROXY	0x00080000 /* unused */

#घोषणा RTCF_FAST	0x00200000 /* unused */
#घोषणा RTCF_MASQ	0x00400000 /* unused */
#घोषणा RTCF_SNAT	0x00800000 /* unused */
#घोषणा RTCF_DOREसूचीECT 0x01000000
#घोषणा RTCF_सूचीECTSRC	0x04000000
#घोषणा RTCF_DNAT	0x08000000
#घोषणा RTCF_BROADCAST	0x10000000
#घोषणा RTCF_MULTICAST	0x20000000
#घोषणा RTCF_REJECT	0x40000000 /* unused */
#घोषणा RTCF_LOCAL	0x80000000

#घोषणा RTCF_NAT	(RTCF_DNAT|RTCF_SNAT)

#घोषणा RT_TOS(tos)	((tos)&IPTOS_TOS_MASK)

#पूर्ण_अगर /* _LINUX_IN_ROUTE_H */
