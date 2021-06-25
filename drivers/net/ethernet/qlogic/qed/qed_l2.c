<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/param.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/माला.स>
#समावेश <linux/workqueue.h>
#समावेश <linux/bitops.h>
#समावेश <linux/bug.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश "qed.h"
#समावेश <linux/qed/qed_chain.h>
#समावेश "qed_cxt.h"
#समावेश "qed_dcbx.h"
#समावेश "qed_dev_api.h"
#समावेश <linux/qed/qed_eth_अगर.h>
#समावेश "qed_hsi.h"
#समावेश "qed_hw.h"
#समावेश "qed_int.h"
#समावेश "qed_l2.h"
#समावेश "qed_mcp.h"
#समावेश "qed_ptp.h"
#समावेश "qed_reg_addr.h"
#समावेश "qed_sp.h"
#समावेश "qed_sriov.h"


#घोषणा QED_MAX_SGES_NUM 16
#घोषणा CRC32_POLY 0x1edc6f41

काष्ठा qed_l2_info अणु
	u32 queues;
	अचिन्हित दीर्घ **pp_qid_usage;

	/* The lock is meant to synchronize access to the qid usage */
	काष्ठा mutex lock;
पूर्ण;

पूर्णांक qed_l2_alloc(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_l2_info *p_l2_info;
	अचिन्हित दीर्घ **pp_qids;
	u32 i;

	अगर (!QED_IS_L2_PERSONALITY(p_hwfn))
		वापस 0;

	p_l2_info = kzalloc(माप(*p_l2_info), GFP_KERNEL);
	अगर (!p_l2_info)
		वापस -ENOMEM;
	p_hwfn->p_l2_info = p_l2_info;

	अगर (IS_PF(p_hwfn->cdev)) अणु
		p_l2_info->queues = RESC_NUM(p_hwfn, QED_L2_QUEUE);
	पूर्ण अन्यथा अणु
		u8 rx = 0, tx = 0;

		qed_vf_get_num_rxqs(p_hwfn, &rx);
		qed_vf_get_num_txqs(p_hwfn, &tx);

		p_l2_info->queues = max_t(u8, rx, tx);
	पूर्ण

	pp_qids = kसुस्मृति(p_l2_info->queues, माप(अचिन्हित दीर्घ *),
			  GFP_KERNEL);
	अगर (!pp_qids)
		वापस -ENOMEM;
	p_l2_info->pp_qid_usage = pp_qids;

	क्रम (i = 0; i < p_l2_info->queues; i++) अणु
		pp_qids[i] = kzalloc(MAX_QUEUES_PER_QZONE / 8, GFP_KERNEL);
		अगर (!pp_qids[i])
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

व्योम qed_l2_setup(काष्ठा qed_hwfn *p_hwfn)
अणु
	अगर (!QED_IS_L2_PERSONALITY(p_hwfn))
		वापस;

	mutex_init(&p_hwfn->p_l2_info->lock);
पूर्ण

व्योम qed_l2_मुक्त(काष्ठा qed_hwfn *p_hwfn)
अणु
	u32 i;

	अगर (!QED_IS_L2_PERSONALITY(p_hwfn))
		वापस;

	अगर (!p_hwfn->p_l2_info)
		वापस;

	अगर (!p_hwfn->p_l2_info->pp_qid_usage)
		जाओ out_l2_info;

	/* Free until hit first uninitialized entry */
	क्रम (i = 0; i < p_hwfn->p_l2_info->queues; i++) अणु
		अगर (!p_hwfn->p_l2_info->pp_qid_usage[i])
			अवरोध;
		kमुक्त(p_hwfn->p_l2_info->pp_qid_usage[i]);
	पूर्ण

	kमुक्त(p_hwfn->p_l2_info->pp_qid_usage);

out_l2_info:
	kमुक्त(p_hwfn->p_l2_info);
	p_hwfn->p_l2_info = शून्य;
पूर्ण

अटल bool qed_eth_queue_qid_usage_add(काष्ठा qed_hwfn *p_hwfn,
					काष्ठा qed_queue_cid *p_cid)
अणु
	काष्ठा qed_l2_info *p_l2_info = p_hwfn->p_l2_info;
	u16 queue_id = p_cid->rel.queue_id;
	bool b_rc = true;
	u8 first;

	mutex_lock(&p_l2_info->lock);

	अगर (queue_id >= p_l2_info->queues) अणु
		DP_NOTICE(p_hwfn,
			  "Requested to increase usage for qzone %04x out of %08x\n",
			  queue_id, p_l2_info->queues);
		b_rc = false;
		जाओ out;
	पूर्ण

	first = (u8)find_first_zero_bit(p_l2_info->pp_qid_usage[queue_id],
					MAX_QUEUES_PER_QZONE);
	अगर (first >= MAX_QUEUES_PER_QZONE) अणु
		b_rc = false;
		जाओ out;
	पूर्ण

	__set_bit(first, p_l2_info->pp_qid_usage[queue_id]);
	p_cid->qid_usage_idx = first;

out:
	mutex_unlock(&p_l2_info->lock);
	वापस b_rc;
पूर्ण

अटल व्योम qed_eth_queue_qid_usage_del(काष्ठा qed_hwfn *p_hwfn,
					काष्ठा qed_queue_cid *p_cid)
अणु
	mutex_lock(&p_hwfn->p_l2_info->lock);

	clear_bit(p_cid->qid_usage_idx,
		  p_hwfn->p_l2_info->pp_qid_usage[p_cid->rel.queue_id]);

	mutex_unlock(&p_hwfn->p_l2_info->lock);
पूर्ण

व्योम qed_eth_queue_cid_release(काष्ठा qed_hwfn *p_hwfn,
			       काष्ठा qed_queue_cid *p_cid)
अणु
	bool b_legacy_vf = !!(p_cid->vf_legacy & QED_QCID_LEGACY_VF_CID);

	अगर (IS_PF(p_hwfn->cdev) && !b_legacy_vf)
		_qed_cxt_release_cid(p_hwfn, p_cid->cid, p_cid->vfid);

	/* For PF's VFs we मुख्यtain the index inside queue-zone in IOV */
	अगर (p_cid->vfid == QED_QUEUE_CID_SELF)
		qed_eth_queue_qid_usage_del(p_hwfn, p_cid);

	vमुक्त(p_cid);
पूर्ण

/* The पूर्णांकernal is only meant to be directly called by PFs initializeing CIDs
 * क्रम their VFs.
 */
अटल काष्ठा qed_queue_cid *
_qed_eth_queue_to_cid(काष्ठा qed_hwfn *p_hwfn,
		      u16 opaque_fid,
		      u32 cid,
		      काष्ठा qed_queue_start_common_params *p_params,
		      bool b_is_rx,
		      काष्ठा qed_queue_cid_vf_params *p_vf_params)
अणु
	काष्ठा qed_queue_cid *p_cid;
	पूर्णांक rc;

	p_cid = vzalloc(माप(*p_cid));
	अगर (!p_cid)
		वापस शून्य;

	p_cid->opaque_fid = opaque_fid;
	p_cid->cid = cid;
	p_cid->p_owner = p_hwfn;

	/* Fill in parameters */
	p_cid->rel.vport_id = p_params->vport_id;
	p_cid->rel.queue_id = p_params->queue_id;
	p_cid->rel.stats_id = p_params->stats_id;
	p_cid->sb_igu_id = p_params->p_sb->igu_sb_id;
	p_cid->b_is_rx = b_is_rx;
	p_cid->sb_idx = p_params->sb_idx;

	/* Fill-in bits related to VFs' queues अगर inक्रमmation was provided */
	अगर (p_vf_params) अणु
		p_cid->vfid = p_vf_params->vfid;
		p_cid->vf_qid = p_vf_params->vf_qid;
		p_cid->vf_legacy = p_vf_params->vf_legacy;
	पूर्ण अन्यथा अणु
		p_cid->vfid = QED_QUEUE_CID_SELF;
	पूर्ण

	/* Don't try calculating the असलolute indices क्रम VFs */
	अगर (IS_VF(p_hwfn->cdev)) अणु
		p_cid->असल = p_cid->rel;
		जाओ out;
	पूर्ण

	/* Calculate the engine-असलolute indices of the resources.
	 * This would guarantee they're valid later on.
	 * In some हालs [SBs] we alपढ़ोy have the right values.
	 */
	rc = qed_fw_vport(p_hwfn, p_cid->rel.vport_id, &p_cid->असल.vport_id);
	अगर (rc)
		जाओ fail;

	rc = qed_fw_l2_queue(p_hwfn, p_cid->rel.queue_id, &p_cid->असल.queue_id);
	अगर (rc)
		जाओ fail;

	/* In हाल of a PF configuring its VF's queues, the stats-id is alपढ़ोy
	 * असलolute [since there's a single index that's suitable per-VF].
	 */
	अगर (p_cid->vfid == QED_QUEUE_CID_SELF) अणु
		rc = qed_fw_vport(p_hwfn, p_cid->rel.stats_id,
				  &p_cid->असल.stats_id);
		अगर (rc)
			जाओ fail;
	पूर्ण अन्यथा अणु
		p_cid->असल.stats_id = p_cid->rel.stats_id;
	पूर्ण

out:
	/* VF-images have provided the qid_usage_idx on their own.
	 * Otherwise, we need to allocate a unique one.
	 */
	अगर (!p_vf_params) अणु
		अगर (!qed_eth_queue_qid_usage_add(p_hwfn, p_cid))
			जाओ fail;
	पूर्ण अन्यथा अणु
		p_cid->qid_usage_idx = p_vf_params->qid_usage_idx;
	पूर्ण

	DP_VERBOSE(p_hwfn,
		   QED_MSG_SP,
		   "opaque_fid: %04x CID %08x vport %02x [%02x] qzone %04x.%02x [%04x] stats %02x [%02x] SB %04x PI %02x\n",
		   p_cid->opaque_fid,
		   p_cid->cid,
		   p_cid->rel.vport_id,
		   p_cid->असल.vport_id,
		   p_cid->rel.queue_id,
		   p_cid->qid_usage_idx,
		   p_cid->असल.queue_id,
		   p_cid->rel.stats_id,
		   p_cid->असल.stats_id, p_cid->sb_igu_id, p_cid->sb_idx);

	वापस p_cid;

fail:
	vमुक्त(p_cid);
	वापस शून्य;
पूर्ण

काष्ठा qed_queue_cid *
qed_eth_queue_to_cid(काष्ठा qed_hwfn *p_hwfn,
		     u16 opaque_fid,
		     काष्ठा qed_queue_start_common_params *p_params,
		     bool b_is_rx,
		     काष्ठा qed_queue_cid_vf_params *p_vf_params)
अणु
	काष्ठा qed_queue_cid *p_cid;
	u8 vfid = QED_CXT_PF_CID;
	bool b_legacy_vf = false;
	u32 cid = 0;

	/* In हाल of legacy VFs, The CID can be derived from the additional
	 * VF parameters - the VF assumes queue X uses CID X, so we can simply
	 * use the vf_qid क्रम this purpose as well.
	 */
	अगर (p_vf_params) अणु
		vfid = p_vf_params->vfid;

		अगर (p_vf_params->vf_legacy & QED_QCID_LEGACY_VF_CID) अणु
			b_legacy_vf = true;
			cid = p_vf_params->vf_qid;
		पूर्ण
	पूर्ण

	/* Get a unique firmware CID क्रम this queue, in हाल it's a PF.
	 * VF's don't need a CID as the queue configuration will be करोne
	 * by PF.
	 */
	अगर (IS_PF(p_hwfn->cdev) && !b_legacy_vf) अणु
		अगर (_qed_cxt_acquire_cid(p_hwfn, PROTOCOLID_ETH,
					 &cid, vfid)) अणु
			DP_NOTICE(p_hwfn, "Failed to acquire cid\n");
			वापस शून्य;
		पूर्ण
	पूर्ण

	p_cid = _qed_eth_queue_to_cid(p_hwfn, opaque_fid, cid,
				      p_params, b_is_rx, p_vf_params);
	अगर (!p_cid && IS_PF(p_hwfn->cdev) && !b_legacy_vf)
		_qed_cxt_release_cid(p_hwfn, cid, vfid);

	वापस p_cid;
पूर्ण

अटल काष्ठा qed_queue_cid *
qed_eth_queue_to_cid_pf(काष्ठा qed_hwfn *p_hwfn,
			u16 opaque_fid,
			bool b_is_rx,
			काष्ठा qed_queue_start_common_params *p_params)
अणु
	वापस qed_eth_queue_to_cid(p_hwfn, opaque_fid, p_params, b_is_rx,
				    शून्य);
पूर्ण

पूर्णांक qed_sp_eth_vport_start(काष्ठा qed_hwfn *p_hwfn,
			   काष्ठा qed_sp_vport_start_params *p_params)
अणु
	काष्ठा vport_start_ramrod_data *p_ramrod = शून्य;
	काष्ठा eth_vport_tpa_param *tpa_param;
	काष्ठा qed_spq_entry *p_ent =  शून्य;
	काष्ठा qed_sp_init_data init_data;
	u16 min_size, rx_mode = 0;
	u8 असल_vport_id = 0;
	पूर्णांक rc;

	rc = qed_fw_vport(p_hwfn, p_params->vport_id, &असल_vport_id);
	अगर (rc)
		वापस rc;

	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_params->opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 ETH_RAMROD_VPORT_START,
				 PROTOCOLID_ETH, &init_data);
	अगर (rc)
		वापस rc;

	p_ramrod		= &p_ent->ramrod.vport_start;
	p_ramrod->vport_id	= असल_vport_id;

	p_ramrod->mtu			= cpu_to_le16(p_params->mtu);
	p_ramrod->handle_ptp_pkts	= p_params->handle_ptp_pkts;
	p_ramrod->inner_vlan_removal_en	= p_params->हटाओ_inner_vlan;
	p_ramrod->drop_ttl0_en		= p_params->drop_ttl0;
	p_ramrod->untagged		= p_params->only_untagged;

	SET_FIELD(rx_mode, ETH_VPORT_RX_MODE_UCAST_DROP_ALL, 1);
	SET_FIELD(rx_mode, ETH_VPORT_RX_MODE_MCAST_DROP_ALL, 1);

	p_ramrod->rx_mode.state = cpu_to_le16(rx_mode);

	/* TPA related fields */
	tpa_param = &p_ramrod->tpa_param;
	स_रखो(tpa_param, 0, माप(*tpa_param));

	tpa_param->max_buff_num = p_params->max_buffers_per_cqe;

	चयन (p_params->tpa_mode) अणु
	हाल QED_TPA_MODE_GRO:
		min_size = p_params->mtu / 2;

		tpa_param->tpa_max_aggs_num = ETH_TPA_MAX_AGGS_NUM;
		tpa_param->tpa_max_size = cpu_to_le16(U16_MAX);
		tpa_param->tpa_min_माप_प्रकारo_cont = cpu_to_le16(min_size);
		tpa_param->tpa_min_माप_प्रकारo_start = cpu_to_le16(min_size);
		tpa_param->tpa_ipv4_en_flg = 1;
		tpa_param->tpa_ipv6_en_flg = 1;
		tpa_param->tpa_pkt_split_flg = 1;
		tpa_param->tpa_gro_consistent_flg = 1;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	p_ramrod->tx_चयनing_en = p_params->tx_चयनing;

	p_ramrod->ctl_frame_mac_check_en = !!p_params->check_mac;
	p_ramrod->ctl_frame_ethtype_check_en = !!p_params->check_ethtype;

	/* Software Function ID in hwfn (PFs are 0 - 15, VFs are 16 - 135) */
	p_ramrod->sw_fid = qed_concrete_to_sw_fid(p_hwfn->cdev,
						  p_params->concrete_fid);

	वापस qed_spq_post(p_hwfn, p_ent, शून्य);
