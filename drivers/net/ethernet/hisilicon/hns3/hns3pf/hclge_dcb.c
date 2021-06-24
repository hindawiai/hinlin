<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright (c) 2016-2017 Hisilicon Limited.

#समावेश "hclge_main.h"
#समावेश "hclge_dcb.h"
#समावेश "hclge_tm.h"
#समावेश "hnae3.h"

#घोषणा BW_PERCENT	100

अटल पूर्णांक hclge_ieee_ets_to_पंचांग_info(काष्ठा hclge_dev *hdev,
				     काष्ठा ieee_ets *ets)
अणु
	u8 i;

	क्रम (i = 0; i < HNAE3_MAX_TC; i++) अणु
		चयन (ets->tc_tsa[i]) अणु
		हाल IEEE_8021QAZ_TSA_STRICT:
			hdev->पंचांग_info.tc_info[i].tc_sch_mode =
				HCLGE_SCH_MODE_SP;
			hdev->पंचांग_info.pg_info[0].tc_dwrr[i] = 0;
			अवरोध;
		हाल IEEE_8021QAZ_TSA_ETS:
			hdev->पंचांग_info.tc_info[i].tc_sch_mode =
				HCLGE_SCH_MODE_DWRR;
			hdev->पंचांग_info.pg_info[0].tc_dwrr[i] =
				ets->tc_tx_bw[i];
			अवरोध;
		शेष:
			/* Hardware only supports SP (strict priority)
			 * or ETS (enhanced transmission selection)
			 * algorithms, अगर we receive some other value
			 * from dcbnl, then throw an error.
			 */
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	hclge_पंचांग_prio_tc_info_update(hdev, ets->prio_tc);

	वापस 0;
पूर्ण

अटल व्योम hclge_पंचांग_info_to_ieee_ets(काष्ठा hclge_dev *hdev,
				      काष्ठा ieee_ets *ets)
अणु
	u32 i;

	स_रखो(ets, 0, माप(*ets));
	ets->willing = 1;
	ets->ets_cap = hdev->tc_max;

	क्रम (i = 0; i < HNAE3_MAX_TC; i++) अणु
		ets->prio_tc[i] = hdev->पंचांग_info.prio_tc[i];
		ets->tc_tx_bw[i] = hdev->पंचांग_info.pg_info[0].tc_dwrr[i];

		अगर (hdev->पंचांग_info.tc_info[i].tc_sch_mode ==
		    HCLGE_SCH_MODE_SP)
			ets->tc_tsa[i] = IEEE_8021QAZ_TSA_STRICT;
		अन्यथा
			ets->tc_tsa[i] = IEEE_8021QAZ_TSA_ETS;
	पूर्ण
पूर्ण

/* IEEE std */
अटल पूर्णांक hclge_ieee_getets(काष्ठा hnae3_handle *h, काष्ठा ieee_ets *ets)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(h);
	काष्ठा hclge_dev *hdev = vport->back;

	hclge_पंचांग_info_to_ieee_ets(hdev, ets);

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_dcb_common_validate(काष्ठा hclge_dev *hdev, u8 num_tc,
				     u8 *prio_tc)
अणु
	पूर्णांक i;

	अगर (num_tc > hdev->tc_max) अणु
		dev_err(&hdev->pdev->dev,
			"tc num checking failed, %u > tc_max(%u)\n",
			num_tc, hdev->tc_max);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < HNAE3_MAX_USER_PRIO; i++) अणु
		अगर (prio_tc[i] >= num_tc) अणु
			dev_err(&hdev->pdev->dev,
				"prio_tc[%d] checking failed, %u >= num_tc(%u)\n",
				i, prio_tc[i], num_tc);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (num_tc > hdev->vport[0].alloc_tqps) अणु
		dev_err(&hdev->pdev->dev,
			"allocated tqp checking failed, %u > tqp(%u)\n",
			num_tc, hdev->vport[0].alloc_tqps);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_ets_validate(काष्ठा hclge_dev *hdev, काष्ठा ieee_ets *ets,
			      u8 *tc, bool *changed)
