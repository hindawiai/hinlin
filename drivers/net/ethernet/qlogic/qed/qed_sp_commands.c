<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/bitops.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश "qed.h"
#समावेश <linux/qed/qed_chain.h>
#समावेश "qed_cxt.h"
#समावेश "qed_dcbx.h"
#समावेश "qed_hsi.h"
#समावेश "qed_hw.h"
#समावेश "qed_int.h"
#समावेश "qed_reg_addr.h"
#समावेश "qed_sp.h"
#समावेश "qed_sriov.h"

व्योम qed_sp_destroy_request(काष्ठा qed_hwfn *p_hwfn,
			    काष्ठा qed_spq_entry *p_ent)
अणु
	/* qed_spq_get_entry() can either get an entry from the मुक्त_pool,
	 * or, अगर no entries are left, allocate a new entry and add it to
	 * the unlimited_pending list.
	 */
	अगर (p_ent->queue == &p_hwfn->p_spq->unlimited_pending)
		kमुक्त(p_ent);
	अन्यथा
		qed_spq_वापस_entry(p_hwfn, p_ent);
पूर्ण

पूर्णांक qed_sp_init_request(काष्ठा qed_hwfn *p_hwfn,
			काष्ठा qed_spq_entry **pp_ent,
			u8 cmd, u8 protocol, काष्ठा qed_sp_init_data *p_data)
अणु
	u32 opaque_cid = p_data->opaque_fid << 16 | p_data->cid;
	काष्ठा qed_spq_entry *p_ent = शून्य;
	पूर्णांक rc;

	अगर (!pp_ent)
		वापस -ENOMEM;

	rc = qed_spq_get_entry(p_hwfn, pp_ent);

	अगर (rc)
		वापस rc;

	p_ent = *pp_ent;

	p_ent->elem.hdr.cid		= cpu_to_le32(opaque_cid);
	p_ent->elem.hdr.cmd_id		= cmd;
	p_ent->elem.hdr.protocol_id	= protocol;

	p_ent->priority		= QED_SPQ_PRIORITY_NORMAL;
	p_ent->comp_mode	= p_data->comp_mode;
	p_ent->comp_करोne.करोne	= 0;

	चयन (p_ent->comp_mode) अणु
	हाल QED_SPQ_MODE_EBLOCK:
		p_ent->comp_cb.cookie = &p_ent->comp_करोne;
		अवरोध;

	हाल QED_SPQ_MODE_BLOCK:
		अगर (!p_data->p_comp_data)
			जाओ err;

		p_ent->comp_cb.cookie = p_data->p_comp_data->cookie;
		अवरोध;

	हाल QED_SPQ_MODE_CB:
		अगर (!p_data->p_comp_data)
			p_ent->comp_cb.function = शून्य;
		अन्यथा
			p_ent->comp_cb = *p_data->p_comp_data;
		अवरोध;

	शेष:
		DP_NOTICE(p_hwfn, "Unknown SPQE completion mode %d\n",
			  p_ent->comp_mode);
		जाओ err;
	पूर्ण

	DP_VERBOSE(p_hwfn, QED_MSG_SPQ,
		   "Initialized: CID %08x cmd %02x protocol %02x data_addr %lu comp_mode [%s]\n",
		   opaque_cid, cmd, protocol,
		   (अचिन्हित दीर्घ)&p_ent->ramrod,
		   D_TRINE(p_ent->comp_mode, QED_SPQ_MODE_EBLOCK,
			   QED_SPQ_MODE_BLOCK, "MODE_EBLOCK", "MODE_BLOCK",
			   "MODE_CB"));

	स_रखो(&p_ent->ramrod, 0, माप(p_ent->ramrod));

	वापस 0;

err:
	qed_sp_destroy_request(p_hwfn, p_ent);

	वापस -EINVAL;
पूर्ण