पूर्ण

अटल पूर्णांक qed_sp_vport_start(काष्ठा qed_hwfn *p_hwfn,
			      काष्ठा qed_sp_vport_start_params *p_params)
अणु
	अगर (IS_VF(p_hwfn->cdev)) अणु
		वापस qed_vf_pf_vport_start(p_hwfn, p_params->vport_id,
					     p_params->mtu,
					     p_params->हटाओ_inner_vlan,
					     p_params->tpa_mode,
					     p_params->max_buffers_per_cqe,
					     p_params->only_untagged);
	पूर्ण

	वापस qed_sp_eth_vport_start(p_hwfn, p_params);
पूर्ण

अटल पूर्णांक
qed_sp_vport_update_rss(काष्ठा qed_hwfn *p_hwfn,
			काष्ठा vport_update_ramrod_data *p_ramrod,
			काष्ठा qed_rss_params *p_rss)
अणु
	काष्ठा eth_vport_rss_config *p_config;
	u16 capabilities = 0;
	पूर्णांक i, table_size;
	पूर्णांक rc = 0;

	अगर (!p_rss) अणु
		p_ramrod->common.update_rss_flg = 0;
		वापस rc;
	पूर्ण
	p_config = &p_ramrod->rss_config;

	BUILD_BUG_ON(QED_RSS_IND_TABLE_SIZE != ETH_RSS_IND_TABLE_ENTRIES_NUM);

	rc = qed_fw_rss_eng(p_hwfn, p_rss->rss_eng_id, &p_config->rss_id);
	अगर (rc)
		वापस rc;

	p_ramrod->common.update_rss_flg = p_rss->update_rss_config;
	p_config->update_rss_capabilities = p_rss->update_rss_capabilities;
	p_config->update_rss_ind_table = p_rss->update_rss_ind_table;
	p_config->update_rss_key = p_rss->update_rss_key;

	p_config->rss_mode = p_rss->rss_enable ?
			     ETH_VPORT_RSS_MODE_REGULAR :
			     ETH_VPORT_RSS_MODE_DISABLED;

	SET_FIELD(capabilities,
		  ETH_VPORT_RSS_CONFIG_IPV4_CAPABILITY,
		  !!(p_rss->rss_caps & QED_RSS_IPV4));
	SET_FIELD(capabilities,
		  ETH_VPORT_RSS_CONFIG_IPV6_CAPABILITY,
		  !!(p_rss->rss_caps & QED_RSS_IPV6));
	SET_FIELD(capabilities,
		  ETH_VPORT_RSS_CONFIG_IPV4_TCP_CAPABILITY,
		  !!(p_rss->rss_caps & QED_RSS_IPV4_TCP));
	SET_FIELD(capabilities,
		  ETH_VPORT_RSS_CONFIG_IPV6_TCP_CAPABILITY,
		  !!(p_rss->rss_caps & QED_RSS_IPV6_TCP));
	SET_FIELD(capabilities,
		  ETH_VPORT_RSS_CONFIG_IPV4_UDP_CAPABILITY,
		  !!(p_rss->rss_caps & QED_RSS_IPV4_UDP));
	SET_FIELD(capabilities,
		  ETH_VPORT_RSS_CONFIG_IPV6_UDP_CAPABILITY,
		  !!(p_rss->rss_caps & QED_RSS_IPV6_UDP));
	p_config->tbl_size = p_rss->rss_table_size_log;

	p_config->capabilities = cpu_to_le16(capabilities);

	DP_VERBOSE(p_hwfn, NETIF_MSG_IFUP,
		   "update rss flag %d, rss_mode = %d, update_caps = %d, capabilities = %d, update_ind = %d, update_rss_key = %d\n",
		   p_ramrod->common.update_rss_flg,
		   p_config->rss_mode,
		   p_config->update_rss_capabilities,
		   p_config->capabilities,
		   p_config->update_rss_ind_table, p_config->update_rss_key);

	table_size = min_t(पूर्णांक, QED_RSS_IND_TABLE_SIZE,
			   1 << p_config->tbl_size);
	क्रम (i = 0; i < table_size; i++) अणु
		काष्ठा qed_queue_cid *p_queue = p_rss->rss_ind_table[i];

		अगर (!p_queue)
			वापस -EINVAL;

		p_config->indirection_table[i] =
		    cpu_to_le16(p_queue->असल.queue_id);
	पूर्ण

	DP_VERBOSE(p_hwfn, NETIF_MSG_IFUP,
		   "Configured RSS indirection table [%d entries]:\n",
		   table_size);
	क्रम (i = 0; i < QED_RSS_IND_TABLE_SIZE; i += 0x10) अणु
		DP_VERBOSE(p_hwfn,
			   NETIF_MSG_IFUP,
			   "%04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x\n",
			   le16_to_cpu(p_config->indirection_table[i]),
			   le16_to_cpu(p_config->indirection_table[i + 1]),
			   le16_to_cpu(p_config->indirection_table[i + 2]),
			   le16_to_cpu(p_config->indirection_table[i + 3]),
			   le16_to_cpu(p_config->indirection_table[i + 4]),
			   le16_to_cpu(p_config->indirection_table[i + 5]),
			   le16_to_cpu(p_config->indirection_table[i + 6]),
			   le16_to_cpu(p_config->indirection_table[i + 7]),
			   le16_to_cpu(p_config->indirection_table[i + 8]),
			   le16_to_cpu(p_config->indirection_table[i + 9]),
			   le16_to_cpu(p_config->indirection_table[i + 10]),
			   le16_to_cpu(p_config->indirection_table[i + 11]),
			   le16_to_cpu(p_config->indirection_table[i + 12]),
			   le16_to_cpu(p_config->indirection_table[i + 13]),
			   le16_to_cpu(p_config->indirection_table[i + 14]),
			   le16_to_cpu(p_config->indirection_table[i + 15]));
	पूर्ण

	क्रम (i = 0; i < 10; i++)
		p_config->rss_key[i] = cpu_to_le32(p_rss->rss_key[i]);

	वापस rc;
पूर्ण

अटल व्योम
qed_sp_update_accept_mode(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा vport_update_ramrod_data *p_ramrod,
			  काष्ठा qed_filter_accept_flags accept_flags)
अणु
	p_ramrod->common.update_rx_mode_flg =
		accept_flags.update_rx_mode_config;

	p_ramrod->common.update_tx_mode_flg =
		accept_flags.update_tx_mode_config;

	/* Set Rx mode accept flags */
	अगर (p_ramrod->common.update_rx_mode_flg) अणु
		u8 accept_filter = accept_flags.rx_accept_filter;
		u16 state = 0;

		SET_FIELD(state, ETH_VPORT_RX_MODE_UCAST_DROP_ALL,
			  !(!!(accept_filter & QED_ACCEPT_UCAST_MATCHED) ||
			    !!(accept_filter & QED_ACCEPT_UCAST_UNMATCHED)));

		SET_FIELD(state, ETH_VPORT_RX_MODE_UCAST_ACCEPT_UNMATCHED,
			  !!(accept_filter & QED_ACCEPT_UCAST_UNMATCHED));

		SET_FIELD(state, ETH_VPORT_RX_MODE_MCAST_DROP_ALL,
			  !(!!(accept_filter & QED_ACCEPT_MCAST_MATCHED) ||
			    !!(accept_filter & QED_ACCEPT_MCAST_UNMATCHED)));

		SET_FIELD(state, ETH_VPORT_RX_MODE_MCAST_ACCEPT_ALL,
			  (!!(accept_filter & QED_ACCEPT_MCAST_MATCHED) &&
			   !!(accept_filter & QED_ACCEPT_MCAST_UNMATCHED)));

		SET_FIELD(state, ETH_VPORT_RX_MODE_BCAST_ACCEPT_ALL,
			  !!(accept_filter & QED_ACCEPT_BCAST));

		SET_FIELD(state, ETH_VPORT_RX_MODE_ACCEPT_ANY_VNI,
			  !!(accept_filter & QED_ACCEPT_ANY_VNI));

		p_ramrod->rx_mode.state = cpu_to_le16(state);
		DP_VERBOSE(p_hwfn, QED_MSG_SP,
			   "p_ramrod->rx_mode.state = 0x%x\n", state);
	पूर्ण

	/* Set Tx mode accept flags */
	अगर (p_ramrod->common.update_tx_mode_flg) अणु
		u8 accept_filter = accept_flags.tx_accept_filter;
		u16 state = 0;

		SET_FIELD(state, ETH_VPORT_TX_MODE_UCAST_DROP_ALL,
			  !!(accept_filter & QED_ACCEPT_NONE));

		SET_FIELD(state, ETH_VPORT_TX_MODE_MCAST_DROP_ALL,
			  !!(accept_filter & QED_ACCEPT_NONE));

		SET_FIELD(state, ETH_VPORT_TX_MODE_MCAST_ACCEPT_ALL,
			  (!!(accept_filter & QED_ACCEPT_MCAST_MATCHED) &&
			   !!(accept_filter & QED_ACCEPT_MCAST_UNMATCHED)));

		SET_FIELD(state, ETH_VPORT_TX_MODE_UCAST_ACCEPT_ALL,
			  (!!(accept_filter & QED_ACCEPT_UCAST_MATCHED) &&
			   !!(accept_filter & QED_ACCEPT_UCAST_UNMATCHED)));

		SET_FIELD(state, ETH_VPORT_TX_MODE_BCAST_ACCEPT_ALL,
			  !!(accept_filter & QED_ACCEPT_BCAST));

		p_ramrod->tx_mode.state = cpu_to_le16(state);
		DP_VERBOSE(p_hwfn, QED_MSG_SP,
			   "p_ramrod->tx_mode.state = 0x%x\n", state);
	पूर्ण
पूर्ण

अटल व्योम
qed_sp_vport_update_sge_tpa(काष्ठा qed_hwfn *p_hwfn,
			    काष्ठा vport_update_ramrod_data *p_ramrod,
			    स्थिर काष्ठा qed_sge_tpa_params *param)
अणु
	काष्ठा eth_vport_tpa_param *tpa;

	अगर (!param) अणु
		p_ramrod->common.update_tpa_param_flg = 0;
		p_ramrod->common.update_tpa_en_flg = 0;
		p_ramrod->common.update_tpa_param_flg = 0;
		वापस;
	पूर्ण

	p_ramrod->common.update_tpa_en_flg = param->update_tpa_en_flg;
	tpa = &p_ramrod->tpa_param;
	tpa->tpa_ipv4_en_flg = param->tpa_ipv4_en_flg;
	tpa->tpa_ipv6_en_flg = param->tpa_ipv6_en_flg;
	tpa->tpa_ipv4_tunn_en_flg = param->tpa_ipv4_tunn_en_flg;
	tpa->tpa_ipv6_tunn_en_flg = param->tpa_ipv6_tunn_en_flg;

	p_ramrod->common.update_tpa_param_flg = param->update_tpa_param_flg;
	tpa->max_buff_num = param->max_buffers_per_cqe;
	tpa->tpa_pkt_split_flg = param->tpa_pkt_split_flg;
	tpa->tpa_hdr_data_split_flg = param->tpa_hdr_data_split_flg;
	tpa->tpa_gro_consistent_flg = param->tpa_gro_consistent_flg;
	tpa->tpa_max_aggs_num = param->tpa_max_aggs_num;
	tpa->tpa_max_size = cpu_to_le16(param->tpa_max_size);
	tpa->tpa_min_माप_प्रकारo_start = cpu_to_le16(param->tpa_min_माप_प्रकारo_start);
	tpa->tpa_min_माप_प्रकारo_cont = cpu_to_le16(param->tpa_min_माप_प्रकारo_cont);
पूर्ण

अटल व्योम
qed_sp_update_mcast_bin(काष्ठा qed_hwfn *p_hwfn,
			काष्ठा vport_update_ramrod_data *p_ramrod,
			काष्ठा qed_sp_vport_update_params *p_params)
अणु
	पूर्णांक i;

	स_रखो(&p_ramrod->approx_mcast.bins, 0,
	       माप(p_ramrod->approx_mcast.bins));

	अगर (!p_params->update_approx_mcast_flg)
		वापस;

	p_ramrod->common.update_approx_mcast_flg = 1;
	क्रम (i = 0; i < ETH_MULTICAST_MAC_BINS_IN_REGS; i++) अणु
		u32 *p_bins = p_params->bins;

		p_ramrod->approx_mcast.bins[i] = cpu_to_le32(p_bins[i]);
	पूर्ण
पूर्ण

पूर्णांक qed_sp_vport_update(काष्ठा qed_hwfn *p_hwfn,
			काष्ठा qed_sp_vport_update_params *p_params,
			क्रमागत spq_mode comp_mode,
			काष्ठा qed_spq_comp_cb *p_comp_data)
अणु
	काष्ठा qed_rss_params *p_rss_params = p_params->rss_params;
	काष्ठा vport_update_ramrod_data_cmn *p_cmn;
	काष्ठा qed_sp_init_data init_data;
	काष्ठा vport_update_ramrod_data *p_ramrod = शून्य;
	काष्ठा qed_spq_entry *p_ent = शून्य;
	u8 असल_vport_id = 0, val;
	पूर्णांक rc = -EINVAL;

	अगर (IS_VF(p_hwfn->cdev)) अणु
		rc = qed_vf_pf_vport_update(p_hwfn, p_params);
		वापस rc;
	पूर्ण

	rc = qed_fw_vport(p_hwfn, p_params->vport_id, &असल_vport_id);
	अगर (rc)
		वापस rc;

	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_params->opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_data;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 ETH_RAMROD_VPORT_UPDATE,
				 PROTOCOLID_ETH, &init_data);
	अगर (rc)
		वापस rc;

	/* Copy input params to ramrod according to FW काष्ठा */
	p_ramrod = &p_ent->ramrod.vport_update;
	p_cmn = &p_ramrod->common;

	p_cmn->vport_id = असल_vport_id;
	p_cmn->rx_active_flg = p_params->vport_active_rx_flg;
	p_cmn->update_rx_active_flg = p_params->update_vport_active_rx_flg;
	p_cmn->tx_active_flg = p_params->vport_active_tx_flg;
	p_cmn->update_tx_active_flg = p_params->update_vport_active_tx_flg;
	p_cmn->accept_any_vlan = p_params->accept_any_vlan;
	val = p_params->update_accept_any_vlan_flg;
	p_cmn->update_accept_any_vlan_flg = val;

	p_cmn->inner_vlan_removal_en = p_params->inner_vlan_removal_flg;
	val = p_params->update_inner_vlan_removal_flg;
	p_cmn->update_inner_vlan_removal_en_flg = val;

	p_cmn->शेष_vlan_en = p_params->शेष_vlan_enable_flg;
	val = p_params->update_शेष_vlan_enable_flg;
	p_cmn->update_शेष_vlan_en_flg = val;

	p_cmn->शेष_vlan = cpu_to_le16(p_params->शेष_vlan);
	p_cmn->update_शेष_vlan_flg = p_params->update_शेष_vlan_flg;

	p_cmn->silent_vlan_removal_en = p_params->silent_vlan_removal_flg;

	p_ramrod->common.tx_चयनing_en = p_params->tx_चयनing_flg;
	p_cmn->update_tx_चयनing_en_flg = p_params->update_tx_चयनing_flg;

	p_cmn->anti_spoofing_en = p_params->anti_spoofing_en;
	val = p_params->update_anti_spoofing_en_flg;
	p_ramrod->common.update_anti_spoofing_en_flg = val;

	rc = qed_sp_vport_update_rss(p_hwfn, p_ramrod, p_rss_params);
	अगर (rc) अणु
		qed_sp_destroy_request(p_hwfn, p_ent);
		वापस rc;
	पूर्ण

	अगर (p_params->update_ctl_frame_check) अणु
		p_cmn->ctl_frame_mac_check_en = p_params->mac_chk_en;
		p_cmn->ctl_frame_ethtype_check_en = p_params->ethtype_chk_en;
	पूर्ण

	/* Update mcast bins क्रम VFs, PF करोesn't use this functionality */
	qed_sp_update_mcast_bin(p_hwfn, p_ramrod, p_params);

	qed_sp_update_accept_mode(p_hwfn, p_ramrod, p_params->accept_flags);
	qed_sp_vport_update_sge_tpa(p_hwfn, p_ramrod, p_params->sge_tpa_params);
	वापस qed_spq_post(p_hwfn, p_ent, शून्य);
