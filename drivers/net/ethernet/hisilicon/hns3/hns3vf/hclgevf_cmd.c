<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright (c) 2016-2017 Hisilicon Limited.

#समावेश <linux/device.h>
#समावेश <linux/dma-direction.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश "hclgevf_cmd.h"
#समावेश "hclgevf_main.h"
#समावेश "hnae3.h"

#घोषणा cmq_ring_to_dev(ring)   (&(ring)->dev->pdev->dev)

अटल पूर्णांक hclgevf_ring_space(काष्ठा hclgevf_cmq_ring *ring)
अणु
	पूर्णांक ntc = ring->next_to_clean;
	पूर्णांक ntu = ring->next_to_use;
	पूर्णांक used;

	used = (ntu - ntc + ring->desc_num) % ring->desc_num;

	वापस ring->desc_num - used - 1;
पूर्ण

अटल पूर्णांक hclgevf_is_valid_csq_clean_head(काष्ठा hclgevf_cmq_ring *ring,
					   पूर्णांक head)
अणु
	पूर्णांक ntu = ring->next_to_use;
	पूर्णांक ntc = ring->next_to_clean;

	अगर (ntu > ntc)
		वापस head >= ntc && head <= ntu;

	वापस head >= ntc || head <= ntu;
पूर्ण

अटल पूर्णांक hclgevf_cmd_csq_clean(काष्ठा hclgevf_hw *hw)
अणु
	काष्ठा hclgevf_dev *hdev = container_of(hw, काष्ठा hclgevf_dev, hw);
	काष्ठा hclgevf_cmq_ring *csq = &hw->cmq.csq;
	पूर्णांक clean;
	u32 head;

	head = hclgevf_पढ़ो_dev(hw, HCLGEVF_NIC_CSQ_HEAD_REG);
	rmb(); /* Make sure head is पढ़ोy beक्रमe touch any data */

	अगर (!hclgevf_is_valid_csq_clean_head(csq, head)) अणु
		dev_warn(&hdev->pdev->dev, "wrong cmd head (%u, %d-%d)\n", head,
			 csq->next_to_use, csq->next_to_clean);
		dev_warn(&hdev->pdev->dev,
			 "Disabling any further commands to IMP firmware\n");
		set_bit(HCLGEVF_STATE_CMD_DISABLE, &hdev->state);
		वापस -EIO;
	पूर्ण

	clean = (head - csq->next_to_clean + csq->desc_num) % csq->desc_num;
	csq->next_to_clean = head;
	वापस clean;
पूर्ण

अटल bool hclgevf_cmd_csq_करोne(काष्ठा hclgevf_hw *hw)
अणु
	u32 head;

	head = hclgevf_पढ़ो_dev(hw, HCLGEVF_NIC_CSQ_HEAD_REG);

	वापस head == hw->cmq.csq.next_to_use;
पूर्ण

अटल bool hclgevf_is_special_opcode(u16 opcode)
अणु
	अटल स्थिर u16 spec_opcode[] = अणु0x30, 0x31, 0x32पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(spec_opcode); i++) अणु
		अगर (spec_opcode[i] == opcode)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम hclgevf_cmd_config_regs(काष्ठा hclgevf_cmq_ring *ring)
