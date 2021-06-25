<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2012-2014 Intel Corporation
 * Copyright (C) 2013-2014 Intel Mobile Communications GmbH
 * Copyright (C) 2015 Intel Deutschland GmbH
 */
#समावेश <net/ipv6.h>
#समावेश <net/addrconf.h>
#समावेश <linux/bitops.h>
#समावेश "mvm.h"

व्योम iwl_mvm_set_wowlan_qos_seq(काष्ठा iwl_mvm_sta *mvm_ap_sta,
				काष्ठा iwl_wowlan_config_cmd *cmd)
अणु
	पूर्णांक i;

	/*
	 * For QoS counters, we store the one to use next, so subtract 0x10
	 * since the uCode will add 0x10 *beक्रमe* using the value जबतक we
	 * increment after using the value (i.e. store the next value to use).
	 */
	क्रम (i = 0; i < IWL_MAX_TID_COUNT; i++) अणु
		u16 seq = mvm_ap_sta->tid_data[i].seq_number;
		seq -= 0x10;
		cmd->qos_seq[i] = cpu_to_le16(seq);
	पूर्ण
पूर्ण

पूर्णांक iwl_mvm_send_proto_offload(काष्ठा iwl_mvm *mvm,
			       काष्ठा ieee80211_vअगर *vअगर,
			       bool disable_offloading,
			       bool offload_ns,
			       u32 cmd_flags)
अणु
	जोड़ अणु
		काष्ठा iwl_proto_offload_cmd_v1 v1;
		काष्ठा iwl_proto_offload_cmd_v2 v2;
		काष्ठा iwl_proto_offload_cmd_v3_small v3s;
		काष्ठा iwl_proto_offload_cmd_v3_large v3l;
	पूर्ण cmd = अणुपूर्ण;
	काष्ठा iwl_host_cmd hcmd = अणु
		.id = PROT_OFFLOAD_CONFIG_CMD,
		.flags = cmd_flags,
		.data[0] = &cmd,
		.dataflags[0] = IWL_HCMD_DFL_DUP,
	पूर्ण;
	काष्ठा iwl_proto_offload_cmd_common *common;
	u32 enabled = 0, size;
	u32 capa_flags = mvm->fw->ucode_capa.flags;
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	पूर्णांक i;
	/*
	 * Skip tentative address when ns offload is enabled to aव्योम
	 * violating RFC4862.
	 * Keep tentative address when ns offload is disabled so the NS packets
	 * will not be filtered out and will wake up the host.
	 */
	bool skip_tentative = offload_ns;

	अगर (capa_flags & IWL_UCODE_TLV_FLAGS_NEW_NSOFFL_SMALL ||
	    capa_flags & IWL_UCODE_TLV_FLAGS_NEW_NSOFFL_LARGE) अणु
		काष्ठा iwl_ns_config *nsc;
		काष्ठा iwl_targ_addr *addrs;
		पूर्णांक n_nsc, n_addrs;
		पूर्णांक c;
		पूर्णांक num_skipped = 0;

		अगर (capa_flags & IWL_UCODE_TLV_FLAGS_NEW_NSOFFL_SMALL) अणु
			nsc = cmd.v3s.ns_config;
			n_nsc = IWL_PROTO_OFFLOAD_NUM_NS_CONFIG_V3S;
			addrs = cmd.v3s.targ_addrs;
			n_addrs = IWL_PROTO_OFFLOAD_NUM_IPV6_ADDRS_V3S;
		पूर्ण अन्यथा अणु
			nsc = cmd.v3l.ns_config;
			n_nsc = IWL_PROTO_OFFLOAD_NUM_NS_CONFIG_V3L;
			addrs = cmd.v3l.targ_addrs;
			n_addrs = IWL_PROTO_OFFLOAD_NUM_IPV6_ADDRS_V3L;
		पूर्ण

		/*
		 * For each address we have (and that will fit) fill a target
		 * address काष्ठा and combine क्रम NS offload काष्ठाs with the
		 * solicited node addresses.
		 */
		क्रम (i = 0, c = 0;
		     i < mvmvअगर->num_target_ipv6_addrs &&
		     i < n_addrs && c < n_nsc; i++) अणु
			काष्ठा in6_addr solicited_addr;
			पूर्णांक j;

			अगर (skip_tentative &&
			    test_bit(i, mvmvअगर->tentative_addrs)) अणु
				num_skipped++;
				जारी;
			पूर्ण

			addrconf_addr_solict_mult(&mvmvअगर->target_ipv6_addrs[i],
						  &solicited_addr);
			क्रम (j = 0; j < c; j++)
				अगर (ipv6_addr_cmp(&nsc[j].dest_ipv6_addr,
						  &solicited_addr) == 0)
					अवरोध;
			अगर (j == c)
				c++;
			addrs[i].addr = mvmvअगर->target_ipv6_addrs[i];
			addrs[i].config_num = cpu_to_le32(j);
			nsc[j].dest_ipv6_addr = solicited_addr;
			स_नकल(nsc[j].target_mac_addr, vअगर->addr, ETH_ALEN);
		पूर्ण

		अगर (mvmvअगर->num_target_ipv6_addrs - num_skipped)
			enabled |= IWL_D3_PROTO_IPV6_VALID;

		अगर (capa_flags & IWL_UCODE_TLV_FLAGS_NEW_NSOFFL_SMALL)
			cmd.v3s.num_valid_ipv6_addrs =
				cpu_to_le32(i - num_skipped);
		अन्यथा
			cmd.v3l.num_valid_ipv6_addrs =
				cpu_to_le32(i - num_skipped);
	पूर्ण अन्यथा अगर (capa_flags & IWL_UCODE_TLV_FLAGS_D3_6_IPV6_ADDRS) अणु
		bool found = false;

		BUILD_BUG_ON(माप(cmd.v2.target_ipv6_addr[0]) !=
			     माप(mvmvअगर->target_ipv6_addrs[0]));

		क्रम (i = 0; i < min(mvmvअगर->num_target_ipv6_addrs,
				    IWL_PROTO_OFFLOAD_NUM_IPV6_ADDRS_V2); i++) अणु
			अगर (skip_tentative &&
			    test_bit(i, mvmvअगर->tentative_addrs))
				जारी;

			स_नकल(cmd.v2.target_ipv6_addr[i],
			       &mvmvअगर->target_ipv6_addrs[i],
			       माप(cmd.v2.target_ipv6_addr[i]));

			found = true;
		पूर्ण
		अगर (found) अणु
			enabled |= IWL_D3_PROTO_IPV6_VALID;
			स_नकल(cmd.v2.ndp_mac_addr, vअगर->addr, ETH_ALEN);
		पूर्ण
	पूर्ण अन्यथा अणु
		bool found = false;
		BUILD_BUG_ON(माप(cmd.v1.target_ipv6_addr[0]) !=
			     माप(mvmvअगर->target_ipv6_addrs[0]));

		क्रम (i = 0; i < min(mvmvअगर->num_target_ipv6_addrs,
				    IWL_PROTO_OFFLOAD_NUM_IPV6_ADDRS_V1); i++) अणु
			अगर (skip_tentative &&
			    test_bit(i, mvmvअगर->tentative_addrs))
				जारी;

			स_नकल(cmd.v1.target_ipv6_addr[i],
			       &mvmvअगर->target_ipv6_addrs[i],
			       माप(cmd.v1.target_ipv6_addr[i]));

			found = true;
		पूर्ण

		अगर (found) अणु
			enabled |= IWL_D3_PROTO_IPV6_VALID;
			स_नकल(cmd.v1.ndp_mac_addr, vअगर->addr, ETH_ALEN);
		पूर्ण
	पूर्ण

	अगर (offload_ns && (enabled & IWL_D3_PROTO_IPV6_VALID))
		enabled |= IWL_D3_PROTO_OFFLOAD_NS;
