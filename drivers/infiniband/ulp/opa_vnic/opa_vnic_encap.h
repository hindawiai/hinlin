<शैली गुरु>
#अगर_अघोषित _OPA_VNIC_ENCAP_H
#घोषणा _OPA_VNIC_ENCAP_H
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
 * This file contains all OPA VNIC declaration required क्रम encapsulation
 * and decapsulation of Ethernet packets
 */

#समावेश <linux/types.h>
#समावेश <rdma/ib_mad.h>

/* EMA class version */
#घोषणा OPA_EMA_CLASS_VERSION               0x80

/*
 * Define the Intel venकरोr management class क्रम OPA
 * ETHERNET MANAGEMENT
 */
#घोषणा OPA_MGMT_CLASS_INTEL_EMA            0x34

/* EM attribute IDs */
#घोषणा OPA_EM_ATTR_CLASS_PORT_INFO                 0x0001
#घोषणा OPA_EM_ATTR_VESWPORT_INFO                   0x0011
#घोषणा OPA_EM_ATTR_VESWPORT_MAC_ENTRIES            0x0012
#घोषणा OPA_EM_ATTR_IFACE_UCAST_MACS                0x0013
#घोषणा OPA_EM_ATTR_IFACE_MCAST_MACS                0x0014
#घोषणा OPA_EM_ATTR_DELETE_VESW                     0x0015
#घोषणा OPA_EM_ATTR_VESWPORT_SUMMARY_COUNTERS       0x0020
#घोषणा OPA_EM_ATTR_VESWPORT_ERROR_COUNTERS         0x0022

/* VNIC configured and operational state values */
#घोषणा OPA_VNIC_STATE_DROP_ALL        0x1
#घोषणा OPA_VNIC_STATE_FORWARDING      0x3

#घोषणा OPA_VESW_MAX_NUM_DEF_PORT   16
#घोषणा OPA_VNIC_MAX_NUM_PCP        8

#घोषणा OPA_VNIC_EMA_DATA    (OPA_MGMT_MAD_SIZE - IB_MGMT_VENDOR_HDR)

/* Defines क्रम venकरोr specअगरic notice(trap) attributes */
#घोषणा OPA_INTEL_EMA_NOTICE_TYPE_INFO 0x04

/* INTEL OUI */
#घोषणा INTEL_OUI_1 0x00
#घोषणा INTEL_OUI_2 0x06
#घोषणा INTEL_OUI_3 0x6a

/* Trap opcodes sent from VNIC */
#घोषणा OPA_VESWPORT_TRAP_IFACE_UCAST_MAC_CHANGE 0x1
#घोषणा OPA_VESWPORT_TRAP_IFACE_MCAST_MAC_CHANGE 0x2
#घोषणा OPA_VESWPORT_TRAP_ETH_LINK_STATUS_CHANGE 0x3

#घोषणा OPA_VNIC_DLID_SD_IS_SRC_MAC(dlid_sd)  (!!((dlid_sd) & 0x20))
#घोषणा OPA_VNIC_DLID_SD_GET_DLID(dlid_sd)    ((dlid_sd) >> 8)

/* VNIC Ethernet link status */
#घोषणा OPA_VNIC_ETH_LINK_UP     1
#घोषणा OPA_VNIC_ETH_LINK_DOWN   2

/* routing control */
#घोषणा OPA_VNIC_ENCAP_RC_DEFAULT   0
#घोषणा OPA_VNIC_ENCAP_RC_IPV4      4
#घोषणा OPA_VNIC_ENCAP_RC_IPV4_UDP  8
#घोषणा OPA_VNIC_ENCAP_RC_IPV4_TCP  12
#घोषणा OPA_VNIC_ENCAP_RC_IPV6      16
#घोषणा OPA_VNIC_ENCAP_RC_IPV6_TCP  20
#घोषणा OPA_VNIC_ENCAP_RC_IPV6_UDP  24

#घोषणा OPA_VNIC_ENCAP_RC_EXT(w, b) (((w) >> OPA_VNIC_ENCAP_RC_ ## b) & 0x7)

