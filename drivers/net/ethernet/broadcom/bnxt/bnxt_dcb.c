<शैली गुरु>
/* Broadcom NetXtreme-C/E network driver.
 *
 * Copyright (c) 2014-2016 Broadcom Corporation
 * Copyright (c) 2016-2017 Broadcom Limited
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#समावेश <linux/netdevice.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/etherdevice.h>
#समावेश <rdma/ib_verbs.h>
#समावेश "bnxt_hsi.h"
#समावेश "bnxt.h"
#समावेश "bnxt_dcb.h"

#अगर_घोषित CONFIG_BNXT_DCB
अटल पूर्णांक bnxt_queue_to_tc(काष्ठा bnxt *bp, u8 queue_id)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < bp->max_tc; i++) अणु
		अगर (bp->q_info[i].queue_id == queue_id) अणु
			क्रम (j = 0; j < bp->max_tc; j++) अणु
				अगर (bp->tc_to_qidx[j] == i)
					वापस j;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक bnxt_hwrm_queue_pri2cos_cfg(काष्ठा bnxt *bp, काष्ठा ieee_ets *ets)
अणु
	काष्ठा hwrm_queue_pri2cos_cfg_input req = अणु0पूर्ण;
	u8 *pri2cos;
	पूर्णांक i;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_QUEUE_PRI2COS_CFG, -1, -1);
	req.flags = cpu_to_le32(QUEUE_PRI2COS_CFG_REQ_FLAGS_PATH_BIसूची |
				QUEUE_PRI2COS_CFG_REQ_FLAGS_IVLAN);

	pri2cos = &req.pri0_cos_queue_id;
	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) अणु
		u8 qidx;

		req.enables |= cpu_to_le32(
			QUEUE_PRI2COS_CFG_REQ_ENABLES_PRI0_COS_QUEUE_ID << i);

		qidx = bp->tc_to_qidx[ets->prio_tc[i]];
		pri2cos[i] = bp->q_info[qidx].queue_id;
	पूर्ण
	वापस hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
पूर्ण

अटल पूर्णांक bnxt_hwrm_queue_pri2cos_qcfg(काष्ठा bnxt *bp, काष्ठा ieee_ets *ets)
अणु
	काष्ठा hwrm_queue_pri2cos_qcfg_output *resp = bp->hwrm_cmd_resp_addr;
	काष्ठा hwrm_queue_pri2cos_qcfg_input req = अणु0पूर्ण;
	पूर्णांक rc = 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_QUEUE_PRI2COS_QCFG, -1, -1);
	req.flags = cpu_to_le32(QUEUE_PRI2COS_QCFG_REQ_FLAGS_IVLAN);

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (!rc) अणु
		u8 *pri2cos = &resp->pri0_cos_queue_id;
		पूर्णांक i;

		क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) अणु
			u8 queue_id = pri2cos[i];
			पूर्णांक tc;

			tc = bnxt_queue_to_tc(bp, queue_id);
			अगर (tc >= 0)
				ets->prio_tc[i] = tc;
		पूर्ण
	पूर्ण
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_hwrm_queue_cos2bw_cfg(काष्ठा bnxt *bp, काष्ठा ieee_ets *ets,
				      u8 max_tc)
अणु
	काष्ठा hwrm_queue_cos2bw_cfg_input req = अणु0पूर्ण;
	काष्ठा bnxt_cos2bw_cfg cos2bw;
	व्योम *data;
	पूर्णांक i;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_QUEUE_COS2BW_CFG, -1, -1);
	क्रम (i = 0; i < max_tc; i++) अणु
		u8 qidx = bp->tc_to_qidx[i];

		req.enables |= cpu_to_le32(
			QUEUE_COS2BW_CFG_REQ_ENABLES_COS_QUEUE_ID0_VALID <<
			qidx);

		स_रखो(&cos2bw, 0, माप(cos2bw));
		cos2bw.queue_id = bp->q_info[qidx].queue_id;
		अगर (ets->tc_tsa[i] == IEEE_8021QAZ_TSA_STRICT) अणु
			cos2bw.tsa =
				QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_TSA_ASSIGN_SP;
			cos2bw.pri_lvl = i;
		पूर्ण अन्यथा अणु
			cos2bw.tsa =
				QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_TSA_ASSIGN_ETS;
			cos2bw.bw_weight = ets->tc_tx_bw[i];
			/* older firmware requires min_bw to be set to the
			 * same weight value in percent.
			 */
			cos2bw.min_bw =
				cpu_to_le32((ets->tc_tx_bw[i] * 100) |
					    BW_VALUE_UNIT_PERCENT1_100);
		पूर्ण
		data = &req.unused_0 + qidx * (माप(cos2bw) - 4);
		स_नकल(data, &cos2bw.queue_id, माप(cos2bw) - 4);
		अगर (qidx == 0) अणु
			req.queue_id0 = cos2bw.queue_id;
			req.unused_0 = 0;
		पूर्ण
	पूर्ण
	वापस hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