#पूर्ण_अगर
	अगर (capa_flags & IWL_UCODE_TLV_FLAGS_NEW_NSOFFL_SMALL) अणु
		common = &cmd.v3s.common;
		size = माप(cmd.v3s);
	पूर्ण अन्यथा अगर (capa_flags & IWL_UCODE_TLV_FLAGS_NEW_NSOFFL_LARGE) अणु
		common = &cmd.v3l.common;
		size = माप(cmd.v3l);
	पूर्ण अन्यथा अगर (capa_flags & IWL_UCODE_TLV_FLAGS_D3_6_IPV6_ADDRS) अणु
		common = &cmd.v2.common;
		size = माप(cmd.v2);
	पूर्ण अन्यथा अणु
		common = &cmd.v1.common;
		size = माप(cmd.v1);
	पूर्ण

	अगर (vअगर->bss_conf.arp_addr_cnt) अणु
		enabled |= IWL_D3_PROTO_OFFLOAD_ARP | IWL_D3_PROTO_IPV4_VALID;
		common->host_ipv4_addr = vअगर->bss_conf.arp_addr_list[0];
		स_नकल(common->arp_mac_addr, vअगर->addr, ETH_ALEN);
	पूर्ण

	अगर (!disable_offloading)
		common->enabled = cpu_to_le32(enabled);

	hcmd.len[0] = size;
	वापस iwl_mvm_send_cmd(mvm, &hcmd);
पूर्ण
