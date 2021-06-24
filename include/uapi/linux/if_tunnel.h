<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_IF_TUNNEL_H_
#घोषणा _UAPI_IF_TUNNEL_H_

#समावेश <linux/types.h>
#समावेश <linux/अगर.h>
#समावेश <linux/ip.h>
#समावेश <linux/in6.h>
#समावेश <यंत्र/byteorder.h>


#घोषणा SIOCGETTUNNEL   (SIOCDEVPRIVATE + 0)
#घोषणा SIOCADDTUNNEL   (SIOCDEVPRIVATE + 1)
#घोषणा SIOCDELTUNNEL   (SIOCDEVPRIVATE + 2)
#घोषणा SIOCCHGTUNNEL   (SIOCDEVPRIVATE + 3)
#घोषणा SIOCGETPRL      (SIOCDEVPRIVATE + 4)
#घोषणा SIOCADDPRL      (SIOCDEVPRIVATE + 5)
#घोषणा SIOCDELPRL      (SIOCDEVPRIVATE + 6)
#घोषणा SIOCCHGPRL      (SIOCDEVPRIVATE + 7)
#घोषणा SIOCGET6RD      (SIOCDEVPRIVATE + 8)
#घोषणा SIOCADD6RD      (SIOCDEVPRIVATE + 9)
#घोषणा SIOCDEL6RD      (SIOCDEVPRIVATE + 10)
#घोषणा SIOCCHG6RD      (SIOCDEVPRIVATE + 11)

#घोषणा GRE_CSUM	__cpu_to_be16(0x8000)
#घोषणा GRE_ROUTING	__cpu_to_be16(0x4000)
#घोषणा GRE_KEY		__cpu_to_be16(0x2000)
#घोषणा GRE_SEQ		__cpu_to_be16(0x1000)
#घोषणा GRE_STRICT	__cpu_to_be16(0x0800)
#घोषणा GRE_REC		__cpu_to_be16(0x0700)
#घोषणा GRE_ACK		__cpu_to_be16(0x0080)
#घोषणा GRE_FLAGS	__cpu_to_be16(0x0078)
#घोषणा GRE_VERSION	__cpu_to_be16(0x0007)

#घोषणा GRE_IS_CSUM(f)		((f) & GRE_CSUM)
#घोषणा GRE_IS_ROUTING(f)	((f) & GRE_ROUTING)
#घोषणा GRE_IS_KEY(f)		((f) & GRE_KEY)
#घोषणा GRE_IS_SEQ(f)		((f) & GRE_SEQ)
#घोषणा GRE_IS_STRICT(f)	((f) & GRE_STRICT)
#घोषणा GRE_IS_REC(f)		((f) & GRE_REC)
#घोषणा GRE_IS_ACK(f)		((f) & GRE_ACK)

#घोषणा GRE_VERSION_0		__cpu_to_be16(0x0000)
#घोषणा GRE_VERSION_1		__cpu_to_be16(0x0001)
#घोषणा GRE_PROTO_PPP		__cpu_to_be16(0x880b)
#घोषणा GRE_PPTP_KEY_MASK	__cpu_to_be32(0xffff)

काष्ठा ip_tunnel_parm अणु
	अक्षर			name[IFNAMSIZ];
	पूर्णांक			link;
	__be16			i_flags;
	__be16			o_flags;
	__be32			i_key;
	__be32			o_key;
	काष्ठा iphdr		iph;
पूर्ण;

क्रमागत अणु
	IFLA_IPTUN_UNSPEC,
	IFLA_IPTUN_LINK,
	IFLA_IPTUN_LOCAL,
	IFLA_IPTUN_REMOTE,
	IFLA_IPTUN_TTL,
	IFLA_IPTUN_TOS,
	IFLA_IPTUN_ENCAP_LIMIT,
	IFLA_IPTUN_FLOWINFO,
	IFLA_IPTUN_FLAGS,
	IFLA_IPTUN_PROTO,
	IFLA_IPTUN_PMTUDISC,
	IFLA_IPTUN_6RD_PREFIX,
	IFLA_IPTUN_6RD_RELAY_PREFIX,
	IFLA_IPTUN_6RD_PREFIXLEN,
	IFLA_IPTUN_6RD_RELAY_PREFIXLEN,
	IFLA_IPTUN_ENCAP_TYPE,
	IFLA_IPTUN_ENCAP_FLAGS,
	IFLA_IPTUN_ENCAP_SPORT,
	IFLA_IPTUN_ENCAP_DPORT,
	IFLA_IPTUN_COLLECT_METADATA,
	IFLA_IPTUN_FWMARK,
	__IFLA_IPTUN_MAX,
पूर्ण;
#घोषणा IFLA_IPTUN_MAX	(__IFLA_IPTUN_MAX - 1)

