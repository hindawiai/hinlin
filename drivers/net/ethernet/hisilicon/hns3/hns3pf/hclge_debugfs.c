<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Copyright (c) 2018-2019 Hisilicon Limited. */

#समावेश <linux/device.h>

#समावेश "hclge_debugfs.h"
#समावेश "hclge_main.h"
#समावेश "hclge_tm.h"
#समावेश "hnae3.h"

अटल स्थिर काष्ठा hclge_dbg_reg_type_info hclge_dbg_reg_info[] = अणु
	अणु .reg_type = "bios common",
	  .dfx_msg = &hclge_dbg_bios_common_reg[0],
	  .reg_msg = अणु .msg_num = ARRAY_SIZE(hclge_dbg_bios_common_reg),
		       .offset = HCLGE_DBG_DFX_BIOS_OFFSET,
		       .cmd = HCLGE_OPC_DFX_BIOS_COMMON_REG पूर्ण पूर्ण,
	अणु .reg_type = "ssu",
	  .dfx_msg = &hclge_dbg_ssu_reg_0[0],
	  .reg_msg = अणु .msg_num = ARRAY_SIZE(hclge_dbg_ssu_reg_0),
		       .offset = HCLGE_DBG_DFX_SSU_0_OFFSET,
		       .cmd = HCLGE_OPC_DFX_SSU_REG_0 पूर्ण पूर्ण,
	अणु .reg_type = "ssu",
	  .dfx_msg = &hclge_dbg_ssu_reg_1[0],
	  .reg_msg = अणु .msg_num = ARRAY_SIZE(hclge_dbg_ssu_reg_1),
		       .offset = HCLGE_DBG_DFX_SSU_1_OFFSET,
		       .cmd = HCLGE_OPC_DFX_SSU_REG_1 पूर्ण पूर्ण,
	अणु .reg_type = "ssu",
	  .dfx_msg = &hclge_dbg_ssu_reg_2[0],
	  .reg_msg = अणु .msg_num = ARRAY_SIZE(hclge_dbg_ssu_reg_2),
		       .offset = HCLGE_DBG_DFX_SSU_2_OFFSET,
		       .cmd = HCLGE_OPC_DFX_SSU_REG_2 पूर्ण पूर्ण,
	अणु .reg_type = "igu egu",
	  .dfx_msg = &hclge_dbg_igu_egu_reg[0],
	  .reg_msg = अणु .msg_num = ARRAY_SIZE(hclge_dbg_igu_egu_reg),
		       .offset = HCLGE_DBG_DFX_IGU_OFFSET,
		       .cmd = HCLGE_OPC_DFX_IGU_EGU_REG पूर्ण पूर्ण,
	अणु .reg_type = "rpu",
	  .dfx_msg = &hclge_dbg_rpu_reg_0[0],
	  .reg_msg = अणु .msg_num = ARRAY_SIZE(hclge_dbg_rpu_reg_0),
		       .offset = HCLGE_DBG_DFX_RPU_0_OFFSET,
		       .cmd = HCLGE_OPC_DFX_RPU_REG_0 पूर्ण पूर्ण,
	अणु .reg_type = "rpu",
	  .dfx_msg = &hclge_dbg_rpu_reg_1[0],
	  .reg_msg = अणु .msg_num = ARRAY_SIZE(hclge_dbg_rpu_reg_1),
		       .offset = HCLGE_DBG_DFX_RPU_1_OFFSET,
		       .cmd = HCLGE_OPC_DFX_RPU_REG_1 पूर्ण पूर्ण,
	अणु .reg_type = "ncsi",
	  .dfx_msg = &hclge_dbg_ncsi_reg[0],
	  .reg_msg = अणु .msg_num = ARRAY_SIZE(hclge_dbg_ncsi_reg),
		       .offset = HCLGE_DBG_DFX_NCSI_OFFSET,
		       .cmd = HCLGE_OPC_DFX_NCSI_REG पूर्ण पूर्ण,
	अणु .reg_type = "rtc",
	  .dfx_msg = &hclge_dbg_rtc_reg[0],
	  .reg_msg = अणु .msg_num = ARRAY_SIZE(hclge_dbg_rtc_reg),
		       .offset = HCLGE_DBG_DFX_RTC_OFFSET,
		       .cmd = HCLGE_OPC_DFX_RTC_REG पूर्ण पूर्ण,
	अणु .reg_type = "ppp",
	  .dfx_msg = &hclge_dbg_ppp_reg[0],
	  .reg_msg = अणु .msg_num = ARRAY_SIZE(hclge_dbg_ppp_reg),
		       .offset = HCLGE_DBG_DFX_PPP_OFFSET,
		       .cmd = HCLGE_OPC_DFX_PPP_REG पूर्ण पूर्ण,
	अणु .reg_type = "rcb",
	  .dfx_msg = &hclge_dbg_rcb_reg[0],
	  .reg_msg = अणु .msg_num = ARRAY_SIZE(hclge_dbg_rcb_reg),
		       .offset = HCLGE_DBG_DFX_RCB_OFFSET,
		       .cmd = HCLGE_OPC_DFX_RCB_REG पूर्ण पूर्ण,
	अणु .reg_type = "tqp",
	  .dfx_msg = &hclge_dbg_tqp_reg[0],
	  .reg_msg = अणु .msg_num = ARRAY_SIZE(hclge_dbg_tqp_reg),
		       .offset = HCLGE_DBG_DFX_TQP_OFFSET,
		       .cmd = HCLGE_OPC_DFX_TQP_REG पूर्ण पूर्ण,
पूर्ण;

अटल पूर्णांक hclge_dbg_get_dfx_bd_num(काष्ठा hclge_dev *hdev, पूर्णांक offset)
अणु
	काष्ठा hclge_desc desc[HCLGE_GET_DFX_REG_TYPE_CNT];
	पूर्णांक entries_per_desc;
	पूर्णांक index;
	पूर्णांक ret;

	ret = hclge_query_bd_num_cmd_send(hdev, desc);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"get dfx bdnum fail, ret = %d\n", ret);
		वापस ret;
	पूर्ण

	entries_per_desc = ARRAY_SIZE(desc[0].data);
	index = offset % entries_per_desc;
	वापस le32_to_cpu(desc[offset / entries_per_desc].data[index]);
पूर्ण

अटल पूर्णांक hclge_dbg_cmd_send(काष्ठा hclge_dev *hdev,
			      काष्ठा hclge_desc *desc_src,
			      पूर्णांक index, पूर्णांक bd_num,
			      क्रमागत hclge_opcode_type cmd)
अणु
	काष्ठा hclge_desc *desc = desc_src;
	पूर्णांक ret, i;

	hclge_cmd_setup_basic_desc(desc, cmd, true);
	desc->data[0] = cpu_to_le32(index);

	क्रम (i = 1; i < bd_num; i++) अणु
		desc->flag |= cpu_to_le16(HCLGE_CMD_FLAG_NEXT);
		desc++;
		hclge_cmd_setup_basic_desc(desc, cmd, true);
	पूर्ण

	ret = hclge_cmd_send(&hdev->hw, desc_src, bd_num);
	अगर (ret)
		dev_err(&hdev->pdev->dev,
			"cmd(0x%x) send fail, ret = %d\n", cmd, ret);
	वापस ret;
पूर्ण

अटल व्योम hclge_dbg_dump_reg_common(काष्ठा hclge_dev *hdev,
				      स्थिर काष्ठा hclge_dbg_reg_type_info *reg_info,
				      स्थिर अक्षर *cmd_buf)
अणु
#घोषणा IDX_OFFSET	1

	स्थिर अक्षर *s = &cmd_buf[म_माप(reg_info->reg_type) + IDX_OFFSET];
	स्थिर काष्ठा hclge_dbg_dfx_message *dfx_message = reg_info->dfx_msg;
	स्थिर काष्ठा hclge_dbg_reg_common_msg *reg_msg = &reg_info->reg_msg;
	काष्ठा hclge_desc *desc_src;
	काष्ठा hclge_desc *desc;
	पूर्णांक entries_per_desc;
	पूर्णांक bd_num, buf_len;
	पूर्णांक index = 0;
	पूर्णांक min_num;
	पूर्णांक ret, i;

	अगर (*s) अणु
		ret = kstrtouपूर्णांक(s, 0, &index);
		index = (ret != 0) ? 0 : index;
	पूर्ण

	bd_num = hclge_dbg_get_dfx_bd_num(hdev, reg_msg->offset);
	अगर (bd_num <= 0) अणु
		dev_err(&hdev->pdev->dev, "get cmd(%d) bd num(%d) failed\n",
			reg_msg->offset, bd_num);
		वापस;
	पूर्ण

	buf_len = माप(काष्ठा hclge_desc) * bd_num;
	desc_src = kzalloc(buf_len, GFP_KERNEL);
	अगर (!desc_src)
		वापस;

	desc = desc_src;
	ret = hclge_dbg_cmd_send(hdev, desc, index, bd_num, reg_msg->cmd);
	अगर (ret) अणु
		kमुक्त(desc_src);
		वापस;
	पूर्ण

	entries_per_desc = ARRAY_SIZE(desc->data);
	min_num = min_t(पूर्णांक, bd_num * entries_per_desc, reg_msg->msg_num);

	desc = desc_src;
	क्रम (i = 0; i < min_num; i++) अणु
		अगर (i > 0 && (i % entries_per_desc) == 0)
			desc++;
		अगर (dfx_message->flag)
			dev_info(&hdev->pdev->dev, "%s: 0x%x\n",
				 dfx_message->message,
				 le32_to_cpu(desc->data[i % entries_per_desc]));

		dfx_message++;
	पूर्ण

	kमुक्त(desc_src);
पूर्ण