अटल क्रमागत tunnel_clss qed_tunn_clss_to_fw_clss(u8 type)
अणु
	चयन (type) अणु
	हाल QED_TUNN_CLSS_MAC_VLAN:
		वापस TUNNEL_CLSS_MAC_VLAN;
	हाल QED_TUNN_CLSS_MAC_VNI:
		वापस TUNNEL_CLSS_MAC_VNI;
	हाल QED_TUNN_CLSS_INNER_MAC_VLAN:
		वापस TUNNEL_CLSS_INNER_MAC_VLAN;
	हाल QED_TUNN_CLSS_INNER_MAC_VNI:
		वापस TUNNEL_CLSS_INNER_MAC_VNI;
	हाल QED_TUNN_CLSS_MAC_VLAN_DUAL_STAGE:
		वापस TUNNEL_CLSS_MAC_VLAN_DUAL_STAGE;
	शेष:
		वापस TUNNEL_CLSS_MAC_VLAN;
	पूर्ण
पूर्ण

अटल व्योम
qed_set_pf_update_tunn_mode(काष्ठा qed_tunnel_info *p_tun,
			    काष्ठा qed_tunnel_info *p_src, bool b_pf_start)
अणु
	अगर (p_src->vxlan.b_update_mode || b_pf_start)
		p_tun->vxlan.b_mode_enabled = p_src->vxlan.b_mode_enabled;

	अगर (p_src->l2_gre.b_update_mode || b_pf_start)
		p_tun->l2_gre.b_mode_enabled = p_src->l2_gre.b_mode_enabled;

	अगर (p_src->ip_gre.b_update_mode || b_pf_start)
		p_tun->ip_gre.b_mode_enabled = p_src->ip_gre.b_mode_enabled;

	अगर (p_src->l2_geneve.b_update_mode || b_pf_start)
		p_tun->l2_geneve.b_mode_enabled =
		    p_src->l2_geneve.b_mode_enabled;

	अगर (p_src->ip_geneve.b_update_mode || b_pf_start)
		p_tun->ip_geneve.b_mode_enabled =
		    p_src->ip_geneve.b_mode_enabled;
पूर्ण

अटल व्योम qed_set_tunn_cls_info(काष्ठा qed_tunnel_info *p_tun,
				  काष्ठा qed_tunnel_info *p_src)
अणु
	पूर्णांक type;

	p_tun->b_update_rx_cls = p_src->b_update_rx_cls;
	p_tun->b_update_tx_cls = p_src->b_update_tx_cls;

	type = qed_tunn_clss_to_fw_clss(p_src->vxlan.tun_cls);
	p_tun->vxlan.tun_cls = type;
	type = qed_tunn_clss_to_fw_clss(p_src->l2_gre.tun_cls);
	p_tun->l2_gre.tun_cls = type;
	type = qed_tunn_clss_to_fw_clss(p_src->ip_gre.tun_cls);
	p_tun->ip_gre.tun_cls = type;
	type = qed_tunn_clss_to_fw_clss(p_src->l2_geneve.tun_cls);
	p_tun->l2_geneve.tun_cls = type;
	type = qed_tunn_clss_to_fw_clss(p_src->ip_geneve.tun_cls);
	p_tun->ip_geneve.tun_cls = type;
पूर्ण

अटल व्योम qed_set_tunn_ports(काष्ठा qed_tunnel_info *p_tun,
			       काष्ठा qed_tunnel_info *p_src)
अणु
	p_tun->geneve_port.b_update_port = p_src->geneve_port.b_update_port;
	p_tun->vxlan_port.b_update_port = p_src->vxlan_port.b_update_port;

	अगर (p_src->geneve_port.b_update_port)
		p_tun->geneve_port.port = p_src->geneve_port.port;

	अगर (p_src->vxlan_port.b_update_port)
		p_tun->vxlan_port.port = p_src->vxlan_port.port;
पूर्ण

अटल व्योम
__qed_set_ramrod_tunnel_param(u8 *p_tunn_cls,
			      काष्ठा qed_tunn_update_type *tun_type)
अणु
	*p_tunn_cls = tun_type->tun_cls;
पूर्ण

अटल व्योम
qed_set_ramrod_tunnel_param(u8 *p_tunn_cls,
			    काष्ठा qed_tunn_update_type *tun_type,
			    u8 *p_update_port,
			    __le16 *p_port,
			    काष्ठा qed_tunn_update_udp_port *p_udp_port)