अणु
	bool has_ets_tc = false;
	u32 total_ets_bw = 0;
	u8 max_tc = 0;
	पूर्णांक ret;
	u8 i;

	क्रम (i = 0; i < HNAE3_MAX_USER_PRIO; i++) अणु
		अगर (ets->prio_tc[i] != hdev->पंचांग_info.prio_tc[i])
			*changed = true;

		अगर (ets->prio_tc[i] > max_tc)
			max_tc = ets->prio_tc[i];
	पूर्ण

	ret = hclge_dcb_common_validate(hdev, max_tc + 1, ets->prio_tc);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < hdev->tc_max; i++) अणु
		चयन (ets->tc_tsa[i]) अणु
		हाल IEEE_8021QAZ_TSA_STRICT:
			अगर (hdev->पंचांग_info.tc_info[i].tc_sch_mode !=
				HCLGE_SCH_MODE_SP)
				*changed = true;
			अवरोध;
		हाल IEEE_8021QAZ_TSA_ETS:
			अगर (hdev->पंचांग_info.tc_info[i].tc_sch_mode !=
				HCLGE_SCH_MODE_DWRR)
				*changed = true;

			total_ets_bw += ets->tc_tx_bw[i];
			has_ets_tc = true;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (has_ets_tc && total_ets_bw != BW_PERCENT)
		वापस -EINVAL;

	*tc = max_tc + 1;
	अगर (*tc != hdev->पंचांग_info.num_tc)
		*changed = true;

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_map_update(काष्ठा hclge_dev *hdev)
अणु
	पूर्णांक ret;

	ret = hclge_पंचांग_schd_setup_hw(hdev);
	अगर (ret)
		वापस ret;

	ret = hclge_छोड़ो_setup_hw(hdev, false);
	अगर (ret)
		वापस ret;

	ret = hclge_buffer_alloc(hdev);
	अगर (ret)
		वापस ret;

	hclge_rss_indir_init_cfg(hdev);

	वापस hclge_rss_init_hw(hdev);
पूर्ण

अटल पूर्णांक hclge_notअगरy_करोwn_uinit(काष्ठा hclge_dev *hdev)
अणु
	पूर्णांक ret;

	ret = hclge_notअगरy_client(hdev, HNAE3_DOWN_CLIENT);
	अगर (ret)
		वापस ret;

	वापस hclge_notअगरy_client(hdev, HNAE3_UNINIT_CLIENT);
पूर्ण

अटल पूर्णांक hclge_notअगरy_init_up(काष्ठा hclge_dev *hdev)
अणु
	पूर्णांक ret;

	ret = hclge_notअगरy_client(hdev, HNAE3_INIT_CLIENT);
	अगर (ret)
		वापस ret;

	वापस hclge_notअगरy_client(hdev, HNAE3_UP_CLIENT);
पूर्ण

अटल पूर्णांक hclge_ieee_setets(काष्ठा hnae3_handle *h, काष्ठा ieee_ets *ets)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(h);
	काष्ठा net_device *netdev = h->kinfo.netdev;
	काष्ठा hclge_dev *hdev = vport->back;
	bool map_changed = false;
	u8 num_tc = 0;
	पूर्णांक ret;

	अगर (!(hdev->dcbx_cap & DCB_CAP_DCBX_VER_IEEE) ||
	    hdev->flag & HCLGE_FLAG_MQPRIO_ENABLE)
		वापस -EINVAL;

	ret = hclge_ets_validate(hdev, ets, &num_tc, &map_changed);
	अगर (ret)
		वापस ret;

	अगर (map_changed) अणु
		netअगर_dbg(h, drv, netdev, "set ets\n");

		ret = hclge_notअगरy_करोwn_uinit(hdev);
		अगर (ret)
			वापस ret;
	पूर्ण

	hclge_पंचांग_schd_info_update(hdev, num_tc);

	ret = hclge_ieee_ets_to_पंचांग_info(hdev, ets);
	अगर (ret)
		जाओ err_out;

	अगर (map_changed) अणु
		ret = hclge_map_update(hdev);
		अगर (ret)
			जाओ err_out;

		ret = hclge_notअगरy_init_up(hdev);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस hclge_पंचांग_dwrr_cfg(hdev);

