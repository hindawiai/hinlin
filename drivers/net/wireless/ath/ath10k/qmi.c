<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2018 The Linux Foundation. All rights reserved.
 */

#समावेश <linux/completion.h>
#समावेश <linux/device.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/idr.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/module.h>
#समावेश <linux/net.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/qcom_scm.h>
#समावेश <linux/माला.स>
#समावेश <net/sock.h>

#समावेश "debug.h"
#समावेश "snoc.h"

#घोषणा ATH10K_QMI_CLIENT_ID		0x4b4e454c
#घोषणा ATH10K_QMI_TIMEOUT		30

अटल पूर्णांक ath10k_qmi_map_msa_permission(काष्ठा ath10k_qmi *qmi,
					 काष्ठा ath10k_msa_mem_info *mem_info)
अणु
	काष्ठा qcom_scm_vmperm dst_perms[3];
	काष्ठा ath10k *ar = qmi->ar;
	अचिन्हित पूर्णांक src_perms;
	u32 perm_count;
	पूर्णांक ret;

	src_perms = BIT(QCOM_SCM_VMID_HLOS);

	dst_perms[0].vmid = QCOM_SCM_VMID_MSS_MSA;
	dst_perms[0].perm = QCOM_SCM_PERM_RW;
	dst_perms[1].vmid = QCOM_SCM_VMID_WLAN;
	dst_perms[1].perm = QCOM_SCM_PERM_RW;

	अगर (mem_info->secure) अणु
		perm_count = 2;
	पूर्ण अन्यथा अणु
		dst_perms[2].vmid = QCOM_SCM_VMID_WLAN_CE;
		dst_perms[2].perm = QCOM_SCM_PERM_RW;
		perm_count = 3;
	पूर्ण

	ret = qcom_scm_assign_mem(mem_info->addr, mem_info->size,
				  &src_perms, dst_perms, perm_count);
	अगर (ret < 0)
		ath10k_err(ar, "failed to assign msa map permissions: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_qmi_unmap_msa_permission(काष्ठा ath10k_qmi *qmi,
					   काष्ठा ath10k_msa_mem_info *mem_info)
अणु
	काष्ठा qcom_scm_vmperm dst_perms;
	काष्ठा ath10k *ar = qmi->ar;
	अचिन्हित पूर्णांक src_perms;
	पूर्णांक ret;

	src_perms = BIT(QCOM_SCM_VMID_MSS_MSA) | BIT(QCOM_SCM_VMID_WLAN);

	अगर (!mem_info->secure)
		src_perms |= BIT(QCOM_SCM_VMID_WLAN_CE);

	dst_perms.vmid = QCOM_SCM_VMID_HLOS;
	dst_perms.perm = QCOM_SCM_PERM_RW;

	ret = qcom_scm_assign_mem(mem_info->addr, mem_info->size,
				  &src_perms, &dst_perms, 1);
	अगर (ret < 0)
		ath10k_err(ar, "failed to unmap msa permissions: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_qmi_setup_msa_permissions(काष्ठा ath10k_qmi *qmi)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	अगर (qmi->msa_fixed_perm)
		वापस 0;

	क्रम (i = 0; i < qmi->nr_mem_region; i++) अणु
		ret = ath10k_qmi_map_msa_permission(qmi, &qmi->mem_region[i]);
		अगर (ret)
			जाओ err_unmap;
	पूर्ण

	वापस 0;

err_unmap:
	क्रम (i--; i >= 0; i--)
		ath10k_qmi_unmap_msa_permission(qmi, &qmi->mem_region[i]);
	वापस ret;
पूर्ण

अटल व्योम ath10k_qmi_हटाओ_msa_permission(काष्ठा ath10k_qmi *qmi)
अणु
	पूर्णांक i;

	अगर (qmi->msa_fixed_perm)
		वापस;

	क्रम (i = 0; i < qmi->nr_mem_region; i++)
		ath10k_qmi_unmap_msa_permission(qmi, &qmi->mem_region[i]);
पूर्ण

अटल पूर्णांक ath10k_qmi_msa_mem_info_send_sync_msg(काष्ठा ath10k_qmi *qmi)
अणु
	काष्ठा wlfw_msa_info_resp_msg_v01 resp = अणुपूर्ण;
	काष्ठा wlfw_msa_info_req_msg_v01 req = अणुपूर्ण;
	काष्ठा ath10k *ar = qmi->ar;
	phys_addr_t max_mapped_addr;
	काष्ठा qmi_txn txn;
	पूर्णांक ret;
	पूर्णांक i;

	req.msa_addr = ar->msa.paddr;
	req.size = ar->msa.mem_size;

	ret = qmi_txn_init(&qmi->qmi_hdl, &txn,
			   wlfw_msa_info_resp_msg_v01_ei, &resp);
	अगर (ret < 0)
		जाओ out;

	ret = qmi_send_request(&qmi->qmi_hdl, शून्य, &txn,
			       QMI_WLFW_MSA_INFO_REQ_V01,
			       WLFW_MSA_INFO_REQ_MSG_V01_MAX_MSG_LEN,
			       wlfw_msa_info_req_msg_v01_ei, &req);
	अगर (ret < 0) अणु
		qmi_txn_cancel(&txn);
		ath10k_err(ar, "failed to send msa mem info req: %d\n", ret);
		जाओ out;
	पूर्ण

	ret = qmi_txn_रुको(&txn, ATH10K_QMI_TIMEOUT * HZ);
	अगर (ret < 0)
		जाओ out;

	अगर (resp.resp.result != QMI_RESULT_SUCCESS_V01) अणु
		ath10k_err(ar, "msa info req rejected: %d\n", resp.resp.error);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (resp.mem_region_info_len > QMI_WLFW_MAX_MEM_REG_V01) अणु
		ath10k_err(ar, "invalid memory region length received: %d\n",
			   resp.mem_region_info_len);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	max_mapped_addr = ar->msa.paddr + ar->msa.mem_size;
	qmi->nr_mem_region = resp.mem_region_info_len;
	क्रम (i = 0; i < resp.mem_region_info_len; i++) अणु
		अगर (resp.mem_region_info[i].size > ar->msa.mem_size ||
		    resp.mem_region_info[i].region_addr > max_mapped_addr ||
		    resp.mem_region_info[i].region_addr < ar->msa.paddr ||
		    resp.mem_region_info[i].size +
		    resp.mem_region_info[i].region_addr > max_mapped_addr) अणु
			ath10k_err(ar, "received out of range memory region address 0x%llx with size 0x%x, aborting\n",
				   resp.mem_region_info[i].region_addr,
				   resp.mem_region_info[i].size);
			ret = -EINVAL;
			जाओ fail_unwind;
		पूर्ण
		qmi->mem_region[i].addr = resp.mem_region_info[i].region_addr;
		qmi->mem_region[i].size = resp.mem_region_info[i].size;
		qmi->mem_region[i].secure = resp.mem_region_info[i].secure_flag;
		ath10k_dbg(ar, ATH10K_DBG_QMI,
			   "qmi msa mem region %d addr 0x%pa size 0x%x flag 0x%08x\n",
			   i, &qmi->mem_region[i].addr,
			   qmi->mem_region[i].size,
			   qmi->mem_region[i].secure);
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_QMI, "qmi msa mem info request completed\n");
	वापस 0;