पूर्ण

पूर्णांक qed_sp_vport_stop(काष्ठा qed_hwfn *p_hwfn, u16 opaque_fid, u8 vport_id)
अणु
	काष्ठा vport_stop_ramrod_data *p_ramrod;
	काष्ठा qed_sp_init_data init_data;
	काष्ठा qed_spq_entry *p_ent;
	u8 असल_vport_id = 0;
	पूर्णांक rc;

	अगर (IS_VF(p_hwfn->cdev))
		वापस qed_vf_pf_vport_stop(p_hwfn);

	rc = qed_fw_vport(p_hwfn, vport_id, &असल_vport_id);
	अगर (rc)
		वापस rc;

	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 ETH_RAMROD_VPORT_STOP,
				 PROTOCOLID_ETH, &init_data);
	अगर (rc)
		वापस rc;

	p_ramrod = &p_ent->ramrod.vport_stop;
	p_ramrod->vport_id = असल_vport_id;

	वापस qed_spq_post(p_hwfn, p_ent, शून्य);
पूर्ण

अटल पूर्णांक
qed_vf_pf_accept_flags(काष्ठा qed_hwfn *p_hwfn,
		       काष्ठा qed_filter_accept_flags *p_accept_flags)
अणु
	काष्ठा qed_sp_vport_update_params s_params;

	स_रखो(&s_params, 0, माप(s_params));
	स_नकल(&s_params.accept_flags, p_accept_flags,
	       माप(काष्ठा qed_filter_accept_flags));

	वापस qed_vf_pf_vport_update(p_hwfn, &s_params);
पूर्ण

अटल पूर्णांक qed_filter_accept_cmd(काष्ठा qed_dev *cdev,
				 u8 vport,
				 काष्ठा qed_filter_accept_flags accept_flags,
				 u8 update_accept_any_vlan,
				 u8 accept_any_vlan,
				 क्रमागत spq_mode comp_mode,
				 काष्ठा qed_spq_comp_cb *p_comp_data)
अणु
	काष्ठा qed_sp_vport_update_params vport_update_params;
	पूर्णांक i, rc;

	/* Prepare and send the vport rx_mode change */
	स_रखो(&vport_update_params, 0, माप(vport_update_params));
	vport_update_params.vport_id = vport;
	vport_update_params.accept_flags = accept_flags;
	vport_update_params.update_accept_any_vlan_flg = update_accept_any_vlan;
	vport_update_params.accept_any_vlan = accept_any_vlan;

	क्रम_each_hwfn(cdev, i) अणु
		काष्ठा qed_hwfn *p_hwfn = &cdev->hwfns[i];

		vport_update_params.opaque_fid = p_hwfn->hw_info.opaque_fid;

		अगर (IS_VF(cdev)) अणु
			rc = qed_vf_pf_accept_flags(p_hwfn, &accept_flags);
			अगर (rc)
				वापस rc;
			जारी;
		पूर्ण

		rc = qed_sp_vport_update(p_hwfn, &vport_update_params,
					 comp_mode, p_comp_data);
		अगर (rc) अणु
			DP_ERR(cdev, "Update rx_mode failed %d\n", rc);
			वापस rc;
		पूर्ण

		DP_VERBOSE(p_hwfn, QED_MSG_SP,
			   "Accept filter configured, flags = [Rx]%x [Tx]%x\n",
			   accept_flags.rx_accept_filter,
			   accept_flags.tx_accept_filter);
		अगर (update_accept_any_vlan)
			DP_VERBOSE(p_hwfn, QED_MSG_SP,
				   "accept_any_vlan=%d configured\n",
				   accept_any_vlan);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक qed_eth_rxq_start_ramrod(काष्ठा qed_hwfn *p_hwfn,
			     काष्ठा qed_queue_cid *p_cid,
			     u16 bd_max_bytes,
			     dma_addr_t bd_chain_phys_addr,
			     dma_addr_t cqe_pbl_addr, u16 cqe_pbl_size)
अणु
	काष्ठा rx_queue_start_ramrod_data *p_ramrod = शून्य;
	काष्ठा qed_spq_entry *p_ent = शून्य;
	काष्ठा qed_sp_init_data init_data;
	पूर्णांक rc = -EINVAL;

	DP_VERBOSE(p_hwfn, QED_MSG_SP,
		   "opaque_fid=0x%x, cid=0x%x, rx_qzone=0x%x, vport_id=0x%x, sb_id=0x%x\n",
		   p_cid->opaque_fid, p_cid->cid,
		   p_cid->असल.queue_id, p_cid->असल.vport_id, p_cid->sb_igu_id);

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = p_cid->cid;
	init_data.opaque_fid = p_cid->opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 ETH_RAMROD_RX_QUEUE_START,
				 PROTOCOLID_ETH, &init_data);
	अगर (rc)
		वापस rc;

	p_ramrod = &p_ent->ramrod.rx_queue_start;

	p_ramrod->sb_id = cpu_to_le16(p_cid->sb_igu_id);
	p_ramrod->sb_index = p_cid->sb_idx;
	p_ramrod->vport_id = p_cid->असल.vport_id;
	p_ramrod->stats_counter_id = p_cid->असल.stats_id;
	p_ramrod->rx_queue_id = cpu_to_le16(p_cid->असल.queue_id);
	p_ramrod->complete_cqe_flg = 0;
	p_ramrod->complete_event_flg = 1;

	p_ramrod->bd_max_bytes = cpu_to_le16(bd_max_bytes);
	DMA_REGPAIR_LE(p_ramrod->bd_base, bd_chain_phys_addr);

	p_ramrod->num_of_pbl_pages = cpu_to_le16(cqe_pbl_size);
	DMA_REGPAIR_LE(p_ramrod->cqe_pbl_addr, cqe_pbl_addr);

	अगर (p_cid->vfid != QED_QUEUE_CID_SELF) अणु
		bool b_legacy_vf = !!(p_cid->vf_legacy &
				      QED_QCID_LEGACY_VF_RX_PROD);

		p_ramrod->vf_rx_prod_index = p_cid->vf_qid;
		DP_VERBOSE(p_hwfn, QED_MSG_SP,
			   "Queue%s is meant for VF rxq[%02x]\n",
			   b_legacy_vf ? " [legacy]" : "", p_cid->vf_qid);
		p_ramrod->vf_rx_prod_use_zone_a = b_legacy_vf;
	पूर्ण

	वापस qed_spq_post(p_hwfn, p_ent, शून्य);
पूर्ण

अटल पूर्णांक
qed_eth_pf_rx_queue_start(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_queue_cid *p_cid,
			  u16 bd_max_bytes,
			  dma_addr_t bd_chain_phys_addr,
			  dma_addr_t cqe_pbl_addr,
			  u16 cqe_pbl_size, व्योम __iomem **pp_prod)
अणु
	u32 init_prod_val = 0;

	*pp_prod = p_hwfn->regview +
		   GTT_BAR0_MAP_REG_MSDM_RAM +
		    MSTORM_ETH_PF_PRODS_OFFSET(p_cid->असल.queue_id);

	/* Init the rcq, rx bd and rx sge (अगर valid) producers to 0 */
	__पूर्णांकernal_ram_wr(p_hwfn, *pp_prod, माप(u32),
			  (u32 *)(&init_prod_val));

	वापस qed_eth_rxq_start_ramrod(p_hwfn, p_cid,
					bd_max_bytes,
					bd_chain_phys_addr,
					cqe_pbl_addr, cqe_pbl_size);
पूर्ण

अटल पूर्णांक
qed_eth_rx_queue_start(काष्ठा qed_hwfn *p_hwfn,
		       u16 opaque_fid,
		       काष्ठा qed_queue_start_common_params *p_params,
		       u16 bd_max_bytes,
		       dma_addr_t bd_chain_phys_addr,
		       dma_addr_t cqe_pbl_addr,
		       u16 cqe_pbl_size,
		       काष्ठा qed_rxq_start_ret_params *p_ret_params)
अणु
	काष्ठा qed_queue_cid *p_cid;
	पूर्णांक rc;

	/* Allocate a CID क्रम the queue */
	p_cid = qed_eth_queue_to_cid_pf(p_hwfn, opaque_fid, true, p_params);
	अगर (!p_cid)
		वापस -ENOMEM;

	अगर (IS_PF(p_hwfn->cdev)) अणु
		rc = qed_eth_pf_rx_queue_start(p_hwfn, p_cid,
					       bd_max_bytes,
					       bd_chain_phys_addr,
					       cqe_pbl_addr, cqe_pbl_size,
					       &p_ret_params->p_prod);
	पूर्ण अन्यथा अणु
		rc = qed_vf_pf_rxq_start(p_hwfn, p_cid,
					 bd_max_bytes,
					 bd_chain_phys_addr,
					 cqe_pbl_addr,
					 cqe_pbl_size, &p_ret_params->p_prod);
	पूर्ण

	/* Provide the caller with a reference to as handler */
	अगर (rc)
		qed_eth_queue_cid_release(p_hwfn, p_cid);
	अन्यथा
		p_ret_params->p_handle = (व्योम *)p_cid;

	वापस rc;
पूर्ण

पूर्णांक qed_sp_eth_rx_queues_update(काष्ठा qed_hwfn *p_hwfn,
				व्योम **pp_rxq_handles,
				u8 num_rxqs,
				u8 complete_cqe_flg,
				u8 complete_event_flg,
				क्रमागत spq_mode comp_mode,
				काष्ठा qed_spq_comp_cb *p_comp_data)
अणु
	काष्ठा rx_queue_update_ramrod_data *p_ramrod = शून्य;
	काष्ठा qed_spq_entry *p_ent = शून्य;
	काष्ठा qed_sp_init_data init_data;
	काष्ठा qed_queue_cid *p_cid;
	पूर्णांक rc = -EINVAL;
	u8 i;

	स_रखो(&init_data, 0, माप(init_data));
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_data;

	क्रम (i = 0; i < num_rxqs; i++) अणु
		p_cid = ((काष्ठा qed_queue_cid **)pp_rxq_handles)[i];

		/* Get SPQ entry */
		init_data.cid = p_cid->cid;
		init_data.opaque_fid = p_cid->opaque_fid;

		rc = qed_sp_init_request(p_hwfn, &p_ent,
					 ETH_RAMROD_RX_QUEUE_UPDATE,
					 PROTOCOLID_ETH, &init_data);
		अगर (rc)
			वापस rc;

		p_ramrod = &p_ent->ramrod.rx_queue_update;
		p_ramrod->vport_id = p_cid->असल.vport_id;

		p_ramrod->rx_queue_id = cpu_to_le16(p_cid->असल.queue_id);
		p_ramrod->complete_cqe_flg = complete_cqe_flg;
		p_ramrod->complete_event_flg = complete_event_flg;

		rc = qed_spq_post(p_hwfn, p_ent, शून्य);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक
qed_eth_pf_rx_queue_stop(काष्ठा qed_hwfn *p_hwfn,
			 काष्ठा qed_queue_cid *p_cid,
			 bool b_eq_completion_only, bool b_cqe_completion)
अणु
	काष्ठा rx_queue_stop_ramrod_data *p_ramrod = शून्य;
	काष्ठा qed_spq_entry *p_ent = शून्य;
	काष्ठा qed_sp_init_data init_data;
	पूर्णांक rc;

	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = p_cid->cid;
	init_data.opaque_fid = p_cid->opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 ETH_RAMROD_RX_QUEUE_STOP,
				 PROTOCOLID_ETH, &init_data);
	अगर (rc)
		वापस rc;

	p_ramrod = &p_ent->ramrod.rx_queue_stop;
	p_ramrod->vport_id = p_cid->असल.vport_id;
	p_ramrod->rx_queue_id = cpu_to_le16(p_cid->असल.queue_id);

	/* Cleaning the queue requires the completion to arrive there.
	 * In addition, VFs require the answer to come as eqe to PF.
	 */
	p_ramrod->complete_cqe_flg = ((p_cid->vfid == QED_QUEUE_CID_SELF) &&
				      !b_eq_completion_only) ||
				     b_cqe_completion;
	p_ramrod->complete_event_flg = (p_cid->vfid != QED_QUEUE_CID_SELF) ||
				       b_eq_completion_only;

	वापस qed_spq_post(p_hwfn, p_ent, शून्य);
पूर्ण

पूर्णांक qed_eth_rx_queue_stop(काष्ठा qed_hwfn *p_hwfn,
			  व्योम *p_rxq,
			  bool eq_completion_only, bool cqe_completion)
अणु
	काष्ठा qed_queue_cid *p_cid = (काष्ठा qed_queue_cid *)p_rxq;
	पूर्णांक rc = -EINVAL;

	अगर (IS_PF(p_hwfn->cdev))
		rc = qed_eth_pf_rx_queue_stop(p_hwfn, p_cid,
					      eq_completion_only,
					      cqe_completion);
	अन्यथा
		rc = qed_vf_pf_rxq_stop(p_hwfn, p_cid, cqe_completion);

	अगर (!rc)
		qed_eth_queue_cid_release(p_hwfn, p_cid);
	वापस rc;
पूर्ण

पूर्णांक
qed_eth_txq_start_ramrod(काष्ठा qed_hwfn *p_hwfn,
			 काष्ठा qed_queue_cid *p_cid,
			 dma_addr_t pbl_addr, u16 pbl_size, u16 pq_id)
अणु
	काष्ठा tx_queue_start_ramrod_data *p_ramrod = शून्य;
	काष्ठा qed_spq_entry *p_ent = शून्य;
	काष्ठा qed_sp_init_data init_data;
	पूर्णांक rc = -EINVAL;

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = p_cid->cid;
	init_data.opaque_fid = p_cid->opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 ETH_RAMROD_TX_QUEUE_START,
				 PROTOCOLID_ETH, &init_data);
	अगर (rc)
		वापस rc;

	p_ramrod = &p_ent->ramrod.tx_queue_start;
	p_ramrod->vport_id = p_cid->असल.vport_id;

	p_ramrod->sb_id = cpu_to_le16(p_cid->sb_igu_id);
	p_ramrod->sb_index = p_cid->sb_idx;
	p_ramrod->stats_counter_id = p_cid->असल.stats_id;

	p_ramrod->queue_zone_id = cpu_to_le16(p_cid->असल.queue_id);
	p_ramrod->same_as_last_id = cpu_to_le16(p_cid->असल.queue_id);

	p_ramrod->pbl_size = cpu_to_le16(pbl_size);
	DMA_REGPAIR_LE(p_ramrod->pbl_base_addr, pbl_addr);

	p_ramrod->qm_pq_id = cpu_to_le16(pq_id);

	वापस qed_spq_post(p_hwfn, p_ent, शून्य);
पूर्ण

अटल पूर्णांक
qed_eth_pf_tx_queue_start(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_queue_cid *p_cid,
			  u8 tc,
			  dma_addr_t pbl_addr,
			  u16 pbl_size, व्योम __iomem **pp_करोorbell)
