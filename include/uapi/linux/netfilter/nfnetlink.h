<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_NFNETLINK_H
#घोषणा _UAPI_NFNETLINK_H
#समावेश <linux/types.h>
#समावेश <linux/netfilter/nfnetlink_compat.h>

क्रमागत nfnetlink_groups अणु
	NFNLGRP_NONE,
#घोषणा NFNLGRP_NONE			NFNLGRP_NONE
	NFNLGRP_CONNTRACK_NEW,
#घोषणा NFNLGRP_CONNTRACK_NEW		NFNLGRP_CONNTRACK_NEW
	NFNLGRP_CONNTRACK_UPDATE,
#घोषणा NFNLGRP_CONNTRACK_UPDATE	NFNLGRP_CONNTRACK_UPDATE
	NFNLGRP_CONNTRACK_DESTROY,
#घोषणा NFNLGRP_CONNTRACK_DESTROY	NFNLGRP_CONNTRACK_DESTROY
	NFNLGRP_CONNTRACK_EXP_NEW,
#घोषणा	NFNLGRP_CONNTRACK_EXP_NEW	NFNLGRP_CONNTRACK_EXP_NEW
	NFNLGRP_CONNTRACK_EXP_UPDATE,
#घोषणा NFNLGRP_CONNTRACK_EXP_UPDATE	NFNLGRP_CONNTRACK_EXP_UPDATE
	NFNLGRP_CONNTRACK_EXP_DESTROY,
#घोषणा NFNLGRP_CONNTRACK_EXP_DESTROY	NFNLGRP_CONNTRACK_EXP_DESTROY
	NFNLGRP_NFTABLES,
#घोषणा NFNLGRP_NFTABLES                NFNLGRP_NFTABLES
	NFNLGRP_ACCT_QUOTA,
#घोषणा NFNLGRP_ACCT_QUOTA		NFNLGRP_ACCT_QUOTA
	NFNLGRP_NFTRACE,
#घोषणा NFNLGRP_NFTRACE			NFNLGRP_NFTRACE
	__NFNLGRP_MAX,
पूर्ण;
#घोषणा NFNLGRP_MAX	(__NFNLGRP_MAX - 1)

/* General क्रमm of address family dependent message.
 */
काष्ठा nfgenmsg अणु
	__u8  nfgen_family;		/* AF_xxx */
	__u8  version;		/* nfnetlink version */
	__be16    res_id;		/* resource id */
पूर्ण;

#घोषणा NFNETLINK_V0	0

/* netfilter netlink message types are split in two pieces:
 * 8 bit subप्रणाली, 8bit operation.
 */

#घोषणा NFNL_SUBSYS_ID(x)	((x & 0xff00) >> 8)
#घोषणा NFNL_MSG_TYPE(x)	(x & 0x00ff)

/* No क्रमागत here, otherwise __stringअगरy() trick of MODULE_ALIAS_NFNL_SUBSYS()
 * won't work anymore */
#घोषणा NFNL_SUBSYS_NONE 		0
#घोषणा NFNL_SUBSYS_CTNETLINK		1
#घोषणा NFNL_SUBSYS_CTNETLINK_EXP	2
#घोषणा NFNL_SUBSYS_QUEUE		3
#घोषणा NFNL_SUBSYS_ULOG		4
#घोषणा NFNL_SUBSYS_OSF			5
#घोषणा NFNL_SUBSYS_IPSET		6
#घोषणा NFNL_SUBSYS_ACCT		7
#घोषणा NFNL_SUBSYS_CTNETLINK_TIMEOUT	8
#घोषणा NFNL_SUBSYS_CTHELPER		9
#घोषणा NFNL_SUBSYS_NFTABLES		10
#घोषणा NFNL_SUBSYS_NFT_COMPAT		11
#घोषणा NFNL_SUBSYS_COUNT		12

/* Reserved control nfnetlink messages */
#घोषणा NFNL_MSG_BATCH_BEGIN		NLMSG_MIN_TYPE
#घोषणा NFNL_MSG_BATCH_END		NLMSG_MIN_TYPE+1

/**
 * क्रमागत nfnl_batch_attributes - nfnetlink batch netlink attributes
 *
 * @NFNL_BATCH_GENID: generation ID क्रम this changeset (NLA_U32)
 */
क्रमागत nfnl_batch_attributes अणु
        NFNL_BATCH_UNSPEC,
        NFNL_BATCH_GENID,
        __NFNL_BATCH_MAX
पूर्ण;
#घोषणा NFNL_BATCH_MAX			(__NFNL_BATCH_MAX - 1)

#पूर्ण_अगर /* _UAPI_NFNETLINK_H */
