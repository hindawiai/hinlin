<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#समावेश <linux/etherdevice.h>
#समावेश <linux/crc32.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/crash_dump.h>
#समावेश <linux/qed/qed_iov_अगर.h>
#समावेश "qed_cxt.h"
#समावेश "qed_hsi.h"
#समावेश "qed_hw.h"
#समावेश "qed_init_ops.h"
#समावेश "qed_int.h"
#समावेश "qed_mcp.h"
#समावेश "qed_reg_addr.h"
#समावेश "qed_sp.h"
#समावेश "qed_sriov.h"
#समावेश "qed_vf.h"
अटल पूर्णांक qed_sriov_eqe_event(काष्ठा qed_hwfn *p_hwfn,
			       u8 opcode,
			       __le16 echo,
			       जोड़ event_ring_data *data, u8 fw_वापस_code);
अटल पूर्णांक qed_iov_bulletin_set_mac(काष्ठा qed_hwfn *p_hwfn, u8 *mac, पूर्णांक vfid);

अटल u8 qed_vf_calculate_legacy(काष्ठा qed_vf_info *p_vf)
अणु
	u8 legacy = 0;

	अगर (p_vf->acquire.vfdev_info.eth_fp_hsi_minor ==
	    ETH_HSI_VER_NO_PKT_LEN_TUNN)
		legacy |= QED_QCID_LEGACY_VF_RX_PROD;

	अगर (!(p_vf->acquire.vfdev_info.capabilities &
	      VFPF_ACQUIRE_CAP_QUEUE_QIDS))
		legacy |= QED_QCID_LEGACY_VF_CID;

	वापस legacy;
पूर्ण

/* IOV ramrods */
अटल पूर्णांक qed_sp_vf_start(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_vf_info *p_vf)
अणु
	काष्ठा vf_start_ramrod_data *p_ramrod = शून्य;
	काष्ठा qed_spq_entry *p_ent = शून्य;
	काष्ठा qed_sp_init_data init_data;
	पूर्णांक rc = -EINVAL;
	u8 fp_minor;

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_vf->opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 COMMON_RAMROD_VF_START,
				 PROTOCOLID_COMMON, &init_data);
	अगर (rc)
		वापस rc;

	p_ramrod = &p_ent->ramrod.vf_start;

	p_ramrod->vf_id = GET_FIELD(p_vf->concrete_fid, PXP_CONCRETE_FID_VFID);
	p_ramrod->opaque_fid = cpu_to_le16(p_vf->opaque_fid);

	चयन (p_hwfn->hw_info.personality) अणु
	हाल QED_PCI_ETH:
		p_ramrod->personality = PERSONALITY_ETH;
		अवरोध;
	हाल QED_PCI_ETH_ROCE:
	हाल QED_PCI_ETH_IWARP:
		p_ramrod->personality = PERSONALITY_RDMA_AND_ETH;
		अवरोध;
	शेष:
		DP_NOTICE(p_hwfn, "Unknown VF personality %d\n",
			  p_hwfn->hw_info.personality);
		qed_sp_destroy_request(p_hwfn, p_ent);
		वापस -EINVAL;
	पूर्ण

	fp_minor = p_vf->acquire.vfdev_info.eth_fp_hsi_minor;
	अगर (fp_minor > ETH_HSI_VER_MINOR &&
	    fp_minor != ETH_HSI_VER_NO_PKT_LEN_TUNN) अणु
		DP_VERBOSE(p_hwfn,
			   QED_MSG_IOV,
			   "VF [%d] - Requested fp hsi %02x.%02x which is slightly newer than PF's %02x.%02x; Configuring PFs version\n",
			   p_vf->असल_vf_id,
			   ETH_HSI_VER_MAJOR,
			   fp_minor, ETH_HSI_VER_MAJOR, ETH_HSI_VER_MINOR);
		fp_minor = ETH_HSI_VER_MINOR;
	पूर्ण

	p_ramrod->hsi_fp_ver.major_ver_arr[ETH_VER_KEY] = ETH_HSI_VER_MAJOR;
	p_ramrod->hsi_fp_ver.minor_ver_arr[ETH_VER_KEY] = fp_minor;

	DP_VERBOSE(p_hwfn, QED_MSG_IOV,
		   "VF[%d] - Starting using HSI %02x.%02x\n",
		   p_vf->असल_vf_id, ETH_HSI_VER_MAJOR, fp_minor);

	वापस qed_spq_post(p_hwfn, p_ent, शून्य);
पूर्ण

अटल पूर्णांक qed_sp_vf_stop(काष्ठा qed_hwfn *p_hwfn,
			  u32 concrete_vfid, u16 opaque_vfid)
अणु
	काष्ठा vf_stop_ramrod_data *p_ramrod = शून्य;
	काष्ठा qed_spq_entry *p_ent = शून्य;
	काष्ठा qed_sp_init_data init_data;
	पूर्णांक rc = -EINVAL;

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = opaque_vfid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 COMMON_RAMROD_VF_STOP,
				 PROTOCOLID_COMMON, &init_data);
	अगर (rc)
		वापस rc;

	p_ramrod = &p_ent->ramrod.vf_stop;

	p_ramrod->vf_id = GET_FIELD(concrete_vfid, PXP_CONCRETE_FID_VFID);

	वापस qed_spq_post(p_hwfn, p_ent, शून्य);
पूर्ण

bool qed_iov_is_valid_vfid(काष्ठा qed_hwfn *p_hwfn,
			   पूर्णांक rel_vf_id,
			   bool b_enabled_only, bool b_non_malicious)
अणु
	अगर (!p_hwfn->pf_iov_info) अणु
		DP_NOTICE(p_hwfn->cdev, "No iov info\n");
		वापस false;
	पूर्ण

	अगर ((rel_vf_id >= p_hwfn->cdev->p_iov_info->total_vfs) ||
	    (rel_vf_id < 0))
		वापस false;

	अगर ((!p_hwfn->pf_iov_info->vfs_array[rel_vf_id].b_init) &&
	    b_enabled_only)
		वापस false;

	अगर ((p_hwfn->pf_iov_info->vfs_array[rel_vf_id].b_malicious) &&
	    b_non_malicious)
		वापस false;

	वापस true;
पूर्ण

अटल काष्ठा qed_vf_info *qed_iov_get_vf_info(काष्ठा qed_hwfn *p_hwfn,
					       u16 relative_vf_id,
					       bool b_enabled_only)
अणु
	काष्ठा qed_vf_info *vf = शून्य;

	अगर (!p_hwfn->pf_iov_info) अणु
		DP_NOTICE(p_hwfn->cdev, "No iov info\n");
		वापस शून्य;
	पूर्ण

	अगर (qed_iov_is_valid_vfid(p_hwfn, relative_vf_id,
				  b_enabled_only, false))
		vf = &p_hwfn->pf_iov_info->vfs_array[relative_vf_id];
	अन्यथा
		DP_ERR(p_hwfn, "qed_iov_get_vf_info: VF[%d] is not enabled\n",
		       relative_vf_id);

	वापस vf;
पूर्ण

अटल काष्ठा qed_queue_cid *
qed_iov_get_vf_rx_queue_cid(काष्ठा qed_vf_queue *p_queue)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_QUEUES_PER_QZONE; i++) अणु
		अगर (p_queue->cids[i].p_cid && !p_queue->cids[i].b_is_tx)
			वापस p_queue->cids[i].p_cid;
	पूर्ण

	वापस शून्य;
पूर्ण

क्रमागत qed_iov_validate_q_mode अणु
	QED_IOV_VALIDATE_Q_NA,
	QED_IOV_VALIDATE_Q_ENABLE,
	QED_IOV_VALIDATE_Q_DISABLE,
पूर्ण;

अटल bool qed_iov_validate_queue_mode(काष्ठा qed_hwfn *p_hwfn,
					काष्ठा qed_vf_info *p_vf,
					u16 qid,
					क्रमागत qed_iov_validate_q_mode mode,
					bool b_is_tx)
अणु
	पूर्णांक i;

	अगर (mode == QED_IOV_VALIDATE_Q_NA)
		वापस true;

	क्रम (i = 0; i < MAX_QUEUES_PER_QZONE; i++) अणु
		काष्ठा qed_vf_queue_cid *p_qcid;

		p_qcid = &p_vf->vf_queues[qid].cids[i];

		अगर (!p_qcid->p_cid)
			जारी;

		अगर (p_qcid->b_is_tx != b_is_tx)
			जारी;

		वापस mode == QED_IOV_VALIDATE_Q_ENABLE;
	पूर्ण

	/* In हाल we haven't found any valid cid, then its disabled */
	वापस mode == QED_IOV_VALIDATE_Q_DISABLE;
पूर्ण

अटल bool qed_iov_validate_rxq(काष्ठा qed_hwfn *p_hwfn,
				 काष्ठा qed_vf_info *p_vf,
				 u16 rx_qid,
				 क्रमागत qed_iov_validate_q_mode mode)
अणु
	अगर (rx_qid >= p_vf->num_rxqs) अणु
		DP_VERBOSE(p_hwfn,
			   QED_MSG_IOV,
			   "VF[0x%02x] - can't touch Rx queue[%04x]; Only 0x%04x are allocated\n",
			   p_vf->असल_vf_id, rx_qid, p_vf->num_rxqs);
		वापस false;
	पूर्ण

	वापस qed_iov_validate_queue_mode(p_hwfn, p_vf, rx_qid, mode, false);
पूर्ण

अटल bool qed_iov_validate_txq(काष्ठा qed_hwfn *p_hwfn,
				 काष्ठा qed_vf_info *p_vf,
				 u16 tx_qid,
				 क्रमागत qed_iov_validate_q_mode mode)
अणु
	अगर (tx_qid >= p_vf->num_txqs) अणु
		DP_VERBOSE(p_hwfn,
			   QED_MSG_IOV,
			   "VF[0x%02x] - can't touch Tx queue[%04x]; Only 0x%04x are allocated\n",
			   p_vf->असल_vf_id, tx_qid, p_vf->num_txqs);
		वापस false;
	पूर्ण

	वापस qed_iov_validate_queue_mode(p_hwfn, p_vf, tx_qid, mode, true);
पूर्ण

अटल bool qed_iov_validate_sb(काष्ठा qed_hwfn *p_hwfn,
				काष्ठा qed_vf_info *p_vf, u16 sb_idx)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < p_vf->num_sbs; i++)
		अगर (p_vf->igu_sbs[i] == sb_idx)
			वापस true;

	DP_VERBOSE(p_hwfn,
		   QED_MSG_IOV,
		   "VF[0%02x] - tried using sb_idx %04x which doesn't exist as one of its 0x%02x SBs\n",
		   p_vf->असल_vf_id, sb_idx, p_vf->num_sbs);

	वापस false;
पूर्ण

अटल bool qed_iov_validate_active_rxq(काष्ठा qed_hwfn *p_hwfn,
					काष्ठा qed_vf_info *p_vf)
अणु
	u8 i;

	क्रम (i = 0; i < p_vf->num_rxqs; i++)
		अगर (qed_iov_validate_queue_mode(p_hwfn, p_vf, i,
						QED_IOV_VALIDATE_Q_ENABLE,
						false))
			वापस true;

	वापस false;
पूर्ण

अटल bool qed_iov_validate_active_txq(काष्ठा qed_hwfn *p_hwfn,
					काष्ठा qed_vf_info *p_vf)
अणु
	u8 i;

	क्रम (i = 0; i < p_vf->num_txqs; i++)
		अगर (qed_iov_validate_queue_mode(p_hwfn, p_vf, i,
						QED_IOV_VALIDATE_Q_ENABLE,
						true))
			वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक qed_iov_post_vf_bulletin(काष्ठा qed_hwfn *p_hwfn,
				    पूर्णांक vfid, काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा qed_bulletin_content *p_bulletin;
	पूर्णांक crc_size = माप(p_bulletin->crc);
	काष्ठा qed_dmae_params params;
	काष्ठा qed_vf_info *p_vf;

	p_vf = qed_iov_get_vf_info(p_hwfn, (u16) vfid, true);
	अगर (!p_vf)
		वापस -EINVAL;

	अगर (!p_vf->vf_bulletin)
		वापस -EINVAL;

	p_bulletin = p_vf->bulletin.p_virt;

	/* Increment bulletin board version and compute crc */
	p_bulletin->version++;
	p_bulletin->crc = crc32(0, (u8 *)p_bulletin + crc_size,
				p_vf->bulletin.size - crc_size);

	DP_VERBOSE(p_hwfn, QED_MSG_IOV,
		   "Posting Bulletin 0x%08x to VF[%d] (CRC 0x%08x)\n",
		   p_bulletin->version, p_vf->relative_vf_id, p_bulletin->crc);

	/* propagate bulletin board via dmae to vm memory */
	स_रखो(&params, 0, माप(params));
	SET_FIELD(params.flags, QED_DMAE_PARAMS_DST_VF_VALID, 0x1);
	params.dst_vfid = p_vf->असल_vf_id;
	वापस qed_dmae_host2host(p_hwfn, p_ptt, p_vf->bulletin.phys,
				  p_vf->vf_bulletin, p_vf->bulletin.size / 4,
				  &params);
पूर्ण

अटल पूर्णांक qed_iov_pci_cfg_info(काष्ठा qed_dev *cdev)
अणु
	काष्ठा qed_hw_sriov_info *iov = cdev->p_iov_info;
	पूर्णांक pos = iov->pos;

	DP_VERBOSE(cdev, QED_MSG_IOV, "sriov ext pos %d\n", pos);
	pci_पढ़ो_config_word(cdev->pdev, pos + PCI_SRIOV_CTRL, &iov->ctrl);

	pci_पढ़ो_config_word(cdev->pdev,
			     pos + PCI_SRIOV_TOTAL_VF, &iov->total_vfs);
	pci_पढ़ो_config_word(cdev->pdev,
			     pos + PCI_SRIOV_INITIAL_VF, &iov->initial_vfs);

	pci_पढ़ो_config_word(cdev->pdev, pos + PCI_SRIOV_NUM_VF, &iov->num_vfs);
	अगर (iov->num_vfs) अणु
		DP_VERBOSE(cdev,
			   QED_MSG_IOV,
			   "Number of VFs are already set to non-zero value. Ignoring PCI configuration value\n");
		iov->num_vfs = 0;
	पूर्ण

	pci_पढ़ो_config_word(cdev->pdev,
			     pos + PCI_SRIOV_VF_OFFSET, &iov->offset);

	pci_पढ़ो_config_word(cdev->pdev,
			     pos + PCI_SRIOV_VF_STRIDE, &iov->stride);

	pci_पढ़ो_config_word(cdev->pdev,
			     pos + PCI_SRIOV_VF_DID, &iov->vf_device_id);

	pci_पढ़ो_config_dword(cdev->pdev,
			      pos + PCI_SRIOV_SUP_PGSIZE, &iov->pgsz);

	pci_पढ़ो_config_dword(cdev->pdev, pos + PCI_SRIOV_CAP, &iov->cap);

	pci_पढ़ो_config_byte(cdev->pdev, pos + PCI_SRIOV_FUNC_LINK, &iov->link);

	DP_VERBOSE(cdev,
		   QED_MSG_IOV,
		   "IOV info: nres %d, cap 0x%x, ctrl 0x%x, total %d, initial %d, num vfs %d, offset %d, stride %d, page size 0x%x\n",
		   iov->nres,
		   iov->cap,
		   iov->ctrl,
		   iov->total_vfs,
		   iov->initial_vfs,
		   iov->nr_virtfn, iov->offset, iov->stride, iov->pgsz);

	/* Some sanity checks */
	अगर (iov->num_vfs > NUM_OF_VFS(cdev) ||
	    iov->total_vfs > NUM_OF_VFS(cdev)) अणु
		/* This can happen only due to a bug. In this हाल we set
		 * num_vfs to zero to aव्योम memory corruption in the code that
		 * assumes max number of vfs
		 */
		DP_NOTICE(cdev,
			  "IOV: Unexpected number of vfs set: %d setting num_vf to zero\n",
			  iov->num_vfs);

		iov->num_vfs = 0;
		iov->total_vfs = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qed_iov_setup_vfdb(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_hw_sriov_info *p_iov = p_hwfn->cdev->p_iov_info;
	काष्ठा qed_pf_iov *p_iov_info = p_hwfn->pf_iov_info;
	काष्ठा qed_bulletin_content *p_bulletin_virt;
	dma_addr_t req_p, rply_p, bulletin_p;
	जोड़ pfvf_tlvs *p_reply_virt_addr;
	जोड़ vfpf_tlvs *p_req_virt_addr;
	u8 idx = 0;

	स_रखो(p_iov_info->vfs_array, 0, माप(p_iov_info->vfs_array));

	p_req_virt_addr = p_iov_info->mbx_msg_virt_addr;
	req_p = p_iov_info->mbx_msg_phys_addr;
	p_reply_virt_addr = p_iov_info->mbx_reply_virt_addr;
	rply_p = p_iov_info->mbx_reply_phys_addr;
	p_bulletin_virt = p_iov_info->p_bulletins;
	bulletin_p = p_iov_info->bulletins_phys;
	अगर (!p_req_virt_addr || !p_reply_virt_addr || !p_bulletin_virt) अणु
		DP_ERR(p_hwfn,
		       "qed_iov_setup_vfdb called without allocating mem first\n");
		वापस;
	पूर्ण

	क्रम (idx = 0; idx < p_iov->total_vfs; idx++) अणु
		काष्ठा qed_vf_info *vf = &p_iov_info->vfs_array[idx];
		u32 concrete;

		vf->vf_mbx.req_virt = p_req_virt_addr + idx;
		vf->vf_mbx.req_phys = req_p + idx * माप(जोड़ vfpf_tlvs);
		vf->vf_mbx.reply_virt = p_reply_virt_addr + idx;
		vf->vf_mbx.reply_phys = rply_p + idx * माप(जोड़ pfvf_tlvs);

		vf->state = VF_STOPPED;
		vf->b_init = false;

		vf->bulletin.phys = idx *
				    माप(काष्ठा qed_bulletin_content) +
				    bulletin_p;
		vf->bulletin.p_virt = p_bulletin_virt + idx;
		vf->bulletin.size = माप(काष्ठा qed_bulletin_content);

		vf->relative_vf_id = idx;
		vf->असल_vf_id = idx + p_iov->first_vf_in_pf;
		concrete = qed_vfid_to_concrete(p_hwfn, vf->असल_vf_id);
		vf->concrete_fid = concrete;
		vf->opaque_fid = (p_hwfn->hw_info.opaque_fid & 0xff) |
				 (vf->असल_vf_id << 8);
		vf->vport_id = idx + 1;

		vf->num_mac_filters = QED_ETH_VF_NUM_MAC_FILTERS;
		vf->num_vlan_filters = QED_ETH_VF_NUM_VLAN_FILTERS;
	पूर्ण
पूर्ण

अटल पूर्णांक qed_iov_allocate_vfdb(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_pf_iov *p_iov_info = p_hwfn->pf_iov_info;
	व्योम **p_v_addr;
	u16 num_vfs = 0;

	num_vfs = p_hwfn->cdev->p_iov_info->total_vfs;

	DP_VERBOSE(p_hwfn, QED_MSG_IOV,
		   "qed_iov_allocate_vfdb for %d VFs\n", num_vfs);

	/* Allocate PF Mailbox buffer (per-VF) */
	p_iov_info->mbx_msg_size = माप(जोड़ vfpf_tlvs) * num_vfs;
	p_v_addr = &p_iov_info->mbx_msg_virt_addr;
	*p_v_addr = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
				       p_iov_info->mbx_msg_size,
				       &p_iov_info->mbx_msg_phys_addr,
				       GFP_KERNEL);
	अगर (!*p_v_addr)
		वापस -ENOMEM;

	/* Allocate PF Mailbox Reply buffer (per-VF) */
	p_iov_info->mbx_reply_size = माप(जोड़ pfvf_tlvs) * num_vfs;
	p_v_addr = &p_iov_info->mbx_reply_virt_addr;
	*p_v_addr = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
				       p_iov_info->mbx_reply_size,
				       &p_iov_info->mbx_reply_phys_addr,
				       GFP_KERNEL);
	अगर (!*p_v_addr)
		वापस -ENOMEM;

	p_iov_info->bulletins_size = माप(काष्ठा qed_bulletin_content) *
				     num_vfs;
	p_v_addr = &p_iov_info->p_bulletins;
	*p_v_addr = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
				       p_iov_info->bulletins_size,
				       &p_iov_info->bulletins_phys,
				       GFP_KERNEL);
	अगर (!*p_v_addr)
		वापस -ENOMEM;

	DP_VERBOSE(p_hwfn,
		   QED_MSG_IOV,
		   "PF's Requests mailbox [%p virt 0x%llx phys],  Response mailbox [%p virt 0x%llx phys] Bulletins [%p virt 0x%llx phys]\n",
		   p_iov_info->mbx_msg_virt_addr,
		   (u64) p_iov_info->mbx_msg_phys_addr,
		   p_iov_info->mbx_reply_virt_addr,
		   (u64) p_iov_info->mbx_reply_phys_addr,
		   p_iov_info->p_bulletins, (u64) p_iov_info->bulletins_phys);

	वापस 0;
पूर्ण

अटल व्योम qed_iov_मुक्त_vfdb(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_pf_iov *p_iov_info = p_hwfn->pf_iov_info;

	अगर (p_hwfn->pf_iov_info->mbx_msg_virt_addr)
		dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
				  p_iov_info->mbx_msg_size,
				  p_iov_info->mbx_msg_virt_addr,
				  p_iov_info->mbx_msg_phys_addr);

	अगर (p_hwfn->pf_iov_info->mbx_reply_virt_addr)
		dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
				  p_iov_info->mbx_reply_size,
				  p_iov_info->mbx_reply_virt_addr,
				  p_iov_info->mbx_reply_phys_addr);

	अगर (p_iov_info->p_bulletins)
		dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
				  p_iov_info->bulletins_size,
				  p_iov_info->p_bulletins,
				  p_iov_info->bulletins_phys);
पूर्ण

पूर्णांक qed_iov_alloc(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_pf_iov *p_sriov;

	अगर (!IS_PF_SRIOV(p_hwfn)) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "No SR-IOV - no need for IOV db\n");
		वापस 0;
	पूर्ण

	p_sriov = kzalloc(माप(*p_sriov), GFP_KERNEL);
	अगर (!p_sriov)
		वापस -ENOMEM;

	p_hwfn->pf_iov_info = p_sriov;

	qed_spq_रेजिस्टर_async_cb(p_hwfn, PROTOCOLID_COMMON,
				  qed_sriov_eqe_event);

	वापस qed_iov_allocate_vfdb(p_hwfn);
पूर्ण

व्योम qed_iov_setup(काष्ठा qed_hwfn *p_hwfn)
अणु
	अगर (!IS_PF_SRIOV(p_hwfn) || !IS_PF_SRIOV_ALLOC(p_hwfn))
		वापस;

	qed_iov_setup_vfdb(p_hwfn);
पूर्ण

व्योम qed_iov_मुक्त(काष्ठा qed_hwfn *p_hwfn)
अणु
	qed_spq_unरेजिस्टर_async_cb(p_hwfn, PROTOCOLID_COMMON);

	अगर (IS_PF_SRIOV_ALLOC(p_hwfn)) अणु
		qed_iov_मुक्त_vfdb(p_hwfn);
		kमुक्त(p_hwfn->pf_iov_info);
	पूर्ण
पूर्ण

व्योम qed_iov_मुक्त_hw_info(काष्ठा qed_dev *cdev)
अणु
	kमुक्त(cdev->p_iov_info);
	cdev->p_iov_info = शून्य;
पूर्ण

पूर्णांक qed_iov_hw_info(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_dev *cdev = p_hwfn->cdev;
	पूर्णांक pos;
	पूर्णांक rc;

	अगर (is_kdump_kernel())
		वापस 0;

	अगर (IS_VF(p_hwfn->cdev))
		वापस 0;

	/* Learn the PCI configuration */
	pos = pci_find_ext_capability(p_hwfn->cdev->pdev,
				      PCI_EXT_CAP_ID_SRIOV);
	अगर (!pos) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_IOV, "No PCIe IOV support\n");
		वापस 0;
	पूर्ण

	/* Allocate a new काष्ठा क्रम IOV inक्रमmation */
	cdev->p_iov_info = kzalloc(माप(*cdev->p_iov_info), GFP_KERNEL);
	अगर (!cdev->p_iov_info)
		वापस -ENOMEM;

	cdev->p_iov_info->pos = pos;

	rc = qed_iov_pci_cfg_info(cdev);
	अगर (rc)
		वापस rc;

	/* We want PF IOV to be synonemous with the existance of p_iov_info;
	 * In हाल the capability is published but there are no VFs, simply
	 * de-allocate the काष्ठा.
	 */
	अगर (!cdev->p_iov_info->total_vfs) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "IOV capabilities, but no VFs are published\n");
		kमुक्त(cdev->p_iov_info);
		cdev->p_iov_info = शून्य;
		वापस 0;
	पूर्ण

	/* First VF index based on offset is tricky:
	 *  - If ARI is supported [likely], offset - (16 - pf_id) would
	 *    provide the number क्रम eng0. 2nd engine Vfs would begin
	 *    after the first engine's VFs.
	 *  - If !ARI, VFs would start on next device.
	 *    so offset - (256 - pf_id) would provide the number.
	 * Utilize the fact that (256 - pf_id) is achieved only by later
	 * to dअगरferentiate between the two.
	 */

	अगर (p_hwfn->cdev->p_iov_info->offset < (256 - p_hwfn->असल_pf_id)) अणु
		u32 first = p_hwfn->cdev->p_iov_info->offset +
			    p_hwfn->असल_pf_id - 16;

		cdev->p_iov_info->first_vf_in_pf = first;

		अगर (QED_PATH_ID(p_hwfn))
			cdev->p_iov_info->first_vf_in_pf -= MAX_NUM_VFS_BB;
	पूर्ण अन्यथा अणु
		u32 first = p_hwfn->cdev->p_iov_info->offset +
			    p_hwfn->असल_pf_id - 256;

		cdev->p_iov_info->first_vf_in_pf = first;
	पूर्ण

	DP_VERBOSE(p_hwfn, QED_MSG_IOV,
		   "First VF in hwfn 0x%08x\n",
		   cdev->p_iov_info->first_vf_in_pf);

	वापस 0;
पूर्ण

अटल bool _qed_iov_pf_sanity_check(काष्ठा qed_hwfn *p_hwfn,
				     पूर्णांक vfid, bool b_fail_malicious)
अणु
	/* Check PF supports sriov */
	अगर (IS_VF(p_hwfn->cdev) || !IS_QED_SRIOV(p_hwfn->cdev) ||
	    !IS_PF_SRIOV_ALLOC(p_hwfn))
		वापस false;

	/* Check VF validity */
	अगर (!qed_iov_is_valid_vfid(p_hwfn, vfid, true, b_fail_malicious))
		वापस false;

	वापस true;
पूर्ण

अटल bool qed_iov_pf_sanity_check(काष्ठा qed_hwfn *p_hwfn, पूर्णांक vfid)
अणु
	वापस _qed_iov_pf_sanity_check(p_hwfn, vfid, true);
पूर्ण

अटल व्योम qed_iov_set_vf_to_disable(काष्ठा qed_dev *cdev,
				      u16 rel_vf_id, u8 to_disable)
अणु
	काष्ठा qed_vf_info *vf;
	पूर्णांक i;

	क्रम_each_hwfn(cdev, i) अणु
		काष्ठा qed_hwfn *p_hwfn = &cdev->hwfns[i];

		vf = qed_iov_get_vf_info(p_hwfn, rel_vf_id, false);
		अगर (!vf)
			जारी;

		vf->to_disable = to_disable;
	पूर्ण
पूर्ण

अटल व्योम qed_iov_set_vfs_to_disable(काष्ठा qed_dev *cdev, u8 to_disable)
अणु
	u16 i;

	अगर (!IS_QED_SRIOV(cdev))
		वापस;

	क्रम (i = 0; i < cdev->p_iov_info->total_vfs; i++)
		qed_iov_set_vf_to_disable(cdev, i, to_disable);