अणु
	काष्ठा hclgevf_dev *hdev = ring->dev;
	काष्ठा hclgevf_hw *hw = &hdev->hw;
	u32 reg_val;

	अगर (ring->flag == HCLGEVF_TYPE_CSQ) अणु
		reg_val = lower_32_bits(ring->desc_dma_addr);
		hclgevf_ग_लिखो_dev(hw, HCLGEVF_NIC_CSQ_BASEADDR_L_REG, reg_val);
		reg_val = upper_32_bits(ring->desc_dma_addr);
		hclgevf_ग_लिखो_dev(hw, HCLGEVF_NIC_CSQ_BASEADDR_H_REG, reg_val);

		reg_val = hclgevf_पढ़ो_dev(hw, HCLGEVF_NIC_CSQ_DEPTH_REG);
		reg_val &= HCLGEVF_NIC_SW_RST_RDY;
		reg_val |= (ring->desc_num >> HCLGEVF_NIC_CMQ_DESC_NUM_S);
		hclgevf_ग_लिखो_dev(hw, HCLGEVF_NIC_CSQ_DEPTH_REG, reg_val);

		hclgevf_ग_लिखो_dev(hw, HCLGEVF_NIC_CSQ_HEAD_REG, 0);
		hclgevf_ग_लिखो_dev(hw, HCLGEVF_NIC_CSQ_TAIL_REG, 0);
	पूर्ण अन्यथा अणु
		reg_val = lower_32_bits(ring->desc_dma_addr);
		hclgevf_ग_लिखो_dev(hw, HCLGEVF_NIC_CRQ_BASEADDR_L_REG, reg_val);
		reg_val = upper_32_bits(ring->desc_dma_addr);
		hclgevf_ग_लिखो_dev(hw, HCLGEVF_NIC_CRQ_BASEADDR_H_REG, reg_val);

		reg_val = (ring->desc_num >> HCLGEVF_NIC_CMQ_DESC_NUM_S);
		hclgevf_ग_लिखो_dev(hw, HCLGEVF_NIC_CRQ_DEPTH_REG, reg_val);

		hclgevf_ग_लिखो_dev(hw, HCLGEVF_NIC_CRQ_HEAD_REG, 0);
		hclgevf_ग_लिखो_dev(hw, HCLGEVF_NIC_CRQ_TAIL_REG, 0);
	पूर्ण
पूर्ण

अटल व्योम hclgevf_cmd_init_regs(काष्ठा hclgevf_hw *hw)
अणु
	hclgevf_cmd_config_regs(&hw->cmq.csq);
	hclgevf_cmd_config_regs(&hw->cmq.crq);
पूर्ण

अटल पूर्णांक hclgevf_alloc_cmd_desc(काष्ठा hclgevf_cmq_ring *ring)
अणु
	पूर्णांक size = ring->desc_num * माप(काष्ठा hclgevf_desc);

	ring->desc = dma_alloc_coherent(cmq_ring_to_dev(ring), size,
					&ring->desc_dma_addr, GFP_KERNEL);
	अगर (!ring->desc)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम hclgevf_मुक्त_cmd_desc(काष्ठा hclgevf_cmq_ring *ring)
अणु
	पूर्णांक size  = ring->desc_num * माप(काष्ठा hclgevf_desc);

	अगर (ring->desc) अणु
		dma_मुक्त_coherent(cmq_ring_to_dev(ring), size,
				  ring->desc, ring->desc_dma_addr);
		ring->desc = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक hclgevf_alloc_cmd_queue(काष्ठा hclgevf_dev *hdev, पूर्णांक ring_type)
अणु
	काष्ठा hclgevf_hw *hw = &hdev->hw;
	काष्ठा hclgevf_cmq_ring *ring =
		(ring_type == HCLGEVF_TYPE_CSQ) ? &hw->cmq.csq : &hw->cmq.crq;
	पूर्णांक ret;

	ring->dev = hdev;
	ring->flag = ring_type;

	/* allocate CSQ/CRQ descriptor */
	ret = hclgevf_alloc_cmd_desc(ring);
	अगर (ret)
		dev_err(&hdev->pdev->dev, "failed(%d) to alloc %s desc\n", ret,
			(ring_type == HCLGEVF_TYPE_CSQ) ? "CSQ" : "CRQ");

	वापस ret;
पूर्ण

व्योम hclgevf_cmd_setup_basic_desc(काष्ठा hclgevf_desc *desc,
				  क्रमागत hclgevf_opcode_type opcode, bool is_पढ़ो)
