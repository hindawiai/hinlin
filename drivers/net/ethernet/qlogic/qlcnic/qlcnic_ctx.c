<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic qlcnic NIC Driver
 * Copyright (c) 2009-2013 QLogic Corporation
 */

#समावेश "qlcnic.h"

अटल स्थिर काष्ठा qlcnic_mailbox_metadata qlcnic_mbx_tbl[] = अणु
	अणुQLCNIC_CMD_CREATE_RX_CTX, 4, 1पूर्ण,
	अणुQLCNIC_CMD_DESTROY_RX_CTX, 2, 1पूर्ण,
	अणुQLCNIC_CMD_CREATE_TX_CTX, 4, 1पूर्ण,
	अणुQLCNIC_CMD_DESTROY_TX_CTX, 3, 1पूर्ण,
	अणुQLCNIC_CMD_INTRPT_TEST, 4, 1पूर्ण,
	अणुQLCNIC_CMD_SET_MTU, 4, 1पूर्ण,
	अणुQLCNIC_CMD_READ_PHY, 4, 2पूर्ण,
	अणुQLCNIC_CMD_WRITE_PHY, 5, 1पूर्ण,
	अणुQLCNIC_CMD_READ_HW_REG, 4, 1पूर्ण,
	अणुQLCNIC_CMD_GET_FLOW_CTL, 4, 2पूर्ण,
	अणुQLCNIC_CMD_SET_FLOW_CTL, 4, 1पूर्ण,
	अणुQLCNIC_CMD_READ_MAX_MTU, 4, 2पूर्ण,
	अणुQLCNIC_CMD_READ_MAX_LRO, 4, 2पूर्ण,
	अणुQLCNIC_CMD_MAC_ADDRESS, 4, 3पूर्ण,
	अणुQLCNIC_CMD_GET_PCI_INFO, 4, 1पूर्ण,
	अणुQLCNIC_CMD_GET_NIC_INFO, 4, 1पूर्ण,
	अणुQLCNIC_CMD_SET_NIC_INFO, 4, 1पूर्ण,
	अणुQLCNIC_CMD_GET_ESWITCH_CAPABILITY, 4, 3पूर्ण,
	अणुQLCNIC_CMD_TOGGLE_ESWITCH, 4, 1पूर्ण,
	अणुQLCNIC_CMD_GET_ESWITCH_STATUS, 4, 3पूर्ण,
	अणुQLCNIC_CMD_SET_PORTMIRRORING, 4, 1पूर्ण,
	अणुQLCNIC_CMD_CONFIGURE_ESWITCH, 4, 1पूर्ण,
	अणुQLCNIC_CMD_GET_MAC_STATS, 4, 1पूर्ण,
	अणुQLCNIC_CMD_GET_ESWITCH_PORT_CONFIG, 4, 3पूर्ण,
	अणुQLCNIC_CMD_GET_ESWITCH_STATS, 4, 1पूर्ण,
	अणुQLCNIC_CMD_CONFIG_PORT, 4, 1पूर्ण,
	अणुQLCNIC_CMD_TEMP_SIZE, 4, 4पूर्ण,
	अणुQLCNIC_CMD_GET_TEMP_HDR, 4, 1पूर्ण,
	अणुQLCNIC_CMD_82XX_SET_DRV_VER, 4, 1पूर्ण,
	अणुQLCNIC_CMD_GET_LED_STATUS, 4, 2पूर्ण,
	अणुQLCNIC_CMD_MQ_TX_CONFIG_INTR, 2, 3पूर्ण,
	अणुQLCNIC_CMD_DCB_QUERY_CAP, 1, 2पूर्ण,
	अणुQLCNIC_CMD_DCB_QUERY_PARAM, 4, 1पूर्ण,
पूर्ण;

अटल अंतरभूत u32 qlcnic_get_cmd_signature(काष्ठा qlcnic_hardware_context *ahw)
अणु
	वापस (ahw->pci_func & 0xff) | ((ahw->fw_hal_version & 0xff) << 8) |
	       (0xcafe << 16);
पूर्ण

/* Allocate mailbox रेजिस्टरs */
पूर्णांक qlcnic_82xx_alloc_mbx_args(काष्ठा qlcnic_cmd_args *mbx,
			       काष्ठा qlcnic_adapter *adapter, u32 type)
अणु
	पूर्णांक i, size;
	स्थिर काष्ठा qlcnic_mailbox_metadata *mbx_tbl;

	mbx_tbl = qlcnic_mbx_tbl;
	size = ARRAY_SIZE(qlcnic_mbx_tbl);
	क्रम (i = 0; i < size; i++) अणु
		अगर (type == mbx_tbl[i].cmd) अणु
			mbx->req.num = mbx_tbl[i].in_args;
			mbx->rsp.num = mbx_tbl[i].out_args;
			mbx->req.arg = kसुस्मृति(mbx->req.num,
					       माप(u32), GFP_ATOMIC);
			अगर (!mbx->req.arg)
				वापस -ENOMEM;
			mbx->rsp.arg = kसुस्मृति(mbx->rsp.num,
					       माप(u32), GFP_ATOMIC);
			अगर (!mbx->rsp.arg) अणु
				kमुक्त(mbx->req.arg);
				mbx->req.arg = शून्य;
				वापस -ENOMEM;
			पूर्ण
			mbx->req.arg[0] = type;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* Free up mailbox रेजिस्टरs */
व्योम qlcnic_मुक्त_mbx_args(काष्ठा qlcnic_cmd_args *cmd)
अणु
	kमुक्त(cmd->req.arg);
	cmd->req.arg = शून्य;
	kमुक्त(cmd->rsp.arg);
	cmd->rsp.arg = शून्य;
पूर्ण