अटल व्योम hclge_dbg_dump_mac_enable_status(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_config_mac_mode_cmd *req;
	काष्ठा hclge_desc desc;
	u32 loop_en;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_CONFIG_MAC_MODE, true);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"failed to dump mac enable status, ret = %d\n", ret);
		वापस;
	पूर्ण

	req = (काष्ठा hclge_config_mac_mode_cmd *)desc.data;
	loop_en = le32_to_cpu(req->txrx_pad_fcs_loop_en);

	dev_info(&hdev->pdev->dev, "config_mac_trans_en: %#x\n",
		 hnae3_get_bit(loop_en, HCLGE_MAC_TX_EN_B));
	dev_info(&hdev->pdev->dev, "config_mac_rcv_en: %#x\n",
		 hnae3_get_bit(loop_en, HCLGE_MAC_RX_EN_B));
	dev_info(&hdev->pdev->dev, "config_pad_trans_en: %#x\n",
		 hnae3_get_bit(loop_en, HCLGE_MAC_PAD_TX_B));
	dev_info(&hdev->pdev->dev, "config_pad_rcv_en: %#x\n",
		 hnae3_get_bit(loop_en, HCLGE_MAC_PAD_RX_B));
	dev_info(&hdev->pdev->dev, "config_1588_trans_en: %#x\n",
		 hnae3_get_bit(loop_en, HCLGE_MAC_1588_TX_B));
	dev_info(&hdev->pdev->dev, "config_1588_rcv_en: %#x\n",
		 hnae3_get_bit(loop_en, HCLGE_MAC_1588_RX_B));
	dev_info(&hdev->pdev->dev, "config_mac_app_loop_en: %#x\n",
		 hnae3_get_bit(loop_en, HCLGE_MAC_APP_LP_B));
	dev_info(&hdev->pdev->dev, "config_mac_line_loop_en: %#x\n",
		 hnae3_get_bit(loop_en, HCLGE_MAC_LINE_LP_B));
	dev_info(&hdev->pdev->dev, "config_mac_fcs_tx_en: %#x\n",
		 hnae3_get_bit(loop_en, HCLGE_MAC_FCS_TX_B));
	dev_info(&hdev->pdev->dev, "config_mac_rx_oversize_truncate_en: %#x\n",
		 hnae3_get_bit(loop_en, HCLGE_MAC_RX_OVERSIZE_TRUNCATE_B));
	dev_info(&hdev->pdev->dev, "config_mac_rx_fcs_strip_en: %#x\n",
		 hnae3_get_bit(loop_en, HCLGE_MAC_RX_FCS_STRIP_B));
	dev_info(&hdev->pdev->dev, "config_mac_rx_fcs_en: %#x\n",
		 hnae3_get_bit(loop_en, HCLGE_MAC_RX_FCS_B));
	dev_info(&hdev->pdev->dev, "config_mac_tx_under_min_err_en: %#x\n",
		 hnae3_get_bit(loop_en, HCLGE_MAC_TX_UNDER_MIN_ERR_B));
	dev_info(&hdev->pdev->dev, "config_mac_tx_oversize_truncate_en: %#x\n",
		 hnae3_get_bit(loop_en, HCLGE_MAC_TX_OVERSIZE_TRUNCATE_B));
पूर्ण

अटल व्योम hclge_dbg_dump_mac_frame_size(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_config_max_frm_size_cmd *req;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_CONFIG_MAX_FRM_SIZE, true);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"failed to dump mac frame size, ret = %d\n", ret);
		वापस;
	पूर्ण

	req = (काष्ठा hclge_config_max_frm_size_cmd *)desc.data;

	dev_info(&hdev->pdev->dev, "max_frame_size: %u\n",
		 le16_to_cpu(req->max_frm_size));
	dev_info(&hdev->pdev->dev, "min_frame_size: %u\n", req->min_frm_size);
पूर्ण

अटल व्योम hclge_dbg_dump_mac_speed_duplex(काष्ठा hclge_dev *hdev)
अणु
#घोषणा HCLGE_MAC_SPEED_SHIFT	0
#घोषणा HCLGE_MAC_SPEED_MASK	GENMASK(5, 0)
#घोषणा HCLGE_MAC_DUPLEX_SHIFT	7

	काष्ठा hclge_config_mac_speed_dup_cmd *req;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_CONFIG_SPEED_DUP, true);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"failed to dump mac speed duplex, ret = %d\n", ret);
		वापस;
	पूर्ण

	req = (काष्ठा hclge_config_mac_speed_dup_cmd *)desc.data;

	dev_info(&hdev->pdev->dev, "speed: %#lx\n",
		 hnae3_get_field(req->speed_dup, HCLGE_MAC_SPEED_MASK,
				 HCLGE_MAC_SPEED_SHIFT));
	dev_info(&hdev->pdev->dev, "duplex: %#x\n",
		 hnae3_get_bit(req->speed_dup, HCLGE_MAC_DUPLEX_SHIFT));
पूर्ण

अटल व्योम hclge_dbg_dump_mac(काष्ठा hclge_dev *hdev)
अणु
	hclge_dbg_dump_mac_enable_status(hdev);

	hclge_dbg_dump_mac_frame_size(hdev);

	hclge_dbg_dump_mac_speed_duplex(hdev);
पूर्ण

अटल व्योम hclge_dbg_dump_dcb(काष्ठा hclge_dev *hdev, स्थिर अक्षर *cmd_buf)
अणु
	काष्ठा device *dev = &hdev->pdev->dev;
	काष्ठा hclge_dbg_biपंचांगap_cmd *biपंचांगap;
	क्रमागत hclge_opcode_type cmd;
	पूर्णांक rq_id, pri_id, qset_id;
	पूर्णांक port_id, nq_id, pg_id;
	काष्ठा hclge_desc desc[2];

	पूर्णांक cnt, ret;

	cnt = माला_पूछो(cmd_buf, "%i %i %i %i %i %i",
		     &port_id, &pri_id, &pg_id, &rq_id, &nq_id, &qset_id);
	अगर (cnt != 6) अणु
		dev_err(&hdev->pdev->dev,
			"dump dcb: bad command parameter, cnt=%d\n", cnt);
		वापस;
	पूर्ण

	cmd = HCLGE_OPC_QSET_DFX_STS;
	ret = hclge_dbg_cmd_send(hdev, desc, qset_id, 1, cmd);
	अगर (ret)
		जाओ err_dcb_cmd_send;

	biपंचांगap = (काष्ठा hclge_dbg_biपंचांगap_cmd *)&desc[0].data[1];
	dev_info(dev, "roce_qset_mask: 0x%x\n", biपंचांगap->bit0);
	dev_info(dev, "nic_qs_mask: 0x%x\n", biपंचांगap->bit1);
	dev_info(dev, "qs_shaping_pass: 0x%x\n", biपंचांगap->bit2);
	dev_info(dev, "qs_bp_sts: 0x%x\n", biपंचांगap->bit3);

	cmd = HCLGE_OPC_PRI_DFX_STS;
	ret = hclge_dbg_cmd_send(hdev, desc, pri_id, 1, cmd);
	अगर (ret)
		जाओ err_dcb_cmd_send;

	biपंचांगap = (काष्ठा hclge_dbg_biपंचांगap_cmd *)&desc[0].data[1];
	dev_info(dev, "pri_mask: 0x%x\n", biपंचांगap->bit0);
	dev_info(dev, "pri_cshaping_pass: 0x%x\n", biपंचांगap->bit1);
	dev_info(dev, "pri_pshaping_pass: 0x%x\n", biपंचांगap->bit2);

	cmd = HCLGE_OPC_PG_DFX_STS;
	ret = hclge_dbg_cmd_send(hdev, desc, pg_id, 1, cmd);
	अगर (ret)
		जाओ err_dcb_cmd_send;

	biपंचांगap = (काष्ठा hclge_dbg_biपंचांगap_cmd *)&desc[0].data[1];
	dev_info(dev, "pg_mask: 0x%x\n", biपंचांगap->bit0);
	dev_info(dev, "pg_cshaping_pass: 0x%x\n", biपंचांगap->bit1);
	dev_info(dev, "pg_pshaping_pass: 0x%x\n", biपंचांगap->bit2);

	cmd = HCLGE_OPC_PORT_DFX_STS;
	ret = hclge_dbg_cmd_send(hdev, desc, port_id, 1, cmd);
	अगर (ret)
		जाओ err_dcb_cmd_send;

	biपंचांगap = (काष्ठा hclge_dbg_biपंचांगap_cmd *)&desc[0].data[1];
	dev_info(dev, "port_mask: 0x%x\n", biपंचांगap->bit0);
	dev_info(dev, "port_shaping_pass: 0x%x\n", biपंचांगap->bit1);

	cmd = HCLGE_OPC_SCH_NQ_CNT;
	ret = hclge_dbg_cmd_send(hdev, desc, nq_id, 1, cmd);
	अगर (ret)
		जाओ err_dcb_cmd_send;

	dev_info(dev, "sch_nq_cnt: 0x%x\n", le32_to_cpu(desc[0].data[1]));

	cmd = HCLGE_OPC_SCH_RQ_CNT;
	ret = hclge_dbg_cmd_send(hdev, desc, nq_id, 1, cmd);
	अगर (ret)
		जाओ err_dcb_cmd_send;

	dev_info(dev, "sch_rq_cnt: 0x%x\n", le32_to_cpu(desc[0].data[1]));

	cmd = HCLGE_OPC_TM_INTERNAL_STS;
	ret = hclge_dbg_cmd_send(hdev, desc, 0, 2, cmd);
	अगर (ret)
		जाओ err_dcb_cmd_send;

	dev_info(dev, "pri_bp: 0x%x\n", le32_to_cpu(desc[0].data[1]));
	dev_info(dev, "fifo_dfx_info: 0x%x\n", le32_to_cpu(desc[0].data[2]));
	dev_info(dev, "sch_roce_fifo_afull_gap: 0x%x\n",
		 le32_to_cpu(desc[0].data[3]));
	dev_info(dev, "tx_private_waterline: 0x%x\n",
		 le32_to_cpu(desc[0].data[4]));
	dev_info(dev, "tm_bypass_en: 0x%x\n", le32_to_cpu(desc[0].data[5]));
	dev_info(dev, "SSU_TM_BYPASS_EN: 0x%x\n", le32_to_cpu(desc[1].data[0]));
	dev_info(dev, "SSU_RESERVE_CFG: 0x%x\n", le32_to_cpu(desc[1].data[1]));

	cmd = HCLGE_OPC_TM_INTERNAL_CNT;
	ret = hclge_dbg_cmd_send(hdev, desc, port_id, 1, cmd);
	अगर (ret)
		जाओ err_dcb_cmd_send;

	dev_info(dev, "SCH_NIC_NUM: 0x%x\n", le32_to_cpu(desc[0].data[1]));
	dev_info(dev, "SCH_ROCE_NUM: 0x%x\n", le32_to_cpu(desc[0].data[2]));

	cmd = HCLGE_OPC_TM_INTERNAL_STS_1;
	ret = hclge_dbg_cmd_send(hdev, desc, port_id, 1, cmd);
	अगर (ret)
		जाओ err_dcb_cmd_send;

	dev_info(dev, "TC_MAP_SEL: 0x%x\n", le32_to_cpu(desc[0].data[1]));
	dev_info(dev, "IGU_PFC_PRI_EN: 0x%x\n", le32_to_cpu(desc[0].data[2]));
	dev_info(dev, "MAC_PFC_PRI_EN: 0x%x\n", le32_to_cpu(desc[0].data[3]));
	dev_info(dev, "IGU_PRI_MAP_TC_CFG: 0x%x\n",
		 le32_to_cpu(desc[0].data[4]));
	dev_info(dev, "IGU_TX_PRI_MAP_TC_CFG: 0x%x\n",
		 le32_to_cpu(desc[0].data[5]));
	वापस;

err_dcb_cmd_send:
	dev_err(&hdev->pdev->dev,
		"failed to dump dcb dfx, cmd = %#x, ret = %d\n",
		cmd, ret);
पूर्ण

