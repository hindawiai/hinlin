<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * DPAA2 Ethernet Switch declarations
 *
 * Copyright 2014-2016 Freescale Semiconductor Inc.
 * Copyright 2017-2021 NXP
 *
 */

#अगर_अघोषित __ETHSW_H
#घोषणा __ETHSW_H

#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <uapi/linux/अगर_bridge.h>
#समावेश <net/चयनdev.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/fsl/mc.h>
#समावेश <net/pkt_cls.h>
#समावेश <soc/fsl/dpaa2-पन.स>

#समावेश "dpsw.h"

/* Number of IRQs supported */
#घोषणा DPSW_IRQ_NUM	2

/* Port is member of VLAN */
#घोषणा ETHSW_VLAN_MEMBER	1
/* VLAN to be treated as untagged on egress */
#घोषणा ETHSW_VLAN_UNTAGGED	2
/* Untagged frames will be asचिन्हित to this VLAN */
#घोषणा ETHSW_VLAN_PVID		4
/* VLAN configured on the चयन */
#घोषणा ETHSW_VLAN_GLOBAL	8

/* Maximum Frame Length supported by HW (currently 10k) */
#घोषणा DPAA2_MFL		(10 * 1024)
#घोषणा ETHSW_MAX_FRAME_LENGTH	(DPAA2_MFL - VLAN_ETH_HLEN - ETH_FCS_LEN)
#घोषणा ETHSW_L2_MAX_FRM(mtu)	((mtu) + VLAN_ETH_HLEN + ETH_FCS_LEN)

#घोषणा ETHSW_FEATURE_MAC_ADDR	BIT(0)

/* Number of receive queues (one RX and one TX_CONF) */
#घोषणा DPAA2_SWITCH_RX_NUM_FQS	2

/* Hardware requires alignment क्रम ingress/egress buffer addresses */
#घोषणा DPAA2_SWITCH_RX_BUF_RAW_SIZE	PAGE_SIZE
#घोषणा DPAA2_SWITCH_RX_BUF_TAILROOM \
	SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info))
#घोषणा DPAA2_SWITCH_RX_BUF_SIZE \
	(DPAA2_SWITCH_RX_BUF_RAW_SIZE - DPAA2_SWITCH_RX_BUF_TAILROOM)

#घोषणा DPAA2_SWITCH_STORE_SIZE 16

/* Buffer management */
#घोषणा BUFS_PER_CMD			7
#घोषणा DPAA2_ETHSW_NUM_BUFS		(1024 * BUFS_PER_CMD)
#घोषणा DPAA2_ETHSW_REFILL_THRESH	(DPAA2_ETHSW_NUM_BUFS * 5 / 6)

/* Number of बार to retry DPIO portal operations जबतक रुकोing
 * क्रम portal to finish executing current command and become
 * available. We want to aव्योम being stuck in a जबतक loop in हाल
 * hardware becomes unresponsive, but not give up too easily अगर
 * the portal really is busy क्रम valid reasons
 */
#घोषणा DPAA2_SWITCH_SWP_BUSY_RETRIES		1000

/* Hardware annotation buffer size */
#घोषणा DPAA2_SWITCH_HWA_SIZE			64
/* Software annotation buffer size */
#घोषणा DPAA2_SWITCH_SWA_SIZE			64

#घोषणा DPAA2_SWITCH_TX_BUF_ALIGN		64

#घोषणा DPAA2_SWITCH_TX_DATA_OFFSET \
	(DPAA2_SWITCH_HWA_SIZE + DPAA2_SWITCH_SWA_SIZE)

#घोषणा DPAA2_SWITCH_NEEDED_HEADROOM \
	(DPAA2_SWITCH_TX_DATA_OFFSET + DPAA2_SWITCH_TX_BUF_ALIGN)

#घोषणा DPAA2_ETHSW_PORT_MAX_ACL_ENTRIES	16
#घोषणा DPAA2_ETHSW_PORT_DEFAULT_TRAPS		1

#घोषणा DPAA2_ETHSW_PORT_ACL_CMD_BUF_SIZE	256

बाह्य स्थिर काष्ठा ethtool_ops dpaa2_चयन_port_ethtool_ops;

काष्ठा ethsw_core;

काष्ठा dpaa2_चयन_fq अणु
	काष्ठा ethsw_core *ethsw;
	क्रमागत dpsw_queue_type type;
	काष्ठा dpaa2_io_store *store;
	काष्ठा dpaa2_io_notअगरication_ctx nctx;
	काष्ठा napi_काष्ठा napi;
	u32 fqid;
पूर्ण;

काष्ठा dpaa2_चयन_fdb अणु
	काष्ठा net_device	*bridge_dev;
	u16			fdb_id;
	bool			in_use;
पूर्ण;

काष्ठा dpaa2_चयन_acl_entry अणु
	काष्ठा list_head	list;
	u16			prio;
	अचिन्हित दीर्घ		cookie;

	काष्ठा dpsw_acl_entry_cfg cfg;
	काष्ठा dpsw_acl_key	key;
पूर्ण;

काष्ठा dpaa2_चयन_acl_tbl अणु
	काष्ठा list_head	entries;
	काष्ठा ethsw_core	*ethsw;
	u64			ports;

	u16			id;
	u8			num_rules;
	bool			in_use;
पूर्ण;