पूर्ण

अटल व्योम qed_iov_vf_pglue_clear_err(काष्ठा qed_hwfn *p_hwfn,
				       काष्ठा qed_ptt *p_ptt, u8 असल_vfid)
अणु
	qed_wr(p_hwfn, p_ptt,
	       PGLUE_B_REG_WAS_ERROR_VF_31_0_CLR + (असल_vfid >> 5) * 4,
	       1 << (असल_vfid & 0x1f));
पूर्ण

अटल व्योम qed_iov_vf_igu_reset(काष्ठा qed_hwfn *p_hwfn,
				 काष्ठा qed_ptt *p_ptt, काष्ठा qed_vf_info *vf)
अणु
	पूर्णांक i;

	/* Set VF masks and configuration - pretend */
	qed_fid_pretend(p_hwfn, p_ptt, (u16) vf->concrete_fid);

	qed_wr(p_hwfn, p_ptt, IGU_REG_STATISTIC_NUM_VF_MSG_SENT, 0);

	/* unpretend */
	qed_fid_pretend(p_hwfn, p_ptt, (u16) p_hwfn->hw_info.concrete_fid);

	/* iterate over all queues, clear sb consumer */
	क्रम (i = 0; i < vf->num_sbs; i++)
		qed_पूर्णांक_igu_init_pure_rt_single(p_hwfn, p_ptt,
						vf->igu_sbs[i],
						vf->opaque_fid, true);
पूर्ण

अटल व्योम qed_iov_vf_igu_set_पूर्णांक(काष्ठा qed_hwfn *p_hwfn,
				   काष्ठा qed_ptt *p_ptt,
				   काष्ठा qed_vf_info *vf, bool enable)
अणु
	u32 igu_vf_conf;

	qed_fid_pretend(p_hwfn, p_ptt, (u16) vf->concrete_fid);

	igu_vf_conf = qed_rd(p_hwfn, p_ptt, IGU_REG_VF_CONFIGURATION);

	अगर (enable)
		igu_vf_conf |= IGU_VF_CONF_MSI_MSIX_EN;
	अन्यथा
		igu_vf_conf &= ~IGU_VF_CONF_MSI_MSIX_EN;

	qed_wr(p_hwfn, p_ptt, IGU_REG_VF_CONFIGURATION, igu_vf_conf);

	/* unpretend */
	qed_fid_pretend(p_hwfn, p_ptt, (u16) p_hwfn->hw_info.concrete_fid);
पूर्ण

अटल पूर्णांक
qed_iov_enable_vf_access_msix(काष्ठा qed_hwfn *p_hwfn,
			      काष्ठा qed_ptt *p_ptt, u8 असल_vf_id, u8 num_sbs)
अणु
	u8 current_max = 0;
	पूर्णांक i;

	/* For AH onward, configuration is per-PF. Find maximum of all
	 * the currently enabled child VFs, and set the number to be that.
	 */
	अगर (!QED_IS_BB(p_hwfn->cdev)) अणु
		qed_क्रम_each_vf(p_hwfn, i) अणु
			काष्ठा qed_vf_info *p_vf;

			p_vf = qed_iov_get_vf_info(p_hwfn, (u16)i, true);
			अगर (!p_vf)
				जारी;

			current_max = max_t(u8, current_max, p_vf->num_sbs);
		पूर्ण
	पूर्ण

	अगर (num_sbs > current_max)
		वापस qed_mcp_config_vf_msix(p_hwfn, p_ptt,
					      असल_vf_id, num_sbs);

	वापस 0;
पूर्ण

अटल पूर्णांक qed_iov_enable_vf_access(काष्ठा qed_hwfn *p_hwfn,
				    काष्ठा qed_ptt *p_ptt,
				    काष्ठा qed_vf_info *vf)
अणु
	u32 igu_vf_conf = IGU_VF_CONF_FUNC_EN;
	पूर्णांक rc;

	/* It's possible VF was previously considered malicious -
	 * clear the indication even अगर we're only going to disable VF.
	 */
	vf->b_malicious = false;

	अगर (vf->to_disable)
		वापस 0;

	DP_VERBOSE(p_hwfn,
		   QED_MSG_IOV,
		   "Enable internal access for vf %x [abs %x]\n",
		   vf->असल_vf_id, QED_VF_ABS_ID(p_hwfn, vf));

	qed_iov_vf_pglue_clear_err(p_hwfn, p_ptt, QED_VF_ABS_ID(p_hwfn, vf));

	qed_iov_vf_igu_reset(p_hwfn, p_ptt, vf);

	rc = qed_iov_enable_vf_access_msix(p_hwfn, p_ptt,
					   vf->असल_vf_id, vf->num_sbs);
	अगर (rc)
		वापस rc;

	qed_fid_pretend(p_hwfn, p_ptt, (u16) vf->concrete_fid);

	SET_FIELD(igu_vf_conf, IGU_VF_CONF_PARENT, p_hwfn->rel_pf_id);
	STORE_RT_REG(p_hwfn, IGU_REG_VF_CONFIGURATION_RT_OFFSET, igu_vf_conf);

	qed_init_run(p_hwfn, p_ptt, PHASE_VF, vf->असल_vf_id,
		     p_hwfn->hw_info.hw_mode);

	/* unpretend */
	qed_fid_pretend(p_hwfn, p_ptt, (u16) p_hwfn->hw_info.concrete_fid);

	vf->state = VF_FREE;

	वापस rc;
पूर्ण

/**
 * qed_iov_config_perm_table() - Configure the permission zone table.
 *
 * @p_hwfn: HW device data.
 * @p_ptt: PTT winकरोw क्रम writing the रेजिस्टरs.
 * @vf: VF info data.
 * @enable: The actual permision क्रम this VF.
 *
 * In E4, queue zone permission table size is 320x9. There
 * are 320 VF queues क्रम single engine device (256 क्रम dual
 * engine device), and each entry has the following क्रमmat:
 * अणुValid, VF[7:0]पूर्ण
 */
अटल व्योम qed_iov_config_perm_table(काष्ठा qed_hwfn *p_hwfn,
				      काष्ठा qed_ptt *p_ptt,
				      काष्ठा qed_vf_info *vf, u8 enable)
अणु
	u32 reg_addr, val;
	u16 qzone_id = 0;
	पूर्णांक qid;

	क्रम (qid = 0; qid < vf->num_rxqs; qid++) अणु
		qed_fw_l2_queue(p_hwfn, vf->vf_queues[qid].fw_rx_qid,
				&qzone_id);

		reg_addr = PSWHST_REG_ZONE_PERMISSION_TABLE + qzone_id * 4;
		val = enable ? (vf->असल_vf_id | BIT(8)) : 0;
		qed_wr(p_hwfn, p_ptt, reg_addr, val);
	पूर्ण
पूर्ण

अटल व्योम qed_iov_enable_vf_traffic(काष्ठा qed_hwfn *p_hwfn,
				      काष्ठा qed_ptt *p_ptt,
				      काष्ठा qed_vf_info *vf)
अणु
	/* Reset vf in IGU - पूर्णांकerrupts are still disabled */
	qed_iov_vf_igu_reset(p_hwfn, p_ptt, vf);

	qed_iov_vf_igu_set_पूर्णांक(p_hwfn, p_ptt, vf, 1);

	/* Permission Table */
	qed_iov_config_perm_table(p_hwfn, p_ptt, vf, true);
पूर्ण

अटल u8 qed_iov_alloc_vf_igu_sbs(काष्ठा qed_hwfn *p_hwfn,
				   काष्ठा qed_ptt *p_ptt,
				   काष्ठा qed_vf_info *vf, u16 num_rx_queues)
अणु
	काष्ठा qed_igu_block *p_block;
	काष्ठा cau_sb_entry sb_entry;
	पूर्णांक qid = 0;
	u32 val = 0;

	अगर (num_rx_queues > p_hwfn->hw_info.p_igu_info->usage.मुक्त_cnt_iov)
		num_rx_queues = p_hwfn->hw_info.p_igu_info->usage.मुक्त_cnt_iov;
	p_hwfn->hw_info.p_igu_info->usage.मुक्त_cnt_iov -= num_rx_queues;

	SET_FIELD(val, IGU_MAPPING_LINE_FUNCTION_NUMBER, vf->असल_vf_id);
	SET_FIELD(val, IGU_MAPPING_LINE_VALID, 1);
	SET_FIELD(val, IGU_MAPPING_LINE_PF_VALID, 0);

	क्रम (qid = 0; qid < num_rx_queues; qid++) अणु
		p_block = qed_get_igu_मुक्त_sb(p_hwfn, false);
		vf->igu_sbs[qid] = p_block->igu_sb_id;
		p_block->status &= ~QED_IGU_STATUS_FREE;
		SET_FIELD(val, IGU_MAPPING_LINE_VECTOR_NUMBER, qid);

		qed_wr(p_hwfn, p_ptt,
		       IGU_REG_MAPPING_MEMORY +
		       माप(u32) * p_block->igu_sb_id, val);

		/* Configure igu sb in CAU which were marked valid */
		qed_init_cau_sb_entry(p_hwfn, &sb_entry,
				      p_hwfn->rel_pf_id, vf->असल_vf_id, 1);

		qed_dmae_host2grc(p_hwfn, p_ptt,
				  (u64)(uपूर्णांकptr_t)&sb_entry,
				  CAU_REG_SB_VAR_MEMORY +
				  p_block->igu_sb_id * माप(u64), 2, शून्य);
	पूर्ण

	vf->num_sbs = (u8) num_rx_queues;

	वापस vf->num_sbs;
पूर्ण

अटल व्योम qed_iov_मुक्त_vf_igu_sbs(काष्ठा qed_hwfn *p_hwfn,
				    काष्ठा qed_ptt *p_ptt,
				    काष्ठा qed_vf_info *vf)
अणु
	काष्ठा qed_igu_info *p_info = p_hwfn->hw_info.p_igu_info;
	पूर्णांक idx, igu_id;
	u32 addr, val;

	/* Invalidate igu CAM lines and mark them as मुक्त */
	क्रम (idx = 0; idx < vf->num_sbs; idx++) अणु
		igu_id = vf->igu_sbs[idx];
		addr = IGU_REG_MAPPING_MEMORY + माप(u32) * igu_id;

		val = qed_rd(p_hwfn, p_ptt, addr);
		SET_FIELD(val, IGU_MAPPING_LINE_VALID, 0);
		qed_wr(p_hwfn, p_ptt, addr, val);

		p_info->entry[igu_id].status |= QED_IGU_STATUS_FREE;
		p_hwfn->hw_info.p_igu_info->usage.मुक्त_cnt_iov++;
	पूर्ण

	vf->num_sbs = 0;
पूर्ण

अटल व्योम qed_iov_set_link(काष्ठा qed_hwfn *p_hwfn,
			     u16 vfid,
			     काष्ठा qed_mcp_link_params *params,
			     काष्ठा qed_mcp_link_state *link,
			     काष्ठा qed_mcp_link_capabilities *p_caps)
अणु
	काष्ठा qed_vf_info *p_vf = qed_iov_get_vf_info(p_hwfn,
						       vfid,
						       false);
	काष्ठा qed_bulletin_content *p_bulletin;

	अगर (!p_vf)
		वापस;

	p_bulletin = p_vf->bulletin.p_virt;
	p_bulletin->req_स्वतःneg = params->speed.स्वतःneg;
	p_bulletin->req_adv_speed = params->speed.advertised_speeds;
	p_bulletin->req_क्रमced_speed = params->speed.क्रमced_speed;
	p_bulletin->req_स्वतःneg_छोड़ो = params->छोड़ो.स्वतःneg;
	p_bulletin->req_क्रमced_rx = params->छोड़ो.क्रमced_rx;
	p_bulletin->req_क्रमced_tx = params->छोड़ो.क्रमced_tx;
	p_bulletin->req_loopback = params->loopback_mode;

	p_bulletin->link_up = link->link_up;
	p_bulletin->speed = link->speed;
	p_bulletin->full_duplex = link->full_duplex;
	p_bulletin->स्वतःneg = link->an;
	p_bulletin->स्वतःneg_complete = link->an_complete;
	p_bulletin->parallel_detection = link->parallel_detection;
	p_bulletin->pfc_enabled = link->pfc_enabled;
	p_bulletin->partner_adv_speed = link->partner_adv_speed;
	p_bulletin->partner_tx_flow_ctrl_en = link->partner_tx_flow_ctrl_en;
	p_bulletin->partner_rx_flow_ctrl_en = link->partner_rx_flow_ctrl_en;
	p_bulletin->partner_adv_छोड़ो = link->partner_adv_छोड़ो;
	p_bulletin->sfp_tx_fault = link->sfp_tx_fault;

	p_bulletin->capability_speed = p_caps->speed_capabilities;
पूर्ण

अटल पूर्णांक qed_iov_init_hw_क्रम_vf(काष्ठा qed_hwfn *p_hwfn,
				  काष्ठा qed_ptt *p_ptt,
				  काष्ठा qed_iov_vf_init_params *p_params)
अणु
	काष्ठा qed_mcp_link_capabilities link_caps;
	काष्ठा qed_mcp_link_params link_params;
	काष्ठा qed_mcp_link_state link_state;
	u8 num_of_vf_avaiable_chains = 0;
	काष्ठा qed_vf_info *vf = शून्य;
	u16 qid, num_irqs;
	पूर्णांक rc = 0;
	u32 cids;
	u8 i;

	vf = qed_iov_get_vf_info(p_hwfn, p_params->rel_vf_id, false);
	अगर (!vf) अणु
		DP_ERR(p_hwfn, "qed_iov_init_hw_for_vf : vf is NULL\n");
		वापस -EINVAL;
	पूर्ण

	अगर (vf->b_init) अणु
		DP_NOTICE(p_hwfn, "VF[%d] is already active.\n",
			  p_params->rel_vf_id);
		वापस -EINVAL;
	पूर्ण

	/* Perक्रमm sanity checking on the requested queue_id */
	क्रम (i = 0; i < p_params->num_queues; i++) अणु
		u16 min_vf_qzone = FEAT_NUM(p_hwfn, QED_PF_L2_QUE);
		u16 max_vf_qzone = min_vf_qzone +
		    FEAT_NUM(p_hwfn, QED_VF_L2_QUE) - 1;

		qid = p_params->req_rx_queue[i];
		अगर (qid < min_vf_qzone || qid > max_vf_qzone) अणु
			DP_NOTICE(p_hwfn,
				  "Can't enable Rx qid [%04x] for VF[%d]: qids [0x%04x,...,0x%04x] available\n",
				  qid,
				  p_params->rel_vf_id,
				  min_vf_qzone, max_vf_qzone);
			वापस -EINVAL;
		पूर्ण

		qid = p_params->req_tx_queue[i];
		अगर (qid > max_vf_qzone) अणु
			DP_NOTICE(p_hwfn,
				  "Can't enable Tx qid [%04x] for VF[%d]: max qid 0x%04x\n",
				  qid, p_params->rel_vf_id, max_vf_qzone);
			वापस -EINVAL;
		पूर्ण

		/* If client *really* wants, Tx qid can be shared with PF */
		अगर (qid < min_vf_qzone)
			DP_VERBOSE(p_hwfn,
				   QED_MSG_IOV,
				   "VF[%d] is using PF qid [0x%04x] for Txq[0x%02x]\n",
				   p_params->rel_vf_id, qid, i);
	पूर्ण

	/* Limit number of queues according to number of CIDs */
	qed_cxt_get_proto_cid_count(p_hwfn, PROTOCOLID_ETH, &cids);
	DP_VERBOSE(p_hwfn,
		   QED_MSG_IOV,
		   "VF[%d] - requesting to initialize for 0x%04x queues [0x%04x CIDs available]\n",
		   vf->relative_vf_id, p_params->num_queues, (u16)cids);
	num_irqs = min_t(u16, p_params->num_queues, ((u16)cids));

	num_of_vf_avaiable_chains = qed_iov_alloc_vf_igu_sbs(p_hwfn,
							     p_ptt,
							     vf, num_irqs);
	अगर (!num_of_vf_avaiable_chains) अणु
		DP_ERR(p_hwfn, "no available igu sbs\n");
		वापस -ENOMEM;
	पूर्ण

	/* Choose queue number and index ranges */
	vf->num_rxqs = num_of_vf_avaiable_chains;
	vf->num_txqs = num_of_vf_avaiable_chains;

	क्रम (i = 0; i < vf->num_rxqs; i++) अणु
		काष्ठा qed_vf_queue *p_queue = &vf->vf_queues[i];

		p_queue->fw_rx_qid = p_params->req_rx_queue[i];
		p_queue->fw_tx_qid = p_params->req_tx_queue[i];

		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "VF[%d] - Q[%d] SB %04x, qid [Rx %04x Tx %04x]\n",
			   vf->relative_vf_id, i, vf->igu_sbs[i],
			   p_queue->fw_rx_qid, p_queue->fw_tx_qid);
	पूर्ण

	/* Update the link configuration in bulletin */
	स_नकल(&link_params, qed_mcp_get_link_params(p_hwfn),
	       माप(link_params));
	स_नकल(&link_state, qed_mcp_get_link_state(p_hwfn), माप(link_state));
	स_नकल(&link_caps, qed_mcp_get_link_capabilities(p_hwfn),
	       माप(link_caps));
	qed_iov_set_link(p_hwfn, p_params->rel_vf_id,
			 &link_params, &link_state, &link_caps);

	rc = qed_iov_enable_vf_access(p_hwfn, p_ptt, vf);
	अगर (!rc) अणु
		vf->b_init = true;

		अगर (IS_LEAD_HWFN(p_hwfn))
			p_hwfn->cdev->p_iov_info->num_vfs++;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक qed_iov_release_hw_क्रम_vf(काष्ठा qed_hwfn *p_hwfn,
				     काष्ठा qed_ptt *p_ptt, u16 rel_vf_id)
अणु
	काष्ठा qed_mcp_link_capabilities caps;
	काष्ठा qed_mcp_link_params params;
	काष्ठा qed_mcp_link_state link;
	काष्ठा qed_vf_info *vf = शून्य;

	vf = qed_iov_get_vf_info(p_hwfn, rel_vf_id, true);
	अगर (!vf) अणु
		DP_ERR(p_hwfn, "qed_iov_release_hw_for_vf : vf is NULL\n");
		वापस -EINVAL;
	पूर्ण

	अगर (vf->bulletin.p_virt)
		स_रखो(vf->bulletin.p_virt, 0, माप(*vf->bulletin.p_virt));

	स_रखो(&vf->p_vf_info, 0, माप(vf->p_vf_info));

	/* Get the link configuration back in bulletin so
	 * that when VFs are re-enabled they get the actual
	 * link configuration.
	 */
	स_नकल(&params, qed_mcp_get_link_params(p_hwfn), माप(params));
	स_नकल(&link, qed_mcp_get_link_state(p_hwfn), माप(link));
	स_नकल(&caps, qed_mcp_get_link_capabilities(p_hwfn), माप(caps));
	qed_iov_set_link(p_hwfn, rel_vf_id, &params, &link, &caps);

	/* Forget the VF's acquisition message */
	स_रखो(&vf->acquire, 0, माप(vf->acquire));

	/* disablng पूर्णांकerrupts and resetting permission table was करोne during
	 * vf-बंद, however, we could get here without going through vf_बंद
	 */
	/* Disable Interrupts क्रम VF */
	qed_iov_vf_igu_set_पूर्णांक(p_hwfn, p_ptt, vf, 0);

	/* Reset Permission table */
	qed_iov_config_perm_table(p_hwfn, p_ptt, vf, 0);

	vf->num_rxqs = 0;
	vf->num_txqs = 0;
	qed_iov_मुक्त_vf_igu_sbs(p_hwfn, p_ptt, vf);

	अगर (vf->b_init) अणु
		vf->b_init = false;

		अगर (IS_LEAD_HWFN(p_hwfn))
			p_hwfn->cdev->p_iov_info->num_vfs--;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool qed_iov_tlv_supported(u16 tlvtype)
अणु
	वापस CHANNEL_TLV_NONE < tlvtype && tlvtype < CHANNEL_TLV_MAX;
पूर्ण

/* place a given tlv on the tlv buffer, continuing current tlv list */
व्योम *qed_add_tlv(काष्ठा qed_hwfn *p_hwfn, u8 **offset, u16 type, u16 length)
अणु
	काष्ठा channel_tlv *tl = (काष्ठा channel_tlv *)*offset;

	tl->type = type;
	tl->length = length;

	/* Offset should keep poपूर्णांकing to next TLV (the end of the last) */
	*offset += length;

	/* Return a poपूर्णांकer to the start of the added tlv */
	वापस *offset - length;
पूर्ण

/* list the types and lengths of the tlvs on the buffer */
व्योम qed_dp_tlv_list(काष्ठा qed_hwfn *p_hwfn, व्योम *tlvs_list)
अणु
	u16 i = 1, total_length = 0;
	काष्ठा channel_tlv *tlv;

	करो अणु
		tlv = (काष्ठा channel_tlv *)((u8 *)tlvs_list + total_length);

		/* output tlv */
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "TLV number %d: type %d, length %d\n",
			   i, tlv->type, tlv->length);

		अगर (tlv->type == CHANNEL_TLV_LIST_END)
			वापस;

		/* Validate entry - protect against malicious VFs */
		अगर (!tlv->length) अणु
			DP_NOTICE(p_hwfn, "TLV of length 0 found\n");
			वापस;
		पूर्ण

		total_length += tlv->length;

		अगर (total_length >= माप(काष्ठा tlv_buffer_size)) अणु
			DP_NOTICE(p_hwfn, "TLV ==> Buffer overflow\n");
			वापस;
		पूर्ण

		i++;
	पूर्ण जबतक (1);
पूर्ण

अटल व्योम qed_iov_send_response(काष्ठा qed_hwfn *p_hwfn,
				  काष्ठा qed_ptt *p_ptt,
				  काष्ठा qed_vf_info *p_vf,
				  u16 length, u8 status)
अणु
	काष्ठा qed_iov_vf_mbx *mbx = &p_vf->vf_mbx;
	काष्ठा qed_dmae_params params;
	u8 eng_vf_id;

	mbx->reply_virt->शेष_resp.hdr.status = status;

	qed_dp_tlv_list(p_hwfn, mbx->reply_virt);

	eng_vf_id = p_vf->असल_vf_id;

	स_रखो(&params, 0, माप(params));
	SET_FIELD(params.flags, QED_DMAE_PARAMS_DST_VF_VALID, 0x1);
	params.dst_vfid = eng_vf_id;

	qed_dmae_host2host(p_hwfn, p_ptt, mbx->reply_phys + माप(u64),
			   mbx->req_virt->first_tlv.reply_address +
			   माप(u64),
			   (माप(जोड़ pfvf_tlvs) - माप(u64)) / 4,
			   &params);

	/* Once PF copies the rc to the VF, the latter can जारी
	 * and send an additional message. So we have to make sure the
	 * channel would be re-set to पढ़ोy prior to that.
	 */
	REG_WR(p_hwfn,
	       GTT_BAR0_MAP_REG_USDM_RAM +
	       USTORM_VF_PF_CHANNEL_READY_OFFSET(eng_vf_id), 1);

	qed_dmae_host2host(p_hwfn, p_ptt, mbx->reply_phys,
			   mbx->req_virt->first_tlv.reply_address,
			   माप(u64) / 4, &params);
पूर्ण

अटल u16 qed_iov_vport_to_tlv(काष्ठा qed_hwfn *p_hwfn,
				क्रमागत qed_iov_vport_update_flag flag)
अणु
	चयन (flag) अणु
	हाल QED_IOV_VP_UPDATE_ACTIVATE:
		वापस CHANNEL_TLV_VPORT_UPDATE_ACTIVATE;
	हाल QED_IOV_VP_UPDATE_VLAN_STRIP:
		वापस CHANNEL_TLV_VPORT_UPDATE_VLAN_STRIP;
	हाल QED_IOV_VP_UPDATE_TX_SWITCH:
		वापस CHANNEL_TLV_VPORT_UPDATE_TX_SWITCH;
	हाल QED_IOV_VP_UPDATE_MCAST:
		वापस CHANNEL_TLV_VPORT_UPDATE_MCAST;
	हाल QED_IOV_VP_UPDATE_ACCEPT_PARAM:
		वापस CHANNEL_TLV_VPORT_UPDATE_ACCEPT_PARAM;
	हाल QED_IOV_VP_UPDATE_RSS:
		वापस CHANNEL_TLV_VPORT_UPDATE_RSS;
	हाल QED_IOV_VP_UPDATE_ACCEPT_ANY_VLAN:
		वापस CHANNEL_TLV_VPORT_UPDATE_ACCEPT_ANY_VLAN;
	हाल QED_IOV_VP_UPDATE_SGE_TPA:
		वापस CHANNEL_TLV_VPORT_UPDATE_SGE_TPA;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल u16 qed_iov_prep_vp_update_resp_tlvs(काष्ठा qed_hwfn *p_hwfn,
					    काष्ठा qed_vf_info *p_vf,
					    काष्ठा qed_iov_vf_mbx *p_mbx,
					    u8 status,
					    u16 tlvs_mask, u16 tlvs_accepted)
अणु
	काष्ठा pfvf_def_resp_tlv *resp;
	u16 size, total_len, i;

	स_रखो(p_mbx->reply_virt, 0, माप(जोड़ pfvf_tlvs));
	p_mbx->offset = (u8 *)p_mbx->reply_virt;
	size = माप(काष्ठा pfvf_def_resp_tlv);
	total_len = size;

	qed_add_tlv(p_hwfn, &p_mbx->offset, CHANNEL_TLV_VPORT_UPDATE, size);

	/* Prepare response क्रम all extended tlvs अगर they are found by PF */
	क्रम (i = 0; i < QED_IOV_VP_UPDATE_MAX; i++) अणु
		अगर (!(tlvs_mask & BIT(i)))
			जारी;

		resp = qed_add_tlv(p_hwfn, &p_mbx->offset,
				   qed_iov_vport_to_tlv(p_hwfn, i), size);

		अगर (tlvs_accepted & BIT(i))
			resp->hdr.status = status;
		अन्यथा
			resp->hdr.status = PFVF_STATUS_NOT_SUPPORTED;

		DP_VERBOSE(p_hwfn,
			   QED_MSG_IOV,
			   "VF[%d] - vport_update response: TLV %d, status %02x\n",
			   p_vf->relative_vf_id,
			   qed_iov_vport_to_tlv(p_hwfn, i), resp->hdr.status);

		total_len += size;
	पूर्ण

	qed_add_tlv(p_hwfn, &p_mbx->offset, CHANNEL_TLV_LIST_END,
		    माप(काष्ठा channel_list_end_tlv));

	वापस total_len;
पूर्ण

अटल व्योम qed_iov_prepare_resp(काष्ठा qed_hwfn *p_hwfn,
				 काष्ठा qed_ptt *p_ptt,
				 काष्ठा qed_vf_info *vf_info,
				 u16 type, u16 length, u8 status)
अणु
	काष्ठा qed_iov_vf_mbx *mbx = &vf_info->vf_mbx;

	mbx->offset = (u8 *)mbx->reply_virt;

	qed_add_tlv(p_hwfn, &mbx->offset, type, length);
	qed_add_tlv(p_hwfn, &mbx->offset, CHANNEL_TLV_LIST_END,
		    माप(काष्ठा channel_list_end_tlv));

	qed_iov_send_response(p_hwfn, p_ptt, vf_info, length, status);
पूर्ण

अटल काष्ठा
qed_खुला_vf_info *qed_iov_get_खुला_vf_info(काष्ठा qed_hwfn *p_hwfn,
					       u16 relative_vf_id,
					       bool b_enabled_only)
अणु
	काष्ठा qed_vf_info *vf = शून्य;

	vf = qed_iov_get_vf_info(p_hwfn, relative_vf_id, b_enabled_only);
	अगर (!vf)
		वापस शून्य;

	वापस &vf->p_vf_info;
पूर्ण