अणु
	स_रखो(desc, 0, माप(काष्ठा hclgevf_desc));
	desc->opcode = cpu_to_le16(opcode);
	desc->flag = cpu_to_le16(HCLGEVF_CMD_FLAG_NO_INTR |
				 HCLGEVF_CMD_FLAG_IN);
	अगर (is_पढ़ो)
		desc->flag |= cpu_to_le16(HCLGEVF_CMD_FLAG_WR);
	अन्यथा
		desc->flag &= cpu_to_le16(~HCLGEVF_CMD_FLAG_WR);
पूर्ण

काष्ठा vf_errcode अणु
	u32 imp_errcode;
	पूर्णांक common_त्रुटि_सं;
पूर्ण;

अटल व्योम hclgevf_cmd_copy_desc(काष्ठा hclgevf_hw *hw,
				  काष्ठा hclgevf_desc *desc, पूर्णांक num)
अणु
	काष्ठा hclgevf_desc *desc_to_use;
	पूर्णांक handle = 0;

	जबतक (handle < num) अणु
		desc_to_use = &hw->cmq.csq.desc[hw->cmq.csq.next_to_use];
		*desc_to_use = desc[handle];
		(hw->cmq.csq.next_to_use)++;
		अगर (hw->cmq.csq.next_to_use == hw->cmq.csq.desc_num)
			hw->cmq.csq.next_to_use = 0;
		handle++;
	पूर्ण
पूर्ण

अटल पूर्णांक hclgevf_cmd_convert_err_code(u16 desc_ret)
अणु
	काष्ठा vf_errcode hclgevf_cmd_errcode[] = अणु
		अणुHCLGEVF_CMD_EXEC_SUCCESS, 0पूर्ण,
		अणुHCLGEVF_CMD_NO_AUTH, -EPERMपूर्ण,
		अणुHCLGEVF_CMD_NOT_SUPPORTED, -EOPNOTSUPPपूर्ण,
		अणुHCLGEVF_CMD_QUEUE_FULL, -EXFULLपूर्ण,
		अणुHCLGEVF_CMD_NEXT_ERR, -ENOSRपूर्ण,
		अणुHCLGEVF_CMD_UNEXE_ERR, -ENOTBLKपूर्ण,
		अणुHCLGEVF_CMD_PARA_ERR, -EINVALपूर्ण,
		अणुHCLGEVF_CMD_RESULT_ERR, -दुस्फलपूर्ण,
		अणुHCLGEVF_CMD_TIMEOUT, -ETIMEपूर्ण,
		अणुHCLGEVF_CMD_HILINK_ERR, -ENOLINKपूर्ण,
		अणुHCLGEVF_CMD_QUEUE_ILLEGAL, -ENXIOपूर्ण,
		अणुHCLGEVF_CMD_INVALID, -EBADRपूर्ण,
	पूर्ण;
	u32 errcode_count = ARRAY_SIZE(hclgevf_cmd_errcode);
	u32 i;

	क्रम (i = 0; i < errcode_count; i++)
		अगर (hclgevf_cmd_errcode[i].imp_errcode == desc_ret)
			वापस hclgevf_cmd_errcode[i].common_त्रुटि_सं;

	वापस -EIO;
पूर्ण

अटल पूर्णांक hclgevf_cmd_check_retval(काष्ठा hclgevf_hw *hw,
				    काष्ठा hclgevf_desc *desc, पूर्णांक num, पूर्णांक ntc)
अणु
	u16 opcode, desc_ret;
	पूर्णांक handle;

	opcode = le16_to_cpu(desc[0].opcode);
	क्रम (handle = 0; handle < num; handle++) अणु
		/* Get the result of hardware ग_लिखो back */
		desc[handle] = hw->cmq.csq.desc[ntc];
		ntc++;
		अगर (ntc == hw->cmq.csq.desc_num)
			ntc = 0;
	पूर्ण
	अगर (likely(!hclgevf_is_special_opcode(opcode)))
		desc_ret = le16_to_cpu(desc[num - 1].retval);
	अन्यथा
		desc_ret = le16_to_cpu(desc[0].retval);
	hw->cmq.last_status = desc_ret;

	वापस hclgevf_cmd_convert_err_code(desc_ret);