fail_unwind:
	स_रखो(&qmi->mem_region[0], 0, माप(qmi->mem_region[0]) * i);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_qmi_msa_पढ़ोy_send_sync_msg(काष्ठा ath10k_qmi *qmi)
अणु
	काष्ठा wlfw_msa_पढ़ोy_resp_msg_v01 resp = अणुपूर्ण;
	काष्ठा wlfw_msa_पढ़ोy_req_msg_v01 req = अणुपूर्ण;
	काष्ठा ath10k *ar = qmi->ar;
	काष्ठा qmi_txn txn;
	पूर्णांक ret;

	ret = qmi_txn_init(&qmi->qmi_hdl, &txn,
			   wlfw_msa_पढ़ोy_resp_msg_v01_ei, &resp);
	अगर (ret < 0)
		जाओ out;

	ret = qmi_send_request(&qmi->qmi_hdl, शून्य, &txn,
			       QMI_WLFW_MSA_READY_REQ_V01,
			       WLFW_MSA_READY_REQ_MSG_V01_MAX_MSG_LEN,
			       wlfw_msa_पढ़ोy_req_msg_v01_ei, &req);
	अगर (ret < 0) अणु
		qmi_txn_cancel(&txn);
		ath10k_err(ar, "failed to send msa mem ready request: %d\n", ret);
		जाओ out;
	पूर्ण

	ret = qmi_txn_रुको(&txn, ATH10K_QMI_TIMEOUT * HZ);
	अगर (ret < 0)
		जाओ out;

	अगर (resp.resp.result != QMI_RESULT_SUCCESS_V01) अणु
		ath10k_err(ar, "msa ready request rejected: %d\n", resp.resp.error);
		ret = -EINVAL;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_QMI, "qmi msa mem ready request completed\n");
	वापस 0;

out:
	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_qmi_bdf_dnld_send_sync(काष्ठा ath10k_qmi *qmi)
अणु
	काष्ठा wlfw_bdf_करोwnload_resp_msg_v01 resp = अणुपूर्ण;
	काष्ठा wlfw_bdf_करोwnload_req_msg_v01 *req;
	काष्ठा ath10k *ar = qmi->ar;
	अचिन्हित पूर्णांक reमुख्यing;
	काष्ठा qmi_txn txn;
	स्थिर u8 *temp;
	पूर्णांक ret;

	req = kzalloc(माप(*req), GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	temp = ar->normal_mode_fw.board_data;
	reमुख्यing = ar->normal_mode_fw.board_len;

	जबतक (reमुख्यing) अणु
		req->valid = 1;
		req->file_id_valid = 1;
		req->file_id = 0;
		req->total_size_valid = 1;
		req->total_size = ar->normal_mode_fw.board_len;
		req->seg_id_valid = 1;
		req->data_valid = 1;
		req->end_valid = 1;

		अगर (reमुख्यing > QMI_WLFW_MAX_DATA_SIZE_V01) अणु
			req->data_len = QMI_WLFW_MAX_DATA_SIZE_V01;
		पूर्ण अन्यथा अणु
			req->data_len = reमुख्यing;
			req->end = 1;
		पूर्ण

		स_नकल(req->data, temp, req->data_len);

		ret = qmi_txn_init(&qmi->qmi_hdl, &txn,
				   wlfw_bdf_करोwnload_resp_msg_v01_ei,
				   &resp);
		अगर (ret < 0)
			जाओ out;

		ret = qmi_send_request(&qmi->qmi_hdl, शून्य, &txn,
				       QMI_WLFW_BDF_DOWNLOAD_REQ_V01,
				       WLFW_BDF_DOWNLOAD_REQ_MSG_V01_MAX_MSG_LEN,
				       wlfw_bdf_करोwnload_req_msg_v01_ei, req);
		अगर (ret < 0) अणु
			qmi_txn_cancel(&txn);
			जाओ out;
		पूर्ण

		ret = qmi_txn_रुको(&txn, ATH10K_QMI_TIMEOUT * HZ);

		अगर (ret < 0)
			जाओ out;

		/* end = 1 triggers a CRC check on the BDF.  If this fails, we
		 * get a QMI_ERR_MALFORMED_MSG_V01 error, but the FW is still
		 * willing to use the BDF.  For some platक्रमms, all the valid
		 * released BDFs fail this CRC check, so attempt to detect this
		 * scenario and treat it as non-fatal.
		 */
		अगर (resp.resp.result != QMI_RESULT_SUCCESS_V01 &&
		    !(req->end == 1 &&
		      resp.resp.result == QMI_ERR_MALFORMED_MSG_V01)) अणु
			ath10k_err(ar, "failed to download board data file: %d\n",
				   resp.resp.error);
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		reमुख्यing -= req->data_len;
		temp += req->data_len;
		req->seg_id++;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_QMI, "qmi bdf download request completed\n");

	kमुक्त(req);
	वापस 0;