अटल व्योम qed_iov_clean_vf(काष्ठा qed_hwfn *p_hwfn, u8 vfid)
अणु
	काष्ठा qed_खुला_vf_info *vf_info;

	vf_info = qed_iov_get_खुला_vf_info(p_hwfn, vfid, false);

	अगर (!vf_info)
		वापस;

	/* Clear the VF mac */
	eth_zero_addr(vf_info->mac);

	vf_info->rx_accept_mode = 0;
	vf_info->tx_accept_mode = 0;
पूर्ण

अटल व्योम qed_iov_vf_cleanup(काष्ठा qed_hwfn *p_hwfn,
			       काष्ठा qed_vf_info *p_vf)
अणु
	u32 i, j;

	p_vf->vf_bulletin = 0;
	p_vf->vport_instance = 0;
	p_vf->configured_features = 0;

	/* If VF previously requested less resources, go back to शेष */
	p_vf->num_rxqs = p_vf->num_sbs;
	p_vf->num_txqs = p_vf->num_sbs;

	p_vf->num_active_rxqs = 0;

	क्रम (i = 0; i < QED_MAX_VF_CHAINS_PER_PF; i++) अणु
		काष्ठा qed_vf_queue *p_queue = &p_vf->vf_queues[i];

		क्रम (j = 0; j < MAX_QUEUES_PER_QZONE; j++) अणु
			अगर (!p_queue->cids[j].p_cid)
				जारी;

			qed_eth_queue_cid_release(p_hwfn,
						  p_queue->cids[j].p_cid);
			p_queue->cids[j].p_cid = शून्य;
		पूर्ण
	पूर्ण

	स_रखो(&p_vf->shaकरोw_config, 0, माप(p_vf->shaकरोw_config));
	स_रखो(&p_vf->acquire, 0, माप(p_vf->acquire));
	qed_iov_clean_vf(p_hwfn, p_vf->relative_vf_id);
पूर्ण

/* Returns either 0, or log(size) */
अटल u32 qed_iov_vf_db_bar_size(काष्ठा qed_hwfn *p_hwfn,
				  काष्ठा qed_ptt *p_ptt)
अणु
	u32 val = qed_rd(p_hwfn, p_ptt, PGLUE_B_REG_VF_BAR1_SIZE);

	अगर (val)
		वापस val + 11;
	वापस 0;
पूर्ण

अटल व्योम
qed_iov_vf_mbx_acquire_resc_cids(काष्ठा qed_hwfn *p_hwfn,
				 काष्ठा qed_ptt *p_ptt,
				 काष्ठा qed_vf_info *p_vf,
				 काष्ठा vf_pf_resc_request *p_req,
				 काष्ठा pf_vf_resc *p_resp)
अणु
	u8 num_vf_cons = p_hwfn->pf_params.eth_pf_params.num_vf_cons;
	u8 db_size = qed_db_addr_vf(1, DQ_DEMS_LEGACY) -
		     qed_db_addr_vf(0, DQ_DEMS_LEGACY);
	u32 bar_size;

	p_resp->num_cids = min_t(u8, p_req->num_cids, num_vf_cons);

	/* If VF didn't bother asking for QIDs than don't bother limiting
	 * number of CIDs. The VF करोesn't care about the number, and this
	 * has the likely result of causing an additional acquisition.
	 */
	अगर (!(p_vf->acquire.vfdev_info.capabilities &
	      VFPF_ACQUIRE_CAP_QUEUE_QIDS))
		वापस;

	/* If करोorbell bar was mapped by VF, limit the VF CIDs to an amount
	 * that would make sure करोorbells क्रम all CIDs fall within the bar.
	 * If it करोesn't, make sure regview winकरोw is sufficient.
	 */
	अगर (p_vf->acquire.vfdev_info.capabilities &
	    VFPF_ACQUIRE_CAP_PHYSICAL_BAR) अणु
		bar_size = qed_iov_vf_db_bar_size(p_hwfn, p_ptt);
		अगर (bar_size)
			bar_size = 1 << bar_size;

		अगर (p_hwfn->cdev->num_hwfns > 1)
			bar_size /= 2;
	पूर्ण अन्यथा अणु
		bar_size = PXP_VF_BAR0_DQ_LENGTH;
	पूर्ण

	अगर (bar_size / db_size < 256)
		p_resp->num_cids = min_t(u8, p_resp->num_cids,
					 (u8)(bar_size / db_size));
पूर्ण

अटल u8 qed_iov_vf_mbx_acquire_resc(काष्ठा qed_hwfn *p_hwfn,
				      काष्ठा qed_ptt *p_ptt,
				      काष्ठा qed_vf_info *p_vf,
				      काष्ठा vf_pf_resc_request *p_req,
				      काष्ठा pf_vf_resc *p_resp)
अणु
	u8 i;

	/* Queue related inक्रमmation */
	p_resp->num_rxqs = p_vf->num_rxqs;
	p_resp->num_txqs = p_vf->num_txqs;
	p_resp->num_sbs = p_vf->num_sbs;

	क्रम (i = 0; i < p_resp->num_sbs; i++) अणु
		p_resp->hw_sbs[i].hw_sb_id = p_vf->igu_sbs[i];
		p_resp->hw_sbs[i].sb_qid = 0;
	पूर्ण

	/* These fields are filled क्रम backward compatibility.
	 * Unused by modern vfs.
	 */
	क्रम (i = 0; i < p_resp->num_rxqs; i++) अणु
		qed_fw_l2_queue(p_hwfn, p_vf->vf_queues[i].fw_rx_qid,
				(u16 *)&p_resp->hw_qid[i]);
		p_resp->cid[i] = i;
	पूर्ण

	/* Filter related inक्रमmation */
	p_resp->num_mac_filters = min_t(u8, p_vf->num_mac_filters,
					p_req->num_mac_filters);
	p_resp->num_vlan_filters = min_t(u8, p_vf->num_vlan_filters,
					 p_req->num_vlan_filters);

	qed_iov_vf_mbx_acquire_resc_cids(p_hwfn, p_ptt, p_vf, p_req, p_resp);

	/* This isn't really needed/enक्रमced, but some legacy VFs might depend
	 * on the correct filling of this field.
	 */
	p_resp->num_mc_filters = QED_MAX_MC_ADDRS;

	/* Validate sufficient resources क्रम VF */
	अगर (p_resp->num_rxqs < p_req->num_rxqs ||
	    p_resp->num_txqs < p_req->num_txqs ||
	    p_resp->num_sbs < p_req->num_sbs ||
	    p_resp->num_mac_filters < p_req->num_mac_filters ||
	    p_resp->num_vlan_filters < p_req->num_vlan_filters ||
	    p_resp->num_mc_filters < p_req->num_mc_filters ||
	    p_resp->num_cids < p_req->num_cids) अणु
		DP_VERBOSE(p_hwfn,
			   QED_MSG_IOV,
			   "VF[%d] - Insufficient resources: rxq [%02x/%02x] txq [%02x/%02x] sbs [%02x/%02x] mac [%02x/%02x] vlan [%02x/%02x] mc [%02x/%02x] cids [%02x/%02x]\n",
			   p_vf->असल_vf_id,
			   p_req->num_rxqs,
			   p_resp->num_rxqs,
			   p_req->num_rxqs,
			   p_resp->num_txqs,
			   p_req->num_sbs,
			   p_resp->num_sbs,
			   p_req->num_mac_filters,
			   p_resp->num_mac_filters,
			   p_req->num_vlan_filters,
			   p_resp->num_vlan_filters,
			   p_req->num_mc_filters,
			   p_resp->num_mc_filters,
			   p_req->num_cids, p_resp->num_cids);

		/* Some legacy OSes are incapable of correctly handling this
		 * failure.
		 */
		अगर ((p_vf->acquire.vfdev_info.eth_fp_hsi_minor ==
		     ETH_HSI_VER_NO_PKT_LEN_TUNN) &&
		    (p_vf->acquire.vfdev_info.os_type ==
		     VFPF_ACQUIRE_OS_WINDOWS))
			वापस PFVF_STATUS_SUCCESS;

		वापस PFVF_STATUS_NO_RESOURCE;
	पूर्ण

	वापस PFVF_STATUS_SUCCESS;
पूर्ण

अटल व्योम qed_iov_vf_mbx_acquire_stats(काष्ठा qed_hwfn *p_hwfn,
					 काष्ठा pfvf_stats_info *p_stats)
अणु
	p_stats->mstats.address = PXP_VF_BAR0_START_MSDM_ZONE_B +
				  दुरत्व(काष्ठा mstorm_vf_zone,
					   non_trigger.eth_queue_stat);
	p_stats->mstats.len = माप(काष्ठा eth_mstorm_per_queue_stat);
	p_stats->ustats.address = PXP_VF_BAR0_START_USDM_ZONE_B +
				  दुरत्व(काष्ठा ustorm_vf_zone,
					   non_trigger.eth_queue_stat);
	p_stats->ustats.len = माप(काष्ठा eth_ustorm_per_queue_stat);
	p_stats->pstats.address = PXP_VF_BAR0_START_PSDM_ZONE_B +
				  दुरत्व(काष्ठा pstorm_vf_zone,
					   non_trigger.eth_queue_stat);
	p_stats->pstats.len = माप(काष्ठा eth_pstorm_per_queue_stat);
	p_stats->tstats.address = 0;
	p_stats->tstats.len = 0;
पूर्ण

अटल व्योम qed_iov_vf_mbx_acquire(काष्ठा qed_hwfn *p_hwfn,
				   काष्ठा qed_ptt *p_ptt,
				   काष्ठा qed_vf_info *vf)
अणु
	काष्ठा qed_iov_vf_mbx *mbx = &vf->vf_mbx;
	काष्ठा pfvf_acquire_resp_tlv *resp = &mbx->reply_virt->acquire_resp;
	काष्ठा pf_vf_pfdev_info *pfdev_info = &resp->pfdev_info;
	काष्ठा vfpf_acquire_tlv *req = &mbx->req_virt->acquire;
	u8 vfpf_status = PFVF_STATUS_NOT_SUPPORTED;
	काष्ठा pf_vf_resc *resc = &resp->resc;
	पूर्णांक rc;

	स_रखो(resp, 0, माप(*resp));

	/* Write the PF version so that VF would know which version
	 * is supported - might be later overriden. This guarantees that
	 * VF could recognize legacy PF based on lack of versions in reply.
	 */
	pfdev_info->major_fp_hsi = ETH_HSI_VER_MAJOR;
	pfdev_info->minor_fp_hsi = ETH_HSI_VER_MINOR;

	अगर (vf->state != VF_FREE && vf->state != VF_STOPPED) अणु
		DP_VERBOSE(p_hwfn,
			   QED_MSG_IOV,
			   "VF[%d] sent ACQUIRE but is already in state %d - fail request\n",
			   vf->असल_vf_id, vf->state);
		जाओ out;
	पूर्ण

	/* Validate FW compatibility */
	अगर (req->vfdev_info.eth_fp_hsi_major != ETH_HSI_VER_MAJOR) अणु
		अगर (req->vfdev_info.capabilities &
		    VFPF_ACQUIRE_CAP_PRE_FP_HSI) अणु
			काष्ठा vf_pf_vfdev_info *p_vfdev = &req->vfdev_info;

			DP_VERBOSE(p_hwfn, QED_MSG_IOV,
				   "VF[%d] is pre-fastpath HSI\n",
				   vf->असल_vf_id);
			p_vfdev->eth_fp_hsi_major = ETH_HSI_VER_MAJOR;
			p_vfdev->eth_fp_hsi_minor = ETH_HSI_VER_NO_PKT_LEN_TUNN;
		पूर्ण अन्यथा अणु
			DP_INFO(p_hwfn,
				"VF[%d] needs fastpath HSI %02x.%02x, which is incompatible with loaded FW's fastpath HSI %02x.%02x\n",
				vf->असल_vf_id,
				req->vfdev_info.eth_fp_hsi_major,
				req->vfdev_info.eth_fp_hsi_minor,
				ETH_HSI_VER_MAJOR, ETH_HSI_VER_MINOR);

			जाओ out;
		पूर्ण
	पूर्ण

	/* On 100g PFs, prevent old VFs from loading */
	अगर ((p_hwfn->cdev->num_hwfns > 1) &&
	    !(req->vfdev_info.capabilities & VFPF_ACQUIRE_CAP_100G)) अणु
		DP_INFO(p_hwfn,
			"VF[%d] is running an old driver that doesn't support 100g\n",
			vf->असल_vf_id);
		जाओ out;
	पूर्ण

	/* Store the acquire message */
	स_नकल(&vf->acquire, req, माप(vf->acquire));

	vf->opaque_fid = req->vfdev_info.opaque_fid;

	vf->vf_bulletin = req->bulletin_addr;
	vf->bulletin.size = (vf->bulletin.size < req->bulletin_size) ?
			    vf->bulletin.size : req->bulletin_size;

	/* fill in pfdev info */
	pfdev_info->chip_num = p_hwfn->cdev->chip_num;
	pfdev_info->db_size = 0;
	pfdev_info->indices_per_sb = PIS_PER_SB_E4;

	pfdev_info->capabilities = PFVF_ACQUIRE_CAP_DEFAULT_UNTAGGED |
				   PFVF_ACQUIRE_CAP_POST_FW_OVERRIDE;
	अगर (p_hwfn->cdev->num_hwfns > 1)
		pfdev_info->capabilities |= PFVF_ACQUIRE_CAP_100G;

	/* Share our ability to use multiple queue-ids only with VFs
	 * that request it.
	 */
	अगर (req->vfdev_info.capabilities & VFPF_ACQUIRE_CAP_QUEUE_QIDS)
		pfdev_info->capabilities |= PFVF_ACQUIRE_CAP_QUEUE_QIDS;

	/* Share the sizes of the bars with VF */
	resp->pfdev_info.bar_size = qed_iov_vf_db_bar_size(p_hwfn, p_ptt);

	qed_iov_vf_mbx_acquire_stats(p_hwfn, &pfdev_info->stats_info);

	स_नकल(pfdev_info->port_mac, p_hwfn->hw_info.hw_mac_addr, ETH_ALEN);

	pfdev_info->fw_major = FW_MAJOR_VERSION;
	pfdev_info->fw_minor = FW_MINOR_VERSION;
	pfdev_info->fw_rev = FW_REVISION_VERSION;
	pfdev_info->fw_eng = FW_ENGINEERING_VERSION;

	/* Incorrect when legacy, but करोesn't matter as legacy isn't पढ़ोing
	 * this field.
	 */
	pfdev_info->minor_fp_hsi = min_t(u8, ETH_HSI_VER_MINOR,
					 req->vfdev_info.eth_fp_hsi_minor);
	pfdev_info->os_type = VFPF_ACQUIRE_OS_LINUX;
	qed_mcp_get_mfw_ver(p_hwfn, p_ptt, &pfdev_info->mfw_ver, शून्य);

	pfdev_info->dev_type = p_hwfn->cdev->type;
	pfdev_info->chip_rev = p_hwfn->cdev->chip_rev;

	/* Fill resources available to VF; Make sure there are enough to
	 * satisfy the VF's request.
	 */
	vfpf_status = qed_iov_vf_mbx_acquire_resc(p_hwfn, p_ptt, vf,
						  &req->resc_request, resc);
	अगर (vfpf_status != PFVF_STATUS_SUCCESS)
		जाओ out;

	/* Start the VF in FW */
	rc = qed_sp_vf_start(p_hwfn, vf);
	अगर (rc) अणु
		DP_NOTICE(p_hwfn, "Failed to start VF[%02x]\n", vf->असल_vf_id);
		vfpf_status = PFVF_STATUS_FAILURE;
		जाओ out;
	पूर्ण

	/* Fill agreed size of bulletin board in response */
	resp->bulletin_size = vf->bulletin.size;
	qed_iov_post_vf_bulletin(p_hwfn, vf->relative_vf_id, p_ptt);

	DP_VERBOSE(p_hwfn,
		   QED_MSG_IOV,
		   "VF[%d] ACQUIRE_RESPONSE: pfdev_info- chip_num=0x%x, db_size=%d, idx_per_sb=%d, pf_cap=0x%llx\n"
		   "resources- n_rxq-%d, n_txq-%d, n_sbs-%d, n_macs-%d, n_vlans-%d\n",
		   vf->असल_vf_id,
		   resp->pfdev_info.chip_num,
		   resp->pfdev_info.db_size,
		   resp->pfdev_info.indices_per_sb,
		   resp->pfdev_info.capabilities,
		   resc->num_rxqs,
		   resc->num_txqs,
		   resc->num_sbs,
		   resc->num_mac_filters,
		   resc->num_vlan_filters);
	vf->state = VF_ACQUIRED;

	/* Prepare Response */
out:
	qed_iov_prepare_resp(p_hwfn, p_ptt, vf, CHANNEL_TLV_ACQUIRE,
			     माप(काष्ठा pfvf_acquire_resp_tlv), vfpf_status);
पूर्ण

अटल पूर्णांक __qed_iov_spoofchk_set(काष्ठा qed_hwfn *p_hwfn,
				  काष्ठा qed_vf_info *p_vf, bool val)
अणु
	काष्ठा qed_sp_vport_update_params params;
	पूर्णांक rc;

	अगर (val == p_vf->spoof_chk) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "Spoofchk value[%d] is already configured\n", val);
		वापस 0;
	पूर्ण

	स_रखो(&params, 0, माप(काष्ठा qed_sp_vport_update_params));
	params.opaque_fid = p_vf->opaque_fid;
	params.vport_id = p_vf->vport_id;
	params.update_anti_spoofing_en_flg = 1;
	params.anti_spoofing_en = val;

	rc = qed_sp_vport_update(p_hwfn, &params, QED_SPQ_MODE_EBLOCK, शून्य);
	अगर (!rc) अणु
		p_vf->spoof_chk = val;
		p_vf->req_spoofchk_val = p_vf->spoof_chk;
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "Spoofchk val[%d] configured\n", val);
	पूर्ण अन्यथा अणु
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "Spoofchk configuration[val:%d] failed for VF[%d]\n",
			   val, p_vf->relative_vf_id);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक qed_iov_reconfigure_unicast_vlan(काष्ठा qed_hwfn *p_hwfn,
					    काष्ठा qed_vf_info *p_vf)
अणु
	काष्ठा qed_filter_ucast filter;
	पूर्णांक rc = 0;
	पूर्णांक i;

	स_रखो(&filter, 0, माप(filter));
	filter.is_rx_filter = 1;
	filter.is_tx_filter = 1;
	filter.vport_to_add_to = p_vf->vport_id;
	filter.opcode = QED_FILTER_ADD;

	/* Reconfigure vlans */
	क्रम (i = 0; i < QED_ETH_VF_NUM_VLAN_FILTERS + 1; i++) अणु
		अगर (!p_vf->shaकरोw_config.vlans[i].used)
			जारी;

		filter.type = QED_FILTER_VLAN;
		filter.vlan = p_vf->shaकरोw_config.vlans[i].vid;
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "Reconfiguring VLAN [0x%04x] for VF [%04x]\n",
			   filter.vlan, p_vf->relative_vf_id);
		rc = qed_sp_eth_filter_ucast(p_hwfn, p_vf->opaque_fid,
					     &filter, QED_SPQ_MODE_CB, शून्य);
		अगर (rc) अणु
			DP_NOTICE(p_hwfn,
				  "Failed to configure VLAN [%04x] to VF [%04x]\n",
				  filter.vlan, p_vf->relative_vf_id);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक
qed_iov_reconfigure_unicast_shaकरोw(काष्ठा qed_hwfn *p_hwfn,
				   काष्ठा qed_vf_info *p_vf, u64 events)
अणु
	पूर्णांक rc = 0;

	अगर ((events & BIT(VLAN_ADDR_FORCED)) &&
	    !(p_vf->configured_features & (1 << VLAN_ADDR_FORCED)))
		rc = qed_iov_reconfigure_unicast_vlan(p_hwfn, p_vf);

	वापस rc;
पूर्ण

अटल पूर्णांक qed_iov_configure_vport_क्रमced(काष्ठा qed_hwfn *p_hwfn,
					  काष्ठा qed_vf_info *p_vf, u64 events)
अणु
	पूर्णांक rc = 0;
	काष्ठा qed_filter_ucast filter;

	अगर (!p_vf->vport_instance)
		वापस -EINVAL;

	अगर ((events & BIT(MAC_ADDR_FORCED)) ||
	    p_vf->p_vf_info.is_trusted_configured) अणु
		/* Since there's no way [currently] of removing the MAC,
		 * we can always assume this means we need to क्रमce it.
		 */
		स_रखो(&filter, 0, माप(filter));
		filter.type = QED_FILTER_MAC;
		filter.opcode = QED_FILTER_REPLACE;
		filter.is_rx_filter = 1;
		filter.is_tx_filter = 1;
		filter.vport_to_add_to = p_vf->vport_id;
		ether_addr_copy(filter.mac, p_vf->bulletin.p_virt->mac);

		rc = qed_sp_eth_filter_ucast(p_hwfn, p_vf->opaque_fid,
					     &filter, QED_SPQ_MODE_CB, शून्य);
		अगर (rc) अणु
			DP_NOTICE(p_hwfn,
				  "PF failed to configure MAC for VF\n");
			वापस rc;
		पूर्ण
		अगर (p_vf->p_vf_info.is_trusted_configured)
			p_vf->configured_features |=
				BIT(VFPF_BULLETIN_MAC_ADDR);
		अन्यथा
			p_vf->configured_features |=
				BIT(MAC_ADDR_FORCED);
	पूर्ण

	अगर (events & BIT(VLAN_ADDR_FORCED)) अणु
		काष्ठा qed_sp_vport_update_params vport_update;
		u8 removal;
		पूर्णांक i;

		स_रखो(&filter, 0, माप(filter));
		filter.type = QED_FILTER_VLAN;
		filter.is_rx_filter = 1;
		filter.is_tx_filter = 1;
		filter.vport_to_add_to = p_vf->vport_id;
		filter.vlan = p_vf->bulletin.p_virt->pvid;
		filter.opcode = filter.vlan ? QED_FILTER_REPLACE :
					      QED_FILTER_FLUSH;

		/* Send the ramrod */
		rc = qed_sp_eth_filter_ucast(p_hwfn, p_vf->opaque_fid,
					     &filter, QED_SPQ_MODE_CB, शून्य);
		अगर (rc) अणु
			DP_NOTICE(p_hwfn,
				  "PF failed to configure VLAN for VF\n");
			वापस rc;
		पूर्ण

		/* Update the शेष-vlan & silent vlan stripping */
		स_रखो(&vport_update, 0, माप(vport_update));
		vport_update.opaque_fid = p_vf->opaque_fid;
		vport_update.vport_id = p_vf->vport_id;
		vport_update.update_शेष_vlan_enable_flg = 1;
		vport_update.शेष_vlan_enable_flg = filter.vlan ? 1 : 0;
		vport_update.update_शेष_vlan_flg = 1;
		vport_update.शेष_vlan = filter.vlan;

		vport_update.update_inner_vlan_removal_flg = 1;
		removal = filter.vlan ? 1
				      : p_vf->shaकरोw_config.inner_vlan_removal;
		vport_update.inner_vlan_removal_flg = removal;
		vport_update.silent_vlan_removal_flg = filter.vlan ? 1 : 0;
		rc = qed_sp_vport_update(p_hwfn,
					 &vport_update,
					 QED_SPQ_MODE_EBLOCK, शून्य);
		अगर (rc) अणु
			DP_NOTICE(p_hwfn,
				  "PF failed to configure VF vport for vlan\n");
			वापस rc;
		पूर्ण

		/* Update all the Rx queues */
		क्रम (i = 0; i < QED_MAX_VF_CHAINS_PER_PF; i++) अणु
			काष्ठा qed_vf_queue *p_queue = &p_vf->vf_queues[i];
			काष्ठा qed_queue_cid *p_cid = शून्य;

			/* There can be at most 1 Rx queue on qzone. Find it */
			p_cid = qed_iov_get_vf_rx_queue_cid(p_queue);
			अगर (!p_cid)
				जारी;

			rc = qed_sp_eth_rx_queues_update(p_hwfn,
							 (व्योम **)&p_cid,
							 1, 0, 1,
							 QED_SPQ_MODE_EBLOCK,
							 शून्य);
			अगर (rc) अणु
				DP_NOTICE(p_hwfn,
					  "Failed to send Rx update fo queue[0x%04x]\n",
					  p_cid->rel.queue_id);
				वापस rc;
			पूर्ण
		पूर्ण

		अगर (filter.vlan)
			p_vf->configured_features |= 1 << VLAN_ADDR_FORCED;
		अन्यथा
			p_vf->configured_features &= ~BIT(VLAN_ADDR_FORCED);
	पूर्ण

	/* If क्रमced features are terminated, we need to configure the shaकरोw
	 * configuration back again.
	 */
	अगर (events)
		qed_iov_reconfigure_unicast_shaकरोw(p_hwfn, p_vf, events);

	वापस rc;
पूर्ण

अटल व्योम qed_iov_vf_mbx_start_vport(काष्ठा qed_hwfn *p_hwfn,
				       काष्ठा qed_ptt *p_ptt,
				       काष्ठा qed_vf_info *vf)
अणु
	काष्ठा qed_sp_vport_start_params params = अणु 0 पूर्ण;
	काष्ठा qed_iov_vf_mbx *mbx = &vf->vf_mbx;
	काष्ठा vfpf_vport_start_tlv *start;
	u8 status = PFVF_STATUS_SUCCESS;
	काष्ठा qed_vf_info *vf_info;
	u64 *p_biपंचांगap;
	पूर्णांक sb_id;
	पूर्णांक rc;

	vf_info = qed_iov_get_vf_info(p_hwfn, (u16) vf->relative_vf_id, true);
	अगर (!vf_info) अणु
		DP_NOTICE(p_hwfn->cdev,
			  "Failed to get VF info, invalid vfid [%d]\n",
			  vf->relative_vf_id);
		वापस;
	पूर्ण

	vf->state = VF_ENABLED;
	start = &mbx->req_virt->start_vport;

	qed_iov_enable_vf_traffic(p_hwfn, p_ptt, vf);

	/* Initialize Status block in CAU */
	क्रम (sb_id = 0; sb_id < vf->num_sbs; sb_id++) अणु
		अगर (!start->sb_addr[sb_id]) अणु
			DP_VERBOSE(p_hwfn, QED_MSG_IOV,
				   "VF[%d] did not fill the address of SB %d\n",
				   vf->relative_vf_id, sb_id);
			अवरोध;
		पूर्ण

		qed_पूर्णांक_cau_conf_sb(p_hwfn, p_ptt,
				    start->sb_addr[sb_id],
				    vf->igu_sbs[sb_id], vf->असल_vf_id, 1);
	पूर्ण

	vf->mtu = start->mtu;
	vf->shaकरोw_config.inner_vlan_removal = start->inner_vlan_removal;

	/* Take पूर्णांकo consideration configuration क्रमced by hypervisor;
	 * If none is configured, use the supplied VF values [क्रम old
	 * vfs that would still be fine, since they passed '0' as padding].
	 */
	p_biपंचांगap = &vf_info->bulletin.p_virt->valid_biपंचांगap;
	अगर (!(*p_biपंचांगap & BIT(VFPF_BULLETIN_UNTAGGED_DEFAULT_FORCED))) अणु
		u8 vf_req = start->only_untagged;

		vf_info->bulletin.p_virt->शेष_only_untagged = vf_req;
		*p_biपंचांगap |= 1 << VFPF_BULLETIN_UNTAGGED_DEFAULT;
	पूर्ण

	params.tpa_mode = start->tpa_mode;
	params.हटाओ_inner_vlan = start->inner_vlan_removal;
	params.tx_चयनing = true;

	params.only_untagged = vf_info->bulletin.p_virt->शेष_only_untagged;
	params.drop_ttl0 = false;
	params.concrete_fid = vf->concrete_fid;
	params.opaque_fid = vf->opaque_fid;
	params.vport_id = vf->vport_id;
	params.max_buffers_per_cqe = start->max_buffers_per_cqe;
	params.mtu = vf->mtu;

	/* Non trusted VFs should enable control frame filtering */
	params.check_mac = !vf->p_vf_info.is_trusted_configured;

	rc = qed_sp_eth_vport_start(p_hwfn, &params);
	अगर (rc) अणु
		DP_ERR(p_hwfn,
		       "qed_iov_vf_mbx_start_vport returned error %d\n", rc);
		status = PFVF_STATUS_FAILURE;
	पूर्ण अन्यथा अणु
		vf->vport_instance++;

		/* Force configuration अगर needed on the newly खोलोed vport */
		qed_iov_configure_vport_क्रमced(p_hwfn, vf, *p_biपंचांगap);

		__qed_iov_spoofchk_set(p_hwfn, vf, vf->req_spoofchk_val);
	पूर्ण
	qed_iov_prepare_resp(p_hwfn, p_ptt, vf, CHANNEL_TLV_VPORT_START,
			     माप(काष्ठा pfvf_def_resp_tlv), status);
