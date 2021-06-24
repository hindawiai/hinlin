<शैली गुरु>
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
 * This file contains OPA VNIC EMA Interface functions.
 */

#समावेश "opa_vnic_internal.h"

/**
 * opa_vnic_vema_report_event - sent trap to report the specअगरied event
 * @adapter: vnic port adapter
 * @event: event to be reported
 *
 * This function calls vema api to sent a trap क्रम the given event.
 */
व्योम opa_vnic_vema_report_event(काष्ठा opa_vnic_adapter *adapter, u8 event)
अणु
	काष्ठा __opa_veswport_info *info = &adapter->info;
	काष्ठा __opa_veswport_trap trap_data;

	trap_data.fabric_id = info->vesw.fabric_id;
	trap_data.veswid = info->vesw.vesw_id;
	trap_data.veswportnum = info->vport.port_num;
	trap_data.opaportnum = adapter->port_num;
	trap_data.veswportindex = adapter->vport_num;
	trap_data.opcode = event;

	opa_vnic_vema_send_trap(adapter, &trap_data, info->vport.encap_slid);
पूर्ण

/**
 * opa_vnic_get_summary_counters - get summary counters
 * @adapter: vnic port adapter
 * @cntrs: poपूर्णांकer to destination summary counters काष्ठाure
 *
 * This function populates the summary counters that is मुख्यtained by the
 * given adapter to destination address provided.
 */
व्योम opa_vnic_get_summary_counters(काष्ठा opa_vnic_adapter *adapter,
				   काष्ठा opa_veswport_summary_counters *cntrs)
अणु
	काष्ठा opa_vnic_stats vstats;
	__be64 *dst;
	u64 *src;

	स_रखो(&vstats, 0, माप(vstats));
	spin_lock(&adapter->stats_lock);
	adapter->rn_ops->nकरो_get_stats64(adapter->netdev, &vstats.netstats);
	spin_unlock(&adapter->stats_lock);

	cntrs->vp_instance = cpu_to_be16(adapter->vport_num);
	cntrs->vesw_id = cpu_to_be16(adapter->info.vesw.vesw_id);
	cntrs->veswport_num = cpu_to_be32(adapter->port_num);

	cntrs->tx_errors = cpu_to_be64(vstats.netstats.tx_errors);
	cntrs->rx_errors = cpu_to_be64(vstats.netstats.rx_errors);
	cntrs->tx_packets = cpu_to_be64(vstats.netstats.tx_packets);
	cntrs->rx_packets = cpu_to_be64(vstats.netstats.rx_packets);
	cntrs->tx_bytes = cpu_to_be64(vstats.netstats.tx_bytes);
	cntrs->rx_bytes = cpu_to_be64(vstats.netstats.rx_bytes);

	/*
	 * This loop depends on layout of
	 * opa_veswport_summary_counters opa_vnic_stats काष्ठाures.
	 */
	क्रम (dst = &cntrs->tx_unicast, src = &vstats.tx_grp.unicast;
	     dst < &cntrs->reserved[0]; dst++, src++) अणु
		*dst = cpu_to_be64(*src);
	पूर्ण
पूर्ण

/**
 * opa_vnic_get_error_counters - get error counters
 * @adapter: vnic port adapter
 * @cntrs: poपूर्णांकer to destination error counters काष्ठाure
 *
 * This function populates the error counters that is मुख्यtained by the
 * given adapter to destination address provided.
 */
व्योम opa_vnic_get_error_counters(काष्ठा opa_vnic_adapter *adapter,
				 काष्ठा opa_veswport_error_counters *cntrs)
अणु
	काष्ठा opa_vnic_stats vstats;

	स_रखो(&vstats, 0, माप(vstats));
	spin_lock(&adapter->stats_lock);
	adapter->rn_ops->nकरो_get_stats64(adapter->netdev, &vstats.netstats);
	spin_unlock(&adapter->stats_lock);

	cntrs->vp_instance = cpu_to_be16(adapter->vport_num);
	cntrs->vesw_id = cpu_to_be16(adapter->info.vesw.vesw_id);
	cntrs->veswport_num = cpu_to_be32(adapter->port_num);

	cntrs->tx_errors = cpu_to_be64(vstats.netstats.tx_errors);
	cntrs->rx_errors = cpu_to_be64(vstats.netstats.rx_errors);
	cntrs->tx_dlid_zero = cpu_to_be64(vstats.tx_dlid_zero);
	cntrs->tx_drop_state = cpu_to_be64(vstats.tx_drop_state);
	cntrs->tx_logic = cpu_to_be64(vstats.netstats.tx_fअगरo_errors +
				      vstats.netstats.tx_carrier_errors);

	cntrs->rx_bad_veswid = cpu_to_be64(vstats.netstats.rx_nohandler);
	cntrs->rx_runt = cpu_to_be64(vstats.rx_runt);
	cntrs->rx_oversize = cpu_to_be64(vstats.rx_oversize);
	cntrs->rx_drop_state = cpu_to_be64(vstats.rx_drop_state);
	cntrs->rx_logic = cpu_to_be64(vstats.netstats.rx_fअगरo_errors);