पूर्ण

अटल पूर्णांक bnxt_hwrm_queue_cos2bw_qcfg(काष्ठा bnxt *bp, काष्ठा ieee_ets *ets)
अणु
	काष्ठा hwrm_queue_cos2bw_qcfg_output *resp = bp->hwrm_cmd_resp_addr;
	काष्ठा hwrm_queue_cos2bw_qcfg_input req = अणु0पूर्ण;
	काष्ठा bnxt_cos2bw_cfg cos2bw;
	व्योम *data;
	पूर्णांक rc, i;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_QUEUE_COS2BW_QCFG, -1, -1);

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (rc) अणु
		mutex_unlock(&bp->hwrm_cmd_lock);
		वापस rc;
	पूर्ण

	data = &resp->queue_id0 + दुरत्व(काष्ठा bnxt_cos2bw_cfg, queue_id);
	क्रम (i = 0; i < bp->max_tc; i++, data += माप(cos2bw) - 4) अणु
		पूर्णांक tc;

		स_नकल(&cos2bw.queue_id, data, माप(cos2bw) - 4);
		अगर (i == 0)
			cos2bw.queue_id = resp->queue_id0;

		tc = bnxt_queue_to_tc(bp, cos2bw.queue_id);
		अगर (tc < 0)
			जारी;

		अगर (cos2bw.tsa ==
		    QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_TSA_ASSIGN_SP) अणु
			ets->tc_tsa[tc] = IEEE_8021QAZ_TSA_STRICT;
		पूर्ण अन्यथा अणु
			ets->tc_tsa[tc] = IEEE_8021QAZ_TSA_ETS;
			ets->tc_tx_bw[tc] = cos2bw.bw_weight;
		पूर्ण
	पूर्ण
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_queue_remap(काष्ठा bnxt *bp, अचिन्हित पूर्णांक lltc_mask)
अणु
	अचिन्हित दीर्घ qmap = 0;
	पूर्णांक max = bp->max_tc;
	पूर्णांक i, j, rc;

	/* Assign lossless TCs first */
	क्रम (i = 0, j = 0; i < max; ) अणु
		अगर (lltc_mask & (1 << i)) अणु
			अगर (BNXT_LLQ(bp->q_info[j].queue_profile)) अणु
				bp->tc_to_qidx[i] = j;
				__set_bit(j, &qmap);
				i++;
			पूर्ण
			j++;
			जारी;
		पूर्ण
		i++;
	पूर्ण

	क्रम (i = 0, j = 0; i < max; i++) अणु
		अगर (lltc_mask & (1 << i))
			जारी;
		j = find_next_zero_bit(&qmap, max, j);
		bp->tc_to_qidx[i] = j;
		__set_bit(j, &qmap);
		j++;
	पूर्ण

	अगर (netअगर_running(bp->dev)) अणु
		bnxt_बंद_nic(bp, false, false);
		rc = bnxt_खोलो_nic(bp, false, false);
		अगर (rc) अणु
			netdev_warn(bp->dev, "failed to open NIC, rc = %d\n", rc);
			वापस rc;
		पूर्ण
	पूर्ण
	अगर (bp->ieee_ets) अणु
		पूर्णांक tc = netdev_get_num_tc(bp->dev);

		अगर (!tc)
			tc = 1;
		rc = bnxt_hwrm_queue_cos2bw_cfg(bp, bp->ieee_ets, tc);
		अगर (rc) अणु
			netdev_warn(bp->dev, "failed to config BW, rc = %d\n", rc);
			वापस rc;
		पूर्ण
		rc = bnxt_hwrm_queue_pri2cos_cfg(bp, bp->ieee_ets);
		अगर (rc) अणु
			netdev_warn(bp->dev, "failed to config prio, rc = %d\n", rc);
			वापस rc;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_hwrm_queue_pfc_cfg(काष्ठा bnxt *bp, काष्ठा ieee_pfc *pfc)