पूर्ण

अटल पूर्णांक hclgevf_cmd_check_result(काष्ठा hclgevf_hw *hw,
				    काष्ठा hclgevf_desc *desc, पूर्णांक num, पूर्णांक ntc)
अणु
	काष्ठा hclgevf_dev *hdev = (काष्ठा hclgevf_dev *)hw->hdev;
	bool is_completed = false;
	u32 समयout = 0;
	पूर्णांक handle, ret;

	/* If the command is sync, रुको क्रम the firmware to ग_लिखो back,
	 * अगर multi descriptors to be sent, use the first one to check
	 */
	अगर (HCLGEVF_SEND_SYNC(le16_to_cpu(desc->flag))) अणु
		करो अणु
			अगर (hclgevf_cmd_csq_करोne(hw)) अणु
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
		ret = hclgevf_cmd_check_retval(hw, desc, num, ntc);

	/* Clean the command send queue */
	handle = hclgevf_cmd_csq_clean(hw);
	अगर (handle < 0)
		ret = handle;
	अन्यथा अगर (handle != num)
		dev_warn(&hdev->pdev->dev,
			 "cleaned %d, need to clean %d\n", handle, num);
	वापस ret;
पूर्ण

/* hclgevf_cmd_send - send command to command queue
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @desc: prefilled descriptor क्रम describing the command
 * @num : the number of descriptors to be sent
 *
 * This is the मुख्य send command क्रम command queue, it
 * sends the queue, cleans the queue, etc
 */
पूर्णांक hclgevf_cmd_send(काष्ठा hclgevf_hw *hw, काष्ठा hclgevf_desc *desc, पूर्णांक num)
अणु
	काष्ठा hclgevf_dev *hdev = (काष्ठा hclgevf_dev *)hw->hdev;
	काष्ठा hclgevf_cmq_ring *csq = &hw->cmq.csq;
	पूर्णांक ret;
	पूर्णांक ntc;

	spin_lock_bh(&hw->cmq.csq.lock);

	अगर (test_bit(HCLGEVF_STATE_CMD_DISABLE, &hdev->state)) अणु
		spin_unlock_bh(&hw->cmq.csq.lock);
		वापस -EBUSY;
	पूर्ण

	अगर (num > hclgevf_ring_space(&hw->cmq.csq)) अणु
		/* If CMDQ ring is full, SW HEAD and HW HEAD may be dअगरferent,
		 * need update the SW HEAD poपूर्णांकer csq->next_to_clean
		 */
		csq->next_to_clean = hclgevf_पढ़ो_dev(hw,
						      HCLGEVF_NIC_CSQ_HEAD_REG);
		spin_unlock_bh(&hw->cmq.csq.lock);
		वापस -EBUSY;
	पूर्ण

	/* Record the location of desc in the ring क्रम this समय
	 * which will be use क्रम hardware to ग_लिखो back
	 */
	ntc = hw->cmq.csq.next_to_use;

	hclgevf_cmd_copy_desc(hw, desc, num);

	/* Write to hardware */
	hclgevf_ग_लिखो_dev(hw, HCLGEVF_NIC_CSQ_TAIL_REG,
			  hw->cmq.csq.next_to_use);

	ret = hclgevf_cmd_check_result(hw, desc, num, ntc);

	spin_unlock_bh(&hw->cmq.csq.lock);

	वापस ret;
पूर्ण

अटल व्योम hclgevf_set_शेष_capability(काष्ठा hclgevf_dev *hdev)
अणु
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(hdev->pdev);

	set_bit(HNAE3_DEV_SUPPORT_FD_B, ae_dev->caps);
	set_bit(HNAE3_DEV_SUPPORT_GRO_B, ae_dev->caps);
	set_bit(HNAE3_DEV_SUPPORT_FEC_B, ae_dev->caps);
पूर्ण

अटल व्योम hclgevf_parse_capability(काष्ठा hclgevf_dev *hdev,
				     काष्ठा hclgevf_query_version_cmd *cmd)