पूर्ण

/**
 * opa_vnic_get_vesw_info -- Get the vesw inक्रमmation
 * @adapter: vnic port adapter
 * @info: poपूर्णांकer to destination vesw info काष्ठाure
 *
 * This function copies the vesw info that is मुख्यtained by the
 * given adapter to destination address provided.
 */
व्योम opa_vnic_get_vesw_info(काष्ठा opa_vnic_adapter *adapter,
			    काष्ठा opa_vesw_info *info)
अणु
	काष्ठा __opa_vesw_info *src = &adapter->info.vesw;
	पूर्णांक i;

	info->fabric_id = cpu_to_be16(src->fabric_id);
	info->vesw_id = cpu_to_be16(src->vesw_id);
	स_नकल(info->rsvd0, src->rsvd0, ARRAY_SIZE(src->rsvd0));
	info->def_port_mask = cpu_to_be16(src->def_port_mask);
	स_नकल(info->rsvd1, src->rsvd1, ARRAY_SIZE(src->rsvd1));
	info->pkey = cpu_to_be16(src->pkey);

	स_नकल(info->rsvd2, src->rsvd2, ARRAY_SIZE(src->rsvd2));
	info->u_mcast_dlid = cpu_to_be32(src->u_mcast_dlid);
	क्रम (i = 0; i < OPA_VESW_MAX_NUM_DEF_PORT; i++)
		info->u_ucast_dlid[i] = cpu_to_be32(src->u_ucast_dlid[i]);

	info->rc = cpu_to_be32(src->rc);

	स_नकल(info->rsvd3, src->rsvd3, ARRAY_SIZE(src->rsvd3));
	info->eth_mtu = cpu_to_be16(src->eth_mtu);
	स_नकल(info->rsvd4, src->rsvd4, ARRAY_SIZE(src->rsvd4));
पूर्ण

/**
 * opa_vnic_set_vesw_info -- Set the vesw inक्रमmation
 * @adapter: vnic port adapter
 * @info: poपूर्णांकer to vesw info काष्ठाure
 *
 * This function updates the vesw info that is मुख्यtained by the
 * given adapter with vesw info provided. Reserved fields are stored
 * and वापसed back to EM as is.
 */
व्योम opa_vnic_set_vesw_info(काष्ठा opa_vnic_adapter *adapter,
			    काष्ठा opa_vesw_info *info)
अणु
	काष्ठा __opa_vesw_info *dst = &adapter->info.vesw;
	पूर्णांक i;

	dst->fabric_id = be16_to_cpu(info->fabric_id);
	dst->vesw_id = be16_to_cpu(info->vesw_id);
	स_नकल(dst->rsvd0, info->rsvd0, ARRAY_SIZE(info->rsvd0));
	dst->def_port_mask = be16_to_cpu(info->def_port_mask);
	स_नकल(dst->rsvd1, info->rsvd1, ARRAY_SIZE(info->rsvd1));
	dst->pkey = be16_to_cpu(info->pkey);

	स_नकल(dst->rsvd2, info->rsvd2, ARRAY_SIZE(info->rsvd2));
	dst->u_mcast_dlid = be32_to_cpu(info->u_mcast_dlid);
	क्रम (i = 0; i < OPA_VESW_MAX_NUM_DEF_PORT; i++)
		dst->u_ucast_dlid[i] = be32_to_cpu(info->u_ucast_dlid[i]);

	dst->rc = be32_to_cpu(info->rc);

	स_नकल(dst->rsvd3, info->rsvd3, ARRAY_SIZE(info->rsvd3));
	dst->eth_mtu = be16_to_cpu(info->eth_mtu);
	स_नकल(dst->rsvd4, info->rsvd4, ARRAY_SIZE(info->rsvd4));