अटल u32
qlcnic_poll_rsp(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 rsp;
	पूर्णांक समयout = 0, err = 0;

	करो अणु
		/* give atleast 1ms क्रम firmware to respond */
		mdelay(1);

		अगर (++समयout > QLCNIC_OS_CRB_RETRY_COUNT)
			वापस QLCNIC_CDRP_RSP_TIMEOUT;

		rsp = QLCRD32(adapter, QLCNIC_CDRP_CRB_OFFSET, &err);
	पूर्ण जबतक (!QLCNIC_CDRP_IS_RSP(rsp));

	वापस rsp;
पूर्ण

पूर्णांक qlcnic_82xx_issue_cmd(काष्ठा qlcnic_adapter *adapter,
			  काष्ठा qlcnic_cmd_args *cmd)
अणु
	पूर्णांक i, err = 0;
	u32 rsp;
	u32 signature;
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	स्थिर अक्षर *fmt;

	signature = qlcnic_get_cmd_signature(ahw);

	/* Acquire semaphore beक्रमe accessing CRB */
	अगर (qlcnic_api_lock(adapter)) अणु
		cmd->rsp.arg[0] = QLCNIC_RCODE_TIMEOUT;
		वापस cmd->rsp.arg[0];
	पूर्ण

	QLCWR32(adapter, QLCNIC_SIGN_CRB_OFFSET, signature);
	क्रम (i = 1; i < cmd->req.num; i++)
		QLCWR32(adapter, QLCNIC_CDRP_ARG(i), cmd->req.arg[i]);
	QLCWR32(adapter, QLCNIC_CDRP_CRB_OFFSET,
		QLCNIC_CDRP_FORM_CMD(cmd->req.arg[0]));
	rsp = qlcnic_poll_rsp(adapter);

	अगर (rsp == QLCNIC_CDRP_RSP_TIMEOUT) अणु
		dev_err(&pdev->dev, "command timeout, response = 0x%x\n", rsp);
		cmd->rsp.arg[0] = QLCNIC_RCODE_TIMEOUT;
	पूर्ण अन्यथा अगर (rsp == QLCNIC_CDRP_RSP_FAIL) अणु
		cmd->rsp.arg[0] = QLCRD32(adapter, QLCNIC_CDRP_ARG(1), &err);
		चयन (cmd->rsp.arg[0]) अणु
		हाल QLCNIC_RCODE_INVALID_ARGS:
			fmt = "CDRP invalid args: [%d]\n";
			अवरोध;
		हाल QLCNIC_RCODE_NOT_SUPPORTED:
		हाल QLCNIC_RCODE_NOT_IMPL:
			fmt = "CDRP command not supported: [%d]\n";
			अवरोध;
		हाल QLCNIC_RCODE_NOT_PERMITTED:
			fmt = "CDRP requested action not permitted: [%d]\n";
			अवरोध;
		हाल QLCNIC_RCODE_INVALID:
			fmt = "CDRP invalid or unknown cmd received: [%d]\n";
			अवरोध;
		हाल QLCNIC_RCODE_TIMEOUT:
			fmt = "CDRP command timeout: [%d]\n";
			अवरोध;
		शेष:
			fmt = "CDRP command failed: [%d]\n";
			अवरोध;
		पूर्ण
		dev_err(&pdev->dev, fmt, cmd->rsp.arg[0]);
		qlcnic_dump_mbx(adapter, cmd);
	पूर्ण अन्यथा अगर (rsp == QLCNIC_CDRP_RSP_OK)
		cmd->rsp.arg[0] = QLCNIC_RCODE_SUCCESS;

	क्रम (i = 1; i < cmd->rsp.num; i++)
		cmd->rsp.arg[i] = QLCRD32(adapter, QLCNIC_CDRP_ARG(i), &err);

	/* Release semaphore */
	qlcnic_api_unlock(adapter);
	वापस cmd->rsp.arg[0];
पूर्ण

पूर्णांक qlcnic_fw_cmd_set_drv_version(काष्ठा qlcnic_adapter *adapter, u32 fw_cmd)
अणु
	काष्ठा qlcnic_cmd_args cmd;
	u32 arg1, arg2, arg3;
	अक्षर drv_string[12];
	पूर्णांक err = 0;

	स_रखो(drv_string, 0, माप(drv_string));
	snम_लिखो(drv_string, माप(drv_string), "%d"".""%d"".""%d",
		 _QLCNIC_LINUX_MAJOR, _QLCNIC_LINUX_MINOR,
		 _QLCNIC_LINUX_SUBVERSION);

	err = qlcnic_alloc_mbx_args(&cmd, adapter, fw_cmd);
	अगर (err)
		वापस err;

	स_नकल(&arg1, drv_string, माप(u32));
	स_नकल(&arg2, drv_string + 4, माप(u32));
	स_नकल(&arg3, drv_string + 8, माप(u32));

	cmd.req.arg[1] = arg1;
	cmd.req.arg[2] = arg2;
	cmd.req.arg[3] = arg3;

	err = qlcnic_issue_cmd(adapter, &cmd);
	अगर (err) अणु
		dev_info(&adapter->pdev->dev,
			 "Failed to set driver version in firmware\n");
		err = -EIO;
	पूर्ण
	qlcnic_मुक्त_mbx_args(&cmd);
	वापस err;
पूर्ण

पूर्णांक
qlcnic_fw_cmd_set_mtu(काष्ठा qlcnic_adapter *adapter, पूर्णांक mtu)
अणु
	पूर्णांक err = 0;
	काष्ठा qlcnic_cmd_args cmd;
	काष्ठा qlcnic_recv_context *recv_ctx = adapter->recv_ctx;

	अगर (recv_ctx->state != QLCNIC_HOST_CTX_STATE_ACTIVE)
		वापस err;
	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_SET_MTU);
	अगर (err)
		वापस err;

	cmd.req.arg[1] = recv_ctx->context_id;
	cmd.req.arg[2] = mtu;

	err = qlcnic_issue_cmd(adapter, &cmd);
	अगर (err) अणु
		dev_err(&adapter->pdev->dev, "Failed to set mtu\n");
		err = -EIO;
	पूर्ण
	qlcnic_मुक्त_mbx_args(&cmd);
	वापस err;
पूर्ण

पूर्णांक qlcnic_82xx_fw_cmd_create_rx_ctx(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_recv_context *recv_ctx = adapter->recv_ctx;
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	dma_addr_t hostrq_phys_addr, cardrsp_phys_addr;
	काष्ठा net_device *netdev = adapter->netdev;
	u32 temp_पूर्णांकr_crb_mode, temp_rds_crb_mode;
	काष्ठा qlcnic_cardrsp_rds_ring *prsp_rds;
	काष्ठा qlcnic_cardrsp_sds_ring *prsp_sds;
	काष्ठा qlcnic_hostrq_rds_ring *prq_rds;
	काष्ठा qlcnic_hostrq_sds_ring *prq_sds;
	काष्ठा qlcnic_host_rds_ring *rds_ring;
	काष्ठा qlcnic_host_sds_ring *sds_ring;
	काष्ठा qlcnic_cardrsp_rx_ctx *prsp;
	काष्ठा qlcnic_hostrq_rx_ctx *prq;
	u8 i, nrds_rings, nsds_rings;
	काष्ठा qlcnic_cmd_args cmd;
	माप_प्रकार rq_size, rsp_size;
	u32 cap, reg, val, reg2;
	u64 phys_addr;
	u16 temp_u16;
	व्योम *addr;
	पूर्णांक err;

	nrds_rings = adapter->max_rds_rings;
	nsds_rings = adapter->drv_sds_rings;

	rq_size = SIZखातापूर्ण_HOSTRQ_RX(काष्ठा qlcnic_hostrq_rx_ctx, nrds_rings,
				   nsds_rings);
	rsp_size = SIZखातापूर्ण_CARDRSP_RX(काष्ठा qlcnic_cardrsp_rx_ctx, nrds_rings,
				     nsds_rings);

	addr = dma_alloc_coherent(&adapter->pdev->dev, rq_size,
				  &hostrq_phys_addr, GFP_KERNEL);
	अगर (addr == शून्य)
		वापस -ENOMEM;
	prq = addr;

	addr = dma_alloc_coherent(&adapter->pdev->dev, rsp_size,
			&cardrsp_phys_addr, GFP_KERNEL);
	अगर (addr == शून्य) अणु
		err = -ENOMEM;
		जाओ out_मुक्त_rq;
	पूर्ण
	prsp = addr;

	prq->host_rsp_dma_addr = cpu_to_le64(cardrsp_phys_addr);

	cap = (QLCNIC_CAP0_LEGACY_CONTEXT | QLCNIC_CAP0_LEGACY_MN
						| QLCNIC_CAP0_VALIDOFF);
	cap |= (QLCNIC_CAP0_JUMBO_CONTIGUOUS | QLCNIC_CAP0_LRO_CONTIGUOUS);

	अगर (qlcnic_check_multi_tx(adapter) &&
	    !adapter->ahw->diag_test) अणु
		cap |= QLCNIC_CAP0_TX_MULTI;
	पूर्ण अन्यथा अणु
		temp_u16 = दुरत्व(काष्ठा qlcnic_hostrq_rx_ctx, msix_handler);
		prq->valid_field_offset = cpu_to_le16(temp_u16);
		prq->txrx_sds_binding = nsds_rings - 1;
		temp_पूर्णांकr_crb_mode = QLCNIC_HOST_INT_CRB_MODE_SHARED;
		prq->host_पूर्णांक_crb_mode = cpu_to_le32(temp_पूर्णांकr_crb_mode);
		temp_rds_crb_mode = QLCNIC_HOST_RDS_CRB_MODE_UNIQUE;
		prq->host_rds_crb_mode = cpu_to_le32(temp_rds_crb_mode);
	पूर्ण

	prq->capabilities[0] = cpu_to_le32(cap);

	prq->num_rds_rings = cpu_to_le16(nrds_rings);
	prq->num_sds_rings = cpu_to_le16(nsds_rings);
	prq->rds_ring_offset = 0;

	val = le32_to_cpu(prq->rds_ring_offset) +
		(माप(काष्ठा qlcnic_hostrq_rds_ring) * nrds_rings);
	prq->sds_ring_offset = cpu_to_le32(val);

	prq_rds = (काष्ठा qlcnic_hostrq_rds_ring *)(prq->data +
			le32_to_cpu(prq->rds_ring_offset));

	क्रम (i = 0; i < nrds_rings; i++) अणु
		rds_ring = &recv_ctx->rds_rings[i];
		rds_ring->producer = 0;
		prq_rds[i].host_phys_addr = cpu_to_le64(rds_ring->phys_addr);
		prq_rds[i].ring_size = cpu_to_le32(rds_ring->num_desc);
		prq_rds[i].ring_kind = cpu_to_le32(i);
		prq_rds[i].buff_size = cpu_to_le64(rds_ring->dma_size);
	पूर्ण

	prq_sds = (काष्ठा qlcnic_hostrq_sds_ring *)(prq->data +
			le32_to_cpu(prq->sds_ring_offset));

	क्रम (i = 0; i < nsds_rings; i++) अणु
		sds_ring = &recv_ctx->sds_rings[i];
		sds_ring->consumer = 0;
		स_रखो(sds_ring->desc_head, 0, STATUS_DESC_RINGSIZE(sds_ring));
		prq_sds[i].host_phys_addr = cpu_to_le64(sds_ring->phys_addr);
		prq_sds[i].ring_size = cpu_to_le32(sds_ring->num_desc);
		अगर (qlcnic_check_multi_tx(adapter) &&
		    !adapter->ahw->diag_test)
			prq_sds[i].msi_index = cpu_to_le16(ahw->पूर्णांकr_tbl[i].id);
		अन्यथा
			prq_sds[i].msi_index = cpu_to_le16(i);
	पूर्ण

	phys_addr = hostrq_phys_addr;
	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_CREATE_RX_CTX);
	अगर (err)
		जाओ out_मुक्त_rsp;

	cmd.req.arg[1] = MSD(phys_addr);
	cmd.req.arg[2] = LSD(phys_addr);
	cmd.req.arg[3] = rq_size;
	err = qlcnic_issue_cmd(adapter, &cmd);
	अगर (err) अणु
		dev_err(&adapter->pdev->dev,
			"Failed to create rx ctx in firmware%d\n", err);
		जाओ out_मुक्त_rsp;
	पूर्ण

	prsp_rds = ((काष्ठा qlcnic_cardrsp_rds_ring *)
			 &prsp->data[le32_to_cpu(prsp->rds_ring_offset)]);

	क्रम (i = 0; i < le16_to_cpu(prsp->num_rds_rings); i++) अणु
		rds_ring = &recv_ctx->rds_rings[i];
		reg = le32_to_cpu(prsp_rds[i].host_producer_crb);
		rds_ring->crb_rcv_producer = ahw->pci_base0 + reg;
	पूर्ण

	prsp_sds = ((काष्ठा qlcnic_cardrsp_sds_ring *)
			&prsp->data[le32_to_cpu(prsp->sds_ring_offset)]);

	क्रम (i = 0; i < le16_to_cpu(prsp->num_sds_rings); i++) अणु
		sds_ring = &recv_ctx->sds_rings[i];
		reg = le32_to_cpu(prsp_sds[i].host_consumer_crb);
		अगर (qlcnic_check_multi_tx(adapter) && !adapter->ahw->diag_test)
			reg2 = ahw->पूर्णांकr_tbl[i].src;
		अन्यथा
			reg2 = le32_to_cpu(prsp_sds[i].पूर्णांकerrupt_crb);

		sds_ring->crb_पूर्णांकr_mask = ahw->pci_base0 + reg2;
		sds_ring->crb_sts_consumer = ahw->pci_base0 + reg;
	पूर्ण

	recv_ctx->state = le32_to_cpu(prsp->host_ctx_state);
	recv_ctx->context_id = le16_to_cpu(prsp->context_id);
	recv_ctx->virt_port = prsp->virt_port;

	netdev_info(netdev, "Rx Context[%d] Created, state 0x%x\n",
		    recv_ctx->context_id, recv_ctx->state);
	qlcnic_मुक्त_mbx_args(&cmd);