पूर्ण

अटल व्योम qed_iov_vf_mbx_stop_vport(काष्ठा qed_hwfn *p_hwfn,
				      काष्ठा qed_ptt *p_ptt,
				      काष्ठा qed_vf_info *vf)
अणु
	u8 status = PFVF_STATUS_SUCCESS;
	पूर्णांक rc;

	vf->vport_instance--;
	vf->spoof_chk = false;

	अगर ((qed_iov_validate_active_rxq(p_hwfn, vf)) ||
	    (qed_iov_validate_active_txq(p_hwfn, vf))) अणु
		vf->b_malicious = true;
		DP_NOTICE(p_hwfn,
			  "VF [%02x] - considered malicious; Unable to stop RX/TX queues\n",
			  vf->असल_vf_id);
		status = PFVF_STATUS_MALICIOUS;
		जाओ out;
	पूर्ण

	rc = qed_sp_vport_stop(p_hwfn, vf->opaque_fid, vf->vport_id);
	अगर (rc) अणु
		DP_ERR(p_hwfn, "qed_iov_vf_mbx_stop_vport returned error %d\n",
		       rc);
		status = PFVF_STATUS_FAILURE;
	पूर्ण

	/* Forget the configuration on the vport */
	vf->configured_features = 0;
	स_रखो(&vf->shaकरोw_config, 0, माप(vf->shaकरोw_config));

out:
	qed_iov_prepare_resp(p_hwfn, p_ptt, vf, CHANNEL_TLV_VPORT_TEARDOWN,
			     माप(काष्ठा pfvf_def_resp_tlv), status);
पूर्ण

अटल व्योम qed_iov_vf_mbx_start_rxq_resp(काष्ठा qed_hwfn *p_hwfn,
					  काष्ठा qed_ptt *p_ptt,
					  काष्ठा qed_vf_info *vf,
					  u8 status, bool b_legacy)
अणु
	काष्ठा qed_iov_vf_mbx *mbx = &vf->vf_mbx;
	काष्ठा pfvf_start_queue_resp_tlv *p_tlv;
	काष्ठा vfpf_start_rxq_tlv *req;
	u16 length;

	mbx->offset = (u8 *)mbx->reply_virt;

	/* Taking a bigger काष्ठा instead of adding a TLV to list was a
	 * mistake, but one which we're now stuck with, as some older
	 * clients assume the size of the previous response.
	 */
	अगर (!b_legacy)
		length = माप(*p_tlv);
	अन्यथा
		length = माप(काष्ठा pfvf_def_resp_tlv);

	p_tlv = qed_add_tlv(p_hwfn, &mbx->offset, CHANNEL_TLV_START_RXQ,
			    length);
	qed_add_tlv(p_hwfn, &mbx->offset, CHANNEL_TLV_LIST_END,
		    माप(काष्ठा channel_list_end_tlv));

	/* Update the TLV with the response */
	अगर ((status == PFVF_STATUS_SUCCESS) && !b_legacy) अणु
		req = &mbx->req_virt->start_rxq;
		p_tlv->offset = PXP_VF_BAR0_START_MSDM_ZONE_B +
				दुरत्व(काष्ठा mstorm_vf_zone,
					 non_trigger.eth_rx_queue_producers) +
				माप(काष्ठा eth_rx_prod_data) * req->rx_qid;
	पूर्ण

	qed_iov_send_response(p_hwfn, p_ptt, vf, length, status);
पूर्ण

अटल u8 qed_iov_vf_mbx_qid(काष्ठा qed_hwfn *p_hwfn,
			     काष्ठा qed_vf_info *p_vf, bool b_is_tx)
अणु
	काष्ठा qed_iov_vf_mbx *p_mbx = &p_vf->vf_mbx;
	काष्ठा vfpf_qid_tlv *p_qid_tlv;

	/* Search क्रम the qid अगर the VF published its going to provide it */
	अगर (!(p_vf->acquire.vfdev_info.capabilities &
	      VFPF_ACQUIRE_CAP_QUEUE_QIDS)) अणु
		अगर (b_is_tx)
			वापस QED_IOV_LEGACY_QID_TX;
		अन्यथा
			वापस QED_IOV_LEGACY_QID_RX;
	पूर्ण

	p_qid_tlv = (काष्ठा vfpf_qid_tlv *)
		    qed_iov_search_list_tlvs(p_hwfn, p_mbx->req_virt,
					     CHANNEL_TLV_QID);
	अगर (!p_qid_tlv) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "VF[%2x]: Failed to provide qid\n",
			   p_vf->relative_vf_id);

		वापस QED_IOV_QID_INVALID;
	पूर्ण

	अगर (p_qid_tlv->qid >= MAX_QUEUES_PER_QZONE) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "VF[%02x]: Provided qid out-of-bounds %02x\n",
			   p_vf->relative_vf_id, p_qid_tlv->qid);
		वापस QED_IOV_QID_INVALID;
	पूर्ण

	वापस p_qid_tlv->qid;
पूर्ण

अटल व्योम qed_iov_vf_mbx_start_rxq(काष्ठा qed_hwfn *p_hwfn,
				     काष्ठा qed_ptt *p_ptt,
				     काष्ठा qed_vf_info *vf)
अणु
	काष्ठा qed_queue_start_common_params params;
	काष्ठा qed_queue_cid_vf_params vf_params;
	काष्ठा qed_iov_vf_mbx *mbx = &vf->vf_mbx;
	u8 status = PFVF_STATUS_NO_RESOURCE;
	u8 qid_usage_idx, vf_legacy = 0;
	काष्ठा vfpf_start_rxq_tlv *req;
	काष्ठा qed_vf_queue *p_queue;
	काष्ठा qed_queue_cid *p_cid;
	काष्ठा qed_sb_info sb_dummy;
	पूर्णांक rc;

	req = &mbx->req_virt->start_rxq;

	अगर (!qed_iov_validate_rxq(p_hwfn, vf, req->rx_qid,
				  QED_IOV_VALIDATE_Q_DISABLE) ||
	    !qed_iov_validate_sb(p_hwfn, vf, req->hw_sb))
		जाओ out;

	qid_usage_idx = qed_iov_vf_mbx_qid(p_hwfn, vf, false);
	अगर (qid_usage_idx == QED_IOV_QID_INVALID)
		जाओ out;

	p_queue = &vf->vf_queues[req->rx_qid];
	अगर (p_queue->cids[qid_usage_idx].p_cid)
		जाओ out;

	vf_legacy = qed_vf_calculate_legacy(vf);

	/* Acquire a new queue-cid */
	स_रखो(&params, 0, माप(params));
	params.queue_id = p_queue->fw_rx_qid;
	params.vport_id = vf->vport_id;
	params.stats_id = vf->असल_vf_id + 0x10;
	/* Since IGU index is passed via sb_info, स्थिरruct a dummy one */
	स_रखो(&sb_dummy, 0, माप(sb_dummy));
	sb_dummy.igu_sb_id = req->hw_sb;
	params.p_sb = &sb_dummy;
	params.sb_idx = req->sb_index;

	स_रखो(&vf_params, 0, माप(vf_params));
	vf_params.vfid = vf->relative_vf_id;
	vf_params.vf_qid = (u8)req->rx_qid;
	vf_params.vf_legacy = vf_legacy;
	vf_params.qid_usage_idx = qid_usage_idx;
	p_cid = qed_eth_queue_to_cid(p_hwfn, vf->opaque_fid,
				     &params, true, &vf_params);
	अगर (!p_cid)
		जाओ out;

	/* Legacy VFs have their Producers in a dअगरferent location, which they
	 * calculate on their own and clean the producer prior to this.
	 */
	अगर (!(vf_legacy & QED_QCID_LEGACY_VF_RX_PROD))
		REG_WR(p_hwfn,
		       GTT_BAR0_MAP_REG_MSDM_RAM +
		       MSTORM_ETH_VF_PRODS_OFFSET(vf->असल_vf_id, req->rx_qid),
		       0);

	rc = qed_eth_rxq_start_ramrod(p_hwfn, p_cid,
				      req->bd_max_bytes,
				      req->rxq_addr,
				      req->cqe_pbl_addr, req->cqe_pbl_size);
	अगर (rc) अणु
		status = PFVF_STATUS_FAILURE;
		qed_eth_queue_cid_release(p_hwfn, p_cid);
	पूर्ण अन्यथा अणु
		p_queue->cids[qid_usage_idx].p_cid = p_cid;
		p_queue->cids[qid_usage_idx].b_is_tx = false;
		status = PFVF_STATUS_SUCCESS;
		vf->num_active_rxqs++;
	पूर्ण

out:
	qed_iov_vf_mbx_start_rxq_resp(p_hwfn, p_ptt, vf, status,
				      !!(vf_legacy &
					 QED_QCID_LEGACY_VF_RX_PROD));
पूर्ण

अटल व्योम
qed_iov_pf_update_tun_response(काष्ठा pfvf_update_tunn_param_tlv *p_resp,
			       काष्ठा qed_tunnel_info *p_tun,
			       u16 tunn_feature_mask)
अणु
	p_resp->tunn_feature_mask = tunn_feature_mask;
	p_resp->vxlan_mode = p_tun->vxlan.b_mode_enabled;
	p_resp->l2geneve_mode = p_tun->l2_geneve.b_mode_enabled;
	p_resp->ipgeneve_mode = p_tun->ip_geneve.b_mode_enabled;
	p_resp->l2gre_mode = p_tun->l2_gre.b_mode_enabled;
	p_resp->ipgre_mode = p_tun->l2_gre.b_mode_enabled;
	p_resp->vxlan_clss = p_tun->vxlan.tun_cls;
	p_resp->l2gre_clss = p_tun->l2_gre.tun_cls;
	p_resp->ipgre_clss = p_tun->ip_gre.tun_cls;
	p_resp->l2geneve_clss = p_tun->l2_geneve.tun_cls;
	p_resp->ipgeneve_clss = p_tun->ip_geneve.tun_cls;
	p_resp->geneve_udp_port = p_tun->geneve_port.port;
	p_resp->vxlan_udp_port = p_tun->vxlan_port.port;
पूर्ण

अटल व्योम
__qed_iov_pf_update_tun_param(काष्ठा vfpf_update_tunn_param_tlv *p_req,
			      काष्ठा qed_tunn_update_type *p_tun,
			      क्रमागत qed_tunn_mode mask, u8 tun_cls)
अणु
	अगर (p_req->tun_mode_update_mask & BIT(mask)) अणु
		p_tun->b_update_mode = true;

		अगर (p_req->tunn_mode & BIT(mask))
			p_tun->b_mode_enabled = true;
	पूर्ण

	p_tun->tun_cls = tun_cls;
पूर्ण

अटल व्योम
qed_iov_pf_update_tun_param(काष्ठा vfpf_update_tunn_param_tlv *p_req,
			    काष्ठा qed_tunn_update_type *p_tun,
			    काष्ठा qed_tunn_update_udp_port *p_port,
			    क्रमागत qed_tunn_mode mask,
			    u8 tun_cls, u8 update_port, u16 port)
अणु
	अगर (update_port) अणु
		p_port->b_update_port = true;
		p_port->port = port;
	पूर्ण

	__qed_iov_pf_update_tun_param(p_req, p_tun, mask, tun_cls);
पूर्ण

अटल bool
qed_iov_pf_validate_tunn_param(काष्ठा vfpf_update_tunn_param_tlv *p_req)
अणु
	bool b_update_requested = false;

	अगर (p_req->tun_mode_update_mask || p_req->update_tun_cls ||
	    p_req->update_geneve_port || p_req->update_vxlan_port)
		b_update_requested = true;

	वापस b_update_requested;
पूर्ण

अटल व्योम qed_pf_validate_tunn_mode(काष्ठा qed_tunn_update_type *tun, पूर्णांक *rc)
अणु
	अगर (tun->b_update_mode && !tun->b_mode_enabled) अणु
		tun->b_update_mode = false;
		*rc = -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक
qed_pf_validate_modअगरy_tunn_config(काष्ठा qed_hwfn *p_hwfn,
				   u16 *tun_features, bool *update,
				   काष्ठा qed_tunnel_info *tun_src)
अणु
	काष्ठा qed_eth_cb_ops *ops = p_hwfn->cdev->protocol_ops.eth;
	काष्ठा qed_tunnel_info *tun = &p_hwfn->cdev->tunnel;
	u16 bultn_vxlan_port, bultn_geneve_port;
	व्योम *cookie = p_hwfn->cdev->ops_cookie;
	पूर्णांक i, rc = 0;

	*tun_features = p_hwfn->cdev->tunn_feature_mask;
	bultn_vxlan_port = tun->vxlan_port.port;
	bultn_geneve_port = tun->geneve_port.port;
	qed_pf_validate_tunn_mode(&tun_src->vxlan, &rc);
	qed_pf_validate_tunn_mode(&tun_src->l2_geneve, &rc);
	qed_pf_validate_tunn_mode(&tun_src->ip_geneve, &rc);
	qed_pf_validate_tunn_mode(&tun_src->l2_gre, &rc);
	qed_pf_validate_tunn_mode(&tun_src->ip_gre, &rc);

	अगर ((tun_src->b_update_rx_cls || tun_src->b_update_tx_cls) &&
	    (tun_src->vxlan.tun_cls != QED_TUNN_CLSS_MAC_VLAN ||
	     tun_src->l2_geneve.tun_cls != QED_TUNN_CLSS_MAC_VLAN ||
	     tun_src->ip_geneve.tun_cls != QED_TUNN_CLSS_MAC_VLAN ||
	     tun_src->l2_gre.tun_cls != QED_TUNN_CLSS_MAC_VLAN ||
	     tun_src->ip_gre.tun_cls != QED_TUNN_CLSS_MAC_VLAN)) अणु
		tun_src->b_update_rx_cls = false;
		tun_src->b_update_tx_cls = false;
		rc = -EINVAL;
	पूर्ण

	अगर (tun_src->vxlan_port.b_update_port) अणु
		अगर (tun_src->vxlan_port.port == tun->vxlan_port.port) अणु
			tun_src->vxlan_port.b_update_port = false;
		पूर्ण अन्यथा अणु
			*update = true;
			bultn_vxlan_port = tun_src->vxlan_port.port;
		पूर्ण
	पूर्ण

	अगर (tun_src->geneve_port.b_update_port) अणु
		अगर (tun_src->geneve_port.port == tun->geneve_port.port) अणु
			tun_src->geneve_port.b_update_port = false;
		पूर्ण अन्यथा अणु
			*update = true;
			bultn_geneve_port = tun_src->geneve_port.port;
		पूर्ण
	पूर्ण

	qed_क्रम_each_vf(p_hwfn, i) अणु
		qed_iov_bulletin_set_udp_ports(p_hwfn, i, bultn_vxlan_port,
					       bultn_geneve_port);
	पूर्ण

	qed_schedule_iov(p_hwfn, QED_IOV_WQ_BULLETIN_UPDATE_FLAG);
	ops->ports_update(cookie, bultn_vxlan_port, bultn_geneve_port);

	वापस rc;
पूर्ण

अटल व्योम qed_iov_vf_mbx_update_tunn_param(काष्ठा qed_hwfn *p_hwfn,
					     काष्ठा qed_ptt *p_ptt,
					     काष्ठा qed_vf_info *p_vf)
अणु
	काष्ठा qed_tunnel_info *p_tun = &p_hwfn->cdev->tunnel;
	काष्ठा qed_iov_vf_mbx *mbx = &p_vf->vf_mbx;
	काष्ठा pfvf_update_tunn_param_tlv *p_resp;
	काष्ठा vfpf_update_tunn_param_tlv *p_req;
	u8 status = PFVF_STATUS_SUCCESS;
	bool b_update_required = false;
	काष्ठा qed_tunnel_info tunn;
	u16 tunn_feature_mask = 0;
	पूर्णांक i, rc = 0;

	mbx->offset = (u8 *)mbx->reply_virt;

	स_रखो(&tunn, 0, माप(tunn));
	p_req = &mbx->req_virt->tunn_param_update;

	अगर (!qed_iov_pf_validate_tunn_param(p_req)) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "No tunnel update requested by VF\n");
		status = PFVF_STATUS_FAILURE;
		जाओ send_resp;
	पूर्ण

	tunn.b_update_rx_cls = p_req->update_tun_cls;
	tunn.b_update_tx_cls = p_req->update_tun_cls;

	qed_iov_pf_update_tun_param(p_req, &tunn.vxlan, &tunn.vxlan_port,
				    QED_MODE_VXLAN_TUNN, p_req->vxlan_clss,
				    p_req->update_vxlan_port,
				    p_req->vxlan_port);
	qed_iov_pf_update_tun_param(p_req, &tunn.l2_geneve, &tunn.geneve_port,
				    QED_MODE_L2GENEVE_TUNN,
				    p_req->l2geneve_clss,
				    p_req->update_geneve_port,
				    p_req->geneve_port);
	__qed_iov_pf_update_tun_param(p_req, &tunn.ip_geneve,
				      QED_MODE_IPGENEVE_TUNN,
				      p_req->ipgeneve_clss);
	__qed_iov_pf_update_tun_param(p_req, &tunn.l2_gre,
				      QED_MODE_L2GRE_TUNN, p_req->l2gre_clss);
	__qed_iov_pf_update_tun_param(p_req, &tunn.ip_gre,
				      QED_MODE_IPGRE_TUNN, p_req->ipgre_clss);

	/* If PF modअगरies VF's req then it should
	 * still वापस an error in हाल of partial configuration
	 * or modअगरied configuration as opposed to requested one.
	 */
	rc = qed_pf_validate_modअगरy_tunn_config(p_hwfn, &tunn_feature_mask,
						&b_update_required, &tunn);

	अगर (rc)
		status = PFVF_STATUS_FAILURE;

	/* If QED client is willing to update anything ? */
	अगर (b_update_required) अणु
		u16 geneve_port;

		rc = qed_sp_pf_update_tunn_cfg(p_hwfn, p_ptt, &tunn,
					       QED_SPQ_MODE_EBLOCK, शून्य);
		अगर (rc)
			status = PFVF_STATUS_FAILURE;

		geneve_port = p_tun->geneve_port.port;
		qed_क्रम_each_vf(p_hwfn, i) अणु
			qed_iov_bulletin_set_udp_ports(p_hwfn, i,
						       p_tun->vxlan_port.port,
						       geneve_port);
		पूर्ण
	पूर्ण

send_resp:
	p_resp = qed_add_tlv(p_hwfn, &mbx->offset,
			     CHANNEL_TLV_UPDATE_TUNN_PARAM, माप(*p_resp));

	qed_iov_pf_update_tun_response(p_resp, p_tun, tunn_feature_mask);
	qed_add_tlv(p_hwfn, &mbx->offset, CHANNEL_TLV_LIST_END,
		    माप(काष्ठा channel_list_end_tlv));

	qed_iov_send_response(p_hwfn, p_ptt, p_vf, माप(*p_resp), status);
पूर्ण

अटल व्योम qed_iov_vf_mbx_start_txq_resp(काष्ठा qed_hwfn *p_hwfn,
					  काष्ठा qed_ptt *p_ptt,
					  काष्ठा qed_vf_info *p_vf,
					  u32 cid, u8 status)
अणु
	काष्ठा qed_iov_vf_mbx *mbx = &p_vf->vf_mbx;
	काष्ठा pfvf_start_queue_resp_tlv *p_tlv;
	bool b_legacy = false;
	u16 length;

	mbx->offset = (u8 *)mbx->reply_virt;

	/* Taking a bigger काष्ठा instead of adding a TLV to list was a
	 * mistake, but one which we're now stuck with, as some older
	 * clients assume the size of the previous response.
	 */
	अगर (p_vf->acquire.vfdev_info.eth_fp_hsi_minor ==
	    ETH_HSI_VER_NO_PKT_LEN_TUNN)
		b_legacy = true;

	अगर (!b_legacy)
		length = माप(*p_tlv);
	अन्यथा
		length = माप(काष्ठा pfvf_def_resp_tlv);

	p_tlv = qed_add_tlv(p_hwfn, &mbx->offset, CHANNEL_TLV_START_TXQ,
			    length);
	qed_add_tlv(p_hwfn, &mbx->offset, CHANNEL_TLV_LIST_END,
		    माप(काष्ठा channel_list_end_tlv));

	/* Update the TLV with the response */
	अगर ((status == PFVF_STATUS_SUCCESS) && !b_legacy)
		p_tlv->offset = qed_db_addr_vf(cid, DQ_DEMS_LEGACY);

	qed_iov_send_response(p_hwfn, p_ptt, p_vf, length, status);
पूर्ण

अटल व्योम qed_iov_vf_mbx_start_txq(काष्ठा qed_hwfn *p_hwfn,
				     काष्ठा qed_ptt *p_ptt,
				     काष्ठा qed_vf_info *vf)
अणु
	काष्ठा qed_queue_start_common_params params;
	काष्ठा qed_queue_cid_vf_params vf_params;
	काष्ठा qed_iov_vf_mbx *mbx = &vf->vf_mbx;
	u8 status = PFVF_STATUS_NO_RESOURCE;
	काष्ठा vfpf_start_txq_tlv *req;
	काष्ठा qed_vf_queue *p_queue;
	काष्ठा qed_queue_cid *p_cid;
	काष्ठा qed_sb_info sb_dummy;
	u8 qid_usage_idx, vf_legacy;
	u32 cid = 0;
	पूर्णांक rc;
	u16 pq;

	स_रखो(&params, 0, माप(params));
	req = &mbx->req_virt->start_txq;

	अगर (!qed_iov_validate_txq(p_hwfn, vf, req->tx_qid,
				  QED_IOV_VALIDATE_Q_NA) ||
	    !qed_iov_validate_sb(p_hwfn, vf, req->hw_sb))
		जाओ out;

	qid_usage_idx = qed_iov_vf_mbx_qid(p_hwfn, vf, true);
	अगर (qid_usage_idx == QED_IOV_QID_INVALID)
		जाओ out;

	p_queue = &vf->vf_queues[req->tx_qid];
	अगर (p_queue->cids[qid_usage_idx].p_cid)
		जाओ out;

	vf_legacy = qed_vf_calculate_legacy(vf);

	/* Acquire a new queue-cid */
	params.queue_id = p_queue->fw_tx_qid;
	params.vport_id = vf->vport_id;
	params.stats_id = vf->असल_vf_id + 0x10;

	/* Since IGU index is passed via sb_info, स्थिरruct a dummy one */
	स_रखो(&sb_dummy, 0, माप(sb_dummy));
	sb_dummy.igu_sb_id = req->hw_sb;
	params.p_sb = &sb_dummy;
	params.sb_idx = req->sb_index;

	स_रखो(&vf_params, 0, माप(vf_params));
	vf_params.vfid = vf->relative_vf_id;
	vf_params.vf_qid = (u8)req->tx_qid;
	vf_params.vf_legacy = vf_legacy;
	vf_params.qid_usage_idx = qid_usage_idx;

	p_cid = qed_eth_queue_to_cid(p_hwfn, vf->opaque_fid,
				     &params, false, &vf_params);
	अगर (!p_cid)
		जाओ out;

	pq = qed_get_cm_pq_idx_vf(p_hwfn, vf->relative_vf_id);
	rc = qed_eth_txq_start_ramrod(p_hwfn, p_cid,
				      req->pbl_addr, req->pbl_size, pq);
	अगर (rc) अणु
		status = PFVF_STATUS_FAILURE;
		qed_eth_queue_cid_release(p_hwfn, p_cid);
	पूर्ण अन्यथा अणु
		status = PFVF_STATUS_SUCCESS;
		p_queue->cids[qid_usage_idx].p_cid = p_cid;
		p_queue->cids[qid_usage_idx].b_is_tx = true;
		cid = p_cid->cid;
	पूर्ण

out:
	qed_iov_vf_mbx_start_txq_resp(p_hwfn, p_ptt, vf, cid, status);
पूर्ण

अटल पूर्णांक qed_iov_vf_stop_rxqs(काष्ठा qed_hwfn *p_hwfn,
				काष्ठा qed_vf_info *vf,
				u16 rxq_id,
				u8 qid_usage_idx, bool cqe_completion)
अणु
	काष्ठा qed_vf_queue *p_queue;
	पूर्णांक rc = 0;

	अगर (!qed_iov_validate_rxq(p_hwfn, vf, rxq_id, QED_IOV_VALIDATE_Q_NA)) अणु
		DP_VERBOSE(p_hwfn,
			   QED_MSG_IOV,
			   "VF[%d] Tried Closing Rx 0x%04x.%02x which is inactive\n",
			   vf->relative_vf_id, rxq_id, qid_usage_idx);
		वापस -EINVAL;
	पूर्ण

	p_queue = &vf->vf_queues[rxq_id];

	/* We've validated the index and the existence of the active RXQ -
	 * now we need to make sure that it's using the correct qid.
	 */
	अगर (!p_queue->cids[qid_usage_idx].p_cid ||
	    p_queue->cids[qid_usage_idx].b_is_tx) अणु
		काष्ठा qed_queue_cid *p_cid;

		p_cid = qed_iov_get_vf_rx_queue_cid(p_queue);
		DP_VERBOSE(p_hwfn,
			   QED_MSG_IOV,
			   "VF[%d] - Tried Closing Rx 0x%04x.%02x, but Rx is at %04x.%02x\n",
			   vf->relative_vf_id,
			   rxq_id, qid_usage_idx, rxq_id, p_cid->qid_usage_idx);
		वापस -EINVAL;
	पूर्ण

	/* Now that we know we have a valid Rx-queue - बंद it */
	rc = qed_eth_rx_queue_stop(p_hwfn,
				   p_queue->cids[qid_usage_idx].p_cid,
				   false, cqe_completion);
	अगर (rc)
		वापस rc;

	p_queue->cids[qid_usage_idx].p_cid = शून्य;
	vf->num_active_rxqs--;

	वापस 0;
पूर्ण

अटल पूर्णांक qed_iov_vf_stop_txqs(काष्ठा qed_hwfn *p_hwfn,
				काष्ठा qed_vf_info *vf,
				u16 txq_id, u8 qid_usage_idx)
अणु
	काष्ठा qed_vf_queue *p_queue;
	पूर्णांक rc = 0;

	अगर (!qed_iov_validate_txq(p_hwfn, vf, txq_id, QED_IOV_VALIDATE_Q_NA))
		वापस -EINVAL;

	p_queue = &vf->vf_queues[txq_id];
	अगर (!p_queue->cids[qid_usage_idx].p_cid ||
	    !p_queue->cids[qid_usage_idx].b_is_tx)
		वापस -EINVAL;

	rc = qed_eth_tx_queue_stop(p_hwfn, p_queue->cids[qid_usage_idx].p_cid);
	अगर (rc)
		वापस rc;

	p_queue->cids[qid_usage_idx].p_cid = शून्य;
	वापस 0;
पूर्ण

अटल व्योम qed_iov_vf_mbx_stop_rxqs(काष्ठा qed_hwfn *p_hwfn,
				     काष्ठा qed_ptt *p_ptt,
				     काष्ठा qed_vf_info *vf)