out:
	kमुक्त(req);
	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_qmi_send_cal_report_req(काष्ठा ath10k_qmi *qmi)
अणु
	काष्ठा wlfw_cal_report_resp_msg_v01 resp = अणुपूर्ण;
	काष्ठा wlfw_cal_report_req_msg_v01 req = अणुपूर्ण;
	काष्ठा ath10k *ar = qmi->ar;
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	काष्ठा qmi_txn txn;
	पूर्णांक i, j = 0;
	पूर्णांक ret;

	अगर (ar_snoc->xo_cal_supported) अणु
		req.xo_cal_data_valid = 1;
		req.xo_cal_data = ar_snoc->xo_cal_data;
	पूर्ण

	ret = qmi_txn_init(&qmi->qmi_hdl, &txn, wlfw_cal_report_resp_msg_v01_ei,
			   &resp);
	अगर (ret < 0)
		जाओ out;

	क्रम (i = 0; i < QMI_WLFW_MAX_NUM_CAL_V01; i++) अणु
		अगर (qmi->cal_data[i].total_size &&
		    qmi->cal_data[i].data) अणु
			req.meta_data[j] = qmi->cal_data[i].cal_id;
			j++;
		पूर्ण
	पूर्ण
	req.meta_data_len = j;

	ret = qmi_send_request(&qmi->qmi_hdl, शून्य, &txn,
			       QMI_WLFW_CAL_REPORT_REQ_V01,
			       WLFW_CAL_REPORT_REQ_MSG_V01_MAX_MSG_LEN,
			       wlfw_cal_report_req_msg_v01_ei, &req);
	अगर (ret < 0) अणु
		qmi_txn_cancel(&txn);
		ath10k_err(ar, "failed to send calibration request: %d\n", ret);
		जाओ out;
	पूर्ण

	ret = qmi_txn_रुको(&txn, ATH10K_QMI_TIMEOUT * HZ);
	अगर (ret < 0)
		जाओ out;

	अगर (resp.resp.result != QMI_RESULT_SUCCESS_V01) अणु
		ath10k_err(ar, "calibration request rejected: %d\n", resp.resp.error);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_QMI, "qmi cal report request completed\n");
	वापस 0;

out:
	वापस ret;
पूर्ण

अटल पूर्णांक
ath10k_qmi_mode_send_sync_msg(काष्ठा ath10k *ar, क्रमागत wlfw_driver_mode_क्रमागत_v01 mode)
अणु
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	काष्ठा ath10k_qmi *qmi = ar_snoc->qmi;
	काष्ठा wlfw_wlan_mode_resp_msg_v01 resp = अणुपूर्ण;
	काष्ठा wlfw_wlan_mode_req_msg_v01 req = अणुपूर्ण;
	काष्ठा qmi_txn txn;
	पूर्णांक ret;

	ret = qmi_txn_init(&qmi->qmi_hdl, &txn,
			   wlfw_wlan_mode_resp_msg_v01_ei,
			   &resp);
	अगर (ret < 0)
		जाओ out;

	req.mode = mode;
	req.hw_debug_valid = 1;
	req.hw_debug = 0;

	ret = qmi_send_request(&qmi->qmi_hdl, शून्य, &txn,
			       QMI_WLFW_WLAN_MODE_REQ_V01,
			       WLFW_WLAN_MODE_REQ_MSG_V01_MAX_MSG_LEN,
			       wlfw_wlan_mode_req_msg_v01_ei, &req);
	अगर (ret < 0) अणु
		qmi_txn_cancel(&txn);
		ath10k_err(ar, "failed to send wlan mode %d request: %d\n", mode, ret);
		जाओ out;
	पूर्ण

	ret = qmi_txn_रुको(&txn, ATH10K_QMI_TIMEOUT * HZ);
	अगर (ret < 0)
		जाओ out;

	अगर (resp.resp.result != QMI_RESULT_SUCCESS_V01) अणु
		ath10k_err(ar, "more request rejected: %d\n", resp.resp.error);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_QMI, "qmi wlan mode req completed: %d\n", mode);
	वापस 0;

out:
	वापस ret;
पूर्ण

अटल पूर्णांक
ath10k_qmi_cfg_send_sync_msg(काष्ठा ath10k *ar,
			     काष्ठा ath10k_qmi_wlan_enable_cfg *config,
			     स्थिर अक्षर *version)
