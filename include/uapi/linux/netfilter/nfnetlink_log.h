<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _NFNETLINK_LOG_H
#घोषणा _NFNETLINK_LOG_H

/* This file describes the netlink messages (i.e. 'protocol packets'),
 * and not any kind of function definitions.  It is shared between kernel and
 * userspace.  Don't put kernel specअगरic stuff in here */

#समावेश <linux/types.h>
#समावेश <linux/netfilter/nfnetlink.h>

क्रमागत nfulnl_msg_types अणु
	NFULNL_MSG_PACKET,		/* packet from kernel to userspace */
	NFULNL_MSG_CONFIG,		/* connect to a particular queue */

	NFULNL_MSG_MAX
पूर्ण;

काष्ठा nfulnl_msg_packet_hdr अणु
	__be16		hw_protocol;	/* hw protocol (network order) */
	__u8	hook;		/* netfilter hook */
	__u8	_pad;
पूर्ण;

काष्ठा nfulnl_msg_packet_hw अणु
	__be16		hw_addrlen;
	__u16	_pad;
	__u8	hw_addr[8];
पूर्ण;

काष्ठा nfulnl_msg_packet_बारtamp अणु
	__aligned_be64	sec;
	__aligned_be64	usec;
पूर्ण;

क्रमागत nfulnl_vlan_attr अणु
	NFULA_VLAN_UNSPEC,
	NFULA_VLAN_PROTO,		/* __be16 skb vlan_proto */
	NFULA_VLAN_TCI,			/* __be16 skb htons(vlan_tci) */
	__NFULA_VLAN_MAX,
पूर्ण;

#घोषणा NFULA_VLAN_MAX (__NFULA_VLAN_MAX + 1)

क्रमागत nfulnl_attr_type अणु
	NFULA_UNSPEC,
	NFULA_PACKET_HDR,
	NFULA_MARK,			/* __u32 nfmark */
	NFULA_TIMESTAMP,		/* nfulnl_msg_packet_बारtamp */
	NFULA_IFINDEX_INDEV,		/* __u32 अगरindex */
	NFULA_IFINDEX_OUTDEV,		/* __u32 अगरindex */
	NFULA_IFINDEX_PHYSINDEV,	/* __u32 अगरindex */
	NFULA_IFINDEX_PHYSOUTDEV,	/* __u32 अगरindex */
	NFULA_HWADDR,			/* nfulnl_msg_packet_hw */
	NFULA_PAYLOAD,			/* opaque data payload */
	NFULA_PREFIX,			/* string prefix */
	NFULA_UID,			/* user id of socket */
	NFULA_SEQ,			/* instance-local sequence number */
	NFULA_SEQ_GLOBAL,		/* global sequence number */
	NFULA_GID,			/* group id of socket */
	NFULA_HWTYPE,			/* hardware type */
	NFULA_HWHEADER,			/* hardware header */
	NFULA_HWLEN,			/* hardware header length */
	NFULA_CT,                       /* nf_conntrack_netlink.h */
	NFULA_CT_INFO,                  /* क्रमागत ip_conntrack_info */
	NFULA_VLAN,			/* nested attribute: packet vlan info */
	NFULA_L2HDR,			/* full L2 header */

	__NFULA_MAX
पूर्ण;
#घोषणा NFULA_MAX (__NFULA_MAX - 1)

क्रमागत nfulnl_msg_config_cmds अणु
	NFULNL_CFG_CMD_NONE,
	NFULNL_CFG_CMD_BIND,
	NFULNL_CFG_CMD_UNBIND,
	NFULNL_CFG_CMD_PF_BIND,
	NFULNL_CFG_CMD_PF_UNBIND,
पूर्ण;

काष्ठा nfulnl_msg_config_cmd अणु
	__u8	command;	/* nfulnl_msg_config_cmds */
पूर्ण __attribute__ ((packed));

काष्ठा nfulnl_msg_config_mode अणु
	__be32		copy_range;
	__u8	copy_mode;
	__u8	_pad;
पूर्ण __attribute__ ((packed));

क्रमागत nfulnl_attr_config अणु
	NFULA_CFG_UNSPEC,
	NFULA_CFG_CMD,			/* nfulnl_msg_config_cmd */
	NFULA_CFG_MODE,			/* nfulnl_msg_config_mode */
	NFULA_CFG_NLबफ_मान,		/* __u32 buffer size */
	NFULA_CFG_TIMEOUT,		/* __u32 in 1/100 s */
	NFULA_CFG_QTHRESH,		/* __u32 */
	NFULA_CFG_FLAGS,		/* __u16 */
	__NFULA_CFG_MAX
पूर्ण;
#घोषणा NFULA_CFG_MAX (__NFULA_CFG_MAX -1)

#घोषणा NFULNL_COPY_NONE	0x00
#घोषणा NFULNL_COPY_META	0x01
#घोषणा NFULNL_COPY_PACKET	0x02
/* 0xff is reserved, करोn't use it क्रम new copy modes. */

#घोषणा NFULNL_CFG_F_SEQ	0x0001
#घोषणा NFULNL_CFG_F_SEQ_GLOBAL	0x0002
#घोषणा NFULNL_CFG_F_CONNTRACK	0x0004

#पूर्ण_अगर /* _NFNETLINK_LOG_H */