अणु
	u16 length = माप(काष्ठा pfvf_def_resp_tlv);
	काष्ठा qed_iov_vf_mbx *mbx = &vf->vf_mbx;
	u8 status = PFVF_STATUS_FAILURE;
	काष्ठा vfpf_stop_rxqs_tlv *req;
	u8 qid_usage_idx;
	पूर्णांक rc;

	/* There has never been an official driver that used this पूर्णांकerface
	 * क्रम stopping multiple queues, and it is now considered deprecated.
	 * Validate this isn't used here.
	 */
	req = &mbx->req_virt->stop_rxqs;
	अगर (req->num_rxqs != 1) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "Odd; VF[%d] tried stopping multiple Rx queues\n",
			   vf->relative_vf_id);
		status = PFVF_STATUS_NOT_SUPPORTED;
		जाओ out;
	पूर्ण

	/* Find which qid-index is associated with the queue */
	qid_usage_idx = qed_iov_vf_mbx_qid(p_hwfn, vf, false);
	अगर (qid_usage_idx == QED_IOV_QID_INVALID)
		जाओ out;

	rc = qed_iov_vf_stop_rxqs(p_hwfn, vf, req->rx_qid,
				  qid_usage_idx, req->cqe_completion);
	अगर (!rc)
		status = PFVF_STATUS_SUCCESS;
out:
	qed_iov_prepare_resp(p_hwfn, p_ptt, vf, CHANNEL_TLV_STOP_RXQS,
			     length, status);
पूर्ण

अटल व्योम qed_iov_vf_mbx_stop_txqs(काष्ठा qed_hwfn *p_hwfn,
				     काष्ठा qed_ptt *p_ptt,
				     काष्ठा qed_vf_info *vf)
अणु
	u16 length = माप(काष्ठा pfvf_def_resp_tlv);
	काष्ठा qed_iov_vf_mbx *mbx = &vf->vf_mbx;
	u8 status = PFVF_STATUS_FAILURE;
	काष्ठा vfpf_stop_txqs_tlv *req;
	u8 qid_usage_idx;
	पूर्णांक rc;

	/* There has never been an official driver that used this पूर्णांकerface
	 * क्रम stopping multiple queues, and it is now considered deprecated.
	 * Validate this isn't used here.
	 */
	req = &mbx->req_virt->stop_txqs;
	अगर (req->num_txqs != 1) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "Odd; VF[%d] tried stopping multiple Tx queues\n",
			   vf->relative_vf_id);
		status = PFVF_STATUS_NOT_SUPPORTED;
		जाओ out;
	पूर्ण

	/* Find which qid-index is associated with the queue */
	qid_usage_idx = qed_iov_vf_mbx_qid(p_hwfn, vf, true);
	अगर (qid_usage_idx == QED_IOV_QID_INVALID)
		जाओ out;

	rc = qed_iov_vf_stop_txqs(p_hwfn, vf, req->tx_qid, qid_usage_idx);
	अगर (!rc)
		status = PFVF_STATUS_SUCCESS;

out:
	qed_iov_prepare_resp(p_hwfn, p_ptt, vf, CHANNEL_TLV_STOP_TXQS,
			     length, status);
पूर्ण

अटल व्योम qed_iov_vf_mbx_update_rxqs(काष्ठा qed_hwfn *p_hwfn,
				       काष्ठा qed_ptt *p_ptt,
				       काष्ठा qed_vf_info *vf)
अणु
	काष्ठा qed_queue_cid *handlers[QED_MAX_VF_CHAINS_PER_PF];
	u16 length = माप(काष्ठा pfvf_def_resp_tlv);
	काष्ठा qed_iov_vf_mbx *mbx = &vf->vf_mbx;
	काष्ठा vfpf_update_rxq_tlv *req;
	u8 status = PFVF_STATUS_FAILURE;
	u8 complete_event_flg;
	u8 complete_cqe_flg;
	u8 qid_usage_idx;
	पूर्णांक rc;
	u8 i;

	req = &mbx->req_virt->update_rxq;
	complete_cqe_flg = !!(req->flags & VFPF_RXQ_UPD_COMPLETE_CQE_FLAG);
	complete_event_flg = !!(req->flags & VFPF_RXQ_UPD_COMPLETE_EVENT_FLAG);

	qid_usage_idx = qed_iov_vf_mbx_qid(p_hwfn, vf, false);
	अगर (qid_usage_idx == QED_IOV_QID_INVALID)
		जाओ out;

	/* There shouldn't exist a VF that uses queue-qids yet uses this
	 * API with multiple Rx queues. Validate this.
	 */
	अगर ((vf->acquire.vfdev_info.capabilities &
	     VFPF_ACQUIRE_CAP_QUEUE_QIDS) && req->num_rxqs != 1) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "VF[%d] supports QIDs but sends multiple queues\n",
			   vf->relative_vf_id);
		जाओ out;
	पूर्ण

	/* Validate inमाला_दो - क्रम the legacy हाल this is still true since
	 * qid_usage_idx क्रम each Rx queue would be LEGACY_QID_RX.
	 */
	क्रम (i = req->rx_qid; i < req->rx_qid + req->num_rxqs; i++) अणु
		अगर (!qed_iov_validate_rxq(p_hwfn, vf, i,
					  QED_IOV_VALIDATE_Q_NA) ||
		    !vf->vf_queues[i].cids[qid_usage_idx].p_cid ||
		    vf->vf_queues[i].cids[qid_usage_idx].b_is_tx) अणु
			DP_VERBOSE(p_hwfn, QED_MSG_IOV,
				   "VF[%d]: Incorrect Rxqs [%04x, %02x]\n",
				   vf->relative_vf_id, req->rx_qid,
				   req->num_rxqs);
			जाओ out;
		पूर्ण
	पूर्ण

	/* Prepare the handlers */
	क्रम (i = 0; i < req->num_rxqs; i++) अणु
		u16 qid = req->rx_qid + i;

		handlers[i] = vf->vf_queues[qid].cids[qid_usage_idx].p_cid;
	पूर्ण

	rc = qed_sp_eth_rx_queues_update(p_hwfn, (व्योम **)&handlers,
					 req->num_rxqs,
					 complete_cqe_flg,
					 complete_event_flg,
					 QED_SPQ_MODE_EBLOCK, शून्य);
	अगर (rc)
		जाओ out;

	status = PFVF_STATUS_SUCCESS;
out:
	qed_iov_prepare_resp(p_hwfn, p_ptt, vf, CHANNEL_TLV_UPDATE_RXQ,
			     length, status);
पूर्ण

व्योम *qed_iov_search_list_tlvs(काष्ठा qed_hwfn *p_hwfn,
			       व्योम *p_tlvs_list, u16 req_type)
अणु
	काष्ठा channel_tlv *p_tlv = (काष्ठा channel_tlv *)p_tlvs_list;
	पूर्णांक len = 0;

	करो अणु
		अगर (!p_tlv->length) अणु
			DP_NOTICE(p_hwfn, "Zero length TLV found\n");
			वापस शून्य;
		पूर्ण

		अगर (p_tlv->type == req_type) अणु
			DP_VERBOSE(p_hwfn, QED_MSG_IOV,
				   "Extended tlv type %d, length %d found\n",
				   p_tlv->type, p_tlv->length);
			वापस p_tlv;
		पूर्ण

		len += p_tlv->length;
		p_tlv = (काष्ठा channel_tlv *)((u8 *)p_tlv + p_tlv->length);

		अगर ((len + p_tlv->length) > TLV_BUFFER_SIZE) अणु
			DP_NOTICE(p_hwfn, "TLVs has overrun the buffer size\n");
			वापस शून्य;
		पूर्ण
	पूर्ण जबतक (p_tlv->type != CHANNEL_TLV_LIST_END);

	वापस शून्य;
पूर्ण

अटल व्योम
qed_iov_vp_update_act_param(काष्ठा qed_hwfn *p_hwfn,
			    काष्ठा qed_sp_vport_update_params *p_data,
			    काष्ठा qed_iov_vf_mbx *p_mbx, u16 *tlvs_mask)
अणु
	काष्ठा vfpf_vport_update_activate_tlv *p_act_tlv;
	u16 tlv = CHANNEL_TLV_VPORT_UPDATE_ACTIVATE;

	p_act_tlv = (काष्ठा vfpf_vport_update_activate_tlv *)
		    qed_iov_search_list_tlvs(p_hwfn, p_mbx->req_virt, tlv);
	अगर (!p_act_tlv)
		वापस;

	p_data->update_vport_active_rx_flg = p_act_tlv->update_rx;
	p_data->vport_active_rx_flg = p_act_tlv->active_rx;
	p_data->update_vport_active_tx_flg = p_act_tlv->update_tx;
	p_data->vport_active_tx_flg = p_act_tlv->active_tx;
	*tlvs_mask |= 1 << QED_IOV_VP_UPDATE_ACTIVATE;
पूर्ण

अटल व्योम
qed_iov_vp_update_vlan_param(काष्ठा qed_hwfn *p_hwfn,
			     काष्ठा qed_sp_vport_update_params *p_data,
			     काष्ठा qed_vf_info *p_vf,
			     काष्ठा qed_iov_vf_mbx *p_mbx, u16 *tlvs_mask)
अणु
	काष्ठा vfpf_vport_update_vlan_strip_tlv *p_vlan_tlv;
	u16 tlv = CHANNEL_TLV_VPORT_UPDATE_VLAN_STRIP;

	p_vlan_tlv = (काष्ठा vfpf_vport_update_vlan_strip_tlv *)
		     qed_iov_search_list_tlvs(p_hwfn, p_mbx->req_virt, tlv);
	अगर (!p_vlan_tlv)
		वापस;

	p_vf->shaकरोw_config.inner_vlan_removal = p_vlan_tlv->हटाओ_vlan;

	/* Ignore the VF request अगर we're क्रमcing a vlan */
	अगर (!(p_vf->configured_features & BIT(VLAN_ADDR_FORCED))) अणु
		p_data->update_inner_vlan_removal_flg = 1;
		p_data->inner_vlan_removal_flg = p_vlan_tlv->हटाओ_vlan;
	पूर्ण

	*tlvs_mask |= 1 << QED_IOV_VP_UPDATE_VLAN_STRIP;
पूर्ण

अटल व्योम
qed_iov_vp_update_tx_चयन(काष्ठा qed_hwfn *p_hwfn,
			    काष्ठा qed_sp_vport_update_params *p_data,
			    काष्ठा qed_iov_vf_mbx *p_mbx, u16 *tlvs_mask)
अणु
	काष्ठा vfpf_vport_update_tx_चयन_tlv *p_tx_चयन_tlv;
	u16 tlv = CHANNEL_TLV_VPORT_UPDATE_TX_SWITCH;

	p_tx_चयन_tlv = (काष्ठा vfpf_vport_update_tx_चयन_tlv *)
			  qed_iov_search_list_tlvs(p_hwfn, p_mbx->req_virt,
						   tlv);
	अगर (!p_tx_चयन_tlv)
		वापस;

	p_data->update_tx_चयनing_flg = 1;
	p_data->tx_चयनing_flg = p_tx_चयन_tlv->tx_चयनing;
	*tlvs_mask |= 1 << QED_IOV_VP_UPDATE_TX_SWITCH;
पूर्ण

अटल व्योम
qed_iov_vp_update_mcast_bin_param(काष्ठा qed_hwfn *p_hwfn,
				  काष्ठा qed_sp_vport_update_params *p_data,
				  काष्ठा qed_iov_vf_mbx *p_mbx, u16 *tlvs_mask)
अणु
	काष्ठा vfpf_vport_update_mcast_bin_tlv *p_mcast_tlv;
	u16 tlv = CHANNEL_TLV_VPORT_UPDATE_MCAST;

	p_mcast_tlv = (काष्ठा vfpf_vport_update_mcast_bin_tlv *)
	    qed_iov_search_list_tlvs(p_hwfn, p_mbx->req_virt, tlv);
	अगर (!p_mcast_tlv)
		वापस;

	p_data->update_approx_mcast_flg = 1;
	स_नकल(p_data->bins, p_mcast_tlv->bins,
	       माप(u32) * ETH_MULTICAST_MAC_BINS_IN_REGS);
	*tlvs_mask |= 1 << QED_IOV_VP_UPDATE_MCAST;
पूर्ण

अटल व्योम
qed_iov_vp_update_accept_flag(काष्ठा qed_hwfn *p_hwfn,
			      काष्ठा qed_sp_vport_update_params *p_data,
			      काष्ठा qed_iov_vf_mbx *p_mbx, u16 *tlvs_mask)
अणु
	काष्ठा qed_filter_accept_flags *p_flags = &p_data->accept_flags;
	काष्ठा vfpf_vport_update_accept_param_tlv *p_accept_tlv;
	u16 tlv = CHANNEL_TLV_VPORT_UPDATE_ACCEPT_PARAM;

	p_accept_tlv = (काष्ठा vfpf_vport_update_accept_param_tlv *)
	    qed_iov_search_list_tlvs(p_hwfn, p_mbx->req_virt, tlv);
	अगर (!p_accept_tlv)
		वापस;

	p_flags->update_rx_mode_config = p_accept_tlv->update_rx_mode;
	p_flags->rx_accept_filter = p_accept_tlv->rx_accept_filter;
	p_flags->update_tx_mode_config = p_accept_tlv->update_tx_mode;
	p_flags->tx_accept_filter = p_accept_tlv->tx_accept_filter;
	*tlvs_mask |= 1 << QED_IOV_VP_UPDATE_ACCEPT_PARAM;
पूर्ण

अटल व्योम
qed_iov_vp_update_accept_any_vlan(काष्ठा qed_hwfn *p_hwfn,
				  काष्ठा qed_sp_vport_update_params *p_data,
				  काष्ठा qed_iov_vf_mbx *p_mbx, u16 *tlvs_mask)
अणु
	काष्ठा vfpf_vport_update_accept_any_vlan_tlv *p_accept_any_vlan;
	u16 tlv = CHANNEL_TLV_VPORT_UPDATE_ACCEPT_ANY_VLAN;

	p_accept_any_vlan = (काष्ठा vfpf_vport_update_accept_any_vlan_tlv *)
			    qed_iov_search_list_tlvs(p_hwfn, p_mbx->req_virt,
						     tlv);
	अगर (!p_accept_any_vlan)
		वापस;

	p_data->accept_any_vlan = p_accept_any_vlan->accept_any_vlan;
	p_data->update_accept_any_vlan_flg =
		    p_accept_any_vlan->update_accept_any_vlan_flg;
	*tlvs_mask |= 1 << QED_IOV_VP_UPDATE_ACCEPT_ANY_VLAN;
पूर्ण

अटल व्योम
qed_iov_vp_update_rss_param(काष्ठा qed_hwfn *p_hwfn,
			    काष्ठा qed_vf_info *vf,
			    काष्ठा qed_sp_vport_update_params *p_data,
			    काष्ठा qed_rss_params *p_rss,
			    काष्ठा qed_iov_vf_mbx *p_mbx,
			    u16 *tlvs_mask, u16 *tlvs_accepted)
अणु
	काष्ठा vfpf_vport_update_rss_tlv *p_rss_tlv;
	u16 tlv = CHANNEL_TLV_VPORT_UPDATE_RSS;
	bool b_reject = false;
	u16 table_size;
	u16 i, q_idx;

	p_rss_tlv = (काष्ठा vfpf_vport_update_rss_tlv *)
		    qed_iov_search_list_tlvs(p_hwfn, p_mbx->req_virt, tlv);
	अगर (!p_rss_tlv) अणु
		p_data->rss_params = शून्य;
		वापस;
	पूर्ण

	स_रखो(p_rss, 0, माप(काष्ठा qed_rss_params));

	p_rss->update_rss_config = !!(p_rss_tlv->update_rss_flags &
				      VFPF_UPDATE_RSS_CONFIG_FLAG);
	p_rss->update_rss_capabilities = !!(p_rss_tlv->update_rss_flags &
					    VFPF_UPDATE_RSS_CAPS_FLAG);
	p_rss->update_rss_ind_table = !!(p_rss_tlv->update_rss_flags &
					 VFPF_UPDATE_RSS_IND_TABLE_FLAG);
	p_rss->update_rss_key = !!(p_rss_tlv->update_rss_flags &
				   VFPF_UPDATE_RSS_KEY_FLAG);

	p_rss->rss_enable = p_rss_tlv->rss_enable;
	p_rss->rss_eng_id = vf->relative_vf_id + 1;
	p_rss->rss_caps = p_rss_tlv->rss_caps;
	p_rss->rss_table_size_log = p_rss_tlv->rss_table_size_log;
	स_नकल(p_rss->rss_key, p_rss_tlv->rss_key, माप(p_rss->rss_key));

	table_size = min_t(u16, ARRAY_SIZE(p_rss->rss_ind_table),
			   (1 << p_rss_tlv->rss_table_size_log));

	क्रम (i = 0; i < table_size; i++) अणु
		काष्ठा qed_queue_cid *p_cid;

		q_idx = p_rss_tlv->rss_ind_table[i];
		अगर (!qed_iov_validate_rxq(p_hwfn, vf, q_idx,
					  QED_IOV_VALIDATE_Q_ENABLE)) अणु
			DP_VERBOSE(p_hwfn,
				   QED_MSG_IOV,
				   "VF[%d]: Omitting RSS due to wrong queue %04x\n",
				   vf->relative_vf_id, q_idx);
			b_reject = true;
			जाओ out;
		पूर्ण

		p_cid = qed_iov_get_vf_rx_queue_cid(&vf->vf_queues[q_idx]);
		p_rss->rss_ind_table[i] = p_cid;
	पूर्ण

	p_data->rss_params = p_rss;
out:
	*tlvs_mask |= 1 << QED_IOV_VP_UPDATE_RSS;
	अगर (!b_reject)
		*tlvs_accepted |= 1 << QED_IOV_VP_UPDATE_RSS;
पूर्ण

अटल व्योम
qed_iov_vp_update_sge_tpa_param(काष्ठा qed_hwfn *p_hwfn,
				काष्ठा qed_vf_info *vf,
				काष्ठा qed_sp_vport_update_params *p_data,
				काष्ठा qed_sge_tpa_params *p_sge_tpa,
				काष्ठा qed_iov_vf_mbx *p_mbx, u16 *tlvs_mask)
अणु
	काष्ठा vfpf_vport_update_sge_tpa_tlv *p_sge_tpa_tlv;
	u16 tlv = CHANNEL_TLV_VPORT_UPDATE_SGE_TPA;

	p_sge_tpa_tlv = (काष्ठा vfpf_vport_update_sge_tpa_tlv *)
	    qed_iov_search_list_tlvs(p_hwfn, p_mbx->req_virt, tlv);

	अगर (!p_sge_tpa_tlv) अणु
		p_data->sge_tpa_params = शून्य;
		वापस;
	पूर्ण

	स_रखो(p_sge_tpa, 0, माप(काष्ठा qed_sge_tpa_params));

	p_sge_tpa->update_tpa_en_flg =
	    !!(p_sge_tpa_tlv->update_sge_tpa_flags & VFPF_UPDATE_TPA_EN_FLAG);
	p_sge_tpa->update_tpa_param_flg =
	    !!(p_sge_tpa_tlv->update_sge_tpa_flags &
		VFPF_UPDATE_TPA_PARAM_FLAG);

	p_sge_tpa->tpa_ipv4_en_flg =
	    !!(p_sge_tpa_tlv->sge_tpa_flags & VFPF_TPA_IPV4_EN_FLAG);
	p_sge_tpa->tpa_ipv6_en_flg =
	    !!(p_sge_tpa_tlv->sge_tpa_flags & VFPF_TPA_IPV6_EN_FLAG);
	p_sge_tpa->tpa_pkt_split_flg =
	    !!(p_sge_tpa_tlv->sge_tpa_flags & VFPF_TPA_PKT_SPLIT_FLAG);
	p_sge_tpa->tpa_hdr_data_split_flg =
	    !!(p_sge_tpa_tlv->sge_tpa_flags & VFPF_TPA_HDR_DATA_SPLIT_FLAG);
	p_sge_tpa->tpa_gro_consistent_flg =
	    !!(p_sge_tpa_tlv->sge_tpa_flags & VFPF_TPA_GRO_CONSIST_FLAG);

	p_sge_tpa->tpa_max_aggs_num = p_sge_tpa_tlv->tpa_max_aggs_num;
	p_sge_tpa->tpa_max_size = p_sge_tpa_tlv->tpa_max_size;
	p_sge_tpa->tpa_min_माप_प्रकारo_start = p_sge_tpa_tlv->tpa_min_माप_प्रकारo_start;
	p_sge_tpa->tpa_min_माप_प्रकारo_cont = p_sge_tpa_tlv->tpa_min_माप_प्रकारo_cont;
	p_sge_tpa->max_buffers_per_cqe = p_sge_tpa_tlv->max_buffers_per_cqe;

	p_data->sge_tpa_params = p_sge_tpa;

	*tlvs_mask |= 1 << QED_IOV_VP_UPDATE_SGE_TPA;
पूर्ण

अटल पूर्णांक qed_iov_pre_update_vport(काष्ठा qed_hwfn *hwfn,
				    u8 vfid,
				    काष्ठा qed_sp_vport_update_params *params,
				    u16 *tlvs)
अणु
	u8 mask = QED_ACCEPT_UCAST_UNMATCHED | QED_ACCEPT_MCAST_UNMATCHED;
	काष्ठा qed_filter_accept_flags *flags = &params->accept_flags;
	काष्ठा qed_खुला_vf_info *vf_info;

	/* Untrusted VFs can't even be trusted to know that fact.
	 * Simply indicate everything is configured fine, and trace
	 * configuration 'behind their back'.
	 */
	अगर (!(*tlvs & BIT(QED_IOV_VP_UPDATE_ACCEPT_PARAM)))
		वापस 0;

	vf_info = qed_iov_get_खुला_vf_info(hwfn, vfid, true);

	अगर (flags->update_rx_mode_config) अणु
		vf_info->rx_accept_mode = flags->rx_accept_filter;
		अगर (!vf_info->is_trusted_configured)
			flags->rx_accept_filter &= ~mask;
	पूर्ण

	अगर (flags->update_tx_mode_config) अणु
		vf_info->tx_accept_mode = flags->tx_accept_filter;
		अगर (!vf_info->is_trusted_configured)
			flags->tx_accept_filter &= ~mask;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qed_iov_vf_mbx_vport_update(काष्ठा qed_hwfn *p_hwfn,
					काष्ठा qed_ptt *p_ptt,
					काष्ठा qed_vf_info *vf)
अणु
	काष्ठा qed_rss_params *p_rss_params = शून्य;
	काष्ठा qed_sp_vport_update_params params;
	काष्ठा qed_iov_vf_mbx *mbx = &vf->vf_mbx;
	काष्ठा qed_sge_tpa_params sge_tpa_params;
	u16 tlvs_mask = 0, tlvs_accepted = 0;
	u8 status = PFVF_STATUS_SUCCESS;
	u16 length;
	पूर्णांक rc;

	/* Valiate PF can send such a request */
	अगर (!vf->vport_instance) अणु
		DP_VERBOSE(p_hwfn,
			   QED_MSG_IOV,
			   "No VPORT instance available for VF[%d], failing vport update\n",
			   vf->असल_vf_id);
		status = PFVF_STATUS_FAILURE;
		जाओ out;
	पूर्ण
	p_rss_params = vzalloc(माप(*p_rss_params));
	अगर (p_rss_params == शून्य) अणु
		status = PFVF_STATUS_FAILURE;
		जाओ out;
	पूर्ण

	स_रखो(&params, 0, माप(params));
	params.opaque_fid = vf->opaque_fid;
	params.vport_id = vf->vport_id;
	params.rss_params = शून्य;

	/* Search क्रम extended tlvs list and update values
	 * from VF in काष्ठा qed_sp_vport_update_params.
	 */
	qed_iov_vp_update_act_param(p_hwfn, &params, mbx, &tlvs_mask);
	qed_iov_vp_update_vlan_param(p_hwfn, &params, vf, mbx, &tlvs_mask);
	qed_iov_vp_update_tx_चयन(p_hwfn, &params, mbx, &tlvs_mask);
	qed_iov_vp_update_mcast_bin_param(p_hwfn, &params, mbx, &tlvs_mask);
	qed_iov_vp_update_accept_flag(p_hwfn, &params, mbx, &tlvs_mask);
	qed_iov_vp_update_accept_any_vlan(p_hwfn, &params, mbx, &tlvs_mask);
	qed_iov_vp_update_sge_tpa_param(p_hwfn, vf, &params,
					&sge_tpa_params, mbx, &tlvs_mask);

	tlvs_accepted = tlvs_mask;

	/* Some of the extended TLVs need to be validated first; In that हाल,
	 * they can update the mask without updating the accepted [so that
	 * PF could communicate to VF it has rejected request].
	 */
	qed_iov_vp_update_rss_param(p_hwfn, vf, &params, p_rss_params,
				    mbx, &tlvs_mask, &tlvs_accepted);

	अगर (qed_iov_pre_update_vport(p_hwfn, vf->relative_vf_id,
				     &params, &tlvs_accepted)) अणु
		tlvs_accepted = 0;
		status = PFVF_STATUS_NOT_SUPPORTED;
		जाओ out;
	पूर्ण

	अगर (!tlvs_accepted) अणु
		अगर (tlvs_mask)
			DP_VERBOSE(p_hwfn, QED_MSG_IOV,
				   "Upper-layer prevents VF vport configuration\n");
		अन्यथा
			DP_VERBOSE(p_hwfn, QED_MSG_IOV,
				   "No feature tlvs found for vport update\n");
		status = PFVF_STATUS_NOT_SUPPORTED;
		जाओ out;
	पूर्ण

	rc = qed_sp_vport_update(p_hwfn, &params, QED_SPQ_MODE_EBLOCK, शून्य);

	अगर (rc)
		status = PFVF_STATUS_FAILURE;

out:
	vमुक्त(p_rss_params);
	length = qed_iov_prep_vp_update_resp_tlvs(p_hwfn, vf, mbx, status,
						  tlvs_mask, tlvs_accepted);
	qed_iov_send_response(p_hwfn, p_ptt, vf, length, status);
पूर्ण

अटल पूर्णांक qed_iov_vf_update_vlan_shaकरोw(काष्ठा qed_hwfn *p_hwfn,
					 काष्ठा qed_vf_info *p_vf,
					 काष्ठा qed_filter_ucast *p_params)
अणु
	पूर्णांक i;

	/* First हटाओ entries and then add new ones */
	अगर (p_params->opcode == QED_FILTER_REMOVE) अणु
		क्रम (i = 0; i < QED_ETH_VF_NUM_VLAN_FILTERS + 1; i++)
			अगर (p_vf->shaकरोw_config.vlans[i].used &&
			    p_vf->shaकरोw_config.vlans[i].vid ==
			    p_params->vlan) अणु
				p_vf->shaकरोw_config.vlans[i].used = false;
				अवरोध;
			पूर्ण
		अगर (i == QED_ETH_VF_NUM_VLAN_FILTERS + 1) अणु
			DP_VERBOSE(p_hwfn,
				   QED_MSG_IOV,
				   "VF [%d] - Tries to remove a non-existing vlan\n",
				   p_vf->relative_vf_id);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (p_params->opcode == QED_FILTER_REPLACE ||
		   p_params->opcode == QED_FILTER_FLUSH) अणु
		क्रम (i = 0; i < QED_ETH_VF_NUM_VLAN_FILTERS + 1; i++)
			p_vf->shaकरोw_config.vlans[i].used = false;
	पूर्ण

	/* In क्रमced mode, we're willing to remove entries - but we don't add
	 * new ones.
	 */
	अगर (p_vf->bulletin.p_virt->valid_biपंचांगap & BIT(VLAN_ADDR_FORCED))
		वापस 0;

	अगर (p_params->opcode == QED_FILTER_ADD ||
	    p_params->opcode == QED_FILTER_REPLACE) अणु
		क्रम (i = 0; i < QED_ETH_VF_NUM_VLAN_FILTERS + 1; i++) अणु
			अगर (p_vf->shaकरोw_config.vlans[i].used)
				जारी;

			p_vf->shaकरोw_config.vlans[i].used = true;
			p_vf->shaकरोw_config.vlans[i].vid = p_params->vlan;
			अवरोध;
		पूर्ण

		अगर (i == QED_ETH_VF_NUM_VLAN_FILTERS + 1) अणु
			DP_VERBOSE(p_hwfn,
				   QED_MSG_IOV,
				   "VF [%d] - Tries to configure more than %d vlan filters\n",
				   p_vf->relative_vf_id,
				   QED_ETH_VF_NUM_VLAN_FILTERS + 1);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qed_iov_vf_update_mac_shaकरोw(काष्ठा qed_hwfn *p_hwfn,
					काष्ठा qed_vf_info *p_vf,
					काष्ठा qed_filter_ucast *p_params)