अणु
	पूर्णांक rc;


	rc = qed_eth_txq_start_ramrod(p_hwfn, p_cid,
				      pbl_addr, pbl_size,
				      qed_get_cm_pq_idx_mcos(p_hwfn, tc));
	अगर (rc)
		वापस rc;

	/* Provide the caller with the necessary वापस values */
	*pp_करोorbell = p_hwfn->करोorbells +
		       qed_db_addr(p_cid->cid, DQ_DEMS_LEGACY);

	वापस 0;
पूर्ण

अटल पूर्णांक
qed_eth_tx_queue_start(काष्ठा qed_hwfn *p_hwfn,
		       u16 opaque_fid,
		       काष्ठा qed_queue_start_common_params *p_params,
		       u8 tc,
		       dma_addr_t pbl_addr,
		       u16 pbl_size,
		       काष्ठा qed_txq_start_ret_params *p_ret_params)
अणु
	काष्ठा qed_queue_cid *p_cid;
	पूर्णांक rc;

	p_cid = qed_eth_queue_to_cid_pf(p_hwfn, opaque_fid, false, p_params);
	अगर (!p_cid)
		वापस -EINVAL;

	अगर (IS_PF(p_hwfn->cdev))
		rc = qed_eth_pf_tx_queue_start(p_hwfn, p_cid, tc,
					       pbl_addr, pbl_size,
					       &p_ret_params->p_करोorbell);
	अन्यथा
		rc = qed_vf_pf_txq_start(p_hwfn, p_cid,
					 pbl_addr, pbl_size,
					 &p_ret_params->p_करोorbell);

	अगर (rc)
		qed_eth_queue_cid_release(p_hwfn, p_cid);
	अन्यथा
		p_ret_params->p_handle = (व्योम *)p_cid;

	वापस rc;
पूर्ण

अटल पूर्णांक
qed_eth_pf_tx_queue_stop(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_queue_cid *p_cid)
अणु
	काष्ठा qed_spq_entry *p_ent = शून्य;
	काष्ठा qed_sp_init_data init_data;
	पूर्णांक rc;

	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = p_cid->cid;
	init_data.opaque_fid = p_cid->opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 ETH_RAMROD_TX_QUEUE_STOP,
				 PROTOCOLID_ETH, &init_data);
	अगर (rc)
		वापस rc;

	वापस qed_spq_post(p_hwfn, p_ent, शून्य);
पूर्ण

पूर्णांक qed_eth_tx_queue_stop(काष्ठा qed_hwfn *p_hwfn, व्योम *p_handle)
अणु
	काष्ठा qed_queue_cid *p_cid = (काष्ठा qed_queue_cid *)p_handle;
	पूर्णांक rc;

	अगर (IS_PF(p_hwfn->cdev))
		rc = qed_eth_pf_tx_queue_stop(p_hwfn, p_cid);
	अन्यथा
		rc = qed_vf_pf_txq_stop(p_hwfn, p_cid);

	अगर (!rc)
		qed_eth_queue_cid_release(p_hwfn, p_cid);
	वापस rc;
पूर्ण

अटल क्रमागत eth_filter_action qed_filter_action(क्रमागत qed_filter_opcode opcode)
अणु
	क्रमागत eth_filter_action action = MAX_ETH_FILTER_ACTION;

	चयन (opcode) अणु
	हाल QED_FILTER_ADD:
		action = ETH_FILTER_ACTION_ADD;
		अवरोध;
	हाल QED_FILTER_REMOVE:
		action = ETH_FILTER_ACTION_REMOVE;
		अवरोध;
	हाल QED_FILTER_FLUSH:
		action = ETH_FILTER_ACTION_REMOVE_ALL;
		अवरोध;
	शेष:
		action = MAX_ETH_FILTER_ACTION;
	पूर्ण

	वापस action;
पूर्ण

अटल पूर्णांक
qed_filter_ucast_common(काष्ठा qed_hwfn *p_hwfn,
			u16 opaque_fid,
			काष्ठा qed_filter_ucast *p_filter_cmd,
			काष्ठा vport_filter_update_ramrod_data **pp_ramrod,
			काष्ठा qed_spq_entry **pp_ent,
			क्रमागत spq_mode comp_mode,
			काष्ठा qed_spq_comp_cb *p_comp_data)
अणु
	u8 vport_to_add_to = 0, vport_to_हटाओ_from = 0;
	काष्ठा vport_filter_update_ramrod_data *p_ramrod;
	काष्ठा eth_filter_cmd *p_first_filter;
	काष्ठा eth_filter_cmd *p_second_filter;
	काष्ठा qed_sp_init_data init_data;
	क्रमागत eth_filter_action action;
	पूर्णांक rc;

	rc = qed_fw_vport(p_hwfn, p_filter_cmd->vport_to_हटाओ_from,
			  &vport_to_हटाओ_from);
	अगर (rc)
		वापस rc;

	rc = qed_fw_vport(p_hwfn, p_filter_cmd->vport_to_add_to,
			  &vport_to_add_to);
	अगर (rc)
		वापस rc;

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_data;

	rc = qed_sp_init_request(p_hwfn, pp_ent,
				 ETH_RAMROD_FILTERS_UPDATE,
				 PROTOCOLID_ETH, &init_data);
	अगर (rc)
		वापस rc;

	*pp_ramrod = &(*pp_ent)->ramrod.vport_filter_update;
	p_ramrod = *pp_ramrod;
	p_ramrod->filter_cmd_hdr.rx = p_filter_cmd->is_rx_filter ? 1 : 0;
	p_ramrod->filter_cmd_hdr.tx = p_filter_cmd->is_tx_filter ? 1 : 0;

	चयन (p_filter_cmd->opcode) अणु
	हाल QED_FILTER_REPLACE:
	हाल QED_FILTER_MOVE:
		p_ramrod->filter_cmd_hdr.cmd_cnt = 2; अवरोध;
	शेष:
		p_ramrod->filter_cmd_hdr.cmd_cnt = 1; अवरोध;
	पूर्ण

	p_first_filter	= &p_ramrod->filter_cmds[0];
	p_second_filter = &p_ramrod->filter_cmds[1];

	चयन (p_filter_cmd->type) अणु
	हाल QED_FILTER_MAC:
		p_first_filter->type = ETH_FILTER_TYPE_MAC; अवरोध;
	हाल QED_FILTER_VLAN:
		p_first_filter->type = ETH_FILTER_TYPE_VLAN; अवरोध;
	हाल QED_FILTER_MAC_VLAN:
		p_first_filter->type = ETH_FILTER_TYPE_PAIR; अवरोध;
	हाल QED_FILTER_INNER_MAC:
		p_first_filter->type = ETH_FILTER_TYPE_INNER_MAC; अवरोध;
	हाल QED_FILTER_INNER_VLAN:
		p_first_filter->type = ETH_FILTER_TYPE_INNER_VLAN; अवरोध;
	हाल QED_FILTER_INNER_PAIR:
		p_first_filter->type = ETH_FILTER_TYPE_INNER_PAIR; अवरोध;
	हाल QED_FILTER_INNER_MAC_VNI_PAIR:
		p_first_filter->type = ETH_FILTER_TYPE_INNER_MAC_VNI_PAIR;
		अवरोध;
	हाल QED_FILTER_MAC_VNI_PAIR:
		p_first_filter->type = ETH_FILTER_TYPE_MAC_VNI_PAIR; अवरोध;
	हाल QED_FILTER_VNI:
		p_first_filter->type = ETH_FILTER_TYPE_VNI; अवरोध;
	पूर्ण

	अगर ((p_first_filter->type == ETH_FILTER_TYPE_MAC) ||
	    (p_first_filter->type == ETH_FILTER_TYPE_PAIR) ||
	    (p_first_filter->type == ETH_FILTER_TYPE_INNER_MAC) ||
	    (p_first_filter->type == ETH_FILTER_TYPE_INNER_PAIR) ||
	    (p_first_filter->type == ETH_FILTER_TYPE_INNER_MAC_VNI_PAIR) ||
	    (p_first_filter->type == ETH_FILTER_TYPE_MAC_VNI_PAIR)) अणु
		qed_set_fw_mac_addr(&p_first_filter->mac_msb,
				    &p_first_filter->mac_mid,
				    &p_first_filter->mac_lsb,
				    (u8 *)p_filter_cmd->mac);
	पूर्ण

	अगर ((p_first_filter->type == ETH_FILTER_TYPE_VLAN) ||
	    (p_first_filter->type == ETH_FILTER_TYPE_PAIR) ||
	    (p_first_filter->type == ETH_FILTER_TYPE_INNER_VLAN) ||
	    (p_first_filter->type == ETH_FILTER_TYPE_INNER_PAIR))
		p_first_filter->vlan_id = cpu_to_le16(p_filter_cmd->vlan);

	अगर ((p_first_filter->type == ETH_FILTER_TYPE_INNER_MAC_VNI_PAIR) ||
	    (p_first_filter->type == ETH_FILTER_TYPE_MAC_VNI_PAIR) ||
	    (p_first_filter->type == ETH_FILTER_TYPE_VNI))
		p_first_filter->vni = cpu_to_le32(p_filter_cmd->vni);

	अगर (p_filter_cmd->opcode == QED_FILTER_MOVE) अणु
		p_second_filter->type = p_first_filter->type;
		p_second_filter->mac_msb = p_first_filter->mac_msb;
		p_second_filter->mac_mid = p_first_filter->mac_mid;
		p_second_filter->mac_lsb = p_first_filter->mac_lsb;
		p_second_filter->vlan_id = p_first_filter->vlan_id;
		p_second_filter->vni = p_first_filter->vni;

		p_first_filter->action = ETH_FILTER_ACTION_REMOVE;

		p_first_filter->vport_id = vport_to_हटाओ_from;

		p_second_filter->action = ETH_FILTER_ACTION_ADD;
		p_second_filter->vport_id = vport_to_add_to;
	पूर्ण अन्यथा अगर (p_filter_cmd->opcode == QED_FILTER_REPLACE) अणु
		p_first_filter->vport_id = vport_to_add_to;
		स_नकल(p_second_filter, p_first_filter,
		       माप(*p_second_filter));
		p_first_filter->action	= ETH_FILTER_ACTION_REMOVE_ALL;
		p_second_filter->action = ETH_FILTER_ACTION_ADD;
	पूर्ण अन्यथा अणु
		action = qed_filter_action(p_filter_cmd->opcode);

		अगर (action == MAX_ETH_FILTER_ACTION) अणु
			DP_NOTICE(p_hwfn,
				  "%d is not supported yet\n",
				  p_filter_cmd->opcode);
			qed_sp_destroy_request(p_hwfn, *pp_ent);
			वापस -EINVAL;
		पूर्ण

		p_first_filter->action = action;
		p_first_filter->vport_id = (p_filter_cmd->opcode ==
					    QED_FILTER_REMOVE) ?
					   vport_to_हटाओ_from :
					   vport_to_add_to;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक qed_sp_eth_filter_ucast(काष्ठा qed_hwfn *p_hwfn,
			    u16 opaque_fid,
			    काष्ठा qed_filter_ucast *p_filter_cmd,
			    क्रमागत spq_mode comp_mode,
			    काष्ठा qed_spq_comp_cb *p_comp_data)
अणु
	काष्ठा vport_filter_update_ramrod_data	*p_ramrod	= शून्य;
	काष्ठा qed_spq_entry			*p_ent		= शून्य;
	काष्ठा eth_filter_cmd_header		*p_header;
	पूर्णांक					rc;

	rc = qed_filter_ucast_common(p_hwfn, opaque_fid, p_filter_cmd,
				     &p_ramrod, &p_ent,
				     comp_mode, p_comp_data);
	अगर (rc) अणु
		DP_ERR(p_hwfn, "Uni. filter command failed %d\n", rc);
		वापस rc;
	पूर्ण
	p_header = &p_ramrod->filter_cmd_hdr;
	p_header->निश्चित_on_error = p_filter_cmd->निश्चित_on_error;

	rc = qed_spq_post(p_hwfn, p_ent, शून्य);
	अगर (rc) अणु
		DP_ERR(p_hwfn, "Unicast filter ADD command failed %d\n", rc);
		वापस rc;
	पूर्ण

	DP_VERBOSE(p_hwfn, QED_MSG_SP,
		   "Unicast filter configured, opcode = %s, type = %s, cmd_cnt = %d, is_rx_filter = %d, is_tx_filter = %d\n",
		   (p_filter_cmd->opcode == QED_FILTER_ADD) ? "ADD" :
		   ((p_filter_cmd->opcode == QED_FILTER_REMOVE) ?
		   "REMOVE" :
		   ((p_filter_cmd->opcode == QED_FILTER_MOVE) ?
		    "MOVE" : "REPLACE")),
		   (p_filter_cmd->type == QED_FILTER_MAC) ? "MAC" :
		   ((p_filter_cmd->type == QED_FILTER_VLAN) ?
		    "VLAN" : "MAC & VLAN"),
		   p_ramrod->filter_cmd_hdr.cmd_cnt,
		   p_filter_cmd->is_rx_filter,
		   p_filter_cmd->is_tx_filter);
	DP_VERBOSE(p_hwfn, QED_MSG_SP,
		   "vport_to_add_to = %d, vport_to_remove_from = %d, mac = %2x:%2x:%2x:%2x:%2x:%2x, vlan = %d\n",
		   p_filter_cmd->vport_to_add_to,
		   p_filter_cmd->vport_to_हटाओ_from,
		   p_filter_cmd->mac[0],
		   p_filter_cmd->mac[1],
		   p_filter_cmd->mac[2],
		   p_filter_cmd->mac[3],
		   p_filter_cmd->mac[4],
		   p_filter_cmd->mac[5],
		   p_filter_cmd->vlan);

	वापस 0;
पूर्ण

/*******************************************************************************
 * Description:
 *         Calculates crc 32 on a buffer
 *         Note: crc32_length MUST be aligned to 8
 * Return:
 ******************************************************************************/
अटल u32 qed_calc_crc32c(u8 *crc32_packet,
			   u32 crc32_length, u32 crc32_seed, u8 complement)
अणु
	u32 byte = 0, bit = 0, crc32_result = crc32_seed;
	u8 msb = 0, current_byte = 0;

	अगर ((!crc32_packet) ||
	    (crc32_length == 0) ||
	    ((crc32_length % 8) != 0))
		वापस crc32_result;
	क्रम (byte = 0; byte < crc32_length; byte++) अणु
		current_byte = crc32_packet[byte];
		क्रम (bit = 0; bit < 8; bit++) अणु
			msb = (u8)(crc32_result >> 31);
			crc32_result = crc32_result << 1;
			अगर (msb != (0x1 & (current_byte >> bit))) अणु
				crc32_result = crc32_result ^ CRC32_POLY;
				crc32_result |= 1; /*crc32_result[0] = 1;*/
			पूर्ण
		पूर्ण
	पूर्ण
	वापस crc32_result;
पूर्ण

अटल u32 qed_crc32c_le(u32 seed, u8 *mac, u32 len)
अणु
	u32 packet_buf[2] = अणु 0 पूर्ण;

	स_नकल((u8 *)(&packet_buf[0]), &mac[0], 6);
	वापस qed_calc_crc32c((u8 *)packet_buf, 8, seed, 0);
पूर्ण

u8 qed_mcast_bin_from_mac(u8 *mac)
अणु
	u32 crc = qed_crc32c_le(ETH_MULTICAST_BIN_FROM_MAC_SEED,
				mac, ETH_ALEN);

	वापस crc & 0xff;
पूर्ण

