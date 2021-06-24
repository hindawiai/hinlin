<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright (c) 2016-2017 Hisilicon Limited.

#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/dma-direction.h>
#समावेश "hclge_cmd.h"
#समावेश "hnae3.h"
#समावेश "hclge_main.h"

#घोषणा cmq_ring_to_dev(ring)   (&(ring)->dev->pdev->dev)

अटल पूर्णांक hclge_ring_space(काष्ठा hclge_cmq_ring *ring)
अणु
	पूर्णांक ntu = ring->next_to_use;
	पूर्णांक ntc = ring->next_to_clean;
	पूर्णांक used = (ntu - ntc + ring->desc_num) % ring->desc_num;

	वापस ring->desc_num - used - 1;
पूर्ण

अटल पूर्णांक is_valid_csq_clean_head(काष्ठा hclge_cmq_ring *ring, पूर्णांक head)
अणु
	पूर्णांक ntu = ring->next_to_use;
	पूर्णांक ntc = ring->next_to_clean;

	अगर (ntu > ntc)
		वापस head >= ntc && head <= ntu;

	वापस head >= ntc || head <= ntu;
पूर्ण

अटल पूर्णांक hclge_alloc_cmd_desc(काष्ठा hclge_cmq_ring *ring)
अणु
	पूर्णांक size  = ring->desc_num * माप(काष्ठा hclge_desc);

	ring->desc = dma_alloc_coherent(cmq_ring_to_dev(ring), size,
					&ring->desc_dma_addr, GFP_KERNEL);
	अगर (!ring->desc)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम hclge_मुक्त_cmd_desc(काष्ठा hclge_cmq_ring *ring)
अणु
	पूर्णांक size  = ring->desc_num * माप(काष्ठा hclge_desc);

	अगर (ring->desc) अणु
		dma_मुक्त_coherent(cmq_ring_to_dev(ring), size,
				  ring->desc, ring->desc_dma_addr);
		ring->desc = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक hclge_alloc_cmd_queue(काष्ठा hclge_dev *hdev, पूर्णांक ring_type)
अणु
	काष्ठा hclge_hw *hw = &hdev->hw;
	काष्ठा hclge_cmq_ring *ring =
		(ring_type == HCLGE_TYPE_CSQ) ? &hw->cmq.csq : &hw->cmq.crq;
	पूर्णांक ret;

	ring->ring_type = ring_type;
	ring->dev = hdev;

	ret = hclge_alloc_cmd_desc(ring);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev, "descriptor %s alloc error %d\n",
			(ring_type == HCLGE_TYPE_CSQ) ? "CSQ" : "CRQ", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

व्योम hclge_cmd_reuse_desc(काष्ठा hclge_desc *desc, bool is_पढ़ो)
अणु
	desc->flag = cpu_to_le16(HCLGE_CMD_FLAG_NO_INTR | HCLGE_CMD_FLAG_IN);
	अगर (is_पढ़ो)
		desc->flag |= cpu_to_le16(HCLGE_CMD_FLAG_WR);
	अन्यथा
		desc->flag &= cpu_to_le16(~HCLGE_CMD_FLAG_WR);
पूर्ण

व्योम hclge_cmd_setup_basic_desc(काष्ठा hclge_desc *desc,
				क्रमागत hclge_opcode_type opcode, bool is_पढ़ो)
अणु
	स_रखो((व्योम *)desc, 0, माप(काष्ठा hclge_desc));
	desc->opcode = cpu_to_le16(opcode);
	desc->flag = cpu_to_le16(HCLGE_CMD_FLAG_NO_INTR | HCLGE_CMD_FLAG_IN);

	अगर (is_पढ़ो)
		desc->flag |= cpu_to_le16(HCLGE_CMD_FLAG_WR);
पूर्ण

