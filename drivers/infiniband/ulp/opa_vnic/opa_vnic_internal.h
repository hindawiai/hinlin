<शैली गुरु>
#अगर_अघोषित _OPA_VNIC_INTERNAL_H
#घोषणा _OPA_VNIC_INTERNAL_H
/*
 * Copyright(c) 2017 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*
 * This file contains OPA VNIC driver पूर्णांकernal declarations
 */

#समावेश <linux/bitops.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/sizes.h>
#समावेश <rdma/opa_vnic.h>

#समावेश "opa_vnic_encap.h"

#घोषणा OPA_VNIC_VLAN_PCP(vlan_tci)  \
			(((vlan_tci) & VLAN_PRIO_MASK) >> VLAN_PRIO_SHIFT)

/* Flow to शेष port redirection table size */
#घोषणा OPA_VNIC_FLOW_TBL_SIZE    32

/* Invalid port number */
#घोषणा OPA_VNIC_INVALID_PORT     0xff

काष्ठा opa_vnic_adapter;

/*
 * काष्ठा __opa_vesw_info - OPA vnic भव चयन info
 *
 * Same as opa_vesw_info without bitwise attribute.
 */
काष्ठा __opa_vesw_info अणु
	u16  fabric_id;
	u16  vesw_id;

	u8   rsvd0[6];
	u16  def_port_mask;

	u8   rsvd1[2];
	u16  pkey;

	u8   rsvd2[4];
	u32  u_mcast_dlid;
	u32  u_ucast_dlid[OPA_VESW_MAX_NUM_DEF_PORT];

	u32  rc;

	u8   rsvd3[56];
	u16  eth_mtu;
	u8   rsvd4[2];
पूर्ण __packed;

/*
 * काष्ठा __opa_per_veswport_info - OPA vnic per port info
 *
 * Same as opa_per_veswport_info without bitwise attribute.
 */
काष्ठा __opa_per_veswport_info अणु
	u32  port_num;

	u8   eth_link_status;
	u8   rsvd0[3];

	u8   base_mac_addr[ETH_ALEN];
	u8   config_state;
	u8   oper_state;

	u16  max_mac_tbl_ent;
	u16  max_smac_ent;
	u32  mac_tbl_digest;
	u8   rsvd1[4];

	u32  encap_slid;

	u8   pcp_to_sc_uc[OPA_VNIC_MAX_NUM_PCP];
	u8   pcp_to_vl_uc[OPA_VNIC_MAX_NUM_PCP];
	u8   pcp_to_sc_mc[OPA_VNIC_MAX_NUM_PCP];
	u8   pcp_to_vl_mc[OPA_VNIC_MAX_NUM_PCP];

	u8   non_vlan_sc_uc;
	u8   non_vlan_vl_uc;
	u8   non_vlan_sc_mc;
	u8   non_vlan_vl_mc;

	u8   rsvd2[48];

	u16  uc_macs_gen_count;
	u16  mc_macs_gen_count;

	u8   rsvd3[8];
पूर्ण __packed;

/*
 * काष्ठा __opa_veswport_info - OPA vnic port info
 *
 * Same as opa_veswport_info without bitwise attribute.
 */
काष्ठा __opa_veswport_info अणु
	काष्ठा __opa_vesw_info            vesw;
	काष्ठा __opa_per_veswport_info    vport;
पूर्ण;

/*
 * काष्ठा __opa_veswport_trap - OPA vnic trap info
 *
 * Same as opa_veswport_trap without bitwise attribute.
 */
काष्ठा __opa_veswport_trap अणु
	u16	fabric_id;
	u16	veswid;
	u32	veswportnum;
	u16	opaportnum;
	u8	veswportindex;
	u8	opcode;
	u32	reserved;
पूर्ण __packed;

/**
 * काष्ठा opa_vnic_ctrl_port - OPA भव NIC control port
 * @ibdev: poपूर्णांकer to ib device
 * @ops: opa vnic control operations
 * @num_ports: number of opa ports
 */
काष्ठा opa_vnic_ctrl_port अणु
	काष्ठा ib_device           *ibdev;
	काष्ठा opa_vnic_ctrl_ops   *ops;
	u8                          num_ports;
पूर्ण;