पूर्ण

/**
 * opa_vnic_get_per_veswport_info -- Get the vesw per port inक्रमmation
 * @adapter: vnic port adapter
 * @info: poपूर्णांकer to destination vport info काष्ठाure
 *
 * This function copies the vesw per port info that is मुख्यtained by the
 * given adapter to destination address provided.
 * Note that the पढ़ो only fields are not copied.
 */
व्योम opa_vnic_get_per_veswport_info(काष्ठा opa_vnic_adapter *adapter,
				    काष्ठा opa_per_veswport_info *info)
अणु
	काष्ठा __opa_per_veswport_info *src = &adapter->info.vport;

	info->port_num = cpu_to_be32(src->port_num);
	info->eth_link_status = src->eth_link_status;
	स_नकल(info->rsvd0, src->rsvd0, ARRAY_SIZE(src->rsvd0));

	स_नकल(info->base_mac_addr, src->base_mac_addr,
	       ARRAY_SIZE(info->base_mac_addr));
	info->config_state = src->config_state;
	info->oper_state = src->oper_state;
	info->max_mac_tbl_ent = cpu_to_be16(src->max_mac_tbl_ent);
	info->max_smac_ent = cpu_to_be16(src->max_smac_ent);
	info->mac_tbl_digest = cpu_to_be32(src->mac_tbl_digest);
	स_नकल(info->rsvd1, src->rsvd1, ARRAY_SIZE(src->rsvd1));

	info->encap_slid = cpu_to_be32(src->encap_slid);
	स_नकल(info->pcp_to_sc_uc, src->pcp_to_sc_uc,
	       ARRAY_SIZE(info->pcp_to_sc_uc));
	स_नकल(info->pcp_to_vl_uc, src->pcp_to_vl_uc,
	       ARRAY_SIZE(info->pcp_to_vl_uc));
	स_नकल(info->pcp_to_sc_mc, src->pcp_to_sc_mc,
	       ARRAY_SIZE(info->pcp_to_sc_mc));
	स_नकल(info->pcp_to_vl_mc, src->pcp_to_vl_mc,
	       ARRAY_SIZE(info->pcp_to_vl_mc));
	info->non_vlan_sc_uc = src->non_vlan_sc_uc;
	info->non_vlan_vl_uc = src->non_vlan_vl_uc;
	info->non_vlan_sc_mc = src->non_vlan_sc_mc;
	info->non_vlan_vl_mc = src->non_vlan_vl_mc;
	स_नकल(info->rsvd2, src->rsvd2, ARRAY_SIZE(src->rsvd2));

	info->uc_macs_gen_count = cpu_to_be16(src->uc_macs_gen_count);
	info->mc_macs_gen_count = cpu_to_be16(src->mc_macs_gen_count);
	स_नकल(info->rsvd3, src->rsvd3, ARRAY_SIZE(src->rsvd3));
पूर्ण

/**
 * opa_vnic_set_per_veswport_info -- Set vesw per port inक्रमmation
 * @adapter: vnic port adapter
 * @info: poपूर्णांकer to vport info काष्ठाure
 *
 * This function updates the vesw per port info that is मुख्यtained by the
 * given adapter with vesw per port info provided. Reserved fields are
 * stored and वापसed back to EM as is.
 */
व्योम opa_vnic_set_per_veswport_info(काष्ठा opa_vnic_adapter *adapter,
				    काष्ठा opa_per_veswport_info *info)
अणु
	काष्ठा __opa_per_veswport_info *dst = &adapter->info.vport;

	dst->port_num = be32_to_cpu(info->port_num);
	स_नकल(dst->rsvd0, info->rsvd0, ARRAY_SIZE(info->rsvd0));

	स_नकल(dst->base_mac_addr, info->base_mac_addr,
	       ARRAY_SIZE(dst->base_mac_addr));
	dst->config_state = info->config_state;
	स_नकल(dst->rsvd1, info->rsvd1, ARRAY_SIZE(info->rsvd1));

	dst->encap_slid = be32_to_cpu(info->encap_slid);
	स_नकल(dst->pcp_to_sc_uc, info->pcp_to_sc_uc,
	       ARRAY_SIZE(dst->pcp_to_sc_uc));
	स_नकल(dst->pcp_to_vl_uc, info->pcp_to_vl_uc,
	       ARRAY_SIZE(dst->pcp_to_vl_uc));
	स_नकल(dst->pcp_to_sc_mc, info->pcp_to_sc_mc,
	       ARRAY_SIZE(dst->pcp_to_sc_mc));
	स_नकल(dst->pcp_to_vl_mc, info->pcp_to_vl_mc,
	       ARRAY_SIZE(dst->pcp_to_vl_mc));
	dst->non_vlan_sc_uc = info->non_vlan_sc_uc;
	dst->non_vlan_vl_uc = info->non_vlan_vl_uc;
	dst->non_vlan_sc_mc = info->non_vlan_sc_mc;
	dst->non_vlan_vl_mc = info->non_vlan_vl_mc;
	स_नकल(dst->rsvd2, info->rsvd2, ARRAY_SIZE(info->rsvd2));
	स_नकल(dst->rsvd3, info->rsvd3, ARRAY_SIZE(info->rsvd3));