अणु
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(hdev->pdev);
	u32 caps;

	caps = __le32_to_cpu(cmd->caps[0]);
	अगर (hnae3_get_bit(caps, HCLGEVF_CAP_UDP_GSO_B))
		set_bit(HNAE3_DEV_SUPPORT_UDP_GSO_B, ae_dev->caps);
	अगर (hnae3_get_bit(caps, HCLGEVF_CAP_INT_QL_B))
		set_bit(HNAE3_DEV_SUPPORT_INT_QL_B, ae_dev->caps);
	अगर (hnae3_get_bit(caps, HCLGEVF_CAP_TQP_TXRX_INDEP_B))
		set_bit(HNAE3_DEV_SUPPORT_TQP_TXRX_INDEP_B, ae_dev->caps);
	अगर (hnae3_get_bit(caps, HCLGEVF_CAP_HW_TX_CSUM_B))
		set_bit(HNAE3_DEV_SUPPORT_HW_TX_CSUM_B, ae_dev->caps);
	अगर (hnae3_get_bit(caps, HCLGEVF_CAP_UDP_TUNNEL_CSUM_B))
		set_bit(HNAE3_DEV_SUPPORT_UDP_TUNNEL_CSUM_B, ae_dev->caps);
पूर्ण

अटल __le32 hclgevf_build_api_caps(व्योम)
अणु
	u32 api_caps = 0;

	hnae3_set_bit(api_caps, HCLGEVF_API_CAP_FLEX_RSS_TBL_B, 1);

	वापस cpu_to_le32(api_caps);
पूर्ण

अटल पूर्णांक hclgevf_cmd_query_version_and_capability(काष्ठा hclgevf_dev *hdev)
अणु
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(hdev->pdev);
	काष्ठा hclgevf_query_version_cmd *resp;
	काष्ठा hclgevf_desc desc;
	पूर्णांक status;

	resp = (काष्ठा hclgevf_query_version_cmd *)desc.data;

	hclgevf_cmd_setup_basic_desc(&desc, HCLGEVF_OPC_QUERY_FW_VER, 1);
	resp->api_caps = hclgevf_build_api_caps();
	status = hclgevf_cmd_send(&hdev->hw, &desc, 1);
	अगर (status)
		वापस status;

	hdev->fw_version = le32_to_cpu(resp->firmware);

	ae_dev->dev_version = le32_to_cpu(resp->hardware) <<
				 HNAE3_PCI_REVISION_BIT_SIZE;
	ae_dev->dev_version |= hdev->pdev->revision;

	अगर (ae_dev->dev_version >= HNAE3_DEVICE_VERSION_V2)
		hclgevf_set_शेष_capability(hdev);

	hclgevf_parse_capability(hdev, resp);

	वापस status;
पूर्ण

पूर्णांक hclgevf_cmd_queue_init(काष्ठा hclgevf_dev *hdev)
अणु
	पूर्णांक ret;

	/* Setup the lock क्रम command queue */
	spin_lock_init(&hdev->hw.cmq.csq.lock);
	spin_lock_init(&hdev->hw.cmq.crq.lock);

	hdev->hw.cmq.tx_समयout = HCLGEVF_CMDQ_TX_TIMEOUT;
	hdev->hw.cmq.csq.desc_num = HCLGEVF_NIC_CMQ_DESC_NUM;
	hdev->hw.cmq.crq.desc_num = HCLGEVF_NIC_CMQ_DESC_NUM;

	ret = hclgevf_alloc_cmd_queue(hdev, HCLGEVF_TYPE_CSQ);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"CSQ ring setup error %d\n", ret);
		वापस ret;
	पूर्ण

	ret = hclgevf_alloc_cmd_queue(hdev, HCLGEVF_TYPE_CRQ);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"CRQ ring setup error %d\n", ret);
		जाओ err_csq;
	पूर्ण

	वापस 0;