/**
 * काष्ठा opa_vesw_info - OPA vnic चयन inक्रमmation
 * @fabric_id: 10-bit fabric id
 * @vesw_id: 12-bit भव ethernet चयन id
 * @rsvd0: reserved bytes
 * @def_port_mask: biपंचांगask of शेष ports
 * @rsvd1: reserved bytes
 * @pkey: partition key
 * @rsvd2: reserved bytes
 * @u_mcast_dlid: unknown multicast dlid
 * @u_ucast_dlid: array of unknown unicast dlids
 * @rsvd3: reserved bytes
 * @rc: routing control
 * @eth_mtu: Ethernet MTU
 * @rsvd4: reserved bytes
 */
काष्ठा opa_vesw_info अणु
	__be16  fabric_id;
	__be16  vesw_id;

	u8      rsvd0[6];
	__be16  def_port_mask;

	u8      rsvd1[2];
	__be16  pkey;

	u8      rsvd2[4];
	__be32  u_mcast_dlid;
	__be32  u_ucast_dlid[OPA_VESW_MAX_NUM_DEF_PORT];

	__be32  rc;

	u8      rsvd3[56];
	__be16  eth_mtu;
	u8      rsvd4[2];
पूर्ण __packed;

/**
 * काष्ठा opa_per_veswport_info - OPA vnic per port inक्रमmation
 * @port_num: port number
 * @eth_link_status: current ethernet link state
 * @rsvd0: reserved bytes
 * @base_mac_addr: base mac address
 * @config_state: configured port state
 * @oper_state: operational port state
 * @max_mac_tbl_ent: max number of mac table entries
 * @max_smac_ent: max smac entries in mac table
 * @mac_tbl_digest: mac table digest
 * @rsvd1: reserved bytes
 * @encap_slid: base slid क्रम the port
 * @pcp_to_sc_uc: sc by pcp index क्रम unicast ethernet packets
 * @pcp_to_vl_uc: vl by pcp index क्रम unicast ethernet packets
 * @pcp_to_sc_mc: sc by pcp index क्रम multicast ethernet packets
 * @pcp_to_vl_mc: vl by pcp index क्रम multicast ethernet packets
 * @non_vlan_sc_uc: sc क्रम non-vlan unicast ethernet packets
 * @non_vlan_vl_uc: vl क्रम non-vlan unicast ethernet packets
 * @non_vlan_sc_mc: sc क्रम non-vlan multicast ethernet packets
 * @non_vlan_vl_mc: vl क्रम non-vlan multicast ethernet packets
 * @rsvd2: reserved bytes
 * @uc_macs_gen_count: generation count क्रम unicast macs list
 * @mc_macs_gen_count: generation count क्रम multicast macs list
 * @rsvd3: reserved bytes
 */
काष्ठा opa_per_veswport_info अणु
	__be32  port_num;

	u8      eth_link_status;
	u8      rsvd0[3];

	u8      base_mac_addr[ETH_ALEN];
	u8      config_state;
	u8      oper_state;

	__be16  max_mac_tbl_ent;
	__be16  max_smac_ent;
	__be32  mac_tbl_digest;
	u8      rsvd1[4];

	__be32  encap_slid;

	u8      pcp_to_sc_uc[OPA_VNIC_MAX_NUM_PCP];
	u8      pcp_to_vl_uc[OPA_VNIC_MAX_NUM_PCP];
	u8      pcp_to_sc_mc[OPA_VNIC_MAX_NUM_PCP];
	u8      pcp_to_vl_mc[OPA_VNIC_MAX_NUM_PCP];

	u8      non_vlan_sc_uc;
	u8      non_vlan_vl_uc;
	u8      non_vlan_sc_mc;
	u8      non_vlan_vl_mc;

	u8      rsvd2[48];

	__be16  uc_macs_gen_count;
	__be16  mc_macs_gen_count;

	u8      rsvd3[8];
पूर्ण __packed;