अणु
	पूर्णांक i;

	/* If we're in forced-mode, we don't allow any change */
	अगर (p_vf->bulletin.p_virt->valid_biपंचांगap & BIT(MAC_ADDR_FORCED))
		वापस 0;

	/* Don't keep track of shadow copy since we don't पूर्णांकend to restore. */
	अगर (p_vf->p_vf_info.is_trusted_configured)
		वापस 0;

	/* First हटाओ entries and then add new ones */
	अगर (p_params->opcode == QED_FILTER_REMOVE) अणु
		क्रम (i = 0; i < QED_ETH_VF_NUM_MAC_FILTERS; i++) अणु
			अगर (ether_addr_equal(p_vf->shaकरोw_config.macs[i],
					     p_params->mac)) अणु
				eth_zero_addr(p_vf->shaकरोw_config.macs[i]);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (i == QED_ETH_VF_NUM_MAC_FILTERS) अणु
			DP_VERBOSE(p_hwfn, QED_MSG_IOV,
				   "MAC isn't configured\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (p_params->opcode == QED_FILTER_REPLACE ||
		   p_params->opcode == QED_FILTER_FLUSH) अणु
		क्रम (i = 0; i < QED_ETH_VF_NUM_MAC_FILTERS; i++)
			eth_zero_addr(p_vf->shaकरोw_config.macs[i]);
	पूर्ण

	/* List the new MAC address */
	अगर (p_params->opcode != QED_FILTER_ADD &&
	    p_params->opcode != QED_FILTER_REPLACE)
		वापस 0;

	क्रम (i = 0; i < QED_ETH_VF_NUM_MAC_FILTERS; i++) अणु
		अगर (is_zero_ether_addr(p_vf->shaकरोw_config.macs[i])) अणु
			ether_addr_copy(p_vf->shaकरोw_config.macs[i],
					p_params->mac);
			DP_VERBOSE(p_hwfn, QED_MSG_IOV,
				   "Added MAC at %d entry in shadow\n", i);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == QED_ETH_VF_NUM_MAC_FILTERS) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_IOV, "No available place for MAC\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
qed_iov_vf_update_unicast_shaकरोw(काष्ठा qed_hwfn *p_hwfn,
				 काष्ठा qed_vf_info *p_vf,
				 काष्ठा qed_filter_ucast *p_params)
अणु
	पूर्णांक rc = 0;

	अगर (p_params->type == QED_FILTER_MAC) अणु
		rc = qed_iov_vf_update_mac_shaकरोw(p_hwfn, p_vf, p_params);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (p_params->type == QED_FILTER_VLAN)
		rc = qed_iov_vf_update_vlan_shaकरोw(p_hwfn, p_vf, p_params);

	वापस rc;
पूर्ण

अटल पूर्णांक qed_iov_chk_ucast(काष्ठा qed_hwfn *hwfn,
			     पूर्णांक vfid, काष्ठा qed_filter_ucast *params)
अणु
	काष्ठा qed_खुला_vf_info *vf;

	vf = qed_iov_get_खुला_vf_info(hwfn, vfid, true);
	अगर (!vf)
		वापस -EINVAL;

	/* No real decision to make; Store the configured MAC */
	अगर (params->type == QED_FILTER_MAC ||
	    params->type == QED_FILTER_MAC_VLAN) अणु
		ether_addr_copy(vf->mac, params->mac);

		अगर (vf->is_trusted_configured) अणु
			qed_iov_bulletin_set_mac(hwfn, vf->mac, vfid);

			/* Update and post bulleitin again */
			qed_schedule_iov(hwfn, QED_IOV_WQ_BULLETIN_UPDATE_FLAG);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qed_iov_vf_mbx_ucast_filter(काष्ठा qed_hwfn *p_hwfn,
					काष्ठा qed_ptt *p_ptt,
					काष्ठा qed_vf_info *vf)
अणु
	काष्ठा qed_bulletin_content *p_bulletin = vf->bulletin.p_virt;
	काष्ठा qed_iov_vf_mbx *mbx = &vf->vf_mbx;
	काष्ठा vfpf_ucast_filter_tlv *req;
	u8 status = PFVF_STATUS_SUCCESS;
	काष्ठा qed_filter_ucast params;
	पूर्णांक rc;

	/* Prepare the unicast filter params */
	स_रखो(&params, 0, माप(काष्ठा qed_filter_ucast));
	req = &mbx->req_virt->ucast_filter;
	params.opcode = (क्रमागत qed_filter_opcode)req->opcode;
	params.type = (क्रमागत qed_filter_ucast_type)req->type;

	params.is_rx_filter = 1;
	params.is_tx_filter = 1;
	params.vport_to_हटाओ_from = vf->vport_id;
	params.vport_to_add_to = vf->vport_id;
	स_नकल(params.mac, req->mac, ETH_ALEN);
	params.vlan = req->vlan;

	DP_VERBOSE(p_hwfn,
		   QED_MSG_IOV,
		   "VF[%d]: opcode 0x%02x type 0x%02x [%s %s] [vport 0x%02x] MAC %pM, vlan 0x%04x\n",
		   vf->असल_vf_id, params.opcode, params.type,
		   params.is_rx_filter ? "RX" : "",
		   params.is_tx_filter ? "TX" : "",
		   params.vport_to_add_to,
		   params.mac, params.vlan);

	अगर (!vf->vport_instance) अणु
		DP_VERBOSE(p_hwfn,
			   QED_MSG_IOV,
			   "No VPORT instance available for VF[%d], failing ucast MAC configuration\n",
			   vf->असल_vf_id);
		status = PFVF_STATUS_FAILURE;
		जाओ out;
	पूर्ण

	/* Update shaकरोw copy of the VF configuration */
	अगर (qed_iov_vf_update_unicast_shaकरोw(p_hwfn, vf, &params)) अणु
		status = PFVF_STATUS_FAILURE;
		जाओ out;
	पूर्ण

	/* Determine अगर the unicast filtering is acceptible by PF */
	अगर ((p_bulletin->valid_biपंचांगap & BIT(VLAN_ADDR_FORCED)) &&
	    (params.type == QED_FILTER_VLAN ||
	     params.type == QED_FILTER_MAC_VLAN)) अणु
		/* Once VLAN is क्रमced or PVID is set, करो not allow
		 * to add/replace any further VLANs.
		 */
		अगर (params.opcode == QED_FILTER_ADD ||
		    params.opcode == QED_FILTER_REPLACE)
			status = PFVF_STATUS_FORCED;
		जाओ out;
	पूर्ण

	अगर ((p_bulletin->valid_biपंचांगap & BIT(MAC_ADDR_FORCED)) &&
	    (params.type == QED_FILTER_MAC ||
	     params.type == QED_FILTER_MAC_VLAN)) अणु
		अगर (!ether_addr_equal(p_bulletin->mac, params.mac) ||
		    (params.opcode != QED_FILTER_ADD &&
		     params.opcode != QED_FILTER_REPLACE))
			status = PFVF_STATUS_FORCED;
		जाओ out;
	पूर्ण

	rc = qed_iov_chk_ucast(p_hwfn, vf->relative_vf_id, &params);
	अगर (rc) अणु
		status = PFVF_STATUS_FAILURE;
		जाओ out;
	पूर्ण

	rc = qed_sp_eth_filter_ucast(p_hwfn, vf->opaque_fid, &params,
				     QED_SPQ_MODE_CB, शून्य);
	अगर (rc)
		status = PFVF_STATUS_FAILURE;

out:
	qed_iov_prepare_resp(p_hwfn, p_ptt, vf, CHANNEL_TLV_UCAST_FILTER,
			     माप(काष्ठा pfvf_def_resp_tlv), status);
पूर्ण

अटल व्योम qed_iov_vf_mbx_पूर्णांक_cleanup(काष्ठा qed_hwfn *p_hwfn,
				       काष्ठा qed_ptt *p_ptt,
				       काष्ठा qed_vf_info *vf)
अणु
	पूर्णांक i;

	/* Reset the SBs */
	क्रम (i = 0; i < vf->num_sbs; i++)
		qed_पूर्णांक_igu_init_pure_rt_single(p_hwfn, p_ptt,
						vf->igu_sbs[i],
						vf->opaque_fid, false);

	qed_iov_prepare_resp(p_hwfn, p_ptt, vf, CHANNEL_TLV_INT_CLEANUP,
			     माप(काष्ठा pfvf_def_resp_tlv),
			     PFVF_STATUS_SUCCESS);
पूर्ण

अटल व्योम qed_iov_vf_mbx_बंद(काष्ठा qed_hwfn *p_hwfn,
				 काष्ठा qed_ptt *p_ptt, काष्ठा qed_vf_info *vf)
अणु
	u16 length = माप(काष्ठा pfvf_def_resp_tlv);
	u8 status = PFVF_STATUS_SUCCESS;

	/* Disable Interrupts क्रम VF */
	qed_iov_vf_igu_set_पूर्णांक(p_hwfn, p_ptt, vf, 0);

	/* Reset Permission table */
	qed_iov_config_perm_table(p_hwfn, p_ptt, vf, 0);

	qed_iov_prepare_resp(p_hwfn, p_ptt, vf, CHANNEL_TLV_CLOSE,
			     length, status);
पूर्ण

अटल व्योम qed_iov_vf_mbx_release(काष्ठा qed_hwfn *p_hwfn,
				   काष्ठा qed_ptt *p_ptt,
				   काष्ठा qed_vf_info *p_vf)
अणु
	u16 length = माप(काष्ठा pfvf_def_resp_tlv);
	u8 status = PFVF_STATUS_SUCCESS;
	पूर्णांक rc = 0;

	qed_iov_vf_cleanup(p_hwfn, p_vf);

	अगर (p_vf->state != VF_STOPPED && p_vf->state != VF_FREE) अणु
		/* Stopping the VF */
		rc = qed_sp_vf_stop(p_hwfn, p_vf->concrete_fid,
				    p_vf->opaque_fid);

		अगर (rc) अणु
			DP_ERR(p_hwfn, "qed_sp_vf_stop returned error %d\n",
			       rc);
			status = PFVF_STATUS_FAILURE;
		पूर्ण

		p_vf->state = VF_STOPPED;
	पूर्ण

	qed_iov_prepare_resp(p_hwfn, p_ptt, p_vf, CHANNEL_TLV_RELEASE,
			     length, status);
पूर्ण

अटल व्योम qed_iov_vf_pf_get_coalesce(काष्ठा qed_hwfn *p_hwfn,
				       काष्ठा qed_ptt *p_ptt,
				       काष्ठा qed_vf_info *p_vf)
अणु
	काष्ठा qed_iov_vf_mbx *mbx = &p_vf->vf_mbx;
	काष्ठा pfvf_पढ़ो_coal_resp_tlv *p_resp;
	काष्ठा vfpf_पढ़ो_coal_req_tlv *req;
	u8 status = PFVF_STATUS_FAILURE;
	काष्ठा qed_vf_queue *p_queue;
	काष्ठा qed_queue_cid *p_cid;
	u16 coal = 0, qid, i;
	bool b_is_rx;
	पूर्णांक rc = 0;

	mbx->offset = (u8 *)mbx->reply_virt;
	req = &mbx->req_virt->पढ़ो_coal_req;

	qid = req->qid;
	b_is_rx = req->is_rx ? true : false;

	अगर (b_is_rx) अणु
		अगर (!qed_iov_validate_rxq(p_hwfn, p_vf, qid,
					  QED_IOV_VALIDATE_Q_ENABLE)) अणु
			DP_VERBOSE(p_hwfn, QED_MSG_IOV,
				   "VF[%d]: Invalid Rx queue_id = %d\n",
				   p_vf->असल_vf_id, qid);
			जाओ send_resp;
		पूर्ण

		p_cid = qed_iov_get_vf_rx_queue_cid(&p_vf->vf_queues[qid]);
		rc = qed_get_rxq_coalesce(p_hwfn, p_ptt, p_cid, &coal);
		अगर (rc)
			जाओ send_resp;
	पूर्ण अन्यथा अणु
		अगर (!qed_iov_validate_txq(p_hwfn, p_vf, qid,
					  QED_IOV_VALIDATE_Q_ENABLE)) अणु
			DP_VERBOSE(p_hwfn, QED_MSG_IOV,
				   "VF[%d]: Invalid Tx queue_id = %d\n",
				   p_vf->असल_vf_id, qid);
			जाओ send_resp;
		पूर्ण
		क्रम (i = 0; i < MAX_QUEUES_PER_QZONE; i++) अणु
			p_queue = &p_vf->vf_queues[qid];
			अगर ((!p_queue->cids[i].p_cid) ||
			    (!p_queue->cids[i].b_is_tx))
				जारी;

			p_cid = p_queue->cids[i].p_cid;

			rc = qed_get_txq_coalesce(p_hwfn, p_ptt, p_cid, &coal);
			अगर (rc)
				जाओ send_resp;
			अवरोध;
		पूर्ण
	पूर्ण

	status = PFVF_STATUS_SUCCESS;

send_resp:
	p_resp = qed_add_tlv(p_hwfn, &mbx->offset, CHANNEL_TLV_COALESCE_READ,
			     माप(*p_resp));
	p_resp->coal = coal;

	qed_add_tlv(p_hwfn, &mbx->offset, CHANNEL_TLV_LIST_END,
		    माप(काष्ठा channel_list_end_tlv));

	qed_iov_send_response(p_hwfn, p_ptt, p_vf, माप(*p_resp), status);
पूर्ण

अटल व्योम qed_iov_vf_pf_set_coalesce(काष्ठा qed_hwfn *p_hwfn,
				       काष्ठा qed_ptt *p_ptt,
				       काष्ठा qed_vf_info *vf)
अणु
	काष्ठा qed_iov_vf_mbx *mbx = &vf->vf_mbx;
	काष्ठा vfpf_update_coalesce *req;
	u8 status = PFVF_STATUS_FAILURE;
	काष्ठा qed_queue_cid *p_cid;
	u16 rx_coal, tx_coal;
	पूर्णांक rc = 0, i;
	u16 qid;

	req = &mbx->req_virt->update_coalesce;

	rx_coal = req->rx_coal;
	tx_coal = req->tx_coal;
	qid = req->qid;

	अगर (!qed_iov_validate_rxq(p_hwfn, vf, qid,
				  QED_IOV_VALIDATE_Q_ENABLE) && rx_coal) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "VF[%d]: Invalid Rx queue_id = %d\n",
			   vf->असल_vf_id, qid);
		जाओ out;
	पूर्ण

	अगर (!qed_iov_validate_txq(p_hwfn, vf, qid,
				  QED_IOV_VALIDATE_Q_ENABLE) && tx_coal) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "VF[%d]: Invalid Tx queue_id = %d\n",
			   vf->असल_vf_id, qid);
		जाओ out;
	पूर्ण

	DP_VERBOSE(p_hwfn,
		   QED_MSG_IOV,
		   "VF[%d]: Setting coalesce for VF rx_coal = %d, tx_coal = %d at queue = %d\n",
		   vf->असल_vf_id, rx_coal, tx_coal, qid);

	अगर (rx_coal) अणु
		p_cid = qed_iov_get_vf_rx_queue_cid(&vf->vf_queues[qid]);

		rc = qed_set_rxq_coalesce(p_hwfn, p_ptt, rx_coal, p_cid);
		अगर (rc) अणु
			DP_VERBOSE(p_hwfn,
				   QED_MSG_IOV,
				   "VF[%d]: Unable to set rx queue = %d coalesce\n",
				   vf->असल_vf_id, vf->vf_queues[qid].fw_rx_qid);
			जाओ out;
		पूर्ण
		vf->rx_coal = rx_coal;
	पूर्ण

	अगर (tx_coal) अणु
		काष्ठा qed_vf_queue *p_queue = &vf->vf_queues[qid];

		क्रम (i = 0; i < MAX_QUEUES_PER_QZONE; i++) अणु
			अगर (!p_queue->cids[i].p_cid)
				जारी;

			अगर (!p_queue->cids[i].b_is_tx)
				जारी;

			rc = qed_set_txq_coalesce(p_hwfn, p_ptt, tx_coal,
						  p_queue->cids[i].p_cid);

			अगर (rc) अणु
				DP_VERBOSE(p_hwfn,
					   QED_MSG_IOV,
					   "VF[%d]: Unable to set tx queue coalesce\n",
					   vf->असल_vf_id);
				जाओ out;
			पूर्ण
		पूर्ण
		vf->tx_coal = tx_coal;
	पूर्ण

	status = PFVF_STATUS_SUCCESS;
out:
	qed_iov_prepare_resp(p_hwfn, p_ptt, vf, CHANNEL_TLV_COALESCE_UPDATE,
			     माप(काष्ठा pfvf_def_resp_tlv), status);
पूर्ण
अटल पूर्णांक
qed_iov_vf_flr_poll_करोrq(काष्ठा qed_hwfn *p_hwfn,
			 काष्ठा qed_vf_info *p_vf, काष्ठा qed_ptt *p_ptt)
अणु
	पूर्णांक cnt;
	u32 val;

	qed_fid_pretend(p_hwfn, p_ptt, (u16) p_vf->concrete_fid);

	क्रम (cnt = 0; cnt < 50; cnt++) अणु
		val = qed_rd(p_hwfn, p_ptt, DORQ_REG_VF_USAGE_CNT);
		अगर (!val)
			अवरोध;
		msleep(20);
	पूर्ण
	qed_fid_pretend(p_hwfn, p_ptt, (u16) p_hwfn->hw_info.concrete_fid);

	अगर (cnt == 50) अणु
		DP_ERR(p_hwfn,
		       "VF[%d] - dorq failed to cleanup [usage 0x%08x]\n",
		       p_vf->असल_vf_id, val);
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
qed_iov_vf_flr_poll_pbf(काष्ठा qed_hwfn *p_hwfn,
			काष्ठा qed_vf_info *p_vf, काष्ठा qed_ptt *p_ptt)
अणु
	u32 cons[MAX_NUM_VOQS_E4], distance[MAX_NUM_VOQS_E4];
	पूर्णांक i, cnt;

	/* Read initial consumers & producers */
	क्रम (i = 0; i < MAX_NUM_VOQS_E4; i++) अणु
		u32 prod;

		cons[i] = qed_rd(p_hwfn, p_ptt,
				 PBF_REG_NUM_BLOCKS_ALLOCATED_CONS_VOQ0 +
				 i * 0x40);
		prod = qed_rd(p_hwfn, p_ptt,
			      PBF_REG_NUM_BLOCKS_ALLOCATED_PROD_VOQ0 +
			      i * 0x40);
		distance[i] = prod - cons[i];
	पूर्ण

	/* Wait क्रम consumers to pass the producers */
	i = 0;
	क्रम (cnt = 0; cnt < 50; cnt++) अणु
		क्रम (; i < MAX_NUM_VOQS_E4; i++) अणु
			u32 पंचांगp;

			पंचांगp = qed_rd(p_hwfn, p_ptt,
				     PBF_REG_NUM_BLOCKS_ALLOCATED_CONS_VOQ0 +
				     i * 0x40);
			अगर (distance[i] > पंचांगp - cons[i])
				अवरोध;
		पूर्ण

		अगर (i == MAX_NUM_VOQS_E4)
			अवरोध;

		msleep(20);
	पूर्ण

	अगर (cnt == 50) अणु
		DP_ERR(p_hwfn, "VF[%d] - pbf polling failed on VOQ %d\n",
		       p_vf->असल_vf_id, i);
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qed_iov_vf_flr_poll(काष्ठा qed_hwfn *p_hwfn,
			       काष्ठा qed_vf_info *p_vf, काष्ठा qed_ptt *p_ptt)
अणु
	पूर्णांक rc;

	rc = qed_iov_vf_flr_poll_करोrq(p_hwfn, p_vf, p_ptt);
	अगर (rc)
		वापस rc;

	rc = qed_iov_vf_flr_poll_pbf(p_hwfn, p_vf, p_ptt);
	अगर (rc)
		वापस rc;

	वापस 0;
पूर्ण

अटल पूर्णांक
qed_iov_execute_vf_flr_cleanup(काष्ठा qed_hwfn *p_hwfn,
			       काष्ठा qed_ptt *p_ptt,
			       u16 rel_vf_id, u32 *ack_vfs)
अणु
	काष्ठा qed_vf_info *p_vf;
	पूर्णांक rc = 0;

	p_vf = qed_iov_get_vf_info(p_hwfn, rel_vf_id, false);
	अगर (!p_vf)
		वापस 0;

	अगर (p_hwfn->pf_iov_info->pending_flr[rel_vf_id / 64] &
	    (1ULL << (rel_vf_id % 64))) अणु
		u16 vfid = p_vf->असल_vf_id;

		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "VF[%d] - Handling FLR\n", vfid);

		qed_iov_vf_cleanup(p_hwfn, p_vf);

		/* If VF isn't active, no need क्रम anything but SW */
		अगर (!p_vf->b_init)
			जाओ cleanup;

		rc = qed_iov_vf_flr_poll(p_hwfn, p_vf, p_ptt);
		अगर (rc)
			जाओ cleanup;

		rc = qed_final_cleanup(p_hwfn, p_ptt, vfid, true);
		अगर (rc) अणु
			DP_ERR(p_hwfn, "Failed handle FLR of VF[%d]\n", vfid);
			वापस rc;
		पूर्ण

		/* Workaround to make VF-PF channel पढ़ोy, as FW
		 * करोesn't करो that as a part of FLR.
		 */
		REG_WR(p_hwfn,
		       GTT_BAR0_MAP_REG_USDM_RAM +
		       USTORM_VF_PF_CHANNEL_READY_OFFSET(vfid), 1);

		/* VF_STOPPED has to be set only after final cleanup
		 * but prior to re-enabling the VF.
		 */
		p_vf->state = VF_STOPPED;

		rc = qed_iov_enable_vf_access(p_hwfn, p_ptt, p_vf);
		अगर (rc) अणु
			DP_ERR(p_hwfn, "Failed to re-enable VF[%d] acces\n",
			       vfid);
			वापस rc;
		पूर्ण
cleanup:
		/* Mark VF क्रम ack and clean pending state */
		अगर (p_vf->state == VF_RESET)
			p_vf->state = VF_STOPPED;
		ack_vfs[vfid / 32] |= BIT((vfid % 32));
		p_hwfn->pf_iov_info->pending_flr[rel_vf_id / 64] &=
		    ~(1ULL << (rel_vf_id % 64));
		p_vf->vf_mbx.b_pending_msg = false;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक
qed_iov_vf_flr_cleanup(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	u32 ack_vfs[VF_MAX_STATIC / 32];
	पूर्णांक rc = 0;
	u16 i;

	स_रखो(ack_vfs, 0, माप(u32) * (VF_MAX_STATIC / 32));

	/* Since BRB <-> PRS पूर्णांकerface can't be tested as part of the flr
	 * polling due to HW limitations, simply sleep a bit. And since
	 * there's no need to रुको per-vf, करो it beक्रमe looping.
	 */
	msleep(100);

	क्रम (i = 0; i < p_hwfn->cdev->p_iov_info->total_vfs; i++)
		qed_iov_execute_vf_flr_cleanup(p_hwfn, p_ptt, i, ack_vfs);

	rc = qed_mcp_ack_vf_flr(p_hwfn, p_ptt, ack_vfs);
	वापस rc;
पूर्ण

bool qed_iov_mark_vf_flr(काष्ठा qed_hwfn *p_hwfn, u32 *p_disabled_vfs)
अणु
	bool found = false;
	u16 i;

	DP_VERBOSE(p_hwfn, QED_MSG_IOV, "Marking FLR-ed VFs\n");
	क्रम (i = 0; i < (VF_MAX_STATIC / 32); i++)
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "[%08x,...,%08x]: %08x\n",
			   i * 32, (i + 1) * 32 - 1, p_disabled_vfs[i]);

	अगर (!p_hwfn->cdev->p_iov_info) अणु
		DP_NOTICE(p_hwfn, "VF flr but no IOV\n");
		वापस false;
	पूर्ण

	/* Mark VFs */
	क्रम (i = 0; i < p_hwfn->cdev->p_iov_info->total_vfs; i++) अणु
		काष्ठा qed_vf_info *p_vf;
		u8 vfid;

		p_vf = qed_iov_get_vf_info(p_hwfn, i, false);
		अगर (!p_vf)
			जारी;

		vfid = p_vf->असल_vf_id;
		अगर (BIT((vfid % 32)) & p_disabled_vfs[vfid / 32]) अणु
			u64 *p_flr = p_hwfn->pf_iov_info->pending_flr;
			u16 rel_vf_id = p_vf->relative_vf_id;

			DP_VERBOSE(p_hwfn, QED_MSG_IOV,
				   "VF[%d] [rel %d] got FLR-ed\n",
				   vfid, rel_vf_id);

			p_vf->state = VF_RESET;

			/* No need to lock here, since pending_flr should
			 * only change here and beक्रमe ACKing MFw. Since
			 * MFW will not trigger an additional attention क्रम
			 * VF flr until ACKs, we're safe.
			 */
			p_flr[rel_vf_id / 64] |= 1ULL << (rel_vf_id % 64);
			found = true;
		पूर्ण
	पूर्ण

	वापस found;
पूर्ण

अटल व्योम qed_iov_get_link(काष्ठा qed_hwfn *p_hwfn,
			     u16 vfid,
			     काष्ठा qed_mcp_link_params *p_params,
			     काष्ठा qed_mcp_link_state *p_link,
			     काष्ठा qed_mcp_link_capabilities *p_caps)
अणु
	काष्ठा qed_vf_info *p_vf = qed_iov_get_vf_info(p_hwfn,
						       vfid,
						       false);
	काष्ठा qed_bulletin_content *p_bulletin;

	अगर (!p_vf)
		वापस;

	p_bulletin = p_vf->bulletin.p_virt;

	अगर (p_params)
		__qed_vf_get_link_params(p_hwfn, p_params, p_bulletin);
	अगर (p_link)
		__qed_vf_get_link_state(p_hwfn, p_link, p_bulletin);
	अगर (p_caps)
		__qed_vf_get_link_caps(p_hwfn, p_caps, p_bulletin);
पूर्ण

अटल पूर्णांक
qed_iov_vf_pf_bulletin_update_mac(काष्ठा qed_hwfn *p_hwfn,
				  काष्ठा qed_ptt *p_ptt,
				  काष्ठा qed_vf_info *p_vf)
अणु
	काष्ठा qed_bulletin_content *p_bulletin = p_vf->bulletin.p_virt;
	काष्ठा qed_iov_vf_mbx *mbx = &p_vf->vf_mbx;
	काष्ठा vfpf_bulletin_update_mac_tlv *p_req;
	u8 status = PFVF_STATUS_SUCCESS;
	पूर्णांक rc = 0;

	अगर (!p_vf->p_vf_info.is_trusted_configured) अणु
		DP_VERBOSE(p_hwfn,
			   QED_MSG_IOV,
			   "Blocking bulletin update request from untrusted VF[%d]\n",
			   p_vf->असल_vf_id);
		status = PFVF_STATUS_NOT_SUPPORTED;
		rc = -EINVAL;
		जाओ send_status;
	पूर्ण

	p_req = &mbx->req_virt->bulletin_update_mac;
	ether_addr_copy(p_bulletin->mac, p_req->mac);
	DP_VERBOSE(p_hwfn, QED_MSG_IOV,
		   "Updated bulletin of VF[%d] with requested MAC[%pM]\n",
		   p_vf->असल_vf_id, p_req->mac);