err_out:
	अगर (!map_changed)
		वापस ret;

	hclge_notअगरy_init_up(hdev);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_ieee_getpfc(काष्ठा hnae3_handle *h, काष्ठा ieee_pfc *pfc)
अणु
	u64 requests[HNAE3_MAX_TC], indications[HNAE3_MAX_TC];
	काष्ठा hclge_vport *vport = hclge_get_vport(h);
	काष्ठा hclge_dev *hdev = vport->back;
	u8 i, j, pfc_map, *prio_tc;
	पूर्णांक ret;

	स_रखो(pfc, 0, माप(*pfc));
	pfc->pfc_cap = hdev->pfc_max;
	prio_tc = hdev->पंचांग_info.prio_tc;
	pfc_map = hdev->पंचांग_info.hw_pfc_map;

	/* Pfc setting is based on TC */
	क्रम (i = 0; i < hdev->पंचांग_info.num_tc; i++) अणु
		क्रम (j = 0; j < HNAE3_MAX_USER_PRIO; j++) अणु
			अगर ((prio_tc[j] == i) && (pfc_map & BIT(i)))
				pfc->pfc_en |= BIT(j);
		पूर्ण
	पूर्ण

	ret = hclge_pfc_tx_stats_get(hdev, requests);
	अगर (ret)
		वापस ret;

	ret = hclge_pfc_rx_stats_get(hdev, indications);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < HCLGE_MAX_TC_NUM; i++) अणु
		pfc->requests[i] = requests[i];
		pfc->indications[i] = indications[i];
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक hclge_ieee_setpfc(काष्ठा hnae3_handle *h, काष्ठा ieee_pfc *pfc)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(h);
	काष्ठा net_device *netdev = h->kinfo.netdev;
	काष्ठा hclge_dev *hdev = vport->back;
	u8 i, j, pfc_map, *prio_tc;
	पूर्णांक ret;

	अगर (!(hdev->dcbx_cap & DCB_CAP_DCBX_VER_IEEE) ||
	    hdev->flag & HCLGE_FLAG_MQPRIO_ENABLE)
		वापस -EINVAL;

	अगर (pfc->pfc_en == hdev->पंचांग_info.pfc_en)
		वापस 0;

	prio_tc = hdev->पंचांग_info.prio_tc;
	pfc_map = 0;

	क्रम (i = 0; i < hdev->पंचांग_info.num_tc; i++) अणु
		क्रम (j = 0; j < HNAE3_MAX_USER_PRIO; j++) अणु
			अगर ((prio_tc[j] == i) && (pfc->pfc_en & BIT(j))) अणु
				pfc_map |= BIT(i);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	hdev->पंचांग_info.hw_pfc_map = pfc_map;
	hdev->पंचांग_info.pfc_en = pfc->pfc_en;

	netअगर_dbg(h, drv, netdev,
		  "set pfc: pfc_en=%x, pfc_map=%x, num_tc=%u\n",
		  pfc->pfc_en, pfc_map, hdev->पंचांग_info.num_tc);

	hclge_पंचांग_pfc_info_update(hdev);

	ret = hclge_छोड़ो_setup_hw(hdev, false);
	अगर (ret)
		वापस ret;

	ret = hclge_notअगरy_client(hdev, HNAE3_DOWN_CLIENT);
	अगर (ret)
		वापस ret;

	ret = hclge_buffer_alloc(hdev);
	अगर (ret) अणु
		hclge_notअगरy_client(hdev, HNAE3_UP_CLIENT);
		वापस ret;
	पूर्ण

	वापस hclge_notअगरy_client(hdev, HNAE3_UP_CLIENT);
पूर्ण