अणु
	काष्ठा hwrm_queue_pfcenable_cfg_input req = अणु0पूर्ण;
	काष्ठा ieee_ets *my_ets = bp->ieee_ets;
	अचिन्हित पूर्णांक tc_mask = 0, pri_mask = 0;
	u8 i, pri, lltc_count = 0;
	bool need_q_remap = false;

	अगर (!my_ets)
		वापस -EINVAL;

	क्रम (i = 0; i < bp->max_tc; i++) अणु
		क्रम (pri = 0; pri < IEEE_8021QAZ_MAX_TCS; pri++) अणु
			अगर ((pfc->pfc_en & (1 << pri)) &&
			    (my_ets->prio_tc[pri] == i)) अणु
				pri_mask |= 1 << pri;
				tc_mask |= 1 << i;
			पूर्ण
		पूर्ण
		अगर (tc_mask & (1 << i))
			lltc_count++;
	पूर्ण
	अगर (lltc_count > bp->max_lltc)
		वापस -EINVAL;

	क्रम (i = 0; i < bp->max_tc; i++) अणु
		अगर (tc_mask & (1 << i)) अणु
			u8 qidx = bp->tc_to_qidx[i];

			अगर (!BNXT_LLQ(bp->q_info[qidx].queue_profile)) अणु
				need_q_remap = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (need_q_remap)
		bnxt_queue_remap(bp, tc_mask);

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_QUEUE_PFCENABLE_CFG, -1, -1);
	req.flags = cpu_to_le32(pri_mask);
	वापस hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
पूर्ण

अटल पूर्णांक bnxt_hwrm_queue_pfc_qcfg(काष्ठा bnxt *bp, काष्ठा ieee_pfc *pfc)
अणु
	काष्ठा hwrm_queue_pfcenable_qcfg_output *resp = bp->hwrm_cmd_resp_addr;
	काष्ठा hwrm_queue_pfcenable_qcfg_input req = अणु0पूर्ण;
	u8 pri_mask;
	पूर्णांक rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_QUEUE_PFCENABLE_QCFG, -1, -1);

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (rc) अणु
		mutex_unlock(&bp->hwrm_cmd_lock);
		वापस rc;
	पूर्ण

	pri_mask = le32_to_cpu(resp->flags);
	pfc->pfc_en = pri_mask;
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_hwrm_set_dcbx_app(काष्ठा bnxt *bp, काष्ठा dcb_app *app,
				  bool add)