send_status:
	qed_iov_prepare_resp(p_hwfn, p_ptt, p_vf,
			     CHANNEL_TLV_BULLETIN_UPDATE_MAC,
			     माप(काष्ठा pfvf_def_resp_tlv), status);
	वापस rc;
पूर्ण

अटल व्योम qed_iov_process_mbx_req(काष्ठा qed_hwfn *p_hwfn,
				    काष्ठा qed_ptt *p_ptt, पूर्णांक vfid)
अणु
	काष्ठा qed_iov_vf_mbx *mbx;
	काष्ठा qed_vf_info *p_vf;

	p_vf = qed_iov_get_vf_info(p_hwfn, (u16) vfid, true);
	अगर (!p_vf)
		वापस;

	mbx = &p_vf->vf_mbx;

	/* qed_iov_process_mbx_request */
	अगर (!mbx->b_pending_msg) अणु
		DP_NOTICE(p_hwfn,
			  "VF[%02x]: Trying to process mailbox message when none is pending\n",
			  p_vf->असल_vf_id);
		वापस;
	पूर्ण
	mbx->b_pending_msg = false;

	mbx->first_tlv = mbx->req_virt->first_tlv;

	DP_VERBOSE(p_hwfn, QED_MSG_IOV,
		   "VF[%02x]: Processing mailbox message [type %04x]\n",
		   p_vf->असल_vf_id, mbx->first_tlv.tl.type);

	/* check अगर tlv type is known */
	अगर (qed_iov_tlv_supported(mbx->first_tlv.tl.type) &&
	    !p_vf->b_malicious) अणु
		चयन (mbx->first_tlv.tl.type) अणु
		हाल CHANNEL_TLV_ACQUIRE:
			qed_iov_vf_mbx_acquire(p_hwfn, p_ptt, p_vf);
			अवरोध;
		हाल CHANNEL_TLV_VPORT_START:
			qed_iov_vf_mbx_start_vport(p_hwfn, p_ptt, p_vf);
			अवरोध;
		हाल CHANNEL_TLV_VPORT_TEARDOWN:
			qed_iov_vf_mbx_stop_vport(p_hwfn, p_ptt, p_vf);
			अवरोध;
		हाल CHANNEL_TLV_START_RXQ:
			qed_iov_vf_mbx_start_rxq(p_hwfn, p_ptt, p_vf);
			अवरोध;
		हाल CHANNEL_TLV_START_TXQ:
			qed_iov_vf_mbx_start_txq(p_hwfn, p_ptt, p_vf);
			अवरोध;
		हाल CHANNEL_TLV_STOP_RXQS:
			qed_iov_vf_mbx_stop_rxqs(p_hwfn, p_ptt, p_vf);
			अवरोध;
		हाल CHANNEL_TLV_STOP_TXQS:
			qed_iov_vf_mbx_stop_txqs(p_hwfn, p_ptt, p_vf);
			अवरोध;
		हाल CHANNEL_TLV_UPDATE_RXQ:
			qed_iov_vf_mbx_update_rxqs(p_hwfn, p_ptt, p_vf);
			अवरोध;
		हाल CHANNEL_TLV_VPORT_UPDATE:
			qed_iov_vf_mbx_vport_update(p_hwfn, p_ptt, p_vf);
			अवरोध;
		हाल CHANNEL_TLV_UCAST_FILTER:
			qed_iov_vf_mbx_ucast_filter(p_hwfn, p_ptt, p_vf);
			अवरोध;
		हाल CHANNEL_TLV_CLOSE:
			qed_iov_vf_mbx_बंद(p_hwfn, p_ptt, p_vf);
			अवरोध;
		हाल CHANNEL_TLV_INT_CLEANUP:
			qed_iov_vf_mbx_पूर्णांक_cleanup(p_hwfn, p_ptt, p_vf);
			अवरोध;
		हाल CHANNEL_TLV_RELEASE:
			qed_iov_vf_mbx_release(p_hwfn, p_ptt, p_vf);
			अवरोध;
		हाल CHANNEL_TLV_UPDATE_TUNN_PARAM:
			qed_iov_vf_mbx_update_tunn_param(p_hwfn, p_ptt, p_vf);
			अवरोध;
		हाल CHANNEL_TLV_COALESCE_UPDATE:
			qed_iov_vf_pf_set_coalesce(p_hwfn, p_ptt, p_vf);
			अवरोध;
		हाल CHANNEL_TLV_COALESCE_READ:
			qed_iov_vf_pf_get_coalesce(p_hwfn, p_ptt, p_vf);
			अवरोध;
		हाल CHANNEL_TLV_BULLETIN_UPDATE_MAC:
			qed_iov_vf_pf_bulletin_update_mac(p_hwfn, p_ptt, p_vf);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (qed_iov_tlv_supported(mbx->first_tlv.tl.type)) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "VF [%02x] - considered malicious; Ignoring TLV [%04x]\n",
			   p_vf->असल_vf_id, mbx->first_tlv.tl.type);

		qed_iov_prepare_resp(p_hwfn, p_ptt, p_vf,
				     mbx->first_tlv.tl.type,
				     माप(काष्ठा pfvf_def_resp_tlv),
				     PFVF_STATUS_MALICIOUS);
	पूर्ण अन्यथा अणु
		/* unknown TLV - this may beदीर्घ to a VF driver from the future
		 * - a version written after this PF driver was written, which
		 * supports features unknown as of yet. Too bad since we करोn't
		 * support them. Or this may be because someone wrote a crappy
		 * VF driver and is sending garbage over the channel.
		 */
		DP_NOTICE(p_hwfn,
			  "VF[%02x]: unknown TLV. type %04x length %04x padding %08x reply address %llu\n",
			  p_vf->असल_vf_id,
			  mbx->first_tlv.tl.type,
			  mbx->first_tlv.tl.length,
			  mbx->first_tlv.padding, mbx->first_tlv.reply_address);

		/* Try replying in हाल reply address matches the acquisition's
		 * posted address.
		 */
		अगर (p_vf->acquire.first_tlv.reply_address &&
		    (mbx->first_tlv.reply_address ==
		     p_vf->acquire.first_tlv.reply_address)) अणु
			qed_iov_prepare_resp(p_hwfn, p_ptt, p_vf,
					     mbx->first_tlv.tl.type,
					     माप(काष्ठा pfvf_def_resp_tlv),
					     PFVF_STATUS_NOT_SUPPORTED);
		पूर्ण अन्यथा अणु
			DP_VERBOSE(p_hwfn,
				   QED_MSG_IOV,
				   "VF[%02x]: Can't respond to TLV - no valid reply address\n",
				   p_vf->असल_vf_id);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम qed_iov_pf_get_pending_events(काष्ठा qed_hwfn *p_hwfn, u64 *events)
अणु
	पूर्णांक i;

	स_रखो(events, 0, माप(u64) * QED_VF_ARRAY_LENGTH);

	qed_क्रम_each_vf(p_hwfn, i) अणु
		काष्ठा qed_vf_info *p_vf;

		p_vf = &p_hwfn->pf_iov_info->vfs_array[i];
		अगर (p_vf->vf_mbx.b_pending_msg)
			events[i / 64] |= 1ULL << (i % 64);
	पूर्ण
पूर्ण

अटल काष्ठा qed_vf_info *qed_sriov_get_vf_from_असलid(काष्ठा qed_hwfn *p_hwfn,
						       u16 असल_vfid)
अणु
	u8 min = (u8) p_hwfn->cdev->p_iov_info->first_vf_in_pf;

	अगर (!_qed_iov_pf_sanity_check(p_hwfn, (पूर्णांक)असल_vfid - min, false)) अणु
		DP_VERBOSE(p_hwfn,
			   QED_MSG_IOV,
			   "Got indication for VF [abs 0x%08x] that cannot be handled by PF\n",
			   असल_vfid);
		वापस शून्य;
	पूर्ण

	वापस &p_hwfn->pf_iov_info->vfs_array[(u8) असल_vfid - min];
पूर्ण

अटल पूर्णांक qed_sriov_vfpf_msg(काष्ठा qed_hwfn *p_hwfn,
			      u16 असल_vfid, काष्ठा regpair *vf_msg)
अणु
	काष्ठा qed_vf_info *p_vf = qed_sriov_get_vf_from_असलid(p_hwfn,
			   असल_vfid);

	अगर (!p_vf)
		वापस 0;

	/* List the physical address of the request so that handler
	 * could later on copy the message from it.
	 */
	p_vf->vf_mbx.pending_req = HILO_64(vf_msg->hi, vf_msg->lo);

	/* Mark the event and schedule the workqueue */
	p_vf->vf_mbx.b_pending_msg = true;
	qed_schedule_iov(p_hwfn, QED_IOV_WQ_MSG_FLAG);

	वापस 0;
पूर्ण

अटल व्योम qed_sriov_vfpf_malicious(काष्ठा qed_hwfn *p_hwfn,
				     काष्ठा malicious_vf_eqe_data *p_data)
अणु
	काष्ठा qed_vf_info *p_vf;

	p_vf = qed_sriov_get_vf_from_असलid(p_hwfn, p_data->vf_id);

	अगर (!p_vf)
		वापस;

	अगर (!p_vf->b_malicious) अणु
		DP_NOTICE(p_hwfn,
			  "VF [%d] - Malicious behavior [%02x]\n",
			  p_vf->असल_vf_id, p_data->err_id);

		p_vf->b_malicious = true;
	पूर्ण अन्यथा अणु
		DP_INFO(p_hwfn,
			"VF [%d] - Malicious behavior [%02x]\n",
			p_vf->असल_vf_id, p_data->err_id);
	पूर्ण
पूर्ण

अटल पूर्णांक qed_sriov_eqe_event(काष्ठा qed_hwfn *p_hwfn, u8 opcode, __le16 echo,
			       जोड़ event_ring_data *data, u8 fw_वापस_code)
अणु
	चयन (opcode) अणु
	हाल COMMON_EVENT_VF_PF_CHANNEL:
		वापस qed_sriov_vfpf_msg(p_hwfn, le16_to_cpu(echo),
					  &data->vf_pf_channel.msg_addr);
	हाल COMMON_EVENT_MALICIOUS_VF:
		qed_sriov_vfpf_malicious(p_hwfn, &data->malicious_vf);
		वापस 0;
	शेष:
		DP_INFO(p_hwfn->cdev, "Unknown sriov eqe event 0x%02x\n",
			opcode);
		वापस -EINVAL;
	पूर्ण
पूर्ण

u16 qed_iov_get_next_active_vf(काष्ठा qed_hwfn *p_hwfn, u16 rel_vf_id)
अणु
	काष्ठा qed_hw_sriov_info *p_iov = p_hwfn->cdev->p_iov_info;
	u16 i;

	अगर (!p_iov)
		जाओ out;

	क्रम (i = rel_vf_id; i < p_iov->total_vfs; i++)
		अगर (qed_iov_is_valid_vfid(p_hwfn, rel_vf_id, true, false))
			वापस i;

out:
	वापस MAX_NUM_VFS;
पूर्ण

अटल पूर्णांक qed_iov_copy_vf_msg(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *ptt,
			       पूर्णांक vfid)
अणु
	काष्ठा qed_dmae_params params;
	काष्ठा qed_vf_info *vf_info;

	vf_info = qed_iov_get_vf_info(p_hwfn, (u16) vfid, true);
	अगर (!vf_info)
		वापस -EINVAL;

	स_रखो(&params, 0, माप(params));
	SET_FIELD(params.flags, QED_DMAE_PARAMS_SRC_VF_VALID, 0x1);
	SET_FIELD(params.flags, QED_DMAE_PARAMS_COMPLETION_DST, 0x1);
	params.src_vfid = vf_info->असल_vf_id;

	अगर (qed_dmae_host2host(p_hwfn, ptt,
			       vf_info->vf_mbx.pending_req,
			       vf_info->vf_mbx.req_phys,
			       माप(जोड़ vfpf_tlvs) / 4, &params)) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "Failed to copy message from VF 0x%02x\n", vfid);

		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qed_iov_bulletin_set_क्रमced_mac(काष्ठा qed_hwfn *p_hwfn,
					    u8 *mac, पूर्णांक vfid)
अणु
	काष्ठा qed_vf_info *vf_info;
	u64 feature;

	vf_info = qed_iov_get_vf_info(p_hwfn, (u16)vfid, true);
	अगर (!vf_info) अणु
		DP_NOTICE(p_hwfn->cdev,
			  "Can not set forced MAC, invalid vfid [%d]\n", vfid);
		वापस;
	पूर्ण

	अगर (vf_info->b_malicious) अणु
		DP_NOTICE(p_hwfn->cdev,
			  "Can't set forced MAC to malicious VF [%d]\n", vfid);
		वापस;
	पूर्ण

	अगर (vf_info->p_vf_info.is_trusted_configured) अणु
		feature = BIT(VFPF_BULLETIN_MAC_ADDR);
		/* Trust mode will disable Forced MAC */
		vf_info->bulletin.p_virt->valid_biपंचांगap &=
			~BIT(MAC_ADDR_FORCED);
	पूर्ण अन्यथा अणु
		feature = BIT(MAC_ADDR_FORCED);
		/* Forced MAC will disable MAC_ADDR */
		vf_info->bulletin.p_virt->valid_biपंचांगap &=
			~BIT(VFPF_BULLETIN_MAC_ADDR);
	पूर्ण

	स_नकल(vf_info->bulletin.p_virt->mac, mac, ETH_ALEN);

	vf_info->bulletin.p_virt->valid_biपंचांगap |= feature;

	qed_iov_configure_vport_क्रमced(p_hwfn, vf_info, feature);
पूर्ण

अटल पूर्णांक qed_iov_bulletin_set_mac(काष्ठा qed_hwfn *p_hwfn, u8 *mac, पूर्णांक vfid)
अणु
	काष्ठा qed_vf_info *vf_info;
	u64 feature;

	vf_info = qed_iov_get_vf_info(p_hwfn, (u16)vfid, true);
	अगर (!vf_info) अणु
		DP_NOTICE(p_hwfn->cdev, "Can not set MAC, invalid vfid [%d]\n",
			  vfid);
		वापस -EINVAL;
	पूर्ण

	अगर (vf_info->b_malicious) अणु
		DP_NOTICE(p_hwfn->cdev, "Can't set MAC to malicious VF [%d]\n",
			  vfid);
		वापस -EINVAL;
	पूर्ण

	अगर (vf_info->bulletin.p_virt->valid_biपंचांगap & BIT(MAC_ADDR_FORCED)) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "Can not set MAC, Forced MAC is configured\n");
		वापस -EINVAL;
	पूर्ण

	feature = BIT(VFPF_BULLETIN_MAC_ADDR);
	ether_addr_copy(vf_info->bulletin.p_virt->mac, mac);

	vf_info->bulletin.p_virt->valid_biपंचांगap |= feature;

	अगर (vf_info->p_vf_info.is_trusted_configured)
		qed_iov_configure_vport_क्रमced(p_hwfn, vf_info, feature);

	वापस 0;
पूर्ण

अटल व्योम qed_iov_bulletin_set_क्रमced_vlan(काष्ठा qed_hwfn *p_hwfn,
					     u16 pvid, पूर्णांक vfid)
अणु
	काष्ठा qed_vf_info *vf_info;
	u64 feature;

	vf_info = qed_iov_get_vf_info(p_hwfn, (u16) vfid, true);
	अगर (!vf_info) अणु
		DP_NOTICE(p_hwfn->cdev,
			  "Can not set forced MAC, invalid vfid [%d]\n", vfid);
		वापस;
	पूर्ण

	अगर (vf_info->b_malicious) अणु
		DP_NOTICE(p_hwfn->cdev,
			  "Can't set forced vlan to malicious VF [%d]\n", vfid);
		वापस;
	पूर्ण

	feature = 1 << VLAN_ADDR_FORCED;
	vf_info->bulletin.p_virt->pvid = pvid;
	अगर (pvid)
		vf_info->bulletin.p_virt->valid_biपंचांगap |= feature;
	अन्यथा
		vf_info->bulletin.p_virt->valid_biपंचांगap &= ~feature;

	qed_iov_configure_vport_क्रमced(p_hwfn, vf_info, feature);
पूर्ण

व्योम qed_iov_bulletin_set_udp_ports(काष्ठा qed_hwfn *p_hwfn,
				    पूर्णांक vfid, u16 vxlan_port, u16 geneve_port)
अणु
	काष्ठा qed_vf_info *vf_info;

	vf_info = qed_iov_get_vf_info(p_hwfn, (u16)vfid, true);
	अगर (!vf_info) अणु
		DP_NOTICE(p_hwfn->cdev,
			  "Can not set udp ports, invalid vfid [%d]\n", vfid);
		वापस;
	पूर्ण

	अगर (vf_info->b_malicious) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "Can not set udp ports to malicious VF [%d]\n",
			   vfid);
		वापस;
	पूर्ण

	vf_info->bulletin.p_virt->vxlan_udp_port = vxlan_port;
	vf_info->bulletin.p_virt->geneve_udp_port = geneve_port;
पूर्ण

अटल bool qed_iov_vf_has_vport_instance(काष्ठा qed_hwfn *p_hwfn, पूर्णांक vfid)
अणु
	काष्ठा qed_vf_info *p_vf_info;

	p_vf_info = qed_iov_get_vf_info(p_hwfn, (u16) vfid, true);
	अगर (!p_vf_info)
		वापस false;

	वापस !!p_vf_info->vport_instance;
पूर्ण

अटल bool qed_iov_is_vf_stopped(काष्ठा qed_hwfn *p_hwfn, पूर्णांक vfid)
अणु
	काष्ठा qed_vf_info *p_vf_info;

	p_vf_info = qed_iov_get_vf_info(p_hwfn, (u16) vfid, true);
	अगर (!p_vf_info)
		वापस true;

	वापस p_vf_info->state == VF_STOPPED;
पूर्ण

अटल bool qed_iov_spoofchk_get(काष्ठा qed_hwfn *p_hwfn, पूर्णांक vfid)
अणु
	काष्ठा qed_vf_info *vf_info;

	vf_info = qed_iov_get_vf_info(p_hwfn, (u16) vfid, true);
	अगर (!vf_info)
		वापस false;

	वापस vf_info->spoof_chk;
पूर्ण

अटल पूर्णांक qed_iov_spoofchk_set(काष्ठा qed_hwfn *p_hwfn, पूर्णांक vfid, bool val)
अणु
	काष्ठा qed_vf_info *vf;
	पूर्णांक rc = -EINVAL;

	अगर (!qed_iov_pf_sanity_check(p_hwfn, vfid)) अणु
		DP_NOTICE(p_hwfn,
			  "SR-IOV sanity check failed, can't set spoofchk\n");
		जाओ out;
	पूर्ण

	vf = qed_iov_get_vf_info(p_hwfn, (u16) vfid, true);
	अगर (!vf)
		जाओ out;

	अगर (!qed_iov_vf_has_vport_instance(p_hwfn, vfid)) अणु
		/* After VF VPORT start PF will configure spoof check */
		vf->req_spoofchk_val = val;
		rc = 0;
		जाओ out;
	पूर्ण

	rc = __qed_iov_spoofchk_set(p_hwfn, vf, val);

out:
	वापस rc;
पूर्ण

अटल u8 *qed_iov_bulletin_get_mac(काष्ठा qed_hwfn *p_hwfn, u16 rel_vf_id)
अणु
	काष्ठा qed_vf_info *p_vf;

	p_vf = qed_iov_get_vf_info(p_hwfn, rel_vf_id, true);
	अगर (!p_vf || !p_vf->bulletin.p_virt)
		वापस शून्य;

	अगर (!(p_vf->bulletin.p_virt->valid_biपंचांगap &
	      BIT(VFPF_BULLETIN_MAC_ADDR)))
		वापस शून्य;

	वापस p_vf->bulletin.p_virt->mac;
पूर्ण

अटल u8 *qed_iov_bulletin_get_क्रमced_mac(काष्ठा qed_hwfn *p_hwfn,
					   u16 rel_vf_id)
अणु
	काष्ठा qed_vf_info *p_vf;

	p_vf = qed_iov_get_vf_info(p_hwfn, rel_vf_id, true);
	अगर (!p_vf || !p_vf->bulletin.p_virt)
		वापस शून्य;

	अगर (!(p_vf->bulletin.p_virt->valid_biपंचांगap & BIT(MAC_ADDR_FORCED)))
		वापस शून्य;

	वापस p_vf->bulletin.p_virt->mac;
पूर्ण

अटल u16
qed_iov_bulletin_get_क्रमced_vlan(काष्ठा qed_hwfn *p_hwfn, u16 rel_vf_id)
अणु
	काष्ठा qed_vf_info *p_vf;

	p_vf = qed_iov_get_vf_info(p_hwfn, rel_vf_id, true);
	अगर (!p_vf || !p_vf->bulletin.p_virt)
		वापस 0;

	अगर (!(p_vf->bulletin.p_virt->valid_biपंचांगap & BIT(VLAN_ADDR_FORCED)))
		वापस 0;

	वापस p_vf->bulletin.p_virt->pvid;
पूर्ण

अटल पूर्णांक qed_iov_configure_tx_rate(काष्ठा qed_hwfn *p_hwfn,
				     काष्ठा qed_ptt *p_ptt, पूर्णांक vfid, पूर्णांक val)
अणु
	काष्ठा qed_vf_info *vf;
	u8 असल_vp_id = 0;
	u16 rl_id;
	पूर्णांक rc;

	vf = qed_iov_get_vf_info(p_hwfn, (u16)vfid, true);
	अगर (!vf)
		वापस -EINVAL;

	rc = qed_fw_vport(p_hwfn, vf->vport_id, &असल_vp_id);
	अगर (rc)
		वापस rc;

	rl_id = असल_vp_id;	/* The "rl_id" is set as the "vport_id" */
	वापस qed_init_global_rl(p_hwfn, p_ptt, rl_id, (u32)val);
पूर्ण