अटल पूर्णांक
qed_sp_eth_filter_mcast(काष्ठा qed_hwfn *p_hwfn,
			u16 opaque_fid,
			काष्ठा qed_filter_mcast *p_filter_cmd,
			क्रमागत spq_mode comp_mode,
			काष्ठा qed_spq_comp_cb *p_comp_data)
अणु
	काष्ठा vport_update_ramrod_data *p_ramrod = शून्य;
	u32 bins[ETH_MULTICAST_MAC_BINS_IN_REGS];
	काष्ठा qed_spq_entry *p_ent = शून्य;
	काष्ठा qed_sp_init_data init_data;
	u8 असल_vport_id = 0;
	पूर्णांक rc, i;

	अगर (p_filter_cmd->opcode == QED_FILTER_ADD)
		rc = qed_fw_vport(p_hwfn, p_filter_cmd->vport_to_add_to,
				  &असल_vport_id);
	अन्यथा
		rc = qed_fw_vport(p_hwfn, p_filter_cmd->vport_to_हटाओ_from,
				  &असल_vport_id);
	अगर (rc)
		वापस rc;

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_data;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 ETH_RAMROD_VPORT_UPDATE,
				 PROTOCOLID_ETH, &init_data);
	अगर (rc) अणु
		DP_ERR(p_hwfn, "Multi-cast command failed %d\n", rc);
		वापस rc;
	पूर्ण

	p_ramrod = &p_ent->ramrod.vport_update;
	p_ramrod->common.update_approx_mcast_flg = 1;

	/* explicitly clear out the entire vector */
	स_रखो(&p_ramrod->approx_mcast.bins, 0,
	       माप(p_ramrod->approx_mcast.bins));
	स_रखो(bins, 0, माप(bins));
	/* filter ADD op is explicit set op and it हटाओs
	 *  any existing filters क्रम the vport
	 */
	अगर (p_filter_cmd->opcode == QED_FILTER_ADD) अणु
		क्रम (i = 0; i < p_filter_cmd->num_mc_addrs; i++) अणु
			u32 bit, nbits;

			bit = qed_mcast_bin_from_mac(p_filter_cmd->mac[i]);
			nbits = माप(u32) * BITS_PER_BYTE;
			bins[bit / nbits] |= 1 << (bit % nbits);
		पूर्ण

		/* Convert to correct endianity */
		क्रम (i = 0; i < ETH_MULTICAST_MAC_BINS_IN_REGS; i++) अणु
			काष्ठा vport_update_ramrod_mcast *p_ramrod_bins;

			p_ramrod_bins = &p_ramrod->approx_mcast;
			p_ramrod_bins->bins[i] = cpu_to_le32(bins[i]);
		पूर्ण
	पूर्ण

	p_ramrod->common.vport_id = असल_vport_id;

	वापस qed_spq_post(p_hwfn, p_ent, शून्य);
पूर्ण

अटल पूर्णांक qed_filter_mcast_cmd(काष्ठा qed_dev *cdev,
				काष्ठा qed_filter_mcast *p_filter_cmd,
				क्रमागत spq_mode comp_mode,
				काष्ठा qed_spq_comp_cb *p_comp_data)
अणु
	पूर्णांक rc = 0;
	पूर्णांक i;

	/* only ADD and REMOVE operations are supported क्रम multi-cast */
	अगर ((p_filter_cmd->opcode != QED_FILTER_ADD &&
	     (p_filter_cmd->opcode != QED_FILTER_REMOVE)) ||
	    (p_filter_cmd->num_mc_addrs > QED_MAX_MC_ADDRS))
		वापस -EINVAL;

	क्रम_each_hwfn(cdev, i) अणु
		काष्ठा qed_hwfn *p_hwfn = &cdev->hwfns[i];

		u16 opaque_fid;

		अगर (IS_VF(cdev)) अणु
			qed_vf_pf_filter_mcast(p_hwfn, p_filter_cmd);
			जारी;
		पूर्ण

		opaque_fid = p_hwfn->hw_info.opaque_fid;

		rc = qed_sp_eth_filter_mcast(p_hwfn,
					     opaque_fid,
					     p_filter_cmd,
					     comp_mode, p_comp_data);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक qed_filter_ucast_cmd(काष्ठा qed_dev *cdev,
				काष्ठा qed_filter_ucast *p_filter_cmd,
				क्रमागत spq_mode comp_mode,
				काष्ठा qed_spq_comp_cb *p_comp_data)
अणु
	पूर्णांक rc = 0;
	पूर्णांक i;

	क्रम_each_hwfn(cdev, i) अणु
		काष्ठा qed_hwfn *p_hwfn = &cdev->hwfns[i];
		u16 opaque_fid;

		अगर (IS_VF(cdev)) अणु
			rc = qed_vf_pf_filter_ucast(p_hwfn, p_filter_cmd);
			जारी;
		पूर्ण

		opaque_fid = p_hwfn->hw_info.opaque_fid;

		rc = qed_sp_eth_filter_ucast(p_hwfn,
					     opaque_fid,
					     p_filter_cmd,
					     comp_mode, p_comp_data);
		अगर (rc)
			अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

/* Statistics related code */
अटल व्योम __qed_get_vport_pstats_addrlen(काष्ठा qed_hwfn *p_hwfn,
					   u32 *p_addr,
					   u32 *p_len, u16 statistics_bin)
अणु
	अगर (IS_PF(p_hwfn->cdev)) अणु
		*p_addr = BAR0_MAP_REG_PSDM_RAM +
		    PSTORM_QUEUE_STAT_OFFSET(statistics_bin);
		*p_len = माप(काष्ठा eth_pstorm_per_queue_stat);
	पूर्ण अन्यथा अणु
		काष्ठा qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
		काष्ठा pfvf_acquire_resp_tlv *p_resp = &p_iov->acquire_resp;

		*p_addr = p_resp->pfdev_info.stats_info.pstats.address;
		*p_len = p_resp->pfdev_info.stats_info.pstats.len;
	पूर्ण
पूर्ण

अटल noअंतरभूत_क्रम_stack व्योम
__qed_get_vport_pstats(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt,
		       काष्ठा qed_eth_stats *p_stats, u16 statistics_bin)
अणु
	काष्ठा eth_pstorm_per_queue_stat pstats;
	u32 pstats_addr = 0, pstats_len = 0;

	__qed_get_vport_pstats_addrlen(p_hwfn, &pstats_addr, &pstats_len,
				       statistics_bin);

	स_रखो(&pstats, 0, माप(pstats));
	qed_स_नकल_from(p_hwfn, p_ptt, &pstats, pstats_addr, pstats_len);

	p_stats->common.tx_ucast_bytes +=
	    HILO_64_REGPAIR(pstats.sent_ucast_bytes);
	p_stats->common.tx_mcast_bytes +=
	    HILO_64_REGPAIR(pstats.sent_mcast_bytes);
	p_stats->common.tx_bcast_bytes +=
	    HILO_64_REGPAIR(pstats.sent_bcast_bytes);
	p_stats->common.tx_ucast_pkts +=
	    HILO_64_REGPAIR(pstats.sent_ucast_pkts);
	p_stats->common.tx_mcast_pkts +=
	    HILO_64_REGPAIR(pstats.sent_mcast_pkts);
	p_stats->common.tx_bcast_pkts +=
	    HILO_64_REGPAIR(pstats.sent_bcast_pkts);
	p_stats->common.tx_err_drop_pkts +=
	    HILO_64_REGPAIR(pstats.error_drop_pkts);
पूर्ण

अटल noअंतरभूत_क्रम_stack व्योम
__qed_get_vport_tstats(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt,
		       काष्ठा qed_eth_stats *p_stats, u16 statistics_bin)
अणु
	काष्ठा tstorm_per_port_stat tstats;
	u32 tstats_addr, tstats_len;

	अगर (IS_PF(p_hwfn->cdev)) अणु
		tstats_addr = BAR0_MAP_REG_TSDM_RAM +
		    TSTORM_PORT_STAT_OFFSET(MFW_PORT(p_hwfn));
		tstats_len = माप(काष्ठा tstorm_per_port_stat);
	पूर्ण अन्यथा अणु
		काष्ठा qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
		काष्ठा pfvf_acquire_resp_tlv *p_resp = &p_iov->acquire_resp;

		tstats_addr = p_resp->pfdev_info.stats_info.tstats.address;
		tstats_len = p_resp->pfdev_info.stats_info.tstats.len;
	पूर्ण

	स_रखो(&tstats, 0, माप(tstats));
	qed_स_नकल_from(p_hwfn, p_ptt, &tstats, tstats_addr, tstats_len);

	p_stats->common.mftag_filter_discards +=
	    HILO_64_REGPAIR(tstats.mftag_filter_discard);
	p_stats->common.mac_filter_discards +=
	    HILO_64_REGPAIR(tstats.eth_mac_filter_discard);
	p_stats->common.gft_filter_drop +=
		HILO_64_REGPAIR(tstats.eth_gft_drop_pkt);
पूर्ण

अटल व्योम __qed_get_vport_ustats_addrlen(काष्ठा qed_hwfn *p_hwfn,
					   u32 *p_addr,
					   u32 *p_len, u16 statistics_bin)
अणु
	अगर (IS_PF(p_hwfn->cdev)) अणु
		*p_addr = BAR0_MAP_REG_USDM_RAM +
		    USTORM_QUEUE_STAT_OFFSET(statistics_bin);
		*p_len = माप(काष्ठा eth_ustorm_per_queue_stat);
	पूर्ण अन्यथा अणु
		काष्ठा qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
		काष्ठा pfvf_acquire_resp_tlv *p_resp = &p_iov->acquire_resp;

		*p_addr = p_resp->pfdev_info.stats_info.ustats.address;
		*p_len = p_resp->pfdev_info.stats_info.ustats.len;
	पूर्ण
पूर्ण

अटल noअंतरभूत_क्रम_stack
व्योम __qed_get_vport_ustats(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt,
			    काष्ठा qed_eth_stats *p_stats, u16 statistics_bin)
अणु
	काष्ठा eth_ustorm_per_queue_stat ustats;
	u32 ustats_addr = 0, ustats_len = 0;

	__qed_get_vport_ustats_addrlen(p_hwfn, &ustats_addr, &ustats_len,
				       statistics_bin);

	स_रखो(&ustats, 0, माप(ustats));
	qed_स_नकल_from(p_hwfn, p_ptt, &ustats, ustats_addr, ustats_len);

	p_stats->common.rx_ucast_bytes +=
	    HILO_64_REGPAIR(ustats.rcv_ucast_bytes);
	p_stats->common.rx_mcast_bytes +=
	    HILO_64_REGPAIR(ustats.rcv_mcast_bytes);
	p_stats->common.rx_bcast_bytes +=
	    HILO_64_REGPAIR(ustats.rcv_bcast_bytes);
	p_stats->common.rx_ucast_pkts += HILO_64_REGPAIR(ustats.rcv_ucast_pkts);
	p_stats->common.rx_mcast_pkts += HILO_64_REGPAIR(ustats.rcv_mcast_pkts);
	p_stats->common.rx_bcast_pkts += HILO_64_REGPAIR(ustats.rcv_bcast_pkts);
पूर्ण

अटल व्योम __qed_get_vport_mstats_addrlen(काष्ठा qed_hwfn *p_hwfn,
					   u32 *p_addr,
					   u32 *p_len, u16 statistics_bin)
अणु
	अगर (IS_PF(p_hwfn->cdev)) अणु
		*p_addr = BAR0_MAP_REG_MSDM_RAM +
		    MSTORM_QUEUE_STAT_OFFSET(statistics_bin);
		*p_len = माप(काष्ठा eth_mstorm_per_queue_stat);
	पूर्ण अन्यथा अणु
		काष्ठा qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
		काष्ठा pfvf_acquire_resp_tlv *p_resp = &p_iov->acquire_resp;

		*p_addr = p_resp->pfdev_info.stats_info.mstats.address;
		*p_len = p_resp->pfdev_info.stats_info.mstats.len;
	पूर्ण
पूर्ण

अटल noअंतरभूत_क्रम_stack व्योम
__qed_get_vport_mstats(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt,
		       काष्ठा qed_eth_stats *p_stats, u16 statistics_bin)
अणु
	काष्ठा eth_mstorm_per_queue_stat mstats;
	u32 mstats_addr = 0, mstats_len = 0;

	__qed_get_vport_mstats_addrlen(p_hwfn, &mstats_addr, &mstats_len,
				       statistics_bin);

	स_रखो(&mstats, 0, माप(mstats));
	qed_स_नकल_from(p_hwfn, p_ptt, &mstats, mstats_addr, mstats_len);

	p_stats->common.no_buff_discards +=
	    HILO_64_REGPAIR(mstats.no_buff_discard);
	p_stats->common.packet_too_big_discard +=
	    HILO_64_REGPAIR(mstats.packet_too_big_discard);
	p_stats->common.ttl0_discard += HILO_64_REGPAIR(mstats.ttl0_discard);
	p_stats->common.tpa_coalesced_pkts +=
	    HILO_64_REGPAIR(mstats.tpa_coalesced_pkts);
	p_stats->common.tpa_coalesced_events +=
	    HILO_64_REGPAIR(mstats.tpa_coalesced_events);
	p_stats->common.tpa_पातs_num +=
	    HILO_64_REGPAIR(mstats.tpa_पातs_num);
	p_stats->common.tpa_coalesced_bytes +=
	    HILO_64_REGPAIR(mstats.tpa_coalesced_bytes);
पूर्ण

अटल noअंतरभूत_क्रम_stack व्योम
__qed_get_vport_port_stats(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt,
			   काष्ठा qed_eth_stats *p_stats)