/**
 * काष्ठा opa_veswport_info - OPA vnic port inक्रमmation
 * @vesw: OPA vnic चयन inक्रमmation
 * @vport: OPA vnic per port inक्रमmation
 *
 * On host, each of the भव ethernet ports beदीर्घs
 * to a dअगरferent भव ethernet चयनes.
 */
काष्ठा opa_veswport_info अणु
	काष्ठा opa_vesw_info          vesw;
	काष्ठा opa_per_veswport_info  vport;
पूर्ण;

/**
 * काष्ठा opa_veswport_mactable_entry - single entry in the क्रमwarding table
 * @mac_addr: MAC address
 * @mac_addr_mask: MAC address bit mask
 * @dlid_sd: Matching DLID and side data
 *
 * On the host each भव ethernet port will have
 * a क्रमwarding table. These tables are used to
 * map a MAC to a LID and other data. For more
 * details see काष्ठा opa_veswport_mactable_entries.
 * This is the काष्ठाure of a single mactable entry
 */
काष्ठा opa_veswport_mactable_entry अणु
	u8      mac_addr[ETH_ALEN];
	u8      mac_addr_mask[ETH_ALEN];
	__be32  dlid_sd;
पूर्ण __packed;

/**
 * काष्ठा opa_veswport_mactable - Forwarding table array
 * @offset: mac table starting offset
 * @num_entries: Number of entries to get or set
 * @mac_tbl_digest: mac table digest
 * @tbl_entries: Array of table entries
 *
 * The EM sends करोwn this काष्ठाure in a MAD indicating
 * the starting offset in the क्रमwarding table that this
 * entry is to be loaded पूर्णांकo and the number of entries
 * that that this MAD instance contains
 * The mac_tbl_digest has been added to this MAD काष्ठाure. It will be set by
 * the EM and it will be used by the EM to check अगर there are any
 * discrepancies with this value and the value
 * मुख्यtained by the EM in the हाल of VNIC port being deleted or unloaded
 * A new instantiation of a VNIC will always have a value of zero.
 * This value is stored as part of the vnic adapter काष्ठाure and will be
 * accessed by the GET and SET routines क्रम both the mactable entries and the
 * veswport info.
 */
काष्ठा opa_veswport_mactable अणु
	__be16                              offset;
	__be16                              num_entries;
	__be32                              mac_tbl_digest;
	काष्ठा opa_veswport_mactable_entry  tbl_entries[];
पूर्ण __packed;

/**
 * काष्ठा opa_veswport_summary_counters - summary counters
 * @vp_instance: vport instance on the OPA port
 * @vesw_id: भव ethernet चयन id
 * @veswport_num: भव ethernet चयन port number
 * @tx_errors: transmit errors
 * @rx_errors: receive errors
 * @tx_packets: transmit packets
 * @rx_packets: receive packets
 * @tx_bytes: transmit bytes
 * @rx_bytes: receive bytes
 * @tx_unicast: unicast packets transmitted
 * @tx_mcastbcast: multicast/broadcast packets transmitted
 * @tx_untagged: non-vlan packets transmitted
 * @tx_vlan: vlan packets transmitted
 * @tx_64_size: transmit packet length is 64 bytes
 * @tx_65_127: transmit packet length is >=65 and < 127 bytes
 * @tx_128_255: transmit packet length is >=128 and < 255 bytes
 * @tx_256_511: transmit packet length is >=256 and < 511 bytes
 * @tx_512_1023: transmit packet length is >=512 and < 1023 bytes
 * @tx_1024_1518: transmit packet length is >=1024 and < 1518 bytes
 * @tx_1519_max: transmit packet length >= 1519 bytes
 * @rx_unicast: unicast packets received
 * @rx_mcastbcast: multicast/broadcast packets received
 * @rx_untagged: non-vlan packets received
 * @rx_vlan: vlan packets received
 * @rx_64_size: received packet length is 64 bytes
 * @rx_65_127: received packet length is >=65 and < 127 bytes
 * @rx_128_255: received packet length is >=128 and < 255 bytes
 * @rx_256_511: received packet length is >=256 and < 511 bytes
 * @rx_512_1023: received packet length is >=512 and < 1023 bytes
 * @rx_1024_1518: received packet length is >=1024 and < 1518 bytes
 * @rx_1519_max: received packet length >= 1519 bytes
 * @reserved: reserved bytes
 *
 * All the above are counters of corresponding conditions.
 */