अणु
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	काष्ठा ath10k_qmi *qmi = ar_snoc->qmi;
	काष्ठा wlfw_wlan_cfg_resp_msg_v01 resp = अणुपूर्ण;
	काष्ठा wlfw_wlan_cfg_req_msg_v01 *req;
	काष्ठा qmi_txn txn;
	पूर्णांक ret;
	u32 i;

	req = kzalloc(माप(*req), GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	ret = qmi_txn_init(&qmi->qmi_hdl, &txn,
			   wlfw_wlan_cfg_resp_msg_v01_ei,
			   &resp);
	अगर (ret < 0)
		जाओ out;

	req->host_version_valid = 0;

	req->tgt_cfg_valid = 1;
	अगर (config->num_ce_tgt_cfg > QMI_WLFW_MAX_NUM_CE_V01)
		req->tgt_cfg_len = QMI_WLFW_MAX_NUM_CE_V01;
	अन्यथा
		req->tgt_cfg_len = config->num_ce_tgt_cfg;
	क्रम (i = 0; i < req->tgt_cfg_len; i++) अणु
		req->tgt_cfg[i].pipe_num = config->ce_tgt_cfg[i].pipe_num;
		req->tgt_cfg[i].pipe_dir = config->ce_tgt_cfg[i].pipe_dir;
		req->tgt_cfg[i].nentries = config->ce_tgt_cfg[i].nentries;
		req->tgt_cfg[i].nbytes_max = config->ce_tgt_cfg[i].nbytes_max;
		req->tgt_cfg[i].flags = config->ce_tgt_cfg[i].flags;
	पूर्ण

	req->svc_cfg_valid = 1;
	अगर (config->num_ce_svc_pipe_cfg > QMI_WLFW_MAX_NUM_SVC_V01)
		req->svc_cfg_len = QMI_WLFW_MAX_NUM_SVC_V01;
	अन्यथा
		req->svc_cfg_len = config->num_ce_svc_pipe_cfg;
	क्रम (i = 0; i < req->svc_cfg_len; i++) अणु
		req->svc_cfg[i].service_id = config->ce_svc_cfg[i].service_id;
		req->svc_cfg[i].pipe_dir = config->ce_svc_cfg[i].pipe_dir;
		req->svc_cfg[i].pipe_num = config->ce_svc_cfg[i].pipe_num;
	पूर्ण

	req->shaकरोw_reg_valid = 1;
	अगर (config->num_shaकरोw_reg_cfg >
	    QMI_WLFW_MAX_NUM_SHADOW_REG_V01)
		req->shaकरोw_reg_len = QMI_WLFW_MAX_NUM_SHADOW_REG_V01;
	अन्यथा
		req->shaकरोw_reg_len = config->num_shaकरोw_reg_cfg;

	स_नकल(req->shaकरोw_reg, config->shaकरोw_reg_cfg,
	       माप(काष्ठा wlfw_shaकरोw_reg_cfg_s_v01) * req->shaकरोw_reg_len);

	ret = qmi_send_request(&qmi->qmi_hdl, शून्य, &txn,
			       QMI_WLFW_WLAN_CFG_REQ_V01,
			       WLFW_WLAN_CFG_REQ_MSG_V01_MAX_MSG_LEN,
			       wlfw_wlan_cfg_req_msg_v01_ei, req);
	अगर (ret < 0) अणु
		qmi_txn_cancel(&txn);
		ath10k_err(ar, "failed to send config request: %d\n", ret);
		जाओ out;
	पूर्ण

	ret = qmi_txn_रुको(&txn, ATH10K_QMI_TIMEOUT * HZ);
	अगर (ret < 0)
		जाओ out;

	अगर (resp.resp.result != QMI_RESULT_SUCCESS_V01) अणु
		ath10k_err(ar, "config request rejected: %d\n", resp.resp.error);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_QMI, "qmi config request completed\n");
	kमुक्त(req);
	वापस 0;

out:
	kमुक्त(req);
	वापस ret;
पूर्ण

पूर्णांक ath10k_qmi_wlan_enable(काष्ठा ath10k *ar,
			   काष्ठा ath10k_qmi_wlan_enable_cfg *config,
			   क्रमागत wlfw_driver_mode_क्रमागत_v01 mode,
			   स्थिर अक्षर *version)