out_मुक्त_rsp:
	dma_मुक्त_coherent(&adapter->pdev->dev, rsp_size, prsp,
			  cardrsp_phys_addr);
out_मुक्त_rq:
	dma_मुक्त_coherent(&adapter->pdev->dev, rq_size, prq, hostrq_phys_addr);

	वापस err;
पूर्ण

व्योम qlcnic_82xx_fw_cmd_del_rx_ctx(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक err;
	काष्ठा qlcnic_cmd_args cmd;
	काष्ठा qlcnic_recv_context *recv_ctx = adapter->recv_ctx;

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_DESTROY_RX_CTX);
	अगर (err)
		वापस;

	cmd.req.arg[1] = recv_ctx->context_id;
	err = qlcnic_issue_cmd(adapter, &cmd);
	अगर (err)
		dev_err(&adapter->pdev->dev,
			"Failed to destroy rx ctx in firmware\n");

	recv_ctx->state = QLCNIC_HOST_CTX_STATE_FREED;
	qlcnic_मुक्त_mbx_args(&cmd);
पूर्ण

पूर्णांक qlcnic_82xx_fw_cmd_create_tx_ctx(काष्ठा qlcnic_adapter *adapter,
				     काष्ठा qlcnic_host_tx_ring *tx_ring,
				     पूर्णांक ring)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा qlcnic_hostrq_tx_ctx	*prq;
	काष्ठा qlcnic_hostrq_cds_ring	*prq_cds;
	काष्ठा qlcnic_cardrsp_tx_ctx	*prsp;
	काष्ठा qlcnic_cmd_args cmd;
	u32 temp, पूर्णांकr_mask, temp_पूर्णांक_crb_mode;
	dma_addr_t rq_phys_addr, rsp_phys_addr;
	पूर्णांक temp_nsds_rings, index, err;
	व्योम *rq_addr, *rsp_addr;
	माप_प्रकार rq_size, rsp_size;
	u64 phys_addr;
	u16 msix_id;

	/* reset host resources */
	tx_ring->producer = 0;
	tx_ring->sw_consumer = 0;
	*(tx_ring->hw_consumer) = 0;

	rq_size = SIZखातापूर्ण_HOSTRQ_TX(काष्ठा qlcnic_hostrq_tx_ctx);
	rq_addr = dma_alloc_coherent(&adapter->pdev->dev, rq_size,
				     &rq_phys_addr, GFP_KERNEL);
	अगर (!rq_addr)
		वापस -ENOMEM;

	rsp_size = SIZखातापूर्ण_CARDRSP_TX(काष्ठा qlcnic_cardrsp_tx_ctx);
	rsp_addr = dma_alloc_coherent(&adapter->pdev->dev, rsp_size,
				      &rsp_phys_addr, GFP_KERNEL);
	अगर (!rsp_addr) अणु
		err = -ENOMEM;
		जाओ out_मुक्त_rq;
	पूर्ण

	prq = rq_addr;
	prsp = rsp_addr;

	prq->host_rsp_dma_addr = cpu_to_le64(rsp_phys_addr);

	temp = (QLCNIC_CAP0_LEGACY_CONTEXT | QLCNIC_CAP0_LEGACY_MN |
		QLCNIC_CAP0_LSO);
	अगर (qlcnic_check_multi_tx(adapter) && !adapter->ahw->diag_test)
		temp |= QLCNIC_CAP0_TX_MULTI;

	prq->capabilities[0] = cpu_to_le32(temp);

	अगर (qlcnic_check_multi_tx(adapter) &&
	    !adapter->ahw->diag_test) अणु
		temp_nsds_rings = adapter->drv_sds_rings;
		index = temp_nsds_rings + ring;
		msix_id = ahw->पूर्णांकr_tbl[index].id;
		prq->msi_index = cpu_to_le16(msix_id);
	पूर्ण अन्यथा अणु
		temp_पूर्णांक_crb_mode = QLCNIC_HOST_INT_CRB_MODE_SHARED;
		prq->host_पूर्णांक_crb_mode = cpu_to_le32(temp_पूर्णांक_crb_mode);
		prq->msi_index = 0;
	पूर्ण

	prq->पूर्णांकerrupt_ctl = 0;
	prq->cmd_cons_dma_addr = cpu_to_le64(tx_ring->hw_cons_phys_addr);

	prq_cds = &prq->cds_ring;

	prq_cds->host_phys_addr = cpu_to_le64(tx_ring->phys_addr);
	prq_cds->ring_size = cpu_to_le32(tx_ring->num_desc);

	phys_addr = rq_phys_addr;

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_CREATE_TX_CTX);
	अगर (err)
		जाओ out_मुक्त_rsp;

	cmd.req.arg[1] = MSD(phys_addr);
	cmd.req.arg[2] = LSD(phys_addr);
	cmd.req.arg[3] = rq_size;
	err = qlcnic_issue_cmd(adapter, &cmd);

	अगर (err == QLCNIC_RCODE_SUCCESS) अणु
		tx_ring->state = le32_to_cpu(prsp->host_ctx_state);
		temp = le32_to_cpu(prsp->cds_ring.host_producer_crb);
		tx_ring->crb_cmd_producer = adapter->ahw->pci_base0 + temp;
		tx_ring->ctx_id = le16_to_cpu(prsp->context_id);
		अगर (qlcnic_check_multi_tx(adapter) &&
		    !adapter->ahw->diag_test &&
		    (adapter->flags & QLCNIC_MSIX_ENABLED)) अणु
			index = adapter->drv_sds_rings + ring;
			पूर्णांकr_mask = ahw->पूर्णांकr_tbl[index].src;
			tx_ring->crb_पूर्णांकr_mask = ahw->pci_base0 + पूर्णांकr_mask;
		पूर्ण

		netdev_info(netdev, "Tx Context[0x%x] Created, state 0x%x\n",
			    tx_ring->ctx_id, tx_ring->state);
	पूर्ण अन्यथा अणु
		netdev_err(netdev, "Failed to create tx ctx in firmware%d\n",
			   err);
		err = -EIO;
	पूर्ण
	qlcnic_मुक्त_mbx_args(&cmd);