अणु
	काष्ठा hwrm_fw_set_काष्ठाured_data_input set = अणु0पूर्ण;
	काष्ठा hwrm_fw_get_काष्ठाured_data_input get = अणु0पूर्ण;
	काष्ठा hwrm_काष्ठा_data_dcbx_app *fw_app;
	काष्ठा hwrm_काष्ठा_hdr *data;
	dma_addr_t mapping;
	माप_प्रकार data_len;
	पूर्णांक rc, n, i;

	अगर (bp->hwrm_spec_code < 0x10601)
		वापस 0;

	n = IEEE_8021QAZ_MAX_TCS;
	data_len = माप(*data) + माप(*fw_app) * n;
	data = dma_alloc_coherent(&bp->pdev->dev, data_len, &mapping,
				  GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	bnxt_hwrm_cmd_hdr_init(bp, &get, HWRM_FW_GET_STRUCTURED_DATA, -1, -1);
	get.dest_data_addr = cpu_to_le64(mapping);
	get.काष्ठाure_id = cpu_to_le16(STRUCT_HDR_STRUCT_ID_DCBX_APP);
	get.subtype = cpu_to_le16(HWRM_STRUCT_DATA_SUBTYPE_HOST_OPERATIONAL);
	get.count = 0;
	rc = hwrm_send_message(bp, &get, माप(get), HWRM_CMD_TIMEOUT);
	अगर (rc)
		जाओ set_app_निकास;

	fw_app = (काष्ठा hwrm_काष्ठा_data_dcbx_app *)(data + 1);

	अगर (data->काष्ठा_id != cpu_to_le16(STRUCT_HDR_STRUCT_ID_DCBX_APP)) अणु
		rc = -ENODEV;
		जाओ set_app_निकास;
	पूर्ण

	n = data->count;
	क्रम (i = 0; i < n; i++, fw_app++) अणु
		अगर (fw_app->protocol_id == cpu_to_be16(app->protocol) &&
		    fw_app->protocol_selector == app->selector &&
		    fw_app->priority == app->priority) अणु
			अगर (add)
				जाओ set_app_निकास;
			अन्यथा
				अवरोध;
		पूर्ण
	पूर्ण
	अगर (add) अणु
		/* append */
		n++;
		fw_app->protocol_id = cpu_to_be16(app->protocol);
		fw_app->protocol_selector = app->selector;
		fw_app->priority = app->priority;
		fw_app->valid = 1;
	पूर्ण अन्यथा अणु
		माप_प्रकार len = 0;

		/* not found, nothing to delete */
		अगर (n == i)
			जाओ set_app_निकास;

		len = (n - 1 - i) * माप(*fw_app);
		अगर (len)
			स_हटाओ(fw_app, fw_app + 1, len);
		n--;
		स_रखो(fw_app + n, 0, माप(*fw_app));
	पूर्ण
	data->count = n;
	data->len = cpu_to_le16(माप(*fw_app) * n);
	data->subtype = cpu_to_le16(HWRM_STRUCT_DATA_SUBTYPE_HOST_OPERATIONAL);

	bnxt_hwrm_cmd_hdr_init(bp, &set, HWRM_FW_SET_STRUCTURED_DATA, -1, -1);
	set.src_data_addr = cpu_to_le64(mapping);
	set.data_len = cpu_to_le16(माप(*data) + माप(*fw_app) * n);
	set.hdr_cnt = 1;
	rc = hwrm_send_message(bp, &set, माप(set), HWRM_CMD_TIMEOUT);

set_app_निकास:
	dma_मुक्त_coherent(&bp->pdev->dev, data_len, data, mapping);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_hwrm_queue_dscp_qcaps(काष्ठा bnxt *bp)
अणु
	काष्ठा hwrm_queue_dscp_qcaps_output *resp = bp->hwrm_cmd_resp_addr;
	काष्ठा hwrm_queue_dscp_qcaps_input req = अणु0पूर्ण;
	पूर्णांक rc;

	bp->max_dscp_value = 0;
	अगर (bp->hwrm_spec_code < 0x10800 || BNXT_VF(bp))
		वापस 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_QUEUE_DSCP_QCAPS, -1, -1);
	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message_silent(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (!rc) अणु
		bp->max_dscp_value = (1 << resp->num_dscp_bits) - 1;
		अगर (bp->max_dscp_value < 0x3f)
			bp->max_dscp_value = 0;
	पूर्ण

	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_hwrm_queue_dscp2pri_cfg(काष्ठा bnxt *bp, काष्ठा dcb_app *app,
					bool add)
अणु
	काष्ठा hwrm_queue_dscp2pri_cfg_input req = अणु0पूर्ण;
	काष्ठा bnxt_dscp2pri_entry *dscp2pri;
	dma_addr_t mapping;
	पूर्णांक rc;

	अगर (bp->hwrm_spec_code < 0x10800)
		वापस 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_QUEUE_DSCP2PRI_CFG, -1, -1);
	dscp2pri = dma_alloc_coherent(&bp->pdev->dev, माप(*dscp2pri),
				      &mapping, GFP_KERNEL);
	अगर (!dscp2pri)
		वापस -ENOMEM;

	req.src_data_addr = cpu_to_le64(mapping);
	dscp2pri->dscp = app->protocol;
	अगर (add)
		dscp2pri->mask = 0x3f;
	अन्यथा
		dscp2pri->mask = 0;
	dscp2pri->pri = app->priority;
	req.entry_cnt = cpu_to_le16(1);
	rc = hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	dma_मुक्त_coherent(&bp->pdev->dev, माप(*dscp2pri), dscp2pri,
			  mapping);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_ets_validate(काष्ठा bnxt *bp, काष्ठा ieee_ets *ets, u8 *tc)