अटल व्योम hclge_dbg_dump_reg_cmd(काष्ठा hclge_dev *hdev, स्थिर अक्षर *cmd_buf)
अणु
	स्थिर काष्ठा hclge_dbg_reg_type_info *reg_info;
	bool has_dump = false;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(hclge_dbg_reg_info); i++) अणु
		reg_info = &hclge_dbg_reg_info[i];
		अगर (!म_भेदन(cmd_buf, reg_info->reg_type,
			     म_माप(reg_info->reg_type))) अणु
			hclge_dbg_dump_reg_common(hdev, reg_info, cmd_buf);
			has_dump = true;
		पूर्ण
	पूर्ण

	अगर (म_भेदन(cmd_buf, "mac", म_माप("mac")) == 0) अणु
		hclge_dbg_dump_mac(hdev);
		has_dump = true;
	पूर्ण

	अगर (म_भेदन(cmd_buf, "dcb", 3) == 0) अणु
		hclge_dbg_dump_dcb(hdev, &cmd_buf[माप("dcb")]);
		has_dump = true;
	पूर्ण

	अगर (!has_dump) अणु
		dev_info(&hdev->pdev->dev, "unknown command\n");
		वापस;
	पूर्ण
पूर्ण

अटल व्योम hclge_prपूर्णांक_tc_info(काष्ठा hclge_dev *hdev, bool flag, पूर्णांक index)
अणु
	अगर (flag)
		dev_info(&hdev->pdev->dev, "tc(%d): no sp mode weight: %u\n",
			 index, hdev->पंचांग_info.pg_info[0].tc_dwrr[index]);
	अन्यथा
		dev_info(&hdev->pdev->dev, "tc(%d): sp mode\n", index);
पूर्ण

अटल व्योम hclge_dbg_dump_tc(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_ets_tc_weight_cmd *ets_weight;
	काष्ठा hclge_desc desc;
	पूर्णांक i, ret;

	अगर (!hnae3_dev_dcb_supported(hdev)) अणु
		dev_info(&hdev->pdev->dev,
			 "Only DCB-supported dev supports tc\n");
		वापस;
	पूर्ण

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_ETS_TC_WEIGHT, true);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev, "dump tc fail, ret = %d\n", ret);
		वापस;
	पूर्ण

	ets_weight = (काष्ठा hclge_ets_tc_weight_cmd *)desc.data;

	dev_info(&hdev->pdev->dev, "dump tc: %u tc enabled\n",
		 hdev->पंचांग_info.num_tc);
	dev_info(&hdev->pdev->dev, "weight_offset: %u\n",
		 ets_weight->weight_offset);

	क्रम (i = 0; i < HNAE3_MAX_TC; i++)
		hclge_prपूर्णांक_tc_info(hdev, ets_weight->tc_weight[i], i);
पूर्ण