अटल व्योम hclge_cmd_config_regs(काष्ठा hclge_cmq_ring *ring)
अणु
	dma_addr_t dma = ring->desc_dma_addr;
	काष्ठा hclge_dev *hdev = ring->dev;
	काष्ठा hclge_hw *hw = &hdev->hw;
	u32 reg_val;

	अगर (ring->ring_type == HCLGE_TYPE_CSQ) अणु
		hclge_ग_लिखो_dev(hw, HCLGE_NIC_CSQ_BASEADDR_L_REG,
				lower_32_bits(dma));
		hclge_ग_लिखो_dev(hw, HCLGE_NIC_CSQ_BASEADDR_H_REG,
				upper_32_bits(dma));
		reg_val = hclge_पढ़ो_dev(hw, HCLGE_NIC_CSQ_DEPTH_REG);
		reg_val &= HCLGE_NIC_SW_RST_RDY;
		reg_val |= ring->desc_num >> HCLGE_NIC_CMQ_DESC_NUM_S;
		hclge_ग_लिखो_dev(hw, HCLGE_NIC_CSQ_DEPTH_REG, reg_val);
		hclge_ग_लिखो_dev(hw, HCLGE_NIC_CSQ_HEAD_REG, 0);
		hclge_ग_लिखो_dev(hw, HCLGE_NIC_CSQ_TAIL_REG, 0);
	पूर्ण अन्यथा अणु
		hclge_ग_लिखो_dev(hw, HCLGE_NIC_CRQ_BASEADDR_L_REG,
				lower_32_bits(dma));
		hclge_ग_लिखो_dev(hw, HCLGE_NIC_CRQ_BASEADDR_H_REG,
				upper_32_bits(dma));
		hclge_ग_लिखो_dev(hw, HCLGE_NIC_CRQ_DEPTH_REG,
				ring->desc_num >> HCLGE_NIC_CMQ_DESC_NUM_S);
		hclge_ग_लिखो_dev(hw, HCLGE_NIC_CRQ_HEAD_REG, 0);
		hclge_ग_लिखो_dev(hw, HCLGE_NIC_CRQ_TAIL_REG, 0);
	पूर्ण
पूर्ण

अटल व्योम hclge_cmd_init_regs(काष्ठा hclge_hw *hw)
अणु
	hclge_cmd_config_regs(&hw->cmq.csq);
	hclge_cmd_config_regs(&hw->cmq.crq);
पूर्ण

अटल पूर्णांक hclge_cmd_csq_clean(काष्ठा hclge_hw *hw)
अणु
	काष्ठा hclge_dev *hdev = container_of(hw, काष्ठा hclge_dev, hw);
	काष्ठा hclge_cmq_ring *csq = &hw->cmq.csq;
	u32 head;
	पूर्णांक clean;

	head = hclge_पढ़ो_dev(hw, HCLGE_NIC_CSQ_HEAD_REG);
	rmb(); /* Make sure head is पढ़ोy beक्रमe touch any data */

	अगर (!is_valid_csq_clean_head(csq, head)) अणु
		dev_warn(&hdev->pdev->dev, "wrong cmd head (%u, %d-%d)\n", head,
			 csq->next_to_use, csq->next_to_clean);
		dev_warn(&hdev->pdev->dev,
			 "Disabling any further commands to IMP firmware\n");
		set_bit(HCLGE_STATE_CMD_DISABLE, &hdev->state);
		dev_warn(&hdev->pdev->dev,
			 "IMP firmware watchdog reset soon expected!\n");
		वापस -EIO;
	पूर्ण

	clean = (head - csq->next_to_clean + csq->desc_num) % csq->desc_num;
	csq->next_to_clean = head;
	वापस clean;
पूर्ण

अटल पूर्णांक hclge_cmd_csq_करोne(काष्ठा hclge_hw *hw)
अणु
	u32 head = hclge_पढ़ो_dev(hw, HCLGE_NIC_CSQ_HEAD_REG);
	वापस head == hw->cmq.csq.next_to_use;
पूर्ण

अटल bool hclge_is_special_opcode(u16 opcode)
अणु
	/* these commands have several descriptors,
	 * and use the first one to save opcode and वापस value
	 */
	u16 spec_opcode[] = अणुHCLGE_OPC_STATS_64_BIT,
			     HCLGE_OPC_STATS_32_BIT,
			     HCLGE_OPC_STATS_MAC,
			     HCLGE_OPC_STATS_MAC_ALL,
			     HCLGE_OPC_QUERY_32_BIT_REG,
			     HCLGE_OPC_QUERY_64_BIT_REG,
			     HCLGE_QUERY_CLEAR_MPF_RAS_INT,
			     HCLGE_QUERY_CLEAR_PF_RAS_INT,
			     HCLGE_QUERY_CLEAR_ALL_MPF_MSIX_INT,
			     HCLGE_QUERY_CLEAR_ALL_PF_MSIX_INTपूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(spec_opcode); i++) अणु
		अगर (spec_opcode[i] == opcode)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

काष्ठा errcode अणु
	u32 imp_errcode;
	पूर्णांक common_त्रुटि_सं;
पूर्ण;