out_मुक्त_rsp:
	dma_मुक्त_coherent(&adapter->pdev->dev, rsp_size, rsp_addr,
			  rsp_phys_addr);
out_मुक्त_rq:
	dma_मुक्त_coherent(&adapter->pdev->dev, rq_size, rq_addr, rq_phys_addr);

	वापस err;
पूर्ण

व्योम qlcnic_82xx_fw_cmd_del_tx_ctx(काष्ठा qlcnic_adapter *adapter,
				   काष्ठा qlcnic_host_tx_ring *tx_ring)
अणु
	काष्ठा qlcnic_cmd_args cmd;
	पूर्णांक ret;

	ret = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_DESTROY_TX_CTX);
	अगर (ret)
		वापस;

	cmd.req.arg[1] = tx_ring->ctx_id;
	अगर (qlcnic_issue_cmd(adapter, &cmd))
		dev_err(&adapter->pdev->dev,
			"Failed to destroy tx ctx in firmware\n");
	qlcnic_मुक्त_mbx_args(&cmd);
पूर्ण

पूर्णांक
qlcnic_fw_cmd_set_port(काष्ठा qlcnic_adapter *adapter, u32 config)
अणु
	पूर्णांक err;
	काष्ठा qlcnic_cmd_args cmd;

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_CONFIG_PORT);
	अगर (err)
		वापस err;

	cmd.req.arg[1] = config;
	err = qlcnic_issue_cmd(adapter, &cmd);
	qlcnic_मुक्त_mbx_args(&cmd);
	वापस err;
पूर्ण

पूर्णांक qlcnic_alloc_hw_resources(काष्ठा qlcnic_adapter *adapter)
अणु
	व्योम *addr;
	पूर्णांक err, ring;
	काष्ठा qlcnic_recv_context *recv_ctx;
	काष्ठा qlcnic_host_rds_ring *rds_ring;
	काष्ठा qlcnic_host_sds_ring *sds_ring;
	काष्ठा qlcnic_host_tx_ring *tx_ring;
	__le32 *ptr;

	काष्ठा pci_dev *pdev = adapter->pdev;

	recv_ctx = adapter->recv_ctx;

	क्रम (ring = 0; ring < adapter->drv_tx_rings; ring++) अणु
		tx_ring = &adapter->tx_ring[ring];
		ptr = (__le32 *)dma_alloc_coherent(&pdev->dev, माप(u32),
						   &tx_ring->hw_cons_phys_addr,
						   GFP_KERNEL);
		अगर (ptr == शून्य) अणु
			err = -ENOMEM;
			जाओ err_out_मुक्त;
		पूर्ण

		tx_ring->hw_consumer = ptr;
		/* cmd desc ring */
		addr = dma_alloc_coherent(&pdev->dev, TX_DESC_RINGSIZE(tx_ring),
					  &tx_ring->phys_addr,
					  GFP_KERNEL);
		अगर (addr == शून्य) अणु
			err = -ENOMEM;
			जाओ err_out_मुक्त;
		पूर्ण

		tx_ring->desc_head = addr;
	पूर्ण

	क्रम (ring = 0; ring < adapter->max_rds_rings; ring++) अणु
		rds_ring = &recv_ctx->rds_rings[ring];
		addr = dma_alloc_coherent(&adapter->pdev->dev,
					  RCV_DESC_RINGSIZE(rds_ring),
					  &rds_ring->phys_addr, GFP_KERNEL);
		अगर (addr == शून्य) अणु
			err = -ENOMEM;
			जाओ err_out_मुक्त;
		पूर्ण
		rds_ring->desc_head = addr;

	पूर्ण

	क्रम (ring = 0; ring < adapter->drv_sds_rings; ring++) अणु
		sds_ring = &recv_ctx->sds_rings[ring];

		addr = dma_alloc_coherent(&adapter->pdev->dev,
					  STATUS_DESC_RINGSIZE(sds_ring),
					  &sds_ring->phys_addr, GFP_KERNEL);
		अगर (addr == शून्य) अणु
			err = -ENOMEM;
			जाओ err_out_मुक्त;
		पूर्ण
		sds_ring->desc_head = addr;
	पूर्ण

	वापस 0;

err_out_मुक्त:
	qlcnic_मुक्त_hw_resources(adapter);
	वापस err;
पूर्ण

पूर्णांक qlcnic_fw_create_ctx(काष्ठा qlcnic_adapter *dev)
अणु
	पूर्णांक i, err, ring;

	अगर (dev->flags & QLCNIC_NEED_FLR) अणु
		pci_reset_function(dev->pdev);
		dev->flags &= ~QLCNIC_NEED_FLR;
	पूर्ण

	अगर (qlcnic_83xx_check(dev) && (dev->flags & QLCNIC_MSIX_ENABLED)) अणु
		अगर (dev->ahw->diag_test != QLCNIC_LOOPBACK_TEST) अणु
			err = qlcnic_83xx_config_पूर्णांकrpt(dev, 1);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	अगर (qlcnic_82xx_check(dev) && (dev->flags & QLCNIC_MSIX_ENABLED) &&
	    qlcnic_check_multi_tx(dev) && !dev->ahw->diag_test) अणु
		err = qlcnic_82xx_mq_पूर्णांकrpt(dev, 1);
		अगर (err)
			वापस err;
	पूर्ण

	err = qlcnic_fw_cmd_create_rx_ctx(dev);
	अगर (err)
		जाओ err_out;

	क्रम (ring = 0; ring < dev->drv_tx_rings; ring++) अणु
		err = qlcnic_fw_cmd_create_tx_ctx(dev,
						  &dev->tx_ring[ring],
						  ring);
		अगर (err) अणु
			qlcnic_fw_cmd_del_rx_ctx(dev);
			अगर (ring == 0)
				जाओ err_out;

			क्रम (i = 0; i < ring; i++)
				qlcnic_fw_cmd_del_tx_ctx(dev, &dev->tx_ring[i]);

			जाओ err_out;
		पूर्ण
	पूर्ण

	set_bit(__QLCNIC_FW_ATTACHED, &dev->state);

	वापस 0;

err_out:
	अगर (qlcnic_82xx_check(dev) && (dev->flags & QLCNIC_MSIX_ENABLED) &&
	    qlcnic_check_multi_tx(dev) && !dev->ahw->diag_test)
			qlcnic_82xx_config_पूर्णांकrpt(dev, 0);

	अगर (qlcnic_83xx_check(dev) && (dev->flags & QLCNIC_MSIX_ENABLED)) अणु
		अगर (dev->ahw->diag_test != QLCNIC_LOOPBACK_TEST)
			qlcnic_83xx_config_पूर्णांकrpt(dev, 0);
	पूर्ण

	वापस err;
पूर्ण