अणु
	__qed_set_ramrod_tunnel_param(p_tunn_cls, tun_type);
	अगर (p_udp_port->b_update_port) अणु
		*p_update_port = 1;
		*p_port = cpu_to_le16(p_udp_port->port);
	पूर्ण
पूर्ण

अटल व्योम
qed_tunn_set_pf_update_params(काष्ठा qed_hwfn *p_hwfn,
			      काष्ठा qed_tunnel_info *p_src,
			      काष्ठा pf_update_tunnel_config *p_tunn_cfg)
अणु
	काष्ठा qed_tunnel_info *p_tun = &p_hwfn->cdev->tunnel;

	qed_set_pf_update_tunn_mode(p_tun, p_src, false);
	qed_set_tunn_cls_info(p_tun, p_src);
	qed_set_tunn_ports(p_tun, p_src);

	qed_set_ramrod_tunnel_param(&p_tunn_cfg->tunnel_clss_vxlan,
				    &p_tun->vxlan,
				    &p_tunn_cfg->set_vxlan_udp_port_flg,
				    &p_tunn_cfg->vxlan_udp_port,
				    &p_tun->vxlan_port);

	qed_set_ramrod_tunnel_param(&p_tunn_cfg->tunnel_clss_l2geneve,
				    &p_tun->l2_geneve,
				    &p_tunn_cfg->set_geneve_udp_port_flg,
				    &p_tunn_cfg->geneve_udp_port,
				    &p_tun->geneve_port);

	__qed_set_ramrod_tunnel_param(&p_tunn_cfg->tunnel_clss_ipgeneve,
				      &p_tun->ip_geneve);

	__qed_set_ramrod_tunnel_param(&p_tunn_cfg->tunnel_clss_l2gre,
				      &p_tun->l2_gre);

	__qed_set_ramrod_tunnel_param(&p_tunn_cfg->tunnel_clss_ipgre,
				      &p_tun->ip_gre);

	p_tunn_cfg->update_rx_pf_clss = p_tun->b_update_rx_cls;
पूर्ण

अटल व्योम qed_set_hw_tunn_mode(काष्ठा qed_hwfn *p_hwfn,
				 काष्ठा qed_ptt *p_ptt,
				 काष्ठा qed_tunnel_info *p_tun)
अणु
	qed_set_gre_enable(p_hwfn, p_ptt, p_tun->l2_gre.b_mode_enabled,
			   p_tun->ip_gre.b_mode_enabled);
	qed_set_vxlan_enable(p_hwfn, p_ptt, p_tun->vxlan.b_mode_enabled);

	qed_set_geneve_enable(p_hwfn, p_ptt, p_tun->l2_geneve.b_mode_enabled,
			      p_tun->ip_geneve.b_mode_enabled);
पूर्ण

अटल व्योम qed_set_hw_tunn_mode_port(काष्ठा qed_hwfn *p_hwfn,
				      काष्ठा qed_ptt *p_ptt,
				      काष्ठा qed_tunnel_info *p_tunn)
अणु
	अगर (p_tunn->vxlan_port.b_update_port)
		qed_set_vxlan_dest_port(p_hwfn, p_ptt,
					p_tunn->vxlan_port.port);

	अगर (p_tunn->geneve_port.b_update_port)
		qed_set_geneve_dest_port(p_hwfn, p_ptt,
					 p_tunn->geneve_port.port);

	qed_set_hw_tunn_mode(p_hwfn, p_ptt, p_tunn);
पूर्ण

अटल व्योम
qed_tunn_set_pf_start_params(काष्ठा qed_hwfn *p_hwfn,
			     काष्ठा qed_tunnel_info *p_src,
			     काष्ठा pf_start_tunnel_config *p_tunn_cfg)