अणु
	काष्ठा qed_eth_stats_common *p_common = &p_stats->common;
	काष्ठा port_stats port_stats;
	पूर्णांक j;

	स_रखो(&port_stats, 0, माप(port_stats));

	qed_स_नकल_from(p_hwfn, p_ptt, &port_stats,
			p_hwfn->mcp_info->port_addr +
			दुरत्व(काष्ठा खुला_port, stats),
			माप(port_stats));

	p_common->rx_64_byte_packets += port_stats.eth.r64;
	p_common->rx_65_to_127_byte_packets += port_stats.eth.r127;
	p_common->rx_128_to_255_byte_packets += port_stats.eth.r255;
	p_common->rx_256_to_511_byte_packets += port_stats.eth.r511;
	p_common->rx_512_to_1023_byte_packets += port_stats.eth.r1023;
	p_common->rx_1024_to_1518_byte_packets += port_stats.eth.r1518;
	p_common->rx_crc_errors += port_stats.eth.rfcs;
	p_common->rx_mac_crtl_frames += port_stats.eth.rxcf;
	p_common->rx_छोड़ो_frames += port_stats.eth.rxpf;
	p_common->rx_pfc_frames += port_stats.eth.rxpp;
	p_common->rx_align_errors += port_stats.eth.raln;
	p_common->rx_carrier_errors += port_stats.eth.rfcr;
	p_common->rx_oversize_packets += port_stats.eth.rovr;
	p_common->rx_jabbers += port_stats.eth.rjbr;
	p_common->rx_undersize_packets += port_stats.eth.rund;
	p_common->rx_fragments += port_stats.eth.rfrg;
	p_common->tx_64_byte_packets += port_stats.eth.t64;
	p_common->tx_65_to_127_byte_packets += port_stats.eth.t127;
	p_common->tx_128_to_255_byte_packets += port_stats.eth.t255;
	p_common->tx_256_to_511_byte_packets += port_stats.eth.t511;
	p_common->tx_512_to_1023_byte_packets += port_stats.eth.t1023;
	p_common->tx_1024_to_1518_byte_packets += port_stats.eth.t1518;
	p_common->tx_छोड़ो_frames += port_stats.eth.txpf;
	p_common->tx_pfc_frames += port_stats.eth.txpp;
	p_common->rx_mac_bytes += port_stats.eth.rbyte;
	p_common->rx_mac_uc_packets += port_stats.eth.rxuca;
	p_common->rx_mac_mc_packets += port_stats.eth.rxmca;
	p_common->rx_mac_bc_packets += port_stats.eth.rxbca;
	p_common->rx_mac_frames_ok += port_stats.eth.rxpok;
	p_common->tx_mac_bytes += port_stats.eth.tbyte;
	p_common->tx_mac_uc_packets += port_stats.eth.txuca;
	p_common->tx_mac_mc_packets += port_stats.eth.txmca;
	p_common->tx_mac_bc_packets += port_stats.eth.txbca;
	p_common->tx_mac_ctrl_frames += port_stats.eth.txcf;
	क्रम (j = 0; j < 8; j++) अणु
		p_common->brb_truncates += port_stats.brb.brb_truncate[j];
		p_common->brb_discards += port_stats.brb.brb_discard[j];
	पूर्ण

	अगर (QED_IS_BB(p_hwfn->cdev)) अणु
		काष्ठा qed_eth_stats_bb *p_bb = &p_stats->bb;

		p_bb->rx_1519_to_1522_byte_packets +=
		    port_stats.eth.u0.bb0.r1522;
		p_bb->rx_1519_to_2047_byte_packets +=
		    port_stats.eth.u0.bb0.r2047;
		p_bb->rx_2048_to_4095_byte_packets +=
		    port_stats.eth.u0.bb0.r4095;
		p_bb->rx_4096_to_9216_byte_packets +=
		    port_stats.eth.u0.bb0.r9216;
		p_bb->rx_9217_to_16383_byte_packets +=
		    port_stats.eth.u0.bb0.r16383;
		p_bb->tx_1519_to_2047_byte_packets +=
		    port_stats.eth.u1.bb1.t2047;
		p_bb->tx_2048_to_4095_byte_packets +=
		    port_stats.eth.u1.bb1.t4095;
		p_bb->tx_4096_to_9216_byte_packets +=
		    port_stats.eth.u1.bb1.t9216;
		p_bb->tx_9217_to_16383_byte_packets +=
		    port_stats.eth.u1.bb1.t16383;
		p_bb->tx_lpi_entry_count += port_stats.eth.u2.bb2.tlpiec;
		p_bb->tx_total_collisions += port_stats.eth.u2.bb2.tncl;
	पूर्ण अन्यथा अणु
		काष्ठा qed_eth_stats_ah *p_ah = &p_stats->ah;

		p_ah->rx_1519_to_max_byte_packets +=
		    port_stats.eth.u0.ah0.r1519_to_max;
		p_ah->tx_1519_to_max_byte_packets =
		    port_stats.eth.u1.ah1.t1519_to_max;
	पूर्ण

	p_common->link_change_count = qed_rd(p_hwfn, p_ptt,
					     p_hwfn->mcp_info->port_addr +
					     दुरत्व(काष्ठा खुला_port,
						      link_change_count));
पूर्ण

अटल व्योम __qed_get_vport_stats(काष्ठा qed_hwfn *p_hwfn,
				  काष्ठा qed_ptt *p_ptt,
				  काष्ठा qed_eth_stats *stats,
				  u16 statistics_bin, bool b_get_port_stats)
अणु
	__qed_get_vport_mstats(p_hwfn, p_ptt, stats, statistics_bin);
	__qed_get_vport_ustats(p_hwfn, p_ptt, stats, statistics_bin);
	__qed_get_vport_tstats(p_hwfn, p_ptt, stats, statistics_bin);
	__qed_get_vport_pstats(p_hwfn, p_ptt, stats, statistics_bin);

	अगर (b_get_port_stats && p_hwfn->mcp_info)
		__qed_get_vport_port_stats(p_hwfn, p_ptt, stats);
पूर्ण

अटल व्योम _qed_get_vport_stats(काष्ठा qed_dev *cdev,
				 काष्ठा qed_eth_stats *stats)
अणु
	u8 fw_vport = 0;
	पूर्णांक i;

	स_रखो(stats, 0, माप(*stats));

	क्रम_each_hwfn(cdev, i) अणु
		काष्ठा qed_hwfn *p_hwfn = &cdev->hwfns[i];
		काष्ठा qed_ptt *p_ptt = IS_PF(cdev) ? qed_ptt_acquire(p_hwfn)
						    :  शून्य;
		bool b_get_port_stats;

		अगर (IS_PF(cdev)) अणु
			/* The मुख्य vport index is relative first */
			अगर (qed_fw_vport(p_hwfn, 0, &fw_vport)) अणु
				DP_ERR(p_hwfn, "No vport available!\n");
				जाओ out;
			पूर्ण
		पूर्ण

		अगर (IS_PF(cdev) && !p_ptt) अणु
			DP_ERR(p_hwfn, "Failed to acquire ptt\n");
			जारी;
		पूर्ण

		b_get_port_stats = IS_PF(cdev) && IS_LEAD_HWFN(p_hwfn);
		__qed_get_vport_stats(p_hwfn, p_ptt, stats, fw_vport,
				      b_get_port_stats);

out:
		अगर (IS_PF(cdev) && p_ptt)
			qed_ptt_release(p_hwfn, p_ptt);
	पूर्ण
पूर्ण

व्योम qed_get_vport_stats(काष्ठा qed_dev *cdev, काष्ठा qed_eth_stats *stats)
अणु
	u32 i;

	अगर (!cdev) अणु
		स_रखो(stats, 0, माप(*stats));
		वापस;
	पूर्ण

	_qed_get_vport_stats(cdev, stats);

	अगर (!cdev->reset_stats)
		वापस;

	/* Reduce the statistics baseline */
	क्रम (i = 0; i < माप(काष्ठा qed_eth_stats) / माप(u64); i++)
		((u64 *)stats)[i] -= ((u64 *)cdev->reset_stats)[i];
पूर्ण

/* zeroes V-PORT specअगरic portion of stats (Port stats reमुख्यs untouched) */
व्योम qed_reset_vport_stats(काष्ठा qed_dev *cdev)
अणु
	पूर्णांक i;

	क्रम_each_hwfn(cdev, i) अणु
		काष्ठा qed_hwfn *p_hwfn = &cdev->hwfns[i];
		काष्ठा eth_mstorm_per_queue_stat mstats;
		काष्ठा eth_ustorm_per_queue_stat ustats;
		काष्ठा eth_pstorm_per_queue_stat pstats;
		काष्ठा qed_ptt *p_ptt = IS_PF(cdev) ? qed_ptt_acquire(p_hwfn)
						    : शून्य;
		u32 addr = 0, len = 0;

		अगर (IS_PF(cdev) && !p_ptt) अणु
			DP_ERR(p_hwfn, "Failed to acquire ptt\n");
			जारी;
		पूर्ण

		स_रखो(&mstats, 0, माप(mstats));
		__qed_get_vport_mstats_addrlen(p_hwfn, &addr, &len, 0);
		qed_स_नकल_to(p_hwfn, p_ptt, addr, &mstats, len);

		स_रखो(&ustats, 0, माप(ustats));
		__qed_get_vport_ustats_addrlen(p_hwfn, &addr, &len, 0);
		qed_स_नकल_to(p_hwfn, p_ptt, addr, &ustats, len);

		स_रखो(&pstats, 0, माप(pstats));
		__qed_get_vport_pstats_addrlen(p_hwfn, &addr, &len, 0);
		qed_स_नकल_to(p_hwfn, p_ptt, addr, &pstats, len);

		अगर (IS_PF(cdev))
			qed_ptt_release(p_hwfn, p_ptt);
	पूर्ण

	/* PORT statistics are not necessarily reset, so we need to
	 * पढ़ो and create a baseline क्रम future statistics.
	 * Link change stat is मुख्यtained by MFW, वापस its value as is.
	 */
	अगर (!cdev->reset_stats) अणु
		DP_INFO(cdev, "Reset stats not allocated\n");
	पूर्ण अन्यथा अणु
		_qed_get_vport_stats(cdev, cdev->reset_stats);
		cdev->reset_stats->common.link_change_count = 0;
	पूर्ण
पूर्ण

अटल क्रमागत gft_profile_type
qed_arfs_mode_to_hsi(क्रमागत qed_filter_config_mode mode)
अणु
	अगर (mode == QED_FILTER_CONFIG_MODE_5_TUPLE)
		वापस GFT_PROखाता_TYPE_4_TUPLE;
	अगर (mode == QED_FILTER_CONFIG_MODE_IP_DEST)
		वापस GFT_PROखाता_TYPE_IP_DST_ADDR;
	अगर (mode == QED_FILTER_CONFIG_MODE_IP_SRC)
		वापस GFT_PROखाता_TYPE_IP_SRC_ADDR;
	वापस GFT_PROखाता_TYPE_L4_DST_PORT;
पूर्ण

व्योम qed_arfs_mode_configure(काष्ठा qed_hwfn *p_hwfn,
			     काष्ठा qed_ptt *p_ptt,
			     काष्ठा qed_arfs_config_params *p_cfg_params)
अणु
	अगर (test_bit(QED_MF_DISABLE_ARFS, &p_hwfn->cdev->mf_bits))
		वापस;

	अगर (p_cfg_params->mode != QED_FILTER_CONFIG_MODE_DISABLE) अणु
		qed_gft_config(p_hwfn, p_ptt, p_hwfn->rel_pf_id,
			       p_cfg_params->tcp,
			       p_cfg_params->udp,
			       p_cfg_params->ipv4,
			       p_cfg_params->ipv6,
			       qed_arfs_mode_to_hsi(p_cfg_params->mode));
		DP_VERBOSE(p_hwfn,
			   QED_MSG_SP,
			   "Configured Filtering: tcp = %s, udp = %s, ipv4 = %s, ipv6 =%s mode=%08x\n",
			   p_cfg_params->tcp ? "Enable" : "Disable",
			   p_cfg_params->udp ? "Enable" : "Disable",
			   p_cfg_params->ipv4 ? "Enable" : "Disable",
			   p_cfg_params->ipv6 ? "Enable" : "Disable",
			   (u32)p_cfg_params->mode);
	पूर्ण अन्यथा अणु
		DP_VERBOSE(p_hwfn, QED_MSG_SP, "Disabled Filtering\n");
		qed_gft_disable(p_hwfn, p_ptt, p_hwfn->rel_pf_id);
	पूर्ण
पूर्ण

पूर्णांक
qed_configure_rfs_ntuple_filter(काष्ठा qed_hwfn *p_hwfn,
				काष्ठा qed_spq_comp_cb *p_cb,
				काष्ठा qed_ntuple_filter_params *p_params)
अणु
	काष्ठा rx_update_gft_filter_data *p_ramrod = शून्य;
	काष्ठा qed_spq_entry *p_ent = शून्य;
	काष्ठा qed_sp_init_data init_data;
	u16 असल_rx_q_id = 0;
	u8 असल_vport_id = 0;
	पूर्णांक rc = -EINVAL;

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);

	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;

	अगर (p_cb) अणु
		init_data.comp_mode = QED_SPQ_MODE_CB;
		init_data.p_comp_data = p_cb;
	पूर्ण अन्यथा अणु
		init_data.comp_mode = QED_SPQ_MODE_EBLOCK;
	पूर्ण

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 ETH_RAMROD_GFT_UPDATE_FILTER,
				 PROTOCOLID_ETH, &init_data);
	अगर (rc)
		वापस rc;

	p_ramrod = &p_ent->ramrod.rx_update_gft;

	DMA_REGPAIR_LE(p_ramrod->pkt_hdr_addr, p_params->addr);
	p_ramrod->pkt_hdr_length = cpu_to_le16(p_params->length);

	अगर (p_params->b_is_drop) अणु
		p_ramrod->vport_id = cpu_to_le16(ETH_GFT_TRASHCAN_VPORT);
	पूर्ण अन्यथा अणु
		rc = qed_fw_vport(p_hwfn, p_params->vport_id, &असल_vport_id);
		अगर (rc)
			जाओ err;

		अगर (p_params->qid != QED_RFS_NTUPLE_QID_RSS) अणु
			rc = qed_fw_l2_queue(p_hwfn, p_params->qid,
					     &असल_rx_q_id);
			अगर (rc)
				जाओ err;

			p_ramrod->rx_qid_valid = 1;
			p_ramrod->rx_qid = cpu_to_le16(असल_rx_q_id);
		पूर्ण

		p_ramrod->vport_id = cpu_to_le16((u16)असल_vport_id);
	पूर्ण

	p_ramrod->flow_id_valid = 0;
	p_ramrod->flow_id = 0;
	p_ramrod->filter_action = p_params->b_is_add ? GFT_ADD_FILTER
	    : GFT_DELETE_FILTER;

	DP_VERBOSE(p_hwfn, QED_MSG_SP,
		   "V[%0x], Q[%04x] - %s filter from 0x%llx [length %04xb]\n",
		   असल_vport_id, असल_rx_q_id,
		   p_params->b_is_add ? "Adding" : "Removing",
		   (u64)p_params->addr, p_params->length);

	वापस qed_spq_post(p_hwfn, p_ent, शून्य);

err:
	qed_sp_destroy_request(p_hwfn, p_ent);
	वापस rc;
पूर्ण

पूर्णांक qed_get_rxq_coalesce(काष्ठा qed_hwfn *p_hwfn,
			 काष्ठा qed_ptt *p_ptt,
			 काष्ठा qed_queue_cid *p_cid, u16 *p_rx_coal)
अणु
	u32 coalesce, address, is_valid;
	काष्ठा cau_sb_entry sb_entry;
	u8 समयr_res;
	पूर्णांक rc;

	rc = qed_dmae_grc2host(p_hwfn, p_ptt, CAU_REG_SB_VAR_MEMORY +
			       p_cid->sb_igu_id * माप(u64),
			       (u64)(uपूर्णांकptr_t)&sb_entry, 2, शून्य);
	अगर (rc) अणु
		DP_ERR(p_hwfn, "dmae_grc2host failed %d\n", rc);
		वापस rc;
	पूर्ण

	समयr_res = GET_FIELD(le32_to_cpu(sb_entry.params),
			      CAU_SB_ENTRY_TIMER_RES0);

	address = BAR0_MAP_REG_USDM_RAM +
		  USTORM_ETH_QUEUE_ZONE_OFFSET(p_cid->असल.queue_id);
	coalesce = qed_rd(p_hwfn, p_ptt, address);

	is_valid = GET_FIELD(coalesce, COALESCING_TIMESET_VALID);
	अगर (!is_valid)
		वापस -EINVAL;

	coalesce = GET_FIELD(coalesce, COALESCING_TIMESET_TIMESET);
	*p_rx_coal = (u16)(coalesce << समयr_res);

	वापस 0;
पूर्ण

पूर्णांक qed_get_txq_coalesce(काष्ठा qed_hwfn *p_hwfn,
			 काष्ठा qed_ptt *p_ptt,
			 काष्ठा qed_queue_cid *p_cid, u16 *p_tx_coal)
अणु
	u32 coalesce, address, is_valid;
	काष्ठा cau_sb_entry sb_entry;
	u8 समयr_res;
	पूर्णांक rc;

	rc = qed_dmae_grc2host(p_hwfn, p_ptt, CAU_REG_SB_VAR_MEMORY +
			       p_cid->sb_igu_id * माप(u64),
			       (u64)(uपूर्णांकptr_t)&sb_entry, 2, शून्य);
	अगर (rc) अणु
		DP_ERR(p_hwfn, "dmae_grc2host failed %d\n", rc);
		वापस rc;
	पूर्ण

	समयr_res = GET_FIELD(le32_to_cpu(sb_entry.params),
			      CAU_SB_ENTRY_TIMER_RES1);

	address = BAR0_MAP_REG_XSDM_RAM +
		  XSTORM_ETH_QUEUE_ZONE_OFFSET(p_cid->असल.queue_id);
	coalesce = qed_rd(p_hwfn, p_ptt, address);

	is_valid = GET_FIELD(coalesce, COALESCING_TIMESET_VALID);
	अगर (!is_valid)
		वापस -EINVAL;

	coalesce = GET_FIELD(coalesce, COALESCING_TIMESET_TIMESET);
	*p_tx_coal = (u16)(coalesce << समयr_res);

	वापस 0;