व्योम qlcnic_fw_destroy_ctx(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक ring;

	अगर (test_and_clear_bit(__QLCNIC_FW_ATTACHED, &adapter->state)) अणु
		qlcnic_fw_cmd_del_rx_ctx(adapter);
		क्रम (ring = 0; ring < adapter->drv_tx_rings; ring++)
			qlcnic_fw_cmd_del_tx_ctx(adapter,
						 &adapter->tx_ring[ring]);

		अगर (qlcnic_82xx_check(adapter) &&
		    (adapter->flags & QLCNIC_MSIX_ENABLED) &&
		    qlcnic_check_multi_tx(adapter) &&
		    !adapter->ahw->diag_test)
				qlcnic_82xx_config_पूर्णांकrpt(adapter, 0);

		अगर (qlcnic_83xx_check(adapter) &&
		    (adapter->flags & QLCNIC_MSIX_ENABLED)) अणु
			अगर (adapter->ahw->diag_test != QLCNIC_LOOPBACK_TEST)
				qlcnic_83xx_config_पूर्णांकrpt(adapter, 0);
		पूर्ण
		/* Allow dma queues to drain after context reset */
		mdelay(20);
	पूर्ण
पूर्ण

व्योम qlcnic_मुक्त_hw_resources(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_recv_context *recv_ctx;
	काष्ठा qlcnic_host_rds_ring *rds_ring;
	काष्ठा qlcnic_host_sds_ring *sds_ring;
	काष्ठा qlcnic_host_tx_ring *tx_ring;
	पूर्णांक ring;

	recv_ctx = adapter->recv_ctx;

	क्रम (ring = 0; ring < adapter->drv_tx_rings; ring++) अणु
		tx_ring = &adapter->tx_ring[ring];
		अगर (tx_ring->hw_consumer != शून्य) अणु
			dma_मुक्त_coherent(&adapter->pdev->dev, माप(u32),
					  tx_ring->hw_consumer,
					  tx_ring->hw_cons_phys_addr);

			tx_ring->hw_consumer = शून्य;
		पूर्ण

		अगर (tx_ring->desc_head != शून्य) अणु
			dma_मुक्त_coherent(&adapter->pdev->dev,
					  TX_DESC_RINGSIZE(tx_ring),
					  tx_ring->desc_head,
					  tx_ring->phys_addr);
			tx_ring->desc_head = शून्य;
		पूर्ण
	पूर्ण

	क्रम (ring = 0; ring < adapter->max_rds_rings; ring++) अणु
		rds_ring = &recv_ctx->rds_rings[ring];

		अगर (rds_ring->desc_head != शून्य) अणु
			dma_मुक्त_coherent(&adapter->pdev->dev,
					RCV_DESC_RINGSIZE(rds_ring),
					rds_ring->desc_head,
					rds_ring->phys_addr);
			rds_ring->desc_head = शून्य;
		पूर्ण
	पूर्ण

	क्रम (ring = 0; ring < adapter->drv_sds_rings; ring++) अणु
		sds_ring = &recv_ctx->sds_rings[ring];

		अगर (sds_ring->desc_head != शून्य) अणु
			dma_मुक्त_coherent(&adapter->pdev->dev,
				STATUS_DESC_RINGSIZE(sds_ring),
				sds_ring->desc_head,
				sds_ring->phys_addr);
			sds_ring->desc_head = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक qlcnic_82xx_config_पूर्णांकrpt(काष्ठा qlcnic_adapter *adapter, u8 op_type)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा qlcnic_cmd_args cmd;
	u32 type, val;
	पूर्णांक i, err = 0;

	क्रम (i = 0; i < ahw->num_msix; i++) अणु
		err = qlcnic_alloc_mbx_args(&cmd, adapter,
					    QLCNIC_CMD_MQ_TX_CONFIG_INTR);
		अगर (err)
			वापस err;
		type = op_type ? QLCNIC_INTRPT_ADD : QLCNIC_INTRPT_DEL;
		val = type | (ahw->पूर्णांकr_tbl[i].type << 4);
		अगर (ahw->पूर्णांकr_tbl[i].type == QLCNIC_INTRPT_MSIX)
			val |= (ahw->पूर्णांकr_tbl[i].id << 16);
		cmd.req.arg[1] = val;
		err = qlcnic_issue_cmd(adapter, &cmd);
		अगर (err) अणु
			netdev_err(netdev, "Failed to %s interrupts %d\n",
				   op_type == QLCNIC_INTRPT_ADD ? "Add" :
				   "Delete", err);
			qlcnic_मुक्त_mbx_args(&cmd);
			वापस err;
		पूर्ण
		val = cmd.rsp.arg[1];
		अगर (LSB(val)) अणु
			netdev_info(netdev,
				    "failed to configure interrupt for %d\n",
				    ahw->पूर्णांकr_tbl[i].id);
			जारी;
		पूर्ण
		अगर (op_type) अणु
			ahw->पूर्णांकr_tbl[i].id = MSW(val);
			ahw->पूर्णांकr_tbl[i].enabled = 1;
			ahw->पूर्णांकr_tbl[i].src = cmd.rsp.arg[2];
		पूर्ण अन्यथा अणु
			ahw->पूर्णांकr_tbl[i].id = i;
			ahw->पूर्णांकr_tbl[i].enabled = 0;
			ahw->पूर्णांकr_tbl[i].src = 0;
		पूर्ण
		qlcnic_मुक्त_mbx_args(&cmd);
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक qlcnic_82xx_get_mac_address(काष्ठा qlcnic_adapter *adapter, u8 *mac,
				u8 function)
अणु
	पूर्णांक err, i;
	काष्ठा qlcnic_cmd_args cmd;
	u32 mac_low, mac_high;

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_MAC_ADDRESS);
	अगर (err)
		वापस err;

	cmd.req.arg[1] = function | BIT_8;
	err = qlcnic_issue_cmd(adapter, &cmd);

	अगर (err == QLCNIC_RCODE_SUCCESS) अणु
		mac_low = cmd.rsp.arg[1];
		mac_high = cmd.rsp.arg[2];

		क्रम (i = 0; i < 2; i++)
			mac[i] = (u8) (mac_high >> ((1 - i) * 8));
		क्रम (i = 2; i < 6; i++)
			mac[i] = (u8) (mac_low >> ((5 - i) * 8));
	पूर्ण अन्यथा अणु
		dev_err(&adapter->pdev->dev,
			"Failed to get mac address%d\n", err);
		err = -EIO;
	पूर्ण
	qlcnic_मुक्त_mbx_args(&cmd);
	वापस err;
पूर्ण

/* Get info of a NIC partition */
पूर्णांक qlcnic_82xx_get_nic_info(काष्ठा qlcnic_adapter *adapter,
			     काष्ठा qlcnic_info *npar_info, u8 func_id)
अणु
	पूर्णांक	err;
	dma_addr_t nic_dma_t;
	स्थिर काष्ठा qlcnic_info_le *nic_info;
	व्योम *nic_info_addr;
	काष्ठा qlcnic_cmd_args cmd;
	माप_प्रकार  nic_size = माप(काष्ठा qlcnic_info_le);

	nic_info_addr = dma_alloc_coherent(&adapter->pdev->dev, nic_size,
					   &nic_dma_t, GFP_KERNEL);
	अगर (!nic_info_addr)
		वापस -ENOMEM;

	nic_info = nic_info_addr;

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_GET_NIC_INFO);
	अगर (err)
		जाओ out_मुक्त_dma;

	cmd.req.arg[1] = MSD(nic_dma_t);
	cmd.req.arg[2] = LSD(nic_dma_t);
	cmd.req.arg[3] = (func_id << 16 | nic_size);
	err = qlcnic_issue_cmd(adapter, &cmd);
	अगर (err != QLCNIC_RCODE_SUCCESS) अणु
		dev_err(&adapter->pdev->dev,
			"Failed to get nic info%d\n", err);
		err = -EIO;
	पूर्ण अन्यथा अणु
		npar_info->pci_func = le16_to_cpu(nic_info->pci_func);
		npar_info->op_mode = le16_to_cpu(nic_info->op_mode);
		npar_info->min_tx_bw = le16_to_cpu(nic_info->min_tx_bw);
		npar_info->max_tx_bw = le16_to_cpu(nic_info->max_tx_bw);
		npar_info->phys_port = le16_to_cpu(nic_info->phys_port);
		npar_info->चयन_mode = le16_to_cpu(nic_info->चयन_mode);
		npar_info->max_tx_ques = le16_to_cpu(nic_info->max_tx_ques);
		npar_info->max_rx_ques = le16_to_cpu(nic_info->max_rx_ques);
		npar_info->capabilities = le32_to_cpu(nic_info->capabilities);
		npar_info->max_mtu = le16_to_cpu(nic_info->max_mtu);
	पूर्ण

	qlcnic_मुक्त_mbx_args(&cmd);