err_csq:
	hclgevf_मुक्त_cmd_desc(&hdev->hw.cmq.csq);
	वापस ret;
पूर्ण

पूर्णांक hclgevf_cmd_init(काष्ठा hclgevf_dev *hdev)
अणु
	पूर्णांक ret;

	spin_lock_bh(&hdev->hw.cmq.csq.lock);
	spin_lock(&hdev->hw.cmq.crq.lock);

	/* initialize the poपूर्णांकers of async rx queue of mailbox */
	hdev->arq.hdev = hdev;
	hdev->arq.head = 0;
	hdev->arq.tail = 0;
	atomic_set(&hdev->arq.count, 0);
	hdev->hw.cmq.csq.next_to_clean = 0;
	hdev->hw.cmq.csq.next_to_use = 0;
	hdev->hw.cmq.crq.next_to_clean = 0;
	hdev->hw.cmq.crq.next_to_use = 0;

	hclgevf_cmd_init_regs(&hdev->hw);

	spin_unlock(&hdev->hw.cmq.crq.lock);
	spin_unlock_bh(&hdev->hw.cmq.csq.lock);

	clear_bit(HCLGEVF_STATE_CMD_DISABLE, &hdev->state);

	/* Check अगर there is new reset pending, because the higher level
	 * reset may happen when lower level reset is being processed.
	 */
	अगर (hclgevf_is_reset_pending(hdev)) अणु
		ret = -EBUSY;
		जाओ err_cmd_init;
	पूर्ण

	/* get version and device capabilities */
	ret = hclgevf_cmd_query_version_and_capability(hdev);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"failed to query version and capabilities, ret = %d\n", ret);
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

	वापस 0;

err_cmd_init:
	set_bit(HCLGEVF_STATE_CMD_DISABLE, &hdev->state);

	वापस ret;
पूर्ण

अटल व्योम hclgevf_cmd_uninit_regs(काष्ठा hclgevf_hw *hw)
अणु
	hclgevf_ग_लिखो_dev(hw, HCLGEVF_NIC_CSQ_BASEADDR_L_REG, 0);
	hclgevf_ग_लिखो_dev(hw, HCLGEVF_NIC_CSQ_BASEADDR_H_REG, 0);
	hclgevf_ग_लिखो_dev(hw, HCLGEVF_NIC_CSQ_DEPTH_REG, 0);
	hclgevf_ग_लिखो_dev(hw, HCLGEVF_NIC_CSQ_HEAD_REG, 0);
	hclgevf_ग_लिखो_dev(hw, HCLGEVF_NIC_CSQ_TAIL_REG, 0);
	hclgevf_ग_लिखो_dev(hw, HCLGEVF_NIC_CRQ_BASEADDR_L_REG, 0);
	hclgevf_ग_लिखो_dev(hw, HCLGEVF_NIC_CRQ_BASEADDR_H_REG, 0);
	hclgevf_ग_लिखो_dev(hw, HCLGEVF_NIC_CRQ_DEPTH_REG, 0);
	hclgevf_ग_लिखो_dev(hw, HCLGEVF_NIC_CRQ_HEAD_REG, 0);
	hclgevf_ग_लिखो_dev(hw, HCLGEVF_NIC_CRQ_TAIL_REG, 0);
पूर्ण

व्योम hclgevf_cmd_uninit(काष्ठा hclgevf_dev *hdev)
अणु
	spin_lock_bh(&hdev->hw.cmq.csq.lock);
	spin_lock(&hdev->hw.cmq.crq.lock);
	set_bit(HCLGEVF_STATE_CMD_DISABLE, &hdev->state);
	hclgevf_cmd_uninit_regs(&hdev->hw);
	spin_unlock(&hdev->hw.cmq.crq.lock);
	spin_unlock_bh(&hdev->hw.cmq.csq.lock);
	hclgevf_मुक्त_cmd_desc(&hdev->hw.cmq.csq);
	hclgevf_मुक्त_cmd_desc(&hdev->hw.cmq.crq);
पूर्ण