अटल व्योम hclge_dbg_dump_पंचांग_pg(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_port_shapping_cmd *port_shap_cfg_cmd;
	काष्ठा hclge_bp_to_qs_map_cmd *bp_to_qs_map_cmd;
	काष्ठा hclge_pg_shapping_cmd *pg_shap_cfg_cmd;
	क्रमागत hclge_opcode_type cmd;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	cmd = HCLGE_OPC_TM_PG_C_SHAPPING;
	hclge_cmd_setup_basic_desc(&desc, cmd, true);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		जाओ err_पंचांग_pg_cmd_send;

	pg_shap_cfg_cmd = (काष्ठा hclge_pg_shapping_cmd *)desc.data;
	dev_info(&hdev->pdev->dev, "PG_C pg_id: %u\n", pg_shap_cfg_cmd->pg_id);
	dev_info(&hdev->pdev->dev, "PG_C pg_shapping: 0x%x\n",
		 le32_to_cpu(pg_shap_cfg_cmd->pg_shapping_para));

	cmd = HCLGE_OPC_TM_PG_P_SHAPPING;
	hclge_cmd_setup_basic_desc(&desc, cmd, true);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		जाओ err_पंचांग_pg_cmd_send;

	pg_shap_cfg_cmd = (काष्ठा hclge_pg_shapping_cmd *)desc.data;
	dev_info(&hdev->pdev->dev, "PG_P pg_id: %u\n", pg_shap_cfg_cmd->pg_id);
	dev_info(&hdev->pdev->dev, "PG_P pg_shapping: 0x%x\n",
		 le32_to_cpu(pg_shap_cfg_cmd->pg_shapping_para));
	dev_info(&hdev->pdev->dev, "PG_P flag: %#x\n", pg_shap_cfg_cmd->flag);
	dev_info(&hdev->pdev->dev, "PG_P pg_rate: %u(Mbps)\n",
		 le32_to_cpu(pg_shap_cfg_cmd->pg_rate));

	cmd = HCLGE_OPC_TM_PORT_SHAPPING;
	hclge_cmd_setup_basic_desc(&desc, cmd, true);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		जाओ err_पंचांग_pg_cmd_send;

	port_shap_cfg_cmd = (काष्ठा hclge_port_shapping_cmd *)desc.data;
	dev_info(&hdev->pdev->dev, "PORT port_shapping: 0x%x\n",
		 le32_to_cpu(port_shap_cfg_cmd->port_shapping_para));
	dev_info(&hdev->pdev->dev, "PORT flag: %#x\n", port_shap_cfg_cmd->flag);
	dev_info(&hdev->pdev->dev, "PORT port_rate: %u(Mbps)\n",
		 le32_to_cpu(port_shap_cfg_cmd->port_rate));

	cmd = HCLGE_OPC_TM_PG_SCH_MODE_CFG;
	hclge_cmd_setup_basic_desc(&desc, cmd, true);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		जाओ err_पंचांग_pg_cmd_send;

	dev_info(&hdev->pdev->dev, "PG_SCH pg_id: %u\n",
		 le32_to_cpu(desc.data[0]));

	cmd = HCLGE_OPC_TM_PRI_SCH_MODE_CFG;
	hclge_cmd_setup_basic_desc(&desc, cmd, true);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		जाओ err_पंचांग_pg_cmd_send;

	dev_info(&hdev->pdev->dev, "PRI_SCH pri_id: %u\n",
		 le32_to_cpu(desc.data[0]));

	cmd = HCLGE_OPC_TM_QS_SCH_MODE_CFG;
	hclge_cmd_setup_basic_desc(&desc, cmd, true);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		जाओ err_पंचांग_pg_cmd_send;

	dev_info(&hdev->pdev->dev, "QS_SCH qs_id: %u\n",
		 le32_to_cpu(desc.data[0]));

	अगर (!hnae3_dev_dcb_supported(hdev)) अणु
		dev_info(&hdev->pdev->dev,
			 "Only DCB-supported dev supports tm mapping\n");
		वापस;
	पूर्ण

	cmd = HCLGE_OPC_TM_BP_TO_QSET_MAPPING;
	hclge_cmd_setup_basic_desc(&desc, cmd, true);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		जाओ err_पंचांग_pg_cmd_send;

	bp_to_qs_map_cmd = (काष्ठा hclge_bp_to_qs_map_cmd *)desc.data;
	dev_info(&hdev->pdev->dev, "BP_TO_QSET tc_id: %u\n",
		 bp_to_qs_map_cmd->tc_id);
	dev_info(&hdev->pdev->dev, "BP_TO_QSET qs_group_id: 0x%x\n",
		 bp_to_qs_map_cmd->qs_group_id);
	dev_info(&hdev->pdev->dev, "BP_TO_QSET qs_bit_map: 0x%x\n",
		 le32_to_cpu(bp_to_qs_map_cmd->qs_bit_map));
	वापस;

err_पंचांग_pg_cmd_send:
	dev_err(&hdev->pdev->dev, "dump tm_pg fail(0x%x), ret = %d\n",
		cmd, ret);
पूर्ण

अटल व्योम hclge_dbg_dump_पंचांग(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_priority_weight_cmd *priority_weight;
	काष्ठा hclge_pg_to_pri_link_cmd *pg_to_pri_map;
	काष्ठा hclge_qs_to_pri_link_cmd *qs_to_pri_map;
	काष्ठा hclge_nq_to_qs_link_cmd *nq_to_qs_map;
	काष्ठा hclge_pri_shapping_cmd *shap_cfg_cmd;
	काष्ठा hclge_pg_weight_cmd *pg_weight;
	काष्ठा hclge_qs_weight_cmd *qs_weight;
	क्रमागत hclge_opcode_type cmd;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	cmd = HCLGE_OPC_TM_PG_TO_PRI_LINK;
	hclge_cmd_setup_basic_desc(&desc, cmd, true);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		जाओ err_पंचांग_cmd_send;

	pg_to_pri_map = (काष्ठा hclge_pg_to_pri_link_cmd *)desc.data;
	dev_info(&hdev->pdev->dev, "dump tm\n");
	dev_info(&hdev->pdev->dev, "PG_TO_PRI gp_id: %u\n",
		 pg_to_pri_map->pg_id);
	dev_info(&hdev->pdev->dev, "PG_TO_PRI map: 0x%x\n",
		 pg_to_pri_map->pri_bit_map);

	cmd = HCLGE_OPC_TM_QS_TO_PRI_LINK;
	hclge_cmd_setup_basic_desc(&desc, cmd, true);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		जाओ err_पंचांग_cmd_send;

	qs_to_pri_map = (काष्ठा hclge_qs_to_pri_link_cmd *)desc.data;
	dev_info(&hdev->pdev->dev, "QS_TO_PRI qs_id: %u\n",
		 le16_to_cpu(qs_to_pri_map->qs_id));
	dev_info(&hdev->pdev->dev, "QS_TO_PRI priority: %u\n",
		 qs_to_pri_map->priority);
	dev_info(&hdev->pdev->dev, "QS_TO_PRI link_vld: %u\n",
		 qs_to_pri_map->link_vld);

	cmd = HCLGE_OPC_TM_NQ_TO_QS_LINK;
	hclge_cmd_setup_basic_desc(&desc, cmd, true);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		जाओ err_पंचांग_cmd_send;

	nq_to_qs_map = (काष्ठा hclge_nq_to_qs_link_cmd *)desc.data;
	dev_info(&hdev->pdev->dev, "NQ_TO_QS nq_id: %u\n",
		 le16_to_cpu(nq_to_qs_map->nq_id));
	dev_info(&hdev->pdev->dev, "NQ_TO_QS qset_id: 0x%x\n",
		 le16_to_cpu(nq_to_qs_map->qset_id));

	cmd = HCLGE_OPC_TM_PG_WEIGHT;
	hclge_cmd_setup_basic_desc(&desc, cmd, true);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		जाओ err_पंचांग_cmd_send;

	pg_weight = (काष्ठा hclge_pg_weight_cmd *)desc.data;
	dev_info(&hdev->pdev->dev, "PG pg_id: %u\n", pg_weight->pg_id);
	dev_info(&hdev->pdev->dev, "PG dwrr: %u\n", pg_weight->dwrr);

	cmd = HCLGE_OPC_TM_QS_WEIGHT;
	hclge_cmd_setup_basic_desc(&desc, cmd, true);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		जाओ err_पंचांग_cmd_send;

	qs_weight = (काष्ठा hclge_qs_weight_cmd *)desc.data;
	dev_info(&hdev->pdev->dev, "QS qs_id: %u\n",
		 le16_to_cpu(qs_weight->qs_id));
	dev_info(&hdev->pdev->dev, "QS dwrr: %u\n", qs_weight->dwrr);

	cmd = HCLGE_OPC_TM_PRI_WEIGHT;
	hclge_cmd_setup_basic_desc(&desc, cmd, true);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		जाओ err_पंचांग_cmd_send;

	priority_weight = (काष्ठा hclge_priority_weight_cmd *)desc.data;
	dev_info(&hdev->pdev->dev, "PRI pri_id: %u\n", priority_weight->pri_id);
	dev_info(&hdev->pdev->dev, "PRI dwrr: %u\n", priority_weight->dwrr);

	cmd = HCLGE_OPC_TM_PRI_C_SHAPPING;
	hclge_cmd_setup_basic_desc(&desc, cmd, true);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		जाओ err_पंचांग_cmd_send;

	shap_cfg_cmd = (काष्ठा hclge_pri_shapping_cmd *)desc.data;
	dev_info(&hdev->pdev->dev, "PRI_C pri_id: %u\n", shap_cfg_cmd->pri_id);
	dev_info(&hdev->pdev->dev, "PRI_C pri_shapping: 0x%x\n",
		 le32_to_cpu(shap_cfg_cmd->pri_shapping_para));
	dev_info(&hdev->pdev->dev, "PRI_C flag: %#x\n", shap_cfg_cmd->flag);
	dev_info(&hdev->pdev->dev, "PRI_C pri_rate: %u(Mbps)\n",
		 le32_to_cpu(shap_cfg_cmd->pri_rate));

	cmd = HCLGE_OPC_TM_PRI_P_SHAPPING;
	hclge_cmd_setup_basic_desc(&desc, cmd, true);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		जाओ err_पंचांग_cmd_send;

	shap_cfg_cmd = (काष्ठा hclge_pri_shapping_cmd *)desc.data;
	dev_info(&hdev->pdev->dev, "PRI_P pri_id: %u\n", shap_cfg_cmd->pri_id);
	dev_info(&hdev->pdev->dev, "PRI_P pri_shapping: 0x%x\n",
		 le32_to_cpu(shap_cfg_cmd->pri_shapping_para));
	dev_info(&hdev->pdev->dev, "PRI_P flag: %#x\n", shap_cfg_cmd->flag);
	dev_info(&hdev->pdev->dev, "PRI_P pri_rate: %u(Mbps)\n",
		 le32_to_cpu(shap_cfg_cmd->pri_rate));

	hclge_dbg_dump_पंचांग_pg(hdev);

	वापस;

err_पंचांग_cmd_send:
	dev_err(&hdev->pdev->dev, "dump tm fail(0x%x), ret = %d\n",
		cmd, ret);
पूर्ण

अटल व्योम hclge_dbg_dump_पंचांग_map(काष्ठा hclge_dev *hdev,
				  स्थिर अक्षर *cmd_buf)
अणु
	काष्ठा hclge_bp_to_qs_map_cmd *bp_to_qs_map_cmd;
	काष्ठा hclge_nq_to_qs_link_cmd *nq_to_qs_map;
	u32 qset_mapping[HCLGE_BP_EXT_GRP_NUM];
	काष्ठा hclge_qs_to_pri_link_cmd *map;
	काष्ठा hclge_tqp_tx_queue_tc_cmd *tc;
	u16 group_id, queue_id, qset_id;
	क्रमागत hclge_opcode_type cmd;
	u8 grp_num, pri_id, tc_id;
	काष्ठा hclge_desc desc;
	u16 qs_id_l;
	u16 qs_id_h;
	पूर्णांक ret;
	u32 i;

	ret = kstrtou16(cmd_buf, 0, &queue_id);
	queue_id = (ret != 0) ? 0 : queue_id;

	cmd = HCLGE_OPC_TM_NQ_TO_QS_LINK;
	nq_to_qs_map = (काष्ठा hclge_nq_to_qs_link_cmd *)desc.data;
	hclge_cmd_setup_basic_desc(&desc, cmd, true);
	nq_to_qs_map->nq_id = cpu_to_le16(queue_id);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		जाओ err_पंचांग_map_cmd_send;
	qset_id = le16_to_cpu(nq_to_qs_map->qset_id);

	/* convert qset_id to the following क्रमmat, drop the vld bit
	 *            | qs_id_h | vld | qs_id_l |
	 * qset_id:   | 15 ~ 11 |  10 |  9 ~ 0  |
	 *             \         \   /         /
	 *              \         \ /         /
	 * qset_id: | 15 | 14 ~ 10 |  9 ~ 0  |
	 */
	qs_id_l = hnae3_get_field(qset_id, HCLGE_TM_QS_ID_L_MSK,
				  HCLGE_TM_QS_ID_L_S);
	qs_id_h = hnae3_get_field(qset_id, HCLGE_TM_QS_ID_H_EXT_MSK,
				  HCLGE_TM_QS_ID_H_EXT_S);
	qset_id = 0;
	hnae3_set_field(qset_id, HCLGE_TM_QS_ID_L_MSK, HCLGE_TM_QS_ID_L_S,
			qs_id_l);
	hnae3_set_field(qset_id, HCLGE_TM_QS_ID_H_MSK, HCLGE_TM_QS_ID_H_S,
			qs_id_h);

	cmd = HCLGE_OPC_TM_QS_TO_PRI_LINK;
	map = (काष्ठा hclge_qs_to_pri_link_cmd *)desc.data;
	hclge_cmd_setup_basic_desc(&desc, cmd, true);
	map->qs_id = cpu_to_le16(qset_id);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		जाओ err_पंचांग_map_cmd_send;
	pri_id = map->priority;

	cmd = HCLGE_OPC_TQP_TX_QUEUE_TC;
	tc = (काष्ठा hclge_tqp_tx_queue_tc_cmd *)desc.data;
	hclge_cmd_setup_basic_desc(&desc, cmd, true);
	tc->queue_id = cpu_to_le16(queue_id);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		जाओ err_पंचांग_map_cmd_send;
	tc_id = tc->tc_id & 0x7;

	dev_info(&hdev->pdev->dev, "queue_id | qset_id | pri_id | tc_id\n");
	dev_info(&hdev->pdev->dev, "%04u     | %04u    | %02u     | %02u\n",
		 queue_id, qset_id, pri_id, tc_id);

	अगर (!hnae3_dev_dcb_supported(hdev)) अणु
		dev_info(&hdev->pdev->dev,
			 "Only DCB-supported dev supports tm mapping\n");
		वापस;
	पूर्ण

	grp_num = hdev->num_tqps <= HCLGE_TQP_MAX_SIZE_DEV_V2 ?
		  HCLGE_BP_GRP_NUM : HCLGE_BP_EXT_GRP_NUM;
	cmd = HCLGE_OPC_TM_BP_TO_QSET_MAPPING;
	bp_to_qs_map_cmd = (काष्ठा hclge_bp_to_qs_map_cmd *)desc.data;
	क्रम (group_id = 0; group_id < grp_num; group_id++) अणु
		hclge_cmd_setup_basic_desc(&desc, cmd, true);
		bp_to_qs_map_cmd->tc_id = tc_id;
		bp_to_qs_map_cmd->qs_group_id = group_id;
		ret = hclge_cmd_send(&hdev->hw, &desc, 1);
		अगर (ret)
			जाओ err_पंचांग_map_cmd_send;

		qset_mapping[group_id] =
			le32_to_cpu(bp_to_qs_map_cmd->qs_bit_map);
	पूर्ण

	dev_info(&hdev->pdev->dev, "index | tm bp qset maping:\n");

	i = 0;
	क्रम (group_id = 0; group_id < grp_num / 8; group_id++) अणु
		dev_info(&hdev->pdev->dev,
			 "%04d  | %08x:%08x:%08x:%08x:%08x:%08x:%08x:%08x\n",
			 group_id * 256, qset_mapping[(u32)(i + 7)],
			 qset_mapping[(u32)(i + 6)], qset_mapping[(u32)(i + 5)],
			 qset_mapping[(u32)(i + 4)], qset_mapping[(u32)(i + 3)],
			 qset_mapping[(u32)(i + 2)], qset_mapping[(u32)(i + 1)],
			 qset_mapping[i]);
		i += 8;
	पूर्ण

	वापस;

err_पंचांग_map_cmd_send:
	dev_err(&hdev->pdev->dev, "dump tqp map fail(0x%x), ret = %d\n",
		cmd, ret);
पूर्ण

अटल पूर्णांक hclge_dbg_dump_पंचांग_nodes(काष्ठा hclge_dev *hdev, अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा hclge_पंचांग_nodes_cmd *nodes;
	काष्ठा hclge_desc desc;
	पूर्णांक pos = 0;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_TM_NODES, true);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"failed to dump tm nodes, ret = %d\n", ret);
		वापस ret;
	पूर्ण

	nodes = (काष्ठा hclge_पंचांग_nodes_cmd *)desc.data;

	pos += scnम_लिखो(buf + pos, len - pos, "       BASE_ID  MAX_NUM\n");
	pos += scnम_लिखो(buf + pos, len - pos, "PG      %4u      %4u\n",
			 nodes->pg_base_id, nodes->pg_num);
	pos += scnम_लिखो(buf + pos, len - pos, "PRI     %4u      %4u\n",
			 nodes->pri_base_id, nodes->pri_num);
	pos += scnम_लिखो(buf + pos, len - pos, "QSET    %4u      %4u\n",
			 le16_to_cpu(nodes->qset_base_id),
			 le16_to_cpu(nodes->qset_num));
	pos += scnम_लिखो(buf + pos, len - pos, "QUEUE   %4u      %4u\n",
			 le16_to_cpu(nodes->queue_base_id),
			 le16_to_cpu(nodes->queue_num));

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_dbg_dump_पंचांग_pri(काष्ठा hclge_dev *hdev, अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा hclge_pri_shaper_para c_shaper_para;
	काष्ठा hclge_pri_shaper_para p_shaper_para;
	u8 pri_num, sch_mode, weight;
	अक्षर *sch_mode_str;
	पूर्णांक pos = 0;
	पूर्णांक ret;
	u8 i;

	ret = hclge_पंचांग_get_pri_num(hdev, &pri_num);
	अगर (ret)
		वापस ret;

	pos += scnम_लिखो(buf + pos, len - pos,
			 "ID    MODE  DWRR  C_IR_B  C_IR_U  C_IR_S  C_BS_B  ");
	pos += scnम_लिखो(buf + pos, len - pos,
			 "C_BS_S  C_FLAG  C_RATE(Mbps)  P_IR_B  P_IR_U  ");
	pos += scnम_लिखो(buf + pos, len - pos,
			 "P_IR_S  P_BS_B  P_BS_S  P_FLAG  P_RATE(Mbps)\n");

	क्रम (i = 0; i < pri_num; i++) अणु
		ret = hclge_पंचांग_get_pri_sch_mode(hdev, i, &sch_mode);
		अगर (ret)
			वापस ret;

		ret = hclge_पंचांग_get_pri_weight(hdev, i, &weight);
		अगर (ret)
			वापस ret;

		ret = hclge_पंचांग_get_pri_shaper(hdev, i,
					      HCLGE_OPC_TM_PRI_C_SHAPPING,
					      &c_shaper_para);
		अगर (ret)
			वापस ret;

		ret = hclge_पंचांग_get_pri_shaper(hdev, i,
					      HCLGE_OPC_TM_PRI_P_SHAPPING,
					      &p_shaper_para);
		अगर (ret)
			वापस ret;

		sch_mode_str = sch_mode & HCLGE_TM_TX_SCHD_DWRR_MSK ? "dwrr" :
			       "sp";

		pos += scnम_लिखो(buf + pos, len - pos,
				 "%04u  %4s  %3u   %3u     %3u     %3u     ",
				 i, sch_mode_str, weight, c_shaper_para.ir_b,
				 c_shaper_para.ir_u, c_shaper_para.ir_s);
		pos += scnम_लिखो(buf + pos, len - pos,
				 "%3u     %3u       %1u     %6u        ",
				 c_shaper_para.bs_b, c_shaper_para.bs_s,
				 c_shaper_para.flag, c_shaper_para.rate);
		pos += scnम_लिखो(buf + pos, len - pos,
				 "%3u     %3u     %3u     %3u     %3u       ",
				 p_shaper_para.ir_b, p_shaper_para.ir_u,
				 p_shaper_para.ir_s, p_shaper_para.bs_b,
				 p_shaper_para.bs_s);
		pos += scnम_लिखो(buf + pos, len - pos, "%1u     %6u\n",
				 p_shaper_para.flag, p_shaper_para.rate);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_dbg_dump_पंचांग_qset(काष्ठा hclge_dev *hdev, अक्षर *buf, पूर्णांक len)
अणु
	u8 priority, link_vld, sch_mode, weight;
	अक्षर *sch_mode_str;
	पूर्णांक ret, pos;
	u16 qset_num;
	u16 i;

	ret = hclge_पंचांग_get_qset_num(hdev, &qset_num);
	अगर (ret)
		वापस ret;

	pos = scnम_लिखो(buf, len, "ID    MAP_PRI  LINK_VLD  MODE  DWRR\n");

	क्रम (i = 0; i < qset_num; i++) अणु
		ret = hclge_पंचांग_get_qset_map_pri(hdev, i, &priority, &link_vld);
		अगर (ret)
			वापस ret;

		ret = hclge_पंचांग_get_qset_sch_mode(hdev, i, &sch_mode);
		अगर (ret)
			वापस ret;

		ret = hclge_पंचांग_get_qset_weight(hdev, i, &weight);
		अगर (ret)
			वापस ret;

		sch_mode_str = sch_mode & HCLGE_TM_TX_SCHD_DWRR_MSK ? "dwrr" :
			       "sp";
		pos += scnम_लिखो(buf + pos, len - pos,
				 "%04u  %4u        %1u      %4s  %3u\n",
				 i, priority, link_vld, sch_mode_str, weight);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hclge_dbg_dump_qos_छोड़ो_cfg(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_cfg_छोड़ो_param_cmd *छोड़ो_param;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_CFG_MAC_PARA, true);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev, "dump checksum fail, ret = %d\n",
			ret);
		वापस;
	पूर्ण

	छोड़ो_param = (काष्ठा hclge_cfg_छोड़ो_param_cmd *)desc.data;
	dev_info(&hdev->pdev->dev, "dump qos pause cfg\n");
	dev_info(&hdev->pdev->dev, "pause_trans_gap: 0x%x\n",
		 छोड़ो_param->छोड़ो_trans_gap);
	dev_info(&hdev->pdev->dev, "pause_trans_time: 0x%x\n",
		 le16_to_cpu(छोड़ो_param->छोड़ो_trans_समय));
पूर्ण

अटल व्योम hclge_dbg_dump_qos_pri_map(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_qos_pri_map_cmd *pri_map;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_PRI_TO_TC_MAPPING, true);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"dump qos pri map fail, ret = %d\n", ret);
		वापस;
	पूर्ण

	pri_map = (काष्ठा hclge_qos_pri_map_cmd *)desc.data;
	dev_info(&hdev->pdev->dev, "dump qos pri map\n");
	dev_info(&hdev->pdev->dev, "vlan_to_pri: 0x%x\n", pri_map->vlan_pri);
	dev_info(&hdev->pdev->dev, "pri_0_to_tc: 0x%x\n", pri_map->pri0_tc);
	dev_info(&hdev->pdev->dev, "pri_1_to_tc: 0x%x\n", pri_map->pri1_tc);
	dev_info(&hdev->pdev->dev, "pri_2_to_tc: 0x%x\n", pri_map->pri2_tc);
	dev_info(&hdev->pdev->dev, "pri_3_to_tc: 0x%x\n", pri_map->pri3_tc);
	dev_info(&hdev->pdev->dev, "pri_4_to_tc: 0x%x\n", pri_map->pri4_tc);
	dev_info(&hdev->pdev->dev, "pri_5_to_tc: 0x%x\n", pri_map->pri5_tc);
	dev_info(&hdev->pdev->dev, "pri_6_to_tc: 0x%x\n", pri_map->pri6_tc);
	dev_info(&hdev->pdev->dev, "pri_7_to_tc: 0x%x\n", pri_map->pri7_tc);