out_मुक्त_dma:
	dma_मुक्त_coherent(&adapter->pdev->dev, nic_size, nic_info_addr,
			  nic_dma_t);

	वापस err;
पूर्ण

/* Configure a NIC partition */
पूर्णांक qlcnic_82xx_set_nic_info(काष्ठा qlcnic_adapter *adapter,
			     काष्ठा qlcnic_info *nic)
अणु
	पूर्णांक err = -EIO;
	dma_addr_t nic_dma_t;
	व्योम *nic_info_addr;
	काष्ठा qlcnic_cmd_args cmd;
	काष्ठा qlcnic_info_le *nic_info;
	माप_प्रकार nic_size = माप(काष्ठा qlcnic_info_le);

	अगर (adapter->ahw->op_mode != QLCNIC_MGMT_FUNC)
		वापस err;

	nic_info_addr = dma_alloc_coherent(&adapter->pdev->dev, nic_size,
					   &nic_dma_t, GFP_KERNEL);
	अगर (!nic_info_addr)
		वापस -ENOMEM;

	nic_info = nic_info_addr;

	nic_info->pci_func = cpu_to_le16(nic->pci_func);
	nic_info->op_mode = cpu_to_le16(nic->op_mode);
	nic_info->phys_port = cpu_to_le16(nic->phys_port);
	nic_info->चयन_mode = cpu_to_le16(nic->चयन_mode);
	nic_info->capabilities = cpu_to_le32(nic->capabilities);
	nic_info->max_mac_filters = nic->max_mac_filters;
	nic_info->max_tx_ques = cpu_to_le16(nic->max_tx_ques);
	nic_info->max_rx_ques = cpu_to_le16(nic->max_rx_ques);
	nic_info->min_tx_bw = cpu_to_le16(nic->min_tx_bw);
	nic_info->max_tx_bw = cpu_to_le16(nic->max_tx_bw);

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_SET_NIC_INFO);
	अगर (err)
		जाओ out_मुक्त_dma;

	cmd.req.arg[1] = MSD(nic_dma_t);
	cmd.req.arg[2] = LSD(nic_dma_t);
	cmd.req.arg[3] = ((nic->pci_func << 16) | nic_size);
	err = qlcnic_issue_cmd(adapter, &cmd);

	अगर (err != QLCNIC_RCODE_SUCCESS) अणु
		dev_err(&adapter->pdev->dev,
			"Failed to set nic info%d\n", err);
		err = -EIO;
	पूर्ण

	qlcnic_मुक्त_mbx_args(&cmd);
out_मुक्त_dma:
	dma_मुक्त_coherent(&adapter->pdev->dev, nic_size, nic_info_addr,
			  nic_dma_t);

	वापस err;
पूर्ण

/* Get PCI Info of a partition */
पूर्णांक qlcnic_82xx_get_pci_info(काष्ठा qlcnic_adapter *adapter,
			     काष्ठा qlcnic_pci_info *pci_info)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	माप_प्रकार npar_size = माप(काष्ठा qlcnic_pci_info_le);
	माप_प्रकार pci_size = npar_size * ahw->max_vnic_func;
	u16 nic = 0, fcoe = 0, iscsi = 0;
	काष्ठा qlcnic_pci_info_le *npar;
	काष्ठा qlcnic_cmd_args cmd;
	dma_addr_t pci_info_dma_t;
	व्योम *pci_info_addr;
	पूर्णांक err = 0, i;

	pci_info_addr = dma_alloc_coherent(&adapter->pdev->dev, pci_size,
					   &pci_info_dma_t, GFP_KERNEL);
	अगर (!pci_info_addr)
		वापस -ENOMEM;

	npar = pci_info_addr;
	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_GET_PCI_INFO);
	अगर (err)
		जाओ out_मुक्त_dma;

	cmd.req.arg[1] = MSD(pci_info_dma_t);
	cmd.req.arg[2] = LSD(pci_info_dma_t);
	cmd.req.arg[3] = pci_size;
	err = qlcnic_issue_cmd(adapter, &cmd);

	ahw->total_nic_func = 0;
	अगर (err == QLCNIC_RCODE_SUCCESS) अणु
		क्रम (i = 0; i < ahw->max_vnic_func; i++, npar++, pci_info++) अणु
			pci_info->id = le16_to_cpu(npar->id);
			pci_info->active = le16_to_cpu(npar->active);
			अगर (!pci_info->active)
				जारी;
			pci_info->type = le16_to_cpu(npar->type);
			err = qlcnic_get_pci_func_type(adapter, pci_info->type,
						       &nic, &fcoe, &iscsi);
			pci_info->शेष_port =
				le16_to_cpu(npar->शेष_port);
			pci_info->tx_min_bw =
				le16_to_cpu(npar->tx_min_bw);
			pci_info->tx_max_bw =
				le16_to_cpu(npar->tx_max_bw);
			स_नकल(pci_info->mac, npar->mac, ETH_ALEN);
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(&adapter->pdev->dev,
			"Failed to get PCI Info%d\n", err);
		err = -EIO;
	पूर्ण

	ahw->total_nic_func = nic;
	ahw->total_pci_func = nic + fcoe + iscsi;
	अगर (ahw->total_nic_func == 0 || ahw->total_pci_func == 0) अणु
		dev_err(&adapter->pdev->dev,
			"%s: Invalid function count: total nic func[%x], total pci func[%x]\n",
			__func__, ahw->total_nic_func, ahw->total_pci_func);
		err = -EIO;
	पूर्ण
	qlcnic_मुक्त_mbx_args(&cmd);
out_मुक्त_dma:
	dma_मुक्त_coherent(&adapter->pdev->dev, pci_size, pci_info_addr,
		pci_info_dma_t);

	वापस err;
पूर्ण

/* Configure eSwitch क्रम port mirroring */
पूर्णांक qlcnic_config_port_mirroring(काष्ठा qlcnic_adapter *adapter, u8 id,
				 u8 enable_mirroring, u8 pci_func)
अणु
	काष्ठा device *dev = &adapter->pdev->dev;
	काष्ठा qlcnic_cmd_args cmd;
	पूर्णांक err = -EIO;
	u32 arg1;

	अगर (adapter->ahw->op_mode != QLCNIC_MGMT_FUNC ||
	    !(adapter->eचयन[id].flags & QLCNIC_SWITCH_ENABLE)) अणु
		dev_err(&adapter->pdev->dev, "%s: Not a management function\n",
			__func__);
		वापस err;
	पूर्ण

	arg1 = id | (enable_mirroring ? BIT_4 : 0);
	arg1 |= pci_func << 8;

	err = qlcnic_alloc_mbx_args(&cmd, adapter,
				    QLCNIC_CMD_SET_PORTMIRRORING);
	अगर (err)
		वापस err;

	cmd.req.arg[1] = arg1;
	err = qlcnic_issue_cmd(adapter, &cmd);

	अगर (err != QLCNIC_RCODE_SUCCESS)
		dev_err(dev, "Failed to configure port mirroring for vNIC function %d on eSwitch %d\n",
			pci_func, id);
	अन्यथा
		dev_info(dev, "Configured port mirroring for vNIC function %d on eSwitch %d\n",
			 pci_func, id);
	qlcnic_मुक्त_mbx_args(&cmd);

	वापस err;
पूर्ण