अणु
	पूर्णांक ret;

	ath10k_dbg(ar, ATH10K_DBG_QMI, "qmi mode %d config %p\n",
		   mode, config);

	ret = ath10k_qmi_cfg_send_sync_msg(ar, config, version);
	अगर (ret) अणु
		ath10k_err(ar, "failed to send qmi config: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ath10k_qmi_mode_send_sync_msg(ar, mode);
	अगर (ret) अणु
		ath10k_err(ar, "failed to send qmi mode: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ath10k_qmi_wlan_disable(काष्ठा ath10k *ar)
अणु
	वापस ath10k_qmi_mode_send_sync_msg(ar, QMI_WLFW_OFF_V01);
पूर्ण

अटल पूर्णांक ath10k_qmi_cap_send_sync_msg(काष्ठा ath10k_qmi *qmi)
अणु
	काष्ठा wlfw_cap_resp_msg_v01 *resp;
	काष्ठा wlfw_cap_req_msg_v01 req = अणुपूर्ण;
	काष्ठा ath10k *ar = qmi->ar;
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	काष्ठा qmi_txn txn;
	पूर्णांक ret;

	resp = kzalloc(माप(*resp), GFP_KERNEL);
	अगर (!resp)
		वापस -ENOMEM;

	ret = qmi_txn_init(&qmi->qmi_hdl, &txn, wlfw_cap_resp_msg_v01_ei, resp);
	अगर (ret < 0)
		जाओ out;

	ret = qmi_send_request(&qmi->qmi_hdl, शून्य, &txn,
			       QMI_WLFW_CAP_REQ_V01,
			       WLFW_CAP_REQ_MSG_V01_MAX_MSG_LEN,
			       wlfw_cap_req_msg_v01_ei, &req);
	अगर (ret < 0) अणु
		qmi_txn_cancel(&txn);
		ath10k_err(ar, "failed to send capability request: %d\n", ret);
		जाओ out;
	पूर्ण

	ret = qmi_txn_रुको(&txn, ATH10K_QMI_TIMEOUT * HZ);
	अगर (ret < 0)
		जाओ out;

	अगर (resp->resp.result != QMI_RESULT_SUCCESS_V01) अणु
		ath10k_err(ar, "capability req rejected: %d\n", resp->resp.error);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (resp->chip_info_valid) अणु
		qmi->chip_info.chip_id = resp->chip_info.chip_id;
		qmi->chip_info.chip_family = resp->chip_info.chip_family;
	पूर्ण अन्यथा अणु
		qmi->chip_info.chip_id = 0xFF;
	पूर्ण

	अगर (resp->board_info_valid)
		qmi->board_info.board_id = resp->board_info.board_id;
	अन्यथा
		qmi->board_info.board_id = 0xFF;

	अगर (resp->soc_info_valid)
		qmi->soc_info.soc_id = resp->soc_info.soc_id;

	अगर (resp->fw_version_info_valid) अणु
		qmi->fw_version = resp->fw_version_info.fw_version;
		strlcpy(qmi->fw_build_बारtamp, resp->fw_version_info.fw_build_बारtamp,
			माप(qmi->fw_build_बारtamp));
	पूर्ण

	अगर (resp->fw_build_id_valid)
		strlcpy(qmi->fw_build_id, resp->fw_build_id,
			MAX_BUILD_ID_LEN + 1);

	अगर (!test_bit(ATH10K_SNOC_FLAG_REGISTERED, &ar_snoc->flags)) अणु
		ath10k_info(ar, "qmi chip_id 0x%x chip_family 0x%x board_id 0x%x soc_id 0x%x",
			    qmi->chip_info.chip_id, qmi->chip_info.chip_family,
			    qmi->board_info.board_id, qmi->soc_info.soc_id);
		ath10k_info(ar, "qmi fw_version 0x%x fw_build_timestamp %s fw_build_id %s",
			    qmi->fw_version, qmi->fw_build_बारtamp, qmi->fw_build_id);
	पूर्ण

	kमुक्त(resp);
	वापस 0;

out:
	kमुक्त(resp);
	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_qmi_host_cap_send_sync(काष्ठा ath10k_qmi *qmi)
अणु
	काष्ठा wlfw_host_cap_resp_msg_v01 resp = अणुपूर्ण;
	काष्ठा wlfw_host_cap_req_msg_v01 req = अणुपूर्ण;
	काष्ठा qmi_elem_info *req_ei;
	काष्ठा ath10k *ar = qmi->ar;
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	काष्ठा qmi_txn txn;
	पूर्णांक ret;

	req.daemon_support_valid = 1;
	req.daemon_support = 0;

	ret = qmi_txn_init(&qmi->qmi_hdl, &txn, wlfw_host_cap_resp_msg_v01_ei,
			   &resp);
	अगर (ret < 0)
		जाओ out;

	अगर (test_bit(ATH10K_SNOC_FLAG_8BIT_HOST_CAP_QUIRK, &ar_snoc->flags))
		req_ei = wlfw_host_cap_8bit_req_msg_v01_ei;
	अन्यथा
		req_ei = wlfw_host_cap_req_msg_v01_ei;

	ret = qmi_send_request(&qmi->qmi_hdl, शून्य, &txn,
			       QMI_WLFW_HOST_CAP_REQ_V01,
			       WLFW_HOST_CAP_REQ_MSG_V01_MAX_MSG_LEN,
			       req_ei, &req);
	अगर (ret < 0) अणु
		qmi_txn_cancel(&txn);
		ath10k_err(ar, "failed to send host capability request: %d\n", ret);
		जाओ out;
	पूर्ण

	ret = qmi_txn_रुको(&txn, ATH10K_QMI_TIMEOUT * HZ);
	अगर (ret < 0)
		जाओ out;

	/* older FW didn't support this request, which is not fatal */
	अगर (resp.resp.result != QMI_RESULT_SUCCESS_V01 &&
	    resp.resp.error != QMI_ERR_NOT_SUPPORTED_V01) अणु
		ath10k_err(ar, "host capability request rejected: %d\n", resp.resp.error);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_QMI, "qmi host capability request completed\n");
	वापस 0;

out:
	वापस ret;
पूर्ण

पूर्णांक ath10k_qmi_set_fw_log_mode(काष्ठा ath10k *ar, u8 fw_log_mode)
अणु
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	काष्ठा wlfw_ini_resp_msg_v01 resp = अणुपूर्ण;
	काष्ठा ath10k_qmi *qmi = ar_snoc->qmi;
	काष्ठा wlfw_ini_req_msg_v01 req = अणुपूर्ण;
	काष्ठा qmi_txn txn;
	पूर्णांक ret;

	req.enablefwlog_valid = 1;
	req.enablefwlog = fw_log_mode;

	ret = qmi_txn_init(&qmi->qmi_hdl, &txn, wlfw_ini_resp_msg_v01_ei,
			   &resp);
	अगर (ret < 0)
		जाओ out;

	ret = qmi_send_request(&qmi->qmi_hdl, शून्य, &txn,
			       QMI_WLFW_INI_REQ_V01,
			       WLFW_INI_REQ_MSG_V01_MAX_MSG_LEN,
			       wlfw_ini_req_msg_v01_ei, &req);
	अगर (ret < 0) अणु
		qmi_txn_cancel(&txn);
		ath10k_err(ar, "failed to send fw log request: %d\n", ret);
		जाओ out;
	पूर्ण

	ret = qmi_txn_रुको(&txn, ATH10K_QMI_TIMEOUT * HZ);
	अगर (ret < 0)
		जाओ out;

	अगर (resp.resp.result != QMI_RESULT_SUCCESS_V01) अणु
		ath10k_err(ar, "fw log request rejected: %d\n",
			   resp.resp.error);
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	ath10k_dbg(ar, ATH10K_DBG_QMI, "qmi fw log request completed, mode: %d\n",
		   fw_log_mode);
	वापस 0;

out:
	वापस ret;
पूर्ण

अटल पूर्णांक
ath10k_qmi_ind_रेजिस्टर_send_sync_msg(काष्ठा ath10k_qmi *qmi)
अणु
	काष्ठा wlfw_ind_रेजिस्टर_resp_msg_v01 resp = अणुपूर्ण;
	काष्ठा wlfw_ind_रेजिस्टर_req_msg_v01 req = अणुपूर्ण;
	काष्ठा ath10k *ar = qmi->ar;
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	काष्ठा qmi_txn txn;
	पूर्णांक ret;

	req.client_id_valid = 1;
	req.client_id = ATH10K_QMI_CLIENT_ID;
	req.fw_पढ़ोy_enable_valid = 1;
	req.fw_पढ़ोy_enable = 1;
	req.msa_पढ़ोy_enable_valid = 1;
	req.msa_पढ़ोy_enable = 1;

	अगर (ar_snoc->xo_cal_supported) अणु
		req.xo_cal_enable_valid = 1;
		req.xo_cal_enable = 1;
	पूर्ण

	ret = qmi_txn_init(&qmi->qmi_hdl, &txn,
			   wlfw_ind_रेजिस्टर_resp_msg_v01_ei, &resp);
	अगर (ret < 0)
		जाओ out;

	ret = qmi_send_request(&qmi->qmi_hdl, शून्य, &txn,
			       QMI_WLFW_IND_REGISTER_REQ_V01,
			       WLFW_IND_REGISTER_REQ_MSG_V01_MAX_MSG_LEN,
			       wlfw_ind_रेजिस्टर_req_msg_v01_ei, &req);
	अगर (ret < 0) अणु
		qmi_txn_cancel(&txn);
		ath10k_err(ar, "failed to send indication registered request: %d\n", ret);
		जाओ out;
	पूर्ण

	ret = qmi_txn_रुको(&txn, ATH10K_QMI_TIMEOUT * HZ);
	अगर (ret < 0)
		जाओ out;

	अगर (resp.resp.result != QMI_RESULT_SUCCESS_V01) अणु
		ath10k_err(ar, "indication request rejected: %d\n", resp.resp.error);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (resp.fw_status_valid) अणु
		अगर (resp.fw_status & QMI_WLFW_FW_READY_V01)
			qmi->fw_पढ़ोy = true;
	पूर्ण
	ath10k_dbg(ar, ATH10K_DBG_QMI, "qmi indication register request completed\n");
	वापस 0;

out:
	वापस ret;
पूर्ण

अटल व्योम ath10k_qmi_event_server_arrive(काष्ठा ath10k_qmi *qmi)
अणु
	काष्ठा ath10k *ar = qmi->ar;
	पूर्णांक ret;

	ret = ath10k_qmi_ind_रेजिस्टर_send_sync_msg(qmi);
	अगर (ret)
		वापस;

	अगर (qmi->fw_पढ़ोy) अणु
		ath10k_snoc_fw_indication(ar, ATH10K_QMI_EVENT_FW_READY_IND);
		वापस;
	पूर्ण

	ret = ath10k_qmi_host_cap_send_sync(qmi);
	अगर (ret)
		वापस;

	ret = ath10k_qmi_msa_mem_info_send_sync_msg(qmi);
	अगर (ret)
		वापस;

	/*
	 * HACK: sleep क्रम a जबतक inbetween receiving the msa info response
	 * and the XPU update to prevent SDM845 from crashing due to a security
	 * violation, when running MPSS.AT.4.0.c2-01184-SDM845_GEN_PACK-1.
	 */
	msleep(20);

	ret = ath10k_qmi_setup_msa_permissions(qmi);
	अगर (ret)
		वापस;

	ret = ath10k_qmi_msa_पढ़ोy_send_sync_msg(qmi);
	अगर (ret)
		जाओ err_setup_msa;

	ret = ath10k_qmi_cap_send_sync_msg(qmi);
	अगर (ret)
		जाओ err_setup_msa;

	वापस;

err_setup_msa:
	ath10k_qmi_हटाओ_msa_permission(qmi);
पूर्ण

अटल पूर्णांक ath10k_qmi_fetch_board_file(काष्ठा ath10k_qmi *qmi)
अणु
	काष्ठा ath10k *ar = qmi->ar;
	पूर्णांक ret;

	ar->hअगर.bus = ATH10K_BUS_SNOC;
	ar->id.qmi_ids_valid = true;
	ar->id.qmi_board_id = qmi->board_info.board_id;
	ar->id.qmi_chip_id = qmi->chip_info.chip_id;
	ar->hw_params.fw.dir = WCN3990_HW_1_0_FW_सूची;

	ret = ath10k_core_check_dt(ar);
	अगर (ret)
		ath10k_dbg(ar, ATH10K_DBG_QMI, "DT bdf variant name not set.\n");

	वापस ath10k_core_fetch_board_file(qmi->ar, ATH10K_BD_IE_BOARD);
पूर्ण

अटल पूर्णांक
ath10k_qmi_driver_event_post(काष्ठा ath10k_qmi *qmi,
			     क्रमागत ath10k_qmi_driver_event_type type,
			     व्योम *data)
अणु
	काष्ठा ath10k_qmi_driver_event *event;

	event = kzalloc(माप(*event), GFP_ATOMIC);
	अगर (!event)
		वापस -ENOMEM;

	event->type = type;
	event->data = data;

	spin_lock(&qmi->event_lock);
	list_add_tail(&event->list, &qmi->event_list);
	spin_unlock(&qmi->event_lock);

	queue_work(qmi->event_wq, &qmi->event_work);

	वापस 0;
पूर्ण

अटल व्योम ath10k_qmi_event_server_निकास(काष्ठा ath10k_qmi *qmi)
अणु
	काष्ठा ath10k *ar = qmi->ar;
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);

	ath10k_qmi_हटाओ_msa_permission(qmi);
	ath10k_core_मुक्त_board_files(ar);
	अगर (!test_bit(ATH10K_SNOC_FLAG_UNREGISTERING, &ar_snoc->flags))
		ath10k_snoc_fw_crashed_dump(ar);

	ath10k_snoc_fw_indication(ar, ATH10K_QMI_EVENT_FW_DOWN_IND);
	ath10k_dbg(ar, ATH10K_DBG_QMI, "wifi fw qmi service disconnected\n");