अणु
	काष्ठा qed_tunnel_info *p_tun = &p_hwfn->cdev->tunnel;

	अगर (!p_src)
		वापस;

	qed_set_pf_update_tunn_mode(p_tun, p_src, true);
	qed_set_tunn_cls_info(p_tun, p_src);
	qed_set_tunn_ports(p_tun, p_src);

	qed_set_ramrod_tunnel_param(&p_tunn_cfg->tunnel_clss_vxlan,
				    &p_tun->vxlan,
				    &p_tunn_cfg->set_vxlan_udp_port_flg,
				    &p_tunn_cfg->vxlan_udp_port,
				    &p_tun->vxlan_port);

	qed_set_ramrod_tunnel_param(&p_tunn_cfg->tunnel_clss_l2geneve,
				    &p_tun->l2_geneve,
				    &p_tunn_cfg->set_geneve_udp_port_flg,
				    &p_tunn_cfg->geneve_udp_port,
				    &p_tun->geneve_port);

	__qed_set_ramrod_tunnel_param(&p_tunn_cfg->tunnel_clss_ipgeneve,
				      &p_tun->ip_geneve);

	__qed_set_ramrod_tunnel_param(&p_tunn_cfg->tunnel_clss_l2gre,
				      &p_tun->l2_gre);

	__qed_set_ramrod_tunnel_param(&p_tunn_cfg->tunnel_clss_ipgre,
				      &p_tun->ip_gre);
पूर्ण

पूर्णांक qed_sp_pf_start(काष्ठा qed_hwfn *p_hwfn,
		    काष्ठा qed_ptt *p_ptt,
		    काष्ठा qed_tunnel_info *p_tunn,
		    bool allow_npar_tx_चयन)