काष्ठा opa_veswport_summary_counters अणु
	__be16  vp_instance;
	__be16  vesw_id;
	__be32  veswport_num;

	__be64  tx_errors;
	__be64  rx_errors;
	__be64  tx_packets;
	__be64  rx_packets;
	__be64  tx_bytes;
	__be64  rx_bytes;

	__be64  tx_unicast;
	__be64  tx_mcastbcast;

	__be64  tx_untagged;
	__be64  tx_vlan;

	__be64  tx_64_size;
	__be64  tx_65_127;
	__be64  tx_128_255;
	__be64  tx_256_511;
	__be64  tx_512_1023;
	__be64  tx_1024_1518;
	__be64  tx_1519_max;

	__be64  rx_unicast;
	__be64  rx_mcastbcast;

	__be64  rx_untagged;
	__be64  rx_vlan;

	__be64  rx_64_size;
	__be64  rx_65_127;
	__be64  rx_128_255;
	__be64  rx_256_511;
	__be64  rx_512_1023;
	__be64  rx_1024_1518;
	__be64  rx_1519_max;

	__be64  reserved[16];
पूर्ण __packed;

/**
 * काष्ठा opa_veswport_error_counters - error counters
 * @vp_instance: vport instance on the OPA port
 * @vesw_id: भव ethernet चयन id
 * @veswport_num: भव ethernet चयन port number
 * @tx_errors: transmit errors
 * @rx_errors: receive errors
 * @rsvd0: reserved bytes
 * @tx_smac_filt: smac filter errors
 * @rsvd1: reserved bytes
 * @rsvd2: reserved bytes
 * @rsvd3: reserved bytes
 * @tx_dlid_zero: transmit packets with invalid dlid
 * @rsvd4: reserved bytes
 * @tx_logic: other transmit errors
 * @rsvd5: reserved bytes
 * @tx_drop_state: packet tansmission in non-क्रमward port state
 * @rx_bad_veswid: received packet with invalid vesw id
 * @rsvd6: reserved bytes
 * @rx_runt: received ethernet packet with length < 64 bytes
 * @rx_oversize: received ethernet packet with length > MTU size
 * @rsvd7: reserved bytes
 * @rx_eth_करोwn: received packets when पूर्णांकerface is करोwn
 * @rx_drop_state: received packets in non-क्रमwarding port state
 * @rx_logic: other receive errors
 * @rsvd8: reserved bytes
 * @rsvd9: reserved bytes
 *
 * All the above are counters of corresponding error conditions.
 */
काष्ठा opa_veswport_error_counters अणु
	__be16  vp_instance;
	__be16  vesw_id;
	__be32  veswport_num;

	__be64  tx_errors;
	__be64  rx_errors;

	__be64  rsvd0;
	__be64  tx_smac_filt;
	__be64  rsvd1;
	__be64  rsvd2;
	__be64  rsvd3;
	__be64  tx_dlid_zero;
	__be64  rsvd4;
	__be64  tx_logic;
	__be64  rsvd5;
	__be64  tx_drop_state;

	__be64  rx_bad_veswid;
	__be64  rsvd6;
	__be64  rx_runt;
	__be64  rx_oversize;
	__be64  rsvd7;
	__be64  rx_eth_करोwn;
	__be64  rx_drop_state;
	__be64  rx_logic;
	__be64  rsvd8;

	__be64  rsvd9[16];
पूर्ण __packed;