/**
 * काष्ठा opa_vnic_adapter - OPA VNIC netdev निजी data काष्ठाure
 * @netdev: poपूर्णांकer to associated netdev
 * @ibdev: ib device
 * @cport: poपूर्णांकer to opa vnic control port
 * @rn_ops: rdma netdev's net_device_ops
 * @port_num: OPA port number
 * @vport_num: vesw port number
 * @lock: adapter lock
 * @info: भव ethernet चयन port inक्रमmation
 * @vema_mac_addr: mac address configured by vema
 * @umac_hash: unicast maclist hash
 * @mmac_hash: multicast maclist hash
 * @mactbl: hash table of MAC entries
 * @mactbl_lock: mac table lock
 * @stats_lock: statistics lock
 * @flow_tbl: flow to शेष port redirection table
 * @trap_समयout: trap समयout
 * @trap_count: no. of traps allowed within समयout period
 */
काष्ठा opa_vnic_adapter अणु
	काष्ठा net_device             *netdev;
	काष्ठा ib_device              *ibdev;
	काष्ठा opa_vnic_ctrl_port     *cport;
	स्थिर काष्ठा net_device_ops   *rn_ops;

	u8 port_num;
	u8 vport_num;

	/* Lock used around concurrent updates to netdev */
	काष्ठा mutex lock;

	काष्ठा __opa_veswport_info  info;
	u8                          vema_mac_addr[ETH_ALEN];
	u32                         umac_hash;
	u32                         mmac_hash;
	काष्ठा hlist_head  __rcu   *mactbl;

	/* Lock used to protect updates to mac table */
	काष्ठा mutex mactbl_lock;

	/* Lock used to protect access to vnic counters */
	spinlock_t stats_lock;

	u8 flow_tbl[OPA_VNIC_FLOW_TBL_SIZE];

	अचिन्हित दीर्घ trap_समयout;
	u8            trap_count;
पूर्ण;

/* Same as opa_veswport_mactable_entry, but without bitwise attribute */
काष्ठा __opa_vnic_mactable_entry अणु
	u8  mac_addr[ETH_ALEN];
	u8  mac_addr_mask[ETH_ALEN];
	u32 dlid_sd;
पूर्ण __packed;

/**
 * काष्ठा opa_vnic_mac_tbl_node - OPA VNIC mac table node
 * @hlist: hash list handle
 * @index: index of entry in the mac table
 * @entry: entry in the table
 */
काष्ठा opa_vnic_mac_tbl_node अणु
	काष्ठा hlist_node                    hlist;
	u16                                  index;
	काष्ठा __opa_vnic_mactable_entry     entry;
पूर्ण;