अणु
	पूर्णांक total_ets_bw = 0;
	u8 max_tc = 0;
	पूर्णांक i;

	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) अणु
		अगर (ets->prio_tc[i] > bp->max_tc) अणु
			netdev_err(bp->dev, "priority to TC mapping exceeds TC count %d\n",
				   ets->prio_tc[i]);
			वापस -EINVAL;
		पूर्ण
		अगर (ets->prio_tc[i] > max_tc)
			max_tc = ets->prio_tc[i];

		अगर ((ets->tc_tx_bw[i] || ets->tc_tsa[i]) && i > bp->max_tc)
			वापस -EINVAL;

		चयन (ets->tc_tsa[i]) अणु
		हाल IEEE_8021QAZ_TSA_STRICT:
			अवरोध;
		हाल IEEE_8021QAZ_TSA_ETS:
			total_ets_bw += ets->tc_tx_bw[i];
			अवरोध;
		शेष:
			वापस -ENOTSUPP;
		पूर्ण
	पूर्ण
	अगर (total_ets_bw > 100)
		वापस -EINVAL;

	अगर (max_tc >= bp->max_tc)
		*tc = bp->max_tc;
	अन्यथा
		*tc = max_tc + 1;
	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_dcbnl_ieee_getets(काष्ठा net_device *dev, काष्ठा ieee_ets *ets)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	काष्ठा ieee_ets *my_ets = bp->ieee_ets;
	पूर्णांक rc;

	ets->ets_cap = bp->max_tc;

	अगर (!my_ets) अणु
		अगर (bp->dcbx_cap & DCB_CAP_DCBX_HOST)
			वापस 0;

		my_ets = kzalloc(माप(*my_ets), GFP_KERNEL);
		अगर (!my_ets)
			वापस -ENOMEM;
		rc = bnxt_hwrm_queue_cos2bw_qcfg(bp, my_ets);
		अगर (rc)
			जाओ error;
		rc = bnxt_hwrm_queue_pri2cos_qcfg(bp, my_ets);
		अगर (rc)
			जाओ error;

		/* cache result */
		bp->ieee_ets = my_ets;
	पूर्ण

	ets->cbs = my_ets->cbs;
	स_नकल(ets->tc_tx_bw, my_ets->tc_tx_bw, माप(ets->tc_tx_bw));
	स_नकल(ets->tc_rx_bw, my_ets->tc_rx_bw, माप(ets->tc_rx_bw));
	स_नकल(ets->tc_tsa, my_ets->tc_tsa, माप(ets->tc_tsa));
	स_नकल(ets->prio_tc, my_ets->prio_tc, माप(ets->prio_tc));
	वापस 0;