पूर्ण

अटल पूर्णांक hclge_dbg_dump_tx_buf_cfg(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_tx_buff_alloc_cmd *tx_buf_cmd;
	काष्ठा hclge_desc desc;
	पूर्णांक i, ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_TX_BUFF_ALLOC, true);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		वापस ret;

	dev_info(&hdev->pdev->dev, "dump qos buf cfg\n");
	tx_buf_cmd = (काष्ठा hclge_tx_buff_alloc_cmd *)desc.data;
	क्रम (i = 0; i < HCLGE_MAX_TC_NUM; i++)
		dev_info(&hdev->pdev->dev, "tx_packet_buf_tc_%d: 0x%x\n", i,
			 le16_to_cpu(tx_buf_cmd->tx_pkt_buff[i]));

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_dbg_dump_rx_priv_buf_cfg(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_rx_priv_buff_cmd *rx_buf_cmd;
	काष्ठा hclge_desc desc;
	पूर्णांक i, ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_RX_PRIV_BUFF_ALLOC, true);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		वापस ret;

	dev_info(&hdev->pdev->dev, "\n");
	rx_buf_cmd = (काष्ठा hclge_rx_priv_buff_cmd *)desc.data;
	क्रम (i = 0; i < HCLGE_MAX_TC_NUM; i++)
		dev_info(&hdev->pdev->dev, "rx_packet_buf_tc_%d: 0x%x\n", i,
			 le16_to_cpu(rx_buf_cmd->buf_num[i]));

	dev_info(&hdev->pdev->dev, "rx_share_buf: 0x%x\n",
		 le16_to_cpu(rx_buf_cmd->shared_buf));

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_dbg_dump_rx_common_wl_cfg(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_rx_com_wl *rx_com_wl;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_RX_COM_WL_ALLOC, true);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		वापस ret;

	rx_com_wl = (काष्ठा hclge_rx_com_wl *)desc.data;
	dev_info(&hdev->pdev->dev, "\n");
	dev_info(&hdev->pdev->dev, "rx_com_wl: high: 0x%x, low: 0x%x\n",
		 le16_to_cpu(rx_com_wl->com_wl.high),
		 le16_to_cpu(rx_com_wl->com_wl.low));

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_dbg_dump_rx_global_pkt_cnt(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_rx_com_wl *rx_packet_cnt;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_RX_GBL_PKT_CNT, true);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		वापस ret;

	rx_packet_cnt = (काष्ठा hclge_rx_com_wl *)desc.data;
	dev_info(&hdev->pdev->dev,
		 "rx_global_packet_cnt: high: 0x%x, low: 0x%x\n",
		 le16_to_cpu(rx_packet_cnt->com_wl.high),
		 le16_to_cpu(rx_packet_cnt->com_wl.low));

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_dbg_dump_rx_priv_wl_buf_cfg(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_rx_priv_wl_buf *rx_priv_wl;
	काष्ठा hclge_desc desc[2];
	पूर्णांक i, ret;

	hclge_cmd_setup_basic_desc(&desc[0], HCLGE_OPC_RX_PRIV_WL_ALLOC, true);
	desc[0].flag |= cpu_to_le16(HCLGE_CMD_FLAG_NEXT);
	hclge_cmd_setup_basic_desc(&desc[1], HCLGE_OPC_RX_PRIV_WL_ALLOC, true);
	ret = hclge_cmd_send(&hdev->hw, desc, 2);
	अगर (ret)
		वापस ret;

	rx_priv_wl = (काष्ठा hclge_rx_priv_wl_buf *)desc[0].data;
	क्रम (i = 0; i < HCLGE_TC_NUM_ONE_DESC; i++)
		dev_info(&hdev->pdev->dev,
			 "rx_priv_wl_tc_%d: high: 0x%x, low: 0x%x\n", i,
			 le16_to_cpu(rx_priv_wl->tc_wl[i].high),
			 le16_to_cpu(rx_priv_wl->tc_wl[i].low));

	rx_priv_wl = (काष्ठा hclge_rx_priv_wl_buf *)desc[1].data;
	क्रम (i = 0; i < HCLGE_TC_NUM_ONE_DESC; i++)
		dev_info(&hdev->pdev->dev,
			 "rx_priv_wl_tc_%d: high: 0x%x, low: 0x%x\n",
			 i + HCLGE_TC_NUM_ONE_DESC,
			 le16_to_cpu(rx_priv_wl->tc_wl[i].high),
			 le16_to_cpu(rx_priv_wl->tc_wl[i].low));

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_dbg_dump_rx_common_threshold_cfg(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_rx_com_thrd *rx_com_thrd;
	काष्ठा hclge_desc desc[2];
	पूर्णांक i, ret;

	hclge_cmd_setup_basic_desc(&desc[0], HCLGE_OPC_RX_COM_THRD_ALLOC, true);
	desc[0].flag |= cpu_to_le16(HCLGE_CMD_FLAG_NEXT);
	hclge_cmd_setup_basic_desc(&desc[1], HCLGE_OPC_RX_COM_THRD_ALLOC, true);
	ret = hclge_cmd_send(&hdev->hw, desc, 2);
	अगर (ret)
		वापस ret;

	dev_info(&hdev->pdev->dev, "\n");
	rx_com_thrd = (काष्ठा hclge_rx_com_thrd *)desc[0].data;
	क्रम (i = 0; i < HCLGE_TC_NUM_ONE_DESC; i++)
		dev_info(&hdev->pdev->dev,
			 "rx_com_thrd_tc_%d: high: 0x%x, low: 0x%x\n", i,
			 le16_to_cpu(rx_com_thrd->com_thrd[i].high),
			 le16_to_cpu(rx_com_thrd->com_thrd[i].low));

	rx_com_thrd = (काष्ठा hclge_rx_com_thrd *)desc[1].data;
	क्रम (i = 0; i < HCLGE_TC_NUM_ONE_DESC; i++)
		dev_info(&hdev->pdev->dev,
			 "rx_com_thrd_tc_%d: high: 0x%x, low: 0x%x\n",
			 i + HCLGE_TC_NUM_ONE_DESC,
			 le16_to_cpu(rx_com_thrd->com_thrd[i].high),
			 le16_to_cpu(rx_com_thrd->com_thrd[i].low));

	वापस 0;
पूर्ण

अटल व्योम hclge_dbg_dump_qos_buf_cfg(काष्ठा hclge_dev *hdev)
अणु
	क्रमागत hclge_opcode_type cmd;
	पूर्णांक ret;

	cmd = HCLGE_OPC_TX_BUFF_ALLOC;
	ret = hclge_dbg_dump_tx_buf_cfg(hdev);
	अगर (ret)
		जाओ err_qos_cmd_send;

	cmd = HCLGE_OPC_RX_PRIV_BUFF_ALLOC;
	ret = hclge_dbg_dump_rx_priv_buf_cfg(hdev);
	अगर (ret)
		जाओ err_qos_cmd_send;

	cmd = HCLGE_OPC_RX_COM_WL_ALLOC;
	ret = hclge_dbg_dump_rx_common_wl_cfg(hdev);
	अगर (ret)
		जाओ err_qos_cmd_send;

	cmd = HCLGE_OPC_RX_GBL_PKT_CNT;
	ret = hclge_dbg_dump_rx_global_pkt_cnt(hdev);
	अगर (ret)
		जाओ err_qos_cmd_send;

	dev_info(&hdev->pdev->dev, "\n");
	अगर (!hnae3_dev_dcb_supported(hdev)) अणु
		dev_info(&hdev->pdev->dev,
			 "Only DCB-supported dev supports rx priv wl\n");
		वापस;
	पूर्ण

	cmd = HCLGE_OPC_RX_PRIV_WL_ALLOC;
	ret = hclge_dbg_dump_rx_priv_wl_buf_cfg(hdev);
	अगर (ret)
		जाओ err_qos_cmd_send;

	cmd = HCLGE_OPC_RX_COM_THRD_ALLOC;
	ret = hclge_dbg_dump_rx_common_threshold_cfg(hdev);
	अगर (ret)
		जाओ err_qos_cmd_send;

	वापस;

err_qos_cmd_send:
	dev_err(&hdev->pdev->dev,
		"dump qos buf cfg fail(0x%x), ret = %d\n", cmd, ret);
पूर्ण

अटल व्योम hclge_dbg_dump_mng_table(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_mac_ethertype_idx_rd_cmd *req0;
	अक्षर म_लिखो_buf[HCLGE_DBG_BUF_LEN];
	काष्ठा hclge_desc desc;
	u32 msg_egress_port;
	पूर्णांक ret, i;

	dev_info(&hdev->pdev->dev, "mng tab:\n");
	स_रखो(म_लिखो_buf, 0, HCLGE_DBG_BUF_LEN);
	म_जोड़न(म_लिखो_buf,
		"entry|mac_addr         |mask|ether|mask|vlan|mask",
		HCLGE_DBG_BUF_LEN - 1);
	म_जोड़न(म_लिखो_buf + म_माप(म_लिखो_buf),
		"|i_map|i_dir|e_type|pf_id|vf_id|q_id|drop\n",
		HCLGE_DBG_BUF_LEN - म_माप(म_लिखो_buf) - 1);

	dev_info(&hdev->pdev->dev, "%s", म_लिखो_buf);

	क्रम (i = 0; i < HCLGE_DBG_MNG_TBL_MAX; i++) अणु
		hclge_cmd_setup_basic_desc(&desc, HCLGE_MAC_ETHERTYPE_IDX_RD,
					   true);
		req0 = (काष्ठा hclge_mac_ethertype_idx_rd_cmd *)&desc.data;
		req0->index = cpu_to_le16(i);

		ret = hclge_cmd_send(&hdev->hw, &desc, 1);
		अगर (ret) अणु
			dev_err(&hdev->pdev->dev,
				"call hclge_cmd_send fail, ret = %d\n", ret);
			वापस;
		पूर्ण

		अगर (!req0->resp_code)
			जारी;

		स_रखो(म_लिखो_buf, 0, HCLGE_DBG_BUF_LEN);
		snम_लिखो(म_लिखो_buf, HCLGE_DBG_BUF_LEN,
			 "%02u   |%02x:%02x:%02x:%02x:%02x:%02x|",
			 le16_to_cpu(req0->index),
			 req0->mac_addr[0], req0->mac_addr[1],
			 req0->mac_addr[2], req0->mac_addr[3],
			 req0->mac_addr[4], req0->mac_addr[5]);

		snम_लिखो(म_लिखो_buf + म_माप(म_लिखो_buf),
			 HCLGE_DBG_BUF_LEN - म_माप(म_लिखो_buf),
			 "%x   |%04x |%x   |%04x|%x   |%02x   |%02x   |",
			 !!(req0->flags & HCLGE_DBG_MNG_MAC_MASK_B),
			 le16_to_cpu(req0->ethter_type),
			 !!(req0->flags & HCLGE_DBG_MNG_ETHER_MASK_B),
			 le16_to_cpu(req0->vlan_tag) & HCLGE_DBG_MNG_VLAN_TAG,
			 !!(req0->flags & HCLGE_DBG_MNG_VLAN_MASK_B),
			 req0->i_port_biपंचांगap, req0->i_port_direction);

		msg_egress_port = le16_to_cpu(req0->egress_port);
		snम_लिखो(म_लिखो_buf + म_माप(म_लिखो_buf),
			 HCLGE_DBG_BUF_LEN - म_माप(म_लिखो_buf),
			 "%x     |%x    |%02x   |%04x|%x\n",
			 !!(msg_egress_port & HCLGE_DBG_MNG_E_TYPE_B),
			 msg_egress_port & HCLGE_DBG_MNG_PF_ID,
			 (msg_egress_port >> 3) & HCLGE_DBG_MNG_VF_ID,
			 le16_to_cpu(req0->egress_queue),
			 !!(msg_egress_port & HCLGE_DBG_MNG_DROP_B));

		dev_info(&hdev->pdev->dev, "%s", म_लिखो_buf);
	पूर्ण
पूर्ण

अटल पूर्णांक hclge_dbg_fd_tcam_पढ़ो(काष्ठा hclge_dev *hdev, u8 stage,
				  bool sel_x, u32 loc)
अणु
	काष्ठा hclge_fd_tcam_config_1_cmd *req1;
	काष्ठा hclge_fd_tcam_config_2_cmd *req2;
	काष्ठा hclge_fd_tcam_config_3_cmd *req3;
	काष्ठा hclge_desc desc[3];
	पूर्णांक ret, i;
	u32 *req;

	hclge_cmd_setup_basic_desc(&desc[0], HCLGE_OPC_FD_TCAM_OP, true);
	desc[0].flag |= cpu_to_le16(HCLGE_CMD_FLAG_NEXT);
	hclge_cmd_setup_basic_desc(&desc[1], HCLGE_OPC_FD_TCAM_OP, true);
	desc[1].flag |= cpu_to_le16(HCLGE_CMD_FLAG_NEXT);
	hclge_cmd_setup_basic_desc(&desc[2], HCLGE_OPC_FD_TCAM_OP, true);

	req1 = (काष्ठा hclge_fd_tcam_config_1_cmd *)desc[0].data;
	req2 = (काष्ठा hclge_fd_tcam_config_2_cmd *)desc[1].data;
	req3 = (काष्ठा hclge_fd_tcam_config_3_cmd *)desc[2].data;

	req1->stage  = stage;
	req1->xy_sel = sel_x ? 1 : 0;
	req1->index  = cpu_to_le32(loc);

	ret = hclge_cmd_send(&hdev->hw, desc, 3);
	अगर (ret)
		वापस ret;

	dev_info(&hdev->pdev->dev, " read result tcam key %s(%u):\n",
		 sel_x ? "x" : "y", loc);

	/* tcam_data0 ~ tcam_data1 */
	req = (u32 *)req1->tcam_data;
	क्रम (i = 0; i < 2; i++)
		dev_info(&hdev->pdev->dev, "%08x\n", *req++);

	/* tcam_data2 ~ tcam_data7 */
	req = (u32 *)req2->tcam_data;
	क्रम (i = 0; i < 6; i++)
		dev_info(&hdev->pdev->dev, "%08x\n", *req++);

	/* tcam_data8 ~ tcam_data12 */
	req = (u32 *)req3->tcam_data;
	क्रम (i = 0; i < 5; i++)
		dev_info(&hdev->pdev->dev, "%08x\n", *req++);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_dbg_get_rules_location(काष्ठा hclge_dev *hdev, u16 *rule_locs)
अणु
	काष्ठा hclge_fd_rule *rule;
	काष्ठा hlist_node *node;
	पूर्णांक cnt = 0;

	spin_lock_bh(&hdev->fd_rule_lock);
	hlist_क्रम_each_entry_safe(rule, node, &hdev->fd_rule_list, rule_node) अणु
		rule_locs[cnt] = rule->location;
		cnt++;
	पूर्ण
	spin_unlock_bh(&hdev->fd_rule_lock);

	अगर (cnt != hdev->hclge_fd_rule_num)
		वापस -EINVAL;

	वापस cnt;
पूर्ण

अटल व्योम hclge_dbg_fd_tcam(काष्ठा hclge_dev *hdev)
अणु
	पूर्णांक i, ret, rule_cnt;
	u16 *rule_locs;

	अगर (!hnae3_dev_fd_supported(hdev)) अणु
		dev_err(&hdev->pdev->dev,
			"Only FD-supported dev supports dump fd tcam\n");
		वापस;
	पूर्ण

	अगर (!hdev->hclge_fd_rule_num ||
	    !hdev->fd_cfg.rule_num[HCLGE_FD_STAGE_1])
		वापस;

	rule_locs = kसुस्मृति(hdev->fd_cfg.rule_num[HCLGE_FD_STAGE_1],
			    माप(u16), GFP_KERNEL);
	अगर (!rule_locs)
		वापस;

	rule_cnt = hclge_dbg_get_rules_location(hdev, rule_locs);
	अगर (rule_cnt <= 0) अणु
		dev_err(&hdev->pdev->dev,
			"failed to get rule number, ret = %d\n", rule_cnt);
		kमुक्त(rule_locs);
		वापस;
	पूर्ण

	क्रम (i = 0; i < rule_cnt; i++) अणु
		ret = hclge_dbg_fd_tcam_पढ़ो(hdev, 0, true, rule_locs[i]);
		अगर (ret) अणु
			dev_err(&hdev->pdev->dev,
				"failed to get fd tcam key x, ret = %d\n", ret);
			kमुक्त(rule_locs);
			वापस;
		पूर्ण

		ret = hclge_dbg_fd_tcam_पढ़ो(hdev, 0, false, rule_locs[i]);
		अगर (ret) अणु
			dev_err(&hdev->pdev->dev,
				"failed to get fd tcam key y, ret = %d\n", ret);
			kमुक्त(rule_locs);
			वापस;
		पूर्ण
	पूर्ण

	kमुक्त(rule_locs);
पूर्ण

व्योम hclge_dbg_dump_rst_info(काष्ठा hclge_dev *hdev)
अणु
	dev_info(&hdev->pdev->dev, "PF reset count: %u\n",
		 hdev->rst_stats.pf_rst_cnt);
	dev_info(&hdev->pdev->dev, "FLR reset count: %u\n",
		 hdev->rst_stats.flr_rst_cnt);
	dev_info(&hdev->pdev->dev, "GLOBAL reset count: %u\n",
		 hdev->rst_stats.global_rst_cnt);
	dev_info(&hdev->pdev->dev, "IMP reset count: %u\n",
		 hdev->rst_stats.imp_rst_cnt);
	dev_info(&hdev->pdev->dev, "reset done count: %u\n",
		 hdev->rst_stats.reset_करोne_cnt);
	dev_info(&hdev->pdev->dev, "HW reset done count: %u\n",
		 hdev->rst_stats.hw_reset_करोne_cnt);
	dev_info(&hdev->pdev->dev, "reset count: %u\n",
		 hdev->rst_stats.reset_cnt);
	dev_info(&hdev->pdev->dev, "reset fail count: %u\n",
		 hdev->rst_stats.reset_fail_cnt);
	dev_info(&hdev->pdev->dev, "vector0 interrupt enable status: 0x%x\n",
		 hclge_पढ़ो_dev(&hdev->hw, HCLGE_MISC_VECTOR_REG_BASE));
	dev_info(&hdev->pdev->dev, "reset interrupt source: 0x%x\n",
		 hclge_पढ़ो_dev(&hdev->hw, HCLGE_MISC_RESET_STS_REG));
	dev_info(&hdev->pdev->dev, "reset interrupt status: 0x%x\n",
		 hclge_पढ़ो_dev(&hdev->hw, HCLGE_MISC_VECTOR_INT_STS));
	dev_info(&hdev->pdev->dev, "hardware reset status: 0x%x\n",
		 hclge_पढ़ो_dev(&hdev->hw, HCLGE_GLOBAL_RESET_REG));
	dev_info(&hdev->pdev->dev, "handshake status: 0x%x\n",
		 hclge_पढ़ो_dev(&hdev->hw, HCLGE_NIC_CSQ_DEPTH_REG));
	dev_info(&hdev->pdev->dev, "function reset status: 0x%x\n",
		 hclge_पढ़ो_dev(&hdev->hw, HCLGE_FUN_RST_ING));
	dev_info(&hdev->pdev->dev, "hdev state: 0x%lx\n", hdev->state);
पूर्ण

अटल व्योम hclge_dbg_dump_serv_info(काष्ठा hclge_dev *hdev)
अणु
	dev_info(&hdev->pdev->dev, "last_serv_processed: %lu\n",
		 hdev->last_serv_processed);
	dev_info(&hdev->pdev->dev, "last_serv_cnt: %lu\n",
		 hdev->serv_processed_cnt);
पूर्ण

अटल व्योम hclge_dbg_dump_पूर्णांकerrupt(काष्ठा hclge_dev *hdev)
अणु
	dev_info(&hdev->pdev->dev, "num_nic_msi: %u\n", hdev->num_nic_msi);
	dev_info(&hdev->pdev->dev, "num_roce_msi: %u\n", hdev->num_roce_msi);
	dev_info(&hdev->pdev->dev, "num_msi_used: %u\n", hdev->num_msi_used);
	dev_info(&hdev->pdev->dev, "num_msi_left: %u\n", hdev->num_msi_left);
पूर्ण

अटल व्योम hclge_dbg_get_m7_stats_info(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_desc *desc_src, *desc_पंचांगp;
	काष्ठा hclge_get_m7_bd_cmd *req;
	काष्ठा hclge_desc desc;
	u32 bd_num, buf_len;
	पूर्णांक ret, i;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_M7_STATS_BD, true);

	req = (काष्ठा hclge_get_m7_bd_cmd *)desc.data;
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"get firmware statistics bd number failed, ret = %d\n",
			ret);
		वापस;
	पूर्ण

	bd_num = le32_to_cpu(req->bd_num);

	buf_len	 = माप(काष्ठा hclge_desc) * bd_num;
	desc_src = kzalloc(buf_len, GFP_KERNEL);
	अगर (!desc_src)
		वापस;

	desc_पंचांगp = desc_src;
	ret  = hclge_dbg_cmd_send(hdev, desc_पंचांगp, 0, bd_num,
				  HCLGE_OPC_M7_STATS_INFO);
	अगर (ret) अणु
		kमुक्त(desc_src);
		dev_err(&hdev->pdev->dev,
			"get firmware statistics failed, ret = %d\n", ret);
		वापस;
	पूर्ण

	क्रम (i = 0; i < bd_num; i++) अणु
		dev_info(&hdev->pdev->dev, "0x%08x  0x%08x  0x%08x\n",
			 le32_to_cpu(desc_पंचांगp->data[0]),
			 le32_to_cpu(desc_पंचांगp->data[1]),
			 le32_to_cpu(desc_पंचांगp->data[2]));
		dev_info(&hdev->pdev->dev, "0x%08x  0x%08x  0x%08x\n",
			 le32_to_cpu(desc_पंचांगp->data[3]),
			 le32_to_cpu(desc_पंचांगp->data[4]),
			 le32_to_cpu(desc_पंचांगp->data[5]));

		desc_पंचांगp++;
	पूर्ण

	kमुक्त(desc_src);
पूर्ण

#घोषणा HCLGE_CMD_NCL_CONFIG_BD_NUM	5

अटल व्योम hclge_ncl_config_data_prपूर्णांक(काष्ठा hclge_dev *hdev,
					काष्ठा hclge_desc *desc, पूर्णांक *offset,
					पूर्णांक *length)
अणु
#घोषणा HCLGE_CMD_DATA_NUM		6

	पूर्णांक i;
	पूर्णांक j;

	क्रम (i = 0; i < HCLGE_CMD_NCL_CONFIG_BD_NUM; i++) अणु
		क्रम (j = 0; j < HCLGE_CMD_DATA_NUM; j++) अणु
			अगर (i == 0 && j == 0)
				जारी;

			dev_info(&hdev->pdev->dev, "0x%04x | 0x%08x\n",
				 *offset,
				 le32_to_cpu(desc[i].data[j]));
			*offset += माप(u32);
			*length -= माप(u32);
			अगर (*length <= 0)
				वापस;
		पूर्ण
	पूर्ण
पूर्ण

/* hclge_dbg_dump_ncl_config: prपूर्णांक specअगरied range of NCL_CONFIG file
 * @hdev: poपूर्णांकer to काष्ठा hclge_dev
 * @cmd_buf: string that contains offset and length
 */
अटल व्योम hclge_dbg_dump_ncl_config(काष्ठा hclge_dev *hdev,
				      स्थिर अक्षर *cmd_buf)
अणु
#घोषणा HCLGE_MAX_NCL_CONFIG_OFFSET	4096
#घोषणा HCLGE_NCL_CONFIG_LENGTH_IN_EACH_CMD	(20 + 24 * 4)
#घोषणा HCLGE_NCL_CONFIG_PARAM_NUM	2

	काष्ठा hclge_desc desc[HCLGE_CMD_NCL_CONFIG_BD_NUM];
	पूर्णांक bd_num = HCLGE_CMD_NCL_CONFIG_BD_NUM;
	पूर्णांक offset;
	पूर्णांक length;
	पूर्णांक data0;
	पूर्णांक ret;

	ret = माला_पूछो(cmd_buf, "%x %x", &offset, &length);
	अगर (ret != HCLGE_NCL_CONFIG_PARAM_NUM) अणु
		dev_err(&hdev->pdev->dev,
			"Too few parameters, num = %d.\n", ret);
		वापस;
	पूर्ण

	अगर (offset < 0 || offset >= HCLGE_MAX_NCL_CONFIG_OFFSET ||
	    length <= 0 || length > HCLGE_MAX_NCL_CONFIG_OFFSET - offset) अणु
		dev_err(&hdev->pdev->dev,
			"Invalid input, offset = %d, length = %d.\n",
			offset, length);
		वापस;
	पूर्ण

	dev_info(&hdev->pdev->dev, "offset |    data\n");

	जबतक (length > 0) अणु
		data0 = offset;
		अगर (length >= HCLGE_NCL_CONFIG_LENGTH_IN_EACH_CMD)
			data0 |= HCLGE_NCL_CONFIG_LENGTH_IN_EACH_CMD << 16;
		अन्यथा
			data0 |= length << 16;
		ret = hclge_dbg_cmd_send(hdev, desc, data0, bd_num,
					 HCLGE_OPC_QUERY_NCL_CONFIG);
		अगर (ret)
			वापस;

		hclge_ncl_config_data_prपूर्णांक(hdev, desc, &offset, &length);
	पूर्ण
पूर्ण

अटल व्योम hclge_dbg_dump_loopback(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा phy_device *phydev = hdev->hw.mac.phydev;
	काष्ठा hclge_config_mac_mode_cmd *req_app;
	काष्ठा hclge_common_lb_cmd *req_common;
	काष्ठा hclge_desc desc;
	u8 loopback_en;
	पूर्णांक ret;

	req_app = (काष्ठा hclge_config_mac_mode_cmd *)desc.data;
	req_common = (काष्ठा hclge_common_lb_cmd *)desc.data;

	dev_info(&hdev->pdev->dev, "mac id: %u\n", hdev->hw.mac.mac_id);

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_CONFIG_MAC_MODE, true);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"failed to dump app loopback status, ret = %d\n", ret);
		वापस;
	पूर्ण

	loopback_en = hnae3_get_bit(le32_to_cpu(req_app->txrx_pad_fcs_loop_en),
				    HCLGE_MAC_APP_LP_B);
	dev_info(&hdev->pdev->dev, "app loopback: %s\n",
		 loopback_en ? "on" : "off");

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_COMMON_LOOPBACK, true);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"failed to dump common loopback status, ret = %d\n",
			ret);
		वापस;
	पूर्ण

	loopback_en = req_common->enable & HCLGE_CMD_SERDES_SERIAL_INNER_LOOP_B;
	dev_info(&hdev->pdev->dev, "serdes serial loopback: %s\n",
		 loopback_en ? "on" : "off");

	loopback_en = req_common->enable &
			HCLGE_CMD_SERDES_PARALLEL_INNER_LOOP_B;
	dev_info(&hdev->pdev->dev, "serdes parallel loopback: %s\n",
		 loopback_en ? "on" : "off");

	अगर (phydev) अणु
		dev_info(&hdev->pdev->dev, "phy loopback: %s\n",
			 phydev->loopback_enabled ? "on" : "off");
	पूर्ण अन्यथा अगर (hnae3_dev_phy_imp_supported(hdev)) अणु
		loopback_en = req_common->enable &
			      HCLGE_CMD_GE_PHY_INNER_LOOP_B;
		dev_info(&hdev->pdev->dev, "phy loopback: %s\n",
			 loopback_en ? "on" : "off");
	पूर्ण