/* DCBX configuration */
अटल u8 hclge_getdcbx(काष्ठा hnae3_handle *h)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(h);
	काष्ठा hclge_dev *hdev = vport->back;

	अगर (hdev->flag & HCLGE_FLAG_MQPRIO_ENABLE)
		वापस 0;

	वापस hdev->dcbx_cap;
पूर्ण

अटल u8 hclge_setdcbx(काष्ठा hnae3_handle *h, u8 mode)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(h);
	काष्ठा net_device *netdev = h->kinfo.netdev;
	काष्ठा hclge_dev *hdev = vport->back;

	netअगर_dbg(h, drv, netdev, "set dcbx: mode=%u\n", mode);

	/* No support क्रम LLD_MANAGED modes or CEE */
	अगर ((mode & DCB_CAP_DCBX_LLD_MANAGED) ||
	    (mode & DCB_CAP_DCBX_VER_CEE) ||
	    !(mode & DCB_CAP_DCBX_HOST))
		वापस 1;

	hdev->dcbx_cap = mode;

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_mqprio_qopt_check(काष्ठा hclge_dev *hdev,
				   काष्ठा tc_mqprio_qopt_offload *mqprio_qopt)
अणु
	u16 queue_sum = 0;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (!mqprio_qopt->qopt.num_tc) अणु
		mqprio_qopt->qopt.num_tc = 1;
		वापस 0;
	पूर्ण

	ret = hclge_dcb_common_validate(hdev, mqprio_qopt->qopt.num_tc,
					mqprio_qopt->qopt.prio_tc_map);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < mqprio_qopt->qopt.num_tc; i++) अणु
		अगर (!is_घातer_of_2(mqprio_qopt->qopt.count[i])) अणु
			dev_err(&hdev->pdev->dev,
				"qopt queue count must be power of 2\n");
			वापस -EINVAL;
		पूर्ण

		अगर (mqprio_qopt->qopt.count[i] > hdev->pf_rss_size_max) अणु
			dev_err(&hdev->pdev->dev,
				"qopt queue count should be no more than %u\n",
				hdev->pf_rss_size_max);
			वापस -EINVAL;
		पूर्ण

		अगर (mqprio_qopt->qopt.offset[i] != queue_sum) अणु
			dev_err(&hdev->pdev->dev,
				"qopt queue offset must start from 0, and being continuous\n");
			वापस -EINVAL;
		पूर्ण

		अगर (mqprio_qopt->min_rate[i] || mqprio_qopt->max_rate[i]) अणु
			dev_err(&hdev->pdev->dev,
				"qopt tx_rate is not supported\n");
			वापस -EOPNOTSUPP;
		पूर्ण

		queue_sum = mqprio_qopt->qopt.offset[i];
		queue_sum += mqprio_qopt->qopt.count[i];
	पूर्ण
	अगर (hdev->vport[0].alloc_tqps < queue_sum) अणु
		dev_err(&hdev->pdev->dev,
			"qopt queue count sum should be less than %u\n",
			hdev->vport[0].alloc_tqps);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hclge_sync_mqprio_qopt(काष्ठा hnae3_tc_info *tc_info,
				   काष्ठा tc_mqprio_qopt_offload *mqprio_qopt)
अणु
	पूर्णांक i;

	स_रखो(tc_info, 0, माप(*tc_info));
	tc_info->num_tc = mqprio_qopt->qopt.num_tc;
	स_नकल(tc_info->prio_tc, mqprio_qopt->qopt.prio_tc_map,
	       माप_field(काष्ठा hnae3_tc_info, prio_tc));
	स_नकल(tc_info->tqp_count, mqprio_qopt->qopt.count,
	       माप_field(काष्ठा hnae3_tc_info, tqp_count));
	स_नकल(tc_info->tqp_offset, mqprio_qopt->qopt.offset,
	       माप_field(काष्ठा hnae3_tc_info, tqp_offset));

	क्रम (i = 0; i < HNAE3_MAX_USER_PRIO; i++)
		set_bit(tc_info->prio_tc[i], &tc_info->tc_en);
पूर्ण