पूर्ण

अटल व्योम ath10k_qmi_event_msa_पढ़ोy(काष्ठा ath10k_qmi *qmi)
अणु
	पूर्णांक ret;

	ret = ath10k_qmi_fetch_board_file(qmi);
	अगर (ret)
		जाओ out;

	ret = ath10k_qmi_bdf_dnld_send_sync(qmi);
	अगर (ret)
		जाओ out;

	ret = ath10k_qmi_send_cal_report_req(qmi);

out:
	वापस;
पूर्ण

अटल पूर्णांक ath10k_qmi_event_fw_पढ़ोy_ind(काष्ठा ath10k_qmi *qmi)
अणु
	काष्ठा ath10k *ar = qmi->ar;

	ath10k_dbg(ar, ATH10K_DBG_QMI, "wifi fw ready event received\n");
	ath10k_snoc_fw_indication(ar, ATH10K_QMI_EVENT_FW_READY_IND);

	वापस 0;
पूर्ण

अटल व्योम ath10k_qmi_fw_पढ़ोy_ind(काष्ठा qmi_handle *qmi_hdl,
				    काष्ठा sockaddr_qrtr *sq,
				    काष्ठा qmi_txn *txn, स्थिर व्योम *data)
अणु
	काष्ठा ath10k_qmi *qmi = container_of(qmi_hdl, काष्ठा ath10k_qmi, qmi_hdl);

	ath10k_qmi_driver_event_post(qmi, ATH10K_QMI_EVENT_FW_READY_IND, शून्य);