पूर्ण

/**
 * opa_vnic_query_mcast_macs - query multicast mac list
 * @adapter: vnic port adapter
 * @macs: poपूर्णांकer mac list
 *
 * This function populates the provided mac list with the configured
 * multicast addresses in the adapter.
 */
व्योम opa_vnic_query_mcast_macs(काष्ठा opa_vnic_adapter *adapter,
			       काष्ठा opa_veswport_अगरace_macs *macs)
अणु
	u16 start_idx, num_macs, idx = 0, count = 0;
	काष्ठा netdev_hw_addr *ha;

	start_idx = be16_to_cpu(macs->start_idx);
	num_macs = be16_to_cpu(macs->num_macs_in_msg);
	netdev_क्रम_each_mc_addr(ha, adapter->netdev) अणु
		काष्ठा opa_vnic_अगरace_mac_entry *entry = &macs->entry[count];

		अगर (start_idx > idx++)
			जारी;
		अन्यथा अगर (num_macs == count)
			अवरोध;
		स_नकल(entry, ha->addr, माप(*entry));
		count++;
	पूर्ण

	macs->tot_macs_in_lst = cpu_to_be16(netdev_mc_count(adapter->netdev));
	macs->num_macs_in_msg = cpu_to_be16(count);
	macs->gen_count = cpu_to_be16(adapter->info.vport.mc_macs_gen_count);
पूर्ण

/**
 * opa_vnic_query_ucast_macs - query unicast mac list
 * @adapter: vnic port adapter
 * @macs: poपूर्णांकer mac list
 *
 * This function populates the provided mac list with the configured
 * unicast addresses in the adapter.
 */
व्योम opa_vnic_query_ucast_macs(काष्ठा opa_vnic_adapter *adapter,
			       काष्ठा opa_veswport_अगरace_macs *macs)
अणु
	u16 start_idx, tot_macs, num_macs, idx = 0, count = 0, em_macs = 0;
	काष्ठा netdev_hw_addr *ha;

	start_idx = be16_to_cpu(macs->start_idx);
	num_macs = be16_to_cpu(macs->num_macs_in_msg);
	/* loop through dev_addrs list first */
	क्रम_each_dev_addr(adapter->netdev, ha) अणु
		काष्ठा opa_vnic_अगरace_mac_entry *entry = &macs->entry[count];

		/* Do not include EM specअगरied MAC address */
		अगर (!स_भेद(adapter->info.vport.base_mac_addr, ha->addr,
			    ARRAY_SIZE(adapter->info.vport.base_mac_addr))) अणु
			em_macs++;
			जारी;
		पूर्ण

		अगर (start_idx > idx++)
			जारी;
		अन्यथा अगर (num_macs == count)
			अवरोध;
		स_नकल(entry, ha->addr, माप(*entry));
		count++;
	पूर्ण

	/* loop through uc list */
	netdev_क्रम_each_uc_addr(ha, adapter->netdev) अणु
		काष्ठा opa_vnic_अगरace_mac_entry *entry = &macs->entry[count];

		अगर (start_idx > idx++)
			जारी;
		अन्यथा अगर (num_macs == count)
			अवरोध;
		स_नकल(entry, ha->addr, माप(*entry));
		count++;
	पूर्ण

	tot_macs = netdev_hw_addr_list_count(&adapter->netdev->dev_addrs) +
		   netdev_uc_count(adapter->netdev) - em_macs;
	macs->tot_macs_in_lst = cpu_to_be16(tot_macs);
	macs->num_macs_in_msg = cpu_to_be16(count);
	macs->gen_count = cpu_to_be16(adapter->info.vport.uc_macs_gen_count);
पूर्ण