अटल व्योम hclge_cmd_copy_desc(काष्ठा hclge_hw *hw, काष्ठा hclge_desc *desc,
				पूर्णांक num)
अणु
	काष्ठा hclge_desc *desc_to_use;
	पूर्णांक handle = 0;

	जबतक (handle < num) अणु
		desc_to_use = &hw->cmq.csq.desc[hw->cmq.csq.next_to_use];
		*desc_to_use = desc[handle];
		(hw->cmq.csq.next_to_use)++;
		अगर (hw->cmq.csq.next_to_use >= hw->cmq.csq.desc_num)
			hw->cmq.csq.next_to_use = 0;
		handle++;
	पूर्ण
पूर्ण

अटल पूर्णांक hclge_cmd_convert_err_code(u16 desc_ret)
अणु
	काष्ठा errcode hclge_cmd_errcode[] = अणु
		अणुHCLGE_CMD_EXEC_SUCCESS, 0पूर्ण,
		अणुHCLGE_CMD_NO_AUTH, -EPERMपूर्ण,
		अणुHCLGE_CMD_NOT_SUPPORTED, -EOPNOTSUPPपूर्ण,
		अणुHCLGE_CMD_QUEUE_FULL, -EXFULLपूर्ण,
		अणुHCLGE_CMD_NEXT_ERR, -ENOSRपूर्ण,
		अणुHCLGE_CMD_UNEXE_ERR, -ENOTBLKपूर्ण,
		अणुHCLGE_CMD_PARA_ERR, -EINVALपूर्ण,
		अणुHCLGE_CMD_RESULT_ERR, -दुस्फलपूर्ण,
		अणुHCLGE_CMD_TIMEOUT, -ETIMEपूर्ण,
		अणुHCLGE_CMD_HILINK_ERR, -ENOLINKपूर्ण,
		अणुHCLGE_CMD_QUEUE_ILLEGAL, -ENXIOपूर्ण,
		अणुHCLGE_CMD_INVALID, -EBADRपूर्ण,
	पूर्ण;
	u32 errcode_count = ARRAY_SIZE(hclge_cmd_errcode);
	u32 i;

	क्रम (i = 0; i < errcode_count; i++)
		अगर (hclge_cmd_errcode[i].imp_errcode == desc_ret)
			वापस hclge_cmd_errcode[i].common_त्रुटि_सं;

	वापस -EIO;
पूर्ण

अटल पूर्णांक hclge_cmd_check_retval(काष्ठा hclge_hw *hw, काष्ठा hclge_desc *desc,
				  पूर्णांक num, पूर्णांक ntc)
अणु
	u16 opcode, desc_ret;
	पूर्णांक handle;

	opcode = le16_to_cpu(desc[0].opcode);
	क्रम (handle = 0; handle < num; handle++) अणु
		desc[handle] = hw->cmq.csq.desc[ntc];
		ntc++;
		अगर (ntc >= hw->cmq.csq.desc_num)
			ntc = 0;
	पूर्ण
	अगर (likely(!hclge_is_special_opcode(opcode)))
		desc_ret = le16_to_cpu(desc[num - 1].retval);
	अन्यथा
		desc_ret = le16_to_cpu(desc[0].retval);

	hw->cmq.last_status = desc_ret;

	वापस hclge_cmd_convert_err_code(desc_ret);
पूर्ण

अटल पूर्णांक hclge_cmd_check_result(काष्ठा hclge_hw *hw, काष्ठा hclge_desc *desc,
				  पूर्णांक num, पूर्णांक ntc)
अणु
	काष्ठा hclge_dev *hdev = container_of(hw, काष्ठा hclge_dev, hw);
	bool is_completed = false;
	u32 समयout = 0;
	पूर्णांक handle, ret;

	/**
	 * If the command is sync, रुको क्रम the firmware to ग_लिखो back,
	 * अगर multi descriptors to be sent, use the first one to check
	 */
	अगर (HCLGE_SEND_SYNC(le16_to_cpu(desc->flag))) अणु
		करो अणु
			अगर (hclge_cmd_csq_करोne(hw)) अणु
				is_completed = true;
				अवरोध;
			पूर्ण
			udelay(1);
			समयout++;
		पूर्ण जबतक (समयout < hw->cmq.tx_समयout);
	पूर्ण

	अगर (!is_completed)
		ret = -EBADE;
	अन्यथा
		ret = hclge_cmd_check_retval(hw, desc, num, ntc);

	/* Clean the command send queue */
	handle = hclge_cmd_csq_clean(hw);
	अगर (handle < 0)
		ret = handle;
	अन्यथा अगर (handle != num)
		dev_warn(&hdev->pdev->dev,
			 "cleaned %d, need to clean %d\n", handle, num);
	वापस ret;
