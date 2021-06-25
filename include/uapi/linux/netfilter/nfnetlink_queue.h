<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _NFNETLINK_QUEUE_H
#घोषणा _NFNETLINK_QUEUE_H

#समावेश <linux/types.h>
#समावेश <linux/netfilter/nfnetlink.h>

क्रमागत nfqnl_msg_types अणु
	NFQNL_MSG_PACKET,		/* packet from kernel to userspace */
	NFQNL_MSG_VERDICT,		/* verdict from userspace to kernel */
	NFQNL_MSG_CONFIG,		/* connect to a particular queue */
	NFQNL_MSG_VERDICT_BATCH,	/* batchv from userspace to kernel */

	NFQNL_MSG_MAX
पूर्ण;

काष्ठा nfqnl_msg_packet_hdr अणु
	__be32		packet_id;	/* unique ID of packet in queue */
	__be16		hw_protocol;	/* hw protocol (network order) */
	__u8	hook;		/* netfilter hook */
पूर्ण __attribute__ ((packed));

काष्ठा nfqnl_msg_packet_hw अणु
	__be16		hw_addrlen;
	__u16	_pad;
	__u8	hw_addr[8];
पूर्ण;

काष्ठा nfqnl_msg_packet_बारtamp अणु
	__aligned_be64	sec;
	__aligned_be64	usec;
पूर्ण;

क्रमागत nfqnl_vlan_attr अणु
	NFQA_VLAN_UNSPEC,
	NFQA_VLAN_PROTO,		/* __be16 skb vlan_proto */
	NFQA_VLAN_TCI,			/* __be16 skb htons(vlan_tci) */
	__NFQA_VLAN_MAX,
पूर्ण;
#घोषणा NFQA_VLAN_MAX (__NFQA_VLAN_MAX - 1)

क्रमागत nfqnl_attr_type अणु
	NFQA_UNSPEC,
	NFQA_PACKET_HDR,
	NFQA_VERDICT_HDR,		/* nfqnl_msg_verdict_hrd */
	NFQA_MARK,			/* __u32 nfmark */
	NFQA_TIMESTAMP,			/* nfqnl_msg_packet_बारtamp */
	NFQA_IFINDEX_INDEV,		/* __u32 अगरindex */
	NFQA_IFINDEX_OUTDEV,		/* __u32 अगरindex */
	NFQA_IFINDEX_PHYSINDEV,		/* __u32 अगरindex */
	NFQA_IFINDEX_PHYSOUTDEV,	/* __u32 अगरindex */
	NFQA_HWADDR,			/* nfqnl_msg_packet_hw */
	NFQA_PAYLOAD,			/* opaque data payload */
	NFQA_CT,			/* nf_conntrack_netlink.h */
	NFQA_CT_INFO,			/* क्रमागत ip_conntrack_info */
	NFQA_CAP_LEN,			/* __u32 length of captured packet */
	NFQA_SKB_INFO,			/* __u32 skb meta inक्रमmation */
	NFQA_EXP,			/* nf_conntrack_netlink.h */
	NFQA_UID,			/* __u32 sk uid */
	NFQA_GID,			/* __u32 sk gid */
	NFQA_SECCTX,			/* security context string */
	NFQA_VLAN,			/* nested attribute: packet vlan info */
	NFQA_L2HDR,			/* full L2 header */

	__NFQA_MAX
पूर्ण;
#घोषणा NFQA_MAX (__NFQA_MAX - 1)

काष्ठा nfqnl_msg_verdict_hdr अणु
	__be32 verdict;
	__be32 id;
पूर्ण;


क्रमागत nfqnl_msg_config_cmds अणु
	NFQNL_CFG_CMD_NONE,
	NFQNL_CFG_CMD_BIND,
	NFQNL_CFG_CMD_UNBIND,
	NFQNL_CFG_CMD_PF_BIND,
	NFQNL_CFG_CMD_PF_UNBIND,
पूर्ण;

काष्ठा nfqnl_msg_config_cmd अणु
	__u8	command;	/* nfqnl_msg_config_cmds */
	__u8	_pad;
	__be16		pf;		/* AF_xxx क्रम PF_[UN]BIND */
पूर्ण;

क्रमागत nfqnl_config_mode अणु
	NFQNL_COPY_NONE,
	NFQNL_COPY_META,
	NFQNL_COPY_PACKET,
पूर्ण;

काष्ठा nfqnl_msg_config_params अणु
	__be32		copy_range;
	__u8	copy_mode;	/* क्रमागत nfqnl_config_mode */
पूर्ण __attribute__ ((packed));


क्रमागत nfqnl_attr_config अणु
	NFQA_CFG_UNSPEC,
	NFQA_CFG_CMD,			/* nfqnl_msg_config_cmd */
	NFQA_CFG_PARAMS,		/* nfqnl_msg_config_params */
	NFQA_CFG_QUEUE_MAXLEN,		/* __u32 */
	NFQA_CFG_MASK,			/* identअगरy which flags to change */
	NFQA_CFG_FLAGS,			/* value of these flags (__u32) */
	__NFQA_CFG_MAX
पूर्ण;
#घोषणा NFQA_CFG_MAX (__NFQA_CFG_MAX-1)

/* Flags क्रम NFQA_CFG_FLAGS */
#घोषणा NFQA_CFG_F_FAIL_OPEN			(1 << 0)
#घोषणा NFQA_CFG_F_CONNTRACK			(1 << 1)
#घोषणा NFQA_CFG_F_GSO				(1 << 2)
#घोषणा NFQA_CFG_F_UID_GID			(1 << 3)
#घोषणा NFQA_CFG_F_SECCTX			(1 << 4)
#घोषणा NFQA_CFG_F_MAX				(1 << 5)

/* flags क्रम NFQA_SKB_INFO */
/* packet appears to have wrong checksums, but they are ok */
#घोषणा NFQA_SKB_CSUMNOTREADY (1 << 0)
/* packet is GSO (i.e., exceeds device mtu) */
#घोषणा NFQA_SKB_GSO (1 << 1)
/* csum not validated (incoming device करोesn't support hw checksum, etc.) */
#घोषणा NFQA_SKB_CSUM_NOTVERIFIED (1 << 2)

#पूर्ण_अगर /* _NFNETLINK_QUEUE_H */