अटल पूर्णांक
qed_iov_configure_min_tx_rate(काष्ठा qed_dev *cdev, पूर्णांक vfid, u32 rate)
अणु
	काष्ठा qed_vf_info *vf;
	u8 vport_id;
	पूर्णांक i;

	क्रम_each_hwfn(cdev, i) अणु
		काष्ठा qed_hwfn *p_hwfn = &cdev->hwfns[i];

		अगर (!qed_iov_pf_sanity_check(p_hwfn, vfid)) अणु
			DP_NOTICE(p_hwfn,
				  "SR-IOV sanity check failed, can't set min rate\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	vf = qed_iov_get_vf_info(QED_LEADING_HWFN(cdev), (u16)vfid, true);
	vport_id = vf->vport_id;

	वापस qed_configure_vport_wfq(cdev, vport_id, rate);
पूर्ण

अटल पूर्णांक qed_iov_get_vf_min_rate(काष्ठा qed_hwfn *p_hwfn, पूर्णांक vfid)
अणु
	काष्ठा qed_wfq_data *vf_vp_wfq;
	काष्ठा qed_vf_info *vf_info;

	vf_info = qed_iov_get_vf_info(p_hwfn, (u16) vfid, true);
	अगर (!vf_info)
		वापस 0;

	vf_vp_wfq = &p_hwfn->qm_info.wfq_data[vf_info->vport_id];

	अगर (vf_vp_wfq->configured)
		वापस vf_vp_wfq->min_speed;
	अन्यथा
		वापस 0;
पूर्ण

/**
 * qed_schedule_iov - schedules IOV task क्रम VF and PF
 * @hwfn: hardware function poपूर्णांकer
 * @flag: IOV flag क्रम VF/PF
 */
व्योम qed_schedule_iov(काष्ठा qed_hwfn *hwfn, क्रमागत qed_iov_wq_flag flag)
अणु
	smp_mb__beक्रमe_atomic();
	set_bit(flag, &hwfn->iov_task_flags);
	smp_mb__after_atomic();
	DP_VERBOSE(hwfn, QED_MSG_IOV, "Scheduling iov task [Flag: %d]\n", flag);
	queue_delayed_work(hwfn->iov_wq, &hwfn->iov_task, 0);
पूर्ण

व्योम qed_vf_start_iov_wq(काष्ठा qed_dev *cdev)
अणु
	पूर्णांक i;

	क्रम_each_hwfn(cdev, i)
	    queue_delayed_work(cdev->hwfns[i].iov_wq,
			       &cdev->hwfns[i].iov_task, 0);
पूर्ण

पूर्णांक qed_sriov_disable(काष्ठा qed_dev *cdev, bool pci_enabled)
अणु
	पूर्णांक i, j;

	क्रम_each_hwfn(cdev, i)
	    अगर (cdev->hwfns[i].iov_wq)
		flush_workqueue(cdev->hwfns[i].iov_wq);

	/* Mark VFs क्रम disablement */
	qed_iov_set_vfs_to_disable(cdev, true);

	अगर (cdev->p_iov_info && cdev->p_iov_info->num_vfs && pci_enabled)
		pci_disable_sriov(cdev->pdev);

	अगर (cdev->recov_in_prog) अणु
		DP_VERBOSE(cdev,
			   QED_MSG_IOV,
			   "Skip SRIOV disable operations in the device since a recovery is in progress\n");
		जाओ out;
	पूर्ण

	क्रम_each_hwfn(cdev, i) अणु
		काष्ठा qed_hwfn *hwfn = &cdev->hwfns[i];
		काष्ठा qed_ptt *ptt = qed_ptt_acquire(hwfn);

		/* Failure to acquire the ptt in 100g creates an odd error
		 * where the first engine has alपढ़ोy relased IOV.
		 */
		अगर (!ptt) अणु
			DP_ERR(hwfn, "Failed to acquire ptt\n");
			वापस -EBUSY;
		पूर्ण

		/* Clean WFQ db and configure equal weight क्रम all vports */
		qed_clean_wfq_db(hwfn, ptt);

		qed_क्रम_each_vf(hwfn, j) अणु
			पूर्णांक k;

			अगर (!qed_iov_is_valid_vfid(hwfn, j, true, false))
				जारी;

			/* Wait until VF is disabled beक्रमe releasing */
			क्रम (k = 0; k < 100; k++) अणु
				अगर (!qed_iov_is_vf_stopped(hwfn, j))
					msleep(20);
				अन्यथा
					अवरोध;
			पूर्ण

			अगर (k < 100)
				qed_iov_release_hw_क्रम_vf(&cdev->hwfns[i],
							  ptt, j);
			अन्यथा
				DP_ERR(hwfn,
				       "Timeout waiting for VF's FLR to end\n");
		पूर्ण

		qed_ptt_release(hwfn, ptt);
	पूर्ण
out:
	qed_iov_set_vfs_to_disable(cdev, false);

	वापस 0;
पूर्ण

अटल व्योम qed_sriov_enable_qid_config(काष्ठा qed_hwfn *hwfn,
					u16 vfid,
					काष्ठा qed_iov_vf_init_params *params)
अणु
	u16 base, i;

	/* Since we have an equal resource distribution per-VF, and we assume
	 * PF has acquired the QED_PF_L2_QUE first queues, we start setting
	 * sequentially from there.
	 */
	base = FEAT_NUM(hwfn, QED_PF_L2_QUE) + vfid * params->num_queues;

	params->rel_vf_id = vfid;
	क्रम (i = 0; i < params->num_queues; i++) अणु
		params->req_rx_queue[i] = base + i;
		params->req_tx_queue[i] = base + i;
	पूर्ण
पूर्ण

अटल पूर्णांक qed_sriov_enable(काष्ठा qed_dev *cdev, पूर्णांक num)
अणु
	काष्ठा qed_iov_vf_init_params params;
	काष्ठा qed_hwfn *hwfn;
	काष्ठा qed_ptt *ptt;
	पूर्णांक i, j, rc;

	अगर (num >= RESC_NUM(&cdev->hwfns[0], QED_VPORT)) अणु
		DP_NOTICE(cdev, "Can start at most %d VFs\n",
			  RESC_NUM(&cdev->hwfns[0], QED_VPORT) - 1);
		वापस -EINVAL;
	पूर्ण

	स_रखो(&params, 0, माप(params));

	/* Initialize HW क्रम VF access */
	क्रम_each_hwfn(cdev, j) अणु
		hwfn = &cdev->hwfns[j];
		ptt = qed_ptt_acquire(hwfn);

		/* Make sure not to use more than 16 queues per VF */
		params.num_queues = min_t(पूर्णांक,
					  FEAT_NUM(hwfn, QED_VF_L2_QUE) / num,
					  16);

		अगर (!ptt) अणु
			DP_ERR(hwfn, "Failed to acquire ptt\n");
			rc = -EBUSY;
			जाओ err;
		पूर्ण

		क्रम (i = 0; i < num; i++) अणु
			अगर (!qed_iov_is_valid_vfid(hwfn, i, false, true))
				जारी;

			qed_sriov_enable_qid_config(hwfn, i, &params);
			rc = qed_iov_init_hw_क्रम_vf(hwfn, ptt, &params);
			अगर (rc) अणु
				DP_ERR(cdev, "Failed to enable VF[%d]\n", i);
				qed_ptt_release(hwfn, ptt);
				जाओ err;
			पूर्ण
		पूर्ण

		qed_ptt_release(hwfn, ptt);
	पूर्ण

	/* Enable SRIOV PCIe functions */
	rc = pci_enable_sriov(cdev->pdev, num);
	अगर (rc) अणु
		DP_ERR(cdev, "Failed to enable sriov [%d]\n", rc);
		जाओ err;
	पूर्ण

	hwfn = QED_LEADING_HWFN(cdev);
	ptt = qed_ptt_acquire(hwfn);
	अगर (!ptt) अणु
		DP_ERR(hwfn, "Failed to acquire ptt\n");
		rc = -EBUSY;
		जाओ err;
	पूर्ण

	rc = qed_mcp_ov_update_eचयन(hwfn, ptt, QED_OV_ESWITCH_VEB);
	अगर (rc)
		DP_INFO(cdev, "Failed to update eswitch mode\n");
	qed_ptt_release(hwfn, ptt);

	वापस num;

err:
	qed_sriov_disable(cdev, false);
	वापस rc;
पूर्ण

अटल पूर्णांक qed_sriov_configure(काष्ठा qed_dev *cdev, पूर्णांक num_vfs_param)
अणु
	अगर (!IS_QED_SRIOV(cdev)) अणु
		DP_VERBOSE(cdev, QED_MSG_IOV, "SR-IOV is not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (num_vfs_param)
		वापस qed_sriov_enable(cdev, num_vfs_param);
	अन्यथा
		वापस qed_sriov_disable(cdev, true);
पूर्ण

अटल पूर्णांक qed_sriov_pf_set_mac(काष्ठा qed_dev *cdev, u8 *mac, पूर्णांक vfid)
अणु
	पूर्णांक i;

	अगर (!IS_QED_SRIOV(cdev) || !IS_PF_SRIOV_ALLOC(&cdev->hwfns[0])) अणु
		DP_VERBOSE(cdev, QED_MSG_IOV,
			   "Cannot set a VF MAC; Sriov is not enabled\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!qed_iov_is_valid_vfid(&cdev->hwfns[0], vfid, true, true)) अणु
		DP_VERBOSE(cdev, QED_MSG_IOV,
			   "Cannot set VF[%d] MAC (VF is not active)\n", vfid);
		वापस -EINVAL;
	पूर्ण

	क्रम_each_hwfn(cdev, i) अणु
		काष्ठा qed_hwfn *hwfn = &cdev->hwfns[i];
		काष्ठा qed_खुला_vf_info *vf_info;

		vf_info = qed_iov_get_खुला_vf_info(hwfn, vfid, true);
		अगर (!vf_info)
			जारी;

		/* Set the MAC, and schedule the IOV task */
		अगर (vf_info->is_trusted_configured)
			ether_addr_copy(vf_info->mac, mac);
		अन्यथा
			ether_addr_copy(vf_info->क्रमced_mac, mac);

		qed_schedule_iov(hwfn, QED_IOV_WQ_SET_UNICAST_FILTER_FLAG);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qed_sriov_pf_set_vlan(काष्ठा qed_dev *cdev, u16 vid, पूर्णांक vfid)
अणु
	पूर्णांक i;

	अगर (!IS_QED_SRIOV(cdev) || !IS_PF_SRIOV_ALLOC(&cdev->hwfns[0])) अणु
		DP_VERBOSE(cdev, QED_MSG_IOV,
			   "Cannot set a VF MAC; Sriov is not enabled\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!qed_iov_is_valid_vfid(&cdev->hwfns[0], vfid, true, true)) अणु
		DP_VERBOSE(cdev, QED_MSG_IOV,
			   "Cannot set VF[%d] MAC (VF is not active)\n", vfid);
		वापस -EINVAL;
	पूर्ण

	क्रम_each_hwfn(cdev, i) अणु
		काष्ठा qed_hwfn *hwfn = &cdev->hwfns[i];
		काष्ठा qed_खुला_vf_info *vf_info;

		vf_info = qed_iov_get_खुला_vf_info(hwfn, vfid, true);
		अगर (!vf_info)
			जारी;

		/* Set the क्रमced vlan, and schedule the IOV task */
		vf_info->क्रमced_vlan = vid;
		qed_schedule_iov(hwfn, QED_IOV_WQ_SET_UNICAST_FILTER_FLAG);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qed_get_vf_config(काष्ठा qed_dev *cdev,
			     पूर्णांक vf_id, काष्ठा अगरla_vf_info *ivi)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_खुला_vf_info *vf_info;
	काष्ठा qed_mcp_link_state link;
	u32 tx_rate;

	/* Sanitize request */
	अगर (IS_VF(cdev))
		वापस -EINVAL;

	अगर (!qed_iov_is_valid_vfid(&cdev->hwfns[0], vf_id, true, false)) अणु
		DP_VERBOSE(cdev, QED_MSG_IOV,
			   "VF index [%d] isn't active\n", vf_id);
		वापस -EINVAL;
	पूर्ण

	vf_info = qed_iov_get_खुला_vf_info(hwfn, vf_id, true);

	qed_iov_get_link(hwfn, vf_id, शून्य, &link, शून्य);

	/* Fill inक्रमmation about VF */
	ivi->vf = vf_id;

	अगर (is_valid_ether_addr(vf_info->क्रमced_mac))
		ether_addr_copy(ivi->mac, vf_info->क्रमced_mac);
	अन्यथा
		ether_addr_copy(ivi->mac, vf_info->mac);

	ivi->vlan = vf_info->क्रमced_vlan;
	ivi->spoofchk = qed_iov_spoofchk_get(hwfn, vf_id);
	ivi->linkstate = vf_info->link_state;
	tx_rate = vf_info->tx_rate;
	ivi->max_tx_rate = tx_rate ? tx_rate : link.speed;
	ivi->min_tx_rate = qed_iov_get_vf_min_rate(hwfn, vf_id);

	वापस 0;
पूर्ण

व्योम qed_inक्रमm_vf_link_state(काष्ठा qed_hwfn *hwfn)
अणु
	काष्ठा qed_hwfn *lead_hwfn = QED_LEADING_HWFN(hwfn->cdev);
	काष्ठा qed_mcp_link_capabilities caps;
	काष्ठा qed_mcp_link_params params;
	काष्ठा qed_mcp_link_state link;
	पूर्णांक i;

	अगर (!hwfn->pf_iov_info)
		वापस;

	/* Update bulletin of all future possible VFs with link configuration */
	क्रम (i = 0; i < hwfn->cdev->p_iov_info->total_vfs; i++) अणु
		काष्ठा qed_खुला_vf_info *vf_info;

		vf_info = qed_iov_get_खुला_vf_info(hwfn, i, false);
		अगर (!vf_info)
			जारी;

		/* Only hwfn0 is actually पूर्णांकerested in the link speed.
		 * But since only it would receive an MFW indication of link,
		 * need to take configuration from it - otherwise things like
		 * rate limiting क्रम hwfn1 VF would not work.
		 */
		स_नकल(&params, qed_mcp_get_link_params(lead_hwfn),
		       माप(params));
		स_नकल(&link, qed_mcp_get_link_state(lead_hwfn), माप(link));
		स_नकल(&caps, qed_mcp_get_link_capabilities(lead_hwfn),
		       माप(caps));

		/* Modअगरy link according to the VF's configured link state */
		चयन (vf_info->link_state) अणु
		हाल IFLA_VF_LINK_STATE_DISABLE:
			link.link_up = false;
			अवरोध;
		हाल IFLA_VF_LINK_STATE_ENABLE:
			link.link_up = true;
			/* Set speed according to maximum supported by HW.
			 * that is 40G क्रम regular devices and 100G क्रम CMT
			 * mode devices.
			 */
			link.speed = (hwfn->cdev->num_hwfns > 1) ?
				     100000 : 40000;
			अवरोध;
		शेष:
			/* In स्वतः mode pass PF link image to VF */
			अवरोध;
		पूर्ण

		अगर (link.link_up && vf_info->tx_rate) अणु
			काष्ठा qed_ptt *ptt;
			पूर्णांक rate;

			rate = min_t(पूर्णांक, vf_info->tx_rate, link.speed);

			ptt = qed_ptt_acquire(hwfn);
			अगर (!ptt) अणु
				DP_NOTICE(hwfn, "Failed to acquire PTT\n");
				वापस;
			पूर्ण

			अगर (!qed_iov_configure_tx_rate(hwfn, ptt, i, rate)) अणु
				vf_info->tx_rate = rate;
				link.speed = rate;
			पूर्ण

			qed_ptt_release(hwfn, ptt);
		पूर्ण

		qed_iov_set_link(hwfn, i, &params, &link, &caps);
	पूर्ण

	qed_schedule_iov(hwfn, QED_IOV_WQ_BULLETIN_UPDATE_FLAG);
पूर्ण

अटल पूर्णांक qed_set_vf_link_state(काष्ठा qed_dev *cdev,
				 पूर्णांक vf_id, पूर्णांक link_state)
अणु
	पूर्णांक i;

	/* Sanitize request */
	अगर (IS_VF(cdev))
		वापस -EINVAL;

	अगर (!qed_iov_is_valid_vfid(&cdev->hwfns[0], vf_id, true, true)) अणु
		DP_VERBOSE(cdev, QED_MSG_IOV,
			   "VF index [%d] isn't active\n", vf_id);
		वापस -EINVAL;
	पूर्ण

	/* Handle configuration of link state */
	क्रम_each_hwfn(cdev, i) अणु
		काष्ठा qed_hwfn *hwfn = &cdev->hwfns[i];
		काष्ठा qed_खुला_vf_info *vf;

		vf = qed_iov_get_खुला_vf_info(hwfn, vf_id, true);
		अगर (!vf)
			जारी;

		अगर (vf->link_state == link_state)
			जारी;

		vf->link_state = link_state;
		qed_inक्रमm_vf_link_state(&cdev->hwfns[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qed_spoof_configure(काष्ठा qed_dev *cdev, पूर्णांक vfid, bool val)
अणु
	पूर्णांक i, rc = -EINVAL;

	क्रम_each_hwfn(cdev, i) अणु
		काष्ठा qed_hwfn *p_hwfn = &cdev->hwfns[i];

		rc = qed_iov_spoofchk_set(p_hwfn, vfid, val);
		अगर (rc)
			अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक qed_configure_max_vf_rate(काष्ठा qed_dev *cdev, पूर्णांक vfid, पूर्णांक rate)
अणु
	पूर्णांक i;

	क्रम_each_hwfn(cdev, i) अणु
		काष्ठा qed_hwfn *p_hwfn = &cdev->hwfns[i];
		काष्ठा qed_खुला_vf_info *vf;

		अगर (!qed_iov_pf_sanity_check(p_hwfn, vfid)) अणु
			DP_NOTICE(p_hwfn,
				  "SR-IOV sanity check failed, can't set tx rate\n");
			वापस -EINVAL;
		पूर्ण

		vf = qed_iov_get_खुला_vf_info(p_hwfn, vfid, true);

		vf->tx_rate = rate;

		qed_inक्रमm_vf_link_state(p_hwfn);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qed_set_vf_rate(काष्ठा qed_dev *cdev,
			   पूर्णांक vfid, u32 min_rate, u32 max_rate)
अणु
	पूर्णांक rc_min = 0, rc_max = 0;

	अगर (max_rate)
		rc_max = qed_configure_max_vf_rate(cdev, vfid, max_rate);

	अगर (min_rate)
		rc_min = qed_iov_configure_min_tx_rate(cdev, vfid, min_rate);

	अगर (rc_max | rc_min)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक qed_set_vf_trust(काष्ठा qed_dev *cdev, पूर्णांक vfid, bool trust)
अणु
	पूर्णांक i;

	क्रम_each_hwfn(cdev, i) अणु
		काष्ठा qed_hwfn *hwfn = &cdev->hwfns[i];
		काष्ठा qed_खुला_vf_info *vf;

		अगर (!qed_iov_pf_sanity_check(hwfn, vfid)) अणु
			DP_NOTICE(hwfn,
				  "SR-IOV sanity check failed, can't set trust\n");
			वापस -EINVAL;
		पूर्ण

		vf = qed_iov_get_खुला_vf_info(hwfn, vfid, true);

		अगर (vf->is_trusted_request == trust)
			वापस 0;
		vf->is_trusted_request = trust;

		qed_schedule_iov(hwfn, QED_IOV_WQ_TRUST_FLAG);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qed_handle_vf_msg(काष्ठा qed_hwfn *hwfn)
अणु
	u64 events[QED_VF_ARRAY_LENGTH];
	काष्ठा qed_ptt *ptt;
	पूर्णांक i;

	ptt = qed_ptt_acquire(hwfn);
	अगर (!ptt) अणु
		DP_VERBOSE(hwfn, QED_MSG_IOV,
			   "Can't acquire PTT; re-scheduling\n");
		qed_schedule_iov(hwfn, QED_IOV_WQ_MSG_FLAG);
		वापस;
	पूर्ण

	qed_iov_pf_get_pending_events(hwfn, events);

	DP_VERBOSE(hwfn, QED_MSG_IOV,
		   "Event mask of VF events: 0x%llx 0x%llx 0x%llx\n",
		   events[0], events[1], events[2]);

	qed_क्रम_each_vf(hwfn, i) अणु
		/* Skip VFs with no pending messages */
		अगर (!(events[i / 64] & (1ULL << (i % 64))))
			जारी;

		DP_VERBOSE(hwfn, QED_MSG_IOV,
			   "Handling VF message from VF 0x%02x [Abs 0x%02x]\n",
			   i, hwfn->cdev->p_iov_info->first_vf_in_pf + i);

		/* Copy VF's message to PF's request buffer क्रम that VF */
		अगर (qed_iov_copy_vf_msg(hwfn, ptt, i))
			जारी;

		qed_iov_process_mbx_req(hwfn, ptt, i);
	पूर्ण

	qed_ptt_release(hwfn, ptt);
पूर्ण

अटल bool qed_pf_validate_req_vf_mac(काष्ठा qed_hwfn *hwfn,
				       u8 *mac,
				       काष्ठा qed_खुला_vf_info *info)
अणु
	अगर (info->is_trusted_configured) अणु
		अगर (is_valid_ether_addr(info->mac) &&
		    (!mac || !ether_addr_equal(mac, info->mac)))
			वापस true;
	पूर्ण अन्यथा अणु
		अगर (is_valid_ether_addr(info->क्रमced_mac) &&
		    (!mac || !ether_addr_equal(mac, info->क्रमced_mac)))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम qed_set_bulletin_mac(काष्ठा qed_hwfn *hwfn,
				 काष्ठा qed_खुला_vf_info *info,
				 पूर्णांक vfid)
अणु
	अगर (info->is_trusted_configured)
		qed_iov_bulletin_set_mac(hwfn, info->mac, vfid);
	अन्यथा
		qed_iov_bulletin_set_क्रमced_mac(hwfn, info->क्रमced_mac, vfid);
पूर्ण

अटल व्योम qed_handle_pf_set_vf_unicast(काष्ठा qed_hwfn *hwfn)
अणु
	पूर्णांक i;

	qed_क्रम_each_vf(hwfn, i) अणु
		काष्ठा qed_खुला_vf_info *info;
		bool update = false;
		u8 *mac;

		info = qed_iov_get_खुला_vf_info(hwfn, i, true);
		अगर (!info)
			जारी;

		/* Update data on bulletin board */
		अगर (info->is_trusted_configured)
			mac = qed_iov_bulletin_get_mac(hwfn, i);
		अन्यथा
			mac = qed_iov_bulletin_get_क्रमced_mac(hwfn, i);

		अगर (qed_pf_validate_req_vf_mac(hwfn, mac, info)) अणु
			DP_VERBOSE(hwfn,
				   QED_MSG_IOV,
				   "Handling PF setting of VF MAC to VF 0x%02x [Abs 0x%02x]\n",
				   i,
				   hwfn->cdev->p_iov_info->first_vf_in_pf + i);

			/* Update bulletin board with MAC */
			qed_set_bulletin_mac(hwfn, info, i);
			update = true;
		पूर्ण

		अगर (qed_iov_bulletin_get_क्रमced_vlan(hwfn, i) ^
		    info->क्रमced_vlan) अणु
			DP_VERBOSE(hwfn,
				   QED_MSG_IOV,
				   "Handling PF setting of pvid [0x%04x] to VF 0x%02x [Abs 0x%02x]\n",
				   info->क्रमced_vlan,
				   i,
				   hwfn->cdev->p_iov_info->first_vf_in_pf + i);
			qed_iov_bulletin_set_क्रमced_vlan(hwfn,
							 info->क्रमced_vlan, i);
			update = true;
		पूर्ण

		अगर (update)
			qed_schedule_iov(hwfn, QED_IOV_WQ_BULLETIN_UPDATE_FLAG);
	पूर्ण
पूर्ण

अटल व्योम qed_handle_bulletin_post(काष्ठा qed_hwfn *hwfn)
अणु
	काष्ठा qed_ptt *ptt;
	पूर्णांक i;

	ptt = qed_ptt_acquire(hwfn);
	अगर (!ptt) अणु
		DP_NOTICE(hwfn, "Failed allocating a ptt entry\n");
		qed_schedule_iov(hwfn, QED_IOV_WQ_BULLETIN_UPDATE_FLAG);
		वापस;
	पूर्ण

	qed_क्रम_each_vf(hwfn, i)
	    qed_iov_post_vf_bulletin(hwfn, i, ptt);

	qed_ptt_release(hwfn, ptt);
पूर्ण

अटल व्योम qed_update_mac_क्रम_vf_trust_change(काष्ठा qed_hwfn *hwfn, पूर्णांक vf_id)
अणु
	काष्ठा qed_खुला_vf_info *vf_info;
	काष्ठा qed_vf_info *vf;
	u8 *क्रमce_mac;
	पूर्णांक i;

	vf_info = qed_iov_get_खुला_vf_info(hwfn, vf_id, true);
	vf = qed_iov_get_vf_info(hwfn, vf_id, true);

	अगर (!vf_info || !vf)
		वापस;

	/* Force MAC converted to generic MAC in हाल of VF trust on */
	अगर (vf_info->is_trusted_configured &&
	    (vf->bulletin.p_virt->valid_biपंचांगap & BIT(MAC_ADDR_FORCED))) अणु
		क्रमce_mac = qed_iov_bulletin_get_क्रमced_mac(hwfn, vf_id);

		अगर (क्रमce_mac) अणु
			/* Clear existing shaकरोw copy of MAC to have a clean
			 * slate.
			 */
			क्रम (i = 0; i < QED_ETH_VF_NUM_MAC_FILTERS; i++) अणु
				अगर (ether_addr_equal(vf->shaकरोw_config.macs[i],
						     vf_info->mac)) अणु
					eth_zero_addr(vf->shaकरोw_config.macs[i]);
					DP_VERBOSE(hwfn, QED_MSG_IOV,
						   "Shadow MAC %pM removed for VF 0x%02x, VF trust mode is ON\n",
						    vf_info->mac, vf_id);
					अवरोध;
				पूर्ण
			पूर्ण

			ether_addr_copy(vf_info->mac, क्रमce_mac);
			eth_zero_addr(vf_info->क्रमced_mac);
			vf->bulletin.p_virt->valid_biपंचांगap &=
					~BIT(MAC_ADDR_FORCED);
			qed_schedule_iov(hwfn, QED_IOV_WQ_BULLETIN_UPDATE_FLAG);
		पूर्ण
	पूर्ण

	/* Update shaकरोw copy with VF MAC when trust mode is turned off */
	अगर (!vf_info->is_trusted_configured) अणु
		u8 empty_mac[ETH_ALEN];

		eth_zero_addr(empty_mac);
		क्रम (i = 0; i < QED_ETH_VF_NUM_MAC_FILTERS; i++) अणु
			अगर (ether_addr_equal(vf->shaकरोw_config.macs[i],
					     empty_mac)) अणु
				ether_addr_copy(vf->shaकरोw_config.macs[i],
						vf_info->mac);
				DP_VERBOSE(hwfn, QED_MSG_IOV,
					   "Shadow is updated with %pM for VF 0x%02x, VF trust mode is OFF\n",
					    vf_info->mac, vf_id);
				अवरोध;
			पूर्ण
		पूर्ण
		/* Clear bulletin when trust mode is turned off,
		 * to have a clean slate क्रम next (normal) operations.
		 */
		qed_iov_bulletin_set_mac(hwfn, empty_mac, vf_id);
		qed_schedule_iov(hwfn, QED_IOV_WQ_BULLETIN_UPDATE_FLAG);
	पूर्ण
पूर्ण

अटल व्योम qed_iov_handle_trust_change(काष्ठा qed_hwfn *hwfn)
अणु
	काष्ठा qed_sp_vport_update_params params;
	काष्ठा qed_filter_accept_flags *flags;
	काष्ठा qed_खुला_vf_info *vf_info;
	काष्ठा qed_vf_info *vf;
	u8 mask;
	पूर्णांक i;

	mask = QED_ACCEPT_UCAST_UNMATCHED | QED_ACCEPT_MCAST_UNMATCHED;
	flags = &params.accept_flags;

	qed_क्रम_each_vf(hwfn, i) अणु
		/* Need to make sure current requested configuration didn't
		 * flip so that we'll end up configuring something that's not
		 * needed.
		 */
		vf_info = qed_iov_get_खुला_vf_info(hwfn, i, true);
		अगर (vf_info->is_trusted_configured ==
		    vf_info->is_trusted_request)
			जारी;
		vf_info->is_trusted_configured = vf_info->is_trusted_request;

		/* Handle क्रमced MAC mode */
		qed_update_mac_क्रम_vf_trust_change(hwfn, i);

		/* Validate that the VF has a configured vport */
		vf = qed_iov_get_vf_info(hwfn, i, true);
		अगर (!vf->vport_instance)
			जारी;

		स_रखो(&params, 0, माप(params));
		params.opaque_fid = vf->opaque_fid;
		params.vport_id = vf->vport_id;

		params.update_ctl_frame_check = 1;
		params.mac_chk_en = !vf_info->is_trusted_configured;

		अगर (vf_info->rx_accept_mode & mask) अणु
			flags->update_rx_mode_config = 1;
			flags->rx_accept_filter = vf_info->rx_accept_mode;
		पूर्ण

		अगर (vf_info->tx_accept_mode & mask) अणु
			flags->update_tx_mode_config = 1;
			flags->tx_accept_filter = vf_info->tx_accept_mode;
		पूर्ण

		/* Remove अगर needed; Otherwise this would set the mask */
		अगर (!vf_info->is_trusted_configured) अणु
			flags->rx_accept_filter &= ~mask;
			flags->tx_accept_filter &= ~mask;
		पूर्ण

		अगर (flags->update_rx_mode_config ||
		    flags->update_tx_mode_config ||
		    params.update_ctl_frame_check)
			qed_sp_vport_update(hwfn, &params,
					    QED_SPQ_MODE_EBLOCK, शून्य);
	पूर्ण
पूर्ण

अटल व्योम qed_iov_pf_task(काष्ठा work_काष्ठा *work)

अणु
	काष्ठा qed_hwfn *hwfn = container_of(work, काष्ठा qed_hwfn,
					     iov_task.work);
	पूर्णांक rc;

	अगर (test_and_clear_bit(QED_IOV_WQ_STOP_WQ_FLAG, &hwfn->iov_task_flags))
		वापस;

	अगर (test_and_clear_bit(QED_IOV_WQ_FLR_FLAG, &hwfn->iov_task_flags)) अणु
		काष्ठा qed_ptt *ptt = qed_ptt_acquire(hwfn);

		अगर (!ptt) अणु
			qed_schedule_iov(hwfn, QED_IOV_WQ_FLR_FLAG);
			वापस;
		पूर्ण

		rc = qed_iov_vf_flr_cleanup(hwfn, ptt);
		अगर (rc)
			qed_schedule_iov(hwfn, QED_IOV_WQ_FLR_FLAG);

		qed_ptt_release(hwfn, ptt);
	पूर्ण

	अगर (test_and_clear_bit(QED_IOV_WQ_MSG_FLAG, &hwfn->iov_task_flags))
		qed_handle_vf_msg(hwfn);

	अगर (test_and_clear_bit(QED_IOV_WQ_SET_UNICAST_FILTER_FLAG,
			       &hwfn->iov_task_flags))
		qed_handle_pf_set_vf_unicast(hwfn);

	अगर (test_and_clear_bit(QED_IOV_WQ_BULLETIN_UPDATE_FLAG,
			       &hwfn->iov_task_flags))
		qed_handle_bulletin_post(hwfn);

	अगर (test_and_clear_bit(QED_IOV_WQ_TRUST_FLAG, &hwfn->iov_task_flags))
		qed_iov_handle_trust_change(hwfn);
पूर्ण

व्योम qed_iov_wq_stop(काष्ठा qed_dev *cdev, bool schedule_first)
अणु
	पूर्णांक i;

	क्रम_each_hwfn(cdev, i) अणु
		अगर (!cdev->hwfns[i].iov_wq)
			जारी;

		अगर (schedule_first) अणु
			qed_schedule_iov(&cdev->hwfns[i],
					 QED_IOV_WQ_STOP_WQ_FLAG);
			cancel_delayed_work_sync(&cdev->hwfns[i].iov_task);
		पूर्ण

		flush_workqueue(cdev->hwfns[i].iov_wq);
		destroy_workqueue(cdev->hwfns[i].iov_wq);
	पूर्ण
पूर्ण

पूर्णांक qed_iov_wq_start(काष्ठा qed_dev *cdev)
अणु
	अक्षर name[NAME_SIZE];
	पूर्णांक i;

	क्रम_each_hwfn(cdev, i) अणु
		काष्ठा qed_hwfn *p_hwfn = &cdev->hwfns[i];

		/* PFs needs a dedicated workqueue only अगर they support IOV.
		 * VFs always require one.
		 */
		अगर (IS_PF(p_hwfn->cdev) && !IS_PF_SRIOV(p_hwfn))
			जारी;

		snम_लिखो(name, NAME_SIZE, "iov-%02x:%02x.%02x",
			 cdev->pdev->bus->number,
			 PCI_SLOT(cdev->pdev->devfn), p_hwfn->असल_pf_id);

		p_hwfn->iov_wq = create_singlethपढ़ो_workqueue(name);
		अगर (!p_hwfn->iov_wq) अणु
			DP_NOTICE(p_hwfn, "Cannot create iov workqueue\n");
			वापस -ENOMEM;
		पूर्ण

		अगर (IS_PF(cdev))
			INIT_DELAYED_WORK(&p_hwfn->iov_task, qed_iov_pf_task);
		अन्यथा
			INIT_DELAYED_WORK(&p_hwfn->iov_task, qed_iov_vf_task);
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा qed_iov_hv_ops qed_iov_ops_pass = अणु
	.configure = &qed_sriov_configure,
	.set_mac = &qed_sriov_pf_set_mac,
	.set_vlan = &qed_sriov_pf_set_vlan,
	.get_config = &qed_get_vf_config,
	.set_link_state = &qed_set_vf_link_state,
	.set_spoof = &qed_spoof_configure,
	.set_rate = &qed_set_vf_rate,
	.set_trust = &qed_set_vf_trust,
पूर्ण;