पूर्ण

/**
 * hclge_cmd_send - send command to command queue
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @desc: prefilled descriptor क्रम describing the command
 * @num : the number of descriptors to be sent
 *
 * This is the मुख्य send command क्रम command queue, it
 * sends the queue, cleans the queue, etc
 **/
पूर्णांक hclge_cmd_send(काष्ठा hclge_hw *hw, काष्ठा hclge_desc *desc, पूर्णांक num)
अणु
	काष्ठा hclge_dev *hdev = container_of(hw, काष्ठा hclge_dev, hw);
	काष्ठा hclge_cmq_ring *csq = &hw->cmq.csq;
	पूर्णांक ret;
	पूर्णांक ntc;

	spin_lock_bh(&hw->cmq.csq.lock);

	अगर (test_bit(HCLGE_STATE_CMD_DISABLE, &hdev->state)) अणु
		spin_unlock_bh(&hw->cmq.csq.lock);
		वापस -EBUSY;
	पूर्ण

	अगर (num > hclge_ring_space(&hw->cmq.csq)) अणु
		/* If CMDQ ring is full, SW HEAD and HW HEAD may be dअगरferent,
		 * need update the SW HEAD poपूर्णांकer csq->next_to_clean
		 */
		csq->next_to_clean = hclge_पढ़ो_dev(hw, HCLGE_NIC_CSQ_HEAD_REG);
		spin_unlock_bh(&hw->cmq.csq.lock);
		वापस -EBUSY;
	पूर्ण

	/**
	 * Record the location of desc in the ring क्रम this समय
	 * which will be use क्रम hardware to ग_लिखो back
	 */
	ntc = hw->cmq.csq.next_to_use;

	hclge_cmd_copy_desc(hw, desc, num);

	/* Write to hardware */
	hclge_ग_लिखो_dev(hw, HCLGE_NIC_CSQ_TAIL_REG, hw->cmq.csq.next_to_use);

	ret = hclge_cmd_check_result(hw, desc, num, ntc);

	spin_unlock_bh(&hw->cmq.csq.lock);

	वापस ret;
पूर्ण