पूर्ण

/* hclge_dbg_dump_mac_tnl_status: prपूर्णांक message about mac tnl पूर्णांकerrupt
 * @hdev: poपूर्णांकer to काष्ठा hclge_dev
 */
अटल व्योम hclge_dbg_dump_mac_tnl_status(काष्ठा hclge_dev *hdev)
अणु
#घोषणा HCLGE_BILLION_न_अंकO_SECONDS 1000000000

	काष्ठा hclge_mac_tnl_stats stats;
	अचिन्हित दीर्घ rem_nsec;

	dev_info(&hdev->pdev->dev, "Recently generated mac tnl interruption:\n");

	जबतक (kfअगरo_get(&hdev->mac_tnl_log, &stats)) अणु
		rem_nsec = करो_भाग(stats.समय, HCLGE_BILLION_न_अंकO_SECONDS);
		dev_info(&hdev->pdev->dev, "[%07lu.%03lu] status = 0x%x\n",
			 (अचिन्हित दीर्घ)stats.समय, rem_nsec / 1000,
			 stats.status);
	पूर्ण
पूर्ण

अटल व्योम hclge_dbg_dump_qs_shaper_single(काष्ठा hclge_dev *hdev, u16 qsid)
अणु
	काष्ठा hclge_qs_shapping_cmd *shap_cfg_cmd;
	u8 ir_u, ir_b, ir_s, bs_b, bs_s;
	काष्ठा hclge_desc desc;
	u32 shapping_para;
	u32 rate;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_QCN_SHAPPING_CFG, true);

	shap_cfg_cmd = (काष्ठा hclge_qs_shapping_cmd *)desc.data;
	shap_cfg_cmd->qs_id = cpu_to_le16(qsid);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"qs%u failed to get tx_rate, ret=%d\n",
			qsid, ret);
		वापस;
	पूर्ण

	shapping_para = le32_to_cpu(shap_cfg_cmd->qs_shapping_para);
	ir_b = hclge_पंचांग_get_field(shapping_para, IR_B);
	ir_u = hclge_पंचांग_get_field(shapping_para, IR_U);
	ir_s = hclge_पंचांग_get_field(shapping_para, IR_S);
	bs_b = hclge_पंचांग_get_field(shapping_para, BS_B);
	bs_s = hclge_पंचांग_get_field(shapping_para, BS_S);
	rate = le32_to_cpu(shap_cfg_cmd->qs_rate);

	dev_info(&hdev->pdev->dev,
		 "qs%u ir_b:%u, ir_u:%u, ir_s:%u, bs_b:%u, bs_s:%u, flag:%#x, rate:%u(Mbps)\n",
		 qsid, ir_b, ir_u, ir_s, bs_b, bs_s, shap_cfg_cmd->flag, rate);
