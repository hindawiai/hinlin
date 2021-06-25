<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _IP6_TUNNEL_H
#घोषणा _IP6_TUNNEL_H

#समावेश <linux/types.h>
#समावेश <linux/अगर.h>		/* For IFNAMSIZ. */
#समावेश <linux/in6.h>		/* For काष्ठा in6_addr. */

#घोषणा IPV6_TLV_TNL_ENCAP_LIMIT 4
#घोषणा IPV6_DEFAULT_TNL_ENCAP_LIMIT 4

/* करोn't add encapsulation limit if one isn't present in inner packet */
#घोषणा IP6_TNL_F_IGN_ENCAP_LIMIT 0x1
/* copy the traffic class field from the inner packet */
#घोषणा IP6_TNL_F_USE_ORIG_TCLASS 0x2
/* copy the flowlabel from the inner packet */
#घोषणा IP6_TNL_F_USE_ORIG_FLOWLABEL 0x4
/* being used क्रम Mobile IPv6 */
#घोषणा IP6_TNL_F_MIP6_DEV 0x8
/* copy DSCP from the outer packet */
#घोषणा IP6_TNL_F_RCV_DSCP_COPY 0x10
/* copy fwmark from inner packet */
#घोषणा IP6_TNL_F_USE_ORIG_FWMARK 0x20
/* allow remote endpoपूर्णांक on the local node */
#घोषणा IP6_TNL_F_ALLOW_LOCAL_REMOTE 0x40

काष्ठा ip6_tnl_parm अणु
	अक्षर name[IFNAMSIZ];	/* name of tunnel device */
	पूर्णांक link;		/* अगरindex of underlying L2 पूर्णांकerface */
	__u8 proto;		/* tunnel protocol */
	__u8 encap_limit;	/* encapsulation limit क्रम tunnel */
	__u8 hop_limit;		/* hop limit क्रम tunnel */
	__be32 flowinfo;	/* traffic class and flowlabel क्रम tunnel */
	__u32 flags;		/* tunnel flags */
	काष्ठा in6_addr laddr;	/* local tunnel end-poपूर्णांक address */
	काष्ठा in6_addr raddr;	/* remote tunnel end-poपूर्णांक address */
पूर्ण;

काष्ठा ip6_tnl_parm2 अणु
	अक्षर name[IFNAMSIZ];	/* name of tunnel device */
	पूर्णांक link;		/* अगरindex of underlying L2 पूर्णांकerface */
	__u8 proto;		/* tunnel protocol */
	__u8 encap_limit;	/* encapsulation limit क्रम tunnel */
	__u8 hop_limit;		/* hop limit क्रम tunnel */
	__be32 flowinfo;	/* traffic class and flowlabel क्रम tunnel */
	__u32 flags;		/* tunnel flags */
	काष्ठा in6_addr laddr;	/* local tunnel end-poपूर्णांक address */
	काष्ठा in6_addr raddr;	/* remote tunnel end-poपूर्णांक address */

	__be16			i_flags;
	__be16			o_flags;
	__be32			i_key;
	__be32			o_key;
पूर्ण;

#पूर्ण_अगर