पूर्ण

अटल व्योम ath10k_qmi_msa_पढ़ोy_ind(काष्ठा qmi_handle *qmi_hdl,
				     काष्ठा sockaddr_qrtr *sq,
				     काष्ठा qmi_txn *txn, स्थिर व्योम *data)
अणु
	काष्ठा ath10k_qmi *qmi = container_of(qmi_hdl, काष्ठा ath10k_qmi, qmi_hdl);

	ath10k_qmi_driver_event_post(qmi, ATH10K_QMI_EVENT_MSA_READY_IND, शून्य);
पूर्ण

अटल स्थिर काष्ठा qmi_msg_handler qmi_msg_handler[] = अणु
	अणु
		.type = QMI_INDICATION,
		.msg_id = QMI_WLFW_FW_READY_IND_V01,
		.ei = wlfw_fw_पढ़ोy_ind_msg_v01_ei,
		.decoded_size = माप(काष्ठा wlfw_fw_पढ़ोy_ind_msg_v01),
		.fn = ath10k_qmi_fw_पढ़ोy_ind,
	पूर्ण,
	अणु
		.type = QMI_INDICATION,
		.msg_id = QMI_WLFW_MSA_READY_IND_V01,
		.ei = wlfw_msa_पढ़ोy_ind_msg_v01_ei,
		.decoded_size = माप(काष्ठा wlfw_msa_पढ़ोy_ind_msg_v01),
		.fn = ath10k_qmi_msa_पढ़ोy_ind,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक ath10k_qmi_new_server(काष्ठा qmi_handle *qmi_hdl,
				 काष्ठा qmi_service *service)
अणु
	काष्ठा ath10k_qmi *qmi = container_of(qmi_hdl, काष्ठा ath10k_qmi, qmi_hdl);
	काष्ठा sockaddr_qrtr *sq = &qmi->sq;
	काष्ठा ath10k *ar = qmi->ar;
	पूर्णांक ret;

	sq->sq_family = AF_QIPCRTR;
	sq->sq_node = service->node;
	sq->sq_port = service->port;

	ath10k_dbg(ar, ATH10K_DBG_QMI, "wifi fw qmi service found\n");

	ret = kernel_connect(qmi_hdl->sock, (काष्ठा sockaddr *)&qmi->sq,
			     माप(qmi->sq), 0);
	अगर (ret) अणु
		ath10k_err(ar, "failed to connect to a remote QMI service port\n");
		वापस ret;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_QMI, "qmi wifi fw qmi service connected\n");
	ath10k_qmi_driver_event_post(qmi, ATH10K_QMI_EVENT_SERVER_ARRIVE, शून्य);

	वापस ret;