अटल अंतरभूत bool
dpaa2_चयन_acl_tbl_is_full(काष्ठा dpaa2_चयन_acl_tbl *acl_tbl)
अणु
	अगर ((acl_tbl->num_rules + DPAA2_ETHSW_PORT_DEFAULT_TRAPS) >=
	    DPAA2_ETHSW_PORT_MAX_ACL_ENTRIES)
		वापस true;
	वापस false;
पूर्ण

/* Per port निजी data */
काष्ठा ethsw_port_priv अणु
	काष्ठा net_device	*netdev;
	u16			idx;
	काष्ठा ethsw_core	*ethsw_data;
	u8			link_state;
	u8			stp_state;

	u8			vlans[VLAN_VID_MASK + 1];
	u16			pvid;
	u16			tx_qdid;

	काष्ठा dpaa2_चयन_fdb	*fdb;
	bool			bcast_flood;
	bool			ucast_flood;
	bool			learn_ena;

	काष्ठा dpaa2_चयन_acl_tbl *acl_tbl;
पूर्ण;

/* Switch data */
काष्ठा ethsw_core अणु
	काष्ठा device			*dev;
	काष्ठा fsl_mc_io		*mc_io;
	u16				dpsw_handle;
	काष्ठा dpsw_attr		sw_attr;
	u16				major, minor;
	अचिन्हित दीर्घ			features;
	पूर्णांक				dev_id;
	काष्ठा ethsw_port_priv		**ports;
	काष्ठा iommu_करोमुख्य		*iommu_करोमुख्य;

	u8				vlans[VLAN_VID_MASK + 1];

	काष्ठा workqueue_काष्ठा		*workqueue;

	काष्ठा dpaa2_चयन_fq		fq[DPAA2_SWITCH_RX_NUM_FQS];
	काष्ठा fsl_mc_device		*dpbp_dev;
	पूर्णांक				buf_count;
	u16				bpid;
	पूर्णांक				napi_users;

	काष्ठा dpaa2_चयन_fdb		*fdbs;
	काष्ठा dpaa2_चयन_acl_tbl	*acls;
पूर्ण;

अटल अंतरभूत पूर्णांक dpaa2_चयन_get_index(काष्ठा ethsw_core *ethsw,
					 काष्ठा net_device *netdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ethsw->sw_attr.num_अगरs; i++)
		अगर (ethsw->ports[i]->netdev == netdev)
			वापस ethsw->ports[i]->idx;

	वापस -EINVAL;
पूर्ण

अटल अंतरभूत bool dpaa2_चयन_supports_cpu_traffic(काष्ठा ethsw_core *ethsw)
अणु
	अगर (ethsw->sw_attr.options & DPSW_OPT_CTRL_IF_DIS) अणु
		dev_err(ethsw->dev, "Control Interface is disabled, cannot probe\n");
		वापस false;
	पूर्ण

	अगर (ethsw->sw_attr.flooding_cfg != DPSW_FLOODING_PER_FDB) अणु
		dev_err(ethsw->dev, "Flooding domain is not per FDB, cannot probe\n");
		वापस false;
	पूर्ण

	अगर (ethsw->sw_attr.broadcast_cfg != DPSW_BROADCAST_PER_FDB) अणु
		dev_err(ethsw->dev, "Broadcast domain is not per FDB, cannot probe\n");
		वापस false;
	पूर्ण

	अगर (ethsw->sw_attr.max_fdbs < ethsw->sw_attr.num_अगरs) अणु
		dev_err(ethsw->dev, "The number of FDBs is lower than the number of ports, cannot probe\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

bool dpaa2_चयन_port_dev_check(स्थिर काष्ठा net_device *netdev);

पूर्णांक dpaa2_चयन_port_vlans_add(काष्ठा net_device *netdev,
				स्थिर काष्ठा चयनdev_obj_port_vlan *vlan);

पूर्णांक dpaa2_चयन_port_vlans_del(काष्ठा net_device *netdev,
				स्थिर काष्ठा चयनdev_obj_port_vlan *vlan);

प्रकार पूर्णांक dpaa2_चयन_fdb_cb_t(काष्ठा ethsw_port_priv *port_priv,
				  काष्ठा fdb_dump_entry *fdb_entry,
				  व्योम *data);

/* TC offload */

पूर्णांक dpaa2_चयन_cls_flower_replace(काष्ठा dpaa2_चयन_acl_tbl *acl_tbl,
				    काष्ठा flow_cls_offload *cls);

पूर्णांक dpaa2_चयन_cls_flower_destroy(काष्ठा dpaa2_चयन_acl_tbl *acl_tbl,
				    काष्ठा flow_cls_offload *cls);

पूर्णांक dpaa2_चयन_cls_matchall_replace(काष्ठा dpaa2_चयन_acl_tbl *acl_tbl,
				      काष्ठा tc_cls_matchall_offload *cls);

पूर्णांक dpaa2_चयन_cls_matchall_destroy(काष्ठा dpaa2_चयन_acl_tbl *acl_tbl,
				      काष्ठा tc_cls_matchall_offload *cls);

पूर्णांक dpaa2_चयन_acl_entry_add(काष्ठा dpaa2_चयन_acl_tbl *acl_tbl,
			       काष्ठा dpaa2_चयन_acl_entry *entry);
#पूर्ण_अगर	/* __ETHSW_H */