अणु
	काष्ठा outer_tag_config_काष्ठा *outer_tag_config;
	काष्ठा pf_start_ramrod_data *p_ramrod = शून्य;
	u16 sb = qed_पूर्णांक_get_sp_sb_id(p_hwfn);
	u8 sb_index = p_hwfn->p_eq->eq_sb_index;
	काष्ठा qed_spq_entry *p_ent = शून्य;
	काष्ठा qed_sp_init_data init_data;
	u8 page_cnt, i;
	पूर्णांक rc;

	/* update initial eq producer */
	qed_eq_prod_update(p_hwfn,
			   qed_chain_get_prod_idx(&p_hwfn->p_eq->chain));

	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 COMMON_RAMROD_PF_START,
				 PROTOCOLID_COMMON, &init_data);
	अगर (rc)
		वापस rc;

	p_ramrod = &p_ent->ramrod.pf_start;

	p_ramrod->event_ring_sb_id	= cpu_to_le16(sb);
	p_ramrod->event_ring_sb_index	= sb_index;
	p_ramrod->path_id		= QED_PATH_ID(p_hwfn);
	p_ramrod->करोnt_log_ramrods	= 0;
	p_ramrod->log_type_mask		= cpu_to_le16(0xf);

	अगर (test_bit(QED_MF_OVLAN_CLSS, &p_hwfn->cdev->mf_bits))
		p_ramrod->mf_mode = MF_OVLAN;
	अन्यथा
		p_ramrod->mf_mode = MF_NPAR;

	outer_tag_config = &p_ramrod->outer_tag_config;
	outer_tag_config->outer_tag.tci = cpu_to_le16(p_hwfn->hw_info.ovlan);

	अगर (test_bit(QED_MF_8021Q_TAGGING, &p_hwfn->cdev->mf_bits)) अणु
		outer_tag_config->outer_tag.tpid = cpu_to_le16(ETH_P_8021Q);
	पूर्ण अन्यथा अगर (test_bit(QED_MF_8021AD_TAGGING, &p_hwfn->cdev->mf_bits)) अणु
		outer_tag_config->outer_tag.tpid = cpu_to_le16(ETH_P_8021AD);
		outer_tag_config->enable_stag_pri_change = 1;
	पूर्ण

	outer_tag_config->pri_map_valid = 1;
	क्रम (i = 0; i < QED_MAX_PFC_PRIORITIES; i++)
		outer_tag_config->inner_to_outer_pri_map[i] = i;

	/* enable_stag_pri_change should be set अगर port is in BD mode or,
	 * UFP with Host Control mode.
	 */
	अगर (test_bit(QED_MF_UFP_SPECIFIC, &p_hwfn->cdev->mf_bits)) अणु
		अगर (p_hwfn->ufp_info.pri_type == QED_UFP_PRI_OS)
			outer_tag_config->enable_stag_pri_change = 1;
		अन्यथा
			outer_tag_config->enable_stag_pri_change = 0;

		outer_tag_config->outer_tag.tci |=
		    cpu_to_le16(((u16)p_hwfn->ufp_info.tc << 13));
	पूर्ण

	/* Place EQ address in RAMROD */
	DMA_REGPAIR_LE(p_ramrod->event_ring_pbl_addr,
		       qed_chain_get_pbl_phys(&p_hwfn->p_eq->chain));
	page_cnt = (u8)qed_chain_get_page_cnt(&p_hwfn->p_eq->chain);
	p_ramrod->event_ring_num_pages = page_cnt;
	DMA_REGPAIR_LE(p_ramrod->consolid_q_pbl_addr,
		       qed_chain_get_pbl_phys(&p_hwfn->p_consq->chain));

	qed_tunn_set_pf_start_params(p_hwfn, p_tunn, &p_ramrod->tunnel_config);

	अगर (test_bit(QED_MF_INTER_PF_SWITCH, &p_hwfn->cdev->mf_bits))
		p_ramrod->allow_npar_tx_चयनing = allow_npar_tx_चयन;

	चयन (p_hwfn->hw_info.personality) अणु
	हाल QED_PCI_ETH:
		p_ramrod->personality = PERSONALITY_ETH;
		अवरोध;
	हाल QED_PCI_FCOE:
		p_ramrod->personality = PERSONALITY_FCOE;
		अवरोध;
	हाल QED_PCI_ISCSI:
		p_ramrod->personality = PERSONALITY_ISCSI;
		अवरोध;
	हाल QED_PCI_ETH_ROCE:
	हाल QED_PCI_ETH_IWARP:
		p_ramrod->personality = PERSONALITY_RDMA_AND_ETH;
		अवरोध;
	शेष:
		DP_NOTICE(p_hwfn, "Unknown personality %d\n",
			  p_hwfn->hw_info.personality);
		p_ramrod->personality = PERSONALITY_ETH;
	पूर्ण

	अगर (p_hwfn->cdev->p_iov_info) अणु
		काष्ठा qed_hw_sriov_info *p_iov = p_hwfn->cdev->p_iov_info;

		p_ramrod->base_vf_id = (u8) p_iov->first_vf_in_pf;
		p_ramrod->num_vfs = (u8) p_iov->total_vfs;
	पूर्ण
	p_ramrod->hsi_fp_ver.major_ver_arr[ETH_VER_KEY] = ETH_HSI_VER_MAJOR;
	p_ramrod->hsi_fp_ver.minor_ver_arr[ETH_VER_KEY] = ETH_HSI_VER_MINOR;

	DP_VERBOSE(p_hwfn, QED_MSG_SPQ,
		   "Setting event_ring_sb [id %04x index %02x], outer_tag.tci [%d]\n",
		   sb, sb_index, outer_tag_config->outer_tag.tci);

	rc = qed_spq_post(p_hwfn, p_ent, शून्य);

	अगर (p_tunn)
		qed_set_hw_tunn_mode_port(p_hwfn, p_ptt,
					  &p_hwfn->cdev->tunnel);

	वापस rc;
पूर्ण

पूर्णांक qed_sp_pf_update(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_spq_entry *p_ent = शून्य;
	काष्ठा qed_sp_init_data init_data;
	पूर्णांक rc;

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_CB;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 COMMON_RAMROD_PF_UPDATE, PROTOCOLID_COMMON,
				 &init_data);
	अगर (rc)
		वापस rc;

	qed_dcbx_set_pf_update_params(&p_hwfn->p_dcbx_info->results,
				      &p_ent->ramrod.pf_update);

	वापस qed_spq_post(p_hwfn, p_ent, शून्य);
पूर्ण