पूर्ण

अटल व्योम ath10k_qmi_del_server(काष्ठा qmi_handle *qmi_hdl,
				  काष्ठा qmi_service *service)
अणु
	काष्ठा ath10k_qmi *qmi =
		container_of(qmi_hdl, काष्ठा ath10k_qmi, qmi_hdl);

	qmi->fw_पढ़ोy = false;

	/*
	 * The del_server event is to be processed only अगर coming from
	 * the qmi server. The qmi infraकाष्ठाure sends del_server, when
	 * any client releases the qmi handle. In this हाल करो not process
	 * this del_server event.
	 */
	अगर (qmi->state == ATH10K_QMI_STATE_INIT_DONE)
		ath10k_qmi_driver_event_post(qmi, ATH10K_QMI_EVENT_SERVER_EXIT,
					     शून्य);
पूर्ण

अटल स्थिर काष्ठा qmi_ops ath10k_qmi_ops = अणु
	.new_server = ath10k_qmi_new_server,
	.del_server = ath10k_qmi_del_server,
पूर्ण;

अटल व्योम ath10k_qmi_driver_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath10k_qmi *qmi = container_of(work, काष्ठा ath10k_qmi,
					      event_work);
	काष्ठा ath10k_qmi_driver_event *event;
	काष्ठा ath10k *ar = qmi->ar;

	spin_lock(&qmi->event_lock);
	जबतक (!list_empty(&qmi->event_list)) अणु
		event = list_first_entry(&qmi->event_list,
					 काष्ठा ath10k_qmi_driver_event, list);
		list_del(&event->list);
		spin_unlock(&qmi->event_lock);

		चयन (event->type) अणु
		हाल ATH10K_QMI_EVENT_SERVER_ARRIVE:
			ath10k_qmi_event_server_arrive(qmi);
			अवरोध;
		हाल ATH10K_QMI_EVENT_SERVER_EXIT:
			ath10k_qmi_event_server_निकास(qmi);
			अवरोध;
		हाल ATH10K_QMI_EVENT_FW_READY_IND:
			ath10k_qmi_event_fw_पढ़ोy_ind(qmi);
			अवरोध;
		हाल ATH10K_QMI_EVENT_MSA_READY_IND:
			ath10k_qmi_event_msa_पढ़ोy(qmi);
			अवरोध;
		शेष:
			ath10k_warn(ar, "invalid event type: %d", event->type);
			अवरोध;
		पूर्ण
		kमुक्त(event);
		spin_lock(&qmi->event_lock);
	पूर्ण
	spin_unlock(&qmi->event_lock);
पूर्ण

पूर्णांक ath10k_qmi_init(काष्ठा ath10k *ar, u32 msa_size)
अणु
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	काष्ठा device *dev = ar->dev;
	काष्ठा ath10k_qmi *qmi;
	पूर्णांक ret;

	qmi = kzalloc(माप(*qmi), GFP_KERNEL);
	अगर (!qmi)
		वापस -ENOMEM;

	qmi->ar = ar;
	ar_snoc->qmi = qmi;

	अगर (of_property_पढ़ो_bool(dev->of_node, "qcom,msa-fixed-perm"))
		qmi->msa_fixed_perm = true;

	ret = qmi_handle_init(&qmi->qmi_hdl,
			      WLFW_BDF_DOWNLOAD_REQ_MSG_V01_MAX_MSG_LEN,
			      &ath10k_qmi_ops, qmi_msg_handler);
	अगर (ret)
		जाओ err;

	qmi->event_wq = alloc_workqueue("ath10k_qmi_driver_event",
					WQ_UNBOUND, 1);
	अगर (!qmi->event_wq) अणु
		ath10k_err(ar, "failed to allocate workqueue\n");
		ret = -EFAULT;
		जाओ err_release_qmi_handle;
	पूर्ण

	INIT_LIST_HEAD(&qmi->event_list);
	spin_lock_init(&qmi->event_lock);
	INIT_WORK(&qmi->event_work, ath10k_qmi_driver_event_work);

	ret = qmi_add_lookup(&qmi->qmi_hdl, WLFW_SERVICE_ID_V01,
			     WLFW_SERVICE_VERS_V01, 0);
	अगर (ret)
		जाओ err_qmi_lookup;

	qmi->state = ATH10K_QMI_STATE_INIT_DONE;
	वापस 0;

err_qmi_lookup:
	destroy_workqueue(qmi->event_wq);

err_release_qmi_handle:
	qmi_handle_release(&qmi->qmi_hdl);

err:
	kमुक्त(qmi);
	वापस ret;
पूर्ण

पूर्णांक ath10k_qmi_deinit(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	काष्ठा ath10k_qmi *qmi = ar_snoc->qmi;

	qmi->state = ATH10K_QMI_STATE_DEINIT;
	qmi_handle_release(&qmi->qmi_hdl);
	cancel_work_sync(&qmi->event_work);
	destroy_workqueue(qmi->event_wq);
	kमुक्त(qmi);
	ar_snoc->qmi = शून्य;

	वापस 0;
पूर्ण