error:
	kमुक्त(my_ets);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_dcbnl_ieee_setets(काष्ठा net_device *dev, काष्ठा ieee_ets *ets)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	काष्ठा ieee_ets *my_ets = bp->ieee_ets;
	u8 max_tc = 0;
	पूर्णांक rc, i;

	अगर (!(bp->dcbx_cap & DCB_CAP_DCBX_VER_IEEE) ||
	    !(bp->dcbx_cap & DCB_CAP_DCBX_HOST))
		वापस -EINVAL;

	rc = bnxt_ets_validate(bp, ets, &max_tc);
	अगर (!rc) अणु
		अगर (!my_ets) अणु
			my_ets = kzalloc(माप(*my_ets), GFP_KERNEL);
			अगर (!my_ets)
				वापस -ENOMEM;
			/* initialize PRI2TC mappings to invalid value */
			क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++)
				my_ets->prio_tc[i] = IEEE_8021QAZ_MAX_TCS;
			bp->ieee_ets = my_ets;
		पूर्ण
		rc = bnxt_setup_mq_tc(dev, max_tc);
		अगर (rc)
			वापस rc;
		rc = bnxt_hwrm_queue_cos2bw_cfg(bp, ets, max_tc);
		अगर (rc)
			वापस rc;
		rc = bnxt_hwrm_queue_pri2cos_cfg(bp, ets);
		अगर (rc)
			वापस rc;
		स_नकल(my_ets, ets, माप(*my_ets));
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_dcbnl_ieee_getpfc(काष्ठा net_device *dev, काष्ठा ieee_pfc *pfc)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	__le64 *stats = bp->port_stats.hw_stats;
	काष्ठा ieee_pfc *my_pfc = bp->ieee_pfc;
	दीर्घ rx_off, tx_off;
	पूर्णांक i, rc;

	pfc->pfc_cap = bp->max_lltc;

	अगर (!my_pfc) अणु
		अगर (bp->dcbx_cap & DCB_CAP_DCBX_HOST)
			वापस 0;

		my_pfc = kzalloc(माप(*my_pfc), GFP_KERNEL);
		अगर (!my_pfc)
			वापस 0;
		bp->ieee_pfc = my_pfc;
		rc = bnxt_hwrm_queue_pfc_qcfg(bp, my_pfc);
		अगर (rc)
			वापस 0;
	पूर्ण

	pfc->pfc_en = my_pfc->pfc_en;
	pfc->mbc = my_pfc->mbc;
	pfc->delay = my_pfc->delay;

	अगर (!stats)
		वापस 0;

	rx_off = BNXT_RX_STATS_OFFSET(rx_pfc_ena_frames_pri0);
	tx_off = BNXT_TX_STATS_OFFSET(tx_pfc_ena_frames_pri0);
	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++, rx_off++, tx_off++) अणु
		pfc->requests[i] = le64_to_cpu(*(stats + tx_off));
		pfc->indications[i] = le64_to_cpu(*(stats + rx_off));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_dcbnl_ieee_setpfc(काष्ठा net_device *dev, काष्ठा ieee_pfc *pfc)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	काष्ठा ieee_pfc *my_pfc = bp->ieee_pfc;
	पूर्णांक rc;

	अगर (!(bp->dcbx_cap & DCB_CAP_DCBX_VER_IEEE) ||
	    !(bp->dcbx_cap & DCB_CAP_DCBX_HOST))
		वापस -EINVAL;

	अगर (!my_pfc) अणु
		my_pfc = kzalloc(माप(*my_pfc), GFP_KERNEL);
		अगर (!my_pfc)
			वापस -ENOMEM;
		bp->ieee_pfc = my_pfc;
	पूर्ण
	rc = bnxt_hwrm_queue_pfc_cfg(bp, pfc);
	अगर (!rc)
		स_नकल(my_pfc, pfc, माप(*my_pfc));

	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_dcbnl_ieee_dscp_app_prep(काष्ठा bnxt *bp, काष्ठा dcb_app *app)
अणु
	अगर (app->selector == IEEE_8021QAZ_APP_SEL_DSCP) अणु
		अगर (!bp->max_dscp_value)
			वापस -ENOTSUPP;
		अगर (app->protocol > bp->max_dscp_value)
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_dcbnl_ieee_setapp(काष्ठा net_device *dev, काष्ठा dcb_app *app)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	पूर्णांक rc;

	अगर (!(bp->dcbx_cap & DCB_CAP_DCBX_VER_IEEE) ||
	    !(bp->dcbx_cap & DCB_CAP_DCBX_HOST))
		वापस -EINVAL;

	rc = bnxt_dcbnl_ieee_dscp_app_prep(bp, app);
	अगर (rc)
		वापस rc;

	rc = dcb_ieee_setapp(dev, app);
	अगर (rc)
		वापस rc;

	अगर ((app->selector == IEEE_8021QAZ_APP_SEL_ETHERTYPE &&
	     app->protocol == ETH_P_IBOE) ||
	    (app->selector == IEEE_8021QAZ_APP_SEL_DGRAM &&
	     app->protocol == ROCE_V2_UDP_DPORT))
		rc = bnxt_hwrm_set_dcbx_app(bp, app, true);

	अगर (app->selector == IEEE_8021QAZ_APP_SEL_DSCP)
		rc = bnxt_hwrm_queue_dscp2pri_cfg(bp, app, true);

	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_dcbnl_ieee_delapp(काष्ठा net_device *dev, काष्ठा dcb_app *app)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	पूर्णांक rc;

	अगर (!(bp->dcbx_cap & DCB_CAP_DCBX_VER_IEEE) ||
	    !(bp->dcbx_cap & DCB_CAP_DCBX_HOST))
		वापस -EINVAL;

	rc = bnxt_dcbnl_ieee_dscp_app_prep(bp, app);
	अगर (rc)
		वापस rc;

	rc = dcb_ieee_delapp(dev, app);
	अगर (rc)
		वापस rc;
	अगर ((app->selector == IEEE_8021QAZ_APP_SEL_ETHERTYPE &&
	     app->protocol == ETH_P_IBOE) ||
	    (app->selector == IEEE_8021QAZ_APP_SEL_DGRAM &&
	     app->protocol == ROCE_V2_UDP_DPORT))
		rc = bnxt_hwrm_set_dcbx_app(bp, app, false);

	अगर (app->selector == IEEE_8021QAZ_APP_SEL_DSCP)
		rc = bnxt_hwrm_queue_dscp2pri_cfg(bp, app, false);

	वापस rc;