अटल पूर्णांक hclge_config_tc(काष्ठा hclge_dev *hdev,
			   काष्ठा hnae3_tc_info *tc_info)
अणु
	पूर्णांक i;

	hclge_पंचांग_schd_info_update(hdev, tc_info->num_tc);
	क्रम (i = 0; i < HNAE3_MAX_USER_PRIO; i++)
		hdev->पंचांग_info.prio_tc[i] = tc_info->prio_tc[i];

	वापस hclge_map_update(hdev);
पूर्ण

/* Set up TC क्रम hardware offloaded mqprio in channel mode */
अटल पूर्णांक hclge_setup_tc(काष्ठा hnae3_handle *h,
			  काष्ठा tc_mqprio_qopt_offload *mqprio_qopt)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(h);
	काष्ठा hnae3_knic_निजी_info *kinfo;
	काष्ठा hclge_dev *hdev = vport->back;
	काष्ठा hnae3_tc_info old_tc_info;
	u8 tc = mqprio_qopt->qopt.num_tc;
	पूर्णांक ret;

	/* अगर client unरेजिस्टरed, it's not allowed to change
	 * mqprio configuration, which may cause uninit ring
	 * fail.
	 */
	अगर (!test_bit(HCLGE_STATE_NIC_REGISTERED, &hdev->state))
		वापस -EBUSY;

	अगर (hdev->flag & HCLGE_FLAG_DCB_ENABLE)
		वापस -EINVAL;

	ret = hclge_mqprio_qopt_check(hdev, mqprio_qopt);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"failed to check mqprio qopt params, ret = %d\n", ret);
		वापस ret;
	पूर्ण

	ret = hclge_notअगरy_करोwn_uinit(hdev);
	अगर (ret)
		वापस ret;

	kinfo = &vport->nic.kinfo;
	स_नकल(&old_tc_info, &kinfo->tc_info, माप(old_tc_info));
	hclge_sync_mqprio_qopt(&kinfo->tc_info, mqprio_qopt);
	kinfo->tc_info.mqprio_active = tc > 0;

	ret = hclge_config_tc(hdev, &kinfo->tc_info);
	अगर (ret)
		जाओ err_out;

	hdev->flag &= ~HCLGE_FLAG_DCB_ENABLE;

	अगर (tc > 1)
		hdev->flag |= HCLGE_FLAG_MQPRIO_ENABLE;
	अन्यथा
		hdev->flag &= ~HCLGE_FLAG_MQPRIO_ENABLE;

	वापस hclge_notअगरy_init_up(hdev);

err_out:
	/* roll-back */
	स_नकल(&kinfo->tc_info, &old_tc_info, माप(old_tc_info));
	अगर (hclge_config_tc(hdev, &kinfo->tc_info))
		dev_err(&hdev->pdev->dev,
			"failed to roll back tc configuration\n");

	hclge_notअगरy_init_up(hdev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा hnae3_dcb_ops hns3_dcb_ops = अणु
	.ieee_getets	= hclge_ieee_getets,
	.ieee_setets	= hclge_ieee_setets,
	.ieee_getpfc	= hclge_ieee_getpfc,
	.ieee_setpfc	= hclge_ieee_setpfc,
	.getdcbx	= hclge_getdcbx,
	.setdcbx	= hclge_setdcbx,
	.setup_tc	= hclge_setup_tc,
पूर्ण;

व्योम hclge_dcb_ops_set(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_vport *vport = hdev->vport;
	काष्ठा hnae3_knic_निजी_info *kinfo;

	/* Hdev करोes not support DCB or vport is
	 * not a pf, then dcb_ops is not set.
	 */
	अगर (!hnae3_dev_dcb_supported(hdev) ||
	    vport->vport_id != 0)
		वापस;

	kinfo = &vport->nic.kinfo;
	kinfo->dcb_ops = &hns3_dcb_ops;
	hdev->dcbx_cap = DCB_CAP_DCBX_VER_IEEE | DCB_CAP_DCBX_HOST;
पूर्ण