पूर्णांक qlcnic_get_port_stats(काष्ठा qlcnic_adapter *adapter, स्थिर u8 func,
		स्थिर u8 rx_tx, काष्ठा __qlcnic_esw_statistics *esw_stats) अणु

	माप_प्रकार stats_size = माप(काष्ठा qlcnic_esw_stats_le);
	काष्ठा qlcnic_esw_stats_le *stats;
	dma_addr_t stats_dma_t;
	व्योम *stats_addr;
	u32 arg1;
	काष्ठा qlcnic_cmd_args cmd;
	पूर्णांक err;

	अगर (esw_stats == शून्य)
		वापस -ENOMEM;

	अगर ((adapter->ahw->op_mode != QLCNIC_MGMT_FUNC) &&
	    (func != adapter->ahw->pci_func)) अणु
		dev_err(&adapter->pdev->dev,
			"Not privilege to query stats for func=%d", func);
		वापस -EIO;
	पूर्ण

	stats_addr = dma_alloc_coherent(&adapter->pdev->dev, stats_size,
					&stats_dma_t, GFP_KERNEL);
	अगर (!stats_addr)
		वापस -ENOMEM;

	arg1 = func | QLCNIC_STATS_VERSION << 8 | QLCNIC_STATS_PORT << 12;
	arg1 |= rx_tx << 15 | stats_size << 16;

	err = qlcnic_alloc_mbx_args(&cmd, adapter,
				    QLCNIC_CMD_GET_ESWITCH_STATS);
	अगर (err)
		जाओ out_मुक्त_dma;

	cmd.req.arg[1] = arg1;
	cmd.req.arg[2] = MSD(stats_dma_t);
	cmd.req.arg[3] = LSD(stats_dma_t);
	err = qlcnic_issue_cmd(adapter, &cmd);

	अगर (!err) अणु
		stats = stats_addr;
		esw_stats->context_id = le16_to_cpu(stats->context_id);
		esw_stats->version = le16_to_cpu(stats->version);
		esw_stats->size = le16_to_cpu(stats->size);
		esw_stats->multicast_frames =
				le64_to_cpu(stats->multicast_frames);
		esw_stats->broadcast_frames =
				le64_to_cpu(stats->broadcast_frames);
		esw_stats->unicast_frames = le64_to_cpu(stats->unicast_frames);
		esw_stats->dropped_frames = le64_to_cpu(stats->dropped_frames);
		esw_stats->local_frames = le64_to_cpu(stats->local_frames);
		esw_stats->errors = le64_to_cpu(stats->errors);
		esw_stats->numbytes = le64_to_cpu(stats->numbytes);
	पूर्ण

	qlcnic_मुक्त_mbx_args(&cmd);
out_मुक्त_dma:
	dma_मुक्त_coherent(&adapter->pdev->dev, stats_size, stats_addr,
			  stats_dma_t);

	वापस err;
पूर्ण

/* This routine will retrieve the MAC statistics from firmware */
पूर्णांक qlcnic_get_mac_stats(काष्ठा qlcnic_adapter *adapter,
		काष्ठा qlcnic_mac_statistics *mac_stats)
अणु
	काष्ठा qlcnic_mac_statistics_le *stats;
	काष्ठा qlcnic_cmd_args cmd;
	माप_प्रकार stats_size = माप(काष्ठा qlcnic_mac_statistics_le);
	dma_addr_t stats_dma_t;
	व्योम *stats_addr;
	पूर्णांक err;

	अगर (mac_stats == शून्य)
		वापस -ENOMEM;

	stats_addr = dma_alloc_coherent(&adapter->pdev->dev, stats_size,
					&stats_dma_t, GFP_KERNEL);
	अगर (!stats_addr)
		वापस -ENOMEM;

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_GET_MAC_STATS);
	अगर (err)
		जाओ out_मुक्त_dma;

	cmd.req.arg[1] = stats_size << 16;
	cmd.req.arg[2] = MSD(stats_dma_t);
	cmd.req.arg[3] = LSD(stats_dma_t);
	err = qlcnic_issue_cmd(adapter, &cmd);
	अगर (!err) अणु
		stats = stats_addr;
		mac_stats->mac_tx_frames = le64_to_cpu(stats->mac_tx_frames);
		mac_stats->mac_tx_bytes = le64_to_cpu(stats->mac_tx_bytes);
		mac_stats->mac_tx_mcast_pkts =
					le64_to_cpu(stats->mac_tx_mcast_pkts);
		mac_stats->mac_tx_bcast_pkts =
					le64_to_cpu(stats->mac_tx_bcast_pkts);
		mac_stats->mac_rx_frames = le64_to_cpu(stats->mac_rx_frames);
		mac_stats->mac_rx_bytes = le64_to_cpu(stats->mac_rx_bytes);
		mac_stats->mac_rx_mcast_pkts =
					le64_to_cpu(stats->mac_rx_mcast_pkts);
		mac_stats->mac_rx_length_error =
				le64_to_cpu(stats->mac_rx_length_error);
		mac_stats->mac_rx_length_small =
				le64_to_cpu(stats->mac_rx_length_small);
		mac_stats->mac_rx_length_large =
				le64_to_cpu(stats->mac_rx_length_large);
		mac_stats->mac_rx_jabber = le64_to_cpu(stats->mac_rx_jabber);
		mac_stats->mac_rx_dropped = le64_to_cpu(stats->mac_rx_dropped);
		mac_stats->mac_rx_crc_error = le64_to_cpu(stats->mac_rx_crc_error);
	पूर्ण अन्यथा अणु
		dev_err(&adapter->pdev->dev,
			"%s: Get mac stats failed, err=%d.\n", __func__, err);
	पूर्ण

	qlcnic_मुक्त_mbx_args(&cmd);

out_मुक्त_dma:
	dma_मुक्त_coherent(&adapter->pdev->dev, stats_size, stats_addr,
			  stats_dma_t);

	वापस err;
पूर्ण

पूर्णांक qlcnic_get_eचयन_stats(काष्ठा qlcnic_adapter *adapter, स्थिर u8 eचयन,
		स्थिर u8 rx_tx, काष्ठा __qlcnic_esw_statistics *esw_stats) अणु

	काष्ठा __qlcnic_esw_statistics port_stats;
	u8 i;
	पूर्णांक ret = -EIO;

	अगर (esw_stats == शून्य)
		वापस -ENOMEM;
	अगर (adapter->ahw->op_mode != QLCNIC_MGMT_FUNC)
		वापस -EIO;
	अगर (adapter->npars == शून्य)
		वापस -EIO;

	स_रखो(esw_stats, 0, माप(u64));
	esw_stats->unicast_frames = QLCNIC_STATS_NOT_AVAIL;
	esw_stats->multicast_frames = QLCNIC_STATS_NOT_AVAIL;
	esw_stats->broadcast_frames = QLCNIC_STATS_NOT_AVAIL;
	esw_stats->dropped_frames = QLCNIC_STATS_NOT_AVAIL;
	esw_stats->errors = QLCNIC_STATS_NOT_AVAIL;
	esw_stats->local_frames = QLCNIC_STATS_NOT_AVAIL;
	esw_stats->numbytes = QLCNIC_STATS_NOT_AVAIL;
	esw_stats->context_id = eचयन;

	क्रम (i = 0; i < adapter->ahw->total_nic_func; i++) अणु
		अगर (adapter->npars[i].phy_port != eचयन)
			जारी;

		स_रखो(&port_stats, 0, माप(काष्ठा __qlcnic_esw_statistics));
		अगर (qlcnic_get_port_stats(adapter, adapter->npars[i].pci_func,
					  rx_tx, &port_stats))
			जारी;

		esw_stats->size = port_stats.size;
		esw_stats->version = port_stats.version;
		QLCNIC_ADD_ESW_STATS(esw_stats->unicast_frames,
						port_stats.unicast_frames);
		QLCNIC_ADD_ESW_STATS(esw_stats->multicast_frames,
						port_stats.multicast_frames);
		QLCNIC_ADD_ESW_STATS(esw_stats->broadcast_frames,
						port_stats.broadcast_frames);
		QLCNIC_ADD_ESW_STATS(esw_stats->dropped_frames,
						port_stats.dropped_frames);
		QLCNIC_ADD_ESW_STATS(esw_stats->errors,
						port_stats.errors);
		QLCNIC_ADD_ESW_STATS(esw_stats->local_frames,
						port_stats.local_frames);
		QLCNIC_ADD_ESW_STATS(esw_stats->numbytes,
						port_stats.numbytes);
		ret = 0;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक qlcnic_clear_esw_stats(काष्ठा qlcnic_adapter *adapter, स्थिर u8 func_esw,
		स्थिर u8 port, स्थिर u8 rx_tx)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा qlcnic_cmd_args cmd;
	पूर्णांक err;
	u32 arg1;

	अगर (ahw->op_mode != QLCNIC_MGMT_FUNC)
		वापस -EIO;

	अगर (func_esw == QLCNIC_STATS_PORT) अणु
		अगर (port >= ahw->max_vnic_func)
			जाओ err_ret;
	पूर्ण अन्यथा अगर (func_esw == QLCNIC_STATS_ESWITCH) अणु
		अगर (port >= QLCNIC_NIU_MAX_XG_PORTS)
			जाओ err_ret;
	पूर्ण अन्यथा अणु
		जाओ err_ret;
	पूर्ण

	अगर (rx_tx > QLCNIC_QUERY_TX_COUNTER)
		जाओ err_ret;

	arg1 = port | QLCNIC_STATS_VERSION << 8 | func_esw << 12;
	arg1 |= BIT_14 | rx_tx << 15;

	err = qlcnic_alloc_mbx_args(&cmd, adapter,
				    QLCNIC_CMD_GET_ESWITCH_STATS);
	अगर (err)
		वापस err;

	cmd.req.arg[1] = arg1;
	err = qlcnic_issue_cmd(adapter, &cmd);
	qlcnic_मुक्त_mbx_args(&cmd);
	वापस err;