अटल व्योम hclge_set_शेष_capability(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(hdev->pdev);

	set_bit(HNAE3_DEV_SUPPORT_FD_B, ae_dev->caps);
	set_bit(HNAE3_DEV_SUPPORT_GRO_B, ae_dev->caps);
	अगर (hdev->ae_dev->dev_version == HNAE3_DEVICE_VERSION_V2) अणु
		set_bit(HNAE3_DEV_SUPPORT_FEC_B, ae_dev->caps);
		set_bit(HNAE3_DEV_SUPPORT_PAUSE_B, ae_dev->caps);
	पूर्ण
पूर्ण

अटल व्योम hclge_parse_capability(काष्ठा hclge_dev *hdev,
				   काष्ठा hclge_query_version_cmd *cmd)
अणु
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(hdev->pdev);
	u32 caps;

	caps = __le32_to_cpu(cmd->caps[0]);
	अगर (hnae3_get_bit(caps, HCLGE_CAP_UDP_GSO_B))
		set_bit(HNAE3_DEV_SUPPORT_UDP_GSO_B, ae_dev->caps);
	अगर (hnae3_get_bit(caps, HCLGE_CAP_PTP_B))
		set_bit(HNAE3_DEV_SUPPORT_PTP_B, ae_dev->caps);
	अगर (hnae3_get_bit(caps, HCLGE_CAP_INT_QL_B))
		set_bit(HNAE3_DEV_SUPPORT_INT_QL_B, ae_dev->caps);
	अगर (hnae3_get_bit(caps, HCLGE_CAP_TQP_TXRX_INDEP_B))
		set_bit(HNAE3_DEV_SUPPORT_TQP_TXRX_INDEP_B, ae_dev->caps);
	अगर (hnae3_get_bit(caps, HCLGE_CAP_HW_TX_CSUM_B))
		set_bit(HNAE3_DEV_SUPPORT_HW_TX_CSUM_B, ae_dev->caps);
	अगर (hnae3_get_bit(caps, HCLGE_CAP_UDP_TUNNEL_CSUM_B))
		set_bit(HNAE3_DEV_SUPPORT_UDP_TUNNEL_CSUM_B, ae_dev->caps);
	अगर (hnae3_get_bit(caps, HCLGE_CAP_FD_FORWARD_TC_B))
		set_bit(HNAE3_DEV_SUPPORT_FD_FORWARD_TC_B, ae_dev->caps);
	अगर (hnae3_get_bit(caps, HCLGE_CAP_FEC_B))
		set_bit(HNAE3_DEV_SUPPORT_FEC_B, ae_dev->caps);
	अगर (hnae3_get_bit(caps, HCLGE_CAP_PAUSE_B))
		set_bit(HNAE3_DEV_SUPPORT_PAUSE_B, ae_dev->caps);
	अगर (hnae3_get_bit(caps, HCLGE_CAP_PHY_IMP_B))
		set_bit(HNAE3_DEV_SUPPORT_PHY_IMP_B, ae_dev->caps);
पूर्ण

अटल __le32 hclge_build_api_caps(व्योम)
अणु
	u32 api_caps = 0;

	hnae3_set_bit(api_caps, HCLGE_API_CAP_FLEX_RSS_TBL_B, 1);

	वापस cpu_to_le32(api_caps);
पूर्ण

अटल क्रमागत hclge_cmd_status
hclge_cmd_query_version_and_capability(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(hdev->pdev);
	काष्ठा hclge_query_version_cmd *resp;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_QUERY_FW_VER, 1);
	resp = (काष्ठा hclge_query_version_cmd *)desc.data;
	resp->api_caps = hclge_build_api_caps();

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		वापस ret;

	hdev->fw_version = le32_to_cpu(resp->firmware);

	ae_dev->dev_version = le32_to_cpu(resp->hardware) <<
					 HNAE3_PCI_REVISION_BIT_SIZE;
	ae_dev->dev_version |= hdev->pdev->revision;

	अगर (ae_dev->dev_version >= HNAE3_DEVICE_VERSION_V2)
		hclge_set_शेष_capability(hdev);

	hclge_parse_capability(hdev, resp);

	वापस ret;
पूर्ण

पूर्णांक hclge_cmd_queue_init(काष्ठा hclge_dev *hdev)
अणु
	पूर्णांक ret;

	/* Setup the lock क्रम command queue */
	spin_lock_init(&hdev->hw.cmq.csq.lock);
	spin_lock_init(&hdev->hw.cmq.crq.lock);

	/* Setup the queue entries क्रम use cmd queue */
	hdev->hw.cmq.csq.desc_num = HCLGE_NIC_CMQ_DESC_NUM;
	hdev->hw.cmq.crq.desc_num = HCLGE_NIC_CMQ_DESC_NUM;

	/* Setup Tx ग_लिखो back समयout */
	hdev->hw.cmq.tx_समयout = HCLGE_CMDQ_TX_TIMEOUT;

	/* Setup queue rings */
	ret = hclge_alloc_cmd_queue(hdev, HCLGE_TYPE_CSQ);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"CSQ ring setup error %d\n", ret);
		वापस ret;
	पूर्ण

	ret = hclge_alloc_cmd_queue(hdev, HCLGE_TYPE_CRQ);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"CRQ ring setup error %d\n", ret);
		जाओ err_csq;
	पूर्ण

	वापस 0;
err_csq:
	hclge_मुक्त_cmd_desc(&hdev->hw.cmq.csq);
	वापस ret;
पूर्ण

अटल पूर्णांक hclge_firmware_compat_config(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_firmware_compat_cmd *req;
	काष्ठा hclge_desc desc;
	u32 compat = 0;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_M7_COMPAT_CFG, false);

	req = (काष्ठा hclge_firmware_compat_cmd *)desc.data;

	hnae3_set_bit(compat, HCLGE_LINK_EVENT_REPORT_EN_B, 1);
	hnae3_set_bit(compat, HCLGE_NCSI_ERROR_REPORT_EN_B, 1);
	अगर (hnae3_dev_phy_imp_supported(hdev))
		hnae3_set_bit(compat, HCLGE_PHY_IMP_EN_B, 1);
	req->compat = cpu_to_le32(compat);

	वापस hclge_cmd_send(&hdev->hw, &desc, 1);
पूर्ण