#घोषणा v_dbg(क्रमmat, arg...) \
	netdev_dbg(adapter->netdev, क्रमmat, ## arg)
#घोषणा v_err(क्रमmat, arg...) \
	netdev_err(adapter->netdev, क्रमmat, ## arg)
#घोषणा v_info(क्रमmat, arg...) \
	netdev_info(adapter->netdev, क्रमmat, ## arg)
#घोषणा v_warn(क्रमmat, arg...) \
	netdev_warn(adapter->netdev, क्रमmat, ## arg)

#घोषणा c_err(क्रमmat, arg...) \
	dev_err(&cport->ibdev->dev, क्रमmat, ## arg)
#घोषणा c_info(क्रमmat, arg...) \
	dev_info(&cport->ibdev->dev, क्रमmat, ## arg)
#घोषणा c_dbg(क्रमmat, arg...) \
	dev_dbg(&cport->ibdev->dev, क्रमmat, ## arg)

/* The maximum allowed entries in the mac table */
#घोषणा OPA_VNIC_MAC_TBL_MAX_ENTRIES  2048
/* Limit of smac entries in mac table */
#घोषणा OPA_VNIC_MAX_SMAC_LIMIT       256

/* The last octet of the MAC address is used as the key to the hash table */
#घोषणा OPA_VNIC_MAC_HASH_IDX         5

/* The VNIC MAC hash table is of size 2^8 */
#घोषणा OPA_VNIC_MAC_TBL_HASH_BITS    8
#घोषणा OPA_VNIC_MAC_TBL_SIZE  BIT(OPA_VNIC_MAC_TBL_HASH_BITS)

/* VNIC HASH MACROS */
#घोषणा vnic_hash_init(hashtable) __hash_init(hashtable, OPA_VNIC_MAC_TBL_SIZE)

#घोषणा vnic_hash_add(hashtable, node, key)                                   \
	hlist_add_head(node,                                                  \
		&hashtable[hash_min(key, ilog2(OPA_VNIC_MAC_TBL_SIZE))])

#घोषणा vnic_hash_क्रम_each_safe(name, bkt, पंचांगp, obj, member)                  \
	क्रम ((bkt) = 0, obj = शून्य;                                           \
		    !obj && (bkt) < OPA_VNIC_MAC_TBL_SIZE; (bkt)++)           \
		hlist_क्रम_each_entry_safe(obj, पंचांगp, &name[bkt], member)

#घोषणा vnic_hash_क्रम_each_possible(name, obj, member, key)                   \
	hlist_क्रम_each_entry(obj,                                             \
		&name[hash_min(key, ilog2(OPA_VNIC_MAC_TBL_SIZE))], member)

#घोषणा vnic_hash_क्रम_each(name, bkt, obj, member)                            \
	क्रम ((bkt) = 0, obj = शून्य;                                           \
		    !obj && (bkt) < OPA_VNIC_MAC_TBL_SIZE; (bkt)++)           \
		hlist_क्रम_each_entry(obj, &name[bkt], member)

बाह्य अक्षर opa_vnic_driver_name[];

काष्ठा opa_vnic_adapter *opa_vnic_add_netdev(काष्ठा ib_device *ibdev,
					     u8 port_num, u8 vport_num);
व्योम opa_vnic_rem_netdev(काष्ठा opa_vnic_adapter *adapter);
व्योम opa_vnic_encap_skb(काष्ठा opa_vnic_adapter *adapter, काष्ठा sk_buff *skb);
u8 opa_vnic_get_vl(काष्ठा opa_vnic_adapter *adapter, काष्ठा sk_buff *skb);
u8 opa_vnic_calc_entropy(काष्ठा sk_buff *skb);
व्योम opa_vnic_process_vema_config(काष्ठा opa_vnic_adapter *adapter);
व्योम opa_vnic_release_mac_tbl(काष्ठा opa_vnic_adapter *adapter);
व्योम opa_vnic_query_mac_tbl(काष्ठा opa_vnic_adapter *adapter,
			    काष्ठा opa_veswport_mactable *tbl);
पूर्णांक opa_vnic_update_mac_tbl(काष्ठा opa_vnic_adapter *adapter,
			    काष्ठा opa_veswport_mactable *tbl);
व्योम opa_vnic_query_ucast_macs(काष्ठा opa_vnic_adapter *adapter,
			       काष्ठा opa_veswport_अगरace_macs *macs);
व्योम opa_vnic_query_mcast_macs(काष्ठा opa_vnic_adapter *adapter,
			       काष्ठा opa_veswport_अगरace_macs *macs);
व्योम opa_vnic_get_summary_counters(काष्ठा opa_vnic_adapter *adapter,
				   काष्ठा opa_veswport_summary_counters *cntrs);
व्योम opa_vnic_get_error_counters(काष्ठा opa_vnic_adapter *adapter,
				 काष्ठा opa_veswport_error_counters *cntrs);
व्योम opa_vnic_get_vesw_info(काष्ठा opa_vnic_adapter *adapter,
			    काष्ठा opa_vesw_info *info);
व्योम opa_vnic_set_vesw_info(काष्ठा opa_vnic_adapter *adapter,
			    काष्ठा opa_vesw_info *info);
व्योम opa_vnic_get_per_veswport_info(काष्ठा opa_vnic_adapter *adapter,
				    काष्ठा opa_per_veswport_info *info);
व्योम opa_vnic_set_per_veswport_info(काष्ठा opa_vnic_adapter *adapter,
				    काष्ठा opa_per_veswport_info *info);
व्योम opa_vnic_vema_report_event(काष्ठा opa_vnic_adapter *adapter, u8 event);
व्योम opa_vnic_set_ethtool_ops(काष्ठा net_device *netdev);
व्योम opa_vnic_vema_send_trap(काष्ठा opa_vnic_adapter *adapter,
			     काष्ठा __opa_veswport_trap *data, u32 lid);

#पूर्ण_अगर /* _OPA_VNIC_INTERNAL_H */
