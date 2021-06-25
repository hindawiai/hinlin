<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright(c) 2017 - 2020 Intel Corporation.
 */

#अगर_अघोषित _OPA_VNIC_H
#घोषणा _OPA_VNIC_H

/*
 * This file contains Intel Omni-Path (OPA) Virtual Network Interface
 * Controller (VNIC) specअगरic declarations.
 */

#समावेश <rdma/ib_verbs.h>

/* 16 header bytes + 2 reserved bytes */
#घोषणा OPA_VNIC_L2_HDR_LEN   (16 + 2)

#घोषणा OPA_VNIC_L4_HDR_LEN   2

#घोषणा OPA_VNIC_HDR_LEN      (OPA_VNIC_L2_HDR_LEN + \
			       OPA_VNIC_L4_HDR_LEN)

#घोषणा OPA_VNIC_L4_ETHR  0x78

#घोषणा OPA_VNIC_ICRC_LEN   4
#घोषणा OPA_VNIC_TAIL_LEN   1
#घोषणा OPA_VNIC_ICRC_TAIL_LEN  (OPA_VNIC_ICRC_LEN + OPA_VNIC_TAIL_LEN)

#घोषणा OPA_VNIC_SKB_MDATA_LEN         4
#घोषणा OPA_VNIC_SKB_MDATA_ENCAP_ERR   0x1

/* opa vnic rdma netdev's निजी data काष्ठाure */
काष्ठा opa_vnic_rdma_netdev अणु
	काष्ठा rdma_netdev rn;  /* keep this first */
	/* followed by device निजी data */
	अक्षर *dev_priv[];
पूर्ण;

अटल अंतरभूत व्योम *opa_vnic_priv(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा rdma_netdev *rn = netdev_priv(dev);

	वापस rn->clnt_priv;
पूर्ण

अटल अंतरभूत व्योम *opa_vnic_dev_priv(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा opa_vnic_rdma_netdev *oparn = netdev_priv(dev);

	वापस oparn->dev_priv;
पूर्ण

/* opa_vnic skb meta data काष्ठाrue */
काष्ठा opa_vnic_skb_mdata अणु
	u8 vl;
	u8 entropy;
	u8 flags;
	u8 rsvd;
पूर्ण __packed;

/* OPA VNIC group statistics */
काष्ठा opa_vnic_grp_stats अणु
	u64 unicast;
	u64 mcastbcast;
	u64 untagged;
	u64 vlan;
	u64 s_64;
	u64 s_65_127;
	u64 s_128_255;
	u64 s_256_511;
	u64 s_512_1023;
	u64 s_1024_1518;
	u64 s_1519_max;
पूर्ण;

काष्ठा opa_vnic_stats अणु
	/* standard netdev statistics */
	काष्ठा rtnl_link_stats64 netstats;

	/* OPA VNIC statistics */
	काष्ठा opa_vnic_grp_stats tx_grp;
	काष्ठा opa_vnic_grp_stats rx_grp;
	u64 tx_dlid_zero;
	u64 tx_drop_state;
	u64 rx_drop_state;
	u64 rx_runt;
	u64 rx_oversize;
पूर्ण;

अटल अंतरभूत bool rdma_cap_opa_vnic(काष्ठा ib_device *device)
अणु
	वापस !!(device->attrs.device_cap_flags &
		  IB_DEVICE_RDMA_NETDEV_OPA);
पूर्ण

#पूर्ण_अगर /* _OPA_VNIC_H */