पूर्ण

अटल व्योम hclge_dbg_dump_qs_shaper_all(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hnae3_knic_निजी_info *kinfo;
	काष्ठा hclge_vport *vport;
	पूर्णांक vport_id, i;

	क्रम (vport_id = 0; vport_id <= pci_num_vf(hdev->pdev); vport_id++) अणु
		vport = &hdev->vport[vport_id];
		kinfo = &vport->nic.kinfo;

		dev_info(&hdev->pdev->dev, "qs cfg of vport%d:\n", vport_id);

		क्रम (i = 0; i < kinfo->tc_info.num_tc; i++) अणु
			u16 qsid = vport->qs_offset + i;

			hclge_dbg_dump_qs_shaper_single(hdev, qsid);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hclge_dbg_dump_qs_shaper(काष्ठा hclge_dev *hdev,
				     स्थिर अक्षर *cmd_buf)
अणु
	u16 qsid;
	पूर्णांक ret;

	ret = kstrtou16(cmd_buf, 0, &qsid);
	अगर (ret) अणु
		hclge_dbg_dump_qs_shaper_all(hdev);
		वापस;
	पूर्ण

	अगर (qsid >= hdev->ae_dev->dev_specs.max_qset_num) अणु
		dev_err(&hdev->pdev->dev, "qsid(%u) out of range[0-%u]\n",
			qsid, hdev->ae_dev->dev_specs.max_qset_num - 1);
		वापस;
	पूर्ण

	hclge_dbg_dump_qs_shaper_single(hdev, qsid);
पूर्ण

अटल पूर्णांक hclge_dbg_dump_mac_list(काष्ठा hclge_dev *hdev, स्थिर अक्षर *cmd_buf,
				   bool is_unicast)
अणु
	काष्ठा hclge_mac_node *mac_node, *पंचांगp;
	काष्ठा hclge_vport *vport;
	काष्ठा list_head *list;
	u32 func_id;
	पूर्णांक ret;

	ret = kstrtouपूर्णांक(cmd_buf, 0, &func_id);
	अगर (ret < 0) अणु
		dev_err(&hdev->pdev->dev,
			"dump mac list: bad command string, ret = %d\n", ret);
		वापस -EINVAL;
	पूर्ण

	अगर (func_id >= hdev->num_alloc_vport) अणु
		dev_err(&hdev->pdev->dev,
			"function id(%u) is out of range(0-%u)\n", func_id,
			hdev->num_alloc_vport - 1);
		वापस -EINVAL;
	पूर्ण

	vport = &hdev->vport[func_id];

	list = is_unicast ? &vport->uc_mac_list : &vport->mc_mac_list;

	dev_info(&hdev->pdev->dev, "vport %u %s mac list:\n",
		 func_id, is_unicast ? "uc" : "mc");
	dev_info(&hdev->pdev->dev, "mac address              state\n");

	spin_lock_bh(&vport->mac_list_lock);

	list_क्रम_each_entry_safe(mac_node, पंचांगp, list, node) अणु
		dev_info(&hdev->pdev->dev, "%pM         %d\n",
			 mac_node->mac_addr, mac_node->state);
	पूर्ण

	spin_unlock_bh(&vport->mac_list_lock);

	वापस 0;
पूर्ण

पूर्णांक hclge_dbg_run_cmd(काष्ठा hnae3_handle *handle, स्थिर अक्षर *cmd_buf)
अणु
#घोषणा DUMP_REG	"dump reg"
#घोषणा DUMP_TM_MAP	"dump tm map"
#घोषणा DUMP_LOOPBACK	"dump loopback"
#घोषणा DUMP_INTERRUPT	"dump intr"

	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;

	अगर (म_भेदन(cmd_buf, "dump fd tcam", 12) == 0) अणु
		hclge_dbg_fd_tcam(hdev);
	पूर्ण अन्यथा अगर (म_भेदन(cmd_buf, "dump tc", 7) == 0) अणु
		hclge_dbg_dump_tc(hdev);
	पूर्ण अन्यथा अगर (म_भेदन(cmd_buf, DUMP_TM_MAP, म_माप(DUMP_TM_MAP)) == 0) अणु
		hclge_dbg_dump_पंचांग_map(hdev, &cmd_buf[माप(DUMP_TM_MAP)]);
	पूर्ण अन्यथा अगर (म_भेदन(cmd_buf, "dump tm", 7) == 0) अणु
		hclge_dbg_dump_पंचांग(hdev);
	पूर्ण अन्यथा अगर (म_भेदन(cmd_buf, "dump qos pause cfg", 18) == 0) अणु
		hclge_dbg_dump_qos_छोड़ो_cfg(hdev);
	पूर्ण अन्यथा अगर (म_भेदन(cmd_buf, "dump qos pri map", 16) == 0) अणु
		hclge_dbg_dump_qos_pri_map(hdev);
	पूर्ण अन्यथा अगर (म_भेदन(cmd_buf, "dump qos buf cfg", 16) == 0) अणु
		hclge_dbg_dump_qos_buf_cfg(hdev);
	पूर्ण अन्यथा अगर (म_भेदन(cmd_buf, "dump mng tbl", 12) == 0) अणु
		hclge_dbg_dump_mng_table(hdev);
	पूर्ण अन्यथा अगर (म_भेदन(cmd_buf, DUMP_REG, म_माप(DUMP_REG)) == 0) अणु
		hclge_dbg_dump_reg_cmd(hdev, &cmd_buf[माप(DUMP_REG)]);
	पूर्ण अन्यथा अगर (म_भेदन(cmd_buf, "dump reset info", 15) == 0) अणु
		hclge_dbg_dump_rst_info(hdev);
	पूर्ण अन्यथा अगर (म_भेदन(cmd_buf, "dump serv info", 14) == 0) अणु
		hclge_dbg_dump_serv_info(hdev);
	पूर्ण अन्यथा अगर (म_भेदन(cmd_buf, "dump m7 info", 12) == 0) अणु
		hclge_dbg_get_m7_stats_info(hdev);
	पूर्ण अन्यथा अगर (म_भेदन(cmd_buf, "dump ncl_config", 15) == 0) अणु
		hclge_dbg_dump_ncl_config(hdev,
					  &cmd_buf[माप("dump ncl_config")]);
	पूर्ण अन्यथा अगर (म_भेदन(cmd_buf, "dump mac tnl status", 19) == 0) अणु
		hclge_dbg_dump_mac_tnl_status(hdev);
	पूर्ण अन्यथा अगर (म_भेदन(cmd_buf, DUMP_LOOPBACK,
		   म_माप(DUMP_LOOPBACK)) == 0) अणु
		hclge_dbg_dump_loopback(hdev);
	पूर्ण अन्यथा अगर (म_भेदन(cmd_buf, "dump qs shaper", 14) == 0) अणु
		hclge_dbg_dump_qs_shaper(hdev,
					 &cmd_buf[माप("dump qs shaper")]);
	पूर्ण अन्यथा अगर (म_भेदन(cmd_buf, "dump uc mac list", 16) == 0) अणु
		hclge_dbg_dump_mac_list(hdev,
					&cmd_buf[माप("dump uc mac list")],
					true);
	पूर्ण अन्यथा अगर (म_भेदन(cmd_buf, "dump mc mac list", 16) == 0) अणु
		hclge_dbg_dump_mac_list(hdev,
					&cmd_buf[माप("dump mc mac list")],
					false);
	पूर्ण अन्यथा अगर (म_भेदन(cmd_buf, DUMP_INTERRUPT,
		   म_माप(DUMP_INTERRUPT)) == 0) अणु
		hclge_dbg_dump_पूर्णांकerrupt(hdev);
	पूर्ण अन्यथा अणु
		dev_info(&hdev->pdev->dev, "unknown command\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hclge_dbg_पढ़ो_cmd(काष्ठा hnae3_handle *handle, स्थिर अक्षर *cmd_buf,
		       अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;

	अगर (म_भेदन(cmd_buf, HNAE3_DBG_TM_NODES,
		    म_माप(HNAE3_DBG_TM_NODES)) == 0)
		वापस hclge_dbg_dump_पंचांग_nodes(hdev, buf, len);
	अन्यथा अगर (म_भेदन(cmd_buf, HNAE3_DBG_TM_PRI,
			 म_माप(HNAE3_DBG_TM_PRI)) == 0)
		वापस hclge_dbg_dump_पंचांग_pri(hdev, buf, len);
	अन्यथा अगर (म_भेदन(cmd_buf, HNAE3_DBG_TM_QSET,
			 म_माप(HNAE3_DBG_TM_QSET)) == 0)
		वापस hclge_dbg_dump_पंचांग_qset(hdev, buf, len);

	वापस -EINVAL;
पूर्ण