पूर्ण

अटल u8 bnxt_dcbnl_getdcbx(काष्ठा net_device *dev)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);

	वापस bp->dcbx_cap;
पूर्ण

अटल u8 bnxt_dcbnl_setdcbx(काष्ठा net_device *dev, u8 mode)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);

	/* All firmware DCBX settings are set in NVRAM */
	अगर (bp->dcbx_cap & DCB_CAP_DCBX_LLD_MANAGED)
		वापस 1;

	अगर (mode & DCB_CAP_DCBX_HOST) अणु
		अगर (BNXT_VF(bp) || (bp->fw_cap & BNXT_FW_CAP_LLDP_AGENT))
			वापस 1;

		/* only support IEEE */
		अगर ((mode & DCB_CAP_DCBX_VER_CEE) ||
		    !(mode & DCB_CAP_DCBX_VER_IEEE))
			वापस 1;
	पूर्ण

	अगर (mode == bp->dcbx_cap)
		वापस 0;

	bp->dcbx_cap = mode;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dcbnl_rtnl_ops dcbnl_ops = अणु
	.ieee_getets	= bnxt_dcbnl_ieee_getets,
	.ieee_setets	= bnxt_dcbnl_ieee_setets,
	.ieee_getpfc	= bnxt_dcbnl_ieee_getpfc,
	.ieee_setpfc	= bnxt_dcbnl_ieee_setpfc,
	.ieee_setapp	= bnxt_dcbnl_ieee_setapp,
	.ieee_delapp	= bnxt_dcbnl_ieee_delapp,
	.getdcbx	= bnxt_dcbnl_getdcbx,
	.setdcbx	= bnxt_dcbnl_setdcbx,
पूर्ण;

व्योम bnxt_dcb_init(काष्ठा bnxt *bp)
अणु
	bp->dcbx_cap = 0;
	अगर (bp->hwrm_spec_code < 0x10501)
		वापस;

	bnxt_hwrm_queue_dscp_qcaps(bp);
	bp->dcbx_cap = DCB_CAP_DCBX_VER_IEEE;
	अगर (BNXT_PF(bp) && !(bp->fw_cap & BNXT_FW_CAP_LLDP_AGENT))
		bp->dcbx_cap |= DCB_CAP_DCBX_HOST;
	अन्यथा अगर (bp->fw_cap & BNXT_FW_CAP_DCBX_AGENT)
		bp->dcbx_cap |= DCB_CAP_DCBX_LLD_MANAGED;
	bp->dev->dcbnl_ops = &dcbnl_ops;
पूर्ण

व्योम bnxt_dcb_मुक्त(काष्ठा bnxt *bp)
अणु
	kमुक्त(bp->ieee_pfc);
	kमुक्त(bp->ieee_ets);
	bp->ieee_pfc = शून्य;
	bp->ieee_ets = शून्य;
पूर्ण

#अन्यथा

व्योम bnxt_dcb_init(काष्ठा bnxt *bp)
अणु
पूर्ण

व्योम bnxt_dcb_मुक्त(काष्ठा bnxt *bp)
अणु
पूर्ण

#पूर्ण_अगर