क्रमागत tunnel_encap_types अणु
	TUNNEL_ENCAP_NONE,
	TUNNEL_ENCAP_FOU,
	TUNNEL_ENCAP_GUE,
	TUNNEL_ENCAP_MPLS,
पूर्ण;

#घोषणा TUNNEL_ENCAP_FLAG_CSUM		(1<<0)
#घोषणा TUNNEL_ENCAP_FLAG_CSUM6		(1<<1)
#घोषणा TUNNEL_ENCAP_FLAG_REMCSUM	(1<<2)

/* SIT-mode i_flags */
#घोषणा	SIT_ISATAP	0x0001

काष्ठा ip_tunnel_prl अणु
	__be32			addr;
	__u16			flags;
	__u16			__reserved;
	__u32			datalen;
	__u32			__reserved2;
	/* data follows */
पूर्ण;

/* PRL flags */
#घोषणा	PRL_DEFAULT		0x0001

काष्ठा ip_tunnel_6rd अणु
	काष्ठा in6_addr		prefix;
	__be32			relay_prefix;
	__u16			prefixlen;
	__u16			relay_prefixlen;
पूर्ण;

क्रमागत अणु
	IFLA_GRE_UNSPEC,
	IFLA_GRE_LINK,
	IFLA_GRE_IFLAGS,
	IFLA_GRE_OFLAGS,
	IFLA_GRE_IKEY,
	IFLA_GRE_OKEY,
	IFLA_GRE_LOCAL,
	IFLA_GRE_REMOTE,
	IFLA_GRE_TTL,
	IFLA_GRE_TOS,
	IFLA_GRE_PMTUDISC,
	IFLA_GRE_ENCAP_LIMIT,
	IFLA_GRE_FLOWINFO,
	IFLA_GRE_FLAGS,
	IFLA_GRE_ENCAP_TYPE,
	IFLA_GRE_ENCAP_FLAGS,
	IFLA_GRE_ENCAP_SPORT,
	IFLA_GRE_ENCAP_DPORT,
	IFLA_GRE_COLLECT_METADATA,
	IFLA_GRE_IGNORE_DF,
	IFLA_GRE_FWMARK,
	IFLA_GRE_ERSPAN_INDEX,
	IFLA_GRE_ERSPAN_VER,
	IFLA_GRE_ERSPAN_सूची,
	IFLA_GRE_ERSPAN_HWID,
	__IFLA_GRE_MAX,
पूर्ण;

#घोषणा IFLA_GRE_MAX	(__IFLA_GRE_MAX - 1)

/* VTI-mode i_flags */
#घोषणा VTI_ISVTI ((__क्रमce __be16)0x0001)

क्रमागत अणु
	IFLA_VTI_UNSPEC,
	IFLA_VTI_LINK,
	IFLA_VTI_IKEY,
	IFLA_VTI_OKEY,
	IFLA_VTI_LOCAL,
	IFLA_VTI_REMOTE,
	IFLA_VTI_FWMARK,
	__IFLA_VTI_MAX,
पूर्ण;

#घोषणा IFLA_VTI_MAX	(__IFLA_VTI_MAX - 1)

#घोषणा TUNNEL_CSUM		__cpu_to_be16(0x01)
#घोषणा TUNNEL_ROUTING		__cpu_to_be16(0x02)
#घोषणा TUNNEL_KEY		__cpu_to_be16(0x04)
#घोषणा TUNNEL_SEQ		__cpu_to_be16(0x08)
#घोषणा TUNNEL_STRICT		__cpu_to_be16(0x10)
#घोषणा TUNNEL_REC		__cpu_to_be16(0x20)
#घोषणा TUNNEL_VERSION		__cpu_to_be16(0x40)
#घोषणा TUNNEL_NO_KEY		__cpu_to_be16(0x80)
#घोषणा TUNNEL_DONT_FRAGMENT    __cpu_to_be16(0x0100)
#घोषणा TUNNEL_OAM		__cpu_to_be16(0x0200)
#घोषणा TUNNEL_CRIT_OPT		__cpu_to_be16(0x0400)
#घोषणा TUNNEL_GENEVE_OPT	__cpu_to_be16(0x0800)
#घोषणा TUNNEL_VXLAN_OPT	__cpu_to_be16(0x1000)
#घोषणा TUNNEL_NOCACHE		__cpu_to_be16(0x2000)
#घोषणा TUNNEL_ERSPAN_OPT	__cpu_to_be16(0x4000)

#घोषणा TUNNEL_OPTIONS_PRESENT \
		(TUNNEL_GENEVE_OPT | TUNNEL_VXLAN_OPT | TUNNEL_ERSPAN_OPT)

#पूर्ण_अगर /* _UAPI_IF_TUNNEL_H_ */