पूर्णांक hclge_cmd_init(काष्ठा hclge_dev *hdev)
अणु
	पूर्णांक ret;

	spin_lock_bh(&hdev->hw.cmq.csq.lock);
	spin_lock(&hdev->hw.cmq.crq.lock);

	hdev->hw.cmq.csq.next_to_clean = 0;
	hdev->hw.cmq.csq.next_to_use = 0;
	hdev->hw.cmq.crq.next_to_clean = 0;
	hdev->hw.cmq.crq.next_to_use = 0;

	hclge_cmd_init_regs(&hdev->hw);

	spin_unlock(&hdev->hw.cmq.crq.lock);
	spin_unlock_bh(&hdev->hw.cmq.csq.lock);

	clear_bit(HCLGE_STATE_CMD_DISABLE, &hdev->state);

	/* Check अगर there is new reset pending, because the higher level
	 * reset may happen when lower level reset is being processed.
	 */
	अगर ((hclge_is_reset_pending(hdev))) अणु
		dev_err(&hdev->pdev->dev,
			"failed to init cmd since reset %#lx pending\n",
			hdev->reset_pending);
		ret = -EBUSY;
		जाओ err_cmd_init;
	पूर्ण

	/* get version and device capabilities */
	ret = hclge_cmd_query_version_and_capability(hdev);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"failed to query version and capabilities, ret = %d\n",
			ret);
		जाओ err_cmd_init;
	पूर्ण

	dev_info(&hdev->pdev->dev, "The firmware version is %lu.%lu.%lu.%lu\n",
		 hnae3_get_field(hdev->fw_version, HNAE3_FW_VERSION_BYTE3_MASK,
				 HNAE3_FW_VERSION_BYTE3_SHIFT),
		 hnae3_get_field(hdev->fw_version, HNAE3_FW_VERSION_BYTE2_MASK,
				 HNAE3_FW_VERSION_BYTE2_SHIFT),
		 hnae3_get_field(hdev->fw_version, HNAE3_FW_VERSION_BYTE1_MASK,
				 HNAE3_FW_VERSION_BYTE1_SHIFT),
		 hnae3_get_field(hdev->fw_version, HNAE3_FW_VERSION_BYTE0_MASK,
				 HNAE3_FW_VERSION_BYTE0_SHIFT));

	/* ask the firmware to enable some features, driver can work without
	 * it.
	 */
	ret = hclge_firmware_compat_config(hdev);
	अगर (ret)
		dev_warn(&hdev->pdev->dev,
			 "Firmware compatible features not enabled(%d).\n",
			 ret);

	वापस 0;

err_cmd_init:
	set_bit(HCLGE_STATE_CMD_DISABLE, &hdev->state);

	वापस ret;
पूर्ण

अटल व्योम hclge_cmd_uninit_regs(काष्ठा hclge_hw *hw)
अणु
	hclge_ग_लिखो_dev(hw, HCLGE_NIC_CSQ_BASEADDR_L_REG, 0);
	hclge_ग_लिखो_dev(hw, HCLGE_NIC_CSQ_BASEADDR_H_REG, 0);
	hclge_ग_लिखो_dev(hw, HCLGE_NIC_CSQ_DEPTH_REG, 0);
	hclge_ग_लिखो_dev(hw, HCLGE_NIC_CSQ_HEAD_REG, 0);
	hclge_ग_लिखो_dev(hw, HCLGE_NIC_CSQ_TAIL_REG, 0);
	hclge_ग_लिखो_dev(hw, HCLGE_NIC_CRQ_BASEADDR_L_REG, 0);
	hclge_ग_लिखो_dev(hw, HCLGE_NIC_CRQ_BASEADDR_H_REG, 0);
	hclge_ग_लिखो_dev(hw, HCLGE_NIC_CRQ_DEPTH_REG, 0);
	hclge_ग_लिखो_dev(hw, HCLGE_NIC_CRQ_HEAD_REG, 0);
	hclge_ग_लिखो_dev(hw, HCLGE_NIC_CRQ_TAIL_REG, 0);
पूर्ण

व्योम hclge_cmd_uninit(काष्ठा hclge_dev *hdev)
अणु
	spin_lock_bh(&hdev->hw.cmq.csq.lock);
	spin_lock(&hdev->hw.cmq.crq.lock);
	set_bit(HCLGE_STATE_CMD_DISABLE, &hdev->state);
	hclge_cmd_uninit_regs(&hdev->hw);
	spin_unlock(&hdev->hw.cmq.crq.lock);
	spin_unlock_bh(&hdev->hw.cmq.csq.lock);

	hclge_मुक्त_cmd_desc(&hdev->hw.cmq.csq);
	hclge_मुक्त_cmd_desc(&hdev->hw.cmq.crq);
पूर्ण