err_ret:
	dev_err(&adapter->pdev->dev,
		"Invalid args func_esw %d port %d rx_ctx %d\n",
		func_esw, port, rx_tx);
	वापस -EIO;
पूर्ण

अटल पूर्णांक __qlcnic_get_eचयन_port_config(काष्ठा qlcnic_adapter *adapter,
					    u32 *arg1, u32 *arg2)
अणु
	काष्ठा device *dev = &adapter->pdev->dev;
	काष्ठा qlcnic_cmd_args cmd;
	u8 pci_func = *arg1 >> 8;
	पूर्णांक err;

	err = qlcnic_alloc_mbx_args(&cmd, adapter,
				    QLCNIC_CMD_GET_ESWITCH_PORT_CONFIG);
	अगर (err)
		वापस err;

	cmd.req.arg[1] = *arg1;
	err = qlcnic_issue_cmd(adapter, &cmd);
	*arg1 = cmd.rsp.arg[1];
	*arg2 = cmd.rsp.arg[2];
	qlcnic_मुक्त_mbx_args(&cmd);

	अगर (err == QLCNIC_RCODE_SUCCESS)
		dev_info(dev, "Get eSwitch port config for vNIC function %d\n",
			 pci_func);
	अन्यथा
		dev_err(dev, "Failed to get eswitch port config for vNIC function %d\n",
			pci_func);
	वापस err;
पूर्ण
/* Configure eSwitch port
op_mode = 0 क्रम setting शेष port behavior
op_mode = 1 क्रम setting  vlan id
op_mode = 2 क्रम deleting vlan id
op_type = 0 क्रम vlan_id
op_type = 1 क्रम port vlan_id
*/
पूर्णांक qlcnic_config_चयन_port(काष्ठा qlcnic_adapter *adapter,
		काष्ठा qlcnic_esw_func_cfg *esw_cfg)
अणु
	काष्ठा device *dev = &adapter->pdev->dev;
	काष्ठा qlcnic_cmd_args cmd;
	पूर्णांक err = -EIO, index;
	u32 arg1, arg2 = 0;
	u8 pci_func;

	अगर (adapter->ahw->op_mode != QLCNIC_MGMT_FUNC) अणु
		dev_err(&adapter->pdev->dev, "%s: Not a management function\n",
			__func__);
		वापस err;
	पूर्ण

	pci_func = esw_cfg->pci_func;
	index = qlcnic_is_valid_nic_func(adapter, pci_func);
	अगर (index < 0)
		वापस err;
	arg1 = (adapter->npars[index].phy_port & BIT_0);
	arg1 |= (pci_func << 8);

	अगर (__qlcnic_get_eचयन_port_config(adapter, &arg1, &arg2))
		वापस err;
	arg1 &= ~(0x0ff << 8);
	arg1 |= (pci_func << 8);
	arg1 &= ~(BIT_2 | BIT_3);
	चयन (esw_cfg->op_mode) अणु
	हाल QLCNIC_PORT_DEFAULTS:
		arg1 |= (BIT_4 | BIT_6 | BIT_7);
		arg2 |= (BIT_0 | BIT_1);
		अगर (adapter->ahw->capabilities & QLCNIC_FW_CAPABILITY_TSO)
			arg2 |= (BIT_2 | BIT_3);
		अगर (!(esw_cfg->discard_tagged))
			arg1 &= ~BIT_4;
		अगर (!(esw_cfg->promisc_mode))
			arg1 &= ~BIT_6;
		अगर (!(esw_cfg->mac_override))
			arg1 &= ~BIT_7;
		अगर (!(esw_cfg->mac_anti_spoof))
			arg2 &= ~BIT_0;
		अगर (!(esw_cfg->offload_flags & BIT_0))
			arg2 &= ~(BIT_1 | BIT_2 | BIT_3);
		अगर (!(esw_cfg->offload_flags & BIT_1))
			arg2 &= ~BIT_2;
		अगर (!(esw_cfg->offload_flags & BIT_2))
			arg2 &= ~BIT_3;
		अवरोध;
	हाल QLCNIC_ADD_VLAN:
			arg1 &= ~(0x0ffff << 16);
			arg1 |= (BIT_2 | BIT_5);
			arg1 |= (esw_cfg->vlan_id << 16);
			अवरोध;
	हाल QLCNIC_DEL_VLAN:
			arg1 |= (BIT_3 | BIT_5);
			arg1 &= ~(0x0ffff << 16);
			अवरोध;
	शेष:
		dev_err(&adapter->pdev->dev, "%s: Invalid opmode 0x%x\n",
			__func__, esw_cfg->op_mode);
		वापस err;
	पूर्ण

	err = qlcnic_alloc_mbx_args(&cmd, adapter,
				    QLCNIC_CMD_CONFIGURE_ESWITCH);
	अगर (err)
		वापस err;

	cmd.req.arg[1] = arg1;
	cmd.req.arg[2] = arg2;
	err = qlcnic_issue_cmd(adapter, &cmd);
	qlcnic_मुक्त_mbx_args(&cmd);

	अगर (err != QLCNIC_RCODE_SUCCESS)
		dev_err(dev, "Failed to configure eswitch for vNIC function %d\n",
			pci_func);
	अन्यथा
		dev_info(dev, "Configured eSwitch for vNIC function %d\n",
			 pci_func);

	वापस err;
पूर्ण

पूर्णांक
qlcnic_get_eचयन_port_config(काष्ठा qlcnic_adapter *adapter,
			काष्ठा qlcnic_esw_func_cfg *esw_cfg)
अणु
	u32 arg1, arg2;
	पूर्णांक index;
	u8 phy_port;

	अगर (adapter->ahw->op_mode == QLCNIC_MGMT_FUNC) अणु
		index = qlcnic_is_valid_nic_func(adapter, esw_cfg->pci_func);
		अगर (index < 0)
			वापस -EIO;
		phy_port = adapter->npars[index].phy_port;
	पूर्ण अन्यथा अणु
		phy_port = adapter->ahw->physical_port;
	पूर्ण
	arg1 = phy_port;
	arg1 |= (esw_cfg->pci_func << 8);
	अगर (__qlcnic_get_eचयन_port_config(adapter, &arg1, &arg2))
		वापस -EIO;

	esw_cfg->discard_tagged = !!(arg1 & BIT_4);
	esw_cfg->host_vlan_tag = !!(arg1 & BIT_5);
	esw_cfg->promisc_mode = !!(arg1 & BIT_6);
	esw_cfg->mac_override = !!(arg1 & BIT_7);
	esw_cfg->vlan_id = LSW(arg1 >> 16);
	esw_cfg->mac_anti_spoof = (arg2 & 0x1);
	esw_cfg->offload_flags = ((arg2 >> 1) & 0x7);

	वापस 0;
पूर्ण