/**
 * काष्ठा opa_veswport_trap - Trap message sent to EM by VNIC
 * @fabric_id: 10 bit fabric id
 * @veswid: 12 bit भव ethernet चयन id
 * @veswportnum: logical port number on the Virtual चयन
 * @opaportnum: physical port num (redundant on host)
 * @veswportindex: चयन port index on opa port 0 based
 * @opcode: operation
 * @reserved: 32 bit क्रम alignment
 *
 * The VNIC will send trap messages to the Ethernet manager to
 * inक्रमm it about changes to the VNIC config, behaviour etc.
 * This is the क्रमmat of the trap payload.
 */
काष्ठा opa_veswport_trap अणु
	__be16  fabric_id;
	__be16  veswid;
	__be32  veswportnum;
	__be16  opaportnum;
	u8      veswportindex;
	u8      opcode;
	__be32  reserved;
पूर्ण __packed;

/**
 * काष्ठा opa_vnic_अगरace_mac_entry - single entry in the mac list
 * @mac_addr: MAC address
 */
काष्ठा opa_vnic_अगरace_mac_entry अणु
	u8 mac_addr[ETH_ALEN];
पूर्ण;

/**
 * काष्ठा opa_veswport_अगरace_macs - Msg to set globally administered MAC
 * @start_idx: position of first entry (0 based)
 * @num_macs_in_msg: number of MACs in this message
 * @tot_macs_in_lst: The total number of MACs the agent has
 * @gen_count: gen_count to indicate change
 * @entry: The mac list entry
 *
 * Same attribute IDS and attribute modअगरiers as in locally administered
 * addresses used to set globally administered addresses
 */
काष्ठा opa_veswport_अगरace_macs अणु
	__be16 start_idx;
	__be16 num_macs_in_msg;
	__be16 tot_macs_in_lst;
	__be16 gen_count;
	काष्ठा opa_vnic_अगरace_mac_entry entry[];
पूर्ण __packed;

/**
 * काष्ठा opa_vnic_vema_mad - Generic VEMA MAD
 * @mad_hdr: Generic MAD header
 * @rmpp_hdr: RMPP header क्रम venकरोr specअगरic MADs
 * @reserved: reserved bytes
 * @oui: Unique org identअगरier
 * @data: MAD data
 */
काष्ठा opa_vnic_vema_mad अणु
	काष्ठा ib_mad_hdr  mad_hdr;
	काष्ठा ib_rmpp_hdr rmpp_hdr;
	u8                 reserved;
	u8                 oui[3];
	u8                 data[OPA_VNIC_EMA_DATA];
पूर्ण;

/**
 * काष्ठा opa_vnic_notice_attr - Generic Notice MAD
 * @gen_type: Generic/Specअगरic bit and type of notice
 * @oui_1: Venकरोr ID byte 1
 * @oui_2: Venकरोr ID byte 2
 * @oui_3: Venकरोr ID byte 3
 * @trap_num: Trap number
 * @toggle_count: Notice toggle bit and count value
 * @issuer_lid: Trap issuer's lid
 * @reserved: reserved bytes
 * @issuer_gid: Issuer GID (only अगर Report method)
 * @raw_data: Trap message body
 */
काष्ठा opa_vnic_notice_attr अणु
	u8     gen_type;
	u8     oui_1;
	u8     oui_2;
	u8     oui_3;
	__be16 trap_num;
	__be16 toggle_count;
	__be32 issuer_lid;
	__be32 reserved;
	u8     issuer_gid[16];
	u8     raw_data[64];
पूर्ण __packed;

/**
 * काष्ठा opa_vnic_vema_mad_trap - Generic VEMA MAD Trap
 * @mad_hdr: Generic MAD header
 * @rmpp_hdr: RMPP header क्रम venकरोr specअगरic MADs
 * @reserved: reserved bytes
 * @oui: Unique org identअगरier
 * @notice: Notice काष्ठाure
 */
काष्ठा opa_vnic_vema_mad_trap अणु
	काष्ठा ib_mad_hdr            mad_hdr;
	काष्ठा ib_rmpp_hdr           rmpp_hdr;
	u8                           reserved;
	u8                           oui[3];
	काष्ठा opa_vnic_notice_attr  notice;
पूर्ण;

#पूर्ण_अगर /* _OPA_VNIC_ENCAP_H */