पूर्णांक qed_sp_pf_update_ufp(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_spq_entry *p_ent = शून्य;
	काष्ठा qed_sp_init_data init_data;
	पूर्णांक rc;

	अगर (p_hwfn->ufp_info.pri_type == QED_UFP_PRI_UNKNOWN) अणु
		DP_INFO(p_hwfn, "Invalid priority type %d\n",
			p_hwfn->ufp_info.pri_type);
		वापस -EINVAL;
	पूर्ण

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_CB;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 COMMON_RAMROD_PF_UPDATE, PROTOCOLID_COMMON,
				 &init_data);
	अगर (rc)
		वापस rc;

	p_ent->ramrod.pf_update.update_enable_stag_pri_change = true;
	अगर (p_hwfn->ufp_info.pri_type == QED_UFP_PRI_OS)
		p_ent->ramrod.pf_update.enable_stag_pri_change = 1;
	अन्यथा
		p_ent->ramrod.pf_update.enable_stag_pri_change = 0;

	वापस qed_spq_post(p_hwfn, p_ent, शून्य);
पूर्ण

/* Set pf update ramrod command params */
पूर्णांक qed_sp_pf_update_tunn_cfg(काष्ठा qed_hwfn *p_hwfn,
			      काष्ठा qed_ptt *p_ptt,
			      काष्ठा qed_tunnel_info *p_tunn,
			      क्रमागत spq_mode comp_mode,
			      काष्ठा qed_spq_comp_cb *p_comp_data)
अणु
	काष्ठा qed_spq_entry *p_ent = शून्य;
	काष्ठा qed_sp_init_data init_data;
	पूर्णांक rc;

	अगर (IS_VF(p_hwfn->cdev))
		वापस qed_vf_pf_tunnel_param_update(p_hwfn, p_tunn);

	अगर (!p_tunn)
		वापस -EINVAL;

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_data;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 COMMON_RAMROD_PF_UPDATE, PROTOCOLID_COMMON,
				 &init_data);
	अगर (rc)
		वापस rc;

	qed_tunn_set_pf_update_params(p_hwfn, p_tunn,
				      &p_ent->ramrod.pf_update.tunnel_config);

	rc = qed_spq_post(p_hwfn, p_ent, शून्य);
	अगर (rc)
		वापस rc;

	qed_set_hw_tunn_mode_port(p_hwfn, p_ptt, &p_hwfn->cdev->tunnel);

	वापस rc;
पूर्ण

पूर्णांक qed_sp_pf_stop(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_spq_entry *p_ent = शून्य;
	काष्ठा qed_sp_init_data init_data;
	पूर्णांक rc;

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 COMMON_RAMROD_PF_STOP, PROTOCOLID_COMMON,
				 &init_data);
	अगर (rc)
		वापस rc;

	वापस qed_spq_post(p_hwfn, p_ent, शून्य);
पूर्ण

पूर्णांक qed_sp_heartbeat_ramrod(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_spq_entry *p_ent = शून्य;
	काष्ठा qed_sp_init_data init_data;
	पूर्णांक rc;

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 COMMON_RAMROD_EMPTY, PROTOCOLID_COMMON,
				 &init_data);
	अगर (rc)
		वापस rc;

	वापस qed_spq_post(p_hwfn, p_ent, शून्य);
पूर्ण

पूर्णांक qed_sp_pf_update_stag(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_spq_entry *p_ent = शून्य;
	काष्ठा qed_sp_init_data init_data;
	पूर्णांक rc;

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_CB;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 COMMON_RAMROD_PF_UPDATE, PROTOCOLID_COMMON,
				 &init_data);
	अगर (rc)
		वापस rc;

	p_ent->ramrod.pf_update.update_mf_vlan_flag = true;
	p_ent->ramrod.pf_update.mf_vlan = cpu_to_le16(p_hwfn->hw_info.ovlan);
	अगर (test_bit(QED_MF_UFP_SPECIFIC, &p_hwfn->cdev->mf_bits))
		p_ent->ramrod.pf_update.mf_vlan |=
			cpu_to_le16(((u16)p_hwfn->ufp_info.tc << 13));

	वापस qed_spq_post(p_hwfn, p_ent, शून्य);
पूर्ण