पूर्ण

पूर्णांक qed_get_queue_coalesce(काष्ठा qed_hwfn *p_hwfn, u16 *p_coal, व्योम *handle)
अणु
	काष्ठा qed_queue_cid *p_cid = handle;
	काष्ठा qed_ptt *p_ptt;
	पूर्णांक rc = 0;

	अगर (IS_VF(p_hwfn->cdev)) अणु
		rc = qed_vf_pf_get_coalesce(p_hwfn, p_coal, p_cid);
		अगर (rc)
			DP_NOTICE(p_hwfn, "Unable to read queue coalescing\n");

		वापस rc;
	पूर्ण

	p_ptt = qed_ptt_acquire(p_hwfn);
	अगर (!p_ptt)
		वापस -EAGAIN;

	अगर (p_cid->b_is_rx) अणु
		rc = qed_get_rxq_coalesce(p_hwfn, p_ptt, p_cid, p_coal);
		अगर (rc)
			जाओ out;
	पूर्ण अन्यथा अणु
		rc = qed_get_txq_coalesce(p_hwfn, p_ptt, p_cid, p_coal);
		अगर (rc)
			जाओ out;
	पूर्ण

out:
	qed_ptt_release(p_hwfn, p_ptt);

	वापस rc;
पूर्ण

अटल पूर्णांक qed_fill_eth_dev_info(काष्ठा qed_dev *cdev,
				 काष्ठा qed_dev_eth_info *info)
अणु
	काष्ठा qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	पूर्णांक i;

	स_रखो(info, 0, माप(*info));

	अगर (IS_PF(cdev)) अणु
		पूर्णांक max_vf_vlan_filters = 0;
		पूर्णांक max_vf_mac_filters = 0;

		info->num_tc = p_hwfn->hw_info.num_hw_tc;

		अगर (cdev->पूर्णांक_params.out.पूर्णांक_mode == QED_INT_MODE_MSIX) अणु
			u16 num_queues = 0;

			/* Since the feature controls only queue-zones,
			 * make sure we have the contexts [rx, xdp, tcs] to
			 * match.
			 */
			क्रम_each_hwfn(cdev, i) अणु
				काष्ठा qed_hwfn *hwfn = &cdev->hwfns[i];
				u16 l2_queues = (u16)FEAT_NUM(hwfn,
							      QED_PF_L2_QUE);
				u16 cids;

				cids = hwfn->pf_params.eth_pf_params.num_cons;
				cids /= (2 + info->num_tc);
				num_queues += min_t(u16, l2_queues, cids);
			पूर्ण

			/* queues might theoretically be >256, but पूर्णांकerrupts'
			 * upper-limit guarantes that it would fit in a u8.
			 */
			अगर (cdev->पूर्णांक_params.fp_msix_cnt) अणु
				u8 irqs = cdev->पूर्णांक_params.fp_msix_cnt;

				info->num_queues = (u8)min_t(u16,
							     num_queues, irqs);
			पूर्ण
		पूर्ण अन्यथा अणु
			info->num_queues = cdev->num_hwfns;
		पूर्ण

		अगर (IS_QED_SRIOV(cdev)) अणु
			max_vf_vlan_filters = cdev->p_iov_info->total_vfs *
					      QED_ETH_VF_NUM_VLAN_FILTERS;
			max_vf_mac_filters = cdev->p_iov_info->total_vfs *
					     QED_ETH_VF_NUM_MAC_FILTERS;
		पूर्ण
		info->num_vlan_filters = RESC_NUM(QED_LEADING_HWFN(cdev),
						  QED_VLAN) -
					 max_vf_vlan_filters;
		info->num_mac_filters = RESC_NUM(QED_LEADING_HWFN(cdev),
						 QED_MAC) -
					max_vf_mac_filters;

		ether_addr_copy(info->port_mac,
				cdev->hwfns[0].hw_info.hw_mac_addr);

		info->xdp_supported = true;
	पूर्ण अन्यथा अणु
		u16 total_cids = 0;

		info->num_tc = 1;

		/* Determine queues &  XDP support */
		क्रम_each_hwfn(cdev, i) अणु
			काष्ठा qed_hwfn *p_hwfn = &cdev->hwfns[i];
			u8 queues, cids;

			qed_vf_get_num_cids(p_hwfn, &cids);
			qed_vf_get_num_rxqs(p_hwfn, &queues);
			info->num_queues += queues;
			total_cids += cids;
		पूर्ण

		/* Enable VF XDP in हाल PF guarntees sufficient connections */
		अगर (total_cids >= info->num_queues * 3)
			info->xdp_supported = true;

		qed_vf_get_num_vlan_filters(&cdev->hwfns[0],
					    (u8 *)&info->num_vlan_filters);
		qed_vf_get_num_mac_filters(&cdev->hwfns[0],
					   (u8 *)&info->num_mac_filters);
		qed_vf_get_port_mac(&cdev->hwfns[0], info->port_mac);

		info->is_legacy = !!cdev->hwfns[0].vf_iov_info->b_pre_fp_hsi;
	पूर्ण

	qed_fill_dev_info(cdev, &info->common);

	अगर (IS_VF(cdev))
		eth_zero_addr(info->common.hw_mac);

	वापस 0;
पूर्ण

अटल व्योम qed_रेजिस्टर_eth_ops(काष्ठा qed_dev *cdev,
				 काष्ठा qed_eth_cb_ops *ops, व्योम *cookie)
अणु
	cdev->protocol_ops.eth = ops;
	cdev->ops_cookie = cookie;

	/* For VF, we start bulletin पढ़ोing */
	अगर (IS_VF(cdev))
		qed_vf_start_iov_wq(cdev);
पूर्ण

अटल bool qed_check_mac(काष्ठा qed_dev *cdev, u8 *mac)
अणु
	अगर (IS_PF(cdev))
		वापस true;

	वापस qed_vf_check_mac(&cdev->hwfns[0], mac);
पूर्ण

अटल पूर्णांक qed_start_vport(काष्ठा qed_dev *cdev,
			   काष्ठा qed_start_vport_params *params)
अणु
	पूर्णांक rc, i;

	क्रम_each_hwfn(cdev, i) अणु
		काष्ठा qed_sp_vport_start_params start = अणु 0 पूर्ण;
		काष्ठा qed_hwfn *p_hwfn = &cdev->hwfns[i];

		start.tpa_mode = params->gro_enable ? QED_TPA_MODE_GRO :
							QED_TPA_MODE_NONE;
		start.हटाओ_inner_vlan = params->हटाओ_inner_vlan;
		start.only_untagged = true;	/* untagged only */
		start.drop_ttl0 = params->drop_ttl0;
		start.opaque_fid = p_hwfn->hw_info.opaque_fid;
		start.concrete_fid = p_hwfn->hw_info.concrete_fid;
		start.handle_ptp_pkts = params->handle_ptp_pkts;
		start.vport_id = params->vport_id;
		start.max_buffers_per_cqe = 16;
		start.mtu = params->mtu;

		rc = qed_sp_vport_start(p_hwfn, &start);
		अगर (rc) अणु
			DP_ERR(cdev, "Failed to start VPORT\n");
			वापस rc;
		पूर्ण

		rc = qed_hw_start_fastpath(p_hwfn);
		अगर (rc) अणु
			DP_ERR(cdev, "Failed to start VPORT fastpath\n");
			वापस rc;
		पूर्ण

		DP_VERBOSE(cdev, (QED_MSG_SPQ | NETIF_MSG_IFUP),
			   "Started V-PORT %d with MTU %d\n",
			   start.vport_id, start.mtu);
	पूर्ण

	अगर (params->clear_stats)
		qed_reset_vport_stats(cdev);

	वापस 0;
पूर्ण

अटल पूर्णांक qed_stop_vport(काष्ठा qed_dev *cdev, u8 vport_id)
अणु
	पूर्णांक rc, i;

	क्रम_each_hwfn(cdev, i) अणु
		काष्ठा qed_hwfn *p_hwfn = &cdev->hwfns[i];

		rc = qed_sp_vport_stop(p_hwfn,
				       p_hwfn->hw_info.opaque_fid, vport_id);

		अगर (rc) अणु
			DP_ERR(cdev, "Failed to stop VPORT\n");
			वापस rc;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qed_update_vport_rss(काष्ठा qed_dev *cdev,
				काष्ठा qed_update_vport_rss_params *input,
				काष्ठा qed_rss_params *rss)
अणु
	पूर्णांक i, fn;

	/* Update configuration with what's correct regardless of CMT */
	rss->update_rss_config = 1;
	rss->rss_enable = 1;
	rss->update_rss_capabilities = 1;
	rss->update_rss_ind_table = 1;
	rss->update_rss_key = 1;
	rss->rss_caps = input->rss_caps;
	स_नकल(rss->rss_key, input->rss_key, QED_RSS_KEY_SIZE * माप(u32));

	/* In regular scenario, we'd simply need to take input handlers.
	 * But in CMT, we'd have to split the handlers according to the
	 * engine they were configured on. We'd then have to understand
	 * whether RSS is really required, since 2-queues on CMT करोesn't
	 * require RSS.
	 */
	अगर (cdev->num_hwfns == 1) अणु
		स_नकल(rss->rss_ind_table,
		       input->rss_ind_table,
		       QED_RSS_IND_TABLE_SIZE * माप(व्योम *));
		rss->rss_table_size_log = 7;
		वापस 0;
	पूर्ण

	/* Start by copying the non-spcअगरic inक्रमmation to the 2nd copy */
	स_नकल(&rss[1], &rss[0], माप(काष्ठा qed_rss_params));

	/* CMT should be round-robin */
	क्रम (i = 0; i < QED_RSS_IND_TABLE_SIZE; i++) अणु
		काष्ठा qed_queue_cid *cid = input->rss_ind_table[i];
		काष्ठा qed_rss_params *t_rss;

		अगर (cid->p_owner == QED_LEADING_HWFN(cdev))
			t_rss = &rss[0];
		अन्यथा
			t_rss = &rss[1];

		t_rss->rss_ind_table[i / cdev->num_hwfns] = cid;
	पूर्ण

	/* Make sure RSS is actually required */
	क्रम_each_hwfn(cdev, fn) अणु
		क्रम (i = 1; i < QED_RSS_IND_TABLE_SIZE / cdev->num_hwfns; i++) अणु
			अगर (rss[fn].rss_ind_table[i] !=
			    rss[fn].rss_ind_table[0])
				अवरोध;
		पूर्ण
		अगर (i == QED_RSS_IND_TABLE_SIZE / cdev->num_hwfns) अणु
			DP_VERBOSE(cdev, NETIF_MSG_IFUP,
				   "CMT - 1 queue per-hwfn; Disabling RSS\n");
			वापस -EINVAL;
		पूर्ण
		rss[fn].rss_table_size_log = 6;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qed_update_vport(काष्ठा qed_dev *cdev,
			    काष्ठा qed_update_vport_params *params)
अणु
	काष्ठा qed_sp_vport_update_params sp_params;
	काष्ठा qed_rss_params *rss;
	पूर्णांक rc = 0, i;

	अगर (!cdev)
		वापस -ENODEV;

	rss = vzalloc(array_size(माप(*rss), cdev->num_hwfns));
	अगर (!rss)
		वापस -ENOMEM;

	स_रखो(&sp_params, 0, माप(sp_params));

	/* Translate protocol params पूर्णांकo sp params */
	sp_params.vport_id = params->vport_id;
	sp_params.update_vport_active_rx_flg = params->update_vport_active_flg;
	sp_params.update_vport_active_tx_flg = params->update_vport_active_flg;
	sp_params.vport_active_rx_flg = params->vport_active_flg;
	sp_params.vport_active_tx_flg = params->vport_active_flg;
	sp_params.update_tx_चयनing_flg = params->update_tx_चयनing_flg;
	sp_params.tx_चयनing_flg = params->tx_चयनing_flg;
	sp_params.accept_any_vlan = params->accept_any_vlan;
	sp_params.update_accept_any_vlan_flg =
		params->update_accept_any_vlan_flg;

	/* Prepare the RSS configuration */
	अगर (params->update_rss_flg)
		अगर (qed_update_vport_rss(cdev, &params->rss_params, rss))
			params->update_rss_flg = 0;

	क्रम_each_hwfn(cdev, i) अणु
		काष्ठा qed_hwfn *p_hwfn = &cdev->hwfns[i];

		अगर (params->update_rss_flg)
			sp_params.rss_params = &rss[i];

		sp_params.opaque_fid = p_hwfn->hw_info.opaque_fid;
		rc = qed_sp_vport_update(p_hwfn, &sp_params,
					 QED_SPQ_MODE_EBLOCK,
					 शून्य);
		अगर (rc) अणु
			DP_ERR(cdev, "Failed to update VPORT\n");
			जाओ out;
		पूर्ण

		DP_VERBOSE(cdev, (QED_MSG_SPQ | NETIF_MSG_IFUP),
			   "Updated V-PORT %d: active_flag %d [update %d]\n",
			   params->vport_id, params->vport_active_flg,
			   params->update_vport_active_flg);
	पूर्ण

out:
	vमुक्त(rss);
	वापस rc;
पूर्ण

अटल पूर्णांक qed_start_rxq(काष्ठा qed_dev *cdev,
			 u8 rss_num,
			 काष्ठा qed_queue_start_common_params *p_params,
			 u16 bd_max_bytes,
			 dma_addr_t bd_chain_phys_addr,
			 dma_addr_t cqe_pbl_addr,
			 u16 cqe_pbl_size,
			 काष्ठा qed_rxq_start_ret_params *ret_params)
अणु
	काष्ठा qed_hwfn *p_hwfn;
	पूर्णांक rc, hwfn_index;

	hwfn_index = rss_num % cdev->num_hwfns;
	p_hwfn = &cdev->hwfns[hwfn_index];

	p_params->queue_id = p_params->queue_id / cdev->num_hwfns;
	p_params->stats_id = p_params->vport_id;

	rc = qed_eth_rx_queue_start(p_hwfn,
				    p_hwfn->hw_info.opaque_fid,
				    p_params,
				    bd_max_bytes,
				    bd_chain_phys_addr,
				    cqe_pbl_addr, cqe_pbl_size, ret_params);
	अगर (rc) अणु
		DP_ERR(cdev, "Failed to start RXQ#%d\n", p_params->queue_id);
		वापस rc;
	पूर्ण

	DP_VERBOSE(cdev, (QED_MSG_SPQ | NETIF_MSG_IFUP),
		   "Started RX-Q %d [rss_num %d] on V-PORT %d and SB igu %d\n",
		   p_params->queue_id, rss_num, p_params->vport_id,
		   p_params->p_sb->igu_sb_id);

	वापस 0;
पूर्ण

अटल पूर्णांक qed_stop_rxq(काष्ठा qed_dev *cdev, u8 rss_id, व्योम *handle)
अणु
	पूर्णांक rc, hwfn_index;
	काष्ठा qed_hwfn *p_hwfn;

	hwfn_index = rss_id % cdev->num_hwfns;
	p_hwfn = &cdev->hwfns[hwfn_index];

	rc = qed_eth_rx_queue_stop(p_hwfn, handle, false, false);
	अगर (rc) अणु
		DP_ERR(cdev, "Failed to stop RXQ#%02x\n", rss_id);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qed_start_txq(काष्ठा qed_dev *cdev,
			 u8 rss_num,
			 काष्ठा qed_queue_start_common_params *p_params,
			 dma_addr_t pbl_addr,
			 u16 pbl_size,
			 काष्ठा qed_txq_start_ret_params *ret_params)
अणु
	काष्ठा qed_hwfn *p_hwfn;
	पूर्णांक rc, hwfn_index;

	hwfn_index = rss_num % cdev->num_hwfns;
	p_hwfn = &cdev->hwfns[hwfn_index];
	p_params->queue_id = p_params->queue_id / cdev->num_hwfns;
	p_params->stats_id = p_params->vport_id;

	rc = qed_eth_tx_queue_start(p_hwfn,
				    p_hwfn->hw_info.opaque_fid,
				    p_params, p_params->tc,
				    pbl_addr, pbl_size, ret_params);

	अगर (rc) अणु
		DP_ERR(cdev, "Failed to start TXQ#%d\n", p_params->queue_id);
		वापस rc;
	पूर्ण

	DP_VERBOSE(cdev, (QED_MSG_SPQ | NETIF_MSG_IFUP),
		   "Started TX-Q %d [rss_num %d] on V-PORT %d and SB igu %d\n",
		   p_params->queue_id, rss_num, p_params->vport_id,
		   p_params->p_sb->igu_sb_id);

	वापस 0;
पूर्ण

#घोषणा QED_HW_STOP_RETRY_LIMIT (10)
अटल पूर्णांक qed_fastpath_stop(काष्ठा qed_dev *cdev)
अणु
	पूर्णांक rc;

	rc = qed_hw_stop_fastpath(cdev);
	अगर (rc) अणु
		DP_ERR(cdev, "Failed to stop Fastpath\n");
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qed_stop_txq(काष्ठा qed_dev *cdev, u8 rss_id, व्योम *handle)
अणु
	काष्ठा qed_hwfn *p_hwfn;
	पूर्णांक rc, hwfn_index;

	hwfn_index = rss_id % cdev->num_hwfns;
	p_hwfn = &cdev->hwfns[hwfn_index];

	rc = qed_eth_tx_queue_stop(p_hwfn, handle);
	अगर (rc) अणु
		DP_ERR(cdev, "Failed to stop TXQ#%02x\n", rss_id);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qed_tunn_configure(काष्ठा qed_dev *cdev,
			      काष्ठा qed_tunn_params *tunn_params)
अणु
	काष्ठा qed_tunnel_info tunn_info;
	पूर्णांक i, rc;

	स_रखो(&tunn_info, 0, माप(tunn_info));
	अगर (tunn_params->update_vxlan_port) अणु
		tunn_info.vxlan_port.b_update_port = true;
		tunn_info.vxlan_port.port = tunn_params->vxlan_port;
	पूर्ण

	अगर (tunn_params->update_geneve_port) अणु
		tunn_info.geneve_port.b_update_port = true;
		tunn_info.geneve_port.port = tunn_params->geneve_port;
	पूर्ण

	क्रम_each_hwfn(cdev, i) अणु
		काष्ठा qed_hwfn *hwfn = &cdev->hwfns[i];
		काष्ठा qed_ptt *p_ptt;
		काष्ठा qed_tunnel_info *tun;

		tun = &hwfn->cdev->tunnel;
		अगर (IS_PF(cdev)) अणु
			p_ptt = qed_ptt_acquire(hwfn);
			अगर (!p_ptt)
				वापस -EAGAIN;
		पूर्ण अन्यथा अणु
			p_ptt = शून्य;
		पूर्ण

		rc = qed_sp_pf_update_tunn_cfg(hwfn, p_ptt, &tunn_info,
					       QED_SPQ_MODE_EBLOCK, शून्य);
		अगर (rc) अणु
			अगर (IS_PF(cdev))
				qed_ptt_release(hwfn, p_ptt);
			वापस rc;
		पूर्ण

		अगर (IS_PF_SRIOV(hwfn)) अणु
			u16 vxlan_port, geneve_port;
			पूर्णांक j;

			vxlan_port = tun->vxlan_port.port;
			geneve_port = tun->geneve_port.port;

			qed_क्रम_each_vf(hwfn, j) अणु
				qed_iov_bulletin_set_udp_ports(hwfn, j,
							       vxlan_port,
							       geneve_port);
			पूर्ण

			qed_schedule_iov(hwfn, QED_IOV_WQ_BULLETIN_UPDATE_FLAG);
		पूर्ण
		अगर (IS_PF(cdev))
			qed_ptt_release(hwfn, p_ptt);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qed_configure_filter_rx_mode(काष्ठा qed_dev *cdev,
					क्रमागत qed_filter_rx_mode_type type)
अणु
	काष्ठा qed_filter_accept_flags accept_flags;

	स_रखो(&accept_flags, 0, माप(accept_flags));

	accept_flags.update_rx_mode_config = 1;
	accept_flags.update_tx_mode_config = 1;
	accept_flags.rx_accept_filter = QED_ACCEPT_UCAST_MATCHED |
					QED_ACCEPT_MCAST_MATCHED |
					QED_ACCEPT_BCAST;
	accept_flags.tx_accept_filter = QED_ACCEPT_UCAST_MATCHED |
					QED_ACCEPT_MCAST_MATCHED |
					QED_ACCEPT_BCAST;

	अगर (type == QED_FILTER_RX_MODE_TYPE_PROMISC) अणु
		accept_flags.rx_accept_filter |= QED_ACCEPT_UCAST_UNMATCHED |
						 QED_ACCEPT_MCAST_UNMATCHED;
		accept_flags.tx_accept_filter |= QED_ACCEPT_UCAST_UNMATCHED |
						 QED_ACCEPT_MCAST_UNMATCHED;
	पूर्ण अन्यथा अगर (type == QED_FILTER_RX_MODE_TYPE_MULTI_PROMISC) अणु
		accept_flags.rx_accept_filter |= QED_ACCEPT_MCAST_UNMATCHED;
		accept_flags.tx_accept_filter |= QED_ACCEPT_MCAST_UNMATCHED;
	पूर्ण

	वापस qed_filter_accept_cmd(cdev, 0, accept_flags, false, false,
				     QED_SPQ_MODE_CB, शून्य);
पूर्ण

अटल पूर्णांक qed_configure_filter_ucast(काष्ठा qed_dev *cdev,
				      काष्ठा qed_filter_ucast_params *params)
अणु
	काष्ठा qed_filter_ucast ucast;

	अगर (!params->vlan_valid && !params->mac_valid) अणु
		DP_NOTICE(cdev,
			  "Tried configuring a unicast filter, but both MAC and VLAN are not set\n");
		वापस -EINVAL;
	पूर्ण

	स_रखो(&ucast, 0, माप(ucast));
	चयन (params->type) अणु
	हाल QED_FILTER_XCAST_TYPE_ADD:
		ucast.opcode = QED_FILTER_ADD;
		अवरोध;
	हाल QED_FILTER_XCAST_TYPE_DEL:
		ucast.opcode = QED_FILTER_REMOVE;
		अवरोध;
	हाल QED_FILTER_XCAST_TYPE_REPLACE:
		ucast.opcode = QED_FILTER_REPLACE;
		अवरोध;
	शेष:
		DP_NOTICE(cdev, "Unknown unicast filter type %d\n",
			  params->type);
	पूर्ण

	अगर (params->vlan_valid && params->mac_valid) अणु
		ucast.type = QED_FILTER_MAC_VLAN;
		ether_addr_copy(ucast.mac, params->mac);
		ucast.vlan = params->vlan;
	पूर्ण अन्यथा अगर (params->mac_valid) अणु
		ucast.type = QED_FILTER_MAC;
		ether_addr_copy(ucast.mac, params->mac);
	पूर्ण अन्यथा अणु
		ucast.type = QED_FILTER_VLAN;
		ucast.vlan = params->vlan;
	पूर्ण

	ucast.is_rx_filter = true;
	ucast.is_tx_filter = true;

	वापस qed_filter_ucast_cmd(cdev, &ucast, QED_SPQ_MODE_CB, शून्य);
पूर्ण

अटल पूर्णांक qed_configure_filter_mcast(काष्ठा qed_dev *cdev,
				      काष्ठा qed_filter_mcast_params *params)
अणु
	काष्ठा qed_filter_mcast mcast;
	पूर्णांक i;

	स_रखो(&mcast, 0, माप(mcast));
	चयन (params->type) अणु
	हाल QED_FILTER_XCAST_TYPE_ADD:
		mcast.opcode = QED_FILTER_ADD;
		अवरोध;
	हाल QED_FILTER_XCAST_TYPE_DEL:
		mcast.opcode = QED_FILTER_REMOVE;
		अवरोध;
	शेष:
		DP_NOTICE(cdev, "Unknown multicast filter type %d\n",
			  params->type);
	पूर्ण

	mcast.num_mc_addrs = params->num;
	क्रम (i = 0; i < mcast.num_mc_addrs; i++)
		ether_addr_copy(mcast.mac[i], params->mac[i]);

	वापस qed_filter_mcast_cmd(cdev, &mcast, QED_SPQ_MODE_CB, शून्य);
पूर्ण

अटल पूर्णांक qed_configure_filter(काष्ठा qed_dev *cdev,
				काष्ठा qed_filter_params *params)
अणु
	क्रमागत qed_filter_rx_mode_type accept_flags;

	चयन (params->type) अणु
	हाल QED_FILTER_TYPE_UCAST:
		वापस qed_configure_filter_ucast(cdev, &params->filter.ucast);
	हाल QED_FILTER_TYPE_MCAST:
		वापस qed_configure_filter_mcast(cdev, &params->filter.mcast);
	हाल QED_FILTER_TYPE_RX_MODE:
		accept_flags = params->filter.accept_flags;
		वापस qed_configure_filter_rx_mode(cdev, accept_flags);
	शेष:
		DP_NOTICE(cdev, "Unknown filter type %d\n", (पूर्णांक)params->type);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक qed_configure_arfs_searcher(काष्ठा qed_dev *cdev,
				       क्रमागत qed_filter_config_mode mode)
अणु
	काष्ठा qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_arfs_config_params arfs_config_params;

	स_रखो(&arfs_config_params, 0, माप(arfs_config_params));
	arfs_config_params.tcp = true;
	arfs_config_params.udp = true;
	arfs_config_params.ipv4 = true;
	arfs_config_params.ipv6 = true;
	arfs_config_params.mode = mode;
	qed_arfs_mode_configure(p_hwfn, p_hwfn->p_arfs_ptt,
				&arfs_config_params);
	वापस 0;
पूर्ण

अटल व्योम
qed_arfs_sp_response_handler(काष्ठा qed_hwfn *p_hwfn,
			     व्योम *cookie,
			     जोड़ event_ring_data *data, u8 fw_वापस_code)
अणु
	काष्ठा qed_common_cb_ops *op = p_hwfn->cdev->protocol_ops.common;
	व्योम *dev = p_hwfn->cdev->ops_cookie;

	op->arfs_filter_op(dev, cookie, fw_वापस_code);
पूर्ण

अटल पूर्णांक
qed_ntuple_arfs_filter_config(काष्ठा qed_dev *cdev,
			      व्योम *cookie,
			      काष्ठा qed_ntuple_filter_params *params)
अणु
	काष्ठा qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_spq_comp_cb cb;
	पूर्णांक rc = -EINVAL;

	cb.function = qed_arfs_sp_response_handler;
	cb.cookie = cookie;

	अगर (params->b_is_vf) अणु
		अगर (!qed_iov_is_valid_vfid(p_hwfn, params->vf_id, false,
					   false)) अणु
			DP_INFO(p_hwfn, "vfid 0x%02x is out of bounds\n",
				params->vf_id);
			वापस rc;
		पूर्ण

		params->vport_id = params->vf_id + 1;
		params->qid = QED_RFS_NTUPLE_QID_RSS;
	पूर्ण

	rc = qed_configure_rfs_ntuple_filter(p_hwfn, &cb, params);
	अगर (rc)
		DP_NOTICE(p_hwfn,
			  "Failed to issue a-RFS filter configuration\n");
	अन्यथा
		DP_VERBOSE(p_hwfn, NETIF_MSG_DRV,
			   "Successfully issued a-RFS filter configuration\n");

	वापस rc;
पूर्ण

अटल पूर्णांक qed_get_coalesce(काष्ठा qed_dev *cdev, u16 *coal, व्योम *handle)
अणु
	काष्ठा qed_queue_cid *p_cid = handle;
	काष्ठा qed_hwfn *p_hwfn;
	पूर्णांक rc;

	p_hwfn = p_cid->p_owner;
	rc = qed_get_queue_coalesce(p_hwfn, coal, handle);
	अगर (rc)
		DP_VERBOSE(cdev, QED_MSG_DEBUG,
			   "Unable to read queue coalescing\n");

	वापस rc;
पूर्ण

अटल पूर्णांक qed_fp_cqe_completion(काष्ठा qed_dev *dev,
				 u8 rss_id, काष्ठा eth_slow_path_rx_cqe *cqe)
अणु
	वापस qed_eth_cqe_completion(&dev->hwfns[rss_id % dev->num_hwfns],
				      cqe);
पूर्ण

अटल पूर्णांक qed_req_bulletin_update_mac(काष्ठा qed_dev *cdev, u8 *mac)
अणु
	पूर्णांक i, ret;

	अगर (IS_PF(cdev))
		वापस 0;

	क्रम_each_hwfn(cdev, i) अणु
		काष्ठा qed_hwfn *p_hwfn = &cdev->hwfns[i];

		ret = qed_vf_pf_bulletin_update_mac(p_hwfn, mac);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा qed_eth_ops qed_eth_ops_pass = अणु
	.common = &qed_common_ops_pass,
#अगर_घोषित CONFIG_QED_SRIOV
	.iov = &qed_iov_ops_pass,
#पूर्ण_अगर
#अगर_घोषित CONFIG_DCB
	.dcb = &qed_dcbnl_ops_pass,
#पूर्ण_अगर
	.ptp = &qed_ptp_ops_pass,
	.fill_dev_info = &qed_fill_eth_dev_info,
	.रेजिस्टर_ops = &qed_रेजिस्टर_eth_ops,
	.check_mac = &qed_check_mac,
	.vport_start = &qed_start_vport,
	.vport_stop = &qed_stop_vport,
	.vport_update = &qed_update_vport,
	.q_rx_start = &qed_start_rxq,
	.q_rx_stop = &qed_stop_rxq,
	.q_tx_start = &qed_start_txq,
	.q_tx_stop = &qed_stop_txq,
	.filter_config = &qed_configure_filter,
	.fastpath_stop = &qed_fastpath_stop,
	.eth_cqe_completion = &qed_fp_cqe_completion,
	.get_vport_stats = &qed_get_vport_stats,
	.tunn_config = &qed_tunn_configure,
	.ntuple_filter_config = &qed_ntuple_arfs_filter_config,
	.configure_arfs_searcher = &qed_configure_arfs_searcher,
	.get_coalesce = &qed_get_coalesce,
	.req_bulletin_update_mac = &qed_req_bulletin_update_mac,
पूर्ण;

स्थिर काष्ठा qed_eth_ops *qed_get_eth_ops(व्योम)
अणु
	वापस &qed_eth_ops_pass;
पूर्ण
EXPORT_SYMBOL(qed_get_eth_ops);

व्योम qed_put_eth_ops(व्योम)
अणु
	/* TODO - reference count क्रम module? */
पूर्ण
EXPORT_SYMBOL(qed_put_eth_ops);
